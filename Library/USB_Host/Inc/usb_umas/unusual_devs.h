/* Driver for USB Mass Storage compliant devices
 * Ununsual Devices File
 *
 * $Id: unusual_devs.h,v 1.1 2000/12/05 05:38:31 mdharm Exp $
 *
 * Current development and maintenance by:
 *   (c) 2000 Matthew Dharm (mdharm-usb@one-eyed-alien.net)
 *
 * Initial work by:
 *   (c) 2000 Adam J. Richter (adam@yggdrasil.com), Yggdrasil Computing, Inc.
 *
 * Please see http://www.one-eyed-alien.net/~mdharm/linux-usb for more
 * information about this driver.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2, or (at your option) any
 * later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/* IMPORTANT NOTE: This file must be included in another file which does
 * the following thing for it to work:
 * The macro UNUSUAL_DEV() must be defined before this file is included
 */

/* If you edit this file, please try to keep it sorted first by VendorID,
 * then by ProductID.
 */

UNUSUAL_DEV(  0x03ee, 0x0000, 0x0000, 0x0245,
              "Mitsumi",
              "CD-R/RW Drive",
              UMAS_SC_8020, UMAS_PR_CBI, NULL, 0),

                            UNUSUAL_DEV(  0x03f0, 0x0107, 0x0200, 0x0200,
                                    "HP",
                                    "CD-Writer+",
                                    UMAS_SC_8070, UMAS_PR_CB, NULL, 0),

                            UNUSUAL_DEV(  0x04e6, 0x0001, 0x0200, 0x0200,
                                    "Matshita",
                                    "LS-120",
                                    UMAS_SC_8020, UMAS_PR_CB, NULL, 0),

                            UNUSUAL_DEV(  0x04e6, 0x0006, 0x0100, 0x0200,
                                    "Shuttle",
                                    "eUSB MMC Adapter",
                                    UMAS_SC_SCSI, UMAS_PR_CB, NULL,
                                    UMAS_FL_SINGLE_LUN),

                            UNUSUAL_DEV(  0x04e6, 0x0007, 0x0100, 0x0200,
                                    "Sony",
                                    "Hifd",
                                    UMAS_SC_SCSI, UMAS_PR_CB, NULL,
                                    UMAS_FL_SINGLE_LUN),

                            UNUSUAL_DEV(  0x04e6, 0x0009, 0x0200, 0x0200,
                                    "Shuttle",
                                    "eUSB ATA/ATAPI Adapter",
                                    UMAS_SC_8020, UMAS_PR_CB, NULL, 0),

                            UNUSUAL_DEV(  0x04e6, 0x000a, 0x0200, 0x0200,
                                    "Shuttle",
                                    "eUSB CompactFlash Adapter",
                                    UMAS_SC_8020, UMAS_PR_CB, NULL, 0),

                            UNUSUAL_DEV(  0x04e6, 0x0101, 0x0200, 0x0200,
                                    "Shuttle",
                                    "CD-RW Device",
                                    UMAS_SC_8020, UMAS_PR_CB, NULL, 0),

                            UNUSUAL_DEV(  0x054c, 0x0010, 0x0106, 0x0210,
                                    "Sony",
                                    "DSC-S30/S70/505V/F505",
                                    UMAS_SC_SCSI, UMAS_PR_CB, NULL,
                                    UMAS_FL_SINGLE_LUN | UMAS_FL_START_STOP | UMAS_FL_MODE_XLATE ),

                            UNUSUAL_DEV(  0x054c, 0x002d, 0x0100, 0x0100,
                                    "Sony",
                                    "Memorystick MSAC-US1",
                                    UMAS_SC_UFI, UMAS_PR_CB, NULL,
                                    UMAS_FL_SINGLE_LUN | UMAS_FL_START_STOP ),

                            UNUSUAL_DEV(  0x057b, 0x0000, 0x0000, 0x0299,
                                    "Y-E Data",
                                    "Flashbuster-U",
                                    UMAS_SC_UFI,  UMAS_PR_CB, NULL,
                                    UMAS_FL_SINGLE_LUN),

                            UNUSUAL_DEV(  0x057b, 0x0000, 0x0300, 0x9999,
                                    "Y-E Data",
                                    "Flashbuster-U",
                                    UMAS_SC_UFI,  UMAS_PR_CBI, NULL,
                                    UMAS_FL_SINGLE_LUN),

                            UNUSUAL_DEV(  0x059f, 0xa601, 0x0200, 0x0200,
                                    "LaCie",
                                    "USB Hard Disk",
                                    UMAS_SC_RBC, UMAS_PR_CB, NULL, 0 ),

                            UNUSUAL_DEV(  0x05ab, 0x0031, 0x0100, 0x0100,
                                    "In-System",
                                    "USB/IDE Bridge (ATAPI ONLY!)",
                                    UMAS_SC_8070, UMAS_PR_BULK, NULL, 0 ),

                            UNUSUAL_DEV(  0x0644, 0x0000, 0x0100, 0x0100,
                                    "TEAC",
                                    "Floppy Drive",
                                    UMAS_SC_UFI, UMAS_PR_CB, NULL, 0 ),

                            UNUSUAL_DEV(  0x0693, 0x0002, 0x0100, 0x0100,
                                    "Hagiwara",
                                    "FlashGate SmartMedia",
                                    UMAS_SC_SCSI, UMAS_PR_BULK, NULL, 0 ),

                            UNUSUAL_DEV(  0x0693, 0x0005, 0x0100, 0x0100,
                                    "Hagiwara",
                                    "Flashgate",
                                    UMAS_SC_SCSI, UMAS_PR_BULK, NULL, 0 ),

                            UNUSUAL_DEV(  0x0781, 0x0001, 0x0200, 0x0200,
                                    "Sandisk",
                                    "ImageMate SDDR-05a",
                                    UMAS_SC_SCSI, UMAS_PR_CB, NULL,
                                    UMAS_FL_SINGLE_LUN | UMAS_FL_START_STOP),

                            UNUSUAL_DEV( 0x0781, 0x0100, 0x0100, 0x0100,
                                    "Sandisk",
                                    "ImageMate SDDR-12",
                                    UMAS_SC_SCSI, UMAS_PR_CB, NULL,
                                    UMAS_FL_SINGLE_LUN ),

                            UNUSUAL_DEV(  0x0781, 0x0002, 0x0009, 0x0009,
                                    "Sandisk",
                                    "ImageMate SDDR-31",
                                    UMAS_SC_SCSI, UMAS_PR_BULK, NULL,
                                    UMAS_FL_IGNORE_SER),

#if 0
                            UNUSUAL_DEV(  0x416, 0x963, 0x0000, 0x9999,
                                    "Nuvoton",
                                    "W78E727",
                                    UMAS_SC_SCSI, UMAS_PR_BULK, NULL,
                                    UMAS_FL_IGNORE_SER),
#endif


#ifdef CONFIG_USB_STORAGE_FREECOM
                            UNUSUAL_DEV( 0x07ab, 0xfc01, 0x0000, 0x9999,
                                    "Freecom",
                                    "USB-IDE",
                                    UMAS_SC_QIC, UMAS_PR_FREECOM, freecom_init, 0),
#endif

