/**************************************************************************//**
 * @file     descriptors.c
 * @brief    M480 series USBD driver source file
 * @version  2.0.0
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
/*!<Includes */
#include "NuMicro.h"
#include "hid_touch.h"

/*!<USB HID Report Descriptor */
uint8_t HID_DigitizerReportDescriptor[] =
{
    0x05, 0x0D,         // USAGE_PAGE (Digitizers)
    0x09, 0x04,         // USAGE (Touch Screen)
    0xA1, 0x01,         // COLLECTION (Application)
    0x85, 0x01,         // REPORT_ID (1)
    0x09, 0x22,         // USAGE (Finger)

    0xA1, 0x02,         // COLLECTION (Logical)
    0x09, 0x42,         // USAGE (Tip Switch)
    0x15, 0x00,         // LOGICAL_MINIMUM (0)
    0x25, 0x01,         // LOGICAL_MAXIMUM (1)
    0x75, 0x01,         // REPORT_SIZE (1)
    0x95, 0x01,         // REPORT_COUNT (1)
    0x81, 0x02,         // INPUT (Data,Var,Abs)
    0x09, 0x32,         // USAGE (In Range)
    0x81, 0x02,         // INPUT (Data,Var,Abs)
    0x09, 0x47,         // USAGE (Touch Valid)
    0x81, 0x02,         // INPUT (Data,Var,Abs)
    0x95, 0x05,         // REPORT_COUNT (5)
    0x81, 0x03,         // INPUT (Cnst,Ary,Abs)
    0x75, 0x08,         // REPORT_SIZE (8)
    0x09, 0x51,         // USAGE (Contact Identifier)
    0x95, 0x01,         // REPORT_COUNT (1)
    0x81, 0x02,         // INPUT (Data,Var,Abs)
    0x05, 0x01,         // USAGE_PAGE (Generic Desktop)
    0x75, 0x10,         // REPORT_SIZE (16)
    0x55, 0x0E,         // UNIT_EXPONENT (-2)
    0x65, 0x11,         // UNIT (Centimeter)
    0x09, 0x30,         // USAGE (X)
    0x35, 0x00,         // PHYSICAL_MINIMUM (0)
    0x46, 0xE3, 0x13,       // PHYSICAL_MAXIMUM (0x13E3)
    0x26, 0x7F, 0x07,       // LOGICAL_MAXIMUM (0x77F)
    0x81, 0x02,         // INPUT (Data,Var,Abs)
    0x09, 0x31,         // USAGE (Y)
    0x46, 0x2F, 0x0B,       // PHYSICAL_MAXIMUM (0xB2F)
    0x26, 0x37, 0x04,       // LOGICAL_MAXIMUM (0x437)
    0x81, 0x02,         // INPUT (Data,Var,Abs)
    0xC0,               // END_COLLECTION

    0xA1, 0x02,         // COLLECTION (Logical)
    0x05, 0x0D,         // USAGE_PAGE (Digitizers)
    0x09, 0x42,         // USAGE (Tip Switch)
    0x15, 0x00,         // LOGICAL_MINIMUM (0)
    0x25, 0x01,         // LOGICAL_MAXIMUM (1)
    0x75, 0x01,         // REPORT_SIZE (1)
    0x95, 0x01,         // REPORT_COUNT (1)
    0x81, 0x02,         // INPUT (Data,Var,Abs)
    0x09, 0x32,         // USAGE (In Range)
    0x81, 0x02,         // INPUT (Data,Var,Abs)
    0x09, 0x47,         // USAGE (Touch Valid)
    0x81, 0x02,         // INPUT (Data,Var,Abs)
    0x95, 0x05,         // REPORT_COUNT (5)
    0x81, 0x03,         // INPUT (Cnst,Ary,Abs)
    0x75, 0x08,         // REPORT_SIZE (8)
    0x09, 0x51,         // USAGE (Contact Identifier)
    0x95, 0x01,         // REPORT_COUNT (1)
    0x81, 0x02,         // INPUT (Data,Var,Abs)
    0x05, 0x01,         // USAGE_PAGE (Generic Desktop)
    0x75, 0x10,         // REPORT_SIZE (16)
    0x55, 0x0E,         // UNIT_EXPONENT (-2)
    0x65, 0x11,         // UNIT (Centimeter)
    0x09, 0x30,         // USAGE (X)
    0x35, 0x00,         // PHYSICAL_MINIMUM (0)
    0x46, 0xE3, 0x13,       // PHYSICAL_MAXIMUM (0x13E3)
    0x26, 0x7F, 0x07,       // LOGICAL_MAXIMUM (0x77F)
    0x81, 0x02,         // INPUT (Data,Var,Abs)
    0x46, 0x2F, 0x0B,       // PHYSICAL_MAXIMUM (0xB2F)
    0x26, 0x37, 0x04,       // LOGICAL_MAXIMUM (0x437)
    0x09, 0x31,         // USAGE (Y)
    0x81, 0x02,         // INPUT (Data,Var,Abs)
    0xC0,               // END_COLLECTION

    0x05, 0x0D,         // USAGE_PAGE (Digitizers)
    0x09, 0x54,         // USAGE (Contact Count)
    0x15, 0x00,         // LOGICAL_MINIMUM (0)
    0x26, 0xFF, 0x00,       // LOGICAL_MAXIMUM (0x00FF)
    0x95, 0x01,         // REPORT_COUNT (1)
    0x75, 0x08,         // REPORT_SIZE (8)
    0x81, 0x02,         // INPUT (Data,Var,Abs)
    0x09, 0x55,         // USAGE (Contact Count Maximum)
    0x25, 0x02,         // LOGICAL_MAXIMUM (2)
    0x95, 0x01,         // REPORT_COUNT (1)
    0x85, 0x02,         // REPORT_ID (2)
    0xB1, 0x02,         // FEATURE (Data,Var,Abs)
    0xC0                // END_COLLECTION
};


/*----------------------------------------------------------------------------*/
/*!<USB Device Descriptor */
uint8_t gu8DeviceDescriptor[] =
{
    LEN_DEVICE,     /* bLength */
    DESC_DEVICE,    /* bDescriptorType */
    0x01, 0x02,     /* bcdUSB */
    0x00,           /* bDeviceClass */
    0x00,           /* bDeviceSubClass */
    0x00,           /* bDeviceProtocol */
    EP0_MAX_PKT_SIZE,   /* bMaxPacketSize0 */
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

/*!<USB Configure Descriptor */
uint8_t gu8ConfigDescriptor[] =
{
    LEN_CONFIG,     /* bLength */
    DESC_CONFIG,    /* bDescriptorType */
    /* wTotalLength */
    LEN_CONFIG_AND_SUBORDINATE & 0x00FF,
    ((LEN_CONFIG_AND_SUBORDINATE & 0xFF00) >> 8),
    0x01,           /* bNumInterfaces */
    0x01,           /* bConfigurationValue */
    0x00,           /* iConfiguration */
    0x80 | (USBD_SELF_POWERED << 6) | (USBD_REMOTE_WAKEUP << 5),/* bmAttributes */
    USBD_MAX_POWER, /* MaxPower */

    /* I/F descr: HID */
    LEN_INTERFACE,  /* bLength */
    DESC_INTERFACE, /* bDescriptorType */
    0x00,           /* bInterfaceNumber */
    0x00,           /* bAlternateSetting */
    0x01,           /* bNumEndpoints */
    0x03,           /* bInterfaceClass */
    0x00,           /* bInterfaceSubClass */
    HID_NONE,       /* bInterfaceProtocol */
    0x00,           /* iInterface */

    /* HID Descriptor */
    LEN_HID,        /* Size of this descriptor in UINT8s. */
    DESC_HID,       /* HID descriptor type. */
    0x10, 0x01,     /* HID Class Spec. release number. */
    0x00,           /* H/W target country. */
    0x01,           /* Number of HID class descriptors to follow. */
    DESC_HID_RPT,   /* Descriptor type. */
    /* Total length of report descriptor. */
    sizeof(HID_DigitizerReportDescriptor) & 0x00FF,
    ((sizeof(HID_DigitizerReportDescriptor) & 0xFF00) >> 8),

    /* EP Descriptor: interrupt in. */
    LEN_ENDPOINT,   /* bLength */
    DESC_ENDPOINT,  /* bDescriptorType */
    (INT_IN_EP_NUM | EP_INPUT), /* bEndpointAddress */
    EP_INT,         /* bmAttributes */
    /* wMaxPacketSize */
    EP2_MAX_PKT_SIZE & 0x00FF,
    ((EP2_MAX_PKT_SIZE & 0xFF00) >> 8),
    HID_DEFAULT_INT_IN_INTERVAL     /* bInterval */
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
    20,
    DESC_STRING,
    'H', 0, 'I', 0, 'D', 0, ' ', 0, 'T', 0, 'o', 0, 'u', 0, 'c', 0, 'h', 0
};

/*!<USB BOS Descriptor */
uint8_t gu8BOSDescriptor[] =
{
    LEN_BOS,        /* bLength */
    DESC_BOS,       /* bDescriptorType */
    /* wTotalLength */
    0x0C & 0x00FF,
    ((0x0C & 0xFF00) >> 8),
    0x01,           /* bNumDeviceCaps */

    /* Device Capability */
    LEN_BOSCAP,     /* bLength */
    DESC_CAPABILITY,/* bDescriptorType */
    CAP_USB20_EXT,  /* bDevCapabilityType */
    0x02, 0x00, 0x00, 0x00  /* bmAttributes */
};

uint8_t *gpu8UsbString[4] =
{
    gu8StringLang,
    gu8VendorStringDesc,
    gu8ProductStringDesc,
    NULL,
};

uint8_t *gu8UsbHidReport[3] =
{
    HID_DigitizerReportDescriptor,
    NULL,
    NULL,
};

uint32_t gu32UsbHidReportLen[3] =
{
    sizeof(HID_DigitizerReportDescriptor),
    0,
    0,
};

uint32_t gu32ConfigHidDescIdx[3] =
{
    (LEN_CONFIG+LEN_INTERFACE),
    0,
    0,
};


const S_USBD_INFO_T gsInfo =
{
    (uint8_t *)gu8DeviceDescriptor,
    (uint8_t *)gu8ConfigDescriptor,
    (uint8_t **)gpu8UsbString,
    (uint8_t **)gu8UsbHidReport,
    (uint8_t *)gu8BOSDescriptor,
    (uint32_t *)gu32UsbHidReportLen,
    (uint32_t *)gu32ConfigHidDescIdx
};

