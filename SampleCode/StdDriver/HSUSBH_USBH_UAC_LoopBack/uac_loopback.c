/***************************************************************************//**
 * @file     usbd_audio.c
 * @brief    NuMicro series USBD audio sample file
 *
 * @copyright (C) 2013~2015 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/

/*!<Includes */
#include <string.h>
#include <stdio.h>

#include "NuMicro.h"
#include "usbh_lib.h"
#include "usbh_uac.h"


#define PCM_BUF_LEN            (192*24)     /* suggest 1K at least */


/* Global variables  */
volatile uint8_t g_u8RecEn = 0;
volatile uint8_t g_u8PlayEn = 0;

volatile int8_t   g_bMicIsMono = 0;

/* UAC audio in/out PCM buffer.  */
#ifdef __ICCARM__
#pragma data_alignment=32
uint8_t g_u8PcmBuf[PCM_BUF_LEN];
#else
uint8_t g_u8PcmBuf[PCM_BUF_LEN] __attribute__((aligned(4)));
#endif
volatile uint32_t g_UacRecPos = 0;          /* UAC record pointer of PCM buffer       */
volatile uint32_t g_UacPlayPos = 0;         /* UAC playback pointer of PCM buffer     */
volatile uint32_t g_UacRecCnt = 0;          /* Counter of UAC record data             */
volatile uint32_t g_UacPlayCnt = 0;         /* Counter UAC playback data              */


void ResetAudioLoopBack(void)
{
    memset(g_u8PcmBuf, 0, sizeof(g_u8PcmBuf));
    g_UacRecPos = 0;
    g_UacPlayPos = 0;
    g_UacRecCnt = 0;
    g_UacPlayCnt = 0;
    g_u8RecEn = 0;
    g_u8PlayEn = 0;
}


/**
 *  @brief  USB UAC audio-in data callback function.
 *          UAC driver deleivers an audio in data packet received from UAC device.
 *  @param[in] dev    Audio Class device
 *  @param[in] data   Audio in packet buffer
 *  @param[in] len    Length of audio in packet
 *  @return   UAC driver does not check this return value.
 */
int audio_in_callback(UAC_DEV_T *dev, uint8_t *data, int len)
{
    int        i, cp_len;
    uint16_t   *dptr, *bptr;

    if (g_bMicIsMono)
    {
        if (g_UacRecPos + len*2 >= PCM_BUF_LEN)
        {
            cp_len = (PCM_BUF_LEN - g_UacRecPos)/2;
        }
        else
        {
            cp_len = len;
        }

        dptr = (uint16_t *)data;
        bptr = (uint16_t *)&g_u8PcmBuf[g_UacRecPos];
        for (i = 0; i < cp_len; i+=2)
        {
            *bptr++ = *dptr;                /* 16-bit PCM data                            */
            *bptr++ = *dptr++;              /* duplicate PCM data                         */
        }

        g_UacRecPos = (g_UacRecPos + cp_len*2) % PCM_BUF_LEN;
        g_UacRecCnt += cp_len;
        len -= cp_len;

        if (len)
        {
            dptr = (uint16_t *)&data[cp_len];
            bptr = (uint16_t *)g_u8PcmBuf;
            for (i = 0; i < len; i+=2)
            {
                *bptr++ = *dptr;            /* 16-bit PCM data                            */
                *bptr++ = *dptr++;          /* duplicate PCM data                         */
            }
            g_UacRecPos = len*2;
            g_UacRecCnt += len;
        }
    }
    else
    {
        if (g_UacRecPos + len >= PCM_BUF_LEN)
        {
            cp_len = PCM_BUF_LEN - g_UacRecPos;
        }
        else
        {
            cp_len = len;
        }
        memcpy(&g_u8PcmBuf[g_UacRecPos], data, cp_len);

        g_UacRecPos = (g_UacRecPos + cp_len) % PCM_BUF_LEN;
        g_UacRecCnt += cp_len;
        len -= cp_len;

        if (len)
        {
            memcpy(&g_u8PcmBuf[0], &data[cp_len], len);
            g_UacRecPos = len;
            g_UacRecCnt += len;
        }
    }

    if ((g_u8PlayEn == 0) && (g_UacRecPos >= PCM_BUF_LEN/2))
    {
        g_UacPlayPos = g_UacPlayCnt = 0;
        g_u8PlayEn = 1;
    }

    return 0;
}


/**
 *  @brief  Audio-out data callback function.
 *          UAC driver requests user to move audio-out data into the specified address. The audio-out
 *          data will then be send to UAC device via isochronous-out pipe.
 *  @param[in] dev    Audio Class device
 *  @param[in] data   Application should move audio-out data into this buffer.
 *  @param[in] len    Maximum length of audio-out data can be moved.
 *  @return   Actual length of audio data moved.
 */
int audio_out_callback(UAC_DEV_T *dev, uint8_t *data, int len)
{
    int  cp_len;

    if (!g_u8PlayEn)
    {
        memset(data, 0, 192);
        g_UacPlayCnt += 192;
        return 192;
    }

    if (PCM_BUF_LEN - g_UacPlayPos < 192)
    {
        cp_len = PCM_BUF_LEN - g_UacPlayPos;
    }
    else
    {
        cp_len = 192;
    }

    memcpy(data, &g_u8PcmBuf[g_UacPlayPos], cp_len);
    g_UacPlayPos = (g_UacPlayPos + cp_len) % PCM_BUF_LEN;

    if (cp_len < 192)
    {
        memcpy(&data[cp_len], &g_u8PcmBuf[0], 192-cp_len);
        g_UacPlayPos = 192-cp_len;
    }
    g_UacPlayCnt += 192;

    return 192;   // for 48000 stero Hz
}


