/***************************************************************************//**
 * @file     codec.c
 * @brief    Audio Codec setting.
 * @version  1.0.0
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "usbd_audio.h"

#if NAU8822

/**************************************/
/* NAU8822 Setting                    */
/**************************************/
__IO uint32_t EndFlag0 = 0;
static volatile uint8_t bIsI2CIdle = TRUE;

void RecoveryFromArbLost(void)
{
    I2C2->CTL0 &= ~I2C_CTL0_I2CEN_Msk;
    I2C2->CTL0 |= I2C_CTL0_I2CEN_Msk;
}
/*---------------------------------------------------------------------------------------------------------*/
/*  Write 9-bit data to 7-bit address register of WAU8822 with I2C2                                        */
/*---------------------------------------------------------------------------------------------------------*/
void I2C_WriteNAU8822(uint8_t u8addr, uint16_t u16data)
{
    bIsI2CIdle = FALSE;
restart:
    I2C_START(I2C2);
    I2C_WAIT_READY(I2C2);

    I2C_SET_DATA(I2C2, 0x1A << 1);
    I2C_SET_CONTROL_REG(I2C2, I2C_CTL_SI);
    I2C_WAIT_READY(I2C2);
    if(I2C_GET_STATUS(I2C2) == 0x38)
    {
        RecoveryFromArbLost();
        goto restart;
    }
    else if(I2C_GET_STATUS(I2C2) != 0x18)
        goto stop;

    I2C_SET_DATA(I2C2, (uint8_t)((u8addr << 1) | (u16data >> 8)));
    I2C_SET_CONTROL_REG(I2C2, I2C_CTL_SI);
    I2C_WAIT_READY(I2C2);
    if(I2C_GET_STATUS(I2C2) == 0x38)
    {
        RecoveryFromArbLost();
        goto restart;
    }
    else if(I2C_GET_STATUS(I2C2) != 0x28)
        goto stop;

    I2C_SET_DATA(I2C2, (uint8_t)(u16data & 0x00FF));
    I2C_SET_CONTROL_REG(I2C2, I2C_CTL_SI);
    I2C_WAIT_READY(I2C2);
    if(I2C_GET_STATUS(I2C2) == 0x38)
    {
        RecoveryFromArbLost();
        goto restart;
    }
    else if(I2C_GET_STATUS(I2C2) != 0x28)
        goto stop;

stop:
    I2C_STOP(I2C2);
    while(I2C2->CTL0 & I2C_CTL0_STO_Msk);

    bIsI2CIdle = TRUE;
    EndFlag0 = 1;
}

static void ATOM_I2C_WriteNAU8822(uint8_t u8addr, uint16_t u16data)
{
    if(!bIsI2CIdle)
        while (EndFlag0 == 0);

    I2C_WriteNAU8822(u8addr, u16data);
}

uint32_t u32OldSampleRate=0;

/* config play sampling rate */
void NAU8822_ConfigSampleRate(uint32_t u32SampleRate)
{
    if(u32SampleRate == u32OldSampleRate)
        return;

    u32OldSampleRate = u32SampleRate;

    printf("[NAU8822] Configure Sampling Rate to %d\n", u32SampleRate);

    if((u32SampleRate % 8) == 0)
    {
        I2C_WriteNAU8822(36, 0x008);    //12.288Mhz
        I2C_WriteNAU8822(37, 0x00C);
        I2C_WriteNAU8822(38, 0x093);
        I2C_WriteNAU8822(39, 0x0E9);
    }
    else
    {
        I2C_WriteNAU8822(36, 0x007);    //11.2896Mhz
        I2C_WriteNAU8822(37, 0x021);
        I2C_WriteNAU8822(38, 0x161);
        I2C_WriteNAU8822(39, 0x026);
    }

    switch (u32SampleRate)
    {
    case 44100:
        I2C_WriteNAU8822(6, 0x14D);    /* Divide by 2, 48K */
        I2C_WriteNAU8822(7, 0x000);    /* 48K for internal filter coefficients */
        u32BuffLen = 441;
        u32RxBuffLen = 444;
        break;

    case 48000:
        I2C_WriteNAU8822(6, 0x14D);    /* Divide by 2, 48K */
        I2C_WriteNAU8822(7, 0x000);    /* 48K for internal filter coefficients */
        HSUSBD_SET_MAX_PAYLOAD(EPA, 24);
        u32BuffLen = 768;
        u32RxBuffLen = 768;
        break;

    case 96000:
        I2C_WriteNAU8822(6, 0x109);
        I2C_WriteNAU8822(72, 0x013);
        HSUSBD_SET_MAX_PAYLOAD(EPA, 48);
        u32BuffLen = 768;
        u32RxBuffLen = 768;
        break;
    }
}

void NAU8822_Setup()
{
    I2C_WriteNAU8822(0,  0x000);   /* Reset all registers */
    CLK_SysTickDelay(10000);

    I2C_WriteNAU8822(1,  0x02F);
    I2C_WriteNAU8822(2,  0x1B3);   /* Enable L/R Headphone, ADC Mix/Boost, ADC */
    I2C_WriteNAU8822(3,  0x07F);   /* Enable L/R main mixer, DAC */
    I2C_WriteNAU8822(4,  0x010);   /* 16-bit word length, I2S format, Stereo */
    I2C_WriteNAU8822(5,  0x000);   /* Companding control and loop back mode (all disable) */
    I2C_WriteNAU8822(10, 0x008);   /* DAC soft mute is disabled, DAC oversampling rate is 128x */
    I2C_WriteNAU8822(14, 0x108);   /* ADC HP filter is disabled, ADC oversampling rate is 128x */
    I2C_WriteNAU8822(15, 0x1FF);   /* ADC left digital volume control */
    I2C_WriteNAU8822(16, 0x1FF);   /* ADC right digital volume control */
    I2C_WriteNAU8822(44, 0x000);   /* LLIN/RLIN is not connected to PGA */
    I2C_WriteNAU8822(47, 0x060);   /* LLIN connected, and its Gain value */
    I2C_WriteNAU8822(48, 0x060);   /* RLIN connected, and its Gain value */
    I2C_WriteNAU8822(50, 0x001);   /* Left DAC connected to LMIX */
    I2C_WriteNAU8822(51, 0x001);   /* Right DAC connected to RMIX */
}

/* adjust codec PLL */
void AdjustCodecPll(RESAMPLE_STATE_T r)
{
    static uint16_t tb0[3][3] = {{0x00C, 0x093, 0x0E9}, // 8.192
        {0x00E, 0x1D2, 0x1E3},  // * 1.005 = 8.233
        {0x009, 0x153, 0x1EF}
    }; // * .995 = 8.151
    static uint16_t tb1[3][3] = {{0x021, 0x131, 0x026}, // 7.526
        {0x024, 0x010, 0x0C5},  // * 1.005 = 7.563
        {0x01F, 0x076, 0x191}
    }; // * .995 = 7.488
    static RESAMPLE_STATE_T current = E_RS_NONE;
    int i, s;

    if(r == current)
        return;
    else
        current = r;
    switch(r)
    {
    case E_RS_UP:
        s = 1;
        break;
    case E_RS_DOWN:
        s = 2;
        break;
    case E_RS_NONE:
    default:
        s = 0;
    }

    if((g_usbd_SampleRate % 8) == 0)
    {
        for(i=0; i<3; i++)
            ATOM_I2C_WriteNAU8822(37+i, tb0[s][i]);
    }
    else
    {
        for(i=0; i<3; i++)
            ATOM_I2C_WriteNAU8822(37+i, tb1[s][i]);
    }
}


#else   // NAU88L25

/***************************************/
/* NAU88L25 Setting                    */
/***************************************/
uint8_t I2cWrite_MultiByteforNAU88L25(uint8_t chipadd,uint16_t subaddr, const uint8_t *p,uint32_t len)
{
    /* Send START */
    I2C_START(I2C2);
    I2C_WAIT_READY(I2C2);

    /* Send device address */
    I2C_SET_DATA(I2C2, chipadd);
    I2C_SET_CONTROL_REG(I2C2, I2C_CTL_SI);
    I2C_WAIT_READY(I2C2);

    /* Send register number and MSB of data */
    I2C_SET_DATA(I2C2, (uint8_t)(subaddr>>8));
    I2C_SET_CONTROL_REG(I2C2, I2C_CTL_SI);
    I2C_WAIT_READY(I2C2);

    /* Send register number and MSB of data */
    I2C_SET_DATA(I2C2, (uint8_t)(subaddr));
    I2C_SET_CONTROL_REG(I2C2, I2C_CTL_SI);
    I2C_WAIT_READY(I2C2);

    /* Send data */
    I2C_SET_DATA(I2C2, p[0]);
    I2C_SET_CONTROL_REG(I2C2, I2C_CTL_SI);
    I2C_WAIT_READY(I2C2);

    /* Send data */
    I2C_SET_DATA(I2C2, p[1]);
    I2C_SET_CONTROL_REG(I2C2, I2C_CTL_SI);
    I2C_WAIT_READY(I2C2);

    /* Send STOP */
    I2C_STOP(I2C2);

    return  0;
}


uint8_t I2C_WriteNAU88L25(uint16_t addr,uint16_t dat)
{
    uint8_t Tx_Data0[2];

    Tx_Data0[0] = (uint8_t)(dat >> 8);
    Tx_Data0[1] = (uint8_t)(dat & 0x00FF);

    return ( I2cWrite_MultiByteforNAU88L25(0x1A << 1,addr,&Tx_Data0[0],2) );
}

uint32_t u32OldSampleRate=0;

/* config play sampling rate */
void NAU88L25_ConfigSampleRate(uint32_t u32SampleRate)
{
    if(u32SampleRate == u32OldSampleRate)
        return;

    u32OldSampleRate = u32SampleRate;

    printf("[NAU88L25] Configure Sampling Rate to %d\n", u32SampleRate);

    I2C_WriteNAU88L25(0x0003,  0x8053);
    I2C_WriteNAU88L25(0x0004,  0x0001);
    if((u32SampleRate % 8) == 0)
    {
        I2C_WriteNAU88L25(0x0005, 0x3126); //12.288Mhz
        I2C_WriteNAU88L25(0x0006, 0x0008);
    }
    else
    {
        I2C_WriteNAU88L25(0x0005, 0x86C2); //11.2896Mhz
        I2C_WriteNAU88L25(0x0006, 0x0007);
    }

    switch (u32SampleRate)
    {
    case 44100:
        I2C_WriteNAU88L25(0x001D,  0x301A); //301A:Master, BCLK_DIV=11.2896M/8=1.4112M, LRC_DIV=1.4112M/32=44.1K
        I2C_WriteNAU88L25(0x002B,  0x0012);
        I2C_WriteNAU88L25(0x002C,  0x0082);
        u32BuffLen = 441;
        u32RxBuffLen = 444;
        break;

    case 48000:
        I2C_WriteNAU88L25(0x001D,  0x301A); //301A:Master, BCLK_DIV=12.288M/8=1.536M, LRC_DIV=1.536M/32=48K
        I2C_WriteNAU88L25(0x002B,  0x0012);
        I2C_WriteNAU88L25(0x002C,  0x0082);
        HSUSBD_SET_MAX_PAYLOAD(EPA, 192);
        u32BuffLen = 768;
        u32RxBuffLen = 192;
        break;

    case 96000:
        I2C_WriteNAU88L25(0x0003,  0x80A2); //MCLK = SYSCLK_SRC/2
        I2C_WriteNAU88L25(0x0004,  0x1801);
        I2C_WriteNAU88L25(0x0005,  0x3126); //MCLK = 24.576MHz
        I2C_WriteNAU88L25(0x0006,  0xF008);
        I2C_WriteNAU88L25(0x001D,  0x301A); //3019:Master, BCLK_DIV=MCLK/8=3.072M, LRC_DIV=3.072M/32=96K
        I2C_WriteNAU88L25(0x002B,  0x0001);
        I2C_WriteNAU88L25(0x002C,  0x0080);
        HSUSBD_SET_MAX_PAYLOAD(EPA, 384);
        u32BuffLen = 768;
        u32RxBuffLen = 384;
        break;

    default:
        printf("do not support %d sampling rate\n", u32SampleRate);
    }
}


void NAU88L25_Reset(void)
{
    I2C_WriteNAU88L25(0,  0x1);
    I2C_WriteNAU88L25(0,  0);   // Reset all registers
    CLK_SysTickDelay(10000);

    printf("NAU88L25 Software Reset.\n");
}


void NAU88L25_Setup(void)
{
    I2C_WriteNAU88L25(0x0003,  0x8053);
    I2C_WriteNAU88L25(0x0004,  0x0001);
    I2C_WriteNAU88L25(0x0005,  0x3126);
    I2C_WriteNAU88L25(0x0006,  0x0008);
    I2C_WriteNAU88L25(0x0007,  0x0010);
    I2C_WriteNAU88L25(0x0008,  0xC000);
    I2C_WriteNAU88L25(0x0009,  0x6000);
    I2C_WriteNAU88L25(0x000A,  0xF13C);
    I2C_WriteNAU88L25(0x000C,  0x0048);
    I2C_WriteNAU88L25(0x000D,  0x0000);
    I2C_WriteNAU88L25(0x000F,  0x0000);
    I2C_WriteNAU88L25(0x0010,  0x0000);
    I2C_WriteNAU88L25(0x0011,  0x0000);
    I2C_WriteNAU88L25(0x0012,  0xFFFF);
    I2C_WriteNAU88L25(0x0013,  0x0015);
    I2C_WriteNAU88L25(0x0014,  0x0110);
    I2C_WriteNAU88L25(0x0015,  0x0000);
    I2C_WriteNAU88L25(0x0016,  0x0000);
    I2C_WriteNAU88L25(0x0017,  0x0000);
    I2C_WriteNAU88L25(0x0018,  0x0000);
    I2C_WriteNAU88L25(0x0019,  0x0000);
    I2C_WriteNAU88L25(0x001A,  0x0000);
    I2C_WriteNAU88L25(0x001B,  0x0000);
    I2C_WriteNAU88L25(0x001C,  0x0002);
    I2C_WriteNAU88L25(0x001D,  0x301a);   //301A:Master, BCLK_DIV=12.288M/8=1.536M, LRC_DIV=1.536M/32=48K
    I2C_WriteNAU88L25(0x001E,  0x0000);
    I2C_WriteNAU88L25(0x001F,  0x0000);
    I2C_WriteNAU88L25(0x0020,  0x0000);
    I2C_WriteNAU88L25(0x0021,  0x0000);
    I2C_WriteNAU88L25(0x0022,  0x0000);
    I2C_WriteNAU88L25(0x0023,  0x0000);
    I2C_WriteNAU88L25(0x0024,  0x0000);
    I2C_WriteNAU88L25(0x0025,  0x0000);
    I2C_WriteNAU88L25(0x0026,  0x0000);
    I2C_WriteNAU88L25(0x0027,  0x0000);
    I2C_WriteNAU88L25(0x0028,  0x0000);
    I2C_WriteNAU88L25(0x0029,  0x0000);
    I2C_WriteNAU88L25(0x002A,  0x0000);
    I2C_WriteNAU88L25(0x002B,  0x0012);
    I2C_WriteNAU88L25(0x002C,  0x0082);
    I2C_WriteNAU88L25(0x002D,  0x0000);
    I2C_WriteNAU88L25(0x0030,  0x00CF);
    I2C_WriteNAU88L25(0x0031,  0x0000);
    I2C_WriteNAU88L25(0x0032,  0x0000);
    I2C_WriteNAU88L25(0x0033,  0x009E);
    I2C_WriteNAU88L25(0x0034,  0x029E);
    I2C_WriteNAU88L25(0x0038,  0x1486);
    I2C_WriteNAU88L25(0x0039,  0x0F12);
    I2C_WriteNAU88L25(0x003A,  0x25FF);
    I2C_WriteNAU88L25(0x003B,  0x3457);
    I2C_WriteNAU88L25(0x0045,  0x1486);
    I2C_WriteNAU88L25(0x0046,  0x0F12);
    I2C_WriteNAU88L25(0x0047,  0x25F9);
    I2C_WriteNAU88L25(0x0048,  0x3457);
    I2C_WriteNAU88L25(0x004C,  0x0000);
    I2C_WriteNAU88L25(0x004D,  0x0000);
    I2C_WriteNAU88L25(0x004E,  0x0000);
    I2C_WriteNAU88L25(0x0050,  0x2007);
    I2C_WriteNAU88L25(0x0051,  0x0000);
    I2C_WriteNAU88L25(0x0053,  0xC201);
    I2C_WriteNAU88L25(0x0054,  0x0C95);
    I2C_WriteNAU88L25(0x0055,  0x0000);
    I2C_WriteNAU88L25(0x0058,  0x1A14);
    I2C_WriteNAU88L25(0x0059,  0x00FF);
    I2C_WriteNAU88L25(0x0066,  0x0060);
    I2C_WriteNAU88L25(0x0068,  0xC300);
    I2C_WriteNAU88L25(0x0069,  0x0000);
    I2C_WriteNAU88L25(0x006A,  0x0083);
    I2C_WriteNAU88L25(0x0071,  0x0011);
    I2C_WriteNAU88L25(0x0072,  0x0260);
    I2C_WriteNAU88L25(0x0073,  0x332C);
    I2C_WriteNAU88L25(0x0074,  0x4502);
    I2C_WriteNAU88L25(0x0076,  0x3140);
    I2C_WriteNAU88L25(0x0077,  0x0000);
    I2C_WriteNAU88L25(0x007F,  0x553F);
    I2C_WriteNAU88L25(0x0080,  0x0420);
    I2C_WriteNAU88L25(0x0001,  0x07D4);

    printf("NAU88L25 Configured done.\n");
}

/* adjust codec PLL */
void AdjustCodecPll(RESAMPLE_STATE_T r)
{
    /* Sample rate = 48KH, 96KHz */
    /* 8.192, 8.192*1.005 = 8.23296, 8.192*0.995 = 8.15104 */
    /* 0.192   * 2^16 = 0x3126 */
    /* 0.23296 * 2^16 = 0x3BA3 */
    /* 0.15104 * 2^16 = 0x26AB */
    static uint16_t tb0[3] = {0x3126, 0x3BA3, 0x26AB};

    /* Sample rate = 44.1KHz only */
    /* 7.5264, 7.5264*1.005 = 7.5640, 7.5264*0.995 = 7.4887 */
    /* 0.5264  * 2^16 = 0x86C2 */
    /* 0.5640  * 2^16 = 0x9062 */
    /* 0.4887  * 2^16 = 0x7D1B */
    static uint16_t tb1[3] = {0x86C2, 0x9062, 0x7D1B};

    static RESAMPLE_STATE_T current = E_RS_NONE;
    int s;

    if(r == current)
        return;
    else
        current = r;
    switch(r)
    {
    case E_RS_UP:
        s = 1;
        break;
    case E_RS_DOWN:
        s = 2;
        break;
    case E_RS_NONE:
    default:
        s = 0;
    }

    if((g_usbd_SampleRate % 8) == 0)
    {
        I2C_WriteNAU88L25(0x0005, tb0[s]);
        I2C_WriteNAU88L25(0x0006, 0x0008);
    }
    else
    {
        I2C_WriteNAU88L25(0x0005, tb1[s]);
        I2C_WriteNAU88L25(0x0006, 0x0007);
    }
}

#endif



