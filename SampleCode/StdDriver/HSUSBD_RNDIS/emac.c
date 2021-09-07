/**************************************************************************//**
 * @file     emac.c
 * @version  V1.00
 * @brief    M480 EMAC driver source file
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

extern uint8_t rndis_indata[EMAC_RX_DESC_SIZE + 1][1580];
extern uint32_t u32CurrentRxBuf;


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup EMAC_Driver EMAC Driver
  @{
*/


/* Below are structure, definitions, static variables used locally by EMAC driver and does not want to parse by doxygen unless HIDDEN_SYMBOLS is defined */
/** @cond HIDDEN_SYMBOLS */

/** @addtogroup EMAC_EXPORTED_CONSTANTS EMAC Exported Constants
  @{
*/

/* PHY Register Description */
#define PHY_CNTL_REG    0x00UL        /*!<  PHY control register address */
#define PHY_STATUS_REG  0x01UL        /*!<  PHY status register address */
#define PHY_ID1_REG     0x02UL        /*!<  PHY ID1 register */
#define PHY_ID2_REG     0x03UL        /*!<  PHY ID2 register */
#define PHY_ANA_REG     0x04UL        /*!<  PHY auto-negotiation advertisement register */
#define PHY_ANLPA_REG   0x05UL        /*!<  PHY auto-negotiation link partner availability register */
#define PHY_ANE_REG     0x06UL        /*!<  PHY auto-negotiation expansion register */

/* PHY Control Register */
#define PHY_CNTL_RESET_PHY      (1UL << 15UL)
#define PHY_CNTL_DR_100MB       (1UL << 13UL)
#define PHY_CNTL_ENABLE_AN      (1UL << 12UL)
#define PHY_CNTL_POWER_DOWN     (1UL << 11UL)
#define PHY_CNTL_RESTART_AN     (1UL << 9UL)
#define PHY_CNTL_FULLDUPLEX     (1UL << 8UL)

/* PHY Status Register */
#define PHY_STATUS_AN_COMPLETE   (1UL << 5UL)
#define PHY_STATUS_LINK_VALID    (1UL << 2UL)

/* PHY Auto-negotiation Advertisement Register */
#define PHY_ANA_DR100_TX_FULL   (1UL << 8UL)
#define PHY_ANA_DR100_TX_HALF   (1UL << 7UL)
#define PHY_ANA_DR10_TX_FULL    (1UL << 6UL)
#define PHY_ANA_DR10_TX_HALF    (1UL << 5UL)
#define PHY_ANA_IEEE_802_3_CSMA_CD   (1UL << 0UL)

/* PHY Auto-negotiation Link Partner Advertisement Register */
#define PHY_ANLPA_DR100_TX_FULL   (1UL << 8UL)
#define PHY_ANLPA_DR100_TX_HALF   (1UL << 7UL)
#define PHY_ANLPA_DR10_TX_FULL    (1UL << 6UL)
#define PHY_ANLPA_DR10_TX_HALF    (1UL << 5UL)

/* EMAC Tx/Rx descriptor's owner bit */
#define EMAC_DESC_OWN_EMAC 0x80000000UL  /*!<  Set owner to EMAC */
#define EMAC_DESC_OWN_CPU  0x00000000UL  /*!<  Set owner to CPU */

/* Rx Frame Descriptor Status */
#define EMAC_RXFD_RTSAS   0x0080UL  /*!<  Time Stamp Available */
#define EMAC_RXFD_RP      0x0040UL  /*!<  Runt Packet */
#define EMAC_RXFD_ALIE    0x0020UL  /*!<  Alignment Error */
#define EMAC_RXFD_RXGD    0x0010UL  /*!<  Receiving Good packet received */
#define EMAC_RXFD_PTLE    0x0008UL  /*!<  Packet Too Long Error */
#define EMAC_RXFD_CRCE    0x0002UL  /*!<  CRC Error */
#define EMAC_RXFD_RXINTR  0x0001UL  /*!<  Interrupt on receive */

/* Tx Frame Descriptor's Control bits */
#define EMAC_TXFD_TTSEN     0x08UL      /*!<  Tx time stamp enable */
#define EMAC_TXFD_INTEN     0x04UL      /*!<  Tx interrupt enable */
#define EMAC_TXFD_CRCAPP    0x02UL      /*!<  Append CRC */
#define EMAC_TXFD_PADEN     0x01UL      /*!<  Padding mode enable */

/* Tx Frame Descriptor Status */
#define EMAC_TXFD_TXINTR 0x0001UL  /*!<  Interrupt on Transmit */
#define EMAC_TXFD_DEF    0x0002UL  /*!<  Transmit deferred  */
#define EMAC_TXFD_TXCP   0x0008UL  /*!<  Transmission Completion  */
#define EMAC_TXFD_EXDEF  0x0010UL  /*!<  Exceed Deferral */
#define EMAC_TXFD_NCS    0x0020UL  /*!<  No Carrier Sense Error */
#define EMAC_TXFD_TXABT  0x0040UL  /*!<  Transmission Abort  */
#define EMAC_TXFD_LC     0x0080UL  /*!<  Late Collision  */
#define EMAC_TXFD_TXHA   0x0100UL  /*!<  Transmission halted */
#define EMAC_TXFD_PAU    0x0200UL  /*!<  Paused */
#define EMAC_TXFD_SQE    0x0400UL  /*!<  SQE error  */
#define EMAC_TXFD_TTSAS  0x0800UL  /*!<  Time Stamp available */

/*@}*/ /* end of group EMAC_EXPORTED_CONSTANTS */

/** @addtogroup EMAC_EXPORTED_TYPEDEF EMAC Exported Type Defines
  @{
*/

/** Tx/Rx buffer descriptor structure */
typedef struct
{
    uint32_t u32Status1;   /*!<  Status word 1 */
    uint32_t u32Data;      /*!<  Pointer to data buffer */
    uint32_t u32Status2;   /*!<  Status word 2 */
    uint32_t u32Next;      /*!<  Pointer to next descriptor */
} EMAC_DESCRIPTOR_T;

/** Tx/Rx buffer structure */
typedef struct
{
    uint8_t au8Buf[1600];
} EMAC_FRAME_T;

/*@}*/ /* end of group EMAC_EXPORTED_TYPEDEF */

/* local variables */
static volatile EMAC_DESCRIPTOR_T rx_desc[EMAC_RX_DESC_SIZE];
//static volatile EMAC_FRAME_T rx_buf[EMAC_RX_DESC_SIZE];
static volatile EMAC_DESCRIPTOR_T tx_desc[EMAC_TX_DESC_SIZE];
//static volatile EMAC_FRAME_T tx_buf[EMAC_TX_DESC_SIZE];


static uint32_t u32NextTxDesc, u32CurrentRxDesc;


static void EMAC_MdioWrite(uint32_t u32Reg, uint32_t u32Addr, uint32_t u32Data);
static uint32_t EMAC_MdioRead(uint32_t u32Reg, uint32_t u32Addr);
static void _EMAC_PhyInit(void);
static void EMAC_TxDescInit(void);
static void EMAC_RxDescInit(void);

/** @addtogroup EMAC_EXPORTED_FUNCTIONS EMAC Exported Functions
  @{
*/

/**
  * @brief  Trigger EMAC Tx function
  * @param  None
  * @return None
  */
#define EMAC_TRIGGER_TX() do{EMAC->TXST = 0UL;}while(0)


/**
  * @brief  Write PHY register
  * @param[in]  u32Reg PHY register number
  * @param[in]  u32Addr PHY address, this address is board dependent
  * @param[in] u32Data data to write to PHY register
  * @return None
  */
static void EMAC_MdioWrite(uint32_t u32Reg, uint32_t u32Addr, uint32_t u32Data)
{
    /* Set data register */
    EMAC->MIIMDAT = u32Data ;
    /* Set PHY address, PHY register address, busy bit and write bit */
    EMAC->MIIMCTL = u32Reg | (u32Addr << 8) | EMAC_MIIMCTL_BUSY_Msk | EMAC_MIIMCTL_WRITE_Msk | EMAC_MIIMCTL_MDCON_Msk;
    /* Wait write complete by polling busy bit. */
    while(EMAC->MIIMCTL & EMAC_MIIMCTL_BUSY_Msk)
    {
        ;
    }

}

/**
  * @brief  Read PHY register
  * @param[in]  u32Reg PHY register number
  * @param[in]  u32Addr PHY address, this address is board dependent
  * @return Value read from PHY register
  */
static uint32_t EMAC_MdioRead(uint32_t u32Reg, uint32_t u32Addr)
{
    /* Set PHY address, PHY register address, busy bit */
    EMAC->MIIMCTL = u32Reg | (u32Addr << EMAC_MIIMCTL_PHYADDR_Pos) | EMAC_MIIMCTL_BUSY_Msk | EMAC_MIIMCTL_MDCON_Msk;
    /* Wait read complete by polling busy bit */
    while(EMAC->MIIMCTL & EMAC_MIIMCTL_BUSY_Msk)
    {
        ;
    }
    /* Get return data */
    return EMAC->MIIMDAT;
}

/**
  * @brief  Initialize PHY chip, check for the auto-negotiation result.
  * @param  None
  * @return None
  */
static void _EMAC_PhyInit(void)
{
    uint32_t reg;
    uint32_t i = 0UL;

    /* Reset Phy Chip */
    EMAC_MdioWrite(PHY_CNTL_REG, EMAC_PHY_ADDR, PHY_CNTL_RESET_PHY);

    /* Wait until reset complete */
    while (1)
    {
        reg = EMAC_MdioRead(PHY_CNTL_REG, EMAC_PHY_ADDR) ;
        if ((reg & PHY_CNTL_RESET_PHY)==0UL)
        {
            break;
        }
    }
    while(!(EMAC_MdioRead(PHY_STATUS_REG, EMAC_PHY_ADDR) & PHY_STATUS_LINK_VALID))
    {
        if(i++ > 80000UL)       /* Cable not connected */
        {
            EMAC->CTL &= ~EMAC_CTL_OPMODE_Msk;
            EMAC->CTL &= ~EMAC_CTL_FUDUP_Msk;
            break;
        }
    }

    if(i <= 80000UL)
    {
        /* Configure auto negotiation capability */
        EMAC_MdioWrite(PHY_ANA_REG, EMAC_PHY_ADDR, PHY_ANA_DR100_TX_FULL |
                       PHY_ANA_DR100_TX_HALF |
                       PHY_ANA_DR10_TX_FULL |
                       PHY_ANA_DR10_TX_HALF |
                       PHY_ANA_IEEE_802_3_CSMA_CD);
        /* Restart auto negotiation */
        EMAC_MdioWrite(PHY_CNTL_REG, EMAC_PHY_ADDR, EMAC_MdioRead(PHY_CNTL_REG, EMAC_PHY_ADDR) | PHY_CNTL_RESTART_AN);

        /* Wait for auto-negotiation complete */
        while(!(EMAC_MdioRead(PHY_STATUS_REG, EMAC_PHY_ADDR) & PHY_STATUS_AN_COMPLETE))
        {
            ;
        }
        /* Check link valid again. Some PHYs needs to check result after link valid bit set */
        while(!(EMAC_MdioRead(PHY_STATUS_REG, EMAC_PHY_ADDR) & PHY_STATUS_LINK_VALID))
        {
            ;
        }

        /* Check link partner capability */
        reg = EMAC_MdioRead(PHY_ANLPA_REG, EMAC_PHY_ADDR) ;
        if (reg & PHY_ANLPA_DR100_TX_FULL)
        {
            EMAC->CTL |= EMAC_CTL_OPMODE_Msk;
            EMAC->CTL |= EMAC_CTL_FUDUP_Msk;
        }
        else if (reg & PHY_ANLPA_DR100_TX_HALF)
        {
            EMAC->CTL |= EMAC_CTL_OPMODE_Msk;
            EMAC->CTL &= ~EMAC_CTL_FUDUP_Msk;
        }
        else if (reg & PHY_ANLPA_DR10_TX_FULL)
        {
            EMAC->CTL &= ~EMAC_CTL_OPMODE_Msk;
            EMAC->CTL |= EMAC_CTL_FUDUP_Msk;
        }
        else
        {
            EMAC->CTL &= ~EMAC_CTL_OPMODE_Msk;
            EMAC->CTL &= ~EMAC_CTL_FUDUP_Msk;
        }
    }
}

/**
  * @brief  Initial EMAC Tx descriptors and get Tx descriptor base address
  * @param None
  * @return None
  */
static void EMAC_TxDescInit(void)
{
    uint32_t i;

    /* Get Frame descriptor's base address. */
    EMAC->TXDSA = (uint32_t)&tx_desc[0];
    u32NextTxDesc = (uint32_t)&tx_desc[0];

    for(i = 0UL; i < EMAC_TX_DESC_SIZE; i++)
    {
        tx_desc[i].u32Status1 = EMAC_TXFD_PADEN | EMAC_TXFD_CRCAPP | EMAC_TXFD_INTEN | EMAC_TXFD_TTSEN;
        //tx_desc[i].u32Data = (uint32_t)((uint32_t)&tx_buf[i]);
        tx_desc[i].u32Status2 = 0UL;
        tx_desc[i].u32Next = (uint32_t)&tx_desc[(i + 1UL) % EMAC_TX_DESC_SIZE];
    }

}


/**
  * @brief  Initial EMAC Rx descriptors and get Rx descriptor base address
  * @param None
  * @return None
  */
static void EMAC_RxDescInit(void)
{
    uint32_t i;

    /* Get Frame descriptor's base address. */
    EMAC->RXDSA = (uint32_t)&rx_desc[0];
    u32CurrentRxDesc = (uint32_t)&rx_desc[0];

    for(i = 0UL; i < EMAC_RX_DESC_SIZE; i++)
    {
        rx_desc[i].u32Status1 = EMAC_DESC_OWN_EMAC;
        rx_desc[i].u32Data = (uint32_t)(&rndis_indata[i][44]);
        rx_desc[i].u32Status2 = 0UL;
        rx_desc[i].u32Next = (uint32_t)&rx_desc[(i + 1UL) % EMAC_RX_DESC_SIZE];
    }
}

/*@}*/ /* end of group EMAC_EXPORTED_FUNCTIONS */



/** @endcond HIDDEN_SYMBOLS */


/** @addtogroup EMAC_EXPORTED_FUNCTIONS EMAC Exported Functions
  @{
*/


/**
  * @brief  Initialize EMAC interface, including descriptors, MAC address, and PHY.
  * @param[in]  pu8MacAddr  Pointer to uint8_t array holds MAC address
  * @return None
  * @note This API configures EMAC to receive all broadcast and multicast packets, but could configure to other settings with
  *       \ref EMAC_ENABLE_RECV_BCASTPKT, \ref EMAC_DISABLE_RECV_BCASTPKT, \ref EMAC_ENABLE_RECV_MCASTPKT, and \ref EMAC_DISABLE_RECV_MCASTPKT
  * @note Receive(RX) and transmit(TX) are not enabled yet, application must call \ref EMAC_ENABLE_RX and \ref EMAC_ENABLE_TX to
  *       enable receive and transmit function.
  */
void EMAC_Open(uint8_t *pu8MacAddr)
{
    /* Enable transmit and receive descriptor */
    EMAC_TxDescInit();
    EMAC_RxDescInit();

    /* Set the CAM Control register and the MAC address value */
    EMAC_SetMacAddr(pu8MacAddr);


    /* Configure the MAC control register. */
    EMAC->CTL = EMAC_CTL_STRIPCRC_Msk |
                EMAC_CTL_RMIIEN_Msk;

    /* Accept packets for us and all broadcast and multicast packets */
    EMAC->CAMCTL =  EMAC_CAMCTL_CMPEN_Msk |
                    EMAC_CAMCTL_AMP_Msk |
                    EMAC_CAMCTL_ABP_Msk;

    /* Limit the max receive frame length to 1514 + 4 */
    EMAC->MRFL = 1518;
    _EMAC_PhyInit();
}

/**
  * @brief  This function stop all receive and transmit activity and disable MAC interface
  * @param None
  * @return Disable EMAC success or not
  * @retval 0 Disable EMAC success
  * @retval -1 Disable EMAC failed because reset EMAC state machine takes longer than expected
  */

int32_t EMAC_Close(void)
{
    // It takes a few ECLK for the reset bit to be auto-cleared. Add a small counter if something goes wrong.
    uint32_t u32Delay = 10;
    EMAC->CTL |= EMAC_CTL_RST_Msk;
    while ((EMAC->CTL & EMAC_CTL_RST_Msk) && (--u32Delay))
    {
        ;
    }
    return u32Delay > 0 ? 0 : -1;
}

/**
  * @brief  Set the device MAC address
  * @param[in]  pu8MacAddr  Pointer to uint8_t array holds MAC address
  * @return None
  */
void EMAC_SetMacAddr(uint8_t *pu8MacAddr)
{
    EMAC_EnableCamEntry(0UL, pu8MacAddr);
}

/**
  * @brief Fill a CAM entry for MAC address comparison.
  * @param[in] u32Entry MAC entry to fill. Entry 0 is used to store device MAC address, do not overwrite the setting in it.
  * @param[in] pu8MacAddr  Pointer to uint8_t array holds MAC address
  * @return None
  */
void EMAC_EnableCamEntry(uint32_t u32Entry, uint8_t pu8MacAddr[])
{
    uint32_t u32Lsw, u32Msw;
    uint32_t reg;
    u32Lsw = (uint32_t)(((uint32_t)pu8MacAddr[4] << 24) |
                        ((uint32_t)pu8MacAddr[5] << 16));
    u32Msw = (uint32_t)(((uint32_t)pu8MacAddr[0] << 24)|
                        ((uint32_t)pu8MacAddr[1] << 16)|
                        ((uint32_t)pu8MacAddr[2] << 8)|
                        (uint32_t)pu8MacAddr[3]);

    reg = (uint32_t)&EMAC->CAM0M + u32Entry * 2UL * 4UL;
    *(uint32_t volatile *)reg = u32Msw;
    reg = (uint32_t)&EMAC->CAM0L + u32Entry * 2UL * 4UL;
    *(uint32_t volatile *)reg = u32Lsw;

    EMAC->CAMEN |= (1UL << u32Entry);
}

/**
  * @brief  Disable a specified CAM entry
  * @param[in]  u32Entry CAM entry to be disabled
  * @return None
  */
void EMAC_DisableCamEntry(uint32_t u32Entry)
{
    EMAC->CAMEN &= ~(1UL << u32Entry);
}


/**
  * @brief Receive an Ethernet packet
  * @param[in] pu8Data Pointer to a buffer to store received packet (4 byte CRC removed)
  * @param[in] pu32Size Received packet size (without 4 byte CRC).
  * @return Packet receive success or not
  * @retval 0 No packet available for receive
  * @retval Others Recevied packet length
  */
uint32_t My_EMAC_RecvPkt(void)
{
    EMAC_DESCRIPTOR_T *desc;
    uint32_t u32Count = 0UL, i;

    /* Get Rx Frame Descriptor */
    desc = (EMAC_DESCRIPTOR_T *)u32CurrentRxDesc;

    /* If we reach last recv Rx descriptor, leave the loop */
    if ((desc->u32Status1 & EMAC_DESC_OWN_EMAC) != EMAC_DESC_OWN_EMAC)   /* ownership=CPU */
    {
        //u32Count = 1UL;
        if(u32CurrentRxBuf == 0)
            i = EMAC_RX_DESC_SIZE;
        else
            i = u32CurrentRxBuf - 1;
        desc->u32Data = (uint32_t)(&rndis_indata[i][44]);
        u32Count = desc->u32Status1 & 0xFFFFUL;
        /* Change ownership to DMA for next use */
        desc->u32Status1 |= EMAC_DESC_OWN_EMAC;

        EMAC_TRIGGER_RX();
        u32CurrentRxDesc = desc->u32Next;
    }
    return u32Count;
}



/**
  * @brief Send an Ethernet packet
  * @param[in] pu8Data Pointer to a buffer holds the packet to transmit
  * @param[in] u32Size Packet size (without 4 byte CRC).
  * @return Packet transmit success or not
  * @retval 0 Transmit failed due to descriptor unavailable.
  * @retval 1 Packet is copied to descriptor and triggered to transmit.
  * @note Return 1 doesn't guarantee the packet will be sent and received successfully.
  */
uint32_t My_EMAC_SendPkt(uint8_t *pu8Data, uint32_t u32Size)
{
    EMAC_DESCRIPTOR_T *desc;
    uint32_t status;
    uint32_t ret = 0UL;
    /* Get Tx frame descriptor & data pointer */
    desc = (EMAC_DESCRIPTOR_T *)u32NextTxDesc;

    status = desc->u32Status1;

    /* Check descriptor ownership */
    if((status & EMAC_DESC_OWN_EMAC) != EMAC_DESC_OWN_EMAC)
    {
        //memcpy((uint8_t *)desc->u32Data, pu8Data, u32Size);
        desc->u32Data = (uint32_t)pu8Data;
        /* Set Tx descriptor transmit byte count */
        desc->u32Status2 = u32Size;

        /* Change descriptor ownership to EMAC */
        desc->u32Status1 |= EMAC_DESC_OWN_EMAC;

        /* Get next Tx descriptor */
        u32NextTxDesc = (uint32_t)(desc->u32Next);

        ret = 1UL;
        /* Trigger EMAC to send the packet */
        EMAC_TRIGGER_TX();
    }
    return(ret);
}


/**
  * @brief  Check Ethernet link status
  * @param  None
  * @return Current link status, could be one of following value.
  * - \ref EMAC_LINK_DOWN
  * - \ref EMAC_LINK_100F
  * - \ref EMAC_LINK_100H
  * - \ref EMAC_LINK_10F
  * - \ref EMAC_LINK_10H
  * @note   This API should be called regularly to sync EMAC setting with real connection status
  */
uint32_t EMAC_CheckLinkStatus(void)
{
    uint32_t reg, ret = EMAC_LINK_DOWN;

    /* Check link valid again */
    if(EMAC_MdioRead(PHY_STATUS_REG, EMAC_PHY_ADDR) & PHY_STATUS_LINK_VALID)
    {
        /* Check link partner capability */
        reg = EMAC_MdioRead(PHY_ANLPA_REG, EMAC_PHY_ADDR) ;
        if (reg & PHY_ANLPA_DR100_TX_FULL)
        {
            EMAC->CTL |= EMAC_CTL_OPMODE_Msk;
            EMAC->CTL |= EMAC_CTL_FUDUP_Msk;
            ret = EMAC_LINK_100F;
        }
        else if (reg & PHY_ANLPA_DR100_TX_HALF)
        {
            EMAC->CTL |= EMAC_CTL_OPMODE_Msk;
            EMAC->CTL &= ~EMAC_CTL_FUDUP_Msk;
            ret = EMAC_LINK_100H;
        }
        else if (reg & PHY_ANLPA_DR10_TX_FULL)
        {
            EMAC->CTL &= ~EMAC_CTL_OPMODE_Msk;
            EMAC->CTL |= EMAC_CTL_FUDUP_Msk;
            ret = EMAC_LINK_10F;
        }
        else
        {
            EMAC->CTL &= ~EMAC_CTL_OPMODE_Msk;
            EMAC->CTL &= ~EMAC_CTL_FUDUP_Msk;
            ret = EMAC_LINK_10H;
        }
    }
    return ret;
}


/*@}*/ /* end of group EMAC_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group EMAC_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2019 Nuvoton Technology Corp. ***/
