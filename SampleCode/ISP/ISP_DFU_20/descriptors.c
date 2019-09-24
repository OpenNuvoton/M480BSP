/***************************************************************************//**
 * @file     descriptors.c
 * @brief    M480 series USBD driver source file
 * @version  2.0.0
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include "NuMicro.h"
#include "dfu_transfer.h"

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
    0x00,   /* bDeviceClass : See interface */
    0x00,   /* bDeviceSubClass : See interface*/
    0x00,   /* bDeviceProtocol : See interface */
    CEP_MAX_PKT_SIZE,   /* bMaxPacketSize0 */
    /* idVendor */
    USBD_VID & 0x00FF,
    ((USBD_VID & 0xFF00) >> 8),
    /* idProduct */
    USBD_PID & 0x00FF,
    (USBD_PID & 0xFF00) >> 8,
    0x00,   /* bcdDevice*/
    0x01,
    0x01,   /* iManufacturer : index of string Manufacturer  */
    0x02,   /* iProduct      : index of string descriptor of product*/
    0x03,   /* iSerialNumber : index of string serial number*/
    0x01    /*bNumConfigurations */
};

#define u8_usbConfigDescriptorDFU_LENGTH      (18 + (9 * 1))

/*!<USB Configure Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8ConfigDescriptor[] =
#else
uint8_t gu8ConfigDescriptor[] __attribute__((aligned(4))) =
#endif
{
    0x09,   /* bLength: Configuation Descriptor size */
    0x02,   /* bDescriptorType: Configuration */
    u8_usbConfigDescriptorDFU_LENGTH,   /* wTotalLength: Bytes returned */
    0x00,
    0x01,   /* bNumInterfaces: 1 interface */
    0x01,   /* bConfigurationValue: */
    0x00,   /* iConfiguration: */
    0x80,   /* bmAttributes: */
    0x32,   /* MaxPower 100 mA */
    /* 09 */

    /************ Descriptor of DFU interface 0 Alternate setting 0 *********/
    0x09,   /* bLength: Interface Descriptor size */
    0x04,   /* bDescriptorType: */
    0x00,   /* bInterfaceNumber: Number of Interface */
    0x00,   /* bAlternateSetting: Alternate setting */
    0x00,   /* bNumEndpoints*/
    0xFE,   /* bInterfaceClass: DFU */
    0x01,   /* bInterfaceSubClass */
    0x02,   /* nInterfaceProtocol, switched to 0x02 while in dfu_mode */
    0x00,   /* iInterface: */

    /******************** DFU Functional Descriptor********************/
    0x09,   /*blength = 7 Bytes*/
    0x21,   /* DFU Functional Descriptor*/
    0x0B,   /*bmAttributes, bitCanDnload | bitCanUpload */
    0xFF,   /*DetachTimeOut= 255 ms*/
    0x00,
    (TRANSFER_SIZE & 0x00FF),
    (TRANSFER_SIZE & 0xFF00) >> 8, /* TransferSize = 1024 Byte*/
    0x10,                          /* bcdDFUVersion = 1.1 */
    0x01
};

/*!<USB Language String Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8StringLang[4] =
#else
uint8_t gu8StringLang[4] __attribute__((aligned(4))) =
#endif
{
    4,              /* bLength */
    DESC_STRING,    /* bDescriptorType */
    0x09, 0x04
};

/*!<USB Vendor String Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8VendorStringDesc[] =
#else
uint8_t gu8VendorStringDesc[] __attribute__((aligned(4))) =
#endif
{
    16,
    DESC_STRING,
    'N', 0, 'u', 0, 'v', 0, 'o', 0, 't', 0, 'o', 0, 'n', 0
};

/*!<USB Product String Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8ProductStringDesc[] =
#else
uint8_t gu8ProductStringDesc[] __attribute__((aligned(4))) =
#endif
{
    14,
    DESC_STRING,
    'N', 0, 'u', 0, '_', 0, 'D', 0, 'F', 0, 'U', 0
};

#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8StringSerial[] =
#else
uint8_t gu8StringSerial[] __attribute__((aligned(4))) =
#endif
{
    4,             // bLength
    DESC_STRING,   // bDescriptorType
    '1', 0
};

