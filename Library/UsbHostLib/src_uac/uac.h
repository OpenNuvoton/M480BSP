/**************************************************************************//**
 * @file     uac.h
 * @version  V1.00
 * @brief    M480 MCU USB Host Audio Class header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __INCLUDED_UAC_H__
#define __INCLUDED_UAC_H__


/// @cond HIDDEN_SYMBOLS

//#define UAC_DEBUG

/*
 * Debug message
 */
#define UAC_ERRMSG     printf
#ifdef UAC_DEBUG
#define UAC_DBGMSG      printf
#else
#define UAC_DBGMSG(...)
#endif

typedef enum
{
    UAC_STATE_CONNECTING,
    UAC_STATE_READY,
    UAC_STATE_RUNNING,
    UAC_STATE_DISCONNECTING,
}  UAC_STATE_E;


/* Audio Interface Subclass Codes (A.2)               */
#define SUBCLS_UNDEFINED              0x00
#define SUBCLS_AUDIOCONTROL           0x01
#define SUBCLS_AUDIOSTREAMING         0x02
#define SUBCLS_MIDISTREAMING          0x03

/* Audio Interface Protocol Code (A.3)                */
#define PR_PROTOCOL_UNDEFINED         0x00

/* Audio Class-specific descritpor types (A.4)        */
#define CS_UNDEFINED                  0x20
#define CS_DEVICE                     0x21
#define CS_CONFIGURATION              0x22
#define CS_STRING                     0x23
#define CS_INTERFACE                  0x24
#define CS_ENDPOINT                   0x25

/* Audio Class-Specific AC Interface Descriptor Subtypes (A.5) */
#define AC_DESCRIPTOR_UNDEFINED       0x00
#define HEADER                        0x01
#define INPUT_TERMINAL                0x02
#define OUTPUT_TERMINAL               0x03
#define MIXER_UNIT                    0x04
#define SELECTOR_UNIT                 0x05
#define FEATURE_UNIT                  0x06
#define PROCESSING_UNIT               0x07
#define EXTENSION_UNIT                0x08

/* Audio Class-Specific AS Interface Descriptor Subtypes (A.6) */
#define AS_DESCRIPTOR_UNDEFINED       0x00
#define AS_GENERAL                    0x01
#define FORMAT_TYPE                   0x02
#define FORMAT_SPECIFIC               0x03

/* Processing Unit Process Types (A.7)                */
#define PROCESS_UNDEFINED             0x00
#define UP_DOWNMIX_PROCESS            0x01
#define DOLBY_PROLOGIC_PROCESS        0x02
#define _3D_STEREO_EXTENDER_PROCESS   0x03
#define REVERBERATION_PROCESS         0x04
#define CHORUS_PROCESS                0x05
#define DYN_RANGE_COMP_PROCESS        0x06

/* Audio Class-Specific Endpoint Descriptor Subtypes (A.8) */
#define DESCRIPTOR_UNDEFINED          0x00
#define EP_GENERAL                    0x01

/* Audio Class-Specific Request Codes (A.9)           */
#define REQUEST_CODE_UNDEFINED        0x00
#define SET_CUR                       0x01
#define GET_CUR                       0x81
#define SET_MIN                       0x02
#define GET_MIN                       0x82
#define SET_MAX                       0x03
#define GET_MAX                       0x83
#define SET_RES                       0x04
#define GET_RES                       0x84
#define SET_MEM                       0x05
#define GET_MEM                       0x85
#define GET_STAT                      0xFF

/* Terminal Control Selectors (A.10.1)                */
#define TE_CONTROL_UNDEFINED          0x00
#define COPY_PROTECT_CONTROL          0x01

/* Feature Unit Control Selectors (A.10.2)            */
#define FU_CONTROL_UNDEFINED          0x00
#define MUTE_CONTROL                  0x01
#define VOLUME_CONTROL                0x02
#define BASS_CONTROL                  0x03
#define MID_CONTROL                   0x04
#define TREBLE_CONTROL                0x05
#define GRAPHIC_EQUALIZER_CONTROL     0x06
#define AUTOMATIC_GAIN_CONTROL        0x07
#define DELAY_CONTROL                 0x08
#define BASS_BOOST_CONTROL            0x09
#define LOUDNESS_CONTROL              0x0A

/* Up/Down-mix Processing Unit Control Selectors (A.10.3.1) */
#define UD_CONTROL_UNDEFINED          0x00
#define UD_ENABLE_CONTROL             0x01
#define UD_MODE_SELECT_CONTROL        0x02

/* Dolby Prologic Processing Unit Control Selectors (A.10.3.2) */
#define DP_CONTROL_UNDEFINED          0x00
#define DP_ENABLE_CONTROL             0x01
#define DP_MODE_SELECT_CONTROL        0x02

/* 3D Stereo Extender Processing Unit Control Selectors (A.10.3.3) */
#define _3D_CONTROL_UNDEFINED         0x00
#define _3D_ENABLE_CONTROL            0x01
#define SPACIOUSNESS_CONTROL          0x03

/* Reverberation Processing Unit Control Selectors (A.10.3.4) */
#define RV_CONTROL_UNDEFINED          0x00
#define RV_ENABLE_CONTROL             0x01
#define REVERB_LEVEL_CONTROL          0x02
#define REVERB_TIME_CONTROL           0x03
#define REVERB_FEEDBACK_CONTROL       0x04

/* Chorus Processing Unit Control Selectors (A.10.3.5) */
#define CH_CONTROL_UNDEFINED          0x00
#define CH_ENABLE_CONTROL             0x01
#define CHORUS_LEVEL_CONTROL          0x02
#define CHORUS_RATE_CONTROL           0x03
#define CHORUS_DEPTH_CONTROL          0x04

/* Dynamic Range Compressor Processing Unit Control Selectors (A.10.3.6) */
#define DR_CONTROL_UNDEFINED          0x00
#define DR_ENABLE_CONTROL             0x01
#define COMPRESSION_RATE_CONTROL      0x02
#define MAXAMPL_CONTROL               0x03
#define THRESHOLD_CONTROL             0x04
#define ATTACK_TIME                   0x05
#define RELEASE_TIME                  0x06

/* Extension Unit Control Selectors (A.10.4)  */
#define XU_CONTROL_UNDEFINED          0x00
#define XU_ENABLE_CONTROL             0x01

/* Endpoint Control Selectors  (A.10.5) */
#define EP_CONTROL_UNDEFINED          0x00
#define SAMPLING_FREQ_CONTROL         0x01
#define PITCH_CONTROL                 0x02

/* Format Type Codes of Format Type Descriptor bFormatType field */
#define FORMAT_TYPE_UNDEFINED         0x00
#define FORMAT_TYPE_I                 0x01
#define FORMAT_TYPE_II                0x02
#define FORMAT_TYPE_III               0x03


/*-----------------------------------------------------------------------------------
 *  Audio Class Control Interface Descriptor header
 */
#ifdef __ICCARM__
typedef struct cs_hdr_t                     /*! Audio Class-Specific AC Interface Header Descriptor   */
{
    __packed uint8_t  bLength;              /*!< Size of this descriptor in bytes                     */
    __packed uint8_t  bDescriptorType;      /*!< CS_INTERFACE descriptor type 0x24                    */
    __packed uint8_t  bDescriptorSubtype;   /*!< HEADER descriptor subtype                            */
} CS_HDR_T;                                 /*! Audio Class-Specific AC Interface Header Descriptor   */
#else
typedef struct __attribute__((__packed__)) cs_hdr_t       /*! Audio Class-Specific AC Interface Header Descriptor   */
{
    uint8_t  bLength;                       /*!< Size of this descriptor in bytes                     */
    uint8_t  bDescriptorType;               /*!< CS_INTERFACE descriptor type 0x24                    */
    uint8_t  bDescriptorSubtype;            /*!< HEADER descriptor subtype                            */
} CS_HDR_T;                                 /*! Audio Class-Specific AC Interface Header Descriptor   */
#endif

/*-----------------------------------------------------------------------------------
 *  Class-Specific AC Interface Header Descriptor (4.3.2)
 */
#ifdef __ICCARM__
typedef struct ac_if_header                 /*! Audio Class-Specific AC Interface Header Descriptor   */
{
    __packed uint8_t  bLength;              /*!< Size of this descriptor, in bytes: 8+n               */
    __packed uint8_t  bDescriptorType;      /*!< CS_INTERFACE descriptor type; 0x24                   */
    __packed uint8_t  bDescriptorSubtype;   /*!< HEADER descriptor subtype; 0x1                       */
    __packed uint16_t bcdADC;               /*!< Audio Device Class Specification Release Number in Binary-Coded Decimal \hideinitializer  */
    __packed uint16_t wTotalLength;         /*!< Total number of bytes returned for the class-specific AudioControl interface
                                                 descriptor. Includes the combined length of this descriptor header and all Unit and
                                                 Terminal descriptors.                                */
    __packed uint8_t  bInCollection;        /*!< The number of AudioStreaming and MIDIStreaming interfaces in the Audio
                                                Interface Collection to which this AudioControl interface belongs.  */
} AC_IF_HDR_T;                              /*! Audio Class-Specific AC Interface Header Descriptor   */
#else
typedef struct __attribute__((__packed__)) ac_if_header    /*! Audio Class-Specific AC Interface Header Descriptor   */
{
    uint8_t  bLength;                       /*!< Size of this descriptor, in bytes: 8+n               */
    uint8_t  bDescriptorType;               /*!< CS_INTERFACE descriptor type; 0x24                   */
    uint8_t  bDescriptorSubtype;            /*!< HEADER descriptor subtype; 0x1                       */
    uint16_t bcdADC;                        /*!< Audio Device Class Specification Release Number in Binary-Coded Decimal \hideinitializer  */
    uint16_t wTotalLength;                  /*!< Total number of bytes returned for the class-specific AudioControl interface
                                                 descriptor. Includes the combined length of this descriptor header and all Unit and
                                                 Terminal descriptors.                                */
    uint8_t  bInCollection;                 /*!< The number of AudioStreaming and MIDIStreaming interfaces in the Audio
                                                 Interface Collection to which this AudioControl interface belongs.  */
} AC_IF_HDR_T;                              /*! Audio Class-Specific AC Interface Header Descriptor   */
#endif

/*-----------------------------------------------------------------------------------
 *  UAC Input Terminal Descriptor
 */
#ifdef __ICCARM__
typedef struct ac_itd_t                     /*! Audio Class-Specific Input Terminal Descriptor        */
{
    __packed uint8_t  bLength;              /*!< Size of this descriptor, in bytes: 12                */
    __packed uint8_t  bDescriptorType;      /*!< CS_INTERFACE descriptor type; 0x24                   */
    __packed uint8_t  bDescriptorSubtype;   /*!< INPUT_TERMINAL descriptor subtype; 0x2               */
    __packed uint8_t  bTerminalID;
    __packed uint16_t wTerminalType;
    __packed uint8_t  bAssocTerminal;
    __packed uint8_t  bNrChannels;
    __packed uint16_t wChannelConfig;
    __packed uint8_t  iChannelNames;
    __packed uint8_t  iTerminal;
} AC_IT_T;                                  /*! Audio Class-Specific Input Terminal Descriptor        */
#else
typedef struct __attribute__((__packed__)) ac_itd_t     /*! Audio Class-Specific Input Terminal Descriptor        */
{
    uint8_t  bLength;                       /*!< Size of this descriptor, in bytes: 12                */
    uint8_t  bDescriptorType;               /*!< CS_INTERFACE descriptor type; 0x24                   */
    uint8_t  bDescriptorSubtype;            /*!< INPUT_TERMINAL descriptor subtype; 0x2               */
    uint8_t  bTerminalID;
    uint16_t wTerminalType;
    uint8_t  bAssocTerminal;
    uint8_t  bNrChannels;
    uint16_t wChannelConfig;
    uint8_t  iChannelNames;
    uint8_t  iTerminal;
} AC_IT_T;                                  /*! Audio Class-Specific Input Terminal Descriptor        */
#endif

/*-----------------------------------------------------------------------------------
 *  UAC Output Terminal Descriptor
 */
#ifdef __ICCARM__
typedef struct ac_otd_t
{
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bTerminalID;
    __packed uint16_t wTerminalType;
    __packed uint8_t  bAssocTerminal;
    __packed uint8_t  bSourceID;
    __packed uint8_t  iTerminal;
} AC_OT_T;
#else
typedef struct __attribute__((__packed__)) ac_otd_t
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubtype;
    uint8_t  bTerminalID;
    uint16_t wTerminalType;
    uint8_t  bAssocTerminal;
    uint8_t  bSourceID;
    uint8_t  iTerminal;
} AC_OT_T;
#endif

/*---------------------------------*/
/*  Terminal Types                 */
/*---------------------------------*/
/* USB Terminal Types     */
#define UAC_TT_USB_UNDEFINED        0x0100  /* USB Terminal, undefined Type.              */
#define UAC_TT_USB_STREAMING        0x0101  /* A Terminal dealing with a signal carried 
                                               over an endpoint in an AudioStreaming 
                                               interface. The AudioStreaming interface.   */
#define UAC_TT_USB_VENDOR           0x01FF  /* A Terminal dealing with a signal carried 
                                               over a vendor-specific interface.          */
/* Input Terminal Types   */
#define UAC_TT_INPUT_UNDEFINED      0x0200  /* Input Terminal, undefined Type.            */
#define UAC_TT_MICROPHONE           0x0201  /* A generic microphone that does not fit 
                                               under any of the other classifications.    */
#define UAC_TT_DESKTOP_MICROPHONE   0x0202  /* A microphone normally placed on the desktop 
                                               or integrated into the monitor.            */
#define UAC_TT_PERSONAL_MICROPHONE  0x0203  /* A head-mounted or clip-on microphone.      */
#define UAC_TT_OMNI_MICROPHONE      0x0204  /* A microphone designed to pick up voice from 
                                               more than one speaker at relatively long 
                                               ranges.                                    */
#define UAC_TT_MICROPHONE_ARRAY     0x0205  /* An array of microphones designed for 
                                               directional processing using host-based 
                                               signal processing algorithms.              */
/* Output Terminal Types  */
#define UAC_TT_OUTPUT_UNDEFINED     0x0300  /* Output Terminal, undefined Type.           */
#define UAC_TT_SPEAKER              0x0301  /* A generic speaker or set of speakers that 
                                               doe not fit under any of the other 
                                               classifications.                           */
#define UAC_TT_HEADPHONES           0x0302  /* A head-mounted audio output device.        */
#define UAC_TT_HEAD_MOUNTED         0x0303  /* The audio part of a VR head mounted display. 
                                               The Associated Interfaces descriptor can 
                                               be used to reference the HID interface used 
                                               to report the position and orientation of 
                                               the HMD.                                   */
#define UAC_TT_DESKTOP_SPEAKER      0x0304  /* Relatively small speaker or set of speakers 
                                               normally placed on the desktop or 
                                               integrated into the monitor. These speakers 
                                               are close to the user and have limited 
                                               stereo separation.                         */
#define UAC_TT_ROOM_SPEAKER         0x0305  /* Larger speaker or set of speakers that are 
                                               heard well anywhere in the room.           */
#define UAC_TT_COMM_SPEAKER         0x0306  /* Speaker or set of speakers designed for 
                                               voice communication.                       */
#define UAC_TT_LFE_SPEAKER          0x0307  /* Speaker designed for low frequencies 
                                               (subwoofer). Not capable of reproducing 
                                               speech or music.                           */

/*----------------------------------------------------------------------------------------*/
/*  UAC Mixer Unit Descriptor                                                             */
/*----------------------------------------------------------------------------------------*/
#ifdef __ICCARM__
typedef struct ac_mxr_t
{
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bUnitID;              /* Constant uniquely identifying the Unit within the audio function. */
    __packed uint8_t  bNrInPins;            /* Number of Input Pins of this Unit: p       */
} AC_MXR_T;
#else
typedef struct __attribute__((__packed__)) ac_mxr_t
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubtype;
    uint8_t  bUnitID;                       /* Constant uniquely identifying the Unit within the audio function. */
    uint8_t  bNrInPins;                     /* Number of Input Pins of this Unit: p       */
} AC_MXR_T;
#endif

/*-----------------------------------------------------------------------------------
 *  UAC Selector Unit Descriptor
 */
#ifdef __ICCARM__
typedef struct ac_su_t
{
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bUnitID;              /* Constant uniquely identifying the Unit within the audio function. */
    __packed uint8_t  bNrInPins;            /* Number of Input Pins of this Unit: p       */
} AC_SU_T;
#else
typedef struct __attribute__((__packed__)) ac_su_t
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubtype;
    uint8_t  bUnitID;                       /* Constant uniquely identifying the Unit within the audio function. */
    uint8_t  bNrInPins;                     /* Number of Input Pins of this Unit: p       */
} AC_SU_T;
#endif

/*-----------------------------------------------------------------------------------
 *  UAC Feature Unit Descriptor
 */
#ifdef __ICCARM__
typedef struct ac_fu_t
{
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bUnitID;              /* Constant uniquely identifying the Unit within the audio function. */
    __packed uint8_t  bSourceID;            /* ID of the Unit or Terminal to which this Feature Unit is connected. */
    __packed uint8_t  bControlSize;         /* Size in bytes of an element of the bmaControls() array: n */
} AC_FU_T;
#else
typedef struct __attribute__((__packed__)) ac_fu_t
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubtype;
    uint8_t  bUnitID;                       /* Constant uniquely identifying the Unit within the audio function. */
    uint8_t  bSourceID;                     /* ID of the Unit or Terminal to which this Feature Unit is connected. */
    uint8_t  bControlSize;                  /* Size in bytes of an element of the bmaControls() array: n */
} AC_FU_T;
#endif

/* Feature Unit Control Selectors */
#define FU_CONTROL_UNDEFINED          0x00
#define MUTE_CONTROL                  0x01  /* Feature Unit Descriptor bmaControls bit 0  */
#define VOLUME_CONTROL                0x02  /* Feature Unit Descriptor bmaControls bit 1  */
#define BASS_CONTROL                  0x03  /* Feature Unit Descriptor bmaControls bit 2  */
#define MID_CONTROL                   0x04
#define TREBLE_CONTROL                0x05
#define GRAPHIC_EQUALIZER_CONTROL     0x06
#define AUTOMATIC_GAIN_CONTROL        0x07
#define DELAY_CONTROL                 0x08
#define BASS_BOOST_CONTROL            0x09
#define LOUDNESS_CONTROL              0x0A

/*-----------------------------------------------------------------------------------
 *  UAC AS Isochronous Audio Data Endpoint Descriptor
 */
#ifdef __ICCARM__
typedef struct as_gen_t
{
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bTerminalLink;
    __packed uint8_t  bDelay;
    __packed uint16_t wFormatTag;
} AS_GEN_T;
#else
typedef struct __attribute__((__packed__)) as_gen_t
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubtype;
    uint8_t  bTerminalLink;
    uint8_t  bDelay;
    uint16_t wFormatTag;
} AS_GEN_T;
#endif

/*-----------------------------------------------------------------------------------
 *  UAC Processing Unit Descriptor
 */
#ifdef __ICCARM__
typedef struct ac_pu_t
{
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bUnitID;              /* Constant uniquely identifying the Unit within the audio function. */
    __packed uint16_t wProcessType;         /* Constant identifying the type of processing this Unit is performing. */
    __packed uint8_t  bNrInPins;            /* Number of Input Pins of this Unit: p */
} AC_PU_T;
#else
typedef struct __attribute__((__packed__)) ac_pu_t
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubtype;
    uint8_t  bUnitID;                       /* Constant uniquely identifying the Unit within the audio function. */
    uint16_t wProcessType;                  /* Constant identifying the type of processing this Unit is performing. */
    uint8_t  bNrInPins;                     /* Number of Input Pins of this Unit: p */
} AC_PU_T;
#endif

/*-----------------------------------------------------------------------------------
 *  Class-Specific AS Isochronous Audio Data Endpoint Descriptor
 */
#ifdef __ICCARM__
typedef struct cs_ep_t
{
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bmAttributes;
    __packed uint8_t  bLockDelayUnits;
    __packed uint16_t wLockDelay;
} CS_EP_T;
#else
typedef struct __attribute__((__packed__)) cs_ep_t
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubtype;
    uint8_t  bmAttributes;
    uint8_t  bLockDelayUnits;
    uint16_t wLockDelay;
} CS_EP_T;
#endif

/*-----------------------------------------------------------------------------------
 *  UAC Type I Format Type Descriptor
 */
#ifdef __ICCARM__
typedef struct ac_ft1_t
{
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bFormatType;
    __packed uint8_t  bNrChannels;
    __packed uint8_t  bSubframeSize;
    __packed uint8_t  bBitResolution;
    __packed uint8_t  bSamFreqType;
    __packed uint8_t  tSamFreq[16][3];
} AS_FT1_T;
#else
typedef struct __attribute__((__packed__)) ac_ft1_t
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubtype;
    uint8_t  bFormatType;
    uint8_t  bNrChannels;
    uint8_t  bSubframeSize;
    uint8_t  bBitResolution;
    uint8_t  bSamFreqType;
    uint8_t  tSamFreq[16][3];
} AS_FT1_T;
#endif

/*-----------------------------------------------------------------------------------
 *  UAC Type 2 Format Type Descriptor
 */
#ifdef __ICCARM__
typedef struct ac_ft2_t
{
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bFormatType;
    __packed uint16_t wMaxBitRate;
    __packed uint16_t wSamplesPerFrame;
    __packed uint8_t  bSamFreqType;
} AS_FT2_T;
#else
typedef struct __attribute__((__packed__)) ac_ft2_t
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubtype;
    uint8_t  bFormatType;
    uint16_t wMaxBitRate;
    uint16_t wSamplesPerFrame;
    uint8_t  bSamFreqType;
} AS_FT2_T;
#endif

/*-----------------------------------------------------------------------------------
 *  UAC Type 3 Format Type Descriptor
 */
#ifdef __ICCARM__
typedef struct ac_ft3_t
{
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bFormatType;
    __packed uint8_t  bNrChannels;
    __packed uint8_t  bSubframeSize;
    __packed uint8_t  bBitResolution;
    __packed uint8_t  bSamFreqType;
    __packed uint8_t  tLowerSamFreq[3];
    __packed uint8_t  tUpperSamFreq[3];
} AS_FT3_T;
#else
typedef struct __attribute__((__packed__)) ac_ft3_t
{
    uint8_t  bLength;
    uint8_t  bDescriptorType;
    uint8_t  bDescriptorSubtype;
    uint8_t  bFormatType;
    uint8_t  bNrChannels;
    uint8_t  bSubframeSize;
    uint8_t  bBitResolution;
    uint8_t  bSamFreqType;
    uint8_t  tLowerSamFreq[3];
    uint8_t  tUpperSamFreq[3];
} AS_FT3_T;
#endif


/// @endcond HIDDEN_SYMBOLS


#endif /* __INCLUDED_UAC_H__ */

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/

