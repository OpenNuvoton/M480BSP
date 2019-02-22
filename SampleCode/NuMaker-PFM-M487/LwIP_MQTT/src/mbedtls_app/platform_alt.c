/**
    @file       platform_alt.c
    @author Nishant Agrawal
    @org        Real Time Solutions Pvt. Ltd.
    @date       19/4/2018
    @brief  Platform specific implementation for memory allocation, free and hardware_poll using freertos
*/
#include "mbedtls/platform.h"
#include "FreeRTOS.h"
#include <string.h>

void * platform_alt_calloc(size_t obj_count, size_t obj_size)
{
    void * spc;//clyu

    //printf("obj_count:%d,%d\n",obj_count,obj_size);
    obj_count *= obj_size;
    //printf("obj_count:%d\r\n",obj_count);
    //void * spc = pvPortMalloc(obj_count);
    spc = pvPortMalloc(obj_count);
    //printf("c %d,%x,%d\r\n",obj_count,spc,xPortGetFreeHeapSize());
    if(spc)
    {
        memset(spc, 0, obj_count);
    }
    else
    {
        TRACE("alt_calloc, size:%d, current heap:%d", obj_count, xPortGetFreeHeapSize());
    }
    return spc;
}

void platform_alt_free(void * spc)
{
    //printf("f %x,%d\r\n",spc,xPortGetFreeHeapSize());
    if(spc == 0)
    {
        volatile int i;
        i = 4;
    }
    vPortFree(spc);
}

int mbedtls_hardware_poll( void *data, unsigned char *output, size_t len, size_t *olen )
{
    uint32_t i = 0;
    uint32_t j = 0;
    uint32_t round_len = len >> 2;

    while(j < round_len)
    {
        union
        {
            uint8_t byte[4];
            uint32_t number;
        } temp;

        temp.number = rand();

        output[i++] = temp.byte[0];
        output[i++] = temp.byte[1];
        output[i++] = temp.byte[2];
        output[i++] = temp.byte[3];
        j++;
    }

    while(i < len)
    {
        output[i++] = rand();
    }

    if(olen)
    {
        *olen = len;
    }
    return 0;
}

