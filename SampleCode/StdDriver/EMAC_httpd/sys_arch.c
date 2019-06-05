/*************************************************************************//**
 * @file     sys_arch.c
 * @version  V1.00
 * @brief    System functions for LwIP
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

#include "lwip/tcpip.h"

static uint32_t u32Jiffies = 0;

void TMR0_IRQHandler(void)
{
    u32Jiffies += 10;
    TIMER_ClearIntFlag(TIMER0);

}

u32_t sys_now(void)
{

    return u32Jiffies;

}

uint32_t sys_arch_protect(void)
{
    uint32_t mask = __get_PRIMASK();
    __disable_irq();
    return mask;
}

void sys_arch_unprotect(uint32_t mask)
{
    __set_PRIMASK(mask);
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
