/**************************************************************************//**
 * @file     main.c
 * @version  V1.10
 * @brief    Generate random numbers using Crypto IP PRNG
 *
 * @copyright (C) 2013 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"


#define GENERATE_COUNT      10


static volatile int  g_PRNG_done;

void CRYPTO_IRQHandler()
{
    if (PRNG_GET_INT_FLAG(CRPT))
    {
        g_PRNG_done = 1;
        PRNG_CLR_INT_FLAG(CRPT);
    }
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
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HXT,CLK_CLKDIV0_HCLK(1));

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


int32_t main (void)
{
    uint32_t    i, u32KeySize;
    uint32_t    au32PrngData[8];

    SYS_Init();                        /* Init System, IP clock and multi-function I/O */

    UART0_Init();                      /* Initialize UART0 */

    SYS_UnlockReg();                   /* Unlock register lock protect */

    printf("+-----------------------------------+\n");
    printf("|  M480 Crypto PRNG Sample Demo     |\n");
    printf("+-----------------------------------+\n");

    NVIC_EnableIRQ(CRPT_IRQn);
    PRNG_ENABLE_INT(CRPT);

    for (u32KeySize = PRNG_KEY_SIZE_64; u32KeySize <= PRNG_KEY_SIZE_256; u32KeySize++)
    {
        printf("\n\nPRNG Key size = %s\n\n",(u32KeySize == PRNG_KEY_SIZE_64) ? "64" :
               (u32KeySize == PRNG_KEY_SIZE_128) ? "128" :
               (u32KeySize == PRNG_KEY_SIZE_192) ? "192" :
               (u32KeySize == PRNG_KEY_SIZE_256) ? "256" : "unknown");

        //PRNG_Open(CRPT, u32KeySize, 0, 0);        // start PRNG with default seed
        PRNG_Open(CRPT, u32KeySize, 1, 0x55);     // start PRNG with seed 0x55

        for (i = 0; i < GENERATE_COUNT; i++)
        {
            g_PRNG_done = 0;
            PRNG_Start(CRPT);
            while (!g_PRNG_done);

            memset(au32PrngData, 0, sizeof(au32PrngData));
            PRNG_Read(CRPT, au32PrngData);

            printf("PRNG DATA ==>\n");
            printf("    0x%08x  0x%08x  0x%08x  0x%08x\n", au32PrngData[0], au32PrngData[1], au32PrngData[2], au32PrngData[3]);
            printf("    0x%08x  0x%08x  0x%08x  0x%08x\n", au32PrngData[4], au32PrngData[5], au32PrngData[6], au32PrngData[7]);
        }
    }

    printf("\nAll done.\n");

    while (1);
}



