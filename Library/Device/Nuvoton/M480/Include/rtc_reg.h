/**************************************************************************//**
 * @file     rtc_reg.h
 * @version  V1.00
 * @brief    RTC register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __RTC_REG_H__
#define __RTC_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
  @{
*/

/**
    @addtogroup RTC Real Time Clock Controller(RTC)
    Memory Mapped Structure for RTC Controller
@{ */

typedef struct
{


    /**
@var RTC_T::INIT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INIT
</font><br><p> <font size="2">
Offset: 0x00  RTC Initiation Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>INIT_ACTIVE</td><td><div style="word-wrap: break-word;"><b>RTC Active Status (Read Only)
</b><br>
0 = RTC is at reset state.
<br>
1 = RTC is at normal active state.
<br>
</div></td></tr><tr><td>
[31:1]</td><td>INIT</td><td><div style="word-wrap: break-word;"><b>RTC Initiation (Write Only)
</b><br>
When RTC block is powered on, RTC is at reset state
<br>
User has to write a number (0xa5eb1357) to INIT to make RTC leaving reset state
<br>
Once the INIT is written as 0xa5eb1357, the RTC will be in un-reset state permanently.
<br>
The INIT is a write-only field and read value will be always 0.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::RWEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">RWEN
</font><br><p> <font size="2">
Offset: 0x04  RTC Access Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[16]</td><td>RWENF</td><td><div style="word-wrap: break-word;"><b>RTC Register Access Enable Flag (Read Only)
</b><br>
0 = RTC register read/write Disabled.
<br>
1 = RTC register read/write Enabled.
<br>
Note: RWENF will be mask to 0 during RTCBUSY is 1, and first turn on RTCCKEN (CLK_APBCLK[1]) also.
<br>
</div></td></tr><tr><td>
[24]</td><td>RTCBUSY</td><td><div style="word-wrap: break-word;"><b>RTC Write Busy Flag
</b><br>
This bit indicates RTC registers are writable or not.
<br>
0: RTC registers are writable.
<br>
1: RTC registers can't write, RTC under Busy Status.
<br>
Note: RTCBUSY flag will be set when execute write RTC register command exceed 6 times within 1120 PCLK cycles.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::FREQADJ

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">FREQADJ
</font><br><p> <font size="2">
Offset: 0x08  RTC Frequency Compensation Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[21:0]</td><td>FREQADJ</td><td><div style="word-wrap: break-word;"><b>Frequency Compensation Register (M480)
</b><br>
User must to get actual LXT frequency for RTC application.
<br>
FCR = 0x200000 * (32768 / LXT frequency).
<br>
Note: This formula is suitable only when RTC clock source is from LXT, RTCSEL (CLK_CLKSEL3[8]) is 0.
<br>
</div></td></tr><tr><td>
[5:0]</td><td>FRACTION</td><td><div style="word-wrap: break-word;"><b>Fraction Part (M480LD)
</b><br>
Formula: FRACTION = (fraction part of detected value) X 64.
<br>
Note: Digit in FCR must be expressed as hexadecimal number.
<br>
</div></td></tr><tr><td>
[12:8]</td><td>INTEGER</td><td><div style="word-wrap: break-word;"><b>Integer Part (M480LD)
</b><br>
00000 = Integer part of detected value is 32752.
<br>
00001 = Integer part of detected value is 32753.
<br>
00010 = Integer part of detected value is 32754.
<br>
00011 = Integer part of detected value is 32755.
<br>
00100 = Integer part of detected value is 32756.
<br>
00101 = Integer part of detected value is 32757.
<br>
00110 = Integer part of detected value is 32758.
<br>
00111 = Integer part of detected value is 32759.
<br>
01000 = Integer part of detected value is 32760.
<br>
01001 = Integer part of detected value is 32761.
<br>
01010 = Integer part of detected value is 32762.
<br>
01011 = Integer part of detected value is 32763.
<br>
01100 = Integer part of detected value is 32764.
<br>
01101 = Integer part of detected value is 32765.
<br>
01110 = Integer part of detected value is 32766.
<br>
01111 = Integer part of detected value is 32767.
<br>
10000 = Integer part of detected value is 32768.
<br>
10001 = Integer part of detected value is 32769.
<br>
10010 = Integer part of detected value is 32770.
<br>
10011 = Integer part of detected value is 32771.
<br>
10100 = Integer part of detected value is 32772.
<br>
10101 = Integer part of detected value is 32773.
<br>
10110 = Integer part of detected value is 32774.
<br>
10111 = Integer part of detected value is 32775.
<br>
11000 = Integer part of detected value is 32776.
<br>
11001 = Integer part of detected value is 32777.
<br>
11010 = Integer part of detected value is 32778.
<br>
11011 = Integer part of detected value is 32779.
<br>
11100 = Integer part of detected value is 32780.
<br>
11101 = Integer part of detected value is 32781.
<br>
11110 = Integer part of detected value is 32782.
<br>
11111 = Integer part of detected value is 32783.
<br>
</div></td></tr><tr><td>
[31]</td><td>FCR_BUSY</td><td><div style="word-wrap: break-word;"><b>Frequency Compensation Register Write Operation Busy (Read Only) (M480LD)
</b><br>
0 = The new register write operation is acceptable.
<br>
1 = The last write operation is in progress and new register write operation prohibited.
<br>
Note: This bit is only used when DYN_COMP_EN(RTC_CLKFMT[16]) enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::TIME

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TIME
</font><br><p> <font size="2">
Offset: 0x0C  RTC Time Loading Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>SEC</td><td><div style="word-wrap: break-word;"><b>1-Sec Time Digit (0~9)
</b><br>
</div></td></tr><tr><td>
[6:4]</td><td>TENSEC</td><td><div style="word-wrap: break-word;"><b>10-Sec Time Digit (0~5)
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>MIN</td><td><div style="word-wrap: break-word;"><b>1-Min Time Digit (0~9)
</b><br>
</div></td></tr><tr><td>
[14:12]</td><td>TENMIN</td><td><div style="word-wrap: break-word;"><b>10-Min Time Digit (0~5)
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>HR</td><td><div style="word-wrap: break-word;"><b>1-Hour Time Digit (0~9)
</b><br>
</div></td></tr><tr><td>
[21:20]</td><td>TENHR</td><td><div style="word-wrap: break-word;"><b>10-Hour Time Digit (0~2)
</b><br>
When RTC runs as 12-hour time scale mode, RTC_TIME[21] (the high bit of TENHR[1:0]) means AM/PM indication
<br>
(If RTC_TIME[21] is 1, it indicates PM time message).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::CAL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAL
</font><br><p> <font size="2">
Offset: 0x10  RTC Calendar Loading Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>DAY</td><td><div style="word-wrap: break-word;"><b>1-Day Calendar Digit (0~9)
</b><br>
</div></td></tr><tr><td>
[5:4]</td><td>TENDAY</td><td><div style="word-wrap: break-word;"><b>10-Day Calendar Digit (0~3)
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>MON</td><td><div style="word-wrap: break-word;"><b>1-Month Calendar Digit (0~9)
</b><br>
</div></td></tr><tr><td>
[12]</td><td>TENMON</td><td><div style="word-wrap: break-word;"><b>10-Month Calendar Digit (0~1)
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>YEAR</td><td><div style="word-wrap: break-word;"><b>1-Year Calendar Digit (0~9)
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>TENYEAR</td><td><div style="word-wrap: break-word;"><b>10-Year Calendar Digit (0~9)
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::CLKFMT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKFMT
</font><br><p> <font size="2">
Offset: 0x14  RTC Time Scale Selection Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>24HEN</td><td><div style="word-wrap: break-word;"><b>24-hour / 12-hour Time Scale Selection
</b><br>
Indicates that RTC_TIME and RTC_TALM are in 24-hour time scale or 12-hour time scale
<br>
0 = 12-hour time scale with AM and PM indication selected.
<br>
1 = 24-hour time scale selected.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::WEEKDAY

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">WEEKDAY
</font><br><p> <font size="2">
Offset: 0x18  RTC Day of the Week Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2:0]</td><td>WEEKDAY</td><td><div style="word-wrap: break-word;"><b>Day of the Week Register
</b><br>
000 = Sunday.
<br>
001 = Monday.
<br>
010 = Tuesday.
<br>
011 = Wednesday.
<br>
100 = Thursday.
<br>
101 = Friday.
<br>
110 = Saturday.
<br>
111 = Reserved.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::TALM

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TALM
</font><br><p> <font size="2">
Offset: 0x1C  RTC Time Alarm Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>SEC</td><td><div style="word-wrap: break-word;"><b>1-Sec Time Digit of Alarm Setting (0~9)
</b><br>
</div></td></tr><tr><td>
[6:4]</td><td>TENSEC</td><td><div style="word-wrap: break-word;"><b>10-Sec Time Digit of Alarm Setting (0~5)
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>MIN</td><td><div style="word-wrap: break-word;"><b>1-Min Time Digit of Alarm Setting (0~9)
</b><br>
</div></td></tr><tr><td>
[14:12]</td><td>TENMIN</td><td><div style="word-wrap: break-word;"><b>10-Min Time Digit of Alarm Setting (0~5)
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>HR</td><td><div style="word-wrap: break-word;"><b>1-Hour Time Digit of Alarm Setting (0~9)
</b><br>
</div></td></tr><tr><td>
[21:20]</td><td>TENHR</td><td><div style="word-wrap: break-word;"><b>10-Hour Time Digit of Alarm Setting (0~2)
</b><br>
When RTC runs as 12-hour time scale mode, RTC_TIME[21] (the high bit of TENHR[1:0]) means AM/PM indication
<br>
(If RTC_TIME[21] is 1, it indicates PM time message).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::CALM

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CALM
</font><br><p> <font size="2">
Offset: 0x20  RTC Calendar Alarm Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>DAY</td><td><div style="word-wrap: break-word;"><b>1-Day Calendar Digit of Alarm Setting (0~9)
</b><br>
</div></td></tr><tr><td>
[5:4]</td><td>TENDAY</td><td><div style="word-wrap: break-word;"><b>10-Day Calendar Digit of Alarm Setting (0~3)
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>MON</td><td><div style="word-wrap: break-word;"><b>1-Month Calendar Digit of Alarm Setting (0~9)
</b><br>
</div></td></tr><tr><td>
[12]</td><td>TENMON</td><td><div style="word-wrap: break-word;"><b>10-Month Calendar Digit of Alarm Setting (0~1)
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>YEAR</td><td><div style="word-wrap: break-word;"><b>1-Year Calendar Digit of Alarm Setting (0~9)
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>TENYEAR</td><td><div style="word-wrap: break-word;"><b>10-Year Calendar Digit of Alarm Setting (0~9)
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::LEAPYEAR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">LEAPYEAR
</font><br><p> <font size="2">
Offset: 0x24  RTC Leap Year Indicator Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>LEAPYEAR</td><td><div style="word-wrap: break-word;"><b>Leap Year Indication Register (Read Only)
</b><br>
0 = This year is not a leap year.
<br>
1 = This year is leap year.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::INTEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTEN
</font><br><p> <font size="2">
Offset: 0x28  RTC Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ALMIEN</td><td><div style="word-wrap: break-word;"><b>Alarm Interrupt Enable Bit
</b><br>
Set ALMIEN to 1 can also enable chip wake-up function when RTC alarm interrupt event is generated.
<br>
0 = RTC Alarm interrupt Disabled.
<br>
1 = RTC Alarm interrupt Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>TICKIEN</td><td><div style="word-wrap: break-word;"><b>Time Tick Interrupt Enable Bit
</b><br>
Set TICKIEN to 1 can also enable chip wake-up function when RTC tick interrupt event is generated.
<br>
0 = RTC Time Tick interrupt Disabled.
<br>
1 = RTC Time Tick interrupt Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>TAMP0IEN</td><td><div style="word-wrap: break-word;"><b>Tamper 0 Interrupt Enable Bit
</b><br>
Set TAMP0IEN to 1 can also enable chip wake-up function when tamper 0 interrupt event is generated.
<br>
0 = Tamper 0 interrupt Disabled.
<br>
1 = Tamper 0 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[9]</td><td>TAMP1IEN</td><td><div style="word-wrap: break-word;"><b>Tamper 1 or Pair 0 Interrupt Enable Bit
</b><br>
Set TAMP1IEN to 1 can also enable chip wake-up function when tamper 1 interrupt event is generated.
<br>
0 = Tamper 1 or Pair 0 interrupt Disabled.
<br>
1 = Tamper 1 or Pair 0 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[10]</td><td>TAMP2IEN</td><td><div style="word-wrap: break-word;"><b>Tamper 2 Interrupt Enable Bit
</b><br>
Set TAMP2IEN to 1 can also enable chip wake-up function when tamper 2 interrupt event is generated.
<br>
0 = Tamper 2 interrupt Disabled.
<br>
1 = Tamper 2 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[11]</td><td>TAMP3IEN</td><td><div style="word-wrap: break-word;"><b>Tamper 3 or Pair 1 Interrupt Enable Bit
</b><br>
Set TAMP3IEN to 1 can also enable chip wake-up function when tamper 3 interrupt event is generated.
<br>
0 = Tamper 3 or Pair 1 interrupt Disabled.
<br>
1 = Tamper 3 or Pair 1 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[12]</td><td>TAMP4IEN</td><td><div style="word-wrap: break-word;"><b>Tamper 4 Interrupt Enable Bit
</b><br>
Set TAMP4IEN to 1 can also enable chip wake-up function when tamper 4 interrupt event is generated.
<br>
0 = Tamper 4 interrupt Disabled.
<br>
1 = Tamper 4 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[13]</td><td>TAMP5IEN</td><td><div style="word-wrap: break-word;"><b>Tamper 5 or Pair 2 Interrupt Enable Bit
</b><br>
Set TAMP5IEN to 1 can also enable chip wake-up function when tamper 5 interrupt event is generated.
<br>
0 = Tamper 5 or Pair 2 interrupt Disabled.
<br>
1 = Tamper 5 or Pair 2 interrupt Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::INTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTSTS
</font><br><p> <font size="2">
Offset: 0x2C  RTC Interrupt Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ALMIF</td><td><div style="word-wrap: break-word;"><b>RTC Alarm Interrupt Flag
</b><br>
0 = Alarm condition is not matched.
<br>
1 = Alarm condition is matched.
<br>
Note: Write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[1]</td><td>TICKIF</td><td><div style="word-wrap: break-word;"><b>RTC Time Tick Interrupt Flag
</b><br>
0 = Tick condition does not occur.
<br>
1 = Tick condition occur.
<br>
Note: Write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[8]</td><td>TAMP0IF</td><td><div style="word-wrap: break-word;"><b>Tamper 0 Interrupt Flag
</b><br>
This bit is set when TAMP0_PIN detected level non-equal TAMP0LV (RTC_TAMPCTL[9]).
<br>
0 = No Tamper 0 interrupt flag is generated.
<br>
1 = Tamper 0 interrupt flag is generated.
<br>
Note1: Write 1 to clear this bit.
<br>
Note2: Clear all TAPMxIF will clear RTC_TAMPTIME and RTC_TAMPCAL automatically.
<br>
</div></td></tr><tr><td>
[9]</td><td>TAMP1IF</td><td><div style="word-wrap: break-word;"><b>Tamper 1 or Pair 0 Interrupt Flag
</b><br>
This bit is set when TAMP1_PIN detected level non-equal TAMP1LV (RTC_TAMPCTL[13])
<br>
or TAMP0_PIN and TAMP1_PIN disconnected during DYNPR0EN (RTC_TAMPCTL[15]) is activated.
<br>
0 = No Tamper 1 or Pair 0 interrupt flag is generated.
<br>
1 = Tamper 1 or Pair 0 interrupt flag is generated.
<br>
Note1: Write 1 to clear this bit.
<br>
Note2: Clear all TAPMxIF will clear RTC_TAMPTIME and RTC_TAMPCAL automatically.
<br>
</div></td></tr><tr><td>
[10]</td><td>TAMP2IF</td><td><div style="word-wrap: break-word;"><b>Tamper 2 Interrupt Flag
</b><br>
This bit is set when TAMP2_PIN detected level non-equal TAMP2LV (RTC_TAMPCTL[17]).
<br>
0 = No Tamper 2 interrupt flag is generated.
<br>
1 = Tamper 2 interrupt flag is generated.
<br>
Note1: Write 1 to clear this bit.
<br>
Note2: Clear all TAPMxIF will clear RTC_TAMPTIME and RTC_TAMPCAL automatically.
<br>
</div></td></tr><tr><td>
[11]</td><td>TAMP3IF</td><td><div style="word-wrap: break-word;"><b>Tamper 3 or Pair 1 Interrupt Flag
</b><br>
This bit is set when TAMP3_PIN detected level non-equal TAMP3LV (RTC_TAMPCTL[21])
<br>
or TAMP2_PIN and TAMP3_PIN disconnected during DYNPR1EN (RTC_TAMPCTL[23]) is activated
<br>
or TAMP0_PIN and TAMP3_PIN disconnected during DYNPR1EN (RTC_TAMPCTL[23]) and DYN1ISS (RTC_TAMPCTL[0]) are activated.
<br>
0 = No Tamper 3 or Pair 1 interrupt flag is generated.
<br>
1 = Tamper 3 or Pair 1 interrupt flag is generated.
<br>
Note1: Write 1 to clear this bit.
<br>
Note2: Clear all TAPMxIF will clear RTC_TAMPTIME and RTC_TAMPCAL automatically.
<br>
</div></td></tr><tr><td>
[12]</td><td>TAMP4IF</td><td><div style="word-wrap: break-word;"><b>Tamper 4 Interrupt Flag
</b><br>
This bit is set when TAMP4_PIN detected level non-equal TAMP4LV (RTC_TAMPCTL[25]).
<br>
0 = No Tamper 4 interrupt flag is generated.
<br>
1 = Tamper 4 interrupt flag is generated.
<br>
Note1: Write 1 to clear this bit.
<br>
Note2: Clear all TAPMxIF will clear RTC_TAMPTIME and RTC_TAMPCAL automatically.
<br>
</div></td></tr><tr><td>
[13]</td><td>TAMP5IF</td><td><div style="word-wrap: break-word;"><b>Tamper 5 or Pair 2 Interrupt Flag
</b><br>
This bit is set when TAMP5_PIN detected level non-equal TAMP5LV (RTC_TAMPCTL[29])
<br>
or TAMP4_PIN and TAMP5_PIN disconnected during DYNPR2EN (RTC_TAMPCTL[31]) is activated
<br>
or TAMP0_PIN and TAMP5_PIN disconnected during DYNPR2EN (RTC_TAMPCTL[31]) and DYN2ISS (RTC_TAMPCTL[1]) are activated.
<br>
0 = No Tamper 5 or Pair 2 interrupt flag is generated.
<br>
1 = Tamper 5 or Pair 2 interrupt flag is generated.
<br>
Note1: Write 1 to clear this bit.
<br>
Note2: Clear all TAPMxIF will clear RTC_TAMPTIME and RTC_TAMPCAL automatically.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::TICK

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TICK
</font><br><p> <font size="2">
Offset: 0x30  RTC Time Tick Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2:0]</td><td>TICK</td><td><div style="word-wrap: break-word;"><b>Time Tick Register
</b><br>
These bits are used to select RTC time tick period for Periodic Time Tick Interrupt request.
<br>
000 = Time tick is 1 second.
<br>
001 = Time tick is 1/2 second.
<br>
010 = Time tick is 1/4 second.
<br>
011 = Time tick is 1/8 second.
<br>
100 = Time tick is 1/16 second.
<br>
101 = Time tick is 1/32 second.
<br>
110 = Time tick is 1/64 second.
<br>
111 = Time tick is 1/128 second.
<br>
Note: This register can be read back after the RTC register access enable bit RWENF (RTC_RWEN[16]) is active.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::TAMSK

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TAMSK
</font><br><p> <font size="2">
Offset: 0x34  RTC Time Alarm Mask Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>MSEC</td><td><div style="word-wrap: break-word;"><b>Mask 1-Sec Time Digit of Alarm Setting (0~9)
</b><br>
</div></td></tr><tr><td>
[1]</td><td>MTENSEC</td><td><div style="word-wrap: break-word;"><b>Mask 10-Sec Time Digit of Alarm Setting (0~5)
</b><br>
</div></td></tr><tr><td>
[2]</td><td>MMIN</td><td><div style="word-wrap: break-word;"><b>Mask 1-Min Time Digit of Alarm Setting (0~9)
</b><br>
</div></td></tr><tr><td>
[3]</td><td>MTENMIN</td><td><div style="word-wrap: break-word;"><b>Mask 10-Min Time Digit of Alarm Setting (0~5)
</b><br>
</div></td></tr><tr><td>
[4]</td><td>MHR</td><td><div style="word-wrap: break-word;"><b>Mask 1-Hour Time Digit of Alarm Setting (0~9)
</b><br>
</div></td></tr><tr><td>
[5]</td><td>MTENHR</td><td><div style="word-wrap: break-word;"><b>Mask 10-Hour Time Digit of Alarm Setting (0~2)
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::CAMSK

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAMSK
</font><br><p> <font size="2">
Offset: 0x38  RTC Calendar Alarm Mask Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>MDAY</td><td><div style="word-wrap: break-word;"><b>Mask 1-Day Calendar Digit of Alarm Setting (0~9)
</b><br>
</div></td></tr><tr><td>
[1]</td><td>MTENDAY</td><td><div style="word-wrap: break-word;"><b>Mask 10-Day Calendar Digit of Alarm Setting (0~3)
</b><br>
</div></td></tr><tr><td>
[2]</td><td>MMON</td><td><div style="word-wrap: break-word;"><b>Mask 1-Month Calendar Digit of Alarm Setting (0~9)
</b><br>
</div></td></tr><tr><td>
[3]</td><td>MTENMON</td><td><div style="word-wrap: break-word;"><b>Mask 10-Month Calendar Digit of Alarm Setting (0~1)
</b><br>
</div></td></tr><tr><td>
[4]</td><td>MYEAR</td><td><div style="word-wrap: break-word;"><b>Mask 1-Year Calendar Digit of Alarm Setting (0~9)
</b><br>
</div></td></tr><tr><td>
[5]</td><td>MTENYEAR</td><td><div style="word-wrap: break-word;"><b>Mask 10-Year Calendar Digit of Alarm Setting (0~9)
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::SPRCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SPRCTL
</font><br><p> <font size="2">
Offset: 0x3C  RTC Spare Functional Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2]</td><td>SPRRWEN</td><td><div style="word-wrap: break-word;"><b>Spare Register Enable Bit
</b><br>
0 = Spare register is Disabled.
<br>
1 = Spare register is Enabled.
<br>
Note: When spare register is disabled, RTC_SPR0 ~ RTC_SPR19 cannot be accessed.
<br>
</div></td></tr><tr><td>
[5]</td><td>SPRCSTS</td><td><div style="word-wrap: break-word;"><b>SPR Clear Flag
</b><br>
This bit indicates if the RTC_SPR0 ~RTC_SPR19 content is cleared when specify tamper event is detected.
<br>
0 = Spare register content is not cleared.
<br>
1 = Spare register content is cleared.
<br>
Writes 1 to clear this bit.
<br>
Note: This bit keep 1 when RTC_INTSTS[13:8] not equal zero.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::SPR[20]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SPR[20]
</font><br><p> <font size="2">
Offset: 0x40 ~ 0x8C  RTC Spare Register 0 ~ 19
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SPARE</td><td><div style="word-wrap: break-word;"><b>Spare Register
</b><br>
This field is used to store back-up information defined by user.
<br>
This field will be cleared by hardware automatically once a tamper pin event is detected.
<br>
Before storing back-up information in to RTC_SPRx register,
<br>
user should check REWNF (RTC_RWEN[16]) is enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::LXTCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">LXTCTL
</font><br><p> <font size="2">
Offset: 0x100  RTC 32.768 kHz Oscillator Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2:1]</td><td>GAIN</td><td><div style="word-wrap: break-word;"><b>Oscillator Gain Option
</b><br>
User can select oscillator gain according to crystal external loading and operating temperature range
<br>
The larger gain value corresponding to stronger driving capability and higher power consumption.
<br>
00 = L0 mode.
<br>
01 = L1 mode.
<br>
10 = L2 mode.
<br>
11 = L3 mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::GPIOCTL0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPIOCTL0
</font><br><p> <font size="2">
Offset: 0x104  RTC GPIO Control 0 Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1:0]</td><td>OPMODE0</td><td><div style="word-wrap: break-word;"><b>IO Operation Mode
</b><br>
00 = PF.4 is input only mode, without pull-up resistor.
<br>
01 = PF.4 is output push pull mode.
<br>
10 = PF.4 is open drain mode.
<br>
11 = PF.4 is quasi-bidirectional mode with internal pull up.
<br>
</div></td></tr><tr><td>
[2]</td><td>DOUT0</td><td><div style="word-wrap: break-word;"><b>IO Output Data
</b><br>
0 = PF.4 output low.
<br>
1 = PF.4 output high.
<br>
</div></td></tr><tr><td>
[3]</td><td>CTLSEL0</td><td><div style="word-wrap: break-word;"><b>IO Pin State Backup Selection
</b><br>
When low speed 32 kHz oscillator is disabled, PF.4 pin (X32KO pin) can be used as GPIO function
<br>
User can program CTLSEL0 to decide PF.4 I/O function is controlled by system power domain GPIO module or
<br>
VBAT power domain RTC_GPIOCTL0 control register.
<br>
0 = PF.4 pin I/O function is controlled by GPIO module.
<br>
Hardware auto becomes CTLSEL0 = 1 when system power is turned off.
<br>
1 = PF.4 pin I/O function is controlled by VBAT power domain.
<br>
PF.4 pin function and I/O status are controlled by OPMODE0[1:0] and DOUT0 after CTLSEL0 is set to 1.
<br>
Note: CTLSEL0 will automatically be set by hardware to 1 when system power is off and INIT[0] (RTC_INIT[0]) is 1.
<br>
</div></td></tr><tr><td>
[5:4]</td><td>PUSEL0</td><td><div style="word-wrap: break-word;"><b>IO Pull-up and Pull-down Enable
</b><br>
Determine PF.4 I/O pull-up or pull-down.
<br>
00 = PF.4 pull-up and pull-up disable.
<br>
01 = PF.4 pull-down enable.
<br>
10 = PF.4 pull-up enable.
<br>
11 = PF.4 pull-up and pull-up disable.
<br>
Note:
<br>
Basically, the pull-up control and pull-down control has following behavior limitation.
<br>
The independent pull-up control register only valid when OPMODE0 set as input tri-state and open-drain mode.
<br>
The independent pull-down control register only valid when OPMODE0 set as input tri-state mode.
<br>
</div></td></tr><tr><td>
[9:8]</td><td>OPMODE1</td><td><div style="word-wrap: break-word;"><b>IO Operation Mode
</b><br>
00 = PF.5 is input only mode, without pull-up resistor.
<br>
01 = PF.5 is output push pull mode.
<br>
10 = PF.5 is open drain mode.
<br>
11 = PF.5 is quasi-bidirectional mode with internal pull up.
<br>
</div></td></tr><tr><td>
[10]</td><td>DOUT1</td><td><div style="word-wrap: break-word;"><b>IO Output Data
</b><br>
0 = PF.5 output low.
<br>
1 = PF.5 output high.
<br>
</div></td></tr><tr><td>
[11]</td><td>CTLSEL1</td><td><div style="word-wrap: break-word;"><b>IO Pin State Backup Selection
</b><br>
When low speed 32 kHz oscillator is disabled, PF.5 pin (X32KI pin) can be used as GPIO function
<br>
User can program CTLSEL1 to decide PF.5 I/O function is controlled by system power domain GPIO module or
<br>
VBAT power domain RTC_GPIOCTL0 control register.
<br>
0 = PF.5 pin I/O function is controlled by GPIO module.
<br>
Hardware auto becomes CTLSEL1 = 1 when system power is turned off.
<br>
1 = PF.5 pin I/O function is controlled by VBAT power domain.
<br>
PF.5 pin function and I/O status are controlled by OPMODE1[1:0] and DOUT1 after CTLSEL1 is set to 1.
<br>
Note: CTLSEL1 will automatically be set by hardware to 1 when system power is off and INIT[0] (RTC_INIT[0]) is 1.
<br>
</div></td></tr><tr><td>
[13:12]</td><td>PUSEL1</td><td><div style="word-wrap: break-word;"><b>IO Pull-up and Pull-down Enable
</b><br>
Determine PF.5 I/O pull-up or pull-down.
<br>
00 = PF.5 pull-up and pull-up disable.
<br>
01 = PF.5 pull-down enable.
<br>
10 = PF.5 pull-up enable.
<br>
11 = PF.5 pull-up and pull-up disable.
<br>
Note:
<br>
Basically, the pull-up control and pull-down control has following behavior limitation.
<br>
The independent pull-up control register only valid when OPMODE1 set as input tri-state and open-drain mode.
<br>
The independent pull-down control register only valid when OPMODE1 set as input tri-state mode.
<br>
</div></td></tr><tr><td>
[17:16]</td><td>OPMODE2</td><td><div style="word-wrap: break-word;"><b>IO Operation Mode
</b><br>
00 = PF.6 is input only mode, without pull-up resistor.
<br>
01 = PF.6 is output push pull mode.
<br>
10 = PF.6 is open drain mode.
<br>
11 = PF.6 is quasi-bidirectional mode with internal pull up.
<br>
</div></td></tr><tr><td>
[18]</td><td>DOUT2</td><td><div style="word-wrap: break-word;"><b>IO Output Data
</b><br>
0 = PF.6 output low.
<br>
1 = PF.6 output high.
<br>
</div></td></tr><tr><td>
[19]</td><td>CTLSEL2</td><td><div style="word-wrap: break-word;"><b>IO Pin State Backup Selection
</b><br>
When TAMP0EN is disabled, PF.6 pin (TAMPER0 pin) can be used as GPIO function
<br>
User can program CTLSEL2 to decide PF.6 I/O function is controlled by system power domain GPIO module or
<br>
VBAT power domain RTC_GPIOCTL0 control register.
<br>
0 = PF.6 pin I/O function is controlled by GPIO module.
<br>
Hardware auto becomes CTLSEL2 = 1 when system power is turned off.
<br>
1 = PF.6 pin I/O function is controlled by VBAT power domain.
<br>
PF.6 pin function and I/O status are controlled by OPMODE2[1:0] and DOUT2 after CTLSEL2 is set to 1.
<br>
Note: CTLSEL2 will automatically be set by hardware to 1 when system power is off and INIT[0] (RTC_INIT[0]) is 1.
<br>
</div></td></tr><tr><td>
[21:20]</td><td>PUSEL2</td><td><div style="word-wrap: break-word;"><b>IO Pull-up and Pull-down Enable
</b><br>
Determine PF.6 I/O pull-up or pull-down.
<br>
00 = PF.6 pull-up and pull-up disable.
<br>
01 = PF.6 pull-down enable.
<br>
10 = PF.6 pull-up enable.
<br>
11 = PF.6 pull-up and pull-up disable.
<br>
Note1:
<br>
Basically, the pull-up control and pull-down control has following behavior limitation.
<br>
The independent pull-up control register only valid when OPMODE2 set as input tri-state and open-drain mode.
<br>
The independent pull-down control register only valid when OPMODE2 set as input tri-state mode.
<br>
</div></td></tr><tr><td>
[25:24]</td><td>OPMODE3</td><td><div style="word-wrap: break-word;"><b>IO Operation Mode
</b><br>
00 = PF.7 is input only mode, without pull-up resistor.
<br>
01 = PF.7 is output push pull mode.
<br>
10 = PF.7 is open drain mode.
<br>
11 = PF.7 is quasi-bidirectional mode.
<br>
</div></td></tr><tr><td>
[26]</td><td>DOUT3</td><td><div style="word-wrap: break-word;"><b>IO Output Data
</b><br>
0 = PF.7 output low.
<br>
1 = PF.7 output high.
<br>
</div></td></tr><tr><td>
[27]</td><td>CTLSEL3</td><td><div style="word-wrap: break-word;"><b>IO Pin State Backup Selection
</b><br>
When TAMP1EN is disabled, PF.7 pin (TAMPER1 pin) can be used as GPIO function
<br>
User can program CTLSEL3 to decide PF.7 I/O function is controlled by system power domain GPIO module or
<br>
VBAT power domain RTC_GPIOCTL0 control register.
<br>
0 = PF.7 pin I/O function is controlled by GPIO module.
<br>
Hardware auto becomes CTLSEL3 = 1 when system power is turned off.
<br>
1 = PF.7 pin I/O function is controlled by VBAT power domain.
<br>
PF.7 pin function and I/O status are controlled by OPMODE3[1:0] and DOUT3 after CTLSEL3 is set to 1.
<br>
Note: CTLSEL3 will automatically be set by hardware to 1 when system power is off and RTC_INIT[0] (RTC Active Status) is 1.
<br>
</div></td></tr><tr><td>
[29:28]</td><td>PUSEL3</td><td><div style="word-wrap: break-word;"><b>IO Pull-up and Pull-down Enable
</b><br>
Determine PF.7 I/O pull-up or pull-down.
<br>
00 = PF.7 pull-up and pull-down disable.
<br>
01 = PF.7 pull-down enable.
<br>
10 = PF.7 pull-up enable.
<br>
11 = PF.7 pull-up and pull-down disable.
<br>
Note:
<br>
Basically, the pull-up control and pull-down control has following behavior limitation.
<br>
The independent pull-up control register only valid when OPMODE3 set as input tri-state and open-drain mode.
<br>
The independent pull-down control register only valid when OPMODE3 set as input tri-state mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::GPIOCTL1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPIOCTL1
</font><br><p> <font size="2">
Offset: 0x108  RTC GPIO Control 1 Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1:0]</td><td>OPMODE4</td><td><div style="word-wrap: break-word;"><b>IO Operation Mode
</b><br>
00 = PF.8 is input only mode, without pull-up resistor.
<br>
01 = PF.8 is output push pull mode.
<br>
10 = PF.8 is open drain mode.
<br>
11 = PF.8 is quasi-bidirectional mode.
<br>
</div></td></tr><tr><td>
[2]</td><td>DOUT4</td><td><div style="word-wrap: break-word;"><b>IO Output Data
</b><br>
0 = PF.8 output low.
<br>
1 = PF.8 output high.
<br>
</div></td></tr><tr><td>
[3]</td><td>CTLSEL4</td><td><div style="word-wrap: break-word;"><b>IO Pin State Backup Selection
</b><br>
When TAMP2EN is disabled, PF.8 pin (TAMPER2 pin) can be used as GPIO function
<br>
User can program CTLSEL4 to decide PF.8 I/O function is controlled by system power domain GPIO module or
<br>
VBAT power domain RTC_GPIOCTL1 control register.
<br>
0 = PF.8 pin I/O function is controlled by GPIO module.
<br>
Hardware auto becomes CTLSEL4 = 1 when system power is turned off.
<br>
1 = PF.8 pin I/O function is controlled by VBAT power domain.
<br>
PF.8 pin function and I/O status are controlled by OPMODE4[1:0] and DOUT4 after CTLSEL4 is set to 1.
<br>
Note: CTLSEL4 will automatically be set by hardware to 1 when system power is off and RTC_INIT[0] (RTC Active Status) is 1.
<br>
</div></td></tr><tr><td>
[5:4]</td><td>PUSEL4</td><td><div style="word-wrap: break-word;"><b>IO Pull-up and Pull-down Enable
</b><br>
Determine PF.8 I/O pull-up or pull-down.
<br>
00 = PF.8 pull-up and pull-down disable.
<br>
01 = PF.8 pull-down enable.
<br>
10 = PF.8 pull-up enable.
<br>
11 = PF.8 pull-up and pull-down disable.
<br>
Note:
<br>
Basically, the pull-up control and pull-down control has following behavior limitation.
<br>
The independent pull-up control register only valid when OPMODE4 set as input tri-state and open-drain mode.
<br>
The independent pull-down control register only valid when OPMODE4 set as input tri-state mode.
<br>
</div></td></tr><tr><td>
[9:8]</td><td>OPMODE5</td><td><div style="word-wrap: break-word;"><b>IO Operation Mode
</b><br>
00 = PF.9 is input only mode, without pull-up resistor.
<br>
01 = PF.9 is output push pull mode.
<br>
10 = PF.9 is open drain mode.
<br>
11 = PF.9 is quasi-bidirectional mode.
<br>
</div></td></tr><tr><td>
[10]</td><td>DOUT5</td><td><div style="word-wrap: break-word;"><b>IO Output Data
</b><br>
0 = PF.9 output low.
<br>
1 = PF.9 output high.
<br>
</div></td></tr><tr><td>
[11]</td><td>CTLSEL5</td><td><div style="word-wrap: break-word;"><b>IO Pin State Backup Selection
</b><br>
When TAMP3EN is disabled, PF.9 pin (TAMPER3 pin) can be used as GPIO function
<br>
User can program CTLSEL5 to decide PF.9 I/O function is controlled by system power domain GPIO module or
<br>
VBAT power domain RTC_GPIOCTL1 control register.
<br>
0 = PF.9 pin I/O function is controlled by GPIO module.
<br>
Hardware auto becomes CTLSEL5 = 1 when system power is turned off.
<br>
1 = PF.9 pin I/O function is controlled by VBAT power domain.
<br>
PF.9 pin function and I/O status are controlled by OPMODE5[1:0] and DOUT5 after CTLSEL5 is set to 1.
<br>
Note: CTLSEL5 will automatically be set by hardware to 1 when system power is off and INIT[0] (RTC_INIT[0]) is 1.
<br>
</div></td></tr><tr><td>
[13:12]</td><td>PUSEL5</td><td><div style="word-wrap: break-word;"><b>IO Pull-up and Pull-down Enable
</b><br>
Determine PF.9 I/O pull-up or pull-down.
<br>
00 = PF.9 pull-up and pull-down disable.
<br>
01 = PF.9 pull-down enable.
<br>
10 = PF.9 pull-up enable.
<br>
11 = PF.9 pull-up and pull-down disable.
<br>
Note:
<br>
Basically, the pull-up control and pull-down control has following behavior limitation.
<br>
The independent pull-up control register only valid when OPMODE5 set as input tri-state and open-drain mode.
<br>
The independent pull-down control register only valid when OPMODE5 set as input tri-state mode.
<br>
</div></td></tr><tr><td>
[17:16]</td><td>OPMODE6</td><td><div style="word-wrap: break-word;"><b>IO Operation Mode
</b><br>
00 = PF.10 is input only mode, without pull-up resistor.
<br>
01 = PF.10 is output push pull mode.
<br>
10 = PF.10 is open drain mode.
<br>
11 = PF.10 is quasi-bidirectional mode.
<br>
</div></td></tr><tr><td>
[18]</td><td>DOUT6</td><td><div style="word-wrap: break-word;"><b>IO Output Data
</b><br>
0 = PF.10 output low.
<br>
1 = PF.10 output high.
<br>
</div></td></tr><tr><td>
[19]</td><td>CTLSEL6</td><td><div style="word-wrap: break-word;"><b>IO Pin State Backup Selection
</b><br>
When TAMP4EN is disabled, PF.10 pin (TAMPER4 pin) can be used as GPIO function
<br>
User can program CTLSEL6 to decide PF.10 I/O function is controlled by system power domain GPIO module or
<br>
VBAT power domain RTC_GPIOCTL1 control register.
<br>
0 = PF.10 pin I/O function is controlled by GPIO module.
<br>
Hardware auto becomes CTLSEL6 = 1 when system power is turned off.
<br>
1 = PF.10 pin I/O function is controlled by VBAT power domain.
<br>
PF.10 pin function and I/O status are controlled by OPMODE6[1:0] and DOUT6 after CTLSEL6 is set to 1.
<br>
Note: CTLSEL6 will automatically be set by hardware to 1 when system power is off and INIT[0] (RTC_INIT[0]) is 1.
<br>
</div></td></tr><tr><td>
[21:20]</td><td>PUSEL6</td><td><div style="word-wrap: break-word;"><b>IO Pull-up and Pull-down Enable
</b><br>
Determine PF.10 I/O pull-up or pull-down.
<br>
00 = PF.10 pull-up and pull-down disable.
<br>
01 = PF.10 pull-down enable.
<br>
10 = PF.10 pull-up enable.
<br>
11 = PF.10 pull-up and pull-down disable.
<br>
Note:
<br>
Basically, the pull-up control and pull-down control has following behavior limitation.
<br>
The independent pull-up control register only valid when OPMODE6 set as input tri-state and open-drain mode.
<br>
The independent pull-down control register only valid when OPMODE6 set as input tri-state mode.
<br>
</div></td></tr><tr><td>
[25:24]</td><td>OPMODE7</td><td><div style="word-wrap: break-word;"><b>IO Operation Mode
</b><br>
00 = PF.11 is input only mode, without pull-up resistor.
<br>
01 = PF.11 is output push pull mode.
<br>
10 = PF.11 is open drain mode.
<br>
11 = PF.11 is quasi-bidirectional mode.
<br>
</div></td></tr><tr><td>
[26]</td><td>DOUT7</td><td><div style="word-wrap: break-word;"><b>IO Output Data
</b><br>
0 = PF.11 output low.
<br>
1 = PF.11 output high.
<br>
</div></td></tr><tr><td>
[27]</td><td>CTLSEL7</td><td><div style="word-wrap: break-word;"><b>IO Pin State Backup Selection
</b><br>
When TAMP5EN is disabled, PF.11 pin (TAMPER5 pin) can be used as GPIO function
<br>
User can program CTLSEL7 to decide PF.11 I/O function is controlled by system power domain GPIO module or
<br>
VBAT power domain RTC_GPIOCTL1 control register.
<br>
0 = PF.11 pin I/O function is controlled by GPIO module.
<br>
Hardware auto becomes CTLSEL7 = 1 when system power is turned off.
<br>
1 = PF.11 pin I/O function is controlled by VBAT power domain.
<br>
PF.11 pin function and I/O status are controlled by OPMODE7[1:0] and DOUT7 after CTLSEL7 is set to 1.
<br>
Note: CTLSEL7 will automatically be set by hardware to 1 when system power is off and INIT[0] (RTC_INIT[0]) is 1.
<br>
</div></td></tr><tr><td>
[29:28]</td><td>PUSEL7</td><td><div style="word-wrap: break-word;"><b>IO Pull-up and Pull-down Enable
</b><br>
Determine PF.11 I/O pull-up or pull-down.
<br>
00 = PF.11 pull-up and pull-down disable.
<br>
01 = PF.11 pull-down enable.
<br>
10 = PF.11 pull-up enable.
<br>
11 = PF.11 pull-up and pull-down disable.
<br>
Note:
<br>
Basically, the pull-up control and pull-down control has following behavior limitation.
<br>
The independent pull-up control register only valid when OPMODE7 set as input tri-state and open-drain mode.
<br>
The independent pull-down control register only valid when OPMODE7 set as input tri-state mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::DSTCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DSTCTL
</font><br><p> <font size="2">
Offset: 0x110  RTC Daylight Saving Time Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ADDHR</td><td><div style="word-wrap: break-word;"><b>Add 1 Hour
</b><br>
0 = No effect.
<br>
1 = Indicates RTC hour digit has been added one hour for summer time change.
<br>
</div></td></tr><tr><td>
[1]</td><td>SUBHR</td><td><div style="word-wrap: break-word;"><b>Subtract 1 Hour
</b><br>
0 = No effect.
<br>
1 = Indicates RTC hour digit has been subtracted one hour for winter time change.
<br>
</div></td></tr><tr><td>
[2]</td><td>DSBAK</td><td><div style="word-wrap: break-word;"><b>Daylight Saving Back
</b><br>
0= Normal mode.
<br>
1= Daylight saving mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::TAMPCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TAMPCTL
</font><br><p> <font size="2">
Offset: 0x120  RTC Tamper Pin Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>DYN1ISS</td><td><div style="word-wrap: break-word;"><b>Dynamic Pair 1 Input Source Select
</b><br>
This bit determine Tamper 3 input is from Tamper 2 or Tamper 0 in dynamic mode.
<br>
0 = Tamper input is from Tamper 2.
<br>
1 = Tamper input is from Tamper 0.
<br>
Note: This bit has effect only when DYNPR1EN (RTC_TAMPCTL[16]) and DYNPR0EN (RTC_TAMPCTL[15]) are set
<br>
</div></td></tr><tr><td>
[1]</td><td>DYN2ISS</td><td><div style="word-wrap: break-word;"><b>Dynamic Pair 2 Input Source Select
</b><br>
This bit determine Tamper 5 input is from Tamper 4 or Tamper 0 in dynamic mode.
<br>
0 = Tamper input is from Tamper 4.
<br>
1 = Tamper input is from Tamper 0.
<br>
Note: This bit has effect only when DYNPR2EN (RTC_TAMPCTL[24]) and DYNPR0EN (RTC_TAMPCTL[15]) are set
<br>
</div></td></tr><tr><td>
[3:2]</td><td>DYNSRC</td><td><div style="word-wrap: break-word;"><b>Dynamic Reference Pattern
</b><br>
This fields determine the new reference pattern when current pattern run out in dynamic pair mode.
<br>
00 or 10 = The new reference pattern is generated by random number generator when the reference pattern run out.
<br>
01 = The new reference pattern is repeated previous random value when the reference pattern run out.
<br>
11 = The new reference pattern is repeated from SEED (RTC_TAMPSEED[31:0]) when the reference pattern run out.
<br>
Note: After revise this bit, the SEEDRLD (RTC_TAMPCTL[4]) should be set.
<br>
</div></td></tr><tr><td>
[4]</td><td>SEEDRLD</td><td><div style="word-wrap: break-word;"><b>Reload New Seed for PRNG Engine
</b><br>
Setting this bit, the tamper configuration will be reload.
<br>
0 = Generating key based on the current seed.
<br>
1 = Reload new seed.
<br>
Note: Before set this bit, the tamper configuration should be set to complete.
<br>
</div></td></tr><tr><td>
[7:5]</td><td>DYNRATE</td><td><div style="word-wrap: break-word;"><b>Dynamic Change Rate
</b><br>
This item is choice the dynamic tamper output change rate.
<br>
000 = 210 * RTC_CLK.
<br>
001 = 211 * RTC_CLK.
<br>
010 = 212 * RTC_CLK.
<br>
011 = 213 * RTC_CLK.
<br>
100 = 214 * RTC_CLK.
<br>
101 = 215 * RTC_CLK.
<br>
110 = 216 * RTC_CLK.
<br>
111 = 217 * RTC_CLK.
<br>
Note: After revise this field, set SEEDRLD (RTC_TAMPCTL[4]) can reload change rate immediately.
<br>
</div></td></tr><tr><td>
[8]</td><td>TAMP0EN</td><td><div style="word-wrap: break-word;"><b>Tamper0 Detect Enable Bit
</b><br>
0 = Tamper 0 detect Disabled.
<br>
1 = Tamper 0 detect Enabled.
<br>
Note1: The reference is RTC-clock . Tamper detector need sync 2 ~ 3 RTC-clock.
<br>
</div></td></tr><tr><td>
[9]</td><td>TAMP0LV</td><td><div style="word-wrap: break-word;"><b>Tamper 0 Level
</b><br>
This bit depend on level attribute of tamper pin for static tamper detection.
<br>
0 = Detect voltage level is low.
<br>
1 = Detect voltage level is high.
<br>
</div></td></tr><tr><td>
[10]</td><td>TAMP0DBEN</td><td><div style="word-wrap: break-word;"><b>Tamper 0 De-bounce Enable Bit
</b><br>
0 = Tamper 0 de-bounce Disabled.
<br>
1 = Tamper 0 de-bounce Enabled.
<br>
</div></td></tr><tr><td>
[12]</td><td>TAMP1EN</td><td><div style="word-wrap: break-word;"><b>Tamper 1 Detect Enable Bit
</b><br>
0 = Tamper 1 detect Disabled.
<br>
1 = Tamper 1 detect Enabled.
<br>
Note1: The reference is RTC-clock . Tamper detector need sync 2 ~ 3 RTC-clock.
<br>
</div></td></tr><tr><td>
[13]</td><td>TAMP1LV</td><td><div style="word-wrap: break-word;"><b>Tamper 1 Level
</b><br>
This bit depend on level attribute of tamper pin for static tamper detection.
<br>
0 = Detect voltage level is low.
<br>
1 = Detect voltage level is high.
<br>
</div></td></tr><tr><td>
[14]</td><td>TAMP1DBEN</td><td><div style="word-wrap: break-word;"><b>Tamper 1 De-bounce Enable Bit
</b><br>
0 = Tamper 1 de-bounce Disabled.
<br>
1 = Tamper 1 de-bounce Enabled.
<br>
</div></td></tr><tr><td>
[15]</td><td>DYNPR0EN</td><td><div style="word-wrap: break-word;"><b>Dynamic Pair 0 Enable Bit
</b><br>
0 = Static detect.
<br>
1 = Dynamic detect.
<br>
</div></td></tr><tr><td>
[16]</td><td>TAMP2EN</td><td><div style="word-wrap: break-word;"><b>Tamper 2 Detect Enable Bit
</b><br>
0 = Tamper 2 detect Disabled.
<br>
1 = Tamper 2 detect Enabled.
<br>
Note1: The reference is RTC-clock . Tamper detector need sync 2 ~ 3 RTC-clock.
<br>
</div></td></tr><tr><td>
[17]</td><td>TAMP2LV</td><td><div style="word-wrap: break-word;"><b>Tamper 2 Level
</b><br>
This bit depend on level attribute of tamper pin for static tamper detection.
<br>
0 = Detect voltage level is low.
<br>
1 = Detect voltage level is high.
<br>
</div></td></tr><tr><td>
[18]</td><td>TAMP2DBEN</td><td><div style="word-wrap: break-word;"><b>Tamper 2 De-bounce Enable Bit
</b><br>
0 = Tamper 2 de-bounce Disabled.
<br>
1 = Tamper 2 de-bounce Enabled.
<br>
</div></td></tr><tr><td>
[20]</td><td>TAMP3EN</td><td><div style="word-wrap: break-word;"><b>Tamper 3 Detect Enable Bit
</b><br>
0 = Tamper 3 detect Disabled.
<br>
1 = Tamper 3 detect Enabled.
<br>
Note1: The reference is RTC-clock . Tamper detector need sync 2 ~ 3 RTC-clock.
<br>
</div></td></tr><tr><td>
[21]</td><td>TAMP3LV</td><td><div style="word-wrap: break-word;"><b>Tamper 3 Level
</b><br>
This bit depend on level attribute of tamper pin for static tamper detection.
<br>
0 = Detect voltage level is low.
<br>
1 = Detect voltage level is high.
<br>
</div></td></tr><tr><td>
[22]</td><td>TAMP3DBEN</td><td><div style="word-wrap: break-word;"><b>Tamper 3 De-bounce Enable Bit
</b><br>
0 = Tamper 3 de-bounce Disabled.
<br>
1 = Tamper 3 de-bounce Enabled.
<br>
</div></td></tr><tr><td>
[23]</td><td>DYNPR1EN</td><td><div style="word-wrap: break-word;"><b>Dynamic Pair 1 Enable Bit
</b><br>
0 = Static detect.
<br>
1 = Dynamic detect.
<br>
</div></td></tr><tr><td>
[24]</td><td>TAMP4EN</td><td><div style="word-wrap: break-word;"><b>Tamper4 Detect Enable Bit
</b><br>
0 = Tamper 4 detect Disabled.
<br>
1 = Tamper 4 detect Enabled.
<br>
Note1: The reference is RTC-clock . Tamper detector need sync 2 ~ 3 RTC-clock.
<br>
</div></td></tr><tr><td>
[25]</td><td>TAMP4LV</td><td><div style="word-wrap: break-word;"><b>Tamper 4 Level
</b><br>
This bit depends on level attribute of tamper pin for static tamper detection.
<br>
0 = Detect voltage level is low.
<br>
1 = Detect voltage level is high.
<br>
</div></td></tr><tr><td>
[26]</td><td>TAMP4DBEN</td><td><div style="word-wrap: break-word;"><b>Tamper 4 De-bounce Enable Bit
</b><br>
0 = Tamper 4 de-bounce Disabled.
<br>
1 = Tamper 4 de-bounce Enabled.
<br>
</div></td></tr><tr><td>
[28]</td><td>TAMP5EN</td><td><div style="word-wrap: break-word;"><b>Tamper 5 Detect Enable Bit
</b><br>
0 = Tamper 5 detect Disabled.
<br>
1 = Tamper 5 detect Enabled.
<br>
Note1: The reference is RTC-clock . Tamper detector need sync 2 ~ 3 RTC-clock.
<br>
</div></td></tr><tr><td>
[29]</td><td>TAMP5LV</td><td><div style="word-wrap: break-word;"><b>Tamper 5 Level
</b><br>
This bit depend on level attribute of tamper pin for static tamper detection.
<br>
0 = Detect voltage level is low.
<br>
1 = Detect voltage level is high.
<br>
</div></td></tr><tr><td>
[30]</td><td>TAMP5DBEN</td><td><div style="word-wrap: break-word;"><b>Tamper 5 De-bounce Enable Bit
</b><br>
0 = Tamper 5 de-bounce Disabled.
<br>
1 = Tamper 5 de-bounce Enabled.
<br>
</div></td></tr><tr><td>
[31]</td><td>DYNPR2EN</td><td><div style="word-wrap: break-word;"><b>Dynamic Pair 2 Enable Bit
</b><br>
0 = Static detect.
<br>
1 = Dynamic detect.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::TAMPSEED

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TAMPSEED
</font><br><p> <font size="2">
Offset: 0x128  RTC Tamper Dynamic Seed Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SEED</td><td><div style="word-wrap: break-word;"><b>Seed Value
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::TAMPTIME

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TAMPTIME
</font><br><p> <font size="2">
Offset: 0x130  RTC Tamper Time Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>SEC</td><td><div style="word-wrap: break-word;"><b>1-Sec Time Digit of TAMPER Time (0~9)
</b><br>
</div></td></tr><tr><td>
[6:4]</td><td>TENSEC</td><td><div style="word-wrap: break-word;"><b>10-Sec Time Digit of TAMPER Time (0~5)
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>MIN</td><td><div style="word-wrap: break-word;"><b>1-Min Time Digit of TAMPER Time (0~9)
</b><br>
</div></td></tr><tr><td>
[14:12]</td><td>TENMIN</td><td><div style="word-wrap: break-word;"><b>10-Min Time Digit of TAMPER Time (0~5)
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>HR</td><td><div style="word-wrap: break-word;"><b>1-Hour Time Digit of TAMPER Time (0~9)
</b><br>
</div></td></tr><tr><td>
[21:20]</td><td>TENHR</td><td><div style="word-wrap: break-word;"><b>10-Hour Time Digit of TAMPER Time (0~2)
</b><br>
Note: 24-hour time scale only.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var RTC_T::TAMPCAL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TAMPCAL
</font><br><p> <font size="2">
Offset: 0x134  RTC Tamper Calendar Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>DAY</td><td><div style="word-wrap: break-word;"><b>1-Day Calendar Digit of TAMPER Calendar (0~9)
</b><br>
</div></td></tr><tr><td>
[5:4]</td><td>TENDAY</td><td><div style="word-wrap: break-word;"><b>10-Day Calendar Digit of TAMPER Calendar (0~3)
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>MON</td><td><div style="word-wrap: break-word;"><b>1-Month Calendar Digit of TAMPER Calendar (0~9)
</b><br>
</div></td></tr><tr><td>
[12]</td><td>TENMON</td><td><div style="word-wrap: break-word;"><b>10-Month Calendar Digit of TAMPER Calendar (0~1)
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>YEAR</td><td><div style="word-wrap: break-word;"><b>1-Year Calendar Digit of TAMPER Calendar (0~9)
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>TENYEAR</td><td><div style="word-wrap: break-word;"><b>10-Year Calendar Digit of TAMPER Calendar (0~9)
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t INIT;                  /*!< [0x0000] RTC Initiation Register                                          */
    __IO uint32_t RWEN;                  /*!< [0x0004] RTC Access Enable Register                                       */
    __IO uint32_t FREQADJ;               /*!< [0x0008] RTC Frequency Compensation Register                              */
    __IO uint32_t TIME;                  /*!< [0x000c] RTC Time Loading Register                                        */
    __IO uint32_t CAL;                   /*!< [0x0010] RTC Calendar Loading Register                                    */
    __IO uint32_t CLKFMT;                /*!< [0x0014] RTC Time Scale Selection Register                                */
    __IO uint32_t WEEKDAY;               /*!< [0x0018] RTC Day of the Week Register                                     */
    __IO uint32_t TALM;                  /*!< [0x001c] RTC Time Alarm Register                                          */
    __IO uint32_t CALM;                  /*!< [0x0020] RTC Calendar Alarm Register                                      */
    __I  uint32_t LEAPYEAR;              /*!< [0x0024] RTC Leap Year Indicator Register                                 */
    __IO uint32_t INTEN;                 /*!< [0x0028] RTC Interrupt Enable Register                                    */
    __IO uint32_t INTSTS;                /*!< [0x002c] RTC Interrupt Status Register                                    */
    __IO uint32_t TICK;                  /*!< [0x0030] RTC Time Tick Register                                           */
    __IO uint32_t TAMSK;                 /*!< [0x0034] RTC Time Alarm Mask Register                                     */
    __IO uint32_t CAMSK;                 /*!< [0x0038] RTC Calendar Alarm Mask Register                                 */
    __IO uint32_t SPRCTL;                /*!< [0x003c] RTC Spare Functional Control Register                            */
    __IO uint32_t SPR[20];               /*!< [0x0040] ~ [0x008c] RTC Spare Register 0 ~ 19                             */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[28];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t LXTCTL;                /*!< [0x0100] RTC 32.768 kHz Oscillator Control Register                       */
    __IO uint32_t GPIOCTL0;              /*!< [0x0104] RTC GPIO Control 0 Register                                      */
    __IO uint32_t GPIOCTL1;              /*!< [0x0108] RTC GPIO Control 1 Register                                      */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t DSTCTL;                /*!< [0x0110] RTC Daylight Saving Time Control Register                        */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE2[3];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t TAMPCTL;               /*!< [0x0120] RTC Tamper Pin Control Register                                  */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE3[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t TAMPSEED;              /*!< [0x0128] RTC Tamper Dynamic Seed Register                                 */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE4[1];
    /// @endcond //HIDDEN_SYMBOLS
    __I  uint32_t TAMPTIME;              /*!< [0x0130] RTC Tamper Time Register                                         */
    __I  uint32_t TAMPCAL;               /*!< [0x0134] RTC Tamper Calendar Register                                     */

} RTC_T;

/**
    @addtogroup RTC_CONST RTC Bit Field Definition
    Constant Definitions for RTC Controller
@{ */

#define RTC_INIT_ACTIVE_Pos         (0)                                               /*!< RTC_T::INIT: INIT_ACTIVE Position      */
#define RTC_INIT_ACTIVE_Msk         (0x1ul << RTC_INIT_ACTIVE_Pos)               /*!< RTC_T::INIT: INIT_ACTIVE Mask          */

#define RTC_INIT_INIT_Pos                (1)                                               /*!< RTC_T::INIT: INIT Position             */
#define RTC_INIT_INIT_Msk                (0x7ffffffful << RTC_INIT_INIT_Pos)               /*!< RTC_T::INIT: INIT Mask                 */

#define RTC_RWEN_RWENF_Pos               (16)                                              /*!< RTC_T::RWEN: RWENF Position            */
#define RTC_RWEN_RWENF_Msk               (0x1ul << RTC_RWEN_RWENF_Pos)                     /*!< RTC_T::RWEN: RWENF Mask                */

#define RTC_RWEN_RTCBUSY_Pos             (24)                                              /*!< RTC_T::RWEN: RTCBUSY Position          */
#define RTC_RWEN_RTCBUSY_Msk             (0x1ul << RTC_RWEN_RTCBUSY_Pos)                   /*!< RTC_T::RWEN: RTCBUSY Mask              */

#define RTC_FREQADJ_FREQADJ_Pos          (0)                                               /*!< RTC_T::FREQADJ: FREQADJ Position       */
#define RTC_FREQADJ_FREQADJ_Msk          (0x3ffffful << RTC_FREQADJ_FREQADJ_Pos)           /*!< RTC_T::FREQADJ: FREQADJ Mask           */

#define RTC_FREQADJ_FRACTION_Pos         (0)                                               /*!< RTC_T::FREQADJ: FRACTION Position      */
#define RTC_FREQADJ_FRACTION_Msk         (0x3ful << RTC_FREQADJ_FRACTION_Pos)              /*!< RTC_T::FREQADJ: FRACTION Mask          */

#define RTC_FREQADJ_INTEGER_Pos          (8)                                               /*!< RTC_T::FREQADJ: INTEGER Position       */
#define RTC_FREQADJ_INTEGER_Msk          (0x1ful << RTC_FREQADJ_INTEGER_Pos)               /*!< RTC_T::FREQADJ: INTEGER Mask           */

#define RTC_FREQADJ_FCR_BUSY_Pos         (31)                                              /*!< RTC_T::FREQADJ: FCR_BUSY Position      */
#define RTC_FREQADJ_FCR_BUSY_Msk         (0x1ul << RTC_FREQADJ_FCR_BUSY_Pos)               /*!< RTC_T::FREQADJ: FCR_BUSY Mask          */

#define RTC_TIME_SEC_Pos                 (0)                                               /*!< RTC_T::TIME: SEC Position              */
#define RTC_TIME_SEC_Msk                 (0xful << RTC_TIME_SEC_Pos)                       /*!< RTC_T::TIME: SEC Mask                  */

#define RTC_TIME_TENSEC_Pos              (4)                                               /*!< RTC_T::TIME: TENSEC Position           */
#define RTC_TIME_TENSEC_Msk              (0x7ul << RTC_TIME_TENSEC_Pos)                    /*!< RTC_T::TIME: TENSEC Mask               */

#define RTC_TIME_MIN_Pos                 (8)                                               /*!< RTC_T::TIME: MIN Position              */
#define RTC_TIME_MIN_Msk                 (0xful << RTC_TIME_MIN_Pos)                       /*!< RTC_T::TIME: MIN Mask                  */

#define RTC_TIME_TENMIN_Pos              (12)                                              /*!< RTC_T::TIME: TENMIN Position           */
#define RTC_TIME_TENMIN_Msk              (0x7ul << RTC_TIME_TENMIN_Pos)                    /*!< RTC_T::TIME: TENMIN Mask               */

#define RTC_TIME_HR_Pos                  (16)                                              /*!< RTC_T::TIME: HR Position               */
#define RTC_TIME_HR_Msk                  (0xful << RTC_TIME_HR_Pos)                        /*!< RTC_T::TIME: HR Mask                   */

#define RTC_TIME_TENHR_Pos               (20)                                              /*!< RTC_T::TIME: TENHR Position            */
#define RTC_TIME_TENHR_Msk               (0x3ul << RTC_TIME_TENHR_Pos)                     /*!< RTC_T::TIME: TENHR Mask                */

#define RTC_CAL_DAY_Pos                  (0)                                               /*!< RTC_T::CAL: DAY Position               */
#define RTC_CAL_DAY_Msk                  (0xful << RTC_CAL_DAY_Pos)                        /*!< RTC_T::CAL: DAY Mask                   */

#define RTC_CAL_TENDAY_Pos               (4)                                               /*!< RTC_T::CAL: TENDAY Position            */
#define RTC_CAL_TENDAY_Msk               (0x3ul << RTC_CAL_TENDAY_Pos)                     /*!< RTC_T::CAL: TENDAY Mask                */

#define RTC_CAL_MON_Pos                  (8)                                               /*!< RTC_T::CAL: MON Position               */
#define RTC_CAL_MON_Msk                  (0xful << RTC_CAL_MON_Pos)                        /*!< RTC_T::CAL: MON Mask                   */

#define RTC_CAL_TENMON_Pos               (12)                                              /*!< RTC_T::CAL: TENMON Position            */
#define RTC_CAL_TENMON_Msk               (0x1ul << RTC_CAL_TENMON_Pos)                     /*!< RTC_T::CAL: TENMON Mask                */

#define RTC_CAL_YEAR_Pos                 (16)                                              /*!< RTC_T::CAL: YEAR Position              */
#define RTC_CAL_YEAR_Msk                 (0xful << RTC_CAL_YEAR_Pos)                       /*!< RTC_T::CAL: YEAR Mask                  */

#define RTC_CAL_TENYEAR_Pos              (20)                                              /*!< RTC_T::CAL: TENYEAR Position           */
#define RTC_CAL_TENYEAR_Msk              (0xful << RTC_CAL_TENYEAR_Pos)                    /*!< RTC_T::CAL: TENYEAR Mask               */

#define RTC_CLKFMT_24HEN_Pos             (0)                                               /*!< RTC_T::CLKFMT: 24HEN Position          */
#define RTC_CLKFMT_24HEN_Msk             (0x1ul << RTC_CLKFMT_24HEN_Pos)                   /*!< RTC_T::CLKFMT: 24HEN Mask              */

#define RTC_WEEKDAY_WEEKDAY_Pos          (0)                                               /*!< RTC_T::WEEKDAY: WEEKDAY Position       */
#define RTC_WEEKDAY_WEEKDAY_Msk          (0x7ul << RTC_WEEKDAY_WEEKDAY_Pos)                /*!< RTC_T::WEEKDAY: WEEKDAY Mask           */

#define RTC_TALM_SEC_Pos                 (0)                                               /*!< RTC_T::TALM: SEC Position              */
#define RTC_TALM_SEC_Msk                 (0xful << RTC_TALM_SEC_Pos)                       /*!< RTC_T::TALM: SEC Mask                  */

#define RTC_TALM_TENSEC_Pos              (4)                                               /*!< RTC_T::TALM: TENSEC Position           */
#define RTC_TALM_TENSEC_Msk              (0x7ul << RTC_TALM_TENSEC_Pos)                    /*!< RTC_T::TALM: TENSEC Mask               */

#define RTC_TALM_MIN_Pos                 (8)                                               /*!< RTC_T::TALM: MIN Position              */
#define RTC_TALM_MIN_Msk                 (0xful << RTC_TALM_MIN_Pos)                       /*!< RTC_T::TALM: MIN Mask                  */

#define RTC_TALM_TENMIN_Pos              (12)                                              /*!< RTC_T::TALM: TENMIN Position           */
#define RTC_TALM_TENMIN_Msk              (0x7ul << RTC_TALM_TENMIN_Pos)                    /*!< RTC_T::TALM: TENMIN Mask               */

#define RTC_TALM_HR_Pos                  (16)                                              /*!< RTC_T::TALM: HR Position               */
#define RTC_TALM_HR_Msk                  (0xful << RTC_TALM_HR_Pos)                        /*!< RTC_T::TALM: HR Mask                   */

#define RTC_TALM_TENHR_Pos               (20)                                              /*!< RTC_T::TALM: TENHR Position            */
#define RTC_TALM_TENHR_Msk               (0x3ul << RTC_TALM_TENHR_Pos)                     /*!< RTC_T::TALM: TENHR Mask                */

#define RTC_CALM_DAY_Pos                 (0)                                               /*!< RTC_T::CALM: DAY Position              */
#define RTC_CALM_DAY_Msk                 (0xful << RTC_CALM_DAY_Pos)                       /*!< RTC_T::CALM: DAY Mask                  */

#define RTC_CALM_TENDAY_Pos              (4)                                               /*!< RTC_T::CALM: TENDAY Position           */
#define RTC_CALM_TENDAY_Msk              (0x3ul << RTC_CALM_TENDAY_Pos)                    /*!< RTC_T::CALM: TENDAY Mask               */

#define RTC_CALM_MON_Pos                 (8)                                               /*!< RTC_T::CALM: MON Position              */
#define RTC_CALM_MON_Msk                 (0xful << RTC_CALM_MON_Pos)                       /*!< RTC_T::CALM: MON Mask                  */

#define RTC_CALM_TENMON_Pos              (12)                                              /*!< RTC_T::CALM: TENMON Position           */
#define RTC_CALM_TENMON_Msk              (0x1ul << RTC_CALM_TENMON_Pos)                    /*!< RTC_T::CALM: TENMON Mask               */

#define RTC_CALM_YEAR_Pos                (16)                                              /*!< RTC_T::CALM: YEAR Position             */
#define RTC_CALM_YEAR_Msk                (0xful << RTC_CALM_YEAR_Pos)                      /*!< RTC_T::CALM: YEAR Mask                 */

#define RTC_CALM_TENYEAR_Pos             (20)                                              /*!< RTC_T::CALM: TENYEAR Position          */
#define RTC_CALM_TENYEAR_Msk             (0xful << RTC_CALM_TENYEAR_Pos)                   /*!< RTC_T::CALM: TENYEAR Mask              */

#define RTC_LEAPYEAR_LEAPYEAR_Pos        (0)                                               /*!< RTC_T::LEAPYEAR: LEAPYEAR Position     */
#define RTC_LEAPYEAR_LEAPYEAR_Msk        (0x1ul << RTC_LEAPYEAR_LEAPYEAR_Pos)              /*!< RTC_T::LEAPYEAR: LEAPYEAR Mask         */

#define RTC_INTEN_ALMIEN_Pos             (0)                                               /*!< RTC_T::INTEN: ALMIEN Position          */
#define RTC_INTEN_ALMIEN_Msk             (0x1ul << RTC_INTEN_ALMIEN_Pos)                   /*!< RTC_T::INTEN: ALMIEN Mask              */

#define RTC_INTEN_TICKIEN_Pos            (1)                                               /*!< RTC_T::INTEN: TICKIEN Position         */
#define RTC_INTEN_TICKIEN_Msk            (0x1ul << RTC_INTEN_TICKIEN_Pos)                  /*!< RTC_T::INTEN: TICKIEN Mask             */

#define RTC_INTEN_TAMP0IEN_Pos           (8)                                               /*!< RTC_T::INTEN: TAMP0IEN Position        */
#define RTC_INTEN_TAMP0IEN_Msk           (0x1ul << RTC_INTEN_TAMP0IEN_Pos)                 /*!< RTC_T::INTEN: TAMP0IEN Mask            */

#define RTC_INTEN_TAMP1IEN_Pos           (9)                                               /*!< RTC_T::INTEN: TAMP1IEN Position        */
#define RTC_INTEN_TAMP1IEN_Msk           (0x1ul << RTC_INTEN_TAMP1IEN_Pos)                 /*!< RTC_T::INTEN: TAMP1IEN Mask            */

#define RTC_INTEN_TAMP2IEN_Pos           (10)                                              /*!< RTC_T::INTEN: TAMP2IEN Position        */
#define RTC_INTEN_TAMP2IEN_Msk           (0x1ul << RTC_INTEN_TAMP2IEN_Pos)                 /*!< RTC_T::INTEN: TAMP2IEN Mask            */

#define RTC_INTEN_TAMP3IEN_Pos           (11)                                              /*!< RTC_T::INTEN: TAMP3IEN Position        */
#define RTC_INTEN_TAMP3IEN_Msk           (0x1ul << RTC_INTEN_TAMP3IEN_Pos)                 /*!< RTC_T::INTEN: TAMP3IEN Mask            */

#define RTC_INTEN_TAMP4IEN_Pos           (12)                                              /*!< RTC_T::INTEN: TAMP4IEN Position        */
#define RTC_INTEN_TAMP4IEN_Msk           (0x1ul << RTC_INTEN_TAMP4IEN_Pos)                 /*!< RTC_T::INTEN: TAMP4IEN Mask            */

#define RTC_INTEN_TAMP5IEN_Pos           (13)                                              /*!< RTC_T::INTEN: TAMP5IEN Position        */
#define RTC_INTEN_TAMP5IEN_Msk           (0x1ul << RTC_INTEN_TAMP5IEN_Pos)                 /*!< RTC_T::INTEN: TAMP5IEN Mask            */

#define RTC_INTSTS_ALMIF_Pos             (0)                                               /*!< RTC_T::INTSTS: ALMIF Position          */
#define RTC_INTSTS_ALMIF_Msk             (0x1ul << RTC_INTSTS_ALMIF_Pos)                   /*!< RTC_T::INTSTS: ALMIF Mask              */

#define RTC_INTSTS_TICKIF_Pos            (1)                                               /*!< RTC_T::INTSTS: TICKIF Position         */
#define RTC_INTSTS_TICKIF_Msk            (0x1ul << RTC_INTSTS_TICKIF_Pos)                  /*!< RTC_T::INTSTS: TICKIF Mask             */

#define RTC_INTSTS_TAMP0IF_Pos           (8)                                               /*!< RTC_T::INTSTS: TAMP0IF Position        */
#define RTC_INTSTS_TAMP0IF_Msk           (0x1ul << RTC_INTSTS_TAMP0IF_Pos)                 /*!< RTC_T::INTSTS: TAMP0IF Mask            */

#define RTC_INTSTS_TAMP1IF_Pos           (9)                                               /*!< RTC_T::INTSTS: TAMP1IF Position        */
#define RTC_INTSTS_TAMP1IF_Msk           (0x1ul << RTC_INTSTS_TAMP1IF_Pos)                 /*!< RTC_T::INTSTS: TAMP1IF Mask            */

#define RTC_INTSTS_TAMP2IF_Pos           (10)                                              /*!< RTC_T::INTSTS: TAMP2IF Position        */
#define RTC_INTSTS_TAMP2IF_Msk           (0x1ul << RTC_INTSTS_TAMP2IF_Pos)                 /*!< RTC_T::INTSTS: TAMP2IF Mask            */

#define RTC_INTSTS_TAMP3IF_Pos           (11)                                              /*!< RTC_T::INTSTS: TAMP3IF Position        */
#define RTC_INTSTS_TAMP3IF_Msk           (0x1ul << RTC_INTSTS_TAMP3IF_Pos)                 /*!< RTC_T::INTSTS: TAMP3IF Mask            */

#define RTC_INTSTS_TAMP4IF_Pos           (12)                                              /*!< RTC_T::INTSTS: TAMP4IF Position        */
#define RTC_INTSTS_TAMP4IF_Msk           (0x1ul << RTC_INTSTS_TAMP4IF_Pos)                 /*!< RTC_T::INTSTS: TAMP4IF Mask            */

#define RTC_INTSTS_TAMP5IF_Pos           (13)                                              /*!< RTC_T::INTSTS: TAMP5IF Position        */
#define RTC_INTSTS_TAMP5IF_Msk           (0x1ul << RTC_INTSTS_TAMP5IF_Pos)                 /*!< RTC_T::INTSTS: TAMP5IF Mask            */

#define RTC_TICK_TICK_Pos                (0)                                               /*!< RTC_T::TICK: TICK Position             */
#define RTC_TICK_TICK_Msk                (0x7ul << RTC_TICK_TICK_Pos)                      /*!< RTC_T::TICK: TICK Mask                 */

#define RTC_TAMSK_MSEC_Pos               (0)                                               /*!< RTC_T::TAMSK: MSEC Position            */
#define RTC_TAMSK_MSEC_Msk               (0x1ul << RTC_TAMSK_MSEC_Pos)                     /*!< RTC_T::TAMSK: MSEC Mask                */

#define RTC_TAMSK_MTENSEC_Pos            (1)                                               /*!< RTC_T::TAMSK: MTENSEC Position         */
#define RTC_TAMSK_MTENSEC_Msk            (0x1ul << RTC_TAMSK_MTENSEC_Pos)                  /*!< RTC_T::TAMSK: MTENSEC Mask             */

#define RTC_TAMSK_MMIN_Pos               (2)                                               /*!< RTC_T::TAMSK: MMIN Position            */
#define RTC_TAMSK_MMIN_Msk               (0x1ul << RTC_TAMSK_MMIN_Pos)                     /*!< RTC_T::TAMSK: MMIN Mask                */

#define RTC_TAMSK_MTENMIN_Pos            (3)                                               /*!< RTC_T::TAMSK: MTENMIN Position         */
#define RTC_TAMSK_MTENMIN_Msk            (0x1ul << RTC_TAMSK_MTENMIN_Pos)                  /*!< RTC_T::TAMSK: MTENMIN Mask             */

#define RTC_TAMSK_MHR_Pos                (4)                                               /*!< RTC_T::TAMSK: MHR Position             */
#define RTC_TAMSK_MHR_Msk                (0x1ul << RTC_TAMSK_MHR_Pos)                      /*!< RTC_T::TAMSK: MHR Mask                 */

#define RTC_TAMSK_MTENHR_Pos             (5)                                               /*!< RTC_T::TAMSK: MTENHR Position          */
#define RTC_TAMSK_MTENHR_Msk             (0x1ul << RTC_TAMSK_MTENHR_Pos)                   /*!< RTC_T::TAMSK: MTENHR Mask              */

#define RTC_CAMSK_MDAY_Pos               (0)                                               /*!< RTC_T::CAMSK: MDAY Position            */
#define RTC_CAMSK_MDAY_Msk               (0x1ul << RTC_CAMSK_MDAY_Pos)                     /*!< RTC_T::CAMSK: MDAY Mask                */

#define RTC_CAMSK_MTENDAY_Pos            (1)                                               /*!< RTC_T::CAMSK: MTENDAY Position         */
#define RTC_CAMSK_MTENDAY_Msk            (0x1ul << RTC_CAMSK_MTENDAY_Pos)                  /*!< RTC_T::CAMSK: MTENDAY Mask             */

#define RTC_CAMSK_MMON_Pos               (2)                                               /*!< RTC_T::CAMSK: MMON Position            */
#define RTC_CAMSK_MMON_Msk               (0x1ul << RTC_CAMSK_MMON_Pos)                     /*!< RTC_T::CAMSK: MMON Mask                */

#define RTC_CAMSK_MTENMON_Pos            (3)                                               /*!< RTC_T::CAMSK: MTENMON Position         */
#define RTC_CAMSK_MTENMON_Msk            (0x1ul << RTC_CAMSK_MTENMON_Pos)                  /*!< RTC_T::CAMSK: MTENMON Mask             */

#define RTC_CAMSK_MYEAR_Pos              (4)                                               /*!< RTC_T::CAMSK: MYEAR Position           */
#define RTC_CAMSK_MYEAR_Msk              (0x1ul << RTC_CAMSK_MYEAR_Pos)                    /*!< RTC_T::CAMSK: MYEAR Mask               */

#define RTC_CAMSK_MTENYEAR_Pos           (5)                                               /*!< RTC_T::CAMSK: MTENYEAR Position        */
#define RTC_CAMSK_MTENYEAR_Msk           (0x1ul << RTC_CAMSK_MTENYEAR_Pos)                 /*!< RTC_T::CAMSK: MTENYEAR Mask            */

#define RTC_SPRCTL_SPRRWEN_Pos           (2)                                               /*!< RTC_T::SPRCTL: SPRRWEN Position        */
#define RTC_SPRCTL_SPRRWEN_Msk           (0x1ul << RTC_SPRCTL_SPRRWEN_Pos)                 /*!< RTC_T::SPRCTL: SPRRWEN Mask            */

#define RTC_SPRCTL_SPRCSTS_Pos           (5)                                               /*!< RTC_T::SPRCTL: SPRCSTS Position        */
#define RTC_SPRCTL_SPRCSTS_Msk           (0x1ul << RTC_SPRCTL_SPRCSTS_Pos)                 /*!< RTC_T::SPRCTL: SPRCSTS Mask            */

#define RTC_SPR0_SPARE_Pos               (0)                                               /*!< RTC_T::SPR0: SPARE Position            */
#define RTC_SPR0_SPARE_Msk               (0xfffffffful << RTC_SPR0_SPARE_Pos)              /*!< RTC_T::SPR0: SPARE Mask                */

#define RTC_SPR1_SPARE_Pos               (0)                                               /*!< RTC_T::SPR1: SPARE Position            */
#define RTC_SPR1_SPARE_Msk               (0xfffffffful << RTC_SPR1_SPARE_Pos)              /*!< RTC_T::SPR1: SPARE Mask                */

#define RTC_SPR2_SPARE_Pos               (0)                                               /*!< RTC_T::SPR2: SPARE Position            */
#define RTC_SPR2_SPARE_Msk               (0xfffffffful << RTC_SPR2_SPARE_Pos)              /*!< RTC_T::SPR2: SPARE Mask                */

#define RTC_SPR3_SPARE_Pos               (0)                                               /*!< RTC_T::SPR3: SPARE Position            */
#define RTC_SPR3_SPARE_Msk               (0xfffffffful << RTC_SPR3_SPARE_Pos)              /*!< RTC_T::SPR3: SPARE Mask                */

#define RTC_SPR4_SPARE_Pos               (0)                                               /*!< RTC_T::SPR4: SPARE Position            */
#define RTC_SPR4_SPARE_Msk               (0xfffffffful << RTC_SPR4_SPARE_Pos)              /*!< RTC_T::SPR4: SPARE Mask                */

#define RTC_SPR5_SPARE_Pos               (0)                                               /*!< RTC_T::SPR5: SPARE Position            */
#define RTC_SPR5_SPARE_Msk               (0xfffffffful << RTC_SPR5_SPARE_Pos)              /*!< RTC_T::SPR5: SPARE Mask                */

#define RTC_SPR6_SPARE_Pos               (0)                                               /*!< RTC_T::SPR6: SPARE Position            */
#define RTC_SPR6_SPARE_Msk               (0xfffffffful << RTC_SPR6_SPARE_Pos)              /*!< RTC_T::SPR6: SPARE Mask                */

#define RTC_SPR7_SPARE_Pos               (0)                                               /*!< RTC_T::SPR7: SPARE Position            */
#define RTC_SPR7_SPARE_Msk               (0xfffffffful << RTC_SPR7_SPARE_Pos)              /*!< RTC_T::SPR7: SPARE Mask                */

#define RTC_SPR8_SPARE_Pos               (0)                                               /*!< RTC_T::SPR8: SPARE Position            */
#define RTC_SPR8_SPARE_Msk               (0xfffffffful << RTC_SPR8_SPARE_Pos)              /*!< RTC_T::SPR8: SPARE Mask                */

#define RTC_SPR9_SPARE_Pos               (0)                                               /*!< RTC_T::SPR9: SPARE Position            */
#define RTC_SPR9_SPARE_Msk               (0xfffffffful << RTC_SPR9_SPARE_Pos)              /*!< RTC_T::SPR9: SPARE Mask                */

#define RTC_SPR10_SPARE_Pos              (0)                                               /*!< RTC_T::SPR10: SPARE Position           */
#define RTC_SPR10_SPARE_Msk              (0xfffffffful << RTC_SPR10_SPARE_Pos)             /*!< RTC_T::SPR10: SPARE Mask               */

#define RTC_SPR11_SPARE_Pos              (0)                                               /*!< RTC_T::SPR11: SPARE Position           */
#define RTC_SPR11_SPARE_Msk              (0xfffffffful << RTC_SPR11_SPARE_Pos)             /*!< RTC_T::SPR11: SPARE Mask               */

#define RTC_SPR12_SPARE_Pos              (0)                                               /*!< RTC_T::SPR12: SPARE Position           */
#define RTC_SPR12_SPARE_Msk              (0xfffffffful << RTC_SPR12_SPARE_Pos)             /*!< RTC_T::SPR12: SPARE Mask               */

#define RTC_SPR13_SPARE_Pos              (0)                                               /*!< RTC_T::SPR13: SPARE Position           */
#define RTC_SPR13_SPARE_Msk              (0xfffffffful << RTC_SPR13_SPARE_Pos)             /*!< RTC_T::SPR13: SPARE Mask               */

#define RTC_SPR14_SPARE_Pos              (0)                                               /*!< RTC_T::SPR14: SPARE Position           */
#define RTC_SPR14_SPARE_Msk              (0xfffffffful << RTC_SPR14_SPARE_Pos)             /*!< RTC_T::SPR14: SPARE Mask               */

#define RTC_SPR15_SPARE_Pos              (0)                                               /*!< RTC_T::SPR15: SPARE Position           */
#define RTC_SPR15_SPARE_Msk              (0xfffffffful << RTC_SPR15_SPARE_Pos)             /*!< RTC_T::SPR15: SPARE Mask               */

#define RTC_SPR16_SPARE_Pos              (0)                                               /*!< RTC_T::SPR16: SPARE Position           */
#define RTC_SPR16_SPARE_Msk              (0xfffffffful << RTC_SPR16_SPARE_Pos)             /*!< RTC_T::SPR16: SPARE Mask               */

#define RTC_SPR17_SPARE_Pos              (0)                                               /*!< RTC_T::SPR17: SPARE Position           */
#define RTC_SPR17_SPARE_Msk              (0xfffffffful << RTC_SPR17_SPARE_Pos)             /*!< RTC_T::SPR17: SPARE Mask               */

#define RTC_SPR18_SPARE_Pos              (0)                                               /*!< RTC_T::SPR18: SPARE Position           */
#define RTC_SPR18_SPARE_Msk              (0xfffffffful << RTC_SPR18_SPARE_Pos)             /*!< RTC_T::SPR18: SPARE Mask               */

#define RTC_SPR19_SPARE_Pos              (0)                                               /*!< RTC_T::SPR19: SPARE Position           */
#define RTC_SPR19_SPARE_Msk              (0xfffffffful << RTC_SPR19_SPARE_Pos)             /*!< RTC_T::SPR19: SPARE Mask               */

#define RTC_LXTCTL_GAIN_Pos              (1)                                               /*!< RTC_T::LXTCTL: GAIN Position           */
#define RTC_LXTCTL_GAIN_Msk              (0x3ul << RTC_LXTCTL_GAIN_Pos)                    /*!< RTC_T::LXTCTL: GAIN Mask               */

#define RTC_GPIOCTL0_OPMODE0_Pos         (0)                                               /*!< RTC_T::GPIOCTL0: OPMODE0 Position      */
#define RTC_GPIOCTL0_OPMODE0_Msk         (0x3ul << RTC_GPIOCTL0_OPMODE0_Pos)               /*!< RTC_T::GPIOCTL0: OPMODE0 Mask          */

#define RTC_GPIOCTL0_DOUT0_Pos           (2)                                               /*!< RTC_T::GPIOCTL0: DOUT0 Position        */
#define RTC_GPIOCTL0_DOUT0_Msk           (0x1ul << RTC_GPIOCTL0_DOUT0_Pos)                 /*!< RTC_T::GPIOCTL0: DOUT0 Mask            */

#define RTC_GPIOCTL0_CTLSEL0_Pos         (3)                                               /*!< RTC_T::GPIOCTL0: CTLSEL0 Position      */
#define RTC_GPIOCTL0_CTLSEL0_Msk         (0x1ul << RTC_GPIOCTL0_CTLSEL0_Pos)               /*!< RTC_T::GPIOCTL0: CTLSEL0 Mask          */

#define RTC_GPIOCTL0_PUSEL0_Pos          (4)                                               /*!< RTC_T::GPIOCTL0: PUSEL0 Position       */
#define RTC_GPIOCTL0_PUSEL0_Msk          (0x3ul << RTC_GPIOCTL0_PUSEL0_Pos)                /*!< RTC_T::GPIOCTL0: PUSEL0 Mask           */

#define RTC_GPIOCTL0_OPMODE1_Pos         (8)                                               /*!< RTC_T::GPIOCTL0: OPMODE1 Position      */
#define RTC_GPIOCTL0_OPMODE1_Msk         (0x3ul << RTC_GPIOCTL0_OPMODE1_Pos)               /*!< RTC_T::GPIOCTL0: OPMODE1 Mask          */

#define RTC_GPIOCTL0_DOUT1_Pos           (10)                                              /*!< RTC_T::GPIOCTL0: DOUT1 Position        */
#define RTC_GPIOCTL0_DOUT1_Msk           (0x1ul << RTC_GPIOCTL0_DOUT1_Pos)                 /*!< RTC_T::GPIOCTL0: DOUT1 Mask            */

#define RTC_GPIOCTL0_CTLSEL1_Pos         (11)                                              /*!< RTC_T::GPIOCTL0: CTLSEL1 Position      */
#define RTC_GPIOCTL0_CTLSEL1_Msk         (0x1ul << RTC_GPIOCTL0_CTLSEL1_Pos)               /*!< RTC_T::GPIOCTL0: CTLSEL1 Mask          */

#define RTC_GPIOCTL0_PUSEL1_Pos          (12)                                              /*!< RTC_T::GPIOCTL0: PUSEL1 Position       */
#define RTC_GPIOCTL0_PUSEL1_Msk          (0x3ul << RTC_GPIOCTL0_PUSEL1_Pos)                /*!< RTC_T::GPIOCTL0: PUSEL1 Mask           */

#define RTC_GPIOCTL0_OPMODE2_Pos         (16)                                              /*!< RTC_T::GPIOCTL0: OPMODE2 Position      */
#define RTC_GPIOCTL0_OPMODE2_Msk         (0x3ul << RTC_GPIOCTL0_OPMODE2_Pos)               /*!< RTC_T::GPIOCTL0: OPMODE2 Mask          */

#define RTC_GPIOCTL0_DOUT2_Pos           (18)                                              /*!< RTC_T::GPIOCTL0: DOUT2 Position        */
#define RTC_GPIOCTL0_DOUT2_Msk           (0x1ul << RTC_GPIOCTL0_DOUT2_Pos)                 /*!< RTC_T::GPIOCTL0: DOUT2 Mask            */

#define RTC_GPIOCTL0_CTLSEL2_Pos         (19)                                              /*!< RTC_T::GPIOCTL0: CTLSEL2 Position      */
#define RTC_GPIOCTL0_CTLSEL2_Msk         (0x1ul << RTC_GPIOCTL0_CTLSEL2_Pos)               /*!< RTC_T::GPIOCTL0: CTLSEL2 Mask          */

#define RTC_GPIOCTL0_PUSEL2_Pos          (20)                                              /*!< RTC_T::GPIOCTL0: PUSEL2 Position       */
#define RTC_GPIOCTL0_PUSEL2_Msk          (0x3ul << RTC_GPIOCTL0_PUSEL2_Pos)                /*!< RTC_T::GPIOCTL0: PUSEL2 Mask           */

#define RTC_GPIOCTL0_OPMODE3_Pos         (24)                                              /*!< RTC_T::GPIOCTL0: OPMODE3 Position      */
#define RTC_GPIOCTL0_OPMODE3_Msk         (0x3ul << RTC_GPIOCTL0_OPMODE3_Pos)               /*!< RTC_T::GPIOCTL0: OPMODE3 Mask          */

#define RTC_GPIOCTL0_DOUT3_Pos           (26)                                              /*!< RTC_T::GPIOCTL0: DOUT3 Position        */
#define RTC_GPIOCTL0_DOUT3_Msk           (0x1ul << RTC_GPIOCTL0_DOUT3_Pos)                 /*!< RTC_T::GPIOCTL0: DOUT3 Mask            */

#define RTC_GPIOCTL0_CTLSEL3_Pos         (27)                                              /*!< RTC_T::GPIOCTL0: CTLSEL3 Position      */
#define RTC_GPIOCTL0_CTLSEL3_Msk         (0x1ul << RTC_GPIOCTL0_CTLSEL3_Pos)               /*!< RTC_T::GPIOCTL0: CTLSEL3 Mask          */

#define RTC_GPIOCTL0_PUSEL3_Pos          (28)                                              /*!< RTC_T::GPIOCTL0: PUSEL3 Position       */
#define RTC_GPIOCTL0_PUSEL3_Msk          (0x3ul << RTC_GPIOCTL0_PUSEL3_Pos)                /*!< RTC_T::GPIOCTL0: PUSEL3 Mask           */

#define RTC_GPIOCTL1_OPMODE4_Pos         (0)                                               /*!< RTC_T::GPIOCTL1: OPMODE4 Position      */
#define RTC_GPIOCTL1_OPMODE4_Msk         (0x3ul << RTC_GPIOCTL1_OPMODE4_Pos)               /*!< RTC_T::GPIOCTL1: OPMODE4 Mask          */

#define RTC_GPIOCTL1_DOUT4_Pos           (2)                                               /*!< RTC_T::GPIOCTL1: DOUT4 Position        */
#define RTC_GPIOCTL1_DOUT4_Msk           (0x1ul << RTC_GPIOCTL1_DOUT4_Pos)                 /*!< RTC_T::GPIOCTL1: DOUT4 Mask            */

#define RTC_GPIOCTL1_CTLSEL4_Pos         (3)                                               /*!< RTC_T::GPIOCTL1: CTLSEL4 Position      */
#define RTC_GPIOCTL1_CTLSEL4_Msk         (0x1ul << RTC_GPIOCTL1_CTLSEL4_Pos)               /*!< RTC_T::GPIOCTL1: CTLSEL4 Mask          */

#define RTC_GPIOCTL1_PUSEL4_Pos          (4)                                               /*!< RTC_T::GPIOCTL1: PUSEL4 Position       */
#define RTC_GPIOCTL1_PUSEL4_Msk          (0x3ul << RTC_GPIOCTL1_PUSEL4_Pos)                /*!< RTC_T::GPIOCTL1: PUSEL4 Mask           */

#define RTC_GPIOCTL1_OPMODE5_Pos         (8)                                               /*!< RTC_T::GPIOCTL1: OPMODE5 Position      */
#define RTC_GPIOCTL1_OPMODE5_Msk         (0x3ul << RTC_GPIOCTL1_OPMODE5_Pos)               /*!< RTC_T::GPIOCTL1: OPMODE5 Mask          */

#define RTC_GPIOCTL1_DOUT5_Pos           (10)                                              /*!< RTC_T::GPIOCTL1: DOUT5 Position        */
#define RTC_GPIOCTL1_DOUT5_Msk           (0x1ul << RTC_GPIOCTL1_DOUT5_Pos)                 /*!< RTC_T::GPIOCTL1: DOUT5 Mask            */

#define RTC_GPIOCTL1_CTLSEL5_Pos         (11)                                              /*!< RTC_T::GPIOCTL1: CTLSEL5 Position      */
#define RTC_GPIOCTL1_CTLSEL5_Msk         (0x1ul << RTC_GPIOCTL1_CTLSEL5_Pos)               /*!< RTC_T::GPIOCTL1: CTLSEL5 Mask          */

#define RTC_GPIOCTL1_PUSEL5_Pos          (12)                                              /*!< RTC_T::GPIOCTL1: PUSEL5 Position       */
#define RTC_GPIOCTL1_PUSEL5_Msk          (0x3ul << RTC_GPIOCTL1_PUSEL5_Pos)                /*!< RTC_T::GPIOCTL1: PUSEL5 Mask           */

#define RTC_GPIOCTL1_OPMODE6_Pos         (16)                                              /*!< RTC_T::GPIOCTL1: OPMODE6 Position      */
#define RTC_GPIOCTL1_OPMODE6_Msk         (0x3ul << RTC_GPIOCTL1_OPMODE6_Pos)               /*!< RTC_T::GPIOCTL1: OPMODE6 Mask          */

#define RTC_GPIOCTL1_DOUT6_Pos           (18)                                              /*!< RTC_T::GPIOCTL1: DOUT6 Position        */
#define RTC_GPIOCTL1_DOUT6_Msk           (0x1ul << RTC_GPIOCTL1_DOUT6_Pos)                 /*!< RTC_T::GPIOCTL1: DOUT6 Mask            */

#define RTC_GPIOCTL1_CTLSEL6_Pos         (19)                                              /*!< RTC_T::GPIOCTL1: CTLSEL6 Position      */
#define RTC_GPIOCTL1_CTLSEL6_Msk         (0x1ul << RTC_GPIOCTL1_CTLSEL6_Pos)               /*!< RTC_T::GPIOCTL1: CTLSEL6 Mask          */

#define RTC_GPIOCTL1_PUSEL6_Pos          (20)                                              /*!< RTC_T::GPIOCTL1: PUSEL6 Position       */
#define RTC_GPIOCTL1_PUSEL6_Msk          (0x3ul << RTC_GPIOCTL1_PUSEL6_Pos)                /*!< RTC_T::GPIOCTL1: PUSEL6 Mask           */

#define RTC_GPIOCTL1_OPMODE7_Pos         (24)                                              /*!< RTC_T::GPIOCTL1: OPMODE7 Position      */
#define RTC_GPIOCTL1_OPMODE7_Msk         (0x3ul << RTC_GPIOCTL1_OPMODE7_Pos)               /*!< RTC_T::GPIOCTL1: OPMODE7 Mask          */

#define RTC_GPIOCTL1_DOUT7_Pos           (26)                                              /*!< RTC_T::GPIOCTL1: DOUT7 Position        */
#define RTC_GPIOCTL1_DOUT7_Msk           (0x1ul << RTC_GPIOCTL1_DOUT7_Pos)                 /*!< RTC_T::GPIOCTL1: DOUT7 Mask            */

#define RTC_GPIOCTL1_CTLSEL7_Pos         (27)                                              /*!< RTC_T::GPIOCTL1: CTLSEL7 Position      */
#define RTC_GPIOCTL1_CTLSEL7_Msk         (0x1ul << RTC_GPIOCTL1_CTLSEL7_Pos)               /*!< RTC_T::GPIOCTL1: CTLSEL7 Mask          */

#define RTC_GPIOCTL1_PUSEL7_Pos          (28)                                              /*!< RTC_T::GPIOCTL1: PUSEL7 Position       */
#define RTC_GPIOCTL1_PUSEL7_Msk          (0x3ul << RTC_GPIOCTL1_PUSEL7_Pos)                /*!< RTC_T::GPIOCTL1: PUSEL7 Mask           */

#define RTC_DSTCTL_ADDHR_Pos             (0)                                               /*!< RTC_T::DSTCTL: ADDHR Position          */
#define RTC_DSTCTL_ADDHR_Msk             (0x1ul << RTC_DSTCTL_ADDHR_Pos)                   /*!< RTC_T::DSTCTL: ADDHR Mask              */

#define RTC_DSTCTL_SUBHR_Pos             (1)                                               /*!< RTC_T::DSTCTL: SUBHR Position          */
#define RTC_DSTCTL_SUBHR_Msk             (0x1ul << RTC_DSTCTL_SUBHR_Pos)                   /*!< RTC_T::DSTCTL: SUBHR Mask              */

#define RTC_DSTCTL_DSBAK_Pos             (2)                                               /*!< RTC_T::DSTCTL: DSBAK Position          */
#define RTC_DSTCTL_DSBAK_Msk             (0x1ul << RTC_DSTCTL_DSBAK_Pos)                   /*!< RTC_T::DSTCTL: DSBAK Mask              */

#define RTC_TAMPCTL_DYN1ISS_Pos          (0)                                               /*!< RTC_T::TAMPCTL: DYN1ISS Position       */
#define RTC_TAMPCTL_DYN1ISS_Msk          (0x1ul << RTC_TAMPCTL_DYN1ISS_Pos)                /*!< RTC_T::TAMPCTL: DYN1ISS Mask           */

#define RTC_TAMPCTL_DYN2ISS_Pos          (1)                                               /*!< RTC_T::TAMPCTL: DYN2ISS Position       */
#define RTC_TAMPCTL_DYN2ISS_Msk          (0x1ul << RTC_TAMPCTL_DYN2ISS_Pos)                /*!< RTC_T::TAMPCTL: DYN2ISS Mask           */

#define RTC_TAMPCTL_DYNSRC_Pos           (2)                                               /*!< RTC_T::TAMPCTL: DYNSRC Position        */
#define RTC_TAMPCTL_DYNSRC_Msk           (0x3ul << RTC_TAMPCTL_DYNSRC_Pos)                 /*!< RTC_T::TAMPCTL: DYNSRC Mask            */

#define RTC_TAMPCTL_SEEDRLD_Pos          (4)                                               /*!< RTC_T::TAMPCTL: SEEDRLD Position       */
#define RTC_TAMPCTL_SEEDRLD_Msk          (0x1ul << RTC_TAMPCTL_SEEDRLD_Pos)                /*!< RTC_T::TAMPCTL: SEEDRLD Mask           */

#define RTC_TAMPCTL_DYNRATE_Pos          (5)                                               /*!< RTC_T::TAMPCTL: DYNRATE Position       */
#define RTC_TAMPCTL_DYNRATE_Msk          (0x7ul << RTC_TAMPCTL_DYNRATE_Pos)                /*!< RTC_T::TAMPCTL: DYNRATE Mask           */

#define RTC_TAMPCTL_TAMP0EN_Pos          (8)                                               /*!< RTC_T::TAMPCTL: TAMP0EN Position       */
#define RTC_TAMPCTL_TAMP0EN_Msk          (0x1ul << RTC_TAMPCTL_TAMP0EN_Pos)                /*!< RTC_T::TAMPCTL: TAMP0EN Mask           */

#define RTC_TAMPCTL_TAMP0LV_Pos          (9)                                               /*!< RTC_T::TAMPCTL: TAMP0LV Position       */
#define RTC_TAMPCTL_TAMP0LV_Msk          (0x1ul << RTC_TAMPCTL_TAMP0LV_Pos)                /*!< RTC_T::TAMPCTL: TAMP0LV Mask           */

#define RTC_TAMPCTL_TAMP0DBEN_Pos        (10)                                              /*!< RTC_T::TAMPCTL: TAMP0DBEN Position     */
#define RTC_TAMPCTL_TAMP0DBEN_Msk        (0x1ul << RTC_TAMPCTL_TAMP0DBEN_Pos)              /*!< RTC_T::TAMPCTL: TAMP0DBEN Mask         */

#define RTC_TAMPCTL_TAMP1EN_Pos          (12)                                              /*!< RTC_T::TAMPCTL: TAMP1EN Position       */
#define RTC_TAMPCTL_TAMP1EN_Msk          (0x1ul << RTC_TAMPCTL_TAMP1EN_Pos)                /*!< RTC_T::TAMPCTL: TAMP1EN Mask           */

#define RTC_TAMPCTL_TAMP1LV_Pos          (13)                                              /*!< RTC_T::TAMPCTL: TAMP1LV Position       */
#define RTC_TAMPCTL_TAMP1LV_Msk          (0x1ul << RTC_TAMPCTL_TAMP1LV_Pos)                /*!< RTC_T::TAMPCTL: TAMP1LV Mask           */

#define RTC_TAMPCTL_TAMP1DBEN_Pos        (14)                                              /*!< RTC_T::TAMPCTL: TAMP1DBEN Position     */
#define RTC_TAMPCTL_TAMP1DBEN_Msk        (0x1ul << RTC_TAMPCTL_TAMP1DBEN_Pos)              /*!< RTC_T::TAMPCTL: TAMP1DBEN Mask         */

#define RTC_TAMPCTL_DYNPR0EN_Pos         (15)                                              /*!< RTC_T::TAMPCTL: DYNPR0EN Position      */
#define RTC_TAMPCTL_DYNPR0EN_Msk         (0x1ul << RTC_TAMPCTL_DYNPR0EN_Pos)               /*!< RTC_T::TAMPCTL: DYNPR0EN Mask          */

#define RTC_TAMPCTL_TAMP2EN_Pos          (16)                                              /*!< RTC_T::TAMPCTL: TAMP2EN Position       */
#define RTC_TAMPCTL_TAMP2EN_Msk          (0x1ul << RTC_TAMPCTL_TAMP2EN_Pos)                /*!< RTC_T::TAMPCTL: TAMP2EN Mask           */

#define RTC_TAMPCTL_TAMP2LV_Pos          (17)                                              /*!< RTC_T::TAMPCTL: TAMP2LV Position       */
#define RTC_TAMPCTL_TAMP2LV_Msk          (0x1ul << RTC_TAMPCTL_TAMP2LV_Pos)                /*!< RTC_T::TAMPCTL: TAMP2LV Mask           */

#define RTC_TAMPCTL_TAMP2DBEN_Pos        (18)                                              /*!< RTC_T::TAMPCTL: TAMP2DBEN Position     */
#define RTC_TAMPCTL_TAMP2DBEN_Msk        (0x1ul << RTC_TAMPCTL_TAMP2DBEN_Pos)              /*!< RTC_T::TAMPCTL: TAMP2DBEN Mask         */

#define RTC_TAMPCTL_TAMP3EN_Pos          (20)                                              /*!< RTC_T::TAMPCTL: TAMP3EN Position       */
#define RTC_TAMPCTL_TAMP3EN_Msk          (0x1ul << RTC_TAMPCTL_TAMP3EN_Pos)                /*!< RTC_T::TAMPCTL: TAMP3EN Mask           */

#define RTC_TAMPCTL_TAMP3LV_Pos          (21)                                              /*!< RTC_T::TAMPCTL: TAMP3LV Position       */
#define RTC_TAMPCTL_TAMP3LV_Msk          (0x1ul << RTC_TAMPCTL_TAMP3LV_Pos)                /*!< RTC_T::TAMPCTL: TAMP3LV Mask           */

#define RTC_TAMPCTL_TAMP3DBEN_Pos        (22)                                              /*!< RTC_T::TAMPCTL: TAMP3DBEN Position     */
#define RTC_TAMPCTL_TAMP3DBEN_Msk        (0x1ul << RTC_TAMPCTL_TAMP3DBEN_Pos)              /*!< RTC_T::TAMPCTL: TAMP3DBEN Mask         */

#define RTC_TAMPCTL_DYNPR1EN_Pos         (23)                                              /*!< RTC_T::TAMPCTL: DYNPR1EN Position      */
#define RTC_TAMPCTL_DYNPR1EN_Msk         (0x1ul << RTC_TAMPCTL_DYNPR1EN_Pos)               /*!< RTC_T::TAMPCTL: DYNPR1EN Mask          */

#define RTC_TAMPCTL_TAMP4EN_Pos          (24)                                              /*!< RTC_T::TAMPCTL: TAMP4EN Position       */
#define RTC_TAMPCTL_TAMP4EN_Msk          (0x1ul << RTC_TAMPCTL_TAMP4EN_Pos)                /*!< RTC_T::TAMPCTL: TAMP4EN Mask           */

#define RTC_TAMPCTL_TAMP4LV_Pos          (25)                                              /*!< RTC_T::TAMPCTL: TAMP4LV Position       */
#define RTC_TAMPCTL_TAMP4LV_Msk          (0x1ul << RTC_TAMPCTL_TAMP4LV_Pos)                /*!< RTC_T::TAMPCTL: TAMP4LV Mask           */

#define RTC_TAMPCTL_TAMP4DBEN_Pos        (26)                                              /*!< RTC_T::TAMPCTL: TAMP4DBEN Position     */
#define RTC_TAMPCTL_TAMP4DBEN_Msk        (0x1ul << RTC_TAMPCTL_TAMP4DBEN_Pos)              /*!< RTC_T::TAMPCTL: TAMP4DBEN Mask         */

#define RTC_TAMPCTL_TAMP5EN_Pos          (28)                                              /*!< RTC_T::TAMPCTL: TAMP5EN Position       */
#define RTC_TAMPCTL_TAMP5EN_Msk          (0x1ul << RTC_TAMPCTL_TAMP5EN_Pos)                /*!< RTC_T::TAMPCTL: TAMP5EN Mask           */

#define RTC_TAMPCTL_TAMP5LV_Pos          (29)                                              /*!< RTC_T::TAMPCTL: TAMP5LV Position       */
#define RTC_TAMPCTL_TAMP5LV_Msk          (0x1ul << RTC_TAMPCTL_TAMP5LV_Pos)                /*!< RTC_T::TAMPCTL: TAMP5LV Mask           */

#define RTC_TAMPCTL_TAMP5DBEN_Pos        (30)                                              /*!< RTC_T::TAMPCTL: TAMP5DBEN Position     */
#define RTC_TAMPCTL_TAMP5DBEN_Msk        (0x1ul << RTC_TAMPCTL_TAMP5DBEN_Pos)              /*!< RTC_T::TAMPCTL: TAMP5DBEN Mask         */

#define RTC_TAMPCTL_DYNPR2EN_Pos         (31)                                              /*!< RTC_T::TAMPCTL: DYNPR2EN Position      */
#define RTC_TAMPCTL_DYNPR2EN_Msk         (0x1ul << RTC_TAMPCTL_DYNPR2EN_Pos)               /*!< RTC_T::TAMPCTL: DYNPR2EN Mask          */

#define RTC_TAMPSEED_SEED_Pos            (0)                                               /*!< RTC_T::TAMPSEED: SEED Position         */
#define RTC_TAMPSEED_SEED_Msk            (0xfffffffful << RTC_TAMPSEED_SEED_Pos)           /*!< RTC_T::TAMPSEED: SEED Mask             */

#define RTC_TAMPTIME_SEC_Pos             (0)                                               /*!< RTC_T::TAMPTIME: SEC Position          */
#define RTC_TAMPTIME_SEC_Msk             (0xful << RTC_TAMPTIME_SEC_Pos)                   /*!< RTC_T::TAMPTIME: SEC Mask              */

#define RTC_TAMPTIME_TENSEC_Pos          (4)                                               /*!< RTC_T::TAMPTIME: TENSEC Position       */
#define RTC_TAMPTIME_TENSEC_Msk          (0x7ul << RTC_TAMPTIME_TENSEC_Pos)                /*!< RTC_T::TAMPTIME: TENSEC Mask           */

#define RTC_TAMPTIME_MIN_Pos             (8)                                               /*!< RTC_T::TAMPTIME: MIN Position          */
#define RTC_TAMPTIME_MIN_Msk             (0xful << RTC_TAMPTIME_MIN_Pos)                   /*!< RTC_T::TAMPTIME: MIN Mask              */

#define RTC_TAMPTIME_TENMIN_Pos          (12)                                              /*!< RTC_T::TAMPTIME: TENMIN Position       */
#define RTC_TAMPTIME_TENMIN_Msk          (0x7ul << RTC_TAMPTIME_TENMIN_Pos)                /*!< RTC_T::TAMPTIME: TENMIN Mask           */

#define RTC_TAMPTIME_HR_Pos              (16)                                              /*!< RTC_T::TAMPTIME: HR Position           */
#define RTC_TAMPTIME_HR_Msk              (0xful << RTC_TAMPTIME_HR_Pos)                    /*!< RTC_T::TAMPTIME: HR Mask               */

#define RTC_TAMPTIME_TENHR_Pos           (20)                                              /*!< RTC_T::TAMPTIME: TENHR Position        */
#define RTC_TAMPTIME_TENHR_Msk           (0x3ul << RTC_TAMPTIME_TENHR_Pos)                 /*!< RTC_T::TAMPTIME: TENHR Mask            */

#define RTC_TAMPCAL_DAY_Pos              (0)                                               /*!< RTC_T::TAMPCAL: DAY Position           */
#define RTC_TAMPCAL_DAY_Msk              (0xful << RTC_TAMPCAL_DAY_Pos)                    /*!< RTC_T::TAMPCAL: DAY Mask               */

#define RTC_TAMPCAL_TENDAY_Pos           (4)                                               /*!< RTC_T::TAMPCAL: TENDAY Position        */
#define RTC_TAMPCAL_TENDAY_Msk           (0x3ul << RTC_TAMPCAL_TENDAY_Pos)                 /*!< RTC_T::TAMPCAL: TENDAY Mask            */

#define RTC_TAMPCAL_MON_Pos              (8)                                               /*!< RTC_T::TAMPCAL: MON Position           */
#define RTC_TAMPCAL_MON_Msk              (0xful << RTC_TAMPCAL_MON_Pos)                    /*!< RTC_T::TAMPCAL: MON Mask               */

#define RTC_TAMPCAL_TENMON_Pos           (12)                                              /*!< RTC_T::TAMPCAL: TENMON Position        */
#define RTC_TAMPCAL_TENMON_Msk           (0x1ul << RTC_TAMPCAL_TENMON_Pos)                 /*!< RTC_T::TAMPCAL: TENMON Mask            */

#define RTC_TAMPCAL_YEAR_Pos             (16)                                              /*!< RTC_T::TAMPCAL: YEAR Position          */
#define RTC_TAMPCAL_YEAR_Msk             (0xful << RTC_TAMPCAL_YEAR_Pos)                   /*!< RTC_T::TAMPCAL: YEAR Mask              */

#define RTC_TAMPCAL_TENYEAR_Pos          (20)                                              /*!< RTC_T::TAMPCAL: TENYEAR Position       */
#define RTC_TAMPCAL_TENYEAR_Msk          (0xful << RTC_TAMPCAL_TENYEAR_Pos)                /*!< RTC_T::TAMPCAL: TENYEAR Mask           */


/**@}*/ /* RTC_CONST */
/**@}*/ /* end of RTC register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __RTC_REG_H__ */
