/***************************************************************************//**
 * @file     hid_mouse.c
 * @brief    M480 series USBD driver Sample file
 * @version  2.0.0
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

/*!<Includes */
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"
#include "VCOM_And_hid_transfer.h"

uint32_t volatile g_u32OutToggle = 0;

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
            g_u32OutToggle = 0;
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
        extern uint8_t g_usbd_SetupPacket[];
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

            // In ACK of SET_LINE_CODE
            if(g_usbd_SetupPacket[1] == SET_LINE_CODE)
            {
                if(g_usbd_SetupPacket[4] == 0)  /* VCOM-1 */
                    VCOM_LineCoding(0); /* Apply UART settings */
            }
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
            // Interrupt IN
            EP5_Handler();
        }

        if (u32IntSts & USBD_INTSTS_EP6)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP6);
            // Interrupt OUT
            EP6_Handler();
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
    gu32TxSize = 0;
}

void EP3_Handler(void)
{
    /* Bulk OUT */
    if (g_u32OutToggle == (USBD->EPSTS0 & USBD_EPSTS0_EPSTS3_Msk))
    {
        USBD_SET_PAYLOAD_LEN(EP3, EP3_MAX_PKT_SIZE);
    }
    else
    {
        gu32RxSize = USBD_GET_PAYLOAD_LEN(EP3);
        gpu8RxBuf = (uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP3));

        g_u32OutToggle = USBD->EPSTS0 & USBD_EPSTS0_EPSTS3_Msk;
        /* Set a flag to indicate bulk out ready */
        gi8BulkOutReady = 1;
    }
}

void EP5_Handler(void)  /* Interrupt IN handler */
{
    HID_SetInReport();
}

void EP6_Handler(void)  /* Interrupt OUT handler */
{
    uint8_t *ptr;
    /* Interrupt OUT */
    ptr = (uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP6));
    HID_GetOutReport(ptr, USBD_GET_PAYLOAD_LEN(EP6));
    USBD_SET_PAYLOAD_LEN(EP6, EP6_MAX_PKT_SIZE);
}


/*--------------------------------------------------------------------------*/
/**
  * @brief  USBD Endpoint Config.
  * @param  None.
  * @retval None.
  */
void HID_Init(void)
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
    /* EP2 ==> Bulk IN endpoint, address 1 */
    USBD_CONFIG_EP(EP2, USBD_CFG_EPMODE_IN | BULK_IN_EP_NUM);
    /* Buffer offset for EP2 */
    USBD_SET_EP_BUF_ADDR(EP2, EP2_BUF_BASE);

    /* EP3 ==> Bulk Out endpoint, address 2 */
    USBD_CONFIG_EP(EP3, USBD_CFG_EPMODE_OUT | BULK_OUT_EP_NUM);
    /* Buffer offset for EP3 */
    USBD_SET_EP_BUF_ADDR(EP3, EP3_BUF_BASE);
    /* trigger receive OUT data */
    USBD_SET_PAYLOAD_LEN(EP3, EP3_MAX_PKT_SIZE);

    /* EP4 ==> Interrupt IN endpoint, address 3 */
    USBD_CONFIG_EP(EP4, USBD_CFG_EPMODE_IN | INT_IN_EP_NUM);
    /* Buffer offset for EP4 ->  */
    USBD_SET_EP_BUF_ADDR(EP4, EP4_BUF_BASE);

    /*****************************************************/
    /* EP5 ==> Interrupt IN endpoint, address 4 */
    USBD_CONFIG_EP(EP5, USBD_CFG_EPMODE_IN | INT_IN_EP_NUM_1);
    /* Buffer range for EP5 */
    USBD_SET_EP_BUF_ADDR(EP5, EP5_BUF_BASE);

    /* EP6 ==> Interrupt OUT endpoint, address 5 */
    USBD_CONFIG_EP(EP6, USBD_CFG_EPMODE_OUT | INT_OUT_EP_NUM_1);
    /* Buffer range for EP6 */
    USBD_SET_EP_BUF_ADDR(EP6, EP6_BUF_BASE);
    /* trigger to receive OUT data */
    USBD_SET_PAYLOAD_LEN(EP6, EP6_MAX_PKT_SIZE);

}

void HID_ClassRequest(void)
{
    uint8_t buf[8];

    USBD_GetSetupPacket(buf);

    if (buf[0] & 0x80)   /* request data transfer direction */
    {
        // Device to host
        switch (buf[1])
        {
        case GET_LINE_CODE:
        {
            if (buf[4] == 0)   /* VCOM-1 */
            {
                USBD_MemCopy((uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)), (uint8_t *)&gLineCoding, 7);
            }
            /* Data stage */
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 7);
            /* Status stage */
            USBD_PrepareCtrlOut(0,0);
            break;
        }
        case GET_REPORT:
        case GET_IDLE:
        case GET_PROTOCOL:
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
        case SET_CONTROL_LINE_STATE:
        {
            if (buf[4] == 0)   /* VCOM-1 */
            {
                gCtrlSignal = buf[3];
                gCtrlSignal = (gCtrlSignal << 8) | buf[2];
                //printf("RTS=%d  DTR=%d\n", (gCtrlSignal0 >> 1) & 1, gCtrlSignal0 & 1);
            }

            /* Status stage */
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 0);
            break;
        }
        case SET_LINE_CODE:
        {
            //g_usbd_UsbConfig = 0100;
            if (buf[4] == 0) /* VCOM-1 */
                USBD_PrepareCtrlOut((uint8_t *)&gLineCoding, 7);

            /* Status stage */
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 0);

            break;
        }
        case SET_REPORT:
        {
            if (buf[3] == 3)
            {
                /* Request Type = Feature */
                USBD_SET_DATA1(EP1);
                USBD_SET_PAYLOAD_LEN(EP1, 0);
            }
            break;
        }
        case SET_IDLE:
        {
            /* Status stage */
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 0);
            break;
        }
        case SET_PROTOCOL:
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

void VCOM_LineCoding(uint8_t port)
{
    uint32_t u32Reg, u32Baud_Div;

    if (port == 0)
    {
        NVIC_DisableIRQ(UART0_IRQn);
        // Reset software fifo
        comRbytes = 0;
        comRhead = 0;
        comRtail = 0;

        comTbytes = 0;
        comThead = 0;
        comTtail = 0;

        // Reset hardware fifo
        UART0->FIFO = 0x3;

        // Set baudrate
        u32Baud_Div = UART_BAUD_MODE0_DIVIDER(__HXT, gLineCoding.u32DTERate);

        if(u32Baud_Div > 0xFFFF)
            UART0->BAUD = (UART_BAUD_MODE0 | UART_BAUD_MODE0_DIVIDER(__HXT, gLineCoding.u32DTERate));
        else
            UART0->BAUD = (UART_BAUD_MODE2 | u32Baud_Div);

        // Set parity
        if(gLineCoding.u8ParityType == 0)
            u32Reg = 0; // none parity
        else if(gLineCoding.u8ParityType == 1)
            u32Reg = 0x08; // odd parity
        else if(gLineCoding.u8ParityType == 2)
            u32Reg = 0x18; // even parity
        else
            u32Reg = 0;

        // bit width
        switch(gLineCoding.u8DataBits)
        {
        case 5:
            u32Reg |= 0;
            break;
        case 6:
            u32Reg |= 1;
            break;
        case 7:
            u32Reg |= 2;
            break;
        case 8:
            u32Reg |= 3;
            break;
        default:
            break;
        }

        // stop bit
        if(gLineCoding.u8CharFormat > 0)
            u32Reg |= 0x4; // 2 or 1.5 bits

        UART0->LINE = u32Reg;

        // Re-enable UART interrupt
        NVIC_EnableIRQ(UART0_IRQn);
    }
}

/***************************************************************/
#define HID_CMD_SIGNATURE   0x43444948

/* HID Transfer Commands */
#define HID_CMD_NONE     0x00
#define HID_CMD_ERASE    0x71
#define HID_CMD_READ     0xD2
#define HID_CMD_WRITE    0xC3
#define HID_CMD_TEST     0xB4

#define PAGE_SIZE        2048
#define TEST_PAGES       4
#define SECTOR_SIZE      4096
#define START_SECTOR     0x10

#ifdef __ICCARM__
typedef __packed struct
{
    uint8_t u8Cmd;
    uint8_t u8Size;
    uint32_t u32Arg1;
    uint32_t u32Arg2;
    uint32_t u32Signature;
    uint32_t u32Checksum;
} CMD_T;

#else
typedef struct __attribute__((__packed__))
{
    uint8_t u8Cmd;
    uint8_t u8Size;
    uint32_t u32Arg1;
    uint32_t u32Arg2;
    uint32_t u32Signature;
    uint32_t u32Checksum;
}
CMD_T;
#endif

CMD_T gCmd;

static uint8_t  g_u8PageBuff[PAGE_SIZE] = {0};    /* Page buffer to upload/download through HID report */
static uint32_t g_u32BytesInPageBuf = 0;          /* The bytes of data in g_u8PageBuff */
static uint8_t  g_u8TestPages[TEST_PAGES * PAGE_SIZE] = {0};    /* Test pages to upload/download through HID report */

int32_t HID_CmdEraseSectors(CMD_T *pCmd)
{
    uint32_t u32StartSector;
    uint32_t u32Sectors;

    u32StartSector = pCmd->u32Arg1 - START_SECTOR;
    u32Sectors = pCmd->u32Arg2;

    printf("Erase command - Sector: %d   Sector Cnt: %d\n", u32StartSector, u32Sectors);

    /* TODO: To erase the sector of storage */
    memset(g_u8TestPages + u32StartSector * SECTOR_SIZE, 0xFF, sizeof(uint8_t) * u32Sectors * SECTOR_SIZE);

    /* To note the command has been done */
    pCmd->u8Cmd = HID_CMD_NONE;

    return 0;
}


int32_t HID_CmdReadPages(CMD_T *pCmd)
{
    uint32_t u32StartPage;
    uint32_t u32Pages;

    u32StartPage = pCmd->u32Arg1;
    u32Pages     = pCmd->u32Arg2;

    printf("Read command - Start page: %d    Pages Numbers: %d\n", u32StartPage, u32Pages);

    if(u32Pages)
    {
        /* Update data to page buffer to upload */
        /* TODO: We need to update the page data if got a page read command. (0xFF is used in this sample code) */
        memcpy(g_u8PageBuff, g_u8TestPages, sizeof(g_u8PageBuff));
        g_u32BytesInPageBuf = PAGE_SIZE;

        /* The signature word is used as page counter */
        pCmd->u32Signature = 1;

        /* Trigger HID IN */
        USBD_MemCopy((uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP5)), (void *)g_u8PageBuff, EP5_MAX_PKT_SIZE);
        USBD_SET_PAYLOAD_LEN(EP5, EP5_MAX_PKT_SIZE);
        g_u32BytesInPageBuf -= EP5_MAX_PKT_SIZE;
    }

    return 0;
}


int32_t HID_CmdWritePages(CMD_T *pCmd)
{
    uint32_t u32StartPage;
    uint32_t u32Pages;

    u32StartPage = pCmd->u32Arg1;
    u32Pages     = pCmd->u32Arg2;

    printf("Write command - Start page: %d    Pages Numbers: %d\n", u32StartPage, u32Pages);
    g_u32BytesInPageBuf = 0;

    /* The signature is used to page counter */
    pCmd->u32Signature = 0;

    return 0;
}


int32_t gi32CmdTestCnt = 0;
int32_t HID_CmdTest(CMD_T *pCmd)
{
    int32_t i;
    uint8_t *pu8;

    pu8 = (uint8_t *)pCmd;
    printf("Get test command #%d (%d bytes)\n", gi32CmdTestCnt++, pCmd->u8Size);
    for(i=0; i<pCmd->u8Size; i++)
    {
        if((i&0xF) == 0)
        {
            printf("\n");
        }
        printf(" %02x", pu8[i]);
    }

    printf("\n");


    /* To note the command has been done */
    pCmd->u8Cmd = HID_CMD_NONE;

    return 0;
}


uint32_t CalCheckSum(uint8_t *buf, uint32_t size)
{
    uint32_t sum;
    int32_t i;

    i = 0;
    sum = 0;
    while(size--)
    {
        sum+=buf[i++];
    }

    return sum;

}


int32_t ProcessCommand(uint8_t *pu8Buffer, uint32_t u32BufferLen)
{
    uint32_t u32sum;


    USBD_MemCopy((uint8_t *)&gCmd, pu8Buffer, u32BufferLen);

    /* Check size */
    if((gCmd.u8Size > sizeof(gCmd)) || (gCmd.u8Size > u32BufferLen))
        return -1;

    /* Check signature */
    if(gCmd.u32Signature != HID_CMD_SIGNATURE)
        return -1;

    /* Calculate checksum & check it*/
    u32sum = CalCheckSum((uint8_t *)&gCmd, gCmd.u8Size);
    if(u32sum != gCmd.u32Checksum)
        return -1;

    switch(gCmd.u8Cmd)
    {
    case HID_CMD_ERASE:
    {
        HID_CmdEraseSectors(&gCmd);
        break;
    }
    case HID_CMD_READ:
    {
        HID_CmdReadPages(&gCmd);
        break;
    }
    case HID_CMD_WRITE:
    {
        HID_CmdWritePages(&gCmd);
        break;
    }
    case HID_CMD_TEST:
    {
        HID_CmdTest(&gCmd);
        break;
    }
    default:
        return -1;
    }

    return 0;
}


void HID_GetOutReport(uint8_t *pu8EpBuf, uint32_t u32Size)
{
    uint8_t  u8Cmd;
    uint32_t u32StartPage;
    uint32_t u32Pages;
    uint32_t u32PageCnt;

    /* Get command information */
    u8Cmd        = gCmd.u8Cmd;
    u32StartPage = gCmd.u32Arg1;
    u32Pages     = gCmd.u32Arg2;
    u32PageCnt   = gCmd.u32Signature; /* The signature word is used to count pages */


    /* Check if it is in the data phase of write command */
    if((u8Cmd == HID_CMD_WRITE) &&  (u32PageCnt < u32Pages))
    {
        /* Process the data phase of write command */

        /* Get data from HID OUT */
        USBD_MemCopy(&g_u8PageBuff[g_u32BytesInPageBuf], pu8EpBuf, EP6_MAX_PKT_SIZE);
        g_u32BytesInPageBuf += EP6_MAX_PKT_SIZE;

        /* The HOST must make sure the data is PAGE_SIZE alignment */
        if(g_u32BytesInPageBuf >= PAGE_SIZE)
        {
            printf("Writing page %d\n", u32StartPage + u32PageCnt);
            /* TODO: We should program received data to storage here */
            memcpy(g_u8TestPages + u32PageCnt * PAGE_SIZE, g_u8PageBuff, sizeof(g_u8PageBuff));
            u32PageCnt++;

            /* Write command complete! */
            if(u32PageCnt >= u32Pages)
            {
                u8Cmd = HID_CMD_NONE;

                printf("Write command complete.\n");
            }

            g_u32BytesInPageBuf = 0;

        }

        /* Update command status */
        gCmd.u8Cmd        = u8Cmd;
        gCmd.u32Signature = u32PageCnt;
    }
    else
    {
        /* Check and process the command packet */
        if(ProcessCommand(pu8EpBuf, u32Size))
        {
            printf("Unknown HID command!\n");
        }
    }
}

void HID_SetInReport(void)
{
    uint32_t u32StartPage;
    uint32_t u32TotalPages;
    uint32_t u32PageCnt;
    uint8_t *ptr;
    uint8_t u8Cmd;

    u8Cmd        = gCmd.u8Cmd;
    u32StartPage = gCmd.u32Arg1;
    u32TotalPages= gCmd.u32Arg2;
    u32PageCnt   = gCmd.u32Signature;

    /* Check if it is in data phase of read command */
    if(u8Cmd == HID_CMD_READ)
    {
        /* Process the data phase of read command */
        if((u32PageCnt >= u32TotalPages) && (g_u32BytesInPageBuf == 0))
        {
            /* The data transfer is complete. */
            u8Cmd = HID_CMD_NONE;
            printf("Read command complete!\n");
        }
        else
        {
            if(g_u32BytesInPageBuf == 0)
            {
                /* The previous page has sent out. Read new page to page buffer */
                /* TODO: We should update new page data here. (0xFF is used in this sample code) */
                printf("Reading page %d\n", u32StartPage + u32PageCnt);
                memcpy(g_u8PageBuff, g_u8TestPages + u32PageCnt * PAGE_SIZE, sizeof(g_u8PageBuff));

                g_u32BytesInPageBuf = PAGE_SIZE;

                /* Update the page counter */
                u32PageCnt++;
            }

            /* Prepare the data for next HID IN transfer */
            ptr = (uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP5));
            USBD_MemCopy(ptr, (void *)&g_u8PageBuff[PAGE_SIZE - g_u32BytesInPageBuf], EP5_MAX_PKT_SIZE);
            USBD_SET_PAYLOAD_LEN(EP5, EP5_MAX_PKT_SIZE);
            g_u32BytesInPageBuf -= EP5_MAX_PKT_SIZE;
        }
    }

    gCmd.u8Cmd        = u8Cmd;
    gCmd.u32Signature = u32PageCnt;

}


