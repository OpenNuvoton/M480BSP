/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief
 *           Show how to wake up system form SPD Power-down mode by Wake-up pin(PA.0)
 *           or Wake-up Timer or Wake-up ACMP or RTC Tick or RTC Alarm and RTC Tamper 0
 *           or LVR or BOD.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include "stdio.h"
#include "NuMicro.h"


#define SIGNATURE       0x125ab234
#define FLAG_ADDR       0x20000FFC

#define PLL_CLOCK       192000000

void GpioPinSetting(void);
/*---------------------------------------------------------------------------------------------------------*/
/*  Function for System Entry to Power Down Mode and Wake up source by GPIO Wake-up pin                    */
/*---------------------------------------------------------------------------------------------------------*/
void WakeUpPinFunction(uint32_t u32PDMode)
{
    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)
        printf("Enter to SPD%d Power-Down mode......\n", (u32PDMode - 4));
    else
        printf("Enter to SPD Power-Down mode......\n");

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) != 0x0) // M480LD
    {
        /* Set IO State and all IPs clock disable for power consumption */
        GpioPinSetting();
        /* PA.0 Pull-up Enable */
        GPIO_SetPullCtl(PA, 0, GPIO_PUSEL_PULL_UP);
    }

    /* Select Power-down mode */
    CLK_SetPowerDownMode(u32PDMode);

    /* Configure GPIO as Input mode */
    GPIO_SetMode(PA, BIT0, GPIO_MODE_INPUT);

    // GPIO SPD Power-down Wake-up Pin Select and Debounce Disable
    CLK_EnableSPDWKPin(0, 0, CLK_SPDWKPIN_RISING, CLK_SPDWKPIN_DEBOUNCEDIS);

    /* Enter to Power-down mode */
    CLK_PowerDown();

    /* Wait for Power-down mode wake-up reset happen */
    while(1);
}

/*-----------------------------------------------------------------------------------------------------------*/
/*  Function for System Entry to Power Down Mode and Wake up source by Wake-up Timer                         */
/*-----------------------------------------------------------------------------------------------------------*/
void  WakeUpTimerFunction(uint32_t u32PDMode, uint32_t u32Interval)
{

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)
        printf("Enter to SPD%d Power-Down mode......\n", (u32PDMode - 4));
    else
        printf("Enter to SPD Power-Down mode......\n");

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) != 0x0) // M480LD
    {
        /* Set IO State and all IPs clock disable for power consumption */
        GpioPinSetting();
    }

    /* Select Power-down mode */
    CLK_SetPowerDownMode(u32PDMode);

    /* Set Wake-up Timer Time-out Interval */
    CLK_SET_WKTMR_INTERVAL(u32Interval);

    /* Enable Wake-up Timer */
    CLK_ENABLE_WKTMR();

    /* Enter to Power-down mode */
    CLK_PowerDown();

    /* Wait for Power-down mode wake-up reset happen */
    while(1);
}


/*-----------------------------------------------------------------------------------------------------------*/
/*  Function for System Entry to Power Down Mode and Wake up source by Wake-up ACMP0                         */
/*-----------------------------------------------------------------------------------------------------------*/
void  WakeUpACMP0Function(uint32_t u32PDMode)
{
    printf("\nUsing ACMP0_P0(PA11) as ACMP0 positive input.\n");
    printf("Using internal band-gap voltage as the negative input.\n\n");

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)
        printf("Enter to SPD%d Power-Down mode......\n", (u32PDMode - 4));
    else
        printf("Enter to SPD Power-Down mode......\n");

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) != 0x0) // M480LD
    {
        /* Set IO State and all IPs clock disable for power consumption */
        GpioPinSetting();
    }

    /* Enable ACMP01 peripheral clock */
    CLK_EnableModuleClock(ACMP01_MODULE);

    /* Set PA11 multi-function pin for ACMP0 positive input pin */
    SYS->GPA_MFPH = (SYS->GPA_MFPH & (~SYS_GPA_MFPH_PA11MFP_Msk)) | SYS_GPA_MFPH_PA11MFP_ACMP0_P0;

    /* Set PB7 multi-function pin for ACMP0 output pin */
    SYS->GPB_MFPL = (SYS->GPB_MFPL & (~SYS_GPB_MFPL_PB7MFP_Msk)) | SYS_GPB_MFPL_PB7MFP_ACMP0_O;

    /* Disable digital input path of analog pin ACMP0_P0 to prevent leakage */
    GPIO_DISABLE_DIGITAL_PATH(PA, BIT11);

    /* Configure ACMP0. Enable ACMP0 and select band-gap voltage as the source of ACMP negative input. */
    ACMP_Open(ACMP01, 0, ACMP_CTL_NEGSEL_VBG, ACMP_CTL_HYSTERESIS_DISABLE);
    /* Enable interrupt */
    ACMP_ENABLE_INT(ACMP01, 0);
    /* Clear ACMP 0 interrupt flag */
    ACMP_CLR_INT_FLAG(ACMP01, 0);

    /* Enable wake-up function */
    ACMP_ENABLE_WAKEUP(ACMP01, 0);

    /* Select Power-down mode */
    CLK_SetPowerDownMode(u32PDMode);

    /* Enable Wake-up ACMP */
    CLK_ENABLE_SPDACMP();

    /* Enter to Power-down mode */
    CLK_PowerDown();

    /* Wait for Power-down mode wake-up reset happen */
    while(1);
}

/*-----------------------------------------------------------------------------------------------------------*/
/*  Function for System Entry to Power Down Mode and Wake up source by RTC Tick                              */
/*-----------------------------------------------------------------------------------------------------------*/
void  WakeUpRTCTickFunction(uint32_t u32PDMode)
{
    uint32_t u32TimeOutCnt = SystemCoreClock;// 1 second timeout

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)
        printf("Enter to SPD%d Power-Down mode......\n", (u32PDMode - 4));
    else
        printf("Enter to SPD Power-Down mode......\n");

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) != 0x0) // M480LD
    {
        /* Set IO State and all IPs clock disable for power consumption */
        GpioPinSetting();
    }

    /* enable RTC peripheral clock */
    CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk;
    /* RTC clock source select 32KHz */
    CLK->CLKSEL3 &= ~(CLK_CLKSEL3_RTCSEL_Msk);

    /* Open RTC and start counting */
    RTC->INIT = RTC_INIT_KEY;
    if(RTC->INIT != RTC_INIT_ACTIVE_Msk) {
        RTC->INIT = RTC_INIT_KEY;
        while(RTC->INIT != RTC_INIT_ACTIVE_Msk)
        {
            if(--u32TimeOutCnt == 0)
            {
                printf("Initialize RTC module and start counting failed\n");
                while(1);
            }
        }
    }

    RTC_WaitAccessEnable();
    /* clear tick status */
    RTC_CLEAR_TICK_INT_FLAG();

    /* Enable RTC Tick interrupt */
    RTC_EnableInt(RTC_INTEN_TICKIEN_Msk);
    RTC_WaitAccessEnable();

    /* Select Power-down mode */
    CLK_SetPowerDownMode(u32PDMode);

    RTC_SetTickPeriod(RTC_TICK_1_SEC);

    /* Enable RTC wake-up */
    CLK_ENABLE_RTCWK();

    /* Enter to Power-down mode */
    CLK_PowerDown();

    /* Wait for Power-down mode wake-up reset happen */
    while(1);
}


/*-----------------------------------------------------------------------------------------------------------*/
/*  Function for System Entry to Power Down Mode and Wake up source by RTC Alarm                             */
/*-----------------------------------------------------------------------------------------------------------*/
void  WakeUpRTCAlarmFunction(uint32_t u32PDMode)
{
    S_RTC_TIME_DATA_T sWriteRTC;
    uint32_t u32TimeOutCnt = SystemCoreClock;// 1 second timeout

    /* enable RTC peripheral clock */
    CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk;
    /* RTC clock source select 32KHz */
    CLK->CLKSEL3 &= ~(CLK_CLKSEL3_RTCSEL_Msk);

    /* Open RTC and start counting */
    RTC->INIT = RTC_INIT_KEY;
    if(RTC->INIT != RTC_INIT_ACTIVE_Msk) {
        RTC->INIT = RTC_INIT_KEY;
        while(RTC->INIT != RTC_INIT_ACTIVE_Msk)
        {
            if(--u32TimeOutCnt == 0)
            {
                printf("Initialize RTC module and start counting failed\n");
                while(1);
            }
        }
    }

    /* Open RTC */
    sWriteRTC.u32Year       = 2016;
    sWriteRTC.u32Month      = 5;
    sWriteRTC.u32Day        = 11;
    sWriteRTC.u32DayOfWeek  = 3;
    sWriteRTC.u32Hour       = 15;
    sWriteRTC.u32Minute     = 4;
    sWriteRTC.u32Second     = 10;
    sWriteRTC.u32TimeScale  = 1;
    RTC_Open(&sWriteRTC);

    /* Set RTC alarm date/time */
    sWriteRTC.u32Year       = 2016;
    sWriteRTC.u32Month      = 5;
    sWriteRTC.u32Day        = 11;
    sWriteRTC.u32DayOfWeek  = 3;
    sWriteRTC.u32Hour       = 15;
    sWriteRTC.u32Minute     = 4;
    sWriteRTC.u32Second     = 15;
    RTC_SetAlarmDateAndTime(&sWriteRTC);

    printf("# Set RTC current date/time: 2016/08/16 15:04:10.\n");
    printf("# Set RTC alarm   date/time: 2016/08/16 15:04:%d.\n", sWriteRTC.u32Second);
    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)
        printf("Enter to SPD%d Power-Down mode......\n", (u32PDMode - 4));
    else
        printf("Enter to SPD Power-Down mode......\n");

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) != 0x0) // M480LD
    {
        /* Set IO State and all IPs clock disable for power consumption */
        GpioPinSetting();
    }

    RTC_WaitAccessEnable();
    /* clear alarm status */
    RTC_CLEAR_ALARM_INT_FLAG();

    /* Enable RTC alarm interrupt */
    RTC_EnableInt(RTC_INTEN_ALMIEN_Msk);

    /* Select Power-down mode */
    CLK_SetPowerDownMode(u32PDMode);

    /* Enable RTC wake-up */
    CLK_ENABLE_RTCWK();

    /* Enter to Power-down mode */
    CLK_PowerDown();

    /* Wait for Power-down mode wake-up reset happen */
    while(1);
}

/*-----------------------------------------------------------------------------------------------------------*/
/*  Function for System Entry to Power Down Mode and Wake up source by RTC Tamper pins                       */
/*-----------------------------------------------------------------------------------------------------------*/
void  WakeUpRTCTamperFunction(uint32_t u32PDMode)
{
    uint32_t u32TimeOutCnt = SystemCoreClock;// 1 second timeout

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)
        printf("Enter to SPD%d Power-Down mode......\n", (u32PDMode - 4));
    else
        printf("Enter to SPD Power-Down mode......\n");

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) != 0x0) // M480LD
    {
        /* Set IO State and all IPs clock disable for power consumption */
        GpioPinSetting();
    }

    /* enable RTC peripheral clock */
    CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk;
    /* RTC clock source select 32KHz */
    CLK->CLKSEL3 &= ~(CLK_CLKSEL3_RTCSEL_Msk);

    /* Open RTC and start counting */
    RTC->INIT = RTC_INIT_KEY;
    if(RTC->INIT != RTC_INIT_ACTIVE_Msk) {
        RTC->INIT = RTC_INIT_KEY;
        while(RTC->INIT != RTC_INIT_ACTIVE_Msk)
        {
            if(--u32TimeOutCnt == 0)
            {
                printf("Initialize RTC module and start counting failed\n");
                while(1);
            }
        }
    }

    RTC_WaitAccessEnable();

    RTC_StaticTamperEnable(RTC_TAMPER0_SELECT, RTC_TAMPER_LOW_LEVEL_DETECT, RTC_TAMPER_DEBOUNCE_DISABLE);

    /* Clear Tamper0 status */
    RTC_CLEAR_TAMPER_INT_FLAG(RTC_INTSTS_TAMP0IF_Msk);
    /* Disable Spare Register */
    RTC->SPRCTL = (1 << 5);

    RTC_WaitAccessEnable();

    RTC_EnableInt(RTC_INTEN_TAMP0IEN_Msk);

    /* Select Power-down mode */
    CLK_SetPowerDownMode(u32PDMode);

    /* Enable RTC wake-up */
    CLK_ENABLE_RTCWK();

    /* Enter to Power-down mode */
    CLK_PowerDown();

    /* Wait for Power-down mode wake-up reset happen */
    while(1);
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Function for System Entry to Power Down Mode and Wake up source by LVR                                 */
/*---------------------------------------------------------------------------------------------------------*/
void WakeUpLVRFunction(uint32_t u32PDMode)
{
    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)
        printf("Enter to SPD%d Power-Down mode......\n", (u32PDMode - 4));
    else
        printf("Enter to SPD Power-Down mode......\n");

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) != 0x0) // M480LD
    {
        /* Set IO State and all IPs clock disable for power consumption */
        GpioPinSetting();
    }

    /* Select Power-down mode */
    CLK_SetPowerDownMode(u32PDMode);

    /* Enter to Power-down mode */
    CLK_PowerDown();

    /* Wait for Power-down mode wake-up reset happen */
    while(1);
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Function for System Entry to Power Down Mode and Wake up source by BOD                                 */
/*---------------------------------------------------------------------------------------------------------*/
void WakeUpBODFunction(uint32_t u32PDMode)
{
    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)
        printf("Enter to SPD%d Power-Down mode......\n", (u32PDMode - 4));
    else
        printf("Enter to SPD Power-Down mode......\n");

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) != 0x0) // M480LD
    {
        /* Set IO State and all IPs clock disable for power consumption */
        GpioPinSetting();
    }

    /* Select Power-down mode */
    CLK_SetPowerDownMode(u32PDMode);

    /* Enable Brown-out detector function */
    SYS_ENABLE_BOD();

    /* Set Brown-out detector voltage level as 3.0V */
    SYS_SET_BOD_LEVEL(SYS_BODCTL_BODVL_3_0V);

    /* Enable Brown-out detector reset function */
    SYS_ENABLE_BOD_RST();

    /* Enter to Power-down mode */
    CLK_PowerDown();

    /* Wait for Power-down mode wake-up reset happen */
    while(1);
}

/*-----------------------------------------------------------------------------------------------------------*/
/*  Function for Check Power Manager Status                                                                  */
/*-----------------------------------------------------------------------------------------------------------*/
void CheckPowerSource(void)
{
    unsigned int uRegRstsrc;
    uRegRstsrc = CLK_GetPMUWKSrc();

    printf("Power manager Power Manager Status 0x%x\n", uRegRstsrc);

    if((uRegRstsrc & CLK_PMUSTS_ACMPWK_Msk) != 0)
        printf("Wake-up source is ACMP.\n");
    if((uRegRstsrc & CLK_PMUSTS_RTCWK_Msk) != 0)
        printf("Wake-up source is RTC.\n");
    if((uRegRstsrc & CLK_PMUSTS_TMRWK_Msk) != 0)
        printf("Wake-up source is Wake-up Timer.\n");
    if((uRegRstsrc & CLK_PMUSTS_GPAWK_Msk) != 0)
        printf("Wake-up source is GPIO PortA.\n");
    if((uRegRstsrc & CLK_PMUSTS_LVRWK_Msk) != 0)
        printf("Wake-up source is LVR.\n");
    if((uRegRstsrc & CLK_PMUSTS_BODWK_Msk) != 0)
        printf("Wake-up source is BOD.\n");

    /* Clear all wake-up flag */
    CLK->PMUSTS |= CLK_PMUSTS_CLRWK_Msk;

    if(uRegRstsrc) {
        if(M32(FLAG_ADDR) == SIGNATURE) {
            if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)
                printf("System waken-up from SPD0 mode done!\n");
            else
                printf("System waken-up from SPD mode done! (16K SRAM retention)\n");
            M32(FLAG_ADDR) = 0;
            printf("Press any key to continue ...\n");
            getchar();
        } else {
            if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)
                printf("System waken-up from SPD1 mode done!\n");
            else
                printf("System waken-up from SPD mode done! (No SRAM retention)\n");
        }
    }
}

/*-----------------------------------------------------------------------------------------------------------*/
/*  Function for GPIO Setting                                                                                */
/*-----------------------------------------------------------------------------------------------------------*/
void GpioPinSetting(void)
{
    /* Set function pin to GPIO mode */
    SYS->GPA_MFPH = 0;
    SYS->GPA_MFPL = 0;
    SYS->GPB_MFPH = 0;
    SYS->GPB_MFPL = 0;
    SYS->GPC_MFPH = 0;
    SYS->GPC_MFPL = 0;
    SYS->GPD_MFPH = 0;
    SYS->GPD_MFPL = 0;
    SYS->GPE_MFPH = 0;
    SYS->GPE_MFPL = 0;
    SYS->GPF_MFPH = 0;
    SYS->GPF_MFPL = 0x000000EE; //ICE pin
    SYS->GPG_MFPH = 0;
    SYS->GPG_MFPL = 0;
    SYS->GPH_MFPH = 0;
    SYS->GPH_MFPL = 0;

    /* Set all GPIOs are output mode */
    PA->MODE = 0x55555555;
    PB->MODE = 0x55555555;
    PC->MODE = 0x55555555;
    PD->MODE = 0x55555555;
    PE->MODE = 0x55555555;
    PF->MODE = 0x55555555;
    PG->MODE = 0x55555555;
    PH->MODE = 0x55555555;

    /* Set all GPIOs are output high */
    PA->DOUT = 0xFFFFFFFF;
    PB->DOUT = 0xFFFFFFFF;
    PC->DOUT = 0xFFFFFFFF;
    PD->DOUT = 0xFFFFFFFF;
    PE->DOUT = 0xFFFFFFFF;
    PF->DOUT = 0xFFFFFFFF;
    PG->DOUT = 0xFFFFFFFF;
    PH->DOUT = 0xFFFFFFFF;
}

void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Disable HXT clock (external RC 12MHz) */
    CLK_DisableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Set X32_OUT(PF.4) and X32_IN(PF.5) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE4_Msk | GPIO_MODE_MODE5_Msk);

    /* Enable HIRC, LXT clock (Internal RC 12MHz, external XTAL 32kHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk | CLK_PWRCTL_LXTEN_Msk);

    /* Wait for HIRC, LXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk | CLK_STATUS_LXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);

    /* Enable UART clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART clock source from HIRC */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set PC multi-function pins for CLKO(PC.13) */
    SYS->GPC_MFPH = (SYS->GPC_MFPH & ~SYS_GPC_MFPH_PC13MFP_Msk) | SYS_GPC_MFPH_PC13MFP_CLKO;

}

void UART0_Init()
{
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

int32_t main(void)
{
    uint8_t u8Item;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Release I/O hold status */
    CLK->IOPDCTL = 1;

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0) // M480MD
    {
        /* Set IO State and all IPs clock disable for power consumption */
        GpioPinSetting();
    }


    CLK->APBCLK1 = 0x00000000;
    CLK->APBCLK0 = 0x00000000;

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* ---------- Turn off RTC  -------- */
    CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk;
    RTC_WaitAccessEnable();
    RTC->INTEN = 0;
    RTC_Close();

    /* Init UART0 for printf */
    UART0_Init();

    printf("\n\nCPU @ %d Hz\n\n", SystemCoreClock);
    CLK_EnableCKO(CLK_CLKSEL1_CLKOSEL_HCLK, 3, 0);

    /* Get power manager wake up source */
    CheckPowerSource();

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)
    {
        printf("+-----------------------------------------------------------------+\n");
        printf("|    SPD Power-down Mode and Wake-up Sample Code                  |\n");
        printf("|    Please Select Power Down Mode and Wake up source.            |\n");
        printf("+-----------------------------------------------------------------+\n");
        printf("|[1] SPD0 GPIO Wake-up pin(PA.0) and using rising edge wake up.   |\n");
        printf("|[2] SPD0 Wake-up TIMER time-out interval is 1024 OSC10K clocks.  |\n");
        printf("|[3] SPD0 Wake-up by ACMP0.(band-gap voltage)                     |\n");
        printf("|[4] SPD0 Wake-up by RTC Tick.                                    |\n");
        printf("|[5] SPD0 Wake-up by RTC Alarm.                                   |\n");
        printf("|[6] SPD0 Wake-up by RTC Tamper0(PF.6), Low level.                |\n");
        printf("|[7] SPD0 Wake-up by BOD.                                         |\n");
        printf("|[8] SPD0 Wake-up by LVR.                                         |\n");
        printf("|[a] SPD1 GPIO Wake-up pin(PA.0) and using rising edge wake up.   |\n");
        printf("|[b] SPD1 Wake-up TIMER time-out interval is 1024 OSC10K clocks.  |\n");
        printf("|[c] SPD1 Wake-up by ACMP0.(band-gap voltage)                     |\n");
        printf("|[d] SPD1 Wake-up by RTC Tick.                                    |\n");
        printf("|[e] SPD1 Wake-up by RTC Alarm.                                   |\n");
        printf("|[f] SPD1 Wake-up by RTC Tamper0(PF.6), Low level.                |\n");
        printf("|[g] SPD1 Wake-up by BOD.                                         |\n");
        printf("|[h] SPD1 Wake-up by LVR.                                         |\n");
        printf("+-----------------------------------------------------------------+\n");
    }
    else // M480LD
    {
        printf("+-------------------------------------------------------------------------------------+\n");
        printf("|    SPD Power-down Mode and Wake-up Sample Code.                                     |\n");
        printf("|    Please Select Power Down Mode, SRAM retention range and Wake up source.          |\n");
        printf("+-------------------------------------------------------------------------------------+\n");
        printf("|[1] SPD (16K SRAM retention) GPIO Wake-up pin(PA.0) and using rising edge wake up.   |\n");
        printf("|[2] SPD (16K SRAM retention) Wake-up TIMER time-out interval is 1024 OSC10K clocks.  |\n");
        printf("|[3] SPD (16K SRAM retention) Wake-up by ACMP0.(band-gap voltage)                     |\n");
        printf("|[4] SPD (16K SRAM retention) Wake-up by RTC Tick.                                    |\n");
        printf("|[5] SPD (16K SRAM retention) Wake-up by RTC Alarm.                                   |\n");
        printf("|[6] SPD (16K SRAM retention) Wake-up by RTC Tamper0(PF.6), Low level.                |\n");
        printf("|[7] SPD (16K SRAM retention) Wake-up by BOD.                                         |\n");
        printf("|[8] SPD (16K SRAM retention) Wake-up by LVR.                                         |\n");
        printf("|[a] SPD ( No SRAM retention) GPIO Wake-up pin(PA.0) and using rising edge wake up.   |\n");
        printf("|[b] SPD ( No SRAM retention) Wake-up TIMER time-out interval is 1024 OSC10K clocks.  |\n");
        printf("|[c] SPD ( No SRAM retention) Wake-up by ACMP0.(band-gap voltage)                     |\n");
        printf("|[d] SPD ( No SRAM retention) Wake-up by RTC Tick.                                    |\n");
        printf("|[e] SPD ( No SRAM retention) Wake-up by RTC Alarm.                                   |\n");
        printf("|[f] SPD ( No SRAM retention) Wake-up by RTC Tamper0(PF.6), Low level.                |\n");
        printf("|[g] SPD ( No SRAM retention) Wake-up by BOD.                                         |\n");
        printf("|[h] SPD ( No SRAM retention) Wake-up by LVR.                                         |\n");
        printf("+-------------------------------------------------------------------------------------+\n");
    }

    u8Item = getchar();

    // SRAM retention test
    M32(FLAG_ADDR) = SIGNATURE;

    switch(u8Item)
    {
    case '1':
        WakeUpPinFunction(CLK_PMUCTL_PDMSEL_SPD0);
        break;
    case '2':
        WakeUpTimerFunction(CLK_PMUCTL_PDMSEL_SPD0, CLK_PMUCTL_WKTMRIS_1024);
        break;
    case '3':
        WakeUpACMP0Function(CLK_PMUCTL_PDMSEL_SPD0);
        break;
    case '4':
        WakeUpRTCTickFunction(CLK_PMUCTL_PDMSEL_SPD0);
        break;
    case '5':
        WakeUpRTCAlarmFunction(CLK_PMUCTL_PDMSEL_SPD0);
        break;
    case '6':
        WakeUpRTCTamperFunction(CLK_PMUCTL_PDMSEL_SPD0);
        break;
    case '7':
        WakeUpBODFunction(CLK_PMUCTL_PDMSEL_SPD0);
        break;
    case '8':
        WakeUpLVRFunction(CLK_PMUCTL_PDMSEL_SPD0);
        break;
    case 'a':
    case 'A':
        WakeUpPinFunction(CLK_PMUCTL_PDMSEL_SPD1);
        break;
    case 'b':
    case 'B':
        WakeUpTimerFunction(CLK_PMUCTL_PDMSEL_SPD1, CLK_PMUCTL_WKTMRIS_1024);
        break;
    case 'c':
    case 'C':
        WakeUpACMP0Function(CLK_PMUCTL_PDMSEL_SPD1);
        break;
    case 'd':
    case 'D':
        WakeUpRTCTickFunction(CLK_PMUCTL_PDMSEL_SPD1);
        break;
    case 'e':
    case 'E':
        WakeUpRTCAlarmFunction(CLK_PMUCTL_PDMSEL_SPD1);
        break;
    case 'f':
    case 'F':
        WakeUpRTCTamperFunction(CLK_PMUCTL_PDMSEL_SPD1);
        break;
    case 'g':
    case 'G':
        WakeUpBODFunction(CLK_PMUCTL_PDMSEL_SPD1);
        break;
    case 'h':
    case 'H':
        WakeUpLVRFunction(CLK_PMUCTL_PDMSEL_SPD1);
        break;
    default:
        break;
    }

    while(1);
}

