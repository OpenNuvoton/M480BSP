/**************************************************************************//**
 * @file     timer_reg.h
 * @version  V1.00
 * @brief    TIMER register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __TIMER_REG_H__
#define __TIMER_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup TIMER Timer Controller(TIMER)
    Memory Mapped Structure for TIMER Controller
@{ */

typedef struct
{


    /**
@var TIMER_T::CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL
</font><br><p> <font size="2">
Offset: 0x00  Timer Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>PSC</td><td><div style="word-wrap: break-word;"><b>Prescale Counter
</b><br>
Timer input clock or event source is divided by (PSC+1) before it is fed to the timer up counter
<br>
If this field is 0 (PSC = 0), then there is no scaling.
<br>
Note: Update prescale counter value will reset internal 8-bit prescale counter and 24-bit up counter value.
<br>
</div></td></tr><tr><td>
[19]</td><td>INTRGEN</td><td><div style="word-wrap: break-word;"><b>Inter-timer Trigger Mode Enable Control
</b><br>
Setting this bit will enable the inter-timer trigger capture function.
<br>
The Timer0/2 will be in event counter mode and counting with external clock source or event
<br>
Also, Timer1/3 will be in trigger-counting mode of capture function.
<br>
0 = Inter-Timer Trigger Capture mode Disabled.
<br>
1 = Inter-Timer Trigger Capture mode Enabled.
<br>
Note: For Timer1/3, this bit is ignored and the read back value is always 0.
<br>
</div></td></tr><tr><td>
[20]</td><td>PERIOSEL</td><td><div style="word-wrap: break-word;"><b>Periodic Mode Behavior Selection Enable Bit
</b><br>
0 = The behavior selection in periodic mode is Disabled.
<br>
When user updates CMPDAT while timer is running in periodic mode,
<br>
CNT will be reset to default value.
<br>
1 = The behavior selection in periodic mode is Enabled.
<br>
When user update CMPDAT while timer is running in periodic mode, the limitations as bellows list,
<br>
If updated CMPDAT value > CNT, CMPDAT will be updated and CNT keep running continually.
<br>
If updated CMPDAT value = CNT, timer time-out interrupt will be asserted immediately.
<br>
If updated CMPDAT value < CNT, CNT will be reset to default value.
<br>
</div></td></tr><tr><td>
[21]</td><td>TGLPINSEL</td><td><div style="word-wrap: break-word;"><b>Toggle-output Pin Select
</b><br>
0 = Toggle mode output to TMx (Timer Event Counter Pin).
<br>
1 = Toggle mode output to TMx_EXT (Timer External Capture Pin).
<br>
</div></td></tr><tr><td>
[22]</td><td>CAPSRC</td><td><div style="word-wrap: break-word;"><b>Capture Pin Source Selection
</b><br>
0 = Capture Function source is from TMx_EXT (x= 0~3) pin.
<br>
1 = Capture Function source is from internal ACMP output signal
<br>
User can set ACMPSSEL (TIMERx_EXTCTL[8]) to decide which internal ACMP output signal as timer capture source.
<br>
</div></td></tr><tr><td>
[23]</td><td>WKEN</td><td><div style="word-wrap: break-word;"><b>Wake-up Function Enable Bit
</b><br>
If this bit is set to 1, while timer interrupt flag TIF (TIMERx_INTSTS[0]) is 1 and INTEN (TIMERx_CTL[29]) is enabled, the timer interrupt signal will generate a wake-up trigger event to CPU.
<br>
0 = Wake-up function Disabled if timer interrupt signal generated.
<br>
1 = Wake-up function Enabled if timer interrupt signal generated.
<br>
</div></td></tr><tr><td>
[24]</td><td>EXTCNTEN</td><td><div style="word-wrap: break-word;"><b>Event Counter Mode Enable Bit
</b><br>
This bit is for external counting pin function enabled.
<br>
0 = Event counter mode Disabled.
<br>
1 = Event counter mode Enabled.
<br>
Note: When timer is used as an event counter, this bit should be set to 1 and select PCLK as timer clock source.
<br>
</div></td></tr><tr><td>
[25]</td><td>ACTSTS</td><td><div style="word-wrap: break-word;"><b>Timer Active Status Bit (Read Only)
</b><br>
This bit indicates the 24-bit up counter status.
<br>
0 = 24-bit up counter is not active.
<br>
1 = 24-bit up counter is active.
<br>
Note: This bit may active when CNT 0 transition to CNT 1.
<br>
</div></td></tr><tr><td>
[28:27]</td><td>OPMODE</td><td><div style="word-wrap: break-word;"><b>Timer Counting Mode Select
</b><br>
00 = The Timer controller is operated in One-shot mode.
<br>
01 = The Timer controller is operated in Periodic mode.
<br>
10 = The Timer controller is operated in Toggle-output mode.
<br>
11 = The Timer controller is operated in Continuous Counting mode.
<br>
</div></td></tr><tr><td>
[29]</td><td>INTEN</td><td><div style="word-wrap: break-word;"><b>Timer Interrupt Enable Bit
</b><br>
0 = Timer time-out interrupt Disabled.
<br>
1 = Timer time-out interrupt Enabled.
<br>
Note: If this bit is enabled, when the timer time-out interrupt flag TIF is set to 1, the timer interrupt signal is generated and inform to CPU.
<br>
</div></td></tr><tr><td>
[30]</td><td>CNTEN</td><td><div style="word-wrap: break-word;"><b>Timer Counting Enable Bit
</b><br>
0 = Stops/Suspends counting.
<br>
1 = Starts counting.
<br>
Note1: In stop status, and then set CNTEN to 1 will enable the 24-bit up counter to keep counting from the last stop counting value.
<br>
Note2: This bit is auto-cleared by hardware in one-shot mode (TIMER_CTL[28:27] = 00) when the timer time-out interrupt flag TIF (TIMERx_INTSTS[0]) is generated.
<br>
Note3: Set enable/disable this bit needs 2 * TMR_CLK period to become active, user can read ACTSTS (TIMERx_CTL[25]) to check enable/disable command is completed or not.
<br>
</div></td></tr><tr><td>
[31]</td><td>ICEDEBUG</td><td><div style="word-wrap: break-word;"><b>ICE Debug Mode Acknowledge Disable Control (Write Protect)
</b><br>
0 = ICE debug mode acknowledgement effects TIMER counting.
<br>
TIMER counter will be held while CPU is held by ICE.
<br>
1 = ICE debug mode acknowledgement Disabled.
<br>
TIMER counter will keep going no matter CPU is held by ICE or not.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::CMP

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CMP
</font><br><p> <font size="2">
Offset: 0x04  Timer Comparator Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:0]</td><td>CMPDAT</td><td><div style="word-wrap: break-word;"><b>Timer Comparator Value
</b><br>
CMPDAT is a 24-bit compared value register
<br>
When the internal 24-bit up counter value is equal to CMPDAT value, the TIF (TIMERx_INTSTS[0] Timer Interrupt Flag) will set to 1.
<br>
Time-out period = (Period of timer clock input) * (8-bit PSC + 1) * (24-bit CMPDAT).
<br>
Note1: Never write 0x0 or 0x1 in CMPDAT field, or the core will run into unknown state.
<br>
Note2: When timer is operating at continuous counting mode, the 24-bit up counter will keep counting continuously even if user writes a new value into CMPDAT field
<br>
But if timer is operating at other modes, the 24-bit up counter will restart counting from 0 and using newest CMPDAT value to be the timer compared value while user writes a new value into CMPDAT field.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::INTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTSTS
</font><br><p> <font size="2">
Offset: 0x08  Timer Interrupt Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>TIF</td><td><div style="word-wrap: break-word;"><b>Timer Interrupt Flag
</b><br>
This bit indicates the interrupt flag status of Timer while 24-bit timer up counter CNT (TIMERx_CNT[23:0]) value reaches to CMPDAT (TIMERx_CMP[23:0]) value.
<br>
0 = No effect.
<br>
1 = CNT value matches the CMPDAT value.
<br>
Note: This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[1]</td><td>TWKF</td><td><div style="word-wrap: break-word;"><b>Timer Wake-up Flag
</b><br>
This bit indicates the interrupt wake-up flag status of timer.
<br>
0 = Timer does not cause CPU wake-up.
<br>
1 = CPU wake-up from Idle or Power-down mode if timer time-out interrupt signal generated.
<br>
Note: This bit is cleared by writing 1 to it.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::CNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CNT
</font><br><p> <font size="2">
Offset: 0x0C  Timer Data Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:0]</td><td>CNT</td><td><div style="word-wrap: break-word;"><b>Timer Data Register
</b><br>
Read operation.
<br>
Read this register to get CNT value. For example:
<br>
If EXTCNTEN (TIMERx_CTL[24] ) is 0, user can read CNT value for getting current 24-bit counter value.
<br>
If EXTCNTEN (TIMERx_CTL[24] ) is 1, user can read CNT value for getting current 24-bit event input counter value.
<br>
Write operation.
<br>
Writing any value to this register will reset current CNT value to 0 and reload internal 8-bit prescale counter.
<br>
</div></td></tr><tr><td>
[31]</td><td>RSTACT</td><td><div style="word-wrap: break-word;"><b>Timer Data Register Reset Active (Read Only)
</b><br>
This bit indicates if the counter reset operation active.
<br>
When user writes this CNT register, timer starts to reset its internal 24-bit timer up-counter to 0 and reload 8-bit pre-scale counter
<br>
At the same time, timer set this flag to 1 to indicate the counter reset operation is in progress
<br>
Once the counter reset operation done, timer clear this bit to 0 automatically.
<br>
0 = Reset operation is done.
<br>
1 = Reset operation triggered by writing TIMERx_CNT is in progress.
<br>
Note: This bit is read only.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::CAP

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAP
</font><br><p> <font size="2">
Offset: 0x10  Timer Capture Data Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:0]</td><td>CAPDAT</td><td><div style="word-wrap: break-word;"><b>Timer Capture Data Register
</b><br>
When CAPEN (TIMERx_EXTCTL[3]) bit is set, CAPFUNCS (TIMERx_EXTCTL[4]) bit is 0, and a transition on TMx_EXT pin matched the CAPEDGE (TIMERx_EXTCTL[14:12]) setting, CAPIF (TIMERx_EINTSTS[0]) will set to 1 and the current timer counter value CNT (TIMERx_CNT[23:0]) will be auto-loaded into this CAPDAT field.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::EXTCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EXTCTL
</font><br><p> <font size="2">
Offset: 0x14  Timer External Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CNTPHASE</td><td><div style="word-wrap: break-word;"><b>Timer External Count Phase
</b><br>
This bit indicates the detection phase of external counting pin TMx (x= 0~3).
<br>
0 = A falling edge of external counting pin will be counted.
<br>
1 = A rising edge of external counting pin will be counted.
<br>
</div></td></tr><tr><td>
[3]</td><td>CAPEN</td><td><div style="word-wrap: break-word;"><b>Timer External Capture Pin Enable Bit
</b><br>
This bit enables the TMx_EXT capture pin input function.
<br>
0 =TMx_EXT (x= 0~3) pin Disabled.
<br>
1 =TMx_EXT (x= 0~3) pin Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>CAPFUNCS</td><td><div style="word-wrap: break-word;"><b>Capture Function Selection
</b><br>
0 = External Capture Mode Enabled.
<br>
1 = External Reset Mode Enabled.
<br>
Note1: When CAPFUNCS is 0, transition on TMx_EXT (x= 0~3) pin is using to save current 24-bit timer counter value (CNT value) to CAPDAT field.
<br>
Note2: When CAPFUNCS is 1, transition on TMx_EXT (x= 0~3) pin is using to save current 24-bit timer counter value (CNT value) to CAPDAT field then CNT value will be reset immediately.
<br>
</div></td></tr><tr><td>
[5]</td><td>CAPIEN</td><td><div style="word-wrap: break-word;"><b>Timer External Capture Interrupt Enable Bit
</b><br>
0 = TMx_EXT (x= 0~3) pin detection Interrupt Disabled.
<br>
1 = TMx_EXT (x= 0~3) pin detection Interrupt Enabled.
<br>
Note: CAPIEN is used to enable timer external interrupt
<br>
If CAPIEN enabled, timer will rise an interrupt when CAPIF (TIMERx_EINTSTS[0]) is 1.
<br>
For example, while CAPIEN = 1, CAPEN = 1, and CAPEDGE = 00, a 1 to 0 transition on the TMx_EXT pin will cause the CAPIF to be set then the interrupt signal is generated and sent to NVIC to inform CPU.
<br>
</div></td></tr><tr><td>
[6]</td><td>CAPDBEN</td><td><div style="word-wrap: break-word;"><b>Timer External Capture Pin De-bounce Enable Bit
</b><br>
0 = TMx_EXT (x= 0~3) pin de-bounce or ACMP output de-bounce Disabled.
<br>
1 = TMx_EXT (x= 0~3) pin de-bounce or ACMP output de-bounce Enabled.
<br>
Note: If this bit is enabled, the edge detection of TMx_EXT pin or ACMP output is detected with de-bounce circuit.
<br>
</div></td></tr><tr><td>
[7]</td><td>CNTDBEN</td><td><div style="word-wrap: break-word;"><b>Timer Counter Pin De-bounce Enable Bit
</b><br>
0 = TMx (x= 0~3) pin de-bounce Disabled.
<br>
1 = TMx (x= 0~3) pin de-bounce Enabled.
<br>
Note: If this bit is enabled, the edge detection of TMx pin is detected with de-bounce circuit.
<br>
</div></td></tr><tr><td>
[8:10]</td><td>ICAPSEL</td><td><div style="word-wrap: break-word;"><b>Internal Capture Source Select
</b><br>
000 = Capture Function source is from internal ACMP0 output signal.
<br>
001 = Capture Function source is from internal ACMP1 output signal.
<br>
010 = Capture Function source is from HXT.
<br>
011 = Capture Function source is from LXT.
<br>
100 = Capture Function source is from HIRC.
<br>
101 = Capture Function source is from LIRC.
<br>
110 = Reserved.
<br>
111 = Reserved.
<br>
Note: these bits only available when CAPSRC (TIMERx_CTL[22]) is 1.
<br>
</div></td></tr><tr><td>
[14:12]</td><td>CAPEDGE</td><td><div style="word-wrap: break-word;"><b>Timer External Capture Pin Edge Detect
</b><br>
When first capture event is generated, the CNT (TIMERx_CNT[23:0]) will be reset to 0 and first CAPDAT (TIMERx_CAP[23:0]) should be to 0.
<br>
000 = Capture event occurred when detect falling edge transfer on TMx_EXT (x= 0~3) pin.
<br>
001 = Capture event occurred when detect rising edge transfer on TMx_EXT (x= 0~3) pin.
<br>
010 = Capture event occurred when detect both falling and rising edge transfer on TMx_EXT (x= 0~3) pin, and first capture event occurred at falling edge transfer.
<br>
011 = Capture event occurred when detect both rising and falling edge transfer on TMx_EXT (x= 0~3) pin, and first capture event occurred at rising edge transfer..
<br>
110 = First capture event occurred at falling edge, follows capture events are at rising edge transfer on TMx_EXT (x= 0~3) pin.
<br>
111 = First capture event occurred at rising edge, follows capture events are at falling edge transfer on TMx_EXT (x= 0~3) pin.
<br>
100, 101 = Reserved.
<br>
</div></td></tr><tr><td>
[16]</td><td>ECNTSSEL</td><td><div style="word-wrap: break-word;"><b>Event Counter Source Selection to Trigger Event Counter Function
</b><br>
0 = Event Counter input source is from TMx (x= 0~3) pin.
<br>
1 = Event Counter input source is from USB internal SOF output signal.
<br>
</div></td></tr><tr><td>
[31:28]</td><td>CAPDIVSCL</td><td><div style="word-wrap: break-word;"><b>Timer Capture Source Divider
</b><br>
This bits indicate the divide scale for capture source divider
<br>
0000 = Capture source/1.
<br>
0001 = Capture source/2.
<br>
0010 = Capture source/4.
<br>
0011 = Capture source/8.
<br>
0100 = Capture source/16.
<br>
0101 = Capture source/32.
<br>
0110 = Capture source/64.
<br>
0111 = Capture source/128.
<br>
1000 = Capture source/256.
<br>
1001~1111 = Reserved.
<br>
Note: Sets INTERCAPSEL (TIMERx_EXTCTL[10:8]) and CAPSRC (TIMERx_CTL[22]) to select capture source.     * @var TIMER_T::EINTSTS
<br>
xternal Interrupt Status Register
<br>
------------------------------------------------------------------------------
<br>
Descriptions
<br>
 :---- |
<br>
</div></td></tr><tr><td>
[0]</td><td>CAPIF</td><td><div style="word-wrap: break-word;"><b>Timer External Capture Interrupt Flag
</b><br>
This bit indicates the timer external capture interrupt flag status.
<br>
0 = TMx_EXT (x= 0~3) pin interrupt did not occur.
<br>
1 = TMx_EXT (x= 0~3) pin interrupt occurred.
<br>
Note1: This bit is cleared by writing 1 to it.
<br>
Note2: When CAPEN (TIMERx_EXTCTL[3]) bit is set, CAPFUNCS (TIMERx_EXTCTL[4]) bit is 0, and a transition on TMx_EXT (x= 0~3) pin matched the CAPEDGE (TIMERx_EXTCTL[2:1]) setting, this bit will set to 1 by hardware.
<br>
Note3: There is a new incoming capture event detected before CPU clearing the CAPIF status
<br>
If the above condition occurred, the Timer will keep register TIMERx_CAP unchanged and drop the new capture value.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::TRGCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TRGCTL
</font><br><p> <font size="2">
Offset: 0x1C  Timer Trigger Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>TRGSSEL</td><td><div style="word-wrap: break-word;"><b>Trigger Source Select Bit
</b><br>
This bit is used to select internal trigger source is form timer time-out interrupt signal or
<br>
capture interrupt signal.
<br>
0 = Time-out interrupt signal is used to internal trigger EPWM, BPWM, PDMA, DAC, and EADC.
<br>
1 = Capture interrupt signal is used to internal trigger EPWM, BPWM, PDMA, DAC, and EADC.
<br>
</div></td></tr><tr><td>
[1]</td><td>TRGEPWM</td><td><div style="word-wrap: break-word;"><b>Trigger EPWM and BPWM Enable Bit
</b><br>
If this bit is set to 1, each timer time-out event or capture event can be as EPWM and BPWM counter clock source.
<br>
0 = Timer interrupt trigger EPWM and BPWM Disabled.
<br>
1 = Timer interrupt trigger EPWM and BPWM Enabled.
<br>
Note: If TRGSSEL (TIMERx_TRGCTL[0]) = 0, time-out interrupt signal as EPWM and BPWM counter clock source.
<br>
If TRGSSEL (TIMERx_TRGCTL[0]) = 1, capture interrupt signal as EPWM counter clock source.
<br>
</div></td></tr><tr><td>
[2]</td><td>TRGEADC</td><td><div style="word-wrap: break-word;"><b>Trigger EADC Enable Bit
</b><br>
If this bit is set to 1, each timer time-out event or capture event can be triggered EADC conversion.
<br>
0 = Timer interrupt trigger EADC Disabled.
<br>
1 = Timer interrupt trigger EADC Enabled.
<br>
Note: If TRGSSEL (TIMERx_TRGCTL[0]) = 0, time-out interrupt signal will trigger EADC conversion.
<br>
If TRGSSEL (TIMERx_TRGCTL[0]) = 1, capture interrupt signal will trigger EADC conversion.
<br>
</div></td></tr><tr><td>
[3]</td><td>TRGDAC</td><td><div style="word-wrap: break-word;"><b>Trigger DAC Enable Bit
</b><br>
If this bit is set to 1, timer time-out interrupt or capture interrupt can be triggered DAC.
<br>
0 = Timer interrupt trigger DAC Disabled.
<br>
1 = Timer interrupt trigger DAC Enabled.
<br>
Note: If TRGSSEL (TIMERx_TRGCTL[0]) = 0, time-out interrupt signal will trigger DAC.
<br>
If TRGSSEL (TIMERx_TRGCTL[0]) = 1, capture interrupt signal will trigger DAC.
<br>
</div></td></tr><tr><td>
[4]</td><td>TRGPDMA</td><td><div style="word-wrap: break-word;"><b>Trigger PDMA Enable Bit
</b><br>
If this bit is set to 1, each timer time-out event or capture event can be triggered PDMA transfer.
<br>
0 = Timer interrupt trigger PDMA Disabled.
<br>
1 = Timer interrupt trigger PDMA Enabled.
<br>
Note: If TRGSSEL (TIMERx_TRGCTL[0]) = 0, time-out interrupt signal will trigger PDMA transfer.
<br>
If TRGSSEL (TIMERx_TRGCTL[0]) = 1, capture interrupt signal will trigger PDMA transfer.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::ALTCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ALTCTL
</font><br><p> <font size="2">
Offset: 0x20  Timer Alternative Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>FUNCSEL</td><td><div style="word-wrap: break-word;"><b>Function Selection
</b><br>
0 = Timer controller is used as timer function.
<br>
1 = Timer controller is used as PWM function.
<br>
Note: When timer is used as PWM, the clock source of time controller will be forced to PCLKx automatically.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMCTL
</font><br><p> <font size="2">
Offset: 0x40  Timer PWM Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CNTEN</td><td><div style="word-wrap: break-word;"><b>PWM Counter Enable Bit
</b><br>
0 = PWM counter and clock prescale Stop Running.
<br>
1 = PWM counter and clock prescale Start Running.
<br>
</div></td></tr><tr><td>
[2:1]</td><td>CNTTYPE</td><td><div style="word-wrap: break-word;"><b>PWM Counter Behavior Type
</b><br>
00 = Up count type.
<br>
01 = Down count type.
<br>
10 = Up-down count type.
<br>
11 = Reserved.
<br>
</div></td></tr><tr><td>
[3]</td><td>CNTMODE</td><td><div style="word-wrap: break-word;"><b>PWM Counter Mode
</b><br>
0 = Auto-reload mode.
<br>
1 = One-shot mode.
<br>
</div></td></tr><tr><td>
[8]</td><td>CTRLD</td><td><div style="word-wrap: break-word;"><b>Center Re-load
</b><br>
In up-down count type, PERIOD will load to PBUF when current PWM period is completed always and CMP will load to CMPBUF at the center point of current period.
<br>
</div></td></tr><tr><td>
[9]</td><td>IMMLDEN</td><td><div style="word-wrap: break-word;"><b>Immediately Load Enable Bit
</b><br>
0 = PERIOD will load to PBUF when current PWM period is completed no matter CTRLD is enabled/disabled
<br>
If CTRLD is disabled, CMP will load to CMPBUF when current PWM period is completed; if CTRLD is enabled in up-down count type, CMP will load to CMPBUF at the center point of current period.
<br>
1 = PERIOD/CMP will load to PBUF/CMPBUF immediately when user update PERIOD/CMP.
<br>
Note: If IMMLDEN is enabled, CTRLD will be invalid.
<br>
</div></td></tr><tr><td>
[16]</td><td>OUTMODE</td><td><div style="word-wrap: break-word;"><b>PWM Output Mode
</b><br>
This bit controls the output mode of corresponding PWM channel.
<br>
0 = PWM independent mode.
<br>
1 = PWM complementary mode.
<br>
</div></td></tr><tr><td>
[30]</td><td>DBGHALT</td><td><div style="word-wrap: break-word;"><b>ICE Debug Mode Counter Halt (Write Protect)
</b><br>
If debug mode counter halt is enabled, PWM counter will keep current value until exit ICE debug mode.
<br>
0 = ICE debug mode counter halt disable.
<br>
1 = ICE debug mode counter halt enable.
<br>
Note: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[31]</td><td>DBGTRIOFF</td><td><div style="word-wrap: break-word;"><b>ICE Debug Mode Acknowledge Disable Bit (Write Protect)
</b><br>
0 = ICE debug mode acknowledgement effects PWM output.
<br>
PWM output pin will be forced as tri-state while ICE debug mode acknowledged.
<br>
1 = ICE debug mode acknowledgement disabled.
<br>
PWM output pin will keep output no matter ICE debug mode acknowledged or not.
<br>
Note: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMCLKSRC

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMCLKSRC
</font><br><p> <font size="2">
Offset: 0x44  Timer PWM Counter Clock Source Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2:0]</td><td>CLKSRC</td><td><div style="word-wrap: break-word;"><b>PWM Counter Clock Source Select
</b><br>
The PWM counter clock source can be selected from TMRx_CLK or internal timer time-out or capture event.
<br>
000 = TMRx_CLK.
<br>
001 = Internal TIMER0 time-out or capture event.
<br>
010 = Internal TIMER1 time-out or capture event.
<br>
011 = Internal TIMER2 time-out or capture event.
<br>
100 = Internal TIMER3 time-out or capture event.
<br>
Others = Reserved.
<br>
Note: If TIMER0 PWM function is enabled, the PWM counter clock source can be selected from TMR0_CLK, TIMER1 interrupt events, TIMER2 interrupt events, or TIMER3 interrupt events.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMCLKPSC

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMCLKPSC
</font><br><p> <font size="2">
Offset: 0x48  Timer PWM Counter Clock Pre-scale Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[11:0]</td><td>CLKPSC</td><td><div style="word-wrap: break-word;"><b>PWM Counter Clock Pre-scale
</b><br>
The active clock of PWM counter is decided by counter clock prescale and divided by (CLKPSC + 1)
<br>
If CLKPSC is 0, then there is no scaling in PWM counter clock source.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMCNTCLR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMCNTCLR
</font><br><p> <font size="2">
Offset: 0x4C  Timer PWM Clear Counter Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CNTCLR</td><td><div style="word-wrap: break-word;"><b>Clear PWM Counter Control Bit
</b><br>
It is automatically cleared by hardware.
<br>
0 = No effect.
<br>
1 = Clear 16-bit PWM counter to 0x10000 in up and up-down count type and reset counter value to PERIOD in down count type.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMPERIOD

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMPERIOD
</font><br><p> <font size="2">
Offset: 0x50  Timer PWM Period Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>PERIOD</td><td><div style="word-wrap: break-word;"><b>PWM Period Register
</b><br>
In up count type: PWM counter counts from 0 to PERIOD, and restarts from 0.
<br>
In down count type: PWM counter counts from PERIOD to 0, and restarts from PERIOD.
<br>
In up-down count type: PWM counter counts from 0 to PERIOD, then decrements to 0 and repeats again.
<br>
In up and down count type:
<br>
PWM period time = (PERIOD + 1) * (CLKPSC + 1) * TMRx_PWMCLK.
<br>
In up-down count type:
<br>
PWM period time = 2 * PERIOD * (CLKPSC+ 1) * TMRx_PWMCLK.
<br>
Note: User should take care DIRF (TIMERx_PWMCNT[16]) bit in up/down/up-down count type to monitor current counter direction in each count type.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMCMPDAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMCMPDAT
</font><br><p> <font size="2">
Offset: 0x54  Timer PWM Comparator Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>CMP</td><td><div style="word-wrap: break-word;"><b>PWM Comparator Register
</b><br>
PWM CMP is used to compare with PWM CNT to generate PWM output waveform, interrupt events and trigger ADC to start convert.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMDTCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMDTCTL
</font><br><p> <font size="2">
Offset: 0x58  Timer PWM Dead-Time Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[11:0]</td><td>DTCNT</td><td><div style="word-wrap: break-word;"><b>Dead-time Counter (Write Protect)
</b><br>
The dead-time can be calculated from the following two formulas:
<br>
Dead-time = (DTCNT[11:0] + 1) * TMRx_PWMCLK, if DTCKSEL is 0.
<br>
Dead-time = (DTCNT[11:0] + 1) * TMRx_PWMCLK * (CLKPSC + 1), if DTCKSEL is 1.
<br>
Note: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[16]</td><td>DTEN</td><td><div style="word-wrap: break-word;"><b>Enable Dead-time Insertion for PWMx_CH0 and PWMx_CH1 (Write Protect)
</b><br>
Dead-time insertion function is only active when PWM complementary mode is enabled
<br>
If dead- time insertion is inactive, the outputs of PWMx_CH0 and PWMx_CH1 are complementary without any delay.
<br>
0 = Dead-time insertion Disabled on the pin pair.
<br>
1 = Dead-time insertion Enabled on the pin pair.
<br>
Note: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[24]</td><td>DTCKSEL</td><td><div style="word-wrap: break-word;"><b>Dead-time Clock Select (Write Protect)
</b><br>
0 = Dead-time clock source from TMRx_PWMCLK without counter clock prescale.
<br>
1 = Dead-time clock source from TMRx_PWMCLK with counter clock prescale.
<br>
Note: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMCNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMCNT
</font><br><p> <font size="2">
Offset: 0x5C  Timer PWM Counter Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>CNT</td><td><div style="word-wrap: break-word;"><b>PWM Counter Value Register (Read Only)
</b><br>
User can monitor CNT to know the current counter value in 16-bit period counter.
<br>
</div></td></tr><tr><td>
[16]</td><td>DIRF</td><td><div style="word-wrap: break-word;"><b>PWM Counter Direction Indicator Flag (Read Only)
</b><br>
0 = Counter is active in down count.
<br>
1 = Counter is active up count.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMMSKEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMMSKEN
</font><br><p> <font size="2">
Offset: 0x60  Timer PWM Output Mask Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>MSKEN0</td><td><div style="word-wrap: break-word;"><b>PWMx_CH0 Output Mask Enable Bit
</b><br>
The PWMx_CH0 output signal will be masked when this bit is enabled
<br>
The PWMx_CH0 will output MSKDAT0 (TIMER_PWMMSK[0]) data.
<br>
0 = PWMx_CH0 output signal is non-masked.
<br>
1 = PWMx_CH0 output signal is masked and output MSKDAT0 data.
<br>
</div></td></tr><tr><td>
[1]</td><td>MSKEN1</td><td><div style="word-wrap: break-word;"><b>PWMx_CH1 Output Mask Enable Bit
</b><br>
The PWMx_CH1 output signal will be masked when this bit is enabled
<br>
The PWMx_CH1 will output MSKDAT1 (TIMER_PWMMSK[1]) data.
<br>
0 = PWMx_CH1 output signal is non-masked.
<br>
1 = PWMx_CH1 output signal is masked and output MSKDAT1 data.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMMSK

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMMSK
</font><br><p> <font size="2">
Offset: 0x64  Timer PWM Output Mask Data Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>MSKDAT0</td><td><div style="word-wrap: break-word;"><b>PWMx_CH0 Output Mask Data Control Bit
</b><br>
This bit is used to control the output state of PWMx_CH0 pin when PWMx_CH0 output mask function is enabled (MSKEN0 = 1).
<br>
0 = Output logic Low to PWMx_CH0.
<br>
1 = Output logic High to PWMx_CH0.
<br>
</div></td></tr><tr><td>
[1]</td><td>MSKDAT1</td><td><div style="word-wrap: break-word;"><b>PWMx_CH1 Output Mask Data Control Bit
</b><br>
This bit is used to control the output state of PWMx_CH1 pin when PWMx_CH1 output mask function is enabled (MSKEN1 = 1).
<br>
0 = Output logic Low to PWMx_CH1.
<br>
1 = Output logic High to PWMx_CH1.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMBNF

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMBNF
</font><br><p> <font size="2">
Offset: 0x68  Timer PWM Brake Pin Noise Filter Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BRKNFEN</td><td><div style="word-wrap: break-word;"><b>Brake Pin Noise Filter Enable Bit
</b><br>
0 = Pin noise filter detect of PWMx_BRAKEy Disabled.
<br>
1 = Pin noise filter detect of PWMx_BRAKEy Enabled.
<br>
</div></td></tr><tr><td>
[3:1]</td><td>BRKNFSEL</td><td><div style="word-wrap: break-word;"><b>Brake Pin Noise Filter Clock Selection
</b><br>
000 = Noise filter clock is PCLKx.
<br>
001 = Noise filter clock is PCLKx/2.
<br>
010 = Noise filter clock is PCLKx/4.
<br>
011 = Noise filter clock is PCLKx/8.
<br>
100 = Noise filter clock is PCLKx/16.
<br>
101 = Noise filter clock is PCLKx/32.
<br>
110 = Noise filter clock is PCLKx/64.
<br>
111 = Noise filter clock is PCLKx/128.
<br>
</div></td></tr><tr><td>
[6:4]</td><td>BRKFCNT</td><td><div style="word-wrap: break-word;"><b>Brake Pin Noise Filter Count
</b><br>
The fields is used to control the active noise filter sample time.
<br>
Once noise filter sample time = (Period time of BRKDBCS) * BRKFCNT.
<br>
</div></td></tr><tr><td>
[7]</td><td>BRKPINV</td><td><div style="word-wrap: break-word;"><b>Brake Pin Detection Control Bit
</b><br>
0 = Brake pin event will be detected if PWMx_BRAKEy pin status transfer from low to high in edge-detect, or pin status is high in level-detect.
<br>
1 = Brake pin event will be detected if PWMx_BRAKEy pin status transfer from high to low in edge-detect, or pin status is low in level-detect .
<br>
</div></td></tr><tr><td>
[17:16]</td><td>BKPINSRC</td><td><div style="word-wrap: break-word;"><b>Brake Pin Source Select
</b><br>
00 = Brake pin source comes from PWM0_BRAKE0 pin.
<br>
01 = Brake pin source comes from PWM0_BRAKE1 pin.
<br>
10 = Brake pin source comes from PWM1_BRAKE0 pin.
<br>
11 = Brake pin source comes from PWM1_BRAKE1 pin.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMFAILBRK

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMFAILBRK
</font><br><p> <font size="2">
Offset: 0x6C  Timer PWM System Fail Brake Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CSSBRKEN</td><td><div style="word-wrap: break-word;"><b>Clock Security System Detection Trigger PWM Brake Function Enable Bit
</b><br>
0 = Brake Function triggered by clock fail detection Disabled.
<br>
1 = Brake Function triggered by clock fail detection Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>BODBRKEN</td><td><div style="word-wrap: break-word;"><b>Brown-out Detection Trigger PWM Brake Function Enable Bit
</b><br>
0 = Brake Function triggered by BOD event Disabled.
<br>
1 = Brake Function triggered by BOD event Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>RAMBRKEN</td><td><div style="word-wrap: break-word;"><b>SRAM Parity Error Detection Trigger PWM Brake Function Enable Bit
</b><br>
0 = Brake Function triggered by SRAM parity error detection Disabled.
<br>
1 = Brake Function triggered by SRAM parity error detection Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>CORBRKEN</td><td><div style="word-wrap: break-word;"><b>Core Lockup Detection Trigger PWM Brake Function Enable Bit
</b><br>
0 = Brake Function triggered by core lockup event Disabled.
<br>
1 = Brake Function triggered by core lockup event Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMBRKCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMBRKCTL
</font><br><p> <font size="2">
Offset: 0x70  Timer PWM Brake Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CPO0EBEN</td><td><div style="word-wrap: break-word;"><b>Enable Internal ACMP0_O Digital Output As Edge-detect Brake Source (Write Protect)
</b><br>
0 = Internal ACMP0_O signal as edge-detect brake source Disabled.
<br>
1 = Internal ACMP0_O signal as edge-detect brake source Enabled.
<br>
Note1: Only internal ACMP0_O signal from low to high will be detected as brake event.
<br>
Note2: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[1]</td><td>CPO1EBEN</td><td><div style="word-wrap: break-word;"><b>Enable Internal ACMP1_O Digital Output As Edge-detect Brake Source (Write Protect)
</b><br>
0 = Internal ACMP1_O signal as edge-detect brake source Disabled.
<br>
1 = Internal ACMP1_O signal as edge-detect brake source Enabled.
<br>
Note1: Only internal ACMP1_O signal from low to high will be detected as brake event.
<br>
Note2: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[4]</td><td>BRKPEEN</td><td><div style="word-wrap: break-word;"><b>Enable TM_BRAKEx Pin As Edge-detect Brake Source (Write Protect)
</b><br>
0 = PWMx_BRAKEy pin event as edge-detect brake source Disabled.
<br>
1 = PWMx_BRAKEy pin event as edge-detect brake source Enabled.
<br>
Note: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[7]</td><td>SYSEBEN</td><td><div style="word-wrap: break-word;"><b>Enable System Fail As Edge-detect Brake Source (Write Protect)
</b><br>
0 = System fail condition as edge-detect brake source Disabled.
<br>
1 = System fail condition as edge-detect brake source Enabled.
<br>
Note: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[8]</td><td>CPO0LBEN</td><td><div style="word-wrap: break-word;"><b>Enable Internal ACMP0_O Digital Output As Level-detect Brake Source (Write Protect)
</b><br>
0 = Internal ACMP0_O signal as level-detect brake source Disabled.
<br>
1 = Internal ACMP0_O signal as level-detect brake source Enabled.
<br>
Note1: Only internal ACMP0_O signal from low to high will be detected as brake event.
<br>
Note2: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[9]</td><td>CPO1LBEN</td><td><div style="word-wrap: break-word;"><b>Enable Internal ACMP1_O Digital Output As Level-detect Brake Source (Write Protect)
</b><br>
0 = Internal ACMP1_O signal as level-detect brake source Disabled.
<br>
1 = Internal ACMP1_O signal as level-detect brake source Enabled.
<br>
Note1: Only internal ACMP1_O signal from low to high will be detected as brake event.
<br>
Note: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[12]</td><td>BRKPLEN</td><td><div style="word-wrap: break-word;"><b>Enable TM_BRAKEx Pin As Level-detect Brake Source (Write Protect)
</b><br>
0 = PWMx_BRAKEy pin event as level-detect brake source Disabled.
<br>
1 = PWMx_BRAKEy pin event as level-detect brake source Enabled.
<br>
Note: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[15]</td><td>SYSLBEN</td><td><div style="word-wrap: break-word;"><b>Enable System Fail As Level-detect Brake Source (Write Protect)
</b><br>
0 = System fail condition as level-detect brake source Disabled.
<br>
1 = System fail condition as level-detect brake source Enabled.
<br>
Note: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[17:16]</td><td>BRKAEVEN</td><td><div style="word-wrap: break-word;"><b>PWM Brake Action Select for PWMx_CH0 (Write Protect)
</b><br>
00 = PWMx_BRAKEy brake event will not affect PWMx_CH0 output.
<br>
01 = PWMx_CH0 output tri-state when PWMx_BRAKEy brake event happened.
<br>
10 = PWMx_CH0 output low level when PWMx_BRAKEy brake event happened.
<br>
11 = PWMx_CH0 output high level when PWMx_BRAKEy brake event happened.
<br>
Note: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[19:18]</td><td>BRKAODD</td><td><div style="word-wrap: break-word;"><b>PWM Brake Action Select for PWMx_CH1 (Write Protect)
</b><br>
00 = PWMx_BRAKEy brake event will not affect PWMx_CH1 output.
<br>
01 = PWMx_CH1 output tri-state when PWMx_BRAKEy brake event happened.
<br>
10 = PWMx_CH1 output low level when PWMx_BRAKEy brake event happened.
<br>
11 = PWMx_CH1 output high level when PWMx_BRAKEy brake event happened.
<br>
Note: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMPOLCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMPOLCTL
</font><br><p> <font size="2">
Offset: 0x74  Timer PWM Pin Output Polar Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>PINV0</td><td><div style="word-wrap: break-word;"><b>PWMx_CH0 Output Pin Polar Control Bit
</b><br>
The bit is used to control polarity state of PWMx_CH0 output pin.
<br>
0 = PWMx_CH0 output pin polar inverse Disabled.
<br>
1 = PWMx_CH0 output pin polar inverse Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>PINV1</td><td><div style="word-wrap: break-word;"><b>PWMx_CH1 Output Pin Polar Control Bit
</b><br>
The bit is used to control polarity state of PWMx_CH1 output pin.
<br>
0 = PWMx_CH1 output pin polar inverse Disabled.
<br>
1 = PWMx_CH1 output pin polar inverse Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMPOEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMPOEN
</font><br><p> <font size="2">
Offset: 0x78  Timer PWM Pin Output Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>POEN0</td><td><div style="word-wrap: break-word;"><b>PWMx_CH0 Output Pin Enable Bit
</b><br>
0 = PWMx_CH0 pin at tri-state mode.
<br>
1 = PWMx_CH0 pin in output mode.
<br>
</div></td></tr><tr><td>
[1]</td><td>POEN1</td><td><div style="word-wrap: break-word;"><b>PWMx_CH1 Output Pin Enable Bit
</b><br>
0 = PWMx_CH1 pin at tri-state mode.
<br>
1 = PWMx_CH1 pin in output mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMSWBRK

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMSWBRK
</font><br><p> <font size="2">
Offset: 0x7C  Timer PWM Software Trigger Brake Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BRKETRG</td><td><div style="word-wrap: break-word;"><b>Software Trigger Edge-detect Brake Source (Write Only) (Write Protect)
</b><br>
Write 1 to this bit will trigger PWM edge-detect brake source, then BRKEIF0 and BRKEIF1 will set to 1 automatically in TIMERx_PWMINTSTS1 register.
<br>
Note: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[8]</td><td>BRKLTRG</td><td><div style="word-wrap: break-word;"><b>Software Trigger Level-detect Brake Source (Write Only) (Write Protect)
</b><br>
Write 1 to this bit will trigger PWM level-detect brake source, then BRKLIF0 and BRKLIF1 will set to 1 automatically in TIMERx_PWMINTSTS1 register.
<br>
Note: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMINTEN0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMINTEN0
</font><br><p> <font size="2">
Offset: 0x80  Timer PWM Interrupt Enable Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ZIEN</td><td><div style="word-wrap: break-word;"><b>PWM Zero Point Interrupt Enable Bit
</b><br>
0 = Zero point interrupt Disabled.
<br>
1 = Zero point interrupt Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>PIEN</td><td><div style="word-wrap: break-word;"><b>PWM Period Point Interrupt Enable Bit
</b><br>
0 = Period point interrupt Disabled.
<br>
1 = Period point interrupt Enabled.
<br>
Note: When in up-down count type, period point means the center point of current PWM period.
<br>
</div></td></tr><tr><td>
[2]</td><td>CMPUIEN</td><td><div style="word-wrap: break-word;"><b>PWM Compare Up Count Interrupt Enable Bit
</b><br>
0 = Compare up count interrupt Disabled.
<br>
1 = Compare up count interrupt Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>CMPDIEN</td><td><div style="word-wrap: break-word;"><b>PWM Compare Down Count Interrupt Enable Bit
</b><br>
0 = Compare down count interrupt Disabled.
<br>
1 = Compare down count interrupt Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMINTEN1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMINTEN1
</font><br><p> <font size="2">
Offset: 0x84  Timer PWM Interrupt Enable Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BRKEIEN</td><td><div style="word-wrap: break-word;"><b>PWM Edge-detect Brake Interrupt Enable (Write Protect)
</b><br>
0 = PWM edge-detect brake interrupt Disabled.
<br>
1 = PWM edge-detect brake interrupt Enabled.
<br>
Note: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[8]</td><td>BRKLIEN</td><td><div style="word-wrap: break-word;"><b>PWM Level-detect Brake Interrupt Enable (Write Protect)
</b><br>
0 = PWM level-detect brake interrupt Disabled.
<br>
1 = PWM level-detect brake interrupt Enabled.
<br>
Note: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMINTSTS0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMINTSTS0
</font><br><p> <font size="2">
Offset: 0x88  Timer PWM Interrupt Status Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ZIF</td><td><div style="word-wrap: break-word;"><b>PWM Zero Point Interrupt Flag
</b><br>
This bit is set by hardware when TIMERx_PWM counter reaches zero.
<br>
Note: This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[1]</td><td>PIF</td><td><div style="word-wrap: break-word;"><b>PWM Period Point Interrupt Flag
</b><br>
This bit is set by hardware when TIMERx_PWM counter reaches PERIOD.
<br>
Note1: When in up-down count type, PIF flag means the center point flag of current PWM period.
<br>
Note2: This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[2]</td><td>CMPUIF</td><td><div style="word-wrap: break-word;"><b>PWM Compare Up Count Interrupt Flag
</b><br>
This bit is set by hardware when TIMERx_PWM counter in up count direction and reaches CMP.
<br>
Note1: If CMP equal to PERIOD, there is no CMPUIF flag in up count type and up-down count type.
<br>
Note2: This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[3]</td><td>CMPDIF</td><td><div style="word-wrap: break-word;"><b>PWM Compare Down Count Interrupt Flag
</b><br>
This bit is set by hardware when TIMERx_PWM counter in down count direction and reaches CMP.
<br>
Note1: If CMP equal to PERIOD, there is no CMPDIF flag in down count type.
<br>
Note2: This bit is cleared by writing 1 to it.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMINTSTS1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMINTSTS1
</font><br><p> <font size="2">
Offset: 0x8C  Timer PWM Interrupt Status Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BRKEIF0</td><td><div style="word-wrap: break-word;"><b>Edge-detect Brake Interrupt Flag on PWMx_CH0 (Write Protect)
</b><br>
0 = PWMx_CH0 edge-detect brake event do not happened.
<br>
1 = PWMx_CH0 edge-detect brake event happened.
<br>
Note1: This bit is cleared by writing 1 to it.
<br>
Note2: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[1]</td><td>BRKEIF1</td><td><div style="word-wrap: break-word;"><b>Edge-detect Brake Interrupt Flag PWMx_CH1 (Write Protect)
</b><br>
0 = PWMx_CH1 edge-detect brake event do not happened.
<br>
1 = PWMx_CH1 edge-detect brake event happened.
<br>
Note1: This bit is cleared by writing 1 to it.
<br>
Note2: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[8]</td><td>BRKLIF0</td><td><div style="word-wrap: break-word;"><b>Level-detect Brake Interrupt Flag on PWMx_CH0 (Write Protect)
</b><br>
0 = PWMx_CH0 level-detect brake event do not happened.
<br>
1 = PWMx_CH0 level-detect brake event happened.
<br>
Note1: This bit is cleared by writing 1 to it.
<br>
Note2: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[9]</td><td>BRKLIF1</td><td><div style="word-wrap: break-word;"><b>Level-detect Brake Interrupt Flag on PWMx_CH1 (Write Protect)
</b><br>
0 = PWMx_CH1 level-detect brake event do not happened.
<br>
1 = PWMx_CH1 level-detect brake event happened.
<br>
Note1: This bit is cleared by writing 1 to it.
<br>
Note2: This register is write protected. Refer toSYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[16]</td><td>BRKESTS0</td><td><div style="word-wrap: break-word;"><b>Edge -detect Brake Status of PWMx_CH0 (Read Only)
</b><br>
0 = PWMx_CH0 edge-detect brake state is released.
<br>
1 = PWMx_CH0 at edge-detect brake state.
<br>
Note: User can set BRKEIF0 1 to clear BRKEIF0 flag and PWMx_CH0 will release brake state when current PWM period finished and resume PWMx_CH0 output waveform start from next full PWM period.
<br>
</div></td></tr><tr><td>
[17]</td><td>BRKESTS1</td><td><div style="word-wrap: break-word;"><b>Edge-detect Brake Status of PWMx_CH1 (Read Only)
</b><br>
0 = PWMx_CH1 edge-detect brake state is released.
<br>
1 = PWMx_CH1 at edge-detect brake state.
<br>
Note: User can set BRKEIF1 1 to clear BRKEIF1 flag and PWMx_CH1 will release brake state when current PWM period finished and resume PWMx_CH1 output waveform start from next full PWM period.
<br>
</div></td></tr><tr><td>
[24]</td><td>BRKLSTS0</td><td><div style="word-wrap: break-word;"><b>Level-detect Brake Status of PWMx_CH0 (Read Only)
</b><br>
0 = PWMx_CH0 level-detect brake state is released.
<br>
1 = PWMx_CH0 at level-detect brake state.
<br>
Note: If TIMERx_PWM level-detect brake source has released, both PWMx_CH0 and PWMx_CH1 will release brake state when current PWM period finished and resume PWMx_CH0 and PWMx_CH1 output waveform start from next full PWM period.
<br>
</div></td></tr><tr><td>
[25]</td><td>BRKLSTS1</td><td><div style="word-wrap: break-word;"><b>Level-detect Brake Status of PWMx_CH1 (Read Only)
</b><br>
0 = PWMx_CH1 level-detect brake state is released.
<br>
1 = PWMx_CH1 at level-detect brake state.
<br>
Note: If TIMERx_PWM level-detect brake source has released, both PWMx_CH0 and PWMx_CH1 will release brake state when current PWM period finished and resume PWMx_CH0 and PWMx_CH1 output waveform start from next full PWM period.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMEADCTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMEADCTS
</font><br><p> <font size="2">
Offset: 0x90  Timer PWM ADC Trigger Source Select Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2:0]</td><td>TRGSEL</td><td><div style="word-wrap: break-word;"><b>PWM Counter Event Source Select to Trigger EADC Conversion
</b><br>
000 = Trigger EADC conversion at zero point (ZIF).
<br>
001 = Trigger EADC conversion at period point (PIF).
<br>
010 = Trigger EADC conversion at zero or period point (ZIF or PIF).
<br>
011 = Trigger EADC conversion at compare up count point (CMPUIF).
<br>
100 = Trigger EADC conversion at compare down count point (CMPDIF).
<br>
Others = Reserved.
<br>
</div></td></tr><tr><td>
[7]</td><td>TRGEN</td><td><div style="word-wrap: break-word;"><b>PWM Counter Event Trigger EADC Conversion Enable Bit
</b><br>
0 = PWM counter event trigger EADC conversion Disabled.
<br>
1 = PWM counter event trigger EADC conversion Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMSCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMSCTL
</font><br><p> <font size="2">
Offset: 0x94  Timer PWM Synchronous Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1:0]</td><td>SYNCMODE</td><td><div style="word-wrap: break-word;"><b>PWM Synchronous Mode Enable Select
</b><br>
00 = PWM synchronous function Disabled.
<br>
01 = PWM synchronous counter start function Enabled.
<br>
10 = Reserved.
<br>
11 = PWM synchronous counter clear function Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>SYNCSRC</td><td><div style="word-wrap: break-word;"><b>PWM Synchronous Counter Start/Clear Source Select
</b><br>
0 = Counter synchronous start/clear by trigger TIMER0_PWMSTRG STRGEN.
<br>
1 = Counter synchronous start/clear by trigger TIMER2_PWMSTRG STRGEN.
<br>
Note1: If TIMER0/1/2/3 PWM counter synchronous source are from TIMER0, TIMER0_PWMSCTL[8], TIMER1_PWMSCTL[8], TIMER2_PWMSCTL[8] and TIMER3_PWMSCTL[8] should be 0.
<br>
Note2: If TIMER0/1/ PWM counter synchronous source are from TIMER0, TIMER0_PWMSCTL[8] and TIMER1_PWMSCTL[8] should be set 0, and TIMER2/3/ PWM counter synchronous source are from TIMER2, TIME2_PWMSCTL[8] and TIMER3_PWMSCTL[8] should be set 1.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMSTRG

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMSTRG
</font><br><p> <font size="2">
Offset: 0x98  Timer PWM Synchronous Trigger Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>STRGEN</td><td><div style="word-wrap: break-word;"><b>PWM Counter Synchronous Trigger Enable Bit (Write Only)
</b><br>
PMW counter synchronous function is used to make selected PWM channels (include TIMER0/1/2/3 PWM, TIMER0/1 PWM and TIMER2/3 PWM) start counting or clear counter at the same time according to TIMERx_PWMSCTL setting.
<br>
Note: This bit is only available in TIMER0 and TIMER2.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMSTATUS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMSTATUS
</font><br><p> <font size="2">
Offset: 0x9C  Timer PWM Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CNTMAXF</td><td><div style="word-wrap: break-word;"><b>PWM Counter Equal to 0xFFFF Flag
</b><br>
0 = Indicates the PWM counter value never reached its maximum value 0xFFFF.
<br>
1 = Indicates the PWM counter value has reached its maximum value.
<br>
Note: This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[16]</td><td>EADCTRGF</td><td><div style="word-wrap: break-word;"><b>Trigger EADC Start Conversion Flag
</b><br>
0 = PWM counter event trigger EADC start conversion is not occurred.
<br>
1 = PWM counter event trigger EADC start conversion has occurred.
<br>
Note: This bit is cleared by writing 1 to it.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMPBUF

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMPBUF
</font><br><p> <font size="2">
Offset: 0xA0  Timer PWM Period Buffer Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>PBUF</td><td><div style="word-wrap: break-word;"><b>PWM Period Buffer Register (Read Only)
</b><br>
Used as PERIOD active register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var TIMER_T::PWMCMPBUF

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWMCMPBUF
</font><br><p> <font size="2">
Offset: 0xA4  Timer PWM Comparator Buffer Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>CMPBUF</td><td><div style="word-wrap: break-word;"><b>PWM Comparator Buffer Register (Read Only)
</b><br>
Used as CMP active register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CTL;                   /*!< [0x0000] Timer Control Register                                           */
    __IO uint32_t CMP;                   /*!< [0x0004] Timer Comparator Register                                        */
    __IO uint32_t INTSTS;                /*!< [0x0008] Timer Interrupt Status Register                                  */
    __IO uint32_t CNT;                   /*!< [0x000c] Timer Data Register                                              */
    __I  uint32_t CAP;                   /*!< [0x0010] Timer Capture Data Register                                      */
    __IO uint32_t EXTCTL;                /*!< [0x0014] Timer External Control Register                                  */
    __IO uint32_t EINTSTS;               /*!< [0x0018] Timer External Interrupt Status Register                         */
    __IO uint32_t TRGCTL;                /*!< [0x001c] Timer Trigger Control Register                                   */
    __IO uint32_t ALTCTL;                /*!< [0x0020] Timer Alternative Control Register                               */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE0[7];
    /** @endcond */
    __IO uint32_t PWMCTL;                /*!< [0x0040] Timer PWM Control Register                                       */
    __IO uint32_t PWMCLKSRC;             /*!< [0x0044] Timer PWM Counter Clock Source Register                          */
    __IO uint32_t PWMCLKPSC;             /*!< [0x0048] Timer PWM Counter Clock Pre-scale Register                       */
    __IO uint32_t PWMCNTCLR;             /*!< [0x004c] Timer PWM Clear Counter Register                                 */
    __IO uint32_t PWMPERIOD;             /*!< [0x0050] Timer PWM Period Register                                        */
    __IO uint32_t PWMCMPDAT;             /*!< [0x0054] Timer PWM Comparator Register                                    */
    __IO uint32_t PWMDTCTL;              /*!< [0x0058] Timer PWM Dead-Time Control Register                             */
    __I  uint32_t PWMCNT;                /*!< [0x005c] Timer PWM Counter Register                                       */
    __IO uint32_t PWMMSKEN;              /*!< [0x0060] Timer PWM Output Mask Enable Register                            */
    __IO uint32_t PWMMSK;                /*!< [0x0064] Timer PWM Output Mask Data Control Register                      */
    __IO uint32_t PWMBNF;                /*!< [0x0068] Timer PWM Brake Pin Noise Filter Register                        */
    __IO uint32_t PWMFAILBRK;            /*!< [0x006c] Timer PWM System Fail Brake Control Register                     */
    __IO uint32_t PWMBRKCTL;             /*!< [0x0070] Timer PWM Brake Control Register                                 */
    __IO uint32_t PWMPOLCTL;             /*!< [0x0074] Timer PWM Pin Output Polar Control Register                      */
    __IO uint32_t PWMPOEN;               /*!< [0x0078] Timer PWM Pin Output Enable Register                             */
    __O  uint32_t PWMSWBRK;              /*!< [0x007c] Timer PWM Software Trigger Brake Control Register                */
    __IO uint32_t PWMINTEN0;             /*!< [0x0080] Timer PWM Interrupt Enable Register 0                            */
    __IO uint32_t PWMINTEN1;             /*!< [0x0084] Timer PWM Interrupt Enable Register 1                            */
    __IO uint32_t PWMINTSTS0;            /*!< [0x0088] Timer PWM Interrupt Status Register 0                            */
    __IO uint32_t PWMINTSTS1;            /*!< [0x008c] Timer PWM Interrupt Status Register 1                            */
    __IO uint32_t PWMEADCTS;             /*!< [0x0090] Timer PWM EADC Trigger Source Select Register                    */
    __IO uint32_t PWMSCTL;               /*!< [0x0094] Timer PWM Synchronous Control Register                           */
    __O  uint32_t PWMSTRG;               /*!< [0x0098] Timer PWM Synchronous Trigger Register                           */
    __IO uint32_t PWMSTATUS;             /*!< [0x009c] Timer PWM Status Register                                        */
    __I  uint32_t PWMPBUF;               /*!< [0x00a0] Timer PWM Period Buffer Register                                 */
    __I  uint32_t PWMCMPBUF;             /*!< [0x00a4] Timer PWM Comparator Buffer Register                             */

} TIMER_T;

/**
    @addtogroup TIMER_CONST TIMER Bit Field Definition
    Constant Definitions for TIMER Controller
@{ */

#define TIMER_CTL_PSC_Pos                (0)                                               /*!< TIMER_T::CTL: PSC Position             */
#define TIMER_CTL_PSC_Msk                (0xfful << TIMER_CTL_PSC_Pos)                     /*!< TIMER_T::CTL: PSC Mask                 */

#define TIMER_CTL_INTRGEN_Pos            (19)                                              /*!< TIMER_T::CTL: INTRGEN Position         */
#define TIMER_CTL_INTRGEN_Msk            (0x1ul << TIMER_CTL_INTRGEN_Pos)                  /*!< TIMER_T::CTL: INTRGEN Mask             */

#define TIMER_CTL_PERIOSEL_Pos           (20)                                              /*!< TIMER_T::CTL: PERIOSEL Position        */
#define TIMER_CTL_PERIOSEL_Msk           (0x1ul << TIMER_CTL_PERIOSEL_Pos)                 /*!< TIMER_T::CTL: PERIOSEL Mask            */

#define TIMER_CTL_TGLPINSEL_Pos          (21)                                              /*!< TIMER_T::CTL: TGLPINSEL Position       */
#define TIMER_CTL_TGLPINSEL_Msk          (0x1ul << TIMER_CTL_TGLPINSEL_Pos)                /*!< TIMER_T::CTL: TGLPINSEL Mask           */

#define TIMER_CTL_CAPSRC_Pos             (22)                                              /*!< TIMER_T::CTL: CAPSRC Position          */
#define TIMER_CTL_CAPSRC_Msk             (0x1ul << TIMER_CTL_CAPSRC_Pos)                   /*!< TIMER_T::CTL: CAPSRC Mask              */

#define TIMER_CTL_WKEN_Pos               (23)                                              /*!< TIMER_T::CTL: WKEN Position            */
#define TIMER_CTL_WKEN_Msk               (0x1ul << TIMER_CTL_WKEN_Pos)                     /*!< TIMER_T::CTL: WKEN Mask                */

#define TIMER_CTL_EXTCNTEN_Pos           (24)                                              /*!< TIMER_T::CTL: EXTCNTEN Position        */
#define TIMER_CTL_EXTCNTEN_Msk           (0x1ul << TIMER_CTL_EXTCNTEN_Pos)                 /*!< TIMER_T::CTL: EXTCNTEN Mask            */

#define TIMER_CTL_ACTSTS_Pos             (25)                                              /*!< TIMER_T::CTL: ACTSTS Position          */
#define TIMER_CTL_ACTSTS_Msk             (0x1ul << TIMER_CTL_ACTSTS_Pos)                   /*!< TIMER_T::CTL: ACTSTS Mask              */

#define TIMER_CTL_OPMODE_Pos             (27)                                              /*!< TIMER_T::CTL: OPMODE Position          */
#define TIMER_CTL_OPMODE_Msk             (0x3ul << TIMER_CTL_OPMODE_Pos)                   /*!< TIMER_T::CTL: OPMODE Mask              */

#define TIMER_CTL_INTEN_Pos              (29)                                              /*!< TIMER_T::CTL: INTEN Position           */
#define TIMER_CTL_INTEN_Msk              (0x1ul << TIMER_CTL_INTEN_Pos)                    /*!< TIMER_T::CTL: INTEN Mask               */

#define TIMER_CTL_CNTEN_Pos              (30)                                              /*!< TIMER_T::CTL: CNTEN Position           */
#define TIMER_CTL_CNTEN_Msk              (0x1ul << TIMER_CTL_CNTEN_Pos)                    /*!< TIMER_T::CTL: CNTEN Mask               */

#define TIMER_CTL_ICEDEBUG_Pos           (31)                                              /*!< TIMER_T::CTL: ICEDEBUG Position        */
#define TIMER_CTL_ICEDEBUG_Msk           (0x1ul << TIMER_CTL_ICEDEBUG_Pos)                 /*!< TIMER_T::CTL: ICEDEBUG Mask            */

#define TIMER_CMP_CMPDAT_Pos             (0)                                               /*!< TIMER_T::CMP: CMPDAT Position          */
#define TIMER_CMP_CMPDAT_Msk             (0xfffffful << TIMER_CMP_CMPDAT_Pos)              /*!< TIMER_T::CMP: CMPDAT Mask              */

#define TIMER_INTSTS_TIF_Pos             (0)                                               /*!< TIMER_T::INTSTS: TIF Position          */
#define TIMER_INTSTS_TIF_Msk             (0x1ul << TIMER_INTSTS_TIF_Pos)                   /*!< TIMER_T::INTSTS: TIF Mask              */

#define TIMER_INTSTS_TWKF_Pos            (1)                                               /*!< TIMER_T::INTSTS: TWKF Position         */
#define TIMER_INTSTS_TWKF_Msk            (0x1ul << TIMER_INTSTS_TWKF_Pos)                  /*!< TIMER_T::INTSTS: TWKF Mask             */

#define TIMER_CNT_CNT_Pos                (0)                                               /*!< TIMER_T::CNT: CNT Position             */
#define TIMER_CNT_CNT_Msk                (0xfffffful << TIMER_CNT_CNT_Pos)                 /*!< TIMER_T::CNT: CNT Mask                 */

#define TIMER_CNT_RSTACT_Pos             (31)                                              /*!< TIMER_T::CNT: RSTACT Position          */
#define TIMER_CNT_RSTACT_Msk             (0x1ul << TIMER_CNT_RSTACT_Pos)                   /*!< TIMER_T::CNT: RSTACT Mask              */

#define TIMER_CAP_CAPDAT_Pos             (0)                                               /*!< TIMER_T::CAP: CAPDAT Position          */
#define TIMER_CAP_CAPDAT_Msk             (0xfffffful << TIMER_CAP_CAPDAT_Pos)              /*!< TIMER_T::CAP: CAPDAT Mask              */

#define TIMER_EXTCTL_CNTPHASE_Pos        (0)                                               /*!< TIMER_T::EXTCTL: CNTPHASE Position     */
#define TIMER_EXTCTL_CNTPHASE_Msk        (0x1ul << TIMER_EXTCTL_CNTPHASE_Pos)              /*!< TIMER_T::EXTCTL: CNTPHASE Mask         */

#define TIMER_EXTCTL_CAPEN_Pos           (3)                                               /*!< TIMER_T::EXTCTL: CAPEN Position        */
#define TIMER_EXTCTL_CAPEN_Msk           (0x1ul << TIMER_EXTCTL_CAPEN_Pos)                 /*!< TIMER_T::EXTCTL: CAPEN Mask            */

#define TIMER_EXTCTL_CAPFUNCS_Pos        (4)                                               /*!< TIMER_T::EXTCTL: CAPFUNCS Position     */
#define TIMER_EXTCTL_CAPFUNCS_Msk        (0x1ul << TIMER_EXTCTL_CAPFUNCS_Pos)              /*!< TIMER_T::EXTCTL: CAPFUNCS Mask         */

#define TIMER_EXTCTL_CAPIEN_Pos          (5)                                               /*!< TIMER_T::EXTCTL: CAPIEN Position       */
#define TIMER_EXTCTL_CAPIEN_Msk          (0x1ul << TIMER_EXTCTL_CAPIEN_Pos)                /*!< TIMER_T::EXTCTL: CAPIEN Mask           */

#define TIMER_EXTCTL_CAPDBEN_Pos         (6)                                               /*!< TIMER_T::EXTCTL: CAPDBEN Position      */
#define TIMER_EXTCTL_CAPDBEN_Msk         (0x1ul << TIMER_EXTCTL_CAPDBEN_Pos)               /*!< TIMER_T::EXTCTL: CAPDBEN Mask          */

#define TIMER_EXTCTL_CNTDBEN_Pos         (7)                                               /*!< TIMER_T::EXTCTL: CNTDBEN Position      */
#define TIMER_EXTCTL_CNTDBEN_Msk         (0x1ul << TIMER_EXTCTL_CNTDBEN_Pos)               /*!< TIMER_T::EXTCTL: CNTDBEN Mask          */

#define TIMER_EXTCTL_ICAPSEL_Pos         (8)                                               /*!< TIMER_T::EXTCTL: ICAPSEL Position      */
#define TIMER_EXTCTL_ICAPSEL_Msk         (0x7ul << TIMER_EXTCTL_ICAPSEL_Pos)               /*!< TIMER_T::EXTCTL: ICAPSEL Mask          */

#define TIMER_EXTCTL_CAPEDGE_Pos         (12)                                              /*!< TIMER_T::EXTCTL: CAPEDGE Position      */
#define TIMER_EXTCTL_CAPEDGE_Msk         (0x7ul << TIMER_EXTCTL_CAPEDGE_Pos)               /*!< TIMER_T::EXTCTL: CAPEDGE Mask          */

#define TIMER_EXTCTL_ECNTSSEL_Pos        (16)                                              /*!< TIMER_T::EXTCTL: ECNTSSEL Position     */
#define TIMER_EXTCTL_ECNTSSEL_Msk        (0x1ul << TIMER_EXTCTL_ECNTSSEL_Pos)              /*!< TIMER_T::EXTCTL: ECNTSSEL Mask         */

#define TIMER_EXTCTL_CAPDIVSCL_Pos       (28)                                              /*!< TIMER_T::EXTCTL: CAPDIVSCL Position     */
#define TIMER_EXTCTL_CAPDIVSCL_Msk       (0xful << TIMER_EXTCTL_CAPDIVSCL_Pos)             /*!< TIMER_T::EXTCTL: CAPDIVSCL Mask         */

#define TIMER_EINTSTS_CAPIF_Pos          (0)                                               /*!< TIMER_T::EINTSTS: CAPIF Position       */
#define TIMER_EINTSTS_CAPIF_Msk          (0x1ul << TIMER_EINTSTS_CAPIF_Pos)                /*!< TIMER_T::EINTSTS: CAPIF Mask           */

#define TIMER_TRGCTL_TRGSSEL_Pos         (0)                                               /*!< TIMER_T::TRGCTL: TRGSSEL Position      */
#define TIMER_TRGCTL_TRGSSEL_Msk         (0x1ul << TIMER_TRGCTL_TRGSSEL_Pos)               /*!< TIMER_T::TRGCTL: TRGSSEL Mask          */

#define TIMER_TRGCTL_TRGEPWM_Pos         (1)                                               /*!< TIMER_T::TRGCTL: TRGEPWM Position      */
#define TIMER_TRGCTL_TRGEPWM_Msk         (0x1ul << TIMER_TRGCTL_TRGEPWM_Pos)               /*!< TIMER_T::TRGCTL: TRGEPWM Mask          */

#define TIMER_TRGCTL_TRGEADC_Pos         (2)                                               /*!< TIMER_T::TRGCTL: TRGEADC Position      */
#define TIMER_TRGCTL_TRGEADC_Msk         (0x1ul << TIMER_TRGCTL_TRGEADC_Pos)               /*!< TIMER_T::TRGCTL: TRGEADC Mask          */

#define TIMER_TRGCTL_TRGDAC_Pos          (3)                                               /*!< TIMER_T::TRGCTL: TRGDAC Position       */
#define TIMER_TRGCTL_TRGDAC_Msk          (0x1ul << TIMER_TRGCTL_TRGDAC_Pos)                /*!< TIMER_T::TRGCTL: TRGDAC Mask           */

#define TIMER_TRGCTL_TRGPDMA_Pos         (4)                                               /*!< TIMER_T::TRGCTL: TRGPDMA Position      */
#define TIMER_TRGCTL_TRGPDMA_Msk         (0x1ul << TIMER_TRGCTL_TRGPDMA_Pos)               /*!< TIMER_T::TRGCTL: TRGPDMA Mask          */

#define TIMER_ALTCTL_FUNCSEL_Pos         (0)                                               /*!< TIMER_T::ALTCTL: FUNCSEL Position      */
#define TIMER_ALTCTL_FUNCSEL_Msk         (0x1ul << TIMER_ALTCTL_FUNCSEL_Pos)               /*!< TIMER_T::ALTCTL: FUNCSEL Mask          */

#define TIMER_PWMCTL_CNTEN_Pos           (0)                                               /*!< TIMER_T::PWMCTL: CNTEN Position        */
#define TIMER_PWMCTL_CNTEN_Msk           (0x1ul << TIMER_PWMCTL_CNTEN_Pos)                 /*!< TIMER_T::PWMCTL: CNTEN Mask            */

#define TIMER_PWMCTL_CNTTYPE_Pos         (1)                                               /*!< TIMER_T::PWMCTL: CNTTYPE Position      */
#define TIMER_PWMCTL_CNTTYPE_Msk         (0x3ul << TIMER_PWMCTL_CNTTYPE_Pos)               /*!< TIMER_T::PWMCTL: CNTTYPE Mask          */

#define TIMER_PWMCTL_CNTMODE_Pos         (3)                                               /*!< TIMER_T::PWMCTL: CNTMODE Position      */
#define TIMER_PWMCTL_CNTMODE_Msk         (0x1ul << TIMER_PWMCTL_CNTMODE_Pos)               /*!< TIMER_T::PWMCTL: CNTMODE Mask          */

#define TIMER_PWMCTL_CTRLD_Pos           (8)                                               /*!< TIMER_T::PWMCTL: CTRLD Position        */
#define TIMER_PWMCTL_CTRLD_Msk           (0x1ul << TIMER_PWMCTL_CTRLD_Pos)                 /*!< TIMER_T::PWMCTL: CTRLD Mask            */

#define TIMER_PWMCTL_IMMLDEN_Pos         (9)                                               /*!< TIMER_T::PWMCTL: IMMLDEN Position      */
#define TIMER_PWMCTL_IMMLDEN_Msk         (0x1ul << TIMER_PWMCTL_IMMLDEN_Pos)               /*!< TIMER_T::PWMCTL: IMMLDEN Mask          */

#define TIMER_PWMCTL_OUTMODE_Pos         (16)                                              /*!< TIMER_T::PWMCTL: OUTMODE Position      */
#define TIMER_PWMCTL_OUTMODE_Msk         (0x1ul << TIMER_PWMCTL_OUTMODE_Pos)               /*!< TIMER_T::PWMCTL: OUTMODE Mask          */

#define TIMER_PWMCTL_DBGHALT_Pos         (30)                                              /*!< TIMER_T::PWMCTL: DBGHALT Position      */
#define TIMER_PWMCTL_DBGHALT_Msk         (0x1ul << TIMER_PWMCTL_DBGHALT_Pos)               /*!< TIMER_T::PWMCTL: DBGHALT Mask          */

#define TIMER_PWMCTL_DBGTRIOFF_Pos       (31)                                              /*!< TIMER_T::PWMCTL: DBGTRIOFF Position    */
#define TIMER_PWMCTL_DBGTRIOFF_Msk       (0x1ul << TIMER_PWMCTL_DBGTRIOFF_Pos)             /*!< TIMER_T::PWMCTL: DBGTRIOFF Mask        */

#define TIMER_PWMCLKSRC_CLKSRC_Pos       (0)                                               /*!< TIMER_T::PWMCLKSRC: CLKSRC Position    */
#define TIMER_PWMCLKSRC_CLKSRC_Msk       (0x7ul << TIMER_PWMCLKSRC_CLKSRC_Pos)             /*!< TIMER_T::PWMCLKSRC: CLKSRC Mask        */

#define TIMER_PWMCLKPSC_CLKPSC_Pos       (0)                                               /*!< TIMER_T::PWMCLKPSC: CLKPSC Position    */
#define TIMER_PWMCLKPSC_CLKPSC_Msk       (0xffful << TIMER_PWMCLKPSC_CLKPSC_Pos)           /*!< TIMER_T::PWMCLKPSC: CLKPSC Mask        */

#define TIMER_PWMCNTCLR_CNTCLR_Pos       (0)                                               /*!< TIMER_T::PWMCNTCLR: CNTCLR Position    */
#define TIMER_PWMCNTCLR_CNTCLR_Msk       (0x1ul << TIMER_PWMCNTCLR_CNTCLR_Pos)             /*!< TIMER_T::PWMCNTCLR: CNTCLR Mask        */

#define TIMER_PWMPERIOD_PERIOD_Pos       (0)                                               /*!< TIMER_T::PWMPERIOD: PERIOD Position    */
#define TIMER_PWMPERIOD_PERIOD_Msk       (0xfffful << TIMER_PWMPERIOD_PERIOD_Pos)          /*!< TIMER_T::PWMPERIOD: PERIOD Mask        */

#define TIMER_PWMCMPDAT_CMP_Pos          (0)                                               /*!< TIMER_T::PWMCMPDAT: CMP Position       */
#define TIMER_PWMCMPDAT_CMP_Msk          (0xfffful << TIMER_PWMCMPDAT_CMP_Pos)             /*!< TIMER_T::PWMCMPDAT: CMP Mask           */

#define TIMER_PWMDTCTL_DTCNT_Pos         (0)                                               /*!< TIMER_T::PWMDTCTL: DTCNT Position      */
#define TIMER_PWMDTCTL_DTCNT_Msk         (0xffful << TIMER_PWMDTCTL_DTCNT_Pos)             /*!< TIMER_T::PWMDTCTL: DTCNT Mask          */

#define TIMER_PWMDTCTL_DTEN_Pos          (16)                                              /*!< TIMER_T::PWMDTCTL: DTEN Position       */
#define TIMER_PWMDTCTL_DTEN_Msk          (0x1ul << TIMER_PWMDTCTL_DTEN_Pos)                /*!< TIMER_T::PWMDTCTL: DTEN Mask           */

#define TIMER_PWMDTCTL_DTCKSEL_Pos       (24)                                              /*!< TIMER_T::PWMDTCTL: DTCKSEL Position    */
#define TIMER_PWMDTCTL_DTCKSEL_Msk       (0x1ul << TIMER_PWMDTCTL_DTCKSEL_Pos)             /*!< TIMER_T::PWMDTCTL: DTCKSEL Mask        */

#define TIMER_PWMCNT_CNT_Pos             (0)                                               /*!< TIMER_T::PWMCNT: CNT Position          */
#define TIMER_PWMCNT_CNT_Msk             (0xfffful << TIMER_PWMCNT_CNT_Pos)                /*!< TIMER_T::PWMCNT: CNT Mask              */

#define TIMER_PWMCNT_DIRF_Pos            (16)                                              /*!< TIMER_T::PWMCNT: DIRF Position         */
#define TIMER_PWMCNT_DIRF_Msk            (0x1ul << TIMER_PWMCNT_DIRF_Pos)                  /*!< TIMER_T::PWMCNT: DIRF Mask             */

#define TIMER_PWMMSKEN_MSKEN0_Pos        (0)                                               /*!< TIMER_T::PWMMSKEN: MSKEN0 Position     */
#define TIMER_PWMMSKEN_MSKEN0_Msk        (0x1ul << TIMER_PWMMSKEN_MSKEN0_Pos)              /*!< TIMER_T::PWMMSKEN: MSKEN0 Mask         */

#define TIMER_PWMMSKEN_MSKEN1_Pos        (1)                                               /*!< TIMER_T::PWMMSKEN: MSKEN1 Position     */
#define TIMER_PWMMSKEN_MSKEN1_Msk        (0x1ul << TIMER_PWMMSKEN_MSKEN1_Pos)              /*!< TIMER_T::PWMMSKEN: MSKEN1 Mask         */

#define TIMER_PWMMSK_MSKDAT0_Pos         (0)                                               /*!< TIMER_T::PWMMSK: MSKDAT0 Position      */
#define TIMER_PWMMSK_MSKDAT0_Msk         (0x1ul << TIMER_PWMMSK_MSKDAT0_Pos)               /*!< TIMER_T::PWMMSK: MSKDAT0 Mask          */

#define TIMER_PWMMSK_MSKDAT1_Pos         (1)                                               /*!< TIMER_T::PWMMSK: MSKDAT1 Position      */
#define TIMER_PWMMSK_MSKDAT1_Msk         (0x1ul << TIMER_PWMMSK_MSKDAT1_Pos)               /*!< TIMER_T::PWMMSK: MSKDAT1 Mask          */

#define TIMER_PWMBNF_BRKNFEN_Pos         (0)                                               /*!< TIMER_T::PWMBNF: BRKNFEN Position      */
#define TIMER_PWMBNF_BRKNFEN_Msk         (0x1ul << TIMER_PWMBNF_BRKNFEN_Pos)               /*!< TIMER_T::PWMBNF: BRKNFEN Mask          */

#define TIMER_PWMBNF_BRKNFSEL_Pos        (1)                                               /*!< TIMER_T::PWMBNF: BRKNFSEL Position     */
#define TIMER_PWMBNF_BRKNFSEL_Msk        (0x7ul << TIMER_PWMBNF_BRKNFSEL_Pos)              /*!< TIMER_T::PWMBNF: BRKNFSEL Mask         */

#define TIMER_PWMBNF_BRKFCNT_Pos         (4)                                               /*!< TIMER_T::PWMBNF: BRKFCNT Position      */
#define TIMER_PWMBNF_BRKFCNT_Msk         (0x7ul << TIMER_PWMBNF_BRKFCNT_Pos)               /*!< TIMER_T::PWMBNF: BRKFCNT Mask          */

#define TIMER_PWMBNF_BRKPINV_Pos         (7)                                               /*!< TIMER_T::PWMBNF: BRKPINV Position      */
#define TIMER_PWMBNF_BRKPINV_Msk         (0x1ul << TIMER_PWMBNF_BRKPINV_Pos)               /*!< TIMER_T::PWMBNF: BRKPINV Mask          */

#define TIMER_PWMBNF_BKPINSRC_Pos        (16)                                              /*!< TIMER_T::PWMBNF: BKPINSRC Position     */
#define TIMER_PWMBNF_BKPINSRC_Msk        (0x3ul << TIMER_PWMBNF_BKPINSRC_Pos)              /*!< TIMER_T::PWMBNF: BKPINSRC Mask         */

#define TIMER_PWMFAILBRK_CSSBRKEN_Pos    (0)                                               /*!< TIMER_T::PWMFAILBRK: CSSBRKEN Position */
#define TIMER_PWMFAILBRK_CSSBRKEN_Msk    (0x1ul << TIMER_PWMFAILBRK_CSSBRKEN_Pos)          /*!< TIMER_T::PWMFAILBRK: CSSBRKEN Mask     */

#define TIMER_PWMFAILBRK_BODBRKEN_Pos    (1)                                               /*!< TIMER_T::PWMFAILBRK: BODBRKEN Position */
#define TIMER_PWMFAILBRK_BODBRKEN_Msk    (0x1ul << TIMER_PWMFAILBRK_BODBRKEN_Pos)          /*!< TIMER_T::PWMFAILBRK: BODBRKEN Mask     */

#define TIMER_PWMFAILBRK_RAMBRKEN_Pos    (2)                                               /*!< TIMER_T::PWMFAILBRK: RAMBRKEN Position */
#define TIMER_PWMFAILBRK_RAMBRKEN_Msk    (0x1ul << TIMER_PWMFAILBRK_RAMBRKEN_Pos)          /*!< TIMER_T::PWMFAILBRK: RAMBRKEN Mask     */

#define TIMER_PWMFAILBRK_CORBRKEN_Pos    (3)                                               /*!< TIMER_T::PWMFAILBRK: CORBRKEN Position */
#define TIMER_PWMFAILBRK_CORBRKEN_Msk    (0x1ul << TIMER_PWMFAILBRK_CORBRKEN_Pos)          /*!< TIMER_T::PWMFAILBRK: CORBRKEN Mask     */

#define TIMER_PWMBRKCTL_CPO0EBEN_Pos     (0)                                               /*!< TIMER_T::PWMBRKCTL: CPO0EBEN Position  */
#define TIMER_PWMBRKCTL_CPO0EBEN_Msk     (0x1ul << TIMER_PWMBRKCTL_CPO0EBEN_Pos)           /*!< TIMER_T::PWMBRKCTL: CPO0EBEN Mask      */

#define TIMER_PWMBRKCTL_CPO1EBEN_Pos     (1)                                               /*!< TIMER_T::PWMBRKCTL: CPO1EBEN Position  */
#define TIMER_PWMBRKCTL_CPO1EBEN_Msk     (0x1ul << TIMER_PWMBRKCTL_CPO1EBEN_Pos)           /*!< TIMER_T::PWMBRKCTL: CPO1EBEN Mask      */

#define TIMER_PWMBRKCTL_BRKPEEN_Pos      (4)                                               /*!< TIMER_T::PWMBRKCTL: BRKPEEN Position   */
#define TIMER_PWMBRKCTL_BRKPEEN_Msk      (0x1ul << TIMER_PWMBRKCTL_BRKPEEN_Pos)            /*!< TIMER_T::PWMBRKCTL: BRKPEEN Mask       */

#define TIMER_PWMBRKCTL_SYSEBEN_Pos      (7)                                               /*!< TIMER_T::PWMBRKCTL: SYSEBEN Position   */
#define TIMER_PWMBRKCTL_SYSEBEN_Msk      (0x1ul << TIMER_PWMBRKCTL_SYSEBEN_Pos)            /*!< TIMER_T::PWMBRKCTL: SYSEBEN Mask       */

#define TIMER_PWMBRKCTL_CPO0LBEN_Pos     (8)                                               /*!< TIMER_T::PWMBRKCTL: CPO0LBEN Position  */
#define TIMER_PWMBRKCTL_CPO0LBEN_Msk     (0x1ul << TIMER_PWMBRKCTL_CPO0LBEN_Pos)           /*!< TIMER_T::PWMBRKCTL: CPO0LBEN Mask      */

#define TIMER_PWMBRKCTL_CPO1LBEN_Pos     (9)                                               /*!< TIMER_T::PWMBRKCTL: CPO1LBEN Position  */
#define TIMER_PWMBRKCTL_CPO1LBEN_Msk     (0x1ul << TIMER_PWMBRKCTL_CPO1LBEN_Pos)           /*!< TIMER_T::PWMBRKCTL: CPO1LBEN Mask      */

#define TIMER_PWMBRKCTL_BRKPLEN_Pos      (12)                                              /*!< TIMER_T::PWMBRKCTL: BRKPLEN Position   */
#define TIMER_PWMBRKCTL_BRKPLEN_Msk      (0x1ul << TIMER_PWMBRKCTL_BRKPLEN_Pos)            /*!< TIMER_T::PWMBRKCTL: BRKPLEN Mask       */

#define TIMER_PWMBRKCTL_SYSLBEN_Pos      (15)                                              /*!< TIMER_T::PWMBRKCTL: SYSLBEN Position   */
#define TIMER_PWMBRKCTL_SYSLBEN_Msk      (0x1ul << TIMER_PWMBRKCTL_SYSLBEN_Pos)            /*!< TIMER_T::PWMBRKCTL: SYSLBEN Mask       */

#define TIMER_PWMBRKCTL_BRKAEVEN_Pos     (16)                                              /*!< TIMER_T::PWMBRKCTL: BRKAEVEN Position  */
#define TIMER_PWMBRKCTL_BRKAEVEN_Msk     (0x3ul << TIMER_PWMBRKCTL_BRKAEVEN_Pos)           /*!< TIMER_T::PWMBRKCTL: BRKAEVEN Mask      */

#define TIMER_PWMBRKCTL_BRKAODD_Pos      (18)                                              /*!< TIMER_T::PWMBRKCTL: BRKAODD Position   */
#define TIMER_PWMBRKCTL_BRKAODD_Msk      (0x3ul << TIMER_PWMBRKCTL_BRKAODD_Pos)            /*!< TIMER_T::PWMBRKCTL: BRKAODD Mask       */

#define TIMER_PWMPOLCTL_PINV0_Pos        (0)                                               /*!< TIMER_T::PWMPOLCTL: PINV0 Position     */
#define TIMER_PWMPOLCTL_PINV0_Msk        (0x1ul << TIMER_PWMPOLCTL_PINV0_Pos)              /*!< TIMER_T::PWMPOLCTL: PINV0 Mask         */

#define TIMER_PWMPOLCTL_PINV1_Pos        (1)                                               /*!< TIMER_T::PWMPOLCTL: PINV1 Position     */
#define TIMER_PWMPOLCTL_PINV1_Msk        (0x1ul << TIMER_PWMPOLCTL_PINV1_Pos)              /*!< TIMER_T::PWMPOLCTL: PINV1 Mask         */

#define TIMER_PWMPOEN_POEN0_Pos          (0)                                               /*!< TIMER_T::PWMPOEN: POEN0 Position       */
#define TIMER_PWMPOEN_POEN0_Msk          (0x1ul << TIMER_PWMPOEN_POEN0_Pos)                /*!< TIMER_T::PWMPOEN: POEN0 Mask           */

#define TIMER_PWMPOEN_POEN1_Pos          (1)                                               /*!< TIMER_T::PWMPOEN: POEN1 Position       */
#define TIMER_PWMPOEN_POEN1_Msk          (0x1ul << TIMER_PWMPOEN_POEN1_Pos)                /*!< TIMER_T::PWMPOEN: POEN1 Mask           */

#define TIMER_PWMSWBRK_BRKETRG_Pos       (0)                                               /*!< TIMER_T::PWMSWBRK: BRKETRG Position    */
#define TIMER_PWMSWBRK_BRKETRG_Msk       (0x1ul << TIMER_PWMSWBRK_BRKETRG_Pos)             /*!< TIMER_T::PWMSWBRK: BRKETRG Mask        */

#define TIMER_PWMSWBRK_BRKLTRG_Pos       (8)                                               /*!< TIMER_T::PWMSWBRK: BRKLTRG Position    */
#define TIMER_PWMSWBRK_BRKLTRG_Msk       (0x1ul << TIMER_PWMSWBRK_BRKLTRG_Pos)             /*!< TIMER_T::PWMSWBRK: BRKLTRG Mask        */

#define TIMER_PWMINTEN0_ZIEN_Pos         (0)                                               /*!< TIMER_T::PWMINTEN0: ZIEN Position      */
#define TIMER_PWMINTEN0_ZIEN_Msk         (0x1ul << TIMER_PWMINTEN0_ZIEN_Pos)               /*!< TIMER_T::PWMINTEN0: ZIEN Mask          */

#define TIMER_PWMINTEN0_PIEN_Pos         (1)                                               /*!< TIMER_T::PWMINTEN0: PIEN Position      */
#define TIMER_PWMINTEN0_PIEN_Msk         (0x1ul << TIMER_PWMINTEN0_PIEN_Pos)               /*!< TIMER_T::PWMINTEN0: PIEN Mask          */

#define TIMER_PWMINTEN0_CMPUIEN_Pos      (2)                                               /*!< TIMER_T::PWMINTEN0: CMPUIEN Position   */
#define TIMER_PWMINTEN0_CMPUIEN_Msk      (0x1ul << TIMER_PWMINTEN0_CMPUIEN_Pos)            /*!< TIMER_T::PWMINTEN0: CMPUIEN Mask       */

#define TIMER_PWMINTEN0_CMPDIEN_Pos      (3)                                               /*!< TIMER_T::PWMINTEN0: CMPDIEN Position   */
#define TIMER_PWMINTEN0_CMPDIEN_Msk      (0x1ul << TIMER_PWMINTEN0_CMPDIEN_Pos)            /*!< TIMER_T::PWMINTEN0: CMPDIEN Mask       */

#define TIMER_PWMINTEN1_BRKEIEN_Pos      (0)                                               /*!< TIMER_T::PWMINTEN1: BRKEIEN Position   */
#define TIMER_PWMINTEN1_BRKEIEN_Msk      (0x1ul << TIMER_PWMINTEN1_BRKEIEN_Pos)            /*!< TIMER_T::PWMINTEN1: BRKEIEN Mask       */

#define TIMER_PWMINTEN1_BRKLIEN_Pos      (8)                                               /*!< TIMER_T::PWMINTEN1: BRKLIEN Position   */
#define TIMER_PWMINTEN1_BRKLIEN_Msk      (0x1ul << TIMER_PWMINTEN1_BRKLIEN_Pos)            /*!< TIMER_T::PWMINTEN1: BRKLIEN Mask       */

#define TIMER_PWMINTSTS0_ZIF_Pos         (0)                                               /*!< TIMER_T::PWMINTSTS0: ZIF Position      */
#define TIMER_PWMINTSTS0_ZIF_Msk         (0x1ul << TIMER_PWMINTSTS0_ZIF_Pos)               /*!< TIMER_T::PWMINTSTS0: ZIF Mask          */

#define TIMER_PWMINTSTS0_PIF_Pos         (1)                                               /*!< TIMER_T::PWMINTSTS0: PIF Position      */
#define TIMER_PWMINTSTS0_PIF_Msk         (0x1ul << TIMER_PWMINTSTS0_PIF_Pos)               /*!< TIMER_T::PWMINTSTS0: PIF Mask          */

#define TIMER_PWMINTSTS0_CMPUIF_Pos      (2)                                               /*!< TIMER_T::PWMINTSTS0: CMPUIF Position   */
#define TIMER_PWMINTSTS0_CMPUIF_Msk      (0x1ul << TIMER_PWMINTSTS0_CMPUIF_Pos)            /*!< TIMER_T::PWMINTSTS0: CMPUIF Mask       */

#define TIMER_PWMINTSTS0_CMPDIF_Pos      (3)                                               /*!< TIMER_T::PWMINTSTS0: CMPDIF Position   */
#define TIMER_PWMINTSTS0_CMPDIF_Msk      (0x1ul << TIMER_PWMINTSTS0_CMPDIF_Pos)            /*!< TIMER_T::PWMINTSTS0: CMPDIF Mask       */

#define TIMER_PWMINTSTS1_BRKEIF0_Pos     (0)                                               /*!< TIMER_T::PWMINTSTS1: BRKEIF0 Position  */
#define TIMER_PWMINTSTS1_BRKEIF0_Msk     (0x1ul << TIMER_PWMINTSTS1_BRKEIF0_Pos)           /*!< TIMER_T::PWMINTSTS1: BRKEIF0 Mask      */

#define TIMER_PWMINTSTS1_BRKEIF1_Pos     (1)                                               /*!< TIMER_T::PWMINTSTS1: BRKEIF1 Position  */
#define TIMER_PWMINTSTS1_BRKEIF1_Msk     (0x1ul << TIMER_PWMINTSTS1_BRKEIF1_Pos)           /*!< TIMER_T::PWMINTSTS1: BRKEIF1 Mask      */

#define TIMER_PWMINTSTS1_BRKLIF0_Pos     (8)                                               /*!< TIMER_T::PWMINTSTS1: BRKLIF0 Position  */
#define TIMER_PWMINTSTS1_BRKLIF0_Msk     (0x1ul << TIMER_PWMINTSTS1_BRKLIF0_Pos)           /*!< TIMER_T::PWMINTSTS1: BRKLIF0 Mask      */

#define TIMER_PWMINTSTS1_BRKLIF1_Pos     (9)                                               /*!< TIMER_T::PWMINTSTS1: BRKLIF1 Position  */
#define TIMER_PWMINTSTS1_BRKLIF1_Msk     (0x1ul << TIMER_PWMINTSTS1_BRKLIF1_Pos)           /*!< TIMER_T::PWMINTSTS1: BRKLIF1 Mask      */

#define TIMER_PWMINTSTS1_BRKESTS0_Pos    (16)                                              /*!< TIMER_T::PWMINTSTS1: BRKESTS0 Position */
#define TIMER_PWMINTSTS1_BRKESTS0_Msk    (0x1ul << TIMER_PWMINTSTS1_BRKESTS0_Pos)          /*!< TIMER_T::PWMINTSTS1: BRKESTS0 Mask     */

#define TIMER_PWMINTSTS1_BRKESTS1_Pos    (17)                                              /*!< TIMER_T::PWMINTSTS1: BRKESTS1 Position */
#define TIMER_PWMINTSTS1_BRKESTS1_Msk    (0x1ul << TIMER_PWMINTSTS1_BRKESTS1_Pos)          /*!< TIMER_T::PWMINTSTS1: BRKESTS1 Mask     */

#define TIMER_PWMINTSTS1_BRKLSTS0_Pos    (24)                                              /*!< TIMER_T::PWMINTSTS1: BRKLSTS0 Position */
#define TIMER_PWMINTSTS1_BRKLSTS0_Msk    (0x1ul << TIMER_PWMINTSTS1_BRKLSTS0_Pos)          /*!< TIMER_T::PWMINTSTS1: BRKLSTS0 Mask     */

#define TIMER_PWMINTSTS1_BRKLSTS1_Pos    (25)                                              /*!< TIMER_T::PWMINTSTS1: BRKLSTS1 Position */
#define TIMER_PWMINTSTS1_BRKLSTS1_Msk    (0x1ul << TIMER_PWMINTSTS1_BRKLSTS1_Pos)          /*!< TIMER_T::PWMINTSTS1: BRKLSTS1 Mask     */

#define TIMER_PWMEADCTS_TRGSEL_Pos       (0)                                               /*!< TIMER_T::PWMEADCTS: TRGSEL Position    */
#define TIMER_PWMEADCTS_TRGSEL_Msk       (0x7ul << TIMER_PWMEADCTS_TRGSEL_Pos)             /*!< TIMER_T::PWMEADCTS: TRGSEL Mask        */

#define TIMER_PWMEADCTS_TRGEN_Pos        (7)                                               /*!< TIMER_T::PWMEADCTS: TRGEN Position     */
#define TIMER_PWMEADCTS_TRGEN_Msk        (0x1ul << TIMER_PWMEADCTS_TRGEN_Pos)              /*!< TIMER_T::PWMEADCTS: TRGEN Mask         */

#define TIMER_PWMSCTL_SYNCMODE_Pos       (0)                                               /*!< TIMER_T::PWMSCTL: SYNCMODE Position    */
#define TIMER_PWMSCTL_SYNCMODE_Msk       (0x3ul << TIMER_PWMSCTL_SYNCMODE_Pos)             /*!< TIMER_T::PWMSCTL: SYNCMODE Mask        */

#define TIMER_PWMSCTL_SYNCSRC_Pos        (8)                                               /*!< TIMER_T::PWMSCTL: SYNCSRC Position     */
#define TIMER_PWMSCTL_SYNCSRC_Msk        (0x1ul << TIMER_PWMSCTL_SYNCSRC_Pos)              /*!< TIMER_T::PWMSCTL: SYNCSRC Mask         */

#define TIMER_PWMSTRG_STRGEN_Pos         (0)                                               /*!< TIMER_T::PWMSTRG: STRGEN Position      */
#define TIMER_PWMSTRG_STRGEN_Msk         (0x1ul << TIMER_PWMSTRG_STRGEN_Pos)               /*!< TIMER_T::PWMSTRG: STRGEN Mask          */

#define TIMER_PWMSTATUS_CNTMAXF_Pos      (0)                                               /*!< TIMER_T::PWMSTATUS: CNTMAXF Position   */
#define TIMER_PWMSTATUS_CNTMAXF_Msk      (0x1ul << TIMER_PWMSTATUS_CNTMAXF_Pos)            /*!< TIMER_T::PWMSTATUS: CNTMAXF Mask       */

#define TIMER_PWMSTATUS_EADCTRGF_Pos     (16)                                              /*!< TIMER_T::PWMSTATUS: EADCTRGF Position  */
#define TIMER_PWMSTATUS_EADCTRGF_Msk     (0x1ul << TIMER_PWMSTATUS_EADCTRGF_Pos)           /*!< TIMER_T::PWMSTATUS: EADCTRGF Mask      */

#define TIMER_PWMPBUF_PBUF_Pos           (0)                                               /*!< TIMER_T::PWMPBUF: PBUF Position        */
#define TIMER_PWMPBUF_PBUF_Msk           (0xfffful << TIMER_PWMPBUF_PBUF_Pos)              /*!< TIMER_T::PWMPBUF: PBUF Mask            */

#define TIMER_PWMCMPBUF_CMPBUF_Pos       (0)                                               /*!< TIMER_T::PWMCMPBUF: CMPBUF Position    */
#define TIMER_PWMCMPBUF_CMPBUF_Msk       (0xfffful << TIMER_PWMCMPBUF_CMPBUF_Pos)          /*!< TIMER_T::PWMCMPBUF: CMPBUF Mask        */

/**@}*/ /* TIMER_CONST */
/**@}*/ /* end of TIMER register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __TIMER_REG_H__ */
