/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Implement CRC in CRC-32 mode with PDMA transfer.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK           192000000


void SYS_Init(void)
{
    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL and SysTick source to HCLK/2*/
    CLK_SetCoreClock(PLL_CLOCK);
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable peripheral clock */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(CRC_MODULE);

    /* Peripheral clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));


    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

}

void UART0_Init(void)
{
    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0, 115200);
}

uint32_t GetFMCChecksum(uint32_t u32Address, uint32_t u32Size)
{
    uint32_t u32CHKS;

    FMC_ENABLE_ISP();
    u32CHKS = FMC_GetChkSum(u32Address, u32Size);

    return u32CHKS;
}

typedef struct dma_desc_t
{
    uint32_t ctl;
    uint32_t src;
    uint32_t dest;
    uint32_t offset;
} DMA_DESC_T;
DMA_DESC_T DMA_DESC[1];

uint32_t GetPDMAChecksum(uint32_t u32Address, uint32_t u32Size)
{
    volatile uint32_t loop = 0;

    /* Enable PDMA module clock */
    CLK->AHBCLK |= CLK_AHBCLK_PDMACKEN_Msk;

    /* Give valid source address and transfer count and program PDMA memory to memory, dest => CRC_WDATA */
    PDMA->CHCTL = (1<<0); // use PDMA CH0
    DMA_DESC[0].ctl =
        (1<<PDMA_DSCT_CTL_OPMODE_Pos)  | (0<<PDMA_DSCT_CTL_TXTYPE_Pos) |
        (7<<PDMA_DSCT_CTL_BURSIZE_Pos) |
        (0<<PDMA_DSCT_CTL_SAINC_Pos)   | (3<<PDMA_DSCT_CTL_DAINC_Pos) |
        (2<<PDMA_DSCT_CTL_TXWIDTH_Pos) | (((u32Size/4)-1)<<PDMA_DSCT_CTL_TXCNT_Pos);
    DMA_DESC[0].src = (uint32_t)u32Address;
    DMA_DESC[0].dest = (uint32_t)&(CRC->DAT);
    DMA_DESC[0].offset = 0;

    PDMA->DSCT[0].CTL = PDMA_OP_SCATTER;
    PDMA->DSCT[0].NEXT = (uint32_t)&DMA_DESC[0] - (PDMA->SCATBA);

    PDMA->INTSTS = PDMA->INTSTS;
    PDMA->INTEN = (1<<0);

    /* Trigger PDMA CH0 transfer ... */
    PDMA->SWREQ = (1<<0);

    while(PDMA->TRGSTS & 0x1)   // wait PDMA finish
    {
        if(loop++ > (SystemCoreClock/100))
        {
            printf("\n[PDMA transfer time-out]\n");
            while(1);
        }
    }

    return CRC->CHECKSUM;
}


int main(void)
{
    volatile uint32_t addr, size, u32FMCChecksum, u32CRC32Checksum, u32PDMAChecksum;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Init UART0 for printf */
    UART0_Init();

    size = 1024 *2;

    printf("\n\nCPU @ %d Hz\n", SystemCoreClock);
    printf("+-----------------------------------------------------+\n");
    printf("|    CRC32 with PDMA Sample Code                      |\n");
    printf("|       - Get APROM first %d bytes CRC result by    |\n", size);
    printf("|          a.) FMC checksum command                   |\n");
    printf("|          b.) CPU write CRC data register directly   |\n");
    printf("|          c.) PDMA write CRC data register           |\n");
    printf("+-----------------------------------------------------+\n\n");


    /* Disable CRC function */
    CRC->CTL = 0;

    CRC->CTL = CRC_CTL_CRCEN_Msk;
    CRC->CTL |= CRC_32;
    CRC->CTL |= CRC_CPU_WDATA_32 | CRC_WDATA_RVS | CRC_CHECKSUM_RVS | CRC_CHECKSUM_COM;

    /*  Case a. */
    u32FMCChecksum = GetFMCChecksum(0x0, size);

    /*  Case b. */
    /* Configure CRC controller for CRC-CRC32 mode */
    CRC_Open(CRC_32, (CRC_WDATA_RVS | CRC_CHECKSUM_RVS | CRC_CHECKSUM_COM), 0xFFFFFFFF, CRC_CPU_WDATA_32);
    /* Start to execute CRC-CRC32 operation */
    for(addr=0; addr<size; addr+=4)
    {
        CRC_WRITE_DATA(inpw(addr));
    }
    u32CRC32Checksum = CRC_GetChecksum();

    /*  Case c. */
    /* Configure CRC controller for CRC-CRC32 mode */
    CRC_Open(CRC_32, (CRC_WDATA_RVS | CRC_CHECKSUM_RVS | CRC_CHECKSUM_COM), 0xFFFFFFFF, CRC_CPU_WDATA_32);
    u32PDMAChecksum = GetPDMAChecksum(0x0, size);

    printf("APROM first %d bytes checksum:\n", size);
    printf("   - by FMC command: 0x%08X\n", u32FMCChecksum);
    printf("   - by CPU write:   0x%08X\n", u32CRC32Checksum);
    printf("   - by PDMA write:  0x%08X\n", u32PDMAChecksum);

    if((u32FMCChecksum == u32CRC32Checksum) && (u32CRC32Checksum == u32PDMAChecksum))
    {
        if((u32FMCChecksum == 0) || (u32FMCChecksum == 0xFFFFFFFF))
        {
            printf("\n[Get checksum ... WRONG]");
        }
        else
        {
            printf("\n[Compare checksum ... PASS]");
        }
    }
    else
    {
        printf("\n[Compare checksum ... WRONG]");
    }

    /* Disable CRC function */
    CRC->CTL &= ~CRC_CTL_CRCEN_Msk;

    while(1);
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
