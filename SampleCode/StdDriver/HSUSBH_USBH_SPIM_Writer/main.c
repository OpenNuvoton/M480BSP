/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    A sample provides command line interface for reading files from
 *           USB disk and writing to SPIM flash. It also provide functions of
 *           dump SPIM flash, compare USB disk file with SPIM flash,
 *           and branch to run code on SPIM.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include <stdio.h>
#include <string.h>

#include "NuMicro.h"

#include "usbh_lib.h"
#include "ff.h"
#include "diskio.h"


#define BUFF_SIZE                 2048      /* Working buffer size                        */
#define SPIM_FLASH_MAX_SIZE       0x8000000 /* Assumed maximum flash size 128 MB          */
#define SPIM_FLASH_PAGE_SIZE      0x10000   /* SPIM flash page size, depend on flash      */
#define IS_4BYTES_ADDR            0         /* W25Q20 does not support 4-bytes address mode. */

typedef void (FUNC_PTR)(void);

char      usbh_path[] = { '3', ':', 0 };    /* USB drive started from 3                   */
uint8_t   idBuf[3];

#ifdef __ICCARM__
#pragma data_alignment=32
uint8_t  Buff1[BUFF_SIZE] ;                 /* Working buffer                             */
uint8_t  Buff2[BUFF_SIZE] ;                 /* Working buffer                             */
#else
uint8_t  Buff1[BUFF_SIZE] __attribute__((aligned(32)));     /* Working buffer                             */
uint8_t  Buff2[BUFF_SIZE] __attribute__((aligned(32)));     /* Working buffer                             */
#endif

char      Line[128];                        /* Console input buffer                       */

FILINFO   Finfo;
FIL       file;


volatile uint32_t  g_tick_cnt;              /* SYSTICK timer counter                      */

void SysTick_Handler(void)
{
    g_tick_cnt++;                           /* timer tick counting 100 per second         */
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

/*
 *  Set stack base address to SP register.
 */
#ifdef __ARMCC_VERSION                 /* for Keil compiler */
void __set_SP(uint32_t _sp)
{
    __set_MSP(_sp);
}
#endif


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

    /* Enable SPIM module clock */
    CLK_EnableModuleClock(SPIM_MODULE);

    /* Update System Core Clock */
    SystemCoreClockUpdate();

    /* Set GPB multi-function pins for UART0 RXD and TXD */
    SYS->GPB_MFPH &= ~(SYS_GPB_MFPH_PB12MFP_Msk | SYS_GPB_MFPH_PB13MFP_Msk);
    SYS->GPB_MFPH |= (SYS_GPB_MFPH_PB12MFP_UART0_RXD | SYS_GPB_MFPH_PB13MFP_UART0_TXD);

    /* Init SPIM multi-function pins, MOSI(PC.0), MISO(PC.1), CLK(PC.2), SS(PC.3), D3(PC.4), and D2(PC.5) */
    SYS->GPC_MFPL &= ~(SYS_GPC_MFPL_PC0MFP_Msk | SYS_GPC_MFPL_PC1MFP_Msk | SYS_GPC_MFPL_PC2MFP_Msk |
                       SYS_GPC_MFPL_PC3MFP_Msk | SYS_GPC_MFPL_PC4MFP_Msk | SYS_GPC_MFPL_PC5MFP_Msk);
    SYS->GPC_MFPL |= SYS_GPC_MFPL_PC0MFP_SPIM_MOSI | SYS_GPC_MFPL_PC1MFP_SPIM_MISO |
                     SYS_GPC_MFPL_PC2MFP_SPIM_CLK | SYS_GPC_MFPL_PC3MFP_SPIM_SS |
                     SYS_GPC_MFPL_PC4MFP_SPIM_D3 | SYS_GPC_MFPL_PC5MFP_SPIM_D2;

    /* Set SPIM I/O pins as high slew rate up to 80 MHz. */
    PC->SLEWCTL = (PC->SLEWCTL & 0xFFFFF000) |
                  (0x1<<GPIO_SLEWCTL_HSREN0_Pos) | (0x1<<GPIO_SLEWCTL_HSREN1_Pos) |
                  (0x1<<GPIO_SLEWCTL_HSREN2_Pos) | (0x1<<GPIO_SLEWCTL_HSREN3_Pos) |
                  (0x1<<GPIO_SLEWCTL_HSREN4_Pos) | (0x1<<GPIO_SLEWCTL_HSREN5_Pos);

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

/*----------------------------------------------*/
/* Get a line from the input                    */
/*----------------------------------------------*/
void get_line (char *buff, int len)
{
    char    c;
    int     idx = 0;

    for (;;)
    {
        c = getchar();
        putchar(c);
        if (c == '\r') break;
        if ((c == '\b') && idx) idx--;
        if ((c >= ' ') && (idx < len - 1)) buff[idx++] = c;
    }
    buff[idx] = 0;
    putchar('\n');
}

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

void put_rc (FRESULT rc)
{
    const char *p =
        _T("OK\0DISK_ERR\0INT_ERR\0NOT_READY\0NO_FILE\0NO_PATH\0INVALID_NAME\0")
        _T("DENIED\0EXIST\0INVALID_OBJECT\0WRITE_PROTECTED\0INVALID_DRIVE\0")
        _T("NOT_ENABLED\0NO_FILE_SYSTEM\0MKFS_ABORTED\0TIMEOUT\0LOCKED\0")
        _T("NOT_ENOUGH_CORE\0TOO_MANY_OPEN_FILES\0");
    //FRESULT i;
    uint32_t i;
    for (i = 0; (i != (UINT)rc) && *p; i++)
    {
        while(*p++) ;
    }
    printf(_T("rc=%d FR_%s\n"), (UINT)rc, p);
}

int xatoi (                                 /* 0:Failed, 1:Successful                     */
    char       **str,                       /* Pointer to pointer to the string           */
    uint32_t   *res                         /* Pointer to a variable to store the value   */
)
{
    uint32_t   val;
    uint8_t    r, s = 0;
    char       c;


    *res = 0;
    while ((c = **str) == ' ') (*str)++;    /* Skip leading spaces */

    if (c == '-')       /* negative? */
    {
        s = 1;
        c = *(++(*str));
    }

    if (c == '0')
    {
        c = *(++(*str));
        switch (c)
        {
        case 'x':       /* hexadecimal */
            r = 16;
            c = *(++(*str));
            break;
        case 'b':       /* binary */
            r = 2;
            c = *(++(*str));
            break;
        default:
            if (c <= ' ') return 1; /* single zero */
            if (c < '0' || c > '9') return 0;   /* invalid char */
            r = 8;      /* octal */
        }
    }
    else
    {
        if (c < '0' || c > '9') return 0;   /* EOL or invalid char */
        r = 10;         /* decimal */
    }

    val = 0;
    while (c > ' ')
    {
        if (c >= 'a') c -= 0x20;
        c -= '0';
        if (c >= 17)
        {
            c -= 7;
            if (c <= 9) return 0;   /* invalid char */
        }
        if (c >= r) return 0;       /* invalid char for current radix */
        val = val * r + c;
        c = *(++(*str));
    }
    if (s) val = 0 - val;           /* apply sign if needed */

    *res = val;
    return 1;
}

static void  dump_buff_hex(uint32_t addr, uint8_t *pucBuff, int nBytes)
{
    int     nIdx, i;

    nIdx = 0;
    while (nBytes > 0)
    {
        printf("0x%08X  ", addr+ nIdx);
        for (i = 0; i < 16; i++)
            printf("%02x ", pucBuff[nIdx + i]);
        printf("  ");
        for (i = 0; i < 16; i++)
        {
            if ((pucBuff[nIdx + i] >= 0x20) && (pucBuff[nIdx + i] < 127))
                printf("%c", pucBuff[nIdx + i]);
            else
                printf(".");
            nBytes--;
        }
        nIdx += 16;
        printf("\n");
    }
    printf("\n");
}

int  show_root_dir()
{
    long    p1;                             /* total file size counter                    */
    FRESULT res;                            /* FATFS operation return code                */

    DIR dir;                                /* FATFS directory object                     */
    UINT s1, s2;                            /* file and directory counter                 */

    if (f_opendir(&dir, usbh_path))         /* try to open USB drive root directory       */
        return -1;                          /* open failed                                */

    p1 = s1 = s2 = 0;                       /* initialize counters                        */
    for (; ;)                               /* loop until reached end of root directory   */
    {
        res = f_readdir(&dir, &Finfo);      /* read directory entry                       */
        if ((res != FR_OK) || !Finfo.fname[0]) break;  /* no more entries                 */
        if (Finfo.fattrib & AM_DIR)         /* is a directory?                            */
        {
            s2++;                           /* increase directory counter                 */
        }
        else                                /* should be a file                           */
        {
            s1++;                           /* increase file counter                      */
            p1 += Finfo.fsize;              /* increase total file size counter           */
        }
        /* print file entry information               */
        printf("%c%c%c%c%c %u/%02u/%02u %02u:%02u %9lu  %s",
               (Finfo.fattrib & AM_DIR) ? 'D' : '-',    /* is a directory?                */
               (Finfo.fattrib & AM_RDO) ? 'R' : '-',    /* is read-only?                  */
               (Finfo.fattrib & AM_HID) ? 'H' : '-',    /* is hidden?                     */
               (Finfo.fattrib & AM_SYS) ? 'S' : '-',    /* is system file/directory?      */
               (Finfo.fattrib & AM_ARC) ? 'A' : '-',    /* is an archive?                 */
               (Finfo.fdate >> 9) + 1980, (Finfo.fdate >> 5) & 15, Finfo.fdate & 31,       /* date */
               (Finfo.ftime >> 11), (Finfo.ftime >> 5) & 63, Finfo.fsize, Finfo.fname);    /* time */
#if _USE_LFN
        for (p2 = strlen(Finfo.fname); p2 < 14; p2++)   /* print the long file name       */
            putchar(' ');
        printf("%s\n", Lfname);
#else
        putchar('\n');
#endif
    }
    /* print the statistic information            */
    printf("%4u File(s),%10lu bytes total\n%4u Dir(s)\n\n", s1, p1, s2);
    return 0;
}

/*
 *  w <file> <addr>
 */
int  write_file_to_flash(char *cmdline)
{
    char        *ptr = cmdline;             /* command string pointer                     */
    char        fname[64];                  /* file name string pointer                   */
    uint32_t    faddr, page_addr, addr;     /* flash address                              */
    UINT        len;                        /* data length                                */
    FRESULT     res;                        /* FATFS operation return code                */

    while (*ptr == ' ') ptr++;              /* skip space characters                      */

    for (len = 0; len < 60; len++)
    {
        if ((*ptr == ' ') || (*ptr == 0))
            break;
        fname[len] = *ptr++;
    }
    fname[len] = 0;

    if (!xatoi(&ptr, &faddr))               /* get <addr> parameter (SPIM flash address)  */
    {
        printf("Usage:  w <file> <addr>\n");
        return -1;
    }
    faddr = faddr - (faddr % SPIM_FLASH_PAGE_SIZE);  /* force page alignment              */

    printf("Write file [%s] to SPIM address 0x%x...\n", fname, faddr);
    res = f_open(&file, fname, FA_OPEN_EXISTING | FA_READ);   /* Open file                */
    if (res)
    {
        put_rc(res);                        /* Open failed, print error message           */
        return -1;                          /* Abort...                                   */
    }

    SPIM_ReadJedecId(idBuf, sizeof (idBuf), 1);
    printf("Flash ID=0x%02X, 0x%02X, 0x%02X\n", idBuf[0], idBuf[1], idBuf[2]);

    SPIM_Enable_4Bytes_Mode(IS_4BYTES_ADDR, 1);  /* Enable 4-bytes address mode?          */

    /*
     *  Erase SPIM flash page and program...
     */
    for (page_addr = faddr; page_addr < SPIM_FLASH_MAX_SIZE; page_addr += SPIM_FLASH_PAGE_SIZE)
    {
        if (f_eof(&file))
        {
            printf("OK [%d]\n", res);
            f_close(&file);             /* close file                                 */
            return 0;                   /* done                                       */
        }

        /* Erase SPIM flash */
        printf("Erase flash page 0x%x...\n", page_addr);
        SPIM_EraseBlock(page_addr, IS_4BYTES_ADDR, OPCODE_BE_64K, 1, 1);

        memset(Buff2, 0xff, BUFF_SIZE);     /* prepared compare buffer                    */

        /* Verify erased page */
        printf("Verify erased page...");
        for (addr = page_addr; addr < page_addr+SPIM_FLASH_PAGE_SIZE; addr += BUFF_SIZE)
        {
            memset(Buff1, 0x11, BUFF_SIZE); /* fill buffer with non-0xFF                  */

            /* DMA read SPIM flash                                                        */
            SPIM_DMA_Read(addr, IS_4BYTES_ADDR, BUFF_SIZE, Buff1, CMD_DMA_FAST_READ, 1);

            if (memcmp(Buff1, Buff2, BUFF_SIZE) != 0)
            {
                printf("Verify address 0x%x failed!\n", addr);
                f_close(&file);             /* close file                                 */
                return -1;                  /* non-0xFF data found, erase failed          */
            }
        }
        printf("OK.\n");

        printf("Program page and verify...");
        for (addr = page_addr; addr < page_addr+SPIM_FLASH_PAGE_SIZE; addr += BUFF_SIZE)
        {
            res = f_read(&file, Buff1, BUFF_SIZE, &len);

            if (res || (len == 0))
            {
                printf("OK [%d]\n", res);
                f_close(&file);             /* close file                                 */
                return 0;                   /* done                                       */
            }
            /* DMA write SPIM flash                       */
            SPIM_DMA_Write(addr, IS_4BYTES_ADDR, BUFF_SIZE, Buff1, CMD_NORMAL_PAGE_PROGRAM);

            memset(Buff2, 0, BUFF_SIZE);
            /* DMA read SPIM flash                        */
            SPIM_DMA_Read(addr, IS_4BYTES_ADDR, BUFF_SIZE, Buff2, CMD_DMA_FAST_READ, 1);

            if (memcmp(Buff1, Buff2, BUFF_SIZE) != 0)
            {
                printf("Failed at address 0x%x!\n", addr);
                f_close(&file);             /* close file                                 */
                return -1;
            }
            printf(".");
        }
        printf("OK\n");
    }
    return 0;
}

/*
 *  c <file> <addr>
 */
int  compare_file_with_flash(char *cmdline)
{
    char        *ptr = cmdline;             /* command string pointer                     */
    char        fname[64];                  /* file name string pointer                   */
    uint32_t    faddr, page_addr, addr;     /* flash address                              */
    UINT        i, len;                     /* data length                                */
    FRESULT     res;                        /* FATFS operation return code                */

    while (*ptr == ' ') ptr++;              /* skip space characters                      */

    for (len = 0; len < 60; len++)
    {
        if ((*ptr == ' ') || (*ptr == 0))
            break;
        fname[len] = *ptr++;
    }
    fname[len] = 0;

    if (!xatoi(&ptr, &faddr))               /* get <addr> parameter (SPIM flash address)  */
    {
        printf("Usage:  c <file> <addr>\n");
        return -1;
    }
    faddr = faddr - (faddr % SPIM_FLASH_PAGE_SIZE);  /* force page alignment              */

    printf("Compare file [%s] with SPIM address 0x%x...\n", fname, faddr);
    res = f_open(&file, fname, FA_OPEN_EXISTING | FA_READ);   /* Open file                */
    if (res)
    {
        put_rc(res);                        /* Open failed, print error message           */
        return -1;                          /* Abort...                                   */
    }

    SPIM_ReadJedecId(idBuf, sizeof (idBuf), 1);
    printf("Flash ID=0x%02X, 0x%02X, 0x%02X\n", idBuf[0], idBuf[1], idBuf[2]);

    SPIM_Enable_4Bytes_Mode(IS_4BYTES_ADDR, 1);  /* Enable 4-bytes address mode?          */

    /*
     *  Compare ...
     */
    for (page_addr = faddr; page_addr < SPIM_FLASH_MAX_SIZE; page_addr += SPIM_FLASH_PAGE_SIZE)
    {
        printf("Comparing...");
        for (addr = page_addr; addr < page_addr+SPIM_FLASH_PAGE_SIZE; addr += BUFF_SIZE)
        {
            memset(Buff1, 0xff, BUFF_SIZE); /* fill 0xff to clear buffer                  */
            memset(Buff2, 0, BUFF_SIZE);    /* fill 0x00 to clear buffer                  */

            res = f_read(&file, Buff1, BUFF_SIZE, &len);
            if (res || (len == 0))
            {
                printf("Compare OK.\n");
                f_close(&file);             /* close file                                 */
                return 0;                   /* done                                       */
            }
            /* DMA read SPIM flash                        */
            SPIM_DMA_Read(addr, IS_4BYTES_ADDR, BUFF_SIZE, Buff2, CMD_DMA_FAST_READ, 1);

            if (memcmp(Buff1, Buff2, len) != 0)
            {
                for (i = 0; i < len; i++)
                    printf("0x%04x: 0x%02x  0x%02x\n", addr+i, Buff1[i], Buff2[i]);
                printf("Compare failed!\n");
                f_close(&file);             /* close file                                 */
                return -1;
            }
            printf(".");
        }
        printf("OK\n");
    }
    return 0;
}

/*
 *  d <addr> <len>
 */
int  dump_spim_flash(char *cmdline)
{
    char        *ptr = cmdline;             /* command string pointer                     */
    uint32_t    faddr, addr;                /* flash address                              */
    uint32_t    dump_len;                   /* dump length                                */
    UINT        len;                        /* data length                                */

    if (!xatoi(&ptr, &faddr))               /* get <addr> parameter (SPIM flash address)  */
    {
        printf("Usage:  d <addr> <len>\n");
        return -1;
    }
    faddr = faddr - (faddr % BUFF_SIZE);    /* force block alignment                      */

    if (!xatoi(&ptr, &dump_len))            /* get <len> parameter (data dump length)     */
    {
        printf("Usage:  d <addr> <len>\n");
        return -1;
    }

    SPIM_ReadJedecId(idBuf, sizeof (idBuf), 1);
    printf("Flash ID=0x%02X, 0x%02X, 0x%02X\n", idBuf[0], idBuf[1], idBuf[2]);

    SPIM_Enable_4Bytes_Mode(IS_4BYTES_ADDR, 1);  /* Enable 4-bytes address mode?          */

    /*
     *  Read and dump ...
     */
    for (addr = faddr; dump_len > 0; addr += BUFF_SIZE)
    {
        memset(Buff1, 0, BUFF_SIZE);        /* fill 0x00 to clear buffer                  */
        /* DMA read SPIM flash                        */
        SPIM_DMA_Read(addr, IS_4BYTES_ADDR, BUFF_SIZE, Buff1, CMD_DMA_FAST_READ, 1);

        if (dump_len < BUFF_SIZE)
            len = dump_len;
        else
            len = BUFF_SIZE;

        dump_buff_hex(addr, Buff1, len);    /* dump data                                  */
        dump_len -= len;
    }
    return 0;
}

/*
 *  g <addr>
 *
 *  Example:
 *  Assumed the image located on SPIM flash offset address 0x2000. It's RO_BASE must
 *  be (SPIM_DMM_MAP_ADDR+0x2000). To branch and run this image, user must issue
 *  command "g 0x2000".
 */
int  go_to_flash(char *cmdline)
{
    char        *ptr = cmdline;             /* command string pointer                     */
    uint32_t    faddr;                      /* flash address                              */
    FUNC_PTR    *func;                      /* function pointer                           */

    if (!xatoi(&ptr, &faddr))               /* get <addr> parameter (SPIM flash address)  */
    {
        printf("Usage:  g <addr>\n");
        return -1;
    }

    SPIM_ReadJedecId(idBuf, sizeof (idBuf), 1);
    printf("Flash ID=0x%02X, 0x%02X, 0x%02X\n", idBuf[0], idBuf[1], idBuf[2]);

    SPIM_DISABLE_CCM();
    SPIM_ENABLE_CACHE();

    SPIM_Enable_4Bytes_Mode(IS_4BYTES_ADDR, 1);  /* Enable 4-bytes address mode?          */

    SPIM->CTL1 |= SPIM_CTL1_CDINVAL_Msk;    /* invalid cache                              */
    /* Enable DMM mode                            */
    SPIM_EnterDirectMapMode(IS_4BYTES_ADDR, CMD_DMA_FAST_READ, 0);

    func = (FUNC_PTR *)inpw(SPIM_DMM_MAP_ADDR + faddr + 4);

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;   /* disable SYSTICK (prevent interrupt)   */

#if defined (__GNUC__) && !defined(__ARMCC_VERSION)
    asm volatile("msr msp, r0");
    asm volatile("bx  lr");
#else
    __set_SP(inpw(SPIM_DMM_MAP_ADDR + faddr));
#endif

    func();                                      /* branch to SPIM                        */

    return 0;
}


int32_t main(void)
{
    char        *ptr;                       /* str pointer                                */

    SYS_Init();                             /* Init System, clock and I/O pins.           */

    UART0_Init();                           /* Initialize UART0                           */

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1)
    {
        printf("M480LD does not support SPIM.\n");
        while (1);
    }

    enable_sys_tick(100);

    printf("\n\n");
    printf("+-----------------------------------------------+\n");
    printf("|   USB SPIM writer                             |\n");
    printf("+-----------------------------------------------+\n");

    SYS_UnlockReg();                        /* Unlock register lock protect               */

    SPIM_SET_CLOCK_DIVIDER(2);             /* Set SPIM clock as HCLK divided by 4        */

    SPIM_SET_RXCLKDLY_RDDLYSEL(0);         /* Insert 0 delay cycle. Adjust the sampling clock of received data to latch the correct data. */
    SPIM_SET_RXCLKDLY_RDEDGE();            /* Use SPI input clock rising edge to sample received data. */

    SPIM_SET_DCNUM(8);                     /* 8 is the default value.                    */

    if (SPIM_InitFlash(1) != 0)             /* Initialized SPI flash                      */
    {
        printf("SPIM flash initialize failed!\n");
        while (1);
    }

    SPIM_ReadJedecId(idBuf, sizeof (idBuf), 1);   /* read SPIM flash ID                   */
    printf("SPIM get JEDEC ID=0x%02X, 0x%02X, 0x%02X\n", idBuf[0], idBuf[1], idBuf[2]);

    usbh_core_init();                       /* initialize USB Host library                */
    usbh_umas_init();                       /* initialize USB mass storage driver         */
    usbh_pooling_hubs();                    /* monitor USB hub ports                      */

    f_chdrive(usbh_path);                   /* set default path                           */

    for (;;)
    {
        usbh_pooling_hubs();

        printf(_T(">"));
        ptr = Line;

        get_line(ptr, sizeof(Line));

        switch (*ptr++)
        {

        case 'h':
        case '?':                           /* Show usage                                 */
            printf(
                _T("l - List root directory files\n")
                _T("w <file> <addr> - Write a file to SPIM flash. <addr> is an offset from SPIM flash base.\n")
                _T("c <file> <addr> - Compare a file with SPIM flash. <addr> is an offset from SPIM flash base.\n")
                _T("d <addr> <len> - Dump SPIM offset <addr> contents.\n")
                _T("g <addr> - Branch to SPIM offset <addr> and execute.\n")
            );
            break;

        case 'l' :                          /* List root directory files                  */
            show_root_dir();
            break;

        case 'w' :                          /* w <file> <addr>                            */
            write_file_to_flash(ptr);       /* Write a file to SPIM flash.                */
            break;

        case 'c' :                          /* c <file> <addr>                            */
            compare_file_with_flash(ptr);   /* Compare a file with SPIM flash block.      */
            break;

        case 'd' :                          /* d <addr> <len>                             */
            dump_spim_flash(ptr);           /* Dump contents of a SPIM flash block.       */
            break;

        case 'g' :                          /* g <addr>                                   */
            go_to_flash(ptr);               /* Branch to SPIM flash offset <addr>         */
            break;
        }
    }
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/

