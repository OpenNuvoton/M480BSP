/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Demonstrate how to use EPWM brake function.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK       192000000


/**
 * @brief       EPWM0 Brake0 IRQ Handler
 *
 * @param       None
 *
 * @return      None
 *
 * @details     ISR to handle EPWM0 Brake0 interrupt event
 */
void BRAKE0_IRQHandler(void)
{
    printf("\nFault brake!\n");
    printf("Press any key to unlock brake state. (EPWM0 channel 0 output will toggle again)\n");
    getchar();

    /* Unlock protected registers */
    SYS_UnlockReg();
    // Clear brake interrupt flag
    EPWM_ClearFaultBrakeIntFlag(EPWM0, EPWM_FB_EDGE);
    /* Lock protected registers */
    SYS_LockReg();
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

    /* Set B7 multi-function pin for EPWM1 brake pin 0 */
    SYS->GPB_MFPL =  (SYS->GPB_MFPL & ~SYS_GPB_MFPL_PB7MFP_Msk) | SYS_GPB_MFPL_PB7MFP_EPWM1_BRAKE0;
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

    printf("\nConnect PB.7 (EPWM1 brake pin 0) to PD.0.\n");
    printf("It will generate brake interrupt and EPWM0 channel 0 output stop toggling.\n");

    GPIO_SetMode(PD, BIT0, GPIO_MODE_OUTPUT);
    PD0 = 0;

    // EPWM0 frequency is 100Hz, duty 30%,
    EPWM_ConfigOutputChannel(EPWM0, 0, 100, 30);

    // Enable output of all EPWM channels
    EPWM_EnableOutput(EPWM0, BIT5|BIT4|BIT3|BIT2|BIT1|BIT0);

    /* Unlock protected registers */
    SYS_UnlockReg();
    // Enable brake and interrupt
    EPWM_EnableFaultBrake (EPWM0, EPWM_CH_0_MASK, 1, EPWM_FB_EDGE_BKP0);
    // Set Brake pin to EPWM1_BRAKE0
    EPWM_SetBrakePinSource(EPWM0, 0, 1);
    EPWM_EnableFaultBrakeInt (EPWM0, 0);
    // Enable brake noise filter : brake pin 0, filter count=7, filter clock=HCLK/128
    EPWM_EnableBrakeNoiseFilter(EPWM0, 0, 7, EPWM_NF_CLK_DIV_128);
    // Clear brake interrupt flag
    EPWM_ClearFaultBrakeIntFlag(EPWM0, EPWM_FB_EDGE);
    /* Lock protected registers */
    SYS_LockReg();

    NVIC_ClearPendingIRQ(BRAKE0_IRQn);
    NVIC_EnableIRQ(BRAKE0_IRQn);

    // Start
    EPWM_Start(EPWM0, 1);

    printf("\nPress any key to generate a brake event\n");
    getchar();
    PD0 = 1;

    while(1);
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
