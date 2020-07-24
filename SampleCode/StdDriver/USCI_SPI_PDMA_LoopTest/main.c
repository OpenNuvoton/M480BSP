/**************************************************************************//**
 * @file     main.c
 * @version  V0.10
 * @brief
 *           Demonstrate USCI_SPI data transfer with PDMA.
 *           USCI_SPI0 will be configured as Master mode and USCI_SPI1 will be configured as Slave mode.
 *           Both TX PDMA function and RX PDMA function will be enabled.
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define USPI_MASTER_TX_DMA_CH 0
#define USPI_MASTER_RX_DMA_CH 1
#define USPI_SLAVE_TX_DMA_CH  2
#define USPI_SLAVE_RX_DMA_CH  3

#define TEST_COUNT 64
#define PLL_CLOCK   192000000

/* Function prototype declaration */
void SYS_Init(void);
void USCI_SPI_Init(void);
void SpiLoopTest_WithPDMA(void);

/* Global variable declaration */
uint16_t g_au16MasterToSlaveTestPattern[TEST_COUNT];
uint16_t g_au16SlaveToMasterTestPattern[TEST_COUNT];
uint16_t g_au16MasterRxBuffer[TEST_COUNT];
uint16_t g_au16SlaveRxBuffer[TEST_COUNT];

int main(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();
    /* Init System, IP clock and multi-function I/O. */
    SYS_Init();
    /* Lock protected registers */
    SYS_LockReg();

    /* Configure UART0: 115200, 8-bit word, no parity bit, 1 stop bit. */
    UART_Open(UART0, 115200);

    /* Init USCI_SPI */
    USCI_SPI_Init();

    printf("\n\n");
    printf("+--------------------------------------------------------------+\n");
    printf("|                  USCI_SPI + PDMA Sample Code                 |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("\n");
    printf("Configure USCI_SPI0 as a master and USCI_SPI1 as a slave.\n");
    printf("Bit length of a transaction: 32\n");
    printf("The I/O connection for USCI_SPI0/USCI_SPI1 loopback:\n");
    printf("    USCI_SPI0_SS(PD4)   <--> USCI_SPI1_SS(PB5)\n    USCI_SPI0_CLK(PD0)  <--> USCI_SPI1_CLK(PB1)\n");
    printf("    USCI_SPI0_MISO(PA9) <--> USCI_SPI1_MISO(PB3)\n    USCI_SPI0_MOSI(PD1) <--> USCI_SPI1_MOSI(PB2)\n\n");
    printf("Please connect USCI_SPI0 with USCI_SPI1, and press any key to start transmission ...");
    getchar();
    printf("\n");

    SpiLoopTest_WithPDMA();

    printf("\n\nExit USCI_SPI driver sample code.\n");

    /* Close USCI_SPI0 */
    USPI_Close(USPI0);
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

    /* Enable UART peripheral clock */
    CLK_EnableModuleClock(UART0_MODULE);
    /* Enable USCI_SPI0 peripheral clock */
    CLK_EnableModuleClock(USCI0_MODULE);
    /* Enable USCI_SPI1 peripheral clock */
    CLK_EnableModuleClock(USCI1_MODULE);

    /* Enable PDMA clock source */
    CLK_EnableModuleClock(PDMA_MODULE);

    /* Peripheral clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock and CyclesPerUs automatically. */
    SystemCoreClockUpdate();


    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set USCI_SPI0 multi-function pins */
    SYS->GPA_MFPH = (SYS->GPA_MFPH & ~SYS_GPA_MFPH_PA9MFP_Msk )| SYS_GPA_MFPH_PA9MFP_USCI0_DAT1;
    SYS->GPD_MFPL &= (~(SYS_GPD_MFPL_PD1MFP_Msk | SYS_GPD_MFPL_PD4MFP_Msk | SYS_GPD_MFPL_PD0MFP_Msk));
    SYS->GPD_MFPL |= ( SYS_GPD_MFPL_PD1MFP_USCI0_DAT0 | SYS_GPD_MFPL_PD4MFP_USCI0_CTL0 | SYS_GPD_MFPL_PD0MFP_USCI0_CLK);

    /* Set USCI1_SPI multi-function pins */
    SYS->GPB_MFPL = SYS->GPB_MFPL & ~(SYS_GPB_MFPL_PB1MFP_Msk|SYS_GPB_MFPL_PB2MFP_Msk|SYS_GPB_MFPL_PB3MFP_Msk|SYS_GPB_MFPL_PB5MFP_Msk);
    SYS->GPB_MFPL = SYS->GPB_MFPL | (SYS_GPB_MFPL_PB1MFP_USCI1_CLK | SYS_GPB_MFPL_PB2MFP_USCI1_DAT0 | SYS_GPB_MFPL_PB3MFP_USCI1_DAT1 | SYS_GPB_MFPL_PB5MFP_USCI1_CTL0);

    /* USCI_SPI clock pin enable schmitt trigger */
    PB->SMTEN |= GPIO_SMTEN_SMTEN1_Msk;

}


void USCI_SPI_Init(void)
{

    /* Configure USCI_SPI0 */
    /* Configure USCI_SPI0 as a master, USCI_SPI clock rate 2MHz,
       clock idle low, 32-bit transaction, drive output on falling clock edge and latch input on rising edge. */
    USPI_Open(USPI0, USPI_MASTER, USPI_MODE_0, 16, 2000000);
    /* Enable the automatic hardware slave selection function. Select the USCI_SPI0_SS pin and configure as low-active. */
    USPI_EnableAutoSS(USPI0, USPI_SS, USPI_SS_ACTIVE_LOW);

    /* Configure USCI_SPI1 */
    /* Configure USCI_SPI1 as a slave, clock idle low, 32-bit transaction, drive output on falling clock edge and latch input on rising edge. */
    /* Configure USCI_SPI1 as a low level active device. USCI_SPI peripheral clock rate = f_PCLK0 */
    USPI_Open(USPI1, USPI_SLAVE, USPI_MODE_0, 16, 0);

}

void SpiLoopTest_WithPDMA(void)
{
    uint32_t u32DataCount, u32TestCycle;
    uint32_t u32RegValue, u32Abort;
    int32_t i32Err;

    USPI_T *UspiMaster = USPI0;
    USPI_T *UspiSlave  = USPI1;


    printf("\nUSCI_SPI0/1 Loop test with PDMA ");

    /* Source data initiation */
    for(u32DataCount = 0; u32DataCount < TEST_COUNT; u32DataCount++)
    {
        g_au16MasterToSlaveTestPattern[u32DataCount] = 0x5500 | (u32DataCount + 1);
        g_au16SlaveToMasterTestPattern[u32DataCount] = 0xAA00 | (u32DataCount + 1);
    }


    /* Enable PDMA channels */
    PDMA_Open(PDMA,(1 << USPI_MASTER_TX_DMA_CH) | (1 << USPI_MASTER_RX_DMA_CH) | (1 << USPI_SLAVE_RX_DMA_CH) | (1 << USPI_SLAVE_TX_DMA_CH));


    /*=======================================================================
      USCI_SPI master PDMA TX channel configuration:
      -----------------------------------------------------------------------
        Word length = 16 bits
        Transfer Count = TEST_COUNT
        Source = g_au16MasterToSlaveTestPattern
        Source Address = Increasing
        Destination = USCI_SPI0->TX
        Destination Address = Fixed
        Burst Type = Single Transfer
    =========================================================================*/
    /* Set transfer width (16 bits) and transfer count */
    PDMA_SetTransferCnt(PDMA,USPI_MASTER_TX_DMA_CH, PDMA_WIDTH_16, TEST_COUNT);
    /* Set source/destination address and attributes */
    PDMA_SetTransferAddr(PDMA,USPI_MASTER_TX_DMA_CH, (uint32_t)g_au16MasterToSlaveTestPattern, PDMA_SAR_INC, (uint32_t)&UspiMaster->TXDAT, PDMA_DAR_FIX);
    /* Set request source; set basic mode. */
    PDMA_SetTransferMode(PDMA,USPI_MASTER_TX_DMA_CH, PDMA_USCI0_TX, FALSE, 0);
    /* Single request type. USCI_SPI only support PDMA single request type. */
    PDMA_SetBurstType(PDMA,USPI_MASTER_TX_DMA_CH, PDMA_REQ_SINGLE, 0);
    /* Disable table interrupt */
    PDMA->DSCT[USPI_MASTER_TX_DMA_CH].CTL |= PDMA_DSCT_CTL_TBINTDIS_Msk;

    /*=======================================================================
      USCI_SPI master PDMA RX channel configuration:
      -----------------------------------------------------------------------
        Word length = 16 bits
        Transfer Count = TEST_COUNT
        Source = USCI_SPI0->RX
        Source Address = Fixed
        Destination = g_au16MasterRxBuffer
        Destination Address = Increasing
        Burst Type = Single Transfer
    =========================================================================*/
    /* Set transfer width (16 bits) and transfer count */
    PDMA_SetTransferCnt(PDMA,USPI_MASTER_RX_DMA_CH, PDMA_WIDTH_16, TEST_COUNT);
    /* Set source/destination address and attributes */
    PDMA_SetTransferAddr(PDMA,USPI_MASTER_RX_DMA_CH, (uint32_t)&UspiMaster->RXDAT, PDMA_SAR_FIX, (uint32_t)g_au16MasterRxBuffer, PDMA_DAR_INC);
    /* Set request source; set basic mode. */
    PDMA_SetTransferMode(PDMA,USPI_MASTER_RX_DMA_CH, PDMA_USCI0_RX, FALSE, 0);
    /* Single request type. USCI_SPI only support PDMA single request type. */
    PDMA_SetBurstType(PDMA,USPI_MASTER_RX_DMA_CH, PDMA_REQ_SINGLE, 0);
    /* Disable table interrupt */
    PDMA->DSCT[USPI_MASTER_RX_DMA_CH].CTL |= PDMA_DSCT_CTL_TBINTDIS_Msk;

    /*=======================================================================
      USCI_SPI slave PDMA RX channel configuration:
      -----------------------------------------------------------------------
        Word length = 16 bits
        Transfer Count = TEST_COUNT
        Source = USCI_SPI1->RX
        Source Address = Fixed
        Destination = g_au16SlaveRxBuffer
        Destination Address = Increasing
        Burst Type = Single Transfer
    =========================================================================*/
    /* Set transfer width (16 bits) and transfer count */
    PDMA_SetTransferCnt(PDMA,USPI_SLAVE_RX_DMA_CH, PDMA_WIDTH_16, TEST_COUNT);
    /* Set source/destination address and attributes */
    PDMA_SetTransferAddr(PDMA,USPI_SLAVE_RX_DMA_CH, (uint32_t)&UspiSlave->RXDAT, PDMA_SAR_FIX, (uint32_t)g_au16SlaveRxBuffer, PDMA_DAR_INC);
    /* Set request source; set basic mode. */
    PDMA_SetTransferMode(PDMA,USPI_SLAVE_RX_DMA_CH, PDMA_USCI1_RX, FALSE, 0);
    /* Single request type. USCI_SPI only support PDMA single request type. */
    PDMA_SetBurstType(PDMA,USPI_SLAVE_RX_DMA_CH, PDMA_REQ_SINGLE, 0);
    /* Disable table interrupt */
    PDMA->DSCT[USPI_SLAVE_RX_DMA_CH].CTL |= PDMA_DSCT_CTL_TBINTDIS_Msk;

    /*=======================================================================
      USCI_SPI slave PDMA TX channel configuration:
      -----------------------------------------------------------------------
        Word length = 16 bits
        Transfer Count = TEST_COUNT
        Source = g_au16SlaveToMasterTestPattern
        Source Address = Increasing
        Destination = USCI_SPI1->TX
        Destination Address = Fixed
        Burst Type = Single Transfer
    =========================================================================*/
    /* Set transfer width (16 bits) and transfer count */
    PDMA_SetTransferCnt(PDMA,USPI_SLAVE_TX_DMA_CH, PDMA_WIDTH_16, TEST_COUNT);
    /* Set source/destination address and attributes */
    PDMA_SetTransferAddr(PDMA,USPI_SLAVE_TX_DMA_CH, (uint32_t)g_au16SlaveToMasterTestPattern, PDMA_SAR_INC, (uint32_t)&UspiSlave->TXDAT, PDMA_DAR_FIX);
    /* Set request source; set basic mode. */
    PDMA_SetTransferMode(PDMA,USPI_SLAVE_TX_DMA_CH, PDMA_USCI1_TX, FALSE, 0);
    /* Single request type. USCI_SPI only support PDMA single request type. */
    PDMA_SetBurstType(PDMA,USPI_SLAVE_TX_DMA_CH, PDMA_REQ_SINGLE, 0);
    /* Disable table interrupt */
    PDMA->DSCT[USPI_SLAVE_TX_DMA_CH].CTL |= PDMA_DSCT_CTL_TBINTDIS_Msk;

    /* Enable USCI_SPI slave DMA function */
    USPI_TRIGGER_TX_RX_PDMA(UspiSlave);

    /* Enable USCI_SPI master DMA function */
    USPI_TRIGGER_TX_RX_PDMA(UspiMaster);

    i32Err = 0;
    for(u32TestCycle = 0; u32TestCycle < 10000; u32TestCycle++)
    {
        if((u32TestCycle & 0x1FF) == 0)
            putchar('.');

        while(1)
        {
            /* Get interrupt status */
            u32RegValue = PDMA_GET_INT_STATUS(PDMA);
            /* Check the PDMA transfer done interrupt flag */
            if(u32RegValue & PDMA_INTSTS_TDIF_Msk)
            {
                /* Check the PDMA transfer done flags */
                if((PDMA_GET_TD_STS(PDMA) & ((1 << USPI_MASTER_TX_DMA_CH) | (1 << USPI_MASTER_RX_DMA_CH) | (1 << USPI_SLAVE_TX_DMA_CH) | (1 << USPI_SLAVE_RX_DMA_CH))) ==
                        ((1 << USPI_MASTER_TX_DMA_CH) | (1 << USPI_MASTER_RX_DMA_CH) | (1 << USPI_SLAVE_TX_DMA_CH) | (1 << USPI_SLAVE_RX_DMA_CH)))
                {
                    /* Clear the PDMA transfer done flags */
                    PDMA_CLR_TD_FLAG(PDMA,(1 << USPI_MASTER_TX_DMA_CH) | (1 << USPI_MASTER_RX_DMA_CH) | (1 << USPI_SLAVE_TX_DMA_CH) | (1 << USPI_SLAVE_RX_DMA_CH));
                    /* Disable USCI_SPI master's PDMA transfer function */
                    USPI_DISABLE_TX_RX_PDMA(UspiMaster);
                    /* Check the transfer data */
                    for(u32DataCount = 0; u32DataCount < TEST_COUNT; u32DataCount++)
                    {
                        if(g_au16MasterToSlaveTestPattern[u32DataCount] != g_au16SlaveRxBuffer[u32DataCount])
                        {
                            i32Err = 1;
                            break;
                        }
                        if(g_au16SlaveToMasterTestPattern[u32DataCount] != g_au16MasterRxBuffer[u32DataCount])
                        {
                            i32Err = 1;
                            break;
                        }
                    }

                    if(u32TestCycle >= 10000)
                        break;

                    /* Source data initiation */
                    for(u32DataCount = 0; u32DataCount < TEST_COUNT; u32DataCount++)
                    {
                        g_au16MasterToSlaveTestPattern[u32DataCount]++;
                        g_au16SlaveToMasterTestPattern[u32DataCount]++;
                    }
                    /* Re-trigger */
                    /* Slave PDMA TX channel configuration */
                    /* Set transfer width (16 bits) and transfer count */
                    PDMA_SetTransferCnt(PDMA,USPI_SLAVE_TX_DMA_CH, PDMA_WIDTH_16, TEST_COUNT);
                    /* Set request source; set basic mode. */
                    PDMA_SetTransferMode(PDMA,USPI_SLAVE_TX_DMA_CH, PDMA_USCI1_TX, FALSE, 0);

                    /* Slave PDMA RX channel configuration */
                    /* Set transfer width (16 bits) and transfer count */
                    PDMA_SetTransferCnt(PDMA,USPI_SLAVE_RX_DMA_CH, PDMA_WIDTH_16, TEST_COUNT);
                    /* Set request source; set basic mode. */
                    PDMA_SetTransferMode(PDMA,USPI_SLAVE_RX_DMA_CH, PDMA_USCI1_RX, FALSE, 0);

                    /* Master PDMA TX channel configuration */
                    /* Set transfer width (16 bits) and transfer count */
                    PDMA_SetTransferCnt(PDMA,USPI_MASTER_TX_DMA_CH, PDMA_WIDTH_16, TEST_COUNT);
                    /* Set request source; set basic mode. */
                    PDMA_SetTransferMode(PDMA,USPI_MASTER_TX_DMA_CH, PDMA_USCI0_TX, FALSE, 0);

                    /* Master PDMA RX channel configuration */
                    /* Set transfer width (16 bits) and transfer count */
                    PDMA_SetTransferCnt(PDMA,USPI_MASTER_RX_DMA_CH, PDMA_WIDTH_16, TEST_COUNT);
                    /* Set request source; set basic mode. */
                    PDMA_SetTransferMode(PDMA,USPI_MASTER_RX_DMA_CH, PDMA_USCI0_RX, FALSE, 0);

                    /* Enable master's DMA transfer function */
                    USPI_TRIGGER_TX_RX_PDMA(UspiMaster);
                    break;
                }
            }
            /* Check the DMA transfer abort interrupt flag */
            if(u32RegValue & PDMA_INTSTS_ABTIF_Msk)
            {
                /* Get the target abort flag */
                u32Abort = PDMA_GET_ABORT_STS(PDMA);
                /* Clear the target abort flag */
                PDMA_CLR_ABORT_FLAG(PDMA,u32Abort);
                i32Err = 1;
                break;
            }
            /* Check the DMA time-out interrupt flag */
            if(u32RegValue & (PDMA_INTSTS_REQTOF0_Msk|PDMA_INTSTS_REQTOF1_Msk))
            {
                /* Clear the time-out flag */
                PDMA->INTSTS = u32RegValue & (PDMA_INTSTS_REQTOF0_Msk|PDMA_INTSTS_REQTOF1_Msk);
                i32Err = 1;
                break;
            }
        }

        if(i32Err)
            break;
    }

    /* Disable all PDMA channels */
    PDMA_Close(PDMA);

    if(i32Err)
    {
        printf(" [FAIL]\n");
    }
    else
    {
        printf(" [PASS]\n");
    }

    return;
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
