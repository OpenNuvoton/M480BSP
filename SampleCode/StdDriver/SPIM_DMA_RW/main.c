/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Show SPIM DMA mode read/write function.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include <stdio.h>
#include <string.h>

#include "NuMicro.h"

// #define HCLK_192MHZ
// #define SUPPORT_4B_ADDR_MODE

#define FLASH_BLOCK_SIZE            (64*1024)    /* Flash block size. Depend on the physical flash. */
#define TEST_BLOCK_ADDR             0x10000      /* Test block address on SPI flash. */
#define BUFFER_SIZE                 2048

#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t  g_buff[BUFFER_SIZE];
#else
uint8_t  g_buff[BUFFER_SIZE] __attribute__((aligned(4)));
#endif


void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Switch HCLK clock source to HXT */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HXT,CLK_CLKDIV0_HCLK(1));

#ifdef HCLK_192MHZ
    /* Set core clock (HCLK) as 192MHz from PLL. SPIM clock run at 48 MHz.            */
    /* The maximum frequency of W25Q20 SPI flash is 80 MHz.                           */
    /* SPIM clock source is HCLK. This will configue SPIM clock as HCLK divided by 4. */
    CLK_SetCoreClock(FREQ_192MHZ);
#else
    /* Set core clock (HCLK) as 160MHz from PLL. SPIM clock run at 80 MHz.            */
    /* The maximum frequency of W25Q20 SPI flash is 80 MHz.                           */
    /* SPIM clock source is HCLK. This will configue SPIM clock as HCLK divided by 2. */
    CLK_SetCoreClock(FREQ_160MHZ);
#endif

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable SPIM module clock */
    CLK_EnableModuleClock(SPIM_MODULE);

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Init SPIM multi-function pins, MOSI(PC.0), MISO(PC.1), CLK(PC.2), SS(PC.3), D3(PC.4), and D2(PC.5) */
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC0MFP_Msk | SYS_GPC_MFPL_PC1MFP_Msk | SYS_GPC_MFPL_PC2MFP_Msk |
                       SYS_GPC_MFPL_PC3MFP_Msk | SYS_GPC_MFPL_PC4MFP_Msk | SYS_GPC_MFPL_PC5MFP_Msk);
    SYS->GPC_MFPL |= SYS_GPC_MFPL_PC0MFP_SPIM_MOSI | SYS_GPC_MFPL_PC1MFP_SPIM_MISO |
                     SYS_GPC_MFPL_PC2MFP_SPIM_CLK | SYS_GPC_MFPL_PC3MFP_SPIM_SS |
                     SYS_GPC_MFPL_PC4MFP_SPIM_D3 | SYS_GPC_MFPL_PC5MFP_SPIM_D2;
    PC->SMTEN |= GPIO_SMTEN_SMTEN2_Msk;

    /* Set SPIM I/O pins as high slew rate up to 80 MHz. */
    PC->SLEWCTL = (PC->SLEWCTL & 0xFFFFF000) |
                  (0x1<<GPIO_SLEWCTL_HSREN0_Pos) | (0x1<<GPIO_SLEWCTL_HSREN1_Pos) |
                  (0x1<<GPIO_SLEWCTL_HSREN2_Pos) | (0x1<<GPIO_SLEWCTL_HSREN3_Pos) |
                  (0x1<<GPIO_SLEWCTL_HSREN4_Pos) | (0x1<<GPIO_SLEWCTL_HSREN5_Pos);

    /* Lock protected registers */
    SYS_LockReg();
}

void UART0_Init(void)
{
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

int  dma_read_write(int is4ByteAddr, uint32_t u32RdCmd, uint32_t WrCmd, int dc_num)
{
    uint32_t    i, offset;             /* variables */
    uint32_t    *pData;

#ifdef SUPPORT_4B_ADDR_MODE
    if (SPIM_Enable_4Bytes_Mode(is4ByteAddr, 1) != 0)
    {
        printf("SPIM_Enable_4Bytes_Mode failed!\n");
        return -1;
    }
#endif

    SPIM_SET_DCNUM(dc_num);

    /*
     *  Erase flash page
     */
    printf("Erase SPI flash block 0x%x...", TEST_BLOCK_ADDR);
    SPIM_EraseBlock(TEST_BLOCK_ADDR, is4ByteAddr, OPCODE_BE_64K, 1, 1);
    printf("done.\n");

    /*
     *  Verify flash page be erased
     */
    if ((u32RdCmd == CMD_DMA_NORMAL_QUAD_READ) || (u32RdCmd == CMD_DMA_FAST_QUAD_READ) ||
            (u32RdCmd == CMD_DMA_FAST_READ_QUAD_OUTPUT))
        SPIM_SetQuadEnable(1, 1);

    printf("Verify SPI flash block 0x%x be erased...", TEST_BLOCK_ADDR);
    for (offset = 0; offset < FLASH_BLOCK_SIZE; offset += BUFFER_SIZE)
    {
        memset(g_buff, 0, BUFFER_SIZE);
        SPIM_DMA_Read(TEST_BLOCK_ADDR+offset, is4ByteAddr, BUFFER_SIZE, g_buff, u32RdCmd, 1);

        pData = (uint32_t *)g_buff;
        for (i = 0; i < BUFFER_SIZE; i += 4, pData++)
        {
            if (*pData != 0xFFFFFFFF)
            {
                printf("FAILED!\n");
                printf("Flash address 0x%x, read 0x%x!\n", TEST_BLOCK_ADDR+i, *pData);
                return -1;
            }
        }
    }

    printf("done.\n");

    SPIM_SetQuadEnable(0, 1);

    /*
     *  Program data to flash block
     */
    printf("Program sequential data to flash block 0x%x...", TEST_BLOCK_ADDR);
    for (offset = 0; offset < FLASH_BLOCK_SIZE; offset += BUFFER_SIZE)
    {
        pData = (uint32_t *)g_buff;
        for (i = 0; i < BUFFER_SIZE; i += 4, pData++)
            *pData = (i << 16) | (TEST_BLOCK_ADDR + offset + i);

        SPIM_DMA_Write(TEST_BLOCK_ADDR+offset, is4ByteAddr, BUFFER_SIZE, g_buff, WrCmd);
    }
    printf("done.\n");

    /*
     *  Verify flash block data
     */
    if ((u32RdCmd == CMD_DMA_NORMAL_QUAD_READ) || (u32RdCmd == CMD_DMA_FAST_QUAD_READ) ||
            (u32RdCmd == CMD_DMA_FAST_READ_QUAD_OUTPUT))
        SPIM_SetQuadEnable(1, 1);

    printf("Verify SPI flash block 0x%x data...", TEST_BLOCK_ADDR);
    for (offset = 0; offset < FLASH_BLOCK_SIZE; offset += BUFFER_SIZE)
    {
        memset(g_buff, 0, BUFFER_SIZE);
        SPIM_DMA_Read(TEST_BLOCK_ADDR+offset, is4ByteAddr, BUFFER_SIZE, g_buff, u32RdCmd, 1);

        pData = (uint32_t *)g_buff;
        for (i = 0; i < BUFFER_SIZE; i += 4, pData++)
        {
            if (*pData != ((i << 16) | (TEST_BLOCK_ADDR + offset + i)))
            {
                printf("FAILED!\n");
                printf("Flash address 0x%x, read 0x%x, expect 0x%x!\n", TEST_BLOCK_ADDR+i, *pData, (i << 16) | (TEST_BLOCK_ADDR + offset + i));
                return -1;
            }
        }

    }
    SPIM_SetQuadEnable(0, 1);
    printf("done.\n");
    return 0;
}

int main()
{
    uint8_t     idBuf[3];

    SYS_Init();                        /* Init System, IP clock and multi-function I/O */

    UART0_Init();                      /* Initialize UART0 */

    /*---------------------------------------------------------------------------------------------------------*/
    /* SAMPLE CODE                                                                                             */
    /*---------------------------------------------------------------------------------------------------------*/

    printf("+-------------------------------------------+\n");
    printf("|    M480 SPIM DMA mode read/write sample   |\n");
    printf("+-------------------------------------------+\n");

    SYS_UnlockReg();                   /* Unlock register lock protect */

#ifdef HCLK_192MHZ
    SPIM_SET_CLOCK_DIVIDER(2);        /* Set SPIM clock as HCLK divided by 4 */

    SPIM_SET_RXCLKDLY_RDDLYSEL(0);    /* Insert 0 delay cycle. Adjust the sampling clock of received data to latch the correct data. */
    SPIM_SET_RXCLKDLY_RDEDGE();       /* Use SPI input clock rising edge to sample received data. */
#else
    SPIM_SET_CLOCK_DIVIDER(1);        /* Set SPIM clock as HCLK divided by 2 */

    SPIM_SET_RXCLKDLY_RDDLYSEL(0);    /* Insert 0 delay cycle. Adjust the sampling clock of received data to latch the correct data. */
    SPIM_SET_RXCLKDLY_RDEDGE();       /* Use SPI input clock rising edge to sample received data. */
#endif
    SPIM_SET_DCNUM(8);                /* Set 8 dummy cycle. */

    if (SPIM_InitFlash(1) != 0)        /* Initialized SPI flash */
    {
        printf("SPIM flash initialize failed!\n");
        goto lexit;
    }

    SPIM_ReadJedecId(idBuf, sizeof (idBuf), 1);
    printf("SPIM get JEDEC ID=0x%02X, 0x%02X, 0x%02X\n", idBuf[0], idBuf[1], idBuf[2]);

    printf("\n[Fast Read] 3-bytes address mode, Fast Read command...");
    if (dma_read_write(0, CMD_DMA_FAST_READ, CMD_NORMAL_PAGE_PROGRAM, 8) < 0)
    {
        printf("  FAILED!!\n");
        goto lexit;
    }
    printf("[OK].\n");

    printf("\n[Fast Read Dual Output] 3-bytes address mode, Fast Read Dual command...");
    if (dma_read_write(0, CMD_DMA_FAST_READ_DUAL_OUTPUT, CMD_NORMAL_PAGE_PROGRAM, 8) < 0)
    {
        printf("  FAILED!!\n");
        goto lexit;
    }
    printf("[OK].\n");

    printf("\n[Fast Read Quad Output] 3-bytes address mode, Fast Read Quad command...");
    if (dma_read_write(0, CMD_DMA_FAST_QUAD_READ, CMD_NORMAL_PAGE_PROGRAM, 4) < 0)
    {
        printf("  FAILED!!\n");
        goto lexit;
    }
    printf("[OK].\n");

#if 0  /* W25Q20 does not support 4-bytes address mode. */
    printf("\n[Fast Read Dual I/O] 4-bytes address mode, dual read...");
    if (dma_read_write(1, CMD_DMA_FAST_DUAL_READ, CMD_NORMAL_PAGE_PROGRAM, 8) < 0)
    {
        printf("  FAILED!!\n");
        goto lexit;
    }
    printf("[OK].\n");

    printf("\n[Fast Read Quad I/O] 4-bytes address mode, quad read...");
    if (dma_read_write(1, CMD_DMA_FAST_QUAD_READ, CMD_NORMAL_PAGE_PROGRAM, 4) < 0)
    {
        printf("  FAILED!!\n");
        goto lexit;
    }
    printf("[OK].\n");
#endif

    printf("\nSPIM DMA read/write demo done.\n");

lexit:

    SYS_LockReg();                     /* Lock protected registers */
    while (1);
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
