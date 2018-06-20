/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_battery.c
DESCRIPTION
NOTES
********************************************************************************/
#include "service_battery.h"
#include "ble_gatt_server.h"

static uint8_t level_data[1];
static uint8_t level_cccd[2];
static uint16_t level_att_handle;
static bool support_notify;

void BAS_init(bool support_notification)
{
    gatt_add_service_para servicepara =
    {
        .type = primary_service,
        .size = UUID_16bit,
        .UUID = {0x0F,0x18},
    };

    gatt_add_charact_para charactpara =
    {
        .size = UUID_16bit,
        .UUID = {0x19,0x2A},
        .property = (C_READ),
        .permission = A_RP_WB,
        .data_initial_length = 1,
        .data_maximum_length = 0,
        .char_data = level_data,
        .cb = NULL,
    };

    gatt_add_descrip_para descrippara =
    {
        .size = UUID_16bit,
        .UUID = {0x02,0x29},
        .permission = A_RP_WP,
        .data_initial_length = 2,
        .data_maximum_length = 0,
        .desc_data = level_cccd,
        .cb = NULL,
    };

    support_notify = support_notification;
    if(support_notify)
    {
        charactpara.property |= (C_NOTIFY);
        BLE_gatt_add_service(&servicepara);
        level_att_handle = BLE_gatt_add_charact(&charactpara);
        BLE_gatt_add_descrip(&descrippara);
    }
    else
    {
        BLE_gatt_add_service(&servicepara);
        BLE_gatt_add_charact(&charactpara);
    }
}

void BAS_update_battery_level(uint8_t level, bool notify_after_update)
{
    level_data[0] = level;

    if(support_notify && notify_after_update)
    {
        BLE_gatt_charact_notify(level_att_handle, ALL_CCCD_ENABLED_LINK);
    }
}

