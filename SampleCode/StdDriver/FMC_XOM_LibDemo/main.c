
/******************************************************************************
 * @file     main.c
 * @version  V3.00
 * $Revision: 3 $
 * $Date: 16/10/17 2:06p $
 * @brief    This sample shows a solution of calling the library reside in an XOM region.
 * @note
 * Copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "xom_lib.h"


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


int32_t main(void)
{
    int32_t    result;
    int32_t    NumArray[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O. */
    SYS_Init();


    /* Configure UART0: 115200, 8-bit word, no parity bit, 1 stop bit. */
    UART_Open(UART0, 115200);

    /*
        This sample code is used to show how to call the library in XOM.
        The XOM library is built by FMC_XOM_Lib project.

        Note:
        The library image must be downloaded to XOM region before calling it.
    */

    printf("\n\n");
    printf("+-------------------------------------------+\n");
    printf("|  Demo how to use a library in XOM         |\n");
    printf("+-------------------------------------------+\n");

    /* Run XOM function */
    printf("\n");
    XOM_func(XOM_FUNC_ADD, 100, 200, &result);
    printf(" 100 + 200 = %d\n", result);
    XOM_func(XOM_FUNC_SUB, 500, 100, &result);
    printf(" 500 - 100 = %d\n", result);
    XOM_func(XOM_FUNC_MUL, 200, 100, &result);
    printf(" 200 * 100 = %d\n", result);
    XOM_func(XOM_FUNC_DIV, 1000, 250, &result);
    printf("1000 / 250 = %d\n", result);

    printf("\n");
    XOM_func(XOM_FUNC_SUM, (int32_t)NumArray, 10, &result);
    printf("1 + 2 +..+ 10 = %d\n", result);

    while(1);
}

/*** (C) COPYRIGHT 2019 Nuvoton Technology Corp. ***/


