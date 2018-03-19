#ifndef _USBH_MSC_H_
#define _USBH_MSC_H_

#include "ff.h"
#include "diskio.h"     /* FatFs lower layer API */


/// @cond HIDDEN_SYMBOLS

//#define MSC_DEBUG

#ifdef MSC_DEBUG
#define msc_debug_msg       printf
#else
#define msc_debug_msg(...)
#endif


#define USBDRV_0                  3      /* FATFS assigned USB disk drive volumn number base   */
#define USBDRV_MAX                9      /* FATFS assigned USB disk drive volumn number end    */
#define USBDRV_CNT                (USBDRV_MAX - USBDRV_0 + 1)


/* Mass Storage Class Sub-class */
#define MSC_SCLASS_RBC            0x01   /* Typically, flash devices      */
#define MSC_SCLASS_8020           0x02   /* CD-ROM                        */
#define MSC_SCLASS_QIC            0x03   /* QIC-157 Tapes                 */
#define MSC_SCLASS_UFI            0x04   /* Floppy                        */
#define MSC_SCLASS_8070           0x05   /* Removable media               */
#define MSC_SCLASS_SCSI           0x06   /* Transparent                   */

/* Mass Storage Class Sub-protocol */
#define MSC_SPROTO_CBI            0x00   /* Control/Bulk/Interrupt        */
#define MSC_SPROTO_CB             0x01   /* Control/Bulk w/o interrupt    */
#define MSC_SPROTO_BULK           0x50   /* Bulk only                     */
#define MSC_SPROTO_DPCM_USB       0xf0   /* Combination CB/SDDR09         */


/* Command Block Wrapper */
struct bulk_cb_wrap
{
    uint32_t  Signature;                 /* 0x43425355 = "USBC"           */
    uint32_t  Tag;                       /* unique per command id         */
    uint32_t  DataTransferLength;        /* size of data                  */
    uint8_t   Flags;                     /* Flag                          */
    uint8_t   Lun;                       /* LUN number (begin from 0)     */
    uint8_t   Length;                    /* length of the CDB             */
    uint8_t   CDB[16];                   /* max command                   */
};

#define MSC_CB_WRAP_LEN           31
#define MSC_CB_SIGN               0x43425355
#define MSC_FLAG_IN               1
#define MSC_FLAG_OUT              0

/* Command Status Wrapper */
struct bulk_cs_wrap
{
    uint32_t  Signature;                 /* 0x53425355 = "USBS"           */
    uint32_t  Tag;                       /* same as original command      */
    uint32_t  Residue;                   /* amount not transferred        */
    uint8_t   Status;                    /* see below                     */
};

#define MSC_CS_WRAP_LEN           13
#define MSC_CS_SIGN               0x53425355   /* "USBS"                  */
#define MSC_STAT_OK               0      /* command passed                */
#define MSC_STAT_FAIL             1      /* command failed                */
#define MSC_STAT_PHASE            2      /* phase error                   */

/*
 *      SCSI opcodes
 */
#define TEST_UNIT_READY           0x00
#define REQUEST_SENSE             0x03
#define INQUIRY                   0x12
#define MODE_SENSE                0x1a
#define READ_CAPACITY             0x25
#define READ_10                   0x28
#define WRITE_10                  0x2a
#define MODE_SENSE_10             0x5a

#define SCSI_BUFF_LEN             36

typedef struct msc_t
{
    IFACE_T     *iface;
    uint32_t    uid;                     /*!< The unique ID to identify a MSC device.     */
    EP_INFO_T   *ep_bulk_in;             /* bulk-in endpoint                              */
    EP_INFO_T   *ep_bulk_out;            /* bulk-out endpoint                             */
    uint8_t     max_lun;
    uint8_t     lun;                     /* MSC lun of this instance                      */
    uint8_t     root;                    /* root instance?                                */
    struct bulk_cb_wrap  cmd_blk;        /* MSC Bulk-only command block                   */
    struct bulk_cs_wrap  cmd_status;     /* MSC Bulk-only command status                  */
    uint8_t     scsi_buff[SCSI_BUFF_LEN];/* buffer for SCSI commands                      */
    uint32_t    uTotalSectorN;
    uint32_t    nSectorSize;
    uint32_t    uDiskSize;
    int         drv_no;                  /* Logical drive number associated with this instance */
    FATFS       fatfs_vol;               /* FATFS volumn                                  */
    struct msc_t  *next;                 /* point to next MSC device                      */
}  MSC_T;


extern int  run_scsi_command(MSC_T *msc, uint8_t *buff, uint32_t data_len, int bIsDataIn, int timeout_ticks);


/// @endcond


#endif  /* _USBH_MSC_H_ */

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/


