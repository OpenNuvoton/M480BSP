/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Use BPWM0 Channel 0(PA.0) to capture the BPWM1 Channel 5(PE.13) Waveform.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK       192000000

/**
 * @brief       BPWM0 IRQ Handler
 *
 * @param       None
 *
 * @return      None
 *
 * @details     ISR to handle BPWM0 interrupt event
 */
void BPWM0_IRQHandler(void)
{
    if(BPWM_GetCaptureIntFlag(BPWM0, 0) > 1)
    {
        BPWM_ClearCaptureIntFlag(BPWM0, 0, BPWM_CAPTURE_INT_FALLING_LATCH);
    }
}

/*--------------------------------------------------------------------------------------*/
/* Capture function to calculate the input waveform information                         */
/* u32Count[4] : Keep the internal counter value when input signal rising / falling     */
/*               happens                                                                */
/*                                                                                      */
/* time    A    B     C     D                                                           */
/*           ___   ___   ___   ___   ___   ___   ___   ___                              */
/*      ____|   |_|   |_|   |_|   |_|   |_|   |_|   |_|   |_____                        */
/* index              0 1   2 3                                                         */
/*                                                                                      */
/* The capture internal counter down count from 0x10000, and reload to 0x10000 after    */
/* input signal falling happens (Time B/C/D)                                            */
/*--------------------------------------------------------------------------------------*/
void CalPeriodTime(BPWM_T *BPWM, uint32_t u32Ch)
{
    uint16_t u32Count[4];
    uint32_t u32i;
    uint16_t u16RisingTime, u16FallingTime, u16HighPeriod, u16LowPeriod, u16TotalPeriod;

    /* Clear Capture Falling Indicator (Time A) */
    BPWM_ClearCaptureIntFlag(BPWM, u32Ch, BPWM_CAPTURE_INT_FALLING_LATCH | BPWM_CAPTURE_INT_RISING_LATCH);

    /* Wait for Capture Falling Indicator  */
    while(BPWM_GetCaptureIntFlag(BPWM, u32Ch) < 2);

    /* Clear Capture Falling Indicator (Time B)*/
    BPWM_ClearCaptureIntFlag(BPWM, u32Ch, BPWM_CAPTURE_INT_FALLING_LATCH);

    u32i = 0;

    while(u32i < 4)
    {
        /* Wait for Capture Falling Indicator */
        while(BPWM_GetCaptureIntFlag(BPWM, u32Ch) < 2);

        /* Clear Capture Falling and Rising Indicator */
        BPWM_ClearCaptureIntFlag(BPWM, u32Ch, BPWM_CAPTURE_INT_FALLING_LATCH | BPWM_CAPTURE_INT_RISING_LATCH);

        /* Get Capture Falling Latch Counter Data */
        u32Count[u32i++] = BPWM_GET_CAPTURE_FALLING_DATA(BPWM, u32Ch);

        /* Wait for Capture Rising Indicator */
        while(BPWM_GetCaptureIntFlag(BPWM, u32Ch) < 1);

        /* Clear Capture Rising Indicator */
        BPWM_ClearCaptureIntFlag(BPWM, u32Ch, BPWM_CAPTURE_INT_RISING_LATCH);

        /* Get Capture Rising Latch Counter Data */
        u32Count[u32i++] = BPWM_GET_CAPTURE_RISING_DATA(BPWM, u32Ch);
    }

    u16RisingTime = u32Count[1];

    u16FallingTime = u32Count[0];

    u16HighPeriod = u32Count[1] - u32Count[2];

    u16LowPeriod = 0x10000 - u32Count[1];

    u16TotalPeriod = 0x10000 - u32Count[2];

    printf("\nBPWM generate: \nHigh Period=19199 ~ 19201, Low Period=44799 ~ 44801, Total Period=63999 ~ 64001\n");
    printf("\nCapture Result: Rising Time = %d, Falling Time = %d \nHigh Period = %d, Low Period = %d, Total Period = %d.\n\n",
           u16RisingTime, u16FallingTime, u16HighPeriod, u16LowPeriod, u16TotalPeriod);
    if((u16HighPeriod < 19199) || (u16HighPeriod > 19201) || (u16LowPeriod < 44799) || (u16LowPeriod > 44801) || (u16TotalPeriod < 63999) || (u16TotalPeriod > 64001))
        printf("Capture Test Fail!!\n");
    else
        printf("Capture Test Pass!!\n");
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

    /* Enable BPWM module clock */
    CLK_EnableModuleClock(BPWM0_MODULE);
    CLK_EnableModuleClock(BPWM1_MODULE);

    /* Select UART module clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Select BPWM module clock source */
    CLK_SetModuleClock(BPWM0_MODULE, CLK_CLKSEL2_BPWM0SEL_PCLK0, 0);
    CLK_SetModuleClock(BPWM1_MODULE, CLK_CLKSEL2_BPWM1SEL_PCLK1, 0);

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set PA.0, PE.13 multi-function pin for BPWM0 channel 0 and BPWM1 channel 5 */
    SYS->GPA_MFPL &= ~SYS_GPA_MFPL_PA0MFP_Msk;
    SYS->GPA_MFPL |= SYS_GPA_MFPL_PA0MFP_BPWM0_CH0;
    SYS->GPE_MFPH &= ~SYS_GPE_MFPH_PE13MFP_Msk;
    SYS->GPE_MFPH |= SYS_GPE_MFPH_PE13MFP_BPWM1_CH5;


}

void UART0_Init()
{

    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
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

    printf("+------------------------------------------------------------------------+\n");
    printf("|                          BPWM Driver Sample Code                        |\n");
    printf("|                                                                        |\n");
    printf("+------------------------------------------------------------------------+\n");
    printf("  This sample code will use BPWM0 channel 0 to capture\n  the signal from BPWM1 channel 5.\n");
    printf("  I/O configuration:\n");
    printf("    BPWM0_CH0(PA.0 BPWM0 channel 0) <--> BPWM1_CH5(PE.13 BPWM1 channel 5)\n\n");
    printf("Use BPWM0 Channel 0(PA.0) to capture the BPWM1 Channel 5(PE.13) Waveform\n");

    while(1)
    {
        printf("Press any key to start BPWM Capture Test\n");
        getchar();

        /*--------------------------------------------------------------------------------------*/
        /* Set the BPWM1 Channel 5 as BPWM output function.                                       */
        /*--------------------------------------------------------------------------------------*/

        /* Assume BPWM output frequency is 250Hz and duty ratio is 30%, user can calculate BPWM settings by follows.
           duty ratio = (CMR+1)/(CNR+1)
           cycle time = CNR+1
           High level = CMR+1
           BPWM clock source frequency = PCLK = 80000000
           (CNR+1) = BPWM clock source frequency/prescaler/clock source divider/BPWM output frequency
                   = 80000000/5/250 = 64000
           (Note: CNR is 16 bits, so if calculated value is larger than 65536, user should increase prescale value.)
           CNR = 63999
           duty ratio = 30% ==> (CMR+1)/(CNR+1) = 30%
           CMR = 19199
           Prescale value is 4 : prescaler = 5
        */

        /* set BPWM1 channel 5 output configuration */
        BPWM_ConfigOutputChannel(BPWM1, 5, 250, 30);

        /* Enable BPWM Output path for BPWM1 channel 5 */
        BPWM_EnableOutput(BPWM1, BPWM_CH_5_MASK);

        /* Enable Timer for BPWM1 channel 5 */
        BPWM_Start(BPWM1, BPWM_CH_5_MASK);

        /*--------------------------------------------------------------------------------------*/
        /* Set the BPWM0 channel 0 for capture function                                          */
        /*--------------------------------------------------------------------------------------*/

        /* If input minimum frequency is 250Hz, user can calculate capture settings by follows.
           Capture clock source frequency = PCLK = 80000000 in the sample code.
           (CNR+1) = Capture clock source frequency/prescaler/clock source divider/minimum input frequency
                   = 80000000/5/250 = 64000
           (Note: CNR is 16 bits, so if calculated value is larger than 65536, user should increase prescale value.)
           CNR = 0xFFFF
           (Note: In capture mode, user should set CNR to 0xFFFF to increase capture frequency range.)
        */

        /* set BPWM0 channel 0 capture configuration */
        BPWM_ConfigCaptureChannel(BPWM0, 0, 62, 0);

        /* Enable capture falling edge interrupt for BPWM0 channel 0 */
        //BPWM_EnableCaptureInt(BPWM0, 0, BPWM_CAPTURE_INT_FALLING_LATCH);

        /* Enable BPWM0 NVIC interrupt */
        //NVIC_EnableIRQ(BPWM0_IRQn);

        /* Enable Timer for BPWM0 channel 0 */
        BPWM_Start(BPWM0, BPWM_CH_0_MASK);

        /* Enable Capture Function for BPWM0 channel 0 */
        BPWM_EnableCapture(BPWM0, BPWM_CH_0_MASK);

        /* Enable falling capture reload */
        BPWM0->CAPCTL |= BPWM_CAPCTL_FCRLDEN0_Msk;

        /* Wait until BPWM0 channel 0 Timer start to count */
        while((BPWM0->CNT) == 0);

        /* Capture the Input Waveform Data */
        CalPeriodTime(BPWM0, 0);
        /*---------------------------------------------------------------------------------------------------------*/
        /* Stop BPWM1 channel 0 (Recommended procedure method 1)                                                    */
        /* Set BPWM Timer loaded value(Period) as 0. When BPWM internal counter(CNT) reaches to 0, disable BPWM Timer */
        /*---------------------------------------------------------------------------------------------------------*/

        /* Set BPWM1 channel 5 loaded value as 0 */
        BPWM_Stop(BPWM1, BPWM_CH_5_MASK);

        /* Wait until BPWM1 channel 5 Timer Stop */
        while((BPWM1->CNT & BPWM_CNT_CNT_Msk) != 0);

        /* Disable Timer for BPWM1 channel 5 */
        BPWM_ForceStop(BPWM1, BPWM_CH_5_MASK);

        /* Disable BPWM Output path for BPWM1 channel 5 */
        BPWM_DisableOutput(BPWM1, BPWM_CH_5_MASK);

        /*---------------------------------------------------------------------------------------------------------*/
        /* Stop BPWM0 channel 0 (Recommended procedure method 1)                                                    */
        /* Set BPWM Timer loaded value(Period) as 0. When BPWM internal counter(CNT) reaches to 0, disable BPWM Timer */
        /*---------------------------------------------------------------------------------------------------------*/

        /* Disable BPWM0 NVIC */
        //NVIC_DisableIRQ(BPWM0_IRQn);

        /* Set loaded value as 0 for BPWM0 channel 0 */
        BPWM_Stop(BPWM0, BPWM_CH_0_MASK);

        /* Wait until BPWM0 channel 0 current counter reach to 0 */
        while((BPWM0->CNT & BPWM_CNT_CNT_Msk) != 0);

        /* Disable Timer for BPWM0 channel 0 */
        BPWM_ForceStop(BPWM0, BPWM_CH_0_MASK);

        /* Disable Capture Function and Capture Input path for BPWM0 channel 0 */
        BPWM_DisableCapture(BPWM0, BPWM_CH_0_MASK);

        /* Clear Capture Interrupt flag for BPWM0 channel 0 */
        BPWM_ClearCaptureIntFlag(BPWM0, 0, BPWM_CAPTURE_INT_FALLING_LATCH);
    }
}


/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
