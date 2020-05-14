/**************************************************************************//**
 * @file     usb_core.c
 * @version  V1.10
 * @brief   USB Host library core.
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "NuMicro.h"

#include "usb.h"
#include "hub.h"


/// @cond HIDDEN_SYMBOLS

USBH_T     *_ohci;
HSUSBH_T   *_ehci;

int    _IsInUsbInterrupt = 0;

static UDEV_DRV_T *  _drivers[MAX_UDEV_DRIVER];

static CONN_FUNC  *g_conn_func, *g_disconn_func;

/// @endcond HIDDEN_SYMBOLS


/**
  * @brief       Initialize M480 USB Host controller and USB stack.
  *
  * @return      None.
  */
void  usbh_core_init()
{
    NVIC_DisableIRQ(HSUSBH_IRQn);
    NVIC_DisableIRQ(USBH_IRQn);

    _ohci = USBH;
    _ehci = HSUSBH;

    memset(_drivers, 0, sizeof(_drivers));

    g_conn_func = NULL;
    g_disconn_func = NULL;

    usbh_hub_init();

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)    /* Only M480MD has EHCI. */
    {
        _ehci->USBPCR0 = 0x160;                /* enable PHY 0          */
        _ehci->USBPCR1 = 0x520;                /* enable PHY 1          */
    }

    usbh_memory_init();

    _ohci->HcMiscControl |= USBH_HcMiscControl_OCAL_Msk; /* Over-current active low  */
    //_ohci->HcMiscControl &= ~USBH_HcMiscControl_OCAL_Msk; /* Over-current active high  */

#ifdef ENABLE_OHCI
    ohci_driver.init();
    ENABLE_OHCI_IRQ();
#endif

#ifdef ENABLE_EHCI
    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)    /* Only M480MD has EHCI. */
    {
        ehci_driver.init();
        ENABLE_EHCI_IRQ();
    }
#endif
}

/**
  * @brief    Install device connect and disconnect callback function.
  *
  * @param[in]  conn_func       Device connect callback function.
  * @param[in]  disconn_func    Device disconnect callback function.
  * @return      None.
  */
void usbh_install_conn_callback(CONN_FUNC *conn_func, CONN_FUNC *disconn_func)
{
    g_conn_func = conn_func;
    g_disconn_func = disconn_func;
}

static int  reset_device(UDEV_T *udev)
{
    if (udev->parent == NULL)
    {
        if (udev->hc_driver)
            return udev->hc_driver->rthub_port_reset(udev->port_num-1);
        else
            return USBH_ERR_NOT_FOUND;
    }
    else
    {
        return udev->parent->port_reset(udev->parent, udev->port_num);
    }
}

#ifdef ENABLE_EHCI
static uint32_t ehci_UCMDR;
#endif

/**
  * @brief    Suspend USB Host Controller and devices
  * @return   None
  */
void usbh_suspend()
{
#ifdef ENABLE_EHCI
    int   time_out = 10;   /* ms */
#endif

#ifdef ENABLE_OHCI
    /* set port suspend if connected */
    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)
    {
        /* M480MD has port1, but M480LD has not port1 */
        if (_ohci->HcRhPortStatus[0] & USBH_HcRhPortStatus_CCS_Msk)
            _ohci->HcRhPortStatus[0] = USBH_HcRhPortStatus_PSS_Msk;    /* set port suspend    */
    }

    if (_ohci->HcRhPortStatus[1] & USBH_HcRhPortStatus_CCS_Msk)
        _ohci->HcRhPortStatus[1] = USBH_HcRhPortStatus_PSS_Msk;    /* set port suspend    */

    /* enable Device Remote Wakeup */
    _ohci->HcRhStatus |= USBH_HcRhStatus_DRWE_Msk;

    /* enable USBH RHSC interrupt for system wakeup */
    _ohci->HcInterruptEnable =  USBH_HcInterruptEnable_RHSC_Msk | USBH_HcInterruptEnable_RD_Msk;

    /* set Host Controller enter suspend state */
    _ohci->HcControl = (_ohci->HcControl & ~USBH_HcControl_HCFS_Msk) | (3 << USBH_HcControl_HCFS_Pos);
#endif

#ifdef ENABLE_EHCI
    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)    /* Only M480MD has EHCI. */
    {
        ehci_UCMDR = _ehci->UCMDR;

        if (_ehci->UPSCR[0] & HSUSBH_UPSCR_PE_Msk)
        {
            _ehci->UPSCR[0] |= HSUSBH_UPSCR_SUSPEND_Msk;
            delay_us(2000);         /* wait 2 ms */
        }

        _ehci->UCMDR &= ~(HSUSBH_UCMDR_PSEN_Msk | HSUSBH_UCMDR_ASEN_Msk | HSUSBH_UCMDR_RUN_Msk);
        while (time_out > 0)
        {
            if (!(_ehci->UCMDR & HSUSBH_UCMDR_RUN_Msk) && (_ehci->USTSR & HSUSBH_USTSR_HCHalted_Msk))
            {
                break;
            }
        }
        if (time_out == 0)
        {
            USB_error("usbh_suspend - RUN/HCHalted error!\n");
        }
        delay_us(100);
    }
#endif
}


/**
  * @brief    Resume USB Host controller and devices
  * @return   None
  */
void usbh_resume(void)
{
#ifdef ENABLE_OHCI
    _ohci->HcControl = (_ohci->HcControl & ~USBH_HcControl_HCFS_Msk) | (1 << USBH_HcControl_HCFS_Pos);

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)
    {
        if (_ohci->HcRhPortStatus[0] & USBH_HcRhPortStatus_PSS_Msk)
            _ohci->HcRhPortStatus[0] = USBH_HcRhPortStatus_POCI_Msk;   /* clear suspend status */
    }
    if (_ohci->HcRhPortStatus[1] & USBH_HcRhPortStatus_PSS_Msk)
        _ohci->HcRhPortStatus[1] = USBH_HcRhPortStatus_POCI_Msk;   /* clear suspend status */

    delay_us(30000);                       /* wait at least 20ms for Host to resume device */

    /* enter operational state */
    _ohci->HcControl = (_ohci->HcControl & ~USBH_HcControl_HCFS_Msk) | (2 << USBH_HcControl_HCFS_Pos);
#endif

#ifdef ENABLE_EHCI
    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)    /* Only M480MD has EHCI. */
    {
        _ehci->UCMDR = ehci_UCMDR;

        if (_ehci->UPSCR[0] & HSUSBH_UPSCR_PE_Msk)
        {
            _ehci->UPSCR[0] |= HSUSBH_UPSCR_FPR_Msk;
            delay_us(20000);                         /* keep resume signal for 20 ms */
            _ehci->UPSCR[0] &= ~HSUSBH_UPSCR_FPR_Msk;
        }
        delay_us(1000);
    }
#endif
}



/// @cond HIDDEN_SYMBOLS

/**
  * @brief    Register an USB device class or vendor driver to lightweight USB stack.
  *           All USB device drivers must be registered before usbh_core_init() called.
  * @param[in]  udrv   The USB device driver to be registered.
  * @return   Driver registration success or not.
  * @retval   0  Success
  * @retval   USBH_ERR_MEMORY_OUT   Registered drivers have reached MAX_UDEV_DRIVER limitation.
  */
int  usbh_register_driver(UDEV_DRV_T *udrv)
{
    int   i;

    for (i = 0; i < MAX_UDEV_DRIVER; i++)
    {
        if (_drivers[i] == udrv)
            return 0;                  /* already registered, do nothing */

        if (_drivers[i] == NULL)
        {
            _drivers[i] = udrv;        /* register this driver */
            return 0;
        }
    }
    return USBH_ERR_MEMORY_OUT;        /* reached MAX_UDEV_DRIVER limitation, aborted */
}


/**
  * @brief    Execute an USB request in control transfer. This function returns after the request
  *           was done or aborted.
  * @param[in]  udev            The target USB device.
  * @param[in]  bmRequestType   Characteristics of request
  * @param[in]  bRequest        Specific request
  * @param[in]  wValue          Word-sized field that varies according to request
  * @param[in]  wIndex          Word-sized field that varies according to request
  * @param[in]  wLength         Number of bytes to transfer if there is a Data stage
  * @param[in]  buff            Data buffer used in data stage
  * @param[in]  data_len        Length of data to be transmitted/received
  * @param[out] xfer_len        Transmitted/received length of data
  * @param[in]  timeout         Time-out limit (in 10ms - timer tick) of this transfer
  * @retval   0     Transfer success
  * @retval   < 0   Transfer failed. Refer to error code definitions.
  */
int usbh_ctrl_xfer(UDEV_T *udev, uint8_t bmRequestType, uint8_t bRequest, uint16_t wValue, uint16_t wIndex,
                   uint16_t wLength, uint8_t *buff, uint32_t *xfer_len, uint32_t timeout)
{
    UTR_T      *utr;
    uint32_t   t0;
    int        status;

    *xfer_len = 0;

    //if (check_device(udev))
    //    return USBH_ERR_INVALID_PARAM;

    utr = alloc_utr(udev);
    if (utr == NULL)
        return USBH_ERR_MEMORY_OUT;

    utr->setup.bmRequestType = bmRequestType;
    utr->setup.bRequest   = bRequest;
    utr->setup.wValue     = wValue;
    utr->setup.wIndex     = wIndex;
    utr->setup.wLength    = wLength;

    utr->buff = buff;
    utr->data_len = wLength;
    utr->bIsTransferDone = 0;
    status = udev->hc_driver->ctrl_xfer(utr);
    if (status < 0)
    {
        udev->ep0.hw_pipe = NULL;
        free_utr(utr);
        return status;
    }

    t0 = get_ticks();
    while (utr->bIsTransferDone == 0)
    {
        if (get_ticks() - t0 > timeout)
        {
            usbh_quit_utr(utr);
            free_utr(utr);
            udev->ep0.hw_pipe = NULL;
            return USBH_ERR_TIMEOUT;
        }
    }

    status = utr->status;

    if (status == 0)
    {
        *xfer_len = utr->xfer_len;
    }
    free_utr(utr);

    return status;
}


/**
  * @brief    Execute a bulk transfer request. This function will return immediately after
  *           issued the bulk transfer. USB stack will later call back utr->func() once the bulk
  *           transfer was done or aborted.
  * @param[in]  utr    The bulk transfer request.
  * @retval   0     Transfer success
  * @retval   < 0   Failed. Refer to error code definitions.
  */
int usbh_bulk_xfer(UTR_T *utr)
{
    return utr->udev->hc_driver->bulk_xfer(utr);
}

/**
  * @brief    Execute an interrupt transfer request. This function will return immediately after
  *           issued the interrupt transfer. USB stack will later call back utr->func() once the
  *           interrupt transfer was done or aborted.
  * @param[in]  utr    The interrupt transfer request.
  * @retval   0     Transfer success
  * @retval   < 0   Failed. Refer to error code definitions.
  */
int usbh_int_xfer(UTR_T *utr)
{
    return utr->udev->hc_driver->int_xfer(utr);
}

/**
  * @brief    Execute an isochronous transfer request. This function will return immediately after
  *           issued the isochronous transfer. USB stack will later call back utr->func() once the
  *           isochronous transfer was done or aborted.
  * @param[in]  utr    The isochronous transfer request.
  * @retval   0     Transfer success
  * @retval   < 0   Failed. Refer to error code definitions.
  */
int usbh_iso_xfer(UTR_T *utr)
{
    if (utr->udev->hc_driver == NULL)
    {
        printf("hc_driver - 0x%x\n", (int)utr->udev->hc_driver);
        return -1;
    }
    if (utr->udev->hc_driver->iso_xfer == NULL)
    {
        printf("iso_xfer - 0x%x\n", (int)utr->udev->hc_driver->iso_xfer);
        return -1;
    }
    return utr->udev->hc_driver->iso_xfer(utr);
}

/**
  * @brief    Force to quit an UTR transfer.
  * @param[in]  utr    The UTR transfer to be quit.
  * @retval   0     Transfer success
  * @retval   < 0   Failed. Refer to error code definitions.
  */
int usbh_quit_utr(UTR_T *utr)
{
    if (!utr || !utr->udev)
        return USBH_ERR_NOT_FOUND;

    return utr->udev->hc_driver->quit_xfer(utr, NULL);
}


/**
  * @brief    Force to quit an endpoint transfer.
  * @param[in]  udev     The USB device.
  * @param[in]  ep       The endpoint to be quit.
  * @retval   0     Transfer success
  * @retval   < 0   Failed. Refer to error code definitions.
  */
int usbh_quit_xfer(UDEV_T *udev, EP_INFO_T *ep)
{
    return udev->hc_driver->quit_xfer(NULL, ep);
}


void  dump_device_descriptor(DESC_DEV_T *desc)
{
    USB_debug("\n[Device Descriptor]\n");
    USB_debug("----------------------------------------------\n");
    USB_debug("  Length              = %2d\n",  desc->bLength);
    USB_debug("  DescriptorType      = 0x%02x\n", desc->bDescriptorType);
    USB_debug("  USB version         = %x.%02x\n",
              desc->bcdUSB >> 8, desc->bcdUSB & 0xff);
    USB_debug("  Vendor:Product      = %04x:%04x\n",
              desc->idVendor, desc->idProduct);
    USB_debug("  MaxPacketSize0      = %d\n",   desc->bMaxPacketSize0);
    USB_debug("  NumConfigurations   = %d\n",   desc->bNumConfigurations);
    USB_debug("  Device version      = %x.%02x\n",
              desc->bcdDevice >> 8, desc->bcdDevice & 0xff);
    USB_debug("  Device Class:SubClass:Protocol = %02x:%02x:%02x\n",
              desc->bDeviceClass, desc->bDeviceSubClass, desc->bDeviceProtocol);
}

void usbh_dump_interface_descriptor(DESC_IF_T *if_desc)
{
    USB_debug("\n    [Interface Descriptor]\n");
    USB_debug("    ----------------------------------------------\n");
    USB_debug("      Length              = %2d\n",  if_desc->bLength);
    USB_debug("      DescriptorType      = %02x\n", if_desc->bDescriptorType);
    USB_debug("      bInterfaceNumber    = %d\n", if_desc->bInterfaceNumber);
    USB_debug("      bAlternateSetting   = %d\n", if_desc->bAlternateSetting);
    USB_debug("      bNumEndpoints       = %d\n", if_desc->bNumEndpoints);
    USB_debug("      bInterfaceClass     = 0x%02x\n", if_desc->bInterfaceClass);
    USB_debug("      bInterfaceSubClass  = 0x%02x\n", if_desc->bInterfaceSubClass);
    USB_debug("      bInterfaceProtocol  = 0x%02x\n", if_desc->bInterfaceProtocol);
    USB_debug("      iInterface          = %d\n", if_desc->iInterface);
}

void usbh_dump_endpoint_descriptor(DESC_EP_T *ep_desc)
{
    USB_debug("\n        [Endpoint Descriptor]\n");
    USB_debug("        ----------------------------------------------\n");
    USB_debug("          Length              = %2d\n",  ep_desc->bLength);
    USB_debug("          DescriptorType      = %02x\n", ep_desc->bDescriptorType);
    USB_debug("          bEndpointAddress    = 0x%02x\n", ep_desc->bEndpointAddress);
    USB_debug("          bmAttributes        = 0x%02x\n", ep_desc->bmAttributes);
    USB_debug("          wMaxPacketSize      = %d\n", ep_desc->wMaxPacketSize);
    USB_debug("          bInterval           = %d\n", ep_desc->bInterval);
    USB_debug("          bRefresh            = %d\n", ep_desc->bRefresh);
    USB_debug("          bSynchAddress       = %d\n", ep_desc->bSynchAddress);
}

void  dump_config_descriptor(DESC_CONF_T *desc)
{
    uint8_t     *bptr = (uint8_t *)desc;
    DESC_HDR_T  *hdr;
    int         tlen = desc->wTotalLength;

    while (tlen > 0)
    {
        switch (bptr[1])
        {
        case USB_DT_CONFIGURATION:
            USB_debug("\n[Configuration Descriptor]\n");
            USB_debug("----------------------------------------------\n");
            USB_debug("  Length              = %2d\n",  desc->bLength);
            USB_debug("  DescriptorType      = %02x\n", desc->bDescriptorType);
            USB_debug("  wTotalLength        = %2d\n", desc->wTotalLength);
            USB_debug("  bNumInterfaces      = %d\n", desc->bNumInterfaces);
            USB_debug("  bConfigurationValue = %d\n", desc->bConfigurationValue);
            USB_debug("  iConfiguration      = %d\n", desc->iConfiguration);
            USB_debug("  bmAttributes        = 0x%02x\n", desc->bmAttributes);
            USB_debug("  MaxPower            = %d\n", desc->MaxPower);
            break;

        case USB_DT_INTERFACE:
            usbh_dump_interface_descriptor((DESC_IF_T *)bptr);
            break;

        case USB_DT_ENDPOINT:
            usbh_dump_endpoint_descriptor((DESC_EP_T *)bptr);
            break;

        default:
            hdr = (DESC_HDR_T *)bptr;
            USB_debug("\n!![Unknown Descriptor]\n");
            USB_debug("----------------------------------------------\n");
            USB_debug("Length              = %2d\n",  hdr->bLength);
            USB_debug("DescriptorType      = %02x\n", hdr->bDescriptorType);
            break;
        }
        if (bptr[0] == 0)
            break;
        tlen -= bptr[0];
        bptr += bptr[0];
    }
}

/**
 *  @brief  Execute USB standard request SET ADDRESS.
 *  @retval   0  Success
 *  @retval   < 0   Failed. Refer to error code definitions.
 */
int usbh_set_address(UDEV_T *udev)
{
    uint32_t  read_len;
    int       dev_num, ret;

    if (udev->dev_num != 0)
        return USBH_ERR_SET_DEV_ADDR;

    dev_num = alloc_dev_address();

    /*------------------------------------------------------------------------------------*/
    /* Issue SET ADDRESS command to set device address                                    */
    /*------------------------------------------------------------------------------------*/
    ret = usbh_ctrl_xfer(udev, REQ_TYPE_OUT | REQ_TYPE_STD_DEV | REQ_TYPE_TO_DEV,
                         USB_REQ_SET_ADDRESS, dev_num, 0, 0,
                         NULL, &read_len, 100);
    if (ret < 0)
    {
        free_dev_address(dev_num);
        return ret;
    }

    udev->dev_num = dev_num;

    return 0;
}

/**
 *  @brief  Execute USB standard request SET CONFIGURATION.
 *  @retval   0  Success
 *  @retval   < 0   Failed. Refer to error code definitions.
 */
int usbh_set_configuration(UDEV_T *udev, uint8_t conf_val)
{
    uint32_t  read_len;
    int       ret;

    /* Current configuration is the same. Do nothing. */
    if (udev->cur_conf == conf_val)
        return 0;

    /* Set another configuration is currently not supported! */
    if (udev->cur_conf != -1)
        return USBH_ERR_SET_CONFIG;

    /*------------------------------------------------------------------------------------*/
    /* Issue SET CONFIGURATION command to select device configuration                     */
    /*------------------------------------------------------------------------------------*/
    ret = usbh_ctrl_xfer(udev, REQ_TYPE_OUT | REQ_TYPE_STD_DEV | REQ_TYPE_TO_DEV,
                         USB_REQ_SET_CONFIGURATION, conf_val, 0, 0,
                         NULL, &read_len, 300);
    if (ret < 0)
        return ret;

    udev->cur_conf = (int8_t)conf_val;

    return 0;
}

/**
 *  @brief    Select an alternate setting for the specified interface.
 *  @param[in]  iface        The interface
 *  @param[in]  alt_setting  Desired alternative setting
 *  @retval   0  Success
 *  @retval   < 0   Failed. Refer to error code definitions.
 */
int usbh_set_interface(IFACE_T *iface, uint16_t alt_setting)
{
    ALT_IFACE_T  *aif = NULL;
    uint32_t     xfer_len;
    int          i, ret;

    for (i = 0; i < iface->num_alt; i++)
    {
        if (iface->alt[i].ifd->bAlternateSetting == alt_setting)
        {
            aif = &iface->alt[i];
            break;
        }
    }
    if (aif == NULL)
        return USBH_ERR_NOT_FOUND;          /* cannot find desired alternative setting    */

    ret = usbh_ctrl_xfer(iface->udev, REQ_TYPE_OUT | REQ_TYPE_STD_DEV | REQ_TYPE_TO_IFACE,
                         USB_REQ_SET_INTERFACE, alt_setting, iface->if_num, 0,
                         NULL, &xfer_len, 100);
    if (ret == 0)
        iface->aif = aif;                   /* change active alternative setting          */
    return ret;
}

/**
 *  @brief  Get device descriptor from the USB device.
 *  @param[out] desc_buff  Data buffer to receive device descriptor data.
 *  @return   Success or not.
 *  @retval   0  Success
 *  @retval   Otherwise  Failed
 */
int usbh_get_device_descriptor(UDEV_T *udev, DESC_DEV_T *desc_buff)
{
    uint32_t  read_len;
    int       ret, retry;
    int       timeout = 10;

    for (retry = 0; retry < 3; retry++)
    {
        ret = usbh_ctrl_xfer(udev, REQ_TYPE_IN | REQ_TYPE_STD_DEV | REQ_TYPE_TO_DEV,
                             USB_REQ_GET_DESCRIPTOR,
                             ((USB_DT_STANDARD | USB_DT_DEVICE) << 8), 0, sizeof(DESC_DEV_T),
                             (uint8_t *)desc_buff, &read_len, timeout);
        if (ret == 0)
            return 0;

        USB_debug("Get device descriptor failed - %d, retry!\n", ret);
    }
    return ret;
}

/**
 *  @brief  Get configuration descriptor from the USB device.
 *  @param[out] desc_buff  Data buffer to receive configuration descriptor data.
 *  @param[in]  buff_len   Valid length of <desc_buff>
 *  @return   Success or not.
 *  @retval   0  Success
 *  @retval   Otherwise  Failed
 */
int usbh_get_config_descriptor(UDEV_T *udev, uint8_t *desc_buff, int buff_len)
{
    uint32_t  read_len;
    DESC_CONF_T  *conf = (DESC_CONF_T *)desc_buff;
    int       ret;

    /*------------------------------------------------------------------------------------*/
    /* Issue GET DESCRIPTOR command to get configuration descriptor                       */
    /*------------------------------------------------------------------------------------*/
    ret = usbh_ctrl_xfer(udev, REQ_TYPE_IN | REQ_TYPE_STD_DEV | REQ_TYPE_TO_DEV,
                         USB_REQ_GET_DESCRIPTOR,
                         ((USB_DT_STANDARD | USB_DT_CONFIGURATION) << 8), 0, 9,
                         desc_buff, &read_len, 200);
    if (ret < 0)
        return ret;

    if (conf->wTotalLength > buff_len)
    {
        USB_error("Device configuration %d length > %d!\n", conf->wTotalLength, buff_len);
        return USBH_ERR_DATA_OVERRUN;
    }

    read_len = conf->wTotalLength;

    ret = usbh_ctrl_xfer(udev, REQ_TYPE_IN | REQ_TYPE_STD_DEV | REQ_TYPE_TO_DEV,
                         USB_REQ_GET_DESCRIPTOR,
                         ((USB_DT_STANDARD | USB_DT_CONFIGURATION) << 8), 0, read_len,
                         desc_buff, &read_len, 200);
    if (ret < 0)
        return ret;

    return 0;
}

/**
 *  @brief  Get string descriptor from the USB device.
  * @param[in]  udev       The target USB device.
 *  @param[in]  index      Index of string descriptor
 *  @param[out] desc_buff  Data buffer to receive the string descriptor data.
 *  @param[in]  buff_len   Valid length of <desc_buff>
 *  @return   Success or not.
 *  @retval   0  Success
 *  @retval   Otherwise  Failed
 */
int usbh_get_string_descriptor(UDEV_T *udev, int index, uint8_t *desc_buff, int buff_len)
{
    uint32_t  read_len;
    int       ret;

    /*------------------------------------------------------------------------------------*/
    /* Issue GET DESCRIPTOR command to get configuration descriptor                       */
    /*------------------------------------------------------------------------------------*/
    ret = usbh_ctrl_xfer(udev, REQ_TYPE_IN | REQ_TYPE_STD_DEV | REQ_TYPE_TO_DEV,
                         USB_REQ_GET_DESCRIPTOR,
                         ((USB_DT_STANDARD | USB_DT_STRING) << 8) | index, 0x0409, buff_len,
                         desc_buff, &read_len, 200);
    return ret;
}

/**
 *  @brief  Issue a standard request SET_FEATURE to clear USB device endpoint halt state.
 *  @param[in] ep_addr  Endpoint to be clear halt.
 *  @return   Success or not.
 *  @retval   0  Success
 *  @retval   Otherwise  Failed
 */
int usbh_clear_halt(UDEV_T *udev, uint16_t ep_addr)
{
    uint32_t  read_len;

    USB_debug("Clear endpoint 0x%x halt.\n", ep_addr);
    return usbh_ctrl_xfer(udev, REQ_TYPE_OUT | REQ_TYPE_STD_DEV | REQ_TYPE_TO_EP,
                          USB_REQ_CLEAR_FEATURE, 0, ep_addr, 0,
                          NULL, &read_len, 100);
}

static int  usbh_parse_endpoint(ALT_IFACE_T *alt, int ep_idx, uint8_t *desc_buff, int len)
{
    DESC_EP_T    *ep_desc;
    int          parsed_len = 0;
    int          pksz;

    while (len > 0)
    {
        ep_desc = (DESC_EP_T *)desc_buff;

        if ((len < ep_desc->bLength) || (ep_desc->bLength < 2))
        {
            USB_error("ERR DESCRIPTOR EP LEN [0x%X %d]\n", ep_desc->bDescriptorType, ep_desc->bLength);
            return USBH_ERR_DESCRIPTOR;
        }

        if (ep_desc->bDescriptorType == USB_DT_ENDPOINT)
            break;     /* endpoint descriptor found */

        /* unrecognized descriptor */
        USB_vdebug("ignore descriptor 0x%X %d\n", ep_desc->bDescriptorType, ep_desc->bLength);
        desc_buff += ep_desc->bLength;
        parsed_len += ep_desc->bLength;
        len -= ep_desc->bLength;
    }

    USB_vdebug("Descriptor Found - Alt: %d, Endpoint 0x%x, remaining len: %d\n", alt->ifd->bAlternateSetting, ep_desc->bEndpointAddress, len);

    alt->ep[ep_idx].bEndpointAddress = ep_desc->bEndpointAddress;
    alt->ep[ep_idx].bmAttributes     = ep_desc->bmAttributes;
    alt->ep[ep_idx].bInterval        = ep_desc->bInterval;
    pksz = ep_desc->wMaxPacketSize;
    pksz = (pksz & 0x07ff) * (1 + ((pksz >> 11) & 3));
    alt->ep[ep_idx].wMaxPacketSize   = pksz;
    alt->ep[ep_idx].hw_pipe          = NULL;

    return parsed_len + ep_desc->bLength;
}

/**
  * @brief    Parse interface descriptor.
  * @param[in]  udev    The USB device.
  * @param[in]  desc_buff   Descriptor buffer
  * @param[in]  len         Remaining length of descriptors in buffer.
  * @return   Driver registration success or not.
  * @retval   0  Success
  * @retval   USBH_ERR_MEMORY_OUT   Registered drivers have reached MAX_UDEV_DRIVER limitation.
  */
static int  usbh_parse_interface(UDEV_T *udev, uint8_t *desc_buff, int len)
{
    int         i, matched, parsed_len = 0;
    DESC_HDR_T  *hdr;
    DESC_IF_T   *if_desc;
    IFACE_T     *iface = NULL;
    int         ret;

    iface = usbh_alloc_mem(sizeof(*iface)); /* create an interface                        */
    if (iface == NULL)
        return USBH_ERR_MEMORY_OUT;
    iface->udev = udev;
    iface->aif = &iface->alt[0];            /* Default active interface should be the
                                               first found alternative interface          */
    iface->if_num = ((DESC_IF_T *)desc_buff)->bInterfaceNumber;

    while (len > 0)
    {
        /*--------------------------------------------------------------------------------*/
        /* Find the first/next interface descriptor                                       */
        /*--------------------------------------------------------------------------------*/
        if_desc = (DESC_IF_T *)desc_buff;

        if (if_desc->bDescriptorType != USB_DT_INTERFACE)
        {
            desc_buff += if_desc->bLength;
            parsed_len += if_desc->bLength;
            len -= if_desc->bLength;
            continue;
        }

        if (if_desc->bInterfaceNumber != iface->if_num)
        {
            goto parse_done;
        }

        if (if_desc->bNumEndpoints > MAX_EP_PER_IFACE)
        {
            USB_error("IF EP LIMITE %d\n", if_desc->bNumEndpoints);
            ret = USBH_ERR_IF_EP_LIMIT;
            goto err_out;
        }

        /* Step over the interface descriptor */
        desc_buff += if_desc->bLength;
        parsed_len += if_desc->bLength;
        len -= if_desc->bLength;
        USB_vdebug("Descriptor Found - Interface %d, Alt: %d, num_alt:%d, remaining len: %d\n", if_desc->bInterfaceNumber, if_desc->bAlternateSetting, iface->num_alt, len);

        /*--------------------------------------------------------------------------------*/
        /* Add to alternative interface list                                              */
        /*--------------------------------------------------------------------------------*/
        if (iface->num_alt >= MAX_ALT_PER_IFACE)
        {
            ret = USBH_ERR_IF_ALT_LIMIT;
            goto err_out;
        }

        /*--------------------------------------------------------------------------------*/
        /* Find the next alternative interface or endpoint descriptor                     */
        /*--------------------------------------------------------------------------------*/
        while (len > 0)
        {
            hdr = (DESC_HDR_T *)desc_buff;

            if ((len < hdr->bLength) || (hdr->bLength < 2))
            {
                USB_error("ERR DESCRIPTOR IF LEN [0x%X %d]\n", hdr->bDescriptorType, hdr->bLength);
                ret = USBH_ERR_DESCRIPTOR;
                goto err_out;
            }

            if (hdr->bDescriptorType == USB_DT_CONFIGURATION)
                goto parse_done;            /* is other configuration, parsing completed  */

            if ((hdr->bDescriptorType == USB_DT_INTERFACE) || (hdr->bDescriptorType == USB_DT_ENDPOINT))
                break;                      /* the first endpoint descriptor found        */

            /* unrecognized descriptor */
            USB_vdebug("ignore descriptor 0x%X %d\n", hdr->bDescriptorType, hdr->bLength);
            desc_buff += hdr->bLength;
            parsed_len += hdr->bLength;
            len -= hdr->bLength;
        }

        iface->alt[iface->num_alt].ifd = if_desc;
        iface->num_alt++;

        if (len == 0)
            goto parse_done;

        if (hdr->bDescriptorType == USB_DT_INTERFACE)
            continue;                       /* is the next interface descriptor           */

        USB_vdebug("Finding %d endpoints of interface %d, alt %d...\n", if_desc->bNumEndpoints, if_desc->bInterfaceNumber, if_desc->bAlternateSetting);

        /* parsign all endpoint descriptors */
        for (i = 0; i < if_desc->bNumEndpoints; i++)
        {
            ret = usbh_parse_endpoint(&iface->alt[iface->num_alt-1], i, desc_buff, len);
            if (ret < 0)
                goto err_out;

            desc_buff += ret;
            parsed_len += ret;
            len -= ret;
            USB_vdebug("EP parse remaining %d\n", len);
        }
    }

parse_done:

    /*
     *  Probing all registered USB device drivers to find a matched driver.
     */
    matched = 0;
    for (i = 0; i < MAX_UDEV_DRIVER; i++)
    {
        if ((_drivers[i] != NULL) && (_drivers[i]->probe(iface) == 0))
        {
            matched = 1;
            break;
        }
    }

    if (matched)
    {
        iface->driver = _drivers[i];        /* have a driver now */
        iface->next = NULL;

        /* Added this interface to USB device interface list */
        if (udev->iface_list == NULL)
            udev->iface_list = iface;
        else
        {
            iface->next = udev->iface_list;
            udev->iface_list = iface;
        }
    }
    else
    {
        usbh_free_mem(iface, sizeof(*iface));
        iface = NULL;
    }

    return parsed_len;

err_out:
    usbh_free_mem(iface, sizeof(*iface));
    return ret;
}


static int  usbh_parse_configuration(UDEV_T *udev, uint8_t *desc_buff)
{
    DESC_CONF_T  *config = (DESC_CONF_T *)desc_buff;
    DESC_HDR_T   *hdr;
    int    i, ret, len;

    len = config->wTotalLength;

    desc_buff += config->bLength;
    len -= config->bLength;

    USB_vdebug("Parsing CONFIG =>\n");

    for (i = 0; i < config->bNumInterfaces; i++)
    {
        /*
         *  find the next interface descriptor
         */
        while (len >= sizeof(DESC_HDR_T))
        {
            hdr = (DESC_HDR_T *)desc_buff;

            if ((hdr->bLength > len) || (hdr->bLength < 2))
            {
                USB_error("ERR DESCRIPTOR CONFIG [%d]\n", hdr->bLength);
                return USBH_ERR_DESCRIPTOR;
            }

            if (hdr->bDescriptorType == USB_DT_INTERFACE)
                break;

            USB_debug("ignore descriptor 0x%X %d\n", hdr->bDescriptorType, hdr->bLength);

            desc_buff += hdr->bLength;
            len -= hdr->bLength;
        }

        ret = usbh_parse_interface(udev, desc_buff, len);
        if (ret < 0)
            return ret;

        desc_buff += ret;
        len -= ret;
        USB_vdebug("IFACE parse remaining %d\n", len);
    }

    if (len > 0)
    {
        USB_debug("ERR DESCRIPTOR CONFIG LEN %d\n", len);
        return USBH_ERR_DESCRIPTOR;
    }
    return len;
}

void print_usb_string(char *lead, uint8_t *str)
{
    int  len, i = 2;

    USB_debug("%s", lead);
    len = str[0];
    while (i < len)
    {
        USB_debug("%c", str[i]);
        i += 2;
    }
    USB_debug("\n");
}

int  connect_device(UDEV_T *udev)
{
    DESC_CONF_T  *conf;
    uint32_t     read_len;
    int          ret;

    USB_debug("Connect device =>\n");

    delay_us(100 * 1000);                   /* initially, give 100 ms delay               */

    usbh_get_device_descriptor(udev, &udev->descriptor);

    reset_device(udev);

    delay_us(100 * 1000);

    ret = usbh_set_address(udev);
    if (ret < 0)
    {
        USB_debug("Set address command failed!!\n");
        return ret;
    }

    delay_us(100 * 1000);                   /* after set address, give 100 ms delay       */

    USB_debug("New %s device address %d assigned.\n", (udev->speed == SPEED_HIGH) ? "high-speed" : ((udev->speed == SPEED_FULL) ? "full-speed" : "low-speed"), udev->dev_num);

    /* Get device descriptor again with new device address */
    ret = usbh_get_device_descriptor(udev, &udev->descriptor);
    if (ret < 0)
    {
        free_dev_address(udev->dev_num);
        return ret;
    }

#if  defined(DUMP_DESCRIPTOR) && defined(ENABLE_DEBUG_MSG)
    dump_device_descriptor(&udev->descriptor);
#endif

    if (udev->descriptor.bNumConfigurations != 1)
    {
        USB_debug("Warning! This device has multiple configurations [%d]. \n", udev->descriptor.bNumConfigurations);
    }

    conf = (DESC_CONF_T *)usbh_alloc_mem(MAX_DESC_BUFF_SIZE);
    if (conf == NULL)
    {
        free_dev_address(udev->dev_num);
        return USBH_ERR_MEMORY_OUT;
    }

    udev->cfd_buff = (uint8_t *)conf;

    /* Get configuration descriptor again with new device address */
    ret = usbh_get_config_descriptor(udev, (uint8_t *)conf, MAX_DESC_BUFF_SIZE);
    if (ret < 0)
    {
        free_dev_address(udev->dev_num);
        return ret;
    }

#if  defined(DUMP_DESCRIPTOR) && defined(ENABLE_DEBUG_MSG)
    dump_config_descriptor(conf);
#endif

#if 0  /* printf string descriptors, for debug only */
    str_buff = (uint8_t *)usbh_alloc_mem(MAX_DESC_BUFF_SIZE);
    if (udev->descriptor.iManufacturer != 0)
    {
        usbh_get_string_descriptor(udev, udev->descriptor.iManufacturer, str_buff, MAX_DESC_BUFF_SIZE);
        print_usb_string("Manufactor: ", str_buff);
    }
    if (udev->descriptor.iProduct != 0)
    {
        usbh_get_string_descriptor(udev, udev->descriptor.iProduct, str_buff, MAX_DESC_BUFF_SIZE);
        print_usb_string("Product: ", str_buff);
    }
    if (udev->descriptor.iSerialNumber != 0)
    {
        usbh_get_string_descriptor(udev, udev->descriptor.iSerialNumber, str_buff, MAX_DESC_BUFF_SIZE);
        print_usb_string("Serial Number: ", str_buff);
    }
    usbh_free_mem(str_buff, MAX_DESC_BUFF_SIZE);
#endif

    /* Always select the first configuration */
    ret = usbh_set_configuration(udev, conf->bConfigurationValue);
    if (ret < 0)
    {
        USB_debug("Set configuration %d failed!\n", conf->bConfigurationValue);
        free_dev_address(udev->dev_num);
        return ret;
    }

    /* Parse the configuration/interface/endpoint descriptors and find corresponding drivers. */
    ret = usbh_parse_configuration(udev, (uint8_t *)conf);
    if (ret < 0)
    {
        USB_debug("Parse configuration %d failed!\n", conf->bConfigurationValue);
        free_dev_address(udev->dev_num);
        return ret;
    }

    if (conf->bmAttributes & (1<<5))
    {
        /* If this configuration supports remote wakeup, enable it.                           */
        if (usbh_ctrl_xfer(udev, REQ_TYPE_OUT | REQ_TYPE_STD_DEV | REQ_TYPE_TO_DEV,
                           USB_REQ_SET_FEATURE, 0x01, 0x0000, 0x0000,
                           NULL, &read_len, 300) < 0)
        {
            USB_debug("Device does not accept remote wakeup enable command.\n");
        }
    }

    if (g_conn_func)
        g_conn_func(udev, 0);

    return ret;
}

int  usbh_reset_device(UDEV_T *udev)
{
    IFACE_T      *iface;
    DESC_CONF_T  *conf;
    uint32_t     read_len;
    int          dev_num, ret;

    USB_debug("Reset device =>\n");

    usbh_pooling_hubs();

    /*------------------------------------------------------------------------------------*/
    /*  Disconnect device                                                                 */
    /*------------------------------------------------------------------------------------*/

    if (g_disconn_func)
        g_disconn_func(udev, 0);

    usbh_quit_xfer(udev, &(udev->ep0));    /* Quit control transfer if hw_pipe is not NULL.  */

    /* Notified all actived interface device driver  */
    iface = udev->iface_list;
    while (iface != NULL)
    {
        udev->iface_list = iface->next;
        iface->driver->disconnect(iface);
        usbh_free_mem(iface, sizeof(*iface));
        iface = udev->iface_list;
    }

    /*------------------------------------------------------------------------------------*/
    /*  Reset device                                                                      */
    /*------------------------------------------------------------------------------------*/

    reset_device(udev);

    delay_us(100 * 1000);

    /*------------------------------------------------------------------------------------*/
    /*  Set address (use current address)                                                 */
    /*------------------------------------------------------------------------------------*/

    dev_num = udev->dev_num;
    udev->dev_num = 0;
    /* Issue SET ADDRESS command to set the same device address                           */
    ret = usbh_ctrl_xfer(udev, REQ_TYPE_OUT | REQ_TYPE_STD_DEV | REQ_TYPE_TO_DEV,
                         USB_REQ_SET_ADDRESS, dev_num, 0, 0,
                         NULL, &read_len, 100);
    udev->dev_num = dev_num;
    if (ret < 0)
        return ret;

    delay_us(100 * 1000);                   /* after set address, give 100 ms delay       */

    /*------------------------------------------------------------------------------------*/
    /*  Get device descriptor                                                             */
    /*------------------------------------------------------------------------------------*/

    /* Get device descriptor again with new device address */
    ret = usbh_get_device_descriptor(udev, &udev->descriptor);
    if (ret < 0)
        return ret;

    /*------------------------------------------------------------------------------------*/
    /*  Get configuration descriptor                                                      */
    /*------------------------------------------------------------------------------------*/

    conf = (DESC_CONF_T *)udev->cfd_buff;   /* using the previously allocated buffer      */

    /* Get configuration descriptor again with new device address */
    ret = usbh_get_config_descriptor(udev, (uint8_t *)conf, MAX_DESC_BUFF_SIZE);
    if (ret < 0)
        return ret;

    /* Always select the first configuration */
    ret = usbh_set_configuration(udev, udev->cur_conf);
    if (ret < 0)
    {
        USB_debug("Set configuration %d failed!\n", udev->cur_conf);
        return ret;
    }

    /* Parse the configuration/interface/endpoint descriptors and find corresponding drivers. */
    ret = usbh_parse_configuration(udev, (uint8_t *)conf);
    if (ret < 0)
    {
        USB_debug("Parse configuration %d failed!\n", conf->bConfigurationValue);
        return ret;
    }

    /* Enable remote wakeup                                                                   */
    if (usbh_ctrl_xfer(udev, REQ_TYPE_OUT | REQ_TYPE_STD_DEV | REQ_TYPE_TO_DEV,
                       USB_REQ_SET_FEATURE, 0x01, 0x0000, 0x0000,
                       NULL, &read_len, 300) < 0)
    {
        USB_debug("Device not accept remote wakeup enable command.\n");
    }

    if (g_conn_func)
        g_conn_func(udev, 0);

    return ret;
}

void disconnect_device(UDEV_T *udev)
{
    IFACE_T      *iface;

    USB_debug("disconnect device...\n");

    if (g_disconn_func)
        g_disconn_func(udev, 0);

    usbh_quit_xfer(udev, &(udev->ep0));    /* Quit control transfer if hw_pipe is not NULL.  */

    /* Notified all actived interface device driver  */
    iface = udev->iface_list;
    while (iface != NULL)
    {
        udev->iface_list = iface->next;
        iface->driver->disconnect(iface);
        usbh_free_mem(iface, sizeof(*iface));
        iface = udev->iface_list;
    }

    /* remove device from global device list */
    free_dev_address(udev->dev_num);
    free_device(udev);

    usbh_memory_used();
}

#if 0
static int  check_device(UDEV_T *udev)
{
    UDEV_T  *d;

    if (udev == NULL)
        return USBH_ERR_INVALID_PARAM;

    //if ((udev->hc_driver != &ohci_driver) && (udev->hc_driver != &ehci_driver))
    //  return USBH_ERR_INVALID_PARAM;

    d = g_udev_list;
    while (d)
    {
        if (d == udev)
            return USBH_OK;
        d = d->next;
    }
    return USBH_ERR_INVALID_PARAM;
}
#endif

EP_INFO_T * usbh_iface_find_ep(IFACE_T *iface, uint8_t ep_addr, uint8_t dir_type)
{
    ALT_IFACE_T  *aif = iface->aif;
    int     i;

    if (ep_addr == 0)      /* find the first EP matched with specified direction and type */
    {
        for (i = 0; i < aif->ifd->bNumEndpoints; i++)
        {
            if (((aif->ep[i].bEndpointAddress & EP_ADDR_DIR_MASK) == (dir_type & EP_ADDR_DIR_MASK)) &&
                    ((aif->ep[i].bmAttributes & EP_ATTR_TT_MASK) == (dir_type & EP_ATTR_TT_MASK)))
                return &aif->ep[i];
        }
    }
    else                   /* find the EP with specified endpoint address                 */
    {
        for (i = 0; i < aif->ifd->bNumEndpoints; i++)
        {
            if (aif->ep[i].bEndpointAddress == ep_addr)
                return &aif->ep[i];
        }
    }
    return NULL;
}

void  usbh_dump_buff_bytes(uint8_t *buff, int nSize)
{
    int     nIdx, i;

    nIdx = 0;
    while (nSize > 0)
    {
        printf("0x%04X  ", nIdx);
        for (i = 0; i < 16; i++)
            printf("%02x ", buff[nIdx + i]);
        printf("  ");
        for (i = 0; i < 16; i++)
        {
            if ((buff[nIdx + i] >= 0x20) && (buff[nIdx + i] < 127))
                printf("%c", buff[nIdx + i]);
            else
                printf(".");
            nSize--;
        }
        nIdx += 16;
        printf("\n");
    }
    printf("\n");
}

void usbh_dump_iface(IFACE_T *iface)
{
    USB_debug("\n  [IFACE info] (0x%x)\n", (int)iface);
    USB_debug("  ----------------------------------------------\n");
    USB_debug("  udev       = 0x%x\n", iface->udev);
    USB_debug("  if_num     = %d\n", iface->if_num);
    USB_debug("  driver     = 0x%x\n", (int)iface->driver);
    USB_debug("  next       = 0x%x\n", (int)iface->next);
    usbh_dump_interface_descriptor(iface->aif->ifd);
}

void usbh_dump_ep_info(EP_INFO_T *ep)
{
    USB_debug("\n  [Endpoint Info] (0x%x)\n", (int)ep);
    USB_debug("  ----------------------------------------------\n");
    USB_debug("  bEndpointAddress    = 0x%02x\n", ep->bEndpointAddress);
    USB_debug("  bmAttributes        = 0x%02x\n", ep->bmAttributes);
    USB_debug("  bInterval           = %d\n",     ep->bInterval);
    USB_debug("  wMaxPacketSize      = %d\n",     ep->wMaxPacketSize);
    USB_debug("  hw_pipe             = 0x%x\n",   (int)ep->hw_pipe);
}

/// @endcond HIDDEN_SYMBOLS


/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
