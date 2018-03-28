;/*---------------------------------------------------------------------------------------------------------*/
;/*                                                                                                         */
;/* Copyright(c) 2010 Nuvoton Technology Corp. All rights reserved.                                         */
;/*                                                                                                         */
;/*---------------------------------------------------------------------------------------------------------*/


    AREA _image, DATA, READONLY

    EXPORT  VectorBase_ECP
    EXPORT  VectorLimit_ECP

    ALIGN   4
        
VectorBase_ECP
    INCBIN ..\test_suite_ecp.data
VectorLimit_ECP

    END