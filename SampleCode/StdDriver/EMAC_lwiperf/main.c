/*************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    A LwIP iperf sample on M480
 *
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

#include "lwip/tcpip.h"
#include "netif/ethernetif.h"
#include "lwip/apps/lwiperf.h"
#include "lwip/etharp.h"
#include "lwip/netif.h"
#include "lwip/timeouts.h"
#include "lwip/init.h"
#include "netif/m480_emac.h"

extern struct pbuf *queue_try_get(void);

unsigned char my_mac_addr[6] = {0x00, 0x00, 0x00, 0x55, 0x66, 0x77};

static err_t netif_output(struct netif *netif, struct pbuf *p)
{
    uint16_t len = 0;
    uint8_t *buf

    LINK_STATS_INC(link.xmit);

    __disable_irq();
    buf = EMAC_get_tx_buf();
    if(buf)
        len = pbuf_copy_partial(p, buf, p->tot_len, 0);
    /* Start MAC transmit here */
    if(len)
        EMAC_trigger_tx(len);
    __enable_irq();

    return ERR_OK;
}

#if 0
static void netif_status_callback(struct netif *netif)
{
    printf("netif status changed %s\n", ip4addr_ntoa(netif_ip4_addr(netif)));
}
#endif

static err_t m480_netif_init(struct netif *netif)
{
    netif->linkoutput = netif_output;
    netif->output     = etharp_output;
    netif->mtu        = 1500;
    netif->flags      = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_ETHERNET;

    SMEMCPY(netif->hwaddr, my_mac_addr, sizeof(netif->hwaddr));
    netif->hwaddr_len = sizeof(netif->hwaddr);
    EMAC_init(my_mac_addr);

    return ERR_OK;
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

int main(void)
{
    struct netif netif;
    //void *iperf;
    ip_addr_t ipaddr;
    ip_addr_t netmask;
    ip_addr_t gw;

    SYS_Init();
    UART_Open(UART0, 115200);

    // Set timer frequency to 100HZ
    TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 100);

    // Enable timer interrupt
    TIMER_EnableInt(TIMER0);
    NVIC_EnableIRQ(TMR0_IRQn);

    // Start Timer 0
    TIMER_Start(TIMER0);

    printf("M480 LwIP sample code start\n");

    IP4_ADDR(&gw, 192, 168, 0, 99);
    IP4_ADDR(&ipaddr, 192, 168, 0, 227);
    IP4_ADDR(&netmask, 255, 255, 255, 0);

    lwip_init();
    netif_add(&netif, &ipaddr, &netmask, &gw, NULL, m480_netif_init, netif_input);
    netif.name[0] = 'e';
    netif.name[1] = '0';

    netif_set_default(&netif);
    netif_set_up(&netif);
    netif_set_link_up(&netif);
    NVIC_EnableIRQ(EMAC_TX_IRQn);
    NVIC_EnableIRQ(EMAC_RX_IRQn);

    lwiperf_start_tcp_server_default(NULL, NULL);

    while (1)
    {
        struct pbuf* p;
#if 0   // Only enable under the circumstance cable may be plug/unplug 
        /* Check link state, e.g. via MDIO communication with PHY */
        if(link_state_changed())
        {
            if(link_is_up())
            {
                netif_set_link_up(&netif);
            }
            else
            {
                netif_set_link_down(&netif);
            }
        }
#endif
        /* Check for received frames, feed them to lwIP */
        __disable_irq();
        p = queue_try_get();
        __enable_irq();
        if(p != NULL)
        {
            if(netif.input(p, &netif) != ERR_OK)
            {
                pbuf_free(p);
            }
        }
        /* Cyclic lwIP timers check */
        sys_check_timeouts();
    }
}


/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
