/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    ble_att.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef _ATT_H_ 
#define _ATT_H_

/*!

     @defgroup PAGE_BLE_ATT ble_att.h
     @{
        @page PAGE_BLE_ATT ble_att.h
        ble_att.h specifies attribute protocol related API and parameter definition.
*/


#include <stdint.h>

/*!
     @brief attribute protocol error code
 */
//ATT Error Code==============================================================
#define ATT_NOERR                        0x00
#define ATT_ERR_INVALID_HANDLE           0x01
#define ATT_ERR_READ_NOT_PERMITTED       0x02
#define ATT_ERR_WRITE_NOT_PERMITTED      0x03
#define ATT_ERR_INVALID_PDU              0x04
#define ATT_ERR_INSUFFICIENT_AUTHEN      0x05
#define ATT_ERR_UNSUPPORTED_REQ          0x06
#define ATT_ERR_INVALID_OFFSET           0x07
#define ATT_ERR_INSUFFICIENT_AUTHOR      0x08
#define ATT_ERR_PREPARE_QUEUE_FULL       0x09
#define ATT_ERR_ATTR_NOT_FOUND           0x0A
#define ATT_ERR_ATTR_NOT_LONG            0x0B
#define ATT_ERR_INSUFFICIENT_KEY_SIZE    0x0C
#define ATT_ERR_INVALID_VALUE_LENGTH     0x0D
#define ATT_ERR_UNLIKELY                 0x0E
#define ATT_ERR_INSUFFICIENT_ENCRYPT     0x0F
#define ATT_ERR_UNSUPPORTED_GRP_TYPE     0x10
#define ATT_ERR_INSUFFICIENT_RESOURCES   0x11
//reserved 0x12-0x7F

//end ATT Error Code==========================================================

/*!
     @brief attribute handle.
 */
typedef uint16_t att_handle;


/*!
    @brief UUID size in bytes.
*/
typedef enum
{
    UUID_16bit          = 2,        /**< 2 bytes*/
    UUID_128bit         = 16,       /**<16 bytes*/
}UUID_size;



typedef enum
{
    CB_BEFORE_SENDING = 0x01,
    CB_AFTER_WRITING  = 0x02,
} ATT_CB_TYPE;

typedef enum {
    ATT_R_PERMIT    = 0x00,         /* Always permitted, no restrictions*/
    ATT_R_AUTHEN    = 0x01,         /* Authentication required */
    ATT_R_AUTHOR    = 0x02,         /* Authorization required */
    ATT_R_ENCRYPT   = 0x04,         /* Can only be accessed in encrypted link*/
    ATT_R_BANNED    = 0x08,         /* Operation not permitted */

    ATT_W_PERMIT    = 0x00,         /* Always permitted, no restrictions*/
    ATT_W_AUTHEN    = 0x10,         /* Authentication required */
    ATT_W_AUTHOR    = 0x20,         /* Authorization required */
    ATT_W_ENCRYPT   = 0x40,         /* Can only be accessed in encrypted link*/
    ATT_W_BANNED    = 0x80,         /* Operation not permitted */
} ATT_READ_WRITE_PERMISSION_ENUM;

#define A_RP_WP     (ATT_R_PERMIT|ATT_W_PERMIT)
#define A_RP_WN     (ATT_R_PERMIT|ATT_W_AUTHEN)
#define A_RP_WO     (ATT_R_PERMIT|ATT_W_AUTHOR)
#define A_RP_WB     (ATT_R_PERMIT|ATT_W_BANNED)

#define A_RN_WP     (ATT_R_AUTHEN|ATT_W_PERMIT)
#define A_RN_WN     (ATT_R_AUTHEN|ATT_W_AUTHEN)
#define A_RN_WO     (ATT_R_AUTHEN|ATT_W_AUTHOR)
#define A_RN_WB     (ATT_R_AUTHEN|ATT_W_BANNED)

#define A_RO_WP     (ATT_R_AUTHOR|ATT_W_PERMIT)
#define A_RO_WN     (ATT_R_AUTHOR|ATT_W_AUTHEN)
#define A_RO_WO     (ATT_R_AUTHOR|ATT_W_AUTHOR)
#define A_RO_WB     (ATT_R_AUTHOR|ATT_W_BANNED)

#define A_RB_WP     (ATT_R_BANNED|ATT_W_PERMIT)
#define A_RB_WN     (ATT_R_BANNED|ATT_W_AUTHEN)
#define A_RB_WO     (ATT_R_BANNED|ATT_W_AUTHOR)
#define A_RB_WB     (ATT_R_BANNED|ATT_W_BANNED)

/*!
     @brief attribute value accessed call back function.

     Call back function would be executed if the attribute is read/changed by ATT client.
 */
typedef void (*ATTCB)(ATT_CB_TYPE type, uint8_t linkindex, uint16_t handle);

/*!
     @brief characteristic value indication confirmed call back function.

     Call back function would be executed if indication is confirmed by client.
 */
typedef void (*INDI_CB)(uint8_t link_index);


/*!
    @brief get current length of attribute value
    @param handle @ref att_handle

    @return current length of attribute value. Would return 0xFFFF if attribute handle is not valid.
 */
uint16_t BLE_att_get_attribute_length(att_handle handle);

/*!
    @brief set current length of attribute value
    @param handle @ref att_handle
    @param new_length new length of this attribute. Must < 512.

    @return 0: success 1: attribute handle is not valid.
 */
bool BLE_att_set_attribute_length(att_handle handle, uint16_t new_length);

/*!
    @brief get data pointer of attribute value
    @param handle @ref att_handle

    @return data pointer of attribute value. Would return NULL if attribute handle is not valid.
 */
uint8_t * BLE_att_get_attribute_data_ptr(att_handle handle);

/*!
    @brief set data pointer of attribute value
    @param handle @ref att_handle
    @param new_data_ptr new data pointer of this attribute.

    @return 0: success 1: attribute handle is not valid.
 */
bool BLE_att_set_attribute_data_ptr(att_handle handle, uint8_t *new_data_ptr);

/*!
    @brief Set default MTU
    @param default_mtu Default MTU to be set 
    
*/
void BLE_att_set_default_mtu(uint16_t default_mtu);

/*
    @brief Judge write operaion is finished.
    @param linkidx link index
    @param att_handle attribute handle
    @return true: write is finished. false: some prepared write queued in system.
*/
bool BLE_att_is_write_finished(uint8_t linkidx, uint8_t att_handle);

/*!
    @}
*/
#endif
