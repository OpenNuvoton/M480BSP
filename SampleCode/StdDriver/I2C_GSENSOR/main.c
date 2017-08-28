/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * $Revision: 5 $
 * $Date: 14/05/30 6:00p $
 * @brief    Read G-sensor (DMARD08) data via I2C interface
 *
 * @note
 * Copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "NuMicro.h"

#define PLL_CLOCK           192000000

#define DMARD05_I2C_SLAVE_ADDR 0x38  //I2C slave address

//Start register address for T, X, Y, Z
#define DMARD05_T_REG_START_ADDRESS 0x00
#define DMARD05_X_REG_START_ADDRESS 0x02
#define DMARD05_Y_REG_START_ADDRESS 0x04
#define DMARD05_Z_REG_START_ADDRESS 0x06

// Read value from DMARD08 via I2C
void Multi_Read_TXYZ(uint8_t u8RegAddr, uint16_t *u16Data)
{
    uint16_t volatile temp0, temp1;

    I2C_START(I2C0);
    I2C_WAIT_READY(I2C0);

    I2C_SET_DATA(I2C0, DMARD05_I2C_SLAVE_ADDR);
    I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
    I2C_WAIT_READY(I2C0);

    I2C_SET_DATA(I2C0, u8RegAddr);
    I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
    I2C_WAIT_READY(I2C0);

    I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA_SI);
    I2C_WAIT_READY(I2C0);

    I2C_SET_DATA(I2C0, (DMARD05_I2C_SLAVE_ADDR) | 1);
    I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
    I2C_WAIT_READY(I2C0);

    // T
    I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA_SI_AA);
    I2C_WAIT_READY(I2C0);
    temp0 = I2C_GET_DATA(I2C0);

    I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA_SI_AA);
    I2C_WAIT_READY(I2C0);
    temp1 = I2C_GET_DATA(I2C0);
    *(u16Data) = (temp0 << 3) | temp1;

    // X
    I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA_SI_AA);
    I2C_WAIT_READY(I2C0);
    temp0 = I2C_GET_DATA(I2C0);

    I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA_SI_AA);
    I2C_WAIT_READY(I2C0);
    temp1 = I2C_GET_DATA(I2C0);
    *(u16Data+1) = (temp0 << 3) | temp1;

    // Y
    I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA_SI_AA);
    I2C_WAIT_READY(I2C0);
    temp0 = I2C_GET_DATA(I2C0);

    I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA_SI_AA);
    I2C_WAIT_READY(I2C0);
    temp1 = I2C_GET_DATA(I2C0);
    *(u16Data+2) = (temp0 << 3) | temp1;

    // Z
    I2C_SET_CONTROL_REG(I2C0, I2C_CTL_STA_SI_AA);
    I2C_WAIT_READY(I2C0);
    temp0 = I2C_GET_DATA(I2C0);

    I2C_SET_CONTROL_REG(I2C0, I2C_CTL_SI);
    I2C_WAIT_READY(I2C0);
    temp1 = I2C_GET_DATA(I2C0);
    *(u16Data+3) = (temp0 << 3) | temp1;

    I2C_STOP(I2C0);
}

void SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/

    /* Enable external XTAL 12MHz clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for external XTAL clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(192000000);
    CLK->PCLKDIV = (CLK_PCLKDIV_PCLK0DIV2 | CLK_PCLKDIV_PCLK1DIV2); // PCLK divider set 2

    /* Enable UART clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Enable I2C0 clock */
    CLK_EnableModuleClock(I2C0_MODULE);

    /* Select UART clock source from HXT */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock and cyclesPerUs automatically. */
    SystemCoreClockUpdate();

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Set PD multi-function pins for UART0 RXD and TXD */
    SYS->GPD_MFPL &= ~(SYS_GPD_MFPL_PD2MFP_Msk | SYS_GPD_MFPL_PD3MFP_Msk);
    SYS->GPD_MFPL |= (SYS_GPD_MFPL_PD2MFP_UART0_RXD | SYS_GPD_MFPL_PD3MFP_UART0_TXD);

    /* Set I2C0 multi-function pins */
    SYS->GPA_MFPL = (SYS->GPA_MFPL & ~(SYS_GPA_MFPL_PA4MFP_Msk | SYS_GPA_MFPL_PA5MFP_Msk)) |
                    (SYS_GPA_MFPL_PA4MFP_I2C0_SDA | SYS_GPA_MFPL_PA5MFP_I2C0_SCL);

    /* I2C clock pin enable schmitt trigger */
    PA->SMTEN |= GPIO_SMTEN_SMTEN5_Msk;
}

void I2C0_Init(void)
{
    /* Open I2C0 and set clock to 100k */
    I2C_Open(I2C0, 100000);

    /* Set I2C0 4 Slave Addresses */
    I2C_SetSlaveAddr(I2C0, 0, 0x15, I2C_GCMODE_DISABLE);   /* Slave Address : 0x15 */
    I2C_SetSlaveAddr(I2C0, 1, 0x35, I2C_GCMODE_DISABLE);   /* Slave Address : 0x35 */
    I2C_SetSlaveAddr(I2C0, 2, 0x55, I2C_GCMODE_DISABLE);   /* Slave Address : 0x55 */
    I2C_SetSlaveAddr(I2C0, 3, 0x75, I2C_GCMODE_DISABLE);   /* Slave Address : 0x75 */
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main (void)
{
    uint16_t buffer[4]= {0x00,0x00,0x00,0x00};
    int16_t temp, x, y, z;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Init UART to 115200-8n1 for print message */
    UART_Open(UART0, 115200);

    /* Init I2C0 to access GSensor */
    I2C0_Init();

    while(1) {
        Multi_Read_TXYZ(DMARD05_T_REG_START_ADDRESS, buffer);

        if(buffer[0] & 0x400)
            temp = (int16_t)(0xF800 | buffer[0]);
        else
            temp = (int16_t)(buffer[0]);

        printf("[H********G-Sensor Status*********\n");
        printf("[Temperature] \n");
        printf(" %.2f 'C\n", (float)temp/(float)16 + (float)25);

        printf("\n[Acceleration] \n");

        if(buffer[1] & 0x400)
            x = (int16_t)(0xF800 | buffer[1]);
        else
            x = (int16_t)(buffer[1]);

        if(buffer[2] & 0x400)
            y = (int16_t)(0xF800 | buffer[2]);
        else
            y = (int16_t)(buffer[2]);

        if(buffer[3] & 0x400)
            z = (int16_t)(0xF800 | buffer[3]);
        else
            z = (int16_t)(buffer[3]);

        printf(" (%.3fg, %.3fg, %.3fg)\n", (float)x/(float)256, (float)y/(float)256, (float)z/(float)256);
        printf("********************************\n");
    }
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
