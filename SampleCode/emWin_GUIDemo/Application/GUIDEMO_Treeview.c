/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2012  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.18 - Graphical user interface for embedded applications **
emWin is protected by international copyright laws.   Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with a license and should not be re-
distributed in any way. We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : GUIDEMO_Treeview.c
Purpose     : Treeview demo
----------------------------------------------------------------------
*/

#include "GUIDEMO.h"

#if (SHOW_GUIDEMO_TREEVIEW && GUI_WINSUPPORT)

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
enum {
  JOB_INC_SEL = 1,
  JOB_DEC_SEL,
  JOB_OPEN,
  JOB_CLOSE,
  JOB_SETIMAGE,
  JOB_SETROWMODE,
  JOB_HIDELINES,
  JOB_SHOWLINES
};

/*********************************************************************
*
*       ACTION_ITEM
*/
typedef struct {
  int          Delay;
  int          Job;
  const char * pDescription;
} ACTION_ITEM;

/*********************************************************************
*
*       SPRITE
*/
typedef struct {
  int                             xPos;       // X-position of sprite
  int                             yPos;       // Y-position of sprite
  int                             dx;         // X-step
  int                             dy;         // Y-step
  int                             NumImages;  // Number of images in apImages
  GUI_CONST_STORAGE GUI_BITMAP ** apImages;   // Pointer to images
  GUI_HSPRITE                     hSprite;    // Handle of sprite
  int                             Index;      // Index of currently used bitmap
} SPRITE;

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/
/*********************************************************************
*
*       _bmSmilie
*/
static const GUI_COLOR _ColorsSmilie[] = {
#if (GUI_USE_ARGB)
  0xFFFFFFFF, 0xFF000000, 0xFF70FF70
#else
  0xFFFFFF, 0x000000, 0x70FF70
#endif
};

static const GUI_LOGPALETTE _PalSmilie = {
  3,	// Number of entries
  1, 	// Has transparency
  &_ColorsSmilie[0]
};

static const unsigned char _acSmilie[] = {
  0x00, 0x55, 0x40, 0x00, 0x01, 0xAA, 0x90, 0x00,
  0x06, 0xAA, 0xA4, 0x00, 0x19, 0x6A, 0x59, 0x00,
  0x69, 0x6A, 0x5A, 0x40, 0x6A, 0xA6, 0xAA, 0x40,
  0x6A, 0xA6, 0xAA, 0x40, 0x6A, 0xA6, 0xAA, 0x40,
  0x6A, 0xAA, 0xAA, 0x40, 0x1A, 0x6A, 0x69, 0x00,
  0x06, 0x95, 0xA4, 0x00, 0x01, 0xAA, 0x90, 0x00,
  0x00, 0x55, 0x40, 0x00
};

static const GUI_BITMAP _bmSmilie = {
  13,          // XSize
  13,          // YSize
  4,           // BytesPerLine
  2,           // BitsPerPixel
  _acSmilie,   // Pointer to picture data (indices)
  &_PalSmilie  // Pointer to palette
};

/*********************************************************************
*
*       _bmBookOpen
*/
static GUI_CONST_STORAGE GUI_COLOR _ColorsBookOpen[] = {
#if (GUI_USE_ARGB)
  0xFFFF0000, 0xFFFFFFFF, 0xFF000000, 0xFF008000, 0xFF808080, 0xFFC0C0C0
#else
  0x0000FF, 0xFFFFFF, 0x000000, 0x008000, 0x808080, 0xC0C0C0
#endif
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalBookOpen = {
  6,	// Number of entries
  1, 	// Has transparency
  &_ColorsBookOpen[0]
};

static GUI_CONST_STORAGE unsigned char _acBookOpen[] = {
  0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x04, 0x54, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x23, 0x15, 0x40, 0x00, 0x04, 0x44, 0x00, 0x00,
  0x23, 0x11, 0x40, 0x04, 0x41, 0x14, 0x00, 0x00,
  0x23, 0x11, 0x54, 0x41, 0x11, 0x14, 0x22, 0x00,
  0x23, 0x11, 0x12, 0x51, 0x11, 0x14, 0x13, 0x20,
  0x23, 0x11, 0x12, 0x51, 0x11, 0x14, 0x13, 0x20,
  0x23, 0x11, 0x12, 0x51, 0x11, 0x14, 0x13, 0x20,
  0x23, 0x11, 0x12, 0x51, 0x11, 0x14, 0x13, 0x20,
  0x23, 0x11, 0x12, 0x51, 0x11, 0x14, 0x13, 0x20,
  0x23, 0x31, 0x12, 0x51, 0x11, 0x45, 0x13, 0x20,
  0x02, 0x33, 0x12, 0x51, 0x44, 0x51, 0x13, 0x20,
  0x00, 0x23, 0x12, 0x44, 0x51, 0x11, 0x13, 0x20,
  0x00, 0x02, 0x33, 0x33, 0x33, 0x33, 0x33, 0x20,
  0x00, 0x00, 0x22, 0x22, 0x22, 0x22, 0x22, 0x20
};

static GUI_CONST_STORAGE GUI_BITMAP _bmBookOpen = {
  15,            // XSize
  15,            // YSize
  8,             // BytesPerLine
  4,             // BitsPerPixel
  _acBookOpen,   // Pointer to picture data (indices)
  &_PalBookOpen  // Pointer to palette
};

/*********************************************************************
*
*       _bmBookClosed
*/
static GUI_CONST_STORAGE GUI_COLOR _ColorsBookClosed[] = {
#if (GUI_USE_ARGB)
     0xFFFF0000,0xFF008000,0xFF000000,0xFFC0C0C0
#else
     0x0000FF,0x008000,0x000000,0xC0C0C0
#endif
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalBookClosed = {
  4,	// number of entries
  1, 	// Has transparency
  &_ColorsBookClosed[0]
};

static GUI_CONST_STORAGE unsigned char _acBookClosed[] = {
  0x00, 0x02, 0x80, 0x00,
  0x00, 0x29, 0x60, 0x00,
  0x02, 0x95, 0x58, 0x00,
  0x29, 0x55, 0x56, 0x00,
  0x95, 0x55, 0x55, 0x80,
  0xA5, 0x55, 0x55, 0x60,
  0x99, 0x55, 0x55, 0x58,
  0x96, 0x55, 0x55, 0x5A,
  0x95, 0x95, 0x55, 0xAC,
  0x25, 0x65, 0x5A, 0xFC,
  0x09, 0x59, 0xAF, 0xFA,
  0x02, 0x56, 0xFF, 0xE8,
  0x00, 0x96, 0xFE, 0x80,
  0x00, 0x26, 0xE8, 0x00,
  0x00, 0x0A, 0x80, 0x00
};

static GUI_CONST_STORAGE GUI_BITMAP _bmBookClosed = {
  16,              // XSize
  15,              // YSize
  4,               // BytesPerLine
  2,               // BitsPerPixel
  _acBookClosed,   // Pointer to picture data (indices)
  &_PalBookClosed  // Pointer to palette
};

#if GUIDEMO_SHOW_SPRITES

/*********************************************************************
*
*       Dolphin bitmap arrays
*/
static GUI_CONST_STORAGE GUI_BITMAP * _apImages_0[] = {
  &bmDolphin_00,
  &bmDolphin_01,
  &bmDolphin_02,
  &bmDolphin_03,
  &bmDolphin_04,
};

static GUI_CONST_STORAGE GUI_BITMAP * _apImages_1[] = {
  &bmDolphin_10,
  &bmDolphin_11,
  &bmDolphin_12,
  &bmDolphin_13,
  &bmDolphin_14,
};

/*********************************************************************
*
*       Sprite array
*/
static SPRITE _aSprite[] = {
  { -90,  20, 10,  3, GUI_COUNTOF(_apImages_1), _apImages_1 },
  { 290, 150, -8, -2, GUI_COUNTOF(_apImages_0), _apImages_0 },
};

#endif

/*********************************************************************
*
*       _aAction
*/
static const ACTION_ITEM _aAction[] = {
  { 600, JOB_INC_SEL,    "Moving cursor..." },
  { 500, JOB_OPEN,       NULL },
  { 400, JOB_INC_SEL,    NULL },
  { 300, JOB_OPEN,       NULL },
  { 200, JOB_INC_SEL,    NULL },
  { 200, JOB_INC_SEL,    "Open and close nodes..." },
  { 200, JOB_INC_SEL,    NULL },
  { 200, JOB_INC_SEL,    NULL },
  { 200, JOB_OPEN,       NULL },
  { 200, JOB_INC_SEL,    NULL },
  { 200, JOB_INC_SEL,    NULL },
  { 200, JOB_INC_SEL,    NULL },
  { 200, JOB_INC_SEL,    NULL },
  { 200, JOB_OPEN,       NULL },
  { 900, JOB_SETROWMODE, "Change selection mode..." },
  { 900, JOB_DEC_SEL,    NULL },
  {  10, JOB_DEC_SEL,    NULL },
  {  10, JOB_DEC_SEL,    NULL },
  {  10, JOB_DEC_SEL,    NULL },
  {  10, JOB_DEC_SEL,    NULL },
  {  10, JOB_DEC_SEL,    NULL },
  {  10, JOB_DEC_SEL,    NULL },
  {  10, JOB_DEC_SEL,    NULL },
  {  10, JOB_DEC_SEL,    NULL },
  { 200, JOB_CLOSE,      NULL },
  { 200, JOB_OPEN,       NULL },
  { 200, JOB_CLOSE,      NULL },
  { 200, JOB_OPEN,       NULL },
  { 900, JOB_SETIMAGE,   "Setting images..." },
  { 100, JOB_INC_SEL,    NULL },
  { 100, JOB_INC_SEL,    NULL },
  { 100, JOB_SETIMAGE,   NULL },
  { 100, JOB_INC_SEL,    NULL },
  { 100, JOB_SETIMAGE,   NULL },
  { 100, JOB_INC_SEL,    NULL },
  { 100, JOB_SETIMAGE,   NULL },
  { 900, JOB_HIDELINES,  "Show/hide lines..." },
  { 200, JOB_SHOWLINES,  NULL },
  { 200, JOB_HIDELINES,  NULL },
  { 200, JOB_SHOWLINES,  NULL },
  { 200, JOB_HIDELINES,  NULL },
  { 200, JOB_SHOWLINES,  NULL },
  {1800, 0,              NULL },
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _MoveSprite
*/
#if GUIDEMO_SHOW_SPRITES
static void _MoveSprite(SPRITE * pSprite, int xMax, int yMax) {
  //
  // Set new index
  //
  pSprite->Index += 1;
  if (pSprite->Index >= pSprite->NumImages) {
    pSprite->Index = 0;
  }
  //
  // Adjust X-position
  //
  pSprite->xPos += pSprite->dx;
  if (pSprite->xPos > xMax) {
    pSprite->xPos = -(int)pSprite->apImages[pSprite->Index]->XSize;
  }
  if (pSprite->xPos < -(int)pSprite->apImages[pSprite->Index]->XSize) {
    pSprite->xPos = xMax;
  }
  //
  // Adjust Y-position
  //
  pSprite->yPos += pSprite->dy;
  if (pSprite->yPos < 0) {
    pSprite->dy = -pSprite->dy;
  }
  if (pSprite->yPos > (yMax - pSprite->apImages[pSprite->Index]->YSize)) {
    pSprite->dy = -pSprite->dy;
  }
  //
  // Change sprite
  //
  GUI_SPRITE_SetBitmapAndPosition(pSprite->hSprite, pSprite->apImages[pSprite->Index], pSprite->xPos, pSprite->yPos);
}
#endif

/*********************************************************************
*
*       _InitTreeview
*
*  Function description
*    Adds some data to the treeview widget
*/
static void _InitTreeview(WM_HWIN hTree) {
  TREEVIEW_ITEM_Handle hItem, hNode;
  hNode = TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_NODE, 0,     0,                           "Local disk");
  hItem = TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_NODE, hNode, TREEVIEW_INSERT_FIRST_CHILD, "Pictures");
          TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_NODE, hItem, TREEVIEW_INSERT_BELOW,       "Movies");
  hNode = TREEVIEW_GetItem(hTree, 0,     TREEVIEW_GET_FIRST);
  hNode = TREEVIEW_GetItem(hTree, hNode, TREEVIEW_GET_FIRST_CHILD);
  hItem = TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_NODE, hNode, TREEVIEW_INSERT_FIRST_CHILD, "BMP");
  hItem = TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_NODE, hItem, TREEVIEW_INSERT_BELOW,       "GIF");
  hItem = TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_NODE, hItem, TREEVIEW_INSERT_BELOW,       "JPEG");
          TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_NODE, hItem, TREEVIEW_INSERT_BELOW,       "PNG");
  hNode = TREEVIEW_GetItem(hTree, hNode, TREEVIEW_GET_FIRST_CHILD);
  hItem = TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_LEAF, hNode, TREEVIEW_INSERT_FIRST_CHILD, "Cat.bmp");
  hItem = TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_LEAF, hItem, TREEVIEW_INSERT_BELOW,       "Dog.bmp");
          TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_LEAF, hItem, TREEVIEW_INSERT_BELOW,       "Frog.bmp");
  hNode = TREEVIEW_GetItem(hTree, hNode, TREEVIEW_GET_NEXT_SIBLING);
  hItem = TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_LEAF, hNode, TREEVIEW_INSERT_FIRST_CHILD, "Flowchart.gif");
  hItem = TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_LEAF, hItem, TREEVIEW_INSERT_BELOW,       "Projects.gif");
          TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_LEAF, hItem, TREEVIEW_INSERT_BELOW,       "Interlaced.gif");
  hNode = TREEVIEW_GetItem(hTree, hNode, TREEVIEW_GET_NEXT_SIBLING);
  hItem = TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_LEAF, hNode, TREEVIEW_INSERT_FIRST_CHILD, "Tree.jpeg");
  hItem = TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_LEAF, hItem, TREEVIEW_INSERT_BELOW,       "Joerg.jpeg");
          TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_LEAF, hItem, TREEVIEW_INSERT_BELOW,       "Paul.jpeg");
  hNode = TREEVIEW_GetItem(hTree, hNode, TREEVIEW_GET_NEXT_SIBLING);
          TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_LEAF, hNode, TREEVIEW_INSERT_FIRST_CHILD, "Parrot.png");
  hNode = TREEVIEW_GetItem(hTree, hNode, TREEVIEW_GET_PARENT);
  hNode = TREEVIEW_GetItem(hTree, hNode, TREEVIEW_GET_NEXT_SIBLING);
  hItem = TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_LEAF, hNode, TREEVIEW_INSERT_FIRST_CHILD, "Smilie.gif");
          TREEVIEW_InsertItem(hTree, TREEVIEW_ITEM_TYPE_LEAF, hItem, TREEVIEW_INSERT_BELOW,       "Cats.gif");
  TREEVIEW_SetAutoScrollH(hTree, 1);
  TREEVIEW_SetAutoScrollV(hTree, 1);
  TREEVIEW_ITEM_Expand(TREEVIEW_GetItem(hTree, 0, TREEVIEW_GET_FIRST));
  WM_SetFocus(hTree);
}

/*********************************************************************
*
*       _Action
*
*  Function description
*    Does some action with the treeview widget
*/
static void _Action(WM_HWIN hTree, int xSize, int ySize) {
  TREEVIEW_ITEM_Handle hItem;
  TREEVIEW_ITEM_INFO   Info;
  I32                  TimeNext;
  unsigned             Index;
  #if GUIDEMO_SHOW_SPRITES
    unsigned             i;
  #else
    GUI_USE_PARA(xSize);
    GUI_USE_PARA(ySize);
  #endif

  Index = 0;
  do {
    TimeNext = GUIDEMO_GetTime() + _aAction[Index].Delay;
    if (_aAction[Index].pDescription) {
      GUIDEMO_SetInfoText(_aAction[Index].pDescription);
    }
    do {
      if (GUIDEMO_CheckCancel()) {
        return;
      }
      #if GUIDEMO_SHOW_SPRITES
        if (GUIDEMO_GetConfFlag(GUIDEMO_CF_SHOW_SPRITES)) {
          for (i = 0; i < GUI_COUNTOF(_aSprite); i++) {
            _MoveSprite(&_aSprite[i], xSize, ySize);
          }
        }
      #endif
      GUI_Delay(100);
    } while (GUIDEMO_GetTime() < TimeNext);
    hItem = TREEVIEW_GetSel(hTree);
    TREEVIEW_ITEM_GetInfo(hItem, &Info);
    switch (_aAction[Index].Job) {
    case JOB_HIDELINES:
      TREEVIEW_SetHasLines(hTree, 0);
      break;
    case JOB_SHOWLINES:
      TREEVIEW_SetHasLines(hTree, 1);
      break;
    case JOB_SETROWMODE:
      TREEVIEW_SetSelMode(hTree, TREEVIEW_SELMODE_ROW);
      break;
    case JOB_SETIMAGE:
      if (Info.IsNode) {
        if (Info.IsExpanded) {
          TREEVIEW_ITEM_SetImage(hItem, TREEVIEW_BI_OPEN, &_bmBookOpen);
        } else {
          TREEVIEW_ITEM_SetImage(hItem, TREEVIEW_BI_CLOSED, &_bmBookClosed);
        }
      } else {
        TREEVIEW_ITEM_SetImage(hItem, TREEVIEW_BI_LEAF, &_bmSmilie);
      }
      break;
    case JOB_INC_SEL:
      TREEVIEW_IncSel(hTree);
      break;
    case JOB_DEC_SEL:
      TREEVIEW_DecSel(hTree);
      break;
    case JOB_OPEN:
      TREEVIEW_ITEM_Expand(hItem);
      break;
    case JOB_CLOSE:
      TREEVIEW_ITEM_Collapse(hItem);
      break;
    }
  } while (++Index < GUI_COUNTOF(_aAction));
}

/*********************************************************************
*
*       _cbDialog
*
*  Function description
*    Callback of dialog
*/
static void _cbDialog(WM_MESSAGE * pMsg) {
  WM_HWIN hItem;
  WM_HWIN hDlg;

  hDlg = pMsg->hWin;
  switch (pMsg->MsgId) {
  case WM_INIT_DIALOG:
    hItem = WM_GetDialogItem(hDlg, GUI_ID_TREEVIEW0);
    _InitTreeview(hItem);
    break;
  case WM_PAINT:
    break;
  }
}

/*********************************************************************
*
*       _DemoTreeview
*
*  Function description
*    Creates the dialog and starts the demo
*/
static void _DemoTreeview(void) {
  GUI_WIDGET_CREATE_INFO aCreate[] = {
    { FRAMEWIN_CreateIndirect,  "Explorer", 0,                0, 0, 0, 0 },
    { TREEVIEW_CreateIndirect,  NULL,       GUI_ID_TREEVIEW0, 0, 0, 0, 0 },
  };
  #if GUIDEMO_SHOW_SPRITES
    unsigned i;
  #endif
  WM_HWIN  hClient;
  WM_HWIN  hTree;
  WM_HWIN  hWin;
  int      xSizeClient;
  int      ySizeClient;
  int      xSize;
  int      ySize;

  xSize            = LCD_GetXSize();
  ySize            = LCD_GetYSize();
  aCreate[0].xSize = xSize / 2;
  aCreate[0].ySize = ySize;
  aCreate[1].xSize = xSize / 2;
  aCreate[1].ySize = ySize;
  hWin             = GUI_CreateDialogBox(aCreate, GUI_COUNTOF(aCreate), _cbDialog, WM_HBKWIN, 0, 0);
  hClient          = WM_GetClientWindow(hWin);
  xSizeClient      = WM_GetWindowSizeX(hClient);
  ySizeClient      = WM_GetWindowSizeY(hClient);
  hTree            = WM_GetDialogItem(hWin, GUI_ID_TREEVIEW0);
  WM_SetSize(hTree, xSizeClient, ySizeClient);
  //
  // Create the sprites
  //
  #if GUIDEMO_SHOW_SPRITES
    if (GUIDEMO_GetConfFlag(GUIDEMO_CF_SHOW_SPRITES)) {
      for (i = 0; i < GUI_COUNTOF(_aSprite); i++) {
        _aSprite[i].hSprite = GUI_SPRITE_Create(_aSprite[i].apImages[0], _aSprite[i].xPos, _aSprite[i].yPos);
      }
    }
  #endif
  _Action(hTree, xSize, ySize);
  //
  // Delete the sprites
  //
  #if GUIDEMO_SHOW_SPRITES
    if (GUIDEMO_GetConfFlag(GUIDEMO_CF_SHOW_SPRITES)) {
      for (i = 0; i < GUI_COUNTOF(_aSprite); i++) {
        GUI_SPRITE_Delete(_aSprite[i].hSprite);
      }
    }
  #endif
  WM_DeleteWindow(hWin);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUIDEMO_Treeview
*/
void GUIDEMO_Treeview(void) {
  GUIDEMO_ConfigureDemo("Treeview widget", "Shows a hierarchical view of\nthe files in a directory and\nsome moving sprites", GUIDEMO_SHOW_INFO | GUIDEMO_SHOW_CONTROL);
  GUIDEMO_DrawBk();
  _DemoTreeview();
  GUIDEMO_NotifyStartNext();
}

#else

void GUIDEMO_Treeview_C(void);
void GUIDEMO_Treeview_C(void) {}

#endif  // SHOW_GUIDEMO_TREEVIEW && GUI_WINSUPPORT

/*************************** End of file ****************************/
