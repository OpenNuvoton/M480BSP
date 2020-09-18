/**************************************************************************//**
 * @file     usbh_hid.h
 * @version  V1.10
 * @brief    USB Host HID class driver header file.
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef  _USBH_HID_H_
#define  _USBH_HID_H_

#include "NuMicro.h"
#include "usb.h"

#ifdef __cplusplus
extern "C"
{
#endif

/// @cond HIDDEN_SYMBOLS

#define ENABLE_ERR_MSG          1
#define ENABLE_DBG_MSG          0

#if ENABLE_ERR_MSG
#define HID_ERRMSG   printf
#else
#define HID_ERRMSG(...)
#endif

#if ENABLE_DBG_MSG
#define HID_DBGMSG   printf
#else
#define HID_DBGMSG(...)
#endif

/// @endcond HIDDEN_SYMBOLS


/** @addtogroup LIBRARY Library
  @{
*/

/** @addtogroup USBH_Library USB Host Library
  @{
*/

/** @addtogroup USBH_EXPORTED_CONSTANTS USB Host Exported Constants
  @{
*/

#define CONFIG_HID_MAX_DEV          4      /*!< Maximum number of HID devices (interface) allowed at the same time.  */
#define CONFIG_HID_DEV_MAX_PIPE     8      /*!< Maximum number of interrupt in/out pipes allowed per HID device      */

/// @cond HIDDEN_SYMBOLS

#define HID_DESCRIPTOR_TYPE         0x21
#define REPORT_DESCRIPTOR_TYPE      0x22

#define HID_SUBCLASS_BOOT_DEVICE    0x01   /*!< bInterfaceSubClass: boot device interface   */

#define HID_PROTOCOL_KEYBOARD       0x01   /*!< bInterfaceProtocol: Keyboard                */
#define HID_PROTOCOL_MOUSE          0x02   /*!< bInterfaceProtocol: Mouse                   */

/*-----------------------------------------------------------------------------------
 *  Short Item Tags
 */

/* Main item tag (tag & 0xFC) */
#define TAG_INPUT                   0x80
#define TAG_OUTPUT                  0x90
#define TAG_FEATURE                 0xB0
#define TAG_COLLECTION              0xA0
#define TAG_END_COLLECTION          0xC0


/* Global item tag (tag & 0xFC) */
#define TAG_USAGE_PAGE              0x04
#define TAG_LOGICAL_MIN             0x14
#define TAG_LOGICAL_MAX             0x24
#define TAG_PHYSICAL_MIN            0x34
#define TAG_PHYSICAL_MAX            0x44
#define TAG_UNIT_EXPONENT           0x54
#define TAG_UNIT                    0x64
#define TAG_REPORT_SIZE             0x74
#define TAG_REPORT_ID               0x84
#define TAG_REPORT_COUNT            0x94
#define TAG_PUSH                    0xA4
#define TAG_POP                     0xB4

/* Local item tag (tag & 0xFC) */
#define TAG_USAGE                   0x08
#define TAG_USAGE_MIN               0x18
#define TAG_USAGE_MAX               0x28
#define TAG_DESIGNATOR_INDEX        0x38
#define TAG_DESIGNATOR_MIN          0x48
#define TAG_DESIGNATOR_MAX          0x58
#define TAG_STRING_INDEX            0x78
#define TAG_STRING_MIN              0x88
#define TAG_STRING_MAX              0x98
#define TAG_DELIMITER               0xA8

/* Collection */
#define COLLECT_PHYSICAL            0x00        /* group of axes                    */
#define COLLECT_APPLICATION         0x01        /* mouse, keyboard                  */
#define COLLECT_LOGICAL             0x02        /* interrelated data                */
#define COLLECT_VENDOR              0xFF        /* 0x80-0xFF Vendor-defined         */

/*-----------------------------------------------------------------------------------
 *  Usage Page
 */
#define UP_GENERIC_DESKTOP          0x01
#define UP_SIMULATION_CONTROLS      0x02
#define UP_VR_CONTROLS              0x03
#define UP_SPORT_CONTROLS           0x04
#define UP_GAME_CONTROLS            0x05
#define UP_KEYCODE                  0x07
#define UP_LEDS                     0x08
#define UP_BUTTON                   0x09
#define UP_ORDINAL                  0x0A
#define UP_TELEPHONY                0x0B
#define UP_CONSUMER                 0x0C
#define UP_DIGITIZER                0x0D
#define UP_PID_PAGE                 0x0F
#define UP_UNICODE                  0x10
#define UP_BARCODE_SCANNER          0x8C

/* Usage ID of Generic Desktop Page */
#define USAGE_ID_POINTER            0x01
#define USAGE_ID_MOUSE              0x02
#define USAGE_ID_JOYSTICK           0x04
#define USAGE_ID_GAMEPAD            0x05
#define USAGE_ID_KEYBOARD           0x06
#define USAGE_ID_KEYPAD             0x07
#define USAGE_ID_X                  0x30
#define USAGE_ID_Y                  0x31
#define USAGE_ID_Z                  0x32
#define USAGE_ID_WHEEL              0x38

#define KEYCODE_CAPS_LOCK           0x39
#define KEYCODE_SCROLL_LOCK         0x47
#define KEYCODE_NUM_LOCK            0x53

#define STATE_MASK_NUM_LOCK         0x01
#define STATE_MASK_CAPS_LOCK        0x02
#define STATE_MASK_SCROLL_LOCK      0x04

/// @endcond HIDDEN_SYMBOLS


/// @cond HIDDEN_SYMBOLS
#define USB_DT_HID                  (REQ_TYPE_CLASS_DEV | 0x01)
#define USB_DT_REPORT               (REQ_TYPE_CLASS_DEV | 0x02)
/// @endcond HIDDEN_SYMBOLS

#define HID_REPORT_GET              0x01   /*!< HID Class command Get_Report_Request code.        */
#define HID_GET_IDLE                0x02   /*!< HID Class command Get_Idle code.                  */
#define HID_GET_PROTOCOL            0x03   /*!< HID Class command Get_Protocol code.              */
#define HID_REPORT_SET              0x09   /*!< HID Class command Set_Report_Request code.        */
#define HID_SET_IDLE                0x0A   /*!< HID Class command Set_Idle code.                  */
#define HID_SET_PROTOCOL            0x0B   /*!< HID Class command Set_Protocol code.              */

/* HID Report type */
#define RT_INPUT                    1      /*!< Report type: Input               \hideinitializer */
#define RT_OUTPUT                   2      /*!< Report type: Output              \hideinitializer */
#define RT_FEATURE                  3      /*!< Report type: Feature             \hideinitializer */


/*@}*/ /* end of group USBH_EXPORTED_CONSTANTS */


/** @addtogroup USBH_EXPORTED_STRUCTURES USB Host Exported Structures
  @{
*/

/// @cond HIDDEN_SYMBOLS
/*
 *  HID Descriptor
 */
#ifdef __ICCARM__
typedef struct hid_descriptor
{
    __packed uint8_t  bLength;          /*!< Length of interface descriptor         */
    __packed uint8_t  bDescriptorType;  /*!< HID Descriptor type; 0x21              */
    __packed uint16_t bcdHID;           /*!< HID Class Specification release number */
    __packed uint8_t  bCountryCode;     /*!< Hardware target country                */
    __packed uint8_t  bNumDescriptors;  /*!< Number of HID class descriptors to follow */
    __packed uint8_t  bRPDescType;      /*!< Report descriptor type; 0x22           */
    __packed uint16_t wDescriptorLength;/*!< Total length of Report descriptor      */
} DESC_HID_T;
#else
typedef struct __attribute__((__packed__)) hid_descriptor
{
    uint8_t  bLength;                   /*!< Length of interface descriptor         */
    uint8_t  bDescriptorType;           /*!< HID Descriptor type; 0x21              */
    uint16_t bcdHID;                    /*!< HID Class Specification release number */
    uint8_t  bCountryCode;              /*!< Hardware target country                */
    uint8_t  bNumDescriptors;           /*!< Number of HID class descriptors to follow */
    uint8_t  bRPDescType;               /*!< Report descriptor type; 0x22           */
    uint16_t wDescriptorLength;         /*!< Total length of Report descriptor      */
} DESC_HID_T;
#endif

typedef struct report_info
{
    uint8_t         type;               /* TAG_INPUT, TAG_OUTPUT, or TAG_FEATURE    */
    uint8_t         usage_page;
    uint8_t         app_usage;
    uint8_t         data_usage;
    signed int      usage_mim;
    signed int      usage_max;
    signed int      logical_min;
    signed int      logical_max;
    signed int      physical_min;
    signed int      physical_max;
    signed int      unit_exponent;
    signed int      unit;
    signed int      designator_index;
    signed int      designator_min;
    signed int      designator_max;
    signed int      string_index;
    signed int      string_min;
    signed int      string_max;
    uint8_t         report_id;
    uint8_t         report_size;
    uint8_t         report_count;
    struct
    {
        uint32_t    constant:1;         /* {Data (0) | Constant (1)}                */
        uint32_t    variable:1;         /* {Array (0) | Variable (1)}               */
        uint32_t    relative:1;         /* {Absolute (0) | Relative (1)}            */
        uint32_t    wrap:1;             /* {No Wrap (0) | Wrap (1)}                 */
        uint32_t    non_linear:1;       /* {Linear (0) | Non Linear (1)}            */
        uint32_t    no_preferred:1;     /* {Preferred State (0) | No Preferred (1)} */
        uint32_t    null_state:1;       /* {No Null position (0) | Null state(1)}   */
        uint32_t    is_volatile:1;      /* {Non Volatile (0) | Volatile (1)}        */
        uint32_t    buffered_bytes:1;   /* {Bit Field (0) | Buffered Bytes (1)}     */
        uint32_t    reserved:23;        /* Reserved (0)                             */
    } status;
    struct report_info  *next;
} RP_INFO_T;

static uint8_t  _designator_index, _designator_min, _designator_max;
static uint8_t  _string_index, _string_max, _string_min;


typedef struct rp_desc_info
{
    uint8_t     has_report_id;          /* If a Report ID tag is used anywhere in Report descriptor, all data reports for the device are preceded by a single byte ID field. */
    uint8_t     last_pressed_lock_keys; /* Recording the key-press state of last time (for keyboard)  */
    uint8_t     lock_state;             /*!< bit0: Num Lock; bit1: Caps Lock, bit2: Scroll Lock. 1 is in lock state.  */
    char        utr_led_idle;           /* recording if the utr_led is in idle or not                 */
    UTR_T       *utr_led;               /* UTR for LED control                                        */
    RP_INFO_T   *report;
} RPD_T;

/// @endcond HIDDEN_SYMBOLS


/*---------------------------------------------------------------------------------------------*/
/*  HID device                                                                                 */
/*---------------------------------------------------------------------------------------------*/
/*! HID device structure \hideinitializer                                                      */
typedef struct usbhid_dev
{
    uint16_t      idVendor;             /*!< USB device vendor ID. (from device descriptor)    */
    uint16_t      idProduct;            /*!< USB device product ID. (from device descriptor)   */
    uint8_t       bSubClassCode;        /*!< Interface subclass code                           */
    uint8_t       bProtocolCode;        /*!< Interface protocol code                           */
    HID_IR_FUNC   *read_func;           /*!< Interrupt-in callback function                    */
    HID_IW_FUNC   *write_func;          /*!< Interrupt-out callback function                   */
    UTR_T         *utr_list[CONFIG_HID_DEV_MAX_PIPE];  /*!< UTR list of all INT in and out pipes in running  */
    UTR_T         *out_utr_list;        /*!< UTR list of INT out endpoints                     */
    void          *iface;               /*!< This HID interface                                */
    uint32_t      uid;                  /*!< The unique ID to identify a HID device.           */
    RPD_T         rpd;                  /*!< Information of Report Descriptor                  */
    struct usbhid_dev   *next;          /*!< Point to the next HID device                      */
} HID_DEV_T;                            /*! HID device structure                               */

/*---------------------------------------------------------------------------------------------*/
/*  HID keyboard event.                                                                        */
/*  HID driver delivers the keyboarde event to user application via callback function.         */
/*---------------------------------------------------------------------------------------------*/
/*! HID mouse information structure \hideinitializer                                           */
typedef struct usbhid_keyboard_event
{
    uint8_t       lock_state;           /*!< bit0: Num Lock; bit1: Caps Lock, bit2: Scroll Lock. 1 is in lock state.  */
    uint8_t       modifier;
    uint8_t       keycode[6];           /*!< The key code received from keyboard.              */
    uint8_t       key_cnt;              /*!< The number of key code available in keycode[]     */
} KEYBOARD_EVENT_T;

/*---------------------------------------------------------------------------------------------*/
/*  HID mouse event.                                                                           */
/*  HID driver delivers the mouse event to user application via callback function.             */
/*---------------------------------------------------------------------------------------------*/
/*! HID mouse information structure \hideinitializer                                           */
typedef struct usbhid_mouse_event
{
    uint8_t       axis_relative;        /*!< X,Y axis vlaue is relative(1) or absolute(0)      */
    uint8_t       wheel_relative;       /*!< Wheel vlaue is relative(1) or absolute(0)         */
    uint8_t       button_cnt;           /*!< Number of buttons                                 */
    uint32_t      button_map;           /*!< bit0 for button 0, bit1 for button 1, ...         */
    signed int    axis_min;             /*!< Logical minimum of mouse X,Y axis value           */
    signed int    axis_max;             /*!< Logical maxmum of mouse X,Y axis value            */
    signed int    X;                    /*!< mouse X axis value                                */
    signed int    Y;                    /*!< mouse Y axis value                                */
    signed int    wheel_min;            /*!< Logical minimum of mouse wheel value              */
    signed int    wheel_max;            /*!< Logical maxmum of mouse wheel value               */
    signed int    wheel;                /*!< mouse wheel value                                 */
    int           X_bits;               /*!< X axis bit resolution                             */
    int           Y_bits;               /*!< Y axis bit resolution                             */
    int           wheel_bits;           /*!< wheel bit resolution                              */
    uint32_t      X_raw;                /*!< mouse report X axis raw data                      */
    uint32_t      Y_raw;                /*!< mouse report Y axis raw data                      */
    uint32_t      wheel_raw;            /*!< mouse report wheel raw data                       */
} MOUSE_EVENT_T;

typedef void (HID_MOUSE_FUNC)(struct usbhid_dev *hdev, MOUSE_EVENT_T *mouse);      /*!< HID mouse event callback \hideinitializer */
typedef void (HID_KEYBOARD_FUNC)(struct usbhid_dev *hdev, KEYBOARD_EVENT_T *kbd);  /*!< HID keyboard event callback \hideinitializer */

/*@}*/ /* end of group USBH_EXPORTED_STRUCTURES */


/** @addtogroup USBH_EXPORTED_FUNCTIONS USB Host Exported Functions
  @{
*/

void usbh_hid_regitser_mouse_callback(HID_MOUSE_FUNC *func);
void usbh_hid_regitser_keyboard_callback(HID_KEYBOARD_FUNC *func);

/// @cond HIDDEN_SYMBOLS
int hid_parse_report_descriptor(HID_DEV_T *hdev, IFACE_T *iface);
int hid_parse_keyboard_reports(HID_DEV_T *hdev, uint8_t *data, int data_len);
int hid_parse_mouse_reports(HID_DEV_T *hdev, uint8_t *data, int data_len);
int32_t  usbh_hid_set_report_non_blocking(HID_DEV_T *hdev, int rtp_typ, int rtp_id, uint8_t *data, int len);
/// @endcond HIDDEN_SYMBOLS

/*@}*/ /* end of group USBH_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group USBH_Library */

/*@}*/ /* end of group Library */

#ifdef __cplusplus
}
#endif

#endif  /* _USBH_HID_H_ */

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/



