/**************************************************************************//**
 * @file     usbh_lib.h
 * @version  V1.10
 * $Revision: 4 $
 * $Date: 15/06/10 2:06p $
 * @brief    USB Host driver header file
 *
 * @note
 * Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef  _USBH_LIB_H_
#define  _USBH_LIB_H_

#include "M480.h"

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup M480_Library M480 Library
  @{
*/

/** @addtogroup M480_USBH_Library USB Host Library
  @{
*/

/** @addtogroup M480_USBH_EXPORTED_CONSTANTS USB Host Exported Constants
  @{
*/

#define USBH_OK                     0      /*!< No error.                              \hideinitializer */
#define USBH_ERR_MEMORY_OUT         -1001  /*!< Out of memory.                         \hideinitializer */
#define USBH_ERR_EHCI_INIT          -1003  /*!< Failed to initialize EHCI controller.  \hideinitializer */
#define USBH_ERR_OHCI_INIT          -1005  /*!< Failed to initialize OHIC controller.  \hideinitializer */

#define UMAS_OK                     0      /*!< No error.                              \hideinitializer */
#define UMAS_ERR_NO_DEVICE          -1031  /*!< USB mass storage device not found.     \hideinitializer */
#define UMAS_ERR_IO                 -1033  /*!< Device read/write failed.              \hideinitializer */
#define UMAS_ERR_IVALID_PARM        -1038  /*!< Invalid parameter.                     \hideinitializer */

#define UVC_OK                      0      /*!< No error.                              \hideinitializer */
#define UVC_ERR_MEMORY_OUT          -1051  /*!< Out of memory.                         \hideinitializer */
#define UVC_ERR_NO_DEVICE           -1052  /*!< There's no UVC device connected.       \hideinitializer */
#define UVC_ERR_NO_STREAM           -1053  /*!< UVC video stream is not enbled.        \hideinitializer */
#define UVC_NO_NEW_IMAGE            -1054  /*!< There's no image queued.               \hideinitializer */
#define UVC_ERR_USB_XFER            -1055  /*!< USB data transfer error.               \hideinitializer */
#define UVC_ERR_BUSY                -1056  /*!< UVC device is busy.                    \hideinitializer */
#define UVC_ERR_IVALID_PARM         -1058  /*!< Invalid parameter.                     \hideinitializer */
#define UVC_ERR_NOT_AVAILABLE       -1059  /*!< Feature or format not supported.       \hideinitializer */

#define HID_RET_OK                  0      /*!< Return with no errors.                 \hideinitializer */
#define HID_RET_DEV_NOT_FOUND       -1081  /*!< HID device not found or removed.       \hideinitializer */
#define HID_RET_IO_ERR              -1082  /*!< USB transfer failed.                   \hideinitializer */
#define HID_RET_INVALID_PARAMETER   -1083  /*!< Invalid parameter.                     \hideinitializer */
#define HID_RET_OUT_OF_MEMORY       -1084  /*!< Out of memory.                         \hideinitializer */
#define HID_RET_NOT_SUPPORTED       -1085  /*!< Function not supported.                \hideinitializer */
#define HID_RET_EP_NOT_FOUND        -1086  /*!< Endpoint not found.                    \hideinitializer */
#define HID_RET_EP_USED             -1087  /*!< Endpoint transfer has been enabled early.  \hideinitializer */

#define UAC_RET_OK                   0     /*!< Return with no errors.                 \hideinitializer */
#define UAC_RET_DEV_NOT_FOUND       -2001  /*!< Audio Class device not found or removed.  \hideinitializer */
#define UAC_RET_IO_ERR              -2003  /*!< USB transfer failed.                   \hideinitializer */
#define UAC_RET_INVALID             -2005  /*!< Invalid parameter or usage.            \hideinitializer */
#define UAC_RET_OUT_OF_MEMORY       -2007  /*!< Out of memory.                         \hideinitializer */
#define UAC_RET_DRV_NOT_SUPPORTED   -2009  /*!< Function not supported by this UAC driver.  \hideinitializer */
#define UAC_RET_DEV_NOT_SUPPORTED   -2011  /*!< Function not supported by the UAC device.  \hideinitializer */

#define UVC_FORMAT_YUYV             0x1    /*!< Select YUYV image format.              \hideinitializer */
#define UVC_FORMAT_MJPEG            0x31   /*!< Select motion JPEG image format.       \hideinitializer */
#define UVC_FORMAT_H264             0x41   /*!< Select H.264 image format.             \hideinitializer */


/*@}*/ /* end of group M480_USBH_EXPORTED_CONSTANTS */



/** @addtogroup M480_USBH_EXPORTED_TYPEDEFS USB Host Exported Type Define
  @{
*/
struct usbhid_dev;
typedef void (HID_IR_FUNC)(struct usbhid_dev *hdev, uint16_t ep_addr, uint8_t *rdata, uint32_t data_len);      /*!< interrupt in callback function \hideinitializer */
typedef void (HID_IW_FUNC)(struct usbhid_dev *hdev, uint16_t ep_addr, uint8_t **wbuff, uint32_t *buff_size);   /*!< interrupt out callback function \hideinitializer */

struct uac_dev_t;
typedef int (UAC_CB_FUNC)(struct uac_dev_t *dev, uint8_t *data, int len);    /*!< audio in callback function \hideinitializer */

/*@}*/ /* end of group M480_USBH_EXPORTED_TYPEDEFS */



/** @addtogroup M480_USBH_EXPORTED_FUNCTIONS USB Host Exported Functions
  @{
*/

/*------------------------------------------------------------------*/
/*                                                                  */
/*  USB Core Library APIs                                           */
/*                                                                  */
/*------------------------------------------------------------------*/
extern void usbh_core_init(void);
extern int  usbh_pooling_hubs(void);
extern void usbh_suspend(void);
extern void usbh_resume(void);


/*------------------------------------------------------------------*/
/*                                                                  */
/*  USB Human Interface Class Library APIs                          */
/*                                                                  */
/*------------------------------------------------------------------*/
extern void     usbh_hid_init(void);
extern struct usbhid_dev * usbh_hid_get_device_list(void);
extern int32_t  usbh_hid_get_report_descriptor(struct usbhid_dev *hdev, uint8_t *desc_buf, int buf_max_len);
extern int32_t  usbh_hid_get_report(struct usbhid_dev *hdev, int rtp_typ, int rtp_id, uint8_t *data, int len);
extern int32_t  usbh_hid_set_report(struct usbhid_dev *hdev, int rtp_typ, int rtp_id, uint8_t *data, int len);
extern int32_t  usbh_hid_get_idle(struct usbhid_dev *hdev, int rtp_id, uint8_t *idle_rate);
extern int32_t  usbh_hid_set_idle(struct usbhid_dev *hdev, int rtp_id, uint8_t idle_rate);
extern int32_t  usbh_hid_get_protocol(struct usbhid_dev *hdev, uint8_t *protocol);
extern int32_t  usbh_hid_set_protocol(struct usbhid_dev *hdev, uint8_t protocol);
extern int32_t  usbh_hid_start_int_read(struct usbhid_dev *hdev, uint8_t ep_addr, HID_IR_FUNC *func);
extern int32_t  usbh_hid_stop_int_read(struct usbhid_dev *hdev, uint8_t ep_addr);
extern int32_t  usbh_hid_start_int_write(struct usbhid_dev *hdev, uint8_t ep_addr, HID_IW_FUNC *func);
extern int32_t  usbh_hid_stop_int_write(struct usbhid_dev *hdev, uint8_t ep_addr);

/*------------------------------------------------------------------*/
/*                                                                  */
/*  USB Mass Storage Class Library APIs                             */
/*                                                                  */
/*------------------------------------------------------------------*/
extern int  usbh_umas_init(void);
extern int  usbh_umas_disk_status(int drv_no);
extern int  usbh_umas_disk_sector_size(int drv_no);
extern int  usbh_umas_read(int drv_no, uint32_t sec_no, int sec_cnt, uint8_t *buff);
extern int  usbh_umas_write(int drv_no, uint32_t sec_no, int sec_cnt, uint8_t *buff);
extern int  usbh_umas_ioctl(int drv_no, int cmd, void *buff);

/*------------------------------------------------------------------*/
/*                                                                  */
/*  USB Audio Class Library APIs                                    */
/*                                                                  */
/*------------------------------------------------------------------*/
extern void usbh_uac_init(void);
extern struct uac_dev_t * usbh_uac_get_device_list(void);
extern int usbh_uac_get_channel_number(struct uac_dev_t *audev, uint8_t target);
extern int usbh_uac_get_bit_resolution(struct uac_dev_t *audev, uint8_t target, uint8_t *byte_cnt);
extern int usbh_uac_get_sampling_rate(struct uac_dev_t *audev, uint8_t target, uint32_t *srate_list, int max_cnt, uint8_t *type);
extern int usbh_uac_sampling_rate_control(struct uac_dev_t *audev, uint8_t target, uint8_t req, uint32_t *srate);
extern int usbh_uac_mute_control(struct uac_dev_t *audev, uint8_t target, uint8_t req, uint16_t chn, uint8_t *mute);
extern int usbh_uac_vol_control(struct uac_dev_t *audev, uint8_t target, uint8_t req, uint16_t chn, uint16_t *volume);
extern int usbh_uac_auto_gain_control(struct uac_dev_t *audev, uint8_t target, uint8_t req, uint16_t chn, uint8_t *mute);
extern int usbh_uac_install_iso_in_callback(struct uac_dev_t *audev, uint8_t *au_in_buff, int bufsiz, UAC_CB_FUNC *func);
extern int usbh_uac_start_iso_in(struct uac_dev_t *audev);
extern int usbh_uac_stop_iso_in(struct uac_dev_t *audev);
extern int usbh_uac_install_iso_out_callback(struct uac_dev_t *audev, UAC_CB_FUNC *func);
extern int usbh_uac_start_iso_out(struct uac_dev_t *audev);
extern int usbh_uac_stop_iso_out(struct uac_dev_t *audev);


/// @cond HIDDEN_SYMBOLS

extern void dump_ohci_regs(void);
extern void dump_ehci_regs(void);
extern void dump_ohci_ports(void);
extern void dump_ehci_ports(void);

/// @endcond HIDDEN_SYMBOLS


/*@}*/ /* end of group M480_USBH_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M480_USBH_Library */

/*@}*/ /* end of group M480_Library */

#ifdef __cplusplus
}
#endif

#endif  /* _USBH_LIB_H_ */

/*** (C) COPYRIGHT 2015 Nuvoton Technology Corp. ***/



