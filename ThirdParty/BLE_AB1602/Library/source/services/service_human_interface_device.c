/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_human_interface_device.c
DESCRIPTION
NOTES
********************************************************************************/
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdbool.h>
#include "ble_gatt_server.h"
#include "service_human_interface_device.h"

void HIDS_init(hids_init_para * para)
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

    if(1)   //add HID service
    {
        gatt_add_service_para servicepara =
        {
            .type = primary_service,
            .size = UUID_16bit,
            .UUID = {0x12,0x18},
        };

        BLE_gatt_add_service(&servicepara);
    }

    if(para->rmap.included_service_num)
    {
        uint8_t i;
        gatt_add_include_para includepara;

        for(i=0; i<para->rmap.included_service_num; i++)
        {
            includepara.service_handle = para->rmap.included_service_handle[i];

            BLE_gatt_add_include(&includepara);
        }
    }


    if(1)   //add report map characteristic
    {
#ifndef BYPASS_SECURITY
        charactpara.permission |= ATT_R_ENCRYPT;
#endif
        charactpara.UUID[0] = 0x4B;
        charactpara.data_initial_length = para->rmap.data_len;
        charactpara.char_data = para->rmap.data;

        BLE_gatt_add_charact(&charactpara);
        charactpara.permission &=~ATT_R_ENCRYPT;
    }

    if(para->rmap.ext_rep_ref_uuid_num)
    {
        gatt_add_descrip_para descrippara =
        {
            .size = UUID_16bit,
            .UUID = {0x07,0x29},    //external report reference
            .permission = A_RP_WB,
            .data_initial_length = 2,
            .data_maximum_length = 0,
            .cb = NULL,
        };

        uint8_t i = 0;

        do
        {
            descrippara.desc_data       = malloc(2);
            descrippara.desc_data[0]    = para->rmap.ext_rep_ref_uuid[i] & 0xff;
            descrippara.desc_data[1]    = para->rmap.ext_rep_ref_uuid[i] >> 8;

            BLE_gatt_add_descrip(&descrippara);

        }while(++i < para->rmap.ext_rep_ref_uuid_num);
    }

    if(1)   //add HID information characteristic
    {
        charactpara.UUID[0] = 0x4A;
        charactpara.data_initial_length = 4;
        charactpara.char_data = malloc(4);
        memcpy(charactpara.char_data, &para->hid_info, 4);

        BLE_gatt_add_charact(&charactpara);
    }

    if(1)   //add HID control point characteristic
    {
        charactpara.UUID[0] = 0x4C;
        charactpara.property = C_WRITE_NO_RSP;
        charactpara.permission = A_RB_WP;
        charactpara.data_initial_length = 1;
        charactpara.char_data = para->hid_cp.data;
        charactpara.cb = para->hid_cp.cb;

        BLE_gatt_add_charact(&charactpara);
    }
}

att_handle HIDS_add_report(hids_report_para * para)
{
    uint16_t cvd_handle;

    gatt_add_charact_para charactpara =
    {
        .size = UUID_16bit,
        .UUID = {0x4D,0x2A},
        .char_data = para->data,
        .data_initial_length = para->data_len,
        .data_maximum_length = 0,
        .cb = para->cb,
    };


    switch(para->report_type)
    {
        case HID_REPORT_INPUT:
            charactpara.property = (C_READ|C_NOTIFY);
            charactpara.permission = A_RP_WB;
            break;
        case HID_REPORT_OUTPUT:
            charactpara.property = (C_READ|C_WRITE_NO_RSP|C_WRITE);
            charactpara.permission = A_RP_WP;
            break;
        case HID_REPORT_FEATURE:
            charactpara.property = (C_READ|C_WRITE);
            charactpara.permission = A_RP_WP;
            break;
    }

    cvd_handle = BLE_gatt_add_charact(&charactpara);


    if(1)       // add report reference descriptor
    {
        gatt_add_descrip_para descrippara =
        {
            .size = UUID_16bit,
            .UUID = {0x08,0x29},
            .permission = A_RP_WB,
            .data_initial_length = 2,
            .data_maximum_length = 0,
            .cb = NULL,
        };

        descrippara.desc_data = malloc(2);

        descrippara.desc_data[0] = para->report_ID;
        descrippara.desc_data[1] = para->report_type;

        BLE_gatt_add_descrip(&descrippara);
    }

    if(para->report_type == HID_REPORT_INPUT)   // add cccd
    {
        gatt_add_descrip_para descrippara =
        {
            .size = UUID_16bit,
            .UUID = {0x02,0x29},
            .permission = A_RP_WP,
            .data_initial_length = 2,
            .data_maximum_length = 0,
            .cb = NULL,
        };

        descrippara.desc_data = malloc(2);
        BLE_gatt_add_descrip(&descrippara);
    }


    return cvd_handle;
}
