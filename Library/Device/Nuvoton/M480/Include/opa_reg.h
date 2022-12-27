/**************************************************************************//**
 * @file     opa_reg.h
 * @version  V1.00
 * @brief    OPA register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __OPA_REG_H__
#define __OPA_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup OPA OP Amplifier(OPA)
    Memory Mapped Structure for OPA Controller
@{ */

typedef struct
{


    /**
@var OPA_T::CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL
</font><br><p> <font size="2">
Offset: 0x00  OP Amplifier Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>OPEN0</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 0 Enable Bit
</b><br>
0 = OP amplifier0 Disabled.
<br>
1 = OP amplifier0 Enabled.
<br>
Note: OP Amplifier 0 output needs wait stable 20u03BCs after OPEN0 is set.
<br>
</div></td></tr><tr><td>
[1]</td><td>OPEN1</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 1 Enable Bit
</b><br>
0 = OP amplifier1 Disabled.
<br>
1 = OP amplifier1 Enabled.
<br>
Note: OP Amplifier 1 output needs wait stable 20u03BCs after OPEN1 is set.
<br>
</div></td></tr><tr><td>
[2]</td><td>OPEN2</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 2 Enable Bit
</b><br>
0 = OP amplifier2 Disabled.
<br>
1 = OP amplifier2 Enabled.
<br>
Note: OP Amplifier 2 output needs wait stable 20u03BCs after OPEN2 is set.
<br>
</div></td></tr><tr><td>
[4]</td><td>OPDOEN0</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 0 Schmitt Trigger Non-inverting Buffer Enable Bit
</b><br>
0 = OP amplifier0 Schmitt Trigger non-invert buffer Disabled.
<br>
1 = OP amplifier0 Schmitt Trigger non-invert buffer Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>OPDOEN1</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 1 Schmitt Trigger Non-inverting Buffer Enable Bit
</b><br>
0 = OP amplifier1 Schmitt Trigger non-invert buffer Disabled.
<br>
1 = OP amplifier1 Schmitt Trigger non-invert buffer Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>OPDOEN2</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 2 Schmitt Trigger Non-inverting Buffer Enable Bit
</b><br>
0 = OP amplifier2 Schmitt Trigger non-invert buffer Disabled.
<br>
1 = OP amplifier2 Schmitt Trigger non-invert buffer Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>OPDOIEN0</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 0 Schmitt Trigger Digital Output Interrupt Enable Bit
</b><br>
0 = OP Amplifier 0 digital output interrupt function Disabled.
<br>
1 = OP Amplifier 0 digital output interrupt function Enabled.
<br>
The OPDOIF0 interrupt flag is set by hardware whenever the OP amplifier 0 Schmitt Trigger non-inverting buffer digital output changes state, in the meanwhile, if OPDOIEN0 is set to 1, a comparator interrupt request is generated.
<br>
</div></td></tr><tr><td>
[9]</td><td>OPDOIEN1</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 1 Schmitt Trigger Digital Output Interrupt Enable Bit
</b><br>
0 = OP Amplifier 1 digital output interrupt function Disabled.
<br>
1 = OP Amplifier 1 digital output interrupt function Enabled.
<br>
OPDOIF1 interrupt flag is set by hardware whenever the OP amplifier 1 Schmitt trigger non-inverting buffer digital output changes state, in the meanwhile, if OPDOIEN1 is set to 1, a comparator interrupt request is generated.
<br>
</div></td></tr><tr><td>
[10]</td><td>OPDOIEN2</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 2 Schmitt Trigger Digital Output Interrupt Enable Bit
</b><br>
0 = OP Amplifier 2 digital output interrupt function Disabled.
<br>
1 = OP Amplifier 2 digital output interrupt function Enabled.
<br>
OPDOIF2 interrupt flag is set by hardware whenever the OP amplifier 2 Schmitt Trigger non-inverting buffer digital output changes state, in the meanwhile, if OPDOIEN2 is set to 1, a comparator interrupt request is generated.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var OPA_T::STATUS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STATUS
</font><br><p> <font size="2">
Offset: 0x04  OP Amplifier Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>OPDO0</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 0 Digital Output
</b><br>
Synchronized to the APB clock to allow reading by software
<br>
Cleared when the Schmitt Trigger buffer is disabled (OPDOEN0 = 0)
<br>
</div></td></tr><tr><td>
[1]</td><td>OPDO1</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 1 Digital Output
</b><br>
Synchronized to the APB clock to allow reading by software
<br>
Cleared when the Schmitt Trigger buffer is disabled (OPDOEN1 = 0)
<br>
</div></td></tr><tr><td>
[2]</td><td>OPDO2</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 2 Digital Output
</b><br>
Synchronized to the APB clock to allow reading by software
<br>
Cleared when the Schmitt Trigger buffer is disabled (OPDOEN2 = 0)
<br>
</div></td></tr><tr><td>
[4]</td><td>OPDOIF0</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 0 Schmitt Trigger Digital Output Interrupt Flag
</b><br>
OPDOIF0 interrupt flag is set by hardware whenever the OP amplifier 0 Schmitt Trigger non-inverting buffer digital output changes state
<br>
This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[5]</td><td>OPDOIF1</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 1 Schmitt Trigger Digital Output Interrupt Flag
</b><br>
OPDOIF1 interrupt flag is set by hardware whenever the OP amplifier 1 Schmitt Trigger non-inverting buffer digital output changes state
<br>
This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[6]</td><td>OPDOIF2</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 2 Schmitt Trigger Digital Output Interrupt Flag
</b><br>
OPDOIF2 interrupt flag is set by hardware whenever the OP amplifier 2 Schmitt Trigger non-inverting buffer digital output changes state
<br>
This bit is cleared by writing 1 to it.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var OPA_T::CALCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CALCTL
</font><br><p> <font size="2">
Offset: 0x08  OP Amplifier Calibration Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CALTRG0</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 0 Calibration Trigger Bit
</b><br>
0 = Stop, hardware auto clear.
<br>
1 = Start. Note: Before enable this bit, it should set OPEN0 in advance.
<br>
</div></td></tr><tr><td>
[1]</td><td>CALTRG1</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 1 Calibration Trigger Bit
</b><br>
0 = Stop, hardware auto clear.
<br>
1 = Start. Note: Before enable this bit, it should set OPEN1 in advance.
<br>
</div></td></tr><tr><td>
[2]</td><td>CALTRG2</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 2 Calibration Trigger Bit
</b><br>
0 = Stop, hardware auto clear.
<br>
1 = Start. Note: Before enable this bit, it should set OPEN2 in advance.
<br>
</div></td></tr><tr><td>
[16]</td><td>CALRVS0</td><td><div style="word-wrap: break-word;"><b>OPA0 Calibration Reference Voltage Selection
</b><br>
0 = VREF is AVDD.
<br>
1 = VREF from high vcm to low vcm.
<br>
</div></td></tr><tr><td>
[17]</td><td>CALRVS1</td><td><div style="word-wrap: break-word;"><b>OPA1 Calibration Reference Voltage Selection
</b><br>
0 = VREF is AVDD.
<br>
1 = VREF from high vcm to low vcm.
<br>
</div></td></tr><tr><td>
[18]</td><td>CALRVS2</td><td><div style="word-wrap: break-word;"><b>OPA2 Calibration Reference Voltage Selection
</b><br>
0 = VREF is AVDD.
<br>
1 = VREF from high vcm to low vcm.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var OPA_T::CALST

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CALST
</font><br><p> <font size="2">
Offset: 0x0C  OP Amplifier Calibration Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>DONE0</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 0 Calibration Done Status
</b><br>
0 = Calibrating.
<br>
1 = Calibration Done.
<br>
</div></td></tr><tr><td>
[1]</td><td>CALNS0</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 0 Calibration Result Status for NMOS
</b><br>
0 = Pass.
<br>
1 = Fail.
<br>
</div></td></tr><tr><td>
[2]</td><td>CALPS0</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 0 Calibration Result Status for PMOS
</b><br>
0 = Pass.
<br>
1 = Fail.
<br>
</div></td></tr><tr><td>
[4]</td><td>DONE1</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 1 Calibration Done Status
</b><br>
0 = Calibrating.
<br>
1 = Calibration Done.
<br>
</div></td></tr><tr><td>
[5]</td><td>CALNS1</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 1 Calibration Result Status for NMOS
</b><br>
0 = Pass.
<br>
1 = Fail.
<br>
</div></td></tr><tr><td>
[6]</td><td>CALPS1</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 1 Calibration Result Status for PMOS
</b><br>
0 = Pass.
<br>
1 = Fail.
<br>
</div></td></tr><tr><td>
[8]</td><td>DONE2</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 2 Calibration Done Status
</b><br>
0 = Calibrating.
<br>
1 = Calibration Done.
<br>
</div></td></tr><tr><td>
[9]</td><td>CALNS2</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 2 Calibration Result Status for NMOS
</b><br>
0 = Pass.
<br>
1 = Fail.
<br>
</div></td></tr><tr><td>
[10]</td><td>CALPS2</td><td><div style="word-wrap: break-word;"><b>OP Amplifier 2 Calibration Result Status for PMOS
</b><br>
0 = Pass.
<br>
1 = Fail.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CTL;                   /*!< [0x0000] OP Amplifier Control Register                                    */
    __IO uint32_t STATUS;                /*!< [0x0004] OP Amplifier Status Register                                     */
    __IO uint32_t CALCTL;                /*!< [0x0008] OP Amplifier Calibration Control Register                        */
    __I  uint32_t CALST;                 /*!< [0x000c] OP Amplifier Calibration Status Register                         */

} OPA_T;

/**
    @addtogroup OPA_CONST OPA Bit Field Definition
    Constant Definitions for OPA Controller
@{ */

#define OPA_CTL_OPEN0_Pos                (0)                                               /*!< OPA_T::CTL: OPEN0 Position             */
#define OPA_CTL_OPEN0_Msk                (0x1ul << OPA_CTL_OPEN0_Pos)                      /*!< OPA_T::CTL: OPEN0 Mask                 */

#define OPA_CTL_OPEN1_Pos                (1)                                               /*!< OPA_T::CTL: OPEN1 Position             */
#define OPA_CTL_OPEN1_Msk                (0x1ul << OPA_CTL_OPEN1_Pos)                      /*!< OPA_T::CTL: OPEN1 Mask                 */

#define OPA_CTL_OPEN2_Pos                (2)                                               /*!< OPA_T::CTL: OPEN2 Position             */
#define OPA_CTL_OPEN2_Msk                (0x1ul << OPA_CTL_OPEN2_Pos)                      /*!< OPA_T::CTL: OPEN2 Mask                 */

#define OPA_CTL_OPDOEN0_Pos              (4)                                               /*!< OPA_T::CTL: OPDOEN0 Position           */
#define OPA_CTL_OPDOEN0_Msk              (0x1ul << OPA_CTL_OPDOEN0_Pos)                    /*!< OPA_T::CTL: OPDOEN0 Mask               */

#define OPA_CTL_OPDOEN1_Pos              (5)                                               /*!< OPA_T::CTL: OPDOEN1 Position           */
#define OPA_CTL_OPDOEN1_Msk              (0x1ul << OPA_CTL_OPDOEN1_Pos)                    /*!< OPA_T::CTL: OPDOEN1 Mask               */

#define OPA_CTL_OPDOEN2_Pos              (6)                                               /*!< OPA_T::CTL: OPDOEN2 Position           */
#define OPA_CTL_OPDOEN2_Msk              (0x1ul << OPA_CTL_OPDOEN2_Pos)                    /*!< OPA_T::CTL: OPDOEN2 Mask               */

#define OPA_CTL_OPDOIEN0_Pos             (8)                                               /*!< OPA_T::CTL: OPDOIEN0 Position          */
#define OPA_CTL_OPDOIEN0_Msk             (0x1ul << OPA_CTL_OPDOIEN0_Pos)                   /*!< OPA_T::CTL: OPDOIEN0 Mask              */

#define OPA_CTL_OPDOIEN1_Pos             (9)                                               /*!< OPA_T::CTL: OPDOIEN1 Position          */
#define OPA_CTL_OPDOIEN1_Msk             (0x1ul << OPA_CTL_OPDOIEN1_Pos)                   /*!< OPA_T::CTL: OPDOIEN1 Mask              */

#define OPA_CTL_OPDOIEN2_Pos             (10)                                              /*!< OPA_T::CTL: OPDOIEN2 Position          */
#define OPA_CTL_OPDOIEN2_Msk             (0x1ul << OPA_CTL_OPDOIEN2_Pos)                   /*!< OPA_T::CTL: OPDOIEN2 Mask              */

#define OPA_STATUS_OPDO0_Pos             (0)                                               /*!< OPA_T::STATUS: OPDO0 Position          */
#define OPA_STATUS_OPDO0_Msk             (0x1ul << OPA_STATUS_OPDO0_Pos)                   /*!< OPA_T::STATUS: OPDO0 Mask              */

#define OPA_STATUS_OPDO1_Pos             (1)                                               /*!< OPA_T::STATUS: OPDO1 Position          */
#define OPA_STATUS_OPDO1_Msk             (0x1ul << OPA_STATUS_OPDO1_Pos)                   /*!< OPA_T::STATUS: OPDO1 Mask              */

#define OPA_STATUS_OPDO2_Pos             (2)                                               /*!< OPA_T::STATUS: OPDO2 Position          */
#define OPA_STATUS_OPDO2_Msk             (0x1ul << OPA_STATUS_OPDO2_Pos)                   /*!< OPA_T::STATUS: OPDO2 Mask              */

#define OPA_STATUS_OPDOIF0_Pos           (4)                                               /*!< OPA_T::STATUS: OPDOIF0 Position        */
#define OPA_STATUS_OPDOIF0_Msk           (0x1ul << OPA_STATUS_OPDOIF0_Pos)                 /*!< OPA_T::STATUS: OPDOIF0 Mask            */

#define OPA_STATUS_OPDOIF1_Pos           (5)                                               /*!< OPA_T::STATUS: OPDOIF1 Position        */
#define OPA_STATUS_OPDOIF1_Msk           (0x1ul << OPA_STATUS_OPDOIF1_Pos)                 /*!< OPA_T::STATUS: OPDOIF1 Mask            */

#define OPA_STATUS_OPDOIF2_Pos           (6)                                               /*!< OPA_T::STATUS: OPDOIF2 Position        */
#define OPA_STATUS_OPDOIF2_Msk           (0x1ul << OPA_STATUS_OPDOIF2_Pos)                 /*!< OPA_T::STATUS: OPDOIF2 Mask            */

#define OPA_CALCTL_CALTRG0_Pos           (0)                                               /*!< OPA_T::CALCTL: CALTRG0 Position        */
#define OPA_CALCTL_CALTRG0_Msk           (0x1ul << OPA_CALCTL_CALTRG0_Pos)                 /*!< OPA_T::CALCTL: CALTRG0 Mask            */

#define OPA_CALCTL_CALTRG1_Pos           (1)                                               /*!< OPA_T::CALCTL: CALTRG1 Position        */
#define OPA_CALCTL_CALTRG1_Msk           (0x1ul << OPA_CALCTL_CALTRG1_Pos)                 /*!< OPA_T::CALCTL: CALTRG1 Mask            */

#define OPA_CALCTL_CALTRG2_Pos           (2)                                               /*!< OPA_T::CALCTL: CALTRG2 Position        */
#define OPA_CALCTL_CALTRG2_Msk           (0x1ul << OPA_CALCTL_CALTRG2_Pos)                 /*!< OPA_T::CALCTL: CALTRG2 Mask            */

#define OPA_CALCTL_CALCLK0_Pos           (4)                                               /*!< OPA_T::CALCTL: CALCLK0 Position        */
#define OPA_CALCTL_CALCLK0_Msk           (0x3ul << OPA_CALCTL_CALCLK0_Pos)                 /*!< OPA_T::CALCTL: CALCLK0 Mask            */

#define OPA_CALCTL_CALCLK1_Pos           (6)                                               /*!< OPA_T::CALCTL: CALCLK1 Position        */
#define OPA_CALCTL_CALCLK1_Msk           (0x3ul << OPA_CALCTL_CALCLK1_Pos)                 /*!< OPA_T::CALCTL: CALCLK1 Mask            */

#define OPA_CALCTL_CALCLK2_Pos           (8)                                               /*!< OPA_T::CALCTL: CALCLK2 Position        */
#define OPA_CALCTL_CALCLK2_Msk           (0x3ul << OPA_CALCTL_CALCLK2_Pos)                 /*!< OPA_T::CALCTL: CALCLK2 Mask            */

#define OPA_CALCTL_CALRVS0_Pos           (16)                                              /*!< OPA_T::CALCTL: CALRVS0 Position        */
#define OPA_CALCTL_CALRVS0_Msk           (0x1ul << OPA_CALCTL_CALRVS0_Pos)                 /*!< OPA_T::CALCTL: CALRVS0 Mask            */

#define OPA_CALCTL_CALRVS1_Pos           (17)                                              /*!< OPA_T::CALCTL: CALRVS1 Position        */
#define OPA_CALCTL_CALRVS1_Msk           (0x1ul << OPA_CALCTL_CALRVS1_Pos)                 /*!< OPA_T::CALCTL: CALRVS1 Mask            */

#define OPA_CALCTL_CALRVS2_Pos           (18)                                              /*!< OPA_T::CALCTL: CALRVS2 Position        */
#define OPA_CALCTL_CALRVS2_Msk           (0x1ul << OPA_CALCTL_CALRVS2_Pos)                 /*!< OPA_T::CALCTL: CALRVS2 Mask            */

#define OPA_CALST_DONE0_Pos              (0)                                               /*!< OPA_T::CALST: DONE0 Position           */
#define OPA_CALST_DONE0_Msk              (0x1ul << OPA_CALST_DONE0_Pos)                    /*!< OPA_T::CALST: DONE0 Mask               */

#define OPA_CALST_CALNS0_Pos             (1)                                               /*!< OPA_T::CALST: CALNS0 Position          */
#define OPA_CALST_CALNS0_Msk             (0x1ul << OPA_CALST_CALNS0_Pos)                   /*!< OPA_T::CALST: CALNS0 Mask              */

#define OPA_CALST_CALPS0_Pos             (2)                                               /*!< OPA_T::CALST: CALPS0 Position          */
#define OPA_CALST_CALPS0_Msk             (0x1ul << OPA_CALST_CALPS0_Pos)                   /*!< OPA_T::CALST: CALPS0 Mask              */

#define OPA_CALST_DONE1_Pos              (4)                                               /*!< OPA_T::CALST: DONE1 Position           */
#define OPA_CALST_DONE1_Msk              (0x1ul << OPA_CALST_DONE1_Pos)                    /*!< OPA_T::CALST: DONE1 Mask               */

#define OPA_CALST_CALNS1_Pos             (5)                                               /*!< OPA_T::CALST: CALNS1 Position          */
#define OPA_CALST_CALNS1_Msk             (0x1ul << OPA_CALST_CALNS1_Pos)                   /*!< OPA_T::CALST: CALNS1 Mask              */

#define OPA_CALST_CALPS1_Pos             (6)                                               /*!< OPA_T::CALST: CALPS1 Position          */
#define OPA_CALST_CALPS1_Msk             (0x1ul << OPA_CALST_CALPS1_Pos)                   /*!< OPA_T::CALST: CALPS1 Mask              */

#define OPA_CALST_DONE2_Pos              (8)                                               /*!< OPA_T::CALST: DONE2 Position           */
#define OPA_CALST_DONE2_Msk              (0x1ul << OPA_CALST_DONE2_Pos)                    /*!< OPA_T::CALST: DONE2 Mask               */

#define OPA_CALST_CALNS2_Pos             (9)                                               /*!< OPA_T::CALST: CALNS2 Position          */
#define OPA_CALST_CALNS2_Msk             (0x1ul << OPA_CALST_CALNS2_Pos)                   /*!< OPA_T::CALST: CALNS2 Mask              */

#define OPA_CALST_CALPS2_Pos             (10)                                              /*!< OPA_T::CALST: CALPS2 Position          */
#define OPA_CALST_CALPS2_Msk             (0x1ul << OPA_CALST_CALPS2_Pos)                   /*!< OPA_T::CALST: CALPS2 Mask              */

/**@}*/ /* OPA_CONST */
/**@}*/ /* end of OPA register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __OPA_REG_H__ */

