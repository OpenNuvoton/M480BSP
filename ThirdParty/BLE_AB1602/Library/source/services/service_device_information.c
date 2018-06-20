/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_device_information.c
DESCRIPTION
NOTES
********************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ble_gatt_server.h"
#include "service_device_information.h"

static void _dis_add_char(uint8_t lsb, uint8_t *data, uint8_t len)
{
    gatt_add_charact_para charactpara =
    {
        .size = UUID_16bit,
        .UUID = {0x00,0x2A},
        .property = (C_READ),
        .permission = A_RP_WB,
        .data_maximum_length = 0,
        .cb = NULL,
    };

    charactpara.UUID[0] = lsb;
    charactpara.data_initial_length = (len)? len : strlen((char *)data);
    charactpara.char_data = data;
    BLE_gatt_add_charact(&charactpara);
}

void DIS_init(dis_init_para * para)
{
    gatt_add_service_para servicepara =
    {
        .type = primary_service,
        .size = UUID_16bit,
        .UUID = {0x0A,0x18},
    };

    BLE_gatt_add_service(&servicepara);

    if(para->manufacturer_name_string)
        _dis_add_char(0x29, para->manufacturer_name_string, 0);
    if(para->model_number_string)
        _dis_add_char(0x24, para->model_number_string, 0);
    if(para->seriel_number_string)
        _dis_add_char(0x25, para->seriel_number_string, 0);
    if(para->hardware_revision_string)
        _dis_add_char(0x27, para->hardware_revision_string, 0);
    if(para->firmware_revision_string)
        _dis_add_char(0x26, para->firmware_revision_string, 0);
    if(para->software_revision_string)
        _dis_add_char(0x28, para->software_revision_string, 0);
    if(para->system_id)
        _dis_add_char(0x23, para->system_id, 8);
    if(para->ieee_11073_20601_rcdl)
        _dis_add_char(0x2A, para->ieee_11073_20601_rcdl, 10);
    if(para->pnp_id)
        _dis_add_char(0x50, para->pnp_id, 7);
}
