/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    This sample shows how to make an application running on APROM
 *           but with a sub-routine on SPROM, which can be secured.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>

#include "NuMicro.h"


void sprom_routine(void);


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
    int32_t  ret;
    char     chr;                      /* user input character                            */

    SYS_Init();                        /* Init System, IP clock and multi-function I/O    */

    UART0_Init();                      /* Initialize UART0                                */

    SYS_UnlockReg();                   /* Unlock protected registers                      */

    FMC_Open();                        /* Enable FMC ISP function                         */

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1)
    {
        printf("M480LD does not support SPROM.\n");
        while (1);
    }

    while (1)
    {
        printf("\n\n\n");
        printf("+--------------------------------------+\n");
        printf("| M480 FMC SPROM Sample Demo           |\n");
        printf("+--------------------------------------+\n");
        printf("| [1] Lock SPROM                       |\n");
        printf("| [2] Erase SPROM                      |\n");
        printf("| [3] Branch to SPROM                  |\n");
        printf("+--------------------------------------+\n");

        if (FMC->ISPSTS & FMC_ISPSTS_SCODE_Msk)
            printf("ISPSTS=0x%x, SPROM is secured.\n", FMC->ISPSTS);
        else
            printf("ISPSTS=0x%x, SPROM is not secured.\n", FMC->ISPSTS);

        chr = getchar();

        switch (chr)
        {
        case '1':
            printf("Once SPROM is locked, it will become unreadable and can only "
                   "be unlocked by erase SPROM page.\n"
                   "Are you sure to lock SPROM? (y/n)");
            chr = getchar();
            if ((chr == 'y') || (chr == 'Y'))
            {
                FMC_ENABLE_SP_UPDATE();      /* enable SPROM update                   */

                /*
                 * Program a non-0xFF to the last byte of SPROM can make SPROM
                 * enter secure mode. Note that SPROM secure does not become
                 * effective until next chip boot. Because FMC check SPROM secure
                 * byte only when chip booting.
                 */
                if (FMC_Write(FMC_SPROM_END-4, 0x33333333) != 0)
                {
                    printf("FMC_Write address FMC_SPROM_END-4 failed!\n");
                    while (1);
                }

                /*
                 * Issued a chip reset to make SPROM secure mode take effects.
                 */
                SYS->IPRST0 = SYS_IPRST0_CHIPRST_Msk;
            }
            break;

        case '2':
            printf("Please note that this sample have a sub-routine running on SPROM.\n");
            printf("If SPROM was erased, branch to SPROM will cause a program fault.\n");
            printf("Are you sure to erase SPROM? (y/n)");
            chr = getchar();
            if ((chr == 'y') || (chr == 'Y'))
            {
                FMC_ENABLE_SP_UPDATE();      /* enable SPROM update                   */
                ret = FMC_Erase_SPROM();     /* erase SPROM                           */
                FMC_DISABLE_SP_UPDATE();     /* disable SPROM update                  */
                if (ret != 0)
                {
                    printf("FMC_Erase_SPROM failed!\n");
                    while (1);
                }
                printf("\n\nSPROM is erased.\n");
            }
            break;

        case '3':
            sprom_routine();
            break;
        }
    }
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
