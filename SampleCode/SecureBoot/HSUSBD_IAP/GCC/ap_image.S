/****************************************************************************//**
 * @file     ap_image.S
 * @version  V1.00
 * @brief    AP image include file
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/


    .syntax unified
    .arch   armv7-m

    .globl  loaderImage1Base
    .globl  loaderImage1Limit

    .align  4

    .text

loaderImage1Base:
    .incbin  "../../fwupdate_ld_iap.bin"
loaderImage1Limit:
    .space   4

    .end

