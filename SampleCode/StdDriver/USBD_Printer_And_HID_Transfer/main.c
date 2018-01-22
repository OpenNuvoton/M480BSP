/******************************************************************************
 * @file     main.c
 * @brief    Demonstrate how to implement a composite device.(USB micro printer device and HID Transfer).
 *           Transfer data between USB device and PC through USB HID interface.
 *           A windows tool is also included in this sample code to connect with a USB device.
 * @version  2.0.0
 * @date     22, Aug, 2016
 *
 * @note
 *           Windows tool: User need to input the specific PID for the USB HID device connected to PC.
 *                         PID format with hexadecimal.
 *
 *           -> PID is 0xAABB in this sample.
 *
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "micro_printer_and_hid_transfer.h"

/*--------------------------------------------------------------------------*/
void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable External XTAL (4~24 MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for 12MHz clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Switch HCLK clock source to HXT */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HXT,CLK_CLKDIV0_HCLK(1));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_PCLK0DIV2 | CLK_PCLKDIV_PCLK1DIV2;

    /* Select USBD */
    SYS->USBPHY = (SYS->USBPHY & ~SYS_USBPHY_USBROLE_Msk) | SYS_USBPHY_USBEN_Msk | SYS_USBPHY_SBO_Msk;

    /* Select IP clock source */
    CLK->CLKDIV0 = (CLK->CLKDIV0 & ~CLK_CLKDIV0_USBDIV_Msk) | CLK_CLKDIV0_USB(4);

    /* Enable IP clock */
    CLK_EnableModuleClock(USBD_MODULE);

    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA12MFP_Msk|SYS_GPA_MFPH_PA13MFP_Msk|SYS_GPA_MFPH_PA14MFP_Msk|SYS_GPA_MFPH_PA15MFP_Msk);
    SYS->GPA_MFPH |= (SYS_GPA_MFPH_PA12MFP_USB_VBUS|SYS_GPA_MFPH_PA13MFP_USB_D_N|SYS_GPA_MFPH_PA14MFP_USB_D_P|SYS_GPA_MFPH_PA15MFP_USB_OTG_ID);

    /* Init UART0 multi-function pins */
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD2MFP_Msk | SYS_GPD_MFPL_PD3MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD2MFP_UART0_RXD | SYS_GPD_MFPL_PD3MFP_UART0_TXD);

}

void UART0_Init(void)
{

    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0, 115200);
}


/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main (void)
{
    uint8_t Str[9];

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

    NVIC_EnableIRQ(USBD_IRQn);

    PE->MODE = 0x5000;   //??

    while(1) {
        CLK_SysTickDelay(2000);   // delay
        if(++Str[1] > 0x39)
            Str[1] = 0x30;      // increase 1 to 10 than reset to 0
        PE->DOUT ^= 0x40;
    }
}
