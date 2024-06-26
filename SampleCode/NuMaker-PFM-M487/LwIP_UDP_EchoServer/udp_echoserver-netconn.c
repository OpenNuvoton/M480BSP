

/* Includes ------------------------------------------------------------------*/
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "string.h"
#include "udp_echoserver-netconn.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define UDPECHOSERVER_THREAD_PRIO    ( tskIDLE_PRIORITY + 2UL )
#define UDPECHOSERVER_THREAD_STACKSIZE  200
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  UDP server thread
  * @param arg pointer on argument(not used here)
  * @retval None
  */
static void udp_echoserver_netconn_thread(void *arg)
{
    struct netconn *conn;
    err_t err;
    struct netbuf *buf, *buf_send;
    char *data, *payload_data;
    static ip_addr_t *addr;
    static unsigned short port;
    unsigned int payload_len;

    /* Create a new UDP connection handle */
    conn = netconn_new(NETCONN_UDP);
    if (conn!= NULL)
    {
        /* Bind to port 80 with default IP address */
        err = netconn_bind(conn, NULL, 80);

        if (err == ERR_OK)
        {
            while(1)
            {
                printf("Wait for UDP data ...");
                while(netconn_recv(conn, &buf) != ERR_OK);
                printf(" [OK] ...\n");

                /* Get destination ip address and port*/
                addr = netbuf_fromaddr(buf);
                port = netbuf_fromport(buf);

                /* Get the payload and length */
                payload_len = buf->p->len;
                payload_data = buf->p->payload;

                /* Prepare data */
                buf_send = netbuf_new();
                data = netbuf_alloc(buf_send, payload_len);
                memcpy (data, payload_data, payload_len);

                /* Send the packet */
                netconn_sendto(conn, buf_send, addr, port);

                /* Free the buffer */
                netbuf_delete(buf_send);
                netbuf_delete(buf);
            }
        }
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
  * @brief  Initialize the UDP echo server (start its thread)
  * @param  none
  * @retval None
  */
void udp_echoserver_netconn_init()
{
    sys_thread_new("UDPECHO", udp_echoserver_netconn_thread, NULL, UDPECHOSERVER_THREAD_STACKSIZE, UDPECHOSERVER_THREAD_PRIO);
    sys_thread_new("DMA Monitor", dma_monitor_thread, NULL, UDPECHOSERVER_THREAD_STACKSIZE, UDPECHOSERVER_THREAD_PRIO);
}

