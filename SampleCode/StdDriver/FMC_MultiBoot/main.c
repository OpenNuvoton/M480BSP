/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief
 *           Implement a multi-boot system to boot from different applications in APROM.
 *           A LDROM code and 4 APROM code are implemented in this sample code.
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include <stdio.h>

#include "NuMicro.h"


#if !defined(__ICCARM__) && !defined(__GNUC__)
extern uint32_t Image$$RO$$Base;
#endif

void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Switch HCLK clock source to HXT */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HXT,CLK_CLKDIV0_HCLK(1));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Lock protected registers */
    SYS_LockReg();
}

int32_t main(void)
{
    uint8_t ch;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O. */
    SYS_Init();

    /* Configure UART0: 115200, 8-bit word, no parity bit, 1 stop bit. */
    UART_Open(UART0, 115200);

    /*
        This sample code shows how to boot with different firmware images in APROM.
        In the code, VECMAP is used to implement multi-boot function. Software set VECMAP
        to remap page of VECMAP to 0x0~0x1ff.
        NOTE: VECMAP only valid when CBS = 00'b or 10'b.

        To use this sample code, please:
        1. Build all targets and download to device individually. The targets are:
            FMC_MultiBoot, RO=0x0
            FMC_Boot0, RO=0x4000
            FMC_Boot1, RO=0x8000
            FMC_Boot2, RO=0xC000
            FMC_Boot3, RO=0x10000
        2. Reset MCU to execute FMC_MultiBoot.

    */

    /* Unlock protected registers */
    SYS_UnlockReg();

    printf("\n\n");
    printf("+----------------------------------------------+\n");
    printf("|     Multi-Boot Sample Code(0x%08X)       |\n", FMC_GetVECMAP());
    printf("+----------------------------------------------+\n");

    /* Enable FMC ISP function */
    FMC_Open();

#if defined(__ICCARM__) || defined(__GNUC__)
    printf("VECMAP = 0x%x\n", FMC_GetVECMAP());
#else
#ifndef BootLD
    printf("Current RO Base = 0x%x, VECMAP = 0x%x\n", (uint32_t)&Image$$RO$$Base, FMC_GetVECMAP());
#else
    printf("VECMAP = 0x%x\n", FMC_GetVECMAP());
#endif
#endif

    printf("Select one boot image: \n");
    printf("[0] Boot 0, base = 0x4000\n");
    printf("[1] Boot 1, base = 0x8000\n");
    printf("[2] Boot 2, base = 0xC000\n");
    printf("[3] Boot 3, base = 0x10000\n");
    printf("[4] Boot 4, base = 0x100000\n");
    printf("[Others] Boot, base = 0x0\n");

    ch = getchar();
    switch(ch)
    {
    case '0':
        FMC_SetVectorPageAddr(0x4000);
        break;
    case '1':
        FMC_SetVectorPageAddr(0x8000);
        break;
    case '2':
        FMC_SetVectorPageAddr(0xC000);
        break;
    case '3':
        FMC_SetVectorPageAddr(0x10000);
        break;
    case '4':
        FMC_SetVectorPageAddr(0x100000);
        break;
    default:
        FMC_SetVectorPageAddr(0x0);
        break;
    }

    if (g_FMC_i32ErrCode != 0)
    {
        printf("FMC_SetVectorPageAddr failed!\n");
        while (1);
    }

    /* Reset CPU only to reset to new vector page */
    SYS_ResetCPU();

    /* Reset System to reset to new vector page. */
    // NVIC_SystemReset();

    while(1);
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/


