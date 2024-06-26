

/* Includes ------------------------------------------------------------------*/
#include "lwip/opt.h"
#include "lwip/arch.h"
#include "lwip/api.h"
#include "lwip/sockets.h"
#include "fs.h"
#include "string.h"
#include "httpserver-socket.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define WEBSERVER_THREAD_PRIO    ( tskIDLE_PRIORITY + 2UL )
#define WEBSERVER_THREAD_STACKSIZE  200
#define RX_BUFFER_LEN               1460
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
char au8Buf[RX_BUFFER_LEN];
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief serve tcp connection
  * @param clientfd socket for incoming connection
  * @retval None
  */
void http_server_serve(int clientfd)
{
    struct fs_file * file;
    int32_t i; 
    
    if(recv(clientfd, au8Buf, sizeof(au8Buf), 0) < 0)
        goto out;

    /* Is this an HTTP GET command? (only check the first 5 chars, since
    there are other formats for GET, and we're keeping it very simple )*/
    if(strncmp(au8Buf, "GET /", 5) == 0)
    {
        /* Check if request to get m4.jpg */
        if(strncmp((char const *)au8Buf,"GET /img/m4.jpg", 15) == 0)
        {
            /* Check if request to get M4 banner */
            file = fs_open("/img/m4.jpg");
            send(clientfd, (const unsigned char*)(file->data), (size_t)file->len, 0);
            fs_close(file);
        }
        else if((strncmp(au8Buf, "GET /index.html", 15) == 0)||(strncmp(au8Buf, "GET / ", 6) == 0))
        {
            /* Load index page */
            file = fs_open("/index.html");
            send(clientfd, (const unsigned char*)(file->data), (size_t)file->len, 0);
            fs_close(file);
        }
        else
        {
            /* Load Error page */
            file = fs_open("/404.html");
            send(clientfd, (const unsigned char*)(file->data), (size_t)file->len, 0);
            fs_close(file);
        }
    }

    /* Close connection */
out:
    close(clientfd);
}


/**
  * @brief  http server thread
  * @param arg pointer on argument(not used here)
  * @retval None
  */
static void http_server_socket_thread(void *arg)
{
    int sockfd, clientfd, size;
    struct sockaddr_in addr, client_addr;

    /* create a TCP socket */
    if ((sockfd = lwip_socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        return;
    }

    /* Bind to port 80 (HTTP) with any IP address */
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(sockfd, (struct sockaddr *)&addr, sizeof (addr)) < 0)
    {
        return;
    }

    /* listen for incoming connections */
    listen(sockfd, 8);
  
    size = sizeof(client_addr);
  
    while (1) 
    {
        clientfd = accept(sockfd, (struct sockaddr *)&client_addr, (socklen_t *)&size);
        http_server_serve(clientfd);
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
void http_server_socket_init()
{
    sys_thread_new("HTTP", http_server_socket_thread, NULL, WEBSERVER_THREAD_STACKSIZE, WEBSERVER_THREAD_PRIO);
    sys_thread_new("DMA Monitor", dma_monitor_thread, NULL, WEBSERVER_THREAD_STACKSIZE, WEBSERVER_THREAD_PRIO);
}

