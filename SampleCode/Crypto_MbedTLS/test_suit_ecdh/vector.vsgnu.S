;/*---------------------------------------------------------------------------------------------------------*/
;/* @copyright SPDX-License-Identifier: Apache-2.0                                                          */
;/* @copyright Copyright (C) 2024 Nuvoton Technology Corp. All rights reserved.                             */
;/*---------------------------------------------------------------------------------------------------------*/

	.section .rodata	
	.globl	VectorBase_ECDH
	.globl	VectorLimit_ECDH

	.align	4

	.text

VectorBase_ECDH:
    .incbin  "../../../test_suite_ecdh.data"
VectorLimit_ECDH:

    .space   4

    .end