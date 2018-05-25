/*************************************************************************//**
 * @file     net.c
 * @brief    Packet processor header file for M480 MCU
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef  _NET_H_
#define  _NET_H_

#include <stdint.h>

#define  PROTOCOL_ARP       0x0806
#define  PROTOCOL_IP        0x0800

#define  HT_ETHERNET        0x0001
#define  ARP_PTYPE          0x0800

#define  ARP_REQUEST          0x01
#define  ARP_REPLY            0x02
#define  RARP_REQUEST         0x03
#define  RARP_REPLY           0x04

#define  IP_PRO_ICMP             1
#define  IP_PRO_TCP              6
#define  IP_PRO_UDP             17

/* DHCP client and server ports */
#define SERVER_PORT             67
#define CLIENT_PORT             68

#define DHCP_DISCOVER            1
#define DHCP_OFFER               2
#define DHCP_REQUEST             3
#define DHCP_DECLINE             4
#define DHCP_ACK                 5
#define DHCP_NAK                 6
#define DHCP_RELEASE             7
#define DHCP_INFORM              8

#define BOOTP_REQUEST            1
#define BOOTP_REPLY              2

#define HW_TYPE_ETHERNET         1
#define HOP_COUNT                5

#define DHCP_OPT_OFFSET        236        /* size without options */

typedef struct ETHER_HEADER
{
    uint8_t   au8DestMac[6]; /* Destination MAC address */
    uint8_t   au8SrcMac[6];  /* Source MAC address */
    uint16_t  u16Type;       /* Protocol type */
} ETHER_PACKET;

typedef struct ARP_PACKET
{
    uint8_t   au8DestMac[6];    /* Destination MAC address */
    uint8_t   au8SrcMac[6];     /* Source MAC address */
    uint16_t  u16Type;          /* Protocol type, 0x0806 */
    uint16_t  u16HType;         /* hardware type */
    uint16_t  u16PType;         /* protocol, 0x0800:Internet */
    uint8_t   u8HLen;           /* hardware length */
    uint8_t   u8PLen;           /* protocol length */
    uint16_t  u16Operation;     /* operation, 1:ARP request, 2:ARP reply, 3:RARP request, 4:RARP reply */
    uint8_t   au8SenderHA[6];   /* sender hardware address */
    uint8_t   su8SenderIP[4];   /* sender IP address */
    uint8_t   au8TargetHA[6];   /* target hardware address */
    uint8_t   au8TargetIP[4];   /* target IP address */
} ARP_PACKET;



typedef struct IP_PACKET
{
    uint8_t   au8DestMac[6];    /* Destination MAC address */
    uint8_t   au8SrcMac[6];     /* Source MAC address */
    uint16_t  u16Type;          /* Protocol type, 0x0800 */
    uint8_t   u8VerHLen;        /* bits[7..4]:VERS, bits[3..0]:HLEN */
    uint8_t   u8ToS;            /* service type */
    uint16_t  u16TLen;          /* total length, start from "vers_hlen" field */
    uint16_t  u16ID;            /* IP packet identification */
    uint16_t  u16Frag;          /* bits[15..12]:flags, bits[11..0]:fragment offset */
    uint8_t   u8TTL;            /* time-to-live */
    uint8_t   u8Prot;           /* IP protocol, 1:ICMP, 6:TCP, 17:UDP */
    uint16_t  u16HdrChksum;     /* header check sum */
    uint8_t   au8SrcIP[4];      /* source IP */
    uint8_t   au8DestIP[4];     /* destination IP */
} IP_PACKET;



typedef struct UDP_PACKET
{
    uint8_t   au8DestMac[6];    /* Destination MAC address */
    uint8_t   au8SrcMac[6];     /* Source MAC address */
    uint16_t  u16Type;          /* Protocol type, 0x0800 */
    uint8_t   u8VerHLen;        /* bits[7..4]:VERS, bits[3..0]:HLEN */
    uint8_t   u8ToS;            /* Type of service */
    uint16_t  u16TLen;          /* total length, start from "u8VerHLen" field */
    uint16_t  u16ID;            /* IP packet identification */
    uint16_t  u16Frag;          /* bits[15..12]:flags, bits[11..0]:fragment offset */
    uint8_t   u8TTL;            /* time-to-live */
    uint8_t   u8Prot;           /* IP protocol, 1:ICMP, 6:TCP, 17:UDP */
    uint16_t  u16HdrChksum;     /* header check sum */
    uint8_t   au8SrcIP[4];      /* source IP */
    uint8_t   au8DestIP[4];     /* destination IP */
    uint16_t  u16SrcPort;       /* source port */
    uint16_t  u16DestPort;      /* destination port */
    uint16_t  u16MLen;          /* message length, start from "u16SrcPort" */
    uint16_t  u16UDPChksum;     /* check sum of UDP packet, including virtual header */
} UDP_PACKET;


typedef struct UDP_PSEUDO      /* UDP pseudo header, for check sum calculation */
{
    uint8_t   au8SrcIP[4];     /* source IP */
    uint8_t   au8DestIP[4];    /* destination IP */
    uint16_t  u16Protocol;
    uint16_t  u16UDPLen;
} UDP_PSEUDO;

typedef struct DHCP_HDR_T
{
    uint8_t   op_code;         /* operation */
    uint8_t   hw_type;         /* hardware type */
    uint8_t   hw_len;          /* hardware address length */
    uint8_t   hops;            /* gateway hops */
    uint32_t  tx_id;           /* transaction ID */
    uint16_t  seconds;         /* seconds since boot began */
    uint16_t  flags;           /* flags */
    uint32_t  clientIP;        /* client IP address */
    uint32_t  yourIP;          /* your IP address */
    uint32_t  serverIP;        /* server IP address */
    uint32_t  gatewayIP;       /* gateway IP address */
    uint8_t   client_hw_addr[16];     /* client hardware address */
    uint8_t   serverName[64];  /* server host name */
    uint8_t   bootFile[128];   /* boot bootFile name */
    uint8_t   options[312];    /* options */
} DHCP_HDR_T;

#define COMPARE_IP(ip1,ip2)     ((ip1[3]^ip2[3])|(ip1[2]^ip2[2])|(ip1[1]^ip2[1])|(ip1[0]^ip2[0]))
#define SWAP16(x)               ((((x)>>8)&0xFF)|(((x)<<8)&0xFF00))
#define GET16(bptr,n)           (bptr[n+1] | (bptr[n] << 8))
#define GET32(bptr,n)           (bptr[n+3] | (bptr[n+2] << 8) | (bptr[n+1] << 16) | (bptr[n] << 24))
#define PUT16(bptr,n,val)       do{bptr[n+1] = val & 0xFF;\
                                   bptr[n] = (val >> 8) & 0xFF;}while(0)
#define PUT32(bptr,n,val)       do{bptr[n+3] = val & 0xFF;\
                                   bptr[n+2] = (val >> 8) & 0xFF;\
                                   bptr[n+1] = (val >> 16) & 0xFF;\
                                   bptr[n] = (val >> 24) & 0xFF;}while(0)


extern int process_rx_packet(uint8_t *pu8Packet, uint32_t u32Len);
extern int dhcp_start(void);


#endif  /* _NET_H_ */
