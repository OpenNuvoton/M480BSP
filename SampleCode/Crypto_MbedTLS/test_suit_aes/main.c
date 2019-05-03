/**************************************************************************//**
 * @file     main.c
 * @version  V1.10
 * @brief    Mbedtls AES test suite
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

#include "mbedtls/platform.h"

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)
#include "mbedtls/memory_buffer_alloc.h"
#endif

#include "mbedtls/aes.h"


#define KEY_VALUE_MAPPING_FOUND     0
#define KEY_VALUE_MAPPING_NOT_FOUND -1

#define DISPATCH_TEST_SUCCESS       0
#define DISPATCH_TEST_FN_NOT_FOUND  1
#define DISPATCH_INVALID_TEST_DATA  2
#define DISPATCH_UNSUPPORTED_SUITE  3

int       pass_cnt;
uint8_t   *file_base_ptr;
uint32_t  g_file_idx, g_file_size;


static char  g_line_buff[4096];

int  g_aes_mode;

static int test_errors = 0;

extern uint32_t  VectorBase_CBC, VectorLimit_CBC;
extern uint32_t  VectorBase_CFB, VectorLimit_CFB;
extern uint32_t  VectorBase_ECB, VectorLimit_ECB;


/*----------------------------------------------------------------------------*/
/* Macros */

#define TEST_ASSERT( TEST )                         \
    do                                              \
    {                                               \
        if( ! (TEST) )                              \
        {                                           \
            test_fail( #TEST, __LINE__, __FILE__ ); \
            goto exit;                              \
        }                                           \
    } while( 0 )

#define assert(a) if( !( a ) )                                    \
{                                                                 \
    printf("Assertion Failed at %s:%d - %s\n",                 \
                             __FILE__, __LINE__, #a );            \
    while( 1 );                                            \
}

int  open_test_vector(int vector_no)
{
    g_file_idx = 0;

    if (vector_no == 1)
    {
        printf("\n\nOpen test vector test_suite_aes.cbc.data.\n");
        file_base_ptr = (uint8_t *)&VectorBase_CBC;
        g_file_size = (uint32_t)&VectorLimit_CBC - (uint32_t)&VectorBase_CBC;
        g_aes_mode = AES_MODE_CBC;
        return 0;
    }
    else if (vector_no == 2)
    {
        printf("\n\nOpen test vector test_suite_aes.cfb.data.\n");
        file_base_ptr = (uint8_t *)&VectorBase_CFB;
        g_file_size = (uint32_t)&VectorLimit_CFB - (uint32_t)&VectorBase_CFB;
        g_aes_mode = AES_MODE_CFB;
        return 0;
    }
    else if (vector_no == 3)
    {
        printf("\n\nOpen test vector test_suite_aes.ecb.data.\n");
        file_base_ptr = (uint8_t *)&VectorBase_ECB;
        g_file_size = (uint32_t)&VectorLimit_ECB - (uint32_t)&VectorBase_ECB;
        g_aes_mode = AES_MODE_ECB;
        return 0;
    }
    return -1;
}

static void test_fail( const char *test, int line_no, const char* filename )
{
    test_errors++;
    if( test_errors == 1 )
        printf("FAILED\n" );
    printf("  %s\n  at line %d, %s\n", test, line_no, filename );
}

static int  read_file(uint8_t *pu8Buff, int i32Len)
{
    if (g_file_idx+1 >= g_file_size)
        return -1;
    memcpy(pu8Buff, &file_base_ptr[g_file_idx], i32Len);
    g_file_idx += i32Len;
    return 0;
}

int  get_line(void)
{
    int         i;
    uint8_t     ch[2];

    if (g_file_idx+1 >= g_file_size)
    {
        //printf("EOF.\n");
        return -1;
    }

    memset(g_line_buff, 0, sizeof(g_line_buff));

    for (i = 0; i < sizeof(g_line_buff);)
    {
        if (read_file(ch, 1) < 0)
            return 0;

        if ((ch[0] == 0x0D) || (ch[0] == 0x0A))
            break;

        g_line_buff[i++] = ch[0];
    }

    while (1)
    {
        if (read_file(ch, 1) < 0)
            return 0;

        if ((ch[0] != 0x0D) && (ch[0] != 0x0A))
            break;
    }
    g_file_idx--;
    return 0;
}

int parse_arguments( char *buf, size_t len, char *params[50] )
{
    int cnt = 0, i;
    char *cur = buf;
    char *p = buf, *q;

    params[cnt++] = cur;

    while( *p != '\0' && p < buf + len )
    {
        if( *p == '\\' )
        {
            p++;
            p++;
            continue;
        }
        if( *p == ':' )
        {
            if( p + 1 < buf + len )
            {
                cur = p + 1;
                params[cnt++] = cur;
            }
            *p = '\0';
        }

        p++;
    }

    /* Replace newlines, question marks and colons in strings */
    for( i = 0; i < cnt; i++ )
    {
        p = params[i];
        q = params[i];

        while( *p != '\0' )
        {
            if( *p == '\\' && *(p + 1) == 'n' )
            {
                p += 2;
                *(q++) = '\n';
            }
            else if( *p == '\\' && *(p + 1) == ':' )
            {
                p += 2;
                *(q++) = ':';
            }
            else if( *p == '\\' && *(p + 1) == '?' )
            {
                p += 2;
                *(q++) = '?';
            }
            else
                *(q++) = *(p++);
        }
        *q = '\0';
    }

    return( cnt );
}

static int unhexify( unsigned char *obuf, const char *ibuf )
{
    unsigned char c, c2;
    int len = strlen( ibuf ) / 2;
    assert( strlen( ibuf ) % 2 == 0 ); /* must be even number of bytes */

    while( *ibuf != 0 )
    {
        c = *ibuf++;
        if( c >= '0' && c <= '9' )
            c -= '0';
        else if( c >= 'a' && c <= 'f' )
            c -= 'a' - 10;
        else if( c >= 'A' && c <= 'F' )
            c -= 'A' - 10;
        else
            assert( 0 );

        c2 = *ibuf++;
        if( c2 >= '0' && c2 <= '9' )
            c2 -= '0';
        else if( c2 >= 'a' && c2 <= 'f' )
            c2 -= 'a' - 10;
        else if( c2 >= 'A' && c2 <= 'F' )
            c2 -= 'A' - 10;
        else
            assert( 0 );

        *obuf++ = ( c << 4 ) | c2;
    }

    return len;
}

static void hexify( unsigned char *obuf, const unsigned char *ibuf, int len )
{
    unsigned char l, h;

    while( len != 0 )
    {
        h = *ibuf / 16;
        l = *ibuf % 16;

        if( h < 10 )
            *obuf++ = '0' + h;
        else
            *obuf++ = 'a' + h - 10;

        if( l < 10 )
            *obuf++ = '0' + l;
        else
            *obuf++ = 'a' + l - 10;

        ++ibuf;
        len--;
    }
}

int verify_string( char **str )
{
    if( (*str)[0] != '"' ||
            (*str)[strlen( *str ) - 1] != '"' )
    {
        printf("Expected string (with \"\") for parameter and got: %s\n", *str );
        return( -1 );
    }

    (*str)++;
    (*str)[strlen( *str ) - 1] = '\0';

    return( 0 );
}

int verify_int( char *str, int *value )
{
    size_t i;
    int minus = 0;
    int digits = 1;
    int hex = 0;

    for( i = 0; i < strlen( str ); i++ )
    {
        if( i == 0 && str[i] == '-' )
        {
            minus = 1;
            continue;
        }

        if( ( ( minus && i == 2 ) || ( !minus && i == 1 ) ) &&
                str[i - 1] == '0' && str[i] == 'x' )
        {
            hex = 1;
            continue;
        }

        if( ! ( ( str[i] >= '0' && str[i] <= '9' ) ||
                ( hex && ( ( str[i] >= 'a' && str[i] <= 'f' ) ||
                           ( str[i] >= 'A' && str[i] <= 'F' ) ) ) ) )
        {
            digits = 0;
            break;
        }
    }

    if( digits )
    {
        if( hex )
            *value = strtol( str, NULL, 16 );
        else
            *value = strtol( str, NULL, 10 );

        return( 0 );
    }
    printf("Expected integer for parameter and got: %s\n", str );
    return( KEY_VALUE_MAPPING_NOT_FOUND );
}


void test_suite_aes_encrypt_ecb( char *hex_key_string, char *hex_src_string,
                                 char *hex_dst_string, int setkey_result )
{
    unsigned char key_str[100];
    unsigned char src_str[100];
    unsigned char dst_str[100];
    unsigned char output[100];
    mbedtls_aes_context ctx;
    int key_len;

    memset(key_str, 0x00, 100);
    memset(src_str, 0x00, 100);
    memset(dst_str, 0x00, 100);
    memset(output, 0x00, 100);
    mbedtls_aes_init( &ctx );

    key_len = unhexify( key_str, hex_key_string );
    unhexify( src_str, hex_src_string );

    TEST_ASSERT( mbedtls_aes_setkey_enc( &ctx, key_str, key_len * 8 ) == setkey_result );
    if( setkey_result == 0 )
    {
        TEST_ASSERT( mbedtls_aes_crypt_ecb( &ctx, MBEDTLS_AES_ENCRYPT, src_str, output ) == 0 );
        hexify( dst_str, output, 16 );

        //printf("dst_str:        %s\n", dst_str);
        //printf("hex_dst_string: %s\n", hex_dst_string);

        TEST_ASSERT( strcmp( (char *) dst_str, hex_dst_string ) == 0 );
        pass_cnt++;
    }

exit:
    mbedtls_aes_free( &ctx );
}

void test_suite_aes_decrypt_ecb( char *hex_key_string, char *hex_src_string,
                                 char *hex_dst_string, int setkey_result )
{
    unsigned char key_str[100];
    unsigned char src_str[100];
    unsigned char dst_str[100];
    unsigned char output[100];
    mbedtls_aes_context ctx;
    int key_len;

    memset(key_str, 0x00, 100);
    memset(src_str, 0x00, 100);
    memset(dst_str, 0x00, 100);
    memset(output, 0x00, 100);
    mbedtls_aes_init( &ctx );

    key_len = unhexify( key_str, hex_key_string );
    unhexify( src_str, hex_src_string );

    TEST_ASSERT( mbedtls_aes_setkey_dec( &ctx, key_str, key_len * 8 ) == setkey_result );
    if( setkey_result == 0 )
    {
        TEST_ASSERT( mbedtls_aes_crypt_ecb( &ctx, MBEDTLS_AES_DECRYPT, src_str, output ) == 0 );
        hexify( dst_str, output, 16 );

        TEST_ASSERT( strcmp( (char *) dst_str, hex_dst_string ) == 0 );
        pass_cnt++;
    }

exit:
    mbedtls_aes_free( &ctx );
}

void test_suite_aes_encrypt_cbc( char *hex_key_string, char *hex_iv_string,
                                 char *hex_src_string, char *hex_dst_string,
                                 int cbc_result )
{
    unsigned char key_str[100];
    unsigned char iv_str[100];
    unsigned char src_str[100];
    unsigned char dst_str[100];
    unsigned char output[100];
    mbedtls_aes_context ctx;
    int key_len, data_len;

    memset(key_str, 0x00, 100);
    memset(iv_str, 0x00, 100);
    memset(src_str, 0x00, 100);
    memset(dst_str, 0x00, 100);
    memset(output, 0x00, 100);
    mbedtls_aes_init( &ctx );

    key_len = unhexify( key_str, hex_key_string );
    unhexify( iv_str, hex_iv_string );
    data_len = unhexify( src_str, hex_src_string );

    mbedtls_aes_setkey_enc( &ctx, key_str, key_len * 8 );
    TEST_ASSERT( mbedtls_aes_crypt_cbc( &ctx, MBEDTLS_AES_ENCRYPT, data_len, iv_str, src_str, output ) == cbc_result );
    if( cbc_result == 0 )
    {
        hexify( dst_str, output, data_len );

        TEST_ASSERT( strcmp( (char *) dst_str, hex_dst_string ) == 0 );
        pass_cnt++;
    }

exit:
    mbedtls_aes_free( &ctx );
}

void test_suite_aes_decrypt_cbc( char *hex_key_string, char *hex_iv_string,
                                 char *hex_src_string, char *hex_dst_string,
                                 int cbc_result )
{
    unsigned char key_str[100];
    unsigned char iv_str[100];
    unsigned char src_str[100];
    unsigned char dst_str[100];
    unsigned char output[100];
    mbedtls_aes_context ctx;
    int key_len, data_len;

    memset(key_str, 0x00, 100);
    memset(iv_str, 0x00, 100);
    memset(src_str, 0x00, 100);
    memset(dst_str, 0x00, 100);
    memset(output, 0x00, 100);
    mbedtls_aes_init( &ctx );

    key_len = unhexify( key_str, hex_key_string );
    unhexify( iv_str, hex_iv_string );
    data_len = unhexify( src_str, hex_src_string );

    mbedtls_aes_setkey_dec( &ctx, key_str, key_len * 8 );
    TEST_ASSERT( mbedtls_aes_crypt_cbc( &ctx, MBEDTLS_AES_DECRYPT, data_len, iv_str, src_str, output ) == cbc_result );
    if( cbc_result == 0)
    {
        hexify( dst_str, output, data_len );

        //printf("dst_str:        %s\n", dst_str);
        //printf("hex_dst_string: %s\n", hex_dst_string);

        TEST_ASSERT( strcmp( (char *) dst_str, hex_dst_string ) == 0 );
        pass_cnt++;
    }

exit:
    mbedtls_aes_free( &ctx );
}

void test_suite_aes_encrypt_cfb128( char *hex_key_string, char *hex_iv_string,
                                    char *hex_src_string, char *hex_dst_string )
{
    unsigned char key_str[100];
    unsigned char iv_str[100];
    unsigned char src_str[100];
    unsigned char dst_str[100];
    unsigned char output[100];
    mbedtls_aes_context ctx;
    size_t iv_offset = 0;
    int key_len;

    memset(key_str, 0x00, 100);
    memset(iv_str, 0x00, 100);
    memset(src_str, 0x00, 100);
    memset(dst_str, 0x00, 100);
    memset(output, 0x00, 100);
    mbedtls_aes_init( &ctx );

    key_len = unhexify( key_str, hex_key_string );
    unhexify( iv_str, hex_iv_string );
    unhexify( src_str, hex_src_string );

    mbedtls_aes_setkey_enc( &ctx, key_str, key_len * 8 );
    TEST_ASSERT( mbedtls_aes_crypt_cfb128( &ctx, MBEDTLS_AES_ENCRYPT, 16, &iv_offset, iv_str, src_str, output ) == 0 );
    hexify( dst_str, output, 16 );

    TEST_ASSERT( strcmp( (char *) dst_str, hex_dst_string ) == 0 );
    pass_cnt++;

exit:
    mbedtls_aes_free( &ctx );
}

void test_suite_aes_decrypt_cfb128( char *hex_key_string, char *hex_iv_string,
                                    char *hex_src_string, char *hex_dst_string )
{
    unsigned char key_str[100];
    unsigned char iv_str[100];
    unsigned char src_str[100];
    unsigned char dst_str[100];
    unsigned char output[100];
    mbedtls_aes_context ctx;
    size_t iv_offset = 0;
    int key_len;

    memset(key_str, 0x00, 100);
    memset(iv_str, 0x00, 100);
    memset(src_str, 0x00, 100);
    memset(dst_str, 0x00, 100);
    memset(output, 0x00, 100);
    mbedtls_aes_init( &ctx );

    key_len = unhexify( key_str, hex_key_string );
    unhexify( iv_str, hex_iv_string );
    unhexify( src_str, hex_src_string );

    mbedtls_aes_setkey_enc( &ctx, key_str, key_len * 8 );
    TEST_ASSERT( mbedtls_aes_crypt_cfb128( &ctx, MBEDTLS_AES_DECRYPT, 16, &iv_offset, iv_str, src_str, output ) == 0 );
    hexify( dst_str, output, 16 );

    TEST_ASSERT( strcmp( (char *) dst_str, hex_dst_string ) == 0 );
    pass_cnt++;

exit:
    mbedtls_aes_free( &ctx );
}

void test_suite_aes_encrypt_cfb8( char *hex_key_string, char *hex_iv_string,
                                  char *hex_src_string, char *hex_dst_string )
{
    unsigned char key_str[100];
    unsigned char iv_str[100];
    unsigned char src_str[100];
    unsigned char dst_str[100];
    unsigned char output[100];
    mbedtls_aes_context ctx;
    int key_len, src_len;

    memset(key_str, 0x00, 100);
    memset(iv_str, 0x00, 100);
    memset(src_str, 0x00, 100);
    memset(dst_str, 0x00, 100);
    memset(output, 0x00, 100);
    mbedtls_aes_init( &ctx );

    key_len = unhexify( key_str, hex_key_string );
    unhexify( iv_str, hex_iv_string );
    src_len = unhexify( src_str, hex_src_string );

    mbedtls_aes_setkey_enc( &ctx, key_str, key_len * 8 );
    TEST_ASSERT( mbedtls_aes_crypt_cfb8( &ctx, MBEDTLS_AES_ENCRYPT, src_len, iv_str, src_str, output ) == 0 );
    hexify( dst_str, output, src_len );

    TEST_ASSERT( strcmp( (char *) dst_str, hex_dst_string ) == 0 );
    pass_cnt++;

exit:
    mbedtls_aes_free( &ctx );
}

void test_suite_aes_decrypt_cfb8( char *hex_key_string, char *hex_iv_string,
                                  char *hex_src_string, char *hex_dst_string )
{
    unsigned char key_str[100];
    unsigned char iv_str[100];
    unsigned char src_str[100];
    unsigned char dst_str[100];
    unsigned char output[100];
    mbedtls_aes_context ctx;
    int key_len, src_len;

    memset(key_str, 0x00, 100);
    memset(iv_str, 0x00, 100);
    memset(src_str, 0x00, 100);
    memset(dst_str, 0x00, 100);
    memset(output, 0x00, 100);
    mbedtls_aes_init( &ctx );

    key_len = unhexify( key_str, hex_key_string );
    unhexify( iv_str, hex_iv_string );
    src_len = unhexify( src_str, hex_src_string );

    mbedtls_aes_setkey_enc( &ctx, key_str, key_len * 8 );
    TEST_ASSERT( mbedtls_aes_crypt_cfb8( &ctx, MBEDTLS_AES_DECRYPT, src_len, iv_str, src_str, output ) == 0 );
    hexify( dst_str, output, src_len );

    TEST_ASSERT( strcmp( (char *) dst_str, hex_dst_string ) == 0 );
    pass_cnt++;

exit:
    mbedtls_aes_free( &ctx );
}

void test_suite_aes_selftest()
{
    TEST_ASSERT( mbedtls_aes_self_test( 1 ) == 0 );

exit:
    return;
}

int dispatch_test(int cnt, char *params[50])
{
    int ret;
    ((void) cnt);
    ((void) params);

    ret = DISPATCH_TEST_SUCCESS;

    // Cast to void to avoid compiler warnings
    (void)ret;

    if( strcmp( params[0], "aes_encrypt_ecb" ) == 0 )
    {

        char *param1 = params[1];
        char *param2 = params[2];
        char *param3 = params[3];
        int param4;

        if( cnt != 5 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 5 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_string( &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param3 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_int( params[4], &param4 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_aes_encrypt_ecb( param1, param2, param3, param4 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "aes_decrypt_ecb" ) == 0 )
    {

        char *param1 = params[1];
        char *param2 = params[2];
        char *param3 = params[3];
        int param4;

        if( cnt != 5 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 5 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_string( &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param3 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_int( params[4], &param4 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_aes_decrypt_ecb( param1, param2, param3, param4 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "aes_encrypt_cbc" ) == 0 )
    {
        char *param1 = params[1];
        char *param2 = params[2];
        char *param3 = params[3];
        char *param4 = params[4];
        int param5;

        if( cnt != 6 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 6 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_string( &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param3 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param4 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_int( params[5], &param5 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_aes_encrypt_cbc( param1, param2, param3, param4, param5 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "aes_decrypt_cbc" ) == 0 )
    {
        char *param1 = params[1];
        char *param2 = params[2];
        char *param3 = params[3];
        char *param4 = params[4];
        int param5;

        if( cnt != 6 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 6 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_string( &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param3 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param4 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_int( params[5], &param5 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_aes_decrypt_cbc( param1, param2, param3, param4, param5 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "aes_encrypt_cfb128" ) == 0 )
    {
        char *param1 = params[1];
        char *param2 = params[2];
        char *param3 = params[3];
        char *param4 = params[4];

        if( cnt != 5 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 5 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_string( &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param3 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param4 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_aes_encrypt_cfb128( param1, param2, param3, param4 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "aes_decrypt_cfb128" ) == 0 )
    {
        char *param1 = params[1];
        char *param2 = params[2];
        char *param3 = params[3];
        char *param4 = params[4];

        if( cnt != 5 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 5 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_string( &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param3 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param4 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_aes_decrypt_cfb128( param1, param2, param3, param4 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "aes_encrypt_cfb8" ) == 0 )
    {
        char *param1 = params[1];
        char *param2 = params[2];
        char *param3 = params[3];
        char *param4 = params[4];

        if( cnt != 5 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 5 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_string( &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param3 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param4 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_aes_encrypt_cfb8( param1, param2, param3, param4 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "aes_decrypt_cfb8" ) == 0 )
    {
        char *param1 = params[1];
        char *param2 = params[2];
        char *param3 = params[3];
        char *param4 = params[4];

        if( cnt != 5 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 5 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_string( &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param3 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param4 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_aes_decrypt_cfb8( param1, param2, param3, param4 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "aes_selftest" ) == 0 )
    {
        if( cnt != 1 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 1 );
            return( DISPATCH_INVALID_TEST_DATA );
        }


        test_suite_aes_selftest(  );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else

    {
        printf("FAILED\nSkipping unknown test function '%s'\n", params[0] );
        ret = DISPATCH_TEST_FN_NOT_FOUND;
    }
    return( ret );
}

void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Switch HCLK clock source to HXT */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HXT,CLK_CLKDIV0_HCLK(1));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable CRYPTO module clock */
    CLK_EnableModuleClock(CRPT_MODULE);

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Lock protected registers */
    SYS_LockReg();
}

void UART0_Init(void)
{
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}


volatile int  g_Crypto_Int_done = 0;

void CRYPTO_IRQHandler()
{
    if (AES_GET_INT_FLAG(CRPT))
    {
        g_Crypto_Int_done = 1;
        AES_CLR_INT_FLAG(CRPT);
    }
}

/*-----------------------------------------------------------------------------*/
int main(void)
{
    char  *params[50];
    int   cnt, vector_no;
    int   is_eof;

    SYS_Init();                        /* Init System, IP clock and multi-function I/O */

    UART0_Init();                      /* Initialize UART0 */

    SYS_UnlockReg();                   /* Unlock register lock protect */

    printf("+---------------------------------------+\n");
    printf("|     Crypto mbedtls AES test suit      |\n");
    printf("+---------------------------------------+\n");

    NVIC_EnableIRQ(CRPT_IRQn);
    AES_ENABLE_INT(CRPT);

    for (vector_no = 1; ; vector_no++)
    {
        if (open_test_vector(vector_no) != 0)
            break;

        pass_cnt = 0;

        while (1)
        {
            while (1)
            {
                is_eof = get_line();
                if (is_eof || (strncmp(g_line_buff, "aes_", 4) == 0))
                    break;
            }
            if (is_eof)
                break;

            //printf("LINE: %s\n", g_line_buff);

            cnt = parse_arguments(g_line_buff, sizeof(g_line_buff), params);

            dispatch_test(cnt, params);
        }
        printf("PASS count: %d\n", pass_cnt);
    }
    printf("All test file done.\n");
    while (1);
}
