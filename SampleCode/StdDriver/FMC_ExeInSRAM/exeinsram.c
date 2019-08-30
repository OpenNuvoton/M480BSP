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

static const char message1[] = "[Read/Write FAIL]\n";
static const char message2[] = "\nISP function demo done.\n";

static void SendChar_ToUART(int ch)
{
    while(UART0->FIFOSTS & UART_FIFOSTS_TXFULL_Msk);

    UART0->DAT = ch;
    if(ch == '\n') {
        while(UART0->FIFOSTS & UART_FIFOSTS_TXFULL_Msk);
        UART0->DAT = '\r';
    }
}

static void Put_String(char *str)
{
    while (*str != '\0') {
        SendChar_ToUART(*str);
        str++;
    }
}

static int32_t _FMC_Erase(uint32_t u32PageAddr)
{
    int32_t  ret = 0;

    if (u32PageAddr == FMC_SPROM_BASE) {
        FMC->ISPDAT = 0x0055AA03UL;
    }

    FMC->ISPCMD = FMC_ISPCMD_PAGE_ERASE;
    FMC->ISPADDR = u32PageAddr;
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;

    while (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) { }

    if (FMC->ISPCTL & FMC_ISPCTL_ISPFF_Msk) {
        FMC->ISPCTL |= FMC_ISPCTL_ISPFF_Msk;
        ret = -1;
    }
    return ret;
}

static void _FMC_Write(uint32_t u32Addr, uint32_t u32Data)
{
    FMC->ISPCMD = FMC_ISPCMD_PROGRAM;
    FMC->ISPADDR = u32Addr;
    FMC->ISPDAT = u32Data;
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;
    while (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) { }
}

static uint32_t _FMC_Read(uint32_t u32Addr)
{
    FMC->ISPCMD = FMC_ISPCMD_READ;
    FMC->ISPADDR = u32Addr;
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;
    while (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) { }

    return FMC->ISPDAT;
}

int32_t FlashAccess_OnSRAM(void)
{
    uint32_t u32Data, u32RData;
    uint32_t u32Addr;
    uint32_t u32Cnt;

    SYS_UnlockReg();
    FMC->ISPCTL |=  FMC_ISPCTL_ISPEN_Msk;   /* FMC_Open(); */
    FMC_ENABLE_AP_UPDATE();

    /* The ROM address for erase/write/read demo */
    u32Addr = APROM_TEST_BASE;
    _FMC_Erase(u32Addr); /* Erase page */

    for (u32Cnt = 0; u32Cnt < FMC_FLASH_PAGE_SIZE; u32Cnt += 4) {
        /* Write Demo */
        u32Data = u32Cnt + 0x12345678;
        _FMC_Write(u32Addr + u32Cnt, u32Data);

        if ((u32Cnt & 0xf) == 0)
            SendChar_ToUART('.');

        /* Read Demo */
        u32RData = _FMC_Read(u32Addr + u32Cnt);

        if (u32Data != u32RData) {
            Put_String((char *)message1);

            while (1);
        }
    }
    Put_String((char *)message2);

    FMC_DISABLE_AP_UPDATE();
    return 0;
}


/*** (C) COPYRIGHT 2019 Nuvoton Technology Corp. ***/
