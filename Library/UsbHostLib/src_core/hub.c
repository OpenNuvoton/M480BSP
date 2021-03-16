/**************************************************************************//**
 * @file     hub.c
 * @version  V1.10
 * @brief   USB Host library hub class driver.
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
#include "hub.h"


/// @cond HIDDEN_SYMBOLS


#define HUB_DBGMSG     printf
//#define HUB_DBGMSG(...)

static HUB_DEV_T  g_hub_dev[MAX_HUB_DEVICE];

static int do_port_reset(HUB_DEV_T *hub, int port);

static HUB_DEV_T *alloc_hub_device(void)
{
    int     i;
    for (i = 0; i < MAX_HUB_DEVICE; i++)
    {
        if (g_hub_dev[i].iface == NULL)
        {
            memset((char *)&g_hub_dev[i], 0, sizeof(HUB_DEV_T));
            g_hub_dev[i].port_reset = do_port_reset;
            return &g_hub_dev[i];
        }
    }
    return NULL;
}

static void  free_hub_device(HUB_DEV_T *hub_dev)
{
    int     i;
    for (i = 0; i < MAX_HUB_DEVICE; i++)
    {
        if (g_hub_dev[i].iface == hub_dev->iface)
        {
            memset((char *)&g_hub_dev[i], 0, sizeof(HUB_DEV_T));
        }
    }
}

static HUB_DEV_T * find_hub_device(IFACE_T *iface)
{
    int     i;
    for (i = 0; i < MAX_HUB_DEVICE; i++)
    {
        if (g_hub_dev[i].iface == iface)
        {
            return &g_hub_dev[i];
        }
    }
    return NULL;
}

#if 0
/*
 *  Hub Class-specific Request -  "Set Hub Feature"
 */
static int  set_hub_feature(HUB_DEV_T *hub, int feature_selector, int port)
{
    UDEV_T     *udev = hub->iface->udev;
    uint32_t   read_len;

    return usbh_ctrl_xfer(udev, REQ_TYPE_OUT | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_DEV,
                          USB_REQ_SET_FEATURE, feature_selector, 0, 0,
                          NULL, &read_len, 200);
}
#endif

/*
 *  Hub Class-specific Request -  "Clear Hub Feature"
 */
static int  clear_hub_feature(HUB_DEV_T *hub, int feature_selector)
{
    UDEV_T     *udev = hub->iface->udev;
    uint32_t   read_len;

    return usbh_ctrl_xfer(udev, REQ_TYPE_OUT | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_DEV,
                          USB_REQ_CLEAR_FEATURE, feature_selector, 0, 0,
                          NULL, &read_len, 200);
}

/*
 *  Hub Class-specific Request -  "Get Hub Status"
 */
static int  get_hub_status(HUB_DEV_T *hub, uint16_t *wHubStatus, uint16_t *wHubChange)
{
    UDEV_T     *udev = hub->iface->udev;
    uint8_t    buff[4];
    uint32_t   read_len;
    int        ret;

    ret =  usbh_ctrl_xfer(udev, REQ_TYPE_IN | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_DEV,
                          USB_REQ_GET_STATUS, 0,  0, 4,
                          buff, &read_len, 200);
    if (ret < 0)
        return ret;

    if (read_len != 4)
        return USBH_ERR_DATA_UNDERRUN;

    *wHubStatus = (buff[1] << 8) | buff[0];
    *wHubChange = (buff[3] << 8) | buff[2];
    return 0;
}

/*
 *  Hub Class-specific Request -  "Set Port Feature"
 */
static int  set_port_feature(HUB_DEV_T *hub, int feature_selector, int port)
{
    UDEV_T     *udev = hub->iface->udev;
    uint32_t   read_len;

    return usbh_ctrl_xfer(udev, REQ_TYPE_OUT | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_OTHER,
                          USB_REQ_SET_FEATURE, feature_selector, port, 0,
                          NULL, &read_len, 200);
}

/*
 *  Hub Class-specific Request -  "Clear Port Feature"
 */
static int  clear_port_feature(HUB_DEV_T *hub, int feature_selector, int port)
{
    UDEV_T     *udev = hub->iface->udev;
    uint32_t   read_len;

    return usbh_ctrl_xfer(udev, REQ_TYPE_OUT | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_OTHER,
                          USB_REQ_CLEAR_FEATURE, feature_selector, port, 0,
                          NULL, &read_len, 200);
}

/*
 *  Hub Class-specific Request -  "Get Port Status"
 */
static int  get_port_status(HUB_DEV_T *hub, int port, uint16_t *wPortStatus, uint16_t *wPortChange)
{
    UDEV_T     *udev = hub->iface->udev;
    uint8_t    buff[4];
    uint32_t   read_len;
    int        ret;

    ret =  usbh_ctrl_xfer(udev, REQ_TYPE_IN | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_OTHER,
                          USB_REQ_GET_STATUS, 0, port, 4,
                          buff, &read_len, 200);
    if (ret < 0)
        return ret;

    if (read_len != 4)
    {
        USB_error("HUB [%s] get_port_status read_len!=4. (%d).\n", hub->pos_id, read_len);
        return USBH_ERR_DATA_UNDERRUN;
    }

    *wPortStatus = (buff[1] << 8) | buff[0];
    *wPortChange = (buff[3] << 8) | buff[2];
    return 0;
}

static void hub_status_irq(UTR_T *utr)
{
    HUB_DEV_T   *hub;
    int         i;

    // HUB_DBGMSG("hub_read_irq - %d\n", utr->xfer_len);

    hub = (HUB_DEV_T *)utr->context;

    if (utr->status != 0)
    {
        USB_error("hub_status_irq - has error: 0x%x\n", utr->status);
        return;
    }

    if (utr->xfer_len)
    {
        for (i = 0; i < utr->xfer_len; i++)
        {
            hub->sc_bitmap |= (utr->buff[i] << (i * 8));
        }
        // HUB_DBGMSG("hub_status_irq - status bitmap: 0x%x\n", hub->sc_bitmap);
    }
}

int hub_probe(IFACE_T *iface)
{
    UDEV_T      *udev = iface->udev;
    ALT_IFACE_T *aif = iface->aif;
    EP_INFO_T   *ep;
    HUB_DEV_T   *hub;
    UTR_T       *utr;
    uint32_t    read_len;
    int         i, ret;
    DESC_HUB_T  desc_hub;
    char        str[2] = "0";

    /* Is this interface HID class? */
    if (aif->ifd->bInterfaceClass != USB_CLASS_HUB)
        return USBH_ERR_NOT_MATCHED;

    /*
     *  Try to find an interrupt endpoint
     */
    for (i = 0; i < aif->ifd->bNumEndpoints; i++)
    {
        if (((aif->ep[i].bmAttributes & EP_ATTR_TT_MASK) == EP_ATTR_TT_INT) &&
                ((aif->ep[i].bEndpointAddress & EP_ADDR_DIR_MASK) == EP_ADDR_DIR_IN))
        {
            ep = &aif->ep[i];
            break;
        }
    }

    if (ep == NULL)
        return USBH_ERR_NOT_MATCHED;        /* no INT-in endpoints, Ignore this interface */

    hub = alloc_hub_device();               /* allocate hub device                        */
    if (hub == NULL)
        return USBH_ERR_MEMORY_OUT;         /* out of memory                              */

    hub->iface = iface;                     /* assign interface device pointer            */
    iface->context = (void *)hub;

    str[0] += udev->port_num;
    if (udev->parent == NULL)               /* is connected under the root hub?           */
        strcpy(hub->pos_id, str);           /* create hub position identifier string      */
    else
    {
        strcpy(hub->pos_id, udev->parent->pos_id);
        strcat(hub->pos_id, str);
    }

    HUB_DBGMSG("hub found is:[%s] - device (vid=0x%x, pid=0x%x), interface %d.\n", hub->pos_id,
               udev->descriptor.idVendor, udev->descriptor.idProduct, iface->if_num);

    /*------------------------------------------------------------------------------------*/
    /* Get Hub descriptor and parse to get information                                    */
    /*------------------------------------------------------------------------------------*/
    ret = usbh_ctrl_xfer(udev, REQ_TYPE_IN | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_DEV,
                         USB_REQ_GET_DESCRIPTOR,
                         ((USB_DT_CLASS | 0x9) << 8),  /* Hub descriptor type: 29H   */
                         0, sizeof(desc_hub),
                         (uint8_t *)&desc_hub, &read_len, 200);
    if (ret < 0)
    {
        USB_error("Failed to get hub descriptor!\n");
    }
    else
    {
        hub->bNbrPorts = desc_hub.bNbrPorts;
        hub->bPwrOn2PwrGood = desc_hub.bPwrOn2PwrGood * 2;
        HUB_DBGMSG("Hub has %d ports, power-to-power-good time is %d ms.\n", hub->bNbrPorts, hub->bPwrOn2PwrGood);
    }

    /*------------------------------------------------------------------------------------*/
    /* Enable all hub port power                                                          */
    /*------------------------------------------------------------------------------------*/
    for (i = 1; i <= hub->bNbrPorts; i++)
    {
        ret = set_port_feature(hub, FS_PORT_POWER, i);
        if (ret == 0)
            HUB_DBGMSG("Hub [%s] port %d power enabled.\n", hub->pos_id, i);
        else
            HUB_DBGMSG("Hub [%s] port %d power enabling failed!\n", hub->pos_id, i);
    }

    delay_us(hub->bPwrOn2PwrGood * 1000 + 100000);   /* delay to wait hub power ready     */

    utr = alloc_utr(udev);                  /* allocate an UTR for INT-in transfer        */
    if (utr == NULL)
    {
        free_hub_device(hub);
        return USBH_ERR_MEMORY_OUT;         /* out of memory                              */
    }
    hub->utr = utr;
    utr->context = hub;                     /* hook backward link to hub device           */
    utr->ep = ep;                           /* the INT-in endpoint found earlier          */
    utr->buff = hub->buff;                  /* INT-in data receiving buffer               */
    utr->data_len = HUB_STATUS_MAX_BYTE;    /* maximum length of data of INT-in status    */
    utr->xfer_len = 0;
    utr->func = hub_status_irq;             /* interrupt in transfer done callback        */

    ret = usbh_int_xfer(utr);               /* submit the INT-in transfer                 */
    if (ret < 0)
    {
        HUB_DBGMSG("Error - failed to submit interrupt read request (%d)", ret);
        free_utr(utr);
        free_hub_device(hub);
        return USBH_ERR_TRANSFER;
    }
    HUB_DBGMSG("hub_probe OK.\n");
    return 0;
}

void hub_disconnect(IFACE_T *iface)
{
    HUB_DEV_T   *hub;
    UDEV_T      *udev;
    int         port;

    hub = find_hub_device(iface);           /* find the hub device by inface device       */
    if (hub == NULL)
    {
        HUB_DBGMSG("hub_disconnect - hub not found!\n");
        return;
    }

    /*
     *  disconnect all device under this hub
     */
    for (port = 1; port <= hub->bNbrPorts; port++)
    {
        udev = usbh_find_device(hub->pos_id, port);
        if (udev != NULL)
        {
            HUB_DBGMSG("Disconnect HUB [%s] port %d device 0x%x:0x%x\n", hub->pos_id, port, udev->descriptor.idVendor, udev->descriptor.idProduct);
            disconnect_device(udev);
        }
    }

    if (hub->utr)
    {
        usbh_quit_utr(hub->utr);
        free_utr(hub->utr);
    }

    HUB_DBGMSG("Disconnect HUB [%s].\n", hub->pos_id);
    free_hub_device(hub);
}


UDEV_DRV_T  hub_driver =
{
    hub_probe,
    hub_disconnect,
    NULL,
    NULL
};


static int  hub_status_change(HUB_DEV_T *hub)
{
    uint16_t    wHubStatus, wHubChange;
    int         ret;

    HUB_DBGMSG("Hub [%s] hub status change 0x%x.\n", hub->pos_id, hub->sc_bitmap);

    ret = get_hub_status(hub, &wHubStatus, &wHubChange);
    if (ret < 0)
    {
        USB_error("Failed to get Hub [%s] status! (%d)\n", hub->pos_id, ret);
        return ret;
    }

    printf("Hub [%s] status: 0x%x, change: 0x%x\n", hub->pos_id, wHubStatus, wHubChange);

    if (wHubChange & HUB_C_LOCAL_POWER)     /* has local power change?                    */
    {
        ret = clear_hub_feature(hub, FS_C_HUB_LOCAL_POWER); /* clear local power change   */
        if (ret < 0)
            return ret;                     /* class command failed                       */
    }

    if (wHubChange & HUB_C_OVERCURRENT)     /* has over-current change?                   */
    {
        ret = clear_hub_feature(hub, FS_C_HUB_OVER_CURRENT); /* clear change              */
        if (ret < 0)
            return ret;                     /* class command failed                       */
    }

    return 0;
}

static int do_port_reset(HUB_DEV_T *hub, int port)
{
    int         retry;
    int         reset_time;
    uint32_t    t0;
    uint16_t    wPortStatus, wPortChange;
    int         ret;

    reset_time = PORT_RESET_TIME_MS;        /* initial reset time                         */

    for (retry = 0; retry < PORT_RESET_RETRY; retry++)
    {
        ret = set_port_feature(hub, FS_PORT_RESET, port);  /* submit a port reset         */
        if (ret < 0)
            return ret;                     /* class command failed                       */

        t0 = get_ticks();                   /* get start time                             */
        while (get_ticks() - t0 < (reset_time/10)+1)    /* time-out?                      */
        {
            delay_us(5000);                 /* wait 5 ms                                  */

            ret = get_port_status(hub, port, &wPortStatus, &wPortChange);
            if (ret < 0)
            {
                USB_error("Failed to get Hub [%s] port %d status! (%d)\n", hub->pos_id, port, ret);
                return ret;
            }

            /*
             *  If device is disconnected or port enabled, we can stop port reset.
             */
            if (((wPortStatus & PORT_S_CONNECTION) == 0) ||
                    ((wPortStatus & (PORT_S_CONNECTION | PORT_S_ENABLE)) == (PORT_S_CONNECTION | PORT_S_ENABLE)))
            {
                clear_port_feature(hub, FS_C_PORT_ENABLE, port); /* clear port enable change */
                return USBH_OK;
            }
        }
        reset_time += PORT_RESET_RETRY_INC_MS;   /* increase reset time                   */
    }
    USB_debug("HUB [%s] port %d - port reset failed!\n", hub->pos_id, port);
    return USBH_ERR_PORT_RESET;
}

static int  port_connect_change(HUB_DEV_T *hub, int port, uint16_t wPortStatus)
{
    UDEV_T     *udev;
    uint16_t   wPortChange;
    int        ret;

    if (wPortStatus & PORT_S_CONNECTION)
    {
        /*--------------------------------------------------------------------------------*/
        /*  First of all, check if there's any previously connected device.               */
        /*--------------------------------------------------------------------------------*/
        udev = usbh_find_device(hub->pos_id, port);
        if (udev != NULL)
        {
            disconnect_device(udev);
        }

        /*
         * New device connected. Do a port reset first.
         */
        ret = do_port_reset(hub, port);
        if (ret < 0)
            return ret;

        ret = get_port_status(hub, port, &wPortStatus, &wPortChange);
        if (ret < 0)
        {
            USB_error("Failed to get Hub [%s] port %d status! (%d)\n", hub->pos_id, port, ret);
            return ret;
        }
        printf("Hub [%s] port %d, status: 0x%x, change: 0x%x\n", hub->pos_id, port, wPortStatus, wPortChange);

        /*
         *  Port reset success. Create and enumerate this device.
         */
        udev = alloc_device();
        if (udev == NULL)
            return USBH_ERR_MEMORY_OUT;     /* unlikely, out of memory                    */

        udev->parent = hub;
        udev->port_num = port;

        if (wPortStatus & PORT_S_HIGH_SPEED)
            udev->speed = SPEED_HIGH;
        else if (wPortStatus & PORT_S_LOW_SPEED)
            udev->speed = SPEED_LOW;
        else
            udev->speed = SPEED_FULL;

        udev->hc_driver = hub->iface->udev->hc_driver;

        ret = connect_device(udev);
        if (ret < 0)
        {
            USB_error("connect_device error! [%d]\n", ret);
            free_device(udev);
        }
    }
    else
    {
        /*
         *  Device disconnected
         */
        udev = usbh_find_device(hub->pos_id, port);
        if (udev != NULL)
        {
            disconnect_device(udev);
        }
    }
    return 0;
}

static int  port_status_change(HUB_DEV_T *hub, int port)
{
    uint16_t    wPortStatus, wPortChange;
    int         ret;

    ret = get_port_status(hub, port, &wPortStatus, &wPortChange);
    if (ret < 0)
    {
        USB_error("Failed to get Hub [%s] port %d status! (%d)\n", hub->pos_id, port, ret);
        return ret;
    }
    printf("Hub [%s] port %d, status: 0x%x, change: 0x%x\n", hub->pos_id, port, wPortStatus, wPortChange);

    if (wPortChange & PORT_C_CONNECTION)    /* have port connection change?               */
    {
        ret = clear_port_feature(hub, FS_C_PORT_CONNECTION, port); /* clear port change   */
        if (ret < 0)
            return ret;                     /* class command failed                       */

        port_connect_change(hub, port, wPortStatus);
    }

    if (wPortChange & PORT_C_ENABLE)        /* have port enable change?                   */
    {
        ret = clear_port_feature(hub, FS_C_PORT_ENABLE, port);     /* clear port change   */
        if (ret < 0)
            return ret;                     /* class command failed                       */
    }

    if (wPortChange & PORT_C_SUSPEND)       /* have port suspend change?                  */
    {
        ret = clear_port_feature(hub, FS_C_PORT_SUSPEND, port);    /* clear port change   */
        if (ret < 0)
            return ret;                     /* class command failed                       */
    }

    if (wPortChange & PORT_C_OVERCURRENT)   /* have port over-current change?             */
    {
        ret = clear_port_feature(hub, FS_C_PORT_OVER_CURRENT, port); /* clear port change */
        if (ret < 0)
            return ret;                     /* class command failed                       */
    }

    if (wPortChange & PORT_C_RESET)         /* have port reset change?                     */
    {
        ret = clear_port_feature(hub, FS_C_PORT_RESET, port);        /* clear port change */
        if (ret < 0)
            return ret;                     /* class command failed                       */
    }
    return 0;
}

static  volatile  uint8_t   _hub_polling_mutex = 0;

static int  hub_polling(void)
{
    HUB_DEV_T   *hub;
    UTR_T       *utr;
    int         i, ret, port, change = 0;

    if (_hub_polling_mutex)                 /* do nothing                                 */
        return 0;

    _hub_polling_mutex = 1;

    for (i = 0; i < MAX_HUB_DEVICE; i++)
    {
        if ((g_hub_dev[i].iface != NULL) && (g_hub_dev[i].sc_bitmap))
        {
            /*
             *  This hub device has status change
             */
            hub = &g_hub_dev[i];
            change = 1;

            // HUB_DBGMSG("HUB [%s] hub status change 0x%x.\n", hub->pos_id, hub->sc_bitmap);

            if (hub->sc_bitmap & 0x1)
                hub_status_change(hub);

            for (port = 1; port <= hub->bNbrPorts; port++)
            {
                if (hub->sc_bitmap & (1 << port))
                {
                    ret = port_status_change(hub, port);
                    if (ret < 0)
                        break;
                }
            }
            hub->sc_bitmap = 0;
            /* re-submit interrupt-in transfer */
            if (ret == 0)
            {
                utr = hub->utr;
                utr->xfer_len = 0;
                ret = usbh_int_xfer(utr);
                if (ret)
                {
                    USB_error("Failed to re-submit HUB [%s] interrupt-in request (%d)", hub->pos_id, ret);
                }
            }
        }
    }
    _hub_polling_mutex = 0;
    return change;
}


/**
  * @brief    Initialize USB Hub Class device driver.
  * @return   None
  */
void usbh_hub_init(void)
{
    memset((char *)&g_hub_dev[0], 0, sizeof(g_hub_dev));
    usbh_register_driver(&hub_driver);
}


/// @endcond HIDDEN_SYMBOLS

/**
  * @brief    Let USB stack polls all root hubs and downstream hubs. If there's any hub port
  *           change found, USB stack will manage the hub events in this function call.
  *           In this function, USB stack enumerates newly connected devices and remove staff
  *           of disconnected devices. User's application should periodically invoke this
  *           function.
  * @return   There's hub port change or not.
  * @retval   0   No any hub port status changes found.
  * @retval   1   There's hub port status changes.
  */
int  usbh_pooling_hubs(void)
{
    int   ret, change = 0;

#ifdef ENABLE_EHCI
    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)    /* Only M480MD has EHCI. */
    {
        _ehci->UPSCR[1] = HSUSBH_UPSCR_PP_Msk | HSUSBH_UPSCR_PO_Msk;     /* set port 2 owner to OHCI              */
        do
        {
            ret = ehci_driver.rthub_polling();
            if (ret)
                change = 1;
        }
        while (ret == 1);
    }
#endif

#ifdef ENABLE_OHCI
    do
    {
        ret = ohci_driver.rthub_polling();
        if (ret)
            change = 1;
    }
    while (ret == 1);
#endif


    do
    {
        ret = hub_polling();
        if (ret)
            change = 1;
    }
    while (ret == 1);

    return change;
}


/**
  * @brief    Find the device under the specified hub port.
  * @param[in]  hub_id    Hub identify ID
  * @param[in]  port      Port number of the specified ub.
  * @retval   NULL   Not found. There's no valid device connected under that hub port.
  * @retval   Otherwise  An UDEV_T pointer reference to the device under specified hub and port.
  */
UDEV_T * usbh_find_device(char *hub_id, int port)
{
    int         i;
    HUB_DEV_T   *hub = NULL;
    UDEV_T      *udev;

    for (i = 0; i < MAX_HUB_DEVICE; i++)
    {
        if ((g_hub_dev[i].iface != NULL) && (strcmp(g_hub_dev[i].pos_id, hub_id) == 0))
        {
            hub = &g_hub_dev[i];
            break;
        }
    }
    if (hub == NULL)
        return NULL;

    udev = g_udev_list;
    while (udev != NULL)
    {
        if ((udev->parent == hub) && (udev->port_num == port))
            return udev;
        udev = udev->next;
    }
    return NULL;
}


/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
