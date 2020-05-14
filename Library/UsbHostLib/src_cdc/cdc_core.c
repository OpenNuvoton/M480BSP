/**************************************************************************//**
 * @file     cdc_core.c
 * @version  V1.00
 * @brief    M480 MCU USB Host CDC library core
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "NuMicro.h"

#include "usb.h"
#include "usbh_lib.h"
#include "usbh_cdc.h"


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
#define USB_XFER_TIMEOUT             100
/// @endcond /* HIDDEN_SYMBOLS */

/**
 *  @brief  GET_LINE_CODING  request
 *  @param[in]  cdev         CDC device
 *  @param[out] line_code    The currently configured line coding.
 *
 * @return   Success or not.
 * @retval   0           Success
 * @retval   Otherwise   Failed
 */
int32_t  usbh_cdc_get_line_coding(CDC_DEV_T *cdev, LINE_CODING_T *line_code)
{
    uint32_t  xfer_len;
    int       ret;

    if (cdev == NULL)
        return USBH_ERR_INVALID_PARAM;

    if (cdev->iface_cdc == NULL)
        return USBH_ERR_INVALID_PARAM;

    ret = usbh_ctrl_xfer(cdev->udev,
                         REQ_TYPE_IN | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_IFACE,  /* bmRequestType */
                         CDC_GET_LINE_CODING,           /* bRequest                              */
                         0,                             /* wValue                                */
                         cdev->iface_cdc->if_num,       /* wIndex                                */
                         7,                             /* wLength                               */
                         (uint8_t *)line_code,          /* data buffer                           */
                         &xfer_len, CDC_CMD_TIMEOUT);


    if ((ret < 0) || (xfer_len != 7))
    {
        CDC_DBGMSG("GET_LINE_CODIN command failed. %d, %d\n", ret, xfer_len);
        return ret;
    }
    return ret;
}


/**
 *  @brief  SET_LINE_CODING  request
 *  @param[in]  cdev         CDC device
 *  @param[in]  line_code    The line coding configuration to be set.
 *
 * @return   Success or not.
 * @retval   0           Success
 * @retval   Otherwise   Failed
 */
int32_t  usbh_cdc_set_line_coding(CDC_DEV_T *cdev, LINE_CODING_T *line_code)
{
    uint32_t  xfer_len;
    int       ret;

    if (cdev == NULL)
        return USBH_ERR_NOT_FOUND;

    if (cdev->iface_cdc == NULL)
        return USBH_ERR_NOT_FOUND;

    if ((line_code->stop_bits != 0) && (line_code->stop_bits != 1) &&
            (line_code->stop_bits != 2))
        return USBH_ERR_INVALID_PARAM;

    if (line_code->parity > 4)
        return USBH_ERR_INVALID_PARAM;

    if ((line_code->data_bits != 5) && (line_code->data_bits != 6) &&
            (line_code->data_bits != 7) && (line_code->data_bits != 8) &&
            (line_code->data_bits != 16))
        return USBH_ERR_INVALID_PARAM;

    ret = usbh_ctrl_xfer(cdev->udev,
                         REQ_TYPE_OUT | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_IFACE, /* bmRequestType */
                         CDC_SET_LINE_CODING,           /* bRequest                              */
                         0,                             /* wValue                                */
                         cdev->iface_cdc->if_num,       /* wIndex                                */
                         7,                             /* wLength                               */
                         (uint8_t *)line_code,          /* data buffer                           */
                         &xfer_len, CDC_CMD_TIMEOUT);

    if (ret < 0)
    {
        CDC_DBGMSG("SET_LINE_CODIN command failed. %d\n", ret);
        return ret;
    }
    return 0;
}

/**
 *  @brief  SET_CONTROL_LINE_STATE  request
 *  @param[in]  cdev             CDC device
 *  @param[in]  active_carrier   Carrier control for half duplex modems is activated or not.
 *  @param[in]  DTE_present      Indicates to DCE if DTE is present or not.
 *
 * @return   Success or not.
 * @retval   0           Success
 * @retval   Otherwise   Failed
 */
int32_t  usbh_cdc_set_control_line_state(CDC_DEV_T *cdev, int active_carrier, int DTE_present)
{
    uint32_t   xfer_len;
    int        ret;
    uint16_t   ctrl_bitmap = 0;

    if (cdev == NULL)
        return USBH_ERR_INVALID_PARAM;

    if (cdev->iface_cdc == NULL)
        return USBH_ERR_INVALID_PARAM;

    if (active_carrier)
        ctrl_bitmap |= 0x02;

    if (DTE_present)
        ctrl_bitmap |= 0x01;

    ret = usbh_ctrl_xfer(cdev->udev,
                         REQ_TYPE_OUT | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_IFACE, /* bmRequestType */
                         CDC_SET_CONTROL_LINE_STATE,    /* bRequest                              */
                         ctrl_bitmap,                   /* wValue                                */
                         cdev->iface_cdc->if_num,       /* wIndex                                */
                         0,                             /* wLength                               */
                         NULL,                          /* data buffer                           */
                         &xfer_len, CDC_CMD_TIMEOUT);


    if (ret)
    {
        CDC_DBGMSG("SET_CONTROL_LINE_STATE command failed. %d\n", ret);
        return ret;
    }
    return ret;
}

/// @cond HIDDEN_SYMBOLS
/*
 * CDC INT-in complete function
 */
static void  cdc_int_in_irq(UTR_T *utr)
{
    CDC_DEV_T   *cdev;
    int         ret;

    //CDC_DBGMSG("cdc_int_in_irq. %d\n", utr->xfer_len);

    cdev = (CDC_DEV_T *)utr->context;

    if (utr->status)
    {
        CDC_DBGMSG("cdc_int_in_irq - has error: 0x%x\n", utr->status);
        return;
    }

    if (cdev->sts_func && utr->xfer_len)
        cdev->sts_func(cdev, utr->buff, utr->xfer_len);

    utr->xfer_len = 0;
    ret = usbh_int_xfer(utr);
    if (ret)
    {
        CDC_DBGMSG("cdc_int_in_irq - failed to submit interrupt-in request (%d)", ret);
        free_utr(utr);
        cdev->utr_sts = NULL;
    }
}

/// @endcond HIDDEN_SYMBOLS

/**
 * @brief  Start purge the CDC device's interrupt-in transfer pipe.
 *  @param[in] cdev       CDC device
 *  @param[in] func       The interrupt in data receiver callback function.
 *  @return   Success or not.
 * @retval   0           Success
 * @retval   Otherwise   Failed
 */
int32_t usbh_cdc_start_polling_status(CDC_DEV_T *cdev, CDC_CB_FUNC *func)
{
    EP_INFO_T   *ep;
    UTR_T       *utr;
    int         ret;

    if ((cdev == NULL) || (cdev->iface_cdc == NULL))
        return USBH_ERR_NOT_FOUND;

    if (!func || cdev->utr_sts)
        return USBH_ERR_INVALID_PARAM;

    ep = cdev->ep_sts;
    if (ep == NULL)
    {
        ep = usbh_iface_find_ep(cdev->iface_cdc, 0, EP_ADDR_DIR_IN | EP_ATTR_TT_INT);
        if (ep == NULL)
        {
            CDC_DBGMSG("Interrupt-in endpoint not found in this CDC device!\n");
            return USBH_ERR_EP_NOT_FOUND;
        }
        cdev->ep_sts = ep;
    }

    utr = alloc_utr(cdev->udev);
    if (utr == NULL)
    {
        CDC_DBGMSG("Failed to allocated UTR!\n");
        return USBH_ERR_MEMORY_OUT;
    }

    utr->buff = (uint8_t *)cdev->sts_buff;
    utr->context = cdev;
    utr->ep = ep;
    utr->data_len = ep->wMaxPacketSize;
    if (utr->data_len > CDC_STATUS_BUFF_SIZE)
    {
        CDC_DBGMSG("Warning! CDC_STATUS_BUFF_SIZE %d is smaller than max. packet size %d!\n", CDC_STATUS_BUFF_SIZE, ep->wMaxPacketSize);
        utr->data_len = CDC_STATUS_BUFF_SIZE;
    }
    utr->xfer_len = 0;
    utr->func = cdc_int_in_irq;

    cdev->utr_sts = utr;
    cdev->sts_func = func;

    ret = usbh_int_xfer(utr);
    if (ret < 0)
    {
        CDC_DBGMSG("Error - failed to submit interrupt read request (%d)", ret);
        free_utr(utr);
        cdev->utr_sts = NULL;
        return ret;
    }

    return 0;
}
/// @cond HIDDEN_SYMBOLS
/*
 * CDC BULK-in complete function
 */
static void  cdc_bulk_in_irq(UTR_T *utr)
{
    CDC_DEV_T   *cdev;

    //CDC_DBGMSG("cdc_bulk_in_irq. %d\n", utr->xfer_len);

    cdev = (CDC_DEV_T *)utr->context;

    if (utr->status)
    {
        CDC_DBGMSG("cdc_bulk_in_irq - has error: 0x%x\n", utr->status);
        return;
    }

    if (cdev->rx_func)
        cdev->rx_func(cdev, utr->buff, utr->xfer_len);

    free_utr(utr);
    cdev->utr_rx = NULL;
    cdev->rx_busy = 0;
}

/// @endcond HIDDEN_SYMBOLS

/**
 * @brief  Make CDC device start to receive data from bulk-in transfer pipe.
 *  @param[in] cdev       CDC device
 *  @param[in] func       The BULK in data receiver callback function.
 *  @return   Success or not.
 * @retval   0           Success
 * @retval   Otherwise   Failed
 */
int32_t usbh_cdc_start_to_receive_data(CDC_DEV_T *cdev, CDC_CB_FUNC *func)
{
    EP_INFO_T   *ep;
    UTR_T       *utr;
    int         ret;

    if ((cdev == NULL) || (cdev->iface_data == NULL))
        return USBH_ERR_NOT_FOUND;

    if (!func)
        return USBH_ERR_INVALID_PARAM;

    ep = cdev->ep_rx;
    if (ep == NULL)
    {
        ep = usbh_iface_find_ep(cdev->iface_data, 0, EP_ADDR_DIR_IN | EP_ATTR_TT_BULK);
        if (ep == NULL)
        {
            CDC_DBGMSG("Bulk-in endpoint not found in this CDC device!\n");
            return USBH_ERR_EP_NOT_FOUND;
        }
        cdev->ep_rx = ep;
    }

    utr = alloc_utr(cdev->udev);
    if (utr == NULL)
    {
        CDC_DBGMSG("Failed to allocated UTR!\n");
        return USBH_ERR_MEMORY_OUT;
    }

    utr->buff = (uint8_t *)cdev->rx_buff;
    utr->context = cdev;
    utr->ep = ep;
    utr->data_len = ep->wMaxPacketSize;
    if (utr->data_len > CDC_RX_BUFF_SIZE)
    {
        CDC_DBGMSG("Warning! CDC_RX_BUFF_SIZE %d is smaller than max. packet size %d!\n", CDC_RX_BUFF_SIZE, ep->wMaxPacketSize);
        utr->data_len = CDC_RX_BUFF_SIZE;
    }
    utr->xfer_len = 0;
    utr->func = cdc_bulk_in_irq;

    cdev->rx_func = func;
    cdev->utr_rx = utr;
    cdev->rx_busy = 1;

    ret = usbh_bulk_xfer(utr);
    if (ret < 0)
    {
        CDC_DBGMSG("Error - failed to submit bulk in request (%d)", ret);
        free_utr(utr);
        cdev->utr_rx = NULL;
        cdev->rx_busy = 0;
        return ret;
    }
    return 0;
}
/// @cond HIDDEN_SYMBOLS
/*
 * CDC BULK-in complete function
 */
static volatile int  bulk_out_done;
static void  cdc_bulk_out_irq(UTR_T *utr)
{
    bulk_out_done = 1;
}
/// @endcond /* HIDDEN_SYMBOLS */
/**
 * @brief  Send a block of data via CDC device's bulk-out transfer pipe.
 *  @param[in] cdev      CDC device
 *  @param[in] buff      Buffer contains the data block to be send.
 *  @param[in] buff_len  Length in byte of data to be send
 *  @return   Success or not.
 * @retval   0           Success
 * @retval   Otherwise   Failed
 */
int32_t usbh_cdc_send_data(CDC_DEV_T *cdev, uint8_t *buff, int buff_len)
{
    EP_INFO_T   *ep;
    UTR_T       *utr;
    uint32_t    t0;
    int         ret;

    if ((cdev == NULL) || (cdev->iface_data == NULL))
        return USBH_ERR_NOT_FOUND;

    ep = cdev->ep_tx;
    if (ep == NULL)
    {
        ep = usbh_iface_find_ep(cdev->iface_data, 0, EP_ADDR_DIR_OUT | EP_ATTR_TT_BULK);
        if (ep == NULL)
        {
            CDC_DBGMSG("Bulk-out endpoint not found in this CDC device!\n");
            return USBH_ERR_EP_NOT_FOUND;
        }
        cdev->ep_tx = ep;
    }

    utr = alloc_utr(cdev->udev);
    if (utr == NULL)
    {
        CDC_DBGMSG("Failed to allocated UTR!\n");
        return USBH_ERR_MEMORY_OUT;
    }

    utr->context = cdev;
    utr->ep = ep;
    utr->buff = buff;
    utr->data_len = buff_len;
    utr->xfer_len = 0;
    utr->func = cdc_bulk_out_irq;
    bulk_out_done = 0;

    ret = usbh_bulk_xfer(utr);
    if (ret < 0)
    {
        CDC_DBGMSG("Error - failed to submit bulk in request (%d)", ret);
        free_utr(utr);
        return ret;
    }

    t0 = get_ticks();
    while (bulk_out_done == 0)
    {
        if (get_ticks() - t0 > USB_XFER_TIMEOUT)
        {
            usbh_quit_utr(utr);
            free_utr(utr);
            return USBH_ERR_TIMEOUT;
        }
    }

    free_utr(utr);
    return 0;
}

/*@}*/ /* end of group USBH_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group USBH_Library */

/*@}*/ /* end of group Library */


/*** (C) COPYRIGHT 2018~2019 Nuvoton Technology Corp. ***/


