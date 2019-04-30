/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2018 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "NuMicro.h"


typedef struct
{
    __IO uint32_t CTL;           /*!< [0x0000] TRNG Control Register and Status                                 */
    __I  uint32_t DATA;          /*!< [0x0004] TRNG Data Register                                               */
    __I  uint32_t RESERVE0;
    __IO uint32_t ACT;           /*!< [0x000C] TRNG Activation Register                                         */
} TRNG_T;


#define TRNG_CTL_TRNGEN_Pos              (0)
#define TRNG_CTL_TRNGEN_Msk              (0x1ul << TRNG_CTL_TRNGEN_Pos)

#define TRNG_CTL_DVIF_Pos                (1)
#define TRNG_CTL_DVIF_Msk                (0x1ul << TRNG_CTL_DVIF_Pos)

#define TRNG_CTL_CLKPSC_Pos              (2)
#define TRNG_CTL_CLKPSC_Msk              (0xful << TRNG_CTL_CLKPSC_Pos)

#define TRNG_CTL_DVIEN_Pos               (6)
#define TRNG_CTL_DVIEN_Msk               (0x1ul << TRNG_CTL_DVIEN_Pos)

#define TRNG_CTL_READY_Pos               (7)
#define TRNG_CTL_READY_Msk               (0x1ul << TRNG_CTL_READY_Pos)

#define TRNG_DATA_DATA_Pos               (0)
#define TRNG_DATA_DATA_Msk               (0xfful << TRNG_DATA_DATA_Pos)

#define TRNG_ACT_VER_Pos                 (0)
#define TRNG_ACT_VER_Msk                 (0x7ful << TRNG_ACT_VER_Pos)

#define TRNG_ACT_ACT_Pos                 (7)
#define TRNG_ACT_ACT_Msk                 (0x1ul << TRNG_ACT_ACT_Pos)


#define TRNG                 ((volatile TRNG_T *)0x400B9000UL)


void TRNG_Init(void)
{
#ifdef TRNG_USE_LXT32K
    /* Basic Configuration */
    CLK->PWRCTL |= CLK_PWRCTL_LXTEN_Msk;
    while((CLK->STATUS & CLK_STATUS_LXTSTB_Msk) == 0);
#else
    /* Basic Configuration */
    CLK->PWRCTL |= CLK_PWRCTL_LIRCEN_Msk;
    while((CLK->STATUS & CLK_STATUS_LIRCSTB_Msk) == 0);
    RTC->LXTCTL |= 0x81;
#endif

    CLK->APBCLK1 |= (1<<25);   // CLK_APBCLK1_TRNGCKEN_Msk;

    SYS->IPRST1 |= (1UL<<31);    // SYS_IPRST1_TRNGRST_Msk;
    SYS->IPRST1 ^= (1UL<<31);    // SYS_IPRST1_TRNGRST_Msk;

    TRNG->CTL |= TRNG_CTL_TRNGEN_Msk;

    TRNG->ACT |= TRNG_ACT_ACT_Msk;
    /* Waiting for ready */
    while((TRNG->CTL & TRNG_CTL_READY_Msk) == 0);

    TRNG->CTL = (9 << TRNG_CTL_CLKPSC_Pos);
}

void TRNG_GenKey(char *key, int key_len)
{
    for ( ; key_len > 0; key_len--)
    {
        TRNG->CTL |= TRNG_CTL_TRNGEN_Msk;
        while((TRNG->CTL&TRNG_CTL_DVIF_Msk) == 0);
        *key++ = TRNG->DATA & 0xff;
    }
}



