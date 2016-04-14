;/*---------------------------------------------------------------------------------------------------------*/
;/*                                                                                                         */
;/* Copyright(c) 2010 Nuvoton Technology Corp. All rights reserved.                                         */
;/*                                                                                                         */
;/*---------------------------------------------------------------------------------------------------------*/


    AREA _image, DATA, READONLY

    EXPORT  VectorDataBase
    EXPORT  VectorDataLimit

    ALIGN   4
        
VectorDataBase
    INCBIN .\sha_test_vector
VectorDataLimit

    END