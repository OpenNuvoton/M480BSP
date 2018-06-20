/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME
    hci_constant.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef _HCI_CONSTANT_H_
#define _HCI_CONSTANT_H_
#include "hci.h"
#include "ab16xx.h"
////////////////////////////////////////////////////////////////////////////////
// Bluetooth HCI Command Definitions ///////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/*
 * Status
 */
typedef enum
{
    /*! The command was successful.*/
    hci_success = 0,
    /*! Indicates that the controller does not understand the HCI Command
      Packet OpCode that the host sent. The OpCode given might not correspond
      to any of the OpCodes specified in this document, or any vendor-specific
      OpCodes, or the command may not have been implemented.*/
    hci_error_illegal_command,
    /*! Indicates that a command was sent from the host that should identify a
      connection, but that connection does not exist.*/
    hci_error_no_connection,
    /*! Indicates to the host that something in the controller has failed in a
      manner that cannot be described with any other error code.*/
    hci_error_hardware_fail,
    /*! Indicates that a page timed out because of the Page Timeout
      configuration parameter. This error code may occur only with the
      HCI_Remote_Name_Request and HCI_Create_Connection commands. */
    hci_error_page_timeout,
    /*! Indicates that pairing or authentication failed due to incorrect
      results in the pairing or authentication procedure. This could be due to
      an incorrect PIN or Link Key.*/
    hci_error_auth_fail,
    /*! Used when pairing failed because of a missing PIN.*/
    hci_error_key_missing,
    /*! Indicates to the host that the controller has run out of memory to
      store new parameters.*/
    hci_error_memory_full,
    /*! Indicates that the link supervision timeout has expired for a given
      connection.*/
    hci_error_conn_timeout,
    /*! Indicates that an attempt to create another connection failed because
      the controller is already at its limit of the number of connections it
      can support.*/
    hci_error_max_nr_of_conns,
    /*! Indicates that the controller has reached the limit to the number of
      synchronous connections that can be achieved to a device. */
    hci_error_max_nr_of_sco,
    /*! Indicates that the controller has reached the limit to the number of
      asynchronous connections that can be achieved to a device. */
    hci_error_max_nr_of_acl,
    /*! Indicates that the command requested cannot be executed because the
      controller is in a state where it cannot process this command at this
      time. This error shall not be used for command OpCodes where the error
      code Unknown HCI Command is valid.*/
    hci_error_command_disallowed,
    /*! Indicates that an incoming connection was rejected due to limited
      resources. */
    hci_error_rej_by_remote_no_res,
    /*! Indicates that a connection was rejected due to security requirements
      not being fulfilled, like authentication or pairing. */
    hci_error_rej_by_remote_sec,
    /*! Indicates that a connection was rejected because this device does not
      accept the BD_ADDR. This may be because the device will only accept
      connections from specific BD_ADDRs.*/
    hci_error_rej_by_remote_pers,
    /*! Indicates that the Connection Accept Timeout has been exceeded for this
      connection attempt */
    hci_error_host_timeout = 0x10,
    /*! Indicates that a feature or parameter value in an LMP message or HCI
      Command is not supported.*/
    hci_error_unsupported_feature,
    /*! Indicates that at least one of the HCI command parameters is invalid.*/
    hci_error_illegal_format,
    /*! Indicates that the user on the remote device terminated the
      connection.*/
    hci_error_oetc_user,
    /*! Indicates that the remote device terminated the connection because of
      low resources. */
    hci_error_oetc_low_resource,
    /*! Indicates that the remote device terminated the connection because the
      device is about to power off.*/
    hci_error_oetc_powering_off,
    /*! Indicates that the local device terminated the connection.*/
    hci_error_conn_term_local_host,
    /*! Indicates that the controller is disallowing an authentication or
      pairing procedure because too little time has elapsed since the last
      authentication or pairing attempt failed. */
    hci_error_auth_repeated,
    /*! Indicates that the device does not allow pairing. For example, when a
      device only allows pairing during a certain time window after some user
      input allows pairing.*/
    hci_error_pairing_not_allowed,
    /*! Indicates that the controller has received an unknown LMP opcode. */
    hci_error_unknown_lmp_pdu,
    /*! Indicates that the remote device does not support the feature
      associated with the issued command or LMP PDU.*/
    hci_error_unsupported_rem_feature,
    /*! Indicates that the offset requested in the LMP_SCO_link_req message has
      been rejected.*/
    hci_error_sco_offset_rejected,
    /*! Indicates that the interval requested in the LMP_SCO_link_req message
      has been rejected. */
    hci_error_sco_interval_rejected,
    /*! Indicates that the air mode requested in the LMP_SCO_link_req message
      has been rejected. */
    hci_error_sco_air_mode_rejected,
    /*! Indicates that some LMP message parameters were invalid. This shall be
      used when :
      - The PDU length is invalid.
      - A parameter value must be even.
      - A parameter is outside of the specified range.
      - Two or more parameters have inconsistent values. */
    hci_error_invalid_lmp_parameters,
    /*! Indicates that no other error code specified is appropriate to use. */
    hci_error_unspecified,
    /*! Indicates that an LMP message contains at least one parameter value
      that is not supported by the controller at this time. This is normally
      used after a long negotiation procedure, for example during an
      LMP_hold_req, LMP_sniff_req and LMP_encryption_key_size_req message
      exchanges.*/
    hci_error_unsupp_lmp_param = 0x20,
    /*! Indicates that a controller will not allow a role change at this
      time. */
    hci_error_role_change_not_allowed,
    /*! Indicates that an LMP transaction failed to respond within the LMP
      response timeout. */
    hci_error_lmp_response_timeout,
    /*! Indicates that an LMP transaction has collided with the same
      transaction that is already in progress.*/
    hci_error_lmp_transaction_collision,
    /*! Indicates that a controller sent an LMP message with an opcode that was
      not allowed.*/
    hci_error_lmp_pdu_not_allowed,
    /*! Indicates that the requested encryption mode is not acceptable at this
      time. */
    hci_error_enc_mode_not_acceptable,
    /*! Indicates that a link key can not be changed because a fixed unit key
      is being used.*/
    hci_error_unit_key_used,
    /*! Indicates that the requested Quality of Service is not supported.*/
    hci_error_qos_not_supported,
    /*! Indicates that an LMP PDU that includes an instant can not be performed
      because the instant when this would have occurred has passed.*/
    hci_error_instant_passed,
    /*! Indicates that it was not possible to pair as a unit key was requested
      and it is not supported.*/
    hci_error_pair_unit_key_no_support,
    /*! Indicates that an LMP transaction was started that collides with an
      ongoing transaction.*/
    hci_error_different_transaction_collision,
    /*! Insufficient resources.*/
    hci_error_scm_insufficient_resources,
    /*! Indicates that the specified quality of service parameters could not be
      accepted at this time, but other parameters may be acceptable.*/
    hci_error_qos_unacceptable_parameter,
    /*! Indicates that the specified quality of service parameters can not be
      accepted and QoS negotiation should be terminated.*/
    hci_error_qos_rejected,
    /*! Indicates that the controller can not perform channel classification
      because it is not supported.*/
    hci_error_channel_class_no_support,
    /*! Indicates that the HCI command or LMP message sent is only possible on
      an encrypted link.*/
    hci_error_insufficient_security,
    /*! Indicates that a parameter value requested is outside the mandatory
      range of parameters for the given HCI command or LMP message.*/
    hci_error_param_out_of_mand_range = 0x30,
    /*! No longer required.*/
    hci_error_scm_no_longer_reqd,
    /*! Indicates that a Role Switch is pending. This can be used when an HCI
      command or LMP message can not be accepted because of a pending role
      switch. This can also be used to notify a peer device about a pending
      role switch.*/
    hci_error_role_switch_pending,
    /*! Parameter change pending. */
    hci_error_scm_param_change_pending,
    /*! Indicates that the current Synchronous negotiation was terminated with
      the negotiation state set to Reserved Slot Violation.*/
    hci_error_resvd_slot_violation,
    /*! Indicates that a role switch was attempted but it failed and the
      original piconet structure is restored. The switch may have failed
      because the TDD switch or piconet switch failed.*/
    hci_error_role_switch_failed,

    hci_error_eir_too_large = 0x36,
    hci_error_simple_pairing_not_support_by_host = 0x37,
    hci_error_host_busy_pairing = 0x38,
    hci_error_directed_advertising_timeout = 0x3C,
    hci_error_conn_terminated_due_to_mic_fail = 0x3D,
    hci_error_conn_fail_to_be_established = 0x3E,

    /*! Unrecognised error. */
    hci_error_unrecognised = 0x41
} HCI_STATUS;
/*
 * HCI Command OGFs
 */
typedef uint8_t HCI_CMD_OGF;
#define HCI_CMD_OGF_LINK_CTL                                (HCI_CMD_OGF)0x01
#define HCI_CMD_OGF_LINK_POLICY                             (HCI_CMD_OGF)0x02
#define HCI_CMD_OGF_CTLR_AND_BB                             (HCI_CMD_OGF)0x03
#define HCI_CMD_OGF_INFO_PARA                               (HCI_CMD_OGF)0x04
#define HCI_CMD_OGF_STATUS_PARA                             (HCI_CMD_OGF)0x05
#define HCI_CMD_OGF_TEST                                    (HCI_CMD_OGF)0x06
#define HCI_CMD_OGF_LE_CTLR                                 (HCI_CMD_OGF)0x08
#define HCI_CMD_OGF_SDK_SPECIFIC                            (HCI_CMD_OGF)0x10
#define HCI_CMD_OGF_VENDER                                  (HCI_CMD_OGF)0x3F


/*
 * HCI Command OCFs
 */
typedef uint16_t HCI_CMD_OCF;

/* HCI Command OCF of LINK CONTROL Group */
#define HCI_CMD_OCF_INQUIRY                                 (HCI_CMD_OCF)0x01
#define HCI_CMD_OCF_INQUIRY_CANCEL                          (HCI_CMD_OCF)0x02
#define HCI_CMD_OCF_PERIODIC_INQUIRY_MODE                   (HCI_CMD_OCF)0x03
#define HCI_CMD_OCF_EXIT_PERIODIC_INQUIRY_MODE              (HCI_CMD_OCF)0x04
#define HCI_CMD_OCF_CREATE_CONNECTION                       (HCI_CMD_OCF)0x05
#define HCI_CMD_OCF_DISCONNECT                              (HCI_CMD_OCF)0x06
#define HCI_CMD_OCF_ADD_SCO_CONNECTION                      (HCI_CMD_OCF)0x07   /* Deprecated */
#define HCI_CMD_OCF_CREATE_CONNECTION_CANCEL                (HCI_CMD_OCF)0x08
#define HCI_CMD_OCF_ACCEPT_CONNECTION_REQUEST               (HCI_CMD_OCF)0x09
#define HCI_CMD_OCF_REJECT_CONNECTION_REQUEST               (HCI_CMD_OCF)0x0A
#define HCI_CMD_OCF_LINK_KEY_REQUEST_REPLY                  (HCI_CMD_OCF)0X0B
#define HCI_CMD_OCF_LINK_KEY_REQUEST_NEGATIVE_REPLY         (HCI_CMD_OCF)0X0C
#define HCI_CMD_OCF_PIN_CODE_REQUEST_REPLY                  (HCI_CMD_OCF)0X0D
#define HCI_CMD_OCF_PIN_CODE_REQUEST_NEGATIVE_REPLY         (HCI_CMD_OCF)0X0E
#define HCI_CMD_OCF_CHANGE_CONNECTION_PACKET_TYPE           (HCI_CMD_OCF)0x0F
#define HCI_CMD_OCF_ACL_U_GO_STOP_CONFIRM                   (HCI_CMD_OCF)0x10   /* Airoha defined */
#define HCI_CMD_OCF_AUTHENTICATION_REQUESTED                (HCI_CMD_OCF)0x11
#define HCI_CMD_OCF_ACL_LINK_INDEX_CHANGED_CONFIRM          (HCI_CMD_OCF)0x12   /* Airoha defined */
#define HCI_CMD_OCF_SET_CONNECTION_ENCRYPTION               (HCI_CMD_OCF)0x13
#define HCI_CMD_OCF_RESEGMENT_CNF                           (HCI_CMD_OCF)0x14   /* Airoha defined */
#define HCI_CMD_OCF_CHANGE_CONNECTION_LINK_KEY              (HCI_CMD_OCF)0x15
#define HCI_CMD_OCF_MASTER_LINK_KEY                         (HCI_CMD_OCF)0x17
#define HCI_CMD_OCF_REMOTE_NAME_REQUEST                     (HCI_CMD_OCF)0x19
#define HCI_CMD_OCF_REMOTE_NAME_REQUEST_CANCEL              (HCI_CMD_OCF)0x1A
#define HCI_CMD_OCF_READ_REMOTE_SUPPORTED_FEATURES          (HCI_CMD_OCF)0x1B
#define HCI_CMD_OCF_READ_REMOTE_EXTENDED_FEATURES           (HCI_CMD_OCF)0x1C
#define HCI_CMD_OCF_READ_REMOTE_VERSION_INFORMATION         (HCI_CMD_OCF)0x1D
#define HCI_CMD_OCF_READ_CLOCK_OFFSET                       (HCI_CMD_OCF)0x1F
#define HCI_CMD_OCF_READ_LMP_HANDLE                         (HCI_CMD_OCF)0x20
#define HCI_CMD_OCF_SETUP_SYNCHRONOUS_CONNECTION            (HCI_CMD_OCF)0x28
#define HCI_CMD_OCF_ACCEPT_SYNCHRONOUS_CONNECTION_REQUEST   (HCI_CMD_OCF)0x29
#define HCI_CMD_OCF_REJECT_SYNCHRONOUS_CONNECTION_REQUEST   (HCI_CMD_OCF)0x2A
#define HCI_CMD_OCF_IO_CAPABILITY_REQUEST_REPLY             (HCI_CMD_OCF)0x2B
#define HCI_CMD_OCF_USR_CONFIRMATION_REQ_REPLY              (HCI_CMD_OCF)0x2C
#define HCI_CMD_OCF_USR_CONFIRMATION_REQ_NEGATIVE_REPLY     (HCI_CMD_OCF)0x2D
#define HCI_CMD_OCF_USR_PASSKEY_REQ_REPLY                   (HCI_CMD_OCF)0x2E
#define HCI_CMD_OCF_USR_PASSKEY_REQ_NEGATIVE_REPLY          (HCI_CMD_OCF)0x2F
#define HCI_CMD_OCF_REMOTE_OOB_DATA_REQ_REPLY               (HCI_CMD_OCF)0x30
#define HCI_CMD_OCF_REMOTE_OOB_DATA_REQ_NEGATIVE_REPLY      (HCI_CMD_OCF)0x33
#define HCI_CMD_OCF_IO_CAPABILITY_REQ_NEGATIVE_REPLY        (HCI_CMD_OCF)0x34
#define HCI_CMD_OCF_CREATE_PHYSICAL_LINK                    (HCI_CMD_OCF)0x35
#define HCI_CMD_OCF_ACCEPT_PHYSICAL_LINK                    (HCI_CMD_OCF)0x36
#define HCI_CMD_OCF_DISCONNECT_PHYSICAL_LINK                (HCI_CMD_OCF)0x37
#define HCI_CMD_OCF_CREATE_LOGICAL_LINK                     (HCI_CMD_OCF)0x38
#define HCI_CMD_OCF_ACCEPT_LOGICAL_LINK                     (HCI_CMD_OCF)0x39
#define HCI_CMD_OCF_DISCONNECT_LOGICAL_LINK                 (HCI_CMD_OCF)0x3A
#define HCI_CMD_OCF_LOGICAL_LINK_CANCEL                     (HCI_CMD_OCF)0x3B
#define HCI_CMD_OCF_FLOW_SPEC_MODIFY                        (HCI_CMD_OCF)0x3C

/* HCI Command OCF of LINK POLICY Group */
#define HCI_CMD_OCF_HOLD_MODE                               (HCI_CMD_OCF)0x01
#define HCI_CMD_OCF_SNIFF_MODE                              (HCI_CMD_OCF)0x03
#define HCI_CMD_OCF_EXIT_SNIFF_MODE                         (HCI_CMD_OCF)0x04
#define HCI_CMD_OCF_PARK_STATE                              (HCI_CMD_OCF)0x05
#define HCI_CMD_OCF_EXIT_PARK_STATE                         (HCI_CMD_OCF)0x06
#define HCI_CMD_OCF_QOS_SETUP                               (HCI_CMD_OCF)0x07
#define HCI_CMD_OCF_ROLE_DISCOVERY                          (HCI_CMD_OCF)0x09
#define HCI_CMD_OCF_SWITCH_ROLE                             (HCI_CMD_OCF)0x0B
#define HCI_CMD_OCF_READ_LINK_POLICY_SETTINGS               (HCI_CMD_OCF)0x0C
#define HCI_CMD_OCF_WRITE_LINK_POLICY_SETTINGS              (HCI_CMD_OCF)0x0D
#define HCI_CMD_OCF_READ_DEFAULT_LINK_POLICY_SETTINGS       (HCI_CMD_OCF)0x0E
#define HCI_CMD_OCF_WRITE_DEFAULT_LINK_POLICY_SETTINGS      (HCI_CMD_OCF)0x0F
#define HCI_CMD_OCF_FLOW_SPECIFICATION                      (HCI_CMD_OCF)0x10
#define HCI_CMD_OCF_SNIFF_SUBRATING                         (HCI_CMD_OCF)0x11

/* HCI Command OCF of CONTROLLER AND BASEBAND Group */
#define HCI_CMD_OCF_SET_EVENT_MASK                          (HCI_CMD_OCF)0x01
#define HCI_CMD_OCF_RESET                                   (HCI_CMD_OCF)0x03
#define HCI_CMD_OCF_SET_EVENT_FILTER                        (HCI_CMD_OCF)0x05
#define HCI_CMD_OCF_FLUSH                                   (HCI_CMD_OCF)0x08
#define HCI_CMD_OCF_READ_PIN_TYPE                           (HCI_CMD_OCF)0x09
#define HCI_CMD_OCF_WRITE_PIN_TYPE                          (HCI_CMD_OCF)0x0A
#define HCI_CMD_OCF_CREATE_NEW_UNIT_KEY                     (HCI_CMD_OCF)0x0B
#define HCI_CMD_OCF_READ_STORED_LINK_KEY                    (HCI_CMD_OCF)0x0D
#define HCI_CMD_OCF_WRITE_STORED_LINK_KEY                   (HCI_CMD_OCF)0x11
#define HCI_CMD_OCF_DELETE_STORED_LINK_KEY                  (HCI_CMD_OCF)0x12
#define HCI_CMD_OCF_WRITE_LOCAL_NAME                        (HCI_CMD_OCF)0x13
#define HCI_CMD_OCF_READ_LOCAL_NAME                         (HCI_CMD_OCF)0x14
#define HCI_CMD_OCF_READ_CONNECTION_ACCEPT_TIMEOUT          (HCI_CMD_OCF)0x15
#define HCI_CMD_OCF_WRITE_CONNECTION_ACCEPT_TIMEOUT         (HCI_CMD_OCF)0x16
#define HCI_CMD_OCF_READ_PAGE_TIMEOUT                       (HCI_CMD_OCF)0x17
#define HCI_CMD_OCF_WRITE_PAGE_TIMEOUT                      (HCI_CMD_OCF)0x18
#define HCI_CMD_OCF_READ_SCAN_ENABLE                        (HCI_CMD_OCF)0x19
#define HCI_CMD_OCF_WRITE_SCAN_ENABLE                       (HCI_CMD_OCF)0x1A
#define HCI_CMD_OCF_READ_PAGE_SCAN_ACTIVITY                 (HCI_CMD_OCF)0x1B
#define HCI_CMD_OCF_WRITE_PAGE_SCAN_ACTIVITY                (HCI_CMD_OCF)0x1C
#define HCI_CMD_OCF_READ_INQUIRY_SCAN_ACTIVITY              (HCI_CMD_OCF)0x1D
#define HCI_CMD_OCF_WRITE_INQUIRY_SCAN_ACTIVITY             (HCI_CMD_OCF)0x1E
#define HCI_CMD_OCF_READ_AUTHENTICATION_ENABLE              (HCI_CMD_OCF)0x1F
#define HCI_CMD_OCF_WRITE_AUTHENTICATION_ENABLE             (HCI_CMD_OCF)0x20
#define HCI_CMD_OCF_READ_ENCRYPTION_MODE                    (HCI_CMD_OCF)0x21   /* Deprecated */
#define HCI_CMD_OCF_WRITE_ENCRYPTION_MODE                   (HCI_CMD_OCF)0x22   /* Deprecated */
#define HCI_CMD_OCF_READ_CLASS_OF_DEVICE                    (HCI_CMD_OCF)0x23
#define HCI_CMD_OCF_WRITE_CLASS_OF_DEVICE                   (HCI_CMD_OCF)0x24
#define HCI_CMD_OCF_READ_VOICE_SETTING                      (HCI_CMD_OCF)0x25
#define HCI_CMD_OCF_WRITE_VOICE_SETTING                     (HCI_CMD_OCF)0x26
#define HCI_CMD_OCF_READ_AUTOMATIC_FLUSH_TIMEOUT            (HCI_CMD_OCF)0x27
#define HCI_CMD_OCF_WRITE_AUTOMATIC_FLUSH_TIMEOUT           (HCI_CMD_OCF)0x28
#define HCI_CMD_OCF_READ_NUM_BROADCAST_RETRANSMISSIONS       (HCI_CMD_OCF)0x29
#define HCI_CMD_OCF_WRITE_NUM_BROADCAST_RETRANSMISSIONS      (HCI_CMD_OCF)0x2A
#define HCI_CMD_OCF_READ_HOLD_MODE_ACTIVITY                 (HCI_CMD_OCF)0x2B
#define HCI_CMD_OCF_WRITE_HOLD_MODE_ACTIVITY                (HCI_CMD_OCF)0x2C
#define HCI_CMD_OCF_READ_TRANSMIT_POWER_LEVEL               (HCI_CMD_OCF)0x2D
#define HCI_CMD_OCF_READ_SYNCHRONOUS_FLOW_CONTROL_ENABLE    (HCI_CMD_OCF)0x2E
#define HCI_CMD_OCF_WRITE_SYNCHRONOUS_FLOW_CONTROL_ENABLE   (HCI_CMD_OCF)0x2F
#define HCI_CMD_OCF_SET_CONTROLLER_TO_HOST_FLOW_CONTROL     (HCI_CMD_OCF)0x31
#define HCI_CMD_OCF_HOST_BUFFER_SIZE                        (HCI_CMD_OCF)0x33
#define HCI_CMD_OCF_HOST_NUMBER_OF_COMPLETED_PACKETS        (HCI_CMD_OCF)0x35
#define HCI_CMD_OCF_READ_LINK_SUPERVISION_TIMEOUT           (HCI_CMD_OCF)0x36
#define HCI_CMD_OCF_WRITE_LINK_SUPERVISION_TIMEOUT          (HCI_CMD_OCF)0x37
#define HCI_CMD_OCF_READ_NUMBER_OF_SUPPORTED_IAC            (HCI_CMD_OCF)0x38
#define HCI_CMD_OCF_READ_CURRENT_IAC_LAP                    (HCI_CMD_OCF)0x39
#define HCI_CMD_OCF_WRITE_CURRENT_IAC_LAP                   (HCI_CMD_OCF)0x3A
#define HCI_CMD_OCF_SET_AFH_HOST_CHANNEL_CLASSIFICATION     (HCI_CMD_OCF)0x3F
#define HCI_CMD_OCF_READ_INQUIRY_SCAN_TYPE                  (HCI_CMD_OCF)0x42
#define HCI_CMD_OCF_WRITE_INQUIRY_SCAN_TYPE                 (HCI_CMD_OCF)0x43
#define HCI_CMD_OCF_READ_INQUIRY_MODE                       (HCI_CMD_OCF)0x44
#define HCI_CMD_OCF_WRITE_INQUIRY_MODE                      (HCI_CMD_OCF)0x45
#define HCI_CMD_OCF_READ_PAGE_SCAN_TYPE                     (HCI_CMD_OCF)0x46
#define HCI_CMD_OCF_WRITE_PAGE_SCAN_TYPE                    (HCI_CMD_OCF)0x47
#define HCI_CMD_OCF_READ_AFH_CHANNEL_ASSESSMENT_MODE        (HCI_CMD_OCF)0x48
#define HCI_CMD_OCF_WRITE_AFH_CHANNEL_ASSESSMENT_MODE       (HCI_CMD_OCF)0x49
#define HCI_CMD_OCF_READ_EXTENDED_INQUIRY_RESPONSE          (HCI_CMD_OCF)0x51
#define HCI_CMD_OCF_WRITE_EXTENDED_INQUIRY_RESPONSE         (HCI_CMD_OCF)0x52
#define HCI_CMD_OCF_REFRESH_ENCRYPTION_KEY                  (HCI_CMD_OCF)0x53
#define HCI_CMD_OCF_READ_SIMPLE_PAIRING_MODE                (HCI_CMD_OCF)0x55
#define HCI_CMD_OCF_WRITE_SIMPLE_PAIRING_MODE               (HCI_CMD_OCF)0x56
#define HCI_CMD_OCF_READ_LOCAL_OOB_DATA                     (HCI_CMD_OCF)0x57
#define HCI_CMD_OCF_READ_INQUIRY_RESPONSE_TX_POWER_LEVEL    (HCI_CMD_OCF)0x58
#define HCI_CMD_OCF_WRITE_INQUIRY_TX_POWER_LEVEL            (HCI_CMD_OCF)0x59
#define HCI_CMD_OCF_READ_DEFAULT_ERRONEOUS_DATA_REPORTING   (HCI_CMD_OCF)0x5A
#define HCI_CMD_OCF_WRITE_DEFAULT_ERRONEOUS_DATA_REPORTING  (HCI_CMD_OCF)0x5B
#define HCI_CMD_OCF_ENHANCED_FLUSH                          (HCI_CMD_OCF)0x5F
#define HCI_CMD_OCF_SEND_KEYPRESS_NOTIFICATION              (HCI_CMD_OCF)0x60
#define HCI_CMD_OCF_READ_LOGICAL_LINK_ACCEPT_TIMEOUT        (HCI_CMD_OCF)0x61
#define HCI_CMD_OCF_WRITE_LOGICAL_LINK_ACCEPT_TIMEOUT       (HCI_CMD_OCF)0x62
#define HCI_CMD_OCF_SET_EVENT_MASK_PAGE_2                   (HCI_CMD_OCF)0x63
#define HCI_CMD_OCF_READ_LOCATION_DATA                      (HCI_CMD_OCF)0x64
#define HCI_CMD_OCF_WRITE_LOCATION_DATA                     (HCI_CMD_OCF)0x65
#define HCI_CMD_OCF_READ_FLOW_CONTROL_MODE                  (HCI_CMD_OCF)0x66
#define HCI_CMD_OCF_WRITE_FLOW_CONTROL_MODE                 (HCI_CMD_OCF)0x67
#define HCI_CMD_OCF_READ_ENHANCE_TRANSMIT_POWER_LEVEL       (HCI_CMD_OCF)0x68
#define HCI_CMD_OCF_READ_BEST_EFFORT_FLUSH_TIMEOUT          (HCI_CMD_OCF)0x69
#define HCI_CMD_OCF_WRITE_BEST_EFFORT_FLUSH_TIMEOUT         (HCI_CMD_OCF)0x6A
#define HCI_CMD_OCF_SHORT_RANGE_MODE                        (HCI_CMD_OCF)0x6B
#define HCI_CMD_OCF_READ_LE_HOST_SUPPORT                    (HCI_CMD_OCF)0x6C
#define HCI_CMD_OCF_WRITE_LE_HOST_SUPPORT                   (HCI_CMD_OCF)0x6D

/* HCI Command OCF of INFORMATION PARAMETER Group */
#define HCI_CMD_OCF_READ_LOCAL_VERSION_INFORMATION          (HCI_CMD_OCF)0x01
#define HCI_CMD_OCF_READ_LOCAL_SUPPORTED_COMMANDS           (HCI_CMD_OCF)0x02
#define HCI_CMD_OCF_READ_LOCAL_SUPPORTED_FEATURES           (HCI_CMD_OCF)0x03
#define HCI_CMD_OCF_READ_LOCAL_EXTENDED_FEATURES            (HCI_CMD_OCF)0x04
#define HCI_CMD_OCF_READ_BUFFER_SIZE                        (HCI_CMD_OCF)0x05
#define HCI_CMD_OCF_READ_BD_ADDR                            (HCI_CMD_OCF)0x09
#define HCI_CMD_OCF_READ_DATE_BLOCK_SIZE                    (HCI_CMD_OCF)0x0A

/* HCI Command OCF of STATUS PARAMETER Group */
#define HCI_CMD_OCF_READ_FAILED_CONTACT_COUNTER             (HCI_CMD_OCF)0x01
#define HCI_CMD_OCF_RESET_FAILED_CONTACT_COUNTER            (HCI_CMD_OCF)0x02
#define HCI_CMD_OCF_READ_LINK_QUALITY                       (HCI_CMD_OCF)0x03
#define HCI_CMD_OCF_READ_RSSI                               (HCI_CMD_OCF)0x05
#define HCI_CMD_OCF_READ_AFH_CHANNEL_MAP                    (HCI_CMD_OCF)0x06
#define HCI_CMD_OCF_READ_CLOCK                              (HCI_CMD_OCF)0x07
#define HCI_CMD_OCF_READ_ENCRYPTION_KEY_SIZE                (HCI_CMD_OCF)0x08
#define HCI_CMD_OCF_READ_LOCAL_AMP_INFO                     (HCI_CMD_OCF)0x09
#define HCI_CMD_OCF_READ_LOCAL_AMP_ASSOC                    (HCI_CMD_OCF)0x0A
#define HCI_CMD_OCF_WRITE_REMOTE_AMP_ASSOC                  (HCI_CMD_OCF)0x0B

/* HCI Command OCF of TEST Group */
#define HCI_CMD_OCF_READ_LOOPBACK_MODE                      (HCI_CMD_OCF)0x01
#define HCI_CMD_OCF_WRITE_LOOPBACK_MODE                     (HCI_CMD_OCF)0x02
#define HCI_CMD_OCF_ENABLE_DEVICE_UNDER_TEST_MODE           (HCI_CMD_OCF)0x03
#define HCI_CMD_OCF_WRITE_SIMPLE_PAIRING_DEBUG_MODE         (HCI_CMD_OCF)0x04
#define HCI_CMD_OCF_ENABLE_AMP_RECEIVER_REPORTS             (HCI_CMD_OCF)0x07
#define HCI_CMD_OCF_AMP_TEST_END                            (HCI_CMD_OCF)0x08
#define HCI_CMD_OCF_AMP_TEST                                (HCI_CMD_OCF)0x09

/* HCI Command OCF of LE CONTROLLER Group */
#define HCI_CMD_OCF_LE_SET_EVENT_MASK                          (HCI_CMD_OCF)0x01
#define HCI_CMD_OCF_LE_READ_BUFFER_SIZE                        (HCI_CMD_OCF)0x02
#define HCI_CMD_OCF_LE_READ_LOCAL_SUPPORTED_FEATURES           (HCI_CMD_OCF)0x03
#define HCI_CMD_OCF_LE_SET_RANDOM_ADDRESS                      (HCI_CMD_OCF)0x05
#define HCI_CMD_OCF_LE_SET_ADVERTISING_PARAMETER               (HCI_CMD_OCF)0x06
#define HCI_CMD_OCF_LE_READ_ADVERTISING_CHANNEL_TX_POWER       (HCI_CMD_OCF)0x07
#define HCI_CMD_OCF_LE_ADVERTISING_DATA                        (HCI_CMD_OCF)0x08
#define HCI_CMD_OCF_LE_SET_SCAN_RESPONSE_DATA                  (HCI_CMD_OCF)0x09
#define HCI_CMD_OCF_LE_SET_ADVERTISING_ENABLE                  (HCI_CMD_OCF)0x0A
#define HCI_CMD_OCF_LE_SET_SCAN_PARAMETERS                     (HCI_CMD_OCF)0x0B
#define HCI_CMD_OCF_LE_SET_SCAN_ENABLE                         (HCI_CMD_OCF)0x0C
#define HCI_CMD_OCF_LE_CREATE_CONNECTION                       (HCI_CMD_OCF)0x0D
#define HCI_CMD_OCF_LE_CREATE_CONNECTION_CANCEL                (HCI_CMD_OCF)0x0E
#define HCI_CMD_OCF_LE_READ_WHITE_LIST_SIZE                    (HCI_CMD_OCF)0x0F
#define HCI_CMD_OCF_LE_CLEAR_WHITE_LIST                        (HCI_CMD_OCF)0x10
#define HCI_CMD_OCF_LE_ADD_DEVICE_TO_WHITE_LIST                (HCI_CMD_OCF)0x11
#define HCI_CMD_OCF_LE_REMOVE_DEVICE_FROM_WHITE_LIST           (HCI_CMD_OCF)0x12
#define HCI_CMD_OCF_LE_CONNECTION_UPDATE                       (HCI_CMD_OCF)0x13
#define HCI_CMD_OCF_LE_SET_HOST_CHANNEL_CLASSIFICATION         (HCI_CMD_OCF)0x14
#define HCI_CMD_OCF_LE_READ_CHANNEL_MAP                        (HCI_CMD_OCF)0x15
#define HCI_CMD_OCF_LE_READ_REMOTE_USED_FEATURES               (HCI_CMD_OCF)0x16
#define HCI_CMD_OCF_LE_ENCRYPT                                 (HCI_CMD_OCF)0x17
#define HCI_CMD_OCF_LE_RAND                                    (HCI_CMD_OCF)0x18
#define HCI_CMD_OCF_LE_START_ENCRYPTION                        (HCI_CMD_OCF)0x19
#define HCI_CMD_OCF_LE_LONG_TERM_KEY_REQUEST_REPLY             (HCI_CMD_OCF)0x1A
#define HCI_CMD_OCF_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY    (HCI_CMD_OCF)0x1B
#define HCI_CMD_OCF_LE_READ_SUPPORTED_STATES                   (HCI_CMD_OCF)0x1C
#define HCI_CMD_OCF_LE_RECEIVER_TEST                           (HCI_CMD_OCF)0x1D
#define HCI_CMD_OCF_LE_TRANSMITTER_TEST                        (HCI_CMD_OCF)0x1E
#define HCI_CMD_OCF_LE_TEST_END                                (HCI_CMD_OCF)0x1F
#define HCI_CMD_OCF_LE_REMOTE_CONNECTION_PARAM_REQ_REPLY       (HCI_CMD_OCF)0x20 /*added in BT 4.1*/
#define HCI_CMD_OCF_LE_REMOTE_CONNECTION_PARAM_REQ_NEG_REPLY   (HCI_CMD_OCF)0x21 /*added in BT 4.1*/
#define HCI_CMD_OCF_LE_READ_LOCAL_P256_PUBLIC_KEY              (HCI_CMD_OCF)0x25 /*added in BT 4.2*/
#define HCI_CMD_OCF_LE_GENERATE_DHKEY                          (HCI_CMD_OCF)0x26 /*added in BT 4.2*/

/* HCI Command OCF of chip specific Group */
#define HCI_CMD_OCF_CHIP_SET_PUB_ADDRESS                       (HCI_CMD_OCF)0x00
#define HCI_CMD_OCF_CHIP_SET_TX_POWER                          (HCI_CMD_OCF)0x01
#define HCI_CMD_OCF_CHIP_GET_PUB_ADDRESS                       (HCI_CMD_OCF)0x02
#define HCI_CMD_OCF_CHIP_READ_SFR                              (HCI_CMD_OCF)0x03
#define HCI_CMD_OCF_CHIP_SET_DISABLE_LAENCY                    (HCI_CMD_OCF)0x04


/*
 * HCI Command OPCODE
 */
typedef uint16_t HCI_OPCODE;
#define HCI_COMBINED_OPCODE(ogf,ocf) (((HCI_OPCODE)(ogf)<<10)|(HCI_OPCODE)(ocf))

/* HCI Link Control Command OpCode */
#define HCI_CMDCODE_INQUIRY                                 HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_INQUIRY)
#define HCI_CMDCODE_INQUIRY_CANCEL                          HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_INQUIRY_CANCEL)
#define HCI_CMDCODE_PERIODIC_INQUIRY_MODE                   HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_PERIODIC_INQUIRY_MODE)
#define HCI_CMDCODE_EXIT_PERIODIC_INQUIRY_MODE              HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_EXIT_PERIODIC_INQUIRY_MODE)
#define HCI_CMDCODE_CREATE_CONNECTION                       HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_CREATE_CONNECTION)
#define HCI_CMDCODE_DISCONNECT                              HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_DISCONNECT)
#define HCI_CMDCODE_ADD_SCO_CONNECTION                      HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_ADD_SCO_CONNECTION)
#define HCI_CMDCODE_CREATE_CONNECTION_CANCEL                HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_CREATE_CONNECTION_CANCEL)
#define HCI_CMDCODE_ACCEPT_CONNECTION_REQUEST               HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_ACCEPT_CONNECTION_REQUEST)
#define HCI_CMDCODE_REJECT_CONNECTION_REQUEST               HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_REJECT_CONNECTION_REQUEST)
#define HCI_CMDCODE_LINK_KEY_REQUEST_REPLY                  HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_LINK_KEY_REQUEST_REPLY)
#define HCI_CMDCODE_LINK_KEY_REQUEST_NEGATIVE_REPLY         HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_LINK_KEY_REQUEST_NEGATIVE_REPLY)
#define HCI_CMDCODE_PIN_CODE_REQUEST_REPLY                  HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_PIN_CODE_REQUEST_REPLY)
#define HCI_CMDCODE_PIN_CODE_REQUEST_NEGATIVE_REPLY         HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_PIN_CODE_REQUEST_NEGATIVE_REPLY)
#define HCI_CMDCODE_CHANGE_CONNECTION_PACKET_TYPE           HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_CHANGE_CONNECTION_PACKET_TYPE)
#define HCI_CMDCODE_ACL_U_GO_STOP_CONFIRM                   HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_ACL_U_GO_STOP_CONFIRM)
#define HCI_CMDCODE_AUTHENTICATION_REQUESTED                HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_AUTHENTICATION_REQUESTED)
#define HCI_CMDCODE_ACL_LINK_INDEX_CHANGED_CONFIRM          HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_ACL_LINK_INDEX_CHANGED_CONFIRM)
#define HCI_CMDCODE_SET_CONNECTION_ENCRYPTION               HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_SET_CONNECTION_ENCRYPTION)
#define HCI_CMDCODE_RESEGMENT_CNF                           HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_RESEGMENT_CNF)
#define HCI_CMDCODE_CHANGE_CONNECTION_LINK_KEY              HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_CHANGE_CONNECTION_LINK_KEY)
#define HCI_CMDCODE_MASTER_LINK_KEY                         HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_MASTER_LINK_KEY)
#define HCI_CMDCODE_REMOTE_NAME_REQUEST                     HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_REMOTE_NAME_REQUEST)
#define HCI_CMDCODE_REMOTE_NAME_REQUEST_CANCEL              HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_REMOTE_NAME_REQUEST_CANCEL)
#define HCI_CMDCODE_READ_REMOTE_SUPPORTED_FEATURES          HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_READ_REMOTE_SUPPORTED_FEATURES)
#define HCI_CMDCODE_READ_REMOTE_EXTENDED_FEATURES           HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_READ_REMOTE_EXTENDED_FEATURES)
#define HCI_CMDCODE_READ_REMOTE_VERSION_INFORMATION         HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_READ_REMOTE_VERSION_INFORMATION)
#define HCI_CMDCODE_READ_CLOCK_OFFSET                       HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_READ_CLOCK_OFFSET)
#define HCI_CMDCODE_READ_LMP_HANDLE                         HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_READ_LMP_HANDLE)
#define HCI_CMDCODE_SETUP_SYNCHRONOUS_CONNECTION            HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_SETUP_SYNCHRONOUS_CONNECTION)
#define HCI_CMDCODE_ACCEPT_SYNCHRONOUS_CONNECTION_REQUEST   HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_ACCEPT_SYNCHRONOUS_CONNECTION_REQUEST)
#define HCI_CMDCODE_REJECT_SYNCHRONOUS_CONNECTION_REQUEST   HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_REJECT_SYNCHRONOUS_CONNECTION_REQUEST)
#define HCI_CMDCODE_IO_CAPABILITY_REQUEST_REPLY             HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_IO_CAPABILITY_REQUEST_REPLY)
#define HCI_CMDCODE_USR_CONFIRMATION_REQ_REPLY              HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_USR_CONFIRMATION_REQ_REPLY)
#define HCI_CMDCODE_USR_CONFIRMATION_REQ_NEGATIVE_REPLY     HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_USR_CONFIRMATION_REQ_NEGATIVE_REPLY)
#define HCI_CMDCODE_USR_PASSKEY_REQ_REPLY                   HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_USR_PASSKEY_REQ_REPLY)
#define HCI_CMDCODE_USR_PASSKEY_REQ_NEGATIVE_REPLY          HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_USR_PASSKEY_REQ_NEGATIVE_REPLY)
#define HCI_CMDCODE_REMOTE_OOB_DATA_REQ_REPLY               HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_REMOTE_OOB_DATA_REQ_REPLY)
#define HCI_CMDCODE_REMOTE_OOB_DATA_REQ_NEGATIVE_REPLY      HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_REMOTE_OOB_DATA_REQ_NEGATIVE_REPLY)
#define HCI_CMDCODE_IO_CAPABILITY_REQ_NEGATIVE_REPLY        HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_IO_CAPABILITY_REQ_NEGATIVE_REPLY)
#define HCI_CMDCODE_CREATE_PHYSICAL_LINK                    HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_CREATE_PHYSICAL_LINK)
#define HCI_CMDCODE_ACCEPT_PHYSICAL_LINK                    HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_ACCEPT_PHYSICAL_LINK)
#define HCI_CMDCODE_DISCONNECT_PHYSICAL_LINK                HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_DISCONNECT_PHYSICAL_LINK)
#define HCI_CMDCODE_CREATE_LOGICAL_LINK                     HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_CREATE_LOGICAL_LINK)
#define HCI_CMDCODE_ACCEPT_LOGICAL_LINK                     HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_ACCEPT_LOGICAL_LINK)
#define HCI_CMDCODE_DISCONNECT_LOGICAL_LINK                 HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_DISCONNECT_LOGICAL_LINK)
#define HCI_CMDCODE_LOGICAL_LINK_CANCEL                     HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_LOGICAL_LINK_CANCEL)
#define HCI_CMDCODE_FLOW_SPEC_MODIFY                        HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_CTL,HCI_CMD_OCF_FLOW_SPEC_MODIFY)

/* HCI Link Policy Command OpCode */
#define HCI_CMDCODE_HOLD_MODE                               HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_POLICY,HCI_CMD_OCF_HOLD_MODE)
#define HCI_CMDCODE_SNIFF_MODE                              HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_POLICY,HCI_CMD_OCF_SNIFF_MODE)
#define HCI_CMDCODE_EXIT_SNIFF_MODE                         HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_POLICY,HCI_CMD_OCF_EXIT_SNIFF_MODE)
#define HCI_CMDCODE_PARK_STATE                              HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_POLICY,HCI_CMD_OCF_PARK_STATE)
#define HCI_CMDCODE_EXIT_PARK_STATE                         HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_POLICY,HCI_CMD_OCF_EXIT_PARK_STATE)
#define HCI_CMDCODE_QOS_SETUP                               HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_POLICY,HCI_CMD_OCF_QOS_SETUP)
#define HCI_CMDCODE_ROLE_DISCOVERY                          HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_POLICY,HCI_CMD_OCF_ROLE_DISCOVERY)
#define HCI_CMDCODE_SWITCH_ROLE                             HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_POLICY,HCI_CMD_OCF_SWITCH_ROLE)
#define HCI_CMDCODE_READ_LINK_POLICY_SETTINGS               HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_POLICY,HCI_CMD_OCF_READ_LINK_POLICY_SETTINGS)
#define HCI_CMDCODE_WRITE_LINK_POLICY_SETTINGS              HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_POLICY,HCI_CMD_OCF_WRITE_LINK_POLICY_SETTINGS)
#define HCI_CMDCODE_READ_DEFAULT_LINK_POLICY_SETTINGS       HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_POLICY,HCI_CMD_OCF_READ_DEFAULT_LINK_POLICY_SETTINGS)
#define HCI_CMDCODE_WRITE_DEFAULT_LINK_POLICY_SETTINGS      HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_POLICY,HCI_CMD_OCF_WRITE_DEFAULT_LINK_POLICY_SETTINGS)
#define HCI_CMDCODE_FLOW_SPECIFICATION                      HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_POLICY,HCI_CMD_OCF_FLOW_SPECIFICATION)
#define HCI_CMDCODE_SNIFF_SUBRATING                         HCI_COMBINED_OPCODE(HCI_CMD_OGF_LINK_POLICY,HCI_CMD_OCF_SNIFF_SUBRATING)

/* HCI Controller And Baseband Command OpCode */
#define HCI_CMDCODE_SET_EVENT_MASK                          HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_SET_EVENT_MASK)
#define HCI_CMDCODE_RESET                                   HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_RESET)
#define HCI_CMDCODE_SET_EVENT_FILTER                        HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_SET_EVENT_FILTER)
#define HCI_CMDCODE_FLUSH                                   HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_FLUSH)
#define HCI_CMDCODE_READ_PIN_TYPE                           HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_PIN_TYPE)
#define HCI_CMDCODE_WRITE_PIN_TYPE                          HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_PIN_TYPE)
#define HCI_CMDCODE_CREATE_NEW_UNIT_KEY                     HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_CREATE_NEW_UNIT_KEY)
#define HCI_CMDCODE_READ_STORED_LINK_KEY                    HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_STORED_LINK_KEY)
#define HCI_CMDCODE_WRITE_STORED_LINK_KEY                   HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_STORED_LINK_KEY)
#define HCI_CMDCODE_DELETE_STORED_LINK_KEY                  HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_DELETE_STORED_LINK_KEY)
#define HCI_CMDCODE_WRITE_LOCAL_NAME                        HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_LOCAL_NAME)
#define HCI_CMDCODE_READ_LOCAL_NAME                         HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_LOCAL_NAME)
#define HCI_CMDCODE_READ_CONNECTION_ACCEPT_TIMEOUT          HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_CONNECTION_ACCEPT_TIMEOUT)
#define HCI_CMDCODE_WRITE_CONNECTION_ACCEPT_TIMEOUT         HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_CONNECTION_ACCEPT_TIMEOUT)
#define HCI_CMDCODE_READ_PAGE_TIMEOUT                       HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_PAGE_TIMEOUT)
#define HCI_CMDCODE_WRITE_PAGE_TIMEOUT                      HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_PAGE_TIMEOUT)
#define HCI_CMDCODE_READ_SCAN_ENABLE                        HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_SCAN_ENABLE)
#define HCI_CMDCODE_WRITE_SCAN_ENABLE                       HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_SCAN_ENABLE)
#define HCI_CMDCODE_READ_PAGE_SCAN_ACTIVITY                 HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_PAGE_SCAN_ACTIVITY)
#define HCI_CMDCODE_WRITE_PAGE_SCAN_ACTIVITY                HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_PAGE_SCAN_ACTIVITY)
#define HCI_CMDCODE_READ_INQUIRY_SCAN_ACTIVITY              HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_INQUIRY_SCAN_ACTIVITY)
#define HCI_CMDCODE_WRITE_INQUIRY_SCAN_ACTIVITY             HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_INQUIRY_SCAN_ACTIVITY)
#define HCI_CMDCODE_READ_AUTHENTICATION_ENABLE              HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_AUTHENTICATION_ENABLE)
#define HCI_CMDCODE_WRITE_AUTHENTICATION_ENABLE             HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_AUTHENTICATION_ENABLE)
#define HCI_CMDCODE_READ_ENCRYPTION_MODE                    HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_ENCRYPTION_MODE)
#define HCI_CMDCODE_WRITE_ENCRYPTION_MODE                   HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_ENCRYPTION_MODE)
#define HCI_CMDCODE_READ_CLASS_OF_DEVICE                    HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_CLASS_OF_DEVICE)
#define HCI_CMDCODE_WRITE_CLASS_OF_DEVICE                   HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_CLASS_OF_DEVICE)
#define HCI_CMDCODE_READ_VOICE_SETTING                      HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_VOICE_SETTING)
#define HCI_CMDCODE_WRITE_VOICE_SETTING                     HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_VOICE_SETTING)
#define HCI_CMDCODE_READ_AUTOMATIC_FLUSH_TIMEOUT            HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_AUTOMATIC_FLUSH_TIMEOUT)
#define HCI_CMDCODE_WRITE_AUTOMATIC_FLUSH_TIMEOUT           HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_AUTOMATIC_FLUSH_TIMEOUT)
#define HCI_CMDCODE_READ_NUM_BROADCAST_RETRANSMISSIONS       HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_NUM_BROADCAST_RETRANSMISSIONS)
#define HCI_CMDCODE_WRITE_NUM_BROADCAST_RETRANSMISSIONS      HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_NUM_BROADCAST_RETRANSMISSIONS)
#define HCI_CMDCODE_READ_HOLD_MODE_ACTIVITY                 HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_HOLD_MODE_ACTIVITY)
#define HCI_CMDCODE_WRITE_HOLD_MODE_ACTIVITY                HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_HOLD_MODE_ACTIVITY)
#define HCI_CMDCODE_READ_TRANSMIT_POWER_LEVEL               HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_TRANSMIT_POWER_LEVEL)
#define HCI_CMDCODE_READ_SYNCHRONOUS_FLOW_CONTROL_ENABLE    HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_SYNCHRONOUS_FLOW_CONTROL_ENABLE)
#define HCI_CMDCODE_WRITE_SYNCHRONOUS_FLOW_CONTROL_ENABLE   HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_SYNCHRONOUS_FLOW_CONTROL_ENABLE)
#define HCI_CMDCODE_SET_CONTROLLER_TO_HOST_FLOW_CONTROL     HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_SET_CONTROLLER_TO_HOST_FLOW_CONTROL)
#define HCI_CMDCODE_HOST_BUFFER_SIZE                        HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_HOST_BUFFER_SIZE)
#define HCI_CMDCODE_HOST_NUMBER_OF_COMPLETED_PACKETS        HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_HOST_NUMBER_OF_COMPLETED_PACKETS)
#define HCI_CMDCODE_READ_LINK_SUPERVISION_TIMEOUT           HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_LINK_SUPERVISION_TIMEOUT)
#define HCI_CMDCODE_WRITE_LINK_SUPERVISION_TIMEOUT          HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_LINK_SUPERVISION_TIMEOUT)
#define HCI_CMDCODE_READ_NUMBER_OF_SUPPORTED_IAC            HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_NUMBER_OF_SUPPORTED_IAC)
#define HCI_CMDCODE_READ_CURRENT_IAC_LAP                    HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_CURRENT_IAC_LAP)
#define HCI_CMDCODE_WRITE_CURRENT_IAC_LAP                   HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_CURRENT_IAC_LAP)
#define HCI_CMDCODE_SET_AFH_HOST_CHANNEL_CLASSIFICATION     HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_SET_AFH_HOST_CHANNEL_CLASSIFICATION)
#define HCI_CMDCODE_READ_INQUIRY_SCAN_TYPE                  HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_INQUIRY_SCAN_TYPE)
#define HCI_CMDCODE_WRITE_INQUIRY_SCAN_TYPE                 HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_INQUIRY_SCAN_TYPE)
#define HCI_CMDCODE_READ_INQUIRY_MODE                       HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_INQUIRY_MODE)
#define HCI_CMDCODE_WRITE_INQUIRY_MODE                      HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_INQUIRY_MODE)
#define HCI_CMDCODE_READ_PAGE_SCAN_TYPE                     HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_PAGE_SCAN_TYPE)
#define HCI_CMDCODE_WRITE_PAGE_SCAN_TYPE                    HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_PAGE_SCAN_TYPE)
#define HCI_CMDCODE_READ_AFH_CHANNEL_ASSESSMENT_MODE        HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_AFH_CHANNEL_ASSESSMENT_MODE)
#define HCI_CMDCODE_WRITE_AFH_CHANNEL_ASSESSMENT_MODE       HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_AFH_CHANNEL_ASSESSMENT_MODE)
#define HCI_CMDCODE_READ_EXTENDED_INQUIRY_RESPONSE          HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_EXTENDED_INQUIRY_RESPONSE)
#define HCI_CMDCODE_WRITE_EXTENDED_INQUIRY_RESPONSE         HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_EXTENDED_INQUIRY_RESPONSE)
#define HCI_CMDCODE_REFRESH_ENCRYPTION_KEY                  HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_REFRESH_ENCRYPTION_KEY)
#define HCI_CMDCODE_READ_SIMPLE_PAIRING_MODE                HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_SIMPLE_PAIRING_MODE)
#define HCI_CMDCODE_WRITE_SIMPLE_PAIRING_MODE               HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_SIMPLE_PAIRING_MODE)
#define HCI_CMDCODE_READ_LOCAL_OOB_DATA                     HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_LOCAL_OOB_DATA)
#define HCI_CMDCODE_READ_INQUIRY_RESPONSE_TX_POWER_LEVEL    HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_INQUIRY_RESPONSE_TX_POWER_LEVEL)
#define HCI_CMDCODE_WRITE_INQUIRY_TX_POWER_LEVEL            HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_INQUIRY_TX_POWER_LEVEL)
#define HCI_CMDCODE_READ_DEFAULT_ERRONEOUS_DATA_REPORTING   HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_DEFAULT_ERRONEOUS_DATA_REPORTING)
#define HCI_CMDCODE_WRITE_DEFAULT_ERRONEOUS_DATA_REPORTING  HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_DEFAULT_ERRONEOUS_DATA_REPORTING)
#define HCI_CMDCODE_ENHANCED_FLUSH                          HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_ENHANCED_FLUSH)
#define HCI_CMDCODE_SEND_KEYPRESS_NOTIFICATION              HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_SEND_KEYPRESS_NOTIFICATION)
#define HCI_CMDCODE_READ_LOGICAL_LINK_ACCEPT_TIMEOUT        HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_LOGICAL_LINK_ACCEPT_TIMEOUT)
#define HCI_CMDCODE_WRITE_LOGICAL_LINK_ACCEPT_TIMEOUT       HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_LOGICAL_LINK_ACCEPT_TIMEOUT)
#define HCI_CMDCODE_SET_EVENT_MASK_PAGE_2                   HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_SET_EVENT_MASK_PAGE_2)
#define HCI_CMDCODE_READ_LOCATION_DATA                      HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_LOCATION_DATA)
#define HCI_CMDCODE_WRITE_LOCATION_DATA                     HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_LOCATION_DATA)
#define HCI_CMDCODE_READ_FLOW_CONTROL_MODE                  HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_FLOW_CONTROL_MODE)
#define HCI_CMDCODE_WRITE_FLOW_CONTROL_MODE                 HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_FLOW_CONTROL_MODE)
#define HCI_CMDCODE_READ_ENHANCE_TRANSMIT_POWER_LEVEL       HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_ENHANCE_TRANSMIT_POWER_LEVEL)
#define HCI_CMDCODE_READ_BEST_EFFORT_FLUSH_TIMEOUT          HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_BEST_EFFORT_FLUSH_TIMEOUT)
#define HCI_CMDCODE_WRITE_BEST_EFFORT_FLUSH_TIMEOUT         HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_BEST_EFFORT_FLUSH_TIMEOUT)
#define HCI_CMDCODE_SHORT_RANGE_MODE                        HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_SHORT_RANGE_MODE)
#define HCI_CMDCODE_READ_LE_HOST_SUPPORT                    HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_READ_LE_HOST_SUPPORT)
#define HCI_CMDCODE_WRITE_LE_HOST_SUPPORT                   HCI_COMBINED_OPCODE(HCI_CMD_OGF_CTLR_AND_BB,HCI_CMD_OCF_WRITE_LE_HOST_SUPPORT)

/* HCI Information Parameter Command OpCode */
#define HCI_CMDCODE_READ_LOCAL_VERSION_INFORMATION          HCI_COMBINED_OPCODE(HCI_CMD_OGF_INFO_PARA,HCI_CMD_OCF_READ_LOCAL_VERSION_INFORMATION)
#define HCI_CMDCODE_READ_LOCAL_SUPPORTED_COMMANDS           HCI_COMBINED_OPCODE(HCI_CMD_OGF_INFO_PARA,HCI_CMD_OCF_READ_LOCAL_SUPPORTED_COMMANDS)
#define HCI_CMDCODE_READ_LOCAL_SUPPORTED_FEATURES           HCI_COMBINED_OPCODE(HCI_CMD_OGF_INFO_PARA,HCI_CMD_OCF_READ_LOCAL_SUPPORTED_FEATURES)
#define HCI_CMDCODE_READ_LOCAL_EXTENDED_FEATURES            HCI_COMBINED_OPCODE(HCI_CMD_OGF_INFO_PARA,HCI_CMD_OCF_READ_LOCAL_EXTENDED_FEATURES)
#define HCI_CMDCODE_READ_BUFFER_SIZE                        HCI_COMBINED_OPCODE(HCI_CMD_OGF_INFO_PARA,HCI_CMD_OCF_READ_BUFFER_SIZE)
#define HCI_CMDCODE_READ_BD_ADDR                            HCI_COMBINED_OPCODE(HCI_CMD_OGF_INFO_PARA,HCI_CMD_OCF_READ_BD_ADDR)
#define HCI_CMDCODE_READ_DATE_BLOCK_SIZE                    HCI_COMBINED_OPCODE(HCI_CMD_OGF_INFO_PARA,HCI_CMD_OCF_READ_DATE_BLOCK_SIZE)

/* HCI Status Parameter Command OpCode */
#define HCI_CMDCODE_READ_FAILED_CONTACT_COUNTER             HCI_COMBINED_OPCODE(HCI_CMD_OGF_STATUS_PARA,HCI_CMD_OCF_READ_FAILED_CONTACT_COUNTER)
#define HCI_CMDCODE_RESET_FAILED_CONTACT_COUNTER            HCI_COMBINED_OPCODE(HCI_CMD_OGF_STATUS_PARA,HCI_CMD_OCF_RESET_FAILED_CONTACT_COUNTER)
#define HCI_CMDCODE_READ_LINK_QUALITY                       HCI_COMBINED_OPCODE(HCI_CMD_OGF_STATUS_PARA,HCI_CMD_OCF_READ_LINK_QUALITY)
#define HCI_CMDCODE_READ_RSSI                               HCI_COMBINED_OPCODE(HCI_CMD_OGF_STATUS_PARA,HCI_CMD_OCF_READ_RSSI)
#define HCI_CMDCODE_READ_AFH_CHANNEL_MAP                    HCI_COMBINED_OPCODE(HCI_CMD_OGF_STATUS_PARA,HCI_CMD_OCF_READ_AFH_CHANNEL_MAP)
#define HCI_CMDCODE_READ_CLOCK                              HCI_COMBINED_OPCODE(HCI_CMD_OGF_STATUS_PARA,HCI_CMD_OCF_READ_CLOCK)
#define HCI_CMDCODE_READ_ENCRYPTION_KEY_SIZE                HCI_COMBINED_OPCODE(HCI_CMD_OGF_STATUS_PARA,HCI_CMD_OCF_READ_ENCRYPTION_KEY_SIZE)
#define HCI_CMDCODE_READ_LOCAL_AMP_INFO                     HCI_COMBINED_OPCODE(HCI_CMD_OGF_STATUS_PARA,HCI_CMD_OCF_READ_LOCAL_AMP_INFO)
#define HCI_CMDCODE_READ_LOCAL_AMP_ASSOC                    HCI_COMBINED_OPCODE(HCI_CMD_OGF_STATUS_PARA,HCI_CMD_OCF_READ_LOCAL_AMP_ASSOC)
#define HCI_CMDCODE_WRITE_REMOTE_AMP_ASSOC                  HCI_COMBINED_OPCODE(HCI_CMD_OGF_STATUS_PARA,HCI_CMD_OCF_WRITE_REMOTE_AMP_ASSOC)

/* HCI Test Command OpCode */
#define HCI_CMDCODE_READ_LOOPBACK_MODE                      HCI_COMBINED_OPCODE(HCI_CMD_OGF_TEST,HCI_CMD_OCF_READ_LOOPBACK_MODE)
#define HCI_CMDCODE_WRITE_LOOPBACK_MODE                     HCI_COMBINED_OPCODE(HCI_CMD_OGF_TEST,HCI_CMD_OCF_WRITE_LOOPBACK_MODE)
#define HCI_CMDCODE_ENABLE_DEVICE_UNDER_TEST_MODE           HCI_COMBINED_OPCODE(HCI_CMD_OGF_TEST,HCI_CMD_OCF_ENABLE_DEVICE_UNDER_TEST_MODE)
#define HCI_CMDCODE_WRITE_SIMPLE_PAIRING_DEBUG_MODE         HCI_COMBINED_OPCODE(HCI_CMD_OGF_TEST,HCI_CMD_OCF_WRITE_SIMPLE_PAIRING_DEBUG_MODE)
#define HCI_CMDCODE_ENABLE_AMP_RECEIVER_REPORTS             HCI_COMBINED_OPCODE(HCI_CMD_OGF_TEST,HCI_CMD_OCF_ENABLE_AMP_RECEIVER_REPORTS)
#define HCI_CMDCODE_AMP_TEST_END                            HCI_COMBINED_OPCODE(HCI_CMD_OGF_TEST,HCI_CMD_OCF_AMP_TEST_END)
#define HCI_CMDCODE_AMP_TEST                                HCI_COMBINED_OPCODE(HCI_CMD_OGF_TEST,HCI_CMD_OCF_AMP_TEST)

/* HCI LC Controller Command OpCode */
#define HCI_CMDCODE_LE_SET_EVENT_MASK                           HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_SET_EVENT_MASK)
#define HCI_CMDCODE_LE_READ_BUFFER_SIZE                         HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_READ_BUFFER_SIZE)
#define HCI_CMDCODE_LE_READ_LOCAL_SUPPORTED_FEATURES            HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_READ_LOCAL_SUPPORTED_FEATURES)
#define HCI_CMDCODE_LE_SET_RANDOM_ADDRESS                       HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_SET_RANDOM_ADDRESS)
#define HCI_CMDCODE_LE_SET_ADVERTISING_PARAMETER                HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_SET_ADVERTISING_PARAMETER)
#define HCI_CMDCODE_LE_READ_ADVERTISING_CHANNEL_TX_POWER        HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_READ_ADVERTISING_CHANNEL_TX_POWER)
#define HCI_CMDCODE_LE_SET_ADVERTISING_DATA                     HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_ADVERTISING_DATA)
#define HCI_CMDCODE_LE_SET_SCAN_RESPONSE_DATA                   HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_SET_SCAN_RESPONSE_DATA)
#define HCI_CMDCODE_LE_SET_ADVERTISING_ENABLE                   HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_SET_ADVERTISING_ENABLE)
#define HCI_CMDCODE_LE_SET_SCAN_PARAMETERS                      HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_SET_SCAN_PARAMETERS)
#define HCI_CMDCODE_LE_SET_SCAN_ENABLE                          HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_SET_SCAN_ENABLE)
#define HCI_CMDCODE_LE_CREATE_CONNECTION                        HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_CREATE_CONNECTION)
#define HCI_CMDCODE_LE_CREATE_CONNECTION_CANCEL                 HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_CREATE_CONNECTION_CANCEL)
#define HCI_CMDCODE_LE_READ_WHITE_LIST_SIZE                     HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_READ_WHITE_LIST_SIZE)
#define HCI_CMDCODE_LE_CLEAR_WHITE_LIST                         HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_CLEAR_WHITE_LIST)
#define HCI_CMDCODE_LE_ADD_DEVICE_TO_WHITE_LIST                 HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_ADD_DEVICE_TO_WHITE_LIST)
#define HCI_CMDCODE_LE_REMOVE_DEVICE_FROM_WHITE_LIST            HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_REMOVE_DEVICE_FROM_WHITE_LIST)
#define HCI_CMDCODE_LE_CONNECTION_UPDATE                        HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_CONNECTION_UPDATE)
#define HCI_CMDCODE_LE_SET_HOST_CHANNEL_CLASSIFICATION          HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_SET_HOST_CHANNEL_CLASSIFICATION)
#define HCI_CMDCODE_LE_READ_CHANNEL_MAP                         HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_READ_CHANNEL_MAP)
#define HCI_CMDCODE_LE_READ_REMOTE_USED_FEATURES                HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_READ_REMOTE_USED_FEATURES)
#define HCI_CMDCODE_LE_ENCRYPT                                  HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_ENCRYPT)
#define HCI_CMDCODE_LE_RAND                                     HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_RAND)
#define HCI_CMDCODE_LE_START_ENCRYPTION                         HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_START_ENCRYPTION)
#define HCI_CMDCODE_LE_LONG_TERM_KEY_REQUEST_REPLY              HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_LONG_TERM_KEY_REQUEST_REPLY)
#define HCI_CMDCODE_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY     HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY)
#define HCI_CMDCODE_LE_READ_SUPPORTED_STATES                    HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_READ_SUPPORTED_STATES)
#define HCI_CMDCODE_LE_RECEIVER_TEST                            HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_RECEIVER_TEST)
#define HCI_CMDCODE_LE_TRANSMITTER_TEST                         HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_TRANSMITTER_TEST)
#define HCI_CMDCODE_LE_TEST_END                                 HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_TEST_END)
#define HCI_CMDCODE_LE_REMOTE_CONNECTION_PARAM_REQ_REPLY        HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_REMOTE_CONNECTION_PARAM_REQ_REPLY)
#define HCI_CMDCODE_LE_REMOTE_CONNECTION_PARAM_REQ_NEG_REPLY    HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_REMOTE_CONNECTION_PARAM_REQ_NEG_REPLY)
#define HCI_CMDCODE_LE_READ_LOCAL_P256_PUBLIC_KEY               HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_READ_LOCAL_P256_PUBLIC_KEY)
#define HCI_CMDCODE_LE_GENERATE_DHKEY                           HCI_COMBINED_OPCODE(HCI_CMD_OGF_LE_CTLR,HCI_CMD_OCF_LE_GENERATE_DHKEY)

/* HCI SDK Command OpCode */
#define HCI_CMDCODE_SDK_SET_PUB_ADDRESS                         HCI_COMBINED_OPCODE(HCI_CMD_OGF_SDK_SPECIFIC, HCI_CMD_OCF_CHIP_SET_PUB_ADDRESS)
#define HCI_CMDCODE_SDK_SET_TX_POWER                            HCI_COMBINED_OPCODE(HCI_CMD_OGF_SDK_SPECIFIC, HCI_CMD_OCF_CHIP_SET_TX_POWER)
#define HCI_CMDCODE_SDK_GET_PUB_ADDRESS                         HCI_COMBINED_OPCODE(HCI_CMD_OGF_SDK_SPECIFIC, HCI_CMD_OCF_CHIP_GET_PUB_ADDRESS)
#define HCI_CMDCODE_SDK_READ_SFR                                HCI_COMBINED_OPCODE(HCI_CMD_OGF_SDK_SPECIFIC, HCI_CMD_OCF_CHIP_READ_SFR)
#define HCI_CMDCODE_SDK_SET_DISABLE_LATENCY                     HCI_COMBINED_OPCODE(HCI_CMD_OGF_SDK_SPECIFIC, HCI_CMD_OCF_CHIP_SET_DISABLE_LAENCY)

/* The follow Command OpCodes are AIROHA proprietory */



/*
 * HCI Event Code
 */
//- HCI Event OP code;
typedef uint8_t HCI_EVTCODE;
#define HCI_EVENT_INQUIRY_COMPLETE                                  ((HCI_EVTCODE)0x01)
#define HCI_EVENT_INQUIRY_RESULT                                    ((HCI_EVTCODE)0x02)
#define HCI_EVENT_CONNECTION_COMPLETE                               ((HCI_EVTCODE)0x03)
#define HCI_EVENT_CONNECTION_REQUEST                                ((HCI_EVTCODE)0x04)
#define HCI_EVENT_DISCONNECTION_COMPLETE                            ((HCI_EVTCODE)0x05)
#define HCI_EVENT_AUTHENTICATION_COMPLETE                           ((HCI_EVTCODE)0x06)
#define HCI_EVENT_REMOTE_NAME_REQUEST_COMPLETE                      ((HCI_EVTCODE)0x07)
#define HCI_EVENT_ENCRYPTION_CHANGE                                 ((HCI_EVTCODE)0x08)
#define HCI_EVENT_CHANGE_CONNECTION_LINK_KEY_COMPLETE               ((HCI_EVTCODE)0x09)
#define HCI_EVENT_MASTER_LINK_KEY_COMPLETE                          ((HCI_EVTCODE)0x0A)
#define HCI_EVENT_READ_REMOTE_SUPPORTED_FEATURES_COMPLETE           ((HCI_EVTCODE)0x0B)
#define HCI_EVENT_READ_REMOTE_VERSION_INFORMATION_COMPLETE          ((HCI_EVTCODE)0x0C)
#define HCI_EVENT_QOS_SETUP_COMPLETE                                ((HCI_EVTCODE)0x0D)
#define HCI_EVENT_COMMAND_COMPLETE                                  ((HCI_EVTCODE)0x0E)
#define HCI_EVENT_COMMAND_STATUS                                    ((HCI_EVTCODE)0x0F)
#define HCI_EVENT_HARDWARE_ERROR                                    ((HCI_EVTCODE)0x10)
#define HCI_EVENT_FLUSH_OCCURRED                                    ((HCI_EVTCODE)0x11)
#define HCI_EVENT_ROLE_CHANGE                                       ((HCI_EVTCODE)0x12)
#define HCI_EVENT_NUMBER_OF_COMPLETED_PACKETS                       ((HCI_EVTCODE)0x13)
#define HCI_EVENT_MODE_CHANGE                                       ((HCI_EVTCODE)0x14)
#define HCI_EVENT_RETURN_LINK_KEYS                                  ((HCI_EVTCODE)0x15)
#define HCI_EVENT_PIN_CODE_REQUEST                                  ((HCI_EVTCODE)0x16)
#define HCI_EVENT_LINK_KEY_REQUEST                                  ((HCI_EVTCODE)0x17)
#define HCI_EVENT_LINK_KEY_NOTIFICATION                             ((HCI_EVTCODE)0x18)
#define HCI_EVENT_LOOPBACK_COMMAND                                  ((HCI_EVTCODE)0x19)
#define HCI_EVENT_DATA_BUFFER_OVERFLOW                              ((HCI_EVTCODE)0x1A)
#define HCI_EVENT_MAX_SLOTS_CHANGE                                  ((HCI_EVTCODE)0x1B)
#define HCI_EVENT_READ_CLOCK_OFFSET_COMPLETE                        ((HCI_EVTCODE)0x1C)
#define HCI_EVENT_CONNECTION_PACKET_TYPE_CHANGED                    ((HCI_EVTCODE)0x1D)
#define HCI_EVENT_QOS_VIOLATION                                     ((HCI_EVTCODE)0x1E)
//Not Defined                                                       ((HCI_EVTCODE)0x1F)
#define HCI_EVENT_PAGE_SCAN_REPETITION_MODE_CHANGE                  ((HCI_EVTCODE)0x20)
#define HCI_EVENT_HCI_FLOW_SPECIFICATION_COMPLETE                   ((HCI_EVTCODE)0x21)
#define HCI_EVENT_INQUIRY_RESULT_WITH_RSSI                          ((HCI_EVTCODE)0x22)
#define HCI_EVENT_READ_REMOTE_EXTENDED_FEATURES_COMPLETE            ((HCI_EVTCODE)0x23)
#define HCI_EVENT_SYNCHRONOUS_CONNECTION_COMPLETE                   ((HCI_EVTCODE)0x2C)
#define HCI_EVENT_SYNCHRONOUS_CONNECTION_CHANGED                    ((HCI_EVTCODE)0x2D)
#define HCI_EVENT_SNIFF_SUBRATING                                   ((HCI_EVTCODE)0x2E)
#define HCI_EVENT_EXTENDED_INQUIRY_RESULT                           ((HCI_EVTCODE)0x2F)
#define HCI_EVENT_ENCRYPTION_KEY_REFRESH_COMPLETE                   ((HCI_EVTCODE)0x30)
#define HCI_EVENT_IO_CAPABILITY_REQUEST                             ((HCI_EVTCODE)0x31)
#define HCI_EVENT_IO_CAPABILITY_RESPONSE                            ((HCI_EVTCODE)0x32)
#define HCI_EVENT_USER_CONFIRMATION_REQUEST                         ((HCI_EVTCODE)0x33)
#define HCI_EVENT_PASSKEY_REQUEST                                   ((HCI_EVTCODE)0x34)
#define HCI_EVENT_REMOTE_OOB_DATA_REQUEST                           ((HCI_EVTCODE)0x35)
#define HCI_EVENT_SIMPLE_PAIRING_COMPLETE                           ((HCI_EVTCODE)0x36)
#define HCI_EVENT_LINK_SUPERVISION_TIMEOUT_CHANGED                  ((HCI_EVTCODE)0x38)
#define HCI_EVENT_ENHANCED_FLUSH_COMPLETE                           ((HCI_EVTCODE)0x39)
#define HCI_EVENT_USER_PASSKEY_NOTIFICATION                         ((HCI_EVTCODE)0x3B)
#define HCI_EVENT_KEYPRESS_NOTIFICATION                             ((HCI_EVTCODE)0x3C)
#define HCI_EVENT_REMOTE_HOST_SUPPORTED_FEATURES_NOTI               ((HCI_EVTCODE)0x3D)
#define HCI_EVENT_LE_META                                           ((HCI_EVTCODE)0x3E)

//- LE Meta Event
#define HCI_EVENT_LE_CONNECTION_COMPLETE                            ((HCI_EVTCODE)0x01)
#define HCI_EVENT_LE_ADVERTISING_REPORT                             ((HCI_EVTCODE)0x02)
#define HCI_EVENT_LE_CONNECTION_UPDATE_COMPLETE                     ((HCI_EVTCODE)0x03)
#define HCI_EVENT_LE_READ_REMOTE_USED_FEATURES_COMPLETE             ((HCI_EVTCODE)0x04)
#define HCI_EVENT_LE_LONG_TERM_KEY_REQUEST                          ((HCI_EVTCODE)0x05)
#define HCI_EVENT_LE_REMOTE_CONNECTION_PARAMETER_REQUEST            ((HCI_EVTCODE)0x06)
#define HCI_EVENT_LE_READ_LOCAL_P256_PUBLIC_KEY_COMPLETE            ((HCI_EVTCODE)0x08)
#define HCI_EVENT_LE_GENERATE_DHKEY_COMPLETE                        ((HCI_EVTCODE)0x09)

/*
 * HCI Error Code
 */
typedef uint8_t HCI_ERRCODE;

/* HCI Error Code */
#define HCI_ERRCODE_SUCCESS                                                     (HCI_ERRCODE)0x00
#define HCI_ERRCODE_UNKNOWN_HCI_COMMAND                                         (HCI_ERRCODE)0x01
#define HCI_ERRCODE_UNKNOWN_CONNECTION_IDENTIFIER                               (HCI_ERRCODE)0x02
#define HCI_ERRCODE_HARDWARE_FAILURE                                            (HCI_ERRCODE)0x03
#define HCI_ERRCODE_PAGE_TIMEOUT                                                (HCI_ERRCODE)0x04
#define HCI_ERRCODE_AUTHENTICATION_FAILURE                                      (HCI_ERRCODE)0x05
#define HCI_ERRCODE_PIN_OR_KEY_MISSING                                          (HCI_ERRCODE)0x06
#define HCI_ERRCODE_MEMORY_CAPACITY_EXCEEDED                                    (HCI_ERRCODE)0x07
#define HCI_ERRCODE_CONNECTION_TIMEOUT                                          (HCI_ERRCODE)0x08
#define HCI_ERRCODE_CONNECTION_LIMIT_EXCEEDED                                   (HCI_ERRCODE)0x09
#define HCI_ERRCODE_SYNCHRONOUS_CONNECTION_LIMIT_TO_A_DEVICE_EXCEEDED           (HCI_ERRCODE)0x0A
#define HCI_ERRCODE_ACL_CONNECTION_ALREADY_EXISTS                               (HCI_ERRCODE)0x0B
#define HCI_ERRCODE_COMMAND_DISALLOWED                                          (HCI_ERRCODE)0x0C
#define HCI_ERRCODE_CONNECTION_REJECTED_DUE_TO_LIMITED_RESOURCES                (HCI_ERRCODE)0x0D
#define HCI_ERRCODE_CONNECTION_REJECTED_DUE_TO_SECURITY_REASONS                 (HCI_ERRCODE)0x0E
#define HCI_ERRCODE_CONNECTION_REJECTED_DUE_TO_UNACCEPTABLE_BD_ADDR             (HCI_ERRCODE)0x0F
#define HCI_ERRCODE_CONNECTION_ACCEPT_TIMEOUT_EXCEEDED                          (HCI_ERRCODE)0x10
#define HCI_ERRCODE_UNSUPPORTED_FEATURE_OR_PARAMETER_VALUE                      (HCI_ERRCODE)0x11
#define HCI_ERRCODE_INVALID_HCI_COMMAND_PARAMETERS                              (HCI_ERRCODE)0x12
#define HCI_ERRCODE_REMOTE_USER_TERMINATED_CONNECTION                           (HCI_ERRCODE)0x13
#define HCI_ERRCODE_REMOTE_DEVICE_TERMINATED_CONNECTION_DUE_TO_LOW_RESOURCES    (HCI_ERRCODE)0x14
#define HCI_ERRCODE_REMOTE_DEVICE_TERMINATED_CONNECTION_DUE_TO_POWER_OFF        (HCI_ERRCODE)0x15
#define HCI_ERRCODE_CONNECTION_TERMINATED_BY_LOCAL_HOST                         (HCI_ERRCODE)0x16
#define HCI_ERRCODE_REPEATED_ATTEMPTS                                           (HCI_ERRCODE)0x17
#define HCI_ERRCODE_PAIRING_NOT_ALLOWED                                         (HCI_ERRCODE)0x18
#define HCI_ERRCODE_UNKNOWN_LMP_PDU                                             (HCI_ERRCODE)0x19
#define HCI_ERRCODE_UNSUPPORTED_REMOTE_FEATURE_UNSUPPORTED_LMP_FEATURE          (HCI_ERRCODE)0x1A
#define HCI_ERRCODE_SCO_OFFSET_REJECTED                                         (HCI_ERRCODE)0x1B
#define HCI_ERRCODE_SCO_INTERVAL_REJECTED                                       (HCI_ERRCODE)0x1C
#define HCI_ERRCODE_SCO_AIR_MODE_REJECTED                                       (HCI_ERRCODE)0x1D
#define HCI_ERRCODE_INVALID_LMP_PARAMETERS                                      (HCI_ERRCODE)0x1E
#define HCI_ERRCODE_UNSPECIFIED_ERROR                                           (HCI_ERRCODE)0x1F
#define HCI_ERRCODE_UNSUPPORTED_LMP_PARAMETER_VALUE                             (HCI_ERRCODE)0x20
#define HCI_ERRCODE_ROLE_CHANGE_NOT_ALLOWED                                     (HCI_ERRCODE)0x21
#define HCI_ERRCODE_LMP_RESPONSE_TIMEOUT                                        (HCI_ERRCODE)0x22
#define HCI_ERRCODE_LMP_ERROR_TRANSACTION_COLLISION                             (HCI_ERRCODE)0x23
#define HCI_ERRCODE_LMP_PDU_NOT_ALLOWED                                         (HCI_ERRCODE)0x24
#define HCI_ERRCODE_ENCRYPTION_MODE_NOT_ACCEPTABLE                              (HCI_ERRCODE)0x25
#define HCI_ERRCODE_LINK_KEY_CAN_NOT_BE_CHANGED                                 (HCI_ERRCODE)0x26
#define HCI_ERRCODE_REQUESTED_QOS_NOT_SUPPORTED                                 (HCI_ERRCODE)0x27
#define HCI_ERRCODE_INSTANT_PASSED                                              (HCI_ERRCODE)0x28
#define HCI_ERRCODE_PAIRING_WITH_UNIT_KEY_NOT_SUPPORTED                         (HCI_ERRCODE)0x29
#define HCI_ERRCODE_DIFFERENT_TRANSACTION_COLLISION                             (HCI_ERRCODE)0x2A
#define HCI_ERRCODE_QOS_UNACCEPTABLE_PARAMETER                                  (HCI_ERRCODE)0x2C
#define HCI_ERRCODE_QOS_REJECTED                                                (HCI_ERRCODE)0x2D
#define HCI_ERRCODE_CHANNEL_CLASSIFICATION_NOT_SUPPORTED                        (HCI_ERRCODE)0x2E
#define HCI_ERRCODE_INSUFFICIENT_SECURITY                                       (HCI_ERRCODE)0x2F
#define HCI_ERRCODE_PARAMETER_OUT_OF_MANDATORY_RANGE                            (HCI_ERRCODE)0x30
#define HCI_ERRCODE_ROLE_SWITCH_PENDING                                         (HCI_ERRCODE)0x32
#define HCI_ERRCODE_RESERVED_SLOT_VIOLATION                                     (HCI_ERRCODE)0x34
#define HCI_ERRCODE_ROLE_SWITCH_FAILED                                          (HCI_ERRCODE)0x35
#define HCI_ERRCODE_EXTENDED_INQUIRY_RESPONSE_TOOL_LARGE                        (HCI_ERRCODE)0x36
#define HCI_ERRCODE_SIMPLE_PAIRING_NOT_SUPPORTED_BY_HOST                        (HCI_ERRCODE)0x37
#define HCI_ERRCODE_HOST_BUSY_PAIRING                                           (HCI_ERRCODE)0x38
#define HCI_ERRCODE_DIRECTED_ADVERTISING_TIMEOUT                                (HCI_ERRCODE)0x3C
#define HCI_ERRCODE_CONN_TERMINATED_DUE_TO_MIC_FAILURE                          (HCI_ERRCODE)0x3D
#define HCI_ERRCODE_CONNECTION_FAILED_TO_BE_ESTABLISHED                         (HCI_ERRCODE)0x3E

#ifdef _MSC_VER
__pragma(pack(push, 1))
#define __attribute__(x)
#endif


/* HC CMD Header */
typedef struct stru_hci_cmd_opcode
{
    uint16_t OCF : 10;
    uint16_t OGF :  6;
}__attribute__((packed))HCI_CMD_OPCODE_STRU;

typedef union union_hci_cmd_opcode
{
    uint16_t value;
    HCI_CMD_OPCODE_STRU field;
}__attribute__((packed))HCI_CMD_OPCODE_UNION;

/* HCI Command Header Format */
typedef struct stru_hci_cmd_hdr
{
    HCI_CMD_OPCODE_UNION OpCode;
    uint8_t Len;
}__attribute__((packed))HCI_CMD_HDR_STRU;

/* HCI Event Header Format */
typedef struct stru_hci_event_hdr
{
    uint8_t EvtCode;
    uint8_t Len;
} __attribute__((packed))HCI_EVT_HDR_STRU;

#ifdef _MSC_VER
__pragma(pack(pop))
#undef __attribute__
#endif


#define HCI_PB_L2CAP_START_NON_AUTO						(0x00)
#define HCI_PB_L2CAP_START								(0x02)
#define HCI_PB_L2CAP_CONTINUE							(0x01)

#define HCI_BC_NOB										(0x00)
#define HCI_BC_ASB										(0x01)
#define HCI_BC_PSB										(0x02)

#endif /* _HCI_H_ */

