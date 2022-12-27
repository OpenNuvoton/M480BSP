/**************************************************************************//**
 * @file     sc_reg.h
 * @version  V1.00
 * @brief    SC register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __SC_REG_H__
#define __SC_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup SC Smart Card Host Interface Controller(SC)
    Memory Mapped Structure for SC Controller
@{ */

typedef struct
{


    /**
@var SC_T::DAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DAT
</font><br><p> <font size="2">
Offset: 0x00  SC Receive/Transmit Holding Buffer Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>DAT</td><td><div style="word-wrap: break-word;"><b>Receive/Transmit Holding Buffer
</b><br>
Write Operation:
<br>
By writing data to DAT, the SC will send out an 8-bit data.
<br>
Note: If SCEN (SCn_CTL[0]) is not enabled, DAT cannot be programmed.
<br>
Read Operation:
<br>
By reading DAT, the SC will return an 8-bit received data.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SC_T::CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL
</font><br><p> <font size="2">
Offset: 0x04  SC Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SCEN</td><td><div style="word-wrap: break-word;"><b>SC Controller Enable Bit
</b><br>
Set this bit to 1 to enable SC operation. If this bit is cleared,
<br>
0 = SC will force all transition to IDLE state.
<br>
1 = SC controller is enabled and all function can work correctly.
<br>
Note1: SCEN must be set to 1 before filling in other SC registers, or smart card will not work properly.
<br>
</div></td></tr><tr><td>
[1]</td><td>RXOFF</td><td><div style="word-wrap: break-word;"><b>RX Transition Disable Control Bit
</b><br>
This bit is used for disable Rx transition function.
<br>
0 = The receiver Enabled.
<br>
1 = The receiver Disabled.
<br>
Note1: If AUTOCEN (SCn_CTL[3]) is enabled, this field is ignored.
<br>
</div></td></tr><tr><td>
[2]</td><td>TXOFF</td><td><div style="word-wrap: break-word;"><b>TX Transition Disable Control Bit
</b><br>
This bit is used for disable Tx transition function.
<br>
0 = The transceiver Enabled.
<br>
1 = The transceiver Disabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>AUTOCEN</td><td><div style="word-wrap: break-word;"><b>Auto Convention Enable Bit
</b><br>
This bit is used for enable auto convention function.
<br>
0 = Auto-convention Disabled.
<br>
1 = Auto-convention Enabled.
<br>
If user enables auto convention function, the setting step must be done before Answer to Reset (ATR)
<br>
state and the first data must be 0x3B or 0x3F.
<br>
After hardware received first data and stored it at buffer, hardware will decided the convention and
<br>
change the CONSEL (SCn_CTL[5:4]) bits automatically when received first data is 0x3B or 0x3F.
<br>
If received first byte is 0x3B, TS is direct convention, CONSEL (SCn_CTL[5:4]) will be set to 00
<br>
automatically, otherwise the TS is inverse convention, and CONSEL (SCn_CTL[5:4]) will be set to 11.
<br>
If the first data is not 0x3B or 0x3F, hardware will set ACERRIF (SCn_INTSTS[10]) and generate an
<br>
interrupt to CPU when ACERRIEN (SCn_INTEN[10]) is enabled.
<br>
</div></td></tr><tr><td>
[5:4]</td><td>CONSEL</td><td><div style="word-wrap: break-word;"><b>Convention Selection
</b><br>
00 = Direct convention.
<br>
01 = Reserved.
<br>
10 = Reserved.
<br>
11 = Inverse convention.
<br>
Note: If AUTOCEN (SCn_CTL[3]) is enabled, this field is ignored.
<br>
</div></td></tr><tr><td>
[7:6]</td><td>RXTRGLV</td><td><div style="word-wrap: break-word;"><b>Rx Buffer Trigger Level
</b><br>
When the number of bytes in the receiving buffer equals the RXTRGLV, the RDAIF will be set
<br>
If RDAIEN (SCn_INTEN[0]) is enabled, an interrupt will be generated to CPU.
<br>
00 = Rx Buffer Trigger Level with 01 bytes.
<br>
01 = Rx Buffer Trigger Level with 02 bytes.
<br>
10 = Rx Buffer Trigger Level with 03 bytes.
<br>
11 = Reserved.
<br>
</div></td></tr><tr><td>
[12:8]</td><td>BGT</td><td><div style="word-wrap: break-word;"><b>Block Guard Time (BGT)
</b><br>
Block guard time means the minimum interval between the leading edges of two consecutive characters
<br>
between different transfer directions
<br>
This field indicates the counter for the bit length of block guard time
<br>
According to ISO 7816-3, in T = 0 mode, user must fill 15 (real block guard time = 16.5) to this
<br>
field; in T = 1 mode, user must fill 21 (real block guard time = 22.5) to it.
<br>
Note: The real block guard time is BGT + 1.
<br>
</div></td></tr><tr><td>
[14:13]</td><td>TMRSEL</td><td><div style="word-wrap: break-word;"><b>Timer Channel Selection
</b><br>
00 = All internal timer function Disabled.
<br>
11 = Internal 24 bit timer and two 8 bit timers Enabled
<br>
User can configure them by setting SCn_TMRCTL0[23:0], SCn_TMRCTL1[7:0] and SCn_TMRCTL2[7:0].
<br>
Other configurations are reserved
<br>
</div></td></tr><tr><td>
[15]</td><td>NSB</td><td><div style="word-wrap: break-word;"><b>Stop Bit Length
</b><br>
This field indicates the length of stop bit.
<br>
0 = The stop bit length is 2 ETU.
<br>
1= The stop bit length is 1 ETU.
<br>
Note1: The default stop bit length is 2. SC and UART adopts NSB to program the stop bit length.
<br>
Note2: In UART mode, RX can receive the data sequence in 1 stop bit or 2 stop bits with NSB is set to 0.
<br>
</div></td></tr><tr><td>
[18:16]</td><td>RXRTY</td><td><div style="word-wrap: break-word;"><b>RX Error Retry Count Number
</b><br>
This field indicates the maximum number of receiver retries that are allowed when parity error has occurred.
<br>
Note1: The real retry number is RXRTY + 1, so 8 is the maximum retry number.
<br>
Note2: This field cannot be changed when RXRTYEN enabled
<br>
The change flow is to disable RXRTYEN first and then fill in new retry value.
<br>
</div></td></tr><tr><td>
[19]</td><td>RXRTYEN</td><td><div style="word-wrap: break-word;"><b>RX Error Retry Enable Bit
</b><br>
This bit enables receiver retry function when parity error has occurred.
<br>
0 = RX error retry function Disabled.
<br>
1 = RX error retry function Enabled.
<br>
Note: User must fill in the RXRTY value before enabling this bit.
<br>
</div></td></tr><tr><td>
[22:20]</td><td>TXRTY</td><td><div style="word-wrap: break-word;"><b>TX Error Retry Count Number
</b><br>
This field indicates the maximum number of transmitter retries that are allowed when parity
<br>
error has occurred.
<br>
Note1: The real retry number is TXRTY + 1, so 8 is the maximum retry number.
<br>
Note2: This field cannot be changed when TXRTYEN enabled
<br>
The change flow is to disable TXRTYEN first and then fill in new retry value.
<br>
</div></td></tr><tr><td>
[23]</td><td>TXRTYEN</td><td><div style="word-wrap: break-word;"><b>TX Error Retry Enable Bit
</b><br>
This bit enables transmitter retry function when parity error has occurred.
<br>
0 = TX error retry function Disabled.
<br>
1 = TX error retry function Enabled.
<br>
</div></td></tr><tr><td>
[25:24]</td><td>CDDBSEL</td><td><div style="word-wrap: break-word;"><b>Card Detect De-bounce Selection
</b><br>
This field indicates the card detect de-bounce selection.
<br>
00 = De-bounce sample card insert once per 384 (128 * 3) SC module clocks and de-bounce
<br>
sample card removal once per 128 SC module clocks.
<br>
Other configurations are reserved.
<br>
</div></td></tr><tr><td>
[26]</td><td>CDLV</td><td><div style="word-wrap: break-word;"><b>Card Detect Level Selection
</b><br>
0 = When hardware detects the card detect pin (SCn_CD) from high to low, it indicates a card is detected.
<br>
1 = When hardware detects the card detect pin (SCn_CD) from low to high, it indicates a card is detected.
<br>
Note: User must select card detect level before Smart Card controller enabled.
<br>
</div></td></tr><tr><td>
[30]</td><td>SYNC</td><td><div style="word-wrap: break-word;"><b>SYNC Flag Indicator (Read Only)
</b><br>
Due to synchronization, user should check this bit before writing a new value to RXRTY and TXRTY fields.
<br>
0 = Synchronizing is completion, user can write new data to RXRTY and TXRTY.
<br>
1 = Last value is synchronizing.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SC_T::ALTCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ALTCTL
</font><br><p> <font size="2">
Offset: 0x08  SC Alternate Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>TXRST</td><td><div style="word-wrap: break-word;"><b>TX Software Reset
</b><br>
When TXRST is set, all the bytes in the transmit buffer and TX internal state machine will be cleared.
<br>
0 = No effect.
<br>
1 = Reset the TX internal state machine and pointers.
<br>
Note: This bit will be auto cleared after reset is complete.
<br>
</div></td></tr><tr><td>
[1]</td><td>RXRST</td><td><div style="word-wrap: break-word;"><b>Rx Software Reset
</b><br>
When RXRST is set, all the bytes in the receive buffer and Rx internal state machine will be cleared.
<br>
0 = No effect.
<br>
1 = Reset the Rx internal state machine and pointers.
<br>
Note: This bit will be auto cleared after reset is complete.
<br>
</div></td></tr><tr><td>
[2]</td><td>DACTEN</td><td><div style="word-wrap: break-word;"><b>Deactivation Sequence Generator Enable Bit
</b><br>
This bit enables SC controller to initiate the card by deactivation sequence.
<br>
0 = No effect.
<br>
1 = Deactivation sequence generator Enabled.
<br>
Note1: When the deactivation sequence completed, this bit will be cleared automatically and
<br>
the INITIF (SCn_INTSTS[8]) will be set to 1.
<br>
Note2: This field will be cleared by TXRST (SCn_ALTCTL[0]) and RXRST (SCn_ALTCTL[1])
<br>
Thus, do not fill in this bit DACTEN, TXRST and RXRST at the same time.
<br>
Note3: If SCEN (SCn_CTL[0]) is not enabled, this filed cannot be programmed.
<br>
</div></td></tr><tr><td>
[3]</td><td>ACTEN</td><td><div style="word-wrap: break-word;"><b>Activation Sequence Generator Enable Bit
</b><br>
This bit enables SC controller to initiate the card by activation sequence.
<br>
0 = No effect.
<br>
1 = Activation sequence generator Enabled.
<br>
Note1: When the activation sequence completed, this bit will be cleared automatically and the
<br>
INITIF (SCn_INTSTS[8]) will be set to 1.
<br>
Note2: This field will be cleared by TXRST (SCn_ALTCTL[0]) and RXRST (SCn_ALTCTL[1])
<br>
Thus, do not fill in this bit ACTEN, TXRST and RXRST at the same time.
<br>
Note3: If SCEN (SCn_CTL[0]) is not enabled, this filed cannot be programmed.
<br>
Note4: During the activation sequence, RX is disabled automatically and can not receive data
<br>
After the activation sequence completion, RXOFF (SCn_CTL[1]) keeps the state before hardware activation.
<br>
</div></td></tr><tr><td>
[4]</td><td>WARSTEN</td><td><div style="word-wrap: break-word;"><b>Warm Reset Sequence Generator Enable Bit
</b><br>
This bit enables SC controller to initiate the card by warm reset sequence.
<br>
0 = No effect.
<br>
1 = Warm reset sequence generator Enabled.
<br>
Note1: When the warm reset sequence completed, this bit will be cleared automatically and the
<br>
INITIF (SCn_INTSTS[8]) will be set to 1.
<br>
Note2: This field will be cleared by TXRST (SCn_ALTCTL[0]) and RXRST (SCn_ALTCTL[1])
<br>
Thus, do not fill in this bit WARSTEN, TXRST and RXRST at the same time.
<br>
Note3: If SCEN (SCn_CTL[0]) is not enabled, this filed cannot be programmed.
<br>
Note4: During the warm reset sequence, RX is disabled automatically and can not receive data
<br>
After the warm reset sequence completion, RXOFF (SCn_CTL[1]) keeps the state before perform
<br>
warm reset sequence.
<br>
</div></td></tr><tr><td>
[5]</td><td>CNTEN0</td><td><div style="word-wrap: break-word;"><b>Internal Timer0 Start Enable Bit
</b><br>
This bit enables Timer 0 to start counting
<br>
User can fill 0 to stop it and set 1 to reload and count
<br>
The counter unit is ETU base.
<br>
0 = Stops counting.
<br>
1 = Start counting.
<br>
Note1: This field is used for internal 24 bit timer when TMRSEL (SCn_CTL[14:13]) is 11 only.
<br>
Note2: If the operation mode is not in auto-reload mode (SCn_TMRCTL0[26] = 0), this bit will
<br>
be auto-cleared by hardware.
<br>
Note3: If SCEN (SCn_CTL[0]) is not enabled, this filed cannot be programmed.
<br>
</div></td></tr><tr><td>
[6]</td><td>CNTEN1</td><td><div style="word-wrap: break-word;"><b>Internal Timer1 Start Enable Bit
</b><br>
This bit enables Timer 1 to start counting
<br>
User can fill 0 to stop it and set 1 to reload and count
<br>
The counter unit is ETU base.
<br>
0 = Stops counting.
<br>
1 = Start counting.
<br>
Note1: This field is used for internal 8 bit timer when TMRSEL(SCn_CTL[14:13]) is 11 only
<br>
Do not fill CNTEN1 when TMRSEL (SCn_CTL[14:13]) is not equal to 11.
<br>
Note2: If the operation mode is not in auto-reload mode (SCn_TMRCTL1[26] = 0), this bit will
<br>
be auto-cleared by hardware.
<br>
Note3: If SCEN (SCn_CTL[0]) is not enabled, this filed cannot be programmed.
<br>
</div></td></tr><tr><td>
[7]</td><td>CNTEN2</td><td><div style="word-wrap: break-word;"><b>Internal Timer2 Start Enable Bit
</b><br>
This bit enables Timer 2 to start counting
<br>
User can fill 0 to stop it and set 1 to reload and count
<br>
The counter unit is ETU base.
<br>
0 = Stops counting.
<br>
1 = Start counting.
<br>
Note1: This field is used for internal 8 bit timer when TMRSEL (SCn_CTL[14:13]) is 11 only
<br>
Do not fill in CNTEN2 when TMRSEL (SCn_CTL[14:13]) is not equal to 11.
<br>
Note2: If the operation mode is not in auto-reload mode (SCn_TMRCTL2[26] = 0), this bit will
<br>
be auto-cleared by hardware.
<br>
Note3: If SCEN (SCn_CTL[0]) is not enabled, this filed cannot be programmed.
<br>
</div></td></tr><tr><td>
[9:8]</td><td>INITSEL</td><td><div style="word-wrap: break-word;"><b>Initial Timing Selection
</b><br>
This fields indicates the initial timing of hardware activation, warm-reset or deactivation.
<br>
The unit of initial timing is SC module clock.
<br>
Activation: refer to SC Activation Sequence in Figure 7.17-54.
<br>
Warm-reset: refer to Warm-Reset Sequence in Figure 7.17-5.
<br>
Deactivation: refer to Deactivation Sequence in Figure 7.17-56.
<br>
Note: When set activation and warm reset in Timer0 operation mode 0011, it may have deviation
<br>
at most 128 SC module clock cycles.
<br>
</div></td></tr><tr><td>
[11]</td><td>ADACEN</td><td><div style="word-wrap: break-word;"><b>Auto Deactivation When Card Removal
</b><br>
This bit is used for enable hardware auto deactivation when smart card is removed.
<br>
0 = Auto deactivation Disabled.
<br>
1 = Auto deactivation Enabled.
<br>
Note: When the card is removed, hardware will stop any process and then do deactivation sequence
<br>
if this bit is set
<br>
If auto deactivation process completes, hardware will set INITIF (SCn_INTSTS[8]) also.
<br>
</div></td></tr><tr><td>
[12]</td><td>RXBGTEN</td><td><div style="word-wrap: break-word;"><b>Receiver Block Guard Time Function Enable Bit
</b><br>
This bit enables the receiver block guard time function.
<br>
0 = Receiver block guard time function Disabled.
<br>
1 = Receiver block guard time function Enabled.
<br>
</div></td></tr><tr><td>
[13]</td><td>ACTSTS0</td><td><div style="word-wrap: break-word;"><b>Internal Timer0 Active Status (Read Only)
</b><br>
This bit indicates the timer counter status of timer0.
<br>
0 = Timer0 is not active.
<br>
1 = Timer0 is active.
<br>
Note: Timer0 is active does not always mean timer0 is counting the CNT (SCn_TMRCTL0[23:0]).
<br>
</div></td></tr><tr><td>
[14]</td><td>ACTSTS1</td><td><div style="word-wrap: break-word;"><b>Internal Timer1 Active Status (Read Only)
</b><br>
This bit indicates the timer counter status of timer1.
<br>
0 = Timer1 is not active.
<br>
1 = Timer1 is active.
<br>
Note: Timer1 is active does not always mean timer1 is counting the CNT (SCn_TMRCTL1[7:0]).
<br>
</div></td></tr><tr><td>
[15]</td><td>ACTSTS2</td><td><div style="word-wrap: break-word;"><b>Internal Timer2 Active Status (Read Only)
</b><br>
This bit indicates the timer counter status of timer2.
<br>
0 = Timer2 is not active.
<br>
1 = Timer2 is active.
<br>
Note: Timer2 is active does not always mean timer2 is counting the CNT (SCn_TMRCTL2[7:0]).
<br>
</div></td></tr><tr><td>
[31]</td><td>SYNC</td><td><div style="word-wrap: break-word;"><b>SYNC Flag Indicator (Read Only)
</b><br>
Due to synchronization, user should check this bit when writing a new value to SCn_ALTCTL register.
<br>
0 = Synchronizing is completion, user can write new data to SCn_ALTCTL register.
<br>
1 = Last value is synchronizing.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SC_T::EGT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EGT
</font><br><p> <font size="2">
Offset: 0x0C  SC Extra Guard Time Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>EGT</td><td><div style="word-wrap: break-word;"><b>Extra Guard Time
</b><br>
This field indicates the extra guard time value.
<br>
Note: The extra guard time unit is ETU base.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SC_T::RXTOUT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">RXTOUT
</font><br><p> <font size="2">
Offset: 0x10  SC Receive Buffer Time-out Counter Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[8:0]</td><td>RFTM</td><td><div style="word-wrap: break-word;"><b>SC Receiver FIFO Time-out Counter
</b><br>
The time-out down counter resets and starts counting whenever the RX buffer received a new data
<br>
Once the counter decrease to 1 and no new data is received or CPU does not read data by
<br>
reading SCn_DAT, a receiver time-out flag RBTOIF (SCn_INTSTS[9]) will be set, and hardware will
<br>
generate an interrupt to CPU when RBTOIEN (SCn_INTEN[9]) is enabled.
<br>
Note1: The counter unit is ETU based and the interval of time-out is RFTM + 0.5.
<br>
Note2: Filling in all 0 to this field indicates to disable this function.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SC_T::ETUCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ETUCTL
</font><br><p> <font size="2">
Offset: 0x14  SC Element Time Unit Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[11:0]</td><td>ETURDIV</td><td><div style="word-wrap: break-word;"><b>ETU Rate Divider
</b><br>
The field is used for ETU clock rate divider.
<br>
The real ETU is ETURDIV + 1.
<br>
Note: User can configure this field, but this field must be greater than 0x04.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SC_T::INTEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTEN
</font><br><p> <font size="2">
Offset: 0x18  SC Interrupt Enable Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>RDAIEN</td><td><div style="word-wrap: break-word;"><b>Receive Data Reach Interrupt Enable Bit
</b><br>
This field is used to enable received data reaching trigger level RXTRGLV (SCn_CTL[7:6]) interrupt.
<br>
0 = Receive data reach trigger level interrupt Disabled.
<br>
1 = Receive data reach trigger level interrupt Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>TBEIEN</td><td><div style="word-wrap: break-word;"><b>Transmit Buffer Empty Interrupt Enable Bit
</b><br>
This field is used to enable transmit buffer empty interrupt.
<br>
0 = Transmit buffer empty interrupt Disabled.
<br>
1 = Transmit buffer empty interrupt Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>TERRIEN</td><td><div style="word-wrap: break-word;"><b>Transfer Error Interrupt Enable Bit
</b><br>
This field is used to enable transfer error interrupt
<br>
The transfer error states is at SCn_STATUS register which includes receiver break error
<br>
BEF (SCn_STATUS[6]), frame error FEF (SCn_STATUS[5]), parity error PEF (SCn_STATUS[4]), receive
<br>
buffer overflow error RXOV (SCn_STATUS[0]), transmit buffer overflow error TXOV (SCn_STATUS[8]),
<br>
receiver retry over limit error RXOVERR (SCn_STATUS[22]) and transmitter retry over limit error
<br>
TXOVERR (SCn_STATUS[30]).
<br>
0 = Transfer error interrupt Disabled.
<br>
1 = Transfer error interrupt Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>TMR0IEN</td><td><div style="word-wrap: break-word;"><b>Timer0 Interrupt Enable Bit
</b><br>
This field is used to enable Timer0 interrupt function.
<br>
0 = Timer0 interrupt Disabled.
<br>
1 = Timer0 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>TMR1IEN</td><td><div style="word-wrap: break-word;"><b>Timer1 Interrupt Enable Bit
</b><br>
This field is used to enable the Timer1 interrupt function.
<br>
0 = Timer1 interrupt Disabled.
<br>
1 = Timer1 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>TMR2IEN</td><td><div style="word-wrap: break-word;"><b>Timer2 Interrupt Enable Bit
</b><br>
This field is used to enable Timer2 interrupt function.
<br>
0 = Timer2 interrupt Disabled.
<br>
1 = Timer2 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>BGTIEN</td><td><div style="word-wrap: break-word;"><b>Block Guard Time Interrupt Enable Bit
</b><br>
This field is used to enable block guard time interrupt in receive direction.
<br>
0 = Block guard time interrupt Disabled.
<br>
1 = Block guard time interrupt Enabled.
<br>
Note: This bit is valid only for receive direction block guard time.
<br>
</div></td></tr><tr><td>
[7]</td><td>CDIEN</td><td><div style="word-wrap: break-word;"><b>Card Detect Interrupt Enable Bit
</b><br>
This field is used to enable card detect interrupt
<br>
The card detect status is CDPINSTS (SCn_STATUS[13]).
<br>
0 = Card detect interrupt Disabled.
<br>
1 = Card detect interrupt Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>INITIEN</td><td><div style="word-wrap: break-word;"><b>Initial End Interrupt Enable Bit
</b><br>
This field is used to enable activation (ACTEN (SCn_ALTCTL[3] = 1)), deactivation
<br>
(DACTEN (SCn_ALTCTL[2] = 1)) and warm reset (WARSTEN (SCn_ALTCTL [4])) sequence complete interrupt.
<br>
0 = Initial end interrupt Disabled.
<br>
1 = Initial end interrupt Enabled.
<br>
</div></td></tr><tr><td>
[9]</td><td>RXTOIEN</td><td><div style="word-wrap: break-word;"><b>Receiver Buffer Time-out Interrupt Enable Bit
</b><br>
This field is used to enable receiver buffer time-out interrupt.
<br>
0 = Receiver buffer time-out interrupt Disabled.
<br>
1 = Receiver buffer time-out interrupt Enabled.
<br>
</div></td></tr><tr><td>
[10]</td><td>ACERRIEN</td><td><div style="word-wrap: break-word;"><b>Auto Convention Error Interrupt Enable Bit
</b><br>
This field is used to enable auto-convention error interrupt.
<br>
0 = Auto-convention error interrupt Disabled.
<br>
1 = Auto-convention error interrupt Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SC_T::INTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTSTS
</font><br><p> <font size="2">
Offset: 0x1C  SC Interrupt Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>RDAIF</td><td><div style="word-wrap: break-word;"><b>Receive Data Reach Interrupt Status Flag (Read Only)
</b><br>
This field is used for received data reaching trigger level RXTRGLV (SCn_CTL[7:6]) interrupt status flag.
<br>
0 = Number of receive buffer is less than RXTRGLV setting.
<br>
1 = Number of receive buffer data equals the RXTRGLV setting.
<br>
Note: This bit is read only
<br>
If user reads data from SCn_DAT and receiver buffer data byte number is less than RXTRGLV,
<br>
this bit will be cleared automatically.
<br>
</div></td></tr><tr><td>
[1]</td><td>TBEIF</td><td><div style="word-wrap: break-word;"><b>Transmit Buffer Empty Interrupt Status Flag (Read Only)
</b><br>
This field is used for transmit buffer empty interrupt status flag.
<br>
0 = Transmit buffer is not empty.
<br>
1 = Transmit buffer is empty.
<br>
Note: This bit is read only
<br>
If user wants to clear this bit, user must write data to DAT (SCn_DAT[7:0]) and then this bit
<br>
will be cleared automatically.
<br>
</div></td></tr><tr><td>
[2]</td><td>TERRIF</td><td><div style="word-wrap: break-word;"><b>Transfer Error Interrupt Status Flag
</b><br>
This field is used for transfer error interrupt status flag
<br>
The transfer error states is at SCn_STATUS register which includes receiver break error
<br>
BEF (SCn_STATUS[6]), frame error FEF (SCn_STATUS[5], parity error PEF (SCn_STATUS[4] and receive
<br>
buffer overflow error RXOV (SCn_STATUS[0]), transmit buffer overflow error TXOV (SCn_STATUS[8]),
<br>
receiver retry over limit error RXOVERR (SCn_STATUS[22] or transmitter retry over limit error
<br>
TXOVERR (SCn_STATUS[30]).
<br>
0 = Transfer error interrupt did not occur.
<br>
1 = Transfer error interrupt occurred.
<br>
Note1: This field is the status flag of BEF, FEF, PEF, RXOV, TXOV, RXOVERR or TXOVERR.
<br>
Note2: This bit can be cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[3]</td><td>TMR0IF</td><td><div style="word-wrap: break-word;"><b>Timer0 Interrupt Status Flag
</b><br>
This field is used for Timer0 interrupt status flag.
<br>
0 = Timer0 interrupt did not occur.
<br>
1 = Timer0 interrupt occurred.
<br>
Note: This bit can be cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[4]</td><td>TMR1IF</td><td><div style="word-wrap: break-word;"><b>Timer1 Interrupt Status Flag
</b><br>
This field is used for Timer1 interrupt status flag.
<br>
0 = Timer1 interrupt did not occur.
<br>
1 = Timer1 interrupt occurred.
<br>
Note: This bit can be cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[5]</td><td>TMR2IF</td><td><div style="word-wrap: break-word;"><b>Timer2 Interrupt Status Flag
</b><br>
This field is used for Timer2 interrupt status flag.
<br>
0 = Timer2 interrupt did not occur.
<br>
1 = Timer2 interrupt occurred.
<br>
Note: This bit can be cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[6]</td><td>BGTIF</td><td><div style="word-wrap: break-word;"><b>Block Guard Time Interrupt Status Flag
</b><br>
This field is used for indicate block guard time interrupt status flag in receive direction.
<br>
0 = Block guard time interrupt did not occur.
<br>
1 = Block guard time interrupt occurred.
<br>
Note1: This bit is valid only when RXBGTEN (SCn_ALTCTL[12]) is enabled.
<br>
Note2: This bit can be cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[7]</td><td>CDIF</td><td><div style="word-wrap: break-word;"><b>Card Detect Interrupt Status Flag (Read Only)
</b><br>
This field is used for card detect interrupt status flag
<br>
The card detect status is CINSERT (SCn_STATUS[12]) and CREMOVE (SCn_STATUS[11]).
<br>
0 = Card detect event did not occur.
<br>
1 = Card detect event occurred.
<br>
Note: This bit is read only, user must to clear CINSERT or CREMOVE status to clear it.
<br>
</div></td></tr><tr><td>
[8]</td><td>INITIF</td><td><div style="word-wrap: break-word;"><b>Initial End Interrupt Status Flag
</b><br>
This field is used for activation (ACTEN (SCn_ALTCTL[3])), deactivation (DACTEN (SCn_ALTCTL[2]))
<br>
and warm reset (WARSTEN (SCn_ALTCTL[4])) sequence interrupt status flag.
<br>
0 = Initial sequence is not complete.
<br>
1 = Initial sequence is completed.
<br>
Note: This bit can be cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[9]</td><td>RXTOIF</td><td><div style="word-wrap: break-word;"><b>Receive Buffer Time-out Interrupt Status Flag (Read Only)
</b><br>
This field is used for indicate receive buffer time-out interrupt status flag.
<br>
0 = Receive buffer time-out interrupt did not occur.
<br>
1 = Receive buffer time-out interrupt occurred.
<br>
Note: This bit is read only, user must read all receive buffer remaining data by reading SCn_DAT
<br>
register to clear it.
<br>
</div></td></tr><tr><td>
[10]</td><td>ACERRIF</td><td><div style="word-wrap: break-word;"><b>Auto Convention Error Interrupt Status Flag
</b><br>
This field indicates auto convention sequence error.
<br>
0 = Received TS at ATR state is 0x3B or 0x3F.
<br>
1 = Received TS at ATR state is neither 0x3B nor 0x3F.
<br>
Note: This bit can be cleared by writing 1 to it.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SC_T::STATUS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STATUS
</font><br><p> <font size="2">
Offset: 0x20  SC Transfer Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>RXOV</td><td><div style="word-wrap: break-word;"><b>Receive Overflow Error Status Flag
</b><br>
This bit is set when Rx buffer overflow.
<br>
0 = Rx buffer is not overflow.
<br>
1 = Rx buffer is overflow when the number of received bytes is greater than Rx buffer size (4 bytes).
<br>
Note: This bit can be cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[1]</td><td>RXEMPTY</td><td><div style="word-wrap: break-word;"><b>Receive Buffer Empty Status Flag (Read Only)
</b><br>
This bit indicates Rx buffer empty or not.
<br>
0 = Rx buffer is not empty.
<br>
1 = Rx buffer is empty, it means the last byte of Rx buffer has read from DAT (SCn_DAT[7:0]) by CPU.
<br>
</div></td></tr><tr><td>
[2]</td><td>RXFULL</td><td><div style="word-wrap: break-word;"><b>Receive Buffer Full Status Flag (Read Only)
</b><br>
This bit indicates Rx buffer full or not.
<br>
0 = Rx buffer count is less than 4.
<br>
1 = Rx buffer count equals to 4.
<br>
</div></td></tr><tr><td>
[4]</td><td>PEF</td><td><div style="word-wrap: break-word;"><b>Receiver Parity Error Status Flag
</b><br>
This bit is set to logic 1 whenever the received character does not have a valid parity bit.
<br>
0 = Receiver parity error flag did not occur.
<br>
1 = Receiver parity error flag occurred.
<br>
Note1: This bit can be cleared by writing 1 to it.
<br>
Note2: If CPU sets receiver retries function by setting RXRTYEN (SCn_CTL[19]), hardware will not
<br>
set this flag.
<br>
</div></td></tr><tr><td>
[5]</td><td>FEF</td><td><div style="word-wrap: break-word;"><b>Receiver Frame Error Status Flag
</b><br>
This bit is set to logic 1 whenever the received character does not have a valid stop bit (that is,
<br>
the stop bit following the last data bit or parity bit is detected as logic 0).
<br>
0 = Receiver frame error flag did not occur.
<br>
1 = Receiver frame error flag occurred.
<br>
Note1: This bit can be cleared by writing 1 to it.
<br>
Note2: If CPU sets receiver retries function by setting RXRTYEN (SCn_CTL[19]), hardware will not
<br>
set this flag.
<br>
</div></td></tr><tr><td>
[6]</td><td>BEF</td><td><div style="word-wrap: break-word;"><b>Receiver Break Error Status Flag
</b><br>
This bit is set to logic 1 whenever the received data input (Rx) held in the spacing state
<br>
(logic 0) is longer than a full word transmission time (that is, the total time of start bit +
<br>
data bits + parity bit + stop bit).
<br>
0 = Receiver break error flag did not occur.
<br>
1 = Receiver break error flag occurred.
<br>
Note1: This bit can be cleared by writing 1 to it.
<br>
Note2: If CPU sets receiver retries function by setting RXRTYEN (SCn_CTL[19]), hardware will not set
<br>
this flag.
<br>
</div></td></tr><tr><td>
[8]</td><td>TXOV</td><td><div style="word-wrap: break-word;"><b>Transmit Overflow Error Interrupt Status Flag
</b><br>
This bit is set when Tx buffer overflow.
<br>
0 = Tx buffer is not overflow.
<br>
1 = Tx buffer is overflow when Tx buffer is full and an additional write operation to DAT (SCn_DAT[7:0]).
<br>
Note: This bit can be cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[9]</td><td>TXEMPTY</td><td><div style="word-wrap: break-word;"><b>Transmit Buffer Empty Status Flag (Read Only)
</b><br>
This bit indicates TX buffer empty or not.
<br>
0 = Tx buffer is not empty.
<br>
1 = Tx buffer is empty, it means the last byte of Tx buffer has been transferred to Transmitter
<br>
Shift Register.
<br>
Note: This bit will be cleared when writing data into DAT (SCn_DAT[7:0]).
<br>
</div></td></tr><tr><td>
[10]</td><td>TXFULL</td><td><div style="word-wrap: break-word;"><b>Transmit Buffer Full Status Flag (Read Only)
</b><br>
This bit indicates Tx buffer full or not.
<br>
0 = Tx buffer count is less than 4.
<br>
1 = Tx buffer count equals to 4.
<br>
</div></td></tr><tr><td>
[11]</td><td>CREMOVE</td><td><div style="word-wrap: break-word;"><b>Card Removal Status of SCn_CD Pin
</b><br>
This bit is set whenever card has been removal.
<br>
0 = No effect.
<br>
1 = Card removed.
<br>
Note1: This bit can be cleared by writing 1 to it.
<br>
Note2: Card detect function will start after SCEN (SCn_CTL[0]) set.
<br>
</div></td></tr><tr><td>
[12]</td><td>CINSERT</td><td><div style="word-wrap: break-word;"><b>Card Insert Status of SCn_CD Pin
</b><br>
This bit is set whenever card has been inserted.
<br>
0 = No effect.
<br>
1 = Card insert.
<br>
Note1: This bit can be cleared by writing 1 to it.
<br>
Note2: The card detect function will start after SCEN (SCn_CTL[0]) set.
<br>
</div></td></tr><tr><td>
[13]</td><td>CDPINSTS</td><td><div style="word-wrap: break-word;"><b>Card Detect Pin Status (Read Only)
</b><br>
This bit is the pin status of SCn_CD.
<br>
0 = The SCn_CD pin state at low.
<br>
1 = The SCn_CD pin state at high.
<br>
</div></td></tr><tr><td>
[18:16]</td><td>RXPOINT</td><td><div style="word-wrap: break-word;"><b>Receive Buffer Pointer Status (Read Only)
</b><br>
This field indicates the Rx buffer pointer status
<br>
When SC controller receives one byte from external device, RXPOINT increases one
<br>
When one byte of Rx buffer is read by CPU, RXPOINT decreases one.
<br>
</div></td></tr><tr><td>
[21]</td><td>RXRERR</td><td><div style="word-wrap: break-word;"><b>Receiver Retry Error
</b><br>
This bit is used for receiver error retry and set by hardware.
<br>
0 = No Rx retry transfer.
<br>
1 = Rx has any error and retries transfer.
<br>
Note1: This bit can be cleared by writing 1 to it.
<br>
Note2 This bit is a flag and cannot generate any interrupt to CPU.
<br>
Note3: If CPU enables receiver retries function by setting RXRTYEN (SCn_CTL[19]),
<br>
hardware will not set this flag.
<br>
</div></td></tr><tr><td>
[22]</td><td>RXOVERR</td><td><div style="word-wrap: break-word;"><b>Receiver over Retry Error
</b><br>
This bit is used for receiver retry counts over than retry number limitation.
<br>
0 = Receiver retries counts is not over than RXRTY (SCn_CTL[18:16]) + 1.
<br>
1 = Receiver retries counts over than RXRTY (SCn_CTL[18:16]) + 1.
<br>
Note1: This bit can be cleared by writing 1 to it.
<br>
Note2: If CPU enables receiver retries function by setting RXRTYEN (SCn_CTL[19]), hardware
<br>
will not set this flag.
<br>
</div></td></tr><tr><td>
[23]</td><td>RXACT</td><td><div style="word-wrap: break-word;"><b>Receiver in Active Status Flag (Read Only)
</b><br>
This bit indicates Rx transfer status.
<br>
0 = This bit is cleared automatically when Rx transfer is finished.
<br>
1 = This bit is set by hardware when Rx transfer is in active.
<br>
Note: This bit is read only.
<br>
</div></td></tr><tr><td>
[26:24]</td><td>TXPOINT</td><td><div style="word-wrap: break-word;"><b>Transmit Buffer Pointer Status (Read Only)
</b><br>
This field indicates the Tx buffer pointer status
<br>
When CPU writes data into SCn_DAT, TXPOINT increases one
<br>
When one byte of Tx buffer is transferred to transmitter shift register, TXPOINT decreases one.
<br>
</div></td></tr><tr><td>
[29]</td><td>TXRERR</td><td><div style="word-wrap: break-word;"><b>Transmitter Retry Error
</b><br>
This bit is used for indicate transmitter error retry and set by hardware.
<br>
0 = No Tx retry transfer.
<br>
1 = Tx has any error and retries transfer.
<br>
Note1: This bit can be cleared by writing 1 to it.
<br>
Note2: This bit is a flag and cannot generate any interrupt to CPU.
<br>
</div></td></tr><tr><td>
[30]</td><td>TXOVERR</td><td><div style="word-wrap: break-word;"><b>Transmitter over Retry Error
</b><br>
This bit is used for transmitter retry counts over than retry number limitation.
<br>
0 = Transmitter retries counts is not over than TXRTY (SCn_CTL[22:20]) + 1.
<br>
1 = Transmitter retries counts over than TXRTY (SCn_CTL[22:20]) + 1.
<br>
Note: This bit can be cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[31]</td><td>TXACT</td><td><div style="word-wrap: break-word;"><b>Transmit in Active Status Flag (Read Only)
</b><br>
This bit indicates Tx transmit status.
<br>
0 = This bit is cleared automatically when Tx transfer is finished or the last byte transmission
<br>
has completed.
<br>
1 = Transmit is active and this bit is set by hardware when Tx transfer is in active and the STOP
<br>
bit of the last byte has not been transmitted.
<br>
Note: This bit is read only.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SC_T::PINCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PINCTL
</font><br><p> <font size="2">
Offset: 0x24  SC Pin Control State Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>PWREN</td><td><div style="word-wrap: break-word;"><b>SCn_PWR Pin Signal
</b><br>
User can set PWRINV (SCn_PINCTL[11]) and PWREN (SCn_PINCTL[0]) to decide SCn_PWR pin is in high or low level.
<br>
Write this field to drive SCn_PWR pin
<br>
Refer PWRINV (SCn_PINCTL[11]) description for programming SCn_PWR pin voltage level.
<br>
Read this field to get SCn_PWR signal status.
<br>
0 = SCn_PWR signal status is low.
<br>
1 = SCn_PWR signal status is high.
<br>
Note: When operating at activation, warm reset or deactivation mode, this bit will be changed automatically.
<br>
Thus, do not fill in this field when operating in these modes.
<br>
</div></td></tr><tr><td>
[1]</td><td>RSTEN</td><td><div style="word-wrap: break-word;"><b>SCn_RST Pin Signal
</b><br>
User can set RSTEN (SCn_PINCTL[1]) to decide SCn_RST pin is in high or low level.
<br>
Write this field to drive SCn_RST pin.
<br>
0 = Drive SCn_RST pin to low.
<br>
1 = Drive SCn_RST pin to high.
<br>
Read this field to get SCn_RST signal status.
<br>
0 = SCn_RST signal status is low.
<br>
1 = SCn_RST signal status is high.
<br>
Note: When operating at activation, warm reset or deactivation mode, this bit will be changed automatically.
<br>
Thus, do not fill in this field when operating in these modes.
<br>
</div></td></tr><tr><td>
[6]</td><td>CLKKEEP</td><td><div style="word-wrap: break-word;"><b>SC Clock Enable Bit
</b><br>
0 = SC clock generation Disabled.
<br>
1 = SC clock always keeps free running.
<br>
Note: When operating in activation, warm reset or deactivation mode, this bit will be changed automatically.
<br>
Thus, do not fill in this field when operating in these modes.
<br>
</div></td></tr><tr><td>
[9]</td><td>SCDATA</td><td><div style="word-wrap: break-word;"><b>SCn_DATA Pin Signal
</b><br>
This bit is the signal status of SCn_DATA but user can drive SCn_DATA pin to high or low by setting this bit.
<br>
0 = Drive SCn_DATA pin to low.
<br>
1 = Drive SCn_DATA pin to high.
<br>
Read this field to get SCn_DATA signal status.
<br>
0 = SCn_DATA signal status is low.
<br>
1 = SCn_DATA signal status is high.
<br>
Note: When SC is at activation, warm reset or deactivation mode, this bit will be changed automatically.
<br>
Thus, do not fill in this field when SC is in these modes.
<br>
</div></td></tr><tr><td>
[11]</td><td>PWRINV</td><td><div style="word-wrap: break-word;"><b>SCn_PWR Pin Inverse
</b><br>
This bit is used for inverse the SCn_PWR pin.
<br>
There are four kinds of combination for SCn_PWR pin setting by PWRINV (SCn_PINCTL[11]) and PWREN (SCn_PINCTL[0]).
<br>
PWRINV is 0 and PWREN is 0, SCn_PWR pin is 0.
<br>
PWRINV is 0 and PWREN is 1, SCn_PWR pin is 1.
<br>
PWRINV is 1 and PWREN is 0, SCn_PWR pin is 1.
<br>
PWRINV is 1 and PWREN is 1, SCn_PWR pin is 0.
<br>
Note: User must select PWRINV (SCn_PINCTL[11]) before smart card is enabled by SCEN (SCn_CTL[0]).
<br>
</div></td></tr><tr><td>
[16]</td><td>DATASTS</td><td><div style="word-wrap: break-word;"><b>SCn_DATA Pin Status (Read Only)
</b><br>
This bit is the pin status of SCn_DATA.
<br>
0 = The SCn_DATA pin status is low.
<br>
1 = The SCn_DATA pin status is high.
<br>
</div></td></tr><tr><td>
[17]</td><td>PWRSTS</td><td><div style="word-wrap: break-word;"><b>SCn_PWR Pin Status (Read Only)
</b><br>
This bit is the pin status of SCn_PWR.
<br>
0 = SCn_PWR pin to low.
<br>
1 = SCn_PWR pin to high.
<br>
</div></td></tr><tr><td>
[18]</td><td>RSTSTS</td><td><div style="word-wrap: break-word;"><b>SCn_RST Pin Status (Read Only)
</b><br>
This bit is the pin status of SCn_RST.
<br>
0 = SCn_RST pin is low.
<br>
1 = SCn_RST pin is high.
<br>
</div></td></tr><tr><td>
[30]</td><td>SYNC</td><td><div style="word-wrap: break-word;"><b>SYNC Flag Indicator (Read Only)
</b><br>
Due to synchronization, user should check this bit when writing a new value to SCn_PINCTL register.
<br>
0 = Synchronizing is completion, user can write new data to SCn_PINCTL register.
<br>
1 = Last value is synchronizing.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SC_T::TMRCTL0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TMRCTL0
</font><br><p> <font size="2">
Offset: 0x28  SC Internal Timer0 Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:0]</td><td>CNT</td><td><div style="word-wrap: break-word;"><b>Timer0 Counter Value
</b><br>
This field indicates the internal Timer0 counter values.
<br>
Note: Unit of Timer0 counter is ETU base.
<br>
</div></td></tr><tr><td>
[27:24]</td><td>OPMODE</td><td><div style="word-wrap: break-word;"><b>Timer0 Operation Mode Selection
</b><br>
This field indicates the internal 24-bit Timer0 operation selection.
<br>
Refer to Table 7.17-3 for programming Timer0.
<br>
</div></td></tr><tr><td>
[31]</td><td>SYNC</td><td><div style="word-wrap: break-word;"><b>SYNC Flag Indicator (Read Only)
</b><br>
Due to synchronization, user should check this bit when writing a new value to the SCn_TMRCTL0 register.
<br>
0 = Synchronizing is completion, user can write new data to SCn_TMRCTL0 register.
<br>
1 = Last value is synchronizing.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SC_T::TMRCTL1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TMRCTL1
</font><br><p> <font size="2">
Offset: 0x2C  SC Internal Timer1 Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>CNT</td><td><div style="word-wrap: break-word;"><b>Timer 1 Counter Value
</b><br>
This field indicates the internal Timer1 counter values.
<br>
Note: Unit of Timer1 counter is ETU base.
<br>
</div></td></tr><tr><td>
[27:24]</td><td>OPMODE</td><td><div style="word-wrap: break-word;"><b>Timer 1 Operation Mode Selection
</b><br>
This field indicates the internal 8-bit Timer1 operation selection.
<br>
Refer to Table 7.17-3 for programming Timer1.
<br>
</div></td></tr><tr><td>
[31]</td><td>SYNC</td><td><div style="word-wrap: break-word;"><b>SYNC Flag Indicator (Read Only)
</b><br>
Due to synchronization, software should check this bit when writing a new value to SCn_TMRCTL1 register.
<br>
0 = Synchronizing is completion, user can write new data to SCn_TMRCTL1 register.
<br>
1 = Last value is synchronizing.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SC_T::TMRCTL2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TMRCTL2
</font><br><p> <font size="2">
Offset: 0x30  SC Internal Timer2 Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>CNT</td><td><div style="word-wrap: break-word;"><b>Timer 2 Counter Value
</b><br>
This field indicates the internal Timer2 counter values.
<br>
Note: Unit of Timer2 counter is ETU base.
<br>
</div></td></tr><tr><td>
[27:24]</td><td>OPMODE</td><td><div style="word-wrap: break-word;"><b>Timer 2 Operation Mode Selection
</b><br>
This field indicates the internal 8-bit Timer2 operation selection
<br>
Refer to Table 7.17-3 for programming Timer2.
<br>
</div></td></tr><tr><td>
[31]</td><td>SYNC</td><td><div style="word-wrap: break-word;"><b>SYNC Flag Indicator (Read Only)
</b><br>
Due to synchronization, user should check this bit when writing a new value to SCn_TMRCTL2 register.
<br>
0 = Synchronizing is completion, user can write new data to SCn_TMRCTL2 register.
<br>
1 = Last value is synchronizing.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SC_T::UARTCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">UARTCTL
</font><br><p> <font size="2">
Offset: 0x34  SC UART Mode Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>UARTEN</td><td><div style="word-wrap: break-word;"><b>UART Mode Enable Bit
</b><br>
Sets this bit to enable UART mode function.
<br>
0 = Smart Card mode.
<br>
1 = UART mode.
<br>
Note1: When operating in UART mode, user must set CONSEL (SCn_CTL[5:4]) = 00 and AUTOCEN (SCn_CTL[3]) = 0.
<br>
Note2: When operating in Smart Card mode, user must set UARTEN (SCn_UARTCTL[0]) = 0.
<br>
Note3: When UART mode is enabled, hardware will generate a reset to reset FIFO and internal state machine.
<br>
</div></td></tr><tr><td>
[5:4]</td><td>WLS</td><td><div style="word-wrap: break-word;"><b>Word Length Selection
</b><br>
This field is used for select UART data length.
<br>
00 = Word length is 8 bits.
<br>
01 = Word length is 7 bits.
<br>
10 = Word length is 6 bits.
<br>
11 = Word length is 5 bits.
<br>
Note: In smart card mode, this WLS must be '00'.
<br>
</div></td></tr><tr><td>
[6]</td><td>PBOFF</td><td><div style="word-wrap: break-word;"><b>Parity Bit Disable Control
</b><br>
Sets this bit is used for disable parity check function.
<br>
0 = Parity bit is generated or checked between the last data word bit and stop bit of the serial data.
<br>
1 = Parity bit is not generated (transmitting data) or checked (receiving data) during transfer.
<br>
Note: In smart card mode, this field must be '0' (default setting is with parity bit).
<br>
</div></td></tr><tr><td>
[7]</td><td>OPE</td><td><div style="word-wrap: break-word;"><b>Odd Parity Enable Bit
</b><br>
This is used for odd/even parity selection.
<br>
0 = Even number of logic 1's are transmitted or check the data word and parity bits in receiving mode.
<br>
1 = Odd number of logic 1's are transmitted or check the data word and parity bits in receiving mode.
<br>
Note: This bit has effect only when PBOFF bit is '0'.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SC_T::ACTCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ACTCTL
</font><br><p> <font size="2">
Offset: 0x4C  SC Activation Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[4:0]</td><td>T1EXT</td><td><div style="word-wrap: break-word;"><b>T1 Extend Time of Hardware Activation
</b><br>
This field provide the configurable cycles to extend the activation time T1 period.
<br>
The cycle scaling factor is 2048.
<br>
Extend cycles = (filled value * 2048) cycles.
<br>
Refer to SC activation sequence in Figure 7.17-4.
<br>
For example,
<br>
SCLK = 4MHz, each cycle = 0.25us,.
<br>
Filled 20 to this field
<br>
Extend time = 20 * 2048 * 0.25us = 10.24 ms.
<br>
Note: Setting 0 to this field conforms to the protocol ISO/IEC 7816-3
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t DAT;                   /*!< [0x0000] SC Receive/Transmit Holding Buffer Register                      */
    __IO uint32_t CTL;                   /*!< [0x0004] SC Control Register                                              */
    __IO uint32_t ALTCTL;                /*!< [0x0008] SC Alternate Control Register                                    */
    __IO uint32_t EGT;                   /*!< [0x000c] SC Extra Guard Time Register                                     */
    __IO uint32_t RXTOUT;                /*!< [0x0010] SC Receive Buffer Time-out Counter Register                      */
    __IO uint32_t ETUCTL;                /*!< [0x0014] SC Element Time Unit Control Register                            */
    __IO uint32_t INTEN;                 /*!< [0x0018] SC Interrupt Enable Control Register                             */
    __IO uint32_t INTSTS;                /*!< [0x001c] SC Interrupt Status Register                                     */
    __IO uint32_t STATUS;                /*!< [0x0020] SC Transfer Status Register                                      */
    __IO uint32_t PINCTL;                /*!< [0x0024] SC Pin Control State Register                                    */
    __IO uint32_t TMRCTL0;               /*!< [0x0028] SC Internal Timer0 Control Register                              */
    __IO uint32_t TMRCTL1;               /*!< [0x002c] SC Internal Timer1 Control Register                              */
    __IO uint32_t TMRCTL2;               /*!< [0x0030] SC Internal Timer2 Control Register                              */
    __IO uint32_t UARTCTL;               /*!< [0x0034] SC UART Mode Control Register                                    */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE0[5];
    /** @endcond */
    __IO uint32_t ACTCTL;                /*!< [0x004c] SC Activation Control Register                                   */

} SC_T;

/**
    @addtogroup SC_CONST SC Bit Field Definition
    Constant Definitions for SC Controller
@{ */

#define SC_DAT_DAT_Pos                   (0)                                               /*!< SC_T::DAT: DAT Position                */
#define SC_DAT_DAT_Msk                   (0xfful << SC_DAT_DAT_Pos)                        /*!< SC_T::DAT: DAT Mask                    */

#define SC_CTL_SCEN_Pos                  (0)                                               /*!< SC_T::CTL: SCEN Position               */
#define SC_CTL_SCEN_Msk                  (0x1ul << SC_CTL_SCEN_Pos)                        /*!< SC_T::CTL: SCEN Mask                   */

#define SC_CTL_RXOFF_Pos                 (1)                                               /*!< SC_T::CTL: RXOFF Position              */
#define SC_CTL_RXOFF_Msk                 (0x1ul << SC_CTL_RXOFF_Pos)                       /*!< SC_T::CTL: RXOFF Mask                  */

#define SC_CTL_TXOFF_Pos                 (2)                                               /*!< SC_T::CTL: TXOFF Position              */
#define SC_CTL_TXOFF_Msk                 (0x1ul << SC_CTL_TXOFF_Pos)                       /*!< SC_T::CTL: TXOFF Mask                  */

#define SC_CTL_AUTOCEN_Pos               (3)                                               /*!< SC_T::CTL: AUTOCEN Position            */
#define SC_CTL_AUTOCEN_Msk               (0x1ul << SC_CTL_AUTOCEN_Pos)                     /*!< SC_T::CTL: AUTOCEN Mask                */

#define SC_CTL_CONSEL_Pos                (4)                                               /*!< SC_T::CTL: CONSEL Position             */
#define SC_CTL_CONSEL_Msk                (0x3ul << SC_CTL_CONSEL_Pos)                      /*!< SC_T::CTL: CONSEL Mask                 */

#define SC_CTL_RXTRGLV_Pos               (6)                                               /*!< SC_T::CTL: RXTRGLV Position            */
#define SC_CTL_RXTRGLV_Msk               (0x3ul << SC_CTL_RXTRGLV_Pos)                     /*!< SC_T::CTL: RXTRGLV Mask                */

#define SC_CTL_BGT_Pos                   (8)                                               /*!< SC_T::CTL: BGT Position                */
#define SC_CTL_BGT_Msk                   (0x1ful << SC_CTL_BGT_Pos)                        /*!< SC_T::CTL: BGT Mask                    */

#define SC_CTL_TMRSEL_Pos                (13)                                              /*!< SC_T::CTL: TMRSEL Position             */
#define SC_CTL_TMRSEL_Msk                (0x3ul << SC_CTL_TMRSEL_Pos)                      /*!< SC_T::CTL: TMRSEL Mask                 */

#define SC_CTL_NSB_Pos                   (15)                                              /*!< SC_T::CTL: NSB Position                */
#define SC_CTL_NSB_Msk                   (0x1ul << SC_CTL_NSB_Pos)                         /*!< SC_T::CTL: NSB Mask                    */

#define SC_CTL_RXRTY_Pos                 (16)                                              /*!< SC_T::CTL: RXRTY Position              */
#define SC_CTL_RXRTY_Msk                 (0x7ul << SC_CTL_RXRTY_Pos)                       /*!< SC_T::CTL: RXRTY Mask                  */

#define SC_CTL_RXRTYEN_Pos               (19)                                              /*!< SC_T::CTL: RXRTYEN Position            */
#define SC_CTL_RXRTYEN_Msk               (0x1ul << SC_CTL_RXRTYEN_Pos)                     /*!< SC_T::CTL: RXRTYEN Mask                */

#define SC_CTL_TXRTY_Pos                 (20)                                              /*!< SC_T::CTL: TXRTY Position              */
#define SC_CTL_TXRTY_Msk                 (0x7ul << SC_CTL_TXRTY_Pos)                       /*!< SC_T::CTL: TXRTY Mask                  */

#define SC_CTL_TXRTYEN_Pos               (23)                                              /*!< SC_T::CTL: TXRTYEN Position            */
#define SC_CTL_TXRTYEN_Msk               (0x1ul << SC_CTL_TXRTYEN_Pos)                     /*!< SC_T::CTL: TXRTYEN Mask                */

#define SC_CTL_CDDBSEL_Pos               (24)                                              /*!< SC_T::CTL: CDDBSEL Position            */
#define SC_CTL_CDDBSEL_Msk               (0x3ul << SC_CTL_CDDBSEL_Pos)                     /*!< SC_T::CTL: CDDBSEL Mask                */

#define SC_CTL_CDLV_Pos                  (26)                                              /*!< SC_T::CTL: CDLV Position               */
#define SC_CTL_CDLV_Msk                  (0x1ul << SC_CTL_CDLV_Pos)                        /*!< SC_T::CTL: CDLV Mask                   */

#define SC_CTL_SYNC_Pos                  (30)                                              /*!< SC_T::CTL: SYNC Position               */
#define SC_CTL_SYNC_Msk                  (0x1ul << SC_CTL_SYNC_Pos)                        /*!< SC_T::CTL: SYNC Mask                   */

#define SC_ALTCTL_TXRST_Pos              (0)                                               /*!< SC_T::ALTCTL: TXRST Position           */
#define SC_ALTCTL_TXRST_Msk              (0x1ul << SC_ALTCTL_TXRST_Pos)                    /*!< SC_T::ALTCTL: TXRST Mask               */

#define SC_ALTCTL_RXRST_Pos              (1)                                               /*!< SC_T::ALTCTL: RXRST Position           */
#define SC_ALTCTL_RXRST_Msk              (0x1ul << SC_ALTCTL_RXRST_Pos)                    /*!< SC_T::ALTCTL: RXRST Mask               */

#define SC_ALTCTL_DACTEN_Pos             (2)                                               /*!< SC_T::ALTCTL: DACTEN Position          */
#define SC_ALTCTL_DACTEN_Msk             (0x1ul << SC_ALTCTL_DACTEN_Pos)                   /*!< SC_T::ALTCTL: DACTEN Mask              */

#define SC_ALTCTL_ACTEN_Pos              (3)                                               /*!< SC_T::ALTCTL: ACTEN Position           */
#define SC_ALTCTL_ACTEN_Msk              (0x1ul << SC_ALTCTL_ACTEN_Pos)                    /*!< SC_T::ALTCTL: ACTEN Mask               */

#define SC_ALTCTL_WARSTEN_Pos            (4)                                               /*!< SC_T::ALTCTL: WARSTEN Position         */
#define SC_ALTCTL_WARSTEN_Msk            (0x1ul << SC_ALTCTL_WARSTEN_Pos)                  /*!< SC_T::ALTCTL: WARSTEN Mask             */

#define SC_ALTCTL_CNTEN0_Pos             (5)                                               /*!< SC_T::ALTCTL: CNTEN0 Position          */
#define SC_ALTCTL_CNTEN0_Msk             (0x1ul << SC_ALTCTL_CNTEN0_Pos)                   /*!< SC_T::ALTCTL: CNTEN0 Mask              */

#define SC_ALTCTL_CNTEN1_Pos             (6)                                               /*!< SC_T::ALTCTL: CNTEN1 Position          */
#define SC_ALTCTL_CNTEN1_Msk             (0x1ul << SC_ALTCTL_CNTEN1_Pos)                   /*!< SC_T::ALTCTL: CNTEN1 Mask              */

#define SC_ALTCTL_CNTEN2_Pos             (7)                                               /*!< SC_T::ALTCTL: CNTEN2 Position          */
#define SC_ALTCTL_CNTEN2_Msk             (0x1ul << SC_ALTCTL_CNTEN2_Pos)                   /*!< SC_T::ALTCTL: CNTEN2 Mask              */

#define SC_ALTCTL_INITSEL_Pos            (8)                                               /*!< SC_T::ALTCTL: INITSEL Position         */
#define SC_ALTCTL_INITSEL_Msk            (0x3ul << SC_ALTCTL_INITSEL_Pos)                  /*!< SC_T::ALTCTL: INITSEL Mask             */

#define SC_ALTCTL_ADACEN_Pos             (11)                                              /*!< SC_T::ALTCTL: ADACEN Position          */
#define SC_ALTCTL_ADACEN_Msk             (0x1ul << SC_ALTCTL_ADACEN_Pos)                   /*!< SC_T::ALTCTL: ADACEN Mask              */

#define SC_ALTCTL_RXBGTEN_Pos            (12)                                              /*!< SC_T::ALTCTL: RXBGTEN Position         */
#define SC_ALTCTL_RXBGTEN_Msk            (0x1ul << SC_ALTCTL_RXBGTEN_Pos)                  /*!< SC_T::ALTCTL: RXBGTEN Mask             */

#define SC_ALTCTL_ACTSTS0_Pos            (13)                                              /*!< SC_T::ALTCTL: ACTSTS0 Position         */
#define SC_ALTCTL_ACTSTS0_Msk            (0x1ul << SC_ALTCTL_ACTSTS0_Pos)                  /*!< SC_T::ALTCTL: ACTSTS0 Mask             */

#define SC_ALTCTL_ACTSTS1_Pos            (14)                                              /*!< SC_T::ALTCTL: ACTSTS1 Position         */
#define SC_ALTCTL_ACTSTS1_Msk            (0x1ul << SC_ALTCTL_ACTSTS1_Pos)                  /*!< SC_T::ALTCTL: ACTSTS1 Mask             */

#define SC_ALTCTL_ACTSTS2_Pos            (15)                                              /*!< SC_T::ALTCTL: ACTSTS2 Position         */
#define SC_ALTCTL_ACTSTS2_Msk            (0x1ul << SC_ALTCTL_ACTSTS2_Pos)                  /*!< SC_T::ALTCTL: ACTSTS2 Mask             */

#define SC_ALTCTL_SYNC_Pos               (31)                                              /*!< SC_T::ALTCTL: SYNC Position            */
#define SC_ALTCTL_SYNC_Msk               (0x1ul << SC_ALTCTL_SYNC_Pos)                     /*!< SC_T::ALTCTL: SYNC Mask                */

#define SC_EGT_EGT_Pos                   (0)                                               /*!< SC_T::EGT: EGT Position                */
#define SC_EGT_EGT_Msk                   (0xfful << SC_EGT_EGT_Pos)                        /*!< SC_T::EGT: EGT Mask                    */

#define SC_RXTOUT_RFTM_Pos               (0)                                               /*!< SC_T::RXTOUT: RFTM Position            */
#define SC_RXTOUT_RFTM_Msk               (0x1fful << SC_RXTOUT_RFTM_Pos)                   /*!< SC_T::RXTOUT: RFTM Mask                */

#define SC_ETUCTL_ETURDIV_Pos            (0)                                               /*!< SC_T::ETUCTL: ETURDIV Position         */
#define SC_ETUCTL_ETURDIV_Msk            (0xffful << SC_ETUCTL_ETURDIV_Pos)                /*!< SC_T::ETUCTL: ETURDIV Mask             */

#define SC_INTEN_RDAIEN_Pos              (0)                                               /*!< SC_T::INTEN: RDAIEN Position           */
#define SC_INTEN_RDAIEN_Msk              (0x1ul << SC_INTEN_RDAIEN_Pos)                    /*!< SC_T::INTEN: RDAIEN Mask               */

#define SC_INTEN_TBEIEN_Pos              (1)                                               /*!< SC_T::INTEN: TBEIEN Position           */
#define SC_INTEN_TBEIEN_Msk              (0x1ul << SC_INTEN_TBEIEN_Pos)                    /*!< SC_T::INTEN: TBEIEN Mask               */

#define SC_INTEN_TERRIEN_Pos             (2)                                               /*!< SC_T::INTEN: TERRIEN Position          */
#define SC_INTEN_TERRIEN_Msk             (0x1ul << SC_INTEN_TERRIEN_Pos)                   /*!< SC_T::INTEN: TERRIEN Mask              */

#define SC_INTEN_TMR0IEN_Pos             (3)                                               /*!< SC_T::INTEN: TMR0IEN Position          */
#define SC_INTEN_TMR0IEN_Msk             (0x1ul << SC_INTEN_TMR0IEN_Pos)                   /*!< SC_T::INTEN: TMR0IEN Mask              */

#define SC_INTEN_TMR1IEN_Pos             (4)                                               /*!< SC_T::INTEN: TMR1IEN Position          */
#define SC_INTEN_TMR1IEN_Msk             (0x1ul << SC_INTEN_TMR1IEN_Pos)                   /*!< SC_T::INTEN: TMR1IEN Mask              */

#define SC_INTEN_TMR2IEN_Pos             (5)                                               /*!< SC_T::INTEN: TMR2IEN Position          */
#define SC_INTEN_TMR2IEN_Msk             (0x1ul << SC_INTEN_TMR2IEN_Pos)                   /*!< SC_T::INTEN: TMR2IEN Mask              */

#define SC_INTEN_BGTIEN_Pos              (6)                                               /*!< SC_T::INTEN: BGTIEN Position           */
#define SC_INTEN_BGTIEN_Msk              (0x1ul << SC_INTEN_BGTIEN_Pos)                    /*!< SC_T::INTEN: BGTIEN Mask               */

#define SC_INTEN_CDIEN_Pos               (7)                                               /*!< SC_T::INTEN: CDIEN Position            */
#define SC_INTEN_CDIEN_Msk               (0x1ul << SC_INTEN_CDIEN_Pos)                     /*!< SC_T::INTEN: CDIEN Mask                */

#define SC_INTEN_INITIEN_Pos             (8)                                               /*!< SC_T::INTEN: INITIEN Position          */
#define SC_INTEN_INITIEN_Msk             (0x1ul << SC_INTEN_INITIEN_Pos)                   /*!< SC_T::INTEN: INITIEN Mask              */

#define SC_INTEN_RXTOIEN_Pos             (9)                                               /*!< SC_T::INTEN: RXTOIEN Position          */
#define SC_INTEN_RXTOIEN_Msk             (0x1ul << SC_INTEN_RXTOIEN_Pos)                   /*!< SC_T::INTEN: RXTOIEN Mask              */

#define SC_INTEN_ACERRIEN_Pos            (10)                                              /*!< SC_T::INTEN: ACERRIEN Position         */
#define SC_INTEN_ACERRIEN_Msk            (0x1ul << SC_INTEN_ACERRIEN_Pos)                  /*!< SC_T::INTEN: ACERRIEN Mask             */

#define SC_INTSTS_RDAIF_Pos              (0)                                               /*!< SC_T::INTSTS: RDAIF Position           */
#define SC_INTSTS_RDAIF_Msk              (0x1ul << SC_INTSTS_RDAIF_Pos)                    /*!< SC_T::INTSTS: RDAIF Mask               */

#define SC_INTSTS_TBEIF_Pos              (1)                                               /*!< SC_T::INTSTS: TBEIF Position           */
#define SC_INTSTS_TBEIF_Msk              (0x1ul << SC_INTSTS_TBEIF_Pos)                    /*!< SC_T::INTSTS: TBEIF Mask               */

#define SC_INTSTS_TERRIF_Pos             (2)                                               /*!< SC_T::INTSTS: TERRIF Position          */
#define SC_INTSTS_TERRIF_Msk             (0x1ul << SC_INTSTS_TERRIF_Pos)                   /*!< SC_T::INTSTS: TERRIF Mask              */

#define SC_INTSTS_TMR0IF_Pos             (3)                                               /*!< SC_T::INTSTS: TMR0IF Position          */
#define SC_INTSTS_TMR0IF_Msk             (0x1ul << SC_INTSTS_TMR0IF_Pos)                   /*!< SC_T::INTSTS: TMR0IF Mask              */

#define SC_INTSTS_TMR1IF_Pos             (4)                                               /*!< SC_T::INTSTS: TMR1IF Position          */
#define SC_INTSTS_TMR1IF_Msk             (0x1ul << SC_INTSTS_TMR1IF_Pos)                   /*!< SC_T::INTSTS: TMR1IF Mask              */

#define SC_INTSTS_TMR2IF_Pos             (5)                                               /*!< SC_T::INTSTS: TMR2IF Position          */
#define SC_INTSTS_TMR2IF_Msk             (0x1ul << SC_INTSTS_TMR2IF_Pos)                   /*!< SC_T::INTSTS: TMR2IF Mask              */

#define SC_INTSTS_BGTIF_Pos              (6)                                               /*!< SC_T::INTSTS: BGTIF Position           */
#define SC_INTSTS_BGTIF_Msk              (0x1ul << SC_INTSTS_BGTIF_Pos)                    /*!< SC_T::INTSTS: BGTIF Mask               */

#define SC_INTSTS_CDIF_Pos               (7)                                               /*!< SC_T::INTSTS: CDIF Position            */
#define SC_INTSTS_CDIF_Msk               (0x1ul << SC_INTSTS_CDIF_Pos)                     /*!< SC_T::INTSTS: CDIF Mask                */

#define SC_INTSTS_INITIF_Pos             (8)                                               /*!< SC_T::INTSTS: INITIF Position          */
#define SC_INTSTS_INITIF_Msk             (0x1ul << SC_INTSTS_INITIF_Pos)                   /*!< SC_T::INTSTS: INITIF Mask              */

#define SC_INTSTS_RXTOIF_Pos             (9)                                               /*!< SC_T::INTSTS: RXTOIF Position          */
#define SC_INTSTS_RXTOIF_Msk             (0x1ul << SC_INTSTS_RXTOIF_Pos)                   /*!< SC_T::INTSTS: RXTOIF Mask              */

#define SC_INTSTS_ACERRIF_Pos            (10)                                              /*!< SC_T::INTSTS: ACERRIF Position         */
#define SC_INTSTS_ACERRIF_Msk            (0x1ul << SC_INTSTS_ACERRIF_Pos)                  /*!< SC_T::INTSTS: ACERRIF Mask             */

#define SC_STATUS_RXOV_Pos               (0)                                               /*!< SC_T::STATUS: RXOV Position            */
#define SC_STATUS_RXOV_Msk               (0x1ul << SC_STATUS_RXOV_Pos)                     /*!< SC_T::STATUS: RXOV Mask                */

#define SC_STATUS_RXEMPTY_Pos            (1)                                               /*!< SC_T::STATUS: RXEMPTY Position         */
#define SC_STATUS_RXEMPTY_Msk            (0x1ul << SC_STATUS_RXEMPTY_Pos)                  /*!< SC_T::STATUS: RXEMPTY Mask             */

#define SC_STATUS_RXFULL_Pos             (2)                                               /*!< SC_T::STATUS: RXFULL Position          */
#define SC_STATUS_RXFULL_Msk             (0x1ul << SC_STATUS_RXFULL_Pos)                   /*!< SC_T::STATUS: RXFULL Mask              */

#define SC_STATUS_PEF_Pos                (4)                                               /*!< SC_T::STATUS: PEF Position             */
#define SC_STATUS_PEF_Msk                (0x1ul << SC_STATUS_PEF_Pos)                      /*!< SC_T::STATUS: PEF Mask                 */

#define SC_STATUS_FEF_Pos                (5)                                               /*!< SC_T::STATUS: FEF Position             */
#define SC_STATUS_FEF_Msk                (0x1ul << SC_STATUS_FEF_Pos)                      /*!< SC_T::STATUS: FEF Mask                 */

#define SC_STATUS_BEF_Pos                (6)                                               /*!< SC_T::STATUS: BEF Position             */
#define SC_STATUS_BEF_Msk                (0x1ul << SC_STATUS_BEF_Pos)                      /*!< SC_T::STATUS: BEF Mask                 */

#define SC_STATUS_TXOV_Pos               (8)                                               /*!< SC_T::STATUS: TXOV Position            */
#define SC_STATUS_TXOV_Msk               (0x1ul << SC_STATUS_TXOV_Pos)                     /*!< SC_T::STATUS: TXOV Mask                */

#define SC_STATUS_TXEMPTY_Pos            (9)                                               /*!< SC_T::STATUS: TXEMPTY Position         */
#define SC_STATUS_TXEMPTY_Msk            (0x1ul << SC_STATUS_TXEMPTY_Pos)                  /*!< SC_T::STATUS: TXEMPTY Mask             */

#define SC_STATUS_TXFULL_Pos             (10)                                              /*!< SC_T::STATUS: TXFULL Position          */
#define SC_STATUS_TXFULL_Msk             (0x1ul << SC_STATUS_TXFULL_Pos)                   /*!< SC_T::STATUS: TXFULL Mask              */

#define SC_STATUS_CREMOVE_Pos            (11)                                              /*!< SC_T::STATUS: CREMOVE Position         */
#define SC_STATUS_CREMOVE_Msk            (0x1ul << SC_STATUS_CREMOVE_Pos)                  /*!< SC_T::STATUS: CREMOVE Mask             */

#define SC_STATUS_CINSERT_Pos            (12)                                              /*!< SC_T::STATUS: CINSERT Position         */
#define SC_STATUS_CINSERT_Msk            (0x1ul << SC_STATUS_CINSERT_Pos)                  /*!< SC_T::STATUS: CINSERT Mask             */

#define SC_STATUS_CDPINSTS_Pos           (13)                                              /*!< SC_T::STATUS: CDPINSTS Position        */
#define SC_STATUS_CDPINSTS_Msk           (0x1ul << SC_STATUS_CDPINSTS_Pos)                 /*!< SC_T::STATUS: CDPINSTS Mask            */

#define SC_STATUS_RXPOINT_Pos            (16)                                              /*!< SC_T::STATUS: RXPOINT Position         */
#define SC_STATUS_RXPOINT_Msk            (0x7ul << SC_STATUS_RXPOINT_Pos)                  /*!< SC_T::STATUS: RXPOINT Mask             */

#define SC_STATUS_RXRERR_Pos             (21)                                              /*!< SC_T::STATUS: RXRERR Position          */
#define SC_STATUS_RXRERR_Msk             (0x1ul << SC_STATUS_RXRERR_Pos)                   /*!< SC_T::STATUS: RXRERR Mask              */

#define SC_STATUS_RXOVERR_Pos            (22)                                              /*!< SC_T::STATUS: RXOVERR Position         */
#define SC_STATUS_RXOVERR_Msk            (0x1ul << SC_STATUS_RXOVERR_Pos)                  /*!< SC_T::STATUS: RXOVERR Mask             */

#define SC_STATUS_RXACT_Pos              (23)                                              /*!< SC_T::STATUS: RXACT Position           */
#define SC_STATUS_RXACT_Msk              (0x1ul << SC_STATUS_RXACT_Pos)                    /*!< SC_T::STATUS: RXACT Mask               */

#define SC_STATUS_TXPOINT_Pos            (24)                                              /*!< SC_T::STATUS: TXPOINT Position         */
#define SC_STATUS_TXPOINT_Msk            (0x7ul << SC_STATUS_TXPOINT_Pos)                  /*!< SC_T::STATUS: TXPOINT Mask             */

#define SC_STATUS_TXRERR_Pos             (29)                                              /*!< SC_T::STATUS: TXRERR Position          */
#define SC_STATUS_TXRERR_Msk             (0x1ul << SC_STATUS_TXRERR_Pos)                   /*!< SC_T::STATUS: TXRERR Mask              */

#define SC_STATUS_TXOVERR_Pos            (30)                                              /*!< SC_T::STATUS: TXOVERR Position         */
#define SC_STATUS_TXOVERR_Msk            (0x1ul << SC_STATUS_TXOVERR_Pos)                  /*!< SC_T::STATUS: TXOVERR Mask             */

#define SC_STATUS_TXACT_Pos              (31)                                              /*!< SC_T::STATUS: TXACT Position           */
#define SC_STATUS_TXACT_Msk              (0x1ul << SC_STATUS_TXACT_Pos)                    /*!< SC_T::STATUS: TXACT Mask               */

#define SC_PINCTL_PWREN_Pos              (0)                                               /*!< SC_T::PINCTL: PWREN Position           */
#define SC_PINCTL_PWREN_Msk              (0x1ul << SC_PINCTL_PWREN_Pos)                    /*!< SC_T::PINCTL: PWREN Mask               */

#define SC_PINCTL_RSTEN_Pos              (1)                                               /*!< SC_T::PINCTL: RSTEN Position           */
#define SC_PINCTL_RSTEN_Msk              (0x1ul << SC_PINCTL_RSTEN_Pos)                    /*!< SC_T::PINCTL: RSTEN Mask               */

#define SC_PINCTL_CLKKEEP_Pos            (6)                                               /*!< SC_T::PINCTL: CLKKEEP Position         */
#define SC_PINCTL_CLKKEEP_Msk            (0x1ul << SC_PINCTL_CLKKEEP_Pos)                  /*!< SC_T::PINCTL: CLKKEEP Mask             */

#define SC_PINCTL_SCDATA_Pos             (9)                                               /*!< SC_T::PINCTL: SCDATA Position          */
#define SC_PINCTL_SCDATA_Msk             (0x1ul << SC_PINCTL_SCDATA_Pos)                   /*!< SC_T::PINCTL: SCDATA Mask              */

#define SC_PINCTL_PWRINV_Pos             (11)                                              /*!< SC_T::PINCTL: PWRINV Position          */
#define SC_PINCTL_PWRINV_Msk             (0x1ul << SC_PINCTL_PWRINV_Pos)                   /*!< SC_T::PINCTL: PWRINV Mask              */

#define SC_PINCTL_DATASTS_Pos            (16)                                              /*!< SC_T::PINCTL: DATASTS Position         */
#define SC_PINCTL_DATASTS_Msk            (0x1ul << SC_PINCTL_DATASTS_Pos)                  /*!< SC_T::PINCTL: DATASTS Mask             */

#define SC_PINCTL_PWRSTS_Pos             (17)                                              /*!< SC_T::PINCTL: PWRSTS Position          */
#define SC_PINCTL_PWRSTS_Msk             (0x1ul << SC_PINCTL_PWRSTS_Pos)                   /*!< SC_T::PINCTL: PWRSTS Mask              */

#define SC_PINCTL_RSTSTS_Pos             (18)                                              /*!< SC_T::PINCTL: RSTSTS Position          */
#define SC_PINCTL_RSTSTS_Msk             (0x1ul << SC_PINCTL_RSTSTS_Pos)                   /*!< SC_T::PINCTL: RSTSTS Mask              */

#define SC_PINCTL_SYNC_Pos               (30)                                              /*!< SC_T::PINCTL: SYNC Position            */
#define SC_PINCTL_SYNC_Msk               (0x1ul << SC_PINCTL_SYNC_Pos)                     /*!< SC_T::PINCTL: SYNC Mask                */

#define SC_TMRCTL0_CNT_Pos               (0)                                               /*!< SC_T::TMRCTL0: CNT Position            */
#define SC_TMRCTL0_CNT_Msk               (0xfffffful << SC_TMRCTL0_CNT_Pos)                /*!< SC_T::TMRCTL0: CNT Mask                */

#define SC_TMRCTL0_OPMODE_Pos            (24)                                              /*!< SC_T::TMRCTL0: OPMODE Position         */
#define SC_TMRCTL0_OPMODE_Msk            (0xful << SC_TMRCTL0_OPMODE_Pos)                  /*!< SC_T::TMRCTL0: OPMODE Mask             */

#define SC_TMRCTL0_SYNC_Pos              (31)                                              /*!< SC_T::TMRCTL0: SYNC Position           */
#define SC_TMRCTL0_SYNC_Msk              (0x1ul << SC_TMRCTL0_SYNC_Pos)                    /*!< SC_T::TMRCTL0: SYNC Mask               */

#define SC_TMRCTL1_CNT_Pos               (0)                                               /*!< SC_T::TMRCTL1: CNT Position            */
#define SC_TMRCTL1_CNT_Msk               (0xfful << SC_TMRCTL1_CNT_Pos)                    /*!< SC_T::TMRCTL1: CNT Mask                */

#define SC_TMRCTL1_OPMODE_Pos            (24)                                              /*!< SC_T::TMRCTL1: OPMODE Position         */
#define SC_TMRCTL1_OPMODE_Msk            (0xful << SC_TMRCTL1_OPMODE_Pos)                  /*!< SC_T::TMRCTL1: OPMODE Mask             */

#define SC_TMRCTL1_SYNC_Pos              (31)                                              /*!< SC_T::TMRCTL1: SYNC Position           */
#define SC_TMRCTL1_SYNC_Msk              (0x1ul << SC_TMRCTL1_SYNC_Pos)                    /*!< SC_T::TMRCTL1: SYNC Mask               */

#define SC_TMRCTL2_CNT_Pos               (0)                                               /*!< SC_T::TMRCTL2: CNT Position            */
#define SC_TMRCTL2_CNT_Msk               (0xfful << SC_TMRCTL2_CNT_Pos)                    /*!< SC_T::TMRCTL2: CNT Mask                */

#define SC_TMRCTL2_OPMODE_Pos            (24)                                              /*!< SC_T::TMRCTL2: OPMODE Position         */
#define SC_TMRCTL2_OPMODE_Msk            (0xful << SC_TMRCTL2_OPMODE_Pos)                  /*!< SC_T::TMRCTL2: OPMODE Mask             */

#define SC_TMRCTL2_SYNC_Pos              (31)                                              /*!< SC_T::TMRCTL2: SYNC Position           */
#define SC_TMRCTL2_SYNC_Msk              (0x1ul << SC_TMRCTL2_SYNC_Pos)                    /*!< SC_T::TMRCTL2: SYNC Mask               */

#define SC_UARTCTL_UARTEN_Pos            (0)                                               /*!< SC_T::UARTCTL: UARTEN Position         */
#define SC_UARTCTL_UARTEN_Msk            (0x1ul << SC_UARTCTL_UARTEN_Pos)                  /*!< SC_T::UARTCTL: UARTEN Mask             */

#define SC_UARTCTL_WLS_Pos               (4)                                               /*!< SC_T::UARTCTL: WLS Position            */
#define SC_UARTCTL_WLS_Msk               (0x3ul << SC_UARTCTL_WLS_Pos)                     /*!< SC_T::UARTCTL: WLS Mask                */

#define SC_UARTCTL_PBOFF_Pos             (6)                                               /*!< SC_T::UARTCTL: PBOFF Position          */
#define SC_UARTCTL_PBOFF_Msk             (0x1ul << SC_UARTCTL_PBOFF_Pos)                   /*!< SC_T::UARTCTL: PBOFF Mask              */

#define SC_UARTCTL_OPE_Pos               (7)                                               /*!< SC_T::UARTCTL: OPE Position            */
#define SC_UARTCTL_OPE_Msk               (0x1ul << SC_UARTCTL_OPE_Pos)                     /*!< SC_T::UARTCTL: OPE Mask                */

#define SC_ACTCTL_T1EXT_Pos              (0)                                               /*!< SC_T::ACTCTL: T1EXT Position           */
#define SC_ACTCTL_T1EXT_Msk              (0x1ful << SC_ACTCTL_T1EXT_Pos)                   /*!< SC_T::ACTCTL: T1EXT Mask               */

/**@}*/ /* SC_CONST */
/**@}*/ /* end of SC register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __SC_REG_H__ */
