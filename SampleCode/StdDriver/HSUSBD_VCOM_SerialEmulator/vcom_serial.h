/***************************************************************************//**
 * @file     vcom_serial.h
 * @brief    M480 series USB driver header file
 * @version  V1.00
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __USBD_CDC_H__
#define __USBD_CDC_H__

/* Define the vendor id and product id */
#define USBD_VID        0x0416
#define USBD_PID        0xB002

/*!<Define CDC Class Specific Request */
#define SET_LINE_CODE           0x20
#define GET_LINE_CODE           0x21
#define SET_CONTROL_LINE_STATE  0x22

/* Define DMA Maximum Transfer length */
#define USBD_MAX_DMA_LEN    0x1000

/*-------------------------------------------------------------*/
/* Define EP maximum packet size */
#define CEP_MAX_PKT_SIZE        64
#define CEP_OTHER_MAX_PKT_SIZE  64
#define EPA_MAX_PKT_SIZE        512
#define EPA_OTHER_MAX_PKT_SIZE  64
#define EPB_MAX_PKT_SIZE        512
#define EPB_OTHER_MAX_PKT_SIZE  64
#define EPC_MAX_PKT_SIZE        64
#define EPC_OTHER_MAX_PKT_SIZE  64

#define CEP_BUF_BASE    0
#define CEP_BUF_LEN     CEP_MAX_PKT_SIZE
#define EPA_BUF_BASE    0x200
#define EPA_BUF_LEN     EPA_MAX_PKT_SIZE
#define EPB_BUF_BASE    0x400
#define EPB_BUF_LEN     EPB_MAX_PKT_SIZE
#define EPC_BUF_BASE    0x600
#define EPC_BUF_LEN     EPC_MAX_PKT_SIZE

/* Define the interrupt In EP number */
#define BULK_IN_EP_NUM      0x01
#define BULK_OUT_EP_NUM     0x02
#define INT_IN_EP_NUM       0x03

/* Define Descriptor information */
#define USBD_SELF_POWERED               0
#define USBD_REMOTE_WAKEUP              0
#define USBD_MAX_POWER                  50  /* The unit is in 2mA. ex: 50 * 2mA = 100mA */

/************************************************/
/* for CDC class */
/* Line coding structure
  0-3 dwDTERate    Data terminal rate (baudrate), in bits per second
  4   bCharFormat  Stop bits: 0 - 1 Stop bit, 1 - 1.5 Stop bits, 2 - 2 Stop bits
  5   bParityType  Parity:    0 - None, 1 - Odd, 2 - Even, 3 - Mark, 4 - Space
  6   bDataBits    Data bits: 5, 6, 7, 8, 16  */

typedef struct
{
    uint32_t  u32DTERate;     /* Baud rate    */
    uint8_t   u8CharFormat;   /* stop bit     */
    uint8_t   u8ParityType;   /* parity       */
    uint8_t   u8DataBits;     /* data bits    */
} STR_VCOM_LINE_CODING;

/*-------------------------------------------------------------*/
extern volatile int8_t gi8BulkOutReady;
extern STR_VCOM_LINE_CODING gLineCoding;
extern uint16_t gCtrlSignal;
extern volatile uint16_t comRbytes;
extern volatile uint16_t comRhead;
extern volatile uint16_t comRtail;
extern volatile uint16_t comTbytes;
extern volatile uint16_t comThead;
extern volatile uint16_t comTtail;
extern uint32_t gu32RxSize;
extern uint32_t gu32TxSize;
extern uint8_t gUsbRxBuf[];

/*-------------------------------------------------------------*/
void VCOM_Init(void);
void VCOM_InitForHighSpeed(void);
void VCOM_InitForFullSpeed(void);
void VCOM_ClassRequest(void);

void EPA_Handler(void);
void EPB_Handler(void);
void VCOM_LineCoding(uint8_t port);
void VCOM_TransferData(void);

#endif  /* __USBD_CDC_H_ */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
