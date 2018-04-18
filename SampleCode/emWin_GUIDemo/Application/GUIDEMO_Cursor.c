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

** emWin V5.46 - Graphical user interface for embedded applications **
All  Intellectual Property rights in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product. This file may
only be used in accordance with the following terms:

The  software has  been licensed by SEGGER Software GmbH to Nuvoton Technology Corporation
at the address: No. 4, Creation Rd. III, Hsinchu Science Park, Taiwan
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
File        : GUIDEMO_Cursor.c
Purpose     : shows Cursor-API
----------------------------------------------------------------------
*/

#include "GUIDEMO.h"

#if (SHOW_GUIDEMO_CURSOR && GUI_SUPPORT_CURSOR)

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define NUM_CURSORS 3
#define XMAX        28

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
typedef struct {
  const GUI_CURSOR  * pCursor;
  char                Size;
} CURSOR_INFO;

typedef struct {
  CURSOR_INFO   aCursor[NUM_CURSORS];
  const char        * pType;
} CURSORTYPE_INFO;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
static const CURSORTYPE_INFO _CursorArrow = {
  {
    {&GUI_CursorArrowS, 'S'},
    {&GUI_CursorArrowM, 'M'},
  #if (NUM_CURSORS == 3)
    {&GUI_CursorArrowL, 'L'},
  },
  "arrow cursors"
  #else
  },
  "arrow\ncursors"
  #endif
};

static const CURSORTYPE_INFO _CursorArrowI = {
  {
    {&GUI_CursorArrowSI, 'S'},
    {&GUI_CursorArrowMI, 'M'},
  #if (NUM_CURSORS == 3)
    {&GUI_CursorArrowLI, 'L'},
  },
  "inverted arrow cursors"
  #else
  },
  "inverted\narrow cursors"
  #endif
};

static const CURSORTYPE_INFO _CursorCross = {
  {
    {&GUI_CursorCrossS, 'S'},
    {&GUI_CursorCrossM, 'M'},
  #if (NUM_CURSORS == 3)
    {&GUI_CursorCrossL, 'L'},
  },
  "cross cursors"
  #else
  },
  "cross\ncursors"
  #endif
};

static const CURSORTYPE_INFO _CursorCrossI = {
  {
    {&GUI_CursorCrossSI, 'S'},
    {&GUI_CursorCrossMI, 'M'},
  #if (NUM_CURSORS == 3)
    {&GUI_CursorCrossLI, 'L'},
  },
  "inverted cross cursors"
  #else
  },
  "inverted\ncross cursors"
  #endif
};

static int _ScreenX0;
static int _ScreenY0;

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _ShowCursorType
*/
static void _ShowCursorType(const CURSORTYPE_INFO* pCursorType, int x0, int y0) {
  const GUI_CURSOR * pCursor;
  char               Char;
  int                yMax;
  int                yHot;
  int                i;
  int                x;
  int                y;

  yMax = 0;
  yHot = 0;
  //
  // Calculate height and width of biggest cursor
  //
  for (i = 0; i < NUM_CURSORS; i++) {
    pCursor = pCursorType->aCursor[i].pCursor;
    if (pCursor->pBitmap->YSize > yMax) {
      yMax = pCursor->pBitmap->YSize;
      yHot = pCursor->yHot;
    }
  }
  GUI_SetFont(&GUI_FontRounded16);
  #if (NUM_CURSORS != 3)
    GUI_SetLBorder(x0);
  #endif
  GUI_DispStringAt(pCursorType->pType, x0, y0);
  y0 += GUI_GetFontDistY() + 1;
  GUI_SetFont(&GUI_Font13B_ASCII);
  for (i = 0; i < NUM_CURSORS; i++) {
    pCursor = pCursorType->aCursor[i].pCursor;
    Char    = pCursorType->aCursor[i].Size;
    y       = y0 + yHot - pCursor->yHot;
    x       = ((pCursor->pBitmap->XSize - GUI_GetCharDistX(Char)) / 2);
    GUI_DrawBitmap(pCursor->pBitmap, x0 + XMAX * i + 5,     y);
    GUI_DispCharAt(Char,             x0 + XMAX * i + 5 + x, y0 + yMax + 2);
  }
}

/*********************************************************************
*
*       _DispCursor
*/
static void _DispCursor(void) {
  int xSize;
  int ySize;

  xSize     = LCD_GetXSize();
  ySize     = LCD_GetYSize();
  _ScreenX0 = (xSize - XSIZE_MIN) / 2;
  _ScreenY0 = (ySize - YSIZE_MIN) / 2;
  GUIDEMO_DrawBk();
  GUI_SetTextMode(GUI_TM_TRANS);
  GUI_SetFont(&GUI_FontRounded22);
  GUI_DispStringHCenterAt("Available cursors", xSize / 2, 12);
  //
  // Display the cursors
  //
  _ShowCursorType(&_CursorArrow,  _ScreenX0 + 20,  _ScreenY0 + 50);
  _ShowCursorType(&_CursorCross,  _ScreenX0 + 20,  _ScreenY0 + 120);
  _ShowCursorType(&_CursorArrowI, _ScreenX0 + 140, _ScreenY0 + 50);
  _ShowCursorType(&_CursorCrossI, _ScreenX0 + 140, _ScreenY0 + 120);
  GUIDEMO_Wait(4000);
  GUI_CURSOR_Select(&GUI_CursorArrowM);
  GUI_CURSOR_Hide();
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUIDEMO_Cursor
*/
void GUIDEMO_Cursor(void) {
  GUIDEMO_ConfigureDemo("Cursor", "emWin supports\nsoftware cursors", GUIDEMO_SHOW_CURSOR | GUIDEMO_SHOW_CONTROL);
  _DispCursor();
}

#else

void GUIDEMO_Cursor_C(void);
void GUIDEMO_Cursor_C(void) {}

#endif  // SHOW_GUIDEMO_CURSOR && GUI_SUPPORT_CURSOR

/*************************** End of file ****************************/
