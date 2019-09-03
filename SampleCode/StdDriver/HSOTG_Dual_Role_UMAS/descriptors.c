/**************************************************************************//**
 * @file     descriptors.c
 * @version  V1.00
 * @brief    M480 HSUSBD driver source file
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __DESCRIPTORS_C__
#define __DESCRIPTORS_C__

/*!<Includes */
#include "NuMicro.h"
#include "massstorage.h"


/*----------------------------------------------------------------------------*/
/*!<USB Device Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8DeviceDescriptor[] =
{
#else
uint8_t gu8DeviceDescriptor[] __attribute__((aligned(4))) =
{
#endif
    LEN_DEVICE,     /* bLength */
    DESC_DEVICE,    /* bDescriptorType */
    0x00, 0x02,     /* bcdUSB */
    0x00,           /* bDeviceClass */
    0x00,           /* bDeviceSubClass */
    0x00,           /* bDeviceProtocol */
    CEP_MAX_PKT_SIZE,   /* bMaxPacketSize0 */
    /* idVendor */
    USBD_VID & 0x00FF,
    ((USBD_VID & 0xFF00) >> 8),
    /* idProduct */
    USBD_PID & 0x00FF,
    ((USBD_PID & 0xFF00) >> 8),
    0x00, 0x00,     /* bcdDevice */
    0x01,           /* iManufacture */
    0x02,           /* iProduct */
    0x00,           /* iSerialNumber - no serial */
    0x01            /* bNumConfigurations */
};

/*!<USB Qualifier Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8QualifierDescriptor[] =
{
#else
uint8_t gu8QualifierDescriptor[] __attribute__((aligned(4))) =
{
#endif
    LEN_QUALIFIER,  /* bLength */
    DESC_QUALIFIER, /* bDescriptorType */
    0x00, 0x02,     /* bcdUSB */
    0x00,           /* bDeviceClass */
    0x00,           /* bDeviceSubClass */
    0x00,           /* bDeviceProtocol */
    CEP_OTHER_MAX_PKT_SIZE, /* bMaxPacketSize0 */
    0x01,           /* bNumConfigurations */
    0x00
};

/*!<USB Configure Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8ConfigDescriptor[] =
{
#else
uint8_t gu8ConfigDescriptor[] __attribute__((aligned(4))) =
{
#endif
    LEN_CONFIG,     /* bLength */
    DESC_CONFIG,    /* bDescriptorType */
    /* wTotalLength */
    (LEN_CONFIG+LEN_INTERFACE+LEN_ENDPOINT*2), 0x00,
    0x01,           /* bNumInterfaces */
    0x01,           /* bConfigurationValue */
    0x00,           /* iConfiguration */
    (0x80 | (USBD_SELF_POWERED << 6) | (USBD_REMOTE_WAKEUP << 5)),/* bmAttributes */
    USBD_MAX_POWER,         /* MaxPower */

    /* Interface */
    LEN_INTERFACE,  /* bLength */
    DESC_INTERFACE, /* bDescriptorType */
    0x00,           /* bInterfaceNumber */
    0x00,           /* bAlternateSetting */
    0x02,           /* bNumEndpoints */
    0x08,           /* bInterfaceClass */
    0x05,           /* bInterfaceSubClass */
    0x50,           /* bInterfaceProtocol */
    0x00,           /* iInterface */

    /* EP Descriptor: bulk in. */
    LEN_ENDPOINT,   /* bLength */
    DESC_ENDPOINT,  /* bDescriptorType */
    (BULK_IN_EP_NUM | EP_INPUT),    /* bEndpointAddress */
    EP_BULK,        /* bmAttributes */
    /* wMaxPacketSize */
    EPA_MAX_PKT_SIZE & 0x00FF,
    ((EPA_MAX_PKT_SIZE & 0xFF00) >> 8),
    0x00,           /* bInterval */

    /* EP Descriptor: bulk out. */
    LEN_ENDPOINT,   /* bLength */
    DESC_ENDPOINT,  /* bDescriptorType */
    (BULK_OUT_EP_NUM | EP_OUTPUT),  /* bEndpointAddress */
    EP_BULK,        /* bmAttributes */
    /* wMaxPacketSize */
    EPB_MAX_PKT_SIZE & 0x00FF,
    ((EPB_MAX_PKT_SIZE & 0xFF00) >> 8),
    0x00        /* bInterval */
};

/*!<USB Other Speed Configure Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8OtherConfigDescriptorHS[] =
{
#else
uint8_t gu8OtherConfigDescriptorHS[] __attribute__((aligned(4))) =
{
#endif
    LEN_CONFIG,         /* bLength */
    DESC_OTHERSPEED,    /* bDescriptorType */
    /* wTotalLength */
    (LEN_CONFIG+LEN_INTERFACE+LEN_ENDPOINT*2), 0x00,
    0x01,           /* bNumInterfaces */
    0x01,           /* bConfigurationValue */
    0x00,           /* iConfiguration */
    (0x80 | (USBD_SELF_POWERED << 6) | (USBD_REMOTE_WAKEUP << 5)),/* bmAttributes */
    USBD_MAX_POWER,         /* MaxPower */

    /* Interface */
    LEN_INTERFACE,  /* bLength */
    DESC_INTERFACE, /* bDescriptorType */
    0x00,           /* bInterfaceNumber */
    0x00,           /* bAlternateSetting */
    0x02,           /* bNumEndpoints */
    0x08,           /* bInterfaceClass */
    0x05,           /* bInterfaceSubClass */
    0x50,           /* bInterfaceProtocol */
    0x00,           /* iInterface */

    /* EP Descriptor: bulk in. */
    LEN_ENDPOINT,   /* bLength */
    DESC_ENDPOINT,  /* bDescriptorType */
    (BULK_IN_EP_NUM | EP_INPUT),    /* bEndpointAddress */
    EP_BULK,            /* bmAttributes */
    /* wMaxPacketSize */
    EPA_OTHER_MAX_PKT_SIZE & 0x00FF,
    ((EPA_OTHER_MAX_PKT_SIZE & 0xFF00) >> 8),
    0x00,       /* bInterval */

    /* EP Descriptor: bulk out. */
    LEN_ENDPOINT,   /* bLength */
    DESC_ENDPOINT,  /* bDescriptorType */
    (BULK_OUT_EP_NUM | EP_OUTPUT),  /* bEndpointAddress */
    EP_BULK,            /* bmAttributes */
    /* wMaxPacketSize */
    EPB_OTHER_MAX_PKT_SIZE & 0x00FF,
    ((EPB_OTHER_MAX_PKT_SIZE & 0xFF00) >> 8),
    0x00,       /* bInterval */
};

#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8ConfigDescriptorFS[] =
{
#else
uint8_t gu8ConfigDescriptorFS[] __attribute__((aligned(4))) =
{
#endif
    LEN_CONFIG,     /* bLength */
    DESC_CONFIG,    /* bDescriptorType */
    /* wTotalLength */
    (LEN_CONFIG+LEN_INTERFACE+LEN_ENDPOINT*2), 0x00,
    0x01,           /* bNumInterfaces */
    0x01,           /* bConfigurationValue */
    0x00,           /* iConfiguration */
    (0x80 | (USBD_SELF_POWERED << 6) | (USBD_REMOTE_WAKEUP << 5)),/* bmAttributes */
    USBD_MAX_POWER,         /* MaxPower */

    /* Interface */
    LEN_INTERFACE,  /* bLength */
    DESC_INTERFACE, /* bDescriptorType */
    0x00,           /* bInterfaceNumber */
    0x00,           /* bAlternateSetting */
    0x02,           /* bNumEndpoints */
    0x08,           /* bInterfaceClass */
    0x05,           /* bInterfaceSubClass */
    0x50,           /* bInterfaceProtocol */
    0x00,           /* iInterface */

    /* EP Descriptor: bulk in. */
    LEN_ENDPOINT,   /* bLength */
    DESC_ENDPOINT,  /* bDescriptorType */
    (BULK_IN_EP_NUM | EP_INPUT),    /* bEndpointAddress */
    EP_BULK,        /* bmAttributes */
    /* wMaxPacketSize */
    EPA_OTHER_MAX_PKT_SIZE & 0x00FF,
    ((EPA_OTHER_MAX_PKT_SIZE & 0xFF00) >> 8),
    0x00,           /* bInterval */

    /* EP Descriptor: bulk out. */
    LEN_ENDPOINT,   /* bLength */
    DESC_ENDPOINT,  /* bDescriptorType */
    (BULK_OUT_EP_NUM | EP_OUTPUT),  /* bEndpointAddress */
    EP_BULK,        /* bmAttributes */
    /* wMaxPacketSize */
    EPB_OTHER_MAX_PKT_SIZE & 0x00FF,
    ((EPB_OTHER_MAX_PKT_SIZE & 0xFF00) >> 8),
    0x00        /* bInterval */
};

#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8OtherConfigDescriptorFS[] =
{
#else
uint8_t gu8OtherConfigDescriptorFS[] __attribute__((aligned(4))) =
{
#endif
    LEN_CONFIG,         /* bLength */
    DESC_OTHERSPEED,    /* bDescriptorType */
    /* wTotalLength */
    (LEN_CONFIG+LEN_INTERFACE+LEN_ENDPOINT*2), 0x00,
    0x01,           /* bNumInterfaces */
    0x01,           /* bConfigurationValue */
    0x00,           /* iConfiguration */
    (0x80 | (USBD_SELF_POWERED << 6) | (USBD_REMOTE_WAKEUP << 5)),/* bmAttributes */
    USBD_MAX_POWER,         /* MaxPower */

    /* Interface */
    LEN_INTERFACE,  /* bLength */
    DESC_INTERFACE, /* bDescriptorType */
    0x00,           /* bInterfaceNumber */
    0x00,           /* bAlternateSetting */
    0x02,           /* bNumEndpoints */
    0x08,           /* bInterfaceClass */
    0x05,           /* bInterfaceSubClass */
    0x50,           /* bInterfaceProtocol */
    0x00,           /* iInterface */

    /* EP Descriptor: bulk in. */
    LEN_ENDPOINT,   /* bLength */
    DESC_ENDPOINT,  /* bDescriptorType */
    (BULK_IN_EP_NUM | EP_INPUT),    /* bEndpointAddress */
    EP_BULK,        /* bmAttributes */
    /* wMaxPacketSize */
    EPA_MAX_PKT_SIZE & 0x00FF,
    ((EPA_MAX_PKT_SIZE & 0xFF00) >> 8),
    0x00,           /* bInterval */

    /* EP Descriptor: bulk out. */
    LEN_ENDPOINT,   /* bLength */
    DESC_ENDPOINT,  /* bDescriptorType */
    (BULK_OUT_EP_NUM | EP_OUTPUT),  /* bEndpointAddress */
    EP_BULK,        /* bmAttributes */
    /* wMaxPacketSize */
    EPB_MAX_PKT_SIZE & 0x00FF,
    ((EPB_MAX_PKT_SIZE & 0xFF00) >> 8),
    0x00        /* bInterval */
};



/*!<USB Language String Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8StringLang[4] =
{
#else
uint8_t gu8StringLang[4] __attribute__((aligned(4))) =
{
#endif
    4,              /* bLength */
    DESC_STRING,    /* bDescriptorType */
    0x09, 0x04
};

/*!<USB Vendor String Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8VendorStringDesc[] =
{
#else
uint8_t gu8VendorStringDesc[] __attribute__((aligned(4))) =
{
#endif
    16,
    DESC_STRING,
    'N', 0, 'u', 0, 'v', 0, 'o', 0, 't', 0, 'o', 0, 'n', 0
};

/*!<USB Product String Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8ProductStringDesc[] =
{
#else
uint8_t gu8ProductStringDesc[] __attribute__((aligned(4))) =
{
#endif
    22,             /* bLength          */
    DESC_STRING,    /* bDescriptorType  */
    'U', 0, 'S', 0, 'B', 0, ' ', 0, 'D', 0, 'e', 0, 'v', 0, 'i', 0, 'c', 0, 'e', 0
};

#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8StringSerial[] =
#else
uint8_t gu8StringSerial[] __attribute__((aligned(4))) =
#endif
{
    26,             // bLength
    DESC_STRING,    // bDescriptorType
    'A', 0, '0', 0, '0', 0, '0', 0, '2', 0, '0', 0, '1', 0, '4', 0, '1', 0, '1', 0, '0', 0, '4', 0
};

uint8_t *gpu8UsbString[4] =
{
    gu8StringLang,
    gu8VendorStringDesc,
    gu8ProductStringDesc,
    gu8StringSerial,
};

uint8_t *gu8UsbHidReport[3] =
{
    NULL,
    NULL,
    NULL,
};

uint32_t gu32UsbHidReportLen[3] =
{
    0,
    0,
    0,
};

uint32_t gu32ConfigHidDescIdx[3] =
{
    0,
    0,
    0,
};


S_HSUSBD_INFO_T gsHSInfo =
{
    gu8DeviceDescriptor,
    gu8ConfigDescriptor,
    gpu8UsbString,
    gu8QualifierDescriptor,
    gu8ConfigDescriptorFS,
    gu8OtherConfigDescriptorHS,
    gu8OtherConfigDescriptorFS,
    gu8UsbHidReport,
    gu32UsbHidReportLen,
    gu32ConfigHidDescIdx,
};


#endif  /* __DESCRIPTORS_C__ */
