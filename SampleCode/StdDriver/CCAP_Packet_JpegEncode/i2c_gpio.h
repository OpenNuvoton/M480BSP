/**************************************************************************//**
 * @file     i2c_gpio.h
 * @version  V1.00
 * $Revision: 2 $
 * $Date: 14/05/29 1:14p $
 * @brief    Software I2C driver
 *
 * @note
 * Copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef _I2C_GPIO_H_
#define _I2C_GPIO_H_
#include "NuMicro.h"

#ifdef  __cplusplus
extern "C"
{
#endif

#define     REG_GPIOA_OMD        0x40004000
#define     REG_GPIOA_DOUT       0x40004008
#define     REG_GPIOA_PIN        0x40004010
#define     REG_GPIOA_PUEN       0x40004014

#define E_SWI2C_WRITE_FAIL             0xFFFF0001
#define E_SWI2C_PIN_UNAVAILABLE        0xFFFF0002

// Acknowledgment type
#define DrvI2C_Ack_No        0
#define DrvI2C_Ack_Have        1

#define _SWI2C_SCK_SETHIGH(PortIndex, PinMask)       outp32(REG_GPIOA_DOUT+(PortIndex),inp32(REG_GPIOA_DOUT+(PortIndex))|PinMask)
#define _SWI2C_SCK_SETLOW(PortIndex, PinMask)        outp32(REG_GPIOA_DOUT+(PortIndex),inp32(REG_GPIOA_DOUT+(PortIndex))&(~PinMask))
#define _SWI2C_SDA_SETHIGH(PortIndex, PinMask)       outp32(REG_GPIOA_DOUT+(PortIndex),inp32(REG_GPIOA_DOUT+(PortIndex))|PinMask)
#define _SWI2C_SDA_SETLOW(PortIndex, PinMask)        outp32(REG_GPIOA_DOUT+(PortIndex),inp32(REG_GPIOA_DOUT+(PortIndex))&(~PinMask))

#define _SWI2C_SCK_GETVALUE(PortIndex, PinMask)     (inp32(REG_GPIOA_PIN+(PortIndex))&PinMask)
#define _SWI2C_SDA_GETVALUE(PortIndex, PinMask)     (inp32(REG_GPIOA_PIN+(PortIndex))&PinMask)

typedef void (*PFN_SWI2C_TIMEDELY)(uint32_t);
typedef struct
{
    uint32_t u32SCKPortIndex;
    uint32_t u32SCKPinMask;
    uint32_t u32SDAPortIndex;
    uint32_t u32SDAPinMask;
} S_I2C_Channel;

typedef enum
{
    eDRVGPIO_GPIOA = 0x00,
    eDRVGPIO_GPIOB = 0x40,
    eDRVGPIO_GPIOC = 0x80,
    eDRVGPIO_GPIOD = 0xC0,
    eDRVGPIO_GPIOE = 0x100,
    eDRVGPIO_GPIOF = 0x140,
    eDRVGPIO_GPIOG = 0x180,
    eDRVGPIO_GPIOH = 0x1C0,
    eDRVGPIO_GPIOI = 0x200,
    eDRVGPIO_GPIOJ = 0x240,
} E_DRVGPIO_PORT;
typedef enum
{
    eDRVGPIO_PIN0 = (1),
    eDRVGPIO_PIN1 = (1<<1),
    eDRVGPIO_PIN2 = (1<<2),
    eDRVGPIO_PIN3 = (1<<3),
    eDRVGPIO_PIN4 = (1<<4),
    eDRVGPIO_PIN5 = (1<<5),
    eDRVGPIO_PIN6 = (1<<6),
    eDRVGPIO_PIN7 = (1<<7),
    eDRVGPIO_PIN8 = (1<<8),
    eDRVGPIO_PIN9 = (1<<9),
    eDRVGPIO_PIN10 = (1<<10),
    eDRVGPIO_PIN11 = (1<<11),
    eDRVGPIO_PIN12 = (1<<12),
    eDRVGPIO_PIN13 = (1<<13),
    eDRVGPIO_PIN14 = (1<<14),
    eDRVGPIO_PIN15 = (1<<15)
} E_DRVGPIO_BIT;


// Define function

int SWI2C_Open(uint32_t u32SCKPortIndex,uint32_t u32SCKPinMask,uint32_t u32SDAPortIndex,
               uint32_t u32SDAPinMask,PFN_SWI2C_TIMEDELY pfntimedelay);
void SWI2C_Close(void);
void SWI2C_SendStart(void);
void SWI2C_SendStop(void);
int SWI2C_WriteByte(uint8_t u8Data, uint8_t u8AckType,uint8_t u8Length);
uint32_t SWI2C_ReadByte(uint8_t u8AckType,uint8_t u8Length);
uint8_t SWI2C_Slave_ReadByte(uint8_t u8AckType);
uint32_t SWI2C_GetVersion(void);


/* For OV7725 */
uint8_t SWI2C_Write_8bitSlaveAddr_8bitReg_8bitData(uint8_t uAddr, uint8_t uRegAddr, uint8_t uData);
uint8_t SWI2C_Read_8bitSlaveAddr_8bitReg_8bitData(uint8_t uAddr, uint8_t uRegAddr);


/* For NT99141 */
uint8_t SWI2C_Write_8bitSlaveAddr_16bitReg_8bitData(uint8_t uAddr, uint16_t uRegAddr, uint8_t uData);
uint8_t SWI2C_Read_8bitSlaveAddr_16bitReg_8bitData(uint8_t uAddr, uint16_t uRegAddr);


#ifdef __cplusplus
}
#endif

#endif









