/**************************************************************************//**
 * @file     Report.h
 * @version  V1.00
 * @brief    Nuvoton A.H.R.S Library header file
 *
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#ifndef _REPORT_H
#define _REPORT_H

#include <stdio.h>
#include "NuMicro.h"

#define REPORT_SENSORS_RAW        1
#define REPORT_HEART_SPEED        2

#define REPORT_FORMAT_TEXT        0
#define REPORT_FORMAT_BINARY      1

#define STREAM_START              1
#define STREAM_PAUSE              0

#define TIMER_LOG_CNT   100

extern float HeartFreq1[10];
extern uint32_t ADCData[TIMER_LOG_CNT];
extern uint32_t Time[10];
extern uint32_t HeartFreq[10];
extern char report_mode;
extern char report_format;
extern char stream_mode;
extern uint32_t g_u32ADCValue_ch14;
extern float HeartSpeed;
extern float HeartSpeed1;
void report_sensors(int16_t);
int Serial_available(UART_T*);
char Serial_read(UART_T*);
void Serial_write(UART_T*, char*, int);
#endif
