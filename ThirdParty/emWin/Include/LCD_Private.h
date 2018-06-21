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
File        : LCD_Private.h
Purpose     : To be used only by the display drivers
----------------------------------------------------------------------
*/

#ifndef LCD_Private_H
#define LCD_Private_H

#include "LCDConf.h"
#include "LCD_Protected.h"
#include "GUI.h"

/*********************************************************************
*
*       API functions
*/
extern const struct tLCDDEV_APIList_struct * /* const */ LCD_aAPI[GUI_NUM_LAYERS];

/*********************************************************************
*
*       Support for Segment/COMLUTs
*/
#define LCD_TYPE_SEGTRANS U16
#define LCD_TYPE_COMTRANS U16

#ifdef LCD_LUT_COM
  extern LCD_TYPE_COMTRANS LCD__aLine2Com0[LCD_YSIZE];
#endif

#ifdef LCD_LUT_SEG
  extern LCD_TYPE_COMTRANS LCD__aCol2Seg0[LCD_XSIZE];
#endif

/*********************************************************************
*
*       Support for multiple display controllers
*/
#define DECLARE_PROTOTYPES(DISTX) \
  void     LCD_##DISTX##_SetPixelIndex(int x, int y, int PixelIndex); \
  unsigned LCD_##DISTX##_GetPixelIndex(int x, int y); \
  void     LCD_##DISTX##_XorPixel     (int x, int y); \
  void     LCD_##DISTX##_DrawHLine    (int x0, int y,  int x1); \
  void     LCD_##DISTX##_DrawVLine    (int x, int y0,  int y1); \
  void     LCD_##DISTX##_FillRect     (int x0, int y0, int x1, int y1); \
  void     LCD_##DISTX##_DrawBitmap   (int x0, int y0, int xsize, int ysize, int BitsPerPixel, int BytesPerLine,  const U8 * pData, int Diff, const LCD_PIXELINDEX * pTrans); \
  void     LCD_##DISTX##_SetOrg       (int x, int y); \
  void     LCD_##DISTX##_On           (void); \
  void     LCD_##DISTX##_Off          (void); \
  int      LCD_##DISTX##_Init         (void); \
  void     LCD_##DISTX##_SetLUTEntry  (U8 Pos, LCD_COLOR Color); \
  void   * LCD_##DISTX##_GetDevFunc   (int Index); \
  void     LCD_##DISTX##_ReInit       (void)
    
DECLARE_PROTOTYPES(DIST0);
DECLARE_PROTOTYPES(DIST1);
DECLARE_PROTOTYPES(DIST2);
DECLARE_PROTOTYPES(DIST3);

#endif /* Avoid multiple inclusion */

/*************************** End of file ****************************/
