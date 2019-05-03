/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Use timer to wake up system from Power-down mode periodically.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

void TMR0_IRQHandler(void)
{
    // Clear wake up flag
    TIMER_ClearWakeupFlag(TIMER0);
    // Clear interrupt flag
    TIMER_ClearIntFlag(TIMER0);
}

void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Set X32_OUT(PF.4) and X32_IN(PF.5) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE4_Msk | GPIO_MODE_MODE5_Msk);

    /* Enable External XTAL (4~24 MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);
    /* Enable LXT */
    CLK_EnableXtalRC(CLK_PWRCTL_LXTEN_Msk);

    /* Waiting for 12MHz clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Waiting for LIRC clock stable */
    CLK_WaitClockReady(CLK_STATUS_LXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Select Timer clock source from LIRC */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(TMR0_MODULE);

    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_LXT, 0);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock and CycylesPerUs automatically. */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Lock protected registers */
    SYS_LockReg();
}

int main(void)
{
    int i = 0;
    /* Init System, IP clock and multi-function I/O
       In the end of SYS_Init() will issue SYS_LockReg()
       to lock protected register. If user want to write
       protected register, please issue SYS_UnlockReg()
       to unlock protected register if necessary */
    SYS_Init();
    /* Init UART to 115200-8n1 for print message */
    UART_Open(UART0, 115200);
    printf("Timer power down/wake up sample code\n");
    while(!UART_IS_TX_EMPTY(UART0));

    /* Initial Timer0 to periodic mode with 1Hz, since system is fast (192MHz)
       and timer is slow (32kHz), and following function calls all modified timer's
       CTL register, so add extra delay between each function call and make sure the
       setting take effect */
    TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 1);
    CLK_SysTickDelay(50);
    /* Enable timer wake up system */
    TIMER_EnableWakeup(TIMER0);
    CLK_SysTickDelay(50);
    /* Enable Timer0 interrupt */
    TIMER_EnableInt(TIMER0);
    CLK_SysTickDelay(50);
    NVIC_EnableIRQ(TMR0_IRQn);
    /* Start Timer0 counting */
    TIMER_Start(TIMER0);
    CLK_SysTickDelay(50);
    /* Unlock protected registers */
    SYS_UnlockReg();
    while(1)
    {
        CLK_PowerDown();
        printf("Wake %d\n", i++);
        while(!UART_IS_TX_EMPTY(UART0));
    }

}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/


