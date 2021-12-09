/***************************************************************************//**
 * @file     hid_mouse.h
 * @brief    M480 USB driver header file
 * @version  2.0.0
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __HID_MOUSE_H__
#define __HID_MOUSE_H__

/* Define the vendor id and product id */
#define USBD_VID                0x0416
#define USBD_PID                0x8249

/*!<Define HID Class Specific Request */
#define GET_REPORT              0x01
#define GET_IDLE                0x02
#define GET_PROTOCOL            0x03
#define SET_REPORT              0x09
#define SET_IDLE                0x0A
#define SET_PROTOCOL            0x0B

/*!<USB HID Interface Class protocol */
#define HID_NONE                0x00
#define HID_KEYBOARD            0x01
#define HID_MOUSE               0x02

/*!<USB HID Class Report Type */
#define HID_RPT_TYPE_INPUT      0x01
#define HID_RPT_TYPE_OUTPUT     0x02
#define HID_RPT_TYPE_FEATURE    0x03

/*!<USB HID Protocol Type */
#define HID_BOOT_PROTOCOL       0x00
#define HID_REPORT_PROTOCOL     0x01

/*-------------------------------------------------------------*/
/* Define EP maximum packet size */
#define CEP_MAX_PKT_SIZE        64
#define CEP_OTHER_MAX_PKT_SIZE  64
#define EPA_MAX_PKT_SIZE        64
#define EPA_OTHER_MAX_PKT_SIZE  64

#define CEP_BUF_BASE    0
#define CEP_BUF_LEN     CEP_MAX_PKT_SIZE
#define EPA_BUF_BASE    (CEP_BUF_BASE + CEP_BUF_LEN)
#define EPA_BUF_LEN     EPA_MAX_PKT_SIZE

/* Define the interrupt In EP number */
#define INT_IN_EP_NUM   0x01

/* Define Descriptor information */
#define HID_DEFAULT_INT_IN_INTERVAL     10
#define USBD_SELF_POWERED               0
#define USBD_REMOTE_WAKEUP              1
#define USBD_MAX_POWER                  50  /* The unit is in 2mA. ex: 50 * 2mA = 100mA */

#define LEN_CONFIG_AND_SUBORDINATE      (LEN_CONFIG+LEN_INTERFACE+LEN_HID+LEN_ENDPOINT)


/*-------------------------------------------------------------*/

/*-------------------------------------------------------------*/
void HID_InitForHighSpeed(void);
void HID_InitForFullSpeed(void);
void HID_Init(void);
void HID_ClassRequest(void);

void EPA_Handler(void);
void HID_Process(void);

#endif  /* __HID_MOUSE_H__ */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
