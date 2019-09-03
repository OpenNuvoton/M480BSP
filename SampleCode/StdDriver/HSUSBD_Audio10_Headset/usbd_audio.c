/***************************************************************************//**
 * @file     usbd_audio.c
 * @brief    NuMicro series HSUSBD driver Sample file
 * @version  1.0.0
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
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
uint8_t volatile g_usbd_txflag=0;
uint8_t volatile g_usbd_rxflag=0;

uint32_t volatile u32BuffLen = 0, u32RxBuffLen = 0;

/* Player Buffer and its pointer */
#ifdef __ICCARM__
#pragma data_alignment=4
uint32_t PcmPlayBuff[PDMA_TXBUFFER_CNT][BUFF_LEN] = {0};
uint32_t PcmPlayBuffLen[PDMA_TXBUFFER_CNT] = {0};

uint8_t PcmRecBuff[PDMA_RXBUFFER_CNT][BUFF_LEN] = {0};
uint8_t u8PcmRxBufFull[PDMA_RXBUFFER_CNT] = {0};

uint32_t g_au32UsbTmpBuf[AUDIO_RATE_96K * 2 * PLAY_CHANNELS / 1000 / 4 + 16] = {0};
uint32_t g_au32UsbTmpBuf1[AUDIO_RATE_96K * 2 * PLAY_CHANNELS / 1000 / 4 + 16] = {0};
short g_a16AudioTmpBuf0[REC_RATE * 2 * REC_CHANNELS / 1000 + 16] = {0};
#else
uint32_t PcmPlayBuff[PDMA_TXBUFFER_CNT][BUFF_LEN] __attribute__((aligned(4))) = {0};
uint32_t PcmPlayBuffLen[PDMA_TXBUFFER_CNT] __attribute__((aligned(4))) = {0};

uint8_t PcmRecBuff[PDMA_RXBUFFER_CNT][BUFF_LEN] __attribute__((aligned(4))) = {0};
uint8_t u8PcmRxBufFull[PDMA_RXBUFFER_CNT] __attribute__((aligned(4))) = {0};

uint32_t g_au32UsbTmpBuf[AUDIO_RATE_96K * 2 * PLAY_CHANNELS / 1000 / 4 + 16] __attribute__((aligned(4))) = {0};
uint32_t g_au32UsbTmpBuf1[AUDIO_RATE_96K * 2 * PLAY_CHANNELS / 1000 / 4 + 16] __attribute__((aligned(4))) = {0};
short g_a16AudioTmpBuf0[REC_RATE * 2 * REC_CHANNELS / 1000 + 16] __attribute__((aligned(4))) = {0};
#endif

/* Player Buffer and its pointer */
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
void USBD20_IRQHandler(void)
{
    __IO uint32_t IrqStL, IrqSt;

    IrqStL = HSUSBD->GINTSTS & HSUSBD->GINTEN;    /* get interrupt status */

    if (!IrqStL)    return;

    /* USB Bus interrupt */
    if (IrqStL & HSUSBD_GINTSTS_USBIF_Msk)
    {
        IrqSt = HSUSBD->BUSINTSTS & HSUSBD->BUSINTEN;

        if (IrqSt & HSUSBD_BUSINTSTS_SOFIF_Msk)
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_SOFIF_Msk);

        if (IrqSt & HSUSBD_BUSINTSTS_RSTIF_Msk)
        {
            HSUSBD_SwReset();
            HSUSBD_ResetDMA();
            u8TxDataCntInBuffer = u8RxDataCntInBuffer = 0;

            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
            HSUSBD_SET_ADDR(0);
            HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RSTIEN_Msk|HSUSBD_BUSINTEN_RESUMEIEN_Msk|HSUSBD_BUSINTEN_SUSPENDIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_RSTIF_Msk);
            HSUSBD_CLR_CEP_INT_FLAG(0x1ffc);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_RESUMEIF_Msk)
        {
            HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RSTIEN_Msk|HSUSBD_BUSINTEN_SUSPENDIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_RESUMEIF_Msk);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_SUSPENDIF_Msk)
        {
            HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RSTIEN_Msk | HSUSBD_BUSINTEN_RESUMEIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_SUSPENDIF_Msk);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_HISPDIF_Msk)
        {
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_HISPDIF_Msk);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_DMADONEIF_Msk)
        {
            g_hsusbd_DmaDone = 1;
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_DMADONEIF_Msk);

            if (!(HSUSBD->DMACTL & HSUSBD_DMACTL_DMARD_Msk))
            {
                HSUSBD_ENABLE_EP_INT(EPB, HSUSBD_EPINTEN_RXPKIEN_Msk);
            }

            if (HSUSBD->DMACTL & HSUSBD_DMACTL_DMARD_Msk)
            {
                if (g_hsusbd_ShortPacket == 1)
                {
                    HSUSBD->EP[EPA].EPRSPCTL = HSUSBD_EP_RSPCTL_SHORTTXEN;    // packet end
                    g_hsusbd_ShortPacket = 0;
                }
            }
        }

        if (IrqSt & HSUSBD_BUSINTSTS_PHYCLKVLDIF_Msk)
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_PHYCLKVLDIF_Msk);

        if (IrqSt & HSUSBD_BUSINTSTS_VBUSDETIF_Msk)
        {
            if (HSUSBD_IS_ATTACHED())
            {
                /* USB Plug In */
                HSUSBD_ENABLE_USB();
            }
            else
            {
                /* USB Un-plug */
                HSUSBD_DISABLE_USB();
            }
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_VBUSDETIF_Msk);
        }
    }

    /* Control endpoint interrupt */
    if (IrqStL & HSUSBD_GINTSTS_CEPIF_Msk)
    {
        IrqSt = HSUSBD->CEPINTSTS & HSUSBD->CEPINTEN;

        if (IrqSt & HSUSBD_CEPINTSTS_SETUPTKIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_SETUPTKIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_SETUPPKIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_SETUPPKIF_Msk);
            HSUSBD_ProcessSetupPacket();
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_OUTTKIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_OUTTKIF_Msk);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_INTKIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
            if (!(IrqSt & HSUSBD_CEPINTSTS_STSDONEIF_Msk))
            {
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_TXPKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_TXPKIEN_Msk);
                HSUSBD_CtrlIn();
            }
            else
            {
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_TXPKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_TXPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            }
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_PINGIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_PINGIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_TXPKIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
            if (g_hsusbd_CtrlInSize)
            {
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_INTKIEN_Msk);
            }
            else
            {
                if (g_hsusbd_CtrlZero == 1)
                    HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_ZEROLEN);
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            }
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_TXPKIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_RXPKIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_RXPKIF_Msk);
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_NAKIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_NAKIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_STALLIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STALLIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_ERRIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_ERRIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_STSDONEIF_Msk)
        {
            HSUSBD_UpdateDeviceState();
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_BUFFULLIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_BUFFULLIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_BUFEMPTYIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_BUFEMPTYIF_Msk);
            return;
        }
    }

    /* Non-control endpoint interrupt */
    if (IrqStL & HSUSBD_GINTSTS_EPAIF_Msk)
    {
        /* Isochronous in */
        IrqSt = HSUSBD->EP[EPA].EPINTSTS & HSUSBD->EP[EPA].EPINTEN;

        EPA_Handler();
        HSUSBD_CLR_EP_INT_FLAG(EPA, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPBIF_Msk)
    {
        /* Isochronous out */
        IrqSt = HSUSBD->EP[EPB].EPINTSTS & HSUSBD->EP[EPB].EPINTEN;

        EPB_Handler();
        HSUSBD_CLR_EP_INT_FLAG(EPB, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPCIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPC].EPINTSTS & HSUSBD->EP[EPC].EPINTEN;
#ifdef __FEEDBACK__
        /* Isochronous IN for Feedback */
        EPC_Handler();
#endif
        HSUSBD_CLR_EP_INT_FLAG(EPC, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPDIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPD].EPINTSTS & HSUSBD->EP[EPD].EPINTEN;
#ifdef __HID__
        HSUSBD_ENABLE_EP_INT(EPD, 0);
        EPD_Handler();
#endif
        HSUSBD_CLR_EP_INT_FLAG(EPD, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPEIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPE].EPINTSTS & HSUSBD->EP[EPE].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPE, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPFIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPF].EPINTSTS & HSUSBD->EP[EPF].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPF, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPGIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPG].EPINTSTS & HSUSBD->EP[EPG].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPG, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPHIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPH].EPINTSTS & HSUSBD->EP[EPH].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPH, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPIIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPI].EPINTSTS & HSUSBD->EP[EPI].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPI, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPJIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPJ].EPINTSTS & HSUSBD->EP[EPJ].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPJ, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPKIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPK].EPINTSTS & HSUSBD->EP[EPK].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPK, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPLIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPL].EPINTSTS & HSUSBD->EP[EPL].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPL, IrqSt);
    }
}

/**
 * @brief       EPA Handler
 *
 * @param[in]   None
 *
 * @return      None
 *
 * @details     This function is used to process EPA event
 */
/* Record */
void EPA_Handler(void)
{
    if (HSUSBD->EP[EPA].EPINTSTS & HSUSBD_EPINTSTS_TXPKIF_Msk)
    {
        g_usbd_txflag = 1;
    }
}

/**
 * @brief       EPB Handler
 *
 * @param[in]   None
 *
 * @return      None
 *
 * @details     This function is used to process EPB event
 */
/* Play */
void EPB_Handler(void)
{
    if (HSUSBD->EP[EPB].EPINTSTS & HSUSBD_EPINTSTS_RXPKIF_Msk)
    {
        g_usbd_rxflag = 1;
    }
}

#ifdef __FEEDBACK__
/**
 * @brief       EPC Handler (Iso IN feedback interrupt handler)
 *
 * @param[in]   None
 *
 * @return      None
 *
 */
void EPC_Handler(void)
{
    if (u8AudioPlaying)
    {
        if ((u8TxDataCntInBuffer >= (PDMA_TXBUFFER_CNT/2)) && (u8TxDataCntInBuffer <= (PDMA_TXBUFFER_CNT/2+1)))
        {
            g_u32SampleRate = g_play_len_frame;
        }
        else if (u8TxDataCntInBuffer >= (PDMA_TXBUFFER_CNT-2))
        {
            g_u32SampleRate = g_play_len_frame - 3;
        }
        else
        {
            g_u32SampleRate = g_play_len_frame + 3;
        }
    }
    /* Prepare the data to USB IN buffer */
    HSUSBD->EP[EPC].EPDAT_BYTE = 0x00;
    HSUSBD->EP[EPC].EPDAT_BYTE = (g_u32SampleRate & 0x3) << 6;
    HSUSBD->EP[EPC].EPDAT_BYTE = (g_u32SampleRate & 0xFC) >> 2;
    HSUSBD->EP[EPC].EPTXCNT = 3;
}
#endif

#ifdef __HID__
void EPD_Handler(void)  /* Interrupt IN handler */
{
    g_u8EPDReady = 1;
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
    if ((g_usbd_SampleRate % 8000) == 0)
    {
        u32BuffLen = 768;
        u32RxBuffLen = 768;
    }
    else
    {
        u32BuffLen = 441;
        u32RxBuffLen = 444;
    }

    /* Configure USB controller */
    HSUSBD->OPER = 0; /* Full Speed */
    /* Enable USB BUS, CEP and EPA , EPB global interrupt */
    HSUSBD_ENABLE_USB_INT(HSUSBD_GINTEN_USBIEN_Msk|HSUSBD_GINTEN_CEPIEN_Msk|HSUSBD_GINTEN_EPAIEN_Msk|HSUSBD_GINTEN_EPBIEN_Msk|
                          HSUSBD_GINTEN_EPCIEN_Msk|HSUSBD_GINTEN_EPDIEN_Msk|HSUSBD_GINTEN_EPEIEN_Msk);

    /* Enable BUS interrupt */
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_DMADONEIEN_Msk|HSUSBD_BUSINTEN_RESUMEIEN_Msk|HSUSBD_BUSINTEN_RSTIEN_Msk|HSUSBD_BUSINTEN_VBUSDETIEN_Msk);
    /* Reset Address to 0 */
    HSUSBD_SET_ADDR(0);

    /*****************************************************/
    /* Control endpoint */
    HSUSBD_SetEpBufAddr(CEP, CEP_BUF_BASE, CEP_BUF_LEN);
    HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);

    /*****************************************************/
    /* EPA ==> ISO IN endpoint, address 1 */
    HSUSBD_SetEpBufAddr(EPA, EPA_BUF_BASE, EPA_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPA, EPA_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPA, ISO_IN_EP_NUM, HSUSBD_EP_CFG_TYPE_ISO, HSUSBD_EP_CFG_DIR_IN);
    HSUSBD_ENABLE_EP_INT(EPA, HSUSBD_EPINTEN_TXPKIEN_Msk);

    /* EPB ==> ISO OUT endpoint, address 2 */
    HSUSBD_SetEpBufAddr(EPB, EPB_BUF_BASE, EPB_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPB, EPB_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPB, ISO_OUT_EP_NUM, HSUSBD_EP_CFG_TYPE_ISO, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPB, HSUSBD_EPINTEN_RXPKIEN_Msk|HSUSBD_EPINTEN_SHORTRXIEN_Msk);

#ifdef __FEEDBACK__
    /*****************************************************/
    /* EPC ==> Isochronous IN endpoint, address 3 */
    HSUSBD_SetEpBufAddr(EPC, EPC_BUF_BASE, EPC_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPC, EPC_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPC, ISO_IN_FB_EP_NUM, HSUSBD_EP_CFG_TYPE_ISO, HSUSBD_EP_CFG_DIR_IN);
    HSUSBD_ENABLE_EP_INT(EPC, HSUSBD_EPINTEN_TXPKIEN_Msk);

    g_u32SampleRate = PLAY_RATE/1000;
#endif
#ifdef __HID__
    /*****************************************************/
    /* EPD ==> Interrupt IN endpoint, address 4 */
    HSUSBD_SetEpBufAddr(EPD, EPD_BUF_BASE, EPD_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPD, EPD_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPD, HID_IN_EP_NUM, HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_IN);

    g_u8EPDReady = 1;
#endif
#ifdef __FEEDBACK__
    /* Feedback Endpoint */
    g_u32SampleRate = g_usbd_PlaySampleRate / 1000;
    g_play_len_frame = g_usbd_PlaySampleRate / 1000;

    /* Prepare the data to USB IN buffer */
    HSUSBD->EP[EPC].EPDAT_BYTE = 0x00;
    HSUSBD->EP[EPC].EPDAT_BYTE = (g_u32SampleRate & 0x3) << 6;
    HSUSBD->EP[EPC].EPDAT_BYTE = (g_u32SampleRate & 0xFC) >> 2;
    HSUSBD->EP[EPC].EPTXCNT = 3;
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
#ifdef __HID__
    static uint8_t u8Protocol = 0;
    static uint8_t u8Idle = 0;
#endif
    if (gUsbCmd.bmRequestType & 0x80)
    {
        /* request data transfer direction */
        /* Get Feature Unit Control Request */
        // Device to host
        switch (gUsbCmd.bRequest)
        {
        /* Get current setting attribute */
        case UAC_GET_CUR:
        {
            /* request to endpoint */
            if((gUsbCmd.wIndex & 0x0F) == ISO_IN_EP_NUM)
            {
                HSUSBD_PrepareCtrlIn((uint8_t *)&g_usbd_RecSampleRate, gUsbCmd.wLength);
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_INTKIEN_Msk);
                break;
            }
            else if((gUsbCmd.wIndex & 0x0F) == ISO_OUT_EP_NUM)
            {
                HSUSBD_PrepareCtrlIn((uint8_t *)&g_usbd_PlaySampleRate, gUsbCmd.wLength);
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_INTKIEN_Msk);
                break;
            }
            else
            {
                /* request to interface */
                switch ((gUsbCmd.wValue & 0xff00) >> 8)
                {
                /* Mute Control */
                case MUTE_CONTROL:
                {
                    if (PLAY_FEATURE_UNITID == ((gUsbCmd.wIndex >> 8) & 0xff))
                        HSUSBD_PrepareCtrlIn((uint8_t *)&g_usbd_PlayMute, 1);

                    if (REC_FEATURE_UNITID == ((gUsbCmd.wIndex >> 8) & 0xff))
                        HSUSBD_PrepareCtrlIn((uint8_t *)&g_usbd_RecMute, 1);

                    HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                    HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_INTKIEN_Msk);
                    break;
                }
                /* Volume Control */
                case VOLUME_CONTROL:
                {
                    if (PLAY_FEATURE_UNITID == ((gUsbCmd.wIndex >> 8) & 0xff))
                    {
                        if((gUsbCmd.wValue & 0xff) == 1)
                            HSUSBD_PrepareCtrlIn((uint8_t *)&g_usbd_PlayVolumeL, 2);
                        else
                            HSUSBD_PrepareCtrlIn((uint8_t *)&g_usbd_PlayVolumeR, 2);
                    }

                    if (REC_FEATURE_UNITID == ((gUsbCmd.wIndex >> 8) & 0xff))
                    {
                        if((gUsbCmd.wValue & 0xff) == 1)
                            HSUSBD_PrepareCtrlIn((uint8_t *)&g_usbd_RecVolumeL, 2);
                        else
                            HSUSBD_PrepareCtrlIn((uint8_t *)&g_usbd_RecVolumeR, 2);
                    }

                    HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                    HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_INTKIEN_Msk);
                    break;
                }
                default:
                    /* Setup error, stall the device */
                    HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
                }
            }
            break;
        }

        /* Get Minimum setting attribute */
        case UAC_GET_MIN:
        {
            switch ((gUsbCmd.wValue & 0xff00) >> 8)
            {
            /* Volume Control */
            case VOLUME_CONTROL:
            {
                if (PLAY_FEATURE_UNITID == ((gUsbCmd.wIndex >> 8) & 0xff))
                    HSUSBD_PrepareCtrlIn((uint8_t *)&g_usbd_PlayMinVolume, 2);

                if (REC_FEATURE_UNITID == ((gUsbCmd.wIndex >> 8) & 0xff))
                    HSUSBD_PrepareCtrlIn((uint8_t *)&g_usbd_RecMinVolume, 2);

                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_INTKIEN_Msk);
                break;
            }
            default:
                /* STALL control pipe */
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
            }
            break;
        }

        /* Get Maximum setting attribute */
        case UAC_GET_MAX:
        {
            switch ((gUsbCmd.wValue & 0xff00) >> 8)
            {
            /* Volume Control */
            case VOLUME_CONTROL:
            {
                if (PLAY_FEATURE_UNITID == ((gUsbCmd.wIndex >> 8) & 0xff))
                    HSUSBD_PrepareCtrlIn((uint8_t *)&g_usbd_PlayMaxVolume, 2);
                if (REC_FEATURE_UNITID == ((gUsbCmd.wIndex >> 8) & 0xff))
                    HSUSBD_PrepareCtrlIn((uint8_t *)&g_usbd_RecMaxVolume, 2);
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_INTKIEN_Msk);
                break;
            }
            default:
                /* STALL control pipe */
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
            }
            break;
        }

        /* Get Resolution attribute */
        case UAC_GET_RES:
        {
            switch ((gUsbCmd.wValue & 0xff00) >> 8)
            {
            /* Volume Control */
            case VOLUME_CONTROL:
            {
                if (PLAY_FEATURE_UNITID == ((gUsbCmd.wIndex >> 8) & 0xff))
                    HSUSBD_PrepareCtrlIn((uint8_t *)&g_usbd_PlayResVolume, 2);
                if (REC_FEATURE_UNITID == ((gUsbCmd.wIndex >> 8) & 0xff))
                    HSUSBD_PrepareCtrlIn((uint8_t *)&g_usbd_RecResVolume, 2);
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_INTKIEN_Msk);
                break;
            }
            default:
                /* STALL control pipe */
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
            }
            break;
        }

#ifdef __HID__
//         case GET_REPORT:
//         {
//             break;
//         }
        case GET_IDLE:
        {
            HSUSBD_PrepareCtrlIn((uint8_t *)&u8Idle, 1);
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_INTKIEN_Msk);
            break;
        }
        case GET_PROTOCOL:
        {
            HSUSBD_PrepareCtrlIn((uint8_t *)&u8Protocol, 1);
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_INTKIEN_Msk);
            break;
        }
#endif
        default:
            /* Setup error, stall the device */
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
        }
    }
    else
    {
        // Host to device
        switch (gUsbCmd.bRequest)
        {
        /* Set Current setting attribute */
        case UAC_SET_CUR:
        {
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_OUTTKIEN_Msk | HSUSBD_CEPINTEN_RXPKIEN_Msk);
            /* request to endpoint */
            if((gUsbCmd.wIndex & 0x0F) == ISO_IN_EP_NUM)
            {
                HSUSBD_CtrlOut((uint8_t *)&g_usbd_RecSampleRate, gUsbCmd.wLength);
                /* Status stage */
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);
                break;
            }
            else if((gUsbCmd.wIndex & 0x0F) == ISO_OUT_EP_NUM)
            {
                HSUSBD_CtrlOut((uint8_t *)&g_usbd_PlaySampleRate, gUsbCmd.wLength);
                /* Status stage */
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);
                break;
            }
            else
            {
                /* request to interface */
                switch ((gUsbCmd.wValue & 0xff00) >> 8)
                {
                /* Mute Control */
                case MUTE_CONTROL:
                    if (PLAY_FEATURE_UNITID == ((gUsbCmd.wIndex >> 8) & 0xff))
                        HSUSBD_CtrlOut((uint8_t *)&g_usbd_PlayMute, gUsbCmd.wLength);
                    if (REC_FEATURE_UNITID == ((gUsbCmd.wIndex >> 8) & 0xff))
                        HSUSBD_CtrlOut((uint8_t *)&g_usbd_RecMute, gUsbCmd.wLength);

                    /* Status stage */
                    HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
                    HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
                    HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);
                    break;

                /* Volume Control */
                case VOLUME_CONTROL:
                    if (PLAY_FEATURE_UNITID == ((gUsbCmd.wIndex >> 8) & 0xff))
                    {
                        if (((gUsbCmd.wValue >> 8) & 0xff) == 1)
                        {
                            HSUSBD_CtrlOut((uint8_t *)&g_usbd_PlayVolumeL, gUsbCmd.wLength);
                        }
                        else
                        {
                            HSUSBD_CtrlOut((uint8_t *)&g_usbd_PlayVolumeR, gUsbCmd.wLength);
                        }
                    }
                    if (REC_FEATURE_UNITID == ((gUsbCmd.wIndex >> 8) & 0xff))
                    {
                        if (((gUsbCmd.wValue >> 8) & 0xff) == 1)
                        {
                            HSUSBD_CtrlOut((uint8_t *)&g_usbd_RecVolumeL, gUsbCmd.wLength);
                        }
                        else
                        {
                            HSUSBD_CtrlOut((uint8_t *)&g_usbd_RecVolumeR, gUsbCmd.wLength);
                        }
                    }
                    /* Status stage */
                    HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
                    HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
                    HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);
                    break;

                default:
                    /* STALL control pipe */
                    HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
                    break;
                }
            }
            break;
        }

#ifdef __HID__
        case SET_REPORT:
        {
            if (((gUsbCmd.wValue >> 8) & 0xff) == 3)
            {
                /* Request Type = Feature */
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            }
            break;
        }
        case SET_IDLE:
        {
            /* Status stage */
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            break;
        }
        case SET_PROTOCOL:
#endif
        default:
        {
            /* Setup error, stall the device */
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
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
    if ((gUsbCmd.wIndex & 0xff) == 2)
    {
        /* Audio ISO OUT interface */
        if (u32AltInterface == 0)
            UAC_DeviceDisable(1);    /* stop play */
        else
            UAC_DeviceEnable(1);     /* start play */
    }

    if ((gUsbCmd.wIndex & 0xff) == 1)
    {
        /* Audio ISO IN interface */
        if (u32AltInterface == 1)   /* Start Record */
        {
            g_usbd_UsbAudioState = UAC_START_AUDIO_RECORD;
            HSUSBD->EP[EPA].EPRSPCTL = HSUSBD_EPRSPCTL_ZEROLEN_Msk;
            UAC_DeviceEnable(0);
            g_usbd_txflag = 1;
        }
        else if (u32AltInterface == 0)     /* Stop Record */
        {
            UAC_DeviceDisable(0);
            HSUSBD->EP[EPA].EPRSPCTL = HSUSBD_EPRSPCTL_ZEROLEN_Msk;
            g_usbd_UsbAudioState = UAC_STOP_AUDIO_RECORD;
        }
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
            AudioStartRecord(g_usbd_SampleRate);

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

        //printf("Stop Play ...\n");

        /* Reset some variables */
        u32BufPlayIdx = 0;
        u32PlayBufPos = 0;
        u8PDMATxIdx = 0;
        u8AudioPlaying = 0;
        u8TxDataCntInBuffer = 0;

        /* flush PCM buffer */
        memset(PcmPlayBuff, 0, sizeof(PcmPlayBuff));

        /* stop usbd dma and flush FIFO */
        HSUSBD_ResetDMA();
        g_hsusbd_DmaDone = 1;
        HSUSBD->EP[EPB].EPRSPCTL |= HSUSBD_EPRSPCTL_FLUSH_Msk;
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
        //printf("Stop Record .. \n");

        /* Reset some variables */
        u32BufRecIdx = 0;
        u8PDMARxIdx = 0;
        u8RxDataCntInBuffer = 0;

        /* flush PCM buffer */
        memset(u8PcmRxBufFull, 0, sizeof(u8PcmRxBufFull));

        /* stop usbd dma and flush FIFO */
        HSUSBD_ResetDMA();
        g_hsusbd_DmaDone = 1;
        HSUSBD->EP[EPA].EPRSPCTL |= HSUSBD_EPRSPCTL_FLUSH_Msk;
    }
}


/**
  * @brief  GetPlayData, To get data from ISO OUT to play buffer.
  * @param  None.
  * @retval None.
  */
void UAC_GetPlayData(void)
{
    volatile uint32_t u32len, tmp, u32Samples = 0;
    short *pu16Buf;
    short *p16Src;

    /* if buffer has enough data, play it!! */
    if (!u8AudioPlaying && (u8TxDataCntInBuffer >= (PDMA_TXBUFFER_CNT/2+1)))
    {
        AudioStartPlay(g_usbd_SampleRate);
        u8AudioPlaying = 1;
    }

    if (HSUSBD->DMACTL & HSUSBD_DMACTL_DMAEN_Msk)
        return;

    // get data from FIFO
    u32len = HSUSBD->EP[EPB].EPDATCNT & 0xffff;

    /* active usbd DMA to read data from FIFO and then send to I2S */
    HSUSBD_SET_DMA_WRITE(ISO_OUT_EP_NUM);
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_DMADONEIEN_Msk|HSUSBD_BUSINTEN_SUSPENDIEN_Msk|HSUSBD_BUSINTEN_RSTIEN_Msk|HSUSBD_BUSINTEN_VBUSDETIEN_Msk);
    HSUSBD_SET_DMA_ADDR((uint32_t)g_au32UsbTmpBuf1);
    HSUSBD_SET_DMA_LEN(u32len);
    g_hsusbd_DmaDone = 0;
    HSUSBD_ENABLE_DMA();

    /* wait usbd dma complete */
    while(1)
    {
        if (g_hsusbd_DmaDone)
            break;

        if (!HSUSBD_IS_ATTACHED())
            break;

        if ((HSUSBD->DMACTL & HSUSBD_DMACTL_DMAEN_Msk) == 0)
            break;
    }

    /* Get the address in USB buffer */
    p16Src = (short *)g_au32UsbTmpBuf1;

    /* Get the temp buffer */
    pu16Buf = (short *)g_au32UsbTmpBuf;

    tmp = u32len >> 2;  /* byte to word */
    /* Audio data is resampled to 48MHz (Audio Codec is fixed to 48MHz) */
    /* Do Resample operation to data in USB buffer to SRAM buffer */
    if(PLAY_CHANNELS == 2)
    {
        u32Samples  = Resamples(E_RS_PLAY_CH0, p16Src, PLAY_CHANNELS, tmp, pu16Buf, g_resample_play_s_idx);

        u32Samples += Resamples(E_RS_PLAY_CH1, &p16Src[1], PLAY_CHANNELS, tmp, &pu16Buf[1], g_resample_play_s_idx);
    }
    else
        u32Samples  = Resamples(E_RS_PLAY_CH0, p16Src, PLAY_CHANNELS, tmp, pu16Buf, g_resample_play_s_idx);

    /* Play Data Length for SAMPLING_RATE */
    tmp = u32Samples >> 1;

    /* Ring buffer check */
    if ((u32PlayBufPos + tmp) > u32BuffLen)
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
    HSUSBD_MemCopy((uint8_t *)&PcmPlayBuff[u32BufPlayIdx][u32PlayBufPos], (uint8_t *)g_au32UsbTmpBuf, (tmp << 2));

    u32PlayBufPos += tmp;
    g_usbd_rxflag = 0;
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
    //printf("Start Play ... \n");

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
    uint32_t volatile i;
    short *p16Src;

    p16Src = (short *)(&PcmRecBuff[u32BufRecIdx][0]);
    /* when record buffer full, send data to host */
    if (u8PcmRxBufFull[u32BufRecIdx])
    {
        if (HSUSBD->DMACTL & HSUSBD_DMACTL_DMAEN_Msk)
            return;

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

        /* active usbd DMA to read data to FIFO and then send to host */
        HSUSBD_SET_DMA_READ(ISO_IN_EP_NUM);
        HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_DMADONEIEN_Msk|HSUSBD_BUSINTEN_SUSPENDIEN_Msk|HSUSBD_BUSINTEN_RSTIEN_Msk|HSUSBD_BUSINTEN_VBUSDETIEN_Msk);
        HSUSBD_SET_DMA_ADDR((uint32_t)g_a16AudioTmpBuf0);
        HSUSBD_SET_DMA_LEN(g_rec_max_packet_size);
        g_hsusbd_DmaDone = 0;
        HSUSBD_ENABLE_DMA();

        /* Change to next PCM buffer */
        u32BufRecIdx ++;
        if(u32BufRecIdx >= PDMA_RXBUFFER_CNT)
            u32BufRecIdx=0;
        if (u8RxDataCntInBuffer > 0)
            u8RxDataCntInBuffer --;

        /* wait usbd dma complete */
        while(1)
        {
            if (g_hsusbd_DmaDone)
                break;

            if (!HSUSBD_IS_ATTACHED())
                break;
        }

        g_usbd_txflag = 0;
    }
    else     /* send zero packet when no data*/
    {
        u8RxDataCntInBuffer = 0;
        HSUSBD->EP[EPA].EPRSPCTL = HSUSBD_EPRSPCTL_ZEROLEN_Msk;
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
    //printf("Start Record ... \n");

    PDMA->DSCT[PDMA_I2S_RX_CH].CTL = 0;
    PDMA->DSCT[PDMA_I2S_RX_CH].CTL = 2;
}


#ifndef __FEEDBACK__
//======================================================
void TMR0_IRQHandler(void)
{
    TIMER_ClearIntFlag(TIMER0);

    if(u8PlayEn)
    {
        if((u8TxDataCntInBuffer >= (PDMA_TXBUFFER_CNT/2)) && (u8TxDataCntInBuffer <= (PDMA_TXBUFFER_CNT/2+1)))
            AdjustCodecPll(E_RS_NONE);
        else if(u8TxDataCntInBuffer >= (PDMA_TXBUFFER_CNT-2))
        {
            AdjustCodecPll(E_RS_UP);
        }
        else
        {
            AdjustCodecPll(E_RS_DOWN);
        }
    }
}
#endif



