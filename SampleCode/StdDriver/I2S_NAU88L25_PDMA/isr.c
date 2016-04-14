/******************************************************************************
 * @file     isr.c
 * @version  V0.10
 * $Revision: 2 $
 * $Date: 14/06/09 9:35a $
 * @brief    M480 series ISR source file
 *
 * @note
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "M480.h"

#include "config.h"

extern uint32_t PcmRxBuff[2][BUFF_LEN];
extern uint32_t PcmTxBuff[2][BUFF_LEN];
volatile uint8_t u8TxIdx=0, u8RxIdx=0;

extern uint32_t volatile u32BuffPos;

void PDMA_IRQHandler(void)
{
    uint32_t u32Status = PDMA_GET_INT_STATUS();

    if (u32Status & 0x2) {
        if (PDMA_GET_TD_STS() & 0x4) {          /* channel 2 done */
            /* Copy RX data to TX buffer */
            memcpy(&PcmTxBuff[u8TxIdx^1], &PcmRxBuff[u8RxIdx], BUFF_LEN*4);
            u8RxIdx ^= 1;
        }

        if (PDMA_GET_TD_STS() & 0x2) {          /* channel 1 done */
            u8TxIdx ^= 1;
        }
        PDMA_CLR_TD_FLAG(PDMA_TDSTS_TDIF1_Msk);
        PDMA_CLR_TD_FLAG(PDMA_TDSTS_TDIF2_Msk);
    } else
        printf("unknown interrupt, status=0x%x!!\n", u32Status);
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
