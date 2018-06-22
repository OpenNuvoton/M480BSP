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
File        : WM_GUI.h
Purpose     : Windows manager include for low level GUI routines
----------------------------------------------------------------------
*/

#ifndef WM_GUI_H            /* Make sure we only include it once */
#define WM_GUI_H

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

int       WM__InitIVRSearch(const GUI_RECT* pMaxRect);
int       WM__GetNextIVR   (void);
int       WM__GetOrgX_AA(void);
int       WM__GetOrgY_AA(void);

#define WM_ITERATE_START(pRect)                   \
  {                                               \
    if (WM__InitIVRSearch(pRect))                 \
      do {

#define WM_ITERATE_END()                          \
    } while (WM__GetNextIVR());                   \
  }

#define WM_ADDORGX(x)       (x += GUI_pContext->xOff)
#define WM_ADDORGY(y)       (y += GUI_pContext->yOff)
#define WM_ADDORG(x0,y0)    WM_ADDORGX(x0); WM_ADDORGY(y0)
#define WM_ADDORGX_AA(x)    (x += WM__GetOrgX_AA())
#define WM_ADDORGY_AA(y)    (y += WM__GetOrgY_AA())
#define WM_ADDORG_AA(x0,y0) WM_ADDORGX_AA(x0); WM_ADDORGY_AA(y0)
#define WM_SUBORGX(x)       (x -= GUI_pContext->xOff)
#define WM_SUBORGY(y)       (y -= GUI_pContext->yOff)
#define WM_SUBORG(x0,y0)    WM_SUBORGX(x0); WM_SUBORGY(y0)

#if defined(__cplusplus)
  }
#endif


#endif   /* Avoid multiple inclusion */

/*************************** End of file ****************************/
