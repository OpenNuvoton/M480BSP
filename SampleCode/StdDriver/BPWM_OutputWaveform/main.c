/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Demonstrate how to use BPWM counter output waveform.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK       192000000


void SYS_Init(void)
{

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT clock (external XTAL 12MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);

    /* Set PCLK0 = PCLK1 = HCLK/2 */
    CLK->PCLKDIV = (CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2);

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable BPWM0 clock source */
    CLK_EnableModuleClock(BPWM0_MODULE);

    /* Select BPWM module clock source */
    CLK_SetModuleClock(BPWM0_MODULE, CLK_CLKSEL2_BPWM0SEL_PCLK0, 0);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    SystemCoreClockUpdate();


    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set PA.0~5 multi-function pin for BPWM0 channel 0~5 */
    SYS->GPA_MFPL = (SYS->GPA_MFPL & ~SYS_GPA_MFPL_PA0MFP_Msk) | SYS_GPA_MFPL_PA0MFP_BPWM0_CH0;
    SYS->GPA_MFPL = (SYS->GPA_MFPL & ~SYS_GPA_MFPL_PA1MFP_Msk) | SYS_GPA_MFPL_PA1MFP_BPWM0_CH1;
    SYS->GPA_MFPL = (SYS->GPA_MFPL & ~SYS_GPA_MFPL_PA2MFP_Msk) | SYS_GPA_MFPL_PA2MFP_BPWM0_CH2;
    SYS->GPA_MFPL = (SYS->GPA_MFPL & ~SYS_GPA_MFPL_PA3MFP_Msk) | SYS_GPA_MFPL_PA3MFP_BPWM0_CH3;
    SYS->GPA_MFPL = (SYS->GPA_MFPL & ~SYS_GPA_MFPL_PA4MFP_Msk) | SYS_GPA_MFPL_PA4MFP_BPWM0_CH4;
    SYS->GPA_MFPL = (SYS->GPA_MFPL & ~SYS_GPA_MFPL_PA5MFP_Msk) | SYS_GPA_MFPL_PA5MFP_BPWM0_CH5;
}

void UART0_Init()
{

    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

int32_t main(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART to 115200-8n1 for print message */
    UART0_Init();

    printf("+------------------------------------------------------------------------+\n");
    printf("|                          BPWM Driver Sample Code                       |\n");
    printf("|                                                                        |\n");
    printf("+------------------------------------------------------------------------+\n");
    printf("  This sample code will output waveform with BPWM0 channel 0~5.\n");
    printf("  I/O configuration:\n");
    printf("  BPWM0 channel 0: 180000 Hz, duty 90%%.\n");
    printf("  BPWM0 channel 1: 180000 Hz, duty 80%%.\n");
    printf("  BPWM0 channel 2: 180000 Hz, duty 75%%.\n");
    printf("  BPWM0 channel 3: 180000 Hz, duty 70%%.\n");
    printf("  BPWM0 channel 4: 180000 Hz, duty 60%%.\n");
    printf("  BPWM0 channel 5: 180000 Hz, duty 50%%.\n");
    printf("  waveform output pin: BPWM0_CH0(PA.0), BPWM0_CH1(PA.1), BPWM0_CH2(PA.2), BPWM0_CH3(PA.3), BPWM0_CH4(PA.4), BPWM0_CH5(PA.5)\n");

    /* BPWM0 channel 0~5 frequency and duty configuration are as follows */
    /* Because of BPWM0 channel 0~5 share one period, so the period value of all channels need set the same. */
    BPWM_ConfigOutputChannel(BPWM0, 0, 180000, 90);
    BPWM_ConfigOutputChannel(BPWM0, 1, 180000, 80);
    BPWM_ConfigOutputChannel(BPWM0, 2, 180000, 75);
    BPWM_ConfigOutputChannel(BPWM0, 3, 180000, 70);
    BPWM_ConfigOutputChannel(BPWM0, 4, 180000, 60);
    BPWM_ConfigOutputChannel(BPWM0, 5, 180000, 50);

    /* Enable output of BPWM0 channel 0~5 */
    BPWM_EnableOutput(BPWM0, 0x3F);

    /* Start BPWM0 counter */
    BPWM_Start(BPWM0, 0x3F);

    //printf("Press any key to stop.\n");
    getchar();

    /* Start BPWM0 counter */
    BPWM_ForceStop(BPWM0, 0x3F);

    printf("Done.");
    while(1);

}


/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
