/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    An example of using FMC driver to set up and erase XOM regions.
 *
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>

#include "NuMicro.h"


#define XOMR0_Base    0x10000

extern int32_t Lib_XOM_ADD(uint32_t a, uint32_t b);


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

int main()
{
    uint32_t    u32Status;

    SYS_Init();                        /* Init System, IP clock and multi-function I/O */

    UART0_Init();                      /* Initialize UART0 */

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x0)
    {
        printf("M480MD does not support XOM!\n");
        while (1);
    }

    /*
     *   This sample code is used to show how to use StdDriver API to enable/erase XOM.
     */
    printf("\n\n");
    printf("+----------------------------------------+\n");
    printf("|  FMC XOM config & erase  Sample Code   |\n");
    printf("+----------------------------------------+\n");

    SYS_UnlockReg();                   /* Unlock register lock protect */
    FMC_Open();                        /* Enable FMC ISP function      */
    FMC_ENABLE_AP_UPDATE();            /* Enable APROM update          */

    /* Read User Configuration */
    printf("  User Config 0 ......................... [0x%08x]\n", FMC_Read(FMC_USER_CONFIG_0));

    if (((FMC->XOMSTS & 0x1) == 0) &&
            (FMC_CheckAllOne(XOMR0_Base, FMC_FLASH_PAGE_SIZE) == READ_ALLONE_YES))
    {
        printf("XOM0 region erased. No program code in XOM0.\n");
        printf("Demo completed. Please re-program flash if you want to run again.\n");
        while (1);
    }

    printf("XOM Status = 0x%X\n", FMC->XOMSTS);
    printf("Any key to continue...\n");
    getchar();

    if((FMC->XOMSTS & 0x1) != 0x1)
    {
        /* Config XOMR0 */
        if(FMC_GetXOMState(XOMR0) == 0)
        {
            u32Status = FMC_ConfigXOM(XOMR0, XOMR0_Base, 1);
            if(u32Status)
                printf("XOMR0 Config fail...\n");
            else
                printf("XOMR0 Config OK...\n");
        }

        printf("\nAny key to reset chip to enable XOM regions...\n");
        getchar();

        /* Reset chip to enable XOM region. */
        SYS_ResetChip();
        while(1) {};
    }

    /* Run XOM function */
    printf("\n");
    printf(" 100 + 200 = %d\n", Lib_XOM_ADD(100, 200));

    printf("\nXOMR0 active success....\n");
    printf("\nAny key to Erase XOM...\n");
    getchar();

    if((FMC->XOMSTS & 0x1) == 0x1)
    {
        /* Erase XOMR0 region */
        if(FMC_EraseXOM(XOMR0) == 0)
            printf("Erase XOMR0....OK\n");
        else
            printf("Erase XOMR0....Fail\n");
    }

    printf("Done.\n");
    while(1);
}

/*** (C) COPYRIGHT 2019 Nuvoton Technology Corp. ***/
