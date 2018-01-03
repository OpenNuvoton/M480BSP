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
/*  Function for Check Power Manager Status                                                                  */
/*-----------------------------------------------------------------------------------------------------------*/
void CheckPowerSource(void)
{
    unsigned int uRegRstsrc;
    uRegRstsrc = CLK_GetPMUWKSrc();

    printf("Power manager Power Manager Status 0x%x\n", uRegRstsrc);

    if((uRegRstsrc & CLK_PMUSTS_TMRWK_Msk) != 0)
        printf("Wake-up source is Wake-up Timer.\n");
    if((uRegRstsrc & CLK_PMUSTS_PINWK_Msk) != 0)
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
    /* Disable HXT and LXT clock */
    CLK_DisableXtalRC(CLK_PWRCTL_HXTEN_Msk | CLK_PWRCTL_LXTEN_Msk);

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

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set GPD multi-function pins for UART0 RXD and TXD */
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD2MFP_Msk | SYS_GPD_MFPL_PD3MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD2MFP_UART0_RXD | SYS_GPD_MFPL_PD3MFP_UART0_TXD);

    /* Set PC multi-function pins for CLKO(PC.13) */
    SYS->GPC_MFPH = (SYS->GPC_MFPH & ~SYS_GPC_MFPH_PC13MFP_Msk) | SYS_GPC_MFPH_PC13MFP_CLKO;

}

void UART0_Init()
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{
    uint8_t u8Item;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set IO State and all IPs clock disable for power consumption */
    GpioPinSetting();

    CLK->APBCLK1 = 0x00000000;
    CLK->APBCLK0 = 0x00000000;

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
    printf("+----------------------------------------------------------------+\n");
    u8Item = getchar();

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

    while(1);
}

