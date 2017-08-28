/**************************************************************************
 * @file     usbh_hid_kbd.c
 * @version  V1.00
 * $Revision: 1 $
 * $Date: 14/12/02 5:49p $
 * @brief    M480 MCU USB Host HID keyboard driver
 *
 * @note
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "NuMicro.h"

#include "usbh_lib.h"
#include "usbh_hid.h"
#include "usbh_hid_kbd.h"

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
    struct hid_kbd_dev  *kdev;
    uint8_t    shift = (mod & 0x22);

    kdev = (struct hid_kbd_dev *)hdev->client;

    // [a-z]
    if ((key > 0x03) && (key < 0x1e)) {
        // Upper case letters
        if ((!(kdev->bLED & LED_CapsLoock) && (mod & 2)) ||
                ((kdev->bLED & LED_CapsLoock) && ((mod & 2) == 0)))
            return (key - 4 + 'A');

        // Lower case letters
        else
            return (key - 4 + 'a');
    }
    // Numbers
    else if ((key > 0x1d) && (key < 0x27)) {
        if (shift)
            return (numKeys[key - 0x1e]);
        else
            return (key - 0x1e + '1');
    }
    // Keypad Numbers
    else if (key > 0x58 && key < 0x62) {
        if (kdev->bLED & LED_NumLock)
            return (key - 0x59 + '1');
    } else if ((key > 0x2c) && (key < 0x39))
        return ((shift) ? symKeysUp[key-0x2d] : symKeysLo[key-0x2d]);
    else if ((key > 0x53) && (key < 0x59))
        return padKeys[key - 0x54];
    else {
        switch (key) {
        case KEY_SPACE:
            return (0x20);
        case KEY_ENTER:
            return (0x13);
        case KEY_ZERO:
            return ((shift) ? ')' : '0');
        case KEY_ZERO2:
            return ((kdev->bLED & LED_NumLock) ? '0' : 0);
        case KEY_PERIOD:
            return ((kdev->bLED & LED_NumLock) ? '.' : 0);
        }
    }
    return 0;
}


uint8_t  update_locking_keys(HID_DEV_T *hdev, uint8_t key)
{
    struct hid_kbd_dev  *kdev;
    uint8_t   old_LED;
    int       ret;

    kdev = (struct hid_kbd_dev *)hdev->client;
    old_LED = kdev->bLED;

    switch (key) {
    case KEY_NUM_LOCK:
        kdev->bLED = kdev->bLED ^ LED_NumLock;
        break;
    case KEY_CAPS_LOCK:
        kdev->bLED = kdev->bLED ^ LED_CapsLoock;
        break;
    case KEY_SCROLL_LOCK:
        kdev->bLED = kdev->bLED ^ LED_ScrollLock;
        break;
    }

    if (kdev->bLED != old_LED) {
        ret = usbh_hid_set_report(hdev, 2, 0, &kdev->bLED, 1);
        if (ret < 0)
            printf("usbh_hid_set_report failed - %d\n", ret);
        return ret;
    }

    return 0;
}


int  kbd_parse_report(HID_DEV_T *hdev, uint8_t *buf, int len)
{
    struct hid_kbd_dev  *kdev;
    int       i, j;
    char      down, up;
    uint8_t   key;

    kdev = (struct hid_kbd_dev *)hdev->client;

    // On error - return
    if (buf[2] == 1)
        return -1;

    for (i = 2; i < 8; ++i) {
        down = up = 0;

        for (j = 2; j < 8; j++) {
            if ((buf[i] == kdev->pre_data[j]) && (buf[i] != 1))
                down = 1;
            if ((buf[j] == kdev->pre_data[i]) && (kdev->pre_data[i] != 1))
                up = 1;
        }

        if (!down) {
            update_locking_keys(hdev, buf[i]);
            printf("Pressed: 0x%x ", buf[i]);
            key = oem_key_to_ascii(hdev, buf[0], buf[i]);
            print_key(buf[0], key);
        }

        if (!up) {
            printf("Released: 0x%x ", buf[i]);
            key = oem_key_to_ascii(hdev, buf[0], buf[i]);
            print_key(buf[0], key);
        }
    }

    for (i = 0; i < 8; ++i)
        kdev->pre_data[i] = buf[i];

    return 0;
}


/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/

