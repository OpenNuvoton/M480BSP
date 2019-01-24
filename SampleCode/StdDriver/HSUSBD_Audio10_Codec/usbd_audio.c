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

uint32_t g_usbd_SampleRate = AUDIO_RATE;
/*--------------------------------------------------------------------------*/
static volatile uint8_t bPlayVolumeLAdjust = FALSE;
static volatile uint8_t bPlayVolumeRAdjust = FALSE;


/*--------------------------------------------------------------------------*/
/* Global variables for Audio class */
uint32_t g_usbd_UsbAudioState = 0;

uint8_t  g_usbd_RecMute = 0x01;
int16_t  g_usbd_RecVolume = 0x1000;
int16_t  g_usbd_RecMaxVolume = 0x7FFF;
int16_t  g_usbd_RecMinVolume = 0x8000;
int16_t  g_usbd_RecResVolume = 0x400;

uint8_t  g_usbd_PlayMute = 0x01;
int16_t  g_usbd_PlayVolumeL = 0x1000;
int16_t  g_usbd_PlayVolumeR = 0x1000;
int16_t  g_usbd_PlayMaxVolume = 0x7FFF;
int16_t  g_usbd_PlayMinVolume = 0x8000;
int16_t  g_usbd_PlayResVolume = 0x400;

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
#else
uint32_t PcmPlayBuff[PDMA_TXBUFFER_CNT][BUFF_LEN] __attribute__((aligned(4))) = {0};
uint32_t PcmPlayBuffLen[PDMA_TXBUFFER_CNT] __attribute__((aligned(4))) = {0};

uint8_t PcmRecBuff[PDMA_RXBUFFER_CNT][BUFF_LEN] __attribute__((aligned(4))) = {0};
uint8_t u8PcmRxBufFull[PDMA_RXBUFFER_CNT] __attribute__((aligned(4))) = {0};
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
        HSUSBD_CLR_EP_INT_FLAG(EPC, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPDIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPD].EPINTSTS & HSUSBD->EP[EPD].EPINTEN;
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
    HSUSBD_ENABLE_USB_INT(HSUSBD_GINTEN_USBIEN_Msk|HSUSBD_GINTEN_CEPIEN_Msk|HSUSBD_GINTEN_EPAIEN_Msk|HSUSBD_GINTEN_EPBIEN_Msk);
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
            if ((gUsbCmd.bmRequestType & 0x0f) == 0x2)
            {
                /* request to endpoint */
                HSUSBD_PrepareCtrlIn((uint8_t *)&g_usbd_SampleRate, gUsbCmd.wLength);
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_INTKIEN_Msk);
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
                        HSUSBD_PrepareCtrlIn((uint8_t *)&g_usbd_RecVolume, 2);

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
            if ((gUsbCmd.bmRequestType & 0x0f) == 0x2)
            {
                /* request to endpoint */
                HSUSBD_CtrlOut((uint8_t *)&g_usbd_SampleRate, gUsbCmd.wLength);
                if (u8RecEn)
                {
                    UAC_DeviceDisable(0);
                    AudioStartRecord(g_usbd_SampleRate);
                }

                /* Status stage */
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);
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
                            if(g_usbd_PlayVolumeL & 0x8000)
                                g_usbd_PlayVolumeL = (g_usbd_PlayVolumeL & 0x7FFF) >> 8;
                            else
                                g_usbd_PlayVolumeL = (g_usbd_PlayVolumeL >> 7);
                            bPlayVolumeLAdjust = TRUE;
                        }
                        else
                        {
                            HSUSBD_CtrlOut((uint8_t *)&g_usbd_PlayVolumeR, gUsbCmd.wLength);
                            if(g_usbd_PlayVolumeR & 0x8000)
                                g_usbd_PlayVolumeR = (g_usbd_PlayVolumeR & 0x7FFF) >> 8;
                            else
                                g_usbd_PlayVolumeR = (g_usbd_PlayVolumeR >> 7);
                            bPlayVolumeRAdjust = TRUE;
                        }
                    }
                    if (REC_FEATURE_UNITID == ((gUsbCmd.wIndex >> 8) & 0xff))
                        HSUSBD_CtrlOut((uint8_t *)&g_usbd_RecVolume, gUsbCmd.wLength);
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

        printf("Stop Play ...\n");

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
        printf("Stop Record .. \n");

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
    volatile uint32_t u32len, tmp;

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
    tmp = u32len >> 2;  /* byte to word */

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

    /* active usbd DMA to read data from FIFO and then send to I2S */
    HSUSBD_SET_DMA_WRITE(ISO_OUT_EP_NUM);
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_DMADONEIEN_Msk|HSUSBD_BUSINTEN_SUSPENDIEN_Msk|HSUSBD_BUSINTEN_RSTIEN_Msk|HSUSBD_BUSINTEN_VBUSDETIEN_Msk);
    HSUSBD_SET_DMA_ADDR((uint32_t)&PcmPlayBuff[u32BufPlayIdx][u32PlayBufPos]);
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
    uint32_t volatile i;
    uint32_t *pBuff;

    /* when record buffer full, send data to host */
    if(u8PcmRxBufFull[u32BufRecIdx])
    {
        if (HSUSBD->DMACTL & HSUSBD_DMACTL_DMAEN_Msk)
            return;

        /* Set empty flag */
        u8PcmRxBufFull[u32BufRecIdx] = 0;

        pBuff = (uint32_t *)&PcmRecBuff[u32BufRecIdx][0];

        /* active usbd DMA to read data to FIFO and then send to host */
        HSUSBD_SET_DMA_READ(ISO_IN_EP_NUM);
        HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_DMADONEIEN_Msk|HSUSBD_BUSINTEN_SUSPENDIEN_Msk|HSUSBD_BUSINTEN_RSTIEN_Msk|HSUSBD_BUSINTEN_VBUSDETIEN_Msk);
        HSUSBD_SET_DMA_ADDR((uint32_t)pBuff);
        HSUSBD_SET_DMA_LEN(u32RxBuffLen);
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
        {
            AdjustCodecPll(E_RS_UP);
        }
        else
        {
            AdjustCodecPll(E_RS_DOWN);
        }
    }
}




