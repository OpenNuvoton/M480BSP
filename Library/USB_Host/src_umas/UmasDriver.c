/* Driver for USB Mass Storage compliant devices
 *
 * $Id: usb.c,v 1.61 2001/01/13 00:10:59 mdharm Exp $
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
 * usb_device_id support by Adam J. Richter (adam@yggdrasil.com):
 *   (c) 2000 Yggdrasil Computing, Inc.
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
 *
 *  MODULE_AUTHOR("Matthew Dharm <mdharm-usb@one-eyed-alien.net>");
 *  MODULE_DESCRIPTION("USB Mass Storage driver for Linux");
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "M480.h"

#include "Umas.h"
#include "UmasProtocol.h"
#include "UmasTransport.h"


extern void  fatfs_drive_int(void);
extern void  fatfs_drive_free(FATFS_DRV_T *fdrv);


/* This places the Shuttle/SCM USB<->SCSI bridge devices in multi-target
 * mode */


/*
 * The entries in this table, except for final ones here
 * (USB_MASS_STORAGE_CLASS and the empty entry), correspond,
 * line for line with the entries of us_unsuaul_dev_list[].
 * For now, we duplicate idVendor and idProduct in us_unsual_dev_list,
 * just to avoid alignment bugs.
 */

#define UNUSUAL_DEV(id_vendor, id_product, bcdDeviceMin, bcdDeviceMax, \
                    vendorName, productName,useProtocol, useTransport, \
                    initFunction, flags) \
USB_DEVICE_VER(id_vendor, id_product, bcdDeviceMin,bcdDeviceMax)

static struct usb_device_id  _UmasDeviceIDs[] = {
//#include "unusual_devs.h"
#undef UNUSUAL_DEV
    /* Control/Bulk transport for all SubClass values */
    USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, UMAS_SC_RBC, UMAS_PR_CB),
    USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, UMAS_SC_8020, UMAS_PR_CB),
    USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, UMAS_SC_QIC, UMAS_PR_CB),
    USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, UMAS_SC_UFI, UMAS_PR_CB),
    USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, UMAS_SC_8070, UMAS_PR_CB),
    USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, UMAS_SC_SCSI, UMAS_PR_CB),

    /* Control/Bulk/Interrupt transport for all SubClass values */
    USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, UMAS_SC_RBC, UMAS_PR_CBI),
    USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, UMAS_SC_8020, UMAS_PR_CBI),
    USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, UMAS_SC_QIC, UMAS_PR_CBI),
    USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, UMAS_SC_UFI, UMAS_PR_CBI),
    USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, UMAS_SC_8070, UMAS_PR_CBI),
    USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, UMAS_SC_SCSI, UMAS_PR_CBI),

    /* Bulk-only transport for all SubClass values */
    USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, UMAS_SC_RBC, UMAS_PR_BULK),
    USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, UMAS_SC_8020, UMAS_PR_BULK),
    USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, UMAS_SC_QIC, UMAS_PR_BULK),
    USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, UMAS_SC_UFI, UMAS_PR_BULK),
    USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, UMAS_SC_8070, UMAS_PR_BULK),
    USB_INTERFACE_INFO(USB_CLASS_MASS_STORAGE, UMAS_SC_SCSI, UMAS_PR_BULK),

    /* Terminating entry */
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
};


/* This is the list of devices we recognize, along with their flag data */

/*
 * The vendor name should be kept at eight characters or less, and
 * the product name should be kept at 16 characters or less. If a device
 * has the UMAS_FL_DUMMY_INQUIRY flag, then the vendor and product names
 * normally generated by a device thorugh the INQUIRY response will be
 * taken from this list, and this is the reason for the above size
 * restriction. However, if the flag is not present, then you
 * are free to use as many characters as you like.
 */

#undef UNUSUAL_DEV
#define UNUSUAL_DEV(idVendor, idProduct, bcdDeviceMin, bcdDeviceMax, \
                    vendor_name, product_name, use_protocol, use_transport, \
                    init_function, Flags) \
{ vendor_name, product_name, use_protocol, use_transport, init_function, Flags }

static UMAS_UUDEV_T  _UmasUUDevList[] =    /* LINUX: us_unusual_dev_list */
{
//#include "unusual_devs.h"
#undef UNUSUAL_DEV
    /* Control/Bulk transport for all SubClass values */
    { 0, 0, UMAS_SC_RBC,  UMAS_PR_CB,   0, 0 },
    { 0, 0, UMAS_SC_8020, UMAS_PR_CB,   0, 0 },
    { 0, 0, UMAS_SC_QIC,  UMAS_PR_CB,   0, 0 },
    { 0, 0, UMAS_SC_UFI,  UMAS_PR_CB,   0, 0 },
    { 0, 0, UMAS_SC_8070, UMAS_PR_CB,   0, 0 },
    { 0, 0, UMAS_SC_SCSI, UMAS_PR_CB,   0, 0 },

    /* Control/Bulk/Interrupt transport for all SubClass values */
    { 0, 0, UMAS_SC_RBC,  UMAS_PR_CBI,  0, 0 },
    { 0, 0, UMAS_SC_8020, UMAS_PR_CBI,  0, 0 },
    { 0, 0, UMAS_SC_QIC,  UMAS_PR_CBI,  0, 0 },
    { 0, 0, UMAS_SC_UFI,  UMAS_PR_CBI,  0, 0 },
    { 0, 0, UMAS_SC_8070, UMAS_PR_CBI,  0, 0 },
    { 0, 0, UMAS_SC_SCSI, UMAS_PR_CBI,  0, 0 },

    /* Bulk-only transport for all SubClass values */
    { 0, 0, UMAS_SC_RBC,  UMAS_PR_BULK, 0, 0 },
    { 0, 0, UMAS_SC_8020, UMAS_PR_BULK, 0, 0 },
    { 0, 0, UMAS_SC_QIC,  UMAS_PR_BULK, 0, 0 },
    { 0, 0, UMAS_SC_UFI,  UMAS_PR_BULK, 0, 0 },
    { 0, 0, UMAS_SC_8070, UMAS_PR_BULK, 0, 0 },
    { 0, 0, UMAS_SC_SCSI, UMAS_PR_BULK, 0, 0 },

    /* Terminating entry */
    { 0 }
};



/* The list of structures and the protective lock for them */
UMAS_DATA_T  *_UmasDeviceList;

static int   storage_probe(struct usb_interface *intf, const struct usb_device_id *id);
static void  storage_disconnect(struct usb_interface *intf);

struct usb_driver  _UsbMassStorageDriver = {
    "UMAS",
    storage_probe,
    storage_disconnect,
    NULL,                       /* suspend */
    NULL,                       /* resume */
    NULL,                       /* reset_resume */
    NULL,                       /* pre_reset */
    NULL,                       /* post_reset */
    _UmasDeviceIDs
    //{},
    //{},
    //1
};


#if 0
/*
 *  UMAS_FillInquiryResponse takes an uint8_t array (which must
 *  be at least 36 characters) and populates the vendor name,
 *  product name, and revision fields. Then the array is copied
 *  into the SCSI command's response buffer (oddly enough
 *  called request_buff). data_len contains the length of the
 *  data array, which again must be at least 36.
 */

void  UMAS_FillInquiryResponse(UMAS_DATA_T *umas, uint8_t *data, uint32_t data_len)
{
    int    i;
    SCATTER_LIST_T  *sg;
    int    len = umas->srb->request_bufflen > data_len ? data_len :
                 umas->srb->request_bufflen;
    int    transferred;
    int    amt;

    if (data_len < 36) // You lose.
        return;

    /* vendor name, product name, revision field */
    memcpy(data+8, umas->unusual_dev->vendorName,
           strlen(umas->unusual_dev->vendorName) > 8 ? 8 : strlen(umas->unusual_dev->vendorName));
    memcpy(data+16, umas->unusual_dev->productName,
           strlen(umas->unusual_dev->productName) > 16 ? 16 : strlen(umas->unusual_dev->productName));
    data[32] = 0x30 + ((umas->pusb_dev->descriptor.bcdDevice>>12) & 0x0F);
    data[33] = 0x30 + ((umas->pusb_dev->descriptor.bcdDevice>>8) & 0x0F);
    data[34] = 0x30 + ((umas->pusb_dev->descriptor.bcdDevice>>4) & 0x0F);
    data[35] = 0x30 + ((umas->pusb_dev->descriptor.bcdDevice) & 0x0F);

    if (umas->srb->use_sg) {
        sg = (SCATTER_LIST_T *)umas->srb->request_buff;

        for (i = 0; i < umas->srb->use_sg; i++)
            memset(sg[i].address, 0, sg[i].length);

        for (i = 0, transferred = 0; (i < umas->srb->use_sg) && (transferred < len); i++) {
            amt = sg[i].length > len-transferred ? len-transferred : sg[i].length;
            memcpy(sg[i].address, data+transferred, amt);
            transferred -= amt;
        }
    } else {
        memset(umas->srb->request_buff, 0, umas->srb->request_bufflen);
        memcpy(umas->srb->request_buff, data, len);
    }
}
#endif


/*
 * Set up the IRQ pipe and handler
 * Note that this function assumes that all the data in the umas_data
 * strucuture is current.  This includes the ep_int field, which gives umas
 * the endpoint for the interrupt.
 * Returns non-zero on failure, zero on success
 */
static int  usb_stor_allocate_irq(UMAS_DATA_T *umas)
{
    uint32_t  pipe;
    int     maxp;
    int     result;

    UMAS_DEBUG("Allocating IRQ for CBI transport\n");

    /* allocate the URB */
    umas->irq_urb = usb_alloc_urb(0,0);
    if (!umas->irq_urb) {
        UMAS_DEBUG("couldn't allocate interrupt URB");
        return 1;
    }

    umas->irqbuf = USB_malloc(2, BOUNDARY_WORD);

    /* calculate the pipe and max packet size */
    pipe = usb_rcvintpipe(umas->pusb_dev, umas->ep_int->desc.bEndpointAddress &
                          USB_ENDPOINT_NUMBER_MASK);
    maxp = usb_maxpacket(umas->pusb_dev, pipe, usb_pipeout(pipe));
    if (maxp > sizeof(umas->irqbuf))
        maxp = sizeof(umas->irqbuf);

    /* fill in the URB with our data */
    usb_fill_int_urb(umas->irq_urb, umas->pusb_dev, pipe, umas->irqbuf, maxp,
                     UMAS_CbiIrq, umas, umas->ep_int->desc.bInterval);   /* UMAS_CbiIrq() in UmasTransport.c */

    umas->ip_wanted = 1;
    /* submit the URB for processing */
    result = usb_submit_urb(umas->irq_urb, 0);
    if (result) {
        usb_free_urb(umas->irq_urb);
        result = 2;
    }
    return result;
}



/* Probe to see if a new device is actually a SCSI device */
static int  storage_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
    struct usb_host_interface *desc;
    struct usb_device *dev;
    int    i;
    const  int id_index = id - _UmasDeviceIDs;
    char   mf[USB_STOR_STRING_LEN];    /* manufacturer */
    char   prod[USB_STOR_STRING_LEN];  /* product */
    char   serial[USB_STOR_STRING_LEN];/* serial number */
    GUID(guid);                        /* Global Unique Identifier */
    uint32_t flags;
    UMAS_UUDEV_T  *unusual_dev;
    UMAS_DATA_T    *umas = NULL;

    /*
     * These are temporary copies -- we test on these, then put them
     * in the umas-data structure
     */
    struct usb_host_endpoint  *ep_in = NULL;
    struct usb_host_endpoint  *ep_out = NULL;
    struct usb_host_endpoint  *ep_int = NULL;
    uint8_t   subclass = 0;
    uint8_t   protocol = 0;
    /*
     * The altsettting on the interface we're probing that matched our
     * usb_match_id table
     */
    desc = intf->cur_altsetting;
    dev = interface_to_usbdev(intf);

    UMAS_DEBUG("act_altsettting is %d\n", desc->desc.bInterfaceNumber);
    /* clear the temporary strings */
    memset(mf, 0, sizeof(mf));
    memset(prod, 0, sizeof(prod));
    memset(serial, 0, sizeof(serial));

    /*
     * Can we support this device, either because we know about it
     * from our unusual device list, or because it advertises that it's
     * compliant to the specification?
     *
     * id_index is calculated in the declaration to be the index number
     * of the match from the usb_device_id table, so we can find the
     * corresponding entry in the private table.
     */
    UMAS_DEBUG("id_index calculated to be: %d\n", id_index);
    UMAS_DEBUG("Array length appears to be: %d\n", sizeof(_UmasUUDevList) / sizeof(_UmasUUDevList[0]));

    if (id_index < sizeof(_UmasUUDevList) / sizeof(_UmasUUDevList[0])) {
        unusual_dev = &_UmasUUDevList[id_index];
        if (unusual_dev->vendorName)
            UMAS_DEBUG("Vendor: %s\n", unusual_dev->vendorName);
        if (unusual_dev->productName)
            UMAS_DEBUG("Product: %s\n", unusual_dev->productName);
    } else
        /* no, we can't support it */
        return NULL;

    /* At this point, we know we've got a live one */
    UMAS_DEBUG("USB Mass Storage device detected\n");

    /* Determine subclass and protocol, or copy from the interface */
    subclass = unusual_dev->useProtocol;
    protocol = unusual_dev->useTransport;
    flags = unusual_dev->flags;

    /*
     * Find the endpoints we need
     * We are expecting a minimum of 2 endpoints - in and out (bulk).
     * An optional interrupt is OK (necessary for CBI protocol).
     * We will ignore any others.
     */
    for (i = 0; i < desc->desc.bNumEndpoints; i++) {
        /* is it an BULK endpoint? */
        if ((desc->endpoint[i].desc.bmAttributes &
                USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_BULK) {
            /* BULK in or out? */
            if (desc->endpoint[i].desc.bEndpointAddress & USB_DIR_IN)
                ep_in = &(desc->endpoint[i]);
            else
                ep_out = &(desc->endpoint[i]);
        }

        /* is it an interrupt endpoint? */
        if ((desc->endpoint[i].desc.bmAttributes &
                USB_ENDPOINT_XFERTYPE_MASK) == USB_ENDPOINT_XFER_INT) {
            ep_int = &(desc->endpoint[i]);
        }
    }

    UMAS_DEBUG("Endpoints: In: 0x%x Out: 0x%x Int: 0x%x (Period %d)\n",
               ep_in, ep_out, ep_int, ep_int ? ep_int->desc.bInterval : 0);

    /* Do some basic sanity checks, and bail if we find a problem */
    if (!ep_in || !ep_out || ((protocol == UMAS_PR_CBI) && !ep_int)) {
        UMAS_DEBUG("Endpoint sanity check failed! Rejecting dev.\n");
        return NULL;
    }

    /* At this point, we're committed to using the device */
    //USB_IncreaseDeviceUser(dev);

    /* clear the GUID and fetch the strings */
    GUID_CLEAR(guid);

    /* Create a GUID for this device */
    if (dev->descriptor.iSerialNumber && serial[0]) {
        /* If we have a serial number, and it's a non-NULL string */
        make_guid(guid, dev->descriptor.idVendor, dev->descriptor.idProduct, serial);
    } else {
        /* We don't have a serial number, so we use 0 */
        make_guid(guid, dev->descriptor.idVendor, dev->descriptor.idProduct, "0");
    }

    /*
     * Now check if we have seen this GUID before
     * We're looking for a device with a matching GUID that isn't
     * already on the system
     */
    umas = _UmasDeviceList;
    while ((umas != NULL) && ((umas->pusb_dev) || !GUID_EQUAL(guid, umas->guid)))
        umas = umas->next;

    if (umas != NULL) {
        /* Existing device -- re-connect */
        UMAS_DEBUG("Found existing GUID " GUID_FORMAT "\n", GUID_ARGS(guid));


        /* establish the connection to the new device upon reconnect */
        umas->intf = intf;
        umas->pusb_dev = dev;

        /* copy over the endpoint data */
        if (ep_in)
            umas->ep_in_num = ep_in->desc.bEndpointAddress & USB_ENDPOINT_NUMBER_MASK;
        if (ep_out)
            umas->ep_out_num = ep_out->desc.bEndpointAddress & USB_ENDPOINT_NUMBER_MASK;
        umas->ep_int = ep_int;

        /* allocate an IRQ callback if one is needed */
        if ((umas->protocol == UMAS_PR_CBI) && usb_stor_allocate_irq(umas)) {
            USB_DecreaseDeviceUser(dev);
            return NULL;
        }

        /* allocate the URB we're going to use */
        umas->current_urb = usb_alloc_urb(0,0);
        if (!umas->current_urb) {
            USB_DecreaseDeviceUser(dev);
            return NULL;
        }

        /* Re-Initialize the device if it needs it */
        if (unusual_dev && unusual_dev->initFunction)
            (unusual_dev->initFunction)(umas);
    } else { /* umas == NULL */
        /* New device -- allocate memory and initialize */
        UMAS_DEBUG("New GUID " GUID_FORMAT "\n", GUID_ARGS(guid));

        umas = (UMAS_DATA_T *)USB_malloc(sizeof(UMAS_DATA_T), BOUNDARY_WORD);
        if (umas == NULL) {
            UMAS_DEBUG("Out of memory\n");
            USB_DecreaseDeviceUser(dev);
            return NULL;
        }
        memset((char *)umas, 0, sizeof(UMAS_DATA_T));

        umas->srb = (SCSI_CMD_T *)USB_malloc(sizeof(SCSI_CMD_T), BOUNDARY_WORD);
        if (umas->srb == NULL) {
            UMAS_DEBUG("Out of memory\n");
            USB_free(umas);
            USB_DecreaseDeviceUser(dev);
            return NULL;
        }

        /* allocate the URB we're going to use */
        umas->current_urb = usb_alloc_urb(0,0);
        if (!umas->current_urb) {
            USB_free(umas->srb);
            USB_free(umas);
            USB_DecreaseDeviceUser(dev);
            return NULL;
        }

        /* copy over the subclass and protocol data */
        umas->subclass = subclass;
        umas->protocol = protocol;
        umas->flags = flags;
        umas->unusual_dev = unusual_dev;

        /* copy over the endpoint data */
        if (ep_in)
            umas->ep_in_num = ep_in->desc.bEndpointAddress & USB_ENDPOINT_NUMBER_MASK;
        if (ep_out)
            umas->ep_out_num = ep_out->desc.bEndpointAddress & USB_ENDPOINT_NUMBER_MASK;
        umas->ep_int = ep_int;

        /* establish the connection to the new device */
        umas->intf = intf;
        umas->pusb_dev = dev;

        /* copy over the identifiying strings */
        strncpy(umas->vendor, mf, USB_STOR_STRING_LEN);
        strncpy(umas->product, prod, USB_STOR_STRING_LEN);
        strncpy(umas->serial, serial, USB_STOR_STRING_LEN);
        if (strlen(umas->vendor) == 0) {
            if (unusual_dev->vendorName)
                strncpy(umas->vendor, unusual_dev->vendorName, USB_STOR_STRING_LEN);
            else
                strncpy(umas->vendor, "Unknown", USB_STOR_STRING_LEN);
        }
        if (strlen(umas->product) == 0) {
            if (unusual_dev->productName)
                strncpy(umas->product, unusual_dev->productName, USB_STOR_STRING_LEN);
            else
                strncpy(umas->product, "Unknown", USB_STOR_STRING_LEN);
        }
        if (strlen(umas->serial) == 0)
            strncpy(umas->serial, "None", USB_STOR_STRING_LEN);

        /* copy the GUID we created before */
        memcpy(umas->guid, guid, sizeof(guid));

        /*
         * Set the handler pointers based on the protocol
         * Again, this data is persistant across reattachments
         */
        switch (umas->protocol) {
        case UMAS_PR_CB:
            umas->transport_name = "Control/Bulk";
            umas->transport = UMAS_CbTransport;
            umas->transport_reset = UMAS_CbReset;
            umas->max_lun = 7;
            break;

        case UMAS_PR_CBI:
            umas->transport_name = "Control/Bulk/Interrupt";
            umas->transport = UMAS_CbiTransport;
            umas->transport_reset = UMAS_CbReset;
            umas->max_lun = 7;
            break;

        case UMAS_PR_BULK:
            umas->transport_name = "Bulk-only";
            umas->transport = UMAS_BulkTransport;
            umas->transport_reset = UMAS_BulkReset;
            umas->max_lun = UMAS_BulkMaxLun(umas);
            UMAS_DEBUG("Bulk max logical unit number: %d\n", umas->max_lun);
            break;

#ifdef CONFIG_USB_STORAGE_FREECOM
        case UMAS_PR_FREECOM:
            umas->transport_name = "Freecom";
            umas->transport = freecom_transport;
            umas->transport_reset = usb_stor_freecom_reset;
            umas->max_lun = 0;
            break;
#endif

        default:
            umas->transport_name = "Unknown";
            goto err_ret;
            //USB_DecreaseDeviceUser(dev);
            //return NULL;
            //break;
        } /* end of switch */
        UMAS_DEBUG("Mass storage transport: %s\n", umas->transport_name);

        /* fix for single-lun devices */
        if (umas->flags & UMAS_FL_SINGLE_LUN)
            umas->max_lun = 0;

        switch (umas->subclass) {
        case UMAS_SC_RBC:
            umas->protocol_name = "Reduced Block Commands (RBC)";
            umas->proto_handler = UMAS_TransparentScsiCommand;
            break;

        case UMAS_SC_8020:
            umas->protocol_name = "8020i";
            umas->proto_handler = UMAS_AtapiCommand;
            umas->max_lun = 0;
            break;

        case UMAS_SC_QIC:
            umas->protocol_name = "QIC-157";
            umas->proto_handler = UMAS_Qic157Command;
            umas->max_lun = 0;
            break;

        case UMAS_SC_8070:
            umas->protocol_name = "8070i";
            umas->proto_handler = UMAS_AtapiCommand;
            umas->max_lun = 0;
            break;

        case UMAS_SC_SCSI:
            umas->protocol_name = "Transparent SCSI";
            umas->proto_handler = UMAS_TransparentScsiCommand;
            break;

        case UMAS_SC_UFI:
            umas->protocol_name = "Uniform Floppy Interface (UFI)";
            umas->proto_handler = UMAS_UfiCommand;
            break;

        default:
            umas->protocol_name = "Unknown";
            goto err_ret;
        } /* end of switch */
        UMAS_DEBUG("Mass storage protocol: %s\n", umas->protocol_name);

        /* allocate an IRQ callback if one is needed */
        if ((umas->protocol == UMAS_PR_CBI) && usb_stor_allocate_irq(umas)) {
            //USB_DecreaseDeviceUser(dev);
            return NULL;
        }

        /*
         * Since this is a new device, we need to generate a scsi
         * host definition, and register with the higher SCSI layers
         */

        /* Initialize the host template based on the default one */
        //memcpy(&(umas->htmplt), &usb_stor_host_template, sizeof(usb_stor_host_template));

        /* Grab the next host number */
        //umas->host_number = _MyHostNumber++;

        /*
         * We abuse this pointer so we can pass the umas pointer to
         * the host controller thread in us_detect.  But how else are
         * we to do it?
         */
        //(UMAS_DATA_T *)umas->htmplt.proc_dir = umas;

        /*
         * Just before we start our control thread, initialize
         * the device if it needs initialization
         */
        if (unusual_dev && unusual_dev->initFunction)
            unusual_dev->initFunction(umas);

        /* put umas in the list */
        umas->next = _UmasDeviceList;
        _UmasDeviceList = umas;
    }

    intf->priv = umas;

    UMAS_DEBUG("WARNING: USB Mass Storage data integrity not assured\n");
    UMAS_DEBUG("USB Mass Storage device found at %d\n", dev->devnum);

    if (UMAS_InitUmasDevice(umas) < 0)
        goto err_ret;

    /* return a pointer for the disconnect function */
    return 0;

err_ret:
    usb_free_urb(umas->current_urb);
    USB_free(umas->srb);
    USB_free(umas);
    USB_DecreaseDeviceUser(dev);
    return NULL;
}



/* Handle a disconnect event from the USB core */
static void storage_disconnect(struct usb_interface *intf)
{
    UMAS_DATA_T     *umas = intf->priv;
    UMAS_DRIVE_T    *umas_drive, *next_drv;
    UMAS_DATA_T     *p;
    int             result;

    UMAS_DEBUG("storage_disconnect called\n");

    /* this is the odd case -- we disconnected but weren't using it */
    if (!umas) {
        UMAS_DEBUG("storage_disconnect -- device was not in use\n");
        return;
    }

    /* Unmount disk */
    umas_drive = umas->drive_list;
    while (umas_drive != NULL) {
        next_drv = umas_drive->next;
        fatfs_drive_free((FATFS_DRV_T *)umas_drive->client);
        kfree(umas_drive);
        umas_drive = next_drv;
    }

    if (umas->irq_urb) {
        UMAS_DEBUG("storage_disconnect -- releasing irq URB\n");
        result = usb_unlink_urb(umas->irq_urb);
        UMAS_DEBUG("storage_disconnect -- usb_unlink_urb() returned %d\n", result);
        usb_free_urb(umas->irq_urb);
        umas->irq_urb = NULL;
    }

    /* free up the main URB for this device */
    UMAS_DEBUG("storage_disconnect -- releasing main URB\n");
    result = usb_unlink_urb(umas->current_urb);
    UMAS_DEBUG("storage_disconnect -- usb_unlink_urb() returned %d\n", result);
    usb_free_urb(umas->current_urb);
    umas->current_urb = NULL;

    /* mark the device as gone */
    USB_DecreaseDeviceUser(umas->pusb_dev);
    umas->pusb_dev = NULL;

    if (umas == _UmasDeviceList) {
        _UmasDeviceList = umas->next;
    } else {
        p = _UmasDeviceList;
        while ((p->next != NULL) && (p->next != umas))
            p = p->next;

        if (p->next != NULL)
            p->next = umas->next;
    }

    /* release memory allocated by it */
    if (umas->srb->request_buff != NULL)
        USB_free(umas->srb->request_buff);
    USB_free(umas->srb);
    if (umas->irqbuf != NULL)
        USB_free(umas->irqbuf);
    USB_free(umas);
}



/**
  * @brief       Register and initialize USB Host Mass Storage driver.
  *
  * @retval      0    Success.
  * @retval      1    Failed.
  */
int  usbh_umas_init(void)
{
    fatfs_drive_int();

    /* initialize internal global data elements */
    _UmasDeviceList = NULL;

    /* register the driver, return -1 if error */
    if (usb_register_driver(&_UsbMassStorageDriver, "UMAS") < 0)
        return -1;

    /* we're all set */
    UMAS_DEBUG("USB Mass Storage support registered.\n");
    return 0;
}


void  UMAS_RemoveUmasDriver(void)
{
    UMAS_DATA_T *next;

    /*
     * Deregister the driver
     * This eliminates races with probes and disconnects
     */
    usb_deregister(&_UsbMassStorageDriver) ;

    /*
     * While there are still structures, free them.  Note that we are
     * now race-free, since these structures can no longer be accessed
     * from either the SCSI command layer or the /proc interface
     */
    while (_UmasDeviceList) {
        /* keep track of where the next one is */
        next = _UmasDeviceList->next;

        /* If there's extra data in the umas_data structure then free that first */
        if (_UmasDeviceList->extra) {
            /* call the destructor routine, if it exists */
            if (_UmasDeviceList->extra_destructor) {
                UMAS_DEBUG("-- calling extra_destructor()\n");
                _UmasDeviceList->extra_destructor(_UmasDeviceList->extra);
            }

            /* destroy the extra data */
            UMAS_DEBUG("-- freeing the data structure\n");
            USB_free(_UmasDeviceList->extra);
        }

        /* free the structure itself */
        USB_free (_UmasDeviceList);

        /* advance the list pointer */
        _UmasDeviceList = next;
    } /* end of while */
}

