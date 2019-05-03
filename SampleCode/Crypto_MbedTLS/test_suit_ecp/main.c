/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    mbedtls ECP test suit
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

#define DEPENDENCY_SUPPORTED        0
#define DEPENDENCY_NOT_SUPPORTED    1

#define KEY_VALUE_MAPPING_FOUND     0
#define KEY_VALUE_MAPPING_NOT_FOUND -1

#define DISPATCH_TEST_SUCCESS       0
#define DISPATCH_TEST_FN_NOT_FOUND  1
#define DISPATCH_INVALID_TEST_DATA  2
#define DISPATCH_UNSUPPORTED_SUITE  3


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

#define assert(a) if( !( a ) )                          \
{                                                       \
    printf("Assertion Failed at %s:%d - %s\n",       \
                             __FILE__, __LINE__, #a );  \
    while (1);                                          \
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

extern uint32_t  VectorBase_ECP, VectorLimit_ECP;

int  open_test_vector(int vector_no)
{
    g_file_idx = 0;

    if (vector_no == 1)
    {
        printf("\n\nOpen test vector test_suite_ecp.data.\n");
        file_base_ptr = (uint8_t *)&VectorBase_ECP;
        g_file_size = (uint32_t)&VectorLimit_ECP - (uint32_t)&VectorBase_ECP;
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

#if defined(MBEDTLS_ECP_C)

#include "mbedtls/ecp.h"

#define ECP_PF_UNKNOWN     -1

#endif /* defined(MBEDTLS_ECP_C) */


#if defined(MBEDTLS_ECP_C)

#define TEST_SUITE_ACTIVE

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

    if( strcmp( str, "MBEDTLS_ECP_PF_UNCOMPRESSED" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_PF_UNCOMPRESSED );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_CURVE25519" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_DP_CURVE25519 );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_NONE" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_DP_NONE );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE" ) == 0 )
    {
        *value = ( MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP384R1" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_DP_SECP384R1 );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_BP256R1" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_DP_BP256R1 );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP192R1" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_DP_SECP192R1 );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ERR_ECP_BAD_INPUT_DATA" ) == 0 )
    {
        *value = ( MBEDTLS_ERR_ECP_BAD_INPUT_DATA );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ERR_ECP_INVALID_KEY" ) == 0 )
    {
        *value = ( MBEDTLS_ERR_ECP_INVALID_KEY );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "ECP_PF_UNKNOWN" ) == 0 )
    {
        *value = ( ECP_PF_UNKNOWN );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP224R1" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_DP_SECP224R1 );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ECP_PF_COMPRESSED" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_PF_COMPRESSED );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL" ) == 0 )
    {
        *value = ( MBEDTLS_ERR_ECP_BUFFER_TOO_SMALL );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP224K1" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_DP_SECP224K1 );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_BP512R1" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_DP_BP512R1 );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_BP384R1" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_DP_BP384R1 );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP192K1" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_DP_SECP192K1 );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP521R1" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_DP_SECP521R1 );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP256K1" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_DP_SECP256K1 );
        return( KEY_VALUE_MAPPING_FOUND );
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP256R1" ) == 0 )
    {
        *value = ( MBEDTLS_ECP_DP_SECP256R1 );
        return( KEY_VALUE_MAPPING_FOUND );
    }

    printf("Expected integer for parameter and got: %s\n", str );
    return( KEY_VALUE_MAPPING_NOT_FOUND );
}


/*----------------------------------------------------------------------------*/
/* Test Case code */

void test_suite_mbedtls_ecp_curve_info( int id, int tls_id, int size, char *name )
{
    const mbedtls_ecp_curve_info *by_id, *by_tls, *by_name;

    by_id   = mbedtls_ecp_curve_info_from_grp_id( (mbedtls_ecp_group_id)id     );
    by_tls  = mbedtls_ecp_curve_info_from_tls_id( tls_id );
    by_name = mbedtls_ecp_curve_info_from_name(   name   );

    TEST_ASSERT( by_id   != NULL );
    TEST_ASSERT( by_tls  != NULL );
    TEST_ASSERT( by_name != NULL );

    TEST_ASSERT( by_id == by_tls  );
    TEST_ASSERT( by_id == by_name );

    TEST_ASSERT( by_id->bit_size == size );

exit:
    return;
}

void test_suite_ecp_check_pub( int grp_id, char *x_hex, char *y_hex, char *z_hex, int ret )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_point P;

    mbedtls_ecp_group_init( &grp );
    mbedtls_ecp_point_init( &P );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, (mbedtls_ecp_group_id)grp_id ) == 0 );

    TEST_ASSERT( mbedtls_mpi_read_string( &P.X, 16, x_hex ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &P.Y, 16, y_hex ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &P.Z, 16, z_hex ) == 0 );

    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &P ) == ret );

exit:
    mbedtls_ecp_group_free( &grp );
    mbedtls_ecp_point_free( &P );
}

void test_suite_ecp_test_vect( int id, char *dA_str, char *xA_str, char *yA_str,
                               char *dB_str, char *xB_str, char *yB_str, char *xZ_str,
                               char *yZ_str )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_point R;
    mbedtls_mpi dA, xA, yA, dB, xB, yB, xZ, yZ;
    rnd_pseudo_info rnd_info;

    mbedtls_ecp_group_init( &grp );
    mbedtls_ecp_point_init( &R );
    mbedtls_mpi_init( &dA );
    mbedtls_mpi_init( &xA );
    mbedtls_mpi_init( &yA );
    mbedtls_mpi_init( &dB );
    mbedtls_mpi_init( &xB );
    mbedtls_mpi_init( &yB );
    mbedtls_mpi_init( &xZ );
    mbedtls_mpi_init( &yZ );
    memset( &rnd_info, 0x00, sizeof( rnd_pseudo_info ) );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, (mbedtls_ecp_group_id)id ) == 0 );

    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &grp.G ) == 0 );

    TEST_ASSERT( mbedtls_mpi_read_string( &dA, 16, dA_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &xA, 16, xA_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &yA, 16, yA_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &dB, 16, dB_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &xB, 16, xB_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &yB, 16, yB_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &xZ, 16, xZ_str ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &yZ, 16, yZ_str ) == 0 );

    TEST_ASSERT( mbedtls_ecp_mul( &grp, &R, &dA, &grp.G,
                                  &rnd_pseudo_rand, &rnd_info ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xA ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.Y, &yA ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &R ) == 0 );
    TEST_ASSERT( mbedtls_ecp_mul( &grp, &R, &dB, &R, NULL, NULL ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xZ ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.Y, &yZ ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &R ) == 0 );

    TEST_ASSERT( mbedtls_ecp_mul( &grp, &R, &dB, &grp.G, NULL, NULL ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xB ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.Y, &yB ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &R ) == 0 );
    TEST_ASSERT( mbedtls_ecp_mul( &grp, &R, &dA, &R,
                                  &rnd_pseudo_rand, &rnd_info ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xZ ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.Y, &yZ ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &R ) == 0 );

exit:
    mbedtls_ecp_group_free( &grp );
    mbedtls_ecp_point_free( &R );
    mbedtls_mpi_free( &dA );
    mbedtls_mpi_free( &xA );
    mbedtls_mpi_free( &yA );
    mbedtls_mpi_free( &dB );
    mbedtls_mpi_free( &xB );
    mbedtls_mpi_free( &yB );
    mbedtls_mpi_free( &xZ );
    mbedtls_mpi_free( &yZ );
}

void test_suite_ecp_test_vec_x( int id, char *dA_hex, char *xA_hex,
                                char *dB_hex, char *xB_hex, char *xS_hex )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_point R;
    mbedtls_mpi dA, xA, dB, xB, xS;
    rnd_pseudo_info rnd_info;

    mbedtls_ecp_group_init( &grp );
    mbedtls_ecp_point_init( &R );
    mbedtls_mpi_init( &dA );
    mbedtls_mpi_init( &xA );
    mbedtls_mpi_init( &dB );
    mbedtls_mpi_init( &xB );
    mbedtls_mpi_init( &xS );
    memset( &rnd_info, 0x00, sizeof( rnd_pseudo_info ) );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, (mbedtls_ecp_group_id)id ) == 0 );

    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &grp.G ) == 0 );

    TEST_ASSERT( mbedtls_mpi_read_string( &dA, 16, dA_hex ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &dB, 16, dB_hex ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &xA, 16, xA_hex ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &xB, 16, xB_hex ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &xS, 16, xS_hex ) == 0 );

    TEST_ASSERT( mbedtls_ecp_mul( &grp, &R, &dA, &grp.G,
                                  &rnd_pseudo_rand, &rnd_info ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &R ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xA ) == 0 );

    TEST_ASSERT( mbedtls_ecp_mul( &grp, &R, &dB, &R,
                                  &rnd_pseudo_rand, &rnd_info ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &R ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xS ) == 0 );

    TEST_ASSERT( mbedtls_ecp_mul( &grp, &R, &dB, &grp.G, NULL, NULL ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &R ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xB ) == 0 );

    TEST_ASSERT( mbedtls_ecp_mul( &grp, &R, &dA, &R, NULL, NULL ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &R ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &R.X, &xS ) == 0 );

exit:
    mbedtls_ecp_group_free( &grp );
    mbedtls_ecp_point_free( &R );
    mbedtls_mpi_free( &dA );
    mbedtls_mpi_free( &xA );
    mbedtls_mpi_free( &dB );
    mbedtls_mpi_free( &xB );
    mbedtls_mpi_free( &xS );
}

void test_suite_ecp_fast_mod( mbedtls_ecp_group_id id, char *N_str )
{
    mbedtls_ecp_group grp;
    mbedtls_mpi N, R;

    mbedtls_mpi_init( &N );
    mbedtls_mpi_init( &R );
    mbedtls_ecp_group_init( &grp );

    TEST_ASSERT( mbedtls_mpi_read_string( &N, 16, N_str ) == 0 );
    TEST_ASSERT( mbedtls_ecp_group_load( &grp, id ) == 0 );
    TEST_ASSERT( grp.modp != NULL );

    /*
     * Store correct result before we touch N
     */
    TEST_ASSERT( mbedtls_mpi_mod_mpi( &R, &N, &grp.P ) == 0 );

    TEST_ASSERT( grp.modp( &N ) == 0 );
    TEST_ASSERT( mbedtls_mpi_bitlen( &N ) <= grp.pbits + 3 );

    /*
     * Use mod rather than addition/subtraction in case previous test fails
     */
    TEST_ASSERT( mbedtls_mpi_mod_mpi( &N, &N, &grp.P ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &N, &R ) == 0 );

exit:
    mbedtls_mpi_free( &N );
    mbedtls_mpi_free( &R );
    mbedtls_ecp_group_free( &grp );
}

void test_suite_ecp_write_binary( mbedtls_ecp_group_id id, char *x, char *y, char *z, int format,
                                  char *out, int blen, int ret )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_point P;
    unsigned char buf[256], str[512];
    size_t olen;

    memset( buf, 0, sizeof( buf ) );
    memset( str, 0, sizeof( str ) );

    mbedtls_ecp_group_init( &grp );
    mbedtls_ecp_point_init( &P );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, id ) == 0 );

    TEST_ASSERT( mbedtls_mpi_read_string( &P.X, 16, x ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &P.Y, 16, y ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &P.Z, 16, z ) == 0 );

    TEST_ASSERT( mbedtls_ecp_point_write_binary( &grp, &P, format,
                 &olen, buf, blen ) == ret );

    if( ret == 0 )
    {
        hexify( str, buf, olen );
        TEST_ASSERT( strcasecmp( (char *) str, out ) == 0 );
    }

exit:
    mbedtls_ecp_group_free( &grp );
    mbedtls_ecp_point_free( &P );
}

void test_suite_ecp_read_binary( mbedtls_ecp_group_id id, char *input, char *x, char *y, char *z,
                                 int ret )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_point P;
    mbedtls_mpi X, Y, Z;
    int ilen;
    unsigned char buf[256];

    memset( buf, 0, sizeof( buf ) );

    mbedtls_ecp_group_init( &grp );
    mbedtls_ecp_point_init( &P );
    mbedtls_mpi_init( &X );
    mbedtls_mpi_init( &Y );
    mbedtls_mpi_init( &Z );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, id ) == 0 );

    TEST_ASSERT( mbedtls_mpi_read_string( &X, 16, x ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &Y, 16, y ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &Z, 16, z ) == 0 );

    ilen = unhexify( buf, input );

    TEST_ASSERT( mbedtls_ecp_point_read_binary( &grp, &P, buf, ilen ) == ret );

    if( ret == 0 )
    {
        TEST_ASSERT( mbedtls_mpi_cmp_mpi( &P.X, &X ) == 0 );
        TEST_ASSERT( mbedtls_mpi_cmp_mpi( &P.Y, &Y ) == 0 );
        TEST_ASSERT( mbedtls_mpi_cmp_mpi( &P.Z, &Z ) == 0 );
    }

exit:
    mbedtls_ecp_group_free( &grp );
    mbedtls_ecp_point_free( &P );
    mbedtls_mpi_free( &X );
    mbedtls_mpi_free( &Y );
    mbedtls_mpi_free( &Z );
}

void test_suite_mbedtls_ecp_tls_read_point(mbedtls_ecp_group_id id, char *input, char *x, char *y, char *z,
        int ret )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_point P;
    mbedtls_mpi X, Y, Z;
    size_t ilen;
    unsigned char buf[256];
    const unsigned char *vbuf = buf;

    memset( buf, 0, sizeof( buf ) );

    mbedtls_ecp_group_init( &grp );
    mbedtls_ecp_point_init( &P );
    mbedtls_mpi_init( &X );
    mbedtls_mpi_init( &Y );
    mbedtls_mpi_init( &Z );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, id ) == 0 );

    TEST_ASSERT( mbedtls_mpi_read_string( &X, 16, x ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &Y, 16, y ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &Z, 16, z ) == 0 );

    ilen = unhexify( buf, input );

    TEST_ASSERT( mbedtls_ecp_tls_read_point( &grp, &P, &vbuf, ilen ) == ret );

    if( ret == 0 )
    {
        TEST_ASSERT( mbedtls_mpi_cmp_mpi( &P.X, &X ) == 0 );
        TEST_ASSERT( mbedtls_mpi_cmp_mpi( &P.Y, &Y ) == 0 );
        TEST_ASSERT( mbedtls_mpi_cmp_mpi( &P.Z, &Z ) == 0 );
        TEST_ASSERT( *vbuf == 0x00 );
    }

exit:
    mbedtls_ecp_group_free( &grp );
    mbedtls_ecp_point_free( &P );
    mbedtls_mpi_free( &X );
    mbedtls_mpi_free( &Y );
    mbedtls_mpi_free( &Z );
}

void test_suite_ecp_tls_write_read_point( mbedtls_ecp_group_id id )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_point pt;
    unsigned char buf[256];
    const unsigned char *vbuf;
    size_t olen;

    mbedtls_ecp_group_init( &grp );
    mbedtls_ecp_point_init( &pt );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, id ) == 0 );

    memset( buf, 0x00, sizeof( buf ) );
    vbuf = buf;
    TEST_ASSERT( mbedtls_ecp_tls_write_point( &grp, &grp.G,
                 MBEDTLS_ECP_PF_COMPRESSED, &olen, buf, 256 ) == 0 );
    TEST_ASSERT( mbedtls_ecp_tls_read_point( &grp, &pt, &vbuf, olen )
                 == MBEDTLS_ERR_ECP_FEATURE_UNAVAILABLE );
    TEST_ASSERT( vbuf == buf + olen );

    memset( buf, 0x00, sizeof( buf ) );
    vbuf = buf;
    TEST_ASSERT( mbedtls_ecp_tls_write_point( &grp, &grp.G,
                 MBEDTLS_ECP_PF_UNCOMPRESSED, &olen, buf, 256 ) == 0 );
    TEST_ASSERT( mbedtls_ecp_tls_read_point( &grp, &pt, &vbuf, olen ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &grp.G.X, &pt.X ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &grp.G.Y, &pt.Y ) == 0 );
    TEST_ASSERT( mbedtls_mpi_cmp_mpi( &grp.G.Z, &pt.Z ) == 0 );
    TEST_ASSERT( vbuf == buf + olen );

    memset( buf, 0x00, sizeof( buf ) );
    vbuf = buf;
    TEST_ASSERT( mbedtls_ecp_set_zero( &pt ) == 0 );
    TEST_ASSERT( mbedtls_ecp_tls_write_point( &grp, &pt,
                 MBEDTLS_ECP_PF_COMPRESSED, &olen, buf, 256 ) == 0 );
    TEST_ASSERT( mbedtls_ecp_tls_read_point( &grp, &pt, &vbuf, olen ) == 0 );
    TEST_ASSERT( mbedtls_ecp_is_zero( &pt ) );
    TEST_ASSERT( vbuf == buf + olen );

    memset( buf, 0x00, sizeof( buf ) );
    vbuf = buf;
    TEST_ASSERT( mbedtls_ecp_set_zero( &pt ) == 0 );
    TEST_ASSERT( mbedtls_ecp_tls_write_point( &grp, &pt,
                 MBEDTLS_ECP_PF_UNCOMPRESSED, &olen, buf, 256 ) == 0 );
    TEST_ASSERT( mbedtls_ecp_tls_read_point( &grp, &pt, &vbuf, olen ) == 0 );
    TEST_ASSERT( mbedtls_ecp_is_zero( &pt ) );
    TEST_ASSERT( vbuf == buf + olen );

exit:
    mbedtls_ecp_group_free( &grp );
    mbedtls_ecp_point_free( &pt );
}

void test_suite_mbedtls_ecp_tls_read_group( char *record, int result, int bits )
{
    mbedtls_ecp_group grp;
    unsigned char buf[10];
    const unsigned char *vbuf = buf;
    int len, ret;

    mbedtls_ecp_group_init( &grp );
    memset( buf, 0x00, sizeof( buf ) );

    len = unhexify( buf, record );

    ret = mbedtls_ecp_tls_read_group( &grp, &vbuf, len );

    TEST_ASSERT( ret == result );
    if( ret == 0)
    {
        TEST_ASSERT( mbedtls_mpi_bitlen( &grp.P ) == (size_t) bits );
        TEST_ASSERT( *vbuf == 0x00 );
    }

exit:
    mbedtls_ecp_group_free( &grp );
}

void test_suite_ecp_tls_write_read_group( int id )
{
    mbedtls_ecp_group grp1, grp2;
    unsigned char buf[10];
    const unsigned char *vbuf = buf;
    size_t len;
    int ret;

    mbedtls_ecp_group_init( &grp1 );
    mbedtls_ecp_group_init( &grp2 );
    memset( buf, 0x00, sizeof( buf ) );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp1, (mbedtls_ecp_group_id)id ) == 0 );

    TEST_ASSERT( mbedtls_ecp_tls_write_group( &grp1, &len, buf, 10 ) == 0 );
    ret = mbedtls_ecp_tls_read_group( &grp2, &vbuf, len );
    TEST_ASSERT( ret == 0 );

    if( ret == 0 )
    {
        TEST_ASSERT( mbedtls_mpi_cmp_mpi( &grp1.N, &grp2.N ) == 0 );
        TEST_ASSERT( grp1.id == grp2.id );
    }

exit:
    mbedtls_ecp_group_free( &grp1 );
    mbedtls_ecp_group_free( &grp2 );
}

void test_suite_mbedtls_ecp_check_privkey( int id, char *key_hex, int ret )
{
    mbedtls_ecp_group grp;
    mbedtls_mpi d;

    mbedtls_ecp_group_init( &grp );
    mbedtls_mpi_init( &d );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, (mbedtls_ecp_group_id)id ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &d, 16, key_hex ) == 0 );

    TEST_ASSERT( mbedtls_ecp_check_privkey( &grp, &d ) == ret );

exit:
    mbedtls_ecp_group_free( &grp );
    mbedtls_mpi_free( &d );
}

void test_suite_mbedtls_ecp_check_pub_priv( int id_pub, char *Qx_pub, char *Qy_pub,
        int id, char *d, char *Qx, char *Qy, int ret )
{
    mbedtls_ecp_keypair pub, prv;

    mbedtls_ecp_keypair_init( &pub );
    mbedtls_ecp_keypair_init( &prv );

    if( id_pub != MBEDTLS_ECP_DP_NONE )
        TEST_ASSERT( mbedtls_ecp_group_load( &pub.grp, (mbedtls_ecp_group_id)id_pub ) == 0 );
    TEST_ASSERT( mbedtls_ecp_point_read_string( &pub.Q, 16, Qx_pub, Qy_pub ) == 0 );

    if( id != MBEDTLS_ECP_DP_NONE )
        TEST_ASSERT( mbedtls_ecp_group_load( &prv.grp, (mbedtls_ecp_group_id)id ) == 0 );
    TEST_ASSERT( mbedtls_ecp_point_read_string( &prv.Q, 16, Qx, Qy ) == 0 );
    TEST_ASSERT( mbedtls_mpi_read_string( &prv.d, 16, d ) == 0 );

    TEST_ASSERT( mbedtls_ecp_check_pub_priv( &pub, &prv ) == ret );

exit:
    mbedtls_ecp_keypair_free( &pub );
    mbedtls_ecp_keypair_free( &prv );
}

void test_suite_mbedtls_ecp_gen_keypair( int id )
{
    mbedtls_ecp_group grp;
    mbedtls_ecp_point Q;
    mbedtls_mpi d;
    rnd_pseudo_info rnd_info;

    mbedtls_ecp_group_init( &grp );
    mbedtls_ecp_point_init( &Q );
    mbedtls_mpi_init( &d );
    memset( &rnd_info, 0x00, sizeof( rnd_pseudo_info ) );

    TEST_ASSERT( mbedtls_ecp_group_load( &grp, (mbedtls_ecp_group_id)id ) == 0 );

    TEST_ASSERT( mbedtls_ecp_gen_keypair( &grp, &d, &Q, &rnd_pseudo_rand, &rnd_info )
                 == 0 );

    TEST_ASSERT( mbedtls_ecp_check_pubkey( &grp, &Q ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_privkey( &grp, &d ) == 0 );

exit:
    mbedtls_ecp_group_free( &grp );
    mbedtls_ecp_point_free( &Q );
    mbedtls_mpi_free( &d );
}

void test_suite_mbedtls_ecp_gen_key( int id )
{
    mbedtls_ecp_keypair key;
    rnd_pseudo_info rnd_info;

    mbedtls_ecp_keypair_init( &key );
    memset( &rnd_info, 0x00, sizeof( rnd_pseudo_info ) );

    TEST_ASSERT( mbedtls_ecp_gen_key( (mbedtls_ecp_group_id)id, &key, &rnd_pseudo_rand, &rnd_info ) == 0 );

    TEST_ASSERT( mbedtls_ecp_check_pubkey( &key.grp, &key.Q ) == 0 );
    TEST_ASSERT( mbedtls_ecp_check_privkey( &key.grp, &key.d ) == 0 );

exit:
    mbedtls_ecp_keypair_free( &key );
}

#ifdef MBEDTLS_SELF_TEST
void test_suite_ecp_selftest()
{
    TEST_ASSERT( mbedtls_ecp_self_test( 1 ) == 0 );

exit:
    return;
}
#endif /* MBEDTLS_SELF_TEST */


#endif /* defined(MBEDTLS_ECP_C) */



/*----------------------------------------------------------------------------*/
/* Test dispatch code */

int dep_check( char *str )
{
    if( str == NULL )
        return( 1 );

    if( strcmp( str, "MBEDTLS_ECP_DP_SECP224K1_ENABLED" ) == 0 )
    {
#if defined(MBEDTLS_ECP_DP_SECP224K1_ENABLED)
        return( DEPENDENCY_SUPPORTED );
#else
        return( DEPENDENCY_NOT_SUPPORTED );
#endif
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP521R1_ENABLED" ) == 0 )
    {
#if defined(MBEDTLS_ECP_DP_SECP521R1_ENABLED)
        return( DEPENDENCY_SUPPORTED );
#else
        return( DEPENDENCY_NOT_SUPPORTED );
#endif
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP256K1_ENABLED" ) == 0 )
    {
#if defined(MBEDTLS_ECP_DP_SECP256K1_ENABLED)
        return( DEPENDENCY_SUPPORTED );
#else
        return( DEPENDENCY_NOT_SUPPORTED );
#endif
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_SECP192K1_ENABLED" ) == 0 )
    {
#if defined(MBEDTLS_ECP_DP_SECP192K1_ENABLED)
        return( DEPENDENCY_SUPPORTED );
#else
        return( DEPENDENCY_NOT_SUPPORTED );
#endif
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_BP512R1_ENABLED" ) == 0 )
    {
#if defined(MBEDTLS_ECP_DP_BP512R1_ENABLED)
        return( DEPENDENCY_SUPPORTED );
#else
        return( DEPENDENCY_NOT_SUPPORTED );
#endif
    }
    if( strcmp( str, "MBEDTLS_ECP_DP_BP256R1_ENABLED" ) == 0 )
    {
#if defined(MBEDTLS_ECP_DP_BP256R1_ENABLED)
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
    if( strcmp( str, "MBEDTLS_ECP_DP_CURVE25519_ENABLED" ) == 0 )
    {
#if defined(MBEDTLS_ECP_DP_CURVE25519_ENABLED)
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
    if( strcmp( str, "MBEDTLS_ECP_DP_BP384R1_ENABLED" ) == 0 )
    {
#if defined(MBEDTLS_ECP_DP_BP384R1_ENABLED)
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

#if defined(TEST_SUITE_ACTIVE)
    ret = DISPATCH_TEST_SUCCESS;

    // Cast to void to avoid compiler warnings
    (void)ret;

    if( strcmp( params[0], "mbedtls_ecp_curve_info" ) == 0 )
    {

        int param1;
        int param2;
        int param3;
        char *param4 = params[4];

        if( cnt != 5 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 5 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_int( params[1], &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_int( params[2], &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_int( params[3], &param3 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param4 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_mbedtls_ecp_curve_info( param1, param2, param3, param4 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "ecp_check_pub" ) == 0 )
    {

        int param1;
        char *param2 = params[2];
        char *param3 = params[3];
        char *param4 = params[4];
        int param5;

        if( cnt != 6 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 6 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_int( params[1], &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param3 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param4 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_int( params[5], &param5 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_ecp_check_pub( param1, param2, param3, param4, param5 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "ecp_test_vect" ) == 0 )
    {

        int param1;
        char *param2 = params[2];
        char *param3 = params[3];
        char *param4 = params[4];
        char *param5 = params[5];
        char *param6 = params[6];
        char *param7 = params[7];
        char *param8 = params[8];
        char *param9 = params[9];

        if( cnt != 10 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 10 );
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
        if( verify_string( &param9 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_ecp_test_vect( param1, param2, param3, param4, param5, param6, param7, param8, param9 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "ecp_test_vec_x" ) == 0 )
    {

        int param1;
        char *param2 = params[2];
        char *param3 = params[3];
        char *param4 = params[4];
        char *param5 = params[5];
        char *param6 = params[6];

        if( cnt != 7 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 7 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_int( params[1], &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param3 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param4 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param5 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param6 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_ecp_test_vec_x( param1, param2, param3, param4, param5, param6 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "ecp_fast_mod" ) == 0 )
    {

        int param1;
        char *param2 = params[2];

        if( cnt != 3 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 3 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_int( params[1], &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_ecp_fast_mod( (mbedtls_ecp_group_id)param1, param2 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "ecp_write_binary" ) == 0 )
    {

        int param1;
        char *param2 = params[2];
        char *param3 = params[3];
        char *param4 = params[4];
        int param5;
        char *param6 = params[6];
        int param7;
        int param8;

        if( cnt != 9 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 9 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_int( params[1], &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param3 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param4 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_int( params[5], &param5 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param6 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_int( params[7], &param7 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_int( params[8], &param8 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_ecp_write_binary( (mbedtls_ecp_group_id)param1, param2, param3, param4, param5, param6, param7, param8 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "ecp_read_binary" ) == 0 )
    {

        int param1;
        char *param2 = params[2];
        char *param3 = params[3];
        char *param4 = params[4];
        char *param5 = params[5];
        int param6;

        if( cnt != 7 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 7 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_int( params[1], &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param3 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param4 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param5 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_int( params[6], &param6 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_ecp_read_binary( (mbedtls_ecp_group_id)param1, param2, param3, param4, param5, param6 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "mbedtls_ecp_tls_read_point" ) == 0 )
    {

        int param1;
        char *param2 = params[2];
        char *param3 = params[3];
        char *param4 = params[4];
        char *param5 = params[5];
        int param6;

        if( cnt != 7 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 7 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_int( params[1], &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param3 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param4 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param5 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_int( params[6], &param6 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_mbedtls_ecp_tls_read_point((mbedtls_ecp_group_id)param1, param2, param3, param4, param5, param6 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "ecp_tls_write_read_point" ) == 0 )
    {

        int param1;

        if( cnt != 2 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 2 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_int( params[1], &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_ecp_tls_write_read_point( (mbedtls_ecp_group_id)param1 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "mbedtls_ecp_tls_read_group" ) == 0 )
    {

        char *param1 = params[1];
        int param2;
        int param3;

        if( cnt != 4 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 4 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_string( &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_int( params[2], &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_int( params[3], &param3 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_mbedtls_ecp_tls_read_group( param1, param2, param3 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "ecp_tls_write_read_group" ) == 0 )
    {

        int param1;

        if( cnt != 2 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 2 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_int( params[1], &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_ecp_tls_write_read_group( param1 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "mbedtls_ecp_check_privkey" ) == 0 )
    {

        int param1;
        char *param2 = params[2];
        int param3;

        if( cnt != 4 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 4 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_int( params[1], &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_int( params[3], &param3 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_mbedtls_ecp_check_privkey( param1, param2, param3 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "mbedtls_ecp_check_pub_priv" ) == 0 )
    {

        int param1;
        char *param2 = params[2];
        char *param3 = params[3];
        int param4;
        char *param5 = params[5];
        char *param6 = params[6];
        char *param7 = params[7];
        int param8;

        if( cnt != 9 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 9 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_int( params[1], &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param2 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param3 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_int( params[4], &param4 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param5 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param6 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_string( &param7 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );
        if( verify_int( params[8], &param8 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_mbedtls_ecp_check_pub_priv( param1, param2, param3, param4, param5, param6, param7, param8 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "mbedtls_ecp_gen_keypair" ) == 0 )
    {

        int param1;

        if( cnt != 2 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 2 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_int( params[1], &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_mbedtls_ecp_gen_keypair( param1 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "mbedtls_ecp_gen_key" ) == 0 )
    {

        int param1;

        if( cnt != 2 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 2 );
            return( DISPATCH_INVALID_TEST_DATA );
        }

        if( verify_int( params[1], &param1 ) != 0 ) return( DISPATCH_INVALID_TEST_DATA );

        test_suite_mbedtls_ecp_gen_key( param1 );
        return ( DISPATCH_TEST_SUCCESS );
    }
    else if( strcmp( params[0], "ecp_selftest" ) == 0 )
    {
#ifdef MBEDTLS_SELF_TEST


        if( cnt != 1 )
        {
            printf("\nIncorrect argument count (%d != %d)\n", cnt, 1 );
            return( DISPATCH_INVALID_TEST_DATA );
        }


        test_suite_ecp_selftest(  );
        return ( DISPATCH_TEST_SUCCESS );
#endif /* MBEDTLS_SELF_TEST */
    }
    else

    {
        printf("FAILED\nSkipping unknown test function '%s'\n", params[0] );
        ret = DISPATCH_TEST_FN_NOT_FOUND;
    }
#else
    ret = DISPATCH_UNSUPPORTED_SUITE;
#endif
    return( ret );
}


/*----------------------------------------------------------------------------*/
/* Main Test code */


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
    printf("|  Crypto mbedtls ECC ECP test suit     |\n");
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


