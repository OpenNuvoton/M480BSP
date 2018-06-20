/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_immediate_alert.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef _IMMEDIATE_ALERT_SERVICE_H_
#define _IMMEDIATE_ALERT_SERVICE_H_

/*!
     @defgroup PAGE_SERVICE_IAS service_immediate_alert.h
     @{
        @page PAGE_SERVICE_IAS service_immediate_alert.h
        service_immediate_alert.h provides an easy way to implement immediate alert service.
*/
#include "ble_gatt_server.h"

/*!
    @brief immediate alert service initialization Parameters
*/
typedef struct
{   
    uint8_t* ias_alert_level;
    ATTCB ias_cb;
}ias_init_para;

/*!
    @brief Initialization function of lls service.
    @param para @ref ias_init_para.
    @return None.
*/

void IAS_init(ias_init_para * para);

#endif

