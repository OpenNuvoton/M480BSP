#ifndef __INCLUDED_USBHUAC_H__
#define __INCLUDED_USBHUAC_H__

#include "M480.h"

#include "usb.h"
#include "usbh_lib.h"

/** @addtogroup M480_Library M480 Library
  @{
*/

/** @addtogroup M480_USBH_Library USB Host Library
  @{
*/

/** @addtogroup M480_USBH_EXPORTED_CONSTANTS USB Host Exported Constants
  @{
*/


#define CONFIG_AU_MAX_DEV            3      /*!< Maximum number of Audio Class device.  */
#define MAX_CFG_DESC_SIZE            512    /*!< The acceptable maximum size of Audio Class device configuration descriptor.  */
#define MAX_FEATURE_UNIT             16     /*!< The acceptable maximum number of feature units.           */
#define UAC_ISO_FRAME                8      /*!< Number of isochronous frame per URB.                      */
#define ISO_IN_URB_CNT               2      /*!< Number of USB transfer blocks used by audio in stream.    */
#define ISO_OUT_URB_CNT              2      /*!< Number of USB transfer blocks used by audio out stream.   */
#define AU_IN_MAX_PKTSZ              384    /*!< Audio in maximum packet size supported.                   */
#define AU_OUT_MAX_PKTSZ             384    /*!< Audio in maximum packet size supported.                   */
#define UAC_REQ_TIMEOUT              10000  /*!< UAC control request timeout value in miniseconds.         */

#define UAC_SPEAKER                  1      /*!< Control target is speaker of UAC device. \hideinitializer */
#define UAC_MICROPHONE               2      /*!< Control target is microphone of UAC device. \hideinitializer */

/*
 * Audio Class-Specific Request Codes
 */
#define UAC_SET_CUR                  0x01   /*!< UAC request to set current value.        */
#define UAC_GET_CUR                  0x81   /*!< UAC request to get current value.        */
#define UAC_SET_MIN                  0x02   /*!< UAC request to set lower-bound setting.  */
#define UAC_GET_MIN                  0x82   /*!< UAC request to get lower-bound setting.  */
#define UAC_SET_MAX                  0x03   /*!< UAC request to set upper-bound setting.  */
#define UAC_GET_MAX                  0x83   /*!< UAC request to get upper-bound setting.  */
#define UAC_SET_RES                  0x04   /*!< UAC request to set resolution.           */
#define UAC_GET_RES                  0x84   /*!< UAC request to get resolution.           */
#define UAC_GET_STAT                 0xFF   /*!< UAC request to get status.               */

/*
 * Audio Class-Specific Channel selection
 */
#define UAC_CH_MASTER                0      /*!< Select all channels.  \hideinitializer */
#define UAC_CH_LEFT_FRONT            1      /*!< Select Left Front (L) channel. \hideinitializer */
#define UAC_CH_RIGHT_FRONT           2      /*!< Select Right Front (R) channel.  \hideinitializer */
#define UAC_CH_CENTER_FRONT          3      /*!< Select Center Front (C) channel. \hideinitializer */
#define UAC_CH_LOW_FREQ_EN           4      /*!< Select Low Frequency Enhancement. (LFE) channel \hideinitializer */
#define UAC_CH_LEFT_SRN              5      /*!< Select Left Surround (LS) channel. \hideinitializer */
#define UAC_CH_RIGHT_SRN             6      /*!< Select Right Surround (RS) channel. \hideinitializer */
#define UAC_CH_LEFT_OF_CENTER        7      /*!< Select Left of Center (LC) channel. \hideinitializer */
#define UAC_CH_RIGHT_OF_CENTER       8      /*!< Select Right of Center (RC) channel. \hideinitializer */
#define UAC_CH_SURROUND              9      /*!< Select Surround (S) channel. \hideinitializer */
#define UAC_CH_SIDE_LEFT             10     /*!< Select Side Left (SL) channel. \hideinitializer */
#define UAC_CH_SIDE_RIGHT            11     /*!< Select Side Right (SR) channel. \hideinitializer */
#define UAC_CH_TOP                   12     /*!< Select Top (T) channel. \hideinitializer */

/*@}*/ /* end of group M480_USBH_EXPORTED_CONSTANTS */



/** @addtogroup M480_USBH_EXPORTED_STRUCTURES USB Host Exported Structures
  @{
*/

/*-----------------------------------------------------------------------------------
 *  Audio Class device
 */
/*!< Audio Class device structure   */
typedef struct uac_dev_t {
    struct usb_device  *udev;                     /*!< USB device pointer of UAC_DEV_T.            */
    int                 ctrl_ifnum;               /*!< Audio control interface numder.             */
    int                 au_in_ifnum;              /*!< Audio data-in interface numder.             */
    int                 au_out_ifnum;             /*!< Audio data-out interface numder.            */
    void                *priv;                    /*!< Internal used by audio class driver.        */
    struct uac_dev_t    *next;                    /*!< Point to the next Audio Class device.       */

    /*
     *  The followings are used for audio streaming.
     */
    struct usb_host_endpoint  *ep_au_in;          /*!< Audio data input endoint.                   */
    struct usb_host_endpoint  *ep_au_out;         /*!< Audio data output endoint.                  */
    struct urb *        urbin[ISO_IN_URB_CNT];    /*!< Audio data input URB.                       */
    struct urb *        urbout[ISO_OUT_URB_CNT];  /*!< Audio data output URB.                      */
    uint8_t             in_streaming;             /*!< Audio data in is streaming or not.          */
    uint8_t             out_streaming;            /*!< Audio data out is streaming or not.         */

    /*
     *  The followings are used for interworking with user application.
     */
    UAC_CB_FUNC         *au_in_func;              /*!< Audio data input callback function.         */
    UAC_CB_FUNC         *au_out_func;             /*!< Audio data output callback function.        */
    uint8_t             *au_in_buff;              /*!< Point to the user provided audio input buffer.    */
    int                 au_in_bufsz;              /*!< Size of au_in_buff \hideinitializer.        */
    int                 au_in_bufidx;             /*!< Index for Audio Class driver writing au_in_buff.  */
} UAC_DEV_T;                                      /*! Audio Class device structure.                */


/*@}*/ /* end of group M480_USBH_EXPORTED_STRUCTURES */


#ifdef __cplusplus
extern "C" {
#endif

/*@}*/ /* end of group M480_USBH_Library  */

/*@}*/ /* end of group M480_Library */


#ifdef __cplusplus
}
#endif

#endif /* __INCLUDED_USBHUAC_H__ */

/*** (C) COPYRIGHT 2015 Nuvoton Technology Corp. ***/

