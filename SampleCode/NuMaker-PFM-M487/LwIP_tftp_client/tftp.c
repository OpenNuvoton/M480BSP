/*************************************************************************//**
 * @file     tftp.c
 * @version  V1.00
 * @brief    A simple TFTP client source file.
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "string.h"
#include "tftp.h"


#define TFTP_THREAD_PRIO    ( tskIDLE_PRIORITY + 2UL )
#define TFTP_THREAD_STACKSIZE  200

#ifndef MIN
#define MIN(a, b)   (a) < (b) ? (a) : (b)
#endif

static struct netconn *conn;
static unsigned short server_port = TFTP_PORT;
static ip_addr_t server_addr;

#define FILE_LEN        2048
static uint32_t flen = FILE_LEN;
static uint8_t file[FILE_LEN];

char *file_name = "test.txt";   // File name to put or get
char *tftp_mode = "octet";      // Could be "octet", "netascii", or "mail"

void send_ack(uint16_t blk)
{
    struct netbuf *nbuf;
    char *data;
    /* Prepare data */
    if((nbuf = netbuf_new()) == NULL)
        return;
    if((data = netbuf_alloc(nbuf, 4)) == NULL)      // op 2, ack blk 2
    {
        netbuf_delete(nbuf);
        return;
    }
    *(uint16_t *)data = lwip_htons(TFTP_OPCODE_ACK);
    *(uint16_t *)(data + 2) = lwip_htons(blk);

    /* Send the packet */
    netconn_sendto(conn, nbuf, &server_addr, server_port);

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
    netconn_sendto(conn, nbuf, &server_addr, server_port);

    /* Free the buffer */
    netbuf_delete(nbuf);
}

void send_err(uint16_t err)
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
    netconn_sendto(conn, nbuf, &server_addr, server_port);

    /* Free the buffer */
    netbuf_delete(nbuf);
}

void send_rrq(void)
{
    struct netbuf *nbuf;
    char *data;
    /* Prepare data */
    if((nbuf = netbuf_new()) == NULL)
        return;
    if((data = netbuf_alloc(nbuf, 2 + strlen(file_name) + strlen(tftp_mode) + 2 )) == NULL)      // op 2, two string and two terminators
    {
        netbuf_delete(nbuf);
        return;
    }
    *(uint16_t *)data = lwip_htons(TFTP_OPCODE_RRQ);
    strcpy(data + 2, file_name);
    strcpy(data + 2 + strlen(file_name) + 1, tftp_mode);
    /* Send the packet */
    netconn_sendto(conn, nbuf, &server_addr, server_port);

    /* Free the buffer */
    netbuf_delete(nbuf);
}

void send_wrq(void)
{
    struct netbuf *nbuf;
    char *data;
    /* Prepare data */
    if((nbuf = netbuf_new()) == NULL)
        return;
    if((data = netbuf_alloc(nbuf, 2 + strlen(file_name) + strlen(tftp_mode) + 2 )) == NULL)      // op 2, two string and two terminators
    {
        netbuf_delete(nbuf);
        return;
    }
    *(uint16_t *)data = lwip_htons(TFTP_OPCODE_WRQ);
    strcpy(data + 2, file_name);
    strcpy(data + 2 + strlen(file_name) + 1, tftp_mode);

    /* Send the packet */
    netconn_sendto(conn, nbuf, &server_addr, server_port);

    /* Free the buffer */
    netbuf_delete(nbuf);
}

/**
  * @brief TFTP client thread
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
    uint16_t op, blk = 0;
    int retry, remain;
    char c = 0;
    int done = 0;
    int first = 1;  // set 1 for resend first wrq/rrq request on timeout, otherwise resend ack/data


    /* Configure tftp server IP address */
    IP4_ADDR(&server_addr, 192,168,0,3);

    /* Create a new UDP connection handle */
    conn = netconn_new(NETCONN_UDP);
    if (conn == NULL)
    {
        printf("netconn_new() failed\n");
        while(1);
    }

    printf("Select your option 1)get, 2)put\n");
    while(1)
    {
        c = getchar();
        if(c == '1' || c == '2')
            break;
    }
    if(c == '1')
    {
        printf("You select get file from server\n");
        state = TFTP_STATE_RRQ;
        send_rrq();
    }
    else
    {
        printf("You select put file to server\n");
        state = TFTP_STATE_WRQ;
        send_wrq();
    }

    while(!done)
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
                done = 1;
                continue;
            }
            /* Packet was likely lost */
            if(state == TFTP_STATE_RRQ)
            {
                if(first)
                {
                    printf("Timeout, resend RRQ %d\n", retry);
                    send_rrq();
                }
                else
                {
                    printf("Timeout, resend data %d\n", retry);
                    send_data(blk, (void *)data, MIN(remain, TFTP_BLOCK_LENGTH));
                }
                continue;
            }
            else if (state == TFTP_STATE_WRQ)
            {
                if(first)
                {
                    printf("Timeout, resend WRQ %d\n", retry);
                    send_wrq();
                }
                else
                {
                    printf("Timeout, resend ack %d\n", retry);
                    send_ack(blk);
                }
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
        if(memcmp(addr, &server_addr, sizeof(ip_addr_t)))
        {
            // Ignore everything not coming from server.
            // Server may select other port to complete the service, so check address only
            netbuf_delete(nbuf);
            continue;
        }

        switch(op)
        {
            case TFTP_OPCODE_DATA:
                if(state != TFTP_STATE_RRQ)
                {
                    send_err(TFTP_ERROR_ILLEGAL_OPERATION);
                    state = TFTP_STATE_IDLE;
                    done = 1;
                }
                else
                {
                    uint16_t new_blk = lwip_ntohs(*(uint16_t *)(payload + 2));


                    if(new_blk == blk)
                    {
                        /* Last ACK lost */
                        send_ack(blk);
                    }
                    else if(new_blk == blk + 1)
                    {
                        int i;
                        uint8_t *c = payload + 4;

                        if(first)
                        {
                            // Server may select other port to complete the service
                            server_port = port;
                            first = 0;
                        }
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
                            done = 1;
                            state = TFTP_STATE_IDLE;
                        }
                    }
                    else
                    {
                        /* Wrong ack # */
                        printf("Unknown ID number\n");
                        send_err(TFTP_ERROR_UNKNOWN_ID);
                        state = TFTP_STATE_IDLE;
                        done = 1;
                    }
                }
                break;

            case TFTP_OPCODE_ACK:
                if(state != TFTP_STATE_WRQ)
                {
                    send_err(TFTP_ERROR_ILLEGAL_OPERATION);
                    state = TFTP_STATE_IDLE;
                    done = 1;
                }
                else
                {
                    uint16_t new_blk = lwip_ntohs(*(uint16_t *)(payload + 2));

                    if(first)
                    {
                        if(new_blk != 0)
                        {
                            /* Ack block # for WRQ must be 0 */
                            printf("Unknown ID number\n");
                            send_err(TFTP_ERROR_UNKNOWN_ID);
                            state = TFTP_STATE_IDLE;
                            done = 1;
                        }
                        else
                        {
                            // Server may select other port to complete the service
                            server_port = port;
                            remain = flen;
                            data = file;
                            blk++;
                            printf(".");
                            first = 0;
                            send_data(blk, data, MIN(remain, TFTP_BLOCK_LENGTH));
                        }
                    }
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
                            done = 1;
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
                        send_err(TFTP_ERROR_UNKNOWN_ID);
                        state = TFTP_STATE_IDLE;
                        done = 1;
                    }
                }
                break;
            case TFTP_OPCODE_ERROR:
                /* Reset to idle state on error */
                state = TFTP_STATE_IDLE;
                done = 1;
                printf("Received ERR: %d\n", lwip_ntohs(*(uint16_t *)(payload + 2)));
                break;
            default:
                /* Reset to idle state if recevied unknown op code */
                printf("Received unknown op code\n");
                send_err(TFTP_ERROR_ILLEGAL_OPERATION);
                state = TFTP_STATE_IDLE;
                done = 1;
                break;
        }

        netbuf_delete(nbuf);
    }
    while(1);
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
void tftp_client_init(void)
{
    int i;

    for(i = 0; i < FILE_LEN; i++)
        file[i] = i & 0xFF;
    sys_thread_new("TFTP", tftp_thread, NULL, TFTP_THREAD_STACKSIZE, TFTP_THREAD_PRIO);
    sys_thread_new("DMA Monitor", dma_monitor_thread, NULL, TFTP_THREAD_STACKSIZE, TFTP_THREAD_PRIO);
}

