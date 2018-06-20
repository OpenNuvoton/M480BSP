/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME
    trspx_gatt.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef __TRSPX_GATT_HH__
#define __TRSPX_GATT_HH__

#include "service_trspx.h"


extern uint8_t TRSPX_Write_Data[200];
extern uint8_t TRSPX_Read_Data[200];
extern uint8_t TRSPX_CCCD_Data[2];

void TRSPX_service_init(void);
void TRSPX_send(uint16_t len);

#endif
