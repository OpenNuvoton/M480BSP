/**************************************************************************//**
 * @file     msc_xfer.c
 * @version  V1.00
 * @brief    Lightweight USB mass storage class transfer layer
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "NuMicro.h"
#include "diskio.h"                // FATFS header
#include "usb.h"
#include "msc.h"


static int __tag = 0x10e24388;


static void bulk_xfer_done(UTR_T *utr)
{
    // msc_debug_msg("BULK XFER done - %d\n", utr->status);
}

int msc_bulk_transfer(MSC_T *msc, EP_INFO_T *ep, uint8_t *data_buff, int data_len, int timeout_ticks)
{
    UTR_T     *utr;
    uint32_t  t0;
    int       ret;

    utr = alloc_utr(msc->iface->udev);
    if (!utr)
        return USBH_ERR_MEMORY_OUT;

    utr->ep = ep;
    utr->buff = data_buff;
    utr->data_len = data_len;
    utr->xfer_len = 0;
    utr->func = bulk_xfer_done;
    utr->bIsTransferDone = 0;

    ret = usbh_bulk_xfer(utr);
    if (ret < 0)
        return ret;

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
    msc_debug_msg("    <BULK> status: %d, xfer_len: %d\n", utr->status, utr->xfer_len);

    return ret;
}


static int  do_scsi_command(MSC_T *msc, uint8_t *buff, uint32_t data_len, int bIsDataIn, int timeout_ticks)
{
    int   ret;
    struct bulk_cb_wrap  *cmd_blk = &msc->cmd_blk;         /* MSC Bulk-only command block   */
    struct bulk_cs_wrap  *cmd_status = &msc->cmd_status;;  /* MSC Bulk-only command status  */

    cmd_blk->Signature = MSC_CB_SIGN;
    cmd_blk->Tag = __tag++;
    cmd_blk->DataTransferLength = data_len;
    cmd_blk->Lun = msc->lun;

    ret = msc_bulk_transfer(msc, msc->ep_bulk_out, (uint8_t *)cmd_blk, 31, timeout_ticks);
    if (ret < 0)
        return ret;

    msc_debug_msg("    [XFER] MSC CMD OK.\n");

    if (data_len > 0)
    {
        if (bIsDataIn)
            ret = msc_bulk_transfer(msc, msc->ep_bulk_in, buff, data_len, 500);
        else
            ret = msc_bulk_transfer(msc, msc->ep_bulk_out, buff, data_len, 500);
        if (ret < 0)
            return ret;
        msc_debug_msg("    [XFER] MSC DATA OK.\n");
    }

    ret = msc_bulk_transfer(msc, msc->ep_bulk_in, (uint8_t *)cmd_status, 13, timeout_ticks);
    if (ret < 0)
        return ret;

    msc_debug_msg("    [XFER] MSC STATUS OK.\n");

    if (cmd_status->Status != 0)
    {
        msc_debug_msg("    !! CSW status error.\n");
        return UMAS_ERR_CMD_STATUS;
    }
    msc_debug_msg("    [CSW] status OK.\n");

    msc_debug_msg("SCSI command 0x%0x done.\n", cmd_blk->CDB[0]);
    return 0;
}


int  run_scsi_command(MSC_T *msc, uint8_t *buff, uint32_t data_len, int bIsDataIn, int timeout_ticks)
{
    return do_scsi_command(msc, buff, data_len, bIsDataIn, timeout_ticks);
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/


