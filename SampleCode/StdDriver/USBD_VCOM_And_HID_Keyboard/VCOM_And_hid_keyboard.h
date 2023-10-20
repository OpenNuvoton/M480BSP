/***************************************************************************//**
 * @file     VCOM_And_hid_keyboard.h
 * @brief    M480 series USB driver header file
 * @version  2.0.0
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __USBD_HID_H__
#define __USBD_HID_H__

/* Define the vendor id and product id */
#define USBD_VID        0x0416
#define USBD_PID        0xDC02

/*!<Define HID Class Specific Request */
#define GET_REPORT          0x01
#define GET_IDLE            0x02
#define GET_PROTOCOL        0x03
#define SET_REPORT          0x09
#define SET_IDLE            0x0A
#define SET_PROTOCOL        0x0B

/*!<USB HID Interface Class protocol */
#define HID_NONE            0x00
#define HID_KEYBOARD        0x01
#define HID_MOUSE           0x02

/*!<USB HID Class Report Type */
#define HID_RPT_TYPE_INPUT      0x01
#define HID_RPT_TYPE_OUTPUT     0x02
#define HID_RPT_TYPE_FEATURE    0x03

/*!<USB HID HID LED */
#define HID_LED_NumLock         0x01
#define HID_LED_CapsLock        0x02
#define HID_LED_ScrollLock      0x04
#define HID_LED_Compose         0x08
#define HID_LED_Kana            0x10
#define HID_LED_Constatnt       0xE0
#define HID_LED_ALL             0xFF

/*!<Define CDC Class Specific Request */
#define SET_LINE_CODE           0x20
#define GET_LINE_CODE           0x21
#define SET_CONTROL_LINE_STATE  0x22

/*-------------------------------------------------------------*/
/* Define EP maximum packet size */
#define EP0_MAX_PKT_SIZE    8
#define EP1_MAX_PKT_SIZE    EP0_MAX_PKT_SIZE
#define EP2_MAX_PKT_SIZE    64
#define EP3_MAX_PKT_SIZE    64
#define EP4_MAX_PKT_SIZE    8
#define EP5_MAX_PKT_SIZE    8

#define SETUP_BUF_BASE  0
#define SETUP_BUF_LEN   8
#define EP0_BUF_BASE    (SETUP_BUF_BASE + SETUP_BUF_LEN)
#define EP0_BUF_LEN     EP0_MAX_PKT_SIZE
#define EP1_BUF_BASE    (SETUP_BUF_BASE + SETUP_BUF_LEN)
#define EP1_BUF_LEN     EP1_MAX_PKT_SIZE
#define EP2_BUF_BASE    (EP1_BUF_BASE + EP1_BUF_LEN)
#define EP2_BUF_LEN     EP2_MAX_PKT_SIZE
#define EP3_BUF_BASE    (EP2_BUF_BASE + EP2_BUF_LEN)
#define EP3_BUF_LEN     EP3_MAX_PKT_SIZE
#define EP4_BUF_BASE        (EP3_BUF_BASE + EP3_BUF_LEN)
#define EP4_BUF_LEN     EP4_MAX_PKT_SIZE
#define EP5_BUF_BASE        (EP4_BUF_BASE + EP4_BUF_LEN)
#define EP5_BUF_LEN     EP5_MAX_PKT_SIZE


/* Define the EP number */
#define BULK_IN_EP_NUM        0x01
#define BULK_OUT_EP_NUM       0x02
#define INT_IN_EP_NUM         0x03
#define INT_IN_EP_NUM_1       0x04

/* Define Descriptor information */
#define HID_DEFAULT_INT_IN_INTERVAL     1
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
extern uint8_t *gpu8RxBuf;
extern uint32_t gu32RxSize;
extern uint32_t gu32TxSize;

/*-------------------------------------------------------------*/

/*-------------------------------------------------------------*/
void HID_Init(void);
void HID_ClassRequest(void);

void EP2_Handler(void);
void EP3_Handler(void);
void VCOM_LineCoding(uint8_t port);
void VCOM_TransferData(void);

void EP5_Handler(void);
void HID_UpdateKbData(void);

#endif  /* __USBD_HID_H_ */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
