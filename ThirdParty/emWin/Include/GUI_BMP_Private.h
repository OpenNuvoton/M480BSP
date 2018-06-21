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
File        : GUI_BMP_Private.h
Purpose     : Private header file for GUI_BMP... functions
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUI_BMP_PRIVATE_H
#define GUI_BMP_PRIVATE_H

#include "GUI_Private.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define BI_RGB       0
#define BI_RLE8      1
#define BI_RLE4      2
#define BI_BITFIELDS 3

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
//
// Default parameter structure for reading data from memory
//
typedef struct {
  const U8 * pFileData;
} GUI_BMP_PARAM;

//
// Context structure for getting stdio input
//
typedef struct {
  GUI_GET_DATA_FUNC * pfGetData; // Function pointer
  U32                 Off;       // Data pointer
  void              * pParam;    // Parameter pointer passed to function
} GUI_BMP_CONTEXT;

//
// Parameter structure for passing several required variables to the
// functions _DrawLine_RGB() and _DrawLine_ARGB() (in GUI_BMP_EnableAlpha.c).
//
typedef struct {
  const U8            * pSrc;           // Pointer to data
  I32                   xSrc;           // Used to read data
  int                   ySrc;           // Used to read data
  I32                   xSize;
  U32                   BytesPerPixel;
  tLCDDEV_Color2Index * pfColor2Index;
  tLCDDEV_Index2Color * pfIndex2Color;  // Used to manage bitfield conversion
  LCD_API_NEXT_PIXEL  * pNextPixel_API;
  int                   x0;             // Used to draw data
  int                   y0;             // Used to draw data
  int                   x1;             // Used to draw data
  int                   y1;             // Used to draw data
} GUI_DRAWLINE_INFO;

/*********************************************************************
*
*       Interface
*
**********************************************************************
*/
int GUI_BMP__GetData    (void * p, const U8 ** ppData, unsigned NumBytesReq, U32 Off);
int GUI_BMP__Init       (GUI_BMP_CONTEXT * pContext, I32 * pWidth, I32 * pHeight, U16 * pBitCount, int * pNumColors, int * pCompression);
int GUI_BMP__ReadData   (GUI_BMP_CONTEXT * pContext, int NumBytes, const U8 ** ppData, unsigned StartOfFile);
int GUI_BMP__ReadPalette(GUI_BMP_CONTEXT * pContext, int NumColors);

#endif /* GUI_BMP_PRIVATE_H */

/*************************** End of file ****************************/
