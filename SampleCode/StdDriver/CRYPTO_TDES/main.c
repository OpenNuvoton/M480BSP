/**************************************************************************//**
 * @file     main.c
 * @version  V1.10
 * $Revision: 8 $
 * $Date: 15/11/19 10:48a $
 * @brief    Show Crypto IP Triple DES CBC mode encrypt/decrypt function
 *
 * @note
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

/* TDES Key:  1e4678a17f2c8a33 800e15ac47891a4c a011453291c23340 */
uint32_t au8MyTDESKey[3][2] = {
    { 0x1e4678a1, 0x7f2c8a33 },
    { 0x800e15ac, 0x47891a4c },
    { 0xa0114532, 0x91c23340 }
};

/* Initial vector: 1234567890abcdef */
uint32_t au32MyTDESIV[2] = {  0x12345678, 0x90abcdef };


#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t au8InputData[] = {
#else
__align(4) uint8_t au8InputData[] = {
#endif
    0x12, 0x34, 0x56, 0x78, 0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56, 0x78, 0xAB, 0xCD, 0xEF
};


#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t au8OutputData[1024];
#else
__align(4) uint8_t au8OutputData[1024];
#endif

static volatile int  g_TDES_done;

void CRYPTO_IRQHandler()
{
    if (TDES_GET_INT_FLAG()) {
        g_TDES_done = 1;
        TDES_CLR_INT_FLAG();
    }
}

void  dump_buff_hex(uint8_t *pucBuff, int nBytes)
{
    int     nIdx, i;

    nIdx = 0;
    while (nBytes > 0) {
        printf("0x%04X  ", nIdx);
        for (i = 0; i < 16; i++)
            printf("%02x ", pucBuff[nIdx + i]);
        printf("  ");
        for (i = 0; i < 16; i++) {
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

    /* Enable CRYPTO module clock */
    CLK_EnableModuleClock(CRPT_MODULE);

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART0 multi-function pins, RXD(PD.2) and TXD(PD.3) */
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD2MFP_Msk | SYS_GPD_MFPL_PD3MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD2MFP_UART0_RXD | SYS_GPD_MFPL_PD3MFP_UART0_TXD);

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

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main (void)
{
    SYS_Init();                        /* Init System, IP clock and multi-function I/O */

    UART0_Init();                      /* Initialize UART0 */

    SYS_UnlockReg();                   /* Unlock register lock protect */

    printf("+--------------------------------------------+\n");
    printf("|           Crypto TDES Driver Sample Code   |\n");
    printf("+--------------------------------------------+\n");

    NVIC_EnableIRQ(CRPT_IRQn);
    TDES_ENABLE_INT();

    /*---------------------------------------
     *  TDES CBC mode encrypt
     *---------------------------------------*/
    TDES_Open(0, 1, 1, 1, DES_MODE_CBC, TDES_IN_OUT_WHL_SWAP);  /* 3DES with 3 keys in CBC mode */
    TDES_SetKey(0, au8MyTDESKey);
    TDES_SetInitVect(0, au32MyTDESIV[0], au32MyTDESIV[1]);
    TDES_SetDMATransfer(0, (uint32_t)au8InputData, (uint32_t)au8OutputData, sizeof(au8InputData));

    g_TDES_done = 0;
    TDES_Start(0, CRYPTO_DMA_ONE_SHOT);
    while (!g_TDES_done);

    printf("TDES encrypt done.\n\n");
    dump_buff_hex(au8OutputData, sizeof(au8InputData));

    /*---------------------------------------
     *  TDES CBC mode decrypt
     *---------------------------------------*/
    TDES_Open(0, 0, 1, 1, DES_MODE_CBC, TDES_IN_OUT_WHL_SWAP);
    TDES_SetKey(0, au8MyTDESKey);
    TDES_SetInitVect(0, au32MyTDESIV[0], au32MyTDESIV[1]);
    TDES_SetDMATransfer(0, (uint32_t)au8OutputData, (uint32_t)au8InputData, sizeof(au8InputData));

    g_TDES_done = 0;
    TDES_Start(0, CRYPTO_DMA_ONE_SHOT);
    while (!g_TDES_done);

    printf("TDES decrypt done.\n\n");
    dump_buff_hex(au8InputData, sizeof(au8InputData));

    while (1);
}



