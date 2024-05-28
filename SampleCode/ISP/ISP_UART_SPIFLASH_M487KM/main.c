/***************************************************************************//**
 * @file     main.c
 * @brief    ISP tool main function (only for M487KMCAN)
 * @version  0x32
 * @date     08, May, 2020
 *
 * @note
 * Copyright (C) 2017-2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "targetdev.h"
#include "uart_transfer.h"


#define PLLCON_SETTING          CLK_PLLCTL_160MHz_HIRC
#define PLL_CLOCK               160000000
#define HCLK_DIV                        1

void ProcessHardFault(void);
void SH_Return(void);
void SendChar_ToUART(void);
void SYS_Init(void);

void ProcessHardFault(void) {}
void SH_Return(void) {}
void SendChar_ToUART(void) {}

uint32_t CLK_GetPLLClockFreq(void)
{
    return PLL_CLOCK;
}

void SYS_Init(void)
{
    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable Internal and External RC clock */
    CLK->PWRCTL |= (CLK_PWRCTL_HIRCEN_Msk | CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for Internal RC clock ready */
    while (!(CLK->STATUS & CLK_STATUS_HIRCSTB_Msk));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK->PLLCTL = PLLCON_SETTING;

    while (!(CLK->STATUS & CLK_STATUS_PLLSTB_Msk));

    CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_HCLKSEL_Msk)) | CLK_CLKSEL0_HCLKSEL_PLL;
    CLK->CLKDIV0 &= ~CLK_CLKDIV0_HCLKDIV_Msk;
    CLK->CLKDIV0 |= CLK_CLKDIV0_HCLK(HCLK_DIV);
    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    //SystemCoreClockUpdate();
    PllClock        = PLL_CLOCK;                        // PLL
    SystemCoreClock = PLL_CLOCK / HCLK_DIV;             // HCLK
    CyclesPerUs     = SystemCoreClock / 1000000;  // For SYS_SysTickDelay()
    /* Enable UART module clock */
    CLK->APBCLK0 |= CLK_APBCLK0_UART0CKEN_Msk;
    /* Select UART module clock source */
    CLK->CLKSEL1 &= ~CLK_CLKSEL1_UART0SEL_Msk;
    CLK->CLKSEL1 |= CLK_CLKSEL1_UART0SEL_HIRC;
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init SPIM (ref: SPIM_DMA_RW)                                                                            */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Enable SPIM module clock */
    CLK->AHBCLK |= CLK_AHBCLK_SPIMCKEN_Msk;

    /* Init SPIM multi-function pins, MOSI(PE.2), MISO(PG.13), CLK(PE.4), SS(PG.11), D3(PE.6), and D2(PE.7) */
    SYS->GPE_MFPL &= ~(SYS_GPE_MFPL_PE2MFP_Msk | SYS_GPE_MFPL_PE4MFP_Msk |
                       SYS_GPE_MFPL_PE6MFP_Msk | SYS_GPE_MFPL_PE7MFP_Msk);
    SYS->GPG_MFPH &= ~(SYS_GPG_MFPH_PG11MFP_Msk | SYS_GPG_MFPH_PG13MFP_Msk);
    SYS->GPE_MFPL |= SYS_GPE_MFPL_PE2MFP_SPIM_MOSI | SYS_GPE_MFPL_PE4MFP_SPIM_CLK |
                     SYS_GPE_MFPL_PE6MFP_SPIM_D3 | SYS_GPE_MFPL_PE7MFP_SPIM_D2;
    SYS->GPG_MFPH |= SYS_GPG_MFPH_PG11MFP_SPIM_SS | SYS_GPG_MFPH_PG13MFP_SPIM_MISO;
    PE->SMTEN |= GPIO_SMTEN_SMTEN4_Msk;

    /* Set SPIM I/O pins as high slew rate up to 80 MHz. */
    PE->SLEWCTL = (PE->SLEWCTL & 0xFFFF0CCF) |
                  (0x1<<GPIO_SLEWCTL_HSREN2_Pos) | (0x1<<GPIO_SLEWCTL_HSREN4_Pos) |
                  (0x1<<GPIO_SLEWCTL_HSREN6_Pos) | (0x1<<GPIO_SLEWCTL_HSREN7_Pos);
    PG->SLEWCTL = (PG->SLEWCTL & 0xF33FFFFF) |
                  (0x1<<GPIO_SLEWCTL_HSREN11_Pos) | (0x1<<GPIO_SLEWCTL_HSREN13_Pos);

}

void SPIM_Init()
{
    // uint8_t     idBuf[3];
    SPIM_SET_CLOCK_DIVIDER(1);        /* Set SPIM clock as HCLK divided by 2 */

    SPIM_SET_RXCLKDLY_RDDLYSEL(0);    /* Insert 0 delay cycle. Adjust the sampling clock of received data to latch the correct data. */
    SPIM_SET_RXCLKDLY_RDEDGE();       /* Use SPI input clock rising edge to sample received data. */
    SPIM_SET_DCNUM(8);                /* Set 8 dummy cycle. */
    if (SPIM_InitFlash(1) != 0)       /* Initialized SPI flash */
    {
        printf("SPIM flash initialize failed!\n");
        goto lexit;
    }
    return;

lexit:

    SYS_LockReg();                     /* Lock protected registers */
    while (1);
}

/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/

int main(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();
    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();
    SPIM_Init();
    /* Init UART to 115200-8n1 */
    UART_Init();
    CLK->AHBCLK |= CLK_AHBCLK_ISPCKEN_Msk;
    FMC->ISPCTL |= FMC_ISPCTL_ISPEN_Msk;
    g_apromSize = GetApromSize();
    GetDataFlashInfo(&g_dataFlashAddr, &g_dataFlashSize);
    SysTick->LOAD = 300000 * CyclesPerUs;
    SysTick->VAL   = (0x00);
    SysTick->CTRL = SysTick->CTRL | SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;//using cpu clock

    while (1)
    {
        if ((bufhead >= 4) || (bUartDataReady == TRUE))
        {
            uint32_t lcmd;
            lcmd = inpw(uart_rcvbuf);

            if (lcmd == CMD_CONNECT)
            {
                goto _ISP;
            }
            else
            {
                bUartDataReady = FALSE;
                bufhead = 0;
            }
        }

        //if((SysTick->CTRL & (1 << 16)) != 0)//timeout, then goto APROM
        if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
        {
            goto _APROM;
        }
    }

_ISP:

    while (1)
    {
        if (bUartDataReady == TRUE)
        {
            bUartDataReady = FALSE;
            ParseCmd(uart_rcvbuf, 64);
            PutString();
        }
    }

_APROM:
    SYS->RSTSTS = (SYS_RSTSTS_PORF_Msk | SYS_RSTSTS_PINRF_Msk);
    FMC->ISPCTL &= ~(FMC_ISPCTL_ISPEN_Msk | FMC_ISPCTL_BS_Msk);
    SCB->AIRCR = (V6M_AIRCR_VECTKEY_DATA | V6M_AIRCR_SYSRESETREQ);

    /* Trap the CPU */
    while (1);
}
