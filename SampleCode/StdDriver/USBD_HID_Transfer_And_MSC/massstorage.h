/***************************************************************************//**
 * @file     massstorage.h
 * @brief    M480 series USB driver header file
 * @version  V1.00
 *
 * @copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __USBD_MASS_H__
#define __USBD_MASS_H__


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

/*-----------------------------------------*/
#define BULK_CBW  0x00
#define BULK_IN   0x01
#define BULK_OUT  0x02
#define BULK_CSW  0x04
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
#define DATA_FLASH_STORAGE_SIZE    (30*1024)  /* Configure the DATA FLASH storage size */
#define MASS_BUFFER_SIZE    256                /* Mass Storage command buffer size */
#define STORAGE_BUFFER_SIZE 512               /* Data transfer buffer size in 512 bytes alignment */
#define UDC_SECTOR_SIZE   512               /* logic sector size */

extern uint32_t MassBlock[];
extern uint32_t Storage_Block[];

#define MassCMD_BUF        ((uint32_t)&MassBlock[0])
#define STORAGE_DATA_BUF   ((uint32_t)&Storage_Block[0])

/*-------------------------------------------------------------*/

/*-------------------------------------------------------------*/
void DataFlashWrite(uint32_t addr, uint32_t size, uint32_t buffer);
void DataFlashRead(uint32_t addr, uint32_t size, uint32_t buffer);
void MSC_Init(void);
void MSC_RequestSense(void);
void MSC_ReadFormatCapacity(void);
void MSC_Read(void);
void MSC_ReadCapacity(void);
void MSC_Write(void);
void MSC_ModeSense10(void);
void MSC_ReadTrig(void);

void MSC_ReadMedia(uint32_t addr, uint32_t size, uint8_t *buffer);
void MSC_WriteMedia(uint32_t addr, uint32_t size, uint8_t *buffer);

/*-------------------------------------------------------------*/
void MSC_AckCmd(void);
void MSC_ProcessCmd(void);

#endif  /* __USBD_MASS_H_ */

/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/
