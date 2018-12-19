#ifndef __M48XTOUCHPANEL_H__
#define __M48XTOUCHPANEL_H__

#define __DEMO_TSFILE_ADDR__    0x00040000 /* SPI flash 256KB address */

#define __DEMO_TS_WIDTH__       320
#define __DEMO_TS_HEIGHT__      240

int Init_TouchPanel(void);
int Read_TouchPanel(int *x, int *y);
int Uninit_TouchPanel(void);
int Check_TouchPanel(void);
#endif
