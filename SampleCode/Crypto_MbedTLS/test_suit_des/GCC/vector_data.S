;/*---------------------------------------------------------------------------------------------------------*/
;/*                                                                                                         */
;/* Copyright(c) 2017 Nuvoton Technology Corp. All rights reserved.                                         */
;/*                                                                                                         */
;/*---------------------------------------------------------------------------------------------------------*/

	.syntax	unified
	.arch	armv7-m

	.globl	VectorBase_DES
	.globl	VectorLimit_DES

	.align	4
 
	.text
        
VectorBase_DES:
    .incbin  "../../test_suite_des.data"
VectorLimit_DES:
    .space   4

    .end
   
