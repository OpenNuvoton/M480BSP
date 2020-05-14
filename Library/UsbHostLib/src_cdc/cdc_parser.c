/**************************************************************************//**
 * @file     cdc_parser.c
 * @version  V1.00
 * @brief    M480 MCU USB Host CDC Class driver
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "NuMicro.h"

#include "usb.h"
#include "usbh_lib.h"
#include "usbh_cdc.h"

/// @cond HIDDEN_SYMBOLS


static int  cdc_parse_cs_interface(CDC_DEV_T *cdev, uint8_t *buffer, int size)
{
    DESC_HDR_T      *header;
    CDC_IF_HDR_T    *cifd;
    int             parsed = 0;

    while (size > 0)
    {
        while(size >= sizeof(DESC_HDR_T))
        {
            header = (DESC_HDR_T *)buffer;

            if (header->bLength < 2)
            {
                CDC_DBGMSG("Invalid descriptor length of %d\n", header->bLength);
                return -1;
            }

            if (header->bDescriptorType != CDC_CS_INTERFACE)
                return parsed;

            cifd = (CDC_IF_HDR_T *)header;

            CDC_DBGMSG("CS_INTERFACE: 0x%x, ", cifd->bDescriptorSubtype);

            switch (cifd->bDescriptorSubtype)
            {
            case CDC_DT_HDR_FUNC:
                CDC_DBGMSG("Header Functional\n");
                break;
            case CDC_DT_CALL_MANAGE:
                CDC_DBGMSG("Call Management\n");
                break;
            case CDC_DT_ABS_CTRL:
                CDC_DBGMSG("Abstract Control Management\n");
                break;
            case CDC_DT_LINE_MANAGE:
                CDC_DBGMSG("Direct Line Management\n");
                break;
            case CDC_DT_TEL_RINGER:
                CDC_DBGMSG("Telephone Ringer\n");
                break;
            case CDC_DT_TEL_OPER_MODES:
                CDC_DBGMSG("Telephone Operational Modes\n");
                break;
            case CDC_DT_CALL_LINE_CAP:
                CDC_DBGMSG("Telephone Call and Line State Reporting Capabilities\n");
                break;
            case CDC_DT_UNION:
                CDC_DBGMSG("Union Functional\n");
                if (cifd->bLength >= 5)
                    cdev->ifnum_data = cifd->payload[1];
                if (cifd->bLength >= 6)
                {
                    CDC_DBGMSG("Union Functional length %d, not supported!\n", cifd->bLength);
                }
                break;
            case CDC_DT_COUNTRY_SEL:
                CDC_DBGMSG("Country Selection\n");
                break;
            case CDC_DT_USB_TERMINAL:
                CDC_DBGMSG("USB Terminal\n");
                break;
            case CDC_DT_NET_CHANNEL:
                CDC_DBGMSG("Network Channel Terminal\n");
                break;
            case CDC_DT_PROTO_UNIT:
                CDC_DBGMSG("Protocol Unit\n");
                break;
            case CDC_DT_EXTENT_UNIT:
                CDC_DBGMSG("Extension Unit\n");
                break;
            case CDC_DT_MULTI_CHANNEL:
                CDC_DBGMSG("Multi-Channel Management\n");
                break;
            case CDC_DT_CAPI_CTRL:
                CDC_DBGMSG("CAPI Control Management\n");
                break;
            case CDC_DT_ETHERNET_FUNC:
                CDC_DBGMSG("Ethernet Networking Functional\n");
                break;
            case CDC_DT_ATM_FUNC:
                CDC_DBGMSG("ATM Networking Functional\n");
                break;
            }

            buffer += header->bLength;
            parsed += header->bLength;
            size -= header->bLength;
        }

    }   /* end of while */
    return parsed;
}


int  cdc_config_parser(CDC_DEV_T *cdev)
{
    UDEV_T          *udev = cdev->udev;
    DESC_CONF_T     *config;
    DESC_HDR_T      *header;
    DESC_IF_T       *ifd;
    uint8_t         *bptr;
    int             size, result;

    config = (DESC_CONF_T *)udev->cfd_buff;
    bptr = (uint8_t *)config;
    bptr += config->bLength;
    size = config->wTotalLength - config->bLength;

    while (size >= sizeof(DESC_HDR_T))
    {
        header = (DESC_HDR_T *)bptr;

        if ((header->bLength > size) || (header->bLength < 2))
        {
            CDC_DBGMSG("Error - invalid descriptor length of %d\n", header->bLength);
            return USBH_ERR_NOT_SUPPORTED;
        }

        /*
         *  Is the interface descriptor of this CDC device?
         */
        if (header->bDescriptorType == USB_DT_INTERFACE)
        {
            ifd = (DESC_IF_T *)header;
            if (ifd->bInterfaceNumber == cdev->iface_cdc->if_num)
            {
                bptr += header->bLength;
                size -= header->bLength;
                break;
            }
        }
        bptr += header->bLength;
        size -= header->bLength;
    }   /* end of while */

    /*------------------------------------------------------------------*/
    /*  Parsing all follwoing CDC class interface descriptors           */
    /*------------------------------------------------------------------*/

    while (size >= sizeof(DESC_HDR_T))
    {
        header = (DESC_HDR_T *)bptr;

        if ((header->bLength > size) || (header->bLength < 2))
        {
            CDC_DBGMSG("Error - invalid descriptor length of %d\n", header->bLength);
            return USBH_ERR_NOT_SUPPORTED;
        }

        /*
         *  Is a class interface descriptor?
         */
        if (header->bDescriptorType != CDC_CS_INTERFACE)
            break;

        result = cdc_parse_cs_interface(cdev, bptr, size);
        if (result < 0)
            return result;
        bptr += result;
        size -= result;
    }   /* end of while */

    CDC_DBGMSG("CDC ifnum_cdc = %d\n", cdev->iface_cdc->if_num);
    if (cdev->iface_data)
    {
        CDC_DBGMSG("CDC ifnum_data = %d\n", cdev->iface_data->if_num);
    }
    return 0;
}


/// @endcond HIDDEN_SYMBOLS

/*** (C) COPYRIGHT 2018~2019 Nuvoton Technology Corp. ***/

