#include "SimpleHOGP_Gatt.h"
#include "SimpleHOGP_Gap.h"
#include "SimpleHOGP_Gap_Adv.h"
#include "cfg_sector_m0.h"
#include <string.h>
void SimpleHOGP_Init()
{
    const void *btdata[6] = {NULL/*mp_data*/, &cfg_sector};
    BT_InitEx2(SimpleHOGP_bt_evt_hdl, (void**)btdata, 2, BT_LOG_HCI_CMD | BT_LOG_HCI_EVT);

    SimpleHOGP_Gap_Init((uint8_t*)"\x00\x11\x22\x33\x44\x55", "Nuvoton AB1602 HID");
    SimpleHOGP_Gatt_Init();
}


void SimpleHOGP_Send_MediaKey(uint16_t key)
{
    SIMPLE_hids_report1[0] = (uint8_t)(key & 0xFF);
    SIMPLE_hids_report1[1] = (uint8_t)(key >> 8);

    SimpleHOGP_Send_Hid_Report(report1_handle);


    //release
    memset(SIMPLE_hids_report1, 0, 2);
    SimpleHOGP_Send_Hid_Report(report1_handle);
}

void SimpleHOGP_Send_Key(uint8_t modifier, uint8_t key)
{
    memset(SIMPLE_hids_report2, 0, 8);
    SIMPLE_hids_report2[0] = modifier;
    SIMPLE_hids_report2[2] = key;
    SimpleHOGP_Send_Hid_Report(report2_handle);

    SIMPLE_hids_report2[0] = 0;
    SIMPLE_hids_report2[2] = 0;
    SimpleHOGP_Send_Hid_Report(report2_handle);
}

