/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Configure EBI interface to access MX29LV320T (NOR Flash) on EBI interface.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK       192000000
/*---------------------------------------------------------------------------------------------------------*/
/* Global Interface Variables Declarations                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
extern void NOR_MX29LV320T_RESET(uint32_t u32Bank);
extern int32_t NOR_MX29LV320T_CheckStatus(uint32_t u32DstAddr, uint16_t u16Data, uint32_t u32TimeoutMs);
extern uint16_t NOR_MX29LV320T_READ(uint32_t u32Bank, uint32_t u32DstAddr);
extern int32_t NOR_MX29LV320T_WRITE(uint32_t u32Bank, uint32_t u32DstAddr, uint16_t u16Data);
extern void NOR_MX29LV320T_GET_ID(uint32_t u32Bank, uint16_t *pu16IDTable);
extern int32_t NOR_MX29LV320T_EraseChip(uint32_t u32Bank, uint32_t u32IsCheckBlank);

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

    /* EBI ADR0~3 pins on PH.4~7 */
    SYS->GPH_MFPL |= SYS_GPH_MFPL_PH7MFP_EBI_ADR0 | SYS_GPH_MFPL_PH6MFP_EBI_ADR1 |
                     SYS_GPH_MFPL_PH5MFP_EBI_ADR2 | SYS_GPH_MFPL_PH4MFP_EBI_ADR3;

    /* EBI ADR4~7 pins on PC.9~12 */
    SYS->GPC_MFPH |= SYS_GPC_MFPH_PC12MFP_EBI_ADR4 | SYS_GPC_MFPH_PC11MFP_EBI_ADR5 |
                     SYS_GPC_MFPH_PC10MFP_EBI_ADR6 | SYS_GPC_MFPH_PC9MFP_EBI_ADR7;

    /* EBI ADR8~9 pins on PG.0~1 */
    SYS->GPG_MFPL |= SYS_GPG_MFPL_PG0MFP_EBI_ADR8 | SYS_GPG_MFPL_PG1MFP_EBI_ADR9;

    /* EBI ADR10 pins on PC.13 */
    SYS->GPC_MFPH |= SYS_GPC_MFPH_PC13MFP_EBI_ADR10;

    /* EBI ADR11~13 pins on PG.2~4 */
    SYS->GPG_MFPL |= SYS_GPG_MFPL_PG2MFP_EBI_ADR11 | SYS_GPG_MFPL_PG3MFP_EBI_ADR12 |
                     SYS_GPG_MFPL_PG4MFP_EBI_ADR13;

    /* EBI ADR14~17 pins on PF.8~11 */
    SYS->GPF_MFPH |= SYS_GPF_MFPH_PF11MFP_EBI_ADR14 | SYS_GPF_MFPH_PF10MFP_EBI_ADR15 |
                     SYS_GPF_MFPH_PF9MFP_EBI_ADR16 | SYS_GPF_MFPH_PF8MFP_EBI_ADR17;

    /* EBI ADR18~19 pins on PF.6~7 */
    SYS->GPF_MFPL |= SYS_GPF_MFPL_PF7MFP_EBI_ADR18 | SYS_GPF_MFPL_PF6MFP_EBI_ADR19;

    /* EBI RD and WR pins on PE.4 and PE.5 */
    SYS->GPE_MFPL |= SYS_GPE_MFPL_PE4MFP_EBI_nWR | SYS_GPE_MFPL_PE5MFP_EBI_nRD;

    /* EBI WRL and WRH pins on PB.7 and PB.6 */
    SYS->GPB_MFPL |= SYS_GPB_MFPL_PB6MFP_EBI_nWRH | SYS_GPB_MFPL_PB7MFP_EBI_nWRL;

    /* EBI CS0 pin on PD.12 */
    SYS->GPD_MFPH |= SYS_GPD_MFPH_PD12MFP_EBI_nCS0;

    /* EBI CS1 pin on PD.11 */
    SYS->GPD_MFPH |= SYS_GPD_MFPH_PD11MFP_EBI_nCS1;

    /* EBI CS2 pin on PD.10 */
    SYS->GPD_MFPH |= SYS_GPD_MFPH_PD10MFP_EBI_nCS2;

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
    uint32_t u32Addr, u32MaxEBISize;
    uint16_t u16WData, u16RData;
    uint16_t u16IDTable[2];

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    printf("\n\nCPU @ %d Hz\n", SystemCoreClock);
    printf("+-----------------------------------------+\n");
    printf("|    EBI Nor Flash Sample Code on Bank1   |\n");
    printf("+-----------------------------------------+\n\n");

    printf("************************************************************************\n");
    printf("* Please connect MX29LV320T nor flash to EBI bank1 before accessing !! *\n");
    printf("* EBI pins settings:                                                   *\n");
    printf("*   - AD0 ~ AD5   on PC.0 ~ PC.5                                       *\n");
    printf("*   - AD6 ~ AD7   on PD.8 ~ PD.9                                       *\n");
    printf("*   - AD8 ~ AD9   on PE.14 ~ PE.15                                     *\n");
    printf("*   - AD10        on PE.1                                              *\n");
    printf("*   - AD11        on PE.0                                              *\n");
    printf("*   - AD12 ~ AD15 on PH.8 ~ PH.11                                      *\n");
    printf("*   - ADR0      on PH.7                                                *\n");
    printf("*   - ADR1      on PH.6                                                *\n");
    printf("*   - ADR2      on PH.5                                                *\n");
    printf("*   - ADR3      on PH.4                                                *\n");
    printf("*   - ADR4      on PC.12                                               *\n");
    printf("*   - ADR5      on PC.11                                               *\n");
    printf("*   - ADR6      on PC.10                                               *\n");
    printf("*   - ADR7      on PC.9                                                *\n");
    printf("*   - AD8 ~ AD9 on PG.0 ~ PG.1                                         *\n");
    printf("*   - ADR10     on PC.13                                               *\n");
    printf("*   - AD11 ~ AD13 on PG.2 ~ PG.4                                       *\n");
    printf("*   - ADR14     on PF.11                                               *\n");
    printf("*   - ADR15     on PF.10                                               *\n");
    printf("*   - ADR16     on PF.9                                                *\n");
    printf("*   - ADR17     on PF.8                                                *\n");
    printf("*   - ADR18     on PF.7                                                *\n");
    printf("*   - ADR19     on PF.6                                                *\n");
    printf("*   - nWR on PE.4                                                      *\n");
    printf("*   - nRD on PE.5                                                      *\n");
    printf("*   - nWRL on PG.7                                                     *\n");
    printf("*   - nWRH on PG.8                                                     *\n");
    printf("*   - nCS0 on PD.12                                                    *\n");
    printf("*   - nCS1 on PD.11                                                    *\n");
    printf("*   - nCS2 on PD.10                                                    *\n");
    printf("*   - ALE on PE.2                                                      *\n");
    printf("*   - MCLK on PE.3                                                     *\n");
    printf("************************************************************************\n\n");

    /* Configure multi-function pins for EBI 16-bit application */
    Configure_EBI_16BIT_Pins();

    /* Initialize EBI bank1 to access external nor */
    EBI_Open(EBI_BANK1, EBI_BUSWIDTH_16BIT, EBI_TIMING_VERYSLOW, 0, EBI_CS_ACTIVE_LOW);


    /* Step 1, check ID */
    NOR_MX29LV320T_GET_ID(EBI_BANK1, (uint16_t *)u16IDTable);
    printf(">> Manufacture ID: 0x%X, Device ID: 0x%X .... ", u16IDTable[0], u16IDTable[1]);
    if((u16IDTable[0] != 0xC2) || (u16IDTable[1] != 0x22A8))
    {
        printf("FAIL !!!\n\n");
        while(1);
    }
    else
    {
        printf("PASS !!!\n\n");
    }


    /* Step 2, erase chip */
    if(NOR_MX29LV320T_EraseChip(EBI_BANK1, TRUE) < 0)
        while(1);


    /* Step 3, program flash and compare data */
    printf(">> Run program flash test ......\n");
    u32MaxEBISize = EBI_MAX_SIZE;
    for(u32Addr = 0; u32Addr < u32MaxEBISize; u32Addr += 2)
    {
        u16WData = (0x7657 + u32Addr / 2) & 0xFFFF;
        if(NOR_MX29LV320T_WRITE(EBI_BANK1, u32Addr, u16WData) < 0)
        {
            printf("Program [0x%08X]: [0x%08X] FAIL !!!\n\n", (uint32_t)(EBI_BANK0_BASE_ADDR + (0x100000 * EBI_BANK1)) + u32Addr, u16WData);
            while(1);
        }
        else
        {
            /* Show UART message ...... */
            if((u32Addr % 256) == 0)
                printf("Program [0x%08X]:[0x%08X] !!!       \r", (uint32_t)(EBI_BANK0_BASE_ADDR + (0x100000 * EBI_BANK1)) + u32Addr, u16WData);
        }
    }

    for(u32Addr = 0; u32Addr < u32MaxEBISize; u32Addr += 2)
    {
        u16WData = (0x7657 + u32Addr / 2) & 0xFFFF;
        u16RData = NOR_MX29LV320T_READ(EBI_BANK1, u32Addr);
        if(u16WData != u16RData)
        {
            printf("Compare [0x%08X] FAIL !!! (W:0x%08X, R:0x%08X)\n\n", (uint32_t)(EBI_BANK0_BASE_ADDR + (0x100000 * EBI_BANK1)) + u32Addr, u16WData, u16RData);
            while(1);
        }
        else
        {
            /* Show UART message ...... */
            if((u32Addr % 256) == 0)
                printf("Read [0x%08X]: [0x%08X] !!!         \r", (uint32_t)(EBI_BANK0_BASE_ADDR + (0x100000 * EBI_BANK1)) + u32Addr, u16RData);
        }
    }
    printf(">> Program flash OK !!!                             \n\n");

    /* Disable EBI function */
    EBI_Close(EBI_BANK1);

    /* Disable EBI clock */
    CLK->AHBCLK &= ~CLK_AHBCLK_EBICKEN_Msk;

    while(1);
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
