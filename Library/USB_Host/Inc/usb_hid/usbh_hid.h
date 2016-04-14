/**************************************************************************//**
 * @file     usbh_hid.h
 * @version  V1.10
 * $Revision: 2 $
 * $Date: 15/06/12 9:58a $
 * @brief    USB Host HID class driver header file
 *
 * @note
 * Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef  _USBH_HID_H_
#define  _USBH_HID_H_

#include "M480.h"

#ifdef __cplusplus
extern "C"
{
#endif

/// @cond HIDDEN_SYMBOLS
#define HID_DBGMSG   printf
//#define HID_DBGMSG(...)
/// @endcond HIDDEN_SYMBOLS


/** @addtogroup M480_Library M480 Library
  @{
*/

/** @addtogroup M480_USBH_Library USB Host Library
  @{
*/

/** @addtogroup M480_USBH_EXPORTED_CONSTANTS USB Host Exported Constants
  @{
*/

#define CONFIG_HID_MAX_DEV          8      /*!< Allowed maximum number of HID devices connected at the same time.  */
#define HID_CLIENT_SIZE             1024   /*!< Supported maximum Size of HID device user data area.               */

/// @cond HIDDEN_SYMBOLS
#define USB_DT_HID                      (USB_TYPE_CLASS | 0x01)
#define USB_DT_REPORT                   (USB_TYPE_CLASS | 0x02)
/// @endcond HIDDEN_SYMBOLS

#define HID_REPORT_GET              0x01   /*!< HID Class command Get_Report_Request code.        */
#define HID_GET_IDLE                0x02   /*!< HID Class command Get_Idle code.                  */
#define HID_GET_PROTOCOL            0x03   /*!< HID Class command Get_Protocol code.              */
#define HID_REPORT_SET              0x09   /*!< HID Class command Set_Report_Request code.        */
#define HID_SET_IDLE                0x0A   /*!< HID Class command Set_Idle code.                  */
#define HID_SET_PROTOCOL            0x0B   /*!< HID Class command Set_Protocol code.              */

/* HID Report type */
#define RT_INPUT                    1      /*!< Report type: Input             \hideinitializer */
#define RT_OUTPUT                   2      /*!< Report type: Output            \hideinitializer */
#define RT_FEATURE                  3      /*!< Report type: Feature           \hideinitializer */


/*@}*/ /* end of group M480_USBH_EXPORTED_CONSTANTS */


/** @addtogroup M480_USBH_EXPORTED_STRUCTURES USB Host Exported Structures
  @{
*/

/*-----------------------------------------------------------------------------------
 *  HID device
 */
/*! HID device structure \hideinitializer             */
typedef struct usbhid_dev {
    struct usb_device   *udev;          /*!< USB device pointer of HID_DEV_T                   */
    uint16_t            idVendor;       /*!< USB device vendor ID. (from device descriptor)    */
    uint16_t            idProduct;      /*!< USB device product ID. (from device descriptor)   */
    struct usb_interface *intf;         /*!< USB interface                                     */
    int                 ifnum;          /*!< USB interface number                              */
    uint8_t             bSubClassCode;  /*!< Interface subclass code                           */
    uint8_t             bProtocolCode;  /*!< Interface protocol code                           */
    struct urb          *urb_in[16];    /*!< Array of in-endpoint URBs                         */
    struct urb          *urb_out[16];   /*!< Array of out-endpoint URBs                        */
    HID_IR_FUNC         *read_func;     /*!< Interrupt-in callback function                    */
    HID_IW_FUNC         *write_func;    /*!< Interrupt-out callback function                   */
    struct usbhid_dev   *next;          /*!< Point to the next HID device                      */
    uint8_t             client[HID_CLIENT_SIZE];  /*!< HID driver client can use this buffer to carry user data. */
} HID_DEV_T;                            /*! HID device structure                               */

/*@}*/ /* end of group M480_USBH_EXPORTED_STRUCTURES */


/*@}*/ /* end of group M480_USBH_Library */

/*@}*/ /* end of group M480_Library */

#ifdef __cplusplus
}
#endif

#endif  /* _USBH_HID_H_ */

/*** (C) COPYRIGHT 2015 Nuvoton Technology Corp. ***/



