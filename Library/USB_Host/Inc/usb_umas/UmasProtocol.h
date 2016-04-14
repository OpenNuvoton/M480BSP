/* Driver for USB Mass Storage compliant devices
 * Protocol Functions Header File
 *
 * $Id: protocol.h,v 1.3 2000/08/25 00:13:51 mdharm Exp $
 *
 * Current development and maintenance by:
 *   (c) 1999, 2000 Matthew Dharm (mdharm-usb@one-eyed-alien.net)
 *
 * This driver is based on the 'USB Mass Storage Class' document. This
 * describes in detail the protocol used to communicate with such
 * devices.  Clearly, the designers had SCSI and ATAPI commands in
 * mind when they created this document.  The commands are all very
 * similar to commands in the SCSI-II and ATAPI specifications.
 *
 * It is important to note that in a number of cases this class
 * exhibits class-specific exemptions from the USB specification.
 * Notably the usage of NAK, STALL and ACK differs from the norm, in
 * that they are used to communicate wait, failed and OK on commands.
 *
 * Also, for certain devices, the interrupt endpoint is used to convey
 * status of a command.
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

#ifndef _UMAS_PROTOCOL_H_
#define _UMAS_PROTOCOL_H_


/// @cond HIDDEN_SYMBOLS

/* Sub Classes */
#define UMAS_SC_RBC     0x01        /* Typically, flash devices */
#define UMAS_SC_8020    0x02        /* CD-ROM */
#define UMAS_SC_QIC     0x03        /* QIC-157 Tapes */
#define UMAS_SC_UFI     0x04        /* Floppy */
#define UMAS_SC_8070    0x05        /* Removable media */
#define UMAS_SC_SCSI    0x06        /* Transparent */
#define UMAS_SC_MIN UMAS_SC_RBC
#define UMAS_SC_MAX UMAS_SC_SCSI


#define USB_STOR_SCSI_SENSE_HDRSZ      4
#define USB_STOR_SCSI_SENSE_10_HDRSZ   8


struct usb_stor_scsi_sense_hdr {
    uint8_t   *dataLength;
    uint8_t   *mediumType;
    uint8_t   *devSpecParms;
    uint8_t   *blkDescLength;
};

typedef struct usb_stor_scsi_sense_hdr Usb_Stor_Scsi_Sense_Hdr;

union usb_stor_scsi_sense_hdr_u {
    Usb_Stor_Scsi_Sense_Hdr hdr;
    uint8_t   *array[USB_STOR_SCSI_SENSE_HDRSZ];
};


typedef union usb_stor_scsi_sense_hdr_u Usb_Stor_Scsi_Sense_Hdr_u;

struct usb_stor_scsi_sense_hdr_10 {
    uint8_t   *dataLengthMSB;
    uint8_t   *dataLengthLSB;
    uint8_t   *mediumType;
    uint8_t   *devSpecParms;
    uint8_t   *reserved1;
    uint8_t   *reserved2;
    uint8_t   *blkDescLengthMSB;
    uint8_t   *blkDescLengthLSB;
};

typedef struct usb_stor_scsi_sense_hdr_10 Usb_Stor_Scsi_Sense_Hdr_10;

union usb_stor_scsi_sense_hdr_10_u {
    Usb_Stor_Scsi_Sense_Hdr_10 hdr;
    uint8_t   *array[USB_STOR_SCSI_SENSE_10_HDRSZ];
};

typedef union usb_stor_scsi_sense_hdr_10_u Usb_Stor_Scsi_Sense_Hdr_10_u;


/*===================================================== Exported Functions ==*/
extern void  UMAS_AtapiCommand(SCSI_CMD_T *srb, UMAS_DATA_T *umas);
extern void  UMAS_Qic157Command(SCSI_CMD_T *srb, UMAS_DATA_T *umas);
extern void  UMAS_UfiCommand(SCSI_CMD_T *srb, UMAS_DATA_T *umas);
extern void  UMAS_TransparentScsiCommand(SCSI_CMD_T *srb, UMAS_DATA_T *umas);

/// @endcond HIDDEN_SYMBOLS

#endif  /* _UMAS_PROTOCOL_H_ */
