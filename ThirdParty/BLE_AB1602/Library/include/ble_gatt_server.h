/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    ble_gatt_server.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef _BLE_GATT_SERVER_H_
#define _BLE_GATT_SERVER_H_

/*!

     @defgroup PAGE_BLE_GATT_SERVER ble_gatt_server.h
     @{
        @page PAGE_BLE_GATT_SERVER ble_gatt_server.h
        ble_gatt_server.h provides simple API for implementing GATT profiles as the server role.
        The hierarchical structure is directly decided by the order of API calling.
*/

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "ble_att.h"


/*!
    @brief GATT service type.
*/
typedef enum
{
    primary_service     = 0x2800,   /**<0x2800*/
    secondary_service   = 0x2801,   /**<0x2801*/
}service_type;

/*!
    @brief GATT Notification/Indication target link selection.

    CCCD stands for Client Characteristic Configuration Descriptor.
*/
typedef enum
{
    FORCE_LINK0 = 0,                /**< Send to link0, ignore CCCD value*/
    FORCE_LINK1,                    /**< Send to link1, ignore CCCD value*/
    FORCE_LINK2,                    /**< Send to link2, ignore CCCD value*/
    FORCE_LINK3,                    /**< Send to link3, ignore CCCD value*/
    FORCE_LINK4,                    /**< Send to link4, ignore CCCD value*/
    FORCE_LINK5,                    /**< Send to link5, ignore CCCD value*/
    FORCE_LINK6,                    /**< Send to link6, ignore CCCD value*/
    FORCE_LINK7,                    /**< Send to link7, ignore CCCD value*/

    ALL_CCCD_ENABLED_LINK = 0x99,   /**< Send to all links with valid CCCD value */
}NOTIFY_INDICATE_LINK_SEL;


/*!
     @brief GATT characteristic Property.
 */
typedef enum
{
    C_BCAST            = 0x01,
    C_READ             = 0x02,
    C_WRITE_NO_RSP     = 0x04,
    C_WRITE            = 0x08,
    C_NOTIFY           = 0x10,
    C_INDICATE         = 0x20,
    C_AUTHEN           = 0x40,
    C_EXTENDED         = 0x80,
}CHAR_PROPERTY;

/*!
     @brief API parameter for creating a GATT service.
 */
typedef struct
{
    service_type type;              /**< service type*/
    UUID_size    size;              /**< service UUID size*/
    uint8_t      UUID[16];          /**< service UUID*/
}gatt_add_service_para;

/*!
     @brief API parameter for including a GATT service in another.
 */
typedef struct
{
    att_handle service_handle;      /**< service declaration attribute handle*/
}gatt_add_include_para;

/*!
     @brief API parameter for creating a GATT characteristic.
 */
typedef struct
{
    UUID_size    size;                  /**< characteristic UUID size*/
    uint8_t      UUID[16];              /**< characteristic UUID*/
    uint8_t      property;              /**< characteristic property @ref CHAR_PROPERTY */
    uint8_t      permission;            /**< characteristic value attribute access permission */
    uint16_t     data_initial_length;   /**< characteristic value attribute default length */
    uint16_t     data_maximum_length;   /**< characteristic value attribute maximum length, 0 indicates its a fixed length attribute */
    uint8_t *    char_data;             /**< characteristic value data pointer */
    ATTCB        cb;                    /**< characteristic value call back function */
}gatt_add_charact_para;

/*!
     @brief API parameter for creating a GATT characteristic descriptor.
 */
typedef struct
{
    UUID_size    size;                  /**< descriptor UUID size*/
    uint8_t      UUID[16];              /**< descriptor UUID*/
    uint8_t      permission;            /**< descriptor attribute access permission */
    uint16_t     data_initial_length;   /**< descriptor attribute default length */
    uint16_t     data_maximum_length;   /**< descriptor attribute maximum length, 0 indicates its a fixed length attribute */
    uint8_t *    desc_data;             /**< descriptor data pointer */
    ATTCB        cb;                    /**< descriptor call back function */
}gatt_add_descrip_para;

/*!
     @brief API for adding a GATT Service declaration into the attribute server database.

     @param para @ref gatt_add_service_para
     @return The attribute handle of service declaration within the attribute server database.

     @attention Service declaration should always be the first attribute in the database.
 */
att_handle BLE_gatt_add_service(gatt_add_service_para * para);

/*!
     @brief API for including another GATT Service in last added service.

     @param para @ref gatt_add_include_para
     @return The attribute handle of include declaration within the attribute server database.

     @attention The included service should have smaller attribute handle to avoid circular including.
 */
att_handle BLE_gatt_add_include(gatt_add_include_para * para);

/*!
     @brief API for declaring a GATT Characteristic in last added service.

     @param para @ref gatt_add_charact_para
     @return The attribute handle of characteristic value within the attribute server database.
 */
att_handle BLE_gatt_add_charact(gatt_add_charact_para * para);

/*!
     @brief API for declaring a GATT descriptor in last added characteristic.

     @param para @ref gatt_add_charact_para
     @return The attribute handle of descriptor within the attribute server database.
 */
att_handle BLE_gatt_add_descrip(gatt_add_descrip_para * para);


/*!
     @brief API for sending a characteristic value notification to the selected target(s).

     @param char_handle attribute handle of characteristic value.
     @param sel @ref NOTIFY_INDICATE_LINK_SEL
 */
void BLE_gatt_charact_notify(att_handle char_handle, NOTIFY_INDICATE_LINK_SEL sel);

/*!
     @brief API for sending a characteristic value indication to the selected target(s).

     @param char_handle attribute handle of characteristic value.
     @param sel @ref NOTIFY_INDICATE_LINK_SEL
     @param cb  @ref INDI_CB

     @return 0: indication successfully sent.\n 1: failed to send indication, previous transaction not finished yet.
 */
bool BLE_gatt_charact_indicate(att_handle char_handle, NOTIFY_INDICATE_LINK_SEL sel, INDI_CB cb);

/*!
    @}
*/
#endif
