/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    This sample shows how to make an application booting from APROM
 *           with a sub-routine resided on SPIM flash.
 *           Show how to wake up system form DPD Power-down mode by
 *           Wake-up pin(PC.0) or Wake-up Timer.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define USE_4_BYTES_MODE    0            /* W25Q20 does not support 4-bytes address mode. */

#define PLL_CLOCK       192000000

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
/*  Function for System Entry to Power Down Mode and Wake up source by Wake-up pin                         */
/*---------------------------------------------------------------------------------------------------------*/
void WakeUpPinFunction(uint32_t u32PDMode, uint32_t u32EdgeType)
{
    SPIM_Enter_PowerDown();
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
    SPIM_Enter_PowerDown();
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

    if(u32RegRstsrc)
        SPIM_Exit_PowerDown();

    printf("\n");
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

    /* Set PF multi-function pins for TAMPER0(PF.6) */
    SYS->GPF_MFPL = (SYS->GPF_MFPL & (~SYS_GPF_MFPL_PF6MFP_Msk)) | SYS_GPF_MFPL_PF6MFP_TAMPER0;
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

    /* Set IO State and all IPs clock disable for power consumption */
    GpioPinSetting();

    CLK->APBCLK1 = 0x00000000;
    CLK->APBCLK0 = 0x00000000;

    /* ---------- Turn off RTC  -------- */
    CLK->APBCLK0 |= CLK_APBCLK0_RTCCKEN_Msk;
    RTC_WaitAccessEnable();
    RTC->INTEN = 0;
    CLK->APBCLK0 &= ~CLK_APBCLK0_RTCCKEN_Msk;

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Init UART0 for printf */
    UART0_Init();

    printf("\n\nCPU @ %d Hz\n", SystemCoreClock);
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

        switch(u8Item)
        {
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
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
