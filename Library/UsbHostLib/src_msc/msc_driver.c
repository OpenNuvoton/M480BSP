/**************************************************************************//**
 * @file     msc_driver.c
 * @version  V1.00
 * @brief    Lightweight USB mass storage class driver
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
#include "ff.h"
#include "diskio.h"


/// @cond HIDDEN_SYMBOLS


MSC_T  *g_msc_list;       /* Global list of Mass Storage Class device. A multi-lun device can have
                             several instances appeared with different lun. */

static volatile uint8_t  g_fat_drv_used[USBDRV_CNT];
static TCHAR    _path[3] = { '3', ':', 0 };

static void  fatfs_drive_int()
{
    memset((uint8_t *)g_fat_drv_used, 0, sizeof(g_fat_drv_used));
}

static int fatfs_drive_alloc()
{
    int  i;

    for (i = 0; i < USBDRV_CNT; i++)
    {
        if (g_fat_drv_used[i] == 0)
        {
            g_fat_drv_used[i] = 1;
            return USBDRV_0+i;
        }
    }
    msc_debug_msg("Memory out! No free FATFS USB drive slots!\n");
    return USBH_ERR_MEMORY_OUT;
}

static void  fatfs_drive_free(int drv_no)
{
    _path[0] =  drv_no + '0';
    f_mount(NULL, _path, 1);
    g_fat_drv_used[drv_no-USBDRV_0] = 0;
}

static MSC_T * find_msc_by_drive(int drv_no)
{
    MSC_T  *msc = g_msc_list;

    while (msc != NULL)
    {
        if (msc->drv_no == drv_no)
            return msc;
        msc = msc->next;
    }
    return NULL;
}

static void msc_list_add(MSC_T *msc)
{
    if (g_msc_list == NULL)
    {
        msc->next = NULL;
        g_msc_list = msc;
    }
    else
    {
        msc->next = g_msc_list;
        g_msc_list = msc;
    }
}

static void msc_list_remove(MSC_T *msc)
{
    MSC_T   *p;

    if (g_msc_list == msc)
    {
        g_msc_list = msc->next;
    }
    else
    {
        p = g_msc_list;
        while ((p->next != msc) && (p->next != NULL))
        {
            p = p->next;
        }

        if (p->next == msc)
        {
            p->next = msc->next;
        }
    }
}


static void get_max_lun(MSC_T *msc)
{
    UDEV_T    *udev = msc->iface->udev;
    uint32_t  read_len;
    uint8_t   buff[2];
    int       ret;

    msc->max_lun = 0;

    /*------------------------------------------------------------------------------------*/
    /* Issue GET MAXLUN MSC class command to get the maximum lun number                   */
    /*------------------------------------------------------------------------------------*/
    ret = usbh_ctrl_xfer(udev, REQ_TYPE_IN | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_IFACE,
                         0xFE, 0, 0, msc->iface->if_num, buff, &read_len, 200);
    if (ret < 0)
    {
        msc_debug_msg("Get Max Lun command failed! Assign 0...\n");
        msc->max_lun = 0;
        if (ret == USBH_ERR_STALL)
            usbh_clear_halt(udev, 0);
        return;
    }
    msc->max_lun = buff[0];
    msc_debug_msg("Max lun is %d\n", msc->max_lun);
}

void msc_reset(MSC_T *msc)
{
    UDEV_T    *udev = msc->iface->udev;
    uint32_t  read_len;
    int       ret;

    msc_debug_msg("Reset MSC device...\n");

    ret = usbh_ctrl_xfer(udev, REQ_TYPE_OUT | REQ_TYPE_CLASS_DEV | REQ_TYPE_TO_IFACE,
                         0xFF, 0, msc->iface->if_num, 0, NULL, &read_len, 100);
    if (ret < 0)
    {
        msc_debug_msg("UAMSS reset request failed!\n");
    }
    usbh_clear_halt(udev, msc->ep_bulk_out->bEndpointAddress);
    usbh_clear_halt(udev, msc->ep_bulk_in->bEndpointAddress);
}

static int  msc_inquiry(MSC_T *msc)
{
    struct bulk_cb_wrap  *cmd_blk = &msc->cmd_blk;         /* MSC Bulk-only command block   */
    int  ret;

    msc_debug_msg("INQUIRY...\n");
    memset(cmd_blk, 0, sizeof(*cmd_blk));

    cmd_blk->Flags   = 0x80;
    cmd_blk->Length  = 6;
    cmd_blk->CDB[0]  = INQUIRY;         /* INQUIRY */
    cmd_blk->CDB[1]  = msc->lun << 5;
    cmd_blk->CDB[4]  = 36;

    ret = run_scsi_command(msc, msc->scsi_buff, 36, 1, 100);
    if (ret < 0)
    {
        msc_debug_msg("INQUIRY command failed. [%d]\n", ret);
        return ret;
    }
    else
    {
        msc_debug_msg("INQUIRY command success.\n");
    }
    return ret;
}

static int  msc_request_sense(MSC_T *msc)
{
    struct bulk_cb_wrap  *cmd_blk = &msc->cmd_blk;         /* MSC Bulk-only command block   */
    int  ret;

    msc_debug_msg("REQUEST_SENSE...\n");
    memset(cmd_blk, 0, sizeof(*cmd_blk));

    cmd_blk->Flags   = 0x80;
    cmd_blk->Length  = 6;
    cmd_blk->CDB[0]  = REQUEST_SENSE;
    cmd_blk->CDB[1]  = msc->lun << 5;
    cmd_blk->CDB[4]  = 18;

    ret = run_scsi_command(msc, msc->scsi_buff, 18, 1, 100);
    if (ret < 0)
    {
        msc_debug_msg("REQUEST_SENSE command failed.\n");
        if (ret == USBH_ERR_STALL)
            msc_reset(msc);
        return ret;
    }
    else
    {
        msc_debug_msg("REQUEST_SENSE command success.\n");
        if (msc->scsi_buff[2] != 0x6)
        {
            msc_debug_msg("Device is still not attention. 0x%x\n", msc->scsi_buff[2]);
            return -1;
        }
    }
    return ret;
}

static int  msc_test_unit_ready(MSC_T *msc)
{
    struct bulk_cb_wrap  *cmd_blk = &msc->cmd_blk;         /* MSC Bulk-only command block   */
    int  ret;

    msc_debug_msg("TEST_UNIT_READY...\n");
    memset(cmd_blk, 0, sizeof(*cmd_blk));

    cmd_blk->Flags   = 0x80;
    cmd_blk->Length  = 6;
    cmd_blk->CDB[0]  = TEST_UNIT_READY;
    cmd_blk->CDB[1]  = msc->lun << 5;

    ret = run_scsi_command(msc, msc->scsi_buff, 0, 1, 100);
    if (ret < 0)
    {
        if (ret == USBH_ERR_STALL)
            msc_reset(msc);
        return ret;
    }
    else
    {
        msc_debug_msg("TEST_UNIT_READY command success.\n");
    }
    return ret;
}

/**
  * @brief       Read a number of contiguous sectors from mass storage device.
  *
  * @param[in]   drv_no    FATFS drive volume number.
  * @param[in]   sec_no    Sector number of the start sector.
  * @param[in]   sec_cnt   Number of sectors to be read.
  * @param[out]  buff      Memory buffer to store data read from disk.
  *
  * @retval      0       Success
  * @retval      - \ref UMAS_ERR_DRIVE_NOT_FOUND   There's no mass storage device mounted to this volume.
  * @retval      - \ref UMAS_ERR_IO      Failed to read disk.
  */
int  usbh_umas_read(int drv_no, uint32_t sec_no, int sec_cnt, uint8_t *buff)
{
    MSC_T   *msc;
    struct bulk_cb_wrap  *cmd_blk;         /* MSC Bulk-only command block   */
    int   ret;

    //msc_debug_msg("usbh_umas_read - %d, %d\n", sec_no, sec_cnt);

    msc = find_msc_by_drive(drv_no);
    if (msc == NULL)
        return UMAS_ERR_DRIVE_NOT_FOUND;

    cmd_blk = &msc->cmd_blk;

    //msc_debug_msg("read sector 0x%x\n", sector_no);
    memset(cmd_blk, 0, sizeof(*cmd_blk));

    cmd_blk->Flags   = 0x80;
    cmd_blk->Length  = 10;
    cmd_blk->CDB[0]  = READ_10;
    cmd_blk->CDB[1]  = msc->lun << 5;
    cmd_blk->CDB[2]  = (sec_no >> 24) & 0xFF;
    cmd_blk->CDB[3]  = (sec_no >> 16) & 0xFF;
    cmd_blk->CDB[4]  = (sec_no >> 8) & 0xFF;
    cmd_blk->CDB[5]  = sec_no & 0xFF;
    cmd_blk->CDB[7]  = (sec_cnt >> 8) & 0xFF;
    cmd_blk->CDB[8]  = sec_cnt & 0xFF;

    ret = run_scsi_command(msc, buff, sec_cnt * 512, 1, 500);
    if (ret != 0)
    {
        msc_debug_msg("usbh_umas_read failed! [%d]\n", ret);
        return UMAS_ERR_IO;
    }
    return 0;
}

/**
  * @brief       Write a number of contiguous sectors to mass storage device.
  *
  * @param[in]   drv_no    FATFS drive volume number.
  * @param[in]   sec_no    Sector number of the start sector.
  * @param[in]   sec_cnt   Number of sectors to be written.
  * @param[in]   buff      Memory buffer hold the data to be written..
  *
  * @retval      0       Success
  * @retval      - \ref UMAS_ERR_DRIVE_NOT_FOUND   There's no mass storage device mounted to this volume.
  * @retval      - \ref UMAS_ERR_IO      Failed to write disk.
  */
int  usbh_umas_write(int drv_no, uint32_t sec_no, int sec_cnt, uint8_t *buff)
{
    MSC_T   *msc;
    struct bulk_cb_wrap  *cmd_blk;         /* MSC Bulk-only command block   */
    int   ret;

    //msc_debug_msg("usbh_umas_write - %d, %d\n", sec_no, sec_cnt);

    msc = find_msc_by_drive(drv_no);
    if (msc == NULL)
        return UMAS_ERR_DRIVE_NOT_FOUND;

    cmd_blk = &msc->cmd_blk;
    memset((uint8_t *)&(msc->cmd_blk), 0, sizeof(msc->cmd_blk));

    cmd_blk->Flags   = 0;
    cmd_blk->Length  = 10;
    cmd_blk->CDB[0]  = WRITE_10;
    cmd_blk->CDB[1]  = msc->lun << 5;
    cmd_blk->CDB[2]  = (sec_no >> 24) & 0xFF;
    cmd_blk->CDB[3]  = (sec_no >> 16) & 0xFF;
    cmd_blk->CDB[4]  = (sec_no >> 8) & 0xFF;
    cmd_blk->CDB[5]  = sec_no & 0xFF;
    cmd_blk->CDB[7]  = (sec_cnt >> 8) & 0xFF;
    cmd_blk->CDB[8]  = sec_cnt & 0xFF;

    ret = run_scsi_command(msc, buff, sec_cnt * 512, 0, 500);
    if (ret < 0)
    {
        msc_debug_msg("usbh_umas_write failed!\n");
        return UMAS_ERR_IO;
    }
    return 0;
}

/**
  * @brief       Get information from USB disk volume.
  *
  * @param[in]   drv_no    FATFS drive volume number.
  * @param[in]   cmd       FATFS disk ioctl command.
  * @param[out]  buff      Memory buffer to store information.
  *
  * @retval      - \ref UMAS_OK              Mass storage device is ready.
  * @retval      - \ref UMAS_ERR_DRIVE_NOT_FOUND   There's no mass storage device mounted to this volume.
  * @retval      - \ref UMAS_ERR_IVALID_PARM       Failed to write disk.
  */
int  usbh_umas_ioctl(int drv_no, int cmd, void *buff)
{
    MSC_T   *msc;

    msc = find_msc_by_drive(drv_no);
    if (msc == NULL)
        return UMAS_ERR_DRIVE_NOT_FOUND;

    switch (cmd)
    {
    case CTRL_SYNC:
        return RES_OK;

    case GET_SECTOR_COUNT:
        *(uint32_t *)buff = msc->uTotalSectorN;
        return RES_OK;

    case GET_SECTOR_SIZE:
        *(uint32_t *)buff = msc->nSectorSize;
        return RES_OK;

    case GET_BLOCK_SIZE:
        *(uint32_t *)buff = msc->nSectorSize;
        return RES_OK;

        //case CTRL_ERASE_SECTOR:
        //    return RES_OK;
    }
    return UMAS_ERR_IVALID_PARM;
}

/**
 *  @brief    Get USB disk status of specified drive.
 *  @param[in] drv_no    USB disk drive number.
 *  @retval    0          Disk is ready.
 *  @retval    Otherwise  Disk not found or not ready.
 */
int  usbh_umas_disk_status(int drv_no)
{
    if (find_msc_by_drive(drv_no) == NULL)
        return STA_NODISK;
    return 0;
}

/**
 *  @brief    Reset a connected USB mass storage device.
 *  @param[in] drv_no    USB disk drive number.
 *  @retval    0          Succes
 *  @retval    Otherwise  Failed
 */
int  usbh_umas_reset_disk(int drv_no)
{
    MSC_T      *msc;
    UDEV_T     *udev;

    msc_debug_msg("usbh_umas_reset_disk ...\n");

    msc = find_msc_by_drive(drv_no);
    if (msc == NULL)
        return UMAS_ERR_DRIVE_NOT_FOUND;

    udev = msc->iface->udev;

    usbh_reset_device(udev);

    return 0;
}

static int  umass_init_device(MSC_T *msc)
{
    MSC_T     *try_msc = msc;
    struct bulk_cb_wrap  *cmd_blk;         /* MSC Bulk-only command block   */
    int       retries, lun;
    int8_t    bHasMedia = 0;
    int       ret = USBH_ERR_NOT_FOUND;

    for (lun = 0; lun <= msc->max_lun; lun++)
    {
        msc_debug_msg("\n******* Read lun %d ******\n\n", lun);

        try_msc->lun = lun;
        cmd_blk = &try_msc->cmd_blk;

        for (retries = 0; retries < 3; retries++)
        {
            if (msc_inquiry(try_msc) == USBH_ERR_STALL)
                msc_reset(try_msc);

            if (msc_inquiry(try_msc) == USBH_ERR_STALL)
                msc_reset(try_msc);

            if (msc_test_unit_ready(try_msc) == 0)
                goto disk_found;

            if (msc_request_sense(try_msc) == 0)
            {
                goto disk_found;
            }

            delay_us(100000);       /* delay 100ms, retry later       */
        }

        continue;

disk_found:
        /*
         *  Valid disk found in this lun. Go...
         */
        for (retries = 0; retries < 3; retries++)
        {
            msc_debug_msg("READ CAPACITY ==>\n");

            memset(cmd_blk, 0, sizeof(*cmd_blk));

            cmd_blk->Flags   = 0x80;
            cmd_blk->Length  = 10;
            cmd_blk->CDB[0]  = READ_CAPACITY;
            cmd_blk->CDB[1]  = lun << 5;

            ret = run_scsi_command(try_msc, try_msc->scsi_buff, 8, 1, 100);
            if (ret < 0)
            {
                msc_debug_msg("READ_CAPACITY failed!\n");
                if (ret == USBH_ERR_STALL)
                    msc_reset(try_msc);
                continue;
            }
            else
                break;
        }

        if (retries >= 3)
            continue;              /* try next lun */

        try_msc->uTotalSectorN = (try_msc->scsi_buff[0] << 24) | (try_msc->scsi_buff[1] << 16) |
                                 (try_msc->scsi_buff[2] << 8) | try_msc->scsi_buff[3];
        try_msc->nSectorSize = (try_msc->scsi_buff[4] << 24) | (try_msc->scsi_buff[5] << 16) |
                               (try_msc->scsi_buff[6] << 8) | try_msc->scsi_buff[7];

        try_msc->drv_no = fatfs_drive_alloc();
        if (try_msc->drv_no < 0)        /* should be failed, unless drive free slot is empty    */
        {
            ret = USBH_ERR_MEMORY_OUT;
            break;
        }

        msc_debug_msg("USB disk [%c] found: size=%d MB, uTotalSectorN=%d\n", msc->drv_no+'0', try_msc->uTotalSectorN / 2048, try_msc->uTotalSectorN);

        msc_list_add(try_msc);

        _path[0] =  try_msc->drv_no + '0';
        f_mount(&try_msc->fatfs_vol, _path, 1);
        bHasMedia = 1;


        /*
         *  duplicate another MSC for next try
         */
        try_msc = usbh_alloc_mem(sizeof(*try_msc));
        if (try_msc == NULL)
        {
            ret = USBH_ERR_MEMORY_OUT;
            break;
        }
        memcpy(try_msc, msc, sizeof(*msc));
    }

    if (bHasMedia)
    {
        if (try_msc)
            usbh_free_mem(try_msc, sizeof(*try_msc));
        return 0;
    }
    return ret;
}

static int msc_probe(IFACE_T *iface)
{
    ALT_IFACE_T   *aif = iface->aif;
    DESC_IF_T     *ifd;
    MSC_T         *msc;
    int           i;

    ifd = aif->ifd;

    /* Is this interface mass storage class? */
    if (ifd->bInterfaceClass != USB_CLASS_MASS_STORAGE)
        return USBH_ERR_NOT_MATCHED;

    /* Is supported sub-class? */
    if ((ifd->bInterfaceSubClass != MSC_SCLASS_SCSI) && (ifd->bInterfaceSubClass != MSC_SCLASS_8070) &&
            (ifd->bInterfaceSubClass != MSC_SCLASS_RBC))
        return USBH_ERR_NOT_SUPPORTED;

    /* Is bulk-only protocol? */
    if (ifd->bInterfaceProtocol != MSC_SPROTO_BULK)
    {
        msc_debug_msg("Not bulk-only MSC device!\n");
        return USBH_ERR_NOT_SUPPORTED;
    }

    msc = usbh_alloc_mem(sizeof(*msc));
    if (msc == NULL)
        return USBH_ERR_MEMORY_OUT;
    msc->uid = get_ticks();

    /* Find the bulk in and out endpoints */
    for (i = 0; i < aif->ifd->bNumEndpoints; i++)
    {
        if ((aif->ep[i].bmAttributes & EP_ATTR_TT_MASK) == EP_ATTR_TT_BULK)
        {
            if ((aif->ep[i].bEndpointAddress & EP_ADDR_DIR_MASK) == EP_ADDR_DIR_IN)
                msc->ep_bulk_in = &aif->ep[i];
            else
                msc->ep_bulk_out = &aif->ep[i];
        }
    }

    if ((msc->ep_bulk_in == NULL) || (msc->ep_bulk_out == NULL))
    {
        usbh_free_mem(msc, sizeof(*msc));
        return USBH_ERR_NOT_EXPECTED;
    }

    msc->iface = iface;

    msc_debug_msg("USB Mass Storage device found. Iface:%d, Alt Iface:%d, bep_in:0x%x, bep_out:0x%x\n", ifd->bInterfaceNumber, ifd->bAlternateSetting, msc->ep_bulk_in->bEndpointAddress, msc->ep_bulk_out->bEndpointAddress);

    get_max_lun(msc);

    return umass_init_device(msc);
}

static void msc_disconnect(IFACE_T *iface)
{
    int    i;
    MSC_T  *msc_p, *msc;

    /*
     *  Remove any hardware EP/QH from Host Controller hardware list.
     *  This will finally result in all transfers aborted.
     */
    for (i = 0; i < iface->aif->ifd->bNumEndpoints; i++)
    {
        iface->udev->hc_driver->quit_xfer(NULL, &(iface->aif->ep[i]));
    }

    /*
     *  unmount drive and remove it from MSC device list
     */
    msc = g_msc_list;
    while (msc != NULL)
    {
        msc_p = msc->next;
        if (msc->iface == iface)
        {
            fatfs_drive_free(msc->drv_no);
            msc_list_remove(msc);
            usbh_free_mem(msc, sizeof(*msc));
        }
        msc = msc_p;
    }
}

UDEV_DRV_T  msc_driver =
{
    msc_probe,
    msc_disconnect,
    NULL,
    NULL
};


/// @endcond HIDDEN_SYMBOLS


/**
  * @brief       Register and initialize USB Host Mass Storage driver.
  *
  * @retval      0    Success.
  * @retval      1    Failed.
  */
int  usbh_umas_init(void)
{
    fatfs_drive_int();
    g_msc_list = NULL;
    return usbh_register_driver(&msc_driver);
}




/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/


