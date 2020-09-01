#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "lwip/opt.h"//clyus
#include "lwip_tls.h"
#include "mqtt-client.h"
#include <string.h>
#include "lwip/netbuf.h"
#include "mbedtls/ssl.h"

static void __mbedtls_test(void * pv);
void mqtt_test_init(void);


static const char * ca_certificate =
    "-----BEGIN CERTIFICATE-----\r\n"
    "MIIEkjCCA3qgAwIBAgIQCgFBQgAAAVOFc2oLheynCDANBgkqhkiG9w0BAQsFADA/\r\n"
    "MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\r\n"
    "DkRTVCBSb290IENBIFgzMB4XDTE2MDMxNzE2NDA0NloXDTIxMDMxNzE2NDA0Nlow\r\n"
    "SjELMAkGA1UEBhMCVVMxFjAUBgNVBAoTDUxldCdzIEVuY3J5cHQxIzAhBgNVBAMT\r\n"
    "GkxldCdzIEVuY3J5cHQgQXV0aG9yaXR5IFgzMIIBIjANBgkqhkiG9w0BAQEFAAOC\r\n"
    "AQ8AMIIBCgKCAQEAnNMM8FrlLke3cl03g7NoYzDq1zUmGSXhvb418XCSL7e4S0EF\r\n"
    "q6meNQhY7LEqxGiHC6PjdeTm86dicbp5gWAf15Gan/PQeGdxyGkOlZHP/uaZ6WA8\r\n"
    "SMx+yk13EiSdRxta67nsHjcAHJyse6cF6s5K671B5TaYucv9bTyWaN8jKkKQDIZ0\r\n"
    "Z8h/pZq4UmEUEz9l6YKHy9v6Dlb2honzhT+Xhq+w3Brvaw2VFn3EK6BlspkENnWA\r\n"
    "a6xK8xuQSXgvopZPKiAlKQTGdMDQMc2PMTiVFrqoM7hD8bEfwzB/onkxEz0tNvjj\r\n"
    "/PIzark5McWvxI0NHWQWM6r6hCm21AvA2H3DkwIDAQABo4IBfTCCAXkwEgYDVR0T\r\n"
    "AQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8EBAMCAYYwfwYIKwYBBQUHAQEEczBxMDIG\r\n"
    "CCsGAQUFBzABhiZodHRwOi8vaXNyZy50cnVzdGlkLm9jc3AuaWRlbnRydXN0LmNv\r\n"
    "bTA7BggrBgEFBQcwAoYvaHR0cDovL2FwcHMuaWRlbnRydXN0LmNvbS9yb290cy9k\r\n"
    "c3Ryb290Y2F4My5wN2MwHwYDVR0jBBgwFoAUxKexpHsscfrb4UuQdf/EFWCFiRAw\r\n"
    "VAYDVR0gBE0wSzAIBgZngQwBAgEwPwYLKwYBBAGC3xMBAQEwMDAuBggrBgEFBQcC\r\n"
    "ARYiaHR0cDovL2Nwcy5yb290LXgxLmxldHNlbmNyeXB0Lm9yZzA8BgNVHR8ENTAz\r\n"
    "MDGgL6AthitodHRwOi8vY3JsLmlkZW50cnVzdC5jb20vRFNUUk9PVENBWDNDUkwu\r\n"
    "Y3JsMB0GA1UdDgQWBBSoSmpjBH3duubRObemRWXv86jsoTANBgkqhkiG9w0BAQsF\r\n"
    "AAOCAQEA3TPXEfNjWDjdGBX7CVW+dla5cEilaUcne8IkCJLxWh9KEik3JHRRHGJo\r\n"
    "uM2VcGfl96S8TihRzZvoroed6ti6WqEBmtzw3Wodatg+VyOeph4EYpr/1wXKtx8/\r\n"
    "wApIvJSwtmVi4MFU5aMqrSDE6ea73Mj2tcMyo5jMd6jmeWUHK8so/joWUoHOUgwu\r\n"
    "X4Po1QYz+3dszkDqMp4fklxBwXRsW10KXzPMTZ+sOPAveyxindmjkW8lGy+QsRlG\r\n"
    "PfZ+G6Z6h7mjem0Y+iWlkYcV4PIWL1iwBi8saCbGS5jN2p8M+X+Q7UNKEkROb3N6\r\n"
    "KOqkqm57TH2H3eDJAkSnh6/DNFu0Qg==\r\n"
    "-----END CERTIFICATE-----\r\n";

static void __mbedtls_test(void * pv)
{
    static const char * get_host = "GET https://www.howsmyssl.com/a/check HTTP/1.1\nHost: www.howsmyssl.com\n\n";
    tls_configuration_t * conf = lwip_tls_new_conf(TLS_AUTH_SSL_VERIFY_OPTIONAL, ENDNODE_CLIENT);

    vTaskDelay(2000);

    //static const char * get_host = "GET https://www.howsmyssl.com/a/check HTTP/1.1\nHost: www.howsmyssl.com\n\n";

    TRACE("Current Heap in LAN:%d", xPortGetFreeHeapSize());

    //tls_configuration_t * conf = lwip_tls_new_conf(TLS_AUTH_SSL_VERIFY_OPTIONAL, ENDNODE_CLIENT);

    if(conf)
    {
        tls_context_t * ssl;//clyu

        TRACE("conf done");
        lwip_tls_add_certificate(conf, (uint8_t *)ca_certificate, strlen(ca_certificate) + 1);

        //tls_context_t * ssl = lwip_tls_new(conf, NETCONN_TCP);
        ssl = lwip_tls_new(conf, /*(enum netconn_type)*/NETCONN_TCP);

        if(ssl)
        {
            int32_t ret = lwip_tls_connect(ssl, "www.howsmyssl.com", 443);

            TRACE("ssl ready");

            //int32_t ret = lwip_tls_connect(ssl, "www.howsmyssl.com", 443);
            TRACE("connect:%d", ret);

            if(ret == 0)
            {
                struct netbuf * nbuf;

                lwip_tls_write(ssl, (const uint8_t *)get_host, strlen(get_host), 10000);

                //struct netbuf * nbuf;
                while((ret = lwip_tls_read(ssl, &nbuf, 0)) == 0)
                {
                    if(nbuf)
                    {
                        TRACE("lwip_tls_read:\n");
                        TRACE("%s", (char *)nbuf->ptr->payload);
                        netbuf_delete(nbuf);
                        nbuf = 0;
                    }
                }
                lwip_tls_delete(ssl);
                lwip_tls_delete_conf(conf);
            }
        }
    }
    TRACE("Current Heap in LAN before suspend:%d", xPortGetFreeHeapSize());
    vTaskSuspend(NULL);
}

#include "mqtt-client.h"

typedef struct
{
    uint32_t port;	//0 to disable
    char server[64];
    uint32_t secured;
    char username[128];
    char password[64];
} _S_MQTT_COMMON;

static _S_MQTT_CLIENT_INFO * subs_cinfo = 0;
static TaskHandle_t subs_tsk_handle = 0;

static void __connect_subscribe_failupcall(_S_MQTT_CLIENT_INFO * cinfo)
{
    TRACE("mqtt recv process could not re-connect when the connection failed");
    xTaskNotify(subs_tsk_handle, 0, eSetValueWithoutOverwrite);
}

static _S_MQTT_CLIENT_INFO * __client_init(const _S_MQTT_COMMON * s, _S_MQTT_CLIENT_INFO * c,
        void (*fail_upcall)(_S_MQTT_CLIENT_INFO * cinfo), tls_configuration_t * conf)
{
    MQTTPacket_connectData * options = 0;

    if(c == 0)
    {
        c = mqtt_client_init(1024, 30000, 30000, fail_upcall);
        if(c)
        {
            options = mqtt_client_connect_options("agnishant_test", 60, 1, s->username, s->password);
        }
    }
    else
    {
        options = c->options;
    }
    while(mqtt_client_is_connected(c) == 0)
    {
        _E_MQTT_ERRORS err = mqtt_client_connect(c, s->server, s->port, options, conf);

        TRACE("mqtt client connect, err:%d", err);
        if(err == MQTT_ERROR_NONE)
        {
            break;
        }
        vTaskDelay(50000);
    }
    return c;
}

void dump(char *buf, int t, int len)
{
    int i;

    for(i=0; i<len; i++)
    {
        printf("%c ",buf[i]);
        //if((i%16==0) &&(i!=0))
        //	printf("\n");
    }
    printf("\n");
}
uint32_t __subscribe_upcall(_S_MQTT_SUBSCRIBE_INFO * sinfo, uint32_t qos, uint32_t dup, uint32_t retained,
                            void * payload, uint32_t payload_len)
{
    TRACE("subscribe upcall, qos:%d, dup:%d, retained:%d", qos, dup, retained);
    dump(payload, 0, payload_len);

    return 1;
}

static const char * flespi_ca_certificate =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIDdTCCAl2gAwIBAgILBAAAAAABFUtaw5QwDQYJKoZIhvcNAQEFBQAwVzELMAkG\n"
    "A1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jv\n"
    "b3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw05ODA5MDExMjAw\n"
    "MDBaFw0yODAxMjgxMjAwMDBaMFcxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9i\n"
    "YWxTaWduIG52LXNhMRAwDgYDVQQLEwdSb290IENBMRswGQYDVQQDExJHbG9iYWxT\n"
    "aWduIFJvb3QgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDaDuaZ\n"
    "jc6j40+Kfvvxi4Mla+pIH/EqsLmVEQS98GPR4mdmzxzdzxtIK+6NiY6arymAZavp\n"
    "xy0Sy6scTHAHoT0KMM0VjU/43dSMUBUc71DuxC73/OlS8pF94G3VNTCOXkNz8kHp\n"
    "1Wrjsok6Vjk4bwY8iGlbKk3Fp1S4bInMm/k8yuX9ifUSPJJ4ltbcdG6TRGHRjcdG\n"
    "snUOhugZitVtbNV4FpWi6cgKOOvyJBNPc1STE4U6G7weNLWLBYy5d4ux2x8gkasJ\n"
    "U26Qzns3dLlwR5EiUWMWea6xrkEmCMgZK9FGqkjWZCrXgzT/LCrBbBlDSgeF59N8\n"
    "9iFo7+ryUp9/k5DPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8E\n"
    "BTADAQH/MB0GA1UdDgQWBBRge2YaRQ2XyolQL30EzTSo//z9SzANBgkqhkiG9w0B\n"
    "AQUFAAOCAQEA1nPnfE920I2/7LqivjTFKDK1fPxsnCwrvQmeU79rXqoRSLblCKOz\n"
    "yj1hTdNGCbM+w6DjY1Ub8rrvrTnhQ7k4o+YviiY776BQVvnGCv04zcQLcFGUl5gE\n"
    "38NflNUVyRRBnMRddWQVDf9VMOyGj/8N7yy5Y0b2qvzfvGn9LhJIZJrglfCm7ymP\n"
    "AbEVtQwdpf5pLGkkeB6zpxxxYu7KyJesF12KwvhHhm4qxFYxldBniYUr+WymXUad\n"
    "DKqC5JlR3XC321Y9YeRq4VzW9v493kHMB65jUr9TU/Qr6cf9tveCX4XSQRjbgbME\n"
    "HMUfpIBvFSDJ3gyICh3WZlXi/EjJKSZp4A==\n"
    "-----END CERTIFICATE-----";

#if 0
static const _S_MQTT_COMMON mc = {1883, "mqtt.flespi.io", 0, "FlespiToken QILc0P0LwrdSmJvZl2SXBaWXlzFrczlS8XSWAGyWVzE780WhQD4gDO3Mby1dVdTR", 0};
static void __mqtt_test(void * pv)
{
    TRACE("Current Heap in LAN:%d", xPortGetFreeHeapSize());
    //printf("Current Heap in LAN:%d\n", xPortGetFreeHeapSize());
    //static const _S_MQTT_COMMON mc = {1883, "mqtt.flespi.io", 0, 0, 0};

    subs_cinfo = __client_init(&mc, subs_cinfo, __connect_subscribe_failupcall, 0);
    if(subs_cinfo)
    {
        //mqtt_client_set_publish_info(subs_cinfo,qos,retain);
        //mqtt_client_subscribe(subs_cinfo, "nishant/subs/test", 2, __subscribe_upcall);
        mqtt_client_subscribe(subs_cinfo, "office/light1", 2, __subscribe_upcall);
    }

    do
    {
        //subs_cinfo = __client_init(&mc, subs_cinfo, __connect_subscribe_failupcall, 0);

        if(subs_cinfo)
        {
            //mqtt_client_subscribe(subs_cinfo, "nishant/subs/test", 2, __subscribe_upcall);
            //mqtt_client_subscribe(subs_cinfo, "office/light1", 2, __subscribe_upcall);
            mqtt_client_publish(subs_cinfo, "my/data", "this is a test", 14, 2);
        }
        ulTaskNotifyTake(pdTRUE, /*5000*/portMAX_DELAY);//5s
    }
    while(1);
}
#elif 1//SSL without CA
//static const _S_MQTT_COMMON mc = {1883, "mqtt.flespi.io", 0, "FlespiToken QILc0P0LwrdSmJvZl2SXBaWXlzFrczlS8XSWAGyWVzE780WhQD4gDO3Mby1dVdTR", 0};
static const _S_MQTT_COMMON mc = {8883, "mqtt.flespi.io", 1, "FlespiToken 4eWuTXTFZFRWsAUGfJVjJdHNZenukiydmix55fyVIgH0GrvJ1eSyhna6pnpzvLCG", 0};
static void __mqtt_test(void * pv)
{
    tls_configuration_t * conf = lwip_tls_new_conf(TLS_AUTH_SSL_VERIFY_NONE, ENDNODE_CLIENT);
    tls_context_t * ssl;//clyu

    TRACE("Current Heap in LAN:%d", xPortGetFreeHeapSize());
    subs_cinfo = __client_init(&mc, subs_cinfo, __connect_subscribe_failupcall, conf);

    if(subs_cinfo)
    {
        mbedtls_ssl_set_hostname((mbedtls_ssl_context *)subs_cinfo->ti->ssl,"mqtt.flespi.io");
        //mqtt_client_subscribe(subs_cinfo, "nishant/subs/test", 2, __subscribe_upcall);
        mqtt_client_subscribe(subs_cinfo, "office/light1", 2, __subscribe_upcall);
    }
    do
    {

        if(subs_cinfo)
        {
            mqtt_client_publish(subs_cinfo, "my/data", "this is a test", 14, 2);
        }
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }
    while(1);

}
#elif 0
//static const _S_MQTT_COMMON mc = {1883, "mqtt.flespi.io", 0, "FlespiToken QILc0P0LwrdSmJvZl2SXBaWXlzFrczlS8XSWAGyWVzE780WhQD4gDO3Mby1dVdTR", 0};
static const _S_MQTT_COMMON mc = {8883, "mqtt.flespi.io", 1, "FlespiToken QILc0P0LwrdSmJvZl2SXBaWXlzFrczlS8XSWAGyWVzE780WhQD4gDO3Mby1dVdTR", 0};
static void __mqtt_test(void * pv)
{
    tls_configuration_t * conf = lwip_tls_new_conf(TLS_AUTH_SSL_VERIFY_OPTIONAL, ENDNODE_CLIENT);
    tls_context_t * ssl;//clyu

    TRACE("Current Heap in LAN:%d", xPortGetFreeHeapSize());

    lwip_tls_add_certificate(conf, (uint8_t *)flespi_ca_certificate, strlen(flespi_ca_certificate) + 1);


    //do
    {
        subs_cinfo = __client_init(&mc, subs_cinfo, __connect_subscribe_failupcall, conf);

        if(subs_cinfo)
        {
            //mbedtls_ssl_set_hostname("mqtt.flespi.io");
            //mqtt_client_subscribe(subs_cinfo, "nishant/subs/test", 2, __subscribe_upcall);
            mqtt_client_subscribe(subs_cinfo, "office/light1", 1, __subscribe_upcall);
            //mqtt_client_publish(subs_cinfo, "my/data", "this is a test", 14, 2);
        }
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    } //while(1);
    while(1);
}

#elif 1//Amazon
static const char tlsATS1_ROOT_CERTIFICATE_PEM[] =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF\n"
    "ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6\n"
    "b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL\n"
    "MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv\n"
    "b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj\n"
    "ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM\n"
    "9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw\n"
    "IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6\n"
    "VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L\n"
    "93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm\n"
    "jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC\n"
    "AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA\n"
    "A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI\n"
    "U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs\n"
    "N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv\n"
    "o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU\n"
    "5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy\n"
    "rqXRfboQnoZsG4q5WTP468SQvvG5\n"
    "-----END CERTIFICATE-----\n";


static const char clientcredentialCLIENT_CERTIFICATE_PEM[] = "Paste client certificate here.";

/*
 * PEM-encoded client private key.
 *
 * Must include the PEM header and footer:
 * "-----BEGIN RSA PRIVATE KEY-----"
 * "...base64 data..."
 * "-----END RSA PRIVATE KEY-----";
 */
static const char clientcredentialCLIENT_PRIVATE_KEY_PEM[] = "Paste client private key here.";


static const _S_MQTT_COMMON mc = {8883, "Paste AWS IoT Broker endpoint here.", 1, 0, 0};
static void __mqtt_test(void * pv)
{
    tls_configuration_t * conf = lwip_tls_new_conf(TLS_AUTH_SSL_VERIFY_OPTIONAL, ENDNODE_CLIENT);
    tls_context_t * ssl;//clyu

    TRACE("Current Heap in LAN:%d", xPortGetFreeHeapSize());

    lwip_tls_add_certificate(conf, (uint8_t *)tlsATS1_ROOT_CERTIFICATE_PEM, strlen(tlsATS1_ROOT_CERTIFICATE_PEM) + 1);
    lwip_tls_add_clientcertificate(conf, (uint8_t *)clientcredentialCLIENT_CERTIFICATE_PEM, strlen(clientcredentialCLIENT_CERTIFICATE_PEM) + 1);
    lwip_tls_add_private_key(conf, (uint8_t *)clientcredentialCLIENT_PRIVATE_KEY_PEM, strlen(clientcredentialCLIENT_PRIVATE_KEY_PEM) + 1);

    TRACE("01Current Heap in LAN:%d,root ca %d, client ca %d, private key %d", xPortGetFreeHeapSize(),strlen(tlsATS1_ROOT_CERTIFICATE_PEM),
          strlen(clientcredentialCLIENT_CERTIFICATE_PEM),
          strlen(clientcredentialCLIENT_PRIVATE_KEY_PEM));
    {
        subs_cinfo = __client_init(&mc, subs_cinfo, __connect_subscribe_failupcall, conf);

        if(subs_cinfo)
        {
            //mqtt_client_subscribe(subs_cinfo, "nishant/subs/test", 2, __subscribe_upcall);
            mqtt_client_subscribe(subs_cinfo, "office/light1", 1, __subscribe_upcall);
            //mqtt_client_publish(subs_cinfo, "my/data", "this is a test", 14, 2);
        }
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
    }

    while(1);
}
#endif

//static
void mqtt_test_init(void)
{
    xTaskCreate(__mqtt_test, "MQTT TLS", 1000, NULL, 2, &subs_tsk_handle);//stack size is 1000*4 at least
}

void mbedtls_test_init(void)
{
    xTaskCreate(__mbedtls_test, "Mbed TLS", 4000, NULL, 2, &subs_tsk_handle);
}

ip_addr_t mqtt_get_interface_ip(ip_addr_t * dest)
{
    return ip_addr_any;
}
