/*
 * fbutils.c
 *
 * Utility routines for framebuffer interaction
 *
 * Copyright 2002 Russell King and Doug Lowder
 *
 * This file is placed under the GPL.  Please see the
 * file COPYING for details.
 *
 */

//#include "config.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <unistd.h>
//#include <sys/fcntl.h>
//#include <sys/ioctl.h>
//#include <sys/mman.h>
//#include <sys/time.h>
#include "fbutils.h"
//#include "wbtypes.h"
//#include "LCDconf.h"
#include "M48XTouchPanel.h"
#include "GUI.h"
#if 0
union multiptr
{
    unsigned char *p8;
    unsigned short *p16;
    unsigned long *p32;
};
#endif
//static int con_fd, fb_fd, last_vt = -1;
//static unsigned char *line_addr;
//static int fb_fd=0;
static int bytes_per_pixel=2;
static unsigned colormap [13];
static unsigned colormap2[13];
unsigned int xres=__DEMO_TS_WIDTH__, yres=__DEMO_TS_HEIGHT__;

int red_length = 5;
int green_length = 6;
int blue_length = 5;

int red_offset = 11;
int green_offset = 5;
int blue_offset = 0;

//extern void * g_VAFrameBuf;

void line(int x1, int y1, int x2, int y2, unsigned colidx);

void put_cross(int x, int y, unsigned colidx)
{
    line (x - 10, y, x - 2, y, colidx);
    line (x + 2, y, x + 10, y, colidx);
    line (x, y - 10, x, y - 2, colidx);
    line (x, y + 2, x, y + 10, colidx);

#if 1
    line (x - 6, y - 9, x - 9, y - 9, colidx + 1);
    line (x - 9, y - 8, x - 9, y - 6, colidx + 1);
    line (x - 9, y + 6, x - 9, y + 9, colidx + 1);
    line (x - 8, y + 9, x - 6, y + 9, colidx + 1);
    line (x + 6, y + 9, x + 9, y + 9, colidx + 1);
    line (x + 9, y + 8, x + 9, y + 6, colidx + 1);
    line (x + 9, y - 6, x + 9, y - 9, colidx + 1);
    line (x + 8, y - 9, x + 6, y - 9, colidx + 1);
#else
    line (x - 7, y - 7, x - 4, y - 4, colidx + 1);
    line (x - 7, y + 7, x - 4, y + 4, colidx + 1);
    line (x + 4, y - 4, x + 7, y - 7, colidx + 1);
    line (x + 4, y + 4, x + 7, y + 7, colidx + 1);
#endif
}
#if 0
void put_char(int x, int y, int c, int colidx)
{
    int i,j,bits;

    for (i = 0; i < font_vga_8x8.height; i++)
    {
        bits = font_vga_8x8.data [font_vga_8x8.height * c + i];
        for (j = 0; j < font_vga_8x8.width; j++, bits <<= 1)
            if (bits & 0x80)
                pixel (x + j, y + i, colidx);
    }
}

void put_string(int x, int y, char *s, unsigned colidx)
{
    int i;
    for (i = 0; *s; i++, x += font_vga_8x8.width, s++)
        put_char (x, y, *s, colidx);
}

void put_string_center(int x, int y, char *s, unsigned colidx)
{
    size_t sl = strlen (s);
    put_string (x - (sl / 2) * font_vga_8x8.width,
                y - font_vga_8x8.height / 2, s, colidx);
}
#endif
void setcolor(unsigned colidx, unsigned value)
{
    unsigned res;
    //unsigned short red, green, blue;
//  struct fb_cmap cmap;

#ifdef DEBUG
    if (colidx > 255)
    {
        fprintf (stderr, "WARNING: color index = %u, must be <256\n",
                 colidx);
        return;
    }
#endif

    switch (bytes_per_pixel)
    {
    default:
    case 1:
#if 0
        res = colidx;
        red = (value >> 8) & 0xff00;
        green = value & 0xff00;
        blue = (value << 8) & 0xff00;
        cmap.start = colidx;
        cmap.len = 1;
        cmap.red = &red;
        cmap.green = &green;
        cmap.blue = &blue;
        cmap.transp = NULL;
#endif
        break;
    case 2:
#if 0
        red = (value >> 16) & 0xff;
        green = (value >> 8) & 0xff;
        blue = value & 0xff;
        res = ((red >> (8 - red_length)) << red_offset) |
              ((green >> (8 - green_length)) << green_offset) |
              ((blue >> (8 - blue_length)) << blue_offset);
#endif
    case 4:
        res = value;
    }
    colormap [colidx] = value;
    GUI_SetColor(value);
    GUI_DrawPixel(0, 0);
    res = GUI_GetPixelIndex(0, 0);
    colormap2[colidx] = res;
    GUI_SetColor(0x00);
    GUI_DrawPixel(0, 0);
}
#if 0
static void __setpixel (union multiptr loc, unsigned xormode, unsigned color)
{
    switch(bytes_per_pixel)
    {
    case 1:
    default:
        if (xormode)
            *loc.p8 ^= color;
        else
            *loc.p8 = color;
        break;
    case 2:
        if (xormode)
            *loc.p16 ^= color;
        else
            *loc.p16 = color;
        break;
    case 4:
        if (xormode)
            *loc.p32 ^= color;
        else
            *loc.p32 = color;
        break;
    }
}
#endif
void pixel (int x, int y, unsigned colidx)
{
    unsigned xormode;
    unsigned color, color2;
    //union multiptr loc;

    if ((x < 0) || (x >= __DEMO_TS_WIDTH__) ||
            (y < 0) || (y >= __DEMO_TS_HEIGHT__))
        return;

    xormode = colidx & XORMODE;
    colidx &= ~XORMODE;

#ifdef DEBUG
    if (colidx > 255)
    {
        fprintf (stderr, "WARNING: color value = %u, must be <256\n",
                 colidx);
        return;
    }
#endif

//  loc.p8 = line_addr [y] + x * bytes_per_pixel;
//  line_addr = (unsigned char *)g_VAFrameBuf+ y*(LCD_XSIZE*bytes_per_pixel);
    color = GUI_GetPixelIndex(x, y);
    if ( color == colormap2[0] )
        color = colormap[0];
    else if ( color == colormap2[1] )
        color = colormap[1];
    else if ( color == colormap2[2] )
        color = colormap[2];
    else if ( color == colormap2[3] )
        color = colormap[3];
    else if ( color == colormap2[4] )
        color = colormap[4];
    else if ( color == colormap2[5] )
        color = colormap[5];
    else if ( color == colormap2[6] )
        color = colormap[6];
    else if ( color == colormap2[7] )
        color = colormap[7];
    else if ( color == colormap2[8] )
        color = colormap[8];
    else if ( color == colormap2[9] )
        color = colormap[9];
    else if ( color == colormap2[10] )
        color = colormap[10];
    else if ( color == colormap2[11] )
        color = colormap[11];
    else if ( color == colormap2[12] )
        color = colormap[12];
    color2 = colormap [colidx];
    if (xormode)
        color ^= color2;
    else
        color = color2;
    GUI_SetColor(color);
    GUI_DrawPixel(x, y);


    //loc.p8 = line_addr + x*bytes_per_pixel;
    //__setpixel(loc, xormode, colormap [colidx]);
}

void line(int x1, int y1, int x2, int y2, unsigned colidx)
{
    int tmp;
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (abs (dx) < abs (dy))
    {
        if (y1 > y2)
        {
            tmp = x1;
            x1 = x2;
            x2 = tmp;
            tmp = y1;
            y1 = y2;
            y2 = tmp;
            dx = -dx;
            dy = -dy;
        }
        x1 <<= 16;
        /* dy is apriori >0 */
        dx = (dx << 16) / dy;
        while (y1 <= y2)
        {
            pixel (x1 >> 16, y1, colidx);
            x1 += dx;
            y1++;
        }
    }
    else
    {
        if (x1 > x2)
        {
            tmp = x1;
            x1 = x2;
            x2 = tmp;
            tmp = y1;
            y1 = y2;
            y2 = tmp;
            dx = -dx;
            dy = -dy;
        }
        y1 <<= 16;
        dy = dx ? (dy << 16) / dx : 0;
        while (x1 <= x2)
        {
            pixel (x1, y1 >> 16, colidx);
            y1 += dy;
            x1++;
        }
    }
}
#if 1
void rect (int x1, int y1, int x2, int y2, unsigned colidx)
{
    line (x1, y1, x2, y1, colidx);
    line (x2, y1, x2, y2, colidx);
    line (x2, y2, x1, y2, colidx);
    line (x1, y2, x1, y1, colidx);
}

void fillrect (int x1, int y1, int x2, int y2, unsigned colidx)
{
    int tmp;
    unsigned xormode;
    unsigned color, color2;
    //union multiptr loc;

    /* Clipping and sanity checking */
    if (x1 > x2)
    {
        tmp = x1;
        x1 = x2;
        x2 = tmp;
    }
    if (y1 > y2)
    {
        tmp = y1;
        y1 = y2;
        y2 = tmp;
    }
    if (x1 < 0) x1 = 0;
    if (x1 >= xres) x1 = xres - 1;
    if (x2 < 0) x2 = 0;
    if (x2 >= xres) x2 = xres - 1;
    if (y1 < 0) y1 = 0;
    if (y1 >= yres) y1 = yres - 1;
    if (y2 < 0) y2 = 0;
    if (y2 >= yres) y2 = yres - 1;

    if ((x1 > x2) || (y1 > y2))
        return;

    xormode = colidx & XORMODE;
    colidx &= ~XORMODE;

#ifdef DEBUG
    if (colidx > 255)
    {
        fprintf (stderr, "WARNING: color value = %u, must be <256\n",
                 colidx);
        return;
    }
#endif

    color2 = colormap [colidx];

    for (; y1 <= y2; y1++)
    {
//      loc.p8 = line_addr [y1] + x1 * bytes_per_pixel;
        //line_addr = (unsigned char *)g_VAFrameBuf+ y1*(LCD_XSIZE*bytes_per_pixel);
        //loc.p8 = line_addr + x1* bytes_per_pixel;
        for (tmp = x1; tmp <= x2; tmp++)
        {
            //__setpixel (loc, xormode, colidx);
            //loc.p8 += bytes_per_pixel;
            color = GUI_GetPixelIndex(tmp, y1);
            if ( color == colormap2[0] )
                color = colormap[0];
            else if ( color == colormap2[1] )
                color = colormap[1];
            else if ( color == colormap2[2] )
                color = colormap[2];
            else if ( color == colormap2[3] )
                color = colormap[3];
            else if ( color == colormap2[4] )
                color = colormap[4];
            else if ( color == colormap2[5] )
                color = colormap[5];
            else if ( color == colormap2[6] )
                color = colormap[6];
            else if ( color == colormap2[7] )
                color = colormap[7];
            else if ( color == colormap2[8] )
                color = colormap[8];
            else if ( color == colormap2[9] )
                color = colormap[9];
            else if ( color == colormap2[10] )
                color = colormap[10];
            else if ( color == colormap2[11] )
                color = colormap[11];
            else if ( color == colormap2[12] )
                color = colormap[12];
            color2 = colormap [colidx];
            if (xormode)
                color ^= color2;
            else
                color = color2;
            GUI_SetColor(color);
            GUI_DrawPixel(tmp, y1);
        }
    }
}
#endif
