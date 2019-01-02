/*********************************************************************
*                 SEGGER Software GmbH                               *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2018  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.48 - Graphical user interface for embedded applications **
All  Intellectual Property rights in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product. This file may
only be used in accordance with the following terms:

The  software has  been licensed by SEGGER Software GmbH to Nuvoton Technology Corporationat the address: No. 4, Creation Rd. III, Hsinchu Science Park, Taiwan
for the purposes  of  creating  libraries  for its 
Arm Cortex-M and  Arm9 32-bit microcontrollers, commercialized and distributed by Nuvoton Technology Corporation
under  the terms and conditions  of  an  End  User  
License  Agreement  supplied  with  the libraries.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
Licensing information
Licensor:                 SEGGER Software GmbH
Licensed to:              Nuvoton Technology Corporation, No. 4, Creation Rd. III, Hsinchu Science Park, 30077 Hsinchu City, Taiwan
Licensed SEGGER software: emWin
License number:           GUI-00735
License model:            emWin License Agreement, signed February 27, 2018
Licensed platform:        Cortex-M and ARM9 32-bit series microcontroller designed and manufactured by or for Nuvoton Technology Corporation
----------------------------------------------------------------------
Support and Update Agreement (SUA)
SUA period:               2018-03-26 - 2019-03-27
Contact to extend SUA:    sales@segger.com
----------------------------------------------------------------------
File        : LCDConf.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

#include <stddef.h>
#include <stdio.h>

#include "GUI.h"
#include "GUIDRV_FlexColor.h"

#include "M480.h"

#include "M48XTouchPanel.h"

/*********************************************************************
*
*       Layer configuration
*
**********************************************************************
*/
//
// Physical display size
//
#define XSIZE_PHYS 240
#define YSIZE_PHYS 320

//
// Color conversion
//
#define COLOR_CONVERSION GUICC_565

//
// Display driver
//
#define DISPLAY_DRIVER GUIDRV_FLEXCOLOR

//
// Orientation
//
#define DISPLAY_ORIENTATION (0)

//
// Hardware related
//
/* LCD Module "RS" */
#define PH_CTRL_RS  1
#if PH_CTRL_RS
#define SET_RS  PH3 = 1;
#define CLR_RS  PH3 = 0;
#endif

/* LCD Module "RESET" */
#define SET_RST PB6 = 1;
#define CLR_RST PB6 = 0;

/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
#define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
#define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   XSIZE_PHYS
#error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
#error Physical Y size of display is not defined!
#endif
#ifndef   COLOR_CONVERSION
#error Color conversion not defined!
#endif
#ifndef   DISPLAY_DRIVER
#error No display driver defined!
#endif
#ifndef   DISPLAY_ORIENTATION
#define DISPLAY_ORIENTATION 0
#endif

/*********************************************************************
*
*       Static code
*
**********************************************************************/
/*-----------------------------------------------*/
// Write control registers of LCD module  
// 
/*-----------------------------------------------*/
#if PH_CTRL_RS
void LCD_WR_REG(uint16_t cmd)
{
    CLR_RS
    EBI0_WRITE_DATA16(0x00000000, cmd);
    SET_RS

}

#else
void LCD_WR_REG(uint16_t cmd)
{
    EBI0_WRITE_DATA16(0x00000000, cmd);
}

#endif


/*-----------------------------------------------*/
// Write data to SRAM of LCD module  
// 
/*-----------------------------------------------*/
void LCD_WR_DATA(uint16_t dat)
{
    EBI0_WRITE_DATA16(0x00030000, dat);

}


/*-----------------------------------------------*/
// Read data from SRAM of LCD module 
// 
/*-----------------------------------------------*/
uint16_t LCD_RD_DATA(void)
{
    return EBI0_READ_DATA16(0x00030000);

}

/********************************************************************
*
*       LcdWriteDataMultiple
*
*   Function description:
*   Writes multiple values to a display register.
*/
static void LcdWriteDataMultiple(uint16_t * pData, int NumItems)
{
    while (NumItems--) {
        EBI0_WRITE_DATA16(0x00030000,*pData++);
    }
}

/********************************************************************
*
*       LcdReadDataMultiple
*
*   Function description:
*   Reads multiple values from a display register.
*/
static void LcdReadDataMultiple(uint16_t * pData, int NumItems)
{
    while (NumItems--) {
        *pData++ = EBI0_READ_DATA16(0x00030000);
    }
}

/*-----------------------------------------------*/
// Set cursor positon on the LCD screen 
// 
/*-----------------------------------------------*/
#if 0
void LCD_SetCursor(uint16_t x_s, uint16_t y_s)
{ 
    uint16_t x_e = x_s+1;
    uint16_t y_e = y_s+1;
        
    /* X range */
    LCD_WR_REG(0x2A);
    LCD_WR_DATA(x_s>>8);
    LCD_WR_DATA(x_s);
    LCD_WR_DATA(x_e>>8);
    LCD_WR_DATA(x_e);

    /* Y range */
    LCD_WR_REG(0x2B);
    LCD_WR_DATA(y_s>>8);
    LCD_WR_DATA(y_s);
    LCD_WR_DATA(y_e>>8);
    LCD_WR_DATA(y_e);
        
    /* Memory write */
    LCD_WR_REG(0x2C);
    
}
#endif

/*-----------------------------------------------*/
// Initial LIL9341 LCD driver chip 
// 
/*-----------------------------------------------*/
void ILI9341_Initial(void)
{
    uint16_t Reg = 0;
    
    /* Hardware reset */
    SET_RST;
    CLK_SysTickDelay(5000);     // Delay 5ms
    
    CLR_RST;
    CLK_SysTickDelay(20000);    // Delay 20ms
    
    SET_RST;
    CLK_SysTickDelay(40000);    // Delay 40ms

    /* Initial control registers */
    LCD_WR_REG(0xCB);
    LCD_WR_DATA(0x39);
    LCD_WR_DATA(0x2C);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x34);
    LCD_WR_DATA(0x02);

    LCD_WR_REG(0xCF);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0xC1);
    LCD_WR_DATA(0x30);

    LCD_WR_REG(0xE8);
    LCD_WR_DATA(0x85);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x78);

    LCD_WR_REG(0xEA);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);

    LCD_WR_REG(0xED);
    LCD_WR_DATA(0x64);
    LCD_WR_DATA(0x03);
    LCD_WR_DATA(0x12);
    LCD_WR_DATA(0x81);

    LCD_WR_REG(0xF7);
    LCD_WR_DATA(0x20);

    LCD_WR_REG(0xC0);
    LCD_WR_DATA(0x23);

    LCD_WR_REG(0xC1);
    LCD_WR_DATA(0x10);

    LCD_WR_REG(0xC5);
    LCD_WR_DATA(0x3e);
    LCD_WR_DATA(0x28);

    LCD_WR_REG(0xC7);
    LCD_WR_DATA(0x86);

    LCD_WR_REG(0x36);
    LCD_WR_DATA(0x48);

    LCD_WR_REG(0x3A);
    LCD_WR_DATA(0x55);
        
    LCD_WR_REG(0xB1);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x18);

    LCD_WR_REG(0xB6);
    LCD_WR_DATA(0x08);
    LCD_WR_DATA(0x82);
    LCD_WR_DATA(0x27);

    LCD_WR_REG(0xF2);
    LCD_WR_DATA(0x00);

    LCD_WR_REG(0x26);
    LCD_WR_DATA(0x01);

    LCD_WR_REG(0xE0);
    LCD_WR_DATA(0x0F);
    LCD_WR_DATA(0x31);
    LCD_WR_DATA(0x2B);
    LCD_WR_DATA(0x0C);
    LCD_WR_DATA(0x0E);
    LCD_WR_DATA(0x08);
    LCD_WR_DATA(0x4E);
    LCD_WR_DATA(0xF1);
    LCD_WR_DATA(0x37);
    LCD_WR_DATA(0x07);
    LCD_WR_DATA(0x10);
    LCD_WR_DATA(0x03);
    LCD_WR_DATA(0x0E);
    LCD_WR_DATA(0x09);
    LCD_WR_DATA(0x00);

    LCD_WR_REG(0xE1);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x0E);
    LCD_WR_DATA(0x14);
    LCD_WR_DATA(0x03);
    LCD_WR_DATA(0x11);
    LCD_WR_DATA(0x07);
    LCD_WR_DATA(0x31);
    LCD_WR_DATA(0xC1);
    LCD_WR_DATA(0x48);
    LCD_WR_DATA(0x08);
    LCD_WR_DATA(0x0F);
    LCD_WR_DATA(0x0C);
    LCD_WR_DATA(0x31);
    LCD_WR_DATA(0x36);
    LCD_WR_DATA(0x0F);

    LCD_WR_REG(0x11);
    CLK_SysTickDelay(200000);   // Delay 200ms
    
    LCD_WR_REG(0x29);           //Display on

    LCD_WR_REG(0x0A);
    Reg = LCD_RD_DATA();
    Reg = LCD_RD_DATA();
    printf("0Ah = %02x.\n", Reg);
    
    LCD_WR_REG(0x0B);
    Reg = LCD_RD_DATA();
    Reg = LCD_RD_DATA();
    printf("0Bh = %02x.\n", Reg);
    
    LCD_WR_REG(0x0C);
    Reg = LCD_RD_DATA();
    Reg = LCD_RD_DATA();
    printf("0Ch = %02x.\n", Reg);

    printf("Initial ILI9341 LCD Module done.\n\n");

}

//void I2C2_Init(void)
//{
    /* Open I2C2 and set clock to 100k */
    //I2C_Open(I2C2, 100000);
//}

//void EINT7_IRQHandler(void)
//{
//    /* To check if PB.9 external interrupt occurred */
//    if(GPIO_GET_INT_FLAG(PB, BIT9)) {
//        GPIO_CLR_INT_FLAG(PB, BIT9);
//        printf("PB.9 EINT7 occurred.\n");
//    }

//}


void EBI_FuncPinInit(void)
{
/*=== EBI (LCD module) mult-function pins ===*/ 	
    /* EBI AD0~5 pins on PG.9~14 */
    SYS->GPG_MFPH &= ~(SYS_GPG_MFPH_PG9MFP_Msk  | SYS_GPG_MFPH_PG10MFP_Msk |
                       SYS_GPG_MFPH_PG11MFP_Msk | SYS_GPG_MFPH_PG12MFP_Msk |
                       SYS_GPG_MFPH_PG13MFP_Msk | SYS_GPG_MFPH_PG14MFP_Msk);
    SYS->GPG_MFPH |= (SYS_GPG_MFPH_PG9MFP_EBI_AD0  | SYS_GPG_MFPH_PG10MFP_EBI_AD1 |
                      SYS_GPG_MFPH_PG11MFP_EBI_AD2 | SYS_GPG_MFPH_PG12MFP_EBI_AD3 |
                      SYS_GPG_MFPH_PG13MFP_EBI_AD4 | SYS_GPG_MFPH_PG14MFP_EBI_AD5);

    /* EBI AD6, AD7 pins on PD.8, PD.9 */
    SYS->GPD_MFPH &= ~(SYS_GPD_MFPH_PD8MFP_Msk | SYS_GPD_MFPH_PD9MFP_Msk);
    SYS->GPD_MFPH |= (SYS_GPD_MFPH_PD8MFP_EBI_AD6 | SYS_GPD_MFPH_PD9MFP_EBI_AD7);

    /* EBI AD8, AD9 pins on PE.14, PE.15 */
    SYS->GPE_MFPH &= ~(SYS_GPE_MFPH_PE14MFP_Msk | SYS_GPE_MFPH_PE15MFP_Msk);
    SYS->GPE_MFPH |= (SYS_GPE_MFPH_PE14MFP_EBI_AD8 | SYS_GPE_MFPH_PE15MFP_EBI_AD9);

    /* EBI AD10, AD11 pins on PE.1, PE.0 */
    SYS->GPE_MFPL &= ~(SYS_GPE_MFPL_PE1MFP_Msk | SYS_GPE_MFPL_PE0MFP_Msk);
    SYS->GPE_MFPL |= (SYS_GPE_MFPL_PE1MFP_EBI_AD10 | SYS_GPE_MFPL_PE0MFP_EBI_AD11);

    /* EBI AD12~15 pins on PH.8~11 */
    SYS->GPH_MFPH &= ~(SYS_GPH_MFPH_PH8MFP_Msk  | SYS_GPH_MFPH_PH9MFP_Msk |
    SYS_GPH_MFPH_PH10MFP_Msk | SYS_GPH_MFPH_PH11MFP_Msk);
    SYS->GPH_MFPH |= (SYS_GPH_MFPH_PH8MFP_EBI_AD12  | SYS_GPH_MFPH_PH9MFP_EBI_AD13 |
                      SYS_GPH_MFPH_PH10MFP_EBI_AD14 | SYS_GPH_MFPH_PH11MFP_EBI_AD15);

    /* Configure PH.3 as Output mode for LCD_RS (use GPIO PH.3 to control LCD_RS) */
    GPIO_SetMode(PH, BIT3, GPIO_MODE_OUTPUT);
    PH3 = 1;

    /* EBI RD and WR pins on PE.4 and PE.5 */
    SYS->GPE_MFPL &= ~(SYS_GPE_MFPL_PE4MFP_Msk | SYS_GPE_MFPL_PE5MFP_Msk);
    SYS->GPE_MFPL |= (SYS_GPE_MFPL_PE4MFP_EBI_nWR | SYS_GPE_MFPL_PE5MFP_EBI_nRD);

    /* EBI CS0 pin on PD.14 */
    SYS->GPD_MFPH &= ~SYS_GPD_MFPH_PD14MFP_Msk;
    SYS->GPD_MFPH |= SYS_GPD_MFPH_PD14MFP_EBI_nCS0;

    /* Configure PB.6 and PB.7 as Output mode for LCD_RST and LCD_Backlight */
    GPIO_SetMode(PB, BIT6, GPIO_MODE_OUTPUT);
    GPIO_SetMode(PB, BIT7, GPIO_MODE_OUTPUT);
    PB6 = 1;
    PB7 = 0;
    
    GPIO_SetMode(PH, BIT5, GPIO_MODE_INPUT);
    GPIO_SetMode(PH, BIT6, GPIO_MODE_INPUT);
    GPIO_SetMode(PH, BIT7, GPIO_MODE_INPUT);

}

/*********************************************************************
*
*       _InitController
*
* Purpose:
*   Initializes the display controller
*/
static void _InitController(void)
{
    static uint8_t s_InitOnce = 0;

    if (s_InitOnce == 0)
        s_InitOnce = 1;
    else
        return;

    /* Configure DC/RESET/LED pins */
    EBI_FuncPinInit();

    /* Initialize EBI bank0 to access external LCD Module */
    EBI_Open(EBI_BANK0, EBI_BUSWIDTH_16BIT, EBI_TIMING_NORMAL, 0, EBI_CS_ACTIVE_LOW);
    EBI->CTL0 |= EBI_CTL0_CACCESS_Msk;
    EBI->TCTL0 |= (EBI_TCTL0_WAHDOFF_Msk | EBI_TCTL0_RAHDOFF_Msk);
    printf("\n[EBI CTL0:0x%08X, TCLT0:0x%08X]\n\n", EBI->CTL0, EBI->TCTL0);

    /* Init LCD Module */
    ILI9341_Initial();
    
    /* PB.7 BL_CTRL pin */
    PB7 = 1;

    /* Init I2C2 to TP of LCD module */
    //I2C2_Init();

//		/* Configure PB.9 as Quasi-bidirection mode and enable interrupt by falling edge trigger */
//    GPIO_SetMode(PB, BIT9, GPIO_MODE_QUASI);
//    GPIO_EnableInt(PB, 9, GPIO_INT_FALLING);
//    NVIC_EnableIRQ(EINT7_IRQn);
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
#if GUI_SUPPORT_TOUCH
extern int ts_phy2log(int *sumx, int *sumy);

void GUI_TOUCH_X_ActivateX(void) {
}

void GUI_TOUCH_X_ActivateY(void) {
}


 
int  GUI_TOUCH_X_MeasureX(void) {
  int sumx;
  int sumy;
	if (Read_TouchPanel(&sumx, &sumy))
	{
//		sysprintf("X = %d\n", sumx);
		ts_phy2log(&sumx, &sumy);		
    return sumx;
	}
	return -1;
}

int  GUI_TOUCH_X_MeasureY(void) {
  int sumx;
  int sumy;
	if ( Read_TouchPanel(&sumx, &sumy) )
	{
//		sysprintf("Y = %d\n", sumy);
		ts_phy2log(&sumx, &sumy);				
    return sumy;
	}
	return -1;
}
#endif
/*********************************************************************
*
*       LCD_X_Config
*
* Purpose:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*
*/
void LCD_X_Config(void)
{
    GUI_DEVICE * pDevice;
    CONFIG_FLEXCOLOR Config = {0};
    GUI_PORT_API PortAPI = {0};
    //
    // Set display driver and color conversion
    //
    pDevice = GUI_DEVICE_CreateAndLink(DISPLAY_DRIVER, COLOR_CONVERSION, 0, 0);

    //
    // Display driver configuration
    //
    LCD_SetSizeEx (0, XSIZE_PHYS,   YSIZE_PHYS);
    LCD_SetVSizeEx(0, VXSIZE_PHYS,  VYSIZE_PHYS);
    //
    // Orientation
    //
    Config.Orientation = GUI_MIRROR_X | GUI_MIRROR_Y | GUI_SWAP_XY;
    GUIDRV_FlexColor_Config(pDevice, &Config);
    //
    // Set controller and operation mode
    //
    PortAPI.pfWrite16_A0  = LCD_WR_REG;
    PortAPI.pfWrite16_A1  = LCD_WR_DATA;
    PortAPI.pfWriteM16_A0 = LcdWriteDataMultiple;
    PortAPI.pfWriteM16_A1 = LcdWriteDataMultiple;
    PortAPI.pfRead16_A0   = LCD_RD_DATA;
    PortAPI.pfRead16_A1   = LCD_RD_DATA;
    PortAPI.pfReadM16_A0  = LcdReadDataMultiple;
    PortAPI.pfReadM16_A1  = LcdReadDataMultiple;
    GUIDRV_FlexColor_SetReadFunc66709_B16(pDevice, GUIDRV_FLEXCOLOR_READ_FUNC_III);
    GUIDRV_FlexColor_SetFunc(pDevice, &PortAPI, GUIDRV_FLEXCOLOR_F66709, GUIDRV_FLEXCOLOR_M16C0B16);

#if GUI_SUPPORT_TOUCH
// LCD calibration
//
// Calibrate touch screen
//
    GUI_TOUCH_Calibrate(GUI_COORD_X, 0, (__DEMO_TS_WIDTH__ - 1), 0, (__DEMO_TS_WIDTH__ - 1));
    GUI_TOUCH_Calibrate(GUI_COORD_Y, 0, (__DEMO_TS_HEIGHT__-  1), 0, (__DEMO_TS_HEIGHT__-  1));
#endif
}
/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Purpose:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData)
{
    int r;

    GUI_USE_PARA(LayerIndex);
    GUI_USE_PARA(pData);
    switch (Cmd) {
        //
        // Required
        //
    case LCD_X_INITCONTROLLER: {
        //
        // Called during the initialization process in order to set up the
        // display controller and put it into operation. If the display
        // controller is not initialized by any external routine this needs
        // to be adapted by the customer...
        //
        _InitController();
            //printf("\n************ _InitController \n\n");
        return 0;
    }
    default:
        r = -1;
    }
    return r;
}

/*************************** End of file ****************************/
