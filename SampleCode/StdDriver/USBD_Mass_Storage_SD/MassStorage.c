/***************************************************************************//**
 * @file     MassStorage.c
 * @brief    M480 series USBD driver Sample file
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

/*!<Includes */
#include <string.h>
#include "NuMicro.h"
#include "massstorage.h"

#if 0
#define DBG_PRINTF      printf
#else
#define DBG_PRINTF(...)
#endif
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
extern uint8_t volatile g_u8SdInitFlag;

/*--------------------------------------------------------------------------*/
uint8_t g_au8InquiryID[36] =
{
    0x00,                   /* Peripheral Device Type */
    0x80,                   /* RMB */
    0x00,                   /* ISO/ECMA, ANSI Version */
    0x00,                   /* Response Data Format */
    0x1F, 0x00, 0x00, 0x00, /* Additional Length */

    /* Vendor Identification */
    'N', 'u', 'v', 'o', 't', 'o', 'n', ' ',

    /* Product Identification */
    'U', 'S', 'B', ' ', 'M', 'a', 's', 's', ' ', 'S', 't', 'o', 'r', 'a', 'g', 'e',

    /* Product Revision */
    '1', '.', '0', '0'
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


void USBD_IRQHandler(void)
{
    uint32_t u32IntSts = USBD_GET_INT_FLAG();
    uint32_t u32State = USBD_GET_BUS_STATE();


//------------------------------------------------------------------
    if(u32IntSts & USBD_INTSTS_FLDET)
    {
        // Floating detect
        USBD_CLR_INT_FLAG(USBD_INTSTS_FLDET);

        if(USBD_IS_ATTACHED())
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
    if(u32IntSts & USBD_INTSTS_BUS)
    {
        /* Clear event flag */
        USBD_CLR_INT_FLAG(USBD_INTSTS_BUS);

        if(u32State & USBD_STATE_USBRST)
        {
            /* Bus reset */
            USBD_ENABLE_USB();
            USBD_SwReset();
            DBG_PRINTF("Bus reset\n");
            g_u32OutToggle = g_u32OutSkip = 0;
        }
        if(u32State & USBD_STATE_SUSPEND)
        {
            /* Enable USB but disable PHY */
            USBD_DISABLE_PHY();
            DBG_PRINTF("Suspend\n");
        }
        if(u32State & USBD_STATE_RESUME)
        {
            /* Enable USB and enable PHY */
            USBD_ENABLE_USB();
            DBG_PRINTF("Resume\n");
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
        if(u32IntSts & USBD_INTSTS_EP0)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP0);
            // control IN
            USBD_CtrlIn();
        }

        if(u32IntSts & USBD_INTSTS_EP1)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP1);

            // control OUT
            USBD_CtrlOut();
        }

        if(u32IntSts & USBD_INTSTS_EP2)
        {
            while (USBD_GET_INT_FLAG() & USBD_INTSTS_EP2) {
                /* Clear event flag */
                USBD_CLR_INT_FLAG(USBD_INTSTS_EP2);
            }
            // Bulk IN
            EP2_Handler();
        }

        if(u32IntSts & USBD_INTSTS_EP3)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP3);
            // Bulk OUT
            EP3_Handler();
        }

        if(u32IntSts & USBD_INTSTS_EP4)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP4);
        }

        if(u32IntSts & USBD_INTSTS_EP5)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP5);
        }

        if(u32IntSts & USBD_INTSTS_EP6)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP6);
        }

        if(u32IntSts & USBD_INTSTS_EP7)
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
    if (g_u8SdInitFlag)
    {
        g_TotalSectors = SD0.totalSectorN;
        g_au8SenseKey[0] = 0x0;
        g_au8SenseKey[1] = 0x0;
        g_au8SenseKey[2] = 0x0;
    }
    else
    {
        g_TotalSectors = 0;
        g_au8SenseKey[0] = 0x03;
        g_au8SenseKey[1] = 0x30;
        g_au8SenseKey[2] = 0x01;
    }
    printf("totoal sectors %d\n", SD0.totalSectorN);
}

void MSC_ClassRequest(void)
{
    uint8_t buf[8];

    USBD_GetSetupPacket(buf);

    if(buf[0] & EP_INPUT)    /* request data transfer direction */
    {
        // Device to host
        switch(buf[1])
        {
        case GET_MAX_LUN:
        {
            /* Check interface number with cfg descriptor and check wValue = 0, wLength = 1 */
            if((buf[4] == gsInfo.gu8ConfigDesc[LEN_CONFIG + 2]) && (buf[2] + buf[3] + buf[6] + buf[7] == 1))
            {
                M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = 0;
                /* Data stage */
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, 1);
                /* Status stage */
                USBD_PrepareCtrlOut(0, 0);
            }
            else
                USBD_SET_EP_STALL(EP1); // Stall when wrong parameter

            break;
        }
        default:
        {
            /* Setup error, stall the device */
            USBD_SetStall(0);
            DBG_PRINTF("Unknow MSC req(0x%x). stall ctrl pipe\n", buf[1]);
            break;
        }
        }
    }
    else
    {
        // Host to device
        switch(buf[1])
        {
        case BULK_ONLY_MASS_STORAGE_RESET:
        {
            /* Check interface number with cfg descriptor and check wValue = 0, wLength = 0 */
            if((buf[4] == gsInfo.gu8ConfigDesc[LEN_CONFIG + 2]) && (buf[2] + buf[3] + buf[6] + buf[7] == 0))
            {

                g_u32Length = 0; // Reset all read/write data transfer
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
            else
            {
                /* Stall when wrong parameter */
                USBD_SET_EP_STALL(EP1);
            }

            /* Status stage */
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 0);

            break;
        }
        default:
        {
            // Stall
            /* Setup error, stall the device */
            USBD_SetStall(0);
            DBG_PRINTF("Unknown MSC req (0x%x). stall ctrl pipe\n", buf[1]);
            break;
        }
        }
    }
}


void MSC_RequestSense(void)
{
    uint8_t tmp[20];

    memset(tmp, 0, 18);
    if(g_u8Prevent)
    {
        g_u8Prevent = 0;
        tmp[0] = 0x70;
    }
    else
        tmp[0] = 0xf0;

    if (SD0.IsCardInsert)
    {
        g_au8SenseKey[0] = 0x0;
        g_au8SenseKey[1] = 0x0;
        g_au8SenseKey[2] = 0x0;
    }
    else
    {
        g_au8SenseKey[0] = 0x02;
        g_au8SenseKey[1] = 0x3a;
        g_au8SenseKey[2] = 0x00;
    }
    tmp[2] = g_au8SenseKey[0];
    tmp[7] = 0x0a;
    tmp[12] = g_au8SenseKey[1];
    tmp[13] = g_au8SenseKey[2];
    USBD_MemCopy((uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP2)), tmp, 20);
}

void MSC_ReadFormatCapacity(void)
{
    uint8_t *pu8Desc;

    pu8Desc = (uint8_t *)MassCMD_BUF;
    memset(pu8Desc, 0, 36);

    /*---------- Capacity List Header ----------*/
    // Capacity List Length
    pu8Desc[3] = 0x10;

    /*---------- Current/Maximum Capacity Descriptor ----------*/
    // Number of blocks (MSB first)
    pu8Desc[4] = *((uint8_t *)&g_TotalSectors+3);
    pu8Desc[5] = *((uint8_t *)&g_TotalSectors+2);
    pu8Desc[6] = *((uint8_t *)&g_TotalSectors+1);
    pu8Desc[7] = *((uint8_t *)&g_TotalSectors+0);

    // Descriptor Code:
    // 01b = Unformatted Media - Maximum formattable capacity for this cartridge
    // 10b = Formatted Media - Current media capacity
    // 11b = No Cartridge in Drive - Maximum formattable capacity for any cartridge
    pu8Desc[8] = 0x02;


    // Block Length. Fixed to be 512 (MSB first)
    pu8Desc[ 9] = 0;
    pu8Desc[10] = 0x02;
    pu8Desc[11] = 0;

    /*---------- Formattable Capacity Descriptor ----------*/
    // Number of Blocks
    pu8Desc[12] = *((uint8_t *)&g_TotalSectors+3);
    pu8Desc[13] = *((uint8_t *)&g_TotalSectors+2);
    pu8Desc[14] = *((uint8_t *)&g_TotalSectors+1);
    pu8Desc[15] = *((uint8_t *)&g_TotalSectors+0);

    // Block Length. Fixed to be 512 (MSB first)
    pu8Desc[17] = 0;
    pu8Desc[18] = 0x02;
    pu8Desc[19] = 0;

}

void MSC_Read(void)
{
    uint32_t u32Len;

    if(USBD_GET_EP_BUF_ADDR(EP2) == g_u32BulkBuf1)
        USBD_SET_EP_BUF_ADDR(EP2, g_u32BulkBuf0);
    else
        USBD_SET_EP_BUF_ADDR(EP2, g_u32BulkBuf1);

    /* Trigger to send out the data packet */
    USBD_SET_PAYLOAD_LEN(EP2, g_u8Size);

    g_u32Length -= g_u8Size;
    g_u32BytesInStorageBuf -= g_u8Size;

    if(g_u32Length)
    {
        if(g_u32BytesInStorageBuf)
        {
            /* Prepare next data packet */
            g_u8Size = EP2_MAX_PKT_SIZE;
            if(g_u8Size > g_u32Length)
                g_u8Size = g_u32Length;

            if(USBD_GET_EP_BUF_ADDR(EP2) == g_u32BulkBuf1)
                USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf0), (uint8_t *)g_u32Address, g_u8Size);
            else
                USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf1), (uint8_t *)g_u32Address, g_u8Size);
            g_u32Address += g_u8Size;
        }
        else
        {
            u32Len = g_u32Length;
            if(u32Len > STORAGE_BUFFER_SIZE)
                u32Len = STORAGE_BUFFER_SIZE;

            MSC_ReadMedia(g_u32LbaAddress, u32Len, (uint8_t *)STORAGE_DATA_BUF);
            g_u32BytesInStorageBuf = u32Len;
            g_u32LbaAddress += u32Len;
            g_u32Address = STORAGE_DATA_BUF;

            /* Prepare next data packet */
            g_u8Size = EP2_MAX_PKT_SIZE;
            if(g_u8Size > g_u32Length)
                g_u8Size = g_u32Length;

            if(USBD_GET_EP_BUF_ADDR(EP2) == g_u32BulkBuf1)
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

    if(g_u32Length)
    {
        if(g_u32BytesInStorageBuf)
        {
            /* Prepare next data packet */
            g_u8Size = EP2_MAX_PKT_SIZE;
            if(g_u8Size > g_u32Length)
                g_u8Size = g_u32Length;

            if(USBD_GET_EP_BUF_ADDR(EP2) == g_u32BulkBuf1)
                USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf0), (uint8_t *)g_u32Address, g_u8Size);
            else
                USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf1), (uint8_t *)g_u32Address, g_u8Size);
            g_u32Address += g_u8Size;
        }
        else
        {
            u32Len = g_u32Length;
            if(u32Len > STORAGE_BUFFER_SIZE)
                u32Len = STORAGE_BUFFER_SIZE;

            MSC_ReadMedia(g_u32LbaAddress, u32Len, (uint8_t *)STORAGE_DATA_BUF);
            g_u32BytesInStorageBuf = u32Len;
            g_u32LbaAddress += u32Len;
            g_u32Address = STORAGE_DATA_BUF;

            /* Prepare next data packet */
            g_u8Size = EP2_MAX_PKT_SIZE;
            if(g_u8Size > g_u32Length)
                g_u8Size = g_u32Length;

            if(USBD_GET_EP_BUF_ADDR(EP2) == g_u32BulkBuf1)
                USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf0), (uint8_t *)g_u32Address, g_u8Size);
            else
                USBD_MemCopy((uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf1), (uint8_t *)g_u32Address, g_u8Size);
            g_u32Address += g_u8Size;
        }

        /* DATA0/DATA1 Toggle */
        if(USBD_GET_EP_BUF_ADDR(EP2) == g_u32BulkBuf1)
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

    memset((uint8_t *)MassCMD_BUF, 0, 36);

    tmp = g_TotalSectors - 1;
    *((uint8_t *)(MassCMD_BUF + 0)) = *((uint8_t *)&tmp + 3);
    *((uint8_t *)(MassCMD_BUF + 1)) = *((uint8_t *)&tmp + 2);
    *((uint8_t *)(MassCMD_BUF + 2)) = *((uint8_t *)&tmp + 1);
    *((uint8_t *)(MassCMD_BUF + 3)) = *((uint8_t *)&tmp + 0);
    *((uint8_t *)(MassCMD_BUF + 6)) = 0x02;
}

void MSC_ReadCapacity16(void)
{
    uint32_t tmp;

    memset((uint8_t *)MassCMD_BUF, 0, 36);

    tmp = g_TotalSectors - 1;
    *((uint8_t *)(MassCMD_BUF + 0)) = 0;
    *((uint8_t *)(MassCMD_BUF + 1)) = 0;
    *((uint8_t *)(MassCMD_BUF + 2)) = 0;
    *((uint8_t *)(MassCMD_BUF + 3)) = 0;
    *((uint8_t *)(MassCMD_BUF + 4)) = *((uint8_t *)&tmp + 3);
    *((uint8_t *)(MassCMD_BUF + 5)) = *((uint8_t *)&tmp + 2);
    *((uint8_t *)(MassCMD_BUF + 6)) = *((uint8_t *)&tmp + 1);
    *((uint8_t *)(MassCMD_BUF + 7)) = *((uint8_t *)&tmp + 0);
    *((uint8_t *)(MassCMD_BUF + 10)) = 0x02;
}


void MSC_ModeSense10(void)
{
    uint8_t i, j;
    uint8_t NumHead, NumSector;
    uint16_t NumCyl = 0;

    /* Clear the command buffer */
    *((uint32_t *)MassCMD_BUF) = 0;
    *((uint32_t *)MassCMD_BUF + 1) = 0;

    switch(g_sCBW.au8Data[0])
    {
    case 0x01:
        *((uint8_t *)MassCMD_BUF) = 19;
        i = 8;
        for(j = 0; j < 12; j++, i++)
            *((uint8_t *)(MassCMD_BUF + i)) = g_au8ModePage_01[j];
        break;

    case 0x05:
        *((uint8_t *)MassCMD_BUF) = 39;
        i = 8;
        for(j = 0; j < 32; j++, i++)
            *((uint8_t *)(MassCMD_BUF + i)) = g_au8ModePage_05[j];

        NumHead = 2;
        NumSector = 64;
        NumCyl = g_TotalSectors / 128;

        *((uint8_t *)(MassCMD_BUF + 12)) = NumHead;
        *((uint8_t *)(MassCMD_BUF + 13)) = NumSector;
        *((uint8_t *)(MassCMD_BUF + 16)) = (uint8_t)(NumCyl >> 8);
        *((uint8_t *)(MassCMD_BUF + 17)) = (uint8_t)(NumCyl & 0x00ff);
        break;

    case 0x1B:
        *((uint8_t *)MassCMD_BUF) = 19;
        i = 8;
        for(j = 0; j < 12; j++, i++)
            *((uint8_t *)(MassCMD_BUF + i)) = g_au8ModePage_1B[j];
        break;

    case 0x1C:
        *((uint8_t *)MassCMD_BUF) = 15;
        i = 8;
        for(j = 0; j < 8; j++, i++)
            *((uint8_t *)(MassCMD_BUF + i)) = g_au8ModePage_1C[j];
        break;

    case 0x3F:
        *((uint8_t *)MassCMD_BUF) = 0x47;
        i = 8;
        for(j = 0; j < 12; j++, i++)
            *((uint8_t *)(MassCMD_BUF + i)) = g_au8ModePage_01[j];
        for(j = 0; j < 32; j++, i++)
            *((uint8_t *)(MassCMD_BUF + i)) = g_au8ModePage_05[j];
        for(j = 0; j < 12; j++, i++)
            *((uint8_t *)(MassCMD_BUF + i)) = g_au8ModePage_1B[j];
        for(j = 0; j < 8; j++, i++)
            *((uint8_t *)(MassCMD_BUF + i)) = g_au8ModePage_1C[j];

        NumHead = 2;
        NumSector = 64;
        NumCyl = g_TotalSectors / 128;

        *((uint8_t *)(MassCMD_BUF + 24)) = NumHead;
        *((uint8_t *)(MassCMD_BUF + 25)) = NumSector;
        *((uint8_t *)(MassCMD_BUF + 28)) = (uint8_t)(NumCyl >> 8);
        *((uint8_t *)(MassCMD_BUF + 29)) = (uint8_t)(NumCyl & 0x00ff);
        break;

    default:
        g_au8SenseKey[0] = 0x05;
        g_au8SenseKey[1] = 0x24;
        g_au8SenseKey[2] = 0x00;
    }
}

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
                MSC_WriteMedia(g_u32DataFlashStartAddr, STORAGE_BUFFER_SIZE, (uint8_t *)STORAGE_DATA_BUF);

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

                len = lba * UDC_SECTOR_SIZE + g_sCBW.dCBWDataTransferLength - g_u32DataFlashStartAddr;
                if (len)
                    MSC_WriteMedia(g_u32DataFlashStartAddr, len, (uint8_t *)STORAGE_DATA_BUF);
            }

            g_u8BulkState = BULK_IN;
            MSC_AckCmd();
        }
    }
}

void MSC_ProcessCmd(void)
{
    uint8_t u8Len;
    int32_t i;
    uint32_t Hcount, Dcount;

    if(g_u8EP3Ready)
    {
        g_u8EP3Ready = 0;

        if(g_u8BulkState == BULK_CBW)
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
            for(i = 0; i < u8Len; i++)
                *((uint8_t *)(&g_sCBW.dCBWSignature) + i) = *(uint8_t *)((uint32_t)USBD_BUF_BASE + g_u32BulkBuf0 + i);


            /* Prepare to echo the tag from CBW to CSW */
            g_sCSW.dCSWTag = g_sCBW.dCBWTag;
            Hcount = g_sCBW.dCBWDataTransferLength;

            /* Parse Op-Code of CBW */
            switch(g_sCBW.u8OPCode)
            {
            case UFI_PREVENT_ALLOW_MEDIUM_REMOVAL:
            {
                if(g_sCBW.au8Data[2] & 0x01)
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
                if (g_u32Length == 0)
                {
                    g_u32Length = g_sCBW.dCBWDataTransferLength;
                    g_u32Address = MassCMD_BUF;
                }

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
            case UFI_MODE_SENSE_10:
            {
                if(g_u32Length == 0)
                {
                    g_u32Length = g_sCBW.dCBWDataTransferLength;
                    g_u32Address = MassCMD_BUF;
                }

                MSC_ModeSense10();
                g_u8BulkState = BULK_IN;
                if(g_u32Length > 0)
                {
                    if(g_u32Length > EP2_MAX_PKT_SIZE)
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

                    Dcount = (get_be32(&g_sCBW.au8Data[4])>>8) * 512;
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
                g_u32LbaAddress = g_u32Address * UDC_SECTOR_SIZE;
                g_u32Length = g_sCBW.dCBWDataTransferLength;
                g_u32BytesInStorageBuf = g_u32Length;

                i = g_u32Length;
                if (i > STORAGE_BUFFER_SIZE)
                    i = STORAGE_BUFFER_SIZE;

                MSC_ReadMedia(g_u32Address * UDC_SECTOR_SIZE, i, (uint8_t *)STORAGE_DATA_BUF);
                g_u32BytesInStorageBuf = i;
                g_u32LbaAddress += i;

                g_u32Address = STORAGE_DATA_BUF;

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
                        g_u32DataFlashStartAddr = get_be32(&g_sCBW.au8Data[0]) * UDC_SECTOR_SIZE;
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

                if ((g_u32Length > 0))
                {
                    USBD_SET_PAYLOAD_LEN(EP3, EP3_MAX_PKT_SIZE);
                    g_u8BulkState = BULK_OUT;
                }
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
        default:
        {
            /* Unsupported commmand. Return command fail status */
            g_sCSW.dCSWDataResidue = g_sCBW.dCBWDataTransferLength;
            g_sCSW.bCSWStatus = 0x01;
            break;
        }
        }

        if (SD0.IsCardInsert == 0)
        {
            if ((g_sCBW.u8OPCode == UFI_INQUIRY) || (g_sCBW.u8OPCode == UFI_REQUEST_SENSE))
                g_sCSW.bCSWStatus = 0x00;
            else
                g_sCSW.bCSWStatus = 0x01;
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
    SDH_Read(SDH0, buffer, addr/UDC_SECTOR_SIZE, size/UDC_SECTOR_SIZE);
}

void MSC_WriteMedia(uint32_t addr, uint32_t size, uint8_t *buffer)
{
    SDH_Write(SDH0, buffer, addr/UDC_SECTOR_SIZE, size/UDC_SECTOR_SIZE);
}


void MSC_SetConfig(void)
{
    // Clear stall status and ready
    USBD->EP[2].CFGP = 1;
    USBD->EP[3].CFGP = 1;
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


    USBD_LockEpStall(0);

    g_u8BulkState = BULK_CBW;


    DBG_PRINTF("Set config\n");

}
