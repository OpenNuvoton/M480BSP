

/* Includes ------------------------------------------------------------------*/
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "string.h"
#include "udp_echoclient-netconn.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define UDPECHOCLIENT_THREAD_PRIO    ( tskIDLE_PRIORITY + 2UL )
#define UDPECHOCLIENT_THREAD_STACKSIZE  200
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
char au8Buf[1500];

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief UDP client thread
  * @param arg pointer on argument(not used here)
  * @retval None
  */
static void udp_echoclient_netconn_thread(void *arg)
{
    struct netconn *conn;
    err_t err;
    struct netbuf *buf, *rbuf;
    char *data;
    ip_addr_t addr;

    IP4_ADDR(&addr, 192,168,0,2);

    /* Create a new UDP connection handle */
    conn = netconn_new(NETCONN_UDP);
    if (conn!= NULL)
    {
        err = netconn_bind(conn, IP_ADDR_ANY, 5168); //local port 5168

        if (err == ERR_OK)
        {
            while(1)
            {
                printf("Send to UDP echo server ...");
                buf = netbuf_new();
                strcpy(au8Buf, "Hi there...");
                data = netbuf_alloc(buf, strlen(au8Buf));
                memcpy (data, au8Buf, strlen(au8Buf));
                /* Send the packet */
                netconn_sendto(conn, buf, &addr, 80);
                while(netconn_recv(conn, &rbuf) != ERR_OK);
                printf(" [OK] ...\n");
                printf("Receive: %s\n", (char *)rbuf->p->payload);

                /* Free the buffer */
                netbuf_delete(buf);
                netbuf_delete(rbuf);
                vTaskDelay(500);
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
  * @brief  Initialize the UDP echo client (start its thread)
  * @param  none
  * @retval None
  */
void udp_echoclient_netconn_init()
{
    sys_thread_new("UDPECHO", udp_echoclient_netconn_thread, NULL, UDPECHOCLIENT_THREAD_STACKSIZE, UDPECHOCLIENT_THREAD_PRIO);
    sys_thread_new("DMA Monitor", dma_monitor_thread, NULL, UDPECHOCLIENT_THREAD_STACKSIZE, UDPECHOCLIENT_THREAD_PRIO);
}

