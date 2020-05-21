/**************************************************************************//**
 * @file    spim.c
 * @version V1.00
 * @brief   M480 series SPIM driver
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
*****************************************************************************/

#include <stdio.h>
#include <string.h>
#include "NuMicro.h"


/** @addtogroup Standard_Driver Standard Driver
  @{
*/

/** @addtogroup SPIM_Driver SPIM Driver
  @{
*/

/** @addtogroup SPIM_EXPORTED_FUNCTIONS SPIM Exported Functions
  @{
*/


/** @cond HIDDEN_SYMBOLS */


#define ENABLE_DEBUG    0

#if ENABLE_DEBUG
#define SPIM_DBGMSG   printf
#else
#define SPIM_DBGMSG(...)   do { } while (0)      /* disable debug */
#endif

static volatile uint8_t  g_Supported_List[] =
{
    MFGID_WINBOND,
//    MFGID_MXIC,
//    MFGID_EON,
//    MFGID_ISSI,
//    MFGID_SPANSION
};

static void SwitchNBitOutput(uint32_t u32NBit);
static void SwitchNBitInput(uint32_t u32NBit);
static void spim_write(uint8_t pu8TxBuf[], uint32_t u32NTx);
static void spim_read(uint8_t pu8RxBuf[], uint32_t u32NRx);
static void SPIM_WriteStatusRegister(uint8_t dataBuf[], uint32_t u32NTx, uint32_t u32NBit);
static void SPIM_ReadStatusRegister(uint8_t dataBuf[], uint32_t u32NRx, uint32_t u32NBit);
static void SPIM_ReadStatusRegister2(uint8_t dataBuf[], uint32_t u32NRx, uint32_t u32NBit);
static void SPIM_WriteStatusRegister2(uint8_t dataBuf[], uint32_t u32NTx, uint32_t u32NBit);
static int spim_is_write_done(uint32_t u32NBit);
static int spim_wait_write_done(uint32_t u32NBit);
static void spim_set_write_enable(int isEn, uint32_t u32NBit);
static void SPIM_WriteInPageDataByPageWrite(uint32_t u32Addr, int is4ByteAddr, uint32_t u32NTx,
        uint8_t pu8TxBuf[], uint32_t wrCmd, int isSync);

static void SwitchNBitOutput(uint32_t u32NBit)
{
//    switch (u32NBit)
//    {
//    case 1UL:
        SPIM_ENABLE_SING_OUTPUT_MODE();     /* 1-bit, Output. */
//        break;

//    case 2UL:
//        SPIM_ENABLE_DUAL_OUTPUT_MODE();     /* 2-bit, Output. */
//        break;

//    case 4UL:
//        SPIM_ENABLE_QUAD_OUTPUT_MODE();     /* 4-bit, Output. */
//        break;

//    default:
//        break;
//    }
}

static void SwitchNBitInput(uint32_t u32NBit)
{
//    switch (u32NBit)
//    {
//    case 1UL:
        SPIM_ENABLE_SING_INPUT_MODE();      /* 1-bit, Input.  */
//        break;

//    case 2UL:
//        SPIM_ENABLE_DUAL_INPUT_MODE();      /* 2-bit, Input.  */
//        break;

//    case 4UL:
//        SPIM_ENABLE_QUAD_INPUT_MODE();      /* 4-bit, Input.  */
//        break;

//    default:
//        break;
//    }
}


/**
  * @brief      Write data to SPI slave.
  * @param      pu8TxBuf    Transmit buffer.
  * @param      u32NTx      Number of bytes to transmit.
  * @return     None.
  */
static void spim_write(uint8_t pu8TxBuf[], uint32_t u32NTx)
{
    uint32_t  buf_idx = 0UL;

    while (u32NTx)
    {
        uint32_t dataNum = 0UL, dataNum2;

        if (u32NTx >= 16UL)
        {
            dataNum = 4UL;
        }
        else if (u32NTx >= 12UL)
        {
            dataNum = 3UL;
        }
        else if (u32NTx >= 8UL)
        {
            dataNum = 2UL;
        }
        else if (u32NTx >= 4UL)
        {
            dataNum = 1UL;
        }

        dataNum2 = dataNum;
        while (dataNum2)
        {
            uint32_t tmp;

            memcpy(&tmp, &pu8TxBuf[buf_idx], 4U);
            buf_idx += 4UL;
            u32NTx -= 4UL;

            dataNum2 --;
            /*  *((__O uint32_t *) &SPIM->TX0 + dataNum2) = tmp; */
            SPIM->TX[dataNum2] = tmp;
        }

        if (dataNum)
        {
            SPIM_SET_OPMODE(SPIM_CTL0_OPMODE_IO);    /* Switch to Normal mode. */
            SPIM_SET_DATA_WIDTH(32UL);
            SPIM_SET_DATA_NUM(dataNum);
            SPIM_SET_GO();
            SPIM_WAIT_FREE();
        }

        if (u32NTx && (u32NTx < 4UL))
        {
            uint32_t  rnm, tmp;

            rnm = u32NTx;
            memcpy(&tmp, &pu8TxBuf[buf_idx], u32NTx);
            buf_idx += u32NTx;
            u32NTx = 0UL;
            SPIM->TX[0] = tmp;

            SPIM_SET_OPMODE(SPIM_CTL0_OPMODE_IO);    /* Switch to Normal mode. */
            SPIM_SET_DATA_WIDTH(rnm * 8UL);
            SPIM_SET_DATA_NUM(1UL);
            SPIM_SET_GO();
            SPIM_WAIT_FREE();
        }
    }
}

/**
  * @brief      Read data from SPI slave.
  * @param      pu8TxBuf    Receive buffer.
  * @param      u32NRx      Size of receive buffer in bytes.
  * @return     None.
  */
static void spim_read(uint8_t pu8RxBuf[], uint32_t u32NRx)
{
    uint32_t  buf_idx = 0UL;

    while (u32NRx)
    {
        uint32_t dataNum = 0UL;   /* number of words */

        if (u32NRx >= 16UL)
        {
            dataNum = 4UL;
        }
        else if (u32NRx >= 12UL)
        {
            dataNum = 3UL;
        }
        else if (u32NRx >= 8UL)
        {
            dataNum = 2UL;
        }
        else if (u32NRx >= 4UL)
        {
            dataNum = 1UL;
        }

        if (dataNum)
        {
            SPIM_SET_OPMODE(SPIM_CTL0_OPMODE_IO);    /* Switch to Normal mode. */
            SPIM_SET_DATA_WIDTH(32UL);
            SPIM_SET_DATA_NUM(dataNum);
            SPIM_SET_GO();
            SPIM_WAIT_FREE();
        }

        while (dataNum)
        {
            uint32_t tmp;

            tmp = SPIM->RX[dataNum-1UL];
            memcpy(&pu8RxBuf[buf_idx], &tmp, 4U);
            buf_idx += 4UL;
            dataNum --;
            u32NRx -= 4UL;
        }

        if (u32NRx && (u32NRx < 4UL))
        {
            uint32_t tmp;

            SPIM_SET_OPMODE(SPIM_CTL0_OPMODE_IO);    /* Switch to Normal mode. */
            SPIM_SET_DATA_WIDTH(u32NRx * 8UL);
            SPIM_SET_DATA_NUM(1UL);
            SPIM_SET_GO();
            SPIM_WAIT_FREE();

            tmp = SPIM->RX[0];
            memcpy(&pu8RxBuf[buf_idx], &tmp, u32NRx);
            buf_idx += u32NRx;
            u32NRx = 0UL;
        }
    }
}

/**
  * @brief      Issue Read Status Register #1 command.
  * @param      dataBuf     Receive buffer.
  * @param      u32NRx      Size of receive buffer.
 * @param       u32NBit     N-bit transmit/receive.
  * @return     None.
  */
static void SPIM_ReadStatusRegister(uint8_t dataBuf[], uint32_t u32NRx, uint32_t u32NBit)
{
    uint8_t cmdBuf[] = {OPCODE_RDSR};            /* 1-byte Read Status Register #1 command. */

    SPIM_SET_SS_EN(1);                          /* CS activated. */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SwitchNBitInput(u32NBit);
    spim_read(dataBuf, u32NRx);
    SPIM_SET_SS_EN(0);                          /* CS deactivated. */
}

/**
  * @brief      Issue Write Status Register #1 command.
  * @param      dataBuf     Transmit buffer.
  * @param      u32NTx      Size of transmit buffer.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     None.
  */
static void SPIM_WriteStatusRegister(uint8_t dataBuf[], uint32_t u32NTx, uint32_t u32NBit)
{
    uint8_t cmdBuf[] = {OPCODE_WRSR, 0x00U};     /* 1-byte Write Status Register #1 command + 1-byte data. */

    cmdBuf[1] = dataBuf[0];
    SPIM_SET_SS_EN(1);                          /* CS activated. */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated. */
}

/**
  * @brief      Issue Read Status Register #2 command.
  * @param      dataBuf     Receive buffer.
  * @param      u32NRx      Size of receive buffer.
 * @param       u32NBit     N-bit transmit/receive.
  * @return     None.
  */
static void SPIM_ReadStatusRegister2(uint8_t dataBuf[], uint32_t u32NRx, uint32_t u32NBit)
{
    uint8_t cmdBuf[] = {OPCODE_RDSR2};           /* 1-byte Read Status Register #1 command. */

    SPIM_SET_SS_EN(1);                          /* CS activated.  */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SwitchNBitInput(u32NBit);
    spim_read(dataBuf, u32NRx);
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */
}

/**
  * @brief      Issue Winbond Write Status Register command. This command write both Status Register-1
  *             and Status Register-2.
  * @param      dataBuf     Transmit buffer.
  * @param      u32NTx      Size of transmit buffer.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     None.
  */
static void SPIM_WriteStatusRegister2(uint8_t dataBuf[], uint32_t u32NTx, uint32_t u32NBit)
{
    uint8_t cmdBuf[3] = {OPCODE_WRSR, 0U, 0U};

    cmdBuf[1] = dataBuf[0];
    cmdBuf[2] = dataBuf[1];

    SPIM_SET_SS_EN(1);                          /* CS activated.    */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */
}

#if 0  /* not used */
/**
  * @brief      Issue Write Status Register #3 command.
  * @param      dataBuf     Transmit buffer.
  * @param      u32NTx      Size of transmit buffer.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     None.
  */
static void SPIM_WriteStatusRegister3(uint8_t dataBuf[], uint32_t u32NTx, uint32_t u32NBit)
{
    uint8_t cmdBuf[] = {OPCODE_WRSR3, 0x00U};    /* 1-byte Write Status Register #2 command + 1-byte data. */
    cmdBuf[1] = dataBuf[0];

    SPIM_SET_SS_EN(1);                          /* CS activated. */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated. */
}
#endif


#if 0  /* not used */
/**
  * @brief      Issue Write Security Register command.
  * @param      dataBuf     Transmit buffer.
  * @param      u32NTx      Size of transmit buffer.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     None.
  */
static void SPIM_WriteSecurityRegister(uint8_t dataBuf[], uint32_t u32NTx, uint32_t u32NBit)
{
    uint8_t cmdBuf[] = {OPCODE_WRSCUR, 0x00U};   /* 1-byte Write Status Register #2 command + 1-byte data. */
    cmdBuf[1] = dataBuf[0];

    SPIM_SET_SS_EN(1);                          /* CS activated. */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated. */
}
#endif


/**
  * @brief      Check if Erase/Write is done.
  * @return     0: Not done. 1: Done.
  */
static int spim_is_write_done(uint32_t u32NBit)
{
    uint8_t status[1];
    SPIM_ReadStatusRegister(status, sizeof (status), u32NBit);
    return ! (status[0] & SR_WIP);
}

/**
  * @brief      Wait until Erase/Write done.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     0           SPIM write done.
  */
static int spim_wait_write_done(uint32_t u32NBit)
{
    uint32_t   count;
    int        ret = -1;

    for (count = 0UL; count < SystemCoreClock/1000UL; count++)
    {
        if (spim_is_write_done(u32NBit))
        {
            ret = 0;
            break;
        }
    }
    if (ret != 0)
    {
        SPIM_DBGMSG("spim_wait_write_done time-out!!\n");
    }
    return ret;
}

/**
  * @brief      Issue Write Enable/disable command.
  * @param      isEn        Enable/disable.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     None.
  */
static void spim_set_write_enable(int isEn, uint32_t u32NBit)
{
    uint8_t cmdBuf[] = {0U};                     /* 1-byte Write Enable command. */
    cmdBuf[0] = OPCODE_WREN;

    SPIM_SET_SS_EN(1);                          /* CS activated.   */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */
}

/** @endcond HIDDEN_SYMBOLS */

/**
  * @brief      Get SPIM serial clock.
  * @return     SPI serial clock.
  * @details    This function calculates the serial clock of SPI in Hz.
  */
uint32_t SPIM_GetSClkFreq(void)
{
    uint32_t clkDiv = SPIM_GET_CLOCK_DIVIDER();

    return clkDiv ? SystemCoreClock / (clkDiv * 2U) : SystemCoreClock;
}

/**
  * @brief      Initialize SPIM flash.
  * @param      clrWP       Clear Write Protect or not.
  * @return     0    Success.
  * @return     -1   Unrecognized manufacture ID or failed on reading manufacture ID.
  */
int SPIM_InitFlash(int clrWP)
{
    uint8_t   cmdBuf[1];
    int32_t   ret = -1;

    SPIM_SET_SS_ACTLVL(0);

    /*
     * Because not sure in SPI or QPI mode, do QPI reset and then SPI reset.
     */
    /* QPI Reset Enable */
    cmdBuf[0] = OPCODE_RSTEN;
    SPIM_SET_SS_EN(1);                          /* CS activated.    */
    SPIM_ENABLE_QUAD_OUTPUT_MODE();             /* 1-bit, Output.   */
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */

    /* QPI Reset */
    cmdBuf[0] = OPCODE_RST;
    SPIM_SET_SS_EN(1);                          /* CS activated.    */
    SPIM_ENABLE_QUAD_OUTPUT_MODE();             /* 1-bit, Output.   */
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */

    /* SPI ResetEnable */
    cmdBuf[0] = OPCODE_RSTEN;
    SPIM_SET_SS_EN(1);                          /* CS activated.    */
    SPIM_ENABLE_SING_OUTPUT_MODE();             /* 1-bit, Output.   */
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */

    /* SPI Reset */
    cmdBuf[0] = OPCODE_RST;
    SPIM_SET_SS_EN(1);                          /* CS activated.    */
    SPIM_ENABLE_SING_OUTPUT_MODE();             /* 1-bit, Output.   */
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */

    if (clrWP)
    {
        uint8_t dataBuf[] = {0x00U};

        spim_set_write_enable(1, 1UL);           /* Clear Block Protect. */
        SPIM_WriteStatusRegister(dataBuf, sizeof (dataBuf), 1U);
        spim_wait_write_done(1UL);
    }

	ret = 0;

    return ret;
}

/**
  * @brief      Issue JEDEC ID command.
  * @param      idBuf       ID buffer.
  * @param      u32NRx      Size of ID buffer.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     None.
  */
void SPIM_ReadJedecId(uint8_t idBuf[], uint32_t u32NRx, uint32_t u32NBit)
{
    uint8_t cmdBuf[] = { OPCODE_RDID };          /* 1-byte JEDEC ID command.  */

    SPIM_SET_SS_EN(1);                          /* CS activated.    */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SwitchNBitInput(u32NBit);
    spim_read(idBuf, u32NRx);
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */
}


/**
  * @brief      Set Quad Enable/disable.
  * @param      isEn        Enable/disable.
  * @param      u32NBit     N-bit transmit/receive.
  * @return     None.
  */
void SPIM_SetQuadEnable(int isEn, uint32_t u32NBit)
{
    uint8_t  idBuf[3];
    uint8_t  dataBuf[2];

    SPIM_ReadJedecId(idBuf, sizeof (idBuf), u32NBit);

    SPIM_DBGMSG("SPIM_SetQuadEnable - Flash ID is 0x%x\n", idBuf[0]);

    switch (idBuf[0])
    {
    case MFGID_WINBOND:                      /* Winbond SPI flash  */
        SPIM_ReadStatusRegister(&dataBuf[0], 1UL, u32NBit);
        SPIM_ReadStatusRegister2(&dataBuf[1], 1UL, u32NBit);
        SPIM_DBGMSG("Status Register: 0x%x - 0x%x\n", dataBuf[0], dataBuf[1]);
        if (isEn)
        {
            dataBuf[1] |= SR2_QE;
        }
        else
        {
            dataBuf[1] &= ~SR2_QE;
        }

        spim_set_write_enable(1, u32NBit);   /* Write Enable.    */
        SPIM_WriteStatusRegister2(dataBuf, sizeof (dataBuf), u32NBit);
        spim_wait_write_done(u32NBit);

        SPIM_ReadStatusRegister(&dataBuf[0], 1UL, u32NBit);
        SPIM_ReadStatusRegister2(&dataBuf[1], 1UL, u32NBit);
        SPIM_DBGMSG("Status Register: 0x%x - 0x%x\n", dataBuf[0], dataBuf[1]);
        break;

    default:
        break;
    }
}

/**
  * @brief      Erase whole chip.
  * @param      u32NBit     N-bit transmit/receive.
  * @param      isSync      Block or not.
  * @return     None.
  */
void SPIM_ChipErase(uint32_t u32NBit, int isSync)
{
    uint8_t cmdBuf[] = { OPCODE_CHIP_ERASE };    /* 1-byte Chip Erase command. */

    spim_set_write_enable(1, u32NBit);           /* Write Enable.    */

    SPIM_SET_SS_EN(1);                          /* CS activated.    */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, sizeof (cmdBuf));
    SPIM_SET_SS_EN(0);                          /* CS deactivated.  */

    if (isSync)
    {
        spim_wait_write_done(u32NBit);
    }
}

/**
  * @brief      Erase one block.
  * @param      u32Addr         Block to erase which contains the u32Addr.
  * @param      is4ByteAddr     4-byte u32Address or not.
  * @param      u8ErsCmd        Erase command.
  * @param      u32NBit         N-bit transmit/receive.
  * @param      isSync      Block or not.
  * @return     None.
  */
void SPIM_EraseBlock(uint32_t u32Addr, int is4ByteAddr, uint8_t u8ErsCmd, uint32_t u32NBit, int isSync)
{
    uint8_t  cmdBuf[16];
    uint32_t  buf_idx = 0UL;

    spim_set_write_enable(1, u32NBit);           /* Write Enable.    */

    cmdBuf[buf_idx++] = u8ErsCmd;

//    if (is4ByteAddr)
//    {
//        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 24);
//        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 16);
//        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 8);
//        cmdBuf[buf_idx++] = (uint8_t) (u32Addr & 0xFFUL);
//    }
//    else
//    {
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 16);
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr >> 8);
        cmdBuf[buf_idx++] = (uint8_t) (u32Addr & 0xFFUL);
//    }

    SPIM_SET_SS_EN(1);                      /* CS activated.    */
    SwitchNBitOutput(u32NBit);
    spim_write(cmdBuf, buf_idx);
    SPIM_SET_SS_EN(0);                      /* CS deactivated.  */

    if (isSync)
    {
        spim_wait_write_done(u32NBit);
    }
}


/** @cond HIDDEN_SYMBOLS */

/**
  * @brief      Write data in the same page by Page Write mode.
  * @param      u32Addr     Start u32Address to write.
  * @param      is4ByteAddr 4-byte u32Address or not.
  * @param      u32NTx      Number of bytes to write.
  * @param      pu8TxBuf    Transmit buffer.
  * @param      wrCmd       Write command.
  * @param      isSync      Block or not.
  * @return     None.
  */
static void SPIM_WriteInPageDataByPageWrite(uint32_t u32Addr, int is4ByteAddr, uint32_t u32NTx,
        uint8_t pu8TxBuf[], uint32_t wrCmd, int isSync)
{
//    if ((wrCmd == CMD_QUAD_PAGE_PROGRAM_WINBOND) ||
//            (wrCmd == CMD_QUAD_PAGE_PROGRAM_MXIC))
//    {
//        SPIM_SetQuadEnable(1, 1UL);              /* Set Quad Enable. */
//    }

    SPIM_SET_OPMODE(SPIM_CTL0_OPMODE_PAGEWRITE);/* Switch to Page Write mode.   */
    SPIM_SET_SPIM_MODE(wrCmd);                  /* SPIM mode.       */
//    SPIM_SET_4BYTE_ADDR_EN(is4ByteAddr);        /* Enable/disable 4-Byte Address.  */

    SPIM->SRAMADDR = (uint32_t) pu8TxBuf;        /* SRAM u32Address. */
    SPIM->DMACNT = u32NTx;                       /* Transfer length. */
    SPIM->FADDR = u32Addr;                       /* Flash u32Address.*/
    SPIM_SET_GO();                              /* Go.              */

    if (isSync)
    {
        SPIM_WAIT_FREE();
    }

}

/** @endcond HIDDEN_SYMBOLS */
/**
  * @brief      Write data to SPI Flash by Page Write mode.
  * @param      u32Addr     Start address to write.
  * @param      is4ByteAddr 4-byte address or not.
  * @param      u32NTx      Number of bytes to write.
  * @param      pu8TxBuf    Transmit buffer.
  * @param      wrCmd       Write command.
  * @return     None.
  */
void SPIM_DMA_Write(uint32_t u32Addr, int is4ByteAddr, uint32_t u32NTx, uint8_t pu8TxBuf[], uint32_t wrCmd)
{
    uint32_t   pageOffset, toWr;
    uint32_t   buf_idx = 0UL;

    pageOffset = u32Addr % 256UL;

    if ((pageOffset + u32NTx) <= 256UL)
    {
        /* Do all the bytes fit onto one page ? */
        SPIM_WriteInPageDataByPageWrite(u32Addr, is4ByteAddr, u32NTx, pu8TxBuf, wrCmd, 1);
    }
    else
    {
        toWr = 256UL - pageOffset;               /* Size of data remaining on the first page. */

        SPIM_WriteInPageDataByPageWrite(u32Addr, is4ByteAddr, toWr, &pu8TxBuf[buf_idx], wrCmd, 1);

        u32Addr += toWr;                         /* Advance indicator. */
        u32NTx -= toWr;
        buf_idx += toWr;

        while (u32NTx)
        {
            toWr = 256UL;
            if (toWr > u32NTx)
            {
                toWr = u32NTx;
            }

            SPIM_WriteInPageDataByPageWrite(u32Addr, is4ByteAddr, toWr, &pu8TxBuf[buf_idx], wrCmd, 1);

            u32Addr += toWr;                 /* Advance indicator. */
            u32NTx -= toWr;
            buf_idx += toWr;
        }
    }
}

/*@}*/ /* end of group SPIM_EXPORTED_FUNCTIONS */

/*@}*/ /* end of group SPIM_Driver */

/*@}*/ /* end of group Standard_Driver */

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
