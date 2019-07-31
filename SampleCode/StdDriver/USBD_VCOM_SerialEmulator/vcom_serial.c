/**************************************************************************//**
 * @file     vcom_serial.c
 * @brief    M480 series USBD driver Sample file
 * @version  2.0.0
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

/*!<Includes */
#include <string.h>
#include "NuMicro.h"
#include "vcom_serial.h"

uint32_t volatile g_u32OutToggle = 0;

/*--------------------------------------------------------------------------*/
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
            // Bulk Out
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




/*--------------------------------------------------------------------------*/
/**
  * @brief  USBD Endpoint Config.
  * @param  None.
  * @retval None.
  */
void VCOM_Init(void)
{
    /* Init setup packet buffer */
    /* Buffer for setup packet -> [0 ~ 0x7] */
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
}


void VCOM_ClassRequest(void)
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
            if (buf[4] == 0) /* VCOM-1 */
                USBD_PrepareCtrlOut((uint8_t *)&gLineCoding, 7);

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
            break;
        }
        }
    }
}

void VCOM_LineCoding(uint8_t port)
{
    uint32_t u32Reg;
    uint32_t u32Baud_Div;

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
        u32Baud_Div = UART_BAUD_MODE2_DIVIDER(__HXT, gLineCoding.u32DTERate);

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






