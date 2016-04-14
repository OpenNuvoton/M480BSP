/**************************************************************************//**
 * @file     uac_parser.c
 * @version  V1.00
 * $Revision: 1 $
 * $Date: 15/06/10 2:03p $
 * @brief    M480 MCU USB Host Audio Class driver
 *
 * @note
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "M480.h"

#include "usb.h"
#include "usbh_lib.h"
#include "usbh_uac.h"
#include "uac.h"

/// @cond HIDDEN_SYMBOLS


static AC_FU_T *  funit[MAX_FEATURE_UNIT];       /* array recording position of FEATURE UNITs */
static int        fu_cnt;                        /* number of FEATURE UNITs */


static int  uac_parse_cs_interface(UAC_DEV_T *audev, struct usb_interface_descriptor *ifp,
                                   uint8_t *buffer, int size)
{
    UAC_INFO_T   *uac_info = (UAC_INFO_T *)audev->priv;
    AC_IF_HDR_T  *hdr;
    AS_GEN_T     *as_gen;
    AC_IT_T      *ac_itd;
    AC_OT_T      *ac_otd;
#ifdef USBAS_DEBUG
    AC_FU_T      *ac_fu;
    AC_PU_T      *ac_pu;
    AC_MXR_T     *ac_mxr;
    AC_SU_T      *ac_su;
#endif

    hdr = (AC_IF_HDR_T *)buffer;

    if (ifp->bInterfaceSubClass == SUBCLS_AUDIOCONTROL) {
        switch (hdr->bDescriptorSubtype) {
        case AC_DESCRIPTOR_UNDEFINED:
            USBAS_DBGMSG("AC: AC_DESCRIPTOR_UNDEFINED\n");
            break;

        case HEADER:
            USBAS_DBGMSG("AC: HEADER\n");
            break;

        case INPUT_TERMINAL:
            USBAS_DBGMSG("AC: INPUT_TERMINAL\n");
            ac_itd = (AC_IT_T *)buffer;
            if (ac_itd->wTerminalType == UAC_TT_USB_STREAMING) {
                USBAS_DBGMSG("SPEAKER USB streaming terminal found, ID=0x%x\n", ac_itd->bTerminalID);
                uac_info->it_usbs = ac_itd;
            } else if ((ac_itd->wTerminalType & 0x200) == 0x200) {
                USBAS_DBGMSG("MICROPHONE input terminal found, ID=0x%x\n", ac_itd->bTerminalID);
                uac_info->it_microphone = ac_itd;
            } else {
                USBAS_DBGMSG("Unsupported INPUT TERMINAL, ignore it!\n");
            }
            USBAS_DBGMSG("      bTerminalID: 0%x\n", ac_itd->bTerminalID);
            USBAS_DBGMSG("      wTerminalType: 0%x\n", ac_itd->wTerminalType);
            USBAS_DBGMSG("      bAssocTerminal: 0%x\n", ac_itd->bAssocTerminal);
            USBAS_DBGMSG("      bNrChannels: 0%x\n", ac_itd->bNrChannels);
            USBAS_DBGMSG("      wChannelConfig: 0%x\n", ac_itd->wChannelConfig);
            break;

        case OUTPUT_TERMINAL:
            USBAS_DBGMSG("AC: OUTPUT_TERMINAL\n");
            ac_otd = (AC_OT_T *)buffer;
            if (ac_otd->wTerminalType == UAC_TT_USB_STREAMING) {
                USBAS_DBGMSG("MICROPHONE USB streaming terminal found, ID=0x%x\n", ac_otd->bTerminalID);
                uac_info->ot_usbs = ac_otd;
            } else if ((ac_otd->wTerminalType & 0x300) == 0x300) {
                USBAS_DBGMSG("SPEAKER output terminal found, ID=0x%x\n", ac_otd->bTerminalID);
                uac_info->ot_speaker = ac_otd;
            } else {
                USBAS_DBGMSG("Unsupported OUTPUT TERMINAL, ignore it!\n");
            }
            USBAS_DBGMSG("      bTerminalID: 0%x\n", ac_otd->bTerminalID);
            USBAS_DBGMSG("      wTerminalType: 0%x\n", ac_otd->wTerminalType);
            USBAS_DBGMSG("      bAssocTerminal: 0%x\n", ac_otd->bAssocTerminal);
            USBAS_DBGMSG("      bSourceID: 0%x\n", ac_otd->bSourceID);
            break;

        case MIXER_UNIT:
            USBAS_DBGMSG("AC: MIXER_UNIT\n");
#ifdef USBAS_DEBUG
            ac_mxr = (AC_MXR_T *)buffer;
            USBAS_DBGMSG("      bUnitID: 0%x\n", ac_mxr->bUnitID);
            USBAS_DBGMSG("      bNrInPins: 0%x\n", ac_mxr->bNrInPins);
#endif
            break;

        case SELECTOR_UNIT:
            USBAS_DBGMSG("AC: SELECTOR_UNIT\n");
#ifdef USBAS_DEBUG
            ac_su = (AC_SU_T *)buffer;
            USBAS_DBGMSG("      bUnitID: 0%x\n", ac_su->bUnitID);
            USBAS_DBGMSG("      bNrInPins: 0%x\n", ac_su->bNrInPins);
#endif
            break;

        case FEATURE_UNIT:
            USBAS_DBGMSG("AC: FEATURE_UNIT\n");
            if (fu_cnt < MAX_FEATURE_UNIT) {
                funit[fu_cnt] = (AC_FU_T *)buffer;
                fu_cnt++;
            } else {
                USBAS_ERRMSG("Too many FEATURE UNITs, information may be lost!\n");
            }
#ifdef USBAS_DEBUG
            ac_fu = (AC_FU_T *)buffer;
            USBAS_DBGMSG("      bUnitID: 0%x\n", ac_fu->bUnitID);
            USBAS_DBGMSG("      bSourceID: 0%x\n", ac_fu->bSourceID);
            USBAS_DBGMSG("      bControlSize: 0%x\n", ac_fu->bControlSize);
#endif
            break;

        case PROCESSING_UNIT:
            USBAS_DBGMSG("AC: PROCESSING_UNIT\n");
#ifdef USBAS_DEBUG
            ac_pu = (AC_PU_T *)buffer;
            USBAS_DBGMSG("      bUnitID: 0%x\n", ac_pu->bUnitID);
            USBAS_DBGMSG("      wProcessType: 0%x\n", ac_pu->wProcessType);
            USBAS_DBGMSG("      bNrInPins: 0%x\n", ac_pu->bNrInPins);
#endif
            break;

        case EXTENSION_UNIT:
            USBAS_DBGMSG("AC: EXTENSION_UNIT\n");
            break;
        }
    }

    if (ifp->bInterfaceSubClass == SUBCLS_AUDIOSTREAMING) {
        switch (hdr->bDescriptorSubtype) {
        case AS_DESCRIPTOR_UNDEFINED:
            USBAS_DBGMSG("AS: AS_DESCRIPTOR_UNDEFINED\n");
            break;

        case AS_GENERAL:
            USBAS_DBGMSG("AS: AS_GENERAL\n");
            as_gen = (AS_GEN_T *)hdr;
            uac_info->last_gen = as_gen;
            USBAS_DBGMSG("      bTerminalLink: 0%x\n", as_gen->bTerminalLink);
            USBAS_DBGMSG("      wFormatTag: 0%x\n", as_gen->wFormatTag);
            break;

        case FORMAT_TYPE:
            uac_info->last_ft = (AC_FT1_T *)hdr;
            USBAS_DBGMSG("AS: FORMAT_TYPE\n");
            break;

        case FORMAT_SPECIFIC:
            USBAS_DBGMSG("AS: FORMAT_SPECIFIC\n");
            break;
        }
    }

    return hdr->bLength;
}


static int  uac_parse_interface(UAC_DEV_T *audev, uint8_t *buffer, int size)
{
    UAC_INFO_T      * uac_info = (UAC_INFO_T *)audev->priv;
    struct usb_descriptor_header  * header=NULL;
    static struct usb_interface_descriptor   *ifp;
    struct usb_endpoint_descriptor  *ep;
    int             retval, parsed = 0;

    while (size > 0) {
        while (size >= sizeof(struct usb_descriptor_header)) {
            header = (struct usb_descriptor_header *)buffer;

            if (header->bLength < 2) {
                USBAS_DBGMSG("Invalid descriptor length of %d\n", header->bLength);
                return -1;
            }

            /* We interested in Audio Class-specific descriptor only. */
            if ((header->bDescriptorType == USB_DT_INTERFACE) ||
                    (header->bDescriptorType == USB_DT_ENDPOINT) ||
                    (header->bDescriptorType == USB_DT_CONFIG) ||
                    (header->bDescriptorType == USB_DT_DEVICE) ||
                    (header->bDescriptorType == CS_INTERFACE) ||
                    (header->bDescriptorType == CS_ENDPOINT))
                break;

            USBAS_DBGMSG("IF skipping descriptor 0x%X\n", header->bDescriptorType);
            buffer += header->bLength;
            parsed += header->bLength;
            size -= header->bLength;
        }

        if (header->bDescriptorType == USB_DT_INTERFACE) {
            ifp = (struct usb_interface_descriptor *)buffer;

            USBAS_DBGMSG("DT_INTERFACE\n");
            USBAS_DBGMSG("      bInterfaceNumber: %d\n", ifp->bInterfaceNumber);

            uac_info->last_ifd = ifp;

            /* Skip over the interface */
            buffer += ifp->bLength;
            parsed += ifp->bLength;
            size -= ifp->bLength;
        } else if (header->bDescriptorType == CS_INTERFACE) {
            retval = uac_parse_cs_interface(audev, uac_info->last_ifd, buffer, size);
            if (retval < 0)
                return retval;

            buffer += retval;
            parsed += retval;
            size -= retval;
        } else if (header->bDescriptorType == CS_ENDPOINT) {
            USBAS_DBGMSG("CS_ENDPOINT\n");
            buffer += header->bLength;
            parsed += header->bLength;
            size -= header->bLength;
        } else if (header->bDescriptorType == USB_DT_ENDPOINT) {
            ep = (struct usb_endpoint_descriptor *)header;
            USBAS_DBGMSG("USB_DT_ENDPOINT\n");
            USBAS_DBGMSG("      bEndpointAddress: 0x%x, %s\n", ep->bEndpointAddress, (ep->bEndpointAddress & 0x80) ? "IN" : "OUT");
            USBAS_DBGMSG("      wMaxPacketSize: %d\n", ep->wMaxPacketSize);
            USBAS_DBGMSG("      bInterval: %d\n", ep->bInterval);

            if ((ep->bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_ISOC) {
                if (ep->bEndpointAddress & 0x80) { /* is IN endpoint? */
                    if (ep->wMaxPacketSize > AU_IN_MAX_PKTSZ) {
                        USBAS_ERRMSG("IN endpoint packet size is larger than AU_IN_MAX_PKTSZ setting!\n");
                        return UAC_RET_DRV_NOT_SUPPORTED;
                    }
                    uac_info->ifd_rec = uac_info->last_ifd;
                    uac_info->epd_rec = ep;
                    uac_info->gen_rec = uac_info->last_gen;
                    if ((uac_info->last_ft->bFormatType == FORMAT_TYPE_I) ||
                            (uac_info->last_ft->bFormatType == FORMAT_TYPE_III))
                        uac_info->ft_rec = uac_info->last_ft;
                } else {
                    if (ep->wMaxPacketSize > AU_OUT_MAX_PKTSZ) {
                        USBAS_ERRMSG("OUT endpoint packet size is larger than AU_OUT_MAX_PKTSZ setting!\n");
                        return UAC_RET_DRV_NOT_SUPPORTED;
                    }
                    uac_info->ifd_play = uac_info->last_ifd;
                    uac_info->epd_play = ep;
                    uac_info->gen_play = uac_info->last_gen;
                    if ((uac_info->last_ft->bFormatType == FORMAT_TYPE_I) ||
                            (uac_info->last_ft->bFormatType == FORMAT_TYPE_III))
                        uac_info->ft_play = uac_info->last_ft;
                }
            }

            buffer += header->bLength;
            parsed += header->bLength;
            size -= header->bLength;
        } else {
            USBAS_DBGMSG("Unexpected error occurred on parsing interface descriptor!\n");
            break;
        }

    }   /* end of while */
    return parsed;
}


int  uac_config_parser(UAC_DEV_T *audev)
{
    struct usb_device  *udev = audev->udev;
    UAC_INFO_T *uac_info = (UAC_INFO_T *)audev->priv;
    struct usb_config_descriptor  *config;
    struct usb_descriptor_header  *header;
    uint8_t    *buffer;
    int        i, length, size, result;

    buffer = USB_malloc(MAX_CFG_DESC_SIZE, 32);
    if (buffer == NULL)
        return UAC_RET_OUT_OF_MEMORY;
    uac_info->cfg_desc = buffer;

    config = (struct usb_config_descriptor *)buffer;

    USBAS_DBGMSG("\n\n");
    USBAS_DBGMSG("+------------------------------+\n");
    USBAS_DBGMSG("|   UAC descriptor parser      |\n");
    USBAS_DBGMSG("+------------------------------+\n");

    /*------------------------------------------------------------------*/
    /*  Get configuration descriptor from device...                     */
    /*------------------------------------------------------------------*/

    result = usb_get_descriptor(udev, USB_DT_CONFIG, 0, buffer, 8);
    if (result < 8)
        return -1;

    length = config->wTotalLength;
    if (length > MAX_CFG_DESC_SIZE) {
        USBAS_ERRMSG("The Configuration descriptor of Audio Class device is too large.\n");
        USBAS_ERRMSG("Please enlarge MAX_CFG_DESC_SIZE in usbh_uac.h to be larger than %d.\n", length);
        return -1;
    }

    /* Now that we know the length, get the whole thing */
    result = usb_get_descriptor(udev, USB_DT_CONFIG, 0, buffer, length);
    if (result != length) {
        USBAS_DBGMSG("Failed to get configuration descriptor!\n");
        return -1;
    }

    /*------------------------------------------------------------------*/
    /*  Parsing configuration descriptor...                             */
    /*------------------------------------------------------------------*/

    fu_cnt = 0;
    buffer = (uint8_t *)uac_info->cfg_desc;
    buffer += config->bLength;
    size = config->wTotalLength - config->bLength;

    for (i = 0; i < config->bNumInterfaces; i++) {
        /* Skip over the rest of the Class Specific or Vendor */
        /*  Specific descriptors */
        while (size >= sizeof(struct usb_descriptor_header)) {
            header = (struct usb_descriptor_header *)buffer;

            if ((header->bLength > size) || (header->bLength < 2)) {
                USBAS_DBGMSG("Error - invalid descriptor length of %d\n", header->bLength);
                return -1;
            }

            /* If we find another descriptor which is at or below */
            /*  us in the descriptor heirarchy then we're done  */
            if ((header->bDescriptorType == USB_DT_ENDPOINT) ||
                    (header->bDescriptorType == USB_DT_INTERFACE) ||
                    (header->bDescriptorType == USB_DT_CONFIG) ||
                    (header->bDescriptorType == USB_DT_DEVICE) ||
                    (header->bDescriptorType == CS_INTERFACE) ||
                    (header->bDescriptorType == CS_ENDPOINT))
                break;

            USBAS_DBGMSG("CFG skipping descriptor 0x%X\n", header->bDescriptorType);

            buffer += header->bLength;
            size -= header->bLength;
        } /* end of while */

        result = uac_parse_interface(audev, buffer, size);
        if (result < 0)
            return -1;

        buffer += result;
        size -= result;
    }

    if ((uac_info->gen_play == NULL) && (uac_info->gen_rec == NULL)) {
        USBAS_ERRMSG("Audio stream interface not found!\n");
        return -1;
    }

    for (i = 0; i < fu_cnt; i++) {
        if (funit[i]->bSourceID == uac_info->it_microphone->bTerminalID) {
            uac_info->fu_rec = funit[i];
            break;
        }
    }

    for (i = 0; i < fu_cnt; i++) {
        if (funit[i]->bUnitID == uac_info->ot_speaker->bSourceID) {
            uac_info->fu_play = funit[i];
            break;
        }
    }

    if (uac_info->fu_play)
        USBAS_DBGMSG("FEATURE UNIT for playback is 0x%x\n", uac_info->fu_play->bUnitID);

    if (uac_info->fu_rec)
        USBAS_DBGMSG("FEATURE UNIT for record is 0x%x\n", uac_info->fu_rec->bUnitID);

    return 0;
}


int uac_check_fu_ctrl(UAC_INFO_T  *uac_info, uint8_t target, int channel, int control)
{
    AC_FU_T   *fu = NULL;
    AC_FT1_T  *ft = NULL;
    uint8_t   *bptr;
    uint16_t  bitmap;

    if (channel == 0)
        return 0;          /* always fine for master channel */

    if (target == UAC_SPEAKER) {
        fu = uac_info->fu_play;
        ft = uac_info->ft_play;
    } else if (target == UAC_MICROPHONE) {
        fu = uac_info->fu_rec;
        ft = uac_info->ft_rec;
    } else
        return UAC_RET_INVALID;

    if (!fu || !ft)
        return UAC_RET_DEV_NOT_SUPPORTED;

    if (channel > ft->bNrChannels)
        return UAC_RET_DEV_NOT_SUPPORTED;

    bptr = (uint8_t *)fu + 6 + fu->bControlSize * (channel - 1);

    if (fu->bControlSize == 1)
        bitmap = *bptr;
    else
        bitmap = *bptr | (*(bptr+1) << 8);

    USBAS_DBGMSG("channel %d bmaControl is 0x%x\n", channel, bitmap);

    if (bitmap & (1 << (control-1)))
        return 0;      // UAC device support this control.
    else
        return UAC_RET_DEV_NOT_SUPPORTED;
}


/// @endcond HIDDEN_SYMBOLS

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/

