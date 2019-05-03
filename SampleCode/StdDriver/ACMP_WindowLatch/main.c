/*************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Demonstrate the usage of ACMP window latch function.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"


void ACMP01_IRQHandler(void)
{
    static uint32_t u32Cnt = 0;

    /* Clear ACMP 1 interrupt flag */
    ACMP_CLR_INT_FLAG(ACMP01, 1);
    /* Check Comparator 1 Output Status */
    if(ACMP_GET_OUTPUT(ACMP01, 1))
        printf("ACMP1_P voltage > Band-gap voltage (%d)\n", u32Cnt);
    else
        printf("ACMP1_P voltage <= Band-gap voltage (%d)\n", u32Cnt);

    u32Cnt++;
}


void SYS_Init(void)
{
    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable external 12MHz XTAL */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable UART peripheral clock */
    CLK_EnableModuleClock(UART0_MODULE);
    /* Enable ACMP01 peripheral clock */
    CLK_EnableModuleClock(ACMP01_MODULE);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock and CyclesPerUs automatically. */
    SystemCoreClockUpdate();

    /* Set PA6 multi-function pin for ACMP1 window latch pin */
    SYS->GPA_MFPL |= SYS_GPA_MFPL_PA6MFP_ACMP1_WLAT;
    /* Set PB.4 and PB.6 to input mode */
    PB->MODE &= ~(GPIO_MODE_MODE4_Msk | GPIO_MODE_MODE6_Msk);
    /* Set PB4 multi-function pin for ACMP1 positive input pin and PB6 multi-function pin for ACMP1 output pin */
    SYS->GPB_MFPL |= SYS_GPB_MFPL_PB4MFP_ACMP1_P1 | SYS_GPB_MFPL_PB6MFP_ACMP1_O;

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Disable digital input path of analog pin ACMP1_P1 to prevent leakage */
    GPIO_DISABLE_DIGITAL_PATH(PB, (1ul << 4));
}

/*
 * In window latch mode and window latch pin is at high level, the voltage of the positive
 * input is greater than the  voltage of the negative input, the analog comparator outputs
 * logical one; otherwise, it outputs logical zero. When window latch pin is at low level,
 * the output level does not change no matter how positive  input voltage changes.
 */

int32_t main(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();
    /* Init System, IP clock and multi-function I/O. */
    SYS_Init();
    /* Lock protected registers */
    SYS_LockReg();

    /* Configure UART0: 115200, 8-bit word, no parity bit, 1 stop bit. */
    UART_Open(UART0, 115200);

    printf("\nThis sample code demonstrates ACMP1 window latch function. Using ACMP1_P1 (PB4) as ACMP1\n");
    printf("positive input and using internal band-gap voltage as the negative input. ACMP1_WLAT is at\n");
    printf("PA6, when PA6 is low, compare result on ACMP1_O (PB6) does not change with ACMP1_P1. When PA6");
    printf("is high, ACMP1_O works as usual\n");

    printf("Press any key to start ...");
    getchar();
    /* Configure ACMP1. Enable ACMP1 and select band-gap voltage as the source of ACMP negative input. */
    ACMP_Open(ACMP01, 1, ACMP_CTL_NEGSEL_VBG, ACMP_CTL_HYSTERESIS_DISABLE);
    /* Select P1 as ACMP positive input channel */
    ACMP_SELECT_P(ACMP01, 1, ACMP_CTL_POSSEL_P1);
    /* Enable interrupt */
    ACMP_ENABLE_INT(ACMP01, 1);
    /* Enable window latch mode */
    ACMP_ENABLE_WINDOW_LATCH(ACMP01, 1);

    /* Enable ACMP01 interrupt */
    NVIC_EnableIRQ(ACMP01_IRQn);

    while(1);

}
/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/


