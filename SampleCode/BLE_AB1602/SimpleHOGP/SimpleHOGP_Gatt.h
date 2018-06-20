/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME
    SimpleHOGP_gatt.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef __SIMPLE_HOGP_GATT_HH__
#define __SIMPLE_HOGP_GATT_HH__
#include <stdint.h>

extern uint8_t SIMPLE_hids_cp[1];
extern uint8_t SIMPLE_hids_report1[2];
extern uint8_t SIMPLE_hids_report2[8];

extern uint16_t report1_handle;
extern uint16_t report2_handle;

void SimpleHOGP_Gatt_Init(void);
void SimpleHOGP_Send_Hid_Report(uint16_t attHandle);


#endif
