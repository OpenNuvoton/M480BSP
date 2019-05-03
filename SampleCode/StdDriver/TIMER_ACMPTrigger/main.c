/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Use ACMP to trigger Timer0 counter reset mode.
 *
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"


void TMR0_IRQHandler(void)
{
    printf("ACMP triggered timer reset while counter is at %d\n", TIMER_GetCaptureData(TIMER0));
    // Clear timer capture interrupt flag.
    TIMER_ClearCaptureIntFlag(TIMER0);

}


void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable External XTAL (4~24 MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for 12MHz clock ready */
    CLK_WaitClockReady( CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(TMR0_MODULE);
    CLK_EnableModuleClock(ACMP01_MODULE);

    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HXT, 0);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set PB4 multi-function pin for ACMP0 positive input pin */
    SYS->GPB_MFPL |= SYS_GPB_MFPL_PB4MFP_ACMP1_P1;
    /* Disable digital input path of analog pin ACMP1_P1 to prevent leakage */
    GPIO_DISABLE_DIGITAL_PATH(PB, (1ul << 4));

    /* Lock protected registers */
    SYS_LockReg();
}


int main(void)
{
    int volatile i;

    /* Init System, IP clock and multi-function I/O
       In the end of SYS_Init() will issue SYS_LockReg()
       to lock protected register. If user want to write
       protected register, please issue SYS_UnlockReg()
       to unlock protected register if necessary */
    SYS_Init();

    /* Init UART to 115200-8n1 for print message */
    UART_Open(UART0, 115200);


    PB->DOUT |= 1 << GPIO_DOUT_DOUT5_Pos;    // Set init state to high
    PB->MODE = (PB->MODE & ~GPIO_MODE_MODE5_Msk) | (GPIO_MODE_OUTPUT << GPIO_MODE_MODE5_Pos);  // Set to output mode

    printf("\nThis sample code demonstrate ACMP trigger timer counter reset mode.\n");
    printf("Please connect PB.5 with ACMP0 positive input pin PB.4,  press any key to continue\n");
    getchar();

    // Give a dummy target frequency here. Will over write capture resolution with macro
    TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 1000000);

    // Update prescale to set proper resolution.
    TIMER_SET_PRESCALE_VALUE(TIMER0, 0);

    // Set compare value as large as possible, so don't need to worry about counter overrun too frequently.
    TIMER_SET_CMP_VALUE(TIMER0, 0xFFFFFF);

    // Configure Timer 0 free counting mode
    TIMER_EnableCapture(TIMER0, TIMER_CAPTURE_COUNTER_RESET_MODE, TIMER_CAPTURE_EVENT_RISING);
    // Set capture source from ACMP
    TIMER0->CTL |= TIMER_CTL_CAPSRC_Msk;
    // Set capture source from ACMP1
    TIMER0->EXTCTL |= (1 << TIMER_EXTCTL_ICAPSEL_Pos);

    // Start Timer 0
    TIMER_Start(TIMER0);

    /* Configure ACMP1. Enable ACMP1 and select band-gap voltage as the source of ACMP negative input. */
    ACMP_Open(ACMP01, 1, ACMP_CTL_NEGSEL_VBG, ACMP_CTL_HYSTERESIS_DISABLE);
    /* Select P1 as ACMP1 positive input channel */
    ACMP_SELECT_P(ACMP01, 1, ACMP_CTL_POSSEL_P1);
    // Enable timer interrupt
    TIMER_EnableCaptureInt(TIMER0);
    NVIC_EnableIRQ(TMR0_IRQn);

    while(1)
    {
        PB5 = 0; // low
        CLK_SysTickDelay(10000);
        PB5 = 1;  // high
        CLK_SysTickDelay(10000);
    }

}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/


