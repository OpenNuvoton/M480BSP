/***************************************************************************//**
 * @file     MassStorage.c
 * @brief    M480 series USBD driver Sample file
 * @version  V1.00
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

/*!<Includes */
#include <string.h>
#include "NuMicro.h"
#include "massstorage.h"

/*--------------------------------------------------------------------------*/
/* Global variables for Control Pipe */
int32_t g_TotalSectors = 0;

uint8_t volatile g_u8EP2Ready = 0;
uint8_t volatile g_u8EP3Ready = 0;
uint8_t volatile g_u8Remove = 0;

/* USB flow control variables */
uint8_t g_u8BulkState;
uint8_t g_u8Prevent = 0;
uint8_t g_u8Size;

uint8_t g_au8SenseKey[4];

uint32_t g_u32DataFlashStartAddr;
uint32_t g_u32Address;
uint32_t g_u32Length;
uint32_t g_u32LbaAddress;
uint32_t g_u32BytesInStorageBuf;

uint32_t g_u32BulkBuf0, g_u32BulkBuf1;
uint32_t volatile g_u32OutToggle = 0, g_u32OutSkip = 0;

/* CBW/CSW variables */
struct CBW g_sCBW;
struct CSW g_sCSW;

uint32_t MassBlock[MASS_BUFFER_SIZE / 4];
uint32_t Storage_Block[STORAGE_BUFFER_SIZE / 4];

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
    '1', '.', '0', '0'
};

// code = 5Ah, Mode Sense 10
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

static uint8_t  g_au8ReadTOC_LBA0[] =
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
    0x01,    0x14,   0x00, 0xA0, 0x00,0x00,0x00, 0x00,0x01,0x00,0x00,
    0x01,    0x14,   0x00, 0xA1, 0x00,0x00,0x00, 0x00,0x01,0x00,0x00,
    0x01,    0x14,   0x00, 0xA2, 0x00,0x00,0x00, 0x00,0x00,0x1d,0x17,
    0x01,    0x14,   0x00, 0x01, 0x00,0x00,0x00, 0x00,0x01,0x02,0x00
};

const uint8_t g_au8GetConfiguration[] =
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

void USBD_IRQHandler(void)
{
    uint32_t u32IntSts = USBD_GET_INT_FLAG();
    uint32_t u32State = USBD_GET_BUS_STATE();

//------------------------------------------------------------------
    if (u32IntSts & USBD_INTSTS_FLDET)
    {
        // Floating detect
        USBD_CLR_INT_FLAG(USBD_INTSTS_FLDET);

        if (USBD_IS_ATTACHED())
        {
            /* USB Plug In */
            USBD_ENABLE_USB();
        }
        else
        {
            /* USB Un-plug */
            USBD_DISABLE_USB();
        }
    }

//------------------------------------------------------------------
    if (u32IntSts & USBD_INTSTS_BUS)
    {
        /* Clear event flag */
        USBD_CLR_INT_FLAG(USBD_INTSTS_BUS);

        if (u32State & USBD_STATE_USBRST)
        {
            /* Bus reset */
            USBD_ENABLE_USB();
            USBD_SwReset();
            g_u8Remove = 0;
            g_u32OutToggle = g_u32OutSkip = 0;
        }
        if (u32State & USBD_STATE_SUSPEND)
        {
            /* Enable USB but disable PHY */
            USBD_DISABLE_PHY();
        }
        if (u32State & USBD_STATE_RESUME)
        {
            /* Enable USB and enable PHY */
            USBD_ENABLE_USB();
        }
    }

//------------------------------------------------------------------
    if(u32IntSts & USBD_INTSTS_WAKEUP)
    {
        /* Clear event flag */
        USBD_CLR_INT_FLAG(USBD_INTSTS_WAKEUP);
    }

    if (u32IntSts & USBD_INTSTS_USB)
    {
        // USB event
        if (u32IntSts & USBD_INTSTS_SETUP)
        {
            // Setup packet
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_SETUP);

            /* Clear the data IN/OUT ready flag of control end-points */
            USBD_STOP_TRANSACTION(EP0);
            USBD_STOP_TRANSACTION(EP1);

            USBD_ProcessSetupPacket();
        }

        // EP events
        if (u32IntSts & USBD_INTSTS_EP0)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP0);
            // control IN
            USBD_CtrlIn();
        }

        if (u32IntSts & USBD_INTSTS_EP1)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP1);

            // control OUT
            USBD_CtrlOut();
        }

        if (u32IntSts & USBD_INTSTS_EP2)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP2);
            // Bulk IN
            EP2_Handler();
        }

        if (u32IntSts & USBD_INTSTS_EP3)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP3);
            // Bulk OUT
            EP3_Handler();
        }

        if (u32IntSts & USBD_INTSTS_EP4)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP4);
        }

        if (u32IntSts & USBD_INTSTS_EP5)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP5);
        }

        if (u32IntSts & USBD_INTSTS_EP6)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP6);
        }

        if (u32IntSts & USBD_INTSTS_EP7)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP7);
        }
    }
}

void EP2_Handler(void)
{
    g_u8EP2Ready = 1;
    MSC_AckCmd();
}


void EP3_Handler(void)
{
    /* Bulk OUT */
    if (g_u32OutToggle == (USBD->EPSTS0 & USBD_EPSTS0_EPSTS3_Msk))
    {
        g_u32OutSkip = 1;
        USBD_SET_PAYLOAD_LEN(EP3, EP3_MAX_PKT_SIZE);
    }
    else
    {
        g_u8EP3Ready = 1;
        g_u32OutToggle = USBD->EPSTS0 & USBD_EPSTS0_EPSTS3_Msk;
        g_u32OutSkip = 0;
    }
}


void MSC_Init(void)
{
    /* Init setup packet buffer */
    /* Buffer range for setup packet -> [0 ~ 0x7] */
    USBD->STBUFSEG = SETUP_BUF_BASE;

    /*****************************************************/
    /* EP0 ==> control IN endpoint, address 0 */
    USBD_CONFIG_EP(EP0, USBD_CFG_CSTALL | USBD_CFG_EPMODE_IN | 0);
    /* Buffer range for EP0 */
    USBD_SET_EP_BUF_ADDR(EP0, EP0_BUF_BASE);

    /* EP1 ==> control OUT endpoint, address 0 */
    USBD_CONFIG_EP(EP1, USBD_CFG_CSTALL | USBD_CFG_EPMODE_OUT | 0);
    /* Buffer range for EP1 */
    USBD_SET_EP_BUF_ADDR(EP1, EP1_BUF_BASE);

    /*****************************************************/
    /* EP2 ==> Bulk IN endpoint, address 2 */
    USBD_CONFIG_EP(EP2, USBD_CFG_EPMODE_IN | BULK_IN_EP_NUM);
    /* Buffer range for EP2 */
    USBD_SET_EP_BUF_ADDR(EP2, EP2_BUF_BASE);

    /* EP3 ==> Bulk Out endpoint, address 3 */
    USBD_CONFIG_EP(EP3, USBD_CFG_EPMODE_OUT | BULK_OUT_EP_NUM);
    /* Buffer range for EP3 */
    USBD_SET_EP_BUF_ADDR(EP3, EP3_BUF_BASE);

    /* trigger to receive OUT data */
    USBD_SET_PAYLOAD_LEN(EP3, EP3_MAX_PKT_SIZE);

    /*****************************************************/
    g_u32BulkBuf0 = EP3_BUF_BASE;
    g_u32BulkBuf1 = EP2_BUF_BASE;

    g_sCSW.dCSWSignature = CSW_SIGNATURE;
    g_TotalSectors = DATA_FLASH_STORAGE_SIZE / CDROM_BLOCK_SIZE;
}

void MSC_ClassRequest(void)
{
    uint8_t buf[8];

    USBD_GetSetupPacket(buf);

    if (buf[0] & 0x80)   /* request data transfer direction */
    {
        // Device to host
        switch (buf[1])
        {
        case GET_MAX_LUN:
        {
            /* Check interface number with cfg descriptor and check wValue = 0, wLength = 1 */
            if ((((buf[3]<<8)+buf[2]) == 0) && (((buf[5]<<8)+buf[4]) == 0) && (((buf[7]<<8)+buf[6]) == 1))
            {
                M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = 0;
                /* Data stage */
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, 1);
                /* Status stage */
                USBD_PrepareCtrlOut(0,0);
            }
            else     /* Invalid Get MaxLun command */
            {
                USBD_SetStall(0);
            }
            break;
        }
        default:
        {
            /* Setup error, stall the device */
            USBD_SetStall(0);
            break;
        }
        }
    }
    else
    {
        // Host to device
        switch (buf[1])
        {
        case BULK_ONLY_MASS_STORAGE_RESET:
        {
            /* Check interface number with cfg descriptor and check wValue = 0, wLength = 0 */
            if ((((buf[3]<<8)+buf[2]) == 0) && (((buf[5]<<8)+buf[4]) == 0) && (((buf[7]<<8)+buf[6]) == 0))
            {
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, 0);

                USBD_LockEpStall(0);

                /* Clear ready */
                USBD->EP[EP2].CFGP |= USBD_CFGP_CLRRDY_Msk;
                USBD->EP[EP3].CFGP |= USBD_CFGP_CLRRDY_Msk;

                /* Prepare to receive the CBW */
                g_u8EP3Ready = 0;
                g_u8BulkState = BULK_CBW;

                USBD_SET_DATA1(EP3);
                USBD_SET_EP_BUF_ADDR(EP3, g_u32BulkBuf0);
                USBD_SET_PAYLOAD_LEN(EP3, EP3_MAX_PKT_SIZE);
            }
            else     /* Invalid Reset command */
            {
                USBD_SetStall(0);
            }
            break;
        }
        default:
        {
            // Stall
            /* Setup error, stall the device */
            USBD_SetStall(0);
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
            g_u8BulkState = BULK_IN;
            USBD_MemCopy((uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP2)), g_au8ReadTOC_MSF0, u32Len);
            USBD_SET_PAYLOAD_LEN(EP2, u32Len);
            break;
        }
        case 0x02:
        {
            u32Len = g_sCBW.dCBWDataTransferLength;
            if (u32Len > sizeof(g_au8ReadTOC_MSF2))
                u32Len = sizeof(g_au8ReadTOC_MSF2);
            g_u8BulkState = BULK_IN;
            USBD_MemCopy((uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP2)), g_au8ReadTOC_MSF2, u32Len);
            USBD_SET_PAYLOAD_LEN(EP2, u32Len);
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
            g_u8BulkState = BULK_IN;
            USBD_MemCopy((uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP2)), g_au8ReadTOC_LBA1, u32Len);
            USBD_SET_PAYLOAD_LEN(EP2, u32Len);
            break;
        }
        case 0x00:
        {
            u32Len = g_sCBW.dCBWDataTransferLength;
            if (u32Len > sizeof(g_au8ReadTOC_LBA0))
                u32Len = sizeof(g_au8ReadTOC_LBA0);
            g_u8BulkState = BULK_IN;
            USBD_MemCopy((uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP2)), g_au8ReadTOC_LBA0, u32Len);
            USBD_SET_PAYLOAD_LEN(EP2, u32Len);
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

        USBD_SET_EP_STALL(EP2);
        g_u8Prevent = 1;
        g_sCSW.bCSWStatus = 0x01;
        g_sCSW.dCSWDataResidue = 0;
        g_u8BulkState = BULK_IN;
        MSC_AckCmd();
        return;
    }
}

void MSC_GetConfiguration(uint32_t len, uint8_t *buff)
{
    uint32_t u32index, u32feature_len;
    uint8_t  *ptr;

    if (g_u8Remove)
    {
        memset((int8_t *)buff, 0, len);
        return;
    }

    if (g_sCBW.u8LUN == 0x02)
    {
        memcpy( buff, g_au8GetConfiguration, 8);
        u32feature_len = 0;
        // the first feature on the array
        u32index = 8;

        // find the specified feature
        while ( u32index < sizeof(g_au8GetConfiguration) )
        {
            if ((g_au8GetConfiguration[u32index] == g_sCBW.au8Data[0]) && (g_au8GetConfiguration[u32index + 1] == g_sCBW.au8Data[1]))
            {
                // copy the feature
                u32feature_len = g_au8GetConfiguration[u32index + 3] + 4;
                memcpy(buff + 8, &g_au8GetConfiguration[u32index], u32feature_len);
                break;
            }
            else
            {
                u32index += (g_au8GetConfiguration[u32index + 3] + 4);
            }
        }
        // fix up return length
        len = 8 + u32feature_len;
        buff[3] = len - 4;
    }
    else if (g_sCBW.u8LUN == 0x01)
    {
        memcpy(buff, g_au8GetConfiguration, 8);
        ptr = buff + 8;

        // the first feature on the array
        u32index = 8;

        // find current features
        while ( u32index < sizeof(g_au8GetConfiguration))
        {
            u32feature_len = g_au8GetConfiguration[u32index + 3] + 4;
            if (g_au8GetConfiguration[u32index + 2] & 0x01)    // check current bit
            {
                memcpy( ptr, &g_au8GetConfiguration[u32index], u32feature_len);
                ptr += u32feature_len;
            }
            u32index += u32feature_len;
        }
        len = ptr - buff;
        buff[3] = len - 4;
    }
    else if (g_sCBW.u8LUN == 0x00)
        memcpy((char *)buff, &g_au8GetConfiguration[0], sizeof(g_au8GetConfiguration));
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
    if (u32Len > 8)
        u32Len = 8;

    g_u8BulkState = BULK_IN;
    USBD_MemCopy((uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP2)), g_au8GetEventStatusNotification_01, u32Len);
    /* Trigger to send out the data packet */
    USBD_SET_PAYLOAD_LEN(EP2, u32Len);
}

void MSC_RequestSense(void)
{
    uint8_t tmp[20];

    memset(tmp, 0, 18);
    if (g_u8Prevent)
    {
        g_u8Prevent = 0;
        tmp[0]= 0x70;
    }
    else
        tmp[0] = 0xf0;

    tmp[2] = g_au8SenseKey[0];
    tmp[7] = 0x0a;
    tmp[12] = g_au8SenseKey[1];
    tmp[13] = g_au8SenseKey[2];
    USBD_MemCopy((uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP2)), tmp, 20);

    g_au8SenseKey[0] = 0;
    g_au8SenseKey[1] = 0;
    g_au8SenseKey[2] = 0;
}

void MSC_ReadFormatCapacity(void)
{
    memset((uint8_t *)MassCMD_BUF, 0, 12);

    *((uint8_t *)(MassCMD_BUF+0)) = 0x00;
    *((uint8_t *)(MassCMD_BUF+1)) = 0x00;
    *((uint8_t *)(MassCMD_BUF+2)) = 0x00;
    *((uint8_t *)(MassCMD_BUF+3)) = 0x08;                      /* Capacity List Length */

    /* Block Count */
    *((uint8_t *)(MassCMD_BUF+4)) = (g_TotalSectors >> 24) & 0xFF;
    *((uint8_t *)(MassCMD_BUF+5)) = (g_TotalSectors >> 16) & 0xFF;
    *((uint8_t *)(MassCMD_BUF+6)) = (g_TotalSectors >>  8) & 0xFF;
    *((uint8_t *)(MassCMD_BUF+7)) = (g_TotalSectors >>  0) & 0xFF;

    /* Block Length */
    *((uint8_t *)(MassCMD_BUF+8)) = 0x02;                      /* Descriptor Code: Formatted Media */
    *((uint8_t *)(MassCMD_BUF+9)) =  (CDROM_BLOCK_SIZE >> 16) & 0xFF;
    *((uint8_t *)(MassCMD_BUF+10)) = (CDROM_BLOCK_SIZE >>  8) & 0xFF;
    *((uint8_t *)(MassCMD_BUF+11)) = (CDROM_BLOCK_SIZE >>  0) & 0xFF;
}

void MSC_Read(void)
{
    uint32_t u32Len;

    if (USBD_GET_EP_BUF_ADDR(EP2) == g_u32BulkBuf1)
        USBD_SET_EP_BUF_ADDR(EP2, g_u32BulkBuf0);
    else
        USBD_SET_EP_BUF_ADDR(EP2, g_u32BulkBuf1);

    /* Trigger to send out the data packet */
    USBD_SET_PAYLOAD_LEN(EP2, g_u8Size);

    g_u32Length -= g_u8Size;
    g_u32BytesInStorageBuf -= g_u8Size;

    if (g_u32Length)
    {
        if (g_u32BytesInStorageBuf)
        {
            /* Prepare next data packet */
            g_u8Size = EP2_MAX_PKT_SIZE;
            if (g_u8Size > g_u32Length)
                g_u8Size = g_u32Length;

            if (USBD_GET_EP_BUF_ADDR(EP2) == g_u32BulkBuf1)
                USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf0), (uint8_t *)g_u32Address, g_u8Size);
            else
                USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf1), (uint8_t *)g_u32Address, g_u8Size);
            g_u32Address += g_u8Size;
        }
        else
        {
            u32Len = g_u32Length;
            if (u32Len > STORAGE_BUFFER_SIZE)
                u32Len = STORAGE_BUFFER_SIZE;

            MSC_ReadMedia(g_u32LbaAddress, u32Len, (uint8_t *)STORAGE_DATA_BUF);
            g_u32BytesInStorageBuf = u32Len;
            g_u32LbaAddress += u32Len;
            g_u32Address = STORAGE_DATA_BUF;

            /* Prepare next data packet */
            g_u8Size = EP2_MAX_PKT_SIZE;
            if (g_u8Size > g_u32Length)
                g_u8Size = g_u32Length;

            if (USBD_GET_EP_BUF_ADDR(EP2) == g_u32BulkBuf1)
                USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf0), (uint8_t *)g_u32Address, g_u8Size);
            else
                USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf1), (uint8_t *)g_u32Address, g_u8Size);
            g_u32Address += g_u8Size;
        }
    }
}

void MSC_ReadTrig(void)
{
    uint32_t u32Len;

    if (g_u32Length)
    {
        if (g_u32BytesInStorageBuf)
        {
            /* Prepare next data packet */
            g_u8Size = EP2_MAX_PKT_SIZE;
            if (g_u8Size > g_u32Length)
                g_u8Size = g_u32Length;

            if (USBD_GET_EP_BUF_ADDR(EP2) == g_u32BulkBuf1)
                USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf0), (uint8_t *)g_u32Address, g_u8Size);
            else
                USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf1), (uint8_t *)g_u32Address, g_u8Size);
            g_u32Address += g_u8Size;
        }
        else
        {
            u32Len = g_u32Length;
            if (u32Len > STORAGE_BUFFER_SIZE)
                u32Len = STORAGE_BUFFER_SIZE;

            MSC_ReadMedia(g_u32LbaAddress, u32Len, (uint8_t *)STORAGE_DATA_BUF);
            g_u32BytesInStorageBuf = u32Len;
            g_u32LbaAddress += u32Len;
            g_u32Address = STORAGE_DATA_BUF;

            /* Prepare next data packet */
            g_u8Size = EP2_MAX_PKT_SIZE;
            if (g_u8Size > g_u32Length)
                g_u8Size = g_u32Length;

            if (USBD_GET_EP_BUF_ADDR(EP2) == g_u32BulkBuf1)
                USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf0), (uint8_t *)g_u32Address, g_u8Size);
            else
                USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf1), (uint8_t *)g_u32Address, g_u8Size);
            g_u32Address += g_u8Size;
        }

        /* DATA0/DATA1 Toggle */
        if (USBD_GET_EP_BUF_ADDR(EP2) == g_u32BulkBuf1)
            USBD_SET_EP_BUF_ADDR(EP2, g_u32BulkBuf0);
        else
            USBD_SET_EP_BUF_ADDR(EP2, g_u32BulkBuf1);

        /* Trigger to send out the data packet */
        USBD_SET_PAYLOAD_LEN(EP2, g_u8Size);

        g_u32Length -= g_u8Size;
        g_u32BytesInStorageBuf -= g_u8Size;
    }
    else
        USBD_SET_PAYLOAD_LEN(EP2, 0);
}


void MSC_ReadCapacity(void)
{
    uint32_t tmp;

    memset((uint8_t *)MassCMD_BUF, 0, 8);

    tmp = g_TotalSectors - 1;

    /* Last Logical Block */
    *((uint8_t *)(MassCMD_BUF+0)) = (tmp >> 24) & 0xFF;
    *((uint8_t *)(MassCMD_BUF+1)) = (tmp >> 16) & 0xFF;
    *((uint8_t *)(MassCMD_BUF+2)) = (tmp >>  8) & 0xFF;
    *((uint8_t *)(MassCMD_BUF+3)) = (tmp >>  0) & 0xFF;

    /* Block Length */
    *((uint8_t *)(MassCMD_BUF+4)) = (CDROM_BLOCK_SIZE >> 24) & 0xFF;
    *((uint8_t *)(MassCMD_BUF+5)) = (CDROM_BLOCK_SIZE >> 16) & 0xFF;
    *((uint8_t *)(MassCMD_BUF+6)) = (CDROM_BLOCK_SIZE >>  8) & 0xFF;
    *((uint8_t *)(MassCMD_BUF+7)) = (CDROM_BLOCK_SIZE >>  0) & 0xFF;
}

void MSC_ModeSense10(void)
{
    uint8_t i,j;
    uint8_t NumHead,NumSector;
    uint16_t NumCyl=0;

    /* Clear the command buffer */
    *((uint32_t *)MassCMD_BUF  ) = 0;
    *((uint32_t *)MassCMD_BUF + 1) = 0;

    switch (g_sCBW.au8Data[0])
    {
    case 0x01:
        *((uint8_t *)MassCMD_BUF) = 19;
        i = 8;
        for (j = 0; j<12; j++, i++)
            *((uint8_t *)(MassCMD_BUF+i)) = g_au8ModePage_01[j];
        break;

    case 0x05:
        *((uint8_t *)MassCMD_BUF) = 39;
        i = 8;
        for (j = 0; j<32; j++, i++)
            *((uint8_t *)(MassCMD_BUF+i)) = g_au8ModePage_05[j];

        NumHead = 2;
        NumSector = 64;
        NumCyl = g_TotalSectors / 128;

        *((uint8_t *)(MassCMD_BUF+12)) = NumHead;
        *((uint8_t *)(MassCMD_BUF+13)) = NumSector;
        *((uint8_t *)(MassCMD_BUF+16)) = (uint8_t)(NumCyl >> 8);
        *((uint8_t *)(MassCMD_BUF+17)) = (uint8_t)(NumCyl & 0x00ff);
        break;

    case 0x1B:
        *((uint8_t *)MassCMD_BUF) = 19;
        i = 8;
        for (j = 0; j<12; j++, i++)
            *((uint8_t *)(MassCMD_BUF+i)) = g_au8ModePage_1B[j];
        break;

    case 0x1C:
        *((uint8_t *)MassCMD_BUF) = 15;
        i = 8;
        for (j = 0; j<8; j++, i++)
            *((uint8_t *)(MassCMD_BUF+i)) = g_au8ModePage_1C[j];
        break;

    case 0x3F:
        *((uint8_t *)MassCMD_BUF) = 0x47;
        i = 8;
        for (j = 0; j<12; j++, i++)
            *((uint8_t *)(MassCMD_BUF+i)) = g_au8ModePage_01[j];
        for (j = 0; j<32; j++, i++)
            *((uint8_t *)(MassCMD_BUF+i)) = g_au8ModePage_05[j];
        for (j = 0; j<12; j++, i++)
            *((uint8_t *)(MassCMD_BUF+i)) = g_au8ModePage_1B[j];
        for (j = 0; j<8; j++, i++)
            *((uint8_t *)(MassCMD_BUF+i)) = g_au8ModePage_1C[j];

        NumHead = 2;
        NumSector = 64;
        NumCyl = g_TotalSectors / 128;

        *((uint8_t *)(MassCMD_BUF+24)) = NumHead;
        *((uint8_t *)(MassCMD_BUF+25)) = NumSector;
        *((uint8_t *)(MassCMD_BUF+28)) = (uint8_t)(NumCyl >> 8);
        *((uint8_t *)(MassCMD_BUF+29)) = (uint8_t)(NumCyl & 0x00ff);
        break;

    default:
        g_au8SenseKey[0] = 0x05;
        g_au8SenseKey[1] = 0x24;
        g_au8SenseKey[2] = 0x00;
    }
}

#if(0)
void MSC_Write(void)
{
    uint32_t lba, len;

    if (g_u32OutSkip == 0)
    {
        if (g_u32Length > EP3_MAX_PKT_SIZE)
        {
            if (USBD_GET_EP_BUF_ADDR(EP3) == g_u32BulkBuf0)
            {
                USBD_SET_EP_BUF_ADDR(EP3, g_u32BulkBuf1);
                USBD_SET_PAYLOAD_LEN(EP3, EP3_MAX_PKT_SIZE);
                USBD_MemCopy((uint8_t *)g_u32Address, (uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf0), EP3_MAX_PKT_SIZE);
            }
            else
            {
                USBD_SET_EP_BUF_ADDR(EP3, g_u32BulkBuf0);
                USBD_SET_PAYLOAD_LEN(EP3, EP3_MAX_PKT_SIZE);
                USBD_MemCopy((uint8_t *)g_u32Address, (uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf1), EP3_MAX_PKT_SIZE);
            }

            g_u32Address += EP3_MAX_PKT_SIZE;
            g_u32Length -= EP3_MAX_PKT_SIZE;

            /* Buffer full. Writer it to storage first. */
            if (g_u32Address >= (STORAGE_DATA_BUF + STORAGE_BUFFER_SIZE))
            {
                DataFlashWrite(g_u32DataFlashStartAddr, STORAGE_BUFFER_SIZE, (uint32_t)STORAGE_DATA_BUF);

                g_u32Address = STORAGE_DATA_BUF;
                g_u32DataFlashStartAddr += STORAGE_BUFFER_SIZE;
            }
        }
        else
        {
            if (USBD_GET_EP_BUF_ADDR(EP3) == g_u32BulkBuf0)
                USBD_MemCopy((uint8_t *)g_u32Address, (uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf0), g_u32Length);
            else
                USBD_MemCopy((uint8_t *)g_u32Address, (uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf1), g_u32Length);
            g_u32Address += g_u32Length;
            g_u32Length = 0;


            if ((g_sCBW.u8OPCode == UFI_WRITE_10) || (g_sCBW.u8OPCode == UFI_WRITE_12))
            {
                lba = get_be32(&g_sCBW.au8Data[0]);
                len = g_sCBW.dCBWDataTransferLength;

                len = lba * CDROM_BLOCK_SIZE + g_sCBW.dCBWDataTransferLength - g_u32DataFlashStartAddr;
                if (len)
                    DataFlashWrite(g_u32DataFlashStartAddr, len, (uint32_t)STORAGE_DATA_BUF);
            }

            g_u8BulkState = BULK_IN;
            MSC_AckCmd();
        }
    }
}
#endif

void MSC_ProcessCmd(void)
{
    uint8_t u8Len;
    int32_t i;
    uint32_t Hcount, Dcount;

    if (g_u8EP3Ready)
    {
        g_u8EP3Ready = 0;
        if (g_u8BulkState == BULK_CBW)
        {
            u8Len = USBD_GET_PAYLOAD_LEN(EP3);

            /* Check Signature & length of CBW */
            /* Bulk Out buffer */
            if ((*(uint32_t *) ((uint32_t)USBD_BUF_BASE + g_u32BulkBuf0) != CBW_SIGNATURE) || (u8Len != 31))
            {
                /* Invalid CBW */
                g_u8Prevent = 1;
                USBD_SET_EP_STALL(EP2);
                USBD_SET_EP_STALL(EP3);
                USBD_LockEpStall((1 << EP2) | (1 << EP3));
                return;
            }

            /* Get the CBW */
            for (i = 0; i < u8Len; i++)
                *((uint8_t *) (&g_sCBW.dCBWSignature) + i) = *(uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf0 + i);

            /* Prepare to echo the tag from CBW to CSW */
            g_sCSW.dCSWTag = g_sCBW.dCBWTag;
            Hcount = g_sCBW.dCBWDataTransferLength;

            /* Parse Op-Code of CBW */
            switch (g_sCBW.u8OPCode)
            {
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
                g_u8BulkState = BULK_IN;
                MSC_AckCmd();
                return;
            }
            case UFI_TEST_UNIT_READY:
            {
                if (Hcount != 0)
                {
                    if (g_sCBW.bmCBWFlags == 0)     /* Ho > Dn (Case 9) */
                    {
                        g_u8Prevent = 1;
                        USBD_SET_EP_STALL(EP3);
                        g_sCSW.bCSWStatus = 0x1;
                        g_sCSW.dCSWDataResidue = Hcount;
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
                        g_sCSW.dCSWDataResidue = 0;
                        g_sCSW.bCSWStatus = 0;
                    }
                }
                g_u8BulkState = BULK_IN;
                MSC_AckCmd();
                return;
            }
            case UFI_START_STOP:
            {
                if ((g_sCBW.au8Data[2] & 0x03) == 0x2)
                {
                    g_u8Remove = 1;
                }
                g_u8BulkState = BULK_IN;
                MSC_AckCmd();
                return;
            }
            case UFI_VERIFY_10:
            {
                g_u8BulkState = BULK_IN;
                MSC_AckCmd();
                return;
            }
            case UFI_REQUEST_SENSE:
            {
                if ((Hcount > 0) && (Hcount <= 18))
                {
                    MSC_RequestSense();
                    USBD_SET_PAYLOAD_LEN(EP2, Hcount);
                    g_u8BulkState = BULK_IN;
                    g_sCSW.bCSWStatus = 0;
                    g_sCSW.dCSWDataResidue = 0;
                    return;
                }
                else
                {
                    USBD_SET_EP_STALL(EP2);
                    g_u8Prevent = 1;
                    g_sCSW.bCSWStatus = 0x01;
                    g_sCSW.dCSWDataResidue = 0;
                    g_u8BulkState = BULK_IN;
                    MSC_AckCmd();
                    return;
                }
            }
            case UFI_READ_FORMAT_CAPACITY:
            {
                if (g_u32Length == 0)
                {
                    g_u32Length = g_sCBW.dCBWDataTransferLength;
                    g_u32Address = MassCMD_BUF;
                }
                MSC_ReadFormatCapacity();
                g_u8BulkState = BULK_IN;
                if (g_u32Length > 0)
                {
                    if (g_u32Length > EP2_MAX_PKT_SIZE)
                        g_u8Size = EP2_MAX_PKT_SIZE;
                    else
                        g_u8Size = g_u32Length;

                    /* Bulk IN buffer */
                    USBD_MemCopy((uint8_t *)(USBD_BUF_BASE + g_u32BulkBuf1), (uint8_t *)g_u32Address, g_u8Size);

                    g_u32Address += g_u8Size;
                    USBD_SET_EP_BUF_ADDR(EP2, g_u32BulkBuf0);
                    MSC_Read();
                }
                return;
            }
            case UFI_READ_CAPACITY:
            {
                g_u32Length = g_sCBW.dCBWDataTransferLength;
                g_u32Address = MassCMD_BUF;

                MSC_ReadCapacity();
                g_u8BulkState = BULK_IN;
                if (g_u32Length > 0)
                {
                    if (g_u32Length > EP2_MAX_PKT_SIZE)
                        g_u8Size = EP2_MAX_PKT_SIZE;
                    else
                        g_u8Size = g_u32Length;

                    /* Bulk IN buffer */
                    USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf1), (uint8_t *)g_u32Address, g_u8Size);

                    g_u32Address += g_u8Size;
                    USBD_SET_EP_BUF_ADDR(EP2, g_u32BulkBuf0);
                    MSC_Read();
                }
                return;
            }
#if(0)
            // commands not supported
            case UFI_MODE_SELECT_6:
            case UFI_MODE_SELECT_10:
            {
                g_u32Length = g_sCBW.dCBWDataTransferLength;
                g_u32Address = MassCMD_BUF;

                if (g_u32Length > 0)
                {
                    USBD_SET_PAYLOAD_LEN(EP3, EP3_MAX_PKT_SIZE);
                    g_u8BulkState = BULK_OUT;
                }
                return;
            }
            // commands not supported
            case UFI_MODE_SENSE_6:
            {

                *(uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf1+0) = 0x3;
                *(uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf1+1) = 0x0;
                *(uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf1+2) = 0x0;
                *(uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf1+3) = 0x0;

                USBD_SET_PAYLOAD_LEN(EP2, 4);
                g_u8BulkState = BULK_IN;
                g_sCSW.bCSWStatus = 0;
                g_sCSW.dCSWDataResidue = Hcount - 4;;
                return;
            }
#endif
            case UFI_MODE_SENSE_10:
            {
                if (g_u32Length == 0)
                {
                    g_u32Length = g_sCBW.dCBWDataTransferLength;
                    g_u32Address = MassCMD_BUF;
                }

                MSC_ModeSense10();
                g_u8BulkState = BULK_IN;
                if (g_u32Length > 0)
                {
                    if (g_u32Length > EP2_MAX_PKT_SIZE)
                        g_u8Size = EP2_MAX_PKT_SIZE;
                    else
                        g_u8Size = g_u32Length;
                    /* Bulk IN buffer */
                    USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf1), (uint8_t *)g_u32Address, g_u8Size);

                    g_u32Address += g_u8Size;

                    USBD_SET_EP_BUF_ADDR(EP2, g_u32BulkBuf0);
                    MSC_Read();
                }
                return;
            }
            case UFI_INQUIRY:
            {

                if ((Hcount > 0) && (Hcount <= 36))
                {
                    /* Bulk IN buffer */
                    USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf1), (uint8_t *)g_au8InquiryID, Hcount);
                    USBD_SET_PAYLOAD_LEN(EP2, Hcount);
                    g_u8BulkState = BULK_IN;
                    g_sCSW.bCSWStatus = 0;
                    g_sCSW.dCSWDataResidue = 0;
                    return;
                }
                else
                {
                    USBD_SET_EP_STALL(EP2);
                    g_u8Prevent = 1;
                    g_sCSW.bCSWStatus = 0x01;
                    g_sCSW.dCSWDataResidue = 0;
                    g_u8BulkState = BULK_IN;
                    MSC_AckCmd();
                    return;
                }
            }
            case UFI_READ_12:
            case UFI_READ_10:
            {
                /* Check if it is a new transfer */
                if(g_u32Length == 0)
                {

                    Dcount = (get_be32(&g_sCBW.au8Data[4])>>8) * CDROM_BLOCK_SIZE;
                    if (g_sCBW.bmCBWFlags == 0x80)      /* IN */
                    {
                        if (Hcount == Dcount)   /* Hi == Di (Case 6)*/
                        {
                        }
                        else if (Hcount < Dcount)     /* Hn < Di (Case 2) || Hi < Di (Case 7) */
                        {
                            if (Hcount)     /* Hi < Di (Case 7) */
                            {
                                g_u8Prevent = 1;
                                g_sCSW.bCSWStatus = 0x01;
                                g_sCSW.dCSWDataResidue = 0;
                            }
                            else     /* Hn < Di (Case 2) */
                            {
                                g_u8Prevent = 1;
                                g_sCSW.bCSWStatus = 0x01;
                                g_sCSW.dCSWDataResidue = 0;
                                g_u8BulkState = BULK_IN;
                                MSC_AckCmd();
                                return;
                            }
                        }
                        else if (Hcount > Dcount)     /* Hi > Dn (Case 4) || Hi > Di (Case 5) */
                        {
                            g_u8Prevent = 1;
                            g_sCSW.bCSWStatus = 0x01;
                            g_sCSW.dCSWDataResidue = 0;
                        }
                    }
                    else     /* Ho <> Di (Case 10) */
                    {
                        g_u8Prevent = 1;
                        USBD_SET_EP_STALL(EP3);
                        g_sCSW.bCSWStatus = 0x01;
                        g_sCSW.dCSWDataResidue = Hcount;
                        g_u8BulkState = BULK_IN;
                        MSC_AckCmd();
                        return;
                    }
                }

                /* Get LBA address */
                g_u32Address = get_be32(&g_sCBW.au8Data[0]);
                g_u32LbaAddress = g_u32Address * CDROM_BLOCK_SIZE;
                g_u32Length = g_sCBW.dCBWDataTransferLength;
                g_u32BytesInStorageBuf = g_u32Length;

                i = g_u32Length;
                if (g_u32LbaAddress >= (16 * CDROM_BLOCK_SIZE))
                {
                    if (i > MSC_ImageSize)
                        i = MSC_ImageSize;
                    g_u32Address = (uint32_t)(&eprom[g_u32LbaAddress - 32768]);
                    g_u32LbaAddress += i;
                }
                else
                {
                    if (i > STORAGE_BUFFER_SIZE)
                        i = STORAGE_BUFFER_SIZE;
                    memset((uint32_t*)Storage_Block, 0, i);
                    g_u32Address = STORAGE_DATA_BUF;
                }
                g_u32BytesInStorageBuf = i;

                /* Indicate the next packet should be Bulk IN Data packet */
                g_u8BulkState = BULK_IN;
                if (g_u32BytesInStorageBuf > 0)
                {
                    /* Set the packet size */
                    if (g_u32BytesInStorageBuf > EP2_MAX_PKT_SIZE)
                        g_u8Size = EP2_MAX_PKT_SIZE;
                    else
                        g_u8Size = g_u32BytesInStorageBuf;

                    /* Prepare the first data packet (DATA1) */
                    /* Bulk IN buffer */
                    USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf1), (uint8_t *)g_u32Address, g_u8Size);
                    g_u32Address += g_u8Size;

                    /* kick - start */
                    USBD_SET_EP_BUF_ADDR(EP2, g_u32BulkBuf1);
                    /* Trigger to send out the data packet */
                    USBD_SET_PAYLOAD_LEN(EP2, g_u8Size);
                    g_u32Length -= g_u8Size;
                    g_u32BytesInStorageBuf -= g_u8Size;
                }
                return;
            }

            case UFI_WRITE_12:
            case UFI_WRITE_10:
            {
                if (g_u32Length == 0)
                {
                    Dcount = (get_be32(&g_sCBW.au8Data[4])>>8) * 512;
                    if (g_sCBW.bmCBWFlags == 0x00)      /* OUT */
                    {
                        if (Hcount == Dcount)   /* Ho == Do (Case 12)*/
                        {
                            g_sCSW.dCSWDataResidue = 0;
                            g_sCSW.bCSWStatus = 0;
                        }
                        else if (Hcount < Dcount)     /* Hn < Do (Case 3) || Ho < Do (Case 13) */
                        {
                            g_u8Prevent = 1;
                            g_sCSW.dCSWDataResidue = 0;
                            g_sCSW.bCSWStatus = 0x1;
                            if (Hcount == 0)    /* Hn < Do (Case 3) */
                            {
                                g_u8BulkState = BULK_IN;
                                MSC_AckCmd();
                                return;
                            }
                        }
                        else if (Hcount > Dcount)     /* Ho > Do (Case 11) */
                        {
                            g_u8Prevent = 1;
                            g_sCSW.dCSWDataResidue = 0;
                            g_sCSW.bCSWStatus = 0x1;
                        }
                        g_u32Length = g_sCBW.dCBWDataTransferLength;
                        g_u32Address = STORAGE_DATA_BUF;
                        g_u32DataFlashStartAddr = get_be32(&g_sCBW.au8Data[0]) * CDROM_BLOCK_SIZE;
                    }
                    else     /* Hi <> Do (Case 8) */
                    {
                        g_u8Prevent = 1;
                        g_sCSW.dCSWDataResidue = Hcount;
                        g_sCSW.bCSWStatus = 0x1;
                        USBD_SET_EP_STALL(EP2);
                        g_u8BulkState = BULK_IN;
                        MSC_AckCmd();
                        return;
                    }
                }
#if(0)
                if ((g_u32Length > 0))
                {
                    USBD_SET_PAYLOAD_LEN(EP3, EP3_MAX_PKT_SIZE);
                    g_u8BulkState = BULK_OUT;
                }
#else
                USBD_SET_EP_STALL(EP3);
                g_u8Prevent = 1;
                g_sCSW.bCSWStatus = 0x01;
                g_sCSW.dCSWDataResidue = 0;
                g_u8BulkState = BULK_IN;
                MSC_AckCmd();
#endif
                return;
            }
            case UFI_READ_16:
            {
                USBD_SET_EP_STALL(EP2);
                g_u8Prevent = 1;
                g_sCSW.bCSWStatus = 0x01;
                g_sCSW.dCSWDataResidue = 0;
                g_u8BulkState = BULK_IN;
                MSC_AckCmd();
                return;
            }
            case UFI_READ_TOC:
            {
                MSC_ReadTOC();
                return;
            }
            case UFI_GET_CONFIGURATION:
            {
                if (g_u32Length == 0)
                {
                    // LBA
                    g_u32Address = get_be32(&g_sCBW.au8Data[0]);
                    g_u32Length = g_sCBW.dCBWDataTransferLength;
                    MSC_GetConfiguration(g_u32Length, (uint8_t *)MassBlock);
                }
                g_u32Address = (uint32_t)MassBlock;
                g_u8BulkState = BULK_IN;
                if (g_u32Length > 0)
                {
                    if (g_u32Length > EP2_MAX_PKT_SIZE)
                        g_u8Size = EP2_MAX_PKT_SIZE;
                    else
                        g_u8Size = g_u32Length;

                    USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf1), (uint8_t *)g_u32Address, g_u8Size);

                    USBD_SET_EP_BUF_ADDR(EP2, g_u32BulkBuf0);
                    /* Trigger to send out the data packet */
                    USBD_SET_PAYLOAD_LEN(EP2, g_u8Size);

                    g_u32Address += g_u8Size;
                    g_u32Length -= g_u8Size;

                    g_u32BytesInStorageBuf -= g_u8Size;
                }
                else
                    MSC_AckCmd();
                return;
            }
            case UFI_SET_CDROM_SPEED:
            {
                g_u8BulkState = BULK_IN;
                MSC_AckCmd();
                return;
            }
            case UFI_GET_EVENT_STATUS_NOTIFICATION:
            {
                MSC_GetEventStatusNotification();
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
                    /* Data Phase, zero/short packet */
                    if ((g_sCBW.bmCBWFlags & 0x80) != 0)
                    {
                        /* Data-In */
                        g_u8BulkState = BULK_IN;
                        USBD_SET_PAYLOAD_LEN(EP2, 0);
                    }
                }
                else
                {
                    /* Status Phase */
                    g_u8BulkState = BULK_IN;
                    MSC_AckCmd();
                }
                return;
            }
            }
        }
#if(0)
        else if (g_u8BulkState == BULK_OUT)
        {
            switch (g_sCBW.u8OPCode)
            {
            case UFI_WRITE_12:
            case UFI_WRITE_10:
            case UFI_MODE_SELECT_6:
            case UFI_MODE_SELECT_10:
            {
                MSC_Write();
                return;
            }
            }
        }
#endif
    }
}

void MSC_AckCmd(void)
{
    /* Bulk IN */
    if (g_u8BulkState == BULK_CSW)
    {
        /* Prepare to receive the CBW */
        g_u8BulkState = BULK_CBW;

        USBD_SET_EP_BUF_ADDR(EP3, g_u32BulkBuf0);
        USBD_SET_PAYLOAD_LEN(EP3, 31);
    }
    else if (g_u8BulkState == BULK_IN)
    {
        switch (g_sCBW.u8OPCode)
        {
        case UFI_READ_12:
        case UFI_READ_10:
        {
            if (g_u32Length > 0)
            {
                MSC_ReadTrig();
                return;
            }
            break;
        }
        case UFI_READ_FORMAT_CAPACITY:
        case UFI_READ_CAPACITY:
        case UFI_MODE_SENSE_10:
        case UFI_GET_CONFIGURATION:
        case UFI_READ_CD:
        {
            if (g_u32Length > 0)
            {
                MSC_Read();
                return;
            }
            g_sCSW.dCSWDataResidue = 0;
            g_sCSW.bCSWStatus = 0;
            break;
        }

        case UFI_WRITE_12:
        case UFI_WRITE_10:
            break;
        case UFI_PREVENT_ALLOW_MEDIUM_REMOVAL:
        case UFI_VERIFY_10:
        case UFI_START_STOP:
        case UFI_GET_EVENT_STATUS_NOTIFICATION:
        case UFI_SET_CDROM_SPEED:
        {
            int32_t tmp;

            tmp = g_sCBW.dCBWDataTransferLength - STORAGE_BUFFER_SIZE;
            if (tmp < 0)
                tmp = 0;

            g_sCSW.dCSWDataResidue = tmp;
            g_sCSW.bCSWStatus = 0;
            break;
        }
        case UFI_INQUIRY:
        case UFI_MODE_SENSE_6:
        case UFI_REQUEST_SENSE:
        case UFI_TEST_UNIT_READY:
        {
            break;
        }
        case UFI_READ_TOC:
        {
            g_sCSW.dCSWDataResidue = 0;
            g_sCSW.bCSWStatus = 0;
            break;
        }
        default:
        {
            /* Unsupported command. Return command fail status */
            g_sCSW.dCSWDataResidue = g_sCBW.dCBWDataTransferLength;
            g_sCSW.bCSWStatus = 0x01;
            break;
        }
        }

        /* Return the CSW */
        USBD_SET_EP_BUF_ADDR(EP2, g_u32BulkBuf1);

        /* Bulk IN buffer */
        USBD_MemCopy((uint8_t *)(USBD_BUF_BASE + g_u32BulkBuf1), (uint8_t *)&g_sCSW.dCSWSignature, 16);

        g_u8BulkState = BULK_CSW;
        USBD_SET_PAYLOAD_LEN(EP2, 13);
    }
}

void MSC_ReadMedia(uint32_t addr, uint32_t size, uint8_t *buffer)
{
}

void MSC_WriteMedia(uint32_t addr, uint32_t size, uint8_t *buffer)
{
}



