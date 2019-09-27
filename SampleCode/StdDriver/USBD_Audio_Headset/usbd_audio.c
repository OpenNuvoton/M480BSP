/**************************************************************************//**
 * @file     usbd_audio.c
 * @brief    NuMicro series USBD driver Sample file
 * @version  1.0.0
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

/*!<Includes */
#include <string.h>
#include "NuMicro.h"
#include "usbd_audio.h"

uint32_t volatile g_usbd_SampleRate = AUDIO_RATE;

/*--------------------------------------------------------------------------*/
/* Global variables for Audio class */
volatile uint32_t g_usbd_UsbAudioState = 0;
volatile uint32_t g_usbd_PlaySampleRate  = PLAY_RATE;
volatile uint32_t g_usbd_RecSampleRate   = REC_RATE;
volatile uint32_t g_PrePlaySampleRate  = PLAY_RATE;
volatile uint32_t g_PreRecSampleRate   = REC_RATE;

volatile uint32_t g_play_max_packet_size = (PLAY_RATE * PLAY_CHANNELS * 2 / 1000);
volatile uint32_t g_rec_max_packet_size = (REC_RATE * REC_CHANNELS * 2 / 1000);

volatile uint32_t g_resample_play_s_idx = 3;
volatile uint32_t g_resample_rec_s_idx = 3;

volatile uint32_t g_u32SampleRate = PLAY_RATE / 1000;
volatile uint32_t g_play_len_frame = PLAY_RATE / 1000;

volatile uint8_t g_usbd_RecMute       = 0x0001;   /* Record MUTE control. 0 = normal. 1 = MUTE */
volatile int16_t g_usbd_RecVolumeL    = 0x0000;   /* Record left channel volume. Range is -8176 ~ 8176 */
volatile int16_t g_usbd_RecVolumeR    = 0x0000;   /* Record right channel volume. Range is -8176 ~ 8176 */
volatile int16_t g_usbd_RecMaxVolume  =   8176;   /*  8176 */
volatile int16_t g_usbd_RecMinVolume  =  -8176;   /* -8176 */
volatile int16_t g_usbd_RecResVolume  = 0x0020;

volatile uint8_t g_usbd_PlayMute      = 0x0000;   /* Play MUTE control. 0 = normal. 1 = MUTE */
volatile int16_t g_usbd_PlayVolumeL   = 0xFFC0;   /* Play left channel volume. Range is -32752 ~ -25504 */
volatile int16_t g_usbd_PlayVolumeR   = 0xFFC0;   /* Play right channel volume. Range is -32752 ~ -25504 */
volatile int16_t g_usbd_PlayMaxVolume = 0xFFF0;   /* -32752 */
volatile int16_t g_usbd_PlayMinVolume = 0xE3A0;   /* -25504 */
volatile int16_t g_usbd_PlayResVolume = 0x0030;

uint8_t volatile u8PlayEn = 0;
uint8_t volatile u8AudioPlaying=0;
uint8_t volatile u8TxDataCntInBuffer=0;
uint8_t volatile u8PDMATxIdx=0;

uint8_t volatile u8RecEn = 0;
uint8_t volatile u8RxDataCntInBuffer=0;
uint8_t volatile u8PDMARxIdx=0;

uint32_t volatile u32BuffLen = 0, u32RxBuffLen = 0;

/* Player Buffer and its pointer */
#ifdef __ICCARM__
#pragma data_alignment=4
uint32_t PcmPlayBuff[PDMA_TXBUFFER_CNT][BUFF_LEN] = {0};
uint32_t PcmPlayBuffLen[PDMA_TXBUFFER_CNT] = {0};

uint8_t PcmRecBuff[PDMA_RXBUFFER_CNT][BUFF_LEN] = {0};
uint8_t u8PcmRxBufFull[PDMA_RXBUFFER_CNT] = {0};

uint32_t g_au32UsbTmpBuf[AUDIO_RATE_96K * 2 * PLAY_CHANNELS / 1000 / 4 + 16] = {0};
short g_a16AudioTmpBuf0[REC_RATE * 2 * REC_CHANNELS / 1000 + 16] = {0};
#else
uint32_t PcmPlayBuff[PDMA_TXBUFFER_CNT][BUFF_LEN] __attribute__((aligned(4))) = {0};
uint32_t PcmPlayBuffLen[PDMA_TXBUFFER_CNT] __attribute__((aligned(4))) = {0};

uint8_t PcmRecBuff[PDMA_RXBUFFER_CNT][BUFF_LEN] __attribute__((aligned(4))) = {0};
uint8_t u8PcmRxBufFull[PDMA_RXBUFFER_CNT] __attribute__((aligned(4))) = {0};

uint32_t g_au32UsbTmpBuf[AUDIO_RATE_96K * 2 * PLAY_CHANNELS / 1000 / 4 + 16] __attribute__((aligned(4))) = {0};
short g_a16AudioTmpBuf0[REC_RATE * 2 * REC_CHANNELS / 1000 + 16] __attribute__((aligned(4))) = {0};
#endif

volatile uint32_t u32BufPlayIdx = 0;
volatile uint32_t u32PlayBufPos=0;
volatile uint32_t u32BufRecIdx = 0;


/*--------------------------------------------------------------------------*/
/**
 * @brief       USBD Interrupt Service Routine
 *
 * @param[in]   None
 *
 * @return      None
 *
 * @details     This function is the USBD ISR
 */
void USBD_IRQHandler(void)
{
    uint32_t u32IntSts = USBD_GET_INT_FLAG();
    uint32_t u32State = USBD_GET_BUS_STATE();

//------------------------------------------------------------------
    if(u32IntSts & USBD_INTSTS_FLDET)
    {
        // Floating detect
        USBD_CLR_INT_FLAG(USBD_INTSTS_FLDET);

        if (USBD_IS_ATTACHED())
        {
            /* USB Plug In */
            USBD_ENABLE_USB();
        }
        else
        {
            /* USB Un-plug */
            USBD_DISABLE_USB();
        }
    }

//------------------------------------------------------------------
    if(u32IntSts & USBD_INTSTS_BUS)
    {
        /* Clear event flag */
        USBD_CLR_INT_FLAG(USBD_INTSTS_BUS);

        if(u32State & USBD_STATE_USBRST)
        {
            /* Bus reset */
            USBD_ENABLE_USB();
            USBD_SwReset();
        }
        if(u32State & USBD_STATE_SUSPEND)
        {
            /* Enable USB but disable PHY */
            USBD_DISABLE_PHY();
        }
        if(u32State & USBD_STATE_RESUME)
        {
            /* Enable USB and enable PHY */
            USBD_ENABLE_USB();
        }
    }

//------------------------------------------------------------------
    if(u32IntSts & USBD_INTSTS_WAKEUP)
    {
        /* Clear event flag */
        USBD_CLR_INT_FLAG(USBD_INTSTS_WAKEUP);
    }

    if(u32IntSts & USBD_INTSTS_USB)
    {
        // USB event
        if(u32IntSts & USBD_INTSTS_SETUP)
        {
            // Setup packet
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_SETUP);

            /* Clear the data IN/OUT ready flag of control end-points */
            USBD_STOP_TRANSACTION(EP0);
            USBD_STOP_TRANSACTION(EP1);

            USBD_ProcessSetupPacket();
        }

        // EP events
        if(u32IntSts & USBD_INTSTS_EP0)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP0);

            // control IN
            USBD_CtrlIn();
        }

        if(u32IntSts & USBD_INTSTS_EP1)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP1);

            // control OUT
            USBD_CtrlOut();
        }

        if(u32IntSts & USBD_INTSTS_EP2)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP2);

            // Isochronous IN
            EP2_Handler();
        }

        if(u32IntSts & USBD_INTSTS_EP3)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP3);

            // Isochronous OUT
            EP3_Handler();
        }

        if(u32IntSts & USBD_INTSTS_EP4)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP4);
#ifdef __FEEDBACK__
            /* Isochronous IN for Feedback */
            EP4_Handler();
#endif
        }

        if(u32IntSts & USBD_INTSTS_EP5)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP5);
#ifdef __HID__
            /* Interrupt IN for HID */
            EP5_Handler();
#endif
        }

        if(u32IntSts & USBD_INTSTS_EP6)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP6);
        }

        if(u32IntSts & USBD_INTSTS_EP7)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP7);
        }
    }
}

/**
 * @brief       EP2 Handler
 *
 * @param[in]   None
 *
 * @return      None
 *
 * @details     This function is used to process EP2 event
 */
/* Record */
void EP2_Handler(void)
{
    /* ISO IN transfer ACK */
    if (g_usbd_UsbAudioState == UAC_START_AUDIO_RECORD)
        UAC_SendRecData();
}

/**
 * @brief       EP3 Handler
 *
 * @param[in]   None
 *
 * @return      None
 *
 * @details     This function is used to process EP3 event
 */
/* Play */
void EP3_Handler(void)
{
    /* ISO OUT transfer ACK */
    uint32_t u32Len,u32Samples = 0;
    short *pu16Buf;
    short *p16Src;

    /* Get the address in USB buffer */
    p16Src = (short *)((uint32_t)USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP3));

    /* Get the temp buffer */
    pu16Buf = (short *)g_au32UsbTmpBuf;

    u32Len = USBD_GET_PAYLOAD_LEN(EP3) >> 2;

    /* Audio data is resampled to 48MHz (Audio Codec is fixed to 48MHz) */
    /* Do Resample operation to data in USB buffer to SRAM buffer */
    if(PLAY_CHANNELS == 2)
    {
        u32Samples  = Resamples(E_RS_PLAY_CH0, p16Src, PLAY_CHANNELS, u32Len, pu16Buf, g_resample_play_s_idx);

        u32Samples += Resamples(E_RS_PLAY_CH1, &p16Src[1], PLAY_CHANNELS, u32Len, &pu16Buf[1], g_resample_play_s_idx);
    }
    else
        u32Samples  = Resamples(E_RS_PLAY_CH0, p16Src, PLAY_CHANNELS, u32Len, pu16Buf, g_resample_play_s_idx);

    /* Play Data Length for SAMPLING_RATE */
    u32Len = u32Samples * 2;

    UAC_GetPlayData((uint8_t *)g_au32UsbTmpBuf, u32Len);
#ifdef __FEEDBACK__
    /* Prepare for nex OUT packet */
    USBD_SET_PAYLOAD_LEN(EP3, g_play_max_packet_size + 64);
#else
    /* Prepare for nex OUT packet */
    USBD_SET_PAYLOAD_LEN(EP3, g_play_max_packet_size);
#endif
}

#ifdef __FEEDBACK__
/**
 * @brief       EP4 Handler (Iso IN feedback interrupt handler)
 *
 * @param[in]   None
 *
 * @return      None
 *
 */
void EP4_Handler(void)
{
    uint8_t *pu8Buf;

    if (u8AudioPlaying)
    {
        if ((u8TxDataCntInBuffer >= (PDMA_TXBUFFER_CNT/2)) && (u8TxDataCntInBuffer <= (PDMA_TXBUFFER_CNT/2+1)))
        {
            g_u32SampleRate = g_play_len_frame;
        }
        else if (u8TxDataCntInBuffer >= (PDMA_TXBUFFER_CNT-2))
        {
            g_u32SampleRate = g_play_len_frame -3;
        }
        else
        {
            g_u32SampleRate = g_play_len_frame + 3;
        }
    }
    /* Get the address in USB buffer */
    pu8Buf = (uint8_t *)((uint32_t)USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP4));

    /* Prepare the data to USB IN buffer */
    *pu8Buf++ = 0x00;
    *pu8Buf++ = (g_u32SampleRate & 0x3) << 6;
    *pu8Buf = (g_u32SampleRate & 0xFC) >> 2;
    /* Trigger ISO IN */
    USBD_SET_PAYLOAD_LEN(EP4, 3);
}
#endif
#ifdef __HID__
void EP5_Handler(void)  /* Interrupt IN handler */
{
    g_u8EP5Ready = 1;
}
#endif


/*--------------------------------------------------------------------------*/
/**
 * @brief       UAC Class Initial
 *
 * @param[in]   None
 *
 * @return      None
 *
 * @details     This function is used to configure endpoints for UAC class
 */
void UAC_Init(void)
{
#ifdef __FEEDBACK__
    uint8_t *pu8Buf;
#endif 
    if ((g_usbd_SampleRate % 8000) == 0)
    {
        u32BuffLen = 768;
        u32RxBuffLen = (g_usbd_SampleRate / 1000) * 4;
    }
    else
    {
        u32BuffLen = 441;
        u32RxBuffLen = 444;
    }

    /* Init setup packet buffer */
    /* Buffer for setup packet -> [0 ~ 0x7] */
    USBD->STBUFSEG = SETUP_BUF_BASE;

    /*****************************************************/
    /* EP0 ==> control IN endpoint, address 0 */
    USBD_CONFIG_EP(EP0, USBD_CFG_CSTALL | USBD_CFG_EPMODE_IN | 0);
    /* Buffer range for EP0 */
    USBD_SET_EP_BUF_ADDR(EP0, EP0_BUF_BASE);

    /* EP1 ==> control OUT endpoint, address 0 */
    USBD_CONFIG_EP(EP1, USBD_CFG_CSTALL | USBD_CFG_EPMODE_OUT | 0);
    /* Buffer range for EP1 */
    USBD_SET_EP_BUF_ADDR(EP1, EP1_BUF_BASE);

    /*****************************************************/
    /* EP2 ==> Isochronous IN endpoint, address 1 */
    USBD_CONFIG_EP(EP2, USBD_CFG_EPMODE_IN | ISO_IN_EP_NUM | USBD_CFG_TYPE_ISO);
    /* Buffer offset for EP2 */
    USBD_SET_EP_BUF_ADDR(EP2, EP2_BUF_BASE);

    /*****************************************************/
    /* EP3 ==> Isochronous OUT endpoint, address 2 */
    USBD_CONFIG_EP(EP3, USBD_CFG_EPMODE_OUT | ISO_OUT_EP_NUM | USBD_CFG_TYPE_ISO);
    /* Buffer offset for EP3 */
    USBD_SET_EP_BUF_ADDR(EP3, EP3_BUF_BASE);
    /* trigger receive OUT data */
    USBD_SET_PAYLOAD_LEN(EP3, EP3_MAX_PKT_SIZE);

#ifdef __FEEDBACK__
    /*****************************************************/
    /* EP4 ==> Isochronous IN endpoint, address 3 */
    USBD_CONFIG_EP(EP4, USBD_CFG_EPMODE_IN | ISO_IN_FB_EP_NUM | USBD_CFG_TYPE_ISO);
    /* Buffer offset for EP4 */
    USBD_SET_EP_BUF_ADDR(EP4, EP4_BUF_BASE);

    g_u32SampleRate = PLAY_RATE/1000;
#endif
#ifdef __HID__
    /*****************************************************/
    /* EP5 ==> Interrupt IN endpoint, address 4 */
    USBD_CONFIG_EP(EP5, USBD_CFG_EPMODE_IN | HID_IN_EP_NUM);
    /* Buffer offset for EP5 */
    USBD_SET_EP_BUF_ADDR(EP5, EP5_BUF_BASE);

    g_u8EP5Ready = 1;
#endif
#ifdef __FEEDBACK__
    /* Feedback Endpoint */
    pu8Buf = (uint8_t *)((uint32_t)USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP4));
    g_u32SampleRate = g_usbd_PlaySampleRate / 1000;
    g_play_len_frame = g_usbd_PlaySampleRate / 1000;

    /* Prepare the data to USB IN buffer */
    *pu8Buf++ = 0x00;
    *pu8Buf++ = (g_u32SampleRate & 0x3) << 6;
    *pu8Buf = (g_u32SampleRate & 0xFC) >> 2;

    /* Trigger ISO IN */
    USBD_SET_DATA1(EP4);
    USBD_SET_PAYLOAD_LEN(EP4, 3);
    /* End of Feedback Endpoint */
#endif
}


/**
 * @brief       UAC class request
 *
 * @param[in]   None
 *
 * @return      None
 *
 * @details     This function is used to process UAC class requests
 */
void UAC_ClassRequest(void)
{
    uint8_t buf[8];
#ifdef __HID__
    static uint8_t u8Protocol = 0;
    static uint8_t u8Idle = 0;
#endif

    USBD_GetSetupPacket(buf);

    if (buf[0] & 0x80)
    {
        /* request data transfer direction */
        // Device to host
        switch (buf[1])
        {
        case UAC_GET_CUR:
        {
            /* request to endpoint */
            if((buf[4] & 0x0F) == ISO_IN_EP_NUM)
            {
                M32(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_RecSampleRate;
                /* Data stage */
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, buf[6]);
                break;
            }
            else if((buf[4] & 0x0F) == ISO_OUT_EP_NUM)
            {
                M32(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_PlaySampleRate;
                /* Data stage */
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, buf[6]);
                break;
            }
            else
            {
                switch (buf[3])
                {
                case MUTE_CONTROL:
                {
                    if (REC_FEATURE_UNITID == buf[5])
                        M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_RecMute;
                    else if (PLAY_FEATURE_UNITID == buf[5])
                        M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_PlayMute;

                    /* Data stage */
                    USBD_SET_DATA1(EP0);
                    USBD_SET_PAYLOAD_LEN(EP0, 1);
                    break;
                }
                case VOLUME_CONTROL:
                {
                    if (REC_FEATURE_UNITID == buf[5])
                    {
                        /* Left or right channel */
                        if(buf[2] == 1)
                        {
                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_RecVolumeL;
                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_RecVolumeL >> 8;
                        }
                        else
                        {
                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_RecVolumeR;
                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_RecVolumeR >> 8;
                        }
                    }
                    else if (PLAY_FEATURE_UNITID == buf[5])
                    {
                        if(buf[2] == 1)
                        {
                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_PlayVolumeL;
                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_PlayVolumeL >> 8;
                        }
                        else
                        {
                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_PlayVolumeR;
                            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_PlayVolumeR >> 8;
                        }
                    }
                    /* Data stage */
                    USBD_SET_DATA1(EP0);
                    USBD_SET_PAYLOAD_LEN(EP0, 2);
                    break;
                }
                default:
                {
                    /* Setup error, stall the device */
                    USBD_SetStall(0);
                }
                }
            }
            // Trigger next Control Out DATA1 Transaction.
            /* Status stage */
            USBD_PrepareCtrlOut(0,0);
            break;
        }

        case UAC_GET_MIN:
        {
            switch (buf[3])
            {
            case VOLUME_CONTROL:
            {
                if (REC_FEATURE_UNITID == buf[5])
                {
                    M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_RecMinVolume;
                    M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_RecMinVolume >> 8;
                }
                else if (PLAY_FEATURE_UNITID == buf[5])
                {
                    M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_PlayMinVolume;
                    M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_PlayMinVolume >> 8;
                }
                /* Data stage */
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, 2);
                break;
            }
            default:
                /* STALL control pipe */
                USBD_SetStall(0);
            }
            // Trigger next Control Out DATA1 Transaction.
            /* Status stage */
            USBD_PrepareCtrlOut(0,0);
            break;
        }

        case UAC_GET_MAX:
        {
            switch (buf[3])
            {
            case VOLUME_CONTROL:
            {
                if (REC_FEATURE_UNITID == buf[5])
                {
                    M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_RecMaxVolume;
                    M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_RecMaxVolume >> 8;
                }
                else if (PLAY_FEATURE_UNITID == buf[5])
                {
                    M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_PlayMaxVolume;
                    M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_PlayMaxVolume >> 8;
                }
                /* Data stage */
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, 2);
                break;
            }
            default:
                /* STALL control pipe */
                USBD_SetStall(0);
            }
            // Trigger next Control Out DATA1 Transaction.
            /* Status stage */
            USBD_PrepareCtrlOut(0,0);
            break;
        }

        case UAC_GET_RES:
        {
            switch (buf[3])
            {
            case VOLUME_CONTROL:
            {
                if (REC_FEATURE_UNITID == buf[5])
                {
                    M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_RecResVolume;
                    M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_RecResVolume >> 8;
                }
                else if (PLAY_FEATURE_UNITID == buf[5])
                {
                    M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = g_usbd_PlayResVolume;
                    M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1) = g_usbd_PlayResVolume >> 8;
                }
                /* Data stage */
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, 2);
                break;
            }
            default:
                /* STALL control pipe */
                USBD_SetStall(0);
            }
            // Trigger next Control Out DATA1 Transaction.
            /* Status stage */
            USBD_PrepareCtrlOut(0,0);
            break;
        }

#ifdef __HID__
//         case GET_REPORT:
//         {
//             break;
//         }
        case GET_IDLE:
        {
//            /* Setup error, stall the device */
//            USBD_SetStall(0);
//            break;
            /* Data stage */
            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = u8Idle;
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 1);
            /* Status stage */
            USBD_PrepareCtrlOut(0,0);
            break;
        }
        case GET_PROTOCOL:
        {
            /* Data stage */
            M8(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0)) = u8Protocol;
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 1);
            /* Status stage */
            USBD_PrepareCtrlOut(0,0);
            break;
        }
#endif
        default:
        {
            /* Setup error, stall the device */
            USBD_SetStall(0);
        }
        }
    }
    else
    {
        // Host to device
        switch (buf[1])
        {
        case UAC_SET_CUR:
        {
            /* request to endpoint */
            if((buf[4] & 0x0F) == ISO_IN_EP_NUM)
            {
                USBD_PrepareCtrlOut((uint8_t *)&g_usbd_RecSampleRate, buf[6]);
                /* Status stage */
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, 0);
                break;
            }
            else if((buf[4] & 0x0F) == ISO_OUT_EP_NUM)
            {                     
                USBD_PrepareCtrlOut((uint8_t *)&g_usbd_PlaySampleRate, buf[6]);
                /* Status stage */
                USBD_SET_DATA1(EP0);
                USBD_SET_PAYLOAD_LEN(EP0, 0);
                break;
            }
            else
            {
                switch (buf[3])
                {
                case MUTE_CONTROL:
                    if (REC_FEATURE_UNITID == buf[5])
                        USBD_PrepareCtrlOut((uint8_t *)&g_usbd_RecMute, buf[6]);
                    else if (PLAY_FEATURE_UNITID == buf[5])
                        USBD_PrepareCtrlOut((uint8_t *)&g_usbd_PlayMute, buf[6]);
                    /* Status stage */
                    USBD_SET_DATA1(EP0);
                    USBD_SET_PAYLOAD_LEN(EP0, 0);
                    break;

                case VOLUME_CONTROL:
                    if (REC_FEATURE_UNITID == buf[5])
                    {
                        if(buf[2] == 1)
                        {
                            /* Prepare the buffer for new record volume of left channel */
                            USBD_PrepareCtrlOut((uint8_t *)&g_usbd_RecVolumeL, buf[6]);
                        }
                        else
                        {
                            /* Prepare the buffer for new record volume of right channel */
                            USBD_PrepareCtrlOut((uint8_t *)&g_usbd_RecVolumeR, buf[6]);
                        }
                    }
                    else if (PLAY_FEATURE_UNITID == buf[5])
                    {
                        if (buf[2] == 1)
                        {
                            USBD_PrepareCtrlOut((uint8_t *)&g_usbd_PlayVolumeL, buf[6]);
                        }
                        else
                        {
                            USBD_PrepareCtrlOut((uint8_t *)&g_usbd_PlayVolumeR, buf[6]);
                        }
                    }
                    /* Status stage */
                    USBD_SET_DATA1(EP0);
                    USBD_SET_PAYLOAD_LEN(EP0, 0);
                    break;

                default:
                    /* STALL control pipe */
                    USBD_SetStall(0);
                    break;
                }
                break;
            }
        }

#ifdef __HID__
        case SET_REPORT:
        {
            if (buf[3] == 3)
            {
                printf("Set Report\n");
                /* Request Type = Feature */
                USBD_SET_DATA1(EP1);
                USBD_SET_PAYLOAD_LEN(EP1, 0);
            }
            break;
        }
        case SET_IDLE:
        {
            /* Status stage */
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 0);
            break;
        }
        case SET_PROTOCOL:
#endif
        default:
        {
            /* Setup error, stall the device */
            USBD_SetStall(0);
            break;
        }
        }
    }
}

/**
 * @brief       Set Interface standard request
 *
 * @param[in]   u32AltInterface Interface
 *
 * @return      None
 *
 * @details     This function is used to set UAC Class relative setting
 */
void UAC_SetInterface(uint32_t u32AltInterface)
{
    uint8_t buf[8];

    USBD_GetSetupPacket(buf);

    if (buf[4] == 1)
    {
        /* Audio Iso IN interface */
        if (u32AltInterface == 1)
        {
            g_usbd_UsbAudioState = UAC_START_AUDIO_RECORD;
            USBD_SET_DATA1(EP2);
            USBD_SET_PAYLOAD_LEN(EP2, 0);
            UAC_DeviceEnable(0);
        }
        else if (u32AltInterface == 0)
        {
            UAC_DeviceDisable(0);
            USBD_SET_DATA1(EP2);
            USBD_SET_PAYLOAD_LEN(EP2, 0);
            g_usbd_UsbAudioState = UAC_STOP_AUDIO_RECORD;
        }
    }
    else if (buf[4] == 2)
    {
        /* Audio Iso OUT interface */
        if (u32AltInterface == 1)
        {
            USBD_SET_PAYLOAD_LEN(EP3, EP3_MAX_PKT_SIZE);
            UAC_DeviceEnable(1);
        }
        else
            UAC_DeviceDisable(1);
    }
}

/**
  * @brief  UAC_DeviceEnable. To enable the device to play or record audio data.
  * @param  None.
  * @retval None.
  */
void UAC_DeviceEnable(uint32_t bIsPlay)
{
    if (bIsPlay)
    {
        /* Enable play hardware */
        u8PlayEn = 1;
        TIMER_Start(TIMER0);
    }
    else
    {
        /* Enable record hardware */
        if(!u8RecEn)
        {
            AudioStartRecord(g_usbd_SampleRate);
        }

        u8RecEn = 1;
    }
}


/**
  * @brief  UAC_DeviceDisable. To disable the device to play or record audio data.
  * @param  None.
  * @retval None.
  */
void UAC_DeviceDisable(uint32_t bIsPlay)
{
    if (bIsPlay)
    {
        /* Disable play hardware/stop play */
        u8PlayEn = 0;
        /* Disable I2S Tx function */
        I2S_DISABLE_TXDMA(I2S0);
        I2S_DISABLE_TX(I2S0);

        /* Disable PDMA channel */
        PDMA->PAUSE |= (1 << PDMA_I2S_TX_CH);
        printf("Stop Play ...\n");

        /* Reset some variables */
        u32BufPlayIdx = 0;
        u32PlayBufPos = 0;
        u8PDMATxIdx = 0;
        u8AudioPlaying = 0;
        u8TxDataCntInBuffer = 0;

        /* flush PCM buffer */
        memset(PcmPlayBuff, 0, sizeof(PcmPlayBuff));
        TIMER0->CNT = 0x7657;

    }
    else
    {
        /* Disable record hardware/stop record */
        u8RecEn = 0;
        /* Disable I2S Rx function */
        I2S_DISABLE_RXDMA(I2S0);
        I2S_DISABLE_RX(I2S0);

        /* Disable PDMA channel */
        PDMA->PAUSE |= (1 << PDMA_I2S_RX_CH);
        printf("Stop Record ..\n");

        /* Reset some variables */
        u32BufRecIdx = 0;
        u8PDMARxIdx = 0;

        /* flush PCM buffer */
        memset(u8PcmRxBufFull, 0, sizeof(u8PcmRxBufFull));
    }
}


/**
  * @brief  GetPlayData, To get data from ISO OUT to play buffer.
  * @param  pi16src: The data buffer of ISO OUT.
  *         i16Samples: The sample number in data buffer.
  * @retval None.
  */
void UAC_GetPlayData(uint8_t *psrc, uint32_t u32Samples)
{
    uint32_t i, u32len;
    uint32_t *pBuff;
    uint32_t *pSrc;

    /* if buffer has enough data, play it!! */
    if (!u8AudioPlaying && (u8TxDataCntInBuffer >= (PDMA_TXBUFFER_CNT/2+1)))
    {
        AudioStartPlay(g_usbd_SampleRate);
        u8AudioPlaying = 1;
    }

    u32len = u32Samples/4;

    /* Ring buffer check */
    if ((u32PlayBufPos + u32len) > u32BuffLen)
    {
        PcmPlayBuffLen[u32BufPlayIdx] = u32PlayBufPos;
        u32PlayBufPos = 0;
        u32BufPlayIdx ++;

        /* change buffer index */
        if(u32BufPlayIdx >= PDMA_TXBUFFER_CNT)
            u32BufPlayIdx=0;

        /* increase data count in buffer */
        u8TxDataCntInBuffer ++;
    }

    pBuff = &PcmPlayBuff[u32BufPlayIdx][u32PlayBufPos];
    pSrc = (uint32_t *) psrc;
    for ( i = 0; i < u32len; i++ )
    {
        pBuff[i] = pSrc[i];
    }

    u32PlayBufPos += u32len;
}



void AudioStartPlay(uint32_t u32SampleRate)
{
    UAC_DeviceEnable(1);

    /* Configure TX PDMA SG table */
    PDMA_WriteTxSGTable();

    /* Configure codec to specific sample rate */
#if NAU8822
    NAU8822_ConfigSampleRate(u32SampleRate);
#else
    NAU88L25_ConfigSampleRate(u32SampleRate);
#endif

    /* Enable I2S Tx function */
    I2S_ENABLE_TXDMA(I2S0);
    I2S_ENABLE_TX(I2S0);

    /* Enable PDMA channel */
    PDMA->CHCTL |= (1 << PDMA_I2S_TX_CH);
    printf("Start Play ... \n");

    // workaround for PDMA suspend
    PDMA->DSCT[PDMA_I2S_TX_CH].CTL = 0;
    PDMA->DSCT[PDMA_I2S_TX_CH].CTL = 2;
}


/**
  * @brief  SendRecData, prepare the record data for next ISO transfer.
  * @param  None.
  * @retval None.
  */
void UAC_SendRecData(void)
{
    short *p16Buf;
    short *p16Src;

    /* Get the address in USB buffer */
    p16Buf = (short *)((uint32_t)USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP2));
    p16Src = (short *)(&PcmRecBuff[u32BufRecIdx][0]);

    /* when record buffer full, send data to host */
    if(u8PcmRxBufFull[u32BufRecIdx])
    {
        /* Set empty flag */
        u8PcmRxBufFull[u32BufRecIdx] = 0;

        /* Audio data is resampled to 48MHz (Audio Codec is fixed to 48MHz) */
        /* Do Resample operation to data in USB buffer to SRAM buffer */
        if(REC_CHANNELS == 2)
        {
            Resamples(E_RS_REC_CH0, p16Src, REC_CHANNELS, srt[g_resample_rec_s_idx].count, g_a16AudioTmpBuf0, g_resample_rec_s_idx);
            Resamples(E_RS_REC_CH1, &p16Src[1], REC_CHANNELS, srt[g_resample_rec_s_idx].count, &g_a16AudioTmpBuf0[1], g_resample_rec_s_idx);
        }
        else
            Resamples(E_RS_REC_CH0, p16Src, REC_CHANNELS, srt[g_resample_rec_s_idx].count, g_a16AudioTmpBuf0, g_resample_rec_s_idx);

        USBD_MemCopy((uint8_t *)p16Buf, (uint8_t *)g_a16AudioTmpBuf0, g_rec_max_packet_size);
        USBD_SET_PAYLOAD_LEN(EP2, g_rec_max_packet_size);

        /* Change to next PCM buffer */
        u32BufRecIdx ++;
        if(u32BufRecIdx >= PDMA_RXBUFFER_CNT)
            u32BufRecIdx=0;
    }
    else
    {
        USBD_SET_PAYLOAD_LEN(EP2, 0);
    }
}

void AudioStartRecord(uint32_t u32SampleRate)
{
    /* Configure RX PDMA SG table */
    PDMA_WriteRxSGTable();

    /* Configure codec to specific sample rate */
#if NAU8822
    NAU8822_ConfigSampleRate(u32SampleRate);
#else
    NAU88L25_ConfigSampleRate(u32SampleRate);
#endif

    /* Enable I2S Tx function */
    I2S_ENABLE_RXDMA(I2S0);
    I2S_ENABLE_RX(I2S0);

    /* Enable PDMA channel */
    PDMA->CHCTL |= (1 << PDMA_I2S_RX_CH);
    printf("Start Record ... \n");

    PDMA->DSCT[PDMA_I2S_RX_CH].CTL = 0;
    PDMA->DSCT[PDMA_I2S_RX_CH].CTL = 2;
}


//======================================================
void TMR0_IRQHandler(void)
{
    TIMER_ClearIntFlag(TIMER0);

    if(u8PlayEn)
    {
        if((u8TxDataCntInBuffer >= (PDMA_TXBUFFER_CNT/2)) && (u8TxDataCntInBuffer <= (PDMA_TXBUFFER_CNT/2+1)))
            AdjustCodecPll(E_RS_NONE);
        else if(u8TxDataCntInBuffer >= (PDMA_TXBUFFER_CNT-2))
            AdjustCodecPll(E_RS_UP);
        else
            AdjustCodecPll(E_RS_DOWN);
    }
}




