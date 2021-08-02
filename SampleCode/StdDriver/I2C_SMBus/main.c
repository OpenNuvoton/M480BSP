/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * $Revision: 17 $
 * $Date: 15/09/02 10:04a $
 * @brief
 *           Show how to control SMBus interface and use SMBus protocol between Host and Slave.
 *
 * @note
 * Copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define SMBUS_ALERT_RESPONSE_ADDRESS 0x0C
#define SMBUS_DEFAULT_ADDRESS        0x61
#define ARP_COMMAND 0x01

/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
const uint8_t g_u8MasterAddr[4] = {0x15, 0x35, 0x55, 0x75};
const uint8_t g_u8SlaveAddr[4] = {0x18, 0x38, 0x58, 0x78};

uint32_t slave_buff_addr;
uint8_t g_u8SlvData[256];
uint8_t g_au8RxData[4];
uint8_t g_u8DeviceAddr;
uint8_t g_u8ARA_Addr;
uint8_t g_au8TxData[4];
uint8_t g_u8RxData;
uint8_t g_u8DataLen0;
uint8_t g_u8DataLen1;
uint8_t g_u8EndFlag = 0;
uint8_t g_u8SendPEC = 0;
uint8_t g_u8AlertInt0 = 0;
uint8_t g_u8AlertInt1 = 0;
uint8_t g_u8AlertAddrAck0 = 0;
uint8_t g_u8AlertAddrAck1 = 0;
uint8_t g_u8PECErr = 0;

typedef void (*I2C_FUNC)(uint32_t u32Status);

static volatile I2C_FUNC s_I2C0HandlerFn = NULL;
static volatile I2C_FUNC s_I2C1HandlerFn = NULL;


/*---------------------------------------------------------------------------------------------------------*/
/*  I2C0 IRQ Handler                                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
void I2C0_IRQHandler(void)
{
    uint32_t u32Status;

    u32Status = I2C_GET_STATUS(I2C0);
    /* Check Transmit byte done interrupt flag */
    if((I2C_SMBusGetStatus(I2C0) & I2C_BUSSTS_BCDONE_Msk) == I2C_BUSSTS_BCDONE_Msk)
    {
        I2C_SMBusClearInterruptFlag(I2C0, I2C_BUSSTS_BCDONE_Msk);
        //printf("I2C0 Byte Transmit Byte Done Interrupt !\n");
        return;
    }

    /* Occur receive PEC packet error */
    if((I2C_SMBusGetStatus(I2C0) & I2C_BUSSTS_PECERR_Msk) == I2C_BUSSTS_PECERR_Msk)
    {
        I2C_SMBusClearInterruptFlag(I2C0, I2C_BUSSTS_PECERR_Msk);
        //printf("I2C0 PEC Error Interrupt !\n");
        return;
    }

    /* Check Alert Interrupt when I2C0 is Host */
    if(((I2C_SMBusGetStatus(I2C0) & I2C_BUSSTS_ALERT_Msk) == I2C_BUSSTS_ALERT_Msk) &
            ((I2C0->BUSCTL & I2C_BUSCTL_BMHEN_Msk) == I2C_BUSCTL_BMHEN_Msk))
    {
        I2C_SMBusClearInterruptFlag(I2C0, I2C_BUSSTS_ALERT_Msk);
        //printf("I2C0 Alert Interrupt !\n");
        g_u8AlertInt0 = 1;
        return ;
    }

    if(I2C_GET_TIMEOUT_FLAG(I2C0))
    {
        /* Clear I2C0 Timeout Flag */
        I2C_ClearTimeoutFlag(I2C0);
    }
    else
    {
        if(s_I2C0HandlerFn != NULL)
            s_I2C0HandlerFn(u32Status);
    }
}

/*---------------------------------------------------------------------------------------------------------*/
/*  I2C1 IRQ Handler                                                                                       */
/*---------------------------------------------------------------------------------------------------------*/
void I2C1_IRQHandler(void)
{
    uint32_t u32Status;

    u32Status = I2C_GET_STATUS(I2C1);

    /* Check Transmit byte done interrupt flag */
    if((I2C_SMBusGetStatus(I2C1) & I2C_BUSSTS_BCDONE_Msk) == I2C_BUSSTS_BCDONE_Msk)
    {
        I2C_SMBusClearInterruptFlag(I2C1, I2C_BUSSTS_BCDONE_Msk);
        //printf("I2C1 Byte Receive Byte Done Interrupt !\n");
        return;
    }

    /* Occur receive PEC packet error */
    if((I2C_SMBusGetStatus(I2C1) & I2C_BUSSTS_PECERR_Msk) == I2C_BUSSTS_PECERR_Msk)
    {
        I2C_SMBusClearInterruptFlag(I2C1, I2C_BUSSTS_PECERR_Msk);
        //printf("I2C1 PEC Error Interrupt !\n");
        return;
    }

    /* Check Alert Interrupt when I2C1 is Host */
    if(((I2C_SMBusGetStatus(I2C1) & I2C_BUSSTS_ALERT_Msk) == I2C_BUSSTS_ALERT_Msk) &
            ((I2C1->BUSCTL & I2C_BUSCTL_BMHEN_Msk) == I2C_BUSCTL_BMHEN_Msk))
    {
        I2C_SMBusClearInterruptFlag(I2C1, I2C_BUSSTS_ALERT_Msk);
        //printf("I2C1 Alert Interrupt !\n");
        g_u8AlertInt1 = 1;
        return ;
    }

    if(I2C_GET_TIMEOUT_FLAG(I2C1))
    {
        /* Clear I2C1 Timeout Flag */
        I2C_ClearTimeoutFlag(I2C1);
    }
    else
    {
        if(s_I2C1HandlerFn != NULL)
            s_I2C1HandlerFn(u32Status);
    }
}

/*---------------------------------------------------------------------------------------------------------*/
/*  I2C Master Tx Callback Function                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
void I2C_MasterTx(uint32_t u32Status)
{
    if(u32Status == 0x08)                       /* START has been transmitted */
    {
        I2C_SET_DATA(I2C0, g_u8DeviceAddr << 1);     /* Write SLA+W to Register I2CDAT */
        I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
    }
    else if(u32Status == 0x18)                  /* SLA+W has been transmitted and ACK has been received */
    {
        I2C_SET_DATA(I2C0, g_au8TxData[g_u8DataLen0++]);
        I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
    }
    else if(u32Status == 0x20)                  /* SLA+W has been transmitted and NACK has been received */
    {
        I2C_STOP(I2C0);
        I2C_START(I2C0);
    }
    else if(u32Status == 0x28)                  /* DATA has been transmitted and ACK has been received */
    {
        if(g_u8DataLen0 != 3)
        {
            I2C_SET_DATA(I2C0, g_au8TxData[g_u8DataLen0++]);
            I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
        }
        else
        {
            if(g_u8SendPEC == 0)
            {
                g_u8SendPEC = 1;
                I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
            }
            else
            {
                I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STO_SI);
                g_u8EndFlag = 1;
            }
        }
    }
    else
    {
        /* TO DO */
        printf("Status 0x%x is NOT processed\n", u32Status);
    }
}

/*---------------------------------------------------------------------------------------------------------*/
/*  I2C Master Alert Callback Function                                                                     */
/*---------------------------------------------------------------------------------------------------------*/
void I2C_MasterAlert(uint32_t u32Status)
{
    if(u32Status == 0x08)                       /* START has been transmitted */
    {
        I2C_SET_DATA(I2C0, (g_u8DeviceAddr << 1) + 1);             /* Write SLA+R to Register I2CDAT */
        I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
    }
    else if(u32Status == 0x18)                  /* SLA+W has been transmitted and ACK has been received */
    {
        I2C_SET_DATA(I2C0, g_au8TxData[g_u8DataLen0++]);
        I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
    }
    else if(u32Status == 0x20)                  /* SLA+W has been transmitted and NACK has been received */
    {
        I2C_STOP(I2C0);
        I2C_START(I2C0);
    }
    else if(u32Status == 0x40)
    {
        I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI_AA);
    }
    else if(u32Status == 0x50)
    {
        if(g_u8DataLen0 == 0)
        {
            g_au8RxData[g_u8DataLen0] = (unsigned char)I2C_GET_DATA(I2C0);
            I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI_AA);
            g_u8DataLen0++;
        }
        else
        {
            g_au8RxData[g_u8DataLen0] = (unsigned char) I2C_GET_DATA(I2C0);
            I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STO_SI_AA);
            g_u8AlertAddrAck0 = 1;
        }
    }
    else if(u32Status == 0x28)                  /* DATA has been transmitted and ACK has been received */
    {
        if(g_u8DataLen0 != 3)
        {
            I2C_SET_DATA(I2C0, g_au8TxData[g_u8DataLen0++]);
            I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
        }
        else
        {
            if(g_u8SendPEC == 0)
            {
                g_u8SendPEC = 1;
                I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
            }
            else
            {
                I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STO_SI);
                g_u8EndFlag = 1;
            }
        }
    }
    else
    {
        /* TO DO */
        printf("Status 0x%x is NOT processed\n", u32Status);
    }
}

/*---------------------------------------------------------------------------------------------------------*/
/*  I2C Master Default Address and Acknowledge by Manual Callback Function                                 */
/*---------------------------------------------------------------------------------------------------------*/
void I2C_MasterDefaultAddrACKM(uint32_t u32Status)
{
    if(u32Status == 0x08)                            /* START has been transmitted */
    {
        I2C_SET_DATA(I2C0, g_u8DeviceAddr << 1);     /* Write SLA+W to Register I2CDAT */
        I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
    }
    else if(u32Status == 0x18)                       /* SLA+W has been transmitted and ACK has been received */
    {
        I2C_SET_DATA(I2C0, g_au8TxData[g_u8DataLen0++]);
        I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
    }
    else if(u32Status == 0x20)                       /* SLA+W has been transmitted and NACK has been received */
    {
        I2C_STOP(I2C0);
        I2C_START(I2C0);
    }
    else if(u32Status == 0x28)                       /* DATA has been transmitted and ACK has been received */
    {
        if(g_u8SendPEC == 0)
        {
            g_u8SendPEC = 1;
            I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
        }
        else
        {
            I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STO_SI);
            g_u8EndFlag = 1;
        }
    }
    else
    {
        /* TO DO */
        printf("Status 0x%x is NOT processed\n", u32Status);
    }
}
/*---------------------------------------------------------------------------------------------------------*/
/*  I2C Slave TRx Callback Function                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
void I2C_SlaveTRx(uint32_t u32Status)
{
    if(u32Status == 0x60)                       /* Own SLA+W has been receive; ACK has been return */
    {
        g_u8DataLen1 = 0;
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);
    }
    else if(u32Status == 0x80)                 /* Previously address with own SLA address
                                                   Data has been received; ACK has been returned*/
    {
        g_au8RxData[g_u8DataLen1] = (unsigned char)I2C_GET_DATA(I2C1);
        g_u8DataLen1++;

        if(g_u8DataLen1 == 2)
        {
            slave_buff_addr = (g_au8RxData[0] << 8) + g_au8RxData[1];
        }
        if(g_u8DataLen1 == 3)
        {
            g_u8SlvData[slave_buff_addr] = g_au8RxData[2];
        }
        if(g_u8DataLen1 == 4)
        {
            if(g_au8RxData[3] != I2C_SMBusGetPECValue(I2C1))
            {
                g_u8PECErr = 1;
            }
            g_u8DataLen1 = 0;
        }
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);
    }
    else if(u32Status == 0xA8)                  /* Own SLA+R has been receive; ACK has been return */
    {

        I2C_SET_DATA(I2C1, g_u8SlvData[slave_buff_addr]);
        slave_buff_addr++;
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);
    }
    else if(u32Status == 0xC0)                 /* Data byte or last data in I2CDAT has been transmitted
                                                   Not ACK has been received */
    {
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);
    }
    else if(u32Status == 0x88)                 /* Previously addressed with own SLA address; NOT ACK has
                                                   been returned */
    {
        g_u8DataLen1 = 0;
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);
    }
    else if(u32Status == 0xA0)                 /* A STOP or repeated START has been received while still
                                                   addressed as Slave/Receiver*/
    {
        g_u8DataLen1 = 0;
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);
    }
    else
    {
        /* TO DO */
        printf("Status 0x%x is NOT processed\n", u32Status);
    }
}

/*---------------------------------------------------------------------------------------------------------*/
/*  I2C Slave Alert Callback Function                                                                      */
/*---------------------------------------------------------------------------------------------------------*/
void I2C_SlaveAlert(uint32_t u32Status)
{
    if(u32Status == 0x60)                       /* Own SLA+W has been receive; ACK has been return */
    {
        g_u8DataLen1 = 0;
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);
    }
    else if(u32Status == 0x80)                 /* Previously address with own SLA address
                                                   Data has been received; ACK has been returned*/
    {
        g_au8RxData[g_u8DataLen1] = (unsigned char) I2C_GET_DATA(I2C1);
        g_u8DataLen1++;

        if(g_u8DataLen1 == 2)
        {
            slave_buff_addr = (g_au8RxData[0] << 8) + g_au8RxData[1];
        }
        if(g_u8DataLen1 == 3)
        {
            g_u8SlvData[slave_buff_addr] = g_au8RxData[2];

        }
        if(g_u8DataLen1 == 4)
        {
            if(g_au8RxData[3] != I2C_SMBusGetPECValue(I2C1))
            {
                g_u8PECErr = 1;
            }
            g_u8DataLen1 = 0;
        }
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);
    }
    else if(u32Status == 0xA8)                  /* Own SLA+R has been receive; ACK has been return */
    {
        I2C_SET_DATA(I2C1, g_u8SlaveAddr[0]);
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);
    }
    else if(u32Status == 0xC0)                 /* Data byte or last data in I2CDAT has been transmitted
                                                   Not ACK has been received */
    {
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);
    }
    else if(u32Status == 0x88)                 /* Previously addressed with own SLA address; NOT ACK has
                                                   been returned */
    {
        g_u8DataLen1 = 0;
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);
    }
    else if(u32Status == 0xA0)                 /* A STOP or repeated START has been received while still
                                                   addressed as Slave/Receiver*/
    {
        g_u8DataLen1 = 0;
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);
    }
    else if(u32Status == 0xB8)
    {
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);
    }
    else
    {
        /* TO DO */
        printf("Status 0x%x is NOT processed\n", u32Status);
    }
}

/*---------------------------------------------------------------------------------------------------------*/
/*  I2C Slave Default Address and Acknowledge by Manual Callback Function                                  */
/*---------------------------------------------------------------------------------------------------------*/
void I2C_SlaveDefaultAddrACKM(uint32_t u32Status)
{
    if(u32Status == 0x60)                       /* Own SLA+W has been receive; ACK has been return */
    {
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI);
    }
    else if(u32Status == 0xF0)
    {
        /* Enable ACKMEN & SLV in Receive Mode */
        g_au8RxData[g_u8DataLen1] = (unsigned char) I2C_GET_DATA(I2C1);
        g_u8DataLen1++;

        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);           //Acknowledge by Manual
    }
    else if(u32Status == 0x80)                 /* Previously address with own SLA address
                                                   Data has been received; ACK has been returned*/
    {
        g_au8RxData[g_u8DataLen1] = (unsigned char) I2C_GET_DATA(I2C1);
        g_u8DataLen1++;

        if(g_u8DataLen1 == 2)
        {
            if(g_au8RxData[1] != I2C_SMBusGetPECValue(I2C1))
            {
                g_u8PECErr = 1;
            }
            g_u8DataLen1 = 0;
        }
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);
    }
    else if(u32Status == 0xA8)                  /* Own SLA+R has been receive; ACK has been return */
    {
        I2C_SET_DATA(I2C1, g_u8SlvData[slave_buff_addr]);
        slave_buff_addr++;
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);
    }
    else if(u32Status == 0xC0)                 /* Data byte or last data in I2CDAT has been transmitted
                                                   Not ACK has been received */
    {
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);
    }
    else if(u32Status == 0x88)                 /* Previously addressed with own SLA address; NOT ACK has
                                                   been returned */
    {
        g_u8DataLen1 = 0;
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);
    }
    else if(u32Status == 0xA0)                 /* A STOP or repeated START has been received while still
                                                   addressed as Slave/Receiver*/
    {
        g_u8DataLen1 = 0;
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);
    }
    else
    {
        /* TO DO */
        printf("Status 0x%x is NOT processed\n", u32Status);
    }
}

void SYS_Init(void)
{
    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable external XTAL 12MHz clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for external XTAL clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(192000000);
    CLK->PCLKDIV = (CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2); // PCLK divider set 2

    /* Enable UART clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Enable I2C0 clock */
    CLK_EnableModuleClock(I2C0_MODULE);

    /* Enable I2C1 clock */
    CLK_EnableModuleClock(I2C1_MODULE);

    /* Select UART module clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));


    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock and cyclesPerUs automatically. */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Set I2C0 multi-function pins */
    SYS->GPA_MFPL = (SYS->GPA_MFPL & ~(SYS_GPA_MFPL_PA4MFP_Msk | SYS_GPA_MFPL_PA5MFP_Msk)) |
                    (SYS_GPA_MFPL_PA4MFP_I2C0_SDA | SYS_GPA_MFPL_PA5MFP_I2C0_SCL);
    SYS->GPA_MFPL = (SYS->GPA_MFPL & ~(SYS_GPA_MFPL_PA2MFP_Msk | SYS_GPA_MFPL_PA3MFP_Msk)) |
                    (SYS_GPA_MFPL_PA2MFP_I2C0_SMBSUS | SYS_GPA_MFPL_PA3MFP_I2C0_SMBAL);

    /* Set I2C1 multi-function pins */
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~(SYS_GPB_MFPH_PB10MFP_Msk | SYS_GPB_MFPH_PB11MFP_Msk)) |
                    (SYS_GPB_MFPH_PB10MFP_I2C1_SDA | SYS_GPB_MFPH_PB11MFP_I2C1_SCL);
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~(SYS_GPB_MFPH_PB8MFP_Msk | SYS_GPB_MFPH_PB9MFP_Msk)) |
                    (SYS_GPB_MFPH_PB8MFP_I2C1_SMBSUS | SYS_GPB_MFPH_PB9MFP_I2C1_SMBAL);

    /* I2C pin enable schmitt trigger */
    PA->SMTEN |= GPIO_SMTEN_SMTEN4_Msk | GPIO_SMTEN_SMTEN5_Msk;
    PB->SMTEN |= GPIO_SMTEN_SMTEN10_Msk | GPIO_SMTEN_SMTEN11_Msk;

}

void UART0_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset IP */
    SYS_ResetModule(UART0_RST);

    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0, 115200);
}

void I2C0_Init(void)
{
    /* Reset I2C0 */
    SYS_ResetModule(I2C0_RST);

    /* Open I2C module and set bus clock */
    I2C_Open(I2C0, 100000);

    /* Get I2C0 Bus Clock */
    printf("I2C0 clock %d Hz\n", I2C_GetBusClockFreq(I2C0));

    /* Enable I2C0 interrupt */
    I2C_EnableInt(I2C0);
    NVIC_EnableIRQ(I2C0_IRQn);
}

void I2C1_Init(void)
{
    /* Reset I2C1 */
    SYS_ResetModule(I2C1_RST);

    /* Open I2C module and set bus clock */
    I2C_Open(I2C1, 100000);

    /* Get I2C0 Bus Clock */
    printf("I2C1 clock %d Hz\n", I2C_GetBusClockFreq(I2C1));

    /* Set I2C1 4 Slave addresses */
    /* Slave address : 0x18 */
    I2C_SetSlaveAddr(I2C1, 0, g_u8SlaveAddr[0], 0);   /* Slave Address : 0x18 */
    /* Slave address : 0x38 */
    I2C_SetSlaveAddr(I2C1, 1, g_u8SlaveAddr[1], 0);   /* Slave Address : 0x38 */
    /* Slave address : 0x58 */
    I2C_SetSlaveAddr(I2C1, 2, g_u8SlaveAddr[2], 0);   /* Slave Address : 0x58 */
    /* Slave address : 0x78 */
    I2C_SetSlaveAddr(I2C1, 3, g_u8SlaveAddr[3], 0);   /* Slave Address : 0x78 */


    /* Set I2C1 4 Slave addresses mask bits*/
    /* Slave address mask Bits: 0x04 */
    I2C_SetSlaveAddrMask(I2C1, 0, 0x04);
    /* Slave address mask Bits: 0x02 */
    I2C_SetSlaveAddrMask(I2C1, 1, 0x02);
    /* Slave address mask Bits: 0x04 */
    I2C_SetSlaveAddrMask(I2C1, 2, 0x04);
    /* Slave address mask Bits: 0x02 */
    I2C_SetSlaveAddrMask(I2C1, 3, 0x02);

    /* Enable I2C1 interrupt */
    I2C_EnableInt(I2C1);
    NVIC_EnableIRQ(I2C1_IRQn);
}

void I2C0_Close(void)
{
    /* Disable I2C0 interrupt and clear corresponding NVIC bit */
    I2C_DisableInt(I2C0);
    NVIC_DisableIRQ(I2C0_IRQn);

    /* Disable I2C0 and close I2C0 clock */
    I2C_Close(I2C0);
    CLK_DisableModuleClock(I2C0_MODULE);

}

void I2C1_Close(void)
{
    /* Disable I2C1 interrupt and clear corresponding NVIC bit */
    I2C_DisableInt(I2C1);
    NVIC_DisableIRQ(I2C1_IRQn);

    /* Disable I2C1 and close I2C1 clock */
    I2C_Close(I2C1);
    CLK_DisableModuleClock(I2C1_MODULE);
}

int32_t SMBusSendByteTest(uint8_t slvaddr)
{
    uint32_t i;

    g_u8DeviceAddr = slvaddr;

    for(i = 0; i < 0x100; i++)
    {
        /* Init transmission bytes */
        g_au8TxData[0] = (uint8_t)((i & 0xFF00) >> 8);
        g_au8TxData[1] = (uint8_t)(i & 0x00FF);
        g_au8TxData[2] = (uint8_t)(g_au8TxData[1] + 3);

        g_u8DataLen0 = 0;
        g_u8EndFlag = 0;
        g_u8SendPEC = 0;

        /* I2C0 function to write data to slave */
        s_I2C0HandlerFn = (I2C_FUNC)I2C_MasterTx;

        /* I2C0 as master sends START signal */
        I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA);

        /* Wait I2C0 transmit finish */
        while(g_u8EndFlag == 0);
        g_u8EndFlag = 0;

        if(g_u8PECErr)
        {
            printf("PEC Check Error !\n");
            while(1);
        }
    }
    return 0;
}

int32_t SMBusAlertTest(uint8_t slvaddr)
{
    g_u8DeviceAddr = slvaddr;

    /* I2C function to Send Alert Response Address to bus */
    s_I2C0HandlerFn = (I2C_FUNC)I2C_MasterAlert;

    /* I2C0 Send Start condition */
    I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA);

    /* Init receive data index */
    g_u8DataLen0 = 0;

    /* Waiting for Get Alert Address*/
    while(g_u8AlertAddrAck0 == 0);
    g_u8AlertAddrAck0 = 0;

    if(g_u8PECErr)
    {
        printf("PEC Check Error !\n");
        while(1);
    }

    return 0;
}

int32_t SMBusDefaultAddressTest(uint8_t slvaddr)
{
    g_u8DeviceAddr = slvaddr;

    /* Set Transmission ARP command */
    g_au8TxData[0] = ARP_COMMAND;

    g_u8DataLen0 = 0;
    g_u8DataLen1 = 0;
    g_u8EndFlag = 0;
    g_u8SendPEC = 0;

    /* I2C0 function to write data to slave */
    s_I2C0HandlerFn = (I2C_FUNC)I2C_MasterDefaultAddrACKM;

    /* I2C0 as master sends START signal */
    I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA);

    /* Wait I2C0 transmit finish */
    while(g_u8EndFlag == 0);
    g_u8EndFlag = 0;

    if(g_u8PECErr)
    {
        printf("PEC Check Error !\n");
        while(1);
    }

    printf("\n");
    printf("Master Sends ARP Command(0x01) to Slave (0x%X) Test OK\n", slvaddr);
    return 0;
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{
    uint32_t i, ch = 0;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();


    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART0 for printf */
    UART0_Init();

    while(ch != 0x30)
    {
        /*
            This sample code sets I2C bus clock to 100kHz. Then, Master accesses Slave with Byte Write
            and Byte Read operations, and check if the read data is equal to the programmed data.
        */
        printf("\n");
        printf("+-------------------------------------------------------+\n");
        printf("|  M480 I2C SMBUS Driver Sample Code                    |\n");
        printf("|                                                       |\n");
        printf("| I2C Master (I2C0) <---> I2C Slave(I2C1)               |\n");
        printf("+-------------------------------------------------------+\n");

        printf("Configure I2C0 as master and I2C1 as a slave.\n");
        printf("\n");

        /* Init I2C0 */
        I2C0_Init();

        /* Init I2C1 */
        I2C1_Init();

        /* I2C1 enter no address SLV mode */
        I2C_SET_CONTROL_REG(I2C1, I2C_CTL_SI_AA);

        printf("\n");
        printf("I2C Slave Mode is Running.\n");
        for(i = 0; i < 0x100; i++)
        {
            g_u8SlvData[i] = 0;
        }

        printf("\n");
        printf("[1] SMBus Send Bytes Protocol with PEC Test\n");
        printf("[2] SMBus Alert Function Test\n");
        printf("[3] Simple ARP and ACK Control by Manual Test\n");
        printf("[0] Exit\n");
        ch = getchar();
        if(ch == '1')
        {
            /* I2C0 Bus Management enable */
            I2C_SMBusOpen(I2C0, I2C_SMBH_ENABLE);

            /* I2C0 Bus PEC Check and transmit enable */
            I2C_SMBusPECTxEnable(I2C0, I2C_PECTX_ENABLE);

            /* I2C1 Bus Management init */
            I2C_SMBusOpen(I2C1, I2C_SMBD_ENABLE);

            /* I2C1 Bus PEC check enable */
            I2C_SMBusPECTxEnable(I2C1, I2C_PECTX_DISABLE);

            /* Set I2C0 Payload bytes */
            I2C_SMBusSetPacketByteCount(I2C0, 4);            // I2C0: 1byte address + 3byte data

            /* Set I2C1 Payload bytes */
            I2C_SMBusSetPacketByteCount(I2C1, 4);            // I2C1: 1byte address + 3byte data

            g_u8PECErr = 0;

            /* I2C function to Slave receive/transmit data */
            s_I2C1HandlerFn = I2C_SlaveTRx;

            /* Access Slave with no address mask */
            printf("\n");
            printf(" == SMBus Send Bytes Protocol test ==\n");

            /* SMBus send byte protocol test*/
            SMBusSendByteTest(g_u8SlaveAddr[0]);

            printf("\n");
            printf("SMBus transmit data done.\n");
        }
        else if(ch == '2')
        {
            /* I2C0 Bus Management Enable */
            I2C_SMBusOpen(I2C0, I2C_SMBH_ENABLE);

            /* I2C0 Bus PEC Check and transmit Enable */
            I2C_SMBusPECTxEnable(I2C0, I2C_PECTX_DISABLE);

            /* I2C1 Bus Management init */
            I2C_SMBusOpen(I2C1, I2C_SMBD_ENABLE);

            /* I2C1 Bus PEC Check enable */
            I2C_SMBusPECTxEnable(I2C1, I2C_PECTX_ENABLE);

            /* Set I2C0 Payload bytes */
            I2C_SMBusSetPacketByteCount(I2C0, 2);            // I2C0: 1byte address + 1byte data

            /* Set I2C1 Payload bytes */
            I2C_SMBusSetPacketByteCount(I2C1, 2);            // I2C1: 1byte address + 1byte data

            /* Alert pin support if BMHEN(I2C0->BUSCTL[4]) = 0 */
            I2C_SMBUS_ENABLE_ALERT(I2C0);

            /* Enable Host SUSCON pin function and output Hi */
            I2C_SMBUS_SET_SUSCON_OUT(I2C0);
            I2C_SMBUS_SET_SUSCON_HIGH(I2C0);

            /* Release Slave Alert pin to Hi */
            I2C_SMBUS_DISABLE_ALERT(I2C1);

            /* Set Slave SUSCON pin is Input */
            I2C_SMBUS_SET_SUSCON_IN(I2C1);

            g_u8PECErr = 0;

            /* I2C function to Slave for receive/transmit data */
            s_I2C1HandlerFn = I2C_SlaveAlert;

            /* Access Slave with no address mask */
            printf("\n");
            printf(" == SMBus Alert Function Test ==\n");


            /* I2C1 Slave has a Alert request, pull Alert Pin to Lo */
            I2C_SMBUS_ENABLE_ALERT(I2C1);

            printf("\n");
            printf("I2C1 has Alert Request and Alert Pin Pull Lo. \n");

            /* Wait I2C0 get Alert interrupt */
            while(g_u8AlertInt0 == 0);

            /* I2C0 Get Alert Request */
            g_u8AlertInt0 = 0;
            printf("I2C0 Get Alert Interrupt Request\n");

            /* I2C0 Send Alert Response Address(ARA) to I2C bus */
            SMBusAlertTest(SMBUS_ALERT_RESPONSE_ADDRESS);

            /* Printf the Alert Slave address */
            printf("\n");
            printf("Get Alert Address 0x%X test OK.\n", g_au8RxData[0]);

            /* Show I2C1 SUSCON pin state before I2C0 pull Lo */
            printf("\n");
            printf("I2C1 SUSCON Pin state is %d\n", (int)((I2C1->BUSSTS & I2C_BUSSTS_SCTLDIN_Msk) >> 4));

            /* Output I2C0 SUSCON pin Low */
            I2C_SMBUS_SET_SUSCON_LOW(I2C0);
            printf("I2C0 SUSCON Pin output Lo\n");

            /* Show I2C1 SUSCON pin state after I2C0 pull Lo */
            printf("\n");
            printf("I2C1 SUSCON Pin state change to %d\n", (int)((I2C1->BUSSTS & I2C_BUSSTS_SCTLDIN_Msk) >> 4));

            printf("\n");
            printf("SMBus Alert Test Done\n");
        }
        else if(ch == '3')
        {
            /* I2C0 Bus management enable */
            I2C_SMBusOpen(I2C0, I2C_SMBH_ENABLE);

            /* I2C0 Bus PEC check and transmit enable */
            I2C_SMBusPECTxEnable(I2C0, I2C_PECTX_ENABLE);

            /* I2C1 Bus Management init */
            I2C_SMBusOpen(I2C1, I2C_SMBD_ENABLE);

            /* I2C1 Bus PEC check enable */
            I2C_SMBusPECTxEnable(I2C1, I2C_PECTX_DISABLE);

            /* I2C1 Acknowledge by Manual enable */
            I2C_SMBUS_ACK_MANUAL(I2C1);

            /* Set I2C0 Payload bytes */
            I2C_SMBusSetPacketByteCount(I2C0, 2);            // I2C0: 1byte address + 1byte data

            /* Set I2C1 Payload bytes */
            I2C_SMBusSetPacketByteCount(I2C1, 2);            // I2C1: 1byte address + 1byte data

            g_u8PECErr = 0;

            /* I2C function to Slave receive/transmit data */
            s_I2C1HandlerFn = I2C_SlaveDefaultAddrACKM;

            printf("\n");
            printf("== Simple ARP and Acknowledge by Manual Test ==\n");

            /* I2C0 sends Default Address and ARP Command (0x01) to Slave */
            SMBusDefaultAddressTest(SMBUS_DEFAULT_ADDRESS);

            /* Show I2C1 get ARP command from  I2C0 */
            printf("\n");
            printf("Slave Get ARP Command is 0x%X\n", g_au8RxData[0]);

            /* Check Slave get command */
            printf("\n");
            if(g_au8RxData[0] != ARP_COMMAND)
            {
                printf("Get Wrong ARP Command, Please Check again !\n");
            }
            else
            {
                printf("Default Address and Acknowledge by Manual test OK.\n");
            }
        }
    }

    s_I2C0HandlerFn = NULL;
    s_I2C1HandlerFn = NULL;

    printf("SMBus Test Exit\n");

    /* Close I2C0 */
    I2C0_Close();

    /* Close I2C1 */
    I2C1_Close();

    while(1);
}
