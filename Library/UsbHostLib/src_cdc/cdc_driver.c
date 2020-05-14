/**************************************************************************//**
 * @file     cdc_driver.c
 * @version  V1.00
 * @brief    M480 MCU USB Host CDC driver
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

extern int  cdc_config_parser(CDC_DEV_T *cdev);

static CDC_DEV_T *g_cdev_list = NULL;

static CDC_DEV_T *alloc_cdc_device(void)
{
    CDC_DEV_T  *cdev;

    cdev = (CDC_DEV_T *)usbh_alloc_mem(sizeof(CDC_DEV_T));
    if (cdev == NULL)
        return NULL;

    memset((char *)cdev, 0, sizeof(CDC_DEV_T));
    cdev->ifnum_data = -1;
    return cdev;
}

void  free_cdc_device(CDC_DEV_T *cdev)
{
    usbh_free_mem(cdev, sizeof(CDC_DEV_T));
}

static void add_new_cdc_device(CDC_DEV_T *cdev)
{
    if (g_cdev_list == NULL)
    {
        cdev->next = NULL;
        g_cdev_list = cdev;
    }
    else
    {
        cdev->next = g_cdev_list;
        g_cdev_list = cdev;
    }
}

static void remove_cdc_device(CDC_DEV_T *cdev)
{
    CDC_DEV_T  *p;

    if (g_cdev_list == cdev)
    {
        g_cdev_list = g_cdev_list->next;
        return;
    }

    p = g_cdev_list;
    while (p != NULL)
    {
        if (p->next == cdev)
        {
            p->next = cdev->next;
            return;
        }
        p = p->next;
    }
    CDC_DBGMSG("Warning! remove_cdc_device 0x%x not found!\n", (int)cdev);
}

/*
 *  Try to find the companion CDC interface of a DATA interface.
 */
static CDC_DEV_T * find_cdc_com_iface(IFACE_T *iface_data)
{
    CDC_DEV_T  *p;

    p = g_cdev_list;
    while (p != NULL)
    {
        if (p->ifnum_data == iface_data->if_num)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

/*
 *  Try to find any temporary CDC device holder of data interface
 */
static CDC_DEV_T * find_cdc_data_iface(int ifnum)
{
    CDC_DEV_T  *p;

    p = g_cdev_list;
    while (p != NULL)
    {
        if ((p->iface_cdc == NULL) && (p->iface_data != NULL) &&
                (p->ifnum_data == ifnum))
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

static int  cdc_probe(IFACE_T *iface)
{
    UDEV_T       *udev = iface->udev;
    ALT_IFACE_T  *aif = iface->aif;
    DESC_IF_T    *ifd;
    CDC_DEV_T    *cdev, *d;
    int          ret;

    ifd = aif->ifd;

    /* Is this interface CDC class? */
    if ((ifd->bInterfaceClass != USB_CLASS_COMM) && (ifd->bInterfaceClass != USB_CLASS_DATA))
        return USBH_ERR_NOT_MATCHED;

    CDC_DBGMSG("cdc_probe %s - device (vid=0x%x, pid=0x%x), interface %d.\n",
               (ifd->bInterfaceClass == USB_CLASS_COMM) ? "COMM" : "DATA",
               udev->descriptor.idVendor, udev->descriptor.idProduct, ifd->bInterfaceNumber);

    if (ifd->bInterfaceClass == USB_CLASS_DATA)
    {
        cdev = find_cdc_com_iface(iface);      /* If this CDC device may have been created in the previous inetrface probing? */
        if (cdev == NULL)
        {
            CDC_DBGMSG("Warning! CDC device DTAT interface %d cannot find COMM interface!\n", iface->if_num);

            /* create a temporary CDC device holder */
            cdev = alloc_cdc_device();
            if (cdev == NULL)
                return USBH_ERR_NOT_FOUND;

            cdev->udev = udev;
            add_new_cdc_device(cdev);
            cdev->ifnum_data = iface->if_num;
        }
        cdev->iface_data = iface;
        iface->context = cdev;
        return 0;
    }

    /*------- Is CDC COMM interface ----------*/

    cdev = alloc_cdc_device();
    if (cdev == NULL)
        return USBH_ERR_NOT_FOUND;

    cdev->udev = udev;
    cdev->iface_cdc = iface;
    iface->context = (void *)cdev;

    ret = cdc_config_parser(cdev);
    if (ret != 0)
    {
        CDC_DBGMSG("Parsing CDC desceiptor failed! 0x%x\n", ret);
        free_cdc_device(cdev);
        return -1;
    }

    add_new_cdc_device(cdev);

    /* find temporary CDC device holder of data interface */
    d = find_cdc_data_iface(cdev->ifnum_data);      /* If this CDC device may have been created in the previous inetrface probing? */
    if (d)
    {
        cdev->iface_data = d->iface_data;
        cdev->iface_data->context = cdev;
        remove_cdc_device(d);
        free_cdc_device(d);
    }

    return 0;
}

static void  cdc_disconnect(IFACE_T *iface)
{
    IFACE_T     *if_cdc, *if_data;
    CDC_DEV_T   *cdev;
    int         i;

    CDC_DBGMSG("CDC device interface %d disconnected!\n", iface->if_num);

    cdev = (CDC_DEV_T *)(iface->context);

    if (cdev == NULL)
        return;              /* should have been disconnected. */

    if_cdc = cdev->iface_cdc;
    if_data = cdev->iface_data;

    /*
     *  Quit transfers of all endpoints of COMM and DATA interface.
     */
    if (if_cdc)
    {
        for (i = 0; i < if_cdc->aif->ifd->bNumEndpoints; i++)
        {
            if_cdc->udev->hc_driver->quit_xfer(NULL, &(if_cdc->aif->ep[i]));
        }
    }

    if (if_data)
    {
        for (i = 0; i < if_data->aif->ifd->bNumEndpoints; i++)
        {
            if_data->udev->hc_driver->quit_xfer(NULL, &(if_data->aif->ep[i]));
        }
    }

    if (cdev->utr_sts)
    {
        usbh_quit_utr(cdev->utr_sts);             /* Quit the UTR                               */
        free_utr(cdev->utr_sts);
        cdev->utr_sts = NULL;
    }
    if (cdev->utr_rx)
    {
        usbh_quit_utr(cdev->utr_rx);             /* Quit the UTR                               */
        free_utr(cdev->utr_rx);
        cdev->utr_rx = NULL;
    }

    if_cdc->context = NULL;
    if_data->context = NULL;

    remove_cdc_device(cdev);
    free_cdc_device(cdev);
}


static UDEV_DRV_T  cdc_driver =
{
    cdc_probe,
    cdc_disconnect,
    NULL,
    NULL,
};


/// @endcond /* HIDDEN_SYMBOLS */


/**
  * @brief    Init USB Host CDC driver.
  * @return   None
  */
void usbh_cdc_init(void)
{
    g_cdev_list = NULL;
    usbh_register_driver(&cdc_driver);
}


/**
 *  @brief   Get a list of currently connected USB Hid devices.
 *  @return  List of CDC devices.
 *  @retval  NULL       There's no CDC device found.
 *  @retval  Otherwise  A list of connected CDC devices.
 *
 *  The CDC devices are chained by the "next" member of CDC_DEV_T.
 */
CDC_DEV_T * usbh_cdc_get_device_list(void)
{
    return g_cdev_list;
}


/*** (C) COPYRIGHT 2018~2019 Nuvoton Technology Corp. ***/

