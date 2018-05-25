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

static uint32_t PcmBuff[32] = {0};
extern uint32_t volatile u32BuffPos;

void I2S0_IRQHandler(void)
{
    uint32_t u32Reg;
    uint32_t u32Len, i;
    uint32_t *pBuffTx, *pBuffRx;

    // enable sound output
    PA4 = 0;

    u32Reg = I2S_GET_INT_FLAG(I2S0, I2S_STATUS0_TXTHIF_Msk | I2S_STATUS0_RXTHIF_Msk);

    if (u32Reg & I2S_STATUS0_TXTHIF_Msk)
    {
        pBuffTx = &PcmBuff[0];

        /* Read Tx FIFO free size */
        u32Len = 8 - I2S_GET_TX_FIFO_LEVEL(I2S0);

        if (u32BuffPos >= 8)
        {
            for (i = 0; i < u32Len; i++)
            {
                I2S_WRITE_TX_FIFO(I2S0, pBuffTx[i]);
            }

            for (i = 0; i < BUFF_LEN - u32Len; i++)
            {
                pBuffTx[i] = pBuffTx[i + u32Len];
            }

            u32BuffPos -= u32Len;
        }
        else
        {
            for (i = 0; i < u32Len; i++)
            {
                I2S_WRITE_TX_FIFO(I2S0, 0x00);
            }
        }
    }

    if (u32Reg & I2S_STATUS0_RXTHIF_Msk)
    {
        if (u32BuffPos < (BUFF_LEN-8))
        {
            pBuffRx = &PcmBuff[u32BuffPos];

            /* Read Rx FIFO Level */
            u32Len = I2S_GET_RX_FIFO_LEVEL(I2S0);

            for ( i = 0; i < u32Len; i++ )
            {
                pBuffRx[i] = I2S_READ_RX_FIFO(I2S0);
            }

            u32BuffPos += u32Len;

            if (u32BuffPos >= BUFF_LEN)
            {
                u32BuffPos =    0;
            }
        }
    }
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
