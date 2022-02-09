/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief
 *           Show how to wake up system form DPD Power-down mode by Wake-up pin(PC.0)
 *           or Wake-up Timer or RTC Tick or RTC Alarm or RTC Tamper 0.
 *
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include "stdio.h"
#include "NuMicro.h"

#define PLL_CLOCK       192000000

/*---------------------------------------------------------------------------------------------------------*/
/*  Function for System Entry to Power Down Mode and Wake up source by Wake-up pin                         */
/*---------------------------------------------------------------------------------------------------------*/
void WakeUpPinFunction(uint32_t u32PDMode, uint32_t u32EdgeType)
{
    printf("Enter to DPD Power-Down mode......\n");

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    /* Select Power-down mode */
    CLK_SetPowerDownMode(u32PDMode);

    /* Configure GPIO as Input mode */
    GPIO_SetMode(PC, BIT0, GPIO_MODE_INPUT);

    // Set Wake-up pin trigger type at Deep Power down mode
    CLK_EnableDPDWKPin(u32EdgeType);

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
    printf("Enter to DPD Power-Down mode......\n");

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    /* Select Power-down mode */
    CLK_SetPowerDownMode(u32PDMode);

    /* Enable LIRC clock */
    CLK->PWRCTL |= CLK_PWRCTL_LIRCEN_Msk;

    /* Wait for LIRC clock stable */
    CLK_WaitClockReady(CLK_STATUS_LIRCSTB_Msk);

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
/*  Function for System Entry to Power Down Mode and Wake up source by RTC Tick                              */
/*-----------------------------------------------------------------------------------------------------------*/
void WakeUpRTCTickFunction(uint32_t u32PDMode)
{
    uint32_t u32TimeOutCnt = SystemCoreClock;// 1 second timeout

    printf("Enter to DPD Power-down mode......\n");

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    /* Enable RTC peripheral clock */
    CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk;

    /* RTC clock source select LXT */
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

    /* Clear tick status */
    RTC_WaitAccessEnable();
    RTC_CLEAR_TICK_INT_FLAG();

    /* Enable RTC Tick interrupt */
    RTC_WaitAccessEnable();
    RTC_EnableInt(RTC_INTEN_TICKIEN_Msk);

    /* Select Power-down mode */
    CLK_SetPowerDownMode(u32PDMode);

    /* Set RTC tick period as 1 second */
    RTC_SetTickPeriod(RTC_TICK_1_SEC);

    /* Set GPF6~7 pull-up when enter DPD mode */ /* PF4(X32_OUT), PF5(X32_IN) unnecessary set pull-up */
    RTC->GPIOCTL0 |= (0x1 << RTC_GPIOCTL0_PUSEL2_Pos) | (0x1 << RTC_GPIOCTL0_PUSEL3_Pos);
    /* Set GPF8~11 pull-up when enter DPD mode */
    RTC->GPIOCTL1 |= (0x1 << RTC_GPIOCTL1_PUSEL4_Pos) | (0x1 << RTC_GPIOCTL1_PUSEL5_Pos) |
                     (0x1 << RTC_GPIOCTL1_PUSEL6_Pos) | (0x1 << RTC_GPIOCTL1_PUSEL7_Pos);

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

    /* Enable RTC peripheral clock */
    CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk;

    /* RTC clock source select LXT */
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
    printf("Enter to DPD Power-down mode......\n");

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    /* Enable RTC alarm interrupt and wake-up function will be enabled also */
    RTC_EnableInt(RTC_INTEN_ALMIEN_Msk);

    RTC_WaitAccessEnable();
    /* clear alarm status */
    RTC->INTSTS = RTC_INTSTS_ALMIF_Msk;

    /* Enable RTC alarm interrupt and wake-up function will be enabled also */
    RTC->INTEN = RTC_INTEN_ALMIEN_Msk;

    /* Set GPF6~7 pull-up when enter DPD mode */ /* PF4(X32_OUT), PF5(X32_IN) unnecessary set pull-up */
    RTC->GPIOCTL0 |= (0x1 << RTC_GPIOCTL0_PUSEL2_Pos) | (0x1 << RTC_GPIOCTL0_PUSEL3_Pos);
    /* Set GPF8~11 pull-up when enter DPD mode */
    RTC->GPIOCTL1 |= (0x1 << RTC_GPIOCTL1_PUSEL4_Pos) | (0x1 << RTC_GPIOCTL1_PUSEL5_Pos) |
                     (0x1 << RTC_GPIOCTL1_PUSEL6_Pos) | (0x1 << RTC_GPIOCTL1_PUSEL7_Pos);

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
/*  Function for System Entry to Power Down Mode and Wake up source by RTC Tamper                            */
/*-----------------------------------------------------------------------------------------------------------*/
void  WakeUpRTCTamperFunction(uint32_t u32PDMode)
{
    uint32_t u32TimeOutCnt = SystemCoreClock;// 1 second timeout

    printf("Enter to DPD Power-down mode......\n");

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    /* Enable RTC peripheral clock */
    CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk;

    /* RTC clock source select LXT */
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

    /* Set GPF7 pull-up when enter DPD mode */ /* PF4(X32_OUT), PF5(X32_IN), PF6(Tamper0) unnecessary set pull-up */
    RTC->GPIOCTL0 |= (0x1 << RTC_GPIOCTL0_PUSEL3_Pos);
    /* Set GPF8~11 pull-up when enter DPD mode */
    RTC->GPIOCTL1 |= (0x1 << RTC_GPIOCTL1_PUSEL4_Pos) | (0x1 << RTC_GPIOCTL1_PUSEL5_Pos) |
                     (0x1 << RTC_GPIOCTL1_PUSEL6_Pos) | (0x1 << RTC_GPIOCTL1_PUSEL7_Pos);

    /* Set RTC Tamper 0 as low level detect */
    RTC_StaticTamperEnable(RTC_TAMPER0_SELECT, RTC_TAMPER_LOW_LEVEL_DETECT, RTC_TAMPER_DEBOUNCE_DISABLE);

    /* Clear Tamper 0 status */
    RTC_WaitAccessEnable();
    RTC_CLEAR_TAMPER_INT_FLAG(RTC_INTSTS_TAMP0IF_Msk);

    /* Disable Spare Register */
    RTC_WaitAccessEnable();
    RTC->SPRCTL = RTC_SPRCTL_SPRCSTS_Msk;

    /* Enable RTC Tamper 0 */
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

/*-----------------------------------------------------------------------------------------------------------*/
/*  Function for Check Power Manager Status                                                                  */
/*-----------------------------------------------------------------------------------------------------------*/
void CheckPowerSource(void)
{
    uint32_t u32RegRstsrc;
    u32RegRstsrc = CLK_GetPMUWKSrc();

    printf("Power manager Power Manager Status 0x%x\n", u32RegRstsrc);

    if((u32RegRstsrc & CLK_PMUSTS_RTCWK_Msk) != 0)
        printf("Wake-up source is RTC.\n");
    if((u32RegRstsrc & CLK_PMUSTS_TMRWK_Msk) != 0)
        printf("Wake-up source is Wake-up Timer.\n");
    if((u32RegRstsrc & CLK_PMUSTS_PINWK_Msk) != 0)
        printf("Wake-up source is Wake-up Pin.\n");

    /* Clear all wake-up flag */
    CLK->PMUSTS |= CLK_PMUSTS_CLRWK_Msk;
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
    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Set X32_OUT(PF.4) and X32_IN(PF.5) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE4_Msk | GPIO_MODE_MODE5_Msk);

    /* Enable HXT and LXT */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk | CLK_PWRCTL_LXTEN_Msk);

    /* Waiting clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);
    CLK_WaitClockReady(CLK_STATUS_LXTSTB_Msk);

    /* Enable HIRC clock (Internal RC 12MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);

    /* Wait for HIRC clock ready */
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

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

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1) {
        /* Set PF multi-function pins for TAMPER0(PF.6) */
        SYS->GPF_MFPL = (SYS->GPF_MFPL & (~SYS_GPF_MFPL_PF6MFP_Msk)) | SYS_GPF_MFPL_PF6MFP_TAMPER0;
    }
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

    /* Set IO State and all IPs clock disable for power consumption */
    GpioPinSetting();

    CLK->APBCLK1 = 0x00000000;
    CLK->APBCLK0 = 0x00000000;

    /* ---------- Turn off RTC  -------- */
    CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk;
    RTC_WaitAccessEnable();
    RTC->INTEN = 0;
    CLK->APBCLK0 &= ~CLK_APBCLK0_RTCCKEN_Msk;

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1) {
        CLK->IOPDCTL = 1;
        CLK->PMUCTL |= CLK_PMUCTL_DPDHOLDEN_Msk;
    }

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Init UART0 for printf */
    UART0_Init();

    printf("\n\nCPU @ %d Hz\n", SystemCoreClock);
    CLK_EnableCKO(CLK_CLKSEL1_CLKOSEL_HCLK, 3, 0);

    /* Get power manager wake up source */
    CheckPowerSource();

    printf("+----------------------------------------------------------------+\n");
    printf("|    DPD Power-down Mode and Wake-up Sample Code.                |\n");
    printf("|    Please Select Wake up source.                               |\n");
    printf("+----------------------------------------------------------------+\n");
    printf("|[1] DPD Wake-up Pin(PC.0) trigger type is rising edge.          |\n");
    printf("|[2] DPD Wake-up TIMER time-out interval is 16384 OSC10K clocks. |\n");

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1) {
        printf("|[3] DPD Wake-up by RTC Tick(1 second).                          |\n");
        printf("|[4] DPD Wake-up by RTC Alarm.                                   |\n");
        printf("|[5] DPD Wake-up by RTC Tamper0(PF.6).                           |\n");
        printf("|    Tamper pin detect voltage level is low.                     |\n");
    }

    printf("+----------------------------------------------------------------+\n");
    u8Item = getchar();

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1) {
        switch(u8Item) {
        case '1':
            WakeUpPinFunction(CLK_PMUCTL_PDMSEL_DPD, CLK_DPDWKPIN_RISING);
            break;
        case '2':
            WakeUpTimerFunction(CLK_PMUCTL_PDMSEL_DPD, CLK_PMUCTL_WKTMRIS_16384);
            break;
        case '3':
            WakeUpRTCTickFunction(CLK_PMUCTL_PDMSEL_DPD);
            break;
        case '4':
            WakeUpRTCAlarmFunction(CLK_PMUCTL_PDMSEL_DPD);
            break;
        case '5':
            WakeUpRTCTamperFunction(CLK_PMUCTL_PDMSEL_DPD);
            break;
        default:
            break;
        }
    } else {
        switch(u8Item) {
        case '1':
            WakeUpPinFunction(CLK_PMUCTL_PDMSEL_DPD, CLK_DPDWKPIN_RISING);
            break;
        case '2':
            WakeUpTimerFunction(CLK_PMUCTL_PDMSEL_DPD, CLK_PMUCTL_WKTMRIS_16384);
            break;
        default:
            break;
        }
    }

    while(1);
}

