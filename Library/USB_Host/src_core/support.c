/**************************************************************************//**
 * @file     support.c
 * @version  V1.10
 * $Revision: 11 $
 * $Date: 14/10/03 1:54p $
 * @brief  Functions to support USB host driver.
 *
 * @note
 * Copyright (C) 2015 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "M480.h"

#include "usb.h"

/// @cond HIDDEN_SYMBOLS

//#define USBMEM_USE_HEAP      // using heap, otherwise, static memory


static uint32_t  _FreeMemorySize;
uint32_t  _AllocatedMemorySize;


#ifdef USBMEM_USE_HEAP


void  USB_InitializeMemoryPool()
{
    _FreeMemorySize = USB_MEMORY_POOL_SIZE;
    _AllocatedMemorySize = 0;
}


int  USB_available_memory()
{
    return USB_MEMORY_POOL_SIZE;
}

void  *USB_malloc(int wanted_size, int boundary)
{
    void  *ptr;

    ptr = malloc(wanted_size);

    return ptr;
}

void  USB_free(void *alloc_addr)
{
    free(alloc_addr);
}

#else  // static memory

#define USB_MEM_ALLOC_MAGIC     0x19685788    /* magic number in leading block */

typedef struct USB_mhdr {
    uint32_t  flag;  /* 0:free, 1:allocated, 0x3:first block */
    uint32_t  bcnt;  /* if allocated, the block count of allocated memory block */
    uint32_t  magic;
    uint32_t  reserved;
}  USB_MHDR_T;

#ifdef __ICCARM__
#pragma data_alignment=USB_MEM_BLOCK_SIZE
uint8_t  _USBMemoryPool[USB_MEMORY_POOL_SIZE];
#else
__align(USB_MEM_BLOCK_SIZE) uint8_t  _USBMemoryPool[USB_MEMORY_POOL_SIZE];
#endif


static USB_MHDR_T  *_pCurrent;
uint32_t  *_USB_pCurrent = (uint32_t *)&_pCurrent;

static uint32_t  _MemoryPoolBase, _MemoryPoolEnd;

extern int    _IsInUsbInterrupt;


void  USB_InitializeMemoryPool()
{
    _MemoryPoolBase = (uint32_t)&_USBMemoryPool[0];
    _MemoryPoolEnd = _MemoryPoolBase + USB_MEMORY_POOL_SIZE;
    _FreeMemorySize = _MemoryPoolEnd - _MemoryPoolBase;
    _AllocatedMemorySize = 0;
    _pCurrent = (USB_MHDR_T *)_MemoryPoolBase;
    memset((char *)_MemoryPoolBase, 0, _FreeMemorySize);
}


int  USB_available_memory()
{
    return _FreeMemorySize;
}


int  USB_allocated_memory()
{
    return _AllocatedMemorySize;
}


void  *USB_malloc(int wanted_size, int boundary)
{
    USB_MHDR_T  *pPrimitivePos = _pCurrent;
    USB_MHDR_T  *pFound = NULL;
    int   found_size=-1;
    int   i, block_count = 0;
    int   wrap = 0;

    if (!_IsInUsbInterrupt)
        DISABLE_USB_INT();

    if (wanted_size >= _FreeMemorySize) {
        printf("USB_malloc - want=%d, free=%d\n", wanted_size, _FreeMemorySize);
        if (!_IsInUsbInterrupt)
            ENABLE_USB_INT();
        return NULL;
    }

    if ((uint32_t)_pCurrent >= _MemoryPoolEnd)
        _pCurrent = (USB_MHDR_T *)_MemoryPoolBase;   /* wrapped */

    do {
        if (_pCurrent->flag) {        /* is not a free block */
            if (_pCurrent->magic != USB_MEM_ALLOC_MAGIC) {
                printf("\nUSB_malloc - incorrect magic number! C:%x F:%x, wanted:%d, Base:0x%x, End:0x%x\n", (uint32_t)_pCurrent, _FreeMemorySize, wanted_size, (uint32_t)_MemoryPoolBase, (uint32_t)_MemoryPoolEnd);
                if (!_IsInUsbInterrupt)
                    ENABLE_USB_INT();
                return NULL;
            }

            if (_pCurrent->flag == 0x3)
                _pCurrent = (USB_MHDR_T *)((uint32_t)_pCurrent + _pCurrent->bcnt * USB_MEM_BLOCK_SIZE);
            else {
                printf("USB_malloc warning - not the first block!\n");
                _pCurrent = (USB_MHDR_T *)((uint32_t)_pCurrent + USB_MEM_BLOCK_SIZE);
            }

            if ((uint32_t)_pCurrent > _MemoryPoolEnd)
                printf("USB_malloc - behind limit!!\n");

            if ((uint32_t)_pCurrent == _MemoryPoolEnd) {
                //printf("USB_alloc - warp!!\n");
                wrap = 1;
                _pCurrent = (USB_MHDR_T *)_MemoryPoolBase;   /* wrapped */
            }

            found_size = -1;          /* reset the accumlator */
        } else {                     /* is a free block */
            if (found_size == -1) {   /* the leading block */
                pFound = _pCurrent;
                block_count = 1;

                if (boundary > BOUNDARY_WORD)
                    found_size = 0;    /* not use the data area of the leading block */
                else
                    found_size = USB_MEM_BLOCK_SIZE - sizeof(USB_MHDR_T);

                /* check boundary -
                 * If boundary > BOUNDARY_WORD, the start of next block should
                 * be the beginning address of allocated memory. Thus, we check
                 * the boundary of the next block. The leading block will be
                 * used as a header only.
                 */
                if ((boundary > BOUNDARY_WORD) &&
                        ((((uint32_t)_pCurrent)+USB_MEM_BLOCK_SIZE >= _MemoryPoolEnd) ||
                         ((((uint32_t)_pCurrent)+USB_MEM_BLOCK_SIZE) % boundary != 0)))
                    found_size = -1;   /* violate boundary, reset the accumlator */
            } else {                  /* not the leading block */
                found_size += USB_MEM_BLOCK_SIZE;
                block_count++;
            }

            if (found_size >= wanted_size) {
                pFound->bcnt = block_count;
                pFound->magic = USB_MEM_ALLOC_MAGIC;
                _FreeMemorySize -= block_count * USB_MEM_BLOCK_SIZE;
                _AllocatedMemorySize += block_count * USB_MEM_BLOCK_SIZE;
                _pCurrent = pFound;
                for (i=0; i<block_count; i++) {
                    _pCurrent->flag = 1;     /* allocate block */
                    _pCurrent = (USB_MHDR_T *)((uint32_t)_pCurrent + USB_MEM_BLOCK_SIZE);
                }
                pFound->flag = 0x3;

                if (boundary > BOUNDARY_WORD) {
                    if (!_IsInUsbInterrupt)
                        ENABLE_USB_INT();
                    //printf("- 0x%x, %d\n", (int)pFound, wanted_size);
                    return (void *)((uint32_t)pFound + USB_MEM_BLOCK_SIZE);
                } else {
                    //USB_debug("USB_malloc(%d,%d):%x\tsize:%d, C:0x%x, %d\n", wanted_size, boundary, (uint32_t)pFound + sizeof(USB_MHDR_T), block_count * USB_MEM_BLOCK_SIZE, _pCurrent, block_count);
                    if (!_IsInUsbInterrupt)
                        ENABLE_USB_INT();
                    //printf("- 0x%x, %d\n", (int)pFound, wanted_size);
                    return (void *)((uint32_t)pFound + sizeof(USB_MHDR_T));
                }
            }

            /* advance to the next block */
            _pCurrent = (USB_MHDR_T *)((uint32_t)_pCurrent + USB_MEM_BLOCK_SIZE);
            if ((uint32_t)_pCurrent >= _MemoryPoolEnd) {
                wrap = 1;
                _pCurrent = (USB_MHDR_T *)_MemoryPoolBase;   /* wrapped */
                found_size = -1;     /* reset accumlator */
            }
        }
    } while ((wrap == 0) || (_pCurrent < pPrimitivePos));

    printf("USB_malloc - No free memory!\n");
    if (!_IsInUsbInterrupt)
        ENABLE_USB_INT();
    return NULL;
}


void  USB_free(void *alloc_addr)
{
    USB_MHDR_T  *pMblk;
    uint32_t  addr = (uint32_t)alloc_addr;
    int     i, count;

    //printf("USB_free: 0x%x\n", (int)alloc_addr);

    if ((addr < _MemoryPoolBase) || (addr >= _MemoryPoolEnd)) {
        if (addr)
            free(alloc_addr);
        return;
    }

    if (!_IsInUsbInterrupt)
        DISABLE_USB_INT();

    //printf("USB_free:%x\n", (int)addr+USB_MEM_BLOCK_SIZE);

    /* get the leading block address */
    if (addr % USB_MEM_BLOCK_SIZE == 0)
        addr -= USB_MEM_BLOCK_SIZE;
    else
        addr -= sizeof(USB_MHDR_T);

    if (addr % USB_MEM_BLOCK_SIZE != 0) {
        printf("USB_free fatal error on address: %x!!\n", (uint32_t)alloc_addr);
        if (!_IsInUsbInterrupt)
            ENABLE_USB_INT();
        return;
    }

    pMblk = (USB_MHDR_T *)addr;
    if (pMblk->flag == 0) {
        //printf("USB_free(), warning - try to free a free block: %x\n", (uint32_t)alloc_addr);
        if (!_IsInUsbInterrupt)
            ENABLE_USB_INT();
        return;
    }
    if (pMblk->magic != USB_MEM_ALLOC_MAGIC) {
        printf("USB_free(), warning - try to free an unknow block at address:%x.\n", addr);
        if (!_IsInUsbInterrupt)
            ENABLE_USB_INT();
        return;
    }

    //_pCurrent = pMblk;

    //printf("+ 0x%x, %d\n", (int)pMblk, pMblk->bcnt);

    count = pMblk->bcnt;
    for (i = 0; i < count; i++) {
        pMblk->flag = 0;     /* release block */
        pMblk = (USB_MHDR_T *)((uint32_t)pMblk + USB_MEM_BLOCK_SIZE);
    }

    _FreeMemorySize += count * USB_MEM_BLOCK_SIZE;
    _AllocatedMemorySize -= count * USB_MEM_BLOCK_SIZE;
    if (!_IsInUsbInterrupt)
        ENABLE_USB_INT();
    return;
}

#endif

/*-------------------------------------------------------------------------
 *  Logging System
 *-------------------------------------------------------------------------*/

#ifdef LOG_TO_MEMORY
#define UART_putchar(c) {  \
                        _DriverLogPool[_DriverLogIndex] = c; \
                        _DriverLogIndex = (_DriverLogIndex+1) % DRIVER_LOG_MEMORY_SIZE; \
                        }
#endif


/// @endcond HIDDEN_SYMBOLS

