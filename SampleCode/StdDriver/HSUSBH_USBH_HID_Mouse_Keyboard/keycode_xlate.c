/**************************************************************************//**
 * @file     keycode_xltae.c
 * @version  V1.00
 * @brief    M480 MCU USB Host HID keyboard code translation.
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "NuMicro.h"

#include "usbh_lib.h"
#include "usbh_hid.h"

#define PRINT_MESSAGE

#define MOD_KEY_LEFT_CTRL       0x01
#define MOD_KEY_LEFT_SHIFT      0x02
#define MOD_KEY_LEFT_ALT        0x04
#define MOD_KEY_LEFT_GUI        0x08
#define MOD_KEY_RIGHT_CTRL      0x10
#define MOD_KEY_RIGHT_SHIFT     0x20
#define MOD_KEY_RIGHT_ALT       0x40
#define MOD_KEY_RIGHT_GUI       0x80

#define NUM_LOCK                0x01
#define CAPS_LOCK               0x02
#define SCROLL_LOCK             0x04

#define KEY_ZERO                0x27
#define KEY_ENTER               0x28
#define KEY_SPACE               0x2C
#define KEY_F1                  0x3A
#define KEY_F12                 0x45
#define KEY_PRINT_SCREEN        0x46
#define KEY_PAUSE               0x48
#define KEY_INSERT              0x49
#define KEY_HOME                0x4A
#define KEY_PAGE_UP             0x4B
#define KEY_DEL                 0x4C
#define KEY_END                 0x4D
#define KEY_PAGE_DOWN           0x4E
#define KEY_RIGHT_ARROW         0x4F
#define KEY_LEFT_ARROW          0x50
#define KEY_DOWN_ARROW          0x51
#define KEY_UP_ARROW            0x52
#define KEY_ENTER2              0x58
#define KEY_END2                0x59
#define KEY_DOWN_ARROW2         0x5A
#define KEY_PAGE_DOWN2          0x5B
#define KEY_LEFT_ARROW2         0x5C
#define KEY_MIDDLE2             0x5D
#define KEY_RIGHT_ARROW2        0x5E
#define KEY_HOME2               0x5F
#define KEY_UP_ARROW2           0x60
#define KEY_PAGE_UP2            0x61
#define KEY_ZERO2               0x62
#define KEY_INSERT2             0x62
#define KEY_DEL2                0x63
#define KEY_PERIOD              0x63


static const uint8_t numKeys[] = { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')' };
static const uint8_t symKeysUp[] = { '_', '+', '{', '}', '|', '~', ':', '"', '~', '<', '>', '?' };
static const uint8_t symKeysLo[] = { '-', '=', '[', ']', '\\', ' ', ';', '\'', '`', ',', '.', '/' };
static const uint8_t padKeys[] = { '/', '*', '-', '+', 0x13 };

void kbd_ascii_input(uint8_t code);
void kbd_function_input(uint8_t code);

/*
 *  Translate OEM key to ASCII code.
 */
uint8_t  translate_keycode(KEYBOARD_EVENT_T *kbd, uint8_t key)
{
    uint8_t    modifier, shift, locks;

    modifier = kbd->modifier;
    locks= kbd->lock_state;
    shift = (modifier & (MOD_KEY_LEFT_SHIFT | MOD_KEY_RIGHT_SHIFT));

    /* [a-z] */
    if ((key > 0x03) && (key < 0x1e))
    {
        if ((!(locks & CAPS_LOCK) && (modifier & MOD_KEY_LEFT_SHIFT)) ||
                ((locks & CAPS_LOCK) && ((modifier & MOD_KEY_LEFT_SHIFT) == 0)))
        {
            return (key - 4 + 'A');
        }
        else
        {
            return (key - 4 + 'a');
        }
    }

    /* Numbers */
    else if ((key > 0x1d) && (key < 0x27))
    {
        if (shift)
            return (numKeys[key - 0x1e]);
        else
            return (key - 0x1e + '1');
    }

    /* Keypad Numbers */
    else if ((key > 0x58) && (key < 0x62))
    {
        if (locks & NUM_LOCK)
            return (key - 0x59 + '1');
    }
    else if ((key > 0x2c) && (key < 0x39))
    {
        return ((shift) ? symKeysUp[key-0x2d] : symKeysLo[key-0x2d]);
    }
    else if ((key > 0x53) && (key < 0x59))
    {
        return padKeys[key - 0x54];
    }
    else
    {
        switch (key)
        {
        case KEY_SPACE:
            return (0x20);
        case KEY_ENTER:
        case KEY_ENTER2:
            return (0x13);
        case KEY_ZERO:
            return ((shift) ? ')' : '0');
        case KEY_ZERO2:
            return ((locks & NUM_LOCK) ? '0' : 0);
        case KEY_PERIOD:
            return ((locks & NUM_LOCK) ? '.' : 0);
        }
    }
    return 0;
}


void keycode_process(KEYBOARD_EVENT_T *kbd)
{
    int       i;
    uint8_t   code;

#ifdef PRINT_MESSAGE
    if (kbd->lock_state & NUM_LOCK)
        printf("[Num Lock] ");
    if (kbd->lock_state & CAPS_LOCK)
        printf("[Caps Lock] ");
    if (kbd->lock_state & SCROLL_LOCK)
        printf("[Scroll Lock] ");

    if (kbd->modifier & MOD_KEY_LEFT_CTRL)
        printf("L-Ctrl ");
    if (kbd->modifier & MOD_KEY_LEFT_SHIFT)
        printf("L-Shift ");
    if (kbd->modifier & MOD_KEY_LEFT_ALT)
        printf("L-Alt ");
    if (kbd->modifier & MOD_KEY_LEFT_GUI)
        printf("L-GUI ");
    if (kbd->modifier & MOD_KEY_RIGHT_CTRL)
        printf("R-Ctrl ");
    if (kbd->modifier & MOD_KEY_RIGHT_SHIFT)
        printf("R-Shift ");
    if (kbd->modifier & MOD_KEY_RIGHT_ALT)
        printf("R-Alt ");
    if (kbd->modifier & MOD_KEY_RIGHT_GUI)
        printf("R-GUI ");
#endif

    for (i = 0; i < kbd->key_cnt; ++i)
    {
        code = translate_keycode(kbd, kbd->keycode[i]);
        if (code == 0)
            kbd_function_input(kbd->keycode[i]);
        else
            kbd_ascii_input(code);
    }
#ifdef PRINT_MESSAGE
    printf("\n");
#endif
}


void kbd_ascii_input(uint8_t code)
{
    // TO DO
    // Implement your keyboard ascii input processor here.
    // This function is in interrupt context.
    // It's better to copy and queue key codes and deliver to a non-interrupt context routine.
#ifdef PRINT_MESSAGE
    printf("%c", code);
#endif
}

void kbd_function_input(uint8_t code)
{
    // TO DO
    // Implement your keyboard function key processor here.
    // This function is in interrupt context.
    // It's better to copy and queue key codes and deliver to a non-interrupt context routine.
#ifdef PRINT_MESSAGE
    if ((code >= KEY_F1) && (code <= KEY_F12))
    {
        printf("F%d ", code - KEY_F1 + 1);
    }
    else
    {
        switch (code)
        {
        case KEY_PRINT_SCREEN:
            printf("[PrnScr] ");
            break;
        case KEY_PAUSE:
            printf("[Pause] ");
            break;
        case KEY_INSERT:
        case KEY_INSERT2:
            printf("[Inst] ");
            break;
        case KEY_HOME:
        case KEY_HOME2:
            printf("[Home] ");
            break;
        case KEY_PAGE_UP:
        case KEY_PAGE_UP2:
            printf("[PgUp] ");
            break;
        case KEY_DEL:
        case KEY_DEL2:
            printf("[Del] ");
            break;
        case KEY_END:
        case KEY_END2:
            printf("[End] ");
            break;
        case KEY_PAGE_DOWN:
        case KEY_PAGE_DOWN2:
            printf("[PgDn] ");
            break;
        case KEY_RIGHT_ARROW:
        case KEY_RIGHT_ARROW2:
            printf("[R-Arrow] ");
            break;
        case KEY_LEFT_ARROW:
        case KEY_LEFT_ARROW2:
            printf("[L-Arrow] ");
            break;
        case KEY_DOWN_ARROW:
        case KEY_DOWN_ARROW2:
            printf("[D-Arrow] ");
            break;
        case KEY_UP_ARROW:
        case KEY_UP_ARROW2:
            printf("[U-Arrow] ");
            break;
        case KEY_MIDDLE2:
            printf("[ ] ");
            break;
        default:
            printf("[?? %x] ", code);
            break;
        }
    }
#endif
}

