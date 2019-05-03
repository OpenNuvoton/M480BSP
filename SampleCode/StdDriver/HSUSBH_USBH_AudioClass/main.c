/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Demonstrates how to use USBH Audio Class driver. It shows the
 *           mute, volume, auto-gain, channel, and sampling rate control.
 *
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include <stdio.h>
#include <string.h>

#include "NuMicro.h"

#include "usbh_lib.h"
#include "usbh_uac.h"

#define AUDIO_IN_BUFSIZ             8192

#ifdef __ICCARM__
#pragma data_alignment=32
uint8_t  au_in_buff[AUDIO_IN_BUFSIZ];
#else
uint8_t  au_in_buff[AUDIO_IN_BUFSIZ] __attribute__((aligned(32)));
#endif

static volatile int  au_in_cnt, au_out_cnt;

static uint16_t  vol_max, vol_min, vol_res, vol_cur;

#ifdef DEBUG_ENABLE_SEMIHOST
#error This sample cannot execute with semihost enabled
#endif
extern int kbhit(void);                        /* function in retarget.c                 */


volatile uint32_t  g_tick_cnt;

void SysTick_Handler(void)
{
    g_tick_cnt++;
}

void enable_sys_tick(int ticks_per_second)
{
    g_tick_cnt = 0;
    if (SysTick_Config(SystemCoreClock / ticks_per_second))
    {
        /* Setup SysTick Timer for 1 second interrupts  */
        printf("Set system tick error!!\n");
        while (1);
    }
}

uint32_t get_ticks()
{
    return g_tick_cnt;
}

/*
 *  This function is necessary for USB Host library.
 */
void delay_us(int usec)
{
    /*
     *  Configure Timer0, clock source from XTL_12M. Prescale 12
     */
    /* TIMER0 clock from HXT */
    CLK->CLKSEL1 = (CLK->CLKSEL1 & (~CLK_CLKSEL1_TMR0SEL_Msk)) | CLK_CLKSEL1_TMR0SEL_HXT;
    CLK->APBCLK0 |= CLK_APBCLK0_TMR0CKEN_Msk;
    TIMER0->CTL = 0;        /* disable timer */
    TIMER0->INTSTS = (TIMER_INTSTS_TIF_Msk | TIMER_INTSTS_TWKF_Msk);   /* write 1 to clear for safety */
    TIMER0->CMP = usec;
    TIMER0->CTL = (11 << TIMER_CTL_PSC_Pos) | TIMER_ONESHOT_MODE | TIMER_CTL_CNTEN_Msk;

    while (!TIMER0->INTSTS);
}

void SYS_Init(void)
{
    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT clock */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Switch HCLK clock source to HXT */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HXT,CLK_CLKDIV0_HCLK(1));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable USBH module clock */
    CLK_EnableModuleClock(USBH_MODULE);

    /* USB Host desired input clock is 48 MHz. Set as PLL divided by 4 (192/4 = 48) */
    CLK->CLKDIV0 = (CLK->CLKDIV0 & ~CLK_CLKDIV0_USBDIV_Msk) | CLK_CLKDIV0_USB(4);

    /* Enable USBD and OTG clock */
    CLK->APBCLK0 |= CLK_APBCLK0_USBDCKEN_Msk | CLK_APBCLK0_OTGCKEN_Msk;

    /* Set OTG as USB Host role */
    SYS->USBPHY = SYS_USBPHY_HSUSBEN_Msk | (0x1 << SYS_USBPHY_HSUSBROLE_Pos) | SYS_USBPHY_USBEN_Msk | SYS_USBPHY_SBO_Msk | (0x1 << SYS_USBPHY_USBROLE_Pos);
    delay_us(20);
    SYS->USBPHY |= SYS_USBPHY_HSUSBACT_Msk;

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* USB_VBUS_EN (USB 1.1 VBUS power enable pin) multi-function pin - PB.15     */
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~SYS_GPB_MFPH_PB15MFP_Msk) | SYS_GPB_MFPH_PB15MFP_USB_VBUS_EN;

    /* USB_VBUS_ST (USB 1.1 over-current detect pin) multi-function pin - PC.14   */
    SYS->GPC_MFPH = (SYS->GPC_MFPH & ~SYS_GPC_MFPH_PC14MFP_Msk) | SYS_GPC_MFPH_PC14MFP_USB_VBUS_ST;

    /* HSUSB_VBUS_EN (USB 2.0 VBUS power enable pin) multi-function pin - PB.10   */
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~SYS_GPB_MFPH_PB10MFP_Msk) | SYS_GPB_MFPH_PB10MFP_HSUSB_VBUS_EN;

    /* HSUSB_VBUS_ST (USB 2.0 over-current detect pin) multi-function pin - PB.11 */
    SYS->GPB_MFPH = (SYS->GPB_MFPH & ~SYS_GPB_MFPH_PB11MFP_Msk) | SYS_GPB_MFPH_PB11MFP_HSUSB_VBUS_ST;

    /* USB 1.1 port multi-function pin VBUS, D+, D-, and ID pins */
    SYS->GPA_MFPH &= ~(SYS_GPA_MFPH_PA12MFP_Msk | SYS_GPA_MFPH_PA13MFP_Msk |
                       SYS_GPA_MFPH_PA14MFP_Msk | SYS_GPA_MFPH_PA15MFP_Msk);
    SYS->GPA_MFPH |= SYS_GPA_MFPH_PA12MFP_USB_VBUS | SYS_GPA_MFPH_PA13MFP_USB_D_N |
                     SYS_GPA_MFPH_PA14MFP_USB_D_P | SYS_GPA_MFPH_PA15MFP_USB_OTG_ID;

    /* Lock protected registers */
    SYS_LockReg();
}

void UART0_Init(void)
{
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

/**
 *  @brief  Audio-in data callback function.
 *          UAC driver notify user that audio-in data has been moved into user audio-in buffer,
 *          which is provided by user application via UAC_InstallIsoInCbFun().
 *  @param[in] dev    Audio Class device
 *  @param[in] data   Available audio-in data, which is located in user audio-in buffer.
 *  @param[in] len    Length of available audio-in data started from <data>.
 *  @return   UAC driver does not check this return value.
 */
int audio_in_callback(UAC_DEV_T *dev, uint8_t *data, int len)
{
    au_in_cnt += len;
    //printf("I %x,%x\n", (int)data & 0xffff, len);   // UART send too many will cause ISO transfer time overrun

    // Add your code here to get audio-in data ...
    // For example, memcpy(audio_record_buffer, data, len);
    // . . .

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
    au_out_cnt += len;
    //printf("O %x,%x\n", (int)data & 0xffff, len);   // UART send too many will cause ISO transfer time overrun

    // Add your code here to put audio-out data ...
    // For example, memcpy(data, playback_buffer, actual_len);
    //              return actual_len;
    // . . .

    return 192;   // for 48000 stereo Hz
}


void  uac_control_example(UAC_DEV_T *uac_dev)
{
    uint16_t   val16;
    uint32_t   srate[4];
    uint8_t    val8;
    uint8_t    data[8];
    int        i, ret;
    uint32_t   val32;

    vol_max = vol_min = vol_res = 0;

    printf("\nGet channel information ===>\n");

    /*-------------------------------------------------------------*/
    /*  Get channel number information                             */
    /*-------------------------------------------------------------*/
    ret = usbh_uac_get_channel_number(uac_dev, UAC_SPEAKER);
    if(ret < 0)
        printf("    Failed to get speaker's channel number.\n");
    else
        printf("    Speaker: %d\n", ret);

    ret = usbh_uac_get_channel_number(uac_dev, UAC_MICROPHONE);
    if (ret < 0)
        printf("    Failed to get microphone's channel number.\n");
    else
    {
        printf("    Microphone: %d\n", ret);
    }

    printf("\nGet subframe bit resolution ===>\n");

    /*-------------------------------------------------------------*/
    /*  Get audio subframe bit resolution information              */
    /*-------------------------------------------------------------*/
    ret = usbh_uac_get_bit_resolution(uac_dev, UAC_SPEAKER, &val8);
    if(ret < 0)
        printf("    Failed to get speaker's bit resoltion.\n");
    else
    {
        printf("    Speaker audio subframe size: %d bytes\n", val8);
        printf("    Speaker subframe bit resolution: %d\n", ret);
    }

    ret = usbh_uac_get_bit_resolution(uac_dev, UAC_MICROPHONE, &val8);
    if(ret < 0)
        printf("    Failed to get microphone's bit resoltion.\n");
    else
    {
        printf("    Microphone audio subframe size: %d bytes\n", val8);
        printf("    Microphone subframe bit resolution: %d\n", ret);
    }

    printf("\nGet sampling rate list ===>\n");

    /*-------------------------------------------------------------*/
    /*  Get audio subframe bit resolution information              */
    /*-------------------------------------------------------------*/
    ret = usbh_uac_get_sampling_rate(uac_dev, UAC_SPEAKER, (uint32_t *)&srate[0], 4, &val8);
    if(ret < 0)
        printf("    Failed to get speaker's sampling rate.\n");
    else
    {
        if(val8 == 0)
            printf("    Speaker sampling rate range: %d ~ %d Hz\n", srate[0], srate[1]);
        else
        {
            for(i = 0; i < val8; i++)
                printf("    Speaker sampling rate: %d\n", srate[i]);
        }
    }

    ret = usbh_uac_get_sampling_rate(uac_dev, UAC_MICROPHONE, (uint32_t *)&srate[0], 4, &val8);
    if(ret < 0)
        printf("    Failed to get microphone's sampling rate.\n");
    else
    {
        if(val8 == 0)
            printf("    Microphone sampling rate range: %d ~ %d Hz\n", srate[0], srate[1]);
        else
        {
            for(i = 0; i < val8; i++)
                printf("    Microphone sampling rate: %d\n", srate[i]);
        }
    }

    printf("\nSpeaker mute control ===>\n");

    /*-------------------------------------------------------------*/
    /*  Get current mute value of UAC device's speaker.            */
    /*-------------------------------------------------------------*/
    if (usbh_uac_mute_control(uac_dev, UAC_SPEAKER, UAC_GET_CUR, UAC_CH_MASTER, data) == UAC_RET_OK)
    {
        printf("    Speaker mute state is %d.\n", data[0]);
    }
    else
        printf("    Failed to get speaker mute state!\n");

    printf("\nSpeaker L(F) volume control ===>\n");

#if 0
    /*--------------------------------------------------------------------------*/
    /*  Get current volume value of UAC device's speaker left channel.          */
    /*--------------------------------------------------------------------------*/
    if (usbh_uac_vol_control(uac_dev, UAC_SPEAKER, UAC_GET_CUR, UAC_CH_LEFT_FRONT, &val16) == UAC_RET_OK)
        printf("    Speaker L(F) volume is 0x%x.\n", val16);
    else
        printf("    Failed to get seaker L(F) volume!\n");

    /*--------------------------------------------------------------------------*/
    /*  Get minimum volume value of UAC device's speaker left channel.          */
    /*--------------------------------------------------------------------------*/
    if(usbh_uac_vol_control(uac_dev, UAC_SPEAKER, UAC_GET_MIN, UAC_CH_LEFT_FRONT, &val16) == UAC_RET_OK)
        printf("    Speaker L(F) minimum volume is 0x%x.\n", val16);
    else
        printf("    Failed to get speaker L(F) minimum volume!\n");

    /*--------------------------------------------------------------------------*/
    /*  Get maximum volume value of UAC device's speaker left channel.          */
    /*--------------------------------------------------------------------------*/
    if(usbh_uac_vol_control(uac_dev, UAC_SPEAKER, UAC_GET_MAX, UAC_CH_LEFT_FRONT, &val16) == UAC_RET_OK)
        printf("    Speaker L(F) maximum volume is 0x%x.\n", val16);
    else
        printf("    Failed to get speaker L(F) maximum volume!\n");

    /*--------------------------------------------------------------------------*/
    /*  Get volume resolution of UAC device's speaker left channel.             */
    /*--------------------------------------------------------------------------*/
    if(usbh_uac_vol_control(uac_dev, UAC_SPEAKER, UAC_GET_RES, UAC_CH_LEFT_FRONT, &val16) == UAC_RET_OK)
        printf("    Speaker L(F) volume resolution is 0x%x.\n", val16);
    else
        printf("    Failed to get speaker L(F) volume resolution!\n");

    printf("\nSpeaker R(F) volume control ===>\n");

    /*--------------------------------------------------------------------------*/
    /*  Get current volume value of UAC device's speaker right channel.         */
    /*--------------------------------------------------------------------------*/
    if(usbh_uac_vol_control(uac_dev, UAC_SPEAKER, UAC_GET_CUR, UAC_CH_RIGHT_FRONT, &val16) == UAC_RET_OK)
        printf("    Speaker R(F) volume is 0x%x.\n", val16);
    else
        printf("    Failed to get speaker R(F) volume!\n");

    /*--------------------------------------------------------------------------*/
    /*  Get minimum volume value of UAC device's speaker right channel.         */
    /*--------------------------------------------------------------------------*/
    if(usbh_uac_vol_control(uac_dev, UAC_SPEAKER, UAC_GET_MIN, UAC_CH_RIGHT_FRONT, &val16) == UAC_RET_OK)
        printf("    Speaker R(F) minimum volume is 0x%x.\n", val16);
    else
        printf("    Failed to get speaker R(F) minimum volume!\n");

    /*--------------------------------------------------------------------------*/
    /*  Get maximum volume value of UAC device's speaker right channel.         */
    /*--------------------------------------------------------------------------*/
    if(usbh_uac_vol_control(uac_dev, UAC_SPEAKER, UAC_GET_MAX, UAC_CH_RIGHT_FRONT, &val16) == UAC_RET_OK)
        printf("    Speaker R(F) maximum volume is 0x%x.\n", val16);
    else
        printf("    Failed to get speaker R(F) maximum volume!\n");

    /*--------------------------------------------------------------------------*/
    /*  Get volume resolution of UAC device's speaker right channel.            */
    /*--------------------------------------------------------------------------*/
    if(usbh_uac_vol_control(uac_dev, UAC_SPEAKER, UAC_GET_RES, UAC_CH_RIGHT_FRONT, &val16) == UAC_RET_OK)
        printf("    Speaker R(F) volume resolution is 0x%x.\n", val16);
    else
        printf("    Failed to get speaker R(F) volume resolution!\n");
#endif

    printf("\nSpeaker master volume control ===>\n");

    /*--------------------------------------------------------------------------*/
    /*  Get minimum volume value of UAC device's speaker master channel.        */
    /*--------------------------------------------------------------------------*/
    if(usbh_uac_vol_control(uac_dev, UAC_SPEAKER, UAC_GET_MIN, UAC_CH_MASTER, &val16) == UAC_RET_OK)
        printf("    Speaker minimum master volume is 0x%x.\n", val16);
    else
        printf("    Failed to get speaker master minimum volume!\n");

    /*--------------------------------------------------------------------------*/
    /*  Get maximum volume value of UAC device's speaker master channel.        */
    /*--------------------------------------------------------------------------*/
    if(usbh_uac_vol_control(uac_dev, UAC_SPEAKER, UAC_GET_MAX, UAC_CH_MASTER, &val16) == UAC_RET_OK)
        printf("    Speaker maximum master volume is 0x%x.\n", val16);
    else
        printf("    Failed to get speaker maximum master volume!\n");

    /*--------------------------------------------------------------------------*/
    /*  Get volume resolution of UAC device's speaker master channel.           */
    /*--------------------------------------------------------------------------*/
    if(usbh_uac_vol_control(uac_dev, UAC_SPEAKER, UAC_GET_RES, UAC_CH_MASTER, &val16) == UAC_RET_OK)
        printf("    Speaker master volume resolution is 0x%x.\n", val16);
    else
        printf("    Failed to get speaker master volume resolution!\n");

    /*--------------------------------------------------------------------------*/
    /*  Get current volume value of UAC device's speaker master channel.        */
    /*--------------------------------------------------------------------------*/
    if(usbh_uac_vol_control(uac_dev, UAC_SPEAKER, UAC_GET_CUR, UAC_CH_MASTER, &val16) == UAC_RET_OK)
        printf("    Speaker master volume is 0x%x.\n", val16);
    else
        printf("    Failed to get speaker master volume!\n");

#if 0
    printf("\nMixer master volume control ===>\n");

    /*-------------------------------------------------------------*/
    /*  Get current mute value of UAC device's microphone.         */
    /*-------------------------------------------------------------*/
    printf("\nMicrophone mute control ===>\n");
    if(usbh_uac_mute_control(uac_dev, UAC_MICROPHONE, UAC_GET_CUR, UAC_CH_MASTER, data) == UAC_RET_OK)
        printf("    Microphone mute state is %d.\n", data[0]);
    else
        printf("    Failed to get microphone mute state!\n");
#endif

    printf("\nMicrophone volume control ===>\n");

    /*-------------------------------------------------------------*/
    /*  Get current volume value of UAC device's microphone.       */
    /*-------------------------------------------------------------*/
    if(usbh_uac_vol_control(uac_dev, UAC_MICROPHONE, UAC_GET_CUR, UAC_CH_MASTER, &vol_cur) == UAC_RET_OK)
        printf("    Microphone current volume is 0x%x.\n", vol_cur);
    else
        printf("    Failed to get microphone current volume!\n");

    /*-------------------------------------------------------------*/
    /*  Get minimum volume value of UAC device's microphone.       */
    /*-------------------------------------------------------------*/
    if(usbh_uac_vol_control(uac_dev, UAC_MICROPHONE, UAC_GET_MIN, UAC_CH_MASTER, &vol_min) == UAC_RET_OK)
        printf("    Microphone minimum volume is 0x%x.\n", vol_min);
    else
        printf("    Failed to get microphone minimum volume!\n");

    /*-------------------------------------------------------------*/
    /*  Get maximum volume value of UAC device's microphone.       */
    /*-------------------------------------------------------------*/
    if(usbh_uac_vol_control(uac_dev, UAC_MICROPHONE, UAC_GET_MAX, UAC_CH_MASTER, &vol_max) == UAC_RET_OK)
        printf("    Microphone maximum volume is 0x%x.\n", vol_max);
    else
        printf("    Failed to get microphone maximum volume!\n");

    /*-------------------------------------------------------------*/
    /*  Get resolution of UAC device's microphone volume value.    */
    /*-------------------------------------------------------------*/
    if(usbh_uac_vol_control(uac_dev, UAC_MICROPHONE, UAC_GET_RES, UAC_CH_MASTER, &vol_res) == UAC_RET_OK)
        printf("    Microphone volume resolution is 0x%x.\n", vol_res);
    else
        printf("    Failed to get microphone volume resolution!\n");

#if 0
    /*-------------------------------------------------------------*/
    /*  Get current auto-gain setting of UAC device's microphone.  */
    /*-------------------------------------------------------------*/
    printf("\nMicrophone automatic gain control ===>\n");
    if(UAC_AutoGainControl(uac_dev, UAC_MICROPHONE, UAC_GET_CUR, UAC_CH_MASTER, data) == UAC_RET_OK)
        printf("    Microphone auto gain is %s.\n", data[0] ? "ON" : "OFF");
    else
        printf("    Failed to get microphone auto-gain state!\n");
#endif

    printf("\nSampling rate control ===>\n");

    /*-------------------------------------------------------------*/
    /*  Get current sampling rate value of UAC device's speaker.   */
    /*-------------------------------------------------------------*/
    if (usbh_uac_sampling_rate_control(uac_dev, UAC_SPEAKER, UAC_GET_CUR, &val32) == UAC_RET_OK)
        printf("    Speaker's current sampling rate is %d.\n", val32);
    else
        printf("    Failed to get speaker's current sampling rate!\n");

    /*-------------------------------------------------------------*/
    /*  Set new sampling rate value of UAC device's speaker.       */
    /*-------------------------------------------------------------*/
    val32 = 48000;
    if (usbh_uac_sampling_rate_control(uac_dev, UAC_SPEAKER, UAC_SET_CUR, &val32) != UAC_RET_OK)
        printf("    Failed to set Speaker's current sampling rate %d.\n", val32);

    if(usbh_uac_sampling_rate_control(uac_dev, UAC_SPEAKER, UAC_GET_CUR, &val32) == UAC_RET_OK)
        printf("    Speaker's current sampling rate is %d.\n", val32);
    else
        printf("    Failed to get speaker's current sampling rate!\n");

    /*-------------------------------------------------------------*/
    /*  Get current sampling rate value of UAC device's microphone.*/
    /*-------------------------------------------------------------*/
    if(usbh_uac_sampling_rate_control(uac_dev, UAC_MICROPHONE, UAC_GET_CUR, &val32) == UAC_RET_OK)
        printf("    Microphone's current sampling rate is %d.\n", val32);
    else
        printf("    Failed to get microphone's current sampling rate!\n");

    /*-------------------------------------------------------------*/
    /*  Set new sampling rate value of UAC device's microphone.    */
    /*-------------------------------------------------------------*/
    val32 = 48000;
    if (usbh_uac_sampling_rate_control(uac_dev, UAC_MICROPHONE, UAC_SET_CUR, &val32) != UAC_RET_OK)
        printf("    Failed to set microphone's current sampling rate!\n");

    if (usbh_uac_sampling_rate_control(uac_dev, UAC_MICROPHONE, UAC_GET_CUR, &val32) == UAC_RET_OK)
        printf("    Microphone's current sampling rate is %d.\n", val32);
    else
        printf("    Failed to get microphone's current sampling rate!\n");
}


int32_t main(void)
{
    UAC_DEV_T  *uac_dev;
    int        ch;
    uint16_t   val16;

    SYS_Init();                        /* Init System, IP clock and multi-function I/O */

    UART0_Init();                      /* Initialize UART0 */

    printf("\n\n");
    printf("+----------------------------------------------+\n");
    printf("|                                              |\n");
    printf("|     USB Host Audio Class sample program      |\n");
    printf("|                                              |\n");
    printf("+----------------------------------------------+\n");

    enable_sys_tick(100);

    usbh_core_init();
    usbh_uac_init();
    usbh_memory_used();

    while(1)
    {
        if (usbh_pooling_hubs())              /* USB Host port detect polling and management */
        {
            /*
             *  Has hub port event.
             */

            uac_dev = usbh_uac_get_device_list();
            if (uac_dev == NULL)
                continue;

            if (uac_dev != NULL)                  /* should be newly connected UAC device        */
            {
                usbh_uac_open(uac_dev);

                uac_control_example(uac_dev);

                usbh_uac_start_audio_out(uac_dev, audio_out_callback);

                usbh_uac_start_audio_in(uac_dev, audio_in_callback);
            }
        }

        if (uac_dev == NULL)
        {
            au_in_cnt = 0;
            au_out_cnt = 0;

            if (!kbhit())
            {
                ch = getchar();
                usbh_memory_used();
            }

            continue;
        }

        if (!kbhit())
        {
            ch = getchar();

            if ((ch == '+') && (vol_cur + vol_res <= vol_max))
            {
                printf("+");
                val16 = vol_cur+vol_res;
                if (usbh_uac_vol_control(uac_dev, UAC_MICROPHONE, UAC_SET_CUR, UAC_CH_MASTER, &val16) == UAC_RET_OK)
                {
                    printf("    Microphone set volume 0x%x success.\n", val16);
                    vol_cur = val16;
                }
                else
                    printf("    Failed to set microphone volume 0x%x!\n", val16);
            }
            else if ((ch == '-') && (vol_cur - vol_res >= vol_min))
            {
                printf("-");
                val16 = vol_cur-vol_res;
                if (usbh_uac_vol_control(uac_dev, UAC_MICROPHONE, UAC_SET_CUR, UAC_CH_MASTER, &val16) == UAC_RET_OK)
                {
                    printf("    Microphone set volume 0x%x success.\n", val16);
                    vol_cur = val16;
                }
                else
                    printf("    Failed to set microphone volume 0x%x!\n", val16);
            }
            else if ((ch == '0') && (vol_cur - vol_res >= vol_min))
            {
                if (usbh_uac_vol_control(uac_dev, UAC_MICROPHONE, UAC_GET_CUR, UAC_CH_MASTER, &vol_cur) == UAC_RET_OK)
                    printf("    Microphone current volume is 0x%x.\n", vol_cur);
                else
                    printf("    Failed to get microphone current volume!\n");
            }
            else
            {
                printf("IN: %d, OUT: %d\n", au_in_cnt, au_out_cnt);
                usbh_memory_used();
            }

        }  /* end of kbhit() */
    }
}


/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
