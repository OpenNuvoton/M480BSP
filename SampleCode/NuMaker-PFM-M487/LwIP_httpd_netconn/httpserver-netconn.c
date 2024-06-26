

/* Includes ------------------------------------------------------------------*/
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "fs.h"
#include "string.h"
#include "httpserver-netconn.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define WEBSERVER_THREAD_PRIO    ( tskIDLE_PRIORITY + 2UL )
#define WEBSERVER_THREAD_STACKSIZE  200
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
u32_t nPageHits = 0;


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief serve tcp connection
  * @param conn: pointer on connection structure
  * @retval None
  */
void http_server_serve(struct netconn *conn)
{
    struct netbuf *inbuf;
    char* buf;
    u16_t buflen;
    struct fs_file * file;

    /* Read the data from the port, blocking if nothing yet there.
     We assume the request (the part we care about) is in one netbuf */
    netconn_recv(conn,&inbuf);

    if (inbuf != NULL)
    {
        if (netconn_err(conn) == ERR_OK)
        {
            netbuf_data(inbuf, (void**)&buf, &buflen);

            /* Is this an HTTP GET command? (only check the first 5 chars, since
            there are other formats for GET, and we're keeping it very simple )*/
            if ((buflen >=5) && (strncmp(buf, "GET /", 5) == 0))
            {
                /* Check if request to get m4.jpg */
                if (strncmp((char const *)buf,"GET /img/m4.jpg", 15) == 0)
                {
                    /* Check if request to get M4 banner */
                    file = fs_open("/img/m4.jpg");
                    netconn_write(conn, (const unsigned char*)(file->data), (size_t)file->len, NETCONN_NOCOPY);
                    fs_close(file);
                }
                else if((strncmp(buf, "GET /index.html", 15) == 0)||(strncmp(buf, "GET / ", 6) == 0))
                {
                    /* Load index page */
                    file = fs_open("/index.html");
                    netconn_write(conn, (const unsigned char*)(file->data), (size_t)file->len, NETCONN_NOCOPY);
                    fs_close(file);
                }
                else
                {
                    /* Load Error page */
                    file = fs_open("/404.html");
                    netconn_write(conn, (const unsigned char*)(file->data), (size_t)file->len, NETCONN_NOCOPY);
                    fs_close(file);
                }
            }
        }
    }
    /* Close the connection (server closes in HTTP) */
    netconn_close(conn);

    /* Delete the buffer (netconn_recv gives us ownership,
     so we have to make sure to deallocate the buffer) */
    netbuf_delete(inbuf);
}


/**
  * @brief  http server thread
  * @param arg: pointer on argument(not used here)
  * @retval None
  */
static void http_server_netconn_thread(void *arg)
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
                /* accept any incoming connection */
                netconn_accept(conn,&newconn);

                if(newconn)
                {
                    /* serve connection */
                    http_server_serve(newconn);

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
  * @brief  Initialize the HTTP server (start its thread)
  * @param  none
  * @retval None
  */
void http_server_netconn_init()
{
    sys_thread_new("HTTP", http_server_netconn_thread, NULL, WEBSERVER_THREAD_STACKSIZE, WEBSERVER_THREAD_PRIO);
    sys_thread_new("DMA Monitor", dma_monitor_thread, NULL, WEBSERVER_THREAD_STACKSIZE, WEBSERVER_THREAD_PRIO);
}

