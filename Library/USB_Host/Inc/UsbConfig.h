/**************************************************************************//**
 * @file     UsbConfig.h
 * @version  V1.00
 * @brief    USB Host configuration header file.
 * @note
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef  _USBCONFIG_H_
#define  _USBCONFIG_H_

/// @cond HIDDEN_SYMBOLS


/*---  CPU clock speed ---*/
#define HZ                      (200)

#define CONFIG_HAVE_OHCI
#ifndef CONFIG_OTG
#define CONFIG_HAVE_EHCI
#endif

//#define DEBUG
//#define VDEBUG
//#define DUMP_DESCRIPTOR

#define AUTO_SUSPEND                    /* automatically suspend and resume */

#define EHCI_ISO_DELAY          0       //8
#define OHCI_ISO_DELAY          8


/*
 *  Size of static memory buffers
 */
#ifndef USB_MEMORY_POOL_SIZE
#define USB_MEMORY_POOL_SIZE   (48*1024)
#endif
#define USB_MEM_BLOCK_SIZE      128

#define USB_error               printf
#ifdef DEBUG
#define USB_debug               printf
#ifdef VDEBUG
#define USB_vdebug              printf
#else
#define USB_vdebug(...)
#endif
#else
#define USB_debug(...)
#define USB_vdebug(...)
#endif

/// @endcond HIDDEN_SYMBOLS

#endif  /* _USBCONFIG_H_ */


