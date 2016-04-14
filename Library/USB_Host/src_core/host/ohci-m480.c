/*
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation;version 2 of the License.
 *
 */

/**
 * usb_hcd_ppc_soc_probe - initialize On-Chip HCDs
 * Context: !in_interrupt()
 *
 * Allocates basic resources for this USB host controller.
 *
 * Store this function in the HCD's struct pci_driver as probe().
 */

struct usb_hcd  *_g_ohci_usb_hcd = NULL;

static struct device  m480_ohci_dummy_dev;

static int usb_m480_probe(const struct hc_driver *driver)
{
    int retval;
    struct usb_hcd *hcd;
    struct ohci_hcd *ohci ;

    hcd = usb_create_hcd(driver, &m480_ohci_dummy_dev, "m480-ohci");
    if (!hcd)
        return -ENOMEM;
    ohci = hcd_to_ohci(hcd);
    ohci_hcd_init(ohci);

    _g_ohci_usb_hcd = hcd;

    hcd->regs = (void *)USBH_BASE;
    ohci->regs = (struct ohci_regs *)OHCI_BASE;

    retval = usb_add_hcd(hcd, 0, 0);
    if (retval == 0)
        return retval;

    USB_error("OHCI usb_m480_probe failed!\n");
    usb_put_hcd(hcd);
    return retval;
}


static void usb_hcd_m480_remove(struct usb_hcd *hcd)
{
    usb_remove_hcd(hcd);
    //iounmap(hcd->regs);
    //release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
    usb_put_hcd(hcd);
}


static int ohci_m480_start (struct usb_hcd *hcd)
{
    int ret;

    if ((ret = ohci_init(hcd)) < 0)
        return ret;

    if ((ret = ohci_run (hcd)) < 0) {
        USB_error("can't start %s", hcd->self.bus_name);
        ohci_stop (hcd);
        return ret;
    }
    return 0;
}


static const struct hc_driver ohci_m480_hc_driver = {
    hcd_name,
    "Nvoton M480 USBH(OHCI) Host Controller",
    sizeof(struct ohci_hcd),
    HCD_USB11|HCD_MEMORY,       // flags
    NULL,                       // reset
    ohci_m480_start,          // start
    ohci_stop,                  // stop
    NULL,                       // shutdown
    ohci_get_frame,             // get_frame_number
    ohci_urb_enqueue,           // urb_enqueue
    ohci_urb_dequeue,           // urb_dequeue
    ohci_endpoint_disable,      // endpoint_disable
    NULL,                       // endpoint_reset
    ohci_hub_status_data,       // hub_status_data
    ohci_hub_control,           // hub_control
    NULL,                       // bus_suspend
    NULL,                       // bus_resume
    ohci_start_port_reset,      // start_port_reset
    NULL,                       // relinquish_port
    NULL,                       // port_handed_over
    NULL,                       // clear_tt_buffer_complete
    NULL,                       // alloc_dev
    NULL,                       // free_dev
    NULL,                       // alloc_streams
    NULL,                       // free_streams
    NULL,                       // add_endpoint
    NULL,                       // drop_endpoint
    NULL,                       // check_bandwidth
    NULL,                       // reset_bandwidth
    NULL,                       // address_device
    NULL,                       // update_hub_device
    NULL,                       // reset_device
    NULL,                       // update_device
    NULL                        // set_usb2_hw_lpm
};


int usb_ohci_init(void)
{
    if (usb_disabled())
        return -ENODEV;
    return usb_m480_probe(&ohci_m480_hc_driver);
}

