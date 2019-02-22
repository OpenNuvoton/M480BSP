/**
    @file       mqtt-client.h
    @author Nishant Agrawal
    @org        Real Time Solutions Pvt. Ltd.
    @date       30th Aug 2017
    @brief  functions which create application layer for client functions to use on top of paho provided mqtt
                    client related functions.
    @note       It supports both plain and tls layers of communication as implemented using mqtt-tcp, which handles
                    the communicationn layer

    @note       With every mqtt_client_connect, a _mqtt_recv_process is created which will handle the receive process after
                    the connection is successfully established
    @todo       add implmenetation for wildcards in subscribe topic handling while receiving messages
*/
#ifndef __MQTT_CLIENT_H__
#define __MQTT_CLIENT_H__
#include "mqtt-tcp.h"
#include "MQTTPacket.h"

typedef enum
{
#define DEF_MQTT_ERROR(type, str)   MQTT_ERROR_##type,
#include "mqtt-client-error.h"
    MQTT_ERROR_UNDEFINED,
} _E_MQTT_ERRORS;

typedef struct _s_mqtt_subscribe_info
{
    char * topic;
    uint32_t (*upcall_func)(struct _s_mqtt_subscribe_info * sinfo, uint32_t qos, uint32_t dup, uint32_t retained, void * payload, uint32_t payload_len);
    struct _s_mqtt_subscribe_info * next;
    uint8_t qos;
    uint8_t granted_qos;
} _S_MQTT_SUBSCRIBE_INFO;

typedef struct _s_mqtt_clinet_info
{
    _S_MQTT_TCP_INFO * ti;
    tls_configuration_t * ssl_conf;

    MQTTPacket_connectData * options;
    void (*connection_fail_upcall)(struct _s_mqtt_clinet_info *);
    void * upcall_arg;

    _S_MQTT_SUBSCRIBE_INFO * subs_info;

    uint8_t * buffer;
    uint32_t buffer_size;
    uint32_t tcp_send_wait_time_ms;
    uint32_t tcp_recv_wait_time_ms;
    uint32_t last_publish_tick;

    const char * hostname;
    xSemaphoreHandle tx_control;
    xSemaphoreHandle rx_semphr;
    struct netbuf * recv_buf;

    uint8_t current_pub_qos;
    uint8_t session_present;
    _E_MQTT_TCP_ERRORS tcp_err;
    _E_MQTT_ERRORS mqtt_err;
    uint8_t current_pub_retain;
    uint8_t subscribe_topic_count;
    uint8_t _packet_id;
    volatile uint8_t kill_recv_process;

    uint16_t keep_alive_secs;
    uint16_t port_no;
} _S_MQTT_CLIENT_INFO;

/**
    @fn         mqtt_client_tick_divider
    @brief  Used to divide the internal ticks which is in ms, to the os tick rate.
    @param  divider         the number by which the internal ticks is to be divided

    @see        mqtt_tcp_tick_divider
    @note       If the function is not called, the divider will be set to 1. This function needs to be called before
                    calling any other function on this file.
    @eg         mqtt_client_tick_divider(10)
*/
void mqtt_client_tick_divider(uint32_t divider);

/**
    @fn         mqtt_client_init
    @brief  the function to initialize the mqtt client pointer
    @param  buffer_size                 size of the buffer which will be used to build mqtt packets for transmission
    @param  tcp_send_timeout        the max time in milliseconds to wait to transmit the packet, 0 to wait forever
    @param  tcp_recv_timeout        the max time in milliseconds to wait to receive a packet, 0, to wait forever
    @param  connect_failupcall  if the connection fails in the future, after successfully connecting while calling
                                                            this function, _recv_process will try to reconnect and in case of failure, shut
                                                            everything down and call this function to inform the application
    @return pointer to client_info which will hold all the information related to the connection, 0 incase of failure

    @see        mqtt_client_connect
    @note       need to call this function to get the pointer to the client structure which will be used for all future
                    functions
    @eg         mqtt_clientn_init(512, 10000, 30000, 0);
*/
_S_MQTT_CLIENT_INFO * mqtt_client_init(uint32_t buffer_size, uint32_t tcp_send_timeout, uint32_t tcp_recv_timeout, void (*connect_failupcall)(_S_MQTT_CLIENT_INFO *));

/**
    @fn         mqtt_client_is_connected
    @brief  to check if the connection to the server is still active or not
    @param  cinfo                   pointer to the client info
    @return 1 if the connection is active, 0 in case the connection to the server is down

    @see        mqtt_client_init
    @see        mqtt_client_connect
*/
uint32_t mqtt_client_is_connected(_S_MQTT_CLIENT_INFO * cinfo);

/**
    @fn         mqtt_client_connect
    @brief  function to connect to the mqtt server
    @param  cinfo               pointer to the client structure returned when the init function is called
    @param  hostname        the name of the mqtt server or IP address that has to be connected
    @param  port                the port number to connect to the server
    @param  options         pointer to the options as returned by the function mqtt_client_connect_options
    @param  conf                pointer to the tls_configuration_t if encryption is to be used, else 0
    @return enum to mqtt errors as returned, MQTT_ERROR_NONE is there are not errors

    @see        mqtt_client_init
    @see        mqtt_client_connect_options
    @note       this function needs to called before subscribing to a topic or publishing to a topic and after calling
                    mqtt_client_init and mqtt_client_will_options
    @eg         mqtt_client_connect(cinfo, "mqtt.flespi.io", 1883, options);
*/
_E_MQTT_ERRORS mqtt_client_connect(_S_MQTT_CLIENT_INFO * cinfo, const char * hostname, uint32_t port, MQTTPacket_connectData * options, tls_configuration_t * conf);

/**
    @fn         mqtt_client_connect_options
    @brief  function to configure different connection options and returns pointer to the created options
    @param  client_id               pointer to the client id as used during connection
    @param  alive_interval  the interval to send keep alive packets in seconds, 0 to disable
    @param  clean_session       check mqtt documentation to understand clean_session, 1 or 0
    @param  username                pointer to the username, if required by the server for authentication, 0 if not needed
    @param  password                pointer to the password, if required by the server for authentication, 0 if not needed
    @return pointer to the options structure as created by this function, 0 in case of failure

    @see        mqtt_client_connect
    @note       this function needs to be called before calling mqtt_client_connect, as it will create the options pointer
    @eg         mqtt_client_connect_options("12345678", 30, 1, "username", "password");
*/
MQTTPacket_connectData * mqtt_client_connect_options(char * client_id, uint32_t alive_interval, uint32_t clean_session, const char * username, const char * password);

/**
    @fn         mqtt_client_will_options
    @brief  this will fill in the will information in the connect options pointer created by the above function
    @param  c                       pointer to the connect options, this needs to be created by the function mqtt_client_connect_options
    @param  topic               will topic
    @param  msg                 will message
    @param  retained        option to enable if the will message is to be retained or not
    @param  qos                 the qos level of the will message
    @return none

    @see        mqtt_client_connect_options
    @see        mqtt_client_connect
    @note       this function needs to called after mqtt_client_connect_options and before calling mqtt_client_connect.
                    This function is optional and need not be called if the will msg is not required
    @eg         mqtt_clinet_will_options(c, "my/death", "I am dead", 0, 1);
*/
void mqtt_client_will_options(MQTTPacket_connectData * c, char * topic, char * msg, uint32_t retained, uint32_t qos);

/**
    @fn         mqtt_client_tcp_close
    @brief  to close the tcp connection without mqtt disconnect
    @param  info                    pointer to the clinet info as created by mqtt_client_init
    @return enum to mqtt errors as returned, MQTT_ERROR_NONE is there are not errors

    @see        mqtt_client_connect
    @see        mqtt_client_tcp_delete
    @see        mqtt_client_disconnect
    @note       This function will only close the connection from this side and wait for the server to close its
                    connection. This will not do a mqtt disconnect so will message might be sent. A call to this function
                    will trigger a connection close from server which in turn will trigger a re-connect from the internal
                    process of mqtt_client(_mqtt_recv_process). If you don't want the reconnect to take place call
                    mqtt_client_tcp_delete
    @eg         mqtt_client_tcp_close(cinfo);
*/
_E_MQTT_ERRORS mqtt_client_tcp_close(_S_MQTT_CLIENT_INFO * info);

/**
    @fn         mqtt_client_tcp_delete
    @brief  function to close the tcp connection with the server and delete the pointer structure
    @param  info                pointer to the client structure
    @param  force               if this flag is set, it will make sure that the delete is not blocked by netconn being
                                            used by any other function
    @return enum to mqtt errors as returned, MQTT_ERROR_NONE is there are not errors

    @see        mqtt_client_tcp_close
    @see        mqtt_client_connect
    @note       this function will close and delete the tcp layer as being worked by from mqtt_tcp_xx functions. This
                    will not delete the mqtt clinet layer. In case of problems with publish, it is a safer option to delete
                    the tcp connection and reconnect again usin mqtt_client_connect
    @eg         mqtt_client_tcp_delete(cinfo, 1);
*/
_E_MQTT_ERRORS mqtt_client_tcp_delete(_S_MQTT_CLIENT_INFO * info, uint32_t force);

/**
    @fn         mqtt_client_publish
    @brief  to publish data to a topic on the connection created
    @param  info                pointer to the client connection structure
    @param  _topic          pointer to the topic to which the data is to be published
    @param  payload         pointer to the data to be published
    @param  payload_len holds the size of the payload
    @param  retry               defines the number of retries to be done to publish the data in case of failure
    @return enum to mqtt errors as returned, MQTT_ERROR_NONE is there are not errors

    @see        mqtt_client_connect
    @see        mqtt_client_set_publish_info
    @note       If mqtt_client_publish_info is not called, the default qos of 0 and retain of 0 is used.
    @eg         mqtt_client_publish(cinfo, "my/data", "this is a test", 14, 2);
*/
_E_MQTT_ERRORS mqtt_client_publish(_S_MQTT_CLIENT_INFO * info, char * _topic, const void * payload, uint32_t payload_len, uint32_t retry);

/**
    @fn         mqtt_client_set_publish_info
    @brief  to set the qos and retain falgs for the data to be published
    @param  info                pointer to the client strructure
    @param  qos                 to set the qos of the next data to publish, 0, 1 and 2 as per the mqtt protocol
    @param  retain          to set the retain flag for the next data to publish, 0 and 1 as per the mqtt protocol
    @return none

    @see        mqtt_client_publish
    @note       if you want to change the qos and/or retain flag, call this function before calling the publish function
    @eg         mqtt_client_set_publish_info(cinfo, 2, 0);
*/
void mqtt_client_set_publish_info(_S_MQTT_CLIENT_INFO * info, uint32_t qos, uint32_t retain);

/**
    @fn         mqtt_client_disconnect
    @brief  to disconnect the mqtt session.
    @param  info                pointer to the client structure
    @param  reconnect       if 1 is passed, the _mqtt_recv_process will do a reconnect, in case of 0, the _mqtt_recv_process
                                            will be deleted and tcp connection will also be deleted and closed
    @return enum to mqtt errors as returned, MQTT_ERROR_NONE is there are not errors

    @see        mqtt_client_connect
    @see        mqtt_client_delete
    @note       if the mqtt is disconnected, it was observed that the mqtt server will close the tcp connection. Thus
                    a direct tcp close is not performed.
    @eg         mqtt_client_disconnect(cinfo, 0);
*/
_E_MQTT_ERRORS mqtt_client_disconnect(_S_MQTT_CLIENT_INFO * info, uint32_t reconnect);

/**
    @fn         mqtt_client_delete
    @brief  to clean up and delete the client struture
    @param  info                pointer to the client structure
    @return enum to mqtt errors as returned, MQTT_ERROR_NONE is there are not errors

    @see        mqtt_client_disconnect
    @see        mqtt_client_connect
    @note       This will do a tcp close, delete and all the clean ups required to free the memory. After that it will
                    also delete the pointer passed. So do not use the passed variable after calling this function.
    @eg         mqtt_client_delete(cinfo);
*/
_E_MQTT_ERRORS mqtt_client_delete(_S_MQTT_CLIENT_INFO * info);

/**
    @fn         mqtt_client_subscribe
    @brief  to add topic to subscribe for the client connection
    @param  info                            pointer to the client structure
    @param  subscribe_topic     pointer to the topic to subsribe, wildcards are not supported
    @param  qos                             the qos level to use to subscribe to the topic
    @param  subscribe_func      upcall function which will be called when a message is recieved for this topic
                        @param  sinfo                   pointer to the subscribe topic info
                        @param  qos                     the qos level with which the message is received
                        @param  dup                     set if the received message is a duplicate
                        @param  retained            set if the received message was in the retained state
                        @param  payload             pointer to the buffer holding the message
                        @param  payload_len     holds the size of the data in the pointer payload
    @return enum to mqtt errors as returned, MQTT_ERROR_NONE is there are not errors

    @see        mqtt_client_unsubscribe
    @see        mqtt_client_connect
    @note       this function will make sure that the topic is subscribed. If the message is received for any
                    subscribed topic, the defined upcall function will be called.
                    ***Do not call any mqtt_client_xx functions from the upcall functions and exit it asap.
                    ***wildcards in the subscribe are not supported
                    ***You can use same function or different functions for upcall with each topic
    @eg         mqtt_client_subscribe(cinfo, "my/topic/subs", 1, _upcall_func);
*/
_E_MQTT_ERRORS mqtt_client_subscribe(_S_MQTT_CLIENT_INFO * info, char * subscribe_topic, int32_t qos,
                                     uint32_t (*subscribe_func)(_S_MQTT_SUBSCRIBE_INFO * sinfo, uint32_t qos, uint32_t dup, uint32_t retained, void * payload, uint32_t payload_len));

/**
    @fn         mqtt_client_unsubscribe
    @brief  to unsubscribe a topic that has already been subscribed
    @param  info                pointer to the client structure
    @param  stopic          the topic to unsubscribe
    @return enum to mqtt errors as returned, MQTT_ERROR_NONE is there are not errors

    @see        mqtt_client_subscribe
    @see        mqtt_client_connect
    @note       this will unsubscribe the topic if it has been subscribed. If the topic is not
                    inside the structure, nothing will be done.
    @eg         mqtt_client_unsubsscribe(cinfo, "my/topic/subs");
*/
_E_MQTT_ERRORS mqtt_client_unsubscribe(_S_MQTT_CLIENT_INFO * info, char * stopic);

/**
    @fn         mqtt_client_error_to_string
    @brief  string print function for the error that is passed
    @param  err             the error from the enum
    @return pointer to the string that relates to the error

    @note       used during debug
*/
const char * mqtt_client_error_to_string(_E_MQTT_ERRORS err);

/**
    @fn         mqtt_client_upcall_argument
    @brief  to add an upcall argument to to use when the upcall function is called when the connection to the server is down
    @param  info                pointer to the client structure
    @param  arg                 pointer to the argument which will be linked to the client structure
    @return none

    @see        mqtt_client_init
    @note       this is optional and needed if the same upcall function is used by different mqtt client connections.
                    the passed argument is saved to the variable upcall_arg and to be used from the structure pointer
                    directly.
*/
void mqtt_client_upcall_argument(_S_MQTT_CLIENT_INFO * info, void * arg);
#endif
