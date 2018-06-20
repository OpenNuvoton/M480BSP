#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "M480.h"
/******************************************************************************
 * typedef
 ******************************************************************************/
/******************************************************************************
 * Variable
 ******************************************************************************/

/******************************************************************************
 * Prototype
 ******************************************************************************/

/******************************************************************************
 * Private Functions
 ******************************************************************************/
#if 0 //flash testing procedures
AB_Flash_SectorErase(0xa000);

uint32_t addr;
uint8_t ptr[16];
uint8_t len, i;

addr = 0xa000;

while(addr < 0xb000)
{
    len = rand() % 16;

    if(addr + len >= 0xb000)
    {
        len = 0xb000 - addr;
    }

    for(i = 0;  i < len ; i++)
    {
        ptr[i] = (addr + i) & 0xFF;
    }

    printf("%x, %d bytes\n", addr, len);
    AB_Flash_ByteProgram(addr, ptr, len);
    addr += len;
}
#endif

//flash driver
bool AB_Flash_ByteProgram(uint32_t addr, uint8_t * ptr, uint16_t len)
{
    uint32_t data;

    SYS_UnlockReg();
    FMC_Open();
    FMC_ENABLE_AP_UPDATE();

    if(addr & 3)
    {
        uint32_t i;

        data = FMC_Read((addr & ~3));

        for(i = (addr & 3); i < 4 && len; i++)
        {
            data &= ~(0xff << (i * 8));
            data |= (*ptr++ << (i * 8));
            len--;
        }

        FMC_Write((addr & ~3), data);

        addr = (addr & ~3) + 4;
    }

    while(len)
    {
        if(len >= 4)
        {
            data = ptr[0] | (ptr[1] << 8) | (ptr[2] << 16) | (ptr[3] << 24);
            FMC_Write(addr, data);
            len -= 4;
            ptr += 4;
            addr += 4;
        }
        else
        {
            uint32_t i;

            data = FMC_Read(addr);
            for(i = 0; len; i++)
            {
                data &= ~(0xff << (i * 8));
                data |= (*ptr++ << (i * 8));
                len--;
            }

            FMC_Write(addr, data);
        }
    }

    return true;
}

bool AB_Flash_SectorErase(uint32_t addr)
{
    int32_t ret;
    uint8_t i;

    SYS_UnlockReg();
    FMC_Open();
    FMC_ENABLE_AP_UPDATE();

    /*4K*/
    addr = addr & ~4095;
    ret = 0;
    for(i = 0; i < 8; i++)
    {
        ret |= FMC_Erase(addr);
        addr += 512;
    }

    FMC_DISABLE_AP_UPDATE();
    FMC_Close();
    SYS_LockReg();

    return ret == 0;
}


