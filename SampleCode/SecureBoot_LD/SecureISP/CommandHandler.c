/**************************************************************************//**
 * @file     CommandHandler.c
 * @version  V3.00
 * @brief    Secure ISP - Process commands
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#include <stdio.h>
#include <string.h>
#include "NuMicro.h"
#include "SecureISP.h"


/*--------------------------------------------------------------------------------------------------*/
/*  Status and Erroe Code Constant Definitions                                                      */
/*--------------------------------------------------------------------------------------------------*/
#define BL_ERR_TT_CHECK         0xF0F00000UL    /*!< Not a Non-secure parameter         */
#define BL_ERR_PARAMETER        0xF0F00001UL    /*!< Invalid parameter                  */
#define BL_PARAM_ALIGN          0xF0F00002UL    /*!< Parameter alignment error          */
#define BL_NOT_FLASH_ADDR       0xF0F00003UL    /*!< Invalid flash address              */
#define BL_NOT_SRAM_ADDR        0xF0F00004UL    /*!< Invalid sram address               */
#define BL_XOM_NOT_CONFIG       0xF0F00005UL    /*!< XOM is not configure yet           */
#define BL_XOM_HAS_CONFIG       0xF0F00006UL    /*!< XOM has beeen configured           */
#define BL_XOM_HAS_ACTIVE       0xF0F00007UL    /*!< XOM is actived                     */
#define BL_XOM_BASE_ERROR       0xF0F00008UL    /*!< Invalid XOM base address           */
#define BL_KPROM_NOT_ENABLE     0xF0F00009UL    /*!< KPROM is not enabled yet           */
#define BL_KPROM_KEY_FORBID     0xF0F0000AUL    /*!< KPROM comparison is forbidden      */
#define BL_KPROM_KEY_UNMATCH    0xF0F0000BUL    /*!< KPROM comparison is unmatched      */
#define BL_KPROM_KEY_LOCKED     0xF0F0000CUL    /*!< KPROM write-protect is enabled     */
#define BL_KPROM_SET_FAIL       0xF0F0000EUL    /*!< Set KPROM key fail                 */
#define BL_ISP_CMD_FAIL         (-1)            /*!< FMC command fail                   */
#define BL_FLASH_ALLONE         0xA11FFFFFUL    /*!< Check-all-one result is all one    */
#define BL_FLASH_NOT_ALLONE     0xA1100000UL    /*!< Check-all-one result is not all one*/

#ifdef ENBALE_DEBUG
struct sisp_cmd
{
    uint32_t    code;
    char        cmd_str[24];
};

static const struct sisp_cmd  _sisp_cmd_list[] =
{
    { CMD_CONNECT,            "CMD_CONNECT" },
    { CMD_RESET,              "CMD_RESET" },
    { CMD_READ_CONFIG,        "CMD_READ_CONFIG" },
    { CMD_WRITE,              "CMD_WRITE" },
    { CMD_ERASE,              "CMD_ERASE" },
    { CMD_GET_PID,            "CMD_GET_PID" },
    { CMD_GET_ID,             "CMD_GET_ID" },
    { CMD_DH_KEY,             "CMD_DH_KEY" },
    { CMD_AUTH_KEY,           "CMD_AUTH_KEY" },
    { CMD_AUTH_KPROM,         "CMD_AUTH_KPROM" },
    { CMD_CAL_ID_SIGNATURE,   "CMD_CAL_ID_SIGNATURE" },
    { CMD_GET_ID_SIGNATURE,   "CMD_GET_ID_SIGNATURE" },
    { CMD_READ_OTP,           "CMD_READ_OTP" },
    { CMD_XOM_ERASE,          "CMD_XOM_ERASE" },
    { CMD_XOM_SET,            "CMD_XOM_SET" },
    { CMD_SET_SBK,            "CMD_SET_SBK" },
    { CMD_SET_REGION_LOCK,    "CMD_SET_REGION_LOCK" },
    { CMD_SET_KPROM,          "CMD_SET_KPROM" },
    { CMD_MASS_ERASE,         "CMD_MASS_ERASE" },
    { CMD_UPDATE_CFG,         "CMD_UPDATE_CFG" },
    { CMD_SET_NS,             "CMD_SET_NS" },
    { CMD_SET_IB_INFO,        "CMD_SET_IB_INFO" },
    { CMD_CAL_IB_INFO,        "CMD_CAL_IB_INFO" },
    { CMD_SPI_GET_INFO,       "CMD_SPI_GET_INFO" },
    { CMD_SPI_SET_CMD,        "CMD_SPI_SET_CMD" },
    { CMD_SPI_GET_STATUS,     "CMD_SPI_GET_STATUS" },
    { CMD_SPI_WRITE,          "CMD_SPI_WRITE" },
    { CMD_SPI_ERASE,          "CMD_SPI_ERASE" },
    { CMD_DISCONNECT,         "CMD_DISCONNECT" },
    { CMD_GET_VERSION,        "CMD_GET_VERSION" },
    { CMD_ECDH_PUB0,          "CMD_ECDH_PUB0" },
    { CMD_ECDH_PUB1,          "CMD_ECDH_PUB1" },
    { CMD_ECDH_GET_PUB0,      "CMD_ECDH_GET_PUB0" },
    { CMD_ECDH_GET_PUB1,      "CMD_ECDH_GET_PUB1" },
    { CMD_ECDH_RAND_PUB0,     "CMD_ECDH_RAND_PUB0" },
    { CMD_ECDH_RAND_PUB1,     "CMD_ECDH_RAND_PUB1" },
    { CMD_ECDH_GET_RAND_PUB0, "CMD_ECDH_GET_RAND_PUB0" },
    { CMD_ECDH_GET_RAND_PUB1, "CMD_ECDH_GET_RAND_PUB1" },
    { CMD_GET_RAND_IV,        "CMD_GET_RAND_IV" },
    { CMD_SET_RAND_IV,        "CMD_SET_RAND_IV" },
    { CMD_SET_MASS_WRITE,     "CMD_SET_MASS_WRITE" },
    { CMD_MASS_WRITE,         "CMD_MASS_WRITE" },
    { CMD_WRITE_OTP,          "CMD_WRITE_OTP" },
    { CMD_IDENTIFY_SERVER,    "CMD_IDENTIFY_SERVER" },
    { CMD_EXEC_VENDOR_FUNC,   "CMD_EXEC_VENDOR_FUNC" },
    { CMD_ERASE_KPROM,        "CMD_ERASE_KPROM" },
    { CMD_KPROM_STS,          "CMD_KPROM_STS" },
    { CMD_RESYNC,             "CMD_RESYNC" },
    { CMD_IS_MASKED,          "CMD_IS_MASKED" },
};
void print_cmd(uint32_t code)
{
    int  i;
    for (i = 0; i < sizeof(_sisp_cmd_list)/sizeof(struct sisp_cmd); i++)
    {
        if (code == _sisp_cmd_list[i].code)
        {
            printf("[ISP COMMAND: %s]\n", _sisp_cmd_list[i].cmd_str);
            return;
        }
    }
    printf("[ISP COMMAND: Unknown!!]\n");
}
#else
void print_cmd(uint32_t code) { }
#endif


#define CMD_CONNECT                 0x80    /* ok */
#define CMD_RESET                   0x81    /* ok */
#define CMD_READ_CONFIG             0x82    /* ok */
#define CMD_WRITE                   0x83
#define CMD_ERASE                   0x84
#define CMD_GET_PID                 0x85    /* ok */
#define CMD_GET_ID                  0x85
#define CMD_DH_KEY                  0x86    /* ok */
#define CMD_AUTH_KEY                0x87
#define CMD_AUTH_KPROM              0x87
#define CMD_CAL_ID_SIGNATURE        0x88
#define CMD_GET_ID_SIGNATURE        0x89    /* 0:get R; 1:get S */
#define CMD_READ_OTP                0x8D

#define CMD_XOM_ERASE               0x90
#define CMD_XOM_SET                 0x91
#define CMD_SET_SBK                 0x96
#define CMD_SET_REGION_LOCK         0x97    /* 0:Secure region; 1:All region */
#define CMD_SET_KPROM               0x98    /* 0xA5: CFG not locked; 0xA4: CFG locked */
#define CMD_MASS_ERASE              0x99    /* */
#define CMD_UPDATE_CFG              0x9A    /* CBS, MBS, EraseCFG */
#define CMD_SET_NS                  0x9B    /* Only available if no SCRLOCK and ARLOCK */
#define CMD_SET_IB_INFO             0x9C    /* Only available if no SCRLOCK and ARLOCK */
#define CMD_CAL_IB_INFO             0x9D    /* Only available if no SCRLOCK and ARLOCK */

#define CMD_SPI_GET_INFO            0x88
#define CMD_SPI_SET_CMD             0x89
#define CMD_SPI_GET_STATUS          0x8A
#define CMD_SPI_WRITE               0x8B
#define CMD_SPI_ERASE               0x8C

#define CMD_DISCONNECT              0x8E
#define CMD_GET_VERSION             0x8F    /* ok */

#define CMD_ECDH_PUB0               0x8600
#define CMD_ECDH_PUB1               0x8601
#define CMD_ECDH_GET_PUB0           0x8602
#define CMD_ECDH_GET_PUB1           0x8603
#define CMD_ECDH_RAND_PUB0          0x8604
#define CMD_ECDH_RAND_PUB1          0x8605
#define CMD_ECDH_GET_RAND_PUB0      0x8606
#define CMD_ECDH_GET_RAND_PUB1      0x8607
#define CMD_GET_RAND_IV             0x8608
#define CMD_SET_RAND_IV             0x8609
#define CMD_SET_MASS_WRITE          0x8300
#define CMD_MASS_WRITE              0x8301
#define CMD_WRITE_OTP               0x8D00
#define CMD_IDENTIFY_SERVER         0x8700 //?
#define CMD_EXEC_VENDOR_FUNC        0x8FF0
#define CMD_ERASE_KPROM             0x9801
#define CMD_KPROM_STS               0x9802
#define CMD_RESYNC                  0x8000
#define CMD_IS_MASKED               0x8888


uint32_t CheckKPROMStatus(void)
{
    if((FMC->KPKEYSTS & FMC_KPKEYSTS_KEYLOCK_Msk) == FMC_KPKEYSTS_KEYLOCK_Msk)
        return ERR_KPROM_IS_LOCKED;

    if((FMC->KPKEYSTS & FMC_KPKEYSTS_KEYFLAG_Msk) == FMC_KPKEYSTS_KEYFLAG_Msk)
    {
        /* KPROM has enabled */
        if((FMC->KPKEYSTS & FMC_KPKEYSTS_KEYMATCH_Msk) == FMC_KPKEYSTS_KEYMATCH_Msk)
        {
            /* User can access all region if KPROM keys matched */
            return STS_KPROM_MATCH;
        }
        else
        {
            return ERR_AUTH_KEY;   /* status */
        }
    }
    else
    {
        return STS_NO_KPROM; /* Without KPROM function */
    }
}

/*
    * CCITT (0xFFFF)
    * mode: 0: calculate; 1: verify
*/
static int cmd_ExecCCITT(uint32_t *pu32buf, uint16_t len, uint8_t mode)
{
    volatile uint16_t   i;
    uint16_t            *pu16buf, OrgSum, CalSum;

    if(len > 56) // valid data byte count
        return -1;

    pu16buf = (uint16_t *)pu32buf;

    CLK->AHBCLK |= CLK_AHBCLK_CRCCKEN_Msk;
    CRC->SEED = 0xFFFFul;
    CRC->CTL = (CRC_CCITT | CRC_CPU_WDATA_16) | CRC_CTL_CRCEN_Msk;
    CRC->CTL |= CRC_CTL_CHKSINIT_Msk;

    for(i = 1; i < (len / 2); i++)
    {
#if (0)
        ISP_DBGMSG("idx-%d: 0x%04x. (CCITT)\n", i, *(pu16buf + i));
#endif
        CRC->DAT = *(pu16buf + i);
    }

    OrgSum = *(pu16buf + 0);
    CalSum = (CRC->CHECKSUM & 0xFFFFul);

    /* Clear CRC checksum */
    CRC->SEED = 0xFFFFul;
    CRC->CTL |= CRC_CTL_CHKSINIT_Msk;

    if(mode == 0)
    {
        *(pu16buf + 0) = CalSum;
        return CalSum;
    }
    else if(mode == 1)
    {
        /* Verify CCITT checksum */
        if(OrgSum == CalSum)
            return 0;   /* Verify CCITT Pass */
        else
            return -1;  /* Verify CCITT Fail */
    }
    else
    {
        return -1;
    }
}

/*
    * CRC32
    * mode: 0: calculate; 1: verify
*/
static int cmd_ExecCRC32(uint32_t *pu32buf, uint16_t len, uint8_t mode)
{
    volatile uint16_t   i;
    uint32_t            OrgSum, CalSum;

    if(len > 60) // valid data byte count
        return -1;

    CLK->AHBCLK |= CLK_AHBCLK_CRCCKEN_Msk;
    CRC->SEED = 0xFFFFFFFFul;
    CRC->CTL = (CRC_32 | CRC_CPU_WDATA_32 | CRC_WDATA_RVS | CRC_CHECKSUM_COM | CRC_CHECKSUM_RVS) | CRC_CTL_CRCEN_Msk;
    CRC->CTL |= CRC_CTL_CHKSINIT_Msk;

    for(i = 0; i < (len / 4) - 1; i++)
    {
#if (0)
        ISP_DBGMSG("idx-%d: 0x%08x. (CRC32)\n", i, *(pu32buf + i));
#endif
        CRC->DAT = *(pu32buf + i);
    }

    OrgSum = *(pu32buf + i);
    CalSum = (CRC->CHECKSUM & 0xFFFFFFFFul);

    /* Clear CRC checksum */
    CRC->SEED = 0xFFFFFFFFul;
    CRC->CTL |= CRC_CTL_CHKSINIT_Msk;

    if(mode == 0)
    {
        *(pu32buf + i) = CalSum;
        return CalSum;
    }
    else if(mode == 1)
    {
        /* Verify CRC32 checksum */
        if(OrgSum == CalSum)
            return 0;   /* Verify CRC32 Pass */
        else
            return -1;  /* Verify CRC32 Fail */
    }
    else
    {
        return -1;
    }
}

/**
  * @brief      Perform AES-256 CFB NoPadding encrypt
  */
int32_t cmd_AES256Encrypt(uint32_t *in, uint32_t *out, uint32_t len, uint32_t *KEY, uint32_t *IV)
{
    volatile int32_t    i;

    CLK->AHBCLK |= CLK_AHBCLK_CRPTCKEN_Msk;

    /* KEY and IV are byte order (32 bit) reversed, Swap32(x)) and stored in ISP_INFO_T */
    memcpy((void *)&CRPT->AES0_KEY[0], KEY, (4 * 8));
    memcpy((void *)&CRPT->AES0_IV[0], IV, (4 * 4));

    CRPT->AES0_SADDR = (uint32_t)in;
    CRPT->AES0_DADDR = (uint32_t)out;
    CRPT->AES0_CNT   = len;
    CRPT->AES_CTL = ((AES_KEY_SIZE_256 << CRPT_AES_CTL_KEYSZ_Pos) | (AES_IN_OUT_SWAP << CRPT_AES_CTL_OUTSWAP_Pos));
    CRPT->AES_CTL |= (CRPT_AES_CTL_ENCRPT_Msk);
    CRPT->AES_CTL |= ((AES_MODE_CFB << CRPT_AES_CTL_OPMODE_Pos) | CRPT_AES_CTL_START_Msk | CRPT_AES_CTL_DMAEN_Msk);
//    CRPT->AES_CTL |= ((AES_MODE_ECB << CRPT_AES_CTL_OPMODE_Pos) | CRPT_AES_CTL_START_Msk | CRPT_AES_CTL_DMAEN_Msk);
    while(CRPT->AES_STS & CRPT_AES_STS_BUSY_Msk) {}

    return 0;
}

/**
  * @brief      Perform AES-256 CFB NoPadding decrypt
  */
int32_t cmd_AES256Decrypt(uint32_t *in, uint32_t *out, uint32_t len, uint32_t *KEY, uint32_t *IV)
{
    volatile int32_t    i;

    CLK->AHBCLK |= CLK_AHBCLK_CRPTCKEN_Msk;

    CLK->AHBCLK |= CLK_AHBCLK_CRPTCKEN_Msk;

    /* KEY and IV are byte order (32 bit) reversed, Swap32(x)) and stored in ISP_INFO_T */
    memcpy((void *)&CRPT->AES0_KEY[0], KEY, (4 * 8));
    memcpy((void *)&CRPT->AES0_IV[0], IV, (4 * 4));

    CRPT->AES0_SADDR = (uint32_t)in;
    CRPT->AES0_DADDR = (uint32_t)out;
    CRPT->AES0_CNT   = len;
    CRPT->AES_CTL = ((AES_KEY_SIZE_256 << CRPT_AES_CTL_KEYSZ_Pos) | (AES_IN_OUT_SWAP << CRPT_AES_CTL_OUTSWAP_Pos));
    CRPT->AES_CTL |= ((AES_MODE_CFB << CRPT_AES_CTL_OPMODE_Pos) | CRPT_AES_CTL_START_Msk | CRPT_AES_CTL_DMAEN_Msk);
//    CRPT->AES_CTL |= ((AES_MODE_ECB << CRPT_AES_CTL_OPMODE_Pos) | CRPT_AES_CTL_START_Msk | CRPT_AES_CTL_DMAEN_Msk);
    while(CRPT->AES_STS & CRPT_AES_STS_BUSY_Msk) {}

    return 0;
}

int32_t cmd_GenRspPacket(CMD_PACKET_T *pCMD, ISP_INFO_T *pISPInfo)
{
    volatile int32_t    i;

#if (0)
    {
        uint32_t *pu32;
        pu32 = (uint32_t *)pCMD;
        ISP_DBGMSG("Raw RSP data:\n");
        for(i = 0; i < 2; i++)
            ISP_DBGMSG("   0x%08x", pu32[i]);
        for(i = 2; i < sizeof(CMD_PACKET_T) / 4; i++)
        {
            if((i % 4) == 2)
                ISP_DBGMSG("\n");
            ISP_DBGMSG("   0x%08x", pu32[i]);
        }
        ISP_DBGMSG("\n");
    }
#endif
    /* Generate CCITT */
    cmd_ExecCCITT((uint32_t *)pCMD, sizeof(CMD_PACKET_T) - 8, 0);

    for(i = 0; i < sizeof(pISPInfo->au32AESKey) / 4; i++)
    {
        if(pISPInfo->au32AESKey[i] != 0x0ul)
            break;
    }
    /* if i == 8, NO AES key, do not encrypt the cmd data */
    if(i == 8)
    {
        ISP_DBGMSG("\nDo not encrypt cmd data. \n");
    }
    else
    {
        cmd_AES256Encrypt((uint32_t *)pCMD->au32Data, (uint32_t *)pCMD->au32Data, sizeof(pCMD->au32Data),
                          (uint32_t *)pISPInfo->au32AESKey, (uint32_t *)pISPInfo->au32AESIV);
    }
#if (0)
    {
        uint32_t *pu32;
        pu32 = (uint32_t *)pCMD;
        ISP_DBGMSG("AES KEY:\n");
        for(i = 0; i < sizeof(pISPInfo->au32AESKey) / 4; i++)
            ISP_DBGMSG("   0x%08x", pISPInfo->au32AESKey[i]);
        ISP_DBGMSG("\nAES IV:\n");
        for(i = 0; i < sizeof(pISPInfo->au32AESIV) / 4; i++)
            ISP_DBGMSG("   0x%08x", pISPInfo->au32AESIV[i]);
        ISP_DBGMSG("\nRSP data(encryption?):\n");
        for(i = 0; i < 2; i++)
            ISP_DBGMSG("   0x%08x", pu32[i]);
        for(i = 2; i < sizeof(CMD_PACKET_T) / 4; i++)
        {
            if((i % 4) == 2)
                ISP_DBGMSG("\n");
            ISP_DBGMSG("   0x%08x", pu32[i]);
        }
        ISP_DBGMSG("\n");
    }
#endif

    /* Generate CRC32 */
    cmd_ExecCRC32((uint32_t *)pCMD, sizeof(CMD_PACKET_T) - 4, 0);

    return 0;
}

int32_t cmd_ParseReqPacket(CMD_PACKET_T *pCMD, ISP_INFO_T *pISPInfo)
{
    volatile int32_t    i;

#if (0)
    {
        uint32_t *pu32;
        pu32 = (uint32_t *)pCMD;
        ISP_DBGMSG("Raw REQ data:\n");
        for(i = 0; i < 2; i++)
            ISP_DBGMSG("   0x%08x", pu32[i]);
        for(i = 2; i < sizeof(CMD_PACKET_T) / 4; i++)
        {
            if((i % 4) == 2)
                ISP_DBGMSG("\n");
            ISP_DBGMSG("   0x%08x", pu32[i]);
        }
        ISP_DBGMSG("\n");
    }
#endif
    /* verify CRC32 */
    if(cmd_ExecCRC32((uint32_t *)pCMD, sizeof(CMD_PACKET_T) - 4, 1) != 0)
    {
        ISP_DBGMSG("\n\tPacket CRC32 mismatch!\n");
        return -1;
    }

    for(i = 0; i < sizeof(pISPInfo->au32AESKey) / 4; i++)
    {
        if(pISPInfo->au32AESKey[i] != 0x0ul)
            break;
    }
    /* if i == 8, NO AES key, do not decrypt the cmd data */
    if(i == 8)
    {
        ISP_DBGMSG("\nDo not decrypt cmd data. \n");
    }
    else
    {
        cmd_AES256Decrypt((uint32_t *)pCMD->au32Data, (uint32_t*)pCMD->au32Data, sizeof(pCMD->au32Data),
                          (uint32_t *)pISPInfo->au32AESKey, (uint32_t *)pISPInfo->au32AESIV);
    }
#if (0)
    {
        uint32_t *pu32;
        pu32 = (uint32_t *)pCMD;
        ISP_DBGMSG("AES KEY:\n");
        for(i = 0; i < sizeof(pISPInfo->au32AESKey) / 4; i++)
            ISP_DBGMSG("   0x%08x", pISPInfo->au32AESKey[i]);
        ISP_DBGMSG("\nAES IV:\n");
        for(i = 0; i < sizeof(pISPInfo->au32AESIV) / 4; i++)
            ISP_DBGMSG("   0x%08x", pISPInfo->au32AESIV[i]);
        ISP_DBGMSG("\nREQ data(decryption?):\n");
        for(i = 0; i < 2; i++)
            ISP_DBGMSG("   0x%08x", pu32[i]);
        for(i = 2; i < sizeof(CMD_PACKET_T) / 4; i++)
        {
            if((i % 4) == 2)
                ISP_DBGMSG("\n");
            ISP_DBGMSG("   0x%08x", pu32[i]);
        }
        ISP_DBGMSG("\n");
    }
#endif

    /* verify CCITT */
    if(cmd_ExecCCITT((uint32_t *)pCMD, sizeof(CMD_PACKET_T) - 8, 1) != 0)
    {
        ISP_DBGMSG("\n\tPacket CCITT mismatch!\n");
        return -1;
    }

    ISP_DBGMSG("Parse cmd PASS!\n\n");
    return 0;
}


/* stage 1. */
/* "CMD_RESYNC"     "CMD_CONNECT"   "CMD_DISCONNECT" */

int32_t ParseCONNECT(ISP_INFO_T *pISPInfo)
{
    volatile int32_t    i, ret = 0, cmd_case;
    CMD_PACKET_T        cmd;

    memset(&cmd,             0x0, sizeof(CMD_PACKET_T));
    memset((uint8_t *)pISPInfo->rspbuf, 0x0, sizeof(pISPInfo->rspbuf));

    memcpy(&cmd, (uint8_t *)pISPInfo->rcvbuf, sizeof(cmd));

    print_cmd(cmd.u16CmdID);

    do
    {
        /* plaint text cmd */
        if(cmd.u16CmdID == CMD_RESYNC)
        {
            cmd.au32Data[0] = STS_OK;
            cmd.u16Len      = (4 * 1);
            ret = cmd.u16CmdID;
            pISPInfo->IsConnectOK = 0;
            break;
        }

        if(cmd_ParseReqPacket(&cmd, pISPInfo) != 0)
        {
            ISP_DBGMSG("*** [Pasre error: 0x%x] ***\n", cmd.u16CmdID);
            memset((void *)cmd.au32Data, 0x0, sizeof(cmd.au32Data));

            cmd.au32Data[0] = ERR_CMD_CHECKSUM;
            cmd.u16Len      = (4 * 1);
            ret = -1;
            break;
        }
        else
        {
            cmd_case = cmd.u16CmdID;
            switch(cmd_case)
            {
            case CMD_DISCONNECT:
                ISP_DBGMSG("[CMD_DISCONNECT] (stage 1)\n");
                cmd.au32Data[0] = STS_OK;
                cmd.u16Len      = (4 * 1);
                ret = cmd.u16CmdID;
                pISPInfo->IsConnectOK = 0;
                break;

            case CMD_CONNECT:
                ISP_DBGMSG("[CMD_CONNECT] (stage 1)\n");
                for(i = 0; i < 4; i++)
                    pISPInfo->au32AESIV[i] = ISP_Swap32(cmd.au32Data[i]);
                for(i = 0; i < 4; i++)
                {
                    if(pISPInfo->au32AESIV[i] != 0)
                        break;
                }
                if(i == 4)
                {
                    /* NO AESIV. Client will generate a new random AES IV */
                    GenRandomIV(NULL, pISPInfo);
                }
                cmd.au32Data[0] = STS_OK;
                cmd.au32Data[1] = SYS->PDID;
                for(i = 0; i < 4; i++)
                    cmd.au32Data[2 + i] = ISP_Swap32(pISPInfo->au32AESIV[i]);
                cmd.au32Data[6] = 0;    // not used, pISPInfo->u32CmdMask;
                cmd.au32Data[7] = FMC->KPKEYSTS; /* KPKEYSTS: bit-4:KEYFLAG(1:enable/0:disable), bit-3:FORBID */
                cmd.au32Data[8] = (((FMC->KPKEYCNT&0xFFFF)<<16) | (FMC->KPCNT&0xFFFF));

                ISP_DBGMSG("PDID:  0x%08x.\n", cmd.au32Data[1]);
                for(i = 0; i < 4; i++)
                    ISP_DBGMSG("Target IV[%d]: 0x%08x.\n", i, pISPInfo->au32AESIV[i]);
                cmd.u16Len      = (4 * 9);
                ret = cmd.u16CmdID;
                pISPInfo->IsConnectOK = 1;
                break;

            default:
                ISP_DBGMSG("*** [Cmd error: 0x%x] ***\n", cmd.u16CmdID);
                cmd.au32Data[0] = ERR_CMD_INVALID;
                cmd.u16Len      = (4 * 1);
                ret = -1;
                break;
            }
        }
        if(ret == -1)
            pISPInfo->IsConnectOK = 0;
    }
    while(0);

    cmd_GenRspPacket(&cmd, pISPInfo);

    /* Prepare respone data done */
    memcpy((uint8_t *)pISPInfo->rspbuf, (uint8_t *)&cmd, sizeof(CMD_PACKET_T));

    ISP_DBGMSG("Repone.\n\n");
    return  ret;
}


int32_t IdentifyServer(uint32_t *pu32Buf)
{
    ECC_PUBKEY_T        *pubkey;
    uint32_t            pub_key0[8] = HOST_PUBLIC_KEY1;
    uint32_t            pub_key1[8] = HOST_PUBLIC_KEY2;

    if (pu32Buf == NULL)
        return -1;

    pubkey = (ECC_PUBKEY_T *)pu32Buf;

    if (memcmp(pubkey->au32Key0, pub_key0, sizeof(pub_key0)) != 0)
    {
        ISP_DBGMSG("\nIdentify Server public key 0 FAIL.\n");
        return -1;
    }

    if (memcmp(pubkey->au32Key1, pub_key1, sizeof(pub_key1)) != 0)
    {
        ISP_DBGMSG("\nIdentify Server public key 1 FAIL.\n");
        return -1;
    }

    ISP_DBGMSG("\nIdentify Server public key PASS.\n");
    return 1;
}

/* stage 2. */
/* "CMD_RESYNC"             "CMD_DISCONNECT" */
/* "CMD_ECDH_PUB0"          "CMD_ECDH_PUB1" */
/* "CMD_ECDH_GET_PUB0"      "CMD_ECDH_GET_PUB1" */
/* "CMD_ECDH_RAND_PUB0"     "CMD_ECDH_RAND_PUB1" */
/* "CMD_ECDH_GET_RAND_PUB0" "CMD_ECDH_GET_RAND_PUB1" */

int32_t ParseECDH(ISP_INFO_T *pISPInfo)
{
    volatile int32_t    i, ret = 0, cmd_case;
    CMD_PACKET_T        cmd;
    uint32_t            AESKey[8];
    ECC_PUBKEY_T        randpub;
    char                priv[ECC_KBUF_LEN];

    memset(&cmd,             0x0, sizeof(CMD_PACKET_T));
    memset((uint8_t *)pISPInfo->rspbuf, 0x0, sizeof(pISPInfo->rspbuf));
    memset(priv, 0, sizeof(priv));

    memcpy(&cmd, (uint8_t *)pISPInfo->rcvbuf, sizeof(cmd));

    print_cmd(cmd.u16CmdID);

    do
    {
        /* plaint text cmd */
        if(cmd.u16CmdID == CMD_RESYNC)
        {
            cmd.au32Data[0] = STS_OK;
            cmd.u16Len      = (4 * 1);
            ret = cmd.u16CmdID;
            pISPInfo->IsConnectOK = 0;
            break;
        }

        if(cmd_ParseReqPacket(&cmd, pISPInfo) != 0)
        {
            ISP_DBGMSG("*** [Pasre error: 0x%x] ***\n", cmd.u16CmdID);
            memset((void *)cmd.au32Data, 0x0, sizeof(cmd.au32Data));

            cmd.au32Data[0] = ERR_CMD_CHECKSUM;
            cmd.u16Len      = (4 * 1);
            ret = -1;
            break;
        }
        else
        {
            cmd_case = cmd.u16CmdID;
            switch(cmd_case)
            {
            case CMD_DISCONNECT:
                ISP_DBGMSG("[CMD_DISCONNECT] (stage 2)\n");
                memset((void *)cmd.au32Data, 0x0, sizeof(cmd.au32Data));

                cmd.au32Data[0] = STS_OK;
                cmd.u16Len      = (4 * 1);
                ret = cmd.u16CmdID;
                pISPInfo->IsConnectOK = 0;
                break;

            case CMD_ECDH_PUB0:
                /* Get Server public key 0 */
                memcpy((void *)pISPInfo->ServerPubKey.au32Key0, (void *)cmd.au32Data, cmd.u16Len);
                for(i = 0; i < 8; i++)
                    ISP_DBGMSG("Get pub0[%d]: 0x%08x.\n", i, pISPInfo->ServerPubKey.au32Key0[i]);

                cmd.au32Data[0] = STS_OK;
                cmd.u16Len      = (4 * 1);
                ret = cmd.u16CmdID;
                break;

            case CMD_ECDH_PUB1:
                /* Get Server public key 1 and generate ist ECDH AES key */
                memcpy((void *)pISPInfo->ServerPubKey.au32Key1, (void *)cmd.au32Data, cmd.u16Len);
                for(i = 0; i < 8; i++)
                    ISP_DBGMSG("Get pub1[%d]: 0x%08x.\n", i, pISPInfo->ServerPubKey.au32Key1[i]);

                /* Identify OTP Public key Hash */
                if(IdentifyServer((uint32_t *)&pISPInfo->ServerPubKey) < 0)
                {
                    cmd.au32Data[0] = ERR_AUTH_KEY;
                    cmd.u16Len      = (4 * 1);
                    ret = -1;
                    break;
                }

                /* Generate 1st ECDH AES key */
                if (GenECDHKey(MY_PRIVATE_KEY, &pISPInfo->ServerPubKey, AESKey) != 0)
                {
                    cmd.au32Data[0] = ERR_PARAMETER;
                    cmd.u16Len      = (4 * 1);
                    ret = -1;
                    break;
                }
                for(i = 0; i < 8; i++)
                    AESKey[i] = ISP_Swap32(AESKey[i]);

                cmd.au32Data[0] = STS_OK;
                cmd.u16Len      = (4 * 1);
                ret = cmd.u16CmdID;
                break;

            case CMD_ECDH_GET_PUB0: // MUST be encrypted
                /* Response encrypted Client public key 0 */
                cmd.au32Data[0] = STS_OK;
                memcpy((void *)&cmd.au32Data[1], (void *)pISPInfo->ClientPubKey.au32Key0, sizeof(pISPInfo->ClientPubKey.au32Key0));
                for(i = 0; i < 8; i++)
                    ISP_DBGMSG("Out pub0[%d]: 0x%08x.\n", i, cmd.au32Data[1 + i]);
                cmd.u16Len      = (4 * (1 + 8));
                ret = cmd.u16CmdID;
                break;

            case CMD_ECDH_GET_PUB1: // MUST be encrypted
                /* Response encrypted Client public key 1 */
                cmd.au32Data[0] = STS_OK;
                memcpy((void *)&cmd.au32Data[1], (void *)pISPInfo->ClientPubKey.au32Key1, sizeof(pISPInfo->ClientPubKey.au32Key1));
                for(i = 0; i < 8; i++)
                    ISP_DBGMSG("Out pub1[%d]: 0x%08x.\n", i, cmd.au32Data[1 + i]);
                cmd.u16Len      = (4 * (1 + 8));
                ret = cmd.u16CmdID;
                break;

            case CMD_ECDH_RAND_PUB0: // MUST be encrypted
                /* Get Server random public key 0 */
                memcpy((void *)pISPInfo->ServerPubKey.au32Key0, (void *)cmd.au32Data, cmd.u16Len);
                for(i = 0; i < 8; i++)
                    ISP_DBGMSG("Get rand_pub0[%d]: 0x%08x.\n", i, pISPInfo->ServerPubKey.au32Key0[i]);

                cmd.au32Data[0] = STS_OK;
                cmd.u16Len      = (4 * 1);
                ret = cmd.u16CmdID;
                break;

            case CMD_ECDH_RAND_PUB1: // MUST be encrypted
                /* Get Server random public key 1 */
                memcpy((void *)pISPInfo->ServerPubKey.au32Key1, (void *)cmd.au32Data, cmd.u16Len);
                for(i = 0; i < 8; i++)
                    ISP_DBGMSG("Get rand_pub1[%d]: 0x%08x.\n", i, pISPInfo->ServerPubKey.au32Key1[i]);

                cmd.au32Data[0] = STS_OK;
                cmd.u16Len      = (4 * 1);
                ret = cmd.u16CmdID;
                break;

            case CMD_ECDH_GET_RAND_PUB0: // MUST be encrypted
                /* Generate Client random ECC key pair */
                if (GenerateECCKeyPair(priv, &randpub) != 0)
                {
                    memset(priv, 0x0, sizeof(priv));
                    memset(&randpub, 0x0, sizeof(ECC_PUBKEY_T));
                    cmd.au32Data[0] = ERR_PARAMETER;
                    cmd.u16Len      = (4 * 1);
                    ret = -1;
                    break;
                }

                /* Generate 2nd ECDH AES key and update in CMD_ECDH_RSP_RAND_PUB1 cmd */
                if (GenECDHKey(priv, &pISPInfo->ServerPubKey, AESKey) != 0)
                {
                    cmd.au32Data[0] = ERR_PARAMETER;
                    cmd.u16Len      = (4 * 1);
                    ret = -1;
                    break;
                }
                for(i = 0; i < 8; i++)
                    AESKey[i] = ISP_Swap32(AESKey[i]);
                memcpy(pISPInfo->tmp0, AESKey, sizeof(AESKey));

                memcpy(pISPInfo->ClientPubKey.au32Key0, randpub.au32Key0, sizeof(randpub.au32Key0));
                memcpy(pISPInfo->ClientPubKey.au32Key1, randpub.au32Key1, sizeof(randpub.au32Key1));
                memset(priv, 0x0, sizeof(priv));
                memset(&randpub, 0x0, sizeof(ECC_PUBKEY_T));

                /* Response encrypted Client random public key 0 */
                cmd.au32Data[0] = STS_OK;
                memcpy((void *)&cmd.au32Data[1], (void *)pISPInfo->ClientPubKey.au32Key0, sizeof(pISPInfo->ClientPubKey.au32Key0));
                for(i = 0; i < 8; i++)
                    ISP_DBGMSG("Out rand_pub0[%d]: 0x%08x.\n", i, cmd.au32Data[1 + i]);
                cmd.u16Len      = (4 * (1 + 8));
                ret = cmd.u16CmdID;
                break;

            case CMD_ECDH_GET_RAND_PUB1: // MUST be encrypted
                /* Response encrypted Client random public key 1 */
                cmd.au32Data[0] = STS_OK;
                memcpy((void *)&cmd.au32Data[1], (void *)pISPInfo->ClientPubKey.au32Key1, sizeof(pISPInfo->ClientPubKey.au32Key1));
                for(i = 0; i < 8; i++)
                    ISP_DBGMSG("Out rand_pub1[%d]: 0x%08x.\n", i, cmd.au32Data[1 + i]);
                cmd.u16Len      = (4 * (1 + 8));
                ret = cmd.u16CmdID;
                break;

            default:
                ISP_DBGMSG("*** [Cmd error: 0x%x] ***\n", cmd.u16CmdID);
                cmd.au32Data[0] = ERR_CMD_INVALID;
                cmd.u16Len      = (4 * 1);
                ret = -1;
                break;
            }
        }
        if(ret == -1)
            pISPInfo->IsConnectOK = 0;
    }
    while(0);

    cmd_GenRspPacket(&cmd, pISPInfo);

    memcpy((uint8_t *)pISPInfo->rspbuf, (uint8_t *)&cmd, sizeof(CMD_PACKET_T));

    if((ret == CMD_ECDH_PUB1) || (ret == CMD_ECDH_GET_RAND_PUB1))
    {
        if(ret == CMD_ECDH_PUB1)
        {
            /* Update 1st ECDH AES key to pISPInfo */
            memcpy(pISPInfo->au32AESKey, AESKey, sizeof(AESKey));
            for(i = 0; i < 8; i++)
                ISP_DBGMSG("Gen 1st KEY[%d]: 0x%08x.\n", i, pISPInfo->au32AESKey[i]);
        }
        else
        {
            /* Update 2nd ECDH AES key to pISPInfo */
            memcpy(pISPInfo->au32AESKey, pISPInfo->tmp0, sizeof(AESKey));
            for(i = 0; i < 8; i++)
                ISP_DBGMSG("Gen 2nd KEY[%d]: 0x%08x.\n", i, pISPInfo->au32AESKey[i]);
            memset(pISPInfo->tmp0, 0x0, sizeof(AESKey));
        }
    }
    memset(AESKey, 0x0, sizeof(AESKey));

    ISP_DBGMSG("Repone.\n\n");
    return ret;
}

static uint32_t FMC_ReadDID(void)
{
    FMC->ISPCMD = FMC_ISPCMD_READ_DID;          /* Set ISP Command Code */
    FMC->ISPADDR = 0x00u;
    FMC->ISPTRG = FMC_ISPTRG_ISPGO_Msk;         /* Trigger to start ISP procedure */
    while(FMC->ISPTRG & FMC_ISPTRG_ISPGO_Msk) {} /* Waiting for ISP Done */
    return FMC->ISPDAT;
}

static int32_t erase_flash_pages(uint32_t addr, uint32_t count)
{
    volatile int32_t    i, ret = ERR_ISP_ERASE;

    ISP_DBGMSG("[Page erase] addr: 0x%x, page counts: %d.\n", addr, count);

    if (addr % FMC_FLASH_PAGE_SIZE)
        return ERR_PAGE_ALIGN;

    if (!IsValidFlashRegion(addr, count * FMC_FLASH_PAGE_SIZE))
        return ERR_INVALID_ADDRESS;

    FMC_ENABLE_AP_UPDATE();
    FMC_ENABLE_LD_UPDATE();

    for (i = 0; i < count; i++, addr += FMC_FLASH_PAGE_SIZE)
    {
        if (FMC_Erase(addr) != 0)
        {
            ret = ERR_ISP_ERASE;
            break;
        }

        if (FMC_CheckAllOne(addr, FMC_FLASH_PAGE_SIZE) != READ_ALLONE_YES)
        {
            printf("Flash check-all-one verify failed on 0x%x!\n", addr);
            ret = ERR_ISP_ERASE;
            break;
        }
    }

    FMC_DISABLE_AP_UPDATE();
    FMC_DISABLE_LD_UPDATE();
    return ret;
}


static int32_t program_flash(uint32_t addr, uint32_t size, uint32_t *pu32Data)
{
    volatile int32_t    i, ret = 0;

    //ISP_DBGMSG("[Program flash] addr: 0x%x, size: %d, buff: 0x%x\n", addr, size, (int)pu32Data);

    if (!IsValidFlashRegion(addr, size))
        return ERR_INVALID_ADDRESS;

    FMC_ENABLE_AP_UPDATE();
    FMC_ENABLE_LD_UPDATE();

    for(i = 0; i < (size / 4); i++, addr+=4)
    {
        /* write */
        FMC_Write(addr, pu32Data[i]);

        /* verify */
        if (FMC_Read(addr) != pu32Data[i])
        {
            ret = ERR_ISP_WRITE;
            FMC_DISABLE_AP_UPDATE();
            FMC_DISABLE_LD_UPDATE();
            break;
        }
    }

    FMC_DISABLE_AP_UPDATE();
    FMC_DISABLE_LD_UPDATE();
    return ret;
}


static int32_t _UpdateCFG0(uint32_t cfg0)
{
    volatile int32_t    i, ret = 0;
    uint32_t   config[4];

    FMC_ENABLE_CFG_UPDATE();

    for (i = 0; i < 4; i ++)
        config[i] = FMC_Read(FMC_CONFIG_BASE + i*4);

    cfg0 |= (BIT29 | BIT25 | BIT24 | BIT14 | BIT8 | BIT9 | BIT2); /* Set reserved bits all 1 */

    config[0] = cfg0;

    FMC_Erase(FMC_CONFIG_BASE);

    FMC_Write(FMC_CONFIG_BASE+0x0, config[0]);
    FMC_Write(FMC_CONFIG_BASE+0x4, config[1]);
    FMC_Write(FMC_CONFIG_BASE+0x8, config[2]);
    FMC_Write(FMC_CONFIG_BASE+0xC, config[3]);

    for (i = 0; i < 4; i ++)
    {
        if (config[i] != FMC_Read(FMC_CONFIG_BASE + i*4))
        {
            ret = ERR_ISP_WRITE;
            ISP_DBGMSG("CONFIG%d verify error, read 0x%x, expect 0x%x!!\n", i, FMC_Read(FMC_CONFIG_BASE + i*4), config[i]);
        }
        else
            ISP_DBGMSG("New CONFIG%d: 0x%x\n", i, config[i]);
    }
    FMC_DISABLE_CFG_UPDATE();
    return ret;
}

static int32_t SetKPROM(uint32_t key[], uint32_t u32attr)
{
    volatile uint32_t   KPStatus, u32KeySts;
    volatile uint32_t   kpmax, kemax, lock_ctrl;

    KPStatus = CheckKPROMStatus();
    if((KPStatus == STS_NO_KPROM) || (KPStatus == STS_KPROM_MATCH))
    {
        ;
    }
    else
    {
        return BL_KPROM_KEY_LOCKED; /* ERR_KPROM_IS_LOCKED or ERR_AUTH_KEY */
    }

    kpmax  = ((u32attr >> 16) & 0x7);
    kemax  = ((u32attr >> 8) & 0x1F);
    lock_ctrl  = (u32attr & 0xFF);

    if((lock_ctrl == 0xA5) || (lock_ctrl == 0xA4))
    {
        ;
    }
    else
    {
        return BL_ERR_PARAMETER;
    }

    if (FMC_Erase(FMC_KPROM_BASE) < 0)
        return BL_ISP_CMD_FAIL;

    if (FMC_Erase(FMC_KPROM_BASE+0x200UL) < 0)
        return BL_ISP_CMD_FAIL;

    FMC_Write(FMC_KPROM_BASE + 0x0UL, key[0]);
    FMC_Write(FMC_KPROM_BASE + 0x4UL, key[1]);
    FMC_Write(FMC_KPROM_BASE + 0x8UL, key[2]);
    FMC_Write(FMC_KPROM_BASE + 0xCUL, kpmax);
    FMC_Write(FMC_KPROM_BASE + 0x10UL, kemax);
    FMC_Write(FMC_KPROM_BASE + 0x14UL, lock_ctrl);

    while(FMC->KPKEYSTS & FMC_KPKEYSTS_KEYBUSY_Msk) { };

    u32KeySts = FMC->KPKEYSTS;

    if((FMC->KPKEYSTS & FMC_KPKEYSTS_KEYLOCK_Msk) != FMC_KPKEYSTS_KEYLOCK_Msk)
    {
        return BL_KPROM_SET_FAIL;
    }
    else if((FMC->KPKEYSTS & FMC_KPKEYSTS_KEYFLAG_Msk) != FMC_KPKEYSTS_KEYFLAG_Msk)
    {
        return BL_KPROM_SET_FAIL;
    }
    else if(((FMC->KPCNT & FMC_KPCNT_KPMAX_Msk) >> FMC_KPCNT_KPMAX_Pos) != kpmax)
    {
        return BL_KPROM_SET_FAIL;
    }
    else if(((FMC->KPKEYCNT & FMC_KPKEYCNT_KPKEMAX_Msk) >> FMC_KPKEYCNT_KPKEMAX_Pos) != kemax)
    {
        return BL_KPROM_SET_FAIL;
    }
    else
    {
        if((lock_ctrl & BIT0) == 0)
        {
            if((u32KeySts & FMC_KPKEYSTS_CFGFLAG_Msk) != FMC_KPKEYSTS_CFGFLAG_Msk)
                return BL_KPROM_SET_FAIL;
        }
        else
        {
            if((u32KeySts & FMC_KPKEYSTS_CFGFLAG_Msk) != 0x0UL)
                return BL_KPROM_SET_FAIL;
        }
    }

    return 0;
}

static int32_t _PerformKPROM(uint32_t *data, uint32_t mode)
{
    int32_t   ret = 0;
    uint32_t  key[3], kpmax, kemax, lock, attr;

    ret = CheckKPROMStatus();

    key[0] = data[0];
    key[1] = data[1];
    key[2] = data[2];
    kpmax  = data[3];
    kemax  = data[4];
    lock   = data[5];
    attr   = ((kpmax & 0x7) << 16) | ((kemax & 0x1F) << 8) | (lock & 0xFF);
    /* Erase KPROM */
    if(mode == 0)
    {
        if(ret == STS_KPROM_MATCH)
        {
            if (FMC_Erase(FMC_KPROM_BASE) != 0)
                return ERR_ISP_ERASE;

            if (FMC_Erase(FMC_KPROM_BASE+FMC_FLASH_PAGE_SIZE) != 0)
                return ERR_ISP_ERASE;
            ret = 0;
        }
    }

    /* Set KPROM */
    if (mode == 1)
    {
        if(ret == STS_NO_KPROM)
        {
            ret = SetKPROM(key, attr);
            if(ret != 0)
                return ret;
            ret = 0;
        }
    }

    /* Trigger compare KPROM */
    if (mode == 2)
    {
        if (FMC_CompareSPKey(key) != 0)
            return ERR_AUTH_KEY;
        ret = 0;
    }

    return ret;
}


/* stage 3. */
/* "CMD_RESYNC"         "CMD_DISCONNECT" */
/* "CMD_GET_VERSION"    "CMD_RESET" */
/* "CMD_WRITE"          "CMD_ERASE" */
/* "CMD_SET_MASS_WRITE" "CMD_MASS_WRITE" */
/* "CMD_READ_CONFIG"    "CMD_UPDATE_CFG" */
/* "CMD_SET_REGION_LOCK" */
/* "CMD_XOM_SET"        "CMD_XOM_ERASE" */
/* "CMD_ERASE_KPROM"    "CMD_SET_KPROM"     "CMD_AUTH_KPROM"    "CMD_KPROM_STS" */
/* "CMD_GET_RAND_IV"    "CMD_SET_RAND_IV"   "CMD_GET_ID_SIGNATURE" */
/* "CMD_IDENTIFY_SERVER"    */
/* "CMD_MASS_ERASE"         */
/* "CMD_SET_NS */

int32_t ParseCommands(ISP_INFO_T *pISPInfo)
{
    volatile int32_t    i, ret = 0, cmd_case, tmp;
    CMD_PACKET_T        cmd;
    uint32_t            addr, size;
    uint32_t            msg[8], R[8], S[8];
    ECC_PUBKEY_T        PubKey;

    memset(&cmd,             0x0, sizeof(CMD_PACKET_T));
    memset((uint8_t *)pISPInfo->rspbuf, 0x0, sizeof(pISPInfo->rspbuf));
    memset(msg, 0x0, sizeof(msg));
    memset(R, 0x0, sizeof(R));
    memset(S, 0x0, sizeof(S));
    memset(&PubKey, 0x0, sizeof(ECC_PUBKEY_T));

    memcpy(&cmd, (uint8_t *)pISPInfo->rcvbuf, sizeof(cmd));

    print_cmd(cmd.u16CmdID);

    do
    {
        /* plaint text cmd */
        if(cmd.u16CmdID == CMD_RESYNC)
        {
            cmd.au32Data[0] = STS_OK;
            cmd.u16Len      = (4 * 1);
            ret = cmd.u16CmdID;
            pISPInfo->IsConnectOK = 0;
            break;
        }

        if(cmd_ParseReqPacket(&cmd, pISPInfo) != 0)
        {
            ISP_DBGMSG("*** [Parse error: 0x%x] ***\n", cmd.u16CmdID);
            memset((void *)cmd.au32Data, 0x0, sizeof(cmd.au32Data));

            cmd.au32Data[0] = ERR_CMD_CHECKSUM;
            cmd.u16Len      = (4 * 1);
            ret = -1;
            break;
        }
        else
        {
            cmd_case = cmd.u16CmdID;
            switch(cmd_case)
            {
            case CMD_DISCONNECT:
                ISP_DBGMSG("[CMD_DISCONNECT] (stage 3)\n");
                memset((void *)cmd.au32Data, 0x0, sizeof(cmd.au32Data));

                cmd.au32Data[0] = STS_OK;
                cmd.u16Len      = (4 * 1);
                ret = cmd.u16CmdID;
                pISPInfo->IsConnectOK = 0;
                break;

            case CMD_GET_VERSION:
                ISP_DBGMSG("[CMD_GET_VERSION]\n");
                memset((void *)cmd.au32Data, 0x0, sizeof(cmd.au32Data));

                cmd.au32Data[0] = STS_OK;
                cmd.au32Data[1] = FW_VERSION;
                cmd.u16Len      = (4 * 2);
                ret = cmd.u16CmdID;
                break;

            case CMD_ERASE:
                ISP_DBGMSG("[CMD_ERASE]\n");
                ret = erase_flash_pages(cmd.au32Data[0], cmd.au32Data[1]);
                cmd.au32Data[0] = (ret == 0) ? STS_OK : ret;
                cmd.u16Len      = (4 * 1);
//                    ret = (ret == 0) ? cmd.u16CmdID : -1;
                ret = cmd.u16CmdID;
                break;

            case CMD_WRITE:
                ISP_DBGMSG("[CMD_WRITE] (0x%x, 0x%x, 0x%x)\n", cmd.au32Data[0], cmd.au32Data[1], cmd.au32Data[2]);
                addr = cmd.au32Data[0];
                size = cmd.au32Data[1];
                ret = program_flash(addr, size, (void *)&cmd.au32Data[2]);
                cmd.au32Data[0] = (ret == 0) ? STS_OK : ret;
                cmd.u16Len      = (4 * 1);
                ret = (ret == 0) ? cmd.u16CmdID : -1;
                break;

            case CMD_SET_MASS_WRITE:
                ISP_DBGMSG("[CMD_SET_MASS_WRITE] (0x%x, 0x%x)\n", cmd.au32Data[0], cmd.au32Data[1]);
                ret = IsValidFlashRegion(cmd.au32Data[0], cmd.au32Data[1]);
                if(ret == 0)
                {
                    pISPInfo->tmp0[0] = cmd.au32Data[0]; // store write address
                    pISPInfo->tmp0[1] = cmd.au32Data[1]; // store write data length
                    FMC_DISABLE_AP_UPDATE();
                    FMC_DISABLE_LD_UPDATE();
                }
                cmd.au32Data[0] = (ret == 0) ? STS_OK : ret;
                cmd.u16Len      = (4 * 1);
//                    ret = (ret == 0) ? cmd.u16CmdID : -1;
                ret = cmd.u16CmdID;
                break;

            case CMD_MASS_WRITE:
                ISP_DBGMSG("[CMD_MASS_WRITE]\n");
                addr = pISPInfo->tmp0[0] + (cmd.u16PacketID * 48); // maximum data length is 48
                size = cmd.u16Len;
                ret = program_flash(addr, size, (uint32_t *)cmd.au32Data);
                cmd.au32Data[0] = (ret == 0) ? STS_OK : ret;
                cmd.u16Len      = (4 * 1);
                ret = (ret == 0) ? cmd.u16CmdID : -1;
                break;

            case CMD_GET_ID:
                ISP_DBGMSG("[CMD_GET_ID]\n");
                memset((void *)cmd.au32Data, 0x0, sizeof(cmd.au32Data));

                cmd.au32Data[0] = STS_OK;
                cmd.au32Data[1] = SYS->PDID;
                cmd.au32Data[2] = FMC_ReadUID(0);
                cmd.au32Data[3] = FMC_ReadUID(1);
                cmd.au32Data[4] = FMC_ReadUID(2);
                cmd.au32Data[5] = FMC_ReadUCID(0);
                cmd.au32Data[6] = FMC_ReadUCID(1);
                cmd.au32Data[7] = FMC_ReadUCID(2);
                cmd.au32Data[8] = FMC_ReadUCID(3);
                cmd.au32Data[9] = FMC_ReadCID();
                cmd.au32Data[10] = FMC_ReadDID();
                cmd.u16Len      = (4 * 11);
                ret = cmd.u16CmdID;
                break;

            case CMD_READ_CONFIG:
                ISP_DBGMSG("[CMD_READ_CONFIG]\n");
                memset((void *)cmd.au32Data, 0x0, sizeof(cmd.au32Data));

                cmd.au32Data[0] = STS_OK;
                cmd.au32Data[1] = FMC_Read(FMC_CONFIG_BASE); // CFG0
                cmd.au32Data[2] = GetAPROMSize();
                cmd.au32Data[3] = 0x5A5A;
                cmd.au32Data[4] = GetAPROMSize();
                cmd.au32Data[5] = FMC->KPKEYSTS;
                cmd.au32Data[6] = FMC_Read(FMC_CONFIG_BASE + 0xC); // CFG3
                cmd.au32Data[7] = FMC->XOMSTS;
                cmd.au32Data[8] = FMC->XOMR0STS;
                cmd.au32Data[9] = FMC->XOMR1STS;
                cmd.au32Data[10] = FMC->XOMR2STS;
                cmd.au32Data[11] = FMC->XOMR3STS;
                cmd.u16Len      = (4 * 12);
                ret = cmd.u16CmdID;
                break;

            case CMD_UPDATE_CFG:
                ISP_DBGMSG("[CMD_UPDATE_CFG] (CFG0:0x%x, CFG3:0x%x)\n", cmd.au32Data[0], cmd.au32Data[3]);
                ret = _UpdateCFG0(cmd.au32Data[0]);
                if(ret != 0)
                    cmd.au32Data[0] = ret;
                else
                    cmd.au32Data[0] = STS_OK;
                cmd.u16Len      = (4 * 1);
                ret = cmd.u16CmdID;
                break;

            case CMD_RESET:
                ISP_DBGMSG("[CMD_RESET] (0x%x)\n", cmd.au32Data[0]);
                if(cmd.au32Data[0] > 2)
                {
                    cmd.au32Data[0] = ERR_PARAMETER;
                    cmd.u16Len      = (4 * 1);
                    ret = cmd.u16CmdID;
                    break;
                }
                if(cmd.au32Data[0] == 0)
                {
                    SYS->IPRST0 |= SYS_IPRST0_CHIPRST_Msk;
                }
                else if(cmd.au32Data[0] == 1)
                {
                    NVIC_SystemReset();
                }
                else if(cmd.au32Data[0] == 2)
                {
                    SYS->IPRST0 |= SYS_IPRST0_CPURST_Msk;
                }
                cmd.au32Data[0] = STS_OK;
                cmd.u16Len      = (4 * 1);
                ret = cmd.u16CmdID;
                break;

            case CMD_ERASE_KPROM:
            case CMD_SET_KPROM:
            case CMD_AUTH_KPROM:
                if(cmd_case == CMD_ERASE_KPROM)
                {
                    ISP_DBGMSG("[CMD_ERASE_KPROM] (0x%x)\n", cmd.au32Data[0]);
                    tmp = 0;
                }
                if(cmd_case == CMD_SET_KPROM)
                {
                    ISP_DBGMSG("[CMD_SET_KPROM] (0x%x)\n", cmd.au32Data[0]);
                    tmp = 1;
                }
                if(cmd_case == CMD_AUTH_KPROM)
                {
                    ISP_DBGMSG("[CMD_AUTH_KPROM] (0x%x)\n", cmd.au32Data[0]);
                    tmp = 2;
                }
                ret = _PerformKPROM((uint32_t *)cmd.au32Data, tmp);
                if(ret != 0)
                    cmd.au32Data[0] = ret;
                else
                    cmd.au32Data[0] = STS_OK;
                cmd.u16Len      = (4 * 1);
                ret = cmd.u16CmdID;
                break;

            case CMD_KPROM_STS:
                ISP_DBGMSG("[CMD_KPROM_STS]\n");
                cmd.au32Data[0] = STS_OK;
                cmd.au32Data[1] = FMC->KPKEYSTS;
                cmd.au32Data[2] = FMC->KPCNT;
                cmd.au32Data[3] = FMC->KPKEYCNT;
                cmd.u16Len      = (4 * 4);
                ret = cmd.u16CmdID;
                break;

            case CMD_GET_RAND_IV:
                ISP_DBGMSG("[CMD_GET_RAND_IV]\n");
                for(i = 0; i < 4; i++)
                    pISPInfo->tmp1[i] = pISPInfo->au32AESIV[i]; // store old AESIV
                GenRandomIV(NULL, pISPInfo);
                for(i = 0; i < 4; i++)
                {
                    pISPInfo->tmp0[i] = pISPInfo->au32AESIV[i]; // generate new AESIV
                    pISPInfo->au32AESIV[i] = pISPInfo->tmp1[i]; // restore old AESIV for response current cmd
                }
                cmd.au32Data[0] = STS_OK;
                for(i = 0; i < 4; i++)
                {
                    cmd.au32Data[1 + i] = ISP_Swap32(pISPInfo->tmp0[i]);
                    ISP_DBGMSG("Get Target IV[%d]: 0x%08x.\n", i, pISPInfo->tmp0[i]);
                }
                cmd.u16Len      = (4 * 5);
                ret = cmd.u16CmdID;
                break;

            case CMD_SET_RAND_IV:
                ISP_DBGMSG("[CMD_SET_RAND_IV]\n");
                for(i = 0; i < 4; i++)
                {
                    pISPInfo->tmp0[i] = ISP_Swap32(cmd.au32Data[i]); // set new AESIV
                    ISP_DBGMSG("Set Target IV[%d]: 0x%08x.\n", i, pISPInfo->tmp0[i]);
                }
                cmd.au32Data[0] = STS_OK;
                cmd.u16Len      = (4 * 1);
                ret = cmd.u16CmdID;
                break;

            case CMD_GET_ID_SIGNATURE:
                ISP_DBGMSG("[CMD_GET_ID_SIGNATURE] (0x%x)\n", cmd.au32Data[0]);
                if(cmd.au32Data[0] == 0)
                {
                    /* response R */
                    for(i = 0; i < 8; i++)
                        cmd.au32Data[1 + i] = pISPInfo->sign.au32R[i];;
                    for(i = 0; i < 8; i++)
                        ISP_DBGMSG("R[%d]: 0x%08x.\n", i, cmd.au32Data[1 + i]);
                }
                else
                {
                    /* response S */
                    for(i = 0; i < 8; i++)
                        cmd.au32Data[1 + i] = pISPInfo->sign.au32S[i];;
                    for(i = 0; i < 8; i++)
                        ISP_DBGMSG("S[%d]: 0x%08x.\n", i, cmd.au32Data[1 + i]);
                }
                cmd.au32Data[0] = STS_OK;
                cmd.u16Len      = (4 * 9);
                ret = cmd.u16CmdID;
                break;

            case CMD_IDENTIFY_SERVER:
                ISP_DBGMSG("[CMD_IDENTIFY_SERVER] (0x%x)\n", cmd.au32Data[0]);
                if(cmd.au32Data[0] != 0) // execute identify
                    memcpy(pISPInfo->tmp1, (void *)&cmd.au32Data[1], (ECC_BIT_LEN / 8)); // 256-bit
                else
                    memcpy(pISPInfo->tmp0, (void *)&cmd.au32Data[1], (ECC_BIT_LEN / 8)); // 256-bit
                memcpy(PubKey.au32Key0, pISPInfo->tmp0, (ECC_BIT_LEN / 8)); // 256-bit
                memcpy(PubKey.au32Key1, pISPInfo->tmp1, (ECC_BIT_LEN / 8)); // 256-bit
                if(cmd.au32Data[0] != 0)
                {
                    if(IdentifyServer((uint32_t *)&PubKey) < 0)
                    {
                        cmd.au32Data[0] = ERR_AUTH_KEY;
                        cmd.u16Len      = (4 * 1);
                        ret = cmd.u16CmdID;
                        break;
                    }
                }
                cmd.au32Data[0] = STS_OK;
                cmd.u16Len      = (4 * 1);
                ret = cmd.u16CmdID;
                break;

            case CMD_IS_MASKED:
                ISP_DBGMSG("[CMD_IS_MASKED] (0x%x)\n", cmd.u16CmdID);
                cmd.au32Data[0] = CMD_IS_MASKED;
                cmd.u16Len      = (4 * 1);
                ret = cmd.u16CmdID;
                break;

            default:
                ISP_DBGMSG("*** [Cmd error: 0x%x] (may not supported in this implement) ***\n", cmd.u16CmdID);
                cmd.au32Data[0] = ERR_CMD_INVALID;
                cmd.u16Len      = (4 * 1);
                ret = -1;
                break;
            }
        }
        if(ret == -1)
            pISPInfo->IsConnectOK = 0;
    }
    while(0);

    memset(msg, 0x0, sizeof(msg));
    memset(R, 0x0, sizeof(R));
    memset(S, 0x0, sizeof(S));
    memset(&PubKey, 0x0, sizeof(ECC_PUBKEY_T));

    cmd_GenRspPacket(&cmd, pISPInfo);

    memcpy((uint8_t *)pISPInfo->rspbuf, (uint8_t *)&cmd, sizeof(CMD_PACKET_T));

    if((ret == CMD_GET_RAND_IV) || (ret == CMD_SET_RAND_IV))
    {
        /* Update AESIV to pISPInfo */
        memcpy(pISPInfo->au32AESIV, pISPInfo->tmp0, (128 / 8)); // 128-bits
    }

    ISP_DBGMSG("Repone.\n\n");
    return ret;
}

/* stage 1. */
int32_t ProcessConnect(ISP_INFO_T *pISPInfo)
{
    volatile int32_t    ret = 0, timeout;
    volatile ISP_INFO_T *pCurISPInfo;

    pCurISPInfo = pISPInfo;

    timeout = pCurISPInfo->timeout;
    ISP_DBGMSG("Wait time-out counts: %d.\n\n", timeout);

    pCurISPInfo->IsConnectOK = 0;

    ISP_DBGMSG("\n[In ProcessConnect]\n\n");
    USBD->INTSTS = USBD_INTSTS_SOFIF_Msk;
    while(1)
    {
        /* Is USB event? */
        if(pCurISPInfo->IsUSBDataReady == TRUE)
        {
            timeout = -1;
            ISP_DBGMSG("IS USB_CMD:\n\n");
            ret = ParseCONNECT((ISP_INFO_T *)pCurISPInfo);
            EP2_Handler((uint8_t *)pCurISPInfo->rspbuf);
            pCurISPInfo->IsUSBDataReady = FALSE;
        }

        /* Is UART event? */
        if(pCurISPInfo->IsUARTDataReady == TRUE)
        {
            timeout = -1;
            ISP_DBGMSG("IS UART_CMD:\n\n");
            pCurISPInfo->IsUARTDataReady = FALSE;
            ret = ParseCONNECT((ISP_INFO_T *)pCurISPInfo);
            PutString((uint8_t *)pCurISPInfo->rspbuf);
        }

        if((ret == -1) || (ret == CMD_DISCONNECT) || (ret == CMD_CONNECT) || (ret == CMD_RESYNC))
            break;

        if(timeout != -1)
        {
            if(timeout-- == 0)
            {
                ISP_DBGMSG("[Connect time-out]\n\n");
                ret = -1;
                break;
            }
        }
    }
    return ret;
}

/* stage 2. */
int32_t ProcessECDH(ISP_INFO_T *pISPInfo)
{
    volatile int32_t    ret = 0;
    volatile ISP_INFO_T *pCurISPInfo;

    pCurISPInfo = pISPInfo;

    ISP_DBGMSG("\n[In ProcessECDH]\n\n");
    while(1)
    {
        /* Is USB event? */
        if(pCurISPInfo->IsUSBDataReady == TRUE)
        {
            ret = ParseECDH((ISP_INFO_T *)pCurISPInfo);
            EP2_Handler((uint8_t *)pCurISPInfo->rspbuf);
            pCurISPInfo->IsUSBDataReady = FALSE;
        }

        /* Is UART event? */
        if(pCurISPInfo->IsUARTDataReady == TRUE)
        {
            pCurISPInfo->IsUARTDataReady = FALSE;
            ret = ParseECDH((ISP_INFO_T *)pCurISPInfo);
            PutString((uint8_t *)pCurISPInfo->rspbuf);
        }

        if((ret == -1) || (ret == CMD_DISCONNECT) || (ret == CMD_ECDH_GET_RAND_PUB1) || (ret == CMD_RESYNC))
            break;
    }

    return ret;
}

/* stage 3. */
int32_t ProcessCommands(ISP_INFO_T *pISPInfo)
{
    volatile int32_t    ret = 0;
    volatile ISP_INFO_T *pCurISPInfo;

    pCurISPInfo = pISPInfo;

    ISP_DBGMSG("\n[In ProcessCommands]\n\n");
    while(1)
    {
        /* Is USB event? */
        if(pCurISPInfo->IsUSBDataReady == TRUE)
        {
            ret = ParseCommands((ISP_INFO_T *)pCurISPInfo);
            EP2_Handler((uint8_t *)pCurISPInfo->rspbuf);
            pCurISPInfo->IsUSBDataReady = FALSE;
        }

        /* Is UART event? */
        if(pCurISPInfo->IsUARTDataReady == TRUE)
        {
            pCurISPInfo->IsUARTDataReady = FALSE;
            ret = ParseCommands((ISP_INFO_T *)pCurISPInfo);
            PutString((uint8_t *)pCurISPInfo->rspbuf);
        }

        if((ret == -1) || (ret == CMD_DISCONNECT) || (ret == CMD_RESYNC))
            break;
    }

    return ret;
}

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
