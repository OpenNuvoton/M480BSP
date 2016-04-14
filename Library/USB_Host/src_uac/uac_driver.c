/**************************************************************************//**
 * @file     uac_driver.c
 * @version  V1.00
 * $Revision: 2 $
 * $Date: 15/06/12 10:12a $
 * @brief    M480 MCU USB Host Audio Class driver
 *
 * @note     Support mono and stero audio input and output.
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "M480.h"

#include "usb.h"
#include "usbh_lib.h"
#include "usbh_uac.h"
#include "uac.h"


/** @addtogroup M480_Library M480 Library
  @{
*/

/** @addtogroup M480_USBH_Library USB Host Library
  @{
*/

/** @addtogroup M480_USBH_EXPORTED_FUNCTIONS USB Host Exported Functions
  @{
*/

/// @cond HIDDEN_SYMBOLS

static UAC_DEV_T    g_au_dev[CONFIG_AU_MAX_DEV];
static UAC_INFO_T   g_uac_info[CONFIG_AU_MAX_DEV];

static UAC_DEV_T *g_audev_list = NULL;

int  au_parsing_descriptors(UAC_DEV_T *audev);

static UAC_DEV_T *alloc_as_device(void)
{
    int     i;

    for (i = 0; i < CONFIG_AU_MAX_DEV; i++) {
        if (g_au_dev[i].udev == NULL) {
            memset((char *)&g_au_dev[i], 0, sizeof(UAC_DEV_T));
            g_au_dev[i].ctrl_ifnum = -1;
            g_au_dev[i].au_in_ifnum = -1;
            g_au_dev[i].au_out_ifnum = -1;
            memset((char *)&g_uac_info[i], 0, sizeof(UAC_INFO_T));
            g_au_dev[i].priv = (void *)&g_uac_info[i];
            return &g_au_dev[i];
        }
    }
    return NULL;
}

static void  free_au_device(UAC_DEV_T *audev)
{
    audev->udev = NULL;
}

UAC_DEV_T *find_as_deivce_by_udev(struct usb_device *udev)
{
    int     i;

    if (udev == NULL)
        return NULL;

    for (i = 0; i < CONFIG_AU_MAX_DEV; i++) {
        if (g_au_dev[i].udev == udev) {
            return &g_au_dev[i];
        }
    }
    return NULL;
}

int  find_as_device(UAC_DEV_T *hdev)
{
    int    i;

    for (i = 0; i < CONFIG_AU_MAX_DEV; i++) {
        if (&g_au_dev[i] == hdev) {
            return TRUE;
        }
    }
    return FALSE;
}


static int  au_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
    struct usb_device *udev;
    struct usb_host_interface *desc;
    struct usb_host_endpoint  *ep;

    int         ifnum;
    UAC_DEV_T   *audev, *p;
    int         i;

    desc = intf->cur_altsetting;
    udev = interface_to_usbdev(intf);

    USBAS_DBGMSG("au_probe - device (vid=0x%x, pid=0x%x), interface %d.\n",
                 udev->descriptor.idVendor, udev->descriptor.idProduct, desc->desc.bInterfaceNumber);

    if ((desc->desc.bInterfaceSubClass != SUBCLS_AUDIOCONTROL) &&
            (desc->desc.bInterfaceSubClass != SUBCLS_AUDIOSTREAMING)) {
        printf("Does not support audio sub-class %x\n", desc->desc.bInterfaceSubClass);
        return UAC_RET_DRV_NOT_SUPPORTED;
    }


    ifnum = desc->desc.bInterfaceNumber;

    audev = find_as_deivce_by_udev(udev);
    if (audev != NULL) {
        printf("reduant calling to au_probe()!\n");
        return UAC_RET_DRV_NOT_SUPPORTED;
    }

    audev = alloc_as_device();
    if (audev == NULL)
        return UAC_RET_OUT_OF_MEMORY;

    audev->next = NULL;
    audev->udev = udev;

    USBAS_DBGMSG("au_probe called for ifnum %d\n", ifnum);

    if (desc->desc.bInterfaceSubClass == SUBCLS_AUDIOSTREAMING) {
        /*
         * Try to find any interrupt endpoints
         */
        for (i = 0, ep = NULL; i < desc->desc.bNumEndpoints; i++) {
            /* Is it an Isochronous endpoint? */
            if ((desc->endpoint[i].desc.bmAttributes &
                    USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_ISOC) {
                ep =  &(desc->endpoint[i]);
                break;
            }
        }

        if (ep == NULL) {
            USBAS_DBGMSG("couldn't find isochronous endpoints\n");
            return UAC_RET_DRV_NOT_SUPPORTED;
        }

        if ((ep->desc.bEndpointAddress & USB_ENDPOINT_DIR_MASK) == USB_DIR_IN) {
            audev->ep_au_in = ep;
            audev->au_in_ifnum = ifnum;
            USBAS_DBGMSG("Audio in stream interface is %d\n", ifnum);
        } else {
            audev->ep_au_out = ep;
            audev->au_out_ifnum = ifnum;
            USBAS_DBGMSG("Audio out stream interface is %d\n", ifnum);
        }
    } else {
        audev->ctrl_ifnum = ifnum;
        USBAS_DBGMSG("Audio control interface is %d\n", ifnum);
    }

    /*
     *  Chaining newly found Audio Class device to end of Audio Class device list.
     */
    if (g_audev_list == NULL)
        g_audev_list = audev;
    else {
        for (p = g_audev_list; p->next != NULL; p = p->next)
            ;
        p->next = audev;
    }

    return uac_config_parser(audev);
}


static void  au_disconnect(struct usb_interface *intf)
{
    struct usb_device *udev;
    UAC_DEV_T   *audev, *p;
    UAC_INFO_T  *uac_info;
    int    i;

    USBAS_DBGMSG("Audio Class device disconnected!\n");

    udev = interface_to_usbdev(intf);

    audev = find_as_deivce_by_udev(udev);
    if (audev == NULL)
        return;

    uac_info = (UAC_INFO_T *)audev->priv;

    for (i = 0; i < ISO_IN_URB_CNT; i++) {
        if (audev->urbin[i]) {
            usb_unlink_urb(audev->urbin[i]);
            if (audev->urbin[i]->transfer_buffer)
                USB_free(audev->urbin[i]->transfer_buffer);
            usb_free_urb(audev->urbin[i]);
        }
    }

    for (i = 0; i < ISO_OUT_URB_CNT; i++) {
        if (audev->urbout[i]) {
            usb_unlink_urb(audev->urbout[i]);
            if (audev->urbout[i]->transfer_buffer)
                USB_free(audev->urbout[i]->transfer_buffer);
            usb_free_urb(audev->urbout[i]);
        }
    }

    if (uac_info->cfg_desc != NULL) {
        USB_free(uac_info->cfg_desc);
        uac_info->cfg_desc = NULL;
    }

    /*
     *  Remove this Audio Class device from device list.
     */
    if (audev == g_audev_list)
        g_audev_list = g_audev_list->next;
    else {
        for (p = g_audev_list; p != NULL; p = p->next) {
            if (p->next == audev) {
                p->next = audev->next;
                break;
            }
        }
    }
    free_au_device(audev);
}


static struct usb_device_id  au_id_table[] = {
    {
        USB_DEVICE_ID_MATCH_INT_CLASS,    /* match_flags */
        0, 0, 0, 0, 0, 0, 0,
        UAC_IFACE_CODE,                     /* Audio Interface Class Code */
        0, 0, 0
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0 }         /* Terminating entry */
};


static struct usb_driver  au_driver = {
    "uac",
    au_probe,
    au_disconnect,
    NULL,                       /* suspend */
    NULL,                       /* resume */
    NULL,                       /* reset_resume */
    NULL,                       /* pre_reset */
    NULL,                       /* post_reset */
    au_id_table
};


/// @endcond HIDDEN_SYMBOLS

/**
  * @brief    Initialize this USB Audio Class driver.
  * @return   None
  */
void usbh_uac_init(void)
{
    memset((char *)&g_au_dev[0], 0, sizeof(g_au_dev));
    g_audev_list = NULL;
    usb_register_driver(&au_driver, "UAC driver");
}


/**
 *  @brief   Get a list of currently connected USB Audio Class devices.
 *  @return  List of current connected UAC devices.
 *  @retval  NULL       There's no UAC devices found.
 *  @retval  Otherwise  A list of connected UAC devices.
 *
 *  The Audio Class devices are chained by the "next" member of UAC_DEV_T.
 */
UAC_DEV_T * usbh_uac_get_device_list(void)
{
    return g_audev_list;
}


/*@}*/ /* end of group M480_USBH_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group M480_USBH_Library */

/*@}*/ /* end of group M480_Library */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/

