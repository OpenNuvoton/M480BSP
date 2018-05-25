/*************************************************************************//**
 * @file     net.c
 * @brief    Packet processor source file for M480 MCU
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"
#include "net.h"

extern uint8_t  g_au8MacAddr[6];
extern uint8_t  volatile g_au8IpAddr[4];

static uint8_t  au8TxBuf[1514];
static uint8_t  au8RxBuf[1514];
static uint16_t s_u16IpPacketId = 1000;   // Packet ID used in IP header
static uint32_t s_u32PktRdy;                // If not 0, this variable stores the Tx packet length
#ifdef __ICCARM__
#pragma data_alignment=4
static uint8_t  s_au8DhcpRawBuffer[3020];
#elif defined (__GNUC__)
static uint8_t  s_au8DhcpRawBuffer[3020] __attribute__ ((aligned(4)));
#else
__align(4) static uint8_t  s_au8DhcpRawBuffer[3020];   // Buffer to store DHCP Tx/Rx data
#endif

/* RFC 1533
 *
 *
 *  When used with BOOTP, the first four octets of the vendor information
 *  field have been assigned to the "magic cookie" (as suggested in RFC
 *  951).  This field identifies the mode in which the succeeding data is
 *  to be interpreted.  The value of the magic cookie is the 4 octet
 *  dotted decimal 99.130.83.99 (or hexadecimal number 63.82.53.63) in
 *  network byte order.
 *
 * 9.4. DHCP Message Type
 *
 *  This option is used to convey the type of the DHCP message.  The code
 *  for this option is 53, and its length is 1.  Legal values for this
 *  option are:
 *
 *          Value   Message Type
 *          -----   ------------
 *            1     DHCPDISCOVER
 *            2     DHCPOFFER
 *            3     DHCPREQUEST
 *            4     DHCPDECLINE
 *            5     DHCPACK
 *            6     DHCPNAK
 *            7     DHCPRELEASE
 *
 *   Code   Len  Type
 *  +-----+-----+-----+
 *  |  53 |  1  | 1-7 |
 *  +-----+-----+-----+
 */

static uint8_t s_au8DhcpOptions[] = { 0x63, 0x82, 0x53, 0x63, 0x35, 0x01, DHCP_DISCOVER };



static uint16_t chksum(uint16_t *cp, int cnt)
{
    uint16_t i1=0, i2;

    while (cnt--)
    {
        i2 = *cp++;
        i2 = SWAP16(i2);
        i1 += i2;
        if (i1 < i2)
            i1++;
    }
    return SWAP16(i1);
}

static void arp_reply(uint8_t *target_ip, uint8_t *target_mac)
{
    ARP_PACKET  *arp = (ARP_PACKET *)&au8TxBuf[0];

    memcpy((char *)arp->au8DestMac, (char *)target_mac, 6);
    memcpy((char *)arp->au8SrcMac, (char *)g_au8MacAddr, 6);
    arp->u16Type = SWAP16(PROTOCOL_ARP);
    arp->u16HType = SWAP16(HT_ETHERNET);
    arp->u16PType = SWAP16(ARP_PTYPE);
    arp->u8HLen = 6;
    arp->u8PLen = 4;
    arp->u16Operation = SWAP16(ARP_REPLY);
    memcpy((char *)arp->au8SenderHA, (char *)g_au8MacAddr, 6);
    memcpy((char *)arp->su8SenderIP, (char *)g_au8IpAddr, 4);
    memcpy((char *)arp->au8TargetHA, (char *)target_mac, 6);
    memcpy((char *)arp->au8TargetIP, (char *)target_ip, 4);
    EMAC_SendPkt(&au8TxBuf[0], sizeof(ARP_PACKET));
}

static void  udp_send( uint8_t *pu8SrcMac, uint8_t *pu8SrcIP, uint16_t u16SrcPort,
                       uint8_t *pu8DestMac, uint8_t *pu8DestIP, uint16_t u16DestPort,
                       uint8_t *pu8TxData, uint32_t u32Len)
{
    UDP_PACKET *udp = (UDP_PACKET *)&au8TxBuf[0];

    NVIC_DisableIRQ(EMAC_RX_IRQn);

    /*- prepare Ethernet header, 14 bytes -*/
    memcpy((char *)&au8TxBuf[sizeof(UDP_PACKET)], (char *)pu8TxData, u32Len);
    memcpy((char *)udp->au8DestMac, (char *)pu8DestMac, 6);
    memcpy((char *)udp->au8SrcMac, (char *)pu8SrcMac, 6);
    udp->u16Type = SWAP16(PROTOCOL_IP);

    /*- prepare IP header, 20 bytes -*/
    udp->u8VerHLen = 0x45;     /* fixed value, do not change it */
    udp->u8ToS = 0;            /* no special priority */
    udp->u16TLen = SWAP16(sizeof(UDP_PACKET) - 14 + u32Len);
    udp->u16ID = SWAP16(s_u16IpPacketId);
    s_u16IpPacketId++;
    udp->u16Frag = 0;
    udp->u8TTL = 64;
    udp->u8Prot = IP_PRO_UDP;
    udp->u16HdrChksum = 0;
    memcpy((char *)udp->au8SrcIP, (char *)pu8SrcIP, 4);
    memcpy((char *)udp->au8DestIP, (char *)pu8DestIP, 4);
    udp->u16HdrChksum = ~chksum((uint16_t *)&udp->u8VerHLen, 10);  /* 20 bytes */

    /*- prepare UDP header 8 bytes -*/
    udp->u16SrcPort = SWAP16(u16SrcPort);
    udp->u16DestPort = SWAP16(u16DestPort);
    udp->u16MLen = SWAP16(8 + u32Len);
    udp->u16UDPChksum = 0;

    EMAC_SendPkt(&au8TxBuf[0], sizeof(UDP_PACKET) + u32Len);
    NVIC_EnableIRQ(EMAC_RX_IRQn);
}


int process_rx_packet(uint8_t *pu8Packet, uint32_t u32Len)
{
    ARP_PACKET    *arp = (ARP_PACKET *)pu8Packet;
    IP_PACKET    *ip  = (IP_PACKET *)pu8Packet;
    UDP_PACKET    *udp  = (UDP_PACKET *)pu8Packet;

    if (pu8Packet[0] == 0xFF)       /* this is a broadcast packet */
    {
        /*
         *  We manage the ARP reply process here.
         *  In the following code, if we have received a ARP request,
         *  we send ARP reply immediately.
         */
        if ((!COMPARE_IP(arp->au8TargetIP, g_au8IpAddr)) &&
                (arp->u16Type == SWAP16(PROTOCOL_ARP)) && (arp->u16Operation == SWAP16(ARP_REQUEST)))
        {
            arp_reply(arp->su8SenderIP, arp->au8SenderHA);
        }

        return 0;
    }
    else                        /* this is a multicast or unicast packet */
    {
        /*
         *  This is a unicast packet to us.
         */
        if ((ip->u8Prot == IP_PRO_TCP) && (!COMPARE_IP(ip->au8DestIP, g_au8IpAddr)))
        {
            // write me: process TCP packets here
            return 0;
        }

        if ((ip->u8Prot == IP_PRO_UDP) && (udp->u16SrcPort == SWAP16(67)))
        {
            // This is a DHCP packet...

            s_u32PktRdy = u32Len;
            memcpy(au8RxBuf, pu8Packet, u32Len);
            return 0;
        }

        if ((ip->u8Prot == IP_PRO_UDP) && (!COMPARE_IP(ip->au8DestIP, g_au8IpAddr)))
        {
            // write me: process UDP packets here
            return 0;
        }

        /*
         * Check ICMP Echo Request packet -
         * if matched, we reply it right here
         */
        if ((ip->u8Prot == IP_PRO_ICMP) && (!COMPARE_IP(ip->au8DestIP, g_au8IpAddr)) &&
                (pu8Packet[34] == 0x08))
        {
            IP_PACKET    *tx_ip;


            /* duplicate packet then modify it */
            memcpy((char *)&au8TxBuf[0], (char *)&pu8Packet[0], u32Len);


            tx_ip = (IP_PACKET *)&au8TxBuf[0];
            memcpy((char *)tx_ip->au8DestMac, (char *)ip->au8SrcMac, 6);
            memcpy((char *)tx_ip->au8SrcMac, (char *)g_au8MacAddr, 6);
            tx_ip->u16Type = SWAP16(PROTOCOL_IP);
            tx_ip->u8VerHLen = 0x45;         /* fixed value, do not change it */
            tx_ip->u8ToS = 0;                /* no special priority */
            tx_ip->u16TLen = SWAP16(60);
            tx_ip->u16ID = SWAP16(s_u16IpPacketId);
            tx_ip->u16Frag = 0;
            tx_ip->u8TTL = 64;
            tx_ip->u8Prot = IP_PRO_ICMP;
            tx_ip->u16HdrChksum = 0;
            memcpy((char *)tx_ip->au8SrcIP, (char *)g_au8IpAddr, 4);
            memcpy((char *)tx_ip->au8DestIP, (char *)ip->au8SrcIP, 4);
            tx_ip->u16HdrChksum = ~chksum((uint16_t *)&tx_ip->u8VerHLen, 10);  /* 20 bytes */

            s_u16IpPacketId++;

            /* ICMP reply */
            au8TxBuf[34] = 0;

            /* ICMP checksum */
            au8TxBuf[36] = 0;
            au8TxBuf[37] = 0;
            *(uint16_t *)&au8TxBuf[36] = ~chksum((uint16_t *)&au8TxBuf[34], (u32Len - 34) / 2);

            EMAC_SendPkt(au8TxBuf, u32Len);

            return 0;
        }
    }

    return 0;
}


int dhcp_start(void)
{
    uint8_t        *cptr;
    int            opt_len, len, retry, offer, out;
    uint8_t        serverMAC[] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
    uint8_t        serverIP[] = { 0xff, 0xff, 0xff, 0xff };
    uint32_t    tx_id = 0x8900;            /* just give a start value */
    DHCP_HDR_T  *dhcpRx, *dhcpTx;
    UDP_PACKET  *udp;
    uint32_t delay;

    dhcpTx = (DHCP_HDR_T *)&s_au8DhcpRawBuffer[0];
    udp = (UDP_PACKET *)&s_au8DhcpRawBuffer[1500];
    dhcpRx = (DHCP_HDR_T *)((uint32_t)udp + sizeof(UDP_PACKET));

    memset((char *)&dhcpTx[0], 0, sizeof(DHCP_HDR_T));
    dhcpTx->op_code = BOOTP_REQUEST;
    dhcpTx->hw_type = HW_TYPE_ETHERNET;        /* Hardware type: Ethernet */
    dhcpTx->hw_len = sizeof(g_au8MacAddr);     /* Hardware address length */
    dhcpTx->hops = HOP_COUNT;
    dhcpTx->tx_id = tx_id++;
    dhcpTx->seconds = 0;        /* Not use this */


    memset((char *)&(dhcpTx->clientIP), 0, 4);
    //memset((char *)_HostIP, 0, 4);
    /* give host MAC address */

    memcpy((char *)&(dhcpTx->client_hw_addr), (char *)g_au8MacAddr, 6);
    memcpy((char *)dhcpTx->options, (char *)s_au8DhcpOptions, sizeof(s_au8DhcpOptions));

    opt_len = sizeof(s_au8DhcpOptions);
    cptr = dhcpTx->options + opt_len;

    *cptr++ = 55;                  /* param request */
    *cptr++ = 4;                   /* length */
    *cptr++ = 0x01;                /* net mask */
    *cptr++ = 0x03;                /* gateway */
    *cptr++ = 0x06;                /* DNS */
    *cptr++ = 0x0f;                /* DNS domain */
    opt_len += 6;
    *cptr = 0xff;                 /* end of option area */

    printf("DHCP DISCOVER...\n");

wait_offer:
    out = 0;
    for (retry = 0; (retry < 16) && (!out); retry++)
    {
        if (retry)
            printf("DHCP DISCOVER retry: %d\n", retry);

        udp_send(g_au8MacAddr, (uint8_t *)g_au8IpAddr, CLIENT_PORT,
                 serverMAC, serverIP, SERVER_PORT,
                 (uint8_t *)dhcpTx, DHCP_OPT_OFFSET + opt_len + 1);

        delay = 0x600000;
        while(delay--)
        {
            if(s_u32PktRdy)
            {
                NVIC_DisableIRQ(EMAC_RX_IRQn);
                memcpy((char *)&s_au8DhcpRawBuffer[1500], au8RxBuf, s_u32PktRdy);
                s_u32PktRdy = 0;
                NVIC_EnableIRQ(EMAC_RX_IRQn);
                if ((udp->u16DestPort == SWAP16(CLIENT_PORT)) &&
                        (dhcpRx->op_code == BOOTP_REPLY) &&
                        (dhcpRx->tx_id == dhcpTx->tx_id))
                {
                    out = 1;
                    break;
                }
            }
        }

        if (delay == 0)
            continue;


    }  /* end of for */

    if (retry >= 16)
        return -1;                /* DHCP failed */

    cptr = (uint8_t *)&dhcpRx->options + 4;

    /* find out DHCP OFFER and copy server identifier */
    offer = 0;

    while (*cptr != 0xff)
    {
        len = cptr[1] + 2;
        if (*cptr == 53)
        {
            if (cptr[2] == DHCP_OFFER)
                offer = 1;
        }
        else if (*cptr == 54)            /* add server ID */
        {
            memcpy((char *)(dhcpTx->options) + opt_len, (char *)cptr, len);
            opt_len += len;
        }
        cptr += len;
    }

    if (offer == 0)
    {
        printf("No Offer!!\n");
        goto wait_offer;             /* wrong type, read again */
    }

    cptr =     (uint8_t *)(dhcpTx->options) + opt_len;
    *cptr++ = 50;
    *cptr++ = 4;
    memcpy((char *)cptr, (char *)&(dhcpRx->yourIP), 4);
    opt_len += 6;

    dhcpTx->options[6] = DHCP_REQUEST;
    dhcpTx->options[opt_len] = 0xff;
    dhcpTx->tx_id = tx_id++;

    printf("DHCP REQUEST...\n");

    out = 0;
    for (retry = 0; (retry < 16) && (!out); retry++)
    {
        if (retry)
            printf("DHCP REQUEST retry: %d\n", retry);

        udp_send(g_au8MacAddr, (uint8_t *)g_au8IpAddr, CLIENT_PORT,
                 serverMAC, serverIP, SERVER_PORT,
                 (uint8_t *)dhcpTx, DHCP_OPT_OFFSET + opt_len + 1);

        delay = 0x600000;
        while(delay--)
        {
            if(s_u32PktRdy)
            {
                NVIC_DisableIRQ(EMAC_RX_IRQn);
                memcpy((char *)&s_au8DhcpRawBuffer[1500], au8RxBuf, s_u32PktRdy);
                s_u32PktRdy = 0;
                NVIC_EnableIRQ(EMAC_RX_IRQn);
                if((udp->u16DestPort == SWAP16(CLIENT_PORT)) &&
                        (dhcpRx->op_code != BOOTP_REPLY) &&
                        (dhcpRx->tx_id != dhcpTx->tx_id))
                {
                    out = 1;
                    break;
                }
            }
        }

        if (delay == 0)
            continue;

        cptr = (uint8_t *)&dhcpRx->options + 4;

        while (*cptr != 0xff)
        {
            len = cptr[1] + 2;
            if (cptr[0] == 53)
            {
                if (cptr[2] == DHCP_ACK)
                    goto acked;
                if (cptr[2] == DHCP_NAK)
                {
                    printf("DHCP Naked!\n");

                    return -1;
                }
            }
            cptr += len;
        }
    }

    return -1;                /* DHCP failed */

acked:
    printf("DHCP ACKed...\n");

    memcpy((char *)g_au8IpAddr, (char *)&(dhcpRx->yourIP), 4);
    printf("IP Address. . . . . . . . . . . . : %d.%d.%d.%d\n", g_au8IpAddr[0], g_au8IpAddr[1],
           g_au8IpAddr[2], g_au8IpAddr[3]);

    cptr = (uint8_t *)&dhcpRx->options + 4;

    while (*cptr != 0xff)
    {
        len = cptr[1];
        switch (*cptr)
        {
        case 1:                 /* subnet mask */
            printf("Subnet Mask . . . . . . . . . . . : %d.%d.%d.%d\n", cptr[2], cptr[3], cptr[4], cptr[5]);
            break;
        case 2:                 /* time offset */
            break;
        case 3:                 /* router, take 1 */
            printf("Default Gateway . . . . . . . . . : %d.%d.%d.%d\n", cptr[2], cptr[3], cptr[4], cptr[5]);
            break;
        case 4:                 /* time server */
            printf("Time server: %d.%d.%d.%d\n", cptr[2], cptr[3], cptr[4], cptr[5]);
            break;

        }
        cptr += len + 2;
    }

    return 0;
}



