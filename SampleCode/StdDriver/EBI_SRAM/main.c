/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Configure EBI interface to access BS616LV4017 (SRAM) on EBI interface.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK       192000000

extern void SRAM_BS616LV4017(uint32_t u32MaxSize);
void AccessEBIWithPDMA(void);

void Configure_EBI_16BIT_Pins(void)
{
    /* EBI AD0~5 pins on PC.0~5 */
    SYS->GPC_MFPL |= SYS_GPC_MFPL_PC0MFP_EBI_AD0 | SYS_GPC_MFPL_PC1MFP_EBI_AD1 |
                     SYS_GPC_MFPL_PC2MFP_EBI_AD2 | SYS_GPC_MFPL_PC3MFP_EBI_AD3 |
                     SYS_GPC_MFPL_PC4MFP_EBI_AD4 | SYS_GPC_MFPL_PC5MFP_EBI_AD5;

    /* EBI AD6, AD7 pins on PD.8, PD.9 */
    SYS->GPD_MFPH |= SYS_GPD_MFPH_PD8MFP_EBI_AD6 | SYS_GPD_MFPH_PD9MFP_EBI_AD7;

    /* EBI AD8, AD9 pins on PE.14, PE.15 */
    SYS->GPE_MFPH |= SYS_GPE_MFPH_PE14MFP_EBI_AD8 | SYS_GPE_MFPH_PE15MFP_EBI_AD9;

    /* EBI AD10, AD11 pins on PE.1, PE.0 */
    SYS->GPE_MFPL |= SYS_GPE_MFPL_PE1MFP_EBI_AD10 | SYS_GPE_MFPL_PE0MFP_EBI_AD11;

    /* EBI AD12~15 pins on PH.8~11 */
    SYS->GPH_MFPH |= SYS_GPH_MFPH_PH8MFP_EBI_AD12 | SYS_GPH_MFPH_PH9MFP_EBI_AD13 |
                     SYS_GPH_MFPH_PH10MFP_EBI_AD14 | SYS_GPH_MFPH_PH11MFP_EBI_AD15;

    /* EBI ADR16, ADR17 pins on PF.9, PF.8 */
    SYS->GPF_MFPH |= SYS_GPF_MFPH_PF9MFP_EBI_ADR16 | SYS_GPF_MFPH_PF8MFP_EBI_ADR17;

    /* EBI ADR18, ADR19 pins on PF.7, PF.6 */
    SYS->GPF_MFPL |= SYS_GPF_MFPL_PF7MFP_EBI_ADR18 | SYS_GPF_MFPL_PF6MFP_EBI_ADR19;


    /* EBI RD and WR pins on PE.4 and PE.5 */
    SYS->GPE_MFPL |= SYS_GPE_MFPL_PE4MFP_EBI_nWR | SYS_GPE_MFPL_PE5MFP_EBI_nRD;

    /* EBI WRL and WRH pins on PG.7 and PG.8 */
    SYS->GPG_MFPL |= SYS_GPG_MFPL_PG7MFP_EBI_nWRL;
    SYS->GPG_MFPH |= SYS_GPG_MFPH_PG8MFP_EBI_nWRH;

    /* EBI CS0 pin on PD.12 */
    SYS->GPD_MFPH |= SYS_GPD_MFPH_PD12MFP_EBI_nCS0;

    /* EBI ALE pin on PE.2 */
    SYS->GPE_MFPL |= SYS_GPE_MFPL_PE2MFP_EBI_ALE;

    /* EBI MCLK pin on PE.3 */
    SYS->GPE_MFPL |= SYS_GPE_MFPL_PE3MFP_EBI_MCLK;
}

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
    CLK_SetSysTickClockSrc(CLK_CLKSEL0_STCLKSEL_HCLK_DIV2);

    /* Set PCLK0/PCLK1 to HCLK/2 */
    CLK->PCLKDIV = (CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2);

    /* Enable peripheral clock */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(EBI_MODULE);

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

int main(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    printf("\n\nCPU @ %d Hz\n", SystemCoreClock);
    printf("+--------------------------------------------------------+\n");
    printf("|    EBI SRAM Sample Code on Bank0 with PDMA transfer    |\n");
    printf("+--------------------------------------------------------+\n\n");

    printf("********************************************************************\n");
    printf("* Please connect BS616LV4017 SRAM to EBI bank0 before accessing !! *\n");
    printf("* EBI pins settings:                                               *\n");
    printf("*   - AD0 ~ AD5   on PC.0 ~ PC.5                                   *\n");
    printf("*   - AD6 ~ AD7   on PD.8 ~ PD.9                                   *\n");
    printf("*   - AD8 ~ AD9   on PE.14 ~ PE.15                                 *\n");
    printf("*   - AD10        on PE.1                                          *\n");
    printf("*   - AD11        on PE.0                                          *\n");
    printf("*   - AD12 ~ AD15 on PH.8 ~ PH.11                                  *\n");
    printf("*   - ADR16     on PF.9                                            *\n");
    printf("*   - ADR17     on PF.8                                            *\n");
    printf("*   - ADR18     on PF.7                                            *\n");
    printf("*   - ADR19     on PF.6                                            *\n");
    printf("*   - nWR on PE.4                                                  *\n");
    printf("*   - nRD on PE.5                                                  *\n");
    printf("*   - nWRL on PG.7                                                 *\n");
    printf("*   - nWRH on PG.8                                                 *\n");
    printf("*   - nCS0 on PD.12                                                *\n");
    printf("*   - ALE on PE.2                                                  *\n");
    printf("*   - MCLK on PE.3                                                 *\n");
    printf("********************************************************************\n\n");

    /* Configure multi-function pins for EBI 16-bit application */
    Configure_EBI_16BIT_Pins();

    /* Initialize EBI bank0 to access external SRAM */
    EBI_Open(EBI_BANK0, EBI_BUSWIDTH_16BIT, EBI_TIMING_SLOWEST, 0, EBI_CS_ACTIVE_LOW);

    /* Start to test EBI SRAM */
    SRAM_BS616LV4017(512 * 1024);

    /* EBI SRAM with PDMA test */
    AccessEBIWithPDMA();

    /* Disable EBI function */
    EBI_Close(EBI_BANK0);

    /* Disable EBI clock */
    CLK_DisableModuleClock(EBI_MODULE);

    printf("*** SRAM Test OK ***\n");

    while(1);
}


/*---------------------------------------------------------------------------------------------------------*/
/* Global variables for PDMA                                                                               */
/*---------------------------------------------------------------------------------------------------------*/
uint32_t PDMA_TEST_LENGTH = 64;
uint32_t SrcArray[64];
uint32_t DestArray[64];
uint32_t volatile u32IsTestOver = 0;

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
    uint32_t status = PDMA_GET_INT_STATUS(PDMA);

    if(status & PDMA_INTSTS_ABTIF_Msk)    /* abort */
    {
        if(PDMA_GET_ABORT_STS(PDMA) & PDMA_ABTSTS_ABTIF2_Msk)
            u32IsTestOver = 2;
        PDMA_CLR_ABORT_FLAG(PDMA, PDMA_ABTSTS_ABTIF2_Msk);
    }
    else if(status & PDMA_INTSTS_TDIF_Msk)      /* done */
    {
        if(PDMA_GET_TD_STS(PDMA) & PDMA_TDSTS_TDIF2_Msk)
            u32IsTestOver = 1;
        PDMA_CLR_TD_FLAG(PDMA, PDMA_TDSTS_TDIF2_Msk);
    }
    else
        printf("unknown interrupt !!\n");
}

void AccessEBIWithPDMA(void)
{
    uint32_t i;
    uint32_t u32Result0 = 0x5A5A, u32Result1 = 0x5A5A;

    printf("[[ Access EBI with PDMA ]]\n");

    /* Enable PDMA clock source */
    CLK_EnableModuleClock(PDMA_MODULE);

    for(i=0; i<64; i++)
    {
        SrcArray[i] = 0x76570000 + i;
        u32Result0 += SrcArray[i];
    }

    /* Open Channel 2 */
    PDMA_Open(PDMA, (1<<2));

    //burst size is 4
    PDMA_SetBurstType(PDMA, 2, PDMA_REQ_BURST, PDMA_BURST_4);

    /* transfer width is one word(32 bit) */
    PDMA_SetTransferCnt(PDMA, 2, PDMA_WIDTH_32, PDMA_TEST_LENGTH);
    PDMA_SetTransferAddr(PDMA, 2, (uint32_t)SrcArray, PDMA_SAR_INC, EBI_BANK0_BASE_ADDR, PDMA_DAR_INC);
    PDMA_SetTransferMode(PDMA, 2, PDMA_MEM, FALSE, 0);

    PDMA_EnableInt(PDMA, 2, PDMA_INT_TRANS_DONE);
    NVIC_EnableIRQ(PDMA_IRQn);

    u32IsTestOver = 0;
    PDMA_Trigger(PDMA, 2);
    while(u32IsTestOver == 0);
    /* Transfer internal SRAM to EBI SRAM done */

    /* Clear internal SRAM data */
    for(i=0; i<64; i++)
    {
        SrcArray[i] = 0x0;
    }

    /* transfer width is one word(32 bit) */
    PDMA_SetTransferCnt(PDMA, 2, PDMA_WIDTH_32, PDMA_TEST_LENGTH);
    PDMA_SetTransferAddr(PDMA, 2, EBI_BANK0_BASE_ADDR, PDMA_SAR_INC, (uint32_t)SrcArray, PDMA_DAR_INC);
    PDMA_SetTransferMode(PDMA, 2, PDMA_MEM, FALSE, 0);

    u32IsTestOver = 0;
    PDMA_Trigger(PDMA, 2);
    while(u32IsTestOver == 0);
    /* Transfer EBI SRAM to internal SRAM done */
    for(i=0; i<64; i++)
    {
        u32Result1 += SrcArray[i];
    }

    if(u32IsTestOver == 1)
    {
        if((u32Result0 == u32Result1) && (u32Result0 != 0x5A5A))
        {
            printf("        PASS (0x%X)\n\n", u32Result0);
        }
        else
        {
            printf("        FAIL - data matched (0x%X)\n\n", u32Result0);
            while(1);
        }
    }
    else
    {
        printf("        PDMA fail\n\n");
        while(1);
    }

    PDMA_Close(PDMA);
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
