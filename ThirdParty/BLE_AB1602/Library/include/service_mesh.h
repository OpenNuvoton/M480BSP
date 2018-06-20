/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_mesh.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef _BATTERY_MESH_H_
#define _BATTERY_MESH_H_

/*!
     @defgroup PAGE_SERVICE_BAS service_mesh.h
     @{
        @page PAGE_SERVICE_MESH service_mesh.h
        service_mesh.h provides an easy way to implement mesh service.
*/
#include "ble_gatt_server.h"

/*!
    @brief mesh service initialization Parameters
*/
typedef struct
{
    uint8_t * data_in;              /**< data in characteristic data pointer*/
    ATTCB   cb;                     /**< service data in call back function*/
}mesh_init_para;


void MESH_provision_service_init(mesh_init_para * para);
void MESH_proxy_service_init(mesh_init_para * para);
void MESH_provision_data_out_notify(uint8_t len, uint8_t * data);
void MESH_proxy_data_out_notify(uint8_t len, uint8_t * data);

/*!
    @}
*/
#endif
