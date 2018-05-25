/**************************************************************************//**
 * @file     MP3HeaderParser.h
 * @version  V1.00
 * @brief    MP3 header parser
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NuMicro.h"
#include "config.h"

typedef struct mp3Header mp3Header;

extern struct AudioInfoObject audioInfo;

void MP3_DECODE_HEADER(unsigned char *pBytes, struct mp3Header *hdr)
{
    (hdr)->sync     = (pBytes)[0];
    (hdr)->sync     = (hdr)->sync << 3;
    (hdr)->sync     |= ((pBytes)[1] & 0xE0) >> 5;
    (hdr)->version  = ((pBytes)[1] & 0x18) >> 3;
    (hdr)->layer    = ((pBytes)[1] & 0x06) >> 1;
    (hdr)->protect  = ((pBytes)[1] & 0x01);
    (hdr)->bitrate  = ((pBytes)[2] & 0xF0) >> 4;
    (hdr)->samfreq  = ((pBytes)[2] & 0x0C) >> 2;
    (hdr)->padding  = ((pBytes)[2] & 0x02) >> 1;
    (hdr)->private  = ((pBytes)[2] & 0x01);
    (hdr)->channel  = ((pBytes)[3] & 0xC0) >> 6;
    (hdr)->mode     = ((pBytes)[3] & 0x30) >> 4;
    (hdr)->copy     = ((pBytes)[3] & 0x08) >> 3;
    (hdr)->original = ((pBytes)[3] & 0x04) >> 2;
    (hdr)->emphasis = ((pBytes)[3] & 0x03);
}

int MP3_IS_VALID_HEADER(struct mp3Header *hdr)
{
    return( (((hdr)->sync == 0x7FF)
             && ((hdr)->bitrate != 0x0f)
             && ((hdr)->version != 0x01)
             && ((hdr)->layer != 0x00)
             && ((hdr)->samfreq != 0x03)
             && ((hdr)->emphasis != 0x02) ) ? 1:0);
}

int MP3_IS_V1L3_HEADER(struct mp3Header *hdr)
{
    return( ((hdr)->layer == 0x01)
            && (((hdr)->version == 0x03) || ((hdr)->version == 0x02)) ? 1:0);
}

static int mp3GetFrameLength(mp3Header *pHdr)
{
    int pL1Rates[] =   {   0,  32,  64,  96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448,  -1 };
    int pL2Rates[] =   {   0,  32,  48,  56,  64,  80,  96, 112, 128, 160, 192, 224, 256, 320, 384,  -1 };
    int pV1L3Rates[] = {   0,  32,  40,  48,  56,  64,  80,  96, 112, 128, 160, 192, 224, 256, 320,  -1 };
    int pV2L1Rates[] = {   0,  32,  48,  56,  64,  80,  96, 112, 128, 144, 160, 176, 192, 224, 256,  -1 };
    int pV2L3Rates[] = {   0,   8,  16,  24,  32,  40,  48,  56,  64,  80,  96, 112, 128, 144, 160,  -1 };

    int pRate[4][4] =
    {
        { 11025, 12000, 8000, -1 }, // 2.5
        { -1, -1, -1, -1 }, // reserved
        { 22050, 24000, 16000, -1 }, // 2
        { 44100, 48000, 32000, -1 } // 1
    };

    int bitrate;
    int freq;

    int base = 144;

    if (pHdr->layer == 0x01)
    {
        if (pHdr->version == 0x03)
            bitrate = pV1L3Rates[pHdr->bitrate];
        else
            bitrate = pV2L3Rates[pHdr->bitrate];
    }
    else if (pHdr->layer == 0x02)
    {
        if (pHdr->version == 0x03)
            bitrate = pL2Rates[pHdr->bitrate];
        else
            bitrate = pV2L3Rates[pHdr->bitrate];
    }
    else
    {
        if (pHdr->version == 0x03)
            bitrate = pL1Rates[pHdr->bitrate];
        else
            bitrate = pV2L1Rates[pHdr->bitrate];
    }

    if (pHdr->layer == 3)   /* Layer 1 */
    {
        base = 12;
    }

    freq = pRate[pHdr->version][pHdr->samfreq];

    return ((base * 1000 * bitrate) / freq) + pHdr->padding;
}

static void mp3PrintHeader(mp3Header *pHdr)
{
    int pL1Rates[] =   {   0,  32,  64,  96, 128, 160, 192, 224, 256, 288, 320, 352, 384, 416, 448,  -1 };
    int pL2Rates[] =   {   0,  32,  48,  56,  64,  80,  96, 112, 128, 160, 192, 224, 256, 320, 384,  -1 };
    int pV1L3Rates[] = {   0,  32,  40,  48,  56,  64,  80,  96, 112, 128, 160, 192, 224, 256, 320,  -1 };
    int pV2L1Rates[] = {   0,  32,  48,  56,  64,  80,  96, 112, 128, 144, 160, 176, 192, 224, 256,  -1 };
    int pV2L3Rates[] = {   0,   8,  16,  24,  32,  40,  48,  56,  64,  80,  96, 112, 128, 144, 160,  -1 };

    int pRate[4][4] =
    {
        { 11025, 12000, 8000, -1 }, // 2.5
        { -1, -1, -1, -1 }, // reserved
        { 22050, 24000, 16000, -1 }, // 2
        { 44100, 48000, 32000, -1 } // 1
    };

    int bitrate;

    if (pHdr->layer == 0x01)
    {
        if (pHdr->version == 0x03)
            bitrate = pV1L3Rates[pHdr->bitrate];
        else
            bitrate = pV2L3Rates[pHdr->bitrate];
    }
    else if (pHdr->layer == 0x02)
    {
        if (pHdr->version == 0x03)
            bitrate = pL2Rates[pHdr->bitrate];
        else
            bitrate = pV2L3Rates[pHdr->bitrate];
    }
    else
    {
        if (pHdr->version == 0x03)
            bitrate = pL1Rates[pHdr->bitrate];
        else
            bitrate = pV2L1Rates[pHdr->bitrate];
    }

    audioInfo.mp3SampleRate = pRate[pHdr->version][pHdr->samfreq];
    audioInfo.mp3BitRate = bitrate * 1000;
    audioInfo.mp3Channel = (pHdr->channel == 0x03 ? 1:2);
    audioInfo.mp3PlayTime = ((unsigned int)audioInfo.playFileSize / (unsigned int)audioInfo.mp3BitRate * (unsigned int)8) * 1000;

}

int mp3CountV1L3Headers(unsigned char *pBytes, size_t size)
{
    int             offset              = 0;
    int             result              = 0;
    mp3Header       header;

    while (size >= 4)
    {
        if ((pBytes[0] == 0xFF)
                && ((pBytes[1] & 0xE0) == 0xE0)
           )
        {
            MP3_DECODE_HEADER(pBytes, &header);

            if (MP3_IS_VALID_HEADER(&header))
            {
                int framelength = mp3GetFrameLength(&header);

                if ((framelength > 0) && (size > framelength + 4))
                {
                    MP3_DECODE_HEADER(pBytes + framelength, &header);

                    if (MP3_IS_VALID_HEADER(&header))
                    {
                        offset = 0;
                        mp3PrintHeader(&header);
                        result++;
                    }
                }
            }
        }

        offset++;
        pBytes++;
        size--;
    }

    return result;
}
/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
