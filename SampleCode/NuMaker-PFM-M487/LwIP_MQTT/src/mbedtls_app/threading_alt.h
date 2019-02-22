/**
	@file		threading_alt.h
	@author	Nishant Agrawal
	@org		Real Time Solutions Pvt. Ltd.
	@date		18/4/2018
	@brief	Enable MBEDTLS_THREADING_ALT. This function defines the mutex type and the init function
*/
#ifndef __THREADING_ALT_H__
#define __THREADING_ALT_H__

/*!
 * Definition of the mutex. In FreeRTOS, its semaphore and mutex are void *, so using void * rather than including
 * FreeRTOS.h header file.
 */
typedef void * mbedtls_threading_mutex_t;

/**
	@fn			threading_alt_init
	@brief	this function will init the internal alternate mutex layer for mbedtls.

	@see		MBEDTLS_THREADING_ALT in mbedtls configuration
	@see		threading.h
	@see		lwip_tls_init
	@note		Call this function before starting to work on mbedtls, called from lwip_tls_init.
*/
void threading_alt_init(void);
#endif
