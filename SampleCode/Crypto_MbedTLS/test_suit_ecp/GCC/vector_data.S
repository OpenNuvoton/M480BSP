;/*---------------------------------------------------------------------------------------------------------*/
;/*                                                                                                         */
;/* Copyright(c) 2017 Nuvoton Technology Corp. All rights reserved.                                         */
;/*                                                                                                         */
;/*---------------------------------------------------------------------------------------------------------*/

	.syntax	unified
	.arch	armv7-m

	.globl	VectorBase_ECP
	.globl	VectorLimit_ECP

	.align	4
 
	.text
        
VectorBase_ECP:
    .incbin  "../../test_suite_ecp.data"
VectorLimit_ECP:
    .space   4

    .end
   
