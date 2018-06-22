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
File        : GUIDRV_S1D13748.h
Purpose     : Interface definition for GUIDRV_S1D13748 driver
---------------------------END-OF-HEADER------------------------------
*/

#ifndef GUIDRV_S1D13748_H
#define GUIDRV_S1D13748_H

#if defined(__cplusplus)
extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

#define GUIDRV_S1D13748_USE_MAIN 0
#define GUIDRV_S1D13748_USE_PIP1 1
#define GUIDRV_S1D13748_USE_PIP2 2

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
} CONFIG_S1D13748;

/*********************************************************************
*
*       Display drivers
*/
//
// Addresses
//
extern const GUI_DEVICE_API GUIDRV_S1D13748_16_API;
extern const GUI_DEVICE_API GUIDRV_S1D13748_OY_16_API;
extern const GUI_DEVICE_API GUIDRV_S1D13748_OX_16_API;
extern const GUI_DEVICE_API GUIDRV_S1D13748_OXY_16_API;
extern const GUI_DEVICE_API GUIDRV_S1D13748_OS_16_API;
extern const GUI_DEVICE_API GUIDRV_S1D13748_OSY_16_API;
extern const GUI_DEVICE_API GUIDRV_S1D13748_OSX_16_API;
extern const GUI_DEVICE_API GUIDRV_S1D13748_OSXY_16_API;

//
// Macros to be used in configuration files
//
#if defined(WIN32) && !defined(LCD_SIMCONTROLLER)

  #define GUIDRV_S1D13748_16       &GUIDRV_Win_API
  #define GUIDRV_S1D13748_OY_16    &GUIDRV_Win_API
  #define GUIDRV_S1D13748_OX_16    &GUIDRV_Win_API
  #define GUIDRV_S1D13748_OXY_16   &GUIDRV_Win_API
  #define GUIDRV_S1D13748_OS_16    &GUIDRV_Win_API
  #define GUIDRV_S1D13748_OSY_16   &GUIDRV_Win_API
  #define GUIDRV_S1D13748_OSX_16   &GUIDRV_Win_API
  #define GUIDRV_S1D13748_OSXY_16  &GUIDRV_Win_API

#else

  #define GUIDRV_S1D13748_16       &GUIDRV_S1D13748_16_API
  #define GUIDRV_S1D13748_OY_16    &GUIDRV_S1D13748_OY_16_API
  #define GUIDRV_S1D13748_OX_16    &GUIDRV_S1D13748_OX_16_API
  #define GUIDRV_S1D13748_OXY_16   &GUIDRV_S1D13748_OXY_16_API
  #define GUIDRV_S1D13748_OS_16    &GUIDRV_S1D13748_OS_16_API
  #define GUIDRV_S1D13748_OSY_16   &GUIDRV_S1D13748_OSY_16_API
  #define GUIDRV_S1D13748_OSX_16   &GUIDRV_S1D13748_OSX_16_API
  #define GUIDRV_S1D13748_OSXY_16  &GUIDRV_S1D13748_OSXY_16_API

#endif

/*********************************************************************
*
*       Public routines
*/
void GUIDRV_S1D13748_Config  (GUI_DEVICE * pDevice, CONFIG_S1D13748 * pConfig);
void GUIDRV_S1D13748_SetBus16(GUI_DEVICE * pDevice, GUI_PORT_API * pHW_API);

#if defined(__cplusplus)
}
#endif

#endif

/*************************** End of file ****************************/
