/**************************************************************************//**
 * @file     bootisplib.h
 * @version  V1.00
 * @brief    Firmware Update library header file
 * @details  Secure Boot provide four APIs to do firmware update. M480 can
 *           connect with a PC executing firmware update tool via ether HSUSBD
 *           or UART1 to update firmware.
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __BLISPLIB_H__
#define __BLISPLIB_H__

#include "NuMicro.h"

/** @addtogroup LIBRARY Library
  @{
*/

/** @addtogroup BLISPLIB Firmware Update Library
  @{
*/

#ifdef __cplusplus
extern "C"
{
#endif

/** @addtogroup BLISPLIB_EXPORTED_FUNCTIONS Firmware Update Library Exported Functions
  @{
*/

/**
  * @brief UART1 Interrupt Handler
  *        Secure boot firmware update need use interrupt, this API is used to remap
  *        UART1 IRQHandler to MKROM UART1 IRQHandler
  */
void UART1_ISR(void);

/**
  * @brief UART1 ISP function
  *        This function will connect with MKROM ISP tool. And ISP tool will send command through UART1
  *        to this function to do firmware update.
  */
void UART1_ISP(void);

/**
  * @brief HSUSBD Interrupt Handler
  *        Secure boot firmware update need use interrupt, this API is used to remap
  *        HSUSBD IRQHandler to MKROM HSUSBD IRQHandler
  */
void HSUSBD_ISR(void);

/**
  * @brief HSUSBD ISP function
  *        This function will connect with MKROM ISP tool. And ISP tool will send command through HSUSBD
  *        to this function to do firmware update.
  */
void HSUSBD_ISP(void);


#ifdef __cplusplus
}
#endif

#endif /* __BLISPLIB_H__ */

/*@}*/ /* end of group BLISPLIB_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group BLISPLIB */

/*@}*/ /* end of group LIBRARY */

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/

