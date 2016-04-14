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
;    INCBIN .\HMAC_NIST.rsp
    INCBIN .\HMAC_fips198a.rsp
VectorDataLimit

    END