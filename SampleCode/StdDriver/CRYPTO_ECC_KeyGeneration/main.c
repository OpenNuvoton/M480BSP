/**************************************************************************//**
 * @file     main.c
 * @version  V1.10
 * $Revision: 10 $
 * $Date: 15/11/19 10:11a $
 * @brief    Show Crypto IP ECC P-192 key generation function.
 *
 * @note
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

#define KEY_LENGTH          192          /* Select ECC P-192 curve, 192-bits key length */

char d[580]  = "e5ce89a34adddf25ff3bf1ffe6803f57d0220de3118798ea";    /* private key */
char Qx[] = "8abf7b3ceb2b02438af19543d3e5b1d573fa9ac60085840f";    /* expected answer: public key 1 */
char Qy[] = "a87f80182dcd56a6a061f81f7da393e7cffd5e0738c6b245";    /* expected answer: public key 2 */

char key1[580], key2[580];               /* temporary buffer used to keep output public keys */

extern void init_adc_init(void);
void adc_trng_gen_key(char *key, int key_len);


void CRYPTO_IRQHandler()
{
    ECC_DriverISR();
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
    int  i;

    SYS_Init();                        /* Init System, IP clock and multi-function I/O */

    UART0_Init();                      /* Initialize UART0 */

    SYS_UnlockReg();                   /* Unlock register lock protect */

    printf("+---------------------------------------------+\n");
    printf("|   Crypto ECC Public Key Generation Demo     |\n");
    printf("+---------------------------------------------+\n");

    NVIC_EnableIRQ(CRPT_IRQn);
    ECC_ENABLE_INT();

    if (ECC_GeneratePublicKey(CURVE_P_192, d, key1, key2) < 0) {
        printf("ECC key generation failed!!\n");
        while (1);
    }

    if (memcmp(Qx, key1, KEY_LENGTH/8)) {

        printf("Public key 1 [%s] is not matched with expected [%s]!\n", key1, Qx);

        if (memcmp(Qx, key1, KEY_LENGTH/8) == 0)
            printf("PASS.\n");
        else
            printf("Error !!\n");


        for (i = 0; i < KEY_LENGTH/8; i++) {
            if (Qx[i] != key1[i])
                printf("\n%d - 0x%x 0x%x\n", i, Qx[i], key1[i]);
        }
        while (1);
    }

    if (memcmp(Qy, key2, KEY_LENGTH/8)) {
        printf("Public key 2 [%s] is not matched with expected [%s]!\n", key2, Qy);
        while (1);
    }

    printf("ECC public key generation test vector compared passed.\n");

    printf("\n\nECC P-192 key pair generation =>\n");

    init_adc_init();
    memset(d, 0, sizeof(d));

    for (i = 0; i < 192; i++) {
        adc_trng_gen_key(d, 192-i);

        if (ECC_IsPrivateKeyValid(CURVE_P_192, d)) {
            break;
        }
    }

    printf("Select private key: [%s]\n", d);

    if (ECC_GeneratePublicKey(CURVE_P_192, d, key1, key2) < 0) {
        printf("ECC key generation failed!!\n");
        while (1);
    }

    printf("Generated public key is:\n");
    printf("Qx: [%s]\n", key1);
    printf("Qy: [%s]\n", key2);


    printf("\n\nECC P-256 key pair generation =>\n");

    memset(d, 0, sizeof(d));
    for (i = 0; i < 256; i++) {
        adc_trng_gen_key(d, 256-i);

        if (ECC_IsPrivateKeyValid(CURVE_P_256, d)) {
            break;
        }
    }

    printf("Select private key: [%s]\n", d);

    if (ECC_GeneratePublicKey(CURVE_P_256, d, key1, key2) < 0) {
        printf("ECC key generation failed!!\n");
        while (1);
    }

    printf("Generated public key is:\n");
    printf("Qx: [%s]\n", key1);
    printf("Qy: [%s]\n", key2);

    while (1);
}



