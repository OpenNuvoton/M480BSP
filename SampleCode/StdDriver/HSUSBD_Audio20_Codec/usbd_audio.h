/******************************************************************************
 * @file     usbd_audio.h
 * @brief    NuMicro series HSUSBD driver header file
 * @version  1.0.0
 * @date     22, Sep, 2016
 *
 * @note
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __USBD_UAC_H__
#define __USBD_UAC_H__

#define NAU8822     0

/* Define the vendor id and product id */
#define USBD_VID        0x0416
#define USBD_PID        0x1287

#define AUDIO_RATE  AUDIO_RATE_48K

#define AUDIO_RATE_48K   48000       /* The audo play sampling rate. The setting is 48KHz */
#define AUDIO_RATE_96K   96000       /* The audo play sampling rate. The setting is 96KHz */
#define AUDIO_RATE_441K  44100       /* The audo play sampling rate. The setting is 44.1KHz */
#define AUDIO_RATE_192K  192000      /* The audo play sampling rate. The setting is 192KHz */

/*!<Define Audio information */
#define PLAY_CHANNELS   2
#define PLAY_BIT_RATE   0x10    /* 16-bit data rate */

#define REC_CHANNELS    2
#define REC_BIT_RATE    0x10    /* 16-bit data rate */

#define REC_FEATURE_UNITID      0x05
#define PLAY_FEATURE_UNITID     0x06
#define CLOCK_SOURCE_ID         0x29

#define BUFF_LEN    800

/* Define Descriptor information */
#if(PLAY_CHANNELS == 1)
#define PLAY_CH_CFG     1
#define REC_CH_CFG      0
#endif
#if(PLAY_CHANNELS == 2)
#define PLAY_CH_CFG     3
#define REC_CH_CFG      3
#endif

/********************************************/
/* Audio Class Current State                */
/********************************************/
/*!<Define Audio Class Current State */
#define UAC_STOP_AUDIO_RECORD           0
#define UAC_START_AUDIO_RECORD          1
#define UAC_PROCESSING_AUDIO_RECORD     2
#define UAC_BUSY_AUDIO_RECORD           3

/***************************************************/
/*      Audio Class-Specific Request Codes         */
/***************************************************/
/*!<Define Audio Class Specific Request */
#define UAC_REQUEST_CODE_UNDEFINED  0x00
#define UAC_SET_CUR                 0x01
#define UAC_GET_CUR                 0x01
#define UAC_SET_MIN                 0x02
#define UAC_GET_MIN                 0x02
#define UAC_SET_MAX                 0x03
#define UAC_GET_MAX                 0x03
#define UAC_SET_RES                 0x04
#define UAC_GET_RES                 0x04
#define UAC_SET_MEM                 0x05
#define UAC_GET_MEM                 0x05
#define UAC_GET_STAT                0xFF

#define MUTE_CONTROL                0x01
#define VOLUME_CONTROL              0x02

#define FREQ_CONTROL                0x01
#define FREQ_VALID                  0x02

#define UAC_CUR                     0x01
#define UAC_RANGE                   0x02
#define UAC_MEM                     0x03

#define UAC_MD_ENABLE_CONTROL       0x01
#define UAC_MD_BALANCE_CONTROL      0x02

/*-------------------------------------------------------------*/
/* Define EP maximum packet size */
#define CEP_MAX_PKT_SIZE        64
#define EPA_MAX_PKT_SIZE        192
#define EPB_MAX_PKT_SIZE        200
#define EPE_MAX_PKT_SIZE        64

#define CEP_BUF_BASE    0
#define CEP_BUF_LEN     CEP_MAX_PKT_SIZE
#define EPA_BUF_BASE    0x100
#define EPA_BUF_LEN     0x600
#define EPB_BUF_BASE    0x700
#define EPB_BUF_LEN     0x600
#define EPE_BUF_BASE    0xD00
#define EPE_BUF_LEN     EPE_MAX_PKT_SIZE

/* Define the interrupt In EP number */
#define ISO_IN_EP_NUM           0x01
#define ISO_OUT_EP_NUM          0x02
#define ISO_FEEDBACK_ENDPOINT   0x02

#define PDMA_TXBUFFER_CNT     7
#define PDMA_RXBUFFER_CNT     8

#define PDMA_I2S_TX_CH  1
#define PDMA_I2S_RX_CH  2

/* For I2C transfer */
typedef enum {
    E_RS_NONE,          // no re-sampling
    E_RS_UP,            // up sampling
    E_RS_DOWN           // down sampling
} RESAMPLE_STATE_T;


/*-------------------------------------------------------------*/
extern uint32_t volatile u32BuffLen, u32RxBuffLen;
extern uint32_t g_usbd_UsbAudioState;
extern volatile uint8_t u8AudioPlaying;
extern volatile uint8_t u8TxDataCntInBuffer;
extern uint32_t g_usbd_SampleRate;

void UAC_DeviceEnable(uint32_t bIsPlay);
void UAC_DeviceDisable(uint32_t bIsPlay);
void UAC_GetPlayData(void);
void UAC_SendRecData(void);

void AudioStartPlay(uint32_t u32SampleRate);
void AudioStartRecord(uint32_t u32SampleRate);
/*-------------------------------------------------------------*/
void UAC_Init(void);
void UAC_ClassRequest(void);
void UAC_SetInterface(uint32_t u32AltInterface);

void EPA_Handler(void);
void EPB_Handler(void);
void timer_init(void);
void AdjustCodecPll(RESAMPLE_STATE_T r);
#if NAU8822
void NAU8822_Setup(void);
void NAU8822_ConfigSampleRate(uint32_t u32SampleRate);
#else
void NAU88L25_Reset(void);
void NAU88L25_Setup(void);
void NAU88L25_ConfigSampleRate(uint32_t u32SampleRate);
#endif

typedef struct dma_desc_t {
    uint32_t ctl;
    uint32_t src;
    uint32_t dest;
    uint32_t offset;
} DMA_DESC_T;

extern volatile uint8_t g_usbd_txflag;
extern volatile uint8_t g_usbd_rxflag;
extern void PDMA_Init(void);
extern void PDMA_WriteTxSGTable(void);
extern void PDMA_ResetRxSGTable(uint8_t id);
extern void PDMA_WriteRxSGTable(void);
#endif  /* __USBD_UAC_H_ */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
