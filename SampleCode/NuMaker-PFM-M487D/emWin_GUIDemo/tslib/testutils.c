/*
 *  tslib/src/ts_getxy.c
 *
 *  Copyright (C) 2001 Russell King.
 *
 * This file is placed under the GPL.  Please see the file
 * COPYING for more details.
 *
 * $Id: testutils.c,v 1.2 2004/10/19 22:01:27 dlowder Exp $
 *
 * Waits for the screen to be touched, averages x and y sample
 * coordinates until the end of contact
 */

//#include "config.h"
#include <stdio.h>
#include <stdlib.h>
//#include <unistd.h>
//#include <sys/time.h>
//#include "wbio.h"
//#include "wbtypes.h"
//#include "wblib.h"
#include "tslib.h"
#include "fbutils.h"
#include "M48XTouchPanel.h"
#include "GUI.h"

static int sort_by_x(const void* a, const void *b)
{
    return (((struct ts_sample *)a)->x - ((struct ts_sample *)b)->x);
}

static int sort_by_y(const void* a, const void *b)
{
    return (((struct ts_sample *)a)->y - ((struct ts_sample *)b)->y);
}

void getxy(int *x, int *y)
{
#define MAX_SAMPLES 128
    struct ts_sample samp[MAX_SAMPLES];
    int index, middle;
    int sumx, sumy;

    printf("getxy\n");
again:
    do
    {
        if ( Read_TouchPanel(&sumx, &sumy) > 0 )
        {
            if ( (sumx < 0) || ( sumy < 0 ) )
                continue;
            break;
        }
    }
    while (1);

    /* Now collect up to MAX_SAMPLES touches into the samp array. */
    index = 0;
    do
    {
        if (index < MAX_SAMPLES-1)
            index++;
        if ( Read_TouchPanel(&sumx, &sumy) > 0)
        {
            samp[index].x = sumx;
            samp[index].y = sumy;
            samp[index].pressure = 1000;
        }
        else
        {
            samp[index].x = samp[index-1].x;
            samp[index].y = samp[index-1].y;
            samp[index].pressure = 0;
        }

//      printf("%d %d %d\n", samp[index].x, samp[index].y , samp[index].pressure);
    }
    while (samp[index].pressure > 0);
    //printf("Took %d samples...\n",index);

    /*
     * At this point, we have samples in indices zero to (index-1)
     * which means that we have (index) number of samples.  We want
     * to calculate the median of the samples so that wild outliers
     * don't skew the result.  First off, let's assume that arrays
     * are one-based instead of zero-based.  If this were the case
     * and index was odd, we would need sample number ((index+1)/2)
     * of a sorted array; if index was even, we would need the
     * average of sample number (index/2) and sample number
     * ((index/2)+1).  To turn this into something useful for the
     * real world, we just need to subtract one off of the sample
     * numbers.  So for when index is odd, we need sample number
     * (((index+1)/2)-1).  Due to integer division truncation, we
     * can simplify this to just (index/2).  When index is even, we
     * need the average of sample number ((index/2)-1) and sample
     * number (index/2).  Calculate (index/2) now and we'll handle
     * the even odd stuff after we sort.
     */
    middle = index/2;
    if (x)
    {
        qsort(samp, index, sizeof(struct ts_sample), sort_by_x);
        if (index & 1)
            *x = samp[middle].x;
        else
            *x = (samp[middle-1].x + samp[middle].x) / 2;
    }
    if (y)
    {
        qsort(samp, index, sizeof(struct ts_sample), sort_by_y);
        if (index & 1)
            *y = samp[middle].y;
        else
            *y = (samp[middle-1].y + samp[middle].y) / 2;
    }
    if ( (index <= 3) || ( *x < 0) || ( *y < 0 ) )
        goto again;
}

extern int ts_phy2log(int *sumx, int *sumy);

static int palette [] =
{
    /*0x000000, 0xffe080, 0xffffff, 0xe0c0a0, 0x304050, 0x80b8c0*/
    GUI_MAKE_COLOR(0x000000), GUI_MAKE_COLOR(0x80e0ff), GUI_MAKE_COLOR(0xffffff), GUI_MAKE_COLOR(0xa0c0e0), GUI_MAKE_COLOR(0x504030), GUI_MAKE_COLOR(0xc0b880),
    GUI_MAKE_COLOR(0x7F1F00), GUI_MAKE_COLOR(0x20201F), GUI_MAKE_COLOR(0x5F3F1F), GUI_MAKE_COLOR(0xAFBFCF), GUI_MAKE_COLOR(0xF080D0), GUI_MAKE_COLOR(0x3F477F),
    GUI_MAKE_COLOR(0x207820)
};
#define NR_COLORS (sizeof (palette) / sizeof (palette [0]))

#define NR_BUTTONS 3
struct ts_button
{
    int x, y, w, h;
    char *text;
    int flags;
#define BUTTON_ACTIVE 0x00000001
};
static struct ts_button buttons [NR_BUTTONS];

/* [inactive] border fill text [active] border fill text */
static int button_palette [6] =
{
    1, 4, 2,
    1, 5, 0
};

void button_draw (struct ts_button *button)
{
    int s = (button->flags & BUTTON_ACTIVE) ? 3 : 0;

    rect(button->x, button->y, button->x + button->w,
         button->y + button->h, button_palette [s]);
    fillrect(button->x + 1, button->y + 1,
             button->x + button->w - 2,
             button->y + button->h - 2, button_palette [s + 1]);
//    put_string_center(button->x + button->w / 2,
//                      button->y + button->h / 2,
//                      button->text, button_palette [s + 2]);

    GUI_SetColor(palette[button_palette [s + 2]]);
    GUI_DispStringHCenterAt(button->text, button->x + button->w / 2, button->y + button->h / 2);
}

int button_handle (struct ts_button *button, int x, int y, unsigned int p)
{
    int inside = (x >= button->x) && (y >= button->y) &&
                 (x < button->x + button->w) &&
                 (y < button->y + button->h);

    if (p > 0)
    {
        if (inside)
        {
            if (!(button->flags & BUTTON_ACTIVE))
            {
                button->flags |= BUTTON_ACTIVE;
                button_draw (button);
            }
        }
        else if (button->flags & BUTTON_ACTIVE)
        {
            button->flags &= ~BUTTON_ACTIVE;
            button_draw (button);
        }
    }
    else if (button->flags & BUTTON_ACTIVE)
    {
        button->flags &= ~BUTTON_ACTIVE;
        button_draw (button);
        return 1;
    }

    return 0;
}

static void refresh_screen(void)
{
    int i;

//    fillrect (0, 0, xres - 1, yres - 1, 0);
    GUI_Clear();
//    put_string_center (xres/2, yres/4,   "Touchscreen test program", 1);
//    put_string_center (xres/2, yres/4+20,"Touch screen to move crosshair", 2);

    GUI_SetColor(palette[1]);
    GUI_DispStringHCenterAt("Touchscreen test program", xres / 2, yres / 4);

    GUI_SetColor(palette[2]);
    GUI_DispStringHCenterAt("Touch screen to move crosshair", xres / 2, yres / 4 + 20);

    for (i = 0; i < NR_BUTTONS; i++)
        button_draw (&buttons [i]);
}

int ts_test(int xsize, int ysize)
{
    int sumx, sumy;
    int x, y;
    unsigned int i;
    unsigned int mode = 0;
    int quit_pressed = 0;

    xres = xsize;
    yres = ysize;

    x = xres/2;
    y = yres/2;

    for (i = 0; i < NR_COLORS; i++)
        setcolor (i, palette [i]);

    /* Initialize buttons */
    //memset (&buttons, 0, sizeof (buttons));
    buttons [0].w = buttons [1].w = buttons [2].w = xres / 4;
    buttons [0].h = buttons [1].h = buttons [2].h = 20;
    buttons [0].x = 0;
    buttons [1].x = (3 * xres) / 8;
    buttons [2].x = (3 * xres) / 4 - 1;
    buttons [0].y = buttons [1].y = buttons [2].y = 10;
    buttons [0].text = "Drag";
    buttons [1].text = "Draw";
    buttons [2].text = "Quit";

    refresh_screen ();

    while (1)
    {
        struct ts_sample samp;

        /* Show the cross */
        if ((mode & 15) != 1)
            put_cross(x, y, 2 | XORMODE);

        if ( Read_TouchPanel(&sumx, &sumy) > 0)
        {
            ts_phy2log(&sumx, &sumy);
            samp.x = sumx;
            samp.y = sumy;
            samp.pressure = 1000;
        }
        else
        {
            samp.x = x;
            samp.y = y;
            samp.pressure = 0;
        }
        GUI_Delay(30);

        /* Hide it */
        if ((mode & 15) != 1)
            put_cross(x, y, 2 | XORMODE);

        for (i = 0; i < NR_BUTTONS; i++)
            if (button_handle(&buttons [i], samp.x, samp.y, samp.pressure))
                switch (i)
                {
                case 0:
                    mode = 0;
                    refresh_screen ();
                    break;
                case 1:
                    mode = 1;
                    refresh_screen ();
                    break;
                case 2:
                    quit_pressed = 1;
                }

        if (samp.pressure > 0)
        {
            if (mode == 0x80000001)
                line (x, y, samp.x, samp.y, 2);
            //pixel(x, y, 2);
            x = samp.x;
            y = samp.y;
            mode |= 0x80000000;
        }
        else
            mode &= ~0x80000000;
        if (quit_pressed)
            break;
    }
//    fillrect(0, 0, xres - 1, yres - 1, 0);
    GUI_Clear();

    return 0;
}
