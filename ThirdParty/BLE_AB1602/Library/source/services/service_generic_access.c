/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_generic_access.c
DESCRIPTION
NOTES
********************************************************************************/

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "service_generic_access.h"

void GAS_init(gas_init_para * para)
{

    if(1)//gap service
    {
        gatt_add_service_para servicepara =
        {
            .type = primary_service,
            .size = UUID_16bit,
            .UUID = {0x00,0x18},
        };

        BLE_gatt_add_service(&servicepara);
    }

    if(1)//device name
    {
        gatt_add_charact_para charactpara =
        {
            .size = UUID_16bit,
            .UUID = {0x00,0x2A},
            .property = (para->device_name_write_CB)?(C_READ|C_WRITE):(C_READ),
            .permission = (para->device_name_write_CB)?A_RP_WP:A_RP_WB,
            .data_initial_length = para->device_name_ini_length,
            .data_maximum_length = para->device_name_max_length,
            .char_data = para->device_name_buf,
            .cb = para->device_name_write_CB,
        };

        BLE_gatt_add_charact(&charactpara);
    }

    if(1)//appearance
    {
        gatt_add_charact_para charactpara =
        {
            .size = UUID_16bit,
            .UUID = {0x01,0x2A},
            .property = (para->appearance_write_CB)?(C_READ|C_WRITE):(C_READ),
            .permission = (para->appearance_write_CB)?A_RP_WP:A_RP_WB,
            .data_initial_length = 2,
            .data_maximum_length = 0,
            .char_data = malloc(2),
            .cb = para->appearance_write_CB,
        };

        memcpy(charactpara.char_data, &para->appearance, 2);

       BLE_gatt_add_charact(&charactpara);
    }

    if(para->parameter)
    {
        gatt_add_charact_para charactpara =
        {
            .size = UUID_16bit,
            .UUID = {0x04,0x2A},
            .property = (C_READ),
            .permission = A_RP_WB,
            .data_initial_length = 8,
            .data_maximum_length = 0,
            .char_data = malloc(8),
            .cb = NULL,
        };

        memcpy(charactpara.char_data, para->parameter, 8);

        BLE_gatt_add_charact(&charactpara);
    }
}

void GAS_support_privacy_feature(gas_privacy_init_para* para)
{
    if(1)
    {
        gatt_add_charact_para charactpara =
        {
            .size = UUID_16bit,
            .UUID = {0x02,0x2A},
            .property = (C_READ),
            .permission = A_RP_WB,
            .data_initial_length = 1,
            .data_maximum_length = 0,
            .char_data = malloc(1),
            .cb = NULL,
        };

        charactpara.char_data[0] = 1;

        BLE_gatt_add_charact(&charactpara);
    }

    if(1)
    {
        gatt_add_charact_para charactpara =
        {
            .size = UUID_16bit,
            .UUID = {0x03,0x2A},
            .property = (C_WRITE),
            .permission = A_RB_WP,
            .data_initial_length = 6,
            .data_maximum_length = 0,
            .char_data = para->reconnection_addr,
            .cb = para->reconnection_addr_CB,
        };

        BLE_gatt_add_charact(&charactpara);
    }
}


