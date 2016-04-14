/* Driver for USB Mass Storage compliant devices
 *
 * $Id: transport.c,v 1.38 2000/11/21 00:52:10 mdharm Exp $
 *
 * Current development and maintenance by:
 *   (c) 1999, 2000 Matthew Dharm (mdharm-usb@one-eyed-alien.net)
 *
 * Developed with the assistance of:
 *   (c) 2000 David L. Brown, Jr. (usb-storage@davidb.org)
 *   (c) 2000 Stephen J. Gowdy (SGowdy@lbl.gov)
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
#include "UmasTransport.h"
#include "UmasProtocol.h"


/***********************************************************************
 * Helper routines
 ***********************************************************************/
/*
 *  Calculate the length of the data transfer (not the command) for any
 *  given SCSI command
 */
static uint32_t  usb_stor_transfer_length(SCSI_CMD_T *srb)
{
    int     i;
    int     doDefault = 0;
    uint32_t  len = 0;
    uint32_t  total = 0;
    SCATTER_LIST_T  *sg;

    /*
     *  This table tells umas:
     *  X = command not supported
     *  L = return length in cmnd[4] (8 bits).
     *  M = return length in cmnd[8] (8 bits).
     *  G = return length in cmnd[3] and cmnd[4] (16 bits)
     *  H = return length in cmnd[7] and cmnd[8] (16 bits)
     *  I = return length in cmnd[8] and cmnd[9] (16 bits)
     *  C = return length in cmnd[2] to cmnd[5] (32 bits)
     *  D = return length in cmnd[6] to cmnd[9] (32 bits)
     *  B = return length in blocksize so we use buff_len
     *  R = return length in cmnd[2] to cmnd[4] (24 bits)
     *  S = return length in cmnd[3] to cmnd[5] (24 bits)
     *  T = return length in cmnd[6] to cmnd[8] (24 bits)
     *  U = return length in cmnd[7] to cmnd[9] (24 bits)
     *  0-9 = fixed return length
     *  V = 20 bytes
     *  W = 24 bytes
     *  Z = return length is mode dependant or not in command, use buff_len
     */

    static char  *lengths =  /* 0123456789ABCDEF   0123456789ABCDEF */
        "00XLZ6XZBXBBXXXB" "00LBBLG0R0L0GG0X"  /* 00-1F */
        "XXXXT8XXB4B0BBBB" "ZZZ0B00HCSSZTBHH"  /* 20-3F */
        "M0HHB0X000H0HH0X" "XHH0HHXX0TH0H0XX"  /* 40-5F */
        "XXXXXXXXXXXXXXXX" "XXXXXXXXXXXXXXXX"  /* 60-7F */
        "XXXXXXXXXXXXXXXX" "XXXXXXXXXXXXXXXX"  /* 80-9F */
        "X0XXX00XB0BXBXBB" "ZZZ0XUIDU000XHBX"  /* A0-BF */
        "XXXXXXXXXXXXXXXX" "XXXXXXXXXXXXXXXX"  /* C0-DF */
        "XDXXXXXXXXXXXXXX" "XXW00HXXXXXXXXXX"; /* E0-FF */

    /*  Commands checked in table:
     *  CHANGE_DEFINITION 40
     *  COMPARE 39
     *  COPY 18
     *  COPY_AND_VERIFY 3a
     *  ERASE 19
     *  ERASE_10 2c
     *  ERASE_12 ac
     *  EXCHANGE_MEDIUM a6
     *  FORMAT_UNIT 04
     *  GET_DATA_BUFFER_STATUS 34
     *  GET_MESSAGE_10 28
     *  GET_MESSAGE_12 a8
     *  GET_WINDOW 25   !!! Has more data than READ_CAPACITY, need to fix table
     *  INITIALIZE_ELEMENT_STATUS 07 !!! REASSIGN_BLOCKS luckily uses buff_len
     *  INQUIRY 12
     *  LOAD_UNLOAD 1b
     *  LOCATE 2b
     *  LOCK_UNLOCK_CACHE 36
     *  LOG_SELECT 4c
     *  LOG_SENSE 4d
     *  MEDIUM_SCAN 38     !!! This was M
     *  MODE_SELECT6 15
     *  MODE_SELECT_10 55
     *  MODE_SENSE_6 1a
     *  MODE_SENSE_10 5a
     *  MOVE_MEDIUM a5
     *  OBJECT_POSITION 31  !!! Same as SEARCH_DATA_EQUAL
     *  PAUSE_RESUME 4b
     *  PLAY_AUDIO_10 45
     *  PLAY_AUDIO_12 a5
     *  PLAY_AUDIO_MSF 47
     *  PLAY_AUDIO_TRACK_INDEX 48
     *  PLAY_AUDIO_TRACK_RELATIVE_10 49
     *  PLAY_AUDIO_TRACK_RELATIVE_12 a9
     *  POSITION_TO_ELEMENT 2b
     *  PRE-FETCH 34
     *  PREVENT_ALLOW_MEDIUM_REMOVAL 1e
     *  PRINT 0a             !!! Same as WRITE_6 but is always in bytes
     *  READ_6 08
     *  READ_10 28
     *  READ_12 a8
     *  READ_BLOCK_LIMITS 05
     *  READ_BUFFER 3c
     *  READ_CAPACITY 25
     *  READ_CDROM_CAPACITY 25
     *  READ_DEFECT_DATA 37
     *  READ_DEFECT_DATA_12 b7
     *  READ_ELEMENT_STATUS b8 !!! Think this is in bytes
     *  READ_GENERATION 29 !!! Could also be M?
     *  READ_HEADER 44     !!! This was L
     *  READ_LONG 3e
     *  READ_POSITION 34   !!! This should be V but conflicts with PRE-FETCH
     *  READ_REVERSE 0f
     *  READ_SUB-CHANNEL 42 !!! Is this in bytes?
     *  READ_TOC 43         !!! Is this in bytes?
     *  READ_UPDATED_BLOCK 2d
     *  REASSIGN_BLOCKS 07
     *  RECEIVE 08        !!! Same as READ_6 probably in bytes though
     *  RECEIVE_DIAGNOSTIC_RESULTS 1c
     *  RECOVER_BUFFERED_DATA 14 !!! For PRINTERs this is bytes
     *  RELEASE_UNIT 17
     *  REQUEST_SENSE 03
     *  REQUEST_VOLUME_ELEMENT_ADDRESS b5 !!! Think this is in bytes
     *  RESERVE_UNIT 16
     *  REWIND 01
     *  REZERO_UNIT 01
     *  SCAN 1b          !!! Conflicts with various commands, should be L
     *  SEARCH_DATA_EQUAL 31
     *  SEARCH_DATA_EQUAL_12 b1
     *  SEARCH_DATA_LOW 30
     *  SEARCH_DATA_LOW_12 b0
     *  SEARCH_DATA_HIGH 32
     *  SEARCH_DATA_HIGH_12 b2
     *  SEEK_6 0b         !!! Conflicts with SLEW_AND_PRINT
     *  SEEK_10 2b
     *  SEND 0a           !!! Same as WRITE_6, probably in bytes though
     *  SEND 2a           !!! Similar to WRITE_10 but for scanners
     *  SEND_DIAGNOSTIC 1d
     *  SEND_MESSAGE_6 0a   !!! Same as WRITE_6 - is in bytes
     *  SEND_MESSAGE_10 2a  !!! Same as WRITE_10 - is in bytes
     *  SEND_MESSAGE_12 aa  !!! Same as WRITE_12 - is in bytes
     *  SEND_OPC 54
     *  SEND_VOLUME_TAG b6 !!! Think this is in bytes
     *  SET_LIMITS 33
     *  SET_LIMITS_12 b3
     *  SET_WINDOW 24
     *  SLEW_AND_PRINT 0b !!! Conflicts with SEEK_6
     *  SPACE 11
     *  START_STOP_UNIT 1b
     *  STOP_PRINT 1b
     *  SYNCHRONIZE_BUFFER 10
     *  SYNCHRONIZE_CACHE 35
     *  TEST_UNIT_READY 00
     *  UPDATE_BLOCK 3d
     *  VERIFY 13
     *  VERIFY 2f
     *  VERIFY_12 af
     *  WRITE_6 0a
     *  WRITE_10 2a
     *  WRITE_12 aa
     *  WRITE_AND_VERIFY 2e
     *  WRITE_AND_VERIFY_12 ae
     *  WRITE_BUFFER 3b
     *  WRITE_FILEMARKS 10
     *  WRITE_LONG 3f
     *  WRITE_SAME 41
     */

    if (srb->sc_data_direction == SCSI_DATA_WRITE)
        doDefault = 1;
    else {
        switch (lengths[srb->cmnd[0]]) {
        case 'L':
            len = srb->cmnd[4];
            break;
        case 'M':
            len = srb->cmnd[8];
            break;
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            len = lengths[srb->cmnd[0]]-'0';
            break;
        case 'G':
            len = (((uint32_t)srb->cmnd[3])<<8) | srb->cmnd[4];
            break;
        case 'H':
            len = (((uint32_t)srb->cmnd[7])<<8) | srb->cmnd[8];
            break;
        case 'I':
            len = (((uint32_t)srb->cmnd[8])<<8) | srb->cmnd[9];
            break;
        case 'R':
            len = (((uint32_t)srb->cmnd[2])<<16) |
                  (((uint32_t)srb->cmnd[3])<<8) | srb->cmnd[4];
            break;
        case 'S':
            len = (((uint32_t)srb->cmnd[3])<<16) |
                  (((uint32_t)srb->cmnd[4])<<8) | srb->cmnd[5];
            break;
        case 'T':
            len = (((uint32_t)srb->cmnd[6])<<16) |
                  (((uint32_t)srb->cmnd[7])<<8) | srb->cmnd[8];
            break;
        case 'U':
            len = (((uint32_t)srb->cmnd[7])<<16) |
                  (((uint32_t)srb->cmnd[8])<<8) | srb->cmnd[9];
            break;
        case 'C':
            len = (((uint32_t)srb->cmnd[2])<<24) |
                  (((uint32_t)srb->cmnd[3])<<16) |
                  (((uint32_t)srb->cmnd[4])<<8) | srb->cmnd[5];
            break;
        case 'D':
            len = (((uint32_t)srb->cmnd[6])<<24) |
                  (((uint32_t)srb->cmnd[7])<<16) |
                  (((uint32_t)srb->cmnd[8])<<8) | srb->cmnd[9];
            break;
        case 'V':
            len = 20;
            break;
        case 'W':
            len = 24;
            break;
        case 'B':
            /* Use buffer size due to different block sizes */
            doDefault = 1;
            break;
        case 'X':
            UMAS_DEBUG("Error: UNSUPPORTED COMMAND %02X\n", srb->cmnd[0]);
            doDefault = 1;
            break;
        case 'Z':
            /* Use buffer size due to mode dependence */
            doDefault = 1;
            break;
        default:
            UMAS_DEBUG("Error: COMMAND %02X out of range or table inconsistent (%c).\n",
                       srb->cmnd[0], lengths[srb->cmnd[0]] );
            doDefault = 1;
        } /* end of switch */
    }

    if (doDefault == 1) {
        /* Are we going to scatter gather? */
        if (srb->use_sg) {
            /* Add up the sizes of all the sg segments */
            sg = (SCATTER_LIST_T *) srb->request_buff;
            for (i=0; i<srb->use_sg; i++)
                total += sg[i].length;
            len = total;
        } else
            /* Just return the length of the buffer */
            len = srb->request_bufflen;
    }
    return len;
}



/* This is a version of usb_clear_halt() that doesn't read the status from
 * the device -- this is because some devices crash their internal firmware
 * when the status is requested after a halt
 */
static int  clear_halt(struct usb_device *dev, int pipe)
{
    int    result;
    int    endp = usb_pipeendpoint(pipe) | (usb_pipein(pipe) << 7);

    UMAS_DEBUG("clear_halt!\n");
    result = usb_control_msg(dev, usb_sndctrlpipe(dev, 0),
                             USB_REQ_CLEAR_FEATURE, USB_RECIP_ENDPOINT, 0,
                             endp, NULL, 0, 0);
    /* this is a failure case */
    if (result < 0) {
        UMAS_DEBUG("clear_halt failed!!\n");
        return result;
    }

    /* reset the toggles and endpoint flags */
    //usb_endpoint_running(dev, usb_pipeendpoint(pipe), usb_pipeout(pipe));
    usb_settoggle(dev, usb_pipeendpoint(pipe), usb_pipeout(pipe), 0x1000);

    return 0;
}


volatile static int  _UmasUrbComplete;

int  is_urb_completed(void)
{
    return _UmasUrbComplete;
}

/***********************************************************************
 * Data transfer routines
 ***********************************************************************/
/*
 *  This is the completion handler which will wake us up when an URB
 *  completes.
 */
static void  usb_stor_blocking_completion(struct urb *urb)
{
    _UmasUrbComplete = 1;

#ifdef CONFIG_USB_STORAGE_DEBUG
    UMAS_DEBUG("usb_stor_blocking_completion called...\n");
#endif
}



/*
 *  This is our function to emulate usb_control_msg() but give us enough
 *  access to make aborts/resets work
 */
static int  usb_stor_control_msg(UMAS_DATA_T *umas, uint32_t pipe,
                                 uint8_t request, uint8_t requesttype, uint16_t value,
                                 uint16_t index, void *data, uint16_t size)
{
    struct urb  *urb = umas->current_urb;
    int    status;
    struct usb_ctrlrequest  *dr;

    /* allocate the device request structure */
    dr = USB_malloc(sizeof(struct usb_ctrlrequest), BOUNDARY_WORD);
    if (!dr)
        return -ENOMEM;

    /* fill in the structure */
    dr->bRequestType = requesttype;
    dr->bRequest = request;
#ifdef __BIG_ENDIAN
    dr->wValue = USB_SWAP16(value);
    dr->wIndex = USB_SWAP16(index);
    dr->wLength = USB_SWAP16(size);
#else
    dr->wValue = value;
    dr->wIndex = index;
    dr->wLength = size;
#endif

    /* fill the URB */
    usb_fill_control_urb(urb, umas->pusb_dev, pipe, (uint8_t *)dr, data, size,
                         usb_stor_blocking_completion, NULL);
    urb->actual_length = 0;
    urb->error_count = 0;
    //urb->transfer_flags = USB_ASYNC_UNLINK;

    _UmasUrbComplete = 0;

    /* submit the URB */
    status = usb_submit_urb(urb, 0);
    if (status) {
        /* something went wrong */
        USB_free(dr);
        return status;
    }

    /* wait for the completion of the URB */
    if (urb->status == -EINPROGRESS) {
        int  t0;

        t0 = umas_get_ticks();
        while (umas_get_ticks() - t0 < 600) {
            if (is_urb_completed())
                break;
        }

        if (umas_get_ticks() - t0 >= 600) {
            UMAS_DEBUG("usb_stor_control_msg time-out failed!\n");
            return -ETIMEDOUT;
        }
    }

    /* return the actual length of the data transferred if no error*/
    status = urb->status;
    if (status >= 0)
        status = urb->actual_length;

    USB_free(dr);
    return status;
}


/*
 *  This is our function to emulate usb_bulk_msg() but give us enough
 *  access to make aborts/resets work
 */
static int  usb_stor_bulk_msg(UMAS_DATA_T *umas, void *data, int pipe,
                              uint32_t len, uint32_t *act_len)
{
    struct urb  *urb = umas->current_urb;
    int  status;

    /* fill the URB */
    usb_fill_bulk_urb(urb, umas->pusb_dev, pipe, data, len,
                      usb_stor_blocking_completion, NULL);
    urb->actual_length = 0;
    urb->error_count = 0;
    //urb->transfer_flags = USB_ASYNC_UNLINK;

    _UmasUrbComplete = 0;

    /* submit the URB */
    status = usb_submit_urb(urb, 0);
    if (status)
        return status;

    if (urb->status == -EINPROGRESS) {
        int  t0;

        t0 = umas_get_ticks();
        while (umas_get_ticks() - t0 < 3000) {
            if (is_urb_completed())
                break;
        }

        if (umas_get_ticks() - t0 >= 3000) {
            UMAS_DEBUG("usb_stor_bulk_msg time-out failed!  %d\n", t0);
            return -ETIMEDOUT;
        }
    }

    /* return the actual length of the data transferred */
    *act_len = urb->actual_length;

    return urb->status;
}



/*
 *  Transfer one SCSI scatter-gather buffer via bulk transfer
 *
 *  Note that this function is necessary because we want the ability to
 *  use scatter-gather memory.  Good performance is achieved by a combination
 *  of scatter-gather and clustering (which makes each chunk bigger).
 *
 *  Note that the lower layer will always retry when a NAK occurs, up to the
 *  timeout limit.  Thus we don't have to worry about it for individual
 *  packets.
 */
static int  usb_stor_transfer_partial(UMAS_DATA_T *umas, char *buf, int length)
{
    int     result;
    uint32_t  partial;
    int     pipe;

    /* calculate the appropriate pipe information */
    if (umas->srb->sc_data_direction == SCSI_DATA_READ)
        pipe = usb_rcvbulkpipe(umas->pusb_dev, umas->ep_in_num);
    else
        pipe = usb_sndbulkpipe(umas->pusb_dev, umas->ep_out_num);

    /* transfer the data */
    UMAS_VDEBUG("usb_stor_transfer_partial - xfer %d bytes\n", length);
    result = usb_stor_bulk_msg(umas, buf, pipe, length, &partial);
    UMAS_VDEBUG("usb_stor_bulk_msg() returned %d xferred %d/%d\n", result, partial, length);
    //UMAS_DEBUG("usb_stor_bulk_msg() returned %d xferred %d/%d\n", result, partial, length);

    /* if we stall, we need to clear it before we go on */
    if (result == -EPIPE) {
        UMAS_DEBUG("usb_stor_transfer_partial - clearing endpoint halt for pipe 0x%x\n", pipe);
        clear_halt(umas->pusb_dev, pipe);
    }

    /* did we send all the data? */
    if (partial == length) {
        UMAS_VDEBUG("usb_stor_transfer_partial - transfer complete\n");
        return UMAS_BULK_TRANSFER_GOOD;
    }

    /* uh oh... we have an error code, so something went wrong. */
    if (result) {
        /* NAK - that means we've retried a few times already */
        if (result == -ETIMEDOUT) {
            UMAS_DEBUG("usb_stor_transfer_partial - device NAKed\n");
            return UMAS_BULK_TRANSFER_FAILED;
        }

        /* -ENOENT -- we canceled this transfer */
        if (result == -ENOENT) {
            UMAS_DEBUG("usb_stor_transfer_partial - transfer aborted\n");
            return UMAS_BULK_TRANSFER_ABORTED;
        }

        /* the catch-all case */
        UMAS_DEBUG("usb_stor_transfer_partial - unknown error\n");
        return UMAS_BULK_TRANSFER_FAILED;
    }

    /* no error code, so we must have transferred some data, just not all of it */
    return UMAS_BULK_TRANSFER_SHORT;
}



/*
 *  Transfer an entire SCSI command's worth of data payload over the bulk pipe.
 *
 *  Note that this uses usb_stor_transfer_partial to achieve it's goals -- this
 *  function simply determines if we're going to use scatter-gather or not,
 *  and acts appropriately.  For now, it also re-interprets the error codes.
 */
static void  us_transfer(SCSI_CMD_T *srb, UMAS_DATA_T* umas)
{
    int     i;
    int     result = -1;
    uint32_t  total_transferred = 0;
    uint32_t  transfer_amount;
    SCATTER_LIST_T  *sg;

    /* calculate how much we want to transfer */
    transfer_amount = usb_stor_transfer_length(srb);

    /* Was someone foolish enough to request more data than available buffer space?  */
    if (transfer_amount > srb->request_bufflen)
        transfer_amount = srb->request_bufflen;

    /* are we scatter-gathering? */
    if (srb->use_sg) {
        /*
         * loop over all the scatter gather structures and
         * make the appropriate requests for each, until done
         */
        sg = (SCATTER_LIST_T *) srb->request_buff;
        for (i = 0; i < srb->use_sg; i++) {
            /* transfer the lesser of the next buffer or the remaining data */
            if (transfer_amount - total_transferred >= sg[i].length) {
                result = usb_stor_transfer_partial(umas, sg[i].address, sg[i].length);
                total_transferred += sg[i].length;
            } else
                result = usb_stor_transfer_partial(umas, sg[i].address,
                                                   transfer_amount - total_transferred);
            /* if we get an error, end the loop here */
            if (result)
                break;
        }
    } else /* no scatter-gather, just make the request */
        result = usb_stor_transfer_partial(umas, (char *)srb->request_buff, transfer_amount);

    /* return the result in the data structure itself */
    srb->result = result;
}



/***********************************************************************
 * Transport routines
 ***********************************************************************/

/*
 *  Invoke the transport and basic error-handling/recovery methods
 *
 *  This is used by the protocol layers to actually send the message to
 *  the device and receive the response.
 */
void  UMAS_InvokeTransport(SCSI_CMD_T *srb, UMAS_DATA_T *umas)
{
    int    need_auto_sense;
    int    result;

    /* send the command to the transport layer */
    result = umas->transport(srb, umas);

    /*
     * If the command gets aborted by the higher layers, we need to
     * short-circuit all other processing
     */
    if (result == USB_STOR_TRANSPORT_ABORTED) {
        UMAS_DEBUG("UMAS_InvokeTransport - transport indicates command was aborted\n");
        srb->result = DID_ABORT << 16;
        return;
    }

    /*
     * Determine if we need to auto-sense
     *
     * I normally don't use a flag like this, but it's almost impossible
     * to understand what's going on here if I don't.
     */
    need_auto_sense = 0;

    /*
     * If we're running the CB transport, which is incapable
     * of determining status on it's own, we need to auto-sense almost
     * every time.
     */
    if ((umas->protocol == UMAS_PR_CB) || (umas->protocol == UMAS_PR_DPCM_USB)) {
        UMAS_VDEBUG("UMAS_InvokeTransport - CB transport device requiring auto-sense\n");
        need_auto_sense = 1;

        /*
         * There are some exceptions to this.  Notably, if this is
         * a UFI device and the command is REQUEST_SENSE or INQUIRY,
         * then it is impossible to truly determine status.
         */
        if ((umas->subclass == UMAS_SC_UFI) &&
                ((srb->cmnd[0] == REQUEST_SENSE) || (srb->cmnd[0] == INQUIRY))) {
            UMAS_DEBUG("UMAS_InvokeTransport - no auto-sense for a special command\n");
            need_auto_sense = 0;
        }
    }

    /*
     * If we have an error, we're going to do a REQUEST_SENSE
     * automatically.  Note that we differentiate between a command
     * "failure" and an "error" in the transport mechanism.
     */
    if (result == USB_STOR_TRANSPORT_FAILED) {
        UMAS_VDEBUG("UMAS_InvokeTransport - transport indicates command failure\n");
        need_auto_sense = 1;
    }
    if (result == USB_STOR_TRANSPORT_ERROR) {
#if 1  /* YCHuang, 2003.06.30 */
        //umas->transport_reset(umas);
        UMAS_DEBUG("UMAS_InvokeTransport - transport indicates transport error\n");
#endif
        need_auto_sense = 0;
        srb->result = DID_ERROR << 16;
        return;
    }

    /*
     * Also, if we have a short transfer on a command that can't have
     * a short transfer, we're going to do this.
     */
    if ((srb->result == UMAS_BULK_TRANSFER_SHORT) &&
            !((srb->cmnd[0] == REQUEST_SENSE) ||
              (srb->cmnd[0] == INQUIRY) ||
              (srb->cmnd[0] == MODE_SENSE) ||
              (srb->cmnd[0] == LOG_SENSE) ||
              (srb->cmnd[0] == MODE_SENSE_10))) {
        UMAS_DEBUG("UMAS_InvokeTransport - unexpectedly short transfer\n");
        need_auto_sense = 1;
    }

    /* Now, if we need to do the auto-sense, let's do it */
    if (need_auto_sense) {
        int     temp_result;
        void    *old_request_buffer;
        uint16_t  old_sg;
        uint32_t  old_request_bufflen;
        uint8_t   old_sc_data_direction;
        uint8_t   old_cmnd[MAX_COMMAND_SIZE];

        UMAS_VDEBUG("UMAS_InvokeTransport - Issuing auto-REQUEST_SENSE\n");

        /* save the old command */
        memcpy(old_cmnd, srb->cmnd, MAX_COMMAND_SIZE);

        /* set the command and the LUN */
        srb->cmnd[0] = REQUEST_SENSE;
        srb->cmnd[1] = old_cmnd[1] & 0xE0;
        srb->cmnd[2] = 0;
        srb->cmnd[3] = 0;
        srb->cmnd[4] = 18;
        srb->cmnd[5] = 0;

        /* set the transfer direction */
        old_sc_data_direction = srb->sc_data_direction;
        srb->sc_data_direction = SCSI_DATA_READ;

        /* use the new buffer we have */
        old_request_buffer = srb->request_buff;
        srb->request_buff = srb->sense_buffer;

        /* set the buffer length for transfer */
        old_request_bufflen = srb->request_bufflen;
        srb->request_bufflen = 18;

        /* set up for no scatter-gather use */
        old_sg = srb->use_sg;
        srb->use_sg = 0;

        /* issue the auto-sense command */
        temp_result = umas->transport(umas->srb, umas);
        if (temp_result != USB_STOR_TRANSPORT_GOOD) {
            UMAS_DEBUG("-- auto-sense failure\n");

            /*
             * we skip the reset if this happens to be a
             * multi-target device, since failure of an
             * auto-sense is perfectly valid
             */
            if (!(umas->flags & UMAS_FL_SCM_MULT_TARG)) {
                umas->transport_reset(umas);
                printf("transport_reset!!\n");
            }
            srb->result = DID_ERROR << 16;
            return;
        }

        UMAS_VDEBUG("-- Result from auto-sense is %d\n", temp_result);
        UMAS_VDEBUG("-- code: 0x%x, key: 0x%x, ASC: 0x%x, ASCQ: 0x%x\n",
                    srb->sense_buffer[0], srb->sense_buffer[2] & 0xf,
                    srb->sense_buffer[12], srb->sense_buffer[13]);
#ifdef CONFIG_USB_STORAGE_DEBUG
        UMAS_DEBUG_ShowSense(srb->sense_buffer[2] & 0xf,
                             srb->sense_buffer[12], srb->sense_buffer[13]);
#endif

        /* set the result so the higher layers expect this data */
        srb->result = CHECK_CONDITION << 1;

        /* we're done here, let's clean up */
        srb->request_buff = old_request_buffer;
        srb->request_bufflen = old_request_bufflen;
        srb->use_sg = old_sg;
        srb->sc_data_direction = old_sc_data_direction;
        memcpy(srb->cmnd, old_cmnd, MAX_COMMAND_SIZE);

        /* If things are really okay, then let's show that */
        if ((srb->sense_buffer[2] & 0xf) == 0x0)
            srb->result = GOOD << 1;
    } else /* if (need_auto_sense) */
        srb->result = GOOD << 1;

    /*
     * Regardless of auto-sense, if we _know_ we have an error
     * condition, show that in the result code
     */
    if (result == USB_STOR_TRANSPORT_FAILED)
        srb->result = CHECK_CONDITION << 1;

    /*
     * If we think we're good, then make sure the sense data shows it.
     * This is necessary because the auto-sense for some devices always
     * sets byte 0 == 0x70, even if there is no error
     */
    if ((umas->protocol == UMAS_PR_CB || umas->protocol == UMAS_PR_DPCM_USB) &&
            (result == USB_STOR_TRANSPORT_GOOD) && ((srb->sense_buffer[2] & 0xf) == 0x0))
        srb->sense_buffer[0] = 0x0;
}



/*
 * Control/Bulk/Interrupt transport
 */

/* The interrupt handler for CBI devices */
void  UMAS_CbiIrq(struct urb *urb)
{
    UMAS_DATA_T  *umas = (UMAS_DATA_T *)urb->context;

    UMAS_VDEBUG("UMAS_CbiIrq - len=%d, state=%d, status=(0x%x 0x%x)\n", urb->actual_length, urb->status, umas->irqbuf[0], umas->irqbuf[1]);

    /* reject improper IRQs */
    if (urb->actual_length != 2) {
        UMAS_DEBUG("-- IRQ too short\n");
        return;
    }

    /* is the device removed? */
    if (urb->status == -ENOENT) {
        UMAS_DEBUG("-- device has been removed\n");
        return;
    }

    /* was this a command-completion interrupt? */
    if (umas->irqbuf[0] && (umas->subclass != UMAS_SC_UFI)) {
        UMAS_DEBUG("-- not a command-completion IRQ\n");
        return;
    }

#if 0
    /* was this a wanted interrupt? */
    if (!umas->ip_wanted) {
        UMAS_DEBUG("ERROR: Unwanted interrupt received!\n");
        return;
    }
#endif
    umas->ip_wanted = 0 ;

    /* copy the valid data */
    umas->irqdata[0] = umas->irqbuf[0];
    umas->irqdata[1] = umas->irqbuf[1];

    /* wake up the command thread */
#ifdef _LINUX_
    UMAS_VDEBUG("-- Current value of ip_waitq is: %d\n", atomic_read(&umas->ip_waitq.count));
    up(&(umas->ip_waitq));
#endif
}



int  UMAS_CbiTransport(SCSI_CMD_T *srb, UMAS_DATA_T *umas)
{
    int result;

    /* Set up for status notification */
#ifdef _LINUX_
    atomic_set(umas->ip_wanted, 1);
#else
    umas->ip_wanted = 1;
#endif

    /* re-initialize the mutex so that we avoid any races with
     * early/late IRQs from previous commands */

    /* COMMAND STAGE */
    /* let's send the command via the control pipe */
    result = usb_stor_control_msg(umas, usb_sndctrlpipe(umas->pusb_dev,0),
                                  US_CBI_ADSC,
                                  USB_TYPE_CLASS | USB_RECIP_INTERFACE, 0,
                                  umas->intf->cur_altsetting->desc.bInterfaceNumber,
                                  srb->cmnd, srb->cmd_len);

    /* check the return code for the command */
    UMAS_VDEBUG("Call to usb_stor_control_msg() returned %d\n", result);
    if (result < 0) {
#ifdef _LINUX_
        /* Reset flag for status notification */
        atomic_set(umas->ip_wanted, 0);
#endif

        /* if the command was aborted, indicate that */
        if (result == -ENOENT)
            return USB_STOR_TRANSPORT_ABORTED;

        /* STALL must be cleared when they are detected */
        if (result == -EPIPE) {
            UMAS_VDEBUG("-- Stall on control pipe. Clearing\n");
            result = clear_halt(umas->pusb_dev,  usb_sndctrlpipe(umas->pusb_dev, 0));
            UMAS_VDEBUG("-- clear_halt() returns %d\n", result);
            return USB_STOR_TRANSPORT_FAILED;
        }

        /* Uh oh... serious problem here */
        return USB_STOR_TRANSPORT_ERROR;
    }

    /* DATA STAGE */
    /* transfer the data payload for this command, if one exists*/
    if (usb_stor_transfer_length(srb)) {
        us_transfer(srb, umas);
        UMAS_VDEBUG("CBI data stage result is 0x%x\n", srb->result);

        /* if it was aborted, we need to indicate that */
        if (srb->result == USB_STOR_TRANSPORT_ABORTED)
            return USB_STOR_TRANSPORT_ABORTED;

    }

    /* STATUS STAGE */

    //UMAS_VDEBUG("Current value of ip_waitq is: %d\n", umas->ip_waitq.count);

    /* if we were woken up by an abort instead of the actual interrupt */
    if (umas->ip_wanted) {
        UMAS_DEBUG("Did not get interrupt on CBI\n");
        umas->ip_wanted = 0;
        return USB_STOR_TRANSPORT_ABORTED;
    }

    UMAS_VDEBUG("Got interrupt data (0x%x, 0x%x)\n",  umas->irqdata[0], umas->irqdata[1]);

    /*
     *  UFI gives umas ASC and ASCQ, like a request sense
     *
     *  REQUEST_SENSE and INQUIRY don't affect the sense data on UFI
     *  devices, so we ignore the information for those commands.  Note
     *  that this means we could be ignoring a real error on these
     *  commands, but that can't be helped.
     */
    if (umas->subclass == UMAS_SC_UFI) {
        if ((srb->cmnd[0] == REQUEST_SENSE) || (srb->cmnd[0] == INQUIRY))
            return USB_STOR_TRANSPORT_GOOD;
        else {
            if (((uint8_t*)umas->irq_urb->transfer_buffer)[0])
                return USB_STOR_TRANSPORT_FAILED;
            else
                return USB_STOR_TRANSPORT_GOOD;
        }
    }

    /*
     *  If not UFI, we interpret the data as a result code
     *  The first byte should always be a 0x0
     *  The second byte & 0x0F should be 0x0 for good, otherwise error
     */
    if (umas->irqdata[0]) {
        UMAS_VDEBUG("CBI IRQ data showed reserved bType %d\n", umas->irqdata[0]);
        return USB_STOR_TRANSPORT_ERROR;
    }

    switch (umas->irqdata[1] & 0x0F) {
    case 0x00:
        return USB_STOR_TRANSPORT_GOOD;
    case 0x01:
        return USB_STOR_TRANSPORT_FAILED;
    default:
        return USB_STOR_TRANSPORT_ERROR;
    }

    /* we should never get here, but if we do, we're in trouble */
    //return USB_STOR_TRANSPORT_ERROR;
}



/*
 * Control/Bulk transport
 */
int  UMAS_CbTransport(SCSI_CMD_T *srb, UMAS_DATA_T *umas)
{
    int    result;

    /* COMMAND STAGE */
    /* let's send the command via the control pipe */
    result = usb_stor_control_msg(umas, usb_sndctrlpipe(umas->pusb_dev,0),
                                  US_CBI_ADSC,
                                  USB_TYPE_CLASS | USB_RECIP_INTERFACE, 0,
                                  umas->intf->cur_altsetting->desc.bInterfaceNumber,
                                  srb->cmnd, srb->cmd_len);

    /* check the return code for the command */
    UMAS_VDEBUG("UMAS_CbTransport - Call to usb_stor_control_msg() returned %d\n", result);
    if (result < 0) {
        /* if the command was aborted, indicate that */
        if (result == -ENOENT)
            return USB_STOR_TRANSPORT_ABORTED;

        /* a stall is a fatal condition from the device */
        if (result == -EPIPE) {
            UMAS_DEBUG("UMAS_CbTransport - Stall on control pipe. Clearing\n");
            result = clear_halt(umas->pusb_dev, usb_sndctrlpipe(umas->pusb_dev, 0));
            UMAS_DEBUG("UMAS_CbTransport - clear_halt() returns %d\n", result);
            return USB_STOR_TRANSPORT_FAILED;
        }

        /* Uh oh... serious problem here */
        return USB_STOR_TRANSPORT_ERROR;
    }

    /* DATA STAGE */
    /* transfer the data payload for this command, if one exists */
    if (usb_stor_transfer_length(srb)) {
        us_transfer(srb, umas);
        UMAS_VDEBUG("UMAS_CbTransport - CB data stage result is 0x%x\n", srb->result);

        /* if it was aborted, we need to indicate that */
        if (srb->result == USB_STOR_TRANSPORT_ABORTED)
            return USB_STOR_TRANSPORT_ABORTED;
    }

    /* STATUS STAGE */
    /* NOTE: CB does not have a status stage.  Silly, I know.  So
     * we have to catch this at a higher level.
     */
    return USB_STOR_TRANSPORT_GOOD;
}



/*
 * Bulk only transport
 */

/* Determine what the maximum LUN supported is */
int  UMAS_BulkMaxLun(UMAS_DATA_T *umas)
{
    uint8_t     data;
    int     result;
    int     pipe;
    uint8_t   *dma_buff;

    dma_buff = USB_malloc(1, BOUNDARY_WORD);

    /* issue the command */
    pipe = usb_rcvctrlpipe(umas->pusb_dev, 0);
    result = usb_control_msg(umas->pusb_dev, pipe, UMAS_BULK_GET_MAX_LUN,
                             USB_DIR_IN | USB_TYPE_CLASS | USB_RECIP_INTERFACE,
                             0, umas->intf->cur_altsetting->desc.bInterfaceNumber,
                             dma_buff, 1, 0);

    data = dma_buff[0];
    USB_free(dma_buff);

    UMAS_DEBUG("GetMaxLUN command result is %d, data is %d\n", result, data);

    /* if we have a successful request, return the result */
    if (result == 1)
        return data;

    /* if we get a STALL, clear the stall */
    if (result == -EPIPE) {
        UMAS_DEBUG("clearing endpoint halt for pipe 0x%x\n", pipe);
        clear_halt(umas->pusb_dev, pipe);
    }

    /* return the default -- no LUNs */
    return 0;
}



int  UMAS_BulkTransport(SCSI_CMD_T *srb, UMAS_DATA_T *umas)
{
    struct bulk_cb_wrap  *bcb;
    struct bulk_cs_wrap  *bcs;
    int     result, status = 0;
    int     pipe;
    uint32_t    partial;

    /* if the device was removed, then we're already reset */
    if (!umas->pusb_dev)
        return SUCCESS;

    bcb = USB_malloc(sizeof(struct bulk_cb_wrap), BOUNDARY_WORD);
    bcs = USB_malloc(sizeof(struct bulk_cs_wrap), BOUNDARY_WORD);
    if ((bcb == NULL) || (bcs == NULL)) {
        UMAS_DEBUG("UMAS_BulkTransport - Memory not enough!\n");
        status = USB_STOR_TRANSPORT_FAILED;
        goto bulk_error;
    }

    /* set up the command wrapper */
    bcb->Signature = UMAS_BULK_CB_SIGN;
    bcb->DataTransferLength = usb_stor_transfer_length(srb);
#ifdef __BIG_ENDIAN
    bcb->Signature = USB_SWAP32(bcb->Signature);
    bcb->DataTransferLength = USB_SWAP32(bcb->DataTransferLength);
#endif
    bcb->Flags = srb->sc_data_direction == SCSI_DATA_READ ? 1 << 7 : 0;
    bcb->Tag = srb->serial_number;
    bcb->Lun = srb->cmnd[1] >> 5;

    if (umas->flags & UMAS_FL_SCM_MULT_TARG)
        bcb->Lun |= srb->target << 4;
    bcb->Length = srb->cmd_len;

    /* construct the pipe handle */
    pipe = usb_sndbulkpipe(umas->pusb_dev, umas->ep_out_num);

    /* copy the command payload */
    memset(bcb->CDB, 0, sizeof(bcb->CDB));
    memcpy(bcb->CDB, srb->cmnd, bcb->Length);

    /* send it to out endpoint */
    UMAS_VDEBUG("Bulk command S 0x%x T 0x%x Trg %d LUN %d L %d F %d CL %d\n",
                bcb->Signature, bcb->Tag, (bcb->Lun >> 4), (bcb->Lun & 0x0F),
                bcb->DataTransferLength, bcb->Flags, bcb->Length);
    result = usb_stor_bulk_msg(umas, (char *)bcb, pipe, UMAS_BULK_CB_WRAP_LEN, &partial);
    UMAS_VDEBUG("Bulk command transfer result=%d\n", result);

    /* if the command was aborted, indicate that */
    if (result == -ENOENT)
        return USB_STOR_TRANSPORT_ABORTED;

    /* if we stall, we need to clear it before we go on */
    if (result == -EPIPE) {
        UMAS_DEBUG("UMAS_BulkTransport - 1 clearing endpoint halt for pipe 0x%x\n", pipe);
        clear_halt(umas->pusb_dev, pipe);
    } else if (result) {
        /* unknown error -- we've got a problem */
        status = USB_STOR_TRANSPORT_ERROR;
        goto bulk_error;
    }

    /* if the command transferred well, then we go to the data stage */
    if (result == 0) {
        /* send/receive data payload, if there is any */
        if (bcb->DataTransferLength) {
            us_transfer(srb, umas);

            /* if it was aborted, we need to indicate that */
            if (srb->result == USB_STOR_TRANSPORT_ABORTED) {
                status = USB_STOR_TRANSPORT_ABORTED;
                goto bulk_error;
            }
        }
    }

    /*
     *  See flow chart on pg 15 of the Bulk Only Transport spec for
     *  an explanation of how this code works.
     */

    /* construct the pipe handle */
    pipe = usb_rcvbulkpipe(umas->pusb_dev, umas->ep_in_num);

    /* get CSW for device status */
    UMAS_VDEBUG("Attempting to get CSW...\n");
    result = usb_stor_bulk_msg(umas, (char *)bcs, pipe, UMAS_BULK_CS_WRAP_LEN, &partial);

    /* if the command was aborted, indicate that */
    if (result == -ENOENT) {
        status = USB_STOR_TRANSPORT_ABORTED;
        goto bulk_error;
    }

    /* did the attempt to read the CSW fail? */
    if (result == -EPIPE) {
        UMAS_DEBUG("get CSW failed - clearing endpoint halt for pipe 0x%x\n", pipe);
        clear_halt(umas->pusb_dev, pipe);

        /* get the status again */
        UMAS_DEBUG("Attempting to get CSW (2nd try)...\n");
        result = usb_stor_bulk_msg(umas, (char *)bcs, pipe, UMAS_BULK_CS_WRAP_LEN, &partial);

        /* if the command was aborted, indicate that */
        if (result == -ENOENT) {
            UMAS_DEBUG("get CSW Command was aborted!\n");
            status = USB_STOR_TRANSPORT_ABORTED;
            goto bulk_error;
        }

        /* if it fails again, we need a reset and return an error*/
        if (result == -EPIPE) {
            UMAS_DEBUG("get CSW command 2nd try failed - clearing halt for pipe 0x%x\n", pipe);
            clear_halt(umas->pusb_dev, pipe);
            status = USB_STOR_TRANSPORT_ERROR;
            goto bulk_error;
        }
    }

    /* if we still have a failure at this point, we're in trouble */
    UMAS_VDEBUG("Bulk status result = %d\n", result);
    if (result) {
        status = USB_STOR_TRANSPORT_ERROR;
        goto bulk_error;
    }

#ifdef __BIG_ENDIAN
    bcs->Signature = USB_SWAP32(bcs->Signature);
#endif

    /* check bulk status */
    UMAS_VDEBUG("Bulk status Sig 0x%x T 0x%x R %d Stat 0x%x\n",
                USB_SWAP32(bcs->Signature), bcs->Tag, bcs->Residue, bcs->Status);
    if ((bcs->Signature != UMAS_BULK_CS_SIGN) || (bcs->Tag != bcb->Tag) ||
            (bcs->Status > UMAS_BULK_STAT_PHASE) || (partial != 13)) {
        UMAS_DEBUG("Bulk status Sig 0x%x T 0x%x R %d Stat 0x%x\n",
                   USB_SWAP32(bcs->Signature), bcs->Tag, bcs->Residue, bcs->Status);
        status = USB_STOR_TRANSPORT_ERROR;
        goto bulk_error;
    }

    /* based on the status code, we report good or bad */
    switch (bcs->Status) {
    case UMAS_BULK_STAT_OK:
        /* command good -- note that data could be short */
        USB_free(bcb);
        USB_free(bcs);
        return USB_STOR_TRANSPORT_GOOD;

    case UMAS_BULK_STAT_FAIL:
        /* command failed */
        status = USB_STOR_TRANSPORT_FAILED;
        goto bulk_error;

    case UMAS_BULK_STAT_PHASE:
        /* phase error -- note that a transport reset will be
         * invoked by the invoke_transport() function
         */
        status = USB_STOR_TRANSPORT_ERROR;
        goto bulk_error;
    }
    /* we should never get here, but if we do, we're in trouble */

bulk_error:
    USB_free(bcb);
    USB_free(bcs);
    return status;
}




/***********************************************************************
 * Reset routines
 ***********************************************************************/

/*
 *  This issues a CB[I] Reset to the device in question
 */
int  UMAS_CbReset(UMAS_DATA_T *umas)
{
    uint8_t   cmd[12];
    int     result;

    /* if the device was removed, then we're already reset */
    if (!umas->pusb_dev)
        return SUCCESS;

    memset(cmd, 0xFF, sizeof(cmd));
    cmd[0] = SEND_DIAGNOSTIC;
    cmd[1] = 4;
    result = usb_control_msg(umas->pusb_dev, usb_sndctrlpipe(umas->pusb_dev,0),
                             US_CBI_ADSC, USB_TYPE_CLASS | USB_RECIP_INTERFACE,
                             0, umas->intf->cur_altsetting->desc.bInterfaceNumber,
                             cmd, sizeof(cmd), 0);
    if (result < 0) {
        UMAS_DEBUG("UMAS_CbReset - CB[I] soft reset failed %d\n", result);
        return FAILED;
    }

#ifdef _LINUX_
    /* long wait for reset */
    set_current_state(TASK_UNINTERRUPTIBLE);
    schedule_timeout(HZ*6);
    set_current_state(TASK_RUNNING);
#endif

    UMAS_VDEBUG("UMAS_CbReset - clearing endpoint halt\n");
    clear_halt(umas->pusb_dev, usb_rcvbulkpipe(umas->pusb_dev, umas->ep_in_num));
    clear_halt(umas->pusb_dev, usb_rcvbulkpipe(umas->pusb_dev, umas->ep_out_num));

    UMAS_VDEBUG("UMAS_CbReset - done\n");
    /* return a result code based on the result of the control message */
    return SUCCESS;
}



/*
 *  This issues a Bulk-only Reset to the device in question, including
 *  clearing the subsequent endpoint halts that may occur.
 */
int  UMAS_BulkReset(UMAS_DATA_T *umas)
{
    int result;

    UMAS_VDEBUG("Bulk reset requested\n");

    /* if the device was removed, then we're already reset */
    if (!umas->pusb_dev)
        return SUCCESS;

    result = usb_control_msg(umas->pusb_dev,
                             usb_sndctrlpipe(umas->pusb_dev,0), UMAS_BULK_RESET_REQUEST,
                             USB_TYPE_CLASS | USB_RECIP_INTERFACE, 0,
                             umas->intf->cur_altsetting->desc.bInterfaceNumber,
                             NULL, 0, 1000);
    if (result < 0) {
        UMAS_DEBUG("Bulk soft reset failed %d\n", result);
        return FAILED;
    }

    {
        int t0;
        t0 = get_ticks();
        while (get_ticks() - t0 < 10)
            ;
    }

    clear_halt(umas->pusb_dev, usb_rcvbulkpipe(umas->pusb_dev, umas->ep_in_num));
    clear_halt(umas->pusb_dev, usb_sndbulkpipe(umas->pusb_dev, umas->ep_out_num));

    UMAS_VDEBUG("Bulk soft reset completed\n");
    return SUCCESS;
}

