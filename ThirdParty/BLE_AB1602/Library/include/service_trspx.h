/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_trspx.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef _TRSPX_SERVICE_H_
#define _TRSPX_SERVICE_H_
/*!
     @defgroup PAGE_SERVICE_TRSPX service_trspx.h
     @{
        @page PAGE_SERVICE_TRSPX service_trspx.h
        service_trspx.h provides an easy way to implement TRSPX service.
*/

#include "ble_gatt_server.h"

/*
    @brief TRSPX service attribute handle;
*/
extern uint16_t trspx_service_handle;
/*
    @brief TRSPX indication attribute handle;
*/
/*
    @brief TRSPX notification attribute handle;
*/
extern uint16_t trspx_notify_handle;
/*
    @brief TRSPX cccd attribute handle;
*/
extern uint16_t trspx_cccd_handle;
/*
    @brief TRSPX write attribute handle;
*/
extern uint16_t trspx_write_handle;

/*!
    @brief trspx service initialization Parameters
*/
typedef struct
{
    uint8_t* write_data; /**< Data buffer pointer for receiving data*/
    uint8_t* read_data;  /**< Data buffer pointer for sending data*/
    uint8_t* trspx_cccd; /**< Data buffer pointer for cccd*/
    ATTCB trspx_write_CB; /**< callback function for GATT write operation*/
    ATTCB trspx_cccd_CB; /**< callback function for CCCD descriptor write*/
}trspx_init_para;

/*!
    @brief Initialization function of trspx service.
    @param para @ref trspx_init_para.
    @return None.
*/

void TRSPX_service_init_para(trspx_init_para * para);

#endif
