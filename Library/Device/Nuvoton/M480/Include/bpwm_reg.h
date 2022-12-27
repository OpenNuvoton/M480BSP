/**************************************************************************//**
 * @file     bpwm_reg.h
 * @version  V1.00
 * @brief    BPWM register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __BPWM_REG_H__
#define __BPWM_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup BPWM Basic Pulse Width Modulation Controller(BPWM)
    Memory Mapped Structure for BPWM Controller
@{ */

typedef struct
{
    /**
@var BCAPDAT_T::RCAPDAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">RCAPDAT
</font><br><p> <font size="2">
Offset: 0x20C  BPWM Rising Capture Data Register 0~5
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>RCAPDAT</td><td><div style="word-wrap: break-word;"><b>BPWM Rising Capture Data (Read Only)
</b><br>
When rising capture condition happened, the BPWM counter value will be saved in this register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BCAPDAT_T::FCAPDAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">FCAPDAT
</font><br><p> <font size="2">
Offset: 0x210  BPWM Falling Capture Data Register 0~5
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>FCAPDAT</td><td><div style="word-wrap: break-word;"><b>BPWM Falling Capture Data (Read Only)
</b><br>
When falling capture condition happened, the BPWM counter value will be saved in this register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t RCAPDAT; /*!< [0x20C/0x214/0x21C/0x224/0x22C/0x234] BPWM Rising Capture Data Register 0~5 */
    __IO uint32_t FCAPDAT; /*!< [0x210/0x218/0x220/0x228/0x230/0x238] BPWM Falling Capture Data Register 0~5 */
} BCAPDAT_T;

typedef struct
{


    /**
@var BPWM_T::CTL0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL0
</font><br><p> <font size="2">
Offset: 0x00  BPWM Control Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CTRLD0</td><td><div style="word-wrap: break-word;"><b>Center Re-load
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
In up-down counter type, PERIOD will load to PBUF at the end point of each period
<br>
CMPDAT will load to CMPBUF at the center point of a period
<br>
</div></td></tr><tr><td>
[1]</td><td>CTRLD1</td><td><div style="word-wrap: break-word;"><b>Center Re-load
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
In up-down counter type, PERIOD will load to PBUF at the end point of each period
<br>
CMPDAT will load to CMPBUF at the center point of a period
<br>
</div></td></tr><tr><td>
[2]</td><td>CTRLD2</td><td><div style="word-wrap: break-word;"><b>Center Re-load
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
In up-down counter type, PERIOD will load to PBUF at the end point of each period
<br>
CMPDAT will load to CMPBUF at the center point of a period
<br>
</div></td></tr><tr><td>
[3]</td><td>CTRLD3</td><td><div style="word-wrap: break-word;"><b>Center Re-load
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
In up-down counter type, PERIOD will load to PBUF at the end point of each period
<br>
CMPDAT will load to CMPBUF at the center point of a period
<br>
</div></td></tr><tr><td>
[4]</td><td>CTRLD4</td><td><div style="word-wrap: break-word;"><b>Center Re-load
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
In up-down counter type, PERIOD will load to PBUF at the end point of each period
<br>
CMPDAT will load to CMPBUF at the center point of a period
<br>
</div></td></tr><tr><td>
[5]</td><td>CTRLD5</td><td><div style="word-wrap: break-word;"><b>Center Re-load
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
In up-down counter type, PERIOD will load to PBUF at the end point of each period
<br>
CMPDAT will load to CMPBUF at the center point of a period
<br>
</div></td></tr><tr><td>
[16]</td><td>IMMLDEN0</td><td><div style="word-wrap: break-word;"><b>Immediately Load Enable Bit(S)
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = PERIOD will load to PBUF at the end point of each period
<br>
CMPDAT will load to CMPBUF at the end point or center point of each period by setting CTRLD bit.
<br>
1 = PERIOD/CMPDAT will load to PBUF and CMPBUF immediately when software update PERIOD/CMPDAT.
<br>
Note: If IMMLDENn is Enabled, WINLDENn and CTRLDn will be invalid.
<br>
</div></td></tr><tr><td>
[17]</td><td>IMMLDEN1</td><td><div style="word-wrap: break-word;"><b>Immediately Load Enable Bit(S)
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = PERIOD will load to PBUF at the end point of each period
<br>
CMPDAT will load to CMPBUF at the end point or center point of each period by setting CTRLD bit.
<br>
1 = PERIOD/CMPDAT will load to PBUF and CMPBUF immediately when software update PERIOD/CMPDAT.
<br>
Note: If IMMLDENn is Enabled, WINLDENn and CTRLDn will be invalid.
<br>
</div></td></tr><tr><td>
[18]</td><td>IMMLDEN2</td><td><div style="word-wrap: break-word;"><b>Immediately Load Enable Bit(S)
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = PERIOD will load to PBUF at the end point of each period
<br>
CMPDAT will load to CMPBUF at the end point or center point of each period by setting CTRLD bit.
<br>
1 = PERIOD/CMPDAT will load to PBUF and CMPBUF immediately when software update PERIOD/CMPDAT.
<br>
Note: If IMMLDENn is Enabled, WINLDENn and CTRLDn will be invalid.
<br>
</div></td></tr><tr><td>
[19]</td><td>IMMLDEN3</td><td><div style="word-wrap: break-word;"><b>Immediately Load Enable Bit(S)
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = PERIOD will load to PBUF at the end point of each period
<br>
CMPDAT will load to CMPBUF at the end point or center point of each period by setting CTRLD bit.
<br>
1 = PERIOD/CMPDAT will load to PBUF and CMPBUF immediately when software update PERIOD/CMPDAT.
<br>
Note: If IMMLDENn is Enabled, WINLDENn and CTRLDn will be invalid.
<br>
</div></td></tr><tr><td>
[20]</td><td>IMMLDEN4</td><td><div style="word-wrap: break-word;"><b>Immediately Load Enable Bit(S)
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = PERIOD will load to PBUF at the end point of each period
<br>
CMPDAT will load to CMPBUF at the end point or center point of each period by setting CTRLD bit.
<br>
1 = PERIOD/CMPDAT will load to PBUF and CMPBUF immediately when software update PERIOD/CMPDAT.
<br>
Note: If IMMLDENn is Enabled, WINLDENn and CTRLDn will be invalid.
<br>
</div></td></tr><tr><td>
[21]</td><td>IMMLDEN5</td><td><div style="word-wrap: break-word;"><b>Immediately Load Enable Bit(S)
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = PERIOD will load to PBUF at the end point of each period
<br>
CMPDAT will load to CMPBUF at the end point or center point of each period by setting CTRLD bit.
<br>
1 = PERIOD/CMPDAT will load to PBUF and CMPBUF immediately when software update PERIOD/CMPDAT.
<br>
Note: If IMMLDENn is Enabled, WINLDENn and CTRLDn will be invalid.
<br>
</div></td></tr><tr><td>
[30]</td><td>DBGHALT</td><td><div style="word-wrap: break-word;"><b>ICE Debug Mode Counter Halt (Write Protect)
</b><br>
If counter halt is enabled, BPWM all counters will keep current value until exit ICE debug mode.
<br>
0 = ICE debug mode counter halt Disabled.
<br>
1 = ICE debug mode counter halt Enabled.
<br>
Note: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[31]</td><td>DBGTRIOFF</td><td><div style="word-wrap: break-word;"><b>ICE Debug Mode Acknowledge Disable (Write Protect)
</b><br>
0 = ICE debug mode acknowledgement effects BPWM output.
<br>
BPWM pin will be forced as tri-state while ICE debug mode acknowledged.
<br>
1 = ICE debug mode acknowledgement Disabled.
<br>
BPWM pin will keep output no matter ICE debug mode acknowledged or not.
<br>
Note: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::CTL1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL1
</font><br><p> <font size="2">
Offset: 0x04  BPWM Control Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1:0]</td><td>CNTTYPE0</td><td><div style="word-wrap: break-word;"><b>BPWM Counter Behavior Type 0
</b><br>
Each bit n controls corresponding BPWM channel n.
<br>
00 = Up counter type (supports in capture mode).
<br>
01 = Down count type (supports in capture mode).
<br>
10 = Up-down counter type.
<br>
11 = Reserved.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::CLKSRC

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKSRC
</font><br><p> <font size="2">
Offset: 0x10  BPWM Clock Source Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2:0]</td><td>ECLKSRC0</td><td><div style="word-wrap: break-word;"><b>BPWM_CH01 External Clock Source Select
</b><br>
000 = BPWMx_CLK, x denotes 0 or 1.
<br>
001 = TIMER0 overflow.
<br>
010 = TIMER1 overflow.
<br>
011 = TIMER2 overflow.
<br>
100 = TIMER3 overflow.
<br>
Others = Reserved.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::CLKPSC

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKPSC
</font><br><p> <font size="2">
Offset: 0x14  BPWM Clock Prescale Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[11:0]</td><td>CLKPSC</td><td><div style="word-wrap: break-word;"><b>BPWM Counter Clock Prescale
</b><br>
The clock of BPWM counter is decided by clock prescaler
<br>
Each BPWM pair share one BPWM counter clock prescaler
<br>
The clock of BPWM counter is divided by (CLKPSC+ 1)
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::CNTEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CNTEN
</font><br><p> <font size="2">
Offset: 0x20  BPWM Counter Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CNTEN0</td><td><div style="word-wrap: break-word;"><b>BPWM Counter 0 Enable Bit
</b><br>
0 = BPWM Counter and clock prescaler stop running.
<br>
1 = BPWM Counter and clock prescaler start running.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::CNTCLR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CNTCLR
</font><br><p> <font size="2">
Offset: 0x24  BPWM Clear Counter Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CNTCLR0</td><td><div style="word-wrap: break-word;"><b>Clear BPWM Counter Control Bit 0
</b><br>
It is automatically cleared by hardware.
<br>
0 = No effect.
<br>
1 = Clear 16-bit BPWM counter to 0000H.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::PERIOD

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PERIOD
</font><br><p> <font size="2">
Offset: 0x30  BPWM Period Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>PERIOD</td><td><div style="word-wrap: break-word;"><b>BPWM Period Register
</b><br>
Up-Count mode: In this mode, BPWM counter counts from 0 to PERIOD, and restarts from 0.
<br>
Down-Count mode: In this mode, BPWM counter counts from PERIOD to 0, and restarts from PERIOD.
<br>
BPWM period time = (PERIOD+1) * BPWM_CLK period.
<br>
Up-Down-Count mode: In this mode, BPWM counter counts from 0 to PERIOD, then decrements to 0 and repeats again.
<br>
BPWM period time = 2 * PERIOD * BPWM_CLK period.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::CMPDAT[6]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CMPDAT[6]
</font><br><p> <font size="2">
Offset: 0x50  BPWM Comparator Register 0~5
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>CMPDAT</td><td><div style="word-wrap: break-word;"><b>BPWM Comparator Register
</b><br>
CMPDAT use to compare with CNTR to generate BPWM waveform, interrupt and trigger EADC.
<br>
In independent mode, CMPDAT0~5 denote as 6 independent BPWM_CH0~5 compared point.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::CNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CNT
</font><br><p> <font size="2">
Offset: 0x90  BPWM Counter Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>CNT</td><td><div style="word-wrap: break-word;"><b>BPWM Data Register (Read Only)
</b><br>
User can monitor CNTR to know the current value in 16-bit period counter.
<br>
</div></td></tr><tr><td>
[16]</td><td>DIRF</td><td><div style="word-wrap: break-word;"><b>BPWM Direction Indicator Flag (Read Only)
</b><br>
0 = Counter is Down count.
<br>
1 = Counter is UP count.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::WGCTL0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">WGCTL0
</font><br><p> <font size="2">
Offset: 0xB0  BPWM Generation Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1:0]</td><td>ZPCTL0</td><td><div style="word-wrap: break-word;"><b>BPWM Zero Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM zero point output Low.
<br>
10 = BPWM zero point output High.
<br>
11 = BPWM zero point output Toggle.
<br>
BPWM can control output level when BPWM counter count to zero.
<br>
</div></td></tr><tr><td>
[3:2]</td><td>ZPCTL1</td><td><div style="word-wrap: break-word;"><b>BPWM Zero Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM zero point output Low.
<br>
10 = BPWM zero point output High.
<br>
11 = BPWM zero point output Toggle.
<br>
BPWM can control output level when BPWM counter count to zero.
<br>
</div></td></tr><tr><td>
[5:4]</td><td>ZPCTL2</td><td><div style="word-wrap: break-word;"><b>BPWM Zero Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM zero point output Low.
<br>
10 = BPWM zero point output High.
<br>
11 = BPWM zero point output Toggle.
<br>
BPWM can control output level when BPWM counter count to zero.
<br>
</div></td></tr><tr><td>
[7:6]</td><td>ZPCTL3</td><td><div style="word-wrap: break-word;"><b>BPWM Zero Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM zero point output Low.
<br>
10 = BPWM zero point output High.
<br>
11 = BPWM zero point output Toggle.
<br>
BPWM can control output level when BPWM counter count to zero.
<br>
</div></td></tr><tr><td>
[9:8]</td><td>ZPCTL4</td><td><div style="word-wrap: break-word;"><b>BPWM Zero Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM zero point output Low.
<br>
10 = BPWM zero point output High.
<br>
11 = BPWM zero point output Toggle.
<br>
BPWM can control output level when BPWM counter count to zero.
<br>
</div></td></tr><tr><td>
[11:10]</td><td>ZPCTL5</td><td><div style="word-wrap: break-word;"><b>BPWM Zero Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM zero point output Low.
<br>
10 = BPWM zero point output High.
<br>
11 = BPWM zero point output Toggle.
<br>
BPWM can control output level when BPWM counter count to zero.
<br>
</div></td></tr><tr><td>
[17:16]</td><td>PRDPCTL0</td><td><div style="word-wrap: break-word;"><b>BPWM Period (Center) Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM period (center) point output Low.
<br>
10 = BPWM period (center) point output High.
<br>
11 = BPWM period (center) point output Toggle.
<br>
BPWM can control output level when BPWM counter count to (PERIOD+1).
<br>
Note: This bit is center point control when BPWM counter operating in up-down counter type.
<br>
</div></td></tr><tr><td>
[19:18]</td><td>PRDPCTL1</td><td><div style="word-wrap: break-word;"><b>BPWM Period (Center) Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM period (center) point output Low.
<br>
10 = BPWM period (center) point output High.
<br>
11 = BPWM period (center) point output Toggle.
<br>
BPWM can control output level when BPWM counter count to (PERIOD+1).
<br>
Note: This bit is center point control when BPWM counter operating in up-down counter type.
<br>
</div></td></tr><tr><td>
[21:20]</td><td>PRDPCTL2</td><td><div style="word-wrap: break-word;"><b>BPWM Period (Center) Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM period (center) point output Low.
<br>
10 = BPWM period (center) point output High.
<br>
11 = BPWM period (center) point output Toggle.
<br>
BPWM can control output level when BPWM counter count to (PERIOD+1).
<br>
Note: This bit is center point control when BPWM counter operating in up-down counter type.
<br>
</div></td></tr><tr><td>
[23:22]</td><td>PRDPCTL3</td><td><div style="word-wrap: break-word;"><b>BPWM Period (Center) Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM period (center) point output Low.
<br>
10 = BPWM period (center) point output High.
<br>
11 = BPWM period (center) point output Toggle.
<br>
BPWM can control output level when BPWM counter count to (PERIOD+1).
<br>
Note: This bit is center point control when BPWM counter operating in up-down counter type.
<br>
</div></td></tr><tr><td>
[25:24]</td><td>PRDPCTL4</td><td><div style="word-wrap: break-word;"><b>BPWM Period (Center) Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM period (center) point output Low.
<br>
10 = BPWM period (center) point output High.
<br>
11 = BPWM period (center) point output Toggle.
<br>
BPWM can control output level when BPWM counter count to (PERIOD+1).
<br>
Note: This bit is center point control when BPWM counter operating in up-down counter type.
<br>
</div></td></tr><tr><td>
[27:26]</td><td>PRDPCTL5</td><td><div style="word-wrap: break-word;"><b>BPWM Period (Center) Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM period (center) point output Low.
<br>
10 = BPWM period (center) point output High.
<br>
11 = BPWM period (center) point output Toggle.
<br>
BPWM can control output level when BPWM counter count to (PERIOD+1).
<br>
Note: This bit is center point control when BPWM counter operating in up-down counter type.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::WGCTL1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">WGCTL1
</font><br><p> <font size="2">
Offset: 0xB4  BPWM Generation Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1:0]</td><td>CMPUCTL0</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Up Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM compare up point output Low.
<br>
10 = BPWM compare up point output High.
<br>
11 = BPWM compare up point output Toggle.
<br>
BPWM can control output level when BPWM counter up count to CMPDAT.
<br>
</div></td></tr><tr><td>
[3:2]</td><td>CMPUCTL1</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Up Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM compare up point output Low.
<br>
10 = BPWM compare up point output High.
<br>
11 = BPWM compare up point output Toggle.
<br>
BPWM can control output level when BPWM counter up count to CMPDAT.
<br>
</div></td></tr><tr><td>
[5:4]</td><td>CMPUCTL2</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Up Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM compare up point output Low.
<br>
10 = BPWM compare up point output High.
<br>
11 = BPWM compare up point output Toggle.
<br>
BPWM can control output level when BPWM counter up count to CMPDAT.
<br>
</div></td></tr><tr><td>
[7:6]</td><td>CMPUCTL3</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Up Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM compare up point output Low.
<br>
10 = BPWM compare up point output High.
<br>
11 = BPWM compare up point output Toggle.
<br>
BPWM can control output level when BPWM counter up count to CMPDAT.
<br>
</div></td></tr><tr><td>
[9:8]</td><td>CMPUCTL4</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Up Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM compare up point output Low.
<br>
10 = BPWM compare up point output High.
<br>
11 = BPWM compare up point output Toggle.
<br>
BPWM can control output level when BPWM counter up count to CMPDAT.
<br>
</div></td></tr><tr><td>
[11:10]</td><td>CMPUCTL5</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Up Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM compare up point output Low.
<br>
10 = BPWM compare up point output High.
<br>
11 = BPWM compare up point output Toggle.
<br>
BPWM can control output level when BPWM counter up count to CMPDAT.
<br>
</div></td></tr><tr><td>
[17:16]</td><td>CMPDCTL0</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Down Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM compare down point output Low.
<br>
10 = BPWM compare down point output High.
<br>
11 = BPWM compare down point output Toggle.
<br>
BPWM can control output level when BPWM counter down count to CMPDAT.
<br>
</div></td></tr><tr><td>
[19:18]</td><td>CMPDCTL1</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Down Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM compare down point output Low.
<br>
10 = BPWM compare down point output High.
<br>
11 = BPWM compare down point output Toggle.
<br>
BPWM can control output level when BPWM counter down count to CMPDAT.
<br>
</div></td></tr><tr><td>
[21:20]</td><td>CMPDCTL2</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Down Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM compare down point output Low.
<br>
10 = BPWM compare down point output High.
<br>
11 = BPWM compare down point output Toggle.
<br>
BPWM can control output level when BPWM counter down count to CMPDAT.
<br>
</div></td></tr><tr><td>
[23:22]</td><td>CMPDCTL3</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Down Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM compare down point output Low.
<br>
10 = BPWM compare down point output High.
<br>
11 = BPWM compare down point output Toggle.
<br>
BPWM can control output level when BPWM counter down count to CMPDAT.
<br>
</div></td></tr><tr><td>
[25:24]</td><td>CMPDCTL4</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Down Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM compare down point output Low.
<br>
10 = BPWM compare down point output High.
<br>
11 = BPWM compare down point output Toggle.
<br>
BPWM can control output level when BPWM counter down count to CMPDAT.
<br>
</div></td></tr><tr><td>
[27:26]</td><td>CMPDCTL5</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Down Point Control
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
00 = Do nothing.
<br>
01 = BPWM compare down point output Low.
<br>
10 = BPWM compare down point output High.
<br>
11 = BPWM compare down point output Toggle.
<br>
BPWM can control output level when BPWM counter down count to CMPDAT.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::MSKEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MSKEN
</font><br><p> <font size="2">
Offset: 0xB8  BPWM Mask Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>MSKEN0</td><td><div style="word-wrap: break-word;"><b>BPWM Mask Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
The BPWM output signal will be masked when this bit is enabled
<br>
The corresponding BPWM channel n will output MSKDATn (BPWM_MSK[5:0]) data.
<br>
0 = BPWM output signal is non-masked.
<br>
1 = BPWM output signal is masked and output MSKDATn data.
<br>
</div></td></tr><tr><td>
[1]</td><td>MSKEN1</td><td><div style="word-wrap: break-word;"><b>BPWM Mask Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
The BPWM output signal will be masked when this bit is enabled
<br>
The corresponding BPWM channel n will output MSKDATn (BPWM_MSK[5:0]) data.
<br>
0 = BPWM output signal is non-masked.
<br>
1 = BPWM output signal is masked and output MSKDATn data.
<br>
</div></td></tr><tr><td>
[2]</td><td>MSKEN2</td><td><div style="word-wrap: break-word;"><b>BPWM Mask Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
The BPWM output signal will be masked when this bit is enabled
<br>
The corresponding BPWM channel n will output MSKDATn (BPWM_MSK[5:0]) data.
<br>
0 = BPWM output signal is non-masked.
<br>
1 = BPWM output signal is masked and output MSKDATn data.
<br>
</div></td></tr><tr><td>
[3]</td><td>MSKEN3</td><td><div style="word-wrap: break-word;"><b>BPWM Mask Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
The BPWM output signal will be masked when this bit is enabled
<br>
The corresponding BPWM channel n will output MSKDATn (BPWM_MSK[5:0]) data.
<br>
0 = BPWM output signal is non-masked.
<br>
1 = BPWM output signal is masked and output MSKDATn data.
<br>
</div></td></tr><tr><td>
[4]</td><td>MSKEN4</td><td><div style="word-wrap: break-word;"><b>BPWM Mask Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
The BPWM output signal will be masked when this bit is enabled
<br>
The corresponding BPWM channel n will output MSKDATn (BPWM_MSK[5:0]) data.
<br>
0 = BPWM output signal is non-masked.
<br>
1 = BPWM output signal is masked and output MSKDATn data.
<br>
</div></td></tr><tr><td>
[5]</td><td>MSKEN5</td><td><div style="word-wrap: break-word;"><b>BPWM Mask Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
The BPWM output signal will be masked when this bit is enabled
<br>
The corresponding BPWM channel n will output MSKDATn (BPWM_MSK[5:0]) data.
<br>
0 = BPWM output signal is non-masked.
<br>
1 = BPWM output signal is masked and output MSKDATn data.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::MSK

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MSK
</font><br><p> <font size="2">
Offset: 0xBC  BPWM Mask Data Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>MSKDAT0</td><td><div style="word-wrap: break-word;"><b>BPWM Mask Data Bit
</b><br>
This data bit control the state of BPWMn output pin, if corresponding mask function is enabled
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Output logic low to BPWMn.
<br>
1 = Output logic high to BPWMn.
<br>
</div></td></tr><tr><td>
[1]</td><td>MSKDAT1</td><td><div style="word-wrap: break-word;"><b>BPWM Mask Data Bit
</b><br>
This data bit control the state of BPWMn output pin, if corresponding mask function is enabled
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Output logic low to BPWMn.
<br>
1 = Output logic high to BPWMn.
<br>
</div></td></tr><tr><td>
[2]</td><td>MSKDAT2</td><td><div style="word-wrap: break-word;"><b>BPWM Mask Data Bit
</b><br>
This data bit control the state of BPWMn output pin, if corresponding mask function is enabled
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Output logic low to BPWMn.
<br>
1 = Output logic high to BPWMn.
<br>
</div></td></tr><tr><td>
[3]</td><td>MSKDAT3</td><td><div style="word-wrap: break-word;"><b>BPWM Mask Data Bit
</b><br>
This data bit control the state of BPWMn output pin, if corresponding mask function is enabled
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Output logic low to BPWMn.
<br>
1 = Output logic high to BPWMn.
<br>
</div></td></tr><tr><td>
[4]</td><td>MSKDAT4</td><td><div style="word-wrap: break-word;"><b>BPWM Mask Data Bit
</b><br>
This data bit control the state of BPWMn output pin, if corresponding mask function is enabled
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Output logic low to BPWMn.
<br>
1 = Output logic high to BPWMn.
<br>
</div></td></tr><tr><td>
[5]</td><td>MSKDAT5</td><td><div style="word-wrap: break-word;"><b>BPWM Mask Data Bit
</b><br>
This data bit control the state of BPWMn output pin, if corresponding mask function is enabled
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Output logic low to BPWMn.
<br>
1 = Output logic high to BPWMn.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::POLCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">POLCTL
</font><br><p> <font size="2">
Offset: 0xD4  BPWM Pin Polar Inverse Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>PINV0</td><td><div style="word-wrap: break-word;"><b>BPWM PIN Polar Inverse Control
</b><br>
The register controls polarity state of BPWM output
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = BPWM output polar inverse Disabled.
<br>
1 = BPWM output polar inverse Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>PINV1</td><td><div style="word-wrap: break-word;"><b>BPWM PIN Polar Inverse Control
</b><br>
The register controls polarity state of BPWM output
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = BPWM output polar inverse Disabled.
<br>
1 = BPWM output polar inverse Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>PINV2</td><td><div style="word-wrap: break-word;"><b>BPWM PIN Polar Inverse Control
</b><br>
The register controls polarity state of BPWM output
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = BPWM output polar inverse Disabled.
<br>
1 = BPWM output polar inverse Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>PINV3</td><td><div style="word-wrap: break-word;"><b>BPWM PIN Polar Inverse Control
</b><br>
The register controls polarity state of BPWM output
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = BPWM output polar inverse Disabled.
<br>
1 = BPWM output polar inverse Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>PINV4</td><td><div style="word-wrap: break-word;"><b>BPWM PIN Polar Inverse Control
</b><br>
The register controls polarity state of BPWM output
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = BPWM output polar inverse Disabled.
<br>
1 = BPWM output polar inverse Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>PINV5</td><td><div style="word-wrap: break-word;"><b>BPWM PIN Polar Inverse Control
</b><br>
The register controls polarity state of BPWM output
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = BPWM output polar inverse Disabled.
<br>
1 = BPWM output polar inverse Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::POEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">POEN
</font><br><p> <font size="2">
Offset: 0xD8  BPWM Output Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>POEN0</td><td><div style="word-wrap: break-word;"><b>BPWM Pin Output Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = BPWM pin at tri-state.
<br>
1 = BPWM pin in output mode.
<br>
</div></td></tr><tr><td>
[1]</td><td>POEN1</td><td><div style="word-wrap: break-word;"><b>BPWM Pin Output Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = BPWM pin at tri-state.
<br>
1 = BPWM pin in output mode.
<br>
</div></td></tr><tr><td>
[2]</td><td>POEN2</td><td><div style="word-wrap: break-word;"><b>BPWM Pin Output Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = BPWM pin at tri-state.
<br>
1 = BPWM pin in output mode.
<br>
</div></td></tr><tr><td>
[3]</td><td>POEN3</td><td><div style="word-wrap: break-word;"><b>BPWM Pin Output Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = BPWM pin at tri-state.
<br>
1 = BPWM pin in output mode.
<br>
</div></td></tr><tr><td>
[4]</td><td>POEN4</td><td><div style="word-wrap: break-word;"><b>BPWM Pin Output Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = BPWM pin at tri-state.
<br>
1 = BPWM pin in output mode.
<br>
</div></td></tr><tr><td>
[5]</td><td>POEN5</td><td><div style="word-wrap: break-word;"><b>BPWM Pin Output Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = BPWM pin at tri-state.
<br>
1 = BPWM pin in output mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::INTEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTEN
</font><br><p> <font size="2">
Offset: 0xE0  BPWM Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ZIEN0</td><td><div style="word-wrap: break-word;"><b>BPWM Zero Point Interrupt 0 Enable Bit
</b><br>
0 = Zero point interrupt Disabled.
<br>
1 = Zero point interrupt Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>PIEN0</td><td><div style="word-wrap: break-word;"><b>BPWM Period Point Interrupt 0 Enable Bit
</b><br>
0 = Period point interrupt Disabled.
<br>
1 = Period point interrupt Enabled.
<br>
Note: When up-down counter type period point means center point.
<br>
</div></td></tr><tr><td>
[16]</td><td>CMPUIEN0</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Up Count Interrupt Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Compare up count interrupt Disabled.
<br>
1 = Compare up count interrupt Enabled.
<br>
</div></td></tr><tr><td>
[17]</td><td>CMPUIEN1</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Up Count Interrupt Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Compare up count interrupt Disabled.
<br>
1 = Compare up count interrupt Enabled.
<br>
</div></td></tr><tr><td>
[18]</td><td>CMPUIEN2</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Up Count Interrupt Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Compare up count interrupt Disabled.
<br>
1 = Compare up count interrupt Enabled.
<br>
</div></td></tr><tr><td>
[19]</td><td>CMPUIEN3</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Up Count Interrupt Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Compare up count interrupt Disabled.
<br>
1 = Compare up count interrupt Enabled.
<br>
</div></td></tr><tr><td>
[20]</td><td>CMPUIEN4</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Up Count Interrupt Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Compare up count interrupt Disabled.
<br>
1 = Compare up count interrupt Enabled.
<br>
</div></td></tr><tr><td>
[21]</td><td>CMPUIEN5</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Up Count Interrupt Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Compare up count interrupt Disabled.
<br>
1 = Compare up count interrupt Enabled.
<br>
</div></td></tr><tr><td>
[24]</td><td>CMPDIEN0</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Down Count Interrupt Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Compare down count interrupt Disabled.
<br>
1 = Compare down count interrupt Enabled.
<br>
</div></td></tr><tr><td>
[25]</td><td>CMPDIEN1</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Down Count Interrupt Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Compare down count interrupt Disabled.
<br>
1 = Compare down count interrupt Enabled.
<br>
</div></td></tr><tr><td>
[26]</td><td>CMPDIEN2</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Down Count Interrupt Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Compare down count interrupt Disabled.
<br>
1 = Compare down count interrupt Enabled.
<br>
</div></td></tr><tr><td>
[27]</td><td>CMPDIEN3</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Down Count Interrupt Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Compare down count interrupt Disabled.
<br>
1 = Compare down count interrupt Enabled.
<br>
</div></td></tr><tr><td>
[28]</td><td>CMPDIEN4</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Down Count Interrupt Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Compare down count interrupt Disabled.
<br>
1 = Compare down count interrupt Enabled.
<br>
</div></td></tr><tr><td>
[29]</td><td>CMPDIEN5</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Down Count Interrupt Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Compare down count interrupt Disabled.
<br>
1 = Compare down count interrupt Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::INTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTSTS
</font><br><p> <font size="2">
Offset: 0xE8  BPWM Interrupt Flag Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ZIF0</td><td><div style="word-wrap: break-word;"><b>BPWM Zero Point Interrupt Flag 0
</b><br>
This bit is set by hardware when BPWM_CH0 counter reaches zero, software can write 1 to clear this bit to zero.
<br>
</div></td></tr><tr><td>
[8]</td><td>PIF0</td><td><div style="word-wrap: break-word;"><b>BPWM Period Point Interrupt Flag 0
</b><br>
This bit is set by hardware when BPWM_CH0 counter reaches BPWM_PERIOD0, software can write 1 to clear this bit to zero.
<br>
</div></td></tr><tr><td>
[16]</td><td>CMPUIF0</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Up Count Interrupt Flag
</b><br>
Flag is set by hardware when BPWM counter up count and reaches BPWM_CMPDATn, software can clear this bit by writing 1 to it
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
Note: If CMPDAT equal to PERIOD, this flag is not working in up counter type selection.
<br>
</div></td></tr><tr><td>
[17]</td><td>CMPUIF1</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Up Count Interrupt Flag
</b><br>
Flag is set by hardware when BPWM counter up count and reaches BPWM_CMPDATn, software can clear this bit by writing 1 to it
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
Note: If CMPDAT equal to PERIOD, this flag is not working in up counter type selection.
<br>
</div></td></tr><tr><td>
[18]</td><td>CMPUIF2</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Up Count Interrupt Flag
</b><br>
Flag is set by hardware when BPWM counter up count and reaches BPWM_CMPDATn, software can clear this bit by writing 1 to it
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
Note: If CMPDAT equal to PERIOD, this flag is not working in up counter type selection.
<br>
</div></td></tr><tr><td>
[19]</td><td>CMPUIF3</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Up Count Interrupt Flag
</b><br>
Flag is set by hardware when BPWM counter up count and reaches BPWM_CMPDATn, software can clear this bit by writing 1 to it
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
Note: If CMPDAT equal to PERIOD, this flag is not working in up counter type selection.
<br>
</div></td></tr><tr><td>
[20]</td><td>CMPUIF4</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Up Count Interrupt Flag
</b><br>
Flag is set by hardware when BPWM counter up count and reaches BPWM_CMPDATn, software can clear this bit by writing 1 to it
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
Note: If CMPDAT equal to PERIOD, this flag is not working in up counter type selection.
<br>
</div></td></tr><tr><td>
[21]</td><td>CMPUIF5</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Up Count Interrupt Flag
</b><br>
Flag is set by hardware when BPWM counter up count and reaches BPWM_CMPDATn, software can clear this bit by writing 1 to it
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
Note: If CMPDAT equal to PERIOD, this flag is not working in up counter type selection.
<br>
</div></td></tr><tr><td>
[24]</td><td>CMPDIF0</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Down Count Interrupt Flag
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
Flag is set by hardware when BPWM counter down count and reaches BPWM_CMPDATn, software can clear this bit by writing 1 to it.
<br>
Note: If CMPDAT equal to PERIOD, this flag is not working in down counter type selection.
<br>
</div></td></tr><tr><td>
[25]</td><td>CMPDIF1</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Down Count Interrupt Flag
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
Flag is set by hardware when BPWM counter down count and reaches BPWM_CMPDATn, software can clear this bit by writing 1 to it.
<br>
Note: If CMPDAT equal to PERIOD, this flag is not working in down counter type selection.
<br>
</div></td></tr><tr><td>
[26]</td><td>CMPDIF2</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Down Count Interrupt Flag
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
Flag is set by hardware when BPWM counter down count and reaches BPWM_CMPDATn, software can clear this bit by writing 1 to it.
<br>
Note: If CMPDAT equal to PERIOD, this flag is not working in down counter type selection.
<br>
</div></td></tr><tr><td>
[27]</td><td>CMPDIF3</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Down Count Interrupt Flag
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
Flag is set by hardware when BPWM counter down count and reaches BPWM_CMPDATn, software can clear this bit by writing 1 to it.
<br>
Note: If CMPDAT equal to PERIOD, this flag is not working in down counter type selection.
<br>
</div></td></tr><tr><td>
[28]</td><td>CMPDIF4</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Down Count Interrupt Flag
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
Flag is set by hardware when BPWM counter down count and reaches BPWM_CMPDATn, software can clear this bit by writing 1 to it.
<br>
Note: If CMPDAT equal to PERIOD, this flag is not working in down counter type selection.
<br>
</div></td></tr><tr><td>
[29]</td><td>CMPDIF5</td><td><div style="word-wrap: break-word;"><b>BPWM Compare Down Count Interrupt Flag
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
Flag is set by hardware when BPWM counter down count and reaches BPWM_CMPDATn, software can clear this bit by writing 1 to it.
<br>
Note: If CMPDAT equal to PERIOD, this flag is not working in down counter type selection.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::EADCTS0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EADCTS0
</font><br><p> <font size="2">
Offset: 0xF8  BPWM Trigger EADC Source Select Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>TRGSEL0</td><td><div style="word-wrap: break-word;"><b>BPWM_CH0 Trigger EADC Source Select
</b><br>
0000 = BPWM_CH0 zero point.
<br>
0001 = BPWM_CH0 period point.
<br>
0010 = BPWM_CH0 zero or period point.
<br>
0011 = BPWM_CH0 up-count CMPDAT point.
<br>
0100 = BPWM_CH0 down-count CMPDAT point.
<br>
0101 = Reserved.
<br>
0110 = Reserved.
<br>
0111 = Reserved.
<br>
1000 = BPWM_CH1 up-count CMPDAT point.
<br>
1001 = BPWM_CH1 down-count CMPDAT point.
<br>
Others reserved
<br>
</div></td></tr><tr><td>
[7]</td><td>TRGEN0</td><td><div style="word-wrap: break-word;"><b>BPWM_CH0 Trigger EADC Enable Bit
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>TRGSEL1</td><td><div style="word-wrap: break-word;"><b>BPWM_CH1 Trigger EADC Source Select
</b><br>
0000 = BPWM_CH0 zero point.
<br>
0001 = BPWM_CH0 period point.
<br>
0010 = BPWM_CH0 zero or period point.
<br>
0011 = BPWM_CH0 up-count CMPDAT point.
<br>
0100 = BPWM_CH0 down-count CMPDAT point.
<br>
0101 = Reserved.
<br>
0110 = Reserved.
<br>
0111 = Reserved.
<br>
1000 = BPWM_CH1 up-count CMPDAT point.
<br>
1001 = BPWM_CH1 down-count CMPDAT point.
<br>
Others reserved
<br>
</div></td></tr><tr><td>
[15]</td><td>TRGEN1</td><td><div style="word-wrap: break-word;"><b>BPWM_CH1 Trigger EADC Enable Bit
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>TRGSEL2</td><td><div style="word-wrap: break-word;"><b>BPWM_CH2 Trigger EADC Source Select
</b><br>
0000 = BPWM_CH2 zero point.
<br>
0001 = BPWM_CH2 period point.
<br>
0010 = BPWM_CH2 zero or period point.
<br>
0011 = BPWM_CH2 up-count CMPDAT point.
<br>
0100 = BPWM_CH2 down-count CMPDAT point.
<br>
0101 = Reserved.
<br>
0110 = Reserved.
<br>
0111 = Reserved.
<br>
1000 = BPWM_CH3 up-count CMPDAT point.
<br>
1001 = BPWM_CH3 down-count CMPDAT point.
<br>
Others reserved
<br>
</div></td></tr><tr><td>
[23]</td><td>TRGEN2</td><td><div style="word-wrap: break-word;"><b>BPWM_CH2 Trigger EADC Enable Bit
</b><br>
</div></td></tr><tr><td>
[27:24]</td><td>TRGSEL3</td><td><div style="word-wrap: break-word;"><b>BPWM_CH3 Trigger EADC Source Select
</b><br>
0000 = BPWM_CH2 zero point.
<br>
0001 = BPWM_CH2 period point.
<br>
0010 = BPWM_CH2 zero or period point.
<br>
0011 = BPWM_CH2 up-count CMPDAT point.
<br>
0100 = BPWM_CH2 down-count CMPDAT point.
<br>
0101 = Reserved.
<br>
0110 = Reserved.
<br>
0111 = Reserved.
<br>
1000 = BPWM_CH3 up-count CMPDAT point.
<br>
1001 = BPWM_CH3 down-count CMPDAT point.
<br>
Others reserved.
<br>
</div></td></tr><tr><td>
[31]</td><td>TRGEN3</td><td><div style="word-wrap: break-word;"><b>BPWM_CH3 Trigger EADC Enable Bit
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::EADCTS1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EADCTS1
</font><br><p> <font size="2">
Offset: 0xFC  BPWM Trigger EADC Source Select Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>TRGSEL4</td><td><div style="word-wrap: break-word;"><b>BPWM_CH4 Trigger EADC Source Select
</b><br>
0000 = BPWM_CH4 zero point.
<br>
0001 = BPWM_CH4 period point.
<br>
0010 = BPWM_CH4 zero or period point.
<br>
0011 = BPWM_CH4 up-count CMPDAT point.
<br>
0100 = BPWM_CH4 down-count CMPDAT point.
<br>
0101 = Reserved.
<br>
0110 = Reserved.
<br>
0111 = Reserved.
<br>
1000 = BPWM_CH5 up-count CMPDAT point.
<br>
1001 = BPWM_CH5 down-count CMPDAT point.
<br>
Others reserved
<br>
</div></td></tr><tr><td>
[7]</td><td>TRGEN4</td><td><div style="word-wrap: break-word;"><b>BPWM_CH4 Trigger EADC Enable Bit
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>TRGSEL5</td><td><div style="word-wrap: break-word;"><b>BPWM_CH5 Trigger EADC Source Select
</b><br>
0000 = BPWM_CH4 zero point.
<br>
0001 = BPWM_CH4 period point.
<br>
0010 = BPWM_CH4 zero or period point.
<br>
0011 = BPWM_CH4 up-count CMPDAT point.
<br>
0100 = BPWM_CH4 down-count CMPDAT point.
<br>
0101 = Reserved.
<br>
0110 = Reserved.
<br>
0111 = Reserved.
<br>
1000 = BPWM_CH5 up-count CMPDAT point.
<br>
1001 = BPWM_CH5 down-count CMPDAT point.
<br>
Others reserved
<br>
</div></td></tr><tr><td>
[15]</td><td>TRGEN5</td><td><div style="word-wrap: break-word;"><b>BPWM_CH5 Trigger EADC Enable Bit
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::SSCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SSCTL
</font><br><p> <font size="2">
Offset: 0x110  BPWM Synchronous Start Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SSEN0</td><td><div style="word-wrap: break-word;"><b>BPWM Synchronous Start Function 0 Enable Bit
</b><br>
When synchronous start function is enabled, the BPWM_CH0 counter enable bit (CNTEN0) can be enabled by writing BPWM synchronous start trigger bit (CNTSEN).
<br>
0 = BPWM synchronous start function Disabled.
<br>
1 = BPWM synchronous start function Enabled.
<br>
</div></td></tr><tr><td>
[9:8]</td><td>SSRC</td><td><div style="word-wrap: break-word;"><b>BPWM Synchronous Start Source Select
</b><br>
00 = Synchronous start source come from PWM0.
<br>
01 = Synchronous start source come from PWM1.
<br>
10 = Synchronous start source come from BPWM0.
<br>
11 = Synchronous start source come from BPWM1.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::SSTRG

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SSTRG
</font><br><p> <font size="2">
Offset: 0x114  BPWM Synchronous Start Trigger Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CNTSEN</td><td><div style="word-wrap: break-word;"><b>BPWM Counter Synchronous Start Enable Bit(Write Only)
</b><br>
BPMW counter synchronous enable function is used to make PWM or BPWM channels start counting at the same time.
<br>
Writing this bit to 1 will also set the counter enable bit if correlated BPWM channel counter synchronous start function is enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::STATUS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STATUS
</font><br><p> <font size="2">
Offset: 0x120  BPWM Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CNTMAX0</td><td><div style="word-wrap: break-word;"><b>Time-base Counter 0 Equal to 0xFFFF Latched Status
</b><br>
0 = indicates the time-base counter never reached its maximum value 0xFFFF.
<br>
1 = indicates the time-base counter reached its maximum value, software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[16]</td><td>EADCTRG0</td><td><div style="word-wrap: break-word;"><b>EADC Start of Conversion Status
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Indicates no EADC start of conversion trigger event has occurred.
<br>
1 = Indicates an EADC start of conversion trigger event has occurred, software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[17]</td><td>EADCTRG1</td><td><div style="word-wrap: break-word;"><b>EADC Start of Conversion Status
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Indicates no EADC start of conversion trigger event has occurred.
<br>
1 = Indicates an EADC start of conversion trigger event has occurred, software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[18]</td><td>EADCTRG2</td><td><div style="word-wrap: break-word;"><b>EADC Start of Conversion Status
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Indicates no EADC start of conversion trigger event has occurred.
<br>
1 = Indicates an EADC start of conversion trigger event has occurred, software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[19]</td><td>EADCTRG3</td><td><div style="word-wrap: break-word;"><b>EADC Start of Conversion Status
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Indicates no EADC start of conversion trigger event has occurred.
<br>
1 = Indicates an EADC start of conversion trigger event has occurred, software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[20]</td><td>EADCTRG4</td><td><div style="word-wrap: break-word;"><b>EADC Start of Conversion Status
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Indicates no EADC start of conversion trigger event has occurred.
<br>
1 = Indicates an EADC start of conversion trigger event has occurred, software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[21]</td><td>EADCTRG5</td><td><div style="word-wrap: break-word;"><b>EADC Start of Conversion Status
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Indicates no EADC start of conversion trigger event has occurred.
<br>
1 = Indicates an EADC start of conversion trigger event has occurred, software can write 1 to clear this bit.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::CAPINEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAPINEN
</font><br><p> <font size="2">
Offset: 0x200  BPWM Capture Input Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CAPINEN0</td><td><div style="word-wrap: break-word;"><b>Capture Input Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = BPWM Channel capture input path Disabled
<br>
The input of BPWM channel capture function is always regarded as 0.
<br>
1 = BPWM Channel capture input path Enabled
<br>
The input of BPWM channel capture function comes from correlative multifunction pin.
<br>
</div></td></tr><tr><td>
[1]</td><td>CAPINEN1</td><td><div style="word-wrap: break-word;"><b>Capture Input Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = BPWM Channel capture input path Disabled
<br>
The input of BPWM channel capture function is always regarded as 0.
<br>
1 = BPWM Channel capture input path Enabled
<br>
The input of BPWM channel capture function comes from correlative multifunction pin.
<br>
</div></td></tr><tr><td>
[2]</td><td>CAPINEN2</td><td><div style="word-wrap: break-word;"><b>Capture Input Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = BPWM Channel capture input path Disabled
<br>
The input of BPWM channel capture function is always regarded as 0.
<br>
1 = BPWM Channel capture input path Enabled
<br>
The input of BPWM channel capture function comes from correlative multifunction pin.
<br>
</div></td></tr><tr><td>
[3]</td><td>CAPINEN3</td><td><div style="word-wrap: break-word;"><b>Capture Input Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = BPWM Channel capture input path Disabled
<br>
The input of BPWM channel capture function is always regarded as 0.
<br>
1 = BPWM Channel capture input path Enabled
<br>
The input of BPWM channel capture function comes from correlative multifunction pin.
<br>
</div></td></tr><tr><td>
[4]</td><td>CAPINEN4</td><td><div style="word-wrap: break-word;"><b>Capture Input Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = BPWM Channel capture input path Disabled
<br>
The input of BPWM channel capture function is always regarded as 0.
<br>
1 = BPWM Channel capture input path Enabled
<br>
The input of BPWM channel capture function comes from correlative multifunction pin.
<br>
</div></td></tr><tr><td>
[5]</td><td>CAPINEN5</td><td><div style="word-wrap: break-word;"><b>Capture Input Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = BPWM Channel capture input path Disabled
<br>
The input of BPWM channel capture function is always regarded as 0.
<br>
1 = BPWM Channel capture input path Enabled
<br>
The input of BPWM channel capture function comes from correlative multifunction pin.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::CAPCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAPCTL
</font><br><p> <font size="2">
Offset: 0x204  BPWM Capture Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CAPEN0</td><td><div style="word-wrap: break-word;"><b>Capture Function Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Capture function Disabled. RCAPDAT/FCAPDAT register will not be updated.
<br>
1 = Capture function Enabled
<br>
Capture latched the BPWM counter value when detected rising or falling edge of input signal and saved to RCAPDAT (Rising latch) and FCAPDAT (Falling latch).
<br>
</div></td></tr><tr><td>
[1]</td><td>CAPEN1</td><td><div style="word-wrap: break-word;"><b>Capture Function Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Capture function Disabled. RCAPDAT/FCAPDAT register will not be updated.
<br>
1 = Capture function Enabled
<br>
Capture latched the BPWM counter value when detected rising or falling edge of input signal and saved to RCAPDAT (Rising latch) and FCAPDAT (Falling latch).
<br>
</div></td></tr><tr><td>
[2]</td><td>CAPEN2</td><td><div style="word-wrap: break-word;"><b>Capture Function Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Capture function Disabled. RCAPDAT/FCAPDAT register will not be updated.
<br>
1 = Capture function Enabled
<br>
Capture latched the BPWM counter value when detected rising or falling edge of input signal and saved to RCAPDAT (Rising latch) and FCAPDAT (Falling latch).
<br>
</div></td></tr><tr><td>
[3]</td><td>CAPEN3</td><td><div style="word-wrap: break-word;"><b>Capture Function Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Capture function Disabled. RCAPDAT/FCAPDAT register will not be updated.
<br>
1 = Capture function Enabled
<br>
Capture latched the BPWM counter value when detected rising or falling edge of input signal and saved to RCAPDAT (Rising latch) and FCAPDAT (Falling latch).
<br>
</div></td></tr><tr><td>
[4]</td><td>CAPEN4</td><td><div style="word-wrap: break-word;"><b>Capture Function Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Capture function Disabled. RCAPDAT/FCAPDAT register will not be updated.
<br>
1 = Capture function Enabled
<br>
Capture latched the BPWM counter value when detected rising or falling edge of input signal and saved to RCAPDAT (Rising latch) and FCAPDAT (Falling latch).
<br>
</div></td></tr><tr><td>
[5]</td><td>CAPEN5</td><td><div style="word-wrap: break-word;"><b>Capture Function Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Capture function Disabled. RCAPDAT/FCAPDAT register will not be updated.
<br>
1 = Capture function Enabled
<br>
Capture latched the BPWM counter value when detected rising or falling edge of input signal and saved to RCAPDAT (Rising latch) and FCAPDAT (Falling latch).
<br>
</div></td></tr><tr><td>
[8]</td><td>CAPINV0</td><td><div style="word-wrap: break-word;"><b>Capture Inverter Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Capture source inverter Disabled.
<br>
1 = Capture source inverter Enabled. Reverse the input signal from GPIO.
<br>
</div></td></tr><tr><td>
[9]</td><td>CAPINV1</td><td><div style="word-wrap: break-word;"><b>Capture Inverter Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Capture source inverter Disabled.
<br>
1 = Capture source inverter Enabled. Reverse the input signal from GPIO.
<br>
</div></td></tr><tr><td>
[10]</td><td>CAPINV2</td><td><div style="word-wrap: break-word;"><b>Capture Inverter Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Capture source inverter Disabled.
<br>
1 = Capture source inverter Enabled. Reverse the input signal from GPIO.
<br>
</div></td></tr><tr><td>
[11]</td><td>CAPINV3</td><td><div style="word-wrap: break-word;"><b>Capture Inverter Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Capture source inverter Disabled.
<br>
1 = Capture source inverter Enabled. Reverse the input signal from GPIO.
<br>
</div></td></tr><tr><td>
[12]</td><td>CAPINV4</td><td><div style="word-wrap: break-word;"><b>Capture Inverter Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Capture source inverter Disabled.
<br>
1 = Capture source inverter Enabled. Reverse the input signal from GPIO.
<br>
</div></td></tr><tr><td>
[13]</td><td>CAPINV5</td><td><div style="word-wrap: break-word;"><b>Capture Inverter Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Capture source inverter Disabled.
<br>
1 = Capture source inverter Enabled. Reverse the input signal from GPIO.
<br>
</div></td></tr><tr><td>
[16]</td><td>RCRLDEN0</td><td><div style="word-wrap: break-word;"><b>Rising Capture Reload Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Rising capture reload counter Disabled.
<br>
1 = Rising capture reload counter Enabled.
<br>
</div></td></tr><tr><td>
[17]</td><td>RCRLDEN1</td><td><div style="word-wrap: break-word;"><b>Rising Capture Reload Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Rising capture reload counter Disabled.
<br>
1 = Rising capture reload counter Enabled.
<br>
</div></td></tr><tr><td>
[18]</td><td>RCRLDEN2</td><td><div style="word-wrap: break-word;"><b>Rising Capture Reload Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Rising capture reload counter Disabled.
<br>
1 = Rising capture reload counter Enabled.
<br>
</div></td></tr><tr><td>
[19]</td><td>RCRLDEN3</td><td><div style="word-wrap: break-word;"><b>Rising Capture Reload Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Rising capture reload counter Disabled.
<br>
1 = Rising capture reload counter Enabled.
<br>
</div></td></tr><tr><td>
[20]</td><td>RCRLDEN4</td><td><div style="word-wrap: break-word;"><b>Rising Capture Reload Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Rising capture reload counter Disabled.
<br>
1 = Rising capture reload counter Enabled.
<br>
</div></td></tr><tr><td>
[21]</td><td>RCRLDEN5</td><td><div style="word-wrap: break-word;"><b>Rising Capture Reload Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Rising capture reload counter Disabled.
<br>
1 = Rising capture reload counter Enabled.
<br>
</div></td></tr><tr><td>
[24]</td><td>FCRLDEN0</td><td><div style="word-wrap: break-word;"><b>Falling Capture Reload Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Falling capture reload counter Disabled.
<br>
1 = Falling capture reload counter Enabled.
<br>
</div></td></tr><tr><td>
[25]</td><td>FCRLDEN1</td><td><div style="word-wrap: break-word;"><b>Falling Capture Reload Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Falling capture reload counter Disabled.
<br>
1 = Falling capture reload counter Enabled.
<br>
</div></td></tr><tr><td>
[26]</td><td>FCRLDEN2</td><td><div style="word-wrap: break-word;"><b>Falling Capture Reload Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Falling capture reload counter Disabled.
<br>
1 = Falling capture reload counter Enabled.
<br>
</div></td></tr><tr><td>
[27]</td><td>FCRLDEN3</td><td><div style="word-wrap: break-word;"><b>Falling Capture Reload Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Falling capture reload counter Disabled.
<br>
1 = Falling capture reload counter Enabled.
<br>
</div></td></tr><tr><td>
[28]</td><td>FCRLDEN4</td><td><div style="word-wrap: break-word;"><b>Falling Capture Reload Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Falling capture reload counter Disabled.
<br>
1 = Falling capture reload counter Enabled.
<br>
</div></td></tr><tr><td>
[29]</td><td>FCRLDEN5</td><td><div style="word-wrap: break-word;"><b>Falling Capture Reload Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Falling capture reload counter Disabled.
<br>
1 = Falling capture reload counter Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::CAPSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAPSTS
</font><br><p> <font size="2">
Offset: 0x208  BPWM Capture Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CRIFOV0</td><td><div style="word-wrap: break-word;"><b>Capture Rising Interrupt Flag Overrun Status (Read Only)
</b><br>
This flag indicates if rising latch happened when the corresponding CAPRIF is 1
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
Note: This bit will be cleared automatically when user clear corresponding CAPRIF.
<br>
</div></td></tr><tr><td>
[1]</td><td>CRIFOV1</td><td><div style="word-wrap: break-word;"><b>Capture Rising Interrupt Flag Overrun Status (Read Only)
</b><br>
This flag indicates if rising latch happened when the corresponding CAPRIF is 1
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
Note: This bit will be cleared automatically when user clear corresponding CAPRIF.
<br>
</div></td></tr><tr><td>
[2]</td><td>CRIFOV2</td><td><div style="word-wrap: break-word;"><b>Capture Rising Interrupt Flag Overrun Status (Read Only)
</b><br>
This flag indicates if rising latch happened when the corresponding CAPRIF is 1
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
Note: This bit will be cleared automatically when user clear corresponding CAPRIF.
<br>
</div></td></tr><tr><td>
[3]</td><td>CRIFOV3</td><td><div style="word-wrap: break-word;"><b>Capture Rising Interrupt Flag Overrun Status (Read Only)
</b><br>
This flag indicates if rising latch happened when the corresponding CAPRIF is 1
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
Note: This bit will be cleared automatically when user clear corresponding CAPRIF.
<br>
</div></td></tr><tr><td>
[4]</td><td>CRIFOV4</td><td><div style="word-wrap: break-word;"><b>Capture Rising Interrupt Flag Overrun Status (Read Only)
</b><br>
This flag indicates if rising latch happened when the corresponding CAPRIF is 1
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
Note: This bit will be cleared automatically when user clear corresponding CAPRIF.
<br>
</div></td></tr><tr><td>
[5]</td><td>CRIFOV5</td><td><div style="word-wrap: break-word;"><b>Capture Rising Interrupt Flag Overrun Status (Read Only)
</b><br>
This flag indicates if rising latch happened when the corresponding CAPRIF is 1
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
Note: This bit will be cleared automatically when user clear corresponding CAPRIF.
<br>
</div></td></tr><tr><td>
[8]</td><td>CFIFOV0</td><td><div style="word-wrap: break-word;"><b>Capture Falling Interrupt Flag Overrun Status (Read Only)
</b><br>
This flag indicates if falling latch happened when the corresponding CAPFIF is 1
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
Note: This bit will be cleared automatically when user clear corresponding CAPFIF.
<br>
</div></td></tr><tr><td>
[9]</td><td>CFIFOV1</td><td><div style="word-wrap: break-word;"><b>Capture Falling Interrupt Flag Overrun Status (Read Only)
</b><br>
This flag indicates if falling latch happened when the corresponding CAPFIF is 1
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
Note: This bit will be cleared automatically when user clear corresponding CAPFIF.
<br>
</div></td></tr><tr><td>
[10]</td><td>CFIFOV2</td><td><div style="word-wrap: break-word;"><b>Capture Falling Interrupt Flag Overrun Status (Read Only)
</b><br>
This flag indicates if falling latch happened when the corresponding CAPFIF is 1
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
Note: This bit will be cleared automatically when user clear corresponding CAPFIF.
<br>
</div></td></tr><tr><td>
[11]</td><td>CFIFOV3</td><td><div style="word-wrap: break-word;"><b>Capture Falling Interrupt Flag Overrun Status (Read Only)
</b><br>
This flag indicates if falling latch happened when the corresponding CAPFIF is 1
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
Note: This bit will be cleared automatically when user clear corresponding CAPFIF.
<br>
</div></td></tr><tr><td>
[12]</td><td>CFIFOV4</td><td><div style="word-wrap: break-word;"><b>Capture Falling Interrupt Flag Overrun Status (Read Only)
</b><br>
This flag indicates if falling latch happened when the corresponding CAPFIF is 1
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
Note: This bit will be cleared automatically when user clear corresponding CAPFIF.
<br>
</div></td></tr><tr><td>
[13]</td><td>CFIFOV5</td><td><div style="word-wrap: break-word;"><b>Capture Falling Interrupt Flag Overrun Status (Read Only)
</b><br>
This flag indicates if falling latch happened when the corresponding CAPFIF is 1
<br>
Each bit n controls the corresponding BPWM channel n.
<br>
Note: This bit will be cleared automatically when user clear corresponding CAPFIF.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::CAPIEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAPIEN
</font><br><p> <font size="2">
Offset: 0x250  BPWM Capture Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[5:0]</td><td>CAPRIENn</td><td><div style="word-wrap: break-word;"><b>BPWM Capture Rising Latch Interrupt Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Capture rising edge latch interrupt Disabled.
<br>
1 = Capture rising edge latch interrupt Enabled.
<br>
</div></td></tr><tr><td>
[13:8]</td><td>CAPFIENn</td><td><div style="word-wrap: break-word;"><b>BPWM Capture Falling Latch Interrupt Enable Bits
</b><br>
Each bit n controls the corresponding BPWM channel n.
<br>
0 = Capture falling edge latch interrupt Disabled.
<br>
1 = Capture falling edge latch interrupt Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::CAPIF

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAPIF
</font><br><p> <font size="2">
Offset: 0x254  BPWM Capture Interrupt Flag Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CAPRIF0</td><td><div style="word-wrap: break-word;"><b>BPWM Capture Rising Latch Interrupt Flag
</b><br>
This bit is writing 1 to clear. Each bit n controls the corresponding BPWM channel n.
<br>
0 = No capture rising latch condition happened.
<br>
1 = Capture rising latch condition happened, this flag will be set to high.
<br>
</div></td></tr><tr><td>
[1]</td><td>CAPRIF1</td><td><div style="word-wrap: break-word;"><b>BPWM Capture Rising Latch Interrupt Flag
</b><br>
This bit is writing 1 to clear. Each bit n controls the corresponding BPWM channel n.
<br>
0 = No capture rising latch condition happened.
<br>
1 = Capture rising latch condition happened, this flag will be set to high.
<br>
</div></td></tr><tr><td>
[2]</td><td>CAPRIF2</td><td><div style="word-wrap: break-word;"><b>BPWM Capture Rising Latch Interrupt Flag
</b><br>
This bit is writing 1 to clear. Each bit n controls the corresponding BPWM channel n.
<br>
0 = No capture rising latch condition happened.
<br>
1 = Capture rising latch condition happened, this flag will be set to high.
<br>
</div></td></tr><tr><td>
[3]</td><td>CAPRIF3</td><td><div style="word-wrap: break-word;"><b>BPWM Capture Rising Latch Interrupt Flag
</b><br>
This bit is writing 1 to clear. Each bit n controls the corresponding BPWM channel n.
<br>
0 = No capture rising latch condition happened.
<br>
1 = Capture rising latch condition happened, this flag will be set to high.
<br>
</div></td></tr><tr><td>
[4]</td><td>CAPRIF4</td><td><div style="word-wrap: break-word;"><b>BPWM Capture Rising Latch Interrupt Flag
</b><br>
This bit is writing 1 to clear. Each bit n controls the corresponding BPWM channel n.
<br>
0 = No capture rising latch condition happened.
<br>
1 = Capture rising latch condition happened, this flag will be set to high.
<br>
</div></td></tr><tr><td>
[5]</td><td>CAPRIF5</td><td><div style="word-wrap: break-word;"><b>BPWM Capture Rising Latch Interrupt Flag
</b><br>
This bit is writing 1 to clear. Each bit n controls the corresponding BPWM channel n.
<br>
0 = No capture rising latch condition happened.
<br>
1 = Capture rising latch condition happened, this flag will be set to high.
<br>
</div></td></tr><tr><td>
[8]</td><td>CAPFIF0</td><td><div style="word-wrap: break-word;"><b>BPWM Capture Falling Latch Interrupt Flag
</b><br>
This bit is writing 1 to clear. Each bit n controls the corresponding BPWM channel n.
<br>
0 = No capture falling latch condition happened.
<br>
1 = Capture falling latch condition happened, this flag will be set to high.
<br>
</div></td></tr><tr><td>
[9]</td><td>CAPFIF1</td><td><div style="word-wrap: break-word;"><b>BPWM Capture Falling Latch Interrupt Flag
</b><br>
This bit is writing 1 to clear. Each bit n controls the corresponding BPWM channel n.
<br>
0 = No capture falling latch condition happened.
<br>
1 = Capture falling latch condition happened, this flag will be set to high.
<br>
</div></td></tr><tr><td>
[10]</td><td>CAPFIF2</td><td><div style="word-wrap: break-word;"><b>BPWM Capture Falling Latch Interrupt Flag
</b><br>
This bit is writing 1 to clear. Each bit n controls the corresponding BPWM channel n.
<br>
0 = No capture falling latch condition happened.
<br>
1 = Capture falling latch condition happened, this flag will be set to high.
<br>
</div></td></tr><tr><td>
[11]</td><td>CAPFIF3</td><td><div style="word-wrap: break-word;"><b>BPWM Capture Falling Latch Interrupt Flag
</b><br>
This bit is writing 1 to clear. Each bit n controls the corresponding BPWM channel n.
<br>
0 = No capture falling latch condition happened.
<br>
1 = Capture falling latch condition happened, this flag will be set to high.
<br>
</div></td></tr><tr><td>
[12]</td><td>CAPFIF4</td><td><div style="word-wrap: break-word;"><b>BPWM Capture Falling Latch Interrupt Flag
</b><br>
This bit is writing 1 to clear. Each bit n controls the corresponding BPWM channel n.
<br>
0 = No capture falling latch condition happened.
<br>
1 = Capture falling latch condition happened, this flag will be set to high.
<br>
</div></td></tr><tr><td>
[13]</td><td>CAPFIF5</td><td><div style="word-wrap: break-word;"><b>BPWM Capture Falling Latch Interrupt Flag
</b><br>
This bit is writing 1 to clear. Each bit n controls the corresponding BPWM channel n.
<br>
0 = No capture falling latch condition happened.
<br>
1 = Capture falling latch condition happened, this flag will be set to high.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::PBUF

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PBUF
</font><br><p> <font size="2">
Offset: 0x304  BPWM PERIOD Buffer
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>PBUF</td><td><div style="word-wrap: break-word;"><b>BPWM Period Buffer (Read Only)
</b><br>
Used as PERIOD active register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var BPWM_T::CMPBUF[6]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CMPBUF[6]
</font><br><p> <font size="2">
Offset: 0x31C  BPWM CMPDAT 0~5 Buffer
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>CMPBUF</td><td><div style="word-wrap: break-word;"><b>BPWM Comparator Buffer (Read Only)
</b><br>
Used as CMP active register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CTL0;                  /*!< [0x0000] BPWM Control Register 0                                          */
    __IO uint32_t CTL1;                  /*!< [0x0004] BPWM Control Register 1                                          */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[2];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t CLKSRC;                /*!< [0x0010] BPWM Clock Source Register                                       */
    __IO uint32_t CLKPSC;                /*!< [0x0014] BPWM Clock Prescale Register                                     */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[2];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t CNTEN;                 /*!< [0x0020] BPWM Counter Enable Register                                     */
    __IO uint32_t CNTCLR;                /*!< [0x0024] BPWM Clear Counter Register                                      */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE2[2];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t PERIOD;                /*!< [0x0030] BPWM Period Register                                             */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE3[7];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t CMPDAT[6];             /*!< [0x0050] BPWM Comparator Register 0~5                                     */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE4[10];
    /// @endcond //HIDDEN_SYMBOLS
    __I  uint32_t CNT;                   /*!< [0x0090] BPWM Counter Register                                            */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE5[7];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t WGCTL0;                /*!< [0x00b0] BPWM Generation Register 0                                       */
    __IO uint32_t WGCTL1;                /*!< [0x00b4] BPWM Generation Register 1                                       */
    __IO uint32_t MSKEN;                 /*!< [0x00b8] BPWM Mask Enable Register                                        */
    __IO uint32_t MSK;                   /*!< [0x00bc] BPWM Mask Data Register                                          */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE6[5];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t POLCTL;                /*!< [0x00d4] BPWM Pin Polar Inverse Register                                  */
    __IO uint32_t POEN;                  /*!< [0x00d8] BPWM Output Enable Register                                      */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE7[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t INTEN;                 /*!< [0x00e0] BPWM Interrupt Enable Register                                   */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE8[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t INTSTS;                /*!< [0x00e8] BPWM Interrupt Flag Register                                     */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE9[3];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t EADCTS0;               /*!< [0x00f8] BPWM Trigger EADC Source Select Register 0                       */
    __IO uint32_t EADCTS1;               /*!< [0x00fc] BPWM Trigger EADC Source Select Register 1                       */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE10[4];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t SSCTL;                 /*!< [0x0110] BPWM Synchronous Start Control Register                          */
    __O  uint32_t SSTRG;                 /*!< [0x0114] BPWM Synchronous Start Trigger Register                          */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE11[2];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t STATUS;                /*!< [0x0120] BPWM Status Register                                             */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE12[55];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t CAPINEN;               /*!< [0x0200] BPWM Capture Input Enable Register                               */
    __IO uint32_t CAPCTL;                /*!< [0x0204] BPWM Capture Control Register                                    */
    __I  uint32_t CAPSTS;                /*!< [0x0208] BPWM Capture Status Register                                     */
    BCAPDAT_T CAPDAT[6];                  /*!< [0x020C] BPWM Rising and Falling Capture Data Register 0~5                */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE13[5];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t CAPIEN;                /*!< [0x0250] BPWM Capture Interrupt Enable Register                           */
    __IO uint32_t CAPIF;                 /*!< [0x0254] BPWM Capture Interrupt Flag Register                             */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE14[43];
    /// @endcond //HIDDEN_SYMBOLS
    __I  uint32_t PBUF;                  /*!< [0x0304] BPWM PERIOD Buffer                                               */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE15[5];
    /// @endcond //HIDDEN_SYMBOLS
    __I  uint32_t CMPBUF[6];             /*!< [0x031c] BPWM CMPDAT 0~5 Buffer                                           */

} BPWM_T;

/**
    @addtogroup BPWM_CONST BPWM Bit Field Definition
    Constant Definitions for BPWM Controller
@{ */

#define BPWM_CTL0_CTRLD0_Pos             (0)                                               /*!< BPWM_T::CTL0: CTRLD0 Position          */
#define BPWM_CTL0_CTRLD0_Msk             (0x1ul << BPWM_CTL0_CTRLD0_Pos)                   /*!< BPWM_T::CTL0: CTRLD0 Mask              */

#define BPWM_CTL0_CTRLD1_Pos             (1)                                               /*!< BPWM_T::CTL0: CTRLD1 Position          */
#define BPWM_CTL0_CTRLD1_Msk             (0x1ul << BPWM_CTL0_CTRLD1_Pos)                   /*!< BPWM_T::CTL0: CTRLD1 Mask              */

#define BPWM_CTL0_CTRLD2_Pos             (2)                                               /*!< BPWM_T::CTL0: CTRLD2 Position          */
#define BPWM_CTL0_CTRLD2_Msk             (0x1ul << BPWM_CTL0_CTRLD2_Pos)                   /*!< BPWM_T::CTL0: CTRLD2 Mask              */

#define BPWM_CTL0_CTRLD3_Pos             (3)                                               /*!< BPWM_T::CTL0: CTRLD3 Position          */
#define BPWM_CTL0_CTRLD3_Msk             (0x1ul << BPWM_CTL0_CTRLD3_Pos)                   /*!< BPWM_T::CTL0: CTRLD3 Mask              */

#define BPWM_CTL0_CTRLD4_Pos             (4)                                               /*!< BPWM_T::CTL0: CTRLD4 Position          */
#define BPWM_CTL0_CTRLD4_Msk             (0x1ul << BPWM_CTL0_CTRLD4_Pos)                   /*!< BPWM_T::CTL0: CTRLD4 Mask              */

#define BPWM_CTL0_CTRLD5_Pos             (5)                                               /*!< BPWM_T::CTL0: CTRLD5 Position          */
#define BPWM_CTL0_CTRLD5_Msk             (0x1ul << BPWM_CTL0_CTRLD5_Pos)                   /*!< BPWM_T::CTL0: CTRLD5 Mask              */

#define BPWM_CTL0_IMMLDEN0_Pos           (16)                                              /*!< BPWM_T::CTL0: IMMLDEN0 Position        */
#define BPWM_CTL0_IMMLDEN0_Msk           (0x1ul << BPWM_CTL0_IMMLDEN0_Pos)                 /*!< BPWM_T::CTL0: IMMLDEN0 Mask            */

#define BPWM_CTL0_IMMLDEN1_Pos           (17)                                              /*!< BPWM_T::CTL0: IMMLDEN1 Position        */
#define BPWM_CTL0_IMMLDEN1_Msk           (0x1ul << BPWM_CTL0_IMMLDEN1_Pos)                 /*!< BPWM_T::CTL0: IMMLDEN1 Mask            */

#define BPWM_CTL0_IMMLDEN2_Pos           (18)                                              /*!< BPWM_T::CTL0: IMMLDEN2 Position        */
#define BPWM_CTL0_IMMLDEN2_Msk           (0x1ul << BPWM_CTL0_IMMLDEN2_Pos)                 /*!< BPWM_T::CTL0: IMMLDEN2 Mask            */

#define BPWM_CTL0_IMMLDEN3_Pos           (19)                                              /*!< BPWM_T::CTL0: IMMLDEN3 Position        */
#define BPWM_CTL0_IMMLDEN3_Msk           (0x1ul << BPWM_CTL0_IMMLDEN3_Pos)                 /*!< BPWM_T::CTL0: IMMLDEN3 Mask            */

#define BPWM_CTL0_IMMLDEN4_Pos           (20)                                              /*!< BPWM_T::CTL0: IMMLDEN4 Position        */
#define BPWM_CTL0_IMMLDEN4_Msk           (0x1ul << BPWM_CTL0_IMMLDEN4_Pos)                 /*!< BPWM_T::CTL0: IMMLDEN4 Mask            */

#define BPWM_CTL0_IMMLDEN5_Pos           (21)                                              /*!< BPWM_T::CTL0: IMMLDEN5 Position        */
#define BPWM_CTL0_IMMLDEN5_Msk           (0x1ul << BPWM_CTL0_IMMLDEN5_Pos)                 /*!< BPWM_T::CTL0: IMMLDEN5 Mask            */

#define BPWM_CTL0_DBGHALT_Pos            (30)                                              /*!< BPWM_T::CTL0: DBGHALT Position         */
#define BPWM_CTL0_DBGHALT_Msk            (0x1ul << BPWM_CTL0_DBGHALT_Pos)                  /*!< BPWM_T::CTL0: DBGHALT Mask             */

#define BPWM_CTL0_DBGTRIOFF_Pos          (31)                                              /*!< BPWM_T::CTL0: DBGTRIOFF Position       */
#define BPWM_CTL0_DBGTRIOFF_Msk          (0x1ul << BPWM_CTL0_DBGTRIOFF_Pos)                /*!< BPWM_T::CTL0: DBGTRIOFF Mask           */

#define BPWM_CTL1_CNTTYPE0_Pos           (0)                                               /*!< BPWM_T::CTL1: CNTTYPE0 Position        */
#define BPWM_CTL1_CNTTYPE0_Msk           (0x3ul << BPWM_CTL1_CNTTYPE0_Pos)                 /*!< BPWM_T::CTL1: CNTTYPE0 Mask            */

#define BPWM_CLKSRC_ECLKSRC0_Pos         (0)                                               /*!< BPWM_T::CLKSRC: ECLKSRC0 Position      */
#define BPWM_CLKSRC_ECLKSRC0_Msk         (0x7ul << BPWM_CLKSRC_ECLKSRC0_Pos)               /*!< BPWM_T::CLKSRC: ECLKSRC0 Mask          */

#define BPWM_CLKPSC_CLKPSC_Pos           (0)                                               /*!< BPWM_T::CLKPSC: CLKPSC Position        */
#define BPWM_CLKPSC_CLKPSC_Msk           (0xffful << BPWM_CLKPSC_CLKPSC_Pos)               /*!< BPWM_T::CLKPSC: CLKPSC Mask            */

#define BPWM_CNTEN_CNTEN0_Pos            (0)                                               /*!< BPWM_T::CNTEN: CNTEN0 Position         */
#define BPWM_CNTEN_CNTEN0_Msk            (0x1ul << BPWM_CNTEN_CNTEN0_Pos)                  /*!< BPWM_T::CNTEN: CNTEN0 Mask             */

#define BPWM_CNTCLR_CNTCLR0_Pos          (0)                                               /*!< BPWM_T::CNTCLR: CNTCLR0 Position       */
#define BPWM_CNTCLR_CNTCLR0_Msk          (0x1ul << BPWM_CNTCLR_CNTCLR0_Pos)                /*!< BPWM_T::CNTCLR: CNTCLR0 Mask           */

#define BPWM_PERIOD_PERIOD_Pos           (0)                                               /*!< BPWM_T::PERIOD: PERIOD Position        */
#define BPWM_PERIOD_PERIOD_Msk           (0xfffful << BPWM_PERIOD_PERIOD_Pos)              /*!< BPWM_T::PERIOD: PERIOD Mask            */

#define BPWM_CMPDAT0_CMPDAT_Pos          (0)                                               /*!< BPWM_T::CMPDAT0: CMPDAT Position       */
#define BPWM_CMPDAT0_CMPDAT_Msk          (0xfffful << BPWM_CMPDAT0_CMPDAT_Pos)             /*!< BPWM_T::CMPDAT0: CMPDAT Mask           */

#define BPWM_CMPDAT1_CMPDAT_Pos          (0)                                               /*!< BPWM_T::CMPDAT1: CMPDAT Position       */
#define BPWM_CMPDAT1_CMPDAT_Msk          (0xfffful << BPWM_CMPDAT1_CMPDAT_Pos)             /*!< BPWM_T::CMPDAT1: CMPDAT Mask           */

#define BPWM_CMPDAT2_CMPDAT_Pos          (0)                                               /*!< BPWM_T::CMPDAT2: CMPDAT Position       */
#define BPWM_CMPDAT2_CMPDAT_Msk          (0xfffful << BPWM_CMPDAT2_CMPDAT_Pos)             /*!< BPWM_T::CMPDAT2: CMPDAT Mask           */

#define BPWM_CMPDAT3_CMPDAT_Pos          (0)                                               /*!< BPWM_T::CMPDAT3: CMPDAT Position       */
#define BPWM_CMPDAT3_CMPDAT_Msk          (0xfffful << BPWM_CMPDAT3_CMPDAT_Pos)             /*!< BPWM_T::CMPDAT3: CMPDAT Mask           */

#define BPWM_CMPDAT4_CMPDAT_Pos          (0)                                               /*!< BPWM_T::CMPDAT4: CMPDAT Position       */
#define BPWM_CMPDAT4_CMPDAT_Msk          (0xfffful << BPWM_CMPDAT4_CMPDAT_Pos)             /*!< BPWM_T::CMPDAT4: CMPDAT Mask           */

#define BPWM_CMPDAT5_CMPDAT_Pos          (0)                                               /*!< BPWM_T::CMPDAT5: CMPDAT Position       */
#define BPWM_CMPDAT5_CMPDAT_Msk          (0xfffful << BPWM_CMPDAT5_CMPDAT_Pos)             /*!< BPWM_T::CMPDAT5: CMPDAT Mask           */

#define BPWM_CNT_CNT_Pos                 (0)                                               /*!< BPWM_T::CNT: CNT Position              */
#define BPWM_CNT_CNT_Msk                 (0xfffful << BPWM_CNT_CNT_Pos)                    /*!< BPWM_T::CNT: CNT Mask                  */

#define BPWM_CNT_DIRF_Pos                (16)                                              /*!< BPWM_T::CNT: DIRF Position             */
#define BPWM_CNT_DIRF_Msk                (0x1ul << BPWM_CNT_DIRF_Pos)                      /*!< BPWM_T::CNT: DIRF Mask                 */

#define BPWM_WGCTL0_ZPCTL0_Pos           (0)                                               /*!< BPWM_T::WGCTL0: ZPCTL0 Position        */
#define BPWM_WGCTL0_ZPCTL0_Msk           (0x3ul << BPWM_WGCTL0_ZPCTL0_Pos)                 /*!< BPWM_T::WGCTL0: ZPCTL0 Mask            */

#define BPWM_WGCTL0_ZPCTL1_Pos           (2)                                               /*!< BPWM_T::WGCTL0: ZPCTL1 Position        */
#define BPWM_WGCTL0_ZPCTL1_Msk           (0x3ul << BPWM_WGCTL0_ZPCTL1_Pos)                 /*!< BPWM_T::WGCTL0: ZPCTL1 Mask            */

#define BPWM_WGCTL0_ZPCTL2_Pos           (4)                                               /*!< BPWM_T::WGCTL0: ZPCTL2 Position        */
#define BPWM_WGCTL0_ZPCTL2_Msk           (0x3ul << BPWM_WGCTL0_ZPCTL2_Pos)                 /*!< BPWM_T::WGCTL0: ZPCTL2 Mask            */

#define BPWM_WGCTL0_ZPCTL3_Pos           (6)                                               /*!< BPWM_T::WGCTL0: ZPCTL3 Position        */
#define BPWM_WGCTL0_ZPCTL3_Msk           (0x3ul << BPWM_WGCTL0_ZPCTL3_Pos)                 /*!< BPWM_T::WGCTL0: ZPCTL3 Mask            */

#define BPWM_WGCTL0_ZPCTL4_Pos           (8)                                               /*!< BPWM_T::WGCTL0: ZPCTL4 Position        */
#define BPWM_WGCTL0_ZPCTL4_Msk           (0x3ul << BPWM_WGCTL0_ZPCTL4_Pos)                 /*!< BPWM_T::WGCTL0: ZPCTL4 Mask            */

#define BPWM_WGCTL0_ZPCTL5_Pos           (10)                                              /*!< BPWM_T::WGCTL0: ZPCTL5 Position        */
#define BPWM_WGCTL0_ZPCTL5_Msk           (0x3ul << BPWM_WGCTL0_ZPCTL5_Pos)                 /*!< BPWM_T::WGCTL0: ZPCTL5 Mask            */

#define BPWM_WGCTL0_ZPCTLn_Pos           (0)                                               /*!< BPWM_T::WGCTL0: ZPCTLn Position        */
#define BPWM_WGCTL0_ZPCTLn_Msk           (0xffful << BPWM_WGCTL0_ZPCTLn_Pos)               /*!< BPWM_T::WGCTL0: ZPCTLn Mask            */

#define BPWM_WGCTL0_PRDPCTL0_Pos         (16)                                              /*!< BPWM_T::WGCTL0: PRDPCTL0 Position      */
#define BPWM_WGCTL0_PRDPCTL0_Msk         (0x3ul << BPWM_WGCTL0_PRDPCTL0_Pos)               /*!< BPWM_T::WGCTL0: PRDPCTL0 Mask          */

#define BPWM_WGCTL0_PRDPCTL1_Pos         (18)                                              /*!< BPWM_T::WGCTL0: PRDPCTL1 Position      */
#define BPWM_WGCTL0_PRDPCTL1_Msk         (0x3ul << BPWM_WGCTL0_PRDPCTL1_Pos)               /*!< BPWM_T::WGCTL0: PRDPCTL1 Mask          */

#define BPWM_WGCTL0_PRDPCTL2_Pos         (20)                                              /*!< BPWM_T::WGCTL0: PRDPCTL2 Position      */
#define BPWM_WGCTL0_PRDPCTL2_Msk         (0x3ul << BPWM_WGCTL0_PRDPCTL2_Pos)               /*!< BPWM_T::WGCTL0: PRDPCTL2 Mask          */

#define BPWM_WGCTL0_PRDPCTL3_Pos         (22)                                              /*!< BPWM_T::WGCTL0: PRDPCTL3 Position      */
#define BPWM_WGCTL0_PRDPCTL3_Msk         (0x3ul << BPWM_WGCTL0_PRDPCTL3_Pos)               /*!< BPWM_T::WGCTL0: PRDPCTL3 Mask          */

#define BPWM_WGCTL0_PRDPCTL4_Pos         (24)                                              /*!< BPWM_T::WGCTL0: PRDPCTL4 Position      */
#define BPWM_WGCTL0_PRDPCTL4_Msk         (0x3ul << BPWM_WGCTL0_PRDPCTL4_Pos)               /*!< BPWM_T::WGCTL0: PRDPCTL4 Mask          */

#define BPWM_WGCTL0_PRDPCTL5_Pos         (26)                                              /*!< BPWM_T::WGCTL0: PRDPCTL5 Position      */
#define BPWM_WGCTL0_PRDPCTL5_Msk         (0x3ul << BPWM_WGCTL0_PRDPCTL5_Pos)               /*!< BPWM_T::WGCTL0: PRDPCTL5 Mask          */

#define BPWM_WGCTL0_PRDPCTLn_Pos         (16)                                              /*!< BPWM_T::WGCTL0: PRDPCTLn Position      */
#define BPWM_WGCTL0_PRDPCTLn_Msk         (0xffful << BPWM_WGCTL0_PRDPCTLn_Pos)             /*!< BPWM_T::WGCTL0: PRDPCTLn Mask          */

#define BPWM_WGCTL1_CMPUCTL0_Pos         (0)                                               /*!< BPWM_T::WGCTL1: CMPUCTL0 Position      */
#define BPWM_WGCTL1_CMPUCTL0_Msk         (0x3ul << BPWM_WGCTL1_CMPUCTL0_Pos)               /*!< BPWM_T::WGCTL1: CMPUCTL0 Mask          */

#define BPWM_WGCTL1_CMPUCTL1_Pos         (2)                                               /*!< BPWM_T::WGCTL1: CMPUCTL1 Position      */
#define BPWM_WGCTL1_CMPUCTL1_Msk         (0x3ul << BPWM_WGCTL1_CMPUCTL1_Pos)               /*!< BPWM_T::WGCTL1: CMPUCTL1 Mask          */

#define BPWM_WGCTL1_CMPUCTL2_Pos         (4)                                               /*!< BPWM_T::WGCTL1: CMPUCTL2 Position      */
#define BPWM_WGCTL1_CMPUCTL2_Msk         (0x3ul << BPWM_WGCTL1_CMPUCTL2_Pos)               /*!< BPWM_T::WGCTL1: CMPUCTL2 Mask          */

#define BPWM_WGCTL1_CMPUCTL3_Pos         (6)                                               /*!< BPWM_T::WGCTL1: CMPUCTL3 Position      */
#define BPWM_WGCTL1_CMPUCTL3_Msk         (0x3ul << BPWM_WGCTL1_CMPUCTL3_Pos)               /*!< BPWM_T::WGCTL1: CMPUCTL3 Mask          */

#define BPWM_WGCTL1_CMPUCTL4_Pos         (8)                                               /*!< BPWM_T::WGCTL1: CMPUCTL4 Position      */
#define BPWM_WGCTL1_CMPUCTL4_Msk         (0x3ul << BPWM_WGCTL1_CMPUCTL4_Pos)               /*!< BPWM_T::WGCTL1: CMPUCTL4 Mask          */

#define BPWM_WGCTL1_CMPUCTL5_Pos         (10)                                              /*!< BPWM_T::WGCTL1: CMPUCTL5 Position      */
#define BPWM_WGCTL1_CMPUCTL5_Msk         (0x3ul << BPWM_WGCTL1_CMPUCTL5_Pos)               /*!< BPWM_T::WGCTL1: CMPUCTL5 Mask          */

#define BPWM_WGCTL1_CMPUCTLn_Pos         (0)                                               /*!< BPWM_T::WGCTL1: CMPUCTLn Position      */
#define BPWM_WGCTL1_CMPUCTLn_Msk         (0xffful << BPWM_WGCTL1_CMPUCTLn_Pos)             /*!< BPWM_T::WGCTL1: CMPUCTLn Mask          */

#define BPWM_WGCTL1_CMPDCTL0_Pos         (16)                                              /*!< BPWM_T::WGCTL1: CMPDCTL0 Position      */
#define BPWM_WGCTL1_CMPDCTL0_Msk         (0x3ul << BPWM_WGCTL1_CMPDCTL0_Pos)               /*!< BPWM_T::WGCTL1: CMPDCTL0 Mask          */

#define BPWM_WGCTL1_CMPDCTL1_Pos         (18)                                              /*!< BPWM_T::WGCTL1: CMPDCTL1 Position      */
#define BPWM_WGCTL1_CMPDCTL1_Msk         (0x3ul << BPWM_WGCTL1_CMPDCTL1_Pos)               /*!< BPWM_T::WGCTL1: CMPDCTL1 Mask          */

#define BPWM_WGCTL1_CMPDCTL2_Pos         (20)                                              /*!< BPWM_T::WGCTL1: CMPDCTL2 Position      */
#define BPWM_WGCTL1_CMPDCTL2_Msk         (0x3ul << BPWM_WGCTL1_CMPDCTL2_Pos)               /*!< BPWM_T::WGCTL1: CMPDCTL2 Mask          */

#define BPWM_WGCTL1_CMPDCTL3_Pos         (22)                                              /*!< BPWM_T::WGCTL1: CMPDCTL3 Position      */
#define BPWM_WGCTL1_CMPDCTL3_Msk         (0x3ul << BPWM_WGCTL1_CMPDCTL3_Pos)               /*!< BPWM_T::WGCTL1: CMPDCTL3 Mask          */

#define BPWM_WGCTL1_CMPDCTL4_Pos         (24)                                              /*!< BPWM_T::WGCTL1: CMPDCTL4 Position      */
#define BPWM_WGCTL1_CMPDCTL4_Msk         (0x3ul << BPWM_WGCTL1_CMPDCTL4_Pos)               /*!< BPWM_T::WGCTL1: CMPDCTL4 Mask          */

#define BPWM_WGCTL1_CMPDCTL5_Pos         (26)                                              /*!< BPWM_T::WGCTL1: CMPDCTL5 Position      */
#define BPWM_WGCTL1_CMPDCTL5_Msk         (0x3ul << BPWM_WGCTL1_CMPDCTL5_Pos)               /*!< BPWM_T::WGCTL1: CMPDCTL5 Mask          */

#define BPWM_WGCTL1_CMPDCTLn_Pos         (16)                                              /*!< BPWM_T::WGCTL1: CMPDCTLn Position      */
#define BPWM_WGCTL1_CMPDCTLn_Msk         (0xffful << BPWM_WGCTL1_CMPDCTLn_Pos)             /*!< BPWM_T::WGCTL1: CMPDCTLn Mask          */

#define BPWM_MSKEN_MSKEN0_Pos            (0)                                               /*!< BPWM_T::MSKEN: MSKEN0 Position         */
#define BPWM_MSKEN_MSKEN0_Msk            (0x1ul << BPWM_MSKEN_MSKEN0_Pos)                  /*!< BPWM_T::MSKEN: MSKEN0 Mask             */

#define BPWM_MSKEN_MSKEN1_Pos            (1)                                               /*!< BPWM_T::MSKEN: MSKEN1 Position         */
#define BPWM_MSKEN_MSKEN1_Msk            (0x1ul << BPWM_MSKEN_MSKEN1_Pos)                  /*!< BPWM_T::MSKEN: MSKEN1 Mask             */

#define BPWM_MSKEN_MSKEN2_Pos            (2)                                               /*!< BPWM_T::MSKEN: MSKEN2 Position         */
#define BPWM_MSKEN_MSKEN2_Msk            (0x1ul << BPWM_MSKEN_MSKEN2_Pos)                  /*!< BPWM_T::MSKEN: MSKEN2 Mask             */

#define BPWM_MSKEN_MSKEN3_Pos            (3)                                               /*!< BPWM_T::MSKEN: MSKEN3 Position         */
#define BPWM_MSKEN_MSKEN3_Msk            (0x1ul << BPWM_MSKEN_MSKEN3_Pos)                  /*!< BPWM_T::MSKEN: MSKEN3 Mask             */

#define BPWM_MSKEN_MSKEN4_Pos            (4)                                               /*!< BPWM_T::MSKEN: MSKEN4 Position         */
#define BPWM_MSKEN_MSKEN4_Msk            (0x1ul << BPWM_MSKEN_MSKEN4_Pos)                  /*!< BPWM_T::MSKEN: MSKEN4 Mask             */

#define BPWM_MSKEN_MSKEN5_Pos            (5)                                               /*!< BPWM_T::MSKEN: MSKEN5 Position         */
#define BPWM_MSKEN_MSKEN5_Msk            (0x1ul << BPWM_MSKEN_MSKEN5_Pos)                  /*!< BPWM_T::MSKEN: MSKEN5 Mask             */

#define BPWM_MSKEN_MSKENn_Pos            (0)                                               /*!< BPWM_T::MSKEN: MSKENn Position         */
#define BPWM_MSKEN_MSKENn_Msk            (0x3ful << BPWM_MSKEN_MSKENn_Pos)                 /*!< BPWM_T::MSKEN: MSKENn Mask             */

#define BPWM_MSK_MSKDAT0_Pos             (0)                                               /*!< BPWM_T::MSK: MSKDAT0 Position          */
#define BPWM_MSK_MSKDAT0_Msk             (0x1ul << BPWM_MSK_MSKDAT0_Pos)                   /*!< BPWM_T::MSK: MSKDAT0 Mask              */

#define BPWM_MSK_MSKDAT1_Pos             (1)                                               /*!< BPWM_T::MSK: MSKDAT1 Position          */
#define BPWM_MSK_MSKDAT1_Msk             (0x1ul << BPWM_MSK_MSKDAT1_Pos)                   /*!< BPWM_T::MSK: MSKDAT1 Mask              */

#define BPWM_MSK_MSKDAT2_Pos             (2)                                               /*!< BPWM_T::MSK: MSKDAT2 Position          */
#define BPWM_MSK_MSKDAT2_Msk             (0x1ul << BPWM_MSK_MSKDAT2_Pos)                   /*!< BPWM_T::MSK: MSKDAT2 Mask              */

#define BPWM_MSK_MSKDAT3_Pos             (3)                                               /*!< BPWM_T::MSK: MSKDAT3 Position          */
#define BPWM_MSK_MSKDAT3_Msk             (0x1ul << BPWM_MSK_MSKDAT3_Pos)                   /*!< BPWM_T::MSK: MSKDAT3 Mask              */

#define BPWM_MSK_MSKDAT4_Pos             (4)                                               /*!< BPWM_T::MSK: MSKDAT4 Position          */
#define BPWM_MSK_MSKDAT4_Msk             (0x1ul << BPWM_MSK_MSKDAT4_Pos)                   /*!< BPWM_T::MSK: MSKDAT4 Mask              */

#define BPWM_MSK_MSKDAT5_Pos             (5)                                               /*!< BPWM_T::MSK: MSKDAT5 Position          */
#define BPWM_MSK_MSKDAT5_Msk             (0x1ul << BPWM_MSK_MSKDAT5_Pos)                   /*!< BPWM_T::MSK: MSKDAT5 Mask              */

#define BPWM_MSK_MSKDATn_Pos             (0)                                               /*!< BPWM_T::MSK: MSKDATn Position          */
#define BPWM_MSK_MSKDATn_Msk             (0x3ful << BPWM_MSK_MSKDATn_Pos)                  /*!< BPWM_T::MSK: MSKDATn Mask              */

#define BPWM_POLCTL_PINV0_Pos            (0)                                               /*!< BPWM_T::POLCTL: PINV0 Position         */
#define BPWM_POLCTL_PINV0_Msk            (0x1ul << BPWM_POLCTL_PINV0_Pos)                  /*!< BPWM_T::POLCTL: PINV0 Mask             */

#define BPWM_POLCTL_PINV1_Pos            (1)                                               /*!< BPWM_T::POLCTL: PINV1 Position         */
#define BPWM_POLCTL_PINV1_Msk            (0x1ul << BPWM_POLCTL_PINV1_Pos)                  /*!< BPWM_T::POLCTL: PINV1 Mask             */

#define BPWM_POLCTL_PINV2_Pos            (2)                                               /*!< BPWM_T::POLCTL: PINV2 Position         */
#define BPWM_POLCTL_PINV2_Msk            (0x1ul << BPWM_POLCTL_PINV2_Pos)                  /*!< BPWM_T::POLCTL: PINV2 Mask             */

#define BPWM_POLCTL_PINV3_Pos            (3)                                               /*!< BPWM_T::POLCTL: PINV3 Position         */
#define BPWM_POLCTL_PINV3_Msk            (0x1ul << BPWM_POLCTL_PINV3_Pos)                  /*!< BPWM_T::POLCTL: PINV3 Mask             */

#define BPWM_POLCTL_PINV4_Pos            (4)                                               /*!< BPWM_T::POLCTL: PINV4 Position         */
#define BPWM_POLCTL_PINV4_Msk            (0x1ul << BPWM_POLCTL_PINV4_Pos)                  /*!< BPWM_T::POLCTL: PINV4 Mask             */

#define BPWM_POLCTL_PINV5_Pos            (5)                                               /*!< BPWM_T::POLCTL: PINV5 Position         */
#define BPWM_POLCTL_PINV5_Msk            (0x1ul << BPWM_POLCTL_PINV5_Pos)                  /*!< BPWM_T::POLCTL: PINV5 Mask             */

#define BPWM_POLCTL_PINVn_Pos            (0)                                               /*!< BPWM_T::POLCTL: PINVn Position         */
#define BPWM_POLCTL_PINVn_Msk            (0x3ful << BPWM_POLCTL_PINVn_Pos)                 /*!< BPWM_T::POLCTL: PINVn Mask             */

#define BPWM_POEN_POEN0_Pos              (0)                                               /*!< BPWM_T::POEN: POEN0 Position           */
#define BPWM_POEN_POEN0_Msk              (0x1ul << BPWM_POEN_POEN0_Pos)                    /*!< BPWM_T::POEN: POEN0 Mask               */

#define BPWM_POEN_POEN1_Pos              (1)                                               /*!< BPWM_T::POEN: POEN1 Position           */
#define BPWM_POEN_POEN1_Msk              (0x1ul << BPWM_POEN_POEN1_Pos)                    /*!< BPWM_T::POEN: POEN1 Mask               */

#define BPWM_POEN_POEN2_Pos              (2)                                               /*!< BPWM_T::POEN: POEN2 Position           */
#define BPWM_POEN_POEN2_Msk              (0x1ul << BPWM_POEN_POEN2_Pos)                    /*!< BPWM_T::POEN: POEN2 Mask               */

#define BPWM_POEN_POEN3_Pos              (3)                                               /*!< BPWM_T::POEN: POEN3 Position           */
#define BPWM_POEN_POEN3_Msk              (0x1ul << BPWM_POEN_POEN3_Pos)                    /*!< BPWM_T::POEN: POEN3 Mask               */

#define BPWM_POEN_POEN4_Pos              (4)                                               /*!< BPWM_T::POEN: POEN4 Position           */
#define BPWM_POEN_POEN4_Msk              (0x1ul << BPWM_POEN_POEN4_Pos)                    /*!< BPWM_T::POEN: POEN4 Mask               */

#define BPWM_POEN_POEN5_Pos              (5)                                               /*!< BPWM_T::POEN: POEN5 Position           */
#define BPWM_POEN_POEN5_Msk              (0x1ul << BPWM_POEN_POEN5_Pos)                    /*!< BPWM_T::POEN: POEN5 Mask               */

#define BPWM_POEN_POENn_Pos              (0)                                               /*!< BPWM_T::POEN: POENn Position           */
#define BPWM_POEN_POENn_Msk              (0x3ful << BPWM_POEN_POENn_Pos)                   /*!< BPWM_T::POEN: POENn Mask               */

#define BPWM_INTEN_ZIEN0_Pos             (0)                                               /*!< BPWM_T::INTEN: ZIEN0 Position          */
#define BPWM_INTEN_ZIEN0_Msk             (0x1ul << BPWM_INTEN_ZIEN0_Pos)                   /*!< BPWM_T::INTEN: ZIEN0 Mask              */

#define BPWM_INTEN_PIEN0_Pos             (8)                                               /*!< BPWM_T::INTEN: PIEN0 Position          */
#define BPWM_INTEN_PIEN0_Msk             (0x1ul << BPWM_INTEN_PIEN0_Pos)                   /*!< BPWM_T::INTEN: PIEN0 Mask              */

#define BPWM_INTEN_CMPUIEN0_Pos          (16)                                              /*!< BPWM_T::INTEN: CMPUIEN0 Position       */
#define BPWM_INTEN_CMPUIEN0_Msk          (0x1ul << BPWM_INTEN_CMPUIEN0_Pos)                /*!< BPWM_T::INTEN: CMPUIEN0 Mask           */

#define BPWM_INTEN_CMPUIEN1_Pos          (17)                                              /*!< BPWM_T::INTEN: CMPUIEN1 Position       */
#define BPWM_INTEN_CMPUIEN1_Msk          (0x1ul << BPWM_INTEN_CMPUIEN1_Pos)                /*!< BPWM_T::INTEN: CMPUIEN1 Mask           */

#define BPWM_INTEN_CMPUIEN2_Pos          (18)                                              /*!< BPWM_T::INTEN: CMPUIEN2 Position       */
#define BPWM_INTEN_CMPUIEN2_Msk          (0x1ul << BPWM_INTEN_CMPUIEN2_Pos)                /*!< BPWM_T::INTEN: CMPUIEN2 Mask           */

#define BPWM_INTEN_CMPUIEN3_Pos          (19)                                              /*!< BPWM_T::INTEN: CMPUIEN3 Position       */
#define BPWM_INTEN_CMPUIEN3_Msk          (0x1ul << BPWM_INTEN_CMPUIEN3_Pos)                /*!< BPWM_T::INTEN: CMPUIEN3 Mask           */

#define BPWM_INTEN_CMPUIEN4_Pos          (20)                                              /*!< BPWM_T::INTEN: CMPUIEN4 Position       */
#define BPWM_INTEN_CMPUIEN4_Msk          (0x1ul << BPWM_INTEN_CMPUIEN4_Pos)                /*!< BPWM_T::INTEN: CMPUIEN4 Mask           */

#define BPWM_INTEN_CMPUIEN5_Pos          (21)                                              /*!< BPWM_T::INTEN: CMPUIEN5 Position       */
#define BPWM_INTEN_CMPUIEN5_Msk          (0x1ul << BPWM_INTEN_CMPUIEN5_Pos)                /*!< BPWM_T::INTEN: CMPUIEN5 Mask           */

#define BPWM_INTEN_CMPUIENn_Pos          (16)                                              /*!< BPWM_T::INTEN: CMPUIENn Position       */
#define BPWM_INTEN_CMPUIENn_Msk          (0x3ful << BPWM_INTEN_CMPUIENn_Pos)               /*!< BPWM_T::INTEN: CMPUIENn Mask           */

#define BPWM_INTEN_CMPDIEN0_Pos          (24)                                              /*!< BPWM_T::INTEN: CMPDIEN0 Position       */
#define BPWM_INTEN_CMPDIEN0_Msk          (0x1ul << BPWM_INTEN_CMPDIEN0_Pos)                /*!< BPWM_T::INTEN: CMPDIEN0 Mask           */

#define BPWM_INTEN_CMPDIEN1_Pos          (25)                                              /*!< BPWM_T::INTEN: CMPDIEN1 Position       */
#define BPWM_INTEN_CMPDIEN1_Msk          (0x1ul << BPWM_INTEN_CMPDIEN1_Pos)                /*!< BPWM_T::INTEN: CMPDIEN1 Mask           */

#define BPWM_INTEN_CMPDIEN2_Pos          (26)                                              /*!< BPWM_T::INTEN: CMPDIEN2 Position       */
#define BPWM_INTEN_CMPDIEN2_Msk          (0x1ul << BPWM_INTEN_CMPDIEN2_Pos)                /*!< BPWM_T::INTEN: CMPDIEN2 Mask           */

#define BPWM_INTEN_CMPDIEN3_Pos          (27)                                              /*!< BPWM_T::INTEN: CMPDIEN3 Position       */
#define BPWM_INTEN_CMPDIEN3_Msk          (0x1ul << BPWM_INTEN_CMPDIEN3_Pos)                /*!< BPWM_T::INTEN: CMPDIEN3 Mask           */

#define BPWM_INTEN_CMPDIEN4_Pos          (28)                                              /*!< BPWM_T::INTEN: CMPDIEN4 Position       */
#define BPWM_INTEN_CMPDIEN4_Msk          (0x1ul << BPWM_INTEN_CMPDIEN4_Pos)                /*!< BPWM_T::INTEN: CMPDIEN4 Mask           */

#define BPWM_INTEN_CMPDIEN5_Pos          (29)                                              /*!< BPWM_T::INTEN: CMPDIEN5 Position       */
#define BPWM_INTEN_CMPDIEN5_Msk          (0x1ul << BPWM_INTEN_CMPDIEN5_Pos)                /*!< BPWM_T::INTEN: CMPDIEN5 Mask           */

#define BPWM_INTEN_CMPDIENn_Pos          (24)                                              /*!< BPWM_T::INTEN: CMPDIENn Position       */
#define BPWM_INTEN_CMPDIENn_Msk          (0x3ful << BPWM_INTEN_CMPDIENn_Pos)               /*!< BPWM_T::INTEN: CMPDIENn Mask           */

#define BPWM_INTSTS_ZIF0_Pos             (0)                                               /*!< BPWM_T::INTSTS: ZIF0 Position          */
#define BPWM_INTSTS_ZIF0_Msk             (0x1ul << BPWM_INTSTS_ZIF0_Pos)                   /*!< BPWM_T::INTSTS: ZIF0 Mask              */

#define BPWM_INTSTS_PIF0_Pos             (8)                                               /*!< BPWM_T::INTSTS: PIF0 Position          */
#define BPWM_INTSTS_PIF0_Msk             (0x1ul << BPWM_INTSTS_PIF0_Pos)                   /*!< BPWM_T::INTSTS: PIF0 Mask              */

#define BPWM_INTSTS_CMPUIF0_Pos          (16)                                              /*!< BPWM_T::INTSTS: CMPUIF0 Position       */
#define BPWM_INTSTS_CMPUIF0_Msk          (0x1ul << BPWM_INTSTS_CMPUIF0_Pos)                /*!< BPWM_T::INTSTS: CMPUIF0 Mask           */

#define BPWM_INTSTS_CMPUIF1_Pos          (17)                                              /*!< BPWM_T::INTSTS: CMPUIF1 Position       */
#define BPWM_INTSTS_CMPUIF1_Msk          (0x1ul << BPWM_INTSTS_CMPUIF1_Pos)                /*!< BPWM_T::INTSTS: CMPUIF1 Mask           */

#define BPWM_INTSTS_CMPUIF2_Pos          (18)                                              /*!< BPWM_T::INTSTS: CMPUIF2 Position       */
#define BPWM_INTSTS_CMPUIF2_Msk          (0x1ul << BPWM_INTSTS_CMPUIF2_Pos)                /*!< BPWM_T::INTSTS: CMPUIF2 Mask           */

#define BPWM_INTSTS_CMPUIF3_Pos          (19)                                              /*!< BPWM_T::INTSTS: CMPUIF3 Position       */
#define BPWM_INTSTS_CMPUIF3_Msk          (0x1ul << BPWM_INTSTS_CMPUIF3_Pos)                /*!< BPWM_T::INTSTS: CMPUIF3 Mask           */

#define BPWM_INTSTS_CMPUIF4_Pos          (20)                                              /*!< BPWM_T::INTSTS: CMPUIF4 Position       */
#define BPWM_INTSTS_CMPUIF4_Msk          (0x1ul << BPWM_INTSTS_CMPUIF4_Pos)                /*!< BPWM_T::INTSTS: CMPUIF4 Mask           */

#define BPWM_INTSTS_CMPUIF5_Pos          (21)                                              /*!< BPWM_T::INTSTS: CMPUIF5 Position       */
#define BPWM_INTSTS_CMPUIF5_Msk          (0x1ul << BPWM_INTSTS_CMPUIF5_Pos)                /*!< BPWM_T::INTSTS: CMPUIF5 Mask           */

#define BPWM_INTSTS_CMPUIFn_Pos          (16)                                              /*!< BPWM_T::INTSTS: CMPUIFn Position       */
#define BPWM_INTSTS_CMPUIFn_Msk          (0x3ful << BPWM_INTSTS_CMPUIFn_Pos)               /*!< BPWM_T::INTSTS: CMPUIFn Mask           */

#define BPWM_INTSTS_CMPDIF0_Pos          (24)                                              /*!< BPWM_T::INTSTS: CMPDIF0 Position       */
#define BPWM_INTSTS_CMPDIF0_Msk          (0x1ul << BPWM_INTSTS_CMPDIF0_Pos)                /*!< BPWM_T::INTSTS: CMPDIF0 Mask           */

#define BPWM_INTSTS_CMPDIF1_Pos          (25)                                              /*!< BPWM_T::INTSTS: CMPDIF1 Position       */
#define BPWM_INTSTS_CMPDIF1_Msk          (0x1ul << BPWM_INTSTS_CMPDIF1_Pos)                /*!< BPWM_T::INTSTS: CMPDIF1 Mask           */

#define BPWM_INTSTS_CMPDIF2_Pos          (26)                                              /*!< BPWM_T::INTSTS: CMPDIF2 Position       */
#define BPWM_INTSTS_CMPDIF2_Msk          (0x1ul << BPWM_INTSTS_CMPDIF2_Pos)                /*!< BPWM_T::INTSTS: CMPDIF2 Mask           */

#define BPWM_INTSTS_CMPDIF3_Pos          (27)                                              /*!< BPWM_T::INTSTS: CMPDIF3 Position       */
#define BPWM_INTSTS_CMPDIF3_Msk          (0x1ul << BPWM_INTSTS_CMPDIF3_Pos)                /*!< BPWM_T::INTSTS: CMPDIF3 Mask           */

#define BPWM_INTSTS_CMPDIF4_Pos          (28)                                              /*!< BPWM_T::INTSTS: CMPDIF4 Position       */
#define BPWM_INTSTS_CMPDIF4_Msk          (0x1ul << BPWM_INTSTS_CMPDIF4_Pos)                /*!< BPWM_T::INTSTS: CMPDIF4 Mask           */

#define BPWM_INTSTS_CMPDIF5_Pos          (29)                                              /*!< BPWM_T::INTSTS: CMPDIF5 Position       */
#define BPWM_INTSTS_CMPDIF5_Msk          (0x1ul << BPWM_INTSTS_CMPDIF5_Pos)                /*!< BPWM_T::INTSTS: CMPDIF5 Mask           */

#define BPWM_INTSTS_CMPDIFn_Pos          (24)                                              /*!< BPWM_T::INTSTS: CMPDIFn Position       */
#define BPWM_INTSTS_CMPDIFn_Msk          (0x3ful << BPWM_INTSTS_CMPDIFn_Pos)               /*!< BPWM_T::INTSTS: CMPDIFn Mask           */

#define BPWM_EADCTS0_TRGSEL0_Pos         (0)                                               /*!< BPWM_T::EADCTS0: TRGSEL0 Position      */
#define BPWM_EADCTS0_TRGSEL0_Msk         (0xful << BPWM_EADCTS0_TRGSEL0_Pos)               /*!< BPWM_T::EADCTS0: TRGSEL0 Mask          */

#define BPWM_EADCTS0_TRGEN0_Pos          (7)                                               /*!< BPWM_T::EADCTS0: TRGEN0 Position       */
#define BPWM_EADCTS0_TRGEN0_Msk          (0x1ul << BPWM_EADCTS0_TRGEN0_Pos)                /*!< BPWM_T::EADCTS0: TRGEN0 Mask           */

#define BPWM_EADCTS0_TRGSEL1_Pos         (8)                                               /*!< BPWM_T::EADCTS0: TRGSEL1 Position      */
#define BPWM_EADCTS0_TRGSEL1_Msk         (0xful << BPWM_EADCTS0_TRGSEL1_Pos)               /*!< BPWM_T::EADCTS0: TRGSEL1 Mask          */

#define BPWM_EADCTS0_TRGEN1_Pos          (15)                                              /*!< BPWM_T::EADCTS0: TRGEN1 Position       */
#define BPWM_EADCTS0_TRGEN1_Msk          (0x1ul << BPWM_EADCTS0_TRGEN1_Pos)                /*!< BPWM_T::EADCTS0: TRGEN1 Mask           */

#define BPWM_EADCTS0_TRGSEL2_Pos         (16)                                              /*!< BPWM_T::EADCTS0: TRGSEL2 Position      */
#define BPWM_EADCTS0_TRGSEL2_Msk         (0xful << BPWM_EADCTS0_TRGSEL2_Pos)               /*!< BPWM_T::EADCTS0: TRGSEL2 Mask          */

#define BPWM_EADCTS0_TRGEN2_Pos          (23)                                              /*!< BPWM_T::EADCTS0: TRGEN2 Position       */
#define BPWM_EADCTS0_TRGEN2_Msk          (0x1ul << BPWM_EADCTS0_TRGEN2_Pos)                /*!< BPWM_T::EADCTS0: TRGEN2 Mask           */

#define BPWM_EADCTS0_TRGSEL3_Pos         (24)                                              /*!< BPWM_T::EADCTS0: TRGSEL3 Position      */
#define BPWM_EADCTS0_TRGSEL3_Msk         (0xful << BPWM_EADCTS0_TRGSEL3_Pos)               /*!< BPWM_T::EADCTS0: TRGSEL3 Mask          */

#define BPWM_EADCTS0_TRGEN3_Pos          (31)                                              /*!< BPWM_T::EADCTS0: TRGEN3 Position       */
#define BPWM_EADCTS0_TRGEN3_Msk          (0x1ul << BPWM_EADCTS0_TRGEN3_Pos)                /*!< BPWM_T::EADCTS0: TRGEN3 Mask           */

#define BPWM_EADCTS1_TRGSEL4_Pos         (0)                                               /*!< BPWM_T::EADCTS1: TRGSEL4 Position      */
#define BPWM_EADCTS1_TRGSEL4_Msk         (0xful << BPWM_EADCTS1_TRGSEL4_Pos)               /*!< BPWM_T::EADCTS1: TRGSEL4 Mask          */

#define BPWM_EADCTS1_TRGEN4_Pos          (7)                                               /*!< BPWM_T::EADCTS1: TRGEN4 Position       */
#define BPWM_EADCTS1_TRGEN4_Msk          (0x1ul << BPWM_EADCTS1_TRGEN4_Pos)                /*!< BPWM_T::EADCTS1: TRGEN4 Mask           */

#define BPWM_EADCTS1_TRGSEL5_Pos         (8)                                               /*!< BPWM_T::EADCTS1: TRGSEL5 Position      */
#define BPWM_EADCTS1_TRGSEL5_Msk         (0xful << BPWM_EADCTS1_TRGSEL5_Pos)               /*!< BPWM_T::EADCTS1: TRGSEL5 Mask          */

#define BPWM_EADCTS1_TRGEN5_Pos          (15)                                              /*!< BPWM_T::EADCTS1: TRGEN5 Position       */
#define BPWM_EADCTS1_TRGEN5_Msk          (0x1ul << BPWM_EADCTS1_TRGEN5_Pos)                /*!< BPWM_T::EADCTS1: TRGEN5 Mask           */

#define BPWM_SSCTL_SSEN0_Pos             (0)                                               /*!< BPWM_T::SSCTL: SSEN0 Position          */
#define BPWM_SSCTL_SSEN0_Msk             (0x1ul << BPWM_SSCTL_SSEN0_Pos)                   /*!< BPWM_T::SSCTL: SSEN0 Mask              */

#define BPWM_SSCTL_SSRC_Pos              (8)                                               /*!< BPWM_T::SSCTL: SSRC Position           */
#define BPWM_SSCTL_SSRC_Msk              (0x3ul << BPWM_SSCTL_SSRC_Pos)                    /*!< BPWM_T::SSCTL: SSRC Mask               */

#define BPWM_SSTRG_CNTSEN_Pos            (0)                                               /*!< BPWM_T::SSTRG: CNTSEN Position         */
#define BPWM_SSTRG_CNTSEN_Msk            (0x1ul << BPWM_SSTRG_CNTSEN_Pos)                  /*!< BPWM_T::SSTRG: CNTSEN Mask             */

#define BPWM_STATUS_CNTMAX0_Pos          (0)                                               /*!< BPWM_T::STATUS: CNTMAX0 Position       */
#define BPWM_STATUS_CNTMAX0_Msk          (0x1ul << BPWM_STATUS_CNTMAX0_Pos)                /*!< BPWM_T::STATUS: CNTMAX0 Mask           */

#define BPWM_STATUS_EADCTRG0_Pos         (16)                                              /*!< BPWM_T::STATUS: EADCTRG0 Position      */
#define BPWM_STATUS_EADCTRG0_Msk         (0x1ul << BPWM_STATUS_EADCTRG0_Pos)               /*!< BPWM_T::STATUS: EADCTRG0 Mask          */

#define BPWM_STATUS_EADCTRG1_Pos         (17)                                              /*!< BPWM_T::STATUS: EADCTRG1 Position      */
#define BPWM_STATUS_EADCTRG1_Msk         (0x1ul << BPWM_STATUS_EADCTRG1_Pos)               /*!< BPWM_T::STATUS: EADCTRG1 Mask          */

#define BPWM_STATUS_EADCTRG2_Pos         (18)                                              /*!< BPWM_T::STATUS: EADCTRG2 Position      */
#define BPWM_STATUS_EADCTRG2_Msk         (0x1ul << BPWM_STATUS_EADCTRG2_Pos)               /*!< BPWM_T::STATUS: EADCTRG2 Mask          */

#define BPWM_STATUS_EADCTRG3_Pos         (19)                                              /*!< BPWM_T::STATUS: EADCTRG3 Position      */
#define BPWM_STATUS_EADCTRG3_Msk         (0x1ul << BPWM_STATUS_EADCTRG3_Pos)               /*!< BPWM_T::STATUS: EADCTRG3 Mask          */

#define BPWM_STATUS_EADCTRG4_Pos         (20)                                              /*!< BPWM_T::STATUS: EADCTRG4 Position      */
#define BPWM_STATUS_EADCTRG4_Msk         (0x1ul << BPWM_STATUS_EADCTRG4_Pos)               /*!< BPWM_T::STATUS: EADCTRG4 Mask          */

#define BPWM_STATUS_EADCTRG5_Pos         (21)                                              /*!< BPWM_T::STATUS: EADCTRG5 Position      */
#define BPWM_STATUS_EADCTRG5_Msk         (0x1ul << BPWM_STATUS_EADCTRG5_Pos)               /*!< BPWM_T::STATUS: EADCTRG5 Mask          */

#define BPWM_STATUS_EADCTRGn_Pos         (16)                                              /*!< BPWM_T::STATUS: EADCTRGn Position       */
#define BPWM_STATUS_EADCTRGn_Msk         (0x3ful << BPWM_STATUS_EADCTRGn_Pos)               /*!< BPWM_T::STATUS: EADCTRGn Mask           */

#define BPWM_CAPINEN_CAPINEN0_Pos        (0)                                               /*!< BPWM_T::CAPINEN: CAPINEN0 Position     */
#define BPWM_CAPINEN_CAPINEN0_Msk        (0x1ul << BPWM_CAPINEN_CAPINEN0_Pos)              /*!< BPWM_T::CAPINEN: CAPINEN0 Mask         */

#define BPWM_CAPINEN_CAPINEN1_Pos        (1)                                               /*!< BPWM_T::CAPINEN: CAPINEN1 Position     */
#define BPWM_CAPINEN_CAPINEN1_Msk        (0x1ul << BPWM_CAPINEN_CAPINEN1_Pos)              /*!< BPWM_T::CAPINEN: CAPINEN1 Mask         */

#define BPWM_CAPINEN_CAPINEN2_Pos        (2)                                               /*!< BPWM_T::CAPINEN: CAPINEN2 Position     */
#define BPWM_CAPINEN_CAPINEN2_Msk        (0x1ul << BPWM_CAPINEN_CAPINEN2_Pos)              /*!< BPWM_T::CAPINEN: CAPINEN2 Mask         */

#define BPWM_CAPINEN_CAPINEN3_Pos        (3)                                               /*!< BPWM_T::CAPINEN: CAPINEN3 Position     */
#define BPWM_CAPINEN_CAPINEN3_Msk        (0x1ul << BPWM_CAPINEN_CAPINEN3_Pos)              /*!< BPWM_T::CAPINEN: CAPINEN3 Mask         */

#define BPWM_CAPINEN_CAPINEN4_Pos        (4)                                               /*!< BPWM_T::CAPINEN: CAPINEN4 Position     */
#define BPWM_CAPINEN_CAPINEN4_Msk        (0x1ul << BPWM_CAPINEN_CAPINEN4_Pos)              /*!< BPWM_T::CAPINEN: CAPINEN4 Mask         */

#define BPWM_CAPINEN_CAPINEN5_Pos        (5)                                               /*!< BPWM_T::CAPINEN: CAPINEN5 Position     */
#define BPWM_CAPINEN_CAPINEN5_Msk        (0x1ul << BPWM_CAPINEN_CAPINEN5_Pos)              /*!< BPWM_T::CAPINEN: CAPINEN5 Mask         */

#define BPWM_CAPINEN_CAPINENn_Pos        (0)                                               /*!< BPWM_T::CAPINEN: CAPINENn Position     */
#define BPWM_CAPINEN_CAPINENn_Msk        (0x3ful << BPWM_CAPINEN_CAPINENn_Pos)             /*!< BPWM_T::CAPINEN: CAPINENn Mask         */

#define BPWM_CAPCTL_CAPEN0_Pos           (0)                                               /*!< BPWM_T::CAPCTL: CAPEN0 Position        */
#define BPWM_CAPCTL_CAPEN0_Msk           (0x1ul << BPWM_CAPCTL_CAPEN0_Pos)                 /*!< BPWM_T::CAPCTL: CAPEN0 Mask            */

#define BPWM_CAPCTL_CAPEN1_Pos           (1)                                               /*!< BPWM_T::CAPCTL: CAPEN1 Position        */
#define BPWM_CAPCTL_CAPEN1_Msk           (0x1ul << BPWM_CAPCTL_CAPEN1_Pos)                 /*!< BPWM_T::CAPCTL: CAPEN1 Mask            */

#define BPWM_CAPCTL_CAPEN2_Pos           (2)                                               /*!< BPWM_T::CAPCTL: CAPEN2 Position        */
#define BPWM_CAPCTL_CAPEN2_Msk           (0x1ul << BPWM_CAPCTL_CAPEN2_Pos)                 /*!< BPWM_T::CAPCTL: CAPEN2 Mask            */

#define BPWM_CAPCTL_CAPEN3_Pos           (3)                                               /*!< BPWM_T::CAPCTL: CAPEN3 Position        */
#define BPWM_CAPCTL_CAPEN3_Msk           (0x1ul << BPWM_CAPCTL_CAPEN3_Pos)                 /*!< BPWM_T::CAPCTL: CAPEN3 Mask            */

#define BPWM_CAPCTL_CAPEN4_Pos           (4)                                               /*!< BPWM_T::CAPCTL: CAPEN4 Position        */
#define BPWM_CAPCTL_CAPEN4_Msk           (0x1ul << BPWM_CAPCTL_CAPEN4_Pos)                 /*!< BPWM_T::CAPCTL: CAPEN4 Mask            */

#define BPWM_CAPCTL_CAPEN5_Pos           (5)                                               /*!< BPWM_T::CAPCTL: CAPEN5 Position        */
#define BPWM_CAPCTL_CAPEN5_Msk           (0x1ul << BPWM_CAPCTL_CAPEN5_Pos)                 /*!< BPWM_T::CAPCTL: CAPEN5 Mask            */

#define BPWM_CAPCTL_CAPENn_Pos           (0)                                               /*!< BPWM_T::CAPCTL: CAPENn Position        */
#define BPWM_CAPCTL_CAPENn_Msk           (0x3ful << BPWM_CAPCTL_CAPENn_Pos)                /*!< BPWM_T::CAPCTL: CAPENn Mask            */

#define BPWM_CAPCTL_CAPINV0_Pos          (8)                                               /*!< BPWM_T::CAPCTL: CAPINV0 Position       */
#define BPWM_CAPCTL_CAPINV0_Msk          (0x1ul << BPWM_CAPCTL_CAPINV0_Pos)                /*!< BPWM_T::CAPCTL: CAPINV0 Mask           */

#define BPWM_CAPCTL_CAPINV1_Pos          (9)                                               /*!< BPWM_T::CAPCTL: CAPINV1 Position       */
#define BPWM_CAPCTL_CAPINV1_Msk          (0x1ul << BPWM_CAPCTL_CAPINV1_Pos)                /*!< BPWM_T::CAPCTL: CAPINV1 Mask           */

#define BPWM_CAPCTL_CAPINV2_Pos          (10)                                              /*!< BPWM_T::CAPCTL: CAPINV2 Position       */
#define BPWM_CAPCTL_CAPINV2_Msk          (0x1ul << BPWM_CAPCTL_CAPINV2_Pos)                /*!< BPWM_T::CAPCTL: CAPINV2 Mask           */

#define BPWM_CAPCTL_CAPINV3_Pos          (11)                                              /*!< BPWM_T::CAPCTL: CAPINV3 Position       */
#define BPWM_CAPCTL_CAPINV3_Msk          (0x1ul << BPWM_CAPCTL_CAPINV3_Pos)                /*!< BPWM_T::CAPCTL: CAPINV3 Mask           */

#define BPWM_CAPCTL_CAPINV4_Pos          (12)                                              /*!< BPWM_T::CAPCTL: CAPINV4 Position       */
#define BPWM_CAPCTL_CAPINV4_Msk          (0x1ul << BPWM_CAPCTL_CAPINV4_Pos)                /*!< BPWM_T::CAPCTL: CAPINV4 Mask           */

#define BPWM_CAPCTL_CAPINV5_Pos          (13)                                              /*!< BPWM_T::CAPCTL: CAPINV5 Position       */
#define BPWM_CAPCTL_CAPINV5_Msk          (0x1ul << BPWM_CAPCTL_CAPINV5_Pos)                /*!< BPWM_T::CAPCTL: CAPINV5 Mask           */

#define BPWM_CAPCTL_CAPINVn_Pos          (8)                                               /*!< BPWM_T::CAPCTL: CAPINVn Position       */
#define BPWM_CAPCTL_CAPINVn_Msk          (0x3ful << BPWM_CAPCTL_CAPINVn_Pos)               /*!< BPWM_T::CAPCTL: CAPINVn Mask           */

#define BPWM_CAPCTL_RCRLDEN0_Pos         (16)                                              /*!< BPWM_T::CAPCTL: RCRLDEN0 Position      */
#define BPWM_CAPCTL_RCRLDEN0_Msk         (0x1ul << BPWM_CAPCTL_RCRLDEN0_Pos)               /*!< BPWM_T::CAPCTL: RCRLDEN0 Mask          */

#define BPWM_CAPCTL_RCRLDEN1_Pos         (17)                                              /*!< BPWM_T::CAPCTL: RCRLDEN1 Position      */
#define BPWM_CAPCTL_RCRLDEN1_Msk         (0x1ul << BPWM_CAPCTL_RCRLDEN1_Pos)               /*!< BPWM_T::CAPCTL: RCRLDEN1 Mask          */

#define BPWM_CAPCTL_RCRLDEN2_Pos         (18)                                              /*!< BPWM_T::CAPCTL: RCRLDEN2 Position      */
#define BPWM_CAPCTL_RCRLDEN2_Msk         (0x1ul << BPWM_CAPCTL_RCRLDEN2_Pos)               /*!< BPWM_T::CAPCTL: RCRLDEN2 Mask          */

#define BPWM_CAPCTL_RCRLDEN3_Pos         (19)                                              /*!< BPWM_T::CAPCTL: RCRLDEN3 Position      */
#define BPWM_CAPCTL_RCRLDEN3_Msk         (0x1ul << BPWM_CAPCTL_RCRLDEN3_Pos)               /*!< BPWM_T::CAPCTL: RCRLDEN3 Mask          */

#define BPWM_CAPCTL_RCRLDEN4_Pos         (20)                                              /*!< BPWM_T::CAPCTL: RCRLDEN4 Position      */
#define BPWM_CAPCTL_RCRLDEN4_Msk         (0x1ul << BPWM_CAPCTL_RCRLDEN4_Pos)               /*!< BPWM_T::CAPCTL: RCRLDEN4 Mask          */

#define BPWM_CAPCTL_RCRLDEN5_Pos         (21)                                              /*!< BPWM_T::CAPCTL: RCRLDEN5 Position      */
#define BPWM_CAPCTL_RCRLDEN5_Msk         (0x1ul << BPWM_CAPCTL_RCRLDEN5_Pos)               /*!< BPWM_T::CAPCTL: RCRLDEN5 Mask          */

#define BPWM_CAPCTL_RCRLDENn_Pos         (16)                                              /*!< BPWM_T::CAPCTL: RCRLDENn Position      */
#define BPWM_CAPCTL_RCRLDENn_Msk         (0x3ful << BPWM_CAPCTL_RCRLDENn_Pos)              /*!< BPWM_T::CAPCTL: RCRLDENn Mask          */

#define BPWM_CAPCTL_FCRLDEN0_Pos         (24)                                              /*!< BPWM_T::CAPCTL: FCRLDEN0 Position      */
#define BPWM_CAPCTL_FCRLDEN0_Msk         (0x1ul << BPWM_CAPCTL_FCRLDEN0_Pos)               /*!< BPWM_T::CAPCTL: FCRLDEN0 Mask          */

#define BPWM_CAPCTL_FCRLDEN1_Pos         (25)                                              /*!< BPWM_T::CAPCTL: FCRLDEN1 Position      */
#define BPWM_CAPCTL_FCRLDEN1_Msk         (0x1ul << BPWM_CAPCTL_FCRLDEN1_Pos)               /*!< BPWM_T::CAPCTL: FCRLDEN1 Mask          */

#define BPWM_CAPCTL_FCRLDEN2_Pos         (26)                                              /*!< BPWM_T::CAPCTL: FCRLDEN2 Position      */
#define BPWM_CAPCTL_FCRLDEN2_Msk         (0x1ul << BPWM_CAPCTL_FCRLDEN2_Pos)               /*!< BPWM_T::CAPCTL: FCRLDEN2 Mask          */

#define BPWM_CAPCTL_FCRLDEN3_Pos         (27)                                              /*!< BPWM_T::CAPCTL: FCRLDEN3 Position      */
#define BPWM_CAPCTL_FCRLDEN3_Msk         (0x1ul << BPWM_CAPCTL_FCRLDEN3_Pos)               /*!< BPWM_T::CAPCTL: FCRLDEN3 Mask          */

#define BPWM_CAPCTL_FCRLDEN4_Pos         (28)                                              /*!< BPWM_T::CAPCTL: FCRLDEN4 Position      */
#define BPWM_CAPCTL_FCRLDEN4_Msk         (0x1ul << BPWM_CAPCTL_FCRLDEN4_Pos)               /*!< BPWM_T::CAPCTL: FCRLDEN4 Mask          */

#define BPWM_CAPCTL_FCRLDEN5_Pos         (29)                                              /*!< BPWM_T::CAPCTL: FCRLDEN5 Position      */
#define BPWM_CAPCTL_FCRLDEN5_Msk         (0x1ul << BPWM_CAPCTL_FCRLDEN5_Pos)               /*!< BPWM_T::CAPCTL: FCRLDEN5 Mask          */

#define BPWM_CAPCTL_FCRLDENn_Pos         (24)                                              /*!< BPWM_T::CAPCTL: FCRLDENn Position      */
#define BPWM_CAPCTL_FCRLDENn_Msk         (0x3ful << BPWM_CAPCTL_FCRLDENn_Pos)              /*!< BPWM_T::CAPCTL: FCRLDENn Mask          */

#define BPWM_CAPSTS_CRIFOV0_Pos          (0)                                               /*!< BPWM_T::CAPSTS: CRIFOV0 Position       */
#define BPWM_CAPSTS_CRIFOV0_Msk          (0x1ul << BPWM_CAPSTS_CRIFOV0_Pos)                /*!< BPWM_T::CAPSTS: CRIFOV0 Mask           */

#define BPWM_CAPSTS_CRIFOV1_Pos          (1)                                               /*!< BPWM_T::CAPSTS: CRIFOV1 Position       */
#define BPWM_CAPSTS_CRIFOV1_Msk          (0x1ul << BPWM_CAPSTS_CRIFOV1_Pos)                /*!< BPWM_T::CAPSTS: CRIFOV1 Mask           */

#define BPWM_CAPSTS_CRIFOV2_Pos          (2)                                               /*!< BPWM_T::CAPSTS: CRIFOV2 Position       */
#define BPWM_CAPSTS_CRIFOV2_Msk          (0x1ul << BPWM_CAPSTS_CRIFOV2_Pos)                /*!< BPWM_T::CAPSTS: CRIFOV2 Mask           */

#define BPWM_CAPSTS_CRIFOV3_Pos          (3)                                               /*!< BPWM_T::CAPSTS: CRIFOV3 Position       */
#define BPWM_CAPSTS_CRIFOV3_Msk          (0x1ul << BPWM_CAPSTS_CRIFOV3_Pos)                /*!< BPWM_T::CAPSTS: CRIFOV3 Mask           */

#define BPWM_CAPSTS_CRIFOV4_Pos          (4)                                               /*!< BPWM_T::CAPSTS: CRIFOV4 Position       */
#define BPWM_CAPSTS_CRIFOV4_Msk          (0x1ul << BPWM_CAPSTS_CRIFOV4_Pos)                /*!< BPWM_T::CAPSTS: CRIFOV4 Mask           */

#define BPWM_CAPSTS_CRIFOV5_Pos          (5)                                               /*!< BPWM_T::CAPSTS: CRIFOV5 Position       */
#define BPWM_CAPSTS_CRIFOV5_Msk          (0x1ul << BPWM_CAPSTS_CRIFOV5_Pos)                /*!< BPWM_T::CAPSTS: CRIFOV5 Mask           */

#define BPWM_CAPSTS_CRIFOVn_Pos          (0)                                               /*!< BPWM_T::CAPSTS: CRIFOVn Position       */
#define BPWM_CAPSTS_CRIFOVn_Msk          (0x3ful << BPWM_CAPSTS_CRIFOVn_Pos)               /*!< BPWM_T::CAPSTS: CRIFOVn Mask           */

#define BPWM_CAPSTS_CFIFOV0_Pos          (8)                                               /*!< BPWM_T::CAPSTS: CFIFOV0 Position       */
#define BPWM_CAPSTS_CFIFOV0_Msk          (0x1ul << BPWM_CAPSTS_CFIFOV0_Pos)                /*!< BPWM_T::CAPSTS: CFIFOV0 Mask           */

#define BPWM_CAPSTS_CFIFOV1_Pos          (9)                                               /*!< BPWM_T::CAPSTS: CFIFOV1 Position       */
#define BPWM_CAPSTS_CFIFOV1_Msk          (0x1ul << BPWM_CAPSTS_CFIFOV1_Pos)                /*!< BPWM_T::CAPSTS: CFIFOV1 Mask           */

#define BPWM_CAPSTS_CFIFOV2_Pos          (10)                                              /*!< BPWM_T::CAPSTS: CFIFOV2 Position       */
#define BPWM_CAPSTS_CFIFOV2_Msk          (0x1ul << BPWM_CAPSTS_CFIFOV2_Pos)                /*!< BPWM_T::CAPSTS: CFIFOV2 Mask           */

#define BPWM_CAPSTS_CFIFOV3_Pos          (11)                                              /*!< BPWM_T::CAPSTS: CFIFOV3 Position       */
#define BPWM_CAPSTS_CFIFOV3_Msk          (0x1ul << BPWM_CAPSTS_CFIFOV3_Pos)                /*!< BPWM_T::CAPSTS: CFIFOV3 Mask           */

#define BPWM_CAPSTS_CFIFOV4_Pos          (12)                                              /*!< BPWM_T::CAPSTS: CFIFOV4 Position       */
#define BPWM_CAPSTS_CFIFOV4_Msk          (0x1ul << BPWM_CAPSTS_CFIFOV4_Pos)                /*!< BPWM_T::CAPSTS: CFIFOV4 Mask           */

#define BPWM_CAPSTS_CFIFOV5_Pos          (13)                                              /*!< BPWM_T::CAPSTS: CFIFOV5 Position       */
#define BPWM_CAPSTS_CFIFOV5_Msk          (0x1ul << BPWM_CAPSTS_CFIFOV5_Pos)                /*!< BPWM_T::CAPSTS: CFIFOV5 Mask           */

#define BPWM_CAPSTS_CFIFOVn_Pos          (8)                                               /*!< BPWM_T::CAPSTS: CFIFOVn Position       */
#define BPWM_CAPSTS_CFIFOVn_Msk          (0x3ful << BPWM_CAPSTS_CFIFOVn_Pos)               /*!< BPWM_T::CAPSTS: CFIFOVn Mask           */

#define BPWM_RCAPDAT0_RCAPDAT_Pos        (0)                                               /*!< BPWM_T::RCAPDAT0: RCAPDAT Position     */
#define BPWM_RCAPDAT0_RCAPDAT_Msk        (0xfffful << BPWM_RCAPDAT0_RCAPDAT_Pos)           /*!< BPWM_T::RCAPDAT0: RCAPDAT Mask         */

#define BPWM_FCAPDAT0_FCAPDAT_Pos        (0)                                               /*!< BPWM_T::FCAPDAT0: FCAPDAT Position     */
#define BPWM_FCAPDAT0_FCAPDAT_Msk        (0xfffful << BPWM_FCAPDAT0_FCAPDAT_Pos)           /*!< BPWM_T::FCAPDAT0: FCAPDAT Mask         */

#define BPWM_RCAPDAT1_RCAPDAT_Pos        (0)                                               /*!< BPWM_T::RCAPDAT1: RCAPDAT Position     */
#define BPWM_RCAPDAT1_RCAPDAT_Msk        (0xfffful << BPWM_RCAPDAT1_RCAPDAT_Pos)           /*!< BPWM_T::RCAPDAT1: RCAPDAT Mask         */

#define BPWM_FCAPDAT1_FCAPDAT_Pos        (0)                                               /*!< BPWM_T::FCAPDAT1: FCAPDAT Position     */
#define BPWM_FCAPDAT1_FCAPDAT_Msk        (0xfffful << BPWM_FCAPDAT1_FCAPDAT_Pos)           /*!< BPWM_T::FCAPDAT1: FCAPDAT Mask         */

#define BPWM_RCAPDAT2_RCAPDAT_Pos        (0)                                               /*!< BPWM_T::RCAPDAT2: RCAPDAT Position     */
#define BPWM_RCAPDAT2_RCAPDAT_Msk        (0xfffful << BPWM_RCAPDAT2_RCAPDAT_Pos)           /*!< BPWM_T::RCAPDAT2: RCAPDAT Mask         */

#define BPWM_FCAPDAT2_FCAPDAT_Pos        (0)                                               /*!< BPWM_T::FCAPDAT2: FCAPDAT Position     */
#define BPWM_FCAPDAT2_FCAPDAT_Msk        (0xfffful << BPWM_FCAPDAT2_FCAPDAT_Pos)           /*!< BPWM_T::FCAPDAT2: FCAPDAT Mask         */

#define BPWM_RCAPDAT3_RCAPDAT_Pos        (0)                                               /*!< BPWM_T::RCAPDAT3: RCAPDAT Position     */
#define BPWM_RCAPDAT3_RCAPDAT_Msk        (0xfffful << BPWM_RCAPDAT3_RCAPDAT_Pos)           /*!< BPWM_T::RCAPDAT3: RCAPDAT Mask         */

#define BPWM_FCAPDAT3_FCAPDAT_Pos        (0)                                               /*!< BPWM_T::FCAPDAT3: FCAPDAT Position     */
#define BPWM_FCAPDAT3_FCAPDAT_Msk        (0xfffful << BPWM_FCAPDAT3_FCAPDAT_Pos)           /*!< BPWM_T::FCAPDAT3: FCAPDAT Mask         */

#define BPWM_RCAPDAT4_RCAPDAT_Pos        (0)                                               /*!< BPWM_T::RCAPDAT4: RCAPDAT Position     */
#define BPWM_RCAPDAT4_RCAPDAT_Msk        (0xfffful << BPWM_RCAPDAT4_RCAPDAT_Pos)           /*!< BPWM_T::RCAPDAT4: RCAPDAT Mask         */

#define BPWM_FCAPDAT4_FCAPDAT_Pos        (0)                                               /*!< BPWM_T::FCAPDAT4: FCAPDAT Position     */
#define BPWM_FCAPDAT4_FCAPDAT_Msk        (0xfffful << BPWM_FCAPDAT4_FCAPDAT_Pos)           /*!< BPWM_T::FCAPDAT4: FCAPDAT Mask         */

#define BPWM_RCAPDAT5_RCAPDAT_Pos        (0)                                               /*!< BPWM_T::RCAPDAT5: RCAPDAT Position     */
#define BPWM_RCAPDAT5_RCAPDAT_Msk        (0xfffful << BPWM_RCAPDAT5_RCAPDAT_Pos)           /*!< BPWM_T::RCAPDAT5: RCAPDAT Mask         */

#define BPWM_FCAPDAT5_FCAPDAT_Pos        (0)                                               /*!< BPWM_T::FCAPDAT5: FCAPDAT Position     */
#define BPWM_FCAPDAT5_FCAPDAT_Msk        (0xfffful << BPWM_FCAPDAT5_FCAPDAT_Pos)           /*!< BPWM_T::FCAPDAT5: FCAPDAT Mask         */

#define BPWM_CAPIEN_CAPRIENn_Pos         (0)                                               /*!< BPWM_T::CAPIEN: CAPRIENn Position      */
#define BPWM_CAPIEN_CAPRIENn_Msk         (0x3ful << BPWM_CAPIEN_CAPRIENn_Pos)              /*!< BPWM_T::CAPIEN: CAPRIENn Mask          */

#define BPWM_CAPIEN_CAPFIENn_Pos         (8)                                               /*!< BPWM_T::CAPIEN: CAPFIENn Position      */
#define BPWM_CAPIEN_CAPFIENn_Msk         (0x3ful << BPWM_CAPIEN_CAPFIENn_Pos)              /*!< BPWM_T::CAPIEN: CAPFIENn Mask          */

#define BPWM_CAPIF_CAPRIF0_Pos           (0)                                               /*!< BPWM_T::CAPIF: CAPRIF0 Position        */
#define BPWM_CAPIF_CAPRIF0_Msk           (0x1ul << BPWM_CAPIF_CAPRIF0_Pos)                 /*!< BPWM_T::CAPIF: CAPRIF0 Mask            */

#define BPWM_CAPIF_CAPRIF1_Pos           (1)                                               /*!< BPWM_T::CAPIF: CAPRIF1 Position        */
#define BPWM_CAPIF_CAPRIF1_Msk           (0x1ul << BPWM_CAPIF_CAPRIF1_Pos)                 /*!< BPWM_T::CAPIF: CAPRIF1 Mask            */

#define BPWM_CAPIF_CAPRIF2_Pos           (2)                                               /*!< BPWM_T::CAPIF: CAPRIF2 Position        */
#define BPWM_CAPIF_CAPRIF2_Msk           (0x1ul << BPWM_CAPIF_CAPRIF2_Pos)                 /*!< BPWM_T::CAPIF: CAPRIF2 Mask            */

#define BPWM_CAPIF_CAPRIF3_Pos           (3)                                               /*!< BPWM_T::CAPIF: CAPRIF3 Position        */
#define BPWM_CAPIF_CAPRIF3_Msk           (0x1ul << BPWM_CAPIF_CAPRIF3_Pos)                 /*!< BPWM_T::CAPIF: CAPRIF3 Mask            */

#define BPWM_CAPIF_CAPRIF4_Pos           (4)                                               /*!< BPWM_T::CAPIF: CAPRIF4 Position        */
#define BPWM_CAPIF_CAPRIF4_Msk           (0x1ul << BPWM_CAPIF_CAPRIF4_Pos)                 /*!< BPWM_T::CAPIF: CAPRIF4 Mask            */

#define BPWM_CAPIF_CAPRIF5_Pos           (5)                                               /*!< BPWM_T::CAPIF: CAPRIF5 Position        */
#define BPWM_CAPIF_CAPRIF5_Msk           (0x1ul << BPWM_CAPIF_CAPRIF5_Pos)                 /*!< BPWM_T::CAPIF: CAPRIF5 Mask            */

#define BPWM_CAPIF_CAPRIFn_Pos           (0)                                               /*!< BPWM_T::CAPIF: CAPRIFn Position        */
#define BPWM_CAPIF_CAPRIFn_Msk           (0x3ful << BPWM_CAPIF_CAPRIFn_Pos)                /*!< BPWM_T::CAPIF: CAPRIFn Mask            */

#define BPWM_CAPIF_CAPFIF0_Pos           (8)                                               /*!< BPWM_T::CAPIF: CAPFIF0 Position        */
#define BPWM_CAPIF_CAPFIF0_Msk           (0x1ul << BPWM_CAPIF_CAPFIF0_Pos)                 /*!< BPWM_T::CAPIF: CAPFIF0 Mask            */

#define BPWM_CAPIF_CAPFIF1_Pos           (9)                                               /*!< BPWM_T::CAPIF: CAPFIF1 Position        */
#define BPWM_CAPIF_CAPFIF1_Msk           (0x1ul << BPWM_CAPIF_CAPFIF1_Pos)                 /*!< BPWM_T::CAPIF: CAPFIF1 Mask            */

#define BPWM_CAPIF_CAPFIF2_Pos           (10)                                              /*!< BPWM_T::CAPIF: CAPFIF2 Position        */
#define BPWM_CAPIF_CAPFIF2_Msk           (0x1ul << BPWM_CAPIF_CAPFIF2_Pos)                 /*!< BPWM_T::CAPIF: CAPFIF2 Mask            */

#define BPWM_CAPIF_CAPFIF3_Pos           (11)                                              /*!< BPWM_T::CAPIF: CAPFIF3 Position        */
#define BPWM_CAPIF_CAPFIF3_Msk           (0x1ul << BPWM_CAPIF_CAPFIF3_Pos)                 /*!< BPWM_T::CAPIF: CAPFIF3 Mask            */

#define BPWM_CAPIF_CAPFIF4_Pos           (12)                                              /*!< BPWM_T::CAPIF: CAPFIF4 Position        */
#define BPWM_CAPIF_CAPFIF4_Msk           (0x1ul << BPWM_CAPIF_CAPFIF4_Pos)                 /*!< BPWM_T::CAPIF: CAPFIF4 Mask            */

#define BPWM_CAPIF_CAPFIF5_Pos           (13)                                              /*!< BPWM_T::CAPIF: CAPFIF5 Position        */
#define BPWM_CAPIF_CAPFIF5_Msk           (0x1ul << BPWM_CAPIF_CAPFIF5_Pos)                 /*!< BPWM_T::CAPIF: CAPFIF5 Mask            */

#define BPWM_CAPIF_CAPFIFn_Pos           (8)                                               /*!< BPWM_T::CAPIF: CAPFIFn Position        */
#define BPWM_CAPIF_CAPFIFn_Msk           (0x3ful << BPWM_CAPIF_CAPFIFn_Pos)                /*!< BPWM_T::CAPIF: CAPFIFn Mask            */

#define BPWM_PBUF_PBUF_Pos               (0)                                               /*!< BPWM_T::PBUF: PBUF Position            */
#define BPWM_PBUF_PBUF_Msk               (0xfffful << BPWM_PBUF_PBUF_Pos)                  /*!< BPWM_T::PBUF: PBUF Mask                */

#define BPWM_CMPBUF0_CMPBUF_Pos          (0)                                               /*!< BPWM_T::CMPBUF0: CMPBUF Position       */
#define BPWM_CMPBUF0_CMPBUF_Msk          (0xfffful << BPWM_CMPBUF0_CMPBUF_Pos)             /*!< BPWM_T::CMPBUF0: CMPBUF Mask           */

#define BPWM_CMPBUF1_CMPBUF_Pos          (0)                                               /*!< BPWM_T::CMPBUF1: CMPBUF Position       */
#define BPWM_CMPBUF1_CMPBUF_Msk          (0xfffful << BPWM_CMPBUF1_CMPBUF_Pos)             /*!< BPWM_T::CMPBUF1: CMPBUF Mask           */

#define BPWM_CMPBUF2_CMPBUF_Pos          (0)                                               /*!< BPWM_T::CMPBUF2: CMPBUF Position       */
#define BPWM_CMPBUF2_CMPBUF_Msk          (0xfffful << BPWM_CMPBUF2_CMPBUF_Pos)             /*!< BPWM_T::CMPBUF2: CMPBUF Mask           */

#define BPWM_CMPBUF3_CMPBUF_Pos          (0)                                               /*!< BPWM_T::CMPBUF3: CMPBUF Position       */
#define BPWM_CMPBUF3_CMPBUF_Msk          (0xfffful << BPWM_CMPBUF3_CMPBUF_Pos)             /*!< BPWM_T::CMPBUF3: CMPBUF Mask           */

#define BPWM_CMPBUF4_CMPBUF_Pos          (0)                                               /*!< BPWM_T::CMPBUF4: CMPBUF Position       */
#define BPWM_CMPBUF4_CMPBUF_Msk          (0xfffful << BPWM_CMPBUF4_CMPBUF_Pos)             /*!< BPWM_T::CMPBUF4: CMPBUF Mask           */

#define BPWM_CMPBUF5_CMPBUF_Pos          (0)                                               /*!< BPWM_T::CMPBUF5: CMPBUF Position       */
#define BPWM_CMPBUF5_CMPBUF_Msk          (0xfffful << BPWM_CMPBUF5_CMPBUF_Pos)             /*!< BPWM_T::CMPBUF5: CMPBUF Mask           */

/**@}*/ /* BPWM_CONST */
/**@}*/ /* end of BPWM register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __BPWM_REG_H__ */
