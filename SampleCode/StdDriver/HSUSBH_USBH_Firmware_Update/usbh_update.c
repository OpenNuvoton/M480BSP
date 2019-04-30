/**************************************************************************//**
 * @file     usbh_update.c
 * @version  V1.00
 * @brief    Search and read new firmware from USB drive and update APROM flash with it.
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#include <stdio.h>
#include <string.h>

#include "NuMicro.h"

#include "usbh_lib.h"
#include "ff.h"
#include "diskio.h"

#define USBH_DRIVE          3               /* Assigned USBH drive number in FATFS        */

#define APROM_FILE_NAME     "AP.BIN"        /* pre-defined APROM firmware update image    */
#define SPROM_FILE_NAME     "SP.BIN"        /* pre-defined SPROM firmware update image    */
#define DATA_FILE_NAME      "DATA.BIN"      /* pre-defined Data Flash update image        */


TCHAR   usbh_path[] = { '3', ':', 0 };      /* USB drive started from 3                   */

uint8_t   _Buff[FMC_FLASH_PAGE_SIZE];
FILINFO   Finfo;
FIL       file1;


int  do_dir()
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
    printf("%4u File(s),%10lu bytes total\n%4u Dir(s)", s1, p1, s2);
    return 0;
}


int  program_flash_page(uint32_t page_addr, uint32_t *buff, int count)
{
    uint32_t  addr;                         /* flash address                              */
    uint32_t  *p = buff;                    /* data buffer pointer                        */

    printf("Program page 0x%x, count=%d\n", page_addr, count);

    if (page_addr == FMC_SPROM_BASE)        /* is going to erase SPROM?                   */
        FMC_Erase_SPROM();                  /* Erase the SPROM page                       */
    else
        FMC_Erase(page_addr);               /* Erase an APROM page                        */

    for (addr = page_addr; addr < page_addr+count; addr += 4, p++)      /* loop page      */
    {
        FMC_Write(addr, *p);                /* program flash                              */
    }

    /* Verify ... */
    p = buff;
    for (addr = page_addr; addr < page_addr+count; addr += 4, p++)      /* loop page      */
    {
        if (FMC_Read(addr) != *p)           /* Read flash word and verify                 */
        {
            printf("Verify failed at 0x%x, read:0x%x, epect:0x%x\n", addr, FMC_Read(addr), *p);
            return -1;                      /* verify data mismatched                     */
        }
    }
    return 0;
}


void usbh_firmware_update()
{
    uint32_t   addr, dfba;
    UINT       cnt;
    FRESULT    res;

    f_chdrive(usbh_path);                   /* set default path                           */

    if (do_dir() < 0)                       /* Open root directory and print out.         */
        return;                             /* Cannot open root directory. USB disk may   */
    /* not be connected.                          */

    /*------------------------------------------------------------------------------------*/
    /*  Try to open APROM firmware image. If opened successfully, read and update APROM.  */
    /*------------------------------------------------------------------------------------*/
    /* Try to open APROM firmware image file      */
    if (f_open(&file1, APROM_FILE_NAME, FA_OPEN_EXISTING | FA_READ))
    {
        printf("APROM image [%s] not found.\n", APROM_FILE_NAME);    /* File not found    */
    }
    else
    {
        printf("APROM image [%s] found, start update APROM firmware...\n", APROM_FILE_NAME);
        FMC_ENABLE_AP_UPDATE();             /* enable APROM update                        */

        for (addr = 0; ; addr += FMC_FLASH_PAGE_SIZE)
        {
            cnt = FMC_FLASH_PAGE_SIZE;      /* read a flash page size data from file      */
            res = f_read(&file1, _Buff, cnt, &cnt);   /* read file                        */
            if ((res == FR_OK) && cnt)      /* read operation success?                    */
            {
                /* update APROM firmware page                 */
                if (program_flash_page(addr, (uint32_t *)_Buff, cnt) != 0)
                {
                    f_close(&file1);        /* program failed! Close file.                */
                    return;                 /* Abort...                                   */
                }
            }
            else
                break;                      /* read file failed or reached end-of-file    */
        }

        if (f_eof(&file1))                  /* reach end-of-file?                         */
            printf("APROM update success.\n");     /* firmware update success             */
        else
            printf("APROM update failed!\n");      /* firmware update failed              */

        f_close(&file1);                    /* close file                                 */
    }

    /*------------------------------------------------------------------------------------*/
    /*  Try to open SPROM firmware image. If opened successfully, read and update SPROM.  */
    /*------------------------------------------------------------------------------------*/
    /* Try to open SPROM firmware image file      */
    if ((SYS->CSERVER & SYS_CSERVER_VERSION_Msk) == 0x1)
    {
        /* M480LD has not SPROM. */
    }
    else if (f_open(&file1, SPROM_FILE_NAME, FA_OPEN_EXISTING | FA_READ))
    {
        printf("SPROM image [%s] not found.\n", SPROM_FILE_NAME);    /* File not found    */
    }
    else
    {
        printf("SPROM image [%s] found, start update SPROM firmware...\n", SPROM_FILE_NAME);
        FMC_ENABLE_SP_UPDATE();             /* Enable SPROM update                        */
        cnt = FMC_FLASH_PAGE_SIZE;          /* read a flash page size data from file      */
        res = f_read(&file1, _Buff, cnt, &cnt);  /* read file                             */
        if ((res == FR_OK) && cnt)          /* read operation success?                    */
        {
            /* update SPROM firmware page                 */
            if (program_flash_page(FMC_SPROM_BASE, (uint32_t *)_Buff, cnt) != 0)
            {
                f_close(&file1);            /* program failed! Close file.                */
                return;                     /* Abort...                                   */
            }
        }

        if (f_eof(&file1))                  /* reach end-of-file?                         */
            printf("SPROM update success.\n");   /* firmware update success               */
        else
            printf("SPROM update failed!\n");    /* firmware update failed                */

        f_close(&file1);                    /* close file                                 */
    }

    /*------------------------------------------------------------------------------------*/
    /*  Try to open Data Flash data image. If found, read and update Data Flash.          */
    /*------------------------------------------------------------------------------------*/
    if (FMC_Read(FMC_USER_CONFIG_0) & 0x1)   /* Data Flash is enabled?                     */
    {
        printf("Data Flash is not enabled.\n");  /* Data Flash is not enabled             */
        return;                             /* Skip Data Flash update                     */
    }

    dfba = FMC_ReadDataFlashBaseAddr();     /* get Data Flash base address                */
    /* try to open Data Flash update image        */
    if (f_open(&file1, DATA_FILE_NAME, FA_OPEN_EXISTING | FA_READ))
    {
        /* File not found                             */
        printf("Data file %s not found.\n", DATA_FILE_NAME);
    }
    else
    {
        /* Data image found, start updating...        */
        for (addr = dfba; ; addr += FMC_FLASH_PAGE_SIZE)   /* flash page loop             */
        {
            cnt = FMC_FLASH_PAGE_SIZE;      /* will program a flash page                  */
            res = f_read(&file1, _Buff, cnt, &cnt);   /* Read a page size from file       */
            if ((res == FR_OK) && cnt)
            {
                /* file read success, program to flash        */
                if (program_flash_page(addr, (uint32_t *)_Buff, cnt) != 0)   /* program?   */
                {
                    /* program failed                             */
                    f_close(&file1);        /* close file                                 */
                    return;                 /* Abort...                                   */
                }
            }
            else                            /* Read failed or reached end-of-file         */
                break;
        }

        if (f_eof(&file1))                  /* is end-of-file?                            */
            printf("Data Flash update success.\n");   /* Data flash update success        */
        else
            printf("Data Flash update failed!\n");    /* Data Flash update failed         */

        f_close(&file1);                    /* close file                                 */
    }
}


/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/

