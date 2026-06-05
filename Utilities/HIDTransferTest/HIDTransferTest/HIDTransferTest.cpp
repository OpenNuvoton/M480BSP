/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Copyright (c) 2010 Nuvoton Technology Corp. All rights reserved.                                        */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#include "stdafx.h"
#include "HID.hpp"
#include "version.h"

#define USB_VID			0x0416  /* Vendor ID */
#define USB_PID_DEFAULT	0x5020  /* Product ID (default) */

#define HID_CMD_SIGNATURE   0x43444948

/* HID Transfer Commands */
#define HID_CMD_NONE     0x00
#define HID_CMD_ERASE    0x71
#define HID_CMD_READ     0xD2
#define HID_CMD_WRITE    0xC3
#define HID_CMD_TEST     0xB4

#define SECTOR_SIZE     g_PAGE_SIZE
#if (HID_MAX_PACKET_SIZE_EP == 1024)
#define PAGE_SIZE_DEFAULT       1024
#define HID_PACKET_SIZE 1024
#else
#define HID_PACKET_SIZE 512
#define PAGE_SIZE_DEFAULT       512
#endif


#define USB_TIME_OUT    100

using namespace std;

/* Global variables for configurable parameters */
unsigned int g_USB_PID = USB_PID_DEFAULT;
unsigned int g_PAGE_SIZE = PAGE_SIZE_DEFAULT;
int g_ENABLE_VERIFY = 0;  /* Enable blank check & data verify (default: disabled) */
int g_USE_CONTROL_TRANSFER = 0;  /* Use HID control transfer instead of interrupt transfer (default: disabled) */

/* Test parameters (default values) */
#define TEST_PAGES_DEFAULT   1          /* 1 page */
#define TEST_BASE_DEFAULT    0x10000    /* 64kbytes */

unsigned int g_TEST_PAGES = TEST_PAGES_DEFAULT;
unsigned int g_TEST_BASE = TEST_BASE_DEFAULT;

#pragma pack(push)  /* push current alignment to stack */
#pragma pack(1)     /* set alignment to 1 byte boundary */

typedef struct {
    unsigned char cmd;
    unsigned char len;
    unsigned int arg1;
    unsigned int arg2;
    unsigned int signature;
    unsigned int checksum;
}CMD_T;

#pragma pack(pop)   /* restore original alignment from stack */



unsigned int CalCheckSum(unsigned char *buf, unsigned int size)
{
    unsigned int sum;
    int i;

    i = 0;
    sum = 0;
    while(size--)
    {
        sum+=buf[i++];
    }

    return sum;

}

/*
    This function is used to read data through USB HID.
    
    pReadBuf - [in ] The read buffer to store the data from USB HID. User must make sure its size is enough.
    startPage- [out] The start page to read. The page size should be dependent on SPI Flash.
    pages    - [out] The number of pages to read.

    return value is the total read bytes.
*/
int ReadPages(unsigned char *pReadBuf, unsigned int startPage, unsigned int pages)
{
    CHidCmd io;
    CMD_T cmd;
    unsigned long length;
    BOOL bRet;
    unsigned long readBytes, count=0;
    bool isDeviceOpened;

	readBytes = 0;
	isDeviceOpened = 0;
	if(!io.OpenDevice(USB_VID, g_USB_PID))
	{
		printf("Can't Open HID Device\n");
		goto lexit;
	}
	else
	{
		isDeviceOpened = TRUE;
		printf("USB HID Device VID[%04x] PID[%04x] Open Success.\n", USB_VID, g_USB_PID);
		printf(">>> Read pages: %d - %d\n", startPage, startPage + pages - 1);

		cmd.cmd = HID_CMD_READ;
		cmd.len = sizeof(cmd) - 4; /* Not include checksum */
		cmd.arg1 = startPage;
		cmd.arg2 = pages;
		cmd.signature = HID_CMD_SIGNATURE;
		cmd.checksum = CalCheckSum((unsigned char *)&cmd, cmd.len   );

		bRet = io.WriteFile((unsigned char *)&cmd, sizeof(cmd), &length, USB_TIME_OUT);
		if(!bRet)
		{
			printf("ERROR: Send read command error!\n");
			goto lexit;
		}

		while(1)
		{
			if(readBytes >= cmd.arg2 * g_PAGE_SIZE)
			{
				break;
			}

            bRet = io.ReadFile(pReadBuf + readBytes, 256, &length, USB_TIME_OUT);
            if(!bRet)
            {
                printf("ERROR: Read fail!\n");
                goto lexit;
            }
            readBytes += length;
		}
    }

lexit:
    
    if(isDeviceOpened)
        io.CloseDevice();

	return readBytes;
}

/*
    This function is used to erase sectors of target device.
    
    startSector- [out] The start sector to erase. The sector size should be dependent on SPI Flash.
    sectors    - [out] The number of sectors to erase.

    return value is the total erased sec.
*/
int EraseSectors(unsigned int startSector, unsigned int sectors)
{
    CHidCmd io;
    CMD_T cmd;
    unsigned long length;
    BOOL bRet;
    bool isDeviceOpened;
    unsigned int eraseCnt;

	eraseCnt = 0;
	isDeviceOpened = 0;
	if(!io.OpenDevice(USB_VID, g_USB_PID))
	{
		printf("Can't Open HID Device\n");
		goto lexit;
	}
	else
	{
		isDeviceOpened = TRUE;
		printf("USB HID Device VID[%04x] PID[%04x] Open Success.\n", USB_VID, g_USB_PID);
        printf(">>> Erase sectors: %d - %d\n", startSector, startSector + sectors - 1);

        cmd.cmd = HID_CMD_ERASE;
        cmd.len = sizeof(cmd) - 4; /* Not include checksum */
        cmd.arg1 = startSector;
        cmd.arg2 = sectors;
        cmd.signature = HID_CMD_SIGNATURE;
        cmd.checksum = CalCheckSum((unsigned char *)&cmd, cmd.len   );
        
        bRet = io.WriteFile((unsigned char *)&cmd, sizeof(cmd), &length, USB_TIME_OUT);
        if(!bRet)
        {
            printf("ERROR: Send erase command error!\n");
            goto lexit;
        }
        eraseCnt = sectors;
    }


lexit:
    
    if(isDeviceOpened)
        io.CloseDevice();

    return eraseCnt;
}


/*
    This function is used to program data to target device through USB HID.
    
    pWriteBuf- [in ] The buffer of programming data. User must make sure its size is enough.
    startPage- [out] The start page to program SPI Flash. The page size should be dependent on SPI Flash.
    pages    - [out] The number of pages to program.

    return value is the total programming bytes.
*/
int WritePages(unsigned char *pWriteBuf, unsigned int startPage, unsigned int pages)
{
    CHidCmd io;
    CMD_T cmd;
    unsigned long length;
    BOOL bRet;
    unsigned long writeBytes;
    bool isDeviceOpened;

	writeBytes = 0;
	isDeviceOpened = 0;
	if(!io.OpenDevice(USB_VID, g_USB_PID))
	{
		printf("Can't Open HID Device\n");
		goto lexit;
	}
	else
	{
		isDeviceOpened = TRUE;
		printf("USB HID Device VID[%04x] PID[%04x] Open Success.\n", USB_VID, g_USB_PID);
		printf(">>> Write pages: %d - %d\n", startPage, startPage + pages - 1);

		cmd.cmd = HID_CMD_WRITE;
		cmd.len = sizeof(cmd) - 4; /* Not include checksum */
		cmd.arg1 = startPage;
		cmd.arg2 = pages;
		cmd.signature = HID_CMD_SIGNATURE;
		cmd.checksum = CalCheckSum((unsigned char *)&cmd, cmd.len   );

		bRet = io.WriteFile((unsigned char *)&cmd, sizeof(cmd), &length, USB_TIME_OUT);
		if(!bRet)
		{
			printf("ERROR: Send read command error!\n");
			goto lexit;
		}

		while(1)
		{
			if(writeBytes >= cmd.arg2 * g_PAGE_SIZE)
			{
				break;
			}

            bRet = io.WriteFile(pWriteBuf + writeBytes, HID_PACKET_SIZE, &length, USB_TIME_OUT);
            if(!bRet)
            {
                printf("ERROR: Write fail!\n");
                goto lexit;
            }
            writeBytes += length;
		}
    }


lexit:
    
    if(isDeviceOpened)
        io.CloseDevice();

    return writeBytes;
}

/*
    Control Transfer Functions - Use HidD_SetOutputReport/HidD_GetInputReport
*/

/* Control Transfer Test - Send and receive test data */
int ControlTransferTest()
{
    CHidCtrlTransfer io;
    BOOL bRet;
    unsigned char OutputReport[256] = {0};
    unsigned char InputReport[256] = {0};
    bool isDeviceOpened = FALSE;

    if(!io.OpenDevice(USB_VID, g_USB_PID))
    {
        printf("Can't Open HID Device for Control Transfer\n");
        return -1;
    }

    isDeviceOpened = TRUE;
    printf("USB HID Device VID[%04x] PID[%04x] Open Success (Control Transfer Mode).\n", USB_VID, g_USB_PID);
    printf(">>> Control Transfer Test\n");
    printf("  Output Report Length: %d bytes\n", io.GetOutputReportLength());
    printf("  Input Report Length: %d bytes\n", io.GetInputReportLength());

    // Prepare output report with test pattern
    for(int i = 0; i < io.GetOutputReportLength(); i++)
    {
        OutputReport[i] = (unsigned char)i;
    }

    // Send Output Report
    printf("Sending Output Report...\n");
    bRet = io.SetOutputReport(OutputReport, io.GetOutputReportLength());
    if(!bRet)
    {
        printf("ERROR: Failed to send Output Report! Error code: %d\n", GetLastError());
        io.CloseDevice();
        return -1;
    }
    printf("Output Report sent successfully.\n");

    // Small delay to let device process
    Sleep(100);

    // Receive Input Report
    printf("Receiving Input Report...\n");
    bRet = io.GetInputReport(InputReport, io.GetInputReportLength());
    if(!bRet)
    {
        printf("ERROR: Failed to receive Input Report! Error code: %d\n", GetLastError());
        io.CloseDevice();
        return -1;
    }
    printf("Input Report received successfully.\n");

    // Display received data
    printf("Received Input Report Data:\n");
    for(int i = 0; i < io.GetInputReportLength() && i < 64; i++)
    {
        printf("%02X ", InputReport[i]);
        if((i + 1) % 16 == 0)
            printf("\n");
    }
    printf("\n");

    printf("Control Transfer test completed successfully!\n");

    io.CloseDevice();
    return 0;
}

/*
    This function is used to be an simple demo of send command. User may use it as an example to add new command.
*/
int SendTestCmd(void)
{
    CHidCmd io;
    CMD_T cmd;
    unsigned long length;
    BOOL bRet;
    bool isDeviceOpened;


	isDeviceOpened = 0;
	if(!io.OpenDevice(USB_VID, g_USB_PID))
	{
		printf("Can't Open HID Device\n");
		goto lexit;
	}
	else
	{
		isDeviceOpened = TRUE;
		printf("USB HID Device VID[%04x] PID[%04x] Open Success.\n", USB_VID, g_USB_PID);
        printf(">>> Test command\n");

        cmd.cmd = HID_CMD_TEST;
        cmd.len = sizeof(cmd) - 4; /* Not include checksum */
        cmd.arg1 = 0x12345678;
        cmd.arg2 = 0xabcdef01;
        cmd.signature = HID_CMD_SIGNATURE;
        cmd.checksum = CalCheckSum((unsigned char *)&cmd, cmd.len);
        
        bRet = io.WriteFile((unsigned char *)&cmd, sizeof(cmd), &length, USB_TIME_OUT);
        if(!bRet)
        {
            printf("ERROR: Send test command error!\n");
            goto lexit;
        }
    }


lexit:
    
    if(isDeviceOpened)
        io.CloseDevice();

    return 0;
}


int main(int argc, char* argv[])
{
    unsigned int i;
    unsigned int idx;
    int isErr;

    printf("HID Transfer Test Tool v%s\n", TOOL_VERSION_STR);
    printf("======================\n");

    /* Parse command line arguments */
    for(i = 1; (int)i < argc; i++)
    {
        if(strcmp(argv[i], "-pid") == 0 || strcmp(argv[i], "--pid") == 0)
        {
            if((int)i + 1 < argc)
            {
                i++;
                if(strncmp(argv[i], "0x", 2) == 0 || strncmp(argv[i], "0X", 2) == 0)
                {
                    g_USB_PID = strtoul(argv[i], NULL, 16);
                }
                else
                {
                    g_USB_PID = strtoul(argv[i], NULL, 10);
                }
                printf("USB PID set to: 0x%04X\n", g_USB_PID);
            }
            else
            {
                printf("ERROR: -pid requires a value\n");
                printf("Usage: %s [-pid <id>] [-pagesize <size>] [-pages <count>] [-base <addr>] [-verify] [-ctrl]\n", argv[0]);
                printf("  -pid <product_id> : USB Product ID (hex value, e.g., 0x5020)\n");
                printf("  -pagesize <size>  : Page size in bytes (512 or 1024)\n");
                printf("  -pages <count>    : Number of pages to test\n");
                printf("  -base <address>   : Test base address\n");
                printf("  -verify           : Enable blank check and data verify\n");
                printf("  -ctrl             : Use HID Control Transfer mode\n");
                return -1;
            }
        }
        else if(strcmp(argv[i], "-pagesize") == 0 || strcmp(argv[i], "--pagesize") == 0)
        {
            if((int)i + 1 < argc)
            {
                i++;
                g_PAGE_SIZE = atoi(argv[i]);
                printf("Page size set to: %d bytes\n", g_PAGE_SIZE);
            }
            else
            {
                printf("ERROR: -pagesize requires a value\n");
                printf("Usage: %s [-pid <id>] [-pagesize <size>] [-pages <count>] [-base <addr>] [-verify] [-ctrl]\n", argv[0]);
                printf("  -pid <product_id> : USB Product ID (hex or decimal, e.g., 0x5020 or 20512)\n");
                printf("  -pagesize <size>  : Page size in bytes (512 or 1024)\n");
                printf("  -pages <count>    : Number of pages to test\n");
                printf("  -base <address>   : Test base address\n");
                printf("  -verify           : Enable blank check and data verify\n");
                printf("  -ctrl             : Use HID Control Transfer mode\n");
                return -1;
            }
        }
        else if(strcmp(argv[i], "-pages") == 0 || strcmp(argv[i], "--pages") == 0)
        {
            if((int)i + 1 < argc)
            {
                i++;
                if(strncmp(argv[i], "0x", 2) == 0 || strncmp(argv[i], "0X", 2) == 0)
                {
                    g_TEST_PAGES = strtoul(argv[i], NULL, 16);
                }
                else
                {
                    g_TEST_PAGES = strtoul(argv[i], NULL, 10);
                }
                printf("Test pages set to: %d\n", g_TEST_PAGES);
            }
            else
            {
                printf("ERROR: -pages requires a value\n");
                printf("Usage: %s [-pid <product_id>] [-pagesize <size>] [-pages <count>] [-base <address>] [-verify]\n", argv[0]);
                return -1;
            }
        }
        else if(strcmp(argv[i], "-base") == 0 || strcmp(argv[i], "--base") == 0)
        {
            if((int)i + 1 < argc)
            {
                i++;
                if(strncmp(argv[i], "0x", 2) == 0 || strncmp(argv[i], "0X", 2) == 0)
                {
                    g_TEST_BASE = strtoul(argv[i], NULL, 16);
                }
                else
                {
                    g_TEST_BASE = strtoul(argv[i], NULL, 10);
                }
                printf("Test base address set to: 0x%08X\n", g_TEST_BASE);
            }
            else
            {
                printf("ERROR: -base requires a value\n");
                printf("Usage: %s [-pid <product_id>] [-pagesize <size>] [-pages <count>] [-base <address>] [-verify]\n", argv[0]);
                return -1;
            }
        }
        else if(strcmp(argv[i], "-verify") == 0 || strcmp(argv[i], "--verify") == 0)
        {
            g_ENABLE_VERIFY = 1;
            printf("Verification enabled: Blank check and data verify will be performed\n");
        }
        else if(strcmp(argv[i], "-ctrl") == 0 || strcmp(argv[i], "--ctrl") == 0 || strcmp(argv[i], "-control") == 0)
        {
            g_USE_CONTROL_TRANSFER = 1;
            printf("Control Transfer mode enabled: Using HidD_SetOutputReport/HidD_GetInputReport\n");
        }
        else if(strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "-version") == 0 || strcmp(argv[i], "--version") == 0)
        {
            printf("HID Transfer Test Tool version %s\n", TOOL_VERSION_STR);
            printf("Copyright (c) 2010 Nuvoton Technology Corp. All rights reserved.\n");
            return 0;
        }
        else if(strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "/?") == 0)
        {
            printf("Usage: %s [-pid <id>] [-pagesize <size>] [-pages <count>] [-base <addr>] [-verify] [-ctrl]\n", argv[0]);
            printf("\nOptions:\n");
            printf("  -pid <product_id> : USB Product ID (hex or decimal, e.g., 0x5020 or 20512)\n");
            printf("                      Default: 0x%04X\n", USB_PID_DEFAULT);
            printf("  -pagesize <size>  : Page size in bytes (512 or 1024)\n");
            printf("                      Default: %d bytes\n", PAGE_SIZE_DEFAULT);
            printf("  -pages <count>    : Number of pages to test (decimal or hex)\n");
            printf("                      Default: %d pages\n", TEST_PAGES_DEFAULT);
            printf("  -base <address>   : Test base address (hex or decimal)\n");
            printf("                      Default: 0x%08X\n", TEST_BASE_DEFAULT);
            printf("  -verify           : Enable blank check and data verify (default: disabled)\n");
            printf("  -ctrl, -control   : Use HID Control Transfer (SetOutputReport/GetInputReport)\n");
            printf("                      Default: Interrupt Transfer mode\n");
            printf("  -v, -version      : Show version information\n");
            printf("  -h, --help, /?    : Show this help message\n");
            printf("\nExamples:\n");
            printf("  %s -pid 0x5021 -pagesize 1024 -pages 100 -base 0x20000 -verify\n", argv[0]);
            printf("  %s -pid 0x5020 -ctrl    (Use Control Transfer mode)\n", argv[0]);
            return 0;
        }
        else
        {
            printf("ERROR: Unknown argument: %s\n", argv[i]);
            printf("Usage: %s [-pid <id>] [-pagesize <size>] [-pages <count>] [-base <addr>] [-verify] [-ctrl]\n", argv[0]);
            printf("Use -h or --help for more information\n");
            return -1;
        }
    }

    printf("\nConfiguration:\n");
    printf("  USB VID: 0x%04X\n", USB_VID);
    printf("  USB PID: 0x%04X\n", g_USB_PID);
    printf("  Transfer Mode: %s\n", g_USE_CONTROL_TRANSFER ? "Control Transfer" : "Interrupt Transfer");
    printf("  Page Size: %d bytes\n", g_PAGE_SIZE);
    printf("  Test Pages: %d\n", g_TEST_PAGES);
    printf("  Test Base: 0x%08X\n", g_TEST_BASE);
    printf("  Test Size: %d bytes (0x%X)\n", g_TEST_PAGES * g_PAGE_SIZE, g_TEST_PAGES * g_PAGE_SIZE);
    printf("  Verification: %s\n", g_ENABLE_VERIFY ? "Enabled" : "Disabled");
    printf("\n");

    /* Check if Control Transfer mode is enabled */
    if(g_USE_CONTROL_TRANSFER)
    {
        printf("*** Control Transfer Mode ***\n");
        int result = ControlTransferTest();
        return result;
    }

    /* Allocate buffer dynamically based on test size */
    unsigned int bufSize = g_TEST_PAGES * g_PAGE_SIZE;
    unsigned char *buf = (unsigned char*)malloc(bufSize);
    if(buf == NULL)
    {
        printf("ERROR: Failed to allocate %d bytes for buffer\n", bufSize);
        return -1;
    }

    /* Erase test space */
    EraseSectors(g_TEST_BASE / SECTOR_SIZE, (g_TEST_PAGES*g_PAGE_SIZE)/SECTOR_SIZE);

    /* Blank check */
    if(g_ENABLE_VERIFY)
    {
        printf("Performing blank check...\n");
        ReadPages(buf, g_TEST_BASE / g_PAGE_SIZE, g_TEST_PAGES);

        isErr = 0;
        for(idx=0;idx<g_TEST_PAGES*g_PAGE_SIZE;idx++)
        {
            if(buf[idx] != (unsigned char)0xFF)
            {
                isErr = 1;
                printf("ERROR: Blank check fail at index %d, expected 0xFF, got 0x%02X\n", idx, buf[idx]);
                break;
            }
        }

        if(isErr)
        {
            printf("ERROR: Blank test fail!\n");
            return -1;
        }
        printf("Blank check passed.\n");
    }

    for(idx=0;idx<g_TEST_PAGES*g_PAGE_SIZE;idx++)
        buf[idx] = idx & 0xFF;

    /* Write test data */
    WritePages(buf, g_TEST_BASE / g_PAGE_SIZE, g_TEST_PAGES);

    /* Read back and verify */
    if(g_ENABLE_VERIFY)
    {
        printf("Performing data verify...\n");
        /* Clean the buffer */
        memset(buf, 0xCC, g_TEST_PAGES*g_PAGE_SIZE);

        ReadPages(buf, g_TEST_BASE / g_PAGE_SIZE, g_TEST_PAGES);
        isErr = 0;
        for(idx=0;idx<g_TEST_PAGES*g_PAGE_SIZE;idx++)
        {
            if(buf[idx] != (idx & 0xFF))
            {
                printf("ERROR: Data mismatch at index %d, expected 0x%02X, got 0x%02X\n", idx, (idx & 0xFF), buf[idx]);
                isErr = 1;
                break;
            }
        }

        if(isErr)
        {
            printf("ERROR: Programming test fail!\n");
            return -1;
        }
        printf("Data verify passed.\n");
    }

    if(g_ENABLE_VERIFY)
    {
        printf("\nHID Transfer test ok! (All tests passed)\n");
    }
    else
    {
        printf("\nHID Transfer Tool execute completed!\n");
    }

    return 0;
}