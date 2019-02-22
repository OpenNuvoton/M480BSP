/**
    @file       lwip_tls.h
    @author Nishant Agrawal
    @org        Real Time Solutions Pvt. Ltd.
    @date       19/4/2018
    @brief  Header file to the tls library integration with lwIP
*/
#ifndef __NET_LWIP_H__
#define __NET_LWIP_H__
#include <stdint.h>
#include "lwip/tcpip.h"     //! header file of the lwIP library

#define     LWIP_MBEDTLS_ENABLE     1//clyu

/**
    @todo       session caching, ciphersuite configuration, protocol configuration, ssl server implementation
    @note       Initial tests show that the tls processing tasks might need stack of around 1000 with FreeRTOS.
*/

typedef enum
{
    TLS_AUTH_SSL_VERIFY_NONE,
    TLS_AUTH_SSL_VERIFY_OPTIONAL,
    TLS_AUTH_SSL_VERIFY_REQUIRED,
} _E_TLS_AUTHENTICATION_TYPE;

typedef enum
{
    ENDNODE_CLIENT,
    ENDNODE_SERVER,
} _E_TLS_ENDNODE_TYPE;

typedef void * tls_configuration_t;
typedef void * tls_context_t;

#if LWIP_MBEDTLS_ENABLE == 1
/**
    @fn         lwip_tls_init_tick_divider
    @brief  needed especially for esp sdk, as the tick is not 1 ms. To set the tick divider which is used with OS functions for wait.
    @param  divider                 the value with which the division needs to be done.

    @note       call this before doing anything else.
    @eg         lwip_tls_init_tick_divider(5);
*/
void lwip_tls_init_tick_divider(uint32_t divider);

/**
    @fn         lwip_tls_init
    @brief  this function needs to be called before working on tls
*/
void lwip_tls_init(void);

/**
    @fn         lwip_tls_new_conf
    @brief  will setup a new configuration

    @param  auth            check enum _E_TLS_AUTHENTICATION_TYPE, this sets on how to deal with the certificate verification
    @param  endnode     check enum _E_TLS_ENDNODE_TYPE, this defines the working, whether it is client or server

    @return                     0 on failure, the pointer to the configuration on success. This needs to be used when setting up the context

    @see        lwip_tls_add_ceritificate
    @see        lwip_tls_new
    @see        lwip_tls_init
    @see        lwip_tls_delete_conf

    @note       need to call lwip_tls_init before calling this
    @eg         lwip_tls_new_conf(TLS_AUTH_SSL_VERIFY_REQUIRED, ENDNODE_CLIENT);
*/
tls_configuration_t * lwip_tls_new_conf(_E_TLS_AUTHENTICATION_TYPE auth, _E_TLS_ENDNODE_TYPE endnode);

/**
    @fn         lwip_tls_add_certficate
    @brief  will add the certificate to the configuration pointer passed
    @param  conf            pointer to the configuration as returned by lwip_tls_new_conf
    @param  cert            pointer to the array holding the certificate
    @param  cert_len    length of the certificate. The length must include the null pointer, eg strlen(cert) + 1
    @return                     0 if the certificate was added successfully, else the error code provided by the mbedtls library

    @see        lwip_tls_new_conf
    @note       call this function repeatedly to add multiple certificates. make sure that the cert_len includes the null as well.
    @note       if you are going to hardcode the certificate it is better to make it <!const static char * cert
    @eg         lwip_tls_add_certificate(conf, ca_certificate, strlen(ca_certificate) + 1);
*/
int32_t lwip_tls_add_certificate(tls_configuration_t * conf, const uint8_t * cert, uint32_t cert_len);

/**
    @fn         lwip_tls_new
    @brief  this function will create a new context to use for ssl communication with the desired server
    @param  conf            pointer to the configuration which the ssl context will use
    @param  type            the connection type, used from lwip, check enum netconn_type. currently only NETCONN_TCP is supported

    @return                     0 in case of failure, else the pointer to the context

    @see        lwip_tls_new_conf
    @see        lwip_tls_delete
    @note       equivalent to netconn as used when dealing with lwip. all the communication with the server will be based on the
                    returned pointer
    @eg         lwip_tls_new(conf, NETCONN_TCP);
*/
enum netconn_type_t;//clyu
//tls_context_t * lwip_tls_new(tls_configuration_t * conf, enum netconn_type_t type);//clyu
tls_context_t * lwip_tls_new(tls_configuration_t * conf, int type);//clyu

/**
    @fn         lwip_tls_bind
    @brief  to bind the lwip connection to an specific local ip and port. this function is optional and need not be called
    @param  ssl             pointer to the ssl context
    @param  addr            local ip to bind the connection to. pass 0 if any ip can be used
    @param  port            the port which needs to be
    @return                     redundent, 0 is returned

    @see        lwip_tls_new
    @see        lwip_tls_connect
    @note       this is optional and not required, similar to netconn_bind. need to call before lwip_tls_connect if you want a
                    specific port and/or ip
    @eg         lwip_tls_bind(ssl, 0, 123);
*/
int32_t lwip_tls_bind(tls_context_t * ssl, const ip_addr_t * addr, uint32_t port);

/**
    @fn         lwip_tls_connect
    @brief  will start a tcp connection with the server and work on handshake
    @param  ssl             pointer to the ssl context
    @param  server      pointer to the server to which the connection is to be done
    @param  port            the port number to which the connection is to be done

    @return                     return 0 on success, if the return value is in the range of 1 to -16, check err.h from the lwip library.
                                        for other cases, check the mbedtls error codes

    @see        lwip_tls_new
    @note       if the connection fails in the lwip layer, check err.h for error co-relation. add ERR_DNS_FAIL if not defined with value 1
    @eg         lwip_tls_connect(ssl, "hardware.wscada.net", 8883);
*/
int32_t lwip_tls_connect(tls_context_t * ssl, const char * server, uint32_t port);

/**
    @fn         lwip_tls_write
    @brief  wrapper function for ssl_write function provided by mbedtls library.
    @param  ssl             pointer to the ssl context
    @param  data            pointer to the data that needs to be transmitted
    @param  len             holds the length of data that needs to be transmitted
    @param  timeout     0 if you want to wait forever, else the wait time to receive in ms
    @return                     returns the error codes as returned by the ssl write function which is less than 0,
                                        else returns the number of bytes written

    @see        lwip_tls_connect
    @see        lwip_tls_read
    @eg         lwip_tls_write(ssl, data, len);
*/
int32_t lwip_tls_write(tls_context_t * ssl, const void * data, uint32_t len, uint32_t timeout);

/**
    @fn         lwip_tls_read
    @brief  wrapper function for ssl read function provided by the mbedtls library
    @param  ssl             pointer to the ssl context
    @param  _buf            address to the pointer to the netbuf which hold the netbuf if data was recieved, similar to netconn_recv
    @param  timeout     0 if you want to wait forever, else the wait time to receive in ms
    @return                     0 for success, -1 for memory allocation error, and error returned by the mbedtls_ssl_read function

    @see        lwip_tls_write
    @note       the netbuf is allocated inside the function and the address is passed to the _buf parameter. it is the
                    responsibility of the application to delete the netbuf.
    @eg         lwip_tls_read(ssl, &buf);
*/
struct netbuf;//clyu
int32_t lwip_tls_read(tls_context_t * ssl, struct netbuf ** _buf, uint32_t timeout);

/**
    @fn         lwip_tls_close
    @brief  to notify the remote server to close the connection and to close the connection in the netconn layer
    @param  ssl                 pointer to the ssl context
    @param  close_recv  flag to indicate to close the connection so that nothing can be received
    @param  close_tx        flag to indicate to close the connection so that nothing can be transmitted
    @return                     0 for success, error codes as returned by mbedtls_ssl_close_notify

    @see        mbedtls_ssl_close_notify
    @see        lwip_tls_delete
    @see        lwip_tls_reset
    @note       If this function returns something other than 0 or MBEDTLS_ERR_SSL_WANT_READ/WRITE, then the ssl context
                    becomes unusable, and you should either free it or call \c lwip_tls_reset() on it before re-using it for
                    a new connection; the current connection must be closed.
    @note       If any other thread is waiting on receive and the connection is to be closed, only close for tx, ie. only
                    set the flag for close_tx and not for close_recv. If no threads are waiting on receive from the connection
                    set both the flags.
    @eg         lwip_tls_close(ssl);
*/
int32_t lwip_tls_close(tls_context_t * ssl, uint32_t close_recv, uint32_t close_tx);

/**
    @fn         lwip_tls_reset
    @brief  to reset the ssl context, need to call if lwip_tls_close fails
    @param  ssl             pointer to the ssl context
    @return                     0 for success, error codes returned by mbedtls_ssl_session_reset().

    @see        mbedtls_ssl_session_reset
    @see        lwip_tls_close
    @see        lwip_tls_delete
    @note       this functions needs to be called if lwip_tls_close fails and you wish to reuse the context again. If not its
                    better to delete the context by calling lwip_tls_delete
    @eg         lwip_tls_reset(ssl);
*/
int32_t lwip_tls_reset(tls_context_t * ssl);

/**
    @fn         lwip_tls_delete
    @brief  to clear and delete the ssl context
    @param  ssl             pointer to the ssl context
    @return                     0 for success, error codes as returned by mbedtls_ssl_close_notify

    @see        lwip_tls_close
    @see        lwip_tls_reset
    @see        lwip_tls_new
    @note       this will clear and free all the allocated memory during lwip_tls_new. this will free all and the context will no
                    longer be usable
    @eg         lwip_tls_delete(ssl);
*/
int32_t lwip_tls_delete(tls_context_t * ssl);

/**
    @fn         lwip_tls_delete_conf
    @brief  to free and delete the configuration
    @param  conf            pointer to the configuration as returned by lwip_tls_new_conf
    @return                     returns 0

    @see        lwip_tls_new_conf
    @note       to delete and clear the configuration as setup by calling lwip_tls_new_conf. After calling this the conf will no
                    longer be usable. Also make sure that all the ssl contexts have been closed before doing this
    @eg         lwip_tls_delete_conf(conf);
*/
int32_t lwip_tls_delete_conf(tls_configuration_t * conf);

#else   /*LWIP_MBEDTLS_ENABLE*/

#define lwip_tls_init()
#define lwip_tls_new_conf(x, y)                             0
#define lwip_tls_add_certificate(x, y, z)           -1
#define lwip_tls_new(x, y)                                      0
#define lwip_tls_bind(x, y, z)                              -1
#define lwip_tls_connect(x, y, z)                           -1
#define lwip_tls_write(x, y, z, a)                      -1
#define lwip_tls_read(x, y, z)                              -1
#define lwip_tls_close(x, y, z)                             -1
#define lwip_tls_reset(x)                                           -1
#define lwip_tls_delete(x)                                      -1
#define lwip_tls_delete_conf(x)                             -1

#endif  /*LWIP_MBEDTLS_ENABLE*/

#endif
