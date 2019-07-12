/***************************************************************************//**
 * @file     spi_transfer.h
 * @brief    ISP tool SPI initialization header file
 * @version  2.0.0
 *
 * Copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __SPI_TRANS_H__
#define __SPI_TRANS_H__
#include <stdint.h>

extern volatile uint8_t bSpiDataReady;
extern uint32_t spi_rcvbuf[];

/*-------------------------------------------------------------*/
void SPI_Init(void);

#endif  /* __SPI_TRANS_H__ */
