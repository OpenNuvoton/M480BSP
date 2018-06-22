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
File        : LCD_ConfDefaults.h
Purpose     : Valid LCD configuration and defaults
----------------------------------------------------------------------
*/

#ifndef LCD_CONFIG_DEFAULTS_H
#define LCD_CONFIG_DEFAULTS_H

#include "LCDConf.h"            /* Configuration header file */

/**********************************************************
*
*       Configuration defaults
*/
#ifndef   LCD_MIRROR_X
  #define LCD_MIRROR_X 0
#endif
#ifndef   LCD_MIRROR_Y
  #define LCD_MIRROR_Y 0
#endif
#ifndef   LCD_SWAP_XY
  #define LCD_SWAP_XY 0
#endif
#ifndef   LCD_FIRSTCOM0
  #define LCD_FIRSTCOM0 0
#endif
#ifndef   LCD_FIRSTSEG0
  #define LCD_FIRSTSEG0 0
#endif
#ifndef   LCD_SWAP_RB
  #define LCD_SWAP_RB 0
#endif
#ifndef   LCD_DISPLAY_INDEX
  #define LCD_DISPLAY_INDEX 0
#endif
#ifndef   LCD_ENDIAN_BIG
  #define LCD_ENDIAN_BIG 0
#endif
#ifndef   LCD_ALLOW_NON_OPTIMIZED_MODE
  #define LCD_ALLOW_NON_OPTIMIZED_MODE 1
#endif

#endif /* LCD_CONFIG_DEFAULTS_H */

/*************************** End of file ****************************/
