/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_link_loss.c
DESCRIPTION
NOTES
********************************************************************************/
#include "service_link_loss.h"
#include "ble_gatt_server.h"

void LLS_init(lls_init_para * para)
{
    gatt_add_service_para servicepara =
    {
        .type = primary_service,
        .size = UUID_16bit,
        .UUID = {0x03,0x18},
    };
    gatt_add_charact_para charactpara =
    {
        .size = UUID_16bit,
        .UUID = {0x06,0x2A},
        .property = (C_READ | C_WRITE),
        .permission = A_RP_WP,
        .data_initial_length = 1,
        .data_maximum_length = 1,
        .char_data = para->lls_alert_level,
        .cb = para->lls_cb,
    };

    BLE_gatt_add_service(&servicepara);
    BLE_gatt_add_charact(&charactpara);
}