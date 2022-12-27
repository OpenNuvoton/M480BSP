/**************************************************************************//**
 * @file     acmp_reg.h
 * @version  V1.00
 * @brief    ACMP register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __ACMP_REG_H__
#define __ACMP_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup ACMP Analog Comparator Controller(ACMP)
    Memory Mapped Structure for ACMP Controller
@{ */

typedef struct
{


    /**
@var ACMP_T::CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL
</font><br><p> <font size="2">
Offset: 0x00~0x04  Analog Comparator 0/1 Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ACMPEN</td><td><div style="word-wrap: break-word;"><b>Comparator Enable Bit
</b><br>
0 = Comparator x Disabled.
<br>
1 = Comparator x Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>ACMPIE</td><td><div style="word-wrap: break-word;"><b>Comparator Interrupt Enable Bit
</b><br>
0 = Comparator x interrupt Disabled.
<br>
1 = Comparator x interrupt Enabled
<br>
If WKEN (ACMP_CTL0[16]) is set to 1, the wake-up interrupt function will be enabled as well.
<br>
</div></td></tr><tr><td>
[3]</td><td>ACMPOINV</td><td><div style="word-wrap: break-word;"><b>Comparator Output Inverse
</b><br>
0 = Comparator x output inverse Disabled.
<br>
1 = Comparator x output inverse Enabled.
<br>
</div></td></tr><tr><td>
[5:4]</td><td>NEGSEL</td><td><div style="word-wrap: break-word;"><b>Comparator Negative Input Selection
</b><br>
00 = ACMPx_N pin.
<br>
01 = Internal comparator reference voltage (CRV).
<br>
10 = Band-gap voltage.
<br>
11 = DAC output.
<br>
</div></td></tr><tr><td>
[7:6]</td><td>POSSEL</td><td><div style="word-wrap: break-word;"><b>Comparator Positive Input Selection
</b><br>
00 = Input from ACMPx_P0.
<br>
01 = Input from ACMPx_P1.
<br>
10 = Input from ACMPx_P2.
<br>
11 = Input from ACMPx_P3.
<br>
</div></td></tr><tr><td>
[9:8]</td><td>INTPOL</td><td><div style="word-wrap: break-word;"><b>Interrupt Condition Polarity Selection
</b><br>
ACMPIFx will be set to 1 when comparator output edge condition is detected.
<br>
00 = Rising edge or falling edge.
<br>
01 = Rising edge.
<br>
10 = Falling edge.
<br>
11 = Reserved.
<br>
</div></td></tr><tr><td>
[12]</td><td>OUTSEL</td><td><div style="word-wrap: break-word;"><b>Comparator Output Select
</b><br>
0 = Comparator x output to ACMPx_O pin is unfiltered comparator output.
<br>
1 = Comparator x output to ACMPx_O pin is from filter output.
<br>
</div></td></tr><tr><td>
[15:13]</td><td>FILTSEL</td><td><div style="word-wrap: break-word;"><b>Comparator Output Filter Count Selection
</b><br>
000 = Filter function is Disabled.
<br>
001 = ACMPx output is sampled 1 consecutive PCLK.
<br>
010 = ACMPx output is sampled 2 consecutive PCLKs.
<br>
011 = ACMPx output is sampled 4 consecutive PCLKs.
<br>
100 = ACMPx output is sampled 8 consecutive PCLKs.
<br>
101 = ACMPx output is sampled 16 consecutive PCLKs.
<br>
110 = ACMPx output is sampled 32 consecutive PCLKs.
<br>
111 = ACMPx output is sampled 64 consecutive PCLKs.
<br>
</div></td></tr><tr><td>
[16]</td><td>WKEN</td><td><div style="word-wrap: break-word;"><b>Power-down Wake-up Enable Bit
</b><br>
0 = Wake-up function Disabled.
<br>
1 = Wake-up function Enabled.
<br>
</div></td></tr><tr><td>
[17]</td><td>WLATEN</td><td><div style="word-wrap: break-word;"><b>Window Latch Mode Enable Bit
</b><br>
0 = Window Latch Mode Disabled.
<br>
1 = Window Latch Mode Enabled.
<br>
</div></td></tr><tr><td>
[18]</td><td>WCMPSEL</td><td><div style="word-wrap: break-word;"><b>Window Compare Mode Selection
</b><br>
0 = Window Compare Mode Disabled.
<br>
1 = Window Compare Mode is Selected.
<br>
</div></td></tr><tr><td>
[25:24]</td><td>HYSSEL</td><td><div style="word-wrap: break-word;"><b>Hysteresis Mode Selection
</b><br>
00 = Hysteresis is 0mV.
<br>
01 = Hysteresis is 10mV.
<br>
10 = Hysteresis is 20mV.
<br>
11 = Hysteresis is 30mV.
<br>
</div></td></tr><tr><td>
[29:28]</td><td>MODESEL</td><td><div style="word-wrap: break-word;"><b>Propagation Delay Mode Selection
</b><br>
00 = Max propagation delay is 4.5uS, operation current is 1.2uA.
<br>
01 = Max propagation delay is 2uS, operation current is 3uA.
<br>
10 = Max propagation delay is 600nS, operation current is 10uA.
<br>
11 = Max propagation delay is 200nS, operation current is 75uA.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var ACMP_T::STATUS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STATUS
</font><br><p> <font size="2">
Offset: 0x08  Analog Comparator Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ACMPIF0</td><td><div style="word-wrap: break-word;"><b>Comparator 0 Interrupt Flag
</b><br>
This bit is set by hardware when the edge condition defined by INTPOL (ACMP_CTL0[9:8])
<br>
is detected on comparator 0 output.
<br>
This will generate an interrupt if ACMPIE (ACMP_CTL0[1]) is set to 1.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[1]</td><td>ACMPIF1</td><td><div style="word-wrap: break-word;"><b>Comparator 1 Interrupt Flag
</b><br>
This bit is set by hardware when the edge condition defined by INTPOL (ACMP_CTL1[9:8])
<br>
is detected on comparator 1 output.
<br>
This will cause an interrupt if ACMPIE (ACMP_CTL1[1]) is set to 1.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[4]</td><td>ACMPO0</td><td><div style="word-wrap: break-word;"><b>Comparator 0 Output
</b><br>
Synchronized to the PCLK to allow reading by software
<br>
Cleared when the comparator 0 is disabled, i.e.
<br>
ACMPEN (ACMP_CTL0[0]) is cleared to 0.
<br>
</div></td></tr><tr><td>
[5]</td><td>ACMPO1</td><td><div style="word-wrap: break-word;"><b>Comparator 1 Output
</b><br>
Synchronized to the PCLK to allow reading by software.
<br>
Cleared when the comparator 1 is disabled, i.e.
<br>
ACMPEN (ACMP_CTL1[0]) is cleared to 0.
<br>
</div></td></tr><tr><td>
[8]</td><td>WKIF0</td><td><div style="word-wrap: break-word;"><b>Comparator 0 Power-down Wake-up Interrupt Flag
</b><br>
This bit will be set to 1 when ACMP0 wake-up interrupt event occurs.
<br>
0 = No power-down wake-up occurred.
<br>
1 = Power-down wake-up occurred.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[9]</td><td>WKIF1</td><td><div style="word-wrap: break-word;"><b>Comparator 1 Power-down Wake-up Interrupt Flag
</b><br>
This bit will be set to 1 when ACMP1 wake-up interrupt event occurs.
<br>
0 = No power-down wake-up occurred.
<br>
1 = Power-down wake-up occurred.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[12]</td><td>ACMPS0</td><td><div style="word-wrap: break-word;"><b>Comparator 0 Status
</b><br>
Synchronized to the PCLK to allow reading by software
<br>
Cleared when the comparator 0 is disabled, i.e.
<br>
ACMPEN (ACMP_CTL0[0]) is cleared to 0.
<br>
</div></td></tr><tr><td>
[13]</td><td>ACMPS1</td><td><div style="word-wrap: break-word;"><b>Comparator 1 Status
</b><br>
Synchronized to the PCLK to allow reading by software
<br>
Cleared when the comparator 1 is disabled, i.e.
<br>
ACMPEN (ACMP_CTL1[0]) is cleared to 0.
<br>
</div></td></tr><tr><td>
[16]</td><td>ACMPWO</td><td><div style="word-wrap: break-word;"><b>Comparator Window Output
</b><br>
This bit shows the output status of window compare mode
<br>
0 = The positive input voltage is outside the window.
<br>
1 = The positive input voltage is in the window.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var ACMP_T::VREF

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">VREF
</font><br><p> <font size="2">
Offset: 0x0C  Analog Comparator Reference Voltage Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>CRVCTL</td><td><div style="word-wrap: break-word;"><b>Comparator Reference Voltage Setting
</b><br>
CRV = CRV source voltage * (1/6+CRVCTL/24).
<br>
</div></td></tr><tr><td>
[6]</td><td>CRVSSEL</td><td><div style="word-wrap: break-word;"><b>CRV Source Voltage Selection
</b><br>
0 = VDDA is selected as CRV source voltage.
<br>
1 = The reference voltage defined by SYS_VREFCTL register is selected as CRV source voltage.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CTL[2];                /*!< [0x0000~0x0004] Analog Comparator 0/1 Control Register                    */
    __IO uint32_t STATUS;                /*!< [0x0008] Analog Comparator Status Register                                */
    __IO uint32_t VREF;                  /*!< [0x000c] Analog Comparator Reference Voltage Control Register             */

} ACMP_T;

/**
    @addtogroup ACMP_CONST ACMP Bit Field Definition
    Constant Definitions for ACMP Controller
@{ */

#define ACMP_CTL_ACMPEN_Pos              (0)                                               /*!< ACMP_T::CTL: ACMPEN Position           */
#define ACMP_CTL_ACMPEN_Msk              (0x1ul << ACMP_CTL_ACMPEN_Pos)                    /*!< ACMP_T::CTL: ACMPEN Mask               */

#define ACMP_CTL_ACMPIE_Pos              (1)                                               /*!< ACMP_T::CTL: ACMPIE Position           */
#define ACMP_CTL_ACMPIE_Msk              (0x1ul << ACMP_CTL_ACMPIE_Pos)                    /*!< ACMP_T::CTL: ACMPIE Mask               */

#define ACMP_CTL_ACMPOINV_Pos            (3)                                               /*!< ACMP_T::CTL: ACMPOINV Position         */
#define ACMP_CTL_ACMPOINV_Msk            (0x1ul << ACMP_CTL_ACMPOINV_Pos)                  /*!< ACMP_T::CTL: ACMPOINV Mask             */

#define ACMP_CTL_NEGSEL_Pos              (4)                                               /*!< ACMP_T::CTL: NEGSEL Position           */
#define ACMP_CTL_NEGSEL_Msk              (0x3ul << ACMP_CTL_NEGSEL_Pos)                    /*!< ACMP_T::CTL: NEGSEL Mask               */

#define ACMP_CTL_POSSEL_Pos              (6)                                               /*!< ACMP_T::CTL: POSSEL Position           */
#define ACMP_CTL_POSSEL_Msk              (0x3ul << ACMP_CTL_POSSEL_Pos)                    /*!< ACMP_T::CTL: POSSEL Mask               */

#define ACMP_CTL_INTPOL_Pos              (8)                                               /*!< ACMP_T::CTL: INTPOL Position           */
#define ACMP_CTL_INTPOL_Msk              (0x3ul << ACMP_CTL_INTPOL_Pos)                    /*!< ACMP_T::CTL: INTPOL Mask               */

#define ACMP_CTL_OUTSEL_Pos              (12)                                              /*!< ACMP_T::CTL: OUTSEL Position           */
#define ACMP_CTL_OUTSEL_Msk              (0x1ul << ACMP_CTL_OUTSEL_Pos)                    /*!< ACMP_T::CTL: OUTSEL Mask               */

#define ACMP_CTL_FILTSEL_Pos             (13)                                              /*!< ACMP_T::CTL: FILTSEL Position          */
#define ACMP_CTL_FILTSEL_Msk             (0x7ul << ACMP_CTL_FILTSEL_Pos)                   /*!< ACMP_T::CTL: FILTSEL Mask              */

#define ACMP_CTL_WKEN_Pos                (16)                                              /*!< ACMP_T::CTL: WKEN Position             */
#define ACMP_CTL_WKEN_Msk                (0x1ul << ACMP_CTL_WKEN_Pos)                      /*!< ACMP_T::CTL: WKEN Mask                 */

#define ACMP_CTL_WLATEN_Pos              (17)                                              /*!< ACMP_T::CTL: WLATEN Position           */
#define ACMP_CTL_WLATEN_Msk              (0x1ul << ACMP_CTL_WLATEN_Pos)                    /*!< ACMP_T::CTL: WLATEN Mask               */

#define ACMP_CTL_WCMPSEL_Pos             (18)                                              /*!< ACMP_T::CTL: WCMPSEL Position          */
#define ACMP_CTL_WCMPSEL_Msk             (0x1ul << ACMP_CTL_WCMPSEL_Pos)                   /*!< ACMP_T::CTL: WCMPSEL Mask              */

#define ACMP_CTL_HYSSEL_Pos              (24)                                              /*!< ACMP_T::CTL: HYSSEL Position           */
#define ACMP_CTL_HYSSEL_Msk              (0x3ul << ACMP_CTL_HYSSEL_Pos)                    /*!< ACMP_T::CTL: HYSSEL Mask               */

#define ACMP_CTL_MODESEL_Pos             (28)                                              /*!< ACMP_T::CTL: MODESEL Position          */
#define ACMP_CTL_MODESEL_Msk             (0x3ul << ACMP_CTL_MODESEL_Pos)                   /*!< ACMP_T::CTL: MODESEL Mask              */

#define ACMP_STATUS_ACMPIF0_Pos          (0)                                               /*!< ACMP_T::STATUS: ACMPIF0 Position       */
#define ACMP_STATUS_ACMPIF0_Msk          (0x1ul << ACMP_STATUS_ACMPIF0_Pos)                /*!< ACMP_T::STATUS: ACMPIF0 Mask           */

#define ACMP_STATUS_ACMPIF1_Pos          (1)                                               /*!< ACMP_T::STATUS: ACMPIF1 Position       */
#define ACMP_STATUS_ACMPIF1_Msk          (0x1ul << ACMP_STATUS_ACMPIF1_Pos)                /*!< ACMP_T::STATUS: ACMPIF1 Mask           */

#define ACMP_STATUS_ACMPO0_Pos           (4)                                               /*!< ACMP_T::STATUS: ACMPO0 Position        */
#define ACMP_STATUS_ACMPO0_Msk           (0x1ul << ACMP_STATUS_ACMPO0_Pos)                 /*!< ACMP_T::STATUS: ACMPO0 Mask            */

#define ACMP_STATUS_ACMPO1_Pos           (5)                                               /*!< ACMP_T::STATUS: ACMPO1 Position        */
#define ACMP_STATUS_ACMPO1_Msk           (0x1ul << ACMP_STATUS_ACMPO1_Pos)                 /*!< ACMP_T::STATUS: ACMPO1 Mask            */

#define ACMP_STATUS_WKIF0_Pos            (8)                                               /*!< ACMP_T::STATUS: WKIF0 Position         */
#define ACMP_STATUS_WKIF0_Msk            (0x1ul << ACMP_STATUS_WKIF0_Pos)                  /*!< ACMP_T::STATUS: WKIF0 Mask             */

#define ACMP_STATUS_WKIF1_Pos            (9)                                               /*!< ACMP_T::STATUS: WKIF1 Position         */
#define ACMP_STATUS_WKIF1_Msk            (0x1ul << ACMP_STATUS_WKIF1_Pos)                  /*!< ACMP_T::STATUS: WKIF1 Mask             */

#define ACMP_STATUS_ACMPS0_Pos           (12)                                              /*!< ACMP_T::STATUS: ACMPS0 Position        */
#define ACMP_STATUS_ACMPS0_Msk           (0x1ul << ACMP_STATUS_ACMPS0_Pos)                 /*!< ACMP_T::STATUS: ACMPS0 Mask            */

#define ACMP_STATUS_ACMPS1_Pos           (13)                                              /*!< ACMP_T::STATUS: ACMPS1 Position        */
#define ACMP_STATUS_ACMPS1_Msk           (0x1ul << ACMP_STATUS_ACMPS1_Pos)                 /*!< ACMP_T::STATUS: ACMPS1 Mask            */

#define ACMP_STATUS_ACMPWO_Pos           (16)                                              /*!< ACMP_T::STATUS: ACMPWO Position        */
#define ACMP_STATUS_ACMPWO_Msk           (0x1ul << ACMP_STATUS_ACMPWO_Pos)                 /*!< ACMP_T::STATUS: ACMPWO Mask            */

#define ACMP_VREF_CRVCTL_Pos             (0)                                               /*!< ACMP_T::VREF: CRVCTL Position          */
#define ACMP_VREF_CRVCTL_Msk             (0xful << ACMP_VREF_CRVCTL_Pos)                   /*!< ACMP_T::VREF: CRVCTL Mask              */

#define ACMP_VREF_CRVSSEL_Pos            (6)                                               /*!< ACMP_T::VREF: CRVSSEL Position         */
#define ACMP_VREF_CRVSSEL_Msk            (0x1ul << ACMP_VREF_CRVSSEL_Pos)                  /*!< ACMP_T::VREF: CRVSSEL Mask             */

/**@}*/ /* ACMP_CONST */
/**@}*/ /* end of ACMP register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __ACMP_REG_H__ */
