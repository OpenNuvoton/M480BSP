/**
	@file		lwip_tls.c
	@author	Nishant Agrawal
	@org		Real Time Solutions Pvt. Ltd.
	@date		19/4/2018
	@brief	Function implementation creating a wrapper layer in between mbedtls and lwIP for FreeRTOS.
*/
#include "lwip_tls.h"
#include "lwip/api.h"//clyu

#if LWIP_MBEDTLS_ENABLE == 1
#include "FreeRTOS.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/ssl.h"
#include "mbedtls/ssl_internal.h"//clyu
#include <string.h>

#define TRACE(...) {printf(__VA_ARGS__);printf("\n");}//clyu

typedef struct {
	struct netconn * conn;
	struct netbuf * last_buf;
	uint32_t last_offset;
}_S_SSL_LWIP_INFO;

static int32_t _lwip_write(void * lwip_info, const uint8_t * buf, uint32_t len);
static int32_t _lwip_recv(void * lwip_info, uint8_t * buf, uint32_t len);
static int32_t _lwip_recv_timeout(void * ctx, uint8_t * buf, uint32_t len, uint32_t timeout);
static uint32_t _divide_tick(uint32_t original_value, uint32_t divider);

static uint32_t tick_divider = 1;

void lwip_tls_init_tick_divider(uint32_t divider)
{
	tick_divider = divider;
}

void lwip_tls_init()
{
	threading_alt_init();
}


tls_configuration_t * lwip_tls_new_conf(_E_TLS_AUTHENTICATION_TYPE auth, _E_TLS_ENDNODE_TYPE endnode)
{
	//TRACE("mbedtls_ssl_config:%d, mbedtls_entropy_context:%d, mbedtls_ctr_drbg_context:%d, mbedtls_x509_crt:%d",
	//				sizeof(mbedtls_ssl_config), sizeof(mbedtls_entropy_context), sizeof(mbedtls_ctr_drbg_context),
	//				sizeof(mbedtls_x509_crt));
	mbedtls_ssl_config * ssl_conf = platform_alt_calloc(1, sizeof(mbedtls_ssl_config));

	mbedtls_entropy_context * entropy = platform_alt_calloc(1, sizeof(mbedtls_entropy_context));
	mbedtls_ctr_drbg_context * ctr_drbg = platform_alt_calloc(1, sizeof(mbedtls_ctr_drbg_context));
	mbedtls_x509_crt * cert = platform_alt_calloc(1, sizeof(mbedtls_x509_crt));
#if LWIP_ENABLE_CLIENT_CA == 1
	mbedtls_x509_crt *owncert = platform_alt_calloc(1, sizeof(mbedtls_x509_crt));
	mbedtls_pk_context *ownkey = platform_alt_calloc(1, sizeof(mbedtls_pk_context));

	if(owncert == 0 || ownkey == 0)
	{
		vPortFree(owncert);
		vPortFree(ownkey);
	}
	mbedtls_pk_init( ownkey );
	mbedtls_ssl_conf_own_cert(ssl_conf, owncert, ownkey);

#endif


	TRACE("mbedtls_ssl_config:%d, mbedtls_entropy_context:%d, mbedtls_ctr_drbg_context:%d, mbedtls_x509_crt:%d",
					sizeof(mbedtls_ssl_config), sizeof(mbedtls_entropy_context), sizeof(mbedtls_ctr_drbg_context),
					sizeof(mbedtls_x509_crt));

	if(ssl_conf == 0 || entropy == 0 || ctr_drbg == 0 || cert == 0)
	{
		vPortFree(ssl_conf);
		vPortFree(entropy);
		vPortFree(ctr_drbg);
		vPortFree(cert);
		ssl_conf = 0;
	}
	else
	{
		mbedtls_entropy_init(entropy);
		mbedtls_ctr_drbg_init(ctr_drbg);
		mbedtls_ctr_drbg_seed(ctr_drbg, mbedtls_entropy_func, entropy, 0, 0);
		mbedtls_ssl_config_defaults(ssl_conf, endnode, MBEDTLS_SSL_TRANSPORT_STREAM,
																			MBEDTLS_SSL_PRESET_DEFAULT);
		mbedtls_ssl_conf_authmode(ssl_conf, auth);
		mbedtls_ssl_conf_rng(ssl_conf, mbedtls_ctr_drbg_random, ctr_drbg);
		mbedtls_ssl_conf_ca_chain(ssl_conf, cert, 0);
	}
	return (tls_configuration_t *)ssl_conf;	//hiding the mbedtls structure from the application layer
}

int32_t lwip_tls_add_certificate(tls_configuration_t * conf, const uint8_t * cert_buffer, uint32_t cert_len)
{
	mbedtls_x509_crt * cert = ((mbedtls_ssl_config *)conf)->ca_chain;

	return mbedtls_x509_crt_parse(cert, cert_buffer, cert_len);
}

int32_t lwip_tls_add_clientcertificate(tls_configuration_t * conf, const uint8_t * cert_buffer, uint32_t cert_len)
{

	mbedtls_ssl_key_cert * ownkeycertpair = ((mbedtls_ssl_config *)conf)->key_cert;
	mbedtls_x509_crt *owncert = ownkeycertpair->cert;

	return mbedtls_x509_crt_parse(owncert, cert_buffer, cert_len);
}

static tls_configuration_t * g_conf;
tls_context_t * lwip_tls_new(tls_configuration_t * conf, /*enum netconn_type*/int type)
{
	mbedtls_ssl_context * ssl = 0;
g_conf = conf;
	if(type == NETCONN_TCP)
	{
		ssl = platform_alt_calloc(1, sizeof(mbedtls_ssl_context));

		if(ssl)
		{
			int32_t ret = 0;
			_S_SSL_LWIP_INFO * l = platform_alt_calloc(1, sizeof(_S_SSL_LWIP_INFO));

			if(l)
			{
				l->conn = netconn_new(type);

				if(l->conn)
				{
					printf("new conn=%x\n",(uint32_t)l->conn);
					ret = 1;
					ret = mbedtls_ssl_setup(ssl, (mbedtls_ssl_config *)conf);
					mbedtls_ssl_set_bio(ssl, l, _lwip_write, _lwip_recv, _lwip_recv_timeout);
					if(ret < 0)
					{
						mbedtls_ssl_free(ssl);
						ret = 0;
					}
					else
					{
						ret = 1;
					}
				}
			}
			if(ret == 0)
			{
				vPortFree(l);
				vPortFree(ssl);
				ssl = 0;
			}
		}
	}
	return (tls_context_t *)ssl;
}

//clyu
void ipaddr_to_trace(const char *str, ip_addr_t *ipaddr)
{
	//va_list arg;
	//va_start(arg, format);
	//va_end(arg);
	char *addr = (char *)&ipaddr->addr;
	printf("%s",str);
	printf("%d.%d.%d.%d\n",addr[0],addr[1],addr[2],addr[3]);
}

int32_t lwip_tls_connect(tls_context_t * ssl, const char * server_name, uint32_t port)
{
	uint32_t retry = 3;
	ip_addr_t server_ip = {0};
	int32_t ret = ERR_ARG;//ERR_DNS_RESOLVE;//clyu

	TRACE("resolving hostname:%s", server_name);

	do {
		err_t err = netconn_gethostbyname(server_name, &server_ip);

		if(err == ERR_OK)
		{
			ipaddr_to_trace("hostname resolved to ", &server_ip);
			break;
		}
	} while(--retry);

	//int32_t ret = ERR_DNS_RESOLVE;//clyu

	if(retry)
	{
		err_t err;//clyu
		struct netconn * conn;//clyu

		if(((mbedtls_ssl_context *)ssl)->hostname)
		{
			vPortFree(((mbedtls_ssl_context *)ssl)->hostname);
		}
		mbedtls_ssl_set_hostname((mbedtls_ssl_context *)ssl, server_name);

		//struct netconn * conn = ((_S_SSL_LWIP_INFO *)((mbedtls_ssl_context *)ssl)->p_bio)->conn;
		conn = ((_S_SSL_LWIP_INFO *)((mbedtls_ssl_context *)ssl)->p_bio)->conn;

		//err_t err = netconn_connect(conn, &server_ip, port);
		err = netconn_connect(conn, &server_ip, port);

		TRACE("connect:%d,port:%x,conn:%x", err, port,(uint32_t)conn);

		if(err == ERR_OK)
		{
			int32_t temp;//clyu
			#if 0
			{
				err = netconn_close(conn);
				printf("close1:%d\n",err);
				/* delete connection */
                netconn_delete(conn);
                lwip_tls_new(g_conf,NETCONN_TCP);
				err = netconn_connect(conn, &server_ip, port);
				printf("close2:%d,%x\n",err,port);
				ipaddr_to_trace("hostname resolved to ", &server_ip);
				if(err != ERR_OK)
					while(1);

			}
			#endif
			while((ret = mbedtls_ssl_handshake((mbedtls_ssl_context *)ssl)) != 0)
			{
				TRACE("ssl handshake:%x", -ret);
				if((ret != MBEDTLS_ERR_SSL_WANT_READ) && (ret != MBEDTLS_ERR_SSL_WANT_WRITE))
				{
					break;
				}
			}

			TRACE("ssl handshake complete:%x", ret);

			//int32_t temp = mbedtls_ssl_get_verify_result((mbedtls_ssl_context *)ssl);//clyu
			temp = mbedtls_ssl_get_verify_result((mbedtls_ssl_context *)ssl);//clyu
			TRACE("verify result:%d", temp);

			if(temp > 0)
			{
				char * vrfy_buf = pvPortMalloc(512);
				TRACE(" failed\n");
				mbedtls_x509_crt_verify_info(vrfy_buf, 512, "  ! ", temp);
				TRACE("%s\n", vrfy_buf);
				vPortFree(vrfy_buf);
			}
		}
		else
		{
			ret = err;
		}
	}
	return ret;
}

int32_t lwip_tls_bind(tls_context_t * ssl, const ip_addr_t * addr, uint32_t port)
{
	struct netconn * conn = ((_S_SSL_LWIP_INFO *)((mbedtls_ssl_context *)ssl)->p_bio)->conn;

	netconn_bind(conn, addr, port);
	return 0;
}

int32_t lwip_tls_write(tls_context_t * ssl, const void * data, uint32_t len, uint32_t timeout)
{
#if LWIP_SO_SNDTIMEO
	struct netconn * conn = ((_S_SSL_LWIP_INFO *)((mbedtls_ssl_context *)ssl)->p_bio)->conn;

	conn->send_timeout = _divide_tick(timeout, tick_divider);
#endif

	return mbedtls_ssl_write((mbedtls_ssl_context *)ssl, data, len);
}

#if 0//clyu
int32_t lwip_tls_read(tls_context_t * ssl, struct netbuf ** _buf, uint32_t timeout_ms)
{
	static const uint32_t max_data_len = 1500;
	int32_t ret = -1;
	void * data;

	timeout_ms = _divide_tick(timeout_ms, tick_divider);

	//static const uint32_t max_data_len = 1500;//clyu
	//int32_t ret = -1;

	*_buf = 0;

	//void * data = pvPortMalloc(max_data_len);
	data = pvPortMalloc(max_data_len);

	if(data)
	{
		struct netconn * conn = ((_S_SSL_LWIP_INFO *)((mbedtls_ssl_context *)ssl)->p_bio)->conn;
		mbedtls_ssl_config * conf;//clyu

		conn->recv_timeout = timeout_ms;

		//mbedtls_ssl_config * conf = (mbedtls_ssl_config * )((mbedtls_ssl_context *)ssl)->conf;
		conf = (mbedtls_ssl_config * )((mbedtls_ssl_context *)ssl)->conf;

		mbedtls_ssl_conf_read_timeout(conf, timeout_ms);

		ret = mbedtls_ssl_read((mbedtls_ssl_context *)ssl, data, max_data_len);
		if(ret <= 0)
		{
			TRACE("lwip_tls_read:%x", -ret);
		}
		else
		{
			uint32_t data_len = ret;
			struct netbuf * buf = netbuf_new();

			ret = ERR_MEM;
			if(buf)
			{
				void * buf_data = netbuf_alloc(buf, data_len);

				if(buf_data)
				{
					memcpy(buf_data, data, data_len);
					*_buf = buf;
					ret = 0;
				}
				else
				{
					netbuf_delete(buf);
				}
			}
		}
		vPortFree(data);
	}
	return ret;
}
#else
int32_t lwip_tls_read(tls_context_t * ssl, struct netbuf ** _buf, uint32_t timeout_ms)
{
	static const uint32_t max_data_len = 1500;
	int32_t ret = -1;
	void * data;

	timeout_ms = _divide_tick(timeout_ms, tick_divider);

	//static const uint32_t max_data_len = 1500;//clyu
	//int32_t ret = -1;

	*_buf = 0;

	//void * data = pvPortMalloc(max_data_len);
	data = pvPortMalloc(max_data_len);

	if(data)
	{
		struct netconn * conn = ((_S_SSL_LWIP_INFO *)((mbedtls_ssl_context *)ssl)->p_bio)->conn;
		mbedtls_ssl_config * conf;//clyu
		uint32_t xRead = 0;//clyu

		conn->recv_timeout = timeout_ms;

		//mbedtls_ssl_config * conf = (mbedtls_ssl_config * )((mbedtls_ssl_context *)ssl)->conf;
		conf = (mbedtls_ssl_config * )((mbedtls_ssl_context *)ssl)->conf;

		mbedtls_ssl_conf_read_timeout(conf, timeout_ms);

		while( xRead < max_data_len )
        {
			ret = mbedtls_ssl_read((mbedtls_ssl_context *)ssl, (unsigned char*)((uint32_t)data + xRead), max_data_len - xRead);
			if(ret > 0)
			{
				/* Got data, so update the tally and keep looping. */
                xRead += ( size_t ) ret;
			}
			else
            {
            	TRACE("lwip_tls_read:%x", -ret);
                if( ( 0 == ret ) || ( MBEDTLS_ERR_SSL_WANT_READ != ret ) )
                {
                    /* No data and no error or call read again, if indicated, otherwise return error. */
                    break;
                }
            }
		}

		if(xRead)
		{
			uint32_t data_len = xRead;
			struct netbuf * buf = netbuf_new();

			ret = ERR_MEM;
			if(buf)
			{
				void * buf_data = netbuf_alloc(buf, data_len);

				if(buf_data)
				{
					memcpy(buf_data, data, data_len);
					*_buf = buf;
					ret = 0;
				}
				else
				{
					netbuf_delete(buf);
				}
			}
		}
		vPortFree(data);
	}
	return ret;
}
#endif

int32_t lwip_tls_close(tls_context_t * ssl, uint32_t close_recv, uint32_t close_transmit)
{
	int32_t ret = mbedtls_ssl_close_notify((mbedtls_ssl_context *)ssl);
	struct netconn * conn;//clyu
	err_t err;//clyu

	if(ret < 0)
	{
		TRACE("mbedtls_ssl_close_notify:%x", -ret);
	}

	//struct netconn * conn = ((_S_SSL_LWIP_INFO *)((mbedtls_ssl_context *)ssl)->p_bio)->conn;//clyu
	conn = ((_S_SSL_LWIP_INFO *)((mbedtls_ssl_context *)ssl)->p_bio)->conn;

	//err_t err = netconn_shutdown(conn, close_recv, close_transmit);
	//err = netconn_shutdown(conn, close_recv, close_transmit);//clyu
	err = netconn_close(conn);

	TRACE("netconn_close:%d,%x", err, (uint32_t)conn);

	return ret;
}

int32_t lwip_tls_reset(tls_context_t * ssl)
{
	return mbedtls_ssl_session_reset((mbedtls_ssl_context *)ssl);
}

int32_t lwip_tls_delete(tls_context_t * ssl)
{
	int32_t ret = lwip_tls_close(ssl, 1, 1);

	struct netconn * conn = ((_S_SSL_LWIP_INFO *)((mbedtls_ssl_context *)ssl)->p_bio)->conn;
	_S_SSL_LWIP_INFO * info;//clyu

	netconn_delete(conn);
	printf("lwip_tls_delete %x\n", (uint32_t)conn);
	//_S_SSL_LWIP_INFO * info = ((mbedtls_ssl_context *)ssl)->p_bio;
	info = ((mbedtls_ssl_context *)ssl)->p_bio;

	if(info->last_buf)
	{
		netbuf_delete(info->last_buf);
	}

	vPortFree(info);

	mbedtls_ssl_free((mbedtls_ssl_context *)ssl);

	vPortFree(ssl);

	return ret;
}

int32_t lwip_tls_delete_conf(tls_configuration_t * conf)
{
	mbedtls_x509_crt * cert = ((mbedtls_ssl_config *)conf)->ca_chain;
	mbedtls_ctr_drbg_context * ctr_drbg;//clyu
	mbedtls_ssl_key_cert *key_cert = ((mbedtls_ssl_config *)conf)->key_cert;//clyu

	mbedtls_x509_crt_free(cert);
	vPortFree(cert);

	//mbedtls_ctr_drbg_context * ctr_drbg = ((mbedtls_ssl_config *)conf)->p_rng;//clyu
	ctr_drbg = ((mbedtls_ssl_config *)conf)->p_rng;

	mbedtls_entropy_free(ctr_drbg->p_entropy);
	vPortFree(ctr_drbg->p_entropy);

	mbedtls_ctr_drbg_free(ctr_drbg);
	vPortFree(ctr_drbg);

	mbedtls_ssl_config_free((mbedtls_ssl_config *)conf);
	vPortFree(conf);
	//if(key_cert)//clyu
	//{
	//	mbedtls_x509_crt_free(key_cert->cert);
	//	mbedtls_pk_free( key_cert->key );
	//}

	return 0;
}

static int32_t _lwip_write(void * _lwip_info, const uint8_t * buf, uint32_t len)
{
	int32_t ret = -1;
	_S_SSL_LWIP_INFO * info = _lwip_info;

	if(info->conn)
	{
		uint32_t written = 0;
		err_t err = netconn_write_partly(info->conn, buf, len, NETCONN_COPY, &written);

		TRACE("netconn_write:%d", err);
		if(err == ERR_OK)
		{
			ret = written;
		}
	}
	return ret;
}

static int32_t _lwip_recv(void * _lwip_info, uint8_t * recv_ptr, uint32_t recv_len)
{
	_S_SSL_LWIP_INFO * info = _lwip_info;
	struct netconn * conn = info->conn;
	int32_t ret = -1;

	if(conn)
	{
		struct netbuf * buf;
		uint32_t offset = info->last_offset;

		info->last_offset = 0;

		if(info->last_buf)
		{
			buf = info->last_buf;
			info->last_buf = 0;
//			TRACE("last buf:%d, offset:%d", buf->p->tot_len, offset);
		}
		else
		{
			err_t err;//clyu

			buf = 0;

			//err_t err = netconn_recv(conn, &buf);//clyu
			err = netconn_recv(conn, &buf);//clyu


			TRACE("netconn recv:%d", err);
			if((err != ERR_OK) || buf == 0)
			{
				ret = err;
				if(buf)
				{
					netbuf_delete(buf);
					buf = 0;
				}
			}
		}

		if(buf)
		{
			uint32_t copied = pbuf_copy_partial(buf->ptr, recv_ptr, recv_len, offset);

			if(copied)
			{
				ret = copied;
				if((copied + offset) < buf->ptr->tot_len)
				{
					info->last_buf = buf;
					info->last_offset = offset + copied;
				}
			}
			if(info->last_buf == 0)
			{
				netbuf_delete(buf);
			}
		}
	}
//	TRACE("_lwip_recv:%d", ret);
	return ret;
}

static int32_t _lwip_recv_timeout(void * _lwip_info, uint8_t * recv_ptr, uint32_t recv_len, uint32_t timeout)
{
	_S_SSL_LWIP_INFO * info = _lwip_info;
	struct netconn * conn = info->conn;

	conn->recv_timeout = timeout;
	return _lwip_recv(_lwip_info, recv_ptr, recv_len);
}

static uint32_t _divide_tick(uint32_t original_value, uint32_t divider)
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

int lwip_tls_add_private_key(tls_configuration_t * conf,
								const char * pcPrivateKey,
                               	const uint32_t ulPrivateKeyLength)
{
	int ret;
	mbedtls_ssl_key_cert *ownkeycertpair = ((mbedtls_ssl_config *)conf)->key_cert;
	mbedtls_x509_crt * owncert;
	mbedtls_pk_context *ownkey;

    owncert = ownkeycertpair->cert;
    ownkey = ownkeycertpair->key;

    ret = mbedtls_pk_parse_key(
                ownkey,
                ( const unsigned char * ) pcPrivateKey,
                ulPrivateKeyLength,
                NULL,
                0 );
    //if(ret !=0 )
//        return ret;

    return ret;

}
#endif
