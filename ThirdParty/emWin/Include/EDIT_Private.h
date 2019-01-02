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
File        : EDIT_Private.h
Purpose     : Internal header file
---------------------------END-OF-HEADER------------------------------
*/

#ifndef EDIT_PRIVATE_H
#define EDIT_PRIVATE_H

#include "EDIT.h"

#if GUI_WINSUPPORT

#include "WIDGET.h"

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define EDIT_REALLOC_SIZE  16

#ifndef EDIT_XOFF
  #define EDIT_XOFF        1
#endif

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct EDIT_Obj_struct EDIT_Obj;

typedef struct {
  int              Align;
  int              Border;
  const GUI_FONT * pFont;
  GUI_COLOR        aTextColor[3];
  GUI_COLOR        aBkColor[3];
} EDIT_PROPS;

struct EDIT_Obj_struct {
  WIDGET               Widget;
  WM_HMEM              hpText;
  I16                  MaxLen;
  U16                  BufferSize;
  I32                  Min, Max;        // Min max values as normalized floats (integers)
  U8                   NumDecs;         // Number of decimals
  I32                  CurrentValue;    // Current value
  int                  CursorPos;       // Cursor position. 0 means left most
  unsigned             SelSize;         // Number of selected characters
  U8                   EditMode;        // Insert or overwrite mode
  U8                   XSizeCursor;     // Size of cursor when working in insert mode
  U8                   Flags;
  tEDIT_AddKeyEx     * pfAddKeyEx;      // Handle key input
  tEDIT_UpdateBuffer * pfUpdateBuffer;  // Update textbuffer
  EDIT_PROPS           Props;
  WM_HTIMER            hTimer;
  U8                   MinMaxMode;
  int                  TimerPeriod;
};

/*********************************************************************
*
*       Macros for internal use
*
**********************************************************************
*/
#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  #define EDIT_INIT_ID(p) (p->Widget.DebugId = EDIT_ID)
#else
  #define EDIT_INIT_ID(p)
#endif

#if GUI_DEBUG_LEVEL >= GUI_DEBUG_LEVEL_CHECK_ALL
  EDIT_Obj * EDIT_LockH(EDIT_Handle h);
  #define EDIT_LOCK_H(h)   EDIT_LockH(h)
#else
  #define EDIT_LOCK_H(h)   (EDIT_Obj *)GUI_LOCK_H(h)
#endif

/*********************************************************************
*
*       Public data (internal defaults)
*
**********************************************************************
*/
extern EDIT_PROPS EDIT__DefaultProps;

/*********************************************************************
*
*       Public functions (internal)
*
**********************************************************************
*/
U16  EDIT__GetCurrentChar  (EDIT_Obj * pObj);
void EDIT__SetCursorPos    (EDIT_Handle hObj, int CursorPos);
void EDIT__SetValueUnsigned(EDIT_Handle hObj, I32 Value);

#endif // GUI_WINSUPPORT

#endif // EDIT_PRIVATE_H

/*************************** End of file ****************************/
