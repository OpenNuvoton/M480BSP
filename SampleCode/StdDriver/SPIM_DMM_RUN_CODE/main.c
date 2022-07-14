/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    This sample shows how to make an application booting from APROM
 *           with a sub-routine resided on SPIM flash.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include <stdio.h>

#include "NuMicro.h"

#define USE_4_BYTES_MODE            0            /* W25Q20 does not support 4-bytes address mode. */

#define SPIM_CIPHER_ON              0


void spim_routine(void);


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

    /* Set core clock (HCLK) as 160MHz from PLL. SPIM clock run at 80 MHz.            */
    /* The maximum frequency of W25Q20 SPI flash is 80 MHz.                           */
    /* SPIM clock source is HCLK. This will configue SPIM clock as HCLK divided by 2. */
    CLK_SetCoreClock(FREQ_160MHZ);

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

int main()
{
    uint8_t     idBuf[3];

    SYS_Init();                        /* Init System, IP clock and multi-function I/O    */

    UART0_Init();                      /* Initialize UART0                                */

    printf("+--------------------------------------------------+\n");
    printf("|    M480 SPIM DMM mode running program on flash   |\n");
    printf("+--------------------------------------------------+\n");

    SYS_UnlockReg();                   /* Unlock protected registers                      */

    SPIM_SET_CLOCK_DIVIDER(1);        /* Set SPIM clock as HCLK divided by 2 */

    SPIM_SET_RXCLKDLY_RDDLYSEL(0);    /* Insert 0 delay cycle. Adjust the sampling clock of received data to latch the correct data. */
    SPIM_SET_RXCLKDLY_RDEDGE();       /* Use SPI input clock rising edge to sample received data. */

    SPIM_SET_DCNUM(8);                /* 8 is the default value. */

    if (SPIM_InitFlash(1) != 0)        /* Initialized SPI flash */
    {
        printf("SPIM flash initialize failed!\n");
        while (1);
    }

    SPIM_ReadJedecId(idBuf, sizeof (idBuf), 1);
    printf("SPIM get JEDEC ID=0x%02X, 0x%02X, 0x%02X\n", idBuf[0], idBuf[1], idBuf[2]);

    SPIM_DISABLE_CCM();

    //SPIM_DISABLE_CACHE();
    SPIM_ENABLE_CACHE();

    if (SPIM_CIPHER_ON)
        SPIM_ENABLE_CIPHER();
    else
        SPIM_DISABLE_CIPHER();

#if USE_4_BYTES_MODE
    if (SPIM_Enable_4Bytes_Mode(USE_4_BYTES_MODE, 1) != 0)
    {
        printf("SPIM_Enable_4Bytes_Mode failed!\n");
        while (1);
    }
#endif

    SPIM->CTL1 |= SPIM_CTL1_CDINVAL_Msk;        // invalid cache

    SPIM_EnterDirectMapMode(USE_4_BYTES_MODE, CMD_DMA_FAST_READ, 0);

    while (1)
    {
        printf("\n\nProgram is currently running on APROM flash.\n");
        printf("Press any key to branch to sub-routine on SPIM flash...\n");

        getchar();

        spim_routine();
    }
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
