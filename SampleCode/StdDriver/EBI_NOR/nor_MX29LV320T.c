/**************************************************************************//**
 * @file     nor_MX29LV320T.c
 * @version  V3.00
 * @brief    NOR Flash - MX29LV320T driver source file
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

/**
  * @brief      Reset NOR Flash
  *
  * @param[in]  u32Bank         Bank number for EBI
  *
  * @return     None
  *
  * @details    Reset MX29LV320T NOR Flash.
  */
void NOR_MX29LV320T_RESET(uint32_t u32Bank)
{
    EBI1_WRITE_DATA16((0x0 << 1), 0xF0);
}


/**
  * @brief      Check Command Status
  *
  * @param[in]  u32DstAddr      The base address for check status algorithm
  * @param[in]  u16Data         The target data for check status algorithm
  * @param[in]  u32TimeoutMs    Maximum time-out period time
  *
  * @retval     0               Command complete
  * @retval     -1              Command fail or time-out
  *
  * @details    This function is used to check the previous command is complete or not.
  */
int32_t NOR_MX29LV320T_CheckStatus(uint32_t u32DstAddr, uint16_t u16Data, uint32_t u32TimeoutMs)
{
    volatile uint16_t u16RData;
    volatile uint32_t u32DelayLoop = 0;

    if(u16Data != 0xEEEE)
    {
        /* Check normal write command status */
        do
        {
            u16RData = EBI1_READ_DATA16(u32DstAddr) & 0xFF;

            /* check DQ7 */
            if((u16RData & (1 << 7)) == (u16Data & (1 << 7)))
                break;

            /* check DQ5 */
            if((u16RData & (1 << 5)) == (1 << 5))
            {
                u16RData = EBI1_READ_DATA16(u32DstAddr) & 0xFF;

                /* check DQ7 */
                if((u16RData & (1 << 7)) == (u16Data & (1 << 7)))
                    break;
                else
                    return -1;
            }

            if(u32DelayLoop++ > u32TimeoutMs)
                return -1;

            CLK_SysTickDelay(1000);
        }
        while(1);
    }
    else
    {
        /* Check erase command status */
        printf("Chip erase ");

        do
        {
            u16RData = EBI1_READ_DATA16(u32DstAddr);

            if(u32DelayLoop++ > u32TimeoutMs)
            {
                printf("\r                                      \r");
                return -1;
            }

            if((u32DelayLoop % 1024) == 0)
                printf(".");

            CLK_SysTickDelay(1000);
        }
        while((u16RData & (1 << 7)) != (1 << 7));

        printf("\r                                      \r");
    }

    return 0;
}

/**
  * @brief      Read NOR Flash
  *
  * @param[in]  u32Bank         Bank number for EBI
  * @param[in]  u32DstAddr      The target address of read command
  *
  * @return     Return the data
  *
  * @details    Read date from specify EBI address.
  */
uint16_t NOR_MX29LV320T_READ(uint32_t u32Bank, uint32_t u32DstAddr)
{
    return EBI1_READ_DATA16(u32DstAddr);
}

/**
  * @brief      Write NOR Flash
  *
  * @param[in]  u32Bank         Bank number for EBI
  * @param[in]  u32DstAddr      The target address of write command
  * @param[in]  u16Data         The target data for write command
  *
  * @retval     0               Write command pass
  * @retval     -1              Write command fail
  *
  * @details    Write date to specify EBI address.
  */
int32_t NOR_MX29LV320T_WRITE(uint32_t u32Bank, uint32_t u32DstAddr, uint16_t u16Data)
{
    /* Command */
    EBI1_WRITE_DATA16((0x555 << 1), 0xAA);
    EBI1_WRITE_DATA16((0x2AA << 1), 0x55);
    EBI1_WRITE_DATA16((0x555 << 1), 0xA0);

    EBI1_WRITE_DATA16(u32DstAddr, u16Data);

    return NOR_MX29LV320T_CheckStatus(u32DstAddr, (u16Data & 0xFF), 100);
}

/**
  * @brief      Get NOR Flash ID
  *
  * @param[in]  u32Bank         Bank number for EBI
  * @param[out] pu16IDTable     The returned pointer is consist of Manufacture ID and Device ID
  *
  * @return     Return Manufacture ID and Device ID
  *
  * @details    Return the ID of MX29LV320T NOR flash.
  */
void NOR_MX29LV320T_GET_ID(uint32_t u32Bank, uint16_t *pu16IDTable)
{
    NOR_MX29LV320T_RESET(u32Bank);

    /* Command */
    EBI1_WRITE_DATA16((0x555 << 1), 0xAA);
    EBI1_WRITE_DATA16((0x2AA << 1), 0x55);
    EBI1_WRITE_DATA16((0x555 << 1), 0x90);
    CLK_SysTickDelay(1000);

    /* Get Manufacture  */
    pu16IDTable[0] = EBI1_READ_DATA16((0x0 << 1));

    /* Get DeviceID  */
    pu16IDTable[1] = EBI1_READ_DATA16((0x1 << 1));

    NOR_MX29LV320T_RESET(u32Bank);
}

/**
  * @brief      NOR Flash Chip Erase
  *
  * @param[in]  u32Bank             Bank number for EBI
  * @param[in]  u32IsCheckBlank     Determine run blank check or not
  *
  * @retval     0                   Erase command pass
  * @retval     -1                  Erase command fail
  *
  * @details    W39L040P whole chip erase.
  */
int32_t NOR_MX29LV320T_EraseChip(uint32_t u32Bank, uint32_t u32IsCheckBlank)
{
    int32_t i32Status = 0;;

    NOR_MX29LV320T_RESET(u32Bank);

    /* Command */
    EBI1_WRITE_DATA16((0x555 << 1), 0xAA);
    EBI1_WRITE_DATA16((0x2AA << 1), 0x55);
    EBI1_WRITE_DATA16((0x555 << 1), 0x80);
    EBI1_WRITE_DATA16((0x555 << 1), 0xAA);
    EBI1_WRITE_DATA16((0x2AA << 1), 0x55);
    EBI1_WRITE_DATA16((0x555 << 1), 0x10);

    i32Status  = NOR_MX29LV320T_CheckStatus(0, 0xEEEE, 30000);
    if(i32Status < 0)
    {
        printf(">> Chip erase ... Time-out !!!\n\n");
        return i32Status;
    }

    if(u32IsCheckBlank)
    {
        /* Run blank check */
        volatile uint32_t u32Addr;
        uint16_t u16RData;

        for(u32Addr = 0; u32Addr < EBI_MAX_SIZE; u32Addr += 2)
        {
            u16RData = NOR_MX29LV320T_READ(u32Bank, u32Addr);

            if(u16RData != 0xFFFF)
            {
                printf("> Chip erase done and blank check FAIL on 0x%08X (R:0x%X)!!!\n\n", u32Addr, u16RData);
                return -1;
            }
        }
        printf(">> Chip erase done and blank check OK !!!\n\n");
    }
    else
    {
        printf(">> Chip erase done !!!\n\n");
    }

    return 0;
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
