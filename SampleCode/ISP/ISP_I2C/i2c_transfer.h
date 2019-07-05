/**************************************************************************//**
 * @file     i2c_transfer.h
 * @brief    ISP support function header file
 * @version  0x32
 * @date     14, June, 2017
 *
 * @note
 * Copyright (C) 2017-2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __I2C_TRANS_H__
#define __I2C_TRANS_H__
#include <stdint.h>

extern volatile uint8_t bI2cDataReady;
extern uint8_t i2c_rcvbuf[];

/*-------------------------------------------------------------*/
void I2C_Init(void);

#endif  /* __I2C_TRANS_H__ */
