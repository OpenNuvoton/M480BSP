/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    bt_constants.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef __BT_ERROR_HH
#define __BT_ERROR_HH
#include <stdint.h>

 /*! 
     
     @defgroup PAGE_API_BT_CONST bt_contants.h
     @{
        @page PAGE_API_BT_CONST bt_contants.h 
        Some global constants through BT core library.
*/

/*************************************************************************
* Typedef
*************************************************************************/

/*!
    @brief BT API execution status.
*/
typedef enum
{
    BT_SUCCESS = 0,  ///< Success.
    BT_ERROR_GENERIC,  ///< Error, commonly.
    BT_ERROR_INVALID_PARM, ///< Error, invalid parameter.
    BT_ERROR_NOT_SUPPORT_YET, ///< Error, not support.
    BT_ERROR_NO_RESOURCE, ///< Error, no resource
}BT_STATUS;

/*!
    @brief Event ID arrangement
*/
typedef enum
{
    BT_EVENT_MISC = 0x0000, ///< MISC event
    BT_EVENT_GAP  = 0x1000, ///< GAP event
    BT_EVENT_SM   = 0x2000, ///< SM event
    BT_EVENT_GATT = 0x3000, ///< GATT event
}BT_EVENT_BASE;


/*!
    @brief Maximal Link number
*/
#define MAX_NUM_LE_LINK      16

/*!
    @brief BLE address byte length
*/
#define BLE_ADDR_LEN      6

/*!
    @brief GAP Security Random Number Length. 
*/
#define BLE_GAP_SEC_RAND_LEN 8

/*!
    @brief GAP Security Key Length. 
*/
#define BLE_GAP_SEC_KEY_LEN 16

/*!
    @brief GAP Passkey Length. 
*/
#define BLE_GAP_PASSKEY_LEN 6

/*!
    @}
*/
#endif
