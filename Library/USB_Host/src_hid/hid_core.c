/**************************************************************************//**
 * @file     hid_core.c
 * @version  V1.00
 * $Revision: 13 $
 * $Date: 14/12/02 5:47p $
 * @brief    M480 USB Host HID driver.
 *
 * @note
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "M480.h"

#include "usb.h"
#include "usbh_lib.h"
#include "usbh_hid.h"


/// @cond HIDDEN_SYMBOLS

#define USB_TIMEOUT             100000


static int usb_snd_control_msg(HID_DEV_T *hdev, int requesttype, int request,
                               int value, int index, char *bytes, int size, int timeout)
{
    struct usb_device  *udev = hdev->udev;

    return usb_control_msg(udev, usb_sndctrlpipe(udev, 0),
                           request, requesttype, value, index, bytes, size, timeout);
}

int usb_rcv_control_msg(HID_DEV_T *hdev, int requesttype, int request,
                        int value, int index, char *bytes, int size, int timeout)
{
    struct usb_device  *udev = hdev->udev;

    return usb_control_msg(udev, usb_rcvctrlpipe(udev, 0),
                           request, requesttype, value, index, bytes, size, timeout);
}

/// @endcond


/**
 *  @brief  Get report descriptor request.
 *  @param[in]  hdev         HID device
 *  @param[out] desc_buf     The data buffer to store report descriptor.
 *  @param[in]  buf_max_len  The maximum length of desc_buf. This function will read more data
 *                           than buf_max_len.
 *  @return   Report descriptor length or error code.
 *  @retval   <0        Failed
 *  @retval   Otherwise  Length of report descriptor read.
 */
int32_t  usbh_hid_get_report_descriptor(HID_DEV_T *hdev, uint8_t *desc_buf, int buf_max_len)
{
    int  len;

    if (buf_max_len < 9)
        return HID_RET_INVALID_PARAMETER;

    len = usb_rcv_control_msg(hdev,
                              USB_DIR_IN+1,
                              USB_REQ_GET_DESCRIPTOR,
                              (USB_DT_HID << 8) + 0, hdev->ifnum,
                              (char*)desc_buf, buf_max_len,
                              USB_TIMEOUT);

    if (len < 0) {
        HID_DBGMSG("failed to get HID descriptor.\n");
        return HID_RET_IO_ERR;
    }

    len = desc_buf[7] | (desc_buf[8] << 8);

    HID_DBGMSG("Report descriptor size is %d\n", len);

    if (buf_max_len < len)
        return HID_RET_INVALID_PARAMETER;

    len = usb_rcv_control_msg(hdev,
                              USB_DIR_IN+1,
                              USB_REQ_GET_DESCRIPTOR,
                              (USB_DT_REPORT << 8) + 0, hdev->ifnum,
                              (char*)desc_buf, len,
                              USB_TIMEOUT);

    if (len < 0) {
        HID_DBGMSG("failed to get HID descriptor.\n");
        return HID_RET_IO_ERR;
    }

    HID_DBGMSG("successfully initialised HID descriptor %d bytes.\n", len);

    return len;
}


/**
 * @brief  HID class standard request Get_Report request. The Get_Report request
 *         allows the host to receive a report via the Control pipe.
 *
 * @param[in] hdev       HID device
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
    len = usb_rcv_control_msg(hdev,
                              USB_DIR_IN + USB_TYPE_CLASS + USB_RECIP_INTERFACE,
                              HID_REPORT_GET,
                              rtp_id + (rtp_typ << 8),
                              hdev->ifnum,
                              (char *)data, len, USB_TIMEOUT);

    if (len < 0) {
        HID_DBGMSG("failed to get report!\n");
        return HID_RET_IO_ERR;
    }
    return len;
}


/**
 * @brief  HID class standard request Set_Report request. The Set_Report
 *         request allows the host to send a report to the device, possibly
 *         setting the state of input, output, or feature controls.
 *
 * @param[in] hdev       HID device
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
    len = usb_snd_control_msg(hdev,
                              USB_DIR_OUT + USB_TYPE_CLASS + USB_RECIP_INTERFACE,
                              HID_REPORT_SET,
                              rtp_id + (rtp_typ << 8),
                              hdev->ifnum,
                              (char *)data, len, USB_TIMEOUT);

    if (len < 0) {
        HID_DBGMSG("failed to set report!\n");
        return HID_RET_IO_ERR;
    }
    return len;
}


/**
 * @brief  HID class standard request Get_Idle request. The Get_Idle request
 *         reads the current idle rate for a particular Input report
 *
 * @param[in] hdev       HID device
 * @param[in] rtp_id     Report ID
 * @param[out] idle_rate An one byte buffer holds the reported idle rate.
 * @return   Success or not.
 * @retval   0           Success
 * @retval   Otherwise   Failed
 */
int32_t  usbh_hid_get_idle(HID_DEV_T *hdev, int rtp_id, uint8_t *idle_rate)
{
    int   len;

    len = usb_rcv_control_msg(hdev,
                              USB_DIR_IN + USB_TYPE_CLASS + USB_RECIP_INTERFACE,
                              HID_GET_IDLE,
                              rtp_id,
                              hdev->ifnum,
                              (char *)idle_rate, 1, USB_TIMEOUT);

    if (len != 1) {
        HID_DBGMSG("failed to get idle rate! %d\n", len);
        return HID_RET_IO_ERR;
    }
    return HID_RET_OK;
}


/**
 * @brief  HID class standard request Set_Idle request. The Set_Idle request
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
    int       ret;
    uint16_t  wValue = idle_rate;

    ret = usb_snd_control_msg(hdev,
                              USB_DIR_OUT + USB_TYPE_CLASS + USB_RECIP_INTERFACE,
                              HID_SET_IDLE,
                              rtp_id + (wValue << 8),
                              hdev->ifnum,
                              NULL, 0, USB_TIMEOUT);

    if (ret < 0) {
        HID_DBGMSG("failed to set idle rate! %d\n", ret);
        return HID_RET_IO_ERR;
    }
    return HID_RET_OK;
}


/**
 * @brief  HID class standard request Get_Protocol request. The Get_Protocol
 *         request reads which protocol is currently active (either the boot
 *         protocol or the report protocol.)
 *
 * @param[in] hdev       HID device
 * @param[out] protocol  An one byte buffer holds the protocol code.
 * @return   Success or not.
 * @retval   0           Success
 * @retval   Otherwise   Failed
 */
int32_t  usbh_hid_get_protocol(HID_DEV_T *hdev, uint8_t *protocol)
{
    int   len;

    len = usb_rcv_control_msg(hdev,
                              USB_DIR_IN + USB_TYPE_CLASS + USB_RECIP_INTERFACE,
                              HID_GET_PROTOCOL,
                              0,
                              hdev->ifnum,
                              (char *)protocol, 1, USB_TIMEOUT);

    if (len != 1) {
        HID_DBGMSG("failed to get protocol! %d\n", len);
        return HID_RET_IO_ERR;
    }
    return HID_RET_OK;
}


/**
 * @brief  HID class standard request Set_Protocol request. The Set_Protocol
 *         switches between the boot protocol and the report protocol (or
 *         vice versa).
 *
 * @param[in] hdev       HID device
 * @param[in] protocol   The protocol to be set.
 * @return   Success or not.
 * @retval   0           Success
 * @retval   Otherwise   Failed
 */
int32_t  usbh_hid_set_protocol(HID_DEV_T *hdev, uint8_t protocol)
{
    int     ret;

    ret = usb_snd_control_msg(hdev,
                              USB_DIR_OUT + USB_TYPE_CLASS + USB_RECIP_INTERFACE,
                              HID_SET_PROTOCOL,
                              protocol,
                              hdev->ifnum,
                              NULL, 0, USB_TIMEOUT);

    if (ret < 0) {
        HID_DBGMSG("failed to set protocol! %d\n", ret);
        return HID_RET_IO_ERR;
    }
    return HID_RET_OK;
}


/// @cond HIDDEN_SYMBOLS

static struct usb_host_endpoint * hid_find_endpoint(HID_DEV_T *hdev, uint8_t ep_addr, uint8_t dir)
{
    struct usb_host_interface *desc;
    int  i;

    if ((ep_addr & 0x7f) > 0xf)
        return NULL;

    desc = hdev->intf->cur_altsetting;

    for (i = 0; i < desc->desc.bNumEndpoints; i++) {
        if ((desc->endpoint[i].desc.bmAttributes & USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_INT) {
            if (ep_addr == 0) {
                if ((desc->endpoint[i].desc.bEndpointAddress & 0x80) == dir)
                    return &(desc->endpoint[i]);
            } else {
                if (desc->endpoint[i].desc.bEndpointAddress == (ep_addr | USB_DIR_IN))
                    return &(desc->endpoint[i]);
            }
        }
    }
    return NULL;
}


/*
 * HID int-in complete function
 */
static void  hid_read_irq(struct urb *urb)
{
    HID_DEV_T   *hdev;
    int         ret;

    //HID_DBGMSG("hid_read_irq. %d\n", urb->actual_length);

    hdev = (HID_DEV_T *)urb->context;

    if (urb->status) {
        HID_DBGMSG("hid_read_irq - has error: 0x%x\n", urb->status);
        return;
    }

    if (hdev->read_func && urb->actual_length)
        hdev->read_func(hdev, usb_pipeendpoint(urb->pipe), urb->transfer_buffer, urb->actual_length);

    ret = usb_submit_urb(urb, 0);
    if (ret) {
        HID_DBGMSG("hid_read_irq - failed to submit interrupt-in request (%d)", ret);
        USB_free(urb->transfer_buffer);
        usb_free_urb(urb);
        hdev->urb_in[usb_pipeendpoint(urb->pipe)] = NULL;
    }
}

/*
 * HID int-out complete function
 */
static void  hid_write_irq(struct urb *urb)
{
    HID_DEV_T     *hdev;
    int           ret;

    //HID_DBGMSG("hid_write_irq. %d\n", urb->actual_length);

    hdev = (HID_DEV_T *)urb->context;

    if (urb->status) {
        HID_DBGMSG("hid_write_irq - has error: 0x%x\n", urb->status);
        return;
    }

    if (hdev->write_func)
        hdev->write_func(hdev, usb_pipeendpoint(urb->pipe),
                         (uint8_t **)&urb->transfer_buffer, &urb->transfer_buffer_length);

    ret = usb_submit_urb(urb, 0);
    if (ret) {
        HID_DBGMSG("hid_write_irq - failed to submit interrupt-out request (%d)", ret);
        usb_free_urb(urb);
        hdev->urb_out[usb_pipeendpoint(urb->pipe)] = NULL;
    }
}


/// @endcond HIDDEN_SYMBOLS

/**
 *  @brief  Start purge the USB interrupt in transfer.
 *  @param[in] hdev       HID device
 *  @param[in] ep_addr    Endpoint address. If ep_addr is 0, it will use the first found interrupt-in
 *                        endpoint. If ep_addr is not 0, it will use the specified endpoint if found.
 *  @param[in] func       The interrupt in data receiver callback function.
 *  @return   Success or not.
 *  @retval    0          Success
 *  @retval    Otherwise  Failed
 */
int32_t usbh_hid_start_int_read(HID_DEV_T *hdev, uint8_t ep_addr, HID_IR_FUNC *func)
{
    struct usb_device *udev;
    struct usb_host_endpoint  *ep;
    struct urb  *urb;
    void        *xfer_buff;
    uint32_t    pipe;
    int         maxp, ret;

    if (!hdev->udev || !hdev->intf)
        return HID_RET_DEV_NOT_FOUND;

    if (!func)
        return HID_RET_INVALID_PARAMETER;

    udev = hdev->udev;
    ep = hid_find_endpoint(hdev, ep_addr, USB_DIR_IN);
    if (ep == NULL)
        return HID_RET_EP_NOT_FOUND;

    if (hdev->urb_in[ep_addr&0xf] != NULL)
        return HID_RET_EP_USED;

    urb = usb_alloc_urb(0, GFP_KERNEL);
    if (urb == NULL) {
        HID_DBGMSG("Failed to allocated URB!\n");
        return HID_RET_OUT_OF_MEMORY;
    }

    pipe = usb_rcvintpipe(udev, ep->desc.bEndpointAddress);
    maxp = usb_maxpacket(udev, pipe, usb_pipeout(pipe));

    HID_DBGMSG("Endpoint 0x%x maximum packet size is %d.\n", ep->desc.bEndpointAddress, maxp);

    xfer_buff = USB_malloc(maxp, 4);
    if (xfer_buff == NULL) {
        usb_free_urb(urb);
        return HID_RET_OUT_OF_MEMORY;
    }

    usb_fill_int_urb(urb, udev, pipe, xfer_buff, maxp, hid_read_irq, hdev, ep->desc.bInterval);

    urb->context = hdev;
    hdev->urb_in[ep_addr&0xf] = urb;
    hdev->read_func = func;

    ret = usb_submit_urb(urb, 0);
    if (ret) {
        HID_DBGMSG("Error - failed to submit interrupt read request (%d)", ret);
        USB_free(xfer_buff);
        usb_free_urb(urb);
        hdev->urb_in[ep_addr&0xf] = NULL;
        return HID_RET_IO_ERR;
    }
    return HID_RET_OK;
}

/**
 *  @brief  stop purge the USB interrupt in transfer.
 *  @param[in] hdev       HID device
 *  @param[in] ep_addr    Endpoint address. If ep_addr is 0, it will use the first found interrupt-in
 *                        endpoint. If ep_addr is not 0, it will use the specified endpoint if found.
 *  @return   Success or not.
 *  @retval    0          Success
 *  @retval    Otherwise  Failed
 */
int32_t usbh_hid_stop_int_read(HID_DEV_T *hdev, uint8_t ep_addr)
{
    struct usb_host_endpoint  *ep;

    ep = hid_find_endpoint(hdev, ep_addr, USB_DIR_IN);
    if (ep == NULL)
        return HID_RET_EP_NOT_FOUND;

    ep_addr &= 0xf;

    if (hdev->urb_in[ep_addr] == NULL)
        return HID_RET_INVALID_PARAMETER;

    usb_unlink_urb(hdev->urb_in[ep_addr]);
    USB_free(hdev->urb_in[ep_addr]->transfer_buffer);
    usb_free_urb(hdev->urb_in[ep_addr]);
    hdev->urb_in[ep_addr] = NULL;
    return HID_RET_OK;
}

/**
 *  @brief  Start purge the USB interrupt out transfer.
 *  @param[in] hdev       HID device
 *  @param[in] ep_addr    Endpoint address. If ep_addr is 0, it will use the first found interrupt-in
 *                        endpoint. If ep_addr is not 0, it will use the specified endpoint if found.
 *  @param[in] func       The interrupt in data transfer callback function.
 *  @return   Success or not.
 *  @retval   0           Success
 *  @retval   Otherwise   Failed
 */
int32_t usbh_hid_start_int_write(HID_DEV_T *hdev, uint8_t ep_addr, HID_IW_FUNC *func)
{
    struct usb_device *udev;
    struct usb_host_endpoint  *ep;
    struct urb  *urb;
    uint32_t    pipe;
    int         maxp, ret;

    if (!hdev->udev || !hdev->intf)
        return HID_RET_DEV_NOT_FOUND;

    if (!func)
        return HID_RET_INVALID_PARAMETER;

    udev = hdev->udev;

    ep = hid_find_endpoint(hdev, ep_addr, USB_DIR_OUT);
    if (ep == NULL)
        return HID_RET_EP_NOT_FOUND;

    if (hdev->urb_out[ep_addr] != NULL)
        return HID_RET_EP_USED;

    urb = usb_alloc_urb(0, GFP_KERNEL);
    if (urb == NULL) {
        HID_DBGMSG("Failed to allocated URB!\n");
        return HID_RET_OUT_OF_MEMORY;
    }

    pipe = usb_sndintpipe(udev, ep->desc.bEndpointAddress);
    maxp = usb_maxpacket(udev, pipe, usb_pipeout(pipe));

    HID_DBGMSG("Endpoint 0x%x maximum packet size is %d.\n", ep->desc.bEndpointAddress, maxp);

    usb_fill_int_urb(urb, udev, pipe, NULL, maxp, hid_write_irq, hdev, ep->desc.bInterval);

    func(hdev, usb_pipeendpoint(pipe), (uint8_t **)&urb->transfer_buffer, &urb->transfer_buffer_length);

    hdev->urb_out[ep_addr] = urb;
    hdev->write_func = func;

    ret = usb_submit_urb(urb, 0);
    if (ret) {
        HID_DBGMSG("Error - failed to submit interrupt read request (%d)", ret);
        usb_free_urb(urb);
        hdev->urb_out[ep_addr] = NULL;
        return HID_RET_IO_ERR;
    }
    return HID_RET_OK;
}

/**
 *  @brief  stop purge the USB interrupt out transfer.
 *  @param[in] hdev       HID device
 *  @param[in] ep_addr    Endpoint address. If ep_addr is 0, it will use the first found interrupt-in
 *                        endpoint. If ep_addr is not 0, it will use the specified endpoint if found.
 *  @return   Success or not.
 *  @retval    0          Success
 *  @retval    Otherwise  Failed
 */
int32_t usbh_hid_stop_int_write(HID_DEV_T *hdev, uint8_t ep_addr)
{
    struct usb_host_endpoint  *ep;

    ep = hid_find_endpoint(hdev, ep_addr, USB_DIR_OUT);
    if (ep == NULL)
        return HID_RET_EP_NOT_FOUND;

    if (hdev->urb_out[ep_addr] == NULL)
        return HID_RET_INVALID_PARAMETER;

    usb_unlink_urb(hdev->urb_out[ep_addr]);
    usb_free_urb(hdev->urb_out[ep_addr]);
    hdev->urb_out[ep_addr] = NULL;
    return HID_RET_OK;
}


/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/


