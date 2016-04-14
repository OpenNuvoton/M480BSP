/**************************************************************************//**
 * @file     linux_bus_driver.c
 * @version  V1.10
 * $Revision: 11 $
 * $Date: 14/10/03 1:54p $
 * @brief  USB Host bus driver
 *
 * @note
 * Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>

#include "M480.h"

#include "usb.h"

/// @cond HIDDEN_SYMBOLS

int bus_for_each_drv(struct bus_type *bus, struct device_driver *start,
                     void *data, int (*fn)(struct device_driver *, void *));
int bus_for_each_dev(struct bus_type *bus, struct device *start,
                     void *data, int (*fn)(struct device *, void *));


/* drivers/base/base.c */
static inline int driver_match_device(struct device_driver *drv,
                                      struct device *dev)
{
    return drv->bus->match ? drv->bus->match(dev, drv) : 1;
}


/* drivers/base/dd.c */
static int really_probe(struct device *dev, struct device_driver *drv)
{
    int ret = 0;

    dev->driver = drv;

    if (dev->bus->probe) {
        ret = dev->bus->probe(dev);
        if (ret)
            goto probe_failed;
    } else if (drv->probe) {
        ret = drv->probe(dev);
        if (ret)
            goto probe_failed;
    }

    ret = 1;
    goto done;

probe_failed:
    dev->driver = NULL;

    /*
     * Ignore errors returned by ->probe so that the next driver can try
     * its luck.
     */
    ret = 0;
done:
    return ret;
}


/* drivers/base/dd.c */
int driver_probe_device(struct device_driver *drv, struct device *dev)
{
    int ret = 0;

    //if (!device_is_registered(dev))
    //  return -ENODEV;

    //USB_vdebug("driver_probe_device - drv:%s, dev:0x%x\n", drv->name, (int)dev);

    //pm_runtime_get_noresume(dev);
    //pm_runtime_barrier(dev);
    ret = really_probe(dev, drv);
    //pm_runtime_put_sync(dev);

    return ret;
}


/* drivers/base/dd.c */
static int __device_attach(struct device_driver *drv, void *data)
{
    struct device *dev = data;

    if (!driver_match_device(drv, dev))
        return 0;

    return driver_probe_device(drv, dev);
}


/* drivers/base/dd.c */
/**
 * device_attach - try to attach device to a driver.
 * @dev: device.
 *
 * Walk the list of drivers that the bus has and call
 * driver_probe_device() for each pair. If a compatible
 * pair is found, break out and return.
 *
 * Returns 1 if the device was bound to a driver;
 * 0 if no matching driver was found;
 * -ENODEV if the device is not registered.
 *
 * When called for a USB interface, @dev->parent lock must be held.
 */
int device_attach(struct device *dev)
{
    return bus_for_each_drv(dev->bus, NULL, dev, __device_attach);
}


/* drivers/base/dd.c */
static int __driver_attach(struct device *dev, void *data)
{
    struct device_driver *drv = data;

    /*
     * Lock device and try to bind to it. We drop the error
     * here and always return 0, because we need to keep trying
     * to bind to devices and some drivers will return an error
     * simply if it didn't support the device.
     *
     * driver_probe_device() will spit a warning if there
     * is an error.
     */

    if (!driver_match_device(drv, dev))
        return 0;

    if (!dev->driver)
        driver_probe_device(drv, dev);

    return 0;
}


/* drivers/base/dd.c */
int driver_attach(struct device_driver *drv)
{
    return bus_for_each_dev(drv->bus, NULL, drv, __driver_attach);
}


/* drivers/base/bus.c */
static struct device_driver *next_driver(struct klist_iter *i)
{
    struct klist_node *n;
    struct driver_private *drv_priv;

    n = klist_next(i);

    if (n) {
        //drv_priv = container_of(n, struct driver_private, knode_bus);
        drv_priv = (struct driver_private *)((__u32)n - (__u32)&(((struct driver_private *)0)->knode_bus));
        return drv_priv->driver;
    }
    return NULL;
}


/* drivers/base/bus.c */
int bus_for_each_drv(struct bus_type *bus, struct device_driver *start,
                     void *data, int (*fn)(struct device_driver *, void *))
{
    struct klist_iter i;
    struct device_driver *drv;
    int error = 0;

    if (!bus)
        return -EINVAL;

    klist_iter_init_node(&bus->p->klist_drivers, &i,
                         start ? &start->p->knode_bus : NULL);

    drv = next_driver(&i);
    while (drv && !error) {
        error = fn(drv, data);
        drv = next_driver(&i);
    }
    klist_iter_exit(&i);
    return error;
}


//#define to_device_private_bus(obj)   container_of(obj, struct device_private, knode_bus)
#define to_device_private_bus(obj)   (struct device_private *)((u32)obj - (u32)&(((struct device_private *)0)->knode_bus))


/* drivers/base/bus.c */
static struct device *next_device(struct klist_iter *i)
{
    struct klist_node *n;
    struct device *dev = NULL;
    struct device_private *dev_prv;

    n = klist_next(i);
    if (n) {
        dev_prv = to_device_private_bus(n);
        dev = dev_prv->device;
    }
    return dev;
}


/* drivers/base/bus.c */
int bus_for_each_dev(struct bus_type *bus, struct device *start,
                     void *data, int (*fn)(struct device *, void *))
{
    struct klist_iter i;
    struct device *dev;
    int error = 0;

    if (!bus)
        return -EINVAL;

    klist_iter_init_node(&bus->p->klist_devices, &i,
                         (start ? &start->p->knode_bus : NULL));

    dev = next_device(&i);
    while (dev && !error) {
        error = fn(dev, data);
        dev = next_device(&i);
    }
    klist_iter_exit(&i);
    return error;
}


/* drivers/base/bus.c */
/**
 * bus_add_driver - Add a driver to the bus.
 * @drv: driver.
 */
int bus_add_driver(struct device_driver *drv)
{
    struct bus_type *bus;
    struct driver_private *priv;
    int error = 0;

    bus = bus_get(drv->bus);
    if (!bus)
        return -EINVAL;

    priv = kzalloc(sizeof(*priv), GFP_KERNEL);
    if (!priv) {
        error = -ENOMEM;
        goto out_put_bus;
    }
    klist_init(&priv->klist_devices);   // (&priv->klist_devices, NULL, NULL);
    priv->driver = drv;
    drv->p = priv;
    //priv->kobj.kset = bus->p->drivers_kset;
    //error = kobject_init_and_add(&priv->kobj, &driver_ktype, NULL,
    //               "%s", drv->name);
    //if (error)
    //  goto out_unregister;
    if (1) { // (drv->bus->p->drivers_autoprobe) {
        error = driver_attach(drv);
        if (error)
            goto out_unregister;
    }
    klist_add_tail(&priv->knode_bus, &bus->p->klist_drivers);
    //module_add_driver(drv->owner, drv);

    //error = driver_create_file(drv, &driver_attr_uevent);
    //if (error) {
    //  printk(KERN_ERR "%s: uevent attr (%s) failed\n",
    //      __func__, drv->name);
    //}
    //error = driver_add_attrs(bus, drv);
    //if (error) {
    //  /* How the hell do we get out of this pickle? Give up */
    //  printk(KERN_ERR "%s: driver_add_attrs(%s) failed\n",
    //      __func__, drv->name);
    //}

    //if (!drv->suppress_bind_attrs) {
    //  error = add_bind_files(drv);
    //  if (error) {
    //      /* Ditto */
    //      printk(KERN_ERR "%s: add_bind_files(%s) failed\n",
    //          __func__, drv->name);
    //  }
    //}

    //kobject_uevent(&priv->kobj, KOBJ_ADD);
    return 0;

out_unregister:
    //kobject_put(&priv->kobj);
    kfree(drv->p);
    drv->p = NULL;
out_put_bus:
    //bus_put(bus);
    return error;
}


/* drivers/base/bus.c */
int bus_register(struct bus_type *bus)
{
    //int retval;
    struct subsys_private *priv;

    priv = kzalloc(sizeof(struct subsys_private), GFP_KERNEL);
    if (!priv)
        return -ENOMEM;

    priv->bus = bus;
    bus->p = priv;

    //BLOCKING_INIT_NOTIFIER_HEAD(&priv->bus_notifier);

    //retval = kobject_set_name(&priv->subsys.kobj, "%s", bus->name);
    //if (retval)
    //  goto out;

    //priv->subsys.kobj.kset = bus_kset;
    //priv->subsys.kobj.ktype = &bus_ktype;
    priv->drivers_autoprobe = 1;

    //retval = kset_register(&priv->subsys);
    //if (retval)
    //  goto out;

    //retval = bus_create_file(bus, &bus_attr_uevent);
    //if (retval)
    //  goto bus_uevent_fail;

    //priv->devices_kset = kset_create_and_add("devices", NULL,
    //                   &priv->subsys.kobj);
    //if (!priv->devices_kset) {
    //  retval = -ENOMEM;
    //  goto bus_devices_fail;
    //}

    //priv->drivers_kset = kset_create_and_add("drivers", NULL,
    //                   &priv->subsys.kobj);
    //if (!priv->drivers_kset) {
    //  retval = -ENOMEM;
    //  goto bus_drivers_fail;
    //}

    //klist_init(&priv->klist_devices, klist_devices_get, klist_devices_put);
    klist_init(&priv->klist_devices);
    //klist_init(&priv->klist_drivers, NULL, NULL);
    klist_init(&priv->klist_drivers);

    //retval = add_probe_files(bus);
    //if (retval)
    //  goto bus_probe_files_fail;

    //retval = bus_add_attrs(bus);
    //if (retval)
    //  goto bus_attrs_fail;

    USB_vdebug("bus: '%s': registered\n", bus->name);
    return 0;

//bus_attrs_fail:
//  remove_probe_files(bus);
//bus_probe_files_fail:
//  kset_unregister(bus->p->drivers_kset);
//bus_drivers_fail:
//  kset_unregister(bus->p->devices_kset);
//bus_devices_fail:
//  bus_remove_file(bus, &bus_attr_uevent);
//bus_uevent_fail:
//  kset_unregister(&bus->p->subsys);
//out:
//  kfree(bus->p);
//  bus->p = NULL;
//  return retval;
}


/* drivers/base/driver.c */
/**
 * driver_register - register driver with bus
 * @drv: driver to register
 *
 * We pass off most of the work to the bus_add_driver() call,
 * since most of the things we have to do deal with the bus
 * structures.
 */
int driver_register(struct device_driver *drv)
{
    int ret;
    //struct device_driver *other;

    //BUG_ON(!drv->bus->p);

    //if ((drv->bus->probe && drv->probe) ||
    //    (drv->bus->remove && drv->remove) ||
    //    (drv->bus->shutdown && drv->shutdown))
    //  printk(KERN_WARNING "Driver '%s' needs updating - please use "
    //      "bus_type methods\n", drv->name);

    //other = driver_find(drv->name, drv->bus);
    //if (other) {
    //  put_driver(other);
    //  printk(KERN_ERR "Error: Driver '%s' is already registered, "
    //      "aborting...\n", drv->name);
    //  return -EBUSY;
    //}

    ret = bus_add_driver(drv);
    if (ret)
        return ret;
    //ret = driver_add_groups(drv, drv->groups);
    //if (ret)
    //  bus_remove_driver(drv);
    return ret;
}

/// @endcond HIDDEN_SYMBOLS
