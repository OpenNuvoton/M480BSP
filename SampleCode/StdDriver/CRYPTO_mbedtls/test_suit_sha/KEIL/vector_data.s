;/*---------------------------------------------------------------------------------------------------------*/
;/*                                                                                                         */
;/* Copyright(c) 2017 Nuvoton Technology Corp. All rights reserved.                                         */
;/*                                                                                                         */
;/*---------------------------------------------------------------------------------------------------------*/


    AREA _image, DATA, READONLY

    EXPORT  VectorBase_SHA
    EXPORT  VectorLimit_SHA

    ALIGN   4
        
VectorBase_SHA
    INCBIN ..\test_suite_shax.data
VectorLimit_SHA

    END