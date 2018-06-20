/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_link_loss.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef _LINK_LOSS_SERVICE_H_
#define _LINK_LOSS_SERVICE_H_

/*!
     @defgroup PAGE_SERVICE_LLS service_link_loss.h
     @{
        @page PAGE_SERVICE_LLS service_link_loss.h
        service_link_loss.h provides an easy way to implement link loss service.
*/
#include "ble_gatt_server.h"

/*!
    @brief link loss service initialization Parameters
*/
typedef struct
{   
    uint8_t* lls_alert_level;
    ATTCB lls_cb;
}lls_init_para;

/*!
    @brief Initialization function of lls service.
    @param para @ref lls_init_para.
    @return None.
*/

void LLS_init(lls_init_para * para);

#endif

