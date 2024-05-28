/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    This sample shows how to make an application booting from APROM
 *           with a user application code on SPIM flash.
 *
 * @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include <stdio.h>
#include <inttypes.h>

#include "NuMicro.h"

#define USE_4_BYTES_MODE            0            /* W25Q20 does not support 4-bytes address mode. */

#define SPIM_CIPHER_ON              0

typedef void (FUNC_PTR)(void);

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

    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable SPIM module clock */
    CLK_EnableModuleClock(SPIM_MODULE);

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Init SPIM multi-function pins, MOSI(PE.2), MISO(PG.13), CLK(PE.4), SS(PG.11), D3(PE.6), and D2(PE.7) */
    SYS->GPE_MFPL &= ~(SYS_GPE_MFPL_PE2MFP_Msk | SYS_GPE_MFPL_PE4MFP_Msk |
                       SYS_GPE_MFPL_PE6MFP_Msk | SYS_GPE_MFPL_PE7MFP_Msk);
    SYS->GPG_MFPH &= ~(SYS_GPG_MFPH_PG11MFP_Msk | SYS_GPG_MFPH_PG13MFP_Msk);
    SYS->GPE_MFPL |= SYS_GPE_MFPL_PE2MFP_SPIM_MOSI | SYS_GPE_MFPL_PE4MFP_SPIM_CLK |
                     SYS_GPE_MFPL_PE6MFP_SPIM_D3 | SYS_GPE_MFPL_PE7MFP_SPIM_D2;
    SYS->GPG_MFPH |= SYS_GPG_MFPH_PG11MFP_SPIM_SS | SYS_GPG_MFPH_PG13MFP_SPIM_MISO;
    PE->SMTEN |= GPIO_SMTEN_SMTEN4_Msk;

    /* Set SPIM I/O pins as high slew rate up to 80 MHz. */
    PE->SLEWCTL = (PE->SLEWCTL & 0xFFFF0CCF) |
                  (0x1<<GPIO_SLEWCTL_HSREN2_Pos) | (0x1<<GPIO_SLEWCTL_HSREN4_Pos) |
                  (0x1<<GPIO_SLEWCTL_HSREN6_Pos) | (0x1<<GPIO_SLEWCTL_HSREN7_Pos);
    PG->SLEWCTL = (PG->SLEWCTL & 0xF33FFFFF) |
                  (0x1<<GPIO_SLEWCTL_HSREN11_Pos) | (0x1<<GPIO_SLEWCTL_HSREN13_Pos);

    /* Lock protected registers */
    SYS_LockReg();
}

void UART0_Init(void)
{
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

uint32_t __spi_start__ = 0x8000000;

# if defined ( __GNUC__ ) && !(__CC_ARM) && !(__ICCARM__) && !defined(__ARMCC_VERSION)
void start_app(uint32_t pc, uint32_t sp)
{
    asm("MSR MSP, r1                  \n" /*; load r1 into MSP */
        "BX  r0                       \n" /*; branch to the address at r0 */
       );
}
# elif defined(__ICCARM__)      // IAR
void start_app(uint32_t pc, uint32_t sp)
{
    asm("MSR MSP, r1                  \n" /*; load r1 into MSP */
        "BX  r0                       \n" /*; branch to the address at r0 */
       );
}
#else
void start_app(uint32_t pc, uint32_t sp)
{
    FUNC_PTR    *func;
    func = (FUNC_PTR *) pc;
    __set_MSP(sp);
    func();
}
#endif

int main()
{
    uint8_t idBuf[3];
    uint32_t *app_code = (uint32_t *)__spi_start__;
    uint32_t app_sp;
    uint32_t app_start;

    SYS_Init();                        /* Init System, IP clock and multi-function I/O    */

    UART0_Init();                      /* Initialize UART0                                */

    printf("+--------------------------------------------------+\n");
    printf("|    M480 SPIM DMM mode running program on flash   |\n");
    printf("+--------------------------------------------------+\n");

    SYS_UnlockReg();                   /* Unlock protected registers                      */

    SPIM_SET_CLOCK_DIVIDER(1);        /* Set SPIM clock as HCLK divided by 2 */

    SPIM_SET_RXCLKDLY_RDDLYSEL(0);    /* Insert 0 delay cycle. Adjust the sampling clock of received data to latch the correct data. */
    SPIM_SET_RXCLKDLY_RDEDGE();       /* Use SPI input clock rising edge to sample received data. */

    SPIM_SET_DCNUM(8);                /* 8 is the default value. */

    if (SPIM_InitFlash(1) != 0)        /* Initialized SPI flash */
    {
        printf("SPIM flash initialize failed!\n");
        while (1);
    }

    SPIM_ReadJedecId(idBuf, sizeof (idBuf), 1);
    printf("SPIM get JEDEC ID=0x%02X, 0x%02X, 0x%02X\n", idBuf[0], idBuf[1], idBuf[2]);

    SPIM_DISABLE_CCM();

    //SPIM_DISABLE_CACHE();
    SPIM_ENABLE_CACHE();

    if (SPIM_CIPHER_ON)
        SPIM_ENABLE_CIPHER();
    else
        SPIM_DISABLE_CIPHER();

    SPIM_Enable_4Bytes_Mode(USE_4_BYTES_MODE, 1);

    SPIM->CTL1 |= SPIM_CTL1_CDINVAL_Msk;        // invalid cache

    SPIM_EnterDirectMapMode(USE_4_BYTES_MODE, CMD_DMA_FAST_READ, 0);

    printf("\n\nProgram is currently running on APROM flash.\n");
    printf("Now branch to the sub-routine on SPIM flash...\n");

    app_sp = app_code[0];
    app_start = app_code[1];
    SCB->VTOR = ((uint32_t) __spi_start__);
    start_app(app_start, app_sp);
    while(1);
}


