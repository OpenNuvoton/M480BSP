;/*---------------------------------------------------------------------------------------------------------*/
;/*                                                                                                         */
;/* Copyright(c) 2017 Nuvoton Technology Corp. All rights reserved.                                         */
;/*                                                                                                         */
;/*---------------------------------------------------------------------------------------------------------*/


	.syntax	unified
	.arch	armv7-m

	.globl	VectorDataBase
	.globl	VectorDataLimit

	.align	4
 
	.text
        
VectorDataBase:
    .incbin  "../../HMAC_fips198a.rsp"
VectorDataLimit:
    .space   4
    
    .end
    
    