/**************************************************************************//**
 * @file     DataFlashProg.c
 * @version  V1.00
 * @brief    M480 Series Data Flash Access API
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/


/*---------------------------------------------------------------------------------------------------------*/
/* Includes of system headers                                                                              */
/*---------------------------------------------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"
#include "dataflashprog.h"

/*---------------------------------------------------------------------------------------------------------*/
/* Macro, type and constant definitions                                                                    */
/*---------------------------------------------------------------------------------------------------------*/

uint32_t g_sectorBuf[FLASH_PAGE_SIZE / 4];

void DataFlashRead(uint32_t addr, uint32_t size, uint32_t buffer)
{
    /* This is low level read function of USB Mass Storage */
    int32_t len;
    uint32_t i;
    uint32_t * pu32Buf = (uint32_t *)buffer;

    /* Modify the address to MASS_STORAGE_OFFSET */
    addr += MASS_STORAGE_OFFSET;

    len = (int32_t)size;

    while(len >= BUFFER_PAGE_SIZE)
    {
        //FMC_ReadPage(addr, (uint32_t *)buffer);
        for(i = 0; i < BUFFER_PAGE_SIZE / 4; i++)
            pu32Buf[i] = FMC_Read(addr + i * 4);
        addr   += BUFFER_PAGE_SIZE;
        buffer += BUFFER_PAGE_SIZE;
        len  -= BUFFER_PAGE_SIZE;
        pu32Buf = (uint32_t *)buffer;
    }
}

void DataFlashReadPage(uint32_t addr, uint32_t buffer)
{
    uint32_t i;
    uint32_t * pu32Buf = (uint32_t *)buffer;

    /* Modify the address to MASS_STORAGE_OFFSET */
    addr += MASS_STORAGE_OFFSET;

    for(i = 0; i < FLASH_PAGE_SIZE / 4; i++)
        pu32Buf[i] = FMC_Read(addr + i * 4);
}

uint32_t DataFlashProgramPage(uint32_t u32StartAddr, uint32_t * u32Buf)
{
    uint32_t i;

    for(i = 0; i < FLASH_PAGE_SIZE / 4; i++)
    {
        FMC_Write(u32StartAddr + i * 4, u32Buf[i]);
    }

    return 0;
}


void DataFlashWrite(uint32_t addr, uint32_t size, uint32_t buffer)
{
    /* This is low level write function of USB Mass Storage */
    int32_t len, i, offset;
    uint32_t *pu32;
    uint32_t alignAddr;

    /* Modify the address to MASS_STORAGE_OFFSET */
    addr += MASS_STORAGE_OFFSET;

    len = (int32_t)size;

    if((len == FLASH_PAGE_SIZE) && ((addr & (FLASH_PAGE_SIZE - 1)) == 0))
    {
        /* Page erase */
        FMC_Erase(addr);

        while(len >= FLASH_PAGE_SIZE)
        {
            DataFlashProgramPage(addr, (uint32_t *) buffer);
            len    -= FLASH_PAGE_SIZE;
            buffer += FLASH_PAGE_SIZE;
            addr   += FLASH_PAGE_SIZE;
        }
    }
    else
    {
        do
        {
            alignAddr = addr & 0xFFF000;

            /* Get the sector offset*/
            offset = (addr & (FLASH_PAGE_SIZE - 1));

            if(offset || (size < FLASH_PAGE_SIZE))
            {
                /* Not 4096-byte alignment. Read the destination page for modification. Note: It needs to avoid adding MASS_STORAGE_OFFSET twice. */
                DataFlashReadPage(alignAddr - MASS_STORAGE_OFFSET, /*FLASH_PAGE_SIZE,*/ (uint32_t)&g_sectorBuf[0]);

            }

            /* Source buffer */
            pu32 = (uint32_t *)buffer;
            /* Get the update length */
            len = FLASH_PAGE_SIZE - offset;
            if(size < len)
                len = size;
            /* Update the destination buffer */
            for(i = 0; i < len / 4; i++)
            {
                g_sectorBuf[offset / 4 + i] = pu32[i];
            }

            /* Page erase */
            FMC_Erase(alignAddr);
            /* Write to the destination page */
            DataFlashProgramPage(alignAddr, (uint32_t *) g_sectorBuf);

            size -= len;
            addr += len;
            buffer += len;

        }
        while(size > 0);
    }
}

