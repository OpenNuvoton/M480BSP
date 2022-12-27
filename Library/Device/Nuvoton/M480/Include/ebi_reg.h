/**************************************************************************//**
 * @file     ebi_reg.h
 * @version  V1.00
 * @brief    EBI register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __EBI_REG_H__
#define __EBI_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup EBI External Bus Interface Controller(EBI)
    Memory Mapped Structure for EBI Controller
@{ */

typedef struct
{


    /**
@var EBI_T::CTL0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL0
</font><br><p> <font size="2">
Offset: 0x00  External Bus Interface Bank0 Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>EN</td><td><div style="word-wrap: break-word;"><b>EBI Enable Bit
</b><br>
This bit is the functional enable bit for EBI.
<br>
0 = EBI function Disabled.
<br>
1 = EBI function Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>DW16</td><td><div style="word-wrap: break-word;"><b>EBI Data Width 16-bit Select
</b><br>
This bit defines if the EBI data width is 8-bit or 16-bit.
<br>
0 = EBI data width is 8-bit.
<br>
1 = EBI data width is 16-bit.
<br>
</div></td></tr><tr><td>
[2]</td><td>CSPOLINV</td><td><div style="word-wrap: break-word;"><b>Chip Select Pin Polar Inverse
</b><br>
This bit defines the active level of EBI chip select pin (EBI_nCS).
<br>
0 = Chip select pin (EBI_nCS) is active low.
<br>
1 = Chip select pin (EBI_nCS) is active high.
<br>
</div></td></tr><tr><td>
[3]</td><td>ADSEPEN</td><td><div style="word-wrap: break-word;"><b>EBI Address/Data Bus Separating Mode Enable Bit
</b><br>
0 = Address/Data Bus Separating Mode Disabled.
<br>
1 = Address/Data Bus Separating Mode Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>CACCESS</td><td><div style="word-wrap: break-word;"><b>Continuous Data Access Mode
</b><br>
When con tenuous access mode enabled, the tASU, tALE and tLHD cycles are bypass for continuous data transfer request.
<br>
0 = Continuous data access mode Disabled.
<br>
1 = Continuous data access mode Enabled.
<br>
</div></td></tr><tr><td>
[10:8]</td><td>MCLKDIV</td><td><div style="word-wrap: break-word;"><b>External Output Clock Divider
</b><br>
The frequency of EBI output clock (MCLK) is controlled by MCLKDIV as follow:
<br>
000 = HCLK/1.
<br>
001 = HCLK/2.
<br>
010 = HCLK/4.
<br>
011 = HCLK/8.
<br>
100 = HCLK/16.
<br>
101 = HCLK/32.
<br>
110 = HCLK/64.
<br>
111 = HCLK/128.
<br>
</div></td></tr><tr><td>
[18:16]</td><td>TALE</td><td><div style="word-wrap: break-word;"><b>Extend Time of ALE
</b><br>
The EBI_ALE high pulse period (tALE) to latch the address can be controlled by TALE.
<br>
tALE = (TALE+1)*EBI_MCLK.
<br>
Note: This field only available in EBI_CTL0 register
<br>
</div></td></tr><tr><td>
[24]</td><td>WBUFEN</td><td><div style="word-wrap: break-word;"><b>EBI Write Buffer Enable Bit
</b><br>
0 = EBI write buffer Disabled.
<br>
1 = EBI write buffer Enabled.
<br>
Note: This bit only available in EBI_CTL0 register
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EBI_T::TCTL0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TCTL0
</font><br><p> <font size="2">
Offset: 0x04  External Bus Interface Bank0 Timing Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:3]</td><td>TACC</td><td><div style="word-wrap: break-word;"><b>EBI Data Access Time
</b><br>
TACC define data access time (tACC).
<br>
tACC = (TACC +1) * EBI_MCLK.
<br>
</div></td></tr><tr><td>
[10:8]</td><td>TAHD</td><td><div style="word-wrap: break-word;"><b>EBI Data Access Hold Time
</b><br>
TAHD define data access hold time (tAHD).
<br>
tAHD = (TAHD +1) * EBI_MCLK.
<br>
</div></td></tr><tr><td>
[15:12]</td><td>W2X</td><td><div style="word-wrap: break-word;"><b>Idle Cycle After Write
</b><br>
This field defines the number of W2X idle cycle.
<br>
W2X idle cycle = (W2X * EBI_MCLK).
<br>
When write action is finish, W2X idle cycle is inserted and EBI_nCS return to idle state.
<br>
</div></td></tr><tr><td>
[22]</td><td>RAHDOFF</td><td><div style="word-wrap: break-word;"><b>Access Hold Time Disable Control When Read
</b><br>
0 = The Data Access Hold Time (tAHD) during EBI reading is Enabled.
<br>
1 = The Data Access Hold Time (tAHD) during EBI reading is Disabled.
<br>
</div></td></tr><tr><td>
[23]</td><td>WAHDOFF</td><td><div style="word-wrap: break-word;"><b>Access Hold Time Disable Control When Write
</b><br>
0 = The Data Access Hold Time (tAHD) during EBI writing is Enabled.
<br>
1 = The Data Access Hold Time (tAHD) during EBI writing is Disabled.
<br>
</div></td></tr><tr><td>
[27:24]</td><td>R2R</td><td><div style="word-wrap: break-word;"><b>Idle Cycle Between Read-to-read
</b><br>
This field defines the number of R2R idle cycle.
<br>
R2R idle cycle = (R2R * EBI_MCLK).
<br>
When read action is finish and next action is going to read, R2R idle cycle is inserted and EBI_nCS return to idle state.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EBI_T::CTL1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL1
</font><br><p> <font size="2">
Offset: 0x10  External Bus Interface Bank1 Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>EN</td><td><div style="word-wrap: break-word;"><b>EBI Enable Bit
</b><br>
This bit is the functional enable bit for EBI.
<br>
0 = EBI function Disabled.
<br>
1 = EBI function Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>DW16</td><td><div style="word-wrap: break-word;"><b>EBI Data Width 16-bit Select
</b><br>
This bit defines if the EBI data width is 8-bit or 16-bit.
<br>
0 = EBI data width is 8-bit.
<br>
1 = EBI data width is 16-bit.
<br>
</div></td></tr><tr><td>
[2]</td><td>CSPOLINV</td><td><div style="word-wrap: break-word;"><b>Chip Select Pin Polar Inverse
</b><br>
This bit defines the active level of EBI chip select pin (EBI_nCS).
<br>
0 = Chip select pin (EBI_nCS) is active low.
<br>
1 = Chip select pin (EBI_nCS) is active high.
<br>
</div></td></tr><tr><td>
[3]</td><td>ADSEPEN</td><td><div style="word-wrap: break-word;"><b>EBI Address/Data Bus Separating Mode Enable Bit
</b><br>
0 = Address/Data Bus Separating Mode Disabled.
<br>
1 = Address/Data Bus Separating Mode Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>CACCESS</td><td><div style="word-wrap: break-word;"><b>Continuous Data Access Mode
</b><br>
When con tenuous access mode enabled, the tASU, tALE and tLHD cycles are bypass for continuous data transfer request.
<br>
0 = Continuous data access mode Disabled.
<br>
1 = Continuous data access mode Enabled.
<br>
</div></td></tr><tr><td>
[10:8]</td><td>MCLKDIV</td><td><div style="word-wrap: break-word;"><b>External Output Clock Divider
</b><br>
The frequency of EBI output clock (MCLK) is controlled by MCLKDIV as follow:
<br>
000 = HCLK/1.
<br>
001 = HCLK/2.
<br>
010 = HCLK/4.
<br>
011 = HCLK/8.
<br>
100 = HCLK/16.
<br>
101 = HCLK/32.
<br>
110 = HCLK/64.
<br>
111 = HCLK/128.
<br>
</div></td></tr><tr><td>
[18:16]</td><td>TALE</td><td><div style="word-wrap: break-word;"><b>Extend Time of ALE
</b><br>
The EBI_ALE high pulse period (tALE) to latch the address can be controlled by TALE.
<br>
tALE = (TALE+1)*EBI_MCLK.
<br>
Note: This field only available in EBI_CTL0 register
<br>
</div></td></tr><tr><td>
[24]</td><td>WBUFEN</td><td><div style="word-wrap: break-word;"><b>EBI Write Buffer Enable Bit
</b><br>
0 = EBI write buffer Disabled.
<br>
1 = EBI write buffer Enabled.
<br>
Note: This bit only available in EBI_CTL0 register
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EBI_T::TCTL1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TCTL1
</font><br><p> <font size="2">
Offset: 0x14  External Bus Interface Bank1 Timing Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:3]</td><td>TACC</td><td><div style="word-wrap: break-word;"><b>EBI Data Access Time
</b><br>
TACC define data access time (tACC).
<br>
tACC = (TACC +1) * EBI_MCLK.
<br>
</div></td></tr><tr><td>
[10:8]</td><td>TAHD</td><td><div style="word-wrap: break-word;"><b>EBI Data Access Hold Time
</b><br>
TAHD define data access hold time (tAHD).
<br>
tAHD = (TAHD +1) * EBI_MCLK.
<br>
</div></td></tr><tr><td>
[15:12]</td><td>W2X</td><td><div style="word-wrap: break-word;"><b>Idle Cycle After Write
</b><br>
This field defines the number of W2X idle cycle.
<br>
W2X idle cycle = (W2X * EBI_MCLK).
<br>
When write action is finish, W2X idle cycle is inserted and EBI_nCS return to idle state.
<br>
</div></td></tr><tr><td>
[22]</td><td>RAHDOFF</td><td><div style="word-wrap: break-word;"><b>Access Hold Time Disable Control When Read
</b><br>
0 = The Data Access Hold Time (tAHD) during EBI reading is Enabled.
<br>
1 = The Data Access Hold Time (tAHD) during EBI reading is Disabled.
<br>
</div></td></tr><tr><td>
[23]</td><td>WAHDOFF</td><td><div style="word-wrap: break-word;"><b>Access Hold Time Disable Control When Write
</b><br>
0 = The Data Access Hold Time (tAHD) during EBI writing is Enabled.
<br>
1 = The Data Access Hold Time (tAHD) during EBI writing is Disabled.
<br>
</div></td></tr><tr><td>
[27:24]</td><td>R2R</td><td><div style="word-wrap: break-word;"><b>Idle Cycle Between Read-to-read
</b><br>
This field defines the number of R2R idle cycle.
<br>
R2R idle cycle = (R2R * EBI_MCLK).
<br>
When read action is finish and next action is going to read, R2R idle cycle is inserted and EBI_nCS return to idle state.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EBI_T::CTL2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL2
</font><br><p> <font size="2">
Offset: 0x20  External Bus Interface Bank2 Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>EN</td><td><div style="word-wrap: break-word;"><b>EBI Enable Bit
</b><br>
This bit is the functional enable bit for EBI.
<br>
0 = EBI function Disabled.
<br>
1 = EBI function Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>DW16</td><td><div style="word-wrap: break-word;"><b>EBI Data Width 16-bit Select
</b><br>
This bit defines if the EBI data width is 8-bit or 16-bit.
<br>
0 = EBI data width is 8-bit.
<br>
1 = EBI data width is 16-bit.
<br>
</div></td></tr><tr><td>
[2]</td><td>CSPOLINV</td><td><div style="word-wrap: break-word;"><b>Chip Select Pin Polar Inverse
</b><br>
This bit defines the active level of EBI chip select pin (EBI_nCS).
<br>
0 = Chip select pin (EBI_nCS) is active low.
<br>
1 = Chip select pin (EBI_nCS) is active high.
<br>
</div></td></tr><tr><td>
[3]</td><td>ADSEPEN</td><td><div style="word-wrap: break-word;"><b>EBI Address/Data Bus Separating Mode Enable Bit
</b><br>
0 = Address/Data Bus Separating Mode Disabled.
<br>
1 = Address/Data Bus Separating Mode Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>CACCESS</td><td><div style="word-wrap: break-word;"><b>Continuous Data Access Mode
</b><br>
When con tenuous access mode enabled, the tASU, tALE and tLHD cycles are bypass for continuous data transfer request.
<br>
0 = Continuous data access mode Disabled.
<br>
1 = Continuous data access mode Enabled.
<br>
</div></td></tr><tr><td>
[10:8]</td><td>MCLKDIV</td><td><div style="word-wrap: break-word;"><b>External Output Clock Divider
</b><br>
The frequency of EBI output clock (MCLK) is controlled by MCLKDIV as follow:
<br>
000 = HCLK/1.
<br>
001 = HCLK/2.
<br>
010 = HCLK/4.
<br>
011 = HCLK/8.
<br>
100 = HCLK/16.
<br>
101 = HCLK/32.
<br>
110 = HCLK/64.
<br>
111 = HCLK/128.
<br>
</div></td></tr><tr><td>
[18:16]</td><td>TALE</td><td><div style="word-wrap: break-word;"><b>Extend Time of ALE
</b><br>
The EBI_ALE high pulse period (tALE) to latch the address can be controlled by TALE.
<br>
tALE = (TALE+1)*EBI_MCLK.
<br>
Note: This field only available in EBI_CTL0 register
<br>
</div></td></tr><tr><td>
[24]</td><td>WBUFEN</td><td><div style="word-wrap: break-word;"><b>EBI Write Buffer Enable Bit
</b><br>
0 = EBI write buffer Disabled.
<br>
1 = EBI write buffer Enabled.
<br>
Note: This bit only available in EBI_CTL0 register
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EBI_T::TCTL2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TCTL2
</font><br><p> <font size="2">
Offset: 0x24  External Bus Interface Bank2 Timing Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:3]</td><td>TACC</td><td><div style="word-wrap: break-word;"><b>EBI Data Access Time
</b><br>
TACC define data access time (tACC).
<br>
tACC = (TACC +1) * EBI_MCLK.
<br>
</div></td></tr><tr><td>
[10:8]</td><td>TAHD</td><td><div style="word-wrap: break-word;"><b>EBI Data Access Hold Time
</b><br>
TAHD define data access hold time (tAHD).
<br>
tAHD = (TAHD +1) * EBI_MCLK.
<br>
</div></td></tr><tr><td>
[15:12]</td><td>W2X</td><td><div style="word-wrap: break-word;"><b>Idle Cycle After Write
</b><br>
This field defines the number of W2X idle cycle.
<br>
W2X idle cycle = (W2X * EBI_MCLK).
<br>
When write action is finish, W2X idle cycle is inserted and EBI_nCS return to idle state.
<br>
</div></td></tr><tr><td>
[22]</td><td>RAHDOFF</td><td><div style="word-wrap: break-word;"><b>Access Hold Time Disable Control When Read
</b><br>
0 = The Data Access Hold Time (tAHD) during EBI reading is Enabled.
<br>
1 = The Data Access Hold Time (tAHD) during EBI reading is Disabled.
<br>
</div></td></tr><tr><td>
[23]</td><td>WAHDOFF</td><td><div style="word-wrap: break-word;"><b>Access Hold Time Disable Control When Write
</b><br>
0 = The Data Access Hold Time (tAHD) during EBI writing is Enabled.
<br>
1 = The Data Access Hold Time (tAHD) during EBI writing is Disabled.
<br>
</div></td></tr><tr><td>
[27:24]</td><td>R2R</td><td><div style="word-wrap: break-word;"><b>Idle Cycle Between Read-to-read
</b><br>
This field defines the number of R2R idle cycle.
<br>
R2R idle cycle = (R2R * EBI_MCLK).
<br>
When read action is finish and next action is going to read, R2R idle cycle is inserted and EBI_nCS return to idle state.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CTL0;                  /*!< [0x0000] External Bus Interface Bank0 Control Register                    */
    __IO uint32_t TCTL0;                 /*!< [0x0004] External Bus Interface Bank0 Timing Control Register             */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[2];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t CTL1;                  /*!< [0x0010] External Bus Interface Bank1 Control Register                    */
    __IO uint32_t TCTL1;                 /*!< [0x0014] External Bus Interface Bank1 Timing Control Register             */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[2];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t CTL2;                  /*!< [0x0020] External Bus Interface Bank2 Control Register                    */
    __IO uint32_t TCTL2;                 /*!< [0x0024] External Bus Interface Bank2 Timing Control Register             */

} EBI_T;

/**
    @addtogroup EBI_CONST EBI Bit Field Definition
    Constant Definitions for EBI Controller
@{ */

#define EBI_CTL_EN_Pos                   (0)                                               /*!< EBI_T::CTL: EN Position                */
#define EBI_CTL_EN_Msk                   (0x1ul << EBI_CTL_EN_Pos)                         /*!< EBI_T::CTL: EN Mask                    */

#define EBI_CTL_DW16_Pos                 (1)                                               /*!< EBI_T::CTL: DW16 Position              */
#define EBI_CTL_DW16_Msk                 (0x1ul << EBI_CTL_DW16_Pos)                       /*!< EBI_T::CTL: DW16 Mask                  */

#define EBI_CTL_CSPOLINV_Pos             (2)                                               /*!< EBI_T::CTL: CSPOLINV Position          */
#define EBI_CTL_CSPOLINV_Msk             (0x1ul << EBI_CTL_CSPOLINV_Pos)                   /*!< EBI_T::CTL: CSPOLINV Mask              */

#define EBI_CTL_ADSEPEN_Pos              (3)                                               /*!< EBI_T::CTL: ADSEPEN Position           */
#define EBI_CTL_ADSEPEN_Msk              (0x1ul << EBI_CTL_ADSEPEN_Pos)                    /*!< EBI_T::CTL: ADSEPEN Mask               */

#define EBI_CTL_CACCESS_Pos              (4)                                               /*!< EBI_T::CTL: CACCESS Position           */
#define EBI_CTL_CACCESS_Msk              (0x1ul << EBI_CTL_CACCESS_Pos)                    /*!< EBI_T::CTL: CACCESS Mask               */

#define EBI_CTL_MCLKDIV_Pos              (8)                                               /*!< EBI_T::CTL: MCLKDIV Position           */
#define EBI_CTL_MCLKDIV_Msk              (0x7ul << EBI_CTL_MCLKDIV_Pos)                    /*!< EBI_T::CTL: MCLKDIV Mask               */

#define EBI_CTL_TALE_Pos                 (16)                                              /*!< EBI_T::CTL: TALE Position              */
#define EBI_CTL_TALE_Msk                 (0x7ul << EBI_CTL_TALE_Pos)                       /*!< EBI_T::CTL: TALE Mask                  */

#define EBI_CTL_WBUFEN_Pos               (24)                                              /*!< EBI_T::CTL: WBUFEN Position            */
#define EBI_CTL_WBUFEN_Msk               (0x1ul << EBI_CTL_WBUFEN_Pos)                     /*!< EBI_T::CTL: WBUFEN Mask                */

#define EBI_TCTL_TACC_Pos                (3)                                               /*!< EBI_T::TCTL: TACC Position             */
#define EBI_TCTL_TACC_Msk                (0x1ful << EBI_TCTL_TACC_Pos)                     /*!< EBI_T::TCTL: TACC Mask                 */

#define EBI_TCTL_TAHD_Pos                (8)                                               /*!< EBI_T::TCTL: TAHD Position             */
#define EBI_TCTL_TAHD_Msk                (0x7ul << EBI_TCTL_TAHD_Pos)                      /*!< EBI_T::TCTL: TAHD Mask                 */

#define EBI_TCTL_W2X_Pos                 (12)                                              /*!< EBI_T::TCTL: W2X Position              */
#define EBI_TCTL_W2X_Msk                 (0xful << EBI_TCTL_W2X_Pos)                       /*!< EBI_T::TCTL: W2X Mask                  */

#define EBI_TCTL_RAHDOFF_Pos             (22)                                              /*!< EBI_T::TCTL: RAHDOFF Position          */
#define EBI_TCTL_RAHDOFF_Msk             (0x1ul << EBI_TCTL_RAHDOFF_Pos)                   /*!< EBI_T::TCTL: RAHDOFF Mask              */

#define EBI_TCTL_WAHDOFF_Pos             (23)                                              /*!< EBI_T::TCTL: WAHDOFF Position          */
#define EBI_TCTL_WAHDOFF_Msk             (0x1ul << EBI_TCTL_WAHDOFF_Pos)                   /*!< EBI_T::TCTL: WAHDOFF Mask              */

#define EBI_TCTL_R2R_Pos                 (24)                                              /*!< EBI_T::TCTL: R2R Position              */
#define EBI_TCTL_R2R_Msk                 (0xful << EBI_TCTL_R2R_Pos)                       /*!< EBI_T::TCTL: R2R Mask                  */

#define EBI_CTL0_EN_Pos                  (0)                                               /*!< EBI_T::CTL0: EN Position               */
#define EBI_CTL0_EN_Msk                  (0x1ul << EBI_CTL0_EN_Pos)                        /*!< EBI_T::CTL0: EN Mask                   */

#define EBI_CTL0_DW16_Pos                (1)                                               /*!< EBI_T::CTL0: DW16 Position             */
#define EBI_CTL0_DW16_Msk                (0x1ul << EBI_CTL0_DW16_Pos)                      /*!< EBI_T::CTL0: DW16 Mask                 */

#define EBI_CTL0_CSPOLINV_Pos            (2)                                               /*!< EBI_T::CTL0: CSPOLINV Position         */
#define EBI_CTL0_CSPOLINV_Msk            (0x1ul << EBI_CTL0_CSPOLINV_Pos)                  /*!< EBI_T::CTL0: CSPOLINV Mask             */

#define EBI_CTL0_ADSEPEN_Pos             (3)                                               /*!< EBI_T::CTL0: ADSEPEN Position          */
#define EBI_CTL0_ADSEPEN_Msk             (0x1ul << EBI_CTL0_ADSEPEN_Pos)                   /*!< EBI_T::CTL0: ADSEPEN Mask              */

#define EBI_CTL0_CACCESS_Pos             (4)                                               /*!< EBI_T::CTL0: CACCESS Position          */
#define EBI_CTL0_CACCESS_Msk             (0x1ul << EBI_CTL0_CACCESS_Pos)                   /*!< EBI_T::CTL0: CACCESS Mask              */

#define EBI_CTL0_MCLKDIV_Pos             (8)                                               /*!< EBI_T::CTL0: MCLKDIV Position          */
#define EBI_CTL0_MCLKDIV_Msk             (0x7ul << EBI_CTL0_MCLKDIV_Pos)                   /*!< EBI_T::CTL0: MCLKDIV Mask              */

#define EBI_CTL0_TALE_Pos                (16)                                              /*!< EBI_T::CTL0: TALE Position             */
#define EBI_CTL0_TALE_Msk                (0x7ul << EBI_CTL0_TALE_Pos)                      /*!< EBI_T::CTL0: TALE Mask                 */

#define EBI_CTL0_WBUFEN_Pos              (24)                                              /*!< EBI_T::CTL0: WBUFEN Position           */
#define EBI_CTL0_WBUFEN_Msk              (0x1ul << EBI_CTL0_WBUFEN_Pos)                    /*!< EBI_T::CTL0: WBUFEN Mask               */

#define EBI_TCTL0_TACC_Pos               (3)                                               /*!< EBI_T::TCTL0: TACC Position            */
#define EBI_TCTL0_TACC_Msk               (0x1ful << EBI_TCTL0_TACC_Pos)                    /*!< EBI_T::TCTL0: TACC Mask                */

#define EBI_TCTL0_TAHD_Pos               (8)                                               /*!< EBI_T::TCTL0: TAHD Position            */
#define EBI_TCTL0_TAHD_Msk               (0x7ul << EBI_TCTL0_TAHD_Pos)                     /*!< EBI_T::TCTL0: TAHD Mask                */

#define EBI_TCTL0_W2X_Pos                (12)                                              /*!< EBI_T::TCTL0: W2X Position             */
#define EBI_TCTL0_W2X_Msk                (0xful << EBI_TCTL0_W2X_Pos)                      /*!< EBI_T::TCTL0: W2X Mask                 */

#define EBI_TCTL0_RAHDOFF_Pos            (22)                                              /*!< EBI_T::TCTL0: RAHDOFF Position         */
#define EBI_TCTL0_RAHDOFF_Msk            (0x1ul << EBI_TCTL0_RAHDOFF_Pos)                  /*!< EBI_T::TCTL0: RAHDOFF Mask             */

#define EBI_TCTL0_WAHDOFF_Pos            (23)                                              /*!< EBI_T::TCTL0: WAHDOFF Position         */
#define EBI_TCTL0_WAHDOFF_Msk            (0x1ul << EBI_TCTL0_WAHDOFF_Pos)                  /*!< EBI_T::TCTL0: WAHDOFF Mask             */

#define EBI_TCTL0_R2R_Pos                (24)                                              /*!< EBI_T::TCTL0: R2R Position             */
#define EBI_TCTL0_R2R_Msk                (0xful << EBI_TCTL0_R2R_Pos)                      /*!< EBI_T::TCTL0: R2R Mask                 */

#define EBI_CTL1_EN_Pos                  (0)                                               /*!< EBI_T::CTL1: EN Position               */
#define EBI_CTL1_EN_Msk                  (0x1ul << EBI_CTL1_EN_Pos)                        /*!< EBI_T::CTL1: EN Mask                   */

#define EBI_CTL1_DW16_Pos                (1)                                               /*!< EBI_T::CTL1: DW16 Position             */
#define EBI_CTL1_DW16_Msk                (0x1ul << EBI_CTL1_DW16_Pos)                      /*!< EBI_T::CTL1: DW16 Mask                 */

#define EBI_CTL1_CSPOLINV_Pos            (2)                                               /*!< EBI_T::CTL1: CSPOLINV Position         */
#define EBI_CTL1_CSPOLINV_Msk            (0x1ul << EBI_CTL1_CSPOLINV_Pos)                  /*!< EBI_T::CTL1: CSPOLINV Mask             */

#define EBI_CTL1_ADSEPEN_Pos             (3)                                               /*!< EBI_T::CTL1: ADSEPEN Position          */
#define EBI_CTL1_ADSEPEN_Msk             (0x1ul << EBI_CTL1_ADSEPEN_Pos)                   /*!< EBI_T::CTL1: ADSEPEN Mask              */

#define EBI_CTL1_CACCESS_Pos             (4)                                               /*!< EBI_T::CTL1: CACCESS Position          */
#define EBI_CTL1_CACCESS_Msk             (0x1ul << EBI_CTL1_CACCESS_Pos)                   /*!< EBI_T::CTL1: CACCESS Mask              */

#define EBI_CTL1_MCLKDIV_Pos             (8)                                               /*!< EBI_T::CTL1: MCLKDIV Position          */
#define EBI_CTL1_MCLKDIV_Msk             (0x7ul << EBI_CTL1_MCLKDIV_Pos)                   /*!< EBI_T::CTL1: MCLKDIV Mask              */

#define EBI_CTL1_TALE_Pos                (16)                                              /*!< EBI_T::CTL1: TALE Position             */
#define EBI_CTL1_TALE_Msk                (0x7ul << EBI_CTL1_TALE_Pos)                      /*!< EBI_T::CTL1: TALE Mask                 */

#define EBI_CTL1_WBUFEN_Pos              (24)                                              /*!< EBI_T::CTL1: WBUFEN Position           */
#define EBI_CTL1_WBUFEN_Msk              (0x1ul << EBI_CTL1_WBUFEN_Pos)                    /*!< EBI_T::CTL1: WBUFEN Mask               */

#define EBI_TCTL1_TACC_Pos               (3)                                               /*!< EBI_T::TCTL1: TACC Position            */
#define EBI_TCTL1_TACC_Msk               (0x1ful << EBI_TCTL1_TACC_Pos)                    /*!< EBI_T::TCTL1: TACC Mask                */

#define EBI_TCTL1_TAHD_Pos               (8)                                               /*!< EBI_T::TCTL1: TAHD Position            */
#define EBI_TCTL1_TAHD_Msk               (0x7ul << EBI_TCTL1_TAHD_Pos)                     /*!< EBI_T::TCTL1: TAHD Mask                */

#define EBI_TCTL1_W2X_Pos                (12)                                              /*!< EBI_T::TCTL1: W2X Position             */
#define EBI_TCTL1_W2X_Msk                (0xful << EBI_TCTL1_W2X_Pos)                      /*!< EBI_T::TCTL1: W2X Mask                 */

#define EBI_TCTL1_RAHDOFF_Pos            (22)                                              /*!< EBI_T::TCTL1: RAHDOFF Position         */
#define EBI_TCTL1_RAHDOFF_Msk            (0x1ul << EBI_TCTL1_RAHDOFF_Pos)                  /*!< EBI_T::TCTL1: RAHDOFF Mask             */

#define EBI_TCTL1_WAHDOFF_Pos            (23)                                              /*!< EBI_T::TCTL1: WAHDOFF Position         */
#define EBI_TCTL1_WAHDOFF_Msk            (0x1ul << EBI_TCTL1_WAHDOFF_Pos)                  /*!< EBI_T::TCTL1: WAHDOFF Mask             */

#define EBI_TCTL1_R2R_Pos                (24)                                              /*!< EBI_T::TCTL1: R2R Position             */
#define EBI_TCTL1_R2R_Msk                (0xful << EBI_TCTL1_R2R_Pos)                      /*!< EBI_T::TCTL1: R2R Mask                 */

#define EBI_CTL2_EN_Pos                  (0)                                               /*!< EBI_T::CTL2: EN Position               */
#define EBI_CTL2_EN_Msk                  (0x1ul << EBI_CTL2_EN_Pos)                        /*!< EBI_T::CTL2: EN Mask                   */

#define EBI_CTL2_DW16_Pos                (1)                                               /*!< EBI_T::CTL2: DW16 Position             */
#define EBI_CTL2_DW16_Msk                (0x1ul << EBI_CTL2_DW16_Pos)                      /*!< EBI_T::CTL2: DW16 Mask                 */

#define EBI_CTL2_CSPOLINV_Pos            (2)                                               /*!< EBI_T::CTL2: CSPOLINV Position         */
#define EBI_CTL2_CSPOLINV_Msk            (0x1ul << EBI_CTL2_CSPOLINV_Pos)                  /*!< EBI_T::CTL2: CSPOLINV Mask             */

#define EBI_CTL2_ADSEPEN_Pos             (3)                                               /*!< EBI_T::CTL2: ADSEPEN Position          */
#define EBI_CTL2_ADSEPEN_Msk             (0x1ul << EBI_CTL2_ADSEPEN_Pos)                   /*!< EBI_T::CTL2: ADSEPEN Mask              */

#define EBI_CTL2_CACCESS_Pos             (4)                                               /*!< EBI_T::CTL2: CACCESS Position          */
#define EBI_CTL2_CACCESS_Msk             (0x1ul << EBI_CTL2_CACCESS_Pos)                   /*!< EBI_T::CTL2: CACCESS Mask              */

#define EBI_CTL2_MCLKDIV_Pos             (8)                                               /*!< EBI_T::CTL2: MCLKDIV Position          */
#define EBI_CTL2_MCLKDIV_Msk             (0x7ul << EBI_CTL2_MCLKDIV_Pos)                   /*!< EBI_T::CTL2: MCLKDIV Mask              */

#define EBI_CTL2_TALE_Pos                (16)                                              /*!< EBI_T::CTL2: TALE Position             */
#define EBI_CTL2_TALE_Msk                (0x7ul << EBI_CTL2_TALE_Pos)                      /*!< EBI_T::CTL2: TALE Mask                 */

#define EBI_CTL2_WBUFEN_Pos              (24)                                              /*!< EBI_T::CTL2: WBUFEN Position           */
#define EBI_CTL2_WBUFEN_Msk              (0x1ul << EBI_CTL2_WBUFEN_Pos)                    /*!< EBI_T::CTL2: WBUFEN Mask               */

#define EBI_TCTL2_TACC_Pos               (3)                                               /*!< EBI_T::TCTL2: TACC Position            */
#define EBI_TCTL2_TACC_Msk               (0x1ful << EBI_TCTL2_TACC_Pos)                    /*!< EBI_T::TCTL2: TACC Mask                */

#define EBI_TCTL2_TAHD_Pos               (8)                                               /*!< EBI_T::TCTL2: TAHD Position            */
#define EBI_TCTL2_TAHD_Msk               (0x7ul << EBI_TCTL2_TAHD_Pos)                     /*!< EBI_T::TCTL2: TAHD Mask                */

#define EBI_TCTL2_W2X_Pos                (12)                                              /*!< EBI_T::TCTL2: W2X Position             */
#define EBI_TCTL2_W2X_Msk                (0xful << EBI_TCTL2_W2X_Pos)                      /*!< EBI_T::TCTL2: W2X Mask                 */

#define EBI_TCTL2_RAHDOFF_Pos            (22)                                              /*!< EBI_T::TCTL2: RAHDOFF Position         */
#define EBI_TCTL2_RAHDOFF_Msk            (0x1ul << EBI_TCTL2_RAHDOFF_Pos)                  /*!< EBI_T::TCTL2: RAHDOFF Mask             */

#define EBI_TCTL2_WAHDOFF_Pos            (23)                                              /*!< EBI_T::TCTL2: WAHDOFF Position         */
#define EBI_TCTL2_WAHDOFF_Msk            (0x1ul << EBI_TCTL2_WAHDOFF_Pos)                  /*!< EBI_T::TCTL2: WAHDOFF Mask             */

#define EBI_TCTL2_R2R_Pos                (24)                                              /*!< EBI_T::TCTL2: R2R Position             */
#define EBI_TCTL2_R2R_Msk                (0xful << EBI_TCTL2_R2R_Pos)                      /*!< EBI_T::TCTL2: R2R Mask                 */

/**@}*/ /* EBI_CONST */
/**@}*/ /* end of EBI register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __EBI_REG_H__ */
