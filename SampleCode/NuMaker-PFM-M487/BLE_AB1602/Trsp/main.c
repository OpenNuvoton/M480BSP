/*************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    A BLE to UART sample.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

/*************************airoha**************************/
#include "bt_porting.h"
#include "bt.h"
#include "ble_gap.h"
#include "cfg_sector_m0.h"
#include "trspx.h"

#define PLL_CLOCK           192000000
#define UART_TX_PDMA_CH     2
//#define ENABLE_RTS_CTS

// Move definition to project setting
//#define UART_RX_USE_PDMA

#if defined(UART_RX_USE_PDMA)
#define UART_RX_PDMA_CH     1
void UART1_RX_Recv(void);

#else
/*uart rx buffer control*/
#define RX_BUF_RESET()      (rx_buf_ridx = rx_buf_widx = 0)
#define RX_BUF_PUSH(d)      (rx_buf[(uint8_t)(rx_buf_widx++)] = (d))
#define RX_BUF_POP()        (rx_buf[(rx_buf_ridx++)])
#define RX_BUF_DROP(d)      (rx_buf_ridx += d)
#define RX_BUF_READ(idx)    (rx_buf[(uint8_t)(rx_buf_ridx+idx)])
#define RX_BUF_EMPTY()      ((rx_buf_ridx) == (rx_buf_widx))
#define RX_BUF_FULL()       ((rx_buf_ridx) == ((uint8_t)(rx_buf_widx + 1)))
#define RX_BUF_COUNT()      ((uint8_t)(rx_buf_widx - rx_buf_ridx))

/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
static uint8_t rx_buf[256];
static uint8_t rx_buf_ridx, rx_buf_widx;

#endif

/*---------------------------------------------------------------------------------------------------------*/
/* Define functions prototype                                                                              */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void);
int cmd_urx(void *context, int argc, char** argv);
int cmd_utx(void *context, int argc, char** argv);
// use UART1 interface, keep UART1_TX_Send for the unique naming
void UART1_TX_Send(uint32_t len, uint8_t *ptr);
void UART1_IRQHandler(void);

/*---------------------------------------------------------------------------------------------------------*/
/* static function                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/
/* 1000 bytes pending to stop UART1 rx, then 500 bytes will allow again*/
static uint8_t RFTX_Pending_Check()
{
    static volatile uint8_t rf_pending = 0;
    if(rf_pending)
    {
        if(BT_Pending_TxCnt() < 500)
        {
            rf_pending = 0;
            NVIC_EnableIRQ(UART1_IRQn);
        }
    }
    else if(BT_Pending_TxCnt() > 1000)
    {
        NVIC_DisableIRQ(UART1_IRQn);
        rf_pending = 1;
    }
    return rf_pending;
}

void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Enable HXT */
    CLK->PWRCTL |= CLK_PWRCTL_HXTEN_Msk; // XTAL12M (HXT) Enabled

    /* Waiting clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);
    CLK->PCLKDIV = (CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2); // PCLK divider set 2

    /* Enable IP clock */
    CLK->APBCLK0 |= CLK_APBCLK0_UART0CKEN_Msk; // UART0 Clock Enable
    CLK->APBCLK0 |= CLK_APBCLK0_UART1CKEN_Msk; // UART1 Clock Enable

    /* Select IP clock source */
    /* Select UART0 clock source is HXT */
    CLK->CLKSEL1 = (CLK->CLKSEL1 & ~CLK_CLKSEL1_UART0SEL_Msk) | (0x0 << CLK_CLKSEL1_UART0SEL_Pos);
    /* Select UART1 clock source is HXT */
    CLK->CLKSEL1 = (CLK->CLKSEL1 & ~CLK_CLKSEL1_UART1SEL_Msk) | (0x0 << CLK_CLKSEL1_UART1SEL_Pos);

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set PB multi-function pins for UART1 RXD, TXD */
    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB3MFP_Msk | SYS_GPB_MFPL_PB2MFP_Msk);
    SYS->GPB_MFPL |= (SYS_GPB_MFPL_PB3MFP_UART1_TXD | SYS_GPB_MFPL_PB2MFP_UART1_RXD);
#if defined(ENABLE_RTS_CTS)
    /* Set PE multi-function pins for UART1 RTS, CTS */
    SYS->GPE_MFPH &= ~(SYS_GPE_MFPH_PE11MFP_Msk | SYS_GPE_MFPH_PE12MFP_Msk);
    SYS->GPE_MFPH |= (SYS_GPE_MFPH_PE11MFP_UART1_nCTS | SYS_GPE_MFPH_PE12MFP_UART1_nRTS);
#endif
}

void UART0_Init()
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset UART0 module */
//    SYS_ResetModule(UART0_RST);
    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0, 115200);
    /* Set RX Trigger Level = 8 */
    UART0->FIFO = (UART0->FIFO &~ UART_FIFO_RFITL_Msk) | UART_FIFO_RFITL_8BYTES;
    UART0->FIFO |= UART_FIFO_RTSTRGLV_8BYTES;
    /* Set Timeout time 0x3E bit-time */
    UART_SetTimeoutCnt(UART0, 0x3E);
    /* enable uart */
    UART_EnableInt(UART0, (UART_INTEN_RDAIEN_Msk /*| UART_INTEN_THREIEN_Msk*/ |
                           UART_INTEN_RXTOIEN_Msk) | UART_INTEN_TOCNTEN_Msk);
    NVIC_EnableIRQ(UART0_IRQn);
}

void UART1_Init()
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset UART1 module */
//    SYS_ResetModule(UART1_RST);
    /* Configure UART1 and set UART1 Baudrate */
    UART_Open(UART1, 115200);
#if defined(ENABLE_RTS_CTS)
    /* enable flow control */
    //UART_EnableFlowCtrl(UART1);
#endif
#if defined(UART_RX_USE_PDMA)
    PDMA->CHCTL |= (1 << UART_RX_PDMA_CH);
    PDMA_EnableInt(PDMA, UART_RX_PDMA_CH, PDMA_INT_TRANS_DONE);
    /*enable uart*/
    UART1_RX_Recv();
#else
    /* Set RX Trigger Level = 8 */
    UART1->FIFO = (UART1->FIFO &~ UART_FIFO_RFITL_Msk) | UART_FIFO_RFITL_8BYTES;
#if defined(ENABLE_RTS_CTS)
    UART1->FIFO |= UART_FIFO_RTSTRGLV_8BYTES;
#endif
    /* Set Timeout time 0x3E bit-time */
    UART_SetTimeoutCnt(UART1, 0x3E);
    /* enable uart */
    UART_EnableInt(UART1, (UART_INTEN_RDAIEN_Msk /*| UART_INTEN_THREIEN_Msk*/ |
                           UART_INTEN_RXTOIEN_Msk) | UART_INTEN_TOCNTEN_Msk);
#endif
    NVIC_EnableIRQ(UART1_IRQn);
}


void UART1_TX_Send(uint32_t len, uint8_t *ptr)
{
    if(PDMA_IS_CH_BUSY(PDMA, UART_TX_PDMA_CH))
    {
        /*need to maintain queueing to resist the CTS flow stop!!!!*/
        printf("drop data\n");
        return; //drop data;
    }
    PDMA->CHCTL |= (1 << UART_TX_PDMA_CH);
    /* UART Tx PDMA channel configuration */
    /* Set transfer width (8 bits) and transfer count */
    PDMA_SetTransferCnt(PDMA, UART_TX_PDMA_CH, PDMA_WIDTH_8, len);
    /* Set source/destination address and attributes */
    PDMA_SetTransferAddr(PDMA, UART_TX_PDMA_CH, (uint32_t)ptr, PDMA_SAR_INC,
                         (uint32_t)&UART1->DAT, PDMA_DAR_FIX);
    /* Set service selection; set Memory-to-Peripheral mode. */
    PDMA_SetTransferMode(PDMA, UART_TX_PDMA_CH, PDMA_UART1_TX, FALSE, 0);
    /* Trigger PDMA */
    UART1->INTEN |= UART_INTEN_TXPDMAEN_Msk;
}


/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/

int main(void)
{
    const void *btdata[6] = {NULL/*mp_data*/, &cfg_sector};
    /* Unlock protected registers */
    SYS_UnlockReg();
    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();
    /*airoha porting init*/
    Airoha_PortingInit();
    /* Lock protected registers */
    SYS_LockReg();
    /*for debug*/
    GPIO_SetMode(PB, BIT13, GPIO_MODE_OUTPUT);
    PB13 = 0;
    /* Bt Init*/
    BT_InitEx2(TRSPX_bt_evt_hdl, (void**)btdata, 2, BT_LOG_HCI_CMD | BT_LOG_HCI_EVT);
    printf("\n\nCPU @ %dHz\n", SystemCoreClock);
    /* Init UART0 for printf and testing */
    UART0_Init();
    /* Init UART1 for BLE to UART */
    UART1_Init();
#if defined(UART_RX_USE_PDMA)
    printf("UART RX uses PDMA\n");
#else
    RX_BUF_RESET();
#endif
    TRSPX_init();
    while(1)
    {
        RFTX_Pending_Check();
    }
}

/*---------------------------------------------------------------------------------------------------------*/
/* ISR to handle UART Channel 0 interrupt event                                                            */
/*---------------------------------------------------------------------------------------------------------*/
void UART0_IRQHandler(void)
{
    uint32_t u32IntSts = UART0->INTSTS;
    if(u32IntSts & UART_INTSTS_RDAINT_Msk)
    {
        /* Get all the input characters */
        while(!UART_GET_RX_EMPTY(UART0))
        {
            /* Get the character from UART Buffer */
            UART_READ(UART0);
        }
    }
    if(u32IntSts & UART_INTSTS_RXTOIF_Msk)
    {
        /* Get all the input characters */
        while(!UART_GET_RX_EMPTY(UART0))
        {
            /* Get the character from UART Buffer */
            UART_READ(UART0);
        }
    }
    if(u32IntSts & UART_INTSTS_THREINT_Msk)
    {
    }
}


#if defined(UART_RX_USE_PDMA)
void UART1_RX_Recv(void)
{
    /* UART Rx PDMA channel configuration */
    /* Set transfer width (8 bits) and transfer count */
    PDMA_SetTransferCnt(PDMA, UART_RX_PDMA_CH, PDMA_WIDTH_8, TRSPX_mtu);
    /* Set source/destination address and attributes */
    PDMA_SetTransferAddr(PDMA, UART_RX_PDMA_CH, (uint32_t)&UART1->DAT, PDMA_SAR_FIX,
                         (uint32_t)TRSPX_Read_Data, PDMA_DAR_INC);
    /* Set service selection; set Memory-to-Peripheral mode. */
    PDMA_SetTransferMode(PDMA, UART_RX_PDMA_CH, PDMA_UART1_RX, FALSE, 0);
    /* Single request type */
    PDMA_SetBurstType(PDMA, UART_RX_PDMA_CH, PDMA_REQ_SINGLE, 0);
    /* Disable table interrupt */
    PDMA->DSCT[UART_RX_PDMA_CH].CTL |= PDMA_DSCT_CTL_TBINTDIS_Msk;

    /* Set PDMA CH 1 timeout to about 2 ms (5/(72M/(2^15))) */
    PDMA->TOUTPSC = (PDMA->TOUTPSC & (~PDMA_TOUTPSC_TOUTPSC1_Msk)) | (0x7 << PDMA_TOUTPSC_TOUTPSC1_Pos);
    PDMA->TOC0_1 = (PDMA->TOC0_1 & (~PDMA_TOC0_1_TOC1_Msk)) | (0x5 << PDMA_TOC0_1_TOC1_Pos);
    /* Enable PDMA timeout for UART RX*/
    PDMA->TOUTEN |= (1 << UART_RX_PDMA_CH);
    PDMA->TOUTIEN |= (1 << UART_RX_PDMA_CH);

    /* Trigger PDMA */
    UART1->INTEN |= UART_INTEN_RXPDMAEN_Msk;
}

#else
void UART1_IRQHandler(void)
{
    uint8_t tout = 0;
    uint32_t u32IntSts = UART1->INTSTS;
    /*Check if RF pending too much*/
    if(RFTX_Pending_Check())
        return;
    if(u32IntSts & (UART_INTSTS_HWTOIF_Msk|UART_INTSTS_RXTOIF_Msk))
        tout = 1;
    while(!UART_GET_RX_EMPTY(UART1))
    {
        uint8_t dat;
        if(RX_BUF_FULL())
            break;
        dat = UART_READ(UART1);
        RX_BUF_PUSH(dat);
    }
    if(RX_BUF_COUNT() >= TRSPX_mtu)
    {
        uint8_t i;
        for(i = 0; i < TRSPX_mtu; i++)
            TRSPX_Read_Data[i] = RX_BUF_POP();
        //printf("%d\n", TRSPX_mtu);
        TRSPX_send(TRSPX_mtu);
    }
    else if(tout)
    {
        uint8_t cnt, i;
        cnt = RX_BUF_COUNT();
        for(i = 0; i < cnt; i++)
            TRSPX_Read_Data[i] = RX_BUF_POP();
        //printf("%d\n", cnt);
        TRSPX_send(cnt);
    }
}
#endif
