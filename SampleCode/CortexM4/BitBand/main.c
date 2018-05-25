/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Demonstrate the usage of CortexM4 BitBand.
 *
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"


/* Memory Address */
#define MEM_ADDR(address)       *((volatile unsigned long *) (address))
/* BitBand Address */
#define BITBAND(address,bitnum) ((address & 0xF0000000)+0x02000000+((address & 0xFFFFF)<<5)+(bitnum<<2))

void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable External XTAL (4~24 MHz) */
    CLK->PWRCTL |= CLK_PWRCTL_HXTEN_Msk; // XTAL12M (HXT) Enabled

    /* Waiting for 12MHz clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Switch HCLK clock source to XTAL */
    CLK->CLKSEL0 &= ~CLK_CLKSEL0_HCLKSEL_Msk;
    CLK->CLKSEL0 |= CLK_CLKSEL0_HCLKSEL_HXT;

    /* Enable UART clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART clock source from HXT */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Lock protected registers */
    SYS_LockReg();
}

void UART0_Init()
{
    UART_Open(UART0, 115200);
}

void BitBand_Test(void)
{
    uint32_t u32Temp;
    uint32_t u32TestAddress;

    u32TestAddress = 0x20003F00;

    //Read SRAM Address(0x20003F00)
    u32Temp = MEM_ADDR(u32TestAddress);
    printf("\n The value at test address (0x20003F00) is: 0x%x", u32Temp);

    //Use BitBand function to read SRAM bit value
    u32Temp = MEM_ADDR(BITBAND(u32TestAddress, 3));
    printf("\n Use Bit-Band function to get value at bit 3: %x \n", u32Temp);

    //Use BitBand function set bit
    printf("\n Use Bit-Band function set test address (0x20003F00) bit 3 ");
    MEM_ADDR(BITBAND(u32TestAddress, 3)) = 1;
    //Read Test Address Value
    u32Temp = MEM_ADDR(u32TestAddress);
    printf("\n The value at address 0x20003F00 is: 0x%x \n", u32Temp);

    //Use BitBand function clear bit
    printf("\n Use Bit-Band function clear test address (0x20003F00) bit 3 ");
    MEM_ADDR(BITBAND(u32TestAddress, 3)) = 0;
    //Read Test Address Value
    u32Temp = MEM_ADDR(u32TestAddress);
    printf("\n The value at address 0x20003F00 is: 0x%x \n", u32Temp);
}

int main()
{
    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Init UART0 for printf */
    UART0_Init();

    printf("\n Start Bit-Band test: \n");

    BitBand_Test();

    while(1);
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
