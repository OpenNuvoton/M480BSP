/******************************************************************************
 * @file     xom_entry.c
 * @version  V1.00
 * $Revision: 1 $
 * $Date: 19/01/15 2:06p $
 * @brief    XOM library entry function. It will be located at the beginning
 *           of XOM region such that users can refer to it directly. The user
 *           sends a request to this entry function, which dispatchs the request
 *           to the specified API in XOM and then return the result to user.
 *
 * @note
 * Copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "xom_lib.h"


#define XOM_FUNC_ADD          0x101
#define XOM_FUNC_SUB          0x102
#define XOM_FUNC_MUL          0x103
#define XOM_FUNC_DIV          0x104
#define XOM_FUNC_SUM          0x105

int32_t XOM_Add(int32_t a, int32_t b);
int32_t XOM_Sub(int32_t a, int32_t b);
int32_t XOM_Mul(int32_t a, int32_t b);
int32_t XOM_Div(int32_t a, int32_t b);
int32_t XOM_Sum(int32_t *pbuf, int32_t n);

#ifdef __ARMCC_VERSION                 /* for Keil compiler */
int32_t XOM_Dispatch(int32_t id, int32_t arg1, int32_t arg2, void *output) __attribute__((used));
#endif

int32_t XOM_Dispatch(int32_t id, int32_t arg1, int32_t arg2, void *output)
{
    switch (id)
    {
    case XOM_FUNC_ADD:
        *(int32_t *)output = XOM_Add(arg1, arg2);
        return 0;

    case XOM_FUNC_SUB:
        *(int32_t *)output = XOM_Sub(arg1, arg2);
        return 0;

    case XOM_FUNC_MUL:
        *(int32_t *)output = XOM_Mul(arg1, arg2);
        return 0;

    case XOM_FUNC_DIV:
        if (arg2 == 0)
            return -1;
        *(int32_t *)output = XOM_Div(arg1, arg2);
        return 0;

    case XOM_FUNC_SUM:
        *(int32_t *)output = XOM_Sum((int32_t *)arg1, arg2);
        return 0;
    }
    return -1;
}


