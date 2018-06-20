/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME
    ble_gatt_client.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef _BLE_GATT_CLIENT_H_
#define _BLE_GATT_CLIENT_H_

/*!

     @defgroup PAGE_BLE_GATT_CLIENT ble_gatt_client.h
     @{
        @page PAGE_BLE_GATT_CLIENT ble_gatt_client.h
        ble_gatt_client.h provides simple API for implementing GATT profiles as the client role.
*/

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include "ble_att.h"
#include "bt_constants.h"

#ifdef _MSC_VER
__pragma(pack(push, 1))
#define __attribute__(x)
#endif


/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_GET_ERROR_RESPONSE_FROM_SERVER
 */
typedef struct
{
    uint8_t err_code;       /**  standard attribute protocol error code returned by gatt server*/
} __attribute__((packed)) ble_gatt_evt_err_rsponse_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_MTU_EXCHANGED
 */
typedef struct
{
    uint16_t new_mtu;       /**  new mtu size negotiated with gatt server*/
    uint16_t conn_handle;   /**  connection handle of this exchanged MTU*/
} __attribute__((packed)) ble_gatt_evt_mtu_exchange_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_PRIM_SERVICE_DISCOVERED
 */
typedef struct
{
    uint8_t num;                    /**   number of services in this event*/
    struct
    {
        uint16_t handle_start;      /**   handle of the first attribute in this service*/
        uint16_t handle_end;        /**   handle of the last attribute in this service*/
        uint8_t  uuid_len;          /**   uuid length of this service */
        uint8_t  uuid[16];          /**   uuid of this service */
    }__attribute__((packed))service[1];
} __attribute__((packed)) ble_gatt_evt_prim_service_discovered_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_UUID_SERVICE_DISCOVERED
 */
typedef struct
{
    uint8_t num;                    /**   number of services in this event*/
    uint8_t uuid_len;               /**   uuid length of these services */
    uint8_t uuid[16];               /**   uuid of these services */
    struct
    {
        uint16_t handle_start;      /**   handle of the first attribute in this service*/
        uint16_t handle_end;        /**   handle of the last attribute in this service*/
    }__attribute__((packed))service[1];
} __attribute__((packed))ble_gatt_evt_uuid_service_discovered_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_INCLUDED_SERVICE_FOUND
 */
typedef struct
{
    uint8_t num;                    /** number of included services in this event  */
    struct
    {
        uint16_t handle;            /**   handle of the include declaration attribute */
        uint16_t service_start;     /**   handle of the first attribute of the included service*/
        uint16_t service_end;       /**   handle of the last attribute of the included service*/
        uint8_t  service_uuid_len;  /**   uuid length of the included service */
        uint8_t  service_uuid[16];  /**   uuid of the included service */
    }__attribute__((packed))include[1];
} __attribute__((packed))ble_gatt_evt_included_service_found_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_SERVICE_CHAR_DISCOVERED
 */
typedef struct
{
    uint8_t num;                    /** number of characteristics in this event  */
    struct
    {
        uint16_t declaration_handle;    /** handle of the characteristic declaration*/
        uint16_t value_handle;          /** handle of the characteristic value */
        uint8_t  property;              /** characteristic property */
        uint8_t  uuid_len;              /** uuid length of the characteristic */
        uint8_t  uuid[16];              /** uuid of the characteristic */
    }__attribute__((packed))charact[1];
} __attribute__((packed))ble_gatt_evt_service_char_discovered_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_UUID_CHAR_DISCOVERED
 */
typedef struct
{
    uint8_t num;                /** number of characteristics in this event  */
    uint8_t uuid_len;           /** uuid length of these characteristics */
    uint8_t uuid[16];           /** uuid of these characteristics */
    struct
    {
        uint16_t declaration_handle;    /** handle of the characteristic declaration*/
        uint16_t value_handle;          /** handle of the characteristic value */
        uint8_t  property;              /** characteristic property */
    }__attribute__((packed))charact[1];
} __attribute__((packed))ble_gatt_evt_uuid_char_discovered_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_CHAR_DESCRIP_DISCOVERED
 */
typedef struct
{
    uint8_t num;                /** number of descriptors in this event  */
    struct
    {
        uint16_t handle;        /** handle of the descriptor */
        uint8_t  uuid_len;      /** uuid length of this descriptor */
        uint8_t  uuid[16];      /** uuid of this descriptor */
    }__attribute__((packed))descrip[1];
} __attribute__((packed))ble_gatt_evt_char_descrip_discovered_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_CHAR_VALUE_READ
 */
typedef struct
{
    uint16_t handle;            /** handle of the characteristic */
    uint16_t len;               /** attribute value length */
    uint8_t  value[1];          /** attribute value */
} __attribute__((packed))ble_gatt_evt_char_value_read_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_UUID_CHAR_READ
 */
typedef struct
{
    uint8_t num;                /** number of characteristics read in this event  */
    uint8_t uuid_len;           /** designated uuid length  */
    uint8_t uuid[16];           /** designated uuid */
    struct
    {
        uint16_t handle;        /** handle of the characteristic */
        uint8_t  len;           /** attribute value length */
        uint8_t  value[19];     /** attribute value (19 bytes at most)*/
    }__attribute__((packed))charact[1];
} __attribute__((packed))ble_gatt_evt_uuid_char_read_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_LONG_CHAR_READ
 */
typedef struct
{
    uint16_t handle;            /** handle of the characteristic */
    uint16_t len;               /** attribute value length */
    uint8_t  value[1];          /** attribute value */
} __attribute__((packed))ble_gatt_evt_long_char_read_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_MULTI_CHAR_READ
 */
typedef struct
{
    uint8_t  num;               /** number of characteristics read in this event  */
    uint16_t handle[5];         /** array of characteristic handle */
    uint16_t len;               /** length of packed characteristic values */
    uint8_t  value[1];          /** packed characteristic values */
} __attribute__((packed))ble_gatt_evt_multi_char_read_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_CHAR_VALUE_WRITTEN
 */
typedef struct
{
    uint16_t handle;            /** handle of the characteristic which was written successfully*/
} __attribute__((packed))ble_gatt_evt_char_value_written_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_LONG_CHAR_WRITTEN
 */
typedef struct
{
    uint16_t handle;            /** handle of the characteristic which was written successfully*/
    uint16_t len;               /** length of data */
} __attribute__((packed))ble_gatt_evt_long_char_written_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_RELIABLE_WRITE_FINISHED
 */
typedef struct
{
    uint8_t is_cancelled;       /** 0: data was written successfully. \n  1: write procedure was canceled since returned data is different from original request*/
    uint8_t num;                /** number of successful writes. */
} __attribute__((packed))ble_gatt_evt_reliable_write_finished_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_CHAR_DESCRIP_READ
 */
typedef struct
{
    uint16_t handle;            /** handle of the descriptor */
    uint16_t len;               /** attribute value length */
    uint8_t  value[1];          /** attribute value */
} __attribute__((packed))ble_gatt_evt_char_descrip_read_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_LONG_DESCRIP_READ
 */
typedef struct
{
    uint16_t handle;            /** handle of the characteristic */
    uint16_t len;               /** attribute value length */
    uint8_t  value[1];          /** attribute value */
} __attribute__((packed))ble_gatt_evt_long_descrip_read_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_CHAR_DESCRIP_WRITTEN
 */
typedef struct
{
    uint16_t handle;            /** handle of the descriptor which was written successfully*/
} __attribute__((packed))ble_gatt_evt_char_descrip_written_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_LONG_DESCRIP_WRITTEN
 */
typedef struct
{
    uint16_t handle;            /** handle of the descriptor which was written successfully*/
    uint16_t len;               /** length of data */
} __attribute__((packed))ble_gatt_evt_long_descrip_written_t;

/*!
     @brief Event parameter of gatt event @ref BLE_GATT_EVT_HANDLE_VALUE_REPORTED
 */
typedef struct
{
    uint16_t conn_handle;       /** connection handle of this report*/
    uint16_t handle;            /** attribute handle of this report */
    uint16_t len;               /** attribute value length */
    uint8_t  value[1];          /** attribute value */
} __attribute__((packed))ble_gatt_evt_handle_value_reported_t;



/*!
    @brief GATT event structure.
*/
typedef struct
{
    union                                                     ///< union alternative identified by evt_id in enclosing struct.
    {
        ble_gatt_evt_err_rsponse_t                err_response;                 ///<  parameter of gatt event @ref BLE_GATT_EVT_GET_ERROR_RESPONSE_FROM_SERVER
        ble_gatt_evt_mtu_exchange_t               mtu_exchanged;                ///<  parameter of gatt event @ref BLE_GATT_EVT_MTU_EXCHANGED
        ble_gatt_evt_prim_service_discovered_t    prim_service_discovered;      ///<  parameter of gatt event @ref BLE_GATT_EVT_PRIM_SERVICE_DISCOVERED
        ble_gatt_evt_uuid_service_discovered_t    uuid_service_discovered;      ///<  parameter of gatt event @ref BLE_GATT_EVT_UUID_SERVICE_DISCOVERED
        ble_gatt_evt_included_service_found_t     included_service_found;       ///<  parameter of gatt event @ref BLE_GATT_EVT_INCLUDED_SERVICE_FOUND
        ble_gatt_evt_service_char_discovered_t    service_char_discovered;      ///<  parameter of gatt event @ref BLE_GATT_EVT_SERVICE_CHAR_DISCOVERED
        ble_gatt_evt_uuid_char_discovered_t       uuid_char_discovered;         ///<  parameter of gatt event @ref BLE_GATT_EVT_UUID_CHAR_DISCOVERED
        ble_gatt_evt_char_descrip_discovered_t    char_descrip_discovered;      ///<  parameter of gatt event @ref BLE_GATT_EVT_CHAR_DESCRIP_DISCOVERED
        ble_gatt_evt_char_value_read_t            char_value_read;              ///<  parameter of gatt event @ref BLE_GATT_EVT_CHAR_VALUE_READ
        ble_gatt_evt_uuid_char_read_t             uuid_char_read;               ///<  parameter of gatt event @ref BLE_GATT_EVT_UUID_CHAR_READ
        ble_gatt_evt_long_char_read_t             long_char_read;               ///<  parameter of gatt event @ref BLE_GATT_EVT_LONG_CHAR_READ
        ble_gatt_evt_multi_char_read_t            multi_char_read;              ///<  parameter of gatt event @ref BLE_GATT_EVT_MULTI_CHAR_READ
        ble_gatt_evt_char_value_written_t         char_value_written;           ///<  parameter of gatt event @ref BLE_GATT_EVT_CHAR_VALUE_WRITTEN
        ble_gatt_evt_long_char_written_t          long_char_written;            ///<  parameter of gatt event @ref BLE_GATT_EVT_LONG_CHAR_WRITTEN
        ble_gatt_evt_reliable_write_finished_t    reliable_write_finished;      ///<  parameter of gatt event @ref BLE_GATT_EVT_RELIABLE_WRITE_FINISHED
        ble_gatt_evt_char_descrip_read_t          char_descrip_read;            ///<  parameter of gatt event @ref BLE_GATT_EVT_CHAR_DESCRIP_READ
        ble_gatt_evt_long_descrip_read_t          long_descrip_read;            ///<  parameter of gatt event @ref BLE_GATT_EVT_LONG_DESCRIP_READ
        ble_gatt_evt_char_descrip_written_t       char_descrip_written;         ///<  parameter of gatt event @ref BLE_GATT_EVT_CHAR_DESCRIP_WRITTEN
        ble_gatt_evt_long_descrip_written_t       long_descrip_written;         ///<  parameter of gatt event @ref BLE_GATT_EVT_LONG_DESCRIP_WRITTEN
        ble_gatt_evt_handle_value_reported_t      handle_value_reported;        ///<  parameter of gatt event @ref BLE_GATT_EVT_HANDLE_VALUE_REPORTED
    } __attribute__((packed)) gatt;                                                                 ///< Event Parameters.
}  __attribute__((packed)) ble_gatt_evt_t;

#ifdef _MSC_VER
__pragma(pack(pop))
#undef __attribute__
#endif

/*!
    @brief GATT Event ID enumeration.
*/
typedef enum
{
    BLE_GATT_EVT_UNEXPECTED_RESPONSE_FROM_SERVER = BT_EVENT_GATT,/**< gatt event indicating unexpected response was received from gatt server.      */
    BLE_GATT_EVT_GET_ERROR_RESPONSE_FROM_SERVER,                 /**< gatt event indicating corresponding gatt procedure was finished abnormally.   */
    BLE_GATT_EVT_MTU_EXCHANGED,                                  /**< gatt event indicating corresponding gatt procedure was finished successfully. */
    BLE_GATT_EVT_PRIM_SERVICE_DISCOVERED,                        /**< gatt event indicating corresponding gatt procedure was finished successfully. */
    BLE_GATT_EVT_UUID_SERVICE_DISCOVERED,                        /**< gatt event indicating corresponding gatt procedure was finished successfully. */
    BLE_GATT_EVT_INCLUDED_SERVICE_FOUND,                         /**< gatt event indicating corresponding gatt procedure was finished successfully. */
    BLE_GATT_EVT_SERVICE_CHAR_DISCOVERED,                        /**< gatt event indicating corresponding gatt procedure was finished successfully. */
    BLE_GATT_EVT_UUID_CHAR_DISCOVERED,                           /**< gatt event indicating corresponding gatt procedure was finished successfully. */
    BLE_GATT_EVT_CHAR_DESCRIP_DISCOVERED,                        /**< gatt event indicating corresponding gatt procedure was finished successfully. */
    BLE_GATT_EVT_CHAR_VALUE_READ,                                /**< gatt event indicating corresponding gatt procedure was finished successfully. */
    BLE_GATT_EVT_UUID_CHAR_READ,                                 /**< gatt event indicating corresponding gatt procedure was finished successfully. */
    BLE_GATT_EVT_LONG_CHAR_READ,                                 /**< gatt event indicating corresponding gatt procedure was finished successfully. */
    BLE_GATT_EVT_MULTI_CHAR_READ,                                /**< gatt event indicating corresponding gatt procedure was finished successfully. */
    BLE_GATT_EVT_CHAR_VALUE_WRITTEN,                             /**< gatt event indicating corresponding gatt procedure was finished successfully. */
    BLE_GATT_EVT_LONG_CHAR_WRITTEN,                              /**< gatt event indicating corresponding gatt procedure was finished successfully. */
    BLE_GATT_EVT_RELIABLE_WRITE_FINISHED,                        /**< gatt event indicating corresponding gatt procedure was finished successfully. */
    BLE_GATT_EVT_CHAR_DESCRIP_READ,                              /**< gatt event indicating corresponding gatt procedure was finished successfully. */
    BLE_GATT_EVT_LONG_DESCRIP_READ,                              /**< gatt event indicating corresponding gatt procedure was finished successfully. */
    BLE_GATT_EVT_CHAR_DESCRIP_WRITTEN,                           /**< gatt event indicating corresponding gatt procedure was finished successfully. */
    BLE_GATT_EVT_LONG_DESCRIP_WRITTEN,                           /**< gatt event indicating corresponding gatt procedure was finished successfully. */
    BLE_GATT_EVT_HANDLE_VALUE_REPORTED,                          /**< gatt event indicating an attribute value has been reported by gatt server.    */

}ble_gatt_event_id;

/*!
    @brief GATT Client API status.
*/
typedef enum
{
    GATT_SUCCESS,/**< success*/
    GATT_FAILURE_INVALID_CONNECTION_HANDLE, /**< invalid connection handle*/
    GATT_FAILURE_INVALID_PARAMETER, /**< invalid parameter */
    GATT_FAILURE_PREVIOUS_PROCEDURE_NOT_ENDED,/**< previous procedure not ended*/
    GATT_FAILURE_TRANSACTION_TIMEOUT, /**< transaction timeout */
}GATT_STATUS;

#ifdef _MSC_VER
__pragma(pack(push, 1))
#define __attribute__(x)
#endif


/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_3_1_exchange_mtu.
*/
typedef struct
{
    uint16_t conn_handle;       ///< connection handle of designated gatt server
    uint16_t mtu;               ///< desired mtu size to be negotiated (only 23~200 is supported)
} __attribute__((packed)) GATT_4_3_1_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_4_1_disc_all_primary_services.
*/
typedef struct
{
    uint16_t conn_handle;       ///< connection handle of designated gatt server
} __attribute__((packed)) GATT_4_4_1_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_4_2_disc_primary_service_by_UUID.
*/
typedef struct
{
    uint16_t conn_handle;       ///< connection handle of designated gatt server
    uint8_t  uuid_size;         ///< size of uuid
    uint8_t  uuid[16];          ///< uuid in little-endian format
} __attribute__((packed)) GATT_4_4_2_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_5_1_find_included_services.
*/
typedef struct
{
    uint16_t conn_handle;       ///< connection handle of designated gatt server
    uint16_t start;             ///< first attribute handle of discovering range
    uint16_t end;               ///< last attribute handle of discovering range
} __attribute__((packed)) GATT_4_5_1_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_6_1_disc_all_chars.
*/
typedef struct
{
    uint16_t conn_handle;       ///< connection handle of designated gatt server
    uint16_t start;             ///< first attribute handle of discovering range
    uint16_t end;               ///< last attribute handle of discovering range
} __attribute__((packed)) GATT_4_6_1_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_6_2_disc_chars_by_UUID.
*/
typedef struct
{
    uint16_t conn_handle;      ///< connection handle of designated gatt server
    uint16_t start;            ///< first attribute handle of discovering range
    uint16_t end;              ///< last attribute handle of discovering range
    uint8_t  uuid_size;        ///< size of uuid
    uint8_t  uuid[16];         ///< uuid in little-endian format
} __attribute__((packed)) GATT_4_6_2_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_7_1_disc_all_char_descs.
*/
typedef struct
{
    uint16_t conn_handle;       ///< connection handle of designated gatt server
    uint16_t start;             ///< first attribute handle of discovering range
    uint16_t end;               ///< last attribute handle of discovering range
    uint8_t  max_pair;          ///< maximum number of attributes in returned event (10-20 is recommended)
} __attribute__((packed)) GATT_4_7_1_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_8_1_read_char_value.
*/
typedef struct
{
    uint16_t conn_handle;       ///< connection handle of designated gatt server
    uint16_t att_handle;        ///< attribute handle to be read
} __attribute__((packed)) GATT_4_8_1_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_8_2_read_using_char_UUID.
*/
typedef struct
{
    uint16_t conn_handle;       ///< connection handle of designated gatt server
    uint16_t start;             ///< first handle of reading range
    uint16_t end;               ///< last handle of reading range
    uint8_t  uuid_size;         ///< size of uuid
    uint8_t  uuid[16];          ///< uuid in little-endian format
} __attribute__((packed)) GATT_4_8_2_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_8_3_read_long_char_value.
*/
typedef struct
{
    uint16_t conn_handle;       ///< connection handle of designated gatt server
    uint16_t att_handle;        ///< attribute handle to be read
    uint16_t offset;            ///< attribute value offset
} __attribute__((packed)) GATT_4_8_3_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_8_4_read_multi_char_values.
*/
typedef struct
{
    uint16_t conn_handle;       ///< connection handle of designated gatt server
    uint8_t numofhandles;       ///< number of handles to be read
    uint16_t att_handle[5];     ///< array of attribute handles to be read
} __attribute__((packed)) GATT_4_8_4_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_9_1_write_no_rsp.
*/
typedef struct
{
    uint16_t conn_handle;       ///< connection handle of designated gatt server
    uint16_t att_handle;        ///< attribute handle to be written
    uint16_t len;               ///< length of attribute data
    uint8_t  data[1];           ///< attribute data
} __attribute__((packed)) GATT_4_9_1_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_9_2_signed_write_no_rsp.
*/
typedef struct
{
    uint16_t conn_handle;       ///< connection handle of designated gatt server
    uint16_t att_handle;        ///< attribute handle to be written
    uint16_t len;               ///< length of attribute data
    uint8_t  data[1];           ///< attribute data
} __attribute__((packed)) GATT_4_9_2_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_9_3_write_char_value.
*/
typedef struct
{
    uint16_t conn_handle;       ///< connection handle of designated gatt server
    uint16_t att_handle;        ///< attribute handle to be written
    uint16_t len;               ///< length of attribute data
    uint8_t  data[1];           ///< attribute data
} __attribute__((packed)) GATT_4_9_3_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_9_4_write_long_char_value.
*/
typedef struct
{
    uint16_t conn_handle;       ///< connection handle of designated gatt server
    uint16_t att_handle;        ///< attribute handle to be written
    uint16_t len;               ///< length of attribute data
    uint16_t offset;            ///< offset of attribute data
    uint8_t  data[1];           ///< attribute data
} __attribute__((packed)) GATT_4_9_4_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_9_5_reliable_writes.
*/
typedef struct
{
    uint16_t conn_handle;        ///< connection handle of designated gatt server
    uint8_t numofwrite;
    struct
    {
        uint16_t att_handle;     ///< attribute handle to be written
        uint16_t len;            ///< length of attribute data (10 bytes at most)
        uint16_t offset;         ///< offset of attribute data
        uint8_t  value[10];      ///< attribute data
    }__attribute__((packed)) write[6];
} __attribute__((packed)) GATT_4_9_5_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_12_1_read_char_desc.
*/
typedef struct
{
    uint16_t conn_handle;       ///< connection handle of designated gatt server
    uint16_t att_handle;        ///< attribute handle to be read
} __attribute__((packed)) GATT_4_12_1_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_12_2_read_long_char_desc.
*/
typedef struct
{
    uint16_t conn_handle;       ///< connection handle of designated gatt server
    uint16_t att_handle;        ///< attribute handle to be read
    uint16_t offset;            ///< offset of attribute data
} __attribute__((packed)) GATT_4_12_2_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_12_3_write_char_desc.
*/
typedef struct
{
    uint16_t conn_handle;        ///< connection handle of designated gatt server
    uint16_t att_handle;         ///< attribute handle to be written
    uint16_t len;                ///< length of attribute data
    uint8_t  data[1];            ///< attribute data
} __attribute__((packed)) GATT_4_12_3_PARA;

/*!
    @brief GATT Client API parameter for @ref ble_gatt_4_12_4_write_long_char_desc.
*/
typedef struct
{
    uint16_t conn_handle;        ///< connection handle of designated gatt server
    uint16_t att_handle;         ///< attribute handle to be written
    uint16_t len;                ///< length of attribute data
    uint16_t offset;             ///< offset of attribute data
    uint8_t  data[1];            ///< attribute data
} __attribute__((packed)) GATT_4_12_4_PARA;

#ifdef _MSC_VER
__pragma(pack(pop))
#undef __attribute__
#endif

/*!
     @brief Union of GATT client API parameter.
 */
typedef union
{
    GATT_4_3_1_PARA  p_4_3_1;
    GATT_4_4_1_PARA  p_4_4_1;
    GATT_4_4_2_PARA  p_4_4_2;
    GATT_4_5_1_PARA  p_4_5_1;
    GATT_4_6_1_PARA  p_4_6_1;
    GATT_4_6_2_PARA  p_4_6_2;
    GATT_4_7_1_PARA  p_4_7_1;
    GATT_4_8_1_PARA  p_4_8_1;
    GATT_4_8_2_PARA  p_4_8_2;
    GATT_4_8_3_PARA  p_4_8_3;
    GATT_4_8_4_PARA  p_4_8_4;
    GATT_4_9_1_PARA  p_4_9_1;
    GATT_4_9_2_PARA  p_4_9_2;
    GATT_4_9_3_PARA  p_4_9_3;
    GATT_4_9_4_PARA  p_4_9_4;
    GATT_4_9_5_PARA  p_4_9_5;
    GATT_4_12_1_PARA p_4_12_1;
    GATT_4_12_2_PARA p_4_12_2;
    GATT_4_12_3_PARA p_4_12_3;
    GATT_4_12_4_PARA p_4_12_4;
}GATT_PROC_PARA_UNION;


/*!
     @brief API for starting GATT procedure: Exchange MTU.\n
         This API would invoke gatt event @ref BLE_GATT_EVT_MTU_EXCHANGED after procedure is finished successfully.\n
     @param para @ref GATT_4_3_1_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_3_1_exchange_mtu(GATT_4_3_1_PARA * para);

/*!
     @brief API for starting GATT procedure: Discover All Primary Services.\n
         This API would invoke gatt event @ref BLE_GATT_EVT_PRIM_SERVICE_DISCOVERED after procedure is finished successfully.\n
     @param para @ref GATT_4_4_1_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_4_1_disc_all_primary_services(GATT_4_4_1_PARA * para);

/*!
     @brief API for starting GATT procedure: Discover Primary Services By Service UUID.\n
         This API would invoke gatt event @ref BLE_GATT_EVT_UUID_SERVICE_DISCOVERED after procedure is finished successfully.\n
     @param para @ref GATT_4_4_2_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_4_2_disc_primary_service_by_UUID(GATT_4_4_2_PARA * para);

/*!
     @brief API for starting GATT procedure: Find Included Services.\n
         This API would invoke gatt event @ref BLE_GATT_EVT_INCLUDED_SERVICE_FOUND after procedure is finished successfully.\n
     @param para @ref GATT_4_5_1_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_5_1_find_included_services(GATT_4_5_1_PARA * para);

/*!
     @brief API for starting GATT procedure: Discover All Characteristic of A Service.\n
         This API would invoke gatt event @ref BLE_GATT_EVT_SERVICE_CHAR_DISCOVERED after procedure is finished successfully.\n
     @param para @ref GATT_4_6_1_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_6_1_disc_all_chars(GATT_4_6_1_PARA * para);

/*!
     @brief API for starting GATT procedure: Discover Characteristics by UUID.\n
         This API would invoke gatt event @ref BLE_GATT_EVT_UUID_CHAR_DISCOVERED after procedure is finished successfully.\n
     @param para @ref GATT_4_6_2_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_6_2_disc_chars_by_UUID(GATT_4_6_2_PARA * para);

/*!
     @brief API for starting GATT procedure: Discover All Characteristic Descriptors.\n
         This API would invoke gatt event @ref BLE_GATT_EVT_CHAR_DESCRIP_DISCOVERED after procedure is finished successfully.\n
     @param para @ref GATT_4_7_1_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_7_1_disc_all_char_descs(GATT_4_7_1_PARA * para);

/*!
     @brief API for starting GATT procedure: Read Characteristic Value.\n
         This API would invoke gatt event @ref BLE_GATT_EVT_CHAR_VALUE_READ after procedure is finished successfully.\n
     @param para @ref GATT_4_8_1_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_8_1_read_char_value(GATT_4_8_1_PARA * para);

/*!
     @brief API for starting GATT procedure: Read Using Characteristic UUID.\n
         This API would invoke gatt event @ref BLE_GATT_EVT_UUID_CHAR_READ after procedure is finished successfully.\n
     @param para @ref GATT_4_8_2_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_8_2_read_using_char_UUID(GATT_4_8_2_PARA * para);

/*!
     @brief API for starting GATT procedure: Read Long Characteristic Values.\n
         This API would invoke gatt event @ref BLE_GATT_EVT_LONG_CHAR_READ after procedure is finished successfully.\n
     @param para @ref GATT_4_8_3_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_8_3_read_long_char_value(GATT_4_8_3_PARA * para);

/*!
     @brief API for starting GATT procedure: Read Multiple Characteristic Values.\n
         This API would invoke gatt event @ref BLE_GATT_EVT_MULTI_CHAR_READ after procedure is finished successfully.\n
     @param para @ref GATT_4_8_4_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_8_4_read_multi_char_values(GATT_4_8_4_PARA * para);

/*!
     @brief API for starting GATT procedure: Write Without Response.\n
         This API would not invoke gatt event.\n
     @param para @ref GATT_4_9_1_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_9_1_write_no_rsp(GATT_4_9_1_PARA * para);

/*!
     @brief API for starting GATT procedure: Signed Write Without Response.\n
         This API would not invoke gatt event.\n
     @param para @ref GATT_4_9_2_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_9_2_signed_write_no_rsp(GATT_4_9_2_PARA * para);

/*!
     @brief API for starting GATT procedure: Write Characteristic Value.\n
         This API would invoke gatt event @ref BLE_GATT_EVT_CHAR_VALUE_WRITTEN after procedure is finished successfully.\n
     @param para @ref GATT_4_9_3_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_9_3_write_char_value(GATT_4_9_3_PARA * para);

/*!
     @brief API for starting GATT procedure: Write Long Characteristic Values.\n
         This API would invoke gatt event @ref BLE_GATT_EVT_LONG_CHAR_WRITTEN after procedure is finished successfully.\n
     @param para @ref GATT_4_9_4_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_9_4_write_long_char_value(GATT_4_9_4_PARA * para);

/*!
     @brief API for starting GATT procedure: Characteristic Value Reliable Writes.\n
         This API would invoke gatt event @ref BLE_GATT_EVT_RELIABLE_WRITE_FINISHED after procedure is finished successfully.\n
     @param para @ref GATT_4_9_5_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_9_5_reliable_writes(GATT_4_9_5_PARA * para);

/*!
     @brief API for starting GATT procedure: Read Characteristic Descriptors.\n
         This API would invoke gatt event @ref BLE_GATT_EVT_CHAR_DESCRIP_READ after procedure is finished successfully.\n
     @param para @ref GATT_4_12_1_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_12_1_read_char_desc(GATT_4_12_1_PARA * para);

/*!
     @brief API for starting GATT procedure: Read Long Characteristic Descriptors.\n
         This API would invoke gatt event @ref BLE_GATT_EVT_LONG_DESCRIP_READ after procedure is finished successfully.\n
     @param para @ref GATT_4_12_2_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_12_2_read_long_char_desc(GATT_4_12_2_PARA * para);

/*!
     @brief API for starting GATT procedure: Write Characteristic Descriptors.\n
         This API would invoke gatt event @ref BLE_GATT_EVT_CHAR_DESCRIP_WRITTEN after procedure is finished successfully.\n
     @param para @ref GATT_4_12_3_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_12_3_write_char_desc(GATT_4_12_3_PARA * para);

/*!
     @brief API for starting GATT procedure: Write Long Characteristic Descriptors.\n
         This API would invoke gatt event @ref BLE_GATT_EVT_LONG_DESCRIP_WRITTEN after procedure is finished successfully.\n
     @param para @ref GATT_4_12_4_PARA
     @return GATT procedure status @ref GATT_STATUS
 */
GATT_STATUS ble_gatt_4_12_4_write_long_char_desc(GATT_4_12_4_PARA * para);


/*!
    @}
*/
#endif
