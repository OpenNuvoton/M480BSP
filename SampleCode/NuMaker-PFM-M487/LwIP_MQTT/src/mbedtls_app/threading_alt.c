/**
    @file       threading_alt.c
    @author Nishant Agrawal
    @org        Real Time Solutions Pvt. Ltd.
    @date       18/4/2018
    @brief  Implementation of alternative thread implementation for mbedtls. Semaphore was used in place of mutex to avoid
                    priority inheritance
*/
#include "lwip/opt.h"//clyu
#include "mbedtls/threading.h"
#include "FreeRTOS.h"
#include "semphr.h"

static void threading_alt_mutex_init(mbedtls_threading_mutex_t * m);
static void threading_alt_mutex_free(mbedtls_threading_mutex_t * m);
static int threading_alt_mutex_lock(mbedtls_threading_mutex_t * m);
static int threading_alt_mutex_unlock(mbedtls_threading_mutex_t * m);

void threading_alt_init()
{
    mbedtls_threading_set_alt(threading_alt_mutex_init, threading_alt_mutex_free, threading_alt_mutex_lock,
                              threading_alt_mutex_unlock);
}

static void threading_alt_mutex_init(mbedtls_threading_mutex_t * m)
{
    xSemaphoreHandle s = xSemaphoreCreateBinary();

    if(s)
    {
        xSemaphoreGive(s);
    }
    *m = s;
}

static void threading_alt_mutex_free(mbedtls_threading_mutex_t * m)
{
    vSemaphoreDelete(*m);
}

static int threading_alt_mutex_lock(mbedtls_threading_mutex_t * m)
{
    xSemaphoreTake(*m, portMAX_DELAY);

    return 0;
}

static int threading_alt_mutex_unlock(mbedtls_threading_mutex_t * m)
{
    xSemaphoreGive(*m);
    return 0;
}
