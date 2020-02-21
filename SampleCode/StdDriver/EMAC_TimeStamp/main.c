/*************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Demonstrate the usage of Ethernet time stamp function.
 *           It sets current time to 1000 second and prints out
 *           current time every second. It also sets an alarm at
 *           1010 second. And rewind current time by 5 seconds after
 *           the alarm.
 *
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK           192000000

// Our MAC address
uint8_t g_au8MacAddr[6] = {0x00, 0x00, 0x00, 0x59, 0x16, 0x88};

/**
  * @brief  EMAC Tx interrupt handler.
  * @param  None
  * @return None
  */
void EMAC_TX_IRQHandler(void)
{

    if(EMAC_GET_ALARM_FLAG())
    {
        printf("Alarm interrupt!! Rewind current time by 5 second : 0 nano second\n");
        // First parameter set 1 means rewind current time, second parameter is second, and third parameter is nano second
        EMAC_UpdateTime(1, 5, 0);
    }

    // This sample sends no packet out, so this must be an alarm interrupt
    EMAC_CLR_ALARM_FLAG();

}


void SYS_Init(void)
{

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable External XTAL (4~24 MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Waiting for 12MHz clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Switch HCLK clock source to HXT */
    CLK_SetHCLK(CLK_CLKSEL0_HCLKSEL_HXT,CLK_CLKDIV0_HCLK(1));

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(EMAC_MODULE);

    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    // Configure MDC clock rate to HCLK / (127 + 1) = 1.5 MHz if system is running at 192 MHz
    CLK_SetModuleClock(EMAC_MODULE, 0, CLK_CLKDIV3_EMAC(127));

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);
    // Configure RMII pins
    SYS->GPA_MFPL |= SYS_GPA_MFPL_PA6MFP_EMAC_RMII_RXERR | SYS_GPA_MFPL_PA7MFP_EMAC_RMII_CRSDV;
    SYS->GPC_MFPL |= SYS_GPC_MFPL_PC6MFP_EMAC_RMII_RXD1 | SYS_GPC_MFPL_PC7MFP_EMAC_RMII_RXD0;
    SYS->GPC_MFPH |= SYS_GPC_MFPH_PC8MFP_EMAC_RMII_REFCLK;
    SYS->GPE_MFPH |= SYS_GPE_MFPH_PE8MFP_EMAC_RMII_MDC |
                     SYS_GPE_MFPH_PE9MFP_EMAC_RMII_MDIO |
                     SYS_GPE_MFPH_PE10MFP_EMAC_RMII_TXD0 |
                     SYS_GPE_MFPH_PE11MFP_EMAC_RMII_TXD1 |
                     SYS_GPE_MFPH_PE12MFP_EMAC_RMII_TXEN;

    // Enable high slew rate on all RMII TX output pins
    PE->SLEWCTL = (GPIO_SLEWCTL_HIGH << GPIO_SLEWCTL_HSREN10_Pos) |
                  (GPIO_SLEWCTL_HIGH << GPIO_SLEWCTL_HSREN11_Pos) |
                  (GPIO_SLEWCTL_HIGH << GPIO_SLEWCTL_HSREN12_Pos);

    /* Lock protected registers */
    SYS_LockReg();

}



// This sample application can response to ICMP ECHO packets (ping)
// IP address is configure with DHCP, but if a lease cannot be acquired, a static IP will be used.
int main(void)
{
    uint32_t s = 0, ns = 0; // current time
    uint32_t old_s = 0;

    SYS_Init();

    UART_Open(UART0, 115200);

    printf("EMAC Timer Stamp Sample\n");

    // Open EMAC interface. No need to enable Rx and Tx in this sample
    // But still connect Ethernet cable to pass auto-negotiation.
    EMAC_Open(g_au8MacAddr);

    // Init phy
    EMAC_PhyInit();

    // Init time stamp and set current time to 1000s:0ns
    EMAC_EnableTS(1000, 0);

    // Time stamp alarm triggers Tx interrupt, so no need to enable Rx interrupt in this sample
    NVIC_EnableIRQ(EMAC_TX_IRQn);


    // Set Alarm at 1010s:0ns
    EMAC_EnableAlarm(1010, 0);

    while(1)
    {
        EMAC_GetTime(&s, &ns);
        if(s != old_s)
        {
            printf("Current time %ds. %dns\n", s, ns);
            old_s = s;
        }
    }

}


/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
