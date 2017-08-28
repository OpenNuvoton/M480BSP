/******************************************************************************
 * @file     descriptors.c
 * @brief    NuMicro series HSUSBD driver source file
 * @version  1.0.0
 * @date     03, Sep, 2016
 *
 * @note
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
/*!<Includes */
#include "NuMicro.h"
#include "usbd_audio.h"

/*----------------------------------------------------------------------------*/
/*!<USB Device Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8DeviceDescriptor[] = {
#else
__align(4) uint8_t gu8DeviceDescriptor[] = {
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
    (USBD_VID & 0xFF00) >> 8,
    /* idProduct */
    USBD_PID & 0x00FF,
    (USBD_PID & 0xFF00) >> 8,
    0x00, 0x00,     /* bcdDevice */
    0x01,           /* iManufacture */
    0x02,           /* iProduct */
    0x00,           /* iSerialNumber - no serial */
    0x01            /* bNumConfigurations */
};

/*!<USB Qualifier Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8QualifierDescriptor[] = {
#else
__align(4) uint8_t gu8QualifierDescriptor[] = {
#endif
    LEN_QUALIFIER,  /* bLength */
    DESC_QUALIFIER, /* bDescriptorType */
    0x00, 0x02,     /* bcdUSB */
    0x00,           /* bDeviceClass */
    0x00,           /* bDeviceSubClass */
    0x00,           /* bDeviceProtocol */
    CEP_MAX_PKT_SIZE, /* bMaxPacketSize0 */
    0x01,           /* bNumConfigurations */
    0x00
};

/*!<USB Configure Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8ConfigDescriptor[] = {
#else
__align(4) uint8_t gu8ConfigDescriptor[] = {
#endif

    LEN_CONFIG,     /* bLength */
    DESC_CONFIG,    /* bDescriptorType */
    0x18, 0x01,     /* wTotalLength */
    0x04,           /* bNumInterfaces */
    0x01,           /* bConfigurationValue */
    0x00,           /* iConfiguration */
    0x80,           /* bmAttributes */
    0x32,           /* Max power */

    /* Standard Interface Association Descriptor */
    0x08,           /* bLength(0x08) */
    0x0B,           /* bDescriptorType(0x0B) */
    0x00,           /* bFirstInterface(0x01) */
    0x03,           /* bInterfaceCount(0x02) */
    0x01,           /* bFunctionClass(0x01): AUDIO */
    0x00,           /* bFunctionSubClass(0x00) */
    0x20,           /* bFunctionProtocol(0x2000): 2.0 AF_VERSION_02_00 */
    0x00,           /* iFunction(0x00) */

    /* Standard AC interface */
    0x09,           /* bLength */
    0x04,           /* bDescriptorType */
    0x00,           /* bInterfaceNumber */
    0x00,           /* bAlternateSetting */
    0x00,           /* bNumEndpoints */
    0x01,           /* bInterfaceClass:AUDIO */
    0x01,           /* bInterfaceSubClass:AUDIOCONTROL */
    0x20,           /* bInterfaceProtocol */
    0x02,           /* iInterface */

    /* Class-spec AC interface descriptor */
    0x09,           /* bLength */
    0x24,           /* bDescriptorType:CS_INTERFACE */
    0x01,           /* bDescriptorSubType:HEADER */
    0x00,0x02,      /* bcdADC:2.0 */
    0x08,           /* UAC_FUNCTION_IO_BOX */
    9+8+8+2*(0x11+0x12+0x0C), 0x00,   /* wTotalLength */
    0x0,            /* bmControls(0b00000000)  */

    /* bClockID 0x10: Clock Source Descriptor(4.7.2.1) */
    0x08,           /* bLength(0x08) */
    0x24,           /* bDescriptorType(0x24): CS_INTERFACE */
    0x0A,           /* bDescriptorSubType(0x0A): CLOCK_SOURCE */
    0x29,           /* bClockID(0x10): CLOCK_SOURCE_ID */
    0x03,           /* bmAttributes(0x01): internal fixed clock */
    0x07,           /* bmControls(0x07):
                       clock frequency control: 0b11 - host programmable;
                       clock validity control: 0b01 - host read only */
    0x00,           /* bAssocTerminal(0x00) */
    0x00,           /* iClockSource(0x01): Not requested */

    /********************************/
    0x08,
    0x24,
    0x0B,
    0x28,
    0x01,
    0x29,
    0x03,
    0x08,

    /* Audio_Out Input Terminal Descriptor (Speaker) - OK */
    0x11,               /* bLength */
    0x24,               /* bDescriptorType:CS_INTERFACE */
    0x02,               /* bDescriptorSubType:INPUT_TERMINAL */
    0x02,               /* bTerminalID */
    0x01,0x01,          /* wTerminalType: 0x0101 usb streaming */
    0x00,               /* bAssocTerminal */
    0x28,               /* bCSourceID(0x10): CLOCK_SOURCE_ID */
    0x02,               /* bNrChannels */
    0x00,0x00,0x00, 0x00,   /* wChannelConfig */
    0x00,               /* iChannelNames */
    0x00, 0x00,         /* bmcontrols */
    0x00,               /* iTerminal */

    /* Audio_Out Feature Unit Descriptor (Speaker) */
    0x12,                   /* bLength */
    0x24,                   /* bDescriptorType */
    0x06,                   /* bDescriptorSubType */
    0x0A,    /* bUnitID */
    0x02,                   /* bSourceID */
    0x00,0x00, 0x00, 0x00,  /* master control*/
    0x00,0x00, 0x00, 0x00,  /* left volume control */
    0x00,0x00, 0x00, 0x00,  /* right volume control */
    0x00,                   /* iFeature */

    /* Audio_Out Output Terminal Descriptor (Speaker) */
    0x0C,               /* bLength */
    0x24,               /* bDescriptorType:CS_INTERFACE */
    0x03,               /* bDescriptorSubType:OUTPUT_TERMINAL */
    0x14,               /* bTerminalID */
    0x01,0x03,          /* wTerminalType: 0x0301 speaker */
    0x00,               /* bAssocTerminal */
    0x0A,               /* bSourceID */
    0x28,               /* bCSourceID */
    0x00, 0x00,         /* bmControls */
    0x00,               /* iTerminal */

    /* Audio_In Input Terminal Descriptor (Microphone) */
    0x11,                       /* bLength*/
    0x24,                       /* bDescriptorType:CS_INTERFACE*/
    0x02,                       /* bDescriptorSubType:INPUT_TERMINAL*/
    0x01,                       /* bTerminalID*/
    0x01,0x02,                  /* wTerminalType: 0x0201 microphone*/
    0x00,                       /* bAssocTerminal*/
    0x28,                       /* bSourceID*/
    0x02,                       /* bNrChannels*/
    0x00,0x00,0x00, 0x00, /* wChannelConfig */
    0x00,                       /* iChannelNames */
    0x00, 0x00,                 /* bmcontrols */
    0x00,                       /* iTerminal */

    /* Audio_In Feature Unit (Microphone) */
    0x12,                   /* bLength */
    0x24,                   /* bDescriptorType */
    0x06,                   /* bDescriptorSubType */
    0x0B,                   /* bUnitID */
    0x01,                   /* bSourceID */
    0x00,0x00, 0x00, 0x00,  /* master control*/
    0x00,0x00, 0x00, 0x00,  /* left volume control */
    0x00,0x00, 0x00, 0x00,  /* right volume control */
    0x00,                   /* iFeature */

    /* Audio_In Output Terminal Descriptor (Microphone) */
    0x0C,                   /* bLength*/
    0x24,                   /* bDescriptorType:CS_INTERFACE*/
    0x03,                   /* bDescriptorSubType:OUTPUT_TERMINAL*/
    0x16,                   /* bTerminalID*/
    0x01,0x01,              /* wTerminalType: 0x0101 */
    0x00,                   /* bAssocTerminal*/
    0x0B,                   /* bSourceID*/
    0x28,                   /* bCSourceID*/
    0x00, 0x00,             /*bmControls*/
    0x07,                   /* iTerminal*/

    /* Standard AS interface 1, alternate 0 */
    0x09,           /* bLength */
    0x04,           /* bDescriptorType */
    0x01,           /* bInterfaceNumber */
    0x00,           /* bAlternateSetting */
    0x00,           /* bNumEndpoints */
    0x01,           /* bInterfaceClass:AUDIO */
    0x02,           /* bInterfaceSubClass:AUDIOSTREAMING */
    0x20,           /* bInterfaceProtocol */
    0x00,           /* iInterface */

    /* Standard AS interface 1, alternate 1 */
    0x09,           /* bLength */
    0x04,           /* bDescriptorType */
    0x01,           /* bInterfaceNumber */
    0x01,           /* bAlternateSetting */
    0x02,           /* bNumEndpoints */
    0x01,           /* bInterfaceClass:AUDIO */
    0x02,           /* bInterfaceSubClass:AUDIOSTREAMING */
    0x20,           /* bInterfaceProtocol */
    0x00,           /* iInterface */

    /* Class-Specific AS Interface Descriptor */
    0x10,                   /* bLength(16) */
    0x24,                   /* bDescriptorType(0x024): CS_INTERFACE */
    0x01,                   /* bDescriptorSubType(0x01): AS_GENERAL */
    0x02,                   /* bTerminalLink(0x20): INPUT_TERMINAL_ID */
    0x00,                   /* bmControls(0x00) */
    0x01,                   /* bFormatType(0x01): FORMAT_TYPE_I */
    0x01, 0x00, 0x00, 0x00, /* bmFormats(0x00000001): PCM */
    0x02,                   /* bNrChannels(0x02): NB_CHANNELS */
    0x00, 0x00, 0x00, 0x00, /* bmChannelCOnfig(0x00000003) */
    0x00,                   /* iChannelNames(0x00): None */

    /* Type I Format Type Descriptor(2.3.1.6 - Audio Formats) */
    0x06,       /* bLength(6) */
    0x24,       /* bDescriptorType(0x24): CS_INTERFACE */
    0x02,       /* bDescriptorSubtype(0x02): FORMAT_TYPE */
    0x01,       /* bFormatType(0x01): FORMAT_TYPE_I */
    0x02,       /* bSubSlotSize(0x02) */
    0x10,       /* bBitResolution(0x10): 16 bits per sample */

    /* Standard AS ISO Audio Data Endpoint, output, address 2, Max 200 */
    0x07,                       /* bLength */
    0x05,                       /* bDescriptorType */
    ISO_OUT_EP_NUM | EP_OUTPUT, /* bEndpointAddress */
    0x05,                       /* bmAttributes */
    (200)&0xff, ((200)>>8)&0xff,/* wMaxPacketSize */
    0x01,                       /* bInterval - Must be 1 for compliance */

    /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor (4.10.1.2) */
    0x08,                       /* bLength */
    0x25,                       /* bDescriptorType:CS_ENDPOINT */
    0x01,                       /* bDescriptorSubType:EP_GENERAL */
    0x00,                       /* bmAttributes */
    0x00,
    0x02,                       /* bmControls*/
    0x08, 0x00,                 /* wLockDelay */

    /* Audio_OUT Feedback EP */
    0x07,
    0x05,                               /* bDescriptorType: ENDPOINT */
    ISO_FEEDBACK_ENDPOINT | EP_INPUT,   /* bEndpointAddress (D3:0 - EP no. D6:4 - reserved 0. D7 - 0:out, 1:in) */
    0x11,                               /* bmAttributes (bitmap)  */
    0x04,0x0,                           /* wMaxPacketSize */
    0x04,                               /* bInterval - Must be 1 for compliance */

    /* Interface 2 :  Standard AS Interface Descriptor (4.9.1) (Alt) interface 2, alternate 0 */
    /* Standard AS interface 2, alternate 0 */
    0x09,           /* bLength */
    0x04,           /* bDescriptorType */
    0x02,           /* bInterfaceNumber */
    0x00,           /* bAlternateSetting */
    0x00,           /* bNumEndpoints */
    0x01,           /* bInterfaceClass:AUDIO */
    0x02,           /* bInterfaceSubClass:AUDIOSTREAMING */
    0x20,           /* bInterfaceProtocol */
    0x00,           /* iInterface */

    /* Interface 2 :  Standard AS interface 2, alternate 1 */
    0x09,           /* bLength */
    0x04,           /* bDescriptorType */
    0x02,           /* bInterfaceNumber */
    0x01,           /* bAlternateSetting */
    0x01,           /* bNumEndpoints */
    0x01,           /* bInterfaceClass:AUDIO */
    0x02,           /* bInterfaceSubClass:AUDIOSTREAMING */
    0x20,           /* bInterfaceProtocol */
    0x00,           /* iInterface */

    /* Class-Specific AS Interface Descriptor */
    0x10,                   /* bLength(16) */
    0x24,                   /* bDescriptorType(0x024): CS_INTERFACE */
    0x01,                   /* bDescriptorSubType(0x01): AS_GENERAL */
    0x16,                   /* bTerminalLink(0x20): INPUT_TERMINAL_ID */
    0x00,                   /* bmControls(0x00) */
    0x01,                   /* bFormatType(0x01): FORMAT_TYPE_I */
    0x01, 0x00, 0x00, 0x00, /* bmFormats(0x00000001): PCM */
    0x02,                   /* bNrChannels(0x02): NB_CHANNELS */
    0x00, 0x00, 0x00, 0x00, /* bmChannelCOnfig(0x00000003) */
    0x00,                   /* iChannelNames(0x00): None */

    /* Type I Format Type Descriptor(2.3.1.6 - Audio Formats) */
    0x06,       /* bLength(6) */
    0x24,       /* bDescriptorType(0x24): CS_INTERFACE */
    0x02,       /* bDescriptorSubtype(0x02): FORMAT_TYPE */
    0x01,       /* bFormatType(0x01): FORMAT_TYPE_I */
    0x02,       /* bSubSlotSize(0x02) */
    0x10,       /* bBitResolution(0x10): 16 bits per sample */

    /* Standard AS ISO Audio Data Endpoint, output, address 2, Max 200 */
    0x07,                       /* bLength */
    0x05,                       /* bDescriptorType */
    ISO_IN_EP_NUM | EP_INPUT,   /* bEndpointAddress */
    0x05,                       /* bmAttributes */
    (200)&0xff, ((200)>>8)&0xff,/* wMaxPacketSize */
    0x01,                       /* bInterval - Must be 1 for compliance */

    /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor (4.10.1.2) */
    0x08,       /* bLength */
    0x25,       /* bDescriptorType:CS_ENDPOINT */
    0x01,       /* bDescriptorSubType:EP_GENERAL */
    0x00,       /* bmAttributes */
    0x00,
    0x02,       /* bmControls*/
    0x08, 0x00, /* wLockDelay */

    /*****************************/
    0x09,
    0x04,
    0x03,
    0x00,
    0x00,
    0xFE,
    0x01,
    0x01,
    0x00,

    0x09,
    0x21,
    0x07,
    0xFA, 0x00,
    0x40, 0x00,
    0x10, 0x01,
};


/*!<USB Language String Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8StringLang[4] = {
#else
__align(4) uint8_t gu8StringLang[4] = {
#endif
    4,              /* bLength */
    DESC_STRING,    /* bDescriptorType */
    0x09, 0x04
};

/*!<USB Vendor String Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8VendorStringDesc[] = {
#else
__align(4) uint8_t gu8VendorStringDesc[] = {
#endif
    16,
    DESC_STRING,
    'N', 0, 'u', 0, 'v', 0, 'o', 0, 't', 0, 'o', 0, 'n', 0
};

/*!<USB Product String Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8ProductStringDesc[] = {
#else
__align(4) uint8_t gu8ProductStringDesc[] = {
#endif
    20,
    DESC_STRING,
    'U', 0, 'S', 0, 'B', 0, ' ', 0, 'A', 0, 'u', 0, 'd', 0, 'i', 0, 'o', 0
};

uint8_t *gpu8UsbString[4] = {
    gu8StringLang,
    gu8VendorStringDesc,
    gu8ProductStringDesc,
    NULL,
};

uint8_t *gu8UsbHidReport[3] = {
    NULL,
    NULL,
    NULL,
};

uint32_t gu32UsbHidReportLen[3] = {
    0,
    0,
    0,
};

S_HSUSBD_INFO_T gsHSInfo = {
    gu8DeviceDescriptor,
    gu8ConfigDescriptor,
    gpu8UsbString,
    gu8QualifierDescriptor,
    gu8ConfigDescriptor,
    gu8ConfigDescriptor,
    gu8ConfigDescriptor,
    gu8UsbHidReport,
    gu32UsbHidReportLen,
    0,
    0,
};

