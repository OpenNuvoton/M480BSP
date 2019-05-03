/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief
 *           Transmit and receive data in RS485 mode.
 *           This sample code needs to work with USCI_UART_RS485_Slave.
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include "stdio.h"
#include "NuMicro.h"


#define ADDRSS1 0xC0
#define ADDRSS2 0xA2
#define ADDRSS3 0xB1
#define ADDRSS4 0xD3


/*---------------------------------------------------------------------------------------------------------*/
/*  RS485 Transmit Control  (Address Byte: Parity Bit =1 , Data Byte:Parity Bit =0)                        */
/*---------------------------------------------------------------------------------------------------------*/
void RS485_SendAddressByte(uint8_t u8data)
{
    UUART_WRITE(UUART0, (0x100|u8data));
}

void RS485_SendDataByte(uint8_t *pu8TxBuf, uint32_t u32WriteBytes)
{
    uint32_t u32Count;

    for(u32Count = 0; u32Count != u32WriteBytes; u32Count++)
    {
        while(UUART_GET_TX_FULL(UUART0));           /* Wait if Tx is full */
        UUART_WRITE(UUART0, pu8TxBuf[u32Count]);    /* Send UART Data from buffer */
    }
}

/*---------------------------------------------------------------------------------------------------------*/
/*  RS485 Transmit Test                                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
void RS485_9bitModeMaster()
{
    volatile int32_t i32;
    uint8_t g_u8SendDataGroup1[10] = {0};
    uint8_t g_u8SendDataGroup2[10] = {0};
    uint8_t g_u8SendDataGroup3[10] = {0};
    uint8_t g_u8SendDataGroup4[10] = {0};

    printf("\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|               RS485 9-bit Master Test                     |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| The function will send different address with 10 data     |\n");
    printf("| bytes to test RS485 9-bit mode. Please connect TX/RX to   |\n");
    printf("| another board and wait its ready to receive.              |\n");
    printf("| Press any key to start...                                 |\n");
    printf("+-----------------------------------------------------------+\n\n");
    getchar();

    /* Set UART line configuration and control signal output inverse */
    UUART_SetLine_Config(UUART0, 0, UUART_WORD_LEN_9, UUART_PARITY_NONE, UUART_STOP_BIT_1);
    UUART0->LINECTL |= UUART_LINECTL_CTLOINV_Msk;

    /* Enable RTS auto direction function */
    UUART0->PROTCTL |= UUART_PROTCTL_RTSAUDIREN_Msk;

    /* Prepare data to transmit */
    for(i32 = 0; i32 < 10; i32++)
    {
        g_u8SendDataGroup1[i32] = i32;
        g_u8SendDataGroup2[i32] = i32 + 10;
        g_u8SendDataGroup3[i32] = i32 + 20;
        g_u8SendDataGroup4[i32] = i32 + 30;
    }

    /* Send different address and data for test */
    printf("Send Address %x and data 0~9\n", ADDRSS1);
    RS485_SendAddressByte(ADDRSS1);
    RS485_SendDataByte(g_u8SendDataGroup1, 10);

    printf("Send Address %x and data 10~19\n", ADDRSS2);
    RS485_SendAddressByte(ADDRSS1);
    RS485_SendDataByte(g_u8SendDataGroup2, 10);

    printf("Send Address %x and data 20~29\n", ADDRSS3);
    RS485_SendAddressByte(ADDRSS3);
    RS485_SendDataByte(g_u8SendDataGroup3, 10);

    printf("Send Address %x and data 30~39\n", ADDRSS4);
    RS485_SendAddressByte(ADDRSS4);
    RS485_SendDataByte(g_u8SendDataGroup4, 10);

    printf("Transfer Done\n");
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

    RS485_9bitModeMaster();

}

void SYS_Init(void)
{

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable clock */
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

    /* UART RS485 sample master function */
    RS485_FunctionTest();

    while(1);

}
