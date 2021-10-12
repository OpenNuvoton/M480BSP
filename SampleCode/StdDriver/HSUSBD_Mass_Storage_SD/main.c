/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * $Date: 16/08/02 5:11p $
 * @brief    Use SD as back end storage media to simulate a
 *           30 KB USB pen drive
 *
 * @note
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"
#include "massstorage.h"

uint8_t volatile g_u8SdInitFlag = 0;
extern int32_t g_TotalSectors;
/*--------------------------------------------------------------------------*/

void SDH0_IRQHandler(void)
{
    unsigned int volatile isr;
    unsigned int volatile ier;

    // FMI data abort interrupt
    if (SDH0->GINTSTS & SDH_GINTSTS_DTAIF_Msk)
    {
        /* ResetAllEngine() */
        SDH0->GCTL |= SDH_GCTL_GCTLRST_Msk;
    }

    //----- SD interrupt status
    isr = SDH0->INTSTS;
    if (isr & SDH_INTSTS_BLKDIF_Msk)
    {
        // block down
        SD0.DataReadyFlag = TRUE;
        SDH0->INTSTS = SDH_INTSTS_BLKDIF_Msk;
    }

    if (isr & SDH_INTSTS_CDIF_Msk)
    { // card detect
        //----- SD interrupt status
        // delay 10 us to sync the GPIO and SDH
        {
            int volatile delay = SystemCoreClock / 1000000 * 10;
            for(; delay > 0UL; delay--)
            {
                __NOP();
            }
            isr = SDH0->INTSTS;
        }

        if (isr & SDH_INTSTS_CDSTS_Msk)
        {
            printf("\n***** card remove !\n");
            SD0.IsCardInsert = FALSE;   // SDISR_CD_Card = 1 means card remove for GPIO mode
            memset(&SD0, 0, sizeof(SDH_INFO_T));
        }
        else
        {
            printf("***** card insert !\n");
            SDH_Open(SDH0, CardDetect_From_GPIO);
            if (SDH_Probe(SDH0))
            {
                g_u8SdInitFlag = 0;
                printf("SD initial fail!!\n");
            }
            else
            {
                g_u8SdInitFlag = 1;
                g_TotalSectors = SD0.totalSectorN;
            }
        }
        SDH0->INTSTS = SDH_INTSTS_CDIF_Msk;
    }

    // CRC error interrupt
    if (isr & SDH_INTSTS_CRCIF_Msk)
    {
        if (!(isr & SDH_INTSTS_CRC16_Msk))
        {
            //printf("***** ISR sdioIntHandler(): CRC_16 error !\n");
            // handle CRC error
        }
        else if (!(isr & SDH_INTSTS_CRC7_Msk))
        {
            if (!SD0.R3Flag)
            {
                //printf("***** ISR sdioIntHandler(): CRC_7 error !\n");
                // handle CRC error
            }
        }
        SDH0->INTSTS = SDH_INTSTS_CRCIF_Msk;      // clear interrupt flag
    }

    if (isr & SDH_INTSTS_DITOIF_Msk)
    {
        printf("***** ISR: data in timeout !\n");
        SDH0->INTSTS |= SDH_INTSTS_DITOIF_Msk;
    }

    // Response in timeout interrupt
    if (isr & SDH_INTSTS_RTOIF_Msk)
    {
        printf("***** ISR: response in timeout !\n");
        SDH0->INTSTS |= SDH_INTSTS_RTOIF_Msk;
    }
}


void SYS_Init(void)
{
    uint32_t volatile i;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable External XTAL (4~24 MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for 12MHz clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Switch HCLK clock source to HXT */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HXT,CLK_CLKDIV0_HCLK(1));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_PCLK0DIV2 | CLK_PCLKDIV_PCLK1DIV2;

    SYS->USBPHY &= ~SYS_USBPHY_HSUSBROLE_Msk;    /* select HSUSBD */
    /* Enable USB PHY */
    SYS->USBPHY = (SYS->USBPHY & ~(SYS_USBPHY_HSUSBROLE_Msk | SYS_USBPHY_HSUSBACT_Msk)) | SYS_USBPHY_HSUSBEN_Msk;
    for (i=0; i<0x1000; i++);      // delay > 10 us
    SYS->USBPHY |= SYS_USBPHY_HSUSBACT_Msk;

    /* Enable IP clock */
    CLK_EnableModuleClock(HSUSBD_MODULE);

    /* Select IP clock source */
    CLK_SetModuleClock(SDH0_MODULE, CLK_CLKSEL0_SDH0SEL_PLL, CLK_CLKDIV0_SDH0(10));
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable IP clock */
    CLK_EnableModuleClock(SDH0_MODULE);
    CLK_EnableModuleClock(UART0_MODULE);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/

    /* select multi-function pin */
    SYS->GPE_MFPL &= ~(SYS_GPE_MFPL_PE7MFP_Msk     | SYS_GPE_MFPL_PE6MFP_Msk     | SYS_GPE_MFPL_PE3MFP_Msk      | SYS_GPE_MFPL_PE2MFP_Msk);
    SYS->GPE_MFPL |=  (SYS_GPE_MFPL_PE7MFP_SD0_CMD | SYS_GPE_MFPL_PE6MFP_SD0_CLK | SYS_GPE_MFPL_PE3MFP_SD0_DAT1 | SYS_GPE_MFPL_PE2MFP_SD0_DAT0);

    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB5MFP_Msk      | SYS_GPB_MFPL_PB4MFP_Msk);
    SYS->GPB_MFPL |=  (SYS_GPB_MFPL_PB5MFP_SD0_DAT3 | SYS_GPB_MFPL_PB4MFP_SD0_DAT2);

    SYS->GPD_MFPH &= ~(SYS_GPD_MFPH_PD13MFP_Msk);
    SYS->GPD_MFPH |=  (SYS_GPD_MFPH_PD13MFP_SD0_nCD);

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

}

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main (void)
{
    /* Init System, IP clock and multi-function I/O
       In the end of SYS_Init() will issue SYS_LockReg()
       to lock protected register. If user want to write
       protected register, please issue SYS_UnlockReg()
       to unlock protected register if necessary */
    SYS_Init();

    /* Init UART to 115200-8n1 for print message */
    UART_Open(UART0, 115200);

    printf("M480 HSUSB Mass Storage\n");

    /* initial SD card */
    SDH_Open(SDH0, CardDetect_From_GPIO);
    if (SDH_Probe(SDH0) != 0)
    {
        g_u8SdInitFlag = 0;
        printf("SD initial fail!!\n");
    }
    else
        g_u8SdInitFlag = 1;

    HSUSBD_Open(&gsHSInfo, MSC_ClassRequest, NULL);

    /* Endpoint configuration */
    MSC_Init();

    /* Enable USBD interrupt */
    NVIC_EnableIRQ(USBD20_IRQn);

    /* Start transaction */
    while(1)
    {
        if (HSUSBD_IS_ATTACHED())
        {
            HSUSBD_Start();
            break;
        }
    }

    while(1)
    {
        if (g_hsusbd_Configured)
            MSC_ProcessCmd();
    }
}



/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/

