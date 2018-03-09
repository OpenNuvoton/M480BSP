/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Show the usage of clock fail detector and clock frequency monitor function.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include "stdio.h"
#include "NuMicro.h"

#define PLL_CLOCK       192000000


/*---------------------------------------------------------------------------------------------------------*/
/*  Clock Fail Detector IRQ Handler                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
void CKFAIL_IRQHandler(void)
{
    uint32_t u32Reg;

    /* Unlock protected registers */
    SYS_UnlockReg();

    u32Reg = CLK->CLKDSTS;

    if(u32Reg & CLK_CLKDSTS_HXTFIF_Msk)
    {
        /* HCLK is switched to HIRC automatically if HXT clock fail interrupt is happened */
        printf("HXT Clock is stopped! HCLK is switched to HIRC.\n");

        /* Disable HXT clock fail interrupt */
        CLK->CLKDCTL &= ~(CLK_CLKDCTL_HXTFDEN_Msk | CLK_CLKDCTL_HXTFIEN_Msk);

        /* Write 1 to clear HXT Clock fail interrupt flag */
        CLK->CLKDSTS = CLK_CLKDSTS_HXTFIF_Msk;
    }

    if(u32Reg & CLK_CLKDSTS_LXTFIF_Msk)
    {
        /* LXT clock fail interrupt is happened */
        printf("LXT Clock is stopped!\n");

        /* Disable HXT clock fail interrupt */
        CLK->CLKDCTL &= ~(CLK_CLKDCTL_LXTFIEN_Msk | CLK_CLKDCTL_LXTFDEN_Msk);

        /* Write 1 to clear LXT Clock fail interrupt flag */
        CLK->CLKDSTS = CLK_CLKDSTS_LXTFIF_Msk;
    }

    if(u32Reg & CLK_CLKDSTS_HXTFQIF_Msk)
    {
        /* HCLK should be switched to HIRC if HXT clock frequency monitor interrupt is happened */
        CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(1));
        printf("HXT Frequency is abnormal! HCLK is switched to HIRC.\n");

        /* Disable HXT clock frequency monitor interrupt */
        CLK->CLKDCTL &= ~(CLK_CLKDCTL_HXTFQDEN_Msk | CLK_CLKDCTL_HXTFQIEN_Msk);

        /* Write 1 to clear HXT Clock frequency monitor interrupt */
        CLK->CLKDSTS = CLK_CLKDSTS_HXTFQIF_Msk;
    }

    /* Lock protected registers */
    SYS_LockReg();

}


void SYS_Init(void)
{

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Set X32_OUT(PF.4) and X32_IN(PF.5) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE4_Msk | GPIO_MODE_MODE5_Msk);

    /* Enable HIRC, HXT and LXT clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);
    CLK_EnableXtalRC(CLK_PWRCTL_LXTEN_Msk);

    /* Wait for HIRC, HXT and LXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);
    CLK_WaitClockReady(CLK_STATUS_LXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HIRC and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set PC multi-function pins for CLKO(PC.13) */
    SYS->GPC_MFPH = (SYS->GPC_MFPH & ~SYS_GPC_MFPH_PC13MFP_Msk) | SYS_GPC_MFPH_PC13MFP_CLKO;

    /* Set PF multi-function pins for X32_OUT(PF.4) and X32_IN(PF.5) */
    SYS->GPF_MFPL &= ~(SYS_GPF_MFPL_PF4MFP_Msk | SYS_GPF_MFPL_PF5MFP_Msk);
    SYS->GPF_MFPL |= SYS_GPF_MFPL_PF4MFP_X32_OUT | SYS_GPF_MFPL_PF5MFP_X32_IN;

}

void UART0_Init(void)
{

    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

int32_t main(void)
{

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Init UART0 for printf */
    UART0_Init();

    printf("\n\nCPU @ %d Hz\n", SystemCoreClock);
    printf("+-------------------------------------------------------------+\n");
    printf("|                 Clock Detector Sample Code                  |\n");
    printf("+-------------------------------------------------------------+\n");
    printf("| 1. HXT clock fail interrupt will happen if HXT is stopped.  |\n");
    printf("|    HCLK clock source will be switched from HXT to HIRC.     |\n");
    printf("| 2. LXT clock fail interrupt will happen if LXT is stopped.  |\n");
    printf("+-------------------------------------------------------------+\n");
    printf("\nStop HXT or LXT to test.\n\n");

    /* Enable clock output, select CLKO clock source as HCLK and set clock output frequency is HCLK/4.
       HCLK clock source will be switched to HIRC if HXT stop and HCLK clock source is from HXT.
       You can check if HCLK clock source is switched to HIRC by clock output pin output frequency.
    */

    /* Output selected clock to CKO, CKO Clock = HCLK / 2^(1 + 1) */
    CLK_EnableCKO(CLK_CLKSEL1_CLKOSEL_HCLK, 1, 0);

    /* Set the HXT clock frequency monitor upper and lower boundary value.
       The upper boundary value should be more than 512*(HXT/HIRC).
       The low boundary value should be less than 512*(HXT/HIRC).
    */
    CLK->CDUPB = 512;
    CLK->CDLOWB = 510;

    /* Set clock fail detector function enabled and interrupt enabled */
    CLK->CLKDCTL = CLK_CLKDCTL_HXTFDEN_Msk |
                   CLK_CLKDCTL_HXTFIEN_Msk |
                   CLK_CLKDCTL_LXTFDEN_Msk |
                   CLK_CLKDCTL_LXTFIEN_Msk |
                   CLK_CLKDCTL_HXTFQDEN_Msk |
                   CLK_CLKDCTL_HXTFQIEN_Msk;

    /* Enable clock fail detector interrupt */
    NVIC_EnableIRQ(CKFAIL_IRQn);

    /* Wait for clock fail detector interrupt happened */
    while(1);

}
