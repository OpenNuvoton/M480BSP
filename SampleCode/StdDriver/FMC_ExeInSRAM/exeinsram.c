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

int32_t FlashAccess_OnSRAM(void)
{
    uint32_t u32Data, u32RData;
    uint32_t u32Addr;
    uint32_t u32Cnt;

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
        FMC_Write(u32Addr + u32Cnt, u32Data);

        if ((u32Cnt & 0xf) == 0)
            printf(".");

        /* Read Demo */
        u32RData = FMC_Read(u32Addr + u32Cnt);

        if (u32Data != u32RData)
        {
            printf("[Read/Write FAIL]\n");

            while (1);
        }
    }
    printf("\nISP function demo done.\n");

    FMC_DISABLE_AP_UPDATE();
    return 0;
}


/*** (C) COPYRIGHT 2019 Nuvoton Technology Corp. ***/
