/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Change duty cycle and period of output waveform by EPWM Double Buffer function.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK       192000000


/**
 * @brief       EPWM0 IRQ Handler
 *
 * @param       None
 *
 * @return      None
 *
 * @details     ISR to handle EPWM0 interrupt event
 */
void EPWM0P0_IRQHandler(void)
{
    static int toggle = 0;

    // Update EPWM0 channel 0 period and duty
    if(toggle == 0)
    {
        EPWM_SET_CNR(EPWM0, 0, 99);
        EPWM_SET_CMR(EPWM0, 0, 39);
    }
    else
    {
        EPWM_SET_CNR(EPWM0, 0, 399);
        EPWM_SET_CMR(EPWM0, 0, 199);
    }
    toggle ^= 1;
    // Clear channel 0 period interrupt flag
    EPWM_ClearPeriodIntFlag(EPWM0, 0);
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

    /* Enable IP module clock */
    CLK_EnableModuleClock(EPWM0_MODULE);

    /* EPWM clock frequency is set double to PCLK: select EPWM module clock source as PLL */
    CLK_SetModuleClock(EPWM0_MODULE, CLK_CLKSEL2_EPWM0SEL_PLL, (uint32_t)NULL);

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set PA multi-function pins for EPWM0 Channel 0,1,2,3 */
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA5MFP_Msk | SYS_GPA_MFPL_PA4MFP_Msk | SYS_GPA_MFPL_PA3MFP_Msk | SYS_GPA_MFPL_PA2MFP_Msk);
    SYS->GPA_MFPL |= (SYS_GPA_MFPL_PA5MFP_EPWM0_CH0 | SYS_GPA_MFPL_PA4MFP_EPWM0_CH1 | SYS_GPA_MFPL_PA3MFP_EPWM0_CH2 | SYS_GPA_MFPL_PA2MFP_EPWM0_CH3);
}

void UART0_Init()
{
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

int32_t main(void)
{
    /* Init System, IP clock and multi-function I/O
       In the end of SYS_Init() will issue SYS_LockReg()
       to lock protected register. If user want to write
       protected register, please issue SYS_UnlockReg()
       to unlock protected register if necessary */

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART to 115200-8n1 for print message */
    UART0_Init();

    printf("\n\nCPU @ %dHz(PLL@ %dHz)\n", SystemCoreClock, PllClock);
    printf("EPWM0 clock is from %s\n", (CLK->CLKSEL2 & CLK_CLKSEL2_EPWM0SEL_Msk) ? "CPU" : "PLL");
    printf("+------------------------------------------------------------------------+\n");
    printf("|                          EPWM Driver Sample Code                        |\n");
    printf("|                                                                        |\n");
    printf("+------------------------------------------------------------------------+\n");
    printf("  This sample code will use EPWM0 channel 0 to output waveform\n");
    printf("  I/O configuration:\n");
    printf("    waveform output pin: EPWM0 channel 0(PA.5)\n");
    printf("\nUse double buffer feature.\n");

    /*
        EPWM0 channel 0 waveform of this sample shown below:

        |<-        CNR + 1  clk     ->|  CNR + 1 = 399 + 1 CLKs
                       |<-CMR+1 clk ->|  CMR + 1 = 199 + 1 CLKs
                                      |<-   CNR + 1  ->|  CNR + 1 = 99 + 1 CLKs
                                               |<CMR+1>|  CMR + 1 = 39 + 1 CLKs
      __                ______________          _______
        |______200_____|     200      |____60__|   40  |_____EPWM waveform

    */


    /*
      Configure EPWM0 channel 0 init period and duty.
      Period is PLL / (prescaler * (CNR + 1))
      Duty ratio = (CMR + 1) / (CNR + 1)
      Period = 192 MHz / (4 * (199 + 1)) = 240000 Hz
      Duty ratio = (99 + 1) / (199 + 1) = 50%
    */
    // EPWM0 channel 0 frequency is 240000Hz, duty 50%,
    EPWM_ConfigOutputChannel(EPWM0, 0, 240000, 50);

    // Enable output of EPWM0 channel 0
    EPWM_EnableOutput(EPWM0, EPWM_CH_0_MASK);

    // Enable EPWM0 channel 0 period interrupt, use channel 0 to measure time.
    EPWM_EnablePeriodInt(EPWM0, 0, 0);
    NVIC_EnableIRQ(EPWM0P0_IRQn);

    // Start
    EPWM_Start(EPWM0, EPWM_CH_0_MASK);

    while(1);

}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
