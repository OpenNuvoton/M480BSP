/**************************************************************************//**
 * @file     Sensor_HM01B0.c
 * @version  V1.00
 * @brief    HM01B0 sensor driver
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "i2c_gpio.h"

struct NT_RegValue
{
    uint16_t    u16RegAddr;            /* Sensor Register Address */
    uint8_t        u8Value;            /* Sensor Register Data */
};


/* HM01B0_RAW8_QQVGA_4bits_msb_1fps  */
static struct NT_RegValue g_HM01B0_RegValue[]=
{
    /* Initial */
    {0x0103,0x00},
    {0x0100,0x00},
    /* Horizontal Mirror */
    //{0x0101,0x01},
    /* Digital function */
    //BLC
    {0x1000,0x43},
    {0x1001,0x40},
    {0x1002,0x32},
    // Dgain
    {0x0350,0x7F},
    //BLI
    {0x1006,0x01},
    //DPC
    {0x1008,0x00},
    {0x1009,0xA0},
    {0x100A,0x60},
    {0x100B,0x90},
    {0x100C,0x40},
    {0x1012,0x00},
    //ROI Statistic
    {0x2000,0x07},
    {0x2003,0x00},
    {0x2004,0x1C},
    {0x2007,0x00},
    {0x2008,0x58},
    {0x200B,0x00},
    {0x200C,0x7A},
    {0x200F,0x00},
    {0x2010,0xB8},
    {0x2013,0x00},
    {0x2014,0x58},
    {0x2017,0x00},
    {0x2018,0x9B},
    //AE
    {0x2100,0x01},
    {0x2104,0x07},
    {0x2105,0x3E},
    {0x2106,0x58},
//    {0x2105,0x03},
//    {0x2106,0xA4},
    {0x2108,0x03},
    {0x2109,0x03},
    {0x210B,0x80},
    {0x210F,0x00},
    {0x2110,0x85},
    {0x2111,0x00},
    {0x2112,0xA0},
//    {0x2110,0xE9},
//    {0x2111,0x01},
//    {0x2112,0x17},
    //MD
    {0x2150,0x03},

//    /* Frame rate : 1FPS */
//    {0x0340,0x3E},
//    {0x0341,0x5A},
//    {0x0342,0x01},
//    {0x0343,0x78},
    /* Frame rate : 30FPS */
    {0x0340,0x03},
    {0x0341,0xA6},
    {0x0342,0x00},
    {0x0343,0xD7},
    /* Resolution : QVGA 324x244 */
    {0x3010,0x01},
    {0x0383,0x01},
    {0x0387,0x01},
    {0x0390,0x00},
//    /* Resolution : QQVGA 162x122 */
//    {0x3010,0x01},
//    {0x0383,0x03},
//    {0x0387,0x03},
//    {0x0390,0x03},

    /* bit width Selection */
    {0x3011,0x70},
    {0x3059,0x42},
    {0x3060,0x11}, //PCLK Setting

    /* CMU update */
    {0x0104,0x01},
    /* Turn on rolling shutter */
    {0x0100,0x01}
};

static void Delay(uint32_t nCount)
{
    volatile uint32_t i;
    for(; nCount!=0; nCount--)
        for(i=0; i<100; i++);
}

int InitHM01B0_4BIT_YUV422(void)
{
    uint32_t i;
    uint8_t HM01B0_Addr0 = 0x24;
    uint8_t u8DeviceID=(HM01B0_Addr0<<1);
    uint8_t u8ID[2]= {0};
    SYS->GPD_MFPH &= ~SYS_GPD_MFPH_PD9MFP_Msk;        /* PD9 for GPIO to act as SCL */
    SYS->GPD_MFPH &= ~SYS_GPD_MFPH_PD8MFP_Msk;        /* PD8 for GPIO to act as SDA */

    /* switch I2C pin function */
    SWI2C_Open(eDRVGPIO_GPIOD,eDRVGPIO_PIN9,eDRVGPIO_GPIOD,eDRVGPIO_PIN8,Delay);
    printf("HM01B0_RegNum=%3d\n",sizeof(g_HM01B0_RegValue)/sizeof(struct NT_RegValue));
    for(i=0; i<sizeof(g_HM01B0_RegValue)/sizeof(struct NT_RegValue); i++)
    {
        SWI2C_Write_8bitSlaveAddr_16bitReg_8bitData(u8DeviceID,g_HM01B0_RegValue[i].u16RegAddr,g_HM01B0_RegValue[i].u8Value);
        if(g_HM01B0_RegValue[i].u16RegAddr == 0x0103) Delay(0x1000);
    }
    u8ID[0]=SWI2C_Read_8bitSlaveAddr_16bitReg_8bitData(u8DeviceID,0x0); /* Chip_Version_H 0x01 */
    Delay(10);
    u8ID[1]=SWI2C_Read_8bitSlaveAddr_16bitReg_8bitData(u8DeviceID,0x1); /* Chip_Version_L 0xb0 */
    printf("Sensor Chip_Version_H = 0x%02X(0x01) Chip_Version_L = 0x%02X(0xB0)\n", u8ID[0],u8ID[1]);
    if(u8ID[0]!=0x01 || u8ID[1]!=0xB0 )
    {
        printf("HM01B0 init failed!!\n");
        return 0;
    }
    return 1;
}




