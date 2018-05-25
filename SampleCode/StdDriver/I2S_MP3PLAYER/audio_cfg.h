/**************************************************************************//**
 * @file     audio_cfg.h
 * @version  V1.00
 * @brief    M480 I2S Driver Sample Configuration Header File
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef AUDIO_CFG_H
#define AUDIO_CFG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mad.h"

struct mp3Header
{
    unsigned int sync : 11;
    unsigned int version : 2;
    unsigned int layer : 2;
    unsigned int protect : 1;
    unsigned int bitrate : 4;
    unsigned int samfreq : 2;
    unsigned int padding : 1;
    unsigned int private : 1;
    unsigned int channel : 2;
    unsigned int mode : 2;
    unsigned int copy : 1;
    unsigned int original : 1;
    unsigned int emphasis : 2;
};

struct AudioInfoObject
{
    unsigned int playFileSize;
    unsigned int mp3FileEndFlag;
    unsigned int mp3SampleRate;
    unsigned int mp3BitRate;
    unsigned int mp3Channel;
    unsigned int mp3PlayTime;
    unsigned int mp3Playing;
};

#define PLAY_MP3
#define PLAY_WAV

#define MAX_WAV_SIZE                (64*1024)
#define INPUT_BUFFER_SIZE           (4*1024)
#define PCM_BUFFER_SIZE             (8*1024)
#define OUTPUT_BUFFER_SIZE          MAX_WAV_SIZE                            /* Must be an integer multiple of 4. */
#define INPUT_BUFFER_SIZE_PLUS      (INPUT_BUFFER_SIZE + MAD_BUFFER_GUARD)

#define I2S0_TX_PDMA_CH     5
#define I2S1_TX_PDMA_CH     4

void NAU88L25_Setup(uint8_t nChannel);
void MP3Player(void);
signed int MP3FixedToShort(mad_fixed_t sample);
void NAU88L25_ConfigSampleRate(uint32_t u32SampleRate);
void PDMA_SC_ResetTXDescriptor(uint8_t id);
void add_mp3_list_to_html(void);
void MP3_ParseHeaderInfo(uint8_t nChannel);
int mp3CountV1L3Headers(unsigned char *pBytes, size_t size, uint8_t nChannel);
#endif

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
