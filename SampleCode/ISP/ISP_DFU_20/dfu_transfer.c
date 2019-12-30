/******************************************************************************//**
 * @file     dfu_transfer.c
 * @version  V1.00
 * @brief    M480 series USBD DFU transfer sample file
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

/*!<Includes */
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"
#include "dfu_transfer.h"
#include "fmc_user.h"

extern uint32_t g_apromSize;
#define APROM_BLOCK_NUM         ((g_apromSize/TRANSFER_SIZE)-1)

uint32_t command_Count = 0;
uint8_t manifest_state = MANIFEST_COMPLETE;
dfu_status_struct dfu_status;
s_prog_struct prog_struct __attribute__((aligned(4))) = {{0}, 0, 0, APP_LOADED_ADDR};

void USBD20_IRQHandler(void)
{
    __IO uint32_t IrqStL, IrqSt;
    IrqStL = HSUSBD->GINTSTS & HSUSBD->GINTEN;    /* get interrupt status */

    if (!IrqStL)
    {
        return;
    }

    /* USB interrupt */
    if (IrqStL & HSUSBD_GINTSTS_USBIF_Msk)
    {
        IrqSt = HSUSBD->BUSINTSTS & HSUSBD->BUSINTEN;

        if (IrqSt & HSUSBD_BUSINTSTS_RSTIF_Msk)
        {
            HSUSBD_SwReset();
            HSUSBD_ResetDMA();
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
            HSUSBD_SET_ADDR(0);
            HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RSTIEN_Msk | HSUSBD_BUSINTEN_RESUMEIEN_Msk | HSUSBD_BUSINTEN_SUSPENDIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_RSTIF_Msk);
            HSUSBD_CLR_CEP_INT_FLAG(0x1ffc);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_RESUMEIF_Msk)
        {
            HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RSTIEN_Msk | HSUSBD_BUSINTEN_SUSPENDIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_RESUMEIF_Msk);
        }

        if (IrqSt & HSUSBD_BUSINTSTS_SUSPENDIF_Msk)
        {
            HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_RSTIEN_Msk | HSUSBD_BUSINTEN_RESUMEIEN_Msk);
            HSUSBD_CLR_BUS_INT_FLAG(HSUSBD_BUSINTSTS_SUSPENDIF_Msk);
        }

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

        if (IrqSt & HSUSBD_CEPINTSTS_SETUPPKIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_SETUPPKIF_Msk);
            HSUSBD_ProcessSetupPacket();
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
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_TXPKIEN_Msk | HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            }
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
                {
                    HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_ZEROLEN);
                }
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk | HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            }

            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_TXPKIF_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_RXPKIF_Msk)
        {
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_RXPKIF_Msk);
            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk | HSUSBD_CEPINTEN_STSDONEIEN_Msk);
            return;
        }

        if (IrqSt & HSUSBD_CEPINTSTS_STSDONEIF_Msk)
        {
            HSUSBD_UpdateDeviceState();
            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk);
            return;
        }
    }
}


/*--------------------------------------------------------------------------*/
/**
  * @brief  USBD Endpoint Config.
  * @param  None.
  * @retval None.
  */

void DFU_Init(void)
{
    /* Configure USB controller */
    /* Enable USB BUS, CEP and EPA global interrupt */
    HSUSBD_ENABLE_USB_INT(HSUSBD_GINTEN_USBIEN_Msk | HSUSBD_GINTEN_CEPIEN_Msk);
    /* Enable BUS interrupt */
    HSUSBD_ENABLE_BUS_INT(HSUSBD_BUSINTEN_DMADONEIEN_Msk | HSUSBD_BUSINTEN_RESUMEIEN_Msk | HSUSBD_BUSINTEN_RSTIEN_Msk | HSUSBD_BUSINTEN_VBUSDETIEN_Msk);
    /* Reset Address to 0 */
    HSUSBD_SET_ADDR(0);
    /*****************************************************/
    /* Control endpoint */
    HSUSBD_SetEpBufAddr(CEP, CEP_BUF_BASE, CEP_BUF_LEN);
    HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk | HSUSBD_CEPINTEN_STSDONEIEN_Msk);

    /* restore device default state */
    dfu_status.bStatus = STATUS_OK;
    dfu_status.bState = STATE_dfuIDLE;

    prog_struct.block_num = 0;
    prog_struct.data_len = 0;

}


void DFU_ClassRequest(void)
{
    uint32_t u32Len;
    uint8_t *address;

    if (gUsbCmd.bmRequestType & 0x80) 
    { /* request data transfer direction */
        // Device to host
        switch (gUsbCmd.bRequest)
        {
            case DFU_GETSTATUS: 
            {
                if (dfu_status.bState == STATE_dfuDNLOAD_SYNC)
                {
                    command_Count++;

                    if (command_Count == 5)
                    {
                        dfu_status.bState = STATE_dfuDNLOAD_IDLE;

                        WriteData(prog_struct.block_num * TRANSFER_SIZE, (prog_struct.block_num * TRANSFER_SIZE) + prog_struct.data_len, (uint32_t *)prog_struct.buf);
                        //dfu_status.bStatus = STATUS_errWRITE;
                        command_Count = 0;
                    }
                }

                if (dfu_status.bState == STATE_dfuDNLOAD_IDLE)
                {
                    command_Count++;

                    if (command_Count == 5)
                    {
                        dfu_status.bState = STATE_dfuMANIFEST_SYNC;
                        command_Count = 0;
                    }
                }

                if (dfu_status.bState == STATE_dfuMANIFEST_SYNC)
                {
                    command_Count++;

                    if (command_Count == 5)
                    {
                        dfu_status.bState = STATE_dfuIDLE;
                        command_Count = 0;
                    }
                }
                HSUSBD_PrepareCtrlIn((uint8_t *)&dfu_status.bStatus, 6);
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_INTKIEN_Msk);
                break;
            }
            case DFU_GETSTATE:
            {
                HSUSBD_PrepareCtrlIn((uint8_t *)&dfu_status.bState, 1);
                HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_INTKIEN_Msk);
                break;
            }
            case DFU_UPLOAD:
            {
                if (dfu_status.bState == STATE_dfuIDLE || dfu_status.bState == STATE_dfuUPLOAD_IDLE)
                {
                    if (gUsbCmd.wLength <= 0)
                    {
                        dfu_status.bState = STATE_dfuIDLE;
                        return;
                    }
                    else
                    {
                        if (dfu_status.bState == STATE_dfuIDLE)
                        {
                            dfu_status.bState = STATE_dfuUPLOAD_IDLE;
                        }

                        if (gUsbCmd.wValue > APROM_BLOCK_NUM)
                        {
                            dfu_status.bState = STATE_dfuIDLE;
                            HSUSBD->CEPCTL |= HSUSBD_CEPCTL_ZEROLEN_Msk;
                            while (HSUSBD->CEPCTL & HSUSBD_CEPCTL_ZEROLEN_Msk);
                            /* Status stage */
                            HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
                            HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
                            HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_STSDONEIEN_Msk);
                            break;
                        }

                        ReadData(gUsbCmd.wValue * TRANSFER_SIZE, (gUsbCmd.wValue * TRANSFER_SIZE) + gUsbCmd.wLength, (uint32_t *)prog_struct.buf);
                        HSUSBD_PrepareCtrlIn((uint8_t *)prog_struct.buf, gUsbCmd.wLength);
                        HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_INTKIF_Msk);
                        HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_INTKIEN_Msk);
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
    else
    {
        // Host to device
        switch (gUsbCmd.bRequest)
        {
            case DFU_DETACH:
            {
                switch (dfu_status.bState)
                {
                    case STATE_dfuIDLE:
                    case STATE_dfuDNLOAD_SYNC:
                    case STATE_dfuDNLOAD_IDLE:
                    case STATE_dfuMANIFEST_SYNC:
                    case STATE_dfuUPLOAD_IDLE:
                        dfu_status.bStatus = STATUS_OK;
                        dfu_status.bState = STATE_dfuIDLE;
                        dfu_status.iString = 0; /* iString */
                        prog_struct.block_num = 0;
                        prog_struct.data_len = 0;
                        break;

                    default:
                        break;
                }
            }

            case DFU_DNLOAD:
            {
                switch (dfu_status.bState)
                {
                    case STATE_dfuIDLE:
                    case STATE_dfuDNLOAD_IDLE:
                        if (gUsbCmd.wLength > 0)
                        {
                            /* update the global length and block number */
                            prog_struct.block_num = gUsbCmd.wValue;
                            prog_struct.data_len = gUsbCmd.wLength;
                            dfu_status.bState = STATE_dfuDNLOAD_SYNC;
                        }
                        else
                        {
                            manifest_state = MANIFEST_IN_PROGRESS;
                            dfu_status.bState = STATE_dfuMANIFEST_SYNC;
                        }

                        /* enable EP0 prepare receive the buffer */
                        u32Len = gUsbCmd.wLength;
                        address = prog_struct.buf;
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
                        /* Status stage */
                        HSUSBD_CLR_CEP_INT_FLAG(HSUSBD_CEPINTSTS_STSDONEIF_Msk);
                        HSUSBD_SET_CEP_STATE(HSUSBD_CEPCTL_NAKCLR);
                        HSUSBD_ENABLE_CEP_INT(HSUSBD_CEPINTEN_SETUPPKIEN_Msk|HSUSBD_CEPINTEN_STSDONEIEN_Msk);
                        break;
                }
                break;
            }

            case DFU_CLRSTATUS:
            {
                //  if (STATE_dfuERROR == dfu_status.bState) {
                dfu_status.bStatus = STATUS_OK;
                dfu_status.bState = STATE_dfuIDLE;
                // } //else {
                /* state Error */
                // dfu_status.bStatus = STATUS_errUNKNOWN;
                // dfu_status.bState = STATE_dfuERROR;
                // }
                dfu_status.iString = 0; /* iString: index = 0 */
                break;
            }

            case DFU_ABORT:
            {
                switch (dfu_status.bState)
                {
                    case STATE_dfuIDLE:
                    case STATE_dfuDNLOAD_SYNC:
                    case STATE_dfuDNLOAD_IDLE:
                    case STATE_dfuMANIFEST_SYNC:
                    case STATE_dfuUPLOAD_IDLE:
                        dfu_status.bStatus = STATUS_OK;
                        dfu_status.bState = STATE_dfuIDLE;
                        dfu_status.iString = 0; /* iString: index = 0 */

                        prog_struct.block_num = 0;
                        prog_struct.data_len = 0;
                        break;

                    default:
                        break;
                }
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
