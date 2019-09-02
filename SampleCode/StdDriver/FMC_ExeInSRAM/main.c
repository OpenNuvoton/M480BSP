/****************************************************************************//**
 * @file     main.c
 * @version  V0.10
 * @brief    Implement a code and execute in SRAM to program embedded Flash.
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

extern int32_t FlashAccess_OnSRAM(void);

void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Switch HCLK clock source to HXT */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HXT,CLK_CLKDIV0_HCLK(1));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Lock protected registers */
    SYS_LockReg();
}

int32_t main(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O. */
    SYS_Init();

    /* Configure UART5: 115200, 8-bit word, no parity bit, 1 stop bit. */
    UART_Open(UART0, 115200);

    printf("\n\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|      FMC Write/Read code execute in SRAM Sample Code      |\n");
    printf("+-----------------------------------------------------------+\n");

    /*
       This sample code demonstrates how to make a sub-routine code executed in SRAM.
    */

    printf("Will branch to address: 0x%x\n", (uint32_t)FlashAccess_OnSRAM);

    FlashAccess_OnSRAM();

    printf("\nFMC Sample Code Completed.\n");

    while (1);

}

/*** (C) COPYRIGHT 2019 Nuvoton Technology Corp. ***/
