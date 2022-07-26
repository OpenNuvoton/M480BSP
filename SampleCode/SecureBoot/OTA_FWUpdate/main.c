/**************************************************************************//**
 * @file     main.c
 * @version  2.0.0
 * @date     20, June, 2017
 * @brief    This sample code is run at LDROM, and use it to boot from APROM or
 *           update APROM. After reset the system, the program will boot from APROM.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define AP_BOOT_ADDR0     0x0000
#define AP_BOOT_ADDR1     0x4000
#define AP_HEAD           0x8000
#define RECEIVE_TIMEROUT  0x100

void SYS_Init(void)
{
    uint32_t volatile i;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable External XTAL (4~24 MHz) */
    CLK->PWRCTL |= CLK_PWRCTL_HXTEN_Msk;

    /* Waiting for 12MHz clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Switch HCLK clock source to HXT */
    CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_HCLKSEL_Msk) | CLK_CLKSEL0_HCLKSEL_HXT;

    /* Set core clock as PLL_CLOCK from PLL */
    CLK->PLLCTL = CLK_PLLCTL_192MHz_HIRC;

    /* Waiting for PLL clock ready */
    CLK_WaitClockReady(CLK_STATUS_PLLSTB_Msk);

    /* Switch HCLK clock source to PLL */
    CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_HCLKSEL_Msk) | CLK_CLKSEL0_HCLKSEL_PLL;

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Select UART0 clock source from HXT */
    CLK->CLKSEL1 = (CLK->CLKSEL1 & ~CLK_CLKSEL1_UART0SEL_Msk) | CLK_CLKSEL1_UART0SEL_HXT;

    /* Enable IP clock */
    CLK->APBCLK0 |= CLK_APBCLK0_UART0CKEN_Msk;

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);
}

void UART0_Init(void)
{
    /* Configure UART0 and set UART0 baud rate */
    UART0->LINE = 0x3;
    UART0->BAUD = 0x30000066;
}

/**
 * @brief       Routine to send a char
 * @param[in]   ch Character to send to debug port.
 * @returns     Send value from UART debug port
 * @details     Send a target char to UART debug port .
 */
static void SendChar_ToUART(int ch)
{
    while (UART0->FIFOSTS & UART_FIFOSTS_TXFULL_Msk);

    UART0->DAT = ch;
    if(ch == '\n')
    {
        while (UART0->FIFOSTS & UART_FIFOSTS_TXFULL_Msk);
        UART0->DAT = '\r';
    }
}

static void PutString(char *str)
{
    while (*str != '\0')
    {
        SendChar_ToUART(*str++);
    }
}

/**
 * @brief       Receive data from UART0
 *
 * @param[in]   cnt time out counter by system clock * 0x10000
 *
 * @returns     Get value from UART0 or UART_TIMEROUT
 *
 */
uint16_t ReceiveBytes(int32_t cnt)
{
    if(cnt!=0) cnt*=0x10000;
    while(1)
    {
        if(cnt--==1)
        {
            return RECEIVE_TIMEROUT;
        }
        if((UART0->FIFOSTS & UART_FIFOSTS_RXEMPTY_Msk) == 0)
        {
            return (UART0->DAT);
        }
    }
}


/**
 * @brief       Get Old/New firmware address
 *
 * @param[in]   item 1 : New firmware address 0: Old firmware address
 *
 * @returns     AP_BOOT_ADDR0 or AP_BOOT_ADDR1
 *
 */
uint32_t Get_Version(int item)
{
    if(item==1)
    {
        if (FMC_Read(AP_HEAD)==1)
            return AP_BOOT_ADDR0;
        else
            return AP_BOOT_ADDR1;
    }
    else
    {
        if (FMC_Read(AP_HEAD)==1)
            return AP_BOOT_ADDR1;
        else
            return AP_BOOT_ADDR0;
    }
}


/**
 * @brief       Updated Firmware from UART0
 *
 * @param[in]   UpdateAddr AP_BOOT_ADDR0 or AP_BOOT_ADDR0
 *
 * @returns     None
 *
 */
void UpdatedFirmware(uint32_t UpdateAddr)
{
    uint8_t IdxBytes=0;
    uint32_t Addr = UpdateAddr;
    volatile uint32_t u32TmpPtr[1];
    volatile uint8_t *u8TmpPtr = (uint8_t *)u32TmpPtr;
    uint32_t cnt=0;
    uint16_t tmp;
    uint8_t ipage=0;
    *u8TmpPtr=ReceiveBytes(0);
    cnt++;
    IdxBytes=1;
    FMC_Erase(UpdateAddr);   /* Erase page */
    while(1)
    {
        tmp = ReceiveBytes(0x20);
        if((tmp & RECEIVE_TIMEROUT)==0)
        {
            *(u8TmpPtr+IdxBytes)=(uint8_t)tmp;
            cnt++;
            IdxBytes++;
        }
        else
            break;

        if(IdxBytes==4)
        {
            IdxBytes=0;
            if(cnt%FMC_FLASH_PAGE_SIZE==(FMC_FLASH_PAGE_SIZE-1))
            {
                ipage++;
                FMC_Erase(UpdateAddr+FMC_FLASH_PAGE_SIZE*ipage);   /* Erase page */
            }
            FMC_Write(Addr, *u32TmpPtr); /* Write data */
            Addr+=4;
            if(cnt%10==0) PutString(".");
        }
    }
    if(cnt%FMC_FLASH_PAGE_SIZE==(FMC_FLASH_PAGE_SIZE-1))
    {
        ipage++;
        FMC_Erase(UpdateAddr+FMC_FLASH_PAGE_SIZE*ipage);   /* Erase page */
    }
    FMC_Write(Addr+=4, *u32TmpPtr);

    FMC_Erase(AP_HEAD);
    if(UpdateAddr==AP_BOOT_ADDR0)
    {
        FMC_Write(AP_HEAD, 1);
        FMC_Write(AP_HEAD+4, 0);
    }
    else
    {
        FMC_Write(AP_HEAD, 0);
        FMC_Write(AP_HEAD+4, 1);
    }
    PutString("\n.......finished\n");
}

void PutMassage(uint32_t addr)
{
    if(addr==AP_BOOT_ADDR0)
        PutString("(RO_BASE 0x0):\n");
    else
        PutString("(RO_BASE 0x4000):\n");
}

int32_t main (void)
{

    /*---------------------------------------------------------------------------------------------------------*/
    /*    User needs to install "Tera Term" application. and then                                              */
    /*    set "transfer delay" to 10ms and open serial port.                                                   */
    /*    Firstly, choice 2 to update binary files , user need to prepare two binary files,                    */
    /*    set RO_BASE to AP_BOOT_ADDR0 and the other to AP_BOOT_ADDR1 , and then use                           */
    /*    Terra Term(file->Send files and enable binary check box) to send binary file to update APROM.        */
    /*---------------------------------------------------------------------------------------------------------*/
    uint8_t ch;
    uint32_t Uaddr;
    SYS_Init();               /* Init System, IP clock and multi-function I/O */
    UART0_Init();             /* Initialize UART0 */
    SYS_UnlockReg();          /* Unlock register lock protect */
    FMC_Open();               /* Enable FMC ISP function */
    FMC_ENABLE_AP_UPDATE();   /* Enable APROM update. */

    PutString("\n\n");
    PutString("+-----------------------------------------------------+\n");
    PutString("|     Firmware update by UART0(1:boot,2:update)       |\n");
    PutString("+-----------------------------------------------------+\n");
    ch = ReceiveBytes(0); /* block on waiting for any one character input from UART0 */
    switch(ch)
    {
    case '2':
        Uaddr=Get_Version(0);
        PutString("Update");
        PutMassage(Uaddr);
        UpdatedFirmware(Uaddr);
        break;
    default:
        break;
    }
    /* Set vector remap to APROM address AP_BOOT_ADDR0 or AP_BOOT_ADDR1   */
    FMC_SetVectorPageAddr(Get_Version(1));
    PutString("Boot");
    PutMassage(Get_Version(1));
    while((UART0->FIFOSTS & UART_FIFOSTS_TXEMPTY_Msk)==0);
    /* Change boot source as APROM                */
    FMC_SET_APROM_BOOT();
    /* Let CPU reset. Will boot from APROM.       */
    SYS->IPRST0 = SYS_IPRST0_CPURST_Msk;
    while(1);
}



/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/

