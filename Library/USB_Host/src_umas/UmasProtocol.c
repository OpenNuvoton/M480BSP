/* Driver for USB Mass Storage compliant devices
 *
 * $Id: protocol.c,v 1.7 2000/11/13 22:28:33 mdharm Exp $
 *
 * Current development and maintenance by:
 *   (c) 1999, 2000 Matthew Dharm (mdharm-usb@one-eyed-alien.net)
 *
 * Developed with the assistance of:
 *   (c) 2000 David L. Brown, Jr. (usb-storage@davidb.org)
 *
 * Initial work by:
 *   (c) 1999 Michael Gee (michael@linuxspecific.com)
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

#include <stdio.h>
#include <string.h>

#include "M480.h"

#include "Umas.h"
#include "UmasProtocol.h"
#include "UmasTransport.h"


/***********************************************************************
 * Helper routines
 ***********************************************************************/

static void  usb_stor_scsiSenseParseBuffer(SCSI_CMD_T *srb,
        Usb_Stor_Scsi_Sense_Hdr_u *the6,
        Usb_Stor_Scsi_Sense_Hdr_10_u *the10, int *length_p)
{
    int    i = 0, j = 0, element = 0;
    int    length = 0;
    uint8_t  *buffer = 0;
    SCATTER_LIST_T  *sg = 0;

    /* are we scatter-gathering? */
    if (srb->use_sg != 0) {
        /*
         * loop over all the scatter gather structures and
         * get pointer to the data members in the headers
         * (also work out the length while we're here)
         */
        sg = (SCATTER_LIST_T *)srb->request_buff;
        for (i = 0; i < srb->use_sg; i++) {
            length += sg[i].length;
            /* We only do the inner loop for the headers */
            if (element < USB_STOR_SCSI_SENSE_10_HDRSZ) {
                /* scan through this scatterlist */
                for (j = 0; j < sg[i].length; j++) {
                    if (element < USB_STOR_SCSI_SENSE_HDRSZ) {
                        /* fill in the pointers for both header types */
                        the6->array[element] = (uint8_t *)&(sg[i].address[j]);
                        the10->array[element] = (uint8_t *)&(sg[i].address[j]);
                    } else if (element < USB_STOR_SCSI_SENSE_10_HDRSZ) {
                        /* only the longer headers still cares now */
                        the10->array[element] = (uint8_t *)&(sg[i].address[j]);
                    }
                    /* increase element counter */
                    element++;
                }  /* end of for */
            }
        } /* end of for */
    } else {
        length = srb->request_bufflen;
        buffer = srb->request_buff;
        if (length < USB_STOR_SCSI_SENSE_10_HDRSZ)
            UMAS_DEBUG("Buffer length smaller than header!!\n");
        for (i = 0; i < USB_STOR_SCSI_SENSE_10_HDRSZ; i++) {
            if (i < USB_STOR_SCSI_SENSE_HDRSZ) {
                the6->array[i] = &(buffer[i]);
                the10->array[i] = &(buffer[i]);
            } else
                the10->array[i] = &(buffer[i]);
        }
    }
    /* Set value of length passed in */
    *length_p = length;
}



static int  usb_stor_scsiSense10to6(SCSI_CMD_T *the10)
{
    uint8_t   *buffer=0;
    int     outputBufferSize = 0;
    int     length=0;
    int     i=0, j=0, element=0;
    int     sb=0,si=0,db=0,di=0;
    int     sgLength=0;
    SCATTER_LIST_T  *sg = 0;
    Usb_Stor_Scsi_Sense_Hdr_u       the6Locations;
    Usb_Stor_Scsi_Sense_Hdr_10_u    the10Locations;


    UMAS_VDEBUG("usb_stor_scsiSense10to6 - converting 10 byte sense data to 6 byte\n");
    the10->cmnd[0] = the10->cmnd[0] & 0xBF;

    /* Determine buffer locations */
    usb_stor_scsiSenseParseBuffer(the10, &the6Locations, &the10Locations, &length);

    /* Work out minimum buffer to output */
    outputBufferSize = *the10Locations.hdr.dataLengthLSB;
    outputBufferSize += USB_STOR_SCSI_SENSE_HDRSZ;

    /* Check to see if we need to trucate the output */
    if (outputBufferSize > length) {
        UMAS_DEBUG("usb_stor_scsiSense10to6 - Had to truncate MODE_SENSE_10 buffer into MODE_SENSE.\n");
        UMAS_DEBUG("outputBufferSize is %d and length is %d.\n", outputBufferSize, length);
    }
    outputBufferSize = length;

    /* Data length */
    if (*the10Locations.hdr.dataLengthMSB != 0) { /* MSB must be zero */
        UMAS_DEBUG("usb_stor_scsiSense10to6 - Command will be truncated to fit in SENSE6 buffer.\n");
        *the6Locations.hdr.dataLength = 0xff;
    } else {
        *the6Locations.hdr.dataLength = *the10Locations.hdr.dataLengthLSB;
    }

    /* Medium type and DevSpecific parms */
    *the6Locations.hdr.mediumType = *the10Locations.hdr.mediumType;
    *the6Locations.hdr.devSpecParms = *the10Locations.hdr.devSpecParms;

    /* Block descriptor length */
    if (*the10Locations.hdr.blkDescLengthMSB != 0) { /* MSB must be zero */
        UMAS_DEBUG("usb_stor_scsiSense10to6 - Command will be truncated to fit in SENSE6 buffer.\n");
        *the6Locations.hdr.blkDescLength = 0xff;
    } else {
        *the6Locations.hdr.blkDescLength = *the10Locations.hdr.blkDescLengthLSB;
    }

    if (the10->use_sg == 0) {
        buffer = the10->request_buff;
        /* Copy the rest of the data */
        memcpy(&(buffer[USB_STOR_SCSI_SENSE_HDRSZ]),
               &(buffer[USB_STOR_SCSI_SENSE_10_HDRSZ]),
               outputBufferSize - USB_STOR_SCSI_SENSE_HDRSZ );
        /* initialise last bytes left in buffer due to smaller header */
        memset(&(buffer[outputBufferSize
                        -(USB_STOR_SCSI_SENSE_10_HDRSZ-USB_STOR_SCSI_SENSE_HDRSZ)]),
               0,
               USB_STOR_SCSI_SENSE_10_HDRSZ-USB_STOR_SCSI_SENSE_HDRSZ);
    } else {
        sg = (SCATTER_LIST_T *) the10->request_buff;
        /* scan through this scatterlist and figure out starting positions */
        for (i = 0; i < the10->use_sg; i++) {
            sgLength = sg[i].length;
            for (j = 0; j < sgLength; j++ ) {
                /* get to end of header */
                if (element == USB_STOR_SCSI_SENSE_HDRSZ) {
                    db=i;
                    di=j;
                }
                if (element == USB_STOR_SCSI_SENSE_10_HDRSZ) {
                    sb=i;
                    si=j;
                    /* we've found both sets now, exit loops */
                    j = sgLength;
                    i = the10->use_sg;
                }
                element++;
            }
        }

        /* Now we know where to start the copy from */
        element = USB_STOR_SCSI_SENSE_HDRSZ;
        while (element < outputBufferSize
                -(USB_STOR_SCSI_SENSE_10_HDRSZ-USB_STOR_SCSI_SENSE_HDRSZ)) {
            /* check limits */
            if ((sb >= the10->use_sg) || (si >= sg[sb].length) ||
                    (db >= the10->use_sg) || (di >= sg[db].length)) {
                UMAS_DEBUG("usb_stor_scsiSense10to6 - Buffer overrun averted, this shouldn't happen!\n");
                break;
            }

            /* copy one byte */
            sg[db].address[di] = sg[sb].address[si];

            /* get next destination */
            if (sg[db].length - 1 == di) {
                db++;
                di=0;
            } else {
                di++;
            }

            /* get next source */
            if (sg[sb].length - 1 == si) {
                sb++;
                si=0;
            } else {
                si++;
            }
            element++;
        }
        /* zero the remaining bytes */
        while (element < outputBufferSize) {
            /* check limits */
            if ((db >= the10->use_sg) || (di >= sg[db].length)) {
                UMAS_DEBUG("usb_stor_scsiSense10to6 - Buffer overrun averted, this shouldn't happen!\n");
                break;
            }
            sg[db].address[di] = 0;

            /* get next destination */
            if (sg[db].length-1 == di) {
                db++;
                di=0;
            } else {
                di++;
            }
            element++;
        }
    }
    /* All done any everything was fine */
    return 0;
}

static int  usb_stor_scsiSense6to10(SCSI_CMD_T* the6)
{
    /* will be used to store part of buffer */
    uint8_t   tempBuffer[USB_STOR_SCSI_SENSE_10_HDRSZ-USB_STOR_SCSI_SENSE_HDRSZ], *buffer=0;
    int     outputBufferSize = 0;
    int     length=0;
    int     i = 0, j = 0, element = 0;
    int     sb = 0, si = 0, db = 0, di = 0;
    int     lsb = 0, lsi = 0, ldb = 0, ldi = 0;
    SCATTER_LIST_T  *sg = 0;
    Usb_Stor_Scsi_Sense_Hdr_u      the6Locations;
    Usb_Stor_Scsi_Sense_Hdr_10_u   the10Locations;

    UMAS_VDEBUG("-- converting 6 byte sense data to 10 byte\n");
    the6->cmnd[0] = the6->cmnd[0] | 0x40;

    /* Determine buffer locations */
    usb_stor_scsiSenseParseBuffer(the6, &the6Locations, &the10Locations, &length);

    /* Work out minimum buffer to output */
    outputBufferSize = *the6Locations.hdr.dataLength;
    outputBufferSize += USB_STOR_SCSI_SENSE_10_HDRSZ;

    /* Check to see if we need to trucate the output */
    if (outputBufferSize > length) {
        UMAS_DEBUG("Had to truncate MODE_SENSE into MODE_SENSE_10 buffer.\n");
        UMAS_DEBUG("outputBufferSize is %d and length is %d.\n", outputBufferSize, length);
    }
    outputBufferSize = length;

    /* Block descriptor length - save these before overwriting */
    tempBuffer[2] = *the10Locations.hdr.blkDescLengthMSB;
    tempBuffer[3] = *the10Locations.hdr.blkDescLengthLSB;
    *the10Locations.hdr.blkDescLengthLSB = *the6Locations.hdr.blkDescLength;
    *the10Locations.hdr.blkDescLengthMSB = 0;

    /* reserved - save these before overwriting */
    tempBuffer[0] = *the10Locations.hdr.reserved1;
    tempBuffer[1] = *the10Locations.hdr.reserved2;
    *the10Locations.hdr.reserved1 = *the10Locations.hdr.reserved2 = 0;

    /* Medium type and DevSpecific parms */
    *the10Locations.hdr.devSpecParms = *the6Locations.hdr.devSpecParms;
    *the10Locations.hdr.mediumType = *the6Locations.hdr.mediumType;

    /* Data length */
    *the10Locations.hdr.dataLengthLSB = *the6Locations.hdr.dataLength;
    *the10Locations.hdr.dataLengthMSB = 0;

    if (!the6->use_sg) {
        buffer = the6->request_buff;
        /* Copy the rest of the data */
        memcpy(&(buffer[USB_STOR_SCSI_SENSE_10_HDRSZ]),
               &(buffer[USB_STOR_SCSI_SENSE_HDRSZ]),
               outputBufferSize-USB_STOR_SCSI_SENSE_10_HDRSZ);
        /* Put the first four bytes (after header) in place */
        memcpy(&(buffer[USB_STOR_SCSI_SENSE_10_HDRSZ]), tempBuffer,
               USB_STOR_SCSI_SENSE_10_HDRSZ-USB_STOR_SCSI_SENSE_HDRSZ);
    } else {
        sg = (SCATTER_LIST_T *) the6->request_buff;
        /* scan through this scatterlist and figure out ending positions */
        for (i = 0; i < the6->use_sg; i++) {
            for (j = 0; j < sg[i].length; j++) {
                /* get to end of header */
                if (element == USB_STOR_SCSI_SENSE_HDRSZ ) {
                    ldb = i;
                    ldi = j;
                }
                if (element == USB_STOR_SCSI_SENSE_10_HDRSZ) {
                    lsb = i;
                    lsi = j;
                    /* we've found both sets now, exit loops */
                    j = sg[i].length;
                    i = the6->use_sg;
                    break;
                }
                element++;
            }
        }

        /* scan through this scatterlist and figure out starting positions */
        element = length - 1;

        /* destination is the last element */
        db=the6->use_sg - 1;
        di=sg[db].length - 1;

        for (i = the6->use_sg - 1; i >= 0; i--) {
            for (j = sg[i].length - 1; j >= 0; j--) {
                /* get to end of header and find source for copy */
                if (element == length - 1
                        - (USB_STOR_SCSI_SENSE_10_HDRSZ-USB_STOR_SCSI_SENSE_HDRSZ)) {
                    sb = i;
                    si = j;
                    /* we've found both sets now, exit loops */
                    j = -1;
                    i = -1;
                }
                element--;
            }
        }

        /* Now we know where to start the copy from */
        element = length - 1
                  - (USB_STOR_SCSI_SENSE_10_HDRSZ-USB_STOR_SCSI_SENSE_HDRSZ);
        while (element >= USB_STOR_SCSI_SENSE_10_HDRSZ) {
            /* check limits */
            if (((sb <= lsb) && (si < lsi)) || ((db <= ldb) && (di < ldi))) {
                UMAS_DEBUG("Buffer overrun averted, this shouldn't happen!\n");
                break;
            }

            /* copy one byte */
            sg[db].address[di] = sg[sb].address[si];

            /* get next destination */
            if (di == 0) {
                db--;
                di = sg[db].length - 1;
            } else {
                di--;
            }

            /* get next source */
            if (si == 0) {
                sb--;
                si = sg[sb].length - 1;
            } else {
                si--;
            }
            element--;
        }

        /* copy the remaining four bytes */
        while ( element >= USB_STOR_SCSI_SENSE_HDRSZ ) {
            /* check limits */
            if ((db <= ldb) && (di < ldi)) {
                UMAS_DEBUG("Buffer overrun averted, this shouldn't happen!\n");
                break;
            }

            sg[db].address[di] = tempBuffer[element - USB_STOR_SCSI_SENSE_HDRSZ];

            /* get next destination */
            if (di == 0) {
                db--;
                di = sg[db].length - 1;
            } else {
                di--;
            }
            element--;
        }
    }
    /* All done and everything was fine */
    return 0;
}



/*
 *  Fix-up the return data from an INQUIRY command to show
 *  ANSI SCSI rev 2 so we don't confuse the SCSI layers above umas
 */
static void  fix_inquiry_data(SCSI_CMD_T *srb)
{
    uint8_t   *data_ptr;

    /* verify that it's an INQUIRY command */
    if (srb->cmnd[0] != INQUIRY)
        return;

    UMAS_DEBUG("Fixing INQUIRY data to show SCSI rev 2\n");

    /* find the location of the data */
    if (srb->use_sg) {
        SCATTER_LIST_T  *sg;

        sg = (SCATTER_LIST_T *) srb->request_buff;
        data_ptr = (uint8_t *) sg[0].address;
    } else
        data_ptr = (uint8_t *)srb->request_buff;

    /* Change the SCSI revision number */
    data_ptr[2] |= 0x2;
}



/***********************************************************************
 * Protocol routines
 ***********************************************************************/
void  UMAS_Qic157Command(SCSI_CMD_T *srb, UMAS_DATA_T *umas)
{
    /*
     *  Pad the ATAPI command with zeros
     *  NOTE: This only works because a SCSI_CMD_T struct field contains
     *  a uint8_t cmnd[12], so we know we have storage available
     */
    for (; srb->cmd_len<12; srb->cmd_len++)
        srb->cmnd[srb->cmd_len] = 0;

    /* set command length to 12 bytes */
    srb->cmd_len = 12;

    /* send the command to the transport layer */
    UMAS_InvokeTransport(srb, umas);

    /* fix the INQUIRY data if necessary */
    fix_inquiry_data(srb);
}




void  UMAS_AtapiCommand(SCSI_CMD_T *srb, UMAS_DATA_T *umas)
{
    int   old_cmnd = 0;

    /*
     *  Fix some commands -- this is a form of mode translation
     *  ATAPI devices only accept 12 byte long commands
     *
     *  NOTE: This only works because a SCSI_CMD_T struct field contains
     *  a uint8_t cmnd[12], so we know we have storage available
     */

    /* Pad the ATAPI command with zeros */
    for (; srb->cmd_len<12; srb->cmd_len++)
        srb->cmnd[srb->cmd_len] = 0;

    /* set command length to 12 bytes */
    srb->cmd_len = 12;

    /* determine the correct (or minimum) data length for these commands */
    switch (srb->cmnd[0]) {
    /* change MODE_SENSE/MODE_SELECT from 6 to 10 byte commands */
    case MODE_SENSE:
    case MODE_SELECT:
        /* save the command so we can tell what it was */
        old_cmnd = srb->cmnd[0];

        srb->cmnd[11] = 0;
        srb->cmnd[10] = 0;
        srb->cmnd[9] = 0;
        srb->cmnd[8] = srb->cmnd[4];
        srb->cmnd[7] = 0;
        srb->cmnd[6] = 0;
        srb->cmnd[5] = 0;
        srb->cmnd[4] = 0;
        srb->cmnd[3] = 0;
        srb->cmnd[2] = srb->cmnd[2];
        srb->cmnd[1] = srb->cmnd[1];
        srb->cmnd[0] = srb->cmnd[0] | 0x40;
        break;

    /* change READ_6/WRITE_6 to READ_10/WRITE_10, which are ATAPI commands */
    case WRITE_6:
    case READ_6:
        srb->cmnd[11] = 0;
        srb->cmnd[10] = 0;
        srb->cmnd[9] = 0;
        srb->cmnd[8] = srb->cmnd[4];
        srb->cmnd[7] = 0;
        srb->cmnd[6] = 0;
        srb->cmnd[5] = srb->cmnd[3];
        srb->cmnd[4] = srb->cmnd[2];
        srb->cmnd[3] = srb->cmnd[1] & 0x1F;
        srb->cmnd[2] = 0;
        srb->cmnd[1] = srb->cmnd[1] & 0xE0;
        srb->cmnd[0] = srb->cmnd[0] | 0x20;
        break;
    }  /* end switch on cmnd[0] */

    /* convert MODE_SELECT data here */
    if (old_cmnd == MODE_SELECT)
        usb_stor_scsiSense6to10(srb);

    /* send the command to the transport layer */
    UMAS_InvokeTransport(srb, umas);

    /* Fix the MODE_SENSE data if we translated the command */
    if ((old_cmnd == MODE_SENSE) && (status_byte(srb->result) == GOOD))
        usb_stor_scsiSense10to6(srb);

    /* fix the INQUIRY data if necessary */
    fix_inquiry_data(srb);
}




void  UMAS_UfiCommand(SCSI_CMD_T *srb, UMAS_DATA_T *umas)
{
    int old_cmnd = 0;

    /*
     *  fix some commands -- this is a form of mode translation
     *  UFI devices only accept 12 byte long commands
     *
     *  NOTE: This only works because a SCSI_CMD_T struct field contains
     *  a uint8_t cmnd[12], so we know we have storage available
     */

    /* set command length to 12 bytes (this affects the transport layer) */
    srb->cmd_len = 12;

    /* determine the correct (or minimum) data length for these commands */
    switch (srb->cmnd[0]) {
    /* for INQUIRY, UFI devices only ever return 36 bytes */
    case INQUIRY:
        srb->cmnd[4] = 36;
        break;

    /* change MODE_SENSE/MODE_SELECT from 6 to 10 byte commands */
    case MODE_SENSE:
    case MODE_SELECT:
        /* save the command so we can tell what it was */
        old_cmnd = srb->cmnd[0];

        srb->cmnd[11] = 0;
        srb->cmnd[10] = 0;
        srb->cmnd[9] = 0;

        /*
         * If we're sending data, we send all.  If getting data,
         * get the minimum
         */
        if (srb->cmnd[0] == MODE_SELECT)
            srb->cmnd[8] = srb->cmnd[4];
        else
            srb->cmnd[8] = 8;

        srb->cmnd[7] = 0;
        srb->cmnd[6] = 0;
        srb->cmnd[5] = 0;
        srb->cmnd[4] = 0;
        srb->cmnd[3] = 0;
        srb->cmnd[2] = srb->cmnd[2];
        srb->cmnd[1] = srb->cmnd[1];
        srb->cmnd[0] = srb->cmnd[0] | 0x40;
        break;

    /* again, for MODE_SENSE_10, we get the minimum (8) */
    case MODE_SENSE_10:
        srb->cmnd[7] = 0;
        srb->cmnd[8] = 8;
        break;

    /* for REQUEST_SENSE, UFI devices only ever return 18 bytes */
    case REQUEST_SENSE:
        srb->cmnd[4] = 18;
        break;

    /* change READ_6/WRITE_6 to READ_10/WRITE_10, which are UFI commands */
    case WRITE_6:
    case READ_6:
        srb->cmnd[11] = 0;
        srb->cmnd[10] = 0;
        srb->cmnd[9] = 0;
        srb->cmnd[8] = srb->cmnd[4];
        srb->cmnd[7] = 0;
        srb->cmnd[6] = 0;
        srb->cmnd[5] = srb->cmnd[3];
        srb->cmnd[4] = srb->cmnd[2];
        srb->cmnd[3] = srb->cmnd[1] & 0x1F;
        srb->cmnd[2] = 0;
        srb->cmnd[1] = srb->cmnd[1] & 0xE0;
        srb->cmnd[0] = srb->cmnd[0] | 0x20;
        break;
    } /* end switch on cmnd[0] */

    /* convert MODE_SELECT data here */
    if (old_cmnd == MODE_SELECT)
        usb_stor_scsiSense6to10(srb);

    /* send the command to the transport layer */
    UMAS_InvokeTransport(srb, umas);

    /* Fix the MODE_SENSE data if we translated the command */
    if ((old_cmnd == MODE_SENSE) && (status_byte(srb->result) == GOOD))
        usb_stor_scsiSense10to6(srb);

    /* Fix the data for an INQUIRY, if necessary */
    fix_inquiry_data(srb);
}

void  UMAS_TransparentScsiCommand(SCSI_CMD_T *srb, UMAS_DATA_T *umas)
{
    /*
     * This code supports devices which do not support {READ|WRITE}_6
     * Apparently, neither Windows or MacOS will use these commands,
     * so some devices do not support them
     */
    if (umas->flags & UMAS_FL_MODE_XLATE) {
        /* translate READ_6 to READ_10 */
        if (srb->cmnd[0] == READ_6) {
            /* get the control */
            srb->cmnd[9] = umas->srb->cmnd[5];

            /* get the length */
            srb->cmnd[8] = umas->srb->cmnd[6];
            srb->cmnd[7] = 0;

            /* set the reserved area to 0 */
            srb->cmnd[6] = 0;

            /* get LBA */
            srb->cmnd[5] = umas->srb->cmnd[3];
            srb->cmnd[4] = umas->srb->cmnd[2];
            srb->cmnd[3] = 0;
            srb->cmnd[2] = 0;

            /* LUN and other info in cmnd[1] can stay */

            /* fix command code */
            srb->cmnd[0] = 0x28;

            UMAS_DEBUG("Changing READ_6 to READ_10\n");
            UMAS_DEBUG_ShowCommand(srb);
        }

        /* translate WRITE_6 to WRITE_10 */
        if (srb->cmnd[0] == WRITE_6) {
            /* get the control */
            srb->cmnd[9] = umas->srb->cmnd[5];

            /* get the length */
            srb->cmnd[8] = umas->srb->cmnd[4];
            srb->cmnd[7] = 0;

            /* set the reserved area to 0 */
            srb->cmnd[6] = 0;

            /* get LBA */
            srb->cmnd[5] = umas->srb->cmnd[3];
            srb->cmnd[4] = umas->srb->cmnd[2];
            srb->cmnd[3] = 0;
            srb->cmnd[2] = 0;

            /* LUN and other info in cmnd[1] can stay */

            /* fix command code */
            srb->cmnd[0] = 0x2A;

            UMAS_DEBUG("Changing WRITE_6 to WRITE_10\n");
            UMAS_DEBUG_ShowCommand(umas->srb);
        }
    }   /* if (umas->flags & UMAS_FL_MODE_XLATE) */

    /* send the command to the transport layer */
    UMAS_InvokeTransport(srb, umas);

    /* fix the INQUIRY data if necessary */
    fix_inquiry_data(srb);
}

