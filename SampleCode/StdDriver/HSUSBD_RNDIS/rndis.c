/***************************************************************************//**
 * @file     rndis.c
 * @brief    M480 series USBD driver Sample file
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <string.h>
#include "M480.h"
#include "rndis.h"


extern uint8_t rndis_outdata[EMAC_TX_DESC_SIZE + 1][1580];
extern uint8_t rndis_indata[EMAC_RX_DESC_SIZE + 1][1580];
extern uint32_t u32CurrentTxBuf;
extern uint32_t u32CurrentRxBuf;


#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t rndis_command[256];
uint8_t rndis_response[256];
#else
uint8_t rndis_command[256] __attribute__((aligned(32)));
uint8_t rndis_response[256] __attribute__((aligned(32)));
#endif

#ifdef __ICCARM__
#pragma data_alignment=4
uint32_t rndis_oidbuffer[] =
{
#else
uint32_t rndis_oidbuffer[] __attribute__((aligned(4))) =
{
#endif
    OID_GEN_SUPPORTED_LIST,         //0x00010101
    OID_GEN_HARDWARE_STATUS,        //0x00010102
    OID_GEN_MEDIA_SUPPORTED,        //0x00010103
    OID_GEN_MEDIA_IN_USE,           //0x00010104
    OID_GEN_MAXIMUM_FRAME_SIZE,     //0x00010106
    OID_GEN_LINK_SPEED,             //0x00010107
    OID_GEN_TRANSMIT_BLOCK_SIZE,    //0x0001010A
    OID_GEN_RECEIVE_BLOCK_SIZE,     //0x0001010B
    OID_GEN_VENDOR_ID,              //0x0001010C
    OID_GEN_VENDOR_DESCRIPTION,     //0x0001010D
    OID_GEN_VENDOR_DRIVER_VERSION,  //0x00010116
    OID_GEN_CURRENT_PACKET_FILTER,  //0x0001010E
    OID_GEN_MAXIMUM_TOTAL_SIZE,     //0x00010111
    OID_GEN_MEDIA_CONNECT_STATUS,   //0x00010114
    OID_GEN_PHYSICAL_MEDIUM,        //0x00010202
    OID_GEN_XMIT_OK,                //0x00020101
    OID_GEN_RCV_OK,                 //0x00020102
    OID_GEN_XMIT_ERROR,             //0x00020103
    OID_GEN_RCV_ERROR,              //0x00020104
    OID_GEN_RCV_NO_BUFFER,          //0x00020105
    OID_802_3_PERMANENT_ADDRESS,    //0x01010101
    OID_802_3_CURRENT_ADDRESS,      //0x01010102
    OID_802_3_MULTICAST_LIST,       //0x01010103
    OID_802_3_MAC_OPTIONS,          //0x01010105
    OID_802_3_MAXIMUM_LIST_SIZE,    //0x01010104
    OID_802_3_RCV_ERROR_ALIGNMENT,  //0x01020101
    OID_802_3_XMIT_ONE_COLLISION,   //0x01020102
    OID_802_3_XMIT_MORE_COLLISIONS  //0x01020103
};

uint8_t volatile gRndisOutData = 0, gRndisInData = 0;

extern uint8_t g_au8MacAddr[6];

extern uint32_t u32TxCnt, u32RxCnt;
uint32_t volatile linkStatus, outdatalen = 0;

/*--------------------------------------------------------------------------*/
/* MS OS Feature descriptor */
const unsigned char OS_feature_dsc[] =
{
    0x28, 0x00, 0x00, 0x00, /* dwLength */
    0x00, 0x01, /* bcdVersion */
    0x04, 0x00, /* wIndex */
    0x01,       /* bCount */
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* reserve 7 bytes */
    0x00,       /* bInterfaceNumber */
    0x01,       /* reserved */
    /* The following is compatible ID 8 bytes (RNDIS) */
    0x52, 0x4E, 0x44, 0x49, 0x53, 0x00, 0x00, 0x00,
    /* The following is SubCompatible ID null 8 bytes (5162001) */
    0x35, 0x31, 0x36, 0x32, 0x30, 0x30, 0x31, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* reserve 6 bytes */
};

/*--------------------------------------------------------------------------*/
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

            if (HSUSBD->OPER & 0x04)  /* high speed */
                RNDIS_InitForHighSpeed();
            else                    /* full speed */
                RNDIS_InitForFullSpeed();
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
            HSUSBD->EP[EPA].EPRSPCTL = (HSUSBD->EP[EPA].EPRSPCTL & 0x10) | HSUSBD_EP_RSPCTL_SHORTTXEN;    // packet end
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
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_STSDONEIEN_Msk|HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_INTKIF_Msk)
        {

            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
            if (!(IrqSt & HSUSBD_CEPINTSTS_STSDONEIF_Msk))
            {
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_TXPKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_TXPKIEN_Msk|HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
                HSUSBD_CtrlIn();
            }
            else
            {
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_TXPKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_TXPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk|HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
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
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_INTKIEN_Msk|HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
            }
            else
            {
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

    /* bulk in */
    if (IrqStL & HSUSBD_GINTSTS_EPAIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPA].EPINTSTS & HSUSBD->EP[EPA].EPINTEN;
        HSUSBD_ENABLE_EP_INT(EPA, 0);
        HSUSBD_CLR_EP_INT_FLAG(EPA, IrqSt);
    }
    /* bulk out */
    if (IrqStL & HSUSBD_GINTSTS_EPBIF_Msk)
    {
        volatile int i, len;
        HSUSBD_ENABLE_EP_INT(EPB, 0);
        IrqSt = HSUSBD->EP[EPB].EPINTSTS & HSUSBD->EP[EPB].EPINTEN;
        len = HSUSBD->EP[EPB].EPDATCNT & 0xffff;
        for (i=0; i<len; i++)
            rndis_outdata[u32CurrentTxBuf][outdatalen+i] = HSUSBD->EP[EPB].EPDAT_BYTE;
        outdatalen += len;
        gRndisOutData = 1;
        HSUSBD_CLR_EP_INT_FLAG(EPB, IrqSt);
    }
    /* interrupt in */
    if (IrqStL & HSUSBD_GINTSTS_EPCIF_Msk)
    {
        IrqSt = HSUSBD->EP[EPC].EPINTSTS & HSUSBD->EP[EPC].EPINTEN;
        RNDIS_IsAvaiable();
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


void RNDIS_InitForHighSpeed(void)
{
    /*****************************************************/
    /* EPA ==> Bulk IN endpoint, address 1 */
    HSUSBD_SetEpBufAddr(EPA, EPA_BUF_BASE, EPA_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPA, EPA_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPA, BULK_IN_EP_NUM, HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_IN);

    /* EPB ==> Bulk OUT endpoint, address 2 */
    HSUSBD_SetEpBufAddr(EPB, EPB_BUF_BASE, EPB_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPB, EPB_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPB, BULK_OUT_EP_NUM, HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPB, HSUSBD_EPINTEN_RXPKIEN_Msk | HSUSBD_EPINTEN_SHORTRXIEN_Msk);

    /* EPC ==> Interrupt IN endpoint, address 3 */
    HSUSBD_SetEpBufAddr(EPC, EPC_BUF_BASE, EPC_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPC, EPC_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPC, INT_IN_EP_NUM, HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_IN);
    HSUSBD_ENABLE_EP_INT(EPC, HSUSBD_EPINTEN_TXPKIEN_Msk);
    RNDIS_IsAvaiable();
}

void RNDIS_InitForFullSpeed(void)
{
    /*****************************************************/
    /* EPA ==> Bulk IN endpoint, address 1 */
    HSUSBD_SetEpBufAddr(EPA, EPA_BUF_BASE, EPA_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPA, EPA_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPA, BULK_IN_EP_NUM, HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_IN);

    /* EPB ==> Bulk OUT endpoint, address 2 */
    HSUSBD_SetEpBufAddr(EPB, EPB_BUF_BASE, EPB_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPB, EPB_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPB, BULK_OUT_EP_NUM, HSUSBD_EP_CFG_TYPE_BULK, HSUSBD_EP_CFG_DIR_OUT);
    HSUSBD_ENABLE_EP_INT(EPB, HSUSBD_EPINTEN_RXPKIEN_Msk | HSUSBD_EPINTEN_SHORTRXIEN_Msk);

    /* EPC ==> Interrupt IN endpoint, address 3 */
    HSUSBD_SetEpBufAddr(EPC, EPC_BUF_BASE, EPC_BUF_LEN);
    HSUSBD_SET_MAX_PAYLOAD(EPC, EPC_OTHER_MAX_PKT_SIZE);
    HSUSBD_ConfigEp(EPC, INT_IN_EP_NUM, HSUSBD_EP_CFG_TYPE_INT, HSUSBD_EP_CFG_DIR_IN);
    HSUSBD_ENABLE_EP_INT(EPC, HSUSBD_EPINTEN_TXPKIEN_Msk);
    RNDIS_IsAvaiable();
}

/*--------------------------------------------------------------------------*/
/**
  * @brief  USBD Endpoint Config.
  * @param  None.
  * @retval None.
  */
void RNDIS_Init(void)
{
    /* Configure USB controller */
    /* Enable USB BUS, CEP and EPA , EPB global interrupt */
    HSUSBD_ENABLE_USB_INT(HSUSBD_GINTEN_USBIEN_Msk|HSUSBD_GINTEN_CEPIEN_Msk|HSUSBD_GINTEN_EPAIEN_Msk|HSUSBD_GINTEN_EPBIEN_Msk|HSUSBD_GINTEN_EPCIEN_Msk);
    /* Enable BUS interrupt */
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_DMADONEIEN_Msk|HSUSBD_BUSINTEN_RESUMEIEN_Msk|HSUSBD_BUSINTEN_RSTIEN_Msk|HSUSBD_BUSINTEN_VBUSDETIEN_Msk);
    /* Reset Address to 0 */
    HSUSBD_SET_ADDR(0);

    /*****************************************************/
    /* Control endpoint */
    HSUSBD_SetEpBufAddr(CEP, CEP_BUF_BASE, CEP_BUF_LEN);
    HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);

    RNDIS_InitForHighSpeed();

}


void RNDIS_ClassRequest(void)
{
    uint32_t u32Len;
    uint8_t *address;
    if (gUsbCmd.bmRequestType & 0x80)
    { /* request data transfer direction */
        // Device to host
        switch (gUsbCmd.bRequest)
        {
            case GET_ENCAPSULATED_RESPONSE:
            {
                uint32_t len = *(uint32_t *)(rndis_response+4);
                HSUSBD_PrepareCtrlIn((uint8_t *)rndis_response, len);
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_INTKIEN_Msk|HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
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
    else
    {
        // Host to device
        switch (gUsbCmd.bRequest)
        {
            case SEND_ENCAPSULATED_COMMAND:
            {
                u32Len = gUsbCmd.wLength;
                address = rndis_command;
                while(u32Len)
                {
                    if(u32Len > 64)
                    {
                        HSUSBD_CtrlOut((uint8_t *)address, 64);
                        address += 64;
                        u32Len -= 64;
                    }
                    else
                    {
                        HSUSBD_CtrlOut((uint8_t *)address, u32Len);
                        u32Len = 0;
                    }
                }
                RNDIS_ProcessClassCmd();
                /* Status stage */
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
                HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_STSDONEIEN_Msk|HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
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

void RNDIS_VendorRequest(void)
{
    uint32_t u32Len;

    if (gUsbCmd.bmRequestType & 0x80)
    { /* request data transfer direction */
        // Device to host
        if ((gUsbCmd.bRequest == 0xCD) && (gUsbCmd.wIndex == 0x0004))
        {
                u32Len = Minimum(gUsbCmd.wLength, OS_feature_dsc[0]);
                HSUSBD_PrepareCtrlIn((uint8_t *)OS_feature_dsc, u32Len);
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_INTKIEN_Msk|HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
        }
        else
        {
            /* Setup error, stall the device */
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_STALLEN_Msk);
        }
    }
}

void RNDIS_ProcessClassCmd(void)
{
    uint32_t *ptr = (uint32_t *)rndis_response;
    uint32_t *pMsg = (uint32_t *)rndis_command;
    uint32_t msgtype = *pMsg;

    switch (msgtype)
    {
        case REMOTE_NDIS_INITIALIZE_MSG:
            *ptr = REMOTE_NDIS_INITIALIZE_CMPLT;
            *(ptr+1) = 52;
            *(ptr+2) = *(pMsg + 2);    /* Request ID */
            *(ptr+3) = RNDIS_STATUS_SUCCESS;    /* Status */
            *(ptr+4) = 0x00000001;      /* MajorVersion */
            *(ptr+5) = 0x00000000;      /* MinorVersion */
            *(ptr+6) = 0x00000001;      /* DeviceFlags */
            *(ptr+7) = 0x00000000;      /* Medium */
            *(ptr+8) = 0x00000001;      /* max packets per transfer */
            *(ptr+9) = 0x0000062C;      /* max transfer size */
            *(ptr+10) = 0x00000000;     /* PacketAlignmentFactor */
            *(ptr+11) = 0x00000000;     /* AFListOffset */
            *(ptr+12) = 0x00000000;     /* AFListSize */
            break;

        case REMOTE_NDIS_QUERY_MSG:
            *ptr = REMOTE_NDIS_QUERY_CMPLT;
            *(ptr+2) = *(pMsg+2);                   /* Request ID */
            RNDIS_ProcessQueryOID(*(pMsg+3));
            *(ptr+3) = RNDIS_STATUS_SUCCESS;        /* Status */
            break;

        case REMOTE_NDIS_SET_MSG:
            *ptr = REMOTE_NDIS_SET_CMPLT;
            *(ptr+1) = 0x10;
            *(ptr+2) = *(pMsg+2);                   /* Request ID */
            RNDIS_ProcessSetOID(*(pMsg+3));
            *(ptr+3) = RNDIS_STATUS_SUCCESS;        /* Status */
            break;

        case REMOTE_NDIS_RESET_MSG:
            *ptr = REMOTE_NDIS_RESET_CMPLT;
            *(ptr+1) = 0x10;
            *(ptr+2) = RNDIS_STATUS_SUCCESS;        /* Status */
            *(ptr+3) = 0x1;        /* AddressingReset */
            break;

        case REMOTE_NDIS_INDICATE_STATUS_MSG:
            break;

        case REMOTE_NDIS_KEEPALIVE_MSG:
            *ptr = REMOTE_NDIS_KEEPALIVE_CMPLT;
            *(ptr+1) = 0x10;
            *(ptr+2) = *(pMsg+2);               /* Request ID */
            *(ptr+3) = RNDIS_STATUS_SUCCESS;    /* Status */
            break;

        case REMOTE_NDIS_HALT_MSG:
            break;

        default:
            ;
    }
}

extern uint32_t My_EMAC_SendPkt(uint8_t *pu8Data, uint32_t u32Size);
void RNDIS_ProcessOutData(void)
{
    uint32_t size = *(uint32_t *)((uint32_t) &rndis_outdata[u32CurrentTxBuf][0xC]);
    uint32_t offset = size + 44;

    HSUSBD_ENABLE_EP_INT(EPB, HSUSBD_EPINTEN_RXPKIEN_Msk | HSUSBD_EPINTEN_SHORTRXIEN_Msk);
    if (gRndisOutData)
    {
__retry_mac_tx_:
        if (outdatalen >= offset)
        {
            if (My_EMAC_SendPkt(&rndis_outdata[u32CurrentTxBuf][rndis_outdata[u32CurrentTxBuf][8] + 8], size) == 1)
            {
                // data successfully hook to EMAC descriptor, use next free buffer
                u32CurrentTxBuf++;
                if (u32CurrentTxBuf == EMAC_TX_DESC_SIZE + 1)
                    u32CurrentTxBuf = 0;
                if ((outdatalen - offset) > 0)
                {
                    size = *(uint32_t *)((uint32_t) &rndis_outdata[u32CurrentTxBuf-1][offset+0xC]);
                    memcpy(&rndis_outdata[u32CurrentTxBuf][0],&rndis_outdata[u32CurrentTxBuf-1][offset], size);
                    outdatalen -= offset;
                    if (My_EMAC_SendPkt(&rndis_outdata[u32CurrentTxBuf][rndis_outdata[u32CurrentTxBuf][8] + 8], size) == 1)
                    {
                        u32CurrentTxBuf++;
                        if (u32CurrentTxBuf == EMAC_TX_DESC_SIZE + 1)
                            u32CurrentTxBuf = 0;
                    }
                }
                gRndisOutData = 0;
                outdatalen = 0;
                u32TxCnt++;
            }
            else
            {
                HSUSBD_ENABLE_EP_INT(EPB, 0);
                goto __retry_mac_tx_;
            }
        }
    }
}

void RNDIS_InData(unsigned int u32PktLen)
{
    uint32_t *ptr = (uint32_t *)rndis_indata[u32CurrentRxBuf];
    uint32_t msglen;

    *(ptr+1) = msglen = u32PktLen + 44;  /* message len = data len + 44 */
    *(ptr+3) = u32PktLen;                /* data len */

    /* active usbd DMA to send data to FIFO */
    HSUSBD_SET_DMA_READ(BULK_IN_EP_NUM);
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_DMADONEIEN_Msk|HSUSBD_BUSINTEN_SUSPENDIEN_Msk|HSUSBD_BUSINTEN_RSTIEN_Msk|HSUSBD_BUSINTEN_VBUSDETIEN_Msk);
    HSUSBD_SET_DMA_ADDR((uint32_t)rndis_indata[u32CurrentRxBuf]);
    HSUSBD_SET_DMA_LEN(msglen);
    g_hsusbd_DmaDone = 0;
    g_hsusbd_ShortPacket = 1;
    HSUSBD_ENABLE_DMA();

    /* wait usbd dma complete */
    while (1)
    {
        if (g_hsusbd_DmaDone)
            break;

        if (!HSUSBD_IS_ATTACHED())
            break;

        if ((HSUSBD->DMACTL & HSUSBD_DMACTL_DMAEN_Msk) == 0)
            break;
    }
    while (HSUSBD->EP[EPA].EPDATCNT & 0xFFFF)
    {
        if (!HSUSBD_IS_ATTACHED())
            return;
    }
}

void RNDIS_IsAvaiable(void)
{
    static int volatile acnt = 0;

    if (acnt++ == 0)
    {
        linkStatus = EMAC_CheckLinkStatus();
    }
    acnt &= 0x1ff;

    if (linkStatus == EMAC_LINK_DOWN)
    {
        HSUSBD->EP[EPC].EPDAT = 0x00000000;   /* 1: avaiable; 0: not */
    }
    else
    {
        HSUSBD->EP[EPC].EPDAT = 0x00000001;   /* 1: avaiable; 0: not */
    }
    HSUSBD->EP[EPC].EPDAT = 0x00000000;
    HSUSBD->EP[EPC].EPTXCNT = 8;
}


void RNDIS_ProcessQueryOID(uint32_t oid)
{
    int volatile i;
    uint32_t *ptr = (uint32_t *)rndis_response;

    switch (oid)
    {
        case OID_GEN_SUPPORTED_LIST:
        {
            uint32_t len = sizeof(rndis_oidbuffer);
            *(ptr+1) = 24 + len;        /* message len */
            *(ptr+4) = len;             /* InformationBufferLength */
            *(ptr+5) = 0x10;            /* InformationBufferOffset */
            for (i=0; i<len/4; i++)
                *(ptr+6+i) = rndis_oidbuffer[i];
            break;
        }
        case OID_GEN_HARDWARE_STATUS:
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            *(ptr+6) = 0;       /* NdisHardwareStatusReady */
            break;

        case OID_GEN_MEDIA_SUPPORTED:
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            *(ptr+6) = 0;       /* NdisMedium802_3 */
            break;

        case OID_GEN_MEDIA_IN_USE:
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            *(ptr+6) = 0;       /* NdisMedium802_3 */
            break;

        case OID_GEN_MAXIMUM_FRAME_SIZE:
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            *(ptr+6) = 1500;    /* 1500 */
            break;

        case OID_GEN_LINK_SPEED:
            linkStatus = EMAC_CheckLinkStatus();
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            if((linkStatus == EMAC_LINK_100F) || (linkStatus == EMAC_LINK_100H)) {
                *(ptr+6) = 1000000; /* 100Mbps */
            } else if((linkStatus == EMAC_LINK_10F) || (linkStatus == EMAC_LINK_10H)) {
                *(ptr+6) = 100000;  /* 10Mbps */
            } else {
                *(ptr+6) = 0;  /* disconnected */
            }
            break;

        case OID_GEN_TRANSMIT_BLOCK_SIZE:
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            *(ptr+6) = 1500;    /* 1518 */
            break;

        case OID_GEN_RECEIVE_BLOCK_SIZE:
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            *(ptr+6) = 1500;    /* 1518 */
            break;

        case OID_GEN_VENDOR_ID:
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            *(ptr+6) = 0xFFFFFF;  /* Vendors without an IEEE-registered code should use this value */
            break;

        case OID_GEN_VENDOR_DESCRIPTION:
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            *(ptr+6) = 'N';
            *(ptr+6) = 'V';
            *(ptr+6) = 'T';
            *(ptr+6) = 0x00;
            break;

        case OID_GEN_MAXIMUM_TOTAL_SIZE:
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            *(ptr+6) = 0x00000616;  /* 1558 */
            break;

        case OID_GEN_MEDIA_CONNECT_STATUS:
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            if(linkStatus == EMAC_LINK_DOWN)
                *(ptr+6) = 0x00000001;  /* NdisMediaStateDisconnected */
            else
                *(ptr+6) = 0x00000000;  /* NdisMediaStateConnected */
            break;

        case OID_GEN_VENDOR_DRIVER_VERSION:
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            *(ptr+6) = 0x00000001;
            break;

        case OID_GEN_XMIT_OK:
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            *(ptr+6) = u32TxCnt;
            break;

        case OID_GEN_RCV_OK:
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            *(ptr+6) = u32RxCnt;
            break;

        case OID_GEN_XMIT_ERROR:
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            *(ptr+6) = 0x00000000;
            break;

        case OID_GEN_RCV_ERROR:
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            *(ptr+6) = 0x00000000;
            break;

        case OID_GEN_RCV_NO_BUFFER:
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            *(ptr+6) = 0x00000000;
            break;

        case OID_802_3_PERMANENT_ADDRESS:
            *(ptr+1) = 24+6;    /* message len = 24 + info len */
            *(ptr+4) = 6;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            for (i=0; i<6; i++)
                rndis_response[24+i] = g_au8MacAddr[i];
            break;

        case OID_802_3_CURRENT_ADDRESS:
            *(ptr+1) = 24+6;    /* message len = 24 + info len */
            *(ptr+4) = 6;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            for (i=0; i<6; i++)
                rndis_response[24+i] = g_au8MacAddr[i];
            break;

        case OID_802_3_MAXIMUM_LIST_SIZE:
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            *(ptr+6) = 0x00000001;
            break;
        case OID_GEN_PHYSICAL_MEDIUM:
            *(ptr+1) = 24+4;    /* message len = 24 + info len */
            *(ptr+4) = 4;       /* InformationBufferLength */
            *(ptr+5) = 0x10;    /* InformationBufferOffset */
            *(ptr+6) = 0x00000000;
            break;
        default:
            ;
    }
}

void RNDIS_ProcessSetOID(uint32_t oid)
{
    int volatile i;
    uint32_t *ptr = (uint32_t *)rndis_response;

    switch (oid)
    {
        case OID_GEN_CURRENT_PACKET_FILTER:
            *(ptr+1) = 0x10;        /* TODO: message len */
            break;

        case OID_802_3_MULTICAST_LIST:
            *(ptr+1) = 0x10;        /* TODO: message len */
            break;

        default:
            ;
    }
}

/*** (C) COPYRIGHT 2019 Nuvoton Technology Corp. ***/
