/**************************************************************************//**
 * @file     hid_driver.c
 * @version  V1.00
 * $Revision: 11 $
 * $Date: 14/12/02 5:47p $
 * @brief    M480 MCU USB Host HID driver
 *
 * @note
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "M480.h"

#include "usb.h"
#include "usbh_lib.h"
#include "usbh_hid.h"


/// @cond HIDDEN_SYMBOLS

static HID_DEV_T  g_hid_dev[CONFIG_HID_MAX_DEV];

static HID_DEV_T *g_hdev_list = NULL;

static HID_DEV_T *alloc_hid_device(void)
{
    int     i;

    for (i = 0; i < CONFIG_HID_MAX_DEV; i++) {
        if (g_hid_dev[i].udev == NULL) {
            memset((char *)&g_hid_dev[i], 0, sizeof(HID_DEV_T));
            return &g_hid_dev[i];
        }
    }
    return NULL;
}

void  free_hid_device(HID_DEV_T *hid_dev)
{
    hid_dev->udev = NULL;
    memset((char *)hid_dev, 0, sizeof(HID_DEV_T));
}


static int  usbhid_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
    struct usb_device *udev;
    struct usb_host_interface *desc;
    struct usb_host_endpoint  *ep;
    HID_DEV_T   *hid, *p;
    int         i;

    desc = intf->cur_altsetting;
    udev = interface_to_usbdev(intf);

    HID_DBGMSG("usbhid_probe - device (vid=0x%x, pid=0x%x), interface %d.\n",
               udev->descriptor.idVendor, udev->descriptor.idProduct, desc->desc.bInterfaceNumber);

    /*
     * Try to find any interrupt endpoints
     */
    for (i = 0, ep = NULL; i < desc->desc.bNumEndpoints; i++) {
        /* is it an int endpoint? */
        if ((desc->endpoint[i].desc.bmAttributes &
                USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_INT) {
            ep =  &(desc->endpoint[i]);
            break;
        }
    }

    if (ep == NULL)
        return -ENODEV;   // Ignore this interface

    hid = alloc_hid_device();
    if (hid == NULL)
        return HID_RET_OUT_OF_MEMORY;

    hid->udev = udev;
    hid->idVendor  = udev->descriptor.idVendor;
    hid->idProduct = udev->descriptor.idProduct;
    hid->intf = intf;
    hid->ifnum = desc->desc.bInterfaceNumber;
    hid->bSubClassCode = desc->desc.bInterfaceSubClass;
    hid->bProtocolCode = desc->desc.bInterfaceProtocol;
    hid->next = NULL;

    /*
     *  Chaining newly found HID device to end of HID device list.
     */
    if (g_hdev_list == NULL)
        g_hdev_list = hid;
    else {
        for (p = g_hdev_list; p->next != NULL; p = p->next)
            ;
        p->next = hid;
    }

    HID_DBGMSG("usbhid_probe OK.\n");

    return 0;
}


static void  hid_disconnect(struct usb_interface *intf)
{
    struct usb_device *udev;
    struct usb_host_interface *desc;
    HID_DEV_T   *hid_dev, *p;
    int    i, j;

    desc = intf->cur_altsetting;
    udev = interface_to_usbdev(intf);

    HID_DBGMSG("hid_disconnect - device (vid=0x%x, pid=0x%x), interface %d.\n",
               udev->descriptor.idVendor, udev->descriptor.idProduct, desc->desc.bInterfaceNumber);

    for (i = 0; i < CONFIG_HID_MAX_DEV; i++) {
        if (g_hid_dev[i].udev == udev) {
            hid_dev = &g_hid_dev[i];

            /*
             *  Unlink all URB and free transfer buffer
             */
            for (j = 0; j < 16; j++) {
                if (hid_dev->urb_in[j] != NULL) {
                    usb_unlink_urb(hid_dev->urb_in[j]);
                    if (hid_dev->urb_in[j]->transfer_buffer)
                        USB_free(hid_dev->urb_in[j]->transfer_buffer);
                    usb_free_urb(hid_dev->urb_in[j]);
                }

                if (hid_dev->urb_out[j] != NULL) {
                    usb_unlink_urb(hid_dev->urb_out[j]);
                    usb_free_urb(hid_dev->urb_out[j]);
                }
            }

            /*
             *  Remove this HID device from HID device list.
             */
            if (hid_dev == g_hdev_list)
                g_hdev_list = g_hdev_list->next;
            else {
                for (p = g_hdev_list; p != NULL; p = p->next) {
                    if (p->next == hid_dev) {
                        p->next = hid_dev->next;
                        break;
                    }
                }
            }
            free_hid_device(hid_dev);
        }
    }
}


#define USB_INTERFACE_CLASS_HID         3

static struct usb_device_id  hid_id_table[] = {
    {
        USB_DEVICE_ID_MATCH_INT_CLASS,     /* match_flags */
        0, 0, 0, 0, 0, 0, 0,
        USB_INTERFACE_CLASS_HID,           /* bInterfaceClass */
        0, 0, 0
    },
    { 0,0,0,0,0,0,0,0,0,0,0,0 }                     /* Terminating entry */
};

static struct usb_driver  hid_driver = {
    "hid",
    usbhid_probe,
    hid_disconnect,
    NULL,                       /* suspend */
    NULL,                       /* resume */
    NULL,                       /* reset_resume */
    NULL,                       /* pre_reset */
    NULL,                       /* post_reset */
    hid_id_table
};


/// @endcond /* HIDDEN_SYMBOLS */


/**
  * @brief    Initialize USB Host HID driver.
  * @return   None
  */
void usbh_hid_init(void)
{
    memset((char *)&g_hid_dev[0], 0, sizeof(g_hid_dev));
    g_hdev_list = NULL;
    usb_register_driver(&hid_driver, "hid driver");
}


/**
 *  @brief   Get a list of currently connected USB Hid devices.
 *  @return  List of HID devices.
 *  @retval  NULL       There's no HID device found.
 *  @retval  Otherwise  A list of connected HID devices.
 *
 *  The HID devices are chained by the "next" member of HID_DEV_T.
 */
HID_DEV_T * usbh_hid_get_device_list(void)
{
    return g_hdev_list;
}


/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/

