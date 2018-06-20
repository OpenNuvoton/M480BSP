/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    service_human_interface_device.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef _HID_SERVICE_H_
#define _HID_SERVICE_H_

/*!

     @defgroup PAGE_SERVICE_HID service_human_interface_device.h
     @{
        @page PAGE_SERVICE_HID service_human_interface_device.h
        service_human_interface_device.h provides an easy way to implement human interface device service.
*/
#include "ble_gatt_server.h"


/*!
     @name  [Defines]
     @brief defines used by @ref hids_char_report_map_t.
     @{
 */
    #define MAX_EXT_REP_REF_NUM             5  /**< maximum number of external report reference */
    #define MAX_INCLUDED_SERVICE_NUM        3  /**< maximum number of included services */
/*!  @} */

/*!
    @brief Report map characteristic initialization parameters.
*/
typedef struct
{
    uint8_t *       data;                                                   /**< hid report map data pointer    */
    uint16_t        data_len;                                               /**< hid report map data length     */
    uint16_t        ext_rep_ref_uuid[MAX_EXT_REP_REF_NUM];                  /**< list of extended report reference UUID */
    uint16_t        included_service_handle[MAX_INCLUDED_SERVICE_NUM];      /**< list of included service attribute handle*/
    uint8_t         ext_rep_ref_uuid_num;                           /**< number of extended report reference UUIDs, must< @ref  MAX_EXT_REP_REF_NUM */
    uint8_t         included_service_num;                           /**< number of included services, must <@ref MAX_INCLUDED_SERVICE_NUM*/
}hids_char_report_map_t;

/*!
    @brief HID information characteristic initialization parameters.
*/
typedef struct
{
    uint16_t                            bcdHID;         /**< version number of base USB HID Spec. */
    uint8_t                             bCountryCode;   /**< Identifies which country the hardware is localized for. */
    uint8_t                             flags;          /**< Bit mask\n Bit0: RemoteWake.\n Bit1: NormallyConnectable. */
}hids_char_hid_information_t;

/*!
    @brief HID control point characteristic initialization parameters.
*/
typedef struct
{
    uint8_t *                           data;           /**< hid control point data pointer */
    ATTCB                               cb;             /**< hid control pointer call bacck function*/
}hids_char_hid_control_point_t;

/*!
    @brief Human information service initialization parameters.
*/
typedef struct
{
    hids_char_report_map_t              rmap;       /**<  report map @ref hids_char_report_map_t*/
    hids_char_hid_information_t         hid_info;   /**<  hid information  @ref hids_char_hid_information_t*/
    hids_char_hid_control_point_t       hid_cp;     /**<  hid control point @ref hids_char_hid_control_point_t*/
}hids_init_para;

/*!
    @brief HID report type.
*/
typedef enum
{
    /*!1*/
    HID_REPORT_INPUT    = 1,
    /*!2*/
    HID_REPORT_OUTPUT   = 2,
    /*!3*/
    HID_REPORT_FEATURE  = 3,
}HIDS_REPORT_TYPE;

/*!
    @brief HID report characteristic initialization parameter.
*/
typedef struct
{
    HIDS_REPORT_TYPE                    report_type;    /**< hid report type @ref HIDS_REPORT_TYPE */
    uint8_t                             report_ID;      /**< hid report ID  */
    uint8_t *                           data;           /**< hid report data pointer */
    uint16_t                            data_len;       /**< hid report data length */
    ATTCB                               cb;             /**< hid report call back function*/
}hids_report_para;


/*!
    @brief Initialization function of human interface device service.
    @param para @ref hids_init_para.
    @return None.
*/
void HIDS_init(hids_init_para * para);

/*!
    @brief Initialization function of human interface device service.
    @param para @ref hids_report_para.
    @return att_handle attribute handle of report characteristic value.

    @attention HID service requires at least one report characteristic.
*/
att_handle HIDS_add_report(hids_report_para * para);



// not supported yet
//att_handle hids_add_protocol_mode(void);
//att_handle hids_add_boot_keyboard_report(void);
//att_handle hids_add_boot_mouse_report(void);





/*!
    @}
*/

#endif
