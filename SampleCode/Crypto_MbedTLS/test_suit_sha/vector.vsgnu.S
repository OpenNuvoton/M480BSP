;/*---------------------------------------------------------------------------------------------------------*/
;/* @copyright SPDX-License-Identifier: Apache-2.0                                                          */
;/* @copyright Copyright (C) 2024 Nuvoton Technology Corp. All rights reserved.                             */
;/*---------------------------------------------------------------------------------------------------------*/

	.section .rodata	
	.globl	VectorBase_SHA
	.globl	VectorLimit_SHA

	.align	4

	.text

VectorBase_SHA:
    .incbin  "../../../test_suite_shax.data"
VectorLimit_SHA:

    .space   4

    .end