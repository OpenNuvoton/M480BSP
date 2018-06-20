/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_immediate_alert.c
DESCRIPTION
NOTES
********************************************************************************/
#include "service_immediate_alert.h"
#include "ble_gatt_server.h"

void IAS_init(ias_init_para * para)
{
    gatt_add_service_para servicepara =
    {
        .type = primary_service,
        .size = UUID_16bit,
        .UUID = {0x02,0x18},
    };
    gatt_add_charact_para charactpara =
    {
        .size = UUID_16bit,
        .UUID = {0x06,0x2A},
        .property = (C_WRITE_NO_RSP),
        .permission = A_RB_WP,
        .data_initial_length = 1,
        .data_maximum_length = 1,
        .char_data = para->ias_alert_level,
        .cb = para->ias_cb,
    };

    BLE_gatt_add_service(&servicepara);
    BLE_gatt_add_charact(&charactpara);
}