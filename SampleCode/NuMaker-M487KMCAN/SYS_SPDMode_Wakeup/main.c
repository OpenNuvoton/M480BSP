/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    This sample shows how to make an application booting from APROM
 *           with a sub-routine resided on SPIM flash.
 *           Show how to wake up system form SPD0/1 Power-down mode by Wake-up pin(PA.0)
 *           or Wake-up Timer or Wake-up ACMP or RTC Tick or RTC Alarm and RTC Tamper 0
 *           or LVR or BOD.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define USE_4_BYTES_MODE    0            /* W25Q20 does not support 4-bytes address mode. */

#define SIGNATURE       0x125ab234
#define FLAG_ADDR       0x20000FFC

#define PLL_CLOCK       192000000

void GpioPinSetting(void);
void spim_routine(void);

/*---------------------------------------------------------------------------------------------------------*/
/*  To enter the SPI Flash power-down state                                                                */
/*---------------------------------------------------------------------------------------------------------*/
void SPIM_Enter_PowerDown(void)
{
    /* Enter SPI Flash Power-down */
    SPIM_SET_SS_EN(1);                  /* CS activated. */
    SPIM_ENABLE_SING_OUTPUT_MODE();     /* 1-bit, Output. */
    SPIM->TX[0] = 0xB9;                 /* Power down command. */
    SPIM_ENABLE_SING_INPUT_MODE();      /* 1-bit, Input. */
    SPIM_SET_SS_EN(0);                  /* CS deactivated. */
    printf("Enter SPI Flash Power-down.\n");
}

/*---------------------------------------------------------------------------------------------------------*/
/*  To release the SPI Flash from the power-down state                                                     */
/*---------------------------------------------------------------------------------------------------------*/
void SPIM_Exit_PowerDown(void)
{
    /* Release SPI Flash Power-down */
    SPIM_SET_SS_EN(1);                  /* CS activated. */
    SPIM_ENABLE_SING_OUTPUT_MODE();     /* 1-bit, Output. */
    SPIM->TX[0] = 0xAB;                 /* Release Power down command. */
    SPIM_ENABLE_SING_INPUT_MODE();      /* 1-bit, Input. */
    SPIM_SET_SS_EN(0);                  /* CS deactivated. */
    printf("Release SPI Flash Power-down.\n");
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Function for System Entry to Power Down Mode and Wake up source by GPIO Wake-up pin                    */
/*---------------------------------------------------------------------------------------------------------*/
void WakeUpPinFunction(uint32_t u32PDMode)
{
    SPIM_Enter_PowerDown();
    printf("Enter to SPD%d Power-Down mode......\n", (u32PDMode - 4));

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

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
    SPIM_Enter_PowerDown();
    printf("Enter to SPD%d Power-Down mode......\n", (u32PDMode - 4));

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    /* Select Power-down mode */
    CLK_SetPowerDownMode(u32PDMode);

    /* Set Wake-up Timer Time-out Interval */
    CLK_SET_WKTMR_INTERVAL(u32Interval);

    printf("CLK->PMUCTL = 0x%08x\n", CLK->PMUCTL);
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

    SPIM_Enter_PowerDown();
    printf("Enter to SPD%d Power-Down mode......\n", (u32PDMode - 4));

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

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
    SPIM_Enter_PowerDown();
    printf("Enter to SPD%d Power-Down mode......\n", (u32PDMode - 4));

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    /* enable RTC peripheral clock */
    CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk;
    /* RTC clock source select 32KHz */
    CLK->CLKSEL3 &= ~(CLK_CLKSEL3_RTCSEL_Msk);

    /* Open RTC and start counting */
    RTC->INIT = RTC_INIT_KEY;

    if(RTC->INIT != RTC_INIT_ACTIVE_Msk)
    {
        RTC->INIT = RTC_INIT_KEY;
        while(RTC->INIT != RTC_INIT_ACTIVE_Msk);
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

    /* enable RTC peripheral clock */
    CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk;
    /* RTC clock source select 32KHz */
    CLK->CLKSEL3 &= ~(CLK_CLKSEL3_RTCSEL_Msk);

    /* Open RTC and start counting */
    RTC->INIT = RTC_INIT_KEY;

    if(RTC->INIT != RTC_INIT_ACTIVE_Msk)
    {
        RTC->INIT = RTC_INIT_KEY;
        while(RTC->INIT != RTC_INIT_ACTIVE_Msk);
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
    printf("Enter to SPD%d Power-Down mode......\n", (u32PDMode - 4));

    SPIM_Enter_PowerDown();

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

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
    SPIM_Enter_PowerDown();
    printf("Enter to SPD%d Power-Down mode......\n", (u32PDMode - 4));

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    /* enable RTC peripheral clock */
    CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk;
    /* RTC clock source select 32KHz */
    CLK->CLKSEL3 &= ~(CLK_CLKSEL3_RTCSEL_Msk);

    /* Open RTC and start counting */
    RTC->INIT = RTC_INIT_KEY;

    if(RTC->INIT != RTC_INIT_ACTIVE_Msk)
    {
        RTC->INIT = RTC_INIT_KEY;
        while(RTC->INIT != RTC_INIT_ACTIVE_Msk);
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
    SPIM_Enter_PowerDown();
    printf("Enter to SPD%d Power-Down mode......\n", (u32PDMode - 4));

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

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
    SPIM_Enter_PowerDown();
    printf("Enter to SPD%d Power-Down mode......\n", (u32PDMode - 4));

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

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
        SPIM_Exit_PowerDown();
        if(M32(FLAG_ADDR) == SIGNATURE) {
            printf("System waken-up from SPD0 mode done!\n");
            M32(FLAG_ADDR) = 0;
            printf("Press any key to continue ...\n");
            getchar();
        } else {
            printf("System waken-up from SPD1 mode done!\n");
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

    /* Enable SPIM module clock */
    CLK_EnableModuleClock(SPIM_MODULE);

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set PC multi-function pins for CLKO(PC.13) */
    SYS->GPC_MFPH = (SYS->GPC_MFPH & ~SYS_GPC_MFPH_PC13MFP_Msk) | SYS_GPC_MFPH_PC13MFP_CLKO;

    /* Init SPIM multi-function pins, MOSI(PE.2), MISO(PG.13), CLK(PE.4), SS(PG.11), D3(PE.6), and D2(PE.7) */
    SYS->GPE_MFPL &= ~(SYS_GPE_MFPL_PE2MFP_Msk | SYS_GPE_MFPL_PE4MFP_Msk |
                       SYS_GPE_MFPL_PE6MFP_Msk | SYS_GPE_MFPL_PE7MFP_Msk);
    SYS->GPG_MFPH &= ~(SYS_GPG_MFPH_PG11MFP_Msk | SYS_GPG_MFPH_PG13MFP_Msk);
    SYS->GPE_MFPL |= SYS_GPE_MFPL_PE2MFP_SPIM_MOSI | SYS_GPE_MFPL_PE4MFP_SPIM_CLK |
                     SYS_GPE_MFPL_PE6MFP_SPIM_D3 | SYS_GPE_MFPL_PE7MFP_SPIM_D2;
    SYS->GPG_MFPH |= SYS_GPG_MFPH_PG11MFP_SPIM_SS | SYS_GPG_MFPH_PG13MFP_SPIM_MISO;
    PE->SMTEN |= GPIO_SMTEN_SMTEN4_Msk;

    /* Set SPIM I/O pins as high slew rate up to 80 MHz. */
    PE->SLEWCTL = (PE->SLEWCTL & 0xFFFF0CCF) |
                  (0x1<<GPIO_SLEWCTL_HSREN2_Pos) | (0x1<<GPIO_SLEWCTL_HSREN4_Pos) |
                  (0x1<<GPIO_SLEWCTL_HSREN6_Pos) | (0x1<<GPIO_SLEWCTL_HSREN7_Pos);
    PG->SLEWCTL = (PG->SLEWCTL & 0xF33FFFFF) |
                  (0x1<<GPIO_SLEWCTL_HSREN11_Pos) | (0x1<<GPIO_SLEWCTL_HSREN13_Pos);
}

void UART0_Init(void)
{
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

int main()
{
    uint8_t idBuf[3], u8Item;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Release I/O hold status */
    CLK->IOPDCTL = 1;

    /* Set IO State and all IPs clock disable for power consumption */
    GpioPinSetting();
    CLK->APBCLK1 = 0x00000000;
    CLK->APBCLK0 = 0x00000000;

    SYS_Init(); /* Init System, IP clock and multi-function I/O    */

    /* ---------- Turn off RTC  -------- */
    CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk;
    RTC_WaitAccessEnable();
    RTC->INTEN = 0;
    RTC_Close();

    UART0_Init(); /* Initialize UART0                                */

    printf("\n\nCPU @ %d Hz\n\n", SystemCoreClock);
    CLK_EnableCKO(CLK_CLKSEL1_CLKOSEL_HCLK, 3, 0);

    /* Get power manager wake up source */
    CheckPowerSource();


    SPIM_SET_CLOCK_DIVIDER(1);        /* Set SPIM clock as HCLK divided by 2 */

    SPIM_SET_RXCLKDLY_RDDLYSEL(0);    /* Insert 0 delay cycle. Adjust the sampling clock of received data to latch the correct data. */
    SPIM_SET_RXCLKDLY_RDEDGE();       /* Use SPI input clock rising edge to sample received data. */

    SPIM_SET_DCNUM(8);                /* 8 is the default value. */

    if (SPIM_InitFlash(1) != 0)        /* Initialized SPI flash */
    {
        printf("SPIM flash initialize failed!\n");
        while (1);
    }

    SPIM_ReadJedecId(idBuf, sizeof (idBuf), 1);
    printf("SPIM get JEDEC ID=0x%02X, 0x%02X, 0x%02X\n", idBuf[0], idBuf[1], idBuf[2]);

    SPIM_DISABLE_CCM();

    SPIM_ENABLE_CACHE();

    SPIM_DISABLE_CIPHER();

    SPIM_Enable_4Bytes_Mode(USE_4_BYTES_MODE, 1);

    SPIM->CTL1 |= SPIM_CTL1_CDINVAL_Msk;        // invalid cache

    SPIM_EnterDirectMapMode(USE_4_BYTES_MODE, CMD_DMA_FAST_READ, 0);

    while (1)
    {
        printf("\n\nProgram is currently running on APROM flash.\n");
        printf("Now branch to the sub-routine on SPIM flash...\n");

        spim_routine();

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
    }
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
