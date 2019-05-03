/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Demonstrate how to use EPWM Dead Zone function.
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
    static uint32_t cnt;
    static uint32_t out;

    // Channel 0 frequency is 100Hz, every 1 second enter this IRQ handler 100 times.
    if(++cnt == 100)
    {
        if(out)
            EPWM_EnableOutput(EPWM0, EPWM_CH_0_MASK | EPWM_CH_1_MASK | EPWM_CH_2_MASK | EPWM_CH_3_MASK);
        else
            EPWM_DisableOutput(EPWM0, EPWM_CH_0_MASK | EPWM_CH_1_MASK | EPWM_CH_2_MASK | EPWM_CH_3_MASK);
        out ^= 1;
        cnt = 0;
    }
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

int main(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    printf("\n\nCPU @ %dHz(PLL@ %dHz)\n", SystemCoreClock, PllClock);
    printf("EPWM0 clock is from %s\n", (CLK->CLKSEL2 & CLK_CLKSEL2_EPWM0SEL_Msk) ? "CPU" : "PLL");
    printf("+------------------------------------------------------------------------+\n");
    printf("|                          EPWM Driver Sample Code                        |\n");
    printf("|                                                                        |\n");
    printf("+------------------------------------------------------------------------+\n");
    printf("  This sample code will output EPWM0 channel 0~3 with different\n");
    printf("  frequency and duty, enable dead zone function of all EPWM0 pairs.\n");
    printf("  And also enable/disable EPWM output every 1 second.\n");
    printf("  I/O configuration:\n");
    printf("    waveform output pin: EPWM0_CH0(PA.5), EPWM0_CH1(PA.4), EPWM0_CH2(PA.3), EPWM0_CH3(PA.2)\n");

    /*Set Pwm mode as complementary mode*/
    EPWM_ENABLE_COMPLEMENTARY_MODE(EPWM0);

    // EPWM0 channel 0 frequency is 10000Hz, duty 30%,
    EPWM_ConfigOutputChannel(EPWM0, 0, 10000, 30);
    SYS_UnlockReg();
    EPWM_EnableDeadZone(EPWM0, 0, 400);
    SYS_LockReg();

    // EPWM0 channel 2 frequency is 30000Hz, duty 50%
    EPWM_ConfigOutputChannel(EPWM0, 2, 30000, 50);
    SYS_UnlockReg();
    EPWM_EnableDeadZone(EPWM0, 2, 200);
    SYS_LockReg();

    // Enable output of EPWM0 channel 0~3
    EPWM_EnableOutput(EPWM0, BIT3|BIT2|BIT1|BIT0);

    // Enable EPWM0 channel 0 period interrupt, use channel 0 to measure time.
    EPWM_EnablePeriodInt(EPWM0, 0, 0);
    NVIC_EnableIRQ(EPWM0P0_IRQn);

    // Start
    EPWM_Start(EPWM0, BIT3|BIT2|BIT1|BIT0);

    while(1);
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
