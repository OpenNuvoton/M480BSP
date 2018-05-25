/**************************************************************************//**
 * @file     usbh_hid_kbd.c
 * @version  V1.00
 * @brief    M480 MCU USB Host HID keyboard driver
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "NuMicro.h"

#include "usbh_lib.h"
#include "usbh_hid.h"
#include "usbh_hid_kbd.h"

struct hid_kbd_dev   g_kbd_dev;    /* Support one keyboard device at the same time.         */
/* If you want to support mulitiple keyboards, please
   implement an array and handle it.                     */

static const uint8_t numKeys[] = { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')' };
static const uint8_t symKeysUp[] = { '_', '+', '{', '}', '|', '~', ':', '"', '~', '<', '>', '?' };
static const uint8_t symKeysLo[] = { '-', '=', '[', ']', '\\', ' ', ';', '\'', '`', ',', '.', '/' };
static const uint8_t padKeys[] = { '/', '*', '-', '+', 0x13 };


void  print_key(uint8_t mod, uint8_t key)
{
    printf(" mod => ");

    if (mod & LeftCtrl)
        printf("L-Ctrl");
    if (mod & LeftShift)
        printf("L-Shift");
    if (mod & Alt)
        printf("Alt");
    if (mod & LeftCmd)
        printf("L-Cmd");
    if (mod & RightCtrl)
        printf("R-Ctrl");
    if (mod & RightShift)
        printf("R-Shift");
    if (mod & AltGr)
        printf("AltGr");
    if (mod & RightCmd)
        printf("R-Cmd");

    printf("  %c\n", key);
}


/*
 *  Translate OEM key to ASCII code.
 */
uint8_t  oem_key_to_ascii(HID_DEV_T *hdev, uint8_t mod, uint8_t key)
{
    uint8_t    shift = (mod & 0x22);

    // [a-z]
    if ((key > 0x03) && (key < 0x1e))
    {
        // Upper case letters
        if ((!(g_kbd_dev.bLED & LED_CapsLoock) && (mod & 2)) ||
                ((g_kbd_dev.bLED & LED_CapsLoock) && ((mod & 2) == 0)))
            return (key - 4 + 'A');

        // Lower case letters
        else
            return (key - 4 + 'a');
    }
    // Numbers
    else if ((key > 0x1d) && (key < 0x27))
    {
        if (shift)
            return (numKeys[key - 0x1e]);
        else
            return (key - 0x1e + '1');
    }
    // Keypad Numbers
    else if (key > 0x58 && key < 0x62)
    {
        if (g_kbd_dev.bLED & LED_NumLock)
            return (key - 0x59 + '1');
    }
    else if ((key > 0x2c) && (key < 0x39))
        return ((shift) ? symKeysUp[key-0x2d] : symKeysLo[key-0x2d]);
    else if ((key > 0x53) && (key < 0x59))
        return padKeys[key - 0x54];
    else
    {
        switch (key)
        {
        case KEY_SPACE:
            return (0x20);
        case KEY_ENTER:
            return (0x13);
        case KEY_ZERO:
            return ((shift) ? ')' : '0');
        case KEY_ZERO2:
            return ((g_kbd_dev.bLED & LED_NumLock) ? '0' : 0);
        case KEY_PERIOD:
            return ((g_kbd_dev.bLED & LED_NumLock) ? '.' : 0);
        }
    }
    return 0;
}


uint8_t  update_locking_keys(HID_DEV_T *hdev, uint8_t key)
{
    uint8_t   old_LED;
    int       ret;

    old_LED = g_kbd_dev.bLED;

    switch (key)
    {
    case KEY_NUM_LOCK:
        g_kbd_dev.bLED = g_kbd_dev.bLED ^ LED_NumLock;
        break;
    case KEY_CAPS_LOCK:
        g_kbd_dev.bLED = g_kbd_dev.bLED ^ LED_CapsLoock;
        break;
    case KEY_SCROLL_LOCK:
        g_kbd_dev.bLED = g_kbd_dev.bLED ^ LED_ScrollLock;
        break;
    }

    if (g_kbd_dev.bLED != old_LED)
    {
        ret = usbh_hid_set_report(hdev, 2, 0, &g_kbd_dev.bLED, 1);
        if (ret < 0)
            printf("usbh_hid_set_report failed - %d\n", ret);
        return ret;
    }

    return 0;
}


int  kbd_parse_report(HID_DEV_T *hdev, uint8_t *buf, int len)
{
    int       i, j;
    char      down, up;
    uint8_t   key;

    // On error - return
    if (buf[2] == 1)
        return -1;

    for (i = 2; i < 8; ++i)
    {
        down = up = 0;

        for (j = 2; j < 8; j++)
        {
            if ((buf[i] == g_kbd_dev.pre_data[j]) && (buf[i] != 1))
                down = 1;
            if ((buf[j] == g_kbd_dev.pre_data[i]) && (g_kbd_dev.pre_data[i] != 1))
                up = 1;
        }

        if (!down)
        {
            update_locking_keys(hdev, buf[i]);
            printf("Pressed: 0x%x ", buf[i]);
            key = oem_key_to_ascii(hdev, buf[0], buf[i]);
            print_key(buf[0], key);
        }

        if (!up)
        {
            printf("Released: 0x%x ", buf[i]);
            key = oem_key_to_ascii(hdev, buf[0], buf[i]);
            print_key(buf[0], key);
        }
    }

    for (i = 0; i < 8; ++i)
        g_kbd_dev.pre_data[i] = buf[i];

    return 0;
}


/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/

