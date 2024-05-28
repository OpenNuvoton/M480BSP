/****************************************************************************//**
 * @file     exeinsram.c
 * @version  V0.10
 * @brief    Implement a code and execute in SRAM to program embedded Flash.
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

#define APROM_TEST_BASE             0x10000
#define TEST_PATTERN                0x5A5A5A5A

#if defined( __GNUC__ ) && !defined(__ARMCC_VERSION)            /* for GCC compiler */
static __inline__ void * __get_PC(void)
{
    void *pc;
    asm("mov %0, pc" : "=r"(pc));
    return pc;
}
#elif defined(__ARMCC_VERSION)     /* for Keil compiler */
#define __get_PC  __current_pc
#endif

#if defined( __GNUC__ ) && !defined(__ARMCC_VERSION)
__attribute__ ((used, long_call, section(".fastcode"))) int32_t FlashAccess_OnSRAM(void)
#else
int32_t FlashAccess_OnSRAM(void)
#endif
{
    uint32_t u32Data, u32RData;
    uint32_t u32Addr;
    uint32_t u32Cnt;

    printf("\nSub-routine FlashAccess_OnSRAM() is running on SRAM.\n");
    printf("\nCurrent program counter: 0x%x\n", __get_PC());

    SYS_UnlockReg();
    FMC_Open();
    FMC_ENABLE_AP_UPDATE();

    /* The ROM address for erase/write/read demo */
    u32Addr = APROM_TEST_BASE;
    FMC_Erase(u32Addr); /* Erase page */

    for (u32Cnt = 0; u32Cnt < FMC_FLASH_PAGE_SIZE; u32Cnt += 4)
    {
        /* Write Demo */
        u32Data = u32Cnt + 0x12345678;

        if (FMC_Write(u32Addr + u32Cnt, u32Data) != 0)
        {
            printf("FMC_Write failed!\n");
            while (1);
        }

        if ((u32Cnt & 0xf) == 0)
            printf(".");

        /* Read Demo */
        u32RData = FMC_Read(u32Addr + u32Cnt);
        if (g_FMC_i32ErrCode != 0)
        {
            printf("FMC_Read failed!\n");
            while (1);
        }

        if (u32Data != u32RData)
        {
            printf("[Read/Write FAIL]\n");
            while (1);
        }
    }

    printf("\nCurrent program counter: 0x%x\n", __get_PC());

    printf("\nISP function demo done.\n");

    FMC_DISABLE_AP_UPDATE();
    SYS_LockReg();
    return 0;
}

