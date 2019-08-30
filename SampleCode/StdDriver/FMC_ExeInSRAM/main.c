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

#define SRAM_CODE_EXE_ADDR  0x20010000
#define SRAM_CODE_BASE      0x8000
#define SRAM_CODE_SIZE      0x1000

typedef void (FUNC_PTR)(void);

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
    FUNC_PTR    *func;                 /* function pointer */

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
       This sample code is used to demonstrate how to implement a code to execute in SRAM.
       exeinsram.o is moved to 0x20010000 ~ 0x20010fff and execute there.
    */

    /* Unlock protected registers */
    SYS_UnlockReg();

    printf("Execute demo code in APROM ==>\n");

    FlashAccess_OnSRAM();

    memcpy((uint8_t *)SRAM_CODE_EXE_ADDR, (uint8_t *)SRAM_CODE_BASE, SRAM_CODE_SIZE);

    printf("Execute demo code in SRAM ==>\n");

    func = (FUNC_PTR *)(SRAM_CODE_EXE_ADDR+1);

    func();   /* branch to exeinsram.o in SRAM  */

    /* Lock protected registers */
    SYS_LockReg();

    printf("\nFMC Sample Code Completed.\n");

    while (1);

}

/*** (C) COPYRIGHT 2019 Nuvoton Technology Corp. ***/
