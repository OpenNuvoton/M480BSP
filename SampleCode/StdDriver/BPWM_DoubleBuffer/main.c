/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Change duty cycle and period of output waveform by BPWM Double Buffer function.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK       192000000


/**
 * @brief       BPWM0 IRQ Handler
 *
 * @param       None
 *
 * @return      None
 *
 * @details     ISR to handle BPWM0 interrupt event
 */
void BPWM0_IRQHandler(void)
{
    static int toggle = 0;

    // Update BPWM0 channel 0 period and duty
    if(toggle == 0)
    {
        BPWM_SET_CNR(BPWM0, 0, 99);
        BPWM_SET_CMR(BPWM0, 0, 39);
    }
    else
    {
        BPWM_SET_CNR(BPWM0, 0, 399);
        BPWM_SET_CMR(BPWM0, 0, 199);
    }
    toggle ^= 1;
    // Clear channel 0 period interrupt flag
    BPWM_ClearPeriodIntFlag(BPWM0, 0);
}

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

    /* Set PA.0 multi-function pin for BPWM0 channel 0 */
    SYS->GPA_MFPL &= ~SYS_GPA_MFPL_PA0MFP_Msk;
    SYS->GPA_MFPL |= SYS_GPA_MFPL_PA0MFP_BPWM0_CH0;
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
    printf("|                          BPWM Driver Sample Code                        |\n");
    printf("|                                                                        |\n");
    printf("+------------------------------------------------------------------------+\n");
    printf("  This sample code will use BPWM0 channel 0 to output waveform\n");
    printf("  I/O configuration:\n");
    printf("    waveform output pin: BPWM0 channel 0(PA.0)\n");
    printf("\nUse double buffer feature.\n");

    /*
        BPWM0 channel 0 waveform of this sample shown below:

        |<-        CNR + 1  clk     ->|  CNR + 1 = 399 + 1 CLKs
                       |<-CMR+1 clk ->|  CMR + 1 = 199 + 1 CLKs
                                      |<-   CNR + 1  ->|  CNR + 1 = 99 + 1 CLKs
                                               |<CMR+1>|  CMR + 1 = 39 + 1 CLKs

      __                ______________          _______
        |______200_____|     200      |____60__|   40  |_____BPWM waveform

    */


    /*
      Configure BPWM0 channel 0 init period and duty.
      Period is PCLK / (prescaler * clock divider * (CNR + 1))
      Duty ratio = (CMR + 1) / (CNR + 1)
      Period = 96 MHz / (2 * 1 * (199 + 1)) =  240000 Hz
      Duty ratio = (99 + 1) / (199 + 1) = 50%
    */
    // BPWM0 channel 0 frequency is 240000Hz, duty 50%,
    BPWM_ConfigOutputChannel(BPWM0, 0, 240000, 50);

    // Enable output of BPWM0 channel 0
    BPWM_EnableOutput(BPWM0, BPWM_CH_0_MASK);

    // Enable BPWM0 channel 0 period interrupt, use channel 0 to measure time.
    BPWM_EnablePeriodInt(BPWM0, 0, 0);
    NVIC_EnableIRQ(BPWM0_IRQn);

    // Start
    BPWM_Start(BPWM0, BPWM_CH_0_MASK);

    while(1);

}


/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
