/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_mesh.c
DESCRIPTION
NOTES
********************************************************************************/
#include "service_mesh.h"
#include "ble_gatt_server.h"

#define  MESH_PROVISION_SERVICE_UUID    {0xAA,0x18} //temp
#define  MESH_PROVISION_DATA_IN_UUID    {0xAA,0x2A} //temp
#define  MESH_PROVISION_DATA_OUT_UUID   {0xBB,0x2A} //temp

#define  MESH_PROXY_SERVICE_UUID        {0xBB,0x18} //temp
#define  MESH_PROXY_DATA_IN_UUID        {0xCC,0x2A} //temp
#define  MESH_PROXY_DATA_OUT_UUID       {0xDD,0x2A} //temp

static uint8_t provision_cccd[2];
static uint8_t proxy_cccd[2];

static uint16_t provision_out_handle;
static uint16_t proxy_out_handle;

void MESH_provision_service_init(mesh_init_para * para)
{
    gatt_add_service_para servicepara =
    {
        .type = primary_service,
        .size = UUID_16bit,
        .UUID = MESH_PROVISION_SERVICE_UUID,
    };

    gatt_add_charact_para charactpara =
    {
        .size = UUID_16bit,
        .UUID = MESH_PROVISION_DATA_IN_UUID,
        .property = C_WRITE_NO_RSP,
        .permission = A_RB_WP,
        .data_initial_length = 1,
        .data_maximum_length = 66,
        .char_data = para->data_in,
        .cb = para->cb,
    };

    gatt_add_charact_para charactpara2 =
    {
        .size = UUID_16bit,
        .UUID = MESH_PROVISION_DATA_OUT_UUID,
        .property = C_NOTIFY,
        .permission = A_RB_WB,
        .data_initial_length = 0,
        .data_maximum_length = 66,
        .char_data = NULL,
        .cb = NULL,
    };

    gatt_add_descrip_para descrippara =
    {
        .size = UUID_16bit,
        .UUID = {0x02,0x29},
        .permission = A_RP_WP,
        .data_initial_length = 2,
        .data_maximum_length = 0,
        .desc_data = provision_cccd,
        .cb = NULL,
    };


    if(provision_out_handle)
        return;

    BLE_gatt_add_service(&servicepara);
    BLE_gatt_add_charact(&charactpara);
    provision_out_handle = BLE_gatt_add_charact(&charactpara2);
    BLE_gatt_add_descrip(&descrippara);
}

void MESH_proxy_service_init(mesh_init_para * para)
{
    gatt_add_service_para servicepara =
    {
        .type = primary_service,
        .size = UUID_16bit,
        .UUID = MESH_PROXY_SERVICE_UUID,
    };

    gatt_add_charact_para charactpara =
    {
        .size = UUID_16bit,
        .UUID = MESH_PROXY_DATA_IN_UUID,
        .property = C_WRITE_NO_RSP,
        .permission = A_RB_WP,
        .data_initial_length = 1,
        .data_maximum_length = 66,
        .char_data = para->data_in,
        .cb = para->cb,
    };

    gatt_add_charact_para charactpara2 =
    {
        .size = UUID_16bit,
        .UUID = MESH_PROXY_DATA_OUT_UUID,
        .property = C_NOTIFY,
        .permission = A_RB_WB,
        .data_initial_length = 0,
        .data_maximum_length = 66,
        .char_data = NULL,
        .cb = NULL,
    };

    gatt_add_descrip_para descrippara =
    {
        .size = UUID_16bit,
        .UUID = {0x02,0x29},
        .permission = A_RP_WP,
        .data_initial_length = 2,
        .data_maximum_length = 0,
        .desc_data = proxy_cccd,
        .cb = NULL,
    };


    if(proxy_out_handle)
        return;

    BLE_gatt_add_service(&servicepara);
    BLE_gatt_add_charact(&charactpara);
    proxy_out_handle = BLE_gatt_add_charact(&charactpara2);
    BLE_gatt_add_descrip(&descrippara);
}

void MESH_provision_data_out_notify(uint8_t len, uint8_t * data)
{
    BLE_att_set_attribute_length(provision_out_handle,len);
    BLE_att_set_attribute_data_ptr(provision_out_handle, data);
    BLE_gatt_charact_notify(provision_out_handle, ALL_CCCD_ENABLED_LINK);
}

void MESH_proxy_data_out_notify(uint8_t len, uint8_t * data)
{
    BLE_att_set_attribute_length(proxy_out_handle,len);
    BLE_att_set_attribute_data_ptr(proxy_out_handle, data);
    BLE_gatt_charact_notify(proxy_out_handle, ALL_CCCD_ENABLED_LINK);
}
