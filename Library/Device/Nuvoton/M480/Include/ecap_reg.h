/**************************************************************************//**
 * @file     ecap_reg.h
 * @version  V1.00
 * @brief    ECAP register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __ECAP_REG_H__
#define __ECAP_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup ECAP Enhanced Input Capture Timer(ECAP)
    Memory Mapped Structure for ECAP Controller
@{ */

typedef struct
{

    /**
@var ECAP_T::CNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CNT
</font><br><p> <font size="2">
Offset: 0x00  Input Capture Counter (24-bit up counter)
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:0]</td><td>CNT</td><td><div style="word-wrap: break-word;"><b>Input Capture Timer/Counter
</b><br>
The input Capture Timer/Counter is a 24-bit up-counting counter
<br>
The clock source for the counter is from the clock divider
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var ECAP_T::HLD0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HLD0
</font><br><p> <font size="2">
Offset: 0x04  Input Capture Hold Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:0]</td><td>HOLD</td><td><div style="word-wrap: break-word;"><b>Input Capture Counter Hold Register
</b><br>
When an active input capture channel detects a valid edge signal change, the ECAPCNT value is latched into the corresponding holding register
<br>
Each input channel has its own holding register named by ECAP_HLDx where x is from 0 to 2 to indicate inputs from IC0 to IC2, respectively.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var ECAP_T::HLD1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HLD1
</font><br><p> <font size="2">
Offset: 0x08  Input Capture Hold Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:0]</td><td>HOLD</td><td><div style="word-wrap: break-word;"><b>Input Capture Counter Hold Register
</b><br>
When an active input capture channel detects a valid edge signal change, the ECAPCNT value is latched into the corresponding holding register
<br>
Each input channel has its own holding register named by ECAP_HLDx where x is from 0 to 2 to indicate inputs from IC0 to IC2, respectively.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var ECAP_T::HLD2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HLD2
</font><br><p> <font size="2">
Offset: 0x0C  Input Capture Hold Register 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:0]</td><td>HOLD</td><td><div style="word-wrap: break-word;"><b>Input Capture Counter Hold Register
</b><br>
When an active input capture channel detects a valid edge signal change, the ECAPCNT value is latched into the corresponding holding register
<br>
Each input channel has its own holding register named by ECAP_HLDx where x is from 0 to 2 to indicate inputs from IC0 to IC2, respectively.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var ECAP_T::CNTCMP

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CNTCMP
</font><br><p> <font size="2">
Offset: 0x10  Input Capture Compare Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:0]</td><td>CNTCMP</td><td><div style="word-wrap: break-word;"><b>Input Capture Counter Compare Register
</b><br>
If the compare function is enabled (CMPEN = 1), this register (ECAP_CNTCMP) is used to compare with the capture counter (ECAP_CNT).
<br>
If the reload control is enabled (RLDEN[n] = 1, n=0~3), an overflow event or capture events will trigger the hardware to load the value of this register (ECAP_CNTCMP) into ECAP_CNT.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var ECAP_T::CTL0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL0
</font><br><p> <font size="2">
Offset: 0x14  Input Capture Control Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2:0]</td><td>NFCLKSEL</td><td><div style="word-wrap: break-word;"><b>Noise Filter Clock Pre-divide Selection
</b><br>
To determine the sampling frequency of the Noise Filter clock
<br>
000 = CAP_CLK.
<br>
001 = CAP_CLK/2.
<br>
010 = CAP_CLK/4.
<br>
011 = CAP_CLK/16.
<br>
100 = CAP_CLK/32.
<br>
101 = CAP_CLK/64.
<br>
</div></td></tr><tr><td>
[3]</td><td>CAPNFDIS</td><td><div style="word-wrap: break-word;"><b>Input Capture Noise Filter Disable Control
</b><br>
0 = Noise filter of Input Capture Enabled.
<br>
1 = Noise filter of Input Capture Disabled (Bypass).
<br>
</div></td></tr><tr><td>
[4]</td><td>IC0EN</td><td><div style="word-wrap: break-word;"><b>Port Pin IC0 Input to Input Capture Unit Enable Control
</b><br>
0 = IC0 input to Input Capture Unit Disabled.
<br>
1 = IC0 input to Input Capture Unit Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>IC1EN</td><td><div style="word-wrap: break-word;"><b>Port Pin IC1 Input to Input Capture Unit Enable Control
</b><br>
0 = IC1 input to Input Capture Unit Disabled.
<br>
1 = IC1 input to Input Capture Unit Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>IC2EN</td><td><div style="word-wrap: break-word;"><b>Port Pin IC2 Input to Input Capture Unit Enable Control
</b><br>
0 = IC2 input to Input Capture Unit Disabled.
<br>
1 = IC2 input to Input Capture Unit Enabled.
<br>
</div></td></tr><tr><td>
[9:8]</td><td>CAPSEL0</td><td><div style="word-wrap: break-word;"><b>CAP0 Input Source Selection
</b><br>
00 = CAP0 input is from port pin ICAP0.
<br>
01 = Reserved.
<br>
10 = CAP0 input is from signal CHA of QEI controller unit n.
<br>
11 = Reserved.
<br>
Note: Input capture unit n matches QEIn, where n = 0~1.
<br>
</div></td></tr><tr><td>
[11:10]</td><td>CAPSEL1</td><td><div style="word-wrap: break-word;"><b>CAP1 Input Source Selection
</b><br>
00 = CAP1 input is from port pin ICAP1.
<br>
01 = Reserved.
<br>
10 = CAP1 input is from signal CHB of QEI controller unit n.
<br>
11 = Reserved.
<br>
Note: Input capture unit n matches QEIn, where n = 0~1.
<br>
</div></td></tr><tr><td>
[13:12]</td><td>CAPSEL2</td><td><div style="word-wrap: break-word;"><b>CAP2 Input Source Selection
</b><br>
00 = CAP2 input is from port pin ICAP2.
<br>
01 = Reserved.
<br>
10 = CAP2 input is from signal CHX of QEI controller unit n.
<br>
11 = Reserved.
<br>
Note: Input capture unit n matches QEIn, where n = 0~1.
<br>
</div></td></tr><tr><td>
[16]</td><td>CAPIEN0</td><td><div style="word-wrap: break-word;"><b>Input Capture Channel 0 Interrupt Enable Control
</b><br>
0 = The flag CAPTF0 can trigger Input Capture interrupt Disabled.
<br>
1 = The flag CAPTF0 can trigger Input Capture interrupt Enabled.
<br>
</div></td></tr><tr><td>
[17]</td><td>CAPIEN1</td><td><div style="word-wrap: break-word;"><b>Input Capture Channel 1 Interrupt Enable Control
</b><br>
0 = The flag CAPTF1 can trigger Input Capture interrupt Disabled.
<br>
1 = The flag CAPTF1 can trigger Input Capture interrupt Enabled.
<br>
</div></td></tr><tr><td>
[18]</td><td>CAPIEN2</td><td><div style="word-wrap: break-word;"><b>Input Capture Channel 2 Interrupt Enable Control
</b><br>
0 = The flag CAPTF2 can trigger Input Capture interrupt Disabled.
<br>
1 = The flag CAPTF2 can trigger Input Capture interrupt Enabled.
<br>
</div></td></tr><tr><td>
[20]</td><td>OVIEN</td><td><div style="word-wrap: break-word;"><b>CAPOVF Trigger Input Capture Interrupt Enable Control
</b><br>
0 = The flag CAPOVF can trigger Input Capture interrupt Disabled.
<br>
1 = The flag CAPOVF can trigger Input Capture interrupt Enabled.
<br>
</div></td></tr><tr><td>
[21]</td><td>CMPIEN</td><td><div style="word-wrap: break-word;"><b>CAPCMPF Trigger Input Capture Interrupt Enable Control
</b><br>
0 = The flag CAPCMPF can trigger Input Capture interrupt Disabled.
<br>
1 = The flag CAPCMPF can trigger Input Capture interrupt Enabled.
<br>
</div></td></tr><tr><td>
[24]</td><td>CNTEN</td><td><div style="word-wrap: break-word;"><b>Input Capture Counter Start Counting Control
</b><br>
Setting this bit to 1, the capture counter (ECAP_CNT) starts up-counting synchronously with the clock from the .
<br>
0 = ECAP_CNT stop counting.
<br>
1 = ECAP_CNT starts up-counting.
<br>
</div></td></tr><tr><td>
[25]</td><td>CMPCLREN</td><td><div style="word-wrap: break-word;"><b>Input Capture Counter Cleared by Compare-match Control
</b><br>
If this bit is set to 1, the capture counter (ECAP_CNT) will be cleared to 0 when the compare-match event (CAPCMPF = 1) occurs.
<br>
0 = Compare-match event (CAPCMPF) can clear capture counter (ECAP_CNT) Disabled.
<br>
1 = Compare-match event (CAPCMPF) can clear capture counter (ECAP_CNT) Enabled.
<br>
</div></td></tr><tr><td>
[28]</td><td>CMPEN</td><td><div style="word-wrap: break-word;"><b>Compare Function Enable Control
</b><br>
The compare function in input capture timer/counter is to compare the dynamic counting ECAP_CNT with the compare register ECAP_CNTCMP, if ECAP_CNT value reaches ECAP_CNTCMP, the flag CAPCMPF will be set.
<br>
0 = The compare function Disabled.
<br>
1 = The compare function Enabled.
<br>
</div></td></tr><tr><td>
[29]</td><td>CAPEN</td><td><div style="word-wrap: break-word;"><b>Input Capture Timer/Counter Enable Control
</b><br>
0 = Input Capture function Disabled.
<br>
1 = Input Capture function Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var ECAP_T::CTL1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL1
</font><br><p> <font size="2">
Offset: 0x18  Input Capture Control Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1:0]</td><td>EDGESEL0</td><td><div style="word-wrap: break-word;"><b>Channel 0 Captured Edge Selection
</b><br>
Input capture0 can detect falling edge change only, rising edge change only or both edge change
<br>
00 = Detect rising edge only.
<br>
01 = Detect falling edge only.
<br>
1x = Detect both rising and falling edge.
<br>
</div></td></tr><tr><td>
[3:2]</td><td>EDGESEL1</td><td><div style="word-wrap: break-word;"><b>Channel 1 Captured Edge Selection
</b><br>
Input capture1 can detect falling edge change only, rising edge change only or both edge change
<br>
00 = Detect rising edge only.
<br>
01 = Detect falling edge only.
<br>
1x = Detect both rising and falling edge.
<br>
</div></td></tr><tr><td>
[5:4]</td><td>EDGESEL2</td><td><div style="word-wrap: break-word;"><b>Channel 2 Captured Edge Selection
</b><br>
Input capture2 can detect falling edge change only, rising edge change only or both edge changes
<br>
00 = Detect rising edge only.
<br>
01 = Detect falling edge only.
<br>
1x = Detect both rising and falling edge.
<br>
</div></td></tr><tr><td>
[8]</td><td>CAP0RLDEN</td><td><div style="word-wrap: break-word;"><b>Capture Counteru2019s Reload Function Triggered by Event CAPTE0 Enable Bit
</b><br>
0 = The reload triggered by Event CAPTE0 Disabled.
<br>
1 = The reload triggered by Event CAPTE0 Enabled.
<br>
</div></td></tr><tr><td>
[9]</td><td>CAP1RLDEN</td><td><div style="word-wrap: break-word;"><b>Capture Counteru2019s Reload Function Triggered by Event CAPTE1 Enable Bit
</b><br>
0 = The reload triggered by Event CAPTE1 Disabled.
<br>
1 = The reload triggered by Event CAPTE1 Enabled.
<br>
</div></td></tr><tr><td>
[10]</td><td>CAP2RLDEN</td><td><div style="word-wrap: break-word;"><b>Capture Counteru2019s Reload Function Triggered by Event CAPTE2 Enable Bit
</b><br>
0 = The reload triggered by Event CAPTE2 Disabled.
<br>
1 = The reload triggered by Event CAPTE2 Enabled.
<br>
</div></td></tr><tr><td>
[11]</td><td>OVRLDEN</td><td><div style="word-wrap: break-word;"><b>Capture Counteru2019s Reload Function Triggered by Overflow Enable Bit
</b><br>
0 = The reload triggered by CAPOV Disabled.
<br>
1 = The reload triggered by CAPOV Enabled.
<br>
</div></td></tr><tr><td>
[14:12]</td><td>CLKSEL</td><td><div style="word-wrap: break-word;"><b>Capture Timer Clock Divide Selection
</b><br>
The capture timer clock has a pre-divider with eight divided options controlled by CLKSEL[2:0].
<br>
000 = CAP_CLK/1.
<br>
001 = CAP_CLK/4.
<br>
010 = CAP_CLK/16.
<br>
011 = CAP_CLK/32.
<br>
100 = CAP_CLK/64.
<br>
101 = CAP_CLK/96.
<br>
110 = CAP_CLK/112.
<br>
111 = CAP_CLK/128.
<br>
</div></td></tr><tr><td>
[17:16]</td><td>CNTSRCSEL</td><td><div style="word-wrap: break-word;"><b>Capture Timer/Counter Clock Source Selection
</b><br>
Select the capture timer/counter clock source.
<br>
00 = CAP_CLK (default).
<br>
01 = CAP0.
<br>
10 = CAP1.
<br>
11 = CAP2.
<br>
</div></td></tr><tr><td>
[20]</td><td>CAP0CLREN</td><td><div style="word-wrap: break-word;"><b>Capture Counter Cleared by Capture Event0 Control
</b><br>
0 = Event CAPTE0 can clear capture counter (ECAP_CNT) Disabled.
<br>
1 = Event CAPTE0 can clear capture counter (ECAP_CNT) Enabled.
<br>
</div></td></tr><tr><td>
[21]</td><td>CAP1CLREN</td><td><div style="word-wrap: break-word;"><b>Capture Counter Cleared by Capture Event1 Control
</b><br>
0 = Event CAPTE1 can clear capture counter (ECAP_CNT) Disabled.
<br>
1 = Event CAPTE1 can clear capture counter (ECAP_CNT) Enabled.
<br>
</div></td></tr><tr><td>
[22]</td><td>CAP2CLREN</td><td><div style="word-wrap: break-word;"><b>Capture Counter Cleared by Capture Event2 Control
</b><br>
0 = Event CAPTE2 can clear capture counter (ECAP_CNT) Disabled.
<br>
1 = Event CAPTE2 can clear capture counter (ECAP_CNT) Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var ECAP_T::STATUS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STATUS
</font><br><p> <font size="2">
Offset: 0x1C  Input Capture Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CAPTF0</td><td><div style="word-wrap: break-word;"><b>Input Capture Channel 0 Triggered Flag
</b><br>
When the input capture channel 0 detects a valid edge change at CAP0 input, it will set flag CAPTF0 to high.
<br>
0 = No valid edge change has been detected at CAP0 input since last clear.
<br>
1 = At least a valid edge change has been detected at CAP0 input since last clear.
<br>
Note: This bit is only cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[1]</td><td>CAPTF1</td><td><div style="word-wrap: break-word;"><b>Input Capture Channel 1 Triggered Flag
</b><br>
When the input capture channel 1 detects a valid edge change at CAP1 input, it will set flag CAPTF1 to high.
<br>
0 = No valid edge change has been detected at CAP1 input since last clear.
<br>
1 = At least a valid edge change has been detected at CAP1 input since last clear.
<br>
Note: This bit is only cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[2]</td><td>CAPTF2</td><td><div style="word-wrap: break-word;"><b>Input Capture Channel 2 Triggered Flag
</b><br>
When the input capture channel 2 detects a valid edge change at CAP2 input, it will set flag CAPTF2 to high.
<br>
0 = No valid edge change has been detected at CAP2 input since last clear.
<br>
1 = At least a valid edge change has been detected at CAP2 input since last clear.
<br>
Note: This bit is only cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[4]</td><td>CAPCMPF</td><td><div style="word-wrap: break-word;"><b>Input Capture Compare-match Flag
</b><br>
If the input capture compare function is enabled, the flag is set by hardware when capture counter (ECAP_CNT) up counts and reaches the ECAP_CNTCMP value.
<br>
0 = ECAP_CNT has not matched ECAP_CNTCMP value since last clear.
<br>
1 = ECAP_CNT has matched ECAP_CNTCMP value at least once since last clear.
<br>
Note: This bit is only cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[5]</td><td>CAPOVF</td><td><div style="word-wrap: break-word;"><b>Input Capture Counter Overflow Flag
</b><br>
Flag is set by hardware when counter (ECAP_CNT) overflows from 0x00FF_FFFF to zero.
<br>
0 = No overflow event has occurred since last clear.
<br>
1 = Overflow event(s) has/have occurred since last clear.
<br>
Note: This bit is only cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[6]</td><td>CAP0</td><td><div style="word-wrap: break-word;"><b>Value of Input Channel 0, CAP0 (Read Only)
</b><br>
Reflecting the value of input channel 0, CAP0
<br>
(The bit is read only and write is ignored)
<br>
</div></td></tr><tr><td>
[7]</td><td>CAP1</td><td><div style="word-wrap: break-word;"><b>Value of Input Channel 1, CAP1 (Read Only)
</b><br>
Reflecting the value of input channel 1, CAP1
<br>
(The bit is read only and write is ignored)
<br>
</div></td></tr><tr><td>
[8]</td><td>CAP2</td><td><div style="word-wrap: break-word;"><b>Value of Input Channel 2, CAP2 (Read Only)
</b><br>
Reflecting the value of input channel 2, CAP2.
<br>
(The bit is read only and write is ignored)
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CNT;                   /*!< [0x0000] Input Capture Counter                                            */
    __IO uint32_t HLD0;                  /*!< [0x0004] Input Capture Hold Register 0                                    */
    __IO uint32_t HLD1;                  /*!< [0x0008] Input Capture Hold Register 1                                    */
    __IO uint32_t HLD2;                  /*!< [0x000c] Input Capture Hold Register 2                                    */
    __IO uint32_t CNTCMP;                /*!< [0x0010] Input Capture Compare Register                                   */
    __IO uint32_t CTL0;                  /*!< [0x0014] Input Capture Control Register 0                                 */
    __IO uint32_t CTL1;                  /*!< [0x0018] Input Capture Control Register 1                                 */
    __IO uint32_t STATUS;                /*!< [0x001c] Input Capture Status Register                                    */

} ECAP_T;

/**
    @addtogroup ECAP_CONST ECAP Bit Field Definition
    Constant Definitions for ECAP Controller
@{ */

#define ECAP_CNT_CNT_Pos                 (0)                                               /*!< ECAP_T::CNT: CNT Position              */
#define ECAP_CNT_CNT_Msk                 (0xfffffful << ECAP_CNT_CNT_Pos)                  /*!< ECAP_T::CNT: CNT Mask                  */

#define ECAP_HLD0_HOLD_Pos               (0)                                               /*!< ECAP_T::HLD0: HOLD Position            */
#define ECAP_HLD0_HOLD_Msk               (0xfffffful << ECAP_HLD0_HOLD_Pos)                /*!< ECAP_T::HLD0: HOLD Mask                */

#define ECAP_HLD1_HOLD_Pos               (0)                                               /*!< ECAP_T::HLD1: HOLD Position            */
#define ECAP_HLD1_HOLD_Msk               (0xfffffful << ECAP_HLD1_HOLD_Pos)                /*!< ECAP_T::HLD1: HOLD Mask                */

#define ECAP_HLD2_HOLD_Pos               (0)                                               /*!< ECAP_T::HLD2: HOLD Position            */
#define ECAP_HLD2_HOLD_Msk               (0xfffffful << ECAP_HLD2_HOLD_Pos)                /*!< ECAP_T::HLD2: HOLD Mask                */

#define ECAP_CNTCMP_CNTCMP_Pos           (0)                                               /*!< ECAP_T::CNTCMP: CNTCMP Position        */
#define ECAP_CNTCMP_CNTCMP_Msk           (0xfffffful << ECAP_CNTCMP_CNTCMP_Pos)            /*!< ECAP_T::CNTCMP: CNTCMP Mask            */

#define ECAP_CTL0_NFCLKSEL_Pos           (0)                                               /*!< ECAP_T::CTL0: NFCLKSEL Position        */
#define ECAP_CTL0_NFCLKSEL_Msk           (0x7ul << ECAP_CTL0_NFCLKSEL_Pos)                 /*!< ECAP_T::CTL0: NFCLKSEL Mask            */

#define ECAP_CTL0_CAPNFDIS_Pos           (3)                                               /*!< ECAP_T::CTL0: CAPNFDIS Position        */
#define ECAP_CTL0_CAPNFDIS_Msk           (0x1ul << ECAP_CTL0_CAPNFDIS_Pos)                 /*!< ECAP_T::CTL0: CAPNFDIS Mask            */

#define ECAP_CTL0_IC0EN_Pos              (4)                                               /*!< ECAP_T::CTL0: IC0EN Position           */
#define ECAP_CTL0_IC0EN_Msk              (0x1ul << ECAP_CTL0_IC0EN_Pos)                    /*!< ECAP_T::CTL0: IC0EN Mask               */

#define ECAP_CTL0_IC1EN_Pos              (5)                                               /*!< ECAP_T::CTL0: IC1EN Position           */
#define ECAP_CTL0_IC1EN_Msk              (0x1ul << ECAP_CTL0_IC1EN_Pos)                    /*!< ECAP_T::CTL0: IC1EN Mask               */

#define ECAP_CTL0_IC2EN_Pos              (6)                                               /*!< ECAP_T::CTL0: IC2EN Position           */
#define ECAP_CTL0_IC2EN_Msk              (0x1ul << ECAP_CTL0_IC2EN_Pos)                    /*!< ECAP_T::CTL0: IC2EN Mask               */

#define ECAP_CTL0_CAPSEL0_Pos            (8)                                               /*!< ECAP_T::CTL0: CAPSEL0 Position         */
#define ECAP_CTL0_CAPSEL0_Msk            (0x3ul << ECAP_CTL0_CAPSEL0_Pos)                  /*!< ECAP_T::CTL0: CAPSEL0 Mask             */

#define ECAP_CTL0_CAPSEL1_Pos            (10)                                              /*!< ECAP_T::CTL0: CAPSEL1 Position         */
#define ECAP_CTL0_CAPSEL1_Msk            (0x3ul << ECAP_CTL0_CAPSEL1_Pos)                  /*!< ECAP_T::CTL0: CAPSEL1 Mask             */

#define ECAP_CTL0_CAPSEL2_Pos            (12)                                              /*!< ECAP_T::CTL0: CAPSEL2 Position         */
#define ECAP_CTL0_CAPSEL2_Msk            (0x3ul << ECAP_CTL0_CAPSEL2_Pos)                  /*!< ECAP_T::CTL0: CAPSEL2 Mask             */

#define ECAP_CTL0_CAPIEN0_Pos            (16)                                              /*!< ECAP_T::CTL0: CAPIEN0 Position         */
#define ECAP_CTL0_CAPIEN0_Msk            (0x1ul << ECAP_CTL0_CAPIEN0_Pos)                  /*!< ECAP_T::CTL0: CAPIEN0 Mask             */

#define ECAP_CTL0_CAPIEN1_Pos            (17)                                              /*!< ECAP_T::CTL0: CAPIEN1 Position         */
#define ECAP_CTL0_CAPIEN1_Msk            (0x1ul << ECAP_CTL0_CAPIEN1_Pos)                  /*!< ECAP_T::CTL0: CAPIEN1 Mask             */

#define ECAP_CTL0_CAPIEN2_Pos            (18)                                              /*!< ECAP_T::CTL0: CAPIEN2 Position         */
#define ECAP_CTL0_CAPIEN2_Msk            (0x1ul << ECAP_CTL0_CAPIEN2_Pos)                  /*!< ECAP_T::CTL0: CAPIEN2 Mask             */

#define ECAP_CTL0_OVIEN_Pos              (20)                                              /*!< ECAP_T::CTL0: OVIEN Position           */
#define ECAP_CTL0_OVIEN_Msk              (0x1ul << ECAP_CTL0_OVIEN_Pos)                    /*!< ECAP_T::CTL0: OVIEN Mask               */

#define ECAP_CTL0_CMPIEN_Pos             (21)                                              /*!< ECAP_T::CTL0: CMPIEN Position          */
#define ECAP_CTL0_CMPIEN_Msk             (0x1ul << ECAP_CTL0_CMPIEN_Pos)                   /*!< ECAP_T::CTL0: CMPIEN Mask              */

#define ECAP_CTL0_CNTEN_Pos              (24)                                              /*!< ECAP_T::CTL0: CNTEN Position           */
#define ECAP_CTL0_CNTEN_Msk              (0x1ul << ECAP_CTL0_CNTEN_Pos)                    /*!< ECAP_T::CTL0: CNTEN Mask               */

#define ECAP_CTL0_CMPCLREN_Pos           (25)                                              /*!< ECAP_T::CTL0: CMPCLREN Position        */
#define ECAP_CTL0_CMPCLREN_Msk           (0x1ul << ECAP_CTL0_CMPCLREN_Pos)                 /*!< ECAP_T::CTL0: CMPCLREN Mask            */

#define ECAP_CTL0_CMPEN_Pos              (28)                                              /*!< ECAP_T::CTL0: CMPEN Position           */
#define ECAP_CTL0_CMPEN_Msk              (0x1ul << ECAP_CTL0_CMPEN_Pos)                    /*!< ECAP_T::CTL0: CMPEN Mask               */

#define ECAP_CTL0_CAPEN_Pos              (29)                                              /*!< ECAP_T::CTL0: CAPEN Position           */
#define ECAP_CTL0_CAPEN_Msk              (0x1ul << ECAP_CTL0_CAPEN_Pos)                    /*!< ECAP_T::CTL0: CAPEN Mask               */

#define ECAP_CTL1_EDGESEL0_Pos           (0)                                               /*!< ECAP_T::CTL1: EDGESEL0 Position        */
#define ECAP_CTL1_EDGESEL0_Msk           (0x3ul << ECAP_CTL1_EDGESEL0_Pos)                 /*!< ECAP_T::CTL1: EDGESEL0 Mask            */

#define ECAP_CTL1_EDGESEL1_Pos           (2)                                               /*!< ECAP_T::CTL1: EDGESEL1 Position        */
#define ECAP_CTL1_EDGESEL1_Msk           (0x3ul << ECAP_CTL1_EDGESEL1_Pos)                 /*!< ECAP_T::CTL1: EDGESEL1 Mask            */

#define ECAP_CTL1_EDGESEL2_Pos           (4)                                               /*!< ECAP_T::CTL1: EDGESEL2 Position        */
#define ECAP_CTL1_EDGESEL2_Msk           (0x3ul << ECAP_CTL1_EDGESEL2_Pos)                 /*!< ECAP_T::CTL1: EDGESEL2 Mask            */

#define ECAP_CTL1_CAP0RLDEN_Pos          (8)                                               /*!< ECAP_T::CTL1: CAP0RLDEN Position       */
#define ECAP_CTL1_CAP0RLDEN_Msk          (0x1ul << ECAP_CTL1_CAP0RLDEN_Pos)                /*!< ECAP_T::CTL1: CAP0RLDEN Mask           */

#define ECAP_CTL1_CAP1RLDEN_Pos          (9)                                               /*!< ECAP_T::CTL1: CAP1RLDEN Position       */
#define ECAP_CTL1_CAP1RLDEN_Msk          (0x1ul << ECAP_CTL1_CAP1RLDEN_Pos)                /*!< ECAP_T::CTL1: CAP1RLDEN Mask           */

#define ECAP_CTL1_CAP2RLDEN_Pos          (10)                                              /*!< ECAP_T::CTL1: CAP2RLDEN Position       */
#define ECAP_CTL1_CAP2RLDEN_Msk          (0x1ul << ECAP_CTL1_CAP2RLDEN_Pos)                /*!< ECAP_T::CTL1: CAP2RLDEN Mask           */

#define ECAP_CTL1_OVRLDEN_Pos            (11)                                              /*!< ECAP_T::CTL1: OVRLDEN Position         */
#define ECAP_CTL1_OVRLDEN_Msk            (0x1ul << ECAP_CTL1_OVRLDEN_Pos)                  /*!< ECAP_T::CTL1: OVRLDEN Mask             */

#define ECAP_CTL1_CLKSEL_Pos             (12)                                              /*!< ECAP_T::CTL1: CLKSEL Position          */
#define ECAP_CTL1_CLKSEL_Msk             (0x7ul << ECAP_CTL1_CLKSEL_Pos)                   /*!< ECAP_T::CTL1: CLKSEL Mask              */

#define ECAP_CTL1_CNTSRCSEL_Pos          (16)                                              /*!< ECAP_T::CTL1: CNTSRCSEL Position       */
#define ECAP_CTL1_CNTSRCSEL_Msk          (0x3ul << ECAP_CTL1_CNTSRCSEL_Pos)                /*!< ECAP_T::CTL1: CNTSRCSEL Mask           */

#define ECAP_CTL1_CAP0CLREN_Pos          (20)                                              /*!< ECAP_T::CTL1: CAP0CLREN Position       */
#define ECAP_CTL1_CAP0CLREN_Msk          (0x1ul << ECAP_CTL1_CAP0CLREN_Pos)                /*!< ECAP_T::CTL1: CAP0CLREN Mask           */

#define ECAP_CTL1_CAP1CLREN_Pos          (21)                                              /*!< ECAP_T::CTL1: CAP1CLREN Position       */
#define ECAP_CTL1_CAP1CLREN_Msk          (0x1ul << ECAP_CTL1_CAP1CLREN_Pos)                /*!< ECAP_T::CTL1: CAP1CLREN Mask           */

#define ECAP_CTL1_CAP2CLREN_Pos          (22)                                              /*!< ECAP_T::CTL1: CAP2CLREN Position       */
#define ECAP_CTL1_CAP2CLREN_Msk          (0x1ul << ECAP_CTL1_CAP2CLREN_Pos)                /*!< ECAP_T::CTL1: CAP2CLREN Mask           */

#define ECAP_STATUS_CAPTF0_Pos           (0)                                               /*!< ECAP_T::STATUS: CAPTF0 Position        */
#define ECAP_STATUS_CAPTF0_Msk           (0x1ul << ECAP_STATUS_CAPTF0_Pos)                 /*!< ECAP_T::STATUS: CAPTF0 Mask            */

#define ECAP_STATUS_CAPTF1_Pos           (1)                                               /*!< ECAP_T::STATUS: CAPTF1 Position        */
#define ECAP_STATUS_CAPTF1_Msk           (0x1ul << ECAP_STATUS_CAPTF1_Pos)                 /*!< ECAP_T::STATUS: CAPTF1 Mask            */

#define ECAP_STATUS_CAPTF2_Pos           (2)                                               /*!< ECAP_T::STATUS: CAPTF2 Position        */
#define ECAP_STATUS_CAPTF2_Msk           (0x1ul << ECAP_STATUS_CAPTF2_Pos)                 /*!< ECAP_T::STATUS: CAPTF2 Mask            */

#define ECAP_STATUS_CAPCMPF_Pos          (4)                                               /*!< ECAP_T::STATUS: CAPCMPF Position       */
#define ECAP_STATUS_CAPCMPF_Msk          (0x1ul << ECAP_STATUS_CAPCMPF_Pos)                /*!< ECAP_T::STATUS: CAPCMPF Mask           */

#define ECAP_STATUS_CAPOVF_Pos           (5)                                               /*!< ECAP_T::STATUS: CAPOVF Position        */
#define ECAP_STATUS_CAPOVF_Msk           (0x1ul << ECAP_STATUS_CAPOVF_Pos)                 /*!< ECAP_T::STATUS: CAPOVF Mask            */

#define ECAP_STATUS_CAP0_Pos             (8)                                               /*!< ECAP_T::STATUS: CAP0 Position          */
#define ECAP_STATUS_CAP0_Msk             (0x1ul << ECAP_STATUS_CAP0_Pos)                   /*!< ECAP_T::STATUS: CAP0 Mask              */

#define ECAP_STATUS_CAP1_Pos             (9)                                               /*!< ECAP_T::STATUS: CAP1 Position          */
#define ECAP_STATUS_CAP1_Msk             (0x1ul << ECAP_STATUS_CAP1_Pos)                   /*!< ECAP_T::STATUS: CAP1 Mask              */

#define ECAP_STATUS_CAP2_Pos             (10)                                               /*!< ECAP_T::STATUS: CAP2 Position          */
#define ECAP_STATUS_CAP2_Msk             (0x1ul << ECAP_STATUS_CAP2_Pos)                   /*!< ECAP_T::STATUS: CAP2 Mask              */

/**@}*/ /* ECAP_CONST */
/**@}*/ /* end of ECAP register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __ECAP_REG_H__ */
