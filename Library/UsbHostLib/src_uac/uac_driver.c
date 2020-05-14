/**************************************************************************//**
 * @file     uac_driver.c
 * @version  V1.00
 * @brief    M480 MCU USB Host Audio Class driver
 *
 * @note     Support mono and stereo audio input and output.
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

/// @cond HIDDEN_SYMBOLS

static UAC_DEV_T   g_uac_dev[CONFIG_UAC_MAX_DEV];

static UAC_DEV_T   *g_uac_list = NULL;


static UAC_DEV_T *alloc_uac_device(void)
{
    int     i;

    for (i = 0; i < CONFIG_UAC_MAX_DEV; i++)
    {
        if (g_uac_dev[i].udev == NULL)
        {
            memset((char *)&g_uac_dev[i], 0, sizeof(UAC_DEV_T));
            return &g_uac_dev[i];
        }
    }
    return NULL;
}

static void  free_uac_device(UAC_DEV_T *uac)
{
    uac->udev = NULL;
}

UAC_DEV_T *find_uac_device(UDEV_T *udev)
{
    int     i;

    if (udev == NULL)
        return NULL;

    for (i = 0; i < CONFIG_UAC_MAX_DEV; i++)
    {
        if (g_uac_dev[i].udev == udev)
        {
            return &g_uac_dev[i];
        }
    }
    return NULL;
}


static int  uac_probe(IFACE_T *iface)
{
    UDEV_T       *udev = iface->udev;
    ALT_IFACE_T  *aif = iface->aif;
    DESC_IF_T    *ifd;
    UAC_DEV_T    *uac, *p;
    uint8_t      bAlternateSetting;
    int          ret;

    ifd = aif->ifd;

    /* Is this interface Audio class? */
    if (ifd->bInterfaceClass != USB_CLASS_AUDIO)
        return USBH_ERR_NOT_MATCHED;

    if ((ifd->bInterfaceSubClass != SUBCLS_AUDIOCONTROL) &&
            (ifd->bInterfaceSubClass != SUBCLS_AUDIOSTREAMING))
    {
        UAC_ERRMSG("Audio class interface, but sub-class %x not supported!\n", ifd->bInterfaceSubClass);
        return USBH_ERR_NOT_MATCHED;
    }

    UAC_DBGMSG("\nuac_probe - device (vid=0x%x, pid=0x%x), interface %d, type: %s\n",
               udev->descriptor.idVendor, udev->descriptor.idProduct, iface->if_num, (ifd->bInterfaceSubClass == SUBCLS_AUDIOCONTROL) ? "CONTROL" : "STREAM");

    uac = find_uac_device(udev);
    if (uac == NULL)
    {
        /* UAC device should has not been created in the previous probe of the other interface    */
        /* return 0 to make USB core adding this interface to device working interface list.  */
        uac = alloc_uac_device();
        if (uac == NULL)
            return UAC_RET_OUT_OF_MEMORY;

        uac->udev = udev;
        uac->state = UAC_STATE_CONNECTING;

        /*  Add newly found Audio Class device to end of Audio Class device list.
        */
        if (g_uac_list == NULL)
        {
            g_uac_list = uac;
        }
        else
        {
            for (p = g_uac_list; p->next != NULL; p = p->next)
                ;
            p->next = uac;
        }
    }

    iface->context = (void *)uac;

    if (ifd->bInterfaceSubClass == SUBCLS_AUDIOSTREAMING)
    {
        if ((usbh_uac_find_max_alt(iface, EP_ADDR_DIR_IN, EP_ATTR_TT_ISO, &bAlternateSetting) == 0) ||
                (usbh_uac_find_max_alt(iface, EP_ADDR_DIR_OUT, EP_ATTR_TT_ISO, &bAlternateSetting) == 0))
        {
            ret = usbh_set_interface(iface, bAlternateSetting);
            if (ret < 0)
            {
                UAC_ERRMSG("Failed to set interface %d, %d! (%d)\n", iface->if_num, bAlternateSetting, ret);
                return UAC_RET_IO_ERR;
            }
        }
        else
        {
            UAC_ERRMSG("Cannot find audio stream endpoints!\n");
            return UAC_RET_DEV_NOT_FOUND;
        }

        ret = uac_parse_streaming_interface(uac, iface, bAlternateSetting);
        if (ret < 0)
            return ret;
    }
    else if (ifd->bInterfaceSubClass == SUBCLS_AUDIOCONTROL)
    {
        ret = uac_parse_control_interface(uac, iface);
        if (ret < 0)
            return ret;
    }

    UAC_DBGMSG("UAC device 0x%x ==>\n", (int)uac);
    UAC_DBGMSG("    CONTROL IFACE:    0x%x\n", (int)uac->acif.iface);
    UAC_DBGMSG("    STREAM IN IFACE:  0x%x\n", (int)uac->asif_in.iface);
    UAC_DBGMSG("    STREAM OUT IFACE: 0x%x\n", (int)uac->asif_out.iface);

    return ret;
}

static void  uac_disconnect(IFACE_T *iface)
{
    UAC_DEV_T    *uac, *p;
    //ALT_IFACE_T  *aif = iface->aif;
    int          i;

    uac = (UAC_DEV_T *)iface->context;

    uac->state = UAC_STATE_DISCONNECTING;

    UAC_DBGMSG("uac_disconnect - device (vid=0x%x, pid=0x%x), interface %d removed.\n",
               uac->udev->descriptor.idVendor, uac->udev->descriptor.idProduct, iface->if_num);

    /*
     *  remove it from UAC device list
     */
    for (i = 0; i < CONFIG_UAC_MAX_DEV; i++)
    {
        if (g_uac_dev[i].udev == iface->udev)
        {
            uac = &g_uac_dev[i];

            if (uac->acif.iface == iface)
            {
                uac->acif.iface = NULL;
            }
            else if (uac->asif_in.iface == iface)
            {
                usbh_uac_stop_audio_in(uac);
                uac->asif_in.iface = NULL;
            }
            else if (uac->asif_out.iface == iface)
            {
                usbh_uac_stop_audio_out(uac);
                uac->asif_out.iface = NULL;
            }

            if ((uac->acif.iface != NULL) || (uac->asif_in.iface != NULL) || (uac->asif_out.iface != NULL))
                continue;

            /*
             *  All interface of UAC device are all disconnected. Remove it from UAC device list.
             */

            if (uac == g_uac_list)
            {
                g_uac_list = g_uac_list->next;
            }
            else
            {
                for (p = g_uac_list; p != NULL; p = p->next)
                {
                    if (p->next == uac)
                    {
                        p->next = uac->next;
                        break;
                    }
                }
            }
            UAC_DBGMSG("uac_disconnect - device (vid=0x%x, pid=0x%x), UAC device removed.\n",
                       uac->udev->descriptor.idVendor, uac->udev->descriptor.idProduct);
            free_uac_device(uac);
        }
    }
}

UDEV_DRV_T  uac_driver =
{
    uac_probe,
    uac_disconnect,
    NULL,                       /* suspend */
    NULL,                       /* resume */
};


/// @endcond HIDDEN_SYMBOLS

/**
  * @brief    Initialize USB Audio Class driver.
  * @return   None
  */
void usbh_uac_init(void)
{
    memset((char *)&g_uac_dev[0], 0, sizeof(g_uac_dev));
    g_uac_list = NULL;
    usbh_register_driver(&uac_driver);
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
    return g_uac_list;
}


/*@}*/ /* end of group USBH_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group USBH_Library */

/*@}*/ /* end of group LIBRARY */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/

