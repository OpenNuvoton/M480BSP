

/* Includes ------------------------------------------------------------------*/
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "string.h"
#include "tcp_echoclient-netconn.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TCPECHOCLIENT_THREAD_PRIO    ( tskIDLE_PRIORITY + 2UL )
#define TCPECHOCLIENT_THREAD_STACKSIZE  200
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/**
  * @brief  TCP echo client thread
  * @param arg pointer on argument(not used here)
  * @retval None
  */
static void tcp_echoclient_netconn_thread(void *arg)
{
    struct netconn *conn;
    err_t err;
    ip_addr_t server_ip;
    struct netbuf *inbuf;
    char* buf;
    u16_t buflen;
    char string[] = "nuvoton";
    
    IP4_ADDR(&server_ip, 192, 168, 0, 2);
    /* Create a new TCP connection handle */
    conn = netconn_new(NETCONN_TCP);

    if (conn!= NULL)
    {
        /* Bind to port 5168 with default IP address */
        err = netconn_bind(conn, NULL, 5168);

        if (err == ERR_OK)
        {
            err = netconn_connect(conn, &server_ip, 80);

            if(err == ERR_OK)
            {
                while(1)
                {
                    printf("Send for TCP packet ...");
                    netconn_write(conn, (const unsigned char*)string, (size_t)strlen(string), NETCONN_NOCOPY);

                    netconn_recv(conn, &inbuf);
                    netbuf_data(inbuf, (void**)&buf, &buflen);
                    printf("Recv: %s\n", buf);
                    netbuf_delete(inbuf);
                    vTaskDelay(1000);
                }
            }
        }
        else
        {
            printf("can not bind netconn");
            netconn_close(conn);
        }
    }
    else
    {
        printf("can not create netconn");
    }
}

/**
  * @brief  Initialize the TCP client (start its thread)
  * @param  none
  * @retval None
  */
void tcp_echoclient_netconn_init()
{
    sys_thread_new("TCPECHO", tcp_echoclient_netconn_thread, NULL, TCPECHOCLIENT_THREAD_STACKSIZE, TCPECHOCLIENT_THREAD_PRIO);
}

