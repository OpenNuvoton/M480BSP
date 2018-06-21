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
File        : GUI_SetOrientation.h
Purpose     : Private include file for GUI_SetOrientation_xxx
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUI_SETORIENTATION_H
#define GUI_SETORIENTATION_H

#include "GUI_Private.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Use unique context identified
//
#define DRIVER_CONTEXT DRIVER_CONTEXT_ORIENTATION

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
/*********************************************************************
*
*       DRIVER_CONTEXT
*/
typedef struct DRIVER_CONTEXT DRIVER_CONTEXT;

struct DRIVER_CONTEXT {
  void (* pfLog2Phys)(DRIVER_CONTEXT * pContext, int x, int y, int * px_phys, int * py_phys);
  U8 * pData;
  int BytesPerPixel;
  int BytesPerLine;
  int Orientation;
  int xSize, ySize;
  int vxSize, vySize;
  int PixelOffset;
  const GUI_ORIENTATION_API * pDrawingAPI;
};

/*********************************************************************
*
*       Private interface
*
**********************************************************************
*/
void GUI__Sort(int * p0, int * p1);

#endif /* GUI_SETORIENTATION_H */

/*************************** End of file ****************************/
