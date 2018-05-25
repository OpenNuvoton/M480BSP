/**************************************************************************//**
 * @file     sprom.c
 * @version  V1.00
 * @brief    Collect of sub-routines running on SPROM.
 *
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>

#include "NuMicro.h"

/*
 *  Put a character to UART0 transmitter
 */
void sprom_putc(int ch)
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
char sprom_getc(void)
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
void sprom_put_string(char *str)
{
    while (*str)
    {
        sprom_putc(*str++);
    }
}

void sprom_routine(void)
{
    sprom_put_string("\n\n\n");
    sprom_put_string("+----------------------------------------+\n");
    sprom_put_string("|  Program is now running on SPROM.      |\n");
    sprom_put_string("+----------------------------------------+\n\n");

    sprom_put_string("\nPress any to return to APROM main program...\n");

    sprom_getc();
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
