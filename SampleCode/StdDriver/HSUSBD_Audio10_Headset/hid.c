/******************************************************************************
 * @file     hid.c
 * @version  V0.10
 * @brief
 *           Demonstrate how to implement a USB hid class device.
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "usbd_audio.h"

#ifdef __HID__

uint8_t volatile g_u8EPDReady = 0;

void GPIO_Init(void)
{
    /* Enable PB0, PC9~12, PE4 */
    PB->MODE |= 0x3;
    PC->MODE |= 0x3fc0000;
    PE->MODE |= 0x300;
    PB->INTSRC |= 0x1;
    PC->INTSRC |= 0x1e00;
    PE->INTSRC |= 0x10;
    PB->INTEN |= 0x1 | (0x1 << 16);
    PC->INTEN |= 0x1e00 | (0x1e00 << 16);
    PE->INTEN |= 0x10 | (0x10 << 16);
    PB->DBEN |= 0x1;
    PC->DBEN |= 0x1e00;      // Enable key debounce
    PE->DBEN |= 0x10;
    GPIO->DBCTL = 0x16; // Debounce time is about 6ms
//    NVIC_EnableIRQ(GPB_IRQn);
//    NVIC_EnableIRQ(GPC_IRQn);
//    NVIC_EnableIRQ(GPE_IRQn);
}


uint8_t g_hookswitch = 0;
void HID_UpdateHidData(void)
{
    uint8_t buf[8];
    uint32_t u32RegC;
    int32_t volatile i;
#ifndef __MEDIAKEY__
    uint32_t u32RegB;
#endif
    uint32_t u32RegE;

    if(g_u8EPDReady)
    {
        /*
           Key definition:
             Down          PC12
             right         PE4
             up            PC10
             left          PC11
             right key     PB0
             left key      PC9
        */

#ifndef __MEDIAKEY__
        u32RegB = PB->PIN & 0x1;
#endif
        u32RegC = PC->PIN & 0x1e00;
        u32RegE = PE->PIN & 0x10;
#ifdef __JOYSTICK__
        for(i = 0; i < 5; i++)
            buf[i] = 0x7F;

        buf[5] = 0x0F;    /* Hat switch */
        buf[6] = 0x00;
        buf[7] = 0x00;
#elif defined  __MEDIAKEY__
        for(i = 0; i < 8; i++)
            buf[i] = 0;
#else
        for(i = 0; i < 8; i++)
            buf[i] = 0;
#endif

#ifdef __JOYSTICK__
/* Input Report
 +--------+--------+--------+--------+--------+------------------+------------------+--------+
 | Byte 0 | Byte 1 | Byte 2 | Byte 3 | Byte 4 |      Byte 5      |      Byte 6      | Byte 7 |
 +--------+--------+--------+--------+--------+-------+----------+------------------+--------+
 |        |        |        |        |        | Button|Hat switch|      Button      |        |
 | X-axis | Y-axis | Z-axis | Z-axis |   Rz   |-------+----------+------------------|  Pad   |
 |        |        |        |        |        |4|3|2|1|   0xF    |12|11|10|9|8|7|6|5|        |
 +--------+--------+--------+--------+--------+-------+----------+------------------+--------+
*/
    /* Byte 1 */
        if((u32RegC & (1<<10)) == 0)         /* PC10 - Up */
            buf[1] = 0x00;
        if((u32RegC & (1<<12)) == 0)         /* PC12 - Down */
            buf[1] = 0xFF;
    /* Byte 0 */
        if((u32RegC & (1<<11)) == 0)         /* PC11 - Left */
            buf[0] = 0x00;
        if((u32RegE & (1<<4)) == 0)          /* PE4 - Right */
            buf[0] = 0xFF;
    /* Byte 5 */
        if((u32RegC & (1<<9)) == 0)          /* PC9 - Button 1 */
            buf[5] |= 0x10;
        if((u32RegB & (1<<0)) == 0)          /* PB0 - Button 2 */
            buf[5] |= 0x20;

#elif defined  __MEDIAKEY__
/* Input Report
 +--------+---------+--------+--------+----------+--------+----------+----------+------+
 |        |   BIT7  |  BIT6  |  BIT5  |   BIT4   |  BIT3  |   BIT2   |   BIT1   | BIT0 |
 +--------+---------+--------+--------+----------+--------+----------+----------+------+
 |        |                                               |  Volume  |  Volume  |      |
 | Byte 0 |                     Pad                       |Decrement |Increment | Mute |
 +--------+---------+--------+--------+----------+--------+----------+----------+------+
 |        |         |        |        |   Scan   |  Scan  |          |          |      |
 | Byte 1 |   Fast  | Rewind | Record | Previous |  Next  |Play/Pause|   Stop   | Play |
 |        | Forward |        |        |   Track  |  Track |          |          |      |
 +--------+---------+--------+--------+----------+--------+----------+----------+------+
 |  Byte  |                                                                            |
 | 2 ~ 7  |                                 Pad                                        |
 +--------+----------------------------------------------------------------------------+
*/
        buf[0] = 0;
        buf[1] = 0;
    /* Byte 1 */
        if((u32RegC & (1<<9)) == 0)          /* PC9 - Button 1             */
            buf[1] |= HID_CTRL_PAUSE;        /* Play/Pause - 0x04          */
        if((u32RegE & (1<<4)) == 0)          /* PE4 - Right                */
            buf[1] |= HID_CTRL_NEXT;         /* Scan Next Track - 0x08     */
        if((u32RegC & (1<<11)) == 0)         /* PC11 - Left                */
            buf[1] |= HID_CTRL_PREVIOUS;     /* Scan Previous Track - 0x10 */
    /* Byte 0 */
        if((u32RegC & (1<<10)) == 0)         /* PC10 - Up                  */
            buf[0] |= HID_CTRL_VOLUME_INC;   /* Volume Increment - 0x02    */
        if((u32RegC & (1<<12)) == 0)         /* PC12 - Down                */
            buf[0] |= HID_CTRL_VOLUME_DEC;   /* Volume Decrement -0x04     */
#endif
        g_u8EPDReady = 0;
        /* Set transfer length and trigger IN transfer */
        for (i=0; i<8; i++)
            HSUSBD->EP[EPD].EPDAT_BYTE = buf[i];
        HSUSBD->EP[EPD].EPTXCNT = 8;
        HSUSBD_ENABLE_EP_INT(EPD, HSUSBD_EPINTEN_INTKIEN_Msk);
    }
}

void EPE_Handler(void)  /* Interrupt OUT handler */
{
/* Output Report
 +--------+---------+---------+---------+---------+---------+---------+---------+---------+
 |        |   BIT7  |   BIT6  |   BIT5  |   BIT4  |   BIT3  |   BIT2  |   BIT1  |   BIT0  |
 +--------+---------+---------+---------+---------+---------+---------+---------+---------+
 |        | In Use  | In Use  | In Use  | In Use  | In Use  | In Use  |Selected |Selected |
 |        |Indicator|Indicator|Indicator|Indicator|Indicator|Indicator|Indicator|Indicator|
 |        |  Prog.  |  Prog.  |  Prog.  |  Prog.  |  Prog.  |  Prog.  |  Prog.  |  Prog.  |
 | Byte 0 |Button 6 |Button 5 |Button 4 |Button 3 |Button 2 |Button 1 |Button 2 |Button 1 |
 +--------+---------+---------+---------+---------+---------+---------+---------+---------+
 |        |                                                 |                   |Selected |
 |        |                                                 |     Multi-Mode    |Indicator|
 |        |                                                 | Indicator Message |Alternate|
 | Byte 1 |                      Pad                        |      Waiting      |Function |
 +--------+-------------------------------------------------+-------------------+---------+
*/
}
#endif
