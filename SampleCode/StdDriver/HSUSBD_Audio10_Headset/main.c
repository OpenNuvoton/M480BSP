/***************************************************************************//**
 * @file     main.c
 * @version  1.0.0
 * @brief    This is an UAC1.0 sample and used to plays the sound send from PC
 *           through the USB interface
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "usbd_audio.h"

/*--------------------------------------------------------------------------*/
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
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    SYS->USBPHY &= ~SYS_USBPHY_HSUSBROLE_Msk;    /* select HSUSBD */

    /* Enable USB PHY */
    SYS->USBPHY = (SYS->USBPHY & ~(SYS_USBPHY_HSUSBROLE_Msk | SYS_USBPHY_HSUSBACT_Msk)) | SYS_USBPHY_HSUSBEN_Msk;
    for (i=0; i<0x1000; i++);      // delay > 10 us
    SYS->USBPHY |= SYS_USBPHY_HSUSBACT_Msk;

    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HXT, 0);

    /* Enable IP clock */
    CLK_EnableModuleClock(HSUSBD_MODULE);
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(I2C2_MODULE);
    CLK_EnableModuleClock(I2S0_MODULE);
    CLK_EnableModuleClock(PDMA_MODULE);
    CLK_EnableModuleClock(TMR0_MODULE);

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    SYS->GPF_MFPL = (SYS->GPF_MFPL & ~(SYS_GPF_MFPL_PF6MFP_Msk|SYS_GPF_MFPL_PF7MFP_Msk)) |
                    (SYS_GPF_MFPL_PF6MFP_I2S0_LRCK|SYS_GPF_MFPL_PF7MFP_I2S0_DO);
    SYS->GPF_MFPH = (SYS->GPF_MFPH & ~(SYS_GPF_MFPH_PF8MFP_Msk|SYS_GPF_MFPH_PF9MFP_Msk|SYS_GPF_MFPH_PF10MFP_Msk)) |
                    (SYS_GPF_MFPH_PF8MFP_I2S0_DI|SYS_GPF_MFPH_PF9MFP_I2S0_MCLK|SYS_GPF_MFPH_PF10MFP_I2S0_BCLK );

    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD0MFP_Msk | SYS_GPD_MFPL_PD1MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD0MFP_I2C2_SDA | SYS_GPD_MFPL_PD1MFP_I2C2_SCL);

    PF->SMTEN |= GPIO_SMTEN_SMTEN10_Msk;
    PD->SMTEN |= GPIO_SMTEN_SMTEN1_Msk;
}

/* Init I2C interface */
void I2C2_Init(void)
{
    /* Open I2C2 and set clock to 100k */
    I2C_Open(I2C2, 400000);

    /* Get I2C2 Bus Clock */
    printf("I2C clock %d Hz\n", I2C_GetBusClockFreq(I2C2));
}

//extern volatile uint8_t u8TxDataCntInBuffer;
//extern volatile uint8_t u8RxDataCntInBuffer;

int32_t main (void)
{
    uint32_t volatile i;
    /* Init System, IP clock and multi-function I/O
       In the end of SYS_Init() will issue SYS_LockReg()
       to lock protected register. If user want to write
       protected register, please issue SYS_UnlockReg()
       to unlock protected register if necessary */
    SYS_Init();

    /* Init UART to 115200-8n1 for print message */
    UART_Open(UART0, 115200);

#ifdef __HID__
    GPIO_Init();
#endif

    printf("\n");
    printf("+---------------------------------------------------------+\n");
    printf("|           NuMicro HSUSB UAC1.0 Sample Code              |\n");
    printf("+---------------------------------------------------------+\n");
    printf("HXT clock %d Hz\n", CLK_GetHXTFreq());
    printf("CPU clock %d Hz\n", CLK_GetCPUFreq());

    /* Init I2C2 to access NAU88L25 */
    I2C2_Init();

    /* Open I2S0 as slave mode */
    I2S_Open(I2S0, I2S_MODE_SLAVE, 48000, I2S_DATABIT_16, I2S_DISABLE_MONO, I2S_FORMAT_I2S);

    /* Set PE.13 low to enable phone jack on NuMaker board. */
    SYS->GPE_MFPH &= ~(SYS_GPE_MFPH_PE13MFP_Msk);
    GPIO_SetMode(PE, BIT13, GPIO_MODE_OUTPUT);
    PE13 = 0;

    // select source from HXT(12MHz)
    CLK_SetModuleClock(I2S0_MODULE, CLK_CLKSEL3_I2S0SEL_HXT, 0);

    /* Set MCLK and enable MCLK */
    I2S_EnableMCLK(I2S0, 12000000);
#if NAU8822
    NAU8822_Setup();
#else
    NAU88L25_Reset();
    /* Initialize NAU88L25 codec */
    CLK_SysTickDelay(10000);
    I2S0->CTL0 |= I2S_CTL0_ORDER_Msk;
    /* Initialize NAU88L25 codec */
    CLK_SysTickDelay(20000);
    NAU88L25_Setup();
#endif

    /* Configure PDMA */
    PDMA_Init();

#ifndef __FEEDBACK__
    /* Configure TIMER0 for adjusting NAU88L25's PLL */
    TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 100);
    TIMER_EnableInt(TIMER0);
    NVIC_SetPriority(TMR0_IRQn, 3);
    NVIC_EnableIRQ(TMR0_IRQn);
#endif

    HSUSBD_Open(&gsHSInfo, UAC_ClassRequest, UAC_SetInterface);

    /* Endpoint configuration */
    UAC_Init();
    NVIC_EnableIRQ(USBD20_IRQn);
    HSUSBD_CLR_SE0();
    while(1)
    {
        if (g_usbd_rxflag)
        {
            UAC_GetPlayData();
        }
        else if(u8AudioPlaying && (u8TxDataCntInBuffer < 1))
        {
            UAC_DeviceDisable(1);
        }

        if ((g_usbd_UsbAudioState == UAC_START_AUDIO_RECORD) && g_usbd_txflag)
        {
            UAC_SendRecData();
        }

//        if ((u8TxDataCntInBuffer != 0) && ((++i % 0x50000) == 0))
//        {
//            printf("%d <-> %d\n", u8TxDataCntInBuffer, u8RxDataCntInBuffer);
//        }
#ifdef __HID__
        HID_UpdateHidData();
#endif
    }
}



/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/

