/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_trspx.c
DESCRIPTION
NOTES
********************************************************************************/
#include "ble_gatt_server.h"
#include "service_trspx.h"

uint16_t trspx_service_handle;
uint16_t trspx_indicate_handle;
uint16_t trspx_notify_handle;
uint16_t trspx_cccd_handle;
uint16_t trspx_write_handle;
uint16_t trspx_read_handle;

void TRSPX_service_init_para(trspx_init_para * para)
{
    gatt_add_service_para servicepara =
    {
        .type = primary_service,
        .size = UUID_128bit,
        .UUID = {0x55,0xE4,0x05,0xD2,0xAF,0x9F,0xA9,0x8F,
        0xE5,0x4A,0x7D,0xFE,0x43,0x53,0x53,0x49},
    };
    gatt_add_charact_para charactpara1 =
    {
        .size = UUID_128bit,
        .UUID = {0x16,0x96,0x24,0x47,0xC6,0x23,0x61,0xBA,
        0xD9,0x4B,0x4D,0x1E,0x43,0x53,0x53,0x49},
        .property = (C_NOTIFY),
        .permission = A_RB_WB,
        .data_initial_length = 200,
        .data_maximum_length = 200,
        .char_data = para->read_data,
    };

    gatt_add_descrip_para descrippara =
    {
        .size = UUID_16bit,
        .UUID = {0x02,0x29},
        .permission = A_RP_WP,
        .data_initial_length = 2,
        .data_maximum_length = 0,
        .desc_data = para->trspx_cccd,
        .cb = para->trspx_cccd_CB,
    };
    
    gatt_add_charact_para charactpara2 =
    {
        .size = UUID_128bit,
        .UUID = {0xB3,0x9B,0x72,0x34,0xBE,0xEC,0xD4,0xA8,
        0xF4,0x43,0x41,0x88,0x43,0x53,0x53,0x49},
        .property = (C_WRITE|C_WRITE_NO_RSP),
        .permission = A_RB_WP,
        .data_initial_length = 200,
        .data_maximum_length = 200,
        .char_data = para->write_data,
        .cb = para->trspx_write_CB,
    };

    trspx_service_handle = BLE_gatt_add_service(&servicepara);
    trspx_notify_handle = BLE_gatt_add_charact(&charactpara1);
    trspx_cccd_handle = BLE_gatt_add_descrip(&descrippara);
    trspx_write_handle = BLE_gatt_add_charact(&charactpara2);

}
