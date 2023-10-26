/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Demonstrate how to minimize power consumption when entering power down mode.
 *
 * @copyright (C) 2023 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK       192000000

/*
//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
*/

/*
// <o0> Power-down Mode
//      <0=> PD
//      <1=> LLPD
//      <2=> FWPD
//      <4=> SPD0
//      <5=> SPD1
//      <6=> DPD
*/
#define SET_PDMSEL       6

/*
// <o0> POR
//      <0=> Disable
//      <1=> Enable
*/
#define SET_POR       0

/*
// <o0> LIRC
//      <0=> Disable
//      <1=> Enable
*/
#define SET_LIRC       0

/*
// <o0> LXT
//      <0=> Disable
//      <1=> Enable
*/
#define SET_LXT       0

#define GPIO_P0_TO_P15      0xFFFF

void GpioPinSetting(void);

/**
 * @brief       GPIO PC IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The PC default IRQ, declared in startup_M480.s.
 */
void GPC_IRQHandler(void)
{
    volatile uint32_t u32temp;

    /* To check if PC.0 interrupt occurred */
    if(GPIO_GET_INT_FLAG(PC, BIT0))
    {
        GPIO_CLR_INT_FLAG(PC, BIT0);
        printf("PC.0 INT occurred.\n");
    }
    else
    {
        /* Un-expected interrupt. Just clear all PC interrupts */
        u32temp = PC->INTSRC;
        PC->INTSRC = u32temp;
        printf("Un-expected interrupts.\n");
    }
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Function for System Entry to Power Down Mode                                                           */
/*---------------------------------------------------------------------------------------------------------*/
void PowerDownFunction(void)
{
    uint32_t u32TimeOutCnt;

    /* Check if all the debug messages are finished */
    u32TimeOutCnt = SystemCoreClock; /* 1 second time-out */
    UART_WAIT_TX_EMPTY(UART0)
    if(--u32TimeOutCnt == 0) break;

    /* Select Power-down mode */
    CLK_SetPowerDownMode((SET_PDMSEL<< CLK_PMUCTL_PDMSEL_Pos));

    /* Enter to Power-down mode */
    CLK_PowerDown();
}

void PorSetting(void)
{
    if(SET_POR == 0)
    {
        SYS_DISABLE_POR();
    }
    else
    {
        SYS_ENABLE_POR();
    }
}

int32_t LircSetting(void)
{
    uint32_t u32TimeOutCnt;

    if(SET_LIRC == 0)
    {
        CLK_DisableXtalRC(CLK_PWRCTL_LIRCEN_Msk);
        u32TimeOutCnt = SystemCoreClock; /* 1 second time-out */
        while( CLK->STATUS & CLK_STATUS_LIRCSTB_Msk )
        {
            if(--u32TimeOutCnt == 0)
            {
                printf("Wait for LIRC disable time-out!\n");
                return -1;
            }
        }
    }
    else
    {
        CLK_EnableXtalRC(CLK_PWRCTL_LIRCEN_Msk);
        if( CLK_WaitClockReady(CLK_PWRCTL_LIRCEN_Msk) == 0)
        {
            printf("Wait for LIRC enable time-out!\n");
            return -1;
        }
    }

    return 0;
}

int32_t LxtSetting(void)
{
    uint32_t u32TimeOutCnt;

    if(SET_LXT == 0)
    {
        CLK_DisableXtalRC(CLK_PWRCTL_LXTEN_Msk);
        u32TimeOutCnt = SystemCoreClock; /* 1 second time-out */
        while( CLK->STATUS & CLK_STATUS_LXTSTB_Msk )
        {
            if(--u32TimeOutCnt == 0)
            {
                printf("Wait for LXT disable time-out!\n");
                return -1;
            }
        }
    }
    else
    {
        CLK_EnableXtalRC(CLK_PWRCTL_LXTEN_Msk);
        if( CLK_WaitClockReady(CLK_PWRCTL_LXTEN_Msk) == 0)
        {
            printf("Wait for LXT enable time-out!\n");
            return -1;
        }
    }

    return 0;
}

/*------------------------------------------------------------------------------------------------------*/
/*  Function for System Entry to SPD0 or SPD1 and Wake up source by GPIO Wake-up pin (PC.0)             */
/*------------------------------------------------------------------------------------------------------*/
void SPD_WakeUpPinFunction(uint32_t u32PDMode)
{
    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)
        printf("Enter to SPD%d Power-Down mode......\n", (u32PDMode - 4));
    else
        printf("Enter to SPD Power-Down mode......\n");

    /* Check if all the debug messages are finished */
    UART_WAIT_TX_EMPTY(UART0);

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) != 0x0)
    {
        /* Set IO State and all IPs clock disable for power consumption */
        GpioPinSetting();
        /* PC.0 Pull-up Enable */
        GPIO_SetPullCtl(PC, 0, GPIO_PUSEL_PULL_UP);
    }

    /* Configure GPIO as Input mode */
    GPIO_SetMode(PC, BIT0, GPIO_MODE_INPUT);

    // GPIO SPD Power-down Wake-up Pin Select and Debounce Disable
    CLK_EnableSPDWKPin(2, 0, CLK_SPDWKPIN_RISING, CLK_SPDWKPIN_DEBOUNCEDIS);
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Function for System Entry to Power Down Mode and Wake up source by Wake-up pin (PC.0)                  */
/*---------------------------------------------------------------------------------------------------------*/
void DPD_WakeUpPinFunction(uint32_t u32EdgeType)
{
    printf("Enter to DPD Power-Down mode......\n");

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    /* Select Power-down mode */
    CLK_SetPowerDownMode(CLK_PMUCTL_PDMSEL_DPD);

    /* Configure GPIO as Input mode */
    GPIO_SetMode(PC, BIT0, GPIO_MODE_INPUT);

    // Set Wake-up pin trigger type at Deep Power down mode
    CLK_EnableDPDWKPin(u32EdgeType);

    /* Enter to Power-down mode */
    CLK_PowerDown();

    /* Wait for Power-down mode wake-up reset happen */
    while(1);
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

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1) {
        /* Set PF multi-function pins for TAMPER0(PF.6) */
        SYS->GPF_MFPL = (SYS->GPF_MFPL & (~SYS_GPF_MFPL_PF6MFP_Msk)) | SYS_GPF_MFPL_PF6MFP_TAMPER0;
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
    SYS->GPF_MFPL = 0x000000EE; // exclude ICE pin
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

    /*
        To measure Power-down current on NuMaker-M483KG board.
    */
    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) != 0x0)
    {
      PA->DOUT = PA->DOUT & ~(1 << 12);
      PB->DOUT = PB->DOUT & ~(1 << 15);
      PF->DOUT = PF->DOUT & ~(1 << 2);
    }
}

void UART0_Init()
{
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{
    uint32_t u32TimeOutCnt, u32PMUSTS;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set GPF6~7 pull-up when VBAT mode */
    /* PF4(X32_OUT), PF5(X32_IN) unnecessary set pull-up */
    RTC->GPIOCTL0 |= (0x1 << RTC_GPIOCTL0_PUSEL2_Pos) | (0x1 << RTC_GPIOCTL0_PUSEL3_Pos);
    /* Set GPF8~11 pull-up when VBAT mode */
    RTC->GPIOCTL1 |= (0x1 << RTC_GPIOCTL1_PUSEL4_Pos) | (0x1 << RTC_GPIOCTL1_PUSEL5_Pos) |
    (0x1 << RTC_GPIOCTL1_PUSEL6_Pos) | (0x1 << RTC_GPIOCTL1_PUSEL7_Pos);

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

    //printf("     ======  SYS->CSERVER:0x%x, CLK->IOPDCTL:0x%x, CLK->PMUCTL:0x%08x\n", SYS->CSERVER, CLK->IOPDCTL, CLK->PMUCTL);

    /* Clear SPD/DPD mode wake-up status for enterning SPD/DPD mode again */
    u32PMUSTS = CLK_GetPMUWKSrc();
    if( CLK->PMUSTS )
    {
        /* Release I/O hold status for SPD mode */
        CLK->IOPDCTL = 1;

        /* Clear SPD/DPD mode wake-up status */
        CLK->PMUSTS |= CLK_PMUSTS_CLRWK_Msk;

        u32TimeOutCnt = SystemCoreClock; /* 1 second time-out */
        while(CLK->PMUSTS)
        {
            if(--u32TimeOutCnt == 0)
            {
                printf("Wait for SPD/DPD mode wake-up status is cleared time-out!\n");
                goto lexit;
            }
        }
    }

    /* PC.0 falling-edge wake-up event */
    if( u32PMUSTS & (CLK_PMUSTS_PINWK_Msk | CLK_PMUSTS_GPCWK_Msk) )
    {
        printf("SPD/DPD waken-up done.\n\n");
        while(1);
    }

    printf("\n\nCPU @ %d Hz\n", SystemCoreClock);
    printf("+-------------------------------------------------------------------+\n");
    printf("|  SYS_PowerDown_MinCurrent and Wake-up by PC.0 Sample Code         |\n");
    printf("+-------------------------------------------------------------------+\n\n");

    printf("+-------------------------------------------------------------------+\n");
    printf("| Operating sequence                                                |\n");
    printf("|  1. Remove all continuous load, e.g. LED.                         |\n");
    printf("|  2. Configure all GPIO as Quasi-bidirectional Mode                |\n");
    printf("|  3. Disable analog function, e.g. POR module                      |\n");
    printf("|  4. Disable unused clock, e.g. LIRC                               |\n");
    printf("|  5. Disable SRAM retention for SPD mode                           |\n");
    printf("|  6. Enter to Power-Down                                           |\n");
    printf("|  7. Wait for PC.0 rising-edge interrupt event to wake-up the MCU  |\n");
    printf("+-------------------------------------------------------------------+\n\n");

    /*
        To measure Power-down current, remove component, e.g. NuMaker-M487 board,
        Nu-Link2-Me, UP1 LDO, UP2 LDO, U2 HyperRAM, U7 Ethernet PHY and U9 Audio codec.
    */

    /* Check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    /* Configure all GPIO as Quasi-bidirectional Mode */
    GPIO_SetMode(PA, GPIO_P0_TO_P15, GPIO_MODE_QUASI);
    GPIO_SetMode(PB, GPIO_P0_TO_P15, GPIO_MODE_QUASI);
    GPIO_SetMode(PC, GPIO_P0_TO_P15, GPIO_MODE_QUASI);
    GPIO_SetMode(PD, GPIO_P0_TO_P15, GPIO_MODE_QUASI);
    GPIO_SetMode(PE, GPIO_P0_TO_P15, GPIO_MODE_QUASI);
    GPIO_SetMode(PF, GPIO_P0_TO_P15, GPIO_MODE_QUASI);
    GPIO_SetMode(PG, GPIO_P0_TO_P15, GPIO_MODE_QUASI);
    GPIO_SetMode(PH, GPIO_P0_TO_P15, GPIO_MODE_QUASI);

    /* POR setting */
    PorSetting();

    /* LIRC setting */
    if( LircSetting() < 0 ) goto lexit;

    /* LXT setting */
    if( LxtSetting() < 0 ) goto lexit;

    /* Wake-up source configuraion */
    if( ( SET_PDMSEL == 0 ) ||
        ( SET_PDMSEL == 1 ) ||
        ( SET_PDMSEL == 2 ) )
    {
        /* Configure PC.0 as Input mode and enable interrupt by rising edge trigger */
        GPIO_SetMode(PC, BIT0, GPIO_MODE_INPUT);
        GPIO_EnableInt(PC, 0, GPIO_INT_RISING);
        NVIC_EnableIRQ(GPC_IRQn);
    }
    else if( SET_PDMSEL == 4 )
    {
        SPD_WakeUpPinFunction(CLK_PMUCTL_PDMSEL_SPD0);
    }
    else if( SET_PDMSEL == 5 )
    {
        SPD_WakeUpPinFunction(CLK_PMUCTL_PDMSEL_SPD1);
    }
    else if( SET_PDMSEL == 6 )
    {
        DPD_WakeUpPinFunction(CLK_DPDWKPIN_RISING);
    }
    else
    {
        printf("Unknown Power-down mode!\n");
        goto lexit;
    }

    /* Enter to Power-down mode */
    if( SET_PDMSEL == 0 )      printf("Enter to PD Power-Down ......\n");
    else if( SET_PDMSEL == 1 ) printf("Enter to LLPD Power-Down ......\n");
    else if( SET_PDMSEL == 2 ) printf("Enter to FWPD Power-Down ......\n");

    PowerDownFunction();

    /* Waiting for pin rising-edge interrupt event */
    printf("System waken-up done.\n\n");

lexit:

    while(1);
}

/*** (C) COPYRIGHT 2023 Nuvoton Technology Corp. ***/
