/**************************************************************************//**
 * @file     linux_fake.h
 * @version  V1.00
 * @brief    Fake linux APIs.
 * @note
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef  _LINUX_FAKE_H_
#define  _LINUX_FAKE_H_

/// @cond HIDDEN_SYMBOLS

#define GFP_ATOMIC          0
#define GFP_NOIO            0
#define GFP_KERNEL          0


/* include/linux/dma-direction.h */
enum dma_data_direction {
    DMA_BIDIRECTIONAL = 0,
    DMA_TO_DEVICE = 1,
    DMA_FROM_DEVICE = 2,
    DMA_NONE = 3
};


/* copied from scatterlist.h, and remove scatterlist.h */
typedef struct scatterlist {
    char    *address;                  /* Location data is to be transferred to */
    char    *alt_address;              /* Location of actual if address is a
                                        * dma indirect buffer.  NULL otherwise */
    uint32_t  length;
} SCATTER_LIST_T;

struct device;
struct bus_type;

/* Nuvoton ported dummy */
struct kref {
    int  dummy;
};


/* include/linux/sysfs.h */
struct attribute {
    const char      *name;
    mode_t          mode;
#ifdef CONFIG_DEBUG_LOCK_ALLOC
    struct lock_class_key   *key;
    struct lock_class_key   skey;
#endif
};


/* include/linux/klist.h */
struct klist_node {
    void                    *n_klist;       /* never access directly */
    struct list_head        n_node;
    struct kref             n_ref;
};


/* include/linux/klist.h */
struct klist {
    //spinlock_t        k_lock;
    struct list_head    k_list;
    void            (*get)(struct klist_node *);
    void            (*put)(struct klist_node *);
}; //__attribute__ ((aligned (sizeof(void *))));


/* include/linux/klist.h */
struct klist_iter {
    struct klist            *i_klist;
    struct klist_node       *i_cur;
};

/* drivers/base/base.h */
struct driver_private {
    //struct kobject kobj;
    struct klist klist_devices;
    struct klist_node knode_bus;
    //struct module_kobject *mkobj;
    struct device_driver *driver;
};
//#define to_driver(obj) container_of(obj, struct driver_private, kobj)


struct device_driver {
    const char      *name;
    struct bus_type     *bus;

    //struct module     *owner;
    //const char        *mod_name;  /* used for built-in modules */

    //bool suppress_bind_attrs; /* disables bind/unbind via sysfs */

    //const struct of_device_id *of_match_table;

    int (*probe) (struct device *dev);
    int (*remove) (struct device *dev);
    //void (*shutdown) (struct device *dev);
    //int (*suspend) (struct device *dev, pm_message_t state);
    //int (*resume) (struct device *dev);
    //const struct attribute_group **groups;

    //const struct dev_pm_ops *pm;

    struct driver_private *p;
};


struct device_type {
    char  name[64];
    //const struct attribute_group **groups;
    //int (*uevent)(struct device *dev, struct kobj_uevent_env *env);
    //char *(*devnode)(struct device *dev, mode_t *mode);
    //void (*release)(struct device *dev);

    //const struct dev_pm_ops *pm;
};

/* drivers/base/base.h */
struct device_private {
    struct klist klist_children;
    struct klist_node knode_parent;
    struct klist_node knode_driver;
    struct klist_node knode_bus;
    void *driver_data;
    struct device *device;
};


struct device {
    struct device       *parent;

    struct device_private   *p;

    //struct kobject kobj;
    const char      *init_name; /* initial name of the device */
    const struct device_type *type;

    //struct mutex      mutex;  /* mutex to synchronize calls to
    //               * its driver.
    //               */

    struct bus_type *bus;       /* type of bus device is on */
    struct device_driver *driver;   /* which driver has allocated this
    //                 device */
    //void      *platform_data; /* Platform specific data, device
    //                 core doesn't touch it */
    //struct dev_pm_info    power;
    //struct dev_pm_domain  *pm_domain;

#ifdef CONFIG_NUMA
    int     numa_node;  /* NUMA node this device is close to */
#endif
    //u64       *dma_mask;  /* dma mask (if dma'able device) */
    //u64       coherent_dma_mask;/* Like dma_mask, but for
    //                   alloc_coherent mappings as
    //                   not all hardware supports
    //                   64 bit addresses for consistent
    //                   allocations such descriptors. */

    //struct device_dma_parameters *dma_parms;

    //struct list_head  dma_pools;  /* dma pools (if dma'ble) */

    //struct dma_coherent_mem   *dma_mem; /* internal for coherent mem
    //                   override */
    /* arch specific additions */
    //struct dev_archdata   archdata;

    //struct device_node    *of_node; /* associated device tree node */

    //dev_t         devt;   /* dev_t, creates the sysfs "dev" */

    //spinlock_t        devres_lock;
    //struct list_head  devres_head;

    //struct klist_node knode_class;
    //struct class      *class;
    //const struct attribute_group **groups;    /* optional groups */

    //void  (*release)(struct device *dev);
};


/* include/linux/device.h */
struct device_attribute {
    struct attribute    attr;
    ssize_t (*show)(struct device *dev, struct device_attribute *attr,
                    char *buf);
    ssize_t (*store)(struct device *dev, struct device_attribute *attr,
                     const char *buf, size_t count);
};


/* drivers/base/base.h */
struct subsys_private {
    //struct kset subsys;
    //struct kset *devices_kset;

    //struct kset *drivers_kset;
    struct klist klist_devices;
    struct klist klist_drivers;
    //struct blocking_notifier_head bus_notifier;
    unsigned int drivers_autoprobe:1;
    struct bus_type *bus;

    //struct list_head class_interfaces;
    //struct kset glue_dirs;
    //struct mutex class_mutex;
    //struct class *class;
};


/* include/linux/device.h */
struct bus_type {
    const char      *name;
    //struct bus_attribute  *bus_attrs;
    //struct device_attribute   *dev_attrs;
    //struct driver_attribute   *drv_attrs;

    int (*match)(struct device *dev, struct device_driver *drv);
    //int (*uevent)(struct device *dev, struct kobj_uevent_env *env);
    int (*probe)(struct device *dev);
    int (*remove)(struct device *dev);
    void (*shutdown)(struct device *dev);

    //int (*suspend)(struct device *dev, pm_message_t state);
    //int (*resume)(struct device *dev);

    //const struct dev_pm_ops *pm;

    //struct iommu_ops *iommu_ops;

    struct subsys_private *p;
};


struct usb_device_id {
    /* which fields to match against? */
    __u16       match_flags;

    /* Used for product specific matches; range is inclusive */
    __u16       idVendor;
    __u16       idProduct;
    __u16       bcdDevice_lo;
    __u16       bcdDevice_hi;

    /* Used for device class matches */
    __u8        bDeviceClass;
    __u8        bDeviceSubClass;
    __u8        bDeviceProtocol;

    /* Used for interface class matches */
    __u8        bInterfaceClass;
    __u8        bInterfaceSubClass;
    __u8        bInterfaceProtocol;

    /* not matched against */
    __u32       driver_info;
};

/* Some useful macros to use to create struct usb_device_id */
#define USB_DEVICE_ID_MATCH_VENDOR          0x0001
#define USB_DEVICE_ID_MATCH_PRODUCT         0x0002
#define USB_DEVICE_ID_MATCH_DEV_LO          0x0004
#define USB_DEVICE_ID_MATCH_DEV_HI          0x0008
#define USB_DEVICE_ID_MATCH_DEV_CLASS       0x0010
#define USB_DEVICE_ID_MATCH_DEV_SUBCLASS    0x0020
#define USB_DEVICE_ID_MATCH_DEV_PROTOCOL    0x0040
#define USB_DEVICE_ID_MATCH_INT_CLASS       0x0080
#define USB_DEVICE_ID_MATCH_INT_SUBCLASS    0x0100
#define USB_DEVICE_ID_MATCH_INT_PROTOCOL    0x0200


#define bus_get(x)      (x)

#define KNODE_DEAD          1LU
#define KNODE_KLIST_MASK    ~KNODE_DEAD


extern struct usb_hcd  *_g_ohci_usb_hcd;
extern struct usb_hcd  *_g_ehci_usb_hcd;

void set_bit(int nr, volatile unsigned long *addr);
void clear_bit(int nr, volatile unsigned long *addr);
int test_bit(int nr, const volatile unsigned long *addr);
int test_and_clear_bit(int nr, volatile unsigned long *addr);

void *dev_get_drvdata(const struct device *dev);
int dev_set_drvdata(struct device *dev, void *data);

struct usb_interface *to_usb_interface_by_dev(struct device *dev);
struct usb_device *to_usb_device_by_dev(struct device *dev);
struct usb_driver *to_usb_driver_by_devdrv(struct device_driver *dev_driver);
struct usb_device_driver *to_usb_device_driver_by_devdrv(struct device_driver *dev_driver);
struct usb_interface_cache * ref_to_usb_interface_cache_by_ref(struct kref * ref);

extern void msleep(__u32 msec);
extern void mdelay(__u32 msec);
extern void mdelay_in_isr(__u32 msec);
extern void udelay(__u32 us);
extern void udelay_in_isr(__u32 msec);
extern int ffs(int x);
extern int fls(int x);
extern unsigned long find_next_zero_bit(const unsigned long *addr, unsigned long size, unsigned long offset);

extern void *kzalloc(int size, int flags);

extern void klist_init(struct klist *k);
extern int klist_node_attached(struct klist_node *n);
extern void klist_iter_init_node(struct klist *k, struct klist_iter *i, struct klist_node *n);
extern void klist_iter_exit(struct klist_iter *i);
extern struct klist_node *klist_next(struct klist_iter *i);
extern void klist_add_tail(struct klist_node *n, struct klist *k);
extern int klist_node_attached(struct klist_node *n);


extern int driver_register(struct device_driver *drv);
extern int device_register(struct device *dev);
extern int device_attach(struct device *dev);
extern int device_add(struct device *dev);

extern void dump_ohci_regs(void);
extern void dump_ehci_regs(void);
extern void dump_ohci_ports(void);
extern void dump_ehci_ports(void);
extern void dump_ehci_asynclist(void);
extern void dump_ehci_asynclist_simple(char *);

/// @endcond HIDDEN_SYMBOLS

#endif  /* _LINUX_FAKE_H_ */


