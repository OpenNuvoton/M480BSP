/*************************************************************************//**
 * @file     tftp.h
 * @version  V1.00
 * @brief    TFTP header file
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef __TFTP_H__
#define __TFTP_H__


#define TFTP_OPCODE_RRQ         1
#define TFTP_OPCODE_WRQ         2
#define TFTP_OPCODE_DATA        3
#define TFTP_OPCODE_ACK         4
#define TFTP_OPCODE_ERROR       5

#define TFTP_PORT               69
#define TFTP_TIMEOUT            500    //msec
#define TFTP_MAX_RETRIES        5
#define TFTP_BLOCK_LENGTH       512

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
