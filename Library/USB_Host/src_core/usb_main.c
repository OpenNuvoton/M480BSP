/**************************************************************************//**
 * @file     usb_main.c
 * @version  V1.10
 * $Revision: 11 $
 * $Date: 14/10/03 1:54p $
 * @brief   USB Host driver main function.
 *
 * @note
 * Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "M480.h"

#include "usb.h"
#include "host/ehci.h"
#include "usbh_lib.h"


/// @cond HIDDEN_SYMBOLS

extern void usb_poll_root_hubs(void);
extern int  hub_events(void);
extern int  usb_ehci_init(void);
extern int  usb_ohci_init(void);
//extern void USB_InitializeMemoryPool(void);

int    _IsInUsbInterrupt = 0;

extern struct usb_hcd  *_g_ohci_usb_hcd;
extern struct usb_hcd  *_g_ehci_usb_hcd;

/// @endcond HIDDEN_SYMBOLS


/**
  * @brief       Initialize M480 USB Host controller and USB stack.
  *
  * @return      None.
  */
void  usbh_core_init()
{
    volatile int  loop;

    NVIC_DisableIRQ(HSUSBH_IRQn);
    NVIC_DisableIRQ(USBH_IRQn);

    USB_InitializeMemoryPool();

    HSUSBH->USBPCR0 = 0x160;                /* enable PHY 0          */
    HSUSBH->USBPCR1 = 0x520;                /* enable PHY 1          */

    USBH->HcMiscControl |= USBH_HcMiscControl_OCAL_Msk; /* Over-current active low  */
    // USBH->HcMiscControl &= ~USBH_HcMiscControl_OCAL_Msk; /* Over-current active high  */

    bus_register(&usb_bus_type);

#ifdef CONFIG_HAVE_OHCI
    usb_ohci_init();
    NVIC_EnableIRQ(USBH_IRQn);
#endif

#ifdef CONFIG_HAVE_EHCI
    usb_ehci_init();
    NVIC_EnableIRQ(HSUSBH_IRQn);
    HSUSBH->UPSCR[1] = 0x3000;
#endif

    usb_hub_init();
}


/**
  * @brief       Check and process status change of all down-stream hubs, including root hubs.
  *
  * @retval      0   There's no any hub events since the last call.
  * @retval      1   There's hub events occurred since the last call.
  */
int usbh_pooling_hubs()
{
    int  ret;

#ifdef CONFIG_HAVE_EHCI
    HSUSBH->UPSCR[1] = 0x3000;
#endif

    usb_poll_root_hubs();
    ret = hub_events();

    if (ret == 0)
        return 0;
    else
        return 1;
}

/**
  * @brief    Suspend USB Host Controller and devices
  * @return   None
  */
void usbh_suspend()
{
    /* set port suspend if connected */
    if (USBH->HcRhPortStatus[0] & 0x1)
        USBH->HcRhPortStatus[0] = 0x4;

    if (USBH->HcRhPortStatus[1] & 0x1)
        USBH->HcRhPortStatus[1] = 0x4;

    /* enable Device Remote Wakeup */
    USBH->HcRhStatus |= USBH_HcRhStatus_DRWE_Msk;

    /* enable USBH RHSC interrupt for system wakeup */
    USBH->HcInterruptEnable =  USBH_HcInterruptEnable_RHSC_Msk | USBH_HcInterruptEnable_RD_Msk;

    /* set Host Controller enter suspend state */
    USBH->HcControl = (USBH->HcControl & ~USBH_HcControl_HCFS_Msk) | (3 << USBH_HcControl_HCFS_Pos);

    if (HSUSBH->UPSCR[0] & 0x1)
        HSUSBH->UPSCR[0] |= HSUSBH_UPSCR_SUSPEND_Msk;
}


/**
  * @brief    Resume USB Host controller and devices
  * @return   None
  */
void usbh_resume(void)
{
    USBH->HcControl = (USBH->HcControl & ~USBH_HcControl_HCFS_Msk) | (1 << USBH_HcControl_HCFS_Pos);
    USBH->HcControl = (USBH->HcControl & ~USBH_HcControl_HCFS_Msk) | (2 << USBH_HcControl_HCFS_Pos);

    if (USBH->HcRhPortStatus[0] & 0x4)
        USBH->HcRhPortStatus[0] = 0x8;
    if (USBH->HcRhPortStatus[1] & 0x4)
        USBH->HcRhPortStatus[1] = 0x8;

    if (HSUSBH->UPSCR[0] & 0x1)
        HSUSBH->UPSCR[0] = (HSUSBH->UPSCR[0] & ~HSUSBH_UPSCR_SUSPEND_Msk) | HSUSBH_UPSCR_FPR_Msk;
}


/// @cond HIDDEN_SYMBOLS


void dump_ohci_regs()
{
    printf("Dump OCHI registers:\n");
    printf("    HcRevision         = 0x%x\n", USBH->HcRevision);
    printf("    HcControl          = 0x%x\n", USBH->HcControl);
    printf("    HcCommandStatus    = 0x%x\n", USBH->HcCommandStatus);
    printf("    HcInterruptStatus  = 0x%x\n", USBH->HcInterruptStatus);
    printf("    HcInterruptEnable  = 0x%x\n", USBH->HcInterruptEnable);
    printf("    HcInterruptDisable = 0x%x\n", USBH->HcInterruptDisable);
    printf("    HcHCCA             = 0x%x\n", USBH->HcHCCA);
    printf("    HcPeriodCurrentED  = 0x%x\n", USBH->HcPeriodCurrentED);
    printf("    HcControlHeadED    = 0x%x\n", USBH->HcControlHeadED);
    printf("    HcControlCurrentED = 0x%x\n", USBH->HcControlCurrentED);
    printf("    HcBulkHeadED       = 0x%x\n", USBH->HcBulkHeadED);
    printf("    HcBulkCurrentED    = 0x%x\n", USBH->HcBulkCurrentED);
    printf("    HcDoneHead         = 0x%x\n", USBH->HcDoneHead);
    printf("    HcFmInterval       = 0x%x\n", USBH->HcFmInterval);
    printf("    HcFmRemaining      = 0x%x\n", USBH->HcFmRemaining);
    printf("    HcFmNumber         = 0x%x\n", USBH->HcFmNumber);
    printf("    HcPeriodicStart    = 0x%x\n", USBH->HcPeriodicStart);
    printf("    HcLSThreshold      = 0x%x\n", USBH->HcLSThreshold);
    printf("    HcRhDescriptorA    = 0x%x\n", USBH->HcRhDescriptorA);
    printf("    HcRhDescriptorB    = 0x%x\n", USBH->HcRhDescriptorB);
    printf("    HcRhStatus         = 0x%x\n", USBH->HcRhStatus);
    printf("    HcRhPortStatus0    = 0x%x\n", USBH->HcRhPortStatus[0]);
    printf("    HcRhPortStatus1    = 0x%x\n", USBH->HcRhPortStatus[1]);
    printf("    HcPhyControl       = 0x%x\n", USBH->HcPhyControl);
    printf("    HcMiscControl      = 0x%x\n", USBH->HcMiscControl);
}

void dump_ohci_ports()
{
    printf("USBH port0=0x%x, port1=0x%x\n", USBH->HcRhPortStatus[0], USBH->HcRhPortStatus[1]);
}

void dump_ehci_regs()
{
    printf("Dump HSUSBH(EHCI) registers:\n");
    printf("    UCMDR    = 0x%x\n", HSUSBH->UCMDR);
    printf("    USTSR    = 0x%x\n", HSUSBH->USTSR);
    printf("    UIENR    = 0x%x\n", HSUSBH->UIENR);
    printf("    UFINDR   = 0x%x\n", HSUSBH->UFINDR);
    printf("    UPFLBAR  = 0x%x\n", HSUSBH->UPFLBAR);
    printf("    UCALAR   = 0x%x\n", HSUSBH->UCALAR);
    printf("    UASSTR   = 0x%x\n", HSUSBH->UASSTR);
    printf("    UCFGR    = 0x%x\n", HSUSBH->UCFGR);
    printf("    UPSCR0   = 0x%x\n", HSUSBH->UPSCR[0]);
    printf("    UPSCR1   = 0x%x\n", HSUSBH->UPSCR[1]);
    printf("    USBPCR0  = 0x%x\n", HSUSBH->USBPCR0);
    printf("    USBPCR1  = 0x%x\n", HSUSBH->USBPCR1);
}

void dump_ehci_ports()
{
    printf("HSUSBH port0=0x%x, port1=0x%x\n", HSUSBH->UPSCR[0], HSUSBH->UPSCR[1]);
}


void dump_ehci_qtd_list(struct ehci_qtd *qtd)
{
    qtd = (struct ehci_qtd *) ((u32)qtd & 0xfffffff0);
    while (1) {
        printf("   QTD addr = 0x%x\n", (u32)qtd);
        printf("        Next qtd:     0x%x\n", qtd->hw_next);
        printf("        Alt next qtd: 0x%x\n", qtd->hw_alt_next);
        printf("        token:        0x%x\n", qtd->hw_token);
        printf("        buffer ptr:   0x%x\n", qtd->hw_buf[0]);

        if (qtd->hw_next & 0x1)
            return;
        qtd = (struct ehci_qtd *)qtd->hw_next;
    };
}


void dump_ehci_asynclist(void)
{
    struct ehci_qh_hw  *qh;

    printf("ASYNCLISTADDR = 0x%x\n", HSUSBH->UCALAR);
    qh = (struct ehci_qh_hw *)HSUSBH->UCALAR;
    while (qh != NULL) {
        printf("*************************\n");
        printf("Queue Head address = 0x%x\n", (u32)qh);
        printf("    Next link:    0x%x\n", (u32)qh->hw_next);
        printf("    Info1:        0x%x\n", (u32)qh->hw_info1);
        printf("    Info2:        0x%x\n", (u32)qh->hw_info2);
        printf("    Next qtd:     0x%x\n", (u32)qh->hw_qtd_next);
        printf("    dev addr:     %d\n", qh->hw_info1 & 0x7f);
        printf("    endpoint:     %d\n", (qh->hw_info1 >> 8) & 0xf);
        if (0) { // (qh->hw_current)
            printf("    ========================================\n");
            dump_ehci_qtd_list((struct ehci_qtd *)qh->hw_qtd_next);
        }
        qh = (struct ehci_qh_hw *)qh->hw_next;
    }
}


void dump_ehci_asynclist_simple(char *msg)
{
    struct ehci_qh_hw  *qh;
    int  cnt = 0;

    if (msg != NULL)
        printf("%s - ", msg);

    printf("QH 0x%x ", HSUSBH->UCALAR);
    qh = (struct ehci_qh_hw *)HSUSBH->UCALAR;
    while ((qh != NULL) && (cnt++ < 5)) {
        if (!(HSUSBH->UCMDR & 0x20))
            break;
        printf(" => 0x%x (0x%x)", qh->hw_next, qh->hw_qtd_next);
        qh = (struct ehci_qh_hw *)(qh->hw_next & 0xfffffff0);
    }
    printf("\n");
}


/// @endcond HIDDEN_SYMBOLS

