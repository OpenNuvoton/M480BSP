/**************************************************************************//**
 * @file     crypto_reg.h
 * @version  V1.00
 * @brief    CRYPTO register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __CRYPTO_REG_H__
#define __CRYPTO_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup CRPT Cryptographic Accelerator(CRPT)
    Memory Mapped Structure for Cryptographic Accelerator
@{ */

typedef struct
{

    /**
@var CRPT_T::INTEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTEN
</font><br><p> <font size="2">
Offset: 0x00  Crypto Interrupt Enable Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>AESIEN</td><td><div style="word-wrap: break-word;"><b>AES Interrupt Enable Control
</b><br>
0 = AES interrupt Disabled.
<br>
1 = AES interrupt Enabled.
<br>
In DMA mode, an interrupt will be triggered when amount of data set in AES_DMA_CNT is fed into the AES engine.
<br>
In Non-DMA mode, an interrupt will be triggered when the AES engine finishes the operation.
<br>
</div></td></tr><tr><td>
[1]</td><td>AESEIEN</td><td><div style="word-wrap: break-word;"><b>AES Error Flag Enable Control
</b><br>
0 = AES error interrupt flag Disabled.
<br>
1 = AES error interrupt flag Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>TDESIEN</td><td><div style="word-wrap: break-word;"><b>TDES/DES Interrupt Enable Control
</b><br>
0 = TDES/DES interrupt Disabled.
<br>
1 = TDES/DES interrupt Enabled.
<br>
In DMA mode, an interrupt will be triggered when amount of data set in TDES_DMA_CNT is fed into the TDES engine.
<br>
In Non-DMA mode, an interrupt will be triggered when the TDES engine finishes the operation.
<br>
</div></td></tr><tr><td>
[9]</td><td>TDESEIEN</td><td><div style="word-wrap: break-word;"><b>TDES/DES Error Flag Enable Control
</b><br>
0 = TDES/DES error interrupt flag Disabled.
<br>
1 = TDES/DES error interrupt flag Enabled.
<br>
</div></td></tr><tr><td>
[16]</td><td>PRNGIEN</td><td><div style="word-wrap: break-word;"><b>PRNG Interrupt Enable Control
</b><br>
0 = PRNG interrupt Disabled.
<br>
1 = PRNG interrupt Enabled.
<br>
</div></td></tr><tr><td>
[22]</td><td>ECCIEN</td><td><div style="word-wrap: break-word;"><b>ECC Interrupt Enable Control
</b><br>
0 = ECC interrupt Disabled.
<br>
1 = ECC interrupt Enabled.
<br>
In DMA mode, an interrupt will be triggered when amount of data set in ECC_DMA_CNT is fed into the ECC engine.
<br>
In Non-DMA mode, an interrupt will be triggered when the ECC engine finishes the operation.
<br>
</div></td></tr><tr><td>
[23]</td><td>ECCEIEN</td><td><div style="word-wrap: break-word;"><b>ECC Error Interrupt Enable Control
</b><br>
0 = ECC error interrupt flag Disabled.
<br>
1 = ECC error interrupt flag Enabled.
<br>
</div></td></tr><tr><td>
[24]</td><td>HMACIEN</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Interrupt Enable Control
</b><br>
0 = SHA/HMAC interrupt Disabled.
<br>
1 = SHA/HMAC interrupt Enabled.
<br>
In DMA mode, an interrupt will be triggered when amount of data set in SHA _DMA_CNT is fed into the SHA/HMAC engine
<br>
In Non-DMA mode, an interrupt will be triggered when the SHA/HMAC engine finishes the operation.
<br>
</div></td></tr><tr><td>
[25]</td><td>HMACEIEN</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Error Interrupt Enable Control
</b><br>
0 = SHA/HMAC error interrupt flag Disabled.
<br>
1 = SHA/HMAC error interrupt flag Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::INTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTSTS
</font><br><p> <font size="2">
Offset: 0x04  Crypto Interrupt Flag
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>AESIF</td><td><div style="word-wrap: break-word;"><b>AES Finish Interrupt Flag
</b><br>
This bit is cleared by writing 1, and it has no effect by writing 0.
<br>
0 = No AES interrupt.
<br>
= AES encryption/decryption done interrupt.
<br>
</div></td></tr><tr><td>
[1]</td><td>AESEIF</td><td><div style="word-wrap: break-word;"><b>AES Error Flag
</b><br>
This bit is cleared by writing 1, and it has no effect by writing 0.
<br>
0 = No AES error.
<br>
1 = AES encryption/decryption done interrupt.
<br>
</div></td></tr><tr><td>
[8]</td><td>TDESIF</td><td><div style="word-wrap: break-word;"><b>TDES/DES Finish Interrupt Flag
</b><br>
This bit is cleared by writing 1, and it has no effect by writing 0.
<br>
0 = No TDES/DES interrupt.
<br>
1 = TDES/DES encryption/decryption done interrupt.
<br>
</div></td></tr><tr><td>
[9]</td><td>TDESEIF</td><td><div style="word-wrap: break-word;"><b>TDES/DES Error Flag
</b><br>
This bit includes the operating and setting error
<br>
The detailed flag is shown in the CRPT_TDES_STS register
<br>
This includes operating and setting error.
<br>
This bit is cleared by writing 1, and it has no effect by writing 0.
<br>
0 = No TDES/DES error.
<br>
1 = TDES/DES encryption/decryption error interrupt.
<br>
</div></td></tr><tr><td>
[16]</td><td>PRNGIF</td><td><div style="word-wrap: break-word;"><b>PRNG Finish Interrupt Flag
</b><br>
This bit is cleared by writing 1, and it has no effect by writing 0.
<br>
0 = No PRNG interrupt.
<br>
1 = PRNG key generation done interrupt.
<br>
</div></td></tr><tr><td>
[22]</td><td>ECCIF</td><td><div style="word-wrap: break-word;"><b>ECC Finish Interrupt Flag
</b><br>
This bit is cleared by writing 1, and it has no effect by writing 0.
<br>
0 = No ECC interrupt.
<br>
1 = ECC operation done interrupt.
<br>
</div></td></tr><tr><td>
[23]</td><td>ECCEIF</td><td><div style="word-wrap: break-word;"><b>ECC Error Flag
</b><br>
This register includes operating and setting error. The detail flag is shown in CRPT_ECC_STS register.
<br>
This bit is cleared by writing 1, and it has no effect by writing 0.
<br>
0 = No ECC error.
<br>
1 = ECC error interrupt.
<br>
</div></td></tr><tr><td>
[24]</td><td>HMACIF</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Finish Interrupt Flag
</b><br>
This bit is cleared by writing 1, and it has no effect by writing 0.
<br>
0 = No SHA/HMAC interrupt.
<br>
1 = SHA/HMAC operation done interrupt.
<br>
</div></td></tr><tr><td>
[25]</td><td>HMACEIF</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Error Flag
</b><br>
This register includes operating and setting error. The detail flag is shown in CRPT_HMAC_STS register.
<br>
This bit is cleared by writing 1, and it has no effect by writing 0.
<br>
0 = No SHA/HMAC error.
<br>
1 = SHA/HMAC error interrupt.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::PRNG_CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PRNG_CTL
</font><br><p> <font size="2">
Offset: 0x08  PRNG Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>START</td><td><div style="word-wrap: break-word;"><b>Start PRNG Engine
</b><br>
0 = Stop PRNG engine.
<br>
1 = Generate new key and store the new key to register CRPT_PRNG_KEYx , which will be cleared when the new key is generated.
<br>
</div></td></tr><tr><td>
[1]</td><td>SEEDRLD</td><td><div style="word-wrap: break-word;"><b>Reload New Seed for PRNG Engine
</b><br>
0 = Generating key based on the current seed.
<br>
1 = Reload new seed.
<br>
</div></td></tr><tr><td>
[3:2]</td><td>KEYSZ</td><td><div style="word-wrap: break-word;"><b>PRNG Generate Key Size
</b><br>
00 = 64 bits.
<br>
01 = 128 bits.
<br>
10 = 192 bits.
<br>
11 = 256 bits.
<br>
</div></td></tr><tr><td>
[8]</td><td>BUSY</td><td><div style="word-wrap: break-word;"><b>PRNG Busy (Read Only)
</b><br>
0 = PRNG engine is idle.
<br>
1 = Indicate that the PRNG engine is generating CRPT_PRNG_KEYx.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::PRNG_SEED

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PRNG_SEED
</font><br><p> <font size="2">
Offset: 0x0C  Seed for PRNG
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SEED</td><td><div style="word-wrap: break-word;"><b>Seed for PRNG (Write Only)
</b><br>
The bits store the seed for PRNG engine.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::PRNG_KEY[8]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PRNG_KEY[8]
</font><br><p> <font size="2">
Offset: 0x10 ~ 0x2C  PRNG Generated Key0 ~ Key7
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>Store PRNG Generated Key (Read Only)
</b><br>
The bits store the key that is generated by PRNG.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES_FDBCK[4]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES_FDBCK[4]
</font><br><p> <font size="2">
Offset: 0x50 ~ 0x5C  AES Engine Output Feedback Data after Cryptographic Operation
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>FDBCK</td><td><div style="word-wrap: break-word;"><b>AES Feedback Information
</b><br>
The feedback value is 128 bits in size.
<br>
The AES engine uses the data from CRPT_AES_FDBCKx as the data inputted to CRPT_AESn_IVx for the next block in DMA cascade mode.
<br>
The AES engine outputs feedback information for IV in the next block's operation
<br>
Software can use this feedback information to implement more than four DMA channels
<br>
Software can store that feedback value temporarily
<br>
After switching back, fill the stored feedback value to this register in the same channel operation, and then continue the operation with the original setting.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES_FDBCKH

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES_FDBCKH
</font><br><p> <font size="2">
Offset: 0x60  TDES/DES Engine Output Feedback High Word Data after Cryptographic Operation
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>FDBCK</td><td><div style="word-wrap: break-word;"><b>TDES/DES Feedback
</b><br>
The feedback value is 64 bits in size.
<br>
The TDES/DES engine uses the data from {CRPT_TDES_FDBCKH, CRPT_TDES_FDBCKL} as the data inputted to {CRPT_TDESn_IVH, CRPT_TDESn_IVL} for the next block in DMA cascade mode
<br>
The feedback register is for CBC, CFB, and OFB mode.
<br>
TDES/DES engine outputs feedback information for IV in the next block's operation
<br>
Software can use this feedback information to implement more than four DMA channels
<br>
Software can store that feedback value temporarily
<br>
After switching back, fill the stored feedback value to this register in the same channel operation
<br>
Then can continue the operation with the original setting.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES_FDBCKL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES_FDBCKL
</font><br><p> <font size="2">
Offset: 0x64  TDES/DES Engine Output Feedback Low Word Data after Cryptographic Operation
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>FDBCK</td><td><div style="word-wrap: break-word;"><b>TDES/DES Feedback
</b><br>
The feedback value is 64 bits in size.
<br>
The TDES/DES engine uses the data from {CRPT_TDES_FDBCKH, CRPT_TDES_FDBCKL} as the data inputted to {CRPT_TDESn_IVH, CRPT_TDESn_IVL} for the next block in DMA cascade mode
<br>
The feedback register is for CBC, CFB, and OFB mode.
<br>
TDES/DES engine outputs feedback information for IV in the next block's operation
<br>
Software can use this feedback information to implement more than four DMA channels
<br>
Software can store that feedback value temporarily
<br>
After switching back, fill the stored feedback value to this register in the same channel operation
<br>
Then can continue the operation with the original setting.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES_CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES_CTL
</font><br><p> <font size="2">
Offset: 0x100  AES Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>START</td><td><div style="word-wrap: break-word;"><b>AES Engine Start
</b><br>
0 = No effect.
<br>
1 = Start AES engine. BUSY flag will be set.
<br>
Note: This bit is always 0 when it's read back.
<br>
</div></td></tr><tr><td>
[1]</td><td>STOP</td><td><div style="word-wrap: break-word;"><b>AES Engine Stop
</b><br>
0 = No effect.
<br>
1 = Stop AES engine.
<br>
Note: This bit is always 0 when it's read back.
<br>
</div></td></tr><tr><td>
[3:2]</td><td>KEYSZ</td><td><div style="word-wrap: break-word;"><b>AES Key Size
</b><br>
This bit defines three different key size for AES operation.
<br>
2'b00 = 128 bits key.
<br>
2'b01 = 192 bits key.
<br>
2'b10 = 256 bits key.
<br>
2'b11 = Reserved.
<br>
If the AES accelerator is operating and the corresponding flag BUSY is 1, updating this register has no effect.
<br>
</div></td></tr><tr><td>
[5]</td><td>DMALAST</td><td><div style="word-wrap: break-word;"><b>AES Last Block
</b><br>
In DMA mode, this bit must be set as beginning the last DMA cascade round.
<br>
In Non-DMA mode, this bit must be set when feeding in the last block of data in ECB, CBC, CTR, OFB, and CFB mode, and feeding in the (last-1) block of data at CBC-CS1, CBC-CS2, and CBC-CS3 mode.
<br>
This bit is always 0 when it's read back. Must be written again once START is triggered.
<br>
</div></td></tr><tr><td>
[6]</td><td>DMACSCAD</td><td><div style="word-wrap: break-word;"><b>AES Engine DMA with Cascade Mode
</b><br>
0 = DMA cascade function Disabled.
<br>
1 = In DMA cascade mode, software can update DMA source address register, destination address register, and byte count register during a cascade operation, without finishing the accelerator operation.
<br>
</div></td></tr><tr><td>
[7]</td><td>DMAEN</td><td><div style="word-wrap: break-word;"><b>AES Engine DMA Enable Control
</b><br>
0 = AES DMA engine Disabled.
<br>
The AES engine operates in Non-DMA mode, and gets data from the port CRPT_AES_DATIN.
<br>
1 = AES_DMA engine Enabled.
<br>
The AES engine operates in DMA mode, and data movement from/to the engine is done by DMA logic.
<br>
</div></td></tr><tr><td>
[15:8]</td><td>OPMODE</td><td><div style="word-wrap: break-word;"><b>AES Engine Operation Modes
</b><br>
0x00 = ECB (Electronic Codebook Mode)  0x01 = CBC (Cipher Block Chaining Mode).
<br>
0x02 = CFB (Cipher Feedback Mode).
<br>
0x03 = OFB (Output Feedback Mode).
<br>
0x04 = CTR (Counter Mode).
<br>
0x10 = CBC-CS1 (CBC Ciphertext-Stealing 1 Mode).
<br>
0x11 = CBC-CS2 (CBC Ciphertext-Stealing 2 Mode).
<br>
0x12 = CBC-CS3 (CBC Ciphertext-Stealing 3 Mode).
<br>
</div></td></tr><tr><td>
[16]</td><td>ENCRPT</td><td><div style="word-wrap: break-word;"><b>AES Encryption/Decryption
</b><br>
0 = AES engine executes decryption operation.
<br>
1 = AES engine executes encryption operation.
<br>
</div></td></tr><tr><td>
[22]</td><td>OUTSWAP</td><td><div style="word-wrap: break-word;"><b>AES Engine Output Data Swap
</b><br>
0 = Keep the original order.
<br>
1 = The order that CPU outputs data from the accelerator will be changed from {byte3, byte2, byte1, byte0} to {byte0, byte1, byte2, byte3}.
<br>
</div></td></tr><tr><td>
[23]</td><td>INSWAP</td><td><div style="word-wrap: break-word;"><b>AES Engine Input Data Swap
</b><br>
0 = Keep the original order.
<br>
1 = The order that CPU feeds data to the accelerator will be changed from {byte3, byte2, byte1, byte0} to {byte0, byte1, byte2, byte3}.
<br>
</div></td></tr><tr><td>
[25:24]</td><td>CHANNEL</td><td><div style="word-wrap: break-word;"><b>AES Engine Working Channel
</b><br>
00 = Current control register setting is for channel 0.
<br>
01 = Current control register setting is for channel 1.
<br>
10 = Current control register setting is for channel 2.
<br>
11 = Current control register setting is for channel 3.
<br>
</div></td></tr><tr><td>
[30:26]</td><td>KEYUNPRT</td><td><div style="word-wrap: break-word;"><b>Unprotect Key
</b><br>
Writing 0 to CRPT_AES_CTL[31] and "10110" to CRPT_AES_CTL[30:26] is to unprotect the AES key.
<br>
The KEYUNPRT can be read and written
<br>
When it is written as the AES engine is operating, BUSY flag is 1, there would be no effect on KEYUNPRT.
<br>
</div></td></tr><tr><td>
[31]</td><td>KEYPRT</td><td><div style="word-wrap: break-word;"><b>Protect Key
</b><br>
Read as a flag to reflect KEYPRT.
<br>
0 = No effect.
<br>
1 = Protect the content of the AES key from reading
<br>
The return value for reading CRPT_AESn_KEYx is not the content of the registers CRPT_AESn_KEYx
<br>
Once it is set, it can be cleared by asserting KEYUNPRT
<br>
And the key content would be cleared as well.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES_STS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES_STS
</font><br><p> <font size="2">
Offset: 0x104  AES Engine Flag
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BUSY</td><td><div style="word-wrap: break-word;"><b>AES Engine Busy
</b><br>
0 = The AES engine is idle or finished.
<br>
1 = The AES engine is under processing.
<br>
</div></td></tr><tr><td>
[8]</td><td>INBUFEMPTY</td><td><div style="word-wrap: break-word;"><b>AES Input Buffer Empty
</b><br>
0 = There are some data in input buffer waiting for the AES engine to process.
<br>
1 = AES input buffer is empty
<br>
Software needs to feed data to the AES engine
<br>
Otherwise, the AES engine will be pending to wait for input data.
<br>
</div></td></tr><tr><td>
[9]</td><td>INBUFFULL</td><td><div style="word-wrap: break-word;"><b>AES Input Buffer Full Flag
</b><br>
0 = AES input buffer is not full. Software can feed the data into the AES engine.
<br>
1 = AES input buffer is full
<br>
Software cannot feed data to the AES engine
<br>
Otherwise, the flag INBUFERR will be set to 1.
<br>
</div></td></tr><tr><td>
[10]</td><td>INBUFERR</td><td><div style="word-wrap: break-word;"><b>AES Input Buffer Error Flag
</b><br>
0 = No error.
<br>
1 = Error happens during feeding data to the AES engine.
<br>
</div></td></tr><tr><td>
[12]</td><td>CNTERR</td><td><div style="word-wrap: break-word;"><b>CRPT_AESn_CNT Setting Error
</b><br>
0 = No error in CRPT_AESn_CNT setting.
<br>
1 = CRPT_AESn_CNT is not a multiply of 16 in ECB, CBC, CFB, OFB, and CTR mode.
<br>
</div></td></tr><tr><td>
[16]</td><td>OUTBUFEMPTY</td><td><div style="word-wrap: break-word;"><b>AES Out Buffer Empty
</b><br>
0 = AES output buffer is not empty. There are some valid data kept in output buffer.
<br>
1 = AES output buffer is empty
<br>
Software cannot get data from CRPT_AES_DATOUT
<br>
Otherwise, the flag OUTBUFERR will be set to 1 since the output buffer is empty.
<br>
</div></td></tr><tr><td>
[17]</td><td>OUTBUFFULL</td><td><div style="word-wrap: break-word;"><b>AES Out Buffer Full Flag
</b><br>
0 = AES output buffer is not full.
<br>
1 = AES output buffer is full, and software needs to get data from CRPT_AES_DATOUT
<br>
Otherwise, the AES engine will be pending since the output buffer is full.
<br>
</div></td></tr><tr><td>
[18]</td><td>OUTBUFERR</td><td><div style="word-wrap: break-word;"><b>AES Out Buffer Error Flag
</b><br>
0 = No error.
<br>
1 = Error happens during getting the result from AES engine.
<br>
</div></td></tr><tr><td>
[20]</td><td>BUSERR</td><td><div style="word-wrap: break-word;"><b>AES DMA Access Bus Error Flag
</b><br>
0 = No error.
<br>
1 = Bus error will stop DMA operation and AES engine.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES_DATIN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES_DATIN
</font><br><p> <font size="2">
Offset: 0x108  AES Engine Data Input Port Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DATIN</td><td><div style="word-wrap: break-word;"><b>AES Engine Input Port
</b><br>
CPU feeds data to AES engine through this port by checking CRPT_AES_STS. Feed data as INBUFFULL is 0.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES_DATOUT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES_DATOUT
</font><br><p> <font size="2">
Offset: 0x10C  AES Engine Data Output Port Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DATOUT</td><td><div style="word-wrap: break-word;"><b>AES Engine Output Port
</b><br>
CPU gets results from the AES engine through this port by checking CRPT_AES_STS
<br>
Get data as OUTBUFEMPTY is 0.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES0_KEY[8]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES0_KEY[8]
</font><br><p> <font size="2">
Offset: 0x110 ~ 0x12C  AES Key Word 0 ~ 7 Register for Channel 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>CRPT_AESn_KEYx
</b><br>
The KEY keeps the security key for AES operation.
<br>
n = 0, 1..3.
<br>
x = 0, 1..7.
<br>
The security key for AES accelerator can be 128, 192, or 256 bits and four, six, or eight 32-bit registers are to store each security key
<br>
{CRPT_AESn_KEY3, CRPT_AESn_KEY2, CRPT_AESn_KEY1, CRPT_AESn_KEY0} stores the 128-bit security key for AES operation
<br>
{CRPT_AESn_KEY5, CRPT_AESn_KEY4, CRPT_AESn_KEY3, CRPT_AESn_KEY2, CRPT_AESn_KEY1, CRPT_AESn_KEY0} stores the 192-bit security key for AES operation
<br>
{CRPT_AESn_KEY7, CRPT_AESn_KEY6, CRPT_AESn_KEY5, CRPT_AESn_KEY4, CRPT_AESn_KEY3, CRPT_AESn_KEY2, CRPT_AESn_KEY1, CRPT_AESn_KEY0} stores the 256-bit security key for AES operation.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES0_IV[4]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES0_IV[4]
</font><br><p> <font size="2">
Offset: 0x130 ~ 0x13C  AES Initial Vector Word 0 ~ 3 Register for Channel 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>IV</td><td><div style="word-wrap: break-word;"><b>AES Initial Vectors
</b><br>
n = 0, 1..3.
<br>
x = 0, 1..3.
<br>
Four initial vectors (CRPT_AESn_IV0, CRPT_AESn_IV1, CRPT_AESn_IV2, and CRPT_AESn_IV3) are for AES operating in CBC, CFB, and OFB mode
<br>
Four registers (CRPT_AESn_IV0, CRPT_AESn_IV1, CRPT_AESn_IV2, and CRPT_AESn_IV3) act as Nonce counter when the AES engine is operating in CTR mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES0_SADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES0_SADDR
</font><br><p> <font size="2">
Offset: 0x140  AES DMA Source Address Register for Channel 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SADDR</td><td><div style="word-wrap: break-word;"><b>AES DMA Source Address
</b><br>
The AES accelerator supports DMA function to transfer the plain text between system memory and embedded FIFO
<br>
The SADDR keeps the source address of the data buffer where the source text is stored
<br>
Based on the source address, the AES accelerator can read the plain text from system memory and do AES operation
<br>
The start of source address should be located at word boundary
<br>
In other words, bit 1 and 0 of SADDR are ignored.
<br>
SADDR can be read and written
<br>
Writing to SADDR while the AES accelerator is operating doesn't affect the current AES operation
<br>
But the value of SADDR will be updated later on
<br>
Consequently, software can prepare the DMA source address for the next AES operation.
<br>
In DMA mode, software can update the next CRPT_AESn_SADDR before triggering START.
<br>
The value of CRPT_AESn_SADDR and CRPT_AESn_DADDR can be the same.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES0_DADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES0_DADDR
</font><br><p> <font size="2">
Offset: 0x144  AES DMA Destination Address Register for Channel 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DADDR</td><td><div style="word-wrap: break-word;"><b>AES DMA Destination Address
</b><br>
The AES accelerator supports DMA function to transfer the cipher text between system memory and embedded FIFO
<br>
The DADDR keeps the destination address of the data buffer where the engine output's text will be stored
<br>
Based on the destination address, the AES accelerator can write the cipher text back to system memory after the AES operation is finished
<br>
The start of destination address should be located at word boundary
<br>
In other words, bit 1 and 0 of DADDR are ignored.
<br>
DADDR can be read and written
<br>
Writing to DADDR while the AES accelerator is operating doesn't affect the current AES operation
<br>
But the value of DADDR will be updated later on
<br>
Consequently, software can prepare the destination address for the next AES operation.
<br>
In DMA mode, software can update the next CRPT_AESn_DADDR before triggering START.
<br>
The value of CRPT_AESn_SADDR and CRPT_AESn_DADDR can be the same.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES0_CNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES0_CNT
</font><br><p> <font size="2">
Offset: 0x148  AES Byte Count Register for Channel 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>CNT</td><td><div style="word-wrap: break-word;"><b>AES Byte Count
</b><br>
The CRPT_AESn_CNT keeps the byte count of source text that is for the AES engine operating in DMA mode
<br>
The CRPT_AESn_CNT is 32-bit and the maximum of byte count is 4G bytes.
<br>
CRPT_AESn_CNT can be read and written
<br>
Writing to CRPT_AESn_CNT while the AES accelerator is operating doesn't affect the current AES operation
<br>
But the value of CRPT_AESn_CNT will be updated later on
<br>
Consequently, software can prepare the byte count of data for the next AES operation.
<br>
According to CBC-CS1, CBC-CS2, and CBC-CS3 standard, the count of operation data must be at least one block
<br>
Operations that are less than one block will output unexpected result.
<br>
In Non-DMA ECB, CBC, CFB, OFB, and CTR mode, CRPT_AESn_CNT must be set as byte count for the last block of data before feeding in the last block of data
<br>
In Non-DMA CBC-CS1, CBC-CS2, and CBC-CS3 mode, CRPT_AESn_CNT must be set as byte count for the last two blocks of data before feeding in the last two blocks of data.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES1_KEY[8]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES1_KEY[8]
</font><br><p> <font size="2">
Offset: 0x14C ~ 0x168  AES Key Word 0 ~ 7 Register for Channel 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>CRPT_AESn_KEYx
</b><br>
The KEY keeps the security key for AES operation.
<br>
n = 0, 1..3.
<br>
x = 0, 1..7.
<br>
The security key for AES accelerator can be 128, 192, or 256 bits and four, six, or eight 32-bit registers are to store each security key
<br>
{CRPT_AESn_KEY3, CRPT_AESn_KEY2, CRPT_AESn_KEY1, CRPT_AESn_KEY0} stores the 128-bit security key for AES operation
<br>
{CRPT_AESn_KEY5, CRPT_AESn_KEY4, CRPT_AESn_KEY3, CRPT_AESn_KEY2, CRPT_AESn_KEY1, CRPT_AESn_KEY0} stores the 192-bit security key for AES operation
<br>
{CRPT_AESn_KEY7, CRPT_AESn_KEY6, CRPT_AESn_KEY5, CRPT_AESn_KEY4, CRPT_AESn_KEY3, CRPT_AESn_KEY2, CRPT_AESn_KEY1, CRPT_AESn_KEY0} stores the 256-bit security key for AES operation.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES1_IV[4]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES1_IV[4]
</font><br><p> <font size="2">
Offset: 0x16C ~ 0x178  AES Initial Vector Word 0 ~ 3 Register for Channel 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>IV</td><td><div style="word-wrap: break-word;"><b>AES Initial Vectors
</b><br>
n = 0, 1..3.
<br>
x = 0, 1..3.
<br>
Four initial vectors (CRPT_AESn_IV0, CRPT_AESn_IV1, CRPT_AESn_IV2, and CRPT_AESn_IV3) are for AES operating in CBC, CFB, and OFB mode
<br>
Four registers (CRPT_AESn_IV0, CRPT_AESn_IV1, CRPT_AESn_IV2, and CRPT_AESn_IV3) act as Nonce counter when the AES engine is operating in CTR mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES1_SADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES1_SADDR
</font><br><p> <font size="2">
Offset: 0x17C  AES DMA Source Address Register for Channel 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SADDR</td><td><div style="word-wrap: break-word;"><b>AES DMA Source Address
</b><br>
The AES accelerator supports DMA function to transfer the plain text between system memory and embedded FIFO
<br>
The SADDR keeps the source address of the data buffer where the source text is stored
<br>
Based on the source address, the AES accelerator can read the plain text from system memory and do AES operation
<br>
The start of source address should be located at word boundary
<br>
In other words, bit 1 and 0 of SADDR are ignored.
<br>
SADDR can be read and written
<br>
Writing to SADDR while the AES accelerator is operating doesn't affect the current AES operation
<br>
But the value of SADDR will be updated later on
<br>
Consequently, software can prepare the DMA source address for the next AES operation.
<br>
In DMA mode, software can update the next CRPT_AESn_SADDR before triggering START.
<br>
The value of CRPT_AESn_SADDR and CRPT_AESn_DADDR can be the same.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES1_DADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES1_DADDR
</font><br><p> <font size="2">
Offset: 0x180  AES DMA Destination Address Register for Channel 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DADDR</td><td><div style="word-wrap: break-word;"><b>AES DMA Destination Address
</b><br>
The AES accelerator supports DMA function to transfer the cipher text between system memory and embedded FIFO
<br>
The DADDR keeps the destination address of the data buffer where the engine output's text will be stored
<br>
Based on the destination address, the AES accelerator can write the cipher text back to system memory after the AES operation is finished
<br>
The start of destination address should be located at word boundary
<br>
In other words, bit 1 and 0 of DADDR are ignored.
<br>
DADDR can be read and written
<br>
Writing to DADDR while the AES accelerator is operating doesn't affect the current AES operation
<br>
But the value of DADDR will be updated later on
<br>
Consequently, software can prepare the destination address for the next AES operation.
<br>
In DMA mode, software can update the next CRPT_AESn_DADDR before triggering START.
<br>
The value of CRPT_AESn_SADDR and CRPT_AESn_DADDR can be the same.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES1_CNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES1_CNT
</font><br><p> <font size="2">
Offset: 0x184  AES Byte Count Register for Channel 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>CNT</td><td><div style="word-wrap: break-word;"><b>AES Byte Count
</b><br>
The CRPT_AESn_CNT keeps the byte count of source text that is for the AES engine operating in DMA mode
<br>
The CRPT_AESn_CNT is 32-bit and the maximum of byte count is 4G bytes.
<br>
CRPT_AESn_CNT can be read and written
<br>
Writing to CRPT_AESn_CNT while the AES accelerator is operating doesn't affect the current AES operation
<br>
But the value of CRPT_AESn_CNT will be updated later on
<br>
Consequently, software can prepare the byte count of data for the next AES operation.
<br>
According to CBC-CS1, CBC-CS2, and CBC-CS3 standard, the count of operation data must be at least one block
<br>
Operations that are less than one block will output unexpected result.
<br>
In Non-DMA ECB, CBC, CFB, OFB, and CTR mode, CRPT_AESn_CNT must be set as byte count for the last block of data before feeding in the last block of data
<br>
In Non-DMA CBC-CS1, CBC-CS2, and CBC-CS3 mode, CRPT_AESn_CNT must be set as byte count for the last two blocks of data before feeding in the last two blocks of data.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES2_KEY[8]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES2_KEY[8]
</font><br><p> <font size="2">
Offset: 0x188 ~ 0x1A4  AES Key Word 0 ~ 7 Register for Channel 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>CRPT_AESn_KEYx
</b><br>
The KEY keeps the security key for AES operation.
<br>
n = 0, 1..3.
<br>
x = 0, 1..7.
<br>
The security key for AES accelerator can be 128, 192, or 256 bits and four, six, or eight 32-bit registers are to store each security key
<br>
{CRPT_AESn_KEY3, CRPT_AESn_KEY2, CRPT_AESn_KEY1, CRPT_AESn_KEY0} stores the 128-bit security key for AES operation
<br>
{CRPT_AESn_KEY5, CRPT_AESn_KEY4, CRPT_AESn_KEY3, CRPT_AESn_KEY2, CRPT_AESn_KEY1, CRPT_AESn_KEY0} stores the 192-bit security key for AES operation
<br>
{CRPT_AESn_KEY7, CRPT_AESn_KEY6, CRPT_AESn_KEY5, CRPT_AESn_KEY4, CRPT_AESn_KEY3, CRPT_AESn_KEY2, CRPT_AESn_KEY1, CRPT_AESn_KEY0} stores the 256-bit security key for AES operation.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES2_IV[4]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES2_IV[4]
</font><br><p> <font size="2">
Offset: 0x1A8 ~ 0x1B4  AES Initial Vector Word 0 ~ 3 Register for Channel 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>IV</td><td><div style="word-wrap: break-word;"><b>AES Initial Vectors
</b><br>
n = 0, 1..3.
<br>
x = 0, 1..3.
<br>
Four initial vectors (CRPT_AESn_IV0, CRPT_AESn_IV1, CRPT_AESn_IV2, and CRPT_AESn_IV3) are for AES operating in CBC, CFB, and OFB mode
<br>
Four registers (CRPT_AESn_IV0, CRPT_AESn_IV1, CRPT_AESn_IV2, and CRPT_AESn_IV3) act as Nonce counter when the AES engine is operating in CTR mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES2_SADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES2_SADDR
</font><br><p> <font size="2">
Offset: 0x1B8  AES DMA Source Address Register for Channel 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SADDR</td><td><div style="word-wrap: break-word;"><b>AES DMA Source Address
</b><br>
The AES accelerator supports DMA function to transfer the plain text between system memory and embedded FIFO
<br>
The SADDR keeps the source address of the data buffer where the source text is stored
<br>
Based on the source address, the AES accelerator can read the plain text from system memory and do AES operation
<br>
The start of source address should be located at word boundary
<br>
In other words, bit 1 and 0 of SADDR are ignored.
<br>
SADDR can be read and written
<br>
Writing to SADDR while the AES accelerator is operating doesn't affect the current AES operation
<br>
But the value of SADDR will be updated later on
<br>
Consequently, software can prepare the DMA source address for the next AES operation.
<br>
In DMA mode, software can update the next CRPT_AESn_SADDR before triggering START.
<br>
The value of CRPT_AESn_SADDR and CRPT_AESn_DADDR can be the same.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES2_DADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES2_DADDR
</font><br><p> <font size="2">
Offset: 0x1BC  AES DMA Destination Address Register for Channel 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DADDR</td><td><div style="word-wrap: break-word;"><b>AES DMA Destination Address
</b><br>
The AES accelerator supports DMA function to transfer the cipher text between system memory and embedded FIFO
<br>
The DADDR keeps the destination address of the data buffer where the engine output's text will be stored
<br>
Based on the destination address, the AES accelerator can write the cipher text back to system memory after the AES operation is finished
<br>
The start of destination address should be located at word boundary
<br>
In other words, bit 1 and 0 of DADDR are ignored.
<br>
DADDR can be read and written
<br>
Writing to DADDR while the AES accelerator is operating doesn't affect the current AES operation
<br>
But the value of DADDR will be updated later on
<br>
Consequently, software can prepare the destination address for the next AES operation.
<br>
In DMA mode, software can update the next CRPT_AESn_DADDR before triggering START.
<br>
The value of CRPT_AESn_SADDR and CRPT_AESn_DADDR can be the same.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES2_CNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES2_CNT
</font><br><p> <font size="2">
Offset: 0x1C0  AES Byte Count Register for Channel 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>CNT</td><td><div style="word-wrap: break-word;"><b>AES Byte Count
</b><br>
The CRPT_AESn_CNT keeps the byte count of source text that is for the AES engine operating in DMA mode
<br>
The CRPT_AESn_CNT is 32-bit and the maximum of byte count is 4G bytes.
<br>
CRPT_AESn_CNT can be read and written
<br>
Writing to CRPT_AESn_CNT while the AES accelerator is operating doesn't affect the current AES operation
<br>
But the value of CRPT_AESn_CNT will be updated later on
<br>
Consequently, software can prepare the byte count of data for the next AES operation.
<br>
According to CBC-CS1, CBC-CS2, and CBC-CS3 standard, the count of operation data must be at least one block
<br>
Operations that are less than one block will output unexpected result.
<br>
In Non-DMA ECB, CBC, CFB, OFB, and CTR mode, CRPT_AESn_CNT must be set as byte count for the last block of data before feeding in the last block of data
<br>
In Non-DMA CBC-CS1, CBC-CS2, and CBC-CS3 mode, CRPT_AESn_CNT must be set as byte count for the last two blocks of data before feeding in the last two blocks of data.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES3_KEY[8]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES3_KEY[8]
</font><br><p> <font size="2">
Offset: 0x1C4 ~ 0x1E0  AES Key Word 0 ~ 7 Register for Channel 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>CRPT_AESn_KEYx
</b><br>
The KEY keeps the security key for AES operation.
<br>
n = 0, 1..3.
<br>
x = 0, 1..7.
<br>
The security key for AES accelerator can be 128, 192, or 256 bits and four, six, or eight 32-bit registers are to store each security key
<br>
{CRPT_AESn_KEY3, CRPT_AESn_KEY2, CRPT_AESn_KEY1, CRPT_AESn_KEY0} stores the 128-bit security key for AES operation
<br>
{CRPT_AESn_KEY5, CRPT_AESn_KEY4, CRPT_AESn_KEY3, CRPT_AESn_KEY2, CRPT_AESn_KEY1, CRPT_AESn_KEY0} stores the 192-bit security key for AES operation
<br>
{CRPT_AESn_KEY7, CRPT_AESn_KEY6, CRPT_AESn_KEY5, CRPT_AESn_KEY4, CRPT_AESn_KEY3, CRPT_AESn_KEY2, CRPT_AESn_KEY1, CRPT_AESn_KEY0} stores the 256-bit security key for AES operation.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES3_IV[4]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES3_IV[4]
</font><br><p> <font size="2">
Offset: 0x1E4 ~ 0x1F0  AES Initial Vector Word 0 ~ 3 Register for Channel 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>IV</td><td><div style="word-wrap: break-word;"><b>AES Initial Vectors
</b><br>
n = 0, 1..3.
<br>
x = 0, 1..3.
<br>
Four initial vectors (CRPT_AESn_IV0, CRPT_AESn_IV1, CRPT_AESn_IV2, and CRPT_AESn_IV3) are for AES operating in CBC, CFB, and OFB mode
<br>
Four registers (CRPT_AESn_IV0, CRPT_AESn_IV1, CRPT_AESn_IV2, and CRPT_AESn_IV3) act as Nonce counter when the AES engine is operating in CTR mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES3_SADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES3_SADDR
</font><br><p> <font size="2">
Offset: 0x1F4  AES DMA Source Address Register for Channel 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SADDR</td><td><div style="word-wrap: break-word;"><b>AES DMA Source Address
</b><br>
The AES accelerator supports DMA function to transfer the plain text between system memory and embedded FIFO
<br>
The SADDR keeps the source address of the data buffer where the source text is stored
<br>
Based on the source address, the AES accelerator can read the plain text from system memory and do AES operation
<br>
The start of source address should be located at word boundary
<br>
In other words, bit 1 and 0 of SADDR are ignored.
<br>
SADDR can be read and written
<br>
Writing to SADDR while the AES accelerator is operating doesn't affect the current AES operation
<br>
But the value of SADDR will be updated later on
<br>
Consequently, software can prepare the DMA source address for the next AES operation.
<br>
In DMA mode, software can update the next CRPT_AESn_SADDR before triggering START.
<br>
The value of CRPT_AESn_SADDR and CRPT_AESn_DADDR can be the same.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES3_DADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES3_DADDR
</font><br><p> <font size="2">
Offset: 0x1F8  AES DMA Destination Address Register for Channel 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DADDR</td><td><div style="word-wrap: break-word;"><b>AES DMA Destination Address
</b><br>
The AES accelerator supports DMA function to transfer the cipher text between system memory and embedded FIFO
<br>
The DADDR keeps the destination address of the data buffer where the engine output's text will be stored
<br>
Based on the destination address, the AES accelerator can write the cipher text back to system memory after the AES operation is finished
<br>
The start of destination address should be located at word boundary
<br>
In other words, bit 1 and 0 of DADDR are ignored.
<br>
DADDR can be read and written
<br>
Writing to DADDR while the AES accelerator is operating doesn't affect the current AES operation
<br>
But the value of DADDR will be updated later on
<br>
Consequently, software can prepare the destination address for the next AES operation.
<br>
In DMA mode, software can update the next CRPT_AESn_DADDR before triggering START.
<br>
The value of CRPT_AESn_SADDR and CRPT_AESn_DADDR can be the same.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::AES3_CNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AES3_CNT
</font><br><p> <font size="2">
Offset: 0x1FC  AES Byte Count Register for Channel 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>CNT</td><td><div style="word-wrap: break-word;"><b>AES Byte Count
</b><br>
The CRPT_AESn_CNT keeps the byte count of source text that is for the AES engine operating in DMA mode
<br>
The CRPT_AESn_CNT is 32-bit and the maximum of byte count is 4G bytes.
<br>
CRPT_AESn_CNT can be read and written
<br>
Writing to CRPT_AESn_CNT while the AES accelerator is operating doesn't affect the current AES operation
<br>
But the value of CRPT_AESn_CNT will be updated later on
<br>
Consequently, software can prepare the byte count of data for the next AES operation.
<br>
According to CBC-CS1, CBC-CS2, and CBC-CS3 standard, the count of operation data must be at least one block
<br>
Operations that are less than one block will output unexpected result.
<br>
In Non-DMA ECB, CBC, CFB, OFB, and CTR mode, CRPT_AESn_CNT must be set as byte count for the last block of data before feeding in the last block of data
<br>
In Non-DMA CBC-CS1, CBC-CS2, and CBC-CS3 mode, CRPT_AESn_CNT must be set as byte count for the last two blocks of data before feeding in the last two blocks of data.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES_CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES_CTL
</font><br><p> <font size="2">
Offset: 0x200  TDES/DES Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>START</td><td><div style="word-wrap: break-word;"><b>TDES/DES Engine Start
</b><br>
0 = No effect.
<br>
1 = Start TDES/DES engine. The flag BUSY would be set.
<br>
Note: The bit is always 0 when it's read back.
<br>
</div></td></tr><tr><td>
[1]</td><td>STOP</td><td><div style="word-wrap: break-word;"><b>TDES/DES Engine Stop
</b><br>
0 = No effect.
<br>
1 = Stop TDES/DES engine.
<br>
Note: The bit is always 0 when it's read back.
<br>
</div></td></tr><tr><td>
[2]</td><td>TMODE</td><td><div style="word-wrap: break-word;"><b>TDES/DES Engine Operating Mode
</b><br>
0 = Set DES mode for TDES/DES engine.
<br>
1 = Set Triple DES mode for TDES/DES engine.
<br>
</div></td></tr><tr><td>
[3]</td><td>3KEYS</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key Number
</b><br>
0 = Select KEY1 and KEY2 in TDES/DES engine.
<br>
1 = Triple keys in TDES/DES engine Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>DMALAST</td><td><div style="word-wrap: break-word;"><b>TDES/DES Engine Start for the Last Block
</b><br>
In DMA mode, this bit must be set as beginning the last DMA cascade round.
<br>
In Non-DMA mode, this bit must be set as feeding in last block of data.
<br>
</div></td></tr><tr><td>
[6]</td><td>DMACSCAD</td><td><div style="word-wrap: break-word;"><b>TDES/DES Engine DMA with Cascade Mode
</b><br>
0 = DMA cascade function Disabled.
<br>
1 = In DMA Cascade mode, software can update DMA source address register, destination address register, and byte count register during a cascade operation, without finishing the accelerator operation.
<br>
</div></td></tr><tr><td>
[7]</td><td>DMAEN</td><td><div style="word-wrap: break-word;"><b>TDES/DES Engine DMA Enable Control
</b><br>
0 = TDES_DMA engine Disabled.
<br>
TDES engine operates in Non-DMA mode, and get data from the port CRPT_TDES_DATIN.
<br>
1 = TDES_DMA engine Enabled.
<br>
TDES engine operates in DMA mode, and data movement from/to the engine is done by DMA logic.
<br>
</div></td></tr><tr><td>
[10:8]</td><td>OPMODE</td><td><div style="word-wrap: break-word;"><b>TDES/DES Engine Operation Mode
</b><br>
0x00 = ECB (Electronic Codebook Mode).
<br>
0x01 = CBC (Cipher Block Chaining Mode).
<br>
0x02 = CFB (Cipher Feedback Mode).
<br>
0x03 = OFB (Output Feedback Mode).
<br>
0x04 = CTR (Counter Mode).
<br>
Others = CTR (Counter Mode).
<br>
</div></td></tr><tr><td>
[16]</td><td>ENCRPT</td><td><div style="word-wrap: break-word;"><b>TDES/DES Encryption/Decryption
</b><br>
0 = TDES engine executes decryption operation.
<br>
1 = TDES engine executes encryption operation.
<br>
</div></td></tr><tr><td>
[21]</td><td>BLKSWAP</td><td><div style="word-wrap: break-word;"><b>TDES/DES Engine Block Double Word Endian Swap
</b><br>
0 = Keep the original order, e.g. {WORD_H, WORD_L}.
<br>
1 = When this bit is set to 1, the TDES engine would exchange high and low word in the sequence {WORD_L, WORD_H}.
<br>
</div></td></tr><tr><td>
[22]</td><td>OUTSWAP</td><td><div style="word-wrap: break-word;"><b>TDES/DES Engine Output Data Swap
</b><br>
0 = Keep the original order.
<br>
1 = The order that CPU outputs data from the accelerator will be changed from {byte3, byte2, byte1, byte0} to {byte0, byte1, byte2, byte3}.
<br>
</div></td></tr><tr><td>
[23]</td><td>INSWAP</td><td><div style="word-wrap: break-word;"><b>TDES/DES Engine Input Data Swap
</b><br>
0 = Keep the original order.
<br>
1 = The order that CPU feeds data to the accelerator will be changed from {byte3, byte2, byte1, byte0} to {byte0, byte1, byte2, byte3}.
<br>
</div></td></tr><tr><td>
[25:24]</td><td>CHANNEL</td><td><div style="word-wrap: break-word;"><b>TDES/DES Engine Working Channel
</b><br>
00 = Current control register setting is for channel 0.
<br>
01 = Current control register setting is for channel 1.
<br>
10 = Current control register setting is for channel 2.
<br>
11 = Current control register setting is for channel 3.
<br>
</div></td></tr><tr><td>
[30:26]</td><td>KEYUNPRT</td><td><div style="word-wrap: break-word;"><b>Unprotect Key
</b><br>
Writing 0 to CRPT_TDES_CTL [31] and "10110" to CRPT_TDES_CTL [30:26] is to unprotect TDES key.
<br>
The KEYUNPRT can be read and written
<br>
When it is written as the TDES engine is operating, BUSY flag is 1, there would be no effect on KEYUNPRT.
<br>
</div></td></tr><tr><td>
[31]</td><td>KEYPRT</td><td><div style="word-wrap: break-word;"><b>Protect Key
</b><br>
Read as a flag to reflect KEYPRT.
<br>
0 = No effect.
<br>
1 = This bit is to protect the content of TDES key from reading
<br>
The return value for reading CRPT_ TDESn_KEYxH/L is not the content in the registers CRPT_ TDESn_KEYxH/L
<br>
Once it is set, it can be cleared by asserting KEYUNPRT
<br>
The key content would be cleared as well.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES_STS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES_STS
</font><br><p> <font size="2">
Offset: 0x204  TDES/DES Engine Flag
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BUSY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Engine Busy
</b><br>
0 = TDES/DES engine is idle or finished.
<br>
1 = TDES/DES engine is under processing.
<br>
</div></td></tr><tr><td>
[8]</td><td>INBUFEMPTY</td><td><div style="word-wrap: break-word;"><b>TDES/DES in Buffer Empty
</b><br>
0 = There are some data in input buffer waiting for the TDES/DES engine to process.
<br>
1 = TDES/DES input buffer is empty
<br>
Software needs to feed data to the TDES/DES engine
<br>
Otherwise, the TDES/DES engine will be pending to wait for input data.
<br>
</div></td></tr><tr><td>
[9]</td><td>INBUFFULL</td><td><div style="word-wrap: break-word;"><b>TDES/DES in Buffer Full Flag
</b><br>
0 = TDES/DES input buffer is not full. Software can feed the data into the TDES/DES engine.
<br>
1 = TDES input buffer is full
<br>
Software cannot feed data to the TDES/DES engine
<br>
Otherwise, the flag INBUFERR will be set to 1.
<br>
</div></td></tr><tr><td>
[10]</td><td>INBUFERR</td><td><div style="word-wrap: break-word;"><b>TDES/DES in Buffer Error Flag
</b><br>
0 = No error.
<br>
1 = Error happens during feeding data to the TDES/DES engine.
<br>
</div></td></tr><tr><td>
[16]</td><td>OUTBUFEMPTY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Output Buffer Empty Flag
</b><br>
0 = TDES/DES output buffer is not empty. There are some valid data kept in output buffer.
<br>
1 = TDES/DES output buffer is empty, Software cannot get data from TDES_DATA_OUT
<br>
Otherwise the flag OUTBUFERR will be set to 1, since output buffer is empty.
<br>
</div></td></tr><tr><td>
[17]</td><td>OUTBUFFULL</td><td><div style="word-wrap: break-word;"><b>TDES/DES Output Buffer Full Flag
</b><br>
0 = TDES/DES output buffer is not full.
<br>
1 = TDES/DES output buffer is full, and software needs to get data from TDES_DATA_OUT
<br>
Otherwise, the TDES/DES engine will be pending since output buffer is full.
<br>
</div></td></tr><tr><td>
[18]</td><td>OUTBUFERR</td><td><div style="word-wrap: break-word;"><b>TDES/DES Out Buffer Error Flag
</b><br>
0 = No error.
<br>
1 = Error happens during getting test result from TDES/DES engine.
<br>
</div></td></tr><tr><td>
[20]</td><td>BUSERR</td><td><div style="word-wrap: break-word;"><b>TDES/DES DMA Access Bus Error Flag
</b><br>
0 = No error.
<br>
1 = Bus error will stop DMA operation and TDES/DES engine.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES0_KEY1H

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES0_KEY1H
</font><br><p> <font size="2">
Offset: 0x208  TDES/DES Key 1 High Word Register for Channel 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 1 High Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES0_KEY1L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES0_KEY1L
</font><br><p> <font size="2">
Offset: 0x20C  TDES/DES Key 1 Low Word Register for Channel 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 1 Low Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES0_KEY2H

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES0_KEY2H
</font><br><p> <font size="2">
Offset: 0x210  TDES Key 2 High Word Register for Channel 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 2 High Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES0_KEY2L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES0_KEY2L
</font><br><p> <font size="2">
Offset: 0x214  TDES Key 2 Low Word Register for Channel 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 2 Low Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES0_KEY3H

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES0_KEY3H
</font><br><p> <font size="2">
Offset: 0x218  TDES Key 3 High Word Register for Channel 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 3 High Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES0_KEY3L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES0_KEY3L
</font><br><p> <font size="2">
Offset: 0x21C  TDES Key 3 Low Word Register for Channel 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 3 Low Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES0_IVH

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES0_IVH
</font><br><p> <font size="2">
Offset: 0x220  TDES/DES Initial Vector High Word Register for Channel 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>IV</td><td><div style="word-wrap: break-word;"><b>TDES/DES Initial Vector High Word
</b><br>
Initial vector (IV) is for TDES/DES engine in CBC, CFB, and OFB mode
<br>
IV is Nonce counter for TDES/DES engine in CTR mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES0_IVL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES0_IVL
</font><br><p> <font size="2">
Offset: 0x224  TDES/DES Initial Vector Low Word Register for Channel 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>IV</td><td><div style="word-wrap: break-word;"><b>TDES/DES Initial Vector Low Word
</b><br>
Initial vector (IV) is for TDES/DES engine in CBC, CFB, and OFB mode
<br>
IV is Nonce counter for TDES/DES engine in CTR mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES0_SA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES0_SA
</font><br><p> <font size="2">
Offset: 0x228  TDES/DES DMA Source Address Register for Channel 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SADDR</td><td><div style="word-wrap: break-word;"><b>TDES/DES DMA Source Address
</b><br>
The TDES/DES accelerator supports DMA function to transfer the plain text between system memory and embedded FIFO
<br>
The CRPT_TDESn_SA keeps the source address of the data buffer where the source text is stored
<br>
Based on the source address, the TDES/DES accelerator can read the plain text from system memory and do TDES/DES operation
<br>
The start of source address should be located at word boundary
<br>
In other words, bit 1 and 0 of CRPT_TDESn_SA are ignored.
<br>
CRPT_TDESn_SA can be read and written
<br>
Writing to CRPT_TDESn_SA while the TDES/DES accelerator is operating doesn't affect the current TDES/DES operation
<br>
But the value of CRPT_TDESn_SA will be updated later on
<br>
Consequently, software can prepare the DMA source address for the next TDES/DES operation.
<br>
In DMA mode, software can update the next CRPT_TDESn_SA before triggering START.
<br>
CRPT_TDESn_SA and CRPT_TDESn_DA can be the same in the value.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES0_DA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES0_DA
</font><br><p> <font size="2">
Offset: 0x22C  TDES/DES DMA Destination Address Register for Channel 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DADDR</td><td><div style="word-wrap: break-word;"><b>TDES/DES DMA Destination Address
</b><br>
The TDES/DES accelerator supports DMA function to transfer the cipher text between system memory and embedded FIFO
<br>
The CRPT_TDESn_DA keeps the destination address of the data buffer where the engine output's text will be stored
<br>
Based on the destination address, the TDES/DES accelerator can write the cipher text back to system memory after the TDES/DES operation is finished
<br>
The start of destination address should be located at word boundary
<br>
In other words, bit 1 and 0 of CRPT_TDESn_DA are ignored.
<br>
CRPT_TDESn_DA can be read and written
<br>
Writing to CRPT_TDESn_DA while the TDES/DES accelerator is operating doesn't affect the current TDES/DES operation
<br>
But the value of CRPT_TDESn_DA will be updated later on
<br>
Consequently, software can prepare the destination address for the next TDES/DES operation.
<br>
In DMA mode, software can update the next CRPT_TDESn_DA before triggering START.
<br>
CRPT_TDESn_SAD and CRPT_TDESn_DA can be the same in the value.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES0_CNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES0_CNT
</font><br><p> <font size="2">
Offset: 0x230  TDES/DES Byte Count Register for Channel 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>CNT</td><td><div style="word-wrap: break-word;"><b>TDES/DES Byte Count
</b><br>
The CRPT_TDESn_CNT keeps the byte count of source text that is for the TDES/DES engine operating in DMA mode
<br>
The CRPT_TDESn_CNT is 32-bit and the maximum of byte count is 4G bytes.
<br>
CRPT_TDESn_CNT can be read and written
<br>
Writing to CRPT_TDESn_CNT while the TDES/DES accelerator is operating doesn't affect the current TDES/DES operation
<br>
But the value of CRPT_TDESn_CNT will be updated later on
<br>
Consequently, software can prepare the byte count of data for the next TDES /DES operation.
<br>
In Non-DMA ECB, CBC, CFB, OFB, and CTR mode, CRPT_TDESn_CNT must be set as byte count for the last block of data before feeding in the last block of data.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES_DATIN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES_DATIN
</font><br><p> <font size="2">
Offset: 0x234  TDES/DES Engine Input data Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DATIN</td><td><div style="word-wrap: break-word;"><b>TDES/DES Engine Input Port
</b><br>
CPU feeds data to TDES/DES engine through this port by checking CRPT_TDES_STS
<br>
Feed data as INBUFFULL is 0.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES_DATOUT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES_DATOUT
</font><br><p> <font size="2">
Offset: 0x238  TDES/DES Engine Output data Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DATOUT</td><td><div style="word-wrap: break-word;"><b>TDES/DES Engine Output Port
</b><br>
CPU gets result from the TDES/DES engine through this port by checking CRPT_TDES_STS
<br>
Get data as OUTBUFEMPTY is 0.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES1_KEY1H

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES1_KEY1H
</font><br><p> <font size="2">
Offset: 0x248  TDES/DES Key 1 High Word Register for Channel 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 1 High Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES1_KEY1L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES1_KEY1L
</font><br><p> <font size="2">
Offset: 0x24C  TDES/DES Key 1 Low Word Register for Channel 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 1 Low Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES1_KEY2H

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES1_KEY2H
</font><br><p> <font size="2">
Offset: 0x250  TDES Key 2 High Word Register for Channel 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 2 High Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES1_KEY2L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES1_KEY2L
</font><br><p> <font size="2">
Offset: 0x254  TDES Key 2 Low Word Register for Channel 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 2 Low Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES1_KEY3H

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES1_KEY3H
</font><br><p> <font size="2">
Offset: 0x258  TDES Key 3 High Word Register for Channel 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 3 High Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES1_KEY3L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES1_KEY3L
</font><br><p> <font size="2">
Offset: 0x25C  TDES Key 3 Low Word Register for Channel 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 3 Low Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES1_IVH

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES1_IVH
</font><br><p> <font size="2">
Offset: 0x260  TDES/DES Initial Vector High Word Register for Channel 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>IV</td><td><div style="word-wrap: break-word;"><b>TDES/DES Initial Vector High Word
</b><br>
Initial vector (IV) is for TDES/DES engine in CBC, CFB, and OFB mode
<br>
IV is Nonce counter for TDES/DES engine in CTR mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES1_IVL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES1_IVL
</font><br><p> <font size="2">
Offset: 0x264  TDES/DES Initial Vector Low Word Register for Channel 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>IV</td><td><div style="word-wrap: break-word;"><b>TDES/DES Initial Vector Low Word
</b><br>
Initial vector (IV) is for TDES/DES engine in CBC, CFB, and OFB mode
<br>
IV is Nonce counter for TDES/DES engine in CTR mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES1_SA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES1_SA
</font><br><p> <font size="2">
Offset: 0x268  TDES/DES DMA Source Address Register for Channel 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SADDR</td><td><div style="word-wrap: break-word;"><b>TDES/DES DMA Source Address
</b><br>
The TDES/DES accelerator supports DMA function to transfer the plain text between system memory and embedded FIFO
<br>
The CRPT_TDESn_SA keeps the source address of the data buffer where the source text is stored
<br>
Based on the source address, the TDES/DES accelerator can read the plain text from system memory and do TDES/DES operation
<br>
The start of source address should be located at word boundary
<br>
In other words, bit 1 and 0 of CRPT_TDESn_SA are ignored.
<br>
CRPT_TDESn_SA can be read and written
<br>
Writing to CRPT_TDESn_SA while the TDES/DES accelerator is operating doesn't affect the current TDES/DES operation
<br>
But the value of CRPT_TDESn_SA will be updated later on
<br>
Consequently, software can prepare the DMA source address for the next TDES/DES operation.
<br>
In DMA mode, software can update the next CRPT_TDESn_SA before triggering START.
<br>
CRPT_TDESn_SA and CRPT_TDESn_DA can be the same in the value.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES1_DA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES1_DA
</font><br><p> <font size="2">
Offset: 0x26C  TDES/DES DMA Destination Address Register for Channel 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DADDR</td><td><div style="word-wrap: break-word;"><b>TDES/DES DMA Destination Address
</b><br>
The TDES/DES accelerator supports DMA function to transfer the cipher text between system memory and embedded FIFO
<br>
The CRPT_TDESn_DA keeps the destination address of the data buffer where the engine output's text will be stored
<br>
Based on the destination address, the TDES/DES accelerator can write the cipher text back to system memory after the TDES/DES operation is finished
<br>
The start of destination address should be located at word boundary
<br>
In other words, bit 1 and 0 of CRPT_TDESn_DA are ignored.
<br>
CRPT_TDESn_DA can be read and written
<br>
Writing to CRPT_TDESn_DA while the TDES/DES accelerator is operating doesn't affect the current TDES/DES operation
<br>
But the value of CRPT_TDESn_DA will be updated later on
<br>
Consequently, software can prepare the destination address for the next TDES/DES operation.
<br>
In DMA mode, software can update the next CRPT_TDESn_DA before triggering START.
<br>
CRPT_TDESn_SAD and CRPT_TDESn_DA can be the same in the value.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES1_CNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES1_CNT
</font><br><p> <font size="2">
Offset: 0x270  TDES/DES Byte Count Register for Channel 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>CNT</td><td><div style="word-wrap: break-word;"><b>TDES/DES Byte Count
</b><br>
The CRPT_TDESn_CNT keeps the byte count of source text that is for the TDES/DES engine operating in DMA mode
<br>
The CRPT_TDESn_CNT is 32-bit and the maximum of byte count is 4G bytes.
<br>
CRPT_TDESn_CNT can be read and written
<br>
Writing to CRPT_TDESn_CNT while the TDES/DES accelerator is operating doesn't affect the current TDES/DES operation
<br>
But the value of CRPT_TDESn_CNT will be updated later on
<br>
Consequently, software can prepare the byte count of data for the next TDES /DES operation.
<br>
In Non-DMA ECB, CBC, CFB, OFB, and CTR mode, CRPT_TDESn_CNT must be set as byte count for the last block of data before feeding in the last block of data.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES2_KEY1H

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES2_KEY1H
</font><br><p> <font size="2">
Offset: 0x288  TDES/DES Key 1 High Word Register for Channel 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 1 High Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES2_KEY1L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES2_KEY1L
</font><br><p> <font size="2">
Offset: 0x28C  TDES/DES Key 1 Low Word Register for Channel 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 1 Low Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES2_KEY2H

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES2_KEY2H
</font><br><p> <font size="2">
Offset: 0x290  TDES Key 2 High Word Register for Channel 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 2 High Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES2_KEY2L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES2_KEY2L
</font><br><p> <font size="2">
Offset: 0x294  TDES Key 2 Low Word Register for Channel 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 2 Low Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES2_KEY3H

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES2_KEY3H
</font><br><p> <font size="2">
Offset: 0x298  TDES Key 3 High Word Register for Channel 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 3 High Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES2_KEY3L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES2_KEY3L
</font><br><p> <font size="2">
Offset: 0x29C  TDES Key 3 Low Word Register for Channel 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 3 Low Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES2_IVH

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES2_IVH
</font><br><p> <font size="2">
Offset: 0x2A0  TDES/DES Initial Vector High Word Register for Channel 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>IV</td><td><div style="word-wrap: break-word;"><b>TDES/DES Initial Vector High Word
</b><br>
Initial vector (IV) is for TDES/DES engine in CBC, CFB, and OFB mode
<br>
IV is Nonce counter for TDES/DES engine in CTR mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES2_IVL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES2_IVL
</font><br><p> <font size="2">
Offset: 0x2A4  TDES/DES Initial Vector Low Word Register for Channel 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>IV</td><td><div style="word-wrap: break-word;"><b>TDES/DES Initial Vector Low Word
</b><br>
Initial vector (IV) is for TDES/DES engine in CBC, CFB, and OFB mode
<br>
IV is Nonce counter for TDES/DES engine in CTR mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES2_SA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES2_SA
</font><br><p> <font size="2">
Offset: 0x2A8  TDES/DES DMA Source Address Register for Channel 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SADDR</td><td><div style="word-wrap: break-word;"><b>TDES/DES DMA Source Address
</b><br>
The TDES/DES accelerator supports DMA function to transfer the plain text between system memory and embedded FIFO
<br>
The CRPT_TDESn_SA keeps the source address of the data buffer where the source text is stored
<br>
Based on the source address, the TDES/DES accelerator can read the plain text from system memory and do TDES/DES operation
<br>
The start of source address should be located at word boundary
<br>
In other words, bit 1 and 0 of CRPT_TDESn_SA are ignored.
<br>
CRPT_TDESn_SA can be read and written
<br>
Writing to CRPT_TDESn_SA while the TDES/DES accelerator is operating doesn't affect the current TDES/DES operation
<br>
But the value of CRPT_TDESn_SA will be updated later on
<br>
Consequently, software can prepare the DMA source address for the next TDES/DES operation.
<br>
In DMA mode, software can update the next CRPT_TDESn_SA before triggering START.
<br>
CRPT_TDESn_SA and CRPT_TDESn_DA can be the same in the value.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES2_DA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES2_DA
</font><br><p> <font size="2">
Offset: 0x2AC  TDES/DES DMA Destination Address Register for Channel 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DADDR</td><td><div style="word-wrap: break-word;"><b>TDES/DES DMA Destination Address
</b><br>
The TDES/DES accelerator supports DMA function to transfer the cipher text between system memory and embedded FIFO
<br>
The CRPT_TDESn_DA keeps the destination address of the data buffer where the engine output's text will be stored
<br>
Based on the destination address, the TDES/DES accelerator can write the cipher text back to system memory after the TDES/DES operation is finished
<br>
The start of destination address should be located at word boundary
<br>
In other words, bit 1 and 0 of CRPT_TDESn_DA are ignored.
<br>
CRPT_TDESn_DA can be read and written
<br>
Writing to CRPT_TDESn_DA while the TDES/DES accelerator is operating doesn't affect the current TDES/DES operation
<br>
But the value of CRPT_TDESn_DA will be updated later on
<br>
Consequently, software can prepare the destination address for the next TDES/DES operation.
<br>
In DMA mode, software can update the next CRPT_TDESn_DA before triggering START.
<br>
CRPT_TDESn_SAD and CRPT_TDESn_DA can be the same in the value.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES2_CNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES2_CNT
</font><br><p> <font size="2">
Offset: 0x2B0  TDES/DES Byte Count Register for Channel 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>CNT</td><td><div style="word-wrap: break-word;"><b>TDES/DES Byte Count
</b><br>
The CRPT_TDESn_CNT keeps the byte count of source text that is for the TDES/DES engine operating in DMA mode
<br>
The CRPT_TDESn_CNT is 32-bit and the maximum of byte count is 4G bytes.
<br>
CRPT_TDESn_CNT can be read and written
<br>
Writing to CRPT_TDESn_CNT while the TDES/DES accelerator is operating doesn't affect the current TDES/DES operation
<br>
But the value of CRPT_TDESn_CNT will be updated later on
<br>
Consequently, software can prepare the byte count of data for the next TDES /DES operation.
<br>
In Non-DMA ECB, CBC, CFB, OFB, and CTR mode, CRPT_TDESn_CNT must be set as byte count for the last block of data before feeding in the last block of data.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES3_KEY1H

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES3_KEY1H
</font><br><p> <font size="2">
Offset: 0x2C8  TDES/DES Key 1 High Word Register for Channel 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 1 High Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES3_KEY1L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES3_KEY1L
</font><br><p> <font size="2">
Offset: 0x2CC  TDES/DES Key 1 Low Word Register for Channel 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 1 High Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES3_KEY2H

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES3_KEY2H
</font><br><p> <font size="2">
Offset: 0x2D0  TDES Key 2 High Word Register for Channel 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 2 High Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES3_KEY2L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES3_KEY2L
</font><br><p> <font size="2">
Offset: 0x2D4  TDES Key 2 Low Word Register for Channel 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 2 Low Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES3_KEY3H

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES3_KEY3H
</font><br><p> <font size="2">
Offset: 0x2D8  TDES Key 3 High Word Register for Channel 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 3 High Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES3_KEY3L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES3_KEY3L
</font><br><p> <font size="2">
Offset: 0x2DC  TDES Key 3 Low Word Register for Channel 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY</td><td><div style="word-wrap: break-word;"><b>TDES/DES Key 3 Low Word
</b><br>
The key registers for TDES/DES algorithm calculation
<br>
The security key for the TDES/DES accelerator is 64 bits
<br>
Thus, it needs two 32-bit registers to store a security key
<br>
The register CRPT_TDESn_KEYxH is used to keep the bit [63:32] of security key for the TDES/DES operation, while the register CRPT_TDESn_KEYxL is used to keep the bit [31:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES3_IVH

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES3_IVH
</font><br><p> <font size="2">
Offset: 0x2E0  TDES/DES Initial Vector High Word Register for Channel 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>IV</td><td><div style="word-wrap: break-word;"><b>TDES/DES Initial Vector High Word
</b><br>
Initial vector (IV) is for TDES/DES engine in CBC, CFB, and OFB mode
<br>
IV is Nonce counter for TDES/DES engine in CTR mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES3_IVL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES3_IVL
</font><br><p> <font size="2">
Offset: 0x2E4  TDES/DES Initial Vector Low Word Register for Channel 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>IV</td><td><div style="word-wrap: break-word;"><b>TDES/DES Initial Vector Low Word
</b><br>
Initial vector (IV) is for TDES/DES engine in CBC, CFB, and OFB mode
<br>
IV is Nonce counter for TDES/DES engine in CTR mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES3_SA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES3_SA
</font><br><p> <font size="2">
Offset: 0x2E8  TDES/DES DMA Source Address Register for Channel 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SADDR</td><td><div style="word-wrap: break-word;"><b>TDES/DES DMA Source Address
</b><br>
The TDES/DES accelerator supports DMA function to transfer the plain text between system memory and embedded FIFO
<br>
The CRPT_TDESn_SA keeps the source address of the data buffer where the source text is stored
<br>
Based on the source address, the TDES/DES accelerator can read the plain text from system memory and do TDES/DES operation
<br>
The start of source address should be located at word boundary
<br>
In other words, bit 1 and 0 of CRPT_TDESn_SA are ignored.
<br>
CRPT_TDESn_SA can be read and written
<br>
Writing to CRPT_TDESn_SA while the TDES/DES accelerator is operating doesn't affect the current TDES/DES operation
<br>
But the value of CRPT_TDESn_SA will be updated later on
<br>
Consequently, software can prepare the DMA source address for the next TDES/DES operation.
<br>
In DMA mode, software can update the next CRPT_TDESn_SA before triggering START.
<br>
CRPT_TDESn_SA and CRPT_TDESn_DA can be the same in the value.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES3_DA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES3_DA
</font><br><p> <font size="2">
Offset: 0x2EC  TDES/DES DMA Destination Address Register for Channel 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DADDR</td><td><div style="word-wrap: break-word;"><b>TDES/DES DMA Destination Address
</b><br>
The TDES/DES accelerator supports DMA function to transfer the cipher text between system memory and embedded FIFO
<br>
The CRPT_TDESn_DA keeps the destination address of the data buffer where the engine output's text will be stored
<br>
Based on the destination address, the TDES/DES accelerator can write the cipher text back to system memory after the TDES/DES operation is finished
<br>
The start of destination address should be located at word boundary
<br>
In other words, bit 1 and 0 of CRPT_TDESn_DA are ignored.
<br>
CRPT_TDESn_DA can be read and written
<br>
Writing to CRPT_TDESn_DA while the TDES/DES accelerator is operating doesn't affect the current TDES/DES operation
<br>
But the value of CRPT_TDESn_DA will be updated later on
<br>
Consequently, software can prepare the destination address for the next TDES/DES operation.
<br>
In DMA mode, software can update the next CRPT_TDESn_DA before triggering START.
<br>
CRPT_TDESn_SAD and CRPT_TDESn_DA can be the same in the value.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::TDES3_CNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TDES3_CNT
</font><br><p> <font size="2">
Offset: 0x2F0  TDES/DES Byte Count Register for Channel 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>CNT</td><td><div style="word-wrap: break-word;"><b>TDES/DES Byte Count
</b><br>
The CRPT_TDESn_CNT keeps the byte count of source text that is for the TDES/DES engine operating in DMA mode
<br>
The CRPT_TDESn_CNT is 32-bit and the maximum of byte count is 4G bytes.
<br>
CRPT_TDESn_CNT can be read and written
<br>
Writing to CRPT_TDESn_CNT while the TDES/DES accelerator is operating doesn't affect the current TDES/DES operation
<br>
But the value of CRPT_TDESn_CNT will be updated later on
<br>
Consequently, software can prepare the byte count of data for the next TDES /DES operation.
<br>
In Non-DMA ECB, CBC, CFB, OFB, and CTR mode, CRPT_TDESn_CNT must be set as byte count for the last block of data before feeding in the last block of data.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::HMAC_CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HMAC_CTL
</font><br><p> <font size="2">
Offset: 0x300  SHA/HMAC Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>START</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Engine Start
</b><br>
0 = No effect.
<br>
1 = Start SHA/HMAC engine. BUSY flag will be set.
<br>
This bit is always 0 when it's read back.
<br>
</div></td></tr><tr><td>
[1]</td><td>STOP</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Engine Stop
</b><br>
0 = No effect.
<br>
1 = Stop SHA/HMAC engine.
<br>
This bit is always 0 when it's read back.
<br>
</div></td></tr><tr><td>
[4]</td><td>HMACEN</td><td><div style="word-wrap: break-word;"><b>HMAC_SHA Engine Operating Mode
</b><br>
0 = execute SHA function.
<br>
1 = execute HMAC function.
<br>
</div></td></tr><tr><td>
[5]</td><td>DMALAST</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Last Block
</b><br>
This bit must be set as feeding in last byte of data.
<br>
</div></td></tr><tr><td>
[7]</td><td>DMAEN</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Engine DMA Enable Control
</b><br>
0 = SHA/HMAC DMA engine Disabled.
<br>
SHA/HMAC engine operates in Non-DMA mode, and gets data from the port CRPT_HMAC_DATIN.
<br>
1 = SHA/HMAC DMA engine Enabled.
<br>
SHA/HMAC engine operates in DMA mode, and data movement from/to the engine is done by DMA logic.
<br>
</div></td></tr><tr><td>
[10:8]</td><td>OPMODE</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Engine Operation Modes
</b><br>
0x0xx: SHA160
<br>
0x100: SHA256
<br>
0x101: SHA224
<br>
0x110: SHA512
<br>
0x111: SHA384
<br>
These bits can be read and written. But writing to them wouldn't take effect as BUSY is 1.
<br>
</div></td></tr><tr><td>
[22]</td><td>OUTSWAP</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Engine Output Data Swap
</b><br>
0 = Keep the original order.
<br>
1 = The order that CPU feeds data to the accelerator will be changed from {byte3, byte2, byte1, byte0} to {byte0, byte1, byte2, byte3}.
<br>
</div></td></tr><tr><td>
[23]</td><td>INSWAP</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Engine Input Data Swap
</b><br>
0 = Keep the original order.
<br>
1 = The order that CPU feeds data to the accelerator will be changed from {byte3, byte2, byte1, byte0} to {byte0, byte1, byte2, byte3}.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::HMAC_STS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HMAC_STS
</font><br><p> <font size="2">
Offset: 0x304  SHA/HMAC Status Flag
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BUSY</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Engine Busy
</b><br>
0 = SHA/HMAC engine is idle or finished.
<br>
1 = SHA/HMAC engine is busy.
<br>
</div></td></tr><tr><td>
[1]</td><td>DMABUSY</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Engine DMA Busy Flag
</b><br>
0 = SHA/HMAC DMA engine is idle or finished.
<br>
1 = SHA/HMAC DMA engine is busy.
<br>
</div></td></tr><tr><td>
[8]</td><td>DMAERR</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Engine DMA Error Flag
</b><br>
0 = Show the SHA/HMAC engine access normal.
<br>
1 = Show the SHA/HMAC engine access error.
<br>
</div></td></tr><tr><td>
[16]</td><td>DATINREQ</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Non-DMA Mode Data Input Request
</b><br>
0 = No effect.
<br>
1 = Request SHA/HMAC Non-DMA mode data input.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::HMAC_DGST[16]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HMAC_DGST[16]
</font><br><p> <font size="2">
Offset: 0x308 ~ 0x344  SHA/HMAC Digest Message 0 ~ 15
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DGST</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Digest Message Output Register
</b><br>
For SHA-160, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST4.
<br>
For SHA-224, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST6.
<br>
For SHA-256, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST7.
<br>
For SHA-384, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST11.
<br>
For SHA-512, the digest is stored in CRPT_HMAC_DGST0 ~ CRPT_HMAC_DGST15.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::HMAC_KEYCNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HMAC_KEYCNT
</font><br><p> <font size="2">
Offset: 0x348  SHA/HMAC Key Byte Count Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEYCNT</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Key Byte Count
</b><br>
The CRPT_HMAC_KEYCNT keeps the byte count of key that SHA/HMAC engine operates
<br>
The register is 32-bit and the maximum byte count is 4G bytes
<br>
It can be read and written.
<br>
Writing to the register CRPT_HMAC_KEYCNT as the SHA/HMAC accelerator operating doesn't affect the current SHA/HMAC operation
<br>
But the value of CRPT_SHA _KEYCNT will be updated later on
<br>
Consequently, software can prepare the key count for the next SHA/HMAC operation.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::HMAC_SADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HMAC_SADDR
</font><br><p> <font size="2">
Offset: 0x34C  SHA/HMAC DMA Source Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SADDR</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC DMA Source Address
</b><br>
The SHA/HMAC accelerator supports DMA function to transfer the plain text between system memory and embedded FIFO
<br>
The CRPT_HMAC_SADDR keeps the source address of the data buffer where the source text is stored
<br>
Based on the source address, the SHA/HMAC accelerator can read the plain text from system memory and do SHA/HMAC operation
<br>
The start of source address should be located at word boundary
<br>
In other words, bit 1 and 0 of CRPT_HMAC_SADDR are ignored.
<br>
CRPT_HMAC_SADDR can be read and written
<br>
Writing to CRPT_HMAC_SADDR while the SHA/HMAC accelerator is operating doesn't affect the current SHA/HMAC operation
<br>
But the value of CRPT_HMAC_SADDR will be updated later on
<br>
Consequently, software can prepare the DMA source address for the next SHA/HMAC operation.
<br>
In DMA mode, software can update the next CRPT_HMAC_SADDR before triggering START.
<br>
CRPT_HMAC_SADDR and CRPT_HMAC_DADDR can be the same in the value.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::HMAC_DMACNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HMAC_DMACNT
</font><br><p> <font size="2">
Offset: 0x350  SHA/HMAC Byte Count Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DMACNT</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Operation Byte Count
</b><br>
The CRPT_HMAC_DMACNT keeps the byte count of source text that is for the SHA/HMAC engine operating in DMA mode
<br>
The CRPT_HMAC_DMACNT is 32-bit and the maximum of byte count is 4G bytes.
<br>
CRPT_HMAC_DMACNT can be read and written
<br>
Writing to CRPT_HMAC_DMACNT while the SHA/HMAC accelerator is operating doesn't affect the current SHA/HMAC operation
<br>
But the value of CRPT_HMAC_DMACNT will be updated later on
<br>
Consequently, software can prepare the byte count of data for the next SHA/HMAC operation.
<br>
In Non-DMA mode, CRPT_HMAC_DMACNT must be set as the byte count of the last block before feeding in the last block of data.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::HMAC_DATIN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HMAC_DATIN
</font><br><p> <font size="2">
Offset: 0x354  SHA/HMAC Engine Non-DMA Mode Data Input Port Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DATIN</td><td><div style="word-wrap: break-word;"><b>SHA/HMAC Engine Input Port
</b><br>
CPU feeds data to SHA/HMAC engine through this port by checking CRPT_HMAC_STS
<br>
Feed data as DATINREQ is 1.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::ECC_CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ECC_CTL
</font><br><p> <font size="2">
Offset: 0x800  ECC Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>START</td><td><div style="word-wrap: break-word;"><b>ECC Accelerator Start
</b><br>
0 = No effect.
<br>
1 = Start ECC accelerator. BUSY flag will be set.
<br>
This bit is always 0 when it's read back.
<br>
ECC accelerator will ignore this START signal when BUSY flag is 1.
<br>
</div></td></tr><tr><td>
[1]</td><td>STOP</td><td><div style="word-wrap: break-word;"><b>ECC Accelerator Stop
</b><br>
0 = No effect.
<br>
1 = Abort ECC accelerator and make it into idle state.
<br>
This bit is always 0 when it's read back.
<br>
Remember to clear ECC interrupt flag after stopping ECC accelerator.
<br>
</div></td></tr><tr><td>
[7]</td><td>DMAEN</td><td><div style="word-wrap: break-word;"><b>ECC Accelerator DMA Enable Control
</b><br>
0 = ECC DMA engine Disabled.
<br>
1 = ECC DMA engine Enabled.
<br>
Only when START and DMAEN are 1, ECC DMA engine will be active
<br>
</div></td></tr><tr><td>
[8]</td><td>FSEL</td><td><div style="word-wrap: break-word;"><b>Field Selection
</b><br>
0 = Binary Field (GF(2^m)).
<br>
1 = Prime Field (GF(p)).
<br>
</div></td></tr><tr><td>
[10:9]</td><td>ECCOP</td><td><div style="word-wrap: break-word;"><b>Point Operation for BF and PF
</b><br>
00 = Point multiplication :.
<br>
(POINTX1, POINTY1) = SCALARK * (POINTX1, POINTY1).
<br>
01 = Modulus operation : choose by MODOP (CRPT_ECC_CTL[12:11]).
<br>
10 = Point addition :.
<br>
(POINTX1, POINTY1) = (POINTX1, POINTY1) +.
<br>
(POINTX2, POINTY2)
<br>
11 = Point doubling :.
<br>
(POINTX1, POINTY1) = 2 * (POINTX1, POINTY1).
<br>
Besides above three input data, point operations still need the parameters of elliptic curve (CURVEA, CURVEB, CURVEN and CURVEM) as shown in Figure 6.27-11
<br>
</div></td></tr><tr><td>
[12:11]</td><td>MODOP</td><td><div style="word-wrap: break-word;"><b>Modulus Operation for PF
</b><br>
00 = Division :.
<br>
POINTX1 = (POINTY1 / POINTX1) % CURVEN.
<br>
01 = Multiplication :.
<br>
POINTX1 = (POINTX1 * POINTY1) % CURVEN.
<br>
10 = Addition :.
<br>
POINTX1 = (POINTX1 + POINTY1) % CURVEN.
<br>
11 = Subtraction :.
<br>
POINTX1 = (POINTX1 - POINTY1) % CURVEN.
<br>
MODOP is active only when ECCOP = 01.
<br>
</div></td></tr><tr><td>
[16]</td><td>LDP1</td><td><div style="word-wrap: break-word;"><b>The Control Signal of Register for the X and Y Coordinate of the First Point (POINTX1, POINTY1)
</b><br>
0 = The register for POINTX1 and POINTY1 is not modified by DMA or user.
<br>
1 = The register for POINTX1 and POINTY1 is modified by DMA or user.
<br>
</div></td></tr><tr><td>
[17]</td><td>LDP2</td><td><div style="word-wrap: break-word;"><b>The Control Signal of Register for the X and Y Coordinate of the Second Point (POINTX2, POINTY2)
</b><br>
0 = The register for POINTX2 and POINTY2 is not modified by DMA or user.
<br>
1 = The register for POINTX2 and POINTY2 is modified by DMA or user.
<br>
</div></td></tr><tr><td>
[18]</td><td>LDA</td><td><div style="word-wrap: break-word;"><b>The Control Signal of Register for the Parameter CURVEA of Elliptic Curve
</b><br>
0 = The register for CURVEA is not modified by DMA or user.
<br>
1 = The register for CURVEA is modified by DMA or user.
<br>
</div></td></tr><tr><td>
[19]</td><td>LDB</td><td><div style="word-wrap: break-word;"><b>The Control Signal of Register for the Parameter CURVEB of Elliptic Curve
</b><br>
0 = The register for CURVEB is not modified by DMA or user.
<br>
1 = The register for CURVEB is modified by DMA or user.
<br>
</div></td></tr><tr><td>
[20]</td><td>LDN</td><td><div style="word-wrap: break-word;"><b>The Control Signal of Register for the Parameter CURVEN of Elliptic Curve
</b><br>
0 = The register for CURVEN is not modified by DMA or user.
<br>
1 = The register for CURVEN is modified by DMA or user.
<br>
</div></td></tr><tr><td>
[21]</td><td>LDK</td><td><div style="word-wrap: break-word;"><b>The Control Signal of Register for SCALARK
</b><br>
0 = The register for SCALARK is not modified by DMA or user.
<br>
1 = The register for SCALARK is modified by DMA or user.
<br>
</div></td></tr><tr><td>
[31:22]</td><td>CURVEM</td><td><div style="word-wrap: break-word;"><b>The key length of elliptic curve.
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::ECC_STS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ECC_STS
</font><br><p> <font size="2">
Offset: 0x804  ECC Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BUSY</td><td><div style="word-wrap: break-word;"><b>ECC Accelerator Busy Flag
</b><br>
0 = The ECC accelerator is idle or finished.
<br>
1 = The ECC accelerator is under processing and protects all registers.
<br>
Remember to clear ECC interrupt flag after ECC accelerator finished
<br>
</div></td></tr><tr><td>
[1]</td><td>DMABUSY</td><td><div style="word-wrap: break-word;"><b>ECC DMA Busy Flag
</b><br>
0 = ECC DMA is idle or finished.
<br>
1 = ECC DMA is busy.
<br>
</div></td></tr><tr><td>
[16]</td><td>BUSERR</td><td><div style="word-wrap: break-word;"><b>ECC DMA Access Bus Error Flag
</b><br>
0 = No error.
<br>
1 = Bus error will stop DMA operation and ECC accelerator.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::ECC_X1[18]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ECC_X1[18]
</font><br><p> <font size="2">
Offset: 0x808 ~ 0x84C  ECC The X-coordinate word 0 ~ 17 of the first point
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>POINTX1</td><td><div style="word-wrap: break-word;"><b>ECC the x-coordinate Value of the First Point (POINTX1)
</b><br>
For B-163 or K-163, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
<br>
For B-233 or K-233, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
<br>
For B-283 or K-283, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_08
<br>
For B-409 or K-409, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_12
<br>
For B-571 or K-571, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_17
<br>
For P-192, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_05
<br>
For P-224, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_06
<br>
For P-256, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_07
<br>
For P-384, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_11
<br>
For P-521, POINTX1 is stored in CRPT_ECC_X1_00~CRPT_ECC_X1_16
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::ECC_Y1[18]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ECC_Y1[18]
</font><br><p> <font size="2">
Offset: 0x850 ~ 0x894  ECC The Y-coordinate word 0 ~ 17 of the first point
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>POINTY1</td><td><div style="word-wrap: break-word;"><b>ECC the Y-coordinate Value of the First Point (POINTY1)
</b><br>
For B-163 or K-163, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
<br>
For B-233 or K-233, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
<br>
For B-283 or K-283, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_08
<br>
For B-409 or K-409, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_12
<br>
For B-571 or K-571, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_17
<br>
For P-192, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_05
<br>
For P-224, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_06
<br>
For P-256, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_07
<br>
For P-384, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_11
<br>
For P-521, POINTY1 is stored in CRPT_ECC_Y1_00~CRPT_ECC_Y1_16
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::ECC_X2[18]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ECC_X2[18]
</font><br><p> <font size="2">
Offset: 0x898 ~ 0x8DC  ECC The X-coordinate word 0 ~ 17 of the second point
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>POINTX2</td><td><div style="word-wrap: break-word;"><b>ECC the x-coordinate Value of the Second Point (POINTX2)
</b><br>
For B-163 or K-163, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
<br>
For B-233 or K-233, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
<br>
For B-283 or K-283, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_08
<br>
For B-409 or K-409, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_12
<br>
For B-571 or K-571, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_17
<br>
For P-192, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_05
<br>
For P-224, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_06
<br>
For P-256, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_07
<br>
For P-384, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_11
<br>
For P-521, POINTX2 is stored in CRPT_ECC_X2_00~CRPT_ECC_X2_16
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::ECC_Y2[18]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ECC_Y2[18]
</font><br><p> <font size="2">
Offset: 0x8E0 ~ 0x924  ECC The Y-coordinate word 0 ~ 17 of the second point
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>POINTY2</td><td><div style="word-wrap: break-word;"><b>ECC the Y-coordinate Value of the Second Point (POINTY2)
</b><br>
For B-163 or K-163, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
<br>
For B-233 or K-233, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
<br>
For B-283 or K-283, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_08
<br>
For B-409 or K-409, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_12
<br>
For B-571 or K-571, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_17
<br>
For P-192, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_05
<br>
For P-224, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_06
<br>
For P-256, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_07
<br>
For P-384, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_11
<br>
For P-521, POINTY2 is stored in CRPT_ECC_Y2_00~CRPT_ECC_Y2_16
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::ECC_A[18]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ECC_A[18]
</font><br><p> <font size="2">
Offset: 0x928 ~ 0x96C  ECC The parameter CURVEA word 0 ~ 17 of elliptic curve
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>CURVEA</td><td><div style="word-wrap: break-word;"><b>ECC the Parameter CURVEA Value of Elliptic Curve (CURVEA)
</b><br>
The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2^m).
<br>
For B-163 or K-163, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
<br>
For B-233 or K-233, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
<br>
For B-283 or K-283, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_08
<br>
For B-409 or K-409, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_12
<br>
For B-571 or K-571, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_17
<br>
For P-192, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_05
<br>
For P-224, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_06
<br>
For P-256, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_07
<br>
For P-384, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_11
<br>
For P-521, CURVEA is stored in CRPT_ECC_A_00~CRPT_ECC_A_16
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::ECC_B[18]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ECC_B[18]
</font><br><p> <font size="2">
Offset: 0x970 ~ 0x9B4  ECC The parameter CURVEB word 0 ~ 17 of elliptic curve
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>CURVEB</td><td><div style="word-wrap: break-word;"><b>ECC the Parameter CURVEB Value of Elliptic Curve (CURVEA)
</b><br>
The formula of elliptic curve is y2=x3+CURVEA*x+CURVEB in GF(p) and y2+x*y=x3+CURVEA*x2+CURVEB in GF(2^m).
<br>
For B-163 or K-163, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
<br>
For B-233 or K-233, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
<br>
For B-283 or K-283, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_08
<br>
For B-409 or K-409, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_12
<br>
For B-521 or K-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_17
<br>
For P-192, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_05
<br>
For P-224, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_06
<br>
For P-256, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_07
<br>
For P-384, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_11
<br>
For P-521, CURVEB is stored in CRPT_ECC_B_00~CRPT_ECC_B_16
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::ECC_N[18]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ECC_N[18]
</font><br><p> <font size="2">
Offset: 0x9B8 ~ 0x9FC  ECC The parameter CURVEN word 0 ~ 17 of elliptic curve
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>CURVEN</td><td><div style="word-wrap: break-word;"><b>ECC the Parameter CURVEN Value of Elliptic Curve (CURVEN)
</b><br>
In GF(p), CURVEN is the prime p.
<br>
In GF(2^m), CURVEN is the irreducible polynomial.
<br>
For B-163 or K-163, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
<br>
For B-233 or K-233, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
<br>
For B-283 or K-283, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_08
<br>
For B-409 or K-409, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_12
<br>
For B-571 or K-571, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_17
<br>
For P-192, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_05
<br>
For P-224, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_06
<br>
For P-256, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_07
<br>
For P-384, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_11
<br>
For P-521, CURVEN is stored in CRPT_ECC_N_00~CRPT_ECC_N_16
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::ECC_K[18]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ECC_K[18]
</font><br><p> <font size="2">
Offset: 0xA00 ~ 0xA44  ECC The scalar SCALARK word0 of point multiplication
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SCALARK</td><td><div style="word-wrap: break-word;"><b>ECC the Scalar SCALARK Value of Point Multiplication(SCALARK)
</b><br>
Because the SCALARK usually stores the private key, ECC accelerator do not allow to read the register SCALARK.
<br>
For B-163 or K-163, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
<br>
For B-233 or K-233, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
<br>
For B-283 or K-283, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_08
<br>
For B-409 or K-409, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_12
<br>
For B-571 or K-571, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_17
<br>
For P-192, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_05
<br>
For P-224, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_06
<br>
For P-256, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_07
<br>
For P-384, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_11
<br>
For P-521, SCALARK is stored in CRPT_ECC_K_00~CRPT_ECC_K_16
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::ECC_SADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ECC_SADDR
</font><br><p> <font size="2">
Offset: 0xA48  ECC DMA Source Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SADDR</td><td><div style="word-wrap: break-word;"><b>ECC DMA Source Address
</b><br>
The ECC accelerator supports DMA function to transfer the DATA and PARAMETER between
<br>
SRAM memory space and ECC accelerator. The SADDR keeps the source address of the data
<br>
buffer where the source text is stored. Based on the source address, the ECC accelerator
<br>
can read the DATA and PARAMETER from SRAM memory space and do ECC operation. The start
<br>
of source address should be located at word boundary. That is, bit 1 and 0 of SADDR are
<br>
ignored. SADDR can be read and written. In DMA mode, software must update the CRPT_ECC_SADDR
<br>
before triggering START.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::ECC_DADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ECC_DADDR
</font><br><p> <font size="2">
Offset: 0xA4C  ECC DMA Destination Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DADDR</td><td><div style="word-wrap: break-word;"><b>ECC DMA Destination Address
</b><br>
The ECC accelerator supports DMA function to transfer the DATA and PARAMETER between system memory and ECC accelerator
<br>
The DADDR keeps the destination address of the data buffer where output data of ECC engine will be stored
<br>
Based on the destination address, the ECC accelerator can write the result data back to system memory after the ECC operation is finished
<br>
The start of destination address should be located at word boundary
<br>
That is, bit 1 and 0 of DADDR are ignored
<br>
DADDR can be read and written
<br>
In DMA mode, software must update the CRPT_ECC_DADDR before triggering START
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::ECC_STARTREG

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ECC_STARTREG
</font><br><p> <font size="2">
Offset: 0xA50  ECC Starting Address of Updated Registers
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>STARTREG</td><td><div style="word-wrap: break-word;"><b>ECC Starting Address of Updated Registers
</b><br>
The address of the updated registers that DMA feeds the first data or parameter to ECC engine
<br>
When ECC engine is active, ECC accelerator does not allow users to modify STARTREG
<br>
For example, we want to updated input data from register CRPT_ECC POINTX1
<br>
Thus, the value of STARTREG is 0x808.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRPT_T::ECC_WORDCNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ECC_WORDCNT
</font><br><p> <font size="2">
Offset: 0xA54  ECC DMA Word Count
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>WORDCNT</td><td><div style="word-wrap: break-word;"><b>ECC DMA Word Count
</b><br>
The CRPT_ECC_WORDCNT keeps the word count of source data that is for the required input data of ECC accelerator with various operations in DMA mode
<br>
Although CRPT_ECC_WORDCNT is 32-bit, the maximum of word count in ECC accelerator is 144 words
<br>
CRPT_ECC_WORDCNT can be read and written
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t INTEN;                 /*!< [0x0000] Crypto Interrupt Enable Control Register                         */
    __IO uint32_t INTSTS;                /*!< [0x0004] Crypto Interrupt Flag                                            */
    __IO uint32_t PRNG_CTL;              /*!< [0x0008] PRNG Control Register                                            */
    __O  uint32_t PRNG_SEED;             /*!< [0x000c] Seed for PRNG                                                    */
    __I  uint32_t PRNG_KEY[8];           /*!< [0x0010] ~ [0x002c] PRNG Generated Key0 ~ Key7                            */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[8];
    /// @endcond //HIDDEN_SYMBOLS
    __I  uint32_t AES_FDBCK[4];          /*!< [0x0050] ~ [0x005c] AES Engine Output Feedback Data after Cryptographic Operation     */
    __I  uint32_t TDES_FDBCKH;           /*!< [0x0060] TDES/DES Engine Output Feedback High Word Data after Cryptographic Operation */
    __I  uint32_t TDES_FDBCKL;           /*!< [0x0064] TDES/DES Engine Output Feedback Low Word Data after Cryptographic Operation  */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[38];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t AES_CTL;               /*!< [0x0100] AES Control Register                                             */
    __I  uint32_t AES_STS;               /*!< [0x0104] AES Engine Flag                                                  */
    __IO uint32_t AES_DATIN;             /*!< [0x0108] AES Engine Data Input Port Register                              */
    __I  uint32_t AES_DATOUT;            /*!< [0x010c] AES Engine Data Output Port Register                             */
    __IO uint32_t AES0_KEY[8];           /*!< [0x0110] ~ [0x012c] AES Key Word 0~7 Register for Channel 0               */
    __IO uint32_t AES0_IV[4];            /*!< [0x0130] ~ [0x013c] AES Initial Vector Word 0 ~ 3 Register for Channel 0  */
    __IO uint32_t AES0_SADDR;            /*!< [0x0140] AES DMA Source Address Register for Channel 0                    */
    __IO uint32_t AES0_DADDR;            /*!< [0x0144] AES DMA Destination Address Register for Channel 0               */
    __IO uint32_t AES0_CNT;              /*!< [0x0148] AES Byte Count Register for Channel 0                            */
    __IO uint32_t AES1_KEY[8];           /*!< [0x014c] ~ [0x0168] AES Key Word 0~7 Register for Channel 1               */
    __IO uint32_t AES1_IV[4];            /*!< [0x016c] ~ [0x0178] AES Initial Vector Word 0~3 Register for Channel 1    */
    __IO uint32_t AES1_SADDR;            /*!< [0x017c] AES DMA Source Address Register for Channel 1                    */
    __IO uint32_t AES1_DADDR;            /*!< [0x0180] AES DMA Destination Address Register for Channel 1               */
    __IO uint32_t AES1_CNT;              /*!< [0x0184] AES Byte Count Register for Channel 1                            */
    __IO uint32_t AES2_KEY[8];           /*!< [0x0188] ~ [0x01a4] AES Key Word 0~7 Register for Channel 2               */
    __IO uint32_t AES2_IV[4];            /*!< [0x01a8] ~ [0x01b4] AES Initial Vector Word 0~3 Register for Channel 2    */
    __IO uint32_t AES2_SADDR;            /*!< [0x01b8] AES DMA Source Address Register for Channel 2                    */
    __IO uint32_t AES2_DADDR;            /*!< [0x01bc] AES DMA Destination Address Register for Channel 2               */
    __IO uint32_t AES2_CNT;              /*!< [0x01c0] AES Byte Count Register for Channel 2                            */
    __IO uint32_t AES3_KEY[8];           /*!< [0x01c4] ~ [0x01e0] AES Key Word 0~7 Register for Channel 3               */
    __IO uint32_t AES3_IV[4];            /*!< [0x01e4] ~ [0x01f0] AES Initial Vector Word 0~3 Register for Channel 3    */
    __IO uint32_t AES3_SADDR;            /*!< [0x01f4] AES DMA Source Address Register for Channel 3                    */
    __IO uint32_t AES3_DADDR;            /*!< [0x01f8] AES DMA Destination Address Register for Channel 3               */
    __IO uint32_t AES3_CNT;              /*!< [0x01fc] AES Byte Count Register for Channel 3                            */
    __IO uint32_t TDES_CTL;              /*!< [0x0200] TDES/DES Control Register                                        */
    __I  uint32_t TDES_STS;              /*!< [0x0204] TDES/DES Engine Flag                                             */
    __IO uint32_t TDES0_KEY1H;           /*!< [0x0208] TDES/DES Key 1 High Word Register for Channel 0                  */
    __IO uint32_t TDES0_KEY1L;           /*!< [0x020c] TDES/DES Key 1 Low Word Register for Channel 0                   */
    __IO uint32_t TDES0_KEY2H;           /*!< [0x0210] TDES Key 2 High Word Register for Channel 0                      */
    __IO uint32_t TDES0_KEY2L;           /*!< [0x0214] TDES Key 2 Low Word Register for Channel 0                       */
    __IO uint32_t TDES0_KEY3H;           /*!< [0x0218] TDES Key 3 High Word Register for Channel 0                      */
    __IO uint32_t TDES0_KEY3L;           /*!< [0x021c] TDES Key 3 Low Word Register for Channel 0                       */
    __IO uint32_t TDES0_IVH;             /*!< [0x0220] TDES/DES Initial Vector High Word Register for Channel 0         */
    __IO uint32_t TDES0_IVL;             /*!< [0x0224] TDES/DES Initial Vector Low Word Register for Channel 0          */
    __IO uint32_t TDES0_SA;              /*!< [0x0228] TDES/DES DMA Source Address Register for Channel 0               */
    __IO uint32_t TDES0_DA;              /*!< [0x022c] TDES/DES DMA Destination Address Register for Channel 0          */
    __IO uint32_t TDES0_CNT;             /*!< [0x0230] TDES/DES Byte Count Register for Channel 0                       */
    __IO uint32_t TDES_DATIN;            /*!< [0x0234] TDES/DES Engine Input data Word Register                         */
    __I  uint32_t TDES_DATOUT;           /*!< [0x0238] TDES/DES Engine Output data Word Register                        */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE2[3];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t TDES1_KEY1H;           /*!< [0x0248] TDES/DES Key 1 High Word Register for Channel 1                  */
    __IO uint32_t TDES1_KEY1L;           /*!< [0x024c] TDES/DES Key 1 Low Word Register for Channel 1                   */
    __IO uint32_t TDES1_KEY2H;           /*!< [0x0250] TDES Key 2 High Word Register for Channel 1                      */
    __IO uint32_t TDES1_KEY2L;           /*!< [0x0254] TDES Key 2 Low Word Register for Channel 1                       */
    __IO uint32_t TDES1_KEY3H;           /*!< [0x0258] TDES Key 3 High Word Register for Channel 1                      */
    __IO uint32_t TDES1_KEY3L;           /*!< [0x025c] TDES Key 3 Low Word Register for Channel 1                       */
    __IO uint32_t TDES1_IVH;             /*!< [0x0260] TDES/DES Initial Vector High Word Register for Channel 1         */
    __IO uint32_t TDES1_IVL;             /*!< [0x0264] TDES/DES Initial Vector Low Word Register for Channel 1          */
    __IO uint32_t TDES1_SA;              /*!< [0x0268] TDES/DES DMA Source Address Register for Channel 1               */
    __IO uint32_t TDES1_DA;              /*!< [0x026c] TDES/DES DMA Destination Address Register for Channel 1          */
    __IO uint32_t TDES1_CNT;             /*!< [0x0270] TDES/DES Byte Count Register for Channel 1                       */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE3[5];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t TDES2_KEY1H;           /*!< [0x0288] TDES/DES Key 1 High Word Register for Channel 2                  */
    __IO uint32_t TDES2_KEY1L;           /*!< [0x028c] TDES/DES Key 1 Low Word Register for Channel 2                   */
    __IO uint32_t TDES2_KEY2H;           /*!< [0x0290] TDES Key 2 High Word Register for Channel 2                      */
    __IO uint32_t TDES2_KEY2L;           /*!< [0x0294] TDES Key 2 Low Word Register for Channel 2                       */
    __IO uint32_t TDES2_KEY3H;           /*!< [0x0298] TDES Key 3 High Word Register for Channel 2                      */
    __IO uint32_t TDES2_KEY3L;           /*!< [0x029c] TDES Key 3 Low Word Register for Channel 2                       */
    __IO uint32_t TDES2_IVH;             /*!< [0x02a0] TDES/DES Initial Vector High Word Register for Channel 2         */
    __IO uint32_t TDES2_IVL;             /*!< [0x02a4] TDES/DES Initial Vector Low Word Register for Channel 2          */
    __IO uint32_t TDES2_SA;              /*!< [0x02a8] TDES/DES DMA Source Address Register for Channel 2               */
    __IO uint32_t TDES2_DA;              /*!< [0x02ac] TDES/DES DMA Destination Address Register for Channel 2          */
    __IO uint32_t TDES2_CNT;             /*!< [0x02b0] TDES/DES Byte Count Register for Channel 2                       */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE4[5];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t TDES3_KEY1H;           /*!< [0x02c8] TDES/DES Key 1 High Word Register for Channel 3                  */
    __IO uint32_t TDES3_KEY1L;           /*!< [0x02cc] TDES/DES Key 1 Low Word Register for Channel 3                   */
    __IO uint32_t TDES3_KEY2H;           /*!< [0x02d0] TDES Key 2 High Word Register for Channel 3                      */
    __IO uint32_t TDES3_KEY2L;           /*!< [0x02d4] TDES Key 2 Low Word Register for Channel 3                       */
    __IO uint32_t TDES3_KEY3H;           /*!< [0x02d8] TDES Key 3 High Word Register for Channel 3                      */
    __IO uint32_t TDES3_KEY3L;           /*!< [0x02dc] TDES Key 3 Low Word Register for Channel 3                       */
    __IO uint32_t TDES3_IVH;             /*!< [0x02e0] TDES/DES Initial Vector High Word Register for Channel 3         */
    __IO uint32_t TDES3_IVL;             /*!< [0x02e4] TDES/DES Initial Vector Low Word Register for Channel 3          */
    __IO uint32_t TDES3_SA;              /*!< [0x02e8] TDES/DES DMA Source Address Register for Channel 3               */
    __IO uint32_t TDES3_DA;              /*!< [0x02ec] TDES/DES DMA Destination Address Register for Channel 3          */
    __IO uint32_t TDES3_CNT;             /*!< [0x02f0] TDES/DES Byte Count Register for Channel 3                       */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE5[3];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t HMAC_CTL;              /*!< [0x0300] SHA/HMAC Control Register                                        */
    __I  uint32_t HMAC_STS;              /*!< [0x0304] SHA/HMAC Status Flag                                             */
    __I  uint32_t HMAC_DGST[16];         /*!< [0x0308] ~ [0x0344] SHA/HMAC Digest Message 0~15                          */
    __IO uint32_t HMAC_KEYCNT;           /*!< [0x0348] SHA/HMAC Key Byte Count Register                                 */
    __IO uint32_t HMAC_SADDR;            /*!< [0x034c] SHA/HMAC DMA Source Address Register                             */
    __IO uint32_t HMAC_DMACNT;           /*!< [0x0350] SHA/HMAC Byte Count Register                                     */
    __IO uint32_t HMAC_DATIN;            /*!< [0x0354] SHA/HMAC Engine Non-DMA Mode Data Input Port Register            */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE6[298];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t ECC_CTL;               /*!< [0x0800] ECC Control Register                                             */
    __I  uint32_t ECC_STS;               /*!< [0x0804] ECC Status Register                                              */
    __IO uint32_t ECC_X1[18];            /*!< [0x0808] ~ [0x084c] ECC The X-coordinate word 0~17 of the first point     */
    __IO uint32_t ECC_Y1[18];            /*!< [0x0850] ~ [0x0894] ECC The Y-coordinate word 0~17 of the first point     */
    __IO uint32_t ECC_X2[18];            /*!< [0x0898] ~ [0x08dc] ECC The X-coordinate word 0~17 of the second point    */
    __IO uint32_t ECC_Y2[18];            /*!< [0x08e0] ~ [0x0924] ECC The Y-coordinate word 0~17 of the second point    */
    __IO uint32_t ECC_A[18];             /*!< [0x0928] ~ [0x096c] ECC The parameter CURVEA word 0~17 of elliptic curve  */
    __IO uint32_t ECC_B[18];             /*!< [0x0970] ~ [0x09b4] ECC The parameter CURVEB word 0~17 of elliptic curve  */
    __IO uint32_t ECC_N[18];             /*!< [0x09b8] ~ [0x09fc] ECC The parameter CURVEN word 0~17 of elliptic curve  */
    __O  uint32_t ECC_K[18];             /*!< [0x0a00] ~ [0x0a44] ECC The scalar SCALARK word 0~17 of point multiplication */
    __IO uint32_t ECC_SADDR;             /*!< [0x0a48] ECC DMA Source Address Register                                  */
    __IO uint32_t ECC_DADDR;             /*!< [0x0a4c] ECC DMA Destination Address Register                             */
    __IO uint32_t ECC_STARTREG;          /*!< [0x0a50] ECC Starting Address of Updated Registers                        */
    __IO uint32_t ECC_WORDCNT;           /*!< [0x0a54] ECC DMA Word Count                                               */

} CRPT_T;

/**
    @addtogroup CRPT_CONST CRPT Bit Field Definition
    Constant Definitions for CRPT Controller
@{ */

#define CRPT_INTEN_AESIEN_Pos            (0)                                               /*!< CRPT_T::INTEN: AESIEN Position         */
#define CRPT_INTEN_AESIEN_Msk            (0x1ul << CRPT_INTEN_AESIEN_Pos)                  /*!< CRPT_T::INTEN: AESIEN Mask             */

#define CRPT_INTEN_AESEIEN_Pos           (1)                                               /*!< CRPT_T::INTEN: AESEIEN Position        */
#define CRPT_INTEN_AESEIEN_Msk           (0x1ul << CRPT_INTEN_AESEIEN_Pos)                 /*!< CRPT_T::INTEN: AESEIEN Mask            */

#define CRPT_INTEN_TDESIEN_Pos           (8)                                               /*!< CRPT_T::INTEN: TDESIEN Position        */
#define CRPT_INTEN_TDESIEN_Msk           (0x1ul << CRPT_INTEN_TDESIEN_Pos)                 /*!< CRPT_T::INTEN: TDESIEN Mask            */

#define CRPT_INTEN_TDESEIEN_Pos          (9)                                               /*!< CRPT_T::INTEN: TDESEIEN Position       */
#define CRPT_INTEN_TDESEIEN_Msk          (0x1ul << CRPT_INTEN_TDESEIEN_Pos)                /*!< CRPT_T::INTEN: TDESEIEN Mask           */

#define CRPT_INTEN_PRNGIEN_Pos           (16)                                              /*!< CRPT_T::INTEN: PRNGIEN Position        */
#define CRPT_INTEN_PRNGIEN_Msk           (0x1ul << CRPT_INTEN_PRNGIEN_Pos)                 /*!< CRPT_T::INTEN: PRNGIEN Mask            */

#define CRPT_INTEN_ECCIEN_Pos            (22)                                              /*!< CRPT_T::INTEN: ECCIEN Position         */
#define CRPT_INTEN_ECCIEN_Msk            (0x1ul << CRPT_INTEN_ECCIEN_Pos)                  /*!< CRPT_T::INTEN: ECCIEN Mask             */

#define CRPT_INTEN_ECCEIEN_Pos           (23)                                              /*!< CRPT_T::INTEN: ECCEIEN Position        */
#define CRPT_INTEN_ECCEIEN_Msk           (0x1ul << CRPT_INTEN_ECCEIEN_Pos)                 /*!< CRPT_T::INTEN: ECCEIEN Mask            */

#define CRPT_INTEN_HMACIEN_Pos           (24)                                              /*!< CRPT_T::INTEN: HMACIEN Position        */
#define CRPT_INTEN_HMACIEN_Msk           (0x1ul << CRPT_INTEN_HMACIEN_Pos)                 /*!< CRPT_T::INTEN: HMACIEN Mask            */

#define CRPT_INTEN_HMACEIEN_Pos          (25)                                              /*!< CRPT_T::INTEN: HMACEIEN Position       */
#define CRPT_INTEN_HMACEIEN_Msk          (0x1ul << CRPT_INTEN_HMACEIEN_Pos)                /*!< CRPT_T::INTEN: HMACEIEN Mask           */

#define CRPT_INTSTS_AESIF_Pos            (0)                                               /*!< CRPT_T::INTSTS: AESIF Position         */
#define CRPT_INTSTS_AESIF_Msk            (0x1ul << CRPT_INTSTS_AESIF_Pos)                  /*!< CRPT_T::INTSTS: AESIF Mask             */

#define CRPT_INTSTS_AESEIF_Pos           (1)                                               /*!< CRPT_T::INTSTS: AESEIF Position        */
#define CRPT_INTSTS_AESEIF_Msk           (0x1ul << CRPT_INTSTS_AESEIF_Pos)                 /*!< CRPT_T::INTSTS: AESEIF Mask            */

#define CRPT_INTSTS_TDESIF_Pos           (8)                                               /*!< CRPT_T::INTSTS: TDESIF Position        */
#define CRPT_INTSTS_TDESIF_Msk           (0x1ul << CRPT_INTSTS_TDESIF_Pos)                 /*!< CRPT_T::INTSTS: TDESIF Mask            */

#define CRPT_INTSTS_TDESEIF_Pos          (9)                                               /*!< CRPT_T::INTSTS: TDESEIF Position       */
#define CRPT_INTSTS_TDESEIF_Msk          (0x1ul << CRPT_INTSTS_TDESEIF_Pos)                /*!< CRPT_T::INTSTS: TDESEIF Mask           */

#define CRPT_INTSTS_PRNGIF_Pos           (16)                                              /*!< CRPT_T::INTSTS: PRNGIF Position        */
#define CRPT_INTSTS_PRNGIF_Msk           (0x1ul << CRPT_INTSTS_PRNGIF_Pos)                 /*!< CRPT_T::INTSTS: PRNGIF Mask            */

#define CRPT_INTSTS_ECCIF_Pos            (22)                                              /*!< CRPT_T::INTSTS: ECCIF Position         */
#define CRPT_INTSTS_ECCIF_Msk            (0x1ul << CRPT_INTSTS_ECCIF_Pos)                  /*!< CRPT_T::INTSTS: ECCIF Mask             */

#define CRPT_INTSTS_ECCEIF_Pos           (23)                                              /*!< CRPT_T::INTSTS: ECCEIF Position        */
#define CRPT_INTSTS_ECCEIF_Msk           (0x1ul << CRPT_INTSTS_ECCEIF_Pos)                 /*!< CRPT_T::INTSTS: ECCEIF Mask            */

#define CRPT_INTSTS_HMACIF_Pos           (24)                                              /*!< CRPT_T::INTSTS: HMACIF Position        */
#define CRPT_INTSTS_HMACIF_Msk           (0x1ul << CRPT_INTSTS_HMACIF_Pos)                 /*!< CRPT_T::INTSTS: HMACIF Mask            */

#define CRPT_INTSTS_HMACEIF_Pos          (25)                                              /*!< CRPT_T::INTSTS: HMACEIF Position       */
#define CRPT_INTSTS_HMACEIF_Msk          (0x1ul << CRPT_INTSTS_HMACEIF_Pos)                /*!< CRPT_T::INTSTS: HMACEIF Mask           */

#define CRPT_PRNG_CTL_START_Pos          (0)                                               /*!< CRPT_T::PRNG_CTL: START Position       */
#define CRPT_PRNG_CTL_START_Msk          (0x1ul << CRPT_PRNG_CTL_START_Pos)                /*!< CRPT_T::PRNG_CTL: START Mask           */

#define CRPT_PRNG_CTL_SEEDRLD_Pos        (1)                                               /*!< CRPT_T::PRNG_CTL: SEEDRLD Position     */
#define CRPT_PRNG_CTL_SEEDRLD_Msk        (0x1ul << CRPT_PRNG_CTL_SEEDRLD_Pos)              /*!< CRPT_T::PRNG_CTL: SEEDRLD Mask         */

#define CRPT_PRNG_CTL_KEYSZ_Pos          (2)                                               /*!< CRPT_T::PRNG_CTL: KEYSZ Position       */
#define CRPT_PRNG_CTL_KEYSZ_Msk          (0x3ul << CRPT_PRNG_CTL_KEYSZ_Pos)                /*!< CRPT_T::PRNG_CTL: KEYSZ Mask           */

#define CRPT_PRNG_CTL_BUSY_Pos           (8)                                               /*!< CRPT_T::PRNG_CTL: BUSY Position        */
#define CRPT_PRNG_CTL_BUSY_Msk           (0x1ul << CRPT_PRNG_CTL_BUSY_Pos)                 /*!< CRPT_T::PRNG_CTL: BUSY Mask            */

#define CRPT_PRNG_SEED_SEED_Pos          (0)                                               /*!< CRPT_T::PRNG_SEED: SEED Position       */
#define CRPT_PRNG_SEED_SEED_Msk          (0xfffffffful << CRPT_PRNG_SEED_SEED_Pos)         /*!< CRPT_T::PRNG_SEED: SEED Mask           */

#define CRPT_PRNG_KEYx_KEY_Pos           (0)                                               /*!< CRPT_T::PRNG_KEY[8]: KEY Position      */
#define CRPT_PRNG_KEYx_KEY_Msk           (0xfffffffful << CRPT_PRNG_KEYx_KEY_Pos)          /*!< CRPT_T::PRNG_KEY[8]: KEY Mask          */

#define CRPT_AES_FDBCKx_FDBCK_Pos        (0)                                               /*!< CRPT_T::AES_FDBCK[4]: FDBCK Position   */
#define CRPT_AES_FDBCKx_FDBCK_Msk        (0xfffffffful << CRPT_AES_FDBCKx_FDBCK_Pos)       /*!< CRPT_T::AES_FDBCK[4]: FDBCK Mask       */

#define CRPT_TDES_FDBCKH_FDBCK_Pos       (0)                                               /*!< CRPT_T::TDES_FDBCKH: FDBCK Position    */
#define CRPT_TDES_FDBCKH_FDBCK_Msk       (0xfffffffful << CRPT_TDES_FDBCKH_FDBCK_Pos)      /*!< CRPT_T::TDES_FDBCKH: FDBCK Mask        */

#define CRPT_TDES_FDBCKL_FDBCK_Pos       (0)                                               /*!< CRPT_T::TDES_FDBCKL: FDBCK Position    */
#define CRPT_TDES_FDBCKL_FDBCK_Msk       (0xfffffffful << CRPT_TDES_FDBCKL_FDBCK_Pos)      /*!< CRPT_T::TDES_FDBCKL: FDBCK Mask        */

#define CRPT_AES_CTL_START_Pos           (0)                                               /*!< CRPT_T::AES_CTL: START Position        */
#define CRPT_AES_CTL_START_Msk           (0x1ul << CRPT_AES_CTL_START_Pos)                 /*!< CRPT_T::AES_CTL: START Mask            */

#define CRPT_AES_CTL_STOP_Pos            (1)                                               /*!< CRPT_T::AES_CTL: STOP Position         */
#define CRPT_AES_CTL_STOP_Msk            (0x1ul << CRPT_AES_CTL_STOP_Pos)                  /*!< CRPT_T::AES_CTL: STOP Mask             */

#define CRPT_AES_CTL_KEYSZ_Pos           (2)                                               /*!< CRPT_T::AES_CTL: KEYSZ Position        */
#define CRPT_AES_CTL_KEYSZ_Msk           (0x3ul << CRPT_AES_CTL_KEYSZ_Pos)                 /*!< CRPT_T::AES_CTL: KEYSZ Mask            */

#define CRPT_AES_CTL_DMALAST_Pos         (5)                                               /*!< CRPT_T::AES_CTL: DMALAST Position      */
#define CRPT_AES_CTL_DMALAST_Msk         (0x1ul << CRPT_AES_CTL_DMALAST_Pos)               /*!< CRPT_T::AES_CTL: DMALAST Mask          */

#define CRPT_AES_CTL_DMACSCAD_Pos        (6)                                               /*!< CRPT_T::AES_CTL: DMACSCAD Position     */
#define CRPT_AES_CTL_DMACSCAD_Msk        (0x1ul << CRPT_AES_CTL_DMACSCAD_Pos)              /*!< CRPT_T::AES_CTL: DMACSCAD Mask         */

#define CRPT_AES_CTL_DMAEN_Pos           (7)                                               /*!< CRPT_T::AES_CTL: DMAEN Position        */
#define CRPT_AES_CTL_DMAEN_Msk           (0x1ul << CRPT_AES_CTL_DMAEN_Pos)                 /*!< CRPT_T::AES_CTL: DMAEN Mask            */

#define CRPT_AES_CTL_OPMODE_Pos          (8)                                               /*!< CRPT_T::AES_CTL: OPMODE Position       */
#define CRPT_AES_CTL_OPMODE_Msk          (0xfful << CRPT_AES_CTL_OPMODE_Pos)               /*!< CRPT_T::AES_CTL: OPMODE Mask           */

#define CRPT_AES_CTL_ENCRPT_Pos          (16)                                              /*!< CRPT_T::AES_CTL: ENCRPT Position       */
#define CRPT_AES_CTL_ENCRPT_Msk          (0x1ul << CRPT_AES_CTL_ENCRPT_Pos)                /*!< CRPT_T::AES_CTL: ENCRPT Mask           */

#define CRPT_AES_CTL_OUTSWAP_Pos         (22)                                              /*!< CRPT_T::AES_CTL: OUTSWAP Position      */
#define CRPT_AES_CTL_OUTSWAP_Msk         (0x1ul << CRPT_AES_CTL_OUTSWAP_Pos)               /*!< CRPT_T::AES_CTL: OUTSWAP Mask          */

#define CRPT_AES_CTL_INSWAP_Pos          (23)                                              /*!< CRPT_T::AES_CTL: INSWAP Position       */
#define CRPT_AES_CTL_INSWAP_Msk          (0x1ul << CRPT_AES_CTL_INSWAP_Pos)                /*!< CRPT_T::AES_CTL: INSWAP Mask           */

#define CRPT_AES_CTL_CHANNEL_Pos         (24)                                              /*!< CRPT_T::AES_CTL: CHANNEL Position      */
#define CRPT_AES_CTL_CHANNEL_Msk         (0x3ul << CRPT_AES_CTL_CHANNEL_Pos)               /*!< CRPT_T::AES_CTL: CHANNEL Mask          */

#define CRPT_AES_CTL_KEYUNPRT_Pos        (26)                                              /*!< CRPT_T::AES_CTL: KEYUNPRT Position     */
#define CRPT_AES_CTL_KEYUNPRT_Msk        (0x1ful << CRPT_AES_CTL_KEYUNPRT_Pos)             /*!< CRPT_T::AES_CTL: KEYUNPRT Mask         */

#define CRPT_AES_CTL_KEYPRT_Pos          (31)                                              /*!< CRPT_T::AES_CTL: KEYPRT Position       */
#define CRPT_AES_CTL_KEYPRT_Msk          (0x1ul << CRPT_AES_CTL_KEYPRT_Pos)                /*!< CRPT_T::AES_CTL: KEYPRT Mask           */

#define CRPT_AES_STS_BUSY_Pos            (0)                                               /*!< CRPT_T::AES_STS: BUSY Position         */
#define CRPT_AES_STS_BUSY_Msk            (0x1ul << CRPT_AES_STS_BUSY_Pos)                  /*!< CRPT_T::AES_STS: BUSY Mask             */

#define CRPT_AES_STS_INBUFEMPTY_Pos      (8)                                               /*!< CRPT_T::AES_STS: INBUFEMPTY Position   */
#define CRPT_AES_STS_INBUFEMPTY_Msk      (0x1ul << CRPT_AES_STS_INBUFEMPTY_Pos)            /*!< CRPT_T::AES_STS: INBUFEMPTY Mask       */

#define CRPT_AES_STS_INBUFFULL_Pos       (9)                                               /*!< CRPT_T::AES_STS: INBUFFULL Position    */
#define CRPT_AES_STS_INBUFFULL_Msk       (0x1ul << CRPT_AES_STS_INBUFFULL_Pos)             /*!< CRPT_T::AES_STS: INBUFFULL Mask        */

#define CRPT_AES_STS_INBUFERR_Pos        (10)                                              /*!< CRPT_T::AES_STS: INBUFERR Position     */
#define CRPT_AES_STS_INBUFERR_Msk        (0x1ul << CRPT_AES_STS_INBUFERR_Pos)              /*!< CRPT_T::AES_STS: INBUFERR Mask         */

#define CRPT_AES_STS_CNTERR_Pos          (12)                                              /*!< CRPT_T::AES_STS: CNTERR Position       */
#define CRPT_AES_STS_CNTERR_Msk          (0x1ul << CRPT_AES_STS_CNTERR_Pos)                /*!< CRPT_T::AES_STS: CNTERR Mask           */

#define CRPT_AES_STS_OUTBUFEMPTY_Pos     (16)                                              /*!< CRPT_T::AES_STS: OUTBUFEMPTY Position  */
#define CRPT_AES_STS_OUTBUFEMPTY_Msk     (0x1ul << CRPT_AES_STS_OUTBUFEMPTY_Pos)           /*!< CRPT_T::AES_STS: OUTBUFEMPTY Mask      */

#define CRPT_AES_STS_OUTBUFFULL_Pos      (17)                                              /*!< CRPT_T::AES_STS: OUTBUFFULL Position   */
#define CRPT_AES_STS_OUTBUFFULL_Msk      (0x1ul << CRPT_AES_STS_OUTBUFFULL_Pos)            /*!< CRPT_T::AES_STS: OUTBUFFULL Mask       */

#define CRPT_AES_STS_OUTBUFERR_Pos       (18)                                              /*!< CRPT_T::AES_STS: OUTBUFERR Position    */
#define CRPT_AES_STS_OUTBUFERR_Msk       (0x1ul << CRPT_AES_STS_OUTBUFERR_Pos)             /*!< CRPT_T::AES_STS: OUTBUFERR Mask        */

#define CRPT_AES_STS_BUSERR_Pos          (20)                                              /*!< CRPT_T::AES_STS: BUSERR Position       */
#define CRPT_AES_STS_BUSERR_Msk          (0x1ul << CRPT_AES_STS_BUSERR_Pos)                /*!< CRPT_T::AES_STS: BUSERR Mask           */

#define CRPT_AES_DATIN_DATIN_Pos         (0)                                               /*!< CRPT_T::AES_DATIN: DATIN Position      */
#define CRPT_AES_DATIN_DATIN_Msk         (0xfffffffful << CRPT_AES_DATIN_DATIN_Pos)        /*!< CRPT_T::AES_DATIN: DATIN Mask          */

#define CRPT_AES_DATOUT_DATOUT_Pos       (0)                                               /*!< CRPT_T::AES_DATOUT: DATOUT Position    */
#define CRPT_AES_DATOUT_DATOUT_Msk       (0xfffffffful << CRPT_AES_DATOUT_DATOUT_Pos)      /*!< CRPT_T::AES_DATOUT: DATOUT Mask        */

#define CRPT_AES0_KEYx_KEY_Pos           (0)                                               /*!< CRPT_T::AES0_KEY[8]: KEY Position      */
#define CRPT_AES0_KEYx_KEY_Msk           (0xfffffffful << CRPT_AES0_KEYx_KEY_Pos)          /*!< CRPT_T::AES0_KEY[8]: KEY Mask          */

#define CRPT_AES0_IVx_IV_Pos             (0)                                               /*!< CRPT_T::AES0_IV[4]: IV Position        */
#define CRPT_AES0_IVx_IV_Msk             (0xfffffffful << CRPT_AES0_IVx_IV_Pos)            /*!< CRPT_T::AES0_IV[4]: IV Mask            */

#define CRPT_AES0_SADDR_SADDR_Pos        (0)                                               /*!< CRPT_T::AES0_SADDR: SADDR Position     */
#define CRPT_AES0_SADDR_SADDR_Msk        (0xfffffffful << CRPT_AES0_SADDR_SADDR_Pos)       /*!< CRPT_T::AES0_SADDR: SADDR Mask         */

#define CRPT_AES0_DADDR_DADDR_Pos        (0)                                               /*!< CRPT_T::AES0_DADDR: DADDR Position     */
#define CRPT_AES0_DADDR_DADDR_Msk        (0xfffffffful << CRPT_AES0_DADDR_DADDR_Pos)       /*!< CRPT_T::AES0_DADDR: DADDR Mask         */

#define CRPT_AES0_CNT_CNT_Pos            (0)                                               /*!< CRPT_T::AES0_CNT: CNT Position         */
#define CRPT_AES0_CNT_CNT_Msk            (0xfffffffful << CRPT_AES0_CNT_CNT_Pos)           /*!< CRPT_T::AES0_CNT: CNT Mask             */

#define CRPT_AES1_KEYx_KEY_Pos           (0)                                               /*!< CRPT_T::AES1_KEY[8]: KEY Position      */
#define CRPT_AES1_KEYx_KEY_Msk           (0xfffffffful << CRPT_AES1_KEYx_KEY_Pos)          /*!< CRPT_T::AES1_KEY[8]: KEY Mask          */

#define CRPT_AES1_IVx_IV_Pos             (0)                                               /*!< CRPT_T::AES1_IV[4]: IV Position        */
#define CRPT_AES1_IVx_IV_Msk             (0xfffffffful << CRPT_AES1_IVx_IV_Pos)            /*!< CRPT_T::AES1_IV[4]: IV Mask            */

#define CRPT_AES1_SADDR_SADDR_Pos        (0)                                               /*!< CRPT_T::AES1_SADDR: SADDR Position     */
#define CRPT_AES1_SADDR_SADDR_Msk        (0xfffffffful << CRPT_AES1_SADDR_SADDR_Pos)       /*!< CRPT_T::AES1_SADDR: SADDR Mask         */

#define CRPT_AES1_DADDR_DADDR_Pos        (0)                                               /*!< CRPT_T::AES1_DADDR: DADDR Position     */
#define CRPT_AES1_DADDR_DADDR_Msk        (0xfffffffful << CRPT_AES1_DADDR_DADDR_Pos)       /*!< CRPT_T::AES1_DADDR: DADDR Mask         */

#define CRPT_AES1_CNT_CNT_Pos            (0)                                               /*!< CRPT_T::AES1_CNT: CNT Position         */
#define CRPT_AES1_CNT_CNT_Msk            (0xfffffffful << CRPT_AES1_CNT_CNT_Pos)           /*!< CRPT_T::AES1_CNT: CNT Mask             */

#define CRPT_AES2_KEYx_KEY_Pos           (0)                                               /*!< CRPT_T::AES2_KEY[8]: KEY Position      */
#define CRPT_AES2_KEYx_KEY_Msk           (0xfffffffful << CRPT_AES2_KEYx_KEY_Pos)          /*!< CRPT_T::AES2_KEY[8]: KEY Mask          */

#define CRPT_AES2_IVx_IV_Pos             (0)                                               /*!< CRPT_T::AES2_IV[4]: IV Position        */
#define CRPT_AES2_IVx_IV_Msk             (0xfffffffful << CRPT_AES2_IVx_IV_Pos)            /*!< CRPT_T::AES2_IV[4]: IV Mask            */

#define CRPT_AES2_SADDR_SADDR_Pos        (0)                                               /*!< CRPT_T::AES2_SADDR: SADDR Position     */
#define CRPT_AES2_SADDR_SADDR_Msk        (0xfffffffful << CRPT_AES2_SADDR_SADDR_Pos)       /*!< CRPT_T::AES2_SADDR: SADDR Mask         */

#define CRPT_AES2_DADDR_DADDR_Pos        (0)                                               /*!< CRPT_T::AES2_DADDR: DADDR Position     */
#define CRPT_AES2_DADDR_DADDR_Msk        (0xfffffffful << CRPT_AES2_DADDR_DADDR_Pos)       /*!< CRPT_T::AES2_DADDR: DADDR Mask         */

#define CRPT_AES2_CNT_CNT_Pos            (0)                                               /*!< CRPT_T::AES2_CNT: CNT Position         */
#define CRPT_AES2_CNT_CNT_Msk            (0xfffffffful << CRPT_AES2_CNT_CNT_Pos)           /*!< CRPT_T::AES2_CNT: CNT Mask             */

#define CRPT_AES3_KEYx_KEY_Pos           (0)                                               /*!< CRPT_T::AES3_KEY[8]: KEY Position      */
#define CRPT_AES3_KEYx_KEY_Msk           (0xfffffffful << CRPT_AES3_KEYx_KEY_Pos)          /*!< CRPT_T::AES3_KEY[8]: KEY Mask          */

#define CRPT_AES3_IVx_IV_Pos             (0)                                               /*!< CRPT_T::AES3_IV[4]: IV Position        */
#define CRPT_AES3_IVx_IV_Msk             (0xfffffffful << CRPT_AES3_IVx_IV_Pos)            /*!< CRPT_T::AES3_IV[4]: IV Mask            */

#define CRPT_AES3_SADDR_SADDR_Pos        (0)                                               /*!< CRPT_T::AES3_SADDR: SADDR Position     */
#define CRPT_AES3_SADDR_SADDR_Msk        (0xfffffffful << CRPT_AES3_SADDR_SADDR_Pos)       /*!< CRPT_T::AES3_SADDR: SADDR Mask         */

#define CRPT_AES3_DADDR_DADDR_Pos        (0)                                               /*!< CRPT_T::AES3_DADDR: DADDR Position     */
#define CRPT_AES3_DADDR_DADDR_Msk        (0xfffffffful << CRPT_AES3_DADDR_DADDR_Pos)       /*!< CRPT_T::AES3_DADDR: DADDR Mask         */

#define CRPT_AES3_CNT_CNT_Pos            (0)                                               /*!< CRPT_T::AES3_CNT: CNT Position         */
#define CRPT_AES3_CNT_CNT_Msk            (0xfffffffful << CRPT_AES3_CNT_CNT_Pos)           /*!< CRPT_T::AES3_CNT: CNT Mask             */

#define CRPT_TDES_CTL_START_Pos          (0)                                               /*!< CRPT_T::TDES_CTL: START Position       */
#define CRPT_TDES_CTL_START_Msk          (0x1ul << CRPT_TDES_CTL_START_Pos)                /*!< CRPT_T::TDES_CTL: START Mask           */

#define CRPT_TDES_CTL_STOP_Pos           (1)                                               /*!< CRPT_T::TDES_CTL: STOP Position        */
#define CRPT_TDES_CTL_STOP_Msk           (0x1ul << CRPT_TDES_CTL_STOP_Pos)                 /*!< CRPT_T::TDES_CTL: STOP Mask            */

#define CRPT_TDES_CTL_TMODE_Pos          (2)                                               /*!< CRPT_T::TDES_CTL: TMODE Position       */
#define CRPT_TDES_CTL_TMODE_Msk          (0x1ul << CRPT_TDES_CTL_TMODE_Pos)                /*!< CRPT_T::TDES_CTL: TMODE Mask           */

#define CRPT_TDES_CTL_3KEYS_Pos          (3)                                               /*!< CRPT_T::TDES_CTL: 3KEYS Position       */
#define CRPT_TDES_CTL_3KEYS_Msk          (0x1ul << CRPT_TDES_CTL_3KEYS_Pos)                /*!< CRPT_T::TDES_CTL: 3KEYS Mask           */

#define CRPT_TDES_CTL_DMALAST_Pos        (5)                                               /*!< CRPT_T::TDES_CTL: DMALAST Position     */
#define CRPT_TDES_CTL_DMALAST_Msk        (0x1ul << CRPT_TDES_CTL_DMALAST_Pos)              /*!< CRPT_T::TDES_CTL: DMALAST Mask         */

#define CRPT_TDES_CTL_DMACSCAD_Pos       (6)                                               /*!< CRPT_T::TDES_CTL: DMACSCAD Position    */
#define CRPT_TDES_CTL_DMACSCAD_Msk       (0x1ul << CRPT_TDES_CTL_DMACSCAD_Pos)             /*!< CRPT_T::TDES_CTL: DMACSCAD Mask        */

#define CRPT_TDES_CTL_DMAEN_Pos          (7)                                               /*!< CRPT_T::TDES_CTL: DMAEN Position       */
#define CRPT_TDES_CTL_DMAEN_Msk          (0x1ul << CRPT_TDES_CTL_DMAEN_Pos)                /*!< CRPT_T::TDES_CTL: DMAEN Mask           */

#define CRPT_TDES_CTL_OPMODE_Pos         (8)                                               /*!< CRPT_T::TDES_CTL: OPMODE Position      */
#define CRPT_TDES_CTL_OPMODE_Msk         (0x7ul << CRPT_TDES_CTL_OPMODE_Pos)               /*!< CRPT_T::TDES_CTL: OPMODE Mask          */

#define CRPT_TDES_CTL_ENCRPT_Pos         (16)                                              /*!< CRPT_T::TDES_CTL: ENCRPT Position      */
#define CRPT_TDES_CTL_ENCRPT_Msk         (0x1ul << CRPT_TDES_CTL_ENCRPT_Pos)               /*!< CRPT_T::TDES_CTL: ENCRPT Mask          */

#define CRPT_TDES_CTL_BLKSWAP_Pos        (21)                                              /*!< CRPT_T::TDES_CTL: BLKSWAP Position     */
#define CRPT_TDES_CTL_BLKSWAP_Msk        (0x1ul << CRPT_TDES_CTL_BLKSWAP_Pos)              /*!< CRPT_T::TDES_CTL: BLKSWAP Mask         */

#define CRPT_TDES_CTL_OUTSWAP_Pos        (22)                                              /*!< CRPT_T::TDES_CTL: OUTSWAP Position     */
#define CRPT_TDES_CTL_OUTSWAP_Msk        (0x1ul << CRPT_TDES_CTL_OUTSWAP_Pos)              /*!< CRPT_T::TDES_CTL: OUTSWAP Mask         */

#define CRPT_TDES_CTL_INSWAP_Pos         (23)                                              /*!< CRPT_T::TDES_CTL: INSWAP Position      */
#define CRPT_TDES_CTL_INSWAP_Msk         (0x1ul << CRPT_TDES_CTL_INSWAP_Pos)               /*!< CRPT_T::TDES_CTL: INSWAP Mask          */

#define CRPT_TDES_CTL_CHANNEL_Pos        (24)                                              /*!< CRPT_T::TDES_CTL: CHANNEL Position     */
#define CRPT_TDES_CTL_CHANNEL_Msk        (0x3ul << CRPT_TDES_CTL_CHANNEL_Pos)              /*!< CRPT_T::TDES_CTL: CHANNEL Mask         */

#define CRPT_TDES_CTL_KEYUNPRT_Pos       (26)                                              /*!< CRPT_T::TDES_CTL: KEYUNPRT Position    */
#define CRPT_TDES_CTL_KEYUNPRT_Msk       (0x1ful << CRPT_TDES_CTL_KEYUNPRT_Pos)            /*!< CRPT_T::TDES_CTL: KEYUNPRT Mask        */

#define CRPT_TDES_CTL_KEYPRT_Pos         (31)                                              /*!< CRPT_T::TDES_CTL: KEYPRT Position      */
#define CRPT_TDES_CTL_KEYPRT_Msk         (0x1ul << CRPT_TDES_CTL_KEYPRT_Pos)               /*!< CRPT_T::TDES_CTL: KEYPRT Mask          */

#define CRPT_TDES_STS_BUSY_Pos           (0)                                               /*!< CRPT_T::TDES_STS: BUSY Position        */
#define CRPT_TDES_STS_BUSY_Msk           (0x1ul << CRPT_TDES_STS_BUSY_Pos)                 /*!< CRPT_T::TDES_STS: BUSY Mask            */

#define CRPT_TDES_STS_INBUFEMPTY_Pos     (8)                                               /*!< CRPT_T::TDES_STS: INBUFEMPTY Position  */
#define CRPT_TDES_STS_INBUFEMPTY_Msk     (0x1ul << CRPT_TDES_STS_INBUFEMPTY_Pos)           /*!< CRPT_T::TDES_STS: INBUFEMPTY Mask      */

#define CRPT_TDES_STS_INBUFFULL_Pos      (9)                                               /*!< CRPT_T::TDES_STS: INBUFFULL Position   */
#define CRPT_TDES_STS_INBUFFULL_Msk      (0x1ul << CRPT_TDES_STS_INBUFFULL_Pos)            /*!< CRPT_T::TDES_STS: INBUFFULL Mask       */

#define CRPT_TDES_STS_INBUFERR_Pos       (10)                                              /*!< CRPT_T::TDES_STS: INBUFERR Position    */
#define CRPT_TDES_STS_INBUFERR_Msk       (0x1ul << CRPT_TDES_STS_INBUFERR_Pos)             /*!< CRPT_T::TDES_STS: INBUFERR Mask        */

#define CRPT_TDES_STS_OUTBUFEMPTY_Pos    (16)                                              /*!< CRPT_T::TDES_STS: OUTBUFEMPTY Position */
#define CRPT_TDES_STS_OUTBUFEMPTY_Msk    (0x1ul << CRPT_TDES_STS_OUTBUFEMPTY_Pos)          /*!< CRPT_T::TDES_STS: OUTBUFEMPTY Mask     */

#define CRPT_TDES_STS_OUTBUFFULL_Pos     (17)                                              /*!< CRPT_T::TDES_STS: OUTBUFFULL Position  */
#define CRPT_TDES_STS_OUTBUFFULL_Msk     (0x1ul << CRPT_TDES_STS_OUTBUFFULL_Pos)           /*!< CRPT_T::TDES_STS: OUTBUFFULL Mask      */

#define CRPT_TDES_STS_OUTBUFERR_Pos      (18)                                              /*!< CRPT_T::TDES_STS: OUTBUFERR Position   */
#define CRPT_TDES_STS_OUTBUFERR_Msk      (0x1ul << CRPT_TDES_STS_OUTBUFERR_Pos)            /*!< CRPT_T::TDES_STS: OUTBUFERR Mask       */

#define CRPT_TDES_STS_BUSERR_Pos         (20)                                              /*!< CRPT_T::TDES_STS: BUSERR Position      */
#define CRPT_TDES_STS_BUSERR_Msk         (0x1ul << CRPT_TDES_STS_BUSERR_Pos)               /*!< CRPT_T::TDES_STS: BUSERR Mask          */

#define CRPT_TDES0_KEYxH_KEY_Pos         (0)                                               /*!< CRPT_T::TDES0_KEYxH: KEY Position      */
#define CRPT_TDES0_KEYxH_KEY_Msk         (0xfffffffful << CRPT_TDES0_KEYxH_KEY_Pos)        /*!< CRPT_T::TDES0_KEYxH: KEY Mask          */

#define CRPT_TDES0_KEYxL_KEY_Pos         (0)                                               /*!< CRPT_T::TDES0_KEYxL: KEY Position      */
#define CRPT_TDES0_KEYxL_KEY_Msk         (0xfffffffful << CRPT_TDES0_KEYxL_KEY_Pos)        /*!< CRPT_T::TDES0_KEYxL: KEY Mask          */

#define CRPT_TDES0_IVH_IV_Pos            (0)                                               /*!< CRPT_T::TDES0_IVH: IV Position         */
#define CRPT_TDES0_IVH_IV_Msk            (0xfffffffful << CRPT_TDES0_IVH_IV_Pos)           /*!< CRPT_T::TDES0_IVH: IV Mask             */

#define CRPT_TDES0_IVL_IV_Pos            (0)                                               /*!< CRPT_T::TDES0_IVL: IV Position         */
#define CRPT_TDES0_IVL_IV_Msk            (0xfffffffful << CRPT_TDES0_IVL_IV_Pos)           /*!< CRPT_T::TDES0_IVL: IV Mask             */

#define CRPT_TDES0_SADDR_SADDR_Pos       (0)                                               /*!< CRPT_T::TDES0_SADDR: SADDR Position    */
#define CRPT_TDES0_SADDR_SADDR_Msk       (0xfffffffful << CRPT_TDES0_SADDR_SADDR_Pos)      /*!< CRPT_T::TDES0_SADDR: SADDR Mask        */

#define CRPT_TDES0_DADDR_DADDR_Pos       (0)                                               /*!< CRPT_T::TDES0_DADDR: DADDR Position    */
#define CRPT_TDES0_DADDR_DADDR_Msk       (0xfffffffful << CRPT_TDES0_DADDR_DADDR_Pos)      /*!< CRPT_T::TDES0_DADDR: DADDR Mask        */

#define CRPT_TDES0_CNT_CNT_Pos           (0)                                               /*!< CRPT_T::TDES0_CNT: CNT Position        */
#define CRPT_TDES0_CNT_CNT_Msk           (0xfffffffful << CRPT_TDES0_CNT_CNT_Pos)          /*!< CRPT_T::TDES0_CNT: CNT Mask            */

#define CRPT_TDES_DATIN_DATIN_Pos        (0)                                               /*!< CRPT_T::TDES_DATIN: DATIN Position     */
#define CRPT_TDES_DATIN_DATIN_Msk        (0xfffffffful << CRPT_TDES_DATIN_DATIN_Pos)       /*!< CRPT_T::TDES_DATIN: DATIN Mask         */

#define CRPT_TDES_DATOUT_DATOUT_Pos      (0)                                               /*!< CRPT_T::TDES_DATOUT: DATOUT Position   */
#define CRPT_TDES_DATOUT_DATOUT_Msk      (0xfffffffful << CRPT_TDES_DATOUT_DATOUT_Pos)     /*!< CRPT_T::TDES_DATOUT: DATOUT Mask       */

#define CRPT_TDES1_KEYxH_KEY_Pos         (0)                                               /*!< CRPT_T::TDES1_KEYxH: KEY Position      */
#define CRPT_TDES1_KEYxH_KEY_Msk         (0xfffffffful << CRPT_TDES1_KEYxH_KEY_Pos)        /*!< CRPT_T::TDES1_KEYxH: KEY Mask          */

#define CRPT_TDES1_KEYxL_KEY_Pos         (0)                                               /*!< CRPT_T::TDES1_KEYxL: KEY Position      */
#define CRPT_TDES1_KEYxL_KEY_Msk         (0xfffffffful << CRPT_TDES1_KEY1L_KEY_Pos)        /*!< CRPT_T::TDES1_KEYxL: KEY Mask          */

#define CRPT_TDES1_IVH_IV_Pos            (0)                                               /*!< CRPT_T::TDES1_IVH: IV Position         */
#define CRPT_TDES1_IVH_IV_Msk            (0xfffffffful << CRPT_TDES1_IVH_IV_Pos)           /*!< CRPT_T::TDES1_IVH: IV Mask             */

#define CRPT_TDES1_IVL_IV_Pos            (0)                                               /*!< CRPT_T::TDES1_IVL: IV Position         */
#define CRPT_TDES1_IVL_IV_Msk            (0xfffffffful << CRPT_TDES1_IVL_IV_Pos)           /*!< CRPT_T::TDES1_IVL: IV Mask             */

#define CRPT_TDES1_SADDR_SADDR_Pos       (0)                                               /*!< CRPT_T::TDES1_SADDR: SADDR Position    */
#define CRPT_TDES1_SADDR_SADDR_Msk       (0xfffffffful << CRPT_TDES1_SADDR_SADDR_Pos)      /*!< CRPT_T::TDES1_SADDR: SADDR Mask        */

#define CRPT_TDES1_DADDR_DADDR_Pos       (0)                                               /*!< CRPT_T::TDES1_DADDR: DADDR Position    */
#define CRPT_TDES1_DADDR_DADDR_Msk       (0xfffffffful << CRPT_TDES1_DADDR_DADDR_Pos)      /*!< CRPT_T::TDES1_DADDR: DADDR Mask        */

#define CRPT_TDES1_CNT_CNT_Pos           (0)                                               /*!< CRPT_T::TDES1_CNT: CNT Position        */
#define CRPT_TDES1_CNT_CNT_Msk           (0xfffffffful << CRPT_TDES1_CNT_CNT_Pos)          /*!< CRPT_T::TDES1_CNT: CNT Mask            */

#define CRPT_TDES2_KEYxH_KEY_Pos         (0)                                               /*!< CRPT_T::TDES2_KEYxH: KEY Position      */
#define CRPT_TDES2_KEYxH_KEY_Msk         (0xfffffffful << CRPT_TDES2_KEYxH_KEY_Pos)        /*!< CRPT_T::TDES2_KEYxH: KEY Mask          */

#define CRPT_TDES2_KEYxL_KEY_Pos         (0)                                               /*!< CRPT_T::TDES2_KEYxL: KEY Position      */
#define CRPT_TDES2_KEYxL_KEY_Msk         (0xfffffffful << CRPT_TDES2_KEYxL_KEY_Pos)        /*!< CRPT_T::TDES2_KEYxL: KEY Mask          */

#define CRPT_TDES2_IVH_IV_Pos            (0)                                               /*!< CRPT_T::TDES2_IVH: IV Position         */
#define CRPT_TDES2_IVH_IV_Msk            (0xfffffffful << CRPT_TDES2_IVH_IV_Pos)           /*!< CRPT_T::TDES2_IVH: IV Mask             */

#define CRPT_TDES2_IVL_IV_Pos            (0)                                               /*!< CRPT_T::TDES2_IVL: IV Position         */
#define CRPT_TDES2_IVL_IV_Msk            (0xfffffffful << CRPT_TDES2_IVL_IV_Pos)           /*!< CRPT_T::TDES2_IVL: IV Mask             */

#define CRPT_TDES2_SADDR_SADDR_Pos       (0)                                               /*!< CRPT_T::TDES2_SADDR: SADDR Position    */
#define CRPT_TDES2_SADDR_SADDR_Msk       (0xfffffffful << CRPT_TDES2_SADDR_SADDR_Pos)      /*!< CRPT_T::TDES2_SADDR: SADDR Mask        */

#define CRPT_TDES2_DADDR_DADDR_Pos       (0)                                               /*!< CRPT_T::TDES2_DADDR: DADDR Position    */
#define CRPT_TDES2_DADDR_DADDR_Msk       (0xfffffffful << CRPT_TDES2_DADDR_DADDR_Pos)      /*!< CRPT_T::TDES2_DADDR: DADDR Mask        */

#define CRPT_TDES2_CNT_CNT_Pos           (0)                                               /*!< CRPT_T::TDES2_CNT: CNT Position        */
#define CRPT_TDES2_CNT_CNT_Msk           (0xfffffffful << CRPT_TDES2_CNT_CNT_Pos)          /*!< CRPT_T::TDES2_CNT: CNT Mask            */

#define CRPT_TDES3_KEYxH_KEY_Pos         (0)                                               /*!< CRPT_T::TDES3_KEYxH: KEY Position      */
#define CRPT_TDES3_KEYxH_KEY_Msk         (0xfffffffful << CRPT_TDES3_KEYxH_KEY_Pos)        /*!< CRPT_T::TDES3_KEYxH: KEY Mask          */

#define CRPT_TDES3_KEYxL_KEY_Pos         (0)                                               /*!< CRPT_T::TDES3_KEYxL: KEY Position      */
#define CRPT_TDES3_KEYxL_KEY_Msk         (0xfffffffful << CRPT_TDES3_KEYxL_KEY_Pos)        /*!< CRPT_T::TDES3_KEYxL: KEY Mask          */

#define CRPT_TDES3_IVH_IV_Pos            (0)                                               /*!< CRPT_T::TDES3_IVH: IV Position         */
#define CRPT_TDES3_IVH_IV_Msk            (0xfffffffful << CRPT_TDES3_IVH_IV_Pos)           /*!< CRPT_T::TDES3_IVH: IV Mask             */

#define CRPT_TDES3_IVL_IV_Pos            (0)                                               /*!< CRPT_T::TDES3_IVL: IV Position         */
#define CRPT_TDES3_IVL_IV_Msk            (0xfffffffful << CRPT_TDES3_IVL_IV_Pos)           /*!< CRPT_T::TDES3_IVL: IV Mask             */

#define CRPT_TDES3_SADDR_SADDR_Pos       (0)                                               /*!< CRPT_T::TDES3_SADDR: SADDR Position    */
#define CRPT_TDES3_SADDR_SADDR_Msk       (0xfffffffful << CRPT_TDES3_SADDR_SADDR_Pos)      /*!< CRPT_T::TDES3_SADDR: SADDR Mask        */

#define CRPT_TDES3_DADDR_DADDR_Pos       (0)                                               /*!< CRPT_T::TDES3_DADDR: DADDR Position    */
#define CRPT_TDES3_DADDR_DADDR_Msk       (0xfffffffful << CRPT_TDES3_DADDR_DADDR_Pos)      /*!< CRPT_T::TDES3_DADDR: DADDR Mask        */

#define CRPT_TDES3_CNT_CNT_Pos           (0)                                               /*!< CRPT_T::TDES3_CNT: CNT Position        */
#define CRPT_TDES3_CNT_CNT_Msk           (0xfffffffful << CRPT_TDES3_CNT_CNT_Pos)          /*!< CRPT_T::TDES3_CNT: CNT Mask            */

#define CRPT_HMAC_CTL_START_Pos          (0)                                               /*!< CRPT_T::HMAC_CTL: START Position       */
#define CRPT_HMAC_CTL_START_Msk          (0x1ul << CRPT_HMAC_CTL_START_Pos)                /*!< CRPT_T::HMAC_CTL: START Mask           */

#define CRPT_HMAC_CTL_STOP_Pos           (1)                                               /*!< CRPT_T::HMAC_CTL: STOP Position        */
#define CRPT_HMAC_CTL_STOP_Msk           (0x1ul << CRPT_HMAC_CTL_STOP_Pos)                 /*!< CRPT_T::HMAC_CTL: STOP Mask            */

#define CRPT_HMAC_CTL_HMACEN_Pos         (4)                                               /*!< CRPT_T::HMAC_CTL: HMACEN Position      */
#define CRPT_HMAC_CTL_HMACEN_Msk         (0x1ul << CRPT_HMAC_CTL_HMACEN_Pos)               /*!< CRPT_T::HMAC_CTL: HMACEN Mask          */

#define CRPT_HMAC_CTL_DMALAST_Pos        (5)                                               /*!< CRPT_T::HMAC_CTL: DMALAST Position     */
#define CRPT_HMAC_CTL_DMALAST_Msk        (0x1ul << CRPT_HMAC_CTL_DMALAST_Pos)              /*!< CRPT_T::HMAC_CTL: DMALAST Mask         */

#define CRPT_HMAC_CTL_DMAEN_Pos          (7)                                               /*!< CRPT_T::HMAC_CTL: DMAEN Position       */
#define CRPT_HMAC_CTL_DMAEN_Msk          (0x1ul << CRPT_HMAC_CTL_DMAEN_Pos)                /*!< CRPT_T::HMAC_CTL: DMAEN Mask           */

#define CRPT_HMAC_CTL_OPMODE_Pos         (8)                                               /*!< CRPT_T::HMAC_CTL: OPMODE Position      */
#define CRPT_HMAC_CTL_OPMODE_Msk         (0x7ul << CRPT_HMAC_CTL_OPMODE_Pos)               /*!< CRPT_T::HMAC_CTL: OPMODE Mask          */

#define CRPT_HMAC_CTL_OUTSWAP_Pos        (22)                                              /*!< CRPT_T::HMAC_CTL: OUTSWAP Position     */
#define CRPT_HMAC_CTL_OUTSWAP_Msk        (0x1ul << CRPT_HMAC_CTL_OUTSWAP_Pos)              /*!< CRPT_T::HMAC_CTL: OUTSWAP Mask         */

#define CRPT_HMAC_CTL_INSWAP_Pos         (23)                                              /*!< CRPT_T::HMAC_CTL: INSWAP Position      */
#define CRPT_HMAC_CTL_INSWAP_Msk         (0x1ul << CRPT_HMAC_CTL_INSWAP_Pos)               /*!< CRPT_T::HMAC_CTL: INSWAP Mask          */

#define CRPT_HMAC_STS_BUSY_Pos           (0)                                               /*!< CRPT_T::HMAC_STS: BUSY Position        */
#define CRPT_HMAC_STS_BUSY_Msk           (0x1ul << CRPT_HMAC_STS_BUSY_Pos)                 /*!< CRPT_T::HMAC_STS: BUSY Mask            */

#define CRPT_HMAC_STS_DMABUSY_Pos        (1)                                               /*!< CRPT_T::HMAC_STS: DMABUSY Position     */
#define CRPT_HMAC_STS_DMABUSY_Msk        (0x1ul << CRPT_HMAC_STS_DMABUSY_Pos)              /*!< CRPT_T::HMAC_STS: DMABUSY Mask         */

#define CRPT_HMAC_STS_DMAERR_Pos         (8)                                               /*!< CRPT_T::HMAC_STS: DMAERR Position      */
#define CRPT_HMAC_STS_DMAERR_Msk         (0x1ul << CRPT_HMAC_STS_DMAERR_Pos)               /*!< CRPT_T::HMAC_STS: DMAERR Mask          */

#define CRPT_HMAC_STS_DATINREQ_Pos       (16)                                              /*!< CRPT_T::HMAC_STS: DATINREQ Position    */
#define CRPT_HMAC_STS_DATINREQ_Msk       (0x1ul << CRPT_HMAC_STS_DATINREQ_Pos)             /*!< CRPT_T::HMAC_STS: DATINREQ Mask        */

#define CRPT_HMAC_DGSTx_DGST_Pos         (0)                                               /*!< CRPT_T::HMAC_DGST[16]: DGST Position   */
#define CRPT_HMAC_DGSTx_DGST_Msk         (0xfffffffful << CRPT_HMAC_DGSTx_DGST_Pos)        /*!< CRPT_T::HMAC_DGST[16]: DGST Mask       */

#define CRPT_HMAC_KEYCNT_KEYCNT_Pos      (0)                                               /*!< CRPT_T::HMAC_KEYCNT: KEYCNT Position   */
#define CRPT_HMAC_KEYCNT_KEYCNT_Msk      (0xfffffffful << CRPT_HMAC_KEYCNT_KEYCNT_Pos)     /*!< CRPT_T::HMAC_KEYCNT: KEYCNT Mask       */

#define CRPT_HMAC_SADDR_SADDR_Pos        (0)                                               /*!< CRPT_T::HMAC_SADDR: SADDR Position     */
#define CRPT_HMAC_SADDR_SADDR_Msk        (0xfffffffful << CRPT_HMAC_SADDR_SADDR_Pos)       /*!< CRPT_T::HMAC_SADDR: SADDR Mask         */

#define CRPT_HMAC_DMACNT_DMACNT_Pos      (0)                                               /*!< CRPT_T::HMAC_DMACNT: DMACNT Position   */
#define CRPT_HMAC_DMACNT_DMACNT_Msk      (0xfffffffful << CRPT_HMAC_DMACNT_DMACNT_Pos)     /*!< CRPT_T::HMAC_DMACNT: DMACNT Mask       */

#define CRPT_HMAC_DATIN_DATIN_Pos        (0)                                               /*!< CRPT_T::HMAC_DATIN: DATIN Position     */
#define CRPT_HMAC_DATIN_DATIN_Msk        (0xfffffffful << CRPT_HMAC_DATIN_DATIN_Pos)       /*!< CRPT_T::HMAC_DATIN: DATIN Mask         */

#define CRPT_ECC_CTL_START_Pos           (0)                                               /*!< CRPT_T::ECC_CTL: START Position        */
#define CRPT_ECC_CTL_START_Msk           (0x1ul << CRPT_ECC_CTL_START_Pos)                 /*!< CRPT_T::ECC_CTL: START Mask            */

#define CRPT_ECC_CTL_STOP_Pos            (1)                                               /*!< CRPT_T::ECC_CTL: STOP Position         */
#define CRPT_ECC_CTL_STOP_Msk            (0x1ul << CRPT_ECC_CTL_STOP_Pos)                  /*!< CRPT_T::ECC_CTL: STOP Mask             */

#define CRPT_ECC_CTL_DMAEN_Pos           (7)                                               /*!< CRPT_T::ECC_CTL: DMAEN Position        */
#define CRPT_ECC_CTL_DMAEN_Msk           (0x1ul << CRPT_ECC_CTL_DMAEN_Pos)                 /*!< CRPT_T::ECC_CTL: DMAEN Mask            */

#define CRPT_ECC_CTL_FSEL_Pos            (8)                                               /*!< CRPT_T::ECC_CTL: FSEL Position         */
#define CRPT_ECC_CTL_FSEL_Msk            (0x1ul << CRPT_ECC_CTL_FSEL_Pos)                  /*!< CRPT_T::ECC_CTL: FSEL Mask             */

#define CRPT_ECC_CTL_ECCOP_Pos           (9)                                               /*!< CRPT_T::ECC_CTL: ECCOP Position        */
#define CRPT_ECC_CTL_ECCOP_Msk           (0x3ul << CRPT_ECC_CTL_ECCOP_Pos)                 /*!< CRPT_T::ECC_CTL: ECCOP Mask            */

#define CRPT_ECC_CTL_MODOP_Pos           (11)                                              /*!< CRPT_T::ECC_CTL: MODOP Position        */
#define CRPT_ECC_CTL_MODOP_Msk           (0x3ul << CRPT_ECC_CTL_MODOP_Pos)                 /*!< CRPT_T::ECC_CTL: MODOP Mask            */

#define CRPT_ECC_CTL_LDP1_Pos            (16)                                              /*!< CRPT_T::ECC_CTL: LDP1 Position         */
#define CRPT_ECC_CTL_LDP1_Msk            (0x1ul << CRPT_ECC_CTL_LDP1_Pos)                  /*!< CRPT_T::ECC_CTL: LDP1 Mask             */

#define CRPT_ECC_CTL_LDP2_Pos            (17)                                              /*!< CRPT_T::ECC_CTL: LDP2 Position         */
#define CRPT_ECC_CTL_LDP2_Msk            (0x1ul << CRPT_ECC_CTL_LDP2_Pos)                  /*!< CRPT_T::ECC_CTL: LDP2 Mask             */

#define CRPT_ECC_CTL_LDA_Pos             (18)                                              /*!< CRPT_T::ECC_CTL: LDA Position          */
#define CRPT_ECC_CTL_LDA_Msk             (0x1ul << CRPT_ECC_CTL_LDA_Pos)                   /*!< CRPT_T::ECC_CTL: LDA Mask              */

#define CRPT_ECC_CTL_LDB_Pos             (19)                                              /*!< CRPT_T::ECC_CTL: LDB Position          */
#define CRPT_ECC_CTL_LDB_Msk             (0x1ul << CRPT_ECC_CTL_LDB_Pos)                   /*!< CRPT_T::ECC_CTL: LDB Mask              */

#define CRPT_ECC_CTL_LDN_Pos             (20)                                              /*!< CRPT_T::ECC_CTL: LDN Position          */
#define CRPT_ECC_CTL_LDN_Msk             (0x1ul << CRPT_ECC_CTL_LDN_Pos)                   /*!< CRPT_T::ECC_CTL: LDN Mask              */

#define CRPT_ECC_CTL_LDK_Pos             (21)                                              /*!< CRPT_T::ECC_CTL: LDK Position          */
#define CRPT_ECC_CTL_LDK_Msk             (0x1ul << CRPT_ECC_CTL_LDK_Pos)                   /*!< CRPT_T::ECC_CTL: LDK Mask              */

#define CRPT_ECC_CTL_CURVEM_Pos          (22)                                              /*!< CRPT_T::ECC_CTL: CURVEM Position       */
#define CRPT_ECC_CTL_CURVEM_Msk          (0x3fful << CRPT_ECC_CTL_CURVEM_Pos)              /*!< CRPT_T::ECC_CTL: CURVEM Mask           */

#define CRPT_ECC_STS_BUSY_Pos            (0)                                               /*!< CRPT_T::ECC_STS: BUSY Position         */
#define CRPT_ECC_STS_BUSY_Msk            (0x1ul << CRPT_ECC_STS_BUSY_Pos)                  /*!< CRPT_T::ECC_STS: BUSY Mask             */

#define CRPT_ECC_STS_DMABUSY_Pos         (1)                                               /*!< CRPT_T::ECC_STS: DMABUSY Position      */
#define CRPT_ECC_STS_DMABUSY_Msk         (0x1ul << CRPT_ECC_STS_DMABUSY_Pos)               /*!< CRPT_T::ECC_STS: DMABUSY Mask          */

#define CRPT_ECC_STS_BUSERR_Pos          (16)                                              /*!< CRPT_T::ECC_STS: BUSERR Position       */
#define CRPT_ECC_STS_BUSERR_Msk          (0x1ul << CRPT_ECC_STS_BUSERR_Pos)                /*!< CRPT_T::ECC_STS: BUSERR Mask           */

#define CRPT_ECC_X1_POINTX1_Pos          (0)                                               /*!< CRPT_T::ECC_X1[18]:  POINTX1 Position  */
#define CRPT_ECC_X1_POINTX1_Msk          (0xfffffffful << CRPT_ECC_X1_POINTX1_Pos)         /*!< CRPT_T::ECC_X1[18]:  POINTX1 Mask      */

#define CRPT_ECC_Y1_POINTY1_Pos          (0)                                               /*!< CRPT_T::ECC_Y1[18]: POINTY1 Position   */
#define CRPT_ECC_Y1_POINTY1_Msk          (0xfffffffful << CRPT_ECC_Y1_POINTY1_Pos)         /*!< CRPT_T::ECC_Y1[18]: POINTY1 Mask       */

#define CRPT_ECC_X2_POINTX2_Pos          (0)                                               /*!< CRPT_T::ECC_X2[18]: POINTX2 Position   */
#define CRPT_ECC_X2_POINTX2_Msk          (0xfffffffful << CRPT_ECC_X2_POINTX2_Pos)         /*!< CRPT_T::ECC_X2[18]: POINTX2 Mask       */

#define CRPT_ECC_Y2_POINTY2_Pos          (0)                                               /*!< CRPT_T::ECC_Y2[18]: POINTY2 Position   */
#define CRPT_ECC_Y2_POINTY2_Msk          (0xfffffffful << CRPT_ECC_Y2_POINTY2_Pos)         /*!< CRPT_T::ECC_Y2[18]: POINTY2 Mask       */

#define CRPT_ECC_A_CURVEA_Pos            (0)                                               /*!< CRPT_T::ECC_A[18]: CURVEA Position     */
#define CRPT_ECC_A_CURVEA_Msk            (0xfffffffful << CRPT_ECC_A_CURVEA_Pos)           /*!< CRPT_T::ECC_A[18]: CURVEA Mask         */

#define CRPT_ECC_B_CURVEB_Pos            (0)                                               /*!< CRPT_T::ECC_B[18]: CURVEB Position     */
#define CRPT_ECC_B_CURVEB_Msk            (0xfffffffful << CRPT_ECC_B_CURVEB_Pos)           /*!< CRPT_T::ECC_B[18]: CURVEB Mask         */

#define CRPT_ECC_N_CURVEN_Pos            (0)                                               /*!< CRPT_T::ECC_N[18]: CURVEN Position     */
#define CRPT_ECC_N_CURVEN_Msk            (0xfffffffful << CRPT_ECC_N_CURVEN_Pos)           /*!< CRPT_T::ECC_N[18]: CURVEN Mask         */

#define CRPT_ECC_K_SCALARK_Pos           (0)                                               /*!< CRPT_T::ECC_K[18]: SCALARK Position    */
#define CRPT_ECC_K_SCALARK_Msk           (0xfffffffful << CRPT_ECC_K_SCALARK_Pos)          /*!< CRPT_T::ECC_K[18]: SCALARK Mask        */

#define CRPT_ECC_DADDR_DADDR_Pos         (0)                                               /*!< CRPT_T::ECC_DADDR: DADDR Position      */
#define CRPT_ECC_DADDR_DADDR_Msk         (0xfffffffful << CRPT_ECC_DADDR_DADDR_Pos)        /*!< CRPT_T::ECC_DADDR: DADDR Mask          */

#define CRPT_ECC_STARTREG_STARTREG_Pos   (0)                                               /*!< CRPT_T::ECC_STARTREG: STARTREG Position*/
#define CRPT_ECC_STARTREG_STARTREG_Msk   (0xfffffffful << CRPT_ECC_STARTREG_STARTREG_Pos)  /*!< CRPT_T::ECC_STARTREG: STARTREG Mask    */

#define CRPT_ECC_WORDCNT_WORDCNT_Pos     (0)                                               /*!< CRPT_T::ECC_WORDCNT: WORDCNT Position  */
#define CRPT_ECC_WORDCNT_WORDCNT_Msk     (0xfffffffful << CRPT_ECC_WORDCNT_WORDCNT_Pos)    /*!< CRPT_T::ECC_WORDCNT: WORDCNT Mask      */

/**@}*/ /* CRPT_CONST CRYPTO */
/**@}*/ /* end of CRYPTO register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __CRYPTO_REG_H__ */
