/******************************************************************************
 * @file     main.c
 * @version  V1.00
 * @brief    This sample shows how to configure SPIM CCM as a 32KB SRAM and
 *           execute byte, half-word, and word read/write test on it.
 *
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>

#include "NuMicro.h"


void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable HXT clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Switch HCLK clock source to HXT */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HXT,CLK_CLKDIV0_HCLK(1));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_PCLK0DIV2 | CLK_PCLKDIV_PCLK1DIV2;

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable SPIM module clock */
    CLK_EnableModuleClock(SPIM_MODULE);

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART0 multi-function pins, RXD(PD.2) and TXD(PD.3) */
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD2MFP_Msk | SYS_GPD_MFPL_PD3MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD2MFP_UART0_RXD | SYS_GPD_MFPL_PD3MFP_UART0_TXD);

    /* Init SPIM multi-function pins, MOSI(PC.0), MISO(PC.1), CLK(PC.2), SS(PC.3), D3(PC.4), and D2(PC.5) */
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC0MFP_Msk | SYS_GPC_MFPL_PC1MFP_Msk | SYS_GPC_MFPL_PC2MFP_Msk |
                       SYS_GPC_MFPL_PC3MFP_Msk | SYS_GPC_MFPL_PC4MFP_Msk | SYS_GPC_MFPL_PC5MFP_Msk);
    SYS->GPC_MFPL |= SYS_GPC_MFPL_PC0MFP_SPIM_MOSI | SYS_GPC_MFPL_PC1MFP_SPIM_MISO |
                     SYS_GPC_MFPL_PC2MFP_SPIM_CLK | SYS_GPC_MFPL_PC3MFP_SPIM_SS |
                     SYS_GPC_MFPL_PC4MFP_SPIM_D3 | SYS_GPC_MFPL_PC5MFP_SPIM_D2;

    PC->SMTEN |= GPIO_SMTEN_SMTEN2_Msk;
    /* Lock protected registers */
    SYS_LockReg();
}

void UART0_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

int ccm_read_write(uint32_t addr1, uint32_t addr2)
{
    uint32_t    j;
    uint8_t     byte;
    uint16_t    half_word;
    uint32_t    word;

    printf("Sequential byte read/write test...");

    for (j = addr1; j < addr2; j++)
        *(volatile uint8_t *)j = j & 0xff;

    for (j = addr1; j < addr2; j++) {
        byte = *(volatile uint8_t *)j;
        if (byte != (j & 0xff)) {
            printf("\n  addr=0x%08x, write=0x%02x, read=0x%02x\n", j, j & 0xff, byte);
            return -1;
        }
    }
    printf("[OK]\n");

    printf("Sequential half-word read/write test...");

    for (j = addr1; j < addr2; j+=2)
        *(volatile uint16_t *)j = j & 0xffff;

    for (j = addr1; j < addr2; j+=2) {
        half_word = *(volatile uint16_t *)j;
        if (half_word != (j & 0xffff)) {
            printf("\n  addr=0x%08x, write=0x%04x, read=0x%04x, 0x%04x\n", j, j & 0xffff, half_word, *(volatile uint16_t *)j);
            return -1;
        }
    }
    printf("[OK]\n");

    printf("Sequential word address test...");

    for (j = addr1; j < addr2; j+=4)
        *(volatile uint32_t *)j = j;

    for (j = addr1; j < addr2; j+=4) {
        word = *(volatile uint32_t *)j;
        if (word != j) {
            printf("\n  addr=0x%08x, write=0x%08x, read=0x%08x, 0x%08x\n", j, j, word, *(volatile uint32_t *)j);
            return -1;
        }
    }
    printf("[OK]\n");
    return 0;
}

int main()
{
    SYS_Init();                        /* Init System, IP clock and multi-function I/O */

    UART0_Init();                      /* Initialize UART0 */

    /*---------------------------------------------------------------------------------------------------------*/
    /* SAMPLE CODE                                                                                             */
    /*---------------------------------------------------------------------------------------------------------*/

    printf("+-------------------------------------------+\n");
    printf("|    M480 SPIM CCM SRAM read/write sample   |\n");
    printf("+-------------------------------------------+\n");

    SYS_UnlockReg();                   /* Unlock register lock protect */

    SPIM_DISABLE_CACHE();

    SPIM_ENABLE_CCM();

    if (ccm_read_write(SPIM_CCM_ADDR, SPIM_CCM_ADDR+SPIM_CCM_SIZE) == 0)
        printf("\nSPIM CCM SRAM read/write demo done.\n");
    else
        printf("\nSPIM CCM SRAM read/write test failed!\n");

    while (1);
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
