/*************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    This Ethernet sample tends to get a DHCP lease from DHCP
 *           server. And use 192.168.10.10 as IP address it failed to
 *           get a lease. After IP address configured, this sample can
 *           reply to PING packets.
 *
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "net.h"


// Our MAC address
uint8_t g_au8MacAddr[6] = {0x00, 0x00, 0x00, 0x59, 0x16, 0x88};
// Our IP address
uint8_t volatile g_au8IpAddr[4] = {0, 0, 0, 0};
uint8_t auPkt[1514];
uint32_t u32PktLen;

// Descriptor pointers holds current Tx and Rx used by IRQ handler here.
uint32_t u32CurrentTxDesc, u32CurrentRxDesc;

/**
  * @brief  EMAC Tx interrupt handler.
  * @param  None
  * @return None
  */
void EMAC_TX_IRQHandler(void)
{
    // Clean up Tx resource occupied by previous sent packet(s)
    EMAC_SendPktDone();
}

/**
  * @brief  EMAC Rx interrupt handler.
  * @param  None
  * @return None
  */
void EMAC_RX_IRQHandler(void)
{

    while(1)
    {
        // Check if there's any packets available
        if(EMAC_RecvPkt(auPkt, &u32PktLen) == 0)
            break;
        // Process receive packet
        process_rx_packet(auPkt, u32PktLen);
        // Clean up Rx resource occupied by previous received packet
        EMAC_RecvPktDone();
    }
}

void SYS_Init(void)
{

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable External XTAL (4~24 MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for 12MHz clock ready */
    CLK_WaitClockReady( CLK_STATUS_HXTSTB_Msk);

    /* Switch HCLK clock source to HXT */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HXT,CLK_CLKDIV0_HCLK(1));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);
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
    SYS->GPA_MFPL |= SYS_GPA_MFPL_PA6MFP_EMAC_RMII_RXERR | SYS_GPA_MFPL_PA7MFP_EMAC_RMII_CRSDV;
    SYS->GPC_MFPL |= SYS_GPC_MFPL_PC6MFP_EMAC_RMII_RXD1 | SYS_GPC_MFPL_PC7MFP_EMAC_RMII_RXD0;
    SYS->GPC_MFPH |= SYS_GPC_MFPH_PC8MFP_EMAC_RMII_REFCLK;
    SYS->GPE_MFPH |= SYS_GPE_MFPH_PE8MFP_EMAC_RMII_MDC |
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


// This sample application can response to ICMP ECHO packets (ping)
// IP address is configure with DHCP, but if a lease cannot be acquired, a static IP will be used.
int main(void)
{

    SYS_Init();
    UART_Open(UART0, 115200);


    // Select RMII interface by default
    EMAC_Open(g_au8MacAddr);

    // Init phy
    EMAC_PhyInit();

    NVIC_EnableIRQ(EMAC_TX_IRQn);
    NVIC_EnableIRQ(EMAC_RX_IRQn);

    EMAC_ENABLE_RX();
    EMAC_ENABLE_TX();

    if (dhcp_start() < 0)
    {
        // Cannot get a DHCP lease, use static IP.
        printf("DHCP failed, use static IP 192.168.10.10\n");
        g_au8IpAddr[0] = 0xC0;
        g_au8IpAddr[1] = 0xA8;
        g_au8IpAddr[2] = 0x0A;
        g_au8IpAddr[3] = 0x0A;
    }
    while(1);

}


/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
