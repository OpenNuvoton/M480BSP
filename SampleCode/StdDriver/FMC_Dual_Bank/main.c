/**************************************************************************//**
 * @file     main.c
 * @version  V1.00
 * @brief    Show FMC dual bank capability. Non-blocking program APROM bank1
 *           while program is running on APROM bank0.
 *           is running on bank0 without being blocked.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/
#include <stdio.h>

#include "NuMicro.h"

#define APROM_BANK1_BASE            0x40000      /* APROM bank1 base address for 512KB size. */
/* APROM bank1 address is 1/2 APROM size.   */
#define DB_PROG_LEN                 (4 * FMC_FLASH_PAGE_SIZE)  /* background program length  */
#define CRC32_LOOP_CNT              500          /* Loop count                               */


/*
 *  Dual bank background program state
 */
enum
{
    DB_STATE_START,                              /* Start background dual bank program       */
    DB_STATE_ERASE,                              /* Executing ISP page erase                 */
    DB_STATE_PROGRAM,                            /* Executing ISP write                      */
    DB_STATE_DONE,                               /* All queued ISP operations finished. Idle */
    DB_STATE_FAIL                                /* ISP command failed or verify error       */
};

static volatile int  db_state = DB_STATE_DONE;   /* dual bank background program state       */
static volatile uint32_t  db_length;             /* dual bank program remaining length       */
static volatile uint32_t  db_addr;               /* dual bank program current flash address  */


volatile uint32_t  g_tick_cnt;                   /* timer ticks - 100 ticks per second       */


void SysTick_Handler(void)
{
    g_tick_cnt++;                                /* increase timer tick                      */

    if (db_state == DB_STATE_DONE)               /* Background program is in idle state      */
    {
        return;
    }

    if (db_length == 0)                          /* Background program done?                 */
    {
        db_state = DB_STATE_DONE;                /* enter idle state                         */
        return;
    }

    if (FMC->MPSTS & FMC_MPSTS_MPBUSY_Msk)
        return;                                  /* ISP is busy, postpone to next called     */

    /*
     *  Dual-bank background program...
     */
    switch (db_state)
    {
    case DB_STATE_START:
        if (db_addr & ~FMC_PAGE_ADDR_MASK)
        {
            printf("Warning - dual bank start address is not page aligned!\n");
            db_state = DB_STATE_FAIL;
            break;
        }
        if (db_length & ~FMC_PAGE_ADDR_MASK)
        {
            printf("Warning - dual bank length is not page aligned!\n");
            db_state = DB_STATE_FAIL;
            break;
        }
        db_state = DB_STATE_ERASE;           /* Next state is to erase flash            */
        break;

    case DB_STATE_ERASE:
        printf("Erase 0x%x [%d]\n", db_addr, g_tick_cnt);
        FMC->ISPCMD = FMC_ISPCMD_PAGE_ERASE; /* ISP page erase command                   */
        FMC->ISPADDR = db_addr;              /* page address                             */
        FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;  /* trigger ISP page erase and no wait       */

        db_state = DB_STATE_PROGRAM;         /* Next state is to program flash           */
        break;

    case DB_STATE_PROGRAM:
        if ((db_addr & ~FMC_PAGE_ADDR_MASK) == 0)
            printf("Erase done [%d]\n", g_tick_cnt);

        FMC->ISPCMD = FMC_ISPCMD_PROGRAM;    /* ISP word program command                 */
        FMC->ISPADDR = db_addr;              /* word program address                     */
        FMC->ISPDAT = db_addr;               /* 32-bits data to be programmed            */
        FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;  /* trigger ISP program and no wait          */

        db_addr += 4;                        /* advance to next word                     */
        db_length -= 4;
        if ((db_addr & ~FMC_PAGE_ADDR_MASK) == 0)
        {
            /* have reached start of next page          */
            db_state = DB_STATE_ERASE;       /* next state, erase page                   */
        }
        break;

    default:
        printf("Unknown db_state state!\n");
        while (1);
    }
}

void enable_sys_tick(int ticks_per_second)
{
    g_tick_cnt = 0;
    SystemCoreClock = 192000000UL;         /* HCLK is 160 MHz */
    if (SysTick_Config(SystemCoreClock / ticks_per_second))
    {
        /* Setup SysTick Timer for 1 second interrupts  */
        printf("Set system tick error!!\n");
        while (1);
    }
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

static const uint32_t crc32_tab[] =
{
    0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
    0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
    0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
    0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
    0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
    0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
    0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b, 0x35b5a8fa, 0x42b2986c,
    0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
    0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
    0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
    0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190, 0x01db7106,
    0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
    0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
    0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
    0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
    0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
    0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
    0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
    0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
    0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
    0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
    0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
    0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
    0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
    0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
    0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
    0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
    0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
    0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
    0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
    0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
    0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
    0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
    0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
    0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
    0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
    0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
    0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
    0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
    0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
    0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
    0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
    0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

#define CRC_SEED    0xFFFFFFFF
uint32_t g_u32ApCrc = 0;


uint32_t  func_crc32(uint32_t start, uint32_t len)
{
    uint32_t  crc = CRC_SEED;
    uint32_t  idx, data32;
    uint8_t   data8;
    int       i;

    /* WDTAT_RVS, CHECKSUM_RVS, CHECKSUM_COM */
    for (idx = 0; idx < len; idx += 4)
    {
        data32 = *(uint32_t *)(start + idx);
        for (i = 0; i < 4; i++)
        {
            data8 = (data32 >> (i*8)) & 0xff;
            crc = crc32_tab[(crc ^ data8) & 0xFF] ^ (crc >> 8);
        }
    }
    /* CHECKSUM_COM */
    return crc ^ ~0U;
}

void start_timer0()
{
    /* Start TIMER0  */
    CLK->CLKSEL1 = (CLK->CLKSEL1 & (~CLK_CLKSEL1_TMR0SEL_Msk)) | CLK_CLKSEL1_TMR0SEL_HXT;
    CLK->APBCLK0 |= CLK_APBCLK0_TMR0CKEN_Msk;    /* enable TIMER0 clock                  */
    TIMER0->CTL = 0;                   /* disable timer                                  */
    TIMER0->INTSTS = (TIMER_INTSTS_TWKF_Msk | TIMER_INTSTS_TIF_Msk);  /* clear interrupt status */
    TIMER0->CMP = 0xFFFFFE;            /* maximum time                                   */
    TIMER0->CNT = 0;                   /* clear timer counter                            */
    /* start timer */
    TIMER0->CTL = (11 << TIMER_CTL_PSC_Pos) | TIMER_ONESHOT_MODE | TIMER_CTL_CNTEN_Msk;
}

uint32_t  get_timer0_counter()
{
    return TIMER0->CNT;
}

int main()
{
    uint32_t    loop;                  /* loop counter                                   */
    uint32_t    addr;                  /* flash address                                  */
    uint32_t    t;                     /* TIMER0 counter value                           */

    SYS_Init();                        /* Init System, IP clock and multi-function I/O   */

    UART0_Init();                      /* Initialize UART0                               */

    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1)
    {
        printf("M480LD does not support dual bank!\n");
        while (1);
    }

    printf("+------------------------------------------+\n");
    printf("|    M480 FMC Dual Bank Sample Demo        |\n");
    printf("+------------------------------------------+\n");

    SYS_UnlockReg();                   /* Unlock register lock protect                   */

    FMC_Open();                        /* Enable FMC ISP function                        */
    FMC_ENABLE_AP_UPDATE();            /* Enable FMC erase/program APROM                 */

    db_state = DB_STATE_DONE;          /* dual bank program state idle                   */

    enable_sys_tick(1000);
    start_timer0();

    for (loop = 0; loop < CRC32_LOOP_CNT; loop++)
    {
        func_crc32(0x0, 0x10000);      /* Calculate 64KB CRC32 value, just to consume CPU time  */
    }

    t = get_timer0_counter();

    /* TIMER0->CNT is the elapsed us */
    printf("\nTime elapsed without program bank1: %d.%d seconds. Ticks: %d\n\n", t/1000000, t/1000, g_tick_cnt);

    db_addr = APROM_BANK1_BASE;        /* Dual bank background program address           */
    db_length = DB_PROG_LEN;           /* Dual bank background length                 */
    db_state = DB_STATE_START;         /* Start background dual bank program             */

    enable_sys_tick(1000);
    start_timer0();

    for (loop = 0; loop < CRC32_LOOP_CNT; loop++)
    {
        func_crc32(0x0, 0x10000);      /* Calculate 64KB CRC32 value, just to consume CPU time  */
    }

    t = get_timer0_counter();

    /* TIMER0->CNT is the elapsed us */
    printf("\nTime elapsed with program bank1: %d.%d seconds. Ticks: %d\n\n", t/1000000, t/1000, g_tick_cnt);

    while (db_state != DB_STATE_DONE) ;

    /*
     *  Verify ...
     */
    for (addr = APROM_BANK1_BASE; addr < APROM_BANK1_BASE + DB_PROG_LEN; addr += 4)
    {
        if (inpw(addr) != addr)
        {
            printf("Flash address 0x%x verify failed! expect: 0x%x, read: 0x%x.\n", addr, addr, inpw(addr));
            while (1);
        }
    }
    printf("Verify OK.\n");

    FMC_Close();                       /* Disable FMC ISP function                       */

    SYS_LockReg();                     /* Lock protected registers                       */

    printf("\nFMC Sample Code Completed.\n");

    while (1);
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
