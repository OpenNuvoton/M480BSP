/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_device_firmware_update_OTA.c
DESCRIPTION
NOTES
********************************************************************************/
#include "ab16xx.h"
#include "ble_gatt_server.h"
#include "service_device_firmware_update_OTA.h"
#include "dfu.h"


enum
{
    DFU_OTA_READ_STATUS = 1,
    DFU_OTA_ERASE_FLASH,
    DFU_OTA_WRITE_FLASH,
    DFU_OTA_CHANGE_AREA,
    DFU_OTA_CLEAR_CACHE_READ_STATUS,
    DFU_OTA_READ_BOOT_CODE_VER,
    DFU_OTA_READ_FLASH_INFO,
    DFU_OTA_UNKNOWN_CMD = 0xFF,
};

static bool ota_enabled = false;

static OTA_STATUS_CB  ota_cb;
static uint8_t ota_cmd[270];
static uint8_t ota_resp[20];
static uint8_t ota_cccd[2];
static uint16_t cmd_handle;
static uint16_t resp_handle;



/******************************************************************************
 * Internal function
 ******************************************************************************/
void _OTA_read_status(void)
{
    typedef struct
    {
        uint8_t     command;
        uint8_t     code_area;
        uint8_t     area1_status;
        uint32_t    area1_revision;
        uint32_t    area1_checksum;
        uint8_t     area2_status;
        uint32_t    area2_revision;
        uint32_t    area2_checksum;
    } __attribute__((packed)) cmd_resp;

    DFU_DEVICE_STATUS  status;
    cmd_resp * resp = (cmd_resp *)ota_resp;

    AB_DFU_check_status(&status);

    resp->command = DFU_OTA_READ_STATUS;
    resp->code_area = status.curr_area;
    resp->area1_status = status.area1.status;
    resp->area1_revision = status.area1.revision;
    resp->area1_checksum = status.area1.checksum;
    resp->area2_status = status.area2.status;
    resp->area2_revision = status.area2.revision;
    resp->area2_checksum = status.area2.checksum;

    BLE_att_set_attribute_length(resp_handle, 20);
    BLE_gatt_charact_notify(resp_handle, ALL_CCCD_ENABLED_LINK);

    printf("[OTA] read status.\n");
    ble_gap_disable_latency(1);//disable latency

    if(ota_cb)
        ota_cb(OTA_STARTED);

}
/*
void _OTA_read_status_ex(void)
{
    typedef struct
    {
        uint8_t     command;
        uint8_t     code_area;
        uint8_t     area1_status;
        uint32_t    area1_revision;
        uint32_t    area1_checksum;
        uint8_t     area2_status;
        uint32_t    area2_revision;
        uint32_t    area2_checksum;
    } __attribute__((packed)) cmd_resp;

    DFU_DEVICE_STATUS  status;
    cmd_resp * resp = (cmd_resp *)ota_resp;

    DRV_MCU_ClearCache();

    AB_DFU_check_status(&status);

    resp->command = DFU_OTA_CLEAR_CACHE_READ_STATUS;
    resp->code_area = status.curr_area;
    resp->area1_status = status.area1.status;
    resp->area1_revision = status.area1.revision;
    resp->area1_checksum = status.area1.checksum;
    resp->area2_status = status.area2.status;
    resp->area2_revision = status.area2.revision;
    resp->area2_checksum = status.area2.checksum;

    BLE_att_set_attribute_length(resp_handle, 20);
    BLE_gatt_charact_notify(resp_handle, ALL_CCCD_ENABLED_LINK);

    printf("OTA_read_status_2\n");

    if(ota_cb)
        ota_cb(OTA_STARTED);

}
*/

void _OTA_erase_flash(void)
{
    typedef struct
    {
        uint8_t     command;
        uint32_t    addr;
        uint8_t     type;
    }__attribute__((packed))cmd_stru;

    uint32_t alignmask[3] = {0xFFFF,0x7FFF,0x0FFF};

    cmd_stru * cmd = (cmd_stru *)ota_cmd;

    memcpy(ota_resp, ota_cmd, 5);


    if(cmd->addr < AREA1_START)
    {
        ota_resp[5] = 0x56;
        printf("OTA err: erase invalid address.\n");
    }
    else if(cmd->type>ERASE_4KB)
    {
        ota_resp[5] = 0x78;
        printf("OTA err: erase invalid type.\n");
    }
    else if(cmd->addr&alignmask[cmd->type])
    {
        ota_resp[5] = 0x87;
        printf("OTA err: erase invalid alignment.\n");
    }
    else
    {
        ota_resp[5] = 0x00;
        printf("[OTA] Erase %2dKB from 0x%06X\n",(cmd->type == ERASE_64KB)?64:(cmd->type == ERASE_32KB)?32:4,cmd->addr);
        AB_DFU_erase_flash(cmd->addr,cmd->type);
    }

    BLE_att_set_attribute_length(resp_handle, 6);
    BLE_gatt_charact_notify(resp_handle, ALL_CCCD_ENABLED_LINK);

}

void _OTA_write_flash(void)
{
    typedef struct
    {
        uint8_t     command;
        uint32_t    addr;
        uint8_t     length;
        uint8_t     data_start[1];
    }__attribute__((packed))cmd_stru;

    cmd_stru * cmd = (cmd_stru *)ota_cmd;
    uint8_t err = 0;

    if(cmd->addr < AREA1_START)
    {
        err = 0x56;
        printf("OTA err: invalid address.\n");
    }
    else if(cmd->length)
    {
        if(BLE_att_get_attribute_length(cmd_handle) != (cmd->length+6))//command not complete yet
        {
            return;
        }

        err = DRV_Flash_ByteProgram(cmd->addr, cmd->data_start, cmd->length);
        printf("[OTA] write 0x%05X-0x%05X %s.\n",cmd->addr, cmd->addr+cmd->length-1,(err)?"(X)":"(O)");
    }
    else
    {
        if(BLE_att_get_attribute_length(cmd_handle) != 262)//command not complete yet
        {
            return;
        }


        if(cmd->addr & 0xFF)
        {
            err = 0x87;
            printf("OTA err: address not page aligned.\n");
        }
        else
        {
            uint32_t buf[64];

            memcpy(buf, cmd->data_start,256);

            err = DRV_Flash_PageProgram(cmd->addr, buf, NULL);
            printf("[OTA] page write from 0x%05X %s.\n",cmd->addr,(err)?"(X)":"(O)");
        }
    }

    memcpy(ota_resp, ota_cmd, 5);
    ota_resp[5] = err;

    BLE_att_set_attribute_length(resp_handle, 6);
    BLE_gatt_charact_notify(resp_handle, ALL_CCCD_ENABLED_LINK);

}

void _OTA_change_area(void)
{
    typedef struct
    {
        uint8_t     command;
        uint8_t     status;
    } __attribute__((packed)) cmd_resp;

    cmd_resp * resp = (cmd_resp *)ota_resp;

    resp->command = DFU_OTA_CHANGE_AREA;
    resp->status = AB_DFU_set_active_code_area(ota_cmd[1]);

    BLE_att_set_attribute_length(resp_handle, 2);
    BLE_gatt_charact_notify(resp_handle, ALL_CCCD_ENABLED_LINK);

    printf("[OTA] change_area\n");
    ble_gap_disable_latency(0);//enable latency

    if(ota_cb)
        ota_cb(OTA_FINISHED);
}

void _OTA_read_bootcode_ver(void)
{
    typedef struct
    {
        uint8_t     command;
        uint32_t    boot_ver;
    } __attribute__((packed)) cmd_resp;

    cmd_resp * resp = (cmd_resp *)ota_resp;
    resp->command = DFU_OTA_READ_BOOT_CODE_VER;
    resp->boot_ver= *(uint32_t *)(0x803F8);

    BLE_att_set_attribute_length(resp_handle, 5);
    BLE_gatt_charact_notify(resp_handle, ALL_CCCD_ENABLED_LINK);

    printf("[OTA] boot Version: %08X\n",resp->boot_ver);
}

void _OTA_read_flash_info(void)
{
    typedef struct
    {
        uint8_t     command;
        uint32_t    area1_start;
        uint32_t    area2_start;
    } __attribute__((packed)) cmd_resp;

    cmd_resp * resp = (cmd_resp *)ota_resp;
    resp->command = DFU_OTA_READ_FLASH_INFO;
    resp->area1_start = AREA1_START - 0x80000;
    resp->area2_start = AREA2_START - 0x80000;

    BLE_att_set_attribute_length(resp_handle, 9);
    BLE_gatt_charact_notify(resp_handle, ALL_CCCD_ENABLED_LINK);

    printf("[OTA] flash info: 0x%5X,0x%5X\n",AREA1_START,AREA2_START);
}

void _OTA_unknown_command(void)
{
    typedef struct
    {
        uint8_t     error;
    } __attribute__((packed)) cmd_resp;

    cmd_resp * resp = (cmd_resp *)ota_resp;
    resp->error= DFU_OTA_UNKNOWN_CMD;

    BLE_att_set_attribute_length(resp_handle, 1);
    BLE_gatt_charact_notify(resp_handle, ALL_CCCD_ENABLED_LINK);

    printf("OTA err: cmd unknown\n");

}

void _OTA_command_CB(ATT_CB_TYPE type, uint8_t linkindex, uint16_t handle)
{
    if(!ota_enabled)
    {
        printf("ota function not enabled!\n");

        ota_resp[0] = 0xFF;
        BLE_att_set_attribute_length(resp_handle, 1);
        BLE_gatt_charact_notify(resp_handle, ALL_CCCD_ENABLED_LINK);
        return;
    }
    else
    {
        switch(ota_cmd[0])
        {
            case DFU_OTA_READ_STATUS:
                _OTA_read_status();
                break;
            case DFU_OTA_ERASE_FLASH:
                _OTA_erase_flash();
                break;
            case DFU_OTA_WRITE_FLASH:
                _OTA_write_flash();
                break;
            case DFU_OTA_CHANGE_AREA:
                _OTA_change_area();
                break;
//            case DFU_OTA_CLEAR_CACHE_READ_STATUS:
//                _OTA_read_status_ex();
//                break;
            case DFU_OTA_READ_BOOT_CODE_VER:
                _OTA_read_bootcode_ver();
                break;
            case DFU_OTA_READ_FLASH_INFO:
                _OTA_read_flash_info();
                break;
            default:
                _OTA_unknown_command();
                break;
        }
    }
}



/******************************************************************************
 * API function
 ******************************************************************************/


void OTA_init(OTA_STATUS_CB cb)
{
    if(1)
    {
        gatt_add_service_para servicepara =
        {
            .type = primary_service,
            .size = UUID_128bit,
            .UUID = {'e', 'c', 'i', 'v', 'r', 'e', 'S', 'U', 'F', 'D', 'a', 'h', 'o', 'r', 'i', 'A'},
        };

        BLE_gatt_add_service(&servicepara);
    }

    if(1)
    {
        gatt_add_charact_para charactpara_command =
        {
            .size = UUID_128bit,
            .UUID = {'d', 'n', 'a', 'm', 'm', 'o', 'C', 'U', 'F', 'D', 'a', 'h', 'o', 'r', 'i', 'A'},
            .property = C_WRITE_NO_RSP|C_WRITE,
            .permission = A_RB_WP,
            .data_initial_length = 1,
            .data_maximum_length = 270,
            .char_data = ota_cmd,
            .cb = _OTA_command_CB,
        };

        cmd_handle = BLE_gatt_add_charact(&charactpara_command);
    }

    if(1)
    {
        gatt_add_charact_para charactpara_response =
        {
            .size = UUID_128bit,
            .UUID = {'p', 's', 'e', 'R', 'd', 'm', 'C', 'U', 'F', 'D', 'a', 'h', 'o', 'r', 'i', 'A'},
            .property = C_NOTIFY,
            .permission = A_RB_WB,
            .data_initial_length = 1,
            .data_maximum_length = 20,
            .char_data = ota_resp,
            .cb = NULL,
        };

        resp_handle = BLE_gatt_add_charact(&charactpara_response);
    }

    if(1)
    {
        gatt_add_descrip_para descrippara =
        {
            .size = UUID_16bit,
            .UUID = {0x02,0x29},
            .permission = A_RP_WP,
            .data_initial_length = 2,
            .data_maximum_length = 0,
            .desc_data = ota_cccd,
            .cb = NULL,
        };

        BLE_gatt_add_descrip(&descrippara);
    }

    ota_cb = cb;
}

void OTA_change_permission(OTA_PERMISSION_ENUM sel)
{
    switch(sel)
    {
        case OTA_ENABLED:
            ota_enabled = true;
            break;
        case OTA_DISABLED:
            ota_enabled = false;
            break;
    }
}
