/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    This sample demonstrates OTG HNP.
 *           This sample needs two M480 boards. One is as Host, the other is as Device.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>

#include "M480.h"

#include "usbh_lib.h"
#include "usbh_hid.h"
#include "usb.h"
#include "hid_mouse.h"

#ifdef __ICCARM__
#pragma data_alignment=32
uint8_t  g_buff_pool[1024];
#else
__align(32) uint32_t   g_buff_pool[1024];
#endif


uint8_t volatile gStartHNP = 0;
uint8_t volatile otg_role_change=0;
uint32_t volatile intcount = 0;
volatile uint32_t  g_tick_cnt;

void SysTick_Handler(void)
{
    g_tick_cnt++;
}

void enable_sys_tick(int ticks_per_second)
{
    g_tick_cnt = 0;
    SystemCoreClock = 12000000UL;
    if (SysTick_Config(SystemCoreClock / ticks_per_second)) {
        /* Setup SysTick Timer for 1 second interrupts  */
        printf("Set system tick error!!\n");
        while (1);
    }
}

uint32_t get_ticks()
{
    return g_tick_cnt;
}

/*
 *  This function is necessary for USB Host library.
 */
void delay_us(int usec)
{
    /*
     *  Configure Timer0, clock source from XTL_12M. Prescale 12
     */
    /* TIMER0 clock from HXT */
    CLK->CLKSEL1 = (CLK->CLKSEL1 & (~CLK_CLKSEL1_TMR0SEL_Msk)) | CLK_CLKSEL1_TMR0SEL_HXT;
    CLK->APBCLK0 |= CLK_APBCLK0_TMR0CKEN_Msk;
    TIMER0->CTL = 0;        /* disable timer */
    TIMER0->INTSTS = 0x3;   /* write 1 to clear for safty */
    TIMER0->CMP = usec;
    TIMER0->CTL = (11 << TIMER_CTL_PSC_Pos) | TIMER_ONESHOT_MODE | TIMER_CTL_CNTEN_Msk;

    while (!TIMER0->INTSTS);
}

void  dump_buff_hex(uint8_t *pucBuff, int nBytes)
{
    int     nIdx, i;

    nIdx = 0;
    while (nBytes > 0) {
        printf("0x%04X  ", nIdx);
        for (i = 0; (i < 16) && (nBytes > 0); i++) {
            printf("%02x ", pucBuff[nIdx + i]);
            nBytes--;
        }
        nIdx += 16;
        printf("\n");
    }
    printf("\n");
}


void  int_read_callback(HID_DEV_T *hdev, uint16_t ep_addr, uint8_t *rdata, uint32_t data_len)
{
    printf("Device [0x%x,0x%x] ep 0x%x, %d bytes received =>\n",
           hdev->idVendor, hdev->idProduct, ep_addr, data_len);
    dump_buff_hex(rdata, data_len);

    intcount++;
}

int  init_hid_device(HID_DEV_T *hdev)
{
    uint8_t   *data_buff;
    int       i, ret;

    data_buff = (uint8_t *)((uint32_t)g_buff_pool);

    printf("\n\n==================================\n");
    printf("  Init HID device : 0x%x\n", (int)hdev);
    printf("  VID: 0x%x, PID: 0x%x\n\n", hdev->idVendor, hdev->idProduct);

    ret = usbh_hid_get_report_descriptor(hdev, data_buff, 1024);
    if (ret > 0) {
        printf("\nDump report descriptor =>\n");
        dump_buff_hex(data_buff, ret);
    }

    /*
     *  Example: GET_PROTOCOL request.
     */
    ret = usbh_hid_get_protocol(hdev, data_buff);
    printf("[GET_PROTOCOL] ret = %d, protocol = %d\n", ret, data_buff[0]);

    /*
     *  Example: SET_PROTOCOL request.
     */
    ret = usbh_hid_set_protocol(hdev, data_buff[0]);
    printf("[SET_PROTOCOL] ret = %d, protocol = %d\n", ret, data_buff[0]);

    /*
     *  Example: GET_REPORT request on report ID 0x1, report type FEATURE.
     */
    ret = usbh_hid_get_report(hdev, RT_FEATURE, 0x1, data_buff, 64);
    if (ret > 0) {
        printf("[GET_REPORT] Data => ");
        for (i = 0; i < ret; i++)
            printf("%02x ", data_buff[i]);
        printf("\n");
    }

    gStartHNP = 1;

    printf("\nUSBH_HidStartIntReadPipe...\n");
    ret = usbh_hid_start_int_read(hdev, 0, int_read_callback);
    if ((ret != HID_RET_OK) && (ret != HID_RET_EP_USED))
        printf("usbh_hid_start_int_read failed!\n");
    else
        printf("Interrupt in transfer started...\n");

    return 0;
}

void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_PCLK0DIV2 | CLK_PCLKDIV_PCLK1DIV2;

    /* Select USBD */
    SYS->USBPHY = SYS_USBPHY_HSUSBEN_Msk | (0x3 << SYS_USBPHY_HSUSBROLE_Pos) | SYS_USBPHY_USBEN_Msk | SYS_USBPHY_SBO_Msk | (0x3 << SYS_USBPHY_USBROLE_Pos);
    delay_us(20);
    SYS->USBPHY |= SYS_USBPHY_HSUSBACT_Msk;

    /* Select IP clock source */
    CLK->CLKDIV0 = (CLK->CLKDIV0 & ~CLK_CLKDIV0_USBDIV_Msk) | CLK_CLKDIV0_USB(4);
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));

    /* Enable IP clock */
    CLK_EnableModuleClock(USBH_MODULE);
    CLK_EnableModuleClock(HSUSBD_MODULE);
    CLK_EnableModuleClock(HSOTG_MODULE);
    CLK_EnableModuleClock(UART0_MODULE);

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART0 multi-function pins */
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD2MFP_Msk | SYS_GPD_MFPL_PD3MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD2MFP_UART0_RXD | SYS_GPD_MFPL_PD3MFP_UART0_TXD);

    /* USB_VBUS_EN (USB 1.1 VBUS power enable pin) multi-function pin - PB.15     */
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~SYS_GPB_MFPH_PB15MFP_Msk) | SYS_GPB_MFPH_PB15MFP_USB_VBUS_EN;

    /* USB_VBUS_ST (USB 1.1 over-current detect pin) multi-function pin - PC.14   */
    SYS->GPC_MFPH = (SYS->GPC_MFPH & ~SYS_GPC_MFPH_PC14MFP_Msk) | SYS_GPC_MFPH_PC14MFP_USB_VBUS_ST;

    /* HSUSB_VBUS_EN (USB 2.0 VBUS power enable pin) multi-function pin - PB.10   */
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~SYS_GPB_MFPH_PB10MFP_Msk) | SYS_GPB_MFPH_PB10MFP_HSUSB_VBUS_EN;

    /* HSUSB_VBUS_ST (USB 2.0 over-current detect pin) multi-function pin - PB.11 */
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~SYS_GPB_MFPH_PB11MFP_Msk) | SYS_GPB_MFPH_PB11MFP_HSUSB_VBUS_ST;

    /* USB 1.1 port multi-function pin VBUS, D+, D-, and ID pins */
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA12MFP_Msk | SYS_GPA_MFPH_PA13MFP_Msk |
                       SYS_GPA_MFPH_PA14MFP_Msk | SYS_GPA_MFPH_PA15MFP_Msk);
    SYS->GPA_MFPH |= SYS_GPA_MFPH_PA12MFP_USB_VBUS | SYS_GPA_MFPH_PA13MFP_USB_D_N |
                     SYS_GPA_MFPH_PA14MFP_USB_D_P | SYS_GPA_MFPH_PA15MFP_USB_OTG_ID;
}

void UART0_Init(void)
{
    UART_Open(UART0, 115200);
}

extern struct usb_device *gOTG_Dev_pet;
void OTG_SetFeature(uint32_t value)
{
    /* 0x3 - b_hnp_enable, 0x4 - a_hnp_support */
    /* set feature */
    usb_control_msg(gOTG_Dev_pet, usb_sndctrlpipe(gOTG_Dev_pet, 0),
                    USB_REQ_SET_FEATURE, 0, value, 0, NULL, 0, 50000);
}

/**
  * @brief  USBOTG20_IRQHandler, HSOTG interrupt handler.
  * @param  None.
  * @retval None.
  */
void USBOTG20_IRQHandler(void)
{
    __IO uint32_t reg, en, i;

    en = HSOTG->INTEN;
    reg = HSOTG->INTSTS;

    if (reg & en & HSOTG_INTSTS_ROLECHGIF_Msk) {
        printf("[Role Change]\n");
        HSOTG_CLR_INT_FLAG(HSOTG_INTSTS_ROLECHGIF_Msk);
    }

    if (reg & en & HSOTG_INTSTS_GOIDLEIF_Msk) {
        printf("[Go Idle] 0x%x\n", HSOTG->STATUS);
        HSOTG_CLR_INT_FLAG(HSOTG_INTSTS_GOIDLEIF_Msk);
        otg_role_change = 0;
    }

    if (reg & en & HSOTG_INTSTS_IDCHGIF_Msk) {
        printf("[ID change 0x%x]\n", HSOTG->STATUS);
        HSOTG_CLR_INT_FLAG(HSOTG_INTSTS_IDCHGIF_Msk);
        if ((HSOTG->STATUS & HSOTG_STATUS_IDSTS_Msk) == 0)
            HSOTG->CTL |= HSOTG_CTL_BUSREQ_Msk;
    }

    if (reg & en & HSOTG_INTSTS_VBEIF_Msk) {
        printf("[VBUS Err]\n");
        HSOTG_CLR_INT_FLAG(HSOTG_INTSTS_VBEIF_Msk);
    }

    if (reg & en & HSOTG_INTSTS_SRPFIF_Msk) {
        printf("[SRP Fail]\n");
        HSOTG_CLR_INT_FLAG(HSOTG_INTSTS_SRPFIF_Msk);
    }

    if (reg & en & HSOTG_INTSTS_HNPFIF_Msk) {
        printf("[HNP Fail]\n");
        HSOTG_CLR_INT_FLAG(HSOTG_INTSTS_HNPFIF_Msk);
        otg_role_change = 0;
    }

    if (reg & en & HSOTG_INTSTS_SRPDETIF_Msk) {
        printf("[SRP Detect]\n");
        HSOTG_CLR_INT_FLAG(HSOTG_INTSTS_SRPDETIF_Msk);
        for (i=0; i<10000; i++);
        HSOTG->CTL |= HSOTG_CTL_BUSREQ_Msk;
    }

    if (reg & en & HSOTG_INTSTS_HOSTIF_Msk) {
        printf("[Act as Host]\n");
        HSOTG_DISABLE_INT(HSOTG_INTEN_HOSTIEN_Msk);
        HSOTG_CLR_INT_FLAG(HSOTG_INTSTS_HOSTIF_Msk);
        if (HSOTG->STATUS & 0x80) {
            if (otg_role_change == 3)
                otg_role_change = 4;
            else
                otg_role_change = 2;
        }
    }

    if (reg & en & HSOTG_INTSTS_PDEVIF_Msk) {
        printf("[Act as Peripheral]\n");
        HSOTG_DISABLE_INT(HSOTG_INTEN_PDEVIEN_Msk);
        HSOTG_CLR_INT_FLAG(HSOTG_INTSTS_PDEVIF_Msk);
        if (HSOTG->STATUS & 0x40) {
            if (otg_role_change == 2)
                otg_role_change = 4;
            else
                otg_role_change = 3;
        }
    }
}

/*----------------------------------------------------------------------------
  MAIN function
 *----------------------------------------------------------------------------*/
int32_t main(void)
{
    HID_DEV_T    *hdev;

    SYS_Init();                        /* Init System, IP clock and multi-function I/O */
    UART0_Init();                      /* Initialize UART0 */
    enable_sys_tick(100);

    printf("\n\n");
    printf("+------------------------------+\n");
    printf("|                              |\n");
    printf("|     USB HSOTG HNP sample     |\n");
    printf("|                              |\n");
    printf("+------------------------------+\n");

    HSOTG_ENABLE_PHY();
    HSOTG_ENABLE_ID_DETECT();
    NVIC_EnableIRQ(USBOTG20_IRQn);
    delay_us(1000);

    /* clear interrupt and enable relative interrupts */
    HSOTG_ENABLE_INT(HSOTG_INTEN_VBEIEN_Msk | HSOTG_INTEN_SRPFIEN_Msk | HSOTG_INTEN_HNPFIEN_Msk | HSOTG_INTEN_GOIDLEIEN_Msk |
                     HSOTG_INTEN_SRPDETIEN_Msk | HSOTG_INTEN_IDCHGIEN_Msk | HSOTG_INTEN_ROLECHGIEN_Msk);

    usbh_core_init();
    usbh_hid_init();

    while (1) {
        if(HSOTG_GET_STATUS(HSOTG_STATUS_IDSTS_Msk)) { /* B-device */
            if(HSOTG_GET_STATUS(HSOTG_STATUS_BVLD_Msk)) { /* plug-in */
                printf("B-device\n");
                /* wait role change to host */
                HSOTG_ENABLE_INT(HSOTG_INTEN_HOSTIEN_Msk);

                HSUSBD_Open(&gsHSInfo, HID_ClassRequest, NULL);
                HID_Init();
                HSOTG_ENABLE();
                HSOTG_ENABLE_PHY();
                HSUSBD_Start();
                NVIC_EnableIRQ(USBD20_IRQn);

                while(1) {
                    HID_UpdateMouseData();
                    if (otg_role_change) {
                        printf("Role change: B->A  %d\n", otg_role_change);
                        break;
                    }
                }
            }
        } else {
            printf("A-device\n");
            HSOTG_CLR_INT_FLAG(HSOTG_INTSTS_HOSTIF_Msk);
            HSOTG_ENABLE_INT(HSOTG_INTEN_PDEVIEN_Msk);
            HSOTG_ENABLE();
            usbh_pooling_hubs();
            while (1) {
                if (usbh_pooling_hubs()) {
                    hdev = usbh_hid_get_device_list();
                    if (hdev == NULL)
                        continue;
                    init_hid_device(hdev);
                }

                if (intcount > 3) {
                    usbh_hid_stop_int_read(hdev, 0);
                    delay_us(2000);
                    intcount = 0;
                    gStartHNP = 1;
                }

                if (gStartHNP) {
                    printf("do HMP...\n");
                    /* do HNP */
                    OTG_SetFeature(0x3);
                    delay_us(100000);
                    gStartHNP = 0;
                    /* port suspend */
                    HSOTG->CTL |= HSOTG_CTL_HNPREQEN_Msk;
                    HSOTG->CTL &= ~HSOTG_CTL_BUSREQ_Msk;
                    usbh_suspend();
                    printf("A suspend\n");
                }

                if (otg_role_change) {
                    printf("Role change: A->B  %d\n", otg_role_change);
                    break;
                }
            }
        }

        if (otg_role_change == 2) { /* b -> a */
            HSOTG_CLR_INT_FLAG(HSOTG_INTSTS_HOSTIF_Msk|HSOTG_INTSTS_PDEVIF_Msk);
            HSOTG_ENABLE_INT(HSOTG_INTEN_PDEVIEN_Msk);
            HSOTG_ENABLE();
            gStartHNP = intcount = 0;
            while (1) {
                if (usbh_pooling_hubs()) {
                    hdev = usbh_hid_get_device_list();
                    if (hdev == NULL)
                        continue;
                    init_hid_device(hdev);
                }

                if (intcount > 5) {
                    usbh_hid_stop_int_read(hdev, 0);
                    gStartHNP = 1;
                    intcount = 0;
                }

                if (gStartHNP) {
                    printf("\n\nwaiting...\n\n");
                    HSOTG->CTL &= ~HSOTG_CTL_BUSREQ_Msk;
                    gStartHNP = 0;
                    delay_us(5000);
                }

                if (otg_role_change == 4) {
                    printf("Role change: A->B  %d\n", otg_role_change);
                    break;
                }
            }
        }

        if (otg_role_change == 3) { /* a -> b */
            /* wait role change to host */
            HSOTG_CLR_INT_FLAG(HSOTG_INTSTS_HOSTIF_Msk|HSOTG_INTSTS_PDEVIF_Msk);
            HSOTG_ENABLE_INT(HSOTG_INTEN_HOSTIEN_Msk);

            HSUSBD_Open(&gsHSInfo, HID_ClassRequest, NULL);
            HID_Init();
            HSUSBD_Start();
            NVIC_EnableIRQ(USBD20_IRQn);

            while(1) {
                HID_UpdateMouseData();
                if (otg_role_change == 4) {
                    printf("Role change: B->A  %d\n", otg_role_change);
                    break;
                }
            }
        }
        if (otg_role_change == 4)
            break;
    }
    printf("\n finish HNP testing ..\n");
    while(1);
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
