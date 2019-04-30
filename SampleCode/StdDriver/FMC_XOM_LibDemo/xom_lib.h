/******************************************************************************
 * @file     xom_lib.h
 * @version  V1.00
 * $Revision: 1 $
 * $Date: 19/01/15 2:06p $
 * @brief    XOM library header file.
 * @note
 * Copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

/*
 *  XOM function ID
 */
#define XOM_FUNC_ADD          0x101
#define XOM_FUNC_SUB          0x102
#define XOM_FUNC_MUL          0x103
#define XOM_FUNC_DIV          0x104
#define XOM_FUNC_SUM          0x105

/*
 *  The physical location of XOM library image.
 */
#define XOM_ADDR              (0x10000|0x1)


typedef int32_t (XOM_FUNC_T)(int32_t id, int32_t, int32_t, void *);

/**
 * @brief       Invoke XOM functions
 * @param[in]   id    The function ID to select one of XOM library functions.
 * @param[in]   arg1  The first argument for selected XOM function.
 * @param[in]   arg2  The second argument for selected XOM function.
 * @param[out]  out   The calculation result.
 * @return      0     Success
 * @return      -1    Failed
 */
__STATIC_INLINE int32_t XOM_func(int32_t id, int32_t arg1, int32_t arg2, void *out)
{
    XOM_FUNC_T  *func = (XOM_FUNC_T *)XOM_ADDR;

    return func(id, arg1, arg2, out);
}



