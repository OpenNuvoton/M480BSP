/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_battery.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef _BATTERY_SERVICE_H_
#define _BATTERY_SERVICE_H_

/*!
     @defgroup PAGE_SERVICE_BAS service_battery.h
     @{
        @page PAGE_SERVICE_BAS service_battery.h
        service_battery.h provides an easy way to implement battery service.
*/
#include "ble_gatt_server.h"

/*!
    @brief Initialization function of battery service.
    @param support_notification 1:support/0:not support.
    @return None.
*/
void BAS_init(bool support_notification);
/*!
    @brief Update battery level.
    @param level Battery level. Valid range: 0~100
    @param notify_after_update 1:Update battery level and use notification procedure to notify GATT client.\n
                               0:Update battery level characteristic value.
    @return None.
*/
void BAS_update_battery_level(uint8_t level, bool notify_after_update);





/*!
    @}
*/
#endif
