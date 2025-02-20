/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME
    trspx.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef __TRSPX__HH_
#define __TRSPX__HH_

#include "bt.h"
#include "ble_gap_sm.h"
#include "trspx_gatt.h"
#include "trspx_typedef.h"

/******************************************************************************/
/* connection parameter                                                       */
/******************************************************************************/
#define CONN_INTERVAL              10
#define SLAVE_LATENCY              29
#define UART_INS1 0
#define UART_INS2 1

#ifdef UART1_TRSPX_PORT
#define TRSPX_UART_PORT            UART_INS1
#elif defined(UART2_TRSPX_PORT)
#define TRSPX_UART_PORT            UART_INS2
#endif
/******************************************************************************/
/* public variables                                                           */
/******************************************************************************/
extern TRSPX_BLE_STATUS TRSPX_ble_status;
extern uint32_t TRSPX_mtu;

/******************************************************************************/
/* functions                                                                 */
/******************************************************************************/
void TRSPX_init(void);
void TRSPX_bt_evt_hdl(bt_evt_t *evt);

#endif
