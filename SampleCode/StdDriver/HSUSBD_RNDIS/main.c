/**************************************************************************//**
 * @file     main.c
 * @brief    Demonstrate how to implement a Remote Network Driver
 *           Interface Specification (RNDIS) device.
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "M480.h"
#include "rndis.h"

// Our MAC address
uint8_t g_au8MacAddr[6] = {0x00, 0x00, 0x00, 0x59, 0x16, 0x88};
// Buffer for holding received packet

uint32_t u32RxAct = 0;
uint32_t u32TxCnt = 0, u32RxCnt = 0;

// Descriptor pointers holds current Tx and Rx used by IRQ handler here.
uint32_t u32CurrentTxDesc, u32CurrentRxDesc;

// allocate 5 buffers for tx and other 5 for rx.
// 1 for usb, the other 4 for emac. 4 is the descriptor number allocated in this sample
// these buffers are shared between usb and emac so no memory copy is required while
// passing buffer content between two interfaces.

#ifdef __ICCARM__
#pragma data_alignment=4
uint8_t rndis_outdata[EMAC_TX_DESC_SIZE + 1][1580];
uint8_t rndis_indata[EMAC_RX_DESC_SIZE + 1][1580];
#else
uint8_t rndis_outdata[EMAC_TX_DESC_SIZE + 1][1580] __attribute__((aligned(32)));
uint8_t rndis_indata[EMAC_RX_DESC_SIZE + 1][1580] __attribute__((aligned(32)));
#endif

//for usb
uint32_t u32CurrentTxBuf = 0;
uint32_t u32CurrentRxBuf = 0;


void SYS_Init(void)
{
    uint32_t volatile i;

    /* Unlock protected registers */
    SYS_UnlockReg();

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

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(HSUSBD_MODULE);
    CLK_EnableModuleClock(EMAC_MODULE);
    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));
    // Configure MDC clock rate to HCLK / (127 + 1) = 1.5 MHz if system is running at 192 MHz
    CLK_SetModuleClock(EMAC_MODULE, 0, CLK_CLKDIV3_EMAC(127));

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    // Configure RMII pins
    SYS->GPA_MFPL = SYS_GPA_MFPL_PA6MFP_EMAC_RMII_RXERR | SYS_GPA_MFPL_PA7MFP_EMAC_RMII_CRSDV;
    SYS->GPC_MFPL = SYS_GPC_MFPL_PC6MFP_EMAC_RMII_RXD1 | SYS_GPC_MFPL_PC7MFP_EMAC_RMII_RXD0;
    SYS->GPC_MFPH = SYS_GPC_MFPH_PC8MFP_EMAC_RMII_REFCLK;
    SYS->GPE_MFPH = SYS_GPE_MFPH_PE8MFP_EMAC_RMII_MDC |
                    SYS_GPE_MFPH_PE9MFP_EMAC_RMII_MDIO |
                    SYS_GPE_MFPH_PE10MFP_EMAC_RMII_TXD0 |
                    SYS_GPE_MFPH_PE11MFP_EMAC_RMII_TXD1 |
                    SYS_GPE_MFPH_PE12MFP_EMAC_RMII_TXEN;

    // Enable high slew rate on all RMII TX output pins
    PE->SLEWCTL = (GPIO_SLEWCTL_HIGH << GPIO_SLEWCTL_HSREN10_Pos) |
                  (GPIO_SLEWCTL_HIGH << GPIO_SLEWCTL_HSREN11_Pos) |
                  (GPIO_SLEWCTL_HIGH << GPIO_SLEWCTL_HSREN12_Pos);

    /* Lock protected registers */
    SYS_LockReg();

}

extern uint32_t My_EMAC_RecvPkt(void);
/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main (void)
{
    unsigned int i;

    SYS_Init();
    UART_Open(UART0, 115200);

    printf("NuMicro HSUSBD RNDIS\n");

    // Select RMII interface by default
    EMAC_Open(g_au8MacAddr);
    EMAC_ENABLE_RX();
    EMAC_ENABLE_TX();
    EMAC_TRIGGER_RX();

    HSUSBD_Open(&gsHSInfo, RNDIS_ClassRequest, NULL);
    HSUSBD_SetVendorRequest(RNDIS_VendorRequest);
    /* Endpoint configuration */
    RNDIS_Init();
    NVIC_EnableIRQ(USBD20_IRQn);

    for (i = 0; i < EMAC_RX_DESC_SIZE + 1; i++)
    {
        *(uint32_t *)&rndis_indata[i][0] = 0x00000001; /* message type */
        *(uint32_t *)&rndis_indata[i][8] = 0x24;       /* data offset */
    }


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
        // Rx
        // Check if there any Rx packet queued in RX descriptor, if yes, move to USBD
        if ((i = My_EMAC_RecvPkt()) > 0)
        {
            RNDIS_InData(i);
            u32CurrentRxBuf++;
            if(u32CurrentRxBuf == EMAC_RX_DESC_SIZE + 1)
                u32CurrentRxBuf = 0;
        }
        // Tx
        RNDIS_ProcessOutData();
    }
}



/*** (C) COPYRIGHT 2019 Nuvoton Technology Corp. ***/

