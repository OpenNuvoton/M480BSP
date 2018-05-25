/**************************************************************************//**
 * @file     parser.c
 * @version  V1.00
 * @brief    A simple parser
 *
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

extern uint32_t  VectorDataBase, VectorDataLimit;

static uint8_t   *file_base;
static uint32_t   file_idx, file_size;


static char  g_line[20*1024];

#ifdef __ICCARM__
#pragma data_alignment=32
uint8_t  g_hmac_msg_pool[1024];
#pragma data_alignment=32
uint8_t  g_hmac_mac_pool[1024];
#else
uint8_t  g_hmac_msg_pool[1024] __attribute__((aligned (32)));
uint8_t  g_hmac_mac_pool[1024] __attribute__((aligned (32)));
#endif

uint8_t   *g_hmac_msg;
uint8_t   *g_hmac_mac;

int       g_key_len, g_msg_len, g_mac_len;
uint32_t  g_sha_mode;

int  open_test_file(void)
{
    file_base = (uint8_t *)&VectorDataBase;
    file_size = (uint32_t)&VectorDataLimit - (uint32_t)&VectorDataBase;
    file_idx = 0;
    return 1;
}


int  close_test_file()
{
    return 0;
}


static int  read_file(uint8_t *buffer, int length)
{
    if (file_idx+1 >= file_size)
        return -1;
    memcpy(buffer, &file_base[file_idx], length);
    file_idx += length;
    return 0;
}


int  my_get_line(void)
{
    int         i;
    uint8_t     ch[2];

    if (file_idx+1 >= file_size)
    {
        //printf("EOF.\n");
        return -1;
    }

    memset(g_line, 0, sizeof(g_line));

    for (i = 0;  ; i++)
    {
        if (read_file(ch, 1) < 0)
            return 0;

        if ((ch[0] == 0x0D) || (ch[0] == 0x0A))
            break;

        g_line[i] = ch[0];
    }

    while (1)
    {
        if (read_file(ch, 1) < 0)
            return 0;

        if ((ch[0] != 0x0D) && (ch[0] != 0x0A))
            break;
    }
    file_idx--;
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
    int     val32;

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
    int         blen;
    uint8_t     *p;

    /* get non-cachable buffer pointer */
    g_hmac_msg = (uint8_t *)g_hmac_msg_pool;
    g_hmac_mac = (uint8_t *)g_hmac_mac_pool;

    g_key_len = 0;

    memset(g_hmac_msg, 0x0, 128);

    while (my_get_line() == 0)
    {
        line_num++;

        if (g_line[0] == '#')
            continue;

        if (strncmp(g_line,"Klen", 4) == 0)
        {
            p = (uint8_t *)&g_line[4];
            while ((*p < '0') || (*p > '9'))
                p++;

            g_key_len = str_to_decimal(p);
            printf("    Key length = %d\n", g_key_len);
            continue;
        }

        if (strncmp(g_line,"Tlen", 4) == 0)
        {
            p = (uint8_t *)&g_line[4];
            while ((*p < '0') || (*p > '9'))
                p++;

            g_mac_len = str_to_decimal(p);
            printf("    HMAC length = %d\n", g_mac_len);
            continue;
        }

        if (strncmp(g_line,"Key", 3) == 0)
        {
            p = (uint8_t *)&g_line[3];
            while (!is_hex_char(*p)) p++;
            if (str_to_hex(p, &g_hmac_msg[0], 0) != g_key_len)
            {
                printf("key len mismatch!\n");
                return -1;
            }
            continue;
        }

        if (strncmp(g_line,"Msg", 3) == 0)
        {
            p = (uint8_t *)&g_line[3];
            while (!is_hex_char(*p)) p++;
            g_msg_len = str_to_hex(p, &g_hmac_msg[(g_key_len+3)&0xfffffffc], 0);
            printf("    Message length = %d\n", g_msg_len);
            continue;
        }

        if (strncmp(g_line,"Mac", 3) == 0)
        {
            p = (uint8_t *)&g_line[3];
            while (!is_hex_char(*p)) p++;
            str_to_hex(p, &g_hmac_mac[0], 0);
            return 0;
        }

        if (strncmp(g_line,"[L=", 3) == 0)
        {
            p = (uint8_t *)&g_line[3];
            while ((*p < '0') || (*p > '9'))
                p++;
            blen = str_to_decimal(p);
            switch (blen)
            {
            case 20:
                g_sha_mode = SHA_MODE_SHA1;
                printf("SHA1...\n");
                break;
            case 28:
                g_sha_mode = SHA_MODE_SHA224;
                printf("SHA224...\n");
                break;
            case 32:
                printf("SHA256...\n");
                g_sha_mode = SHA_MODE_SHA256;
                break;
            case 48:
                printf("SHA384...\n");
                g_sha_mode = SHA_MODE_SHA384;
                break;
            case 64:
                printf("SHA512...\n");
                g_sha_mode = SHA_MODE_SHA512;
                break;
            }
        }

        // printf("LINE %d = %s\n", line_num, g_line);
    }
    return -1;
}

