/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Demonstrate EADC0 and EADC1 are triggered in simultaneous mode.
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK       160000000

/*---------------------------------------------------------------------------------------------------------*/
/* Define global variables and constants                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
volatile uint32_t g_u32AdcIntFlag, g_u32COVNUMFlag = 0;


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

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable EADC module clock */
    CLK_EnableModuleClock(EADC_MODULE);
    CLK_EnableModuleClock(EADC1_MODULE);

    /* EADC clock source is PCLK, that is 80MHz */
    CLK_SetModuleClock(EADC_MODULE, 0, CLK_CLKDIV0_EADC(1));
    CLK_SetModuleClock(EADC1_MODULE, 0, CLK_CLKDIV2_EADC1(1));

    /* Enable Timer 0 module clock */
    CLK_EnableModuleClock(TMR0_MODULE);

    /* Select timer 0 module clock source as HXT */
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HXT, 0);

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);
    /* Set PB.0 ~ PB.3 to input mode */
    PB->MODE &= ~(GPIO_MODE_MODE0_Msk | GPIO_MODE_MODE1_Msk | GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);
    /* Configure the GPB0 - GPB3 EADC0 analog input pins.  */
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB0MFP_Msk | SYS_GPB_MFPL_PB1MFP_Msk |
                       SYS_GPB_MFPL_PB2MFP_Msk | SYS_GPB_MFPL_PB3MFP_Msk);
    SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB0MFP_EADC0_CH0 | SYS_GPB_MFPL_PB1MFP_EADC0_CH1 |
                      SYS_GPB_MFPL_PB2MFP_EADC0_CH2 | SYS_GPB_MFPL_PB3MFP_EADC0_CH3);

    /* Configure the GPD10 - GPD12, GPC13 EADC1 analog input pins.  */
    SYS->GPD_MFPH &= ~(SYS_GPD_MFPH_PD10MFP_Msk | SYS_GPD_MFPH_PD11MFP_Msk |
                       SYS_GPD_MFPH_PD12MFP_Msk);
    SYS->GPD_MFPH |= (SYS_GPD_MFPH_PD10MFP_EADC1_CH0 | SYS_GPD_MFPH_PD11MFP_EADC1_CH1 |
                      SYS_GPD_MFPH_PD12MFP_EADC1_CH2);
    SYS->GPC_MFPH &= ~SYS_GPC_MFPH_PC13MFP_Msk;
    SYS->GPC_MFPH |= SYS_GPC_MFPH_PC13MFP_EADC1_CH3;

    /* Disable the GPB0 - GPB3, GPC13, GPD10 - GPD12 digital input path to avoid the leakage current. */
    GPIO_DISABLE_DIGITAL_PATH(PB, BIT3|BIT2|BIT1|BIT0);
    GPIO_DISABLE_DIGITAL_PATH(PC, BIT13);
    GPIO_DISABLE_DIGITAL_PATH(PD, BIT10|BIT11|BIT12);
}

void UART0_Init()
{
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

void TIMER0_Init()
{

    /* Set timer0 periodic time-out period is 3us if timer clock is 12 MHz */
    TIMER_SET_CMP_VALUE(TIMER0, 36);//TIMER0->CMP = 36;

    /* Start timer counter in periodic mode and enable timer interrupt trigger EADC */
    TIMER0->CTL = TIMER_PERIODIC_MODE;
    TIMER0->TRGCTL |= TIMER_TRGCTL_TRGEADC_Msk;

}

void EADC_FunctionTest()
{
    int32_t  i32ConversionData[6] = {0};
    int32_t  i32ConversionData1[6] = {0};

    printf("\n");
    printf("+----------------------------------------------------------------------+\n");
    printf("|                      Simultaneous mode test                          |\n");
    printf("+----------------------------------------------------------------------+\n");

    printf("\nIn this test, both EADC0 and EADC1 trigger source are Timer0.\n");

    /* Set input mode as single-end and enable the A/D converter */
    EADC_Open(EADC, EADC_CTL_DIFFEN_SINGLE_END);
    EADC_Open(EADC1, EADC_CTL_DIFFEN_SINGLE_END);

    /* Configure EADC0 sample module 0 for analog input channel 2 and enable Timer0 trigger source */
    EADC_ConfigSampleModule(EADC, 0, EADC_TIMER0_TRIGGER, 2);
    /* Configure EADC1 sample module 1 for analog input channel 2 and enable Timer0 trigger source */
    EADC_ConfigSampleModule(EADC1, 1, EADC_TIMER0_TRIGGER, 2);

    /* Clear the A/D ADINT0 interrupt flag for safe */
    EADC_CLR_INT_FLAG(EADC, EADC_STATUS2_ADIF0_Msk);

    /* Enable the sample module 0 interrupt.  */
    EADC_ENABLE_INT(EADC, BIT0);//Enable sample module A/D ADINT0 interrupt.
    EADC_ENABLE_SAMPLE_MODULE_INT(EADC, 0, BIT0);//Enable sample module 0 interrupt.
    NVIC_EnableIRQ(EADC00_IRQn);

    printf("Conversion result of channel 2:\n");

    /* Reset the ADC indicator and enable Timer0 counter */
    g_u32AdcIntFlag = 0;
    g_u32COVNUMFlag = 0;
    TIMER_Start(TIMER0);

    while(1)
    {
        /* Wait ADC interrupt (g_u32AdcIntFlag will be set at IRQ_Handler function) */
        while(g_u32AdcIntFlag == 0);

        /* Reset the EADC interrupt indicator */
        g_u32AdcIntFlag = 0;

        /* Get the conversion result of EADC0 sample module 0 */
        i32ConversionData[g_u32COVNUMFlag - 1] = EADC_GET_CONV_DATA(EADC, 0);
        /* Get the conversion result of EADC1 sample module 1 */
        i32ConversionData1[g_u32COVNUMFlag - 1] = EADC_GET_CONV_DATA(EADC1, 1);

        if(g_u32COVNUMFlag == 6)
            break;
    }

    /* Disable Timer0 counter */
    TIMER_Stop(TIMER0);

    /* Disable the ADINT0 interrupt */
    EADC_DISABLE_INT(EADC, BIT0);

    printf("EADC0:\n");
    for(g_u32COVNUMFlag = 0; (g_u32COVNUMFlag) < 6; g_u32COVNUMFlag++)
        printf("                                0x%X (%d)\n", i32ConversionData[g_u32COVNUMFlag], i32ConversionData[g_u32COVNUMFlag]);
    printf("EADC1:\n");
    for(g_u32COVNUMFlag = 0; (g_u32COVNUMFlag) < 6; g_u32COVNUMFlag++)
        printf("                                0x%X (%d)\n", i32ConversionData1[g_u32COVNUMFlag], i32ConversionData1[g_u32COVNUMFlag]);

}

void EADC00_IRQHandler(void)
{
    EADC_CLR_INT_FLAG(EADC, EADC_STATUS2_ADIF0_Msk);/* Clear the A/D ADINT0 interrupt flag */
    g_u32AdcIntFlag = 1;
    g_u32COVNUMFlag++;
}

int32_t main(void)
{

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    /* Init TIMER0 for EADC */
    TIMER0_Init();

    printf("\nSystem clock rate: %d Hz", SystemCoreClock);

    /* EADC function test */
    EADC_FunctionTest();
    /* Disable Timer0 IP clock */
    CLK_DisableModuleClock(TMR0_MODULE);

    /* Disable EADC IP clock */
    CLK_DisableModuleClock(EADC_MODULE);
    CLK_DisableModuleClock(EADC1_MODULE);

    /* Disable External Interrupt */
    NVIC_DisableIRQ(EADC00_IRQn);

    printf("Exit EADC sample code\n");

    while(1);

}

/*** (C) COPYRIGHT 2019 Nuvoton Technology Corp. ***/
