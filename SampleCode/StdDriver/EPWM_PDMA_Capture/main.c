/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Capture the EPWM1 Channel 0 waveform by EPWM1 Channel 2, and use PDMA to transfer captured data.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK       192000000


/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
uint16_t g_u32Count[4];
volatile uint32_t g_u32IsTestOver = 0;

/**
 * @brief       EPWM1 IRQ Handler
 *
 * @param       None
 *
 * @return      None
 *
 * @details     ISR to handle EPWM1 interrupt event
 */
void EPWM1P1_IRQHandler(void)
{

}

/**
 * @brief       PDMA IRQ Handler
 *
 * @param       None
 *
 * @return      None
 *
 * @details     ISR to handle PDMA interrupt event
 */
void PDMA_IRQHandler(void)
{
    uint32_t status = PDMA_GET_INT_STATUS(PDMA);

    if(status & PDMA_INTSTS_ABTIF_Msk)    /* abort */
    {
        if(PDMA_GET_ABORT_STS(PDMA) & PDMA_ABTSTS_ABTIF0_Msk)
            g_u32IsTestOver = 2;
        PDMA_CLR_ABORT_FLAG(PDMA,PDMA_ABTSTS_ABTIF0_Msk);
    }
    else if(status & PDMA_INTSTS_TDIF_Msk)      /* done */
    {
        if(PDMA_GET_TD_STS(PDMA) & PDMA_TDSTS_TDIF0_Msk)
            g_u32IsTestOver = 1;
        PDMA_CLR_TD_FLAG(PDMA,PDMA_TDSTS_TDIF0_Msk);
    }
    else
        printf("unknown interrupt !!\n");
}

/*--------------------------------------------------------------------------------------*/
/* Capture function to calculate the input waveform information                         */
/* g_u32Count[4] : Keep the internal counter value when input signal rising / falling     */
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
void CalPeriodTime(EPWM_T *EPWM, uint32_t u32Ch)
{
    uint16_t u16RisingTime, u16FallingTime, u16HighPeriod, u16LowPeriod, u16TotalPeriod;

    g_u32IsTestOver = 0;
    /* Wait PDMA interrupt (g_u32IsTestOver will be set at IRQ_Handler function) */
    while(g_u32IsTestOver == 0);

    u16RisingTime = g_u32Count[1];

    u16FallingTime = g_u32Count[0];

    u16HighPeriod = g_u32Count[1] - g_u32Count[2];

    u16LowPeriod = 0x10000 - g_u32Count[1];

    u16TotalPeriod = 0x10000 - g_u32Count[2];

    printf("\nEPWM generate: \nHigh Period=19199 ~ 19201, Low Period=44799 ~ 44801, Total Period=63999 ~ 64001\n");
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

    /* Enable IP module clock */
    CLK_EnableModuleClock(EPWM1_MODULE);

    /* EPWM clock frequency is set double to PCLK: select EPWM module clock source as PLL */
    CLK_SetModuleClock(EPWM1_MODULE, CLK_CLKSEL2_EPWM1SEL_PLL, (uint32_t)NULL);

    /* Enable PDMA module clock */
    CLK_EnableModuleClock(PDMA_MODULE);

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Update System Core Clock */
    SystemCoreClockUpdate();
    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set PC multi-function pins for EPWM1 Channel 0,2 */
    SYS->GPC_MFPH &= ~(SYS_GPC_MFPH_PC12MFP_Msk | SYS_GPC_MFPH_PC10MFP_Msk);
    SYS->GPC_MFPH |= (SYS_GPC_MFPH_PC12MFP_EPWM1_CH0 | SYS_GPC_MFPH_PC10MFP_EPWM1_CH2);
}

void UART0_Init()
{
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

int32_t main(void)
{
    /* Init System, IP clock and multi-function I/O
       In the end of SYS_Init() will issue SYS_LockReg()
       to lock protected register. If user want to write
       protected register, please issue SYS_UnlockReg()
       to unlock protected register if necessary */

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART to 115200-8n1 for print message */
    UART0_Init();

    printf("\n\nCPU @ %dHz(PLL@ %dHz)\n", SystemCoreClock, PllClock);
    printf("EPWM1 clock is from %s\n", (CLK->CLKSEL2 & CLK_CLKSEL2_EPWM1SEL_Msk) ? "CPU" : "PLL");
    printf("+------------------------------------------------------------------------+\n");
    printf("|                          EPWM Driver Sample Code                        |\n");
    printf("|                                                                        |\n");
    printf("+------------------------------------------------------------------------+\n");
    printf("  This sample code will use EPWM1 channel 2 to capture the signal from EPWM1 channel 0.\n");
    printf("  And the captured data is transferred by PDMA channel 0.\n");
    printf("  I/O configuration:\n");
    printf("    EPWM1 channel 2(PC.10) <--> EPWM1 channel 0(PC.12)\n\n");
    printf("Use EPWM1 Channel 2(PC.10) to capture the EPWM1 Channel 0(PC.12) Waveform\n");

    while(1)
    {
        printf("\n\nPress any key to start EPWM Capture Test\n");
        getchar();

        /*--------------------------------------------------------------------------------------*/
        /* Set the EPWM1 Channel 0 as EPWM output function.                                       */
        /*--------------------------------------------------------------------------------------*/

        /* Assume EPWM output frequency is 250Hz and duty ratio is 30%, user can calculate EPWM settings by follows.
           duty ratio = (CMR+1)/(CNR+1)
           cycle time = CNR+1
           High level = CMR+1
           EPWM clock source frequency = PLL = 192000000
           (CNR+1) = EPWM clock source frequency/prescaler/EPWM output frequency
                   = 192000000/10/300 = 64000
           (Note: CNR is 16 bits, so if calculated value is larger than 65536, user should increase prescale value.)
           CNR = 63999
           duty ratio = 30% ==> (CMR+1)/(CNR+1) = 30%
           CMR = 19199
           Prescale value is 9 : prescaler= 10
        */

        /* Set EPWM1 channel 0 output configuration */
        EPWM_ConfigOutputChannel(EPWM1, 0, 300, 30);

        /* Enable EPWM Output path for EPWM1 channel 0 */
        EPWM_EnableOutput(EPWM1, EPWM_CH_0_MASK);

        /* Enable Timer for EPWM1 channel 0 */
        EPWM_Start(EPWM1, EPWM_CH_0_MASK);

        /*--------------------------------------------------------------------------------------*/
        /* Configure PDMA peripheral mode form EPWM to memory                                    */
        /*--------------------------------------------------------------------------------------*/
        /* Open Channel 0 */
        PDMA_Open(PDMA,BIT0);

        /* Transfer width is half word(16 bit) and transfer count is 4 */
        PDMA_SetTransferCnt(PDMA,0, PDMA_WIDTH_16, 4);

        /* Set source address as EPWM capture channel PDMA register(no increment) and destination address as g_u32Count array(increment) */
        PDMA_SetTransferAddr(PDMA,0, (uint32_t)&(EPWM1->PDMACAP[1]), PDMA_SAR_FIX, (uint32_t)&g_u32Count[0], PDMA_DAR_INC);

        /* Select PDMA request source as EPWM RX(EPWM1 channel 2 should be EPWM1 pair 2) */
        PDMA_SetTransferMode(PDMA,0, PDMA_EPWM1_P2_RX, FALSE, 0);

        /* Set PDMA as single request type for EPWM */
        PDMA_SetBurstType(PDMA,0, PDMA_REQ_SINGLE, PDMA_BURST_4);

        PDMA_EnableInt(PDMA,0, PDMA_INT_TRANS_DONE);
        NVIC_EnableIRQ(PDMA_IRQn);

        /* Enable PDMA for EPWM1 channel 2 capture function, and set capture order as falling first, */
        /* And select capture mode as both rising and falling to do PDMA transfer. */
        EPWM_EnablePDMA(EPWM1, 2, FALSE, EPWM_CAPTURE_PDMA_RISING_FALLING_LATCH);

        /*--------------------------------------------------------------------------------------*/
        /* Set the EPWM1 channel 2 for capture function                                          */
        /*--------------------------------------------------------------------------------------*/

        /* If input minimum frequency is 300Hz, user can calculate capture settings by follows.
           Capture clock source frequency = PCLK = 96000000 in the sample code.
           (CNR+1) = Capture clock source frequency/prescaler/minimum input frequency
                   = 192000000/5/300 = 64000
           (Note: CNR is 16 bits, so if calculated value is larger than 65536, user should increase prescale value.)
           CNR = 0xFFFF
           (Note: In capture mode, user should set CNR to 0xFFFF to increase capture frequency range.)

           Capture unit time = 1/Capture clock source frequency/prescaler
           52ns = 1/192000000/10
        */

        /* Set EPWM1 channel 2 capture configuration */
        EPWM_ConfigCaptureChannel(EPWM1, 2, 52, 0);

        /* Enable Timer for EPWM1 channel 2 */
        EPWM_Start(EPWM1, EPWM_CH_2_MASK);

        /* Enable Capture Function for EPWM1 channel 2 */
        EPWM_EnableCapture(EPWM1, EPWM_CH_2_MASK);

        /* Enable falling capture reload */
        EPWM1->CAPCTL |= EPWM_CAPCTL_FCRLDEN2_Msk;

        /* Wait until EPWM1 channel 2 Timer start to count */
        while((EPWM1->CNT[2]) == 0);

        /* Capture the Input Waveform Data */
        CalPeriodTime(EPWM1, 2);
        /*---------------------------------------------------------------------------------------------------------*/
        /* Stop EPWM1 channel 0 (Recommended procedure method 1)                                                    */
        /* Set EPWM Timer loaded value(Period) as 0. When EPWM internal counter(CNT) reaches to 0, disable EPWM Timer */
        /*---------------------------------------------------------------------------------------------------------*/

        /* Set EPWM1 channel 0 loaded value as 0 */
        EPWM_Stop(EPWM1, EPWM_CH_0_MASK);

        /* Wait until EPWM1 channel 0 Timer Stop */
        while((EPWM1->CNT[0] & EPWM_CNT0_CNT_Msk) != 0);

        /* Disable Timer for EPWM1 channel 0 */
        EPWM_ForceStop(EPWM1, EPWM_CH_0_MASK);

        /* Disable EPWM Output path for EPWM1 channel 0 */
        EPWM_DisableOutput(EPWM1, EPWM_CH_0_MASK);

        /*---------------------------------------------------------------------------------------------------------*/
        /* Stop EPWM1 channel 2 (Recommended procedure method 1)                                                    */
        /* Set EPWM Timer loaded value(Period) as 0. When EPWM internal counter(CNT) reaches to 0, disable EPWM Timer */
        /*---------------------------------------------------------------------------------------------------------*/

        /* Set loaded value as 0 for EPWM1 channel 2 */
        EPWM_Stop(EPWM1, EPWM_CH_2_MASK);

        /* Wait until EPWM1 channel 2 current counter reach to 0 */
        while((EPWM1->CNT[2] & EPWM_CNT0_CNT_Msk) != 0);

        /* Disable Timer for EPWM1 channel 2 */
        EPWM_ForceStop(EPWM1, EPWM_CH_2_MASK);

        /* Disable Capture Function and Capture Input path for  EPWM1 channel 2*/
        EPWM_DisableCapture(EPWM1, EPWM_CH_2_MASK);

        /* Clear Capture Interrupt flag for EPWM1 channel 2 */
        EPWM_ClearCaptureIntFlag(EPWM1, 2, EPWM_CAPTURE_INT_FALLING_LATCH);

        /* Disable PDMA NVIC */
        NVIC_DisableIRQ(PDMA_IRQn);

        PDMA_Close(PDMA);
    }
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
