/*************************************************************************
 * Nuvoton Electronics Corporation confidential
 *
 * Copyright (c) 2008 by Nuvoton Electronics Corporation
 * All rights reserved
 *
 * FILENAME
 *     usbsupport.h
 *
 * VERSION
 *     1.0
 *
 * DESCRIPTION
 *     M480 USB Host driver header file
 *
 * HISTORY
 *     2016.08.24       Created
 *
 * REMARK
 *     None
 **************************************************************************/
#ifndef  _USBSUPPORT_H_
#define  _USBSUPPORT_H_


/// @cond HIDDEN_SYMBOLS

/*-------------------------------------------------------------------------
 *   Memory allocation support on Integrator board
 *-------------------------------------------------------------------------*/

enum {
    BOUNDARY_BYTE=1,
    BOUNDARY_HALF_WORD=2,
    BOUNDARY_WORD=4,
    BOUNDARY32=32,
    BOUNDARY64=64,
    BOUNDARY128=128,
    BOUNDARY256=256,
    BOUNDARY512=512,
    BOUNDARY1024=1024,
    BOUNDARY2048=2048,
    BOUNDARY4096=4096
};

extern uint32_t  *_USB_pCurrent;    /* for debug usage */


extern int _IsInUsbInterrupt;

/*-------------------------------------------------------------------------
 *   Exported Functions
 *-------------------------------------------------------------------------*/
void    USB_InitializeMemoryPool(void);
void    *USB_malloc(int wanted_size, int boundary);
void    USB_free(void *);
int     USB_available_memory(void);
int     USB_allocated_memory(void);

/// @endcond HIDDEN_SYMBOLS

#endif  /* _USBSUPPORT_H_ */
