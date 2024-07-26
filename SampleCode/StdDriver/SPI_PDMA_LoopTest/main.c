/**************************************************************************//**
 * @file     main.c
 * @version  V0.10
 * @brief
 *           Demonstrate SPI data transfer with PDMA.
 *           QSPI0 will be configured as Master mode and SPI1 will be configured as Slave mode.
 *           Both TX PDMA function and RX PDMA function will be enabled.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK           192000000
#define SPI_MASTER_TX_DMA_CH 0
#define SPI_MASTER_RX_DMA_CH 1
#define SPI_SLAVE_TX_DMA_CH  2
#define SPI_SLAVE_RX_DMA_CH  3

#define TEST_COUNT 64

/* Function prototype declaration */
void SYS_Init(void);
void SPI_Init(void);
void SpiLoopTest_WithPDMA(void);

/* Global variable declaration */
uint32_t g_au32MasterToSlaveTestPattern[TEST_COUNT];
uint32_t g_au32SlaveToMasterTestPattern[TEST_COUNT];
uint32_t g_au32MasterRxBuffer[TEST_COUNT];
uint32_t g_au32SlaveRxBuffer[TEST_COUNT];

void SYS_Init(void)
{
    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT clock (external XTAL 12MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Select PCLK as the clock source of QSPI0 and SPI1 */
    CLK_SetModuleClock(QSPI0_MODULE, CLK_CLKSEL2_QSPI0SEL_PCLK0, MODULE_NoMsk);
    CLK_SetModuleClock(SPI1_MODULE, CLK_CLKSEL2_SPI1SEL_PCLK0, MODULE_NoMsk);

    /* Enable UART peripheral clock */
    CLK_EnableModuleClock(UART0_MODULE);
    /* Enable QSPI0 peripheral clock */
    CLK_EnableModuleClock(QSPI0_MODULE);
    /* Enable SPI1 peripheral clock */
    CLK_EnableModuleClock(SPI1_MODULE);

    /* Enable PDMA clock source */
    CLK_EnableModuleClock(PDMA_MODULE);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock and CyclesPerUs automatically. */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Configure QSPI0 related multi-function pins. GPA[3:0] : QSPI0_MOSI0, QSPI0_MISO0, QSPI0_CLK, QSPI0_SS. */
    SYS->GPA_MFPL |= SYS_GPA_MFPL_PA0MFP_QSPI0_MOSI0 | SYS_GPA_MFPL_PA1MFP_QSPI0_MISO0 | SYS_GPA_MFPL_PA2MFP_QSPI0_CLK | SYS_GPA_MFPL_PA3MFP_QSPI0_SS;

    /* Enable QSPI0 clock pin (PA2) schmitt trigger */
    PA->SMTEN |= GPIO_SMTEN_SMTEN2_Msk;

    /* Enable QSPI0 I/O high slew rate */
    GPIO_SetSlewCtl(PA, 0x3F, GPIO_SLEWCTL_HIGH);

    /* Configure SPI1 related multi-function pins. GPH[7:4] : SPI1_MISO, SPI1_MOSI, SPI1_CLK, SPI1_SS. */
    SYS->GPH_MFPL &= ~(SYS_GPH_MFPL_PH4MFP_Msk | SYS_GPH_MFPL_PH5MFP_Msk | SYS_GPH_MFPL_PH6MFP_Msk | SYS_GPH_MFPL_PH7MFP_Msk);
    SYS->GPH_MFPL |= (SYS_GPH_MFPL_PH4MFP_SPI1_MISO | SYS_GPH_MFPL_PH5MFP_SPI1_MOSI | SYS_GPH_MFPL_PH6MFP_SPI1_CLK | SYS_GPH_MFPL_PH7MFP_SPI1_SS);
}

void SPI_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init SPI                                                                                                */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Configure QSPI0 */
    /* Configure QSPI0 as a master, SPI clock rate 2MHz,
       clock idle low, 32-bit transaction, drive output on falling clock edge and latch input on rising edge. */
    QSPI_Open(QSPI0, SPI_MASTER, SPI_MODE_0, 32, 2000000);
    /* Enable the automatic hardware slave selection function. Select the QSPI0_SS pin and configure as low-active. */
    QSPI_EnableAutoSS(QSPI0, SPI_SS, SPI_SS_ACTIVE_LOW);

    /* Configure SPI1 */
    /* Configure SPI1 as a slave, clock idle low, 32-bit transaction, drive output on falling clock edge and latch input on rising edge. */
    /* Configure SPI1 as a low level active device. SPI peripheral clock rate = f_PCLK0 */
    SPI_Open(SPI1, SPI_SLAVE, SPI_MODE_0, 32, (uint32_t)NULL);
}

void SpiLoopTest_WithPDMA(void)
{
    uint32_t u32DataCount, u32TestCycle;
    uint32_t u32RegValue, u32Abort;
    int32_t i32Err;

    printf("\nQSPI0/2 Loop test with PDMA ");

    /* Source data initiation */
    for(u32DataCount = 0; u32DataCount < TEST_COUNT; u32DataCount++)
    {
        g_au32MasterToSlaveTestPattern[u32DataCount] = 0x55000000 | (u32DataCount + 1);
        g_au32SlaveToMasterTestPattern[u32DataCount] = 0xAA000000 | (u32DataCount + 1);
    }


    /* Enable PDMA channels */
    PDMA_Open(PDMA,(1 << SPI_MASTER_TX_DMA_CH) | (1 << SPI_MASTER_RX_DMA_CH) | (1 << SPI_SLAVE_RX_DMA_CH) | (1 << SPI_SLAVE_TX_DMA_CH));

    /*=======================================================================
      SPI master PDMA TX channel configuration:
      -----------------------------------------------------------------------
        Word length = 32 bits
        Transfer Count = TEST_COUNT
        Source = g_au32MasterToSlaveTestPattern
        Source Address = Increasing
        Destination = QSPI0->TX
        Destination Address = Fixed
        Burst Type = Single Transfer
    =========================================================================*/
    /* Set transfer width (32 bits) and transfer count */
    PDMA_SetTransferCnt(PDMA,SPI_MASTER_TX_DMA_CH, PDMA_WIDTH_32, TEST_COUNT);
    /* Set source/destination address and attributes */
    PDMA_SetTransferAddr(PDMA,SPI_MASTER_TX_DMA_CH, (uint32_t)g_au32MasterToSlaveTestPattern, PDMA_SAR_INC, (uint32_t)&QSPI0->TX, PDMA_DAR_FIX);
    /* Set request source; set basic mode. */
    PDMA_SetTransferMode(PDMA,SPI_MASTER_TX_DMA_CH, PDMA_QSPI0_TX, FALSE, 0);
    /* Single request type. SPI only support PDMA single request type. */
    PDMA_SetBurstType(PDMA,SPI_MASTER_TX_DMA_CH, PDMA_REQ_SINGLE, 0);
    /* Disable table interrupt */
    PDMA->DSCT[SPI_MASTER_TX_DMA_CH].CTL |= PDMA_DSCT_CTL_TBINTDIS_Msk;

    /*=======================================================================
      SPI master PDMA RX channel configuration:
      -----------------------------------------------------------------------
        Word length = 32 bits
        Transfer Count = TEST_COUNT
        Source = QSPI0->RX
        Source Address = Fixed
        Destination = g_au32MasterRxBuffer
        Destination Address = Increasing
        Burst Type = Single Transfer
    =========================================================================*/
    /* Set transfer width (32 bits) and transfer count */
    PDMA_SetTransferCnt(PDMA,SPI_MASTER_RX_DMA_CH, PDMA_WIDTH_32, TEST_COUNT);
    /* Set source/destination address and attributes */
    PDMA_SetTransferAddr(PDMA,SPI_MASTER_RX_DMA_CH, (uint32_t)&QSPI0->RX, PDMA_SAR_FIX, (uint32_t)g_au32MasterRxBuffer, PDMA_DAR_INC);
    /* Set request source; set basic mode. */
    PDMA_SetTransferMode(PDMA,SPI_MASTER_RX_DMA_CH, PDMA_QSPI0_RX, FALSE, 0);
    /* Single request type. SPI only support PDMA single request type. */
    PDMA_SetBurstType(PDMA,SPI_MASTER_RX_DMA_CH, PDMA_REQ_SINGLE, 0);
    /* Disable table interrupt */
    PDMA->DSCT[SPI_MASTER_RX_DMA_CH].CTL |= PDMA_DSCT_CTL_TBINTDIS_Msk;

    /*=======================================================================
      SPI slave PDMA RX channel configuration:
      -----------------------------------------------------------------------
        Word length = 32 bits
        Transfer Count = TEST_COUNT
        Source = SPI1->RX
        Source Address = Fixed
        Destination = g_au32SlaveRxBuffer
        Destination Address = Increasing
        Burst Type = Single Transfer
    =========================================================================*/
    /* Set transfer width (32 bits) and transfer count */
    PDMA_SetTransferCnt(PDMA,SPI_SLAVE_RX_DMA_CH, PDMA_WIDTH_32, TEST_COUNT);
    /* Set source/destination address and attributes */
    PDMA_SetTransferAddr(PDMA,SPI_SLAVE_RX_DMA_CH, (uint32_t)&SPI1->RX, PDMA_SAR_FIX, (uint32_t)g_au32SlaveRxBuffer, PDMA_DAR_INC);
    /* Set request source; set basic mode. */
    PDMA_SetTransferMode(PDMA,SPI_SLAVE_RX_DMA_CH, PDMA_SPI1_RX, FALSE, 0);
    /* Single request type. SPI only support PDMA single request type. */
    PDMA_SetBurstType(PDMA,SPI_SLAVE_RX_DMA_CH, PDMA_REQ_SINGLE, 0);
    /* Disable table interrupt */
    PDMA->DSCT[SPI_SLAVE_RX_DMA_CH].CTL |= PDMA_DSCT_CTL_TBINTDIS_Msk;

    /*=======================================================================
      SPI slave PDMA TX channel configuration:
      -----------------------------------------------------------------------
        Word length = 32 bits
        Transfer Count = TEST_COUNT
        Source = g_au32SlaveToMasterTestPattern
        Source Address = Increasing
        Destination = SPI1->TX
        Destination Address = Fixed
        Burst Type = Single Transfer
    =========================================================================*/
    /* Set transfer width (32 bits) and transfer count */
    PDMA_SetTransferCnt(PDMA,SPI_SLAVE_TX_DMA_CH, PDMA_WIDTH_32, TEST_COUNT);
    /* Set source/destination address and attributes */
    PDMA_SetTransferAddr(PDMA,SPI_SLAVE_TX_DMA_CH, (uint32_t)g_au32SlaveToMasterTestPattern, PDMA_SAR_INC, (uint32_t)&SPI1->TX, PDMA_DAR_FIX);
    /* Set request source; set basic mode. */
    PDMA_SetTransferMode(PDMA,SPI_SLAVE_TX_DMA_CH, PDMA_SPI1_TX, FALSE, 0);
    /* Single request type. SPI only support PDMA single request type. */
    PDMA_SetBurstType(PDMA,SPI_SLAVE_TX_DMA_CH, PDMA_REQ_SINGLE, 0);
    /* Disable table interrupt */
    PDMA->DSCT[SPI_SLAVE_TX_DMA_CH].CTL |= PDMA_DSCT_CTL_TBINTDIS_Msk;

    /* Enable SPI slave DMA function */
    SPI_TRIGGER_TX_RX_PDMA(SPI1);
    /* Enable SPI master DMA function */
    QSPI_TRIGGER_TX_RX_PDMA(QSPI0);

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
                if((PDMA_GET_TD_STS(PDMA) & ((1 << SPI_MASTER_TX_DMA_CH) | (1 << SPI_MASTER_RX_DMA_CH) | (1 << SPI_SLAVE_TX_DMA_CH) | (1 << SPI_SLAVE_RX_DMA_CH))) ==
                        ((1 << SPI_MASTER_TX_DMA_CH) | (1 << SPI_MASTER_RX_DMA_CH) | (1 << SPI_SLAVE_TX_DMA_CH) | (1 << SPI_SLAVE_RX_DMA_CH)))
                {

                    /* Clear the PDMA transfer done flags */
                    PDMA_CLR_TD_FLAG(PDMA,(1 << SPI_MASTER_TX_DMA_CH) | (1 << SPI_MASTER_RX_DMA_CH) | (1 << SPI_SLAVE_TX_DMA_CH) | (1 << SPI_SLAVE_RX_DMA_CH));

                    /* Disable QSPI master's PDMA transfer function */
                    QSPI_DISABLE_TX_RX_PDMA(QSPI0);

                    /* Check the transfer data */
                    for(u32DataCount = 0; u32DataCount < TEST_COUNT; u32DataCount++)
                    {
                        if(g_au32MasterToSlaveTestPattern[u32DataCount] != g_au32SlaveRxBuffer[u32DataCount])
                        {
                            i32Err = 1;
                            break;
                        }
                        if(g_au32SlaveToMasterTestPattern[u32DataCount] != g_au32MasterRxBuffer[u32DataCount])
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
                        g_au32MasterToSlaveTestPattern[u32DataCount]++;
                        g_au32SlaveToMasterTestPattern[u32DataCount]++;
                    }
                    /* Re-trigger */
                    /* Slave PDMA TX channel configuration */
                    /* Set transfer width (32 bits) and transfer count */
                    PDMA_SetTransferCnt(PDMA,SPI_SLAVE_TX_DMA_CH, PDMA_WIDTH_32, TEST_COUNT);
                    /* Set request source; set basic mode. */
                    PDMA_SetTransferMode(PDMA,SPI_SLAVE_TX_DMA_CH, PDMA_SPI1_TX, FALSE, 0);

                    /* Slave PDMA RX channel configuration */
                    /* Set transfer width (32 bits) and transfer count */
                    PDMA_SetTransferCnt(PDMA,SPI_SLAVE_RX_DMA_CH, PDMA_WIDTH_32, TEST_COUNT);
                    /* Set request source; set basic mode. */
                    PDMA_SetTransferMode(PDMA,SPI_SLAVE_RX_DMA_CH, PDMA_SPI1_RX, FALSE, 0);

                    /* Master PDMA TX channel configuration */
                    /* Set transfer width (32 bits) and transfer count */
                    PDMA_SetTransferCnt(PDMA,SPI_MASTER_TX_DMA_CH, PDMA_WIDTH_32, TEST_COUNT);
                    /* Set request source; set basic mode. */
                    PDMA_SetTransferMode(PDMA,SPI_MASTER_TX_DMA_CH, PDMA_QSPI0_TX, FALSE, 0);

                    /* Master PDMA RX channel configuration */
                    /* Set transfer width (32 bits) and transfer count */
                    PDMA_SetTransferCnt(PDMA,SPI_MASTER_RX_DMA_CH, PDMA_WIDTH_32, TEST_COUNT);
                    /* Set request source; set basic mode. */
                    PDMA_SetTransferMode(PDMA,SPI_MASTER_RX_DMA_CH, PDMA_QSPI0_RX, FALSE, 0);

                    /* Enable master's DMA transfer function */
                    QSPI_TRIGGER_TX_RX_PDMA(QSPI0);
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

int main(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O. */
    SYS_Init();

    /* Configure UART0: 115200, 8-bit word, no parity bit, 1 stop bit. */
    UART_Open(UART0, 115200);

    /* Init SPI */
    SPI_Init();

    printf("\n\n");
    printf("+--------------------------------------------------------------+\n");
    printf("|                  SPI + PDMA Sample Code                      |\n");
    printf("+--------------------------------------------------------------+\n");
    printf("\n");
    printf("Configure QSPI0 as a master and SPI1 as a slave.\n");
    printf("Bit length of a transaction: 32\n");
    printf("The I/O connection for QSPI0/SPI1 loopback:\n");
    printf("    QSPI0_SS  (PA3) <--> SPI1_SS(PH7)\n    QSPI0_CLK(PA2)  <--> SPI1_CLK(PH6)\n");
    printf("    QSPI0_MISO(PA1) <--> SPI1_MISO(PH4)\n    QSPI0_MOSI(PA0) <--> SPI1_MOSI(PH5)\n\n");
    printf("Please connect QSPI0 with SPI1, and press any key to start transmission ...");
    getchar();
    printf("\n");

    SpiLoopTest_WithPDMA();

    printf("\n\nExit SPI driver sample code.\n");

    /* Close QSPI0 */
    QSPI_Close(QSPI0);
    /* Close SPI1 */
    SPI_Close(SPI1);
    while(1);
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
