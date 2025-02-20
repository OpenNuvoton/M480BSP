;/*---------------------------------------------------------------------------------------------------------*/
;/* @copyright SPDX-License-Identifier: Apache-2.0                                                          */
;/* @copyright Copyright (C) 2024 Nuvoton Technology Corp. All rights reserved.                             */
;/*---------------------------------------------------------------------------------------------------------*/

	.section .rodata	
	.globl	VectorBase_CBC
	.globl	VectorLimit_CBC
	
	.globl	VectorBase_CFB
    .globl	VectorLimit_CFB

    .globl	VectorBase_ECB
    .globl	VectorLimit_ECB

	.align	4

	.text

VectorBase_CBC:
    .incbin  "../../../test_suite_aes.cbc.data"
VectorLimit_CBC:

VectorBase_CFB:
    .incbin  "../../../test_suite_aes.cfb.data"
VectorLimit_CFB:

VectorBase_ECB:
    .incbin  "../../../test_suite_aes.ecb.data"
VectorLimit_ECB:

    .space   4

    .end