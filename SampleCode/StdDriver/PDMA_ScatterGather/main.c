/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief
 *           Use PDMA channel 5 to transfer data from memory to memory by scatter-gather mode.
 *
 *
 * @copyright (C) 2014~2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK           192000000

uint32_t PDMA_TEST_LENGTH = 64;
#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t au8SrcArray[256];
uint8_t au8DestArray0[256];
uint8_t au8DestArray1[256];
#else
__attribute__((aligned(4))) uint8_t au8SrcArray[256];
__attribute__((aligned(4))) uint8_t au8DestArray0[256];
__attribute__((aligned(4))) uint8_t au8DestArray1[256];
#endif

typedef struct dma_desc_t
{
    uint32_t ctl;
    uint32_t src;
    uint32_t dest;
    uint32_t offset;
} DMA_DESC_T;

DMA_DESC_T DMA_DESC[2];

/**
 * @brief       DMA IRQ
 *
 * @param       None
 *
 * @return      None
 *
 * @details     The DMA default IRQ, declared in startup_M480.s.
 */
void PDMA_IRQHandler(void)
{
}

void SYS_Init(void)
{
    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT clock (external XTAL 12MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);

    /* Set PCLK0/PCLK1 to HCLK/2 */
    CLK->PCLKDIV = (CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2);

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(PDMA_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);
}

void UART0_Init(void)
{
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

int main(void)
{
    uint32_t u32Src, u32Dst0, u32Dst1;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    /* If user want to write protected register, please issue SYS_UnlockReg() to unlock protected register. */
    SYS_LockReg();

    /* Init UART for printf */
    UART0_Init();

    printf("\n\nCPU @ %dHz\n", SystemCoreClock);
    printf("+-----------------------------------------------------------------------+ \n");
    printf("|    M480 PDMA Memory to Memory Driver Sample Code (Scatter-gather)     | \n");
    printf("+-----------------------------------------------------------------------+ \n");

    u32Src = (uint32_t)au8SrcArray;
    u32Dst0 = (uint32_t)au8DestArray0;
    u32Dst1 = (uint32_t)au8DestArray1;

    /* This sample will transfer data by finished two descriptor table in sequence.(descriptor table 1 -> descriptor table 2) */

    /*----------------------------------------------------------------------------------
      PDMA transfer configuration:

        Channel = 4
        Operation mode = scatter-gather mode
        First scatter-gather descriptor table = DMA_DESC[0]
        Request source = PDMA_MEM(memory to memory)

        Transmission flow:
           ------------------------      -----------------------
          |                        |    |                       |
          |  DMA_DESC[0]           | -> |  DMA_DESC[1]          | -> transfer done
          |  (Descriptor table 1)  |    |  (Descriptor table 2) |
          |                        |    |                       |
           ------------------------      -----------------------

    ----------------------------------------------------------------------------------*/

    /* Open Channel 4 */
    PDMA_Open(PDMA,1 << 4);
    /* Enable Scatter Gather mode, assign the first scatter-gather descriptor table is table 1,
       and set transfer mode as memory to memory */
    PDMA_SetTransferMode(PDMA,4, PDMA_MEM, 1, (uint32_t)&DMA_DESC[0]);

    /*------------------------------------------------------------------------------------------------------

                         au8SrcArray                         au8DestArray0
                         ---------------------------   -->   ---------------------------
                       /| [0]  | [1]  |  [2] |  [3] |       | [0]  | [1]  |  [2] |  [3] |\
                        |      |      |      |      |       |      |      |      |      |
       PDMA_TEST_LENGTH |            ...            |       |            ...            | PDMA_TEST_LENGTH
                        |      |      |      |      |       |      |      |      |      |
                       \| [60] | [61] | [62] | [63] |       | [60] | [61] | [62] | [63] |/
                         ---------------------------         ---------------------------
                         \                         /         \                         /
                               32bits(one word)                     32bits(one word)

      Descriptor table 1 configuration:

        Operation mode = scatter-gather mode
        Next descriptor table = DMA_DESC[1](Descriptor table 2)
        transfer done and table empty interrupt = disable

        Transfer count = PDMA_TEST_LENGTH
        Transfer width = 32 bits(one word)
        Source address = au8SrcArray
        Source address increment size = 32 bits(one word)
        Destination address = au8DestArray0
        Destination address increment size = 32 bits(one word)
        Transfer type = burst transfer

        Total transfer length = PDMA_TEST_LENGTH * 32 bits
    ------------------------------------------------------------------------------------------------------*/
    DMA_DESC[0].ctl =
        ((PDMA_TEST_LENGTH - 1) << PDMA_DSCT_CTL_TXCNT_Pos) | /* Transfer count is PDMA_TEST_LENGTH */ \
        PDMA_WIDTH_32 |   /* Transfer width is 32 bits(one word) */ \
        PDMA_SAR_INC |    /* Source increment size is 32 bits(one word) */ \
        PDMA_DAR_INC |    /* Destination increment size is 32 bits(one word) */ \
        PDMA_REQ_BURST |  /* Transfer type is burst transfer type */ \
        PDMA_BURST_128 |  /* Burst size is 128. No effect in single transfer type */ \
        PDMA_TBINTDIS_DISABLE |   /* Disable transfer done and table empty interrupt */ \
        PDMA_OP_SCATTER;  /* Operation mode is scatter-gather mode */

    /* Configure source address */
    DMA_DESC[0].src = u32Src;
    /* Configure destination address */
    DMA_DESC[0].dest = u32Dst0;
    /* Configure next descriptor table address */
    DMA_DESC[0].offset = (uint32_t)&DMA_DESC[1] - (PDMA->SCATBA); /* next descriptor table is table 2 */


    /*------------------------------------------------------------------------------------------------------

                         au8DestArray0                       au8DestArray1
                         ---------------------------   -->   ---------------------------
                       /| [0]  | [1]  |  [2] |  [3] |       | [0]  | [1]  |  [2] |  [3] |\
                        |      |      |      |      |       |      |      |      |      |
       PDMA_TEST_LENGTH |            ...            |       |            ...            | PDMA_TEST_LENGTH
                        |      |      |      |      |       |      |      |      |      |
                       \| [60] | [61] | [62] | [63] |       | [60] | [61] | [62] | [63] |/
                         ---------------------------         ---------------------------
                         \                         /         \                         /
                               32bits(one word)                     32bits(one word)

      Descriptor table 2 configuration:

        Operation mode = basic mode
        transfer done and table empty interrupt = enable

        Transfer count = PDMA_TEST_LENGTH
        Transfer width = 32 bits(one word)
        Source address = au8DestArray0
        Source address increment size = 32 bits(one word)
        Destination address = au8DestArray1
        Destination address increment size = 32 bits(one word)
        Transfer type = burst transfer

        Total transfer length = PDMA_TEST_LENGTH * 32 bits
    ------------------------------------------------------------------------------------------------------*/
    DMA_DESC[1].ctl =
        ((PDMA_TEST_LENGTH - 1) << PDMA_DSCT_CTL_TXCNT_Pos) | /* Transfer count is PDMA_TEST_LENGTH */ \
        PDMA_WIDTH_32 |   /* Transfer width is 32 bits(one word) */ \
        PDMA_SAR_INC |    /* Source increment size is 32 bits(one word) */ \
        PDMA_DAR_INC |    /* Destination increment size is 32 bits(one word) */ \
        PDMA_REQ_BURST |  /* Transfer type is burst transfer type */ \
        PDMA_BURST_128 |  /* Burst size is 128. No effect in single transfer type */ \
        PDMA_OP_BASIC;    /* Operation mode is basic mode */

    DMA_DESC[1].src = u32Dst0;
    DMA_DESC[1].dest = u32Dst1;
    DMA_DESC[1].offset = 0; /* No next operation table. No effect in basic mode */


    /* Generate a software request to trigger transfer with PDMA channel 4 */
    PDMA_Trigger(PDMA,4);

    /* Waiting for transfer done */
    while(PDMA_IS_CH_BUSY(PDMA,4));

    printf("test done...\n");

    /* Close Channel 4 */
    PDMA_Close(PDMA);

    while(1);
}

