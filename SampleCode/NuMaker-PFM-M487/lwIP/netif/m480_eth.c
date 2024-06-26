/*
 * Copyright (c) 2016 Nuvoton Technology Corp.
 * Description:   M480 EMAC driver file
 */
#include "netif/m480_eth.h"
#include "arch/sys_arch.h"
#include <string.h>

#define ETH_TRIGGER_RX()    do{EMAC->RXST = 0;}while(0)
#define ETH_TRIGGER_TX()    do{EMAC->TXST = 0;}while(0)
#define ETH_ENABLE_TX()     do{EMAC->CTL |= EMAC_CTL_TXON;}while(0)
#define ETH_ENABLE_RX()     do{EMAC->CTL |= EMAC_CTL_RXON;}while(0)
#define ETH_DISABLE_TX()    do{EMAC->CTL &= ~EMAC_CTL_TXON;}while(0)
#define ETH_DISABLE_RX()    do{EMAC->CTL &= ~EMAC_CTL_RXON;}while(0)

#ifdef __ICCARM__
#pragma data_alignment=4
struct eth_descriptor rx_desc[RX_DESCRIPTOR_NUM];
struct eth_descriptor tx_desc[TX_DESCRIPTOR_NUM];
#else
struct eth_descriptor rx_desc[RX_DESCRIPTOR_NUM] __attribute__ ((aligned(4)));
struct eth_descriptor tx_desc[TX_DESCRIPTOR_NUM] __attribute__ ((aligned(4)));
#endif
struct eth_descriptor volatile *cur_tx_desc_ptr, *cur_rx_desc_ptr, *fin_tx_desc_ptr;

u8_t rx_buf[RX_DESCRIPTOR_NUM][PACKET_BUFFER_SIZE];
u8_t tx_buf[TX_DESCRIPTOR_NUM][PACKET_BUFFER_SIZE];

extern void ethernetif_input(u16_t len, u8_t *buf, u32_t s, u32_t ns);
extern void ethernetif_loopback_input(struct pbuf *p);

// PTP source clock is 84MHz (Real chip using PLL). Each tick is 11.90ns
// Assume we want to set each tick to 100ns.
// Increase register = (100 * 2^31) / (10^9) = 214.71 =~ 215 = 0xD7
// Addend register = 2^32 * tick_freq / (84MHz), where tick_freq = (2^31 / 215) MHz
// From above equation, addend register = 2^63 / (84M * 215) ~= 510707200 = 0x1E70C600

#ifdef TIME_STAMPING
#define DEFAULT_ADDNED    0x1E70C600
#define DEFAULT_INC    0xD7
#endif

extern portBASE_TYPE xInsideISR;


static void mdio_write(u8_t addr, u8_t reg, u16_t val)
{

    EMAC->MIIMDAT = val;
    EMAC->MIIMCTL = (addr << EMAC_MIIMCTL_PHYADDR_Pos) | reg | EMAC_MIIMCTL_BUSY_Msk | EMAC_MIIMCTL_WRITE_Msk | EMAC_MIIMCTL_MDCON_Msk;

    while (EMAC->MIIMCTL & EMAC_MIIMCTL_BUSY_Msk);

}


static u16_t mdio_read(u8_t addr, u8_t reg)
{
    EMAC->MIIMCTL = (addr << EMAC_MIIMCTL_PHYADDR_Pos) | reg | EMAC_MIIMCTL_BUSY_Msk | EMAC_MIIMCTL_MDCON_Msk;
    while (EMAC->MIIMCTL & EMAC_MIIMCTL_BUSY_Msk);

    return(EMAC->MIIMDAT);
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
        EMAC->CTL |= (EMAC_CTL_OPMODE_Msk | EMAC_CTL_FUDUP_Msk);
        return(-1);
    }
    else
    {
        reg = mdio_read(CONFIG_PHY_ADDR, MII_LPA);

        if(reg & ADVERTISE_100FULL)
        {
            printf("100 full\n");
            EMAC->CTL |= (EMAC_CTL_OPMODE_Msk | EMAC_CTL_FUDUP_Msk);
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


    cur_tx_desc_ptr = fin_tx_desc_ptr = &tx_desc[0];

    for(i = 0; i < TX_DESCRIPTOR_NUM; i++)
    {
        tx_desc[i].status1 = TXFD_PADEN | TXFD_CRCAPP | TXFD_INTEN;
        tx_desc[i].buf = &tx_buf[i][0];
        tx_desc[i].status2 = 0;
        tx_desc[i].next = &tx_desc[(i + 1) % TX_DESCRIPTOR_NUM];
#ifdef    TIME_STAMPING
        tx_desc[i].backup1 = (u32_t)tx_desc[i].buf;
        tx_desc[i].backup2 = (u32_t)tx_desc[i].next;
#endif
    }
    EMAC->TXDSA = (unsigned int)&tx_desc[0];
    return;
}

static void init_rx_desc(void)
{
    u32_t i;


    cur_rx_desc_ptr = &rx_desc[0];

    for(i = 0; i < RX_DESCRIPTOR_NUM; i++)
    {
        rx_desc[i].status1 = OWNERSHIP_EMAC;
        rx_desc[i].buf = &rx_buf[i][0];
        rx_desc[i].status2 = 0;
        rx_desc[i].next = &rx_desc[(i + 1) % RX_DESCRIPTOR_NUM];
#ifdef    TIME_STAMPING
        rx_desc[i].backup1 = (u32_t)rx_desc[i].buf;
        rx_desc[i].backup2 = (u32_t)rx_desc[i].next;
#endif
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

    EMAC->CAMCTL = EMAC_CAMCTL_CMPEN_Msk | EMAC_CAMCTL_AMP_Msk | EMAC_CAMCTL_ABP_Msk;
    EMAC->CAMEN = 1;    // Enable CAM entry 0

}


void ETH_init(u8_t *mac_addr)
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



void  ETH_halt(void)
{

    EMAC->CTL &= ~(EMAC_CTL_RXON_Msk | EMAC_CTL_TXON_Msk);
}

void EMAC_RX_IRQHandler(void)
{
    unsigned int status;

    xInsideISR = pdTRUE;
    status = EMAC->INTSTS & 0xFFFF;
    EMAC->INTSTS = status;
    if (status & EMAC_INTSTS_RXBEIF_Msk)
    {
        // Shouldn't goes here, unless descriptor corrupted
    }

    do
    {

        //cur_entry = EMAC->CRXDSA;

        //if ((cur_entry == (u32_t)cur_rx_desc_ptr) && (!(status & EMAC_INTSTS_RDUIF_Msk)))  // cur_entry may equal to cur_rx_desc_ptr if RDU occures
        //    break;
        status = cur_rx_desc_ptr->status1;

        if(status & OWNERSHIP_EMAC)
            break;

        if (status & RXFD_RXGD)
        {

#ifdef    TIME_STAMPING
            if(status & RXFD_RTSAS)
            {
                cur_rx_desc_ptr->buf = (uint8_t *)fin_tx_desc_ptr->backup1;
                cur_rx_desc_ptr->next = (struct eth_descriptor *)fin_tx_desc_ptr->backup2;
            }
#endif
            ethernetif_input(status & 0xFFFF, cur_rx_desc_ptr->buf, cur_rx_desc_ptr->status2, (u32_t)cur_rx_desc_ptr->next);


        }

        cur_rx_desc_ptr->status1 = OWNERSHIP_EMAC;
        cur_rx_desc_ptr = cur_rx_desc_ptr->next;

    }
    while (1);

    ETH_TRIGGER_RX();
    xInsideISR = pdFALSE;
}

void EMAC_TX_IRQHandler(void)
{
    unsigned int cur_entry, status;


    xInsideISR = pdTRUE;
    status = EMAC->INTSTS & 0xFFFF0000;
    EMAC->INTSTS = status;
#ifdef    TIME_STAMPING
    if(status & EMAC_INTSTS_TSALMIF_Msk)
    {
        // TODO: time stamp alarm. write me!!
    }
#endif
    if(status & EMAC_INTSTS_TXBEIF_Msk)
    {
        // Shouldn't goes here, unless descriptor corrupted
        return;
    }

    cur_entry = EMAC->CTXDSA;

    while (cur_entry != (u32_t)fin_tx_desc_ptr)
    {
#ifdef  TIME_STAMPING
        if(fin_tx_desc_ptr->status2 & TXFD_TTSAS)
        {
            if(fin_tx_desc_ptr->reserved1 != NULL)
            {
                ((struct pbuf *)(fin_tx_desc_ptr->reserved1))->ts_nsec = (u32_t)(fin_tx_desc_ptr->buf);
                ((struct pbuf *)(fin_tx_desc_ptr->reserved1))->ts_sec = (u32_t)(fin_tx_desc_ptr->next);
                ethernetif_loopback_input((struct pbuf *)fin_tx_desc_ptr->reserved1);
            }
            fin_tx_desc_ptr->buf = (u8_t *)fin_tx_desc_ptr->backup1;
            fin_tx_desc_ptr->next = (struct eth_descriptor *)fin_tx_desc_ptr->backup2;
        }
        else
        {
            if((struct pbuf *)fin_tx_desc_ptr->reserved1 != NULL)
                pbuf_free((struct pbuf *)fin_tx_desc_ptr->reserved1);  //need to define LWIP_ALLOW_MEM_FREE_FROM_OTHER_CONTEXT 1
        }
        fin_tx_desc_ptr->reserved1 = NULL;
#endif
        fin_tx_desc_ptr = fin_tx_desc_ptr->next;
    }
    xInsideISR = pdFALSE;
}

u8_t *ETH_get_tx_buf(void)
{
    if(cur_tx_desc_ptr->status1 & OWNERSHIP_EMAC)
        return(NULL);
    else
        return(cur_tx_desc_ptr->buf);
}

void ETH_trigger_tx(u16_t length, struct pbuf *p)
{
    struct eth_descriptor volatile *desc;
    cur_tx_desc_ptr->status2 = (unsigned int)length;
    desc = cur_tx_desc_ptr->next;    // in case TX is transmitting and overwrite next pointer before we can update cur_tx_desc_ptr
    cur_tx_desc_ptr->status1 |= OWNERSHIP_EMAC;
    cur_tx_desc_ptr = desc;
#ifdef TIME_STAMPING
    cur_tx_desc_ptr->reserved1 = (u32_t)p;
#endif
    ETH_TRIGGER_TX();

}

u32_t bufp_static_table[BUFP_STATIC_NUM] = {0};
u8_t *rx_bufp[RX_DESCRIPTOR_NUM];
void init_static_buffer(void)
{
    u16_t i;

    memset((void *)BUFP_STATIC_BASE, 0, (size_t)((BUFP_STATIC_NUM + 1) * BUFP_STATIC_SIZE));

    for(i = 0; i < BUFP_STATIC_NUM; i++)
    {
        bufp_static_table[i] = BUFP_STATIC_BASE + BUFP_STATIC_SIZE * i;
        rx_bufp[i] = (u8_t *)bufp_static_table[i];
        rx_desc[i].buf = rx_bufp[i]; // overwrite
    }

    // hard coding identifier at the end of SRAM
    *(u32_t *)BUFP_IDENTIFITER_ADDR = BUFP_IDENTIFITER;
}

extern unsigned char my_mac_addr[];
s16_t check_dma_buf_overflow(void)
{
    if(*(u32_t *)BUFP_IDENTIFITER_ADDR != BUFP_IDENTIFITER)
    {
        // do EMAC reset and wait for PHY ready
        ETH_init(my_mac_addr);

        init_static_buffer();

        return -1;
    }

    return 0;
}

#ifdef TIME_STAMPING


static u32_t subsec2nsec(u32_t subsec)
{
    // 2^31 subsec == 10^9 ns
    uint64_t i;
    i = 1000000000ll * subsec;
    i >>= 31;
    return(i);
}

static u32_t nsec2subsec(u32_t nsec)
{
    // 10^9 ns =  2^31 subsec
    uint64_t i;
    i = (1ll << 31) * nsec;
    i /= 1000000000;
    return(i);
}

s32_t ETH_settime(u32_t sec, u32_t nsec)
{
    // Disable time stamp counter before update time value
    EMAC->TSCTL = EMAC_TSCTL_TSEN_Msk;
    EMAC->UPDSEC = sec;
    EMAC->UPDSUBSEC = nsec2subsec(nsec);
    EMAC->TSCTL |= (EMAC_TSCTL_TSMODE_Msk | EMAC_TSCTL_TSIEN_Msk);

    return ERR_OK;
}

s32_t ETH_gettime(u32_t *sec, u32_t *nsec)
{

    // Must read TSLSR firstly. Hardware will preserve TSMSR value at the time TSLSR read.
    *nsec = subsec2nsec(EMAC->TSSUBSEC);
    *sec = EMAC->TSSEC;

    return ERR_OK;
}

s32_t ETH_updatetime(u32_t neg, u32_t sec, u32_t nsec)
{

    EMAC->UPDSEC = sec;
    EMAC->UPDSUBSEC = nsec2subsec(nsec);
    if(neg)
        EMAC->UPDSUBSEC |= BIT31;   // Set bit 31 indicates this is a negative value

    EMAC->TSCTL |= EMAC_TSCTL_TSUPDATE_Msk;
    return ERR_OK;

}

s32_t ETH_adjtimex(int ppb)
{
    int64_t addend = EMAC->TSADDEND;


    addend = (ppb * DEFAULT_ADDNED) / 1000000000 + DEFAULT_ADDNED;
    if(addend > 0xFFFFFFFF)
        addend = 0xFFFFFFFF;

    EMAC->TSADDEND = addend;

    return ERR_OK;
}

void ETH_setinc(void)
{
    EMAC->TSINC = DEFAULT_INC;
}

#endif
