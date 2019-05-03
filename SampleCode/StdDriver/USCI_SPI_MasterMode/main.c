/*************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief
 *          Configure USCI_SPI1 as Master mode and demonstrate how to communicate with an off-chip SPI Slave device.
 *          Needs to work with USCI_SPI_SlaveMode sample code.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"


#define TEST_COUNT  16
#define PLL_CLOCK   192000000

uint32_t g_au32SourceData[TEST_COUNT];
uint32_t g_au32DestinationData[TEST_COUNT];
volatile uint32_t g_u32TxDataCount;
volatile uint32_t g_u32RxDataCount;

/* Function prototype declaration */
void SYS_Init(void);
void USCI_SPI_Init(void);


int main()
{
    uint32_t u32DataCount;

    /* Unlock protected registers */
    SYS_UnlockReg();
    /* Init System, IP clock and multi-function I/O. */
    SYS_Init();
    /* Lock protected registers */
    SYS_LockReg();

    /* Configure UART0: 115200, 8-bit word, no parity bit, 1 stop bit. */
    UART_Open(UART0, 115200);

    /* Init USCI_SPI1 */
    USCI_SPI_Init();

    printf("\n\n");
    printf("+--------------------------------------------------------+\n");
    printf("|             USCI_SPI Master Mode Sample Code           |\n");
    printf("+--------------------------------------------------------+\n");
    printf("\n");
    printf("Configure USCI_SPI1 as a master.\n");
    printf("Bit length of a transaction: 16\n");
    printf("The I/O connection for USCI_SPI1:\n");
    printf("    USCI_SPI1_SS (PB.5)\n    USCI_SPI1_CLK (PB.1)\n");
    printf("    USCI_SPI1_MISO (PB.3)\n    USCI_SPI1_MOSI (PB.2)\n\n");
    printf("USCI_SPI controller will transfer %d data to a off-chip slave device.\n", TEST_COUNT);
    printf("In the meanwhile the USCI_SPI controller will receive %d data from the off-chip slave device.\n", TEST_COUNT);
    printf("After the transfer is done, the %d received data will be printed out.\n", TEST_COUNT);
    printf("The USCI_SPI master configuration is ready.\n");

    for(u32DataCount = 0; u32DataCount < TEST_COUNT; u32DataCount++)
    {
        /* Write the initial value to source buffer */
        g_au32SourceData[u32DataCount] = 0x5500 + u32DataCount;
        /* Clear destination buffer */
        g_au32DestinationData[u32DataCount] = 0;
    }

    printf("Before starting the data transfer, make sure the slave device is ready. Press any key to start the transfer.");
    getchar();
    printf("\n");

    /* Enable TX end interrupt */
    USPI_EnableInt(USPI1, USPI_TXEND_INT_MASK);
    g_u32TxDataCount = 0;
    g_u32RxDataCount = 0;
    NVIC_EnableIRQ(USCI1_IRQn);

    /* Write to TX Buffer */
    USPI_WRITE_TX(USPI1, g_au32SourceData[g_u32TxDataCount++]);

    /* Wait for transfer done */
    while(g_u32RxDataCount < TEST_COUNT);

    /* Print the received data */
    printf("Received data:\n");
    for(u32DataCount = 0; u32DataCount < TEST_COUNT; u32DataCount++)
    {
        printf("%d:\t0x%X\n", u32DataCount, g_au32DestinationData[u32DataCount]);
    }
    /* Disable TX end interrupt */
    USPI_DisableInt(USPI1, USPI_TXEND_INT_MASK);
    NVIC_DisableIRQ(USCI1_IRQn);
    printf("The data transfer was done.\n");

    printf("\n\nExit USCI_SPI driver sample code.\n");

    /* Close USCI_SPI1 */
    USPI_Close(USPI1);
    while(1);
}

void SYS_Init(void)
{
    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for HXT clock ready */
    while(!(CLK->STATUS & CLK_STATUS_HXTSTB_Msk));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);

    /* Set PCLK0/PCLK1 to HCLK/2 */
    CLK->PCLKDIV = (CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2);

    /* Enable peripheral clock */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(USCI1_MODULE);

    /* Peripheral clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CyclesPerUs automatically. */
    SystemCoreClockUpdate();


    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set USCI1_SPI multi-function pins */
    SYS->GPB_MFPL = SYS->GPB_MFPL & ~(SYS_GPB_MFPL_PB1MFP_Msk|SYS_GPB_MFPL_PB2MFP_Msk|SYS_GPB_MFPL_PB3MFP_Msk|SYS_GPB_MFPL_PB5MFP_Msk);
    SYS->GPB_MFPL = SYS->GPB_MFPL | (SYS_GPB_MFPL_PB1MFP_USCI1_CLK | SYS_GPB_MFPL_PB2MFP_USCI1_DAT0 | SYS_GPB_MFPL_PB3MFP_USCI1_DAT1 | SYS_GPB_MFPL_PB5MFP_USCI1_CTL0);

    /* USCI_SPI clock pin enable schmitt trigger */
    PB->SMTEN |= GPIO_SMTEN_SMTEN1_Msk;
}

void USCI_SPI_Init(void)
{
    /* Configure USCI_SPI1 as a master, USCI_SPI1 clock rate 2 MHz,
       clock idle low, 16-bit transaction, drive output on falling clock edge and latch input on rising edge. */
    USPI_Open(USPI1, USPI_MASTER, USPI_MODE_0, 16, 2000000);
    /* Enable the automatic hardware slave selection function and configure USCI_SPI_SS pin as low-active. */
    USPI_EnableAutoSS(USPI1, 0, USPI_SS_ACTIVE_LOW);
}

void USCI1_IRQHandler(void)
{
    uint32_t u32RxData;

    /* Clear TX end interrupt flag */
    USPI_CLR_PROT_INT_FLAG(USPI1, USPI_PROTSTS_TXENDIF_Msk);

    /* Waiting for RX is not empty */
    while(USPI_GET_RX_EMPTY_FLAG(USPI1) == 1);

    /* Check RX EMPTY flag */
    while(USPI_GET_RX_EMPTY_FLAG(USPI1) == 0)
    {
        /* Read RX Buffer */
        u32RxData = USPI_READ_RX(USPI1);
        g_au32DestinationData[g_u32RxDataCount++] = u32RxData;
    }
    /* Check TX data count */
    if(g_u32TxDataCount < TEST_COUNT)
    {
        /* Write to TX Buffer */
        USPI_WRITE_TX(USPI1, g_au32SourceData[g_u32TxDataCount++]);
    }
}


/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
