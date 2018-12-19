/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME
    remote_gatt.c
DESCRIPTION
NOTES
********************************************************************************/
#include "ble_gatt_server.h"
#include "service_device_information.h"
#include "service_battery.h"
#include "service_human_interface_device.h"
#include "service_generic_access.h"
#include "service_generic_attribute.h"
#include "service_device_firmware_update_OTA.h"
#include "SimpleHOGP_Gap.h"

#include <stdio.h>

/******************************************************************************/
/*Defines                                                                     */
/******************************************************************************/
#define VID 0x0416
#define PID 0xABCD
#define VER 0x0101

/******************************************************************************/
/*Variables                                                                   */
/******************************************************************************/
uint8_t SIMPLE_hids_cp[1];
uint8_t SIMPLE_hids_report1[2];
uint8_t SIMPLE_hids_report2[8]; //modifier, reserver, key[6]
uint8_t SIMPLE_adpcm_codecsel;

uint16_t report1_handle;
uint16_t report2_handle;

static uint8_t recon_addr[6];

static uint8_t SIMPLE_hids_map[] =
{
    0x05, 0x0c,        /* USAGE_PAGE (Consumer Devices) */
    0x09, 0x01,        /* USAGE (Consumer Control) */
    0xa1, 0x01,        /* COLLECTION (Application) */
    0x85, 0x01,        /*  REPORT_ID (1) */
    0x19, 0x00,        /*  USAGE_MINIMUM (0) */
    0x2A, 0x9c, 0x02,  /*  USAGE_MAXIMUM (29c) */
    0x15, 0x00,        /*  LOGICAL_MINIMUM (0) */
    0x26, 0x9c, 0x02,  /*  LOGICAL_MAXIMUM (29c) */
    0x95, 0x01,        /*  REPORT_COUNT (1) */
    0x75, 0x10,        /*  REPORT_SIZE (16) */
    0x81, 0x00,        /*  INPUT (Data,Ary,Abs) */
    0xC0,              /* END_COLLECTION (Application) */


    0x05, 0x01,           /* Usage Page (Generic Desktop)      */ \
    0x09, 0x06,           /* Usage (Keyboard)                  */ \
    0xA1, 0x01,           /* Collection (Application)          */ \
    0x85, 0x02,          /*  REPORT_ID (2) */
    0x75, 0x01,           /* Report Size (1)                   */ \
    0x95, 0x08,           /* Report Count (8)                  */ \
    0x05, 0x07,           /* Usage Page (Key codes)            */ \
    0x19, 0xE0,           /* Usage Minimum (224)               */ \
    0x29, 0xE7,           /* Usage Maximum (231)               */ \
    0x15, 0x00,           /* Logical Minimum (0)               */ \
    0x25, 0x01,           /* Logical Maximum (1)               */ \
    0x81, 0x02,           /* Input (Data, Variable, Absolute)  */ \
    0x95, 0x01,           /* Report Count (1)                  */ \
    0x75, 0x08,           /* Report Size (8)                   */ \
    0x81, 0x03,           /* Input (xxxxxx)                    */ \
    0x95, 0x05,           /* Report Count (5)                  */ \
    0x75, 0x01,           /* Report Size (1)                   */ \
    0x05, 0x08,           /* Usage Page (LED)                  */ \
    0x19, 0x01,           /* Usage Minimum (1)                 */ \
    0x29, 0x05,           /* Usage Maximum (5)                 */ \
    0x91, 0x02,           /* Output (Data, Variable, Absolute) */ \
    0x95, 0x01,           /* Report Count (1)                  */ \
    0x75, 0x03,           /* Report Size (3)                   */ \
    0x91, 0x03,           /* Output (Constant)                 */ \
    0x95, 0x06,           /* Report Count (6)                  */ \
    0x75, 0x08,           /* Report Size (8)                   */ \
    0x15, 0x00,           /* Logical Minimum (0)               */ \
    0x26, 0xFF, 0x00,     /* Logical Minimum (255)             */ \
    0x05, 0x07,           /* Usage Page (Key codes)            */ \
    0x19, 0x00,           /* Usage Minimum (0)                 */ \
    0x29, 0xFF,           /* Usage Maximum (255)               */ \
    0x81, 0x00,           /* Input (Data, Array)               */ \
    0xC0,                 /* END_COLLECTION                    */ \
};

/******************************************************************************/
/*static function                                                             */
/******************************************************************************/
static void _SIMPLE_device_name_cb(ATT_CB_TYPE type, uint8_t linkindex, uint16_t handle)
{
    if(type == CB_AFTER_WRITING)
    {
        printf("device name changed by master, may save to flash.\n");
    }
}

static void _SIMPLE_recon_addr_cb(ATT_CB_TYPE type, uint8_t linkindex, uint16_t handle)
{
    if(type == CB_AFTER_WRITING)
    {
        printf("reconnect address written by master.\n");
    }
}

static void _SIMPLE_gap_init(void)
{
    PPCP_t ppcp = {0x0008,0x0008, 29, 0x012C};

    gas_init_para gas_i_para =
    {
        .appearance = 0x0180,
        .device_name_buf = SimpleHOGP_Gap_GetDeviceName(),
        .device_name_ini_length = 13,
        .device_name_max_length = 30,
        .device_name_write_CB = _SIMPLE_device_name_cb,
        .parameter = &ppcp,
    };

    gas_privacy_init_para gas_pi_para =
    {
        .reconnection_addr = recon_addr,
        .reconnection_addr_CB = _SIMPLE_recon_addr_cb,
    };

    GAS_init(&gas_i_para);
    GAS_support_privacy_feature(&gas_pi_para);
}

static void _SIMPLE_gatt_init(void)
{
    GATT_init(true);
}

static void _SIMPLE_dis_init(void)
{
    uint8_t pnp_id[7];
    pnp_id[0] = 0x02; //usb
    pnp_id[1] = VID & 0xff;
    pnp_id[2] = VID >> 8;
    pnp_id[3] = PID & 0xff;
    pnp_id[4] = PID >> 8;
    pnp_id[5] = VER & 0xff;
    pnp_id[6] = VER >> 8;

    dis_init_para dispara =
    {
        .manufacturer_name_string = (uint8_t*)"Airoha corp.",
        .hardware_revision_string = (uint8_t*)"A:D/B:F",
        .system_id = (uint8_t*)"SystemId",
        .pnp_id = pnp_id
    };

    DIS_init(&dispara);
}

static void _SIMPLE_bas_init(void)
{
    BAS_init(true);
}

static void _SIMPLE_hid_init(void)
{
    hids_init_para init_para =
    {
        .rmap =
        {
            .data = SIMPLE_hids_map,
            .data_len = sizeof(SIMPLE_hids_map),
            .ext_rep_ref_uuid_num = 0,
            .included_service_num = 0,
        },
        .hid_info =
        {
            .bcdHID = 0x0111,
            .bCountryCode = 0x00,
            .flags= 0x3,
        },
        .hid_cp =
        {
            .data = SIMPLE_hids_cp,
            .cb = NULL,
        },
    };

    hids_report_para report_para1 =
    {
        .report_type =  HID_REPORT_INPUT,
        .report_ID = 1,
        .data = SIMPLE_hids_report1,
        .data_len = sizeof(SIMPLE_hids_report1),
        .cb = NULL,
    };
    hids_report_para report_para2 =
    {
        .report_type =  HID_REPORT_INPUT,
        .report_ID = 2,
        .data = SIMPLE_hids_report2,
        .data_len = sizeof(SIMPLE_hids_report2),
        .cb = NULL,
    };

    HIDS_init(&init_para);

    report1_handle = HIDS_add_report(&report_para1);
    report2_handle = HIDS_add_report(&report_para2);
}


/******************************************************************************/
/*Public function                                                             */
/******************************************************************************/

void SimpleHOGP_Gatt_Init(void)
{
    _SIMPLE_gatt_init();
    _SIMPLE_gap_init();
    _SIMPLE_dis_init();
    _SIMPLE_bas_init();
    _SIMPLE_hid_init();
}

void SimpleHOGP_Send_Hid_Report(uint16_t attHandle)
{
    if(SimpleHOGP_Gap_State_Get() != SIMPLE_CONNECTED)
    {
        SimpleHOGP_Gap_Enter_Adv();
        return;
    }

    if((SimpleHOGP_Gap_Bonded() && SimpleHOGP_Gap_LinkEncrypted()))
        BLE_gatt_charact_notify(attHandle, FORCE_LINK0);
    else
        BLE_gatt_charact_notify(attHandle, ALL_CCCD_ENABLED_LINK);
}
