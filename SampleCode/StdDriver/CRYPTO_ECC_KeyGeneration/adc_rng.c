/**************************************************************************//**
 * @file     adc_rng.c
 * @version  V1.10
 * @brief    Use M480 ADC to generate true random numbers.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

#define SNUM        32       /* recorded number of lastest samples */


static uint32_t   adc_val[SNUM];
static uint32_t   val_sum;
static int        oldest;

#ifdef __ICCARM__
#define __inline   inline
#endif

static __inline uint32_t  get_adc_bg_val()
{
    uint32_t  val;

    do
    {
        EADC->SWTRG = (1 << 16);      //Trigger Band-gap
        while ((EADC->STATUS1 & 1) != 1);
        val = (EADC->DAT[16] & 0xFFF);
        //printf("%d\n", val);
    }
    while ((val > 1800) || (val < 1000));
    return val;
}

int  adc_trng_gen_bit()
{
    uint32_t   new_val, average;
    int        ret_val;

    new_val = get_adc_bg_val();

    average = (val_sum / SNUM);   /* sum divided by 32 */

    if (average >= new_val)
        ret_val = 1;
    else
        ret_val = 0;

    //printf("%d - sum = 0x%x, avg = 0x%x, new = 0x%x\n", oldest, val_sum, average, new_val);

    /* kick-off the oldest one and insert the new one */
    val_sum -= adc_val[oldest];
    val_sum += new_val;
    adc_val[oldest] = new_val;
    oldest = (oldest + 1) % SNUM;

    return ret_val;
}


uint32_t  adc_trng_gen_rnd()
{
    int       i;
    uint32_t  val32;

    val32 = 0;
    for (i = 31; i >= 0; i--)
        val32 |= (adc_trng_gen_bit() << i);

    return val32;
}

void adc_trng_gen_key(char *key, int key_len)
{
    int    bcnt = (key_len+3)/4;
    char   c;
    int    i, j;

    memset(key, 0, bcnt);

    for (i = bcnt-1; i >= 0; i--)        /* hex loop */
    {
        c = 0;
        for (j = 0; j < 4; j++)
        {
            c = (c << 1) | adc_trng_gen_bit();
        }

        if (c < 10)
            key[i] = c + '0';
        else
            key[i] = c + 'a' - 10;
    }
}


void  init_adc_init()
{
    int    i;

    /* Enable EADC clock */
    CLK->APBCLK0 |= CLK_APBCLK0_EADCCKEN_Msk;

    /* Set EADC clock divider */
    CLK->CLKDIV0 &= ~CLK_CLKDIV0_EADCDIV_Msk;
    CLK->CLKDIV0 |= (5 << CLK_CLKDIV0_EADCDIV_Pos);

    EADC->CTL = (0x3 << EADC_CTL_RESSEL_Pos) | EADC_CTL_ADCEN_Msk;        /* A/D Converter Enable, select 12-bit ADC result  */

    while (!(EADC->PWRM & EADC_PWRM_PWUPRDY_Msk));

    EADC->SCTL[16] = (0x70 << EADC_SCTL_EXTSMPT_Pos)  /* ADC Sampling Time Extend          */
                     | (0x0 << EADC_SCTL_TRGSEL_Pos);      /* A/D SAMPLE Start of Conversion Trigger Source Selection */

    val_sum = 0;
    for (i = 0; i < SNUM; i++)
    {
        adc_val[i] = get_adc_bg_val();
        // printf("int adc val = 0x%x\n", adc_val[i]);
        val_sum += adc_val[i];
    }
    oldest = 0;

    adc_trng_gen_rnd();    // drop the first 32-bits
}





