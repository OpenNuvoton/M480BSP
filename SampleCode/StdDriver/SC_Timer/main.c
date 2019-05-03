/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Demonstrate how to use SC embedded timer
 *
  * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"


void SC0_IRQHandler(void)
{
    static uint32_t sec = 1;

    if (SC0->INTSTS & SC_INTSTS_TMR0IF_Msk)
    {
        /* Clear interrupt flag */
        SC0->INTSTS = SC_INTSTS_TMR0IF_Msk;
        printf("%d sec\n", sec++);
    }

    return;
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
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(SC0_MODULE);

    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));
    CLK_SetModuleClock(SC0_MODULE, CLK_CLKSEL3_SC0SEL_HXT, CLK_CLKDIV1_SC0(1));

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Lock protected registers */
    SYS_LockReg();
}


int main(void)
{
    /* Init System, IP clock and multi-function I/O
       In the end of SYS_Init() will issue SYS_LockReg()
       to lock protected register. If user want to write
       protected register, please issue SYS_UnlockReg()
       to unlock protected register if necessary */
    SYS_Init();

    /* Init UART to 115200-8n1 for print message */
    UART_Open(UART0, 115200);

    printf("\nThis sample code demo how to use SC embedded timer. \n");

    /* Open smartcard interface */
    SC_Open(SC0, SC_PIN_STATE_IGNORE, SC_PIN_STATE_HIGH);

    /* Enable SC TIMER0 interrupt */
    SC_ENABLE_INT(SC0, SC_INTEN_TMR0IEN_Msk);
    NVIC_EnableIRQ(SC0_IRQn);

    /* Real ETU divider value is "11+1=12", and the duration of each ETU is 12/SC_CLK */
    SC0->ETUCTL = 11;

    /* each 1,000,000 ETU will generate TIMER0 timeout event */
    SC_StartTimer(SC0, 0, SC_TMR_MODE_4, 1000000);  // timer counter will be reloaded.

    while (1);
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
