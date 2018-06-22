/*********************************************************************
*                 SEGGER Software GmbH                               *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2018  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.48 - Graphical user interface for embedded applications **
All  Intellectual Property rights in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product. This file may
only be used in accordance with the following terms:

The  software has  been licensed by SEGGER Software GmbH to Nuvoton Technology Corporationat the address: No. 4, Creation Rd. III, Hsinchu Science Park, Taiwan
for the purposes  of  creating  libraries  for its 
Arm Cortex-M and  Arm9 32-bit microcontrollers, commercialized and distributed by Nuvoton Technology Corporation
under  the terms and conditions  of  an  End  User  
License  Agreement  supplied  with  the libraries.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
Licensing information
Licensor:                 SEGGER Software GmbH
Licensed to:              Nuvoton Technology Corporation, No. 4, Creation Rd. III, Hsinchu Science Park, 30077 Hsinchu City, Taiwan
Licensed SEGGER software: emWin
License number:           GUI-00735
License model:            emWin License Agreement, signed February 27, 2018
Licensed platform:        Cortex-M and ARM9 32-bit series microcontroller designed and manufactured by or for Nuvoton Technology Corporation
----------------------------------------------------------------------
Support and Update Agreement (SUA)
SUA period:               2018-03-26 - 2019-03-27
Contact to extend SUA:    sales@segger.com
----------------------------------------------------------------------
File        : GUI_FontIntern.h
Purpose     : Internal declarations used in font files
---------------------------END-OF-HEADER------------------------------

Attention : Do not modify this file ! If you do, you will not
            be able do update to a later GUI version !

*/


#ifndef  GUI_FONTINTERN_H    /* Guard against multiple inclusion */
#define  GUI_FONTINTERN_H

#include "GUI.h"

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font8ASCII_Prop;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_FontF8x13_ASCII_Prop1;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_FontF8x15B_ASCII_Prop1;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font10S_ASCII_FontProp1;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font10ASCIIProp1;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font13ASCII_Prop1;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font13B_ASCII_Prop1;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font13H_ASCII_Prop1;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font13HB_ASCII_Prop1;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font16_1_FontProp1;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font16ASCIIProp1;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font16B_ASCII_Prop1;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font20_ASCII_Prop1;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font20B_ASCII_Prop1;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font24_ASCII_Prop1;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font24B_ASCII_Prop1;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font32_ASCII_Prop1;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font32B_ASCII_Prop1;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_FontComic18B_ASCII_Prop1;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_FontComic24B_ASCII_Prop1;

extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font6x8ASCII_Prop0;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font8x16ASCII_Prop0;
extern GUI_CONST_STORAGE GUI_FONT_PROP GUI_Font8x8ASCII_Prop0;

extern GUI_CONST_STORAGE GUI_CHARINFO GUI_Font16_HK_CharInfo[169];

#if defined(__cplusplus)
  }
#endif


#endif   /* Guard against multiple inclusion */

/*************************** End of file ****************************/
