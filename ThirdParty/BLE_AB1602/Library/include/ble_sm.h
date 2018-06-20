/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME
    ble_sm.h
DESCRIPTION
NOTES
********************************************************************************/

#ifndef __BLE_SM_H__
#define __BLE_SM_H__

/*!

     @defgroup PAGE_SecurityManager ble_sm.h
     @{
        @page PAGE_SecurityManager ble_sm.h
        ble_sm.h provides security manger APIs as defined in BLE spec.

*/

#include "bt_constants.h"


/******************************************************************************
 * Macros
 ******************************************************************************/
/*!
     @name Defined values
     @{
*/
#define SM_PASSKEY_MAX_BYTE_LEN	    3
/*!
    @}
*/

/*!
     @name BLE_SM_STATUS
     @anchor BLE_SM_STATUS
     @{
*/
#define BLE_SM_STATUS_SUCCESS                         0x00
#define BLE_SM_STATUS_TIMEOUT                         0x01
#define BLE_SM_STATUS_LINK_DISCONNECTED               0x02
#define BLE_SM_STATUS_LTK_NEGATIVE                    0x03
#define BLE_SM_STATUS_RFU_RANGE1_BEGIN                0x04
#define BLE_SM_STATUS_RFU_RANGE1_END                  0x80

#define BLE_SM_STATUS_PAIRING_FAIL_REASON_MASK        0x80
#define BLE_SM_STATUS_PASSKEY_ENTRY_FAILED            0x81
#define BLE_SM_STATUS_OOB_NOT_AVAILABLE               0x82
#define BLE_SM_STATUS_AUTHENTHICATION_REQUIREMENTS    0x83
#define BLE_SM_STATUS_CONFIRM_VALUE                   0x84
#define BLE_SM_STATUS_PAIRING_NOT_SUPPORTED           0x85
#define BLE_SM_STATUS_ENCRYPTION_KEY_SIZE             0x86
#define BLE_SM_STATUS_COMMAND_NOT_SUPPORTED           0x87
#define BLE_SM_STATUS_UNSPECIFIED_REASON              0x88
#define BLE_SM_STATUS_REPEATED_ATTEMPTS               0x89
#define BLE_SM_STATUS_INVALID_PARAMETERS              0x8A
#define BLE_SM_DHKEY_CHECK_FAILED                     0x8B
#define BLE_SM_NUMERIC_COMPARISON_FAILED              0x8C
#define BLE_SM_BR_EDR_PAIRING_IN_PROGRESS             0x8D
#define BLE_SM_CROSS_TRANSPORT_KEY_NOT_ALLOWED        0x8E
#define BLE_SM_STATUS_RFU_RANGE2_BEGIN                0x8F
#define BLE_SM_STATUS_RFU_RANGE2_END                  0xFF

/*!
    @}
*/

/*!
     @name Key type
     @{
*/
#define BLE_GAP_AUTH_KEY_TYPE_NONE     0x00
#define BLE_GAP_AUTH_KEY_TYPE_PASSKEY  0x01
#define BLE_GAP_AUTH_KEY_TYPE_OOB      0x02
/*!
    @}
*/

#ifdef _MSC_VER
__pragma(pack(push, 1))
#define __attribute__(x)
#endif


/*!
    @brief Event structure for @ref BLE_SM_EVT_PASSKEY_DISPLAY.
*/
typedef struct
{
  uint8_t passkey[SM_PASSKEY_MAX_BYTE_LEN];         /**< 6-digit passkey in ASCII ('0'-'9' digits only). */
  uint8_t match_request;
} __attribute__((packed)) ble_sm_evt_passkey_display_t;

/*!
    @brief Connection security modes.
 *
 * Security Mode 0 Level 0: No access permissions at all (this level is not defined by the Bluetooth Core specification).\n
 * Security Mode 1 Level 1: No security is needed (aka open link).\n
 * Security Mode 1 Level 2: Encrypted link required, MITM protection not necessary.\n
 * Security Mode 1 Level 3: MITM protected encrypted link required.\n
 * Security Mode 1 Level 4: LESC MITM protected encrypted link required.\n
 * Security Mode 2 Level 1: Signing or encryption required, MITM protection not necessary.\n
 * Security Mode 2 Level 2: MITM protected signing required, unless link is MITM protected encrypted.\n
 */

/*!
    @brief Connection security status.
*/
typedef struct
{
  uint8_t sm : 4;                     /**< Security Mode (1 or 2), 0 for no permissions at all. */
  uint8_t lv : 4;                     /**< Level (1, 2 or 3), 0 for no permissions at all. */
  uint8_t encr_key_size;      /**< Length of currently active encryption key, 7 to 16 octets (only applicable for bonding procedures). */
} __attribute__((packed)) ble_sm_conn_sec_t;

/*!
    @brief Event structure for @ref BLE_SM_EVT_AUTH_STATUS.
*/
typedef struct
{
  uint8_t auth_status;            /**< Authentication status, see @ref BLE_SM_STATUS. */
} __attribute__((packed)) ble_sm_evt_auth_status_t;

/*!
    @brief Event structure for @ref BLE_SM_EVT_SEC_REQUEST.
*/
typedef struct
{
  uint8_t    bond    : 1;                       /**< Perform bonding. */
  uint8_t    mitm    : 1;                       /**< Man In The Middle protection required. */
} __attribute__((packed)) ble_sm_evt_sec_request_t;

/*!
    @brief Event structure for @ref BLE_SM_EVT_CONN_SEC_UPDATE.
*/
typedef struct
{
  ble_sm_conn_sec_t conn_sec;                  /**< Connection security level. */
  uint8_t    status;                           /**< HCI error code */
} __attribute__((packed)) ble_sm_evt_conn_sec_update_t;

/*!
    @brief Event structure for @ref BLE_SM_EVT_AUTH_KEY_REQUEST.
*/
typedef struct
{
  uint8_t keyType;                             /**< Key type. */
} __attribute__((packed)) ble_sm_evt_auth_key_request_t;

/*!
    @brief LE SC OOB data structure.
*/
typedef struct
{
  uint8_t r[BLE_GAP_SEC_KEY_LEN];     /**< Random number. */
  uint8_t c[BLE_GAP_SEC_KEY_LEN];     /**< Confirm value. */
}__attribute__((packed)) ble_lesc_oob_data_t;

/*!
    @brief Event structure.
*/
typedef struct
{
    uint16_t connHdl;                           /**< Connection handle. */
    union                                       /**< union alternative identified by evt_id in enclosing struct. */
    {
        ble_sm_evt_passkey_display_t            passkey_display;            /**< Passkey Display Event Parameters. */
        ble_sm_evt_conn_sec_update_t            conn_sec_update;            /**< Connection Security Update Event Parameters. */
        ble_sm_evt_auth_key_request_t           auth_key_request;           /**< Authentication Key Request Event Parameters. */
        ble_sm_evt_auth_status_t                auth_status;                /**< Authentication Status Event Parameters. */
        ble_sm_evt_sec_request_t                sec_request;                /**< Security Request Event Parameters. */
        ble_lesc_oob_data_t                     oob_data_response;          /**< OOB data response. */
    } __attribute__((packed)) params;                                                               /**< Event Parameters. */
}__attribute__((packed)) ble_sm_evt_t;

#ifdef _MSC_VER
__pragma(pack(pop))
#undef __attribute__
#endif

/*!
    @brief Security manager event ID.
*/
typedef enum
{
    BLE_SM_EVT_SET_SEC_PARAM_REQUEST = BT_EVENT_SM,     /**< Event for requesting security parameter. */
    BLE_SM_EVT_PASSKEY_DISPLAY,                         /**< Event for passkey display. */
    BLE_SM_EVT_AUTH_KEY_REQUEST,                        /**< Event for requesting passkey or OOB data. */
    BLE_SM_EVT_CONN_SEC_UPDATE,                         /**< Event for updating security level of current connection. */
    BLE_SM_EVT_AUTH_STATUS,                             /**< Event for authorization status. */
    BLE_SM_EVT_SEC_REQUEST,                             /**< Event for requesting authorization. */
    BLE_SM_EVT_OOB_DATA_RESPONSE,                       /**< Event for response of OOB data. */
}ble_sm_event_id;

/*!
    @}
*/


#endif
