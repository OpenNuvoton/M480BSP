/**************************************************************************//**
 * @file     fmc_reg.h
 * @version  V1.00
 * @brief    FMC register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __FMC_REG_H__
#define __FMC_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup FMC Flash Memory Controller(FMC)
    Memory Mapped Structure for FMC Controller
@{ */

typedef struct
{
    /**
@var FMC_T::ISPCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ISPCTL
</font><br><p> <font size="2">
Offset: 0x00  ISP Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ISPEN</td><td><div style="word-wrap: break-word;"><b>ISP Enable Bit (Write Protect)
</b><br>
ISP function enable bit. Set this bit to enable ISP function.
<br>
0 = ISP function Disabled.
<br>
1 = ISP function Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[1]</td><td>BS</td><td><div style="word-wrap: break-word;"><b>Boot Select (Write Protect)
</b><br>
When MBS in CONFIG0 is 1, set/clear this bit to select next booting from LDROM/APROM, respectively
<br>
This bit also functions as chip booting status flag, which can be used to check where chip booted from
<br>
This bit is initiated with the inversed value of CBS[1] (CONFIG0[7]) after any reset is happened except CPU reset (CPU is 1) or system reset (SYS) is happened
<br>
0 = Booting from APROM when MBS (CONFIG0[5]) is 1.
<br>
1 = Booting from LDROM when MBS (CONFIG0[5]) is 1.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[2]</td><td>SPUEN</td><td><div style="word-wrap: break-word;"><b>SPROM Update Enable Bit (Write Protect)
</b><br>
0 = SPROM cannot be updated.
<br>
1 = SPROM can be updated.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[3]</td><td>APUEN</td><td><div style="word-wrap: break-word;"><b>APROM Update Enable Bit (Write Protect)
</b><br>
0 = APROM cannot be updated when the chip runs in APROM.
<br>
1 = APROM can be updated when the chip runs in APROM.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[4]</td><td>CFGUEN</td><td><div style="word-wrap: break-word;"><b>CONFIG Update Enable Bit (Write Protect)
</b><br>
0 = CONFIG cannot be updated.
<br>
1 = CONFIG can be updated.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[5]</td><td>LDUEN</td><td><div style="word-wrap: break-word;"><b>LDROM Update Enable Bit (Write Protect)
</b><br>
LDROM update enable bit.
<br>
0 = LDROM cannot be updated.
<br>
1 = LDROM can be updated.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[6]</td><td>ISPFF</td><td><div style="word-wrap: break-word;"><b>ISP Fail Flag (Write Protect)
</b><br>
This bit is set by hardware when a triggered ISP meets any of the following conditions:
<br>
This bit needs to be cleared by writing 1 to it.
<br>
(1) APROM writes to itself if APUEN is set to 0.
<br>
(2) LDROM writes to itself if LDUEN is set to 0.
<br>
(3) CONFIG is erased/programmed if CFGUEN is set to 0.
<br>
(4) SPROM is erased/programmed if SPUEN is set to 0
<br>
(5) SPROM is programmed at SPROM secured mode.
<br>
(6) Page Erase command at LOCK mode with ICE connection
<br>
(7) Erase or Program command at brown-out detected
<br>
(8) Destination address is illegal, such as over an available range.
<br>
(9) Invalid ISP commands
<br>
(10) Vector address is mapping to SPROM region
<br>
(11) KPROM is erased/programmed if KEYLOCK is set to 1
<br>
(12) APROM(except for Data Flash) is erased/programmed if KEYLOCK is set to 1
<br>
(13) LDROM is erased/programmed if KEYLOCK is set to 1
<br>
(14) SPROM is erased/programmed if KEYLOCK is set to 1 and KEYENROM[1:0] are 1.
<br>
(15) CONFIG is erased/programmed if KEYLOCK is set to 1 and KEYENROM[1:0] are 1
<br>
(16) Invalid operations (except for chip erase) with ICE connection if SBLOCK is not 0x5A
<br>
(17) Read any content of boot loader with ICE connection
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[16]</td><td>BL</td><td><div style="word-wrap: break-word;"><b>Boot Loader Booting (Write Protect)
</b><br>
This bit is initiated with the inversed value of MBS (CONFIG0[5])
<br>
Any reset, except CPU reset (CPU is 1) or system reset (SYS), BL will be reloaded
<br>
This bit is used to check chip boot from Boot Loader or not
<br>
User should keep original value of this bit when updating FMC_ISPCTL register.
<br>
0 = Booting from APROM or LDROM.
<br>
1 = Booting from Boot Loader.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::ISPADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ISPADDR
</font><br><p> <font size="2">
Offset: 0x04  ISP Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>ISPADDR</td><td><div style="word-wrap: break-word;"><b>ISP Address
</b><br>
The NuMicro M480 series is equipped with embedded flash
<br>
ISPADDR[1:0] must be kept 00 for ISP 32-bit operation
<br>
ISPADDR[2:0] must be kept 000 for ISP 64-bit operation.
<br>
For CRC32 Checksum Calculation command, this field is the flash starting address for checksum calculation, 4 Kbytes alignment is necessary for CRC32 checksum calculation.
<br>
For FLASH 32-bit Program, ISP address needs word alignment (4-byte)
<br>
For FLASH 64-bit Program, ISP address needs double word alignment (8-byte).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::ISPDAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ISPDAT
</font><br><p> <font size="2">
Offset: 0x08  ISP Data Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>ISPDAT</td><td><div style="word-wrap: break-word;"><b>ISP Data
</b><br>
Write data to this register before ISP program operation.
<br>
Read data from this register after ISP read operation.
<br>
When ISPFF (FMC_ISPCTL[6]) is 1, ISPDAT = 0xffff_ffff
<br>
For Run CRC32 Checksum Calculation command, ISPDAT is the memory size (byte) and 4 Kbytes alignment
<br>
For ISP Read CRC32 Checksum command, ISPDAT is the checksum result
<br>
If ISPDAT = 0x0000_0000, it means that (1) the checksum calculation is in progress, or (2) the memory range for checksum calculation is incorrect
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::ISPCMD

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ISPCMD
</font><br><p> <font size="2">
Offset: 0x0C  ISP Command Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[6:0]</td><td>CMD</td><td><div style="word-wrap: break-word;"><b>ISP Command
</b><br>
ISP command table is shown below:
<br>
0x00= FLASH Read.
<br>
0x04= Read Unique ID.
<br>
0x08= Read Flash All-One Result.
<br>
0x0B= Read Company ID.
<br>
0x0C= Read Device ID.
<br>
0x0D= Read Checksum.
<br>
0x21= FLASH 32-bit Program.
<br>
0x22= FLASH Page Erase. Erase any page in two banks, except for OTP.
<br>
0x23= FLASH Bank Erase. Erase all pages of APROM in BANK0 or BANK1.
<br>
0x25= FLASH Block Erase. Erase four pages alignment of APROM in BANK0 or BANK1..
<br>
0x27= FLASH Multi-Word Program.
<br>
0x28= Run Flash All-One Verification.
<br>
0x2D= Run Checksum Calculation.
<br>
0x2E= Vector Remap.
<br>
0x40= FLASH 64-bit Read.
<br>
0x61= FLASH 64-bit Program.
<br>
The other commands are invalid.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::ISPTRG

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ISPTRG
</font><br><p> <font size="2">
Offset: 0x10  ISP Trigger Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ISPGO</td><td><div style="word-wrap: break-word;"><b>ISP Start Trigger (Write Protect)
</b><br>
Write 1 to start ISP operation and this bit will be cleared to 0 by hardware automatically when ISP operation is finished.
<br>
0 = ISP operation is finished.
<br>
1 = ISP is progressed.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::DFBA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DFBA
</font><br><p> <font size="2">
Offset: 0x14  Data Flash Base Address
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DFBA</td><td><div style="word-wrap: break-word;"><b>Data Flash Base Address
</b><br>
This register indicates Data Flash start address. It is a read only register.
<br>
The Data Flash is shared with APROM. the content of this register is loaded from CONFIG1
<br>
This register is valid when DFEN (CONFIG0[0]) =0 .
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::ISPSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ISPSTS
</font><br><p> <font size="2">
Offset: 0x40  ISP Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ISPBUSY</td><td><div style="word-wrap: break-word;"><b>ISP Busy Flag (Read Only)
</b><br>
Write 1 to start ISP operation and this bit will be cleared to 0 by hardware automatically when ISP operation is finished.
<br>
This bit is the mirror of ISPGO(FMC_ISPTRG[0]).
<br>
0 = ISP operation is finished.
<br>
1 = ISP is progressed.
<br>
</div></td></tr><tr><td>
[2:1]</td><td>CBS</td><td><div style="word-wrap: break-word;"><b>Boot Selection of CONFIG (Read Only)
</b><br>
This bit is initiated with the CBS (CONFIG0[7:6]) after any reset is happened except CPU reset (CPU is 1) or system reset (SYS) is happened.
<br>
The following function is valid when MBS (FMC_ISPSTS[3])= 1.
<br>
00 = LDROM with IAP mode.
<br>
01 = LDROM without IAP mode.
<br>
10 = APROM with IAP mode.
<br>
11 = APROM without IAP mode.
<br>
</div></td></tr><tr><td>
[3]</td><td>MBS</td><td><div style="word-wrap: break-word;"><b>Boot From Boot Loader Selection Flag (Read Only)
</b><br>
This bit is initiated with the MBS (CONFIG0[5]) after any reset is happened except CPU reset (CPU is 1) or system reset (SYS) is happened
<br>
0 = Booting from Boot Loader.
<br>
1 = Booting from LDROM/APROM.(.see CBS bit setting)
<br>
</div></td></tr><tr><td>
[4]</td><td>FCYCDIS</td><td><div style="word-wrap: break-word;"><b>Flash Access Cycle Auto-tuning Disabled Flag (Read Only)
</b><br>
This bit is set if flash access cycle auto-tuning function is disabled
<br>
The auto-tunning function is disabled by FADIS(FMC_CYCCTL[8]) or HIRC clock is not ready.
<br>
0 = Flash access cycle auto-tuning is enabled.
<br>
1 = Flash access cycle auto-tuning is disabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>PGFF</td><td><div style="word-wrap: break-word;"><b>Flash Program with Fast Verification Flag (Read Only)
</b><br>
This bit is set if data is mismatched at ISP programming verification
<br>
This bit is clear by performing ISP flash erase or ISP read CID operation
<br>
0 = Flash Program is success.
<br>
1 = Flash Program is fail. Program data is different with data in the flash memory
<br>
</div></td></tr><tr><td>
[6]</td><td>ISPFF</td><td><div style="word-wrap: break-word;"><b>ISP Fail Flag (Write Protect)
</b><br>
This bit is the mirror of ISPFF (FMC_ISPCTL[6]), it needs to be cleared by writing 1 to FMC_ISPCTL[6] or FMC_ISPSTS[6]
<br>
This bit is set by hardware when a triggered ISP meets any of the following conditions:
<br>
(1) APROM writes to itself if APUEN is set to 0.
<br>
(2) LDROM writes to itself if LDUEN is set to 0.
<br>
(3) CONFIG is erased/programmed if CFGUEN is set to 0.
<br>
(4) SPROM is erased/programmed if SPUEN is set to 0
<br>
(5) SPROM is programmed at SPROM secured mode.
<br>
(6) Page Erase command at LOCK mode with ICE connection
<br>
(7) Erase or Program command at brown-out detected
<br>
(8) Destination address is illegal, such as over an available range.
<br>
(9) Invalid ISP commands
<br>
(10) Vector address is mapping to SPROM region.
<br>
(11) KPROM is erased/programmed if KEYLOCK is set to 1
<br>
(12) APROM(except for Data Flash) is erased/programmed if KEYLOCK is set to 1
<br>
(13) LDROM is erased/programmed if KEYLOCK is set to 1
<br>
(14) SPROM is erased/programmed if KEYLOCK is set to 1 and KEYENROM[1:0] are 1.
<br>
(15) CONFIG is erased/programmed if KEYLOCK is set to 1 and KEYENROM[1:0] are 1.
<br>
(16) Invalid operations (except for chip erase) with ICE connection if SBLOCK is not 0x5A
<br>
(17) Read any content of boot loader with ICE connection
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[7]</td><td>ALLONE</td><td><div style="word-wrap: break-word;"><b>Flash All-one Verification Flag
</b><br>
This bit is set by hardware if all of flash bits are 1, and clear if flash bits are not all 1 after "Run Flash All-One Verification" complete; this bit also can be clear by writing 1
<br>
0 = All of flash bits are 1 after "Run Flash All-One Verification" complete.
<br>
1 = Flash bits are not all 1 after "Run Flash All-One Verification" complete.
<br>
</div></td></tr><tr><td>
[23:9]</td><td>VECMAP</td><td><div style="word-wrap: break-word;"><b>Vector Page Mapping Address (Read Only)
</b><br>
All access to 0x0000_0000~0x0000_01FF is remapped to the flash memory address {VECMAP[14:0], 9u2019h000} ~ {VECMAP[14:0], 9u2019h1FF}
<br>
</div></td></tr><tr><td>
[31]</td><td>SCODE</td><td><div style="word-wrap: break-word;"><b>Security Code Active Flag
</b><br>
This bit is set by hardware when detecting SPROM secured code is active at flash initiation, or software writes 1 to this bit to make secured code active; this bit is clear by SPROM page erase operation.
<br>
0 = Secured code is inactive.
<br>
1 = Secured code is active.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::CYCCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CYCCTL
</font><br><p> <font size="2">
Offset: 0x4C  Flash Access Cycle Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>CYCLE</td><td><div style="word-wrap: break-word;"><b>Flash Access Cycle Control (Write Protect)
</b><br>
0001 = CPU access with one wait cycle if cache miss; flash access cycle is 1;.
<br>
The HCLK working frequency range range is<27MHz
<br>
0010 = CPU access with two wait cycles if cache miss; flash access cycle is 2;.
<br>
 The optimized HCLK working frequency range is 27~54 MHz
<br>
0011 = CPU access with three wait cycles if cache miss; flash access cycle is 3;.
<br>
The optimized HCLK working frequency range is 54~81MHz
<br>
0100 = CPU access with four wait cycles if cache miss; flash access cycle is 4;.
<br>
 The optimized HCLK working frequency range is81~108MHz
<br>
0101 = CPU access with five wait cycles if cache miss; flash access cycle is 5;.
<br>
The optimized HCLK working frequency range is 108~135MHz
<br>
0110 = CPU access with six wait cycles if cache miss; flash access cycle is 6;.
<br>
 The optimized HCLK working frequency range is 135~162MHz
<br>
0111 = CPU access with seven wait cycles if cache miss; flash access cycle is 7;.
<br>
 The optimized HCLK working frequency range is 162~192MHz
<br>
1000 = CPU access with eight wait cycles if cache miss; flash access cycle is 8;.
<br>
The optimized HCLK working frequency range is >192MHz
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::KPKEY0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">KPKEY0
</font><br><p> <font size="2">
Offset: 0x50  KPROM KEY0 Data Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KPKEY0</td><td><div style="word-wrap: break-word;"><b>KPROM KEY0 Data (Write Only)
</b><br>
Write KPKEY0 data to this register before KEY Comparison operation.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::KPKEY1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">KPKEY1
</font><br><p> <font size="2">
Offset: 0x54  KPROM KEY1 Data Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KPKEY1</td><td><div style="word-wrap: break-word;"><b>KPROM KEY1 Data (Write Only)
</b><br>
Write KPKEY1 data to this register before KEY Comparison operation.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::KPKEY2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">KPKEY2
</font><br><p> <font size="2">
Offset: 0x58  KPROM KEY2 Data Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KPKEY2</td><td><div style="word-wrap: break-word;"><b>KPROM KEY2 Data (Write Only)
</b><br>
Write KPKEY2 data to this register before KEY Comparison operation.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::KPKEYTRG

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">KPKEYTRG
</font><br><p> <font size="2">
Offset: 0x5C  KPROM KEY Comparison Trigger Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>KPKEYGO</td><td><div style="word-wrap: break-word;"><b>KPROM KEY Comparison Start Trigger (Write Protection)
</b><br>
Write 1 to start KEY comparison operation and this bit will be cleared to 0 by hardware automatically when KEY comparison operation is finished
<br>
This trigger operation is valid while FORBID (FMC_KPKEYSTS [3]) is 0.
<br>
0 = KEY comparison operation is finished.
<br>
1 = KEY comparison is progressed.
<br>
Note: This bit is write-protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[1]</td><td>TCEN</td><td><div style="word-wrap: break-word;"><b>Timeout Counting Enable (Write Protection)
</b><br>
0 = Timeout counting is disabled.
<br>
1 = Timeout counting is enabled if input key is matched after key comparison finish.
<br>
10 minutes is at least for timeout, and average is about 20 minutes.
<br>
Note: This bit is write-protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::KPKEYSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">KPKEYSTS
</font><br><p> <font size="2">
Offset: 0x60  KPROM KEY Comparison Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>KEYBUSY</td><td><div style="word-wrap: break-word;"><b>KEY Comparison Busy (Read Only)
</b><br>
0 = KEY comparison is finished.
<br>
1 = KEY comparison is busy.
<br>
</div></td></tr><tr><td>
[1]</td><td>KEYLOCK</td><td><div style="word-wrap: break-word;"><b>KEY LOCK Flag
</b><br>
This bit is set to 1 if KEYMATCH (FMC_KPKEYSTS [2]) is 0 and cleared to 0 if KEYMATCH is 1 in Security Key protection
<br>
After Mass Erase operation, users must reset or power on /off to clear this bit to 0
<br>
This bit also can be set to 1 while
<br>
  - CPU write 1 to KEYLOCK(FMC_KPKEYSTS[1]) or
<br>
  - KEYFLAG(FMC_KPKEYSTS[4]) is 1 at power-on or reset or
<br>
  - KEYENROM is programmed a non-0xFF value or
<br>
  - Timeout event or
<br>
  - FORBID(FMC_KPKEYSTS[3]) is 1
<br>
0 = KPROM, LDROM and APROM (not include Data Flash) is not in write protection.
<br>
1 = KPROM, LDROM and APROM (not include Data Flash) is in write protection.
<br>
SPROM write protect is depended on SPFLAG.
<br>
CONFIG write protect is depended on CFGFLAG
<br>
</div></td></tr><tr><td>
[2]</td><td>KEYMATCH</td><td><div style="word-wrap: break-word;"><b>KEY Match Flag (Read Only)
</b><br>
This bit is set to 1 after KEY comparison complete if the KEY0, KEY1 and KEY2 are matched with the 96-bit security keys in KPROM; and cleared to 0 if KEYs are unmatched
<br>
This bit is also cleared to 0 while
<br>
  - CPU writing 1 to KEYLOCK(FMC_KPKEYSTS[1]) or
<br>
  - Timeout event or
<br>
  - KPROM is erased or
<br>
  - KEYENROM is programmed to a non-0xFF value.
<br>
  - Chip is in power down mode.
<br>
0 = KEY0, KEY1, and KEY2 are unmatched with the KPROM setting.
<br>
1 = KEY0, KEY1, and KEY2 are matched with the KPROM setting.
<br>
</div></td></tr><tr><td>
[3]</td><td>FORBID</td><td><div style="word-wrap: break-word;"><b>KEY Comparison Forbidden Flag (Read Only)
</b><br>
This bit is set to 1 when KPKECNT(FMC_KPKEY0[4:0]) is more than KPKEMAX (FMC_KPKEY0[12:8]) or KPCNT (FMC_KPCNT [2:0]) is more than KPMAX (FMC_KPCNT [10:8]).
<br>
0 = KEY comparison is not forbidden.
<br>
1 = KEY comparison is forbidden, KEYGO (FMC_KEYTRG [0]) cannot trigger.
<br>
</div></td></tr><tr><td>
[4]</td><td>KEYFLAG</td><td><div style="word-wrap: break-word;"><b>KEY Protection Enabled Flag (Read Only)
</b><br>
This bit is set while the KEYENROM [7:0] is not 0xFF at power-on or reset
<br>
This bit is cleared to 0 by hardware while KPROM is erased
<br>
This bit is set to 1 by hardware while KEYENROM is programmed to a non-0xFF value.
<br>
0 = Security Key protection is disabled.
<br>
1 = Security Key protection is enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>CFGFLAG</td><td><div style="word-wrap: break-word;"><b>CONFIG Write-protection Enabled Flag (Read Only)
</b><br>
This bit is set while the KEYENROM [0] is 0 at power-on or reset
<br>
This bit is cleared to 0 by hardware while KPROM is erased
<br>
This bit is set to 1 by hardware while KEYENROM[0] is programmed to 0.
<br>
0 = CONFIG write-protection is disabled.
<br>
1 = CONFIG write-protection is enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>SPFLAG</td><td><div style="word-wrap: break-word;"><b>SPROM Write-protection Enabled Flag (Read Only)
</b><br>
This bit is set while the KEYENROM [1] is 0 at power-on or reset
<br>
This bit is cleared to 0 by hardware while KPROM is erased
<br>
This bit is set to 1 by hardware while KEYENROM[1] is programmed to 0.
<br>
0 = SPROM write-protection is disabled.
<br>
1 = SPROM write-protection is enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::KPKEYCNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">KPKEYCNT
</font><br><p> <font size="2">
Offset: 0x64  KPROM KEY-Unmatched Counting Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[5:0]</td><td>KPKECNT</td><td><div style="word-wrap: break-word;"><b>Error Key Entry Counter at Each Power-on (Read Only)
</b><br>
KPKECNT is increased when entry keys is wrong in Security Key protection
<br>
KPKECNT is cleared to 0 if key comparison is matched or system power-on.
<br>
</div></td></tr><tr><td>
[13:8]</td><td>KPKEMAX</td><td><div style="word-wrap: break-word;"><b>Maximum Number for Error Key Entry at Each Power-on (Read Only)
</b><br>
KPKEMAX is the maximum error key entry number at each power-on
<br>
When KPKEMAXROM of KPROM is erased or programmed, KPKEMAX will also be updated
<br>
KPKEMAX is used to limit KPKECNT(FMC_KPKEY0[5:0]) maximum counting
<br>
The FORBID (FMC_KPKEYSTS [3]) will be set to 1 when KPKECNT is more than KPKEMAX.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::KPCNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">KPCNT
</font><br><p> <font size="2">
Offset: 0x68  KPROM KEY-Unmatched Power-On Counting Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>KPCNT</td><td><div style="word-wrap: break-word;"><b>Power-on Counter for Error Key Entry(Read Only)
</b><br>
KPCNT is the power-on counting for error key entry in Security Key protection
<br>
KPCNT is cleared to 0 if key comparison is matched.
<br>
</div></td></tr><tr><td>
[11:8]</td><td>KPMAX</td><td><div style="word-wrap: break-word;"><b>Power-on Maximum Number for Error Key Entry (Read Only)
</b><br>
KPMAX is the power-on maximum number for error key entry
<br>
When KPMAXROM of KPROM is erased or programmed, KPMAX will also be updated
<br>
KPMAX is used to limit KPCNT (FMC_KPCNT [3:0]) maximum counting
<br>
The FORBID(FMC_KPKEYSTS[3]) will be set to 1 when KPCNT is more than KPMAX
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::MPDAT0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MPDAT0
</font><br><p> <font size="2">
Offset: 0x80  ISP Data0 Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>ISPDAT0</td><td><div style="word-wrap: break-word;"><b>ISP Data 0
</b><br>
This register is the first 32-bit data for 32-bit/64-bit/multi-word programming, and it is also the mirror of FMC_ISPDAT, both registers keep the same data
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::MPDAT1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MPDAT1
</font><br><p> <font size="2">
Offset: 0x84  ISP Data1 Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>ISPDAT1</td><td><div style="word-wrap: break-word;"><b>ISP Data 1
</b><br>
This register is the second 32-bit data for 64-bit/multi-word programming.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::MPDAT2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MPDAT2
</font><br><p> <font size="2">
Offset: 0x88  ISP Data2 Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>ISPDAT2</td><td><div style="word-wrap: break-word;"><b>ISP Data 2
</b><br>
This register is the third 32-bit data for multi-word programming.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::MPDAT3

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MPDAT3
</font><br><p> <font size="2">
Offset: 0x8C  ISP Data3 Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>ISPDAT3</td><td><div style="word-wrap: break-word;"><b>ISP Data 3
</b><br>
This register is the fourth 32-bit data for multi-word programming.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::MPSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MPSTS
</font><br><p> <font size="2">
Offset: 0xC0  ISP Multi-Program Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>MPBUSY</td><td><div style="word-wrap: break-word;"><b>ISP Multi-word Program Busy Flag (Read Only)
</b><br>
Write 1 to start ISP Multi-Word program operation and this bit will be cleared to 0 by hardware automatically when ISP Multi-Word program operation is finished.
<br>
This bit is the mirror of ISPGO(FMC_ISPTRG[0]).
<br>
0 = ISP Multi-Word program operation is finished.
<br>
1 = ISP Multi-Word program operation is progressed.
<br>
</div></td></tr><tr><td>
[1]</td><td>PPGO</td><td><div style="word-wrap: break-word;"><b>ISP Multi-program Status (Read Only)
</b><br>
0 = ISP multi-word program operation is not active.
<br>
1 = ISP multi-word program operation is in progress.
<br>
</div></td></tr><tr><td>
[2]</td><td>ISPFF</td><td><div style="word-wrap: break-word;"><b>ISP Fail Flag (Read Only)
</b><br>
This bit is the mirror of ISPFF (FMC_ISPCTL[6]), it needs to be cleared by writing 1 to FMC_ISPCTL[6] or FMC_ISPSTS[6]
<br>
This bit is set by hardware when a triggered ISP meets any of the following conditions:
<br>
(1) APROM writes to itself if APUEN is set to 0.
<br>
(2) LDROM writes to itself if LDUEN is set to 0.
<br>
(3) CONFIG is erased/programmed if CFGUEN is set to 0.
<br>
(4) SPROM is erased/programmed if SPUEN is set to 0
<br>
(5) SPROM is programmed at SPROM secured mode.
<br>
(6) Page Erase command at LOCK mode with ICE connection
<br>
(7) Erase or Program command at brown-out detected
<br>
(8) Destination address is illegal, such as over an available range.
<br>
(9) Invalid ISP commands
<br>
(10) Vector address is mapping to SPROM region.
<br>
</div></td></tr><tr><td>
[4]</td><td>D0</td><td><div style="word-wrap: break-word;"><b>ISP DATA 0 Flag (Read Only)
</b><br>
This bit is set when FMC_MPDAT0 is written and auto-clear to 0 when the FMC_MPDAT0 data is programmed to flash complete.
<br>
0 = FMC_MPDAT0 register is empty, or program to flash complete.
<br>
1 = FMC_MPDAT0 register has been written, and not program to flash complete.
<br>
</div></td></tr><tr><td>
[5]</td><td>D1</td><td><div style="word-wrap: break-word;"><b>ISP DATA 1 Flag (Read Only)
</b><br>
This bit is set when FMC_MPDAT1 is written and auto-clear to 0 when the FMC_MPDAT1 data is programmed to flash complete.
<br>
0 = FMC_MPDAT1 register is empty, or program to flash complete.
<br>
1 = FMC_MPDAT1 register has been written, and not program to flash complete.
<br>
</div></td></tr><tr><td>
[6]</td><td>D2</td><td><div style="word-wrap: break-word;"><b>ISP DATA 2 Flag (Read Only)
</b><br>
This bit is set when FMC_MPDAT2 is written and auto-clear to 0 when the FMC_MPDAT2 data is programmed to flash complete.
<br>
0 = FMC_MPDAT2 register is empty, or program to flash complete.
<br>
1 = FMC_MPDAT2 register has been written, and not program to flash complete.
<br>
</div></td></tr><tr><td>
[7]</td><td>D3</td><td><div style="word-wrap: break-word;"><b>ISP DATA 3 Flag (Read Only)
</b><br>
This bit is set when FMC_MPDAT3 is written and auto-clear to 0 when the FMC_MPDAT3 data is programmed to flash complete.
<br>
0 = FMC_MPDAT3 register is empty, or program to flash complete.
<br>
1 = FMC_MPDAT3 register has been written, and not program to flash complete.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var FMC_T::MPADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MPADDR
</font><br><p> <font size="2">
Offset: 0xC4  ISP Multi-Program Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>MPADDR</td><td><div style="word-wrap: break-word;"><b>ISP Multi-word Program Address
</b><br>
MPADDR is the address of ISP multi-word program operation when ISPGO flag is 1.
<br>
MPADDR will keep the final ISP address when ISP multi-word program is complete.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t ISPCTL;                /*!< [0x0000] ISP Control Register                                             */
    __IO uint32_t ISPADDR;               /*!< [0x0004] ISP Address Register                                             */
    __IO uint32_t ISPDAT;                /*!< [0x0008] ISP Data Register                                                */
    __IO uint32_t ISPCMD;                /*!< [0x000c] ISP Command Register                                             */
    __IO uint32_t ISPTRG;                /*!< [0x0010] ISP Trigger Control Register                                     */
    __I  uint32_t DFBA;                  /*!< [0x0014] Data Flash Base Address                                          */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[10];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t ISPSTS;                /*!< [0x0040] ISP Status Register                                              */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[2];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t CYCCTL;                /*!< [0x004c] Flash Access Cycle Control Register                              */
    __O  uint32_t KPKEY0;                /*!< [0x0050] KPROM KEY0 Data Register                                         */
    __O  uint32_t KPKEY1;                /*!< [0x0054] KPROM KEY1 Data Register                                         */
    __O  uint32_t KPKEY2;                /*!< [0x0058] KPROM KEY2 Data Register                                         */
    __IO uint32_t KPKEYTRG;              /*!< [0x005c] KPROM KEY Comparison Trigger Control Register                    */
    __IO uint32_t KPKEYSTS;              /*!< [0x0060] KPROM KEY Comparison Status Register                             */
    __I  uint32_t KPKEYCNT;              /*!< [0x0064] KPROM KEY-Unmatched Counting Register                            */
    __I  uint32_t KPCNT;                 /*!< [0x0068] KPROM KEY-Unmatched Power-On Counting Register                   */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE2[5];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t MPDAT0;                /*!< [0x0080] ISP Data0 Register                                               */
    __IO uint32_t MPDAT1;                /*!< [0x0084] ISP Data1 Register                                               */
    __IO uint32_t MPDAT2;                /*!< [0x0088] ISP Data2 Register                                               */
    __IO uint32_t MPDAT3;                /*!< [0x008c] ISP Data3 Register                                               */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE3[12];
    /// @endcond //HIDDEN_SYMBOLS
    __I  uint32_t MPSTS;                 /*!< [0x00c0] ISP Multi-Program Status Register                                */
    __I  uint32_t MPADDR;                /*!< [0x00c4] ISP Multi-Program Address Register                               */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE4[2];
    /// @endcond //HIDDEN_SYMBOLS
    __I  uint32_t XOMR0STS;              /*!< [0x00d0] XOM Region 0 Status Register                                     */
    __I  uint32_t XOMR1STS;              /*!< [0x00d4] XOM Region 1 Status Register                                     */
    __I  uint32_t XOMR2STS;              /*!< [0x00d8] XOM Region 2 Status Register                                     */
    __I  uint32_t XOMR3STS;              /*!< [0x00dc] XOM Region 3 Status Register                                     */
    __I  uint32_t XOMSTS;                /*!< [0x00e0] XOM Status Register                                              */

} FMC_T;

/**
    @addtogroup FMC_CONST FMC Bit Field Definition
    Constant Definitions for FMC Controller
@{ */

#define FMC_ISPCTL_ISPEN_Pos             (0)                                               /*!< FMC_T::ISPCTL: ISPEN Position          */
#define FMC_ISPCTL_ISPEN_Msk             (0x1ul << FMC_ISPCTL_ISPEN_Pos)                   /*!< FMC_T::ISPCTL: ISPEN Mask              */

#define FMC_ISPCTL_BS_Pos                (1)                                               /*!< FMC_T::ISPCTL: BS Position             */
#define FMC_ISPCTL_BS_Msk                (0x1ul << FMC_ISPCTL_BS_Pos)                      /*!< FMC_T::ISPCTL: BS Mask                 */

#define FMC_ISPCTL_SPUEN_Pos             (2)                                               /*!< FMC_T::ISPCTL: SPUEN Position          */
#define FMC_ISPCTL_SPUEN_Msk             (0x1ul << FMC_ISPCTL_SPUEN_Pos)                   /*!< FMC_T::ISPCTL: SPUEN Mask              */

#define FMC_ISPCTL_APUEN_Pos             (3)                                               /*!< FMC_T::ISPCTL: APUEN Position          */
#define FMC_ISPCTL_APUEN_Msk             (0x1ul << FMC_ISPCTL_APUEN_Pos)                   /*!< FMC_T::ISPCTL: APUEN Mask              */

#define FMC_ISPCTL_CFGUEN_Pos            (4)                                               /*!< FMC_T::ISPCTL: CFGUEN Position         */
#define FMC_ISPCTL_CFGUEN_Msk            (0x1ul << FMC_ISPCTL_CFGUEN_Pos)                  /*!< FMC_T::ISPCTL: CFGUEN Mask             */

#define FMC_ISPCTL_LDUEN_Pos             (5)                                               /*!< FMC_T::ISPCTL: LDUEN Position          */
#define FMC_ISPCTL_LDUEN_Msk             (0x1ul << FMC_ISPCTL_LDUEN_Pos)                   /*!< FMC_T::ISPCTL: LDUEN Mask              */

#define FMC_ISPCTL_ISPFF_Pos             (6)                                               /*!< FMC_T::ISPCTL: ISPFF Position          */
#define FMC_ISPCTL_ISPFF_Msk             (0x1ul << FMC_ISPCTL_ISPFF_Pos)                   /*!< FMC_T::ISPCTL: ISPFF Mask              */

#define FMC_ISPCTL_BL_Pos                (16)                                              /*!< FMC_T::ISPCTL: BL Position             */
#define FMC_ISPCTL_BL_Msk                (0x1ul << FMC_ISPCTL_BL_Pos)                      /*!< FMC_T::ISPCTL: BL Mask                 */

#define FMC_ISPADDR_ISPADDR_Pos          (0)                                               /*!< FMC_T::ISPADDR: ISPADDR Position       */
#define FMC_ISPADDR_ISPADDR_Msk          (0xfffffffful << FMC_ISPADDR_ISPADDR_Pos)         /*!< FMC_T::ISPADDR: ISPADDR Mask           */

#define FMC_ISPDAT_ISPDAT_Pos            (0)                                               /*!< FMC_T::ISPDAT: ISPDAT Position         */
#define FMC_ISPDAT_ISPDAT_Msk            (0xfffffffful << FMC_ISPDAT_ISPDAT_Pos)           /*!< FMC_T::ISPDAT: ISPDAT Mask             */

#define FMC_ISPCMD_CMD_Pos               (0)                                               /*!< FMC_T::ISPCMD: CMD Position            */
#define FMC_ISPCMD_CMD_Msk               (0x7ful << FMC_ISPCMD_CMD_Pos)                    /*!< FMC_T::ISPCMD: CMD Mask                */

#define FMC_ISPTRG_ISPGO_Pos             (0)                                               /*!< FMC_T::ISPTRG: ISPGO Position          */
#define FMC_ISPTRG_ISPGO_Msk             (0x1ul << FMC_ISPTRG_ISPGO_Pos)                   /*!< FMC_T::ISPTRG: ISPGO Mask              */

#define FMC_DFBA_DFBA_Pos                (0)                                               /*!< FMC_T::DFBA: DFBA Position             */
#define FMC_DFBA_DFBA_Msk                (0xfffffffful << FMC_DFBA_DFBA_Pos)               /*!< FMC_T::DFBA: DFBA Mask                 */

#define FMC_ISPSTS_ISPBUSY_Pos           (0)                                               /*!< FMC_T::ISPSTS: ISPBUSY Position        */
#define FMC_ISPSTS_ISPBUSY_Msk           (0x1ul << FMC_ISPSTS_ISPBUSY_Pos)                 /*!< FMC_T::ISPSTS: ISPBUSY Mask            */

#define FMC_ISPSTS_CBS_Pos               (1)                                               /*!< FMC_T::ISPSTS: CBS Position            */
#define FMC_ISPSTS_CBS_Msk               (0x3ul << FMC_ISPSTS_CBS_Pos)                     /*!< FMC_T::ISPSTS: CBS Mask                */

#define FMC_ISPSTS_MBS_Pos               (3)                                               /*!< FMC_T::ISPSTS: MBS Position            */
#define FMC_ISPSTS_MBS_Msk               (0x1ul << FMC_ISPSTS_MBS_Pos)                     /*!< FMC_T::ISPSTS: MBS Mask                */

#define FMC_ISPSTS_FCYCDIS_Pos           (4)                                               /*!< FMC_T::ISPSTS: FCYCDIS Position        */
#define FMC_ISPSTS_FCYCDIS_Msk           (0x1ul << FMC_ISPSTS_FCYCDIS_Pos)                 /*!< FMC_T::ISPSTS: FCYCDIS Mask            */

#define FMC_ISPSTS_PGFF_Pos              (5)                                               /*!< FMC_T::ISPSTS: PGFF Position           */
#define FMC_ISPSTS_PGFF_Msk              (0x1ul << FMC_ISPSTS_PGFF_Pos)                    /*!< FMC_T::ISPSTS: PGFF Mask               */

#define FMC_ISPSTS_ISPFF_Pos             (6)                                               /*!< FMC_T::ISPSTS: ISPFF Position          */
#define FMC_ISPSTS_ISPFF_Msk             (0x1ul << FMC_ISPSTS_ISPFF_Pos)                   /*!< FMC_T::ISPSTS: ISPFF Mask              */

#define FMC_ISPSTS_ALLONE_Pos            (7)                                               /*!< FMC_T::ISPSTS: ALLONE Position         */
#define FMC_ISPSTS_ALLONE_Msk            (0x1ul << FMC_ISPSTS_ALLONE_Pos)                  /*!< FMC_T::ISPSTS: ALLONE Mask             */

#define FMC_ISPSTS_VECMAP_Pos            (9)                                               /*!< FMC_T::ISPSTS: VECMAP Position         */
#define FMC_ISPSTS_VECMAP_Msk            (0x7ffful << FMC_ISPSTS_VECMAP_Pos)               /*!< FMC_T::ISPSTS: VECMAP Mask             */

#define FMC_ISPSTS_SCODE_Pos             (31)                                              /*!< FMC_T::ISPSTS: SCODE Position          */
#define FMC_ISPSTS_SCODE_Msk             (0x1ul << FMC_ISPSTS_SCODE_Pos)                   /*!< FMC_T::ISPSTS: SCODE Mask              */

#define FMC_CYCCTL_CYCLE_Pos             (0)                                               /*!< FMC_T::CYCCTL: CYCLE Position          */
#define FMC_CYCCTL_CYCLE_Msk             (0xful << FMC_CYCCTL_CYCLE_Pos)                   /*!< FMC_T::CYCCTL: CYCLE Mask              */

#define FMC_KPKEY0_KPKEY0_Pos            (0)                                               /*!< FMC_T::KPKEY0: KPKEY0 Position         */
#define FMC_KPKEY0_KPKEY0_Msk            (0xfffffffful << FMC_KPKEY0_KPKEY0_Pos)           /*!< FMC_T::KPKEY0: KPKEY0 Mask             */

#define FMC_KPKEY1_KPKEY1_Pos            (0)                                               /*!< FMC_T::KPKEY1: KPKEY1 Position         */
#define FMC_KPKEY1_KPKEY1_Msk            (0xfffffffful << FMC_KPKEY1_KPKEY1_Pos)           /*!< FMC_T::KPKEY1: KPKEY1 Mask             */

#define FMC_KPKEY2_KPKEY2_Pos            (0)                                               /*!< FMC_T::KPKEY2: KPKEY2 Position         */
#define FMC_KPKEY2_KPKEY2_Msk            (0xfffffffful << FMC_KPKEY2_KPKEY2_Pos)           /*!< FMC_T::KPKEY2: KPKEY2 Mask             */

#define FMC_KPKEYTRG_KPKEYGO_Pos         (0)                                               /*!< FMC_T::KPKEYTRG: KPKEYGO Position      */
#define FMC_KPKEYTRG_KPKEYGO_Msk         (0x1ul << FMC_KPKEYTRG_KPKEYGO_Pos)               /*!< FMC_T::KPKEYTRG: KPKEYGO Mask          */

#define FMC_KPKEYTRG_TCEN_Pos            (1)                                               /*!< FMC_T::KPKEYTRG: TCEN Position         */
#define FMC_KPKEYTRG_TCEN_Msk            (0x1ul << FMC_KPKEYTRG_TCEN_Pos)                  /*!< FMC_T::KPKEYTRG: TCEN Mask             */

#define FMC_KPKEYSTS_KEYBUSY_Pos         (0)                                               /*!< FMC_T::KPKEYSTS: KEYBUSY Position      */
#define FMC_KPKEYSTS_KEYBUSY_Msk         (0x1ul << FMC_KPKEYSTS_KEYBUSY_Pos)               /*!< FMC_T::KPKEYSTS: KEYBUSY Mask          */

#define FMC_KPKEYSTS_KEYLOCK_Pos         (1)                                               /*!< FMC_T::KPKEYSTS: KEYLOCK Position      */
#define FMC_KPKEYSTS_KEYLOCK_Msk         (0x1ul << FMC_KPKEYSTS_KEYLOCK_Pos)               /*!< FMC_T::KPKEYSTS: KEYLOCK Mask          */

#define FMC_KPKEYSTS_KEYMATCH_Pos        (2)                                               /*!< FMC_T::KPKEYSTS: KEYMATCH Position     */
#define FMC_KPKEYSTS_KEYMATCH_Msk        (0x1ul << FMC_KPKEYSTS_KEYMATCH_Pos)              /*!< FMC_T::KPKEYSTS: KEYMATCH Mask         */

#define FMC_KPKEYSTS_FORBID_Pos          (3)                                               /*!< FMC_T::KPKEYSTS: FORBID Position       */
#define FMC_KPKEYSTS_FORBID_Msk          (0x1ul << FMC_KPKEYSTS_FORBID_Pos)                /*!< FMC_T::KPKEYSTS: FORBID Mask           */

#define FMC_KPKEYSTS_KEYFLAG_Pos         (4)                                               /*!< FMC_T::KPKEYSTS: KEYFLAG Position      */
#define FMC_KPKEYSTS_KEYFLAG_Msk         (0x1ul << FMC_KPKEYSTS_KEYFLAG_Pos)               /*!< FMC_T::KPKEYSTS: KEYFLAG Mask          */

#define FMC_KPKEYSTS_CFGFLAG_Pos         (5)                                               /*!< FMC_T::KPKEYSTS: CFGFLAG Position      */
#define FMC_KPKEYSTS_CFGFLAG_Msk         (0x1ul << FMC_KPKEYSTS_CFGFLAG_Pos)               /*!< FMC_T::KPKEYSTS: CFGFLAG Mask          */

#define FMC_KPKEYSTS_SPFLAG_Pos          (6)                                               /*!< FMC_T::KPKEYSTS: SPFLAG Position       */
#define FMC_KPKEYSTS_SPFLAG_Msk          (0x1ul << FMC_KPKEYSTS_SPFLAG_Pos)                /*!< FMC_T::KPKEYSTS: SPFLAG Mask           */

#define FMC_KPKEYCNT_KPKECNT_Pos         (0)                                               /*!< FMC_T::KPKEYCNT: KPKECNT Position      */
#define FMC_KPKEYCNT_KPKECNT_Msk         (0x3ful << FMC_KPKEYCNT_KPKECNT_Pos)              /*!< FMC_T::KPKEYCNT: KPKECNT Mask          */

#define FMC_KPKEYCNT_KPKEMAX_Pos         (8)                                               /*!< FMC_T::KPKEYCNT: KPKEMAX Position      */
#define FMC_KPKEYCNT_KPKEMAX_Msk         (0x3ful << FMC_KPKEYCNT_KPKEMAX_Pos)              /*!< FMC_T::KPKEYCNT: KPKEMAX Mask          */

#define FMC_KPCNT_KPCNT_Pos              (0)                                               /*!< FMC_T::KPCNT: KPCNT Position           */
#define FMC_KPCNT_KPCNT_Msk              (0xful << FMC_KPCNT_KPCNT_Pos)                    /*!< FMC_T::KPCNT: KPCNT Mask               */

#define FMC_KPCNT_KPMAX_Pos              (8)                                               /*!< FMC_T::KPCNT: KPMAX Position           */
#define FMC_KPCNT_KPMAX_Msk              (0xful << FMC_KPCNT_KPMAX_Pos)                    /*!< FMC_T::KPCNT: KPMAX Mask               */

#define FMC_MPDAT0_ISPDAT0_Pos           (0)                                               /*!< FMC_T::MPDAT0: ISPDAT0 Position        */
#define FMC_MPDAT0_ISPDAT0_Msk           (0xfffffffful << FMC_MPDAT0_ISPDAT0_Pos)          /*!< FMC_T::MPDAT0: ISPDAT0 Mask            */

#define FMC_MPDAT1_ISPDAT1_Pos           (0)                                               /*!< FMC_T::MPDAT1: ISPDAT1 Position        */
#define FMC_MPDAT1_ISPDAT1_Msk           (0xfffffffful << FMC_MPDAT1_ISPDAT1_Pos)          /*!< FMC_T::MPDAT1: ISPDAT1 Mask            */

#define FMC_MPDAT2_ISPDAT2_Pos           (0)                                               /*!< FMC_T::MPDAT2: ISPDAT2 Position        */
#define FMC_MPDAT2_ISPDAT2_Msk           (0xfffffffful << FMC_MPDAT2_ISPDAT2_Pos)          /*!< FMC_T::MPDAT2: ISPDAT2 Mask            */

#define FMC_MPDAT3_ISPDAT3_Pos           (0)                                               /*!< FMC_T::MPDAT3: ISPDAT3 Position        */
#define FMC_MPDAT3_ISPDAT3_Msk           (0xfffffffful << FMC_MPDAT3_ISPDAT3_Pos)          /*!< FMC_T::MPDAT3: ISPDAT3 Mask            */

#define FMC_MPSTS_MPBUSY_Pos             (0)                                               /*!< FMC_T::MPSTS: MPBUSY Position          */
#define FMC_MPSTS_MPBUSY_Msk             (0x1ul << FMC_MPSTS_MPBUSY_Pos)                   /*!< FMC_T::MPSTS: MPBUSY Mask              */

#define FMC_MPSTS_PPGO_Pos               (1)                                               /*!< FMC_T::MPSTS: PPGO Position            */
#define FMC_MPSTS_PPGO_Msk               (0x1ul << FMC_MPSTS_PPGO_Pos)                     /*!< FMC_T::MPSTS: PPGO Mask                */

#define FMC_MPSTS_ISPFF_Pos              (2)                                               /*!< FMC_T::MPSTS: ISPFF Position           */
#define FMC_MPSTS_ISPFF_Msk              (0x1ul << FMC_MPSTS_ISPFF_Pos)                    /*!< FMC_T::MPSTS: ISPFF Mask               */

#define FMC_MPSTS_D0_Pos                 (4)                                               /*!< FMC_T::MPSTS: D0 Position              */
#define FMC_MPSTS_D0_Msk                 (0x1ul << FMC_MPSTS_D0_Pos)                       /*!< FMC_T::MPSTS: D0 Mask                  */

#define FMC_MPSTS_D1_Pos                 (5)                                               /*!< FMC_T::MPSTS: D1 Position              */
#define FMC_MPSTS_D1_Msk                 (0x1ul << FMC_MPSTS_D1_Pos)                       /*!< FMC_T::MPSTS: D1 Mask                  */

#define FMC_MPSTS_D2_Pos                 (6)                                               /*!< FMC_T::MPSTS: D2 Position              */
#define FMC_MPSTS_D2_Msk                 (0x1ul << FMC_MPSTS_D2_Pos)                       /*!< FMC_T::MPSTS: D2 Mask                  */

#define FMC_MPSTS_D3_Pos                 (7)                                               /*!< FMC_T::MPSTS: D3 Position              */
#define FMC_MPSTS_D3_Msk                 (0x1ul << FMC_MPSTS_D3_Pos)                       /*!< FMC_T::MPSTS: D3 Mask                  */

#define FMC_MPADDR_MPADDR_Pos            (0)                                               /*!< FMC_T::MPADDR: MPADDR Position         */
#define FMC_MPADDR_MPADDR_Msk            (0xfffffffful << FMC_MPADDR_MPADDR_Pos)           /*!< FMC_T::MPADDR: MPADDR Mask             */

#define FMC_XOMR0STS_SIZE_Pos            (0)                                               /*!< FMC_T::XOMR0STS: SIZE Position         */
#define FMC_XOMR0STS_SIZE_Msk            (0xfful << FMC_XOMR0STS_SIZE_Pos)                 /*!< FMC_T::XOMR0STS: SIZE Mask             */

#define FMC_XOMR0STS_BASE_Pos            (8)                                               /*!< FMC_T::XOMR0STS: BASE Position         */
#define FMC_XOMR0STS_BASE_Msk            (0xfffffful << FMC_XOMR0STS_BASE_Pos)             /*!< FMC_T::XOMR0STS: BASE Mask             */

#define FMC_XOMR1STS_SIZE_Pos            (0)                                               /*!< FMC_T::XOMR1STS: SIZE Position         */
#define FMC_XOMR1STS_SIZE_Msk            (0xfful << FMC_XOMR1STS_SIZE_Pos)                 /*!< FMC_T::XOMR1STS: SIZE Mask             */

#define FMC_XOMR1STS_BASE_Pos            (8)                                               /*!< FMC_T::XOMR1STS: BASE Position         */
#define FMC_XOMR1STS_BASE_Msk            (0xfffffful << FMC_XOMR1STS_BASE_Pos)             /*!< FMC_T::XOMR1STS: BASE Mask             */

#define FMC_XOMR2STS_SIZE_Pos            (0)                                               /*!< FMC_T::XOMR2STS: SIZE Position         */
#define FMC_XOMR2STS_SIZE_Msk            (0xfful << FMC_XOMR2STS_SIZE_Pos)                 /*!< FMC_T::XOMR2STS: SIZE Mask             */

#define FMC_XOMR2STS_BASE_Pos            (8)                                               /*!< FMC_T::XOMR2STS: BASE Position         */
#define FMC_XOMR2STS_BASE_Msk            (0xfffffful << FMC_XOM20STS_BASE_Pos)             /*!< FMC_T::XOMR2STS: BASE Mask             */

#define FMC_XOMR3STS_SIZE_Pos            (0)                                               /*!< FMC_T::XOMR3STS: SIZE Position         */
#define FMC_XOMR3STS_SIZE_Msk            (0xfful << FMC_XOMR3STS_SIZE_Pos)                 /*!< FMC_T::XOMR3STS: SIZE Mask             */

#define FMC_XOMR3STS_BASE_Pos            (8)                                               /*!< FMC_T::XOMR3STS: BASE Position         */
#define FMC_XOMR3STS_BASE_Msk            (0xfffffful << FMC_XOMR3STS_BASE_Pos)             /*!< FMC_T::XOMR3STS: BASE Mask             */

#define FMC_XOMSTS_XOMR0ON_Pos           (0)                                               /*!< FMC_T::XOMSTS: XOMR0ON Position        */
#define FMC_XOMSTS_XOMR0ON_Msk           (0x1ul << FMC_XOMSTS_XOMR0ON_Pos)                 /*!< FMC_T::XOMSTS: XOMR0ON Mask            */

#define FMC_XOMSTS_XOMR1ON_Pos           (1)                                               /*!< FMC_T::XOMSTS: XOMR1ON Position        */
#define FMC_XOMSTS_XOMR1ON_Msk           (0x1ul << FMC_XOMSTS_XOMR1ON_Pos)                 /*!< FMC_T::XOMSTS: XOMR1ON Mask            */

#define FMC_XOMSTS_XOMR2ON_Pos           (2)                                               /*!< FMC_T::XOMSTS: XOMR2ON Position        */
#define FMC_XOMSTS_XOMR2ON_Msk           (0x1ul << FMC_XOMSTS_XOMR2ON_Pos)                 /*!< FMC_T::XOMSTS: XOMR2ON Mask            */

#define FMC_XOMSTS_XOMR3ON_Pos           (3)                                               /*!< FMC_T::XOMSTS: XOMR3ON Position        */
#define FMC_XOMSTS_XOMR3ON_Msk           (0x1ul << FMC_XOMSTS_XOMR3ON_Pos)                 /*!< FMC_T::XOMSTS: XOMR3ON Mask            */

#define FMC_XOMSTS_XOMPEF_Pos            (4)                                               /*!< FMC_T::XOMSTS: XOMPEF Position         */
#define FMC_XOMSTS_XOMPEF_Msk            (0x1ul << FMC_XOMSTS_XOMPEF_Pos)                  /*!< FMC_T::XOMSTS: XOMPEF Mask             */

/**@}*/ /* FMC_CONST */
/**@}*/ /* end of FMC register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __FMC_REG_H__ */
