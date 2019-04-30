/**************************************************************************//**
 * @file     HID_transfer.c
 * @version  V3.00
 * @brief    Secure ISP - USBD source file
 *
 * @note
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <string.h>
#include "NuMicro.h"
#include "HID_transfer.h"

#include "SecureISP.h"


extern void USBDSwReset(USBD_INFO_T *pUSBDInfo);
extern void USBDProcessSetupPacket(USBD_INFO_T *pUSBDInfo);
extern void USBDCtrlOut(USBD_INFO_T *pUSBDInfo);
extern void USBDCtrlIn(USBD_INFO_T *pUSBDInfo);
extern void USBDGetSetupPacket(uint8_t *buf, USBD_INFO_T *pUSBDInfo);
extern void USBDSetStall(uint8_t epnum);


int32_t USBDInstallEPHandler(uint32_t ep, void *pfnEPHandler, uint32_t *pfnEPTable)
{
    if(ep < USBD_MAX_EP)
        pfnEPTable[ep] = (uint32_t)pfnEPHandler;
    else
        return -1;

    return 0;
}


int32_t ProcessUSBDInterrupt(uint32_t *pInfo, uint32_t *pUSBDInfo)
{
    volatile uint32_t   u32IntSts, u32State;
    volatile USBD_INFO_T *pCurUSBDInfo;

    pCurUSBDInfo = (USBD_INFO_T *)pUSBDInfo;

    u32IntSts = USBD_GET_INT_FLAG();
    u32State = USBD_GET_BUS_STATE();

//------------------------------------------------------------------
    if(u32IntSts & USBD_INTSTS_FLDET)
    {
        // Floating detect
        USBD_CLR_INT_FLAG(USBD_INTSTS_FLDET);

        if(USBD_IS_ATTACHED())
        {
            /* USB Plug In */
            USBD_ENABLE_USB();
        }
        else
        {
////            /* USB Un-plug */ /* Don't enable Un-Plug ... It's TC8234 real chip bug */
////            USBD_DISABLE_USB();
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
            USBDSwReset((USBD_INFO_T *)pCurUSBDInfo);
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

            USBDProcessSetupPacket((USBD_INFO_T *)pCurUSBDInfo);
        }

        // EP events
        if(u32IntSts & USBD_INTSTS_EP0)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP0);
            // control IN
            USBDCtrlIn((USBD_INFO_T *)pCurUSBDInfo);
        }

        if(u32IntSts & USBD_INTSTS_EP1)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP1);

            // control OUT
            USBDCtrlOut((USBD_INFO_T *)pCurUSBDInfo);
        }

        if(u32IntSts & USBD_INTSTS_EP2)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP2);
        }

        if(u32IntSts & USBD_INTSTS_EP3)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP3);

            EP3_Handler(pInfo);
        }

        if(u32IntSts & USBD_INTSTS_EP4)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP4);
        }

        if(u32IntSts & USBD_INTSTS_EP5)
        {
            /* Clear event flag */
            USBD_CLR_INT_FLAG(USBD_INTSTS_EP5);
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
    return 0;
}

void EP2_Handler(uint8_t *pu8Buf)  /* Interrupt IN handler */
{
    uint8_t *rspbuf;

    rspbuf = pu8Buf;
    NuBL_MemCopy((uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP2)), rspbuf, EP2_MAX_PKT_SIZE);

    /* Trigger start Interrupt IN */
    //g_i32IntInDone = 0;
    USBD_SET_PAYLOAD_LEN(EP2, EP2_MAX_PKT_SIZE);

    /* Waiting to Host get the data */
    //while(g_i32IntInDone == 0);
}

void EP3_Handler(uint32_t *pu32Buf)  /* Interrupt OUT handler */
{
    uint32_t            len;
    volatile ISP_INFO_T *pISPInfo;

    pISPInfo = (ISP_INFO_T *)pu32Buf;

    /* Interrupt OUT */
    if(pISPInfo->IsUSBDataReady == FALSE)
    {
        len = USBD_GET_PAYLOAD_LEN(EP3);

        NuBL_MemCopy((uint8_t *)pISPInfo->rcvbuf, (uint8_t *)(USBD_BUF_BASE + USBD_GET_EP_BUF_ADDR(EP3)), len);

        pISPInfo->IsUSBDataReady = TRUE;

        USBD_SET_PAYLOAD_LEN(EP3, EP3_MAX_PKT_SIZE);
    }
}

void HID_ClassRequest(uint32_t *pUSBDInfo)
{
    uint8_t         buf[8];
    USBD_INFO_T  *pCurUSBDInfo;

    pCurUSBDInfo = (USBD_INFO_T *)pUSBDInfo;

    USBDGetSetupPacket(buf, pCurUSBDInfo);

    if(buf[0] & 0x80)    /* request data transfer direction */
    {
        // Device to host
        switch(buf[1])
        {
        case GET_REPORT:
//             {
//                 break;
//             }
        case GET_IDLE:
//             {
//                 break;
//             }
        case GET_PROTOCOL:
//            {
//                break;
//            }
        default:
        {
            /* Setup error, stall the device */
            USBDSetStall(0);
            break;
        }
        }
    }
    else
    {
        // Host to device
        switch(buf[1])
        {
        case SET_REPORT:
        {
            if(buf[3] == 3)
            {
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
//             {
//                 break;
//             }
        default:
        {
            // Stall
            /* Setup error, stall the device */
            USBDSetStall(0);
            break;
        }
        }
    }
}

void HID_Init(void)
{
    /* Init setup packet buffer */
    /* Buffer range for setup packet -> [0 ~ 0x7] */
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
    /* EP2 ==> Interrupt IN endpoint, address 1 */
    USBD_CONFIG_EP(EP2, USBD_CFG_EPMODE_IN | INT_IN_EP_NUM);
    /* Buffer range for EP2 */
    USBD_SET_EP_BUF_ADDR(EP2, EP2_BUF_BASE);

    /* EP3 ==> Interrupt OUT endpoint, address 2 */
    USBD_CONFIG_EP(EP3, USBD_CFG_EPMODE_OUT | INT_OUT_EP_NUM);
    /* Buffer range for EP3 */
    USBD_SET_EP_BUF_ADDR(EP3, EP3_BUF_BASE);
    /* trigger to receive OUT data */
    USBD_SET_PAYLOAD_LEN(EP3, EP3_MAX_PKT_SIZE);
}
