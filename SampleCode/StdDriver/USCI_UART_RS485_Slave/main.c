/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief
 *           Transmit and receive data in RS485 mode.
 *           This sample code needs to work with USCI_UART_RS485_Master.
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include "stdio.h"
#include "NuMicro.h"


#define MATCH_ADDRSS1       0xC0
#define MATCH_ADDRSS2       0xA2
#define UNMATCH_ADDRSS1     0xB1
#define UNMATCH_ADDRSS2     0xD3

#define RXBUFSIZE 10

uint8_t u8Address;
uint8_t u8RecData[RXBUFSIZE]  = {0};
volatile int32_t r_pointer = 0;


/*---------------------------------------------------------------------------------------------------------*/
/* RS485 Callback function                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
void RS485_HANDLE()
{
    volatile uint32_t u32ProtSts = UUART_GET_PROT_STATUS(UUART0);
    volatile uint32_t u32BufSts = UUART_GET_BUF_STATUS(UUART0);
    volatile uint32_t u32Data;

    if(u32ProtSts & UUART_PROTSTS_RXENDIF_Msk)      /* Receive end interrupt */
    {
        /* Handle received data */
        UUART_CLR_PROT_INT_FLAG(UUART0, UUART_PROTSTS_RXENDIF_Msk);
        u32Data = UUART_READ(UUART0);
        if( u32Data & 0x100 )
            u8Address = u32Data;
        else
        {
            u8RecData[r_pointer] = u32Data;
            r_pointer++;
        }
    }
    else if( u32BufSts & UUART_BUFSTS_RXOVIF_Msk )     /* Receive buffer over-run error interrupt */
    {
        UUART_CLR_BUF_INT_FLAG(UUART0, UUART_BUFSTS_RXOVIF_Msk);
        printf("\nBuffer Error...\n");
    }
}


void USCI0_IRQHandler(void)
{
    RS485_HANDLE();
}

/*---------------------------------------------------------------------------------------------------------*/
/*  RS485 Receive Test                                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
void RS485_9bitModeSlave()
{
    uint32_t i;

    /* Set UART line configuration and control signal output inverse */
    UUART_SetLine_Config(UUART0, 0, UUART_WORD_LEN_9, UUART_PARITY_NONE, UUART_STOP_BIT_1);
    UUART0->LINECTL |= UUART_LINECTL_CTLOINV_Msk;

    /* Enable RTS auto direction function */
    UUART0->PROTCTL |= UUART_PROTCTL_RTSAUDIREN_Msk;

    printf("+-----------------------------------------------------------+\n");
    printf("|    RS485 Mode                                             |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| The function is used to test 9-bit slave mode.            |\n");
    printf("| Receive address and data byte.                            |\n");
    printf("+-----------------------------------------------------------+\n");

    /* Enable USCI receive end and receive buffer over-run error Interrupt */
    UUART_ENABLE_TRANS_INT(UUART0, UUART_INTEN_RXENDIEN_Msk);
    UUART_ENABLE_BUF_INT(UUART0, UUART_BUFCTL_RXOVIEN_Msk);
    NVIC_EnableIRQ(USCI0_IRQn);

    printf("Starting to receive RS485 Address and %d bytes data...\n", RXBUFSIZE);

    while(r_pointer < RXBUFSIZE);

    printf("\n Receive Address: 0x%x ", u8Address);
    printf("\n Receive Data:");
    for(i=0; i<10; i++)
    {
        printf(" %d,", u8RecData[i]);
    }

    /* Disable USCI interrupt */
    UUART_DISABLE_TRANS_INT(UUART0, UUART_INTEN_RXENDIEN_Msk);
    UUART_DISABLE_BUF_INT(UUART0, UUART_BUFCTL_RXOVIEN_Msk);
    NVIC_DisableIRQ(USCI0_IRQn);

    printf("\nEnd test\n");
}


/*---------------------------------------------------------------------------------------------------------*/
/*  RS485 Function Test                                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
void RS485_FunctionTest()
{
    printf("\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|      RS485 Function Test IO Setting                       |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|  ______                                            _____  |\n");
    printf("| |      |                                          |     | |\n");
    printf("| |Master|--USCI0_DAT1   <======> USCI0_DAT0      --|Slave| |\n");
    printf("| |      |--USCI0_CTL1   <======> USCI0_CTL1      --|     | |\n");
    printf("| |______|                                          |_____| |\n");
    printf("|                                                           |\n");
    printf("+-----------------------------------------------------------+\n");


    /*
        The sample code is used to test RS485 9-bit mode and needs
        two Module test board to complete the test.

        Master:
            1.Set RTS auto direction enabled and HW will control RTS pin. CTLOINV is set to '1'.
            2.Master will send four different address with 10 bytes data to test Slave.
            3.Address bytes : the parity bit should be '1'.
            4.Data bytes : the parity bit should be '0'.
            5.RTS pin is low in idle state. When master is sending, RTS pin will be pull high.

        Slave:
            1.Set RTS auto direction enabled and HW will control RTS pin. CTLOINV is set to '1'.
            2.The received byte, parity bit is '1' , is considered "ADDRESS".
            3.The received byte, parity bit is '0' , is considered "DATA".
    */

    RS485_9bitModeSlave();

}

void SYS_Init(void)
{

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT */
    CLK->PWRCTL |= CLK_PWRCTL_HXTEN_Msk; // XTAL12M (HXT) Enabled

    /* Waiting clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(192000000);
    CLK->PCLKDIV = (CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2); // PCLK divider set 2

    /* Enable UART module clock */
    CLK->APBCLK0 |= CLK_APBCLK0_UART0CKEN_Msk;

    /* Enable USCI module clock */
    CLK->APBCLK1 |= CLK_APBCLK1_USCI0CKEN_Msk|CLK_APBCLK1_USCI1CKEN_Msk;

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK->CLKSEL1 &= ~CLK_CLKSEL1_UART0SEL_Msk;
    CLK->CLKSEL1 |= (0x0 << CLK_CLKSEL1_UART0SEL_Pos);


    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set PE multi-function pins for USCI0_DAT0, USCI0_DAT1, USCI0_CTL0 and USCI0_CTL1 */
    SYS->GPE_MFPL = (SYS->GPE_MFPL & (~SYS_GPE_MFPL_PE3MFP_Msk)) | (7 << SYS_GPE_MFPL_PE3MFP_Pos);
    SYS->GPE_MFPL = (SYS->GPE_MFPL & (~SYS_GPE_MFPL_PE4MFP_Msk)) | (7 << SYS_GPE_MFPL_PE4MFP_Pos);
    SYS->GPE_MFPL = (SYS->GPE_MFPL & (~SYS_GPE_MFPL_PE5MFP_Msk)) | (7 << SYS_GPE_MFPL_PE5MFP_Pos);
    SYS->GPE_MFPL = (SYS->GPE_MFPL & (~SYS_GPE_MFPL_PE6MFP_Msk)) | (7 << SYS_GPE_MFPL_PE6MFP_Pos);
}

void UART0_Init()
{

    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

void USCI0_Init()
{

    /* Configure USCI0 as UART mode */
    UUART_Open(UUART0, 115200);
}


int32_t main(void)
{

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, peripheral clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    /* Init USCI0 for test */
    USCI0_Init();


    printf("\n\nCPU @ %d Hz\n", SystemCoreClock);

    printf("\nUSCI UART Sample Program\n");

    /* UART RS485 sample slave function */
    RS485_FunctionTest();

    while(1);

}
