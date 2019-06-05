/*************************************************************************//**
 * @file     queue.c
 * @version  V1.00
 * @brief    A simple implementation of LwIP pbuf queue
 *
 * @note    All queue operating must execute with interrupt disabled
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

#include "lwip/tcpip.h"

#define QUEUE_CNT   32

struct pbuf *q[QUEUE_CNT];
static uint32_t u32Qhead = 0;  // put to here
static uint32_t u32Qtail = 0;  // get from here

uint32_t queue_try_put(struct pbuf *p)
{
    uint32_t i = u32Qhead + 1;
    if(i == QUEUE_CNT)
        i = 0;
    if(i == u32Qtail)
        return 0;
    q[u32Qhead] = p;
    u32Qhead = i;

    return 1;
}

struct pbuf *queue_try_get(void)
{
    struct pbuf *p;

    if(u32Qhead == u32Qtail)
        return NULL;

    p = q[u32Qtail];
    u32Qtail++;
    if(u32Qtail == QUEUE_CNT)
        u32Qtail = 0;
    return p;

}



/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
