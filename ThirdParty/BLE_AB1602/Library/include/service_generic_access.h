/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_generic_access.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef __GENERIC_ACCESS_SERVICE_H_
#define __GENERIC_ACCESS_SERVICE_H_

/*!

     @defgroup PAGE_SERVICE_GAS service_generic_access.h
     @{
        @page PAGE_SERVICE_GAS service_generic_access.h
        service_generic_access.h provides an easy way to implement generic access service.
*/
#include "ble_gatt_server.h"

/*!
    @brief Peripheral Preferred Connection Parameters
*/
typedef struct
{
    uint16_t min_interval;      /**<  Connection Interval = min_interval* 1.25 ms  range: 6~3200 ;65535=no specific minimum  */
    uint16_t max_interval;      /**<  Connection Interval = max_interval* 1.25 ms  range: 6~3200 ;65535=no specific minimum  */
    uint16_t slave_latency;     /**<  range: 0~1000*/
    uint16_t supervision_TO;    /**<  Connection Supervision Timeout Multiplier    range:10~3200 ;65535=no specific value requested */
}PPCP_t;

/*!
    @brief generic access service initialization Parameters
*/
typedef struct
{
    uint16_t  appearance;               /**<  device appearance UUID */
    uint8_t * device_name_buf;          /**<  device name String buffer */
    uint16_t  device_name_ini_length;   /**<  device name String length */
    uint16_t  device_name_max_length;   /**<  [Optional] device name maximum size, only needed if device name is writable*/
    ATTCB     device_name_write_CB;     /**<  [Optional] call back function of device name, device name will be read only if CB is NULL */
    PPCP_t  * parameter;                /**<  [Optional] Peripheral Preferred Connection Parameters */
    ATTCB     appearance_write_CB;      /**<  [Optional] call back function of appearance, appearance will be read only if CB is NULL */
}gas_init_para;

/*!
    @brief privacy feature initialization Parameters
*/
typedef struct
{
    uint8_t * reconnection_addr;        /**<  reconnection address buffer*/
    ATTCB     reconnection_addr_CB;     /**<  call back function of reconnection_addr*/
}gas_privacy_init_para;

/*!
    @brief Initialization function of generic access service.
    @param para @ref gas_init_para.
    @return None.
*/
void GAS_init(gas_init_para * para);

/*!
    @brief Initialization function of privacy feature. Should not be used before @ref GAS_init
    @param para @ref gas_privacy_init_para.
    @return None.
*/
void GAS_support_privacy_feature(gas_privacy_init_para * para);





/*!
    @}
*/
#endif
