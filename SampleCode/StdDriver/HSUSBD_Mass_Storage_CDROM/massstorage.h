/***************************************************************************//**
 * @file     massstorage.h
 * @brief    M480 USB driver header file
 * @version  V1.00
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2024 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __MASSSTORAGE_H_
#define __MASSSTORAGE_H_

/* Define the vendor id and product id */
#define USBD_VID        0x0416
#define USBD_PID        0x0480

/* Define DMA Maximum Transfer length */
#define USBD_MAX_DMA_LEN    0x1000

/* Define EP maximum packet size */
#define CEP_MAX_PKT_SIZE        64
#define CEP_OTHER_MAX_PKT_SIZE  64
#define EPA_MAX_PKT_SIZE        512
#define EPA_OTHER_MAX_PKT_SIZE  64
#define EPB_MAX_PKT_SIZE        512
#define EPB_OTHER_MAX_PKT_SIZE  64

#define CEP_BUF_BASE    0
#define CEP_BUF_LEN     CEP_MAX_PKT_SIZE
#define EPA_BUF_BASE    0x200
#define EPA_BUF_LEN     EPA_MAX_PKT_SIZE
#define EPB_BUF_BASE    0x400
#define EPB_BUF_LEN     EPB_MAX_PKT_SIZE

/* Define the interrupt In EP number */
#define BULK_IN_EP_NUM      0x01
#define BULK_OUT_EP_NUM     0x02

/* Define Descriptor information */
#define USBD_SELF_POWERED               1
#define USBD_REMOTE_WAKEUP              0
#define USBD_MAX_POWER                  50  /* The unit is in 2mA. ex: 50 * 2mA = 100mA */

/*!<Define Mass Storage Class Specific Request */
#define BULK_ONLY_MASS_STORAGE_RESET    0xFF
#define GET_MAX_LUN                     0xFE

/*!<Define Mass Storage Signature */
#define CBW_SIGNATURE       0x43425355
#define CSW_SIGNATURE       0x53425355

/*!<Define Mass Storage UFI Command */
#define UFI_TEST_UNIT_READY                     0x00
#define UFI_REQUEST_SENSE                       0x03
#define UFI_INQUIRY                             0x12
#define UFI_MODE_SELECT_6                       0x15
#define UFI_MODE_SENSE_6                        0x1A
#define UFI_START_STOP                          0x1B
#define UFI_PREVENT_ALLOW_MEDIUM_REMOVAL        0x1E
#define UFI_READ_FORMAT_CAPACITY                0x23
#define UFI_READ_CAPACITY                       0x25
#define UFI_READ_10                             0x28
#define UFI_READ_12                             0xA8
#define UFI_READ_16                             0x9E
#define UFI_WRITE_10                            0x2A
#define UFI_WRITE_12                            0xAA
#define UFI_VERIFY_10                           0x2F
#define UFI_MODE_SELECT_10                      0x55
#define UFI_MODE_SENSE_10                       0x5A
#define UFI_READ_TOC                            0x43
#define UFI_GET_CONFIGURATION                   0x46
#define UFI_READ_DISK_INFORMATION               0x51
#define UFI_GET_EVENT_STATUS_NOTIFICATION       0x4A
#define UFI_REPORT_KEY                          0xA4
#define UFI_SET_CDROM_SPEED                     0xBB
#define UFI_READ_CD                             0xBE

/*-----------------------------------------*/
#define BULK_CBW    0x00
#define BULK_IN     0x01
#define BULK_OUT    0x02
#define BULK_CSW    0x04
#define BULK_NORMAL 0xFF

static __INLINE uint32_t get_be32(uint8_t *buf)
{
    return ((uint32_t) buf[0] << 24) | ((uint32_t) buf[1] << 16) |
           ((uint32_t) buf[2] << 8) | ((uint32_t) buf[3]);
}


/******************************************************************************/
/*                USBD Mass Storage Structure                                 */
/******************************************************************************/

/*!<USB Mass Storage Class - Command Block Wrapper Structure */
struct CBW
{
    uint32_t  dCBWSignature;
    uint32_t  dCBWTag;
    uint32_t  dCBWDataTransferLength;
    uint8_t   bmCBWFlags;
    uint8_t   bCBWLUN;
    uint8_t   bCBWCBLength;
    uint8_t   u8OPCode;
    uint8_t   u8LUN;
    uint8_t   au8Data[14];
};

/*!<USB Mass Storage Class - Command Status Wrapper Structure */
struct CSW
{
    uint32_t  dCSWSignature;
    uint32_t  dCSWTag;
    uint32_t  dCSWDataResidue;
    uint8_t   bCSWStatus;
};

/*-------------------------------------------------------------*/
/* MSC Disk Image Definitions */
#define MSC_ImageSize   0x0000B000

extern unsigned char eprom[MSC_ImageSize];      /* Disk Image */

#define DATA_FLASH_STORAGE_SIZE (MSC_ImageSize) /* Configure the DATA FLASH storage size */
#define MASS_BUFFER_SIZE    256                 /* Mass Storage command buffer size */
#define STORAGE_BUFFER_SIZE 4096                /* Data transfer buffer size in 4096 bytes alignment */
#define CDROM_BLOCK_SIZE    2048                /* Logic sector size */

extern uint8_t gStorageBuf[];

#define STORAGE_DATA_BUF   ((uint32_t)&gStorageBuf[0])

/*-------------------------------------------------------------*/
void MSC_Init(void);
void MSC_InitForHighSpeed(void);
void MSC_InitForFullSpeed(void);
void MSC_ClassRequest(void);
void MSC_ReadTOC(void);
void MSC_GetConfiguration(uint32_t u32Len, uint8_t *pu8Buff);
void MSC_GetEventStatusNotification(void);
void MSC_ReadDiskInformation(void);
void MSC_ReportKey(void);
void MSC_RequestSense(void);
void MSC_ReadFormatCapacity(void);
void MSC_ReadCapacity(void);
void MSC_ModeSense10(void);
void MSC_ModeSense6(void);
void MSC_ReceiveCBW(uint32_t u32Buf, uint32_t u32Len);
void MSC_ProcessCmd(void);
void MSC_ActiveDMA(uint32_t u32Addr, uint32_t u32Len);
void MSC_BulkOut(uint32_t u32Addr, uint32_t u32Len);
void MSC_BulkIn(uint32_t u32Addr, uint32_t u32Len);
void MSC_AckCmd(void);

void MSC_ReadMedia(uint32_t addr, uint32_t size, uint8_t *buffer);
void MSC_WriteMedia(uint32_t addr, uint32_t size, uint8_t *buffer);

#endif  /* __MASSSTORAGE_H_ */

