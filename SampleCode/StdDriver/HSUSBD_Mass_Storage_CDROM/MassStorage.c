/***************************************************************************//**
 * @file     MassStorage.c
 * @brief    M480 HSUSBD driver Sample file
 * @version  V1.00
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2024 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

/*!<Includes */
#include <string.h>
#include "NuMicro.h"
#include "massstorage.h"

/*--------------------------------------------------------------------------*/
/* Global variables for Control Pipe */
int32_t g_TotalSectors = 0;

/* USB flow control variables */
uint8_t g_u8BulkState = BULK_NORMAL;
uint8_t g_u8Prevent = 0;
uint8_t volatile g_u8Remove = 0;
uint8_t volatile g_u8MscOutPacket = 0;
uint8_t g_au8SenseKey[4];

uint32_t g_u32MSCMaxLun = 0;
uint32_t g_u32Address;
uint32_t g_u32LbaAddress;
uint32_t g_u32MassBase, g_u32StorageBase;

uint32_t g_u32EpMaxPacketSize;
uint32_t g_u32CbwSize = 0;

/* CBW/CSW variables */
struct CBW g_sCBW;
struct CSW g_sCSW;

uint8_t gMassBuf[MASS_BUFFER_SIZE];
uint8_t gStorageBuf[STORAGE_BUFFER_SIZE];

/*--------------------------------------------------------------------------*/
uint8_t g_au8InquiryID[36] =
{
    0x05,                   /* Peripheral Device Type : CD/DVD */
    0x80,                   /* RMB */
    0x00,                   /* ISO/ECMA, ANSI Version */
    0x32,                   /* Response Data Format */
    0x1F, 0x00, 0x00, 0x00, /* Additional Length */

    /* Vendor Identification */
    'N', 'u', 'v', 'o', 't', 'o', 'n', ' ',

    /* Product Identification */
    'U', 'S', 'B', ' ', 'C', 'D', 'R', 'O', 'M', ' ', ' ', ' ', ' ',

    /* Product Revision */
    '2', '.', '0', '0'
};

// code = 5Ah, Mode Sense
static uint8_t g_au8ModePage_01[12] =
{
    0x01, 0x0A, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x03, 0x00, 0x00, 0x00
};

static uint8_t g_au8ModePage_05[32] =
{
    0x05, 0x1E, 0x13, 0x88, 0x08, 0x20, 0x02, 0x00,
    0x01, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x05, 0x1E, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x68, 0x00, 0x00
};

static uint8_t g_au8ModePage_1B[12] =
{
    0x1B, 0x0A, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00
};

static uint8_t g_au8ModePage_1C[8] =
{
    0x1C, 0x06, 0x00, 0x05, 0x00, 0x00, 0x00, 0x00
};

static uint8_t g_au8ModeSense_1A[12] =
{
    0x00, 0x12, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x1A, 0x0A, 0x00, 0x03
};

static uint8_t g_au8ModeSense_2A[40] =
{
    0x00, 0x36, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x2A, 0x2E, 0x3F, 0x37, 0xF5, 0x73, 0x29, 0x23,
    0x1B, 0x90, 0x01, 0x00, 0x05, 0x8B, 0x1B, 0x90,
    0x00, 0x00, 0x1B, 0x90, 0x1B, 0x90, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x01, 0x1B, 0x90, 0x00, 0x04
};

static uint8_t g_au8ReadTOC_LBA0[] =
{
    // TOC response header
    0x00, 0x12,
    0x01,
    0x01,
    // track descriptor 1
    0x00,
    0x14,
    0x01,
    0x00,
    0x00, 0x00, 0x00, 0x00,
    // track descriptor 2
    0x00,
    0x14,
    0xAA,
    0x00,
    0x00, 0x00, 0x08, 0x00
};

static uint8_t g_au8ReadTOC_LBA1[] =
{
    // TOC response header
    0x00, 0x0A,
    0x01,
    0x01,
    // track descriptor
    0x00,
    0x14,
    0x01,
    0x00,
    0x00, 0x00, 0x00, 0x00
};

static uint8_t g_au8ReadTOC_MSF0[] =
{
    // TOC response header
    0x00, 0x12,
    0x01,
    0x01,
    // track descriptor 1
    0x00,
    0x14,
    0x01,
    0x00,
    0x00, 0x00, 0x02, 0x00,
    // track descriptor 2
    0x00,
    0x14,
    0xAA,
    0x00,
    0x00, 0x00, 0x29, 0x23
};

static uint8_t g_au8ReadTOC_MSF2[] =
{
    // TOC response header
    0x00, 0x2E,             // Data Length
    0x01,                   // First Track
    0x01,                   // Last Track
    // track descriptors
    // Session ADR/CTRL  TNO   POINT  Min Sec Frame  ZERO PMIN PSEC PFRAME
    0x01,    0x14,   0x00, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
    0x01,    0x14,   0x00, 0xA1, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
    0x01,    0x14,   0x00, 0xA2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1d, 0x17,
    0x01,    0x14,   0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x00
};

static const uint8_t g_au8GetConfiguration[] =
{
    // Feature Header
    0x00, 0x00, 0x00, 0x4C, // Data Length
    0x00, 0x00,             // Reserved
    0x00, 0x00,             // Current Profile
    // Profile List
    0x00, 0x00,             // Feature Code (0000h = Profile List)
    0x03,                   // Version(0) /Persistent(1) /Current(1)
    0x04,                   // Additional Length (= number of profile descriptor x 4)
    // Profile Descriptor
    0x00, 0x08,             // Profile Number (CD-ROM)
    0x00,                   // CurrentP
    0x00,                   // Reserved
    // Features
    0x00, 0x01,             // Core Feature
    0x0B,                   // Version(2) /Persistent(1) /Current(1)
    0x08,                   // Additional Length
    0x00, 0x00, 0x00, 0x02, // Physical Interface Standard (0x00000002: ATAPI)
    0x01,                   // INQ2(0) / Device Busy Event(1)
    0x00, 0x00, 0x00,       // Reserved

    0x00, 0x02,             // Morphing Feature
    0x07,                   // Version(2) /Persistent(1) /Current(1)
    0x04,                   // Additional Length
    0x02,                   // OCEvent(1) / ASYNC(0)
    0x00, 0x00, 0x00,       // Reserved

    0x00, 0x03,             // Removable Medium Feature
    0x0B,                   // Version(0) /Persistent(1) /Current(1)
    0x04,                   // Additional Length
    0x29,                   // Loading mechanism (Tray:001h) /Eject(1) / Pvnt Jmpr(0) / Lock(1)
    0x00, 0x00, 0x00,       // Reserved

    0x00, 0x10,             // Random Readable Feature
    0x00,                   // Version(0) /Persistent(0) /Current(0)
    0x08,                   // Additional Length
    0x00, 0x00, 0x08, 0x00, // Logical Block Size
    0x00, 0x01,             // Blocking
    0x00,                   // Page Present
    0x00,                   // Reserved

    0x00, 0x1E,             // CD Read Feature
    0x08,                   // Version(2) /Persistent(0) /Current(0)
    0x04,                   // Additional Length
    0x00,                   // DAP(0) / C2 Flags(0) / CD-Text(0)
    0x00, 0x00, 0x00,       // Reserved

    0x01, 0x00,             // Power Management Feature
    0x03,                   // Version(0) /Persistent(1) /Current(1)
    0x00,                   // Additional Length

    0x01, 0x05,             // Timeout Feature
    0x07,                   // Version(1) /Persistent(1) /Current(1)
    0x04,                   // Additional Length
    0x00,                   // Group3
    0x00,                   // Reserved
    0x00, 0x00,             // Unit Length
};

static uint8_t g_au8GetEventStatusNotification_01[8] =
{
    0x00, 0x02, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00
};

static uint8_t g_au8ReadDiskInformation[8] =
{
    0x00, 0x20, 0x01, 0x01, 0x02, 0x02, 0x02, 0x80
};

static uint8_t g_au8ReportKey[8] =
{
    0x00, 0x06, 0x00, 0x00, 0x64, 0xFE, 0x01, 0x00
};

static uint8_t g_au8ModePage[24] =
{
    0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x00, 0x1C, 0x0A, 0x80, 0x03,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01
};

void USBD20_IRQHandler(void)
{
    __IO uint32_t IrqStL, IrqSt;

    IrqStL = HSUSBD->GINTSTS & HSUSBD->GINTEN;    /* get interrupt status */

    if (!IrqStL)    return;

    /* USB interrupt */
    if (IrqStL & HSUSBD_GINTSTS_USBIF_Msk) {
        IrqSt = HSUSBD->BUSINTSTS & HSUSBD->BUSINTEN;

        if (IrqSt & HSUSBD_BUSINTSTS_SOFIF_Msk)
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_SOFIF_Msk);

        if (IrqSt & HSUSBD_BUSINTSTS_RSTIF_Msk) {
            HSUSBD_SwReset();
            g_u8Remove = 0;
            g_u8BulkState = BULK_CBW;

            HSUSBD_ResetDMA();
            HSUSBD->EP[EPA].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;
            HSUSBD->EP[EPB].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;

            if (HSUSBD->OPER & 0x04)  /* high speed */
                MSC_InitForHighSpeed();
            else                    /* full speed */
                MSC_InitForFullSpeed();
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
            HSUSBD_SET_ADDR(0);
            HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RSTIEN_Msk|HSUSBD_BUSINTEN_RESUMEIEN_Msk|HSUSBD_BUSINTEN_SUSPENDIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_RSTIF_Msk);
            HSUSBD_CLR_CEP_INT_FLAG(0x1ffc);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_RESUMEIF_Msk) {
            HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RSTIEN_Msk | HSUSBD_BUSINTEN_SUSPENDIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_RESUMEIF_Msk);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_SUSPENDIF_Msk) {
            HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RSTIEN_Msk | HSUSBD_BUSINTEN_RESUMEIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_SUSPENDIF_Msk);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_HISPDIF_Msk) {
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_HISPDIF_Msk);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_DMADONEIF_Msk) {
            g_hsusbd_DmaDone = 1;
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_DMADONEIF_Msk);

            if (HSUSBD->DMACTL & HSUSBD_DMACTL_DMARD_Msk) {
                if (g_hsusbd_ShortPacket == 1) {
                    HSUSBD->EP[EPA].EPRSPCTL = (HSUSBD->EP[EPA].EPRSPCTL & 0x10) | HSUSBD_EP_RSPCTL_SHORTTXEN;    // packet end
                    g_hsusbd_ShortPacket = 0;
                }
            }
        }

        if (IrqSt & HSUSBD_BUSINTSTS_PHYCLKVLDIF_Msk)
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_PHYCLKVLDIF_Msk);

        if (IrqSt & HSUSBD_BUSINTSTS_VBUSDETIF_Msk) {
            if (HSUSBD_IS_ATTACHED()) {
                /* USB Plug In */
                HSUSBD_ENABLE_USB();
            } else {
                /* USB Un-plug */
                HSUSBD_DISABLE_USB();
            }
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_VBUSDETIF_Msk);
        }
    }

    if (IrqStL & HSUSBD_GINTSTS_CEPIF_Msk) {
        IrqSt = HSUSBD->CEPINTSTS & HSUSBD->CEPINTEN;

        if (IrqSt & HSUSBD_CEPINTSTS_SETUPTKIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_SETUPTKIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_SETUPPKIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_SETUPPKIF_Msk);
            HSUSBD_ProcessSetupPacket();
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_OUTTKIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_OUTTKIF_Msk);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_INTKIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
            if (!(IrqSt & HSUSBD_CEPINTSTS_STSDONEIF_Msk)) {
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_TXPKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_TXPKIEN_Msk);
                HSUSBD_CtrlIn();
            } else {
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_TXPKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_TXPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            }
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_PINGIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_PINGIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_TXPKIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
            if (g_hsusbd_CtrlInSize) {
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_INTKIEN_Msk);
            } else {
                if (g_hsusbd_CtrlZero == 1)
                    HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_ZEROLEN);
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            }
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_TXPKIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_RXPKIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_RXPKIF_Msk);
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_NAKIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_NAKIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_STALLIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STALLIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_ERRIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_ERRIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_STSDONEIF_Msk) {
            HSUSBD_UpdateDeviceState();
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_BUFFULLIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_BUFFULLIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_BUFEMPTYIF_Msk) {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_BUFEMPTYIF_Msk);
            return;
        }
    }

    /* bulk in */
    if (IrqStL & HSUSBD_GINTSTS_EPAIF_Msk) {
        IrqSt = HSUSBD->EP[EPA].EPINTSTS & HSUSBD->EP[EPA].EPINTEN;

        HSUSBD_ENABLE_EP_INT(EPA, 0);
        HSUSBD_CLR_EP_INT_FLAG(EPA, IrqSt);
    }
    /* bulk out */
    if (IrqStL & HSUSBD_GINTSTS_EPBIF_Msk) {
        IrqSt = HSUSBD->EP[EPB].EPINTSTS & HSUSBD->EP[EPB].EPINTEN;
        if (IrqSt & HSUSBD_EPINTSTS_RXPKIF_Msk)
        {
            g_u8MscOutPacket = 1;
        }
        HSUSBD_CLR_EP_INT_FLAG(EPB, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPCIF_Msk) {
        IrqSt = HSUSBD->EP[EPC].EPINTSTS & HSUSBD->EP[EPC].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPC, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPDIF_Msk) {
        IrqSt = HSUSBD->EP[EPD].EPINTSTS & HSUSBD->EP[EPD].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPD, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPEIF_Msk) {
        IrqSt = HSUSBD->EP[EPE].EPINTSTS & HSUSBD->EP[EPE].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPE, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPFIF_Msk) {
        IrqSt = HSUSBD->EP[EPF].EPINTSTS & HSUSBD->EP[EPF].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPF, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPGIF_Msk) {
        IrqSt = HSUSBD->EP[EPG].EPINTSTS & HSUSBD->EP[EPG].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPG, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPHIF_Msk) {
        IrqSt = HSUSBD->EP[EPH].EPINTSTS & HSUSBD->EP[EPH].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPH, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPIIF_Msk) {
        IrqSt = HSUSBD->EP[EPI].EPINTSTS & HSUSBD->EP[EPI].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPI, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPJIF_Msk) {
        IrqSt = HSUSBD->EP[EPJ].EPINTSTS & HSUSBD->EP[EPJ].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPJ, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPKIF_Msk) {
        IrqSt = HSUSBD->EP[EPK].EPINTSTS & HSUSBD->EP[EPK].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPK, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPLIF_Msk) {
        IrqSt = HSUSBD->EP[EPL].EPINTSTS & HSUSBD->EP[EPL].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPL, IrqSt);
    }
}

void MSC_InitForHighSpeed(void)
{
    /*****************************************************/
    /* EPA ==> Bulk IN endpoint, address 1 */
    HSUSBD_SetEpBufAddr(EPA, EPA_BUF_BASE, EPA_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPA, EPA_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPA, BULK_IN_EP_NUM, HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_IN);

    /* EPB ==> Bulk OUT endpoint, address 2 */
    HSUSBD_SetEpBufAddr(EPB, EPB_BUF_BASE, EPB_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPB, EPB_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPB, BULK_OUT_EP_NUM, HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPB, HSUSBD_EPINTEN_RXPKIEN_Msk);

    g_u32EpMaxPacketSize = EPA_MAX_PKT_SIZE;
}

void MSC_InitForFullSpeed(void)
{
    /*****************************************************/
    /* EPA ==> Bulk IN endpoint, address 1 */
    HSUSBD_SetEpBufAddr(EPA, EPA_BUF_BASE, EPA_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPA, EPA_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPA, BULK_IN_EP_NUM, HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_IN);

    /* EPB ==> Bulk OUT endpoint, address 2 */
    HSUSBD_SetEpBufAddr(EPB, EPB_BUF_BASE, EPB_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPB, EPB_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPB, BULK_OUT_EP_NUM, HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPB, HSUSBD_EPINTEN_RXPKIEN_Msk);

    g_u32EpMaxPacketSize = EPA_OTHER_MAX_PKT_SIZE;
}

void MSC_Init(void)
{
    /* Configure USB controller */
    /* Enable USB BUS, CEP and EPA , EPB global interrupt */
    HSUSBD_ENABLE_USB_INT(HSUSBD_GINTEN_USBIEN_Msk|HSUSBD_GINTEN_CEPIEN_Msk|HSUSBD_GINTEN_EPAIEN_Msk|HSUSBD_GINTEN_EPBIEN_Msk);
    /* Enable BUS interrupt */
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_DMADONEIEN_Msk | HSUSBD_BUSINTEN_RESUMEIEN_Msk | HSUSBD_BUSINTEN_RSTIEN_Msk | HSUSBD_BUSINTEN_VBUSDETIEN_Msk);
    /* Reset Address to 0 */
    HSUSBD_SET_ADDR(0);

    /*****************************************************/
    /* Control endpoint */
    HSUSBD_SetEpBufAddr(CEP, CEP_BUF_BASE, CEP_BUF_LEN);
    HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);

    MSC_InitForHighSpeed();

    g_sCSW.dCSWSignature = CSW_SIGNATURE;
    /* when doing FDBENCH, the disk size should >= 5MB */
    g_TotalSectors = DATA_FLASH_STORAGE_SIZE / CDROM_BLOCK_SIZE;
    g_u32MassBase = (uint32_t)gMassBuf;
    g_u32StorageBase = (uint32_t)gStorageBuf;
}

void MSC_ClassRequest(void)
{
    if (gUsbCmd.bmRequestType & 0x80) { /* request data transfer direction */
        // Device to host
        switch (gUsbCmd.bRequest) {
        case GET_MAX_LUN: {
            /* Check interface number with cfg descriptor and check wValue = 0, wLength = 1 */
            if ((gUsbCmd.wValue == 0) && (gUsbCmd.wIndex == 0) && (gUsbCmd.wLength == 1))
            {
                // Return current configuration setting
                HSUSBD_PrepareCtrlIn((uint8_t *)&g_u32MSCMaxLun, 1);
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_INTKIEN_Msk);
            }
            else     /* Invalid Get MaxLun command */
            {
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
            }
            break;
        }
        default: {
            /* Setup error, stall the device */
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
            break;
        }
        }
    } else {
        // Host to device
        switch (gUsbCmd.bRequest) {
        case BULK_ONLY_MASS_STORAGE_RESET: {
            /* Check interface number with cfg descriptor and check wValue = 0, wLength = 0 */
            if ((gUsbCmd.wValue == 0) && (gUsbCmd.wIndex == 0) && (gUsbCmd.wLength == 0))
            {
                g_u8Prevent = 1;
                /* Status stage */
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_STSDONEIEN_Msk);

                g_u32HsEpStallLock = 0;

                HSUSBD_ResetDMA();
                HSUSBD->EP[EPA].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;
                HSUSBD->EP[EPB].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;
                g_u8BulkState = BULK_CBW;
                g_u8MscOutPacket = 0;
            }
            else     /* Invalid Get MaxLun command */
            {
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
            }
            break;
        }
        default: {
            // Stall
            /* Setup error, stall the device */
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
            break;
        }
        }
    }
}

void MSC_ReadTOC(void)
{
    uint32_t u32Len;
    uint8_t u8format = (g_sCBW.u8LUN & 0x0F) | (g_sCBW.au8Data[7] >> 6);

    if (g_sCBW.u8LUN == 0x02)
    {
        switch (u8format)
        {
        case 0x00:
        {
            u32Len = g_sCBW.dCBWDataTransferLength;
            if (u32Len > sizeof(g_au8ReadTOC_MSF0))
                u32Len = sizeof(g_au8ReadTOC_MSF0);
            MSC_BulkIn((uint32_t)&g_au8ReadTOC_MSF0, u32Len);
            break;
        }
        case 0x02:
        {
            u32Len = g_sCBW.dCBWDataTransferLength;
            if (u32Len > sizeof(g_au8ReadTOC_MSF2))
                u32Len = sizeof(g_au8ReadTOC_MSF2);
            MSC_BulkIn((uint32_t)&g_au8ReadTOC_MSF2, u32Len);
            break;
        }
        default:
            g_au8SenseKey[0] = 0x05;
            g_au8SenseKey[1] = 0x24;
            g_au8SenseKey[2] = 0x00;
        }
    }
    else if (g_sCBW.u8LUN == 0x00)
    {
        switch (g_sCBW.au8Data[0])
        {
        case 0x01:
        {
            u32Len = g_sCBW.dCBWDataTransferLength;
            if (u32Len > sizeof(g_au8ReadTOC_LBA1))
                u32Len = sizeof(g_au8ReadTOC_LBA1);
            MSC_BulkIn((uint32_t)&g_au8ReadTOC_LBA1, u32Len);
            break;
        }
        case 0x00:
        {
            u32Len = g_sCBW.dCBWDataTransferLength;
            if (u32Len > sizeof(g_au8ReadTOC_LBA0))
                u32Len = sizeof(g_au8ReadTOC_LBA0);
            MSC_BulkIn((uint32_t)&g_au8ReadTOC_LBA0, u32Len);
            break;
        }
        default:
            g_au8SenseKey[0] = 0x05;
            g_au8SenseKey[1] = 0x24;
            g_au8SenseKey[2] = 0x00;
            break;
        }
    }
    else
    {
        g_au8SenseKey[0] = 0x05;
        g_au8SenseKey[1] = 0x24;
        g_au8SenseKey[2] = 0x00;

        HSUSBD_SetEpStall(EPA);
        g_u8Prevent = 1;
        g_sCSW.bCSWStatus = 0x01;
        g_sCSW.dCSWDataResidue = 0;
        MSC_AckCmd();
        return;
    }
}

void MSC_GetConfiguration(uint32_t u32Len, uint8_t *pu8Buff)
{
    uint32_t u32Index, u32FeatureLen;
    uint8_t  *pu8Ptr;

    if(g_u8Remove)
    {
        memset((int8_t *)pu8Buff, 0, u32Len);
        return;
    }

    if(g_sCBW.u8LUN == 0x02)
    {
        memcpy(pu8Buff, g_au8GetConfiguration, 8);
        u32FeatureLen = 0;
        // the first feature on the array
        u32Index = 8;

        // find the specified feature
        while(u32Index < (sizeof(g_au8GetConfiguration) - u32Index))
        {
            if((g_au8GetConfiguration[u32Index] == g_sCBW.au8Data[0]) && (g_au8GetConfiguration[u32Index + 1] == g_sCBW.au8Data[1]))
            {
                // copy the feature
                u32FeatureLen = g_au8GetConfiguration[u32Index + 3] + 4;
                memcpy(pu8Buff + 8, &g_au8GetConfiguration[u32Index], u32FeatureLen);
                break;
            }
            else
            {
                u32Index += (g_au8GetConfiguration[u32Index + 3] + 4);
            }
        }
        // fix up return length
        u32Len = 8 + u32FeatureLen;
        pu8Buff[3] = (uint8_t)(u32Len - 4);
    }
    else if(g_sCBW.u8LUN == 0x01)
    {
        memcpy(pu8Buff, g_au8GetConfiguration, 8);
        pu8Ptr = pu8Buff + 8;

        // the first feature on the array
        u32Index = 8;

        // find current features
        while(u32Index < (sizeof(g_au8GetConfiguration) - u32Index))
        {
            u32FeatureLen = g_au8GetConfiguration[u32Index + 3] + 4;
            if(g_au8GetConfiguration[u32Index + 2] & 0x01)     // check current bit
            {
                memcpy(pu8Ptr, &g_au8GetConfiguration[u32Index], u32FeatureLen);
                pu8Ptr += u32FeatureLen;
            }
            u32Index += u32FeatureLen;
        }
        u32Len = (uint32_t)(pu8Ptr - pu8Buff);
        pu8Buff[3] = (uint8_t)(u32Len - 4);
    }
    else if(g_sCBW.u8LUN == 0x00)
        memcpy((char *)pu8Buff, &g_au8GetConfiguration[0], sizeof(g_au8GetConfiguration));
    else
    {
        g_au8SenseKey[0] = 0x05;
        g_au8SenseKey[1] = 0x24;
        g_au8SenseKey[2] = 0x00;
    }
}

void MSC_GetEventStatusNotification(void)
{
    uint32_t u32Len;

    u32Len = g_sCBW.dCBWDataTransferLength;
    if(u32Len > 8)
        u32Len = 8;

    MSC_BulkIn((uint32_t)&g_au8GetEventStatusNotification_01, u32Len);
}

void MSC_ReadDiskInformation(void)
{
    uint32_t u32Len;

    u32Len = g_sCBW.dCBWDataTransferLength;
    if(u32Len > 8)
        u32Len = 8;

    MSC_BulkIn((uint32_t)&g_au8ReadDiskInformation, u32Len);
}

void MSC_ReportKey(void)
{
    uint32_t u32Len;

    u32Len = g_sCBW.dCBWDataTransferLength;
    if(u32Len > 8)
        u32Len = 8;

    MSC_BulkIn((uint32_t)&g_au8ReportKey, u32Len);
}

void MSC_RequestSense(void)
{
    memset((uint8_t *)(g_u32MassBase), 0, 18);
    if (g_u8Prevent)
    {
        g_u8Prevent = 0;
        *(uint8_t *)(g_u32MassBase) = 0x70;
    }
    else
        *(uint8_t *)(g_u32MassBase) = 0xf0;

    *(uint8_t *)(g_u32MassBase + 2) = g_au8SenseKey[0];
    *(uint8_t *)(g_u32MassBase + 7) = 0x0a;
    *(uint8_t *)(g_u32MassBase + 12) = g_au8SenseKey[1];
    *(uint8_t *)(g_u32MassBase + 13) = g_au8SenseKey[2];
    MSC_BulkIn(g_u32MassBase, g_sCBW.dCBWDataTransferLength);

    g_au8SenseKey[0] = 0;
    g_au8SenseKey[1] = 0;
    g_au8SenseKey[2] = 0;
}

void MSC_ReadFormatCapacity(void)
{
    memset((uint8_t *)g_u32MassBase, 0, 12);

    *((uint8_t *)(g_u32MassBase + 0)) = 0x00;
    *((uint8_t *)(g_u32MassBase + 1)) = 0x00;
    *((uint8_t *)(g_u32MassBase + 2)) = 0x00;
    *((uint8_t *)(g_u32MassBase + 3)) = 0x08;                    /* Capacity List Length */

    /* Block Count */
    *((uint8_t *)(g_u32MassBase + 4)) = (g_TotalSectors >> 24) & 0xFF;
    *((uint8_t *)(g_u32MassBase + 5)) = (g_TotalSectors >> 16) & 0xFF;
    *((uint8_t *)(g_u32MassBase + 6)) = (g_TotalSectors >>  8) & 0xFF;
    *((uint8_t *)(g_u32MassBase + 7)) = (g_TotalSectors >>  0) & 0xFF;

    /* Block Length */
    *((uint8_t *)(g_u32MassBase + 8)) = 0x02;                    /* Descriptor Code: Formatted Media */
    *((uint8_t *)(g_u32MassBase + 9)) = (CDROM_BLOCK_SIZE >> 16) & 0xFF;
    *((uint8_t *)(g_u32MassBase + 10)) = (CDROM_BLOCK_SIZE >>  8) & 0xFF;
    *((uint8_t *)(g_u32MassBase + 11)) = (CDROM_BLOCK_SIZE >>  0) & 0xFF;

    MSC_BulkIn(g_u32MassBase, g_sCBW.dCBWDataTransferLength);
}

void MSC_ReadCapacity(void)
{
    uint32_t tmp;

    memset((uint8_t *)g_u32MassBase, 0, 8);

    tmp = g_TotalSectors - 1;

    /* Last Logical Block */
    *((uint8_t *)(g_u32MassBase + 0)) = (tmp >> 24) & 0xFF;
    *((uint8_t *)(g_u32MassBase + 1)) = (tmp >> 16) & 0xFF;
    *((uint8_t *)(g_u32MassBase + 2)) = (tmp >>  8) & 0xFF;
    *((uint8_t *)(g_u32MassBase + 3)) = (tmp >>  0) & 0xFF;

    /* Block Length */
    *((uint8_t *)(g_u32MassBase + 4)) = (CDROM_BLOCK_SIZE >> 24) & 0xFF;
    *((uint8_t *)(g_u32MassBase + 5)) = (CDROM_BLOCK_SIZE >> 16) & 0xFF;
    *((uint8_t *)(g_u32MassBase + 6)) = (CDROM_BLOCK_SIZE >>  8) & 0xFF;
    *((uint8_t *)(g_u32MassBase + 7)) = (CDROM_BLOCK_SIZE >>  0) & 0xFF;

    MSC_BulkIn(g_u32MassBase, g_sCBW.dCBWDataTransferLength);
}

void MSC_ModeSense10(void)
{
    uint8_t i,j;
    uint8_t NumHead,NumSector;
    uint16_t NumCyl=0;

    /* Clear the command buffer */
    *((uint32_t *)g_u32MassBase  ) = 0;
    *((uint32_t *)g_u32MassBase + 1) = 0;

    switch (g_sCBW.au8Data[0]) {
    case 0x01:
        *((uint8_t *)g_u32MassBase) = 19;
        i = 8;
        for (j = 0; j<12; j++, i++)
            *((uint8_t *)(g_u32MassBase+i)) = g_au8ModePage_01[j];
        break;

    case 0x05:
        *((uint8_t *)g_u32MassBase) = 39;
        i = 8;
        for (j = 0; j<32; j++, i++)
            *((uint8_t *)(g_u32MassBase+i)) = g_au8ModePage_05[j];

        NumHead = 2;
        NumSector = 64;
        NumCyl = g_TotalSectors / 128;

        *((uint8_t *)(g_u32MassBase+12)) = NumHead;
        *((uint8_t *)(g_u32MassBase+13)) = NumSector;
        *((uint8_t *)(g_u32MassBase+16)) = (uint8_t)(NumCyl >> 8);
        *((uint8_t *)(g_u32MassBase+17)) = (uint8_t)(NumCyl & 0x00ff);
        break;

    case 0x1A:
        *((uint8_t *)g_u32MassBase) = 19;
        i = 8;
        for(j = 0; j < 12; j++, i++)
            *((uint8_t *)(g_u32MassBase + i)) = g_au8ModeSense_1A[j];
        break;

    case 0x1B:
        *((uint8_t *)g_u32MassBase) = 19;
        i = 8;
        for (j = 0; j<12; j++, i++)
            *((uint8_t *)(g_u32MassBase+i)) = g_au8ModePage_1B[j];
        break;

    case 0x1C:
        *((uint8_t *)g_u32MassBase) = 15;
        i = 8;
        for (j = 0; j<8; j++, i++)
            *((uint8_t *)(g_u32MassBase+i)) = g_au8ModePage_1C[j];
        break;

    case 0x3F:
        *((uint8_t *)g_u32MassBase) = 0x47;
        i = 8;
        for (j = 0; j<12; j++, i++)
            *((uint8_t *)(g_u32MassBase+i)) = g_au8ModePage_01[j];
        for (j = 0; j<32; j++, i++)
            *((uint8_t *)(g_u32MassBase+i)) = g_au8ModePage_05[j];
        for (j = 0; j<12; j++, i++)
            *((uint8_t *)(g_u32MassBase+i)) = g_au8ModePage_1B[j];
        for (j = 0; j<8; j++, i++)
            *((uint8_t *)(g_u32MassBase+i)) = g_au8ModePage_1C[j];

        NumHead = 2;
        NumSector = 64;
        NumCyl = g_TotalSectors / 128;

        *((uint8_t *)(g_u32MassBase+24)) = NumHead;
        *((uint8_t *)(g_u32MassBase+25)) = NumSector;
        *((uint8_t *)(g_u32MassBase+28)) = (uint8_t)(NumCyl >> 8);
        *((uint8_t *)(g_u32MassBase+29)) = (uint8_t)(NumCyl & 0x00ff);
        break;

    case 0x2A:
        *((uint8_t *)g_u32MassBase) = 47;
        i = 8;
        for(j = 0; j < 40; j++, i++)
            *((uint8_t *)(g_u32MassBase + i)) = g_au8ModeSense_2A[j];
        break;

    default:
        g_au8SenseKey[0] = 0x05;
        g_au8SenseKey[1] = 0x24;
        g_au8SenseKey[2] = 0x00;
    }
    MSC_BulkIn(g_u32MassBase, g_sCBW.dCBWDataTransferLength);
}

void MSC_ModeSense6(void)
{
    uint8_t i;

    for (i = 0; i<4; i++)
        *((uint8_t *)(g_u32MassBase+i)) = g_au8ModePage[i];

    MSC_BulkIn(g_u32MassBase, g_sCBW.dCBWDataTransferLength);
}

void MSC_BulkOut(uint32_t u32Addr, uint32_t u32Len)
{
    uint32_t u32Loop;
    uint32_t i;

    /* bulk out, dma write, epnum = 2 */
    HSUSBD_SET_DMA_WRITE(BULK_OUT_EP_NUM);
    g_hsusbd_ShortPacket = 0;

    u32Loop = u32Len / USBD_MAX_DMA_LEN;
    for (i=0; i<u32Loop; i++) {
        MSC_ActiveDMA(u32Addr+i*USBD_MAX_DMA_LEN, USBD_MAX_DMA_LEN);
    }

    u32Loop = u32Len % USBD_MAX_DMA_LEN;
    if (u32Loop) {
        MSC_ActiveDMA(u32Addr+i*USBD_MAX_DMA_LEN, u32Loop);
    }
}

void MSC_BulkIn(uint32_t u32Addr, uint32_t u32Len)
{
    uint32_t u32Loop;
    uint32_t i, addr, count;

    /* bulk in, dma read, epnum = 1 */
    HSUSBD_SET_DMA_READ(BULK_IN_EP_NUM);

    u32Loop = u32Len / USBD_MAX_DMA_LEN;
    for (i=0; i<u32Loop; i++) {
        HSUSBD_ENABLE_EP_INT(EPA, HSUSBD_EPINTEN_TXPKIEN_Msk);
        g_hsusbd_ShortPacket = 0;
        while(1) {
            if (HSUSBD_GET_EP_INT_FLAG(EPA) & HSUSBD_EPINTSTS_BUFEMPTYIF_Msk) {
                MSC_ActiveDMA(u32Addr+i*USBD_MAX_DMA_LEN, USBD_MAX_DMA_LEN);
                break;
            }
        }
    }

    addr = u32Addr + i * USBD_MAX_DMA_LEN;
    u32Loop = u32Len % USBD_MAX_DMA_LEN;
    if (u32Loop) {
        count = u32Loop / g_u32EpMaxPacketSize;
        if (count) {
            HSUSBD_ENABLE_EP_INT(EPA, HSUSBD_EPINTEN_TXPKIEN_Msk);
            g_hsusbd_ShortPacket = 0;
            while(1) {
                if (HSUSBD_GET_EP_INT_FLAG(EPA) & HSUSBD_EPINTSTS_BUFEMPTYIF_Msk) {
                    MSC_ActiveDMA(addr, count * g_u32EpMaxPacketSize);
                    break;
                }
            }
            addr += (count * g_u32EpMaxPacketSize);
        }
        count = u32Loop % g_u32EpMaxPacketSize;
        if (count) {
            HSUSBD_ENABLE_EP_INT(EPA, HSUSBD_EPINTEN_TXPKIEN_Msk);
            g_hsusbd_ShortPacket = 1;
            while(1) {
                if (HSUSBD_GET_EP_INT_FLAG(EPA) & HSUSBD_EPINTSTS_BUFEMPTYIF_Msk) {
                    MSC_ActiveDMA(addr, count);
                    break;
                }
            }
        }
    }
}


void MSC_ReceiveCBW(uint32_t u32Buf, uint32_t u32Len)
{
    /* bulk out, dma write, epnum = 2 */
    HSUSBD_SET_DMA_WRITE(BULK_OUT_EP_NUM);

    /* Enable BUS interrupt */
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_DMADONEIEN_Msk | HSUSBD_BUSINTEN_SUSPENDIEN_Msk | HSUSBD_BUSINTEN_RSTIEN_Msk | HSUSBD_BUSINTEN_VBUSDETIEN_Msk);

    HSUSBD_SET_DMA_ADDR(u32Buf);
    HSUSBD_SET_DMA_LEN(u32Len);

    g_hsusbd_DmaDone = 0;
    HSUSBD_ENABLE_DMA();

    while(g_hsusbd_Configured)
    {
        if (g_hsusbd_DmaDone == 1)
            break;

        if (!HSUSBD_IS_ATTACHED())
            break;
    }
}

void MSC_ProcessCmd(void)
{
    uint32_t i;
    uint32_t Hcount, Dcount;

    if (g_u8MscOutPacket)
    {
        g_u8MscOutPacket = 0;

        if (g_u8BulkState == BULK_CBW)
        {
            /* Check CBW */
            g_u32CbwSize = HSUSBD->EP[EPB].EPDATCNT & 0xffff;
            MSC_ReceiveCBW(g_u32MassBase, g_u32CbwSize);

            /* Check Signature & length of CBW */
            if ((*(uint32_t *)(g_u32MassBase) != CBW_SIGNATURE) || (g_u32CbwSize != 31))
            {
                /* Invalid CBW */
                g_u8Prevent = 1;
                HSUSBD_SetEpStall(EPA);
                HSUSBD_SetEpStall(EPB);
                g_u32HsEpStallLock = (1 << EPA) | (1 << EPB);
                return;
            }

            /* Get the CBW */
            for (i = 0; i < 31; i++)
                *((uint8_t *) (&g_sCBW.dCBWSignature) + i) = *(uint8_t *)(g_u32MassBase + i);

            /* Prepare to echo the tag from CBW to CSW */
            g_sCSW.dCSWTag = g_sCBW.dCBWTag;
            Hcount = g_sCBW.dCBWDataTransferLength;

            /* Parse Op-Code of CBW */
            switch (g_sCBW.u8OPCode)
            {
            case UFI_READ_12:
            case UFI_READ_10:
            {
                extern const unsigned long eprom_length;
                Dcount = (get_be32(&g_sCBW.au8Data[4])>>8) * CDROM_BLOCK_SIZE;
                if (g_sCBW.bmCBWFlags == 0x80)      /* IN */
                {
                    if (Hcount == Dcount)   /* Hi == Di (Case 6)*/
                    {
                        g_sCSW.bCSWStatus = 0;
                    }
                    else if (Hcount < Dcount)     /* Hn < Di (Case 2) || Hi < Di (Case 7) */
                    {
                        if (Hcount)     /* Hi < Di (Case 7) */
                        {
                            g_u8Prevent = 1;
                            g_sCSW.bCSWStatus = 0x01;
                        }
                        else     /* Hn < Di (Case 2) */
                        {
                            g_u8Prevent = 1;
                            g_sCSW.bCSWStatus = 0x01;
                            g_sCSW.dCSWDataResidue = 0;
                            MSC_AckCmd();
                            return;
                        }
                    }
                    else if (Hcount > Dcount)     /* Hi > Dn (Case 4) || Hi > Di (Case 5) */
                    {
                        g_u8Prevent = 1;
                        g_sCSW.bCSWStatus = 0x01;
                    }
                }
                else     /* Ho <> Di (Case 10) */
                {
                    g_u8Prevent = 1;
                    HSUSBD_SetEpStall(EPB);
                    g_sCSW.bCSWStatus = 0x01;
                    g_sCSW.dCSWDataResidue = Hcount;
                    MSC_AckCmd();
                    return;
                }
                /* Get LBA address */
                g_u32Address = get_be32(&g_sCBW.au8Data[0]);
                g_u32LbaAddress = g_u32Address * CDROM_BLOCK_SIZE;

                i = g_sCBW.dCBWDataTransferLength;
                if(i > STORAGE_BUFFER_SIZE)
                    i = STORAGE_BUFFER_SIZE;

                if((g_u32LbaAddress >= (16 * CDROM_BLOCK_SIZE)) && ((g_u32LbaAddress - 32768) < eprom_length))
                {
                    /*
                        Because first 32KB of the ISO file are all '0', remove first 32KB data from ISO file
                        to reduce the code size instead of including ISO file directly.
                        The array - eprom is the data of ISO file with offset 32768
                     */
                    g_u32Address = (uint32_t)(&eprom[g_u32LbaAddress - 32768]);
                    g_u32LbaAddress += i;
                }
                else                                             /* Logical Block Address > 32KB */
                {
                    memset((uint32_t*)gStorageBuf, 0, i); /* First 32KB of ISO file are all 0 */
                    g_u32Address = STORAGE_DATA_BUF;
                }

                MSC_BulkIn(g_u32Address, g_sCBW.dCBWDataTransferLength);
                g_sCSW.dCSWDataResidue = 0;
                break;
            }
            case UFI_WRITE_12:
            case UFI_WRITE_10:
            {
                if (g_sCBW.dCBWDataTransferLength == 0)
                {
                    Dcount = (get_be32(&g_sCBW.au8Data[4])>>8) * 512;
                    if (g_sCBW.bmCBWFlags == 0x00)      /* OUT */
                    {
                        if (Hcount == Dcount)   /* Ho == Do (Case 12)*/
                        {
                            g_sCSW.bCSWStatus = 0;
                        }
                        else if (Hcount < Dcount)     /* Hn < Do (Case 3) || Ho < Do (Case 13) */
                        {
                            g_u8Prevent = 1;
                            g_sCSW.bCSWStatus = 0x1;
                            if (Hcount == 0)    /* Hn < Do (Case 3) */
                            {
                                g_sCSW.dCSWDataResidue = 0;
                                MSC_AckCmd();
                                return;
                            }
                        }
                        else if (Hcount > Dcount)     /* Ho > Do (Case 11) */
                        {
                            g_u8Prevent = 1;
                            g_sCSW.bCSWStatus = 0x1;
                        }
                        g_u32Address = STORAGE_DATA_BUF;
                        MSC_BulkOut(g_u32Address, g_sCBW.dCBWDataTransferLength);
                        g_sCSW.dCSWDataResidue = 0;
                    }
                    else     /* Hi <> Do (Case 8) */
                    {
                        g_u8Prevent = 1;
                        g_sCSW.bCSWStatus = 0x1;
                        HSUSBD_SetEpStall(EPA);
                        g_sCSW.dCSWDataResidue = Hcount;
                        MSC_AckCmd();
                        return;
                    }
                }
                HSUSBD_SetEpStall(EPB);
                g_u8Prevent = 1;
                g_sCSW.bCSWStatus = 0x1;
                g_sCSW.dCSWDataResidue = 0;
                break;
            }
            case UFI_PREVENT_ALLOW_MEDIUM_REMOVAL:
            {
                if (g_sCBW.au8Data[2] & 0x01)
                {
                    g_au8SenseKey[0] = 0x05;  //INVALID COMMAND
                    g_au8SenseKey[1] = 0x24;
                    g_au8SenseKey[2] = 0;
                    g_u8Prevent = 1;
                }
                else
                    g_u8Prevent = 0;
                g_sCSW.dCSWDataResidue = 0;
                g_sCSW.bCSWStatus = g_u8Prevent;
                break;
            }
            case UFI_TEST_UNIT_READY:
            {
                if (Hcount != 0)
                {
                    if (g_sCBW.bmCBWFlags == 0)     /* Ho > Dn (Case 9) */
                    {
                        g_u8Prevent = 1;
                        HSUSBD_SetEpStall(EPB);
                        g_sCSW.bCSWStatus = 0x1;
                        g_sCSW.dCSWDataResidue = Hcount;
                        MSC_AckCmd();
                    }
                }
                else     /* Hn == Dn (Case 1) */
                {
                    if (g_u8Remove)
                    {
                        g_sCSW.dCSWDataResidue = 0;
                        g_sCSW.bCSWStatus = 1;
                        g_au8SenseKey[0] = 0x02;    /* Not ready */
                        g_au8SenseKey[1] = 0x3A;
                        g_au8SenseKey[2] = 0;
                        g_u8Prevent = 1;
                    }
                    else
                    {
                        g_sCSW.bCSWStatus = 0;
                        g_sCSW.dCSWDataResidue = 0;
                    }
                    MSC_AckCmd();
                }
                return;
            }
            case UFI_START_STOP:
            {
                if ((g_sCBW.au8Data[2] & 0x03) == 0x2)
                {
                    g_u8Remove = 1;
                }
                g_sCSW.dCSWDataResidue = 0;
                g_sCSW.bCSWStatus = 0;
                break;
            }
            case UFI_VERIFY_10:
            {
                g_sCSW.dCSWDataResidue = 0;
                g_sCSW.bCSWStatus = 0;
                break;
            }
            case UFI_REQUEST_SENSE:
            {
                if ((Hcount > 0) && (Hcount <= 18))
                {
                    MSC_RequestSense();
                    g_sCSW.bCSWStatus = 0;
                    g_sCSW.dCSWDataResidue = 0;
                }
                else
                {
                    HSUSBD_SetEpStall(EPA);
                    g_u8Prevent = 1;
                    g_sCSW.bCSWStatus = 0x01;
                    g_sCSW.dCSWDataResidue = 0;
                }
                break;
            }
            case UFI_READ_FORMAT_CAPACITY:
            {
                MSC_ReadFormatCapacity();
                g_sCSW.dCSWDataResidue = 0;
                g_sCSW.bCSWStatus = 0;
                break;
            }
            case UFI_READ_CAPACITY:
            {
                MSC_ReadCapacity();
                g_sCSW.dCSWDataResidue = 0;
                g_sCSW.bCSWStatus = 0;
                break;
            }
            case UFI_READ_CD:
            {
                g_sCSW.dCSWDataResidue = 0;
                g_sCSW.bCSWStatus = 0;
                break;
            }
            case UFI_MODE_SELECT_6:
            case UFI_MODE_SELECT_10:
            {
                MSC_BulkOut(g_u32StorageBase, g_sCBW.dCBWDataTransferLength);
                g_sCSW.dCSWDataResidue = 0;
                g_sCSW.bCSWStatus = 0;
                break;
            }
            case UFI_MODE_SENSE_10:
            {
                MSC_ModeSense10();

                /* If CBW request for data phase, just return zero packet to end data phase */
                if(g_sCBW.dCBWDataTransferLength > 0)
                    g_sCSW.dCSWDataResidue = Hcount;
                else
                    g_sCSW.dCSWDataResidue = 0;
                g_sCSW.bCSWStatus = 0;
                break;
            }
            case UFI_MODE_SENSE_6:
            {
                MSC_ModeSense6();
                g_sCSW.dCSWDataResidue = Hcount - 4;
                g_sCSW.bCSWStatus = 0;
                break;
            }
            case UFI_INQUIRY:
            {
                if ((Hcount > 0) && (Hcount <= 36))
                {
                    /* Bulk IN buffer */
                    HSUSBD_MemCopy((uint8_t *)(g_u32MassBase), (uint8_t *)g_au8InquiryID, Hcount);
                    MSC_BulkIn(g_u32MassBase, Hcount);
                    g_sCSW.bCSWStatus = 0;
                    g_sCSW.dCSWDataResidue = 0;
                }
                else
                {
                    HSUSBD_SetEpStall(EPA);
                    g_u8Prevent = 1;
                    g_sCSW.bCSWStatus = 0x01;
                    g_sCSW.dCSWDataResidue = 0;
                }
                break;
            }
            case UFI_READ_16:
            {
                HSUSBD_SetEpStall(EPA);
                g_u8Prevent = 1;
                g_sCSW.bCSWStatus = 0x01;
                g_sCSW.dCSWDataResidue = 0;
                break;
            }
            case UFI_READ_TOC:
            {
                MSC_ReadTOC();
                g_sCSW.dCSWDataResidue = 0;
                g_sCSW.bCSWStatus = 0;
                MSC_AckCmd();
                return;
            }
            case UFI_GET_CONFIGURATION:
            {
                MSC_GetConfiguration(g_sCBW.dCBWDataTransferLength, (uint8_t *)gMassBuf);
                MSC_BulkIn(g_u32MassBase, g_sCBW.dCBWDataTransferLength);
                g_sCSW.dCSWDataResidue = 0;
                g_sCSW.bCSWStatus = 0;
                MSC_AckCmd();
                return;
            }
            case UFI_SET_CDROM_SPEED:
            {
                int32_t i32Tmp;

                i32Tmp = g_sCBW.dCBWDataTransferLength - STORAGE_BUFFER_SIZE;
                if(i32Tmp < 0)
                    i32Tmp = 0;

                g_sCSW.dCSWDataResidue = i32Tmp;
                g_sCSW.bCSWStatus = 0;
                break;
            }
            case UFI_GET_EVENT_STATUS_NOTIFICATION:
            {
                MSC_GetEventStatusNotification();
                g_sCSW.dCSWDataResidue = 0;
                g_sCSW.bCSWStatus = 0;
                MSC_AckCmd();
                return;
            }
            case UFI_READ_DISK_INFORMATION:
            {
                MSC_ReadDiskInformation();
                g_sCSW.dCSWDataResidue = 0;
                g_sCSW.bCSWStatus = 0;
                MSC_AckCmd();
                return;
            }
            case UFI_REPORT_KEY:
            {
                MSC_ReportKey();
                g_sCSW.dCSWDataResidue = 0;
                g_sCSW.bCSWStatus = 0;
                MSC_AckCmd();
                return;
            }
            default:
            {
                /* Unsupported command */
                g_au8SenseKey[0] = 0x05;
                g_au8SenseKey[1] = 0x20;
                g_au8SenseKey[2] = 0x00;

                /* If CBW request for data phase, just return zero packet to end data phase */
                if (g_sCBW.dCBWDataTransferLength > 0)
                {
                    g_sCSW.dCSWDataResidue = Hcount;
                    /* Data Phase, zero/short packet */
                    if((g_sCBW.bmCBWFlags & 0x80) != 0)
                    {
                        MSC_BulkIn(g_u32MassBase, g_sCBW.dCBWDataTransferLength);
                    }
                }
                else
                    g_sCSW.dCSWDataResidue = 0;
                g_sCSW.bCSWStatus = g_u8Prevent;
            }
            }
            MSC_AckCmd();
        }
    }

    /* For MSC compliance test, if received an invalid command should stall it */
    while(1)
    {
        if (HSUSBD->EP[EPA].EPINTSTS & HSUSBD_EPINTSTS_BUFEMPTYIF_Msk)
        {
            if (g_u32HsEpStallLock & 0x1)
                HSUSBD_SetEpStall(EPA);
            if (g_u32HsEpStallLock & 0x2)
                HSUSBD_SetEpStall(EPB);
            break;
        }
        else
        {
            if ((HSUSBD_GetEpStall(EPA) == 0) && (!(HSUSBD->EP[EPA].EPINTSTS & HSUSBD_EPINTSTS_BUFEMPTYIF_Msk)))
                HSUSBD->EP[EPA].EPRSPCTL = (HSUSBD->EP[EPA].EPRSPCTL & 0x10) | HSUSBD_EP_RSPCTL_SHORTTXEN;
        }
    }
}

void MSC_ActiveDMA(uint32_t u32Addr, uint32_t u32Len)
{
    /* Enable BUS interrupt */
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_DMADONEIEN_Msk | HSUSBD_BUSINTEN_SUSPENDIEN_Msk | HSUSBD_BUSINTEN_RSTIEN_Msk | HSUSBD_BUSINTEN_VBUSDETIEN_Msk);

    HSUSBD_SET_DMA_ADDR(u32Addr);
    HSUSBD_SET_DMA_LEN(u32Len);
    g_hsusbd_DmaDone = 0;
    HSUSBD_ENABLE_DMA();
    while(g_hsusbd_Configured)
    {
        if (g_hsusbd_DmaDone)
            break;

        if (!HSUSBD_IS_ATTACHED())
            break;
    }
}

void MSC_AckCmd(void)
{
    g_sCSW.bCSWStatus = g_u8Prevent;
    HSUSBD_MemCopy((uint8_t *)g_u32MassBase, (uint8_t *)&g_sCSW.dCSWSignature, 16);
    MSC_BulkIn(g_u32MassBase, 13);
    g_u8BulkState = BULK_CBW;
    g_u8MscOutPacket = 0;
}

void MSC_ReadMedia(uint32_t addr, uint32_t size, uint8_t *buffer)
{
}

void MSC_WriteMedia(uint32_t addr, uint32_t size, uint8_t *buffer)
{
}

