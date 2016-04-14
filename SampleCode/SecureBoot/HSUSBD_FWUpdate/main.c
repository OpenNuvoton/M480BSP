/******************************************************************************
 * @file     main.c
 * @version  2.0.0
 * @date     20, June, 2017
 * @brief    Use MKROM API to do internal ISP. This sample code is run at APROM,
 *           and use API to update LDROM. After reset the system, the program will
 *           boot from LDROM.
 *
 * @note
 * Copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "bootisplib.h"


/****************************************************/
void USBD20_IRQHandler(void)
{
    HSUSBD_ISR();
}

void SYS_Init(void)
{
    uint32_t volatile i;

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

    SYS->USBPHY &= ~SYS_USBPHY_HSUSBROLE_Msk;    /* select HSUSBD */
    /* Enable USB PHY */
    SYS->USBPHY = (SYS->USBPHY & ~(SYS_USBPHY_HSUSBROLE_Msk | SYS_USBPHY_HSUSBACT_Msk)) | SYS_USBPHY_HSUSBEN_Msk;
    for (i=0; i<0x1000; i++);      // delay > 10 us
    SYS->USBPHY |= SYS_USBPHY_HSUSBACT_Msk;

    /* Enable IP clock */
    CLK_EnableModuleClock(HSUSBD_MODULE);

    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Init UART0 multi-function pins */
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD2MFP_Msk | SYS_GPD_MFPL_PD3MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD2MFP_UART0_RXD | SYS_GPD_MFPL_PD3MFP_UART0_TXD);

}

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main (void)
{
    uint32_t au32Config[2];

    SYS_Init();
    UART_Open(UART0, 115200);

    printf("\n");
    printf("+-----------------------------------------+\n");
    printf("|      M480 update firmware by HSUSBD     |\n");
    printf("+-----------------------------------------+\n");

    /***********************************************************/
    /* This sample is running at APROM. Will update the LDROM. */
    /* Change the boot select to boot from LDROM               */
    /***********************************************************/
    SYS_UnlockReg();
    /* Enable FMC ISP function */
    CLK->AHBCLK |= CLK_AHBCLK_ISPCKEN_Msk;
    FMC_Open();

    FMC_ReadConfig(au32Config, 2);
    FMC_ENABLE_CFG_UPDATE();
    if ((au32Config[0] & 0x80) == 0x80) /* boot from APROM */
        au32Config[0] &= ~0x80;
    else
        au32Config[0] |= 0x80;
    FMC_WriteConfig(au32Config, 2);
    /***********************************************/

    HSUSBD_ISP();
    while(1);
}



/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/

