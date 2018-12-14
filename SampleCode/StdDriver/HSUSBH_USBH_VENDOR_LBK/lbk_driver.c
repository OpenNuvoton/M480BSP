/**************************************************************************//**
 * @file     lbk_driver.c
 * @version  1.0.1
 * @brief    M480 MCU USB Host Vendor LBK driver
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "NuMicro.h"

#include "usb.h"
#include "usbh_lib.h"
#include "lbk_driver.h"


typedef struct lbk_device_t
{
    UDEV_T       *udev;
    IFACE_T      *iface;
    EP_INFO_T    *ep_bulk_in;
    EP_INFO_T    *ep_bulk_out;
    EP_INFO_T    *ep_int_in;
    EP_INFO_T    *ep_int_out;
    EP_INFO_T    *ep_iso_in;
    EP_INFO_T    *ep_iso_out;
    INT_CB_FUNC  *int_in_func;
    INT_CB_FUNC  *int_out_func;
    ISO_CB_FUNC  *iso_in_func;
    ISO_CB_FUNC  *iso_out_func;
    UTR_T        *utr_int_in[2];
    uint8_t      buff_int_in[2][512];
    UTR_T        *utr_int_out[2];
    uint8_t      buff_int_out[2][512];
    UTR_T        *utr_iso_in[ISO_UTR_NUM];
    UTR_T        *utr_iso_out[ISO_UTR_NUM];
}  LBK_DEV_T;

volatile struct lbk_device_t  g_lbk_dev;


/*
 *  Issue a vendor command REQ_SET_DATA to send data to Vendor LBK device.
 *  Use control-in transfer.
 */
int  lbk_vendor_set_data(uint8_t *buff)
{
    uint32_t   xfer_len = 0;
    int        ret;

    if (g_lbk_dev.udev == NULL)
        return -1;

    ret = usbh_ctrl_xfer(g_lbk_dev.udev,
                         REQ_TYPE_OUT | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_DEV,  /* bmRequestType  */
                         REQ_SET_DATA,                  /* bRequest                              */
                         0,                             /* wValue: not used in this command      */
                         0,                             /* wIndex: not used in this command      */
                         64,                            /* wLength: this command always send 64 bytes  */
                         buff,                          /* data buffer                           */
                         &xfer_len,                     /* actual length of data send            */
                         100);

    if ((ret < 0) || (xfer_len != 64))
    {
        printf("REQ_SET_DATA command failed! %d, %d\n", ret, xfer_len);
        return ret;
    }
    return 0;
}

/*
 *  Issue a vendor command REQ_GET_DATA to get data from Vendor LBK device.
 *  Use control-out transfer.
 */
int  lbk_vendor_get_data(uint8_t *buff)
{
    uint32_t   xfer_len = 0;
    int        ret;

    if (g_lbk_dev.udev == NULL)
        return -1;

    ret = usbh_ctrl_xfer(g_lbk_dev.udev,
                         REQ_TYPE_IN | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_DEV,   /* bmRequestType  */
                         REQ_GET_DATA,                  /* bRequest                              */
                         0,                             /* wValue: not used in this command      */
                         0,                             /* wIndex: not used in this command      */
                         64,                            /* wLength: this command always get 64 bytes  */
                         buff,                          /* data buffer                           */
                         &xfer_len,                     /* actual length of data received        */
                         100);

    if ((ret < 0) || (xfer_len != 64))
    {
        printf("REQ_GET_DATA command failed! %d, %d\n", ret, xfer_len);
        return ret;
    }
    return 0;
}

/*
 *  Write a block of data to Vendor LBK device.
 *  Use bulk-out transfer.
 */
int lbk_bulk_write(uint8_t *data_buff, int data_len, int timeout_ticks)
{
    UTR_T     *utr;
    uint32_t  t0;
    int       ret;

    if ((g_lbk_dev.udev == NULL) || (g_lbk_dev.ep_bulk_out == NULL))
        return -1;

    utr = alloc_utr(g_lbk_dev.udev);
    if (!utr)
        return USBH_ERR_MEMORY_OUT;

    utr->ep = g_lbk_dev.ep_bulk_out;
    utr->buff = data_buff;
    utr->data_len = data_len;
    utr->xfer_len = 0;
    utr->func = NULL;
    utr->bIsTransferDone = 0;

    ret = usbh_bulk_xfer(utr);
    if (ret < 0)
    {
        free_utr(utr);
        return ret;
    }

    t0 = get_ticks();
    while (utr->bIsTransferDone == 0)
    {
        if (get_ticks() - t0 > timeout_ticks)
        {
            usbh_quit_utr(utr);
            free_utr(utr);
            return USBH_ERR_TIMEOUT;
        }
    }
    ret = utr->status;
    free_utr(utr);
    return ret;
}

/*
 *  Read a block of data from Vendor LBK device.
 *  Use bulk-in transfer.
 */
int lbk_bulk_read(uint8_t *data_buff, int data_len, int timeout_ticks)
{
    UTR_T     *utr;
    uint32_t  t0;
    int       ret;

    if ((g_lbk_dev.udev == NULL) || (g_lbk_dev.ep_bulk_in == NULL))
        return -1;

    utr = alloc_utr(g_lbk_dev.udev);
    if (!utr)
        return USBH_ERR_MEMORY_OUT;

    utr->ep = g_lbk_dev.ep_bulk_in;
    utr->buff = data_buff;
    utr->data_len = data_len;
    utr->xfer_len = 0;
    utr->func = NULL;
    utr->bIsTransferDone = 0;

    ret = usbh_bulk_xfer(utr);
    if (ret < 0)
    {
        free_utr(utr);
        return ret;
    }

    t0 = get_ticks();
    while (utr->bIsTransferDone == 0)
    {
        if (get_ticks() - t0 > timeout_ticks)
        {
            usbh_quit_utr(utr);
            free_utr(utr);
            return USBH_ERR_TIMEOUT;
        }
    }
    ret = utr->status;
    free_utr(utr);
    return ret;
}

static void  int_in_done(UTR_T *utr)
{
    int         ret;

    //printf("int_in_done. %d\n", utr->xfer_len);
    if (g_lbk_dev.int_in_func == NULL)
        goto err_out;           /* interrupt-in stopped */

    if (utr->status != 0)
    {
        g_lbk_dev.int_in_func(utr->status, utr->buff, utr->xfer_len);
        printf("int_in_done - stop or error: 0x%x\n", utr->status);
        goto err_out;
    }

    if (g_lbk_dev.int_in_func && utr->xfer_len)
        g_lbk_dev.int_in_func(utr->status, utr->buff, utr->xfer_len);

    utr->xfer_len = 0;
    ret = usbh_int_xfer(utr);
    if (ret != 0)
    {
        printf("int_in_done - failed to re-submit interrupt-in request (%d)", ret);
        g_lbk_dev.int_in_func(ret, utr->buff, 0);
        goto err_out;
    }
    return;

err_out:
    if (utr == g_lbk_dev.utr_int_in[0])
    {
        free_utr(g_lbk_dev.utr_int_in[0]);
        g_lbk_dev.utr_int_in[0] = NULL;
    }
    else if (utr == g_lbk_dev.utr_int_in[1])
    {
        free_utr(g_lbk_dev.utr_int_in[1]);
        g_lbk_dev.utr_int_in[1] = NULL;
    }
}

/*
 *  Start interrupt-in transfer on Vendor LBK device.
 */
int lbk_interrupt_in_start(INT_CB_FUNC *func)
{
    UTR_T     *utr;
    int       i, ret;

    if ((g_lbk_dev.udev == NULL) || (g_lbk_dev.ep_int_in == NULL) || (func == NULL))
        return -1;

    for (i = 0; i < 2; i++)
    {
        utr = alloc_utr(g_lbk_dev.udev);
        if (!utr)
            return USBH_ERR_MEMORY_OUT;

        utr->ep = g_lbk_dev.ep_int_in;
        utr->buff = (uint8_t *)g_lbk_dev.buff_int_in[i];
        utr->data_len = utr->ep->wMaxPacketSize;
        utr->xfer_len = 0;
        utr->func = int_in_done;
        g_lbk_dev.int_in_func = func;
        g_lbk_dev.utr_int_in[i] = utr;

        ret = usbh_int_xfer(utr);
        if (ret < 0)
        {
            //printf("Error - failed to submit interrupt-in transfer (%d)\n", ret);
            free_utr(utr);
            g_lbk_dev.utr_int_in[i] = NULL;
            return ret;
        }
    }
    return 0;
}

void lbk_interrupt_in_stop(void)
{
    int   i;

    /* clear <int_in_func> to stop cascading transfers */
    g_lbk_dev.int_in_func = NULL;
    delay_us(32000);

    for (i = 0; i < 2; i++)
    {
        if (g_lbk_dev.utr_int_in[i] != NULL)
        {
            usbh_quit_utr(g_lbk_dev.utr_int_in[i]);    /* force to stop the transfer   */
            delay_us(32000);
            free_utr(g_lbk_dev.utr_int_in[i]);
            g_lbk_dev.utr_int_in[i] = NULL;
        }
    }
}

static void  int_out_done(UTR_T *utr)
{
    int         ret;

    //printf("int_out_done. %d\n", utr->xfer_len);
    if (g_lbk_dev.int_out_func == NULL)
        goto err_out;              /* interrupt-out stopped */

    if (utr->status != 0)
    {
        printf("int_out_done - stop or error: 0x%x\n", utr->status);
        utr->data_len = g_lbk_dev.int_out_func(utr->status, utr->buff, utr->ep->wMaxPacketSize);
        goto err_out;
    }

    /* callback to prepare data for next interrupt out trasnfer */
    if (g_lbk_dev.int_out_func)
        utr->data_len = g_lbk_dev.int_out_func(0, utr->buff, utr->ep->wMaxPacketSize);

    utr->xfer_len = 0;
    ret = usbh_int_xfer(utr);
    if (ret != 0)
    {
        printf("int_out_done - failed to re-submit interrupt-out request (%d)", ret);
        g_lbk_dev.int_out_func(-1, utr->buff, 0);
        goto err_out;
    }
    return;

err_out:
    if (utr == g_lbk_dev.utr_int_out[0])
    {
        free_utr(g_lbk_dev.utr_int_out[0]);
        g_lbk_dev.utr_int_out[0] = NULL;
    }
    else if (utr == g_lbk_dev.utr_int_out[1])
    {
        free_utr(g_lbk_dev.utr_int_out[1]);
        g_lbk_dev.utr_int_out[1] = NULL;
    }
}

/*
 *  Start interrupt-in transfer on Vendor LBK device.
 */
int lbk_interrupt_out_start(INT_CB_FUNC *func)
{
    UTR_T     *utr;
    int       i, ret;

    if ((g_lbk_dev.udev == NULL) || (g_lbk_dev.ep_int_out == NULL) || (func == NULL))
        return -1;

    for (i = 0; i < 2; i++)
    {
        utr = alloc_utr(g_lbk_dev.udev);
        if (!utr)
            return USBH_ERR_MEMORY_OUT;

        utr->ep = g_lbk_dev.ep_int_out;
        utr->buff = (uint8_t *)g_lbk_dev.buff_int_out[i];
        utr->xfer_len = 0;
        utr->func = int_out_done;
        g_lbk_dev.int_out_func = func;
        g_lbk_dev.utr_int_out[i] = utr;
        utr->data_len = g_lbk_dev.int_out_func(0, utr->buff, utr->ep->wMaxPacketSize);

        ret = usbh_int_xfer(utr);
        if (ret < 0)
        {
            //printf("Error - failed to submit interrupt-out transfer (%d)\n", ret);
            free_utr(utr);
            g_lbk_dev.utr_int_out[i] = NULL;
            return ret;
        }
    }
    return 0;
}

void lbk_interrupt_out_stop(void)
{
    int   i;

    /* clear <int_in_func> to stop cascading transfers */
    g_lbk_dev.int_out_func = NULL;
    delay_us(32000);

    for (i = 0; i < 2; i++)
    {
        if (g_lbk_dev.utr_int_out[i] != NULL)
        {
            usbh_quit_utr(g_lbk_dev.utr_int_out[i]);    /* force to stop the transfer   */
            delay_us(32000);
            free_utr(g_lbk_dev.utr_int_out[i]);
            g_lbk_dev.utr_int_out[i] = NULL;
        }
    }
}

static void iso_in_done(UTR_T *utr)
{
    int         i, ret;

    //printf("SF=%d, 0x%x\n", utr->iso_sf, (int)utr);
    if (!g_lbk_dev.iso_in_func)
        return;

    utr->bIsoNewSched = 0;

    for (i = 0; i < IF_PER_UTR; i++)
    {
        if (utr->iso_status[i] == 0)
        {
            if (g_lbk_dev.iso_in_func && (utr->iso_xlen[i] > 0))
                g_lbk_dev.iso_in_func(utr->buff, utr->xfer_len);
        }
        else
        {
            if ((utr->iso_status[i] == USBH_ERR_NOT_ACCESS0) || (utr->iso_status[i] == USBH_ERR_NOT_ACCESS1))
                utr->bIsoNewSched = 1;
            else
            {
                // printf("Iso %d err - %d\n", i, utr->iso_status[i]);
            }
        }
        utr->iso_xlen[i] = utr->ep->wMaxPacketSize;
    }

    /* schedule the following isochronous transfers */
    ret = usbh_iso_xfer(utr);
    if (ret < 0)
        printf("isochronous-in re-submit failed!\n");
}

/*
 *  Start isochronous-in transfer on Vendor LBK device.
 */
int lbk_isochronous_in_start(ISO_CB_FUNC *func)
{
    UTR_T        *utr;
    EP_INFO_T    *ep;
    uint8_t      *buff;
    int          i, j, ret;

    g_lbk_dev.iso_in_func = func;
    ep = g_lbk_dev.ep_iso_in;

    if ((ep == NULL) || (func == NULL))
        return -1;

    /*------------------------------------------------------------------------------------*/
    /*  Allocate isochronous in buffer                                                    */
    /*------------------------------------------------------------------------------------*/
    for (i = 0; i < ISO_UTR_NUM; i++)       /* allocate UTRs                              */
    {
        g_lbk_dev.utr_iso_in[i] = alloc_utr(g_lbk_dev.udev);      /* allocate UTR         */
        if (g_lbk_dev.utr_iso_in[i] == NULL)
        {
            printf("Memory not enough! Please increase the UTR number.\n");
            ret = USBH_ERR_MEMORY_OUT;      /* memory allocate failed                     */
            goto err_out;                   /* abort                                      */
        }
    }

    buff = (uint8_t *)usbh_alloc_mem(ep->wMaxPacketSize * IF_PER_UTR * ISO_UTR_NUM);
    if (buff == NULL)
    {
        printf("Memory not enough! Please increase the heap size.\n");
        ret = USBH_ERR_MEMORY_OUT;          /* memory allocate failed                     */
        goto err_out;                       /* abort                                      */
    }

    for (i = 0; i < ISO_UTR_NUM; i++)       /* dispatch buffers                           */
    {
        /* divide buffer equally                      */
        utr = g_lbk_dev.utr_iso_in[i];
        utr->buff = buff + (ep->wMaxPacketSize * IF_PER_UTR * i);
        utr->data_len = ep->wMaxPacketSize * IF_PER_UTR;
        for (j = 0; j < IF_PER_UTR; j++)
        {
            utr->iso_xlen[j] = ep->wMaxPacketSize;
            utr->iso_buff[j] = utr->buff + (ep->wMaxPacketSize * j);
        }
    }

    /*------------------------------------------------------------------------------------*/
    /*  Start UTRs                                                                        */
    /*------------------------------------------------------------------------------------*/

    g_lbk_dev.utr_iso_in[0]->bIsoNewSched = 1;

    for (i = 0; i < ISO_UTR_NUM; i++)
    {
        utr = g_lbk_dev.utr_iso_in[i];
        utr->ep = ep;
        utr->func = iso_in_done;
        ret = usbh_iso_xfer(utr);
        if (ret < 0)
        {
            printf("Error - failed to start UTR %d isochronous-in transfer (%d)", i, ret);
            goto err_out;
        }
    }
    return 0;

err_out:

    for (i = 0; i < ISO_UTR_NUM; i++)           /* quit all UTRs                              */
    {
        if (g_lbk_dev.utr_iso_in[i])
            usbh_quit_utr(g_lbk_dev.utr_iso_in[i]);
    }

    /* free USB transfer buffer                   */
    if ((g_lbk_dev.utr_iso_in[0] != NULL) &&
            (g_lbk_dev.utr_iso_in[0]->buff != NULL))
        usbh_free_mem(g_lbk_dev.utr_iso_in[0]->buff, g_lbk_dev.utr_iso_in[0]->data_len * ISO_UTR_NUM);

    for (i = 0; i < ISO_UTR_NUM; i++)           /* free all UTRs                              */
    {
        if (g_lbk_dev.utr_iso_in[i])
            free_utr(g_lbk_dev.utr_iso_in[i]);
        g_lbk_dev.utr_iso_in[i] = NULL;
    }
    return ret;
}

void lbk_isochronous_in_stop(void)
{
    int          i;

    /* clear <iso_in_func> to stop cascading transfers */
    g_lbk_dev.iso_in_func = NULL;

    for (i = 0; i < ISO_UTR_NUM; i++)       /* stop all UTRs                              */
    {
        if (g_lbk_dev.utr_iso_in[i])
            usbh_quit_utr(g_lbk_dev.utr_iso_in[i]);
    }

    if ((g_lbk_dev.utr_iso_in[0] != NULL) &&
            (g_lbk_dev.utr_iso_in[0]->buff != NULL))       /* free audio buffer                */
        usbh_free_mem(g_lbk_dev.utr_iso_in[0]->buff, g_lbk_dev.utr_iso_in[0]->data_len * ISO_UTR_NUM);

    for (i = 0; i < ISO_UTR_NUM; i++)       /* free all UTRs                              */
    {
        if (g_lbk_dev.utr_iso_in[i])
            free_utr(g_lbk_dev.utr_iso_in[i]);
        g_lbk_dev.utr_iso_in[i] = NULL;
    }
}

static void iso_out_done(UTR_T *utr)
{
    int   i, ret;
    //printf("SF=%d, 0x%x\n", utr->iso_sf, (int)utr);

    if (!g_lbk_dev.iso_out_func)
        return;

    utr->bIsoNewSched = 0;

    for (i = 0; i < IF_PER_UTR; i++)
    {
        if (utr->iso_status[i] != 0)
        {
            // printf("Iso %d err - %d\n", i, utr->iso_status[i]);
            if ((utr->iso_status[i] == USBH_ERR_NOT_ACCESS0) || (utr->iso_status[i] == USBH_ERR_NOT_ACCESS1))
                utr->bIsoNewSched = 1;
        }
        if (g_lbk_dev.iso_out_func)
            utr->iso_xlen[i] = g_lbk_dev.iso_out_func(utr->iso_buff[i], utr->ep->wMaxPacketSize);
    }

    /* schedule the following isochronous transfers */
    ret = usbh_iso_xfer(utr);
    if (ret < 0)
        printf("isochronous-out re-submit failed!\n");
}

/*
 *  Start isochronous-out transfer on Vendor LBK device.
 */
int lbk_isochronous_out_start(ISO_CB_FUNC *func)
{
    EP_INFO_T    *ep;
    UTR_T        *utr;
    uint8_t      *buff;
    int          i, j, ret;

    g_lbk_dev.iso_out_func = func;
    ep = g_lbk_dev.ep_iso_out;

    if ((ep == NULL) || (func == NULL))
        return -1;

    /*------------------------------------------------------------------------------------*/
    /*  Allocate isochronous in buffer                                                    */
    /*------------------------------------------------------------------------------------*/
    for (i = 0; i < ISO_UTR_NUM; i++)       /* allocate UTRs                              */
    {
        g_lbk_dev.utr_iso_out[i] = alloc_utr(g_lbk_dev.udev);     /* allocate UTR         */
        if (g_lbk_dev.utr_iso_out[i] == NULL)
        {
            printf("Memory not enough! Please increase the UTR number.\n");
            ret = USBH_ERR_MEMORY_OUT;      /* memory allocate failed                     */
            goto err_out;                   /* abort                                      */
        }
    }

    buff = (uint8_t *)usbh_alloc_mem(ep->wMaxPacketSize * IF_PER_UTR * ISO_UTR_NUM);
    if (buff == NULL)
    {
        printf("Memory not enough! Please increase the heap size.\n");
        ret = USBH_ERR_MEMORY_OUT;          /* memory allocate failed                     */
        goto err_out;                       /* abort                                      */
    }

    for (i = 0; i < ISO_UTR_NUM; i++)           /* dispatch buffers                           */
    {
        /* divide buffer equally                      */
        g_lbk_dev.utr_iso_out[i]->buff = buff + (ep->wMaxPacketSize * IF_PER_UTR * i);
        g_lbk_dev.utr_iso_out[i]->data_len = ep->wMaxPacketSize * IF_PER_UTR;
    }

    /*------------------------------------------------------------------------------------*/
    /*  Start UTRs                                                                        */
    /*------------------------------------------------------------------------------------*/

    g_lbk_dev.utr_iso_out[0]->bIsoNewSched = 1;

    for (i = 0; i < ISO_UTR_NUM; i++)
    {
        utr = g_lbk_dev.utr_iso_out[i];
        utr->ep = ep;
        utr->func = iso_out_done;

        for (j = 0; j < IF_PER_UTR; j++)    /* get audio out data from user               */
        {
            utr->iso_buff[j] = utr->buff + (ep->wMaxPacketSize * j);
            utr->iso_xlen[j] = g_lbk_dev.iso_out_func(utr->iso_buff[j], ep->wMaxPacketSize);
        }

        ret = usbh_iso_xfer(utr);
        if (ret < 0)
        {
            printf("Error - failed to start UTR %d isochronous-in transfer (%d)", i, ret);
            goto err_out;
        }
    }
    return 0;

err_out:

    for (i = 0; i < ISO_UTR_NUM; i++)           /* quit all UTRs                              */
    {
        if (g_lbk_dev.utr_iso_out[i])
            usbh_quit_utr(g_lbk_dev.utr_iso_out[i]);
    }

    if ((g_lbk_dev.utr_iso_out[0] != NULL) &&           /* free USB transfer buffer                   */
            (g_lbk_dev.utr_iso_out[0]->buff != NULL))
        usbh_free_mem(g_lbk_dev.utr_iso_out[0]->buff, g_lbk_dev.utr_iso_out[0]->data_len * ISO_UTR_NUM);

    for (i = 0; i < ISO_UTR_NUM; i++)           /* free all UTRs                              */
    {
        if (g_lbk_dev.utr_iso_out[i])
            free_utr(g_lbk_dev.utr_iso_out[i]);
        g_lbk_dev.utr_iso_out[i] = NULL;
    }
    return ret;
}

void lbk_isochronous_out_stop(void)
{
    int          i;

    /* clear <iso_out_func> to stop cascading transfers */
    g_lbk_dev.iso_out_func = NULL;

    for (i = 0; i < ISO_UTR_NUM; i++)           /* stop all UTRs                              */
    {
        if (g_lbk_dev.utr_iso_out[i])
            usbh_quit_utr(g_lbk_dev.utr_iso_out[i]);
    }

    if ((g_lbk_dev.utr_iso_out[0] != NULL) &&
            (g_lbk_dev.utr_iso_out[0]->buff != NULL))       /* free transfer buffer           */
        usbh_free_mem(g_lbk_dev.utr_iso_out[0]->buff, g_lbk_dev.utr_iso_out[0]->data_len * ISO_UTR_NUM);

    for (i = 0; i < ISO_UTR_NUM; i++)           /* free all UTRs                              */
    {
        if (g_lbk_dev.utr_iso_out[i])
            free_utr(g_lbk_dev.utr_iso_out[i]);
        g_lbk_dev.utr_iso_out[i] = NULL;
    }
}

static int lbk_probe(IFACE_T *iface)
{
    UDEV_T       *udev = iface->udev;
    ALT_IFACE_T  *aif = iface->aif;
    DESC_IF_T    *ifd;              /* interface descriptor */
    int          i;

    ifd = aif->ifd;

    if ((udev->descriptor.idVendor != LBK_VENDOR_ID) || (udev->descriptor.idProduct != LBK_DEVICE_ID))
    {
        printf("Not Vendor LBK device. Ignore this device.\n");
        return USBH_ERR_NOT_MATCHED;
    }

    /* Is this interface HID class? */
    if ((ifd->bInterfaceClass != 0xFF) || (ifd->bInterfaceSubClass != 0xFF))
    {
        printf("Not Vendor LBK interface. Ignore this interface.\n");
        return USBH_ERR_NOT_MATCHED;
    }

    if (g_lbk_dev.udev != NULL)
    {
        printf("A Vendor LBK device is connected, do not support multiple devices!\n");
        return USBH_ERR_NOT_MATCHED;
    }

    printf("lbk_probe - device found (vid=0x%x, pid=0x%x), interface %d.\n",
           udev->descriptor.idVendor, udev->descriptor.idProduct, ifd->bInterfaceNumber);

    /*
     *  Find all endpoints of LBK device
     */
    for (i = 0; i < aif->ifd->bNumEndpoints; i++)
    {
        if ((aif->ep[i].bmAttributes & EP_ATTR_TT_MASK) == EP_ATTR_TT_BULK)
        {
            printf("Bulk-%s endpoint: 0x%x\n", ((aif->ep[i].bEndpointAddress & EP_ADDR_DIR_MASK) == EP_ADDR_DIR_IN) ? "in" : "out", aif->ep[i].bEndpointAddress);
            if ((aif->ep[i].bEndpointAddress & EP_ADDR_DIR_MASK) == EP_ADDR_DIR_IN)
                g_lbk_dev.ep_bulk_in = &aif->ep[i];
            else
                g_lbk_dev.ep_bulk_out = &aif->ep[i];
        }
        else if ((aif->ep[i].bmAttributes & EP_ATTR_TT_MASK) == EP_ATTR_TT_INT)
        {
            printf("Interrupt-%s endpoint: 0x%x\n", ((aif->ep[i].bEndpointAddress & EP_ADDR_DIR_MASK) == EP_ADDR_DIR_IN) ? "in" : "out", aif->ep[i].bEndpointAddress);
            if ((aif->ep[i].bEndpointAddress & EP_ADDR_DIR_MASK) == EP_ADDR_DIR_IN)
                g_lbk_dev.ep_int_in = &aif->ep[i];
            else
                g_lbk_dev.ep_int_out = &aif->ep[i];
        }
        else if ((aif->ep[i].bmAttributes & EP_ATTR_TT_MASK) == EP_ATTR_TT_ISO)
        {
            printf("Isochronous-%s endpoint: 0x%x\n", ((aif->ep[i].bEndpointAddress & EP_ADDR_DIR_MASK) == EP_ADDR_DIR_IN) ? "in" : "out", aif->ep[i].bEndpointAddress);
            if ((aif->ep[i].bEndpointAddress & EP_ADDR_DIR_MASK) == EP_ADDR_DIR_IN)
                g_lbk_dev.ep_iso_in = &aif->ep[i];
            else
                g_lbk_dev.ep_iso_out = &aif->ep[i];
        }
    }
    g_lbk_dev.udev = udev;
    g_lbk_dev.iface = iface;
    return 0;
}

static void  lbk_disconnect(IFACE_T *iface)
{
    int   i;

    lbk_interrupt_in_stop();
    lbk_interrupt_out_stop();
    lbk_isochronous_in_stop();
    lbk_isochronous_out_stop();

    for (i = 0; i < iface->aif->ifd->bNumEndpoints; i++)
    {
        iface->udev->hc_driver->quit_xfer(NULL, &(iface->aif->ep[i]));
    }
    memset((void *)&g_lbk_dev, 0, sizeof(g_lbk_dev));
}

UDEV_DRV_T  lbk_driver =
{
    lbk_probe,
    lbk_disconnect,
    NULL,                       /* suspend */
    NULL,                       /* resume */
};

/// @endcond /* HIDDEN_SYMBOLS */


/**
  * @brief    Initialize USB Host Vendor LBK driver.
  * @return   None
  */
void usbh_lbk_init(void)
{
    memset((void *)&g_lbk_dev, 0, sizeof(g_lbk_dev));
    usbh_register_driver(&lbk_driver);
}

/**
  * @brief    Is the Vendor LBK device currently connected?
  * @return   1: yes
  *           0: no
  */
int lbk_device_is_connected(void)
{
    usbh_pooling_hubs();

    if (g_lbk_dev.udev != NULL)
        return 1;
    else
        return 0;
}

/**
  * @brief    Is the Vendor LBK device in high speed mode?
  * @return   1: yes
  *           0: no
  *          -1: Not connected
  */
int lbk_device_is_high_speed(void)
{
    usbh_pooling_hubs();

    if (g_lbk_dev.udev == NULL)
        return -1;

    if (g_lbk_dev.udev->speed == SPEED_HIGH)
        return 1;
    else
        return 0;
}

int lbk_device_reset(void)
{
    if (g_lbk_dev.udev != NULL)
        return usbh_reset_device(g_lbk_dev.udev);
    return 0;
}

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/

