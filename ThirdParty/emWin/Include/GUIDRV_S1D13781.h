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
File        : GUIDRV_S1D13781.h
Purpose     : Interface definition for GUIDRV_S1D13781 driver
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUIDRV_S1D13781_H
#define GUIDRV_S1D13781_H

#define GUIDRV_S1D13781_USE_MAIN 0
#define GUIDRV_S1D13781_USE_PIP1 1
#define GUIDRV_S1D13781_USE_PIP2 2

/*********************************************************************
*
*       Configuration structure
*/
typedef struct {
  //
  // Driver specific configuration items
  //
  U32 BufferOffset;
  int UseLayer;
  int WriteBufferSize;
  int WaitUntilVNDP;
} CONFIG_S1D13781;

/*********************************************************************
*
*       Display drivers
*/
//
// Addresses
//
extern const GUI_DEVICE_API GUIDRV_S1D13781_8C0_API;
extern const GUI_DEVICE_API GUIDRV_S1D13781_OXY_8C0_API;
extern const GUI_DEVICE_API GUIDRV_S1D13781_OSY_8C0_API;
extern const GUI_DEVICE_API GUIDRV_S1D13781_OSX_8C0_API;

extern const GUI_DEVICE_API GUIDRV_S1D13781_16C0_API;
extern const GUI_DEVICE_API GUIDRV_S1D13781_OXY_16C0_API;
extern const GUI_DEVICE_API GUIDRV_S1D13781_OSY_16C0_API;
extern const GUI_DEVICE_API GUIDRV_S1D13781_OSX_16C0_API;

//
// Macros to be used in configuration files
//
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

  #define GUIDRV_S1D13781_8C0       &GUIDRV_Win_API
  #define GUIDRV_S1D13781_OXY_8C0   &GUIDRV_Win_API
  #define GUIDRV_S1D13781_OSY_8C0   &GUIDRV_Win_API
  #define GUIDRV_S1D13781_OSX_8C0   &GUIDRV_Win_API

  #define GUIDRV_S1D13781_16C0      &GUIDRV_Win_API
  #define GUIDRV_S1D13781_OXY_16C0  &GUIDRV_Win_API
  #define GUIDRV_S1D13781_OSY_16C0  &GUIDRV_Win_API
  #define GUIDRV_S1D13781_OSX_16C0  &GUIDRV_Win_API

#else

  #define GUIDRV_S1D13781_8C0       &GUIDRV_S1D13781_8C0_API
  #define GUIDRV_S1D13781_OXY_8C0   &GUIDRV_S1D13781_OXY_8C0_API
  #define GUIDRV_S1D13781_OSY_8C0   &GUIDRV_S1D13781_OSY_8C0_API
  #define GUIDRV_S1D13781_OSX_8C0   &GUIDRV_S1D13781_OSX_8C0_API

  #define GUIDRV_S1D13781_16C0      &GUIDRV_S1D13781_16C0_API
  #define GUIDRV_S1D13781_OXY_16C0  &GUIDRV_S1D13781_OXY_16C0_API
  #define GUIDRV_S1D13781_OSY_16C0  &GUIDRV_S1D13781_OSY_16C0_API
  #define GUIDRV_S1D13781_OSX_16C0  &GUIDRV_S1D13781_OSX_16C0_API

#endif

/*********************************************************************
*
*       Public routines
*/
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)
  #define GUIDRV_S1D13781_Config(pDevice, pConfig)
  #define GUIDRV_S1D13781_SetBusSPI(pDevice, pHW_API)
  #define GUIDRV_S1D13781_SetOrientation(Orientation, LayerIndex)
#else
  void GUIDRV_S1D13781_Config        (GUI_DEVICE * pDevice, CONFIG_S1D13781 * pConfig);
  void GUIDRV_S1D13781_SetBusSPI     (GUI_DEVICE * pDevice, GUI_PORT_API * pHW_API);
  int  GUIDRV_S1D13781_SetOrientation(int Orientation, int LayerIndex);
#endif

#endif

/*************************** End of file ****************************/
