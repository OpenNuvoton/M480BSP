/**************************************************************************//**
 * @file     usbh_hid.h
 * @version  V1.10
 * @brief    USB Host HID class driver header file.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
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
#define HID_DBGMSG   printf
//#define HID_DBGMSG(...)
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
    struct usbhid_dev   *next;          /*!< Point to the next HID device                      */
} HID_DEV_T;                            /*! HID device structure                               */

/*@}*/ /* end of group USBH_EXPORTED_STRUCTURES */


/*@}*/ /* end of group USBH_Library */

/*@}*/ /* end of group Library */

#ifdef __cplusplus
}
#endif

#endif  /* _USBH_HID_H_ */

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/



