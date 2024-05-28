#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include "M480.h"
#include "ab_queue.h"
/******************************************************************************
 * typedef
 ******************************************************************************/
typedef struct
{
    uint16_t txlen;
    uint16_t rxlen;
    uint8_t *rxbuf;
    void(*tran_complete)(uint8_t *rxbuf, uint16_t rxlen);
    uint8_t *rxbuf_orig;
    uint16_t rxlen_orig;
    uint8_t is_rxbuf_self_create:1;
    uint8_t is_half_duplex : 1;
    uint8_t __attribute__ ((aligned(4)))
    txbuf[1];   //because nuvoton's PDMA can't allow non 4 aligned address
} spi_tran_entry;

#define DMA_Master_TX 3
#define DMA_Master_RX 4

#if defined(UART_RX_USE_PDMA)
#define UART_RX_PDMA_CH    1
void TRSPX_send(uint16_t len);
void UART1_RX_Recv(void);
extern uint32_t TRSPX_mtu;
#endif

/******************************************************************************
 * Variable
 ******************************************************************************/
static void *tran_queue = NULL;
static void (*bt_data_rdy)(void) = NULL;
static uint8_t spi_busy = false;
/******************************************************************************
 * Prototype
 ******************************************************************************/
static void free_spi_tran_entry(spi_tran_entry* entry);

/******************************************************************************
 * Private Functions
 ******************************************************************************/
static void free_spi_tran_entry(spi_tran_entry* entry)
{
    if(entry->is_rxbuf_self_create)
    {
        free(entry->rxbuf);
    }
    AB_queue_entry_free(entry);
}

static spi_tran_entry *alloc_spi_tran_entry(uint8_t *txbuf, uint16_t txlen,
        uint8_t *rxbuf, uint16_t rxlen,
        uint8_t is_half_duplex, void(*tran_complete)(uint8_t *, uint16_t))
{
    spi_tran_entry *entry;
    /*if user didn't provide rx buf, we need to create one*/
    if(is_half_duplex)
        entry = AB_queue_entry_alloc(sizeof(spi_tran_entry) + (txlen + rxlen) - 1);
    else
        entry = AB_queue_entry_alloc(sizeof(spi_tran_entry) + txlen - 1);

    if(!entry)
        return NULL;

    entry->is_half_duplex = is_half_duplex;

    if(is_half_duplex)
    {
        if(rxlen)
        {
            entry->rxbuf_orig = rxbuf;
            entry->rxlen_orig = rxlen;
            rxbuf = malloc(rxlen + txlen);
            entry->is_rxbuf_self_create = true;
        }
        else
        {
            entry->rxbuf_orig = 0;
            entry->rxlen_orig = 0;
            entry->is_rxbuf_self_create = false;
        }
    }
    else
    {
        if(rxlen && !rxbuf)
        {
            entry->rxbuf_orig = rxbuf;
            rxbuf = malloc(rxlen);
            entry->is_rxbuf_self_create = true;
        }
        else
            entry->is_rxbuf_self_create = false;
    }
    entry->tran_complete = tran_complete;
    if(is_half_duplex)
    {
        if(rxlen)
            entry->rxlen = rxlen + txlen;
        else
            entry->rxlen = 0;

        entry->txlen = txlen + rxlen;
        memcpy(entry->txbuf, txbuf, txlen+rxlen/*for test*/);
    }
    else
    {
        entry->rxlen = rxlen;
        entry->txlen = txlen;
        memcpy(entry->txbuf, txbuf, txlen);
    }
    entry->rxbuf = rxbuf;
    return entry;
}

void GPA_IRQHandler(void)
{
    if(GPIO_GET_INT_FLAG(PA, BIT4))
    {
        GPIO_CLR_INT_FLAG(PA, BIT4);
        if(bt_data_rdy)
            bt_data_rdy();
    }
}

void SPITransactionStart(spi_tran_entry *entry)
{
    if(((uint32_t)entry->txbuf & 0x3) || ((uint32_t)entry->rxbuf & 0x3))
        printf("spi (%d, %d) = (%x, %x)\n", entry->txlen, entry->rxlen, (uint32_t)entry->txbuf, (uint32_t)entry->rxbuf);

    spi_busy = true;
    /* Disable SPI DMA function */
    SPI_DISABLE_RX_PDMA(SPI0);
    SPI_DISABLE_TX_PDMA(SPI0);
    if(entry->rxlen)
    {
        SPI0->PDMACTL |= SPI_PDMACTL_PDMARST_Msk;
        while((SPI0->STATUS & (SPI_STATUS_RXEMPTY_Msk | SPI_STATUS_RXFULL_Msk)) != SPI_STATUS_RXEMPTY_Msk)
            SPI0->FIFOCTL |= SPI_FIFOCTL_RXFBCLR_Msk;

        /* Set source/destination address and attributes */
        PDMA_SetTransferAddr(PDMA, DMA_Master_RX, (uint32_t)&SPI0->RX, PDMA_SAR_FIX,
                             (uint32_t)entry->rxbuf, PDMA_DAR_INC);

        PDMA_SetTransferAddr(PDMA, DMA_Master_TX, (uint32_t)entry->txbuf, PDMA_SAR_INC,
                             (uint32_t)&SPI0->TX, PDMA_DAR_FIX);
        /* Set transfer width (8 bits) and transfer count */
        PDMA_SetTransferCnt(PDMA, DMA_Master_TX, PDMA_WIDTH_8, entry->txlen);
        PDMA_SetTransferCnt(PDMA, DMA_Master_RX, PDMA_WIDTH_8, entry->rxlen);
    }
    else //tx only
    {
        while((SPI0->STATUS & (SPI_STATUS_RXEMPTY_Msk | SPI_STATUS_RXFULL_Msk)) != SPI_STATUS_RXEMPTY_Msk)
            SPI0->FIFOCTL |= SPI_FIFOCTL_RXFBCLR_Msk;

        PDMA_SetTransferAddr(PDMA, DMA_Master_RX, (uint32_t)&SPI0->RX, PDMA_SAR_FIX,
                             (uint32_t)entry->txbuf, PDMA_DAR_INC);

        PDMA_SetTransferAddr(PDMA, DMA_Master_TX, (uint32_t)entry->txbuf, PDMA_SAR_INC,
                             (uint32_t)&SPI0->TX, PDMA_DAR_FIX);
        PDMA_SetTransferCnt(PDMA, DMA_Master_TX, PDMA_WIDTH_8, entry->txlen);
        PDMA_SetTransferCnt(PDMA, DMA_Master_RX, PDMA_WIDTH_8, entry->txlen);
    }
    /* Set request source; set basic mode. */
    PDMA_SetTransferMode(PDMA, DMA_Master_RX, PDMA_SPI0_RX, FALSE, 0);
    PDMA_SetTransferMode(PDMA, DMA_Master_TX, PDMA_SPI0_TX, FALSE, 0);
    /* Single request type. SPI only support PDMA single request type. */
    PDMA_SetBurstType(PDMA, DMA_Master_RX, PDMA_REQ_SINGLE, 0);
    PDMA_SetBurstType(PDMA, DMA_Master_TX, PDMA_REQ_SINGLE, 0);
    /* Disable table interrupt */
    PDMA->DSCT[DMA_Master_RX].CTL |= PDMA_DSCT_CTL_TBINTDIS_Msk;
    PDMA->DSCT[DMA_Master_TX].CTL |= PDMA_DSCT_CTL_TBINTDIS_Msk;

    /* Enable SPI DMA function */
    SPI_TRIGGER_RX_PDMA(SPI0);
    SPI_TRIGGER_TX_PDMA(SPI0);
}

static void HandlerSPIComplete(spi_tran_entry *entry)
{
    spi_tran_entry *new_entry;

    spi_busy = false;

    //check for new transaction
    new_entry = AB_queue_pop(tran_queue);
    if(new_entry)
    {
        SPITransactionStart(new_entry);
    }

    //info save complete
    if(entry->tran_complete)
    {
        if(entry->is_half_duplex)
        {
            if(entry->rxbuf_orig)
            {
                memcpy(entry->rxbuf_orig, &entry->rxbuf[entry->rxlen - entry->rxlen_orig],
                       entry->rxlen_orig);
                entry->tran_complete(entry->rxbuf_orig, entry->rxlen_orig);
            }
            else
                entry->tran_complete(&entry->rxbuf[entry->rxlen - entry->rxlen_orig],
                                     entry->rxlen_orig);
        }
        else
            entry->tran_complete(entry->rxbuf, entry->rxlen);
    }
    //free save entry
    free_spi_tran_entry(entry);

}

void PDMA_IRQHandler (void)
{
    spi_tran_entry *entry;
    uint32_t status = PDMA_GET_INT_STATUS(PDMA);
    uint32_t pdma_tout = 0;

#if defined(UART_RX_USE_PDMA)
    if(status & (1 << (PDMA_INTSTS_REQTOF0_Pos + UART_RX_PDMA_CH))) /* Request Time-out */
    {
        /* Clear PDMA timeout interrupt flag */
        PDMA_CLR_TMOUT_FLAG(PDMA, UART_RX_PDMA_CH);
        /* Disable and enable timeout function to restart the timeout counter */
        PDMA->TOUTEN &= ~(1 << UART_RX_PDMA_CH);
        PDMA->TOUTEN |= (1 << UART_RX_PDMA_CH);

        uint8_t cnt;
        cnt = TRSPX_mtu - 1 - ((PDMA->DSCT[UART_RX_PDMA_CH].CTL & PDMA_DSCT_CTL_TXCNT_Msk) >> PDMA_DSCT_CTL_TXCNT_Pos);
        TRSPX_send(cnt);

        /* Set transfer count and trigger again */
        PDMA_SetTransferCnt(PDMA, UART_RX_PDMA_CH, PDMA_WIDTH_8, TRSPX_mtu);
        pdma_tout = 1;
        /* Get the latest status for SPI PDMA again */
        status = PDMA_GET_INT_STATUS(PDMA);
    }
#endif

    entry = (spi_tran_entry*) (PDMA->DSCT[DMA_Master_TX].SA - offsetof(spi_tran_entry, txbuf));
    if(status & PDMA_INTSTS_ABTIF_Msk)  /* Target Abort */
    {
        PDMA->ABTSTS = PDMA->ABTSTS;
    }
    else if(status & PDMA_INTSTS_TDIF_Msk) /* Transfer Done */
    {
        /* Tx PDMA transfer done interrupt flag */
        if(PDMA_GET_TD_STS(PDMA) & (1 << DMA_Master_TX))
        {
            /* Clear PDMA transfer done interrupt flag */
            PDMA_CLR_TD_FLAG(PDMA, (1 << DMA_Master_TX));

            /*
            if(!entry->rxlen) //TX only
            {
                SPI0->STATUS |= SPI_STATUS_RX_OVERRUN_Msk;
                SPI0->FIFO_CTL |= SPI_FIFO_CTL_RX_CLR_Msk;
                HandlerSPIComplete(entry);
            }*/
        }

        /* Rx PDMA transfer done interrupt flag */
        if(PDMA_GET_TD_STS(PDMA) & (1 << DMA_Master_RX))
        {
            /* Clear PDMA transfer done interrupt flag */
            PDMA_CLR_TD_FLAG(PDMA, (1 << DMA_Master_RX));

            //PDMA_STOP(DMA_Master_RX);

            /* Handle PDMA transfer done interrupt event */
            //if(entry->rxlen) //TX/RX both
            {
                HandlerSPIComplete(entry);
            }
        }

#if defined(UART_RX_USE_PDMA)
        /* UART Rx PDMA transfer done interrupt flag */
        if(PDMA_GET_TD_STS(PDMA) & (1 << UART_RX_PDMA_CH))
        {
            /* Clear PDMA transfer done interrupt flag */
            PDMA_CLR_TD_FLAG(PDMA, (1 << UART_RX_PDMA_CH));

            TRSPX_send(TRSPX_mtu);

            /* Set UART RX PAMA again */
            UART1_RX_Recv();
        }
#endif
    }
    else if (pdma_tout == 0)
    {
        printf("unknown interrupt, status=0x%x !!\n", status);
    }
}

bool AB_SPI_Open(int foo, void *deadbeef)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init SPI                                                                                                */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Configure SPI0 as a master, SPI clock rate 2MHz,
       clock idle low, 8-bit transaction, drive output on falling clock edge and latch input on rising edge. */
    SPI_Open(SPI0, SPI_MASTER, SPI_MODE_0, 8, 1000000);
    /* Enable the automatic hardware slave selection function. Select the SPI0_SS pin and configure as low-active. */
    SPI_EnableAutoSS(SPI0, SPI_SS, SPI_SS_ACTIVE_LOW);
    /* Set TX FIFO threshold, enable TX FIFO threshold interrupt and RX FIFO time-out interrupt */
    SPI_SetFIFO(SPI0, 2, 2);
//    SPI_EnableInt(SPI0, SPI_FIFO_TXTH_INT_MASK | SPI_FIFO_RXTO_INT_MASK);
    /* Enable PDMA channels */
    /* Set PDMA Channel 0 for SPI TX*/
    PDMA_Open(PDMA, 1 << DMA_Master_TX);
    PDMA_EnableInt(PDMA, DMA_Master_TX, PDMA_INT_TRANS_DONE);
    /* Set PDMA Channel 1 for SPI RX*/
    PDMA_Open(PDMA, 1 << DMA_Master_RX);
    PDMA_EnableInt(PDMA, DMA_Master_RX, PDMA_INT_TRANS_DONE);
    /* Set PDMA SPI0 TX & RX Selection */
    NVIC_EnableIRQ(PDMA_IRQn);
    tran_queue = AB_queue_alloc();
    return true;
}

void AB_SPI_Close(int foo)
{
    SPI_Close(SPI0);
    PDMA_DisableInt(PDMA, DMA_Master_TX, PDMA_INT_TRANS_DONE);
    PDMA_DisableInt(PDMA, DMA_Master_RX, PDMA_INT_TRANS_DONE);
}


bool AB_SPI_WriteThenRead(int spi_num, uint8_t *txbuf, uint16_t txlen, uint8_t *rxbuf, uint16_t rxlen,
                          void(*tran_complete)(uint8_t *rxbuf, uint16_t rxlen))
{
    spi_tran_entry *entry;
    entry = alloc_spi_tran_entry(txbuf, txlen, rxbuf, rxlen, 1, tran_complete);
    if(!entry)
        return false;
    if(spi_busy || SPI_GetStatus(SPI0, SPI_BUSY_MASK))
    {
        //printf("busy\n");
        AB_queue_push(tran_queue, entry);
        return false;
    }
    else
    {
        spi_busy = true;
        SPITransactionStart(entry);
    }
    return true;
}


bool AB_SPI_WriteAndRead(int spi_num, uint8_t *txbuf, uint8_t *rxbuf,
                         uint16_t rxlen, void(*tran_complete)(uint8_t *rxbuf, uint16_t rxlen))
{
    spi_tran_entry *entry;
    entry = alloc_spi_tran_entry(txbuf, rxlen, rxbuf, rxlen, 0, tran_complete);
    if(!entry)
        return false;
    if(spi_busy || SPI_GetStatus(SPI0, SPI_BUSY_MASK))
    {
        //printf("busy\n");
        AB_queue_push(tran_queue, entry);
        return false;
    }
    else
    {
        SPITransactionStart(entry);
    }
    return true;
}


/*--------------------------------------------------------------------------------------------------------------*/
/* data_ready and reset pin                                                                                     */
/*--------------------------------------------------------------------------------------------------------------*/

void Drv_1602Reset(bool is_reset)
{
    PA5 = is_reset ? 0 : 1;
}

bool Drv_1602DataReady(void)
{
    return PA4;
}

void Drv_1602DataReadyIntEn(bool is_enable)
{
    if(is_enable)
    {
        GPIO_EnableInt(PA, 4, GPIO_INT_RISING);
        NVIC_EnableIRQ(GPA_IRQn);
    }
    else
    {
        NVIC_DisableIRQ(GPA_IRQn);
        GPIO_DisableInt(PA, 4);
    }
}

void Drv_1602DataReadyIntReg(bool foo, void (*int_cb)(void))
{
    bt_data_rdy = int_cb;
    if(Drv_1602DataReady())
    {
        if(bt_data_rdy)
            bt_data_rdy();
    }
    Drv_1602DataReadyIntEn(true);
}



/******************************************************************************
 * Public Functions
 ******************************************************************************/

void Airoha1602_PinInit()
{
    /* Select PCLK as the clock source of SPI0 */
    CLK_SetModuleClock(SPI0_MODULE, CLK_CLKSEL2_SPI0SEL_PCLK1, MODULE_NoMsk);
    /* Enable SPI0 peripheral clock */
    CLK_EnableModuleClock(SPI0_MODULE);
    /* Enable PDMA clock source */
    CLK_EnableModuleClock(PDMA_MODULE);
    /* Configure SPI0 related multi-function pins. GPA[4:0] : SPI0_MOSI0, SPI0_MISO0, SPI0_CLK, SPI0_SS. */
    SYS->GPA_MFPL &= (~(SYS_GPA_MFPL_PA0MFP_Msk | SYS_GPA_MFPL_PA1MFP_Msk |
                        SYS_GPA_MFPL_PA2MFP_Msk | SYS_GPA_MFPL_PA3MFP_Msk));
    SYS->GPA_MFPL |= (SYS_GPA_MFPL_PA0MFP_SPI0_MOSI | SYS_GPA_MFPL_PA1MFP_SPI0_MISO |
                      SYS_GPA_MFPL_PA2MFP_SPI0_CLK | SYS_GPA_MFPL_PA3MFP_SPI0_SS);
    /* Enable SPI0 clock pin (PA2) schmitt trigger */
    PA->SMTEN |= GPIO_SMTEN_SMTEN4_Msk;
    /*1602 reset N */
    GPIO_SetMode(PA, BIT5, GPIO_MODE_OUTPUT);
    PA5 = 0; //reset state
    /*1602 data ready*/
    /* Set PD multi-function pin for GPx_IRQn(PA.4) */
    SYS->GPA_MFPL = (SYS->GPA_MFPL & (~SYS_GPA_MFPL_PA4MFP_Msk)) | SYS_GPA_MFPL_PA4MFP_GPIO;
    GPIO_SetMode(PA, BIT4, GPIO_MODE_INPUT);
}


