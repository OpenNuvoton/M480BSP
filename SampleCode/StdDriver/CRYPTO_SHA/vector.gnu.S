;/**************************************************************************//**
; * @file     vector.s
; * @version  V1.00
; * @brief    Assembly code include test vector
; *
; *
; * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
; ******************************************************************************/

    .syntax unified
    .arch   armv7-m

    .globl  VectorDataBase
    .globl  VectorDataLimit

    .align  4

    .text

VectorDataBase:
    .incbin  "../../sha_test_vector"
VectorDataLimit:
    .space   4

    .end

