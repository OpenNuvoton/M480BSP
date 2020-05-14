/**************************************************************************//**
 * @file     usbh_uac.h
 * @version  V1.10
 * @brief    USB Host UAC class driver header file.
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef  _USBH_UAC_H_
#define  _USBH_UAC_H_

#include "NuMicro.h"

#include "usb.h"
#include "usbh_lib.h"
#include "../src_uac/uac.h"

/** @addtogroup LIBRARY Library
  @{
*/

/** @addtogroup USBH_Library USB Host Library
  @{
*/

/** @addtogroup USBH_EXPORTED_CONSTANTS USB Host Exported Constants
  @{
*/


#define CONFIG_UAC_MAX_DEV           3      /*!< Maximum number of Audio Class device.                     */
#define NUM_UTR                      2      /*!< Number of UTR used for audio in/out transfer.             */
#define UAC_REQ_TIMEOUT              50     /*!< UAC control request timeout value in tick (10ms unit)     */

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
#define UAC_CH_MASTER                0      /*!< Select all channels.                 \hideinitializer */
#define UAC_CH_LEFT_FRONT            1      /*!< Select Left Front (L) channel.       \hideinitializer */
#define UAC_CH_RIGHT_FRONT           2      /*!< Select Right Front (R) channel.      \hideinitializer */
#define UAC_CH_CENTER_FRONT          3      /*!< Select Center Front (C) channel.     \hideinitializer */
#define UAC_CH_LOW_FREQ_EN           4      /*!< Select Low Frequency Enhancement. (LFE) channel \hideinitializer */
#define UAC_CH_LEFT_SRN              5      /*!< Select Left Surround (LS) channel.   \hideinitializer */
#define UAC_CH_RIGHT_SRN             6      /*!< Select Right Surround (RS) channel.  \hideinitializer */
#define UAC_CH_LEFT_OF_CENTER        7      /*!< Select Left of Center (LC) channel.  \hideinitializer */
#define UAC_CH_RIGHT_OF_CENTER       8      /*!< Select Right of Center (RC) channel. \hideinitializer */
#define UAC_CH_SURROUND              9      /*!< Select Surround (S) channel.         \hideinitializer */
#define UAC_CH_SIDE_LEFT             10     /*!< Select Side Left (SL) channel.       \hideinitializer */
#define UAC_CH_SIDE_RIGHT            11     /*!< Select Side Right (SR) channel.      \hideinitializer */
#define UAC_CH_TOP                   12     /*!< Select Top (T) channel.              \hideinitializer */

/*@}*/ /* end of group USBH_EXPORTED_CONSTANTS */



/** @addtogroup USBH_EXPORTED_STRUCTURES USB Host Exported Structures
  @{
*/


/*----------------------------------------------------------------------------------------*/
/*  Audio Control Interface                                                               */
/*----------------------------------------------------------------------------------------*/
typedef struct ac_if_t
{
    IFACE_T        *iface;                  /*!< USB interface                            */
    uint8_t        mic_id;                  /*!< Microphone Input Terminal ID             */
    uint8_t        mic_fuid;                /*!< Microphone Feature Unit ID               */
    uint8_t        speaker_id;              /*!< Speaker terminal ID                      */
    uint8_t        speaker_fuid;            /*!< Speaker Feature Unit ID                  */
}  AC_IF_T;

/*----------------------------------------------------------------------------------------*/
/*  Audio Streaming Interface                                                             */
/*----------------------------------------------------------------------------------------*/
typedef struct as_if_t
{
    IFACE_T        *iface;                  /*!< USB interface                            */
    EP_INFO_T      *ep;                     /*!< Currently selected streaming endpoint    */
    UTR_T          *utr[NUM_UTR];           /*!< ping-pong transfer requests              */
    AS_GEN_T       *as_gen;                 /*!< Point to the Class-Specific AS Interface Descriptor of this interface */
    AC_IT_T        *it;                     /*!< Point to the Input Terminal connected with USB OUT endpoint */
    AC_OT_T        *ot;                     /*!< Point to the Output Terminal connected with USB IN endpoint */
    AS_FT1_T       *ft;                     /*!< Point to Format type descriptor, support Type-I only */
    CS_EP_T        *cs_epd;                 /*!< Point to AS Isochronous Audio Data Endpoint Descriptor */
    uint8_t        flag_streaming;          /*!< audio is streaming or not                */
}  AS_IF_T;


/*----------------------------------------------------------------------------------------*/
/*  Audio Class device                                                                    */
/*----------------------------------------------------------------------------------------*/
typedef struct uac_dev_t
{
    UDEV_T         *udev;                   /*!< pointer to this UAC device               */
    AC_IF_T        acif;                    /*!< audio control interface                  */
    AS_IF_T        asif_in;                 /*!< audio streaming in interface             */
    AS_IF_T        asif_out;                /*!< audio streaming out interface            */
    UAC_CB_FUNC    *func_au_in;             /*!< audio in callback function               */
    UAC_CB_FUNC    *func_au_out;            /*!< audio out callback function              */
    uint32_t       uid;                     /*!< The unique ID to identify an UAC device. */
    UAC_STATE_E    state;
    struct uac_dev_t    *next;              /*!< point to the UAC device                  */
} UAC_DEV_T;                                /*! audio class device structure              */


/*@}*/ /* end of group USBH_EXPORTED_STRUCTURES */


/// @cond HIDDEN_SYMBOLS

extern int uac_parse_control_interface(UAC_DEV_T *uac, IFACE_T *iface);
extern int uac_parse_streaming_interface(UAC_DEV_T *uac, IFACE_T *iface, uint8_t bAlternateSetting);
extern int usbh_uac_find_best_alt(IFACE_T *iface, uint8_t dir, uint8_t attr, int pkt_sz, uint8_t *bAlternateSetting);
extern int usbh_uac_find_max_alt(IFACE_T *iface, uint8_t dir, uint8_t attr, uint8_t *bAlternateSetting);

/// @endcond HIDDEN_SYMBOLS


#ifdef __cplusplus
extern "C" {
#endif

/*@}*/ /* end of group USBH_Library */

/*@}*/ /* end of group LIBRARY */


#ifdef __cplusplus
}
#endif

#endif /* _USBH_UAC_H_ */


/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/

