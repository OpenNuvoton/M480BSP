/**************************************************************************//**
 * @file     main.c
 * @version  V1.10
 * @brief    Generate random numbers using TRNG.
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

#define TRNG_USE_LXT32K


void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Switch HCLK clock source to HXT */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HXT,CLK_CLKDIV0_HCLK(1));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable TRNG module clock */
    CLK_EnableModuleClock(TRNG_MODULE);

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Lock protected registers */
    SYS_LockReg();
}

void UART0_Init(void)
{

    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}


int32_t main (void)
{
    uint32_t    data32;
    char        bignumHex[64+2];

    SYS_Init();                        /* Init System, IP clock and multi-function I/O */

    UART0_Init();                      /* Initialize UART0 */

    SYS_UnlockReg();                   /* Unlock register lock protect */

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)
    {
        printf("M480MD does not support TRNG!\n");
        while (1);
    }

#ifdef TRNG_USE_LXT32K
    /* Basic Configuration */
    CLK->PWRCTL |= CLK_PWRCTL_LXTEN_Msk;
    while((CLK->STATUS & CLK_STATUS_LXTSTB_Msk) == 0);
#else
    /* Basic Configuration */
    CLK->PWRCTL |= CLK_PWRCTL_LIRCEN_Msk;
    while((CLK->STATUS & CLK_STATUS_LIRCSTB_Msk) == 0);
    RTC->LXTCTL |= 0x81;
#endif

    TRNG_Open();

    TRNG_SET_CLKP(0);                  /* PCLK is 96 MHz */

    printf("+--------------------------------------------+\n");
    printf("|  M480 TRNG true random number generation   |\n");
    printf("+--------------------------------------------+\n");

    printf("TRNG generate an 32 bits word:\n");
    if (TRNG_GenWord(&data32) != 0)
    {
        printf("TRNG_GenWord failed!\n");
        while (1);
    }
    printf("    0x%x\n", data32);

    memset(bignumHex, 0, sizeof(bignumHex));
    printf("TRNG generate an 256 bits big number:\n");
    if (TRNG_GenBignumHex(bignumHex, 256) != 0)
    {
        printf("TRNG_GenBignumHex failed!\n");
        while (1);
    }
    printf("    %s\n", bignumHex);

    printf("\nAll done.\n");

    while (1);
}



