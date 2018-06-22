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
File        : CHOOSEFILE.h
Purpose     : File dialog interface
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef CHOOSEFILE_H
#define CHOOSEFILE_H

#include "WM.h"

#if GUI_WINSUPPORT

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       Defines
*
**********************************************************************
*/
#define CHOOSEFILE_FINDFIRST 0
#define CHOOSEFILE_FINDNEXT  1

#define CHOOSEFILE_FLAG_DIRECTORY (1 << 0)

#ifndef   CHOOSEFILE_MAXLEN
  #define CHOOSEFILE_MAXLEN 256
#endif

#define CHOOSEFILE_BI_CANCEL 0
#define CHOOSEFILE_BI_OK     1
#define CHOOSEFILE_BI_UP     2

/*********************************************************************
*
*       Types
*
**********************************************************************
*/
/*********************************************************************
*
*       CHOOSEFILE_INFO
*/
typedef struct CHOOSEFILE_INFO CHOOSEFILE_INFO;

struct CHOOSEFILE_INFO {
  int               Cmd;                                 // Command for GetData() function
  int               Id;                                  // Id of pressed button (for internal use only)
  const char      * pMask;                               // Mask to be used for searching files
  char            * pName;                               // (for internal use only)
  char            * pExt;                                // (for internal use only)
  char            * pAttrib;                             // (for internal use only)
  WM_TOOLTIP_HANDLE hToolTip;                            // (for internal use only)
  U32               SizeL;                               // FileSize low word
  U32               SizeH;                               // FileSize high word
  U32               Flags;                               // File flags
  char              pRoot[CHOOSEFILE_MAXLEN];            // Buffer used internally and for passing result
  int            (* pfGetData)(CHOOSEFILE_INFO * pInfo); // Pointer to GetData() function
};

/*********************************************************************
*
*       Functions
*
**********************************************************************
*/
WM_HWIN CHOOSEFILE_Create(WM_HWIN           hParent,  // Parent window
                          int               xPos,     // xPosition in window coordinates
                          int               yPos,     // yPosition in window coordinates
                          int               xSize,    // xSize in pixels
                          int               ySize,    // ySize in pixels
                          const char      * apRoot[], // Pointers to root strings
                          int               NumRoot,  // Number of roots
                          int               SelRoot,  // Root to be selected at first
                          const char      * sCaption, // Shown in title bar
                          int               Flags,    // Flags for FRAMEWINDOW
                          CHOOSEFILE_INFO * pInfo     // Pointer to CHOOSEFILE_INFO structure
                          );

void    CHOOSEFILE_Callback            (WM_MESSAGE * pMsg);
void    CHOOSEFILE_EnableToolTips      (void);
void    CHOOSEFILE_SetButtonText       (WM_HWIN hWin, unsigned ButtonIndex, const char * pText);
void    CHOOSEFILE_SetDefaultButtonText(unsigned ButtonIndex, const char * pText);
void    CHOOSEFILE_SetDelim            (char Delim);
void    CHOOSEFILE_SetToolTips         (const TOOLTIP_INFO * pInfo, int NumItems);
void    CHOOSEFILE_SetTopMode          (unsigned OnOff);

#if defined(__cplusplus)
  }
#endif

#endif /* GUI_WINSUPPORT */

#endif /* CHOOSEFILE_H */

/*************************** End of file ****************************/
