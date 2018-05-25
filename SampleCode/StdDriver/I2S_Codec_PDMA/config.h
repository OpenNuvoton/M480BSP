/**************************************************************************//**
 * @file     config.h
 * @version  V1.00
 * @brief    I2S Driver Sample Configuration Header File
 *
 * @copyright (C) 2016 Nuvoton Technology Corp. All rights reserved.
 *
 ******************************************************************************/
#ifndef CONFIG_H
#define CONFIG_H

// use LIN as source, undefined it if MIC is used
#define INPUT_IS_LIN

/*---------------------------------------------------------------------------------------------------------*/
/* Global variables                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
#define BUFF_LEN        512
#define BUFF_HALF_LEN   (BUFF_LEN/2)

typedef struct dma_desc_t
{
    uint32_t ctl;
    uint32_t src;
    uint32_t dest;
    uint32_t offset;
} DMA_DESC_T;

extern void PDMA_ResetTxSGTable(uint8_t id);
extern void PDMA_ResetRxSGTable(uint8_t id);
extern void PDMA_Init(void);
#endif

/*** (C) COPYRIGHT 2016 Nuvoton Technology Corp. ***/
