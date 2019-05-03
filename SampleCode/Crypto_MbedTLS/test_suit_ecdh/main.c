/**************************************************************************//**
 * @file     test_suit_ecdh.c
 * @version  V1.00
 * @brief    mbedtls ECDH test suit
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>

#include "mbedtls/config.h"
#include "mbedtls/platform.h"

#if defined(MBEDTLS_MEMORY_BUFFER_ALLOC_C)
#include "mbedtls/memory_buffer_alloc.h"
#endif

#include <stdint.h>
#include <string.h>

/*----------------------------------------------------------------------------*/
/* Constants */

#define DEPENDENCY_SUPPORTED          0
#define DEPENDENCY_NOT_SUPPORTED      1

#define KEY_VALUE_MAPPING_FOUND       0
#define KEY_VALUE_MAPPING_NOT_FOUND   -1

#define DISPATCH_TEST_SUCCESS         0
#define DISPATCH_TEST_FN_NOT_FOUND    1
#define DISPATCH_INVALID_TEST_DATA    2
#define DISPATCH_UNSUPPORTED_SUITE    3


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

#define assert(a) if( !( a ) )                           \
{                                                        \
    printf("Assertion Failed at %s:%d - %s\n",           \
                             __FILE__, __LINE__, #a );   \
    while (1);                                           \
}

/*
 * 32-bit integer manipulation macros (big endian)
 */
#ifndef GET_UINT32_BE
#define GET_UINT32_BE(n,b,i)                            \
{                                                       \
    (n) = ( (uint32_t) (b)[(i)    ] << 24 )             \
        | ( (uint32_t) (b)[(i) + 1] << 16 )             \
        | ( (uint32_t) (b)[(i) + 2] <<  8 )             \
        | ( (uint32_t) (b)[(i) + 3]       );            \
}
#endif

#ifndef PUT_UINT32_BE
#define PUT_UINT32_BE(n,b,i)                            \
{                                                       \
    (b)[(i)    ] = (unsigned char) ( (n) >> 24 );       \
    (b)[(i) + 1] = (unsigned char) ( (n) >> 16 );       \
    (b)[(i) + 2] = (unsigned char) ( (n) >>  8 );       \
    (b)[(i) + 3] = (unsigned char) ( (n)       );       \
}
#endif


int       pass_cnt;
uint8_t   *file_base_ptr;
uint32_t  g_file_idx, g_file_size;


static char  g_line_buff[4096];

static int test_errors = 0;

extern uint32_t  VectorBase_ECDH, VectorLimit_ECDH;

int  open_test_vector(int vector_no)
{
    g_file_idx = 0;

    if (vector_no == 1)
    {
        printf("\n\nOpen test vector test_suite_ecdh.data.\n");
        file_base_ptr = (uint8_t *)&VectorBase_ECDH;
        g_file_size = (uint32_t)&VectorLimit_ECDH - (uint32_t)&VectorBase_ECDH;
        return 0;
    }
    return -1;
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


/**
 * This function just returns data from rand().
 * Although predictable and often similar on multiple
 * runs, this does not result in identical random on
 * each run. So do not use this if the results of a
 * test depend on the random data that is generated.
 *
 * rng_state shall be NULL.
 */
static int rnd_std_rand( void *rng_state, unsigned char *output, size_t len )
{
#if !defined(__OpenBSD__)
    size_t i;

    if( rng_state != NULL )
        rng_state  = NULL;

    for( i = 0; i < len; ++i )
        output[i] = rand();
#else
    if( rng_state != NULL )
        rng_state = NULL;

    arc4random_buf( output, len );
#endif /* !OpenBSD */

    return( 0 );
}

typedef struct
{
    unsigned char *buf;
    size_t length;
} rnd_buf_info;

/**
 * This function returns random based on a buffer it receives.
 *
 * rng_state shall be a pointer to a rnd_buf_info structure.
 *
 * The number of bytes released from the buffer on each call to
 * the random function is specified by per_call. (Can be between
 * 1 and 4)
 *
 * After the buffer is empty it will return rand();
 */
static int rnd_buffer_rand( void *rng_state, unsigned char *output, size_t len )
{
    rnd_buf_info *info = (rnd_buf_info *) rng_state;
    size_t use_len;

    if( rng_state == NULL )
        return( rnd_std_rand( NULL, output, len ) );

    use_len = len;
    if( len > info->length )
        use_len = info->length;

    if( use_len )
    {
        memcpy( output, info->buf, use_len );
        info->buf += use_len;
        info->length -= use_len;
    }

    if( len - use_len > 0 )
        return( rnd_std_rand( NULL, output + use_len, len - use_len ) );

    return( 0 );
}

/**
 * Info structure for the pseudo random function
 *
 * Key should be set at the start to a test-unique value.
 * Do not forget endianness!
 * State( v0, v1 ) should be set to zero.
 */
typedef struct
{
    uint32_t key[16];
    uint32_t v0, v1;
} rnd_pseudo_info;

/**
 * This function returns random based on a pseudo random function.
 * This means the results should be identical on all systems.
 * Pseudo random is based on the XTEA encryption algorithm to
 * generate pseudorandom.
 *
 * rng_state shall be a pointer to a rnd_pseudo_info structure.
 */
static int rnd_pseudo_rand( void *rng_state, unsigned char *output, size_t len )
{
    rnd_pseudo_info *info = (rnd_pseudo_info *) rng_state;
    uint32_t i, *k, sum, delta=0x9E3779B9;
    unsigned char result[4], *out = output;

    if( rng_state == NULL )
        return( rnd_std_rand( NULL, output, len ) );

    k = info->key;

    while( len > 0 )
    {
        size_t use_len = ( len > 4 ) ? 4 : len;
        sum = 0;

        for( i = 0; i < 32; i++ )
        {
            info->v0 += ( ( ( info->v1 << 4 ) ^ ( info->v1 >> 5 ) )
                          + info->v1 ) ^ ( sum + k[sum & 3] );
            sum += delta;
            info->v1 += ( ( ( info->v0 << 4 ) ^ ( info->v0 >> 5 ) )
                          + info->v0 ) ^ ( sum + k[( sum>>11 ) & 3] );
        }

        PUT_UINT32_BE( info->v0, result, 0 );
        memcpy( out, result, use_len );
        len -= use_len;
        out += 4;
    }

    return( 0 );
}

static void test_fail( const char *test, int line_no, const char* filename )
{
    test_errors++;
    if( test_errors == 1 )
        printf("FAILED\n" );
    printf("  %s\n  at line %d, %s\n", test, line_no, filename );
    while (1);
}




/*----------------------------------------------------------------------------*/
/* Test Suite Code */

#include "mbedtls/ecdh.h"

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

    if( strcmp( str, "MBEDTLS_ECP_DP_SECP192R1" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_DP_SECP192R1 );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP521R1" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_DP_SECP521R1 );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP384R1" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_DP_SECP384R1 );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP256R1" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_DP_SECP256R1 );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP224R1" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_DP_SECP224R1 );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    printf("Expected integer for parameter and got: %s\n", str );
    return( KEY_VALUE_MAPPING_NOT_FOUND );
}


/*----------------------------------------------------------------------------*/
/* Test Case code */

void test_suite_ecdh_primitive_random( int id )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_point qA, qB;
    mbedtls_mpi dA, dB, zA, zB;
    rnd_pseudo_info rnd_info;

    mbedtls_ecp_group_init( &grp );
    mbedtls_ecp_point_init( &qA );
    mbedtls_ecp_point_init( &qB );
    mbedtls_mpi_init( &dA );
    mbedtls_mpi_init( &dB );
    mbedtls_mpi_init( &zA );
    mbedtls_mpi_init( &zB );
    memset( &rnd_info, 0x00, sizeof( rnd_pseudo_info ) );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, (mbedtls_ecp_group_id)id ) == 0 );

    TEST_ASSERT( mbedtls_ecdh_gen_public( &grp, &dA, &qA, &rnd_pseudo_rand, &rnd_info ) == 0 );
    TEST_ASSERT( mbedtls_ecdh_gen_public( &grp, &dB, &qB, &rnd_pseudo_rand, &rnd_info ) == 0 );
    TEST_ASSERT( mbedtls_ecdh_compute_shared( &grp, &zA, &qB, &dA, &rnd_pseudo_rand, &rnd_info ) == 0 );
    TEST_ASSERT( mbedtls_ecdh_compute_shared( &grp, &zB, &qA, &dB, NULL, NULL ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &zA, &zB ) == 0 );

exit:
    mbedtls_ecp_group_free( &grp );
    mbedtls_ecp_point_free( &qA );
    mbedtls_ecp_point_free( &qB );
    mbedtls_mpi_free( &dA );
    mbedtls_mpi_free( &dB );
    mbedtls_mpi_free( &zA );
    mbedtls_mpi_free( &zB );
}

void test_suite_ecdh_primitive_testvec( int id, char *dA_str, char *xA_str, char *yA_str,
                                        char *dB_str, char *xB_str, char *yB_str,
                                        char *z_str )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_point qA, qB;
    mbedtls_mpi dA, dB, zA, zB, check;
    unsigned char rnd_buf_A[MBEDTLS_ECP_MAX_BYTES];
    unsigned char rnd_buf_B[MBEDTLS_ECP_MAX_BYTES];
    rnd_buf_info rnd_info_A, rnd_info_B;

    mbedtls_ecp_group_init( &grp );
    mbedtls_ecp_point_init( &qA );
    mbedtls_ecp_point_init( &qB );
    mbedtls_mpi_init( &dA );
    mbedtls_mpi_init( &dB );
    mbedtls_mpi_init( &zA );
    mbedtls_mpi_init( &zB );
    mbedtls_mpi_init( &check );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, (mbedtls_ecp_group_id)id ) == 0 );

    rnd_info_A.buf = rnd_buf_A;
    rnd_info_A.length = unhexify( rnd_buf_A, dA_str );

    /* Fix rnd_buf_A by shifting it left if necessary */
    if( grp.nbits % 8 != 0 )
    {
        unsigned char shift = 8 - ( grp.nbits % 8 );
        size_t i;

        for( i = 0; i < rnd_info_A.length - 1; i++ )
            rnd_buf_A[i] = rnd_buf_A[i] << shift
                           | rnd_buf_A[i+1] >> ( 8 - shift );

        rnd_buf_A[rnd_info_A.length-1] <<= shift;
    }

    rnd_info_B.buf = rnd_buf_B;
    rnd_info_B.length = unhexify( rnd_buf_B, dB_str );

    /* Fix rnd_buf_B by shifting it left if necessary */
    if( grp.nbits % 8 != 0 )
    {
        unsigned char shift = 8 - ( grp.nbits % 8 );
        size_t i;

        for( i = 0; i < rnd_info_B.length - 1; i++ )
            rnd_buf_B[i] = rnd_buf_B[i] << shift
                           | rnd_buf_B[i+1] >> ( 8 - shift );

        rnd_buf_B[rnd_info_B.length-1] <<= shift;
    }

    TEST_ASSERT( mbedtls_ecdh_gen_public( &grp, &dA, &qA,
                                          rnd_buffer_rand, &rnd_info_A ) == 0 );

#ifndef NUVOTON_ENABLE_ECC
    TEST_ASSERT( ! mbedtls_ecp_is_zero( &qA ) );
#endif
    TEST_ASSERT( mbedtls_mpi_read_string( &check, 16, xA_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &qA.X, &check ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &check, 16, yA_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &qA.Y, &check ) == 0 );

    TEST_ASSERT( mbedtls_ecdh_gen_public( &grp, &dB, &qB,
                                          rnd_buffer_rand, &rnd_info_B ) == 0 );
#ifndef NUVOTON_ENABLE_ECC
    TEST_ASSERT( ! mbedtls_ecp_is_zero( &qB ) );
#endif
    TEST_ASSERT( mbedtls_mpi_read_string( &check, 16, xB_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &qB.X, &check ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &check, 16, yB_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &qB.Y, &check ) == 0 );

    TEST_ASSERT( mbedtls_mpi_read_string( &check, 16, z_str ) == 0 );

    TEST_ASSERT( mbedtls_ecdh_compute_shared( &grp, &zA, &qB, &dA, NULL, NULL ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &zA, &check ) == 0 );

    TEST_ASSERT( mbedtls_ecdh_compute_shared( &grp, &zB, &qA, &dB, NULL, NULL ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &zB, &check ) == 0 );

exit:
    mbedtls_ecp_group_free( &grp );
    mbedtls_ecp_point_free( &qA );
    mbedtls_ecp_point_free( &qB );
    mbedtls_mpi_free( &dA );
    mbedtls_mpi_free( &dB );
    mbedtls_mpi_free( &zA );
    mbedtls_mpi_free( &zB );
    mbedtls_mpi_free( &check );
}


void test_suite_ecdh_exchange( int id )
{
    mbedtls_ecdh_context srv, cli;
    unsigned char buf[1000];
    const unsigned char *vbuf;
    size_t len;
    rnd_pseudo_info rnd_info;


    mbedtls_ecdh_init( &srv );
    mbedtls_ecdh_init( &cli );
    memset( &rnd_info, 0x00, sizeof( rnd_pseudo_info ) );

    TEST_ASSERT( mbedtls_ecp_group_load( &srv.grp, (mbedtls_ecp_group_id)id ) == 0 );

    memset( buf, 0x00, sizeof( buf ) );
    vbuf = buf;
    TEST_ASSERT( mbedtls_ecdh_make_params( &srv, &len, buf, 1000,
                                           &rnd_pseudo_rand, &rnd_info ) == 0 );
    TEST_ASSERT( mbedtls_ecdh_read_params( &cli, &vbuf, buf + len ) == 0 );

    memset( buf, 0x00, sizeof( buf ) );
    TEST_ASSERT( mbedtls_ecdh_make_public( &cli, &len, buf, 1000,
                                           &rnd_pseudo_rand, &rnd_info ) == 0 );
    TEST_ASSERT( mbedtls_ecdh_read_public( &srv, buf, len ) == 0 );

    TEST_ASSERT( mbedtls_ecdh_calc_secret( &srv, &len, buf, 1000,
                                           &rnd_pseudo_rand, &rnd_info ) == 0 );
    TEST_ASSERT( mbedtls_ecdh_calc_secret( &cli, &len, buf, 1000, NULL, NULL ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &srv.z, &cli.z ) == 0 );

exit:
    mbedtls_ecdh_free( &srv );
    mbedtls_ecdh_free( &cli );
}


/*----------------------------------------------------------------------------*/
/* Test dispatch code */

int dep_check( char *str )
{
    if( str == NULL )
        return( 1 );

    if( strcmp( str, "MBEDTLS_ECP_DP_SECP521R1_ENABLED" ) == 0 )
    {
#if defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED)
        return( DEPENDENCY_SUPPORTED );
#else
        return( DEPENDENCY_NOT_SUPPORTED );
#endif
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP224R1_ENABLED" ) == 0 )
    {
#if defined(MBEDTLS_ECP_DP_SECP224R1_ENABLED)
        return( DEPENDENCY_SUPPORTED );
#else
        return( DEPENDENCY_NOT_SUPPORTED );
#endif
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP256R1_ENABLED" ) == 0 )
    {
#if defined(MBEDTLS_ECP_DP_SECP256R1_ENABLED)
        return( DEPENDENCY_SUPPORTED );
#else
        return( DEPENDENCY_NOT_SUPPORTED );
#endif
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP192R1_ENABLED" ) == 0 )
    {
#if defined(MBEDTLS_ECP_DP_SECP192R1_ENABLED)
        return( DEPENDENCY_SUPPORTED );
#else
        return( DEPENDENCY_NOT_SUPPORTED );
#endif
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP384R1_ENABLED" ) == 0 )
    {
#if defined(MBEDTLS_ECP_DP_SECP384R1_ENABLED)
        return( DEPENDENCY_SUPPORTED );
#else
        return( DEPENDENCY_NOT_SUPPORTED );
#endif
    }
    return( DEPENDENCY_NOT_SUPPORTED );
}

int dispatch_test(int cnt, char *params[50])
{
    int ret;
    ((void) cnt);
    ((void) params);

    ret = DISPATCH_TEST_SUCCESS;

    // Cast to void to avoid compiler warnings
    (void)ret;

    if( strcmp( params[0], "ecdh_primitive_random" ) == 0 )
    {
        int param1;

        if( cnt != 2 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 2 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_int( params[1], &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_ecdh_primitive_random( param1 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "ecdh_primitive_testvec" ) == 0 )
    {

        int param1;
        char *param2 = params[2];
        char *param3 = params[3];
        char *param4 = params[4];
        char *param5 = params[5];
        char *param6 = params[6];
        char *param7 = params[7];
        char *param8 = params[8];

        if( cnt != 9 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 9 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_int( params[1], &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param3 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param4 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param5 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param6 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param7 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param8 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_ecdh_primitive_testvec( param1, param2, param3, param4, param5, param6, param7, param8 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "ecdh_exchange" ) == 0 )
    {

        int param1;

        if( cnt != 2 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 2 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_int( params[1], &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_ecdh_exchange( param1 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else

    {
        printf("FAILED\nSkipping unknown test function '%s'\n", params[0] );
        ret = DISPATCH_TEST_FN_NOT_FOUND;
    }
    return( ret );
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
    ECC_Complete(CRPT);
}


/*-----------------------------------------------------------------------------*/
int main(void)
{
    char  *params[50];
    int   cnt, vector_no;
    int   is_eof, ret;

    SYS_Init();                        /* Init System, IP clock and multi-function I/O */

    UART0_Init();                      /* Initialize UART0 */

    SYS_UnlockReg();                   /* Unlock register lock protect */

    printf("+---------------------------------------+\n");
    printf("|  Crypto mbedtls ECC ECDH test suit    |\n");
    printf("+---------------------------------------+\n");

    NVIC_EnableIRQ(CRPT_IRQn);
    ECC_ENABLE_INT(CRPT);

    /* Now begin to execute the tests in the testfiles */
    for (vector_no = 1; ; vector_no++)
    {
        if (open_test_vector(vector_no) != 0)
            break;

        pass_cnt = 0;

        while (1)
        {
            is_eof = get_line();
            if (is_eof) break;


            is_eof = get_line();
            if (is_eof) break;

            cnt = parse_arguments(g_line_buff, strlen(g_line_buff), params);

            if (strcmp( params[0], "depends_on" ) == 0)
            {
                is_eof = get_line();
                if (is_eof) break;

                cnt = parse_arguments(g_line_buff, strlen(g_line_buff), params);
            }

            dispatch_test( cnt, params );
            pass_cnt++;

            if ((ret == DISPATCH_TEST_SUCCESS) && (test_errors == 0))
            {
                printf("PASS\n" );
            }
            else if( ret == DISPATCH_INVALID_TEST_DATA )
            {
                printf("FAILED: FATAL PARSE ERROR\n" );
                while (1);
            }
        }
    }

    printf("\n----------------------------------------------------------------------------\n\n");
    printf("%d pattern PASSED", pass_cnt );

    while (1);
}


