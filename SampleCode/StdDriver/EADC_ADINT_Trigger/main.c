/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Use ADINT interrupt to do the EADC continuous scan conversion.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK       144000000

/*---------------------------------------------------------------------------------------------------------*/
/* Define global variables and constants                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
volatile uint32_t g_u32AdcIntFlag, g_u32COVNUMFlag = 0;

/*---------------------------------------------------------------------------------------------------------*/
/* Define functions prototype                                                                              */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void);
void EADC_FunctionTest(void);

/*---------------------------------------------------------------------------------------------------------*/
/* EADC interrupt handler                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/
void ADC00_IRQHandler(void)
{
    g_u32AdcIntFlag = 1;
    EADC_CLR_INT_FLAG(EADC, EADC_STATUS2_ADIF0_Msk);      /* Clear the A/D ADINT0 interrupt flag */
}

void SYS_Init(void)
{

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Enable HXT clock (external XTAL 12MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);

    /* Set PCLK0 = PCLK1 = HCLK/2 */
    CLK->PCLKDIV = (CLK_PCLKDIV_PCLK0DIV2 | CLK_PCLKDIV_PCLK1DIV2);

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable EADC module clock */
    CLK_EnableModuleClock(EADC_MODULE);

    /* EADC clock source is 72MHz, set divider to 1, EADC clock is 72 MHz */
    CLK_SetModuleClock(EADC_MODULE, 0, CLK_CLKDIV0_EADC(1));

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Set PD multi-function pins for UART0 RXD(PD.2) and TXD(PD.3) */
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD2MFP_Msk | SYS_GPD_MFPL_PD3MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD2MFP_UART0_RXD | SYS_GPD_MFPL_PD3MFP_UART0_TXD);

    /* Configure the GPB10 - GPB13 ADC analog input pins (fast channel).  */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB10MFP_Msk | SYS_GPB_MFPH_PB11MFP_Msk |
                       SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB10MFP_EADC0_CH10 | SYS_GPB_MFPH_PB11MFP_EADC0_CH11 |
                      SYS_GPB_MFPH_PB12MFP_EADC0_CH12 | SYS_GPB_MFPH_PB13MFP_EADC0_CH13);

    /* Disable the GPB0 - GPB3 digital input path to avoid the leakage current. */
    GPIO_DISABLE_DIGITAL_PATH(PB, BIT3|BIT2|BIT1|BIT0);

}

void UART0_Init()
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

/*---------------------------------------------------------------------------------------------------------*/
/* EADC function test                                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
void EADC_FunctionTest()
{
    uint8_t  u8Option, u32SAMPLECount = 0;
    int32_t  i32ConversionData[8] = {0};

    /* The Maximum EADC clock frequence is 72 MHz.
     * Hence, we set PLL to 144 MHz, HCLK 144 MHz and PCLK to 72 MHz.
     * EADC clock source is from PCLK = 72 MHz.
     */
    printf("\n");
    printf("+----------------------------------------------------------------------+\n");
    printf("|                      ADINT trigger mode test                         |\n");
    printf("+----------------------------------------------------------------------+\n");

    printf("\nIn this test, software will get conversion result from fast channels.\n");

    while(1) {
        printf("\n\nSelect input mode:\n");
        printf("  [1] Single end input (channel 10, 11, 12 and 13)\n");
        printf("  [2] Differential input (input channel pair 10 and 11)\n");
        printf("  Other keys: exit continuous scan mode test\n");
        u8Option = getchar();
        if(u8Option == '1') {
            /* Set input mode as single-end and enable the A/D converter */
            EADC_Open(EADC, EADC_CTL_DIFFEN_SINGLE_END);

            /* Configure the sample 4 module for analog input channel 10 and enable ADINT0 trigger source */
            EADC_ConfigSampleModule(EADC, 4, EADC_ADINT0_TRIGGER, 10);
            /* Configure the sample 5 module for analog input channel 11 and enable ADINT0 trigger source */
            EADC_ConfigSampleModule(EADC, 5, EADC_ADINT0_TRIGGER, 11);
            /* Configure the sample 6 module for analog input channel 12 and enable ADINT0 trigger source */
            EADC_ConfigSampleModule(EADC, 6, EADC_ADINT0_TRIGGER, 12);
            /* Configure the sample 7 module for analog input channel 13 and enable ADINT0 trigger source */
            EADC_ConfigSampleModule(EADC, 7, EADC_ADINT0_TRIGGER, 13);

            /* Clear the A/D ADINT0 interrupt flag for safe */
            EADC_CLR_INT_FLAG(EADC, EADC_STATUS2_ADIF0_Msk);

            /* Enable the sample module 7 interrupt */
            EADC_ENABLE_INT(EADC, BIT0);//Enable sample module  A/D ADINT0 interrupt.
            EADC_ENABLE_SAMPLE_MODULE_INT(EADC, 0, BIT7);//Enable sample module 7 interrupt.
            NVIC_EnableIRQ(ADC0_IRQn);

            /* Reset the ADC indicator and trigger sample module 7 to start A/D conversion */
            g_u32AdcIntFlag = 0;
            g_u32COVNUMFlag = 0;
            EADC_START_CONV(EADC, BIT7);

            __WFI();

            /* Disable the sample module 7 interrupt */
            EADC_DISABLE_SAMPLE_MODULE_INT(EADC, 0, BIT7);

            /* Wait conversion done */
            while(EADC_GET_DATA_VALID_FLAG(EADC, (BIT7|BIT6|BIT5|BIT4)) != (BIT7|BIT6|BIT5|BIT4));

            /* Get the conversion result of the sample module */
            for(u32SAMPLECount = 0; u32SAMPLECount < 4; u32SAMPLECount++)
                i32ConversionData[u32SAMPLECount] = EADC_GET_CONV_DATA(EADC, (u32SAMPLECount + 4));

            for(g_u32COVNUMFlag = 0; (g_u32COVNUMFlag) < 4; g_u32COVNUMFlag++)
                printf("Conversion result of channel %d: 0x%X (%d)\n", (g_u32COVNUMFlag + 10), i32ConversionData[g_u32COVNUMFlag], i32ConversionData[g_u32COVNUMFlag]);

        } else if(u8Option == '2') {
            /* Set input mode as differential and enable the A/D converter */
            EADC_Open(EADC, EADC_CTL_DIFFEN_DIFFERENTIAL);

            /* Configure the sample module 4 for analog input channel 10 and enable ADINT0 trigger source */
            EADC_ConfigSampleModule(EADC, 4, EADC_ADINT0_TRIGGER, 10);
            /* Configure the sample module 5 for analog input channel 11 and enable ADINT0 trigger source */
            EADC_ConfigSampleModule(EADC, 5, EADC_ADINT0_TRIGGER, 11);
            /* Configure the sample module 6 for analog input channel 12 and enable ADINT0 trigger source */
            EADC_ConfigSampleModule(EADC, 6, EADC_ADINT0_TRIGGER, 12);
            /* Configure the sample module 7 for analog input channel 13 and enable ADINT0 trigger source */
            EADC_ConfigSampleModule(EADC, 7, EADC_ADINT0_TRIGGER, 13);

            /* Clear the A/D ADINT0 interrupt flag for safe */
            EADC_CLR_INT_FLAG(EADC, EADC_STATUS2_ADIF0_Msk);

            /* Enable the sample module 7 interrupt */
            EADC_ENABLE_INT(EADC, BIT0);//Enable sample module A/D ADINT0 interrupt.
            EADC_ENABLE_SAMPLE_MODULE_INT(EADC, 0, BIT7);//Enable sample module 7 interrupt.
            NVIC_EnableIRQ(ADC0_IRQn);

            /* Reset the ADC indicator and trigger sample module 7 to start A/D conversion */
            g_u32AdcIntFlag = 0;
            g_u32COVNUMFlag = 0;
            EADC_START_CONV(EADC, BIT7);

            __WFI();

            /* Disable the sample module 7 interrupt */
            EADC_DISABLE_SAMPLE_MODULE_INT(EADC, 0, BIT7);

            /* Wait conversion done */
            while(EADC_GET_DATA_VALID_FLAG(EADC, (BIT7|BIT6|BIT5|BIT4)) != (BIT7|BIT6|BIT5|BIT4));

            /* Get the conversion result of the sample module */
            for(u32SAMPLECount = 0; u32SAMPLECount < 4; u32SAMPLECount++)
                i32ConversionData[u32SAMPLECount] = EADC_GET_CONV_DATA(EADC, (u32SAMPLECount + 4));

            for(g_u32COVNUMFlag = 0; (g_u32COVNUMFlag) < 4; g_u32COVNUMFlag++)
                printf("Conversion result of channel %d: 0x%X (%d)\n", (g_u32COVNUMFlag + 10), i32ConversionData[g_u32COVNUMFlag], i32ConversionData[g_u32COVNUMFlag]);

        } else
            return ;

    }
}


/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
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

    /*---------------------------------------------------------------------------------------------------------*/
    /* SAMPLE CODE                                                                                             */
    /*---------------------------------------------------------------------------------------------------------*/

    printf("\nSystem clock rate: %d Hz", SystemCoreClock);

    /* EADC function test */
    EADC_FunctionTest();

    /* Disable EADC IP clock */
    CLK_DisableModuleClock(EADC_MODULE);

    /* Disable External Interrupt */
    NVIC_DisableIRQ(ADC0_IRQn);

    printf("Exit EADC sample code\n");

    while(1);

}


/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
