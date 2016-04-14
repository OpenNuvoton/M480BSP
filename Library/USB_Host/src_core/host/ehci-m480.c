/*
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation;version 2 of the License.
 *
 */

struct usb_hcd  *_g_ehci_usb_hcd = NULL;

static struct device  m480_ehci_dummy_dev;

static int usb_m480_probe(const struct hc_driver *driver)
{
    struct usb_hcd *hcd;
    struct ehci_hcd *ehci;
    int retval;

    hcd = usb_create_hcd(driver, &m480_ehci_dummy_dev, "m480-ehci");
    if (!hcd) {
        retval = -ENOMEM;
        goto err1;
    }
    _g_ehci_usb_hcd = hcd;

    ehci = hcd_to_ehci(hcd);

    hcd->regs = (void *)EHCI_BASE;

    ehci->caps = (struct ehci_caps *)EHCI_BASE;         // hcd->regs;
    ehci->regs = (struct ehci_regs *)(EHCI_BASE+0x20);  // hcd->regs + HC_LENGTH(readl(&ehci->caps->hc_capbase));

    /* cache this readonly data; minimize chip reads */
    ehci->hcs_params = readl(&ehci->caps->hcs_params);
    ehci->sbrn = 0x20;

    retval = usb_add_hcd(hcd, 0, 0);

    if (retval != 0)
        goto err1;

    /* enable EHCI */
    //writel(1, &ehci->regs->configured_flag);

    return retval;

err1:
    usb_put_hcd(hcd);

    return retval;
}

void usb_m480_remove(struct usb_hcd *hcd)
{
    usb_remove_hcd(hcd);
    //iounmap(hcd->regs);
    //release_mem_region(hcd->rsrc_start, hcd->rsrc_len);
    usb_put_hcd(hcd);
}


static int ehci_m480_start (struct usb_hcd *hcd)
{
    int ret;

    if ((ret = ehci_init(hcd)) < 0)
        return ret;

    if ((ret = ehci_run (hcd)) < 0) {
        USB_error("can't start %s", hcd->self.bus_name);
        ehci_stop (hcd);
        return ret;
    }

    ehci_port_power(hcd_to_ehci(_g_ehci_usb_hcd), 1);

    return 0;
}


static int __ehci_reset (struct usb_hcd *hcd)
{
    return ehci_reset(hcd_to_ehci(hcd));
}


static const struct hc_driver ehci_m480_hc_driver = {
    hcd_name,
    "Nuvoton M480 HSUSBH(EHCI) Host Controller",
    sizeof(struct ehci_hcd),
    HCD_USB2|HCD_MEMORY,        // flags
    __ehci_reset,               // reset
    ehci_m480_start,            // start
    ehci_stop,                  // stop
    NULL,                       // shutdown
    ehci_get_frame,             // get_frame_number
    ehci_urb_enqueue,           // urb_enqueue
    ehci_urb_dequeue,           // urb_dequeue
    ehci_endpoint_disable,      // endpoint_disable
    NULL,                       // endpoint_reset
    ehci_hub_status_data,       // hub_status_data
    ehci_hub_control,           // hub_control
    NULL,                       // bus_suspend
    NULL,                       // bus_resume
    NULL,                       // start_port_reset
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


int usb_ehci_init(void)
{
    if (usb_disabled())
        return -ENODEV;
    return usb_m480_probe(&ehci_m480_hc_driver);
}


