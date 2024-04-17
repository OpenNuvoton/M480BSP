/*************************************************************************//**
 * @file     tftp.h
 * @version  V1.00
 * @brief    TFTP header file
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __TFTP_H__
#define __TFTP_H__

#include "netif/m480_eth.h"

#define TFTP_OPCODE_RRQ         1
#define TFTP_OPCODE_WRQ         2
#define TFTP_OPCODE_DATA        3
#define TFTP_OPCODE_ACK         4
#define TFTP_OPCODE_ERROR       5

#define TFTP_PORT               69
#define TFTP_TIMEOUT            500    //msec
#define TFTP_MAX_RETRIES        5
#define TFTP_BLOCK_LENGTH       512

#define BUFP_STATIC_NUM         RX_DESCRIPTOR_NUM
#define BUFP_STATIC_SIZE        0x800UL
#define BUFP_STATIC_BASE        (0x20028000UL - (BUFP_STATIC_NUM + 1) * BUFP_STATIC_SIZE)
#if (BUFP_STATIC_NUM > 15)
  #error "BUFP_STATIC_NUM over range!"
#endif
#if (PACKET_BUFFER_SIZE > BUFP_STATIC_SIZE)
  #error "PACKET_BUFFER_SIZE over range!"
#endif
#define BUFP_IDENTIFITER_ADDR   (0x20028000UL - 4)
#define BUFP_IDENTIFITER        0x5A5A3C3CUL

enum tftp_error
{
    TFTP_ERROR_NOT_DEFINED,         // 0
    TFTP_ERROR_FILE_NOT_FOUND,      // 1
    TFTP_ERROR_ACCESS_VIOLATION,    // 2
    TFTP_ERROR_DISK_FULL,           // 3
    TFTP_ERROR_ILLEGAL_OPERATION,   // 4
    TFTP_ERROR_UNKNOWN_ID,          // 5
    TFTP_ERROR_FILE_EXISTS,         // 6
    TFTP_ERROR_NO_SUCH_USER         // 7
};

enum tftp_state
{
    TFTP_STATE_IDLE,                // 0
    TFTP_STATE_WRQ,                 // 1
    TFTP_STATE_RRQ,                 // 2
};

void tftp_client_init(void);

#endif // __TFTP_H__
