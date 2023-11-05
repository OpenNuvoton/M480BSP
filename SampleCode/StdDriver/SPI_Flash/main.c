/**************************************************************************//**
 * @file     main.c
 * @version  V2.00
 * @brief    Access SPI flash through SPI interface.
 *
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK           192000000

#define TEST_NUMBER 1   /* page numbers */
#define TEST_LENGTH 256 /* length */

#define SPI_FLASH_PORT  SPI0

uint8_t SrcArray[TEST_LENGTH];
uint8_t DestArray[TEST_LENGTH];

uint16_t SpiFlash_ReadMidDid(void)
{
    uint8_t u8RxData[6], u8IDCnt = 0;

    // /CS: active
    SPI_SET_SS_LOW(SPI_FLASH_PORT);

    // send Command: 0x90, Read Manufacturer/Device ID
    SPI_WRITE_TX(SPI_FLASH_PORT, 0x90);

    // send 24-bit '0', dummy
    SPI_WRITE_TX(SPI_FLASH_PORT, 0x00);
    SPI_WRITE_TX(SPI_FLASH_PORT, 0x00);
    SPI_WRITE_TX(SPI_FLASH_PORT, 0x00);

    // receive 16-bit
    SPI_WRITE_TX(SPI_FLASH_PORT, 0x00);
    SPI_WRITE_TX(SPI_FLASH_PORT, 0x00);

    // wait tx finish
    while(SPI_IS_BUSY(SPI_FLASH_PORT));

    // /CS: de-active
    SPI_SET_SS_HIGH(SPI_FLASH_PORT);

    while(!SPI_GET_RX_FIFO_EMPTY_FLAG(SPI_FLASH_PORT))
        u8RxData[u8IDCnt ++] = SPI_READ_RX(SPI_FLASH_PORT);

    return ( (u8RxData[4]<<8) | u8RxData[5] );
}

void SpiFlash_ChipErase(void)
{
    // /CS: active
    SPI_SET_SS_LOW(SPI_FLASH_PORT);

    // send Command: 0x06, Write enable
    SPI_WRITE_TX(SPI_FLASH_PORT, 0x06);

    // wait tx finish
    while(SPI_IS_BUSY(SPI_FLASH_PORT));

    // /CS: de-active
    SPI_SET_SS_HIGH(SPI_FLASH_PORT);

    //////////////////////////////////////////

    // /CS: active
    SPI_SET_SS_LOW(SPI_FLASH_PORT);

    // send Command: 0xC7, Chip Erase
    SPI_WRITE_TX(SPI_FLASH_PORT, 0xC7);

    // wait tx finish
    while(SPI_IS_BUSY(SPI_FLASH_PORT));

    // /CS: de-active
    SPI_SET_SS_HIGH(SPI_FLASH_PORT);

    SPI_ClearRxFIFO(SPI_FLASH_PORT);
}

uint8_t SpiFlash_ReadStatusReg(void)
{
    // /CS: active
    SPI_SET_SS_LOW(SPI_FLASH_PORT);

    // send Command: 0x05, Read status register
    SPI_WRITE_TX(SPI_FLASH_PORT, 0x05);

    // read status
    SPI_WRITE_TX(SPI_FLASH_PORT, 0x00);

    // wait tx finish
    while(SPI_IS_BUSY(SPI_FLASH_PORT));

    // /CS: de-active
    SPI_SET_SS_HIGH(SPI_FLASH_PORT);

    // skip first rx data
    SPI_READ_RX(SPI_FLASH_PORT);

    return (SPI_READ_RX(SPI_FLASH_PORT) & 0xff);
}

void SpiFlash_WriteStatusReg(uint8_t u8Value)
{
    // /CS: active
    SPI_SET_SS_LOW(SPI_FLASH_PORT);

    // send Command: 0x06, Write enable
    SPI_WRITE_TX(SPI_FLASH_PORT, 0x06);

    // wait tx finish
    while(SPI_IS_BUSY(SPI_FLASH_PORT));

    // /CS: de-active
    SPI_SET_SS_HIGH(SPI_FLASH_PORT);

    ///////////////////////////////////////

    // /CS: active
    SPI_SET_SS_LOW(SPI_FLASH_PORT);

    // send Command: 0x01, Write status register
    SPI_WRITE_TX(SPI_FLASH_PORT, 0x01);

    // write status
    SPI_WRITE_TX(SPI_FLASH_PORT, u8Value);

    // wait tx finish
    while(SPI_IS_BUSY(SPI_FLASH_PORT));

    // /CS: de-active
    SPI_SET_SS_HIGH(SPI_FLASH_PORT);
}

void SpiFlash_WaitReady(void)
{
    uint8_t ReturnValue;

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
    SPI_SET_SS_LOW(SPI_FLASH_PORT);

    // send Command: 0x06, Write enable
    SPI_WRITE_TX(SPI_FLASH_PORT, 0x06);

    // wait tx finish
    while(SPI_IS_BUSY(SPI_FLASH_PORT));

    // /CS: de-active
    SPI_SET_SS_HIGH(SPI_FLASH_PORT);


    // /CS: active
    SPI_SET_SS_LOW(SPI_FLASH_PORT);

    // send Command: 0x02, Page program
    SPI_WRITE_TX(SPI_FLASH_PORT, 0x02);

    // send 24-bit start address
    SPI_WRITE_TX(SPI_FLASH_PORT, (StartAddress>>16) & 0xFF);
    SPI_WRITE_TX(SPI_FLASH_PORT, (StartAddress>>8)  & 0xFF);
    SPI_WRITE_TX(SPI_FLASH_PORT, StartAddress       & 0xFF);

    // write data
    while(1)
    {
        if(!SPI_GET_TX_FIFO_FULL_FLAG(SPI_FLASH_PORT))
        {
            SPI_WRITE_TX(SPI_FLASH_PORT, u8DataBuffer[i++]);
            if(i > 255) break;
        }
    }

    // wait tx finish
    while(SPI_IS_BUSY(SPI_FLASH_PORT));

    // /CS: de-active
    SPI_SET_SS_HIGH(SPI_FLASH_PORT);

    SPI_ClearRxFIFO(SPI_FLASH_PORT);
}

void SpiFlash_NormalRead(uint32_t StartAddress, uint8_t *u8DataBuffer)
{
    uint32_t i;

    // /CS: active
    SPI_SET_SS_LOW(SPI_FLASH_PORT);

    // send Command: 0x03, Read data
    SPI_WRITE_TX(SPI_FLASH_PORT, 0x03);

    // send 24-bit start address
    SPI_WRITE_TX(SPI_FLASH_PORT, (StartAddress>>16) & 0xFF);
    SPI_WRITE_TX(SPI_FLASH_PORT, (StartAddress>>8)  & 0xFF);
    SPI_WRITE_TX(SPI_FLASH_PORT, StartAddress       & 0xFF);

    while(SPI_IS_BUSY(SPI_FLASH_PORT));
    // clear RX buffer
    SPI_ClearRxFIFO(SPI_FLASH_PORT);

    // read data
    for(i=0; i<256; i++)
    {
        SPI_WRITE_TX(SPI_FLASH_PORT, 0x00);
        while(SPI_IS_BUSY(SPI_FLASH_PORT));
        u8DataBuffer[i] = SPI_READ_RX(SPI_FLASH_PORT);
    }

    // wait tx finish
    while(SPI_IS_BUSY(SPI_FLASH_PORT));

    // /CS: de-active
    SPI_SET_SS_HIGH(SPI_FLASH_PORT);
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

    /* Select PCLK0 as the clock source of SPI0 */
    CLK_SetModuleClock(SPI0_MODULE, CLK_CLKSEL2_SPI0SEL_PCLK1, MODULE_NoMsk);

    /* Enable UART peripheral clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Enable SPI0 peripheral clock */
    CLK_EnableModuleClock(SPI0_MODULE);

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Setup SPI0 multi-function pins */
    SYS->GPA_MFPL |= SYS_GPA_MFPL_PA0MFP_SPI0_MOSI | SYS_GPA_MFPL_PA1MFP_SPI0_MISO | SYS_GPA_MFPL_PA2MFP_SPI0_CLK | SYS_GPA_MFPL_PA3MFP_SPI0_SS;

    /* Enable SPI0 clock pin (PA2) schmitt trigger */
    PA->SMTEN |= GPIO_SMTEN_SMTEN2_Msk;

    /* Enable SPI0 I/O high slew rate */
    GPIO_SetSlewCtl(PA, 0xF, GPIO_SLEWCTL_HIGH);

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

    /* Init System, IP clock and multi-function I/O. */
    SYS_Init();

    /* Init UART to 115200-8n1 for print message */
    UART_Open(UART0, 115200);

    /* Configure SPI_FLASH_PORT as a master, MSB first, 8-bit transaction, SPI Mode-0 timing, clock is 20MHz */
    SPI_Open(SPI_FLASH_PORT, SPI_MASTER, SPI_MODE_0, 8, 20000000);

    /* Disable auto SS function, control SS signal manually. */
    SPI_DisableAutoSS(SPI_FLASH_PORT);

    printf("\n+------------------------------------------------------------------------+\n");
    printf("|                 M480 SPI Sample with SPI Flash                         |\n");
    printf("+------------------------------------------------------------------------+\n");

    u16ID = SpiFlash_ReadMidDid();

    if (u16ID == 0xEF13)
        printf("Flash found: W25Q80 ...\n");
    else if (u16ID == 0xEF14)
        printf("Flash found: W25Q16 ...\n");
    else if (u16ID == 0xEF15)
        printf("Flash found: W25Q32 ...\n");
    else if (u16ID == 0xEF16)
        printf("Flash found: W25Q64 ...\n");
    else if (u16ID == 0xEF17)
        printf("Flash found: W25Q128 ...\n");
    else
    {
        printf("Wrong ID, 0x%x\n", u16ID);

        while (1);
    }

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

    printf("Start to normal write data to Flash ...");
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

    printf("Normal Read & Compare ...");

    /* Read SPI flash */
    u32FlashAddress = 0;
    for(u32PageNumber=0; u32PageNumber<TEST_NUMBER; u32PageNumber++)
    {
        /* page read */
        SpiFlash_NormalRead(u32FlashAddress, DestArray);
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


/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/


