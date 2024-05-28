/**
    @file       mqtt-tcp.c
    @author Nishant Agrawal
    @org        Real Time Solutions Pvt. Ltd.
    @date       29th Aug 2017
    @brief  functions which create a tcp layer on top of lwIP netconn implementation to use on mqtt_client_xx functions
                    in mqtt-client.c.
    @note       The application should not call these functions as they are all called by mqtt_client_xx functions
*/
#include "lwip/opt.h"//clyu
#include "lwip/api.h"//clyu
#include "lwip/tcpip.h"
#include "mqtt-tcp.h"
#include "lwip/dns.h"

#if LWIP_MBEDTLS_ENABLE == 1
#include "mbedtls/ssl.h"
#endif

#define TRACE(...) {printf(__VA_ARGS__);printf("\n");}//clyu

extern void dns_clear(char * hostname);

static _E_MQTT_TCP_ERRORS __map_tcp_err(err_t err);
static struct netconn * __connect(const char * hostname, uint32_t port_no, _E_MQTT_TCP_ERRORS * mqtt_err);
static _E_MQTT_TCP_ERRORS __map_ssl_err(int32_t err);

#ifdef __CC_ARM
__inline static uint32_t __tick_divider(uint32_t original_value, uint32_t divider);
#else
static inline uint32_t __tick_divider(uint32_t original_value, uint32_t divider);
#endif


static uint32_t tick_wait_divider = 1;

void mqtt_tcp_tick_divider(uint32_t divider)
{
    tick_wait_divider = divider;
}

_S_MQTT_TCP_INFO * mqtt_tcp_connect(const char * hostname, uint32_t port_no, tls_configuration_t * conf,
                                    _E_MQTT_TCP_ERRORS * mqtt_tcp_err)
{
    _S_MQTT_TCP_INFO * info = pvPortMalloc(sizeof(_S_MQTT_TCP_INFO));//clyu
#if LWIP_MBEDTLS_ENABLE == 0
    conf = 0;
#endif
    //_S_MQTT_TCP_INFO * info = pvPortMalloc(sizeof(_S_MQTT_TCP_INFO));
    //printf("mqtt_tcp_connect 00heap:%d\n",xPortGetFreeHeapSize());
    if(info)
    {
        if(conf == 0)
        {
            printf("mqtt_tcp_connect ssl_flag==0,conf==0\n");
            info->ssl_flag = 0;
            info->conn = __connect(hostname, port_no, mqtt_tcp_err);
            if(info->conn == 0)
            {
                vPortFree(info);
                info = 0;
            }
        }
        else
        {
            *mqtt_tcp_err = MQTT_TCP_ERROR_NONE;
            info->ssl_flag = 1;

            //printf("mqtt_tcp_connect 01heap:%d\n",xPortGetFreeHeapSize());
            info->ssl = lwip_tls_new(conf, NETCONN_TCP);

            //printf("mqtt_tcp_connect 02heap:%d\n",xPortGetFreeHeapSize());
            if(info->ssl)
            {
                int32_t err = lwip_tls_connect(info->ssl, hostname, port_no);

                if(err)
                {
                    lwip_tls_delete(info->ssl);
                    info->ssl = 0;

                    if(err < ERR_ARG)
                    {
                        *mqtt_tcp_err = __map_ssl_err(err);
                    }
                    else
                    {
                        *mqtt_tcp_err = __map_tcp_err(err);
                    }
                }
            }
            if(info->ssl == 0)
            {
                vPortFree(info);
                info = 0;
            }
        }
    }
    return info;
}

_E_MQTT_TCP_ERRORS mqtt_tcp_write(_S_MQTT_TCP_INFO * info, void * data, uint32_t data_len, uint32_t timeout)
{
    if(info->ssl_flag == 0)
    {
#if LWIP_SO_SNDTIMEO
        info->conn->send_timeout = __tick_divider(timeout, tick_wait_divider);
#endif
        uint32_t written = 0;
        err_t err = netconn_write_partly(info->conn, data, data_len, NETCONN_COPY, &written);

        info->lwip_err = err;
        info->mqtt_tcp_err = __map_tcp_err(err);
        return info->mqtt_tcp_err;
    }
    else
    {
        int32_t ret = lwip_tls_write(info->ssl, data, data_len, timeout);

        if(ret > 0)
        {
            ret = 0;
        }
        info->lwip_err = ret;
        info->mqtt_tcp_err = __map_ssl_err(ret);
        return info->mqtt_tcp_err;
    }
}

_E_MQTT_TCP_ERRORS mqtt_tcp_recv(_S_MQTT_TCP_INFO * info, struct netbuf ** recv, uint32_t timeout_ms)
{

    err_t err;//clyu
    if(info->ssl_flag == 0)
    {
        printf("mqtt_tcp_recv ssl_flag==0\n");
        info->conn->recv_timeout = __tick_divider(timeout_ms, tick_wait_divider);
        //err_t err = netconn_recv(info->conn, recv);//clyu
        err = netconn_recv(info->conn, recv);

        info->lwip_err = err;
        info->mqtt_tcp_err = __map_tcp_err(err);
        return info->mqtt_tcp_err;
    }
    else
    {
        int32_t ret = lwip_tls_read(info->ssl, recv, timeout_ms);
        printf("lwip_tls_read, ret=%d\n",ret);
        info->lwip_err = ret;

        if(ret < ERR_ARG)
        {
            info->mqtt_tcp_err = __map_ssl_err(ret);
        }
        else
        {
            info->mqtt_tcp_err = __map_tcp_err(ret);

            printf("info->mqtt_tcp_err:%d\n",info->mqtt_tcp_err);
        }
        return info->mqtt_tcp_err;
    }
}

_E_MQTT_TCP_ERRORS mqtt_tcp_close(_S_MQTT_TCP_INFO * info)
{
    if(info)
    {
        if(info->ssl_flag == 0)
        {
            if(info->conn)
            {
                netconn_shutdown(info->conn, 0, 1);
            }
        }
        else
        {
            if(info->ssl)
            {
                int32_t ret = lwip_tls_close(info->ssl, 0, 1);

                return __map_ssl_err(ret);
            }
        }
    }
    return MQTT_TCP_ERROR_NONE;
}

_E_MQTT_TCP_ERRORS mqtt_tcp_delete(_S_MQTT_TCP_INFO * info)
{
    if(info)
    {
        if(info->ssl_flag == 0)
        {
            if(info->conn)
            {
                netconn_delete(info->conn);
            }
        }
        else
        {
            if(info->ssl)
            {
                lwip_tls_delete(info->ssl);
            }
        }
        vPortFree(info);
    }
    return MQTT_TCP_ERROR_NONE;
}

char * mqtt_tcp_error_to_string(_E_MQTT_TCP_ERRORS err)
{
    switch(err)
    {
        case MQTT_TCP_ERROR_NONE:
            return "tcp error none";
        case MQTT_TCP_ERROR_DNS:
            return "tcp error dns";
        case MQTT_TCP_ERROR_MEMORY_ALLOC:
            return "tcp error memory allocation";
        case MQTT_TCP_ERROR_BUFFER:
            return "tcp buffer error";
        case MQTT_TCP_ERROR_TIMEOUT:
            return "tcp error timeout";
        case MQTT_TCP_ERROR_ROUTE:
            return "tcp error roouting";
        case MQTT_TCP_ERROR_VAL:
            return "tcp error value";
        case MQTT_TCP_ERROR_ABORT:
            return "tcp error abort";
        case MQTT_TCP_ERROR_RESET:
            return "tcp error reset";
        case MQTT_TCP_ERROR_CLOSED:
            return "tcp error closed";
        case MQTT_TCP_ERROR_CONNECTION:
            return "tcp error not connected";
        case MQTT_TCP_ERROR_ARG:
            return "tcp error invalid argument";
        case MQTT_TCP_ERROR_NETIF:
            return "tcp low level error, netif";
        default:
            return "tcp error undefiend";
    }
}

static _E_MQTT_TCP_ERRORS __map_tcp_err(err_t err)
{
    switch(err)
    {
        case ERR_OK:
            return MQTT_TCP_ERROR_NONE;
        case ERR_MEM:
            return MQTT_TCP_ERROR_MEMORY_ALLOC;
        case ERR_BUF:
            return MQTT_TCP_ERROR_BUFFER;
        case ERR_TIMEOUT:
            return MQTT_TCP_ERROR_TIMEOUT;
        case ERR_RTE:
            return MQTT_TCP_ERROR_ROUTE;
        case ERR_VAL:
            return MQTT_TCP_ERROR_VAL;
        case ERR_ABRT:
            return MQTT_TCP_ERROR_ABORT;
        case ERR_RST:
            return MQTT_TCP_ERROR_RESET;
        case ERR_CLSD:
            return MQTT_TCP_ERROR_CLOSED;
        case ERR_CONN:
            return MQTT_TCP_ERROR_CONNECTION;
        case ERR_ARG:
            return MQTT_TCP_ERROR_ARG;
        case ERR_IF:
            return MQTT_TCP_ERROR_NETIF;
        default:
            return  MQTT_SSL_UNDEFINED;
    }
}

static _E_MQTT_TCP_ERRORS __map_ssl_err(int32_t err)
{
#if LWIP_MBEDTLS_ENABLE == 1
    switch(err)
    {
        case 0:
            return MQTT_TCP_ERROR_NONE;
        case MBEDTLS_ERR_SSL_FEATURE_UNAVAILABLE:
            return MQTT_SSL_FEATURE_UNAVAILABLE;
        case MBEDTLS_ERR_SSL_BAD_INPUT_DATA:
            return MQTT_SSL_BAD_INPUT_DATA;
        case MBEDTLS_ERR_SSL_INVALID_MAC:
            return MQTT_SSL_INVALID_MAC;
        case MBEDTLS_ERR_SSL_INVALID_RECORD:
            return MQTT_SSL_INVALID_RECORD;
        case MBEDTLS_ERR_SSL_CONN_EOF:
            return MQTT_SSL_CONN_EOF;
        case MBEDTLS_ERR_SSL_UNKNOWN_CIPHER:
            return MQTT_SSL_UNKNOWN_CIPHER;
        case MBEDTLS_ERR_SSL_NO_CIPHER_CHOSEN:
            return MQTT_SSL_NO_CIPHER_CHOSEN;
        case MBEDTLS_ERR_SSL_NO_RNG:
            return MQTT_SSL_NO_RNG;
        case MBEDTLS_ERR_SSL_NO_CLIENT_CERTIFICATE:
            return MQTT_SSL_NO_CLIENT_CERTIFICATE;
        case MBEDTLS_ERR_SSL_CERTIFICATE_TOO_LARGE:
            return MQTT_SSL_CERTIFICATE_TOO_LARGE;
        case MBEDTLS_ERR_SSL_CERTIFICATE_REQUIRED:
            return MQTT_SSL_CERTIFICATE_REQUIRED;
        case MBEDTLS_ERR_SSL_PRIVATE_KEY_REQUIRED:
            return MQTT_SSL_PRIVATE_KEY_REQUIRED;
        case MBEDTLS_ERR_SSL_CA_CHAIN_REQUIRED:
            return MQTT_SSL_CA_CHAIN_REQUIRED;
        case MBEDTLS_ERR_SSL_UNEXPECTED_MESSAGE:
            return MQTT_SSL_UNEXPECTED_MESSAGE;
        case MBEDTLS_ERR_SSL_FATAL_ALERT_MESSAGE:
            return MQTT_SSL_FATAL_ALERT_MESSAGE;
        case MBEDTLS_ERR_SSL_PEER_VERIFY_FAILED:
            return MQTT_SSL_PEER_VERIFY_FAILED;
        case MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY:
            return MQTT_SSL_PEER_CLOSE_NOTIFY;
        case MBEDTLS_ERR_SSL_BAD_HS_CLIENT_HELLO:
            return MQTT_SSL_BAD_HS_CLIENT_HELLO;
        case MBEDTLS_ERR_SSL_BAD_HS_SERVER_HELLO:
            return MQTT_SSL_BAD_HS_SERVER_HELLO;
        case MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE:
            return MQTT_SSL_BAD_HS_CERTIFICATE;
        case MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_REQUEST:
            return MQTT_SSL_BAD_HS_SERVER_KEY_EXCHANGE;
        case MBEDTLS_ERR_SSL_BAD_HS_SERVER_KEY_EXCHANGE:
            return MQTT_SSL_BAD_HS_SERVER_KEY_EXCHANGE;
        case MBEDTLS_ERR_SSL_BAD_HS_SERVER_HELLO_DONE:
            return MQTT_SSL_BAD_HS_SERVER_HELLO_DONE;
        case MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE:
            return MQTT_SSL_BAD_HS_CLIENT_KEY_EXCHANGE;
        case MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_RP:
            return MQTT_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_RP;
        case MBEDTLS_ERR_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_CS:
            return MQTT_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_CS;
        case MBEDTLS_ERR_SSL_BAD_HS_CERTIFICATE_VERIFY:
            return MQTT_SSL_BAD_HS_CERTIFICATE_VERIFY;
        case MBEDTLS_ERR_SSL_BAD_HS_CHANGE_CIPHER_SPEC:
            return MQTT_SSL_BAD_HS_CHANGE_CIPHER_SPEC;
        case MBEDTLS_ERR_SSL_BAD_HS_FINISHED:
            return MQTT_SSL_BAD_HS_FINISHED;
        case MBEDTLS_ERR_SSL_ALLOC_FAILED:
            return MQTT_SSL_ALLOC_FAILED;
        case MBEDTLS_ERR_SSL_HW_ACCEL_FAILED:
            return MQTT_SSL_HW_ACCEL_FAILED;
        case MBEDTLS_ERR_SSL_HW_ACCEL_FALLTHROUGH:
            return MQTT_SSL_HW_ACCEL_FALLTHROUGH;
        case MBEDTLS_ERR_SSL_COMPRESSION_FAILED:
            return MQTT_SSL_COMPRESSION_FAILED;
        case MBEDTLS_ERR_SSL_BAD_HS_PROTOCOL_VERSION:
            return MQTT_SSL_BAD_HS_PROTOCOL_VERSION;
        case MBEDTLS_ERR_SSL_BAD_HS_NEW_SESSION_TICKET:
            return MQTT_SSL_BAD_HS_NEW_SESSION_TICKET;
        case MBEDTLS_ERR_SSL_SESSION_TICKET_EXPIRED:
            return MQTT_SSL_SESSION_TICKET_EXPIRED;
        case MBEDTLS_ERR_SSL_PK_TYPE_MISMATCH:
            return MQTT_SSL_PK_TYPE_MISMATCH;
        case MBEDTLS_ERR_SSL_UNKNOWN_IDENTITY:
            return MQTT_SSL_UNKNOWN_IDENTITY;
        case MBEDTLS_ERR_SSL_INTERNAL_ERROR:
            return MQTT_SSL_INTERNAL_ERROR;
        case MBEDTLS_ERR_SSL_COUNTER_WRAPPING:
            return MQTT_SSL_COUNTER_WRAPPING;
        case MBEDTLS_ERR_SSL_WAITING_SERVER_HELLO_RENEGO:
            return MQTT_SSL_WAITING_SERVER_HELLO_RENEGO;
        case MBEDTLS_ERR_SSL_HELLO_VERIFY_REQUIRED:
            return MQTT_SSL_HELLO_VERIFY_REQUIRED;
        case MBEDTLS_ERR_SSL_BUFFER_TOO_SMALL:
            return MQTT_SSL_BUFFER_TOO_SMALL;
        case MBEDTLS_ERR_SSL_NO_USABLE_CIPHERSUITE:
            return MQTT_SSL_NO_USABLE_CIPHERSUITE;
        case MBEDTLS_ERR_SSL_WANT_READ:
            return MQTT_SSL_WANT_READ;
        case MBEDTLS_ERR_SSL_WANT_WRITE:
            return MQTT_SSL_WANT_WRITE;
        case MBEDTLS_ERR_SSL_TIMEOUT:
            return MQTT_SSL_TIMEOUT;
        case MBEDTLS_ERR_SSL_CLIENT_RECONNECT:
            return MQTT_SSL_CLIENT_RECONNECT;
        case MBEDTLS_ERR_SSL_UNEXPECTED_RECORD:
            return MQTT_SSL_UNEXPECTED_RECORD;
        case MBEDTLS_ERR_SSL_NON_FATAL:
            return MQTT_SSL_NON_FATAL;
        case MBEDTLS_ERR_SSL_INVALID_VERIFY_HASH:
            return MQTT_SSL_INVALID_VERIFY_HASH;
        default:
            return MQTT_TCP_ERROR_UNDEFINED;
    }
#else
    return MQTT_TCP_ERROR_UNDEFINED;
#endif
}

static struct netconn * __connect(const char * hostname, uint32_t port_no, _E_MQTT_TCP_ERRORS * mqtt_err)
{
    struct netconn * conn = 0;
    ip_addr_t ip;
    ip_addr_t local_ip;
    err_t err = ERR_OK;
    uint32_t retry = 4;

    if(ip4addr_aton(hostname, &ip) == 0)
    {
        while((err = netconn_gethostbyname(hostname, &ip)) != ERR_OK)
        {
            TRACE("Could not resolve hostname:%s to ip, retry:%d, err:%d, ip:%x", hostname, retry, err, (uint32_t)ip.addr);
            if(--retry == 0)
            {
                *mqtt_err = MQTT_TCP_ERROR_DNS;
                return 0;
            }
        }
    }
    conn = netconn_new(NETCONN_TCP);
    if(conn == 0)
    {
        *mqtt_err = MQTT_TCP_ERROR_MEMORY_ALLOC;
        return 0;
    }
    conn->recv_timeout = __tick_divider(120000, tick_wait_divider);
#if LWIP_SO_SNDTIMEO == 1
    conn->send_timeout = 0;
#endif
    local_ip = mqtt_get_interface_ip(&ip);
    if(local_ip.addr)
    {
        netconn_bind(conn, &local_ip, 0);
    }
    TRACE("trying to connect to ip:%d.%d.%d.%d", ip4_addr1(&ip), ip4_addr2(&ip), ip4_addr3(&ip),
          ip4_addr4(&ip));
    err = netconn_connect(conn, &ip, port_no);
    if(err)
    {
        //if(dns_gethostbyname_2(hostname, &ip) == 0) {//clyu
        if(dns_gethostbyname(hostname, &ip, NULL, NULL) == 0)  //clyu
        {
            TRACE("trying to connect to ip:%d.%d.%d.%d", ip4_addr1(&ip), ip4_addr2(&ip), ip4_addr3(&ip),
                  ip4_addr4(&ip));
            err = netconn_connect(conn, &ip, port_no);
        }
        if(err)
        {
            netconn_delete(conn);
            conn = 0;
            *mqtt_err = __map_tcp_err(err);
        }
    }
    if(err)
    {
//      dns_clear(hostname);
    }
    return conn;
}

#ifdef __CC_ARM
__inline static uint32_t __tick_divider(uint32_t original_value, uint32_t divider)
#else
static inline uint32_t __tick_divider(uint32_t original_value, uint32_t divider)
#endif
{
    if(divider > 1)
    {
        if(original_value > divider)
        {
            original_value /= divider;
        }
        else if(original_value)
        {
            original_value = 1;
        }
    }
    return original_value;
}
