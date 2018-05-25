/*************************************************************************//**
 * @file     isr.c
 * @version  V0.10
 * @brief    M480 ISR source file
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

#include "config.h"

extern volatile uint8_t aPCMBuffer_Full[2];
volatile uint8_t u8PCMBuffer_Playing=0;

void PDMA_IRQHandler(void)
{
    uint32_t u32Status = PDMA_GET_INT_STATUS(PDMA);

    if (u32Status & 0x2)   /* done */
    {
        if (PDMA_GET_TD_STS(PDMA) & 0x4)
        {
            if(aPCMBuffer_Full[u8PCMBuffer_Playing^1] != 1)
                printf("underflow!!\n");
            aPCMBuffer_Full[u8PCMBuffer_Playing] = 0;       //set empty flag
            u8PCMBuffer_Playing ^= 1;
        }
        PDMA_CLR_TD_FLAG(PDMA,PDMA_TDSTS_TDIF2_Msk);
    }
    else if(u32Status & 0x400)     /* Timeout */
    {
        PDMA_CLR_TMOUT_FLAG(PDMA,PDMA_TDSTS_TDIF2_Msk);
        printf("PDMA Timeout!!\n");
    }
    else
    {
        printf("0x%x\n", u32Status);
        while(1);
    }
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
