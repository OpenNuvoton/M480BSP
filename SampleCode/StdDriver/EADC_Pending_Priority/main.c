/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Demonstrate how to trigger multiple sample modules and got conversion results in order of priority.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK       192000000

/*---------------------------------------------------------------------------------------------------------*/
/* Define global variables and constants                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
volatile uint32_t g_u32EadcInt0Flag, g_u32EadcInt1Flag, g_u32EadcInt2Flag, g_u32EadcInt3Flag;

uint32_t g_u32IntModule[4];    /* save the sample module number for ADINT0~3 */
volatile uint32_t g_u32IntSequence[4];  /* save the interrupt sequence for ADINT0~3 */
volatile uint32_t g_u32IntSequenceIndex;



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

    /* EADC clock source is 96MHz, set divider to 8, ADC clock is 96/8 MHz */
    CLK_SetModuleClock(EADC_MODULE, 0, CLK_CLKDIV0_EADC(8));


    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);
    /* Set PB.0, PB.6 ~ PB.9 to input mode */
    PB->MODE &= ~(GPIO_MODE_MODE0_Msk | GPIO_MODE_MODE6_Msk | GPIO_MODE_MODE7_Msk |
                  GPIO_MODE_MODE8_Msk | GPIO_MODE_MODE9_Msk);
    /* Configure the EADC analog input pins.  */
    SYS->GPB_MFPL = (SYS->GPB_MFPL & ~SYS_GPB_MFPL_PB0MFP_Msk) | SYS_GPB_MFPL_PB0MFP_EADC0_CH0;
    SYS->GPB_MFPL = (SYS->GPB_MFPL & ~SYS_GPB_MFPL_PB6MFP_Msk) | SYS_GPB_MFPL_PB6MFP_EADC0_CH6;
    SYS->GPB_MFPL = (SYS->GPB_MFPL & ~SYS_GPB_MFPL_PB7MFP_Msk) | SYS_GPB_MFPL_PB7MFP_EADC0_CH7;
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~SYS_GPB_MFPH_PB8MFP_Msk) | SYS_GPB_MFPH_PB8MFP_EADC0_CH8;
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~SYS_GPB_MFPH_PB9MFP_Msk) | SYS_GPB_MFPH_PB9MFP_EADC0_CH9;

    /* Disable the GPB0, GPB6~9 digital input path to avoid the leakage current. */
    GPIO_DISABLE_DIGITAL_PATH(PB, BIT9|BIT8|BIT7|BIT6|BIT0);
}

void UART0_Init()
{

    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

void EADC_FunctionTest()
{
    uint8_t  u8Option;
    int32_t  i32ConversionData, i;

    printf("\n");
    printf("+----------------------------------------------------------------------+\n");
    printf("|                M251 EADC Pending Priority sample code                |\n");
    printf("+----------------------------------------------------------------------+\n");

    /* Set the EADC and enable the A/D converter */
    EADC_Open(EADC, (uint32_t)NULL);

    while (1)
    {
        printf("Select test items:\n");
        printf("  [1] Assign interrupt ADINT0~3 to Sample Module 0~3\n");
        printf("  [2] Assign interrupt ADINT3~0 to Sample Module 0~3\n");
        printf("  Other keys: exit EADC test\n");
        u8Option = getchar();

        if (u8Option == '1')
        {
            g_u32IntModule[0] = 0;  /* Assign ADINT0 to Sample module 0 */
            g_u32IntModule[1] = 1;  /* Assign ADINT1 to Sample module 1 */
            g_u32IntModule[2] = 2;  /* Assign ADINT2 to Sample module 2 */
            g_u32IntModule[3] = 3;  /* Assign ADINT3 to Sample module 3 */
        }
        else if (u8Option == '2')
        {
            g_u32IntModule[0] = 3;  /* Assign ADINT0 to Sample module 3 */
            g_u32IntModule[1] = 2;  /* Assign ADINT1 to Sample module 2 */
            g_u32IntModule[2] = 1;  /* Assign ADINT2 to Sample module 1 */
            g_u32IntModule[3] = 0;  /* Assign ADINT3 to Sample module 0 */
        }
        else
            break;  /* exit while loop */

        /* Configure the sample module for analog input channel and software trigger source. */
        EADC_ConfigSampleModule(EADC, 0, EADC_SOFTWARE_TRIGGER, 6);
        EADC_ConfigSampleModule(EADC, 1, EADC_SOFTWARE_TRIGGER, 7);
        EADC_ConfigSampleModule(EADC, 2, EADC_SOFTWARE_TRIGGER, 8);
        EADC_ConfigSampleModule(EADC, 3, EADC_SOFTWARE_TRIGGER, 9);

        /* Clear the A/D ADINTx interrupt flag for safe */
        EADC_CLR_INT_FLAG(EADC, EADC_STATUS2_ADIF0_Msk | EADC_STATUS2_ADIF1_Msk | EADC_STATUS2_ADIF2_Msk | EADC_STATUS2_ADIF3_Msk);

        /* Enable the sample module interrupt.  */
        EADC_ENABLE_INT(EADC, BIT0 | BIT1 | BIT2 | BIT3);

        EADC_ENABLE_SAMPLE_MODULE_INT(EADC, 0, BIT0 << g_u32IntModule[0]);
        EADC_ENABLE_SAMPLE_MODULE_INT(EADC, 1, BIT0 << g_u32IntModule[1]);
        EADC_ENABLE_SAMPLE_MODULE_INT(EADC, 2, BIT0 << g_u32IntModule[2]);
        EADC_ENABLE_SAMPLE_MODULE_INT(EADC, 3, BIT0 << g_u32IntModule[3]);

        NVIC_EnableIRQ(EADC00_IRQn);
        NVIC_EnableIRQ(EADC01_IRQn);
        NVIC_EnableIRQ(EADC02_IRQn);
        NVIC_EnableIRQ(EADC03_IRQn);

        /* Reset the EADC interrupt indicator and trigger sample module to start A/D conversion */
        g_u32IntSequenceIndex = 0;
        g_u32EadcInt0Flag = 0;
        g_u32EadcInt1Flag = 0;
        g_u32EadcInt2Flag = 0;
        g_u32EadcInt3Flag = 0;

        /* Start EADC conversion for sample module 0 ~ 3 at the same time */
        EADC_START_CONV(EADC, BIT0 | BIT1 | BIT2 | BIT3);

        /* Wait all EADC interrupt (g_u32EadcIntxFlag will be set at EADC_INTx_IRQHandler() function) */
        while ((g_u32EadcInt0Flag == 0) || (g_u32EadcInt1Flag == 0) ||
                (g_u32EadcInt2Flag == 0) || (g_u32EadcInt3Flag == 0));

        //        for (i=0; i<80000; i++) __NOP();

        /* Get the conversion result of the sample module */
        printf("The ADINTx interrupt sequence is:\n");

        for (i = 0; i < 4; i++)
        {
            i32ConversionData = EADC_GET_CONV_DATA(EADC, g_u32IntModule[i]);
            printf("ADINT%d: #%d, Module %d, Conversion result: 0x%X (%d)\n", i, g_u32IntSequence[i], g_u32IntModule[i], i32ConversionData, i32ConversionData);
        }

        printf("\n");

        /* Disable the ADINTx interrupt */
        EADC_DISABLE_INT(EADC, BIT0 | BIT1 | BIT2 | BIT3);

        EADC_DISABLE_SAMPLE_MODULE_INT(EADC, 0, BIT0 << g_u32IntModule[0]);
        EADC_DISABLE_SAMPLE_MODULE_INT(EADC, 1, BIT0 << g_u32IntModule[1]);
        EADC_DISABLE_SAMPLE_MODULE_INT(EADC, 2, BIT0 << g_u32IntModule[2]);
        EADC_DISABLE_SAMPLE_MODULE_INT(EADC, 3, BIT0 << g_u32IntModule[3]);

        NVIC_DisableIRQ(EADC00_IRQn);
        NVIC_DisableIRQ(EADC01_IRQn);
        NVIC_DisableIRQ(EADC02_IRQn);
        NVIC_DisableIRQ(EADC03_IRQn);
    }   /* End of while(1) */

    /* Disable the A/D converter */
    EADC_Close(EADC);
}



void EADC00_IRQHandler(void)
{
    g_u32EadcInt0Flag = 1;
    /* Clear the A/D ADINT0 interrupt flag */
    EADC_CLR_INT_FLAG(EADC, EADC_STATUS2_ADIF0_Msk);

    /* Save the interrupt sequence about ADINT0 */
    g_u32IntSequence[0] = g_u32IntSequenceIndex++;
}

void EADC01_IRQHandler(void)
{
    g_u32EadcInt1Flag = 1;
    /* Clear the A/D ADINT1 interrupt flag */
    EADC_CLR_INT_FLAG(EADC, EADC_STATUS2_ADIF1_Msk);

    /* Save the interrupt sequence about ADINT1 */
    g_u32IntSequence[1] = g_u32IntSequenceIndex++;
}

void EADC02_IRQHandler(void)
{
    g_u32EadcInt2Flag = 1;
    /* Clear the A/D ADINT2 interrupt flag */
    EADC_CLR_INT_FLAG(EADC, EADC_STATUS2_ADIF2_Msk);

    /* Save the interrupt sequence about ADINT2 */
    g_u32IntSequence[2] = g_u32IntSequenceIndex++;
}

void EADC03_IRQHandler(void)
{
    g_u32EadcInt3Flag = 1;
    /* Clear the A/D ADINT3 interrupt flag */
    EADC_CLR_INT_FLAG(EADC, EADC_STATUS2_ADIF3_Msk);

    /* Save the interrupt sequence about ADINT3 */
    g_u32IntSequence[3] = g_u32IntSequenceIndex++;
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


    printf("\nSystem clock rate: %d Hz", SystemCoreClock);

    /* EADC function test */
    EADC_FunctionTest();

    /* Disable EADC IP clock */
    CLK_DisableModuleClock(EADC_MODULE);

    /* Reset EADC module */
    SYS_ResetModule(EADC_RST);

    /* Disable External Interrupt */
    NVIC_DisableIRQ(EADC00_IRQn);
    NVIC_DisableIRQ(EADC01_IRQn);
    NVIC_DisableIRQ(EADC02_IRQn);
    NVIC_DisableIRQ(EADC03_IRQn);

    printf("Exit EADC sample code\n");

    while(1);

}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
