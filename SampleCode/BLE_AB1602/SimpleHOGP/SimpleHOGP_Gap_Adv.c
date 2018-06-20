/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME
    SimpleHOGP_adv.c
DESCRIPTION
NOTES
********************************************************************************/
#include "SimpleHOGP_Gap.h"
#include <stdio.h>

/******************************************************************************/
/*static function                                                             */
/******************************************************************************/

static void SimpleHOGP_ble_adv_enable_cb(bool isuccess, uint8_t err_code)
{

    printf("enable undirected advertising %s\n", isuccess ? "success" : "failed");

    SimpleHOGP_Gap_State_Set(isuccess ? SIMPLE_ADVING : SIMPLE_IDLE);

}

static void SimpleHOGP_ble_dir_adv_enable_cb(bool isuccess, uint8_t err_code)
{
    printf("enable directed advertising %s\n", isuccess ? "success" : "failed");
    SimpleHOGP_Gap_State_Set(isuccess ? SIMPLE_ADVING : SIMPLE_IDLE);
}

static void SimpleHOGP_ble_set_no_scan_adv_param_and_enable(bool isuccess,
        uint8_t err_code)
{
    ble_gap_adv_params parm =
    {
        .ad_type = ble_ad_type_ind,
        .peer_addr = NULL,
        .self_addr_type = ble_addr_type_public,
        .filter = ble_filter_filter_scan,
        .min_interval = 0x0020,
        .max_interval = 0x0040,
        .channel_mask = 0x7,
    };
    //start adv
    ble_gap_adv_start(&parm, SimpleHOGP_ble_adv_enable_cb);
    printf("set adv param and enable\n");
}

static void SimpleHOGP_ble_set_adv_param_and_enable(bool isuccess,
        uint8_t err_code)
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
    ble_gap_adv_start(&parm, SimpleHOGP_ble_adv_enable_cb);
    printf("set adv param and enable\n");
}

/******************************************************************************/
/*Public function                                                             */
/******************************************************************************/

void SimpleHOGP_normal_undir_adv(void)
{
    uint8_t ad[] =
    {
        0x02, 0x01, 0x05,
        0x03, 0x19, 0x80, 0x01,
        0x03, 0x02, 0x12, 0x18,
        0x13, 0xFF, 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0xFF, 0xFF, 0xFF, 'A', 'i', 'r', 'o', 'h', 'a'
    };
    printf("set normal undirected adv data\n");

    SimpleHOGP_Gap_State_Set(SIMPLE_ADV_REQUESTING);
    ble_gap_adv_data_set(ad, sizeof(ad), SimpleHOGP_ble_set_adv_param_and_enable);
}

void SimpleHOGP_bonded_undir_adv(void)
{
    uint8_t ad[] =
    {
        0x02, 0x01, 0x05,
        0x03, 0x19, 0x80, 0x01,
        0x03, 0x02, 0x12, 0x18,
        0x13, 0xFF, 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
        0xFF, 0xFF, 0xFF, 'A', 'i', 'r', 'o', 'h', 'a'

    };
    printf("set bonded undirected adv data\n");
    SimpleHOGP_Gap_State_Set(SIMPLE_ADV_REQUESTING);
    ble_gap_adv_data_set(ad, sizeof(ad),
                         SimpleHOGP_ble_set_no_scan_adv_param_and_enable);
}

void SimpleHOGP_dir_adv(void)
{
    ble_gap_adv_params parm =
    {
        .ad_type = ble_ad_type_direct_ind,
        .peer_addr = SimpleHOGP_Gap_Get_BondedPeer(),
        .self_addr_type = ble_addr_type_public,
        .filter = ble_filter_any,
        .min_interval = 0x0020,
        .max_interval = 0x0040,
        .channel_mask = 0x7, //use two channel for now
    };
    //start adv
    SimpleHOGP_Gap_State_Set(SIMPLE_ADV_REQUESTING);
    ble_gap_adv_start(&parm, SimpleHOGP_ble_dir_adv_enable_cb);
}
