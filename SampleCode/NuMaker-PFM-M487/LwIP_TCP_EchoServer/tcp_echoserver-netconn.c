

/* Includes ------------------------------------------------------------------*/
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "string.h"
#include "tcp_echoserver-netconn.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TCPECHOSERVER_THREAD_PRIO    ( tskIDLE_PRIORITY + 2UL )
#define TCPECHOSERVER_THREAD_STACKSIZE  200
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief serve TCP connection
  * @param conn: pointer on connection structure
  * @retval None
  */
void tcp_echoserver_serve(struct netconn *conn)
{
    struct netbuf *inbuf;
    char* buf;
    u16_t buflen;
    char string_pass[] = "Hello World!!";
    char string_fail[] = "Wrong Password!!";

    printf("Wait for TCP data       ...");

    /* Read the data from the port, blocking if nothing yet there.
     We assume the request (the part we care about) is in one netbuf */
    netconn_recv(conn,&inbuf);

    printf(" [OK] ...\n");
    if (inbuf != NULL)
    {
        if (netconn_err(conn) == ERR_OK)
        {
            netbuf_data(inbuf, (void**)&buf, &buflen);
            if (strncmp(buf, "nuvoton", 7) == 0)
                netconn_write(conn, (const unsigned char*)string_pass, (size_t)strlen(string_pass), NETCONN_NOCOPY);
            else
                netconn_write(conn, (const unsigned char*)string_fail, (size_t)strlen(string_fail), NETCONN_NOCOPY);
        }
    }

    printf("Close TCP connection    ...");

    /* Close the connection */
    netconn_close(conn);

    /* Delete the buffer (netconn_recv gives us ownership,
     so we have to make sure to deallocate the buffer) */
    netbuf_delete(inbuf);

    printf(" [OK] ...\n");
}


/**
  * @brief  TCP echo server thread
  * @param arg pointer on argument(not used here)
  * @retval None
  */
static void tcp_echoserver_netconn_thread(void *arg)
{
    struct netconn *conn, *newconn;
    err_t err;

    /* Create a new TCP connection handle */
    conn = netconn_new(NETCONN_TCP);

    if (conn!= NULL)
    {
        /* Bind to port 80 (HTTP) with default IP address */
        err = netconn_bind(conn, NULL, 80);

        if (err == ERR_OK)
        {
            /* Put the connection into LISTEN state */
            netconn_listen(conn);

            while(1)
            {
                printf("Wait for TCP connection ...");

                /* accept any icoming connection */
                netconn_accept(conn,&newconn);

                if(newconn)
                {
                    printf(" [OK] ...\n");

                    /* serve connection */
                    tcp_echoserver_serve(newconn);

                    /* delete connection */
                    netconn_delete(newconn);
                }
            }
        }
        else
        {
            printf("can not bind netconn");
        }
    }
    else
    {
        printf("can not create netconn");
    }
}

/**
  * @brief  Initialize the TCP server (start its thread)
  * @param  none
  * @retval None
  */
void tcp_echoserver_netconn_init()
{
    sys_thread_new("TCPECHO", tcp_echoserver_netconn_thread, NULL, TCPECHOSERVER_THREAD_STACKSIZE, TCPECHOSERVER_THREAD_PRIO);
}

