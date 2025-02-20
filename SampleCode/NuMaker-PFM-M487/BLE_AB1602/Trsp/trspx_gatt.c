/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME
    trspx_gatt.c
DESCRIPTION
NOTES
********************************************************************************/
#include "trspx_gatt.h"
#include "trspx.h"

void UART1_TX_Send(uint32_t len, uint8_t *ptr);

uint8_t TRSPX_Write_Data[200];
uint8_t TRSPX_Read_Data[200];
uint8_t TRSPX_CCCD_Data[2];

void _LeXport_RxCB(ATT_CB_TYPE type, uint8_t linkindex, uint16_t handle)
{
    uint16_t att_current_Len;

    att_current_Len = BLE_att_get_attribute_length(trspx_write_handle);

    UART1_TX_Send(att_current_Len, TRSPX_Write_Data);

    //AB_UART_Write(TRSPX_UART_PORT, TRSPX_Write_Data, att_current_Len);
}


void _LeXport_TxCccdCB(ATT_CB_TYPE type, uint8_t linkindex, uint16_t handle)
{
    if(type == CB_AFTER_WRITING)
    {

    }
}

void TRSPX_send(uint16_t len)
{
    if(TRSPX_ble_status == BLE_CONNECTED)
    {
        BLE_att_set_attribute_length(trspx_notify_handle,len);
        BLE_gatt_charact_notify(trspx_notify_handle, FORCE_LINK0);
    }
}

void TRSPX_service_init(void)
{
    trspx_init_para trspx_para =
    {
        .write_data = TRSPX_Write_Data,
        .read_data = TRSPX_Read_Data,
        .trspx_write_CB = _LeXport_RxCB,
        .trspx_cccd = TRSPX_CCCD_Data,
        .trspx_cccd_CB = _LeXport_TxCccdCB,
    };
    TRSPX_service_init_para(&trspx_para);
}

