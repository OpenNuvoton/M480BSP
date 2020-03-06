/**************************************************************************//**
 * @file     spim_code.c
 * @version  V1.00
 * @brief    Collect of sub-routines running on SPIM flash.
 *
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include <stdio.h>

#include "NuMicro.h"

/*
 *  Put a character to UART0 transmitter
 */
void spim_putc(int ch)
{
    while (UART0->FIFOSTS & UART_FIFOSTS_TXFULL_Msk) ;
    UART0->DAT = ch;
    if (ch == '\n')
    {
        while(UART0->FIFOSTS & UART_FIFOSTS_TXFULL_Msk);
        UART0->DAT = '\r';
    }
}

/*
 *  Poll until received a character from UART0 receiver
 */
char spim_getc(void)
{
    while(1)
    {
        if ((UART0->FIFOSTS & UART_FIFOSTS_RXEMPTY_Msk) == 0)
        {
            return (UART0->DAT);
        }
    }
}

/*
 *  print out a string
 */
void spim_put_string(char *str)
{
    while (*str)
    {
        spim_putc(*str++);
    }
}

void spim_routine(void)
{
    spim_put_string("\n\n\n");
    spim_put_string("+------------------------------------------+\n");
    spim_put_string("|  Program is now running on SPIM flash.   |\n");
    spim_put_string("+------------------------------------------+\n\n");
    spim_put_string("Return to APROM...\n\n");
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
