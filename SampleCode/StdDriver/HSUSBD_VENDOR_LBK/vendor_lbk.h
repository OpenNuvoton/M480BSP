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
#define USBD_VID                0x0416
#define USBD_PID                0xff20


/*------------------------------------------------------------------------------*/
/* Define endpoints of Vendor LBK device  */
#define INT_IN_EP_NUM           0x02        /* interrupt-in use HSUSBD EPA      */
#define INT_OUT_EP_NUM          0x03        /* interrupt-out use HSUSBD EPB     */
#define ISO_IN_EP_NUM           0x04        /* isochronous-in use HSUSBD EPC    */
#define ISO_OUT_EP_NUM          0x05        /* isochronous-out use HSUSBD EPD   */
#define BULK_IN_EP_NUM          0x06        /* bulk-in use HSUSBD EPE           */
#define BULK_OUT_EP_NUM         0x07        /* bulk-out use HSUSBD EPF          */

/*------------------------------------------------------------------------------*/
/* Define EP maximum packet size */
#define CEP_MAX_PKT_SIZE        64
#define CEP_OTHER_MAX_PKT_SIZE  64
#define EPA_MAX_PKT_SIZE        512
#define EPA_OTHER_MAX_PKT_SIZE  64
#define EPB_MAX_PKT_SIZE        512
#define EPB_OTHER_MAX_PKT_SIZE  64
#define EPC_MAX_PKT_SIZE        512
#define EPC_OTHER_MAX_PKT_SIZE  192
#define EPD_MAX_PKT_SIZE        512
#define EPD_OTHER_MAX_PKT_SIZE  192
#define EPE_MAX_PKT_SIZE        512
#define EPE_OTHER_MAX_PKT_SIZE  64
#define EPF_MAX_PKT_SIZE        512
#define EPF_OTHER_MAX_PKT_SIZE  64

#define CEP_BUF_BASE            0           /* 0x0000 ~ 0x01FF for control in/out  */
#define CEP_BUF_LEN             CEP_MAX_PKT_SIZE
#define EPA_BUF_BASE            0x200       /* 0x0200 ~ 0x03FF for interrupt-in    */
#define EPA_BUF_LEN             EPA_MAX_PKT_SIZE
#define EPB_BUF_BASE            0x400       /* 0x0400 ~ 0x05FF for interrupt-out   */
#define EPB_BUF_LEN             EPB_MAX_PKT_SIZE
#define EPC_BUF_BASE            0x600       /* 0x0600 ~ 0x07FF for isochronous-in  */
#define EPC_BUF_LEN             EPC_MAX_PKT_SIZE
#define EPD_BUF_BASE            0x800       /* 0x0800 ~ 0x09FF for isochronous-in  */
#define EPD_BUF_LEN             EPD_MAX_PKT_SIZE
#define EPE_BUF_BASE            0xA00       /* 0x0A00 ~ 0x0BFF for isochronous-in  */
#define EPE_BUF_LEN             EPE_MAX_PKT_SIZE
#define EPF_BUF_BASE            0xC00       /* 0x0C00 ~ 0x0DFF for isochronous-in  */
#define EPF_BUF_LEN             EPF_MAX_PKT_SIZE


/* Define Descriptor information */
#define INT_IN_INTERVAL                 1      /* interval is 1 frame */
#define INT_OUT_INTERVAL                1      /* interval is 1 frame */
#define INT_IN_HS_INTERVAL              4      /* 2^(4-1) = 8 =>  interval is 8 micro-frame */
#define INT_OUT_HS_INTERVAL             4      /* 2^(4-1) = 8 =>  interval is 8 micro-frame */
#define ISO_IN_INTERVAL                 1
#define ISO_OUT_INTERVAL                1
#define ISO_IN_HS_INTERVAL              4      /* 2^(4-1) = 8 =>  interval is 8 micro-frame */
#define ISO_OUT_HS_INTERVAL             4      /* 2^(4-1) = 8 =>  interval is 8 micro-frame */
#define HID_DEFAULT_INT_IN_INTERVAL     4
#define USBD_SELF_POWERED               0
#define USBD_REMOTE_WAKEUP              0
#define USBD_MAX_POWER                  50  /* The unit is in 2mA. ex: 50 * 2mA = 100mA */


/*-------------------------------------------------------------*/
/* Vendor LBK device vendor commands */
#define REQ_SET_DATA        0x01
#define REQ_GET_DATA        0x12


/*-------------------------------------------------------------*/
extern uint32_t get_ticks(void);

void VendorLBK_Init(void);
void VendorLBK_ClassRequest(void);
void VendorLBK_ProcessData(void);

#endif  /* __VENDOR_LBK_H_ */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
