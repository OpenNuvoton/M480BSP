/******************************************************************************
 * @file     main.c
 * @brief    USB Mass Storage Device CD-ROM Emulation.
 * @version  2.0.0
 * @date     12, Aug, 2016
 *
 * @note
 *
 *           This sample simulate a USB CDROM with a test.txt file.
 *           User can change file within CDROM, follow steps below:
 *
 *           (1) Generate an ISO file via ISO Workshop.
 *               http://www.glorylogic.com/iso-workshop/
 *               -> Option : Select ISO9660 Level1
 *
 *           (2) Convert the .iso file into C code file via SRecord tool
 *               http://srecord.sourceforge.net
 *
 *               -> srec_cat InputFile.iso -binary -o OutputFile.c -C-Array
 *
 *           (3) The System Area, the first 32768 data bytes is unused by ISO 9660.
 *               Therefore, user need to delete the first 32768 bytes on the DiskImg.c
 *               manually to save space. Finally, replace DiskImg.c in this project.
 *
 *               -> EPROM_LENGTH in DiskImg.c is the size of your .iso image.
 *                  Define MSC_ImageSize value in massstorage.h in this project.
 *                  Modify MSC_ImageSize value to hold the file size.
 *
 *
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "massstorage.h"

#define CRYSTAL_LESS        1

/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/

void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

#if (!CRYSTAL_LESS)
    /* Enable External XTAL (4~24 MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for 12MHz clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Switch HCLK clock source to HXT */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HXT,CLK_CLKDIV0_HCLK(1));
#endif

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_PCLK0DIV2 | CLK_PCLKDIV_PCLK1DIV2;

    /* Select USBD */
    SYS->USBPHY = (SYS->USBPHY & ~SYS_USBPHY_USBROLE_Msk) | SYS_USBPHY_USBEN_Msk | SYS_USBPHY_SBO_Msk;

    /* Select IP clock source */
    CLK->CLKDIV0 = (CLK->CLKDIV0 & ~CLK_CLKDIV0_USBDIV_Msk) | CLK_CLKDIV0_USB(4);

    /* Enable IP clock */
    CLK_EnableModuleClock(USBD_MODULE);

    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HIRC, CLK_CLKDIV0_UART0(1));

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA12MFP_Msk|SYS_GPA_MFPH_PA13MFP_Msk|SYS_GPA_MFPH_PA14MFP_Msk|SYS_GPA_MFPH_PA15MFP_Msk);
    SYS->GPA_MFPH |= (SYS_GPA_MFPH_PA12MFP_USB_VBUS|SYS_GPA_MFPH_PA13MFP_USB_D_N|SYS_GPA_MFPH_PA14MFP_USB_D_P|SYS_GPA_MFPH_PA15MFP_USB_OTG_ID);

    /* Init UART0 multi-function pins */
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD2MFP_Msk | SYS_GPD_MFPL_PD3MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD2MFP_UART0_RXD | SYS_GPD_MFPL_PD3MFP_UART0_TXD);

}


/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main (void)
{
    SYS_Init();
    UART_Open(UART0, 115200);

    printf("+-------------------------------------------------------+\n");
    printf("|          NuMicro USB MassStorage Sample Code          |\n");
    printf("+-------------------------------------------------------+\n");

    printf("NnMicro USB MassStorage Start!\n");

    USBD_Open(&gsInfo, MSC_ClassRequest, NULL);
    /* Endpoint configuration */
    MSC_Init();
    USBD_Start();

#if CRYSTAL_LESS
    /* Waiting for USB signal before auto trim */
    USBD->INTSTS = USBD_INTSTS_SOFIF_Msk;
    while((USBD->INTSTS & USBD_INTSTS_SOFIF_Msk) == 0);
    /* Enable USB clock trim function */
    SYS->IRCTCTL = 0x01;
    SYS->IRCTCTL |= SYS_IRCTCTL_REFCKSEL_Msk;
#endif

    NVIC_EnableIRQ(USBD_IRQn);

    while(1) {

#if CRYSTAL_LESS
        /* Re-start auto trim when any error found */
        if (SYS->IRCTISTS & (SYS_IRCTISTS_CLKERRIF_Msk | SYS_IRCTISTS_TFAILIF_Msk)) {
            SYS->IRCTISTS = SYS_IRCTISTS_CLKERRIF_Msk | SYS_IRCTISTS_TFAILIF_Msk;

            /* Waiting for USB signal before auto trim */
            USBD->INTSTS = USBD_INTSTS_SOFIF_Msk;
            while((USBD->INTSTS & USBD_INTSTS_SOFIF_Msk) == 0);

            /* Re-enable Auto Trim */
            SYS->IRCTCTL = 0x01;
            SYS->IRCTCTL |= SYS_IRCTCTL_REFCKSEL_Msk;
            //printf("USB trim fail. Just retry. SYS->IRCTISTS = 0x%x, SYS->IRCTCTL = 0x%x\n", SYS->IRCTISTS, SYS->IRCTCTL);
        }
#endif
        MSC_ProcessCmd();
    }
}



/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/

