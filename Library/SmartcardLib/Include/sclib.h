/**************************************************************************//**
 * @file     sclib.h
 * @version  V1.00
 * @brief    Smartcard library header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __SCLIB_H__
#define __SCLIB_H__

#include "NuMicro.h"

/** @addtogroup LIBRARY Library
  @{
*/

/** @addtogroup SCLIB Smartcard Library
  @{
*/

/** @addtogroup SCLIB_EXPORTED_CONSTANTS Smartcard Library Exported Constants
  @{
*/


#ifdef __cplusplus
extern "C"
{
#endif

#define SCLIB_MAX_ATR_LEN                               32UL  /*!< Max ATR length. ISO-7816 8.2.1  \hideinitializer */
#define SCLIB_MIN_ATR_LEN                                2UL  /*!< Min ATR length, TS and T0       \hideinitializer */

/* Protocol */
#define SCLIB_PROTOCOL_UNDEFINED                0x00000000UL  /*!< There is no active protocol.    \hideinitializer */
#define SCLIB_PROTOCOL_T0                       0x00000001UL  /*!< T=0 is the active protocol.     \hideinitializer */
#define SCLIB_PROTOCOL_T1                       0x00000002UL  /*!< T=1 is the active protocol.     \hideinitializer */

#define SCLIB_SUCCESS                           0x00000000UL  /*!< Command successful without error \hideinitializer */
/* error code generate by interrupt handler */
#define SCLIB_ERR_CARD_REMOVED                  0x00000001UL  /*!< Smartcard removed               \hideinitializer */
#define SCLIB_ERR_OVER_RUN                      0x00000002UL  /*!< Rx FIFO over run                \hideinitializer */
#define SCLIB_ERR_PARITY_ERROR                  0x00000003UL  /*!< Tx/Rx parity error              \hideinitializer */
#define SCLIB_ERR_NO_STOP                       0x00000004UL  /*!< Stop bit not found              \hideinitializer */
#define SCLIB_ERR_SILENT_BYTE                   0x00000005UL  /*!< I/O pin stay at low for longer than 1 character time \hideinitializer */
/*//#define SCLIB_ERR_CMD                           0x00000006UL */
/*//#define SCLIB_ERR_UNSUPPORTEDCARD               0x00000007UL */
#define SCLIB_ERR_READ                          0x00000008UL  /*!< Smartcard read error            \hideinitializer */
#define SCLIB_ERR_WRITE                         0x00000009UL  /*!< Smartcard write error           \hideinitializer */
#define SCLIB_ERR_TIME0OUT                      0x0000000AUL  /*!< Smartcard timer 0 timeout       \hideinitializer */
#define SCLIB_ERR_TIME1OUT                      0x0000000BUL  /*!< Smartcard timer 1 timeout       \hideinitializer */
#define SCLIB_ERR_TIME2OUT                      0x0000000CUL  /*!< Smartcard timer 2 timeout       \hideinitializer */
#define SCLIB_ERR_AUTOCONVENTION                0x0000000DUL  /*!< Smartcard is neither direct nor inverse convention \hideinitializer */
#define SCLIB_ERR_CLOCK                         0x0000000EUL  /*!< Smartcard clock frequency is not between 1MHz and 5 MHz \hideinitializer */
/*//#define SCLIB_ERR_BGTIMEOUT                     0x0000000EUL */
/* error code generate while parsing ATR and process PPS */
#define SCLIB_ERR_ATR_UNRECOGNIZED              0x00001001UL  /*!< Unrecognized ATR                \hideinitializer */
#define SCLIB_ERR_ATR_INVALID_PARAM             0x00001002UL  /*!< ATR parsing interface bytes error \hideinitializer */
#define SCLIB_ERR_ATR_INVALID_TCK               0x00001003UL  /*!< TCK check byte error            \hideinitializer */
#define SCLIB_ERR_PPS                           0x00001004UL  /*!< PPS error                       \hideinitializer */
/* error code for T=1 protocol */
/*#define SCLIB_ERR_T1_PARITY                     0x00002001UL  ///< T=1 Parity Error Notice          */
/*#define SCLIB_ERR_T1_ICC                        0x00002002UL  ///< ICC communication error          */
#define SCLIB_ERR_T1_PROTOCOL                   0x00002003UL  /*!< T=1 Protocol Error              \hideinitializer */
#define SCLIB_ERR_T1_ABORT_RECEIVED             0x00002004UL  /*!< Received ABORT request          \hideinitializer */
#define SCLIB_ERR_T1_RESYNCH_RECEIVED           0x00002005UL  /*!< Received RESYNCH request        \hideinitializer */
#define SCLIB_ERR_T1_VPP_ERROR_RECEIVED         0x00002006UL  /*!< Received VPP error              \hideinitializer */
#define SCLIB_ERR_T1_WTXRES_RECEIVED            0x00002007UL  /*!< Received BWT extension request  \hideinitializer */
#define SCLIB_ERR_T1_IFSRES_RECEIVED            0x00002008UL  /*!< Received max IFS offer          \hideinitializer */
#define SCLIB_ERR_T1_ABORTRES_RECEIVED          0x00002009UL  /*!< Received ABORT response         \hideinitializer */
#define SCLIB_ERR_T1_CHECKSUM                   0x0000200AUL  /*!< T=1 block check sum error       \hideinitializer */

/* error code for T=0 protocol */
#define SCLIB_ERR_T0_PROTOCOL                   0x00003003UL  /*!< T=0 Protocol Error              \hideinitializer */

/* error code indicates application control flow error */
#define SCLIB_ERR_DEACTIVE                      0x0000F001UL  /*!< Smartcard is deactivate         \hideinitializer */
#define SCLIB_ERR_CARDBUSY                      0x0000F002UL  /*!< Smartcard is busy, previous transmission is not complete yet \hideinitializer */

/*@}*/ /* end of group SCLIB_EXPORTED_CONSTANTS */

/** @addtogroup SCLIB_EXPORTED_STRUCTS Smartcard Library Exported Structs
  @{
*/

/**
  * @brief  A structure holds smartcard information
  */
typedef struct
{
    uint32_t T;                         /*!< Protocol, ether \ref SCLIB_PROTOCOL_T0 or \ref SCLIB_PROTOCOL_T1.  */
    uint32_t ATR_Len;                   /*!< ATR length, between SCLIB_MAX_ATR_LEN and SCLIB_MIN_ATR_LEN.       */
    uint8_t ATR_Buf[SCLIB_MAX_ATR_LEN]; /*!< Buffer holds ATR answered by smartcard.                            */
} SCLIB_CARD_INFO_T;

/*@}*/ /* end of group SCLIB_EXPORTED_STRUCTS */

/** @addtogroup SCLIB_EXPORTED_FUNCTIONS Smartcard Library Exported Functions
  @{
*/

/**
  * @brief Activate a smartcard
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @param[in] u32EMVCheck Enable EMV error check or not. Valid setting are \ref TRUE and \ref FALSE.
  *            By enable EMV error checking, this library will perform ATR checking according to
  *            EMV book 1 specification. Otherwise, the error checking follows ISO 7816-3
  * @return Smartcard successfully activated or not
  * @retval SCLIB_SUCCESS Smartcard activated successfully
  * @retval Others Smartcard activation failed
  * @note It is required to set smartcard interface clock between 1 MHz and 5 MHz before
  *       calling this API, otherwise this API return with \ref SCLIB_ERR_CLOCK error code.
  * @note EMV book 1 is stricter than ISO-7816 on ATR checking. Enable EMV check iff the
  *       application supports EMV cards only.
  * @note If EMVCheck is set \ref TRUE, this API will call \ref SCLIB_SetIFSD to set IFSD if necessary.
  */
int32_t SCLIB_Activate(uint32_t num, uint32_t u32EMVCheck);

/**
  * @brief Activate a smartcard with large delay between set VCC high and start CLK output
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @param[in] u32EMVCheck Enable EMV error check or not. Valid setting are \ref TRUE and \ref FALSE.
  *            By enable EMV error checking, this library will perform ATR checking according to
  *            EMV book 1 specification. Otherwise, the error checking follows ISO 7816-3
  * @param[in] u32Delay Extra delay time between set VCC high and start CLK output, using ETU as time unit.
  * @return Smartcard successfully activated or not
  * @retval SCLIB_SUCCESS Smartcard activated successfully
  * @retval Others Smartcard activation failed
  * @note It is required to set smartcard interface clock between 1 MHz and 5 MHz before
  *       calling this API, otherwise this API return with \ref SCLIB_ERR_CLOCK error code.
  * @note EMV book 1 is stricter than ISO-7816 on ATR checking. Enable EMV check iff the
  *       application supports EMV cards only.
  * @note If EMVCheck is set \ref TRUE, this API will call \ref SCLIB_SetIFSD to set IFSD if necessary.
  * @note Only use this function instead of \ref SCLIB_Activate if there's large capacitor on VCC pin and
  *       VCC raise slowly.
  */
int32_t SCLIB_ActivateDelay(uint32_t num, uint32_t u32EMVCheck, uint32_t u32Delay);



/**
  * @brief Cold reset a smartcard
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @return Smartcard cold reset success or not
  * @retval SCLIB_SUCCESS Smartcard cold reset success
  * @retval Others Smartcard cold reset failed
  */
int32_t SCLIB_ColdReset(uint32_t num);

/**
  * @brief Warm reset a smartcard
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @return Smartcard warm reset success or not
  * @retval SCLIB_SUCCESS Smartcard warm reset success
  * @retval Others Smartcard warm reset failed
  */
int32_t SCLIB_WarmReset(uint32_t num);

/**
  * @brief Deactivate a smartcard
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @return None
  */
void SCLIB_Deactivate(uint32_t num);

/**
  * @brief Get the card information (e.g., protocol selected, ATR...) after activation success
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @param[out] s_info A pointer to \ref SCLIB_CARD_INFO_T holds the card information
  * @return Success or not
  * @retval SCLIB_SUCCESS              Success, s_info contains card information
  * @retval SCLIB_ERR_CARD_REMOVED     Card removed, s_info does not contains card information
  * @retval SCLIB_ERR_DEACTIVE         Card is deactivated, s_info does not contains card information
  */
int32_t SCLIB_GetCardInfo(uint32_t num, SCLIB_CARD_INFO_T *s_info);

/**
  * @brief Start a smartcard transmission.
  * @details SCLIB will start a transmission according to the protocol selected
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @param[in] cmdBuf Command buffer pointer
  * @param[in] cmdLen Command length
  * @param[out] rspBuf Buffer to holds card response
  * @param[out] rspLen Response length received
  * @return Smartcard transmission success or failed
  * @retval SCLIB_SUCCESS Transmission success. rspBuf and rspLen holds response data and length
  * @retval Others Transmission failed
  * @note This API supports case 1, 2S, 3S, and 4S defined in ISO-7816, but does \b NOT support case 2E, 3E, and 4E.
  */
int32_t SCLIB_StartTransmission(uint32_t num, uint8_t *cmdBuf, uint32_t cmdLen, uint8_t *rspBuf, uint32_t *rspLen);

/**
  * @brief Set interface device max information field size (IFSD)
  * @details This function sends S block to notify card about the max size of information filed blocks that
  *          can be received by the interface device. According to EMV 9.2.4.3, this should be the first
  *          block transmitted by terminal to ICC after ATR.
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @param[in] size IFSD size. According to EMV spec 9.2.4.3 Error Free Operation, this field must be 0xFE.
  * @return Smartcard transmission success or failed
  * @retval SCLIB_SUCCESS Smartcard warm reset success
  * @retval Others Smartcard warm reset failed
  */
int32_t SCLIB_SetIFSD(uint32_t num, uint8_t size);


/**
  * @brief  A callback called by library while smartcard request for a time extension
  * @param[in]  u32Protocol What protocol the card is using while it requested for a time extension.
  *                     Could be ether \ref SCLIB_PROTOCOL_T0 or \ref SCLIB_PROTOCOL_T1
  * @return None
  * @note   This function is defined with __weak attribute and does nothing in library.
  *         Application can provide its own time extension function. For example, and CCID reader
  *         can use this function to report this status to PC. See CCID rev 1.1 Table 6.2-3
  */
#if defined (__GNUC__)
void SCLIB_RequestTimeExtension () __attribute__ ((weak));
void SCLIB_RequestTimeExtension(uint32_t u32Protocol);
#else
__weak void SCLIB_RequestTimeExtension(uint32_t u32Protocol);
#endif
/**
  * @brief Process card detect event in IRQ handler
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @return Card detect event occur or not
  * @retval 1 Card detect event occurred
  * @retval 0 Card detect event did not occur
  * @note Smartcard IRQ handler shall call this function with correct interface number as parameter
  */
uint32_t SCLIB_CheckCDEvent(uint32_t num);

/**
  * @brief Process time out event in IRQ handler
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @return Time out event occur or not
  * @retval 1 Time out event occurred
  * @retval 0 Time out event did not occur
  * @note Smartcard IRQ handler shall call this function with correct interface number as parameter
  */
uint32_t SCLIB_CheckTimeOutEvent(uint32_t num);

/**
  * @brief Process card transmission event in IRQ handler
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @return Transmission event occur or not
  * @retval 1 Transmission event occurred
  * @retval 0 Transmission event did not occur
  * @note Smartcard IRQ handler shall call this function with correct interface number as parameter
  */
uint32_t SCLIB_CheckTxRxEvent(uint32_t num);

/**
  * @brief Process error event in IRQ handler
  * @param[in] num Smartcard interface number. From 0 ~ ( \ref SC_INTERFACE_NUM - 1)
  * @return Error event occur or not
  * @retval 1 Error event occurred
  * @retval 0 Error event did not occur
  * @note Smartcard IRQ handler shall call this function with correct interface number as parameter
  */
uint32_t SCLIB_CheckErrorEvent(uint32_t num);


#ifdef __cplusplus
}
#endif

#endif /* __SCLIB_H__ */

/*@}*/ /* end of group SCLIB_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SCLIB */

/*@}*/ /* end of group LIBRARY */

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
