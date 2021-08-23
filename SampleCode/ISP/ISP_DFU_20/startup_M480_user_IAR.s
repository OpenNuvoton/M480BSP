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
        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler

        DCD     NMI_Handler
        DCD     HardFault_Handler
        DCD     MemManage_Handler
        DCD     BusFault_Handler
        DCD     UsageFault_Handler
__vector_table_0x1c
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

__Vectors_End

__Vectors       EQU   __vector_table
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
        PUBWEAK  QSPI0_IRQHandler
        PUBWEAK  SPI0_IRQHandler
        PUBWEAK  BRAKE0_IRQHandler
        PUBWEAK  PWM0P0_IRQHandler
        PUBWEAK  PWM0P1_IRQHandler
        PUBWEAK  PWM0P2_IRQHandler
        PUBWEAK  BRAKE1_IRQHandler
        PUBWEAK  PWM1P0_IRQHandler
        PUBWEAK  PWM1P1_IRQHandler
        PUBWEAK  PWM1P2_IRQHandler
        PUBWEAK  TMR0_IRQHandler
        PUBWEAK  TMR1_IRQHandler
        PUBWEAK  TMR2_IRQHandler
        PUBWEAK  TMR3_IRQHandler
        PUBWEAK  UART0_IRQHandler
        PUBWEAK  UART1_IRQHandler
        PUBWEAK  I2C0_IRQHandler
        PUBWEAK  I2C1_IRQHandler
        PUBWEAK  PDMA_IRQHandler
        PUBWEAK  DAC_IRQHandler
        PUBWEAK  EADC00_IRQHandler
        PUBWEAK  EADC01_IRQHandler
        PUBWEAK  ACMP01_IRQHandler
        PUBWEAK  EADC02_IRQHandler
        PUBWEAK  EADC03_IRQHandler
        PUBWEAK  UART2_IRQHandler
        PUBWEAK  UART3_IRQHandler
        PUBWEAK  QSPI1_IRQHandler
        PUBWEAK  SPI1_IRQHandler
        PUBWEAK  SPI2_IRQHandler
        PUBWEAK  USBD_IRQHandler
        PUBWEAK  OHCI_IRQHandler
        PUBWEAK  USBOTG_IRQHandler
        PUBWEAK  CAN0_IRQHandler
        PUBWEAK  CAN1_IRQHandler
        PUBWEAK  SC0_IRQHandler
        PUBWEAK  SC1_IRQHandler
        PUBWEAK  SC2_IRQHandler
        PUBWEAK  SPI3_IRQHandler
        PUBWEAK  SDH0_IRQHandler
        PUBWEAK  USBD20_IRQHandler
        PUBWEAK  EMAC_TX_IRQHandler
        PUBWEAK  EMAC_RX_IRQHandler
        PUBWEAK  I2S0_IRQHandler
        PUBWEAK  OPA0_IRQHandler
        PUBWEAK  CRYPTO_IRQHandler
        PUBWEAK  GPG_IRQHandler
        PUBWEAK  EINT6_IRQHandler
        PUBWEAK  UART4_IRQHandler
        PUBWEAK  UART5_IRQHandler
        PUBWEAK  USCI0_IRQHandler
        PUBWEAK  USCI1_IRQHandler
        PUBWEAK  BPWM0_IRQHandler
        PUBWEAK  BPWM1_IRQHandler
        PUBWEAK  SPIM_IRQHandler
        PUBWEAK  CCAP_IRQHandler
        PUBWEAK  I2C2_IRQHandler
        PUBWEAK  QEI0_IRQHandler
        PUBWEAK  QEI1_IRQHandler
        PUBWEAK  ECAP0_IRQHandler
        PUBWEAK  ECAP1_IRQHandler
        PUBWEAK  GPH_IRQHandler
        PUBWEAK  EINT7_IRQHandler
        PUBWEAK  SDH1_IRQHandler
        PUBWEAK  EHCI_IRQHandler
        PUBWEAK  USBOTG20_IRQHandler
        PUBWEAK  TRNG_IRQHandler
        PUBWEAK  UART6_IRQHandler
        PUBWEAK  UART7_IRQHandler
        PUBWEAK  EADC10_IRQHandler
        PUBWEAK  EADC11_IRQHandler
        PUBWEAK  EADC12_IRQHandler
        PUBWEAK  EADC13_IRQHandler
        PUBWEAK  CAN2_IRQHandler
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
QSPI0_IRQHandler
SPI0_IRQHandler
BRAKE0_IRQHandler
PWM0P0_IRQHandler
PWM0P1_IRQHandler
PWM0P2_IRQHandler
BRAKE1_IRQHandler
PWM1P0_IRQHandler
PWM1P1_IRQHandler
PWM1P2_IRQHandler
TMR0_IRQHandler
TMR1_IRQHandler
TMR2_IRQHandler
TMR3_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
PDMA_IRQHandler
DAC_IRQHandler
EADC00_IRQHandler
EADC01_IRQHandler
ACMP01_IRQHandler
EADC02_IRQHandler
EADC03_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
QSPI1_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
USBD_IRQHandler
OHCI_IRQHandler
USBOTG_IRQHandler
CAN0_IRQHandler
CAN1_IRQHandler
SC0_IRQHandler
SC1_IRQHandler
SC2_IRQHandler
SPI3_IRQHandler
SDH0_IRQHandler
USBD20_IRQHandler
EMAC_TX_IRQHandler
EMAC_RX_IRQHandler
I2S0_IRQHandler
OPA0_IRQHandler
CRYPTO_IRQHandler
GPG_IRQHandler
EINT6_IRQHandler
UART4_IRQHandler
UART5_IRQHandler
USCI0_IRQHandler
USCI1_IRQHandler
BPWM0_IRQHandler
BPWM1_IRQHandler
SPIM_IRQHandler
CCAP_IRQHandler
I2C2_IRQHandler
QEI0_IRQHandler
QEI1_IRQHandler
ECAP0_IRQHandler
ECAP1_IRQHandler
GPH_IRQHandler
EINT7_IRQHandler
SDH1_IRQHandler
EHCI_IRQHandler
USBOTG20_IRQHandler
TRNG_IRQHandler
UART6_IRQHandler
UART7_IRQHandler
EADC10_IRQHandler
EADC11_IRQHandler
EADC12_IRQHandler
EADC13_IRQHandler
CAN2_IRQHandler
Default_Handler
        B Default_Handler




        END
;/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
