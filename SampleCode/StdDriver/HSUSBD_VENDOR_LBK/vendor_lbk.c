/***************************************************************************//**
 * @file     vendor_lbk.c
 * @brief    M480 series USBD Vendor LBK device driver Sample file
 * @version  2.0.0
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

/*!<Includes */
#include <string.h>
#include "NuMicro.h"
#include "vendor_lbk.h"


volatile uint8_t  g_IsHighSpeedMode = 1;
volatile uint8_t  g_IntInDataEmpty = 0;
volatile uint8_t  g_IsoInDataEmpty = 0;
volatile uint8_t  g_IsoOutDataReady = 0;
volatile uint8_t  g_BulkInDataEmpty = 0;
volatile uint8_t  g_BulkOutDataReady = 0;
volatile uint32_t g_DMA_RunMsk = 0;

volatile uint8_t  g_Ctrl_Buff[512];
volatile uint8_t  g_Int_Buff[1024];
volatile uint8_t  g_Bulk_Buff[512];
volatile uint8_t  g_Iso_Buff[1024];

uint32_t g_u32EpAMaxPacketSize;
uint32_t g_u32EpBMaxPacketSize;
uint32_t g_u32EpCMaxPacketSize;
uint32_t g_u32EpDMaxPacketSize;
uint32_t g_u32EpEMaxPacketSize;
uint32_t g_u32EpFMaxPacketSize;

void LBK_InitForHighSpeed(void);
void LBK_InitForFullSpeed(void);
void EPB_Handler(void);


void USBD20_IRQHandler(void)
{
    __IO uint32_t IrqStL, IrqSt;

    IrqStL = HSUSBD->GINTSTS & HSUSBD->GINTEN;    /* get interrupt status */

    if (!IrqStL)    return;

    /* USB interrupt */
    if (IrqStL & HSUSBD_GINTSTS_USBIF_Msk)
    {
        IrqSt = HSUSBD->BUSINTSTS & HSUSBD->BUSINTEN;

        if (IrqSt & HSUSBD_BUSINTSTS_SOFIF_Msk)
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_SOFIF_Msk);

        if (IrqSt & HSUSBD_BUSINTSTS_RSTIF_Msk)
        {
            HSUSBD_SwReset();

            HSUSBD_ResetDMA();
            HSUSBD->EP[EPA].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;
            HSUSBD->EP[EPB].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;
            HSUSBD->EP[EPC].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;
            HSUSBD->EP[EPD].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;
            HSUSBD->EP[EPE].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;
            HSUSBD->EP[EPF].EPRSPCTL = HSUSBD_EPRSPCTL_FLUSH_Msk;

            g_DMA_RunMsk = 0;

            if (HSUSBD->OPER & 0x04)  /* high speed */
                LBK_InitForHighSpeed();
            else                    /* full speed */
                LBK_InitForFullSpeed();
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
            HSUSBD_SET_ADDR(0);
            HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RSTIEN_Msk|HSUSBD_BUSINTEN_RESUMEIEN_Msk|HSUSBD_BUSINTEN_SUSPENDIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_RSTIF_Msk);
            HSUSBD_CLR_CEP_INT_FLAG(0x1ffc);

            printf("#RST\n");
            g_IntInDataEmpty = 1;
            g_IsoInDataEmpty = 1;
            g_IsoOutDataReady = 0;
            g_BulkInDataEmpty = 1;
            g_BulkOutDataReady = 0;
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
            //printf("IRQ, DMACTL = 0x%x\n", HSUSBD->DMACTL);

            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_DMADONEIF_Msk);

            if (HSUSBD->DMACTL & HSUSBD_DMACTL_DMARD_Msk)
            {
                if (g_hsusbd_ShortPacket == 1)
                {
                    printf("DMA IRQ g_hsusbd_ShortPacket==1\n");
                    HSUSBD->EP[EPA].EPRSPCTL = (HSUSBD->EP[EPA].EPRSPCTL & 0x10) | HSUSBD_EP_RSPCTL_SHORTTXEN;    // packet end
                    g_hsusbd_ShortPacket = 0;
                }
            }

            /*
             *  Is this DMA complete interrupt for isochronous-in?
             */
            if ((HSUSBD->DMACTL & 0xf) == ISO_IN_EP_NUM)
                g_DMA_RunMsk &= ~(1<<ISO_IN_EP_NUM);

            /*
             *  Is this DMA complete interrupt for isochronous-out?
             */
            if ((HSUSBD->DMACTL & 0xf) == ISO_OUT_EP_NUM)
                g_DMA_RunMsk &= ~(1<<ISO_OUT_EP_NUM);

            /*
             *  Is this DMA complete interrupt for bulk-in?
             */
            if ((HSUSBD->DMACTL & 0xf) == BULK_IN_EP_NUM)
                g_DMA_RunMsk &= ~(1<<BULK_IN_EP_NUM);

            /*
             *  Is this DMA complete interrupt for bulk-out?
             */
            if ((HSUSBD->DMACTL & 0xf) == BULK_OUT_EP_NUM)
                g_DMA_RunMsk &= ~(1<<BULK_OUT_EP_NUM);
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
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_INTKIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
            if (!(IrqSt & HSUSBD_CEPINTSTS_STSDONEIF_Msk))
            {
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_TXPKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_TXPKIEN_Msk);
                HSUSBD_CtrlIn();
            }
            else
            {
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_TXPKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_TXPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);
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
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_INTKIEN_Msk);
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

    /* interrupt in */
    if (IrqStL & HSUSBD_GINTSTS_EPAIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPA].EPINTSTS & HSUSBD->EP[EPA].EPINTEN;
        if (HSUSBD->EP[EPA].EPINTSTS & 0x02)
            g_IntInDataEmpty = 1;
        HSUSBD_CLR_EP_INT_FLAG(EPA, IrqSt);
    }
    /* interrupt out */
    if (IrqStL & HSUSBD_GINTSTS_EPBIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPB].EPINTSTS & HSUSBD->EP[EPB].EPINTEN;
        if (HSUSBD->EP[EPB].EPINTSTS & 0x01)
            EPB_Handler();
        HSUSBD_CLR_EP_INT_FLAG(EPB, IrqSt);
    }

    if (IrqStL & HSUSBD_GINTSTS_EPCIF_Msk)
    {
        //printf("C: 0x%x, 0x%x\n", HSUSBD->EP[EPC].EPINTSTS, HSUSBD->EP[EPC].EPINTEN);
        IrqSt = HSUSBD->EP[EPC].EPINTSTS & HSUSBD->EP[EPC].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPC, IrqSt);
        g_IsoInDataEmpty = 1;
    }

    if (IrqStL & HSUSBD_GINTSTS_EPDIF_Msk)
    {
        printf("D: 0x%x, 0x%x\n", HSUSBD->EP[EPD].EPINTSTS, HSUSBD->EP[EPD].EPINTEN);
        IrqSt = HSUSBD->EP[EPD].EPINTSTS & HSUSBD->EP[EPD].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPD, IrqSt);
        g_IsoOutDataReady = 1;
    }

    if (IrqStL & HSUSBD_GINTSTS_EPEIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPE].EPINTSTS & HSUSBD->EP[EPE].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPE, IrqSt);
        g_BulkInDataEmpty = 1;
    }

    if (IrqStL & HSUSBD_GINTSTS_EPFIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPF].EPINTSTS & HSUSBD->EP[EPF].EPINTEN;
        HSUSBD_CLR_EP_INT_FLAG(EPF, IrqSt);
        g_BulkOutDataReady = 1;
    }
}

/*
 *  Interrupt-out handler
 */
void EPB_Handler(void)
{
    uint32_t len, i;

    len = HSUSBD->EP[EPB].EPDATCNT & 0xffff;

    for (i = 0; i < len; i++)
        g_Int_Buff[i] = HSUSBD->EP[EPB].EPDAT_BYTE;
}


/*--------------------------------------------------------------------------*/
/**
  * @brief  USBD Endpoint Config.
  * @param  None.
  * @retval None.
  */
void LBK_InitForHighSpeed(void)
{
    g_IsHighSpeedMode = 1;

    /*****************************************************/
    /* EPA ==> Interrupt-in endpoint */
    HSUSBD_SetEpBufAddr(EPA, EPA_BUF_BASE, EPA_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPA, EPA_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPA, INT_IN_EP_NUM, HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_IN);
    //HSUSBD_ENABLE_EP_INT(EPA, HSUSBD_EPINTEN_TXPKIEN_Msk);
    g_u32EpAMaxPacketSize = EPA_MAX_PKT_SIZE;

    /* EPB ==> Interrupt-out endpoint */
    HSUSBD_SetEpBufAddr(EPB, EPB_BUF_BASE, EPB_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPB, EPB_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPB, INT_OUT_EP_NUM, HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPB, HSUSBD_EPINTEN_RXPKIEN_Msk | HSUSBD_EPINTEN_BUFFULLIEN_Msk);
    g_u32EpBMaxPacketSize = EPB_MAX_PKT_SIZE;

    /*****************************************************/
    /* EPC ==> Isochronous-in endpoint */
    HSUSBD_SetEpBufAddr(EPC, EPC_BUF_BASE, EPC_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPC, EPC_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPC, ISO_IN_EP_NUM, HSUSBD_EP_CFG_TYPE_ISO, HSUSBD_EP_CFG_DIR_IN);
    HSUSBD_ENABLE_EP_INT(EPC, HSUSBD_EPINTEN_TXPKIEN_Msk);
    g_u32EpCMaxPacketSize = EPC_MAX_PKT_SIZE;

    /* EPD ==> Isochronous-out endpoint */
    HSUSBD_SetEpBufAddr(EPD, EPD_BUF_BASE, EPD_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPD, EPD_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPD, ISO_OUT_EP_NUM, HSUSBD_EP_CFG_TYPE_ISO, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPD, HSUSBD_EPINTEN_RXPKIEN_Msk);
    g_u32EpDMaxPacketSize = EPD_MAX_PKT_SIZE;

    /*****************************************************/
    /* EPE ==> Bulk-in endpoint */
    HSUSBD_SetEpBufAddr(EPE, EPE_BUF_BASE, EPE_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPE, EPE_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPE, BULK_IN_EP_NUM, HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_IN);
    HSUSBD_ENABLE_EP_INT(EPE, HSUSBD_EPINTEN_TXPKIEN_Msk);
    g_u32EpEMaxPacketSize = EPE_MAX_PKT_SIZE;

    /* EPF ==> Bulk-out endpoint */
    HSUSBD_SetEpBufAddr(EPF, EPF_BUF_BASE, EPF_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPF, EPF_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPF, BULK_OUT_EP_NUM, HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPF, HSUSBD_EPINTEN_RXPKIEN_Msk);
    g_u32EpFMaxPacketSize = EPF_MAX_PKT_SIZE;
}

void LBK_InitForFullSpeed(void)
{
    g_IsHighSpeedMode = 0;

    /*****************************************************/
    /* EPA ==> Interrupt-in endpoint */
    HSUSBD_SetEpBufAddr(EPA, EPA_BUF_BASE, EPA_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPA, EPA_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPA, INT_IN_EP_NUM, HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_IN);
    HSUSBD_ENABLE_EP_INT(EPA, HSUSBD_EPINTEN_TXPKIEN_Msk);
    g_u32EpAMaxPacketSize = EPA_OTHER_MAX_PKT_SIZE;

    /* EPB ==> Interrupt-out endpoint */
    HSUSBD_SetEpBufAddr(EPB, EPB_BUF_BASE, EPB_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPB, EPB_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPB, INT_OUT_EP_NUM, HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPB, HSUSBD_EPINTEN_RXPKIEN_Msk | HSUSBD_EPINTEN_BUFFULLIEN_Msk);
    g_u32EpBMaxPacketSize = EPB_OTHER_MAX_PKT_SIZE;

    /*****************************************************/
    /* EPC ==> Isochronous-in endpoint */
    HSUSBD_SetEpBufAddr(EPC, EPC_BUF_BASE, EPC_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPC, EPC_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPC, ISO_IN_EP_NUM, HSUSBD_EP_CFG_TYPE_ISO, HSUSBD_EP_CFG_DIR_IN);
    HSUSBD_ENABLE_EP_INT(EPC, HSUSBD_EPINTEN_TXPKIEN_Msk);
    g_u32EpCMaxPacketSize = EPC_OTHER_MAX_PKT_SIZE;

    /* EPD ==> Isochronous-out endpoint */
    HSUSBD_SetEpBufAddr(EPD, EPD_BUF_BASE, EPD_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPD, EPD_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPD, ISO_OUT_EP_NUM, HSUSBD_EP_CFG_TYPE_ISO, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPD, HSUSBD_EPINTEN_RXPKIEN_Msk);
    g_u32EpDMaxPacketSize = EPD_OTHER_MAX_PKT_SIZE;

    /*****************************************************/
    /* EPE ==> Bulk-in endpoint */
    HSUSBD_SetEpBufAddr(EPE, EPE_BUF_BASE, EPE_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPE, EPE_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPE, BULK_IN_EP_NUM, HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_IN);
    HSUSBD_ENABLE_EP_INT(EPE, HSUSBD_EPINTEN_TXPKIEN_Msk);
    g_u32EpEMaxPacketSize = EPE_OTHER_MAX_PKT_SIZE;

    /* EPF ==> Bulk-out endpoint */
    HSUSBD_SetEpBufAddr(EPF, EPF_BUF_BASE, EPF_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPF, EPF_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPF, BULK_OUT_EP_NUM, HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPF, HSUSBD_EPINTEN_RXPKIEN_Msk | HSUSBD_EPINTEN_BUFFULLIEN_Msk);
    g_u32EpFMaxPacketSize = EPF_OTHER_MAX_PKT_SIZE;
}

void VendorLBK_Init(void)
{
    //HSUSBD->OPER = 0;
    /* Configure USB controller */
    /* Enable USB BUS, CEP and EPA global interrupt */
    HSUSBD_ENABLE_USB_INT(HSUSBD_GINTEN_USBIEN_Msk|HSUSBD_GINTEN_CEPIEN_Msk|HSUSBD_GINTEN_EPAIEN_Msk|HSUSBD_GINTEN_EPBIEN_Msk|HSUSBD_GINTEN_EPCIEN_Msk|HSUSBD_GINTEN_EPDIEN_Msk|HSUSBD_GINTEN_EPEIEN_Msk|HSUSBD_GINTEN_EPFIEN_Msk);
    /* Enable BUS interrupt */
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_DMADONEIEN_Msk|HSUSBD_BUSINTEN_RESUMEIEN_Msk|HSUSBD_BUSINTEN_RSTIEN_Msk|HSUSBD_BUSINTEN_VBUSDETIEN_Msk);
    /* Reset Address to 0 */
    HSUSBD_SET_ADDR(0);

    /*****************************************************/
    /* Control endpoint */
    HSUSBD_SetEpBufAddr(CEP, CEP_BUF_BASE, CEP_BUF_LEN);
    HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);

    LBK_InitForHighSpeed();
}

void VendorLBK_ClassRequest(void)
{
    uint8_t   data_len;

    if (g_IsHighSpeedMode)
        data_len = CEP_MAX_PKT_SIZE;
    else
        data_len = CEP_OTHER_MAX_PKT_SIZE;

    if (gUsbCmd.bmRequestType & 0x80)   /* request data transfer direction */
    {
        // Device to host
        switch (gUsbCmd.bRequest)
        {
        case REQ_GET_DATA:
            if (g_IsHighSpeedMode)
                data_len = CEP_MAX_PKT_SIZE;
            else
                data_len = CEP_OTHER_MAX_PKT_SIZE;
            if (gUsbCmd.wLength < data_len)
                data_len = gUsbCmd.wLength;
            HSUSBD_PrepareCtrlIn((uint8_t *)&g_Ctrl_Buff, data_len);
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_INTKIEN_Msk);
            break;

        default:
            /* Setup error, stall the device */
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
            break;
        }
    }
    else
    {
        // Host to device
        switch (gUsbCmd.bRequest)
        {
        case REQ_SET_DATA:
            if (gUsbCmd.wLength < data_len)
                data_len = gUsbCmd.wLength;
            HSUSBD_CtrlOut((uint8_t *)&g_Ctrl_Buff, data_len);

            /* Status stage */
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            break;

        default:
            /* Setup error, stall the device */
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
            break;
        }
    }
}

static void LBK_GetBulkOutData(void)
{
    uint32_t  t0;

    /* bulk out, dma write */
    HSUSBD_SET_DMA_WRITE(BULK_OUT_EP_NUM);

    /* Enable BUS interrupt */
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_DMADONEIEN_Msk|HSUSBD_BUSINTEN_SUSPENDIEN_Msk|HSUSBD_BUSINTEN_RSTIEN_Msk|HSUSBD_BUSINTEN_VBUSDETIEN_Msk);

    g_DMA_RunMsk |= (1<<BULK_OUT_EP_NUM);

    HSUSBD_SET_DMA_ADDR((uint32_t)g_Bulk_Buff);
    HSUSBD_SET_DMA_LEN(g_u32EpFMaxPacketSize);
    HSUSBD_ENABLE_DMA();

    t0 = get_ticks();
    while (1)
    {
        if ((g_DMA_RunMsk & (1<<BULK_OUT_EP_NUM)) == 0)
            break;                      /* DMA done */

        if (!HSUSBD_IS_ATTACHED())
            break;

        if (get_ticks() - t0 > 100)
        {
            printf("Warning!! LBK_GetBulkOutData DMA time-out!\n");
            break;
        }
    }
}

static void LBK_PrepareBulkInData(void)
{
    uint32_t  t0;

    /* bulk in, dma read */
    HSUSBD_SET_DMA_READ(BULK_IN_EP_NUM);
    HSUSBD_ENABLE_EP_INT(EPE, HSUSBD_EPINTEN_TXPKIEN_Msk);
    /* Enable BUS interrupt */
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_DMADONEIEN_Msk|HSUSBD_BUSINTEN_SUSPENDIEN_Msk|HSUSBD_BUSINTEN_RSTIEN_Msk|HSUSBD_BUSINTEN_VBUSDETIEN_Msk);

    g_DMA_RunMsk |= (1<<BULK_IN_EP_NUM);

    HSUSBD_SET_DMA_ADDR((uint32_t)g_Bulk_Buff);
    HSUSBD_SET_DMA_LEN(g_u32EpEMaxPacketSize);
    HSUSBD_ENABLE_DMA();

    t0 = get_ticks();
    while (1)
    {
        if ((g_DMA_RunMsk & (1<<BULK_IN_EP_NUM)) == 0)
            break;                      /* DMA done */

        if (!HSUSBD_IS_ATTACHED())
            break;

        if (get_ticks() - t0 > 100)
        {
            printf("Warning!! LBK_PrepareBulkInData DMA time-out!\n");
            break;
        }
    }
}

static void LBK_GetIsoOutData(void)
{
    uint32_t  t0;

    /* bulk out, dma write */
    HSUSBD_SET_DMA_WRITE(ISO_OUT_EP_NUM);

    /* Enable BUS interrupt */
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_DMADONEIEN_Msk|HSUSBD_BUSINTEN_SUSPENDIEN_Msk|HSUSBD_BUSINTEN_RSTIEN_Msk|HSUSBD_BUSINTEN_VBUSDETIEN_Msk);

    g_DMA_RunMsk |= (1<<ISO_OUT_EP_NUM);

    HSUSBD_SET_DMA_ADDR((uint32_t)g_Iso_Buff);
    HSUSBD_SET_DMA_LEN(g_u32EpDMaxPacketSize);
    HSUSBD_ENABLE_DMA();

    t0 = get_ticks();
    while (1)
    {
        if ((g_DMA_RunMsk & (1<<ISO_OUT_EP_NUM)) == 0)
            break;                      /* DMA done */

        if (!HSUSBD_IS_ATTACHED())
            break;

        if (get_ticks() - t0 > 100)
        {
            printf("Warning!! LBK_GetIsoOutData DMA time-out!\n");
            break;
        }
    }
}

static void LBK_PrepareIsoInData(void)
{
    uint32_t  t0;

    HSUSBD_SET_DMA_READ(ISO_IN_EP_NUM);
    HSUSBD_ENABLE_EP_INT(EPC, HSUSBD_EPINTEN_TXPKIEN_Msk);
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_DMADONEIEN_Msk|HSUSBD_BUSINTEN_SUSPENDIEN_Msk|HSUSBD_BUSINTEN_RSTIEN_Msk|HSUSBD_BUSINTEN_VBUSDETIEN_Msk);

    g_DMA_RunMsk |= (1<<ISO_IN_EP_NUM);

    HSUSBD_SET_DMA_ADDR((uint32_t)g_Iso_Buff);
    HSUSBD_SET_DMA_LEN(g_u32EpCMaxPacketSize);
    HSUSBD_ENABLE_DMA();

    t0 = get_ticks();
    while (1)
    {
        if ((g_DMA_RunMsk & (1<<ISO_IN_EP_NUM)) == 0)
            break;                      /* DMA done */

        if (!HSUSBD_IS_ATTACHED())
            break;

        if (get_ticks() - t0 > 100)
        {
            printf("Warning!! LBK_PrepareIsoInData DMA time-out!\n");
            break;
        }
    }
}

void VendorLBK_ProcessData(void)
{
    int         i;

    if (g_IntInDataEmpty)
    {
        g_IntInDataEmpty = 0;
        /* Prepare the data for next interrupt-in transfer */
        for (i = 0; i < g_u32EpAMaxPacketSize; i++)
            HSUSBD->EP[EPA].EPDAT_BYTE = g_Int_Buff[i];
        HSUSBD->EP[EPA].EPTXCNT = g_u32EpAMaxPacketSize;
        HSUSBD_ENABLE_EP_INT(EPA, HSUSBD_EPINTEN_INTKIEN_Msk);
    }

    if (g_IsoInDataEmpty && !(HSUSBD->DMACTL & HSUSBD_DMACTL_DMAEN_Msk))
    {
        g_IsoInDataEmpty = 0;
        LBK_PrepareIsoInData();
    }

    if (g_IsoOutDataReady && !(HSUSBD->DMACTL & HSUSBD_DMACTL_DMAEN_Msk))
    {
        g_IsoOutDataReady = 0;
        LBK_GetIsoOutData();
    }

    if (g_BulkOutDataReady && !(HSUSBD->DMACTL & HSUSBD_DMACTL_DMAEN_Msk))
    {
        g_BulkOutDataReady = 0;
        LBK_GetBulkOutData();
    }

    if (g_BulkInDataEmpty && !(HSUSBD->DMACTL & HSUSBD_DMACTL_DMAEN_Msk))
    {
        g_BulkInDataEmpty = 0;
        LBK_PrepareBulkInData();
    }
}




