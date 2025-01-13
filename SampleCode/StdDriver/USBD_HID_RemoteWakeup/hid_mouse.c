/**************************************************************************//**
 * @file     hid_mouse.c
 * @brief    M480 series USBD HID mouse sample file
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

/*!<Includes */
#include <string.h>
#include "NuMicro.h"
#include "hid_mouse.h"

uint8_t volatile g_u8EP2Ready = 0;
uint8_t volatile g_u8Suspend = 0;


void PowerDown(void);

void USBD_IRQHandler(void)
{
    uint32_t volatile u32IntSts = USBD_GET_INT_FLAG();
    uint32_t volatile u32State = USBD_GET_BUS_STATE();

//------------------------------------------------------------------
    if(u32IntSts & USBD_INTSTS_VBDETIF_Msk)
    {
        // Floating detect
        USBD_CLR_INT_FLAG(USBD_INTSTS_VBDETIF_Msk);

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
    if(u32IntSts & USBD_INTSTS_BUSIF_Msk)
    {
        /* Clear event flag */
        USBD_CLR_INT_FLAG(USBD_INTSTS_BUSIF_Msk);

        if(u32State & USBD_ATTR_USBRST_Msk)
        {
            /* Bus reset */
            USBD_ENABLE_USB();
            USBD_SwReset();
            g_u8Suspend = 0;
        }
        if(u32State & USBD_ATTR_SUSPEND_Msk)
        {
            /* Enter power down to wait USB attached */
            g_u8Suspend = 1;

            /* Enable USB but disable PHY */
            USBD_DISABLE_PHY();
        }
        if(u32State & USBD_ATTR_RESUME_Msk)
        {
            /* Enable USB and enable PHY */
            USBD_ENABLE_USB();
            g_u8Suspend = 0;
        }
    }

//------------------------------------------------------------------
    if(u32IntSts & USBD_INTSTS_WAKEUP)
    {
        /* Clear event flag */
        USBD_CLR_INT_FLAG(USBD_INTSTS_WAKEUP);
    }

    if(u32IntSts & USBD_INTSTS_USBIF_Msk)
    {
        // USB event
        if(u32IntSts & USBD_INTSTS_SETUP_Msk)
        {
            // Setup packet
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_SETUP_Msk);

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
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP2);
            // Interrupt IN
            EP2_Handler();
        }

        if(u32IntSts & USBD_INTSTS_EP3)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP3);
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

void EP2_Handler(void)  /* Interrupt IN handler */
{
    g_u8EP2Ready = 1;
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
    /* EP2 ==> Interrupt IN endpoint, address 1 */
    USBD_CONFIG_EP(EP2, USBD_CFG_EPMODE_IN | INT_IN_EP_NUM);
    /* Buffer range for EP2 */
    USBD_SET_EP_BUF_ADDR(EP2, EP2_BUF_BASE);

    /* start to IN data */
    g_u8EP2Ready = 1;
}

void HID_ClassRequest(void)
{
    uint8_t buf[8];

    USBD_GetSetupPacket(buf);

    if(buf[0] & 0x80)    /* request data transfer direction */
    {
        // Device to host
        switch(buf[1])
        {
        case GET_REPORT:
//             {
//                 break;
//             }
        case GET_IDLE:
//             {
//                 break;
//             }
        case GET_PROTOCOL:
//            {
//                break;
//            }
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
        switch(buf[1])
        {
        case SET_REPORT:
        {
            if(buf[3] == 3)
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
//             {
//                 break;
//             }
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



void PowerDown()
{
    printf("Enter power down ...\n");
    while((UART0->FIFOSTS & UART_FIFOSTS_TXEMPTYF_Msk) == 0);

    /* Wakeup Enable */
    USBD->INTEN |= USBD_INTEN_WKEN_Msk;

    /* Deep sleep */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    CLK->PWRCTL |= CLK_PWRCTL_PDEN_Msk;

    __WFI();

    /* Clear PWR_DOWN_EN if it is not clear by itself */
    if(CLK->PWRCTL & CLK_PWRCTL_PDEN_Msk)
        CLK->PWRCTL ^= CLK_PWRCTL_PDEN_Msk;

    /* Note HOST to resume USB tree if it is suspended and remote wakeup enabled */
    if(g_usbd_RemoteWakeupEn)
    {
        /* Enable PHY before sending Resume('K') state */
        USBD->ATTR |= USBD_ATTR_PHYEN_Msk;

        /* Keep remote wakeup for 1 ms */
        USBD->ATTR |= USBD_ATTR_RWAKEUP_Msk;
        CLK_SysTickDelay(1000); /* Delay 1ms */
        USBD->ATTR ^= USBD_ATTR_RWAKEUP_Msk;
    }

    printf("device wakeup!\n");

}

void HID_UpdateMouseData(void)
{
    uint8_t *buf;
    uint32_t u32Reg;
    static int32_t x = 0, y = 0;
    uint32_t u32MouseKey;
	static uint32_t u8MousePreKey = 0xFF;

    /*
       Key definition:
           PC0 Down
           PC1 right
           PC2 up
           PC3 right key
           PC4 left
           PC5 left key
    */


    /* Enter power down when USB suspend */
    if(g_u8Suspend)
    {
        PowerDown();

        /* Waiting for key release */
        while((PC->PIN & 0x3F) != 0x3F);
    }

    if(g_u8EP2Ready)
    {
        buf = (uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP2));

        u32Reg = PC->PIN & 0x3F;

        /* To control Y axis */
        if((u32Reg & 1) == 0)
            y += 1;
        else if((u32Reg & 4) == 0)
            y += -1;
        else
            y = 0;
        if(y > 48) y = 48;
        if(y < -48) y = -48;

        /* To control X axis */
        if((u32Reg & 2) == 0)
            x += 1;
        else if((u32Reg & 0x10) == 0)
            x += -1;
        else
            x = 0;
        if(x > 48) x = 48;
        if(x < -48) x = -48;

        /* Mouse key */
        u32MouseKey = 0;
        if((u32Reg & 0x20) == 0)
            u32MouseKey |= 1; /* Left key */
        if((u32Reg & 0x8) == 0)
            u32MouseKey |= 2; /* Right key */

        /* Update new report data */
        buf[0] = u32MouseKey;
        buf[1] = x >> 2;
        buf[2] = y >> 2;
        buf[3] = 0x00;

		if(x | y | (u8MousePreKey != u32MouseKey))
        {
            u8MousePreKey = u32MouseKey;
            g_u8EP2Ready = 0;
            /* Set transfer length and trigger IN transfer */
            USBD_SET_PAYLOAD_LEN(EP2, 4);
        }
    }
}


