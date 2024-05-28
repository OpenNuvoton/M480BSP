/**************************************************************************//**
 * @file     APROM_main.c
 * @version  V1.00
 * @brief    FMC APROM IAP sample program run on APROM.
 *
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
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

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Lock protected registers */
    SYS_LockReg();
}

void UART0_Init(void)
{
    /* Configure UART0 and set UART0 baud rate */
    UART_Open(UART0, 115200);
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

        if (FMC_WriteConfig(au32Config, 2) != 0) /* Update User Configuration CONFIG0 and CONFIG1. */
        {
            printf("FMC_WriteConfig failed!\n");
            return -1;
        }
        SYS->IPRST0 = SYS_IPRST0_CHIPRST_Msk;    /* Perform chip reset to make new User Config take effect. */
    }
    return 0;                          /* success */
}


/*
 *  Set stack base address to SP register.
 */
#ifdef __ARMCC_VERSION                 /* for Keil compiler */
void __set_SP(uint32_t _sp)
{
    __set_MSP(_sp);
}
#endif


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
        if (FMC_Erase(flash_addr + i) != 0)    /* erase a flash page */
        {
            printf("FMC_Erase address 0x%x failed!\n", flash_addr + i);
            return -1;
        }
        for (j = 0; j < FMC_FLASH_PAGE_SIZE; j += 4)                 /* program image to this flash page */
        {
            if (FMC_Write(flash_addr + i + j, pu32Loader[(i + j) / 4]) != 0)
            {
                printf("FMC_Write address 0x%x failed!\n", flash_addr + i + j);
                return -1;
            }
        }
    }
    printf("OK.\nVerify ...");

    /* Verify loader */
    for (i = 0; i < u32ImageSize; i += FMC_FLASH_PAGE_SIZE)
    {
        for (j = 0; j < FMC_FLASH_PAGE_SIZE; j += 4)
        {
            u32Data = FMC_Read(flash_addr + i + j);        /* read a word from flash memory */
            if (g_FMC_i32ErrCode != 0)
            {
                printf("FMC_Read address 0x%x failed!\n", flash_addr + i + j);
                return -1;
            }

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


int main()
{
    uint8_t     u8Item;                /* menu item */
    uint32_t    u32Data;               /* temporary data word */
    FUNC_PTR    *func;                 /* function pointer */
    uint32_t    tout;

    SYS_Init();                        /* Init System, IP clock and multi-function I/O */

    UART0_Init();                      /* Initialize UART0 */

    printf("\n\n");
    printf("+----------------------------------------+\n");
    printf("|     M480 FMC_IAP Sample Code           |\n");
    printf("|           [APROM code]                 |\n");
    printf("+----------------------------------------+\n");

    SYS_UnlockReg();                   /* Unlock register lock protect */

    FMC_Open();                        /* Enable FMC ISP function */

    /*
     *  Check if User Configuration CBS is boot with IAP mode.
     *  If not, modify it.
     */
    if (set_IAP_boot_mode() < 0)
    {
        printf("Failed to set IAP boot mode!\n");
        goto lexit;                    /* Failed to set IAP boot mode. Program aborted. */
    }

    /* Read BS */
    printf("  Boot Mode ............................. ");
    if (FMC_GetBootSource() == 0)      /* Get boot source */
        printf("[APROM]\n");           /* Is booting from APROM */
    else
    {
        printf("[LDROM]\n");           /* Is booting from LDROM */
        printf("  WARNING: The sample code must execute in APROM!\n");
        goto lexit;                    /* This sample program must execute in APROM. Program aborted. */
    }

    u32Data = FMC_ReadCID();           /* get company ID */
    if (g_FMC_i32ErrCode != 0)
    {
        printf("FMC_ReadCID failed!\n");
        goto lexit;
    }
    printf("  Company ID ............................ [0x%08x]\n", u32Data);

    u32Data = FMC_ReadPID();           /* get product ID */
    if (g_FMC_i32ErrCode != 0)
    {
        printf("FMC_ReadPID failed!\n");
        goto lexit;
    }
    printf("  Product ID ............................ [0x%08x]\n", u32Data);

    /* Read User Configuration CONFIG0 */
    printf("  User Config 0 ......................... [0x%08x]\n", FMC_Read(FMC_CONFIG_BASE));
    if (g_FMC_i32ErrCode != 0)
    {
        printf("FMC_Read(FMC_CONFIG_BASE) failed!\n");
        goto lexit;
    }

    /* Read User Configuration CONFIG1 */
    printf("  User Config 1 ......................... [0x%08x]\n", FMC_Read(FMC_CONFIG_BASE+4));
    if (g_FMC_i32ErrCode != 0)
    {
        printf("FMC_Read(FMC_CONFIG_BASE+4) failed!\n");
        goto lexit;
    }

    do
    {
        printf("\n\n\n");
        printf("+----------------------------------------+\n");
        printf("|               Select                   |\n");
        printf("+----------------------------------------+\n");
        printf("| [0] Load IAP code to LDROM             |\n");
        printf("| [1] Run IAP program (in LDROM)         |\n");
        printf("+----------------------------------------+\n");
        printf("Please select...");
        u8Item = getchar();            /* block waiting to receive any one character from UART0 */
        printf("%c\n", u8Item);        /* print out the selected item */

        switch (u8Item)
        {
        case '0':
            FMC_ENABLE_LD_UPDATE();    /* Enable LDROM update capability */
            /*
             *  The binary image of LDROM code is embedded in this sample.
             *  load_image_to_flash() will program this LDROM code to LDROM.
             */
            if (load_image_to_flash((uint32_t)&loaderImage1Base, (uint32_t)&loaderImage1Limit,
                                    FMC_LDROM_BASE, FMC_LDROM_SIZE) != 0)
            {
                printf("Load image to LDROM failed!\n");
                goto lexit;            /* Load LDROM code failed. Program aborted. */
            }
            FMC_DISABLE_LD_UPDATE();   /* Disable LDROM update capability */
            break;

        case '1':
            printf("\n\nChange VECMAP and branch to LDROM...\n");
            printf("LDROM code SP = 0x%x\n", *(uint32_t *)(FMC_LDROM_BASE));
            printf("LDROM code ResetHandler = 0x%x\n", *(uint32_t *)(FMC_LDROM_BASE+4));
            while (!(UART0->FIFOSTS & UART_FIFOSTS_TXEMPTY_Msk));      /* Wait for UART3 TX FIFO cleared */
            /*  NOTE!
             *     Before change VECMAP, user MUST disable all interrupts.
             *     The following code CANNOT locate in address 0x0 ~ 0x200.
             */

            /* FMC_SetVectorPageAddr(FMC_LDROM_BASE) */
            tout = FMC_TIMEOUT_WRITE;
            FMC->ISPCMD = FMC_ISPCMD_VECMAP;              /* ISP command */
            FMC->ISPADDR = FMC_LDROM_BASE;                /* Vector remap address */
            FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;           /* Trigger ISP command */
            while (tout-- > 0)
            {
                if ((FMC->ISPTRG &  FMC_ISPTRG_ISPGO_Msk) == 0)  /* Waiting for ISP Done */
                    break;
            }
            if (tout == 0)
            {
                printf("FMC_ISPCMD_VECMAP time-out!\n");
                goto lexit;
            }

            /*
             *  The reset handler address of an executable image is located at offset 0x4.
             *  Thus, this sample get reset handler address of LDROM code from FMC_LDROM_BASE + 0x4.
             */
            func = (FUNC_PTR *)*(uint32_t *)(FMC_LDROM_BASE + 4);
            /*
             *  The stack base address of an executable image is located at offset 0x0.
             *  Thus, this sample get stack base address of LDROM code from FMC_LDROM_BASE + 0x0.
             */
#if defined (__GNUC__) && !defined(__ARMCC_VERSION)  /* for GNU C compiler */
            u32Data = *(uint32_t *)FMC_LDROM_BASE;
            asm("msr msp, %0" : : "r" (u32Data));
#else
            __set_SP(*(uint32_t *)FMC_LDROM_BASE);
#endif
            /*
             *  Branch to the LDROM code's reset handler in way of function call.
             */
            func();
            break;

        default :
            continue;                  /* invalid selection */
        }
    }
    while (1);


lexit:                                 /* program exit */

    FMC_Close();                       /* Disable FMC ISP function */

    SYS_LockReg();                     /* Lock protected registers */

    printf("\nFMC Sample Code Completed.\n");

    while (1);
}

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
