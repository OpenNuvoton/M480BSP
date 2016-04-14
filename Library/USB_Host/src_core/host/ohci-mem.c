/*-------------------------------------------------------------------------
 * OHCI HCD (Host Controller Driver) for USB.
 *
 * (C) Copyright 1999 Roman Weissgaerber <weissg@vienna.at>
 * (C) Copyright 2000-2002 David Brownell <dbrownell@users.sourceforge.net>
 *
 * This file is licenced under the GPL.
 */

/*-------------------------------------------------------------------------*/

/*
 * OHCI deals with three types of memory:
 *  - data used only by the HCD ... kmalloc is fine
 *  - async and periodic schedules, shared by HC and HCD ... these
 *    need to use dma_pool or dma_alloc_coherent
 *  - driver buffers, read/written by HC ... the hcd glue or the
 *    device driver provides us with dma addresses
 *
 * There's also "register" data, which is memory mapped.
 * No memory seen by this driver (or any HCD) may be paged out.
 */

/*-------------------------------------------------------------------------*/

static void ohci_hcd_init (struct ohci_hcd *ohci)
{
    ohci->next_statechange = jiffies;
    //spin_lock_init (&ohci->lock);
    INIT_LIST_HEAD (&ohci->pending);
}

/*-------------------------------------------------------------------------*/

/* ohci "done list" processing needs this mapping */
static inline struct td *
dma_to_td (struct ohci_hcd *hc, dma_addr_t td_dma)
{
    struct td *td;

    td_dma &= TD_MASK;
    td = hc->td_hash [TD_HASH_FUNC(td_dma)];
    while (td && (td->td_dma != td_dma))
        td = td->td_hash;
    return td;
}

/* TDs ... */
static struct td *
td_alloc (struct ohci_hcd *hc, gfp_t mem_flags)
{
    dma_addr_t  dma;
    struct td   *td;

    td = USB_malloc(sizeof(*td), BOUNDARY32);
    dma = (dma_addr_t)td;
    if (td) {
        /* in case hc fetches it, make it look dead */
        memset (td, 0, sizeof *td);
        td->hwNextTD = cpu_to_hc32 (hc, dma);
        td->td_dma = dma;
        /* hashed in td_fill */
    }
    //printf("td_alloc - 0x%x (0x%x)\n", (int)td, USB_available_memory());
    return td;
}

static void
td_free (struct ohci_hcd *hc, struct td *td)
{
    struct td   **prev;

    prev = &hc->td_hash [TD_HASH_FUNC (td->td_dma)];

    while (*prev && *prev != td)
        prev = &(*prev)->td_hash;
    if (*prev)
        *prev = td->td_hash;
    else if ((td->hwINFO & cpu_to_hc32(hc, TD_DONE)) != 0)
        USB_debug("no hash for td %p\n", td);
    USB_free (td);
}

/*-------------------------------------------------------------------------*/

/* EDs ... */
static struct ed *
ed_alloc (struct ohci_hcd *hc, gfp_t mem_flags)
{
    dma_addr_t  dma;
    struct ed   *ed;

    ed = USB_malloc(sizeof(*ed), BOUNDARY32);
    dma = (dma_addr_t) ed;
    if (ed) {
        memset (ed, 0, sizeof (*ed));
        INIT_LIST_HEAD (&ed->td_list);
        ed->dma = dma;
    }
    return ed;
}

static void
ed_free (struct ohci_hcd *hc, struct ed *ed)
{
    USB_free (ed);
}

