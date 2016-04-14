/* Driver for USB Mass Storage compliant devices
 * Main Header File
 *
 * $Id: usb.h,v 1.12 2000/12/05 03:33:49 mdharm Exp $
 *
 * Current development and maintenance by:
 *   (c) 1999, 2000 Matthew Dharm (mdharm-usb@one-eyed-alien.net)
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

#ifndef _UMAS_H_
#define _UMAS_H_

#ifndef _USB_H_
#include "usb.h"
#endif

#include "UmasScsi.h"

/// @cond HIDDEN_SYMBOLS


#undef DEBUG
#define DEBUG
//#define UMAS_VERBOSE_DEBUG

/* Debug Options */
#ifdef UMAS_VERBOSE_DEBUG
#define UMAS_DEBUG    printf
#define UMAS_VDEBUG   printf
#else
#ifdef DEBUG
#define UMAS_DEBUG    printf
#else
#define UMAS_DEBUG(...)
#endif
#define UMAS_VDEBUG(...)
#endif


#define umas_get_ticks()   get_ticks()

#define USB_DecreaseDeviceUser(x)
#define USB_IncreaseDeviceUser(x)

/*
 * GUID definitions
 */

#define GUID(x)            uint32_t x[3]
#define GUID_EQUAL(x, y)   (x[0] == y[0] && x[1] == y[1] && x[2] == y[2])
#define GUID_CLEAR(x)      x[0] = x[1] = x[2] = 0;
#define GUID_NONE(x)       (!x[0] && !x[1] && !x[2])
#define GUID_FORMAT        "%08x%08x%08x"
#define GUID_ARGS(x)       x[0], x[1], x[2]

static __inline void  make_guid(uint32_t *pg, uint16_t vendor, uint16_t product, char *serial)
{
    pg[0] = (vendor << 16) | product;
    pg[1] = pg[2] = 0;
    while (*serial) {
        pg[1] <<= 4;
        pg[1] |= pg[2] >> 28;
        pg[2] <<= 4;
        if (*serial >= 'a')
            *serial -= 'a' - 'A';
        pg[2] |= (*serial <= '9' && *serial >= '0') ? *serial - '0' : *serial - 'A' + 10;
        serial++;
    }
}

struct umas_data;

/*
 * Unusual device list definitions
 */

typedef struct umas_unusual_dev {
    const char*  vendorName;
    const char*  productName;
    uint8_t   useProtocol;
    uint8_t   useTransport;
    int     (*initFunction)(struct umas_data *);
    uint32_t  flags;
} UMAS_UUDEV_T;


/* Flag definitions */
#define UMAS_FL_SINGLE_LUN      0x00000001  /* allow access to only LUN 0      */
#define UMAS_FL_MODE_XLATE      0x00000002  /* translate _6 to _10 commands for
                                                Win/MacOS compatibility */
#define UMAS_FL_START_STOP      0x00000004  /* ignore START_STOP commands      */
#define UMAS_FL_IGNORE_SER      0x00000010  /* Ignore the serial number given  */
#define UMAS_FL_SCM_MULT_TARG   0x00000020  /* supports multiple targets */

#define USB_STOR_STRING_LEN   256

typedef int  (*trans_cmnd)(SCSI_CMD_T *, struct umas_data *);
typedef int  (*trans_reset)(struct umas_data *);
typedef void (*proto_cmnd)(SCSI_CMD_T*, struct umas_data *);
typedef void (*extra_data_destructor)(void *);   /* extra data destructor   */


struct umas_drive;

/* we allocate one of these for every device that we remember */
typedef struct umas_data {             /* LINUX: struct us_data */
    struct umas_data  *next;           /* next device */
    struct usb_device *pusb_dev;       /* this usb_device */
    uint32_t        flags;               /* from filter initially */

    /* information about the device -- always good */
    char          vendor[USB_STOR_STRING_LEN];
    char          product[USB_STOR_STRING_LEN];
    char          serial[USB_STOR_STRING_LEN];
    char          *transport_name;
    char          *protocol_name;
    uint8_t         subclass;
    uint8_t         protocol;
    uint8_t         max_lun;

    /* information about the device -- only good if device is attached */
    struct usb_interface *intf;        /* interface */
    uint8_t         ep_in_num;           /* bulk in endpoint number  */
    uint8_t         ep_out_num;          /* bulk out endpoint number */
    struct usb_host_endpoint *ep_int;  /* interrupt endpoint description */

    /* function pointers for this device */
    trans_cmnd    transport;           /* transport function     */
    trans_reset   transport_reset;     /* transport device reset */
    proto_cmnd    proto_handler;       /* protocol handler       */

    /* SCSI interfaces */
    GUID(guid);                        /* unique dev id       */
    SCSI_CMD_T    *srb;                /* current srb         */

    int           ip_wanted;           /* is an IRQ expected? (atomic_t) */
    struct urb    *current_urb;        /* non-int USB requests */
    struct urb    *irq_urb;            /* for USB int requests */
    uint8_t         *irqbuf;             /* buffer for USB IRQ   */
    uint8_t         irqdata[2];          /* data from USB IRQ    */

    UMAS_UUDEV_T  *unusual_dev;        /* If unusual device       */
    void          *extra;              /* Any extra data          */
    extra_data_destructor   extra_destructor;  /* extra data destructor   */
    struct umas_drive  *drive_list;
} UMAS_DATA_T;


typedef struct umas_drive {
    UMAS_DATA_T     *umas;
    uint8_t         lun_no;
    void            *client;           /* file system client data */
    struct umas_drive  *next;          /* next device */
} UMAS_DRIVE_T;


typedef struct {
    int        used;
    int        drv_no;
    UMAS_DRIVE_T  *umas_drv;
    uint32_t     uTotalSectorN;
    int        nSectorSize;
    uint32_t     uDiskSize;
}  FATFS_DRV_T;


#define USBDRV_0            3
#define USBDRV_MAX          7

#define USBDRV_CNT          (USBDRV_MAX - USBDRV_0 + 1)


/*======================================================= Global Variables ==*/
/* The list of structures and the protective lock for them */
extern UMAS_DATA_T  *_UmasDeviceList;   /* LINUX: us_list */

/* The structure which defines our driver */
extern struct usb_driver  _UsbMassStorageDriver;   /* LINUX: usb_storage_driver */


/*===================================================== Exported Functions ==*/
extern int  umas_init(void);
extern void UMAS_RemoveUmasDriver(void);

extern int  UMAS_InitUmasDevice(UMAS_DATA_T *umas);

extern void UMAS_ScanAllDevice(void);
extern void UMAS_ScanDeviceLun(UMAS_DATA_T *umas);

/*
 * Debug helper routines, in UsbDebug.c
 */
extern void UMAS_DEBUG_ShowCommand(SCSI_CMD_T   *srb);
extern void UMAS_DEBUG_PrintScsiCommand(SCSI_CMD_T *cmd);
extern void UMAS_DEBUG_ShowSense(uint8_t key, uint8_t asc, uint8_t ascq);

/// @endcond HIDDEN_SYMBOLS

#endif  /* _UMAS_H_ */
