#ifndef __INCLUDED_UAC_H__
#define __INCLUDED_UAC_H__

#include "M480.h"
#include "usbh_lib.h"

/// @cond HIDDEN_SYMBOLS

#define USBAS_DEBUG

/*
 * Debug message
 */
#define USBAS_ERRMSG      printf

#ifdef USBAS_DEBUG
#define USBAS_DBGMSG      printf
#else
#define USBAS_DBGMSG(...)
#endif


#define UAC_IFACE_CODE                1

#define SUBCLS_UNDEFINED              0x00
#define SUBCLS_AUDIOCONTROL           0x01
#define SUBCLS_AUDIOSTREAMING         0x02
#define SUBCLS_MIDISTREAMING          0x03

/* Audio Class-specific descritpor types */
#define CS_UNDEFINED                  0x20
#define CS_DEVICE                     0x21
#define CS_CONFIGURATION              0x22
#define CS_STRING                     0x23
#define CS_INTERFACE                  0x24
#define CS_ENDPOINT                   0x25

/* Audio Class-Specific AC Interface Descriptor Subtypes */
#define AC_DESCRIPTOR_UNDEFINED       0x00
#define HEADER                        0x01
#define INPUT_TERMINAL                0x02
#define OUTPUT_TERMINAL               0x03
#define MIXER_UNIT                    0x04
#define SELECTOR_UNIT                 0x05
#define FEATURE_UNIT                  0x06
#define PROCESSING_UNIT               0x07
#define EXTENSION_UNIT                0x08

/* Audio Class-Specific AS Interface Descriptor Subtypes */
#define AS_DESCRIPTOR_UNDEFINED       0x00
#define AS_GENERAL                    0x01
#define FORMAT_TYPE                   0x02
#define FORMAT_SPECIFIC               0x03

/* Processing Unit Process Types */
#define PROCESS_UNDEFINED             0x00
#define UP_DOWNMIX_PROCESS            0x01
#define DOLBY_PROLOGIC_PROCESS        0x02
#define _3D_STEREO_EXTENDER_PROCESS   0x03
#define REVERBERATION_PROCESS         0x04
#define CHORUS_PROCESS                0x05
#define DYN_RANGE_COMP_PROCESS        0x06

/* Audio Class-Specific Endpoint Descriptor Subtypes */
#define DESCRIPTOR_UNDEFINED          0x00
#define EP_GENERAL                    0x01

/* Audio Class-Specific Request Codes */
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

/* Terminal Control Selectors */
#define TE_CONTROL_UNDEFINED          0x00
#define COPY_PROTECT_CONTROL          0x01

/* Feature Unit Control Selectors */
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

/* Up/Down-mix Processing Unit Control Selectors */
#define UD_CONTROL_UNDEFINED          0x00
#define UD_ENABLE_CONTROL             0x01
#define UD_MODE_SELECT_CONTROL        0x02

/* Dolby Prologic Processing Unit Control Selectors */
#define DP_CONTROL_UNDEFINED          0x00
#define DP_ENABLE_CONTROL             0x01
#define DP_MODE_SELECT_CONTROL        0x02

/* 3D Stereo Extender Processing Unit Control Selectors */
#define _3D_CONTROL_UNDEFINED         0x00
#define _3D_ENABLE_CONTROL            0x01
#define SPACIOUSNESS_CONTROL          0x03

/* Reverberation Processing Unit Control Selectors */
#define RV_CONTROL_UNDEFINED          0x00
#define RV_ENABLE_CONTROL             0x01
#define REVERB_LEVEL_CONTROL          0x02
#define REVERB_TIME_CONTROL           0x03
#define REVERB_FEEDBACK_CONTROL       0x04

/* Chorus Processing Unit Control Selectors */
#define CH_CONTROL_UNDEFINED          0x00
#define CH_ENABLE_CONTROL             0x01
#define CHORUS_LEVEL_CONTROL          0x02
#define CHORUS_RATE_CONTROL           0x03
#define CHORUS_DEPTH_CONTROL          0x04

/* Dynamic Range Compressor Processing Unit Control Selectors */
#define DR_CONTROL_UNDEFINED          0x00
#define DR_ENABLE_CONTROL             0x01
#define COMPRESSION_RATE_CONTROL      0x02
#define MAXAMPL_CONTROL               0x03
#define THRESHOLD_CONTROL             0x04
#define ATTACK_TIME                   0x05
#define RELEASE_TIME                  0x06

/* Extension Unit Control Selectors*/
#define XU_CONTROL_UNDEFINED          0x00
#define XU_ENABLE_CONTROL             0x01

/* Endpoint Control Selectors */
#define EP_CONTROL_UNDEFINED          0x00
#define SAMPLING_FREQ_CONTROL         0x01
#define PITCH_CONTROL                 0x02

/* Format Type Codes of Format Type Descriptor bFormatType field */
#define FORMAT_TYPE_UNDEFINED         0x00
#define FORMAT_TYPE_I                 0x01
#define FORMAT_TYPE_II                0x02
#define FORMAT_TYPE_III               0x03


/*-----------------------------------------------------------------------------------
 *  UAC Class-specific interface descriptor
 */
typedef struct ac_if_header {              /*! Audio Class-Specific AC Interface Header Descriptor   */
    __packed uint8_t  bLength;             /*!< Size of this descriptor, in bytes: 8+n               */
    __packed uint8_t  bDescriptorType;     /*!< CS_INTERFACE descriptor type; 0x24                   */
    __packed uint8_t  bDescriptorSubtype;  /*!< HEADER descriptor subtype; 0x1                       */
    __packed uint16_t bcdADC;              /*!< Audio Device Class Specification Release Number in Binary-Coded Decimal \hideinitializer  */
    __packed uint16_t wTotalLength;        /*!< Total number of bytes returned for the class-specific AudioControl interface
                                                descriptor. Includes the combined length of this descriptor header and all Unit and
                                                Terminal descriptors.                                */
    __packed uint8_t  bInCollection;       /*!< The number of AudioStreaming and MIDIStreaming interfaces in the Audio
                                                Interface Collection to which this AudioControl interface belongs.  */
} AC_IF_HDR_T;                             /*! Audio Class-Specific AC Interface Header Descriptor   */


/*-----------------------------------------------------------------------------------
 *  UAC Input Terminal Descriptor
 */
typedef struct ac_itd_t {                  /*! Audio Class-Specific Input Terminal Descriptor        */
    __packed uint8_t  bLength;             /*!< Size of this descriptor, in bytes: 12                */
    __packed uint8_t  bDescriptorType;     /*!< CS_INTERFACE descriptor type; 0x24                   */
    __packed uint8_t  bDescriptorSubtype;  /*!< INPUT_TERMINAL descriptor subtype; 0x2               */
    __packed uint8_t  bTerminalID;
    __packed uint16_t wTerminalType;
    __packed uint8_t  bAssocTerminal;
    __packed uint8_t  bNrChannels;
    __packed uint16_t wChannelConfig;
    __packed uint8_t  iChannelNames;
    __packed uint8_t  iTerminal;
} AC_IT_T;                                 /*! Audio Class-Specific Input Terminal Descriptor        */


/*-----------------------------------------------------------------------------------
 *  UAC Output Terminal Descriptor
 */
typedef struct ac_otd_t {
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bTerminalID;
    __packed uint16_t wTerminalType;
    __packed uint8_t  bAssocTerminal;
    __packed uint8_t  bSourceID;
    __packed uint8_t  iTerminal;
} AC_OT_T;


/*---------------------------------*/
/*  Terminal Types                 */
/*---------------------------------*/
// USB Terminal Types
#define UAC_TT_USB_UNDEFINED          0x0100   /* USB Terminal, undefined Type. */
#define UAC_TT_USB_STREAMING          0x0101   /* A Terminal dealing with a signal carried over an endpoint in an AudioStreaming interface. The AudioStreaming interface. */
#define UAC_TT_USB_VENDOR             0x01FF   /* A Terminal dealing with a signal carried over a vendor-specific interface. */
// Input Terminal Types
#define UAC_TT_INPUT_UNDEFINED        0x0200   /* Input Terminal, undefined Type. */
#define UAC_TT_MICROPHONE             0x0201   /* A generic microphone that does not fit under any of the other classifications. */
#define UAC_TT_DESKTOP_MICROPHONE     0x0202   /* A microphone normally placed on the desktop or integrated into the monitor. */
#define UAC_TT_PERSONAL_MICROPHONE    0x0203   /* A head-mounted or clip-on microphone. */
#define UAC_TT_OMNI_MICROPHONE        0x0204   /* A microphone designed to pick up voice from more than one speaker at relatively long ranges. */
#define UAC_TT_MICROPHONE_ARRAY       0x0205   /* An array of microphones designed for directional processing using host-based signal processing algorithms. */
// Output Terminal Types
#define UAC_TT_OUTPUT_UNDEFINED       0x0300   /* Output Terminal, undefined Type. */
#define UAC_TT_SPEAKER                0x0301   /* A generic speaker or set of speakers that does not fit under any of the other classifications. */
#define UAC_TT_HEADPHONES             0x0302   /* A head-mounted audio output device. */
#define UAC_TT_HEAD_MOUNTED           0x0303   /* The audio part of a VR head mounted display. The Associated Interfaces descriptor can be used to reference the HID interface used to report the position and orientation of the HMD. */
#define UAC_TT_DESKTOP_SPEAKER        0x0304   /* Relatively small speaker or set of speakers normally placed on the desktop or integrated into the monitor. These speakers are close to the user and have limited stereo separation. */
#define UAC_TT_ROOM_SPEAKER           0x0305   /* Larger speaker or set of speakers that are heard well anywhere in the room. */
#define UAC_TT_COMM_SPEAKER           0x0306   /* Speaker or set of speakers designed for voice communication. */
#define UAC_TT_LFE_SPEAKER            0x0307   /* Speaker designed for low frequencies (subwoofer). Not capable of reproducing speech or music. */


/*-----------------------------------------------------------------------------------
 *  UAC Mixer Unit Descriptor
 */
typedef struct ac_mxr_t {
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bUnitID;              /* Constant uniquely identifying the Unit within the audio function. */
    __packed uint8_t  bNrInPins;            /* Number of Input Pins of this Unit: p */
} AC_MXR_T;


/*-----------------------------------------------------------------------------------
 *  UAC Selector Unit Descriptor
 */
typedef struct ac_su_t {
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bUnitID;              /* Constant uniquely identifying the Unit within the audio function. */
    __packed uint8_t  bNrInPins;            /* Number of Input Pins of this Unit: p */
} AC_SU_T;


/*-----------------------------------------------------------------------------------
 *  UAC Feature Unit Descriptor
 */
typedef struct ac_fu_t {
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bUnitID;              /* Constant uniquely identifying the Unit within the audio function. */
    __packed uint8_t  bSourceID;            /* ID of the Unit or Terminal to which this Feature Unit is connected. */
    __packed uint8_t  bControlSize;         /* Size in bytes of an element of the bmaControls() array: n */
} AC_FU_T;


/* Feature Unit Control Selectors */
#define FU_CONTROL_UNDEFINED          0x00
#define MUTE_CONTROL                  0x01   /* Feature Unit Descriptor bmaControls bit 0 */
#define VOLUME_CONTROL                0x02   /* Feature Unit Descriptor bmaControls bit 1 */
#define BASS_CONTROL                  0x03   /* Feature Unit Descriptor bmaControls bit 2 */
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
typedef struct as_gen_t {
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bTerminalLink;
    __packed uint8_t  bDelay;
    __packed uint16_t wFormatTag;
} AS_GEN_T;


/*-----------------------------------------------------------------------------------
 *  UAC Processing Unit Descriptor
 */
typedef struct ac_pu_t {
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bUnitID;              /* Constant uniquely identifying the Unit within the audio function. */
    __packed uint16_t wProcessType;         /* Constant identifying the type of processing this Unit is performing. */
    __packed uint8_t  bNrInPins;            /* Number of Input Pins of this Unit: p */
} AC_PU_T;


/*-----------------------------------------------------------------------------------
 *  UAC Class-Specific AS Isochronous Audio Data Endpoint Descriptor
 */
typedef struct as_ep_t {
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bmAttributes;
    __packed uint8_t  bLockDelayUnits;
    __packed uint16_t wLockDelay;
} AS_EP_T;


/*-----------------------------------------------------------------------------------
 *  UAC Type I Format Type Descriptor
 */
typedef struct ac_ft1_t {
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bFormatType;
    __packed uint8_t  bNrChannels;
    __packed uint8_t  bSubframeSize;
    __packed uint8_t  bBitResolution;
    __packed uint8_t  bSamFreqType;
    __packed uint8_t  tSamFreq[16][3];
} AC_FT1_T;

/*-----------------------------------------------------------------------------------
 *  UAC Type 2 Format Type Descriptor
 */
typedef struct ac_ft2_t {
    __packed uint8_t  bLength;
    __packed uint8_t  bDescriptorType;
    __packed uint8_t  bDescriptorSubtype;
    __packed uint8_t  bFormatType;
    __packed uint16_t wMaxBitRate;
    __packed uint16_t wSamplesPerFrame;
    __packed uint8_t  bSamFreqType;
} AC_FT2_T;

/*-----------------------------------------------------------------------------------
 *  UAC Type 3 Format Type Descriptor
 */
typedef struct ac_ft3_t {
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
} AC_FT3_T;


typedef struct uac_info_t {
    uint8_t    *cfg_desc;

    struct usb_interface_descriptor *last_ifd;
    AS_GEN_T   *last_gen;
    AC_FT1_T   *last_ft;

    struct usb_interface_descriptor *ifd_play;
    struct usb_endpoint_descriptor  *epd_play;
    AS_GEN_T   *gen_play;
    AC_FT1_T   *ft_play;
    AC_OT_T    *ot_speaker;        /* refer to SPEAKER OUTPUT TERMINAL */
    AC_IT_T    *it_usbs;           /* refer to USB streaming INPUT TERMINAL */
    AC_FU_T    *fu_play;           /* FEATURE UNIT for Speaker */

    struct usb_interface_descriptor *ifd_rec;
    struct usb_endpoint_descriptor  *epd_rec;
    AS_GEN_T   *gen_rec;
    AC_FT1_T   *ft_rec;
    AC_IT_T    *it_microphone;     /* refer to MICROPHONE INPUT TERMINAL */
    AC_OT_T    *ot_usbs;           /* refer to USB streaming OUTPUT TERMINAL */
    AC_FU_T    *fu_rec;            /* FEATURE UNIT for Microphone */

} UAC_INFO_T;


int uac_config_parser(UAC_DEV_T *audev);
int uac_check_fu_ctrl(UAC_INFO_T  *uac_info, uint8_t target, int channel, int control);


/// @endcond HIDDEN_SYMBOLS


#endif /* __INCLUDED_UAC_H__ */

/*** (C) COPYRIGHT 2015 Nuvoton Technology Corp. ***/

