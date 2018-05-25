/*************************************************************************//**
 * @file     m480_emac.c
 * @version  V1.00
 * @brief    M480 LwIP NO_SYS driver
 *
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include "NuMicro.h"
#include "netif/m480_emac.h"


#define TRIGGER_RX()    do{EMAC->RXST = 0;}while(0)
#define TRIGGER_TX()    do{EMAC->TXST = 0;}while(0)
#define ENABLE_TX()     do{EMAC->CTL |= EMAC_CTL_TXON_Msk;}while(0)
#define ENABLE_RX()     do{EMAC->CTL |= EMAC_CTL_RXON_Msk;}while(0)
#define DISABLE_TX()    do{EMAC->CTL &= ~EMAC_CTL_TXON_Msk;}while(0)
#define DISABLE_RX()    do{EMAC->CTL &= ~EMAC_CTL_RXON_Msk;}while(0)

#ifdef __ICCARM__
#pragma data_alignment=4
static struct eth_descriptor rx_desc[RX_DESCRIPTOR_NUM];
static struct eth_descriptor tx_desc[TX_DESCRIPTOR_NUM];
#else
static struct eth_descriptor rx_desc[RX_DESCRIPTOR_NUM] __attribute__ ((aligned(4)));
static struct eth_descriptor tx_desc[TX_DESCRIPTOR_NUM] __attribute__ ((aligned(4)));
#endif
struct eth_descriptor volatile *cur_tx_desc_ptr, *cur_rx_desc_ptr, *fin_tx_desc_ptr;

static u8_t rx_buf[RX_DESCRIPTOR_NUM][PACKET_BUFFER_SIZE];
static u8_t tx_buf[TX_DESCRIPTOR_NUM][PACKET_BUFFER_SIZE];
static int plugged = 0;

//extern void ethernetif_input(u16_t len, u8_t *buf);
//extern void ethernetif_loopback_input(struct pbuf *p);
extern uint32_t queue_try_put(struct pbuf *p);

void EMAC_RX_IRQHandler(void)
{
    unsigned int status;

    status = EMAC->INTSTS & 0xFFFF;
    EMAC->INTSTS = status;

    if (status & EMAC_INTSTS_RXBEIF_Msk)
    {
        // Shouldn't goes here, unless descriptor corrupted
        while(1);
    }

    do
    {
        status = cur_rx_desc_ptr->status1;

        if(status & OWNERSHIP_EMAC)
            break;

        if (status & RXFD_RXGD)
        {
            /* Allocate pbuf from pool (avoid using heap in interrupts) */
            struct pbuf* p = pbuf_alloc(PBUF_RAW, status & 0xFFFF, PBUF_POOL);

            if(p != NULL)
            {
                /* Copy ethernet frame into pbuf */
                pbuf_take(p, cur_rx_desc_ptr->buf, status & 0xFFFF);

                /* Put in a queue which is processed in main loop */
                if(!queue_try_put(p))
                {
                    /* queue is full -> packet loss */
                    //printf("drop\n");
                    pbuf_free(p);
                } //else
                //printf("get\n");
            }


        }

        cur_rx_desc_ptr->status1 = OWNERSHIP_EMAC;
        cur_rx_desc_ptr = cur_rx_desc_ptr->next;

    }
    while (1);

    TRIGGER_RX();

}

void EMAC_TX_IRQHandler(void)
{
    unsigned int cur_entry, status;

    status = EMAC->INTSTS & 0xFFFF0000;
    EMAC->INTSTS = status;

    if(status & EMAC_INTSTS_TXBEIF_Msk)
    {
        // Shouldn't goes here, unless descriptor corrupted
        while(1);
    }

    cur_entry = EMAC->CTXDSA;

    while (cur_entry != (u32_t)fin_tx_desc_ptr)
    {

        fin_tx_desc_ptr = fin_tx_desc_ptr->next;
    }

}

static void mdio_write(u8_t addr, u8_t reg, u16_t val)
{

    EMAC->MIIMDAT = val;
    EMAC->MIIMCTL = reg |
                    (addr << EMAC_MIIMCTL_PHYADDR_Pos) |
                    EMAC_MIIMCTL_MDCON_Msk |
                    EMAC_MIIMCTL_BUSY_Msk |
                    EMAC_MIIMCTL_WRITE_Msk;

    while (EMAC->MIIMCTL & EMAC_MIIMCTL_BUSY_Msk);    // wait busy flag clear

}


static u16_t mdio_read(u8_t addr, u8_t reg)
{
    EMAC->MIIMCTL = reg |
                    (addr << EMAC_MIIMCTL_PHYADDR_Pos) |
                    EMAC_MIIMCTL_MDCON_Msk |
                    EMAC_MIIMCTL_BUSY_Msk;

    while (EMAC->MIIMCTL & EMAC_MIIMCTL_BUSY_Msk);    // wait busy flag clear

    return EMAC->MIIMDAT;
}

static int reset_phy(void)
{

    u16_t reg;
    u32_t delay;


    mdio_write(CONFIG_PHY_ADDR, MII_BMCR, BMCR_RESET);

    delay = 2000;
    while(delay-- > 0)
    {
        if((mdio_read(CONFIG_PHY_ADDR, MII_BMCR) & BMCR_RESET) == 0)
            break;

    }

    if(delay == 0)
    {
        printf("Reset phy failed\n");
        return(-1);
    }

    mdio_write(CONFIG_PHY_ADDR, MII_ADVERTISE, ADVERTISE_CSMA |
               ADVERTISE_10HALF |
               ADVERTISE_10FULL |
               ADVERTISE_100HALF |
               ADVERTISE_100FULL);

    reg = mdio_read(CONFIG_PHY_ADDR, MII_BMCR);
    mdio_write(CONFIG_PHY_ADDR, MII_BMCR, reg | BMCR_ANRESTART);

    delay = 200000;
    while(delay-- > 0)
    {
        if((mdio_read(CONFIG_PHY_ADDR, MII_BMSR) & (BMSR_ANEGCOMPLETE | BMSR_LSTATUS))
                == (BMSR_ANEGCOMPLETE | BMSR_LSTATUS))
            break;
    }

    if(delay == 0)
    {
        printf("AN failed. Set to 100 FULL\n");
        EMAC->CTL |= EMAC_CTL_OPMODE_Msk | EMAC_CTL_FUDUP_Msk;
        plugged = 0;
        return(-1);
    }
    else
    {
        reg = mdio_read(CONFIG_PHY_ADDR, MII_LPA);
        plugged = 1;

        if(reg & ADVERTISE_100FULL)
        {
            printf("100 full\n");
            EMAC->CTL |= EMAC_CTL_OPMODE_Msk | EMAC_CTL_FUDUP_Msk;
        }
        else if(reg & ADVERTISE_100HALF)
        {
            printf("100 half\n");
            EMAC->CTL = (EMAC->CTL & ~EMAC_CTL_FUDUP_Msk) | EMAC_CTL_OPMODE_Msk;
        }
        else if(reg & ADVERTISE_10FULL)
        {
            printf("10 full\n");
            EMAC->CTL = (EMAC->CTL & ~EMAC_CTL_OPMODE_Msk) | EMAC_CTL_FUDUP_Msk;
        }
        else
        {
            printf("10 half\n");
            EMAC->CTL &= ~(EMAC_CTL_OPMODE_Msk | EMAC_CTL_FUDUP_Msk);
        }
    }

    return(0);
}


static void init_tx_desc(void)
{
    u32_t i;


    cur_tx_desc_ptr = fin_tx_desc_ptr = (struct eth_descriptor *)(&tx_desc[0]);

    for(i = 0; i < TX_DESCRIPTOR_NUM; i++)
    {
        tx_desc[i].status1 = TXFD_PADEN | TXFD_CRCAPP | TXFD_INTEN;
        tx_desc[i].buf = (unsigned char *)(&tx_buf[i][0]);
        tx_desc[i].status2 = 0;
        tx_desc[i].next = (struct eth_descriptor *)(&tx_desc[(i + 1) % TX_DESCRIPTOR_NUM]);
    }
    EMAC->TXDSA = (unsigned int)&tx_desc[0];
    return;
}

static void init_rx_desc(void)
{
    u32_t i;


    cur_rx_desc_ptr = (struct eth_descriptor *)(&rx_desc[0]);

    for(i = 0; i < RX_DESCRIPTOR_NUM; i++)
    {
        rx_desc[i].status1 = OWNERSHIP_EMAC;
        rx_desc[i].buf = (unsigned char *)(&rx_buf[i][0]);
        rx_desc[i].status2 = 0;
        rx_desc[i].next = (struct eth_descriptor *)(&rx_desc[(i + 1) % RX_DESCRIPTOR_NUM]);
    }
    EMAC->RXDSA = (unsigned int)&rx_desc[0];
    return;
}

static void set_mac_addr(u8_t *addr)
{

    EMAC->CAM0M = (addr[0] << 24) |
                  (addr[1] << 16) |
                  (addr[2] << 8) |
                  addr[3];
    EMAC->CAM0L = (addr[4] << 24) |
                  (addr[5] << 16);

    EMAC->CAMCTL = EMAC_CAMCTL_ABP_Msk | EMAC_CAMCTL_CMPEN_Msk;
    EMAC->CAMEN = 1;    // Enable CAM entry 0

}

void EMAC_init(u8_t *mac_addr)
{


    // Reset MAC
    EMAC->CTL = EMAC_CTL_RST_Msk;
    while(EMAC->CTL & EMAC_CTL_RST_Msk) {}

    init_tx_desc();
    init_rx_desc();

    set_mac_addr(mac_addr);  // need to reconfigure hardware address 'cos we just RESET emc...
    reset_phy();

    EMAC->CTL |= EMAC_CTL_STRIPCRC_Msk | EMAC_CTL_RXON_Msk | EMAC_CTL_TXON_Msk | EMAC_CTL_RMIIEN_Msk;
    EMAC->INTEN |= EMAC_INTEN_RXIEN_Msk |
                   EMAC_INTEN_RXGDIEN_Msk |
                   EMAC_INTEN_RDUIEN_Msk |
                   EMAC_INTEN_RXBEIEN_Msk |
                   EMAC_INTEN_TXIEN_Msk |
                   EMAC_INTEN_TXABTIEN_Msk |
                   EMAC_INTEN_TXCPIEN_Msk |
                   EMAC_INTEN_TXBEIEN_Msk;
    /* Limit the max receive frame length to 1514 + 4 */
    EMAC->MRFL = 1518;
    EMAC->RXST = 0;  // trigger Rx
}

void EMAC_halt(void)
{
    // clear tx/rx on
    EMAC->CTL &= ~(EMAC_CTL_RXON_Msk | EMAC_CTL_TXON_Msk);
}


unsigned int link_state_changed(void)
{
    unsigned int reg, ret = 0;

    reg = mdio_read(CONFIG_PHY_ADDR, MII_BMSR);

    if (reg & BMSR_LSTATUS)
    {
        if (!plugged)
        {
            ret = 1;
            plugged = 1;
            reset_phy();
            EMAC->CTL |= EMAC_CTL_RXON_Msk | EMAC_CTL_TXON_Msk;
        }
    }
    else
    {
        if (plugged)
        {
            plugged = 0;
            ret = 1;
            EMAC->CTL &= ~(EMAC_CTL_RXON_Msk | EMAC_CTL_TXON_Msk);
        }
    }
    return ret;
}

unsigned int link_is_up(void)
{
    return plugged == 1 ? 1 : 0;

}

u8_t *EMAC_get_tx_buf(void)
{
    if(cur_tx_desc_ptr->status1 & OWNERSHIP_EMAC)
        return(NULL);
    else
        return(cur_tx_desc_ptr->buf);
}

void EMAC_trigger_tx(u16_t length)
{
    struct eth_descriptor volatile *desc;
    cur_tx_desc_ptr->status2 = (unsigned int)length;
    desc = cur_tx_desc_ptr->next;    // in case TX is transmitting and overwrite next pointer before we can update cur_tx_desc_ptr
    cur_tx_desc_ptr->status1 |= OWNERSHIP_EMAC;
    cur_tx_desc_ptr = desc;

    TRIGGER_TX();
}


