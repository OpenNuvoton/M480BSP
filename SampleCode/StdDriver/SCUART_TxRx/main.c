/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Demonstrate smartcard UART mode by connecting PA.0 and PA.1 pins.
 *
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

// This is the string we used in loopback demo
uint8_t au8TxBuf[] = "Hello World!";


/**
  * @brief  The interrupt services routine of smartcard port 0
  * @param  None
  * @retval None
  */
void SC0_IRQHandler(void)
{
    // Print SCUART received data to UART port
    // Data length here is short, so we're not care about UART FIFO over flow.
    while(!SCUART_GET_RX_EMPTY(SC0))
        UART_WRITE(UART0, SCUART_READ(SC0));

    // RDA is the only interrupt enabled in this sample, this status bit
    // automatically cleared after Rx FIFO empty. So no need to clear interrupt
    // status here.

    return;
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
    CLK_WaitClockReady( CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(SC0_MODULE);

    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));
    CLK_SetModuleClock(SC0_MODULE, CLK_CLKSEL3_SC0SEL_HXT, CLK_CLKDIV1_SC0(1));

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set PA.0 and PA.1 pin for SC UART mode */
    /* Smartcard CLK pin is used for TX, and DAT pin is used for Rx */
    SYS->GPA_MFPL |= (SYS_GPA_MFPL_PA0MFP_SC0_CLK | SYS_GPA_MFPL_PA1MFP_SC0_DAT);

    /* Lock protected registers */
    SYS_LockReg();
}

int main(void)
{
    /* Init System, IP clock and multi-function I/O
       In the end of SYS_Init() will issue SYS_LockReg()
       to lock protected register. If user want to write
       protected register, please issue SYS_UnlockReg()
       to unlock protected register if necessary */
    SYS_Init();

    /* Init UART to 115200-8n1 for print message */
    UART_Open(UART0, 115200);

    printf("This sample code demos smartcard interface UART mode\n");
    printf("Please connect SC0 CLK pin(PA.0) with SC0 DAT pin(PA.1)\n");
    printf("Hit any key to continue\n");
    getchar();

    // Open smartcard interface 0 in UART mode. The line config will be 115200-8n1
    // Can call SCUART_SetLineConfig() later if necessary
    SCUART_Open(SC0, 115200);

    // Enable receive interrupt, no need to use other interrupts in this demo
    SCUART_ENABLE_INT(SC0, SC_INTEN_RDAIEN_Msk);
    NVIC_EnableIRQ(SC0_IRQn);

    // Send the demo string out from SC0_CLK pin
    // Received data from SC0_DAT pin will be print out to UART console
    SCUART_Write(SC0, au8TxBuf, sizeof(au8TxBuf));

    // Loop forever. There's no where to go without an operating system.
    while(1);
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/


