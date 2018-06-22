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
File        : SLIDER_Private.h
Purpose     : SLIDER private header file
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef SLIDER_PRIVATE_H
#define SLIDER_PRIVATE_H

#include "WM.h"
#include "WIDGET.h"
#include "SLIDER.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
//
// Flags
//
#define SLIDER_FLAG_DRAW_FOCUS_RECT (1 << 0)

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/
typedef struct {
  WIDGET_DRAW_ITEM_FUNC * pfDrawSkin;
} SLIDER_SKIN_PRIVATE;

typedef struct {
  U8                  Flags;
  GUI_COLOR           BkColor;
  GUI_COLOR           BarColor;
  GUI_COLOR           FocusColor;
  GUI_COLOR           TickColor;
  SLIDER_SKIN_PRIVATE SkinPrivate;
} SLIDER_PROPS;

typedef struct {
  WIDGET              Widget;
  SLIDER_PROPS        Props;
  WIDGET_SKIN const * pWidgetSkin;
  int                 NumTicks;
  int                 Max;
  int                 Min;
  int                 v;
  I16                 Width;
} SLIDER_Obj;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  #define SLIDER_INIT_ID(p) (p->Widget.DebugId = SLIDER_ID)
#else
  #define SLIDER_INIT_ID(p)
#endif

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  SLIDER_Obj * SLIDER_LockH(SLIDER_Handle h);
  #define SLIDER_LOCK_H(h)  SLIDER_LockH(h)
#else
  #define SLIDER_LOCK_H(h)  (SLIDER_Obj *)GUI_LOCK_H(h)
#endif

#ifndef   SLIDER_SUPPORT_TRANSPARENCY
  #define SLIDER_SUPPORT_TRANSPARENCY WM_SUPPORT_TRANSPARENCY
#endif

/*********************************************************************
*
*       Public data (internal defaults)
*
**********************************************************************
*/
extern       SLIDER_PROPS   SLIDER__DefaultProps;
extern const WIDGET_SKIN    SLIDER__SkinClassic;
extern       WIDGET_SKIN    SLIDER__Skin;
extern const WIDGET_SKIN  * SLIDER__pSkinDefault;

#endif  // GUI_WINSUPPORT
#endif  // SLIDER_PRIVATE_H

/*************************** End of file ****************************/
