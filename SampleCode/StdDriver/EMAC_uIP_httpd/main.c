/*************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    A uIP httpd sample for M480 MCU.
 *
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"
#include "uip.h"
#include "uip_arp.h"

#define BUF ((struct uip_eth_hdr *)&uip_buf[0])

// Our MAC address
struct uip_eth_addr ethaddr = {{0x00, 0x00, 0x00, 0x59, 0x16, 0x88}};

static uint8_t rxbuf[1514];
static uint8_t txbuf[1514];
uint32_t volatile u32PktLen;

// Descriptor pointers holds current Tx and Rx used by IRQ handler here.
uint32_t u32CurrentTxDesc, u32CurrentRxDesc;
static uint32_t volatile curTime = 0;
static uint32_t volatile prevTime = 0;  // increase every 0.5 sec


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
        // Get all recv data
        if(EMAC_RecvPkt(rxbuf, (uint32_t *)&u32PktLen) == 0)
            break;
        // Clean up Rx resource occupied by previous received packet
        EMAC_RecvPktDone();
    }


}

void TMR0_IRQHandler(void)
{
    curTime++;
    TIMER_ClearIntFlag(TIMER0);

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
    CLK_EnableModuleClock(TMR0_MODULE);

    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HXT, 0);

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



uint32_t uip_read(void)
{
    int len = 0;

    while((curTime == prevTime) && u32PktLen == 0);
    if(u32PktLen != 0)
    {
        NVIC_DisableIRQ(EMAC_RX_IRQn);

        if(u32PktLen != 0)
        {
            memcpy(uip_buf, rxbuf, u32PktLen);
            len = u32PktLen;
            u32PktLen = 0;
        }

        NVIC_EnableIRQ(EMAC_RX_IRQn);
    }
    else
    {
        prevTime++;
    }
    return len;
}


uint32_t uip_write(void)
{
    memcpy(txbuf, uip_buf, 40 + UIP_LLH_LEN);
    if(uip_len > (40 + UIP_LLH_LEN))
        memcpy(&txbuf[40 + UIP_LLH_LEN], (const void *)uip_appdata, uip_len - 40 - UIP_LLH_LEN);
    return EMAC_SendPkt(txbuf, uip_len);


}


// This sample application can response to ICMP ECHO packets (ping)
// IP address is configure with DHCP, but if a lease cannot be acquired, a static IP will be used.
int main(void)
{
    u8_t i, arptimer = 0;
    uip_ipaddr_t ipaddr = {0, 0};

    SYS_Init();
    UART_Open(UART0, 115200);

    printf("M480 uIP sample code start\n");

    // Select RMII interface by default
    EMAC_Open(ethaddr.addr);

    // Init phy
    EMAC_PhyInit();

    NVIC_EnableIRQ(EMAC_TX_IRQn);
    NVIC_EnableIRQ(EMAC_RX_IRQn);
    EMAC_ENABLE_RX();
    EMAC_ENABLE_TX();

    TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 2);
    TIMER_EnableInt(TIMER0);
    NVIC_EnableIRQ(TMR0_IRQn);
    TIMER_Start(TIMER0);


    uip_ipaddr(ipaddr, 192,168,0,5);
    uip_sethostaddr(ipaddr);
    uip_ipaddr(ipaddr, 192,168,0,1);
    uip_setdraddr(ipaddr);
    uip_ipaddr(ipaddr, 255,255,255,0);
    uip_setnetmask(ipaddr);

    uip_setethaddr(ethaddr);
    httpd_init();

    while(1)
    {
        /* Let the network device driver read an entire IP packet
           into the uip_buf. If it must wait for more than 0.5 seconds, it
           will return with the return value 0. If so, we know that it is
           time to call upon the uip_periodic(). Otherwise, the EMAC has
           received an IP packet that is to be processed by uIP. */
        uip_len = uip_read();
        if(uip_len == 0)
        {
            for(i = 0; i < UIP_CONNS; i++)
            {
                uip_periodic(i);
                /* If the above function invocation resulted in data that
                   should be sent out on the network, the global variable
                   uip_len is set to a value > 0. */
                if(uip_len > 0)
                {
                    uip_arp_out();
                    uip_write();
                }
            }

#if UIP_UDP
            for(i = 0; i < UIP_UDP_CONNS; i++)
            {
                uip_udp_periodic(i);
                /* If the above function invocation resulted in data that
                   should be sent out on the network, the global variable
                   uip_len is set to a value > 0. */
                if(uip_len > 0)
                {
                    uip_arp_out();
                    uip_write();
                }
            }
#endif /* UIP_UDP */

            /* Call the ARP timer function every 10 seconds. */
            if(++arptimer == 20)
            {
                uip_arp_timer();
                arptimer = 0;
            }

        }
        else
        {
            if(BUF->type == htons(UIP_ETHTYPE_IP))
            {
                uip_arp_ipin();
                uip_input();
                /* If the above function invocation resulted in data that
                   should be sent out on the network, the global variable
                   uip_len is set to a value > 0. */
                if(uip_len > 0)
                {
                    uip_arp_out();
                    uip_write();
                }
            }
            else if(BUF->type == htons(UIP_ETHTYPE_ARP))
            {
                uip_arp_arpin();
                /* If the above function invocation resulted in data that
                   should be sent out on the network, the global variable
                   uip_len is set to a value > 0. */
                if(uip_len > 0)
                {
                    uip_write();
                }
            }
        }
    }
}


/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
