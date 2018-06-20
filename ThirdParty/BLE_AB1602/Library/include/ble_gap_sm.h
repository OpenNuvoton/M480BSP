/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    ble_gap_sm.h
DESCRIPTION
NOTES
********************************************************************************/

#ifndef __BLE_GAP_SM_H__
#define __BLE_GAP_SM_H__

#include "ble_gap.h"

/*! 
     
     @defgroup PAGE_BLE_GAP_SM ble_gap_sm.h
     @{
        @page PAGE_BLE_GAP_SM ble_gap_sm.h

        ble_gap_sm.h provides security manger related GAP APIs for feature defined in BLE spec.<br>
        The red circle was added in 1.0.4 version.
        \anchor sm_104
        \image html sm_1_0_4.png
        
*/

/******************************************************************************
 * Macro Definition
 ******************************************************************************/

/*!
     @name SM_IO_CAPABILITY
     @{
         IO capability used to assign @ref ble_sm_security_param_t.ioCapability .
 */
#define SM_IO_DISPLAY_ONLY          0x00
#define SM_IO_DISPLAY_YES_NO		0x01
#define SM_IO_KEYBOARD_ONLY         0x02	
#define SM_IO_NO_INPUT_NO_OUTPUT    0x03
#define SM_IO_KEYBOARD_DISPLAY      0x04
/*!
     @}
*/

/*!
     @name SM_OOB_DATA_FLAG
     @{
         Out of band data flag used to assign @ref ble_sm_security_param_t.oobData .
 */
#define SM_OOB_DATA_NOT_PRESENT    0x00
#define SM_OOB_DATA_FROM_REMOTE    0x01
/*!
     @}
*/

/*!
     @name SM_BONDING_FLAG
     @{
        Bonding flag used to assign @ref ble_sm_security_param_t.authReq .
 */
#define SM_NO_BONDING                   0x00
#define SM_BONDING                      0x01
/*!
     @}
*/

/*!
     @name SM_MITM_FLAG
     @{
        Man in the middle protection flag used to assign @ref ble_sm_security_param_t.authReq .
 */
#define SM_NO_MITM_PROTECTION           0x00
#define SM_MITM_PROTECTION              0x04
/*!
     @}
*/

/*!
     @name SM_SC_FLAG
     @{
        Secure connection flag used to assign @ref ble_sm_security_param_t.authReq .
 */
#define SM_SC_DISABLE                   0x00
#define SM_SC_ENABLE                    0x08
/*!
     @}
*/

/*!
     @name SM_KEYPRESS_FLAG
     @{
        Keypress notifications flag used to assign @ref ble_sm_security_param_t.authReq .
 */
#define SM_KEY_PRESS_NOTI_DISABLE       0x00
#define SM_KEY_PRESS_NOTI_ENABLE        0x10
/*!
     @}
*/

/*!
    Press-key notification type.
*/
typedef enum
{
    bt_sm_passkey_started = 0,      /*!< User started entering passkey.*/
    bt_sm_passkey_digit_entered,    /*!< User entered digit.*/
    bt_sm_passkey_digit_erased,     /*!< User erased digit.*/
    bt_sm_passkey_cleared,          /*!< User cleared entire passkey.*/
    bt_sm_passkey_complete          /*!< User completed passkey entry.*/
}ble_sm_keypress_type;

/*!
    @brief Parameters for @ref BLE_gap_sm_set_security_param function.
*/
typedef struct
{
    uint8_t ioCapability;           /*! IO capability.*/
    uint8_t oobData;                /*! OOB data flag.*/
    uint8_t authReq;                /*! AuthReq field.*/
    uint8_t maxKeySize;             /*! Maximum encryption key size. Key size between 7 to 16.*/
    uint8_t initKeyDistr;           /*! Initiator key distribution/generation.*/
    uint8_t respKeyDistr;           /*! Responder key distribution/generation.*/
}ble_sm_security_param_t;


/*************************************************************************
* API
*************************************************************************/
/*!
    @brief To start authentication procedure.
    @param conn_handle connection handle.
    @param param security parameter format @ref ble_sm_security_param_t.
    @return bool : whether authentication command is sent successfully.
*/
bool BLE_gap_sm_authenticate(uint16_t conn_handle, ble_sm_security_param_t *param);

/*!
    @brief To set security parameter for pairing information exchange.
    @param conn_handle connection handle.
    @param status security status.
    @param param security parameter format @ref ble_sm_security_param_t.
*/
bool BLE_gap_sm_set_security_param(uint16_t conn_handle, uint8_t status, ble_sm_security_param_t *param);

/*!
    @brief To delete bonded device information in flash.
    @param addr BD addr to be deleted or NULL for all record.
*/
bool BLE_gap_sm_delete_paired_record(ble_addr_t *addr);

/*!
    @brief To check if device information exists in flash.
    @param addr BD addr to be checked or NULL for any record.
    @param flashIdx flash index.
    @return true : device is bonded
    @return false : device is not bonded
*/
bool BLE_gap_sm_is_device_bonded(ble_addr_t *addr, uint8_t *flashIdx);

/*!
    @brief To obtain last paired device information in flash.
    @param addr BD addr of last paired device.
    @return true : last device exists
    @return false : last device does not exist
*/
bool BLE_gap_sm_get_last_paired_device(ble_addr_t *addr);

/*!
    @brief To set passkey for display, security manager will use 000000 as default if passkey is not set.
    @param passkey Passkey display value
*/
bool BLE_gap_sm_set_passkey_for_display(uint32_t passkey);

/*!
    @brief To send passkey input to security manager.
    @param conn_handle connection handle.
    @param passkey Passkey input value
*/
bool BLE_gap_sm_passkey_response(uint16_t conn_handle, uint32_t passkey);

/*!
    @brief To send a key notification command.
    @param conn_handle connection handle.
    @param type key type @ref ble_sm_keypress_type.
*/
bool BLE_gap_sm_send_keypress_notification_request(uint16_t conn_handle, ble_sm_keypress_type type);

/*!
    @brief Get LTK in flash by peer address.
    @param peerAddr peer address.
    @param ltk 16-byte long term key.
*/
bool BLE_gap_sm_get_ltk(uint8_t *peerAddr, uint8_t *ltk);

/*!
    @brief Get peer LTK in flash by peer address.
    @param peerAddr peer address.
    @param peerLtk 16-byte peer long term key.
*/
bool BLE_gap_sm_get_peer_ltk(uint8_t *peerAddr, uint8_t *peerLtk);

/*!
    @}
*/

#endif
