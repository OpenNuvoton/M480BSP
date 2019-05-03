/***************************************************************************//**
 * @file     main.c
 * @brief    Demonstrate how to implement a composite device.(USB micro printer device and HID Transfer).
 *           Transfer data between USB device and PC through USB HID interface.
 *           A windows tool is also included in this sample code to connect with a USB device.
 * @version  2.0.0
 *
 * @note
 *           Windows tool: User need to input the specific PID for the USB HID device connected to PC.
 *                         PID format with hexadecimal.
 *
 *           -> PID is 0xAABB in this sample.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "micro_printer_and_hid_transfer.h"
#define CRYSTAL_LESS        1
#define TRIM_INIT           (SYS_BASE+0x10C)

void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable External XTAL (4~24 MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for 12MHz clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Switch HCLK clock source to HXT */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HXT,CLK_CLKDIV0_HCLK(1));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* M480LD support crystal-less */
    if (((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1) && (CRYSTAL_LESS))
    {
        CLK->PWRCTL |= CLK_PWRCTL_HIRC48MEN_Msk;
        /* Select IP clock source */
        CLK->CLKSEL0 &= ~CLK_CLKSEL0_USBSEL_Msk;
    }
    else
    {
        /* Select IP clock source */
        CLK->CLKSEL0 |= CLK_CLKSEL0_USBSEL_Msk;
        CLK->CLKDIV0 = (CLK->CLKDIV0 & ~CLK_CLKDIV0_USBDIV_Msk) | CLK_CLKDIV0_USB(4);
    }

    /* Select USBD */
    SYS->USBPHY = (SYS->USBPHY & ~SYS_USBPHY_USBROLE_Msk) | SYS_USBPHY_USBEN_Msk | SYS_USBPHY_SBO_Msk;

    /* Enable IP clock */
    CLK_EnableModuleClock(USBD_MODULE);

    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Set PA.12 ~ PA.14 to input mode */
    PA->MODE &= ~(GPIO_MODE_MODE12_Msk | GPIO_MODE_MODE13_Msk | GPIO_MODE_MODE14_Msk);
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA12MFP_Msk|SYS_GPA_MFPH_PA13MFP_Msk|SYS_GPA_MFPH_PA14MFP_Msk|SYS_GPA_MFPH_PA15MFP_Msk);
    SYS->GPA_MFPH |= (SYS_GPA_MFPH_PA12MFP_USB_VBUS|SYS_GPA_MFPH_PA13MFP_USB_D_N|SYS_GPA_MFPH_PA14MFP_USB_D_P|SYS_GPA_MFPH_PA15MFP_USB_OTG_ID);

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

}

void UART0_Init(void)
{

    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0, 115200);
}


int32_t main (void)
{
    uint32_t u32TrimInit;
    uint8_t Str[9];
    SYS_UnlockReg();

    SYS_Init();
    UART0_Init();

    printf("+-------------------------------------------------------+\n");
    printf("|          NnMicro USB composite device Sample Code     |\n");
    printf("|          USB Micro Printer + HID Transfer             |\n");
    printf("+-------------------------------------------------------+\n");

    USBD_Open(&gsInfo, PTR_ClassRequest, NULL);

    /* Endpoint configuration */
    PTR_Init();
    USBD_Start();

    if (((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1) && (CRYSTAL_LESS))
    {
        /* Start USB trim */
        USBD->INTSTS = USBD_INTSTS_SOFIF_Msk;
        while((USBD->INTSTS & USBD_INTSTS_SOFIF_Msk) == 0);
        SYS->HIRCTCTL = 0x1;
        SYS->HIRCTCTL |= SYS_HIRCTCTL_REFCKSEL_Msk;
        /* Backup default trim */
        u32TrimInit = M32(TRIM_INIT);
    }

    NVIC_EnableIRQ(USBD_IRQn);

    while(1)
    {
        if (((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1) && (CRYSTAL_LESS))
        {
            /* Start USB trim if it is not enabled. */
            if ((SYS->HIRCTCTL & SYS_HIRCTCTL_FREQSEL_Msk) != 1)
            {
                if(USBD->INTSTS & USBD_INTSTS_SOFIF_Msk)
                {
                    /* Clear SOF */
                    USBD->INTSTS = USBD_INTSTS_SOFIF_Msk;

                    /* Re-enable crystal-less */
                    SYS->HIRCTCTL = 0x1;
                    SYS->HIRCTCTL |= SYS_HIRCTCTL_REFCKSEL_Msk;
                }
            }

            /* Disable USB Trim when error */
            if (SYS->HIRCTISTS & (SYS_HIRCTISTS_CLKERRIF_Msk | SYS_HIRCTISTS_TFAILIF_Msk))
            {
                /* Init TRIM */
                M32(TRIM_INIT) = u32TrimInit;

                /* Disable crystal-less */
                SYS->HIRCTCTL = 0;

                /* Clear error flags */
                SYS->HIRCTISTS = SYS_HIRCTISTS_CLKERRIF_Msk | SYS_HIRCTISTS_TFAILIF_Msk;

                /* Clear SOF */
                USBD->INTSTS = USBD_INTSTS_SOFIF_Msk;
            }
        }
        CLK_SysTickDelay(2000);   // delay
        if(++Str[1] > 0x39)
            Str[1] = 0x30;      // increase 1 to 10 than reset to 0
        PE->DOUT ^= 0x40;
    }
}
