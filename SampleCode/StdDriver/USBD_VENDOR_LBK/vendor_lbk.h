/***************************************************************************//**
 * @file     vendor_lbk.h
 * @brief    M480 series USBD Vendor LBK driver header file
 * @version  2.0.0
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __VENDOR_LBK_H_
#define __VENDOR_LBK_H_

/* Define the vendor id and product id */
#define USBD_VID            0x0416
#define USBD_PID            0xff20

/*-------------------------------------------------------------*/
/* Define Endpoints */
#define NUMBER_OF_EP        6

#define EP0_MAX_PKT_SIZE    64
#define EP1_MAX_PKT_SIZE    EP0_MAX_PKT_SIZE
#define EP2_MAX_PKT_SIZE    64
#define EP3_MAX_PKT_SIZE    64
#define EP4_MAX_PKT_SIZE    192
#define EP5_MAX_PKT_SIZE    192
#define EP6_MAX_PKT_SIZE    64
#define EP7_MAX_PKT_SIZE    64

#define SETUP_BUF_BASE      0
#define SETUP_BUF_LEN       8
#define EP0_BUF_BASE        64
#define EP0_BUF_LEN         EP0_MAX_PKT_SIZE
#define EP1_BUF_BASE        (EP0_BUF_BASE + EP0_BUF_LEN)
#define EP1_BUF_LEN         EP1_MAX_PKT_SIZE
#define EP2_BUF_BASE        (EP1_BUF_BASE + EP1_BUF_LEN)
#define EP2_BUF_LEN         EP2_MAX_PKT_SIZE
#define EP3_BUF_BASE        (EP2_BUF_BASE + EP2_BUF_LEN)
#define EP3_BUF_LEN         EP3_MAX_PKT_SIZE
#define EP4_BUF_BASE        (EP3_BUF_BASE + EP3_BUF_LEN)
#define EP4_BUF_LEN         EP4_MAX_PKT_SIZE
#define EP5_BUF_BASE        (EP4_BUF_BASE + EP4_BUF_LEN)
#define EP5_BUF_LEN         EP5_MAX_PKT_SIZE
#define EP6_BUF_BASE        (EP5_BUF_BASE + EP5_BUF_LEN)
#define EP6_BUF_LEN         EP6_MAX_PKT_SIZE
#define EP7_BUF_BASE        (EP6_BUF_BASE + EP6_BUF_LEN)
#define EP7_BUF_LEN         EP7_MAX_PKT_SIZE

/* Define the EP number */
#define INT_IN_EP_NUM       0x02
#define INT_OUT_EP_NUM      0x03
#define ISO_IN_EP_NUM       0x04
#define ISO_OUT_EP_NUM      0x05
#define BULK_IN_EP_NUM      0x06
#define BULK_OUT_EP_NUM     0x07

/* Define Descriptor information */
#define INT_IN_INTERVAL                 2
#define INT_OUT_INTERVAL                2
#define ISO_IN_INTERVAL                 1
#define ISO_OUT_INTERVAL                1
#define HID_DEFAULT_INT_IN_INTERVAL     1
#define USBD_SELF_POWERED               0
#define USBD_REMOTE_WAKEUP              0
#define USBD_MAX_POWER                  50  /* The unit is in 2mA. ex: 50 * 2mA = 100mA */

#define LEN_CONFIG_AND_SUBORDINATE      (LEN_CONFIG+LEN_INTERFACE+LEN_ENDPOINT*6)


/*-------------------------------------------------------------*/
/* Vendor LBK device vendor commands */
#define REQ_SET_DATA        0x01
#define REQ_GET_DATA        0x12


/*-------------------------------------------------------------*/

/*-------------------------------------------------------------*/
void VendorLBK_Init(void);
void VendorLBK_ClassRequest(void);
void VendorLBK_ProcessData(void);

#endif  /* __VENDOR_LBK_H_ */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
