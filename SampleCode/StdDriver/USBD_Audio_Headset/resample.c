/******************************************************************************
 * @file     resample.c
 * @version  V0.10
 * @brief
 *           Audio Codec Resample.
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "usbd_audio.h"

#if 1
/* fixed sample rate to 48K */
const SR_T srt[] = {
    { 2731, 16000, 48000, 16},   /* For Play */
    { 4096, 24000, 48000, 24},   /* For Play */
    { 5461, 32000, 48000, 32},   /* For Play */
    { 8192, 48000, 48000, 48},   /* For Play / Record */
    {16384, 96000, 48000, 96},   /* For Play / Record */
    {12288, 48000, 32000, 48},   /* For Record */
    {16384, 48000, 24000, 48},   /* For Record */
    {24576, 48000, 16000, 48},   /* For Record */
};
#else
/* fixed sample rate to 96K */
const SR_T srt[] = {
    { 1365, 16000, 96000, 16},   /* For Play */
    { 2048, 24000, 96000, 24},   /* For Play */
    { 2732, 32000, 96000, 32},   /* For Play */
    { 4096, 48000, 96000, 48},   /* For Play / Record */
    { 8192, 96000, 96000, 96},   /* For Play / Record */
    {16384, 96000, 48000, 96},   /* For Play / Record */
    {24576, 96000, 32000, 96},   /* For Record */
    {32768, 96000, 24000, 96},   /* For Record */
    {49152, 96000, 16000, 96},   /* For Record */
};
#endif

/*
int Resamples(RESAMPLE_MODE_T mode, short *x, int ch_num, int samples, short *y, int s_idx)
    
    mode    : E_RS_REC_CH0 / E_RS_REC_CH1 / E_RS_PLAY_CH0 / E_RS_PLAY_CH1
    x       : point to input buffer of 16-bit PCM samples
    ch_num  :
    samples : samples in input buffer
    y       : point to output buffer
    s_idx   : resample index
              0 :   16K to   48K   For Play
              1 :   24K to   48K   For Play
              2 :   32K to   48K   For Play
              3 :    48 to   48K   For Play / Record
              4 :   96K to   48K   For Play / Record
              5 :   48K to   32K   For Record
              6 :   48K to   24K   For Record
              7 :   48K to   16K   For Record
    return  : samples in output buffer
Example:
    Resample 32kHz to 48kHz
    outSamples = Resamples(E_RS_PLAY_CH0, x    , 32,     y, 2);
    outSamples = Resamples(E_RS_PLAY_CH1, x + 1, 32, y + 1, 2);
*/ 
int Resamples(RESAMPLE_MODE_T mode, short *x, int ch_num, int samples, short *y, int s_idx)
{
    int i;
    static int px_play_ch0 = 0, px_play_ch1 = 0, px_rec_ch0 = 0, px_rec_ch1 = 0;
    static int yt_play_ch0 = 0, yt_play_ch1 = 0, yt_rec_ch0 = 0, yt_rec_ch1 = 0;
    static int xt_play_ch0 = 0, xt_play_ch1 = 0, xt_rec_ch0 = 0, xt_rec_ch1 = 0;
    int px = 0;
    int yt = 0;
    int xt = 0;
    int idx;
    int offset;
    int ii;
    int f, r,s;

    switch(mode)
    {
        case E_RS_REC_CH0:
            px = px_rec_ch0;
            yt = yt_rec_ch0;
            xt = xt_rec_ch0;
            break;
        case E_RS_REC_CH1:
            px = px_rec_ch1;
            yt = yt_rec_ch1;
            xt = xt_rec_ch1;
            break;
        case E_RS_PLAY_CH0:
            px = px_play_ch0;
            yt = yt_play_ch0;
            xt = xt_play_ch0;
            break;
        case E_RS_PLAY_CH1:
            px = px_play_ch1;
            yt = yt_play_ch1;
            xt = xt_play_ch1;
            break;
    }
    r = srt[s_idx].r;
    s = srt[s_idx].s;

    offset = xt >> 13;
    i = 0;
    do
    {
        idx = yt >> 13;
        f = yt & ((1 << 13) - 1);
        ii = idx - offset;
        if (ii < 0)
        {
            y[i * ch_num] = ((8192 - f)*px + x[0] * f) >> 13;
        }
        else
        {
            y[i * ch_num] = ((8192 - f)*x[ii * ch_num] + x[ii * ch_num + ch_num] * f) >> 13;
        }

        i++;
        yt += r;
    } while (yt < (xt + ((samples - 1) << 13)));

    px = x[(samples - 1) * ch_num];
    xt += (samples << 13);

    if (xt > (s << 13))
    {
        xt = 0;
        yt = 0;
    }

    switch(mode)
    {
        case E_RS_REC_CH0:
            px_rec_ch0 = px;
            yt_rec_ch0 = yt;
            xt_rec_ch0 = xt;
            break;
        case E_RS_REC_CH1:
            px_rec_ch1 = px;
            yt_rec_ch1 = yt;
            xt_rec_ch1 = xt;
            break;
        case E_RS_PLAY_CH0:
            px_play_ch0 = px;
            yt_play_ch0 = yt;
            xt_play_ch0 = xt;
            break;
        case E_RS_PLAY_CH1:
            px_play_ch1 = px;
            yt_play_ch1 = yt;
            xt_play_ch1 = xt;
            break;
    }

    return i;
}
 
