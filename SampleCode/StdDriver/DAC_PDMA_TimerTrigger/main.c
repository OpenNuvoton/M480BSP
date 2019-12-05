/*************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Demonstrate how to PDMA and trigger DAC by Timer.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include "stdio.h"
#include "NuMicro.h"

#if defined (__GNUC__) && !defined(__ARMCC_VERSION) && defined(OS_USE_SEMIHOSTING)
extern void initialise_monitor_handles(void);
#endif

const uint16_t sine[] = {2047, 2251, 2453, 2651, 2844, 3028, 3202, 3365, 3515, 3650, 3769, 3871, 3954,
                         4019, 4064, 4088, 4095, 4076, 4040, 3984, 3908, 3813, 3701, 3573, 3429, 3272,
                         3102, 2921, 2732, 2536, 2335, 2132, 1927, 1724, 1523, 1328, 1141,  962,  794,
                         639,  497,  371,  262,  171,   99,   45,   12,    0,    7,   35,   84,  151,
                         238,  343,  465,  602,  754,  919, 1095, 1281, 1475, 1674, 1876
                        };
const uint32_t array_size = sizeof(sine) / sizeof(uint16_t);

void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT clock (external XTAL 12MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable DAC module clock */
    CLK_EnableModuleClock(DAC_MODULE);

    /* Enable Timer 0 module clock */
    CLK_EnableModuleClock(TMR0_MODULE);

    /* Enable PDMA module clock */
    CLK_EnableModuleClock(PDMA_MODULE);

    /* Set PB.12 and PB.13 to input mode */
    PB->MODE &= ~(GPIO_MODE_MODE12_Msk | GPIO_MODE_MODE13_Msk);
    /* Set PB multi-function pins for DAC voltage output */
    SYS->GPB_MFPH |= SYS_GPB_MFPH_PB12MFP_DAC0_OUT | SYS_GPB_MFPH_PB13MFP_DAC1_OUT;

    /* Disable digital input path of analog pin DAC0_OUT to prevent leakage */
    GPIO_DISABLE_DIGITAL_PATH(PB, (1ul << 12));
    /* Lock protected registers */
    SYS_LockReg();
}

int32_t main(void)
{
    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

#if defined (__GNUC__) && !defined(__ARMCC_VERSION) && defined(OS_USE_SEMIHOSTING)
    initialise_monitor_handles();
#endif

    printf("This sample code use PDMA and trigger DAC0 output sine wave by Timer 0.\n");

    /* Open Channel 0 */
    PDMA_Open(PDMA,0x1);

    /* Set transfer data width, and transfer count */
    PDMA_SetTransferCnt(PDMA,0, PDMA_WIDTH_16, array_size);

    /* transfer width is one word(32 bit) */
    PDMA_SetTransferAddr(PDMA,0, (uint32_t)&sine[0], PDMA_SAR_INC, (uint32_t)&DAC0->DAT, PDMA_DAR_FIX);

    /* Select channel 0 request source from DAC */
    PDMA_SetTransferMode(PDMA,0, PDMA_DAC0_TX, FALSE, 0);

    /* Set transfer type and burst size */
    PDMA_SetBurstType(PDMA,0, PDMA_REQ_SINGLE, PDMA_BURST_128);

    /* Set the timer 0 trigger DAC and enable D/A converter */
    DAC_Open(DAC0, 0, DAC_TIMER0_TRIGGER);

    /* The DAC conversion settling time is 1us */
    DAC_SetDelayTime(DAC0, 1);

    /* Clear the DAC conversion complete finish flag for safe */
    DAC_CLR_INT_FLAG(DAC0, 0);

    /* Enable the PDMA Mode */
    DAC_ENABLE_PDMA(DAC0);

    /* Enable Timer0 counting to start D/A conversion */
    TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 1000);
    TIMER_SetTriggerTarget(TIMER0, TIMER_TRG_TO_DAC);
    TIMER_Start(TIMER0);

    while(1)
    {
        if (PDMA_GET_TD_STS(PDMA) == 0x1)
        {
            /* Re-Set transfer count and basic operation mode */
            PDMA_SetTransferCnt(PDMA,0, PDMA_WIDTH_16, array_size);
            PDMA_SetTransferMode(PDMA,0, PDMA_DAC0_TX, FALSE, 0);

            /* Clear PDMA channel 0 transfer done flag */
            PDMA_CLR_TD_FLAG(PDMA,0x1);
        }
    }
}
