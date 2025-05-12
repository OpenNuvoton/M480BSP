/***************************************************************************//**
 * @file     main.c
 * @brief    ISP tool main function
 * @version  0x32
 * @date     14, June, 2017
 *
 * @note
 * Copyright (C) 2017-2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "targetdev.h"
#include "i2c_transfer.h"

uint32_t Pclk0;
uint32_t Pclk1;

void ProcessHardFault(void);
void SH_Return(void);
void SendChar_ToUART(void);
void SYS_Init(void);

void ProcessHardFault(void) {}
void SH_Return(void) {}
void SendChar_ToUART(void) {}

#ifdef __ICCARM__
#pragma weak CLK_GetPLLClockFreq
uint32_t CLK_GetPLLClockFreq(void)
#else
__attribute__((weak)) uint32_t CLK_GetPLLClockFreq(void)
#endif
{
    return FREQ_192MHZ;
}

void SYS_Init(void)
{
    SYS_UnlockReg();
    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);
    /* Enable Internal and External XTAL 12MHz clock */
    CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk | CLK_PWRCTL_HXTEN_Msk;

    /* Waiting for external XTAL clock ready */
    while (!(CLK->STATUS & CLK_STATUS_HXTSTB_Msk));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK->PLLCTL = CLK_PLLCTL_192MHz_HXT;

    while (!(CLK->STATUS & CLK_STATUS_PLLSTB_Msk));

    CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_HCLKSEL_Msk)) | CLK_CLKSEL0_HCLKSEL_PLL;
    CLK->CLKDIV0 = (CLK->CLKDIV0 & (~CLK_CLKDIV0_HCLKDIV_Msk)) | CLK_CLKDIV0_HCLK(1);
    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_PCLK0DIV2 | CLK_PCLKDIV_PCLK1DIV2;
    PllClock        = FREQ_192MHZ;
    SystemCoreClock = FREQ_192MHZ;
    CyclesPerUs     = SystemCoreClock / 1000000;  // For SYS_SysTickDelay()
    Pclk0           = SystemCoreClock / 2;
    Pclk1           = SystemCoreClock / 2;
    /* Enable I2C1 clock */
    CLK->APBCLK0 |= CLK_APBCLK0_I2C1CKEN_Msk;
    /* Set I2C1 multi-function pins */
    SYS->GPE_MFPL = (SYS->GPE_MFPL & ~(SYS_GPE_MFPL_PE0MFP_Msk | SYS_GPE_MFPL_PE1MFP_Msk)) |
                    (SYS_GPE_MFPL_PE0MFP_I2C1_SDA | SYS_GPE_MFPL_PE1MFP_I2C1_SCL);
    /* I2C pin enable schmitt trigger */
    PE->SMTEN |= GPIO_SMTEN_SMTEN0_Msk | GPIO_SMTEN_SMTEN1_Msk;
}

int main(void)
{
    uint32_t cmd_buff[16];
    SYS_Init();
    CLK->AHBCLK |= CLK_AHBCLK_ISPCKEN_Msk;
    FMC->ISPCTL |= (FMC_ISPCTL_ISPEN_Msk | FMC_ISPCTL_APUEN_Msk);
    g_apromSize = GetApromSize();
    GetDataFlashInfo(&g_dataFlashAddr, &g_dataFlashSize);
    I2C_Init();
    SysTick->LOAD = 300000 * CyclesPerUs;
    SysTick->VAL   = (0x00);
    SysTick->CTRL = SysTick->CTRL | SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

    while (1)
    {
        if (bI2cDataReady == 1)
        {
            goto _ISP;
        }

        if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
        {
            goto _APROM;
        }
    }

_ISP:

    while (1)
    {
        if (bI2cDataReady == 1)
        {
            NVIC_DisableIRQ(I2C1_IRQn);
            memcpy(cmd_buff, i2c_rcvbuf, 64);
            bI2cDataReady = 0;
            ParseCmd((unsigned char *)cmd_buff, 64);
            NVIC_EnableIRQ(I2C1_IRQn);
        }
    }

_APROM:
    SYS->RSTSTS = (SYS_RSTSTS_PORF_Msk | SYS_RSTSTS_PINRF_Msk);
    FMC->ISPCTL &= ~(FMC_ISPCTL_ISPEN_Msk | FMC_ISPCTL_BS_Msk);
    SCB->AIRCR = (V6M_AIRCR_VECTKEY_DATA | V6M_AIRCR_SYSRESETREQ);

    /* Trap the CPU */
    while (1);
}
