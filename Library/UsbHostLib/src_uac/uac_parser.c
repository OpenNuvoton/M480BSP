/**************************************************************************//**
 * @file     uac_parser.c
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

/// @cond HIDDEN_SYMBOLS

static int  uac_parse_ac_interface(UAC_DEV_T *uac, uint8_t *bptr)
{
    AC_IT_T     *ac_itd;
    AC_OT_T     *ac_otd;

    UAC_DBGMSG("Parse AC - [%d] [0x%x] [0x%x]\n", ((CS_HDR_T *)bptr)->bLength, ((CS_HDR_T *)bptr)->bDescriptorType, ((CS_HDR_T *)bptr)->bDescriptorSubtype);

    switch (((CS_HDR_T *)bptr)->bDescriptorSubtype)
    {
    case AC_DESCRIPTOR_UNDEFINED:       /* Not interested, discard it...              */
        UAC_DBGMSG("AC: AC_DESCRIPTOR_UNDEFINED\n");
        break;

    case HEADER:
        /* Not interested, discard it...              */
        UAC_DBGMSG("AC: HEADER\n");
        break;

    case INPUT_TERMINAL:
        ac_itd = (AC_IT_T *)bptr;
        UAC_DBGMSG("AC: INPUT_TERMINAL\n");
        if (ac_itd->wTerminalType == UAC_TT_USB_STREAMING)
        {
            UAC_DBGMSG("USB streaming terminal found, ID=0x%x\n", ac_itd->bTerminalID);
        }
        else if ((ac_itd->wTerminalType & 0x200) == 0x200)
        {
            UAC_DBGMSG("MICROPHONE input terminal found, ID=0x%x\n", ac_itd->bTerminalID);
            uac->acif.mic_id = ac_itd->bTerminalID;
        }
        else
        {
            UAC_DBGMSG("Unsupported INPUT TERMINAL, ignore it!\n");
        }
        UAC_DBGMSG("      bTerminalID: 0%x\n", ac_itd->bTerminalID);
        UAC_DBGMSG("      wTerminalType: 0%x\n", ac_itd->wTerminalType);
        UAC_DBGMSG("      bAssocTerminal: 0%x\n", ac_itd->bAssocTerminal);
        UAC_DBGMSG("      bNrChannels: 0%x\n", ac_itd->bNrChannels);
        UAC_DBGMSG("      wChannelConfig: 0%x\n", ac_itd->wChannelConfig);
        break;

    case OUTPUT_TERMINAL:
        ac_otd = (AC_OT_T *)bptr;
        UAC_DBGMSG("AC: OUTPUT_TERMINAL\n");
        if (ac_otd->wTerminalType == UAC_TT_USB_STREAMING)
        {
            UAC_DBGMSG("USB streaming terminal found, ID=0x%x\n", ac_otd->bTerminalID);
        }
        else if ((ac_otd->wTerminalType & 0x300) == 0x300)
        {
            UAC_DBGMSG("SPEAKER output terminal found, ID=0x%x\n", ac_otd->bTerminalID);
            uac->acif.speaker_id = ac_otd->bTerminalID;
            uac->acif.speaker_fuid = ac_otd->bSourceID;
        }
        else
        {
            UAC_DBGMSG("Unsupported OUTPUT TERMINAL, ignore it!\n");
        }
        UAC_DBGMSG("      bTerminalID: 0%x\n", ac_otd->bTerminalID);
        UAC_DBGMSG("      wTerminalType: 0%x\n", ac_otd->wTerminalType);
        UAC_DBGMSG("      bAssocTerminal: 0%x\n", ac_otd->bAssocTerminal);
        UAC_DBGMSG("      bSourceID: 0%x\n", ac_otd->bSourceID);
        break;

    case MIXER_UNIT:
#ifdef UAC_DEBUG
        UAC_DBGMSG("AC: MIXER_UNIT\n");
        UAC_DBGMSG("      bUnitID: 0%x\n", ((AC_MXR_T *)bptr)->bUnitID);
        UAC_DBGMSG("      bNrInPins: 0%x\n", ((AC_MXR_T *)bptr)->bNrInPins);
#endif
        break;

    case SELECTOR_UNIT:
#ifdef UAC_DEBUG
        UAC_DBGMSG("AC: SELECTOR_UNIT\n");
        UAC_DBGMSG("      bUnitID: 0%x\n", ((AC_SU_T *)bptr)->bUnitID);
        UAC_DBGMSG("      bNrInPins: 0%x\n", ((AC_SU_T *)bptr)->bNrInPins);
#endif
        break;

    case FEATURE_UNIT:

#ifdef UAC_DEBUG
        UAC_DBGMSG("AC: FEATURE_UNIT\n");
        UAC_DBGMSG("      bUnitID: 0%x\n", ((AC_FU_T *)bptr)->bUnitID);
        UAC_DBGMSG("      bSourceID: 0%x\n", ((AC_FU_T *)bptr)->bSourceID);
        UAC_DBGMSG("      bControlSize: 0%x\n", ((AC_FU_T *)bptr)->bControlSize);
#endif
        break;

    case PROCESSING_UNIT:
#ifdef UAC_DEBUG
        UAC_DBGMSG("AC: PROCESSING_UNIT\n");
        UAC_DBGMSG("      bUnitID: 0%x\n", ((AC_PU_T *)bptr)->bUnitID);
        UAC_DBGMSG("      wProcessType: 0%x\n", ((AC_PU_T *)bptr)->wProcessType);
        UAC_DBGMSG("      bNrInPins: 0%x\n", ((AC_PU_T *)bptr)->bNrInPins);
#endif
        break;

    case EXTENSION_UNIT:
        UAC_DBGMSG("AC: EXTENSION_UNIT\n");
        break;

    default:
        UAC_ERRMSG("uac_parse_ac_interface - unrecognized bDescriptorSubtype 0x%x!\n", ((CS_HDR_T *)bptr)->bDescriptorSubtype);
        return UAC_RET_PARSER;
    }
    return 0;
}

static int  uac_set_microphone_feature_unit(UAC_DEV_T *uac)
{
    DESC_CONF_T  *config;
    AC_FU_T      *hdr;
    uint8_t      *bptr;
    uint8_t      bTerminalID = uac->acif.mic_id;
    int          size;

    bptr = uac->udev->cfd_buff;
    config = (DESC_CONF_T *)bptr;

    /* step over configuration descriptor */
    bptr += config->bLength;
    size = config->wTotalLength - config->bLength;

    /*------------------------------------------------------------------------------------*/
    /*  Find the Terminal Descriptor                                                      */
    /*------------------------------------------------------------------------------------*/
    while (size >= sizeof(DESC_IF_T))
    {
        hdr = (AC_FU_T *)bptr;

        if ((hdr->bDescriptorType == CS_INTERFACE) && (hdr->bDescriptorSubtype == FEATURE_UNIT) &&
                (hdr->bSourceID == bTerminalID))
        {
            uac->acif.mic_fuid = hdr->bUnitID;
            return 0;
        }

        if (hdr->bLength == 0)
            return UAC_RET_PARSER;          /* prevent infinite loop                       */

        bptr += hdr->bLength;
        size -= hdr->bLength;
    }
    return UAC_RET_PARSER;                  /* not found                                  */
}

/**
 *  @brief  Parse and get audio control (AC) interface information from descriptors.
 *  @param[in]  uac    UAC device
 *  @param[in]  iface  Audio control interface
 *  @return   Success or failed.
 *  @retval   0        Success
 *  @retval   Otherwise  Error occurred
 */
int uac_parse_control_interface(UAC_DEV_T *uac, IFACE_T *iface)
{
    DESC_CONF_T  *config;
    DESC_IF_T    *ifd;
    int          if_num;
    uint8_t      *bptr;
    int          size, ret;

    if_num = iface->if_num;                      /* interface number of AC interface      */

    UAC_DBGMSG("UAC parsing audio control (AC) interface %d...\n", if_num);

    memset(&uac->acif, 0, sizeof(uac->acif));    /* clear AC information                  */
    uac->acif.iface = iface;

    bptr = uac->udev->cfd_buff;
    config = (DESC_CONF_T *)bptr;

    /* step over configuration descriptor */
    bptr += config->bLength;
    size = config->wTotalLength - config->bLength;

    /*------------------------------------------------------------------------------------*/
    /*  Find the Standard AC Interface Descriptor                                         */
    /*------------------------------------------------------------------------------------*/
    while (size >= sizeof(DESC_IF_T))
    {
        ifd = (DESC_IF_T *)bptr;

        if ((ifd->bDescriptorType == USB_DT_INTERFACE) && (ifd->bInterfaceNumber == if_num) &&
                (ifd->bInterfaceClass == USB_CLASS_AUDIO) && (ifd->bInterfaceSubClass == SUBCLS_AUDIOCONTROL))
            break;

        if (ifd->bLength == 0)
            return UAC_RET_PARSER;          /* prevent infinite loop                       */

        bptr += ifd->bLength;
        size -= ifd->bLength;
    }

    if (size < sizeof(DESC_IF_T))           /* cannot find the Standard AC descriptor     */
    {
        UAC_ERRMSG("UAC_RET_PARSER! - AC standard not found!\n");
        return UAC_RET_PARSER;
    }

    bptr += ifd->bLength;
    size -= ifd->bLength;

    /*------------------------------------------------------------------------------------*/
    /*  Walk though all Class-Specific AC Interface Descriptor (4.3.2)                    */
    /*------------------------------------------------------------------------------------*/
    while (size > sizeof(DESC_HDR_T))
    {
        ifd = (DESC_IF_T *)bptr;

        if (ifd->bDescriptorType != CS_INTERFACE)
            break;

        ret = uac_parse_ac_interface(uac, bptr);
        if (ret < 0)
        {
            UAC_ERRMSG("UAC_RET_PARSER! - parsing CS\n");
            return UAC_RET_PARSER;
        }

        if (ifd->bLength == 0)
            return UAC_RET_PARSER;          /* prevent infinite loop                       */

        bptr += ifd->bLength;
        size -= ifd->bLength;
    }

    uac_set_microphone_feature_unit(uac);

    UAC_DBGMSG("    Microphone Input Terminal ID: 0x%x\n", uac->acif.mic_id);
    UAC_DBGMSG("    Microphone Feature Unit ID: 0x%x\n", uac->acif.mic_fuid);
    UAC_DBGMSG("    Speaker Output Terminal ID: 0x%x\n", uac->acif.speaker_id);
    UAC_DBGMSG("    Speaker Feature Unit ID: 0x%x\n", uac->acif.speaker_fuid);

    return 0;
}

static int  uac_parse_as_interface(AS_IF_T *asif, uint8_t *bptr)
{
    ALT_IFACE_T  *aif = asif->iface->aif;
    int   i;

    if (((CS_HDR_T *)bptr)->bDescriptorType == USB_DT_ENDPOINT)
    {
        for (i = 0; i < aif->ifd->bNumEndpoints; i++)
        {
            if (aif->ep[i].bEndpointAddress == ((DESC_EP_T *)bptr)->bEndpointAddress)
            {
                asif->ep = &(asif->iface->aif->ep[i]);
                break;
            }
        }
        if (i >= aif->ifd->bNumEndpoints)
        {
            UAC_ERRMSG("Endpoint 0x%x parsing error!\n", ((DESC_EP_T *)bptr)->bEndpointAddress);
            return UAC_RET_PARSER;
        }
        return 0;
    }

    if (((CS_HDR_T *)bptr)->bDescriptorType == CS_ENDPOINT)
    {
        asif->cs_epd = (CS_EP_T *)bptr;
        return 0;
    }

    switch (((CS_HDR_T *)bptr)->bDescriptorSubtype)
    {
    case AS_DESCRIPTOR_UNDEFINED:
        UAC_DBGMSG("AS: AS_DESCRIPTOR_UNDEFINED\n");
        break;

    case AS_GENERAL:
        asif->as_gen = (AS_GEN_T *)bptr;
        UAC_DBGMSG("AS: AS_GENERAL\n");
        UAC_DBGMSG("      bTerminalLink: 0%x\n", asif->as_gen->bTerminalLink);
        UAC_DBGMSG("      wFormatTag: 0%x\n", asif->as_gen->wFormatTag);
        break;

    case FORMAT_TYPE:
        asif->ft = (AS_FT1_T *)bptr;
        UAC_DBGMSG("AS: FORMAT_TYPE\n");
        break;

    case FORMAT_SPECIFIC:
        UAC_DBGMSG("AS: FORMAT_SPECIFIC\n");
        break;

    default:
        UAC_ERRMSG("uac_parse_as_interface - unrecognized bDescriptorSubtype 0x%x!\n", ((CS_HDR_T *)bptr)->bDescriptorSubtype);
        return UAC_RET_PARSER;
    }

    return 0;
}

static int  iface_have_iso_in_ep(IFACE_T *iface)
{
    int         i, j;
    EP_INFO_T   *ep;

    for (i = 0; i < iface->num_alt; i++)
    {
        for (j = 0; j < iface->alt[i].ifd->bNumEndpoints; j++)
        {
            ep = &(iface->alt[i].ep[j]);
            if (ep != NULL)
            {
                if (((ep->bmAttributes & EP_ATTR_TT_MASK) == EP_ATTR_TT_ISO) &&
                        ((ep->bEndpointAddress & EP_ADDR_DIR_MASK) == EP_ADDR_DIR_IN))
                    return 1;
            }
        }
    }
    return 0;
}

static int  iface_have_iso_out_ep(IFACE_T *iface)
{
    int         i, j;
    EP_INFO_T   *ep;

    for (i = 0; i < iface->num_alt; i++)
    {
        for (j = 0; j < iface->alt[i].ifd->bNumEndpoints; j++)
        {
            ep = &(iface->alt[i].ep[j]);
            if (ep != NULL)
            {
                if (((ep->bmAttributes & EP_ATTR_TT_MASK) == EP_ATTR_TT_ISO) &&
                        ((ep->bEndpointAddress & EP_ADDR_DIR_MASK) == EP_ADDR_DIR_OUT))
                    return 1;
            }
        }
    }
    return 0;
}

static void * uac_find_terminal(UAC_DEV_T *uac, uint8_t bTerminalID)
{
    DESC_CONF_T  *config;
    AC_OT_T      *hdr;
    uint8_t      *bptr;
    int          size;

    bptr = uac->udev->cfd_buff;
    config = (DESC_CONF_T *)bptr;

    /* step over configuration descriptor */
    bptr += config->bLength;
    size = config->wTotalLength - config->bLength;

    /*------------------------------------------------------------------------------------*/
    /*  Find the Terminal Descriptor                                                      */
    /*------------------------------------------------------------------------------------*/
    while (size >= sizeof(DESC_IF_T))
    {
        hdr = (AC_OT_T *)bptr;

        if ((hdr->bDescriptorType == CS_INTERFACE) &&
                ((hdr->bDescriptorSubtype == INPUT_TERMINAL) || (hdr->bDescriptorSubtype == OUTPUT_TERMINAL)) &&
                (hdr->bTerminalID == bTerminalID))
            return (void *)hdr;

        if (hdr->bLength == 0)
            return NULL;                    /* prevent infinite loop                       */

        bptr += hdr->bLength;
        size -= hdr->bLength;
    }
    return NULL;                            /* not found                                  */
}

#if 0
static void * uac_find_feature_unit(UAC_DEV_T *uac, uint8_t bUnitID)
{
    DESC_CONF_T  *config;
    AC_FU_T      *hdr;
    uint8_t      *bptr;
    int          size;

    bptr = uac->udev->cfd_buff;
    config = (DESC_CONF_T *)bptr;

    /* step over configuration descriptor */
    bptr += config->bLength;
    size = config->wTotalLength - config->bLength;

    /*------------------------------------------------------------------------------------*/
    /*  Find the Terminal Descriptor                                                      */
    /*------------------------------------------------------------------------------------*/
    while (size >= sizeof(DESC_IF_T))
    {
        hdr = (AC_FU_T *)bptr;

        if ((hdr->bDescriptorType == CS_INTERFACE) && (hdr->bDescriptorSubtype == FEATURE_UNIT) &&
                (hdr->bUnitID == bUnitID))
            return (void *)hdr;

        if (hdr->bLength == 0)
            return NULL;                    /* prevent infinite loop                       */

        bptr += hdr->bLength;
        size -= hdr->bLength;
    }
    return NULL;                            /* not found                                  */
}
#endif

/**
 *  @brief  Parse and get audio streaming (AS) interface information from descriptors.
 *  @param[in]  uac    UAC device
 *  @param[in]  iface  Audio control interface
 *  @param[in]  bAlternateSetting   Selected alternative interface
 *  @return   Success or failed.
 *  @retval   0        Success
 *  @retval   Otherwise  Error occurred
 */
int uac_parse_streaming_interface(UAC_DEV_T *uac, IFACE_T *iface, uint8_t bAlternateSetting)
{
    DESC_CONF_T  *config;
    DESC_IF_T    *ifd;
    AS_IF_T      asif;
    int          if_num;
    uint8_t      *bptr;
    int          size, ret;

    if_num = iface->if_num;                      /* interface number of AC interface      */

    UAC_DBGMSG("UAC parsing audio stream (AS) interface %d, alt %d...\n", if_num, bAlternateSetting);

    memset(&asif, 0, sizeof(asif));              /* clear AS information                  */
    asif.iface = iface;

    bptr = uac->udev->cfd_buff;
    config = (DESC_CONF_T *)bptr;

    /* step over configuration descriptor */
    bptr += config->bLength;
    size = config->wTotalLength - config->bLength;

    /*------------------------------------------------------------------------------------*/
    /*  Find the Standard AS Interface Descriptor                                         */
    /*------------------------------------------------------------------------------------*/
    while (size >= sizeof(DESC_IF_T))
    {
        ifd = (DESC_IF_T *)bptr;

        if ((ifd->bDescriptorType == USB_DT_INTERFACE) &&
                (ifd->bInterfaceNumber == if_num) && (ifd->bAlternateSetting == bAlternateSetting) &&
                (ifd->bInterfaceClass == USB_CLASS_AUDIO) && (ifd->bInterfaceSubClass == SUBCLS_AUDIOSTREAMING))
            break;

        if (ifd->bLength == 0)
            return UAC_RET_PARSER;          /* prevent infinite loop                       */

        bptr += ifd->bLength;
        size -= ifd->bLength;
    }

    if (size < sizeof(DESC_IF_T))           /* cannot find the Standard AC descriptor     */
    {
        UAC_ERRMSG("UAC_RET_PARSER! - AC standard not found!\n");
        return UAC_RET_PARSER;
    }

    if (ifd->bNumEndpoints == 0)
    {
        UAC_DBGMSG("This alternative interface is an idle interface.\n");
        return 0;
    }

    bptr += ifd->bLength;
    size -= ifd->bLength;

    /*------------------------------------------------------------------------------------*/
    /*  Walk though all Class-Specific AS Interface Descriptor (4.5.2)                    */
    /*------------------------------------------------------------------------------------*/
    while (size > sizeof(DESC_HDR_T))
    {
        ifd = (DESC_IF_T *)bptr;

        //UAC_DBGMSG("Parse AS - [%d] [0x%x] [0x%x]\n", ((CS_HDR_T *)bptr)->bLength, ((CS_HDR_T *)bptr)->bDescriptorType, ((CS_HDR_T *)bptr)->bDescriptorSubtype);

        if ((ifd->bDescriptorType != CS_INTERFACE) &&
                (ifd->bDescriptorType != USB_DT_ENDPOINT) &&
                (ifd->bDescriptorType != CS_ENDPOINT))
            break;


        ret = uac_parse_as_interface(&asif, bptr);
        if (ret < 0)
        {
            UAC_ERRMSG("UAC_RET_PARSER! - parsing CS\n");
            return UAC_RET_PARSER;
        }

        if (ifd->bLength == 0)
            return UAC_RET_PARSER;          /* prevent infinite loop                       */

        bptr += ifd->bLength;
        size -= ifd->bLength;
    }

    if (asif.as_gen == NULL)
    {
        UAC_ERRMSG("UAC_RET_PARSER! - AS_GEN not found!\n");
        return UAC_RET_PARSER;
    }

    if (iface_have_iso_in_ep(iface))
    {
        /* Find microphone's output terminal by AS_GEN's bTerminalLink */
        asif.ot = (AC_OT_T *)uac_find_terminal(uac, asif.as_gen->bTerminalLink);
        if (asif.ot)
        {
            UAC_DBGMSG("Audio in Terminal ID: 0%x\n", asif.ot->bTerminalID);
            UAC_DBGMSG("    bDescriptorSubtype: 0%x\n", asif.ot->bDescriptorSubtype);
            UAC_DBGMSG("    wTerminalType: 0%x\n", asif.ot->wTerminalType);
            UAC_DBGMSG("    bAssocTerminal: 0%x\n", asif.ot->bAssocTerminal);
            UAC_DBGMSG("    bSourceID: 0%x\n", asif.ot->bSourceID);
        }
        else
        {
            UAC_ERRMSG("Cannot find audio in Output Terminal %d!\n", asif.as_gen->bTerminalLink);
        }
        memcpy(&uac->asif_in, &asif, sizeof(asif));
    }
    else if (iface_have_iso_out_ep(iface))
    {
        asif.it = (AC_IT_T *)uac_find_terminal(uac, asif.as_gen->bTerminalLink);
        if (asif.it)
        {
            UAC_DBGMSG("Audio out Terminal ID: 0%x\n", asif.it->bTerminalID);
            UAC_DBGMSG("    bDescriptorSubtype: 0%x\n", asif.it->bDescriptorSubtype);
            UAC_DBGMSG("    wTerminalType: 0%x\n", asif.it->wTerminalType);
            UAC_DBGMSG("    bAssocTerminal: 0%x\n", asif.it->bAssocTerminal);
        }
        else
        {
            UAC_ERRMSG("Cannot find audio in Output Terminal %d!\n", asif.as_gen->bTerminalLink);
        }
        memcpy(&uac->asif_out, &asif, sizeof(asif));
    }
    else
    {
        UAC_ERRMSG("Interface cannot find iso endpoints!\n");
        return UAC_RET_PARSER;
    }

    UAC_DBGMSG("\n\nAudio stream interface parsing done =>\n");
    UAC_DBGMSG("    Interface: %d, Alt: %d (iface = 0x%x)\n", if_num, bAlternateSetting, asif.iface);
    if (asif.ep)
        UAC_DBGMSG("    Endpoint: 0x%x, wMaxPacketSize: %d\n", asif.ep->bEndpointAddress, asif.ep->wMaxPacketSize);
    UAC_DBGMSG("    as_gen: %s\n", (asif.as_gen == NULL) ? "Not Found" : "OK");
    UAC_DBGMSG("    it: %s\n", (asif.it == NULL) ? "Not Found" : "OK");
    UAC_DBGMSG("    ot: %s\n", (asif.ot == NULL) ? "Not Found" : "OK");
    UAC_DBGMSG("    ft: %s\n", (asif.ft == NULL) ? "Not Found" : "OK");
    UAC_DBGMSG("    cs_epd: %s\n", (asif.cs_epd == NULL) ? "Not Found" : "OK");

    return 0;
}


/// @endcond HIDDEN_SYMBOLS

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/

