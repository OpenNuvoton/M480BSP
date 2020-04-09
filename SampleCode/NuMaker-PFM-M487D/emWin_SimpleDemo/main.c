/**************************************************************************//**
 * @file     main.c
 * @version  V2.0
 * @brief    To utilize emWin library to demonstrate interactive feature.
 *
 * @copyright (C) 2018 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include <string.h>

#include "NuMicro.h"

#include "GUI.h"
#include "wm.h"
#include "FRAMEWIN.h"
#include "LCDConf.h"

#ifdef __USE_SD__
#include "diskio.h"
#include "ff.h"
#endif

#include "M48XTouchPanel.h"

#ifdef __USE_SD__
//FATFS FatFs[_VOLUMES];      /* File system object for logical drive */

#if defined (__GNUC__)
BYTE Buff[1024] __attribute__ ((aligned(32)));       /* Working buffer */
#elif defined ( __ICCARM__ )
#pragma data_alignment=32
BYTE Buff[1024];       /* Working buffer */
#else
__align(32) BYTE Buff[1024];       /* Working buffer */
#endif

FIL hFile;
#endif

extern int ts_writefile(void);
extern int ts_readfile(void);

#ifdef __USE_SD__
/*---------------------------------------------------------*/
/* User Provided RTC Function for FatFs module             */
/*---------------------------------------------------------*/
/* This is a real time clock service to be called from     */
/* FatFs module. Any valid time must be returned even if   */
/* the system does not support an RTC.                     */
/* This function is not required in read-only cfg.         */

unsigned long get_fattime (void)
{
    unsigned long tmr;

    tmr=0x00000;

    return tmr;
}
#endif

extern volatile GUI_TIMER_TIME OS_TimeMS;


/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _SYS_Init
*/
static void _SYS_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init System Clock                                                                                       */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable HIRC clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HIRCEN_Msk);

    /* Waiting for HIRC clock ready */
    CLK_WaitClockReady(CLK_STATUS_HIRCSTB_Msk);

    /* Switch HCLK clock source to HIRC */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HIRC, CLK_CLKDIV0_HCLK(1));

    /* Enable HXT */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set SysTick source to HCLK/2 */
    CLK_SetSysTickClockSrc(CLK_CLKSEL0_STCLKSEL_HCLK_DIV2);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable peripheral clock */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(EBI_MODULE);
    //CLK_EnableModuleClock(I2C2_MODULE);
    CLK_EnableModuleClock(TMR0_MODULE);

    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HXT, 0);
    CLK->AHBCLK |= (1 << 14);  // 128k~160k for SPIM
    outpw(0x40007004,0x16);  // control SPIM can write

#ifdef __USE_SD__
    SYS->GPE_MFPL &= ~(SYS_GPE_MFPL_PE7MFP_Msk     | SYS_GPE_MFPL_PE6MFP_Msk     | SYS_GPE_MFPL_PE3MFP_Msk      | SYS_GPE_MFPL_PE2MFP_Msk);
    SYS->GPE_MFPL |=  (SYS_GPE_MFPL_PE7MFP_SD0_CMD | SYS_GPE_MFPL_PE6MFP_SD0_CLK | SYS_GPE_MFPL_PE3MFP_SD0_DAT1 | SYS_GPE_MFPL_PE2MFP_SD0_DAT0);

    SYS->GPB_MFPL &= ~(SYS_GPB_MFPL_PB5MFP_Msk      | SYS_GPB_MFPL_PB4MFP_Msk);
    SYS->GPB_MFPL |=  (SYS_GPB_MFPL_PB5MFP_SD0_DAT3 | SYS_GPB_MFPL_PB4MFP_SD0_DAT2);

    SYS->GPD_MFPH &= ~(SYS_GPD_MFPH_PD13MFP_Msk);
    SYS->GPD_MFPH |=  (SYS_GPD_MFPH_PD13MFP_SD0_nCD);

    /* Enable IP clock */
    CLK->AHBCLK |= CLK_AHBCLK_SDH0CKEN_Msk; // SD Card driving clock.
#endif

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /*---------------------------------------------------------------------------------------------------------*/
    /* Init I/O Multi-function                                                                                 */
    /*---------------------------------------------------------------------------------------------------------*/
//    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA14MFP_Msk | SYS_GPA_MFPH_PA15MFP_Msk);
//    SYS->GPA_MFPH |= (SYS_GPA_MFPH_PA14MFP_UART0_TXD | SYS_GPA_MFPH_PA15MFP_UART0_RXD);

    /*=== UART mult-function pins ===*/
    /* Set PB.12 and PB.13 multi-function pins for UART0 RXD, TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Lock protected registers */
    SYS_LockReg();
}

#ifdef __USE_SD__
#define TEST_SDH    SDH0

void SDH0_IRQHandler(void)
{
    unsigned int volatile isr;
    unsigned int volatile ier;

    // FMI data abort interrupt
    if (TEST_SDH->GINTSTS & SDH_GINTSTS_DTAIF_Msk)
    {
        /* ResetAllEngine() */
        TEST_SDH->GCTL |= SDH_GCTL_GCTLRST_Msk;
    }

    //----- SD interrupt status
    isr = TEST_SDH->INTSTS;
    if (isr & SDH_INTSTS_BLKDIF_Msk)
    {
        // block down
        SD0.DataReadyFlag = TRUE;
        TEST_SDH->INTSTS = SDH_INTSTS_BLKDIF_Msk;
    }

    if (isr & SDH_INTSTS_CDIF_Msk)   // card detect
    {
        //----- SD interrupt status
        // it is work to delay 50 times for SD_CLK = 200KHz
        {
            int volatile i;         // delay 30 fail, 50 OK
            for (i=0; i<0x500; i++);  // delay to make sure got updated value from REG_SDISR.
            isr = TEST_SDH->INTSTS;
        }

        if (isr & SDH_INTSTS_CDSTS_Msk)
        {
            printf("\n***** card remove !\n");
            SD0.IsCardInsert = FALSE;   // SDISR_CD_Card = 1 means card remove for GPIO mode
            memset(&SD0, 0, sizeof(SDH_INFO_T));
        }
        else
        {
            printf("***** card insert !\n");
            SDH_Open(TEST_SDH, CardDetect_From_GPIO);
            SDH_Probe(TEST_SDH);
        }

        TEST_SDH->INTSTS = SDH_INTSTS_CDIF_Msk;
    }

    // CRC error interrupt
    if (isr & SDH_INTSTS_CRCIF_Msk)
    {
        if (!(isr & SDH_INTSTS_CRC16_Msk))
        {
            //printf("***** ISR sdioIntHandler(): CRC_16 error !\n");
            // handle CRC error
        }
        else if (!(isr & SDH_INTSTS_CRC7_Msk))
        {
            if (!SD0.R3Flag)
            {
                //printf("***** ISR sdioIntHandler(): CRC_7 error !\n");
                // handle CRC error
            }
        }
        TEST_SDH->INTSTS = SDH_INTSTS_CRCIF_Msk;      // clear interrupt flag
    }

    if (isr & SDH_INTSTS_DITOIF_Msk)
    {
        printf("***** ISR: data in timeout !\n");
        TEST_SDH->INTSTS |= SDH_INTSTS_DITOIF_Msk;
    }

    // Response in timeout interrupt
    if (isr & SDH_INTSTS_RTOIF_Msk)
    {
        printf("***** ISR: response in timeout !\n");
        TEST_SDH->INTSTS |= SDH_INTSTS_RTOIF_Msk;
    }
}
#endif

WM_HWIN CreateFramewin(void);
int ts_calibrate(int xsize, int ysize);
volatile int g_enable_Touch;
void MainTask(void)
{
    WM_HWIN hWin;
    char     acVersion[40] = "Framewin: Version of emWin: ";

    printf("Main Task -> \n");
    GUI_Init();
    //GUI_SetDrawMode(GUI_DRAWMODE_NORMAL);
    strcat(acVersion, GUI_GetVersionString());
    hWin = CreateFramewin();
    FRAMEWIN_SetText(hWin, acVersion);
    while (1)
    {
        //GUI_PID_STATE State;

        //GUI_TOUCH_GetState(&State);

        //if (State.Pressed == 1) {
        //GUI_FillCircle(State.x, State.y, 3);
        //}
        GUI_Delay(500);
        //GUI_Delay(10);
    }
}

/*********************************************************************
*
*       TMR0_IRQHandler
*/

void TMR0_IRQHandler(void)
{
    int Key;
    OS_TimeMS++;
#if GUI_SUPPORT_TOUCH
    if ( OS_TimeMS % 10 == 0 )
    {
        if ( g_enable_Touch == 1 )
        {
            GUI_TOUCH_Exec();
        }
    }
#endif
    if ( (g_enable_Touch == 1) && (OS_TimeMS % 200 == 0) )
    {
        if (PA0 == 0)
        {
            Key = GUI_KEY_TAB;
            GUI_StoreKeyMsg(Key, 1);
        }
        if ((PA1 == 0) || (PG3 == 0))
        {
            Key = GUI_KEY_ENTER;
            GUI_StoreKeyMsg(Key, 1);
        }
        if (PG2 == 0)
        {
            Key = GUI_KEY_UP;
            GUI_StoreKeyMsg(Key, 1);
        }
        if (PC10 == 0)
        {
            Key = GUI_KEY_DOWN;
            GUI_StoreKeyMsg(Key, 1);
        }
        if (PC9 == 0)
        {
            Key = GUI_KEY_LEFT;
            GUI_StoreKeyMsg(Key, 1);
        }
        if (PG4 == 0)
        {
            Key = GUI_KEY_RIGHT;
            GUI_StoreKeyMsg(Key, 1);
        }
    }

    TIMER_ClearIntFlag(TIMER0);
}


void SysTick_Handler(void)
{

}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       main
*/

int main(void)
{
#ifdef __USE_SD__
    FRESULT     res;
#endif

//    uint32_t i;
//    GUI_COLOR aColor[] = {GUI_RED, GUI_YELLOW};

    //
    // Init System, IP clock and multi-function I/O
    //
    _SYS_Init();
    //
    // Init UART to 115200-8n1 for print message
    //
    UART_Open(UART0, 115200);

    g_enable_Touch = 0;

    // Enable Timer0 clock and select Timer0 clock source
    //
    CLK_EnableModuleClock(TMR0_MODULE);
    CLK_SetModuleClock(TMR0_MODULE, CLK_CLKSEL1_TMR0SEL_HXT, 0);
    //
    // Initial Timer0 to periodic mode with 1000Hz
    //
    TIMER_Open(TIMER0, TIMER_PERIODIC_MODE, 1000);
    //
    // Enable Timer0 interrupt
    //
    TIMER_EnableInt(TIMER0);
    NVIC_SetPriority(TMR0_IRQn, 1);
    NVIC_EnableIRQ(TMR0_IRQn);
    //
    // Start Timer0
    //
    TIMER_Start(TIMER0);
//    SysTick_Config(SystemCoreClock / 1000);
    printf("\n\nCPU @ %d Hz\n", SystemCoreClock);

    GPIO_SetMode(PA, BIT0, GPIO_MODE_INPUT);
    GPIO_SetMode(PA, BIT1, GPIO_MODE_INPUT);
    GPIO_SetMode(PG, BIT2, GPIO_MODE_INPUT);
    GPIO_SetMode(PG, BIT3, GPIO_MODE_INPUT);
    GPIO_SetMode(PG, BIT4, GPIO_MODE_INPUT);
    GPIO_SetMode(PC, BIT9, GPIO_MODE_INPUT);
    GPIO_SetMode(PC, BIT10, GPIO_MODE_INPUT);

#if GUI_SUPPORT_TOUCH
    GUI_Init();

    Init_TouchPanel();

#ifdef __USE_SD__
    SDH_Open_Disk(TEST_SDH, CardDetect_From_GPIO);
    printf("rc=%d\n", (WORD)disk_initialize(0));
    disk_read(0, Buff, 2, 1);
    //f_mount(&FatFs[0], "", 0);  // for FATFS v0.11
    GUI_Init();
    res = f_open(&hFile, "0:\\ts_calib", FA_OPEN_EXISTING | FA_READ);
    if (res)
    {
        // file does not exists, so do calibration
        res = f_open(&hFile, "0:\\ts_calib", FA_CREATE_ALWAYS | FA_WRITE);
        if ( res )
        {
            f_close(&hFile);
            GUI_DispStringAt("CANNOT create the calibration file.\nPlease insert a SD card then reboot.", 0, 0);
            while(1);
        }

        ts_calibrate(__DEMO_TS_WIDTH__, __DEMO_TS_HEIGHT__);
        //GUI_SetDrawMode(GUI_DRAWMODE_NORMAL);
        ts_writefile();
    }
    else
    {
        ts_readfile();
    }
    f_close(&hFile);
#else
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable FMC ISP function */
    FMC_Open();

    /* SPI flash 256KB + 0x1C marker address */
    //if (FMC_Read(__DEMO_TSFILE_ADDR__ + 0x1C) != 0x55AAA55A)
    if ( 1 )
    {
        FMC_ENABLE_AP_UPDATE();
        ts_calibrate(__DEMO_TS_WIDTH__, __DEMO_TS_HEIGHT__);
        // Erase page
        FMC_Erase(__DEMO_TSFILE_ADDR__);
        ts_writefile();
        FMC_DISABLE_AP_UPDATE();
    }
    else
    {
        ts_readfile();
    }

    /* Disable FMC ISP function */
    FMC_Close();

    /* Lock protected registers */
    SYS_LockReg();
#endif
#endif

    g_enable_Touch = 1;

    //
    // Start application
    //
    MainTask();
    while(1);

//    printf("\n############# Start !!!!!\n");
//    GUI_Init();
//    while(1) {
//        for (i = 0; i < 2; i++) {
//            GUI_Clear();
//            GUI_SetColor(aColor[i]);
//            GUI_SetFont(&GUI_FontComic24B_ASCII);
//            GUI_DispStringAt("Hello world!", 1, 1);
//            CLK_SysTickDelay(200000);
//        }
//    }

}

/*************************** End of file ****************************/
