/******************************************************************************
 * @file     main.c
 * @brief    Use internal Flash as back end storage media to simulate a USB pen drive.
 * @version  2.0.0
 * @date     27, Aug, 2016
 *
 * @note
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "massstorage.h"


#define DATA_FLASH_BASE  0x40000


void SYS_Init(void)
{
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
    /* Set PA.12 ~ PA.14 to input mode */
    PA->MODE &= ~(GPIO_MODE_MODE12_Msk | GPIO_MODE_MODE13_Msk | GPIO_MODE_MODE14_Msk);
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA12MFP_Msk|SYS_GPA_MFPH_PA13MFP_Msk|SYS_GPA_MFPH_PA14MFP_Msk|SYS_GPA_MFPH_PA15MFP_Msk);
    SYS->GPA_MFPH |= (SYS_GPA_MFPH_PA12MFP_USB_VBUS|SYS_GPA_MFPH_PA13MFP_USB_D_N|SYS_GPA_MFPH_PA14MFP_USB_D_P|SYS_GPA_MFPH_PA15MFP_USB_OTG_ID);

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

}


int32_t main (void)
{
    uint32_t au32Config[2];

    SYS_Init();
    UART_Open(UART0, 115200);

    printf("+-------------------------------------------------------+\n");
    printf("|          NuMicro USB MassStorage Sample Code          |\n");
    printf("+-------------------------------------------------------+\n");

    SYS_UnlockReg();
    /* Enable FMC ISP function */
    FMC_Open();

    /* Check if Data Flash Size is 64K. If not, to re-define Data Flash size and to enable Data Flash function */
    if (FMC_ReadConfig(au32Config, 2) < 0)
        return -1;

    if (((au32Config[0] & 0x01) == 1) || (au32Config[1] != DATA_FLASH_BASE) )
    {
        FMC_ENABLE_CFG_UPDATE();
        au32Config[0] &= ~0x1;
        au32Config[1] = DATA_FLASH_BASE;
        if (FMC_WriteConfig(au32Config, 2) < 0)
            return -1;

        FMC_ReadConfig(au32Config, 2);
        if (((au32Config[0] & 0x01) == 1) || (au32Config[1] != DATA_FLASH_BASE))
        {
            printf("Error: Program Config Failed!\n");
            /* Disable FMC ISP function */
            FMC_Close();
            SYS_LockReg();
            return -1;
        }

        printf("chip reset\n");
        /* Reset Chip to reload new CONFIG value */
        SYS->IPRST0 = SYS_IPRST0_CHIPRST_Msk;
    }

    printf("NuMicro USB MassStorage Start!\n");

    USBD_Open(&gsInfo, MSC_ClassRequest, NULL);
    USBD_SetConfigCallback(MSC_SetConfig);
    /* Endpoint configuration */
    MSC_Init();
    USBD_Start();

    NVIC_EnableIRQ(USBD_IRQn);

    while(1)
    {
        MSC_ProcessCmd();
    }
}



/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/

