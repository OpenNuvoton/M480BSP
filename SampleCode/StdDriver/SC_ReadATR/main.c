/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Read the smartcard ATR from smartcard 1 interface.
 *
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>
#include "NuMicro.h"
#include "sclib.h"

#define SC_INTF 0  // Smartcard interface 0

/**
  * @brief  The interrupt services routine of smartcard port 0
  * @param  None
  * @retval None
  */
void SC0_IRQHandler(void)
{
    /* Please don't remove any of the function calls below */
    // Card insert/remove event occurred, no need to check other event...
    if(SCLIB_CheckCDEvent(SC_INTF))
        return;
    // Check if there's any timeout event occurs. If so, it usually indicates an error
    SCLIB_CheckTimeOutEvent(SC_INTF);
    // Check transmit and receive interrupt, all data transmission take place in this function
    SCLIB_CheckTxRxEvent(SC_INTF);
    /*
        Check if there's any transmission error occurred (e.g. parity error, frame error...)
        These errors will induce SCLIB to deactivation smartcard eventually.
    */
    SCLIB_CheckErrorEvent(SC_INTF);

    return;
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

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(FREQ_192MHZ);

    /* Set both PCLK0 and PCLK1 as HCLK/2 */
    CLK->PCLKDIV = CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2;

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);
    CLK_EnableModuleClock(SC0_MODULE);


    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));
    // Valid smartcard clock rate is from 1MHz to 4MHz, we set it to 4MHz
    CLK_SetModuleClock(SC0_MODULE, CLK_CLKSEL3_SC0SEL_HXT, CLK_CLKDIV1_SC0(3));

    /* Update System Core Clock */
    /* User can use SystemCoreClockUpdate() to calculate SystemCoreClock. */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);
    /* Set PA0~4 for SC0 interface */
    SYS->GPA_MFPL |= SYS_GPA_MFPL_PA0MFP_SC0_CLK |
                     SYS_GPA_MFPL_PA1MFP_SC0_DAT |
                     SYS_GPA_MFPL_PA2MFP_SC0_RST |
                     SYS_GPA_MFPL_PA3MFP_SC0_PWR |
                     SYS_GPA_MFPL_PA4MFP_SC0_nCD;

    /* Lock protected registers */
    SYS_LockReg();
}

int main(void)
{
    SCLIB_CARD_INFO_T s_info;
    int retval, i;

    /* Init System, IP clock and multi-function I/O
       In the end of SYS_Init() will issue SYS_LockReg()
       to lock protected register. If user want to write
       protected register, please issue SYS_UnlockReg()
       to unlock protected register if necessary */
    SYS_Init();

    /* Init UART to 115200-8n1 for print message */
    UART_Open(UART0, 115200);

    printf("\nThis sample code reads ATR from smartcard\n");

    /*
        Open smartcard interface 0. CD pin state low indicates card insert and PWR pin low raise VCC pin to card
        The second and third parameter needs to be set according to the board design
    */
    SC_Open(SC0, SC_PIN_STATE_LOW, SC_PIN_STATE_HIGH);
    NVIC_EnableIRQ(SC0_IRQn);

    // Wait 'til card insert
    while(SC_IsCardInserted(SC0) == FALSE);

    /*
        Activate slot 0, and disable EMV2000 check during card activation
        EMV is a technical standard for smart payment cards and for payment terminals and automated teller
        machines that can accept them. It has a stricter checking rule than ISO 7816-3. If the second
        parameter set as TRUE, SCLIB will report activation failure for cards comply with ISO 7816 but not EMV2000
    */
    retval = SCLIB_Activate(SC_INTF, FALSE);

    if(retval == SCLIB_SUCCESS)
    {
        /*
            Use SCLIB_GetCardInfo to get information about the card, which includes ATR.

            An Answer To Reset (ATR) is a message output by a contact Smart Card conforming to
            ISO/IEC 7816 standards, following electrical reset of the card's chip by a card reader.
            The ATR conveys information about the communication parameters proposed by the card,
            and the card's nature and state.                                --Wikipedia
        */
        SCLIB_GetCardInfo(SC_INTF, &s_info);
        printf("ATR: ");
        for(i = 0; i < s_info.ATR_Len; i++)
            printf("%02x ", s_info.ATR_Buf[i]);
        printf("\n");
    }
    else
        printf("Smartcard activate failed\n");

    // No operating system, so we have no where to go, just loop forever.
    while(1);
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/


