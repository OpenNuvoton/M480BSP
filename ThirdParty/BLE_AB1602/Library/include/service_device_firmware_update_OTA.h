/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_device_firmware_update_OTA.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef __SERVICE_DFU_OTA_H__
#define __SERVICE_DFU_OTA_H__

/*!
     @defgroup PAGE_SERVICE_OTA service_device_firmware_update_OTA.h
     @{
        @page PAGE_SERVICE_OTA service_device_firmware_update_OTA.h
        service_device_firmware_update_OTA.h provides an easy way to implement device firmware update over the air (DFU OTA) service.
*/


/*!
    @brief device firmware update status. SDK user may handle state changing event in callback function @ref OTA_STATUS_CB.
*/
typedef enum
{
    OTA_STARTED,
    OTA_FINISHED,
}OTA_STATUS_ENUM;

/*!
    @brief DFU OTA permission. SDK user may change the permission with API at any time.
*/
typedef enum
{
    OTA_ENABLED,
    OTA_DISABLED,
}OTA_PERMISSION_ENUM;

/*!
    @brief DFU OTA service status changing callback function.
*/

typedef void (* OTA_STATUS_CB)(OTA_STATUS_ENUM status);

/*!
    @brief Initialization function of DFU OTA service defined by AIROHA.
    @param cb @ref OTA_STATUS_CB.
    @return None.
*/
void OTA_init(OTA_STATUS_CB cb);

/*!
    @brief Change OTA service permission immediately.\n
            SDK user may decide whether OTA is permitted under certain circumstances such as low battery level or connecting with particular host.
    @param sel @ref OTA_PERMISSION_ENUM.
    @return None.
*/
void OTA_change_permission(OTA_PERMISSION_ENUM sel);



/*!
    @}
*/
#endif
