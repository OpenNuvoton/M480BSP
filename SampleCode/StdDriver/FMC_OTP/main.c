/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Demonstrate how to program, read, and lock OTP.
 *
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>

#include "NuMicro.h"


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
    uint32_t    i, otp_hw, otp_lw;            /* temporary data */

    SYS_Init();                        /* Init System, IP clock and multi-function I/O */

    UART0_Init();                      /* Initialize UART0 */


    printf("+------------------------------------+\n");
    printf("|   M480 FMC OTP Sample Demo         |\n");
    printf("+------------------------------------+\n");

    SYS_UnlockReg();                   /* Unlock protected registers */

    FMC_Open();                        /* Enable FMC ISP function */

    for (i = 0; i < FMC_OTP_ENTRY_CNT; i++)
    {
        if (FMC_Read_OTP(i, &otp_lw, &otp_hw) != 0)
        {
            printf("Read OTP%d failed!\n", i);
            goto lexit;
        }

        if ((otp_lw == 0xFFFFFFFF) && (otp_hw == 0xFFFFFFFF))
        {
            printf("OTP%d is 0xFFFFFFFF-0xFFFFFFFF. It should be a free entry.\n", i);
            break;
        }
    }

    if (i == FMC_OTP_ENTRY_CNT)
    {
        printf("All OTP entries are used.\n");
        goto lexit;
    }

    printf("Program OTP%d with 0x%x-0x%x...\n", i, 0x5A5A0000 | i, 0x00005A5A | i);

    if (FMC_Write_OTP(i, 0x5A5A0000 | i, 0x00005A5A | i) != 0)
    {
        printf("Failed to program OTP%d!\n", i);
        goto lexit;
    }

    if (FMC_Read_OTP(i, &otp_lw, &otp_hw) != 0)
    {
        printf("Read OTP%d failed after programmed!\n", i);
        goto lexit;
    }

    printf("Read back OTP%d: 0x%x-0x%x.\n", i, otp_lw, otp_hw);

    if ((otp_lw != (0x5A5A0000 | i)) || (otp_hw != (0x00005A5A | i)))
    {
        printf("OTP%d value is not matched with programmed value!\n", i);
        goto lexit;
    }

    printf("Lock OTP%d...\n", i);

    if (FMC_Lock_OTP(i) != 0)
    {
        printf("Failed to lock OTP%d!\n", i);
        goto lexit;
    }

    if (FMC_Read_OTP(i, &otp_lw, &otp_hw) != 0)
    {
        printf("Read OTP%d failed after programmed!\n", i);
        goto lexit;
    }

    printf("Read OTP%d after locked: 0x%x-0x%x.\n", i, otp_lw, otp_hw);

    if ((otp_lw != (0x5A5A0000 | i)) || (otp_hw != (0x00005A5A | i)))
    {
        printf("OTP%d value is incorrect after locked!\n", i);
        goto lexit;
    }

    printf("OTP demo done.\n");

lexit:
    FMC_Close();                       /* Disable FMC ISP function */
    SYS_LockReg();                     /* Lock protected registers */

    while (1);
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
