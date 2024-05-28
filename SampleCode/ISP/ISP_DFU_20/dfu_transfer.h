/******************************************************************************
 * @file     dfu_transfer.h
 * @brief    M480 series USB DFU transfer header file
 *
 * @note
 * Copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __USBD_DFU_H__
#define __USBD_DFU_H__


/* Define the vendor id and product id */
#define USBD_VID                       0x0416
#define USBD_PID                       0xBDF0


/* Define EP maximum packet size */
#define CEP_MAX_PKT_SIZE               64
#define TRANSFER_SIZE                  512

#define CEP_BUF_BASE    0
#define CEP_BUF_LEN     CEP_MAX_PKT_SIZE


/* Define Descriptor information */
#define USBD_SELF_POWERED              0
#define USBD_REMOTE_WAKEUP             0
#define USBD_MAX_POWER                 50  /* The unit is in 2mA. ex: 50 * 2mA = 100mA */

/* manifestation State */
#define MANIFEST_COMPLETE              0x00
#define MANIFEST_IN_PROGRESS           0x01

/* special commands with download request */
#define GET_COMMANDS                   0x00
#define SET_ADDRESS_POINTER            0x21
#define ERASE                          0x41

/* memory operation command */
#define CMD_ERASE                      0
#define CMD_WRITE                      1

#define _BYTE1(x)                      (uint8_t)((x) & 0xFF)               /*!< addressing cycle 1st byte */
#define _BYTE2(x)                      (uint8_t)(((x) & 0xFF00) >> 8)      /*!< addressing cycle 2nd byte */
#define _BYTE3(x)                      (uint8_t)(((x) & 0xFF0000) >> 16)   /*!< addressing cycle 3rd byte */

#define SET_POLLING_TIMEOUT(x)         dfu_status.bwPollTimeout0 = _BYTE1(x);\
    dfu_status.bwPollTimeout1 = _BYTE2(x);\
    dfu_status.bwPollTimeout2 = _BYTE3(x);

#define FLASH_ERASE_TIMEOUT            60
#define FLASH_WRITE_TIMEOUT            80


/* bit detach capable = bit 3 in bmAttributes field */
#define DFU_DETACH_MASK                (uint8_t)(0x10)
#define USB_SERIAL_STRING_SIZE         0x06
#define DFU_DESC_TYPE                  0x21


typedef struct
{
    uint8_t bStatus;
    uint8_t bwPollTimeout0;
    uint8_t bwPollTimeout1;
    uint8_t bwPollTimeout2;
    uint8_t bState;
    uint8_t iString;
} dfu_status_struct;

/* DFU device state defines */
typedef enum
{
    STATE_appIDLE = 0x00,
    STATE_appDETACH,
    STATE_dfuIDLE,
    STATE_dfuDNLOAD_SYNC,
    STATE_dfuDNBUSY,
    STATE_dfuDNLOAD_IDLE,
    STATE_dfuMANIFEST_SYNC,
    STATE_dfuMANIFEST,
    STATE_dfuMANIFEST_WAIT_RESET,
    STATE_dfuUPLOAD_IDLE,
    STATE_dfuERROR
} dfu_state_enum;

/* DFU device status defines */
typedef enum
{
    STATUS_OK = 0x00,
    STATUS_errTARGET,
    STATUS_errFILE,
    STATUS_errWRITE,
    STATUS_errERASE,
    STATUS_errCHECK_ERASED,
    STATUS_errPROG,
    STATUS_errVERIFY,
    STATUS_errADDRESS,
    STATUS_errNOTDONE,
    STATUS_errFIRMWARE,
    STATUS_errVENDOR,
    STATUS_errUSBR,
    STATUS_errPOR,
    STATUS_errUNKNOWN,
    STATUS_errSTALLEDPKT
} dfu_status_enum;

/* DFU class-specific requests */
typedef enum
{
    DFU_DETACH = 0,
    DFU_DNLOAD,
    DFU_UPLOAD,
    DFU_GETSTATUS,
    DFU_CLRSTATUS,
    DFU_GETSTATE,
    DFU_ABORT,
    DFU_REQ_MAX
} dfu_requests_enum;

//#pragma pack(1)

#define DFU_DETACH                        0
#define DFU_DNLOAD                        1
#define DFU_UPLOAD                        2
#define DFU_GETSTATUS                     3
#define DFU_CLRSTATUS                     4
#define DFU_GETSTATE                      5
#define DFU_ABORT                         6


#define APP_LOADED_ADDR 0x1000000
typedef struct
{
    uint8_t buf[TRANSFER_SIZE];
    uint16_t data_len;
    uint16_t block_num;
    uint32_t base_addr;
} s_prog_struct;

/*-------------------------------------------------------------*/
extern uint8_t gu8DeviceDescriptor[];
extern uint8_t gu8ConfigDescriptor[];
extern uint8_t gu8StringLang[4];
extern uint8_t gu8VendorStringDesc[];
extern uint8_t gu8ProductStringDesc[];
extern uint8_t gu8StringSerial[];

/*-------------------------------------------------------------*/
void DFU_Init(void);
void DFU_ClassRequest(void);
//void HID_SetInReport(void);
//void HID_GetOutReport(uint8_t *pu8EpBuf, uint32_t u32Size);

#endif  /* __USBD_DFU_H_ */

/*** (C) COPYRIGHT 2019 Nuvoton Technology Corp. ***/
