/***************************************************************************//**
 * @file     main.c
 * @brief    ISP tool main function
 * @version  0x32
 * @date     14, June, 2017
 *
 * @note
 * Copyright (C) 2017-2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "hid_transfer.h"
#include "targetdev.h"

uint32_t CLK_GetPLLClockFreq(void)
{
    return FREQ_192MHZ;
}

/*--------------------------------------------------------------------------*/
void SYS_Init(void)
{
    uint32_t volatile i;
    /* Unlock protected registers */
    SYS_UnlockReg();
    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);
    CLK->PWRCTL |= (CLK_PWRCTL_HIRCEN_Msk | CLK_PWRCTL_HXTEN_Msk);
    CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_HCLKSEL_Msk)) | CLK_CLKSEL0_HCLKSEL_HIRC;

    // Waiting for clock switching ok
    while (CLK->STATUS & CLK_STATUS_CLKSFAIL_Msk);

    CLK->PLLCTL = CLK_PLLCTL_PD_Msk; // Disable PLL
    CLK->PLLCTL = 0x8842E;           // Enable PLL & set frequency 192MHz

    while (!(CLK->STATUS & CLK_STATUS_PLLSTB_Msk));

    /* Enable External XTAL (4~24 MHz) */
    CLK->PWRCTL |= CLK_PWRCTL_HXTEN_Msk;

    while ((CLK->STATUS & CLK_STATUS_PLLSTB_Msk) != CLK_STATUS_PLLSTB_Msk);

    CLK->CLKDIV0 = CLK->CLKDIV0 & (~CLK_CLKDIV0_HCLKDIV_Msk);   /* PLL/1 */
    CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_HCLKSEL_Msk)) | CLK_CLKSEL0_HCLKSEL_PLL;
    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;
    SYS->USBPHY &= ~SYS_USBPHY_HSUSBROLE_Msk;    /* select HSUSBD */
    /* Enable USB PHY */
    SYS->USBPHY = (SYS->USBPHY & ~(SYS_USBPHY_HSUSBROLE_Msk | SYS_USBPHY_HSUSBACT_Msk)) | SYS_USBPHY_HSUSBEN_Msk;

    for (i = 0; i < 0x1000; i++);  // delay > 10 us

    SYS->USBPHY |= SYS_USBPHY_HSUSBACT_Msk;
    /* Enable IP clock */
    CLK->AHBCLK |= CLK_AHBCLK_HSUSBDCKEN_Msk;   /* USBD20 */
}

extern uint8_t bUsbDataReady;
void USBD20_IRQHandler(void);
int32_t main(void)
{
    SYS_Init();
    FMC->ISPCTL |= FMC_ISPCTL_ISPEN_Msk;    // (1ul << 0)
    g_apromSize = GetApromSize();
    GetDataFlashInfo(&g_dataFlashAddr, &g_dataFlashSize);

    if (DetectPin != 0)
    {
        goto _APROM;
    }

    HSUSBD_Open(NULL, NULL, NULL);
    /* Endpoint configuration */
    HID_Init();
    /* Enable USBD interrupt */
    // NVIC_EnableIRQ(USBD20_IRQn);
    /* Start transaction */
    HSUSBD_CLR_SE0();

    while (DetectPin == 0)
    {
        // polling USBD interrupt flag
        USBD20_IRQHandler();

        if (bUsbDataReady == TRUE)
        {
            ParseCmd((uint8_t *)usb_rcvbuf, 64);
            EPA_Handler();
            bUsbDataReady = FALSE;
        }
    }

_APROM:
    outpw(&SYS->RSTSTS, 3);//clear bit
    outpw(&FMC->ISPCTL, inpw(&FMC->ISPCTL) & 0xFFFFFFFC);
    outpw(&SCB->AIRCR, (V6M_AIRCR_VECTKEY_DATA | V6M_AIRCR_SYSRESETREQ));

    /* Trap the CPU */
    while (1);
}
