#ifndef ISP_USER_H
#define ISP_USER_H

#include "NuMicro.h"

#define FW_VERSION                  (0x04800200UL)

//timtim
/***************************************/
/* CMD                                 */
/***************************************/
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


/***************************************/
/* Upgrade Error Status                */
/***************************************/
#define STS_OK                      0x00
#define STS_XOM_ERASE_DONE          0x01
#define STS_NO_KPROM                0x02
#define STS_KPROM_MATCH             0x03
#define ERR_CMD_CONNECT             0x7F
#define ERR_CMD_INVALID             0x7E
#define ERR_CMD_CHECKSUM            0x7D
#define ERR_ISP_CONFIG              0x7C
#define ERR_ISP_WRITE               0x7B
#define ERR_INVALID_ADDRESS         0x7A
#define ERR_OVER_RANGE              0x79
#define ERR_PAGE_ALIGN              0x78
#define ERR_ISP_ERASE               0x77
#define ERR_DH_KEY                  0x76
#define ERR_DH_ARGUMENT             0x75
#define ERR_AUTH_KEY                0x74
#define ERR_AUTH_KEY_OVER           0x73
#define ERR_CMD_KEY_EXCHANGE        0x72
#define ERR_CMD_IDENTIFY            0x71
#define ERR_SPI_INVALID_PAGESIZE    0x70
#define ERR_TIMEOUT                 0x6F
#define ERR_CFG_MATCHED             0x6E
#define ERR_XOM_PARAMETER           0x6D
#define ERR_XOM_IS_ACTIVE           0x6C
#define ERR_XOM_NOT_ACTIVE          0x6B
#define ERR_SBK_EXIST               0x67
#define ERR_SET_SBK_FAIL            0x66
#define ERR_SREGION_LOCK            0x65
#define ERR_ALLREGION_LOCK          0x64
#define ERR_NS_BOUNDARY_EXIST       0x63
#define ERR_KPROM_IS_LOCKED         0x5F
#define ERR_PROGRAM_KPROM_FAIL      0x5E
#define ERR_ENABLE_KPROM_FAIL       0x5D
#define ERR_KPROM_LOCK_CFG_FAIL     0x5C
#define ERR_KPROM_KPMAX_FAIL        0x5B
#define ERR_KPROM_KEMAX_FAIL        0x5A
#define ERR_KPROM_IS_ENABLED        0x59
#define ERR_IB_INFO_NOT_READY       0x58
#define ERR_CAL_IB_INFO_FAIL        0x57
#define ERR_CAL_ID_SIGNATURE        0x56
#define ERR_VERIFY_ID_SIGNATURE     0x55
#define ERR_SET_ID_SIGNATURE        0x54
#define ERR_CFG_IS_LOCKED           0x53

#define ERR_PARAMETER               0x53


extern int32_t g_u32APROMSize, g_u32SRAMSize;
extern uint32_t volatile IsCmdConnect, ExchangeOK, IsAuthOK;
extern volatile uint32_t g_BootState;

extern void PutString(uint8_t *pu8Buf);

extern int ParseCmd(unsigned char *buffer, uint32_t IsUSB);
extern int ParseKeyCmd(unsigned char *buff);
extern int ParseInfoCmd(unsigned char *buffer, uint32_t IsUSB);

extern void DelayMs(uint32_t ms);
extern void DelayUs(uint32_t us);

extern uint32_t ExchangeKey(void);
extern uint32_t ProcessInfoCommand(void);
extern uint32_t ProcessCommand(void);

extern uint32_t GetMaxAPROMSize(void);

#endif  // #ifndef ISP_USER_H
