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
    spim_put_string("+-----------------------------------------------------------------+\n");
    spim_put_string("|  Program is now running on SPIM flash.                          |\n");
    spim_put_string("+-----------------------------------------------------------------+\n");
    spim_put_string("|    SPD Power-down Mode and Wake-up Sample Code                  |\n");
    spim_put_string("|    Please Select Power Down Mode and Wake up source.            |\n");
    spim_put_string("+-----------------------------------------------------------------+\n");
    spim_put_string("|[1] SPD0 GPIO Wake-up pin(PA.0) and using rising edge wake up.   |\n");
    spim_put_string("|[2] SPD0 Wake-up TIMER time-out interval is 1024 OSC10K clocks.  |\n");
    spim_put_string("|[3] SPD0 Wake-up by ACMP0.(band-gap voltage)                     |\n");
    spim_put_string("|[4] SPD0 Wake-up by RTC Tick.                                    |\n");
    spim_put_string("|[5] SPD0 Wake-up by RTC Alarm.                                   |\n");
    spim_put_string("|[6] SPD0 Wake-up by RTC Tamper0(PF.6), Low level.                |\n");
    spim_put_string("|[7] SPD0 Wake-up by BOD.                                         |\n");
    spim_put_string("|[8] SPD0 Wake-up by LVR.                                         |\n");
    spim_put_string("|[a] SPD1 GPIO Wake-up pin(PA.0) and using rising edge wake up.   |\n");
    spim_put_string("|[b] SPD1 Wake-up TIMER time-out interval is 1024 OSC10K clocks.  |\n");
    spim_put_string("|[c] SPD1 Wake-up by ACMP0.(band-gap voltage)                     |\n");
    spim_put_string("|[d] SPD1 Wake-up by RTC Tick.                                    |\n");
    spim_put_string("|[e] SPD1 Wake-up by RTC Alarm.                                   |\n");
    spim_put_string("|[f] SPD1 Wake-up by RTC Tamper0(PF.6), Low level.                |\n");
    spim_put_string("|[g] SPD1 Wake-up by BOD.                                         |\n");
    spim_put_string("|[h] SPD1 Wake-up by LVR.                                         |\n");
    spim_put_string("+-----------------------------------------------------------------+\n");

    spim_put_string("Return to APROM...\n\n");

}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
