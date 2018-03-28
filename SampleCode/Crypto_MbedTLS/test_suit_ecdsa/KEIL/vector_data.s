;/*---------------------------------------------------------------------------------------------------------*/
;/*                                                                                                         */
;/* Copyright(c) 2010 Nuvoton Technology Corp. All rights reserved.                                         */
;/*                                                                                                         */
;/*---------------------------------------------------------------------------------------------------------*/


    AREA _image, DATA, READONLY

    EXPORT  VectorBase_ECDSA
    EXPORT  VectorLimit_ECDSA

    ALIGN   4
        
VectorBase_ECDSA
    INCBIN ..\test_suite_ecdsa.data
VectorLimit_ECDSA

    END