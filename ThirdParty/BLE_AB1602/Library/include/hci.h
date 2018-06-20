/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    hci.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef _HCI_HH_
#define _HCI_HH_
#include <stdint.h>
#include <stdbool.h>
/******************************************************************************
 * Macro
 ******************************************************************************/
#define MAX_SUPPORT_CTROLLER 1

/******************************************************************************
 * Typedef
 ******************************************************************************/
typedef void (*hci_evt_recv)(uint8_t evt, uint8_t len, uint8_t* buf);
typedef void (*hci_dat_recv)(uint16_t handle, uint16_t len, uint8_t *buf);
typedef void (*hci_inited_callback)(bool is_success);
typedef enum
{

    set_pub_address = 0, //6 bytes address
    set_tx_power = 1,    //1 bytes -127 db ~ 128 dbm
}hci_ctrler_specific;
/******************************************************************************
 * Functions
 ******************************************************************************/
void hci_init(hci_inited_callback cb, hci_dat_recv dat_cb, hci_evt_recv evt_cb, void *cdata[], uint8_t ccount);
void hci_cmd_send(uint16_t op, uint8_t *parm, uint8_t len);
void hci_acl_send(uint16_t handle, uint8_t *dat, uint16_t len);
void hci_log_set(uint8_t level);

#endif
