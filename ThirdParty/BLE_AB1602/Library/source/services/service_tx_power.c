/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_tx_power.c
DESCRIPTION
NOTES
********************************************************************************/
#include "service_tx_power.h"
#include "ble_gatt_server.h"

void TPS_init(tps_init_para * para)
{
    gatt_add_service_para servicepara =
    {
        .type = primary_service,
        .size = UUID_16bit,
        .UUID = {0x04,0x18},
    };
    gatt_add_charact_para charactpara =
    {
        .size = UUID_16bit,
        .UUID = {0x07,0x2A},
        .property = (C_READ),
        .permission = A_RP_WB,
        .data_initial_length = 1,
        .data_maximum_length = 1,
        .char_data = para->txpower_level,
        .cb = para->tps_cb,
    };

    BLE_gatt_add_service(&servicepara);
    BLE_gatt_add_charact(&charactpara);
}