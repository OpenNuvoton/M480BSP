/**************************************************************************//**
 * @file     SecureISP.h
 * @version  V3.00
 * @brief    SecureISP Library header file
 *
 * @copyright (C) 2017 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __SECURE_ISP_H__
#define __SECURE_ISP_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "CommandHandler.h"

//#define ENBALE_DEBUG

#ifdef ENBALE_DEBUG
  #define ISP_DBGMSG      printf
#else
  #define ISP_DBGMSG(...)
#endif


/*-------------------------------------------------------------*/
/* Define maximum packet size */
#define MAX_PKT_SIZE            64
/*-------------------------------------------------------------*/


typedef enum
{
    USB_MODE        = 0x1,
    UART_MODE       = 0x2,
    USB_UART_MODE   = 0x3,
    RESYNC_ISP      = 0x80,
} E_ISP_MODE;


#define ISP_ECC_CURVE           CURVE_P_256
#define ECC_BIT_LEN             256                      /* ECC key length in bits     */
#define ECC_KEY_LEN             (ECC_BIT_LEN/4)          /* ECC key length in nibbles  */
#define ECC_KBUF_LEN            (ECC_KEY_LEN+4)          /* ECC key buffer length      */

#define HOST_PRIVATE_KEY         "be34baa8d040a3b991f9075b56ba292f755b90e4b6dc10dad36715c33cfdac25"
		/* Host public key is
		    fa2737fb93488d19caef11ae7faf6b7f4bcd67b286e3fc54e8a65c2b74aeccb0
		    d4ccd6dae698208aa8c3a6f39e45510d03be09b2f124bfc067856c324f9b4d09
		 */
#define HOST_PUBLIC_KEY1         { 0xfb3727fa, 0x198d4893, 0xae11efca, 0x7f6baf7f, 0xb267cd4b, 0x54fce386, 0x2b5ca6e8, 0xb0ccae74 }
#define HOST_PUBLIC_KEY2         { 0xdad6ccd4, 0x8a2098e6, 0xf3a6c3a8, 0x0d51459e, 0xb209be03, 0xc0bf24f1, 0x326c8567, 0x094d9b4f }

#define MY_PRIVATE_KEY         "1fe33950c5f461124ae992c2bdfdf1c73b1615f571bd567e60d19aa1f48cdf42"
		/* My public key is
		    7c110c66dcfda807f6e69e45ddb3c74f69a1484d203e8dc5ada8e9a9dd7cb3c7
		    0df448986e51bde5d1576f99901f9c2c6a806a47fd907643a72b835597efc8c6
		 */
#define MY_PUBLIC_KEY1           { 0x660c117c, 0x07a8fddc, 0x459ee6f6, 0x4fc7b3dd, 0x4d48a169, 0xc58d3e20, 0xa9e9a8ad, 0xc7b37cdd }
#define MY_PUBLIC_KEY2           { 0x9848f40d, 0xe5bd516e, 0x996f57d1, 0x2c9c1f90, 0x476a806a, 0x437690fd, 0x55832ba7, 0xc6c8ef97 }

typedef struct
{
    uint32_t        au32Key0[8];    /* 256-bits */
    uint32_t        au32Key1[8];    /* 256-bits */
}  ECC_PUBKEY_T;

typedef struct
{
    uint32_t        au32R[8];   /* 256-bits */
    uint32_t        au32S[8];   /* 256-bits */
}  ECDSA_SIGN_T;


typedef int32_t (*ISPCallback)(uint32_t*, uint32_t);

typedef struct
{
    uint32_t        au32AESKey[8];
    uint32_t        au32AESIV[4];
    ECC_PUBKEY_T    ClientPubKey;       /* 64-bytes (256-bits + 256-bits) */
    ECC_PUBKEY_T    ServerPubKey;       /* 64-bytes (256-bits + 256-bits) */
    ECDSA_SIGN_T    sign;               /* 64-bytes (256-bits R + 256-bits S) */
    uint32_t        IsConnectOK;
    uint32_t        timeout;
    uint32_t        rcvbuf[MAX_PKT_SIZE/4];
    uint32_t        rspbuf[MAX_PKT_SIZE/4];
    uint32_t        IsUSBDataReady;
    uint32_t        UARTClockFreq;
    uint32_t        UARTDataIdx;
    uint32_t        IsUARTDataReady;
    ISPCallback     pfnVendorFunc;
    uint32_t        tmp0[8];
    uint32_t        tmp1[8];
}  ISP_INFO_T;


#ifdef __ICCARM__
typedef struct 
{
    __packed uint8_t             g_usbd_SetupPacket[8];          /*!< Setup packet buffer */
    __packed uint8_t             g_usbd_RemoteWakeupEn;          /*!< Remote wake up function enable flag */
    __packed uint8_t             g_usbd_u8ZeroFlag;
    __packed uint8_t             *g_usbd_CtrlInPointer;
    __packed uint8_t             *g_usbd_CtrlOutPointer;
    __packed uint32_t            g_usbd_CtrlInSize;
    __packed uint32_t            g_usbd_CtrlOutSize;
    __packed uint32_t            g_usbd_CtrlOutSizeLimit;
    __packed uint32_t            g_usbd_UsbAddr;
    __packed uint32_t            g_usbd_UsbConfig;
    __packed uint32_t            g_usbd_CtrlMaxPktSize;
    __packed uint32_t            g_usbd_UsbAltInterface;
    __packed S_USBD_INFO_T       *g_usbd_sInfo;                  /*!< A pointer for USB information structure */
    __packed VENDOR_REQ          g_usbd_pfnVendorRequest;        /*!< USB Vendor Request Functional Pointer */
    __packed CLASS_REQ           g_usbd_pfnClassRequest;         /*!< USB Class Request Functional Pointer */
    __packed SET_INTERFACE_REQ   g_usbd_pfnSetInterface;         /*!< USB Set Interface Functional Pointer */
    __packed SET_CONFIG_CB       g_usbd_pfnSetConfigCallback;    /*!< USB Set configuration callback function pointer */
    __packed uint32_t            g_u32EpStallLock;               /*!< Bit map flag to lock specified EP when SET_FEATURE */

}  USBD_INFO_T;
#else
typedef struct 
{
    uint8_t             g_usbd_SetupPacket[8];          /*!< Setup packet buffer */
    volatile uint8_t    g_usbd_RemoteWakeupEn;          /*!< Remote wake up function enable flag */
    volatile uint8_t    g_usbd_u8ZeroFlag;

    volatile uint8_t    *g_usbd_CtrlInPointer;
    volatile uint8_t    *g_usbd_CtrlOutPointer;
    volatile uint32_t   g_usbd_CtrlInSize;
    volatile uint32_t   g_usbd_CtrlOutSize;
    volatile uint32_t   g_usbd_CtrlOutSizeLimit;
    volatile uint32_t   g_usbd_UsbAddr;
    volatile uint32_t   g_usbd_UsbConfig;
    volatile uint32_t   g_usbd_CtrlMaxPktSize;
    volatile uint32_t   g_usbd_UsbAltInterface;

    S_USBD_INFO_T       *g_usbd_sInfo;                  /*!< A pointer for USB information structure */

    VENDOR_REQ          g_usbd_pfnVendorRequest;        /*!< USB Vendor Request Functional Pointer */
    CLASS_REQ           g_usbd_pfnClassRequest;         /*!< USB Class Request Functional Pointer */
    SET_INTERFACE_REQ   g_usbd_pfnSetInterface;         /*!< USB Set Interface Functional Pointer */
    SET_CONFIG_CB       g_usbd_pfnSetConfigCallback;    /*!< USB Set configuration callback function pointer */
    uint32_t            g_u32EpStallLock;               /*!< Bit map flag to lock specified EP when SET_FEATURE */

} __attribute__((packed)) USBD_INFO_T;
#endif


/* Maximum 64-bytes */
#ifdef __ICCARM__
typedef struct
{
    /* Word-0 */
    __packed uint16_t   u16CRC16;       /* CRC16 checksum of from u8CmdID to Word-13 */
    __packed uint16_t   u16CmdID;       /* Command ID */
    /* Word-1 */
    __packed uint16_t   u16PacketID;    /* Packet ID */
    __packed uint16_t   u16Len;         /* Valid data length in command data field */
    /* Word-2 ~ 13 */
    __packed uint32_t   au32Data[12];   /* Command data */
    /* Word-14 */
    __packed uint32_t   u32CRC32;       /* CRC32 from Word-0 to Word-13 for check cmd integrity */
    /* Word-15 */
    __packed uint32_t   RSVD;           /* Reserved */

}  CMD_PACKET_T;
#else
typedef struct
{
    /* Word-0 */
    uint16_t        u16CRC16;       /* CRC16 checksum of from u8CmdID to Word-13 */
    uint16_t        u16CmdID;       /* Command ID */

    /* Word-1 */
    uint16_t        u16PacketID;    /* Packet ID */
    uint16_t        u16Len;         /* Valid data length in command data field */

    /* Word-2 ~ 13 */
    uint32_t        au32Data[12];   /* Command data */

    /* Word-14 */
    uint32_t        u32CRC32;       /* CRC32 from Word-0 to Word-13 for check cmd integrity */

    /* Word-15 */
    uint32_t        RSVD;           /* Reserved */

} __attribute__((packed)) CMD_PACKET_T;
#endif

typedef enum
{
    SHA_ONESHOT     = 0,    /* One shop SHA encrypt */
    SHA_CONTI_START,        /* Start continuous SHA encrypt */
    SHA_CONTI_ING,          /* Continuous SHA encrypt of SHA_CONTI_START */
    SHA_CONTI_END,          /* Last SHA encrypt of SHA_CONTI_START */
} E_SHA_OP_MODE;

typedef enum
{
    SHA_SRC_SRAM    = 0,
    SHA_SRC_FLASH,
} E_SHA_SRC;


/* Function declaration */
int32_t SecureISPInit(ISP_INFO_T *pISPInfo, USBD_INFO_T *pUSBDInfo, E_ISP_MODE mode);
int32_t ProcessISP(ISP_INFO_T *pISPInfo);

extern volatile ISP_INFO_T    g_ISPInfo;
extern volatile USBD_INFO_T   g_USBDInfo;
extern volatile CMD_PACKET_T  g_Cmd;


extern void PutString(uint8_t *pu8Buf);
extern void NuBL_MemCopy(uint8_t dest[], uint8_t src[], uint32_t size);
extern uint32_t ISP_Swap32(uint32_t value);

extern int  IsValidFlashRegion(uint32_t addr, uint32_t size);
extern uint32_t GetAPROMSize(void);
extern void  TRNG_Init(void);
extern void  TRNG_GenKey(char *key, int key_len);
extern void  ISP_Hex2Reg(char input[], uint32_t volatile reg[]);

extern int32_t  cmd_AES256Decrypt(uint32_t *in, uint32_t *out, uint32_t len, uint32_t *KEY, uint32_t *IV);
extern int32_t  cmd_AES256Encrypt(uint32_t *in, uint32_t *out, uint32_t len, uint32_t *KEY, uint32_t *IV);
extern int32_t  CalculateSHA256(uint32_t start, uint32_t end, uint32_t digest[], E_SHA_OP_MODE mode, E_SHA_SRC src);
extern int32_t  IdentifyServer(uint32_t *pu32Buf);
extern int32_t  GenECDHKey(char *PrivKey, ECC_PUBKEY_T *PubKey, uint32_t *Key);
extern int32_t  GenerateECCKeyPair(char *priv, ECC_PUBKEY_T *pubkey);
extern void     ISP_BytesSwap(char *buf, int32_t len);
extern uint32_t CheckKPROMStatus(void);
extern void     ResetWDTCounter(void);
extern int32_t  ProcessConnect(ISP_INFO_T *pISPInfo);
extern int32_t  ProcessECDH(ISP_INFO_T *pISPInfo);
extern int32_t  ProcessCommands(ISP_INFO_T *pISPInfo);

extern int32_t GenRandomIV(char *msg, ISP_INFO_T *pISPInfo);
extern void MassEraseAndReset(uint32_t cfg0, uint32_t cfg3);
extern void EP2_Handler(uint8_t *pu8Buf);
extern void PutString(uint8_t *pu8Buf);


extern int32_t ProcessUSBDInterrupt(uint32_t *pInfo, uint32_t *pUSBDInfo);
extern int32_t ProcessUART1Interrupt(uint32_t *pInfo);

extern int32_t USBDOpen(const S_USBD_INFO_T *param, CLASS_REQ pfnClassReq, SET_INTERFACE_REQ pfnSetInterface, uint32_t *pUSBDInfo);
extern int32_t USBDStart(void);


#ifdef __cplusplus
}
#endif

#endif /* __SECURE_ISP_H__ */

/*** (C) COPYRIGHT 2017 Nuvoton Technology Corp. ***/
