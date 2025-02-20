;/*---------------------------------------------------------------------------------------------------------*/
;/* @copyright SPDX-License-Identifier: Apache-2.0                                                          */
;/* @copyright Copyright (C) 2024 Nuvoton Technology Corp. All rights reserved.                             */
;/*---------------------------------------------------------------------------------------------------------*/

	.section .rodata	
	.globl	VectorBase_DES
	.globl	VectorLimit_DES

	.align	4

	.text

VectorBase_DES:
    .incbin  "../../../test_suite_des.data"
VectorLimit_DES:

    .space   4

    .end