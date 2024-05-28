/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Show hard fault information when hard fault happened.
 *
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "NuMicro.h"

#include "uart.h"

/*
 The ARM Generic User Guide lists the following sources for a hard fault:

 All faults result in the HardFault exception being taken or cause lockup if
 they occur in the NMI or HardFault handler. The faults are:
  - execution of an SVC instruction at a priority equal or higher than SVCall
  - execution of a BKPT instruction without a debugger attached
  - a system-generated bus error on a load or store
  - execution of an instruction from an XN memory address
  - execution of an instruction from a location for which the system generates a bus fault
  - a system-generated bus error on a vector fetch execution of an Undefined instruction
  - execution of an instruction when not in Thumb-State as a result of the T-bit being previously cleared to 0
  - an attempted load or store to an unaligned address.

 In this sample code, we will show you some information to debug with hardfault exception.

  - Default Hard Fault Handler

    The default hard fault handler is implement in retarget.c and called Hard_Fault_Handler
    By default, Hard_Fault_Handler will print out the information of r0, r1, r2, r3, r12, lr, pc and psr.

  - Overwrite the default Hard Fault Handler

    The default Hard_Fault_Handler is a weak function.
    User can over write it by implementing their own Hard_Fault_Handler.

 NOTE:
    Because hard fault exception will cause data stacking.
    User must make sure SP is pointing to an valid memory location.
    Otherwise, it may cause system lockup and reset when hard fault.

*/

#define USE_MY_HARDFAULT    1   /* Select to use default hard fault handler or not. 0: Default  1: User define */

void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
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

    /* Enable IP clock */
    CLK->APBCLK0 |= CLK_APBCLK0_UART0CKEN_Msk; // UART0 Clock Enable

    CLK->APBCLK0 |= CLK_APBCLK0_UART0CKEN_Msk | CLK_APBCLK0_TMR1CKEN_Msk;

    /* Select IP clock source */
    CLK->CLKSEL1 &= ~CLK_CLKSEL1_UART0SEL_Msk;
    CLK->CLKSEL1 |= (0x0 << CLK_CLKSEL1_UART0SEL_Pos);// Clock source from external 12 MHz crystal clock

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
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

#if USE_MY_HARDFAULT

/**
  * @brief      User defined hard fault handler
  * @param      stack   A pointer to current stack
  * @return     None
  * @details    This function is an example to show how to implement user's hard fault handler
  *
  */
uint32_t ProcessHardFault(uint32_t lr, uint32_t msp, uint32_t psp)
{
    uint32_t exception_num;
    uint32_t r0, r1, r2, r3, r12, pc, psr;
    uint32_t *stack;

    stack = (uint32_t *)msp;

    /* Get information from stack */
    r0  = stack[0];
    r1  = stack[1];
    r2  = stack[2];
    r3  = stack[3];
    r12 = stack[4];
    lr  = stack[5];
    pc  = stack[6];
    psr = stack[7];


    /* Check T bit of psr */
    if((psr & (1 << 24)) == 0)
    {
        printf("PSR T bit is 0.\nHard fault caused by changing to ARM mode!\n");
        while(1);
    }

    /* Check hard fault caused by ISR */
    exception_num = psr & xPSR_ISR_Msk;
    if(exception_num > 0)
    {
        /*
        Exception number
            0 = Thread mode
            1 = Reserved
            2 = NMI
            3 = HardFault
            4-10 = Reserved11 = SVCall
            12, 13 = Reserved
            14 = PendSV
            15 = SysTick, if implemented[a]
            16 = IRQ0.
                .
                .
            n+15 = IRQ(n-1)[b]
            (n+16) to 63 = Reserved.
        The number of interrupts, n, is 32
        */

        printf("Hard fault is caused in IRQ #%d\n", exception_num - 16);

        while(1);
    }

    printf("Hard fault location is at 0x%08x\n", pc);
    /*
        If the hard fault location is a memory access instruction, You may debug the load/store issues.

        Memory access faults can be caused by:
            Invalid address - read/write wrong address
            Data alignment issue - Violate alignment rule of Cortex-M processor
            Memory access permission - MPU violations or unprivileged access (Cortex-M0+)
            Bus components or peripheral returned an error response.
    */


    printf("r0  = 0x%x\n", r0);
    printf("r1  = 0x%x\n", r1);
    printf("r2  = 0x%x\n", r2);
    printf("r3  = 0x%x\n", r3);
    printf("r12 = 0x%x\n", r12);
    printf("lr  = 0x%x\n", lr);
    printf("pc  = 0x%x\n", pc);
    printf("psr = 0x%x\n", psr);

    while(1);

}

#endif


void TMR1_IRQHandler(void)
{
    printf("This is exception n = %d\n", TMR1_IRQn);
    M32(0) = 0;
    TIMER1->INTSTS = TIMER_INTSTS_TIF_Msk;
}

int32_t main(void)
{
    void (*func)(void) = (void (*)(void))0x1000;
    char ch;

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Init UART0 for printf */
    UART0_Init();

    while(1)
    {
        printf("\n\n");
        printf("+----------------------------------------------------+\n");
        printf("|        Hard Fault Handler Sample Code              |\n");
        printf("+----------------------------------------------------+\n");
        printf("| [0] Test Load/Store Hard Fault                     |\n");
        printf("| [1] Test Thumb/ARM mode Hard Fault                 |\n");
        printf("| [2] Test Hard Fault in ISR                         |\n");
        printf("+----------------------------------------------------+\n");
        ch = getchar();

        switch(ch)
        {
        case '0':
            /* Write APROM will cause hard fault exception. (Memory access hard fault) */
            M32(0) = 0;
            break;
        case '1':
            /* Call function with bit0 = 0 will cause hard fault. (Change to ARM mode hard fault) */
            func();
            break;
        case '2':
            /* Generate Timer Interrupt to test hard fault in ISR */
            NVIC_EnableIRQ(TMR1_IRQn);
            TIMER1->CMP = 3;
            TIMER1->CTL = TIMER_CTL_INTEN_Msk | TIMER_CTL_CNTEN_Msk | TIMER_CTL_ACTSTS_Msk | TIMER_ONESHOT_MODE;
            break;
        default:
            break;
        }
    }

}




