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
File        : CHECKBOX_Private.h
Purpose     : CHECKBOX private header file
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef CHECKBOX_PRIVATE_H
#define CHECKBOX_PRIVATE_H

#include "WM.h"
#include "WIDGET.h"
#include "CHECKBOX.h"

#if GUI_WINSUPPORT

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#ifndef   CHECKBOX_BKCOLOR0_DEFAULT
  #define CHECKBOX_BKCOLOR0_DEFAULT 0x808080           /* Inactive color */
#endif

#ifndef   CHECKBOX_BKCOLOR1_DEFAULT
  #define CHECKBOX_BKCOLOR1_DEFAULT GUI_WHITE          /* Active color */
#endif

#ifndef   CHECKBOX_FGCOLOR0_DEFAULT
  #define CHECKBOX_FGCOLOR0_DEFAULT 0x101010
#endif

#ifndef   CHECKBOX_FGCOLOR1_DEFAULT
  #define CHECKBOX_FGCOLOR1_DEFAULT GUI_BLACK
#endif

#ifndef   CHECKBOX_DEFAULT_SIZE
  #define CHECKBOX_DEFAULT_SIZE          15
#endif

/*********************************************************************
*
*       Object definition
*
**********************************************************************
*/
typedef struct {
  unsigned              (* pfGetButtonSize)(void);
  WIDGET_DRAW_ITEM_FUNC  * pfDrawSkin;
} CHECKBOX_SKIN_PRIVATE;

typedef struct {
  const GUI_FONT      * pFont;
  GUI_COLOR             aBkColorBox[2]; /* Colors used to draw the box background */
  GUI_COLOR             BkColor;        /* Widget background color */
  GUI_COLOR             TextColor;
  GUI_COLOR             FocusColor;
  CHECKBOX_SKIN_PRIVATE SkinPrivate;
  I16                   Align;
  U8                    Spacing;
  const GUI_BITMAP    * apBm[6];
} CHECKBOX_PROPS;

typedef struct {
  WIDGET              Widget;
  CHECKBOX_PROPS      Props;
  WIDGET_SKIN const * pWidgetSkin;
  U8                  NumStates;
  U8                  CurrentState;
  WM_HMEM             hpText;
  U32                 ButtonSize;
} CHECKBOX_Obj;

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  #define CHECKBOX_INIT_ID(p) (p->Widget.DebugId = CHECKBOX_ID)
#else
  #define CHECKBOX_INIT_ID(p)
#endif

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  CHECKBOX_Obj * CHECKBOX_LockH(CHECKBOX_Handle h);
  #define CHECKBOX_LOCK_H(h)   CHECKBOX_LockH(h)
#else
  #define CHECKBOX_LOCK_H(h)   (CHECKBOX_Obj *)GUI_LOCK_H(h)
#endif

/*********************************************************************
*
*       Private functions
*
**********************************************************************
*/
unsigned CHECKBOX__GetButtonSize(void);

/*********************************************************************
*
*       Public data (internal defaults)
*
**********************************************************************
*/
extern CHECKBOX_PROPS      CHECKBOX__DefaultProps;

extern const WIDGET_SKIN   CHECKBOX__SkinClassic;
extern       WIDGET_SKIN   CHECKBOX__Skin;

extern WIDGET_SKIN const * CHECKBOX__pSkinDefault;

/*********************************************************************
*
*       Extern data
*
**********************************************************************
*/
extern const GUI_BITMAP    CHECKBOX__abmCheck[2];

#endif   /* GUI_WINSUPPORT */
#endif   /* CHECKBOX_PRIVATE_H */

/*************************** End of file ****************************/
