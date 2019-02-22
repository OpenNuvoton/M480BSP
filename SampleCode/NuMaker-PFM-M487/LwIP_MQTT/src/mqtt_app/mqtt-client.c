/**
    @file       mqtt-client.c
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
#include "NuMicro.h"//clyu
#include "mqtt-client.h"
#include "lwip_tls.h"
#include "lwip/api.h"//clyu
#include "lwip/debug.h"//clyu
#include <string.h>
#include <stdlib.h>

__inline static _E_MQTT_ERRORS __tcp_connect(_S_MQTT_CLIENT_INFO * info, const char * hostname, uint32_t port, tls_configuration_t * conf);
static void _mqtt_recv_process(void * pv) __attribute__((noreturn));
__inline static _E_MQTT_ERRORS __map_connack_error(uint32_t err);
static struct netbuf * __get_received_netbuf(_S_MQTT_CLIENT_INFO * info);
static _E_MQTT_ERRORS _get_transmit_control(_S_MQTT_CLIENT_INFO * info, uint32_t wait_ms);
static void _release_transmit_control(_S_MQTT_CLIENT_INFO * info);
static _E_MQTT_ERRORS _transmit_data(_S_MQTT_CLIENT_INFO * info, void * data, uint32_t data_len, uint32_t retry);
static void __fillup_mqttstring(MQTTString * s, const char * data);
static uint8_t __packet_id(uint8_t * pkt_id);
__inline static uint32_t __tick_divider(uint32_t tick, uint32_t divider);

int MQTTPacket_get_type(unsigned char *data, int len);
static uint32_t tick_wait_divider = 1;

void mqtt_client_tick_divider(uint32_t divider)
{
    tick_wait_divider = divider;
}

_S_MQTT_CLIENT_INFO * mqtt_client_init(uint32_t buffer_size, uint32_t tcp_send_timeout,
                                       uint32_t tcp_recv_timeout, void (*failupcall)(_S_MQTT_CLIENT_INFO *))
{
    _S_MQTT_CLIENT_INFO * info = pvPortMalloc(sizeof(_S_MQTT_CLIENT_INFO));

    if(info)
    {
        memset(info, 0, sizeof(_S_MQTT_CLIENT_INFO));
        info->buffer = pvPortMalloc(buffer_size);
        info->rx_semphr = xSemaphoreCreateBinary();
        if((info->buffer == 0) || (info->rx_semphr == 0))
        {
            vPortFree(info->buffer);
            vSemaphoreDelete(info->rx_semphr);
            vPortFree(info);
            info = 0;
        }
        else
        {
            info->buffer_size = buffer_size;
            info->tcp_recv_wait_time_ms = tcp_recv_timeout;
            info->tcp_send_wait_time_ms = tcp_send_timeout;
            info->connection_fail_upcall = failupcall;
        }
    }
    TRACE("mqtt_client_init Heapsize:%d", xPortGetFreeHeapSize());
    return info;
}

uint32_t mqtt_client_is_connected(_S_MQTT_CLIENT_INFO * cinfo)
{
    return (cinfo->tx_control > 0);
}

MQTTPacket_connectData * mqtt_client_connect_options(char * client_id, uint32_t alive_interval,
        uint32_t clean_session, const char * username, const char * password)
{
    MQTTPacket_connectData * c = pvPortMalloc(sizeof(MQTTPacket_connectData));

    if(c)
    {
        static const uint8_t mqtc_id[] = {'M', 'Q', 'T', 'C'};

        memset(c, 0, sizeof(MQTTPacket_connectData));
        memcpy(c->struct_id, mqtc_id, 4);
        c->struct_version = 0;
        c->MQTTVersion = 4;
        __fillup_mqttstring(&c->clientID, client_id);
        c->keepAliveInterval = alive_interval;
        c->cleansession = clean_session;
        c->willFlag = 0;
        __fillup_mqttstring(&c->username, username);
        __fillup_mqttstring(&c->password, password);
    }
    return c;
}

void mqtt_client_will_options(MQTTPacket_connectData * c, char * topic, char * msg, uint32_t retained, uint32_t qos)
{
    if(c)
    {
        static const uint8_t mqtw_id[] = {'M', 'Q', 'T', 'W'};

        memcpy(c->will.struct_id, mqtw_id, 4);
        c->will.struct_version = 0;
        c->willFlag = 1;
        c->will.retained = retained;
        c->will.qos = qos;
        __fillup_mqttstring(&c->will.topicName, topic);
        __fillup_mqttstring(&c->will.message, msg);
    }
}

uint32_t mqtt_client_tcp_error_is_fatal(_S_MQTT_CLIENT_INFO * info)
{
    if(info->mqtt_err == MQTT_ERROR_TCP)
    {
        return mqtt_tcp_error_is_fatal(info->tcp_err);
    }
    else
    {
        return 0;
    }
}

_E_MQTT_ERRORS mqtt_client_connect(_S_MQTT_CLIENT_INFO * info, const char * hostname, uint32_t port,
                                   MQTTPacket_connectData * options, tls_configuration_t * conf)
{
    int32_t ret;
    _E_MQTT_TCP_ERRORS err = MQTT_TCP_ERROR_NONE;
    _E_MQTT_ERRORS mqtt_err = MQTT_ERROR_NONE;

    //printf("mqtt_client_connect 00heap:%d\n",xPortGetFreeHeapSize());
    if(info->ti == 0)
    {
        _S_MQTT_SUBSCRIBE_INFO * s = info->subs_info;

        while(s)
        {
            s->granted_qos = 0x80;
            s = s->next;
        }

        info->mqtt_err = __tcp_connect(info, hostname, port, conf);
        if(info->mqtt_err)
        {
            return info->mqtt_err;
        }
    }
    else
    {
        return MQTT_ERROR_NONE;
    }
    printf("01heap:%d\n",xPortGetFreeHeapSize());
    ret = MQTTSerialize_connect(info->buffer, info->buffer_size, options);
    printf("02heap:%d\n",xPortGetFreeHeapSize());
    if(ret < 1)
    {
        mqtt_err = MQTT_ERROR_S_CONNECT;
    }
    else
    {
        err = mqtt_tcp_write(info->ti, info->buffer, ret, info->tcp_send_wait_time_ms);
        if(err)
        {
            info->tcp_err = err;
            mqtt_err = MQTT_ERROR_TCP;
        }
        else
        {
            struct netbuf * recv = 0;

            err = mqtt_tcp_recv(info->ti, (struct netbuf **)&recv, info->tcp_recv_wait_time_ms);
            if(err)
            {
                if(recv)
                {
                    netbuf_delete(recv);
                }
                info->tcp_err = err;
                mqtt_err = MQTT_ERROR_TCP;
            }
            else if(recv == 0)
            {
                mqtt_err = MQTT_ERROR_CONNECT_EMPTY;
            }
            else
            {
                uint8_t sp, con_ack;

                if(MQTTDeserialize_connack(&sp, &con_ack, recv->ptr->payload, recv->ptr->len))
                {
                    if(con_ack)
                    {
                        mqtt_err = __map_connack_error(con_ack);
                    }
                    else
                    {
                        info->session_present = sp;
                        info->hostname = hostname;
                        info->port_no = port;
                        info->options = options;
                        info->keep_alive_secs = options->keepAliveInterval;
                        if(info->tx_control == 0)
                        {
                            uint32_t recv_stack = 1000;//330;//clyu
                            info->tx_control = xSemaphoreCreateBinary();

                            //uint32_t recv_stack = 330;

                            if(info->ssl_conf)
                            {
                                recv_stack = 1200;
                            }
                            if(info->tx_control == 0 || xTaskCreate(_mqtt_recv_process, "MQTT RP", recv_stack, info, 2, NULL) != pdPASS)
                            {
                                if(info->tx_control)
                                {
                                    vSemaphoreDelete(info->tx_control);
                                    info->tx_control = 0;
                                }
                                mqtt_err = MQTT_ERROR_RECV_TASK;
                            }
                            else
                            {
                                vTaskDelay(__tick_divider(10, tick_wait_divider));
                            }
                        }
                    }
                }
                else
                {
                    mqtt_err = MQTT_ERROR_CONNACK_INVALID;
                }
                netbuf_delete(recv);
            }
        }
    }
    if(mqtt_err)
    {
        /*
        changed from close to delete, as in case of error, the recv process has not started, so if
        mqtt_tcp_close is called, it calls to only close connection from our side and waits for the
        connection to close from the remote side which is handled by _mqtt_recv_process but that process
        does not start if their is mqtt_err. So delete is called.
        */
        mqtt_tcp_delete(info->ti);
        info->ti = 0;
    }

    info->mqtt_err = mqtt_err;
    return mqtt_err;
}

void mqtt_client_upcall_argument(_S_MQTT_CLIENT_INFO * c, void * arg)
{
    c->upcall_arg = arg;
}

_E_MQTT_ERRORS mqtt_client_tcp_close(_S_MQTT_CLIENT_INFO * info)
{
    /*just close the tcp connection, need to check if this will invoke the netconn_recv function.
    it does invoke the netcon_recv function when shutting down only the transmit side using netconn_shutdown.
    if netconn_close is called, the process working with netconn_recv will go to hardware fault. So this function
    can only be used to re-connect using the process above. If a close is done with mqtt disconnect, will msg is sent
    to subscribers which might not be a nice thing.
    */
    mqtt_tcp_close(info->ti);
    return MQTT_ERROR_NONE;
}

_E_MQTT_ERRORS mqtt_client_tcp_delete(_S_MQTT_CLIENT_INFO * info, uint32_t force)
{
    /*this is to be done to kill the connection completely and delete the recv process. The function will not return until the recv_process task is deleted.
    */
    uint32_t prev_recv_wait = info->tcp_recv_wait_time_ms;
    while(info->tx_control)
    {
        uint32_t count = (prev_recv_wait + 500)/100;

        if(force)
        {
            if(xSemaphoreTake(info->tx_control, 0) == pdFALSE)
            {
                xSemaphoreGive(info->rx_semphr);
                xSemaphoreTake(info->tx_control, portMAX_DELAY);
            }
        }
        else
        {
            xSemaphoreTake(info->tx_control, portMAX_DELAY);
        }
        TRACE("tcp close");
        if(info->tcp_recv_wait_time_ms > 10000)
        {
            info->tcp_recv_wait_time_ms = 10000;
        }
        mqtt_tcp_close(info->ti);
        info->kill_recv_process = 1;
        xSemaphoreGive(info->tx_control);
        while(info->kill_recv_process)
        {
            vTaskDelay(__tick_divider(100, tick_wait_divider));
            if(--count == 0)
            {
                xSemaphoreTake(info->tx_control, portMAX_DELAY);
                mqtt_tcp_delete(info->ti);
                info->ti = 0;
                xSemaphoreGive(info->tx_control);
                TRACE("tcp close deleting it");
                return MQTT_ERROR_NONE;
            }
        }
    }
    info->tcp_recv_wait_time_ms = prev_recv_wait;

    return MQTT_ERROR_NONE;
}

_E_MQTT_ERRORS mqtt_client_disconnect(_S_MQTT_CLIENT_INFO * info, uint32_t reconnect)
{
    /*do a mqtt disconnect, and wait for rx_semphr.
    send appropriate error code.
    */
    _E_MQTT_ERRORS mqtt_err = _get_transmit_control(info, info->tcp_recv_wait_time_ms + info->tcp_send_wait_time_ms);

    if(mqtt_err == MQTT_ERROR_NONE)
    {
        int32_t ret = MQTTSerialize_disconnect(info->buffer, info->buffer_size);

        if(ret < 1)
        {
            mqtt_err = MQTT_ERROR_S_DISCONNECT;
        }
        else
        {
            mqtt_err = _transmit_data(info, info->buffer, ret, 3);
        }
        if(reconnect == 0)
        {
            uint32_t count = 10;

            info->kill_recv_process = 1;
            _release_transmit_control(info);
            while(info->kill_recv_process)
            {
                vTaskDelay(__tick_divider(100, tick_wait_divider));
                if(--count == 0)
                {
                    info->kill_recv_process = 0;
                    return mqtt_client_tcp_delete(info, 1);
                }
            }
        }
        else
        {
            _release_transmit_control(info);
        }
    }
    info->mqtt_err = mqtt_err;
    vTaskDelay(__tick_divider(200, tick_wait_divider));
    return mqtt_err;
}

_E_MQTT_ERRORS mqtt_client_delete(_S_MQTT_CLIENT_INFO * info)
{
    _E_MQTT_ERRORS mqtt_err = mqtt_client_disconnect(info, 0);

    TRACE("mqtt_client_delete:%s", mqtt_client_error_to_string(mqtt_err));
    if(1)
    {
        _S_MQTT_SUBSCRIBE_INFO * s = info->subs_info;

        while(s)
        {
            _S_MQTT_SUBSCRIBE_INFO * temp = s;

            s = s->next;
            vPortFree(temp);
        }
        vSemaphoreDelete(info->rx_semphr);
        vPortFree(info->options);
        vPortFree(info->buffer);
        vPortFree(info);
    }
    return mqtt_err;
}

void mqtt_client_set_publish_info(_S_MQTT_CLIENT_INFO * info, uint32_t qos, uint32_t retain)
{
    if(info)
    {
        info->current_pub_qos = qos;
        info->current_pub_retain = retain;
    }
}

static _E_MQTT_ERRORS __publish_response(_S_MQTT_CLIENT_INFO * info, uint8_t * packet_type)
{
    _E_MQTT_ERRORS err = MQTT_ERROR_NONE;
    struct netbuf * buf = 0;

    *packet_type = 0;
    if(xSemaphoreTake(info->rx_semphr, __tick_divider(60000, tick_wait_divider)))
    {
        uint8_t dup;
        uint16_t packet_id;

        buf = __get_received_netbuf(info);

        if(buf && MQTTDeserialize_ack(packet_type, &dup, &packet_id, buf->ptr->payload, buf->ptr->len))
        {
            if(packet_id != info->_packet_id)
            {
                err = MQTT_ERROR_PACKETID_INVALID;
            }
        }
        else
        {
            err = MQTT_ERROR_S_PUBLISH_RESPONSE;
        }
    }
    else
    {
        err = MQTT_ERROR_TCP_NO_RESPONSE;
    }
    return err;
}

_E_MQTT_ERRORS mqtt_client_publish(_S_MQTT_CLIENT_INFO * info, char * _topic, const void * payload,
                                   uint32_t payload_len, uint32_t retry)
{
    _E_MQTT_ERRORS mqtt_err;
    uint32_t dup = 0;
    MQTTString topic;
    int32_t ret;
    uint8_t _packet_type;

    if(retry == 0)
    {
        retry = 1;
    }

    //TRACE("publish");
    //TRACE("topic:%s", _topic);
    //TRACE("payload:%s", (char *)payload);

    mqtt_err = _get_transmit_control(info, info->tcp_recv_wait_time_ms + info->tcp_send_wait_time_ms);

    if(mqtt_err)
    {
        return mqtt_err;
    }

    info->mqtt_err = MQTT_ERROR_NONE;
    __fillup_mqttstring(&topic, _topic);
    _packet_type = PUBLISH;
    do
    {

        if(_packet_type == PUBLISH)
        {
            if(dup < 2)
            {
                ret = MQTTSerialize_publish(info->buffer, info->buffer_size, dup, info->current_pub_qos,
                                            info->current_pub_retain, info->_packet_id, topic, (unsigned char *)payload, payload_len);
                if(ret < 1)
                {
                    mqtt_err = MQTT_ERROR_S_PUBLISH;
                    break;
                }
            }
        }
        else if(_packet_type == PUBREL)
        {
            ret = MQTTSerialize_pubrel(info->buffer, info->buffer_size, dup, info->_packet_id);
            if(ret < 1)
            {
                mqtt_err = MQTT_ERROR_S_PUBREL;
                break;
            }
        }
        else
        {
            break;
        }
        mqtt_err = _transmit_data(info, info->buffer, ret, 2);
        if(mqtt_err)
        {
            if(mqtt_tcp_error_is_fatal(info->tcp_err))
            {
                break;
            }
        }
        else if(info->current_pub_qos)
        {
            uint8_t recv_packet_type = 0;

            info->last_publish_tick = xTaskGetTickCount() * tick_wait_divider;

            mqtt_err = __publish_response(info, &recv_packet_type);

            if(mqtt_err == MQTT_ERROR_NONE)
            {
                if(info->current_pub_qos == 1)
                {
                    if(recv_packet_type == PUBACK)
                    {
                        break;
                    }
                    else
                    {
                        mqtt_err = MQTT_ERROR_ACK_INVALID;
                    }
                }
                else
                {
                    if(_packet_type == PUBLISH && recv_packet_type == PUBREC)
                    {
                        _packet_type = PUBREL;
                        continue;
                    }
                    else if(_packet_type == PUBREL && recv_packet_type == PUBCOMP)
                    {
                        break;
                    }
                    else
                    {
                        mqtt_err = MQTT_ERROR_ACK_INVALID;
                    }
                }
            }
            vTaskDelay(__tick_divider(20, tick_wait_divider));
        }
        else
        {
            break;
        }
        dup++;
        if(--retry == 0)
        {
            break;
        }
    }
    while(1);
    _release_transmit_control(info);
    if(dup)
    {
        __packet_id(&info->_packet_id);
    }
    info->mqtt_err = mqtt_err;
    return mqtt_err;
}

static uint32_t __add_subscribed_topic(_S_MQTT_CLIENT_INFO * info, char * topic, uint32_t qos, uint32_t granted_qos,
                                       uint32_t (*subscribe_func)(struct _s_mqtt_subscribe_info * sinfo, uint32_t qos, uint32_t dup, uint32_t retained, void * payload, uint32_t payload_len))
{
    _S_MQTT_SUBSCRIBE_INFO * s = info->subs_info;
    uint32_t found = 0;

    if(s)
    {
        while(s)
        {
            if(strcmp(s->topic, topic) == 0)
            {
                found = 1;
                break;
            }
            s = s->next;
        }
    }

    if(found == 0)
    {
        s = pvPortMalloc(sizeof(_S_MQTT_SUBSCRIBE_INFO));
    }
    else
    {
        info->mqtt_err = MQTT_ERROR_NONE;
        if(s->qos == qos)
        {
            if(granted_qos < 3)
            {
                s->granted_qos = granted_qos;
                return 0;
            }
            else if(s->granted_qos < 3)
            {
                s->upcall_func = subscribe_func;
                return 0;
            }
        }
        return 1;
    }

    if(s)
    {
        s->topic = topic;
        s->qos = qos;
        s->granted_qos = 0x80;
        s->upcall_func = subscribe_func;
        if(found == 0)
        {
            s->next = 0;
        }

        if(info->subs_info)
        {
            if(found == 0)
            {
                _S_MQTT_SUBSCRIBE_INFO * temp = info->subs_info;

                while(temp->next)
                {
                    temp = temp->next;
                }
                temp->next = s;
            }
        }
        else
        {
            info->subs_info = s;
        }
        info->mqtt_err = MQTT_ERROR_NONE;
    }
    else
    {
        info->mqtt_err = MQTT_ERROR_MEMORY_SUBSCRIBE;
    }
    return 1;
}


_E_MQTT_ERRORS mqtt_client_subscribe(_S_MQTT_CLIENT_INFO * info, char * subscribe_topic, int32_t qos,
                                     uint32_t (*subscribe_func)(_S_MQTT_SUBSCRIBE_INFO * sinfo, uint32_t qos, uint32_t dup, uint32_t retained, void * payload, uint32_t payload_len))
{
    _E_MQTT_ERRORS mqtt_err;
    MQTTString topic;
    int32_t ret;
    uint32_t retry = 2;

    TRACE("waiting to take control for subscribe");
    mqtt_err = _get_transmit_control(info, info->tcp_recv_wait_time_ms + info->tcp_send_wait_time_ms);

    if(mqtt_err)
    {
        return mqtt_err;
    }

    TRACE("ready to subscribe");

    info->mqtt_err = MQTT_ERROR_NONE;
    if(__add_subscribed_topic(info, subscribe_topic, qos, 0x80, subscribe_func) == 0)
    {
        _release_transmit_control(info);
        return info->mqtt_err;
    }
    __fillup_mqttstring(&topic, subscribe_topic);

    do
    {
        ret = MQTTSerialize_subscribe(info->buffer, info->buffer_size, 0, __packet_id(&info->_packet_id), 1, &topic, &qos);
        if(ret < 1)
        {
            mqtt_err = MQTT_ERROR_S_SUBSCRIBE;
            break;
        }
        mqtt_err = _transmit_data(info, info->buffer, ret, 2);
        if(mqtt_err)
        {
            if(mqtt_tcp_error_is_fatal(info->tcp_err))
            {
                break;
            }
        }
        else
        {
            if(xSemaphoreTake(info->rx_semphr, __tick_divider(60000, tick_wait_divider)))
            {
                struct netbuf * buf = __get_received_netbuf(info);
                uint16_t pkt_id;
                int32_t count;
                int32_t granted_qos;

                if(buf)
                {
                    ret = MQTTDeserialize_suback(&pkt_id, 1, &count, &granted_qos, buf->ptr->payload, buf->ptr->len);
                    if(ret >= 0 && pkt_id == info->_packet_id && granted_qos != 0x80)
                    {
                        __add_subscribed_topic(info, subscribe_topic, qos, granted_qos, subscribe_func);
                        break;
                    }
                    else
                    {
                        if(granted_qos == 0x80)
                        {
                            mqtt_err = MQTT_ERROR_SUBACK_UNGRANTED;
                        }
                        else
                        {
                            mqtt_err = MQTT_ERROR_SUBACK_DESERIALIZE;
                        }
                    }
                }
                else
                {
                    mqtt_err = MQTT_ERROR_SUBACK_DESERIALIZE;
                }
            }
        }
        if(--retry == 0)
        {
            break;
        }
    }
    while(1);
    _release_transmit_control(info);
    info->mqtt_err = mqtt_err;
    return mqtt_err;
}

/**
    * Function to unsubscribe a topic
    * @param    structue pointer to the mqtt info created when mqtt_clinet is initialized
    * @param    pointer to the topic that needs to be unsubscribed
    * @return   the enum error related to _E_MQTT_ERRORS
*/
_E_MQTT_ERRORS mqtt_client_unsubscribe(_S_MQTT_CLIENT_INFO * info, char * stopic)
{
    _S_MQTT_SUBSCRIBE_INFO * subs = info->subs_info;
    _S_MQTT_SUBSCRIBE_INFO * prev = 0;
    _E_MQTT_ERRORS mqtt_err = MQTT_ERROR_NONE;//clyu

    while(subs)
    {
        const uint32_t stopic_len = strlen(stopic);

        if((stopic_len == strlen(subs->topic)) && (strcmp(stopic, subs->topic) == 0))
        {
            if(prev)
            {
                prev->next = subs->next;
            }
            else
            {
                info->subs_info = subs->next;
            }
            vPortFree(subs);
            break;
        }
        prev = subs;
        subs = subs->next;
    }

    //_E_MQTT_ERRORS mqtt_err = MQTT_ERROR_NONE;

    if (subs)
    {
        TRACE("wait to take control for unsubscribe for topic:%s", stopic);
        mqtt_err = _get_transmit_control(info, info->tcp_send_wait_time_ms + info->tcp_recv_wait_time_ms);

        if (!mqtt_err)
        {
            MQTTString topic;
            uint32_t retry = 2;//clyu

            __fillup_mqttstring(&topic, stopic);

            //uint32_t retry = 2;

            do
            {
                int32_t ret = MQTTSerialize_unsubscribe(info->buffer, info->buffer_size, 0,
                                                        __packet_id(&info->_packet_id), 1, &topic);

                if (ret < 1)
                {
                    mqtt_err = MQTT_ERROR_S_UNSUBSCRIBE;
                    break;
                }
                mqtt_err = _transmit_data(info, info->buffer, ret, 2);
                if(mqtt_err)
                {
                    if(mqtt_tcp_error_is_fatal(info->tcp_err))
                    {
                        break;
                    }
                }
                else
                {
                    if(xSemaphoreTake(info->rx_semphr, __tick_divider(60000, tick_wait_divider)))
                    {
                        struct netbuf * buf = __get_received_netbuf(info);
                        uint16_t pkt_id;

                        if(buf)
                        {
                            ret = MQTTDeserialize_unsuback(&pkt_id, buf->ptr->payload, buf->ptr->len);
                            if(ret >= 0 && pkt_id == info->_packet_id)
                            {
                                break;
                            }
                            else
                            {
                                mqtt_err = MQTT_ERROR_SUBACK_DESERIALIZE;
                            }
                        }
                        else
                        {
                            mqtt_err = MQTT_ERROR_SUBACK_DESERIALIZE;
                        }
                    }
                }
            }
            while (--retry);
            _release_transmit_control(info);
        }
        info->mqtt_err = mqtt_err;
    }
    return mqtt_err;
}

//const static char * const _client_error[] = {
const static char * const _client_error[] =
{
#undef DEF_MQTT_ERROR
#define DEF_MQTT_ERROR(err, name)           name,
#include "mqtt-client-error.h"
};

const char * mqtt_client_error_to_string(_E_MQTT_ERRORS err)
{
    if(err < MQTT_ERROR_UNDEFINED)
    {
        return _client_error[err];
    }
    return "MQTT error undefined";
}

__inline static _E_MQTT_ERRORS __tcp_connect(_S_MQTT_CLIENT_INFO * info, const char * hostname, uint32_t port,
        tls_configuration_t * conf)
{
    _E_MQTT_TCP_ERRORS err;

    info->ssl_conf = conf;

    info->ti = mqtt_tcp_connect(hostname, port, conf, &err);
    if(info->ti == 0)
    {
        TRACE("mqtt_tcp_connect error:%d", err);
        info->tcp_err = err;
        info->mqtt_err = MQTT_ERROR_TCP_CONNECT;
        return info->mqtt_err;
    }
    return MQTT_ERROR_NONE;
}

static void _mqtt_recv_process(void * pv)
{
    _S_MQTT_CLIENT_INFO * info = pv;
    _S_MQTT_TCP_INFO * tcp_info = info->ti;
    uint32_t ping_tick_remaining = 0;
    uint32_t ping_transmitted = 0;
    uint32_t recv_timeout;//clyu
    uint32_t err_cnt=0,retry;

    if(info->keep_alive_secs)
    {
        if(info->tcp_recv_wait_time_ms == 0)
        {
            info->tcp_recv_wait_time_ms = 60000;
        }
        if(info->tcp_recv_wait_time_ms > (info->keep_alive_secs * 1000))
        {
            info->tcp_recv_wait_time_ms = info->keep_alive_secs * 1000;
        }
        ping_tick_remaining = (xTaskGetTickCount() * tick_wait_divider) + (info->keep_alive_secs * 1000);
    }

    //uint32_t recv_timeout = info->tcp_recv_wait_time_ms;
    recv_timeout = info->tcp_recv_wait_time_ms;

    xSemaphoreGive(info->tx_control);
    do
    {
        /*if I do a netconn_close, will netconn_recv exit, need to check
        */
        struct netbuf * buf = 0;
        _E_MQTT_TCP_ERRORS err;

        if(info->kill_recv_process == 0)
        {
            TRACE("kill_recv_process not set");
            err = mqtt_tcp_recv(tcp_info, &buf, recv_timeout);
        }
        else
        {
            TRACE("kill_recv_process set");
            mqtt_tcp_recv(tcp_info, &buf, 5);
            err = MQTT_TCP_ERROR_CLOSED;
        }

        TRACE("mqtt recv process, recv err:%d, %s, buf: %x, Heapsize %d", err, mqtt_tcp_error_to_string(err)
              ,buf, xPortGetFreeHeapSize());
        if(err)
        {
            if(buf)
            {
                TRACE("recv_err, buf found, deleting it");
                netbuf_delete(buf);
                buf = 0;
            }
            if(info->recv_buf)
            {
                TRACE("deleting netbuf for netconn_recv error");
                netbuf_delete(info->recv_buf);
                info->recv_buf = 0;
            }
#if 0
            //clyu
            if(((err != MQTT_TCP_ERROR_TIMEOUT) &&(err != MQTT_SSL_PEER_CLOSE_NOTIFY)) || (ping_transmitted == 1))
            {
                err_cnt++;
                ping_transmitted = 0;
            }
            if(err_cnt < 3)
            {
                continue;
            }
            err_cnt = 0;
            //end
#endif
            if(mqtt_tcp_error_is_fatal(err) || ping_transmitted == 1)
            {
                TRACE("fatal error, trying to do a new network connection, ping_flag:%d", ping_transmitted);
                ping_transmitted = 0;
                xSemaphoreGive(info->rx_semphr);
                xSemaphoreTake(info->tx_control, portMAX_DELAY);

                mqtt_client_disconnect(info, 1);//clyu
                TRACE("tcp delete from process");
                if(info->ti)
                {
                    mqtt_tcp_delete(tcp_info);
                    printf("tcp_info->ssl_flag=%d\n",tcp_info->ssl_flag);
                    tcp_info = info->ti = 0;
                }
                if(info->kill_recv_process)
                {
                    TRACE("process kill was requested");
                    vSemaphoreDelete(info->tx_control);
                    info->tx_control = 0;
                    info->kill_recv_process = 0;
                    vTaskDelete(NULL);
                }
                //lwip_tls_delete_conf(info->ssl_conf);//clyu
                TRACE("_mqtt_recv_process Heapsize:%d", xPortGetFreeHeapSize());
                //clyu
                retry = 0;
                do
                {
                    vTaskDelay(50000);
                    mqtt_client_connect(info, info->hostname, info->port_no, info->options, info->ssl_conf);
                    if(info->mqtt_err)
                    {
                        printf("re-connect info->mqtt_err:%x, retry:%d\n",info->mqtt_err, ++retry);
                        vTaskDelay(20000);
                    }
                }
                while(info->mqtt_err);
                //ends


                TRACE("successfully re-connected from recv_process");
                tcp_info = info->ti;
                if((info->session_present == 0) && (info->subs_info != 0))
                {
                    _E_MQTT_ERRORS mqtt_err;
                    MQTTString topic;
                    int32_t ret;
                    uint32_t retry = 2;
                    _S_MQTT_SUBSCRIBE_INFO * s = info->subs_info;

                    TRACE("subscribing from recv_process");
                    if(1)
                    {
                        while(s)
                        {
                            TRACE("Topic:%s", s->topic);
                            retry = 2;
                            __fillup_mqttstring(&topic, s->topic);
                            do
                            {
                                int32_t qos = s->qos;
                                ret = MQTTSerialize_subscribe(info->buffer, info->buffer_size, 0, __packet_id(&info->_packet_id), 1, &topic, &qos);
                                if(ret < 1)
                                {
                                    mqtt_err = MQTT_ERROR_S_SUBSCRIBE;
                                    break;
                                }
                                mqtt_err = _transmit_data(info, info->buffer, ret, 2);
                                if(mqtt_err)
                                {
                                    if(mqtt_tcp_error_is_fatal(info->tcp_err))
                                    {
                                        break;
                                    }
                                }
                                else
                                {
                                    buf = 0;
                                    err = mqtt_tcp_recv(tcp_info, &buf, info->tcp_recv_wait_time_ms);
                                    if(buf)
                                    {
                                        uint16_t pkt_id;
                                        int32_t count;
                                        int32_t granted_qos=0;


#if 1
                                        {
                                            int i=0;
                                            uint8_t * data = buf->ptr->payload;
                                            for(i=0; i<buf->ptr->len; i++)
                                            {
                                                printf("%02x ",data[i]);
                                            }
                                        }
#endif

                                        ret = MQTTDeserialize_suback(&pkt_id, 1, &count, &granted_qos, buf->ptr->payload, buf->ptr->len);
                                        netbuf_delete(buf);
                                        TRACE("ret:%d, granted qos:%x, rx pktid:%d, tx pktid:%d", ret, granted_qos, pkt_id, info->_packet_id);
                                        if((ret >= 0) && (pkt_id == info->_packet_id) && (granted_qos != 0x80))
                                        {
                                            s->granted_qos = granted_qos;
                                            TRACE("subscription successfull from recv process");
                                            break;
                                        }
                                        else
                                        {
                                            if(granted_qos == 0x80)
                                            {
                                                mqtt_err = MQTT_ERROR_SUBACK_UNGRANTED;
                                            }
                                            else
                                            {
                                                mqtt_err = MQTT_ERROR_SUBACK_DESERIALIZE;
                                            }
                                        }
                                    }
                                }
                                if(--retry == 0)
                                {
                                    break;
                                }
                            }
                            while(1);
                            s = s->next;
                        }
                    }
                    info->mqtt_err = mqtt_err;
                }

                if(info->keep_alive_secs)
                {
                    //ping_tick_remaining = (xTaskGetTickCount() * tick_wait_divider) + (info->keep_alive_secs * 1000);
                    ping_tick_remaining = (xTaskGetTickCount() * tick_wait_divider);//clyu
                }
                else
                {
                    ping_tick_remaining = 0;
                }
                tcp_info = info->ti;
                xSemaphoreGive(info->tx_control);
            }
        }
        else
        {
            if(buf)
            {
                uint8_t * data = buf->ptr->payload;
                int32_t remaining = buf->ptr->len;

                do
                {
#if 1
                    int i=0;
                    for(i=0; i<remaining; i++)
                    {
                        printf("%02x ",data[i]);
                    }
#endif
                    if(remaining > 1)
                    {

                        //uint32_t packet_type = mqtt_packet_get_type(data, remaining);
                        uint32_t packet_type = MQTTPacket_get_type(data, remaining);//clyu
                        int32_t pkt_len = 0;
                        int32_t length_bytes = MQTTPacket_decodeBuf(&data[1], &pkt_len);

                        TRACE("remaining:%d, packet_type:%x,Packet Type:%s, packet length:%d, length_bytes:%d", remaining, packet_type,MQTTPacket_getName(packet_type), pkt_len, length_bytes);

                        if(pkt_len < 0 || length_bytes == 0)
                        {
                            break;
                        }
                        pkt_len += length_bytes + 1;
                        if(packet_type == PUBLISH)
                        {
                            uint8_t dup;
                            uint8_t retained;
                            int32_t qos;
                            uint16_t pktid;
                            MQTTString topic;
                            uint8_t * payload;
                            int32_t payload_len;
                            int32_t ret;

                            ret = MQTTDeserialize_publish(&dup, &qos, &retained, &pktid, &topic, &payload, &payload_len,
                                                          data, remaining);

                            if(ret >= 0)
                            {
                                _S_MQTT_SUBSCRIBE_INFO * s;

                                if(qos > 0)
                                {
                                    if(qos == 1)
                                    {
                                        ret = MQTTSerialize_puback(info->buffer, info->buffer_size, pktid);
                                    }
                                    else
                                    {
                                        ret = MQTTSerialize_ack(info->buffer, info->buffer_size, PUBREC, 0, pktid);
                                    }
                                    if(ret > 0 && _get_transmit_control(info, 100) == MQTT_ERROR_NONE)
                                    {
                                        TRACE("transmitting puback");
                                        _transmit_data(info, info->buffer, ret, 2);
                                        _release_transmit_control(info);
                                    }
                                }
                                s = info->subs_info;

                                while(s)
                                {
                                    if((strlen(s->topic) == topic.lenstring.len) && memcmp(topic.lenstring.data, s->topic, topic.lenstring.len) == 0)
                                    {
                                        if(s->upcall_func)
                                        {
                                            s->upcall_func(s, qos, dup, retained, payload, payload_len);
                                        }
                                        break;
                                    }
                                    s = s->next;
                                }
                            }
                        }
                        else if(packet_type == PUBREL)
                        {
                            uint8_t packet_type;
                            uint8_t dup;
                            uint16_t pktid;
                            int32_t ret;

                            ret = MQTTDeserialize_ack(&packet_type, &dup, &pktid, data, remaining);
                            if(ret >= 0)
                            {
                                ret = MQTTSerialize_pubcomp(info->buffer, info->buffer_size, pktid);
                                if(ret > 0 && _get_transmit_control(info, 100) == MQTT_ERROR_NONE)
                                {
                                    TRACE("transmitting pubrel");
                                    _transmit_data(info, info->buffer, ret, 2);
                                    _release_transmit_control(info);
                                }
                            }
                        }
                        else if(packet_type == PINGRESP)
                        {
                            ping_transmitted = 0;
                        }
                        else
                        {
                            if(info->recv_buf)
                            {
                                TRACE("deleting netbuf as need to assign new netbuf");
                                netbuf_delete(info->recv_buf);
                            }
                            info->recv_buf = buf;
                            buf = 0;
                            xSemaphoreGive(info->rx_semphr);
                        }
                        data += pkt_len;
                        remaining -= pkt_len;
                    }
                    else
                    {
                        break;
                    }
                }
                while(1);
                if(buf)
                {
                    netbuf_delete(buf);
                    buf = 0;
                }
            }
        }
        if(ping_tick_remaining && info->last_publish_tick)
        {
            ping_tick_remaining = info->last_publish_tick + (info->keep_alive_secs*1000);
            info->last_publish_tick = 0;
        }
        if(ping_tick_remaining)
        {
            int32_t temp = ping_tick_remaining - (xTaskGetTickCount() * tick_wait_divider);
            printf("temp=%d\n",temp);
            if(temp < 15)
            {
                int32_t ret;

                if(xSemaphoreTake(info->tx_control, 0))
                {
                    printf("send ping req\n");
                    ret = MQTTSerialize_pingreq(info->buffer, info->buffer_size);
                    if(ret > 0)
                    {
                        tcp_info->mqtt_tcp_err = mqtt_tcp_write(tcp_info, info->buffer, ret, info->tcp_send_wait_time_ms);
                        ping_transmitted = 1;
                    }
                    xSemaphoreGive(info->tx_control);
                    //}//clyu
                    ping_tick_remaining = (xTaskGetTickCount() * tick_wait_divider) + (info->keep_alive_secs * 1000);
                    recv_timeout = info->tcp_recv_wait_time_ms;
                }
            }
            else if(temp < info->tcp_recv_wait_time_ms)
            {
                recv_timeout = temp;
            }
        }
        else
        {
            recv_timeout = info->tcp_recv_wait_time_ms;
        }
    }
    while(1);
}

static struct netbuf * __get_received_netbuf(_S_MQTT_CLIENT_INFO * info)
{
    return info->recv_buf;
}

static _E_MQTT_ERRORS _get_transmit_control(_S_MQTT_CLIENT_INFO * info, uint32_t wait_ms)
{
    _E_MQTT_ERRORS mqtt_err = MQTT_ERROR_NONE;

    if(info == 0)
    {
        return MQTT_ERROR_INFO;
    }
    else if(info->ti == 0)
    {
        if(info->tx_control)
        {
            if(xSemaphoreTake(info->tx_control, __tick_divider(wait_ms, tick_wait_divider)) == 0)
            {
                mqtt_err = MQTT_ERROR_TX_SEMPHR;
            }
        }
        else
        {
            mqtt_err = MQTT_ERROR_TCP;
        }
    }
    else
    {
        if(xSemaphoreTake(info->tx_control, __tick_divider(wait_ms, tick_wait_divider)) == 0)
        {
            mqtt_err = MQTT_ERROR_TX_SEMPHR;
        }
    }
    if(mqtt_err == MQTT_ERROR_NONE)
    {
        xSemaphoreTake(info->rx_semphr, 0);
    }
    info->mqtt_err = mqtt_err;
    return mqtt_err;
}

static void _release_transmit_control(_S_MQTT_CLIENT_INFO * info)
{
    xSemaphoreGive(info->tx_control);
}

__inline _E_MQTT_ERRORS __map_connack_error(uint32_t err)
{
    switch (err)
    {
        case 1:
            return MQTT_ERROR_CONNACK_PROTOCOL;
        case 2:
            return MQTT_ERROR_CONNACK_ID_REJECT;
        case 3:
            return MQTT_ERROR_CONNACK_SERVER_FAIL;
        case 4:
            return MQTT_ERROR_CONNACK_CREDETIALS;
        case 5:
            return MQTT_ERROR_CONNACK_UNATHORIZED;
        default:
            return MQTT_ERROR_CONNACK_UNDEFINED;
    }
}

static _E_MQTT_ERRORS _transmit_data(_S_MQTT_CLIENT_INFO * info, void * data, uint32_t data_len, uint32_t retry)
{
    _E_MQTT_TCP_ERRORS err = MQTT_TCP_ERROR_NONE;

    do
    {
        err = mqtt_tcp_write(info->ti, data, data_len, info->tcp_send_wait_time_ms);

        if(err)
        {
            if(mqtt_tcp_error_is_fatal(err))
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    while(--retry);
    info->tcp_err = err;
    if(err)
    {
        info->mqtt_err = MQTT_ERROR_TCP;
    }
    else
    {
        info->mqtt_err = MQTT_ERROR_NONE;
    }
    return info->mqtt_err;
}

static void __fillup_mqttstring(MQTTString * s, const char * data)
{
    const char * temp;

    if(data && data[0] == 0)
    {
        temp = 0;
    }
    else
    {
        temp = data;
    }
    s->cstring = (char *)temp;
    s->lenstring.len = 0;
    s->lenstring.data = 0;
}

static uint8_t __packet_id(uint8_t * pkt_id)
{
    uint8_t id = *pkt_id;

    id++;
    if(id > 0xFE)
    {
        do
        {
            id = rand() & 0xFE;
        }
        while(id == 0);
    }
    *pkt_id = id;
    return id;
}

__inline static uint32_t __tick_divider(uint32_t original_value, uint32_t divider)
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
