/***************************************************************************//**
 * @file     descriptors.c
 * @brief    M480 series USBD driver source file
 * @version  2.0.0
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
/*!<Includes */
#include "NuMicro.h"
#include "massstorage.h"

/*----------------------------------------------------------------------------*/
/*!<USB Device Descriptor */
uint8_t gu8DeviceDescriptor[] =
{
    LEN_DEVICE,         /* bLength */
    DESC_DEVICE,        /* bDescriptorType */
    0x10, 0x01,         /* bcdUSB */
    0x00,               /* bDeviceClass */
    0x00,               /* bDeviceSubClass */
    0x00,               /* bDeviceProtocol */
    EP0_MAX_PKT_SIZE,   /* bMaxPacketSize0 */
    /* idVendor */
    USBD_VID & 0x00FF,
    ((USBD_VID & 0xFF00) >> 8),
    /* idProduct */
    USBD_PID & 0x00FF,
    ((USBD_PID & 0xFF00) >> 8),
    0x00, 0x00,        /* bcdDevice */
    0x01,              /* iManufacture */
    0x02,              /* iProduct */
    0x03,              /* iSerialNumber -  is required for BOT device */
    0x01               /* bNumConfigurations */
};

/*!<USB Configure Descriptor */
uint8_t gu8ConfigDescriptor[] =
{
    LEN_CONFIG,                                         // bLength
    DESC_CONFIG,                                        // bDescriptorType
    (LEN_CONFIG+LEN_INTERFACE+LEN_ENDPOINT*2), 0x00,    // wTotalLength
    0x01,                                               // bNumInterfaces
    0x01,                                               // bConfigurationValue
    0x00,                                               // iConfiguration
    0xC0,                                               // bmAttributes
    0x32,                                               // MaxPower

    /* const BYTE cbyInterfaceDescriptor[LEN_INTERFACE] = */
    LEN_INTERFACE,  // bLength
    DESC_INTERFACE, // bDescriptorType
    0x00,           // bInterfaceNumber
    0x00,           // bAlternateSetting
    0x02,           // bNumEndpoints
    0x08,           // bInterfaceClass
    0x06,           // bInterfaceSubClass
    0x50,           // bInterfaceProtocol
    0x00,           // iInterface

    /* const BYTE cbyEndpointDescriptor1[LEN_ENDPOINT] = */
    LEN_ENDPOINT,           // bLength
    DESC_ENDPOINT,          // bDescriptorType
    0x82,                   // bEndpointAddress
    EP_BULK,                // bmAttributes
    EP2_MAX_PKT_SIZE, 0x00, // wMaxPacketSize
    0x00,                   // bInterval

    /* const BYTE cbyEndpointDescriptor2[LEN_ENDPOINT] = */
    LEN_ENDPOINT,           // bLength
    DESC_ENDPOINT,          // bDescriptorType
    0x03,                   // bEndpointAddress
    EP_BULK,                // bmAttributes
    EP3_MAX_PKT_SIZE, 0x00,  // wMaxPacketSize
    0x00                    // bInterval
};

/*!<USB Language String Descriptor */
uint8_t gu8StringLang[4] =
{
    4,              /* bLength */
    DESC_STRING,    /* bDescriptorType */
    0x09, 0x04
};

/*!<USB Vendor String Descriptor */
uint8_t gu8VendorStringDesc[] =
{
    16,
    DESC_STRING,
    'N', 0, 'u', 0, 'v', 0, 'o', 0, 't', 0, 'o', 0, 'n', 0
};

/*!<USB Product String Descriptor */
uint8_t gu8ProductStringDesc[] =
{
    22,             /* bLength          */
    DESC_STRING,    /* bDescriptorType  */
    'U', 0, 'S', 0, 'B', 0, ' ', 0, 'D', 0, 'e', 0, 'v', 0, 'i', 0, 'c', 0, 'e', 0
};

uint8_t gu8StringSerial[] =
{
    26,             // bLength
    DESC_STRING,    // bDescriptorType
    'A', 0, '0', 0, '2', 0, '0', 0, '0', 0, '8', 0, '0', 0, '4', 0, '0', 0, '1', 0, '1', 0, '4', 0
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

const S_USBD_INFO_T gsInfo =
{
    (uint8_t *)gu8DeviceDescriptor,
    (uint8_t *)gu8ConfigDescriptor,
    (uint8_t **)gpu8UsbString,
    NULL,
    NULL,
    NULL,
    NULL
};


