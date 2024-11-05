/***************************************************************************//**
 * @file     main.c
 * @brief    ISP tool main function
 * @version  0x32
 * @date     14, June, 2017
 *
 * @note
 * Copyright (C) 2017-2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"

#define V6M_AIRCR_VECTKEY_DATA            0x05FA0000UL
#define V6M_AIRCR_SYSRESETREQ             0x00000004UL
#define CAN_BAUD_RATE                     500000
#define Master_ISP_ID                     0x487
#define Device0_ISP_ID                    0x784
#define CAN_ISP_DtatLength                0x08
#define CAN_RETRY_COUNTS                  0x1fffffff

#define CMD_READ_CONFIG                   0xA2000000
#define CMD_RUN_APROM                     0xAB000000
#define CMD_GET_DEVICEID                  0xB1000000

/*---------------------------------------------------------------------------*/
/*  Function Declare                                                         */
/*---------------------------------------------------------------------------*/
extern char GetChar(void);

/* Declare a CAN message structure */
typedef struct
{
    uint32_t  Address;
    uint32_t  Data;
} STR_CANMSG_ISP;

STR_CANMSG_T rrMsg;
volatile uint8_t u8CAN_PackageFlag = 0, u8CAN_AckFlag = 0;
uint32_t Chip_EndAddress = 0;

/*---------------------------------------------------------------------------------------------------------*/
/* ISR to handle CAN interrupt event                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
void CAN_MsgInterrupt(CAN_T *tCAN, uint32_t u32IIDR)
{
    if (u32IIDR == 1)
    {
        CAN_Receive(tCAN, 0, &rrMsg);
        u8CAN_PackageFlag = 1;
    }
}

/*---------------------------------------------------------------------------------------------------------*/
/* CAN1 interrupt handler                                                                                  */
/*---------------------------------------------------------------------------------------------------------*/
void CAN1_IRQHandler(void)
{
    uint32_t u8IIDRstatus;
    u8IIDRstatus = CAN1->IIDR;

    if (u8IIDRstatus == 0x00008000)       /* Check Status Interrupt Flag (Error status Int and Status change Int) */
    {
        /**************************/
        /* Status Change interrupt*/
        /**************************/
        if (CAN1->STATUS & CAN_STATUS_RXOK_Msk)
        {
            CAN1->STATUS &= ~CAN_STATUS_RXOK_Msk;   /* Clear RxOK status*/
        }

        if (CAN1->STATUS & CAN_STATUS_TXOK_Msk)
        {
            CAN1->STATUS &= ~CAN_STATUS_TXOK_Msk;    /* Clear TxOK status*/
            u8CAN_AckFlag = 0;
        }
    }
    else if (u8IIDRstatus != 0)
    {
        CAN_MsgInterrupt(CAN1, u8IIDRstatus);
        CAN_CLR_INT_PENDING_BIT(CAN1, (u8IIDRstatus - 1)); /* Clear Interrupt Pending */
    }
}

#define PLLCON_SETTING          CLK_PLLCTL_160MHz_HIRC
#define PLL_CLOCK               160000000
#define HCLK_DIV                        1

#define GPIO_SETMODE(port, pin, u32Mode) port->MODE = (port->MODE & ~(0x3ul << (pin << 1))) | (u32Mode << (pin << 1));

void SYS_Init(void)
{
    /* Enable Internal and External RC clock */
    CLK->PWRCTL |= CLK_PWRCTL_HIRCEN_Msk | CLK_PWRCTL_HXTEN_Msk;

    /* Waiting for Internal RC clock ready */
    while (!(CLK->STATUS & CLK_STATUS_HIRCSTB_Msk));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK->PLLCTL = PLLCON_SETTING;

    while (!(CLK->STATUS & CLK_STATUS_PLLSTB_Msk));

    CLK->CLKSEL0 = (CLK->CLKSEL0 & (~CLK_CLKSEL0_HCLKSEL_Msk)) | CLK_CLKSEL0_HCLKSEL_PLL;
    CLK->CLKDIV0 &= ~CLK_CLKDIV0_HCLKDIV_Msk;
    CLK->CLKDIV0 |= CLK_CLKDIV0_HCLK(HCLK_DIV);
    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate PllClock, SystemCoreClock and CycylesPerUs automatically. */
    //SystemCoreClockUpdate();
    PllClock        = PLL_CLOCK;                        // PLL
    SystemCoreClock = PLL_CLOCK / HCLK_DIV;             // HCLK
    CyclesPerUs     = SystemCoreClock / 1000000;  // For SYS_SysTickDelay()
}

/*----------------------------------------------------------------------------*/
/*  Tx Msg by Normal Mode Function (With Message RAM)                    */
/*----------------------------------------------------------------------------*/
void CAN_Package_ACK(CAN_T *tCAN)
{
    STR_CANMSG_T tMsg;
    u8CAN_AckFlag = 1;
    /* Send a 11-bit Standard Identifier message */
    tMsg.FrameType = CAN_DATA_FRAME;
    tMsg.IdType    = CAN_STD_ID;
    tMsg.Id        = Device0_ISP_ID;
    tMsg.DLC       = CAN_ISP_DtatLength;
    memcpy(&tMsg.Data, &rrMsg.Data, 8);

    if (CAN_Transmit(tCAN, MSG(5), &tMsg) == FALSE)   // Configure Msg RAM and send the Msg in the RAM
    {
        return;
    }

    while (u8CAN_AckFlag);
}

void CAN_Init(void)
{
    /* Enable CAN1 module clock */
    CLK->APBCLK0 |= CLK_APBCLK0_CAN1CKEN_Msk;
    /* Set PC multi-function pins for CAN1 RXD(PC.9) and TXD(PC.10) */
    SYS->GPC_MFPH = (SYS->GPC_MFPH & ~(SYS_GPC_MFPH_PC9MFP_Msk | SYS_GPC_MFPH_PC10MFP_Msk)) |
                    (SYS_GPC_MFPH_PC9MFP_CAN1_RXD | SYS_GPC_MFPH_PC10MFP_CAN1_TXD);
    /* Set CAN transceiver to high speed mode */
    GPIO_SETMODE(PC, 11, GPIO_MODE_OUTPUT);
    PC11 = 0;
    CAN_Open(CAN1, CAN_BAUD_RATE, CAN_NORMAL_MODE);
    CAN_EnableInt(CAN1, (CAN_CON_IE_Msk | CAN_CON_SIE_Msk | CAN_CON_EIE_Msk));
    NVIC_SetPriority(CAN1_IRQn, (1 << __NVIC_PRIO_BITS) - 2);
    NVIC_EnableIRQ(CAN1_IRQn);
    /* Set CAN reveive message */
    CAN_SetRxMsg(CAN1, MSG(0), CAN_STD_ID, Master_ISP_ID);
}

/*---------------------------------------------------------------------------------------------------------*/
/* MAIN function                                                                                           */
/*---------------------------------------------------------------------------------------------------------*/
int main(void)
{
    uint32_t  Address, Data;
    /* Unlock protected registers */
    SYS_UnlockReg();
    /* Init System, IP clock and multi-function I/O */
    SYS_Init();
    /* Enable FMC ISP function */
    FMC_Open();
    FMC_ENABLE_AP_UPDATE();
    FMC_ENABLE_CFG_UPDATE();
    /* Init CAN port */
    CAN_Init();
    SysTick->LOAD = 300000 * CyclesPerUs;
    SysTick->VAL   = (0x00);
    SysTick->CTRL = SysTick->CTRL | SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

    while (1)
    {
        if (u8CAN_PackageFlag == 1)
        {
            break;
        }

        if (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk)
        {
            goto _APROM;
        }
    }

    /* stat update program */
    while (1)
    {
        if (u8CAN_PackageFlag)
        {
            u8CAN_PackageFlag = 0;
            Address = inpw(&rrMsg.Data);
            Data = inpw(&rrMsg.Data[4]);

            if (Address == CMD_GET_DEVICEID)
            {
                outpw(&rrMsg.Data[4], SYS->PDID);
            }
            else if (Address == CMD_READ_CONFIG)
            {
                outpw(&rrMsg.Data[4], FMC_Read(Data));
            }
            else if (Address == CMD_RUN_APROM)
            {
                break;
            }
            else
            {
                if ((Address % FMC_FLASH_PAGE_SIZE) == 0)
                {
                    FMC_Erase(Address);
                }

                FMC_Write(Address, Data);         //program ROM
                Data = FMC_Read(Address);
                memcpy(&rrMsg.Data[4], &Data, 4); //update data
            }

            CAN_Package_ACK(CAN1);            //send CAN ISP Package (ACK)
        }
    }

_APROM:
    SYS->RSTSTS = (SYS_RSTSTS_PORF_Msk | SYS_RSTSTS_PINRF_Msk);
    FMC->ISPCTL &= ~(FMC_ISPCTL_ISPEN_Msk | FMC_ISPCTL_BS_Msk);
    SCB->AIRCR = (V6M_AIRCR_VECTKEY_DATA | V6M_AIRCR_SYSRESETREQ);

    /* Trap the CPU */
    while (1);
}

