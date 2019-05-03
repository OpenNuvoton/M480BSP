/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Show Crypto IP HMAC function
 *
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "NuMicro.h"

#include "parser.c"

static volatile int g_HMAC_done;


void CRYPTO_IRQHandler()
{
    if (SHA_GET_INT_FLAG(CRPT))
    {
        g_HMAC_done = 1;
        SHA_CLR_INT_FLAG(CRPT);
    }
}

int do_compare(uint8_t *output, uint8_t *expect, int cmp_len)
{
    int i;

    if (memcmp(expect, output, cmp_len))
    {
        printf("\nMismatch!! - %d\n", cmp_len);
        for (i = 0; i < cmp_len; i++)
            printf("0x%02x    0x%02x\n", expect[i], output[i]);
        return -1;
    }
    return 0;
}

int HMAC_test()
{
    uint32_t au32OutputDigest[16];

    SHA_Open(CRPT, g_sha_mode, SHA_IN_OUT_SWAP, g_key_len);

    SHA_SetDMATransfer(CRPT, (uint32_t) &g_hmac_msg[0], g_msg_len + ((g_key_len + 3) & 0xfffffffc));

    printf("Start HMAC...\n");

    g_HMAC_done = 0;
    SHA_Start(CRPT, CRYPTO_DMA_ONE_SHOT);
    while (!g_HMAC_done) ;

    SHA_Read(CRPT, au32OutputDigest);

    /*--------------------------------------------*/
    /*  Compare                                   */
    /*--------------------------------------------*/
    printf("Comparing result...");
    if (do_compare((uint8_t *)&au32OutputDigest[0], &g_hmac_mac[0], g_mac_len) < 0)
    {
        printf("Compare error!\n");
        while (1);
    }
    printf("OK.\n");
    return 0;
}

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
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HXT, CLK_CLKDIV0_HCLK(1));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable CRYPTO module clock */
    CLK_EnableModuleClock(CRPT_MODULE);

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Lock protected registers */
    SYS_LockReg();
}

void UART0_Init(void)
{

    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

int32_t main(void)
{
    SYS_Init();                        /* Init System, IP clock and multi-function I/O */

    UART0_Init();                      /* Initialize UART0 */

    SYS_UnlockReg();                   /* Unlock register lock protect */

    printf("+-----------------------------------+\n");
    printf("|  M480 Crypto HMAC Sample Demo     |\n");
    printf("+-----------------------------------+\n");

    NVIC_EnableIRQ(CRPT_IRQn);
    SHA_ENABLE_INT(CRPT);

    open_test_file();

    while (1)
    {
        if (get_next_pattern() < 0)
            break;

        if (((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1) &&
                (g_sha_mode != SHA_MODE_SHA256))
        {
            printf("Skip. M480LD only supports SHA-256.\n");
            continue;                  /* M480LD only support SHA-256 */
        }

        HMAC_test();
    }
    close_test_file();

    printf("\n\nHMAC test done.\n");

    while (1) ;
}
