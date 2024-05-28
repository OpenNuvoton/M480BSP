/**************************************************************************//**
 * @file     main_loader.c
 * @version  V1.00
 * @brief    Load multi_word_prog.bin image to SRAM and branch to execute it.
 *
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>

#include "NuMicro.h"

#define SRAM_IMAGE_BASE             0x20004000   /* The execution address of multi_word_prog.bin. */

typedef void (FUNC_PTR)(void);

extern uint32_t  loaderImage1Base, loaderImage1Limit;   /* symbol of image start and end */


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

void UART0_Init(void)
{
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}


/*
 *  Set stack base address to SP register.
 */
#ifdef __ARMCC_VERSION                 /* for Keil compiler */
void __set_SP(uint32_t _sp)
{
    __set_MSP(_sp);
}
#endif


int main()
{
#ifdef __GNUC__                        /* for GNU C compiler */
    uint32_t    u32Data;
#endif
    FUNC_PTR    *func;                 /* function pointer */

    SYS_Init();                        /* Init System, IP clock and multi-function I/O */

    UART0_Init();                      /* Initialize UART0 */

    printf("\n\n");
    printf("+---------------------------------------------+\n");
    printf("|    M480 FMC_MultiWordProgram Sample Loader  |\n");
    printf("+---------------------------------------------+\n");

    SYS_UnlockReg();                   /* Unlock register lock protect */

    FMC_Open();                        /* Enable FMC ISP function */

    /* Load multi_word_prog.bin image to SRAM address 0x4000. */
    memcpy((uint8_t *)SRAM_IMAGE_BASE, (uint8_t *)&loaderImage1Base, (uint32_t)&loaderImage1Limit - (uint32_t)&loaderImage1Base);

    /* Get the Reset_Handler entry address of multi_word_prog.bin. */
    func = (FUNC_PTR *)*(uint32_t *)(SRAM_IMAGE_BASE+4);

    /* Get and set the SP (Stack Pointer Base) of multi_word_prog.bin. */
#if defined (__GNUC__) && !defined(__ARMCC_VERSION)    /* for GNU C compiler */
    u32Data = *(uint32_t *)SRAM_IMAGE_BASE;
    asm("msr msp, %0" : : "r" (u32Data));
#else
    __set_SP(*(uint32_t *)SRAM_IMAGE_BASE);
#endif

    /*
     *  Branch to the multi_word_prog.bin's reset handler in way of function call.
     */
    func();

    SYS_LockReg();                     /* Lock protected registers */

    while (1);
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
