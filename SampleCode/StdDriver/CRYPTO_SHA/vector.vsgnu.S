;/*---------------------------------------------------------------------------------------------------------*/
;/* @copyright SPDX-License-Identifier: Apache-2.0                                                          */
;/* @copyright Copyright (C) 2024 Nuvoton Technology Corp. All rights reserved.                             */
;/*---------------------------------------------------------------------------------------------------------*/

	.section .rodata
	.globl	VectorDataBase
	.globl	VectorDataLimit

	.align	4

	.text

VectorDataBase:
    .incbin  "../../../sha_test_vector"
VectorDataLimit:
    .space   4

    .end