/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Transmit and receive data in UART RS485 mode.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define RXBUFSIZE 1024

#define IS_USE_RS485NMM   1      //1:Select NMM_Mode , 0:Select AAD_Mode
#define MATCH_ADDRSS1     0xC0
#define MATCH_ADDRSS2     0xA2
#define UNMATCH_ADDRSS1   0xB1
#define UNMATCH_ADDRSS2   0xD3

/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
uint8_t g_u8SendData[12] = {0};

/*---------------------------------------------------------------------------------------------------------*/
/* Define functions prototype                                                                              */
/*---------------------------------------------------------------------------------------------------------*/
void RS485_HANDLE(void);
void RS485_SendAddressByte(uint8_t u8data);
void RS485_SendDataByte(uint8_t *pu8TxBuf, uint32_t u32WriteBytes);
void RS485_9bitModeMaster(void);
void RS485_9bitModeSlave(void);
void RS485_FunctionTest(void);


void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT*/
    CLK->PWRCTL |= CLK_PWRCTL_HXTEN_Msk; // XTAL12M (HXT) Enabled

    /* Waiting clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(192000000);
    CLK->PCLKDIV = (CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2); // PCLK divider set 2

    /* Enable IP clock */
    CLK->APBCLK0 |= CLK_APBCLK0_UART0CKEN_Msk; // UART0 Clock Enable
    CLK->APBCLK0 |= CLK_APBCLK0_UART1CKEN_Msk; // UART1 Clock Enable

    /* Select IP clock source */
    /* Select UART0 clock source is HXT */
    CLK->CLKSEL1 = (CLK->CLKSEL1 & ~CLK_CLKSEL1_UART0SEL_Msk) | (0x0 << CLK_CLKSEL1_UART0SEL_Pos);
    /* Select UART1 clock source is HXT */
    CLK->CLKSEL1 = (CLK->CLKSEL1 & ~CLK_CLKSEL1_UART1SEL_Msk) | (0x0 << CLK_CLKSEL1_UART1SEL_Pos);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set PA multi-function pins for UART1 TXD, RXD, CTS and RTS */
    SYS->GPA_MFPL &= ~(SYS_GPA_MFPL_PA0MFP_Msk | SYS_GPA_MFPL_PA1MFP_Msk |
                       SYS_GPA_MFPL_PA2MFP_Msk | SYS_GPA_MFPL_PA3MFP_Msk);
    SYS->GPA_MFPL |= (0x8 << SYS_GPA_MFPL_PA0MFP_Pos) | (0x8 << SYS_GPA_MFPL_PA1MFP_Pos) |
                     (0x8 << SYS_GPA_MFPL_PA2MFP_Pos) | (0x8 << SYS_GPA_MFPL_PA3MFP_Pos);

    /* Lock protected registers */
    SYS_LockReg();

}

void UART0_Init()
{
    UART_Open(UART0, 115200);
}

void UART1_Init()
{
    UART_Open(UART1, 115200);
}


int main(void)
{
    /* Init System, IP clock and multi-function I/O */
    SYS_Init();
    /* Init UART0 for printf */
    UART0_Init();

    /* Init UART1 */
    UART1_Init();

    printf("\n\nCPU @ %dHz\n", SystemCoreClock);

    printf("+------------------------+\n");
    printf("| RS485 function test     |\n");
    printf("+------------------------+\n");

    RS485_FunctionTest();

    while(1);
}

/*---------------------------------------------------------------------------------------------------------*/
/* ISR to handle UART Channel 1 interrupt event                                                            */
/*---------------------------------------------------------------------------------------------------------*/
void UART1_IRQHandler(void)
{
    RS485_HANDLE();
}

/*---------------------------------------------------------------------------------------------------------*/
/* RS485 Callback function                                                                                 */
/*---------------------------------------------------------------------------------------------------------*/
void RS485_HANDLE()
{
    volatile uint32_t addr=0;
    volatile uint32_t regRX=0xFF;
    volatile uint32_t u32IntSts = UART1->INTSTS;

    if((u32IntSts & UART_INTSTS_RLSINT_Msk)&&(u32IntSts & UART_INTSTS_RDAINT_Msk))           /* RLS INT & RDA INT */  //For RS485 Detect Address
    {
        if(UART1->FIFOSTS & UART_FIFOSTS_ADDRDETF_Msk)   /* ADD_IF, RS485 mode */
        {
            addr = UART1->DAT;
            UART_RS485_CLEAR_ADDR_FLAG(UART1);        /* clear ADD_IF flag */
            printf("\nAddr=0x%x,Get:",addr);

#if (IS_USE_RS485NMM ==1) //RS485_NMM
            /* if address match, enable RX to receive data, otherwise to disable RX. */
            /* In NMM mode,user can decide multi-address filter. In AAD mode,only one address can set */
            if (( addr == MATCH_ADDRSS1)||( addr == MATCH_ADDRSS2))
            {
                UART1->FIFO &= ~ UART_FIFO_RXOFF_Msk;  /* Enable RS485 RX */
            }
            else
            {
                printf("\n");
                UART1->FIFO |= UART_FIFO_RXOFF_Msk;      /* Disable RS485 RX */
                UART1->FIFO |= UART_FIFO_RXRST_Msk;      /* Clear data from RX FIFO */
            }
#endif
        }
    }
    else if((u32IntSts & UART_INTSTS_RDAINT_Msk) || (u32IntSts & UART_INTSTS_RXTOINT_Msk) )     /* Rx Ready or Time-out INT*/
    {
        /* Handle received data */
        printf("%2d,",UART1->DAT);
    }
    else if(u32IntSts & UART_INTSTS_BUFERRINT_Msk)     /* Buffer Error INT */
    {
        printf("\nBuffer Error...\n");
        UART_ClearIntFlag(UART1, UART_INTSTS_BUFERRINT_Msk);
    }
}

/*---------------------------------------------------------------------------------------------------------*/
/*  RS485 Transmit Control  (Address Byte: Parity Bit =1 , Data Byte:Parity Bit =0)                        */
/*---------------------------------------------------------------------------------------------------------*/
void RS485_SendAddressByte(uint8_t u8data)
{
    UART_SetLineConfig(UART1, 0, UART_WORD_LEN_8, UART_PARITY_MARK, UART_STOP_BIT_1);
    UART_WRITE(UART1,u8data);
}

void RS485_SendDataByte(uint8_t *pu8TxBuf, uint32_t u32WriteBytes)
{
    UART_SetLineConfig(UART1, 0, UART_WORD_LEN_8, UART_PARITY_SPACE, UART_STOP_BIT_1);
    UART_Write(UART1,pu8TxBuf,u32WriteBytes);
}

/*---------------------------------------------------------------------------------------------------------*/
/*  RS485 Transmit Test                                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
void RS485_9bitModeMaster()
{
    int32_t i32;
    uint8_t g_u8SendDataGroup1[10] = {0};
    uint8_t g_u8SendDataGroup2[10] = {0};
    uint8_t g_u8SendDataGroup3[10] = {0};
    uint8_t g_u8SendDataGroup4[10] = {0};

    printf("\n\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|               RS485 9-bit Master Test                     |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| The function will send different address with 10 data bytes|\n");
    printf("| to test RS485 9-bit mode. Please connect TX/RX to another |\n");
    printf("| board and wait its ready to receive.                      |\n");
    printf("| Press any key to start...                                 |\n");
    printf("+-----------------------------------------------------------+\n\n");
    getchar();

    /* Set RS485-Master as AUD mode*/
    UART1->MODEM &= ~UART_MODEM_RTSACTLV_Msk;
    UART_SelectRS485Mode(UART1, UART_ALTCTL_RS485AUD_Msk, 0);

    /* Prepare Data to transmit*/
    for(i32=0; i32<10; i32++)
    {
        g_u8SendDataGroup1[i32] = i32;
        g_u8SendDataGroup2[i32] = i32+10;
        g_u8SendDataGroup3[i32] = i32+20;
        g_u8SendDataGroup4[i32] = i32+30;
    }
    /* Send For different Address and data for test */
    printf("Send Address %x and data 0~9\n",MATCH_ADDRSS1);
    RS485_SendAddressByte( MATCH_ADDRSS1 );
    RS485_SendDataByte(g_u8SendDataGroup1,10);

    printf("Send Address %x and data 10~19\n",UNMATCH_ADDRSS1);
    RS485_SendAddressByte( UNMATCH_ADDRSS1 );
    RS485_SendDataByte(g_u8SendDataGroup2,10);

    printf("Send Address %x and data 20~29\n",MATCH_ADDRSS2);
    RS485_SendAddressByte( MATCH_ADDRSS2 );
    RS485_SendDataByte(g_u8SendDataGroup3,10);

    printf("Send Address %x and data 30~39\n",UNMATCH_ADDRSS2);
    RS485_SendAddressByte( UNMATCH_ADDRSS2 );
    RS485_SendDataByte(g_u8SendDataGroup4,10);
    printf("Transfer Done\n");
}

/*---------------------------------------------------------------------------------------------------------*/
/*  RS485 Receive Test  (IS_USE_RS485NMM: 0:AAD  1:NMM)                                                    */
/*---------------------------------------------------------------------------------------------------------*/
void RS485_9bitModeSlave()
{
    /* Set Data Format*/ /* Only need parity enable whenever parity ODD/EVEN */
    UART_SetLineConfig(UART1, 0, UART_WORD_LEN_8, UART_PARITY_EVEN, UART_STOP_BIT_1);

    /* Set RX Trigger Level = 1 */
    UART1->FIFO &= ~UART_FIFO_RFITL_Msk;
    UART1->FIFO |= UART_FIFO_RFITL_1BYTE;

#if(IS_USE_RS485NMM == 1)
    printf("+-----------------------------------------------------------+\n");
    printf("|    Normal Multidrop Operation Mode                        |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| The function is used to test 9-bit slave mode.            |\n");
    printf("| Only Address %2x and %2x,data can receive                  |\n",MATCH_ADDRSS1,MATCH_ADDRSS2);
    printf("+-----------------------------------------------------------+\n");

    /* Set RX_DIS enable before set RS485-NMM mode */
    UART1->FIFO |= UART_FIFO_RXOFF_Msk;

    /* Set RS485-NMM Mode */
    UART1->MODEM &= ~UART_MODEM_RTSACTLV_Msk;
    UART_SelectRS485Mode(UART1, UART_ALTCTL_RS485NMM_Msk|UART_ALTCTL_ADDRDEN_Msk, 0);

#else
    printf("Auto Address Match Operation Mode\n");
    printf("+-----------------------------------------------------------+\n");
    printf("| The function is used to test 9-bit slave mode.            |\n");
    printf("|    Auto Address Match Operation Mode                      |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("|Only Address %2x,data can receive                          |\n",MATCH_ADDRSS1);
    printf("+-----------------------------------------------------------+\n");

    /* Set RS485-AAD Mode and address match is 0xC0 */
    UART_SelectRS485Mode(UART1, UART_ALTCTL_RS485AAD_Msk|UART_ALTCTL_ADDRDEN_Msk, MATCH_ADDRSS1);
#endif

    /* Enable RDA\RLS\Time-out Interrupt  */
    UART_ENABLE_INT(UART1, (UART_INTEN_RDAIEN_Msk | UART_INTEN_RLSIEN_Msk));
    NVIC_EnableIRQ(UART1_IRQn);

    printf("Ready to receive data...(Press any key to stop test)\n");
    getchar();

    UART_DISABLE_INT(UART1, (UART_INTEN_RDAIEN_Msk | UART_INTEN_RLSIEN_Msk | UART_INTEN_RXTOIEN_Msk));

    /* Set UART Function */
    UART_Open(UART1, 115200);
    printf("\n\nEnd test\n");
}


/*---------------------------------------------------------------------------------------------------------*/
/*  RS485 Function Test                                                                                    */
/*---------------------------------------------------------------------------------------------------------*/
void RS485_FunctionTest()
{
    uint32_t u32Item;
    printf("\n\n");
    printf("+-------------------------------------------------------------+\n");
    printf("|            IO Setting                                       |\n");
    printf("+-------------------------------------------------------------+\n");
    printf("|  ______                        _______                      |\n");
    printf("| |      |                      |       |                     |\n");
    printf("| |Master|---TXD0 <====> RXD0---| Slave |                     |\n");
    printf("| |      |---RTS0 <====> RTS0---|       |                     |\n");
    printf("| |______|                      |_______|                     |\n");
    printf("|                                                             |\n");
    printf("+-------------------------------------------------------------+\n\n");
    printf("+-------------------------------------------------------------+\n");
    printf("|       RS485 Function Test                                   |\n");
    printf("+-------------------------------------------------------------+\n");
    printf("|  Please select Master or Slave test                         |\n");
    printf("|  [0] Master    [1] Slave                                    |\n");
    printf("+-------------------------------------------------------------+\n\n");
    u32Item = getchar();

    /*
        The sample code is used to test RS485 9-bit mode and needs
        two Module test board to complete the test.
        Master:
            1.Set AUD mode and HW will control RTS pin. LEV_RTS is set to '0'.
            2.Master will send four different address with 10 bytes data to test Slave.
            3.Address bytes : the parity bit should be '1'. (Set UA_LCR = 0x2B)
            4.Data bytes : the parity bit should be '0'. (Set UA_LCR = 0x3B)
            5.RTS pin is low in idle state. When master is sending,
              RTS pin will be pull high.

        Slave:
            1.Set AAD and AUD mode firstly. LEV_RTS is set to '0'.
            2.The received byte, parity bit is '1' , is considered "ADDRESS".
            3.The received byte, parity bit is '0' , is considered "DATA".  (Default)
            4.AAD: The slave will ignore any data until ADDRESS match ADDR_MATCH value.
              When RLS and RDA interrupt is happened,it means the ADDRESS is received.
              Check if RS485_ADD_DETF is set and read UA_RBR to clear ADDRESS stored in rx_fifo.

              NMM: The slave will ignore data byte until disable RX_DIS.
              When RLS and RDA interrupt is happened,it means the ADDRESS is received.
              Check the ADDRESS is match or not by user in UART_IRQHandler.
              If the ADDRESS is match,clear RX_DIS bit to receive data byte.
              If the ADDRESS is not match,set RX_DIS bit to avoid data byte stored in FIFO.
    */

    if(u32Item =='0')
        RS485_9bitModeMaster();
    else
        RS485_9bitModeSlave();
}


