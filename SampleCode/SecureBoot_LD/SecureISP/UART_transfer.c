/**************************************************************************//**
 * @file     UART_transfer.c
 * @version  V3.00
 * @brief    Secure ISP - UART1 source file
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"
#include "SecureISP.h"


int32_t ProcessUART1Interrupt(uint32_t *pInfo)
{
    volatile uint32_t   INTSTS, data_idx;
    volatile ISP_INFO_T *pISPInfo;
    uint8_t  *rcvbuf;

    pISPInfo = (ISP_INFO_T *)pInfo;

    data_idx = pISPInfo->UARTDataIdx;

    INTSTS = UART1->INTSTS;

    rcvbuf = (uint8_t *)pISPInfo->rcvbuf;

    if(INTSTS & (UART_INTSTS_RDAIF_Msk | UART_INTSTS_RXTOIF_Msk))
    {
        //RDA FIFO interrupt & RDA timeout interrupt
        while(((UART1->FIFOSTS & UART_FIFOSTS_RXEMPTY_Msk) == 0) && (data_idx < MAX_PKT_SIZE)) //RX fifo not empty
        {
            rcvbuf[data_idx++] = UART1->DAT;
            pISPInfo->UARTDataIdx = data_idx;
        }
    }

    if(pISPInfo->UARTDataIdx == MAX_PKT_SIZE)
    {
        pISPInfo->IsUARTDataReady = TRUE;
        pISPInfo->UARTDataIdx     = 0;
    }
    else if(INTSTS & UART_INTSTS_RXTOIF_Msk)
    {
        pISPInfo->UARTDataIdx = 0;
    }

    return 0;
}

/*---------------------------------------------------------------------------------------------------------*/
/* ISR to handle UART Channel 0 interrupt event                                                            */
/*---------------------------------------------------------------------------------------------------------*/
void PutString(uint8_t *pu8Buf)
{
    volatile uint32_t   i;

    for(i = 0; i < MAX_PKT_SIZE; i++)
    {
        while((UART1->FIFOSTS & UART_FIFOSTS_TXFULL_Msk));
        UART1->DAT = pu8Buf[i];
    }
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
