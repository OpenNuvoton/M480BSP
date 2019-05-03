/*************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief
 *           Implement USCI_SPI1 Master loop back transfer.
 *           This sample code needs to connect USCI_SPI1_MISO pin and USCI_SPI1_MOSI pin together.
 *           It will compare the received data with transmitted data.
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"


#define TEST_COUNT  64
#define PLL_CLOCK   192000000

uint32_t g_au32SourceData[TEST_COUNT];
uint32_t g_au32DestinationData[TEST_COUNT];

/* Function prototype declaration */
void SYS_Init(void);
void USCI_SPI_Init(void);


int main()
{
    uint32_t u32DataCount, u32TestCount, u32Err;

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
    printf("+------------------------------------------------------------------+\n");
    printf("|                   USCI_SPI Driver Sample Code                    |\n");
    printf("+------------------------------------------------------------------+\n");
    printf("\n");
    printf("\nThis sample code demonstrates USCI_SPI1 self loop back data transfer.\n");
    printf(" USCI_SPI1 configuration:\n");
    printf("     Master mode; data width 16 bits.\n");
    printf(" I/O connection:\n");
    printf("     PB.2 USCI_SPI1_MOSI <--> PB.3 USCI_SPI1_MISO \n");

    printf("\nUSCI_SPI1 Loopback test ");

    /* set the source data and clear the destination buffer */
    for(u32DataCount = 0; u32DataCount < TEST_COUNT; u32DataCount++)
    {
        g_au32SourceData[u32DataCount] = u32DataCount;
        g_au32DestinationData[u32DataCount] = 0;
    }

    u32Err = 0;
    for(u32TestCount = 0; u32TestCount < 0x1000; u32TestCount++)
    {
        /* set the source data and clear the destination buffer */
        for(u32DataCount = 0; u32DataCount < TEST_COUNT; u32DataCount++)
        {
            g_au32SourceData[u32DataCount]++;
            g_au32DestinationData[u32DataCount] = 0;
        }

        u32DataCount = 0;

        if((u32TestCount & 0x1FF) == 0)
        {
            putchar('.');
        }

        while(1)
        {
            /* Write to TX register */
            USPI_WRITE_TX(USPI1, g_au32SourceData[u32DataCount]);
            /* Check SPI1 busy status */
            while(USPI_IS_BUSY(USPI1));
            /* Read received data */
            g_au32DestinationData[u32DataCount] = USPI_READ_RX(USPI1);
            u32DataCount++;
            if(u32DataCount == TEST_COUNT)
                break;
        }

        /*  Check the received data */
        for(u32DataCount = 0; u32DataCount < TEST_COUNT; u32DataCount++)
        {
            if(g_au32DestinationData[u32DataCount] != g_au32SourceData[u32DataCount])
                u32Err = 1;
        }

        if(u32Err)
            break;
    }

    if(u32Err)
        printf(" [FAIL]\n\n");
    else
        printf(" [PASS]\n\n");

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
    /* Configure USCI_SPI1 as a master, clock idle low, 16-bit transaction, drive output on falling clock edge and latch input on rising edge. */
    /* Set USCI_SPI1 clock rate = 2MHz */
    USPI_Open(USPI1, USPI_MASTER, USPI_MODE_0, 16, 2000000);
}


/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
