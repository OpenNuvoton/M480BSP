/****************************************************************************
 * @file     main.c
 * @version  V1.00
 * @brief    Demonstrate the RTC dynamic tamper function.
 *
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "M480.h"

/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/

volatile int32_t   g_bTamper  = FALSE;


/**
  * @brief  TAMPER ISR to handle interrupt event
  * @param  None
  * @retval None
  */
void TAMPER_IRQHandler(void)
{
    uint32_t u32TmpStatus;
    uint32_t i;

    u32TmpStatus = RTC->INTSTS & (0x3F << RTC_INTEN_TAMP0IEN_Pos);

    if ( u32TmpStatus ) {      /* tamper interrupt occurred */

        for(i = 0; i < 6; i++) {
            if(u32TmpStatus & (0x1 << (i+RTC_INTEN_TAMP0IEN_Pos)))
                printf(" Tamper %d Detected!!\n", i);
        }

        printf(" Tamper detected date: 20%d%d / %d%d / %d%d \n",
               ((RTC->TAMPCAL & RTC_TAMPCAL_TENYEAR_Msk) >> RTC_TAMPCAL_TENYEAR_Pos),
               ((RTC->TAMPCAL & RTC_TAMPCAL_YEAR_Msk) >> RTC_TAMPCAL_YEAR_Pos),
               ((RTC->TAMPCAL & RTC_TAMPCAL_TENMON_Msk) >> RTC_TAMPCAL_TENMON_Pos),
               ((RTC->TAMPCAL & RTC_TAMPCAL_MON_Msk) >> RTC_TAMPCAL_MON_Pos),
               ((RTC->TAMPCAL & RTC_TAMPCAL_TENDAY_Msk) >> RTC_TAMPCAL_TENDAY_Pos),
               ((RTC->TAMPCAL & RTC_TAMPCAL_DAY_Msk) >> RTC_TAMPCAL_DAY_Pos));
        printf(" Tamper detected Time: %d%d: %d%d: %d%d \n",
               ((RTC->TAMPTIME & RTC_TAMPTIME_TENHR_Msk) >> RTC_TAMPTIME_TENHR_Pos),
               ((RTC->TAMPTIME & RTC_TAMPTIME_HR_Msk) >> RTC_TAMPTIME_HR_Pos),
               ((RTC->TAMPTIME & RTC_TAMPTIME_TENMIN_Msk) >> RTC_TAMPTIME_TENMIN_Pos),
               ((RTC->TAMPTIME & RTC_TAMPTIME_MIN_Msk) >> RTC_TAMPTIME_MIN_Pos),
               ((RTC->TAMPTIME & RTC_TAMPTIME_TENSEC_Msk) >> RTC_TAMPTIME_TENSEC_Pos),
               ((RTC->TAMPTIME & RTC_TAMPTIME_SEC_Msk) >> RTC_TAMPTIME_SEC_Pos));
        RTC->INTSTS = u32TmpStatus;
        g_bTamper = TRUE;
    }
}

void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable HXT and LXT */
    CLK->PWRCTL |= CLK_PWRCTL_HXTEN_Msk; // XTAL12M (HXT) Enabled
    CLK->PWRCTL |= CLK_PWRCTL_LXTEN_Msk; // 32K (LXT) Enabled

    /* Waiting clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);
    CLK_WaitClockReady(CLK_STATUS_LXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(192000000);
    CLK->PCLKDIV = (CLK_PCLKDIV_PCLK0DIV2 | CLK_PCLKDIV_PCLK1DIV2); // PCLK divider set 2

    /* Enable IP clock */
    CLK->APBCLK0 |= CLK_APBCLK0_UART0CKEN_Msk; // UART0 Clock Enable
    CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk; // RTC Clock Enable

    /* Select IP clock source */
    CLK->CLKSEL1 &= ~CLK_CLKSEL1_UART0SEL_Msk;
    CLK->CLKSEL1 |= (0x3 << CLK_CLKSEL1_UART0SEL_Pos);// Clock source from HIRC

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    SystemCoreClockUpdate();

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set PD multi-function pins for UART0 RXD and TXD */
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD2MFP_Msk | SYS_GPD_MFPL_PD3MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD2MFP_UART0_RXD | SYS_GPD_MFPL_PD3MFP_UART0_TXD);

    /* Lock protected registers */
    SYS_LockReg();

}

void UART0_Init()
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    UART_Open(UART0, 115200);
}


int32_t main(void)
{
    S_RTC_TIME_DATA_T sInitTime;

    SYS_Init();
    UART0_Init();

    /* Time Setting */
    sInitTime.u32Year       = 2017;
    sInitTime.u32Month      = 5;
    sInitTime.u32Day        = 1;
    sInitTime.u32Hour       = 12;
    sInitTime.u32Minute     = 30;
    sInitTime.u32Second     = 0;
    sInitTime.u32DayOfWeek  = RTC_MONDAY;
    sInitTime.u32TimeScale  = RTC_CLOCK_24;

    RTC_Open(&sInitTime);

    printf("\n RTC Tamper Test Start:");
    printf("\n Please connect (tamper0 & tamper1) and (tamper2 & tamper3) and (tamper4 & tamper5)");
    printf("\n Press any key to start test.");

    getchar();

    RTC_DynamicTamperEnable((RTC_PAIR0_SELECT|RTC_PAIR1_SELECT|RTC_PAIR2_SELECT),
                            RTC_TAMPER_DEBOUNCE_ENABLE, 0, 0);

    RTC_DynamicTamperConfig(RTC_2POW10_CLK, 1, 0, REF_RANDOM_PATTERN);

    RTC_CLEAR_TAMPER_INT_FLAG(RTC_INTSTS_TAMP0IF_Msk | RTC_INTSTS_TAMP1IF_Msk | RTC_INTSTS_TAMP2IF_Msk |
                              RTC_INTSTS_TAMP3IF_Msk | RTC_INTSTS_TAMP4IF_Msk | RTC_INTSTS_TAMP5IF_Msk);

    g_bTamper = FALSE;
    /* Enable RTC Tamper Interrupt */
    RTC_EnableInt(RTC_INTEN_TAMP0IEN_Msk | RTC_INTEN_TAMP1IEN_Msk | RTC_INTEN_TAMP2IEN_Msk |
                  RTC_INTEN_TAMP3IEN_Msk | RTC_INTEN_TAMP4IEN_Msk | RTC_INTEN_TAMP5IEN_Msk);
    NVIC_EnableIRQ(TAMPER_IRQn);

    printf("\n Please disconnect (tamper0 & tamper1) or (tamper2 & tamper3) or (tamper4 & tamper5) \n\n");

    while(!g_bTamper);

    /* Disable RTC Alarm Interrupt */
    RTC_DisableInt(RTC_INTEN_TAMP0IEN_Msk | RTC_INTEN_TAMP1IEN_Msk | RTC_INTEN_TAMP2IEN_Msk |
                   RTC_INTEN_TAMP3IEN_Msk | RTC_INTEN_TAMP4IEN_Msk | RTC_INTEN_TAMP5IEN_Msk);
    NVIC_DisableIRQ(RTC_IRQn);

    printf("\n RTC dynamic Tamper Test End !!\n");

    while(1);

}



/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/



