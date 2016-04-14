/* Driver for USB Mass Storage compliant devices
 * Transport Functions Header File
 *
 * $Id: transport.h,v 1.13 2000/10/03 01:06:07 mdharm Exp $
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

#ifndef _UMAS_TRANSPORT_H_
#define _UMAS_TRANSPORT_H_

/// @cond HIDDEN_SYMBOLS


/* Protocols */
#define UMAS_PR_CBI           0x00     /* Control/Bulk/Interrupt */
#define UMAS_PR_CB            0x01     /* Control/Bulk w/o interrupt */
#define UMAS_PR_BULK          0x50     /* bulk only */
#define UMAS_PR_DPCM_USB      0xf0     /* Combination CB/SDDR09 */

#ifdef CONFIG_USB_STORAGE_FREECOM
#define UMAS_PR_FREECOM       0xf1     /* Freecom */
#endif

/*
 * Bulk only data structures
 */

/* command block wrapper */
struct bulk_cb_wrap {
    uint32_t  Signature;                 /* contains 'USBC' */
    uint32_t  Tag;                       /* unique per command id */
    uint32_t  DataTransferLength;        /* size of data */
    uint8_t   Flags;                     /* direction in bit 0 */
    uint8_t   Lun;                       /* LUN normally 0 */
    uint8_t   Length;                    /* of of the CDB */
    uint8_t   CDB[16];                   /* max command */
};

#define UMAS_BULK_CB_WRAP_LEN     31
#define UMAS_BULK_CB_SIGN         0x43425355   /* spells out USBC */
#define UMAS_BULK_FLAG_IN         1
#define UMAS_BULK_FLAG_OUT        0

/* command status wrapper */
struct bulk_cs_wrap {
    uint32_t  Signature;                 /* should = 'USBS' */
    uint32_t  Tag;                       /* same as original command */
    uint32_t  Residue;                   /* amount not transferred */
    uint8_t   Status;                    /* see below */
    uint8_t   Filler[18];
};

#define UMAS_BULK_CS_WRAP_LEN     13
#define UMAS_BULK_CS_SIGN         0x53425355      /* spells out 'USBS' */
#define UMAS_BULK_STAT_OK         0    /* command passed */
#define UMAS_BULK_STAT_FAIL       1    /* command failed */
#define UMAS_BULK_STAT_PHASE      2    /* phase error */

/* bulk-only class specific requests */
#define UMAS_BULK_RESET_REQUEST   0xff
#define UMAS_BULK_GET_MAX_LUN     0xfe

/*
 * us_bulk_transfer() return codes
 */
#define UMAS_BULK_TRANSFER_GOOD     0  /* good transfer                 */
#define UMAS_BULK_TRANSFER_SHORT    1  /* transferred less than expected */
#define UMAS_BULK_TRANSFER_FAILED   2  /* transfer died in the middle   */
#define UMAS_BULK_TRANSFER_ABORTED  3  /* transfer canceled             */

/*
 * Transport return codes
 */
#define USB_STOR_TRANSPORT_GOOD     0  /* Transport good, command good     */
#define USB_STOR_TRANSPORT_FAILED   1  /* Transport good, command failed   */
#define USB_STOR_TRANSPORT_ERROR    2  /* Transport bad (i.e. device dead) */
#define USB_STOR_TRANSPORT_ABORTED  3  /* Transport aborted                */

/*
 * CBI accept device specific command
 */
#define US_CBI_ADSC                 0

void  UMAS_CbiIrq(struct urb *urb);
int   UMAS_CbiTransport(SCSI_CMD_T *srb, UMAS_DATA_T *umas);

int   UMAS_CbTransport(SCSI_CMD_T *srb, UMAS_DATA_T *umas);
int   UMAS_CbReset(UMAS_DATA_T *umas);

int   UMAS_BulkTransport(SCSI_CMD_T *srb, UMAS_DATA_T *umas);
int   UMAS_BulkMaxLun(UMAS_DATA_T *umas);
int   UMAS_BulkReset(UMAS_DATA_T *umas);

void  UMAS_InvokeTransport(SCSI_CMD_T *srb, UMAS_DATA_T *us);

/// @endcond HIDDEN_SYMBOLS


#endif  /* _UMAS_TRANSPORT_H_ */
