/**************************************************************************//**
 * @file     descriptors.c
 * @version  V1.00
 * @brief    NuMicro series HSUSBD driver source file
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
/*!<Includes */
#include "NuMicro.h"
#include "usbd_audio.h"

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
    CEP_MAX_PKT_SIZE, /* bMaxPacketSize0 */
    0x01,           /* bNumConfigurations */
    0x00
};

#ifdef __HID__
#ifdef __JOYSTICK__
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t HID_DeviceReportDescriptor[] =
#else
uint8_t HID_DeviceReportDescriptor[] __attribute__((aligned(4))) =
#endif
{
    0x05, 0x01,        /* Usage Page(Generic Desktop Controls) */
    0x09, 0x04,        /* Usage(Joystick) */
    0xA1, 0x01,        /* Collection(Application)  */
    0xA1, 0x02,        /* Collection(Logical)  */
    0x75, 0x08,        /* Report Size(0x8) */
    0x95, 0x05,        /* Report Count(0x5) */
    0x15, 0x00,        /* Logical Minimum(0x0) */
    0x26, 0xFF, 0x00,  /* Logical Maximum(0xFF) */
    0x35, 0x00,        /* Physical Minimum(0x0) */
    0x46, 0xFF, 0x00,  /* Physical Maximum(0xFF) */
    0x09, 0x30,        /* Usage(X) */
    0x09, 0x31,        /* Usage(Y) */
    0x09, 0x32,        /* Usage(Z) */
    0x09, 0x32,        /* Usage(Z) */
    0x09, 0x35,        /* Usage(Rz) */
    0x81, 0x02,        /* Input(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field) */
    0x75, 0x04,        /* Report Size(0x4) */
    0x95, 0x01,        /* Report Count(0x1) */
    0x25, 0x07,        /* Logical Maximum(0x7) */
    0x46, 0x3B, 0x01,  /* Physical Maximum(0x13B) */
    0x65, 0x14,        /* Unit(0x14) */
    0x09, 0x39,        /* Usage(Hat switch) */
    0x81, 0x42,        /* Input(Data, Variable, Absolute, No Wrap, Linear, Preferred State, Null State, Bit Field) */
    0x65, 0x00,        /* Unit(0x0) */
    0x75, 0x01,        /* Report Size(0x1) */
    0x95, 0x0C,        /* Report Count(0xC) */
    0x25, 0x01,        /* Logical Maximum(0x1) */
    0x45, 0x01,        /* Physical Maximum(0x1) */
    0x05, 0x09,        /* Usage Page(Button) */
    0x19, 0x01,        /* Usage Minimum(0x1) */
    0x29, 0x0C,        /* Usage Maximum(0xC) */
    0x81, 0x02,        /* Input(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field) */
    0x06, 0x00, 0xFF,  /* Usage Page(Undefined) */
    0x75, 0x01,        /* Report Size(0x1) */
    0x95, 0x08,        /* Report Count(0x8) */
    0x25, 0x01,        /* Logical Maximum(0x1) */
    0x45, 0x01,        /* Physical Maximum(0x1) */
    0x09, 0x01,        /* Usage(1) */
    0x81, 0x02,        /* Input(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field) */
    0xC0,              /* End Collection */
    0xC0,              /* End Collection */
};

#elif defined __MEDIAKEY__
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t HID_DeviceReportDescriptor[] =
#else
uint8_t HID_DeviceReportDescriptor[] __attribute__((aligned(4))) =
#endif
{
    0x05, 0x0C,        /* Usage Page (Consumer) */
    0x09, 0x01,        /* Usage(Consumer Control) */
    0xA1, 0x01,        /* Collection(Application) */
    0x15, 0x00,        /* Logical Minimum(0x0) */
    0x25, 0x01,        /* Logical Maximum(0x1) */
    0x09, 0xE2,        /* Usage(Mute) */
    0x09, 0xE9,        /* Usage(Volume Increment) */
    0x09, 0xEA,        /* Usage(Volume Decrement) */
    0x75, 0x01,        /* Report Size(0x1) */
    0x95, 0x03,        /* Report Count(0x3) */
    0x81, 0x02,        /* Input(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field) */
    0x75, 0x01,        /* Report Size(0x1) */
    0x95, 0x05,        /* Report Count(0x5) */
    0x81, 0x03,        /* Input(Constant, Variable, Absolute) */
    0x09, 0xB0,        /* Usage(Play) */
    0x09, 0xB7,        /* Usage(Stop) */
    0x09, 0xCD,        /* Usage(Play/Pause) */
    0x09, 0xB5,        /* Usage(Scan Next Track) */
    0x09, 0xB6,        /* Usage(Scan Previous Track) */
    0x09, 0xB2,        /* Usage(Record) */
    0x09, 0xB4,        /* Usage(Rewind) */
    0x09, 0xB3,        /* Usage(Fast Forward) */
    0x75, 0x01,        /* Report Size(0x1) */
    0x95, 0x08,        /* Report Count(0x8) */
    0x81, 0x02,        /* Input(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field) */
    0x09, 0x00,        /* Usage(Undefined) */
    0x75, 0x08,        /* Report Size(0x8) */
    0x95, 0x06,        /* Report Count(0x6) */
    0x81, 0x02,        /* Input(Data, Variable, Absolute, No Wrap, Linear, Preferred State, No Null Position, Bit Field) */
    0x09, 0x00,        /* Usage(Undefined) */
    0x75, 0x08,        /* Report Size(0x8) */
    0x95, 0x08,        /* Report Count(0x8) */
    0x91, 0x00,        /* Output(Data, Array, Absolute, No Wrap, Linear, Preferred State, No Null Position, Non VolatileBit Field) */
    0xC0
};

#endif
#endif


/*!<USB Configure Descriptor */
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t gu8ConfigDescriptor[] =
{
#else
uint8_t gu8ConfigDescriptor[] __attribute__((aligned(4))) =
{
#endif

    /* Configuration Descriptor */
    LEN_CONFIG,         /* Config Descriptor Length */
    DESC_CONFIG,        /* DescriptorType: CONFIG */

#ifdef __HID__
    0x17, 0x01,         /* wTotalLength 0xFE+0x19 */
    0x04,               /* bNumInterfaces - Interface 0, Interface 1 (Speaker), Interface 2 (Microphone), Interface 3 (HID) */
#else
    0xFE, 0x00,         /* wTotalLength
                           Configuration Descriptor                      (0x09)
                           Standard Interface Association Descriptor     (0x08)
                           Standard AC Interface Descriptor              (0x09)
                           Class-Specific AC Interface Header Descriptor (0x09)
                           Clock Source Descriptor                       (0x08)
                           Microphone - Audio Control
                             Input Terminal Descriptor                   (0x11)
                             Feature Unit Descriptor                     (0x12)
                             Output Terminal Descriptor                  (0x0C)
                           Speaker - Audio Control
                             Input Terminal Descriptor                   (0x11)
                             Feature Unit Descriptor                     (0x12)
                             Output Terminal Descriptor                  (0x0C)
                           Microphone - Interface alternate 0
                             Standard AS interface                       (0x09)
                           Microphone - Interface alternate 1~2
                             Standard AC Interface Descriptor                             (0x09,0x09)
                             Class-Specific AS Interface Descriptor                       (0x10,0x10)
                             Audio Format Type Descriptor                                 (0x06,0x06)
                             Standard AS Isochronous Feedback Endpoint Descriptor         (0x07,0x07)
                             Class-Specific AS Isochronous Audio Data Endpoint Descriptor (0x08,0x08)
                             *Each Interface alternate Summary                            (0x2E,0x2E)
                           Speaker - Interface alternate 0
                             Standard AS interface                       (0x09)
                           Speaker - Interface alternate 1~2
                             Standard AC Interface Descriptor                             (0x09,0x09)
                             Class-Specific AS Interface Descriptor                       (0x10,0x10)
                             Audio Format Type Descriptor                                 (0x06,0x06)
                             Standard AS Isochronous Feedback Endpoint Descriptor         (0x07,0x07)
                             Class-Specific AS Isochronous Audio Data Endpoint Descriptor (0x08,0x08)
                             AS Isochronous Feedback Endpoint Descriptor                  (0x07,0x07)
                             *Each Interface alternate Summary                            (0x35,0x35)

                           0x09 + 0x08 + 0x9 + 0x09 + 0x08 + (0x11 + 0x12 + 0x0C) + (0x11 + 0x12 + 0x0C) +
                           0x09 + 2 * 0x2E +
                           0x09 + 2 * 0x35 = 0x161
                        */
    0x03,               /* bNumInterfaces - Interface 0, Interface 1 (Speaker), Interface 2 (Microphone) */
#endif
    0x01,               /* bConfigurationValue */
    0x00,               /* iConfiguration */
    0x80,               /* bmAttributes */
    0x32,               /* bMaxPower */

    /* Standard Interface Association Descriptor */
    0x08,               /* bLength(0x08) */
    0x0B,               /* bDescriptorType(0x0B) */
    0x00,               /* bFirstInterface(0x00) */
    0x03,               /* bInterfaceCount(0x03) */
    0x01,               /* bFunctionClass(0x01): AUDIO */
    0x00,               /* bFunctionSubClass(0x00) */
    0x20,               /* bFunctionProtocol(0x2000): 2.0 AF_VERSION_02_00 */
    0x00,               /* iFunction(0x00) */

    /* Standard AC Interface Descriptor */
    0x09,               /* bLength */
    0x04,               /* bDescriptorType */
    0x00,               /* bInterfaceNumber */
    0x00,               /* bAlternateSetting */
    0x00,               /* bNumEndpoints */
    0x01,               /* bInterfaceClass:AUDIO */
    0x01,               /* bInterfaceSubClass:AUDIOCONTROL */
    0x20,               /* bInterfaceProtocol */
    0x02,               /* iInterface */

    /* Class-Specific AC Interface Header Descriptor */
    0x09,               /* bLength */
    0x24,               /* bDescriptorType:CS_INTERFACE */
    0x01,               /* bDescriptorSubType:HEADER */
    0x00, 0x02,         /* bcdADC:2.0 */
    0x08,               /* UAC_FUNCTION_IO_BOX */
    0x6F, 0x00,         /* wTotalLength
                           Class-Specific AC Interface Header Descriptor (0x09)
                           Clock Source Descriptor                       (0x08)
                           Speaker - Audio Control
                             Input Terminal Descriptor                   (0x11)
                             Feature Unit Descriptor                     (0x12)
                             Output Terminal Descriptor                  (0x0C)
                           Microphone - Audio Control
                             Input Terminal Descriptor                   (0x11)
                             Feature Unit Descriptor                     (0x12)
                             Output Terminal Descriptor                  (0x0C)

                           0x09 + 0x08 + (0x11 + 0x12 + 0x0C) + (0x11 + 0x12 + 0x0C) = 0x6F
                        */
    0x00,               /* bmControls(0b00000000) - D1..0: Latency Control */

    /* Clock Source Descriptor (bClockID 0x10) */
    0x08,               /* bLength(0x08) */
    0x24,               /* bDescriptorType(0x24): CS_INTERFACE */
    0x0A,               /* bDescriptorSubType(0x0A): CLOCK_SOURCE */
    CLOCK_SOURCE_ID,    /* bClockID(0x10): CLOCK_SOURCE_ID */
    0x03,               /* bmAttributes */
    0x07,               /* bmControls(0x07):
                           clock frequency control: 0b11 - host programmable;
                           clock validity control: 0b01 - host read only */
    0x00,               /* bAssocTerminal(0x00) */
    0x00,               /* iClockSource */

    /* Input Terminal Descriptor (Terminal ID 0x04 - Source ID 0x10) */
    0x11,                                   /* bLength*/
    0x24,                                   /* bDescriptorType:CS_INTERFACE*/
    0x02,                                   /* bDescriptorSubType:INPUT_TERMINAL*/
    0x04,                                   /* bTerminalID*/
    0x02, 0x04,                             /* wTerminalType: HEADSET */
    0x00,                                   /* bAssocTerminal*/
    0x10,                                   /* bSourceID*/
    REC_CHANNELS,                           /* bNrChannels*/
    REC_CH_CFG, 0x00, 0x00, 0x00,           /* wChannelConfig
                                                 Bit 0: Front Left - FL
                                                 Bit 1: Front Right - FR
                                                 Bit 2: Front Center - FC
                                                 Bit 3: Low Frequency Effects - LFE
                                                 Bit 4: Back Left - BL
                                                 Bit 5: Back Right - BR
                                                 Bit 6: Front Left of Center - FLC
                                                 Bit 7: FRONT RIght of Center - FRC
                                                 Bit 8: Back Center - BC
                                                 Bit 9: Side Left - SL
                                                 Bit 10: Side Right - SR
                                                 Bit 11: Top Center - TC
                                                 Bit 12: Top Front Left - TFL
                                                 Bit 13: Top Front Center - TFC
                                                 Bit 14: Top Front Right - TFR
                                                 Bit 15: Top Back Left - TBL
                                                 Bit 16: Top Back Center - TBC
                                                 Bit 17: Top Back Right - TBR
                                                 Bit 18: Top Front Left of Center - TFLC
                                                 Bit 19: Top Front Right of Center - TFRC
                                                 Bit 20: Left Low Frequency Effects - LLFE
                                                 Bit 21: Right Low Frequency Effects - RLFE
                                                 Bit 22: Top Side Left - TSL
                                                 Bit 23: Top Side Right - TSR
                                                 Bit 24: Bottom Center - BC
                                                 Bit 25: Back Left of Center - BLC
                                                 Bit 26: Back Right of Center - BRC
                                                 Bit 31: Raw Data - RD; Mutually exclusive with all other spatial locations
                                            */
    0x00,                                   /* iChannelNames */
    0x00, 0x00,                             /* bmcontrols
                                                 D1..0: Copy Protect Control
                                                 D3..2: Connector Control
                                                 D5..4: Overload Control
                                                 D7..6: Cluster Control
                                                 D9..8: Underflow Control
                                                 D11..10: Overflow Control
                                                 D15..12: Reserved, should set to 0
                                            */
    0x00,                                   /* iTerminal */

    /* Feature Unit Descriptor (Unit ID 0x05 - Source ID 0x4) */
    0x12,                                   /* bLength */
    0x24,                                   /* bDescriptorType */
    0x06,                                   /* bDescriptorSubType */
    REC_FEATURE_UNITID,                     /* bUnitID */
    0x04,                                   /* bSourceID */
    0x00, 0x00, 0x00, 0x00,                 /* bmaControls(0)
                                               Master control
                                                D1..0: Mute Control
                                                D3..2: Volume Control
                                                D5..4: Bass Control
                                                D7..6: Mid Control
                                                D9..8: Treble Control
                                                D11..10: Graphic Equalizer Control
                                                D13..12: Automatic Gain Control
                                                D15..14: Delay Control
                                                D17..16: Bass Control
                                                D19..18: Loudness Control
                                                D21..20: Input Gain Control
                                                D23..22: Input Gain Pad Control
                                                D25..24: Phase Inverter Control
                                                D27..26: Underflow Control
                                                D29..28: Overflow Control
                                                D31..30: Reserved, should set to 0
                                            */
    0x00, 0x00, 0x00, 0x00,                 /* bmaControls(1)
                                               Left volume control
                                                D1..0: Mute Control
                                                D3..2: Volume Control
                                                D5..4: Bass Control
                                                D7..6: Mid Control
                                                D9..8: Treble Control
                                                D11..10: Graphic Equalizer Control
                                                D13..12: Automatic Gain Control
                                                D15..14: Delay Control
                                                D17..16: Bass Control
                                                D19..18: Loudness Control
                                                D21..20: Input Gain Control
                                                D23..22: Input Gain Pad Control
                                                D25..24: Phase Inverter Control
                                                D27..26: Underflow Control
                                                D29..28: Overflow Control
                                                D31..30: Reserved, should set to 0
                                            */
    0x00, 0x00, 0x00, 0x00,                 /* bmaControls(2)
                                               Right volume control
                                                D1..0: Mute Control
                                                D3..2: Volume Control
                                                D5..4: Bass Control
                                                D7..6: Mid Control
                                                D9..8: Treble Control
                                                D11..10: Graphic Equalizer Control
                                                D13..12: Automatic Gain Control
                                                D15..14: Delay Control
                                                D17..16: Bass Control
                                                D19..18: Loudness Control
                                                D21..20: Input Gain Control
                                                D23..22: Input Gain Pad Control
                                                D25..24: Phase Inverter Control
                                                D27..26: Underflow Control
                                                D29..28: Overflow Control
                                                D31..30: Reserved, should set to 0
                                            */
    0x00,                                   /* iFeature */

    /* Output Terminal Descriptor (Terminal ID 0x02 - Source ID 0x5 - Clock Source ID 0x10) */
    0x0C,               /* bLength*/
    0x24,               /* bDescriptorType:CS_INTERFACE*/
    0x03,               /* bDescriptorSubType:OUTPUT_TERMINAL*/
    0x02,               /* bTerminalID*/
    0x01,0x01,          /* wTerminalType: 0x0101 */
    0x00,               /* bAssocTerminal*/
    REC_FEATURE_UNITID, /* bSourceID*/
    0x10,               /* bCSourceID*/
    0x00, 0x00,         /* bmControls
                             D1..0: Copy Protect Control
                             D3..2: Connector Control
                             D5..4: Overload Control
                             D7..6: Cluster Control
                             D9..8: Underflow Control
                             D11..10: Overflow Control
                             D15..12: Reserved, should set to 0
                        */
    0x00,               /* iTerminal*/
    /* Input Terminal Descriptor (Terminal ID 1 - Source ID 0x10) */
    0x11,                                   /* bLength */
    0x24,                                   /* bDescriptorType:CS_INTERFACE */
    0x02,                                   /* bDescriptorSubType:INPUT_TERMINAL */
    0x01,                                   /* bTerminalID */
    0x01,0x01,                              /* wTerminalType: 0x0101 usb streaming */
    0x00,                                   /* bAssocTerminal */
    CLOCK_SOURCE_ID,                        /* bCSourceID(0x10): CLOCK_SOURCE_ID */
    PLAY_CHANNELS,                          /* bNrChannels - */
    PLAY_CH_CFG, 0x00, 0x00, 0x00,          /* bmChannelConfig
                                                 Bit 0: Front Left - FL
                                                 Bit 1: Front Right - FR
                                                 Bit 2: Front Center - FC
                                                 Bit 3: Low Frequency Effects - LFE
                                                 Bit 4: Back Left - BL
                                                 Bit 5: Back Right - BR
                                                 Bit 6: Front Left of Center - FLC
                                                 Bit 7: FRONT RIght of Center - FRC
                                                 Bit 8: Back Center - BC
                                                 Bit 9: Side Left - SL
                                                 Bit 10: Side Right - SR
                                                 Bit 11: Top Center - TC
                                                 Bit 12: Top Front Left - TFL
                                                 Bit 13: Top Front Center - TFC
                                                 Bit 14: Top Front Right - TFR
                                                 Bit 15: Top Back Left - TBL
                                                 Bit 16: Top Back Center - TBC
                                                 Bit 17: Top Back Right - TBR
                                                 Bit 18: Top Front Left of Center - TFLC
                                                 Bit 19: Top Front Right of Center - TFRC
                                                 Bit 20: Left Low Frequency Effects - LLFE
                                                 Bit 21: Right Low Frequency Effects - RLFE
                                                 Bit 22: Top Side Left - TSL
                                                 Bit 23: Top Side Right - TSR
                                                 Bit 24: Bottom Center - BC
                                                 Bit 25: Back Left of Center - BLC
                                                 Bit 26: Back Right of Center - BRC
                                                 Bit 31: Raw Data - RD; Mutually exclusive with all other spatial locations
                                            */
    0x00,                                   /* iChannelNames */
    0x00, 0x00,                             /* bmcontrols
                                                 D1..0: Copy Protect Control
                                                 D3..2: Connector Control
                                                 D5..4: Overload Control
                                                 D7..6: Cluster Control
                                                 D9..8: Underflow Control
                                                 D11..10: Overflow Control
                                                 D15..12: Reserved, should set to 0
                                            */
    0x00,                                   /* iTerminal */

    /* Feature Unit Descriptor (Unit ID 0x06 - Source ID 0x1) */
    0x12,                                   /* bLength */
    0x24,                                   /* bDescriptorType */
    0x06,                                   /* bDescriptorSubType */
    PLAY_FEATURE_UNITID,                    /* bUnitID */
    0x01,                                   /* bSourceID */
    0x00, 0x00, 0x00, 0x00,                 /* bmaControls(0)
                                               Master control
                                                D1..0: Mute Control
                                                D3..2: Volume Control
                                                D5..4: Bass Control
                                                D7..6: Mid Control
                                                D9..8: Treble Control
                                                D11..10: Graphic Equalizer Control
                                                D13..12: Automatic Gain Control
                                                D15..14: Delay Control
                                                D17..16: Bass Control
                                                D19..18: Loudness Control
                                                D21..20: Input Gain Control
                                                D23..22: Input Gain Pad Control
                                                D25..24: Phase Inverter Control
                                                D27..26: Underflow Control
                                                D29..28: Overflow Control
                                                D31..30: Reserved, should set to 0
                                            */
    0x00, 0x00, 0x00, 0x00,                 /* bmaControls(1)
                                               Left volume control
                                                D1..0: Mute Control
                                                D3..2: Volume Control
                                                D5..4: Bass Control
                                                D7..6: Mid Control
                                                D9..8: Treble Control
                                                D11..10: Graphic Equalizer Control
                                                D13..12: Automatic Gain Control
                                                D15..14: Delay Control
                                                D17..16: Bass Control
                                                D19..18: Loudness Control
                                                D21..20: Input Gain Control
                                                D23..22: Input Gain Pad Control
                                                D25..24: Phase Inverter Control
                                                D27..26: Underflow Control
                                                D29..28: Overflow Control
                                                D31..30: Reserved, should set to 0
                                            */
    0x00, 0x00, 0x00, 0x00,                 /* bmaControls(2)
                                               Right volume control
                                                D1..0: Mute Control
                                                D3..2: Volume Control
                                                D5..4: Bass Control
                                                D7..6: Mid Control
                                                D9..8: Treble Control
                                                D11..10: Graphic Equalizer Control
                                                D13..12: Automatic Gain Control
                                                D15..14: Delay Control
                                                D17..16: Bass Control
                                                D19..18: Loudness Control
                                                D21..20: Input Gain Control
                                                D23..22: Input Gain Pad Control
                                                D25..24: Phase Inverter Control
                                                D27..26: Underflow Control
                                                D29..28: Overflow Control
                                                D31..30: Reserved, should set to 0
                                            */
    0x00,                                   /* iFeature */

    /* Output Terminal Descriptor (Terminal ID 0x03 - Source ID 0x6 - Clock Source ID 0x10) */
    0x0C,               /* bLength */
    0x24,               /* bDescriptorType:CS_INTERFACE */
    0x03,               /* bDescriptorSubType:OUTPUT_TERMINAL */
    0x03,               /* bTerminalID */
    0x02,0x04,          /* wTerminalType: HEADSET */
    0x00,               /* bAssocTerminal */
    PLAY_FEATURE_UNITID,/* bSourceID */
    0x10,               /* bCSourceID */
    0x00, 0x00,         /* bmControls
                             D1..0: Copy Protect Control
                             D3..2: Connector Control
                             D5..4: Overload Control
                             D7..6: Cluster Control
                             D9..8: Underflow Control
                             D11..10: Overflow Control
                             D15..12: Reserved, should set to 0
                        */
    0x00,               /* iTerminal */
    /* Standard AC Interface Descriptor - Interface 1, alternate 0 */
    0x09,               /* bLength */
    0x04,               /* bDescriptorType */
    0x01,               /* bInterfaceNumber */
    0x00,               /* bAlternateSetting */
    0x00,               /* bNumEndpoints */
    0x01,               /* bInterfaceClass:AUDIO */
    0x02,               /* bInterfaceSubClass:AUDIOSTREAMING */
    0x20,               /* bInterfaceProtocol */
    0x00,               /* iInterface */

    /* Standard AC Interface Descriptor - Interface 1, alternate 1 */
    0x09,               /* bLength */
    0x04,               /* bDescriptorType */
    0x01,               /* bInterfaceNumber */
    0x01,               /* bAlternateSetting */
    0x01,               /* bNumEndpoints */
    0x01,               /* bInterfaceClass:AUDIO */
    0x02,               /* bInterfaceSubClass:AUDIOSTREAMING */
    0x20,               /* bInterfaceProtocol */
    0x00,               /* iInterface */

    /* Class-Specific AS Interface Descriptor (this interface's endpoint connect to Terminal ID 0x02 - Microphone) */
    0x10,                                   /* bLength(16) */
    0x24,                                   /* bDescriptorType(0x024): CS_INTERFACE */
    0x01,                                   /* bDescriptorSubType(0x01): AS_GENERAL */
    0x02,                                   /* bTerminalLink(0x02): INPUT_TERMINAL_ID */
    0x00,                                   /* bmControls(0x00) */
    0x01,                                   /* bFormatType(0x01): FORMAT_TYPE_I */
    0x01, 0x00, 0x00, 0x00,                 /* bmFormats(0x00000001): PCM
                                                 Bit 0: IEC61937_AC-3
                                                 Bit 1: IEC61937_MPEG-1_Layer1
                                                 Bit 2: IEC61937_MPEG-1_Layer2/3 or IEC61937__MPEG-2_NOEXT
                                                 Bit 3: IEC61937_MPEG-2_EXT
                                                 Bit 4: IEC61937_MPEG-2_AAC_ADTS
                                                 Bit 5: IEC61937_MPEG-2_Layer1_LS
                                                 Bit 6: IEC61937_MPEG-2_Layer2/3_LS
                                                 Bit 7: IEC61937_DTS-I
                                                 Bit 8: IEC61937_DTS-II
                                                 Bit 9: IEC61937_DTS-III
                                                 Bit 10: IEC61937_ATRAC
                                                 Bit 11: IEC61937_ATRAC2/3
                                                 Bit 12: TYPE_III_WMA
                                            */
    0x02,                                   /* bNrChannels(0x02): NB_CHANNELS */
    0x00, 0x00, 0x00, 0x00,                 /* bmChannelCOnfig(0x00000003)
                                                 Bit 0: Front Left - FL
                                                 Bit 1: Front Right - FR
                                                 Bit 2: Front Center - FC
                                                 Bit 3: Low Frequency Effects - LFE
                                                 Bit 4: Back Left - BL
                                                 Bit 5: Back Right - BR
                                                 Bit 6: Front Left of Center - FLC
                                                 Bit 7: FRONT RIght of Center - FRC
                                                 Bit 8: Back Center - BC
                                                 Bit 9: Side Left - SL
                                                 Bit 10: Side Right - SR
                                                 Bit 11: Top Center - TC
                                                 Bit 12: Top Front Left - TFL
                                                 Bit 13: Top Front Center - TFC
                                                 Bit 14: Top Front Right - TFR
                                                 Bit 15: Top Back Left - TBL
                                                 Bit 16: Top Back Center - TBC
                                                 Bit 17: Top Back Right - TBR
                                                 Bit 18: Top Front Left of Center - TFLC
                                                 Bit 19: Top Front Right of Center - TFRC
                                                 Bit 20: Left Low Frequency Effects - LLFE
                                                 Bit 21: Right Low Frequency Effects - RLFE
                                                 Bit 22: Top Side Left - TSL
                                                 Bit 23: Top Side Right - TSR
                                                 Bit 24: Bottom Center - BC
                                                 Bit 25: Back Left of Center - BLC
                                                 Bit 26: Back Right of Center - BRC
                                                 Bit 31: Raw Data - RD; Mutually exclusive with all other spatial locations
                                            */
    0x00,                                   /* iChannelNames(0x00): None */

    /* Audio Format Type Descriptor */
    0x06,               /* bLength(6) */
    0x24,               /* bDescriptorType(0x24): CS_INTERFACE */
    0x02,               /* bDescriptorSubtype(0x02): FORMAT_TYPE */
    0x01,               /* bFormatType(0x01): FORMAT_TYPE_I */
    0x02,               /* bSubSlotSize(0x02)  :  2 bytes per sample */
    0x10,               /* bBitResolution(0x10): 16  bits per sample */

    /* Standard AS Isochronous Feedback Endpoint Descriptor */
    0x07,                                   /* bLength */
    0x05,                                   /* bDescriptorType */
    ISO_IN_EP_NUM | EP_INPUT,               /* bEndpointAddress */
    0x25,                                   /* bmAttributes */
    (144 + 24)&0xff, ((144 + 24)>>8)&0xff,  /* wMaxPacketSize note */
    0x01,                                   /* bInterval - Must be 1 for compliance */

    /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor */
    0x08,               /* bLength */
    0x25,               /* bDescriptorType:CS_ENDPOINT */
    0x01,               /* bDescriptorSubType:EP_GENERAL */
    0x00,               /* bmAttributes */
    0x00,               /* bmControls */
    0x00,               /* bLockDelayUnits */
    0x00, 0x00,         /* wLockDelay */

    /* Standard AC Interface Descriptor - Interface 1/2, alternate 0
        Interface 2 for Speaker & Microphone
        Interface 1 for Speaker Only
    */
    0x09,               /* bLength */
    0x04,               /* bDescriptorType */
    0x02,               /* bInterfaceNumber */
    0x00,               /* bAlternateSetting */
    0x00,               /* bNumEndpoints */
    0x01,               /* bInterfaceClass:AUDIO */
    0x02,               /* bInterfaceSubClass:AUDIOSTREAMING */
    0x20,               /* bInterfaceProtocol */
    0x00,               /* iInterface */

    /* Standard AC Interface Descriptor - Interface 1/2, alternate 1 */
    0x09,               /* bLength */
    0x04,               /* bDescriptorType */
    0x02,               /* bInterfaceNumber */
    0x01,               /* bAlternateSetting */
    0x02,               /* bNumEndpoints */
    0x01,               /* bInterfaceClass:AUDIO */
    0x02,               /* bInterfaceSubClass:AUDIOSTREAMING */
    0x20,               /* bInterfaceProtocol */
    0x00,               /* iInterface */

    /* Class-Specific AS Interface Descriptor (this interface's endpoint connect to Terminal ID 0x01 - Speaker)*/
    0x10,                                   /* bLength(16) */
    0x24,                                   /* bDescriptorType(0x024): CS_INTERFACE */
    0x01,                                   /* bDescriptorSubType(0x01): AS_GENERAL */
    0x01,                                   /* bTerminalLink(0x01): INPUT_TERMINAL_ID */
    0x00,                                   /* bmControls(0x00) */
    0x01,                                   /* bFormatType(0x01): FORMAT_TYPE_I */
    0x01, 0x00, 0x00, 0x00,                 /* bmFormats(0x00000001): PCM
                                                 Bit 0: IEC61937_AC-3
                                                 Bit 1: IEC61937_MPEG-1_Layer1
                                                 Bit 2: IEC61937_MPEG-1_Layer2/3 or IEC61937__MPEG-2_NOEXT
                                                 Bit 3: IEC61937_MPEG-2_EXT
                                                 Bit 4: IEC61937_MPEG-2_AAC_ADTS
                                                 Bit 5: IEC61937_MPEG-2_Layer1_LS
                                                 Bit 6: IEC61937_MPEG-2_Layer2/3_LS
                                                 Bit 7: IEC61937_DTS-I
                                                 Bit 8: IEC61937_DTS-II
                                                 Bit 9: IEC61937_DTS-III
                                                 Bit 10: IEC61937_ATRAC
                                                 Bit 11: IEC61937_ATRAC2/3
                                                 Bit 12: TYPE_III_WMA
                                            */
    0x02,                                   /* bNrChannels(0x02): NB_CHANNELS */
    0x03, 0x00, 0x00, 0x00,                 /* bmChannelCOnfig(0x00000003)
                                                 Bit 0: Front Left - FL
                                                 Bit 1: Front Right - FR
                                                 Bit 2: Front Center - FC
                                                 Bit 3: Low Frequency Effects - LFE
                                                 Bit 4: Back Left - BL
                                                 Bit 5: Back Right - BR
                                                 Bit 6: Front Left of Center - FLC
                                                 Bit 7: FRONT RIght of Center - FRC
                                                 Bit 8: Back Center - BC
                                                 Bit 9: Side Left - SL
                                                 Bit 10: Side Right - SR
                                                 Bit 11: Top Center - TC
                                                 Bit 12: Top Front Left - TFL
                                                 Bit 13: Top Front Center - TFC
                                                 Bit 14: Top Front Right - TFR
                                                 Bit 15: Top Back Left - TBL
                                                 Bit 16: Top Back Center - TBC
                                                 Bit 17: Top Back Right - TBR
                                                 Bit 18: Top Front Left of Center - TFLC
                                                 Bit 19: Top Front Right of Center - TFRC
                                                 Bit 20: Left Low Frequency Effects - LLFE
                                                 Bit 21: Right Low Frequency Effects - RLFE
                                                 Bit 22: Top Side Left - TSL
                                                 Bit 23: Top Side Right - TSR
                                                 Bit 24: Bottom Center - BC
                                                 Bit 25: Back Left of Center - BLC
                                                 Bit 26: Back Right of Center - BRC
                                                 Bit 31: Raw Data - RD; Mutually exclusive with all other spatial locations
                                            */
    0x00,                                   /* iChannelNames(0x00): None */

    /* Audio Format Type Descriptor */
    0x06,               /* bLength(6) */
    0x24,               /* bDescriptorType(0x24): CS_INTERFACE */
    0x02,               /* bDescriptorSubtype(0x02): FORMAT_TYPE */
    0x01,               /* bFormatType(0x01): FORMAT_TYPE_I */
    0x02,               /* bSubSlotSize(0x02)  :  2 bytes per sample */
    0x10,               /* bBitResolution(0x10): 16  bits per sample */

    /* Standard AS Isochronous Feedback Endpoint Descriptor */
    0x07,                                   /* bLength */
    0x05,                                   /* bDescriptorType */
    ISO_OUT_EP_NUM | EP_OUTPUT,             /* bEndpointAddress */
    0x05,                                   /* bmAttributes */
    (144 + 0)&0xff, ((144 + 0)>>8)&0xff,    /* wMaxPacketSize note */
    0x01,                                   /* bInterval - Must be 1 for compliance */

    /* Class-Specific AS Isochronous Audio Data Endpoint Descriptor */
    0x08,               /* bLength */
    0x25,               /* bDescriptorType:CS_ENDPOINT */
    0x01,               /* bDescriptorSubType:EP_GENERAL */
    0x00,               /* bmAttributes */
    0x00,               /* bmControls */
    0x00,               /* bLockDelayUnits */
    0x00, 0x00,         /* wLockDelay */

    /* AS Isochronous Feedback Endpoint Descriptor */
    0x07,                                   /* bLength */
    0x05,                                   /* bDescriptorType: ENDPOINT */
    ISO_FEEDBACK_ENDPOINT | EP_INPUT,       /* bEndpointAddress */
    0x11,                                   /* bmAttributes (bitmap)  */
    0x04, 0x0,                              /* wMaxPacketSize */
    0x04,                                   /* bInterval - Must be 1 for compliance */

#ifdef __HID__
    /* Interface Descriptor for HID */
    LEN_INTERFACE,      /* bLength */
    DESC_INTERFACE,     /* bDescriptorType */
    0x03,               /* bInterfaceNumber */
    0x00,               /* bAlternateSetting */
    0x01,               /* bNumEndpoints : Interrupt IN Endpoint */
    0x03,               /* bInterfaceClass */
    0x00,               /* bInterfaceSubClass */
    0x00,               /* bInterfaceProtocol */
    0x00,               /* iInterface */

    /* HID Descriptor */
    LEN_HID,            /* Size of this descriptor in UINT8s */
    DESC_HID,           /* HID descriptor type. */
    0x10, 0x01,         /* HID Class Spec. release number.*/
    0x00,               /* H/W target country. */
    0x01,               /* Number of HID class descriptors to follow. */
    DESC_HID_RPT,       /* Dscriptor type. */

    /* Total length of report descriptor */
    sizeof(HID_DeviceReportDescriptor) & 0x00FF,
    ((sizeof(HID_DeviceReportDescriptor) & 0xFF00) >> 8),

    /* Endpoint Descriptor (Interrupt IN Endpoint) */
    LEN_ENDPOINT,                     /* bLength */
    DESC_ENDPOINT,                    /* bDescriptorType */
    (HID_IN_EP_NUM | EP_INPUT),       /* bEndpointAddress */
    EP_INT,                           /* bmAttributes */
    /* wMaxPacketSize */
    EPD_MAX_PKT_SIZE & 0x00FF,
    (EPD_MAX_PKT_SIZE & 0xFF00) >> 8,
    10,                               /* bInterval */
#endif
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
#ifdef __HID__
    72,
    DESC_STRING,
    'U', 0, 'A', 0, 'C', 0, ' ', 0, '2', 0, '.', 0, '0', 0, ' ', 0,
    'H', 0, 'e', 0, 'a', 0, 'd', 0, 's', 0, 'e', 0, 't', 0,
    ' ', 0,
    'E', 0, 'a', 0, 'r', 0, 'p', 0, 'h', 0, 'o', 0, 'n', 0, 'e', 0,
    ' ', 0, '&', 0,
#ifdef __JOYSTICK__
    ' ', 0, 'J', 0, 'o', 0, 'y', 0, 's', 0, 't', 0, 'i', 0, 'c', 0, 'k', 0,
#elif defined __MEDIAKEY__
    ' ', 0, 'M', 0, 'e', 0, 'd', 0, 'i', 0, 'a', 0, 'k', 0, 'e', 0, 'y', 0,
#endif
#else
    50,
    DESC_STRING,
    'U', 0, 'A', 0, 'C', 0, ' ', 0, '2', 0, '.', 0, '0', 0, ' ', 0,
    'H', 0, 'e', 0, 'a', 0, 'd', 0, 's', 0, 'e', 0, 't', 0,
    ' ', 0,
    'E', 0, 'a', 0, 'r', 0, 'p', 0, 'h', 0, 'o', 0, 'n', 0, 'e', 0,
#endif
};

uint8_t *gpu8UsbString[4] =
{
    gu8StringLang,
    gu8VendorStringDesc,
    gu8ProductStringDesc,
    NULL,
};

uint8_t *gu8UsbHidReport[] =
{
    0,
    0,
    0,
#ifdef __HID__
    HID_DeviceReportDescriptor,
#else
    0
#endif
};

uint32_t gu32UsbHidReportLen[4] =
{
    0,
    0,
    0,
#ifdef __HID__
    sizeof(HID_DeviceReportDescriptor),
#else
    0
#endif
};

uint32_t gu32ConfigHidDescIdx[4] =
{
    0,
    0,
    0,
#ifdef __HID__
    263,
#else
    0
#endif
};


S_HSUSBD_INFO_T gsHSInfo =
{
    gu8DeviceDescriptor,
    gu8ConfigDescriptor,
    gpu8UsbString,
    gu8QualifierDescriptor,
    gu8ConfigDescriptor,
    gu8ConfigDescriptor,
    gu8ConfigDescriptor,
    gu8UsbHidReport,
    gu32UsbHidReportLen,
    gu32ConfigHidDescIdx,
};

