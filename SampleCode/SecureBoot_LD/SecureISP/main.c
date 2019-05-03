/**************************************************************************//**
 * @file     main.c
 * @version  1.0.0
 * @brief    A secure firmware updater. The updater connects to the Host(PC)
 *           SecureISP tool via an UART or USB connection. It receive commands
 *           from Host to update secure boot firmware in APROM/LDROM.
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NuMicro.h"

#include "SecureISP.h"

#ifdef IS_M480LD
#include "trng.c"
#else
#include "adc_trng.c"
#endif

volatile ISP_INFO_T    g_ISPInfo;
volatile USBD_INFO_T   g_USBDInfo;


/*
 *  Defined the flash regions this ISP firmware allow to be updated.
 */
typedef struct
{
    uint32_t  begin;
    uint32_t  end;
}  FLASH_VR_T;

FLASH_VR_T   _Flash_Valid_Region[] =
{
    { 0x018000, 0x019FFF },
    { 0x020000, 0x03FFFF },
    { 0x100000, 0x100FFF },
    // { 0x300000, 0x30000B },   /* User Configuration */
};

int  IsValidFlashRegion(uint32_t addr, uint32_t size)
{
    int   i;

    for (i = 0; i < sizeof(_Flash_Valid_Region)/sizeof(FLASH_VR_T); i++)
    {
        if ((addr >= _Flash_Valid_Region[i].begin) && (addr+size-1 <= _Flash_Valid_Region[i].end))
            return 1;  /* is in valid region */
    }
    printf("0x%x ~ 0x%x is not valid flash region!!\n", addr, addr+size);
    return 0;   /* not in any valid region */
}

void CRYPTO_IRQHandler()
{
    ECC_Complete(CRPT);
}

void USBD_IRQHandler(void)
{
    ProcessUSBDInterrupt((uint32_t *)&g_ISPInfo, (uint32_t *)&g_USBDInfo);
}

void UART1_IRQHandler(void)
{
    ProcessUART1Interrupt((uint32_t *)&g_ISPInfo);
}

void ResetWDTCounter(void)
{
    WDT_RESET_COUNTER();
    WDT->CTL |= WDT_CTL_IF_Msk;
}

void ISP_BytesSwap(char *buf, int32_t len)
{
    int32_t i;
    char    tmp;

    for(i = 0; i < (len / 2); i++)
    {
        tmp = buf[len - i - 1];
        buf[len - i - 1] = buf[i];
        buf[i] = tmp;
    }
}

/* __REV(x), byte swap32 */
uint32_t ISP_Swap32(uint32_t value)
{
    volatile uint32_t val;

    val = (value << 24) | ((value << 8) & 0xff0000) | ((value >> 8) & 0xff00) | (value >> 24);
    return val;
}

uint32_t GetAPROMSize(void)
{
    if ((inpw(FMC_BASE+0xFF8) & 0xf0) == 0x50)
        return 128*1024;
    else
        return 256*1024;
}

void NuBL_MemCopy(uint8_t dest[], uint8_t src[], uint32_t size)
{
    uint32_t volatile i = 0UL;

    while(size--)
    {
        dest[i] = src[i];
        i++;
    }
}

int32_t ConfigureUSBDISP(void)
{
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

    return 0;
}

int32_t ConfigureUART1ISP(void)
{
    /* Select IP clock source */
    CLK_SetModuleClock(UART1_MODULE, CLK_CLKSEL1_UART1SEL_HXT, CLK_CLKDIV0_UART1(1));

    /* Enable IP clock */
    CLK_EnableModuleClock(UART1_MODULE);

    /*
     *  ISP UART interface using UART1 PB.2(RX) & PB.3(TX)
     */
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB3MFP_Msk | SYS_GPB_MFPL_PB2MFP_Msk);
    SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB3MFP_UART1_TXD | SYS_GPB_MFPL_PB2MFP_UART1_RXD);

    return __HXT;
}

void SetPubKey0(uint32_t *pub0)
{
//char Qx[] = "66e9160410bb8b6834809d3a82f47de552fc461a7916e14c6f04cf2e643428f0";
    pub0[0] = 0x0416e966;
    pub0[1] = 0x688bbb10;
    pub0[2] = 0x3a9d8034;
    pub0[3] = 0xe57df482;
    pub0[4] = 0x1a46fc52;
    pub0[5] = 0x4ce11679;
    pub0[6] = 0x2ecf046f;
    pub0[7] = 0xf0283464;
}

void SetPubKey1(uint32_t *pub1)
{
//char Qy[] = "51d0cb1894c206c205b50cb2d92d6b3f7d706090a42fde95648570c472ea7079";
    pub1[0] = 0x18cbd051;
    pub1[1] = 0xc206c294;
    pub1[2] = 0xb20cb505;
    pub1[3] = 0x3f6b2dd9;
    pub1[4] = 0x9060707d;
    pub1[5] = 0x95de2fa4;
    pub1[6] = 0xc4708564;
    pub1[7] = 0x7970ea72;
}

int32_t ExecuteSecureISP(void)
{
    volatile int32_t    ret = 0;
    volatile uint32_t   ISPmode = UART_MODE, u32UartClkFreq;

    /* Is WDT enabled? */
    if ((WDT->CTL & WDT_CTL_WDTEN_Msk) == WDT_CTL_WDTEN_Msk)
    {
        ISP_DBGMSG("\n[WDT is enabled]\n\n");
        NVIC_EnableIRQ(WDT_IRQn);
        WDT->CTL |= WDT_CTL_INTEN_Msk;
    }

    while(1)
    {
        if (ret == CMD_RESYNC)
        {
            memset((void *)&g_ISPInfo.au32AESKey[0], 0x0, sizeof(g_ISPInfo.au32AESKey));
            memset((void *)&g_ISPInfo.au32AESIV[0], 0x0, sizeof(g_ISPInfo.au32AESIV));
            memset((void *)&g_ISPInfo.sign, 0x0, sizeof(ECDSA_SIGN_T));
            g_ISPInfo.UARTDataIdx = 0;
            g_ISPInfo.IsUSBDataReady = FALSE;
            g_ISPInfo.IsUARTDataReady = FALSE;
            g_ISPInfo.UARTClockFreq = u32UartClkFreq;

            ISPmode |= RESYNC_ISP;
        }
        else
        {
            memset((void *)&g_ISPInfo, 0x0, sizeof(ISP_INFO_T));
            memset((void *)&g_USBDInfo, 0x0, sizeof(USBD_INFO_T));

            /* check if USBD function present */
            if ((inpw(FMC_BASE+0xFF8)&BIT0) == BIT0)
            {
                ConfigureUSBDISP();
                ISPmode = USB_UART_MODE;
            }

            /* configure UART1 pins */
            g_ISPInfo.UARTClockFreq = ConfigureUART1ISP();
            u32UartClkFreq = g_ISPInfo.UARTClockFreq;
        }

        /* Configure global SysInfo */
        SetPubKey0((uint32_t *)g_ISPInfo.ClientPubKey.au32Key0);
        SetPubKey1((uint32_t *)g_ISPInfo.ClientPubKey.au32Key1);

        g_ISPInfo.timeout = SystemCoreClock;

        ret = SecureISPInit((ISP_INFO_T *)&g_ISPInfo, (USBD_INFO_T *)&g_USBDInfo, (E_ISP_MODE)ISPmode);
        if (ret == CMD_RESYNC)
            continue;

        if (ret < 0)
            return ret;

        break;
    }
    return 0;
}


void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable External XTAL (4~24 MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for 12MHz clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Switch HCLK clock source to HXT */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HXT,CLK_CLKDIV0_HCLK(1));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable CRYPTO module clock */
    CLK_EnableModuleClock(CRPT_MODULE);

    /* Select UART0 clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable UART0 clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

}

int32_t main (void)
{
    SYS_Init();
    UART_Open(UART0, 115200);

    printf("\n");
    printf("+-----------------------------------------+\n");
    printf("|      M480LD secure firmware updater     |\n");
    printf("+-----------------------------------------+\n");

    SYS_UnlockReg();                   /* Unlock register lock protect */
    FMC_Open();                        /* Enable FMC ISP function */

    memset((char *)&g_ISPInfo, 0, sizeof(g_ISPInfo));
    memset((char *)&g_USBDInfo, 0, sizeof(g_USBDInfo));

    NVIC_EnableIRQ(CRPT_IRQn);
    ECC_ENABLE_INT(CRPT);

    TRNG_Init();

    ExecuteSecureISP();

    while(1);
}

/*** (C) COPYRIGHT 2018 Nuvoton Technology Corp. ***/

