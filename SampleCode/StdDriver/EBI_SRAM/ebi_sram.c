/**************************************************************************//**
 * @file     ebi_sram.c
 * @version  V3.00
 * @brief    EBI SRAM Test source file
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

uint32_t g_au32DataArrary[4] = {0x00000000, 0xFFFFFFFF, 0x5A5A5A5A, 0xA5A5A5A5};


/**
  * @brief      This function is used to check SRAM data matched or not.
  */
void SRAM_CompareFunction(uint32_t u32Param0, uint32_t u32Param1, uint32_t u32Param2, uint32_t u32Param3)
{
    uint32_t    u32ReadData, u32CmpData;
    uint32_t    u32Idx;
    uint32_t    u32EBIsize = u32Param1;
    uint32_t    u32Offset = u32Param2;
    uint32_t    u32WriteMode = u32Param3;
    uint8_t     u8D0, u8D1, u8D2, u8D3;
    uint16_t    u16D0, u16D1;

    if(u32Param0 == 4)      // 0x0, 0x1, 0x2, 0x3, 0x4 ... access with offset ......
    {
        /*---------------------------------------------------------------------------------------------------------*/
        /* To check unfixed data pattern                                                                             */
        /*---------------------------------------------------------------------------------------------------------*/
        /* [One Byte Read] compare */
        u32Idx = 0;
        u32ReadData = 0;
        while(u32Idx < u32EBIsize)
        {
            if(u32WriteMode == 0)           // From Byte Write Mode
            {
                u32CmpData = (uint8_t)(u32ReadData + u32Offset);
                if(EBI0_READ_DATA8(u32Idx) != (uint8_t)(u32CmpData))
                {
                    printf("\nSRAM compare fail, Addr= 0x%x\n", (uint32_t)EBI_BANK0_BASE_ADDR + u32Idx);
                    printf("SRAM want data= 0x%x\n", (uint8_t)(u32CmpData));
                    printf("SRAM read data= 0x%x\n",            EBI0_READ_DATA8(u32Idx));
                    printf("One Byte Read compare failed ! \n\n");
                    while(1);
                }
                u32Idx++;
                u32ReadData++;
            }
            else if(u32WriteMode == 1)      // From Half Word Write Mode
            {
                u8D0 = EBI0_READ_DATA8(u32Idx);
                u8D1 = EBI0_READ_DATA8(u32Idx + 1);
                u32CmpData = (uint16_t)(u8D0 + (u8D1 << 8));
                if((uint16_t)(u32ReadData + u32Offset) != (uint16_t)(u32CmpData))
                {
                    printf("\nSRAM compare fail, Addr= 0x%x\n", (uint32_t)EBI_BANK0_BASE_ADDR + u32Idx);
                    printf("SRAM want data= 0x%x\n", (uint16_t)((u32ReadData + u32Offset)));
                    printf("SRAM read data= 0x%x\n", (uint16_t)u32CmpData);
                    printf("One Byte Read compare failed ! \n\n");
                    while(1);
                }
                u32Idx += 2;
                u32ReadData++;
            }
            else if(u32WriteMode == 2)      // From One Word Write Mode
            {
                u8D0 = EBI0_READ_DATA8(u32Idx);
                u8D1 = EBI0_READ_DATA8(u32Idx + 1);
                u8D2 = EBI0_READ_DATA8(u32Idx + 2);
                u8D3 = EBI0_READ_DATA8(u32Idx + 3);
                u32CmpData = (uint32_t)(u8D0 + (u8D1 << 8) + (u8D2 << 16) + (u8D3 << 24));
                if((uint32_t)(u32ReadData + u32Offset) != (uint32_t)(u32CmpData))
                {
                    printf("\nSRAM compare fail, Addr= 0x%x\n", (uint32_t)EBI_BANK0_BASE_ADDR + u32Idx);
                    printf("SRAM want data= 0x%x\n", (uint32_t)((u32ReadData + u32Offset)));
                    printf("SRAM read data= 0x%x\n", (uint32_t)u32CmpData);
                    printf("One Byte Read compare failed ! \n\n");
                    while(1);
                }
                u32Idx += 4;
                u32ReadData++;
            }
        }
        if(u32Idx < u32EBIsize)
        {
            printf("\nOne Byte compare address error 0x%X !\n", (uint32_t)EBI_BANK0_BASE_ADDR + u32Idx);
            while(1);
        }

        /* [Half Word Read] compare */
        u32Idx = 0;
        u32ReadData = 0;
        while(u32Idx < u32EBIsize)
        {
            if(u32WriteMode == 0)           // From Byte Write Mode
            {
                u8D0 = (uint8_t)(u32ReadData + u32Offset);
                u8D1 = (uint8_t)(u32ReadData + u32Offset + 1);
                u32CmpData = (uint16_t)(u8D0 + (u8D1 << 8));
                if(EBI0_READ_DATA16(u32Idx) != (uint16_t)(u32CmpData))
                {
                    printf("\nSRAM compare fail, Addr= 0x%x\n", (uint32_t)EBI_BANK0_BASE_ADDR + u32Idx);
                    printf("SRAM want data= 0x%X\n", (uint16_t)(u32CmpData));
                    printf("SRAM read data= 0x%X\n",            EBI0_READ_DATA16(u32Idx));
                    printf("Half Word Read compare failed ! \n\n");
                    while(1);
                }
                u32Idx += 2;
                u32ReadData += 2;
            }
            else if(u32WriteMode == 1)      // From Half Word Write Mode
            {
                u32CmpData = (uint16_t)(u32ReadData + u32Offset);
                if(EBI0_READ_DATA16(u32Idx) != (uint16_t)(u32CmpData))
                {
                    printf("\nSRAM compare fail, Addr= 0x%x\n", (uint32_t)EBI_BANK0_BASE_ADDR + u32Idx);
                    printf("SRAM want data= 0x%X\n", (uint16_t)(u32CmpData));
                    printf("SRAM read data= 0x%X\n",            EBI0_READ_DATA16(u32Idx));
                    printf("Half Word Read compare failed ! \n\n");
                    while(1);
                }
                u32Idx += 2;
                u32ReadData++;
            }
            else if(u32WriteMode == 2)      // From One Word Write Mode
            {
                u16D0 = EBI0_READ_DATA16(u32Idx);
                u16D1 = EBI0_READ_DATA16(u32Idx + 2);
                u32CmpData = (uint32_t)(u16D0 + (u16D1 << 16));
                if((uint32_t)(u32ReadData + u32Offset) != (uint32_t)(u32CmpData))
                {
                    printf("\nSRAM compare fail, Addr= 0x%x\n", (uint32_t)EBI_BANK0_BASE_ADDR + u32Idx);
                    printf("SRAM want data= 0x%x\n", (uint32_t)((u32ReadData + u32Offset)));
                    printf("SRAM read data= 0x%x\n", (uint32_t)u32CmpData);
                    printf("Half Word Read compare failed ! \n\n");
                    while(1);
                }
                u32Idx += 4;
                u32ReadData++;
            }
        }
        if(u32Idx < u32EBIsize)
        {
            printf("\nHalf Word compare address error 0x%X !\n", (uint32_t)EBI_BANK0_BASE_ADDR + u32Idx);
            while(1);
        }

        /* [One Word Read] compare */
        u32Idx = 0;
        u32ReadData = 0;
        while(u32Idx < u32EBIsize)
        {
            if(u32WriteMode == 0)           // From Byte Write Mode
            {
                u8D0 = (uint8_t)(u32ReadData + u32Offset);
                u8D1 = (uint8_t)(u32ReadData + u32Offset + 1);
                u8D2 = (uint8_t)(u32ReadData + u32Offset + 2);
                u8D3 = (uint8_t)(u32ReadData + u32Offset + 3);
                u32CmpData = (uint32_t)(u8D0 + (u8D1 << 8) + (u8D2 << 16) + (u8D3 << 24));
                if(EBI0_READ_DATA32(u32Idx) != (uint32_t)(u32CmpData))
                {
                    printf("\nSRAM compare fail, Addr= 0x%x\n", (uint32_t)EBI_BANK0_BASE_ADDR + u32Idx);
                    printf("SRAM want data= 0x%X\n", (uint32_t)(u32CmpData));
                    printf("SRAM read data= 0x%X\n",            EBI0_READ_DATA32(u32Idx));
                    printf("One Word Read compare failed ! \n\n");
                    while(1);
                }
                u32Idx += 4;
                u32ReadData += 4;
            }
            else if(u32WriteMode == 1)      // From Half Word Write Mode
            {
                u16D0 = (uint16_t)(u32ReadData + u32Offset);
                u16D1 = (uint16_t)(u32ReadData + u32Offset + 1);
                u32CmpData = (uint32_t)(u16D0 + (u16D1 << 16));
                if(EBI0_READ_DATA32(u32Idx) != (uint32_t)(u32CmpData))
                {
                    printf("\nSRAM compare fail, Addr= 0x%x\n", (uint32_t)EBI_BANK0_BASE_ADDR + u32Idx);
                    printf("SRAM want data= 0x%X\n", (uint32_t)(u32CmpData));
                    printf("SRAM read data= 0x%X\n",            EBI0_READ_DATA32(u32Idx));
                    printf("One Word Read compare failed ! \n\n");
                    while(1);
                }
                u32Idx += 4;
                u32ReadData += 2;
            }
            else if(u32WriteMode == 2)      // From One Word Write Mode
            {
                u32CmpData = (uint32_t)(u32ReadData + u32Offset);
                if(EBI0_READ_DATA32(u32Idx) != (uint32_t)(u32CmpData))
                {
                    printf("\nSRAM compare fail, Addr= 0x%x\n", (uint32_t)EBI_BANK0_BASE_ADDR + u32Idx);
                    printf("SRAM want data= 0x%x\n", (uint32_t)(u32CmpData));
                    printf("SRAM read data= 0x%x\n",            EBI0_READ_DATA32(u32Idx));
                    printf("One Word Read compare failed ! \n\n");
                    while(1);
                }
                u32Idx += 4;
                u32ReadData++;
            }
        }
        if(u32Idx < u32EBIsize)
        {
            printf("\nOne Word compare address error 0x%X !\n", (uint32_t)EBI_BANK0_BASE_ADDR + u32Idx);
            while(1);
        }
    }
    else
    {
        /*---------------------------------------------------------------------------------------------------------*/
        /* To check fixed data pattern                                                                             */
        /*---------------------------------------------------------------------------------------------------------*/
        /* [One Byte Read] compare */
        u32Idx = 0;
        u32ReadData = (uint8_t)g_au32DataArrary[u32Param0];
        while(u32Idx < u32EBIsize)
        {
            if(EBI0_READ_DATA8(u32Idx) != (uint8_t)(u32ReadData))
            {
                printf("\nSRAM compare fail, Addr= 0x%X\n", (uint32_t)EBI_BANK0_BASE_ADDR + u32Idx);
                printf("SRAM want data= 0x%X\n", (uint8_t)(u32ReadData));
                printf("SRAM read data= 0x%X\n",            EBI0_READ_DATA8(u32Idx));
                printf("One Byte Read compare failed ! \n\n");
                while(1);
            }
            u32Idx++;;
        }

        /* [Half Word Read] compare */
        u32Idx = 0;
        u32ReadData = (uint16_t)g_au32DataArrary[u32Param0];
        while(u32Idx < u32EBIsize)
        {
            if(EBI0_READ_DATA16(u32Idx) != (uint16_t)(u32ReadData))
            {
                printf("\nSRAM compare fail, Addr= 0x%X\n", (uint32_t)EBI_BANK0_BASE_ADDR + u32Idx);
                printf("SRAM want data= 0x%X\n", (uint16_t)(u32ReadData));
                printf("SRAM read data= 0x%X\n",            EBI0_READ_DATA16(u32Idx));
                printf("Half Word Read compare failed ! \n\n");
                while(1);
            }
            u32Idx += 2;
        }

        /* [One Word Read] compare */
        u32Idx = 0;
        u32ReadData = (uint32_t)g_au32DataArrary[u32Param0];
        while(u32Idx < u32EBIsize)
        {
            if(EBI0_READ_DATA32(u32Idx) != (uint32_t)(u32ReadData))
            {
                printf("\nSRAM compare fail, Addr= 0x%X\n", (uint32_t)EBI_BANK0_BASE_ADDR + u32Idx);
                printf("SRAM want data= 0x%X\n", (uint32_t)(u32ReadData));
                printf("SRAM read data= 0x%X\n",            EBI0_READ_DATA32(u32Idx));
                printf("One Word Read compare failed ! \n\n");
                while(1);
            }
            u32Idx += 4;
        }
    }
}

/**
  * @brief      This function is used to perform writing data to SRAM and check result.
  */
void SRAM_BS616LV4017(uint32_t u32MaxSize)
{
    uint32_t u32WriteData;
    uint32_t u32Idx, u32DataIdx;
    uint32_t u32EBIsize;

    u32EBIsize = u32MaxSize;
    printf(">> Data width is 16-bit and max. data size is %d KB << \n\n", (u32EBIsize / 1024));

    /* One Byte Write */
    printf("[[ One Byte Write test ]]\n");
    u32DataIdx = 0;
    while(u32DataIdx < 5)
    {
        if(u32DataIdx < 4)
        {
            /*---------------------------------------------------------------------------------------------------------*/
            /* Write fixed data pattern                                                                                */
            /*---------------------------------------------------------------------------------------------------------*/
            u32Idx = 0;
            u32WriteData = g_au32DataArrary[u32DataIdx];
            printf("	All 0x%02X access ... ", (uint8_t)u32WriteData);
            while(u32Idx < u32EBIsize)
            {
                EBI0_WRITE_DATA8(u32Idx, (uint8_t)(u32WriteData));
                u32Idx++;
            }

            /*---------------------------------------------------------------------------------------------------------*/
            /* Read SRAM data and compare with write in data                                                           */
            /*---------------------------------------------------------------------------------------------------------*/
            SRAM_CompareFunction(u32DataIdx, u32EBIsize, 0, 0); // param3:0, Byte Write
            printf("PASS\n");
        }
        else
        {
            /*---------------------------------------------------------------------------------------------------------*/
            /* Write unfixed data pattern                                                                              */
            /*---------------------------------------------------------------------------------------------------------*/
            u32Idx = 0;
            u32WriteData = 0;
            printf("	0x0, 0x1, 0x2, 0x3, 0x4 ... access with offset(0x%X) ... ", (uint32_t)&u32Idx);
            while(u32Idx < u32EBIsize)
            {
                EBI0_WRITE_DATA8(u32Idx, (uint8_t)(u32WriteData + (uint32_t)&u32Idx));
                u32Idx++;
                u32WriteData++;
            }

            /*---------------------------------------------------------------------------------------------------------*/
            /* Read SRAM data and compare with write in data                                                           */
            /*---------------------------------------------------------------------------------------------------------*/
            SRAM_CompareFunction(u32DataIdx, u32EBIsize, (uint32_t)&u32Idx, 0); // param3:0, Byte Write
            printf("PASS\n\n");
        }
        u32DataIdx++;
    }

    /* Half Word Write */
    printf("[[ Half Word Write test]]\n");
    u32DataIdx = 0;
    while(u32DataIdx < 5)
    {
        if(u32DataIdx < 4)
        {
            /*---------------------------------------------------------------------------------------------------------*/
            /* Write fixed data pattern                                                                                */
            /*---------------------------------------------------------------------------------------------------------*/
            u32Idx = 0;
            u32WriteData = g_au32DataArrary[u32DataIdx];
            printf("	All 0x%04X access ... ", (uint16_t)u32WriteData);
            while(u32Idx < u32EBIsize)
            {
                EBI0_WRITE_DATA16(u32Idx, (uint16_t)(u32WriteData));
                u32Idx += 2;
            }

            /*---------------------------------------------------------------------------------------------------------*/
            /* Read SRAM data and compare with write in data                                                           */
            /*---------------------------------------------------------------------------------------------------------*/
            SRAM_CompareFunction(u32DataIdx, u32EBIsize, 0, 1); // param3:1, Half Word Write
            printf("PASS\n");
        }
        else
        {
            /*---------------------------------------------------------------------------------------------------------*/
            /* Write unfixed data pattern                                                                              */
            /*---------------------------------------------------------------------------------------------------------*/
            u32Idx = 0;
            u32WriteData = 0;
            printf("	0x0, 0x1, 0x2, 0x3, 0x4 ... access with offset(0x%X) ... ", (uint32_t)&u32Idx);
            while(u32Idx < u32EBIsize)
            {
                EBI0_WRITE_DATA16(u32Idx, (uint16_t)(u32WriteData + (uint32_t)&u32Idx));
                u32Idx += 2;
                u32WriteData++;
            }

            /*---------------------------------------------------------------------------------------------------------*/
            /* Read SRAM data and compare with write in data                                                           */
            /*---------------------------------------------------------------------------------------------------------*/
            SRAM_CompareFunction(u32DataIdx, u32EBIsize, (uint32_t)&u32Idx, 1); // param3:1, Half Word Write
            printf("PASS\n\n");
        }
        u32DataIdx++;
    }

    /* One Word Write */
    printf("[[ One Word Write test ]]\n");
    u32DataIdx = 0;
    while(u32DataIdx < 5)
    {
        if(u32DataIdx < 4)
        {
            /*---------------------------------------------------------------------------------------------------------*/
            /* Write fixed data pattern                                                                                */
            /*---------------------------------------------------------------------------------------------------------*/
            u32Idx = 0;
            u32WriteData = g_au32DataArrary[u32DataIdx];
            printf("	All 0x%08X access ... ", (uint32_t)u32WriteData);
            while(u32Idx < u32EBIsize)
            {
                EBI0_WRITE_DATA32(u32Idx, (uint32_t)(u32WriteData));
                u32Idx += 4;
            }

            /*---------------------------------------------------------------------------------------------------------*/
            /* Read SRAM data and compare with write in data                                                           */
            /*---------------------------------------------------------------------------------------------------------*/
            SRAM_CompareFunction(u32DataIdx, u32EBIsize, 0, 2); // param3:2, Word Write
            printf("PASS\n");
        }
        else
        {
            /*---------------------------------------------------------------------------------------------------------*/
            /* Write unfixed data pattern                                                                              */
            /*---------------------------------------------------------------------------------------------------------*/
            u32Idx = 0;
            u32WriteData = 0;
            printf("	0x0, 0x1, 0x2, 0x3, 0x4 ... access with offset(0x%X) ... ", (uint32_t)&u32Idx);
            while(u32Idx < u32EBIsize)
            {
                EBI0_WRITE_DATA32(u32Idx, (uint32_t)(u32WriteData + (uint32_t)&u32Idx));
                u32Idx += 4;
                u32WriteData++;
            }

            /*---------------------------------------------------------------------------------------------------------*/
            /* Read SRAM data and compare with write in data                                                           */
            /*---------------------------------------------------------------------------------------------------------*/
            SRAM_CompareFunction(u32DataIdx, u32EBIsize, (uint32_t)&u32Idx, 2); // param3:2, Word Write
            printf("PASS\n\n");
        }
        u32DataIdx++;
    }
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
