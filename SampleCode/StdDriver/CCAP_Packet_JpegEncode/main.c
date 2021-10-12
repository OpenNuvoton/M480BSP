/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Use packet format (all the luma and chroma data interleaved) to
 *           store captured image from NT99141 sensor to SRAM and
 *           encode the image to jpeg.
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#include "NuMicro.h"
#include "sensor.h"
#include <stdio.h>

extern void JpegEncode(unsigned char* image, unsigned char* jBuf,unsigned long *jSize,int width,int height);
/*------------------------------------------------------------------------------------------*/
/* Macro, type and constant definitions                                                     */
/*------------------------------------------------------------------------------------------*/
#define PLL_CLOCK       192000000

/*------------------------------------------------------------------------------------------*/
/* To run CCAPInterruptHandler, when CAP frame end interrupt                                */
/*------------------------------------------------------------------------------------------*/
volatile uint32_t u32FramePass = 0;

void CCAPInterruptHandler(void)
{
    u32FramePass++;
}

/*------------------------------------------------------------------------------------------*/
/*  CCAPIRQHandler                                                                          */
/*------------------------------------------------------------------------------------------*/
void CCAP_IRQHandler(void)
{
    uint32_t u32CapInt;
    u32CapInt = CCAP->INT;
    if( (u32CapInt & (CCAP_INT_VIEN_Msk | CCAP_INT_VINTF_Msk )) == (CCAP_INT_VIEN_Msk | CCAP_INT_VINTF_Msk))
    {
        CCAPInterruptHandler();
        CCAP->INT |= CCAP_INT_VINTF_Msk;        /* Clear Frame end interrupt */
    }

    if((u32CapInt & (CCAP_INT_ADDRMIEN_Msk|CCAP_INT_ADDRMINTF_Msk)) == (CCAP_INT_ADDRMIEN_Msk|CCAP_INT_ADDRMINTF_Msk))
    {
        CCAP->INT |= CCAP_INT_ADDRMINTF_Msk; /* Clear Address match interrupt */
    }

    if ((u32CapInt & (CCAP_INT_MEIEN_Msk|CCAP_INT_MEINTF_Msk)) == (CCAP_INT_MEIEN_Msk|CCAP_INT_MEINTF_Msk))
    {
        CCAP->INT |= CCAP_INT_MEINTF_Msk;    /* Clear Memory error interrupt */
    }
    CCAP->CTL = CCAP->CTL | CCAP_CTL_UPDATE;
}

void CCAPSetFreq(uint32_t u32ModFreqKHz,uint32_t u32SensorFreq)
{
    int32_t i32Div;

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Enable CAP Clock */
    CLK->AHBCLK |= CLK_AHBCLK_CCAPCKEN_Msk;

    /* Enable Sensor Clock */
    CLK->AHBCLK |= CLK_AHBCLK_SENCKEN_Msk;

    /* Reset IP */
    SYS_ResetModule(CCAP_RST);

    /* Specified sensor clock */
    CLK->CLKSEL0 = (CLK->CLKSEL0 & ~CLK_CLKSEL0_CCAPSEL_Msk) | CLK_CLKSEL0_CCAPSEL_HCLK ;

    i32Div = CLK_GetHCLKFreq()/u32SensorFreq-1;
    if(i32Div < 0) i32Div = 0;
    CLK->CLKDIV3 = (CLK->CLKDIV3 & ~CLK_CLKDIV3_VSENSEDIV_Msk) | i32Div<<CLK_CLKDIV3_VSENSEDIV_Pos;

    /* Specified engine clock */
    i32Div = CLK_GetHCLKFreq()/u32ModFreqKHz-1;
    if(i32Div < 0) i32Div = 0;
    CLK->CLKDIV3 = (CLK->CLKDIV3 & ~CLK_CLKDIV3_CCAPDIV_Msk) | i32Div<<CLK_CLKDIV3_CCAPDIV_Pos;

    /* lock protected registers */
    SYS_LockReg();
}

void SYS_Init(void)
{

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT clock (external XTAL 12MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);

    /* Set PCLK0/PCLK1 to HCLK/2 */
    CLK->PCLKDIV = (CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2);

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

//    SYS->GPC_MFPH &= ~(SYS_GPC_MFPH_PC11MFP_Msk | SYS_GPC_MFPH_PC12MFP_Msk);
//    SYS->GPC_MFPH |= (SYS_GPC_MFPH_PC11MFP_UART0_RXD | SYS_GPC_MFPH_PC12MFP_UART0_TXD);

    /* Set multi-function pins for CCAP */
    #if 1
    SYS->GPG_MFPL = (SYS->GPG_MFPL & ~SYS_GPG_MFPL_PG2MFP_Msk) | SYS_GPG_MFPL_PG2MFP_CCAP_DATA7;
    SYS->GPG_MFPL = (SYS->GPG_MFPL & ~SYS_GPG_MFPL_PG3MFP_Msk) | SYS_GPG_MFPL_PG3MFP_CCAP_DATA6;
    SYS->GPG_MFPL = (SYS->GPG_MFPL & ~SYS_GPG_MFPL_PG4MFP_Msk) | SYS_GPG_MFPL_PG4MFP_CCAP_DATA5;
    SYS->GPF_MFPH = (SYS->GPF_MFPH & ~SYS_GPF_MFPH_PF11MFP_Msk)| SYS_GPF_MFPH_PF11MFP_CCAP_DATA4;
    SYS->GPF_MFPH = (SYS->GPF_MFPH & ~SYS_GPF_MFPH_PF10MFP_Msk)| SYS_GPF_MFPH_PF10MFP_CCAP_DATA3;
    SYS->GPF_MFPH = (SYS->GPF_MFPH & ~SYS_GPF_MFPH_PF9MFP_Msk) | SYS_GPF_MFPH_PF9MFP_CCAP_DATA2;
    SYS->GPF_MFPH = (SYS->GPF_MFPH & ~SYS_GPF_MFPH_PF8MFP_Msk) | SYS_GPF_MFPH_PF8MFP_CCAP_DATA1;
    SYS->GPF_MFPL = (SYS->GPF_MFPL & ~SYS_GPF_MFPL_PF7MFP_Msk) | SYS_GPF_MFPL_PF7MFP_CCAP_DATA0;
    SYS->GPG_MFPH = (SYS->GPG_MFPH & ~SYS_GPG_MFPH_PG9MFP_Msk) | SYS_GPG_MFPH_PG9MFP_CCAP_PIXCLK;
    SYS->GPG_MFPH = (SYS->GPG_MFPH & ~SYS_GPG_MFPH_PG10MFP_Msk)| SYS_GPG_MFPH_PG10MFP_CCAP_SCLK;
    SYS->GPG_MFPH = (SYS->GPG_MFPH & ~SYS_GPG_MFPH_PG12MFP_Msk)| SYS_GPG_MFPH_PG12MFP_CCAP_VSYNC;
    SYS->GPG_MFPH = (SYS->GPG_MFPH & ~SYS_GPG_MFPH_PG13MFP_Msk)| SYS_GPG_MFPH_PG13MFP_CCAP_HSYNC;
    #else
    SYS->GPA_MFPL = (SYS->GPA_MFPL & ~SYS_GPA_MFPL_PA1MFP_Msk) | SYS_GPA_MFPL_PA1MFP_CCAP_DATA7;
    SYS->GPA_MFPL = (SYS->GPA_MFPL & ~SYS_GPA_MFPL_PA0MFP_Msk) | SYS_GPA_MFPL_PA0MFP_CCAP_DATA6;
    SYS->GPC_MFPL = (SYS->GPC_MFPL & ~SYS_GPC_MFPL_PC5MFP_Msk) | SYS_GPC_MFPL_PC5MFP_CCAP_DATA5;
    SYS->GPC_MFPL = (SYS->GPC_MFPL & ~SYS_GPC_MFPL_PC4MFP_Msk) | SYS_GPC_MFPL_PC4MFP_CCAP_DATA4;
    SYS->GPC_MFPL = (SYS->GPC_MFPL & ~SYS_GPC_MFPL_PC3MFP_Msk) | SYS_GPC_MFPL_PC3MFP_CCAP_DATA3;
    SYS->GPC_MFPL = (SYS->GPC_MFPL & ~SYS_GPC_MFPL_PC2MFP_Msk) | SYS_GPC_MFPL_PC2MFP_CCAP_DATA2;
    SYS->GPC_MFPL = (SYS->GPC_MFPL & ~SYS_GPC_MFPL_PC1MFP_Msk) | SYS_GPC_MFPL_PC1MFP_CCAP_DATA1;
    SYS->GPC_MFPL = (SYS->GPC_MFPL & ~SYS_GPC_MFPL_PC0MFP_Msk) | SYS_GPC_MFPL_PC0MFP_CCAP_DATA0;
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~SYS_GPB_MFPH_PB13MFP_Msk)| SYS_GPB_MFPH_PB13MFP_CCAP_PIXCLK;
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~SYS_GPB_MFPH_PB12MFP_Msk)| SYS_GPB_MFPH_PB12MFP_CCAP_SCLK;
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~SYS_GPB_MFPH_PB10MFP_Msk)| SYS_GPB_MFPH_PB10MFP_CCAP_VSYNC;
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~SYS_GPB_MFPH_PB9MFP_Msk) | SYS_GPB_MFPH_PB9MFP_CCAP_HSYNC;
    #endif

    /* lock protected registers */
    SYS_LockReg();

}

void UART0_Init(void)
{
    /*---------------------------------------------------------------------------------------------------------*/
    /* Init UART                                                                                               */
    /*---------------------------------------------------------------------------------------------------------*/
    /* Reset IP */
    SYS_ResetModule(UART0_RST);

    /* Configure UART0 and set UART0 Baudrate */
    UART_Open(UART0,115200);
}

#define SENSOR_IN_WIDTH             640
#define SENSOR_IN_HEIGHT            480
#define SYSTEM_WIDTH                160
#define SYSTEM_HEIGHT               120
uint8_t u8FrameBuffer[SYSTEM_WIDTH*SYSTEM_HEIGHT+SYSTEM_WIDTH];

#define DataFormatAndOrder (CCAP_PAR_INDATORD_YUYV | CCAP_PAR_INFMT_YUV422 | CCAP_PAR_OUTFMT_ONLY_Y)

int PacketFormatDownScale(void)
{
    uint32_t u32Frame;

    /* Initialize NT99141 sensor and set NT99141 output YUV422 format  */
    if(InitNT99141_VGA_YUV422()==FALSE) return -1;

    /* Enable External CAP Interrupt */
    NVIC_EnableIRQ(CCAP_IRQn);

    /* Enable External CAP Interrupt */
    CCAP_EnableInt(CCAP_INT_VIEN_Msk);

    /* Set Vsync polarity, Hsync polarity, pixel clock polarity, Sensor Format and Order */
    CCAP_Open(NT99141SensorPolarity | DataFormatAndOrder, CCAP_CTL_PKTEN );

    /* Set Cropping Window Vertical/Horizontal Starting Address and Cropping Window Size */
    CCAP_SetCroppingWindow(0,0,SENSOR_IN_HEIGHT,SENSOR_IN_WIDTH);

    /* Set System Memory Packet Base Address Register */
    CCAP_SetPacketBuf((uint32_t)u8FrameBuffer);

    /* Set Packet Scaling Vertical/Horizontal Factor Register */
    CCAP_SetPacketScaling(SYSTEM_HEIGHT,SENSOR_IN_HEIGHT,SYSTEM_WIDTH,SENSOR_IN_WIDTH);

    /* Set Packet Frame Output Pixel Stride Width */
    CCAP_SetPacketStride(SYSTEM_WIDTH);

    /* Start Image Capture Interface */
    CCAP_Start();

    u32Frame=u32FramePass;
    while(1)
    {
        if(u32FramePass!=(u32Frame)){
            u32Frame = u32FramePass;
            printf("u32FramePass=%d\n",u32FramePass);
        }
        if(u32FramePass>10)
            break;
    }

    /* Stop capturing images */
    CCAP_Stop(TRUE);
    return 0;
}


/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
uint8_t u8JpegBuffer[SYSTEM_WIDTH*SYSTEM_HEIGHT];
int32_t main (void)
{
    unsigned long u32JpegSize = sizeof(u8JpegBuffer);

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Init UART0 for printf */
    UART0_Init();

    /* Init Engine clock and Sensor clock */
    CCAPSetFreq(12000000,12000000);

    /* Using Packet format to Image down scale */
    if(PacketFormatDownScale()>=0){
        /* jpeg encode */
        JpegEncode(u8FrameBuffer, u8JpegBuffer, &u32JpegSize, SYSTEM_WIDTH, SYSTEM_HEIGHT);
    }

    while(1);
}





