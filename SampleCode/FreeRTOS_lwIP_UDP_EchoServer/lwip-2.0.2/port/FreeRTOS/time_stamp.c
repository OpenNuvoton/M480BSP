/*
 * Copyright (c) 2012 Nuvoton Technology Corp.
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 *
 * Description:   PTP hardware time stamping hardware abstract layer
 */
#include "lwip/opt.h"
#include "lwip/def.h"
#include "lwip/time_stamp.h"
#include "netif/m480_eth.h"

#ifdef TIME_STAMPING

u32_t ts_init(struct ts_timeval *t)
{

    ETH_TS_ENABLE();
    ETH_settime(t->sec, t->nsec);
    ETH_adjtimex(0);
    ETH_setinc();
    ETH_TS_START();

    return 0;
}


u32_t ts_update(struct ts_timeval *t)
{
    if(t->sec < 0) {
        ETH_updatetime(1, -t->sec, t->nsec);
    } else if(t->nsec < 0) {
        ETH_updatetime(1, t->sec, -t->nsec);
    } else
        ETH_updatetime(0, t->sec, t->nsec);
    return 0;
}

u32_t ts_settime(struct ts_timeval *t)
{

    ETH_updatetime(0, t->sec, t->nsec);
    return 0;
}

u32_t ts_gettime(struct ts_timeval *t)
{
    ETH_gettime((u32_t *)&t->sec, (u32_t *)&t->nsec);
    return 0;

}

u32_t ts_adjtimex(s32_t ppb)
{
    ETH_adjtimex(ppb);
    return 0;

}


#endif
