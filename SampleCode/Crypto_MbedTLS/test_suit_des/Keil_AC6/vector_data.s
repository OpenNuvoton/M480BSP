;/*---------------------------------------------------------------------------------------------------------*/
;/*                                                                                                         */
;/* Copyright(c) 2018 Nuvoton Technology Corp. All rights reserved.                                         */
;/*                                                                                                         */
;/*---------------------------------------------------------------------------------------------------------*/


    AREA _image, DATA, READONLY

    EXPORT  VectorBase_DES
    EXPORT  VectorLimit_DES

    ALIGN   4
        
VectorBase_DES
    INCBIN ..\test_suite_des.data
VectorLimit_DES

    END