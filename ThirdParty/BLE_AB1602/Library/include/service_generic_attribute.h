/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_generic_attribute.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef __GENERIC_ATTRIBUTE_SERVICE_H_
#define __GENERIC_ATTRIBUTE_SERVICE_H_

/*!

     @defgroup PAGE_SERVICE_GATT service_generic_attribute.h
     @{
        @page PAGE_SERVICE_GATT service_generic_attribute.h
        service_generic_attribute.h provides an easy way to implement generic attribute service.
*/
#include "ble_gatt_server.h"

/*!
    @brief Initialization function of generic attribute service.
    @param support_service_changed 1:support/0:not support.
    @return None.
*/
void GATT_init(bool support_service_changed);

/*!
    @brief Indicate GATT client that GATT database has been changed.
    @param start_handle Start of Affected Attribute Handle Range
    @param end_handle   End of Affected Attribute Handle Range
    @return None.
*/
void GATT_service_changed(uint16_t start_handle, uint16_t end_handle);

/*!
    @}
*/
#endif
