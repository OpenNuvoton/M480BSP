/**************************************************************************//**
 * @file     hid_parser.c
 * @version  V1.00
 * @brief    M480 MCU USB Host HID report descriptor parser
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "NuMicro.h"

#include "usb.h"
#include "usbh_lib.h"
#include "usbh_hid.h"


/// @cond HIDDEN_SYMBOLS


static int hid_parse_item(HID_DEV_T *hdev, uint8_t *buff);

#if ENABLE_DBG_MSG
struct string_table
{
    char        string[32];
    uint8_t     code;
};

static const struct string_table usage_page_list[] =
{
    "Generic Desktop",      UP_GENERIC_DESKTOP,
    "Simulation Controls",  UP_SIMULATION_CONTROLS,
    "VR Controls",          UP_VR_CONTROLS,
    "Sport Controls",       UP_SPORT_CONTROLS,
    "Game Controls",        UP_GAME_CONTROLS,
    "KeyCode",              UP_KEYCODE,
    "LEDs",                 UP_LEDS,
    "Button",               UP_BUTTON,
    "Digitizer",            UP_DIGITIZER,
    "Bar Code Scanner",     UP_BARCODE_SCANNER,
};

static const struct string_table desktop_page_list[] =
{
    "Pointer",              USAGE_ID_POINTER,
    "Mouse",                USAGE_ID_MOUSE,
    "Joystick",             USAGE_ID_JOYSTICK,
    "Game Pad",             USAGE_ID_GAMEPAD,
    "Keyboard",             USAGE_ID_KEYBOARD,
    "Keypad",               USAGE_ID_KEYPAD,
    "X",                    USAGE_ID_X,
    "Y",                    USAGE_ID_Y,
    "Z",                    USAGE_ID_Z,
    "Rx",                   0x33,
    "Ry",                   0x34,
    "Rz",                   0x35,
    "Slider",               0x36,
    "Dial",                 0x37,
    "Wheel",                USAGE_ID_WHEEL,
};

#endif


/*
 * Varibles used on parsing HID report descriptor
 */
static RP_INFO_T   _rp_info;      /* describing the current report */

static uint8_t   _data_usages[16];
static int       _data_usage_cnt;

static void print_usage_page(void)
{
#if ENABLE_DBG_MSG
    int   i;

    for (i = 0; i < sizeof(usage_page_list)/sizeof(struct string_table); i++)
    {
        if (usage_page_list[i].code == _rp_info.usage_page)
        {
            printf("(%s)", usage_page_list[i].string);
            return;
        }
    }
    printf("(?? - 0x%x)", _rp_info.usage_page);
#endif
}

static void print_usage(uint8_t usage)
{
#if ENABLE_DBG_MSG
    int   i, count;
    struct string_table  *p;

    if (_rp_info.usage_page == UP_GENERIC_DESKTOP)
    {
        count = sizeof(desktop_page_list)/sizeof(struct string_table);
        p = (struct string_table *)&desktop_page_list[0];
    }
    else
        return;

    for (i = 0; i < count; i++, p++)
    {
        if (p->code == usage)
        {
            printf("(%s)", p->string);
            return;
        }
    }
    printf("(?? - 0x%x)", usage);
#endif
}

static void read_main_item_status(uint8_t *buff)
{
    HID_DBGMSG("(");
    if (buff[0] & 0x01)
    {
        _rp_info.status.constant = 1;
        _rp_info.status.variable = 0;
        HID_DBGMSG("Constant ");
    }
    if (buff[0] & 0x02)
    {
        _rp_info.status.constant = 0;
        _rp_info.status.variable = 1;
        HID_DBGMSG("Variable ");
    }
    if (buff[0] & 0x04)
    {
        _rp_info.status.relative = 1;
        HID_DBGMSG("Relative ");
    }
    if (buff[0] & 0x08)
    {
        _rp_info.status.wrap = 1;
        HID_DBGMSG("Wrap ");
    }
    if (buff[0] & 0x10)
    {
        _rp_info.status.non_linear = 1;
        HID_DBGMSG("Non-linear ");
    }
    if (buff[0] & 0x20)
    {
        _rp_info.status.no_preferred = 1;
        HID_DBGMSG("Not-prefered ");
    }
    if (buff[0] & 0x40)
    {
        _rp_info.status.null_state = 1;
        HID_DBGMSG("Null-state ");
    }
    if (buff[0] & 0x80)
    {
        _rp_info.status.is_volatile = 1;
        HID_DBGMSG("Volatile ");
    }
    if (buff[1] & 0x01)
    {
        _rp_info.status.buffered_bytes = 1;
        HID_DBGMSG("Buffered-bytes ");
    }
    HID_DBGMSG(")");
}


/**
 *  @brief  Parse report descriptor and get information from descriptors.
 *  @param[in]  hdev    HID device
 *  @param[in]  iface   HID class interface
 *  @return   Success or failed.
 *  @retval   0        Success
 *  @retval   Otheriwse  Error occurred
 */
int hid_parse_report_descriptor(HID_DEV_T *hdev, IFACE_T *iface)
{
    UDEV_T         *udev = iface->udev;
    DESC_CONF_T    *config;
    DESC_IF_T      *ifd;
    DESC_HID_T     *hidd;
    uint8_t        *bptr;
    uint8_t        *desc_buff;
    int            desc_buff_len, remain_len, size;

    HID_DBGMSG("HID interface %d parsing report descriptor...\n", iface->if_num);

    memset(&_rp_info, 0, sizeof(_rp_info));
    _data_usage_cnt = 0;

    hdev->rpd.has_report_id = 0;

    bptr = udev->cfd_buff;
    config = (DESC_CONF_T *)bptr;

    /* step over configuration descritpor */
    bptr += config->bLength;
    size = config->wTotalLength - config->bLength;

    /*------------------------------------------------------------------------------------*/
    /*  Find the Interface Descriptor of this HID interface                               */
    /*------------------------------------------------------------------------------------*/
    while (size >= sizeof(DESC_IF_T))
    {
        ifd = (DESC_IF_T *)bptr;

        if ((ifd->bDescriptorType == USB_DT_INTERFACE) && (ifd->bInterfaceNumber == iface->if_num) &&
                (ifd->bInterfaceClass == USB_CLASS_HID))
            break;

        if (ifd->bLength == 0)
            return -1;

        bptr += ifd->bLength;
        size -= ifd->bLength;
    }

    if (size < sizeof(DESC_IF_T))
    {
        HID_ERRMSG("Can't find the HID interface!\n");
        return HID_RET_PARSING;
    }

    bptr += ifd->bLength;
    size -= ifd->bLength;

    /*------------------------------------------------------------------------------------*/
    /*  Continue to find the subsequent HID Descriptor                                    */
    /*------------------------------------------------------------------------------------*/
    while (size >= sizeof(DESC_HID_T))
    {
        hidd = (DESC_HID_T *)bptr;

        if ((hidd->bDescriptorType == HID_DESCRIPTOR_TYPE) &&
                (hidd->bRPDescType == REPORT_DESCRIPTOR_TYPE))
            break;

        if (hidd->bLength == 0)
            return HID_RET_PARSING;

        bptr += ifd->bLength;
        size -= ifd->bLength;
    }

    if (size < sizeof(DESC_HID_T))
    {
        HID_ERRMSG("Can't find the HID interface!\n");
        return HID_RET_PARSING;
    }

    hidd = (DESC_HID_T *)bptr;

    HID_DBGMSG("[HID Descriptor]\n");
    HID_DBGMSG("bLength = %d\n", hidd->bLength);
    HID_DBGMSG("bDescriptorType = 0x%x\n", hidd->bDescriptorType);
    HID_DBGMSG("bcdHID = 0x%x\n", hidd->bcdHID);
    HID_DBGMSG("bCountryCode = 0x%x\n", hidd->bCountryCode);
    HID_DBGMSG("bNumDescriptors = %d\n", hidd->bNumDescriptors);
    HID_DBGMSG("bRPDescType = 0x%x\n", hidd->bRPDescType);
    HID_DBGMSG("wDescriptorLength = %d\n", hidd->wDescriptorLength);

    HID_DBGMSG("Report descriptor found, length=%d. %d\n", hidd->wDescriptorLength, hidd->bLength);

    desc_buff_len = hidd->wDescriptorLength+8;
    desc_buff = (uint8_t *)usbh_alloc_mem(desc_buff_len);

    remain_len = usbh_hid_get_report_descriptor(hdev, desc_buff, desc_buff_len);
    if (remain_len <= 0)
    {
        usbh_free_mem(desc_buff, desc_buff_len);
        return remain_len;
    }

    //HID_DBGMSG("\nDump report descriptor =>\n");
    //dump_buff_hex(desc_buff, remain_len);

    /*------------------------------------------------------------------------------------*/
    /*  Parsing items                                                                     */
    /*------------------------------------------------------------------------------------*/
    bptr = desc_buff;
    while (remain_len > 0)
    {
        size = hid_parse_item(hdev, bptr);
        //printf("size = %d/%d\n", size, remain_len);
        if (size <= 0)
        {
            usbh_free_mem(desc_buff, desc_buff_len);
            return HID_RET_PARSING;
        }

        bptr += size;
        remain_len -= size;
    }

    usbh_free_mem(desc_buff, desc_buff_len);

    /*------------------------------------------------------------------------------------*/
    /*  For keyboard device, turn on all LEDs for 0.5 seconds and then turn off.          */
    /*------------------------------------------------------------------------------------*/
    if ((hdev->bSubClassCode == HID_SUBCLASS_BOOT_DEVICE) && (hdev->bProtocolCode == HID_PROTOCOL_KEYBOARD))
    {
        RP_INFO_T   *report;

        for (report = hdev->rpd.report; report != NULL; report = report->next)
        {
            if ((report->usage_page == UP_LEDS) && (report->report_size == 1) && report->status.variable)
            {
                uint8_t  i, ret, leds = 0;

                for (i = 0; (i < 8) && (i < report->report_count); i++)
                    leds = (leds << 1) | 0x1;

                /* turn-on keyboard NumLock, CapsLock, ScrollLock LEDs */
                ret = usbh_hid_set_report(hdev, RT_OUTPUT, 0, &leds, 1);
                if (ret != 1)
                {
                    HID_ERRMSG("Failed to turn on LEDs! 0x%x, %d\n", leds, ret);
                }
                else
                {
                    delay_us(500000);       /* delay 0.5 conds */

                    /* turn-off all LEDs */
                    leds = 0x00;
                    ret = usbh_hid_set_report(hdev, RT_OUTPUT, 0, &leds, 1);
                    if (ret != 1)
                        HID_ERRMSG("Failed to turn off LEDs! %d\n", ret);
                }
            }
        }
    }

    return 0;
}

static int hid_add_report(HID_DEV_T *hdev, uint8_t type)
{
    RP_INFO_T   *report, *p;

    report = (RP_INFO_T *)usbh_alloc_mem(sizeof(RP_INFO_T));
    if (report == NULL)
    {
        HID_ERRMSG("hid_add_report allocate memory failed!!\n");
        return USBH_ERR_MEMORY_OUT;
    }
    memcpy(report, &_rp_info, sizeof(RP_INFO_T));
    report->type = type;

    HID_DBGMSG("\nCreate a report. %d x %d (%d)\n", report->report_count, report->report_size, report->report_id);

    if (hdev->rpd.report == NULL)
        hdev->rpd.report = report;
    else
    {
        p = hdev->rpd.report;
        while (p->next  != NULL)
            p = p->next;
        p->next = report;
    }
    return 0;
}

static signed int hid_read_item_value(uint8_t bSize, uint8_t *buff)
{
    if (bSize == 1)
        return (signed char)buff[0];
    else if (bSize == 2)
        return (signed short)(buff[0] | (buff[1]<<8));
    else if (bSize == 4)
        return (signed int)(buff[0] | (buff[1]<<8) | (buff[2]<<16) | (buff[3]<<24));
    else
        return 0;
}


static int hid_parse_item(HID_DEV_T *hdev, uint8_t *buff)
{
    uint8_t     bTag, bSize, tag;
    int         item_len, i;

    bTag  = (buff[0] >> 4) & 0xF;
    //bType = (buff[0] >> 2) & 0x3;
    bSize = buff[0] & 0x3;
    tag =  (buff[0] & 0xFC);

    if (bTag == 0xF)
    {
        bSize = buff[1];
        item_len = bSize+3;
    }
    else
    {
        if (bSize == 0x3)
            bSize = 4;
        item_len = bSize+1;
    }

#if ENABLE_DBG_MSG
    for (i = 0; i < item_len; i++)
    {
        printf("%02x ", buff[i]);
    }
    printf("- ");
#endif

    switch (tag)
    {
    /*------------------------------------------------------------------------------------*/
    /*  Main Item Tags                                                                    */
    /*------------------------------------------------------------------------------------*/

    case TAG_INPUT:
        HID_DBGMSG("Input ");
        read_main_item_status(&buff[1]);
        if (_data_usage_cnt > 0)
        {
            int  report_count = _rp_info.report_count;

            for (i = 0; i < _data_usage_cnt; i++)
            {
                _rp_info.report_count = 1;
                _rp_info.data_usage = _data_usages[i];
                if (hid_add_report(hdev, TAG_INPUT) != 0)
                    return USBH_ERR_MEMORY_OUT;
                report_count--;
            }
            _rp_info.report_count = report_count;
            _rp_info.data_usage = 0;
            _data_usage_cnt = 0;
        }
        if (_rp_info.report_count > 0)
        {
            if (hid_add_report(hdev, TAG_INPUT) != 0)
                return USBH_ERR_MEMORY_OUT;
        }
        break;

    case TAG_OUTPUT:
        HID_DBGMSG("Output ");
        read_main_item_status(&buff[1]);
        if (_rp_info.report_count > 0)
        {
            if (hid_add_report(hdev, TAG_OUTPUT) != 0)
                return USBH_ERR_MEMORY_OUT;
        }
        break;

    case TAG_FEATURE:
        HID_DBGMSG("Feature ");
        read_main_item_status(&buff[1]);
        break;

    case TAG_COLLECTION:
        HID_DBGMSG("Collection ");
        if (buff[1] == 0x00)
            HID_DBGMSG("Physical");
        else if (buff[1] == 0x01)
            HID_DBGMSG("Application");
        else if (buff[1] == 0x02)
            HID_DBGMSG("Logical");
        break;

    case TAG_END_COLLECTION:
        HID_DBGMSG("End Collection");
        break;

    /*------------------------------------------------------------------------------------*/
    /*  Global Item Tags                                                                  */
    /*------------------------------------------------------------------------------------*/

    case TAG_USAGE_PAGE:
        HID_DBGMSG("Usage Page ");
        _rp_info.usage_page = buff[1];
        print_usage_page();
        break;

    case TAG_LOGICAL_MIN:
        _rp_info.logical_min = hid_read_item_value(bSize, &buff[1]);
        HID_DBGMSG("Logical Minimum (%d)", _rp_info.logical_min);
        break;

    case TAG_LOGICAL_MAX:
        _rp_info.logical_max = hid_read_item_value(bSize, &buff[1]);
        HID_DBGMSG("Logical Maximum (%d)", _rp_info.logical_max);
        break;

    case TAG_PHYSICAL_MIN:
        _rp_info.physical_min = hid_read_item_value(bSize, &buff[1]);
        HID_DBGMSG("Physical Minimum (%d)", _rp_info.physical_min);
        break;

    case TAG_PHYSICAL_MAX:
        _rp_info.physical_max = hid_read_item_value(bSize, &buff[1]);
        HID_DBGMSG("Physical Maximum (%d)", _rp_info.physical_max);
        break;

    case TAG_UNIT_EXPONENT:
        _rp_info.unit_exponent = hid_read_item_value(bSize, &buff[1]);
        HID_DBGMSG("Unit Exponent (%d)", _rp_info.unit_exponent);
        break;

    case TAG_UNIT:
        _rp_info.unit = hid_read_item_value(bSize, &buff[1]);
        HID_DBGMSG("Unit (%d)", _rp_info.unit);
        break;

    case TAG_REPORT_SIZE:
        _rp_info.report_size = buff[1];
        HID_DBGMSG("Report Size (%d)", _rp_info.report_size);
        break;

    case TAG_REPORT_ID:
        _rp_info.report_id = buff[1];
        hdev->rpd.has_report_id = 1;
        HID_DBGMSG("Report ID (%d)", _rp_info.report_id);
        break;

    case TAG_REPORT_COUNT:
        _rp_info.report_count = buff[1];
        HID_DBGMSG("Report Count (%d)", _rp_info.report_count);
        break;

    case TAG_PUSH:
        HID_DBGMSG("PUSH");
        break;

    case TAG_POP:
        HID_DBGMSG("POP");
        break;

    /*------------------------------------------------------------------------------------*/
    /*  Local Item Tags                                                                   */
    /*------------------------------------------------------------------------------------*/

    case TAG_USAGE:
        if ((buff[1] == USAGE_ID_X) || (buff[1] == USAGE_ID_Y) || (buff[1] == USAGE_ID_WHEEL))
            _data_usages[_data_usage_cnt++] = buff[1];    /* interested usages */
        else
            _rp_info.app_usage = buff[1];
        HID_DBGMSG("Usage ");
        print_usage(buff[1]);
        break;

    case TAG_USAGE_MIN:
        _rp_info.usage_mim = hid_read_item_value(bSize, &buff[1]);
        HID_DBGMSG("Usage Mimimum (%d)", _rp_info.usage_mim);
        break;

    case TAG_USAGE_MAX:
        _rp_info.usage_max = hid_read_item_value(bSize, &buff[1]);
        HID_DBGMSG("Usage Maximum (%d)", _rp_info.usage_max);
        break;

    case TAG_DESIGNATOR_INDEX:
        _rp_info.designator_index = hid_read_item_value(bSize, &buff[1]);
        HID_DBGMSG("Designator Index (%d)", _rp_info.designator_index);
        break;

    case TAG_DESIGNATOR_MIN:
        _rp_info.designator_min = hid_read_item_value(bSize, &buff[1]);
        HID_DBGMSG("Designator Minimum (%d)", _rp_info.designator_min);
        break;

    case TAG_DESIGNATOR_MAX:
        _rp_info.designator_max = hid_read_item_value(bSize, &buff[1]);
        HID_DBGMSG("Designator Maximum (%d)", _rp_info.designator_max);
        break;

    case TAG_STRING_INDEX:
        _rp_info.string_index = hid_read_item_value(bSize, &buff[1]);
        HID_DBGMSG("String Index (%d)", _rp_info.string_index);
        break;

    case TAG_STRING_MIN:
        _rp_info.string_min = hid_read_item_value(bSize, &buff[1]);
        HID_DBGMSG("String Minimum (%d)", _rp_info.string_min);
        break;

    case TAG_STRING_MAX:
        _rp_info.string_max = hid_read_item_value(bSize, &buff[1]);
        HID_DBGMSG("String Maximum (%d)", _rp_info.string_max);
        break;

    case TAG_DELIMITER:
        HID_DBGMSG("Delimiter");
        break;

    default:
        HID_DBGMSG("Unknow tag: 0x%x\n", tag);
        break;
    }
    HID_DBGMSG("\n");

    return item_len;
}


int hid_parse_keyboard_reports(HID_DEV_T *hdev, uint8_t *data, int data_len)
{
    RP_INFO_T   *report;
    int         i, bit;
    int         byte_idx = 0, bit_idx = 0;
    int         has_kbd_event = 0;
    int         report_id;
    static KEYBOARD_EVENT_T  _keyboard_event;

    memset(&_keyboard_event, 0, sizeof(_keyboard_event));
    _keyboard_event.lock_state = hdev->rpd.lock_state;

    /*
     *  Does this device use report ID?
     */
    if (hdev->rpd.has_report_id && (byte_idx == 0))
    {
        report_id = data[0];
        bit_idx = 8;
        byte_idx = 1;
    }

    for (report = hdev->rpd.report; report != NULL; report = report->next)
    {
        if (hdev->rpd.has_report_id && (report->report_id != report_id))
            continue;

        if (report->type != TAG_INPUT)
            continue;

        /*----------------------------------------------------------------------*/
        /*  Extract keyboard report; only KeyCode reports are interested        */
        /*----------------------------------------------------------------------*/
        if ((report->usage_page == UP_KEYCODE) && (report->app_usage == USAGE_ID_KEYBOARD))
        {
            uint32_t   usage_val;

            if ((report->report_size != 1) && (report->report_size != 8))
            {
                /* unlikely! seems violate HID spec. */
                HID_ERRMSG("Keycode report size %d is not supported!\n", report->report_size);
                return USBH_ERR_NOT_SUPPORTED;
            }

            if (report->report_size == 1)
            {
                usage_val = 0;
                for (i = 0; i < report->report_count; i++)
                {
                    bit = (data[byte_idx] >> (bit_idx % 8)) & 0x1;
                    usage_val |= (bit << i);

                    if (bit_idx < 8)            /* is in the first byte         */
                    {
                        _keyboard_event.modifier |= usage_val;
                    }
                    else if (bit_idx < 16)      /* is in the second byte (reserved)  */
                    {
                    }
                    else
                    {
                        if (bit_idx < 8*8)
                            _keyboard_event.keycode[(bit_idx-16)/8] |= usage_val;
                    }
                    bit_idx++;
                }
                byte_idx = (bit_idx / 8);
            }
            else   /* report->report_size == 8 */
            {
                for (i = 0; i < report->report_count; i++)
                {
                    if (byte_idx == 0)
                    {
                        _keyboard_event.modifier = data[byte_idx];
                    }
                    else if (byte_idx == 1)
                    {
                        /* reserved byte */
                    }
                    else
                    {
                        if (byte_idx < 8)
                        {
                            _keyboard_event.keycode[byte_idx-2] = data[byte_idx];
                        }
                    }
                    byte_idx++;
                }
            }
            has_kbd_event = 1;
        }
        else
        {
            /* not interested, just skip it */
            bit_idx += report->report_size * report->report_count;
            byte_idx = (bit_idx / 8);
        }

        if (byte_idx >= data_len)
            break;
    }

    if ((has_kbd_event) && (_keyboard_callback != NULL))
    {
        uint8_t   pressed_lock_keys = 0;
        char      update_LEDs = 0;

        /*----------------------------------------------------------------------*/
        /*  Scan received key code sequence                                     */
        /*----------------------------------------------------------------------*/
        for (i = 0; i < 6; i++)
        {
            switch (_keyboard_event.keycode[i])
            {
            case KEYCODE_NUM_LOCK:
                pressed_lock_keys |= STATE_MASK_NUM_LOCK;
                break;
            case KEYCODE_CAPS_LOCK:
                pressed_lock_keys |= STATE_MASK_CAPS_LOCK;
                break;
            case KEYCODE_SCROLL_LOCK:
                pressed_lock_keys |= STATE_MASK_SCROLL_LOCK;
                break;
            case 0:         /* empty */
            case 1:         /* error */
                break;

            default:
                _keyboard_event.keycode[_keyboard_event.key_cnt++] = _keyboard_event.keycode[i];
            }
        }

        /*----------------------------------------------------------------------*/
        /*  Update lock keys (Num Lock, Caps Lock, Scroll Lock)                 */
        /*----------------------------------------------------------------------*/
        for (i = 0; i < 3; i++)
        {
            if ((pressed_lock_keys & (1<<i)) && (!(hdev->rpd.last_pressed_lock_keys & (1<<i))))
            {
                /*
                 * A lock key pressed and it is not pressed in the last time.
                 * It should be a press down of the lock key.
                 */
                _keyboard_event.lock_state ^= (1<<i);    /* switch on/off the corresponding lock state */
                update_LEDs = 1;
            }
        }
        hdev->rpd.last_pressed_lock_keys = pressed_lock_keys;  /* record the lock key press state for next time. */
        hdev->rpd.lock_state = _keyboard_event.lock_state;

        if (update_LEDs)
        {
            usbh_hid_set_report_non_blocking(hdev, RT_OUTPUT, 0, &_keyboard_event.lock_state, 1);
        }

        _keyboard_callback(hdev, &_keyboard_event);
    }
    return 0;
}

int hid_parse_mouse_reports(HID_DEV_T *hdev, uint8_t *data, int data_len)
{
    int         byte_idx = 0, bit_idx = 0;
    RP_INFO_T   *report;
    int         i, bit;
    int         has_mouse_event = 0;
    int         report_id;
    static MOUSE_EVENT_T  _mouse_event;

    memset(&_mouse_event, 0, sizeof(_mouse_event));

    /*
     *  Does this device use report ID?
     */
    if (hdev->rpd.has_report_id && (byte_idx == 0))
    {
        report_id = data[0];
        bit_idx = 8;
        byte_idx = 1;
    }

    for (report = hdev->rpd.report; report != NULL; report = report->next)
    {
        if (hdev->rpd.has_report_id && (report->report_id != report_id))
            continue;

        if (report->type != TAG_INPUT)
            continue;

        /*----------------------------------------------------------------------*/
        /*  Extract mouse button report                                         */
        /*----------------------------------------------------------------------*/
        if ((report->usage_page == UP_BUTTON) &&
                ((report->app_usage == USAGE_ID_MOUSE) || (report->app_usage == USAGE_ID_POINTER)))
        {
            /* Get button data */
            if (report->status.variable)
            {
                _mouse_event.button_cnt = report->report_count;
                for (i = 0; i < report->report_count; i++)
                {
                    bit = (data[byte_idx] >> (bit_idx % 8)) & 0x1;
                    _mouse_event.button_map |= (bit << i);
                    bit_idx += report->report_size;
                    byte_idx = (bit_idx / 8);
                }
            }
            else
            {
                /* ignore constant padding bits */
                bit_idx += report->report_count * report->report_size;
                byte_idx = (bit_idx / 8);
            }
            has_mouse_event = 1;
        }

        /*----------------------------------------------------------------------*/
        /*  Extract mouse X, Y, and WHEEL reports                               */
        /*----------------------------------------------------------------------*/
        else if ((report->usage_page == UP_GENERIC_DESKTOP) &&
                 ((report->app_usage == USAGE_ID_MOUSE) || (report->app_usage == USAGE_ID_POINTER) ||
                  (report->data_usage == USAGE_ID_WHEEL)))
        {
            uint32_t   usage_val = 0;
            signed     s_val;

            for (i = 0; i < report->report_size; i++)
            {
                bit = (data[byte_idx] >> (bit_idx % 8)) & 0x1;
                usage_val |= (bit << i);
                bit_idx++;
                byte_idx = (bit_idx / 8);
            }

            if (report->report_size <= 8)
                s_val = (signed char)usage_val;
            else if (report->report_size <= 16)
                s_val = (signed short)usage_val;

            if (report->data_usage == USAGE_ID_X)
            {
                _mouse_event.X = s_val;
                _mouse_event.X_raw = usage_val;
                _mouse_event.X_bits = report->report_size;
                _mouse_event.axis_relative = report->status.relative;
                _mouse_event.axis_min = report->logical_min;
                _mouse_event.axis_max = report->logical_max;
            }
            else if (report->data_usage == USAGE_ID_Y)
            {
                _mouse_event.Y = s_val;
                _mouse_event.Y_raw = usage_val;
                _mouse_event.Y_bits = report->report_size;
            }
            else if (report->data_usage == USAGE_ID_WHEEL)
            {
                _mouse_event.wheel = s_val;
                _mouse_event.wheel_raw = usage_val;
                _mouse_event.wheel_bits = report->report_size;
                _mouse_event.wheel_relative = report->status.relative;
                _mouse_event.wheel_min = report->logical_min;
                _mouse_event.wheel_max = report->logical_max;
            }
            has_mouse_event = 1;
        }
        else
        {
            /* not supported, just skip it */
            bit_idx += report->report_size;
            byte_idx = (bit_idx / 8);
        }

        if (byte_idx >= data_len)
            break;
    }

    if ((has_mouse_event) && (_mouse_callback != NULL))
    {
        _mouse_callback(hdev, &_mouse_event);
        // HID_DBGMSG("X: %d, Y: %d, W: %d, button: 0x%x\n", _mouse_event.X, _mouse_event.Y, _mouse_event.wheel, _mouse_event.button_map);
    }

    return 0;
}


/// @endcond HIDDEN_SYMBOLS


