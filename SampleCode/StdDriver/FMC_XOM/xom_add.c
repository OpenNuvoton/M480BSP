/******************************************************************************
 * @file     main.c
 * @version  V3.00
 * $Revision: 3 $
 * $Date: 16/10/17 2:06p $
 * @brief    Show how to use XOM Lirbary
 * @note
 * Copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

int32_t Lib_XOM_ADD(uint32_t a, uint32_t b)
{
    uint32_t c;
    c =  a + b;
    return c;
}
