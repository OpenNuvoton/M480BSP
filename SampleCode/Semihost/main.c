/******************************************************************************
 * @file     main.c
 * @version  V1.00
 * @brief    Show how to print and get character with IDE console window.
 *
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

/**
 *  @brief  Init system clock and I/O multi function .
 *  @param  None
 *  @return None
 */
void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable External XTAL (4~24 MHz) */
    CLK->PWRCTL |= CLK_PWRCTL_HXTEN_Msk; // HXT Enabled

    while((CLK->STATUS & CLK_STATUS_HXTSTB_Msk) != CLK_STATUS_HXTSTB_Msk) /* Waiting for 12MHz clock ready */

        CLK->CLKSEL0 = (CLK->CLKSEL0 &~ CLK_CLKSEL0_HCLKSEL_Msk) | (CLK_CLKSEL0_HCLKSEL_HXT); /* Switch HCLK clock source to XTAL */

    /* Enable IP clock */


    /* Select IP clock source */


    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    SystemCoreClockUpdate();

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Lock protected registers */
    SYS_LockReg();

}

/**
 *  @brief  main function.
 *  @param  None
 *  @return None
 */
int32_t main()
{
    int8_t item;

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    printf("\n Start SEMIHOST test: \n");

    while(1) {
        item = getchar();
        printf("%c\n",item);
    }

}





/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/



