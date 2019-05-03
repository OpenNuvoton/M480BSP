/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Automatically search and read new firmware from USB drive, if found,
 *           update APROM flash with it. This sample requires booting from LDROM with IAP.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include <stdio.h>
#include <string.h>

#include "NuMicro.h"

#include "usbh_lib.h"
#include "ff.h"
#include "diskio.h"


#define DATA_FLASH_BASE              0x30000
#define USB_UPDATER_BASE             0x20000

/*
        This sample program assumed flash resource allocated like the following figure:

                                     Address            Description
                                     ---------------    -------------------------
     +---------------------------+   0x200FFF
     |  SPROM                    |                      User application in SPROM
     +---------------------------+   0x200000
     |                           |
     ~                           ~
     |                           |
     +---------------------------+   0x100FFF
     |  LDROM                    |                      USB firmware update code boots from LDROM
     |  (updater boot part)      |                      and branches to USB_UPDATER_BASE in APROM.
     +---------------------------+   0x100000
     |                           |
     ~                           ~
     |                           |
     +---------------------------+   0x07FFFF
     |  Data Flash               |
     |                           |
     +---------------------------+   DATA_FLASH_BASE
     |  APROM                    |                      USB firmware updater USB function part.
     |(updater USB function part)|
     +---------------------------+   USB_UPDATER_BASE
     |                           |
     |  APROM                    |                      User application
     |                           |
     |                           |
     |                           |
     |                           |
     +---------------------------+   0x000000
*/


extern void usbh_firmware_update(void);     /* USB firmware update main function          */


volatile uint32_t  g_tick_cnt;              /* SYSTICK timer counter                      */

void SysTick_Handler(void)
{
    g_tick_cnt++;                           /* timer tick counting 100 per second         */
}

void enable_sys_tick(int ticks_per_second)
{
    g_tick_cnt = 0;
    if (SysTick_Config(SystemCoreClock / ticks_per_second))
    {
        /* Setup SysTick Timer for 1 second interrupts  */
        printf("Set system tick error!!\n");
        while (1);
    }
}

/*
 *  This function is necessary for USB Host library.
 */
uint32_t get_ticks()                        /* Get timer tick                             */
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
    TIMER0->INTSTS = (TIMER_INTSTS_TIF_Msk | TIMER_INTSTS_TWKF_Msk);   /* write 1 to clear for safety */
    TIMER0->CMP = usec;
    TIMER0->CTL = (11 << TIMER_CTL_PSC_Pos) | TIMER_ONESHOT_MODE | TIMER_CTL_CNTEN_Msk;

    while (!TIMER0->INTSTS);
}

/*---------------------------------------------------------*/
/* User Provided RTC Function for FatFs module             */
/*---------------------------------------------------------*/
/* This is a real time clock service to be called from     */
/* FatFs module. Any valid time must be returned even if   */
/* the system does not support an RTC.                     */
/* This function is not required in read-only cfg.         */
/*---------------------------------------------------------*/
unsigned long get_fattime (void)
{
    unsigned long tmr;
    tmr=0x00000;
    return tmr;
}

void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable USBH module clock */
    CLK_EnableModuleClock(USBH_MODULE);

    /* USB Host desired input clock is 48 MHz. Set as PLL divided by 4 (192/4 = 48) */
    CLK->CLKDIV0 = (CLK->CLKDIV0 & ~CLK_CLKDIV0_USBDIV_Msk) | CLK_CLKDIV0_USB(4);

    /* Enable USBD and OTG clock */
    CLK->APBCLK0 |= CLK_APBCLK0_USBDCKEN_Msk | CLK_APBCLK0_OTGCKEN_Msk;

    /* Set OTG as USB Host role */
    SYS->USBPHY = SYS_USBPHY_HSUSBEN_Msk | (0x1 << SYS_USBPHY_HSUSBROLE_Pos) | SYS_USBPHY_USBEN_Msk | SYS_USBPHY_SBO_Msk | (0x1 << SYS_USBPHY_USBROLE_Pos);
    delay_us(20);
    SYS->USBPHY |= SYS_USBPHY_HSUSBACT_Msk;

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

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
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

int32_t main(void)
{
    SYS_Init();                        /* Init System, IP clock and multi-function I/O    */

    UART0_Init();                      /* Initialize UART0                                */

    enable_sys_tick(100);

    printf("\n\n");
    printf("+---------------------------------------------+\n");
    printf("|                                             |\n");
    printf("|  USB Host Firmware Update sample program    |\n");
    printf("|                                             |\n");
    printf("+---------------------------------------------+\n");

    FMC_Open();                             /* Enable FMC ISP functions                   */

    usbh_core_init();
    usbh_umas_init();
    usbh_pooling_hubs();

    delay_us(100000);                       /* delay 100ms for some slow response pen drive. */

    usbh_pooling_hubs();
    usbh_pooling_hubs();

    usbh_firmware_update();

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;   /* disable SYSTICK (prevent interrupt)   */

    /* Switch HCLK clock source to HIRC. Restore HCLK to default setting. */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC,CLK_CLKDIV0_HCLK(1));

    FMC_SetVectorPageAddr(0);               /* Set vector remap to APROM address 0x0      */

    FMC_SET_APROM_BOOT();                   /* Change boot source as APROM                */

    SYS->IPRST0 = SYS_IPRST0_CPURST_Msk;    /* Let CPU reset. Will boot from APROM.       */
    /* This reset can bring up user application   */
    /* in APROM address 0x0.                      */
    /* Please make sure user application has been */
    /* programmed to APROM 0x0 at this time.      */
    while(1);
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/

