/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_tx_power.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef _TX_POWER_SERVICE_H_
#define _TX_POWER_SERVICE_H_

/*!
     @defgroup PAGE_SERVICE_TPS service_tx_power.h
     @{
        @page PAGE_SERVICE_TPS service_tx_power.h
        service_tx_power.h provides an easy way to implement tx power service.
*/
#include "ble_gatt_server.h"

/*!
    @brief tx power service initialization Parameters
*/
typedef struct
{   
    uint8_t* txpower_level;
    ATTCB tps_cb;
}tps_init_para;

/*!
    @brief Initialization function of lls service.
    @param para @ref tps_init_para.
    @return None.
*/

void TPS_init(tps_init_para * para);

/*!
	 @}
*/
#endif

