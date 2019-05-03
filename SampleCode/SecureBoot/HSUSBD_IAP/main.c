/**************************************************************************//**
 * @file     main.c
 * @version  2.0.0
 * @brief    Use MKROM API to do internal ISP. This sample code is run at APROM,
 *           this sample will load an image to LDROM, and than doing Secure boot
 *           ISP to update APROM. After finish firmware update, remember to reset
 *           the system.
 *           The LDROM sample code is Secure boot ISP function.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include "NuMicro.h"

typedef void (FUNC_PTR)(void);

extern uint32_t  loaderImage1Base, loaderImage1Limit;   /* symbol of image start and end */


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

    /* Select IP clock source */
    CLK_SetModuleClock(UART0_MODULE, CLK_CLKSEL1_UART0SEL_HXT, CLK_CLKDIV0_UART0(1));

    /* Enable IP clock */
    CLK_EnableModuleClock(UART0_MODULE);

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

}


/**
  * @brief    Check User Configuration CONFIG0 bit 6 IAP boot setting. If it's not boot with IAP
  *           mode, modify it and execute a chip reset to make it take effect.
  * @return   Is boot with IAP mode or not.
  * @retval   0   Success.
  * @retval   -1  Failed on reading or programming User Configuration.
  */
static int  set_IAP_boot_mode(void)
{
    uint32_t  au32Config[2];           /* User Configuration */

    if (FMC_ReadConfig(au32Config, 2) < 0)       /* Read User Configuration CONFIG0 and CONFIG1. */
    {
        printf("\nRead User Config failed!\n");
        return -1;                     /* Failed on reading User Configuration */
    }

    if (au32Config[0] & 0x40)          /* Check if it's boot from APROM/LDROM with IAP. */
    {
        FMC_ENABLE_CFG_UPDATE();       /* Enable User Configuration update. */
        au32Config[0] &= ~0x40;        /* Select IAP boot mode. */
        FMC_WriteConfig(au32Config, 2);/* Update User Configuration CONFIG0 and CONFIG1. */

        SYS->IPRST0 = SYS_IPRST0_CHIPRST_Msk;    /* Perform chip reset to make new User Config take effect. */
    }
    return 0;                          /* success */
}


/**
  * @brief    Load an image to specified flash address. The flash area must have been enabled by
  *           caller. For example, if caller want to program an image to LDROM, FMC_ENABLE_LD_UPDATE()
  *           must be called prior to calling this function.
  * @return   Image is successfully programmed or not.
  * @retval   0   Success.
  * @retval   -1  Program/verify failed.
  */
static int  load_image_to_flash(uint32_t image_base, uint32_t image_limit, uint32_t flash_addr, uint32_t max_size)
{
    uint32_t   i, j, u32Data, u32ImageSize, *pu32Loader;

    u32ImageSize = max_size;           /* Give the maximum size of programmable flash area. */

    printf("Program image to flash address 0x%x...", flash_addr);    /* information message */

    /*
     * program the whole image to specified flash area
     */
    pu32Loader = (uint32_t *)image_base;
    for (i = 0; i < u32ImageSize; i += FMC_FLASH_PAGE_SIZE)
    {

        FMC_Erase(flash_addr + i);     /* erase a flash page */
        for (j = 0; j < FMC_FLASH_PAGE_SIZE; j += 4)                 /* program image to this flash page */
        {
            FMC_Write(flash_addr + i + j, pu32Loader[(i + j) / 4]);
        }
    }
    printf("OK.\nVerify ...");

    /* Verify loader */
    for (i = 0; i < u32ImageSize; i += FMC_FLASH_PAGE_SIZE)
    {
        for (j = 0; j < FMC_FLASH_PAGE_SIZE; j += 4)
        {
            u32Data = FMC_Read(flash_addr + i + j);        /* read a word from flash memory */

            if (u32Data != pu32Loader[(i+j)/4])            /* check if the word read from flash be matched with original image */
            {
                printf("data mismatch on 0x%x, [0x%x], [0x%x]\n", flash_addr + i + j, u32Data, pu32Loader[(i+j)/4]);
                return -1;             /* image program failed */
            }

            if (i + j >= u32ImageSize) /* check if it reach the end of image */
                break;
        }
    }
    printf("OK.\n");
    return 0;                          /* success */
}


int32_t main (void)
{
    FUNC_PTR    *func;                 /* function pointer */

    SYS_Init();
    UART_Open(UART0, 115200);

    printf("\n");
    printf("+-----------------------------------------+\n");
    printf("|      M480 update firmware by HSUSBD     |\n");
    printf("+-----------------------------------------+\n");

    SYS_UnlockReg();                   /* Unlock register lock protect */
    FMC_Open();                        /* Enable FMC ISP function */

    /*
     *  Check if User Configuration CBS is boot with IAP mode.
     *  If not, modify it.
     */
    if (set_IAP_boot_mode() < 0)
    {
        printf("Failed to set IAP boot mode!\n");
        FMC_Close();                       /* Disable FMC ISP function */
        while(1);
    }

    FMC_ENABLE_LD_UPDATE();    /* Enable LDROM update capability */
    /*
     *  The binary image of LDROM code is embedded in this sample.
     *  load_image_to_flash() will program this LDROM code to LDROM.
     */
    if (load_image_to_flash((uint32_t)&loaderImage1Base, (uint32_t)&loaderImage1Limit, FMC_LDROM_BASE, FMC_LDROM_SIZE) != 0)
    {
        printf("Load image to LDROM failed!\n");
        FMC_Close();                       /* Disable FMC ISP function */
        while(1);
    }
    FMC_DISABLE_LD_UPDATE();   /* Disable LDROM update capability */

    printf("\n\nChange VECMAP and branch to LDROM...\n");
    printf("\nAfter update the firmware, please press the reset button...\n");
    while (!(UART0->FIFOSTS & UART_FIFOSTS_TXEMPTY_Msk));      /* Wait for UART3 TX FIFO cleared */

    /*  NOTE!
     *     Before change VECMAP, user MUST disable all interrupts.
     *     The following code CANNOT locate in address 0x0 ~ 0x200.
     */

    /* FMC_SetVectorPageAddr(FMC_LDROM_BASE) */
    FMC->ISPCMD = FMC_ISPCMD_VECMAP;              /* ISP command */
    FMC->ISPADDR = FMC_LDROM_BASE;                /* Vector remap address */
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;           /* Trigger ISP command */
    while (FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) ;  /* Wait for ISP command done. */

    /*
     *  The reset handler address of an executable image is located at offset 0x4.
     *  Thus, this sample get reset handler address of LDROM code from FMC_LDROM_BASE + 0x4.
     */
    func = (FUNC_PTR *)*(uint32_t *)(FMC_LDROM_BASE + 4);
    /*
     *  Branch to the LDROM code's reset handler in way of function call.
     */
    func();

    while(1);
}



/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/

