;/*---------------------------------------------------------------------------------------------------------*/
;/*                                                                                                         */
;/* Copyright(c) 2017 Nuvoton Technology Corp. All rights reserved.                                         */
;/*                                                                                                         */
;/*---------------------------------------------------------------------------------------------------------*/

	.syntax	unified
	.arch	armv7-m

	.globl	VectorBase_ECDH
	.globl	VectorLimit_ECDH

	.align	4
 
	.text
        
VectorBase_ECDH:
    .incbin  "../../test_suite_ecdh.data"
VectorLimit_ECDH:
    .space   4

    .end
   
