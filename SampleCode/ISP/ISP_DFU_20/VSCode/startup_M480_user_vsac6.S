/**************************************************************************//**
 * @file     startup_M480_user_vscode.s
 * @version  V1.00
 * @brief    CMSIS Cortex-M4 Core Device Startup File for M480
 *
 * @copyright SPDX-License-Identifier: Apache-2.0
 * @copyright Copyright (C) 2025 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
/*
//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
*/


    .section .bss.STACK, "aw", %nobits
    .align 3

    .global __initial_sp
#ifndef Stack_Size
// <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
    .equ    Stack_Size, 0x00000800
#endif
Stack_Mem:
    .space   Stack_Size
__initial_sp:


    .section .bss.HEAP, "aw", %nobits
    .align  3
    .global Heap_Mem
    .global __heap_base
    .global __heap_limit
#ifndef Heap_Size
// <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
    .equ    Heap_Size, 0x00000100
#endif
__heap_base:
Heap_Mem:
    .space  Heap_Size
__heap_limit:

    .eabi_attribute Tag_ABI_align_preserved, 1
    .thumb

//*** <<< end of configuration section >>>    ***


// ; Vector Table Mapped to Address 0 at Reset
    .section RESET, "ax"
    .global     __Vectors
    .global     __Vectors_End
    .global     __Vectors_Size

__Vectors:
    .word     __initial_sp              //; Top of Stack
    .word     Reset_Handler             //; Reset Handler
    .word     NMI_Handler               //; NMI Handler
    .word     HardFault_Handler         //; Hard Fault Handler
    .word     MemManage_Handler         //; MPU Fault Handler
    .word     BusFault_Handler          //; Bus Fault Handler
    .word     UsageFault_Handler        //; Usage Fault Handler
    .word     0                         //; Reserved
    .word     0                         //; Reserved
    .word     0                         //; Reserved
    .word     0                         //; Reserved
    .word     SVC_Handler               //; SVCall Handler
    .word     DebugMon_Handler          //; Debug Monitor Handler
    .word     0                         //; Reserved
    .word     PendSV_Handler            //; PendSV Handler
    .word     SysTick_Handler           //; SysTick Handler

    //; External Interrupts

    .word     BOD_IRQHandler  
    .word     IRC_IRQHandler            //; 1: Internal RC
	.word     PWRWU_IRQHandler          //; 2: Power down wake up
	.word     RAMPE_IRQHandler          //; 3: RAM parity error
	.word     CKFAIL_IRQHandler         //; 4: Clock detection fail
	.word     Default_Handler           //; 5: Reserved
	.word     RTC_IRQHandler            //; 6: Real Time Clock
	.word     TAMPER_IRQHandler         //; 7: Tamper detection
	.word     WDT_IRQHandler            //; 8: Watchdog timer
	.word     WWDT_IRQHandler           //; 9: Window watchdog timer
	.word     EINT0_IRQHandler          //; 10: External Input 0
	.word     EINT1_IRQHandler          //; 11: External Input 1
	.word     EINT2_IRQHandler          //; 12: External Input 2
	.word     EINT3_IRQHandler          //; 13: External Input 3
	.word     EINT4_IRQHandler          //; 14: External Input 4
	.word     EINT5_IRQHandler          //; 15: External Input 5
	.word     GPA_IRQHandler            //; 16: GPIO Port A
	.word     GPB_IRQHandler            //; 17: GPIO Port B
	.word     GPC_IRQHandler            //; 18: GPIO Port C
	.word     GPD_IRQHandler            //; 19: GPIO Port D
	.word     GPE_IRQHandler            //; 20: GPIO Port E
	.word     GPF_IRQHandler            //; 21: GPIO Port F
	.word     QSPI0_IRQHandler          //; 22: QSPI0
	.word     SPI0_IRQHandler           //; 23: SPI0
	.word     BRAKE0_IRQHandler         //; 24:
	.word     EPWM0P0_IRQHandler        //; 25:
	.word     EPWM0P1_IRQHandler        //; 26:
	.word     EPWM0P2_IRQHandler        //; 27:
	.word     BRAKE1_IRQHandler         //; 28:
	.word     EPWM1P0_IRQHandler        //; 29:
	.word     EPWM1P1_IRQHandler        //; 30:
	.word     EPWM1P2_IRQHandler        //; 31:
	.word     TMR0_IRQHandler           //; 32: Timer 0
	.word     TMR1_IRQHandler           //; 33: Timer 1
	.word     TMR2_IRQHandler           //; 34: Timer 2
	.word     TMR3_IRQHandler           //; 35: Timer 3
	.word     UART0_IRQHandler          //; 36: UART0
	.word     UART1_IRQHandler          //; 37: UART1
	.word     I2C0_IRQHandler           //; 38: I2C0
	.word     I2C1_IRQHandler           //; 39: I2C1
	.word     PDMA_IRQHandler           //; 40: Peripheral DMA
	.word     DAC_IRQHandler            //; 41: DAC
	.word     EADC00_IRQHandler         //; 42: EADC0 interrupt source 0
	.word     EADC01_IRQHandler         //; 43: EADC0 interrupt source 1
	.word     ACMP01_IRQHandler         //; 44: ACMP0 and ACMP1
	.word     Default_Handler           //; 45: Reserved
	.word     EADC02_IRQHandler         //; 46: EADC0 interrupt source 2
	.word     EADC03_IRQHandler         //; 47: EADC0 interrupt source 3
	.word     UART2_IRQHandler          //; 48: UART2
	.word     UART3_IRQHandler          //; 49: UART3
	.word     QSPI1_IRQHandler          //; 50: QSPI1
	.word     SPI1_IRQHandler           //; 51: SPI1
	.word     SPI2_IRQHandler           //; 52: SPI2
	.word     USBD_IRQHandler           //; 53: USB device
	.word     OHCI_IRQHandler           //; 54: OHCI
	.word     USBOTG_IRQHandler         //; 55: USB OTG
	.word     CAN0_IRQHandler           //; 56: CAN0
	.word     CAN1_IRQHandler           //; 57: CAN1
	

__Vectors_End:
    .equ    __Vectors_Size, __Vectors_End - __Vectors

    .section .text, "ax"

// ; Reset Handler
    .global Reset_Handler
    .global  SystemInit
    .global  __main
    .type   Reset_Handler, "function"
Reset_Handler:
        //; Unlock Register
		LDR     R0, =0x40000100
		LDR     R1, =0x59
		STR     R1, [R0]
		LDR     R1, =0x16
		STR     R1, [R0]
		LDR     R1, =0x88
		STR     R1, [R0]
		
	.ifndef ENABLE_SPIM_CACHE
		LDR     R0, =0x40000200            //; R0 = Clock Controller Register Base Address
		LDR     R1, [R0,#0x4]              //; R1 = 0x40000204  (AHBCLK)
		ORR     R1, R1, #0x4000
		STR     R1, [R0,#0x4]              //; CLK->AHBCLK |= CLK_AHBCLK_SPIMCKEN_Msk;

		LDR     R0, =0x40007000            //; R0 = SPIM Register Base Address
		LDR     R1, [R0,#4]                //; R1 = SPIM->CTL1
		ORR     R1, R1,#2                  //; R1 |= SPIM_CTL1_CACHEOFF_Msk
		STR     R1, [R0,#4]                //; _SPIM_DISABLE_CACHE()
		LDR     R1, [R0,#4]                //; R1 = SPIM->CTL1
		ORR     R1, R1, #4                 //; R1 |= SPIM_CTL1_CCMEN_Msk
		STR     R1, [R0,#4]                //; _SPIM_ENABLE_CCM()
	.endif	

        LDR     R0, =SystemInit
        BLX     R0
		
		//; Init POR
		//; LDR     R2, =0x40000024
		//; LDR     R1, =0x00005AA5
		//; STR     R1, [R2]

		//; Lock
		LDR     R0, =0x40000100
		LDR     R1, =0
		STR     R1, [R0]
				
        LDR     R0, =__main
        BX      R0


// ; Dummy Exception Handlers (infinite loops which can be modified)
    .weak   NMI_Handler
    .type   NMI_Handler, "function"
NMI_Handler:
        B       .

    .weak   HardFault_Handler
    .type   HardFault_Handler, "function"
HardFault_Handler:
        B       .

	.weak   MemManage_Handler, "function"
MemManage_Handler:
        B       .

    .weak   BusFault_Handler, "function"
BusFault_Handler:
        B       .

    .weak   UsageFault_Handler, "function"
UsageFault_Handler:
        B       .

    .weak   SVC_Handler, "function"
SVC_Handler:
        B       .

    .weak   DebugMon_Handler, "function"
DebugMon_Handler:
        B       .

    .weak   PendSV_Handler, "function"
PendSV_Handler:
        B       .

    .weak   SysTick_Handler, "function"
SysTick_Handler:
        B       .		

    .weak  Default_Handler,"function"
    .weak  BOD_IRQHandler,"function"
	.weak  IRC_IRQHandler,"function"
	.weak  PWRWU_IRQHandler,"function"
	.weak  RAMPE_IRQHandler,"function"
	.weak  CKFAIL_IRQHandler,"function"
	.weak  RTC_IRQHandler,"function"
	.weak  TAMPER_IRQHandler,"function"
	.weak  WDT_IRQHandler,"function"
	.weak  WWDT_IRQHandler,"function"
	.weak  EINT0_IRQHandler,"function"
	.weak  EINT1_IRQHandler,"function"
	.weak  EINT2_IRQHandler,"function"
	.weak  EINT3_IRQHandler,"function"
	.weak  EINT4_IRQHandler,"function"
	.weak  EINT5_IRQHandler,"function"
	.weak  GPA_IRQHandler,"function"
	.weak  GPB_IRQHandler,"function"
	.weak  GPC_IRQHandler,"function"
	.weak  GPD_IRQHandler,"function"
	.weak  GPE_IRQHandler,"function"
	.weak  GPF_IRQHandler,"function"
	.weak  QSPI0_IRQHandler,"function"
	.weak  SPI0_IRQHandler,"function"
	.weak  BRAKE0_IRQHandler,"function"
	.weak  EPWM0P0_IRQHandler,"function"
	.weak  EPWM0P1_IRQHandler,"function"
	.weak  EPWM0P2_IRQHandler,"function"
	.weak  BRAKE1_IRQHandler,"function"
	.weak  EPWM1P0_IRQHandler,"function"
	.weak  EPWM1P1_IRQHandler,"function"
	.weak  EPWM1P2_IRQHandler,"function"
	.weak  TMR0_IRQHandler,"function"
	.weak  TMR1_IRQHandler,"function"
	.weak  TMR2_IRQHandler,"function"
	.weak  TMR3_IRQHandler,"function"
	.weak  UART0_IRQHandler,"function"
	.weak  UART1_IRQHandler,"function"
	.weak  I2C0_IRQHandler,"function"
	.weak  I2C1_IRQHandler,"function"
	.weak  PDMA_IRQHandler,"function"
	.weak  DAC_IRQHandler,"function"
	.weak  EADC00_IRQHandler,"function"
	.weak  EADC01_IRQHandler,"function"
	.weak  ACMP01_IRQHandler,"function"
	.weak  EADC02_IRQHandler,"function"
	.weak  EADC03_IRQHandler,"function"
	.weak  UART2_IRQHandler,"function"
	.weak  UART3_IRQHandler,"function"
	.weak  QSPI1_IRQHandler,"function"
	.weak  SPI1_IRQHandler,"function"
	.weak  SPI2_IRQHandler,"function"
	.weak  USBD_IRQHandler,"function"
	.weak  OHCI_IRQHandler,"function"
	.weak  USBOTG_IRQHandler,"function"
	.weak  CAN0_IRQHandler,"function"
	.weak  CAN1_IRQHandler,"function"

Default_Handler:	
BOD_IRQHandler:
IRC_IRQHandler:
PWRWU_IRQHandler:
RAMPE_IRQHandler:
CKFAIL_IRQHandler:
RTC_IRQHandler:
TAMPER_IRQHandler:
WDT_IRQHandler:
WWDT_IRQHandler:
EINT0_IRQHandler:
EINT1_IRQHandler:
EINT2_IRQHandler:
EINT3_IRQHandler:
EINT4_IRQHandler:
EINT5_IRQHandler:
GPA_IRQHandler:
GPB_IRQHandler:
GPC_IRQHandler:
GPD_IRQHandler:
GPE_IRQHandler:
GPF_IRQHandler:
QSPI0_IRQHandler:
SPI0_IRQHandler:
BRAKE0_IRQHandler:
EPWM0P0_IRQHandler:
EPWM0P1_IRQHandler:
EPWM0P2_IRQHandler:
BRAKE1_IRQHandler:
EPWM1P0_IRQHandler:
EPWM1P1_IRQHandler:
EPWM1P2_IRQHandler:
TMR0_IRQHandler:
TMR1_IRQHandler:
TMR2_IRQHandler:
TMR3_IRQHandler:
UART0_IRQHandler:
UART1_IRQHandler:
I2C0_IRQHandler:
I2C1_IRQHandler:
PDMA_IRQHandler:
DAC_IRQHandler:
EADC00_IRQHandler:
EADC01_IRQHandler:
ACMP01_IRQHandler:
EADC02_IRQHandler:
EADC03_IRQHandler:
UART2_IRQHandler:
UART3_IRQHandler:
QSPI1_IRQHandler:
SPI1_IRQHandler:
SPI2_IRQHandler:
USBD_IRQHandler:
OHCI_IRQHandler:
USBOTG_IRQHandler:
CAN0_IRQHandler:
CAN1_IRQHandler:
        B       .

    .align 2


