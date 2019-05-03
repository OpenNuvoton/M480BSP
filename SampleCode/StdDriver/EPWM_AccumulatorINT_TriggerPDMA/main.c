/**************************************************************************//**
 * @file     main.c
 * @version  V3.00
 * @brief    Demonstrate EPWM accumulator interrupt trigger PDMA.
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

#define PLL_CLOCK       192000000


/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
uint16_t g_u32Period[2] = {31999,15999};
volatile uint32_t g_u32IsTestOver = 0;

/**
 * @brief       EPWM1 IRQ Handler
 *
 * @param       None
 *
 * @return      None
 *
 * @details     ISR to handle EPWM1 interrupt event
 */
void EPWM1P1_IRQHandler(void)
{

}

/**
 * @brief       PDMA IRQ Handler
 *
 * @param       None
 *
 * @return      None
 *
 * @details     ISR to handle PDMA interrupt event
 */
void PDMA_IRQHandler(void)
{
    uint32_t status = PDMA_GET_INT_STATUS(PDMA);

    if(status & PDMA_INTSTS_ABTIF_Msk)    /* abort */
    {
        if(PDMA_GET_ABORT_STS(PDMA) & PDMA_ABTSTS_ABTIF0_Msk)
            g_u32IsTestOver = 2;
        PDMA_CLR_ABORT_FLAG(PDMA,PDMA_ABTSTS_ABTIF0_Msk);
    }
    else if(status & PDMA_INTSTS_TDIF_Msk)      /* done */
    {
        if(PDMA_GET_TD_STS(PDMA) & PDMA_TDSTS_TDIF0_Msk)
            g_u32IsTestOver = 1;
        PDMA_CLR_TD_FLAG(PDMA,PDMA_TDSTS_TDIF0_Msk);
    }
    else
        printf("unknown interrupt !!\n");
}


void SYS_Init(void)
{

    /* Set XT1_OUT(PF.2) and XT1_IN(PF.3) to input mode */
    PF->MODE &= ~(GPIO_MODE_MODE2_Msk | GPIO_MODE_MODE3_Msk);

    /* Enable HXT clock (external XTAL 12MHz) */
    CLK_EnableXtalRC(CLK_PWRCTL_HXTEN_Msk);

    /* Wait for HXT clock ready */
    CLK_WaitClockReady(CLK_STATUS_HXTSTB_Msk);

    /* Set core clock as PLL_CLOCK from PLL */
    CLK_SetCoreClock(PLL_CLOCK);

    /* Set PCLK0 = PCLK1 = HCLK/2 */
    CLK->PCLKDIV = (CLK_PCLKDIV_APB0DIV_DIV2 | CLK_PCLKDIV_APB1DIV_DIV2);

    /* Enable IP module clock */
    CLK_EnableModuleClock(EPWM1_MODULE);

    /* EPWM clock frequency is set double to PCLK: select EPWM module clock source as PLL */
    CLK_SetModuleClock(EPWM1_MODULE, CLK_CLKSEL2_EPWM1SEL_PLL, (uint32_t)NULL);

    /* Enable PDMA module clock */
    CLK_EnableModuleClock(PDMA_MODULE);

    /* Enable UART module clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Select UART module clock source as HXT and UART module clock divider as 1 */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);
    /* Set PC.12 multi-function pins for EPWM1 Channel 0 */
    SYS->GPC_MFPH &= ~SYS_GPC_MFPH_PC12MFP_Msk;
    SYS->GPC_MFPH |= SYS_GPC_MFPH_PC12MFP_EPWM1_CH0;
}

void UART0_Init()
{
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
}

int32_t main(void)
{
    /* Init System, IP clock and multi-function I/O
       In the end of SYS_Init() will issue SYS_LockReg()
       to lock protected register. If user want to write
       protected register, please issue SYS_UnlockReg()
       to unlock protected register if necessary */

    /* Unlock protected registers */
    SYS_UnlockReg();

    /* Init System, IP clock and multi-function I/O */
    SYS_Init();

    /* Lock protected registers */
    SYS_LockReg();

    /* Init UART to 115200-8n1 for print message */
    UART0_Init();

    printf("\n\nCPU @ %dHz(PLL@ %dHz)\n", SystemCoreClock, PllClock);
    printf("EPWM1 clock is from %s\n", (CLK->CLKSEL2 & CLK_CLKSEL2_EPWM1SEL_Msk) ? "CPU" : "PLL");
    printf("+------------------------------------------------------------------------+\n");
    printf("|                          EPWM Driver Sample Code                        |\n");
    printf("|                                                                        |\n");
    printf("+------------------------------------------------------------------------+\n");
    printf("  This sample code demonstrate EPWM1 channel 0 accumulator interrupt trigger PDMA.\n");
    printf("  When accumulator interrupt happens, EPWM1 channel 0 period register will be updated \n");
    printf("  to g_u32Count array content, 31999(0x7CFF), by PDMA.\n");

    printf("\n\nPress any key to start EPWM1 channel 0.\n");
    getchar();

    /*--------------------------------------------------------------------------------------*/
    /* Set the EPWM1 Channel 0 as EPWM output function.                                       */
    /*--------------------------------------------------------------------------------------*/

    /* Assume EPWM output frequency is 250Hz and duty ratio is 30%, user can calculate EPWM settings by follows.
       duty ratio = (CMR+1)/(CNR+1)
       cycle time = CNR+1
       High level = CMR+1
       EPWM clock source frequency = PCLK = 96000000
       (CNR+1) = EPWM clock source frequency/prescaler/EPWM output frequency
               = 192000000/10/300 = 64000
       (Note: CNR is 16 bits, so if calculated value is larger than 65536, user should increase prescale value.)
       CNR = 63999
       duty ratio = 30% ==> (CMR+1)/(CNR+1) = 30%
       CMR = 19199
       Prescale value is 9 : prescaler= 10
    */

    /* Set EPWM1 channel 0 output configuration */
    EPWM_ConfigOutputChannel(EPWM1, 0, 300, 30);

    /* Enable EPWM Output path for EPWM1 channel 0 */
    EPWM_EnableOutput(EPWM1, EPWM_CH_0_MASK);

    /* Enable EPWM1 channel 0 accumulator, interrupt count 50, accumulator source select to zero point */
    EPWM_EnableAcc(EPWM1, 0, 50, EPWM_IFA_ZERO_POINT);

    /* Enable EPWM1 channel 0 accumulator interrupt */
    EPWM_EnableAccInt(EPWM1, 0);

    /* Enable EPWM1 channel 0 accumulator interrupt trigger PDMA */
    EPWM_EnableAccPDMA(EPWM1, 0);

    /* Enable Timer for EPWM1 channel 0 */
    EPWM_Start(EPWM1, EPWM_CH_0_MASK);

    /*--------------------------------------------------------------------------------------*/
    /* Configure PDMA peripheral mode form memory to EPWM                                    */
    /*--------------------------------------------------------------------------------------*/
    /* Open Channel 0 */
    PDMA_Open(PDMA,BIT0);

    /* Transfer width is half word(16 bit) and transfer count is 1 */
    PDMA_SetTransferCnt(PDMA,0, PDMA_WIDTH_16, 1);

    /* Set source address as g_u32Count array(increment) and destination address as EPWM1 channel 0 period register(no increment) */
    PDMA_SetTransferAddr(PDMA,0, (uint32_t)&g_u32Period[0], PDMA_SAR_INC, (uint32_t)&(EPWM1->PERIOD[0]), PDMA_DAR_FIX);

    /* Select PDMA request source as PDMA_EPWM1_CH0_TX(EPWM1 channel 0 accumulator interrupt) */
    PDMA_SetTransferMode(PDMA,0, PDMA_EPWM1_CH0_TX, FALSE, 0);

    /* Set PDMA as single request type for EPWM */
    PDMA_SetBurstType(PDMA,0, PDMA_REQ_SINGLE, PDMA_BURST_1);

    PDMA_EnableInt(PDMA,0, PDMA_INT_TRANS_DONE);
    NVIC_EnableIRQ(PDMA_IRQn);

    g_u32IsTestOver = 0;

    /* Wait for PDMA transfer done */
    while (g_u32IsTestOver != 1);

    printf("\n\nEPWM1 channel0 period register is updated to %d(0x%x)\n",EPWM_GET_CNR(EPWM1, 0),EPWM_GET_CNR(EPWM1, 0));
    printf("Press any key to stop EPWM1 channel 0.\n");
    getchar();

    /* Set EPWM1 channel 0 loaded value as 0 */
    EPWM_Stop(EPWM1, EPWM_CH_0_MASK);

    /* Wait until EPWM1 channel 0 Timer Stop */
    while((EPWM1->CNT[0] & EPWM_CNT0_CNT_Msk) != 0);

    /* Disable Timer for EPWM1 channel 0 */
    EPWM_ForceStop(EPWM1, EPWM_CH_0_MASK);

    /* Disable EPWM Output path for EPWM1 channel 0 */
    EPWM_DisableOutput(EPWM1, EPWM_CH_0_MASK);

    /* Disable PDMA NVIC */
    NVIC_DisableIRQ(PDMA_IRQn);

    PDMA_Close(PDMA);

    while(1);
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
