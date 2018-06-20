/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_device_information.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef _DEVICE_INFORMATION_SERVICE_H_
#define _DEVICE_INFORMATION_SERVICE_H_

/*!
     @defgroup PAGE_SERVICE_DIS service_device_information.h
     @{
        @page PAGE_SERVICE_DIS service_device_information.h
        service_device_information.h provides an easy way to implement device information service.
*/
#include "ble_gatt_server.h"


/*!
    @brief device information service initialization Parameters
*/
typedef struct
{
    uint8_t* manufacturer_name_string;      /**< Must be a Null-terminated string and length<512*/
    uint8_t* model_number_string;           /**< Must be a Null-terminated string and length<512*/
    uint8_t* seriel_number_string;          /**< Must be a Null-terminated string and length<512*/
    uint8_t* hardware_revision_string;      /**< Must be a Null-terminated string and length<512*/
    uint8_t* firmware_revision_string;      /**< Must be a Null-terminated string and length<512*/
    uint8_t* software_revision_string;      /**< Must be a Null-terminated string and length<512*/
    uint8_t* system_id;                     /**< length =  8  */
    uint8_t* ieee_11073_20601_rcdl;         /**< length = 10  */
    uint8_t* pnp_id;                        /**< length =  7  */
}dis_init_para;

/*!
    @brief Initialization function of device information service.
    @param para @ref dis_init_para.
    @return None.
*/
void DIS_init(dis_init_para * para);





/*!
    @}
*/
#endif



