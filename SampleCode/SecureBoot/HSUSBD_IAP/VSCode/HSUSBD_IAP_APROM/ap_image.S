/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright(c) 2024 Nuvoton Technology Corp. All rights reserved.                                         */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

    .section _image,"ax"
    .global loaderImage1Base
    .global loaderImage1Limit
    .align 4
	
loaderImage1Base:
    .incbin     BINFILE
loaderImage1Limit:
