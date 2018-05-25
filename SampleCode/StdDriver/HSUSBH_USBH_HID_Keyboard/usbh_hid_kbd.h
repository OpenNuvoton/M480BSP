/***************************************************************************//**
 * @file     usbh_hid_kbd.h
 * @brief    M480 USB Host HID keyboard driver header file
 * @version  V1.00
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __USBH_HID_KBD_H__
#define __USBH_HID_KBD_H__


/* Keyboard Modifiers */
enum kbd_mod
{
    LeftCtrl   = 0x01,
    LeftShift  = 0x02,
    Alt        = 0x04,
    LeftCmd    = 0x08,
    RightCtrl  = 0x10,
    RightShift = 0x20,
    AltGr      = 0x40,
    RightCmd   = 0x80
};


#define LED_NumLock       0x01
#define LED_CapsLoock     0x02
#define LED_ScrollLock    0x04


#define KEY_SPACE         0x2c
#define KEY_ZERO          0x27
#define KEY_ZERO2         0x62
#define KEY_ENTER         0x28
#define KEY_PERIOD        0x63

#define KEY_CAPS_LOCK     0x39
#define KEY_SCROLL_LOCK   0x47
#define KEY_NUM_LOCK      0x53


struct hid_kbd_dev
{
    uint8_t    pre_data[8];     /* previous received report */
    uint8_t    bLED;
};




#endif  /* __USBH_HID_KBD_H__ */

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
