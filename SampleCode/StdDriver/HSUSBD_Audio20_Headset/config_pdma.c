/***************************************************************************//**
 * @file     config_pdma.c
 * @brief    NuMicro series HSUSBD driver Sample file
 * @version  1.0.0
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
/*!<Includes */
#include <string.h>
#include "NuMicro.h"
#include "usbd_audio.h"

/* DMA scatter-gather descriptor */
DMA_DESC_T DMA_TXDESC[PDMA_TXBUFFER_CNT];
DMA_DESC_T DMA_RXDESC[PDMA_RXBUFFER_CNT];

extern uint32_t PcmPlayBuff[PDMA_TXBUFFER_CNT][BUFF_LEN];
extern uint32_t PcmRecBuff[PDMA_RXBUFFER_CNT][BUFF_LEN];
extern uint8_t u8PcmRxBufFull[PDMA_RXBUFFER_CNT];
extern volatile int8_t i8TxDataCntInBuffer, i8RxDataCntInBuffer;
extern volatile uint8_t u8PDMATxIdx;
extern volatile uint8_t u8PDMARxIdx;

/* PDMA Interrupt handler */
void PDMA_IRQHandler(void)
{
    uint32_t u32Status = PDMA_GET_INT_STATUS(PDMA);

    if (u32Status & 0x1)   /* abort */
    {
        if (PDMA_GET_ABORT_STS(PDMA) & 0x4)
            PDMA_CLR_ABORT_FLAG(PDMA,PDMA_ABTSTS_ABTIF2_Msk);
    }
    else if (u32Status & 0x2)
    {
        if (PDMA_GET_TD_STS(PDMA) & 0x2)            /* channel 1 done, Tx */
        {
            PDMA_CLR_TD_FLAG(PDMA,PDMA_TDSTS_TDIF1_Msk);

            /* Decrease number of full buffer */
            i8TxDataCntInBuffer--;
            if (i8TxDataCntInBuffer <= 0)
                i8TxDataCntInBuffer = 0;

            /* Change to next buffer */
            u8PDMATxIdx ++;
            if(u8PDMATxIdx >= PDMA_TXBUFFER_CNT)
                u8PDMATxIdx = 0;
        }
        if (PDMA_GET_TD_STS(PDMA) & 0x4)            /* channel 2 done, Rx */
        {

            PDMA_CLR_TD_FLAG(PDMA,PDMA_TDSTS_TDIF2_Msk);

            /* Set PCM buffer full flag */
            u8PcmRxBufFull[u8PDMARxIdx] = 1;
            i8RxDataCntInBuffer++;
            if (i8RxDataCntInBuffer > PDMA_RXBUFFER_CNT)
                i8RxDataCntInBuffer = 8;

            /* Change to next buffer */
            u8PDMARxIdx ++;
            if(u8PDMARxIdx >= PDMA_RXBUFFER_CNT)
                u8PDMARxIdx = 0;
        }
    }
}

// Configure PDMA to Scatter Gather mode */
void PDMA_Init(void)
{
    PDMA_WriteTxSGTable();
    PDMA_WriteRxSGTable();

    /* Open PDMA channel 1 for I2S TX and channel 2 for I2S RX */
    PDMA_Open(PDMA,(1 << PDMA_I2S_TX_CH) | (1 << PDMA_I2S_RX_CH));

    /* We want to enable these channels at run time */
    PDMA->CHCTL = 0;

    /* Configure PDMA transfer mode */
    PDMA_SetTransferMode(PDMA,PDMA_I2S_TX_CH, PDMA_I2S0_TX, 1, (uint32_t)&DMA_TXDESC[0]);
    PDMA_SetTransferMode(PDMA,PDMA_I2S_RX_CH, PDMA_I2S0_RX, 1, (uint32_t)&DMA_RXDESC[0]);

    /* Enable PDMA channel 1&2 interrupt */
    PDMA_EnableInt(PDMA,PDMA_I2S_TX_CH, 0);
    PDMA_EnableInt(PDMA,PDMA_I2S_RX_CH, 0);

    /* Enable PDMA interrupt */
    NVIC_EnableIRQ(PDMA_IRQn);
}

/* init TX scatter-gather table */
void PDMA_WriteTxSGTable(void)
{
    uint16_t i;

    /* Use PDMA_TXBUFFER_CNT scatter-gather tables and link with each other */
    for(i=0; i<PDMA_TXBUFFER_CNT; i++)
    {
        DMA_TXDESC[i].ctl = ((u32BuffLen-1)<<PDMA_DSCT_CTL_TXCNT_Pos)|PDMA_WIDTH_32|PDMA_SAR_INC|PDMA_DAR_FIX|PDMA_REQ_SINGLE|PDMA_OP_SCATTER;
        DMA_TXDESC[i].src = (uint32_t)&PcmPlayBuff[i];
        DMA_TXDESC[i].dest = (uint32_t)&I2S0->TXFIFO;

        if(i!=PDMA_TXBUFFER_CNT-1)
            DMA_TXDESC[i].offset = (uint32_t)&DMA_TXDESC[i+1] - (PDMA->SCATBA);
        else
            DMA_TXDESC[i].offset = (uint32_t)&DMA_TXDESC[0] - (PDMA->SCATBA);
    }
}

/* init RX scatter-gather table */
void PDMA_WriteRxSGTable(void)
{
    uint16_t i;

    /* Use PDMA_RXBUFFER_CNT scatter-gather tables and link with each other */
    for(i=0; i<PDMA_RXBUFFER_CNT; i++)
    {
        DMA_RXDESC[i].ctl = ((u32RxBuffLen-1)<<PDMA_DSCT_CTL_TXCNT_Pos)|PDMA_WIDTH_32|PDMA_SAR_FIX|PDMA_DAR_INC|PDMA_REQ_SINGLE|PDMA_OP_SCATTER;
        DMA_RXDESC[i].src = (uint32_t)&I2S0->RXFIFO;
        DMA_RXDESC[i].dest = (uint32_t)&PcmRecBuff[i];

        if(i != (PDMA_RXBUFFER_CNT-1))
            DMA_RXDESC[i].offset = (uint32_t)&DMA_RXDESC[i+1] - (PDMA->SCATBA);
        else
            DMA_RXDESC[i].offset = (uint32_t)&DMA_RXDESC[0] - (PDMA->SCATBA);
    }
}


