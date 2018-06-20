/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME
    ble_l2cap.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef __L2CAP_HH__
#define __L2CAP_HH__


 /*!

     @defgroup PAGE_API_L2CAP ble_l2cap.h
     @{
        @page PAGE_API_L2CAP ble_l2cap.h

*/


/*!
    @brief Parameter for fix CID event
*/
typedef struct
{

    uint8_t *parm; ///< parameter
    uint16_t len;  ///< parameter length
}cid_parm;

/*!
    @brief fix CID event id
*/
typedef enum
{
   cid_event_l2cap_pdu = 0,  ///< PDU incomming
   cid_event_link_connected, ///< ACL Link was connected
   cid_event_link_disconnected ///< ACL Link was disconnected
}cid_event;

/*!
    @brief Fix CID event callback function
    @param idx link index
    @param evt CID event
    @param parm CID event parameter.
*/
typedef void (*cid_callback)(uint8_t idx, cid_event evt, cid_parm parm);


/*************************************************************************
* API Functions
*************************************************************************/
/*!
    @brief Register a fix CID
    @param cid Fix channel ID
    @param cb CID event callback function
    @return true if success.
*/
bool BLE_l2cap_cid_register(uint16_t cid, cid_callback cb);

/*!
    @brief Unregister a fix CID
    @param cid Fix channel ID
*/
void BLE_l2cap_cid_unregister(uint16_t cid);
/*!
@}
*/

#endif
