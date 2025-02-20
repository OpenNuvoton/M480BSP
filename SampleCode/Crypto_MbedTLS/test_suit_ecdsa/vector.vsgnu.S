;/*---------------------------------------------------------------------------------------------------------*/
;/* @copyright SPDX-License-Identifier: Apache-2.0                                                          */
;/* @copyright Copyright (C) 2024 Nuvoton Technology Corp. All rights reserved.                             */
;/*---------------------------------------------------------------------------------------------------------*/

	.section .rodata	
	.globl	VectorBase_ECDSA
	.globl	VectorLimit_ECDSA

	.align	4

	.text

VectorBase_ECDSA:
    .incbin  "../../../test_suite_ecdsa.data"
VectorLimit_ECDSA:

    .space   4

    .end