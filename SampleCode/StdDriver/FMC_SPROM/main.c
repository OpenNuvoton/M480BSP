/******************************************************************************
 * @file     main.c
 * @version  V1.00
 * @brief    This sample shows how to make an application running on APROM
 *           but with a sub-routine on SPROM, which can be secured.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>

#include "M480.h"


void sprom_routine(void);


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

int main()
{
    char     chr;                      /* user input character                            */

    SYS_Init();                        /* Init System, IP clock and multi-function I/O    */

    UART0_Init();                      /* Initialize UART0                                */

    /*---------------------------------------------------------------------------------------------------------*/
    /* SAMPLE CODE                                                                                             */
    /*---------------------------------------------------------------------------------------------------------*/

    SYS_UnlockReg();                   /* Unlock protected registers                      */

    FMC_Open();                        /* Enable FMC ISP function                         */

    while (1) {
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

        switch (chr) {
        case '1':
            printf("Once SPROM is locked, it will become unreadable and can only "
                   "be unlocked by erase SPROM page.\n"
                   "Are you sure to lock SPROM? (y/n)");
            chr = getchar();
            if ((chr == 'y') || (chr == 'Y')) {
                FMC_ENABLE_SP_UPDATE();      /* enable SPROM update                   */

                /*
                 * Program a non-0xFF to the last byte of SPROM can make SPROM
                 * enter secure mode. Note that SPROM secure does not become
                 * effective until next chip boot. Because FMC check SPROM secure
                 * byte only when chip booting.
                 */
                FMC_Write(FMC_SPROM_END-4, 0x33333333);
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
            if ((chr == 'y') || (chr == 'Y')) {
                FMC_ENABLE_SP_UPDATE();      /* enable SPROM update                   */
                FMC_Erase_SPROM();           /* erase SPROM                           */
                FMC_DISABLE_SP_UPDATE();     /* disable SPROM update                  */
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
