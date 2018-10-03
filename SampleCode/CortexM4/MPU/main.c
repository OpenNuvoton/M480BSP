/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Demonstrate the usage of Cortex-M4 MPU.
 *
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define Region_Size_1K     0x9
#define Region_Size_16K    0xD
#define Region_Size_32K    0xE
#define Region_Size_64K    0xF
#define Region_Size_128K   0x10
#define Region_Size_512K   0x12

/* MPU Attribute Register: Access Permission Definition */
#define AP_No_Access       0x0
#define AP_Pri_RW_User_NO  0x1
#define AP_Pri_RW_User_RO  0x2
#define AP_Pri_RW_User_RW  0x3
#define AP_Pri_RO_User_NO  0x5
#define AP_Pri_RO_User_RO  0x6

/* MPU Attribute Register: Region Enable Bit */
#define MPU_ATTR_EN        1

uint32_t ReadMemCore(uint32_t address)
{
    __IO uint32_t val = 0;
    uint32_t *a = (uint32_t*) address;
    val = *a;

    return val;
}

void MemManage_Handler(void)
{
    /* NOTE1: Disable MPU to allow simple return from mem_manage handler
              MemManage typically indicates code failure, and would
              be resolved by reset or terminating faulty thread in OS.
       NOTE2: The code set MPU->CTRL below will allow the code touch
              illegal address to be executed after return from
              MemManage_Handler(). If this line is comment out, this code
              will keep enter MemManage_Handler() */
    MPU->CTRL = 0x0;

    // Clear Fault status register
    SCB->CFSR = 0x000000BB;

    printf("\n Memory Fault !!");
}

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

void MPU_Test(void)
{
    uint8_t u8TestItem = 0;

    //------------------------------
    // Configure MPU memory regions
    //------------------------------

    // Region 1 (Flash Memory Space)
    // Start address = 0x0
    // Permission = Full access
    // Size = 128KB

    // Base address = Base address :OR: Region number :OR: VALID bit
    MPU->RBAR = ((0x00000000 & MPU_RBAR_ADDR_Msk) | (0x1 & MPU_RBAR_REGION_Msk) | MPU_RBAR_VALID_Msk);
    // Attribute = Full access :OR: SRD = 0 :OR: Size = 128KB :OR: ENABLE
    MPU->RASR = ((AP_Pri_RW_User_RW << MPU_RASR_AP_Pos)| ( Region_Size_128K << MPU_RASR_SIZE_Pos) | MPU_RASR_ENABLE_Msk);

    // Region 2 (SRAM Memory Space)
    // Start address = 0x20000000
    // Permission = Full access
    // Size = 16KB

    // Base address = Base address :OR: Region number :OR: VALID bit
    MPU->RBAR = ((0x20000000 & MPU_RBAR_ADDR_Msk) | (0x2 & MPU_RBAR_REGION_Msk) | MPU_RBAR_VALID_Msk);
    // Attribute = Full access :OR: SRD = 0 :OR: Size = 16KB :OR: ENABLE
    MPU->RASR = ((AP_Pri_RW_User_RW << MPU_RASR_AP_Pos)| ( Region_Size_16K << MPU_RASR_SIZE_Pos) | MPU_RASR_ENABLE_Msk);

    // Region 3 (Test Memory Space)
    // Start address = 0x20004000
    // Permission = No Access
    // Size = 1KB

    // Base address = Base address :OR: Region number :OR: VALID bit
    MPU->RBAR = ((0x20004000 & MPU_RBAR_ADDR_Msk) | (0x3 & MPU_RBAR_REGION_Msk) | MPU_RBAR_VALID_Msk);
    // Attribute = No Access :OR: SRD = 0 :OR: Size = 1KB :OR: ENABLE
    MPU->RASR = ((AP_No_Access << MPU_RASR_AP_Pos)| ( Region_Size_1K << MPU_RASR_SIZE_Pos) | MPU_RASR_ENABLE_Msk);

    // Enable MemFault enable bit
    SCB->SHCSR = SCB_SHCSR_MEMFAULTENA_Msk;
    // Enable MPU
    MPU->CTRL |= MPU_CTRL_PRIVDEFENA_Msk | MPU_CTRL_ENABLE_Msk;

    printf("\n Please Press '1' to read memory from region 1 (Flash Memory)");

    while(u8TestItem != '1') u8TestItem = getchar();

    ReadMemCore(0x00000000);

    printf("\n Please Press '2' to read memory from region 2 (SRAM)");

    while(u8TestItem != '2') u8TestItem = getchar();

    ReadMemCore(0x20000000);

    printf("\n Please Press '3' to read memory from region 3 (Test Memory)");

    while(u8TestItem != '3') u8TestItem = getchar();

    ReadMemCore(0x20004000);
}

int main()
{
    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Init UART0 for printf */
    UART0_Init();

    printf("\n Start MPU test: \n");

    MPU_Test();

    while(1);
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
