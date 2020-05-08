/**************************************************************************//**
 * @file     main.c
 * @version  V2.00
 * @brief    Access SPI flash using QSPI quad mode
 *
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK           192000000
#define TEST_NUMBER         1   /* page numbers */
#define TEST_LENGTH         256 /* length */

#define QSPI_FLASH_PORT  QSPI0

uint8_t SrcArray[TEST_LENGTH];
uint8_t DestArray[TEST_LENGTH];

void D2D3_SwitchToNormalMode(void)
{
    SYS->GPA_MFPL =  SYS->GPA_MFPL & ~(SYS_GPA_MFPL_PA4MFP_Msk | SYS_GPA_MFPL_PA5MFP_Msk);
    GPIO_SetMode(PA, BIT4, GPIO_MODE_OUTPUT);
    GPIO_SetMode(PA, BIT5, GPIO_MODE_OUTPUT);
    PA4 = 1;
    PA5 = 1;
}

void D2D3_SwitchToQuadMode(void)
{
    SYS->GPA_MFPL =  (SYS->GPA_MFPL & ~(SYS_GPA_MFPL_PA4MFP_Msk | SYS_GPA_MFPL_PA5MFP_Msk)) | SYS_GPA_MFPL_PA4MFP_QSPI0_MOSI1 | SYS_GPA_MFPL_PA5MFP_QSPI0_MISO1;
}

uint16_t SpiFlash_ReadMidDid(void)
{
    uint8_t u8RxData[6], u8IDCnt = 0;

    // /CS: active
    QSPI_SET_SS_LOW(QSPI_FLASH_PORT);

    // send Command: 0x90, Read Manufacturer/Device ID
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x90);

    // send 24-bit '0', dummy
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x00);
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x00);
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x00);

    // receive 16-bit
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x00);
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x00);

    // wait tx finish
    while(QSPI_IS_BUSY(QSPI_FLASH_PORT));

    // /CS: de-active
    QSPI_SET_SS_HIGH(QSPI_FLASH_PORT);

    while(!QSPI_GET_RX_FIFO_EMPTY_FLAG(QSPI_FLASH_PORT))
        u8RxData[u8IDCnt ++] = QSPI_READ_RX(QSPI_FLASH_PORT);

    return ( (u8RxData[4]<<8) | u8RxData[5] );
}

void SpiFlash_ChipErase(void)
{
    // /CS: active
    QSPI_SET_SS_LOW(QSPI_FLASH_PORT);

    // send Command: 0x06, Write enable
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x06);

    // wait tx finish
    while(QSPI_IS_BUSY(QSPI_FLASH_PORT));

    // /CS: de-active
    QSPI_SET_SS_HIGH(QSPI_FLASH_PORT);

    //////////////////////////////////////////

    // /CS: active
    QSPI_SET_SS_LOW(QSPI_FLASH_PORT);

    // send Command: 0xC7, Chip Erase
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0xC7);

    // wait tx finish
    while(QSPI_IS_BUSY(QSPI_FLASH_PORT));

    // /CS: de-active
    QSPI_SET_SS_HIGH(QSPI_FLASH_PORT);

    QSPI_ClearRxFIFO(QSPI_FLASH_PORT);
}

uint8_t SpiFlash_ReadStatusReg(void)
{
    uint8_t u8Val;

    QSPI_ClearRxFIFO(QSPI_FLASH_PORT);

    // /CS: active
    QSPI_SET_SS_LOW(QSPI_FLASH_PORT);

    // send Command: 0x05, Read status register
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x05);

    // read status
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x00);

    // wait tx finish
    while(QSPI_IS_BUSY(QSPI_FLASH_PORT));

    // /CS: de-active
    QSPI_SET_SS_HIGH(QSPI_FLASH_PORT);

    // skip first rx data
    u8Val = QSPI_READ_RX(QSPI_FLASH_PORT);
    u8Val = QSPI_READ_RX(QSPI_FLASH_PORT);

    return u8Val;
}

uint8_t SpiFlash_ReadStatusReg2(void)
{
    uint8_t u8Val;

    QSPI_ClearRxFIFO(QSPI_FLASH_PORT);

    // /CS: active
    QSPI_SET_SS_LOW(QSPI_FLASH_PORT);

    // send Command: 0x35, Read status register
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x35);

    // read status
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x00);

    // wait tx finish
    while(QSPI_IS_BUSY(QSPI_FLASH_PORT));

    // /CS: de-active
    QSPI_SET_SS_HIGH(QSPI_FLASH_PORT);

    // skip first rx data
    u8Val = QSPI_READ_RX(QSPI_FLASH_PORT);
    u8Val = QSPI_READ_RX(QSPI_FLASH_PORT);

    return u8Val;
}

void SpiFlash_WriteStatusReg(uint8_t u8Value1, uint8_t u8Value2)
{
    // /CS: active
    QSPI_SET_SS_LOW(QSPI_FLASH_PORT);

    // send Command: 0x06, Write enable
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x06);

    // wait tx finish
    while(QSPI_IS_BUSY(QSPI_FLASH_PORT));

    // /CS: de-active
    QSPI_SET_SS_HIGH(QSPI_FLASH_PORT);

    ///////////////////////////////////////

    // /CS: active
    QSPI_SET_SS_LOW(QSPI_FLASH_PORT);

    // send Command: 0x01, Write status register
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x01);

    // write status
    QSPI_WRITE_TX(QSPI_FLASH_PORT, u8Value1);
    QSPI_WRITE_TX(QSPI_FLASH_PORT, u8Value2);

    // wait tx finish
    while(QSPI_IS_BUSY(QSPI_FLASH_PORT));

    // /CS: de-active
    QSPI_SET_SS_HIGH(QSPI_FLASH_PORT);
}

void SpiFlash_WaitReady(void)
{
    volatile uint8_t ReturnValue;

    do
    {
        ReturnValue = SpiFlash_ReadStatusReg();
        ReturnValue = ReturnValue & 1;
    }
    while(ReturnValue!=0);   // check the BUSY bit
}

void SpiFlash_NormalPageProgram(uint32_t StartAddress, uint8_t *u8DataBuffer)
{
    uint32_t i = 0;

    // /CS: active
    QSPI_SET_SS_LOW(QSPI_FLASH_PORT);

    // send Command: 0x06, Write enable
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x06);

    // wait tx finish
    while(QSPI_IS_BUSY(QSPI_FLASH_PORT));

    // /CS: de-active
    QSPI_SET_SS_HIGH(QSPI_FLASH_PORT);


    // /CS: active
    QSPI_SET_SS_LOW(QSPI_FLASH_PORT);

    // send Command: 0x02, Page program
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x02);

    // send 24-bit start address
    QSPI_WRITE_TX(QSPI_FLASH_PORT, (StartAddress>>16) & 0xFF);
    QSPI_WRITE_TX(QSPI_FLASH_PORT, (StartAddress>>8)  & 0xFF);
    QSPI_WRITE_TX(QSPI_FLASH_PORT, StartAddress       & 0xFF);

    // write data
    while(1)
    {
        if(!QSPI_GET_TX_FIFO_FULL_FLAG(QSPI_FLASH_PORT))
        {
            QSPI_WRITE_TX(QSPI_FLASH_PORT, u8DataBuffer[i++]);
            if(i > 255) break;
        }
    }

    // wait tx finish
    while(QSPI_IS_BUSY(QSPI_FLASH_PORT));

    // /CS: de-active
    QSPI_SET_SS_HIGH(QSPI_FLASH_PORT);

    QSPI_ClearRxFIFO(QSPI_FLASH_PORT);
}

void spiFlash_EnableQEBit(void)
{
    uint8_t u8Status1 = SpiFlash_ReadStatusReg();
    uint8_t u8Status2 = SpiFlash_ReadStatusReg2();

    u8Status2 |= 0x2;
    SpiFlash_WriteStatusReg(u8Status1, u8Status2);
    SpiFlash_WaitReady();
}

void spiFlash_DisableQEBit(void)
{
    uint8_t u8Status1 = SpiFlash_ReadStatusReg();
    uint8_t u8Status2 = SpiFlash_ReadStatusReg2();

    u8Status2 &= ~0x2;
    SpiFlash_WriteStatusReg(u8Status1, u8Status2);
    SpiFlash_WaitReady();
}

void SpiFlash_QuadFastRead(uint32_t StartAddress, uint8_t *u8DataBuffer)
{
    uint32_t i;

    // enable quad mode
    spiFlash_EnableQEBit();

    // /CS: active
    QSPI_SET_SS_LOW(QSPI_FLASH_PORT);

    // Command: 0xEB, Fast Read quad data
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0xEB);
    while(QSPI_IS_BUSY(QSPI_FLASH_PORT));

    // enable QSPI quad IO mode and set direction to input
    D2D3_SwitchToQuadMode();
    QSPI_ENABLE_QUAD_OUTPUT_MODE(QSPI_FLASH_PORT);

    // send 24-bit start address
    QSPI_WRITE_TX(QSPI_FLASH_PORT, (StartAddress>>16) & 0xFF);
    QSPI_WRITE_TX(QSPI_FLASH_PORT, (StartAddress>>8)  & 0xFF);
    QSPI_WRITE_TX(QSPI_FLASH_PORT, StartAddress       & 0xFF);

    // dummy byte
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x00);
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x00);
    QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x00);

    while(QSPI_IS_BUSY(QSPI_FLASH_PORT));
    QSPI_ENABLE_QUAD_INPUT_MODE(QSPI_FLASH_PORT);

    // clear RX buffer
    QSPI_ClearRxFIFO(QSPI_FLASH_PORT);

    // read data
    for(i=0; i<256; i++)
    {
        QSPI_WRITE_TX(QSPI_FLASH_PORT, 0x00);
        while(QSPI_IS_BUSY(QSPI_FLASH_PORT));
        u8DataBuffer[i] = QSPI_READ_RX(QSPI_FLASH_PORT);
    }

    // wait tx finish
    while(QSPI_IS_BUSY(QSPI_FLASH_PORT));

    // /CS: de-active
    QSPI_SET_SS_HIGH(QSPI_FLASH_PORT);

    QSPI_DISABLE_QUAD_MODE(QSPI_FLASH_PORT);
    D2D3_SwitchToNormalMode();

    // disable quad mode
    spiFlash_DisableQEBit();
}

void SYS_Init(void)
{
    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT clock (external XTAL 12MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Select PCLK0 as the clock source of QSPI0 */
    CLK_SetModuleClock(QSPI0_MODULE, CLK_CLKSEL2_QSPI0SEL_PCLK0, MODULE_NoMsk);

    /* Enable UART peripheral clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Enable QSPI0 peripheral clock */
    CLK_EnableModuleClock(QSPI0_MODULE);

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Setup QSPI0 multi-function pins */
    SYS->GPA_MFPL |= SYS_GPA_MFPL_PA0MFP_QSPI0_MOSI0 | SYS_GPA_MFPL_PA1MFP_QSPI0_MISO0 | SYS_GPA_MFPL_PA2MFP_QSPI0_CLK | SYS_GPA_MFPL_PA3MFP_QSPI0_SS |
                     SYS_GPA_MFPL_PA4MFP_QSPI0_MOSI1 | SYS_GPA_MFPL_PA5MFP_QSPI0_MISO1;

    /* Enable QSPI0 clock pin (PA2) schmitt trigger */
    PA->SMTEN |= GPIO_SMTEN_SMTEN2_Msk;

    /* Enable QSPI0 I/O high slew rate */
    GPIO_SetSlewCtl(PA, 0x3F, GPIO_SLEWCTL_HIGH);

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock and CyclesPerUs automatically. */
    SystemCoreClockUpdate();
}

/* Main */
int main(void)
{
    uint32_t u32ByteCount, u32FlashAddress, u32PageNumber;
    uint32_t nError = 0;
    uint16_t u16ID;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    D2D3_SwitchToNormalMode();

    /* Init UART to 115200-8n1 for print message */
    UART_Open(UART0, 115200);

    /* Configure QSPI_FLASH_PORT as a master, MSB first, 8-bit transaction, QSPI Mode-0 timing, clock is 20MHz */
    QSPI_Open(QSPI_FLASH_PORT, QSPI_MASTER, QSPI_MODE_0, 8, 20000000);

    /* Disable auto SS function, control SS signal manually. */
    QSPI_DisableAutoSS(QSPI_FLASH_PORT);

    printf("\n+------------------------------------------------------------------------+\n");
    printf("|                M480 QSPI Quad Mode with Flash Sample Code               |\n");
    printf("+------------------------------------------------------------------------+\n");

    if((u16ID = SpiFlash_ReadMidDid()) != 0xEF14)
    {
        printf("Wrong ID, 0x%x\n", u16ID);
        while(1);
    }
    else
        printf("Flash found: W25X16 ...\n");

    printf("Erase chip ...");

    /* Erase SPI flash */
    SpiFlash_ChipErase();

    /* Wait ready */
    SpiFlash_WaitReady();

    printf("[OK]\n");

    /* init source data buffer */
    for(u32ByteCount=0; u32ByteCount<TEST_LENGTH; u32ByteCount++)
    {
        SrcArray[u32ByteCount] = u32ByteCount;
    }

    printf("Start to write data to Flash ...");
    /* Program SPI flash */
    u32FlashAddress = 0;
    for(u32PageNumber=0; u32PageNumber<TEST_NUMBER; u32PageNumber++)
    {
        /* page program */
        SpiFlash_NormalPageProgram(u32FlashAddress, SrcArray);
        SpiFlash_WaitReady();
        u32FlashAddress += 0x100;
    }

    printf("[OK]\n");

    /* clear destination data buffer */
    for(u32ByteCount=0; u32ByteCount<TEST_LENGTH; u32ByteCount++)
    {
        DestArray[u32ByteCount] = 0;
    }

    printf("Read & Compare ...");

    /* Read SPI flash */
    u32FlashAddress = 0;
    for(u32PageNumber=0; u32PageNumber<TEST_NUMBER; u32PageNumber++)
    {
        /* page read */
        SpiFlash_QuadFastRead(u32FlashAddress, DestArray);
        u32FlashAddress += 0x100;

        for(u32ByteCount=0; u32ByteCount<TEST_LENGTH; u32ByteCount++)
        {
            if(DestArray[u32ByteCount] != SrcArray[u32ByteCount])
                nError ++;
        }
    }

    if(nError == 0)
        printf("[OK]\n");
    else
        printf("[FAIL]\n");

    while(1);
}


/*** (C) COPYRIGHT 2013 Nuvoton Technology Corp. ***/


