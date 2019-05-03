/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Show how to control OPA.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK       192000000

void OPA0_IRQHandler (void)
{
    static uint32_t u32Cnt = 0;

    /* Clear OPA0 interrupt flag */
    OPA_CLR_INT_FLAG(OPA, 0);
    /* Check OPA0 digital output state */
    if(OPA_GET_DIGITAL_OUTPUT(OPA, 0))
        printf("OP0_P voltage > OP0_N voltage (%d)\n", u32Cnt);
    else
        printf("OP0_P voltage <= OP0_N voltage (%d)\n", u32Cnt);

    u32Cnt++;
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
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(OPA_MODULE);

    /* Peripheral clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    //Set I/O multi-function pins to OPA and input mode
    //PB0: OP0_P
    //PB1: OP0_N
    //PB2: OP0_O
    //PA8: OP1_P
    //PA9: OP1_N
    //PA10: OP1_O
    //PD10: OP2_P
    //PD11: OP2_N
    //PD12: OP2_O
    PA->MODE &= ~(GPIO_MODE_MODE8_Msk | GPIO_MODE_MODE9_Msk | GPIO_MODE_MODE10_Msk);
    PB->MODE &= ~(GPIO_MODE_MODE0_Msk | GPIO_MODE_MODE1_Msk | GPIO_MODE_MODE2_Msk);
    PD->MODE &= ~(GPIO_MODE_MODE10_Msk | GPIO_MODE_MODE11_Msk | GPIO_MODE_MODE12_Msk);
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB0MFP_Msk | SYS_GPB_MFPL_PB1MFP_Msk | SYS_GPB_MFPL_PB2MFP_Msk);
    SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB0MFP_OPA0_P | SYS_GPB_MFPL_PB1MFP_OPA0_N | SYS_GPB_MFPL_PB2MFP_OPA0_O);
    SYS->GPA_MFPH &= ~((SYS_GPA_MFPH_PA8MFP_Msk) | (SYS_GPA_MFPH_PA9MFP_Msk) | (SYS_GPA_MFPH_PA10MFP_Msk));
    SYS->GPA_MFPH |= (SYS_GPA_MFPH_PA8MFP_OPA1_P) | (SYS_GPA_MFPH_PA9MFP_OPA1_N) | (SYS_GPA_MFPH_PA10MFP_OPA1_O);
    SYS->GPD_MFPH &= ~((SYS_GPD_MFPH_PD10MFP_Msk) | (SYS_GPD_MFPH_PD11MFP_Msk) | (SYS_GPD_MFPH_PD12MFP_Msk));
    SYS->GPD_MFPH |= (SYS_GPD_MFPH_PD10MFP_OPA2_P) | (SYS_GPD_MFPH_PD11MFP_OPA2_N) | (SYS_GPD_MFPH_PD12MFP_OPA2_O);
}

void UART0_Init()
{
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

int main(void)
{
    int32_t i32CalResult;
    uint32_t u32DelayCnt;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    printf("\n\n");
    printf("+---------------------------------------+\n");
    printf("|         M480 OPA Sample Code          |\n");
    printf("+---------------------------------------+\n");

    printf("\nThis sample code demonstrates OPA digital output function. OP0_P (PB.0) is the OPA0\n");
    printf("positive input pin, OP0_N (PB.1) is the negative input and OP0_O (PB.2) is the OPA output pin.\n");

    printf("When the voltage of the positive input is greater than the voltage of the negative input,\n");
    printf("the digital output state, OPDO0 (OPA_STATUS[0]), will be set to 1; otherwise, it will be cleared to 0.\n");
    printf("This sample code will show the relation between the OPA's inputs and show a sequence ");
    printf("number when detecting a transition of OPA's digital output.\n");
    printf("Press any key to start ...");
    getchar();
    printf("\n");

    /* Power on the OPA0 circuit */
    OPA_POWER_ON(OPA, 0);

    /* Enable OPA0 schmitt trigger buffer */
    OPA_ENABLE_SCH_TRIGGER(OPA, 0);

    /* Delay for OPA stable time */
    for(u32DelayCnt = 0; u32DelayCnt < 1500; u32DelayCnt++) __NOP();

    /* Clear OPA0 interrupt flag */
    OPA_CLR_INT_FLAG(OPA, 0);

    /* Enable OPA0 interrupt function */
    OPA_ENABLE_INT(OPA, 0);

    /* Enable OPA interrupt */
    NVIC_EnableIRQ(OPA_IRQn);

    /* Start OPA0 calibration */
    i32CalResult = OPA_Calibration(OPA, 0, OPA_CALIBRATION_CLK_1K, OPA_CALIBRATION_RV_1_2_AVDD);
    printf("OPA0 calibration result is %d\n",i32CalResult);

    printf("\nPress any key to power down OPA ...");
    getchar();

    /* Power down OPA0 circuit */
    OPA_POWER_DOWN(OPA, 0);

    /* Reset OPA controller */
    OPA_Reset();

    /* Disable clock for OPA controller */
    CLK_DisableModuleClock(OPA_MODULE);

    printf("\nPower down OPA successfully!\n");

    while(1);
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
