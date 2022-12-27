/**************************************************************************//**
 * @file     crc_reg.h
 * @version  V1.00
 * @brief    CRC register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __CRC_REG_H__
#define __CRC_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup CRC Cyclic Redundancy Check Controller(CRC)
    Memory Mapped Structure for CRC Controller
@{ */

typedef struct
{


    /**
@var CRC_T::CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL
</font><br><p> <font size="2">
Offset: 0x00  CRC Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CRCEN</td><td><div style="word-wrap: break-word;"><b>CRC Channel Enable Bit
</b><br>
0 = No effect.
<br>
1 = CRC operation Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>CHKSINIT</td><td><div style="word-wrap: break-word;"><b>Checksum Initialization
</b><br>
0 = No effect.
<br>
1 = Initial checksum value by auto reload CRC_SEED register value to CRC_CHECKSUM register value.
<br>
Note: This bit will be cleared automatically.
<br>
</div></td></tr><tr><td>
[24]</td><td>DATREV</td><td><div style="word-wrap: break-word;"><b>Write Data Bit Order Reverse
</b><br>
This bit is used to enable the bit order reverse function per byte for write data value in CRC_DAT register.
<br>
0 = Bit order reversed for CRC write data in Disabled.
<br>
1 = Bit order reversed for CRC write data in Enabled (per byte).
<br>
Note: If the write data is 0xAABBCCDD, the bit order reverse for CRC write data in is 0x55DD33BB.
<br>
</div></td></tr><tr><td>
[25]</td><td>CHKSREV</td><td><div style="word-wrap: break-word;"><b>Checksum Bit Order Reverse
</b><br>
This bit is used to enable the bit order reverse function for checksum result in CRC_CHECKSUM register.
<br>
0 = Bit order reverse for CRC checksum Disabled.
<br>
1 = Bit order reverse for CRC checksum Enabled.
<br>
Note: If the checksum result is 0xDD7B0F2E, the bit order reverse for CRC checksum is 0x74F0DEBB.
<br>
</div></td></tr><tr><td>
[26]</td><td>DATFMT</td><td><div style="word-wrap: break-word;"><b>Write Data 1's Complement
</b><br>
This bit is used to enable the 1's complement function for write data value in CRC_DAT register.
<br>
0 = 1's complement for CRC writes data in Disabled.
<br>
1 = 1's complement for CRC writes data in Enabled.
<br>
</div></td></tr><tr><td>
[27]</td><td>CHKSFMT</td><td><div style="word-wrap: break-word;"><b>Checksum 1's Complement
</b><br>
This bit is used to enable the 1's complement function for checksum result in CRC_CHECKSUM register.
<br>
0 = 1's complement for CRC checksum Disabled.
<br>
1 = 1's complement for CRC checksum Enabled.
<br>
</div></td></tr><tr><td>
[29:28]</td><td>DATLEN</td><td><div style="word-wrap: break-word;"><b>CPU Write Data Length
</b><br>
This field indicates the write data length.
<br>
00 = Data length is 8-bit mode.
<br>
01 = Data length is 16-bit mode.
<br>
1x = Data length is 32-bit mode.
<br>
Note: When the write data length is 8-bit mode, the valid data in CRC_DAT register is only DATA[7:0] bits; if the write data length is 16-bit mode, the valid data in CRC_DAT register is only DATA[15:0]
<br>
</div></td></tr><tr><td>
[31:30]</td><td>CRCMODE</td><td><div style="word-wrap: break-word;"><b>CRC Polynomial Mode
</b><br>
This field indicates the CRC operation polynomial mode.
<br>
00 = CRC-CCITT Polynomial mode.
<br>
01 = CRC-8 Polynomial mode.
<br>
10 = CRC-16 Polynomial mode.
<br>
11 = CRC-32 Polynomial mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRC_T::DAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DAT
</font><br><p> <font size="2">
Offset: 0x04  CRC Write Data Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DATA</td><td><div style="word-wrap: break-word;"><b>CRC Write Data Bits
</b><br>
User can write data directly by CPU mode or use PDMA function to write data to this field to perform CRC operation.
<br>
Note: When the write data length is 8-bit mode, the valid data in CRC_DAT register is only DATA[7:0] bits; if the write data length is 16-bit mode, the valid data in CRC_DAT register is only DATA[15:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRC_T::SEED

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SEED
</font><br><p> <font size="2">
Offset: 0x08  CRC Seed Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SEED</td><td><div style="word-wrap: break-word;"><b>CRC Seed Value
</b><br>
This field indicates the CRC seed value.
<br>
Note: This field will be reloaded as checksum initial value (CRC_CHECKSUM register) after perform CHKSINIT (CRC_CTL[1]).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CRC_T::CHECKSUM

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CHECKSUM
</font><br><p> <font size="2">
Offset: 0x0C  CRC Checksum Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>CHECKSUM</td><td><div style="word-wrap: break-word;"><b>CRC Checksum Results
</b><br>
This field indicates the CRC checksum result.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CTL;                   /*!< [0x0000] CRC Control Register                                             */
    __IO uint32_t DAT;                   /*!< [0x0004] CRC Write Data Register                                          */
    __IO uint32_t SEED;                  /*!< [0x0008] CRC Seed Register                                                */
    __I  uint32_t CHECKSUM;              /*!< [0x000c] CRC Checksum Register                                            */

} CRC_T;

/**
    @addtogroup CRC_CONST CRC Bit Field Definition
    Constant Definitions for CRC Controller
@{ */

#define CRC_CTL_CRCEN_Pos                (0)                                               /*!< CRC_T::CTL: CRCEN Position             */
#define CRC_CTL_CRCEN_Msk                (0x1ul << CRC_CTL_CRCEN_Pos)                      /*!< CRC_T::CTL: CRCEN Mask                 */

#define CRC_CTL_CHKSINIT_Pos             (1)                                               /*!< CRC_T::CTL: CHKSINIT Position          */
#define CRC_CTL_CHKSINIT_Msk             (0x1ul << CRC_CTL_CHKSINIT_Pos)                   /*!< CRC_T::CTL: CHKSINIT Mask              */

#define CRC_CTL_DATREV_Pos               (24)                                              /*!< CRC_T::CTL: DATREV Position            */
#define CRC_CTL_DATREV_Msk               (0x1ul << CRC_CTL_DATREV_Pos)                     /*!< CRC_T::CTL: DATREV Mask                */

#define CRC_CTL_CHKSREV_Pos              (25)                                              /*!< CRC_T::CTL: CHKSREV Position           */
#define CRC_CTL_CHKSREV_Msk              (0x1ul << CRC_CTL_CHKSREV_Pos)                    /*!< CRC_T::CTL: CHKSREV Mask               */

#define CRC_CTL_DATFMT_Pos               (26)                                              /*!< CRC_T::CTL: DATFMT Position            */
#define CRC_CTL_DATFMT_Msk               (0x1ul << CRC_CTL_DATFMT_Pos)                     /*!< CRC_T::CTL: DATFMT Mask                */

#define CRC_CTL_CHKSFMT_Pos              (27)                                              /*!< CRC_T::CTL: CHKSFMT Position           */
#define CRC_CTL_CHKSFMT_Msk              (0x1ul << CRC_CTL_CHKSFMT_Pos)                    /*!< CRC_T::CTL: CHKSFMT Mask               */

#define CRC_CTL_DATLEN_Pos               (28)                                              /*!< CRC_T::CTL: DATLEN Position            */
#define CRC_CTL_DATLEN_Msk               (0x3ul << CRC_CTL_DATLEN_Pos)                     /*!< CRC_T::CTL: DATLEN Mask                */

#define CRC_CTL_CRCMODE_Pos              (30)                                              /*!< CRC_T::CTL: CRCMODE Position           */
#define CRC_CTL_CRCMODE_Msk              (0x3ul << CRC_CTL_CRCMODE_Pos)                    /*!< CRC_T::CTL: CRCMODE Mask               */

#define CRC_DAT_DATA_Pos                 (0)                                               /*!< CRC_T::DAT: DATA Position              */
#define CRC_DAT_DATA_Msk                 (0xfffffffful << CRC_DAT_DATA_Pos)                /*!< CRC_T::DAT: DATA Mask                  */

#define CRC_SEED_SEED_Pos                (0)                                               /*!< CRC_T::SEED: SEED Position             */
#define CRC_SEED_SEED_Msk                (0xfffffffful << CRC_SEED_SEED_Pos)               /*!< CRC_T::SEED: SEED Mask                 */

#define CRC_CHECKSUM_CHECKSUM_Pos        (0)                                               /*!< CRC_T::CHECKSUM: CHECKSUM Position     */
#define CRC_CHECKSUM_CHECKSUM_Msk        (0xfffffffful << CRC_CHECKSUM_CHECKSUM_Pos)       /*!< CRC_T::CHECKSUM: CHECKSUM Mask         */

/**@}*/ /* CRC_CONST */
/**@}*/ /* end of CRC register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __CRC_REG_H__ */
