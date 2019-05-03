/**************************************************************************//**
 * @file     main.c
 * @version  2.0.0
 * @date     20, June, 2017
 * @brief    Use MKROM API to do internal ISP. This sample code is run at LDROM,
 *           and use API to update APROM. After reset the system, the program
 *           will boot from APROM.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "BootIspLib.h"

void UART1_IRQHandler(void)
{
    UART1_ISR();
}

void SYS_Init(void)
{
    uint32_t volatile i;

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

    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);


    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

}


int32_t main (void)
{
    uint32_t au32Config[2];

    SYS_Init();
    UART_Open(UART0, 115200);

    printf("\n");
    printf("+----------------------------------------+\n");
    printf("|      M480 firmware update by UART1     |\n");
    printf("+----------------------------------------+\n");

    /*******************************************************/
    /* MKROM support UART1 ISP, should initial UART1 first */
    /*******************************************************/
    /* UART1: TX = PB.7, RX = PB.6 */
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB6MFP_Msk | SYS_GPB_MFPL_PB7MFP_Msk);
    SYS->GPB_MFPL |= ((6ul << SYS_GPB_MFPL_PB6MFP_Pos) | (6ul << SYS_GPB_MFPL_PB7MFP_Pos));
    /* UART1 line configuration for (115200,n,8,1) */
    CLK->CLKSEL1 |= CLK_CLKSEL1_UART1SEL_Msk;   /* HIRC */
    CLK->APBCLK0 |= CLK_APBCLK0_UART1CKEN_Msk;
    UART1->LINE = UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1;
    UART1->FIFO = UART_FIFO_RFITL_14BYTES | UART_FIFO_RTSTRGLV_14BYTES;
    UART1->BAUD = (UART_BAUD_MODE2 | UART_BAUD_MODE2_DIVIDER(__HIRC, 115200));
    UART1->TOUT = 0x40;
    NVIC_SetPriority (UART1_IRQn, 2);
    NVIC_EnableIRQ(UART1_IRQn);
    UART1->INTEN = (UART_INTEN_TOCNTEN_Msk | UART_INTEN_RXTOIEN_Msk | UART_INTEN_RDAIEN_Msk);

    /***********************************************************/
    /* This sample is running at LDROM. Will update the APROM. */
    /* Change the boot select to boot from APROM               */
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


    UART1_ISP();
    while(1);
}



/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/

