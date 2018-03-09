/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief
 *           Show how to wake up system form Power-down mode by brown-out detector interrupt.
 *
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include "stdio.h"
#include "NuMicro.h"


#define PLL_CLOCK    192000000


/*---------------------------------------------------------------------------------------------------------*/
/*  Function for System Entry to Power Down Mode                                                           */
/*---------------------------------------------------------------------------------------------------------*/
void PowerDownFunction(void)
{
    /* Check if all the debug messages are finished */
    UART_WAIT_TX_EMPTY(UART0);

    /* Enable Power-down mode wake-up interrupt */
    CLK->PWRCTL |= CLK_PWRCTL_PDWKIEN_Msk;

    /* Enter to Power-down mode */
    CLK_PowerDown();

}

/*---------------------------------------------------------------------------------------------------------*/
/*  Brown Out Detector IRQ Handler                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
void BOD_IRQHandler(void)
{
    /* Clear BOD Interrupt Flag */
    SYS_CLEAR_BOD_INT_FLAG();

    printf("Brown Out is Detected.\n");
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Power-down Mode Wake-up IRQ Handler                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
void PWRWU_IRQHandler(void)
{
    /* Check system power down mode wake-up interrupt status flag */
    if(CLK->PWRCTL & CLK_PWRCTL_PDWKIF_Msk)
    {
        /* Clear system power down wake-up interrupt flag */
        CLK->PWRCTL |= CLK_PWRCTL_PDWKIF_Msk;

        printf("System wake-up from Power-down mode.\n");
    }
}

void SYS_Init(void)
{

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT clock (external XTAL 12MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);

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

    /* Set PC multi-function pins for CLKO(PC.13) */
    SYS->GPC_MFPH = (SYS->GPC_MFPH & ~SYS_GPC_MFPH_PC13MFP_Msk) | SYS_GPC_MFPH_PC13MFP_CLKO;

}

void UART0_Init()
{
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

int32_t main(void)
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
    printf("+------------------------------------------------+\n");
    printf("|        Power-down and Wake-up Sample Code      |\n");
    printf("+------------------------------------------------+\n");

    /* Unlock protected registers before setting Brown-out detector function and Power-down mode */
    SYS_UnlockReg();

    /* Enable Brown-out detector function */
    SYS_ENABLE_BOD();

    /* Set Brown-out detector voltage level as 3.0V */
    SYS_SET_BOD_LEVEL(SYS_BODCTL_BODVL_3_0V);

    /* Enable Brown-out detector interrupt function */
    SYS_DISABLE_BOD_RST();

    /* Enable Brown-out detector and Power-down wake-up interrupt */
    NVIC_EnableIRQ(BOD_IRQn);
    NVIC_EnableIRQ(PWRWU_IRQn);

    printf("System enter to Power-down mode.\n");
    printf("System wake-up if VDD voltage is lower than 3.0V.\n\n");

    /* Enter to Power-down mode */
    PowerDownFunction();

    /* Wait for Power-down mode wake-up interrupt happen */
    while(1);

}

