/**************************************************************************//**
 * @file     i2c_gpio.c
 * @version  V1.00
 * @brief    Software I2C driver
 *
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdlib.h>
#include "i2c_gpio.h"
#include "NuMicro.h"


//-------------------
// I2C functions
//-------------------

static S_I2C_Channel s_sChannel;
static PFN_SWI2C_TIMEDELY pfntimedelay=NULL;

void _SWI2C_SDA_SETIN(uint32_t PortIndex, uint32_t PinMask)
{
    //PinMask = 1, 2, 4, 8, ..., 0x8000.
    uint32_t u32pin = 0;
    uint32_t u32Idx = 1;
    uint32_t u32ModMask;
    for(u32pin=0; u32pin<16; u32pin=u32pin+1)
    {
        if(PinMask == u32Idx)
        {
            break;
        }
        u32Idx = u32Idx << 1;
    }
    u32ModMask = 3 <<(u32pin*2);
    outp32(REG_GPIOA_OMD+(PortIndex),inp32(REG_GPIOA_OMD+(PortIndex))&(~u32ModMask));
}
void _SWI2C_SCK_SETOUT(uint32_t PortIndex, uint32_t PinMask)
{
    uint32_t u32pin = 0;
    uint32_t u32Idx = 1;
    uint32_t u32ModMask, u32Out;
    for(u32pin=0; u32pin<16; u32pin=u32pin+1)
    {
        if(PinMask == u32Idx)
        {
            break;
        }
        u32Idx = u32Idx << 1;
    }
    u32ModMask = 3 <<(u32pin*2);
    u32Out = 1 <<(u32pin*2);
    outp32(REG_GPIOA_OMD+(PortIndex),(inp32(REG_GPIOA_OMD+(PortIndex))&(~u32ModMask))| u32Out);
}
void _SWI2C_SDA_SETOUT(uint32_t PortIndex, uint32_t PinMask)
{
    uint32_t u32pin = 0;
    uint32_t u32Idx = 1;
    uint32_t u32ModMask, u32Out;
    for(u32pin=0; u32pin<16; u32pin=u32pin+1)
    {
        if(PinMask == u32Idx)
        {
            break;
        }
        u32Idx = u32Idx << 1;
    }
    u32ModMask = 3 <<(u32pin*2);
    u32Out = 1 <<(u32pin*2);
    outp32(REG_GPIOA_OMD+(PortIndex),(inp32(REG_GPIOA_OMD+(PortIndex))&(~u32ModMask))|u32Out);
}
static void _SWI2C_Delay(
    uint32_t nCount
)
{
    volatile uint32_t i;
    if (pfntimedelay!=NULL)
    {
        pfntimedelay(nCount);
    }
    else
    {
        for(; nCount!=0; nCount--)
            for(i=0; i<200; i++);
    }
}
int
SWI2C_Open(
    uint32_t u32SCKPortIndex,
    uint32_t u32SCKPinMask,
    uint32_t u32SDAPortIndex,
    uint32_t u32SDAPinMask,
    PFN_SWI2C_TIMEDELY pfn_SWI2C_Delay
)
{
    // switch pin function
    s_sChannel.u32SCKPortIndex    = u32SCKPortIndex;
    s_sChannel.u32SCKPinMask     = u32SCKPinMask;
    s_sChannel.u32SDAPortIndex    = u32SDAPortIndex;
    s_sChannel.u32SDAPinMask     = u32SDAPinMask;

    // 1.Check I/O pins. If I/O pins are used by other IPs, return error code.
    // 2.Enable IP clock
    // 3.Reset IP
    // 4.Configure IP according to inputted arguments.
    // 5.Enable IP I/O pins
    // eq:GPIOB pin1, pin2 as output mode ( DRVGPIO_PIN1 | DRVGPIO_PIN2)
    // eq:Let clock pin and data pin to be high

    _SWI2C_SCK_SETOUT(s_sChannel.u32SCKPortIndex, s_sChannel.u32SCKPinMask );
    _SWI2C_SDA_SETOUT(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask );
    _SWI2C_SCK_SETHIGH(s_sChannel.u32SCKPortIndex, s_sChannel.u32SCKPinMask);
    _SWI2C_SDA_SETHIGH(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);
    _SWI2C_Delay(5);
    _SWI2C_SCK_SETLOW(s_sChannel.u32SCKPortIndex, s_sChannel.u32SCKPinMask);
    _SWI2C_SDA_SETLOW(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);
    _SWI2C_Delay(5);
    _SWI2C_SCK_SETHIGH(s_sChannel.u32SCKPortIndex, s_sChannel.u32SCKPinMask);
    _SWI2C_SDA_SETHIGH(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);

    pfntimedelay=pfn_SWI2C_Delay;
    // 6.Return 0 to present success
    return 0;

}    //DrvI2C_Open()

void SWI2C_Close(void)
{
    // 1.Disable IP I/O pins
    // 2.Disable IP clock
}



void SWI2C_SendStart(void)
{
    // Assert start bit
    _SWI2C_SDA_SETOUT(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);
    _SWI2C_SDA_SETHIGH(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);        // serial data pin high
    _SWI2C_Delay(2);
    _SWI2C_SCK_SETHIGH(s_sChannel.u32SCKPortIndex, s_sChannel.u32SCKPinMask);        // serial clock pin high
    _SWI2C_Delay(2);
    _SWI2C_SDA_SETLOW(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);        // serial data pin low
    _SWI2C_Delay(2);
    _SWI2C_SCK_SETLOW(s_sChannel.u32SCKPortIndex, s_sChannel.u32SCKPinMask);        // serial clock pin low
    _SWI2C_Delay(2);
}

void SWI2C_SendStop(void)
{
#if 0
    _SWI2C_SDA_SETOUT(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);
    _SWI2C_SDA_SETLOW(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);        // serial data pin low
    _SWI2C_SCK_SETHIGH(s_sChannel.u32SCKPortIndex, s_sChannel.u32SCKPinMask);        // serial clock pin high
#else
    // Assert stop bit
    _SWI2C_Delay(10);
    _SWI2C_SDA_SETOUT(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);
    _SWI2C_SDA_SETLOW(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);        // serial data pin low
    _SWI2C_Delay(2);
    _SWI2C_SCK_SETHIGH(s_sChannel.u32SCKPortIndex, s_sChannel.u32SCKPinMask);        // serial clock pin high
    _SWI2C_Delay(2);
    _SWI2C_SDA_SETHIGH(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);        // serial data pin high
    _SWI2C_Delay(2);
    //DrvI2cDisable(s_sChannel.u32EnablePortIndex, s_sChannel.u32EnablePinMask);
#endif
}

//-------------------------
//master write bytes to slave device
int
SWI2C_WriteByte(
    uint8_t u8Data,
    uint8_t u8AckType,
    uint8_t u8Length
)
{
    uint8_t   u8DataCount;
    uint32_t     i32HoldPinValue;
    _SWI2C_SDA_SETOUT(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);
    // Write data to device and the most signification bit(MSB) first
    for ( u8DataCount=0; u8DataCount<u8Length; u8DataCount++ )
    {
        if ( u8Data&0x80 )
            _SWI2C_SDA_SETHIGH(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);
        else
            _SWI2C_SDA_SETLOW(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);
        _SWI2C_Delay(3);
        _SWI2C_SCK_SETHIGH(s_sChannel.u32SCKPortIndex, s_sChannel.u32SCKPinMask);
        u8Data<<=1;
        _SWI2C_Delay(2);
        _SWI2C_SCK_SETLOW(s_sChannel.u32SCKPortIndex, s_sChannel.u32SCKPinMask);
        _SWI2C_Delay(2);
    }

    // No Ack
    if ( u8AckType == DrvI2C_Ack_No )
        return 0;

    // Have a Ack
    // Wait Device Ack bit
    _SWI2C_SDA_SETLOW(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);
    _SWI2C_SDA_SETIN(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);
    _SWI2C_Delay(3);
    _SWI2C_SCK_SETHIGH(s_sChannel.u32SCKPortIndex, s_sChannel.u32SCKPinMask);
    _SWI2C_Delay(2);
    i32HoldPinValue = _SWI2C_SDA_GETVALUE(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);
    _SWI2C_SCK_SETLOW(s_sChannel.u32SCKPortIndex, s_sChannel.u32SCKPinMask);
    _SWI2C_Delay(2);
    return (i32HoldPinValue == 0 ?E_SWI2C_WRITE_FAIL: 0);
}

//-------------------------------
//master read bytes data from slave device
uint32_t
SWI2C_ReadByte(
    uint8_t u8AckType,
    uint8_t u8Length
)
{
    uint32_t   u32Data=0;
    uint8_t    u8DataCount;

    _SWI2C_SDA_SETIN(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);
    // Read data from slave device and the most signification bit(MSB) first
    for ( u8DataCount=0; u8DataCount<u8Length; u8DataCount++ )
    {
        u32Data = u32Data<<1;
        _SWI2C_Delay(3);
        _SWI2C_SCK_SETHIGH(s_sChannel.u32SCKPortIndex, s_sChannel.u32SCKPinMask);
        if (_SWI2C_SDA_GETVALUE(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask)==s_sChannel.u32SDAPinMask)
            u32Data = u32Data|0x01;
        _SWI2C_Delay(2);
        _SWI2C_SCK_SETLOW(s_sChannel.u32SCKPortIndex, s_sChannel.u32SCKPinMask);
        _SWI2C_Delay(2);
    }
    // No write Ack
    if ( u8AckType == DrvI2C_Ack_No )
        return u32Data;

    // Have a Ack
    // write a ACK bit to slave device
    _SWI2C_SDA_SETOUT(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);
    _SWI2C_SDA_SETHIGH(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);
    _SWI2C_Delay(3);
    _SWI2C_SCK_SETHIGH(s_sChannel.u32SCKPortIndex, s_sChannel.u32SCKPinMask);
    _SWI2C_Delay(2);
    _SWI2C_SCK_SETLOW(s_sChannel.u32SCKPortIndex, s_sChannel.u32SCKPinMask);
    _SWI2C_Delay(2);
    _SWI2C_SDA_SETLOW(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);
    return u32Data;
}

//-------------------------------
//slave read one byte data from master device
uint8_t
SWI2C_Slave_ReadByte(
    uint8_t u8AckType
)
{
    uint8_t u8Data, u8DataCount;
    u8Data = 0;
    // Read data from device and the most signification bit(MSB) first
    for ( u8DataCount=0; u8DataCount<8;  )
    {
        if (_SWI2C_SCK_GETVALUE(s_sChannel.u32SCKPortIndex, s_sChannel.u32SCKPinMask)==0)
        {
            _SWI2C_Delay(3);

            if (_SWI2C_SCK_GETVALUE(s_sChannel.u32SCKPortIndex, s_sChannel.u32SCKPinMask)==s_sChannel.u32SCKPinMask)
            {

                u8Data = u8Data<<1;
                if ( _SWI2C_SDA_GETVALUE(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask)==s_sChannel.u32SDAPinMask )
                    u8Data = u8Data|0x01;

                u8DataCount++;
            }
        }
    }
    //  No Ack
    if ( u8AckType == DrvI2C_Ack_No )
        return u8Data;
    // Assert ACK bit

    _SWI2C_Delay(2);
    _SWI2C_SDA_SETOUT(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);
    _SWI2C_SDA_SETHIGH(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);
    _SWI2C_Delay(7);
    _SWI2C_SDA_SETIN(s_sChannel.u32SDAPortIndex, s_sChannel.u32SDAPinMask);
    return u8Data;
}


//=====================================================================================
static void Delay(uint32_t nCount)
{
    volatile uint32_t i;
    for(; nCount!=0; nCount--)
        for(i=0; i<100; i++);
}

/* for OV7725 */
uint8_t SWI2C_Write_8bitSlaveAddr_8bitReg_8bitData(uint8_t uAddr, uint8_t uRegAddr, uint8_t uData)
{
    // 3-Phase(ID address, register address, data(8bits)) write transmission
    volatile uint8_t u32Delay = 0x50;
    SWI2C_SendStart();
    while(u32Delay--);
    if ( (SWI2C_WriteByte(uAddr,DrvI2C_Ack_Have,8)==FALSE) ||            // Write ID address to sensor
            (SWI2C_WriteByte(uRegAddr,DrvI2C_Ack_Have,8)==FALSE) ||    // Write register address to sensor
            (SWI2C_WriteByte(uData,DrvI2C_Ack_Have,8)==FALSE) )        // Write data to sensor
    {
        SWI2C_SendStop();
        return FALSE;
    }
    SWI2C_SendStop();

    if (uRegAddr==0x12 && (uData&0x80)!=0)
    {
        Delay(1000);
    }
    return TRUE;
}

/* for OV7725 */
uint8_t SWI2C_Read_8bitSlaveAddr_8bitReg_8bitData(uint8_t uAddr, uint8_t uRegAddr)
{
    uint8_t u8Data;

    // 2-Phase(ID address, register address) write transmission
    SWI2C_SendStart();
    SWI2C_WriteByte(uAddr,DrvI2C_Ack_Have,8);        // Write ID address to sensor
    SWI2C_WriteByte(uRegAddr,DrvI2C_Ack_Have,8);    // Write register address to sensor
    SWI2C_SendStop();

    // 2-Phase(ID-address, data(8bits)) read transmission
    SWI2C_SendStart();
    SWI2C_WriteByte(uAddr|0x01,DrvI2C_Ack_Have,8);        // Write ID address to sensor
    u8Data = SWI2C_ReadByte(DrvI2C_Ack_Have,8);        // Read data from sensor
    SWI2C_SendStop();

    return u8Data;
}

/* for NT99141 */
uint8_t SWI2C_Read_8bitSlaveAddr_16bitReg_8bitData(uint8_t uAddr, uint16_t uRegAddr)
{
    uint8_t u8Data;

    // 2-Phase(ID address, register address) write transmission
    SWI2C_SendStart();
    SWI2C_WriteByte(uAddr,DrvI2C_Ack_Have,8);        // Write ID address to sensor
    SWI2C_WriteByte(uRegAddr>>8,DrvI2C_Ack_Have,8);      // Write register addressH to sensor
    SWI2C_WriteByte(uRegAddr&0xFF,DrvI2C_Ack_Have,8);    // Write register addressL to sensor
    //DrvI2C_SendStop();

    // 2-Phase(ID-address, data(8bits)) read transmission
    SWI2C_SendStart();
    SWI2C_WriteByte(uAddr|0x01,DrvI2C_Ack_Have,8);        // Write ID address to sensor
    u8Data = SWI2C_ReadByte(DrvI2C_Ack_Have,8);        // Read data from sensor
    SWI2C_SendStop();

    return u8Data;
}

/* for NT99141 */
uint8_t SWI2C_Write_8bitSlaveAddr_16bitReg_8bitData(uint8_t uAddr, uint16_t uRegAddr, uint8_t uData)
{
    // 3-Phase(ID address, register address, data(8bits)) write transmission
    volatile uint8_t u32Delay = 0x50;
    SWI2C_SendStart();
    while(u32Delay--);
    if ( (SWI2C_WriteByte(uAddr,DrvI2C_Ack_Have,8)==FALSE) ||          // Write ID address to sensor
            (SWI2C_WriteByte(uRegAddr>>8,DrvI2C_Ack_Have,8)==FALSE) ||      // Write register addressH to sensor
            (SWI2C_WriteByte(uRegAddr&0xff,DrvI2C_Ack_Have,8)==FALSE) ||    // Write register addressL to sensor
            (SWI2C_WriteByte(uData,DrvI2C_Ack_Have,8)==FALSE) )                // Write data to sensor
    {
        SWI2C_SendStop();
        return FALSE;
    }
    SWI2C_SendStop();

    if (uRegAddr==0x12 && (uData&0x80)!=0)
    {
        Delay(1000);
    }
    return TRUE;
}

