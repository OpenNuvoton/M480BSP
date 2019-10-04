/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Demonstrate how to trigger EADC by EPWM and transfer conversion data by PDMA.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK       192000000

/*---------------------------------------------------------------------------------------------------------*/
/* Define global variables and constants                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
volatile uint32_t g_u32AdcIntFlag, g_u32COVNUMFlag = 0;
volatile uint32_t g_u32IsTestOver = 0;
int16_t  g_i32ConversionData[6] = {0};
uint32_t g_u32SampleModuleNum = 0;


void EADC00_IRQHandler(void)
{
    g_u32AdcIntFlag = 1;
    EADC_CLR_INT_FLAG(EADC, EADC_STATUS2_ADIF0_Msk);      /* Clear the A/D ADINT0 interrupt flag */
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

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable EPWM0 module clock */
    CLK_EnableModuleClock(EPWM0_MODULE);

    /* Select EPWM0 module clock source as PCLK0 */
    CLK_SetModuleClock(EPWM0_MODULE, CLK_CLKSEL2_EPWM0SEL_PCLK0, 0);

    /* Enable EADC module clock */
    CLK_EnableModuleClock(EADC_MODULE);

    /* EADC clock source is 96MHz, set divider to 8, EADC clock is 96/8 MHz */
    CLK_SetModuleClock(EADC_MODULE, 0, CLK_CLKDIV0_EADC(8));

    /* Enable PDMA clock source */
    CLK_EnableModuleClock(PDMA_MODULE);


    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);
    /* Set PB.0 ~ PB.3 to input mode */
    PB->MODE &= ~(GPIO_MODE_MODE0_Msk | GPIO_MODE_MODE1_Msk | GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);
    /* Configure the GPB0 - GPB3 ADC analog input pins.  */
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB0MFP_Msk | SYS_GPB_MFPL_PB1MFP_Msk |
                       SYS_GPB_MFPL_PB2MFP_Msk | SYS_GPB_MFPL_PB3MFP_Msk);
    SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB0MFP_EADC0_CH0 | SYS_GPB_MFPL_PB1MFP_EADC0_CH1 |
                      SYS_GPB_MFPL_PB2MFP_EADC0_CH2 | SYS_GPB_MFPL_PB3MFP_EADC0_CH3);

    /* Disable the GPB0 - GPB3 digital input path to avoid the leakage current. */
    GPIO_DISABLE_DIGITAL_PATH(PB, BIT3|BIT2|BIT1|BIT0);

}

void UART0_Init()
{


    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

void EPWM0_Init()
{

    /* Set EPWM0 timer clock prescaler */
    EPWM_SET_PRESCALER(EPWM0, 0, 0);

    /* Set up counter type */
    EPWM0->CTL1 &= ~EPWM_CTL1_CNTTYPE0_Msk;

    /* Set EPWM0 timer duty */
    EPWM_SET_CMR(EPWM0, 0, 108);

    /* Set EPWM0 timer period */
    EPWM_SET_CNR(EPWM0, 0, 216);

    /* EPWM period point trigger ADC enable */
    EPWM_EnableADCTrigger(EPWM0, 0, EPWM_TRG_ADC_EVEN_PERIOD);

    /* Set output level at zero, compare up, period(center) and compare down of specified channel */
    EPWM_SET_OUTPUT_LEVEL(EPWM0, BIT0, EPWM_OUTPUT_HIGH, EPWM_OUTPUT_LOW, EPWM_OUTPUT_NOTHING, EPWM_OUTPUT_NOTHING);

    /* Enable output of EPWM0 channel 0 */
    EPWM_EnableOutput(EPWM0, BIT0);
}

void PDMA_Init()
{

    /* Configure PDMA peripheral mode form EADC to memory */
    /* Open Channel 2 */
    PDMA_Open(PDMA,BIT2);

    /* transfer width is half word(16 bit) and transfer count is 6 */
    PDMA_SetTransferCnt(PDMA,2, PDMA_WIDTH_16, 6);

    /* Set source address as EADC data register(no increment) and destination address as g_i32ConversionData array(increment) */
    PDMA_SetTransferAddr(PDMA,2, (uint32_t)&EADC->DAT[g_u32SampleModuleNum], PDMA_SAR_FIX, (uint32_t)g_i32ConversionData, PDMA_DAR_INC);

    /* Select PDMA request source as ADC RX */
    PDMA_SetTransferMode(PDMA,2, PDMA_EADC0_RX, FALSE, 0);

    /* Set PDMA as single request type for EADC */
    PDMA_SetBurstType(PDMA,2, PDMA_REQ_SINGLE, PDMA_BURST_4);

    PDMA_EnableInt(PDMA,2, PDMA_INT_TRANS_DONE);
    NVIC_EnableIRQ(PDMA_IRQn);
}

void ReloadPDMA()
{
    /* transfer width is half word(16 bit) and transfer count is 6 */
    PDMA_SetTransferCnt(PDMA,2, PDMA_WIDTH_16, 6);

    /* Select PDMA request source as ADC RX */
    PDMA_SetTransferMode(PDMA,2, PDMA_EADC0_RX, FALSE, 0);
}


void EADC_FunctionTest()
{
    uint8_t  u8Option;

    printf("\n");
    printf("+----------------------------------------------------------------------+\n");
    printf("|     EPWM trigger mode and transfer conversion data by PDMA test       |\n");
    printf("+----------------------------------------------------------------------+\n");

    printf("\nIn this test, software will get 6 conversion result from the specified channel.\n");

    while(1)
    {
        /* reload PDMA configuration for next transmission */
        ReloadPDMA();

        printf("Select input mode:\n");
        printf("  [1] Single end input (channel 2 only)\n");
        printf("  [2] Differential input (channel pair 1 only(channel 2 and 3))\n");
        printf("  Other keys: exit single mode test\n");
        u8Option = getchar();
        if(u8Option == '1')
        {
            /* Set input mode as single-end and enable the A/D converter */
            EADC_Open(EADC, EADC_CTL_DIFFEN_SINGLE_END);

            /* Configure the sample module 0 for analog input channel 2 and enable EPWM0 trigger source */
            EADC_ConfigSampleModule(EADC, g_u32SampleModuleNum, EADC_EPWM0TG0_TRIGGER, 2);
            if (SYS->CSERVER & SYS_CSERVER_VERSION_Msk) /* M480LD */
                EADC_ENABLE_SAMPLE_MODULE_PDMA(EADC, 1<<g_u32SampleModuleNum);
            else /* M480 */
                EADC_ENABLE_PDMA(EADC);

            printf("Conversion result of channel 2:\n");

            /* Enable EPWM0 channel 0 counter */
            EPWM_Start(EPWM0, BIT0); /* EPWM0 channel 0 counter start running. */

            while(1)
            {
                /* Wait PDMA interrupt (g_u32IsTestOver will be set at IRQ_Handler function) */
                while(g_u32IsTestOver == 0);
                break;
            }
            g_u32IsTestOver = 0;

            /* Disable EPWM0 channel 0 counter */
            EPWM_ForceStop(EPWM0, BIT0); /* EPWM0 counter stop running. */

            for(g_u32COVNUMFlag = 0; (g_u32COVNUMFlag) < 6; g_u32COVNUMFlag++)
                printf("                                0x%X (%d)\n", g_i32ConversionData[g_u32COVNUMFlag], g_i32ConversionData[g_u32COVNUMFlag]);

        }
        else if(u8Option == '2')
        {
            /* Set input mode as differential and enable the A/D converter */
            EADC_Open(EADC, EADC_CTL_DIFFEN_DIFFERENTIAL);
            /* Configure the sample module 0 for analog input channel 2 and software trigger source.*/
            EADC_ConfigSampleModule(EADC, g_u32SampleModuleNum, EADC_EPWM0TG0_TRIGGER, 2);
            if (SYS->CSERVER & SYS_CSERVER_VERSION_Msk) /* M480LD */
                EADC_ENABLE_SAMPLE_MODULE_PDMA(EADC, 1<<g_u32SampleModuleNum);
            else /* M480 */
                EADC_ENABLE_PDMA(EADC);


            printf("Conversion result of channel 2:\n");

            /* Enable EPWM0 channel 0 counter */
            EPWM_Start(EPWM0, BIT0); /* EPWM0 channel 0 counter start running. */

            while(1)
            {
                /* Wait PDMA interrupt (g_u32IsTestOver will be set at IRQ_Handler function) */
                while(g_u32IsTestOver == 0);
                break;
            }
            g_u32IsTestOver = 0;

            /* Disable EPWM0 channel 0 counter */
            EPWM_ForceStop(EPWM0, BIT0); /* EPWM0 counter stop running. */

            for(g_u32COVNUMFlag = 0; (g_u32COVNUMFlag) < 6; g_u32COVNUMFlag++)
                printf("                                0x%X (%d)\n", g_i32ConversionData[g_u32COVNUMFlag], g_i32ConversionData[g_u32COVNUMFlag]);

        }
        else
            return ;

        EADC_Close(EADC);
    }
}


void PDMA_IRQHandler(void)
{
    uint32_t status = PDMA_GET_INT_STATUS(PDMA);

    if(status & PDMA_INTSTS_ABTIF_Msk)    /* abort */
    {
        if(PDMA_GET_ABORT_STS(PDMA) & PDMA_ABTSTS_ABTIF2_Msk)
            g_u32IsTestOver = 2;
        PDMA_CLR_ABORT_FLAG(PDMA,PDMA_ABTSTS_ABTIF2_Msk);
    }
    else if(status & PDMA_INTSTS_TDIF_Msk)      /* done */
    {
        if(PDMA_GET_TD_STS(PDMA) & PDMA_TDSTS_TDIF2_Msk)
            g_u32IsTestOver = 1;
        PDMA_CLR_TD_FLAG(PDMA,PDMA_TDSTS_TDIF2_Msk);
    }
    else
        printf("unknown interrupt !!\n");
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

    /* Init EPWM for EADC */
    EPWM0_Init();

    /* Init PDMA for EADC */
    PDMA_Init();

    printf("\nSystem clock rate: %d Hz", SystemCoreClock);

    /* EADC function test */
    EADC_FunctionTest();

    /* Disable EADC IP clock */
    CLK_DisableModuleClock(EADC_MODULE);

    /* Disable EPWM0 IP clock */
    CLK_DisableModuleClock(EPWM0_MODULE);

    /* Disable PDMA clock source */
    CLK_DisableModuleClock(PDMA_MODULE);

    /* Disable PDMA Interrupt */
    NVIC_DisableIRQ(PDMA_IRQn);

    printf("Exit EADC sample code\n");

    while(1);
}


/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
