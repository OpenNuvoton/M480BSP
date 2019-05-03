/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Measure heartbeat rate by converting electrocardiogram signals
 *           into digit values through ADC. The calculated heartbeat rate will
 *           be sent and printed on screen by UART.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

#include <stdio.h>
#include "NuMicro.h"
#include "Report.h"

#define PLL_CLOCK       192000000

/*---------------------------------------------------------------------------------------------------------*/
/* Define global variables and constants                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
uint32_t Timer_Counter = 0;
uint32_t Timer_Counter1 = 0;
uint32_t HeartSpeedCounter = 0;
uint32_t ShowCounter = 0;
uint32_t Flag = 0;


/*---------------------------------------------------------------------------------------------------------*/
/* Define global variables and constants                                                                   */
/*---------------------------------------------------------------------------------------------------------*/
uint32_t g_u32AdcIntFlag, g_u32COVNUMFlag = 0;

/*---------------------------------------------------------------------------------------------------------*/
/* Define functions prototype                                                                              */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void);

void SYS_Init(void)
{

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT clock (external XTAL 12MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);

    /* Set PCLK0/PCLK1 to HCLK/2 */
    CLK->PCLKDIV = (CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2);

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable EADC module clock */
    CLK_EnableModuleClock(EADC_MODULE);

    /* Enable DAC module clock */
    CLK_EnableModuleClock(DAC_MODULE);

    /* EADC clock source is 80MHz, set divider to 8, ADC clock is 80/8 MHz */
    CLK_SetModuleClock(EADC_MODULE, 0, CLK_CLKDIV0_EADC(8));

    /* Enable OPA clock source */
    CLK_EnableModuleClock(OPA_MODULE);

    /* Enable Timer0 clock source */
    CLK_EnableModuleClock(TMR0_MODULE);
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HXT, 0);

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Set PA multi-function pins for UART0 RXD(PA.3) and TXD(PA.2) */
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD2MFP_Msk | SYS_GPD_MFPL_PD3MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD2MFP_UART0_RXD | SYS_GPD_MFPL_PD3MFP_UART0_TXD);

    /* Configure the GPB0 - GPB3 ADC analog input pins.  */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB14MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB14MFP_EADC0_CH14);
    /* Disable digital input path of analog pin DAC0_OUT to prevent leakage */
    GPIO_DISABLE_DIGITAL_PATH(PB, BIT14);

    /* Set PB multi-function pins for DAC voltage output */
    SYS->GPB_MFPH &= ~SYS_GPB_MFPH_PB12MFP_Msk;
    SYS->GPB_MFPH |= SYS_GPB_MFPH_PB12MFP_DAC0_OUT;
    /* Disable digital input path of analog pin DAC0_OUT to prevent leakage */
    GPIO_DISABLE_DIGITAL_PATH(PB, BIT12);

    /* Disable the GPB0 - GPB3 digital input path to avoid the leakage current. */
    GPIO_DISABLE_DIGITAL_PATH(PB, 0x7EEE);

    //Set I/O multi-function pins to OPA
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB0MFP_Msk | SYS_GPB_MFPL_PB1MFP_Msk | SYS_GPB_MFPL_PB2MFP_Msk);
    SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB0MFP_OPA0_P | SYS_GPB_MFPL_PB1MFP_OPA0_N | SYS_GPB_MFPL_PB2MFP_OPA0_O);
    SYS->GPA_MFPH &= ~((SYS_GPA_MFPH_PA8MFP_Msk) | (SYS_GPA_MFPH_PA9MFP_Msk) | (SYS_GPA_MFPH_PA10MFP_Msk));
    SYS->GPA_MFPH |= (SYS_GPA_MFPH_PA8MFP_OPA1_P) | (SYS_GPA_MFPH_PA9MFP_OPA1_N) | (SYS_GPA_MFPH_PA10MFP_OPA1_O);
    SYS->GPD_MFPH &= ~((SYS_GPD_MFPH_PD10MFP_Msk) | (SYS_GPD_MFPH_PD11MFP_Msk) | (SYS_GPD_MFPH_PD12MFP_Msk));
    SYS->GPD_MFPH |= (SYS_GPD_MFPH_PD10MFP_OPA2_P) | (SYS_GPD_MFPH_PD11MFP_OPA2_N) | (SYS_GPD_MFPH_PD12MFP_OPA2_O);

    /* Lock protected registers */
    SYS_LockReg();
}

void UART0_Init()
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

void DAC_Init()
{
    /* Set the software trigger, enable DAC even trigger mode and enable D/A converter */
    DAC_Open(DAC0, 0, DAC_SOFTWARE_TRIGGER);

    /* The DAC conversion settling time is 1us */
    DAC_SetDelayTime(DAC0, 1);

    /* Set DAC 12-bit holding data */
    DAC_WRITE_DATA(DAC0, 0, 2000);

    /* Start A/D conversion */
    DAC_START_CONV(DAC0);
}

void OPA_Init(uint32_t Ch)
{
    uint32_t u32DelayCnt;

    /* Enable OPA0 Schmitt trigger buffer */
    OPA_ENABLE_SCH_TRIGGER(OPA, Ch);

    /* Power on the OPA0 circuit */
    OPA_POWER_ON(OPA, Ch);

    /* Delay for OPA stable time */
    for(u32DelayCnt = 0; u32DelayCnt < 1500; u32DelayCnt++) __NOP();

    /* Clear OPA0 interrupt flag */
    OPA_CLR_INT_FLAG(OPA, Ch);

    /* Enable OPA0 interrupt function */
    OPA_ENABLE_INT(OPA, Ch);

    /* Configure and start calibration */
    OPA_Calibration(OPA, Ch, 0, OPA_CALIBRATION_RV_1_2_AVDD);
}

void Timer0_Init()
{
    // Set timer frequency to 20HZ
    TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 20);

    // Enable timer interrupt
    TIMER_EnableInt(TIMER0);
    NVIC_EnableIRQ(TMR0_IRQn);

    // Start Timer 0
    TIMER_Start(TIMER0);
}

/*---------------------------------------------------------------------------------------------------------*/
/* EADC function test                                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
void ADC_Init()
{

    /* Set the ADC internal sampling time, input mode as single-end and enable the A/D converter */
    EADC_Open(EADC, EADC_CTL_DIFFEN_SINGLE_END);

    /* Configure the sample module 0 for analog input channel 10 and ADINT0 trigger source */
    EADC_ConfigSampleModule(EADC, 0, EADC_SOFTWARE_TRIGGER, 14);

    /* Clear the A/D ADINT0 interrupt flag for safe */
    EADC_CLR_INT_FLAG(EADC, 0x1);

    /* Enable sample module 0 for ADINT0 */
    EADC_ENABLE_SAMPLE_MODULE_INT(EADC, 0, 0x1);
    /* Enable ADINT0 interrupt */
    EADC_ENABLE_INT(EADC, 0x1);
    NVIC_EnableIRQ(EADC00_IRQn);

    /* Reset the EADC interrupt indicator and trigger sample module 0 to start A/D conversion */
    EADC_START_CONV(EADC, 0x1);

}

void TMR0_IRQHandler(void)
{
    int i;

    /* Reset the EADC interrupt indicator and trigger sample module 0 to start A/D conversion */
    EADC_START_CONV(EADC, 0x1);
    for(i = 20; i>0; i--)
    {
        ADCData[i+1] = ADCData[i];
    }
    ADCData[1] = ADCData[0];
    ADCData[0] = g_u32ADCValue_ch14;

    //report sensor
    report_sensors((int16_t)g_u32ADCValue_ch14);
    if((ADCData[7] < ADCData[6]) && (ADCData[6] < ADCData[5]))
    {
        if((ADCData[4] > ADCData[3]) && (ADCData[3] > ADCData[2]))
        {
            Time[4]=Time[3];
            Time[3]=Time[2];
            Time[2]=Time[1];
            Time[1]=Time[0];
            Time[0]=Timer_Counter;
            HeartFreq[3] = Time[3] - Time[4];
            HeartFreq[2] = Time[2] - Time[3];
            HeartFreq[1] = Time[1] - Time[2];
            HeartFreq[0] = Time[0] - Time[1];

            if(((HeartFreq[0]-3) > HeartFreq[1]) && ((HeartFreq[2]-3) > HeartFreq[1]))
            {
                HeartFreq1[0] = HeartFreq[0] + HeartFreq[1];
                HeartFreq1[1] = (float)1200/(float)(HeartFreq1[0]);
                if(HeartFreq1[1]<120 && HeartFreq1[1]>45)
                {
                    ShowCounter++;
                    if(ShowCounter<10)
                        HeartFreq1[2] = HeartFreq1[1];
                    else
                        HeartFreq1[2] = HeartFreq1[2]*9/10 + HeartFreq1[1]/10;
                }
                Flag = 1;
            }
            else if(((HeartFreq[0]-3) < HeartFreq[1]) && ((HeartFreq[2]+3) > HeartFreq[1]))
            {
                HeartFreq1[0] = HeartFreq[0];
                HeartFreq1[1] = (float)1200/(float)(HeartFreq1[0]);
                if(HeartFreq1[1]<120 && HeartFreq1[1]>45)
                {
                    ShowCounter++;
                    if(ShowCounter<10)
                        HeartFreq1[2] = HeartFreq1[1];
                    else
                        HeartFreq1[2] = HeartFreq1[2]*9/10 + HeartFreq1[1]/10;
                }
                Flag = 2;
            }
            else
            {
                Flag = 0;
            }
        }
    }
    Timer_Counter++;
    // enable timer interrupt trigger EADC
    TIMER0->TRGCTL |= TIMER_TRGCTL_TRGEADC_Msk;

    // clear timer interrupt flag
    TIMER_ClearIntFlag(TIMER0);

}

/*---------------------------------------------------------------------------------------------------------*/
/* EADC interrupt handler                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/
void EADC00_IRQHandler(void)
{

    g_u32ADCValue_ch14 = EADC_GET_CONV_DATA(EADC, 0);

    g_u32AdcIntFlag = 1;
    g_u32COVNUMFlag++;
    EADC_CLR_INT_FLAG(EADC, 0x1);/* Clear the A/D ADINT0 interrupt flag */
}

void CommandProcess()
{
    // Read incoming control messages
    if (Serial_available(UART0) >= 2)
    {
        char start=Serial_read(UART0);
        if (start == '@')  // Start of new control message
        {
            int command = Serial_read(UART0); // Commands
            if (command == 'h')  //Hook AHRS Stack Device
            {
                // Read ID
                char id[2];
                id[0] = getchar();
                id[1] = getchar();
                // Reply with synch message
                printf("@HOOK");
                Serial_write(UART0, id, 2);
            }
            else if (command == 'm')     // Set report 'm'ode
            {
                char mode = getchar();
                if (mode == 'r')  // Report sensor 'r'aw data
                {
                    report_mode = REPORT_SENSORS_RAW;
                }
                if (mode == 's')  // Report Heart 'S'peed data
                {
                    report_mode = REPORT_HEART_SPEED;
                }
            }
            else if (command == 'f')     // Set report 'f'ormat
            {
                char format = getchar();
                if (format == 'b')  // Report 'b'inary format
                {
                    report_format = REPORT_FORMAT_BINARY;
                }
                else if (format == 't')     // Report 't'ext format
                {
                    report_format = REPORT_FORMAT_TEXT;
                }
            }
            else if (command == 's')     // 's'tream output control
            {
                char mode = getchar();
                if (mode == 's')  // 's'tart stream
                {
                    stream_mode = STREAM_START;
                }
                else if (mode == 'p')     // 'p'ause stream
                {
                    stream_mode = STREAM_PAUSE;
                }
                else if (mode == 't')     // 't'oggle stream
                {
                    if(stream_mode==STREAM_START)
                        stream_mode = STREAM_PAUSE;
                    else
                        stream_mode = STREAM_START;
                }
            }
        }
        else
        {
            printf("Unknown command.\n");
        } // Skip character
    }
}

void loop()
{
    CommandProcess();
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

    /* Init Timer0 */
    Timer0_Init();

    /* Init DAC */
    DAC_Init();

    /* Init OPA */
    OPA_Init(0);
    OPA_Init(1);
    OPA_Init(2);

    ADC_Init();

    /*---------------------------------------------------------------------------------------------------------*/
    /* Command list                                                                                             */
    /*---------------------------------------------------------------------------------------------------------*/

    printf("\nSystem clock rate: %d Hz", SystemCoreClock);
    printf("+-----------------------------------------------------------+\n");
    printf("|  Heart Beating Function Test                              |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|  Description :                                            |\n");
    printf("|    The sample code will print Heartbeat rate on terminal  |\n");
    printf("|    Please enter '@ss' to start                            |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("*Command List:\n");
    printf("@ss  - Stream Start\n");
    printf("@sp  - Stream Stop\n");
    printf("@mr  - Report sensor 'r'aw data\n");
    printf("@ms  - Report Heart beating speed\n");
    printf("@fb  - Format Binary, switch display format to binary (GUI protocol)\n");
    printf("@ft  - Format Text, switch display format to text\n");

    /*
        Using OPA to amplify electrocardiogram signal
        UART0 is set to debug port.
        PD2 is UART RX. PD3 is UART TX.
        UART0 will print the Heartbeat rate on screen.
    */

    while(1)
        loop();

}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
