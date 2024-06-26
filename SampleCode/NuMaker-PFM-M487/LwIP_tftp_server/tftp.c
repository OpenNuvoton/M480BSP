/*************************************************************************//**
 * @file     tftp.c
 * @version  V1.00
 * @brief    A simple TFTP source file.
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "string.h"
#include "tftp.h"
#include "netif/m480_eth.h"

#define TFTP_THREAD_PRIO    ( tskIDLE_PRIORITY + 2UL )
#define TFTP_THREAD_STACKSIZE  200

#ifndef MIN
#define MIN(a, b)   (a) < (b) ? (a) : (b)
#endif

static struct netconn *conn;
static unsigned short client_port;
static ip_addr_t client_addr;

#define FILE_LEN        2048
static uint32_t flen = FILE_LEN;
static uint8_t file[FILE_LEN];


void send_ack(uint16_t blk)
{
    struct netbuf *nbuf;
    uint16_t op = TFTP_OPCODE_ACK;
    char *data;
    /* Prepare data */
    if((nbuf = netbuf_new()) == NULL)
        return;
    if((data = netbuf_alloc(nbuf, 4)) == NULL)      // op 2, ack blk 2
    {
        netbuf_delete(nbuf);
        return;
    }
    *(uint16_t *)data = lwip_htons(op);
    *(uint16_t *)(data + 2) = lwip_htons(blk);

    /* Send the packet */
    netconn_sendto(conn, nbuf, &client_addr, client_port);

    /* Free the buffer */
    netbuf_delete(nbuf);
}

void send_data(uint16_t blk, uint8_t *buf, uint16_t len)
{
    struct netbuf *nbuf;
    char *data;
    /* Prepare data */
    if((nbuf = netbuf_new()) == NULL)
        return;
    if((data = netbuf_alloc(nbuf, len + 4)) == NULL)    // op 2, blk 2
    {
        netbuf_delete(nbuf);
        return;
    }
    *(uint16_t *)data = lwip_htons(TFTP_OPCODE_DATA);
    *(uint16_t *)(data + 2) = lwip_htons(blk);
    memcpy(data + 4, (void *)buf, len);
    /* Send the packet */
    netconn_sendto(conn, nbuf, &client_addr, client_port);

    /* Free the buffer */
    netbuf_delete(nbuf);
}

void send_err(ip_addr_t *addr, unsigned short port, uint16_t err)
{
    struct netbuf *nbuf;
    char *data;
    /* Prepare data */
    if((nbuf = netbuf_new()) == NULL)
        return;
    if((data = netbuf_alloc(nbuf, 8)) == NULL)      // op 2, err code 2, msg 4
    {
        netbuf_delete(nbuf);
        return;
    }
    *(uint16_t *)data = lwip_htons(TFTP_OPCODE_ERROR);
    *(uint16_t *)(data + 2) = lwip_htons(err);
    data[4] = 'E';
    data[5] = 'R';
    data[6] = 'R';
    data[7] = 0x00;
    /* Send the packet */
    netconn_sendto(conn, nbuf, addr, port);

    /* Free the buffer */
    netbuf_delete(nbuf);
}

/**
  * @brief TFTP server thread
  * @param arg pointer on argument(not used here)
  * @retval None
  */
static void tftp_thread(void *arg)
{

    err_t err;
    struct netbuf *nbuf;
    uint8_t *data, *payload;
    ip_addr_t *addr;
    unsigned short port;
    uint16_t payload_len;

    uint16_t state = TFTP_STATE_IDLE;
    uint16_t op, blk;
    int retry, remain;


    /* Create a new UDP connection handle */
    conn = netconn_new(NETCONN_UDP);
    if (conn == NULL)
    {
        printf("netconn_new() failed\n");
        while(1);
    }

    /* Set Rx timeout */
    netconn_set_recvtimeout(conn, TFTP_TIMEOUT);

    /* Bind to port 69 with default IP address */
    err = netconn_bind(conn, NULL, TFTP_PORT);

    if (err != ERR_OK)
    {
        printf("netconn_bind() failed\n");
        while(1);
    }

    while(1)
    {
        err = netconn_recv(conn, &nbuf);
        if(err == ERR_TIMEOUT)
        {
            if(state == TFTP_STATE_IDLE)
                continue;

            if(++retry > TFTP_MAX_RETRIES)
            {
                printf("Exceed retry count, reset to idle state\n");
                retry = 0;
                state = TFTP_STATE_IDLE;
                continue;
            }
            /* Packet was likely lost */
            if(state == TFTP_STATE_RRQ)
            {
                printf("Timeout, resend data %d\n", retry);
                send_data(blk, (void *)data, MIN(remain, TFTP_BLOCK_LENGTH));
                continue;
            }
            else
            {
                printf("Timeout, resend ack %d\n", retry);
                send_ack(blk);
                continue;
            }
        }
        else if(err != ERR_OK)
        {
            continue;
        }

        retry = 0;

        /* Get destination IP address and port*/
        addr = netbuf_fromaddr(nbuf);
        port = netbuf_fromport(nbuf);
        /* Get the payload and length */
        netbuf_data(nbuf, (void**)&payload, &payload_len);

        op = lwip_ntohs(*(uint16_t *)payload);

        switch(op)
        {
            case TFTP_OPCODE_RRQ:
            case TFTP_OPCODE_WRQ:
                if(state == TFTP_STATE_IDLE)
                {
                    /* New request comes in, save client's address and port number */
                    memcpy((void *)&client_addr, addr, sizeof(ip_addr_t));
                    client_port = port;
                    /* This sample does not check file name and mode */
                    if(op == TFTP_OPCODE_RRQ)
                    {
                        printf("Received RRQ\n");
                        blk = 1;
                        data = file;
                        remain = flen;
                        state = TFTP_STATE_RRQ;
                        send_data(blk, data, MIN(remain, TFTP_BLOCK_LENGTH));
                    }
                    else
                    {
                        printf("Received WRQ\n");
                        /* ACK for WRQ must be 0 */
                        blk = 0;
                        state = TFTP_STATE_WRQ;
                        send_ack(blk);
                    }
                }
                else
                {
                    /* Be patient, one client at a time.  */
                    send_err(addr, port, TFTP_ERROR_ACCESS_VIOLATION);
                }
                break;

            case TFTP_OPCODE_DATA:
                if((port != client_port) || memcmp(addr, &client_addr, sizeof(ip_addr_t)) || (state != TFTP_STATE_WRQ))
                {
                    send_err(addr, port, TFTP_ERROR_ILLEGAL_OPERATION);
                }
                else
                {
                    uint16_t new_blk = lwip_ntohs(*(uint16_t *)(payload + 2));

                    if(new_blk == blk)
                    {
                        /* Last ACK lost */
                        send_ack(blk);
                    }
                    if(new_blk == blk + 1)
                    {
                        int i;
                        uint8_t *c = payload + 4;
                        // Dump received data */
                        for(i = 0; i < payload_len - 4; i++)
                        {
                            if((i & 0xF) == 0)
                                printf("\n");
                            printf("%02x ", *c++);
                        }

                        blk = new_blk;
                        send_ack(blk);
                        if(payload_len < TFTP_BLOCK_LENGTH + 4)
                        {
                            /* This is the last data packet, all done */
                            printf("Done\n");
                            state = TFTP_STATE_IDLE;
                        }
                    }
                    else
                    {
                        /* Wrong ack # */
                        printf("Unknown ID number\n");
                        send_err(addr, port, TFTP_ERROR_UNKNOWN_ID);
                        state = TFTP_STATE_IDLE;
                    }
                }
                break;

            case TFTP_OPCODE_ACK:
                if((port != client_port) || memcmp(addr, &client_addr, sizeof(ip_addr_t)) || (state != TFTP_STATE_RRQ))
                {
                    send_err(addr, port, TFTP_ERROR_ILLEGAL_OPERATION);
                }
                else
                {
                    uint16_t new_blk = lwip_ntohs(*(uint16_t *)(payload + 2));

                    if(new_blk == (blk - 1))
                    {
                        /* Last packet was lost */
                        send_data(blk, data, MIN(remain, TFTP_BLOCK_LENGTH));
                    }
                    else if(new_blk == blk)
                    {
                        remain -= TFTP_BLOCK_LENGTH;
                        if(remain < 0)  /* Still need to send a 0 data packet if remain is 0 */
                        {
                            /* All done */
                            printf("\nDone\n");
                            state = TFTP_STATE_IDLE;
                        }
                        else
                        {
                            blk++;
                            data += TFTP_BLOCK_LENGTH;
                            printf(".");
                            send_data(blk, data, MIN(remain, TFTP_BLOCK_LENGTH));
                        }
                    }
                    else
                    {
                        /* Wrong ack # */
                        printf("Unknown ID number\n");
                        send_err(addr, port, TFTP_ERROR_UNKNOWN_ID);
                        state = TFTP_STATE_IDLE;
                    }
                }
                break;
            case TFTP_OPCODE_ERROR:
                /* Reset to idle state iff this packet is from our client */
                if((port == client_port) || !memcmp(addr, &client_addr, sizeof(ip_addr_t)))
                {
                    state = TFTP_STATE_IDLE;
                    printf("Received ERR: %d\n", lwip_ntohs(*(uint16_t *)(payload + 2)));
                }
                break;
            default:
                /* Reset to idle state iff this packet is from our client */
                if((port == client_port) || !memcmp(addr, &client_addr, sizeof(ip_addr_t)))
                {
                    printf("Received unknown op code\n");
                    send_err(addr, port, TFTP_ERROR_ILLEGAL_OPERATION);
                    state = TFTP_STATE_IDLE;
                }
                break;
        }

        netbuf_delete(nbuf);
    }
}

static void dma_monitor_thread(void *arg)
{
    while(1)
    {
        if(check_dma_buf_overflow())
            printf("\nDEBUG : DMA overflow !!!\nEMAC has been reset\n\n");
        vTaskDelay(1000); // Check identifier per sec
    }
}

/**
  * @brief  Initialize the TFTP server (start its thread)
  * @param  none
  * @retval None
  */
void tftp_server_init(void)
{
    int i;

    for(i = 0; i < FILE_LEN; i++)
        file[i] = i & 0xFF;
    sys_thread_new("TFTP", tftp_thread, NULL, TFTP_THREAD_STACKSIZE, TFTP_THREAD_PRIO);
    sys_thread_new("DMA Monitor", dma_monitor_thread, NULL, TFTP_THREAD_STACKSIZE, TFTP_THREAD_PRIO);
}

