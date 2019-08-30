/**************************************************************************//**
 * @file     descriptors.c
 * @version  V1.00
 * @brief    M480 HSUSBD driver source file
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
/*!<Includes */
#include "NuMicro.h"
#include "usbd_audio.h"

/*
  *Microphone - Interface alternate 1
  +-----------+------------+----------------+------------------+
  | Alternate | Channel(s) | Bit Resolution | Sampling Rate(s) |
  +-----------+------------+----------------+------------------+
  |     1     |      1     |     16 bits    |   32kHz, 48kHz   |
  +-----------+------------+----------------+------------------+

  *Speaker - Interface alternate 1
  +-----------+------------+----------------+------------------+
  | Alternate | Channel(s) | Bit Resolution | Sampling Rate(s) |
  +-----------+------------+----------------+------------------+
  |     1     |      2     |     16 bits    |  44.1kHz, 48kHz  |
  +-----------+------------+----------------+------------------+

  Note:
  1.If you want to add / remove sampling rate to certain alternate for Microphone or Speaker interface,
    please modify Audio Streaming Format Type Descriptor (bLength, bSamFreqType, tSamFreq fields)
    and the Total Length field of Configuration Descriptor.
    For example,
      Add 32kHz to Speaker Interface alternate 1 (16 bit resolution) from Speaker & Microphone descriptor with HID

      1.Modify Audio Streaming Format Type Descriptor for Speaker Interface alternate 1

         Audio Streaming Format Type Descriptor
         +--------------------+-------------------------------+-------------------------------+
         | *bLength           |        Original Value         |         Modified Value        |
         +--------------------+-------------------------------+-------------------------------+
         | bLength            |              0x0E             |         0x11(+3 Bytes)        |
         +--------------------+-------------------------------+-------------------------------+
         | bDescriptorType    |              0x24             |              0x24             |
         +--------------------+-------------------------------+-------------------------------+
         | bDescriptorSubType |              0x02             |              0x02             |
         +--------------------+-------------------------------+-------------------------------+
         | bFormatType        |              0x01             |              0x01             |
         +--------------------+-------------------------------+-------------------------------+
         | bNrChannels        |              0x02             |              0x02             |
         +--------------------+-------------------------------+-------------------------------+
         | bSubFrameSize      |              0x02             |              0x02             |
         +--------------------+-------------------------------+-------------------------------+
         | bBitResolution     |              0x10             |              0x10             |
         +--------------------+-------------------------------+-------------------------------+
         | *bSamFreqType      |              0x02             |       0x03(+1 Frequency)      |
         +--------------------+-------------------------------+-------------------------------+
         | *tSamFreq          |  AUDIO_RATE_48K & 0xFF        |  AUDIO_RATE_48K & 0xFF        |
         |                    | (AUDIO_RATE_48K >>  8) & 0xFF | (AUDIO_RATE_48K >>  8) & 0xFF | 
         |                    | (AUDIO_RATE_48K >> 16) & 0xFF | (AUDIO_RATE_48K >> 16) & 0xFF |
         |                    |  AUDIO_RATE_32K & 0xFF        |  AUDIO_RATE_32K & 0xFF        |
         |                    | (AUDIO_RATE_32K >>  8) & 0xFF | (AUDIO_RATE_32K >>  8) & 0xFF | 
         |                    | (AUDIO_RATE_32K >> 16) & 0xFF | (AUDIO_RATE_32K >> 16) & 0xFF |
         |                    |                               |  AUDIO_RATE_16K & 0xFF        |
         |                    |                               | (AUDIO_RATE_16K >>  8) & 0xFF | 
         |                    |                               | (AUDIO_RATE_16K >> 16) & 0xFF |
         +--------------------+-------------------------------+-------------------------------+


      2.Modify the Total Length field of Configuration Descriptor to 0xE0.

         0xDD(Original Total Length) + 0x03(The increase Length of Audio Streaming Format Type Descriptor) = 0xE0

  2.If you want to change the support function of audio control, please modify the bmaControls field of
    Audio Control Feature Unit Descriptor for Microphone or Speaker
      A bit set to 1 indicates that the mentioned Control is supported
         0:
         D0: Mute
         D1: Volume
         D2: Bass
         D3: Mid
         D4: Treble
         D5: Graphic Equalizer
         D6: Automatic Gain
         D7: Delay
         D8: Bass Boost
         D9: Loudness
         D10..(n*8-1): Reserved
  3.If you want to change the polling interal of HID Endpoint, please modify the bInterval field of Endpoint Descriptor for HID.
*/

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
    0x10, 0x01,     /* bcdUSB */
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
    0x00, 0x01,     /* bcdDevice */
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
    LEN_CONFIG,         /* bLength */
    DESC_CONFIG,        /* bDescriptorType */
#ifdef __HID__
#ifdef __FEEDBACK__
    0xF8, 0x00,         /* wTotalLength */

#else
    0xEF, 0x00,         /* wTotalLength */
#endif
                        /*
                           Descriptor (Feedback) without HID           (0xDF)
                           Descriptor without HID                      (0xD6)

                           HID Descriptor
                             Interface Descriptor                      (0x09)
                             HID Descriptor                            (0x09)
                             Endpoint Descriptor (IN)                  (0x07)

                           0xDF + (0x09 + 0x09 + 0x07) = 0xF8 (with Feedback Endpoint)
                           0xD6 + (0x09 + 0x09 + 0x07) = 0xEF
                        */
    0x04,               /* bNumInterfaces - Interface 0, Interface 1 (Microphone), Interface 2 (Speaker), Interface 3 (HID) */
#else
#ifdef __FEEDBACK__
    0xDF, 0x00,         /* wTotalLength */
#else
    0xD6, 0x00,         /* wTotalLength */
#endif
    /*
       Configuration Descriptor                    (0x09)
       Interface Descriptor (Audio Class)          (0x09)
       Audio Control Interface Header Descriptor   (0x0A)
       Microphone - Audio Control
         Audio Control Input Terminal Descriptor   (0x0C)
         Audio Control Feature Unit Descriptor     (0x08)
         Audio Control Output Terminal Descriptor  (0x09)
       Speaker - Audio Control
         Audio Control Input Terminal Descriptor   (0x0C)
         Audio Control Feature Unit Descriptor     (0x0A)
         Audio Control Output Terminal Descriptor  (0x09)
       Microphone - Interface alternate 0
         Standard AS interface                     (0x09)
       Microphone - Interface alternate 1
         Standard AS interface                                         (0x09)
         Audio Streaming Class Specific Interface Descriptor           (0x07)
         Audio Streaming Format Type Descriptor                        (0x17)*
         Endpoint Descriptor                                           (0x07)
         Audio Streaming Class Specific Audio Data Endpoint Descriptor (0x07)
         *Each Interface alternate Summary                             (0x35)*
       Speaker - Interface alternate 0
         Standard AS interface                     (0x09)
       Speaker - Interface alternate 1
         Standard AS interface                                         (0x09)
         Audio Streaming Class Specific Interface Descriptor           (0x07)
         Audio Streaming Format Type Descriptor                        (0x17)*
         Endpoint Descriptor                                           (0x09)
         Audio Streaming Class Specific Audio Data Endpoint Descriptor (0x07)
         Feedback Endpoint Descriptor                                  (0x09)
         *Each Interface alternate Summary with Feedback Endpoint      (0x40)*
         *Each Interface alternate Summary                             (0x37)*

       0x09 + 0x09 + 0x0A + (0x0C + 0x08 + 0x09) + (0x0C + 0x0A + 0x09) +
       0x09 + 0x35 + 0x09 + 0x40 = 0xDF (with Feedback Endpoint)

       0x09 + 0x09 + 0x0A + (0x0C + 0x08 + 0x09) + (0x0C + 0x0A + 0x09) +
       0x09 + 0x35 + 0x09 + 0x37 = 0xD6
    */
    0x03,               /* bNumInterfaces - Interface 0, Interface 1 (Microphone), Interface 2 (Speaker) */
#endif
    0x01,               /* bConfigurationValue */
    0x00,               /* iConfiguration */
    0x80,               /* bmAttributes */
    0x20,               /* Max power */

    /* Interface Descriptor (Audio Class) */
    0x09,               /* bLength */
    0x04,               /* bDescriptorType */
    0x00,               /* bInterfaceNumber */
    0x00,               /* bAlternateSetting */
    0x00,               /* bNumEndpoints */
    0x01,               /* bInterfaceClass:AUDIO */
    0x01,               /* bInterfaceSubClass:AUDIOCONTROL */
    0x00,               /* bInterfaceProtocol */
    0x00,               /* iInterface */

    /* Audio Control Interface Header Descriptor */
    0x0A,               /* bLength */
    0x24,               /* bDescriptorType:CS_INTERFACE */
    0x01,               /* bDescriptorSubType:HEADER */
    0x00, 0x01,         /* bcdADC:1.0 */
    0x46, 0x00,         /* wTotalLength
                           Audio Control Interface Header Descriptor  (0x0A)
                           Microphone - Audio Control
                             Audio Control Input Terminal Descriptor  (0x0C)
                             Audio Control Feature Unit Descriptor    (0x08)
                             Audio Control Output Terminal Descriptor (0x09)
                           Speaker - Audio Control
                             Audio Control Input Terminal Descriptor  (0x0C)
                             Audio Control Feature Unit Descriptor    (0x0A)
                             Audio Control Output Terminal Descriptor (0x09)

                             0x0A + (0x0C + 0x08 + 0x09) + (0x0C + 0x0A + 0x09) = 0x46
                        */
    0x02,               /* bInCollection */
    0x01,               /* baInterfaceNr(1) - Microphone */
    0x02,               /* baInterfaceNr(2) - Speaker */



    /* Audio Control Input Terminal Descriptor - Microphone (Terminal ID 4) */
    0x0C,               /* bLength */
    0x24,               /* bDescriptorType:CS_INTERFACE */
    0x02,               /* bDescriptorSubType:INPUT_TERMINAL*/
    0x04,               /* bTerminalID*/
    0x02,0x04,          /* wTerminalType: Headset */
    0x00,               /* bAssocTerminal*/
    REC_CHANNELS,       /* bNrChannels : a number that specifies how many logical audio channels are present in the cluster */
    REC_CH_CFG, 0x00,   /* wChannelConfig: a bit field that indicates which spatial locations are present in the cluster.
                           The bit allocations are as follows:
                             D0: Left Front (L)
                             D1: Right Front (R)
                             D2: Center Front (C)
                             D3: Low Frequency Enhancement (LFE)
                             D4: Left Surround (LS)
                             D5: Right Surround (RS)
                             D6: Left of Center (LC)
                             D7: Right of Center (RC)
                             D8: Surround (S)
                             D9: Side Left (SL)
                             D10: Side Right (SR)
                             D11: Top (T)
                             D15..12: Reserved
                        */
    0x00,               /* iChannelNames*/
    0x00,               /* iTerminal*/

    /* Audio Control Feature Unit Descriptor - Microphone (UNIT ID 5 - Source 4) */
    0x08,               /* bLength */
    0x24,               /* bDescriptorType */
    0x06,               /* bDescriptorSubType */
    REC_FEATURE_UNITID, /* bUnitID */
    0x04,               /* bSourceID */
    0x01,               /* bControlSize - Size, in bytes, of the bmControls field: n */
    0x03,               /* bmaControls(0) */
    /* A bit set to 1 indicates that the mentioned
       Control is supported for master channel
       0:
       D0: Mute
       D1: Volume
       D2: Bass
       D3: Mid
       D4: Treble
       D5: Graphic Equalizer
       D6: Automatic Gain
       D7: Delay
       D8: Bass Boost
       D9: Loudness
       D10..(n*8-1): Reserved
    */
    0x00,               /* iFeature */

    /* Audio Control Output Terminal Descriptor - Microphone (Terminal ID 2 - Source ID 5) */
    0x09,               /* bLength */
    0x24,               /* bDescriptorType:CS_INTERFACE */
    0x03,               /* bDescriptorSubType:OUTPUT_TERMINAL */
    0x02,               /* bTerminalID */
    0x01,0x01,          /* wTerminalType: 0x0101 usb streaming */
    0x00,               /* bAssocTerminal */
    REC_FEATURE_UNITID, /* bSourceID */
    0x00,               /* iTerminal */


    /* Audio Control Input Terminal Descriptor - Speaker (Terminal ID 1) */
    0x0C,               /* bLength */
    0x24,               /* bDescriptorType:CS_INTERFACE */
    0x02,               /* bDescriptorSubType:INPUT_TERMINAL */
    0x01,               /* bTerminalID */
    0x01, 0x01,         /* wTerminalType: USB streaming */
    0x00,               /* bAssocTerminal */
    PLAY_CHANNELS,      /* bNrChannels : a number that specifies how many logical audio channels are present in the cluster */
    PLAY_CH_CFG, 0x00,  /* wChannelConfig: a bit field that indicates which spatial locations are present in the cluster.
                           The bit allocations are as follows:
                             D0: Left Front (L)
                             D1: Right Front (R)
                             D2: Center Front (C)
                             D3: Low Frequency Enhancement (LFE)
                             D4: Left Surround (LS)
                             D5: Right Surround (RS)
                             D6: Left of Center (LC)
                             D7: Right of Center (RC)
                             D8: Surround (S)
                             D9: Side Left (SL)
                             D10: Side Right (SR)
                             D11: Top (T)
                             D15..12: Reserved
                        */
    0x00,               /* iChannelNames */
    0x00,               /* iTerminal */

    /* Audio Control Feature Unit Descriptor - Speaker (UNIT ID 6 - Source ID 1) */
    0x0A,               /* bLength */
    0x24,               /* bDescriptorType */
    0x06,               /* bDescriptorSubType */
    PLAY_FEATURE_UNITID,/* bUnitID */
    0x01,               /* bSourceID */
    0x01,               /* bControlSize - Size, in bytes, of the bmControls field: n */
    0x01,               /* bmaControls(0) */
    /* A bit set to 1 indicates that the mentioned
       Control is supported for master channel
       0:
       D0: Mute
       D1: Volume
       D2: Bass
       D3: Mid
       D4: Treble
       D5: Graphic Equalizer
       D6: Automatic Gain
       D7: Delay
       D8: Bass Boost
       D9: Loudness
       D10..(n*8-1): Reserved
    */
    0x02,               /* bmaControls(1) - Left */
    /* A bit set to 1 indicates that the mentioned
       Control is supported for master channel
       0:
       D0: Mute
       D1: Volume
       D2: Bass
       D3: Mid
       D4: Treble
       D5: Graphic Equalizer
       D6: Automatic Gain
       D7: Delay
       D8: Bass Boost
       D9: Loudness
       D10..(n*8-1): Reserved
    */
    0x02,               /* bmaControls(2) - Right */
    /* A bit set to 1 indicates that the mentioned
       Control is supported for master channel
       0:
       D0: Mute
       D1: Volume
       D2: Bass
       D3: Mid
       D4: Treble
       D5: Graphic Equalizer
       D6: Automatic Gain
       D7: Delay
       D8: Bass Boost
       D9: Loudness
       D10..(n*8-1): Reserved
    */
    0x00,               /* iFeature */

    /* Audio Control Output Terminal Descriptor - Speaker (UNIT ID 3 - Source ID 5) */
    0x09,               /* bLength*/
    0x24,               /* bDescriptorType:CS_INTERFACE*/
    0x03,               /* bDescriptorSubType:OUTPUT_TERMINAL*/
    0x03,               /* bTerminalID*/
    0x02,0x04,          /* wTerminalType: Headset */
    0x00,               /* bAssocTerminal*/
    PLAY_FEATURE_UNITID,/* bSourceID*/
    0x00,               /* iTerminal*/

    /* Interface Descriptor - Interface 1, alternate 0 */
    0x09,               /* bLength */
    0x04,               /* bDescriptorType */
    0x01,               /* bInterfaceNumber */
    0x00,               /* bAlternateSetting */
    0x00,               /* bNumEndpoints */
    0x01,               /* bInterfaceClass:AUDIO */
    0x02,               /* bInterfaceSubClass:AUDIOSTREAMING */
    0x00,               /* bInterfaceProtocol */
    0x00,               /* iInterface */

    /* Interface Descriptor - Interface 1, alternate 1 */
    0x09,               /* bLength */
    0x04,               /* bDescriptorType */
    0x01,               /* bInterfaceNumber */
    0x01,               /* bAlternateSetting */
    0x01,               /* bNumEndpoints */
    0x01,               /* bInterfaceClass:AUDIO */
    0x02,               /* bInterfaceSubClass:AUDIOSTREAMING */
    0x00,               /* bInterfaceProtocol */
    0x00,               /* iInterface */

    /* Audio Streaming Class Specific Interface Descriptor (this interface's endpoint connect to Terminal ID 0x02) */
    0x07,               /* bLength */
    0x24,               /* bDescriptorType:CS_INTERFACE */
    0x01,               /* bDescriptorSubType:AS_GENERAL */
    0x02,               /* bTernimalLink (Microphone) */
    0x01,               /* bDelay */
    0x01, 0x00,         /* wFormatTag:0x0001 PCM */

    /* Audio Streaming Format Type Descriptor */
    0x17,               /* bLength */
    0x24,               /* bDescriptorType:CS_INTERFACE */
    0x02,               /* bDescriptorSubType:FORMAT_TYPE */
    0x01,               /* bFormatType:FORMAT_TYPE_I */
    /* Standard AS interface 1, alternate 1 */
    REC_CHANNELS,       /* bNrChannels    :  2 Channels */
    0x02,               /* bSubFrameSize  :  2 bytes per sample */
    0x10,               /* bBitResolution : 16 bits  per sample */
    0x05,               /* bSamFreqType :
                           0 Continuous sampling frequency
                           1 The number of discrete sampling frequencies */
    /* bSamFreqType  */
    (AUDIO_RATE_16K & 0xFF),
    ((AUDIO_RATE_16K >> 8) & 0xFF),
    ((AUDIO_RATE_16K >> 16) & 0xFF),

    (AUDIO_RATE_24K & 0xFF),
    ((AUDIO_RATE_24K >> 8) & 0xFF),
    ((AUDIO_RATE_24K >> 16) & 0xFF),

    (AUDIO_RATE_32K & 0xFF),
    ((AUDIO_RATE_32K >> 8) & 0xFF),
    ((AUDIO_RATE_32K >> 16) & 0xFF),

    (AUDIO_RATE_48K & 0xFF),
    ((AUDIO_RATE_48K >> 8) & 0xFF),
    ((AUDIO_RATE_48K >> 16) & 0xFF),

    (AUDIO_RATE_96K & 0xFF),
    ((AUDIO_RATE_96K >> 8) & 0xFF),
    ((AUDIO_RATE_96K >> 16) & 0xFF),

    /* Endpoint Descriptor (ISO IN Audio Data Endpoint - alternate 1) */
    0x07,                             /* bLength */
    0x05,                             /* bDescriptorType */
    ISO_IN_EP_NUM | EP_INPUT,         /* bEndpointAddress */
    0x05,                             /* bmAttributes */
    (EPA_MAX_PKT_SIZE & 0xFF), 
    ((EPA_MAX_PKT_SIZE >> 8) & 0xFF),  /* wMaxPacketSize*/
    0x01,                             /* bInterval*/

    /* Audio Streaming Class Specific Audio Data Endpoint Descriptor */
    0x07,               /* bLength */
    0x25,               /* bDescriptorType:CS_ENDPOINT */
    0x01,               /* bDescriptorSubType:EP_GENERAL */
    0x00,               /* bmAttributes */
    0x00,               /* bLockDelayUnits */
    0x00, 0x00,         /* wLockDelay */

    /* Interface Descriptor - Interface 2, alternate 0 */
    0x09,               /* bLength */
    0x04,               /* bDescriptorType */
    0x02,               /* bInterfaceNumber */
    0x00,               /* bAlternateSetting */
    0x00,               /* bNumEndpoints */
    0x01,               /* bInterfaceClass:AUDIO */
    0x02,               /* bInterfaceSubClass:AUDIOSTREAMING */
    0x00,               /* bInterfaceProtocol */
    0x00,               /* iInterface */

    /* Interface Descriptor - Interface 2, alternate 1 */
    0x09,               /* bLength */
    0x04,               /* bDescriptorType */
    0x02,               /* bInterfaceNumber */
    0x01,               /* bAlternateSetting */
#ifdef __FEEDBACK__
    0x02,               /* bNumEndpoints : ISO OUT Endpoint for play & ISO IN Endpoint for Feedback */
#else
    0x01,               /* bNumEndpoints : ISO OUT Endpoint for play */
#endif
    0x01,               /* bInterfaceClass:AUDIO */
    0x02,               /* bInterfaceSubClass:AUDIOSTREAMING */
    0x00,               /* bInterfaceProtocol */
    0x00,               /* iInterface */

    /* Audio Streaming Class Specific Interface Descriptor (this interface's endpoint connect to Terminal ID 0x01 - Speaker) */
    0x07,               /* bLength */
    0x24,               /* bDescriptorType:CS_INTERFACE */
    0x01,               /* bDescriptorSubType:AS_GENERAL */
    0x01,               /* bTernimalLink (Speaker) */
    0x01,               /* bDelay */
    0x01,0x00,          /* wFormatTag:0x0001 PCM */

    /* Audio Streaming Format Type Descriptor */
    0x17,               /* bLength */
    0x24,               /* bDescriptorType:CS_INTERFACE */
    0x02,               /* bDescriptorSubType:FORMAT_TYPE */
    0x01,               /* bFormatType:FORMAT_TYPE_I */
    /* Standard AS interface 1/2, alternate 1 */
    PLAY_CHANNELS,      /* bNrChannels    :  2 Channels */
    0x02,               /* bSubFrameSize  :  2 bytes per sample */
    0x10,               /* bBitResolution : 16 bits  per sample */
    0x05,               /* bSamFreqType :
                           0 Continuous sampling frequency
                           1 The number of discrete sampling frequencies */
    /* bSamFreqType  */
    (AUDIO_RATE_16K & 0xFF),
    ((AUDIO_RATE_16K >> 8) & 0xFF),
    ((AUDIO_RATE_16K >> 16) & 0xFF),

    (AUDIO_RATE_24K & 0xFF),
    ((AUDIO_RATE_24K >> 8) & 0xFF),
    ((AUDIO_RATE_24K >> 16) & 0xFF),

    (AUDIO_RATE_32K & 0xFF),
    ((AUDIO_RATE_32K >> 8) & 0xFF),
    ((AUDIO_RATE_32K >> 16) & 0xFF),

    (AUDIO_RATE_48K & 0xFF),
    ((AUDIO_RATE_48K >> 8) & 0xFF),
    ((AUDIO_RATE_48K >> 16) & 0xFF),

    (AUDIO_RATE_96K & 0xFF),
    ((AUDIO_RATE_96K >> 8) & 0xFF),
    ((AUDIO_RATE_96K >> 16) & 0xFF),

    /* Endpoint Descriptor (ISO OUT Audio Data Endpoint - alternate 1) */
    0x09,                             /* bLength */
    0x05,                             /* bDescriptorType */
    ISO_OUT_EP_NUM | EP_OUTPUT,       /* bEndpointAddress */
#ifdef __FEEDBACK__
    0x05,                             /* bmAttributes */
#else
    0x09,                             /* bmAttributes */
#endif
    (EPB_MAX_PKT_SIZE & 0xff),
    ((EPB_MAX_PKT_SIZE >> 8) & 0xff), /* wMaxPacketSize */
    0x01,                             /* bInterval */
    0x00,                             /* bRefresh */
#ifdef __FEEDBACK__
    ISO_IN_FB_EP_NUM | EP_INPUT,      /* bSynchAddress */
#else
    0x00,                             /* bSynchAddress */
#endif

    /* Audio Streaming Class Specific Audio Data Endpoint Descriptor */
    0x07,                             /* bLength */
    0x25,                             /* bDescriptorType:CS_ENDPOINT */
    0x01,                             /* bDescriptorSubType:EP_GENERAL */
    0x01,                             /* bmAttributes */
    0x02,                             /* bLockDelayUnits */
    0x00, 0x00,                       /* wLockDelay */

#ifdef __FEEDBACK__
    /* Feedback Endpoint */
    0x09,                             /* bLength */
    0x05,                             /* bDescriptorType */
    ISO_IN_FB_EP_NUM | EP_INPUT,      /* bEndpointAddress */
    0x11,                             /* bmAttributes */
    EPC_MAX_PKT_SIZE, 0x00,           /* wMaxPacketSize */
    0x01,                             /* bInterval */
    0x09,                             /* bRefresh */
    0x00,                             /* bSynchAddress */
#endif
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
    'U', 0, 'A', 0, 'C', 0, ' ', 0, '1', 0, '.', 0, '0', 0, ' ', 0,
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
    'U', 0, 'A', 0, 'C', 0, ' ', 0, '1', 0, '.', 0, '0', 0, ' ', 0,
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
#ifdef __FEEDBACK__
    232,
#else
    223,
#endif
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

