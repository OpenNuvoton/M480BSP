/**************************************************************************//**
 * @file     uart_reg.h
 * @version  V1.00
 * @brief    UART register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __UART_REG_H__
#define __UART_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup UART Universal Asynchronous Receiver/Transmitter Controller(UART)
    Memory Mapped Structure for UART Controller
@{ */

typedef struct
{


    /**
@var UART_T::DAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DAT
</font><br><p> <font size="2">
Offset: 0x00  UART Receive/Transmit Buffer Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>DAT</td><td><div style="word-wrap: break-word;"><b>Data Receive/Transmit Buffer
</b><br>
Write Operation:
<br>
By writing one byte to this register, the data byte will be stored in transmitter FIFO
<br>
The UART controller will send out the data stored in transmitter FIFO top location through the UART_TXD.
<br>
Read Operation:
<br>
By reading this register, the UART controller will return an 8-bit data received from receiver FIFO.
<br>
</div></td></tr><tr><td>
[8]</td><td>PARITY</td><td><div style="word-wrap: break-word;"><b>Parity Bit Receive/Transmit Buffer
</b><br>
Write Operation:
<br>
By writing to this bit, the parity bit will be stored in transmitter FIFO
<br>
If PBE (UART_LINE[3]) and PSS (UART_LINE[7]) are set,
<br>
the UART controller will send out this bit follow the DAT (UART_DAT[7:0]) through the UART_TXD.
<br>
Read Operation:
<br>
If PBE (UART_LINE[3]) and PSS (UART_LINE[7]) are enabled, the parity bit can be read by this bit.
<br>
Note: This bit has effect only when PBE (UART_LINE[3]) and PSS (UART_LINE[7]) are set.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UART_T::INTEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTEN
</font><br><p> <font size="2">
Offset: 0x04  UART Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>RDAIEN</td><td><div style="word-wrap: break-word;"><b>Receive Data Available Interrupt Enable Bit
</b><br>
0 = Receive data available interrupt Disabled.
<br>
1 = Receive data available interrupt Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>THREIEN</td><td><div style="word-wrap: break-word;"><b>Transmit Holding Register Empty Interrupt Enable Bit
</b><br>
0 = Transmit holding register empty interrupt Disabled.
<br>
1 = Transmit holding register empty interrupt Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>RLSIEN</td><td><div style="word-wrap: break-word;"><b>Receive Line Status Interrupt Enable Bit
</b><br>
0 = Receive Line Status interrupt Disabled.
<br>
1 = Receive Line Status interrupt Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>MODEMIEN</td><td><div style="word-wrap: break-word;"><b>Modem Status Interrupt Enable Bit
</b><br>
0 = Modem status interrupt Disabled.
<br>
1 = Modem status interrupt Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>RXTOIEN</td><td><div style="word-wrap: break-word;"><b>RX Time-out Interrupt Enable Bit
</b><br>
0 = RX time-out interrupt Disabled.
<br>
1 = RX time-out interrupt Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>BUFERRIEN</td><td><div style="word-wrap: break-word;"><b>Buffer Error Interrupt Enable Bit
</b><br>
0 = Buffer error interrupt Disabled.
<br>
1 = Buffer error interrupt Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>WKIEN</td><td><div style="word-wrap: break-word;"><b>Wake-up Interrupt Enable Bit
</b><br>
0 = Wake-up Interrupt Disabled.
<br>
1 = Wake-up Interrupt Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>LINIEN</td><td><div style="word-wrap: break-word;"><b>LIN Bus Interrupt Enable Bit
</b><br>
0 = LIN bus interrupt Disabled.
<br>
1 = LIN bus interrupt Enabled.
<br>
Note: This bit is used for LIN function mode.
<br>
</div></td></tr><tr><td>
[11]</td><td>TOCNTEN</td><td><div style="word-wrap: break-word;"><b>Receive Buffer Time-out Counter Enable Bit
</b><br>
0 = Receive Buffer Time-out counter Disabled.
<br>
1 = Receive Buffer Time-out counter Enabled.
<br>
</div></td></tr><tr><td>
[12]</td><td>ATORTSEN</td><td><div style="word-wrap: break-word;"><b>nRTS Auto-flow Control Enable Bit
</b><br>
0 = nRTS auto-flow control Disabled.
<br>
1 = nRTS auto-flow control Enabled.
<br>
Note: When nRTS auto-flow is enabled, if the number of bytes in the RX FIFO equals the RTSTRGLV (UART_FIFO[19:16]), the UART will de-assert nRTS signal.
<br>
</div></td></tr><tr><td>
[13]</td><td>ATOCTSEN</td><td><div style="word-wrap: break-word;"><b>nCTS Auto-flow Control Enable Bit
</b><br>
0 = nCTS auto-flow control Disabled.
<br>
1 = nCTS auto-flow control Enabled.
<br>
Note: When nCTS auto-flow is enabled, the UART will send data to external device if nCTS input assert (UART will not send data to device until nCTS is asserted).
<br>
</div></td></tr><tr><td>
[14]</td><td>TXPDMAEN</td><td><div style="word-wrap: break-word;"><b>TX PDMA Enable Bit
</b><br>
This bit can enable or disable TX PDMA service.
<br>
0 = TX PDMA Disabled.
<br>
1 = TX PDMA Enabled.
<br>
Note: If RLSIEN (UART_INTEN[2]) is enabled and HWRLSINT (UART_INTSTS[26]) is set to 1, the RLS (Receive Line Status) Interrupt is caused
<br>
If RLS interrupt is caused by Break Error Flag BIF(UART_FIFOSTS[6]), Frame Error Flag FEF(UART_FIFO[5]) or Parity Error Flag PEF(UART_FIFOSTS[4]) , UART PDMA transmit request operation is stop
<br>
Clear Break Error Flag BIF or Frame Error Flag FEF or Parity Error Flag PEF by writing '1' to corresponding BIF, FEF and PEF to make UART PDMA transmit request operation continue.
<br>
</div></td></tr><tr><td>
[15]</td><td>RXPDMAEN</td><td><div style="word-wrap: break-word;"><b>RX PDMA Enable Bit
</b><br>
This bit can enable or disable RX PDMA service.
<br>
0 = RX PDMA Disabled.
<br>
1 = RX PDMA Enabled.
<br>
Note: If RLSIEN (UART_INTEN[2]) is enabled and HWRLSINT (UART_INTSTS[26]) is set to 1, the RLS (Receive Line Status) Interrupt is caused
<br>
If RLS interrupt is caused by Break Error Flag BIF(UART_FIFOSTS[6]), Frame Error Flag FEF(UART_FIFO[5]) or Parity Error Flag PEF(UART_FIFOSTS[4]) , UART PDMA receive request operation is stop
<br>
Clear Break Error Flag BIF or Frame Error Flag FEF or Parity Error Flag PEF by writing '1' to corresponding BIF, FEF and PEF to make UART PDMA receive request operation continue.
<br>
</div></td></tr><tr><td>
[18]</td><td>ABRIEN</td><td><div style="word-wrap: break-word;"><b>Auto-baud Rate Interrupt Enable Bit
</b><br>
0 = Auto-baud rate interrupt Disabled.
<br>
1 = Auto-baud rate interrupt Enabled.
<br>
</div></td></tr><tr><td>
[22]</td><td>TXENDIEN</td><td><div style="word-wrap: break-word;"><b>Transmitter Empty Interrupt Enable Bit
</b><br>
If TXENDIEN (UART_INTEN[22]) is enabled, the Transmitter Empty interrupt TXENDINT (UART_INTSTS[30]) will be generated when TXENDIF (UART_INTSTS[22]) is set (TX FIFO (UART_DAT) is empty and the STOP bit of the last byte has been transmitted).
<br>
0 = Transmitter empty interrupt Disabled.
<br>
1 = Transmitter empty interrupt Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UART_T::FIFO

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">FIFO
</font><br><p> <font size="2">
Offset: 0x08  UART FIFO Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1]</td><td>RXRST</td><td><div style="word-wrap: break-word;"><b>RX Field Software Reset
</b><br>
When RXRST (UART_FIFO[1]) is set, all the byte in the receiver FIFO and RX internal state machine are cleared.
<br>
0 = No effect.
<br>
1 = Reset the RX internal state machine and pointers.
<br>
Note1: This bit will automatically clear at least 3 UART peripheral clock cycles.
<br>
Note2: Before setting this bit, it should wait for the RXIDLE (UART_FIFOSTS[29]) be set.
<br>
</div></td></tr><tr><td>
[2]</td><td>TXRST</td><td><div style="word-wrap: break-word;"><b>TX Field Software Reset
</b><br>
When TXRST (UART_FIFO[2]) is set, all the byte in the transmit FIFO and TX internal state machine are cleared.
<br>
0 = No effect.
<br>
1 = Reset the TX internal state machine and pointers.
<br>
Note1: This bit will automatically clear at least 3 UART peripheral clock cycles.
<br>
Note2: Before setting this bit, it should wait for the TXEMPTYF (UART_FIFOSTS[28]) be set.
<br>
</div></td></tr><tr><td>
[7:4]</td><td>RFITL</td><td><div style="word-wrap: break-word;"><b>RX FIFO Interrupt Trigger Level
</b><br>
When the number of bytes in the receive FIFO equals the RFITL, the RDAIF (UART_INTSTS[0]) will be set (if RDAIEN (UART_INTEN [0]) enabled, and an interrupt will be generated).
<br>
0000 = RX FIFO Interrupt Trigger Level is 1 byte.
<br>
0001 = RX FIFO Interrupt Trigger Level is 4 bytes.
<br>
0010 = RX FIFO Interrupt Trigger Level is 8 bytes.
<br>
0011 = RX FIFO Interrupt Trigger Level is 14 bytes.
<br>
Others = Reserved.
<br>
</div></td></tr><tr><td>
[8]</td><td>RXOFF</td><td><div style="word-wrap: break-word;"><b>Receiver Disable Bit
</b><br>
The receiver is disabled or not (set 1 to disable receiver).
<br>
0 = Receiver Enabled.
<br>
1 = Receiver Disabled.
<br>
Note: This bit is used for RS-485 Normal Multi-drop mode
<br>
It should be programmed before RS485NMM (UART_ALTCTL [8]) is programmed.
<br>
</div></td></tr><tr><td>
[19:16]</td><td>RTSTRGLV</td><td><div style="word-wrap: break-word;"><b>nRTS Trigger Level for Auto-flow Control Use
</b><br>
0000 = nRTS Trigger Level is 1 byte.
<br>
0001 = nRTS Trigger Level is 4 bytes.
<br>
0010 = nRTS Trigger Level is 8 bytes.
<br>
0011 = nRTS Trigger Level is 14 bytes.
<br>
Others = Reserved.
<br>
Note: This field is used for auto nRTS flow control.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UART_T::LINE

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">LINE
</font><br><p> <font size="2">
Offset: 0x0C  UART Line Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1:0]</td><td>WLS</td><td><div style="word-wrap: break-word;"><b>Word Length Selection
</b><br>
This field sets UART word length.
<br>
00 = 5 bits.
<br>
01 = 6 bits.
<br>
10 = 7 bits.
<br>
11 = 8 bits.
<br>
</div></td></tr><tr><td>
[2]</td><td>NSB</td><td><div style="word-wrap: break-word;"><b>Number of 'STOP Bit'
</b><br>
0 = One 'STOP bit' is generated in the transmitted data.
<br>
1 = When select 5-bit word length, 1.5 'STOP bit' is generated in the transmitted data
<br>
When select 6-, 7- and 8-bit word length, 2 'STOP bit' is generated in the transmitted data.
<br>
</div></td></tr><tr><td>
[3]</td><td>PBE</td><td><div style="word-wrap: break-word;"><b>Parity Bit Enable Bit
</b><br>
0 = Parity bit generated Disabled.
<br>
1 = Parity bit generated Enabled.
<br>
Note: Parity bit is generated on each outgoing character and is checked on each incoming data.
<br>
</div></td></tr><tr><td>
[4]</td><td>EPE</td><td><div style="word-wrap: break-word;"><b>Even Parity Enable Bit
</b><br>
0 = Odd number of logic '1's is transmitted and checked in each word.
<br>
1 = Even number of logic '1's is transmitted and checked in each word.
<br>
Note: This bit has effect only when PBE (UART_LINE[3]) is set.
<br>
</div></td></tr><tr><td>
[5]</td><td>SPE</td><td><div style="word-wrap: break-word;"><b>Stick Parity Enable Bit
</b><br>
0 = Stick parity Disabled.
<br>
1 = Stick parity Enabled.
<br>
Note: If PBE (UART_LINE[3]) and EPE (UART_LINE[4]) are logic 1, the parity bit is transmitted and checked as logic 0
<br>
If PBE (UART_LINE[3]) is 1 and EPE (UART_LINE[4]) is 0 then the parity bit is transmitted and checked as 1.
<br>
</div></td></tr><tr><td>
[6]</td><td>BCB</td><td><div style="word-wrap: break-word;"><b>Break Control Bit
</b><br>
0 = Break Control Disabled.
<br>
1 = Break Control Enabled.
<br>
Note: When this bit is set to logic 1, the transmitted serial data output (TX) is forced to the Spacing State (logic 0)
<br>
This bit acts only on TX line and has no effect on the transmitter logic.
<br>
</div></td></tr><tr><td>
[7]</td><td>PSS</td><td><div style="word-wrap: break-word;"><b>Parity Bit Source Selection
</b><br>
The parity bit can be selected to be generated and checked automatically or by software.
<br>
0 = Parity bit is generated by EPE (UART_LINE[4]) and SPE (UART_LINE[5]) setting and checked automatically.
<br>
1 = Parity bit generated and checked by software.
<br>
Note1: This bit has effect only when PBE (UART_LINE[3]) is set.
<br>
Note2: If PSS is 0, the parity bit is transmitted and checked automatically
<br>
If PSS is 1, the transmitted parity bit value can be determined by writing PARITY (UART_DAT[8]) and the parity bit can be read by reading PARITY (UART_DAT[8]).
<br>
</div></td></tr><tr><td>
[8]</td><td>TXDINV</td><td><div style="word-wrap: break-word;"><b>TX Data Inverted
</b><br>
0 = Transmitted data signal inverted Disabled.
<br>
1 = Transmitted data signal inverted Enabled.
<br>
Note1: Before setting this bit, TXRXDIS (UART_FUNCSEL[3]) should be set then waited for TXRXACT (UART_FIFOSTS[31]) is cleared
<br>
When the configuration is done, cleared TXRXDIS (UART_FUNCSEL[3]) to activate UART controller.
<br>
Note2: This bit is valid when FUNCSEL (UART_FUNCSEL[1:0]) is select UART, LIN or RS485 function.
<br>
</div></td></tr><tr><td>
[9]</td><td>RXDINV</td><td><div style="word-wrap: break-word;"><b>RX Data Inverted
</b><br>
0 = Received data signal inverted Disabled.
<br>
1 = Received data signal inverted Enabled.
<br>
Note1: Before setting this bit, TXRXDIS (UART_FUNCSEL[3]) should be set then waited for TXRXACT (UART_FIFOSTS[31]) is cleared
<br>
When the configuration is done, cleared TXRXDIS (UART_FUNCSEL[3]) to activate UART controller.
<br>
Note2: This bit is valid when FUNCSEL (UART_FUNCSEL[1:0]) is select UART, LIN or RS485 function.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UART_T::MODEM

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MODEM
</font><br><p> <font size="2">
Offset: 0x10  UART Modem Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1]</td><td>RTS</td><td><div style="word-wrap: break-word;"><b>nRTS (Request-to-send) Signal Control
</b><br>
This bit is direct control internal nRTS signal active or not, and then drive the nRTS pin output with RTSACTLV bit configuration.
<br>
0 = nRTS signal is active.
<br>
1 = nRTS signal is inactive.
<br>
Note1: This nRTS signal control bit is not effective when nRTS auto-flow control is enabled in UART function mode.
<br>
Note2: This nRTS signal control bit is not effective when RS-485 auto direction mode (AUD) is enabled in RS-485 function mode.
<br>
</div></td></tr><tr><td>
[9]</td><td>RTSACTLV</td><td><div style="word-wrap: break-word;"><b>nRTS Pin Active Level
</b><br>
This bit defines the active level state of nRTS pin output.
<br>
0 = nRTS pin output is high level active.
<br>
1 = nRTS pin output is low level active. (Default)
<br>
Note1: Before setting this bit, TXRXDIS (UART_FUNCSEL[3]) should be set then waited for TXRXACT (UART_FIFOSTS[31]) is cleared
<br>
When the configuration is done, cleared TXRXDIS (UART_FUNCSEL[3]) to activate UART controller.
<br>
</div></td></tr><tr><td>
[13]</td><td>RTSSTS</td><td><div style="word-wrap: break-word;"><b>nRTS Pin Status (Read Only)
</b><br>
This bit mirror from nRTS pin output of voltage logic status.
<br>
0 = nRTS pin output is low level voltage logic state.
<br>
1 = nRTS pin output is high level voltage logic state.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UART_T::MODEMSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MODEMSTS
</font><br><p> <font size="2">
Offset: 0x14  UART Modem Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CTSDETF</td><td><div style="word-wrap: break-word;"><b>Detect nCTS State Change Flag
</b><br>
This bit is set whenever nCTS input has change state, and it will generate Modem interrupt to CPU when MODEMIEN (UART_INTEN [3]) is set to 1.
<br>
0 = nCTS input has not change state.
<br>
1 = nCTS input has change state.
<br>
Note: This bit can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[4]</td><td>CTSSTS</td><td><div style="word-wrap: break-word;"><b>nCTS Pin Status (Read Only)
</b><br>
This bit mirror from nCTS pin input of voltage logic status.
<br>
0 = nCTS pin input is low level voltage logic state.
<br>
1 = nCTS pin input is high level voltage logic state.
<br>
Note: This bit echoes when UART controller peripheral clock is enabled, and nCTS multi-function port is selected.
<br>
</div></td></tr><tr><td>
[8]</td><td>CTSACTLV</td><td><div style="word-wrap: break-word;"><b>nCTS Pin Active Level
</b><br>
This bit defines the active level state of nCTS pin input.
<br>
0 = nCTS pin input is high level active.
<br>
1 = nCTS pin input is low level active. (Default)
<br>
Note: Before setting this bit, TXRXDIS (UART_FUNCSEL[3]) should be set then waited for TXRXACT (UART_FIFOSTS[31]) is cleared
<br>
When the configuration is done, cleared TXRXDIS (UART_FUNCSEL[3]) to activate UART controller.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UART_T::FIFOSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">FIFOSTS
</font><br><p> <font size="2">
Offset: 0x18  UART FIFO Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>RXOVIF</td><td><div style="word-wrap: break-word;"><b>RX Overflow Error Interrupt Flag
</b><br>
This bit is set when RX FIFO overflow.
<br>
If the number of bytes of received data is greater than RX_FIFO (UART_DAT) size 16 bytes, this bit will be set.
<br>
0 = RX FIFO is not overflow.
<br>
1 = RX FIFO is overflow.
<br>
Note: This bit can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[1]</td><td>ABRDIF</td><td><div style="word-wrap: break-word;"><b>Auto-baud Rate Detect Interrupt Flag
</b><br>
This bit is set to logic '1' when auto-baud rate detect function is finished.
<br>
0 = Auto-baud rate detect function is not finished.
<br>
1 = Auto-baud rate detect function is finished.
<br>
Note: This bit can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[2]</td><td>ABRDTOIF</td><td><div style="word-wrap: break-word;"><b>Auto-baud Rate Detect Time-out Interrupt Flag
</b><br>
This bit is set to logic '1' in Auto-baud Rate Detect mode when the baud rate counter is overflow.
<br>
0 = Auto-baud rate counter is underflow.
<br>
1 = Auto-baud rate counter is overflow.
<br>
Note: This bit can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[3]</td><td>ADDRDETF</td><td><div style="word-wrap: break-word;"><b>RS-485 Address Byte Detect Flag
</b><br>
0 = Receiver detects a data that is not an address bit (bit 9 ='0').
<br>
1 = Receiver detects a data that is an address bit (bit 9 ='1').
<br>
Note1: This field is used for RS-485 function mode and ADDRDEN (UART_ALTCTL[15]) is set to 1 to enable Address detection mode.
<br>
Note2: This bit can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[4]</td><td>PEF</td><td><div style="word-wrap: break-word;"><b>Parity Error Flag
</b><br>
This bit is set to logic 1 whenever the received character does not have a valid 'parity bit'.
<br>
0 = No parity error is generated.
<br>
1 = Parity error is generated.
<br>
Note: This bit can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[5]</td><td>FEF</td><td><div style="word-wrap: break-word;"><b>Framing Error Flag
</b><br>
This bit is set to logic 1 whenever the received character does not have a valid 'stop bit'
<br>
(that is, the stop bit following the last data bit or parity bit is detected as logic 0).
<br>
0 = No framing error is generated.
<br>
1 = Framing error is generated.
<br>
Note: This bit can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[6]</td><td>BIF</td><td><div style="word-wrap: break-word;"><b>Break Interrupt Flag
</b><br>
This bit is set to logic 1 whenever the received data input (RX) is held in the 'spacing state' (logic 0)
<br>
for longer than a full word transmission time (that is, the total time of start bit + data bits + parity + stop bits).
<br>
0 = No Break interrupt is generated.
<br>
1 = Break interrupt is generated.
<br>
Note: This bit can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[13:8]</td><td>RXPTR</td><td><div style="word-wrap: break-word;"><b>RX FIFO Pointer (Read Only)
</b><br>
This field indicates the RX FIFO Buffer Pointer
<br>
When UART receives one byte from external device, RXPTR increases one
<br>
When one byte of RX FIFO is read by CPU, RXPTR decreases one.
<br>
The Maximum value shown in RXPTR is 15
<br>
When the using level of RX FIFO Buffer equal to 16, the RXFULL bit is set to 1 and RXPTR will show 0
<br>
As one byte of RX FIFO is read by CPU, the RXFULL bit is cleared to 0 and RXPTR will show 15
<br>
</div></td></tr><tr><td>
[14]</td><td>RXEMPTY</td><td><div style="word-wrap: break-word;"><b>Receiver FIFO Empty (Read Only)
</b><br>
This bit initiate RX FIFO empty or not.
<br>
0 = RX FIFO is not empty.
<br>
1 = RX FIFO is empty.
<br>
Note: When the last byte of RX FIFO has been read by CPU, hardware sets this bit high
<br>
It will be cleared when UART receives any new data.
<br>
</div></td></tr><tr><td>
[15]</td><td>RXFULL</td><td><div style="word-wrap: break-word;"><b>Receiver FIFO Full (Read Only)
</b><br>
This bit initiates RX FIFO full or not.
<br>
0 = RX FIFO is not full.
<br>
1 = RX FIFO is full.
<br>
Note: This bit is set when the number of usage in RX FIFO Buffer is equal to 16, otherwise it is cleared by hardware.
<br>
</div></td></tr><tr><td>
[21:16]</td><td>TXPTR</td><td><div style="word-wrap: break-word;"><b>TX FIFO Pointer (Read Only)
</b><br>
This field indicates the TX FIFO Buffer Pointer
<br>
When CPU writes one byte into UART_DAT, TXPTR increases one
<br>
When one byte of TX FIFO is transferred to Transmitter Shift Register, TXPTR decreases one.
<br>
The Maximum value shown in TXPTR is 15
<br>
When the using level of TX FIFO Buffer equal to 16, the TXFULL bit is set to 1 and TXPTR will show 0
<br>
As one byte of TX FIFO is transferred to Transmitter Shift Register, the TXFULL bit is cleared to 0 and TXPTR will show 15
<br>
</div></td></tr><tr><td>
[22]</td><td>TXEMPTY</td><td><div style="word-wrap: break-word;"><b>Transmitter FIFO Empty (Read Only)
</b><br>
This bit indicates TX FIFO empty or not.
<br>
0 = TX FIFO is not empty.
<br>
1 = TX FIFO is empty.
<br>
Note: When the last byte of TX FIFO has been transferred to Transmitter Shift Register, hardware sets this bit high
<br>
It will be cleared when writing data into UART_DAT (TX FIFO not empty).
<br>
</div></td></tr><tr><td>
[23]</td><td>TXFULL</td><td><div style="word-wrap: break-word;"><b>Transmitter FIFO Full (Read Only)
</b><br>
This bit indicates TX FIFO full or not.
<br>
0 = TX FIFO is not full.
<br>
1 = TX FIFO is full.
<br>
Note: This bit is set when the number of usage in TX FIFO Buffer is equal to 16, otherwise it is cleared by hardware.
<br>
</div></td></tr><tr><td>
[24]</td><td>TXOVIF</td><td><div style="word-wrap: break-word;"><b>TX Overflow Error Interrupt Flag
</b><br>
If TX FIFO (UART_DAT) is full, an additional write to UART_DAT will cause this bit to logic 1.
<br>
0 = TX FIFO is not overflow.
<br>
1 = TX FIFO is overflow.
<br>
Note: This bit can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[28]</td><td>TXEMPTYF</td><td><div style="word-wrap: break-word;"><b>Transmitter Empty Flag (Read Only)
</b><br>
This bit is set by hardware when TX FIFO (UART_DAT) is empty and the STOP bit of the last byte has been transmitted.
<br>
0 = TX FIFO is not empty or the STOP bit of the last byte has been not transmitted.
<br>
1 = TX FIFO is empty and the STOP bit of the last byte has been transmitted.
<br>
Note: This bit is cleared automatically when TX FIFO is not empty or the last byte transmission has not completed.
<br>
</div></td></tr><tr><td>
[29]</td><td>RXIDLE</td><td><div style="word-wrap: break-word;"><b>RX Idle Status (Read Only)
</b><br>
This bit is set by hardware when RX is idle.
<br>
0 = RX is busy.
<br>
1 = RX is idle. (Default)
<br>
</div></td></tr><tr><td>
[31]</td><td>TXRXACT</td><td><div style="word-wrap: break-word;"><b>TX and RX Active Status (Read Only)
</b><br>
This bit indicates TX and RX are active or inactive.
<br>
0 = TX and RX are inactive.
<br>
1 = TX and RX are active. (Default)
<br>
Note: When TXRXDIS (UART_FUNCSEL[3]) is set and both TX and RX are in idle state, this bit is cleared
<br>
The UART controller can not transmit or receive data at this moment
<br>
Otherwise this bit is set.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UART_T::INTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTSTS
</font><br><p> <font size="2">
Offset: 0x1C  UART Interrupt Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>RDAIF</td><td><div style="word-wrap: break-word;"><b>Receive Data Available Interrupt Flag
</b><br>
When the number of bytes in the RX FIFO equals the RFITL then the RDAIF(UART_INTSTS[0]) will be set
<br>
If RDAIEN (UART_INTEN [0]) is enabled, the RDA interrupt will be generated.
<br>
0 = No RDA interrupt flag is generated.
<br>
1 = RDA interrupt flag is generated.
<br>
Note: This bit is read only and it will be cleared when the number of unread bytes of RX FIFO drops below the threshold level (RFITL(UART_FIFO[7:4]).
<br>
</div></td></tr><tr><td>
[1]</td><td>THREIF</td><td><div style="word-wrap: break-word;"><b>Transmit Holding Register Empty Interrupt Flag
</b><br>
This bit is set when the last data of TX FIFO is transferred to Transmitter Shift Register
<br>
If THREIEN (UART_INTEN[1]) is enabled, the THRE interrupt will be generated.
<br>
0 = No THRE interrupt flag is generated.
<br>
1 = THRE interrupt flag is generated.
<br>
Note: This bit is read only and it will be cleared when writing data into UART_DAT (TX FIFO not empty).
<br>
</div></td></tr><tr><td>
[2]</td><td>RLSIF</td><td><div style="word-wrap: break-word;"><b>Receive Line Interrupt Flag (Read Only)
</b><br>
This bit is set when the RX receive data have parity error, frame error or break error (at least one of 3 bits, BIF(UART_FIFOSTS[6]), FEF(UART_FIFOSTS[5]) and PEF(UART_FIFOSTS[4]), is set)
<br>
If RLSIEN (UART_INTEN [2]) is enabled, the RLS interrupt will be generated.
<br>
0 = No RLS interrupt flag is generated.
<br>
1 = RLS interrupt flag is generated.
<br>
Note1: In RS-485 function mode, this field is set include "receiver detect and received address byte character (bit9 = '1') bit"
<br>
At the same time, the bit of ADDRDETF (UART_FIFOSTS[3]) is also set.
<br>
Note2: This bit is read only and reset to 0 when all bits of BIF (UART_FIFOSTS[6]), FEF(UART_FIFOSTS[5]) and PEF(UART_FIFOSTS[4]) are cleared.
<br>
Note3: In RS-485 function mode, this bit is read only and reset to 0 when all bits of BIF (UART_FIFOSTS[6]) , FEF(UART_FIFOSTS[5]), PEF(UART_FIFOSTS[4]) and ADDRDETF (UART_FIFOSTS[3]) are cleared.
<br>
</div></td></tr><tr><td>
[3]</td><td>MODEMIF</td><td><div style="word-wrap: break-word;"><b>MODEM Interrupt Flag (Read Only)
</b><br>
This bit is set when the nCTS pin has state change (CTSDETF (UART_MODEMSTS[0]) = 1)
<br>
If MODEMIEN (UART_INTEN [3]) is enabled, the Modem interrupt will be generated.
<br>
0 = No Modem interrupt flag is generated.
<br>
1 = Modem interrupt flag is generated.
<br>
Note: This bit is read only and reset to 0 when bit CTSDETF is cleared by a write 1 on CTSDETF(UART_MODEMSTS[0]).
<br>
</div></td></tr><tr><td>
[4]</td><td>RXTOIF</td><td><div style="word-wrap: break-word;"><b>RX Time-out Interrupt Flag (Read Only)
</b><br>
This bit is set when the RX FIFO is not empty and no activities occurred in the RX FIFO and the time-out counter equal to TOIC (UART_TOUT[7:0])
<br>
If RXTOIEN (UART_INTEN [4]) is enabled, the RX time-out interrupt will be generated.
<br>
0 = No RX time-out interrupt flag is generated.
<br>
1 = RX time-out interrupt flag is generated.
<br>
Note: This bit is read only and user can read UART_DAT (RX is in active) to clear it.
<br>
</div></td></tr><tr><td>
[5]</td><td>BUFERRIF</td><td><div style="word-wrap: break-word;"><b>Buffer Error Interrupt Flag (Read Only)
</b><br>
This bit is set when the TX FIFO or RX FIFO overflows (TXOVIF (UART_FIFOSTS[24]) or RXOVIF (UART_FIFOSTS[0]) is set)
<br>
When BUFERRIF (UART_INTSTS[5]) is set, the transfer is not correct
<br>
If BUFERRIEN (UART_INTEN [5]) is enabled, the buffer error interrupt will be generated.
<br>
0 = No buffer error interrupt flag is generated.
<br>
1 = Buffer error interrupt flag is generated.
<br>
Note: This bit is cleared if both of RXOVIF(UART_FIFOSTS[0]) and TXOVIF(UART_FIFOSTS[24]) are cleared to 0 by writing 1 to RXOVIF(UART_FIFOSTS[0]) and TXOVIF(UART_FIFOSTS[24]).
<br>
</div></td></tr><tr><td>
[6]</td><td>WKIF</td><td><div style="word-wrap: break-word;"><b>UART Wake-up Interrupt Flag (Read Only)
</b><br>
This bit is set when TOUTWKF (UART_WKSTS[4]), RS485WKF (UART_WKSTS[3]), RFRTWKF (UART_WKSTS[2]), DATWKF (UART_WKSTS[1]) or CTSWKF(UART_WKSTS[0]) is set to 1.
<br>
0 = No UART wake-up interrupt flag is generated.
<br>
1 = UART wake-up interrupt flag is generated.
<br>
Note: This bit is cleared if all of TOUTWKF, RS485WKF, RFRTWKF, DATWKF and CTSWKF are cleared to 0 by writing 1 to the corresponding interrupt flag.
<br>
</div></td></tr><tr><td>
[7]</td><td>LINIF</td><td><div style="word-wrap: break-word;"><b>LIN Bus Interrupt Flag
</b><br>
This bit is set when LIN slave header detect (SLVHDETF (UART_LINSTS[0] = 1)), LIN break detect (BRKDETF(UART_LINSTS[8]=1)), bit error detect (BITEF(UART_LINSTS[9]=1)), LIN slave ID parity error (SLVIDPEF(UART_LINSTS[2] = 1)) or LIN slave header error detect (SLVHEF (UART_LINSTS[1]))
<br>
If LINIEN (UART_INTEN [8]) is enabled the LIN interrupt will be generated.
<br>
0 = None of SLVHDETF, BRKDETF, BITEF, SLVIDPEF and SLVHEF is generated.
<br>
1 = At least one of SLVHDETF, BRKDETF, BITEF, SLVIDPEF and SLVHEF is generated.
<br>
Note: This bit is cleared when SLVHDETF(UART_LINSTS[0]), BRKDETF(UART_LINSTS[8]), BITEF(UART_LINSTS[9]), SLVIDPEF (UART_LINSTS[2]) and SLVHEF(UART_LINSTS[1]) all are cleared and software writing '1' to LINIF(UART_INTSTS[7]).
<br>
</div></td></tr><tr><td>
[8]</td><td>RDAINT</td><td><div style="word-wrap: break-word;"><b>Receive Data Available Interrupt Indicator (Read Only)
</b><br>
This bit is set if RDAIEN (UART_INTEN[0]) and RDAIF (UART_INTSTS[0]) are both set to 1.
<br>
0 = No RDA interrupt is generated.
<br>
1 = RDA interrupt is generated.
<br>
</div></td></tr><tr><td>
[9]</td><td>THREINT</td><td><div style="word-wrap: break-word;"><b>Transmit Holding Register Empty Interrupt Indicator (Read Only)
</b><br>
This bit is set if THREIEN (UART_INTEN[1]) and THREIF(UART_INTSTS[1]) are both set to 1.
<br>
0 = No THRE interrupt is generated.
<br>
1 = THRE interrupt is generated.
<br>
</div></td></tr><tr><td>
[10]</td><td>RLSINT</td><td><div style="word-wrap: break-word;"><b>Receive Line Status Interrupt Indicator (Read Only)
</b><br>
This bit is set if RLSIEN (UART_INTEN[2]) and RLSIF(UART_INTSTS[2]) are both set to 1.
<br>
0 = No RLS interrupt is generated.
<br>
1 = RLS interrupt is generated.
<br>
</div></td></tr><tr><td>
[11]</td><td>MODEMINT</td><td><div style="word-wrap: break-word;"><b>MODEM Status Interrupt Indicator (Read Only)
</b><br>
This bit is set if MODEMIEN(UART_INTEN[3]) and MODEMIF(UART_INTSTS[3]) are both set to 1
<br>
0 = No Modem interrupt is generated.
<br>
1 = Modem interrupt is generated.
<br>
</div></td></tr><tr><td>
[12]</td><td>RXTOINT</td><td><div style="word-wrap: break-word;"><b>RX Time-out Interrupt Indicator (Read Only)
</b><br>
This bit is set if RXTOIEN (UART_INTEN[4]) and RXTOIF(UART_INTSTS[4]) are both set to 1.
<br>
0 = No RX time-out interrupt is generated.
<br>
1 = RX time-out interrupt is generated.
<br>
</div></td></tr><tr><td>
[13]</td><td>BUFERRINT</td><td><div style="word-wrap: break-word;"><b>Buffer Error Interrupt Indicator (Read Only)
</b><br>
This bit is set if BUFERRIEN(UART_INTEN[5]) and BUFERRIF(UART_ INTSTS[5]) are both set to 1.
<br>
0 = No buffer error interrupt is generated.
<br>
1 = Buffer error interrupt is generated.
<br>
</div></td></tr><tr><td>
[14]</td><td>WKINT</td><td><div style="word-wrap: break-word;"><b>UART Wake-up Interrupt Indicator (Read Only)
</b><br>
This bit is set if WKIEN (UART_INTEN[6]) and WKIF (UART_INTSTS[6]) are both set to 1.
<br>
0 = No UART wake-up interrupt is generated.
<br>
1 = UART wake-up interrupt is generated.
<br>
</div></td></tr><tr><td>
[15]</td><td>LININT</td><td><div style="word-wrap: break-word;"><b>LIN Bus Interrupt Indicator (Read Only)
</b><br>
This bit is set if LINIEN (UART_INTEN[8]) and LINIF(UART_INTSTS[7]) are both set to 1.
<br>
0 = No LIN Bus interrupt is generated.
<br>
1 = The LIN Bus interrupt is generated.
<br>
</div></td></tr><tr><td>
[18]</td><td>HWRLSIF</td><td><div style="word-wrap: break-word;"><b>PDMA Mode Receive Line Status Flag (Read Only)
</b><br>
This bit is set when the RX receive data have parity error, frame error or break error (at least one of 3 bits, BIF (UART_FIFOSTS[6]), FEF (UART_FIFOSTS[5]) and PEF (UART_FIFOSTS[4]) is set)
<br>
If RLSIEN (UART_INTEN [2]) is enabled, the RLS interrupt will be generated.
<br>
0 = No RLS interrupt flag is generated in PDMA mode.
<br>
1 = RLS interrupt flag is generated in PDMA mode.
<br>
Note1: In RS-485 function mode, this field include "receiver detect any address byte received address byte character (bit9 = '1') bit".
<br>
Note2: In UART function mode, this bit is read only and reset to 0 when all bits of BIF(UART_FIFOSTS[6]) , FEF(UART_FIFOSTS[5]) and PEF(UART_FIFOSTS[4]) are cleared.
<br>
Note3: In RS-485 function mode, this bit is read only and reset to 0 when all bits of BIF(UART_FIFOSTS[6]), FEF(UART_FIFOSTS[5]), PEF(UART_FIFOSTS[4]) and ADDRDETF (UART_FIFOSTS[3]) are cleared
<br>
</div></td></tr><tr><td>
[19]</td><td>HWMODIF</td><td><div style="word-wrap: break-word;"><b>PDMA Mode MODEM Interrupt Flag (Read Only)
</b><br>
This bit is set when the nCTS pin has state change (CTSDETF (UART_MODEMSTS [0] =1))
<br>
If MODEMIEN (UART_INTEN [3]) is enabled, the Modem interrupt will be generated.
<br>
0 = No Modem interrupt flag is generated in PDMA mode.
<br>
1 = Modem interrupt flag is generated in PDMA mode.
<br>
Note: This bit is read only and reset to 0 when the bit CTSDETF (UART_MODEMSTS[0]) is cleared by writing 1 on CTSDETF (UART_MODEMSTS [0]).
<br>
</div></td></tr><tr><td>
[20]</td><td>HWTOIF</td><td><div style="word-wrap: break-word;"><b>PDMA Mode RX Time-out Interrupt Flag (Read Only)
</b><br>
This bit is set when the RX FIFO is not empty and no activities occurred in the RX FIFO and the time-out counter equal to TOIC (UART_TOUT[7:0])
<br>
If RXTOIEN (UART_INTEN [4]) is enabled, the RX time-out interrupt will be generated .
<br>
0 = No RX time-out interrupt flag is generated in PDMA mode.
<br>
1 = RX time-out interrupt flag is generated in PDMA mode.
<br>
Note: This bit is read only and user can read UART_DAT (RX is in active) to clear it.
<br>
</div></td></tr><tr><td>
[21]</td><td>HWBUFEIF</td><td><div style="word-wrap: break-word;"><b>PDMA Mode Buffer Error Interrupt Flag (Read Only)
</b><br>
This bit is set when the TX or RX FIFO overflows (TXOVIF (UART_FIFOSTS [24]) or RXOVIF (UART_FIFOSTS[0]) is set)
<br>
When BUFERRIF (UART_INTSTS[5]) is set, the transfer maybe is not correct
<br>
If BUFERRIEN (UART_INTEN [5]) is enabled, the buffer error interrupt will be generated.
<br>
0 = No buffer error interrupt flag is generated in PDMA mode.
<br>
1 = Buffer error interrupt flag is generated in PDMA mode.
<br>
Note: This bit is cleared when both TXOVIF (UART_FIFOSTS[24]]) and RXOVIF (UART_FIFOSTS[0]) are cleared.
<br>
</div></td></tr><tr><td>
[22]</td><td>TXENDIF</td><td><div style="word-wrap: break-word;"><b>Transmitter Empty Interrupt Flag
</b><br>
This bit is set when TX FIFO (UART_DAT) is empty and the STOP bit of the last byte has been transmitted (TXEMPTYF (UART_FIFOSTS[28]) is set)
<br>
If TXENDIEN (UART_INTEN[22]) is enabled, the Transmitter Empty interrupt will be generated.
<br>
0 = No transmitter empty interrupt flag is generated.
<br>
1 = Transmitter empty interrupt flag is generated.
<br>
Note: This bit is cleared automatically when TX FIFO is not empty or the last byte transmission has not completed.
<br>
</div></td></tr><tr><td>
[26]</td><td>HWRLSINT</td><td><div style="word-wrap: break-word;"><b>PDMA Mode Receive Line Status Interrupt Indicator (Read Only)
</b><br>
This bit is set if RLSIEN (UART_INTEN[2]) and HWRLSIF(UART_INTSTS[18]) are both set to 1.
<br>
0 = No RLS interrupt is generated in PDMA mode.
<br>
1 = RLS interrupt is generated in PDMA mode.
<br>
</div></td></tr><tr><td>
[27]</td><td>HWMODINT</td><td><div style="word-wrap: break-word;"><b>PDMA Mode MODEM Status Interrupt Indicator (Read Only)
</b><br>
This bit is set if MODEMIEN (UART_INTEN[3]) and HWMODIF(UART_INTSTS[19]) are both set to 1.
<br>
0 = No Modem interrupt is generated in PDMA mode.
<br>
1 = Modem interrupt is generated in PDMA mode.
<br>
</div></td></tr><tr><td>
[28]</td><td>HWTOINT</td><td><div style="word-wrap: break-word;"><b>PDMA Mode RX Time-out Interrupt Indicator (Read Only)
</b><br>
This bit is set if RXTOIEN (UART_INTEN[4]) and HWTOIF(UART_INTSTS[20]) are both set to 1.
<br>
0 = No RX time-out interrupt is generated in PDMA mode.
<br>
1 = RX time-out interrupt is generated in PDMA mode.
<br>
</div></td></tr><tr><td>
[29]</td><td>HWBUFEINT</td><td><div style="word-wrap: break-word;"><b>PDMA Mode Buffer Error Interrupt Indicator (Read Only)
</b><br>
This bit is set if BUFERRIEN (UART_INTEN[5]) and HWBUFEIF (UART_INTSTS[21]) are both set to 1.
<br>
0 = No buffer error interrupt is generated in PDMA mode.
<br>
1 = Buffer error interrupt is generated in PDMA mode.
<br>
</div></td></tr><tr><td>
[30]</td><td>TXENDINT</td><td><div style="word-wrap: break-word;"><b>Transmitter Empty Interrupt Indicator (Read Only)
</b><br>
This bit is set if TXENDIEN (UART_INTEN[22]) and TXENDIF(UART_INTSTS[22]) are both set to 1.
<br>
0 = No Transmitter Empty interrupt is generated.
<br>
1 = Transmitter Empty interrupt is generated.
<br>
</div></td></tr><tr><td>
[31]</td><td>ABRINT</td><td><div style="word-wrap: break-word;"><b>Auto-baud Rate Interrupt Indicator (Read Only)
</b><br>
This bit is set if ABRIEN (UART_INTEN[18]) and ABRIF (UART_ALTCTL[17]) are both set to 1.
<br>
0 = No Auto-baud Rate interrupt is generated.
<br>
1 = The Auto-baud Rate interrupt is generated.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UART_T::TOUT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TOUT
</font><br><p> <font size="2">
Offset: 0x20  UART Time-out Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>TOIC</td><td><div style="word-wrap: break-word;"><b>Time-out Interrupt Comparator
</b><br>
The time-out counter resets and starts counting (the counting clock = baud rate) whenever the RX FIFO receives a new data word if time out counter is enabled by setting TOCNTEN (UART_INTEN[11])
<br>
Once the content of time-out counter is equal to that of time-out interrupt comparator (TOIC (UART_TOUT[7:0])), a receiver time-out interrupt (RXTOINT(UART_INTSTS[12])) is generated if RXTOIEN (UART_INTEN [4]) enabled
<br>
A new incoming data word or RX FIFO empty will clear RXTOIF (UART_INTSTS[4])
<br>
In order to avoid receiver time-out interrupt generation immediately during one character is being received, TOIC value should be set between 40 and 255
<br>
So, for example, if TOIC is set with 40, the time-out interrupt is generated after four characters are not received when 1 stop bit and no parity check is set for UART transfer.
<br>
</div></td></tr><tr><td>
[15:8]</td><td>DLY</td><td><div style="word-wrap: break-word;"><b>TX Delay Time Value
</b><br>
This field is used to programming the transfer delay time between the last stop bit and next start bit
<br>
The unit is bit time.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UART_T::BAUD

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BAUD
</font><br><p> <font size="2">
Offset: 0x24  UART Baud Rate Divider Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>BRD</td><td><div style="word-wrap: break-word;"><b>Baud Rate Divider
</b><br>
The field indicates the baud rate divider
<br>
This filed is used in baud rate calculation
<br>
The detail description is shown in Table 7.15-4.
<br>
</div></td></tr><tr><td>
[27:24]</td><td>EDIVM1</td><td><div style="word-wrap: break-word;"><b>Extra Divider for BAUD Rate Mode 1
</b><br>
This field is used for baud rate calculation in mode 1 and has no effect for baud rate calculation in mode 0 and mode 2
<br>
The detail description is shown in Table 7.15-4
<br>
</div></td></tr><tr><td>
[28]</td><td>BAUDM0</td><td><div style="word-wrap: break-word;"><b>BAUD Rate Mode Selection Bit 0
</b><br>
This bit is baud rate mode selection bit 0
<br>
UART provides three baud rate calculation modes
<br>
This bit combines with BAUDM1 (UART_BAUD[29]) to select baud rate calculation mode
<br>
The detail description is shown in Table 7.15-4.
<br>
</div></td></tr><tr><td>
[29]</td><td>BAUDM1</td><td><div style="word-wrap: break-word;"><b>BAUD Rate Mode Selection Bit 1
</b><br>
This bit is baud rate mode selection bit 1
<br>
UART provides three baud rate calculation modes
<br>
This bit combines with BAUDM0 (UART_BAUD[28]) to select baud rate calculation mode
<br>
The detail description is shown in Table 7.15-4.
<br>
Note: In IrDA mode must be operated in mode 0.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UART_T::IRDA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">IRDA
</font><br><p> <font size="2">
Offset: 0x28  UART IrDA Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1]</td><td>TXEN</td><td><div style="word-wrap: break-word;"><b>IrDA Receiver/Transmitter Selection Enable Bit
</b><br>
0 = IrDA Transmitter Disabled and Receiver Enabled. (Default)
<br>
1 = IrDA Transmitter Enabled and Receiver Disabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>TXINV</td><td><div style="word-wrap: break-word;"><b>IrDA Inverse Transmitting Output Signal
</b><br>
0 = None inverse transmitting signal. (Default).
<br>
1 = Inverse transmitting output signal.
<br>
Note1: Before setting this bit, TXRXDIS (UART_FUNCSEL[3]) should be set then waited for TXRXACT (UART_FIFOSTS[31]) is cleared
<br>
When the configuration is done, cleared TXRXDIS (UART_FUNCSEL[3]) to activate UART controller.
<br>
Note2: This bit is valid when FUNCSEL (UART_FUNCSEL[1:0]) is select IrDA function.
<br>
</div></td></tr><tr><td>
[6]</td><td>RXINV</td><td><div style="word-wrap: break-word;"><b>IrDA Inverse Receive Input Signal
</b><br>
0 = None inverse receiving input signal.
<br>
1 = Inverse receiving input signal. (Default)
<br>
Note1: Before setting this bit, TXRXDIS (UART_FUNCSEL[3]) should be set then waited for TXRXACT (UART_FIFOSTS[31]) is cleared
<br>
When the configuration is done, cleared TXRXDIS (UART_FUNCSEL[3]) to activate UART controller.
<br>
Note2: This bit is valid when FUNCSEL (UART_FUNCSEL[1:0]) is select IrDA function.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UART_T::ALTCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ALTCTL
</font><br><p> <font size="2">
Offset: 0x2C  UART Alternate Control/Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>BRKFL</td><td><div style="word-wrap: break-word;"><b>UART LIN Break Field Length
</b><br>
This field indicates a 4-bit LIN TX break field count.
<br>
Note1: This break field length is BRKFL + 1.
<br>
Note2: According to LIN spec, the reset value is 0xC (break field length = 13).
<br>
</div></td></tr><tr><td>
[6]</td><td>LINRXEN</td><td><div style="word-wrap: break-word;"><b>LIN RX Enable Bit
</b><br>
0 = LIN RX mode Disabled.
<br>
1 = LIN RX mode Enabled.
<br>
</div></td></tr><tr><td>
[7]</td><td>LINTXEN</td><td><div style="word-wrap: break-word;"><b>LIN TX Break Mode Enable Bit
</b><br>
0 = LIN TX Break mode Disabled.
<br>
1 = LIN TX Break mode Enabled.
<br>
Note: When TX break field transfer operation finished, this bit will be cleared automatically.
<br>
</div></td></tr><tr><td>
[8]</td><td>RS485NMM</td><td><div style="word-wrap: break-word;"><b>RS-485 Normal Multi-drop Operation Mode (NMM)
</b><br>
0 = RS-485 Normal Multi-drop Operation mode (NMM) Disabled.
<br>
1 = RS-485 Normal Multi-drop Operation mode (NMM) Enabled.
<br>
Note: It cannot be active with RS-485_AAD operation mode.
<br>
</div></td></tr><tr><td>
[9]</td><td>RS485AAD</td><td><div style="word-wrap: break-word;"><b>RS-485 Auto Address Detection Operation Mode (AAD)
</b><br>
0 = RS-485 Auto Address Detection Operation mode (AAD) Disabled.
<br>
1 = RS-485 Auto Address Detection Operation mode (AAD) Enabled.
<br>
Note: It cannot be active with RS-485_NMM operation mode.
<br>
</div></td></tr><tr><td>
[10]</td><td>RS485AUD</td><td><div style="word-wrap: break-word;"><b>RS-485 Auto Direction Function (AUD)
</b><br>
0 = RS-485 Auto Direction Operation function (AUD) Disabled.
<br>
1 = RS-485 Auto Direction Operation function (AUD) Enabled.
<br>
Note: It can be active with RS-485_AAD or RS-485_NMM operation mode.
<br>
</div></td></tr><tr><td>
[15]</td><td>ADDRDEN</td><td><div style="word-wrap: break-word;"><b>RS-485 Address Detection Enable Bit
</b><br>
This bit is used to enable RS-485 Address Detection mode.
<br>
0 = Address detection mode Disabled.
<br>
1 = Address detection mode Enabled.
<br>
Note: This bit is used for RS-485 any operation mode.
<br>
</div></td></tr><tr><td>
[17]</td><td>ABRIF</td><td><div style="word-wrap: break-word;"><b>Auto-baud Rate Interrupt Flag (Read Only)
</b><br>
This bit is set when auto-baud rate detection function finished or the auto-baud rate counter was overflow and if ABRIEN(UART_INTEN [18]) is set then the auto-baud rate interrupt will be generated.
<br>
0 = No auto-baud rate interrupt flag is generated.
<br>
1 = Auto-baud rate interrupt flag is generated.
<br>
Note: This bit is read only, but it can be cleared by writing '1' to ABRDTOIF (UART_FIFOSTS[2]) and ABRDIF(UART_FIFOSTS[1])
<br>
</div></td></tr><tr><td>
[18]</td><td>ABRDEN</td><td><div style="word-wrap: break-word;"><b>Auto-baud Rate Detect Enable Bit
</b><br>
0 = Auto-baud rate detect function Disabled.
<br>
1 = Auto-baud rate detect function Enabled.
<br>
Note : This bit is cleared automatically after auto-baud detection is finished.
<br>
</div></td></tr><tr><td>
[20:19]</td><td>ABRDBITS</td><td><div style="word-wrap: break-word;"><b>Auto-baud Rate Detect Bit Length
</b><br>
00 = 1-bit time from Start bit to the 1st rising edge. The input pattern shall be 0x01.
<br>
01 = 2-bit time from Start bit to the 1st rising edge. The input pattern shall be 0x02.
<br>
10 = 4-bit time from Start bit to the 1st rising edge. The input pattern shall be 0x08.
<br>
11 = 8-bit time from Start bit to the 1st rising edge. The input pattern shall be 0x80.
<br>
Note : The calculation of bit number includes the START bit.
<br>
</div></td></tr><tr><td>
[31:24]</td><td>ADDRMV</td><td><div style="word-wrap: break-word;"><b>Address Match Value
</b><br>
This field contains the RS-485 address match values.
<br>
Note: This field is used for RS-485 auto address detection mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UART_T::FUNCSEL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">FUNCSEL
</font><br><p> <font size="2">
Offset: 0x30  UART Function Select Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1:0]</td><td>FUNCSEL</td><td><div style="word-wrap: break-word;"><b>Function Select
</b><br>
00 = UART function.
<br>
01 = LIN function.
<br>
10 = IrDA function.
<br>
11 = RS-485 function.
<br>
</div></td></tr><tr><td>
[3]</td><td>TXRXDIS</td><td><div style="word-wrap: break-word;"><b>TX and RX Disable Bit
</b><br>
Setting this bit can disable TX and RX.
<br>
0 = TX and RX Enabled.
<br>
1 = TX and RX Disabled.
<br>
Note: The TX and RX will not disable immediately when this bit is set
<br>
The TX and RX complete current task before disable TX and RX
<br>
When TX and RX disable, the TXRXACT (UART_FIFOSTS[31]) is cleared.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UART_T::LINCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">LINCTL
</font><br><p> <font size="2">
Offset: 0x34  UART LIN Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SLVEN</td><td><div style="word-wrap: break-word;"><b>LIN Slave Mode Enable Bit
</b><br>
0 = LIN slave mode Disabled.
<br>
1 = LIN slave mode Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>SLVHDEN</td><td><div style="word-wrap: break-word;"><b>LIN Slave Header Detection Enable Bit
</b><br>
0 = LIN slave header detection Disabled.
<br>
1 = LIN slave header detection Enabled.
<br>
Note1: This bit only valid when in LIN slave mode (SLVEN (UART_LINCTL[0]) = 1).
<br>
Note2: In LIN function mode, when detect header field (break + sync + frame ID), SLVHDETF (UART_LINSTS [0]) flag will be asserted
<br>
If the LINIEN (UART_INTEN[8]) = 1, an interrupt will be generated.
<br>
</div></td></tr><tr><td>
[2]</td><td>SLVAREN</td><td><div style="word-wrap: break-word;"><b>LIN Slave Automatic Resynchronization Mode Enable Bit
</b><br>
0 = LIN automatic resynchronization Disabled.
<br>
1 = LIN automatic resynchronization Enabled.
<br>
Note1: This bit only valid when in LIN slave mode (SLVEN (UART_LINCTL[0]) = 1).
<br>
Note2: When operation in Automatic Resynchronization mode, the baud rate setting must be mode2 (BAUDM1 (UART_BAUD [29]) and BAUDM0 (UART_BAUD [28]) must be 1).
<br>
Note3: The control and interactions of this field are explained in 7.15.5.9 (Slave mode with automatic resynchronization).
<br>
</div></td></tr><tr><td>
[3]</td><td>SLVDUEN</td><td><div style="word-wrap: break-word;"><b>LIN Slave Divider Update Method Enable Bit
</b><br>
0 = UART_BAUD updated is written by software (if no automatic resynchronization update occurs at the same time).
<br>
1 = UART_BAUD is updated at the next received character
<br>
User must set the bit before checksum reception.
<br>
Note1: This bit only valid when in LIN slave mode (SLVEN (UART_LINCTL[0]) = 1).
<br>
Note2: This bit used for LIN Slave Automatic Resynchronization mode
<br>
(for Non-Automatic Resynchronization mode, this bit should be kept cleared)
<br>
Note3: The control and interactions of this field are explained in 7.15.5.9 (Slave mode with automatic resynchronization).
<br>
</div></td></tr><tr><td>
[4]</td><td>MUTE</td><td><div style="word-wrap: break-word;"><b>LIN Mute Mode Enable Bit
</b><br>
0 = LIN mute mode Disabled.
<br>
1 = LIN mute mode Enabled.
<br>
Note: The exit from mute mode condition and each control and interactions of this field are explained in 7.15.5.9 (LIN slave mode).
<br>
</div></td></tr><tr><td>
[8]</td><td>SENDH</td><td><div style="word-wrap: break-word;"><b>LIN TX Send Header Enable Bit
</b><br>
The LIN TX header can be break field or 'break and sync field' or 'break, sync and frame ID field', it is depend on setting HSEL (UART_LINCTL[23:22]).
<br>
0 = Send LIN TX header Disabled.
<br>
1 = Send LIN TX header Enabled.
<br>
Note1: This bit is shadow bit of LINTXEN (UART_ALTCTL [7]); user can read/write it by setting LINTXEN (UART_ALTCTL [7]) or SENDH (UART_LINCTL [8]).
<br>
Note2: When transmitter header field (it may be 'break' or 'break + sync' or 'break + sync + frame ID' selected by HSEL (UART_LINCTL[23:22]) field) transfer operation finished, this bit will be cleared automatically.
<br>
</div></td></tr><tr><td>
[9]</td><td>IDPEN</td><td><div style="word-wrap: break-word;"><b>LIN ID Parity Enable Bit
</b><br>
0 = LIN frame ID parity Disabled.
<br>
1 = LIN frame ID parity Enabled.
<br>
Note1: This bit can be used for LIN master to sending header field (SENDH (UART_LINCTL[8])) = 1 and HSEL (UART_LINCTL[23:22]) = 10 or be used for enable LIN slave received frame ID parity checked.
<br>
Note2: This bit is only used when the operation header transmitter is in HSEL (UART_LINCTL[23:22]) = 10
<br>
</div></td></tr><tr><td>
[10]</td><td>BRKDETEN</td><td><div style="word-wrap: break-word;"><b>LIN Break Detection Enable Bit
</b><br>
When detect consecutive dominant greater than 11 bits, and are followed by a delimiter character, the BRKDETF (UART_LINSTS[8]) flag is set at the end of break field
<br>
If the LINIEN (UART_INTEN [8])=1, an interrupt will be generated.
<br>
0 = LIN break detection Disabled .
<br>
1 = LIN break detection Enabled.
<br>
</div></td></tr><tr><td>
[11]</td><td>LINRXOFF</td><td><div style="word-wrap: break-word;"><b>LIN Receiver Disable Bit
</b><br>
If the receiver is enabled (LINRXOFF (UART_LINCTL[11] ) = 0), all received byte data will be accepted and stored in the RX FIFO, and if the receiver is disabled (LINRXOFF (UART_LINCTL[11] = 1), all received byte data will be ignore.
<br>
0 = LIN receiver Enabled.
<br>
1 = LIN receiver Disabled.
<br>
Note: This bit is only valid when operating in LIN function mode (FUNCSEL (UART_FUNCSEL[1:0]) = 01).
<br>
</div></td></tr><tr><td>
[12]</td><td>BITERREN</td><td><div style="word-wrap: break-word;"><b>Bit Error Detect Enable Bit
</b><br>
0 = Bit error detection function Disabled.
<br>
1 = Bit error detection function Enabled.
<br>
Note: In LIN function mode, when occur bit error, the BITEF (UART_LINSTS[9]) flag will be asserted
<br>
If the LINIEN (UART_INTEN[8]) = 1, an interrupt will be generated.
<br>
</div></td></tr><tr><td>
[19:16]</td><td>BRKFL</td><td><div style="word-wrap: break-word;"><b>LIN Break Field Length
</b><br>
This field indicates a 4-bit LIN TX break field count.
<br>
Note1: These registers are shadow registers of BRKFL (UART_ALTCTL[3:0]), User can read/write it by setting BRKFL (UART_ALTCTL[3:0]) or BRKFL (UART_LINCTL[19:16]).
<br>
Note2: This break field length is BRKFL + 1.
<br>
Note3: According to LIN spec, the reset value is 12 (break field length = 13).
<br>
</div></td></tr><tr><td>
[21:20]</td><td>BSL</td><td><div style="word-wrap: break-word;"><b>LIN Break/Sync Delimiter Length
</b><br>
00 = The LIN break/sync delimiter length is 1-bit time.
<br>
01 = The LIN break/sync delimiter length is 2-bit time.
<br>
10 = The LIN break/sync delimiter length is 3-bit time.
<br>
11 = The LIN break/sync delimiter length is 4-bit time.
<br>
Note: This bit used for LIN master to sending header field.
<br>
</div></td></tr><tr><td>
[23:22]</td><td>HSEL</td><td><div style="word-wrap: break-word;"><b>LIN Header Select
</b><br>
00 = The LIN header includes 'break field'.
<br>
01 = The LIN header includes 'break field' and 'sync field'.
<br>
10 = The LIN header includes 'break field', 'sync field' and 'frame ID field'.
<br>
11 = Reserved.
<br>
Note: This bit is used to master mode for LIN to send header field (SENDH (UART_LINCTL [8]) = 1) or used to slave to indicates exit from mute mode condition (MUTE (UART_LINCTL[4] = 1).
<br>
</div></td></tr><tr><td>
[31:24]</td><td>PID</td><td><div style="word-wrap: break-word;"><b>LIN PID Bits
</b><br>
This field contains the LIN frame ID value when in LIN function mode, the frame ID parity can be generated by software or hardware depends on IDPEN (UART_LINCTL[9]) = 1.
<br>
If the parity generated by hardware, user fill ID0~ID5 (PID [29:24] ), hardware will calculate P0 (PID[30]) and P1 (PID[31]), otherwise user must filled frame ID and parity in this field.
<br>
Note1: User can fill any 8-bit value to this field and the bit 24 indicates ID0 (LSB first).
<br>
Note2: This field can be used for LIN master mode or slave mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UART_T::LINSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">LINSTS
</font><br><p> <font size="2">
Offset: 0x38  UART LIN Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SLVHDETF</td><td><div style="word-wrap: break-word;"><b>LIN Slave Header Detection Flag
</b><br>
This bit is set by hardware when a LIN header is detected in LIN slave mode and be cleared by writing 1 to it.
<br>
0 = LIN header not detected.
<br>
1 = LIN header detected (break + sync + frame ID).
<br>
Note1: This bit can be cleared by writing 1 to it.
<br>
Note2: This bit is only valid when in LIN slave mode (SLVEN (UART_LINCTL [0]) = 1) and enable LIN slave header detection function (SLVHDEN (UART_LINCTL [1])).
<br>
Note3: When enable ID parity check IDPEN (UART_LINCTL [9]), if hardware detect complete header ('break + sync + frame ID'), the SLVHDETF will be set whether the frame ID correct or not.
<br>
</div></td></tr><tr><td>
[1]</td><td>SLVHEF</td><td><div style="word-wrap: break-word;"><b>LIN Slave Header Error Flag
</b><br>
This bit is set by hardware when a LIN header error is detected in LIN slave mode and be cleared by writing 1 to it
<br>
The header errors include 'break delimiter is too short (less than 0.5 bit time)', 'frame error in sync field or Identifier field',
<br>
'sync field data is not 0x55 in Non-Automatic Resynchronization mode', 'sync field deviation error with Automatic Resynchronization mode',
<br>
'sync field measure time-out with Automatic Resynchronization mode' and 'LIN header reception time-out'.
<br>
0 = LIN header error not detected.
<br>
1 = LIN header error detected.
<br>
Note1: This bit can be cleared by writing 1 to it.
<br>
Note2: This bit is only valid when UART is operated in LIN slave mode (SLVEN (UART_LINCTL [0]) = 1) and
<br>
enables LIN slave header detection function (SLVHDEN (UART_LINCTL [1])).
<br>
</div></td></tr><tr><td>
[2]</td><td>SLVIDPEF</td><td><div style="word-wrap: break-word;"><b>LIN Slave ID Parity Error Flag
</b><br>
This bit is set by hardware when receipted frame ID parity is not correct.
<br>
0 = No active.
<br>
1 = Receipted frame ID parity is not correct.
<br>
Note1: This bit can be cleared by writing 1 to it.
<br>
Note2: This bit is only valid when in LIN slave mode (SLVEN (UART_LINCTL [0])= 1) and enable LIN frame ID parity check function IDPEN (UART_LINCTL [9]).
<br>
</div></td></tr><tr><td>
[3]</td><td>SLVSYNCF</td><td><div style="word-wrap: break-word;"><b>LIN Slave Sync Field
</b><br>
This bit indicates that the LIN sync field is being analyzed in Automatic Resynchronization mode
<br>
When the receiver header have some error been detect, user must reset the internal circuit to re-search new frame header by writing 1 to this bit.
<br>
0 = The current character is not at LIN sync state.
<br>
1 = The current character is at LIN sync state.
<br>
Note1: This bit is only valid when in LIN Slave mode (SLVEN(UART_LINCTL[0]) = 1).
<br>
Note2: This bit can be cleared by writing 1 to it.
<br>
Note3: When writing 1 to it, hardware will reload the initial baud rate and re-search a new frame header.
<br>
</div></td></tr><tr><td>
[8]</td><td>BRKDETF</td><td><div style="word-wrap: break-word;"><b>LIN Break Detection Flag
</b><br>
This bit is set by hardware when a break is detected and be cleared by writing 1 to it through software.
<br>
0 = LIN break not detected.
<br>
1 = LIN break detected.
<br>
Note1: This bit can be cleared by writing 1 to it.
<br>
Note2: This bit is only valid when LIN break detection function is enabled (BRKDETEN (UART_LINCTL[10]) =1).
<br>
</div></td></tr><tr><td>
[9]</td><td>BITEF</td><td><div style="word-wrap: break-word;"><b>Bit Error Detect Status Flag
</b><br>
At TX transfer state, hardware will monitor the bus state, if the input pin (UART_RXD) state not equals to the output pin (UART_TXD) state, BITEF (UART_LINSTS[9]) will be set.
<br>
When occur bit error, if the LINIEN (UART_INTEN[8]) = 1, an interrupt will be generated.
<br>
0 = Bit error not detected.
<br>
1 = Bit error detected.
<br>
Note1: This bit can be cleared by writing 1 to it.
<br>
Note2: This bit is only valid when enable bit error detection function (BITERREN (UART_LINCTL [12]) = 1).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UART_T::BRCOMP

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BRCOMP
</font><br><p> <font size="2">
Offset: 0x3C  UART Baud Rate Compensation Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[8:0]</td><td>BRCOMP</td><td><div style="word-wrap: break-word;"><b>Baud Rate Compensation Patten
</b><br>
These 9-bits are used to define the relative bit is compensated or not.
<br>
BRCOMP[7:0] is used to define the compensation of UART_DAT[7:0] and BRCOM[8] is used to define the parity bit.
<br>
</div></td></tr><tr><td>
[31]</td><td>BRCOMPDEC</td><td><div style="word-wrap: break-word;"><b>Baud Rate Compensation Decrease
</b><br>
0 = Positive (increase one module clock) compensation for each compensated bit.
<br>
1 = Negative (decrease one module clock) compensation for each compensated bit.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UART_T::WKCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">WKCTL
</font><br><p> <font size="2">
Offset: 0x40  UART Wake-up Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>WKCTSEN</td><td><div style="word-wrap: break-word;"><b>nCTS Wake-up Enable Bit
</b><br>
0 = nCTS Wake-up system function Disabled.
<br>
1 = nCTS Wake-up system function Enabled, when the system is in Power-down mode, an external.
<br>
nCTS change will wake-up system from Power-down mode.
<br>
</div></td></tr><tr><td>
[1]</td><td>WKDATEN</td><td><div style="word-wrap: break-word;"><b>Incoming Data Wake-up Enable Bit
</b><br>
0 = Incoming data wake-up system function Disabled.
<br>
1 = Incoming data wake-up system function Enabled, when the system is in Power-down mode,.
<br>
incoming data will wake-up system from Power-down mode.
<br>
</div></td></tr><tr><td>
[2]</td><td>WKRFRTEN</td><td><div style="word-wrap: break-word;"><b>Received Data FIFO Reached Threshold Wake-up Enable Bit
</b><br>
0 = Received Data FIFO reached threshold wake-up system function Disabled.
<br>
1 = Received Data FIFO reached threshold wake-up system function Enabled, when the system is.
<br>
in Power-down mode, Received Data FIFO reached threshold will wake-up system from
<br>
Power-down mode.
<br>
</div></td></tr><tr><td>
[3]</td><td>WKRS485EN</td><td><div style="word-wrap: break-word;"><b>RS-485 Address Match (AAD Mode) Wake-up Enable Bit
</b><br>
0 = RS-485 Address Match (AAD mode) wake-up system function Disabled.
<br>
1 = RS-485 Address Match (AAD mode) wake-up system function Enabled, when the system is in.
<br>
Power-down mode, RS-485 Address Match will wake-up system from Power-down mode.
<br>
Note: This bit is used for RS-485 Auto Address Detection (AAD) mode in RS-485 function mode
<br>
and ADDRDEN (UART_ALTCTL[15]) is set to 1.
<br>
</div></td></tr><tr><td>
[4]</td><td>WKTOUTEN</td><td><div style="word-wrap: break-word;"><b>Received Data FIFO Reached Threshold Time-out Wake-up Enable Bit
</b><br>
0 = Received Data FIFO reached threshold time-out wake-up system function Disabled.
<br>
1 = Received Data FIFO reached threshold time-out wake-up system function Enabled, when the.
<br>
system is in Power-down mode, Received Data FIFO reached threshold time-out will wake-up
<br>
system from Power-down mode.
<br>
Note: It is suggest the function is enabled when the WKRFRTEN (UART_WKCTL[2]) is set to 1.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UART_T::WKSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">WKSTS
</font><br><p> <font size="2">
Offset: 0x44  UART Wake-up Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CTSWKF</td><td><div style="word-wrap: break-word;"><b>nCTS Wake-up Flag
</b><br>
This bit is set if chip wake-up from power-down state by nCTS wake-up.
<br>
0 = Chip stays in power-down state.
<br>
1 = Chip wake-up from power-down state by nCTS wake-up.
<br>
Note1: If WKCTSEN (UART_WKCTL[0]) is enabled, the nCTS wake-up cause this bit is set to '1'.
<br>
Note2: This bit can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[1]</td><td>DATWKF</td><td><div style="word-wrap: break-word;"><b>Incoming Data Wake-up Flag
</b><br>
This bit is set if chip wake-up from power-down state by data wake-up.
<br>
0 = Chip stays in power-down state.
<br>
1 = Chip wake-up from power-down state by Incoming Data wake-up.
<br>
Note1: If WKDATEN (UART_WKCTL[1]) is enabled, the Incoming Data wake-up cause this bit is set to '1'.
<br>
Note2: This bit can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[2]</td><td>RFRTWKF</td><td><div style="word-wrap: break-word;"><b>Received Data FIFO Reached Threshold Wake-up Flag
</b><br>
This bit is set if chip wake-up from power-down state by Received Data FIFO reached threshold
<br>
wake-up .
<br>
0 = Chip stays in power-down state.
<br>
1 = Chip wake-up from power-down state by Received Data FIFO Reached Threshold wake-up.
<br>
Note1: If WKRFRTEN (UART_WKCTL[2]) is enabled, the Received Data FIFO Reached Threshold wake-up cause this bit is set to '1'.
<br>
Note2: This bit can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[3]</td><td>RS485WKF</td><td><div style="word-wrap: break-word;"><b>RS-485 Address Match (AAD Mode) Wake-up Flag
</b><br>
This bit is set if chip wake-up from power-down state by RS-485 Address Match (AAD mode).
<br>
0 = Chip stays in power-down state.
<br>
1 = Chip wake-up from power-down state by RS-485 Address Match (AAD mode) wake-up.
<br>
Note1: If WKRS485EN (UART_WKCTL[3]) is enabled, the RS-485 Address Match (AAD mode) wake-up cause this bit is set to '1'.
<br>
Note2: This bit can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[4]</td><td>TOUTWKF</td><td><div style="word-wrap: break-word;"><b>Received Data FIFO Threshold Time-out Wake-up Flag
</b><br>
This bit is set if chip wake-up from power-down state by Received Data FIFO Threshold Time-out
<br>
wake-up.
<br>
0 = Chip stays in power-down state.
<br>
1 = Chip wake-up from power-down state by Received Data FIFO reached threshold time-out.
<br>
wake-up.
<br>
Note1: If WKTOUTEN (UART_WKCTL[4]) is enabled, the Received Data FIFO reached threshold time-out wake-up cause this bit is set to '1'.
<br>
Note2: This bit can be cleared by writing '1' to it.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UART_T::DWKCOMP

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DWKCOMP
</font><br><p> <font size="2">
Offset: 0x48  UART Incoming Data Wake-up Compensation Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>STCOMP</td><td><div style="word-wrap: break-word;"><b>Start Bit Compensation Value
</b><br>
These bits field indicate how many clock cycle selected by UART_CLK do the UART controller can get the 1st bit (start bit) when the device is wake-up from power-down mode.
<br>
Note: It is valid only when WKDATEN (UART_WKCTL[1]) is set.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t DAT;                   /*!< [0x0000] UART Receive/Transmit Buffer Register                            */
    __IO uint32_t INTEN;                 /*!< [0x0004] UART Interrupt Enable Register                                   */
    __IO uint32_t FIFO;                  /*!< [0x0008] UART FIFO Control Register                                       */
    __IO uint32_t LINE;                  /*!< [0x000c] UART Line Control Register                                       */
    __IO uint32_t MODEM;                 /*!< [0x0010] UART Modem Control Register                                      */
    __IO uint32_t MODEMSTS;              /*!< [0x0014] UART Modem Status Register                                       */
    __IO uint32_t FIFOSTS;               /*!< [0x0018] UART FIFO Status Register                                        */
    __IO uint32_t INTSTS;                /*!< [0x001c] UART Interrupt Status Register                                   */
    __IO uint32_t TOUT;                  /*!< [0x0020] UART Time-out Register                                           */
    __IO uint32_t BAUD;                  /*!< [0x0024] UART Baud Rate Divider Register                                  */
    __IO uint32_t IRDA;                  /*!< [0x0028] UART IrDA Control Register                                       */
    __IO uint32_t ALTCTL;                /*!< [0x002c] UART Alternate Control/Status Register                           */
    __IO uint32_t FUNCSEL;               /*!< [0x0030] UART Function Select Register                                    */
    __IO uint32_t LINCTL;                /*!< [0x0034] UART LIN Control Register                                        */
    __IO uint32_t LINSTS;                /*!< [0x0038] UART LIN Status Register                                         */
    __IO uint32_t BRCOMP;                /*!< [0x003c] UART Baud Rate Compensation Register                             */
    __IO uint32_t WKCTL;                 /*!< [0x0040] UART Wake-up Control Register                                    */
    __IO uint32_t WKSTS;                 /*!< [0x0044] UART Wake-up Status Register                                     */
    __IO uint32_t DWKCOMP;               /*!< [0x0048] UART Incoming Data Wake-up Compensation Register                 */

} UART_T;

/**
    @addtogroup UART_CONST UART Bit Field Definition
    Constant Definitions for UART Controller
@{ */

#define UART_DAT_DAT_Pos                 (0)                                               /*!< UART_T::DAT: DAT Position              */
#define UART_DAT_DAT_Msk                 (0xfful << UART_DAT_DAT_Pos)                      /*!< UART_T::DAT: DAT Mask                  */

#define UART_DAT_PARITY_Pos              (8)                                               /*!< UART_T::DAT: PARITY Position           */
#define UART_DAT_PARITY_Msk              (0x1ul << UART_DAT_PARITY_Pos)                    /*!< UART_T::DAT: PARITY Mask               */

#define UART_INTEN_RDAIEN_Pos            (0)                                               /*!< UART_T::INTEN: RDAIEN Position         */
#define UART_INTEN_RDAIEN_Msk            (0x1ul << UART_INTEN_RDAIEN_Pos)                  /*!< UART_T::INTEN: RDAIEN Mask             */

#define UART_INTEN_THREIEN_Pos           (1)                                               /*!< UART_T::INTEN: THREIEN Position        */
#define UART_INTEN_THREIEN_Msk           (0x1ul << UART_INTEN_THREIEN_Pos)                 /*!< UART_T::INTEN: THREIEN Mask            */

#define UART_INTEN_RLSIEN_Pos            (2)                                               /*!< UART_T::INTEN: RLSIEN Position         */
#define UART_INTEN_RLSIEN_Msk            (0x1ul << UART_INTEN_RLSIEN_Pos)                  /*!< UART_T::INTEN: RLSIEN Mask             */

#define UART_INTEN_MODEMIEN_Pos          (3)                                               /*!< UART_T::INTEN: MODEMIEN Position       */
#define UART_INTEN_MODEMIEN_Msk          (0x1ul << UART_INTEN_MODEMIEN_Pos)                /*!< UART_T::INTEN: MODEMIEN Mask           */

#define UART_INTEN_RXTOIEN_Pos           (4)                                               /*!< UART_T::INTEN: RXTOIEN Position        */
#define UART_INTEN_RXTOIEN_Msk           (0x1ul << UART_INTEN_RXTOIEN_Pos)                 /*!< UART_T::INTEN: RXTOIEN Mask            */

#define UART_INTEN_BUFERRIEN_Pos         (5)                                               /*!< UART_T::INTEN: BUFERRIEN Position      */
#define UART_INTEN_BUFERRIEN_Msk         (0x1ul << UART_INTEN_BUFERRIEN_Pos)               /*!< UART_T::INTEN: BUFERRIEN Mask          */

#define UART_INTEN_WKIEN_Pos             (6)                                               /*!< UART_T::INTEN: WKIEN Position          */
#define UART_INTEN_WKIEN_Msk             (0x1ul << UART_INTEN_WKIEN_Pos)                   /*!< UART_T::INTEN: WKIEN Mask              */

#define UART_INTEN_LINIEN_Pos            (8)                                               /*!< UART_T::INTEN: LINIEN Position         */
#define UART_INTEN_LINIEN_Msk            (0x1ul << UART_INTEN_LINIEN_Pos)                  /*!< UART_T::INTEN: LINIEN Mask             */

#define UART_INTEN_TOCNTEN_Pos           (11)                                              /*!< UART_T::INTEN: TOCNTEN Position        */
#define UART_INTEN_TOCNTEN_Msk           (0x1ul << UART_INTEN_TOCNTEN_Pos)                 /*!< UART_T::INTEN: TOCNTEN Mask            */

#define UART_INTEN_ATORTSEN_Pos          (12)                                              /*!< UART_T::INTEN: ATORTSEN Position       */
#define UART_INTEN_ATORTSEN_Msk          (0x1ul << UART_INTEN_ATORTSEN_Pos)                /*!< UART_T::INTEN: ATORTSEN Mask           */

#define UART_INTEN_ATOCTSEN_Pos          (13)                                              /*!< UART_T::INTEN: ATOCTSEN Position       */
#define UART_INTEN_ATOCTSEN_Msk          (0x1ul << UART_INTEN_ATOCTSEN_Pos)                /*!< UART_T::INTEN: ATOCTSEN Mask           */

#define UART_INTEN_TXPDMAEN_Pos          (14)                                              /*!< UART_T::INTEN: TXPDMAEN Position       */
#define UART_INTEN_TXPDMAEN_Msk          (0x1ul << UART_INTEN_TXPDMAEN_Pos)                /*!< UART_T::INTEN: TXPDMAEN Mask           */

#define UART_INTEN_RXPDMAEN_Pos          (15)                                              /*!< UART_T::INTEN: RXPDMAEN Position       */
#define UART_INTEN_RXPDMAEN_Msk          (0x1ul << UART_INTEN_RXPDMAEN_Pos)                /*!< UART_T::INTEN: RXPDMAEN Mask           */

#define UART_INTEN_ABRIEN_Pos            (18)                                              /*!< UART_T::INTEN: ABRIEN Position         */
#define UART_INTEN_ABRIEN_Msk            (0x1ul << UART_INTEN_ABRIEN_Pos)                  /*!< UART_T::INTEN: ABRIEN Mask             */

#define UART_INTEN_TXENDIEN_Pos          (22)                                              /*!< UART_T::INTEN: TXENDIEN Position       */
#define UART_INTEN_TXENDIEN_Msk          (0x1ul << UART_INTEN_TXENDIEN_Pos)                /*!< UART_T::INTEN: TXENDIEN Mask           */

#define UART_FIFO_RXRST_Pos              (1)                                               /*!< UART_T::FIFO: RXRST Position           */
#define UART_FIFO_RXRST_Msk              (0x1ul << UART_FIFO_RXRST_Pos)                    /*!< UART_T::FIFO: RXRST Mask               */

#define UART_FIFO_TXRST_Pos              (2)                                               /*!< UART_T::FIFO: TXRST Position           */
#define UART_FIFO_TXRST_Msk              (0x1ul << UART_FIFO_TXRST_Pos)                    /*!< UART_T::FIFO: TXRST Mask               */

#define UART_FIFO_RFITL_Pos              (4)                                               /*!< UART_T::FIFO: RFITL Position           */
#define UART_FIFO_RFITL_Msk              (0xful << UART_FIFO_RFITL_Pos)                    /*!< UART_T::FIFO: RFITL Mask               */

#define UART_FIFO_RXOFF_Pos              (8)                                               /*!< UART_T::FIFO: RXOFF Position           */
#define UART_FIFO_RXOFF_Msk              (0x1ul << UART_FIFO_RXOFF_Pos)                    /*!< UART_T::FIFO: RXOFF Mask               */

#define UART_FIFO_RTSTRGLV_Pos           (16)                                              /*!< UART_T::FIFO: RTSTRGLV Position        */
#define UART_FIFO_RTSTRGLV_Msk           (0xful << UART_FIFO_RTSTRGLV_Pos)                 /*!< UART_T::FIFO: RTSTRGLV Mask            */

#define UART_LINE_WLS_Pos                (0)                                               /*!< UART_T::LINE: WLS Position             */
#define UART_LINE_WLS_Msk                (0x3ul << UART_LINE_WLS_Pos)                      /*!< UART_T::LINE: WLS Mask                 */

#define UART_LINE_NSB_Pos                (2)                                               /*!< UART_T::LINE: NSB Position             */
#define UART_LINE_NSB_Msk                (0x1ul << UART_LINE_NSB_Pos)                      /*!< UART_T::LINE: NSB Mask                 */

#define UART_LINE_PBE_Pos                (3)                                               /*!< UART_T::LINE: PBE Position             */
#define UART_LINE_PBE_Msk                (0x1ul << UART_LINE_PBE_Pos)                      /*!< UART_T::LINE: PBE Mask                 */

#define UART_LINE_EPE_Pos                (4)                                               /*!< UART_T::LINE: EPE Position             */
#define UART_LINE_EPE_Msk                (0x1ul << UART_LINE_EPE_Pos)                      /*!< UART_T::LINE: EPE Mask                 */

#define UART_LINE_SPE_Pos                (5)                                               /*!< UART_T::LINE: SPE Position             */
#define UART_LINE_SPE_Msk                (0x1ul << UART_LINE_SPE_Pos)                      /*!< UART_T::LINE: SPE Mask                 */

#define UART_LINE_BCB_Pos                (6)                                               /*!< UART_T::LINE: BCB Position             */
#define UART_LINE_BCB_Msk                (0x1ul << UART_LINE_BCB_Pos)                      /*!< UART_T::LINE: BCB Mask                 */

#define UART_LINE_PSS_Pos                (7)                                               /*!< UART_T::LINE: PSS Position             */
#define UART_LINE_PSS_Msk                (0x1ul << UART_LINE_PSS_Pos)                      /*!< UART_T::LINE: PSS Mask                 */

#define UART_LINE_TXDINV_Pos             (8)                                               /*!< UART_T::LINE: TXDINV Position          */
#define UART_LINE_TXDINV_Msk             (0x1ul << UART_LINE_TXDINV_Pos)                   /*!< UART_T::LINE: TXDINV Mask              */

#define UART_LINE_RXDINV_Pos             (9)                                               /*!< UART_T::LINE: RXDINV Position          */
#define UART_LINE_RXDINV_Msk             (0x1ul << UART_LINE_RXDINV_Pos)                   /*!< UART_T::LINE: RXDINV Mask              */

#define UART_MODEM_RTS_Pos               (1)                                               /*!< UART_T::MODEM: RTS Position            */
#define UART_MODEM_RTS_Msk               (0x1ul << UART_MODEM_RTS_Pos)                     /*!< UART_T::MODEM: RTS Mask                */

#define UART_MODEM_RTSACTLV_Pos          (9)                                               /*!< UART_T::MODEM: RTSACTLV Position       */
#define UART_MODEM_RTSACTLV_Msk          (0x1ul << UART_MODEM_RTSACTLV_Pos)                /*!< UART_T::MODEM: RTSACTLV Mask           */

#define UART_MODEM_RTSSTS_Pos            (13)                                              /*!< UART_T::MODEM: RTSSTS Position         */
#define UART_MODEM_RTSSTS_Msk            (0x1ul << UART_MODEM_RTSSTS_Pos)                  /*!< UART_T::MODEM: RTSSTS Mask             */

#define UART_MODEMSTS_CTSDETF_Pos        (0)                                               /*!< UART_T::MODEMSTS: CTSDETF Position     */
#define UART_MODEMSTS_CTSDETF_Msk        (0x1ul << UART_MODEMSTS_CTSDETF_Pos)              /*!< UART_T::MODEMSTS: CTSDETF Mask         */

#define UART_MODEMSTS_CTSSTS_Pos         (4)                                               /*!< UART_T::MODEMSTS: CTSSTS Position      */
#define UART_MODEMSTS_CTSSTS_Msk         (0x1ul << UART_MODEMSTS_CTSSTS_Pos)               /*!< UART_T::MODEMSTS: CTSSTS Mask          */

#define UART_MODEMSTS_CTSACTLV_Pos       (8)                                               /*!< UART_T::MODEMSTS: CTSACTLV Position    */
#define UART_MODEMSTS_CTSACTLV_Msk       (0x1ul << UART_MODEMSTS_CTSACTLV_Pos)             /*!< UART_T::MODEMSTS: CTSACTLV Mask        */

#define UART_FIFOSTS_RXOVIF_Pos          (0)                                               /*!< UART_T::FIFOSTS: RXOVIF Position       */
#define UART_FIFOSTS_RXOVIF_Msk          (0x1ul << UART_FIFOSTS_RXOVIF_Pos)                /*!< UART_T::FIFOSTS: RXOVIF Mask           */

#define UART_FIFOSTS_ABRDIF_Pos          (1)                                               /*!< UART_T::FIFOSTS: ABRDIF Position       */
#define UART_FIFOSTS_ABRDIF_Msk          (0x1ul << UART_FIFOSTS_ABRDIF_Pos)                /*!< UART_T::FIFOSTS: ABRDIF Mask           */

#define UART_FIFOSTS_ABRDTOIF_Pos        (2)                                               /*!< UART_T::FIFOSTS: ABRDTOIF Position     */
#define UART_FIFOSTS_ABRDTOIF_Msk        (0x1ul << UART_FIFOSTS_ABRDTOIF_Pos)              /*!< UART_T::FIFOSTS: ABRDTOIF Mask         */

#define UART_FIFOSTS_ADDRDETF_Pos        (3)                                               /*!< UART_T::FIFOSTS: ADDRDETF Position     */
#define UART_FIFOSTS_ADDRDETF_Msk        (0x1ul << UART_FIFOSTS_ADDRDETF_Pos)              /*!< UART_T::FIFOSTS: ADDRDETF Mask         */

#define UART_FIFOSTS_PEF_Pos             (4)                                               /*!< UART_T::FIFOSTS: PEF Position          */
#define UART_FIFOSTS_PEF_Msk             (0x1ul << UART_FIFOSTS_PEF_Pos)                   /*!< UART_T::FIFOSTS: PEF Mask              */

#define UART_FIFOSTS_FEF_Pos             (5)                                               /*!< UART_T::FIFOSTS: FEF Position          */
#define UART_FIFOSTS_FEF_Msk             (0x1ul << UART_FIFOSTS_FEF_Pos)                   /*!< UART_T::FIFOSTS: FEF Mask              */

#define UART_FIFOSTS_BIF_Pos             (6)                                               /*!< UART_T::FIFOSTS: BIF Position          */
#define UART_FIFOSTS_BIF_Msk             (0x1ul << UART_FIFOSTS_BIF_Pos)                   /*!< UART_T::FIFOSTS: BIF Mask              */

#define UART_FIFOSTS_RXPTR_Pos           (8)                                               /*!< UART_T::FIFOSTS: RXPTR Position        */
#define UART_FIFOSTS_RXPTR_Msk           (0x3ful << UART_FIFOSTS_RXPTR_Pos)                /*!< UART_T::FIFOSTS: RXPTR Mask            */

#define UART_FIFOSTS_RXEMPTY_Pos         (14)                                              /*!< UART_T::FIFOSTS: RXEMPTY Position      */
#define UART_FIFOSTS_RXEMPTY_Msk         (0x1ul << UART_FIFOSTS_RXEMPTY_Pos)               /*!< UART_T::FIFOSTS: RXEMPTY Mask          */

#define UART_FIFOSTS_RXFULL_Pos          (15)                                              /*!< UART_T::FIFOSTS: RXFULL Position       */
#define UART_FIFOSTS_RXFULL_Msk          (0x1ul << UART_FIFOSTS_RXFULL_Pos)                /*!< UART_T::FIFOSTS: RXFULL Mask           */

#define UART_FIFOSTS_TXPTR_Pos           (16)                                              /*!< UART_T::FIFOSTS: TXPTR Position        */
#define UART_FIFOSTS_TXPTR_Msk           (0x3ful << UART_FIFOSTS_TXPTR_Pos)                /*!< UART_T::FIFOSTS: TXPTR Mask            */

#define UART_FIFOSTS_TXEMPTY_Pos         (22)                                              /*!< UART_T::FIFOSTS: TXEMPTY Position      */
#define UART_FIFOSTS_TXEMPTY_Msk         (0x1ul << UART_FIFOSTS_TXEMPTY_Pos)               /*!< UART_T::FIFOSTS: TXEMPTY Mask          */

#define UART_FIFOSTS_TXFULL_Pos          (23)                                              /*!< UART_T::FIFOSTS: TXFULL Position       */
#define UART_FIFOSTS_TXFULL_Msk          (0x1ul << UART_FIFOSTS_TXFULL_Pos)                /*!< UART_T::FIFOSTS: TXFULL Mask           */

#define UART_FIFOSTS_TXOVIF_Pos          (24)                                              /*!< UART_T::FIFOSTS: TXOVIF Position       */
#define UART_FIFOSTS_TXOVIF_Msk          (0x1ul << UART_FIFOSTS_TXOVIF_Pos)                /*!< UART_T::FIFOSTS: TXOVIF Mask           */

#define UART_FIFOSTS_TXEMPTYF_Pos        (28)                                              /*!< UART_T::FIFOSTS: TXEMPTYF Position     */
#define UART_FIFOSTS_TXEMPTYF_Msk        (0x1ul << UART_FIFOSTS_TXEMPTYF_Pos)              /*!< UART_T::FIFOSTS: TXEMPTYF Mask         */

#define UART_FIFOSTS_RXIDLE_Pos          (29)                                              /*!< UART_T::FIFOSTS: RXIDLE Position       */
#define UART_FIFOSTS_RXIDLE_Msk          (0x1ul << UART_FIFOSTS_RXIDLE_Pos)                /*!< UART_T::FIFOSTS: RXIDLE Mask           */

#define UART_FIFOSTS_TXRXACT_Pos         (31)                                              /*!< UART_T::FIFOSTS: TXRXACT Position      */
#define UART_FIFOSTS_TXRXACT_Msk         (0x1ul << UART_FIFOSTS_TXRXACT_Pos)               /*!< UART_T::FIFOSTS: TXRXACT Mask          */

#define UART_INTSTS_RDAIF_Pos            (0)                                               /*!< UART_T::INTSTS: RDAIF Position         */
#define UART_INTSTS_RDAIF_Msk            (0x1ul << UART_INTSTS_RDAIF_Pos)                  /*!< UART_T::INTSTS: RDAIF Mask             */

#define UART_INTSTS_THREIF_Pos           (1)                                               /*!< UART_T::INTSTS: THREIF Position        */
#define UART_INTSTS_THREIF_Msk           (0x1ul << UART_INTSTS_THREIF_Pos)                 /*!< UART_T::INTSTS: THREIF Mask            */

#define UART_INTSTS_RLSIF_Pos            (2)                                               /*!< UART_T::INTSTS: RLSIF Position         */
#define UART_INTSTS_RLSIF_Msk            (0x1ul << UART_INTSTS_RLSIF_Pos)                  /*!< UART_T::INTSTS: RLSIF Mask             */

#define UART_INTSTS_MODEMIF_Pos          (3)                                               /*!< UART_T::INTSTS: MODEMIF Position       */
#define UART_INTSTS_MODEMIF_Msk          (0x1ul << UART_INTSTS_MODEMIF_Pos)                /*!< UART_T::INTSTS: MODEMIF Mask           */

#define UART_INTSTS_RXTOIF_Pos           (4)                                               /*!< UART_T::INTSTS: RXTOIF Position        */
#define UART_INTSTS_RXTOIF_Msk           (0x1ul << UART_INTSTS_RXTOIF_Pos)                 /*!< UART_T::INTSTS: RXTOIF Mask            */

#define UART_INTSTS_BUFERRIF_Pos         (5)                                               /*!< UART_T::INTSTS: BUFERRIF Position      */
#define UART_INTSTS_BUFERRIF_Msk         (0x1ul << UART_INTSTS_BUFERRIF_Pos)               /*!< UART_T::INTSTS: BUFERRIF Mask          */

#define UART_INTSTS_WKIF_Pos             (6)                                               /*!< UART_T::INTSTS: WKIF Position          */
#define UART_INTSTS_WKIF_Msk             (0x1ul << UART_INTSTS_WKIF_Pos)                   /*!< UART_T::INTSTS: WKIF Mask              */

#define UART_INTSTS_LINIF_Pos            (7)                                               /*!< UART_T::INTSTS: LINIF Position         */
#define UART_INTSTS_LINIF_Msk            (0x1ul << UART_INTSTS_LINIF_Pos)                  /*!< UART_T::INTSTS: LINIF Mask             */

#define UART_INTSTS_RDAINT_Pos           (8)                                               /*!< UART_T::INTSTS: RDAINT Position        */
#define UART_INTSTS_RDAINT_Msk           (0x1ul << UART_INTSTS_RDAINT_Pos)                 /*!< UART_T::INTSTS: RDAINT Mask            */

#define UART_INTSTS_THREINT_Pos          (9)                                               /*!< UART_T::INTSTS: THREINT Position       */
#define UART_INTSTS_THREINT_Msk          (0x1ul << UART_INTSTS_THREINT_Pos)                /*!< UART_T::INTSTS: THREINT Mask           */

#define UART_INTSTS_RLSINT_Pos           (10)                                              /*!< UART_T::INTSTS: RLSINT Position        */
#define UART_INTSTS_RLSINT_Msk           (0x1ul << UART_INTSTS_RLSINT_Pos)                 /*!< UART_T::INTSTS: RLSINT Mask            */

#define UART_INTSTS_MODEMINT_Pos         (11)                                              /*!< UART_T::INTSTS: MODEMINT Position      */
#define UART_INTSTS_MODEMINT_Msk         (0x1ul << UART_INTSTS_MODEMINT_Pos)               /*!< UART_T::INTSTS: MODEMINT Mask          */

#define UART_INTSTS_RXTOINT_Pos          (12)                                              /*!< UART_T::INTSTS: RXTOINT Position       */
#define UART_INTSTS_RXTOINT_Msk          (0x1ul << UART_INTSTS_RXTOINT_Pos)                /*!< UART_T::INTSTS: RXTOINT Mask           */

#define UART_INTSTS_BUFERRINT_Pos        (13)                                              /*!< UART_T::INTSTS: BUFERRINT Position     */
#define UART_INTSTS_BUFERRINT_Msk        (0x1ul << UART_INTSTS_BUFERRINT_Pos)              /*!< UART_T::INTSTS: BUFERRINT Mask         */

#define UART_INTSTS_WKINT_Pos            (14)                                              /*!< UART_T::INTSTS: WKINT Position         */
#define UART_INTSTS_WKINT_Msk            (0x1ul << UART_INTSTS_WKINT_Pos)                  /*!< UART_T::INTSTS: WKINT Mask             */

#define UART_INTSTS_LININT_Pos           (15)                                              /*!< UART_T::INTSTS: LININT Position        */
#define UART_INTSTS_LININT_Msk           (0x1ul << UART_INTSTS_LININT_Pos)                 /*!< UART_T::INTSTS: LININT Mask            */

#define UART_INTSTS_HWRLSIF_Pos          (18)                                              /*!< UART_T::INTSTS: HWRLSIF Position       */
#define UART_INTSTS_HWRLSIF_Msk          (0x1ul << UART_INTSTS_HWRLSIF_Pos)                /*!< UART_T::INTSTS: HWRLSIF Mask           */

#define UART_INTSTS_HWMODIF_Pos          (19)                                              /*!< UART_T::INTSTS: HWMODIF Position       */
#define UART_INTSTS_HWMODIF_Msk          (0x1ul << UART_INTSTS_HWMODIF_Pos)                /*!< UART_T::INTSTS: HWMODIF Mask           */

#define UART_INTSTS_HWTOIF_Pos           (20)                                              /*!< UART_T::INTSTS: HWTOIF Position        */
#define UART_INTSTS_HWTOIF_Msk           (0x1ul << UART_INTSTS_HWTOIF_Pos)                 /*!< UART_T::INTSTS: HWTOIF Mask            */

#define UART_INTSTS_HWBUFEIF_Pos         (21)                                              /*!< UART_T::INTSTS: HWBUFEIF Position      */
#define UART_INTSTS_HWBUFEIF_Msk         (0x1ul << UART_INTSTS_HWBUFEIF_Pos)               /*!< UART_T::INTSTS: HWBUFEIF Mask          */

#define UART_INTSTS_TXENDIF_Pos          (22)                                              /*!< UART_T::INTSTS: TXENDIF Position       */
#define UART_INTSTS_TXENDIF_Msk          (0x1ul << UART_INTSTS_TXENDIF_Pos)                /*!< UART_T::INTSTS: TXENDIF Mask           */

#define UART_INTSTS_HWRLSINT_Pos         (26)                                              /*!< UART_T::INTSTS: HWRLSINT Position      */
#define UART_INTSTS_HWRLSINT_Msk         (0x1ul << UART_INTSTS_HWRLSINT_Pos)               /*!< UART_T::INTSTS: HWRLSINT Mask          */

#define UART_INTSTS_HWMODINT_Pos         (27)                                              /*!< UART_T::INTSTS: HWMODINT Position      */
#define UART_INTSTS_HWMODINT_Msk         (0x1ul << UART_INTSTS_HWMODINT_Pos)               /*!< UART_T::INTSTS: HWMODINT Mask          */

#define UART_INTSTS_HWTOINT_Pos          (28)                                              /*!< UART_T::INTSTS: HWTOINT Position       */
#define UART_INTSTS_HWTOINT_Msk          (0x1ul << UART_INTSTS_HWTOINT_Pos)                /*!< UART_T::INTSTS: HWTOINT Mask           */

#define UART_INTSTS_HWBUFEINT_Pos        (29)                                              /*!< UART_T::INTSTS: HWBUFEINT Position     */
#define UART_INTSTS_HWBUFEINT_Msk        (0x1ul << UART_INTSTS_HWBUFEINT_Pos)              /*!< UART_T::INTSTS: HWBUFEINT Mask         */

#define UART_INTSTS_TXENDINT_Pos         (30)                                              /*!< UART_T::INTSTS: TXENDINT Position      */
#define UART_INTSTS_TXENDINT_Msk         (0x1ul << UART_INTSTS_TXENDINT_Pos)               /*!< UART_T::INTSTS: TXENDINT Mask          */

#define UART_INTSTS_ABRINT_Pos           (31)                                              /*!< UART_T::INTSTS: ABRINT Position        */
#define UART_INTSTS_ABRINT_Msk           (0x1ul << UART_INTSTS_ABRINT_Pos)                 /*!< UART_T::INTSTS: ABRINT Mask            */

#define UART_TOUT_TOIC_Pos               (0)                                               /*!< UART_T::TOUT: TOIC Position            */
#define UART_TOUT_TOIC_Msk               (0xfful << UART_TOUT_TOIC_Pos)                    /*!< UART_T::TOUT: TOIC Mask                */

#define UART_TOUT_DLY_Pos                (8)                                               /*!< UART_T::TOUT: DLY Position             */
#define UART_TOUT_DLY_Msk                (0xfful << UART_TOUT_DLY_Pos)                     /*!< UART_T::TOUT: DLY Mask                 */

#define UART_BAUD_BRD_Pos                (0)                                               /*!< UART_T::BAUD: BRD Position             */
#define UART_BAUD_BRD_Msk                (0xfffful << UART_BAUD_BRD_Pos)                   /*!< UART_T::BAUD: BRD Mask                 */

#define UART_BAUD_EDIVM1_Pos             (24)                                              /*!< UART_T::BAUD: EDIVM1 Position          */
#define UART_BAUD_EDIVM1_Msk             (0xful << UART_BAUD_EDIVM1_Pos)                   /*!< UART_T::BAUD: EDIVM1 Mask              */

#define UART_BAUD_BAUDM0_Pos             (28)                                              /*!< UART_T::BAUD: BAUDM0 Position          */
#define UART_BAUD_BAUDM0_Msk             (0x1ul << UART_BAUD_BAUDM0_Pos)                   /*!< UART_T::BAUD: BAUDM0 Mask              */

#define UART_BAUD_BAUDM1_Pos             (29)                                              /*!< UART_T::BAUD: BAUDM1 Position          */
#define UART_BAUD_BAUDM1_Msk             (0x1ul << UART_BAUD_BAUDM1_Pos)                   /*!< UART_T::BAUD: BAUDM1 Mask              */

#define UART_IRDA_TXEN_Pos               (1)                                               /*!< UART_T::IRDA: TXEN Position            */
#define UART_IRDA_TXEN_Msk               (0x1ul << UART_IRDA_TXEN_Pos)                     /*!< UART_T::IRDA: TXEN Mask                */

#define UART_IRDA_TXINV_Pos              (5)                                               /*!< UART_T::IRDA: TXINV Position           */
#define UART_IRDA_TXINV_Msk              (0x1ul << UART_IRDA_TXINV_Pos)                    /*!< UART_T::IRDA: TXINV Mask               */

#define UART_IRDA_RXINV_Pos              (6)                                               /*!< UART_T::IRDA: RXINV Position           */
#define UART_IRDA_RXINV_Msk              (0x1ul << UART_IRDA_RXINV_Pos)                    /*!< UART_T::IRDA: RXINV Mask               */

#define UART_ALTCTL_BRKFL_Pos            (0)                                               /*!< UART_T::ALTCTL: BRKFL Position         */
#define UART_ALTCTL_BRKFL_Msk            (0xful << UART_ALTCTL_BRKFL_Pos)                  /*!< UART_T::ALTCTL: BRKFL Mask             */

#define UART_ALTCTL_LINRXEN_Pos          (6)                                               /*!< UART_T::ALTCTL: LINRXEN Position       */
#define UART_ALTCTL_LINRXEN_Msk          (0x1ul << UART_ALTCTL_LINRXEN_Pos)                /*!< UART_T::ALTCTL: LINRXEN Mask           */

#define UART_ALTCTL_LINTXEN_Pos          (7)                                               /*!< UART_T::ALTCTL: LINTXEN Position       */
#define UART_ALTCTL_LINTXEN_Msk          (0x1ul << UART_ALTCTL_LINTXEN_Pos)                /*!< UART_T::ALTCTL: LINTXEN Mask           */

#define UART_ALTCTL_RS485NMM_Pos         (8)                                               /*!< UART_T::ALTCTL: RS485NMM Position      */
#define UART_ALTCTL_RS485NMM_Msk         (0x1ul << UART_ALTCTL_RS485NMM_Pos)               /*!< UART_T::ALTCTL: RS485NMM Mask          */

#define UART_ALTCTL_RS485AAD_Pos         (9)                                               /*!< UART_T::ALTCTL: RS485AAD Position      */
#define UART_ALTCTL_RS485AAD_Msk         (0x1ul << UART_ALTCTL_RS485AAD_Pos)               /*!< UART_T::ALTCTL: RS485AAD Mask          */

#define UART_ALTCTL_RS485AUD_Pos         (10)                                              /*!< UART_T::ALTCTL: RS485AUD Position      */
#define UART_ALTCTL_RS485AUD_Msk         (0x1ul << UART_ALTCTL_RS485AUD_Pos)               /*!< UART_T::ALTCTL: RS485AUD Mask          */

#define UART_ALTCTL_ADDRDEN_Pos          (15)                                              /*!< UART_T::ALTCTL: ADDRDEN Position       */
#define UART_ALTCTL_ADDRDEN_Msk          (0x1ul << UART_ALTCTL_ADDRDEN_Pos)                /*!< UART_T::ALTCTL: ADDRDEN Mask           */

#define UART_ALTCTL_ABRIF_Pos            (17)                                              /*!< UART_T::ALTCTL: ABRIF Position         */
#define UART_ALTCTL_ABRIF_Msk            (0x1ul << UART_ALTCTL_ABRIF_Pos)                  /*!< UART_T::ALTCTL: ABRIF Mask             */

#define UART_ALTCTL_ABRDEN_Pos           (18)                                              /*!< UART_T::ALTCTL: ABRDEN Position        */
#define UART_ALTCTL_ABRDEN_Msk           (0x1ul << UART_ALTCTL_ABRDEN_Pos)                 /*!< UART_T::ALTCTL: ABRDEN Mask            */

#define UART_ALTCTL_ABRDBITS_Pos         (19)                                              /*!< UART_T::ALTCTL: ABRDBITS Position      */
#define UART_ALTCTL_ABRDBITS_Msk         (0x3ul << UART_ALTCTL_ABRDBITS_Pos)               /*!< UART_T::ALTCTL: ABRDBITS Mask          */

#define UART_ALTCTL_ADDRMV_Pos           (24)                                              /*!< UART_T::ALTCTL: ADDRMV Position        */
#define UART_ALTCTL_ADDRMV_Msk           (0xfful << UART_ALTCTL_ADDRMV_Pos)                /*!< UART_T::ALTCTL: ADDRMV Mask            */

#define UART_FUNCSEL_FUNCSEL_Pos         (0)                                               /*!< UART_T::FUNCSEL: FUNCSEL Position      */
#define UART_FUNCSEL_FUNCSEL_Msk         (0x3ul << UART_FUNCSEL_FUNCSEL_Pos)               /*!< UART_T::FUNCSEL: FUNCSEL Mask          */

#define UART_FUNCSEL_TXRXDIS_Pos         (3)                                               /*!< UART_T::FUNCSEL: TXRXDIS Position      */
#define UART_FUNCSEL_TXRXDIS_Msk         (0x1ul << UART_FUNCSEL_TXRXDIS_Pos)               /*!< UART_T::FUNCSEL: TXRXDIS Mask          */

#define UART_LINCTL_SLVEN_Pos            (0)                                               /*!< UART_T::LINCTL: SLVEN Position         */
#define UART_LINCTL_SLVEN_Msk            (0x1ul << UART_LINCTL_SLVEN_Pos)                  /*!< UART_T::LINCTL: SLVEN Mask             */

#define UART_LINCTL_SLVHDEN_Pos          (1)                                               /*!< UART_T::LINCTL: SLVHDEN Position       */
#define UART_LINCTL_SLVHDEN_Msk          (0x1ul << UART_LINCTL_SLVHDEN_Pos)                /*!< UART_T::LINCTL: SLVHDEN Mask           */

#define UART_LINCTL_SLVAREN_Pos          (2)                                               /*!< UART_T::LINCTL: SLVAREN Position       */
#define UART_LINCTL_SLVAREN_Msk          (0x1ul << UART_LINCTL_SLVAREN_Pos)                /*!< UART_T::LINCTL: SLVAREN Mask           */

#define UART_LINCTL_SLVDUEN_Pos          (3)                                               /*!< UART_T::LINCTL: SLVDUEN Position       */
#define UART_LINCTL_SLVDUEN_Msk          (0x1ul << UART_LINCTL_SLVDUEN_Pos)                /*!< UART_T::LINCTL: SLVDUEN Mask           */

#define UART_LINCTL_MUTE_Pos             (4)                                               /*!< UART_T::LINCTL: MUTE Position          */
#define UART_LINCTL_MUTE_Msk             (0x1ul << UART_LINCTL_MUTE_Pos)                   /*!< UART_T::LINCTL: MUTE Mask              */

#define UART_LINCTL_SENDH_Pos            (8)                                               /*!< UART_T::LINCTL: SENDH Position         */
#define UART_LINCTL_SENDH_Msk            (0x1ul << UART_LINCTL_SENDH_Pos)                  /*!< UART_T::LINCTL: SENDH Mask             */

#define UART_LINCTL_IDPEN_Pos            (9)                                               /*!< UART_T::LINCTL: IDPEN Position         */
#define UART_LINCTL_IDPEN_Msk            (0x1ul << UART_LINCTL_IDPEN_Pos)                  /*!< UART_T::LINCTL: IDPEN Mask             */

#define UART_LINCTL_BRKDETEN_Pos         (10)                                              /*!< UART_T::LINCTL: BRKDETEN Position      */
#define UART_LINCTL_BRKDETEN_Msk         (0x1ul << UART_LINCTL_BRKDETEN_Pos)               /*!< UART_T::LINCTL: BRKDETEN Mask          */

#define UART_LINCTL_LINRXOFF_Pos         (11)                                              /*!< UART_T::LINCTL: LINRXOFF Position      */
#define UART_LINCTL_LINRXOFF_Msk         (0x1ul << UART_LINCTL_LINRXOFF_Pos)               /*!< UART_T::LINCTL: LINRXOFF Mask          */

#define UART_LINCTL_BITERREN_Pos         (12)                                              /*!< UART_T::LINCTL: BITERREN Position      */
#define UART_LINCTL_BITERREN_Msk         (0x1ul << UART_LINCTL_BITERREN_Pos)               /*!< UART_T::LINCTL: BITERREN Mask          */

#define UART_LINCTL_BRKFL_Pos            (16)                                              /*!< UART_T::LINCTL: BRKFL Position         */
#define UART_LINCTL_BRKFL_Msk            (0xful << UART_LINCTL_BRKFL_Pos)                  /*!< UART_T::LINCTL: BRKFL Mask             */

#define UART_LINCTL_BSL_Pos              (20)                                              /*!< UART_T::LINCTL: BSL Position           */
#define UART_LINCTL_BSL_Msk              (0x3ul << UART_LINCTL_BSL_Pos)                    /*!< UART_T::LINCTL: BSL Mask               */

#define UART_LINCTL_HSEL_Pos             (22)                                              /*!< UART_T::LINCTL: HSEL Position          */
#define UART_LINCTL_HSEL_Msk             (0x3ul << UART_LINCTL_HSEL_Pos)                   /*!< UART_T::LINCTL: HSEL Mask              */

#define UART_LINCTL_PID_Pos              (24)                                              /*!< UART_T::LINCTL: PID Position           */
#define UART_LINCTL_PID_Msk              (0xfful << UART_LINCTL_PID_Pos)                   /*!< UART_T::LINCTL: PID Mask               */

#define UART_LINSTS_SLVHDETF_Pos         (0)                                               /*!< UART_T::LINSTS: SLVHDETF Position      */
#define UART_LINSTS_SLVHDETF_Msk         (0x1ul << UART_LINSTS_SLVHDETF_Pos)               /*!< UART_T::LINSTS: SLVHDETF Mask          */

#define UART_LINSTS_SLVHEF_Pos           (1)                                               /*!< UART_T::LINSTS: SLVHEF Position        */
#define UART_LINSTS_SLVHEF_Msk           (0x1ul << UART_LINSTS_SLVHEF_Pos)                 /*!< UART_T::LINSTS: SLVHEF Mask            */

#define UART_LINSTS_SLVIDPEF_Pos         (2)                                               /*!< UART_T::LINSTS: SLVIDPEF Position      */
#define UART_LINSTS_SLVIDPEF_Msk         (0x1ul << UART_LINSTS_SLVIDPEF_Pos)               /*!< UART_T::LINSTS: SLVIDPEF Mask          */

#define UART_LINSTS_SLVSYNCF_Pos         (3)                                               /*!< UART_T::LINSTS: SLVSYNCF Position      */
#define UART_LINSTS_SLVSYNCF_Msk         (0x1ul << UART_LINSTS_SLVSYNCF_Pos)               /*!< UART_T::LINSTS: SLVSYNCF Mask          */

#define UART_LINSTS_BRKDETF_Pos          (8)                                               /*!< UART_T::LINSTS: BRKDETF Position       */
#define UART_LINSTS_BRKDETF_Msk          (0x1ul << UART_LINSTS_BRKDETF_Pos)                /*!< UART_T::LINSTS: BRKDETF Mask           */

#define UART_LINSTS_BITEF_Pos            (9)                                               /*!< UART_T::LINSTS: BITEF Position         */
#define UART_LINSTS_BITEF_Msk            (0x1ul << UART_LINSTS_BITEF_Pos)                  /*!< UART_T::LINSTS: BITEF Mask             */

#define UART_BRCOMP_BRCOMP_Pos           (0)                                               /*!< UART_T::BRCOMP: BRCOMP Position        */
#define UART_BRCOMP_BRCOMP_Msk           (0x1fful << UART_BRCOMP_BRCOMP_Pos)               /*!< UART_T::BRCOMP: BRCOMP Mask            */

#define UART_BRCOMP_BRCOMPDEC_Pos        (31)                                              /*!< UART_T::BRCOMP: BRCOMPDEC Position     */
#define UART_BRCOMP_BRCOMPDEC_Msk        (0x1ul << UART_BRCOMP_BRCOMPDEC_Pos)              /*!< UART_T::BRCOMP: BRCOMPDEC Mask         */

#define UART_WKCTL_WKCTSEN_Pos           (0)                                               /*!< UART_T::WKCTL: WKCTSEN Position        */
#define UART_WKCTL_WKCTSEN_Msk           (0x1ul << UART_WKCTL_WKCTSEN_Pos)                 /*!< UART_T::WKCTL: WKCTSEN Mask            */

#define UART_WKCTL_WKDATEN_Pos           (1)                                               /*!< UART_T::WKCTL: WKDATEN Position        */
#define UART_WKCTL_WKDATEN_Msk           (0x1ul << UART_WKCTL_WKDATEN_Pos)                 /*!< UART_T::WKCTL: WKDATEN Mask            */

#define UART_WKCTL_WKRFRTEN_Pos          (2)                                               /*!< UART_T::WKCTL: WKRFRTEN Position       */
#define UART_WKCTL_WKRFRTEN_Msk          (0x1ul << UART_WKCTL_WKRFRTEN_Pos)                /*!< UART_T::WKCTL: WKRFRTEN Mask           */

#define UART_WKCTL_WKRS485EN_Pos         (3)                                               /*!< UART_T::WKCTL: WKRS485EN Position      */
#define UART_WKCTL_WKRS485EN_Msk         (0x1ul << UART_WKCTL_WKRS485EN_Pos)               /*!< UART_T::WKCTL: WKRS485EN Mask          */

#define UART_WKCTL_WKTOUTEN_Pos          (4)                                               /*!< UART_T::WKCTL: WKTOUTEN Position       */
#define UART_WKCTL_WKTOUTEN_Msk          (0x1ul << UART_WKCTL_WKTOUTEN_Pos)                /*!< UART_T::WKCTL: WKTOUTEN Mask           */

#define UART_WKSTS_CTSWKF_Pos            (0)                                               /*!< UART_T::WKSTS: CTSWKF Position         */
#define UART_WKSTS_CTSWKF_Msk            (0x1ul << UART_WKSTS_CTSWKF_Pos)                  /*!< UART_T::WKSTS: CTSWKF Mask             */

#define UART_WKSTS_DATWKF_Pos            (1)                                               /*!< UART_T::WKSTS: DATWKF Position         */
#define UART_WKSTS_DATWKF_Msk            (0x1ul << UART_WKSTS_DATWKF_Pos)                  /*!< UART_T::WKSTS: DATWKF Mask             */

#define UART_WKSTS_RFRTWKF_Pos           (2)                                               /*!< UART_T::WKSTS: RFRTWKF Position        */
#define UART_WKSTS_RFRTWKF_Msk           (0x1ul << UART_WKSTS_RFRTWKF_Pos)                 /*!< UART_T::WKSTS: RFRTWKF Mask            */

#define UART_WKSTS_RS485WKF_Pos          (3)                                               /*!< UART_T::WKSTS: RS485WKF Position       */
#define UART_WKSTS_RS485WKF_Msk          (0x1ul << UART_WKSTS_RS485WKF_Pos)                /*!< UART_T::WKSTS: RS485WKF Mask           */

#define UART_WKSTS_TOUTWKF_Pos           (4)                                               /*!< UART_T::WKSTS: TOUTWKF Position        */
#define UART_WKSTS_TOUTWKF_Msk           (0x1ul << UART_WKSTS_TOUTWKF_Pos)                 /*!< UART_T::WKSTS: TOUTWKF Mask            */

#define UART_DWKCOMP_STCOMP_Pos          (0)                                               /*!< UART_T::DWKCOMP: STCOMP Position       */
#define UART_DWKCOMP_STCOMP_Msk          (0xfffful << UART_DWKCOMP_STCOMP_Pos)             /*!< UART_T::DWKCOMP: STCOMP Mask           */

/**@}*/ /* UART_CONST */
/**@}*/ /* end of UART register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __UART_REG_H__ */
