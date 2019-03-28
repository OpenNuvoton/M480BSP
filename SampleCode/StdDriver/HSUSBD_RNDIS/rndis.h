/***************************************************************************//**
 * @file     rndis.h
 * @brief    M480 series USB driver header file
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef __RNDIS_H__
#define __RNDIS_H__

/* Define the vendor id and product id */
#define USBD_VID        0x0416
#define USBD_PID        0xB055

/*!<Define CDC Class Specific Request */
#define SEND_ENCAPSULATED_COMMAND   0x00
#define GET_ENCAPSULATED_RESPONSE   0x01

/* Define DMA Maximum Transfer length */
#define USBD_MAX_DMA_LEN    0x1000

/*-------------------------------------------------------------*/
/* Define EP maximum packet size */
#define CEP_MAX_PKT_SIZE        64
#define CEP_OTHER_MAX_PKT_SIZE  64
#define EPA_MAX_PKT_SIZE        512
#define EPA_OTHER_MAX_PKT_SIZE  64
#define EPB_MAX_PKT_SIZE        512
#define EPB_OTHER_MAX_PKT_SIZE  64
#define EPC_MAX_PKT_SIZE        8
#define EPC_OTHER_MAX_PKT_SIZE  8

#define CEP_BUF_BASE    0
#define CEP_BUF_LEN     CEP_MAX_PKT_SIZE
#define EPA_BUF_BASE    0x200
#define EPA_BUF_LEN     EPA_MAX_PKT_SIZE
#define EPB_BUF_BASE    0x400
#define EPB_BUF_LEN     EPB_MAX_PKT_SIZE
#define EPC_BUF_BASE    0x100
#define EPC_BUF_LEN     EPC_MAX_PKT_SIZE

/* Define the interrupt In EP number */
#define BULK_IN_EP_NUM      0x01
#define BULK_OUT_EP_NUM     0x02
#define INT_IN_EP_NUM       0x03

/* Define Descriptor information */
#define USBD_SELF_POWERED               0
#define USBD_REMOTE_WAKEUP              0
#define USBD_MAX_POWER                  50  /* The unit is in 2mA. ex: 50 * 2mA = 100mA */

/*-------------------------------------------------------------*/
/* RNDIS message types */
#define REMOTE_NDIS_PACKET_MSG          0x00000001
#define REMOTE_NDIS_INITIALIZE_MSG      0x00000002
#define REMOTE_NDIS_INITIALIZE_CMPLT    0x80000002
#define REMOTE_NDIS_HALT_MSG            0x00000003
#define REMOTE_NDIS_QUERY_MSG           0x00000004
#define REMOTE_NDIS_QUERY_CMPLT         0x80000004
#define REMOTE_NDIS_SET_MSG             0x00000005
#define REMOTE_NDIS_SET_CMPLT           0x80000005
#define REMOTE_NDIS_RESET_MSG           0x00000006
#define REMOTE_NDIS_RESET_CMPLT         0x80000006
#define REMOTE_NDIS_INDICATE_STATUS_MSG 0x00000007
#define REMOTE_NDIS_KEEPALIVE_MSG       0x00000008
#define REMOTE_NDIS_KEEPALIVE_CMPLT     0x80000008

/* Status values in RNDIS messages */
#define RNDIS_STATUS_SUCCESS            0x00000000
#define RNDIS_STATUS_FAILURE            0xC0000001
#define RNDIS_STATUS_INVALID_DATA       0xC0010015
#define RNDIS_STATUS_NOT_SUPPORTED      0xC00000BB
#define RNDIS_STATUS_MEDIA_CONNECT      0x4001000B
#define RNDIS_STATUS_MEDIA_DISCONNECT   0x4001000C

/* Required Object IDs (OIDs) */
#define OID_GEN_SUPPORTED_LIST            0x00010101
#define OID_GEN_HARDWARE_STATUS           0x00010102
#define OID_GEN_MEDIA_SUPPORTED           0x00010103
#define OID_GEN_MEDIA_IN_USE              0x00010104
#define OID_GEN_MAXIMUM_FRAME_SIZE        0x00010106
#define OID_GEN_LINK_SPEED                0x00010107
#define OID_GEN_TRANSMIT_BLOCK_SIZE       0x0001010A
#define OID_GEN_RECEIVE_BLOCK_SIZE        0x0001010B
#define OID_GEN_VENDOR_ID                 0x0001010C
#define OID_GEN_VENDOR_DESCRIPTION        0x0001010D
#define OID_GEN_CURRENT_PACKET_FILTER     0x0001010E
#define OID_GEN_CURRENT_LOOKAHEAD         0x0001010F
#define OID_GEN_DRIVER_VERSION            0x00010110
#define OID_GEN_MAXIMUM_TOTAL_SIZE        0x00010111
#define OID_GEN_PROTOCOL_OPTIONS          0x00010112
#define OID_GEN_MAC_OPTIONS               0x00010113
#define OID_GEN_MEDIA_CONNECT_STATUS      0x00010114
#define OID_GEN_MAXIMUM_SEND_PACKETS      0x00010115
#define OID_GEN_VENDOR_DRIVER_VERSION     0x00010116
#define OID_GEN_SUPPORTED_GUIDS           0x00010117
#define OID_GEN_NETWORK_LAYER_ADDRESSES   0x00010118
#define OID_GEN_TRANSPORT_HEADER_OFFSET   0x00010119
#define OID_GEN_MACHINE_NAME              0x0001021A
#define OID_GEN_RNDIS_CONFIG_PARAMETER    0x0001021B
#define OID_GEN_VLAN_ID                   0x0001021C

/* Optional OIDs */
#define OID_GEN_MEDIA_CAPABILITIES        0x00010201
#define OID_GEN_PHYSICAL_MEDIUM           0x00010202

/* Required statistics OIDs */
#define OID_GEN_XMIT_OK                   0x00020101
#define OID_GEN_RCV_OK                    0x00020102
#define OID_GEN_XMIT_ERROR                0x00020103
#define OID_GEN_RCV_ERROR                 0x00020104
#define OID_GEN_RCV_NO_BUFFER             0x00020105

/* Optional statistics OIDs */
#define OID_GEN_DIRECTED_BYTES_XMIT       0x00020201
#define OID_GEN_DIRECTED_FRAMES_XMIT      0x00020202
#define OID_GEN_MULTICAST_BYTES_XMIT      0x00020203
#define OID_GEN_MULTICAST_FRAMES_XMIT     0x00020204
#define OID_GEN_BROADCAST_BYTES_XMIT      0x00020205
#define OID_GEN_BROADCAST_FRAMES_XMIT     0x00020206
#define OID_GEN_DIRECTED_BYTES_RCV        0x00020207
#define OID_GEN_DIRECTED_FRAMES_RCV       0x00020208
#define OID_GEN_MULTICAST_BYTES_RCV       0x00020209
#define OID_GEN_MULTICAST_FRAMES_RCV      0x0002020A
#define OID_GEN_BROADCAST_BYTES_RCV       0x0002020B
#define OID_GEN_BROADCAST_FRAMES_RCV      0x0002020C
#define OID_GEN_RCV_CRC_ERROR             0x0002020D
#define OID_GEN_TRANSMIT_QUEUE_LENGTH     0x0002020E
#define OID_GEN_GET_TIME_CAPS             0x0002020F
#define OID_GEN_GET_NETCARD_TIME          0x00020210
#define OID_GEN_NETCARD_LOAD              0x00020211
#define OID_GEN_DEVICE_PROFILE            0x00020212
#define OID_GEN_INIT_TIME_MS              0x00020213
#define OID_GEN_RESET_COUNTS              0x00020214
#define OID_GEN_MEDIA_SENSE_COUNTS        0x00020215
#define OID_GEN_FRIENDLY_NAME             0x00020216
#define OID_GEN_MINIPORT_INFO             0x00020217
#define OID_GEN_RESET_VERIFY_PARAMETERS   0x00020218



/* IEEE 802.3 (Ethernet) OIDs */
#define NDIS_802_3_MAC_OPTION_PRIORITY    0x00000001

#define OID_802_3_PERMANENT_ADDRESS       0x01010101
#define OID_802_3_CURRENT_ADDRESS         0x01010102
#define OID_802_3_MULTICAST_LIST          0x01010103
#define OID_802_3_MAXIMUM_LIST_SIZE       0x01010104
#define OID_802_3_MAC_OPTIONS             0x01010105
#define OID_802_3_RCV_ERROR_ALIGNMENT     0x01020101
#define OID_802_3_XMIT_ONE_COLLISION      0x01020102
#define OID_802_3_XMIT_MORE_COLLISIONS    0x01020103
#define OID_802_3_XMIT_DEFERRED           0x01020201
#define OID_802_3_XMIT_MAX_COLLISIONS     0x01020202
#define OID_802_3_RCV_OVERRUN             0x01020203
#define OID_802_3_XMIT_UNDERRUN           0x01020204
#define OID_802_3_XMIT_HEARTBEAT_FAILURE  0x01020205
#define OID_802_3_XMIT_TIMES_CRS_LOST     0x01020206
#define OID_802_3_XMIT_LATE_COLLISIONS    0x01020207


/* OID_GEN_MINIPORT_INFO constants */
#define NDIS_MINIPORT_BUS_MASTER                      0x00000001
#define NDIS_MINIPORT_WDM_DRIVER                      0x00000002
#define NDIS_MINIPORT_SG_LIST                         0x00000004
#define NDIS_MINIPORT_SUPPORTS_MEDIA_QUERY            0x00000008
#define NDIS_MINIPORT_INDICATES_PACKETS               0x00000010
#define NDIS_MINIPORT_IGNORE_PACKET_QUEUE             0x00000020
#define NDIS_MINIPORT_IGNORE_REQUEST_QUEUE            0x00000040
#define NDIS_MINIPORT_IGNORE_TOKEN_RING_ERRORS        0x00000080
#define NDIS_MINIPORT_INTERMEDIATE_DRIVER             0x00000100
#define NDIS_MINIPORT_IS_NDIS_5                       0x00000200
#define NDIS_MINIPORT_IS_CO                           0x00000400
#define NDIS_MINIPORT_DESERIALIZE                     0x00000800
#define NDIS_MINIPORT_REQUIRES_MEDIA_POLLING          0x00001000
#define NDIS_MINIPORT_SUPPORTS_MEDIA_SENSE            0x00002000
#define NDIS_MINIPORT_NETBOOT_CARD                    0x00004000
#define NDIS_MINIPORT_PM_SUPPORTED                    0x00008000
#define NDIS_MINIPORT_SUPPORTS_MAC_ADDRESS_OVERWRITE  0x00010000
#define NDIS_MINIPORT_USES_SAFE_BUFFER_APIS           0x00020000
#define NDIS_MINIPORT_HIDDEN                          0x00040000
#define NDIS_MINIPORT_SWENUM                          0x00080000
#define NDIS_MINIPORT_SURPRISE_REMOVE_OK              0x00100000
#define NDIS_MINIPORT_NO_HALT_ON_SUSPEND              0x00200000
#define NDIS_MINIPORT_HARDWARE_DEVICE                 0x00400000
#define NDIS_MINIPORT_SUPPORTS_CANCEL_SEND_PACKETS    0x00800000
#define NDIS_MINIPORT_64BITS_DMA                      0x01000000

#define NDIS_MEDIUM_802_3                             0x00000000
#define NDIS_MEDIUM_802_5                             0x00000001
#define NDIS_MEDIUM_FDDI                              0x00000002
#define NDIS_MEDIUM_WAN                               0x00000003
#define NDIS_MEDIUM_LOCAL_TALK                        0x00000004
#define NDIS_MEDIUM_DIX                               0x00000005
#define NDIS_MEDIUM_ARCENT_RAW                        0x00000006
#define NDIS_MEDIUM_ARCENT_878_2                      0x00000007
#define NDIS_MEDIUM_ATM                               0x00000008
#define NDIS_MEDIUM_WIRELESS_LAN                      0x00000009
#define NDIS_MEDIUM_IRDA                              0x0000000A
#define NDIS_MEDIUM_BPC                               0x0000000B
#define NDIS_MEDIUM_CO_WAN                            0x0000000C
#define NDIS_MEDIUM_1394                              0x0000000D

#define NDIS_PACKET_TYPE_DIRECTED                     0x00000001
#define NDIS_PACKET_TYPE_MULTICAST                    0x00000002
#define NDIS_PACKET_TYPE_ALL_MULTICAST                0x00000004
#define NDIS_PACKET_TYPE_BROADCAST                    0x00000008
#define NDIS_PACKET_TYPE_SOURCE_ROUTING               0x00000010
#define NDIS_PACKET_TYPE_PROMISCUOUS                  0x00000020
#define NDIS_PACKET_TYPE_SMT                          0x00000040
#define NDIS_PACKET_TYPE_ALL_LOCAL                    0x00000080
#define NDIS_PACKET_TYPE_GROUP                        0x00000100
#define NDIS_PACKET_TYPE_ALL_FUNCTIONAL               0x00000200
#define NDIS_PACKET_TYPE_FUNCTIONAL                   0x00000400
#define NDIS_PACKET_TYPE_MAC_FRAME                    0x00000800

#define NDIS_MEDIA_STATE_CONNECTED                    0x00000000
#define NDIS_MEDIA_STATE_DISCONNECTED                 0x00000001

#define NDIS_MAC_OPTION_COPY_LOOKAHEAD_DATA           0x00000001
#define NDIS_MAC_OPTION_RECEIVE_SERIALIZED            0x00000002
#define NDIS_MAC_OPTION_TRANSFERS_NOT_PEND            0x00000004
#define NDIS_MAC_OPTION_NO_LOOPBACK                   0x00000008
#define NDIS_MAC_OPTION_FULL_DUPLEX                   0x00000010
#define NDIS_MAC_OPTION_EOTX_INDICATION               0x00000020
#define NDIS_MAC_OPTION_8021P_PRIORITY                0x00000040
#define NDIS_MAC_OPTION_RESERVED                      0x80000000


/*-------------------------------------------------------------*/
extern uint8_t volatile gRndisCmd, gRndisAck;
extern uint8_t volatile gRndisOutData, gRndisInData;
/*-------------------------------------------------------------*/


void RNDIS_Init(void);
void RNDIS_InitForHighSpeed(void);
void RNDIS_InitForFullSpeed(void);
void RNDIS_ClassRequest(void);
void RNDIS_VendorRequest(void);

void EPA_Handler(void);
void EPB_Handler(void);
void RNDIS_ProcessClassCmd(void);
void RNDIS_ProcessOutData(void);
void RNDIS_InData(unsigned int u32PktLen);
void RNDIS_IsAvaiable(void);
void RNDIS_ProcessQueryOID(uint32_t oid);
void RNDIS_ProcessSetOID(uint32_t oid);

#endif  /* __RNDIS_H__ */

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
