/**************************************************************************//**
 * @file     Report.c
 * @version  V1.00
 * @brief    Nuvoton A.H.R.S Library
 *
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
/*================================================================================*
 *                                                                                *
 *            _    _ _____   _____   ______         _                             *
 *      /\   | |  | |  __ \ / ____| |  ____|       (_)                            *
 *     /  \  | |__| | |__) | (___   | |__ _   _ ___ _  ___  _ __                  *
 *    / /\ \ |  __  |  _  / \___ \  |  __| | | / __| |/ _ \| '_ \                 *
 *   / ____ \| |  | | | \ \ ____) | | |  | |_| \__ \ | (_) | | | |                *
 *  /_/    \_\_|  |_|_|  \_\_____/  |_|   \__,_|___/_|\___/|_| |_|                *
 *                                                                                *
 *                                                                                *
 * Nuvoton A.H.R.S Library for Cortex M4 Series                                   *
 *                                                                                *
 * Written by by T.L. Shen for Nuvoton Technology.                                *
 * tlshen@nuvoton.com/tzulan611126@gmail.com                                      *
 *                                                                                *
 *================================================================================*
 */
#include <stdio.h>
#include "NuMicro.h"
#include "Report.h"

float HeartFreq1[10];
uint32_t ADCData[TIMER_LOG_CNT] = {0};
uint32_t Time[10];
uint32_t HeartFreq[10];
char report_mode = REPORT_HEART_SPEED;
char report_format = REPORT_FORMAT_TEXT;
char stream_mode = STREAM_PAUSE;
char Start = '@';
float HeartSpeed = 0;
float HeartSpeed1 = 0;
int16_t Counter;

uint32_t g_u32ADCValue_ch14;

int kbnumbers(UART_T *uart)
{
    return ((uart->FIFOSTS>>8)&0x3f);
}
int Serial_available(UART_T *uart)
{
    return kbnumbers(uart);
}
char Serial_read(UART_T *uart)
{
    return (uart->DAT);
}
void Serial_write(UART_T *uart, char* id, int num)
{
    int i;
    for(i=0; i<num; i++)
    {
        while(uart->FIFOSTS & UART_FIFOSTS_TXFULL_Msk);
        uart->DAT = id[i];
    }
}

void report_sensor_raw(int16_t data)
{
    int16_t RawData;

    RawData = g_u32ADCValue_ch14;

    if (report_format == REPORT_FORMAT_BINARY)
    {
        Serial_write(UART0, (char*)&RawData, 2);
    }
    else if (report_format == REPORT_FORMAT_TEXT)
    {
        printf("%d\n",RawData);
    }
}

void report_heart_speed(int16_t data)
{
    int16_t SpeedData;

    SpeedData = (int16_t)HeartFreq1[2];

    if (report_format == REPORT_FORMAT_BINARY)
    {
        Serial_write(UART0, (char*)&SpeedData, 2);
    }
    else if (report_format == REPORT_FORMAT_TEXT)
    {
        printf("SpeedData:%d\n",SpeedData);
    }
}

void report_sensors(int16_t data)
{
    if(stream_mode==STREAM_PAUSE)
        return;

    if (report_mode == REPORT_SENSORS_RAW)
    {
        report_sensor_raw(data);
    }
    if (report_mode == REPORT_HEART_SPEED)
    {
        report_heart_speed(data);
    }
}

