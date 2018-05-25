;/**************************************************************************//**
; * @file     vector.s
; * @version  V1.00
; * @brief    Assembly code include test vector
; *
; *
; * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
; ******************************************************************************/


    AREA _image, DATA, READONLY

    EXPORT  VectorDataBase
    EXPORT  VectorDataLimit

    ALIGN   4
        
VectorDataBase
    INCBIN .\sha_test_vector
VectorDataLimit

    END