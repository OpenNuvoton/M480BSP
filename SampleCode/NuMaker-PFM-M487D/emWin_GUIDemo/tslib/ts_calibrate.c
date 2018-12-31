/*
 *  tslib/tests/ts_calibrate.c
 *
 *  Copyright (C) 2001 Russell King.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 * $Id: ts_calibrate.c,v 1.8 2004/10/19 22:01:27 dlowder Exp $
 *
 * Basic test program for touchscreen library.
 */
#include <stdio.h>
#include <stdlib.h>
//#include <signal.h>
//#include <string.h>
//#include <unistd.h>
//#include <sys/fcntl.h>
//#include <sys/ioctl.h>
//#include <sys/mman.h>
//#include <sys/time.h>
#include "tslib.h"
#include "fbutils.h"
#include "testutils.h"
//#include "wbio.h"
//#include "wbtypes.h"
//#include "wblib.h"
//#include "LCDconf.h"
#include "NuMicro.h"
#include "GUI.h"
#include "M48XTouchPanel.h"
//#include "nvtfat.h"

#ifdef __USE_SD__
#include "diskio.h"
#include "ff.h"
#endif

typedef struct
{
    int x[5], xfb[5];
    int y[5], yfb[5];
    int a[7];
} calibration;

static int palette [] =
{
    /*0x000000, 0xffe080, 0xffffff, 0xe0c0a0*/
    GUI_MAKE_COLOR(0x000000), GUI_MAKE_COLOR(0x80e0ff), GUI_MAKE_COLOR(0xffffff), GUI_MAKE_COLOR(0xa0c0e0), GUI_MAKE_COLOR(0x7F1F00), GUI_MAKE_COLOR(0x20201F), GUI_MAKE_COLOR(0x5F3F1F)
};
#define NR_COLORS (sizeof (palette) / sizeof (palette [0]))

#ifdef __USE_SD__
extern FIL hFile;
#endif

int ts_writefile(void);
int ts_readfile(void);

int ts_calibrate(int xsize, int ysize);
//int linear_read(int *sumx, int *sumy);
int ts_phy2log(int *sumx, int *sumy);
calibration cal, final_cal;

#if 0
int perform_calibration(calibration *cal)
{
    int j;
    float n, x, y, x2, y2, xy, z, zx, zy;
    float det, a, b, c, e, f, i;
    float scaling = 65536.0;

    int nn,nx,ny,nx2,ny2, nxy;
// Get sums for matrix
    n = x = y = x2 = y2 = xy = 0;
    for(j=0; j<5; j++)
    {
        n += 1.0;
        x += (float)cal->x[j];
        y += (float)cal->y[j];
        x2 += (float)(cal->x[j]*cal->x[j]);
        y2 += (float)(cal->y[j]*cal->y[j]);
        xy += (float)(cal->x[j]*cal->y[j]);
    }
    nn = (int)n;
    nx = (int)x;
    ny = (int)y;
    nx2 = (int)x2;
    ny2 = (int)y2;
    nxy = (int)xy;
    printf("n=%d,x=%d,y=%d,x2=%d,y2=%d, xy=%d\n",nn,nx,ny,nx2,ny2,nxy);
// Get determinant of matrix -- check if determinant is too small
    det = n*(x2*y2 - xy*xy) + x*(xy*y - x*y2) + y*(x*xy - y*x2);
    if(det < 0.1 && det > -0.1)
    {
        printf("ts_calibrate: determinant is too small -- %f\n",det);
        return 0;
    }

// Get elements of inverse matrix
    a = (x2*y2 - xy*xy)/det;
    b = (xy*y - x*y2)/det;
    c = (x*xy - y*x2)/det;
    e = (n*y2 - y*y)/det;
    f = (x*y - n*xy)/det;
    i = (n*x2 - x*x)/det;

// Get sums for x calibration
    z = zx = zy = 0;
    for(j=0; j<5; j++)
    {
        z += (float)cal->xfb[j];
        zx += (float)(cal->xfb[j]*cal->x[j]);
        zy += (float)(cal->xfb[j]*cal->y[j]);
    }

// Now multiply out to get the calibration for framebuffer x coord
    cal->a[0] = (int)((a*z + b*zx + c*zy)*(scaling));
    cal->a[1] = (int)((b*z + e*zx + f*zy)*(scaling));
    cal->a[2] = (int)((c*z + f*zx + i*zy)*(scaling));
#if  1 //close
    nn = (int)((a*z + b*zx + c*zy)*(scaling));
    nx = (int)((b*z + e*zx + f*zy)*(scaling));
    ny = (int)((c*z + f*zx + i*zy)*(scaling));
//  nn = (int)(a*z + b*zx + c*zy);
//  nx = (int) (b*z + e*zx + f*zy);
//  ny = (int) (c*z + f*zx + i*zy);
    printf("%d %d %d\n",nn,nx,ny);
#endif
// Get sums for y calibration
    z = zx = zy = 0;
    for(j=0; j<5; j++)
    {
        z += (float)cal->yfb[j];
        zx += (float)(cal->yfb[j]*cal->x[j]);
        zy += (float)(cal->yfb[j]*cal->y[j]);
    }

// Now multiply out to get the calibration for framebuffer y coord
    cal->a[3] = (int)((a*z + b*zx + c*zy)*(scaling));
    cal->a[4] = (int)((b*z + e*zx + f*zy)*(scaling));
    cal->a[5] = (int)((c*z + f*zx + i*zy)*(scaling));
#if 1  // closed
//  nn = (int) (a*z + b*zx + c*zy);
//  nx = (int) (b*z + e*zx + f*zy);
//  ny = (int) (c*z + f*zx + i*zy);
    nn = (int)((a*z + b*zx + c*zy)*(scaling));
    nx = (int)((b*z + e*zx + f*zy)*(scaling));
    ny = (int)((c*z + f*zx + i*zy)*(scaling));
    printf("%d %d %d\n",nn,nx,ny);
#endif
// If we got here, we're OK, so assign scaling to a[6] and return
    cal->a[6] = (int)scaling;
    return 1;
    /*
    // This code was here originally to just insert default values
        for(j=0;j<7;j++) {
            c->a[j]=0;
        }
        c->a[1] = c->a[5] = c->a[6] = 1;
        return 1;
    */
}
#endif

int perform_calibration(calibration *cal)
{
    int j;
    float n, x, y, x2, y2, xy, z, zx, zy;
    float det, a, b, c, e, f, i;
    float scaling = 65536.0;

// Get sums for matrix
    n = x = y = x2 = y2 = xy = 0;
    for(j=0; j<5; j++)
    {
        n += 1.0f;
        x += (float)cal->x[j];
        y += (float)cal->y[j];
        x2 += (float)(cal->x[j]*cal->x[j]);
        y2 += (float)(cal->y[j]*cal->y[j]);
        xy += (float)(cal->x[j]*cal->y[j]);
    }
// Get determinant of matrix -- check if determinant is too small
    det = n*(x2*y2 - xy*xy) + x*(xy*y - x*y2) + y*(x*xy - y*x2);
    if(det < 0.1f && det > -0.1f)
    {
        printf("ts_calibrate: determinant is too small -- %f\n",det);
        return 0;
    }

// Get elements of inverse matrix
    a = (x2*y2 - xy*xy)/det;
    b = (xy*y - x*y2)/det;
    c = (x*xy - y*x2)/det;
    e = (n*y2 - y*y)/det;
    f = (x*y - n*xy)/det;
    i = (n*x2 - x*x)/det;

// Get sums for x calibration
    z = zx = zy = 0;
    for(j=0; j<5; j++)
    {
        z += (float)cal->xfb[j];
        zx += (float)(cal->xfb[j]*cal->x[j]);
        zy += (float)(cal->xfb[j]*cal->y[j]);
    }

// Now multiply out to get the calibration for framebuffer x coord
    cal->a[0] = (int)((a*z + b*zx + c*zy)*(scaling));
    cal->a[1] = (int)((b*z + e*zx + f*zy)*(scaling));
    cal->a[2] = (int)((c*z + f*zx + i*zy)*(scaling));
#if 0 //close
    printf("%f %f %f\n",(a*z + b*zx + c*zy),
              (b*z + e*zx + f*zy),
              (c*z + f*zx + i*zy));
#endif
// Get sums for y calibration
    z = zx = zy = 0;
    for(j=0; j<5; j++)
    {
        z += (float)cal->yfb[j];
        zx += (float)(cal->yfb[j]*cal->x[j]);
        zy += (float)(cal->yfb[j]*cal->y[j]);
    }

// Now multiply out to get the calibration for framebuffer y coord
    cal->a[3] = (int)((a*z + b*zx + c*zy)*(scaling));
    cal->a[4] = (int)((b*z + e*zx + f*zy)*(scaling));
    cal->a[5] = (int)((c*z + f*zx + i*zy)*(scaling));
#if 0  // closed
    printf("%f %f %f\n",(a*z + b*zx + c*zy),
              (b*z + e*zx + f*zy),
              (c*z + f*zx + i*zy));
#endif
// If we got here, we're OK, so assign scaling to a[6] and return
    cal->a[6] = (int)scaling;
    return 1;
}

static void get_sample (calibration *cal,int index, int x, int y, char *name)
{
    static int last_x = -1, last_y;

    if (last_x != -1)
    {
#define NR_STEPS 10
        int dx = ((x - last_x) << 16) / NR_STEPS;
        int dy = ((y - last_y) << 16) / NR_STEPS;
        int i;
        last_x <<= 16;
        last_y <<= 16;
        for (i = 0; i < NR_STEPS; i++)
        {
            put_cross (last_x >> 16, last_y >> 16, 2 | XORMODE);
            //usleep (1000);
            GUI_Delay(10);
            put_cross (last_x >> 16, last_y >> 16, 2 | XORMODE);
            last_x += dx;
            last_y += dy;
        }
    }


    put_cross(x, y, 2 | XORMODE);
    getxy (&cal->x [index], &cal->y [index]);
    put_cross(x, y, 2 | XORMODE);

    last_x = cal->xfb [index] = x;
    last_y = cal->yfb [index] = y;

    printf("%s : X = %4d Y = %4d\n", name, cal->x [index], cal->y [index]);
}

int ts_calibrate(int xsize, int ysize)
{
    int i;

    xres = xsize;
    yres = ysize;

    for (i = 0; i < NR_COLORS; i++)
        setcolor (i, palette [i]);

//    put_string_center (xres / 2, yres / 4,
//                       "TSLIB calibration utility", 1);
//    put_string_center (xres / 2, yres / 4 + 20,
//                       "Touch crosshair to calibrate", 2);

    GUI_SetColor(palette [1]);
    GUI_DispStringHCenterAt("TSLIB calibration utility", xres / 2, yres / 4);

    GUI_SetColor(palette [2]);
    GUI_DispStringHCenterAt("Touch crosshair to calibrate", xres / 2, yres / 4 + 20);

    printf("xres = %d, yres = %d\n", xres, yres);

// Read a touchscreen event to clear the buffer
    //getxy(ts, 0, 0);

    get_sample (&cal, 0, 50,        50,        "Top left");
//  GUI_Delay(200);
    get_sample (&cal, 1, xres - 50, 50,        "Top right");
    //GUI_Delay(200);
    get_sample (&cal, 2, xres - 50, yres - 50, "Bot right");
//  GUI_Delay(200);
    get_sample (&cal, 3, 50,        yres - 50, "Bot left");
//  GUI_Delay(200);
    get_sample (&cal, 4, xres / 2,  yres / 2,  "Center");
//  GUI_Delay(200);
    if (perform_calibration (&cal))
    {
        printf ("Calibration constants: ");
        for (i = 0; i < 7; i++) printf("%d ", cal.a [i]);
        printf("\n");
    }
    else
    {
        printf("Calibration failed.\n");
        i = -1;
    }
    final_cal.a[0] = cal.a[1];
    final_cal.a[1] = cal.a[2];
    final_cal.a[2] = cal.a[0];
    final_cal.a[3] = cal.a[4];
    final_cal.a[4] = cal.a[5];
    final_cal.a[5] = cal.a[3];
    final_cal.a[6] = cal.a[6];
    return i;
}
#if 0
int linear_read(int *sumx, int *sumy)
{
    int xtemp,ytemp;

//  ret = dejitter_read(info->next, samp, nr);
    if ( Read_TouchPanel(sumx, sumy) > 0)
    {
//printf("Before X=%d, Y=%d\n",*sumx, *sumy);
        xtemp = *sumx;
        ytemp = *sumy;
        *sumx = ( final_cal.a[2] +
                  final_cal.a[0]*xtemp +
                  final_cal.a[1]*ytemp ) / final_cal.a[6];
        *sumy = ( final_cal.a[5] +
                  final_cal.a[3]*xtemp +
                  final_cal.a[4]*ytemp ) / final_cal.a[6];
//printf("After X=%d, Y=%d\n",*sumx, *sumy);
        return 1;
    }
    else
    {
        *sumx = -1;
        *sumy = -1;
        return -1;
    }
}
#endif
int ts_phy2log(int *sumx, int *sumy)
{
    int xtemp,ytemp;

    xtemp = *sumx;
    ytemp = *sumy;
    *sumx = ( final_cal.a[2] +
              final_cal.a[0]*xtemp +
              final_cal.a[1]*ytemp ) / final_cal.a[6];
    *sumy = ( final_cal.a[5] +
              final_cal.a[3]*xtemp +
              final_cal.a[4]*ytemp ) / final_cal.a[6];
//printf("After X=%d, Y=%d\n",*sumx, *sumy);
    return 1;
}

int ts_writefile(void)
{
#ifdef __USE_SD__
    size_t cnt;
    FRESULT res;
    res = f_lseek(&hFile, 0);
    if (res != FR_OK)
    {
        printf("CANNOT seek the calibration into file\n");
        return -1;
    }

    res = f_write(&hFile, (char *)&final_cal.a[0], 28, &cnt);
    if (res != FR_OK)
    {
        printf("CANNOT write the calibration into file, %d\n", cnt);
        return -1;
    }
#else
    FMC_Write(__DEMO_TSFILE_ADDR__ + 0x00, final_cal.a[0]);
    FMC_Write(__DEMO_TSFILE_ADDR__ + 0x04, final_cal.a[1]);
    FMC_Write(__DEMO_TSFILE_ADDR__ + 0x08, final_cal.a[2]);
    FMC_Write(__DEMO_TSFILE_ADDR__ + 0x0C, final_cal.a[3]);
    FMC_Write(__DEMO_TSFILE_ADDR__ + 0x10, final_cal.a[4]);
    FMC_Write(__DEMO_TSFILE_ADDR__ + 0x14, final_cal.a[5]);
    FMC_Write(__DEMO_TSFILE_ADDR__ + 0x18, final_cal.a[6]);
    FMC_Write(__DEMO_TSFILE_ADDR__ + 0x1C, 0x55AAA55A);
#endif
    return 0;
}

int ts_readfile(void)
{
#ifdef __USE_SD__
    size_t cnt;
    FRESULT res;
    res = f_lseek(&hFile, 0);
    if (res != FR_OK)
    {
        printf("CANNOT seek the calibration into file\n");
        return -1;
    }

    res = f_read(&hFile, (char *)&final_cal.a[0], 28, &cnt);
    if (res != FR_OK)
    {
        printf("CANNOT read the calibration into file, %d\n", cnt);
        return -1;
    }
#else
    final_cal.a[0] = FMC_Read(__DEMO_TSFILE_ADDR__ + 0x00);
    final_cal.a[1] = FMC_Read(__DEMO_TSFILE_ADDR__ + 0x04);
    final_cal.a[2] = FMC_Read(__DEMO_TSFILE_ADDR__ + 0x08);
    final_cal.a[3] = FMC_Read(__DEMO_TSFILE_ADDR__ + 0x0C);
    final_cal.a[4] = FMC_Read(__DEMO_TSFILE_ADDR__ + 0x10);
    final_cal.a[5] = FMC_Read(__DEMO_TSFILE_ADDR__ + 0x14);
    final_cal.a[6] = FMC_Read(__DEMO_TSFILE_ADDR__ + 0x18);
#endif
    return 0;
}
