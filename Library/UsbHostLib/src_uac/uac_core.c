/**************************************************************************//**
 * @file     uac_core.c
 * @version  V1.00
 * @brief    M480 MCU USB Host Audio Class driver
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "NuMicro.h"

#include "usb.h"
#include "usbh_lib.h"
#include "usbh_uac.h"
#include "uac.h"


/** @addtogroup LIBRARY Library
  @{
*/

/** @addtogroup USBH_Library USB Host Library
  @{
*/

/** @addtogroup USBH_EXPORTED_FUNCTIONS USB Host Exported Functions
  @{
*/


/**
 *  @brief  Obtain Audio Class device's channel number.
 *  @param[in]  uac    UAC device
 *  @param[in]  target Select the control target.
 *                     - \ref UAC_SPEAKER
 *                     - \ref UAC_MICROPHONE
 *  @return   Channel number or error code.
 *  @retval   < 0      Failed. UAC device may not present or function not supported.
 *  @retval   Otherwise  The channel number.
 */
int  usbh_uac_get_channel_number(UAC_DEV_T *uac, uint8_t target)
{
    AS_FT1_T   *ft;

    if (target == UAC_SPEAKER)
        ft = uac->asif_out.ft;
    else
        ft = uac->asif_in.ft;

    if (!ft)
        return UAC_RET_DEV_NOT_SUPPORTED;

    return ft->bNrChannels;
}


/**
 *  @brief  Obtain Audio Class device subframe bit resolution..
 *  @param[in]  uac    UAC device
 *  @param[in]  target Select the control target.
 *                     - \ref UAC_SPEAKER
 *                     - \ref UAC_MICROPHONE
 *  @param[out] byte_cnt  The number of bytes occupied by one audio subframe. Can be 1, 2, 3 or 4.
 *  @return   Bit resolution or error code.
 *  @retval   < 0        Failed. UAC device may not present or function not supported.
 *  @retval   Otherwise  The number of effectively used bits from the available bits in an audio subframe.
 */
int  usbh_uac_get_bit_resolution(UAC_DEV_T *uac, uint8_t target, uint8_t *byte_cnt)
{
    AS_FT1_T   *ft;

    if (target == UAC_SPEAKER)
        ft = uac->asif_out.ft;
    else
        ft = uac->asif_in.ft;

    if (!ft)
        return UAC_RET_DEV_NOT_SUPPORTED;

    *byte_cnt = ft->bSubframeSize;

    return ft->bBitResolution;
}


/// @cond HIDDEN_SYMBOLS

uint32_t  srate_to_u32(uint8_t *srate)
{
    return (srate[2] << 16) | (srate[1] << 8) | srate[0];
}

/// @endcond HIDDEN_SYMBOLS


/**
 *  @brief  Get a list of sampling rate frequencies supported by the UAC device.
 *  @param[in]  uac    UAC device
 *  @param[in]  target Select the control target.
 *                     - \ref UAC_SPEAKER
 *                     - \ref UAC_MICROPHONE
 *  @param[out] srate_list  A word array provided by user application to hold the sampling rate list.
 *  @param[in]  max_cnt  Available number of entries of srate_list[]. Must be > 2.
 *  @param[out] type   Indicates how the sampling frequency can be programmed.
 *                     0:  Continuous sampling frequency. srate_list[0] is the lower bound
 *                          in Hz of the sampling frequency and srate_list[1] is the upper bound.
 *                     1~255:  The number of discrete sampling frequencies supported. They are
 *                             listed in srate_list[].
 *  @return   Success or not.
 *  @retval   0        Success
 *  @retval   Otherwise  Failed
 */
int  usbh_uac_get_sampling_rate(UAC_DEV_T *uac, uint8_t target, uint32_t *srate_list,
                                int max_cnt, uint8_t *type)
{
    AS_FT1_T   *ft;
    int        i;

    if (target == UAC_SPEAKER)
        ft = uac->asif_out.ft;
    else
        ft = uac->asif_in.ft;

    if (!ft)
        return UAC_RET_DEV_NOT_SUPPORTED;

    *type = ft->bSamFreqType;

    if (*type == 0)
    {
        if (max_cnt < 2)
            return UAC_RET_OUT_OF_MEMORY;

        srate_list[0] = srate_to_u32(&ft->tSamFreq[0][0]);
        srate_list[1] = srate_to_u32(&ft->tSamFreq[1][0]);
    }
    else
    {
        for (i = 0; i < *type; i++)
            srate_list[i] = srate_to_u32(&ft->tSamFreq[i][0]);
    }
    return 0;
}


/**
 *  @brief  Set sampling rate frequency.
 *  @param[in]  uac    UAC device
 *  @param[in]  target Select the control target.
 *                     - \ref UAC_SPEAKER
 *                     - \ref UAC_MICROPHONE
 *  @param[in]  req    Control request. This UAC driver supports the following request:
 *                     - \ref UAC_SET_CUR
 *                     - \ref UAC_GET_CUR
 *                     - \ref UAC_SET_MIN
 *                     - \ref UAC_GET_MIN
 *                     - \ref UAC_SET_MAX
 *                     - \ref UAC_GET_MAX
 *                     - \ref UAC_SET_RES
 *                     - \ref UAC_GET_RES
 *  @param[in]  srate  Sampling rate frequency to be set or get.
 *  @return   Success or failed.
 *  @retval   0        Success
 *  @retval   Otherwise  Error occurred
 */
int  usbh_uac_sampling_rate_control(UAC_DEV_T *uac, uint8_t target, uint8_t req, uint32_t *srate)
{
    EP_INFO_T   *ep;
    uint8_t     bmRequestType;
    uint8_t     tSampleFreq[3];
    uint32_t    xfer_len;
    int         ret;

    if (target == UAC_SPEAKER)
        ep = uac->asif_out.ep;
    else
        ep = uac->asif_in.ep;

    if (ep == NULL)
        return UAC_RET_DEV_NOT_SUPPORTED;

    tSampleFreq[0] = *srate & 0xff;
    tSampleFreq[1] = (*srate >> 8) & 0xff;
    tSampleFreq[2] = (*srate >> 16) & 0xff;

    if (req & 0x80)
        bmRequestType = REQ_TYPE_IN | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_EP;
    else
        bmRequestType = REQ_TYPE_OUT | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_EP;

    /* Audio Class Request - Endpoint Control Requests (5.2.3.2) */
    ret = usbh_ctrl_xfer(uac->udev, bmRequestType, req,
                         (SAMPLING_FREQ_CONTROL << 8),  /* wValue - Control Selector (CS) */
                         ep->bEndpointAddress,         /* wIndex - endpoint              */
                         3,                            /* wLength - parameter block length */
                         tSampleFreq,                  /* parameter block                */
                         &xfer_len, UAC_REQ_TIMEOUT);
    if (ret < 0)
        return ret;

    if (xfer_len != 3)
        return UAC_RET_DATA_LEN;

    *srate = srate_to_u32(tSampleFreq);
    return 0;
}


/**
 *  @brief  Control Audio Class device mute on/off.
 *  @param[in]  uac    UAC device
 *  @param[in]  target Select the control target.
 *                     - \ref UAC_SPEAKER
 *                     - \ref UAC_MICROPHONE
 *  @param[in]  req    Control request. This UAC driver supports the following request:
 *                     - \ref UAC_SET_CUR
 *                     - \ref UAC_GET_CUR
 *  @param[in]  chn    The requested channel. It can be one of the followings:
 *                     - \ref UAC_CH_LEFT_FRONT
 *                     - \ref UAC_CH_RIGHT_FRONT
 *                     - \ref UAC_CH_CENTER_FRONT
 *                     - \ref UAC_CH_LOW_FREQ_EN
 *                     - \ref UAC_CH_LEFT_SRN
 *                     - \ref UAC_CH_RIGHT_SRN
 *                     - \ref UAC_CH_LEFT_OF_CENTER
 *                     - \ref UAC_CH_RIGHT_OF_CENTER
 *                     - \ref UAC_CH_SURROUND
 *                     - \ref UAC_CH_SIDE_LEFT
 *                     - \ref UAC_CH_SIDE_RIGHT
 *                     - \ref UAC_CH_TOP
 *  @param[in]  mute   One byte data. If the channel is muted, then the value is 1. Otherwise, it's 0.
 *  @return   Success or failed.
 *  @retval   0        Success
 *  @retval   UAC_RET_DEV_NOT_SUPPORTED  This UAC device does not support this function.
 *  @retval   Otherwise  Error occurred
 */
int usbh_uac_mute_control(UAC_DEV_T *uac, uint8_t target, uint8_t req, uint16_t chn, uint8_t *mute)
{
    uint8_t     bmRequestType;
    uint8_t     bUnitID;
    uint32_t    xfer_len;
    int         ret;

    if (target == UAC_MICROPHONE)
        bUnitID = uac->acif.mic_fuid;
    else
        bUnitID = uac->acif.speaker_fuid;

    if (req & 0x80)
        bmRequestType = REQ_TYPE_IN | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_IFACE;
    else
        bmRequestType = REQ_TYPE_OUT | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_IFACE;

    /* Audio Class Request - Feature Unit Control Request (5.2.2.4) */
    ret = usbh_ctrl_xfer(uac->udev, bmRequestType, req,
                         (MUTE_CONTROL << 8) | chn,  /* wValue - Control Selector (CS)    */
                         (bUnitID << 8) | (uac->acif.iface->if_num),  /* wIndex - unit ID and interface number */
                         1,                          /* wLength - parameter block length  */
                         mute,                       /* parameter block                   */
                         &xfer_len, UAC_REQ_TIMEOUT);
    if (ret < 0)
        return ret;

    if (xfer_len != 1)
        return UAC_RET_DATA_LEN;

    return 0;
}


/**
 *  @brief  Audio Class device volume control.
 *  @param[in]  uac    UAC device
 *  @param[in]  target Select the control target.
 *                     - \ref UAC_SPEAKER
 *                     - \ref UAC_MICROPHONE
 *  @param[in]  req    Control request. This UAC driver supports the following request:
 *                     - \ref UAC_SET_CUR
 *                     - \ref UAC_GET_CUR
 *                     - \ref UAC_SET_MIN
 *                     - \ref UAC_GET_MIN
 *                     - \ref UAC_SET_MAX
 *                     - \ref UAC_GET_MAX
 *                     - \ref UAC_SET_RES
 *                     - \ref UAC_GET_RES
 *                     - \ref UAC_GET_STAT
 *  @param[in]  chn    The requested channel. It can be one of the followings:
 *                     - \ref UAC_CH_LEFT_FRONT
 *                     - \ref UAC_CH_RIGHT_FRONT
 *                     - \ref UAC_CH_CENTER_FRONT
 *                     - \ref UAC_CH_LOW_FREQ_EN
 *                     - \ref UAC_CH_LEFT_SRN
 *                     - \ref UAC_CH_RIGHT_SRN
 *                     - \ref UAC_CH_LEFT_OF_CENTER
 *                     - \ref UAC_CH_RIGHT_OF_CENTER
 *                     - \ref UAC_CH_SURROUND
 *                     - \ref UAC_CH_SIDE_LEFT
 *                     - \ref UAC_CH_SIDE_RIGHT
 *                     - \ref UAC_CH_TOP
 *  @param[in]  volume   Audio Class device volume value, which is interpreted as the following:
 *                       0x7FFF:    127.9961 dB
 *                       . . .
 *                       0x0100:      1.0000 dB
 *                       . . .
 *                       0x0002:      0.0078 dB
 *                       0x0001:      0.0039 dB
 *                       0x0000:      0.0000 dB
 *                       0xFFFF:     -0.0039 dB
 *                       0xFFFE:     -0.0078 dB
 *                       . . .
 *                       0xFE00:     -1.0000 dB
 *                       . . .
 *                       0x8002:   -127.9922 dB
 *                       0x8001:   -127.9961 dB
 *  @return   Success or failed.
 *  @retval   0        Success
 *  @retval   UAC_RET_DEV_NOT_SUPPORTED  This UAC device does not support this function.
 *  @retval   Otherwise  Error occurred
 */
int usbh_uac_vol_control(UAC_DEV_T *uac, uint8_t target, uint8_t req, uint16_t chn, uint16_t *volume)
{
    uint8_t     bmRequestType;
    uint8_t     bUnitID;
    uint32_t    xfer_len;
    int         ret;

    if (target == UAC_MICROPHONE)
        bUnitID = uac->acif.mic_fuid;
    else
        bUnitID = uac->acif.speaker_fuid;

    if (req & 0x80)
        bmRequestType = REQ_TYPE_IN | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_IFACE;
    else
        bmRequestType = REQ_TYPE_OUT | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_IFACE;

    /* Audio Class Request - Feature Unit Control Request (5.2.2.4) */
    ret = usbh_ctrl_xfer(uac->udev, bmRequestType, req,
                         (VOLUME_CONTROL << 8) | chn,/* wValue - Control Selector (CS)    */
                         (bUnitID << 8) | (uac->acif.iface->if_num),  /* wIndex - unit ID and interface number */
                         2,                          /* wLength - parameter block length  */
                         (uint8_t *)volume,          /* parameter block                   */
                         &xfer_len, UAC_REQ_TIMEOUT);
    if (ret < 0)
        return ret;

    if (xfer_len != 2)
        return UAC_RET_DATA_LEN;

    return 0;
}


/**
 *  @brief  Audio Class device automatic gain control.
 *  @param[in]  uac  UAC device
 *  @param[in]  target Select the control target.
 *                     - \ref UAC_SPEAKER
 *                     - \ref UAC_MICROPHONE
 *  @param[in]  req    Control request. This UAC driver supports the following request:
 *                     - \ref UAC_SET_CUR
 *                     - \ref UAC_GET_CUR
 *  @param[in]  chn    The requested channel. It can be one of the followings:
 *                     - \ref UAC_CH_LEFT_FRONT
 *                     - \ref UAC_CH_RIGHT_FRONT
 *                     - \ref UAC_CH_CENTER_FRONT
 *                     - \ref UAC_CH_LOW_FREQ_EN
 *                     - \ref UAC_CH_LEFT_SRN
 *                     - \ref UAC_CH_RIGHT_SRN
 *                     - \ref UAC_CH_LEFT_OF_CENTER
 *                     - \ref UAC_CH_RIGHT_OF_CENTER
 *                     - \ref UAC_CH_SURROUND
 *                     - \ref UAC_CH_SIDE_LEFT
 *                     - \ref UAC_CH_SIDE_RIGHT
 *                     - \ref UAC_CH_TOP
 *  @param[in]  bAGC   One byte data. If the channel's automatic gain control is on, then the value is 1. Otherwise, it's 0.
 *  @return   Success or failed.
 *  @retval   0        Success
 *  @retval   UAC_RET_DEV_NOT_SUPPORTED  This UAC device does not support this function.
 *  @retval   Otherwise  Error occurred
 */
int  usbh_uac_auto_gain_control(UAC_DEV_T *uac, uint8_t target, uint8_t req, uint16_t chn, uint8_t *bAGC)
{
    uint8_t     bmRequestType;
    uint8_t     bUnitID;
    uint32_t    xfer_len;
    int         ret;

    if (target == UAC_MICROPHONE)
        bUnitID = uac->acif.mic_fuid;
    else
        bUnitID = uac->acif.speaker_fuid;

    if (req & 0x80)
        bmRequestType = REQ_TYPE_IN | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_IFACE;
    else
        bmRequestType = REQ_TYPE_OUT | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_IFACE;

    /* Audio Class Request - Feature Unit Control Request (5.2.2.4) */
    ret = usbh_ctrl_xfer(uac->udev, bmRequestType, req,
                         (AUTOMATIC_GAIN_CONTROL << 8) | chn,  /* wValue - Control Selector (CS)    */
                         (bUnitID << 8) | (uac->acif.iface->if_num),  /* wIndex - unit ID and interface number */
                         1,                          /* wLength - parameter block length  */
                         bAGC,                       /* parameter block                   */
                         &xfer_len, UAC_REQ_TIMEOUT);
    if (ret < 0)
        return ret;

    if (xfer_len != 1)
        return UAC_RET_DATA_LEN;

    return 0;
}


/// @cond HIDDEN_SYMBOLS

/**
 *  @brief    Find the alternative interface whose endpoint has the maximum packet size.
 *  @param[in]  ifcae     USB device interface
 *  @param[in]  dir       Endpoint bEndpointAddress[7] direction
 *  @param[in]  attr      Endpoint bmAttributes[1:0] transfer type
 *  @param[out] bAlternateSetting   The alternative interface number if found.
 *  @return   Success or not.
 *  @retval     0         Success.
 *  @retval    Otherwise  Failed
 */
int  usbh_uac_find_max_alt(IFACE_T *iface, uint8_t dir, uint8_t attr, uint8_t *bAlternateSetting)
{
    EP_INFO_T    *ep;
    uint8_t      i,  j;
    uint16_t     wMaxPacketSize = 0;

    for (i = 0; i < iface->num_alt; i++)
    {
        for (j = 0; j < iface->alt[i].ifd->bNumEndpoints; j++)
        {
            ep = &(iface->alt[i].ep[j]);    /* get endpoint                                */

            if (((ep->bEndpointAddress & EP_ADDR_DIR_MASK) != dir) ||
                    ((ep->bmAttributes & EP_ATTR_TT_MASK) != attr))
                continue;                   /* not interested endpoint                    */

            if (ep->wMaxPacketSize > wMaxPacketSize)
            {
                /* a better candidate endpoint found          */
                *bAlternateSetting = i;
                wMaxPacketSize = ep->wMaxPacketSize;
            }
        }
    }
    if (wMaxPacketSize == 0)
        return USBH_ERR_NOT_FOUND;

    return 0;
}

/**
 *  @brief    Find the alternative interface whose endpoint is the best choice.
 *  @param[in]  ifcae     USB device interface
 *  @param[in]  dir       Endpoint bEndpointAddress[7] direction
 *  @param[in]  attr      Endpoint bmAttributes[1:0] transfer type
 *  @param[in]  pkt_sz    Find the endpoint whose wMaxPacketSize is larger than <pkt_sz> and is most cross to <pkt_sz>.
 *  @param[out] bAlternateSetting   The alternative interface number if found.
 *  @return   Success or not.
 *  @retval     0         Success.
 *  @retval    Otherwise  Failed
 */
int  usbh_uac_find_best_alt(IFACE_T *iface, uint8_t dir, uint8_t attr, int pkt_sz, uint8_t *bAlternateSetting)
{
    EP_INFO_T    *ep;
    uint8_t      i,  j;
    uint16_t     wMaxPacketSize = 0xFFFF;

    for (i = 0; i < iface->num_alt; i++)
    {
        for (j = 0; j < iface->alt[i].ifd->bNumEndpoints; j++)
        {
            ep = &(iface->alt[i].ep[j]);    /* get endpoint                                */

            if (((ep->bEndpointAddress & EP_ADDR_DIR_MASK) != dir) ||
                    ((ep->bmAttributes & EP_ATTR_TT_MASK) != attr))
                continue;                   /* not interested endpoint                    */

            if ((ep->wMaxPacketSize >= pkt_sz) && (ep->wMaxPacketSize < wMaxPacketSize))
            {
                /* a better candidate endpoint found          */
                *bAlternateSetting = i;
                wMaxPacketSize = ep->wMaxPacketSize;
            }
        }
    }
    if (wMaxPacketSize == 0xFFFF)
    {
        UAC_DBGMSG("Audio interface %d cannot find endpoint with wMaxPacketSize >= %d!\n", iface->if_num, pkt_sz);
        return USBH_ERR_NOT_FOUND;
    }
    return 0;
}


static void iso_in_irq(UTR_T *utr)
{
    UAC_DEV_T   *uac = (UAC_DEV_T *)utr->context;
    int         i, ret;

    /* We don't want to do anything if we are about to be removed! */
    if (!uac || !uac->udev)
        return;

    if (uac->asif_in.flag_streaming == 0)
        return;

    //UAC_DBGMSG("SF=%d, 0x%x\n", utr->iso_sf, (int)utr);

    utr->bIsoNewSched = 0;

    for (i = 0; i < IF_PER_UTR; i++)
    {
        if (utr->iso_status[i] == 0)
        {
            if ((uac->func_au_in != NULL) && (utr->iso_xlen[i] > 0))
                uac->func_au_in(uac, utr->iso_buff[i], utr->iso_xlen[i]);
        }
        else
        {
            UAC_DBGMSG("Iso %d err - %d\n", i, utr->iso_status[i]);
            if ((utr->iso_status[i] == USBH_ERR_NOT_ACCESS0) || (utr->iso_status[i] == USBH_ERR_NOT_ACCESS1))
                utr->bIsoNewSched = 1;
        }
        utr->iso_xlen[i] = utr->ep->wMaxPacketSize;
    }

    /* schedule the following isochronous transfers */
    ret = usbh_iso_xfer(utr);
    if (ret < 0)
        UAC_DBGMSG("usbh_iso_xfer failed!\n");
}

/// @endcond HIDDEN_SYMBOLS


/**
 *  @brief  Start to receive audio data from UAC device. (Microphone)
 *  @param[in] uac        Audio Class device
 *  @param[in] func       Audio in callback function.
 *  @return   Success or not.
 *  @retval    0          Success
 *  @retval    Otherwise  Failed
 */
int usbh_uac_start_audio_in(UAC_DEV_T *uac, UAC_CB_FUNC *func)
{
    UDEV_T       *udev = uac->udev;
    AS_IF_T      *asif = &uac->asif_in;
    IFACE_T      *iface = uac->asif_in.iface;
    ALT_IFACE_T  *aif;
    EP_INFO_T    *ep;
    UTR_T        *utr;
    uint8_t      *buff;
    uint8_t      bAlternateSetting;
    int          i, j, ret;

    if (!uac || !iface)
        return UAC_RET_DEV_NOT_FOUND;

    if (asif->flag_streaming)
        return UAC_RET_IS_STREAMING;

    /*------------------------------------------------------------------------------------*/
    /*  Select the maximum packet size alternative interface                              */
    /*------------------------------------------------------------------------------------*/
    if (usbh_uac_find_max_alt(iface, EP_ADDR_DIR_IN, EP_ATTR_TT_ISO, &bAlternateSetting) != 0)
        return UAC_RET_FUNC_NOT_FOUND;

    uac->func_au_in = func;

    ret = usbh_set_interface(iface, bAlternateSetting);
    if (ret < 0)
    {
        UAC_ERRMSG("Failed to set interface %d, %d! (%d)\n", iface->if_num, bAlternateSetting, ret);
        return ret;
    }

    ret = uac_parse_streaming_interface(uac, iface, bAlternateSetting);
    if (ret < 0)
        return ret;

    /*------------------------------------------------------------------------------------*/
    /*  Find the endpoint                                                                 */
    /*------------------------------------------------------------------------------------*/
    asif->ep = NULL;
    aif = asif->iface->aif;
    for (i = 0; i < aif->ifd->bNumEndpoints; i++)
    {
        ep = &(aif->ep[i]);

        if (((ep->bEndpointAddress & EP_ADDR_DIR_MASK) == EP_ADDR_DIR_IN) &&
                ((ep->bmAttributes & EP_ATTR_TT_MASK) == EP_ATTR_TT_ISO))
        {
            asif->ep = ep;
            UAC_DBGMSG("Audio in endpoint 0x%x found, size: %d\n", ep->bEndpointAddress, ep->wMaxPacketSize);
            break;
        }
    }
    if (asif->ep == NULL)
        return UAC_RET_FUNC_NOT_FOUND;
    ep = asif->ep;

#ifdef UAC_DEBUG
    UAC_DBGMSG("Activated isochronous-in endpoint =>");
    usbh_dump_ep_info(ep);
#endif

    /*------------------------------------------------------------------------------------*/
    /*  Allocate isochronous in buffer                                                    */
    /*------------------------------------------------------------------------------------*/
    for (i = 0; i < NUM_UTR; i++)           /* allocate UTRs                              */
    {
        asif->utr[i] = alloc_utr(udev);     /* allocate UTR                               */
        if (asif->utr[i] == NULL)
        {
            ret = USBH_ERR_MEMORY_OUT;      /* memory allocate failed                     */
            goto err_out;                   /* abort                                      */
        }
    }

    buff = (uint8_t *)usbh_alloc_mem(ep->wMaxPacketSize * IF_PER_UTR * NUM_UTR);
    if (buff == NULL)
    {
        ret = USBH_ERR_MEMORY_OUT;          /* memory allocate failed                     */
        goto err_out;                       /* abort                                      */
    }

    for (i = 0; i < NUM_UTR; i++)           /* dispatch buffers                           */
    {
        /* divide buffer equally                      */
        utr = asif->utr[i];
        utr->buff = buff + (ep->wMaxPacketSize * IF_PER_UTR * i);
        utr->data_len = ep->wMaxPacketSize * IF_PER_UTR;
        for (j = 0; j < IF_PER_UTR; j++)
        {
            utr->iso_xlen[j] = ep->wMaxPacketSize;
            utr->iso_buff[j] = utr->buff + (ep->wMaxPacketSize * j);
        }
    }

    /*------------------------------------------------------------------------------------*/
    /*  Start UTRs                                                                        */
    /*------------------------------------------------------------------------------------*/

    asif->utr[0]->bIsoNewSched = 1;

    for (i = 0; i < NUM_UTR; i++)
    {
        utr = asif->utr[i];
        utr->context = uac;
        utr->ep = ep;
        utr->func = iso_in_irq;
        ret = usbh_iso_xfer(utr);
        if (ret < 0)
        {
            UAC_DBGMSG("Error - failed to start UTR %d isochronous-in transfer (%d)", i, ret);
            goto err_out;
        }
    }
    asif->flag_streaming = 1;
    uac->state = UAC_STATE_RUNNING;

    return UAC_RET_OK;

err_out:

    for (i = 0; i < NUM_UTR; i++)           /* quit all UTRs                              */
    {
        if (asif->utr[i])
            usbh_quit_utr(asif->utr[i]);
    }
    asif->flag_streaming = 0;
    /* free USB transfer buffer                   */
    if ((asif->utr[0] != NULL) &&
            (asif->utr[0]->buff != NULL))
        usbh_free_mem(asif->utr[0]->buff, asif->utr[0]->data_len * NUM_UTR);

    for (i = 0; i < NUM_UTR; i++)           /* free all UTRs                              */
    {
        if (asif->utr[i])
            free_utr(asif->utr[i]);
        asif->utr[i] = NULL;
    }
    return ret;
}

/**
 *  @brief  Stop UAC device audio in data stream.
 *  @param[in] uac      Audio Class device
 *  @return   Success or not.
 *  @retval    0          Success
 *  @retval    Otherwise  Failed
 */
int usbh_uac_stop_audio_in(UAC_DEV_T *uac)
{
    AS_IF_T      *asif = &uac->asif_in;
    int          i, ret;

    asif->flag_streaming = 0;

    /* Set interface alternative settings */
    if (uac->state != UAC_STATE_DISCONNECTING)
    {
        ret = usbh_set_interface(asif->iface, 0);
        if (ret < 0)
        {
            UAC_ERRMSG("Failed to set interface %d, %d! (%d)\n", asif->iface->if_num, 0, ret);
        }
    }

    for (i = 0; i < NUM_UTR; i++)           /* stop all UTRs                              */
    {
        if (asif->utr[i])
            usbh_quit_utr(asif->utr[i]);
    }

    if ((asif->utr[0] != NULL) &&
            (asif->utr[0]->buff != NULL))       /* free audio buffer                          */
        usbh_free_mem(asif->utr[0]->buff, asif->utr[0]->data_len * NUM_UTR);

    for (i = 0; i < NUM_UTR; i++)           /* free all UTRs                              */
    {
        if (asif->utr[i])
            free_utr(asif->utr[i]);
        asif->utr[i] = NULL;
    }

    if (uac->state != UAC_STATE_DISCONNECTING)
    {
        if ((uac->asif_out.iface == NULL) || (uac->asif_out.flag_streaming == 0))
        {
            uac->state = UAC_STATE_READY;
        }
    }

    return UAC_RET_OK;
}


/// @cond HIDDEN_SYMBOLS

static void iso_out_irq(UTR_T *utr)
{
    UAC_DEV_T   *uac = (UAC_DEV_T *)utr->context;
    int         i, ret;

    /* We don't want to do anything if we are about to be removed! */
    if (!uac || !uac->udev)
        return;

    if (uac->asif_out.flag_streaming == 0)
        return;

    //UAC_DBGMSG("SF=%d, 0x%x\n", utr->iso_sf, (int)utr);

    utr->bIsoNewSched = 0;

    for (i = 0; i < IF_PER_UTR; i++)
    {
        if (utr->iso_status[i] != 0)
        {
            // UAC_DBGMSG("Iso %d err - %d\n", i, utr->iso_status[i]);
            if ((utr->iso_status[i] == USBH_ERR_NOT_ACCESS0) || (utr->iso_status[i] == USBH_ERR_NOT_ACCESS1))
                utr->bIsoNewSched = 1;
        }
        utr->iso_xlen[i] = uac->func_au_out(uac, utr->iso_buff[i], utr->ep->wMaxPacketSize);
    }

    /* schedule the following isochronous transfers */
    ret = usbh_iso_xfer(utr);
    if (ret < 0)
        UAC_DBGMSG("usbh_iso_xfer failed!\n");
}

/// @endcond HIDDEN_SYMBOLS


/**
 *  @brief  Start to transmit audio data to UAC device. (Speaker)
 *  @param[in] uac      Audio Class device
 *  @param[in] func     Audio out call-back function. UAC driver call this function to get audio
 *                      out stream data from user application.
 *  @return   Success or not.
 *  @retval    0          Success
 *  @retval    Otherwise  Failed
 */
int usbh_uac_start_audio_out(UAC_DEV_T *uac, UAC_CB_FUNC *func)
{
    UDEV_T       *udev = uac->udev;
    AS_IF_T      *asif = &uac->asif_out;
    IFACE_T      *iface = uac->asif_out.iface;
    ALT_IFACE_T  *aif;
    EP_INFO_T    *ep;
    UTR_T        *utr;
    uint8_t      *buff;
    uint8_t      bAlternateSetting;
    int          i, j, ret;

    if (!uac || !func || !iface)
        return UAC_RET_DEV_NOT_FOUND;

    if (asif->flag_streaming)
        return UAC_RET_IS_STREAMING;

    /*------------------------------------------------------------------------------------*/
    /*  Select the maximum packet size alternative interface                              */
    /*------------------------------------------------------------------------------------*/
    if (usbh_uac_find_max_alt(iface, EP_ADDR_DIR_OUT, EP_ATTR_TT_ISO, &bAlternateSetting) != 0)
        return UAC_RET_FUNC_NOT_FOUND;

    uac->func_au_out = func;

    ret = usbh_set_interface(iface, bAlternateSetting);
    if (ret < 0)
    {
        UAC_ERRMSG("Failed to set interface %d, %d! (%d)\n", iface->if_num, bAlternateSetting, ret);
        return ret;
    }

    ret = uac_parse_streaming_interface(uac, iface, bAlternateSetting);
    if (ret < 0)
        return ret;

    /*------------------------------------------------------------------------------------*/
    /*  Find the endpoint                                                                 */
    /*------------------------------------------------------------------------------------*/
    asif->ep = NULL;
    aif = asif->iface->aif;
    for (i = 0; i < aif->ifd->bNumEndpoints; i++)
    {
        ep = &(aif->ep[i]);

        if (((ep->bEndpointAddress & EP_ADDR_DIR_MASK) == EP_ADDR_DIR_OUT) &&
                ((ep->bmAttributes & EP_ATTR_TT_MASK) == EP_ATTR_TT_ISO))
        {
            asif->ep = ep;
            UAC_DBGMSG("Audio in endpoint 0x%x found, size: %d\n", ep->bEndpointAddress, ep->wMaxPacketSize);
            break;
        }
    }
    if (asif->ep == NULL)
        return UAC_RET_FUNC_NOT_FOUND;
    ep = asif->ep;

#ifdef UAC_DEBUG
    UAC_DBGMSG("Activated isochronous-out endpoint =>");
    usbh_dump_ep_info(ep);
#endif

    /*------------------------------------------------------------------------------------*/
    /*  Allocate isochronous in buffer                                                    */
    /*------------------------------------------------------------------------------------*/
    for (i = 0; i < NUM_UTR; i++)           /* allocate UTRs                              */
    {
        asif->utr[i] = alloc_utr(udev);     /* allocate UTR                               */
        if (asif->utr[i] == NULL)
        {
            ret = USBH_ERR_MEMORY_OUT;      /* memory allocate failed                     */
            goto err_out;                   /* abort                                      */
        }
    }

    buff = (uint8_t *)usbh_alloc_mem(ep->wMaxPacketSize * IF_PER_UTR * NUM_UTR);
    if (buff == NULL)
    {
        ret = USBH_ERR_MEMORY_OUT;          /* memory allocate failed                     */
        goto err_out;                       /* abort                                      */
    }

    for (i = 0; i < NUM_UTR; i++)           /* dispatch buffers                           */
    {
        /* divide buffer equally                      */
        asif->utr[i]->buff = buff + (ep->wMaxPacketSize * IF_PER_UTR * i);
        asif->utr[i]->data_len = ep->wMaxPacketSize * IF_PER_UTR;
    }

    /*------------------------------------------------------------------------------------*/
    /*  Start UTRs                                                                        */
    /*------------------------------------------------------------------------------------*/

    asif->utr[0]->bIsoNewSched = 1;

    for (i = 0; i < NUM_UTR; i++)
    {
        utr = asif->utr[i];
        utr->context = uac;
        utr->ep = ep;
        utr->func = iso_out_irq;

        for (j = 0; j < IF_PER_UTR; j++)    /* get audio out data from user               */
        {
            utr->iso_buff[j] = utr->buff + (ep->wMaxPacketSize * j);
            utr->iso_xlen[j] = uac->func_au_out(uac, utr->iso_buff[j], ep->wMaxPacketSize);
        }

        ret = usbh_iso_xfer(utr);
        if (ret < 0)
        {
            UAC_DBGMSG("Error - failed to start UTR %d isochronous-in transfer (%d)", i, ret);
            goto err_out;
        }
    }
    asif->flag_streaming = 1;
    uac->state = UAC_STATE_RUNNING;

    return UAC_RET_OK;

err_out:

    for (i = 0; i < NUM_UTR; i++)           /* quit all UTRs                              */
    {
        if (asif->utr[i])
            usbh_quit_utr(asif->utr[i]);
    }
    asif->flag_streaming = 0;

    if ((asif->utr[0] != NULL) &&           /* free USB transfer buffer                   */
            (asif->utr[0]->buff != NULL))
        usbh_free_mem(asif->utr[0]->buff, asif->utr[0]->data_len * NUM_UTR);

    for (i = 0; i < NUM_UTR; i++)           /* free all UTRs                              */
    {
        if (asif->utr[i])
            free_utr(asif->utr[i]);
        asif->utr[i] = NULL;
    }
    return ret;
}

/**
 *  @brief  Stop UAC device audio out data stream.
 *  @param[in] uac      Audio Class device
 *  @return   Success or not.
 *  @retval    0          Success
 *  @retval    Otherwise  Failed
 */
int usbh_uac_stop_audio_out(UAC_DEV_T *uac)
{
    AS_IF_T      *asif = &uac->asif_out;
    int          i, ret;

    /* Set interface alternative settings */
    if (uac->state != UAC_STATE_DISCONNECTING)
    {
        ret = usbh_set_interface(asif->iface, 0);
        if (ret < 0)
        {
            UAC_ERRMSG("Failed to set interface %d, %d! (%d)\n", asif->iface->if_num, 0, ret);
        }
    }

    for (i = 0; i < NUM_UTR; i++)           /* stop all UTRs                              */
    {
        if (asif->utr[i])
            usbh_quit_utr(asif->utr[i]);
    }

    if ((asif->utr[0] != NULL) &&
            (asif->utr[0]->buff != NULL))       /* free audio buffer                          */
        usbh_free_mem(asif->utr[0]->buff, asif->utr[0]->data_len * NUM_UTR);

    for (i = 0; i < NUM_UTR; i++)           /* free all UTRs                              */
    {
        if (asif->utr[i])
            free_utr(asif->utr[i]);
        asif->utr[i] = NULL;
    }

    if (uac->state != UAC_STATE_DISCONNECTING)
    {
        if ((uac->asif_in.iface == NULL) || (uac->asif_in.flag_streaming == 0))
        {
            uac->state = UAC_STATE_READY;
        }
    }
    asif->flag_streaming = 0;

    return UAC_RET_OK;
}

/**
 *  @brief   Open an connected UAC device.
 *  @param[in] uac        Audio Class device
 *  @return   Success or not.
 *  @retval    0          Success
 *  @retval    Otherwise  Failed
 */
int usbh_uac_open(UAC_DEV_T *uac)
{
    IFACE_T      *iface;
    uint8_t      bAlternateSetting;
    int          ret;

    /*------------------------------------------------------------------------------------*/
    /*  Select the maximum packet size alternative interface                              */
    /*------------------------------------------------------------------------------------*/
    iface = uac->asif_in.iface;

    if (iface != NULL)
    {
        if (usbh_uac_find_max_alt(iface, EP_ADDR_DIR_IN, EP_ATTR_TT_ISO, &bAlternateSetting) != 0)
            return UAC_RET_FUNC_NOT_FOUND;

        ret = usbh_set_interface(iface, bAlternateSetting);
        if (ret < 0)
        {
            UAC_ERRMSG("Failed to set interface %d, %d! (%d)\n", iface->if_num, bAlternateSetting, ret);
            return ret;
        }
    }

    /*------------------------------------------------------------------------------------*/
    /*  Select the maximum packet size alternative interface                              */
    /*------------------------------------------------------------------------------------*/
    iface = uac->asif_out.iface;

    if (iface != NULL)
    {
        if (usbh_uac_find_max_alt(iface, EP_ADDR_DIR_OUT, EP_ATTR_TT_ISO, &bAlternateSetting) != 0)
            return UAC_RET_FUNC_NOT_FOUND;

        ret = usbh_set_interface(iface, bAlternateSetting);
        if (ret < 0)
        {
            UAC_ERRMSG("Failed to set interface %d, %d! (%d)\n", iface->if_num, bAlternateSetting, ret);
            return ret;
        }
    }
    return 0;
}

/*@}*/ /* end of group USBH_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group USBH_Library */

/*@}*/ /* end of group LIBRARY */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/

