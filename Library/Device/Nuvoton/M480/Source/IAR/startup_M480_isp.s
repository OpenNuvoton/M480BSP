;/******************************************************************************
; * @file     startup_M480.s
; * @version  V1.00
; * @brief    CMSIS Cortex-M4 Core Device Startup File for M480
; *
; * SPDX-License-Identifier: Apache-2.0
; * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
;*****************************************************************************/

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  HardFault_Handler
        EXTERN  SystemInit
        PUBLIC  __vector1_table
        PUBLIC  __vector1_table_0x1c
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA

__vector1_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler

        DCD     NMI_Handler
        DCD     HardFault_Handler
        DCD     MemManage_Handler
        DCD     BusFault_Handler
        DCD     UsageFault_Handler
__vector1_table_0x1c
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     SVC_Handler
        DCD     DebugMon_Handler
        DCD     0
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        ; External Interrupts
        DCD     BOD_IRQHandler            ; 0: Brown Out detection
        DCD     IRC_IRQHandler            ; 1: Internal RC
        DCD     PWRWU_IRQHandler          ; 2: Power down wake up
        DCD     RAMPE_IRQHandler          ; 3: RAM parity error
        DCD     CKFAIL_IRQHandler         ; 4: Clock detection fail
        DCD     Default_Handler           ; 5: Reserved
        DCD     RTC_IRQHandler            ; 6: Real Time Clock
        DCD     TAMPER_IRQHandler         ; 7: Tamper detection
        DCD     WDT_IRQHandler            ; 8: Watchdog timer
        DCD     WWDT_IRQHandler           ; 9: Window watchdog timer
        DCD     EINT0_IRQHandler          ; 10: External Input 0
        DCD     EINT1_IRQHandler          ; 11: External Input 1
        DCD     EINT2_IRQHandler          ; 12: External Input 2
        DCD     EINT3_IRQHandler          ; 13: External Input 3
        DCD     EINT4_IRQHandler          ; 14: External Input 4
        DCD     EINT5_IRQHandler          ; 15: External Input 5
        DCD     GPA_IRQHandler            ; 16: GPIO Port A
        DCD     GPB_IRQHandler            ; 17: GPIO Port B
        DCD     GPC_IRQHandler            ; 18: GPIO Port C
        DCD     GPD_IRQHandler            ; 19: GPIO Port D
        DCD     GPE_IRQHandler            ; 20: GPIO Port E
        DCD     GPF_IRQHandler            ; 21: GPIO Port F
        DCD     Default_Handler          ; 22: QSPI0
        DCD     Default_Handler           ; 23: SPI0
        DCD     Default_Handler         ; 24:
        DCD     Default_Handler         ; 25:
        DCD     Default_Handler         ; 26:
        DCD     Default_Handler         ; 27:
        DCD     Default_Handler         ; 28:
        DCD     Default_Handler         ; 29:
        DCD     Default_Handler         ; 30:
        DCD     Default_Handler         ; 31:
        DCD     TMR0_IRQHandler           ; 32: Timer 0
        DCD     TMR1_IRQHandler           ; 33: Timer 1
        DCD     Default_Handler           ; 34: Timer 2
        DCD     Default_Handler           ; 35: Timer 3
        DCD     UART0_IRQHandler          ; 36: UART0
        DCD     UART1_IRQHandler          ; 37: UART1
        DCD     I2C0_IRQHandler           ; 38: I2C0
        DCD     I2C1_IRQHandler           ; 39: I2C1
        DCD     PDMA_IRQHandler           ; 40: Peripheral DMA
        DCD     Default_Handler            ; 41: DAC
        DCD     Default_Handler         ; 42: EADC0 interrupt source 0
        DCD     Default_Handler         ; 43: EADC0 interrupt source 1
        DCD     ACMP01_IRQHandler         ; 44: ACMP0 and ACMP1
        DCD     Default_Handler           ; 45: Reserved
        DCD     Default_Handler         ; 46: EADC0 interrupt source 2
        DCD     Default_Handler         ; 47: EADC0 interrupt source 3
        DCD     UART2_IRQHandler          ; 48: UART2
        DCD     UART3_IRQHandler          ; 49: UART3
        DCD     QSPI1_IRQHandler          ; 50: QSPI1
        DCD     SPI1_IRQHandler           ; 51: SPI1
        DCD     SPI2_IRQHandler           ; 52: SPI2
        DCD     USBD_IRQHandler           ; 53: USB device
        DCD     OHCI_IRQHandler           ; 54: OHCI
        DCD     Default_Handler         ; 55: USB OTG
        DCD     Default_Handler           ; 56: CAN0
        DCD     Default_Handler           ; 57: CAN1
        DCD     Default_Handler            ; 58:
        DCD     Default_Handler            ; 59:
        DCD     Default_Handler            ; 60:
        DCD     Default_Handler           ; 61:
        DCD     Default_Handler           ; 62: SPI3
        DCD     Default_Handler           ; 63:
        DCD     SDH0_IRQHandler           ; 64: SDH0
        DCD     USBD20_IRQHandler         ; 65: USBD20
        DCD     Default_Handler        ; 66: EMAC_TX
        DCD     Default_Handler        ; 67: EMAX_RX
        DCD     Default_Handler           ; 68: I2S0
        DCD     Default_Handler           ; 69: ToDo: Add description to this Interrupt
        DCD     Default_Handler           ; 70: OPA0
        DCD     CRYPTO_IRQHandler         ; 71: CRYPTO
        DCD     GPG_IRQHandler            ; 72:
        DCD     Default_Handler          ; 73:
        DCD     Default_Handler          ; 74: UART4
        DCD     Default_Handler          ; 75: UART5
        DCD     Default_Handler          ; 76: USCI0
        DCD     Default_Handler          ; 77: USCI1
        DCD     Default_Handler          ; 78: BPWM0
        DCD     Default_Handler          ; 79: BPWM1
        DCD     SPIM_IRQHandler           ; 80: SPIM
        DCD     Default_Handler           ; 81: CCAP
        DCD     Default_Handler           ; 82: I2C2
        DCD     Default_Handler           ; 83:
        DCD     Default_Handler           ; 84: QEI0
        DCD     Default_Handler           ; 85: QEI1
        DCD     Default_Handler          ; 86: ECAP0
        DCD     Default_Handler          ; 87: ECAP1
        DCD     GPH_IRQHandler            ; 88:
        DCD     Default_Handler          ; 89:
        DCD     SDH1_IRQHandler           ; 90: SDH1
        DCD     Default_Handler           ; 91:
        DCD     Default_Handler           ; 92: EHCI
        DCD     Default_Handler       ; 93:
        DCD     Default_Handler           ; 94:
        DCD     Default_Handler           ; 95:
        DCD     Default_Handler           ; 96:
        DCD     Default_Handler           ; 97:
        DCD     Default_Handler           ; 98:
        DCD     Default_Handler           ; 99:
        DCD     Default_Handler           ; 100:
        DCD     Default_Handler           ; 101: TRNG
        DCD     Default_Handler          ; 102: UART6
        DCD     Default_Handler          ; 103: UART7
        DCD     Default_Handler         ; 104: EADC1 interrupt source 0
        DCD     Default_Handler         ; 105: EADC1 interrupt source 1
        DCD     Default_Handler         ; 106: EADC1 interrupt source 2
        DCD     Default_Handler         ; 107: EADC1 interrupt source 3
        DCD     Default_Handler           ; 108: CAN2
__Vectors_End

__Vectors       EQU   __vector1_table
__Vectors_Size  EQU   __Vectors_End - __Vectors


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        ; Unlock Register
        LDR     R0, =0x40000100
        LDR     R1, =0x59
        STR     R1, [R0]
        LDR     R1, =0x16
        STR     R1, [R0]
        LDR     R1, =0x88
        STR     R1, [R0]

	#ifndef ENABLE_SPIM_CACHE
        LDR     R0, =0x40000200            ; R0 = Clock Controller Register Base Address
        LDR     R1, [R0,#0x4]              ; R1 = 0x40000204  (AHBCLK)
        ORR     R1, R1, #0x4000              
        STR     R1, [R0,#0x4]              ; CLK->AHBCLK |= CLK_AHBCLK_SPIMCKEN_Msk;
                
        LDR     R0, =0x40007000            ; R0 = SPIM Register Base Address
        LDR     R1, [R0,#4]                ; R1 = SPIM->CTL1
        ORR     R1, R1,#2                  ; R1 |= SPIM_CTL1_CACHEOFF_Msk
        STR     R1, [R0,#4]                ; _SPIM_DISABLE_CACHE()
        LDR     R1, [R0,#4]                ; R1 = SPIM->CTL1
        ORR     R1, R1, #4                 ; R1 |= SPIM_CTL1_CCMEN_Msk
        STR     R1, [R0,#4]                ; _SPIM_ENABLE_CCM()
	#endif

        LDR     R0, =SystemInit
        BLX     R0

        ; Init POR
        ; LDR     R2, =0x40000024
        ; LDR     R1, =0x00005AA5
        ; STR     R1, [R2]

        ; Lock register
        LDR     R0, =0x40000100
        MOVS    R1, #0
        STR     R1, [R0]

        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK  BOD_IRQHandler   
        PUBWEAK  IRC_IRQHandler   
        PUBWEAK  PWRWU_IRQHandler 
        PUBWEAK  RAMPE_IRQHandler 
        PUBWEAK  CKFAIL_IRQHandler
        PUBWEAK  Default_Handler  
        PUBWEAK  RTC_IRQHandler   
        PUBWEAK  TAMPER_IRQHandler
        PUBWEAK  WDT_IRQHandler   
        PUBWEAK  WWDT_IRQHandler  
        PUBWEAK  EINT0_IRQHandler 
        PUBWEAK  EINT1_IRQHandler 
        PUBWEAK  EINT2_IRQHandler 
        PUBWEAK  EINT3_IRQHandler 
        PUBWEAK  EINT4_IRQHandler 
        PUBWEAK  EINT5_IRQHandler 
        PUBWEAK  GPA_IRQHandler   
        PUBWEAK  GPB_IRQHandler   
        PUBWEAK  GPC_IRQHandler   
        PUBWEAK  GPD_IRQHandler   
        PUBWEAK  GPE_IRQHandler   
        PUBWEAK  GPF_IRQHandler   
        PUBWEAK  TMR0_IRQHandler  
        PUBWEAK  TMR1_IRQHandler  
        PUBWEAK  UART0_IRQHandler 
        PUBWEAK  UART1_IRQHandler 
        PUBWEAK  I2C0_IRQHandler  
        PUBWEAK  I2C1_IRQHandler  
        PUBWEAK  PDMA_IRQHandler  
        PUBWEAK  ACMP01_IRQHandler
        PUBWEAK  UART2_IRQHandler 
        PUBWEAK  UART3_IRQHandler 
        PUBWEAK  QSPI1_IRQHandler 
        PUBWEAK  SPI1_IRQHandler  
        PUBWEAK  SPI2_IRQHandler  
        PUBWEAK  USBD_IRQHandler  
        PUBWEAK  OHCI_IRQHandler  
        PUBWEAK  SDH0_IRQHandler  
        PUBWEAK  USBD20_IRQHandler
        PUBWEAK  CRYPTO_IRQHandler
        PUBWEAK  GPG_IRQHandler   
        PUBWEAK  SPIM_IRQHandler  
        PUBWEAK  GPH_IRQHandler   
        PUBWEAK  SDH1_IRQHandler  
        SECTION .text:CODE:REORDER:NOROOT(1)


BOD_IRQHandler    
IRC_IRQHandler    
PWRWU_IRQHandler  
RAMPE_IRQHandler  
CKFAIL_IRQHandler 
RTC_IRQHandler    
TAMPER_IRQHandler 
WDT_IRQHandler    
WWDT_IRQHandler   
EINT0_IRQHandler  
EINT1_IRQHandler  
EINT2_IRQHandler  
EINT3_IRQHandler  
EINT4_IRQHandler  
EINT5_IRQHandler  
GPA_IRQHandler
GPB_IRQHandler
GPC_IRQHandler
GPD_IRQHandler
GPE_IRQHandler
GPF_IRQHandler
TMR0_IRQHandler   
TMR1_IRQHandler   
UART0_IRQHandler  
UART1_IRQHandler  
I2C0_IRQHandler   
I2C1_IRQHandler   
PDMA_IRQHandler     
ACMP01_IRQHandler   
UART2_IRQHandler  
UART3_IRQHandler  
QSPI1_IRQHandler  
SPI1_IRQHandler   
SPI2_IRQHandler   
USBD_IRQHandler   
OHCI_IRQHandler  
SDH0_IRQHandler   
USBD20_IRQHandler 
CRYPTO_IRQHandler 
GPG_IRQHandler    
SPIM_IRQHandler   
GPH_IRQHandler    
SDH1_IRQHandler 
Default_Handler
        B Default_Handler




        END
;/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
