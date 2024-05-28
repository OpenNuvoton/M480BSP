/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME
    m0_evn.h
DESCRIPTION
NOTES
********************************************************************************/
#ifndef __M0_ENV_HH
#define __M0_ENV_HH

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)//hhwu
#include "arm_compat.h"
#endif

void OS_delay_us(uint32_t);

typedef struct
{
    uint16_t     Value;
    uint8_t      Addr;
}__attribute__((packed)) CFG_AFE_REG_INIT_STRU;

typedef struct
{
    uint32_t     Addr;
    uint8_t      ByteAlign;
    uint32_t     Value;
}__attribute__((packed)) CFG_CSR_REG_INIT_STRU;

typedef struct
{
    uint8_t                  NumOfAfeRegInit;
    CFG_AFE_REG_INIT_STRU    AfeRegInit[100];
    uint8_t                  NumOfCsrRegInit;
    CFG_CSR_REG_INIT_STRU    CsrRegInit[100];
} __attribute__((packed)) CFG_PARAMETER_STRU_BASE;


extern volatile uint32_t CRITICAL_DEPTH;

static __inline void ndis_enter_critical()
{
  __disable_irq();
	CRITICAL_DEPTH++;
}


static __inline void ndis_exit_critical()
{
    if (!(--CRITICAL_DEPTH))
    {
       __enable_irq();
    }
}

#define PACKED_WIN32
#define UNPACKED_WIN32

#endif
