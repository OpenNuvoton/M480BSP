/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Show how to enter to different Power-down mode and wake-up by RTC.
 *
 * @copyright (C) 2023 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include "stdio.h"
#include "NuMicro.h"


#define PDMD_FLAG_ADDR  0x20000FFC
#define PLL_CLOCK       192000000

/*---------------------------------------------------------------------------------------------------------*/
/* Global Interface Variables Declarations                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
static uint32_t s_u32PowerDownMode;
static volatile uint32_t s_au32TMRINT;

/**
 * @brief       IRQ Handler for TIMER Interrupt
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The TMR0_IRQHandler is default IRQ of TIMER, declared in startup_m480.s.
 */
void TMR0_IRQHandler(void)
{
    /* To check if TIMER tick interrupt occurred */
    if((TIMER_GetIntFlag(TIMER0) == 1) && (TIMER_GetWakeupFlag(TIMER0) == 1))
    {
        /* Clear Timer0 wake up flag */
        TIMER_ClearWakeupFlag(TIMER0);

        /* Clear Timer0 time-out interrupt flag */
        TIMER_ClearIntFlag(TIMER0);

        s_au32TMRINT++;
    }
}

/*-----------------------------------------------------------------------------------------------------------*/
/*  Function for System Entry to Power Down Mode and Wake up source by TIMER Time-out                        */
/*-----------------------------------------------------------------------------------------------------------*/
int32_t TIMER_Init(void)
{
    /* Clear TIMER0 interrupt flag */
    TIMER_ClearIntFlag(TIMER0);

    /* Open Timer0 in periodic mode, enable interrupt and 1 interrupt tick per second */
    TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 1);

    /* Enable Timer wake up system */
    TIMER_EnableWakeup(TIMER0);

    /* Enable Timer0 interrupt */
    TIMER_EnableInt(TIMER0);

    /* Enable Timer0 NVIC */
    NVIC_EnableIRQ(TMR0_IRQn);

    /* Set Wake-up Timer  Time-out Interval wake-up from SPD and DPD */
    CLK_SET_WKTMR_INTERVAL(CLK_PMUCTL_WKTMRIS_16384);

    /* Start Timer0 counting */
    TIMER_Start(TIMER0);

    /* Enable Wake-up Timer */
    CLK_ENABLE_WKTMR();

    return 0;
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Function for System Entry to Power Down Mode                                                           */
/*---------------------------------------------------------------------------------------------------------*/
void PowerDownFunction(void)
{
    /* Select Power-down mode */
    CLK_SetPowerDownMode(s_u32PowerDownMode);

    switch(s_u32PowerDownMode)
    {
        case CLK_PMUCTL_PDMSEL_SPD0:
        case CLK_PMUCTL_PDMSEL_SPD1:
        case CLK_PMUCTL_PDMSEL_DPD:
            /* Set Wake-up Timer Time-out wake-up from SPD and DPD */
            CLK_SET_WKTMR_INTERVAL(CLK_PMUCTL_WKTMRIS_16384);

            /* Enable Wake-up Timer */
            CLK_ENABLE_WKTMR();
            break;
    }

    /* To check if all the debug messages are finished */
    while(!UART_IS_TX_EMPTY(UART0));

    /* Enter to Power-down mode */
    CLK_PowerDown();
}

/*-----------------------------------------------------------------------------------------------------------*/
/*  Function for Check Power Manager Status                                                                  */
/*-----------------------------------------------------------------------------------------------------------*/
int32_t CheckPowerSource(void)
{
    /* Get Power Manager Status */
    uint32_t u32Status = CLK_GetPMUWKSrc();

    /* Clear wake-up status flag */
    CLK->PMUSTS = CLK_PMUSTS_CLRWK_Msk;

    /* Check Power Manager Status is wake-up by Wake-up Timer */
    if(u32Status & CLK_PMUSTS_TMRWK_Msk)
    {
        s_u32PowerDownMode = M32(PDMD_FLAG_ADDR);
        switch(s_u32PowerDownMode)
        {

            case CLK_PMUCTL_PDMSEL_PD:

                /* It is the start of sample code by pressing reset button */
                printf("\n\nCPU @ %dHz\n", SystemCoreClock);
                printf("+------------------------------------------+\n");
                printf("|    Power-down and Wake-up Sample Code    |\n");
                printf("+------------------------------------------+\n");
                break;

            case CLK_PMUCTL_PDMSEL_SPD0:
            case CLK_PMUCTL_PDMSEL_SPD1:

                /* Wake-up from Standby Power-down Mode */
                printf("Wake-up!\n");

                /* Next Power-down Mode is Deep Power-down Mode */
                M32(PDMD_FLAG_ADDR) = CLK_PMUCTL_PDMSEL_DPD;
                break;

            default:

                /* Wake-up from Deep Power-down Mode */
                printf("Wake-up!\n");

                /* End of sample code and clear Power-down Mode flag */
                printf("\nSample code end. Press Reset Button and continue.\n");
                M32(PDMD_FLAG_ADDR) = 0;
                return 1;

        }
    }

    return 0;
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

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);

    /* Enable UART clock */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(TMR0_MODULE);

    /* Select UART clock source from HIRC */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_LIRC, 0);

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

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{
    uint32_t u32TimeOutCnt;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Release I/O hold status */
    CLK->IOPDCTL = 1;

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1) {
        CLK->PMUCTL |= CLK_PMUCTL_DPDHOLDEN_Msk;
    }

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    /* Enable Clock Output function, output clock is stopped in Power-down mode */
    CLK_EnableCKO(CLK_CLKSEL1_CLKOSEL_HCLK, 3, 0);

    /* Get power manager wake up source */
    if( CheckPowerSource() != 0)
        goto lexit;

    /* TIMER wake-up source setting */
    if( TIMER_Init() < 0 )
        goto lexit;

    /*
        This sample code will enter to different Power-down mode and wake-up by RTC:
        1. Normal Power-down mode (PD).
        2. Low Leakage Power-down mode (LLPD).
        3. Fast Wake-up Power-down mode (FWPD).
        4. Standby Power-down mode (SPD).
        5. Deep Power-down mode (DPD).
    */
    while(1)
    {

        /* Select Power-down mode */
        s_u32PowerDownMode = M32(PDMD_FLAG_ADDR);
        switch(s_u32PowerDownMode)
        {
            case CLK_PMUCTL_PDMSEL_PD:
                printf("\nSystem enters to PD power-down mode ... ");
                break;
            case CLK_PMUCTL_PDMSEL_LLPD:
                printf("\nSystem enters to LLPD power-down mode ... ");
                break;
            case CLK_PMUCTL_PDMSEL_FWPD:
                printf("\nSystem enters to FWPD power-down mode ... ");
                break;
            case CLK_PMUCTL_PDMSEL_SPD0:
                printf("\nSystem enters to SPD power-down mode ... ");
                break;
            case CLK_PMUCTL_PDMSEL_SPD1:
                printf("\nSystem enters to SPD power-down mode ... ");
                break;
            case CLK_PMUCTL_PDMSEL_DPD:
                printf("\nSystem enters to DPD power-down mode ... ");
                break;
            default:
                printf("\nInit sample code. Press Reset Button and continue.\n");
                M32(PDMD_FLAG_ADDR) = 0;
                goto lexit;
                //break;
        }

        /* Unlock protected registers before setting Power-down mode */
        SYS_UnlockReg();

        /* Enter to Power-down mode */
        PowerDownFunction();
        u32TimeOutCnt = SystemCoreClock; /* 1 second time-out */
        while(s_au32TMRINT == 0)
        {
            if(--u32TimeOutCnt == 0)
            {
                printf("Wait for TIMER interrupt time-out!");
                break;
            }
        }
        printf("Wake-up!\n");

        /* Select next Power-down mode */
        switch(s_u32PowerDownMode)
        {
            case CLK_PMUCTL_PDMSEL_PD:
                M32(PDMD_FLAG_ADDR) = CLK_PMUCTL_PDMSEL_LLPD;
                break;
            case CLK_PMUCTL_PDMSEL_LLPD:
                M32(PDMD_FLAG_ADDR) = CLK_PMUCTL_PDMSEL_FWPD;
                break;
            case CLK_PMUCTL_PDMSEL_FWPD:
                M32(PDMD_FLAG_ADDR) = CLK_PMUCTL_PDMSEL_SPD0;
                break;
            default:
                printf("\nInit sample code. Press Reset Button and continue.\n");
                M32(PDMD_FLAG_ADDR) = 0;
                goto lexit;
        }
    }

lexit:

    while(1);
}

