/**************************************************************************//**
 * @file     hid_driver.c
 * @version  V1.00
 * @brief    M480 MCU USB Host HID driver
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "NuMicro.h"

#include "usb.h"
#include "usbh_lib.h"
#include "usbh_hid.h"


/// @cond HIDDEN_SYMBOLS

extern int hid_parse_report_descriptor(HID_DEV_T *hdev, IFACE_T *iface);

static HID_DEV_T  g_hid_dev[CONFIG_HID_MAX_DEV];

static HID_DEV_T *g_hdev_list = NULL;

static HID_DEV_T *alloc_hid_device(void)
{
    int     i;

    for (i = 0; i < CONFIG_HID_MAX_DEV; i++)
    {
        if (g_hid_dev[i].iface == NULL)
        {
            memset((char *)&g_hid_dev[i], 0, sizeof(HID_DEV_T));
            g_hid_dev[i].uid = get_ticks();
            return &g_hid_dev[i];
        }
    }
    return NULL;
}

void  free_hid_device(HID_DEV_T *hid_dev)
{
    hid_dev->iface = NULL;
    memset((char *)hid_dev, 0, sizeof(HID_DEV_T));
}


static int hid_probe(IFACE_T *iface)
{
    UDEV_T       *udev = iface->udev;
    ALT_IFACE_T  *aif = iface->aif;
    DESC_IF_T    *ifd;
    EP_INFO_T    *ep;
    HID_DEV_T    *hdev, *p;
    int          i;

    ifd = aif->ifd;

    /* Is this interface HID class? */
    if (ifd->bInterfaceClass != USB_CLASS_HID)
        return USBH_ERR_NOT_MATCHED;

    HID_DBGMSG("hid_probe - device (vid=0x%x, pid=0x%x), interface %d, subclass 0x%x, protocol 0x%x.\n",
               udev->descriptor.idVendor, udev->descriptor.idProduct, ifd->bInterfaceNumber,
               ifd->bInterfaceSubClass, ifd->bInterfaceProtocol);

    /*
     *  Try to find any interrupt endpoints
     */
    for (i = 0; i < aif->ifd->bNumEndpoints; i++)
    {
        if ((aif->ep[i].bmAttributes & EP_ATTR_TT_MASK) == EP_ATTR_TT_INT)
        {
            ep = &aif->ep[i];
            break;
        }
    }

    if (ep == NULL)
        return USBH_ERR_NOT_MATCHED;   // No endpoints, Ignore this interface

    hdev = alloc_hid_device();
    if (hdev == NULL)
        return HID_RET_OUT_OF_MEMORY;

    hdev->iface = iface;
    hdev->idVendor  = udev->descriptor.idVendor;
    hdev->idProduct = udev->descriptor.idProduct;
    hdev->bSubClassCode = ifd->bInterfaceSubClass;
    hdev->bProtocolCode = ifd->bInterfaceProtocol;
    hdev->next = NULL;
    iface->context = (void *)hdev;

    hid_parse_report_descriptor(hdev, iface);

    /*
     *  Chaining newly found HID device to end of HID device list.
     */
    if (g_hdev_list == NULL)
        g_hdev_list = hdev;
    else
    {
        for (p = g_hdev_list; p->next != NULL; p = p->next)
            ;
        p->next = hdev;
    }

    HID_DBGMSG("usbhid_probe OK. hdev=0x%x\n", (int)hdev);

    return 0;
}


static void  hid_disconnect(IFACE_T *iface)
{
    HID_DEV_T   *hdev, *p;
    UTR_T       *utr;
    RP_INFO_T   *rp, *next_rp;
    int         i;

    hdev = (HID_DEV_T *)(iface->context);

    for (i = 0; i < iface->aif->ifd->bNumEndpoints; i++)
    {
        iface->udev->hc_driver->quit_xfer(NULL, &(iface->aif->ep[i]));
    }

    /*
     *  Abort all UTR of this HID device (interface)
     */
    for (i = 0; i < CONFIG_HID_DEV_MAX_PIPE; i++)
    {
        utr = hdev->utr_list[i];
        if (utr != NULL)
        {
            usbh_quit_utr(utr);             /* Quit the UTR                               */
            usbh_free_mem(utr->buff, utr->ep->wMaxPacketSize);
            free_utr(utr);
        }
    }

    if (hdev->rpd.utr_led != NULL)
    {
        usbh_quit_utr(hdev->rpd.utr_led);   /* Quit the UTR                               */
        free_utr(hdev->rpd.utr_led);
    }

    if (hdev->rpd.report != NULL)
    {
        for (rp = hdev->rpd.report; rp != NULL; )
        {
            next_rp = rp->next;
            usbh_free_mem(rp, sizeof(RP_INFO_T));
            rp = next_rp;
        };
    }

    /*
     *  remove it from HID device list
     */
    for (i = 0; i < CONFIG_HID_MAX_DEV; i++)
    {
        if (g_hid_dev[i].iface == iface)
        {
            hdev = &g_hid_dev[i];

            if (hdev == g_hdev_list)
            {
                g_hdev_list = g_hdev_list->next;
            }
            else
            {
                for (p = g_hdev_list; p != NULL; p = p->next)
                {
                    if (p->next == hdev)
                    {
                        p->next = hdev->next;
                        break;
                    }
                }
            }
            HID_DBGMSG("hid_disconnect - device (vid=0x%x, pid=0x%x), interface %d.\n",
                       hdev->idVendor, hdev->idProduct, iface->if_num);
            free_hid_device(hdev);
        }
    }
}


UDEV_DRV_T  hid_driver =
{
    hid_probe,
    hid_disconnect,
    NULL,                       /* suspend */
    NULL,                       /* resume */
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
    usbh_register_driver(&hid_driver);
}


/**
 *  @brief   Get a list of currently connected USB Hid devices.
 *  @return  A list HID_DEV_T pointer reference to connected HID devices.
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

