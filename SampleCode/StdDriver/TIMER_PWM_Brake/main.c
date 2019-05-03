/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Demonstrate how to use Timer0 PWM brake function.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

void TMR0_IRQHandler(void)
{
    printf("\nFault brake!\n");
    printf("Press any key to unlock brake state. (TIMER0 PWM output will toggle again)\n");
    getchar();

    // Clear brake interrupt flag
    SYS_UnlockReg();
    //TPWM_ClearFaultBrakeIntFlag(TIMER0, TPWM_BRAKE_EDGE);
    TIMER0->PWMINTSTS1 = TIMER_PWMINTSTS1_BRKEIF0_Msk | TIMER_PWMINTSTS1_BRKEIF1_Msk | TIMER_PWMINTSTS1_BRKESTS0_Msk | TIMER_PWMINTSTS1_BRKESTS1_Msk;
    SYS_LockReg();
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

    /* Enable peripheral clock */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(TMR0_MODULE);

    /* Peripheral clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_PCLK0, 0);

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set Timer0 PWM output pins and EPWM1 brake pin 0 (TPWM_TM_BRAKE2),
       Timers share the same brake pins with EPWM */
    SYS->GPB_MFPL |= SYS_GPB_MFPL_PB5MFP_TM0 | SYS_GPB_MFPL_PB7MFP_EPWM1_BRAKE0;

    /* Lock protected registers */
    SYS_LockReg();
}

int main(void)
{
    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0, 115200);

    printf("\nL->H state change on PB.7 will generate brake interrupt,\n");
    printf("and Timer0 PWM output will stop until brake state cleared.\n");

    /* Change Timer to PWM counter mode */
    TPWM_ENABLE_PWM_MODE(TIMER0);

    /* Set PWM mode as independent mode*/
    TPWM_ENABLE_INDEPENDENT_MODE(TIMER0);

    /* Set PWM up count type */
    TPWM_SET_COUNTER_TYPE(TIMER0, TPWM_UP_COUNT);

    /* Enable output of PWM_CH0 */
    TPWM_ENABLE_OUTPUT(TIMER0, TPWM_CH0);

    /* Set Timer0 PWM output frequency is 18000 Hz, duty 50% in up count type */
    TPWM_ConfigOutputFreqAndDuty(TIMER0, 18000, 50);

    /* Start Timer PWM counter */
    TPWM_START_COUNTER(TIMER0);

    // Enable brake and interrupt, PWM output stays at low after brake event
    SYS_UnlockReg();
    TPWM_SET_BRAKE_PIN_SOURCE(TIMER0, TPWM_TM_BRAKE2);
    TPWM_EnableFaultBrake(TIMER0, TPWM_OUTPUT_LOW, TPWM_OUTPUT_LOW, TPWM_BRAKE_SOURCE_EDGE_BKPIN);
    TPWM_EnableFaultBrakeInt(TIMER0, TPWM_BRAKE_EDGE);
    SYS_LockReg();

    NVIC_EnableIRQ(TMR0_IRQn);

    while(1);
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
