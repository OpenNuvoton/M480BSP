/*************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Demonstrate how to trigger DAC conversion by external pin.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include "NuMicro.h"

#if defined (__GNUC__) && !defined(__ARMCC_VERSION) && defined(OS_USE_SEMIHOSTING)
extern void initialise_monitor_handles(void);
#endif

#define PLL_CLOCK           192000000

const uint16_t sine[] = {2047, 2251, 2453, 2651, 2844, 3028, 3202, 3365, 3515, 3650, 3769, 3871, 3954,
                         4019, 4064, 4088, 4095, 4076, 4040, 3984, 3908, 3813, 3701, 3573, 3429, 3272,
                         3102, 2921, 2732, 2536, 2335, 2132, 1927, 1724, 1523, 1328, 1141,  962,  794,
                         639,  497,  371,  262,  171,   99,   45,   12,    0,    7,   35,   84,  151,
                         238,  343,  465,  602,  754,  919, 1095, 1281, 1475, 1674, 1876
                        };

const uint32_t array_size = sizeof(sine) / sizeof(uint16_t);
static uint32_t index = 0;

void DAC_IRQHandler(void)
{
    if(DAC_GET_INT_FLAG(DAC0, 0))
    {

        if(index == array_size)
            index = 0;
        else
        {
            DAC_WRITE_DATA(DAC0, 0, sine[index++]);

            /* Clear the DAC conversion complete finish flag */
            DAC_CLR_INT_FLAG(DAC0, 0);

        }
    }
    return;
}


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
    CLK_SetCoreClock(PLL_CLOCK);
    /* Set PCLK0/PCLK1 to HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable DAC module clock */
    CLK_EnableModuleClock(DAC_MODULE);

    /* Set PB.12 to input mode */
    PB->MODE &= ~GPIO_MODE_MODE12_Msk;
    /* Set PB multi-function pin for DAC voltage output */
    SYS->GPB_MFPH |= SYS_GPB_MFPH_PB12MFP_DAC0_OUT;
    /* Disable digital input path of analog pin DAC0_OUT to prevent leakage */
    GPIO_DISABLE_DIGITAL_PATH(PB, (1ul << 12));
    /* Set PA multi-function pin for DAC conversion trigger */
    SYS->GPA_MFPL |= SYS_GPA_MFPL_PA0MFP_DAC0_ST;
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

    printf("Please connect PA0 with PA1, use PA1 to trigger DAC conversion\n");

    /* Set the falling edge trigger DAC and enable D/A converter */
    DAC_Open(DAC0, 0, DAC_FALLING_EDGE_TRIGGER);

    /* The DAC conversion settling time is 1us */
    DAC_SetDelayTime(DAC0, 1);

    /* Set DAC 12-bit holding data */
    DAC_WRITE_DATA(DAC0, 0, sine[index]);

    /* Clear the DAC conversion complete finish flag for safe */
    DAC_CLR_INT_FLAG(DAC0, 0);

    /* Enable the DAC interrupt */
    DAC_ENABLE_INT(DAC0, 0);
    NVIC_EnableIRQ(DAC_IRQn);

    GPIO_SetMode(PA, BIT1, GPIO_MODE_OUTPUT);

    while(1)
    {
        PA1 = 1;
        CLK_SysTickDelay(100);
        PA1 = 0;
        CLK_SysTickDelay(100);
    }

}

