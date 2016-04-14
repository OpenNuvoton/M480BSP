/**************************************************************************//**
 * @file     linux_fake.c
 * @version  V1.10
 * $Revision: 11 $
 * $Date: 14/10/03 1:54p $
 * @brief  Functions to fake Linux functions.
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

// include/linux/bitops.h
#define BIT(nr)             (1UL << (nr))
#define BIT_MASK(nr)        (1UL << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr)        ((nr) / BITS_PER_LONG)
#define BITS_PER_BYTE       8
#define BITS_PER_LONG       32
//#define BITS_TO_LONGS(nr) DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))
#define BITOP_WORD(nr)      ((nr) / BITS_PER_LONG)


// Nuvoton ported
struct usb_interface *to_usb_interface_by_dev(struct device *dev)
{
    struct usb_interface *intf;
    intf = (struct usb_interface *)0;
    return (struct usb_interface *) ((__u32)dev - (__u32)&(intf->dev));
}

// Nuvoton ported
struct usb_device *to_usb_device_by_dev(struct device *dev)
{
    struct usb_device *usb_dev;
    usb_dev = (struct usb_device *)0;
    return (struct usb_device *) ((__u32)dev - (__u32)&(usb_dev->dev));
}

struct usb_driver *to_usb_driver_by_devdrv(struct device_driver *dev_driver)
{
    struct usb_driver *usb_driver;
    usb_driver = (struct usb_driver *)0;
    return (struct usb_driver *)((__u32)dev_driver - (__u32)&(usb_driver->drvwrap.driver));
}

struct usb_device_driver *to_usb_device_driver_by_devdrv(struct device_driver *dev_driver)
{
    struct usb_device_driver *usb_devdrv;
    usb_devdrv = (struct usb_device_driver *)0;
    return (struct usb_device_driver *)((__u32)dev_driver - (__u32)&(usb_devdrv->drvwrap.driver));
}


struct usb_interface_cache * ref_to_usb_interface_cache_by_ref(struct kref * ref)
{
    struct usb_interface_cache *ifc;
    ifc = (struct usb_interface_cache *)0;
    return (struct usb_interface_cache *)((__u32)ref - (__u32)&(ifc->ref));
}


// Nuvoton ported
void msleep(__u32 msec)
{
    delay_us(msec*1000);
}

// Nuvoton ported
void mdelay(__u32 msec)
{
    delay_us(msec*1000);
}

void mdelay_in_isr(__u32 msec)
{
    delay_us(msec*1000);
}

// Nuvoton ported
void udelay(__u32 us)
{
    delay_us(us);
}

// Nuvoton ported
void udelay_in_isr(__u32 us)
{
    delay_us(us);
}


// include/asm-generic/bitops/atomic.h
void clear_bit(int nr, volatile unsigned long *addr)
{
    unsigned long mask;
    unsigned long *p;
    //unsigned long flags;

    mask = BIT_MASK(nr);
    p = ((unsigned long *)addr) + BIT_WORD(nr);

    //_atomic_spin_lock_irqsave(p, flags);
    *p &= ~mask;
    //_atomic_spin_unlock_irqrestore(p, flags);

    //if ((u32)addr == (u32)&_g_ehci_usb_hcd->flags)
    //  printf("Clear EHCI flags bit %d, 0x%x\n", nr, *p);
    //else if ((u32)addr == (u32)&_g_ohci_usb_hcd->flags)
    //  printf("Clear OHCI flags bit %d, 0x%x\n", nr, *p);
    //else
    //  printf("Clear Unknown bit %d\n", nr);
}

// include/asm-generic/bitops/atomic.h
void set_bit(int nr, volatile unsigned long *addr)
{
    unsigned long mask;
    unsigned long *p;
    //unsigned long flags;

    mask = BIT_MASK(nr);
    p = ((unsigned long *)addr) + BIT_WORD(nr);

    //_atomic_spin_lock_irqsave(p, flags);
    *p  |= mask;
    //_atomic_spin_unlock_irqrestore(p, flags);

    //if ((u32)addr == (u32)&_g_ehci_usb_hcd->flags)
    //  printf("Set EHCI flags bit %d, 0x%x\n", nr, *p);
    //else if ((u32)addr == (u32)&_g_ohci_usb_hcd->flags)
    //  printf("Set OHCI flags bit %d, 0x%x\n", nr, *p);
    //else
    //  printf("Set Unknown bit %d\n", nr);
}

// include/asm-generic/bitops/atomic.h
int test_and_clear_bit(int nr, volatile unsigned long *addr)
{
    unsigned long mask;
    unsigned long *p;
    unsigned long old;
    //unsigned long flags;

    mask = BIT_MASK(nr);
    p = ((unsigned long *)addr) + BIT_WORD(nr);

    //_atomic_spin_lock_irqsave(p, flags);
    old = *p;
    *p = old & ~mask;
    //_atomic_spin_unlock_irqrestore(p, flags);

    return (old & mask) != 0;
}


// include/asm-generic/bitops/non-atomic.h
int test_bit(int nr, const volatile unsigned long *addr)
{
    return 1UL & (addr[BIT_WORD(nr)] >> (nr & (BITS_PER_LONG-1)));
}

// include/asm-generic/bitops/ffs.h
int ffs(int x)
{
    int r = 1;

    if (!x)
        return 0;
    if (!(x & 0xffff)) {
        x >>= 16;
        r += 16;
    }
    if (!(x & 0xff)) {
        x >>= 8;
        r += 8;
    }
    if (!(x & 0xf)) {
        x >>= 4;
        r += 4;
    }
    if (!(x & 3)) {
        x >>= 2;
        r += 2;
    }
    if (!(x & 1)) {
        x >>= 1;
        r += 1;
    }
    return r;
}

#define ffz(x)  ffs(~(x))


/**
 * fls - find last (most-significant) bit set
 * @x: the word to search
 *
 * This is defined the same way as ffs.
 * Note fls(0) = 0, fls(1) = 1, fls(0x80000000) = 32.
 */
/* innclude\asm-generic\bitops\fls.h */
int fls(int x)
{
    int r = 32;

    if (!x)
        return 0;
    if (!(x & 0xffff0000u)) {
        x <<= 16;
        r -= 16;
    }
    if (!(x & 0xff000000u)) {
        x <<= 8;
        r -= 8;
    }
    if (!(x & 0xf0000000u)) {
        x <<= 4;
        r -= 4;
    }
    if (!(x & 0xc0000000u)) {
        x <<= 2;
        r -= 2;
    }
    if (!(x & 0x80000000u)) {
        x <<= 1;
        r -= 1;
    }
    return r;
}


// lib/find_next_bit.c
unsigned long find_next_zero_bit(const unsigned long *addr, unsigned long size,
                                 unsigned long offset)
{
    const unsigned long *p;
    unsigned long result;
    unsigned long tmp;

    p = addr + BITOP_WORD(offset);
    result = offset & ~(BITS_PER_LONG-1);

    if (offset >= size)
        return size;
    size -= result;
    offset %= BITS_PER_LONG;
    if (offset) {
        tmp = *(p++);
        tmp |= ~0UL >> (BITS_PER_LONG - offset);
        if (size < BITS_PER_LONG)
            goto found_first;
        if (~tmp)
            goto found_middle;
        size -= BITS_PER_LONG;
        result += BITS_PER_LONG;
    }
    while (size & ~(BITS_PER_LONG-1)) {
        if (~(tmp = *(p++)))
            goto found_middle;
        result += BITS_PER_LONG;
        size -= BITS_PER_LONG;
    }
    if (!size)
        return result;
    tmp = *p;

found_first:
    tmp |= ~0UL << size;
    if (tmp == ~0UL)    /* Are any bits zero? */
        return result + size;   /* Nope. */
found_middle:
    return result + ffz(tmp);
}


void * kzalloc(int size, int flags)
{
    void * ptr;

    ptr = (void *)USB_malloc(size, 4);
    if (ptr != NULL)
        memset((char *)ptr, 0, size);
    return ptr;
}


/* lib/klist.c */
//void klist_init(struct klist *k, void (*get)(struct klist_node *),
//      void (*put)(struct klist_node *))
void klist_init(struct klist *k)
{
    INIT_LIST_HEAD(&k->k_list);
    //spin_lock_init(&k->k_lock);
    //k->get = get;
    //k->put = put;
}


/* lib/klist.c */
static void knode_set_klist(struct klist_node *knode, struct klist *klist)
{
    knode->n_klist = klist;
    /* no knode deserves to start its life dead */
    //WARN_ON(knode_dead(knode));
}


/* lib/klist.c */
static void klist_node_init(struct klist *k, struct klist_node *n)
{
    INIT_LIST_HEAD(&n->n_node);
    //kref_init(&n->n_ref);
    knode_set_klist(n, k);
    //if (k->get)
    //  k->get(n);
}


/* lib/klist.c */
static void knode_kill(struct klist_node *knode)
{
    /* and no knode should die twice ever either, see we're very humane */
    //WARN_ON(knode_dead(knode));
    *(unsigned long *)&knode->n_klist |= KNODE_DEAD;
}


/* lib/klist.c */
static bool knode_dead(struct klist_node *knode)
{
    return (unsigned long)knode->n_klist & KNODE_DEAD;
}


/* lib/klist.c */
//static struct klist *knode_klist(struct klist_node *knode)
//{
//  return (struct klist *)
//      ((unsigned long)knode->n_klist & KNODE_KLIST_MASK);
//}


/* lib/klist.c */
static void klist_put(struct klist_node *n, bool kill)
{
    //struct klist *k = knode_klist(n);
    //void (*put)(struct klist_node *) = k->put;

    spin_lock(&k->k_lock);
    if (kill)
        knode_kill(n);
    //if (!klist_dec_and_del(n))
    //  put = NULL;
    spin_unlock(&k->k_lock);
    //if (put)
    //  put(n);
}


/* lib/klist.c */
void klist_iter_init_node(struct klist *k, struct klist_iter *i,
                          struct klist_node *n)
{
    i->i_klist = k;
    i->i_cur = n;
    //if (n)
    //  kref_get(&n->n_ref);
}


/* lib/klist.c */
void klist_iter_exit(struct klist_iter *i)
{
    if (i->i_cur) {
        klist_put(i->i_cur, false);
        i->i_cur = NULL;
    }
}


/* lib/klist.c */
static struct klist_node *to_klist_node(struct list_head *n)
{
    //return container_of(n, struct klist_node, n_node);
    return (struct klist_node *)((u32)n - (u32)&(((struct klist_node *)0)->n_node));
}


/* lib/klist.c */
struct klist_node *klist_next(struct klist_iter *i)
{
    void (*put)(struct klist_node *) = i->i_klist->put;
    struct klist_node *last;
    struct klist_node *next;

    last = i->i_cur;

    spin_lock(&i->i_klist->k_lock);

    if (last) {
        next = to_klist_node(last->n_node.next);
        //if (!klist_dec_and_del(last))
        //  put = NULL;
    } else
        next = to_klist_node(i->i_klist->k_list.next);

    i->i_cur = NULL;
    while (next != to_klist_node(&i->i_klist->k_list)) {
        if (likely(!knode_dead(next))) {
            //kref_get(&next->n_ref);
            i->i_cur = next;
            break;
        }
        next = to_klist_node(next->n_node.next);
    }

    spin_unlock(&i->i_klist->k_lock);

    if (put && last)
        put(last);
    return i->i_cur;
}


static void add_tail(struct klist *k, struct klist_node *n)
{
    spin_lock(&k->k_lock);
    list_add_tail(&n->n_node, &k->k_list);
    spin_unlock(&k->k_lock);
}


/* lib/klist.c */
/**
 * klist_add_tail - Initialize a klist_node and add it to back.
 * @n: node we're adding.
 * @k: klist it's going on.
 */
void klist_add_tail(struct klist_node *n, struct klist *k)
{
    klist_node_init(k, n);
    add_tail(k, n);
}


/* lib/klist.c */
/**
 * klist_node_attached - Say whether a node is bound to a list or not.
 * @n: Node that we're testing.
 */
int klist_node_attached(struct klist_node *n)
{
    return (n->n_klist != NULL);
}


/* drivers/base/core.c */
int device_private_init(struct device *dev)
{
    dev->p = kzalloc(sizeof(*dev->p), GFP_KERNEL);
    if (!dev->p)
        return -ENOMEM;
    dev->p->device = dev;
    //klist_init(&dev->p->klist_children, klist_children_get, klist_children_put);
    klist_init(&dev->p->klist_children);
    return 0;
}


/* drivers/base/bus.c */
int bus_add_device(struct device *dev)
{
    struct bus_type *bus;
    //int error = 0;

    bus = bus_get(dev->bus);

    if (bus) {
        //USB_debug("bus: '%s': add device %s\n", bus->name, dev_name(dev));
        //error = device_add_attrs(bus, dev);
        //if (error)
        //  goto out_put;
        //error = sysfs_create_link(&bus->p->devices_kset->kobj,
        //              &dev->kobj, dev_name(dev));
        //if (error)
        //  goto out_id;
        //error = sysfs_create_link(&dev->kobj,
        //      &dev->bus->p->subsys.kobj, "subsystem");
        //if (error)
        //  goto out_subsys;
        klist_add_tail(&dev->p->knode_bus, &bus->p->klist_devices);
    }
    return 0;

//out_subsys:
//  sysfs_remove_link(&bus->p->devices_kset->kobj, dev_name(dev));
//out_id:
//  device_remove_attrs(bus, dev);
//out_put:
//  bus_put(dev->bus);
//  return error;
}


/* drivers/base/bus.c */
void bus_probe_device(struct device *dev)
{
    struct bus_type *bus;
    int ret;

    bus = dev->bus;

//  if (bus && bus->p->drivers_autoprobe) {
    if (bus) {
        ret = device_attach(dev);
        WARN_ON(ret < 0);
    }
}


/* drivers/base/core.c */
int device_add(struct device *dev)
{
    struct device *parent = NULL;
    //struct class_interface *class_intf;
    int error = -EINVAL;

    if (!dev)
        goto done;

    if (!dev->p) {
        error = device_private_init(dev);
        if (error)
            goto done;
    }

    /*
     * for statically allocated devices, which should all be converted
     * some day, we need to initialize the name. We prevent reading back
     * the name, and force the use of dev_name()
     */
    //if (dev->init_name) {
    //  dev_set_name(dev, "%s", dev->init_name);
    //  dev->init_name = NULL;
    //}

    //if (!dev_name(dev)) {
    //  error = -EINVAL;
    //  goto name_error;
    //}

    //USB_vdebug("device: '%s': %s\n", dev_name(dev), __func__);

    //parent = dev->parent;
    //setup_parent(dev, parent);

    /* use parent numa_node */
    //if (parent)
    //  set_dev_node(dev, dev_to_node(parent));

    /* first, register with generic layer. */
    /* we require the name to be set before, and pass NULL */
    //error = kobject_add(&dev->kobj, dev->kobj.parent, NULL);
    //if (error)
    //  goto Error;

    /* notify platform of device entry */
    //if (platform_notify)
    //  platform_notify(dev);

    //error = device_create_file(dev, &uevent_attr);
    //if (error)
    //  goto attrError;

    //if (MAJOR(dev->devt)) {
    //  error = device_create_file(dev, &devt_attr);
    //  if (error)
    //      goto ueventattrError;

    //  error = device_create_sys_dev_entry(dev);
    //  if (error)
    //      goto devtattrError;

    //  devtmpfs_create_node(dev);
    //}

    //error = device_add_class_symlinks(dev);
    //if (error)
    //  goto SymlinkError;
    //error = device_add_attrs(dev);
    //if (error)
    //  goto AttrsError;
    error = bus_add_device(dev);
    if (error)
        goto BusError;
    //error = dpm_sysfs_add(dev);
    //if (error)
    //  goto DPMError;
    //device_pm_add(dev);

    /* Notify clients of device addition.  This call must come
     * after dpm_sysf_add() and before kobject_uevent().
     */
    //if (dev->bus)
    //  blocking_notifier_call_chain(&dev->bus->p->bus_notifier,
    //                   BUS_NOTIFY_ADD_DEVICE, dev);

    //kobject_uevent(&dev->kobj, KOBJ_ADD);
    bus_probe_device(dev);
    if (parent)
        klist_add_tail(&dev->p->knode_parent,
                       &parent->p->klist_children);

    //if (dev->class) {
    //  mutex_lock(&dev->class->p->class_mutex);
    //  /* tie the class to the device */
    //  klist_add_tail(&dev->knode_class,
    //             &dev->class->p->klist_devices);

    //  /* notify any interfaces that the device is here */
    //  list_for_each_entry(class_intf,
    //              &dev->class->p->class_interfaces, node)
    //      if (class_intf->add_dev)
    //          class_intf->add_dev(dev, class_intf);
    //  mutex_unlock(&dev->class->p->class_mutex);
    //}
done:
    //put_device(dev);
    return error;
//DPMError:
    //bus_remove_device(dev);
BusError:
    //device_remove_attrs(dev);
    return error;
//AttrsError:
    //device_remove_class_symlinks(dev);
//SymlinkError:
    //if (MAJOR(dev->devt))
    //  devtmpfs_delete_node(dev);
    //if (MAJOR(dev->devt))
    //  device_remove_sys_dev_entry(dev);
//devtattrError:
    //if (MAJOR(dev->devt))
    //  device_remove_file(dev, &devt_attr);
//ueventattrError:
    //device_remove_file(dev, &uevent_attr);
//attrError:
    //kobject_uevent(&dev->kobj, KOBJ_REMOVE);
    //kobject_del(&dev->kobj);
//Error:
    //cleanup_device_parent(dev);
    //if (parent)
    //  put_device(parent);
//name_error:
    //kfree(dev->p);
    //dev->p = NULL;
    //goto done;
}


/* drivers/base/core.c */
int device_register(struct device *dev)
{
    return device_add(dev);
}


/*
 * These exports can't be _GPL due to .h files using this within them, and it
 * might break something that was previously working...
 */
void *dev_get_drvdata(const struct device *dev)
{
    if (dev && dev->p)
        return dev->p->driver_data;
    return NULL;
}


int dev_set_drvdata(struct device *dev, void *data)
{
    int error;

    if (!dev->p) {
        error = device_private_init(dev);
        if (error)
            return error;
    }
    dev->p->driver_data = data;
    return 0;
}

/// @endcond HIDDEN_SYMBOLS
