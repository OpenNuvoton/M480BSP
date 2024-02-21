/**************************************************************************//**
 * @file     wavplayer.c
 * @version  V1.00
 * @brief    M480 Wave file audio player
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NuMicro.h"

#include "config.h"

#include "diskio.h"
#include "ff.h"

/*
 * This is perhaps the simplest example use of the MAD high-level API.
 * Standard input is mapped into memory via mmap(), then the high-level API
 * is invoked with three callbacks: input, output, and error. The output
 * callback converts MAD's high-resolution PCM samples to 16 bits, then
 * writes them to standard output in little-endian, stereo-interleaved
 * format.
 */

FIL    wavFileObject;
size_t ReturnSize;

signed int aPCMBuffer[2][PCM_BUFFER_SIZE];
volatile uint8_t aPCMBuffer_Full[2]= {0,0};
volatile uint8_t u8PCMBuffer_Playing=0;
uint32_t aWavHeader[11];

extern uint8_t bAudioPlaying;

void WAVPlayer(void)
{
    FRESULT res;
    uint8_t u8PCMBufferTargetIdx = 0;
    uint32_t u32WavSamplingRate;

    res = f_open(&wavFileObject, "0:\\test.wav", FA_OPEN_EXISTING | FA_READ);       //USBH:0 , SD0: 1
    if (res != FR_OK)
    {
        printf("Open file error!\n");
        return;
    }

    // read sampling rate from WAV header
    memset(aWavHeader, 0, sizeof(aWavHeader));
    f_read(&wavFileObject, aWavHeader, 44, &ReturnSize);
    u32WavSamplingRate = aWavHeader[6];

    /* Configure NAU88L25 to specific sample rate */
    NAU88L25_ConfigSampleRate(u32WavSamplingRate);
    printf("wav: sampling rate=%d\n", u32WavSamplingRate);

    /* Set MCLK and enable MCLK */
    I2S_EnableMCLK(I2S0, 12000000);
    I2S0->CTL0 |= I2S_CTL0_ORDER_Msk;

    while(1)
    {
        if((aPCMBuffer_Full[0] == 1) && (aPCMBuffer_Full[1] == 1 ))         //all buffers are full, wait
        {
            if(!bAudioPlaying)
            {
                bAudioPlaying = 1;
                I2S_ENABLE_TXDMA(I2S0);
                I2S_ENABLE_TX(I2S0);
                printf("Start Playing ...\n");
            }

            while((aPCMBuffer_Full[0] == 1) && (aPCMBuffer_Full[1] == 1));
            //printf(".");
        }

        res = f_read(&wavFileObject, &aPCMBuffer[u8PCMBufferTargetIdx][0], PCM_BUFFER_SIZE*4, &ReturnSize);
        if (ReturnSize < PCM_BUFFER_SIZE*4)
            memset(&aPCMBuffer[u8PCMBufferTargetIdx][ReturnSize], 0, PCM_BUFFER_SIZE*4 - ReturnSize);

        if(f_eof(&wavFileObject) && (ReturnSize == 0))
            break;
        aPCMBuffer_Full[u8PCMBufferTargetIdx] = 1;

        if(bAudioPlaying)
        {
            if(aPCMBuffer_Full[u8PCMBufferTargetIdx^1] == 1)
                while(aPCMBuffer_Full[u8PCMBufferTargetIdx^1]);
        }

        u8PCMBufferTargetIdx ^= 1;

        //printf("change to ==>%d\n", u8PCMBufferTargetIdx);
    }

    printf("Done..\n");
    I2S_DISABLE_TX(I2S0);
    I2S_DISABLE_TXDMA(I2S0);
    f_close(&wavFileObject);
    bAudioPlaying = 0;
    aPCMBuffer_Full[0] = 0;
    aPCMBuffer_Full[1] = 0; 
}

