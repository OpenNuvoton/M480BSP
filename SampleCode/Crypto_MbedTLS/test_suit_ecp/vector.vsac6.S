;/*---------------------------------------------------------------------------------------------------------*/
;/* @copyright SPDX-License-Identifier: Apache-2.0                                                          */
;/* @copyright Copyright (C) 2024 Nuvoton Technology Corp. All rights reserved.                             */
;/*---------------------------------------------------------------------------------------------------------*/

	.section .rodata
	.globl	VectorBase_ECP
	.globl	VectorLimit_ECP

	.align	4

	.text

VectorBase_ECP:
    .incbin  "test_suite_ecp.data"
VectorLimit_ECP:

    .space   4

    .end