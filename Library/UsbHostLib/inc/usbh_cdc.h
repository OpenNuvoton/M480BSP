/**************************************************************************//**
 * @file     usbh_cdc.h
 * @version  V1.10
 * @brief    USB Host CDC(Communication Device Class) driver header file.
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef  _USBH_CDC_H_
#define  _USBH_CDC_H_

#include "NuMicro.h"
#include "usb.h"

#ifdef __cplusplus
extern "C"
{
#endif

/// @cond HIDDEN_SYMBOLS

#define CDC_DEBUG

#define CDC_ERRMSG      printf
#ifdef CDC_DEBUG
#define CDC_DBGMSG      printf
#else
#define CDC_DBGMSG(...)
#endif

#define CDC_STATUS_BUFF_SIZE    64
#define CDC_RX_BUFF_SIZE        64

/* Interface Class Codes (defined in usbh.h) */
//#define USB_CLASS_COMM        0x02
//#define USB_CLASS_DATA        0x0A

/* Communication Interface Class SubClass Codes */
#define CDC_SC_RESERVED         0x00        /* RESERVED                              */
#define CDC_SC_LINE_CTRL        0x01        /* Direct Line Control Model             */
#define CDC_SC_ABS_CTRL         0x02        /* Abstract Control Model                */
#define CDC_SC_TEL_CTRL         0x03        /* Telephone Control Model               */
#define CDC_SC_MULTI_CHN        0x04        /* Multi-Channel Control Model           */
#define CDC_SC_CAPI             0x05        /* CAPI Control Model                    */
#define CDC_SC_ETHER            0x06        /* Ethernet Networking Control Model     */
#define CDC_SC_ATM              0x07        /* ATM Networking Control Model          */

/* Communication Interface Class Control Protocol Codes */
#define CDC_PC_NONE             0x00        /* No class specific protocol required   */
#define CDC_PC_V25_TER          0x01        /* Common AT commands                    */
#define CDC_PC_VENDOR           0xFF        /* Vendor-specific                       */

/* CDC Class-specific descritpor types */
#define CDC_CS_INTERFACE        0x24
#define CDC_CS_ENDPOINT         0x25

/*
 * CDC class specific descritpor types
 */
#define CDC_DT_HDR_FUNC         0x00        /* Header Functional Descriptor                      */
#define CDC_DT_CALL_MANAGE      0x01        /* Call Management Functional Descriptor             */
#define CDC_DT_ABS_CTRL         0x02        /* Abstract Control Management Functional Descriptor */
#define CDC_DT_LINE_MANAGE      0x03        /* Direct Line Management Functional Descriptor      */
#define CDC_DT_TEL_RINGER       0x04        /* Telephone Ringer Functional Descriptor            */
#define CDC_DT_CALL_LINE_CAP    0x05        /* Telephone Call and Line State Reporting Capabilities Descriptor */
#define CDC_DT_UNION            0x06        /* Union Functional Descriptor                       */
#define CDC_DT_COUNTRY_SEL      0x07        /* Country Selection Functional Descriptor           */
#define CDC_DT_TEL_OPER_MODES   0x08        /* Telephone Operational Modes Functional Descriptor */
#define CDC_DT_USB_TERMINAL     0x09        /* USB Terminal Functional Descriptor                */
#define CDC_DT_NET_CHANNEL      0x0A        /* Network Channel Terminal Functional Descriptor    */
#define CDC_DT_PROTO_UNIT       0x0B        /* Protocol Unit Functional Descriptor               */
#define CDC_DT_EXTENT_UNIT      0x0C        /* Extension Unit Functional Descriptor              */
#define CDC_DT_MULTI_CHANNEL    0x0D        /* Multi-Channel Management Functional Descriptor    */
#define CDC_DT_CAPI_CTRL        0x0E        /* CAPI Control Management Functional Descriptor     */
#define CDC_DT_ETHERNET_FUNC    0x0F        /* Ethernet Networking Functional Descriptor         */
#define CDC_DT_ATM_FUNC         0x10        /* ATM Networking Functional Descriptor              */


/*
 * CDC class requests
 */
#define CDC_SEND_ENCAPSULATED_COMMAND       0x00
#define CDC_GET_ENCAPSULATED_RESPONSE       0x01
#define CDC_SET_COMM_FEATURE                0x02
#define CDC_GET_COMM_FEATURE                0x03
#define CDC_CLEAR_COMM_FEATURE              0x04
#define CDC_SET_AUX_LINE_STATE              0x10
#define CDC_SET_HOOK_STATE                  0x11
#define CDC_PULSE_SETUP                     0x12
#define CDC_SEND_PULSE                      0x13
#define CDC_SET_PULSE_TIME                  0x14
#define CDC_RING_AUX_JACK                   0x15
#define CDC_SET_LINE_CODING                 0x20
#define CDC_GET_LINE_CODING                 0x21
#define CDC_SET_CONTROL_LINE_STATE          0x22
#define CDC_SEND_BREAK                      0x23
#define CDC_SET_RINGER_PARMS                0x30
#define CDC_GET_RINGER_PARMS                0x31
#define CDC_SET_OPERATION_PARMS             0x32
#define CDC_GET_OPERATION_PARMS             0x33
#define CDC_SET_LINE_PARMS                  0x34
#define CDC_GET_LINE_PARMS                  0x35
#define CDC_DIAL_DIGITS                     0x36
#define CDC_SET_UNIT_PARAMETER              0x37
#define CDC_GET_UNIT_PARAMETER              0x38
#define CDC_CLEAR_UNIT_PARAMETER            0x39
#define CDC_GET_PROFILE                     0x3A
#define CDC_SET_ETHERNET_MULTICAST_FILTERS  0x40
#define CDC_SET_ETHERNET_PM_PATTERN_FILTER  0x41
#define CDC_GET_ETHERNET_PM_PATTERN_FILTER  0x42
#define CDC_SET_ETHERNET_PACKET_FILTER      0x43
#define CDC_GET_ETHERNET_STATISTIC          0x44
#define CDC_SET_ATM_DATA_FORMAT             0x50
#define CDC_GET_ATM_DEVICE_STATISTICS       0x51
#define CDC_SET_ATM_DEFAULT_VC              0x52
#define CDC_GET_ATM_VC_STATISTICS           0x53

#define CDC_CMD_TIMEOUT         100


/*-----------------------------------------------------------------------------------
 *  CDC Class-specific interface descriptor header
 */
#ifdef __ICCARM__
typedef struct cdc_if_header
{
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  payload[16];
} CDC_IF_HDR_T;
#else
typedef struct __attribute__((__packed__)) cdc_if_header
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubtype;
    uint8_t  payload[16];
} CDC_IF_HDR_T;
#endif

struct cdc_dev_t;

/// @endcond HIDDEN_SYMBOLS


/** @addtogroup USBH_EXPORTED_STRUCTURES USB Host Exported Structures
  @{
*/

/*
 *  Line Coding
 */
#ifdef __ICCARM__
typedef struct line_coding_t
{
    __packed uint32_t   baud;          /* Baud Rate                                               */
    __packed uint8_t    stop_bits;     /* 0 - 1 Stop bit;  1 - 1.5 Stop bits;  2 - 2 Stop bits    */
    __packed uint8_t    parity;        /* 0 - None; 1 - Odd; 2 - Even; 3 - Mark; 4 - Space        */
    __packed uint8_t    data_bits;     /* Data bits (5, 6, 7, 8 or 16)                            */
}  LINE_CODING_T;
#else
typedef struct __attribute__((__packed__)) line_coding_t
{
    uint32_t   baud;                   /* Baud Rate                                               */
    uint8_t    stop_bits;              /* 0 - 1 Stop bit;  1 - 1.5 Stop bits;  2 - 2 Stop bits    */
    uint8_t    parity;                 /* 0 - None; 1 - Odd; 2 - Even; 3 - Mark; 4 - Space        */
    uint8_t    data_bits;              /* Data bits (5, 6, 7, 8 or 16)                            */
}  LINE_CODING_T;
#endif

/*
 * USB-specific CDC device struct
 */
typedef struct cdc_dev_t
{
    UDEV_T              *udev;
    IFACE_T             *iface_cdc;     /* CDC interface number                               */
    IFACE_T             *iface_data;    /* CDC data interface number (can be NULL)            */
    int                 ifnum_data;
    EP_INFO_T           *ep_sts;
    EP_INFO_T           *ep_rx;
    EP_INFO_T           *ep_tx;
    UTR_T               *utr_sts;       /* Interrupt in URB                                   */
    UTR_T               *utr_rx;        /* Bulk in URB                                        */
    uint32_t            sts_buff[CDC_STATUS_BUFF_SIZE/4];
    uint32_t            rx_buff[CDC_RX_BUFF_SIZE/4];
    CDC_CB_FUNC         *sts_func;      /* Interrupt in data received callback                */
    CDC_CB_FUNC         *rx_func;       /* Bulk in data received callabck                     */
    uint8_t             rx_busy;        /* Bulk in transfer is on going                       */
    struct cdc_dev_t    *next;
}   CDC_DEV_T;

/*@}*/ /* end of group USBH_EXPORTED_STRUCTURES */

/*@}*/ /* end of group USBH_Library */

/*@}*/ /* end of group Library */

#ifdef __cplusplus
}
#endif

#endif  /* _USBH_CDC_H_ */

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/
