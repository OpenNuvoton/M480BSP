/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    bt.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef __BT_HH__
#define __BT_HH__

#include "ble_gap.h"
#include "ble_sm.h"
#include "ble_gap_sm.h"
#include "ble_gatt_client.h"


 /*! 
     
     @defgroup PAGE_API_BT bt.h
     @{
        @page PAGE_API_BT bt.h
        
        bt.h provide BT API.
        
*/

/*************************************************************************
* macro
*************************************************************************/
/*!
    @name BT_LOG_FLAGS [Defines]
    @anchor BT_LOG_FLAGS
    Bitwise switch flag for BT Log on UART. Used in BT_Log_Enable.
   @{ 
*/
#define BT_LOG_NONE 0x00000000
#define BT_LOG_HCI_CMD 0x00000001    ///< HCI command log
#define BT_LOG_HCI_EVT 0x00000002    ///< HCI event log
#define BT_LOG_HCI_TXDAT 0x00000004  ///< HCI TX data log
#define BT_LOG_HCI_RXDAT 0x00000008  ///< HCI RX data log
/**@} */

/*************************************************************************
* Typedef
*************************************************************************/

/*!
    @brief MISC Event IDs.
    IDs that uniquely identify an event.
 */
typedef enum
{
    BT_MISC_EVENT_INITED = BT_EVENT_MISC, ///< Event for BT Initailized.
}bt_misc_event_id;


/*!
    @brief Event structure for @ref BT_MISC_EVENT_INITED
*/
typedef struct
{
    bool is_success;
}bt_init_evt_t;


/*!
    @brief MISC event structure.
*/
typedef struct
{
  union                    
  {
      bt_init_evt_t inited; ///< BT_MISC_EVENT_INITED event structure.
  }param; ///< Event parameter
} ble_misc_evt_t;

/*!
    @brief All event structure
*/
typedef struct
{
  uint32_t evt_id; ///< Event ID

  union
  {
    ble_misc_evt_t misc_evt; ///< MISC event structure
    ble_gap_evt_t gap_evt;   ///< GAP event structure
    ble_sm_evt_t sm_evt;     ///< SM event structure
    ble_gatt_evt_t gatt_evt; ///< GATT event structure
  } evt; ///< Event parameter body.
} bt_evt_t;

/*!
    @brief Event handler
    Event handler, passed in Bt_Init function.
*/
typedef void (*bt_event_handler)(bt_evt_t *);
/*************************************************************************
* API
*************************************************************************/
/*!
    @brief Initialize BT 
    @param handler Global event handler
    @note This function was deprecated. Please use BT_InitEx2.
*/
void BT_Init(bt_event_handler handler);

/*!
    @brief Initialize BT with controller specific data
    @param handler Global event handler
    @param cdata Pre-defined data for BT controller.
    @param log_level Log level switch. @ref BT_LOG_FLAGS
    @note This function was deprecated. Please use BT_InitEx2.
*/
void BT_InitEx(bt_event_handler handler, void *cdata, uint32_t log_level);

/*!
    @brief Initialize BT with controller specific data
    @param handler Global event handler
    @param cdata Pre-defined data for BT controller.
    @param count Pre-define data count for BT controller.
    @param log_level Log level switch. @ref BT_LOG_FLAGS
*/
void BT_InitEx2(bt_event_handler handler, void *cdata[], uint8_t count, uint32_t log_level);

/*!
    @brief BT main Loop
*/
void BT_Loop(void);

/*!
    @brief BT log enable/disable
    @param log_level Log level switch. @ref BT_LOG_FLAGS
*/
void BT_Log_Enable(uint32_t log_level);

/*!
    @brief BT Pending TX Data 
    Query how manay data (In bytes) is not send out.
*/
uint32_t BT_Pending_TxCnt(void);

/*!
    @brief Pause BT TX data transmit
*/
void BT_Pause_Tx(bool is_pause);


/*!
@}
*/
#endif
