/**************************************************************************//**
 * @file     usbd.c
 * @version  V3.00
 * @brief    M2351 series USBD driver source file
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <string.h>


#include "NuMicro.h"
#include "SecureISP.h"

#if 0
#define DBG_PRINTF      printf
#else
#define DBG_PRINTF(...)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup USBD_Driver USBD Driver
  @{
*/


/** @addtogroup USBD_EXPORTED_FUNCTIONS USBD Exported Functions
  @{
*/

extern void HID_ClassRequest(uint32_t *pUSBDInfo);
void BL_USBDStandardRequest(USBD_INFO_T *pUSBDInfo);
void BL_USBDPrepareCtrlIn(uint8_t *pu8Buf, uint32_t u32Size, USBD_INFO_T *pUSBDInfo);
void BL_USBDPrepareCtrlOut(uint8_t *pu8Buf, uint32_t u32Size, USBD_INFO_T *pUSBDInfo);
void USBDSetStall(uint8_t epnum);


/* Move all variables to USBD_INFO_T */
#if 0
/////* Global variables for Control Pipe */
////uint8_t g_usbd_SetupPacket[8] = {0UL};        /*!< Setup packet buffer */
////volatile uint8_t g_usbd_RemoteWakeupEn = 0UL; /*!< Remote wake up function enable flag */

/////**
//// * @cond HIDDEN_SYMBOLS
//// */
////static volatile uint8_t *g_usbd_CtrlInPointer = 0;
////static volatile uint8_t *g_usbd_CtrlOutPointer = 0;
////static volatile uint32_t g_usbd_CtrlInSize = 0UL;
////static volatile uint32_t g_usbd_CtrlOutSize = 0UL;
////static volatile uint32_t g_usbd_CtrlOutSizeLimit = 0UL;
////static volatile uint32_t g_usbd_UsbAddr = 0UL;
////static volatile uint32_t g_usbd_UsbConfig = 0UL;
////static volatile uint32_t g_usbd_CtrlMaxPktSize = 8UL;
////static volatile uint32_t g_usbd_UsbAltInterface = 0UL;
/////**
//// * @endcond
//// */

////const S_USBD_INFO_T *g_usbd_sInfo;                  /*!< A pointer for USB information structure */

////VENDOR_REQ g_usbd_pfnVendorRequest       = NULL;    /*!< USB Vendor Request Functional Pointer */
////CLASS_REQ g_usbd_pfnClassRequest         = NULL;    /*!< USB Class Request Functional Pointer */
////SET_INTERFACE_REQ g_usbd_pfnSetInterface = NULL;    /*!< USB Set Interface Functional Pointer */
////SET_CONFIG_CB g_usbd_pfnSetConfigCallback = NULL;   /*!< USB Set configuration callback function pointer */
////uint32_t g_u32EpStallLock                = 0UL;     /*!< Bit map flag to lock specified EP when SET_FEATURE */
#endif

/**
  * @brief      This function makes USBD module to be ready to use
  *
  * @param[in]  param           The structure of USBD information.
  * @param[in]  pfnClassReq     USB Class request callback function.
  * @param[in]  pfnSetInterface USB Set Interface request callback function.
  *
  * @return     None
  *
  * @details    This function will enable USB controller, USB PHY transceiver and pull-up resistor of USB_D+ pin. USB PHY will drive SE0 to bus.
  */

int32_t USBDOpen(const S_USBD_INFO_T *param, CLASS_REQ pfnClassReq, SET_INTERFACE_REQ pfnSetInterface, uint32_t *pUSBDInfo)
{
    USBD_INFO_T  *pCurUSBDInfo;

    pCurUSBDInfo = (USBD_INFO_T *)pUSBDInfo;

    pCurUSBDInfo->g_usbd_sInfo = (S_USBD_INFO_T *)param;
    if(pfnClassReq == NULL)
        pCurUSBDInfo->g_usbd_pfnClassRequest = (CLASS_REQ)HID_ClassRequest;
    else
        pCurUSBDInfo->g_usbd_pfnClassRequest = pfnClassReq;
    pCurUSBDInfo->g_usbd_pfnSetInterface = pfnSetInterface;

    /* get EP0 maximum packet size */
    pCurUSBDInfo->g_usbd_CtrlMaxPktSize = pCurUSBDInfo->g_usbd_sInfo->gu8DevDesc[7];

    /* Initial USB engine */
    USBD->ATTR = 0x6D0UL;
    /* Force SE0 */
    USBD_SET_SE0();

    return 0;
}

/**
  * @brief    This function makes USB host to recognize the device
  *
  * @param    None
  *
  * @return   None
  *
  * @details  Enable WAKEUP, FLDET, USB and BUS interrupts. Disable software-disconnect function after 100ms delay with SysTick timer.
  */

int32_t USBDStart(void)
{
    /* Disable software-disconnect function */
    USBD_CLR_SE0();
    USBD->ATTR = 0x7D0UL;

    /* Clear USB-related interrupts before enable interrupt */
    USBD_CLR_INT_FLAG(USBD_INT_BUS | USBD_INT_USB | USBD_INT_FLDET | USBD_INT_WAKEUP);

    /* Enable USB-related interrupts. */
    USBD_ENABLE_INT(USBD_INT_BUS | USBD_INT_USB | USBD_INT_FLDET | USBD_INT_WAKEUP);

    return 0;
}

/**
  * @brief    Process GetDescriptor request
  *
  * @param    None
  *
  * @return   None
  *
  * @details  Parse GetDescriptor request and perform the corresponding action.
  *
  */
void BL_USBDGetDescriptor(USBD_INFO_T *pUSBDInfo)
{
    uint32_t u32Len;

    u32Len = 0UL;
    u32Len = pUSBDInfo->g_usbd_SetupPacket[7];
    u32Len <<= 8UL;
    u32Len += pUSBDInfo->g_usbd_SetupPacket[6];

    switch(pUSBDInfo->g_usbd_SetupPacket[3])
    {
    /* Get Device Descriptor */
    case DESC_DEVICE:
    {
        u32Len = USBD_Minimum(u32Len, (uint32_t)LEN_DEVICE);
        DBG_PRINTF("Get device desc, %d\n", u32Len);
        BL_USBDPrepareCtrlIn((uint8_t *)pUSBDInfo->g_usbd_sInfo->gu8DevDesc, u32Len, pUSBDInfo);
        break;
    }
    /* Get Configuration Descriptor */
    case DESC_CONFIG:
    {
        uint32_t u32TotalLen;

        DBG_PRINTF("Get config desc len %d, acture len %d\n", u32Len, u32TotalLen);
        u32TotalLen = pUSBDInfo->g_usbd_sInfo->gu8ConfigDesc[3];
        u32TotalLen = pUSBDInfo->g_usbd_sInfo->gu8ConfigDesc[2] + (u32TotalLen << 8);
        DBG_PRINTF("Get config desc len %d, acture len %d\n", u32Len, u32TotalLen);
        u32Len = USBD_Minimum(u32Len, u32TotalLen);
        DBG_PRINTF("Minimum len %d\n", u32Len);
        BL_USBDPrepareCtrlIn((uint8_t *)pUSBDInfo->g_usbd_sInfo->gu8ConfigDesc, u32Len, pUSBDInfo);
        break;
    }
    /* Get BOS Descriptor */
    case DESC_BOS:
    {
        u32Len = USBD_Minimum(u32Len, LEN_BOS + LEN_BOSCAP);
        DBG_PRINTF("Get bos desc, %d\n", u32Len);
        BL_USBDPrepareCtrlIn((uint8_t *)pUSBDInfo->g_usbd_sInfo->gu8BosDesc, u32Len, pUSBDInfo);
        break;
    }
    /* Get HID Descriptor */
    case DESC_HID:
    {
        /* CV3.0 HID Class Descriptor Test,
           Need to indicate index of the HID Descriptor within gu8ConfigDescriptor, specifically HID Composite device. */
        uint32_t u32ConfigDescOffset;   /* u32ConfigDescOffset is configuration descriptor offset (HID descriptor start index) */
        u32Len = USBD_Minimum(u32Len, LEN_HID);
        DBG_PRINTF("Get HID desc, %d\n", u32Len);
        u32ConfigDescOffset = pUSBDInfo->g_usbd_sInfo->gu32ConfigHidDescIdx[pUSBDInfo->g_usbd_SetupPacket[4]];
        BL_USBDPrepareCtrlIn((uint8_t *)&pUSBDInfo->g_usbd_sInfo->gu8ConfigDesc[u32ConfigDescOffset], u32Len, pUSBDInfo);
        break;
    }
    /* Get Report Descriptor */
    case DESC_HID_RPT:
    {
        DBG_PRINTF("Get HID report, %d\n", u32Len);
        u32Len = USBD_Minimum(u32Len, pUSBDInfo->g_usbd_sInfo->gu32HidReportSize[pUSBDInfo->g_usbd_SetupPacket[4]]);
        BL_USBDPrepareCtrlIn((uint8_t *)pUSBDInfo->g_usbd_sInfo->gu8HidReportDesc[pUSBDInfo->g_usbd_SetupPacket[4]], u32Len, pUSBDInfo);
        break;
    }
    /* Get String Descriptor */
    case DESC_STRING:
    {
        /* Get String Descriptor */
        if(pUSBDInfo->g_usbd_SetupPacket[2] < 4UL)
        {
            u32Len = USBD_Minimum(u32Len, pUSBDInfo->g_usbd_sInfo->gu8StringDesc[pUSBDInfo->g_usbd_SetupPacket[2]][0]);
            DBG_PRINTF("Get string desc %d\n", u32Len);
            BL_USBDPrepareCtrlIn((uint8_t *)pUSBDInfo->g_usbd_sInfo->gu8StringDesc[pUSBDInfo->g_usbd_SetupPacket[2]], u32Len, pUSBDInfo);
            break;
        }
        else
        {
            /* Not support. Reply STALL. */
            USBD_SET_EP_STALL(EP0);
            USBD_SET_EP_STALL(EP1);
            DBG_PRINTF("Unsupported string desc (%d). Stall ctrl pipe.\n", pUSBDInfo->g_usbd_SetupPacket[2]);
            break;
        }
    }
    default:
        /* Not support. Reply STALL. */
        USBD_SET_EP_STALL(EP0);
        USBD_SET_EP_STALL(EP1);
        DBG_PRINTF("Unsupported get desc type. stall ctrl pipe\n");
        break;
    }
}

/**
  * @brief    Process standard request
  *
  * @param    None
  *
  * @return   None
  *
  * @details  Parse standard request and perform the corresponding action.
  *
  */
void BL_USBDStandardRequest(USBD_INFO_T *pUSBDInfo)
{
    uint32_t addr;

    /* clear global variables for new request */
    pUSBDInfo->g_usbd_CtrlInPointer = 0;
    pUSBDInfo->g_usbd_CtrlInSize = 0UL;

    if((pUSBDInfo->g_usbd_SetupPacket[0] & 0x80UL) == 0x80UL)    /* request data transfer direction */
    {
        /* Device to host */
        switch(pUSBDInfo->g_usbd_SetupPacket[1])
        {
        case GET_CONFIGURATION:
        {
            /* Return current configuration setting */
            /* Data stage */
            addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
            M8(addr) = (uint8_t)pUSBDInfo->g_usbd_UsbConfig;
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 1UL);
            /* Status stage */
            BL_USBDPrepareCtrlOut(0, 0UL, pUSBDInfo);
            DBG_PRINTF("Get configuration\n");
            break;
        }
        case GET_DESCRIPTOR:
        {
            BL_USBDGetDescriptor(pUSBDInfo);
            BL_USBDPrepareCtrlOut(0, 0UL, pUSBDInfo); /* For status stage */
            break;
        }
        case GET_INTERFACE:
        {
            // Return current interface setting
            /* Data stage */
            addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
            M8(addr) = (uint8_t)pUSBDInfo->g_usbd_UsbAltInterface;
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 1UL);
            /* Status stage */
            BL_USBDPrepareCtrlOut(0, 0UL, pUSBDInfo);
            DBG_PRINTF("Get interface\n");
            break;
        }
        case GET_STATUS:
        {
            /* Device */
            if(pUSBDInfo->g_usbd_SetupPacket[0] == 0x80UL)
            {
                uint8_t u8Tmp;

                u8Tmp = (uint8_t)0UL;
                if((pUSBDInfo->g_usbd_sInfo->gu8ConfigDesc[7] & 0x40UL) == 0x40UL)
                {
                    u8Tmp |= (uint8_t)1UL; /* Self-Powered/Bus-Powered. */
                }
                if((pUSBDInfo->g_usbd_sInfo->gu8ConfigDesc[7] & 0x20UL) == 0x20UL)
                {
                    u8Tmp |= (uint8_t)(pUSBDInfo->g_usbd_RemoteWakeupEn << 1UL); /* Remote wake up */
                }

                addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
                M8(addr) = u8Tmp;
            }
            /* Interface */
            else if(pUSBDInfo->g_usbd_SetupPacket[0] == 0x81UL)
            {
                addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
                M8(addr) = (uint8_t)0UL;
            }
            /* Endpoint */
            else if(pUSBDInfo->g_usbd_SetupPacket[0] == 0x82UL)
            {
                uint8_t ep = (uint8_t)(pUSBDInfo->g_usbd_SetupPacket[4] & 0xFUL);
                addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
                M8(addr) = (uint8_t)(USBD_GetStall(ep) ? 1UL : 0UL);
            }

            addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0) + 1UL;
            M8(addr) = (uint8_t)0UL;
            /* Data stage */
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 2UL);
            /* Status stage */
            BL_USBDPrepareCtrlOut(0, 0UL, pUSBDInfo);
            DBG_PRINTF("Get status\n");
            break;
        }
        default:
        {
            /* Setup error, stall the device */
            USBD_SET_EP_STALL(EP0);
            USBD_SET_EP_STALL(EP1);
            DBG_PRINTF("Unknown request. stall ctrl pipe.\n");
            break;
        }
        }
    }
    else
    {
        /* Host to device */
        switch(pUSBDInfo->g_usbd_SetupPacket[1])
        {
        case CLEAR_FEATURE:
        {
            if(pUSBDInfo->g_usbd_SetupPacket[2] == FEATURE_ENDPOINT_HALT)
            {
                uint32_t epNum, i;

                /* EP number stall is not allow to be clear in MSC class "Error Recovery Test".
                   a flag: g_u32EpStallLock is added to support it */
                epNum = (uint8_t)(pUSBDInfo->g_usbd_SetupPacket[4] & 0xFUL);
                for(i = 0UL; i < USBD_MAX_EP; i++)
                {
                    if(((USBD->EP[i].CFG & 0xFUL) == epNum) && ((pUSBDInfo->g_u32EpStallLock & (1UL << i)) == 0UL))
                    {
                        USBD->EP[i].CFGP &= ~USBD_CFGP_SSTALL_Msk;
                        DBG_PRINTF("Clr stall ep%d %x\n", i, USBD->EP[i].CFGP);
                    }
                }
            }
            else if(pUSBDInfo->g_usbd_SetupPacket[2] == FEATURE_DEVICE_REMOTE_WAKEUP)
            {
                pUSBDInfo->g_usbd_RemoteWakeupEn = (uint8_t)0UL;
            }

            /* Status stage */
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 0);
            DBG_PRINTF("Clear feature op %d\n", pUSBDInfo->g_usbd_SetupPacket[2]);
            break;
        }
        case SET_ADDRESS:
        {
            pUSBDInfo->g_usbd_UsbAddr = pUSBDInfo->g_usbd_SetupPacket[2];
            DBG_PRINTF("Set addr to %d\n", pUSBDInfo->g_usbd_UsbAddr);
            /* DATA IN for end of setup */
            /* Status Stage */
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 0UL);
            break;
        }
        case SET_CONFIGURATION:
        {
            pUSBDInfo->g_usbd_UsbConfig = pUSBDInfo->g_usbd_SetupPacket[2];

            if(pUSBDInfo->g_usbd_pfnSetConfigCallback)
            {
                pUSBDInfo->g_usbd_pfnSetConfigCallback();
            }

            /* DATA IN for end of setup */
            /* Status stage */
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 0UL);
            DBG_PRINTF("Set config to %d\n", pUSBDInfo->g_usbd_UsbConfig);
            break;
        }
        case SET_FEATURE:
        {
            if((pUSBDInfo->g_usbd_SetupPacket[0] & 0xFUL) == 0UL)   /* 0: device */
            {
                if((pUSBDInfo->g_usbd_SetupPacket[2] == 3UL) && (pUSBDInfo->g_usbd_SetupPacket[3] == 0UL)) /* 3: HNP enable */
                {
                    OTG->CTL |= (OTG_CTL_HNPREQEN_Msk | OTG_CTL_BUSREQ_Msk); //timtim, disable in M2351B
                }
            }
            if(pUSBDInfo->g_usbd_SetupPacket[2] == FEATURE_ENDPOINT_HALT)
            {
                USBDSetStall((uint8_t)(pUSBDInfo->g_usbd_SetupPacket[4] & 0xFUL));
                DBG_PRINTF("Set feature. stall ep %d\n", pUSBDInfo->g_usbd_SetupPacket[4] & 0xF);
            }
            else if(pUSBDInfo->g_usbd_SetupPacket[2] == FEATURE_DEVICE_REMOTE_WAKEUP)
            {
                pUSBDInfo->g_usbd_RemoteWakeupEn = 1;
                DBG_PRINTF("Set feature. enable remote wakeup\n");
            }

            /* Status stage */
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 0UL);
            break;
        }
        case SET_INTERFACE:
        {
            pUSBDInfo->g_usbd_UsbAltInterface = pUSBDInfo->g_usbd_SetupPacket[2];
            if(pUSBDInfo->g_usbd_pfnSetInterface != NULL)
            {
                pUSBDInfo->g_usbd_pfnSetInterface(pUSBDInfo->g_usbd_UsbAltInterface);
            }

            /* Status stage */
            USBD_SET_DATA1(EP0);
            USBD_SET_PAYLOAD_LEN(EP0, 0UL);
            DBG_PRINTF("Set interface to %d\n", pUSBDInfo->g_usbd_UsbAltInterface);
            break;
        }
        default:
        {
            /* Setup error, stall the device */
            USBD_SET_EP_STALL(EP0);
            USBD_SET_EP_STALL(EP1);
            DBG_PRINTF("Unsupported request. stall ctrl pipe.\n");
            break;
        }
        }
    }
}

/**
  * @brief      Prepare the first Control IN pipe
  *
  * @param[in]  pu8Buf  The pointer of data sent to USB host.
  * @param[in]  u32Size The IN transfer size.
  *
  * @return     None
  *
  * @details    Prepare data for Control IN transfer.
  *
  */
#if 1
void BL_USBDPrepareCtrlIn(uint8_t *pu8Buf, uint32_t u32Size, USBD_INFO_T *pUSBDInfo)
{
    uint32_t addr;

    // Data size <= MXPLD
    USBD_SET_DATA1(EP0);
    addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
    NuBL_MemCopy((uint8_t *)addr, pu8Buf, u32Size);
    USBD_SET_PAYLOAD_LEN(EP0, u32Size);
}

#else
void BL_USBDPrepareCtrlIn(uint8_t *pu8Buf, uint32_t u32Size, USBD_INFO_T *pUSBDInfo)
{
    uint32_t addr;

    DBG_PRINTF("Prepare Ctrl In %d\n", u32Size);
    if(u32Size > pUSBDInfo->g_usbd_CtrlMaxPktSize)
    {
        /* Data size > MXPLD */
        pUSBDInfo->g_usbd_CtrlInPointer = pu8Buf + pUSBDInfo->g_usbd_CtrlMaxPktSize;
        pUSBDInfo->g_usbd_CtrlInSize = u32Size - pUSBDInfo->g_usbd_CtrlMaxPktSize;
        USBD_SET_DATA1(EP0);
        addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
        NuBL_MemCopy((uint8_t *)addr, pu8Buf, pUSBDInfo->g_usbd_CtrlMaxPktSize);
        USBD_SET_PAYLOAD_LEN(EP0, pUSBDInfo->g_usbd_CtrlMaxPktSize);
    }
    else
    {
        // Data size <= MXPLD
        pUSBDInfo->g_usbd_CtrlInPointer = 0;
        pUSBDInfo->g_usbd_CtrlInSize = 0UL;
        USBD_SET_DATA1(EP0);
        addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
        NuBL_MemCopy((uint8_t *)addr, pu8Buf, u32Size);
        USBD_SET_PAYLOAD_LEN(EP0, u32Size);
    }
}
#endif


/**
  * @brief      Prepare the first Control OUT pipe
  *
  * @param[in]  pu8Buf  The pointer of data received from USB host.
  * @param[in]  u32Size The OUT transfer size.
  *
  * @return     None
  *
  * @details    This function is used to prepare the first Control OUT transfer.
  *
  */
void BL_USBDPrepareCtrlOut(uint8_t *pu8Buf, uint32_t u32Size, USBD_INFO_T *pUSBDInfo)
{
    pUSBDInfo->g_usbd_CtrlOutPointer = pu8Buf;
    pUSBDInfo->g_usbd_CtrlOutSize = 0UL;
    pUSBDInfo->g_usbd_CtrlOutSizeLimit = u32Size;
    USBD_SET_PAYLOAD_LEN(EP1, pUSBDInfo->g_usbd_CtrlMaxPktSize);
}

/**
 * @brief       USBD Set Vendor Request
 *
 * @param[in]   pfnVendorReq    Vendor Request Callback Function
 *
 * @return      None
 *
 * @details     This function is used to set USBD vendor request callback function
 */
void BL_USBDSetVendorRequest(VENDOR_REQ pfnVendorReq, USBD_INFO_T *pUSBDInfo)
{
    pUSBDInfo->g_usbd_pfnVendorRequest = pfnVendorReq;
}

/**
 * @brief       The callback function which called when get SET CONFIGURATION request
 *
 * @param[in]   pfnSetConfigCallback    Callback function pointer for SET CONFIGURATION request
 *
 * @return      None
 *
 * @details     This function is used to set the callback function which will be called at SET CONFIGURATION request.
 */
void BL_USBDSetConfigCallback(SET_CONFIG_CB pfnSetConfigCallback, USBD_INFO_T *pUSBDInfo)
{
    pUSBDInfo->g_usbd_pfnSetConfigCallback = pfnSetConfigCallback;
}

/**
 * @brief       EP stall lock function to avoid stall clear by USB SET FEATURE request.
 *
 * @param[in]   u32EpBitmap    Use bitmap to select which endpoints will be locked
 *
 * @return      None
 *
 * @details     This function is used to lock relative endpoint to avoid stall clear by SET FEATURE requst.
 *              If ep stall locked, user needs to reset USB device or re-configure device to clear it.
 */
void BL_USBDLockEpStall(uint32_t u32EpBitmap, USBD_INFO_T *pUSBDInfo)
{
    pUSBDInfo->g_u32EpStallLock = u32EpBitmap;
}

void USBDSetStall(uint8_t epnum)
{
    uint32_t u32CfgAddr;
    uint32_t u32Cfg;
    uint32_t i;

    for(i = 0UL; i < USBD_MAX_EP; i++)
    {
        u32CfgAddr = (uint32_t)(i << 4) + (uint32_t)&USBD->EP[0].CFG; /* USBD_CFG0 */
        u32Cfg = *((__IO uint32_t *)(u32CfgAddr));

        if((u32Cfg & 0xFUL) == epnum)
        {
            u32CfgAddr = (uint32_t)(i << 4) + (uint32_t)&USBD->EP[0].CFGP; /* USBD_CFGP0 */
            u32Cfg = *((__IO uint32_t *)(u32CfgAddr));

            *((__IO uint32_t *)(u32CfgAddr)) = (u32Cfg | USBD_CFGP_SSTALL);
            break;
        }
    }
}

/*
    The below APIs can be separated from usbd.c for arrange Non-secure callable address to compatible with M2351B.
*/
/**
  * @brief      Get the received SETUP packet
  *
  * @param[in]  buf A buffer pointer used to store 8-byte SETUP packet.
  *
  * @return     None
  *
  * @details    Store SETUP packet to a user-specified buffer.
  *
  */
void USBDGetSetupPacket(uint8_t *buf, USBD_INFO_T *pUSBDInfo)
{
    NuBL_MemCopy(buf, pUSBDInfo->g_usbd_SetupPacket, 8UL);
}

/**
  * @brief    Process SETUP packet
  *
  * @param    None
  *
  * @return   None
  *
  * @details  Parse SETUP packet and perform the corresponding action.
  *
  */
void USBDProcessSetupPacket(USBD_INFO_T *pUSBDInfo)
{
    /* Get SETUP packet from USB buffer */
    NuBL_MemCopy(pUSBDInfo->g_usbd_SetupPacket, (uint8_t *)USBD_BUF_BASE, 8UL);

    /* Check the request type */
    switch(pUSBDInfo->g_usbd_SetupPacket[0] & 0x60UL)
    {
    case REQ_STANDARD:   /* Standard */
    {
        BL_USBDStandardRequest(pUSBDInfo);
        break;
    }
    case REQ_CLASS:   /* Class */
    {
        if(pUSBDInfo->g_usbd_pfnClassRequest != NULL)
        {
            pUSBDInfo->g_usbd_pfnClassRequest();
        }
        break;
    }
//        case REQ_VENDOR:   /* Vendor */
//        {
//            if(pUSBDInfo->g_usbd_pfnVendorRequest != NULL)
//            {
//                pUSBDInfo->g_usbd_pfnVendorRequest();
//            }
//            break;
//        }
    default:   /* reserved */
    {
        /* Setup error, stall the device */
        USBD_SET_EP_STALL(EP0);
        USBD_SET_EP_STALL(EP1);
        break;
    }
    }
}

/**
  * @brief    Repeat Control IN pipe
  *
  * @param    None
  *
  * @return   None
  *
  * @details  This function processes the remained data of Control IN transfer.
  *
  */
#if 1
void USBDCtrlIn(USBD_INFO_T *pUSBDInfo)
{
    //static uint8_t u8ZeroFlag = 0UL;
    uint32_t addr;

    DBG_PRINTF("Ctrl In Ack. residue %d\n", pUSBDInfo->g_usbd_CtrlInSize);

    /* In ACK for Set address */
    if((pUSBDInfo->g_usbd_SetupPacket[0] == REQ_STANDARD) && (pUSBDInfo->g_usbd_SetupPacket[1] == SET_ADDRESS))
    {
        addr = USBD_GET_ADDR();
        if((addr != pUSBDInfo->g_usbd_UsbAddr) && (addr == 0UL))
        {
            USBD_SET_ADDR(pUSBDInfo->g_usbd_UsbAddr);
        }
    }

    DBG_PRINTF("Ctrl In done.\n");
}

#else
void USBDCtrlIn(USBD_INFO_T *pUSBDInfo)
{
    //static uint8_t u8ZeroFlag = 0UL;
    uint32_t addr;

    DBG_PRINTF("Ctrl In Ack. residue %d\n", g_usbd_CtrlInSize);
    if(pUSBDInfo->g_usbd_CtrlInSize)
    {
        /* Process remained data */
        if(pUSBDInfo->g_usbd_CtrlInSize > pUSBDInfo->g_usbd_CtrlMaxPktSize)
        {
            /* Data size > MXPLD */
            addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
            NuBL_MemCopy((uint8_t *)addr, (uint8_t *)pUSBDInfo->g_usbd_CtrlInPointer, pUSBDInfo->g_usbd_CtrlMaxPktSize);
            USBD_SET_PAYLOAD_LEN(EP0, pUSBDInfo->g_usbd_CtrlMaxPktSize);
            pUSBDInfo->g_usbd_CtrlInPointer += pUSBDInfo->g_usbd_CtrlMaxPktSize;
            pUSBDInfo->g_usbd_CtrlInSize -= pUSBDInfo->g_usbd_CtrlMaxPktSize;
        }
        else
        {
            /* Data size <= MXPLD */
            addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP0);
            NuBL_MemCopy((uint8_t *)addr, (uint8_t *)pUSBDInfo->g_usbd_CtrlInPointer, pUSBDInfo->g_usbd_CtrlInSize);
            USBD_SET_PAYLOAD_LEN(EP0, pUSBDInfo->g_usbd_CtrlInSize);
            if(pUSBDInfo->g_usbd_CtrlInSize == pUSBDInfo->g_usbd_CtrlMaxPktSize)
            {
                pUSBDInfo->g_usbd_u8ZeroFlag = (uint8_t)1UL;
            }
            pUSBDInfo->g_usbd_CtrlInPointer = 0;
            pUSBDInfo->g_usbd_CtrlInSize = 0UL;
        }
    }
    else /* No more data for IN token */
    {
        /* In ACK for Set address */
        if((pUSBDInfo->g_usbd_SetupPacket[0] == REQ_STANDARD) && (pUSBDInfo->g_usbd_SetupPacket[1] == SET_ADDRESS))
        {
            addr = USBD_GET_ADDR();
            if((addr != pUSBDInfo->g_usbd_UsbAddr) && (addr == 0UL))
            {
                USBD_SET_ADDR(pUSBDInfo->g_usbd_UsbAddr);
            }
        }

        /* For the case of data size is integral times maximum packet size */
        if(pUSBDInfo->g_usbd_u8ZeroFlag)
        {
            USBD_SET_PAYLOAD_LEN(EP0, 0UL);
            pUSBDInfo->g_usbd_u8ZeroFlag = (uint8_t)0UL;
        }
        DBG_PRINTF("Ctrl In done.\n");
    }
}
#endif
/**
  * @brief    Repeat Control OUT pipe
  *
  * @param    None
  *
  * @return   None
  *
  * @details  This function processes the successive Control OUT transfer.
  *
  */
void USBDCtrlOut(USBD_INFO_T *pUSBDInfo)
{
    uint32_t u32Size;
    uint32_t addr;

    DBG_PRINTF("Ctrl Out Ack %d\n", pUSBDInfo->g_usbd_CtrlOutSize);
    if(pUSBDInfo->g_usbd_CtrlOutSize < pUSBDInfo->g_usbd_CtrlOutSizeLimit)
    {
        u32Size = USBD_GET_PAYLOAD_LEN(EP1);
        addr = USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP1);
        NuBL_MemCopy((uint8_t *)pUSBDInfo->g_usbd_CtrlOutPointer, (uint8_t *)addr, u32Size);
        pUSBDInfo->g_usbd_CtrlOutPointer += u32Size;
        pUSBDInfo->g_usbd_CtrlOutSize += u32Size;

        if(pUSBDInfo->g_usbd_CtrlOutSize < pUSBDInfo->g_usbd_CtrlOutSizeLimit)
        {
            USBD_SET_PAYLOAD_LEN(EP1, pUSBDInfo->g_usbd_CtrlMaxPktSize);
        }
    }
}

/**
  * @brief    Reset software flags
  *
  * @param    None
  *
  * @return   None
  *
  * @details  This function resets all variables for protocol and resets USB device address to 0.
  *
  */
void USBDSwReset(USBD_INFO_T *pUSBDInfo)
{
    uint32_t i;

    /* Reset all variables for protocol */
    pUSBDInfo->g_usbd_CtrlInPointer = 0;
    pUSBDInfo->g_usbd_CtrlInSize = 0UL;
    pUSBDInfo->g_usbd_CtrlOutPointer = 0;
    pUSBDInfo->g_usbd_CtrlOutSize = 0UL;
    pUSBDInfo->g_usbd_CtrlOutSizeLimit = 0UL;
    pUSBDInfo->g_u32EpStallLock = 0UL;
    memset(pUSBDInfo->g_usbd_SetupPacket, 0, 8UL);

    /* Reset PID DATA0 */
    for(i = 0UL; i < USBD_MAX_EP; i++)
    {
        USBD->EP[i].CFG &= ~USBD_CFG_DSQSYNC_Msk;
    }

    /* Reset USB device address */
    USBD_SET_ADDR(0UL);
}


/*@}*/ /* end of group USBD_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group USBD_Driver */

/*@}*/ /* end of group Standard_Driver */

#ifdef __cplusplus
}
#endif

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
