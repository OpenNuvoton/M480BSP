/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Demonstrate Timer PWM Complementary mode and Dead-Time function.
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

    /* Peripheral clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_PCLK0, 0);
    CLK_SetModuleClock(TMR1_MODULE, CLK_CLKSEL1_TMR1SEL_PCLK0, 0);

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set Timer0 PWM CH0(TM0) and Timer1 PWM CH0(TM1) */
    SYS->GPB_MFPL |= SYS_GPB_MFPL_PB4MFP_TM1 | SYS_GPB_MFPL_PB5MFP_TM0;
    /* Set Timer0 PWM CH1(T0_EXT) and Timer1 PWM CH1(T1_EXT) */
    SYS->GPH_MFPL |= SYS_GPH_MFPL_PH0MFP_TM0_EXT | SYS_GPH_MFPL_PH1MFP_TM1_EXT;

    /* Lock protected registers */
    SYS_LockReg();
}


int main(void)
{
    uint32_t u32Period, u32CMP, u32Prescaler, u32DeadTime;

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0, 115200);

    printf("+--------------------------------------------------------------+\n");
    printf("|    Timer PWM Complementary mode and Dead-Time Sample Code    |\n");
    printf("+--------------------------------------------------------------+\n\n");

    /* Configure Timer0 PWM */
    /* Change Timer to PWM counter mode */
    TPWM_ENABLE_PWM_MODE(TIMER0);

    /* Set PWM mode as complementary mode*/
    TPWM_ENABLE_COMPLEMENTARY_MODE(TIMER0);

    /* Set Timer0 PWM output frequency is 6000 Hz, duty 40% */
    TPWM_ConfigOutputFreqAndDuty(TIMER0, 6000, 40);

    /* Enable output of PWM_CH0 and PWM_CH1 */
    TPWM_ENABLE_OUTPUT(TIMER0, (TPWM_CH1|TPWM_CH0));

    /* Get u32Prescaler, u32Period and u32CMP after called TPWM_ConfigOutputFreqAndDuty() API */
    u32Prescaler = (TIMER0->PWMCLKPSC + 1);
    u32Period = (TIMER0->PWMPERIOD + 1);
    u32CMP = TIMER0->PWMCMPDAT;
    u32DeadTime = u32CMP/2;

    printf("# Timer0 PWM output frequency is 600 Hz and duty 40%%.\n");
    printf("    - Counter clock source:    PCLK0 \n");
    printf("    - Counter clock prescaler: %d \n", u32Prescaler);
    printf("    - Counter type:            Up count type \n");
    printf("    - Operation mode:          Complementary in auto-reload mode \n");
    printf("    - Period value:            %d \n", u32Period);
    printf("    - Comparator value:        %d \n", u32CMP);
    printf("# I/O configuration:\n");
    printf("    - Timer0 PWM_CH0 on PB.5, PWM_CH1 on PH.0\n\n");


    /* Configure Timer1 PWM */
    printf("# Timer1 PWM output frequency is 600 Hz and duty 20%% with dead-time insertion.\n");
    printf("    - Counter clock source:    PCLK0 \n");
    printf("    - Counter clock prescaler: %d \n", u32Prescaler);
    printf("    - Counter type:            Up count type \n");
    printf("    - Operation mode:          Complementary in auto-reload mode \n");
    printf("    - Period value:            %d \n", u32Period);
    printf("    - Comparator value:        %d \n", u32CMP);
    printf("    - Dead-Time interval:      %d \n", u32DeadTime);
    printf("# I/O configuration:\n");
    printf("    - Timer1 PWM_CH0 on PB.4, PWM_CH1 on PH.1\n\n");

    /* Change Timer to PWM counter mode */
    TPWM_ENABLE_PWM_MODE(TIMER1);

    /* Set PWM mode as complementary mode*/
    TPWM_ENABLE_COMPLEMENTARY_MODE(TIMER1);

    /* Set Timer1 PWM output frequency is 6000 Hz, duty 40% */
    TPWM_ConfigOutputFreqAndDuty(TIMER1, 6000, 40);

    /* Enable output of PWM_CH0 and PWM_CH1 */
    TPWM_ENABLE_OUTPUT(TIMER1, (TPWM_CH1|TPWM_CH0));

    /* Enable and configure dead-time interval is (u32DeadTime * TMR1_PWMCLK * prescaler) */
    SYS_UnlockReg(); // Unlock protected registers
    TPWM_EnableDeadTimeWithPrescale(TIMER1, (u32DeadTime-1));
    SYS_LockReg(); // Lock protected registers

    printf("*** Check Timer0 and Timer1 PWM output waveform by oscilloscope ***\n");

    /* Start Timer0 and Timer1 PWM counter by trigger Timer0 sync. start */
    TPWM_SET_COUNTER_SYNC_MODE(TIMER0, TPWM_CNTR_SYNC_START_BY_TIMER0);
    TPWM_SET_COUNTER_SYNC_MODE(TIMER1, TPWM_CNTR_SYNC_START_BY_TIMER0);
    TPWM_TRIGGER_COUNTER_SYNC(TIMER0);

    while(1);
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
