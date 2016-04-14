/* Driver for USB Mass Storage compliant devices
 * SCSI layer glue code
 *
 * $Id: scsiglue.c,v 1.19 2000/11/13 22:28:55 mdharm Exp $
 *
 * Current development and maintenance by:
 *   (c) 1999, 2000 Matthew Dharm (mdharm-usb@one-eyed-alien.net)
 *
 * Developed with the assistance of:
 *   (c) 2000 David L. Brown, Jr. (usb-storage@davidb.org)
 *   (c) 2000 Stephen J. Gowdy (SGowdy@lbl.gov)
 *
 * Initial work by:
 *   (c) 1999 Michael Gee (michael@linuxspecific.com)
 *
 * This driver is based on the 'USB Mass Storage Class' document. This
 * describes in detail the protocol used to communicate with such
 * devices.  Clearly, the designers had SCSI and ATAPI commands in
 * mind when they created this document.  The commands are all very
 * similar to commands in the SCSI-II and ATAPI specifications.
 *
 * It is important to note that in a number of cases this class
 * exhibits class-specific exemptions from the USB specification.
 * Notably the usage of NAK, STALL and ACK differs from the norm, in
 * that they are used to communicate wait, failed and OK on commands.
 *
 * Also, for certain devices, the interrupt endpoint is used to convey
 * status of a command.
 *
 * Please see http://www.one-eyed-alien.net/~mdharm/linux-usb for more
 * information about this driver.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "M480.h"

#include "Umas.h"
#include "UmasScsi.h"

#include "usbh_lib.h"
#include "ff.h"
#include "diskio.h"


FATFS  _FatfsVol[USBDRV_CNT];

FATFS_DRV_T  _FatfsDrv[USBDRV_CNT];

static TCHAR  _Path[3] = { '0', ':', 0 };

void  fatfs_drive_int()
{
    int   i;

    for (i = 0; i < USBDRV_CNT; i++) {
        _FatfsDrv[i].used = 0;
        _FatfsDrv[i].drv_no = USBDRV_0 + i;
    }
}


FATFS_DRV_T * fatfs_drive_alloc()
{
    int  i;

    for (i = 0; i < USBDRV_CNT; i++) {
        if (_FatfsDrv[i].used == 0) {
            _FatfsDrv[i].used = 1;
            return &_FatfsDrv[i];
        }
    }
    printf("No free FATFS USB drive slots!\n");
    return NULL;
}

void  fatfs_drive_free(FATFS_DRV_T *fdrv)
{
    _Path[0] =  fdrv->drv_no - USBDRV_0 + '0';
    f_mount(NULL, _Path, 1);
    fdrv->used = 0;
}


UMAS_DRIVE_T * fatfs_get_drive(int drv_no)
{
    if ((drv_no < USBDRV_0) || (drv_no > USBDRV_MAX))
        return NULL;

    if (_FatfsDrv[drv_no - USBDRV_0].used == 0)
        return NULL;

    return _FatfsDrv[drv_no - USBDRV_0].umas_drv;
}


static uint8_t usb_stor_sense_notready[18] = {
    0x70/* current error */, 0, 0x02/* not ready */, 0 , 0,
    0x0a/* additional length */, 0, 0, 0, 0,
    0x04/* not ready */, 0x03 /* manual intervention */
};


/* run command */
static int  run_scsi_command(SCSI_CMD_T *srb, UMAS_DATA_T *umas)
{
    /* reject the command if the direction indicator is UNKNOWN */
    if (srb->sc_data_direction == SCSI_DATA_UNKNOWN) {
        UMAS_DEBUG("run_scsi_command - UNKNOWN data direction\n");
        umas->srb->result = DID_ERROR << 16;
        return -1;
    }

#if 0
    /* reject if target != 0 or if LUN is higher than the maximum known LUN */
    if (umas->srb->target && (!(umas->flags & UMAS_FL_SCM_MULT_TARG))) {
        UMAS_DEBUG("run_scsi_command - Bad target number (%d/%d)\n", umas->srb->target, umas->srb->lun);
        umas->srb->result = DID_BAD_TARGET << 16;
        return -1;
    }
#endif

    if (umas->srb->lun > umas->max_lun) {
        UMAS_DEBUG("run_scsi_command - Bad LUN (%d/%d)\n", srb->target, srb->lun);
        umas->srb->result = DID_BAD_TARGET << 16;
        return -1;
    }

    /* handle those devices which can't do a START_STOP */
    if ((srb->cmnd[0] == START_STOP) && (umas->flags & UMAS_FL_START_STOP)) {
        UMAS_DEBUG("run_scsi_command - Skipping START_STOP command\n");
        umas->srb->result = GOOD << 1;
        return -1;
    }

    /* our device has gone - pretend not ready */
    if (!umas->pusb_dev) {
        UMAS_DEBUG("run_scsi_command - Request is for removed device\n");
        /*
         * For REQUEST_SENSE, it's the data.  But for anything else,
         * it should look like we auto-sensed for it.
         */
        if (umas->srb->cmnd[0] == REQUEST_SENSE) {
            memcpy(srb->request_buff,
                   usb_stor_sense_notready, sizeof(usb_stor_sense_notready));
            srb->result = GOOD << 1;
        } else {
            memcpy(srb->sense_buffer,
                   usb_stor_sense_notready, sizeof(usb_stor_sense_notready));
            srb->result = CHECK_CONDITION << 1;
        }
    } else { /* !umas->pusb_dev */
#ifdef UMAS_VERBOSE_DEBUG
        UMAS_DEBUG_ShowCommand(srb);
#endif
        /* we've got a command, let's do it! */
        umas->proto_handler(srb, umas);
    }

    /* indicate that the command is done */
    if (umas->srb->result != DID_ABORT << 16) {
        UMAS_VDEBUG("run_scsi_command - scsi cmd done, result=0x%x\n", srb->result);
    } else {
        UMAS_DEBUG("run_scsi_command - scsi command aborted\n");
    }

    return srb->result;
}


int  test_unit_ready(UMAS_DATA_T *umas, int lun)
{
    SCSI_CMD_T      *srb = umas->srb;

    memset(srb->cmnd, 0, MAX_COMMAND_SIZE);
    srb->cmnd[0] = TEST_UNIT_READY;
    srb->cmnd[1] = lun << 5;
    srb->cmd_len = 6;
    srb->request_bufflen = 0;
    srb->use_sg = 0;
    srb->sc_data_direction = SCSI_DATA_READ;
    srb->sense_buffer[0] = 0;
    srb->sense_buffer[2] = 0;
    return run_scsi_command(srb, umas);
}


int  request_sense(UMAS_DATA_T *umas, int lun)
{
    SCSI_CMD_T      *srb = umas->srb;

    memset(srb->cmnd, 0, MAX_COMMAND_SIZE);
    srb->cmnd[0] = REQUEST_SENSE;
    srb->cmnd[1] = lun << 5;
    srb->cmnd[4] = 18;
    srb->cmd_len = 12;
    srb->request_bufflen = 18;
    srb->use_sg = 0;
    srb->sc_data_direction = SCSI_DATA_READ;
    return run_scsi_command(srb, umas);
}


int try_test_unit_ready(UMAS_DATA_T *umas)
{
    int  retries;

    for (retries = 0; retries < 10; retries++) {
        if (test_unit_ready(umas, 0) == 0)
            return 0;
    }
    return -1;
}


/**
  * @brief       Check USB Mass Storage device status.
  *
  * @param[in]   drv_no  FATFS drive volume number. (USB Host Mass Storage driver is 3 ~ 7.)
  *
  * @retval      - \ref UMAS_OK              Mass storage device is ready.
  * @retval      - \ref UMAS_ERR_NO_DEVICE   There's no mass storage device mounted to this volume.
  */
int  usbh_umas_disk_status(int drv_no)
{
    if (fatfs_get_drive(drv_no) == NULL)
        return UMAS_ERR_NO_DEVICE;
    return UMAS_OK;
}


/**
  * @brief       Get the sector size of specified Mass Storage device.
  *
  * @param[in]   drv_no  FATFS drive volume number. (USB Host Mass Storage driver is 3 ~ 7.)
  *
  * @retval      512         There's no mass storage device mounted to this volume.
  * @retval      Otherwise   Sector size of the mass storage device mounted to this volume.
  */
int  usbh_umas_disk_sector_size(int drv_no)
{
    if (fatfs_get_drive(drv_no) == NULL)
        return 512;
    return _FatfsDrv[drv_no - USBDRV_0].nSectorSize;
}


/**
  * @brief       Read a number of contiguous sectors from mass storage device.
  *
  * @param[in]   drv_no    FATFS drive volume number. (USB Host Mass Storage driver is 3 ~ 7.)
  * @param[in]   sec_no    Sector number of the start secotr.
  * @param[in]   sec_cnt   Number of sectors to be read.
  * @param[out]  buff      Memory buffer to store data read from disk.
  *
  * @retval      - \ref UMAS_OK              Mass storage device is ready.
  * @retval      - \ref UMAS_ERR_NO_DEVICE   There's no mass storage device mounted to this volume.
  * @retval      - \ref UMAS_ERR_IO          Failed to read disk.
  */
int  usbh_umas_read(int drv_no, unsigned int sec_no, int sec_cnt, unsigned char *buff)
{
    UMAS_DRIVE_T    *umas_drive;
    UMAS_DATA_T     *umas;
    FATFS_DRV_T     *fdrv;
    SCSI_CMD_T      *srb;
    uint8_t             *old_rq_buff;
    int             retry = 10;

    umas_drive = fatfs_get_drive(drv_no);
    if (umas_drive == NULL)
        return UMAS_ERR_NO_DEVICE;

    umas = umas_drive->umas;

    fdrv = &_FatfsDrv[drv_no - USBDRV_0];

    //UMAS_DEBUG("umas_disk_read - sector=%d, count=%d\n", sec_no, sec_cnt);
    if ((sec_no >= fdrv->uTotalSectorN) && fdrv->uTotalSectorN) {
        UMAS_DEBUG("usbh_umas_read - exceed disk size! (%d/%d)\n", sec_no, fdrv->uTotalSectorN);
        return UMAS_ERR_IO;
    }

    srb = umas->srb;

do_retry:

    old_rq_buff = srb->request_buff;
    srb->request_buff = (uint8_t *)((uint32_t)buff | NON_CACHE_MASK);

    memset(srb->cmnd, 0, MAX_COMMAND_SIZE);
    srb->cmnd[0] = READ_10;
    srb->cmnd[1] = umas_drive->lun_no << 5;
    srb->cmnd[2] = (sec_no >> 24) & 0xFF;
    srb->cmnd[3] = (sec_no >> 16) & 0xFF;
    srb->cmnd[4] = (sec_no >> 8) & 0xFF;
    srb->cmnd[5] = sec_no & 0xFF;
    srb->cmnd[7] = (sec_cnt >> 8) & 0xFF;
    srb->cmnd[8] = sec_cnt & 0xFF;
    srb->cmd_len = 10;

    srb->request_bufflen = fdrv->nSectorSize * sec_cnt;

    srb->use_sg = 0;
    srb->sc_data_direction = SCSI_DATA_READ;

    if (run_scsi_command(srb, umas) != 0) {
        if (retry > 0) {
            retry--;
            goto do_retry;
        }

        UMAS_DEBUG("umas_disk_read - failed at sector %d (%d)\n", sec_no, sec_cnt);
        srb->request_buff = old_rq_buff;
        return UMAS_ERR_IO;
    }
    srb->request_buff = old_rq_buff;
    return UMAS_OK;
}


/**
  * @brief       Write a number of contiguous sectors to mass storage device.
  *
  * @param[in]   drv_no    FATFS drive volume number. (USB Host Mass Storage driver is 3 ~ 7.)
  * @param[in]   sec_no    Sector number of the start secotr.
  * @param[in]   sec_cnt   Number of sectors to be written.
  * @param[in]   buff      Memory buffer to store data to be written to disk.
  *
  * @retval      - \ref UMAS_OK              Mass storage device is ready.
  * @retval      - \ref UMAS_ERR_NO_DEVICE   There's no mass storage device mounted to this volume.
  * @retval      - \ref UMAS_ERR_IO          Failed to write disk.
  */
int  usbh_umas_write(int drv_no, unsigned int sec_no, int sec_cnt, unsigned char *buff)
{
    UMAS_DRIVE_T    *umas_drive;
    UMAS_DATA_T     *umas;
    FATFS_DRV_T     *fdrv;
    SCSI_CMD_T      *srb;
    uint8_t             *old_rq_buff;
    int             retry = 10;

    umas_drive = fatfs_get_drive(drv_no);
    if (umas_drive == NULL)
        return UMAS_ERR_NO_DEVICE;

    umas = umas_drive->umas;

    fdrv = &_FatfsDrv[drv_no - USBDRV_0];

    srb = umas->srb;

    if (sec_no >= fdrv->uTotalSectorN) {
        UMAS_DEBUG("usbh_umas_write - exceed disk size! (%d/%d)\n", sec_no, fdrv->uTotalSectorN);
        return UMAS_ERR_IO;
    }

do_retry:
    //UMAS_DEBUG("usbh_umas_write - Write Sector: %d %d\n", sec_no, sec_cnt);

    old_rq_buff = srb->request_buff;
    srb->request_buff = (uint8_t *)((uint32_t)buff | NON_CACHE_MASK);

    memset(srb->cmnd, 0, MAX_COMMAND_SIZE);
    srb->cmnd[0] = WRITE_10;
    srb->cmnd[1] = umas_drive->lun_no << 5;
    srb->cmnd[2] = (sec_no >> 24) & 0xFF;
    srb->cmnd[3] = (sec_no >> 16) & 0xFF;
    srb->cmnd[4] = (sec_no >> 8) & 0xFF;
    srb->cmnd[5] = sec_no & 0xFF;
    srb->cmnd[7] = (sec_cnt >> 8) & 0xFF;
    srb->cmnd[8] = sec_cnt & 0xFF;
    srb->cmd_len = 10;

    srb->request_bufflen = fdrv->nSectorSize * sec_cnt;

    srb->use_sg = 0;
    srb->sc_data_direction = SCSI_DATA_WRITE;

    if (run_scsi_command(srb, umas) != 0) {
        if (retry > 0) {
            retry--;
            goto do_retry;
        }

        UMAS_DEBUG("umas_disk_write - failed at sector %d (%d)\n", sec_no, sec_cnt);
        srb->request_buff = old_rq_buff;
        return UMAS_ERR_IO;
    }

    srb->request_buff = old_rq_buff;
    return UMAS_OK;
}


/**
  * @brief       Get information from USB disk volume.
  *
  * @param[in]   drv_no    FATFS drive volume number. (USB Host Mass Storage driver is 3 ~ 7.)
  * @param[in]   cmd       FATFS disk ioctl command.
  * @param[out]  buff      Memory buffer to store information.
  *
  * @retval      - \ref UMAS_OK              Mass storage device is ready.
  * @retval      - \ref UMAS_ERR_NO_DEVICE   There's no mass storage device mounted to this volume.
  * @retval      - \ref UMAS_ERR_IO          Failed to write disk.
  */
int  usbh_umas_ioctl(int drv_no, int cmd, void *buff)
{
    UMAS_DRIVE_T    *umas_drive;
    FATFS_DRV_T     *fdrv;

    umas_drive = fatfs_get_drive(drv_no);
    if (umas_drive == NULL)
        return UMAS_ERR_NO_DEVICE;

    fdrv = &_FatfsDrv[drv_no - USBDRV_0];

    switch (cmd) {
    case CTRL_SYNC:
        return UMAS_OK;

    case GET_SECTOR_COUNT:
        *(uint32_t *)buff = fdrv->uTotalSectorN;
        return UMAS_OK;

    case GET_SECTOR_SIZE:
        *(uint32_t *)buff = fdrv->nSectorSize;
        return UMAS_OK;

    case GET_BLOCK_SIZE:
        *(uint32_t *)buff = fdrv->nSectorSize;
        return UMAS_OK;
    }
    return UMAS_ERR_IVALID_PARM;
}


int  UMAS_InitUmasDevice(UMAS_DATA_T *umas)
{
    int             t0, retries;
    SCSI_CMD_T      *srb = umas->srb;
    int             lun;
    int             bHasMedia;
    UMAS_DRIVE_T    *umas_drive;
    FATFS_DRV_T     *fdrv;

    memset(srb, 0, sizeof(SCSI_CMD_T));
    srb->request_buff = (void *)USB_malloc(256, BOUNDARY_WORD);
    if (srb->request_buff == NULL) {
        UMAS_DEBUG("UMAS_InitUmasDevice - Out of memory\n");
        return -1;
    }
    memset(srb->request_buff, 0, 256);

    for (lun = umas->max_lun; lun >= 0; lun--) {
        UMAS_DEBUG("\n\n\n******* Read lun %d ******\n\n", lun);

        /* create a new lun drive */
        umas_drive = kmalloc(sizeof(UMAS_DRIVE_T), 4);
        if (umas_drive == NULL)
            break;
        umas_drive->umas = umas;
        umas_drive->lun_no = lun;
        umas_drive->client = NULL;
        umas_drive->next = umas->drive_list;
        umas->drive_list = umas_drive;

        UMAS_DEBUG("INQUIRY ==>\n");
        memset(srb->cmnd, 0, MAX_COMMAND_SIZE);
        srb->cmnd[0] = INQUIRY;
        srb->cmnd[1] = lun << 5;
        srb->cmnd[4] = 128;
        srb->cmd_len = 6;
        srb->request_bufflen = 128;
        srb->use_sg = 0;
        srb->sc_data_direction = SCSI_DATA_READ;

        if (run_scsi_command(srb, umas) == 0) {
            //HexDumpBuffer("INQUIRY result", srb->request_buff, 128);
        } else
            UMAS_DEBUG("INQUIRY - command failed!\n");

        UMAS_DEBUG("TEST UNIT READY ==>\n");
        bHasMedia = FALSE;
        for (retries = 0; retries < 3; retries++) {
            if (test_unit_ready(umas, lun) != 0) {
                //UMAS_DEBUG("TEST_UNIT_READY - command failed\n");
                //break;
            } else if (srb->result == 0) {
                bHasMedia = TRUE;
                break;
            }

#if 1
            if ((srb->result < 0) || (srb->sense_buffer[2] != UNIT_ATTENTION)) {
                UMAS_DEBUG("TEST_UNIT_READY not UNIT_ATTENTION!\n");
                break;
            }

            /*
             * If the drive has indicated to us that it doesn't have
             * any media in it, don't bother with any of the rest of
             * this crap.
             */
            if ((srb->result < 0) &&
                    (srb->sense_buffer[2] == UNIT_ATTENTION) &&
                    (srb->sense_buffer[12] == 0x3A)) {
                UMAS_DEBUG("TEST_UNIT_READY - no media\n");
                break;
            }

            /* Look for non-removable devices that return NOT_READY.
             * Issue command to spin up drive for these cases. */
            if ((srb->result < 0) && (srb->sense_buffer[2] == NOT_READY)) {
                UMAS_DEBUG("TEST_UNIT_READY - not ready, will retry.\n");
            }
#endif

            t0 = umas_get_ticks();
            while (umas_get_ticks() - t0 < 10)
                ;
        }

        if (bHasMedia == FALSE)
            continue;

        UMAS_DEBUG("REQUEST SENSE ==>\n");

        if (request_sense(umas, lun) == 0) {
            //HexDumpBuffer("REQUEST_SENSE result", srb->request_buff, 256);
            if ((srb->request_buff[16] == 0) && (srb->request_buff[17] == 0))
                UMAS_DEBUG("REQUEST_SENSE - no sense\n");
            else
                UMAS_DEBUG("REQUEST_SENSE - attention %02x %02x\n", srb->request_buff[16], srb->request_buff[17]);
        } else
            UMAS_DEBUG("REQUEST_SENSE failed!\n");;

        UMAS_DEBUG("READ CAPACITY ==>\n");
        memset(srb->cmnd, 0, MAX_COMMAND_SIZE);
        srb->cmnd[0] = READ_CAPACITY;
        srb->cmnd[1] = lun << 5;
        srb->cmd_len = 9;
        srb->sense_buffer[0] = 0;
        srb->sense_buffer[2] = 0;
        srb->sc_data_direction = SCSI_DATA_READ;
        if (run_scsi_command(srb, umas) != 0) {
            UMAS_DEBUG("READ_CAPACITY failed!\n");
            continue;
        }

        fdrv = fatfs_drive_alloc();
        if (fdrv == NULL) {
            printf("No free FATFS drive slots!\n");
            continue;
        }

        fdrv->uTotalSectorN = (srb->request_buff[0] << 24) | (srb->request_buff[1] << 16) |
                              (srb->request_buff[2] << 8) | srb->request_buff[3];
        fdrv->nSectorSize = (srb->request_buff[4] << 24) | (srb->request_buff[5] << 16) |
                            (srb->request_buff[6] << 8) | srb->request_buff[7];
        fdrv->uDiskSize = (fdrv->uTotalSectorN / 1024) * fdrv->nSectorSize;

        UMAS_DEBUG("USB disk found: size=%d MB, uTotalSectorN=%d\n", (int)fdrv->uDiskSize / 1024, fdrv->uTotalSectorN);
        UMAS_DEBUG("USB disk is bounded to FATFS drive %d\n", fdrv->drv_no);

        umas_drive->client = fdrv;
        fdrv->umas_drv = umas_drive;

        _Path[0] =  fdrv->drv_no + '0';
        f_mount(&_FatfsVol[ fdrv->drv_no - USBDRV_0 ], _Path, 1);
    }

    return 0;
}

