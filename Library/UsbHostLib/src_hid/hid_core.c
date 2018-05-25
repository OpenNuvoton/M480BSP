/**************************************************************************//**
 * @file     hid_core.c
 * @version  V1.00
 * @brief    M480 USB Host HID driver.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "NuMicro.h"

#include "usb.h"
#include "usbh_lib.h"
#include "usbh_hid.h"


/// @cond HIDDEN_SYMBOLS

#define USB_CTRL_TIMEOUT_MS        100


static int get_free_utr_slot(HID_DEV_T *hdev)
{
    int    i;

    for (i = 0; i < CONFIG_HID_DEV_MAX_PIPE; i++)
    {
        if (hdev->utr_list[i] == NULL)
            return i;
    }
    return -1;
}


/// @endcond


/**
 *  @brief  Read report descriptor from HID device.
 *  @param[in]  hdev         HID device pointer
 *  @param[out] desc_buf     Data buffer for report descriptor read from HID device.
 *  @param[in]  buf_max_len  The maximum length of desc_buf.
 *  @return   Report descriptor length or error code.
 *  @retval   <0        Failed
 *  @retval   Otherwise  Length of report descriptor read.
 */
int32_t  usbh_hid_get_report_descriptor(HID_DEV_T *hdev, uint8_t *desc_buf, int buf_max_len)
{
    IFACE_T    *iface;
    uint32_t   xfer_len;
    int        ret;

    if (buf_max_len < 9)
        return HID_RET_INVALID_PARAMETER;

    if (!hdev || !hdev->iface)
        return USBH_ERR_NOT_FOUND;

    iface = (IFACE_T *)hdev->iface;

    ret = usbh_ctrl_xfer(iface->udev,
                         REQ_TYPE_IN | REQ_TYPE_STD_DEV | REQ_TYPE_TO_IFACE,    /* bmRequestType */
                         USB_REQ_GET_DESCRIPTOR,        /* bRequest                              */
                         (USB_DT_REPORT << 8) + 0,      /* wValue                                */
                         iface->if_num,                 /* wIndex                                */
                         buf_max_len,                   /* wLength                               */
                         desc_buf, &xfer_len, USB_CTRL_TIMEOUT_MS);

    if ((ret < 0) || (xfer_len == 0))
    {
        HID_DBGMSG("failed to get HID descriptor.\n");
        return HID_RET_IO_ERR;
    }
    return (int)xfer_len;
}


/**
 * @brief  Issue a HID class GET_REPORT request.
 *
 * @param[in] hdev       HID device pointer
 * @param[in] rtp_typ    Report type. Valid values are:
 *                       - \ref RT_INPUT
 *                       - \ref RT_OUTPUT
 *                       - \ref RT_FEATURE
 * @param[in] rtp_id     Report ID
 * @param[out] data      Buffer to store data retrieved from this report ID.
 * @param[in] len        Report length.
 * @return   Report length or error code.
 * @retval   >=0         The actual length of data obtained from this report ID.
 * @retval   Otherwise   Failed
 */
int32_t  usbh_hid_get_report(HID_DEV_T *hdev, int rtp_typ, int rtp_id,
                             uint8_t *data, int len)
{
    IFACE_T    *iface;
    uint32_t   xfer_len;
    int        ret;

    if (!hdev || !hdev->iface)
        return USBH_ERR_NOT_FOUND;

    iface = (IFACE_T *)hdev->iface;

    ret = usbh_ctrl_xfer(iface->udev,
                         REQ_TYPE_IN | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_IFACE,  /* bmRequestType */
                         HID_REPORT_GET,                /* bRequest                              */
                         rtp_id + (rtp_typ << 8),       /* wValue                                */
                         iface->if_num,                 /* wIndex                                */
                         len,                           /* wLength                               */
                         data, &xfer_len, USB_CTRL_TIMEOUT_MS);
    if (ret < 0)
    {
        HID_DBGMSG("failed to get report!\n");
        return HID_RET_IO_ERR;
    }
    return (int)xfer_len;
}


/**
 * @brief  Issue a HID class SET_REPORT request. The Set_Report
 *         request allows the host to send a report to the device, possibly
 *         setting the state of input, output, or feature controls.
 *
 * @param[in] hdev       HID device pointer
 * @param[in] rtp_typ    Report type. Valid values are:
 *                       - \ref RT_INPUT
 *                       - \ref RT_OUTPUT
 *                       - \ref RT_FEATURE
 * @param[in] rtp_id     Report ID
 * @param[out] data      Buffer store data to be send.
 * @param[in] len        Report length.
 * @return   Written length or error code.
 * @retval   >=0         The actual length of data written to this report ID.
 * @retval   Otherwise   Failed
 */
int32_t  usbh_hid_set_report(HID_DEV_T *hdev, int rtp_typ, int rtp_id,
                             uint8_t *data, int len)
{
    IFACE_T    *iface;
    uint32_t   xfer_len;
    int        ret;

    if (!hdev || !hdev->iface)
        return USBH_ERR_NOT_FOUND;

    iface = (IFACE_T *)hdev->iface;

    ret = usbh_ctrl_xfer(iface->udev,
                         REQ_TYPE_OUT | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_IFACE, /* bmRequestType */
                         HID_REPORT_SET,                /* bRequest                              */
                         rtp_id + (rtp_typ << 8),       /* wValue                                */
                         iface->if_num,                 /* wIndex                                */
                         len,                           /* wLength                               */
                         data, &xfer_len, USB_CTRL_TIMEOUT_MS);
    if (ret < 0)
    {
        HID_DBGMSG("failed to set report!\n");
        return HID_RET_IO_ERR;
    }
    return (int)xfer_len;
}


/**
 * @brief  Issue a HID class GET_IDLE request. The GET_IDLE request
 *         reads the current idle rate for a particular Input report.
 *
 * @param[in] hdev       HID device pointer
 * @param[in] rtp_id     Report ID
 * @param[out] idle_rate An one byte buffer holds the reported idle rate.
 * @return   Success or not.
 * @retval   0           Success
 * @retval   Otherwise   Failed
 */
int32_t  usbh_hid_get_idle(HID_DEV_T *hdev, int rtp_id, uint8_t *idle_rate)
{
    IFACE_T    *iface;
    uint32_t   xfer_len;
    int        ret;

    if (!hdev || !hdev->iface)
        return USBH_ERR_NOT_FOUND;

    iface = (IFACE_T *)hdev->iface;

    ret = usbh_ctrl_xfer(iface->udev,
                         REQ_TYPE_IN | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_IFACE,  /* bmRequestType */
                         HID_GET_IDLE,                  /* bRequest                              */
                         rtp_id,                        /* wValue                                */
                         iface->if_num,                 /* wIndex                                */
                         1,                             /* wLength                               */
                         idle_rate, &xfer_len, USB_CTRL_TIMEOUT_MS);

    if ((ret < 0) || (xfer_len != 1))
    {
        HID_DBGMSG("failed to get idle rate! %d\n", ret);
        return HID_RET_IO_ERR;
    }
    return HID_RET_OK;
}


/**
 * @brief  Issue a HID class SET_IDLE request. The SET_IDLE request
 *         silences a particular report on the Interrupt In pipe until a
 *         new event occurs or the specified amount of time passes.
 *
 * @param[in] hdev       HID device
 * @param[in] rtp_id     Report ID
 * @param[out] idle_rate The idle rate to be set.
 * @return   Success or not.
 * @retval   0           Success
 * @retval   Otherwise   Failed
 */
int32_t  usbh_hid_set_idle(HID_DEV_T *hdev, int rtp_id, uint8_t idle_rate)
{
    IFACE_T    *iface;
    uint32_t   xfer_len;
    uint16_t   wValue = idle_rate;
    int        ret;

    if (!hdev || !hdev->iface)
        return USBH_ERR_NOT_FOUND;

    iface = (IFACE_T *)hdev->iface;

    ret = usbh_ctrl_xfer(iface->udev,
                         REQ_TYPE_OUT | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_IFACE, /* bmRequestType */
                         HID_SET_IDLE,                  /* bRequest                              */
                         rtp_id + (wValue << 8),        /* wValue                                */
                         iface->if_num,                 /* wIndex                                */
                         0,                             /* wLength                               */
                         NULL, &xfer_len, USB_CTRL_TIMEOUT_MS);

    if (ret < 0)
    {
        HID_DBGMSG("failed to set idle rate! %d\n", ret);
        return HID_RET_IO_ERR;
    }
    return HID_RET_OK;
}


/**
 * @brief  Issue a HID class GET_PROTOCOL request. The GET_PROTOCOL
 *         request reads which protocol is currently active (either the boot
 *         protocol or the report protocol.)
 *
 * @param[in] hdev       HID device pointer
 * @param[out] protocol  An one byte buffer holds the protocol code.
 * @return   Success or not.
 * @retval   0           Success
 * @retval   Otherwise   Failed
 */
int32_t  usbh_hid_get_protocol(HID_DEV_T *hdev, uint8_t *protocol)
{
    IFACE_T     *iface;
    uint32_t    xfer_len;
    int         ret;

    if (!hdev || !hdev->iface)
        return USBH_ERR_NOT_FOUND;

    iface = (IFACE_T *)hdev->iface;

    ret = usbh_ctrl_xfer(iface->udev,
                         REQ_TYPE_IN | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_IFACE,  /* bmRequestType */
                         HID_GET_PROTOCOL,              /* bRequest                              */
                         0,                             /* wValue                                */
                         iface->if_num,                 /* wIndex                                */
                         1,                             /* wLength                               */
                         protocol, &xfer_len, USB_CTRL_TIMEOUT_MS);

    if ((ret < 0) || (xfer_len != 1))
    {
        HID_DBGMSG("failed to get idle rate! %d\n", ret);
        return HID_RET_IO_ERR;
    }
    return HID_RET_OK;
}


/**
 * @brief  Issue a HID class SET_PROTOCOL request. The SET_PROTOCOL
 *         switches between the boot protocol and the report protocol (or
 *         vice versa).
 *
 * @param[in] hdev       HID device pointer.
 * @param[in] protocol   The protocol to be set.
 * @return   Success or not.
 * @retval   0           Success
 * @retval   Otherwise   Failed
 */
int32_t  usbh_hid_set_protocol(HID_DEV_T *hdev, uint8_t protocol)
{
    IFACE_T    *iface;
    uint32_t   xfer_len;
    int        ret;

    if (!hdev || !hdev->iface)
        return USBH_ERR_NOT_FOUND;

    iface = (IFACE_T *)hdev->iface;

    ret = usbh_ctrl_xfer(iface->udev,
                         REQ_TYPE_OUT | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_IFACE, /* bmRequestType */
                         HID_SET_PROTOCOL,              /* bRequest                              */
                         protocol,                      /* wValue                                */
                         iface->if_num,                 /* wIndex                                */
                         0,                             /* wLength                               */
                         NULL, &xfer_len, USB_CTRL_TIMEOUT_MS);

    if (ret < 0)
    {
        HID_DBGMSG("failed to set idle rate! %d\n", ret);
        return HID_RET_IO_ERR;
    }
    return HID_RET_OK;
}


/// @cond HIDDEN_SYMBOLS


/*
 * HID int-in complete function
 */
static void  hid_read_irq(UTR_T *utr)
{
    HID_DEV_T   *hdev;
    int         ret;

    //HID_DBGMSG("hid_read_irq. %d\n", utr->xfer_len);

    hdev = (HID_DEV_T *)utr->context;

    if (utr->status != 0)
    {
        HID_DBGMSG("hid_read_irq - has error: 0x%x\n", utr->status);
        hdev->read_func(hdev, utr->ep->bEndpointAddress, utr->status, utr->buff, 0);
        return;
    }

    if (hdev->read_func && utr->xfer_len)
        hdev->read_func(hdev, utr->ep->bEndpointAddress, utr->status, utr->buff, utr->xfer_len);

    utr->xfer_len = 0;
    ret = usbh_int_xfer(utr);
    if (ret)
    {
        HID_DBGMSG("hid_read_irq - failed to submit interrupt-in request (%d)", ret);
        hdev->read_func(hdev, utr->ep->bEndpointAddress, ret, utr->buff, 0);
        usbh_free_mem(utr->buff, utr->data_len);
        free_utr(utr);
    }
}

/*
 * HID int-out complete function
 */
static void  hid_write_irq(UTR_T *utr)
{
    HID_DEV_T     *hdev;
    int           ret;

    //HID_DBGMSG("hid_write_irq. %d\n", urb->actual_length);

    hdev = (HID_DEV_T *)utr->context;

    if (utr->status)
    {
        HID_DBGMSG("hid_write_irq - has error: 0x%x\n", utr->status);
        hdev->write_func(hdev, utr->ep->bEndpointAddress, utr->status, utr->buff, &(utr->data_len));
        return;
    }

    if (hdev->write_func)
    {
        utr->data_len = utr->ep->wMaxPacketSize;
        hdev->write_func(hdev, utr->ep->bEndpointAddress, utr->status, utr->buff, &(utr->data_len));
    }

    utr->xfer_len = 0;
    ret = usbh_int_xfer(utr);
    if (ret)
    {
        HID_DBGMSG("hid_write_irq - failed to submit interrupt-out request (%d)", ret);
        hdev->write_func(hdev, utr->ep->bEndpointAddress, ret, utr->buff, &(utr->data_len));
        free_utr(utr);
    }
}


/// @endcond HIDDEN_SYMBOLS

/**
 *  @brief  Start purge the USB interrupt in transfer.
 *  @param[in] hdev       HID device pointer.
 *  @param[in] ep_addr    Endpoint address. If ep_addr is 0, it will use the first found interrupt-in
 *                        endpoint. If ep_addr is not 0, it will use the specified endpoint if found.
 *  @param[in] func       The interrupt in data receiver callback function.
 *  @return   Success or not.
 *  @retval    0          Success
 *  @retval    Otherwise  Failed
 */
int32_t usbh_hid_start_int_read(HID_DEV_T *hdev, uint8_t ep_addr, HID_IR_FUNC *func)
{
    IFACE_T    *iface = (IFACE_T *)hdev->iface;
    UTR_T      *utr;
    EP_INFO_T  *ep;
    int         i, ret;

    if ((!iface) || (!iface->udev))
        return HID_RET_DEV_NOT_FOUND;

    if (!func)
        return HID_RET_INVALID_PARAMETER;

    for (i = 0; i < CONFIG_HID_DEV_MAX_PIPE; i++)
    {
        utr = hdev->utr_list[i];
        if ((utr != NULL) && (utr->ep != NULL) && (utr->ep->bEndpointAddress == ep_addr))
        {
            return HID_RET_XFER_IS_RUNNING;      /* transfer of this pipe is running      */
        }
    }

    if (ep_addr == 0)
        ep = usbh_iface_find_ep(iface, 0, EP_ADDR_DIR_IN | EP_ATTR_TT_INT);
    else
        ep = usbh_iface_find_ep(iface, ep_addr, 0);

    if (ep == NULL)
        return USBH_ERR_EP_NOT_FOUND;

    utr = alloc_utr(iface->udev);
    if (!utr)
        return USBH_ERR_MEMORY_OUT;

    utr->buff = usbh_alloc_mem(ep->wMaxPacketSize);
    if (utr->buff == NULL)
    {
        free_utr(utr);
        return USBH_ERR_MEMORY_OUT;
    }

    hdev->read_func = func;

    utr->context = hdev;
    utr->ep = ep;
    utr->data_len = ep->wMaxPacketSize;
    utr->xfer_len = 0;
    utr->func = hid_read_irq;

    ret = usbh_int_xfer(utr);
    if (ret < 0)
    {
        HID_DBGMSG("Error - failed to submit interrupt read request (%d)", ret);
        usbh_free_mem(utr->buff, utr->data_len);
        free_utr(utr);
        return HID_RET_IO_ERR;
    }

    i = get_free_utr_slot(hdev);
    if (i < 0)
    {
        HID_DBGMSG("Error - No free HID slot!\n");
        usbh_quit_utr(utr);
        usbh_free_mem(utr->buff, utr->data_len);
        free_utr(utr);
        return USBH_ERR_MEMORY_OUT;         /* no free UTR slot.                          */
    }
    else
    {
        hdev->utr_list[i] = utr;
    }

    return HID_RET_OK;
}

/**
 *  @brief  Stop purge the USB interrupt in transfer.
 *  @param[in] hdev       HID device pointer
 *  @param[in] ep_addr    Endpoint address. If ep_addr is 0, it will use the first found interrupt-in
 *                        endpoint. If ep_addr is not 0, it will use the specified endpoint if found.
 *  @return   Success or not.
 *  @retval    0          Success
 *  @retval    Otherwise  Failed
 */
int32_t usbh_hid_stop_int_read(HID_DEV_T *hdev, uint8_t ep_addr)
{
    IFACE_T    *iface = (IFACE_T *)hdev->iface;
    UTR_T      *utr;
    int        i, ret;

    if ((!iface) || (!iface->udev))
        return HID_RET_DEV_NOT_FOUND;

    for (i = 0; i < CONFIG_HID_DEV_MAX_PIPE; i++)
    {
        utr = hdev->utr_list[i];
        if (ep_addr == 0)
        {
            /* Find any running UTR whose endpoint direction is IN                     */
            if ((utr != NULL) && (utr->ep != NULL) &&
                    ((utr->ep->bEndpointAddress & EP_ADDR_DIR_MASK) == EP_ADDR_DIR_IN))
            {
                break;
            }
        }
        else
        {
            /* Find any running UTR whose endpoint address is matched with ep_addr     */
            if ((utr != NULL) && (utr->ep != NULL) && (utr->ep->bEndpointAddress == ep_addr))
            {
                break;                          /* UTR found                                  */
            }
        }
        utr = NULL;
    }

    if (utr == NULL)
        return HID_RET_DEV_NOT_FOUND;

    hdev->utr_list[i] = NULL;               /* remove it from HID UTR list                */

    ret = usbh_quit_utr(utr);               /* force to stop the transfer                 */

    usbh_free_mem(utr->buff, utr->ep->wMaxPacketSize);
    free_utr(utr);

    return ret;
}

/**
 *  @brief  Start purge the USB interrupt out transfer.
 *  @param[in] hdev       HID device pointer.
 *  @param[in] ep_addr    Endpoint address. If ep_addr is 0, it will use the first found interrupt-out
 *                        endpoint. If ep_addr is not 0, it will use the specified endpoint if found.
 *  @param[in] func       The interrupt in data transfer callback function.
 *  @return   Success or not.
 *  @retval   0           Success
 *  @retval   Otherwise   Failed
 */
int32_t usbh_hid_start_int_write(HID_DEV_T *hdev, uint8_t ep_addr, HID_IW_FUNC *func)
{
    IFACE_T    *iface = (IFACE_T *)hdev->iface;
    UTR_T      *utr;
    EP_INFO_T  *ep;
    int        i, ret;

    if ((!iface) || (!iface->udev))
        return HID_RET_DEV_NOT_FOUND;

    if (!func)
        return HID_RET_INVALID_PARAMETER;

    for (i = 0; i < CONFIG_HID_DEV_MAX_PIPE; i++)
    {
        utr = hdev->utr_list[i];
        if ((utr != NULL) && (utr->ep != NULL) && (utr->ep->bEndpointAddress == ep_addr))
        {
            return HID_RET_XFER_IS_RUNNING;      /* transfer of this pipe is running      */
        }
    }

    if (ep_addr == 0)
        ep = usbh_iface_find_ep(iface, 0, EP_ADDR_DIR_OUT | EP_ATTR_TT_INT);
    else
        ep = usbh_iface_find_ep(iface, ep_addr, 0);

    if (ep == NULL)
        return USBH_ERR_EP_NOT_FOUND;

    utr = alloc_utr(iface->udev);
    if (!utr)
        return USBH_ERR_MEMORY_OUT;

    utr->buff = usbh_alloc_mem(ep->wMaxPacketSize);
    if (utr->buff == NULL)
    {
        free_utr(utr);
        return USBH_ERR_MEMORY_OUT;
    }

    hdev->write_func = func;

    utr->context = hdev;
    utr->ep = ep;
    utr->data_len = ep->wMaxPacketSize;
    utr->xfer_len = 0;
    utr->func = hid_write_irq;

    /* first time interrupt write call-back to get first data packet */
    func(hdev, ep->bEndpointAddress, 0, utr->buff, &(utr->data_len));

    ret = usbh_int_xfer(utr);
    if (ret < 0)
    {
        HID_DBGMSG("Error - failed to submit interrupt read request (%d)", ret);
        free_utr(utr);
        return HID_RET_IO_ERR;
    }

    i = get_free_utr_slot(hdev);
    if (i < 0)
    {
        HID_DBGMSG("Error - No free HID slot!\n");
        usbh_quit_utr(utr);
        usbh_free_mem(utr->buff, utr->data_len);
        free_utr(utr);
        return USBH_ERR_MEMORY_OUT;         /* no free UTR slot.                          */
    }
    else
    {
        hdev->utr_list[i] = utr;
    }

    return HID_RET_OK;
}

/**
 *  @brief  stop purge the USB interrupt out transfer.
 *  @param[in] hdev       HID device pointer
 *  @param[in] ep_addr    Endpoint address. If ep_addr is 0, it will use the first found interrupt-out
 *                        endpoint. If ep_addr is not 0, it will use the specified endpoint if found.
 *  @return   Success or not.
 *  @retval    0          Success
 *  @retval    Otherwise  Failed
 */
int32_t usbh_hid_stop_int_write(HID_DEV_T *hdev, uint8_t ep_addr)
{
    IFACE_T    *iface = (IFACE_T *)hdev->iface;
    UTR_T      *utr;
    int        i, ret;

    if ((!iface) || (!iface->udev))
        return HID_RET_DEV_NOT_FOUND;

    for (i = 0; i < CONFIG_HID_DEV_MAX_PIPE; i++)
    {
        utr = hdev->utr_list[i];
        if (ep_addr == 0)
        {
            /* Find any running UTR whose endpoint direction is OUT                    */
            if ((utr != NULL) && (utr->ep != NULL) &&
                    ((utr->ep->bEndpointAddress & EP_ADDR_DIR_MASK) == EP_ADDR_DIR_OUT))
            {
                break;
            }
        }
        else
        {
            /* Find any running UTR whose endpoint address is matched with ep_addr     */
            if ((utr != NULL) && (utr->ep != NULL) && (utr->ep->bEndpointAddress == ep_addr))
            {
                break;                          /* UTR found                                  */
            }
        }
        utr = NULL;
    }

    if (utr == NULL)
        return HID_RET_DEV_NOT_FOUND;

    hdev->utr_list[i] = NULL;               /* remove it from HID UTR list                */

    ret = usbh_quit_utr(utr);

    usbh_free_mem(utr->buff, utr->ep->wMaxPacketSize);
    free_utr(utr);

    return ret;
}


/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/


