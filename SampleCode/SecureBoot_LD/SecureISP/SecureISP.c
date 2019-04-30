/**************************************************************************//**
 * @file     SecureISP.c
 * @version  V3.00
 * @brief    SecureISP Library source file
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"
#include "HID_transfer.h"


#include "SecureISP.h"


static char  d[ECC_KBUF_LEN], Qx[ECC_KBUF_LEN], Qy[ECC_KBUF_LEN], z[ECC_KBUF_LEN];
static char  k[ECC_KBUF_LEN], md[ECC_KBUF_LEN], r[ECC_KBUF_LEN], s[ECC_KBUF_LEN];

static char  hex_char_tbl[] = "0123456789abcdef";


uint8_t B2C(uint8_t c)
{
    if(c < 10)
        return (c + '0');
    if(c < 16)
        return (c - 10 + 'a');

    return 0;
}

static char get_Nth_nibble_char(uint32_t val32, uint32_t idx)
{
    return hex_char_tbl[ (val32 >> (idx * 4U)) & 0xfU ];
}

void ISP_Reg2Hex(int32_t count, uint32_t volatile reg[], char output[])
{
    int32_t    idx, ri;
    uint32_t   i;

    output[count] = 0U;
    idx = count - 1;

    for(ri = 0; idx >= 0; ri++)
    {
        for(i = 0UL; (i < 8UL) && (idx >= 0); i++)
        {
            output[idx] = get_Nth_nibble_char(reg[ri], i);
            idx--;
        }
    }
}

static char  ch2hex(char ch)
{
    if (ch <= '9')
    {
        ch = ch - '0';
    }
    else if ((ch <= 'z') && (ch >= 'a'))
    {
        ch = ch - 'a' + 10U;
    }
    else
    {
        ch = ch - 'A' + 10U;
    }
    return ch;
}

void ISP_Hex2Reg(char input[], uint32_t volatile reg[])
{
    char      hex;
    int       si, ri;
    uint32_t  i, val32;

    si = (int)strlen(input) - 1;
    ri = 0;

    while (si >= 0)
    {
        val32 = 0UL;
        for (i = 0UL; (i < 8UL) && (si >= 0); i++)
        {
            hex = ch2hex(input[si]);
            val32 |= (uint32_t)hex << (i * 4UL);
            si--;
        }
        reg[ri++] = val32;
    }
}

int32_t GenECDHKey(char *PrivKey, ECC_PUBKEY_T *PubKey, uint32_t *Key)
{
    volatile int32_t    ret = 0;
    uint32_t            tmp[8];

    memset(Qx, 0x0, sizeof(Qx));
    memset(Qy, 0x0, sizeof(Qy));
    memset(z,  0x0, sizeof(z));

    /* Set Qx */
    memcpy(tmp, (char*)PubKey->au32Key0, sizeof(tmp));
    ISP_BytesSwap((char*)tmp, sizeof(tmp));
    ISP_Reg2Hex(ECC_KEY_LEN, tmp, Qx);

    /* Set Qy */
    memcpy(tmp, (char*)PubKey->au32Key1, sizeof(tmp));
    ISP_BytesSwap((char*)tmp, sizeof(tmp));
    ISP_Reg2Hex(ECC_KEY_LEN, tmp, Qy);

    ISP_DBGMSG("GenECDHKey  d: %s\n", PrivKey);
    ISP_DBGMSG("           Qx: %s\n", Qx);
    ISP_DBGMSG("           Qy: %s\n", Qy);

    ret = ECC_GenerateSecretZ(CRPT, ISP_ECC_CURVE, PrivKey, Qx, Qy, z);
    if (ret < 0)
        return ret;

    ISP_DBGMSG("z:  %s\n", z);

    ISP_Hex2Reg(z, Key);
    ISP_BytesSwap((char *)Key, (ECC_BIT_LEN / 8));

    ISP_DBGMSG("\n");
    return 0;
}

int32_t GenerateECCKeyPair(char *priv, ECC_PUBKEY_T *pubkey)
{
    volatile int32_t    i, ret;

    memset(d,  0x0, sizeof(d));

    /*-------------------------------------------------------------------------*/
    /*  Generate a private key with TRNG                                       */
    /*-------------------------------------------------------------------------*/
    for (i = 0; i < ECC_BIT_LEN; i++)
    {
        TRNG_GenKey(d, ECC_BIT_LEN-i);

        if (ECC_IsPrivateKeyValid(CRPT, ISP_ECC_CURVE, d))
        {
            break;
        }
    }
    //ISP_DBGMSG("Select private key: [%s]\n", d);

    /*-------------------------------------------------------------------------*/
    /*  Generate the public key                                                */
    /*-------------------------------------------------------------------------*/
    if ((ret = ECC_GeneratePublicKey(CRPT, ISP_ECC_CURVE, d, Qx, Qy)) != 0)
    {
        ISP_DBGMSG("\nECC key generation failed!!\n\n");
        return ret;
    }

    ISP_DBGMSG("GenerateECCKeyPair  d:  %s\n", d);
    ISP_DBGMSG("                   Qx: %s\n", Qx);
    ISP_DBGMSG("                   Qy: %s\n", Qy);
    strcpy(priv, d);
    ISP_Hex2Reg(Qx, (volatile uint32_t *)pubkey->au32Key0);
    ISP_Hex2Reg(Qy, (volatile uint32_t *)pubkey->au32Key1);
    ISP_BytesSwap((char *)pubkey->au32Key0, sizeof(pubkey->au32Key0));
    ISP_BytesSwap((char *)pubkey->au32Key1, sizeof(pubkey->au32Key1));
    return 0;
}

static int32_t GenECDSASignature(char *PrivKey, char *msg, uint32_t *R, uint32_t *S)
{
    volatile int32_t    i, ret = 0;

    memset(k, 0x0, sizeof(k));
    memset(r, 0x0, sizeof(r));
    memset(s, 0x0, sizeof(s));
    memset(R, 0x0, sizeof((ECC_BIT_LEN / 8)));
    memset(S, 0x0, sizeof((ECC_BIT_LEN / 8)));

    /*-------------------------------------------------------------------------*/
    /*  Generate the random k with TRNG                                        */
    /*-------------------------------------------------------------------------*/
    for (i = 0; i < ECC_BIT_LEN; i++)
    {
        TRNG_GenKey(k, ECC_BIT_LEN-i);

        if (ECC_IsPrivateKeyValid(CRPT, ISP_ECC_CURVE, k))
        {
            break;
        }
    }

    ret = ECC_GenerateSignature(CRPT, ISP_ECC_CURVE, (char *)msg, PrivKey, k, r, s);
    if (ret < 0)
        return ret;

    ISP_DBGMSG("GenECDSASignature R: %s\n", r);
    ISP_DBGMSG("                  S: %s\n", s);

    ISP_Hex2Reg(r, R);
    ISP_Hex2Reg(s, S);
    return 0;
}

int32_t GenRandomIV(char *msg, ISP_INFO_T *pISPInfo)
{
    uint32_t    m[8], R[8], S[8];

    if (msg == NULL)
    {
        m[0] = SYS->PDID;
        m[1] = FMC_ReadUID(0);
        m[2] = FMC_ReadUID(1);
        m[3] = FMC_ReadUID(2);
        m[4] = FMC_ReadUCID(0);
        m[5] = FMC_ReadUCID(1);
        m[6] = FMC_ReadUCID(2);
        m[7] = FMC_ReadUCID(3);
        ISP_Reg2Hex(ECC_KEY_LEN, m, md);
    }
    else
    {
        strcpy(md, msg);
    }

    GenECDSASignature(MY_PRIVATE_KEY, md, R, S);

    memcpy(pISPInfo->sign.au32R, R, sizeof(R));
    memcpy(pISPInfo->sign.au32S, S, sizeof(S));
    memcpy(pISPInfo->au32AESIV, R, (128 / 8)); // size is 128-bit
    return 0;
}

/**
  * @brief      Open SHA encrypt function
  * @param[in]  start       SHA encrypt start address
  * @param[in]  end         SHA encrypt end address
  * @param[out] digest      The SHA encrypt output digest
  * @param[in]  mode        SHA operation mode, including:
  *                             - \ref SHA_ONESHOT
  *                             - \ref SHA_CONTI_START
  *                             - \ref SHA_CONTI_ING
  *                             - \ref SHA_CONTI_END
  * @retval     0           Success
  * @retval     -1          Failed
  */
int32_t CalculateSHA256(uint32_t start, uint32_t end, uint32_t digest[], E_SHA_OP_MODE mode, E_SHA_SRC src)
{
    volatile int32_t    i, bytes;
    uint32_t            *ptr, addr, data, Hash[8];

    bytes   = end - start;
    ptr     = (uint32_t *)start;
    addr    = (uint32_t)ptr;

    if((mode == SHA_ONESHOT) || (mode == SHA_CONTI_START))
    {
        ISP_DBGMSG("\n[Start SHA256 from 0x%x to 0x%x. (size: %d) (mode: %d)] (%s)\n", start, end, bytes, mode, (src == SHA_SRC_SRAM) ? "SRAM" : "Flash");
        /* CRYPTO */
        CLK->AHBCLK |= CLK_AHBCLK_CRPTCKEN_Msk;

        //CRPT->HMAC_CTL = (SHA_MODE_SHA256 << CRPT_HMAC_CTL_OPMODE_Pos) | CRPT_HMAC_CTL_INSWAP_Msk;
        // Sync output byte order with PC
        CRPT->HMAC_CTL = (SHA_MODE_SHA256 << CRPT_HMAC_CTL_OPMODE_Pos) | CRPT_HMAC_CTL_INSWAP_Msk | CRPT_HMAC_CTL_OUTSWAP_Msk;
        CRPT->HMAC_DMACNT = 64;
        CRPT->HMAC_CTL |= CRPT_HMAC_CTL_START_Msk;
    }
    else
    {
        ISP_DBGMSG("[Continue SHA256 from 0x%x to 0x%x. (size: %d) (mode: %d)]\n", start, end, bytes, mode);
    }

    /* Start to calculate ... */
    while(bytes > 0)
    {
        if(bytes < 64)
            CRPT->HMAC_DMACNT = bytes;

        if(CRPT->HMAC_STS & CRPT_HMAC_STS_DATINREQ_Msk)
        {
            if(src == SHA_SRC_SRAM)
            {
                data = *ptr++;
                bytes -= 4;
            }
            else if(src == SHA_SRC_FLASH)
            {
                /* NOT Support calculate XOM region */
                if(addr < 512)
                    data = FMC_Read((addr & 0x0FFFFFFF)); /* First 512Byte using FMC ISP command */
                else
                    data = inpw((addr & 0x0FFFFFFF));
                addr += 4;
                bytes -= 4;
            }
            if(bytes <= 0)
                bytes = 0;

            /* bytes means remain byte counts */
            if(bytes != 0)
            {
                CRPT->HMAC_DATIN = data;
            }
            else
            {
                if((mode == SHA_ONESHOT) || (mode == SHA_CONTI_END)) /* The last SHA operation */
                {
                    /* It's last word ... *-* */
                    CRPT->HMAC_CTL |= CRPT_HMAC_CTL_START_Msk | CRPT_HMAC_CTL_DMALAST_Msk;
                    CRPT->HMAC_DATIN = data;
                    while(CRPT->HMAC_STS & CRPT_HMAC_STS_BUSY_Msk);

                    for(i = 0; i < 8; i++)
                        Hash[i] = *(uint32_t *)((uint32_t) & (CRPT->HMAC_DGST[0]) + (i * 4));
                    memcpy(digest, Hash, sizeof(Hash));
                    ISP_DBGMSG("\t[SHA256 done]\n");
                    break;
                }
                else
                {
                    CRPT->HMAC_DATIN = data;
                    /* Exit to wait next SHA operation */
                }
            }
        }
    }

    return 0;
    /*
        Verify:
            Input:
                    String char -> "32107654" on PC tool
                    HXE byte    -> "3332313037363534" on PC tool and {0x30313233,0x34353637} in M2351
            Result:
                6952CF8EACE972CD4F10567331B46D85104E9E57402364F205876D13F84F7E42
                ==> Arraty {0x6952CF8E, 0xACE972CD, 0x4F105673....}
    */
}


static int32_t InitUSBDISP(ISP_INFO_T *pISPInfo, USBD_INFO_T *pUSBDInfo)
{
    ISP_DBGMSG("\n[*** Initial USBD ISP mode ***]\n");

    pISPInfo->IsUSBDataReady = FALSE;

    /* Select USBD */
    SYS->USBPHY = (SYS->USBPHY & ~SYS_USBPHY_USBROLE_Msk) | SYS_USBPHY_USBEN_Msk | SYS_USBPHY_SBO_Msk;

    /* Select IP clock source */
    CLK->CLKDIV0 = (CLK->CLKDIV0 & ~CLK_CLKDIV0_USBDIV_Msk) | CLK_CLKDIV0_USB(4);

    /* Enable IP clock */
    CLK_EnableModuleClock(USBD_MODULE);

    /* Set PA.12 ~ PA.14 to input mode */
    PA->MODE &= ~(GPIO_MODE_MODE12_Msk | GPIO_MODE_MODE13_Msk | GPIO_MODE_MODE14_Msk);
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA12MFP_Msk|SYS_GPA_MFPH_PA13MFP_Msk|SYS_GPA_MFPH_PA14MFP_Msk|SYS_GPA_MFPH_PA15MFP_Msk);
    SYS->GPA_MFPH |= (SYS_GPA_MFPH_PA12MFP_USB_VBUS|SYS_GPA_MFPH_PA13MFP_USB_D_N|SYS_GPA_MFPH_PA14MFP_USB_D_P|SYS_GPA_MFPH_PA15MFP_USB_OTG_ID);

    USBDOpen(&gsInfo, (CLASS_REQ)HID_ClassRequest, NULL, (uint32_t *)pUSBDInfo);

    HID_Init();

    NVIC_EnableIRQ(USBD_IRQn);

    USBDStart();

    return 0;
}

static int32_t InitUART1ISP(ISP_INFO_T *pISPInfo)
{
    ISP_DBGMSG("\n[*** Initial UART1 ISP mode ***]\n");

    pISPInfo->IsUARTDataReady = FALSE;

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    UART1->LINE = UART_WORD_LEN_8 | UART_PARITY_NONE | UART_STOP_BIT_1;
    UART1->FIFO = UART_FIFO_RFITL_14BYTES | UART_FIFO_RTSTRGLV_14BYTES;

    UART1->BAUD = (UART_BAUD_MODE2 | UART_BAUD_MODE2_DIVIDER(pISPInfo->UARTClockFreq, 115200));

    UART1->TOUT = 0x40;

    NVIC_SetPriority(UART1_IRQn, 2);
    NVIC_EnableIRQ(UART1_IRQn);

    UART1->INTEN = (UART_INTEN_TOCNTEN_Msk | UART_INTEN_RXTOIEN_Msk | UART_INTEN_RDAIEN_Msk);

    return 0;
}

/**
  * @brief      Initial NuBL1 Secure ISP
  * @param      None
  * @retval     0           Success
  * @retval     -1          Failed
  * @details    This function initial the Secure ISP to update F/W.
  */

int32_t SecureISPInit(ISP_INFO_T *pISPInfo, USBD_INFO_T *pUSBDInfo, E_ISP_MODE mode)
{
    volatile int32_t    ret = 0;

    ISP_DBGMSG("\nIn [SecureISPInit: %d] (%s, %s)\n", mode, __DATE__, __TIME__);

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable FMC ISP function */
    FMC_ENABLE_ISP();
    FMC_DISABLE_AP_UPDATE();
    FMC_DISABLE_LD_UPDATE();
    FMC_DISABLE_CFG_UPDATE();

    /* Init USBD ISP mdoe ...... */
    if((mode & USB_MODE) == USB_MODE)
    {
        if((mode & RESYNC_ISP) == 0x0)
            InitUSBDISP(pISPInfo, pUSBDInfo);
    }

    /* Init UART1 ISP mdoe ...... */
    if((mode & UART_MODE) == UART_MODE)
    {
        if((mode & RESYNC_ISP) == 0x0)
            InitUART1ISP(pISPInfo);
    }

    /* Enable all interrupt */
    __set_PRIMASK(0);

    ret = ProcessISP(pISPInfo);

    return ret;
}

int32_t ProcessISP(ISP_INFO_T *pISPInfo)
{
    volatile int32_t    ret = 0;

    do
    {
        /* Stage 1.*/
        ret = ProcessConnect(pISPInfo);
        if((ret == -1) || (ret == CMD_DISCONNECT) || (ret == CMD_RESYNC))
        {
            if(ret == -1)
                ISP_DBGMSG("\n[FAIL, ProcessConnect]\n");
            break;
        }

        /* Stage 2.*/
        ret = ProcessECDH(pISPInfo);
        if((ret == -1) || (ret == CMD_DISCONNECT) || (ret == CMD_RESYNC))
        {
            if(ret == -1)
                ISP_DBGMSG("\n[FAIL, ProcessECDH]\n");
            break;
        }

        /* Stage 3.*/
        ret = ProcessCommands(pISPInfo);
        if((ret == -1) || (ret == CMD_DISCONNECT) || (ret == CMD_RESYNC))
        {
            if(ret == -1)
                ISP_DBGMSG("\n[FAIL, ProcessCommands]\n");
            break;
        }
    }
    while(0);

    return ret;
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
