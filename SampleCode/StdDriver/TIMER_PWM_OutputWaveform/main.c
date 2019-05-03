/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Demonstrate output different duty waveform in Timer0~Timer3 PWM.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

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

    /* Enable peripheral clock */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(TMR0_MODULE);
    CLK_EnableModuleClock(TMR1_MODULE);
    CLK_EnableModuleClock(TMR2_MODULE);
    CLK_EnableModuleClock(TMR3_MODULE);

    /* Peripheral clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_PCLK0, 0);
    CLK_SetModuleClock(TMR1_MODULE, CLK_CLKSEL1_TMR1SEL_PCLK0, 0);
    CLK_SetModuleClock(TMR2_MODULE, CLK_CLKSEL1_TMR2SEL_PCLK1, 0);
    CLK_SetModuleClock(TMR3_MODULE, CLK_CLKSEL1_TMR3SEL_PCLK1, 0);


    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set Timer0~4 PWM output pins */
    SYS->GPG_MFPL |= SYS_GPG_MFPL_PG2MFP_TM0 | SYS_GPG_MFPL_PG3MFP_TM1 | SYS_GPG_MFPL_PG4MFP_TM2;
    SYS->GPF_MFPH |= SYS_GPF_MFPH_PF11MFP_TM3;

    /* Lock protected registers */
    SYS_LockReg();
}

int main(void)
{
    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0, 115200);

    printf("+-------------------------------------------------+\n");
    printf("|    Timer0~Timer3 PWM Output Duty Sample Code    |\n");
    printf("+-------------------------------------------------+\n\n");

    printf("# Timer0 PWM_CH0 output frequency is 18000 Hz and duty is 50%%.\n");
    printf("# Timer1 PWM_CH0 output frequency is 10000 Hz and duty is 10%%.\n");
    printf("# Timer2 PWM_CH0 output frequency is  9000 Hz and duty is 75%%.\n");
    printf("# Timer3 PWM_CH0 output frequency is  4000 Hz and duty is 20%%.\n");
    printf("# I/O configuration:\n");
    printf("    - Timer0 PWM_CH0 on PG.2\n");
    printf("    - Timer1 PWM_CH0 on PG.3\n");
    printf("    - Timer2 PWM_CH0 on PG.4\n");
    printf("    - Timer3 PWM_CH0 on PF.11\n\n");

    /* Change Timer to PWM counter mode */
    TPWM_ENABLE_PWM_MODE(TIMER0);
    TPWM_ENABLE_PWM_MODE(TIMER1);
    TPWM_ENABLE_PWM_MODE(TIMER2);
    TPWM_ENABLE_PWM_MODE(TIMER3);

    /* Set PWM mode as independent mode*/
    TPWM_ENABLE_INDEPENDENT_MODE(TIMER0);
    TPWM_ENABLE_INDEPENDENT_MODE(TIMER1);
    TPWM_ENABLE_INDEPENDENT_MODE(TIMER2);
    TPWM_ENABLE_INDEPENDENT_MODE(TIMER3);

    /* Enable output of PWM_CH0 */
    TPWM_ENABLE_OUTPUT(TIMER0, TPWM_CH0);
    TPWM_ENABLE_OUTPUT(TIMER1, TPWM_CH0);
    TPWM_ENABLE_OUTPUT(TIMER2, TPWM_CH0);
    TPWM_ENABLE_OUTPUT(TIMER3, TPWM_CH0);

    /* Set Timer0 PWM output frequency is 18000 Hz, duty 50% in up count type */
    TPWM_ConfigOutputFreqAndDuty(TIMER0, 18000, 50);

    /* Set Timer1 PWM output frequency is 10000 Hz, duty 10% in up count type */
    TPWM_ConfigOutputFreqAndDuty(TIMER1, 10000, 10);

    /* Set Timer2 PWM output frequency is 9000 Hz, duty 75% in up count type */
    TPWM_ConfigOutputFreqAndDuty(TIMER2, 9000, 75);

    /* Set Timer3 PWM output frequency is 4000 Hz, duty 20% in up count type */
    TPWM_ConfigOutputFreqAndDuty(TIMER3, 4000, 20);

    /* Set PWM up count type */
    TPWM_SET_COUNTER_TYPE(TIMER0, TPWM_UP_COUNT);
    TPWM_SET_COUNTER_TYPE(TIMER1, TPWM_UP_COUNT);
    TPWM_SET_COUNTER_TYPE(TIMER2, TPWM_UP_COUNT);
    TPWM_SET_COUNTER_TYPE(TIMER3, TPWM_UP_COUNT);

    /* Start Timer PWM counter */
    TPWM_START_COUNTER(TIMER0);
    TPWM_START_COUNTER(TIMER1);
    TPWM_START_COUNTER(TIMER2);
    TPWM_START_COUNTER(TIMER3);

    printf("*** Check Timer0~Timer3 PWM_CH0 output waveform by oscilloscope ***\n");

    while(1);
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
