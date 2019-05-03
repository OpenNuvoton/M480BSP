/*************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Demonstrate ETM trace data using 'NuMaker-ETM-M487' Board.
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK           192000000

uint32_t g_u32SysTickIntCnt = 0;
uint32_t g_u32exeCnt = 0;

void SysTick_Handler(void)
{
    g_u32SysTickIntCnt++;

    if( g_u32SysTickIntCnt == 1000) {
        g_u32exeCnt = 0;
        g_u32SysTickIntCnt = 0;
        PH0 ^= 1;
    }
}

void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable External XTAL (4~24 MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for 12MHz clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);
    /* Set PCLK0/PCLK1 to HCLK/2 */
    CLK->PCLKDIV = (CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2);

    /* Enable UART clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART clock source from HXT */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);
    /* Lock protected registers */
    SYS_LockReg();
}


void C(void)
{
    g_u32exeCnt++;
}

void B(void)
{
    g_u32exeCnt++;
    C();
}

void A(void)
{
    g_u32exeCnt++;
    B();
}

int main()
{
    /* Init System, IP clock and multi-function I/O
       In the end of SYS_Init() will issue SYS_LockReg()
       to lock protected register. If user want to write
       protected register, please issue SYS_UnlockReg()
       to unlock protected register if necessary */
    SYS_Init();

    /* Init UART to 115200-8n1 for print message */
    UART_Open(UART0, 115200);

    /* Configure PH.0 as Output mode for LED blink */
    GPIO_SetMode(PH, BIT0, GPIO_MODE_OUTPUT);

    /* SysTick 1m second interrupts  */
    SysTick_Config(SystemCoreClock / 1000);

    /* Running A(), B() and C() in the debugging session to capture ETM trace data with a NuTrace window */
    while(1) {
        A();
        B();
        C();
        printf("g_u32exeCnt = %d\n", g_u32exeCnt);
    }
}

/*** (C) COPYRIGHT 2019 Nuvoton Technology Corp. ***/
