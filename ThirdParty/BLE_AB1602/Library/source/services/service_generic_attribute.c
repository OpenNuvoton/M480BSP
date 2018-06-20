/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_generic_attribute.c
DESCRIPTION
NOTES
********************************************************************************/

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "service_generic_attribute.h"

static bool support_service_changed = false;
static uint16_t service_changed[2];
static uint16_t service_changed_cccd[1];
static uint16_t service_changed_att_handle;

void GATT_init(bool is_service_changed_supported)
{

    if(1)//gatt service
    {
        gatt_add_service_para servicepara =
        {
            .type = primary_service,
            .size = UUID_16bit,
            .UUID = {0x01,0x18},
        };

        BLE_gatt_add_service(&servicepara);
    }

    support_service_changed = is_service_changed_supported;
    if(support_service_changed)
    {
        gatt_add_charact_para charactpara =
        {
            .size = UUID_16bit,
            .UUID = {0x05,0x2A},
            .property = C_INDICATE,
            .permission = A_RB_WB,
            .data_initial_length = 4,
            .data_maximum_length = 0,
            .char_data = (uint8_t *)service_changed,
            .cb = NULL,
        };

        gatt_add_descrip_para descrippara =
        {
            .size = UUID_16bit,
            .UUID = {0x02,0x29},
            .permission = A_RP_WP,
            .data_initial_length = 2,
            .data_maximum_length = 0,
            .desc_data = (uint8_t *)service_changed_cccd,
            .cb = NULL,
        };

        service_changed_att_handle = BLE_gatt_add_charact(&charactpara);
        BLE_gatt_add_descrip(&descrippara);
    }
}

void GATT_service_changed(uint16_t start_handle, uint16_t end_handle)
{
    if(support_service_changed)
    {
        service_changed[0] = start_handle;
        service_changed[1] = end_handle;

        BLE_gatt_charact_indicate(service_changed_att_handle, ALL_CCCD_ENABLED_LINK, NULL);
    }
}
