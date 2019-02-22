/**
    @file       mqtt-tcp.h
    @author Nishant Agrawal
    @org        Real Time Solutions Pvt. Ltd.
    @date       29th Aug 2017
    @brief  functions which create a tcp layer on top of lwIP netconn implementation to use on mqtt_client_xx functions
                    in mqtt-client.c.
    @note       The application should not call these functions as they are all called by mqtt_client_xx functions
*/
#ifndef __MQTT_TCP_H__
#define __MQTT_TCP_H__
#include "lwip/api.h"//clyu
#include "lwip/tcpip.h"
#include "lwip_tls.h"
//#include "mqtt-tcp.h"

/*!
 * enum which defines the different tcp layer errors
*/
typedef enum
{
    MQTT_TCP_ERROR_NONE,
    MQTT_TCP_ERROR_DNS,
    MQTT_TCP_ERROR_MEMORY_ALLOC,
    MQTT_TCP_ERROR_BUFFER,
    MQTT_TCP_ERROR_TIMEOUT,
    MQTT_TCP_ERROR_ROUTE,
    MQTT_TCP_ERROR_VAL,

    MQTT_TCP_ERROR_ABORT,       //fatal errors
    MQTT_TCP_ERROR_RESET,
    MQTT_TCP_ERROR_CLOSED,
    MQTT_TCP_ERROR_CONNECTION,
    MQTT_TCP_ERROR_ARG,
    MQTT_TCP_ERROR_NETIF,

    MQTT_TCP_ERROR_UNDEFINED,

    MQTT_SSL_FEATURE_UNAVAILABLE,       //14
    MQTT_SSL_BAD_INPUT_DATA,
    MQTT_SSL_INVALID_MAC,
    MQTT_SSL_INVALID_RECORD,
    MQTT_SSL_CONN_EOF,
    MQTT_SSL_UNKNOWN_CIPHER,
    MQTT_SSL_NO_CIPHER_CHOSEN,
    MQTT_SSL_NO_RNG,
    MQTT_SSL_NO_CLIENT_CERTIFICATE,
    MQTT_SSL_CERTIFICATE_TOO_LARGE,
    MQTT_SSL_CERTIFICATE_REQUIRED,
    MQTT_SSL_PRIVATE_KEY_REQUIRED,
    MQTT_SSL_CA_CHAIN_REQUIRED,
    MQTT_SSL_UNEXPECTED_MESSAGE,
    MQTT_SSL_FATAL_ALERT_MESSAGE,
    MQTT_SSL_PEER_VERIFY_FAILED,
    MQTT_SSL_PEER_CLOSE_NOTIFY,
    MQTT_SSL_BAD_HS_CLIENT_HELLO,
    MQTT_SSL_BAD_HS_SERVER_HELLO,
    MQTT_SSL_BAD_HS_CERTIFICATE,
    MQTT_SSL_BAD_HS_CERTIFICATE_REQUEST,
    MQTT_SSL_BAD_HS_SERVER_KEY_EXCHANGE,
    MQTT_SSL_BAD_HS_SERVER_HELLO_DONE,
    MQTT_SSL_BAD_HS_CLIENT_KEY_EXCHANGE,
    MQTT_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_RP,
    MQTT_SSL_BAD_HS_CLIENT_KEY_EXCHANGE_CS,
    MQTT_SSL_BAD_HS_CERTIFICATE_VERIFY,
    MQTT_SSL_BAD_HS_CHANGE_CIPHER_SPEC,
    MQTT_SSL_BAD_HS_FINISHED,
    MQTT_SSL_ALLOC_FAILED,
    MQTT_SSL_HW_ACCEL_FAILED,
    MQTT_SSL_HW_ACCEL_FALLTHROUGH,
    MQTT_SSL_COMPRESSION_FAILED,
    MQTT_SSL_BAD_HS_PROTOCOL_VERSION,
    MQTT_SSL_BAD_HS_NEW_SESSION_TICKET,
    MQTT_SSL_SESSION_TICKET_EXPIRED,
    MQTT_SSL_PK_TYPE_MISMATCH,
    MQTT_SSL_UNKNOWN_IDENTITY,
    MQTT_SSL_INTERNAL_ERROR,
    MQTT_SSL_COUNTER_WRAPPING,
    MQTT_SSL_WAITING_SERVER_HELLO_RENEGO,
    MQTT_SSL_HELLO_VERIFY_REQUIRED,
    MQTT_SSL_BUFFER_TOO_SMALL,
    MQTT_SSL_NO_USABLE_CIPHERSUITE,
    MQTT_SSL_WANT_READ,
    MQTT_SSL_WANT_WRITE,
    MQTT_SSL_TIMEOUT,
    MQTT_SSL_CLIENT_RECONNECT,
    MQTT_SSL_UNEXPECTED_RECORD,
    MQTT_SSL_NON_FATAL,
    MQTT_SSL_INVALID_VERIFY_HASH,

    MQTT_SSL_UNDEFINED,

} _E_MQTT_TCP_ERRORS;

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

typedef struct
{
    //!union pointer the ssl context or the netconn context, as being used by application.
    union
    {
        tls_context_t * ssl;
        struct netconn * conn;
    };
    _E_MQTT_TCP_ERRORS mqtt_tcp_err;    //!tcp layer error as mapped to the above enum
    err_enum_t lwip_err;                            //!lwIP layer error, error codes as provided by lwIP library
    uint16_t ssl_flag;                              //!flag if 1, ssl is being used, else conn is being used and ssl is disabled
} _S_MQTT_TCP_INFO;

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

/**
    @fn         mqtt_tcp_tick_divider
    @brief  Used to divide the internal ticks which is in ms, to the os tick rate.
    @param  divider         the number by which the internal ticks is to be divided

    @see        mqtt_tcp_write
    @note       If the function is not called, the divider will be set to 1
    @eg         mqtt_tcp_tick_divider(10)
*/
void mqtt_tcp_tick_divider(uint32_t divider);

/**
    @fn         mqtt_tcp_connect
    @brief  function used to connect to the server passed as a parameter
    @param  hostname            the name or IP of the server to which we need to connect
    @param  port_no             the port number to connect to
    @param  conf                    the tls confiuration to be used. Check lwip_tls_new_conf in lwip_tls.h
    @param  err                     if the pointer returned is 0, this might give an insight into the error that occured
    @return pointer to the formed structure with necessary information if the connection is successfull

    @see        lwip_tls_new_conf
    @see        mqtt_tcp_write
    @note       For all future read and write the pointer that is passed is used. The whole implementation is hidden into the
                    mqtt-client.c implementation
    @eg         mqtt_tcp_connect("mqtt.flespi.io", 1883, 0, &err);
*/
_S_MQTT_TCP_INFO * mqtt_tcp_connect(const char * hostname, uint32_t port_no, tls_configuration_t * conf, _E_MQTT_TCP_ERRORS * err);

/**
    @fn         mqtt_tcp_write
    @brief  function used to write the mqtt data called from mqtt_client_xx functions.
    @param  tcp_info            pointer to the structure returned by mqtt_tcp_connect which defines the connection
    @param  data                    pointer to the mqtt data that needs to be transmitted
    @param  data_len            the size of the data in the pointer mentioned above
    @param  timeout             the wait time to transmit the data in milliseconds
    @return the enum error, if MQTT_TCP_ERROR_NONE transmission was successfull

    @see        mqtt_tcp_connect
    @see        mqtt_client_publish
    @note       this handles both the plain and tls layers
    @eg         mqtt_tcp_write(tcp_info, pub_data, publish_len, 10000);
*/
_E_MQTT_TCP_ERRORS mqtt_tcp_write(_S_MQTT_TCP_INFO * tcp_info, void * data, uint32_t data_len, uint32_t timeout);

/**
    @fn         mqtt_tcp_recv
    @brief  function used to receive the data, implementation similar to netconn_recv
    @param  tcp_info            pointer to the structure returned by mqtt_tcp_connect which defines the connection
    @param  recv                    address to the pointer where the received netbuf will be written by this function
    @param  timeout             the wait time to receive the data, if 0, wait forever(not the best idea)
    @return the enum error, if MQTT_TCP_ERROR_NONE receive was successfull

    @see        mqtt_tcp_connect
    @see        netconn_recv
    @note
    @eg         mqtt_tcp_recv(tcp_info, &recv, 60000);
*/
_E_MQTT_TCP_ERRORS mqtt_tcp_recv(_S_MQTT_TCP_INFO * tcp_info, struct netbuf ** recv, uint32_t timeout);

/**
    @fn         mqtt_tcp_close
    @brief  function to close the tcp connection with the server, established by mqtt_tcp_connect
    @param  tcp_info            pointer to the structure returned by mqtt_tcp_connect which defines the connection
    @return the enum error, if MQTT_TCP_ERROR_NONE, close was successfull

    @see        mqtt_tcp_connect
    @see        mqtt_tcp_delete
    @note       this will only close the connection from the this side and noot wait for the connection to be closed from the
                    remote end. This is done coz, in mqtt_client, a receive process (_mqtt_recv_process) is always running
                    waiting to receive the data and without enabling full duplex implementation in lwIP, we might end with
                    fault conditions. If the connection is not closed by the server within a limited time, it might be a good idea
                    to delete the connection and do a connection again by calling mqtt_tcp_connect.
    @eg         mqtt_tcp_close(tcp_info)
*/
_E_MQTT_TCP_ERRORS mqtt_tcp_close(_S_MQTT_TCP_INFO * tcp_info);

/**
    @fn         mqtt_tcp_delete
    @brief  function to delete the tcp connection with the server.
    @param  tcp_info            pointer to the structure returned by mqtt_tcp_connect which defines the connection
    @return the enum erro, if MQTT_TCP_ERROR_NONE, delete was successfull

    @see        mqtt_tcp_connect
    @see        mqtt_tcp_close
    @note       This will also close the connection if not already done. The passed pointer should not be used after this call.
    @eg         mqtt_tcp_delete(tcp_info);
*/
_E_MQTT_TCP_ERRORS mqtt_tcp_delete(_S_MQTT_TCP_INFO * tcp_info);

/**
    @fn         mqtt_tcp_error_to_string
    @brief  function used during debug process which will map the enums to string
    @param  err                     enum values of the errors
    @return pointer to the string that best defines the error

    @eg         mqtt_tcp_error_to_string(MQTT_TCP_ERROR_DNS);
*/
char * mqtt_tcp_error_to_string(_E_MQTT_TCP_ERRORS err);

/**
    @fn         mqtt_get_interface_ip
    @brief  this function needs to be defined by the application.
    @param  dest_ip             IP to the server to which the tcp connection is to be made
    @return the device IP address whose netif is to be used. If only one connection is present, 0 can be returned

    @see        mqtt_tcp_connect
    @note       This function needs to pass the local IP address on the basis of the application requirement and the
                    destination IP address. It is to be used when you have multiple network connections (netif) running. If only
                    one connection is present, 0 can be returned.
    @eg
ip_addr_t mqtt_get_interface_ip(ip_addr_t * dest)
{
    return ip_addr_any;
}

ip_addr_t mqtt_get_interface_ip(ip_addr_t * dest)
{
    if(ip4_addr_netcmp(&eth_ip, dest_ip, &eth_subnet))
    {
        return &eth_ip
    }
    else
    {
        return ip_addr_any;
    }
}
*/
extern ip_addr_t mqtt_get_interface_ip(ip_addr_t * dest_ip);

/**
    @fn         mqtt_tcp_error_is_fatal
    @brief  to check if the error occured is critical to decide on the future action to take in case of error
    @param  e               tcp error that has occured
    @return 1 if the error is critical, else 0
*/
__inline static uint32_t mqtt_tcp_error_is_fatal(_E_MQTT_TCP_ERRORS e)
{
    if((e < MQTT_TCP_ERROR_UNDEFINED) && (e > MQTT_TCP_ERROR_VAL))
    {
        return 1;
    }
    else if((e < MQTT_SSL_UNDEFINED) && (e >= MQTT_SSL_FEATURE_UNAVAILABLE))
    {
        return 1;
    }
    return 0;
}
#endif
