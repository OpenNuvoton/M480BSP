/*
 * drivers/usb/core/endpoint.c
 *
 * (C) Copyright 2002,2004,2006 Greg Kroah-Hartman
 * (C) Copyright 2002,2004 IBM Corp.
 * (C) Copyright 2006 Novell Inc.
 *
 * Endpoint sysfs stuff
 *
 */

/**************************************************************************//**
 * @file     endpoint.c
 * @version  V1.10
 * $Revision: 11 $
 * $Date: 14/10/03 1:54p $
 * @brief  Ported from Linux USB host driver.
 *
 * @note
 * Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "M480.h"

#include "usb.h"

/// @cond HIDDEN_SYMBOLS

#if 0
#define DEVICE_ATTR(_name, _mode, _show, _store) \
         struct device_attribute dev_attr_##_name = __ATTR(_name, _mode, _show, _store)
#endif

struct ep_device {
    struct usb_endpoint_descriptor *desc;
    struct usb_device *udev;
    struct device dev;
};


#ifdef NUVOTON_PORTED
inline  struct ep_device * to_ep_device(struct device *dev)
{
    struct ep_device *epdev;
    epdev = (struct ep_device *)0;
    return (struct ep_device *)((__u32)dev - (__u32)&(epdev->dev));
}
#else
#define to_ep_device(_dev) \
    container_of(_dev, struct ep_device, dev)
#endif


struct device_type usb_ep_device_type = {
    "usb_endpoint"
};

struct ep_attribute {
    struct attribute attr;
    ssize_t (*show)(struct usb_device *,
                    struct usb_endpoint_descriptor *, char *);
};


#if 0
#define to_ep_attribute(_attr) \
    container_of(_attr, struct ep_attribute, attr)
#endif


#if 0
#define usb_ep_attr(field, format_string)           \
static ssize_t show_ep_##field(struct device *dev,      \
                   struct device_attribute *attr,   \
                   char *buf)           \
{                               \
    struct ep_device *ep = to_ep_device(dev);       \
    return sprintf(buf, format_string, ep->desc->field);    \
}                               \
static DEVICE_ATTR(field, S_IRUGO, show_ep_##field, NULL);

usb_ep_attr(bLength, "%02x\n")
usb_ep_attr(bEndpointAddress, "%02x\n")
usb_ep_attr(bmAttributes, "%02x\n")
usb_ep_attr(bInterval, "%02x\n")

#else

static ssize_t show_ep_bLength(struct device *dev,
                               struct device_attribute *attr, char *buf)
{
    struct ep_device *ep;
    ep = to_ep_device(dev);
    return sprintf(buf, "%02x\n", ep->desc->bLength);
}
struct device_attribute dev_attr_bLength = {
    "bLength", 0, show_ep_bLength, NULL
};

static ssize_t show_ep_bEndpointAddress(struct device *dev,
                                        struct device_attribute *attr, char *buf)
{
    struct ep_device *ep;
    ep = to_ep_device(dev);
    return sprintf(buf, "%02x\n", ep->desc->bEndpointAddress);
}
struct device_attribute dev_attr_bEndpointAddress = {
    "bEndpointAddress", 0, show_ep_bEndpointAddress, NULL
};

static ssize_t show_ep_bmAttributes(struct device *dev,
                                    struct device_attribute *attr, char *buf)
{
    struct ep_device *ep;
    ep = to_ep_device(dev);
    return sprintf(buf, "%02x\n", ep->desc->bmAttributes);
}
struct device_attribute dev_attr_bmAttributes = {
    "bmAttributes", 0, show_ep_bmAttributes, NULL
};

static ssize_t show_ep_bInterval(struct device *dev,
                                 struct device_attribute *attr, char *buf)
{
    struct ep_device *ep;
    ep = to_ep_device(dev);
    return sprintf(buf, "%02x\n", ep->desc->bInterval);
}
struct device_attribute dev_attr_bInterval = {
    "bInterval", 0, show_ep_bInterval, NULL
};

#endif


static ssize_t show_ep_wMaxPacketSize(struct device *dev,
                                      struct device_attribute *attr, char *buf)
{
    struct ep_device *ep;
    ep = to_ep_device(dev);
    return sprintf(buf, "%04x\n",
                   usb_endpoint_maxp(ep->desc) & 0x07ff);
}
struct device_attribute dev_attr_wMaxPacketSize = {
    "wMaxPacketSize", 0, show_ep_wMaxPacketSize, NULL
};

static ssize_t show_ep_type(struct device *dev, struct device_attribute *attr,
                            char *buf)
{
    struct ep_device *ep;
    char *type = "unknown";

    ep = to_ep_device(dev);

    switch (usb_endpoint_type(ep->desc)) {
    case USB_ENDPOINT_XFER_CONTROL:
        type = "Control";
        break;
    case USB_ENDPOINT_XFER_ISOC:
        type = "Isoc";
        break;
    case USB_ENDPOINT_XFER_BULK:
        type = "Bulk";
        break;
    case USB_ENDPOINT_XFER_INT:
        type = "Interrupt";
        break;
    }
    return sprintf(buf, "%s\n", type);
}
//static DEVICE_ATTR(type, S_IRUGO, show_ep_type, NULL);
struct device_attribute dev_attr_type = {
    "type", 0, show_ep_type, NULL
};


static ssize_t show_ep_interval(struct device *dev,
                                struct device_attribute *attr, char *buf)
{
    struct ep_device *ep;
    char unit;
    unsigned interval = 0;
    unsigned in;

    ep = to_ep_device(dev);

    in = (ep->desc->bEndpointAddress & USB_DIR_IN);

    switch (usb_endpoint_type(ep->desc)) {
    case USB_ENDPOINT_XFER_CONTROL:
        if (ep->udev->speed == USB_SPEED_HIGH)
            /* uframes per NAK */
            interval = ep->desc->bInterval;
        break;

    case USB_ENDPOINT_XFER_ISOC:
        interval = 1 << (ep->desc->bInterval - 1);
        break;

    case USB_ENDPOINT_XFER_BULK:
        if (ep->udev->speed == USB_SPEED_HIGH && !in)
            /* uframes per NAK */
            interval = ep->desc->bInterval;
        break;

    case USB_ENDPOINT_XFER_INT:
        if (ep->udev->speed == USB_SPEED_HIGH)
            interval = 1 << (ep->desc->bInterval - 1);
        else
            interval = ep->desc->bInterval;
        break;
    }
    interval *= (ep->udev->speed == USB_SPEED_HIGH) ? 125 : 1000;
    if (interval % 1000)
        unit = 'u';
    else {
        unit = 'm';
        interval /= 1000;
    }

    return sprintf(buf, "%d%cs\n", interval, unit);
}
//static DEVICE_ATTR(interval, S_IRUGO, show_ep_interval, NULL);
struct device_attribute dev_attr_interval = {
    "interval", 0, show_ep_interval, NULL
};


static ssize_t show_ep_direction(struct device *dev,
                                 struct device_attribute *attr, char *buf)
{
    struct ep_device *ep;
    char *direction;

    ep = to_ep_device(dev);

    if (usb_endpoint_xfer_control(ep->desc))
        direction = "both";
    else if (usb_endpoint_dir_in(ep->desc))
        direction = "in";
    else
        direction = "out";
    return sprintf(buf, "%s\n", direction);
}
//static DEVICE_ATTR(direction, S_IRUGO, show_ep_direction, NULL);
struct device_attribute dev_attr_direction = {
    "direction", 0, show_ep_direction, NULL
};

int usb_create_ep_devs(struct device *parent,
                       struct usb_host_endpoint *endpoint,
                       struct usb_device *udev)
{
    struct ep_device *ep_dev;
    int retval;

    ep_dev = kzalloc(sizeof(*ep_dev), GFP_KERNEL);
    if (!ep_dev) {
        retval = -ENOMEM;
        goto exit;
    }

    ep_dev->desc = &endpoint->desc;
    ep_dev->udev = udev;
    ep_dev->dev.type = &usb_ep_device_type;
    ep_dev->dev.parent = parent;

    retval = device_register(&ep_dev->dev);
    if (retval)
        goto exit;

    endpoint->ep_dev = ep_dev;
    return retval;

exit:
    return retval;
}

void usb_remove_ep_devs(struct usb_host_endpoint *endpoint)
{
    struct ep_device *ep_dev;

    ep_dev = endpoint->ep_dev;

    if (ep_dev) {
        kfree(endpoint->ep_dev->dev.p);
        kfree(endpoint->ep_dev);
        endpoint->ep_dev = NULL;
    }
}

/// @endcond HIDDEN_SYMBOLS

