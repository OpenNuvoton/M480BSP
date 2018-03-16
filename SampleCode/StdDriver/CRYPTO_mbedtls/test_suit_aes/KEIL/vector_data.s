;/*---------------------------------------------------------------------------------------------------------*/
;/*                                                                                                         */
;/* Copyright(c) 2018 Nuvoton Technology Corp. All rights reserved.                                         */
;/*                                                                                                         */
;/*---------------------------------------------------------------------------------------------------------*/


    AREA _image, DATA, READONLY

    EXPORT  VectorBase_CBC
    EXPORT  VectorLimit_CBC

    EXPORT  VectorBase_CFB
    EXPORT  VectorLimit_CFB

    EXPORT  VectorBase_ECB
    EXPORT  VectorLimit_ECB

    ALIGN   4
        
VectorBase_CBC
    INCBIN ..\test_suite_aes.cbc.data
VectorLimit_CBC

VectorBase_CFB
    INCBIN ..\test_suite_aes.cfb.data
VectorLimit_CFB

VectorBase_ECB
    INCBIN ..\test_suite_aes.ecb.data
VectorLimit_ECB

    END