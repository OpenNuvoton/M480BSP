;/*---------------------------------------------------------------------------------------------------------*/
;/*                                                                                                         */
;/* Copyright(c) 2010 Nuvoton Technology Corp. All rights reserved.                                         */
;/*                                                                                                         */
;/*---------------------------------------------------------------------------------------------------------*/


    AREA _image, DATA, READONLY

    EXPORT  VectorBase_ECDH
    EXPORT  VectorLimit_ECDH

    ALIGN   4
        
VectorBase_ECDH
    INCBIN ..\test_suite_ecdh.data
VectorLimit_ECDH

    END