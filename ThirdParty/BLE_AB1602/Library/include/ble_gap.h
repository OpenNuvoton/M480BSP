/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME
    ble_gap.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef __BLE_GAP_HH
#define __BLE_GAP_HH
#include <stdint.h>
#include "ab16xx.h"
#include "bt_constants.h"
#include "hci_constant.h"
 /*!

     @defgroup PAGE_API_BLE_GAP ble_gap.h
     @{
        @page PAGE_API_BLE_GAP ble_gap.h

        ble_gap.h provide BLE generic access profile API.

*/


/*************************************************************************
* Macro
*************************************************************************/
/**
  @name GAP Role [Defines]
  GAP Link's Roles
* @{ */
#define BLE_GAP_ROLE_MASTER 0x00 ///< Master role
#define BLE_GAP_ROLE_SLAVE 0x01 ///< Slave role
/**@} */

/*!
    @name GAP AD DATA TYPE [Defines]
    GAP Advertisement Type
   @{
*/
#define BLE_GAP_AD_TYPE_FLAGS                               0x01 ///< Flags for discoverability.
#define BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_MORE_AVAILABLE   0x02 ///< Partial list of 16 bit service UUIDs.
#define BLE_GAP_AD_TYPE_16BIT_SERVICE_UUID_COMPLETE         0x03 ///< Complete list of 16 bit service UUIDs.
#define BLE_GAP_AD_TYPE_32BIT_SERVICE_UUID_MORE_AVAILABLE   0x04 ///< Partial list of 32 bit service UUIDs.
#define BLE_GAP_AD_TYPE_32BIT_SERVICE_UUID_COMPLETE         0x05 ///< Complete list of 32 bit service UUIDs.
#define BLE_GAP_AD_TYPE_128BIT_SERVICE_UUID_MORE_AVAILABLE  0x06 ///< Partial list of 128 bit service UUIDs.
#define BLE_GAP_AD_TYPE_128BIT_SERVICE_UUID_COMPLETE        0x07 ///< Complete list of 128 bit service UUIDs.
#define BLE_GAP_AD_TYPE_SHORT_LOCAL_NAME                    0x08 ///< Short local device name.
#define BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME                 0x09 ///< Complete local device name.
#define BLE_GAP_AD_TYPE_TX_POWER_LEVEL                      0x0A ///< Transmit power level.
#define BLE_GAP_AD_TYPE_CLASS_OF_DEVICE                     0x0D ///< Class of device.
#define BLE_GAP_AD_TYPE_SIMPLE_PAIRING_HASH_C               0x0E ///< Simple Pairing Hash C.
#define BLE_GAP_AD_TYPE_SIMPLE_PAIRING_RANDOMIZER_R         0x0F ///< Simple Pairing Randomizer R.
#define BLE_GAP_AD_TYPE_SECURITY_MANAGER_TK_VALUE           0x10 ///< Security Manager TK Value.
#define BLE_GAP_AD_TYPE_SECURITY_MANAGER_OOB_FLAGS          0x11 ///< Security Manager Out Of Band Flags.
#define BLE_GAP_AD_TYPE_SLAVE_CONNECTION_INTERVAL_RANGE     0x12 ///< Slave Connection Interval Range.
#define BLE_GAP_AD_TYPE_SOLICITED_SERVICE_UUIDS_16BIT       0x14 ///< List of 16-bit Service Solicitation UUIDs.
#define BLE_GAP_AD_TYPE_SOLICITED_SERVICE_UUIDS_128BIT      0x15 ///< List of 128-bit Service Solicitation UUIDs.
#define BLE_GAP_AD_TYPE_SERVICE_DATA                        0x16 ///< Service Data - 16-bit UUID.
#define BLE_GAP_AD_TYPE_PUBLIC_TARGET_ADDRESS               0x17 ///< Public Target Address.
#define BLE_GAP_AD_TYPE_RANDOM_TARGET_ADDRESS               0x18 ///< Random Target Address.
#define BLE_GAP_AD_TYPE_APPEARANCE                          0x19 ///< Appearance.
#define BLE_GAP_AD_TYPE_ADVERTISING_INTERVAL                0x1A ///< Advertising Interval.
#define BLE_GAP_AD_TYPE_LE_BLUETOOTH_DEVICE_ADDRESS         0x1B ///< LE Bluetooth Device Address.
#define BLE_GAP_AD_TYPE_LE_ROLE                             0x1C ///< LE Role.
#define BLE_GAP_AD_TYPE_SIMPLE_PAIRING_HASH_C256            0x1D ///< Simple Pairing Hash C-256.
#define BLE_GAP_AD_TYPE_SIMPLE_PAIRING_RANDOMIZER_R256      0x1E ///< Simple Pairing Randomizer R-256.
#define BLE_GAP_AD_TYPE_SERVICE_DATA_32BIT_UUID             0x20 ///< Service Data - 32-bit UUID.
#define BLE_GAP_AD_TYPE_SERVICE_DATA_128BIT_UUID            0x21 ///< Service Data - 128-bit UUID.
#define BLE_GAP_AD_TYPE_UNIFORM_RESOUCE_IDENTIFIER          0x24 ///< Uniform Resource Identifier
#define BLE_GAP_AD_TYPE_3D_INFORMATION_DATA                 0x3D ///< 3D Information Data.
#define BLE_GAP_AD_TYPE_MANUFACTURER_SPECIFIC_DATA          0xFF ///< Manufacturer Specific Data.
/**@} */


/**@name GAP Advertisement Flags [Defines]
 * @{ */
#define BLE_GAP_ADV_FLAG_LE_LIMITED_DISC_MODE         (0x01)   ///< LE Limited Discoverable Mode.
#define BLE_GAP_ADV_FLAG_LE_GENERAL_DISC_MODE         (0x02)   ///< LE General Discoverable Mode.
#define BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED         (0x04)   ///< BR/EDR not supported.
#define BLE_GAP_ADV_FLAG_LE_BR_EDR_CONTROLLER         (0x08)   ///< Simultaneous LE and BR/EDR, Controller.
#define BLE_GAP_ADV_FLAG_LE_BR_EDR_HOST               (0x10)   ///< Simultaneous LE and BR/EDR, Host.
#define BLE_GAP_ADV_FLAGS_LE_ONLY_LIMITED_DISC_MODE   (BLE_GAP_ADV_FLAG_LE_LIMITED_DISC_MODE | BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED)   ///< LE Limited Discoverable Mode, BR/EDR not supported.
#define BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE   (BLE_GAP_ADV_FLAG_LE_GENERAL_DISC_MODE | BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED)   ///< LE General Discoverable Mode, BR/EDR not supported.
/**@} */


/*!
    @name GAP Advertisement Interval Constants [Defines]
   @{
*/
#define BLE_ADV_INTERVAL_MIN        0x0020 ///< Minimum Advertising interval in 625 us units, i.e. 20 ms.
#define BLE_ADV_NONCON_INTERVAL_MIN 0x00A0 ///< Minimum Advertising interval in 625 us units for non connectable mode, i.e. 100 ms.
#define BLE_ADV_INTERVAL_MAX        0x4000 ///< Maximum Advertising interval in 625 us units, i.e. 10.24 s.
/**@} */

/*!
    @name GAP Scan Interval Constants [Defines]
   @{
*/
#define BLE_SCAN_INTERVAL_MIN       0x0004 ///< Minimum Scan interval in 625 us units, i.e. 2.5 ms.
#define BLE_SCAN_INTERVAL_MAX       0x4000 ///< Maximum Scan interval in 625 us units, i.e. 10.24 s.
/**@} */


/*!
    @name GAP Scan Window Constants [Defines]
   @{
*/
#define BLE_SCAN_WINDOW_MIN         0x0004 ///< Minimum Scan window in 625 us units, i.e. 2.5 ms.
#define BLE_SCAN_WINDOW_MAX         0x4000 ///< Maximum Scan window in 625 us units, i.e. 10.24 s.
/**@} */


/*!
    @name GAP Scan Timeout Constants [Defines]
   @{
*/
#define BLE_SCAN_TIMEOUT_MIN        0x0001 ///< Minimum Scan timeout in seconds.
#define BLE_SCAN_TIMEOUT_MAX        0xFFFF ///< Maximum Scan timeout in seconds.
/**@} */


/*!
   @name BLE_GAP_ADV_FLAGS GAP Advertisement Flags
   @{
 */
#define BLE_GAP_ADV_FLAG_LE_LIMITED_DISC_MODE         (0x01)   ///< LE Limited Discoverable Mode.
#define BLE_GAP_ADV_FLAG_LE_GENERAL_DISC_MODE         (0x02)   ///< LE General Discoverable Mode.
#define BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED         (0x04)   ///< BR/EDR not supported.
#define BLE_GAP_ADV_FLAG_LE_BR_EDR_CONTROLLER         (0x08)   ///< Simultaneous LE and BR/EDR, Controller.
#define BLE_GAP_ADV_FLAG_LE_BR_EDR_HOST               (0x10)   ///< Simultaneous LE and BR/EDR, Host.
#define BLE_GAP_ADV_FLAGS_LE_ONLY_LIMITED_DISC_MODE   (BLE_GAP_ADV_FLAG_LE_LIMITED_DISC_MODE | BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED)   ///< LE Limited Discoverable Mode, BR/EDR not supported. */
#define BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE   (BLE_GAP_ADV_FLAG_LE_GENERAL_DISC_MODE | BLE_GAP_ADV_FLAG_BR_EDR_NOT_SUPPORTED)   ///< LE General Discoverable Mode, BR/EDR not supported. */
/**@} */


/*!
   @name BLE_GAP_ADV_INTERVALS GAP Advertising interval max and min
   @{
 */
#define BLE_GAP_ADV_INTERVAL_MIN        0x0020 ///< Minimum Advertising interval in 625 us units, i.e. 20 ms.
#define BLE_GAP_ADV_NONCON_INTERVAL_MIN 0x00A0 ///< Minimum Advertising interval in 625 us units for non connectable mode, i.e. 100 ms.
#define BLE_GAP_ADV_INTERVAL_MAX        0x4000 ///< Maximum Advertising interval in 625 us units, i.e. 10.24 s.
 /**@}  */


/*!
   @name BLE_GAP_SCAN_INTERVALS GAP Scan interval max and min
   @{
*/
#define BLE_GAP_SCAN_INTERVAL_MIN       0x0004 ///< Minimum Scan interval in 625 us units, i.e. 2.5 ms.
#define BLE_GAP_SCAN_INTERVAL_MAX       0x4000 ///< Maximum Scan interval in 625 us units, i.e. 10.24 s.
 /** @}  */


/**@name BLE_GAP_SCAN_WINDOW GAP Scan window max and min
 * @{ */
#define BLE_GAP_SCAN_WINDOW_MIN         0x0004 ///< Minimum Scan window in 625 us units, i.e. 2.5 ms.
#define BLE_GAP_SCAN_WINDOW_MAX         0x4000 ///< Maximum Scan window in 625 us units, i.e. 10.24 s.
 /** @}  */


/**@brief Maximum size of advertising data in octets. */
#define  BLE_GAP_ADV_MAX_SIZE           31


/*!
   @name BLE_GAP_ADDR_TYPES GAP Address types
   @{
 */
#define BLE_GAP_ADDR_TYPE_PUBLIC                        0x00 ///< Public address.
#define BLE_GAP_ADDR_TYPE_RANDOM                        0x01 ///< Random address.
/**@} */


/*!
   @name BLE_GAP_ADV_TYPES GAP Advertising types
   @{
 */
#define BLE_GAP_ADV_TYPE_ADV_IND          0x00   ///< Connectable undirected.
#define BLE_GAP_ADV_TYPE_ADV_DIRECT_IND   0x01   ///< Connectable directed.
#define BLE_GAP_ADV_TYPE_ADV_SCAN_IND     0x02   ///< Scannable undirected.
#define BLE_GAP_ADV_TYPE_ADV_NONCONN_IND  0x03   ///< Non connectable undirected.
/**@} */


/*!
   @name BLE_GAP_ADV_CHANNEL_MAP channel map
   @ {
 */
#define BLE_GAP_ADV_CHANNEL_MAP_37        1
#define BLE_GAP_ADV_CHANNEL_MAP_38        2
#define BLE_GAP_ADV_CHANNEL_MAP_39        4
#define BLE_GAP_ADV_CHANNEL_MAP_ALL       7
/**@} */


/*!
  @name BLE_GAP_ADV_FILTER_POLICIES GAP Advertising filter policies
  @{
  */
#define BLE_GAP_ADV_FP_ANY                0x00   ///< Allow scan requests and connect requests from any device.
#define BLE_GAP_ADV_FP_FILTER_SCANREQ     0x01   ///< Filter scan requests with whitelist.
#define BLE_GAP_ADV_FP_FILTER_CONNREQ     0x02   ///< Filter connect requests with whitelist.
#define BLE_GAP_ADV_FP_FILTER_BOTH        0x03   ///< Filter both scan and connect requests with whitelist.
/**@} */

/*!
  @name BLE_CONN_HANDLES BLE Connection Handles
  @{
*/
#define BLE_CONN_HANDLE_INVALID 0xFFFF  ///< Invalid Connection Handle.
#define BLE_CONN_HANDLE_ALL     0xFFFE  ///< Applies to all Connection Handles.
/** @} */


/*! @name BLE_UUID_VALUES Assigned Values for BLE UUIDs
  @{
*/
/* Generic UUIDs, applicable to all services */
#define BLE_UUID_UNKNOWN                              0x0000 ///< Reserved UUID.
#define BLE_UUID_SERVICE_PRIMARY                      0x2800 ///< Primary Service.
#define BLE_UUID_SERVICE_SECONDARY                    0x2801 ///< Secondary Service.
#define BLE_UUID_SERVICE_INCLUDE                      0x2802 ///< Include.
#define BLE_UUID_CHARACTERISTIC                       0x2803 ///< Characteristic.
#define BLE_UUID_DESCRIPTOR_CHAR_EXT_PROP             0x2900 ///< Characteristic Extended Properties Descriptor.
#define BLE_UUID_DESCRIPTOR_CHAR_USER_DESC            0x2901 ///< Characteristic User Description Descriptor.
#define BLE_UUID_DESCRIPTOR_CLIENT_CHAR_CONFIG        0x2902 ///< Client Characteristic Configuration Descriptor.
#define BLE_UUID_DESCRIPTOR_SERVER_CHAR_CONFIG        0x2903 ///< Server Characteristic Configuration Descriptor.
#define BLE_UUID_DESCRIPTOR_CHAR_PRESENTATION_FORMAT  0x2904 ///< Characteristic Presentation Format Descriptor.
#define BLE_UUID_DESCRIPTOR_CHAR_AGGREGATE_FORMAT     0x2905 ///< Characteristic Aggregate Format Descriptor.
/* GATT specific UUIDs */
#define BLE_UUID_GATT                                 0x1801 ///< Generic Attribute Profile.
#define BLE_UUID_GATT_CHARACTERISTIC_SERVICE_CHANGED  0x2A05 ///< Service Changed Characteristic.
/* GAP specific UUIDs */
#define BLE_UUID_GAP                                  0x1800 ///< Generic Access Profile.
#define BLE_UUID_GAP_CHARACTERISTIC_DEVICE_NAME       0x2A00 ///< Device Name Characteristic.
#define BLE_UUID_GAP_CHARACTERISTIC_APPEARANCE        0x2A01 ///< Appearance Characteristic.
#define BLE_UUID_GAP_CHARACTERISTIC_PPF               0x2A02 ///< Peripheral Privacy Flag Characteristic.
#define BLE_UUID_GAP_CHARACTERISTIC_RECONN_ADDR       0x2A03 ///< Reconnection Address Characteristic.
#define BLE_UUID_GAP_CHARACTERISTIC_PPCP              0x2A04 ///< Peripheral Preferred Connection Parameters Characteristic.
/** @} */

/*!
   @name UUID_SERVICES Service UUID definitions
  @{
 */
#define BLE_UUID_ALERT_NOTIFICATION_SERVICE                      0x1811     ///< Alert Notification service UUID.
#define BLE_UUID_BATTERY_SERVICE                                 0x180F     ///< Battery service UUID. */
#define BLE_UUID_BLOOD_PRESSURE_SERVICE                          0x1810     ///< Blood Pressure service UUID. */
#define BLE_UUID_CURRENT_TIME_SERVICE                            0x1805     ///< Current Time service UUID. */
#define BLE_UUID_CYCLING_SPEED_AND_CADENCE                       0x1816     ///< Cycling Speed and Cadence service UUID. */
#define BLE_UUID_LOCATION_AND_NAVIGATION_SERVICE                 0x1819     ///< Location and Navigation service UUID. */
#define BLE_UUID_DEVICE_INFORMATION_SERVICE                      0x180A     ///< Device Information service UUID. */
#define BLE_UUID_GLUCOSE_SERVICE                                 0x1808     ///< Glucose service UUID. */
#define BLE_UUID_HEALTH_THERMOMETER_SERVICE                      0x1809     ///< Health Thermometer service UUID. */
#define BLE_UUID_HEART_RATE_SERVICE                              0x180D     ///< Heart Rate service UUID. */
#define BLE_UUID_HUMAN_INTERFACE_DEVICE_SERVICE                  0x1812     ///< Human Interface Device service UUID. */
#define BLE_UUID_IMMEDIATE_ALERT_SERVICE                         0x1802     ///< Immediate Alert service UUID. */
#define BLE_UUID_LINK_LOSS_SERVICE                               0x1803     ///< Link Loss service UUID. */
#define BLE_UUID_NEXT_DST_CHANGE_SERVICE                         0x1807     ///< Next Dst Change service UUID. */
#define BLE_UUID_PHONE_ALERT_STATUS_SERVICE                      0x180E     ///< Phone Alert Status service UUID. */
#define BLE_UUID_REFERENCE_TIME_UPDATE_SERVICE                   0x1806     ///< Reference Time Update service UUID. */
#define BLE_UUID_RUNNING_SPEED_AND_CADENCE                       0x1814     ///< Running Speed and Cadence service UUID. */
#define BLE_UUID_SCAN_PARAMETERS_SERVICE                         0x1813     ///< Scan Parameters service UUID. */
#define BLE_UUID_TX_POWER_SERVICE                                0x1804     ///< TX Power service UUID. */
#define BLE_UUID_IPSP_SERVICE                                    0x1820     ///< Internet Protocol Support service UUID. */
#define BLE_UUID_BMS_SERVICE                                     0x181E     ///< BOND MANAGEMENT service UUID*/
#define BLE_UUID_CGM_SERVICE                                     0x181F     ///< Contiunous Glucose Monitoring service UUID*/
#define BLE_UUID_PLX_SERVICE                                     0x1822     ///< Pulse Oximeter Service UUID*/


/** @} */

/*!
  @name UUID_CHARACTERISTICS Characteristic UUID definitions
  @{
 */
#define BLE_UUID_REMOVABLE_CHAR                                  0x2A3A     ///< Removable characteristic UUID. */
#define BLE_UUID_SERVICE_REQUIRED_CHAR                           0x2A3B     ///< Service Required characteristic UUID. */
#define BLE_UUID_ALERT_CATEGORY_ID_CHAR                          0x2A43     ///< Alert Category Id characteristic UUID. */
#define BLE_UUID_ALERT_CATEGORY_ID_BIT_MASK_CHAR                 0x2A42     ///< Alert Category Id Bit Mask characteristic UUID. */
#define BLE_UUID_ALERT_LEVEL_CHAR                                0x2A06     ///< Alert Level characteristic UUID. */
#define BLE_UUID_ALERT_NOTIFICATION_CONTROL_POINT_CHAR           0x2A44     ///< Alert Notification Control Point characteristic UUID. */
#define BLE_UUID_ALERT_STATUS_CHAR                               0x2A3F     ///< Alert Status characteristic UUID. */
#define BLE_UUID_BATTERY_LEVEL_CHAR                              0x2A19     ///< Battery Level characteristic UUID. */
#define BLE_UUID_BLOOD_PRESSURE_FEATURE_CHAR                     0x2A49     ///< Blood Pressure Feature characteristic UUID. */
#define BLE_UUID_BLOOD_PRESSURE_MEASUREMENT_CHAR                 0x2A35     ///< Blood Pressure Measurement characteristic UUID. */
#define BLE_UUID_BODY_SENSOR_LOCATION_CHAR                       0x2A38     ///< Body Sensor Location characteristic UUID. */
#define BLE_UUID_BOOT_KEYBOARD_INPUT_REPORT_CHAR                 0x2A22     ///< Boot Keyboard Input Report characteristic UUID. */
#define BLE_UUID_BOOT_KEYBOARD_OUTPUT_REPORT_CHAR                0x2A32     ///< Boot Keyboard Output Report characteristic UUID. */
#define BLE_UUID_BOOT_MOUSE_INPUT_REPORT_CHAR                    0x2A33     ///< Boot Mouse Input Report characteristic UUID. */
#define BLE_UUID_CURRENT_TIME_CHAR                               0x2A2B     ///< Current Time characteristic UUID. */
#define BLE_UUID_DATE_TIME_CHAR                                  0x2A08     ///< Date Time characteristic UUID. */
#define BLE_UUID_DAY_DATE_TIME_CHAR                              0x2A0A     ///< Day Date Time characteristic UUID. */
#define BLE_UUID_DAY_OF_WEEK_CHAR                                0x2A09     ///< Day Of Week characteristic UUID. */
#define BLE_UUID_DST_OFFSET_CHAR                                 0x2A0D     ///< Dst Offset characteristic UUID. */
#define BLE_UUID_EXACT_TIME_256_CHAR                             0x2A0C     ///< Exact Time 256 characteristic UUID. */
#define BLE_UUID_FIRMWARE_REVISION_STRING_CHAR                   0x2A26     ///< Firmware Revision String characteristic UUID. */
#define BLE_UUID_GLUCOSE_FEATURE_CHAR                            0x2A51     ///< Glucose Feature characteristic UUID. */
#define BLE_UUID_GLUCOSE_MEASUREMENT_CHAR                        0x2A18     ///< Glucose Measurement characteristic UUID. */
#define BLE_UUID_GLUCOSE_MEASUREMENT_CONTEXT_CHAR                0x2A34     ///< Glucose Measurement Context characteristic UUID. */
#define BLE_UUID_HARDWARE_REVISION_STRING_CHAR                   0x2A27     ///< Hardware Revision String characteristic UUID. */
#define BLE_UUID_HEART_RATE_CONTROL_POINT_CHAR                   0x2A39     ///< Heart Rate Control Point characteristic UUID. */
#define BLE_UUID_HEART_RATE_MEASUREMENT_CHAR                     0x2A37     ///< Heart Rate Measurement characteristic UUID. */
#define BLE_UUID_HID_CONTROL_POINT_CHAR                          0x2A4C     ///< Hid Control Point characteristic UUID. */
#define BLE_UUID_HID_INFORMATION_CHAR                            0x2A4A     ///< Hid Information characteristic UUID. */
#define BLE_UUID_IEEE_REGULATORY_CERTIFICATION_DATA_LIST_CHAR    0x2A2A     ///< IEEE Regulatory Certification Data List characteristic UUID. */
#define BLE_UUID_INTERMEDIATE_CUFF_PRESSURE_CHAR                 0x2A36     ///< Intermediate Cuff Pressure characteristic UUID. */
#define BLE_UUID_INTERMEDIATE_TEMPERATURE_CHAR                   0x2A1E     ///< Intermediate Temperature characteristic UUID. */
#define BLE_UUID_LOCAL_TIME_INFORMATION_CHAR                     0x2A0F     ///< Local Time Information characteristic UUID. */
#define BLE_UUID_MANUFACTURER_NAME_STRING_CHAR                   0x2A29     ///< Manufacturer Name String characteristic UUID. */
#define BLE_UUID_MEASUREMENT_INTERVAL_CHAR                       0x2A21     ///< Measurement Interval characteristic UUID. */
#define BLE_UUID_MODEL_NUMBER_STRING_CHAR                        0x2A24     ///< Model Number String characteristic UUID. */
#define BLE_UUID_UNREAD_ALERT_CHAR                               0x2A45     ///< Unread Alert characteristic UUID. */
#define BLE_UUID_NEW_ALERT_CHAR                                  0x2A46     ///< New Alert characteristic UUID. */
#define BLE_UUID_PNP_ID_CHAR                                     0x2A50     ///< PNP Id characteristic UUID. */
#define BLE_UUID_PROTOCOL_MODE_CHAR                              0x2A4E     ///< Protocol Mode characteristic UUID. */
#define BLE_UUID_RECORD_ACCESS_CONTROL_POINT_CHAR                0x2A52     ///< Record Access Control Point characteristic UUID. */
#define BLE_UUID_REFERENCE_TIME_INFORMATION_CHAR                 0x2A14     ///< Reference Time Information characteristic UUID. */
#define BLE_UUID_REPORT_CHAR                                     0x2A4D     ///< Report characteristic UUID. */
#define BLE_UUID_REPORT_MAP_CHAR                                 0x2A4B     ///< Report Map characteristic UUID. */
#define BLE_UUID_RINGER_CONTROL_POINT_CHAR                       0x2A40     ///< Ringer Control Point characteristic UUID. */
#define BLE_UUID_RINGER_SETTING_CHAR                             0x2A41     ///< Ringer Setting characteristic UUID. */
#define BLE_UUID_SCAN_INTERVAL_WINDOW_CHAR                       0x2A4F     ///< Scan Interval Window characteristic UUID. */
#define BLE_UUID_SCAN_REFRESH_CHAR                               0x2A31     ///< Scan Refresh characteristic UUID. */
#define BLE_UUID_SERIAL_NUMBER_STRING_CHAR                       0x2A25     ///< Serial Number String characteristic UUID. */
#define BLE_UUID_SOFTWARE_REVISION_STRING_CHAR                   0x2A28     ///< Software Revision String characteristic UUID. */
#define BLE_UUID_SUPPORTED_NEW_ALERT_CATEGORY_CHAR               0x2A47     ///< Supported New Alert Category characteristic UUID. */
#define BLE_UUID_SUPPORTED_UNREAD_ALERT_CATEGORY_CHAR            0x2A48     ///< Supported Unread Alert Category characteristic UUID. */
#define BLE_UUID_SYSTEM_ID_CHAR                                  0x2A23     ///< System Id characteristic UUID. */
#define BLE_UUID_TEMPERATURE_MEASUREMENT_CHAR                    0x2A1C     ///< Temperature Measurement characteristic UUID. */
#define BLE_UUID_TEMPERATURE_TYPE_CHAR                           0x2A1D     ///< Temperature Type characteristic UUID. */
#define BLE_UUID_TIME_ACCURACY_CHAR                              0x2A12     ///< Time Accuracy characteristic UUID. */
#define BLE_UUID_TIME_SOURCE_CHAR                                0x2A13     ///< Time Source characteristic UUID. */
#define BLE_UUID_TIME_UPDATE_CONTROL_POINT_CHAR                  0x2A16     ///< Time Update Control Point characteristic UUID. */
#define BLE_UUID_TIME_UPDATE_STATE_CHAR                          0x2A17     ///< Time Update State characteristic UUID. */
#define BLE_UUID_TIME_WITH_DST_CHAR                              0x2A11     ///< Time With Dst characteristic UUID. */
#define BLE_UUID_TIME_ZONE_CHAR                                  0x2A0E     ///< Time Zone characteristic UUID. */
#define BLE_UUID_TX_POWER_LEVEL_CHAR                             0x2A07     ///< TX Power Level characteristic UUID. */
#define BLE_UUID_CSC_FEATURE_CHAR                                0x2A5C     ///< Cycling Speed and Cadence Feature characteristic UUID. */
#define BLE_UUID_CSC_MEASUREMENT_CHAR                            0x2A5B     ///< Cycling Speed and Cadence Measurement characteristic UUID. */
#define BLE_UUID_RSC_FEATURE_CHAR                                0x2A54     ///< Running Speed and Cadence Feature characteristic UUID. */
#define BLE_UUID_SC_CTRLPT_CHAR                                  0x2A55     ///< Speed and Cadence Control Point UUID. */
#define BLE_UUID_RSC_MEASUREMENT_CHAR                            0x2A53     ///< Running Speed and Cadence Measurement characteristic UUID. */
#define BLE_UUID_SENSOR_LOCATION_CHAR                            0x2A5D     ///< Sensor Location characteristic UUID. */
#define BLE_UUID_EXTERNAL_REPORT_REF_DESCR                       0x2907     ///< External Report Reference descriptor UUID. */
#define BLE_UUID_REPORT_REF_DESCR                                0x2908     ///< Report Reference descriptor UUID. */
#define BLE_UUID_LN_FEATURE_CHAR                                 0x2A6A     ///< Location Navigation Service, Feature characteristic UUID. */
#define BLE_UUID_LN_POSITION_QUALITY_CHAR                        0x2A69     ///< Location Navigation Service, Position quality UUID. */
#define BLE_UUID_LN_LOCATION_AND_SPEED_CHAR                      0x2A67     ///< Location Navigation Service, Location and Speed characteristic UUID. */
#define BLE_UUID_LN_NAVIGATION_CHAR                              0x2A68     ///< Location Navigation Service, Navigation characteristic UUID. */
#define BLE_UUID_LN_CONTROL_POINT_CHAR                           0x2A6B     ///< Location Navigation Service, Control point characteristic UUID. */
#define BLE_UUID_BMS_CTRLPT                                      0x2AA4     ///< BMS Control Point characteristic UUID. */
#define BLE_UUID_BMS_FEATURE                                     0x2AA5     ///< BMS Feature characteristic UUID. */
#define BLE_UUID_CGM_MEASUREMENT                                 0x2AA7     ///< CGM Service, Measurement characteristic UUID*/
#define BLE_UUID_CGM_FEATURE                                     0x2AA8     ///< CGM Service, Feature characteristic UUID*/
#define BLE_UUID_CGM_STATUS                                      0x2AA9     ///< CGM Service, Status characteristic UUID*/
#define BLE_UUID_CGM_SESSION_START_TIME                          0x2AAA     ///< CGM Service, session start time characteristic UUID*/
#define BLE_UUID_CGM_SESSION_RUN_TIME                            0x2AAB     ///< CGM Service, session run time characteristic UUID*/
#define BLE_UUID_CGM_SPECIFIC_OPS_CTRLPT                         0x2AAC     ///< CGM Service, specific ops ctrlpt characteristic UUID*/
#define BLE_UUID_PLX_SPOT_CHECK_MEAS                             0x2A5E     ///< PLX Service, spot check measurement characteristic UUID*/
#define BLE_UUID_PLX_CONTINUOUS_MEAS                             0x2A5F     ///< PLX Service, continuous measurement characteristic UUID*/
#define BLE_UUID_PLX_FEATURES                                    0x2A60     ///< PLX Service, feature characteristic UUID*/


/*!
 @name BLE_APPEARANCES Bluetooth Appearance values
 @note Retrieved from http://developer.bluetooth.org/gatt/characteristics/Pages/CharacteristicViewer.aspx?u=org.bluetooth.characteristic.gap.appearance.xml
 @{
*/
#define BLE_APPEARANCE_UNKNOWN                                0 ///< Unknown. */
#define BLE_APPEARANCE_GENERIC_PHONE                         64 ///< Generic Phone. */
#define BLE_APPEARANCE_GENERIC_COMPUTER                     128 ///< Generic Computer. */
#define BLE_APPEARANCE_GENERIC_WATCH                        192 ///< Generic Watch. */
#define BLE_APPEARANCE_WATCH_SPORTS_WATCH                   193 ///< Watch: Sports Watch. */
#define BLE_APPEARANCE_GENERIC_CLOCK                        256 ///< Generic Clock. */
#define BLE_APPEARANCE_GENERIC_DISPLAY                      320 ///< Generic Display. */
#define BLE_APPEARANCE_GENERIC_REMOTE_CONTROL               384 ///< Generic Remote Control. */
#define BLE_APPEARANCE_GENERIC_EYE_GLASSES                  448 ///< Generic Eye-glasses. */
#define BLE_APPEARANCE_GENERIC_TAG                          512 ///< Generic Tag. */
#define BLE_APPEARANCE_GENERIC_KEYRING                      576 ///< Generic Keyring. */
#define BLE_APPEARANCE_GENERIC_MEDIA_PLAYER                 640 ///< Generic Media Player. */
#define BLE_APPEARANCE_GENERIC_BARCODE_SCANNER              704 ///< Generic Barcode Scanner. */
#define BLE_APPEARANCE_GENERIC_THERMOMETER                  768 ///< Generic Thermometer. */
#define BLE_APPEARANCE_THERMOMETER_EAR                      769 ///< Thermometer: Ear. */
#define BLE_APPEARANCE_GENERIC_HEART_RATE_SENSOR            832 ///< Generic Heart rate Sensor. */
#define BLE_APPEARANCE_HEART_RATE_SENSOR_HEART_RATE_BELT    833 ///< Heart Rate Sensor: Heart Rate Belt. */
#define BLE_APPEARANCE_GENERIC_BLOOD_PRESSURE               896 ///< Generic Blood Pressure. */
#define BLE_APPEARANCE_BLOOD_PRESSURE_ARM                   897 ///< Blood Pressure: Arm. */
#define BLE_APPEARANCE_BLOOD_PRESSURE_WRIST                 898 ///< Blood Pressure: Wrist. */
#define BLE_APPEARANCE_GENERIC_HID                          960 ///< Human Interface Device (HID). */
#define BLE_APPEARANCE_HID_KEYBOARD                         961 ///< Keyboard (HID Subtype). */
#define BLE_APPEARANCE_HID_MOUSE                            962 ///< Mouse (HID Subtype). */
#define BLE_APPEARANCE_HID_JOYSTICK                         963 ///< Joystiq (HID Subtype). */
#define BLE_APPEARANCE_HID_GAMEPAD                          964 ///< Gamepad (HID Subtype). */
#define BLE_APPEARANCE_HID_DIGITIZERSUBTYPE                 965 ///< Digitizer Tablet (HID Subtype). */
#define BLE_APPEARANCE_HID_CARD_READER                      966 ///< Card Reader (HID Subtype). */
#define BLE_APPEARANCE_HID_DIGITAL_PEN                      967 ///< Digital Pen (HID Subtype). */
#define BLE_APPEARANCE_HID_BARCODE                          968 ///< Barcode Scanner (HID Subtype). */
#define BLE_APPEARANCE_GENERIC_GLUCOSE_METER               1024 ///< Generic Glucose Meter. */
#define BLE_APPEARANCE_GENERIC_RUNNING_WALKING_SENSOR      1088 ///< Generic Running Walking Sensor. */
#define BLE_APPEARANCE_RUNNING_WALKING_SENSOR_IN_SHOE      1089 ///< Running Walking Sensor: In-Shoe. */
#define BLE_APPEARANCE_RUNNING_WALKING_SENSOR_ON_SHOE      1090 ///< Running Walking Sensor: On-Shoe. */
#define BLE_APPEARANCE_RUNNING_WALKING_SENSOR_ON_HIP       1091 ///< Running Walking Sensor: On-Hip. */
#define BLE_APPEARANCE_GENERIC_CYCLING                     1152 ///< Generic Cycling. */
#define BLE_APPEARANCE_CYCLING_CYCLING_COMPUTER            1153 ///< Cycling: Cycling Computer. */
#define BLE_APPEARANCE_CYCLING_SPEED_SENSOR                1154 ///< Cycling: Speed Sensor. */
#define BLE_APPEARANCE_CYCLING_CADENCE_SENSOR              1155 ///< Cycling: Cadence Sensor. */
#define BLE_APPEARANCE_CYCLING_POWER_SENSOR                1156 ///< Cycling: Power Sensor. */
#define BLE_APPEARANCE_CYCLING_SPEED_CADENCE_SENSOR        1157 ///< Cycling: Speed and Cadence Sensor. */
#define BLE_APPEARANCE_GENERIC_PULSE_OXIMETER              3136 ///< Generic Pulse Oximeter. */
#define BLE_APPEARANCE_PULSE_OXIMETER_FINGERTIP            3137 ///< Fingertip (Pulse Oximeter subtype). */
#define BLE_APPEARANCE_PULSE_OXIMETER_WRIST_WORN           3138 ///< Wrist Worn(Pulse Oximeter subtype). */
#define BLE_APPEARANCE_GENERIC_WEIGHT_SCALE                3200 ///< Generic Weight Scale. */
#define BLE_APPEARANCE_GENERIC_OUTDOOR_SPORTS_ACT          5184 ///< Generic Outdoor Sports Activity. */
#define BLE_APPEARANCE_OUTDOOR_SPORTS_ACT_LOC_DISP         5185 ///< Location Display Device (Outdoor Sports Activity subtype). */
#define BLE_APPEARANCE_OUTDOOR_SPORTS_ACT_LOC_AND_NAV_DISP 5186 ///< Location and Navigation Display Device (Outdoor Sports Activity subtype). */
#define BLE_APPEARANCE_OUTDOOR_SPORTS_ACT_LOC_POD          5187 ///< Location Pod (Outdoor Sports Activity subtype). */
#define BLE_APPEARANCE_OUTDOOR_SPORTS_ACT_LOC_AND_NAV_POD  5188 ///< Location and Navigation Pod (Outdoor Sports Activity subtype). */
/** @} */

#define HIGH_BYTE(x) ((uint8_t)(((x)&0xFF00)>>8))
#define LOW_BYTE(x)  ((uint8_t)((x)&0x00FF))


/*************************************************************************
* Type Define
*************************************************************************/
/*!
    @brief Callback prototype for GAP operations.
    @param issuccess Executing is successful or not.
    @param err_code Reason for not successful.
*/
typedef void (*ai_cfm_gap_general)(bool isuccess, uint8_t err_code);

#ifdef _MSC_VER
__pragma(pack(push, 1))
#define __attribute__(x)
#endif


/*!
    @brief BLE ddress Type
*/

typedef enum
{
    ble_addr_type_public = 0,               ///< public address
    ble_addr_type_random_static = 1,        ///< random static address
    ble_addr_type_random_resolvable = 2,    ///< random resolvable addresss
    ble_addr_type_random_non_resolvable = 3, ///< random non resolvable address
}__attribute__((packed)) ble_addr_type;

/*!
    @brief BLE address structure
*/
typedef struct
{
    ble_addr_type addr_type;            ///< address type.
    uint8_t addr[BLE_ADDR_LEN];         ///< address byte array.
} __attribute__((packed)) ble_addr_t;

/*!
    @brief BLE AD Type
    The AD type was mapping to advertising PDU ID.
*/
typedef enum
{
    ble_ad_type_ind = 0x00,             ///< Type for ADV_IND PDU
    ble_ad_type_direct_ind = 0x01,      ///< Type for ADV_DIRECT_IND PDU
    ble_ad_type_scan_ind    = 0x02,     ///< Type for ADV_SCAN_IND PDU
    ble_ad_type_nonconn_ind  = 0x03,    ///< Type for ADV_NONCONN_IND PDU
    ble_ad_type_direct_ind_low = 0x04,  ///< Type for ADV_DIRECT_IND PDU with low duty.
}__attribute__((packed)) ble_ad_type;

/*!
    @brief BLE Scan Type
    Scan type which used in structure ble_gap_scan_params_t.
*/
typedef enum
{
   ble_scan_type_passive = 0x00,    ///< Pasive scan method.
   ble_scan_type_active = 0x01      ///< Active scan method.
}__attribute__((packed))ble_scan_type;

/*!
    @brief BLE Report Type
    The report type is for the scanned peers' type. It could be AD type of passive scan or active scan(SCAN_RSP).
    It was used in structure ble_gap_evt_adv_report_t.
*/
typedef enum
{
    ble_report_type_ind = 0x00,                 ///< Type for ADV_IND found (passive)
    ble_report_type_direct_ind = 0x01,          ///< Type for ADV_DIRECT_IND found (passive)
    ble_report_type_scan_ind    = 0x02,         ///< Type for ADV_SCAN_IND found (passive)
    ble_report_type_nonconn_ind  = 0x03,        ///< Type for ADV_NONCONN_IND found (passive)
    ble_report_type_scan_rsp = 0x04             ///< Type for SCAN_RSP found (active)
}__attribute__((packed)) ble_report_type;

/*!
    @brief BLE Advertising Filter Policy.
    It was used in struct ble_gap_adv_params to indicate policy of filtering peers while advertising.
*/
typedef enum
{
    ble_filter_any = 0x00,              ///< Process scan and connection requests from all devices (i.e., the White Listis not in use).
    ble_filter_filter_scan = 0x01,      ///< Process connection requests from all devices and only scan requests from devices that are in the White List.
    ble_filter_filter_conn = 0x02,      ///< Process scan requests from all devices and only connection requests from devices that are in the White List.
    ble_filter_filter_both = 0x03       ///< Process scan and connection requests only from devices in the White List.
}__attribute__((packed)) ble_filter_policy_t;

/*!
    @brief BLE Scan Fileter Policy
*/
typedef enum
{
    ble_scan_policy_0 = 0x00,       ///<Accept all
                                    ///< - advertisement packets except directed advertising packets not addressed to this device
    ble_scan_policy_1 = 0x01,       ///<Accept only
                                    ///< - advertisement packets from devices where the advertiser' s address is in the White list.
                                    ///< - advertisement packets from devices where the advertiser' s address is in the White list.
    ble_scan_policy_2 = 0x02,       ///<Accept all
                                    ///< - undirected advertisement packets, and
                                    ///< - directed advertising packets where the initiator address is a
                                    ///< - resolvable private address, and
                                    ///< - directed advertising packets addressed to this device.
    ble_scan_policy_3 = 0x03        ///<Accept all
                                    ///< - advertisement packets from devices where the
                                    ///< - advertiser��s address is in the White list, and
                                    ///< - directed advertising packets where the initiator address is a
                                    ///< - resolvable private address, and
                                    ///< - directed advertising packets addressed to this device.
}__attribute__((packed))ble_scan_policy_t;

/*!
    @brief BLE while listing.
*/
typedef struct
{
  uint8_t           addr_count;    ///< device count
  ble_addr_t       *p_addrs;       ///< device address's array. Its size is equal to addr_count.
} ble_gap_whitelist_t;

/*!
    @brief BLE advertisement parameter.
*/
typedef struct
{
  ble_ad_type           ad_type;
  ble_addr_t            *peer_addr;
  ble_addr_type         self_addr_type;
  ble_filter_policy_t   filter;
  uint16_t              min_interval;
  uint16_t              max_interval;
  uint8_t               channel_mask;
}__attribute__((packed)) ble_gap_adv_params;

/*!
    @brief Parameter for scanning.
*/
typedef struct
{
  ble_scan_type           type;
  uint16_t                interval;             ///< Scan interval between 0x0004 and 0x4000 in 0.625ms units (2.5ms to 10.24s).
  uint16_t                window;               ///< Scan window between 0x0004 and 0x4000 in 0.625ms units (2.5ms to 10.24s).
  ble_addr_type           owner;                /**! Owner address type */
  ble_scan_policy_t       policy;
  ble_gap_whitelist_t *   p_whitelist;          ///< Pointer to whitelist, NULL if no whitelist or the current active whitelist is to be used.
  bool                    filter_duplicated;     ///< Filter duplicated device
} __attribute__((packed)) ble_gap_scan_params_t;


/*!
    @brief parameters for creating a link
*/
typedef struct
{
  uint16_t               scan_intvl;          ///< Scan interval between 0x0004 and 0x4000 in 0.625ms units (2.5ms to 10.24s).
  uint16_t               scan_window;         ///< Scan window between 0x0004 and 0x4000 in 0.625ms units (2.5ms to 10.24s).
  ble_scan_policy_t      policy;
  ble_addr_t             peer;                /**! peer address  */
  ble_addr_type          owner;               /**! owner address */
  uint16_t               min_conn_interval;   ///< Minimum Connection Interval in 1.25 ms units,
  uint16_t               max_conn_interval;   ///< Maximum Connection Interval in 1.25 ms units,
  uint16_t               slave_latency;       ///< Slave Latency in number of connection events
  uint16_t               conn_sup_timeout;    ///< Connection Supervision Timeout in 10 ms units.
  uint16_t               ce_min;              ///< Minimal CE
  uint16_t               ce_max;              ///< Maximal CE
} __attribute__((packed)) ble_gap_create_conn_params_t;

/*!
    @brief parameters for a link
    It is usually used for updating parameters of a connection.
*/
typedef struct
{
  uint16_t min_conn_interval;         ///< Minimum Connection Interval in 1.25 ms units
  uint16_t max_conn_interval;         ///< Maximum Connection Interval in 1.25 ms units
  uint16_t slave_latency;             ///< Slave Latency in number of connection events
  uint16_t conn_sup_timeout;          ///< Connection Supervision Timeout in 10 ms units
  uint16_t ce_min;                    ///< Minimal CE
  uint16_t ce_max;                    ///< Maximal CE
} __attribute__((packed)) ble_gap_conn_params_t;


/**@brief GAP Master Identification. */
typedef struct
{
  uint8_t   rand[BLE_GAP_SEC_RAND_LEN]; ///< Random Number.
  uint16_t  ediv;                       ///< Encrypted Diversifier.
  uint8_t   ltk[BLE_GAP_SEC_KEY_LEN];   ///< Long Term Key.
} __attribute__((packed)) ble_gap_master_id_t;


/**@brief Event structure for @ref BLE_GAP_EVT_CONNECTED. */
typedef struct
{
  uint8_t status;                /**! 0: success*/
  uint16_t conn_handle;                                     ///< Connection Handle
  uint8_t role;
  ble_addr_t peer_addr;              ///< Bluetooth address of the peer device.
  uint16_t connInterval;
  uint16_t connLatency;
  uint16_t supervisionTimeout;
  uint8_t masterClockAccuracy;
} __attribute__((packed)) ble_gap_evt_connected_t;


/**@brief Event structure for @ref BLE_GAP_EVT_DISCONNECTED. */
typedef struct
{
  uint16_t conn_handle;                                     ///< Connection Handle
  uint8_t reason;                               ///< HCI error code.
} __attribute__((packed)) ble_gap_evt_disconnected_t;


/**@brief Event structure for @ref BLE_GAP_EVT_CONNECT_PARM_UPDATE. */
typedef struct
{
    uint8_t status;                 ///< 0: success else fail
    uint16_t conn_handle;           ///< Connection Handle
    uint16_t conn_interval;         ///< Connection Interval in 1.25 ms units,
    uint16_t slave_latency;         ///< Slave Latency in number of connection events
    uint16_t conn_sup_timeout;      ///< Connection Supervision Timeout in 10 ms units.
}  __attribute__((packed)) ble_gap_evt_conn_param_update_t;


/**@brief Event structure for @ref BLE_GAP_EVT_ADV_REPORT. */
typedef struct
{
  ble_addr_t        peer_addr;
  int8_t            rssi;
  ble_report_type   type;
  uint8_t           dlen;
  uint8_t           data[31];
}  __attribute__((packed))  ble_gap_evt_adv_report_t;


/**@brief Event structure for @ref BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST. */
typedef struct
{
    uint16_t handle;                    ///< connection handler
    uint16_t identifier;                ///< identifier used to reponse
    uint16_t min_conn_interval;         ///< Minimum Connection Interval in 1.25 ms units
    uint16_t max_conn_interval;         ///< Maximum Connection Interval in 1.25 ms units
    uint16_t slave_latency;             ///< Slave Latency in number of connection events
    uint16_t conn_sup_timeout;          ///< Connection Supervision Timeout in 10 ms units
}__attribute__((packed)) ble_gap_evt_conn_param_update_request_t;

/**@brief Event structure for @ref BLE_GAP_EVT_DISCONNECT_FAIL, @ref BLE_GAP_EVT_CONNECT_FAIL,
@ref BLE_GAP_EVT_START_ENCRYPT_FAIL and @ref BLE_GAP_EVT_CONN_PARM_UPDATE_FAIL
*/
typedef struct
{
    uint8_t err_code; ///< Error code. Usually is HCI error code
}__attribute__((packed)) ble_gap_evt_operation_fail_t;

/*!
    @brief Event structure for @ref BLE_GAP_EVT_READ_REMOTE_VERSION
*/
typedef struct
{
    uint8_t err_code; ///< HCI error code.
    uint16_t handle;  ///< Connection handle.
    uint8_t version;  ///< Version of current LMP.
    uint16_t manu;     ///< Manufacturer name.
    uint16_t sub;       ///< Subversion.
}__attribute__((packed))ble_gap_evt_remote_version_t;

/*!
    @brief GAP event structure.
*/
typedef struct
{
  union                                                     ///< union alternative identified by evt_id in enclosing struct.
  {
    ble_gap_evt_connected_t                   connected;                    ///< Connected Event Parameters.
    ble_gap_evt_disconnected_t                disconnected;                 ///< Disconnected Event Parameters.
    ble_gap_evt_conn_param_update_t           conn_param_update;            ///< Connection Parameter Update Parameters.
    ble_gap_evt_adv_report_t                  adv_report;                   ///< Advertising Report Event Parameters.
    ble_gap_evt_conn_param_update_request_t   conn_param_update_request;    ///< Connection Parameter Update Parameters.
    ble_gap_evt_operation_fail_t              operation_fail;                ///< Operation fail
    ble_gap_evt_remote_version_t              remote_version;               ///< Remote Version
  } __attribute__((packed)) params;                                                                 ///< Event Parameters.
}  __attribute__((packed)) ble_gap_evt_t;

#ifdef _MSC_VER
__pragma(pack(pop))
#undef __attribute__
#endif

/*!
    @brief GAP Event IDs.
    IDs that uniquely identify an event.
 */
typedef enum
{
    BLE_GAP_EVT_CONNECTED = BT_EVENT_GAP,   ///< Event for link connected.
    BLE_GAP_EVT_DISCONNECTED,               ///< Event for link disconnected.
    BLE_GAP_EVT_CONNECT_PARM_UPDATE,        ///< Event for notifying connection parameter has been updated.
    BLE_GAP_EVT_ADV_REPORT,                 ///< Event for scanning result.
    BLE_GAP_EVT_CONN_PARAM_UPDATE_REQUEST,  ///< Event for notifying connection parameter update request from peer.
    BLE_GAP_EVT_DISCONNECT_FAIL,            ///< Event for ble_gap_disconnect operation fail
    BLE_GAP_EVT_CONNECT_FAIL,                ///< Event for ble_gap_connect operation fail
    BLE_GAP_EVT_START_ENCRYPT_FAIL,          ///< Event for ble_gap_start_encrypt operation fail
    BLE_GAP_EVT_CONN_PARM_UPDATE_FAIL,        ///< Event for ble_gap_conn_param_update operation fail
    BLE_GAP_EVT_READ_REMOTE_VERSION           ///< Event for ble_gap_remote_version result.
}ble_gap_event_id;


/*************************************************************************
* API
*************************************************************************/

/*!
    @brief Set Advertisement Data API
    @param p_data Advertisment data array. Maximal length is 31.
    @param dlen Advertissment data array length.
    @param cb Callback which would be called after opertaion complete.
*/
BT_STATUS ble_gap_adv_data_set (uint8_t* p_data, uint8_t dlen, ai_cfm_gap_general cb);

/*!
    @brief Set Scan Response Data
    @param p_data Advertisment data array. Maximal length is 31.
    @param dlen Advertissment data array length.
    @param cb Callback which would be called after opertaion complete.
*/
BT_STATUS ble_gap_scan_data_set (uint8_t* p_data, uint8_t dlen, ai_cfm_gap_general cb);


/*!
    @brief Set Advertisement Parameter
    @param parm Advertisement parameters
    @param cb Callback which would be called after opertaion complete.
    This API is used to set advertisement parameter prior enabling advertisement by invoking ble_gap_adv_start(NULL, ...).
    @note The paramter setting will be reset after power off or deep sleep.
*/
BT_STATUS ble_gap_adv_set_parameter(ble_gap_adv_params *parm, ai_cfm_gap_general cb);

/*!
    @brief Start Advertisement
    @param parm Advertisement parameters
    @param cb Callback which would be called after opertaion complete.
    If parm is NULL, the function will use parameter which was set last time.
    @note The paramter setting will be reset after power off or deep sleep.
*/
BT_STATUS ble_gap_adv_start(ble_gap_adv_params *parm, ai_cfm_gap_general cb);

/*!
    @brief Stop Advertisement
    @param cb Callback which would be called after opertaion complete.
*/
BT_STATUS ble_gap_adv_stop(ai_cfm_gap_general cb);

/*!
    @brief Set BLE address
    @param addr Address
    @param cb Callback which would be called after opertaion complete.
*/
BT_STATUS ble_gap_address_set(ble_addr_t *addr, ai_cfm_gap_general cb);

/*!
    @brief Get Public BLE address
    @param addr Address
*/
BT_STATUS ble_gap_pub_address_get(ble_addr_t *addr);

/*!
    @brief Get static random BLE address
    @param addr Address
*/
BT_STATUS ble_gap_random_address_get(ble_addr_t *addr);

/*!
    @brief Disconnect link
    @param handle Connection handle
    @param reason Reason for disconnect
*/
BT_STATUS ble_gap_disconnect(uint16_t handle, uint8_t reason);

/*!
    @brief Set TX power
    @param tx_power Power in DB unit.
    @param cb Callback which would be called after opertaion complete.
*/
BT_STATUS ble_gap_tx_power_set(int8_t tx_power, ai_cfm_gap_general cb);


/*!
    @brief Set Scan parameter
    @param p_scan_params Scan parameter
    @param cb Callback which would be called after opertaion complete.
    This API is used to set scan parameter prior start scanning by  by invoking ble_gap_scan_start(NULL, ...).
    @note The paramter setting will be reset after power off or deep sleep.
*/
BT_STATUS ble_gap_scan_set_parameter(ble_gap_scan_params_t *p_scan_params, ai_cfm_gap_general cb);

/*!
    @brief Start scan
    @param p_scan_params Scan parameter
    @param cb Callback which would be called after opertaion complete.
    If parm is NULL, the function will use parameter which was set last time.
    @note The paramter setting will be reset after power off or deep sleep.
*/
BT_STATUS ble_gap_scan_start(ble_gap_scan_params_t const * const p_scan_params, ai_cfm_gap_general cb);

/*!
    @brief Stop scan
    @param cb Callback which would be called after opertaion complete.
*/
BT_STATUS ble_gap_scan_stop(ai_cfm_gap_general cb);

/*!
   @brief Start link encrypt
   @param conn_handle Connection handle
   @param p_master_id LTK, EVID and random number.
*/
BT_STATUS ble_gap_start_encrypt(uint16_t conn_handle, ble_gap_master_id_t const * p_master_id);

/*!
    @brief Connect update request
    @param handle Connection handle
    @param p_conn_params Connection update parameters
*/
BT_STATUS ble_gap_conn_param_update(uint16_t handle, ble_gap_conn_params_t const * const p_conn_params);

/*!
    @brief Connect request
    @param p_conn_params Connection request parameters
*/
BT_STATUS ble_gap_connect(ble_gap_create_conn_params_t* p_conn_params);

/*!
    @brief Cancel ongoing connection request
    @param cb Callback which would be called after opertaion complete.
*/
BT_STATUS ble_gap_connect_cancel(ai_cfm_gap_general cb);

/*!
    @brief Add whiteList
    @param p_wlst whitelist table
    @param cb Callback which would be called after opertaion complete.
*/
BT_STATUS ble_gap_add_whitelist(ble_gap_whitelist_t* p_wlst, ai_cfm_gap_general cb);


/*!
    @brief Obtain remote version information
    @param handle conneciton handle
*/
BT_STATUS ble_gap_remote_version(uint16_t handle);


/*!
    @brief Disable slave latency
    @param byDisable is true to disable slave latency
*/
void ble_gap_disable_latency(uint8_t byDisable);

/*!
    @brief Get connection RSSI
    @param handle conneciton handle
    @param cb Callback which would be called after opertaion complete.
*/
BT_STATUS ble_gap_get_rssi(uint16_t handle, ai_cfm_gap_general cb);

/*!
    @}
*/

#endif
