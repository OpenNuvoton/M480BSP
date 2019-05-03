/**************************************************************************//**
 * @file     main.c
 * @version  V1.10
 * @brief    Show Crypto IP Triple DES CBC mode encrypt/decrypt function
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

/* TDES Key:  1e4678a17f2c8a33 800e15ac47891a4c a011453291c23340 */
uint32_t au8MyTDESKey[3][2] =
{
    { 0x1e4678a1, 0x7f2c8a33 },
    { 0x800e15ac, 0x47891a4c },
    { 0xa0114532, 0x91c23340 }
};

/* Initial vector: 1234567890abcdef */
uint32_t au32MyTDESIV[2] = {  0x12345678, 0x90abcdef };


#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t au8InputData[] =
{
#else
uint8_t au8InputData[] __attribute__((aligned(4))) =
{
#endif
    0x12, 0x34, 0x56, 0x78, 0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56, 0x78, 0xAB, 0xCD, 0xEF
};


#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t au8OutputData[1024];
#else
uint8_t au8OutputData[1024] __attribute__((aligned(4)));
#endif

static volatile int  g_TDES_done;

void CRYPTO_IRQHandler()
{
    if (TDES_GET_INT_FLAG(CRPT))
    {
        g_TDES_done = 1;
        TDES_CLR_INT_FLAG(CRPT);
    }
}

void  dump_buff_hex(uint8_t *pucBuff, int nBytes)
{
    int     nIdx, i;

    nIdx = 0;
    while (nBytes > 0)
    {
        printf("0x%04X  ", nIdx);
        for (i = 0; i < 16; i++)
            printf("%02x ", pucBuff[nIdx + i]);
        printf("  ");
        for (i = 0; i < 16; i++)
        {
            if ((pucBuff[nIdx + i] >= 0x20) && (pucBuff[nIdx + i] < 127))
                printf("%c", pucBuff[nIdx + i]);
            else
                printf(".");
            nBytes--;
        }
        nIdx += 16;
        printf("\n");
    }
    printf("\n");
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
    SYS_Init();                        /* Init System, IP clock and multi-function I/O */

    UART0_Init();                      /* Initialize UART0 */

    SYS_UnlockReg();                   /* Unlock register lock protect */

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1)
    {
        printf("M480LD does not support DES/TDES!\n");
        while (1);
    }

    printf("+--------------------------------------------+\n");
    printf("|           Crypto TDES Driver Sample Code   |\n");
    printf("+--------------------------------------------+\n");

    NVIC_EnableIRQ(CRPT_IRQn);
    TDES_ENABLE_INT(CRPT);

    /*---------------------------------------
     *  TDES CBC mode encrypt
     *---------------------------------------*/
    TDES_Open(CRPT, 0, 1, 1, 1, DES_MODE_CBC, TDES_IN_OUT_WHL_SWAP);  /* 3DES with 3 keys in CBC mode */
    TDES_SetKey(CRPT, 0, au8MyTDESKey);
    TDES_SetInitVect(CRPT, 0, au32MyTDESIV[0], au32MyTDESIV[1]);
    TDES_SetDMATransfer(CRPT, 0, (uint32_t)au8InputData, (uint32_t)au8OutputData, sizeof(au8InputData));

    g_TDES_done = 0;
    TDES_Start(CRPT, 0, CRYPTO_DMA_ONE_SHOT);
    while (!g_TDES_done);

    printf("TDES encrypt done.\n\n");
    dump_buff_hex(au8OutputData, sizeof(au8InputData));

    /*---------------------------------------
     *  TDES CBC mode decrypt
     *---------------------------------------*/
    TDES_Open(CRPT, 0, 0, 1, 1, DES_MODE_CBC, TDES_IN_OUT_WHL_SWAP);
    TDES_SetKey(CRPT, 0, au8MyTDESKey);
    TDES_SetInitVect(CRPT, 0, au32MyTDESIV[0], au32MyTDESIV[1]);
    TDES_SetDMATransfer(CRPT, 0, (uint32_t)au8OutputData, (uint32_t)au8InputData, sizeof(au8InputData));

    g_TDES_done = 0;
    TDES_Start(CRPT, 0, CRYPTO_DMA_ONE_SHOT);
    while (!g_TDES_done);

    printf("TDES decrypt done.\n\n");
    dump_buff_hex(au8InputData, sizeof(au8InputData));

    while (1);
}



