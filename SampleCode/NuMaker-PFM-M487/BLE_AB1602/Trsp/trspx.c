/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME
    trspx.c
DESCRIPTION
NOTES
********************************************************************************/
#include "trspx.h"
#include "stdarg.h"
#include "trspx_gatt.h"
#include <string.h>

uint16_t ble_conn_handle;

TRSPX_BLE_STATUS TRSPX_ble_status = BLE_IDLE;

uint32_t TRSPX_mtu = TRSPX_DEFAULT_MTU - 3;

void TRSPX_ble_set_adv_scan_data_cpl_cb(bool isuccess, uint8_t err_code)
{
    TRSPX_ble_status = BLE_ADVERTISING;
    //BT_Log_Enable(0);//disable log
}

void TRSPX_ble_set_adv_parameter_cb(bool isuccess, uint8_t err_code)
{
    ble_gap_adv_params parm =
    {
        .ad_type = ble_ad_type_ind,
        .peer_addr = NULL,
        .self_addr_type = ble_addr_type_public,
        .filter = ble_filter_any,
        .min_interval = 0x0020,
        .max_interval = 0x0040,
        .channel_mask = 0x7,
    };
    //start adv
    ble_gap_adv_start(&parm, TRSPX_ble_set_adv_scan_data_cpl_cb);
}

void TRSPX_ble_set_adv_data_cb(bool isuccess, uint8_t err_code)
{
    uint8_t ad[] =
    {
        0x02, 0x01, 0x06,
        0x0A, 0x09, 'T','R','S','P','X','-','B','L','E',
        0x0C, 0xFF, 0x94, 0x00, 0xFE, 0x01, 0x01, 0x55, 0x66, 0x77, 0x88, 0x78, 0x87,
        0x03, 0x02, 0xE7, 0xFE
    };
    ble_gap_adv_data_set(ad, sizeof(ad), TRSPX_ble_set_adv_parameter_cb);
}

static void TRSPX_ble_set_scan_data_cb(bool isuccess, uint8_t err_code)
{
    uint8_t ad[] =
    {
        0x02, 0x0A,0x00,
    };

    ble_gap_scan_data_set(ad, sizeof(ad), TRSPX_ble_set_adv_data_cb);
}

static void TRSPX_bt_inited_handler(bt_evt_t *evt)
{
    if(evt->evt.misc_evt.param.inited.is_success)
    {
        ble_addr_t addr;

        addr.addr_type = ble_addr_type_public;
        memcpy(addr.addr, "\x21\x12\xCD\x77\x66\x55", 6);   //Must inverse
        ble_gap_address_set(&addr, TRSPX_ble_set_scan_data_cb);
    }
    else
    {
        while(1);
    }
}

static bool TRSPX_update_connection_interval(void)
{
    static uint8_t noise = 0;

    ble_gap_conn_params_t conn =
    {
        CONN_INTERVAL*4/5, CONN_INTERVAL*4/5,           // 10ms
        SLAVE_LATENCY + (noise++&0x03),
        CONN_INTERVAL*10,
        0, 0
    };

    printf("slave sets min_conn = %d max_conn = %d, latency = %d, timeout = %d\n",
           conn.min_conn_interval, conn.max_conn_interval, conn.slave_latency, conn.conn_sup_timeout);
    if(ble_gap_conn_param_update(ble_conn_handle, &conn))
    {
        return false;
    }
    else
    {
        return true;
    }
}


static void TRSPX_connection_complete_handler(bt_evt_t *evt)
{
    if(evt->evt.gap_evt.params.connected.status)    //0 : success
    {
        return;
    }

    ble_conn_handle = evt->evt.gap_evt.params.connected.conn_handle;
    TRSPX_update_connection_interval();
    TRSPX_ble_status = BLE_CONNECTED;
}

static void TRSPX_disconnection_complete_handler(bt_evt_t *evt)
{
    TRSPX_ble_status = BLE_IDLE;

    TRSPX_ble_set_adv_parameter_cb(0, 0);
}

static void TRSPX_mtu_exchanged(bt_evt_t *evt)
{
    ble_gatt_evt_mtu_exchange_t * p = &evt->evt.gatt_evt.gatt.mtu_exchanged;

    TRSPX_mtu = p->new_mtu;
}

void TRSPX_bt_evt_hdl(bt_evt_t *evt)
{
    switch(evt->evt_id)
    {
    case BT_MISC_EVENT_INITED:
        TRSPX_bt_inited_handler(evt);
        break;
    case BLE_GAP_EVT_CONNECTED:
        printf("master sets interval = %d, latency = %d, timeout = %d\n",
               evt->evt.gap_evt.params.connected.connInterval,
               evt->evt.gap_evt.params.connected.connLatency,
               evt->evt.gap_evt.params.connected.supervisionTimeout);
        TRSPX_connection_complete_handler(evt);
        break;
    case BLE_GAP_EVT_DISCONNECTED:
        TRSPX_disconnection_complete_handler(evt);
        break;
    case BLE_GATT_EVT_MTU_EXCHANGED:
        TRSPX_mtu_exchanged(evt);
        break;
    case BLE_GAP_EVT_CONNECT_PARM_UPDATE:
        if(!evt->evt.gap_evt.params.conn_param_update.status)
            printf("master updates interval = %d, latency = %d, timeout = %d\n",
                   evt->evt.gap_evt.params.conn_param_update.conn_interval,
                   evt->evt.gap_evt.params.conn_param_update.slave_latency,
                   evt->evt.gap_evt.params.conn_param_update.conn_sup_timeout);
        else
            printf("connection update fail!!\n");
        break;
    }
}

void TRSPX_init(void)
{
    TRSPX_service_init();
    BLE_att_set_default_mtu(TRSPX_DEFAULT_MTU);
}


