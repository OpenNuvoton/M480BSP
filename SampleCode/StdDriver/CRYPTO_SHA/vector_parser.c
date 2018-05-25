/**************************************************************************//**
 * @file     vector_parser.c
 * @version  V1.00
 * @brief    CRYPTO SHA test vector parser
 *
 * @copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>

#include "NuMicro.h"


extern uint32_t  VectorDataBase, VectorDataLimit;

static uint8_t      *_pu8FileBase;
static uint32_t     _u32FileIdx, _u32FileSize;


static char  _pi8LineBuff[20*1024];

#ifdef __ICCARM__
#pragma data_alignment=32
uint8_t   _au8ShaData_pool[8192] ;
#else
uint8_t   _au8ShaData_pool[8192] __attribute__((aligned (32))) ;
#endif


uint8_t   *_au8ShaData;

uint8_t     _au8ShaDigest[64];
int         _i32DataLen;


void  open_test_vector(void)
{
    _pu8FileBase = (uint8_t *)&VectorDataBase;
    _u32FileSize = (uint32_t)&VectorDataLimit - (uint32_t)&VectorDataBase;
    _u32FileIdx = 0;
}


static int  read_file(uint8_t *pu8Buff, int i32Len)
{
    if (_u32FileIdx+1 >= _u32FileSize)
        return -1;
    memcpy(pu8Buff, &_pu8FileBase[_u32FileIdx], i32Len);
    _u32FileIdx += i32Len;
    return 0;
}


int  my_get_line(void)
{
    int         i;
    uint8_t     ch[2];

    if (_u32FileIdx+1 >= _u32FileSize)
    {
        //printf("EOF.\n");
        return -1;
    }

    memset(_pi8LineBuff, 0, sizeof(_pi8LineBuff));

    for (i = 0;  ; i++)
    {
        if (read_file(ch, 1) < 0)
            return 0;

        if ((ch[0] == 0x0D) || (ch[0] == 0x0A))
            break;

        _pi8LineBuff[i] = ch[0];
    }

    while (1)
    {
        if (read_file(ch, 1) < 0)
            return 0;

        if ((ch[0] != 0x0D) && (ch[0] != 0x0A))
            break;
    }
    _u32FileIdx--;
    return 0;
}


int  is_hex_char(char c)
{
    if ((c >= '0') && (c <= '9'))
        return 1;
    if ((c >= 'a') && (c <= 'f'))
        return 1;
    if ((c >= 'A') && (c <= 'F'))
        return 1;
    return 0;
}


uint8_t  char_to_hex(uint8_t c)
{
    if ((c >= '0') && (c <= '9'))
        return c - '0';
    if ((c >= 'a') && (c <= 'f'))
        return c - 'a' + 10;
    if ((c >= 'A') && (c <= 'F'))
        return c - 'A' + 10;
    return 0;
}


int  str_to_hex(uint8_t *str, uint8_t *hex, int swap)
{
    int         i, count = 0, actual_len;
    uint8_t     val8;

    while (*str)
    {
        if (!is_hex_char(*str))
        {
            //printf("ERROR - not hex!!\n");
            return count;
        }

        val8 = char_to_hex(*str);
        str++;

        if (!is_hex_char(*str))
        {
            //printf("ERROR - not hex!!\n");
            return count;
        }

        val8 = (val8 << 4) | char_to_hex(*str);
        str++;

        hex[count] = val8;
        //printf("hex = 0x%x\n", val8);
        count++;
    }

    actual_len = count;

    for ( ; count % 4 ; count++)
        hex[count] = 0;

    if (!swap)
        return actual_len;

    // SWAP
    for (i = 0; i < count; i+=4)
    {
        val8 = hex[i];
        hex[i] = hex[i+3];
        hex[i+3] = val8;

        val8 = hex[i+1];
        hex[i+1] = hex[i+2];
        hex[i+2] = val8;
    }

    return actual_len;
}


int  str_to_decimal(uint8_t *str)
{
    int         val32;

    val32 = 0;
    while (*str)
    {
        if ((*str < '0') || (*str > '9'))
        {
            return val32;
        }
        val32 = (val32 * 10) + (*str - '0');
        str++;
    }
    return val32;
}


int  get_next_pattern(void)
{
    int         line_num = 1;
    uint8_t     *p;

    _au8ShaData = (uint8_t *)_au8ShaData_pool;

    while (my_get_line() == 0)
    {
        //printf("LINE %d = %s\n", line_num, _pi8LineBuff);
        line_num++;

        if (_pi8LineBuff[0] == '#')
            continue;

        if (strncmp(_pi8LineBuff,"Len", 3) == 0)
        {
            p = (uint8_t *)&_pi8LineBuff[3];
            while ((*p < '0') || (*p > '9'))
                p++;

            _i32DataLen = str_to_decimal(p);
            continue;
        }

        if (strncmp(_pi8LineBuff,"Msg", 3) == 0)
        {
            p = (uint8_t *)&_pi8LineBuff[3];
            while (!is_hex_char(*p)) p++;
            str_to_hex(p, &_au8ShaData[0], 0);
            continue;
        }

        if (strncmp(_pi8LineBuff,"MD", 2) == 0)
        {
            p = (uint8_t *)&_pi8LineBuff[2];
            while (!is_hex_char(*p)) p++;
            str_to_hex(p, &_au8ShaDigest[0], 1);
            return 0;
        }
    }
    return -1;
}




