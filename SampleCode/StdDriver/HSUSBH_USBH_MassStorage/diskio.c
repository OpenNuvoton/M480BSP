/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2013        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various existing      */
/* storage control module to the FatFs module with a defined API.        */
/*-----------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "NuMicro.h"

#include "usbh_lib.h"
#include "ff.h"
#include "diskio.h"

#define SD0_DRIVE       0        /* for SD0          */
#define SD1_DRIVE       1        /* for SD1          */
#define EMMC_DRIVE      2        /* for eMMC/NAND    */
#define USBH_DRIVE_0    3        /* USB Mass Storage */
#define USBH_DRIVE_1    4        /* USB Mass Storage */
#define USBH_DRIVE_2    5        /* USB Mass Storage */
#define USBH_DRIVE_3    6        /* USB Mass Storage */
#define USBH_DRIVE_4    7        /* USB Mass Storage */


/*-----------------------------------------------------------------------*/
/* Initialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (BYTE pdrv)       /* Physical drive number (0..) */
{
    usbh_pooling_hubs();
    if (usbh_umas_disk_status(pdrv) == UMAS_ERR_NO_DEVICE)
        return STA_NODISK;
    return RES_OK;
}


/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (BYTE pdrv)       /* Physical drive number (0..) */
{
    usbh_pooling_hubs();
    if (usbh_umas_disk_status(pdrv) == UMAS_ERR_NO_DEVICE)
        return STA_NODISK;
    return RES_OK;
}


/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/
DRESULT disk_read (
    BYTE pdrv,      /* Physical drive number (0..) */
    BYTE *buff,     /* Data buffer to store read data */
    DWORD sector,   /* Sector address (LBA) */
    UINT count      /* Number of sectors to read (1..128) */
)
{
    int       ret;
//  int       sec_size;

    //printf("disk_read - drv:%d, sec:%d, cnt:%d, buff:0x%x\n", pdrv, sector, count, (uint32_t)buff);

    ret = usbh_umas_read(pdrv, sector, count, buff);
    if (ret != UMAS_OK)
    {
        usbh_umas_reset_disk(pdrv);
        ret = usbh_umas_read(pdrv, sector, count, buff);
    }

    if (ret == UMAS_OK)
        return RES_OK;

    if (ret == UMAS_ERR_NO_DEVICE)
        return RES_NOTRDY;

    if (ret == UMAS_ERR_IO)
        return RES_ERROR;

    return (DRESULT) ret;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
    BYTE pdrv,          /* Physical drive number (0..) */
    const BYTE *buff,   /* Data to be written */
    DWORD sector,       /* Sector address (LBA) */
    UINT count          /* Number of sectors to write (1..128) */
)
{
    int       ret;
//  int       sec_size;

    //printf("disk_write - drv:%d, sec:%d, cnt:%d, buff:0x%x\n", pdrv, sector, count, (uint32_t)buff);

    ret = usbh_umas_write(pdrv, sector, count, (uint8_t *)buff);
    if (ret != UMAS_OK)
    {
        usbh_umas_reset_disk(pdrv);
        ret = usbh_umas_write(pdrv, sector, count, (uint8_t *)buff);
    }

    if (ret == UMAS_OK)
        return RES_OK;

    if (ret == UMAS_ERR_NO_DEVICE)
        return RES_NOTRDY;

    if (ret == UMAS_ERR_IO)
        return RES_ERROR;

    return (DRESULT) ret;
}


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
    BYTE pdrv,      /* Physical drive number (0..) */
    BYTE cmd,       /* Control code */
    void *buff      /* Buffer to send/receive control data */
)
{
    int  ret;

    ret = usbh_umas_ioctl(pdrv, cmd, buff);

    if (ret == UMAS_OK)
        return RES_OK;

    if (ret == UMAS_ERR_IVALID_PARM)
        return RES_PARERR;

    if (ret == UMAS_ERR_NO_DEVICE)
        return RES_NOTRDY;

    return RES_PARERR;
}



