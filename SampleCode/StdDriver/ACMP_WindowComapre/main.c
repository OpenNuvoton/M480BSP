/*************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Demonstrate the usage of ACMP window compare function
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"


void ACMP01_IRQHandler(void)
{
    /* Clear interrupt flag */
    ACMP_CLR_INT_FLAG(ACMP01, 0);
    ACMP_CLR_INT_FLAG(ACMP01, 1);

    if(ACMP01->STATUS & ACMP_STATUS_ACMPWO_Msk)
    {
        printf("The input voltage is within the window\n");
    }
    else
    {
        printf("The input voltage is not within the window\n");
    }
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

    /* Set PA.11 and PB.4 to input mode */
    PA->MODE &= ~GPIO_MODE_MODE11_Msk;
    PB->MODE &= ~GPIO_MODE_MODE4_Msk;

    /* Set PA11 multi-function pin for ACMP0 positive input pin */
    SYS->GPA_MFPH |= SYS_GPA_MFPH_PA11MFP_ACMP0_P0;

    /* Set PB4 multi-function pin for ACMP1 positive input pin */
    SYS->GPB_MFPL |= SYS_GPB_MFPL_PB4MFP_ACMP1_P1;

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Disable digital input path of analog pin ACMP0_P0 and ACMP1_P1 to prevent leakage */
    GPIO_DISABLE_DIGITAL_PATH(PA, (1ul << 11));
    GPIO_DISABLE_DIGITAL_PATH(PB, (1ul << 4));
}


int32_t main(void)
{
    uint32_t volatile i;

    /* Unlock protected registers */
    SYS_UnlockReg();
    /* Init System, IP clock and multi-function I/O. */
    SYS_Init();
    /* Lock protected registers */
    SYS_LockReg();

    /* Configure UART0: 115200, 8-bit word, no parity bit, 1 stop bit. */
    UART_Open(UART0, 115200);

    printf("\nThis sample code demonstrates ACMP window compare function\n");
    printf("Connect the specific analog voltage source to the positive inputs\n");
    printf("of both comparators, PA11 and PB4. This sample code will monitor if the\n");
    printf("input is between the range of VDDA * 9 / 24 and bandgap.\n");
    printf("Press any key to continue ...");
    getchar();
    printf("\n");

    /* Select VDDA as CRV source */
    ACMP_SELECT_CRV_SRC(ACMP01, ACMP_VREF_CRVSSEL_VDDA);
    /* Select CRV level: VDDA * 9 / 24 */
    ACMP_CRV_SEL(ACMP01, 5);
    /* Configure ACMP0. Enable ACMP0 and select CRV as the source of ACMP negative input. */
    ACMP_Open(ACMP01, 0, ACMP_CTL_NEGSEL_CRV, ACMP_CTL_HYSTERESIS_DISABLE);
    /* Configure ACMP1. Enable ACMP1 and select CRV as the source of ACMP negative input. */
    ACMP_Open(ACMP01, 1, ACMP_CTL_NEGSEL_VBG, ACMP_CTL_HYSTERESIS_DISABLE);
    /* Select P1 as ACMP1 positive input channel */
    ACMP_SELECT_P(ACMP01, 1, ACMP_CTL_POSSEL_P1);
    /* Enable window compare mode */
    ACMP_ENABLE_WINDOW_COMPARE(ACMP01, 0);
    ACMP_ENABLE_WINDOW_COMPARE(ACMP01, 1);

    /* Clear ACMP 0 and 1 interrupt flag */
    ACMP_CLR_INT_FLAG(ACMP01, 0);
    ACMP_CLR_INT_FLAG(ACMP01, 1);

    // Give ACMP some time to settle
    for(i = 0; i < 1000; i++);

    if(ACMP01->STATUS & ACMP_STATUS_ACMPWO_Msk)
    {
        printf("The input voltage in inside the window\n");
    }
    else
    {
        printf("The input voltage in outside the window\n");
    }

    /* Enable interrupt */
    ACMP_ENABLE_INT(ACMP01, 0);
    ACMP_ENABLE_INT(ACMP01, 1);
    /* Enable ACMP01 interrupt */
    NVIC_EnableIRQ(ACMP01_IRQn);

    while(1);

}
/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/


