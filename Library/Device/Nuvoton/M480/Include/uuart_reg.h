/**************************************************************************//**
 * @file     uuart_reg.h
 * @version  V1.00
 * @brief    UUART register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __UUART_REG_H__
#define __UUART_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup UUART UART Mode of USCI Controller(UUART)
    Memory Mapped Structure for UUART Controller
@{ */

typedef struct
{


    /**
@var UUART_T::CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL
</font><br><p> <font size="2">
Offset: 0x00  USCI Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2:0]</td><td>FUNMODE</td><td><div style="word-wrap: break-word;"><b>Function Mode
</b><br>
This bit field selects the protocol for this USCI controller
<br>
Selecting a protocol that is not available or a reserved combination disables the USCI
<br>
When switching between two protocols, the USCI has to be disabled before selecting a new protocol
<br>
Simultaneously, the USCI will be reset when user write 000 to FUNMODE.
<br>
000 = The USCI is disabled. All protocol related state machines are set to idle state.
<br>
001 = The SPI protocol is selected.
<br>
010 = The UART protocol is selected.
<br>
100 = The I2C protocol is selected.
<br>
Note: Other bit combinations are reserved.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UUART_T::INTEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTEN
</font><br><p> <font size="2">
Offset: 0x04  USCI Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1]</td><td>TXSTIEN</td><td><div style="word-wrap: break-word;"><b>Transmit Start Interrupt Enable Bit
</b><br>
This bit enables the interrupt generation in case of a transmit start event.
<br>
0 = The transmit start interrupt is disabled.
<br>
1 = The transmit start interrupt is enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>TXENDIEN</td><td><div style="word-wrap: break-word;"><b>Transmit End Interrupt Enable Bit
</b><br>
This bit enables the interrupt generation in case of a transmit finish event.
<br>
0 = The transmit finish interrupt is disabled.
<br>
1 = The transmit finish interrupt is enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>RXSTIEN</td><td><div style="word-wrap: break-word;"><b>Receive Start Interrupt Enable BIt
</b><br>
This bit enables the interrupt generation in case of a receive start event.
<br>
0 = The receive start interrupt is disabled.
<br>
1 = The receive start interrupt is enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>RXENDIEN</td><td><div style="word-wrap: break-word;"><b>Receive End Interrupt Enable Bit
</b><br>
This bit enables the interrupt generation in case of a receive finish event.
<br>
0 = The receive end interrupt is disabled.
<br>
1 = The receive end interrupt is enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UUART_T::BRGEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BRGEN
</font><br><p> <font size="2">
Offset: 0x08  USCI Baud Rate Generator Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>RCLKSEL</td><td><div style="word-wrap: break-word;"><b>Reference Clock Source Selection
</b><br>
This bit selects the source signal of reference clock (fREF_CLK).
<br>
0 = Peripheral device clock fPCLK.
<br>
1 = Reserved.
<br>
</div></td></tr><tr><td>
[1]</td><td>PTCLKSEL</td><td><div style="word-wrap: break-word;"><b>Protocol Clock Source Selection
</b><br>
This bit selects the source signal of protocol clock (fPROT_CLK).
<br>
0 = Reference clock fREF_CLK.
<br>
1 = fREF_CLK2 (its frequency is half of fREF_CLK).
<br>
</div></td></tr><tr><td>
[3:2]</td><td>SPCLKSEL</td><td><div style="word-wrap: break-word;"><b>Sample Clock Source Selection
</b><br>
This bit field used for the clock source selection of a sample clock (fSAMP_CLK) for the protocol processor.
<br>
00 = fSAMP_CLK = fDIV_CLK.
<br>
01 = fSAMP_CLK = fPROT_CLK.
<br>
10 = fSAMP_CLK = fSCLK.
<br>
11 = fSAMP_CLK = fREF_CLK.
<br>
</div></td></tr><tr><td>
[4]</td><td>TMCNTEN</td><td><div style="word-wrap: break-word;"><b>Timing Measurement Counter Enable Bit
</b><br>
This bit enables the 10-bit timing measurement counter.
<br>
0 = Timing measurement counter is Disabled.
<br>
1 = Timing measurement counter is Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>TMCNTSRC</td><td><div style="word-wrap: break-word;"><b>Timing Measurement Counter Clock Source Selection
</b><br>
0 = Timing measurement counter with fPROT_CLK.
<br>
1 = Timing measurement counter with fDIV_CLK.
<br>
</div></td></tr><tr><td>
[9:8]</td><td>PDSCNT</td><td><div style="word-wrap: break-word;"><b>Pre-divider for Sample Counter
</b><br>
This bit field defines the divide ratio of the clock division from sample clock fSAMP_CLK
<br>
The divided frequency fPDS_CNT = fSAMP_CLK / (PDSCNT+1).
<br>
</div></td></tr><tr><td>
[14:10]</td><td>DSCNT</td><td><div style="word-wrap: break-word;"><b>Denominator for Sample Counter
</b><br>
This bit field defines the divide ratio of the sample clock fSAMP_CLK.
<br>
The divided frequency fDS_CNT = fPDS_CNT / (DSCNT+1).
<br>
Note: The maximum value of DSCNT is 0xF on UART mode and suggest to set over 4 to confirm the receiver data is sampled in right value
<br>
</div></td></tr><tr><td>
[25:16]</td><td>CLKDIV</td><td><div style="word-wrap: break-word;"><b>Clock Divider
</b><br>
This bit field defines the ratio between the protocol clock frequency fPROT_CLK and
<br>
the clock divider frequency fDIV_CLK (fDIV_CLK = fPROT_CLK / (CLKDIV+1) ).
<br>
Note: In UART function, it can be updated by hardware in the 4th falling edge of the input data 0x55
<br>
when the auto baud rate function (ABREN(USCI_PROTCTL[6])) is enabled
<br>
The revised value is the average bit time between bit 5 and bit 6
<br>
The user can use revised CLKDIV and new BRDETITV (USCI_PROTCTL[24:16]) to calculate the precise baud rate.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UUART_T::DATIN0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DATIN0
</font><br><p> <font size="2">
Offset: 0x10  USCI Input Data Signal Configuration Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SYNCSEL</td><td><div style="word-wrap: break-word;"><b>Input Signal Synchronization Selection
</b><br>
This bit selects if the un-synchronized input signal (with optionally inverted) or
<br>
the synchronized (and optionally filtered) signal can be used as input for the   data shift unit.
<br>
0 = The un-synchronized signal can be taken as input for the data shift unit.
<br>
1 = The synchronized signal can be taken as input for the data shift unit.
<br>
</div></td></tr><tr><td>
[2]</td><td>ININV</td><td><div style="word-wrap: break-word;"><b>Input Signal Inverse Selection
</b><br>
This bit defines the inverter enable of the input asynchronous signal.
<br>
0 = The un-synchronized input signal will not be inverted.
<br>
1 = The un-synchronized input signal will be inverted.
<br>
</div></td></tr><tr><td>
[4:3]</td><td>EDGEDET</td><td><div style="word-wrap: break-word;"><b>Input Signal   Edge Detection Mode
</b><br>
This bit field selects which edge actives the trigger event of input data signal.
<br>
00 = The trigger event activation is disabled.
<br>
01 = A rising   edge activates the trigger event of input data signal.
<br>
10 = A falling edge activates the trigger event of input data signal.
<br>
11 = Both edges activate the trigger event of input data signal.
<br>
Note: In UART function mode, it is suggested to   set this bit field as 10.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UUART_T::CTLIN0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTLIN0
</font><br><p> <font size="2">
Offset: 0x20  USCI Input Control Signal Configuration Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SYNCSEL</td><td><div style="word-wrap: break-word;"><b>Input Synchronization Signal Selection
</b><br>
This bit selects if the un-synchronized input signal (with optionally inverted) or
<br>
the synchronized (and optionally filtered) signal can be used as input for the   data shift unit.
<br>
0 = The un-synchronized signal can be taken as input for the data shift unit.
<br>
1 = The   synchronized signal can be taken as input for the data shift unit.
<br>
</div></td></tr><tr><td>
[2]</td><td>ININV</td><td><div style="word-wrap: break-word;"><b>Input Signal Inverse Selection
</b><br>
This bit defines the inverter enable of the input asynchronous signal.
<br>
0 = The un-synchronized input signal will not be inverted.
<br>
1 = The un-synchronized input signal will be inverted.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UUART_T::CLKIN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKIN
</font><br><p> <font size="2">
Offset: 0x28  USCI Input Clock Signal Configuration Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SYNCSEL</td><td><div style="word-wrap: break-word;"><b>Input Synchronization Signal Selection
</b><br>
This bit selects if the un-synchronized input signal or
<br>
the synchronized (and optionally filtered) signal can be used as input for the data shift unit.
<br>
0 = The un-synchronized signal can be taken as input for the data shift unit.
<br>
1 = The synchronized signal can be taken as input for the data shift unit.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UUART_T::LINECTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">LINECTL
</font><br><p> <font size="2">
Offset: 0x2C  USCI Line Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>LSB</td><td><div style="word-wrap: break-word;"><b>LSB First Transmission Selection
</b><br>
0 = The MSB, which bit of transmit/receive data buffer depends on the setting of DWIDTH, is transmitted/received first.
<br>
1 = The LSB, the bit 0 of data buffer, will be transmitted/received first.
<br>
</div></td></tr><tr><td>
[5]</td><td>DATOINV</td><td><div style="word-wrap: break-word;"><b>Data Output Inverse Selection
</b><br>
This bit defines the relation between the internal shift data value and the output data signal of USCIx_DAT1 pin.
<br>
0 = The value of USCIx_DAT1 is equal to the data shift register.
<br>
1 = The value of USCIx_DAT1 is the inversion of data shift register.
<br>
</div></td></tr><tr><td>
[7]</td><td>CTLOINV</td><td><div style="word-wrap: break-word;"><b>Control Signal Output Inverse Selection
</b><br>
This bit defines the relation between the internal control signal and the output control signal.
<br>
0 = No effect.
<br>
1 = The control signal will be inverted before its output.
<br>
Note: In UART protocol, the control signal means nRTS signal.
<br>
</div></td></tr><tr><td>
[11:8]</td><td>DWIDTH</td><td><div style="word-wrap: break-word;"><b>Word Length of Transmission
</b><br>
This bit field defines the data word length (amount of bits) for reception and transmission
<br>
The data word is always right-aligned in the data buffer
<br>
USCI support word length from 4 to 16 bits.
<br>
0x0: The data word contains 16 bits located at bit positions [15:0].
<br>
0x1: Reserved.
<br>
0x2: Reserved.
<br>
0x3: Reserved.
<br>
0x4: The data word contains 4 bits located at bit positions [3:0].
<br>
0x5: The data word contains 5 bits located at bit positions [4:0].
<br>
..
<br>
0xF: The data word contains 15 bits located at bit positions [14:0].
<br>
Note: In UART protocol, the length can be configured as 6~13 bits.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UUART_T::TXDAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TXDAT
</font><br><p> <font size="2">
Offset: 0x30  USCI Transmit Data Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>TXDAT</td><td><div style="word-wrap: break-word;"><b>Transmit Data
</b><br>
Software can use this bit field to write 16-bit transmit data for transmission.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UUART_T::RXDAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">RXDAT
</font><br><p> <font size="2">
Offset: 0x34  USCI Receive Data Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>RXDAT</td><td><div style="word-wrap: break-word;"><b>Received Data
</b><br>
This bit field monitors the received data which stored in receive data buffer.
<br>
Note: RXDAT[15:13] indicate the same frame status of BREAK, FRMERR and PARITYERR (USCI_PROTSTS[7:5]).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UUART_T::BUFCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BUFCTL
</font><br><p> <font size="2">
Offset: 0x38  USCI Transmit/Receive Buffer Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7]</td><td>TXCLR</td><td><div style="word-wrap: break-word;"><b>Clear Transmit Buffer
</b><br>
0 = No effect.
<br>
1 = The transmit buffer is cleared (filling level is cleared and output pointer is set to input pointer value)
<br>
Should only be used while the buffer is not taking part in data traffic.
<br>
Note: It is cleared automatically after one PCLK cycle.
<br>
</div></td></tr><tr><td>
[14]</td><td>RXOVIEN</td><td><div style="word-wrap: break-word;"><b>Receive Buffer Overrun Error Interrupt Enable Control
</b><br>
0 = Receive overrun interrupt Disabled.
<br>
1 = Receive overrun interrupt Enabled.
<br>
</div></td></tr><tr><td>
[15]</td><td>RXCLR</td><td><div style="word-wrap: break-word;"><b>Clear Receive Buffer
</b><br>
0 = No effect.
<br>
1 = The receive buffer is cleared (filling level is cleared and output pointer is set to input pointer value)
<br>
Should only be used while the buffer is not taking part in data traffic.
<br>
Note: It is cleared automatically after one PCLK cycle.
<br>
</div></td></tr><tr><td>
[16]</td><td>TXRST</td><td><div style="word-wrap: break-word;"><b>Transmit Reset
</b><br>
0 = No effect.
<br>
1 = Reset the transmit-related counters, state machine, and the content of transmit shift register and data buffer.
<br>
Note: It is cleared automatically after one PCLK cycle.
<br>
</div></td></tr><tr><td>
[17]</td><td>RXRST</td><td><div style="word-wrap: break-word;"><b>Receive Reset
</b><br>
0 = No effect.
<br>
1 = Reset the receive-related counters, state machine, and the content of receive shift register and data buffer.
<br>
Note 1: It is cleared automatically after one PCLK cycle.
<br>
Note 2: It is suggest to check the RXBUSY (USCI_PROTSTS[10]) before this bit will be set to 1.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UUART_T::BUFSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BUFSTS
</font><br><p> <font size="2">
Offset: 0x3C  USCI Transmit/Receive Buffer Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>RXEMPTY</td><td><div style="word-wrap: break-word;"><b>Receive Buffer Empty Indicator
</b><br>
0 = Receive buffer is not empty.
<br>
1 = Receive buffer is empty.
<br>
</div></td></tr><tr><td>
[1]</td><td>RXFULL</td><td><div style="word-wrap: break-word;"><b>Receive Buffer Full Indicator
</b><br>
0 = Receive buffer is not full.
<br>
1 = Receive buffer is full.
<br>
</div></td></tr><tr><td>
[3]</td><td>RXOVIF</td><td><div style="word-wrap: break-word;"><b>Receive Buffer Over-run Error Interrupt Status
</b><br>
This bit indicates that a receive buffer overrun error event has been detected
<br>
If RXOVIEN (USCI_BUFCTL[14]) is enabled, the corresponding interrupt request is activated
<br>
It is cleared by software writes 1 to this bit.
<br>
0 = A receive buffer overrun error event has not been detected.
<br>
1 = A receive buffer overrun error event has been detected.
<br>
</div></td></tr><tr><td>
[8]</td><td>TXEMPTY</td><td><div style="word-wrap: break-word;"><b>Transmit Buffer Empty Indicator
</b><br>
0 = Transmit buffer is not empty.
<br>
1 = Transmit buffer is empty.
<br>
</div></td></tr><tr><td>
[9]</td><td>TXFULL</td><td><div style="word-wrap: break-word;"><b>Transmit Buffer Full Indicator
</b><br>
0 = Transmit buffer is not full.
<br>
1 = Transmit buffer is full.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UUART_T::PDMACTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PDMACTL
</font><br><p> <font size="2">
Offset: 0x40  USCI PDMA Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>PDMARST</td><td><div style="word-wrap: break-word;"><b>PDMA Reset
</b><br>
0 = No effect.
<br>
1 = Reset the USCI's PDMA control logic. This bit will be cleared to 0 automatically.
<br>
</div></td></tr><tr><td>
[1]</td><td>TXPDMAEN</td><td><div style="word-wrap: break-word;"><b>PDMA Transmit Channel Available
</b><br>
0 = Transmit PDMA function Disabled.
<br>
1 = Transmit PDMA function Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>RXPDMAEN</td><td><div style="word-wrap: break-word;"><b>PDMA Receive Channel Available
</b><br>
0 = Receive PDMA function Disabled.
<br>
1 = Receive PDMA function Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>PDMAEN</td><td><div style="word-wrap: break-word;"><b>PDMA Mode Enable Bit
</b><br>
0 = PDMA function Disabled.
<br>
1 = PDMA function Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UUART_T::WKCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">WKCTL
</font><br><p> <font size="2">
Offset: 0x54  USCI Wake-up Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>WKEN</td><td><div style="word-wrap: break-word;"><b>Wake-up Enable Bit
</b><br>
0 = Wake-up function Disabled.
<br>
1 = Wake-up function Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>PDBOPT</td><td><div style="word-wrap: break-word;"><b>Power Down Blocking Option
</b><br>
0 = If user attempts to enter Power-down mode by executing WFI while the protocol is in transferring, MCU will stop the transfer and enter Power-down mode immediately.
<br>
1 = If user attempts to enter Power-down mode by executing WFI while the protocol is in transferring, the on-going transfer will not be stopped and MCU will enter idle mode immediately.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UUART_T::WKSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">WKSTS
</font><br><p> <font size="2">
Offset: 0x58  USCI Wake-up Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>WKF</td><td><div style="word-wrap: break-word;"><b>Wake-up Flag
</b><br>
When chip is woken up from Power-down mode, this bit is set to 1
<br>
Software can write 1 to clear this bit.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UUART_T::PROTCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PROTCTL
</font><br><p> <font size="2">
Offset: 0x5C  USCI Protocol Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>STOPB</td><td><div style="word-wrap: break-word;"><b>Stop Bits
</b><br>
This bit defines the number of stop bits in an UART frame.
<br>
0 = The number of stop bits is 1.
<br>
1 = The number of stop bits is 2.
<br>
</div></td></tr><tr><td>
[1]</td><td>PARITYEN</td><td><div style="word-wrap: break-word;"><b>Parity Enable Bit
</b><br>
This bit defines the parity bit is enabled in an UART frame.
<br>
0 = The parity bit Disabled.
<br>
1 = The parity bit Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>EVENPARITY</td><td><div style="word-wrap: break-word;"><b>Even Parity Enable Bit
</b><br>
0 = Odd number of logic 1's is transmitted and checked in each word.
<br>
1 = Even number of logic 1's is transmitted and checked in each word.
<br>
Note: This bit has effect only when PARITYEN is set.
<br>
</div></td></tr><tr><td>
[3]</td><td>RTSAUTOEN</td><td><div style="word-wrap: break-word;"><b>nRTS Auto-flow Control Enable Bit
</b><br>
When nRTS auto-flow is enabled, if the receiver buffer is full (RXFULL (USCI_BUFSTS[1] = 1'b1)), the UART will de-assert nRTS signal.
<br>
0 = nRTS auto-flow control Disabled.
<br>
1 = nRTS auto-flow control Enabled.
<br>
Note: This bit has effect only when the RTSAUDIREN is not set.
<br>
</div></td></tr><tr><td>
[4]</td><td>CTSAUTOEN</td><td><div style="word-wrap: break-word;"><b>nCTS Auto-flow Control Enable Bit
</b><br>
When nCTS auto-flow is enabled, the UART will send data to external device when nCTS input assert (UART will not send data to device if nCTS input is dis-asserted).
<br>
0 = nCTS auto-flow control Disabled.
<br>
1 = nCTS auto-flow control Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>RTSAUDIREN</td><td><div style="word-wrap: break-word;"><b>nRTS Auto Direction Enable Bit
</b><br>
When nRTS auto direction is enabled, if the transmitted bytes in the TX buffer is empty, the UART asserted nRTS signal automatically.
<br>
0 = nRTS auto direction control Disabled.
<br>
1 = nRTS auto direction control Enabled.
<br>
Note 1: This bit is used for nRTS auto direction control for RS485.
<br>
Note 2: This bit has effect only when the RTSAUTOEN is not set.
<br>
</div></td></tr><tr><td>
[6]</td><td>ABREN</td><td><div style="word-wrap: break-word;"><b>Auto-baud Rate Detect Enable Bit
</b><br>
0 = Auto-baud rate detect function Disabled.
<br>
1 = Auto-baud rate detect function Enabled.
<br>
Note: When the auto - baud rate detect operation finishes, hardware will clear this bit
<br>
The associated interrupt ABRDETIF (USCI_PROTST[9]) will be generated (If ARBIEN (USCI_PROTIEN [1]) is enabled).
<br>
</div></td></tr><tr><td>
[9]</td><td>DATWKEN</td><td><div style="word-wrap: break-word;"><b>Data Wake-up Mode Enable Bit
</b><br>
0 = Data wake-up mode Disabled.
<br>
1 = Data wake-up mode Enabled.
<br>
</div></td></tr><tr><td>
[10]</td><td>CTSWKEN</td><td><div style="word-wrap: break-word;"><b>nCTS Wake-up Mode Enable Bit
</b><br>
0 = nCTS wake-up mode Disabled.
<br>
1 = nCTS wake-up mode Enabled.
<br>
</div></td></tr><tr><td>
[14:11]</td><td>WAKECNT</td><td><div style="word-wrap: break-word;"><b>Wake-up Counter
</b><br>
These bits field indicate how many clock cycle selected by fPDS_CNT do the slave can get the 1st bit (start bit) when the device is wake-up from Power-down mode.
<br>
</div></td></tr><tr><td>
[24:16]</td><td>BRDETITV</td><td><div style="word-wrap: break-word;"><b>Baud Rate Detection Interval
</b><br>
This bit fields indicate how many clock cycle selected by TMCNTSRC (USCI_BRGEN [5]) does the slave calculates the baud rate in one bits
<br>
The order of the bus shall be 1 and 0 step by step (e.g. the input data pattern shall be 0x55)
<br>
The user can read the value to know the current input baud rate of the bus whenever the ABRDETIF (USCI_PROTCTL[9]) is set.
<br>
Note: This bit can be cleared to 0 by software writing '0' to the BRDETITV.
<br>
</div></td></tr><tr><td>
[26]</td><td>STICKEN</td><td><div style="word-wrap: break-word;"><b>Stick Parity Enable Bit
</b><br>
0 = Stick parity Disabled.
<br>
1 = Stick parity Enabled.
<br>
Note: Refer to RS-485 Support section for detail information.
<br>
</div></td></tr><tr><td>
[29]</td><td>BCEN</td><td><div style="word-wrap: break-word;"><b>Transmit Break Control Enable Bit
</b><br>
0 = Transmit Break Control Disabled.
<br>
1 = Transmit Break Control Enabled.
<br>
Note: When this bit is set to logic 1, the serial data output (TX) is forced to the Spacing State (logic 0)
<br>
This bit acts only on TX line and has no effect on the transmitter logic.
<br>
</div></td></tr><tr><td>
[31]</td><td>PROTEN</td><td><div style="word-wrap: break-word;"><b>UART Protocol Enable Bit
</b><br>
0 = UART Protocol Disabled.
<br>
1 = UART Protocol Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UUART_T::PROTIEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PROTIEN
</font><br><p> <font size="2">
Offset: 0x60  USCI Protocol Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1]</td><td>ABRIEN</td><td><div style="word-wrap: break-word;"><b>Auto-baud Rate Interrupt Enable Bit
</b><br>
0 = Auto-baud rate interrupt Disabled.
<br>
1 = Auto-baud rate interrupt Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>RLSIEN</td><td><div style="word-wrap: break-word;"><b>Receive Line Status Interrupt Enable Bit
</b><br>
0 = Receive line status interrupt Disabled.
<br>
1 = Receive line status interrupt Enabled.
<br>
Note: USCI_PROTSTS[7:5] indicates the current interrupt event for receive line status interrupt.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UUART_T::PROTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PROTSTS
</font><br><p> <font size="2">
Offset: 0x64  USCI Protocol Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1]</td><td>TXSTIF</td><td><div style="word-wrap: break-word;"><b>Transmit Start Interrupt Flag
</b><br>
0 = A transmit start interrupt status has not occurred.
<br>
1 = A transmit start interrupt status has occurred.
<br>
Note 1: It is cleared by software writing one into this bit.
<br>
Note 2: Used for user to load next transmit data when there is no data in transmit buffer.
<br>
</div></td></tr><tr><td>
[2]</td><td>TXENDIF</td><td><div style="word-wrap: break-word;"><b>Transmit End Interrupt Flag
</b><br>
0 = A transmit end interrupt status has not occurred.
<br>
1 = A transmit end interrupt status has occurred.
<br>
Note: It is cleared by software writing one into this bit.
<br>
</div></td></tr><tr><td>
[3]</td><td>RXSTIF</td><td><div style="word-wrap: break-word;"><b>Receive Start Interrupt Flag
</b><br>
0 = A receive start interrupt status has not occurred.
<br>
1 = A receive start interrupt status has occurred.
<br>
Note: It is cleared by software writing one into this bit.
<br>
</div></td></tr><tr><td>
[4]</td><td>RXENDIF</td><td><div style="word-wrap: break-word;"><b>Receive End Interrupt Flag
</b><br>
0 = A receive finish interrupt status has not occurred.
<br>
1 = A receive finish interrupt status has occurred.
<br>
Note: It is cleared by software writing one into this bit.
<br>
</div></td></tr><tr><td>
[5]</td><td>PARITYERR</td><td><div style="word-wrap: break-word;"><b>Parity Error Flag
</b><br>
This bit is set to logic 1 whenever the received character does not have a valid 'parity bit'.
<br>
0 = No parity error is generated.
<br>
1 = Parity error is generated.
<br>
Note: This bit can be cleared by write '1' among the BREAK, FRMERR and PARITYERR bits.
<br>
</div></td></tr><tr><td>
[6]</td><td>FRMERR</td><td><div style="word-wrap: break-word;"><b>Framing Error Flag
</b><br>
This bit is set to logic 1 whenever the received character does not have a valid 'stop bit'
<br>
(that is, the stop bit following the last data bit or parity bit is detected as logic 0).
<br>
0 = No framing error is generated.
<br>
1 = Framing error is generated.
<br>
Note: This bit can be cleared by write '1' among the BREAK, FRMERR and PARITYERR bits.
<br>
</div></td></tr><tr><td>
[7]</td><td>BREAK</td><td><div style="word-wrap: break-word;"><b>Break Flag
</b><br>
This bit is set to logic 1 whenever the received data input (RX) is held in the 'spacing state'
<br>
(logic 0) for longer than a full word transmission time (that is, the total time of  start bit + data bits + parity + stop bits).
<br>
0 = No Break is generated.
<br>
1 = Break is generated in the receiver bus.
<br>
Note: This bit can be cleared by write '1' among the BREAK, FRMERR and PARITYERR bits.
<br>
</div></td></tr><tr><td>
[9]</td><td>ABRDETIF</td><td><div style="word-wrap: break-word;"><b>Auto-baud Rate Interrupt Flag
</b><br>
This bit is set when auto-baud rate detection is done among the falling edge of the input data
<br>
If the ABRIEN (USCI_PROTCTL[6]) is set, the auto-baud rate interrupt will be generated
<br>
This bit can be set 4 times when the input data pattern is 0x55 and it is cleared before the next falling edge of the input bus.
<br>
0 = Auto-baud rate detect function is not done.
<br>
1 = One Bit auto-baud rate detect function is done.
<br>
Note: This bit can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[10]</td><td>RXBUSY</td><td><div style="word-wrap: break-word;"><b>RX Bus Status Flag (Read Only)
</b><br>
This bit indicates the busy status of the receiver.
<br>
0 = The receiver is Idle.
<br>
1 = The receiver is BUSY.
<br>
</div></td></tr><tr><td>
[11]</td><td>ABERRSTS</td><td><div style="word-wrap: break-word;"><b>Auto-baud Rate Error Status
</b><br>
This bit is set when auto-baud rate detection counter overrun
<br>
When the auto-baud rate counter overrun, the user shall revise the CLKDIV (USCI_BRGEN[25:16]) value and
<br>
enable ABREN (USCI_PROTCTL[6]) to detect the correct baud rate again.
<br>
0 = Auto-baud rate detect counter is not overrun.
<br>
1 = Auto-baud rate detect counter is overrun.
<br>
Note 1: This bit is set at the same time of ABRDETIF.
<br>
Note 2: This bit can be cleared by writing '1' to ABRDETIF or ABERRSTS.
<br>
</div></td></tr><tr><td>
[16]</td><td>CTSSYNCLV</td><td><div style="word-wrap: break-word;"><b>nCTS Synchronized Level Status (Read Only)
</b><br>
This bit used to indicate the current status of the internal synchronized nCTS signal.
<br>
0 = The internal synchronized nCTS is low.
<br>
1 = The internal synchronized nCTS is high.
<br>
</div></td></tr><tr><td>
[17]</td><td>CTSLV</td><td><div style="word-wrap: break-word;"><b>nCTS Pin Status (Read Only)
</b><br>
This bit used to monitor the current status of nCTS pin input.
<br>
0 = nCTS pin input is low level voltage logic state.
<br>
1 = nCTS pin input is high level voltage logic state.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CTL;                   /*!< [0x0000] USCI Control Register                                            */
    __IO uint32_t INTEN;                 /*!< [0x0004] USCI Interrupt Enable Register                                   */
    __IO uint32_t BRGEN;                 /*!< [0x0008] USCI Baud Rate Generator Register                                */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t DATIN0;                /*!< [0x0010] USCI Input Data Signal Configuration Register 0                  */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[3];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t CTLIN0;                /*!< [0x0020] USCI Input Control Signal Configuration Register 0               */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE2[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t CLKIN;                 /*!< [0x0028] USCI Input Clock Signal Configuration Register                   */
    __IO uint32_t LINECTL;               /*!< [0x002c] USCI Line Control Register                                       */
    __IO uint32_t TXDAT;                 /*!< [0x0030] USCI Transmit Data Register                                      */
    __IO uint32_t RXDAT;                 /*!< [0x0034] USCI Receive Data Register                                       */
    __IO uint32_t BUFCTL;                /*!< [0x0038] USCI Transmit/Receive Buffer Control Register                    */
    __IO uint32_t BUFSTS;                /*!< [0x003c] USCI Transmit/Receive Buffer Status Register                     */
    __IO uint32_t PDMACTL;               /*!< [0x0040] USCI PDMA Control Register                                       */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE3[4];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t WKCTL;                 /*!< [0x0054] USCI Wake-up Control Register                                    */
    __IO uint32_t WKSTS;                 /*!< [0x0058] USCI Wake-up Status Register                                     */
    __IO uint32_t PROTCTL;               /*!< [0x005c] USCI Protocol Control Register                                   */
    __IO uint32_t PROTIEN;               /*!< [0x0060] USCI Protocol Interrupt Enable Register                          */
    __IO uint32_t PROTSTS;               /*!< [0x0064] USCI Protocol Status Register                                    */

} UUART_T;

/**
    @addtogroup UUART_CONST UUART Bit Field Definition
    Constant Definitions for UUART Controller
@{ */

#define UUART_CTL_FUNMODE_Pos            (0)                                               /*!< UUART_T::CTL: FUNMODE Position         */
#define UUART_CTL_FUNMODE_Msk            (0x7ul << UUART_CTL_FUNMODE_Pos)                  /*!< UUART_T::CTL: FUNMODE Mask             */

#define UUART_INTEN_TXSTIEN_Pos          (1)                                               /*!< UUART_T::INTEN: TXSTIEN Position       */
#define UUART_INTEN_TXSTIEN_Msk          (0x1ul << UUART_INTEN_TXSTIEN_Pos)                /*!< UUART_T::INTEN: TXSTIEN Mask           */

#define UUART_INTEN_TXENDIEN_Pos         (2)                                               /*!< UUART_T::INTEN: TXENDIEN Position      */
#define UUART_INTEN_TXENDIEN_Msk         (0x1ul << UUART_INTEN_TXENDIEN_Pos)               /*!< UUART_T::INTEN: TXENDIEN Mask          */

#define UUART_INTEN_RXSTIEN_Pos          (3)                                               /*!< UUART_T::INTEN: RXSTIEN Position       */
#define UUART_INTEN_RXSTIEN_Msk          (0x1ul << UUART_INTEN_RXSTIEN_Pos)                /*!< UUART_T::INTEN: RXSTIEN Mask           */

#define UUART_INTEN_RXENDIEN_Pos         (4)                                               /*!< UUART_T::INTEN: RXENDIEN Position      */
#define UUART_INTEN_RXENDIEN_Msk         (0x1ul << UUART_INTEN_RXENDIEN_Pos)               /*!< UUART_T::INTEN: RXENDIEN Mask          */

#define UUART_BRGEN_RCLKSEL_Pos          (0)                                               /*!< UUART_T::BRGEN: RCLKSEL Position       */
#define UUART_BRGEN_RCLKSEL_Msk          (0x1ul << UUART_BRGEN_RCLKSEL_Pos)                /*!< UUART_T::BRGEN: RCLKSEL Mask           */

#define UUART_BRGEN_PTCLKSEL_Pos         (1)                                               /*!< UUART_T::BRGEN: PTCLKSEL Position      */
#define UUART_BRGEN_PTCLKSEL_Msk         (0x1ul << UUART_BRGEN_PTCLKSEL_Pos)               /*!< UUART_T::BRGEN: PTCLKSEL Mask          */

#define UUART_BRGEN_SPCLKSEL_Pos         (2)                                               /*!< UUART_T::BRGEN: SPCLKSEL Position      */
#define UUART_BRGEN_SPCLKSEL_Msk         (0x3ul << UUART_BRGEN_SPCLKSEL_Pos)               /*!< UUART_T::BRGEN: SPCLKSEL Mask          */

#define UUART_BRGEN_TMCNTEN_Pos          (4)                                               /*!< UUART_T::BRGEN: TMCNTEN Position       */
#define UUART_BRGEN_TMCNTEN_Msk          (0x1ul << UUART_BRGEN_TMCNTEN_Pos)                /*!< UUART_T::BRGEN: TMCNTEN Mask           */

#define UUART_BRGEN_TMCNTSRC_Pos         (5)                                               /*!< UUART_T::BRGEN: TMCNTSRC Position      */
#define UUART_BRGEN_TMCNTSRC_Msk         (0x1ul << UUART_BRGEN_TMCNTSRC_Pos)               /*!< UUART_T::BRGEN: TMCNTSRC Mask          */

#define UUART_BRGEN_PDSCNT_Pos           (8)                                               /*!< UUART_T::BRGEN: PDSCNT Position        */
#define UUART_BRGEN_PDSCNT_Msk           (0x3ul << UUART_BRGEN_PDSCNT_Pos)                 /*!< UUART_T::BRGEN: PDSCNT Mask            */

#define UUART_BRGEN_DSCNT_Pos            (10)                                              /*!< UUART_T::BRGEN: DSCNT Position         */
#define UUART_BRGEN_DSCNT_Msk            (0x1ful << UUART_BRGEN_DSCNT_Pos)                 /*!< UUART_T::BRGEN: DSCNT Mask             */

#define UUART_BRGEN_CLKDIV_Pos           (16)                                              /*!< UUART_T::BRGEN: CLKDIV Position        */
#define UUART_BRGEN_CLKDIV_Msk           (0x3fful << UUART_BRGEN_CLKDIV_Pos)               /*!< UUART_T::BRGEN: CLKDIV Mask            */

#define UUART_DATIN0_SYNCSEL_Pos         (0)                                               /*!< UUART_T::DATIN0: SYNCSEL Position      */
#define UUART_DATIN0_SYNCSEL_Msk         (0x1ul << UUART_DATIN0_SYNCSEL_Pos)               /*!< UUART_T::DATIN0: SYNCSEL Mask          */

#define UUART_DATIN0_ININV_Pos           (2)                                               /*!< UUART_T::DATIN0: ININV Position        */
#define UUART_DATIN0_ININV_Msk           (0x1ul << UUART_DATIN0_ININV_Pos)                 /*!< UUART_T::DATIN0: ININV Mask            */

#define UUART_DATIN0_EDGEDET_Pos         (3)                                               /*!< UUART_T::DATIN0: EDGEDET Position      */
#define UUART_DATIN0_EDGEDET_Msk         (0x3ul << UUART_DATIN0_EDGEDET_Pos)               /*!< UUART_T::DATIN0: EDGEDET Mask          */

#define UUART_CTLIN0_SYNCSEL_Pos         (0)                                               /*!< UUART_T::CTLIN0: SYNCSEL Position      */
#define UUART_CTLIN0_SYNCSEL_Msk         (0x1ul << UUART_CTLIN0_SYNCSEL_Pos)               /*!< UUART_T::CTLIN0: SYNCSEL Mask          */

#define UUART_CTLIN0_ININV_Pos           (2)                                               /*!< UUART_T::CTLIN0: ININV Position        */
#define UUART_CTLIN0_ININV_Msk           (0x1ul << UUART_CTLIN0_ININV_Pos)                 /*!< UUART_T::CTLIN0: ININV Mask            */

#define UUART_CLKIN_SYNCSEL_Pos          (0)                                               /*!< UUART_T::CLKIN: SYNCSEL Position       */
#define UUART_CLKIN_SYNCSEL_Msk          (0x1ul << UUART_CLKIN_SYNCSEL_Pos)                /*!< UUART_T::CLKIN: SYNCSEL Mask           */

#define UUART_LINECTL_LSB_Pos            (0)                                               /*!< UUART_T::LINECTL: LSB Position         */
#define UUART_LINECTL_LSB_Msk            (0x1ul << UUART_LINECTL_LSB_Pos)                  /*!< UUART_T::LINECTL: LSB Mask             */

#define UUART_LINECTL_DATOINV_Pos        (5)                                               /*!< UUART_T::LINECTL: DATOINV Position     */
#define UUART_LINECTL_DATOINV_Msk        (0x1ul << UUART_LINECTL_DATOINV_Pos)              /*!< UUART_T::LINECTL: DATOINV Mask         */

#define UUART_LINECTL_CTLOINV_Pos        (7)                                               /*!< UUART_T::LINECTL: CTLOINV Position     */
#define UUART_LINECTL_CTLOINV_Msk        (0x1ul << UUART_LINECTL_CTLOINV_Pos)              /*!< UUART_T::LINECTL: CTLOINV Mask         */

#define UUART_LINECTL_DWIDTH_Pos         (8)                                               /*!< UUART_T::LINECTL: DWIDTH Position      */
#define UUART_LINECTL_DWIDTH_Msk         (0xful << UUART_LINECTL_DWIDTH_Pos)               /*!< UUART_T::LINECTL: DWIDTH Mask          */

#define UUART_TXDAT_TXDAT_Pos            (0)                                               /*!< UUART_T::TXDAT: TXDAT Position         */
#define UUART_TXDAT_TXDAT_Msk            (0xfffful << UUART_TXDAT_TXDAT_Pos)               /*!< UUART_T::TXDAT: TXDAT Mask             */

#define UUART_RXDAT_RXDAT_Pos            (0)                                               /*!< UUART_T::RXDAT: RXDAT Position         */
#define UUART_RXDAT_RXDAT_Msk            (0xfffful << UUART_RXDAT_RXDAT_Pos)               /*!< UUART_T::RXDAT: RXDAT Mask             */

#define UUART_BUFCTL_TXCLR_Pos           (7)                                               /*!< UUART_T::BUFCTL: TXCLR Position        */
#define UUART_BUFCTL_TXCLR_Msk           (0x1ul << UUART_BUFCTL_TXCLR_Pos)                 /*!< UUART_T::BUFCTL: TXCLR Mask            */

#define UUART_BUFCTL_RXOVIEN_Pos         (14)                                              /*!< UUART_T::BUFCTL: RXOVIEN Position      */
#define UUART_BUFCTL_RXOVIEN_Msk         (0x1ul << UUART_BUFCTL_RXOVIEN_Pos)               /*!< UUART_T::BUFCTL: RXOVIEN Mask          */

#define UUART_BUFCTL_RXCLR_Pos           (15)                                              /*!< UUART_T::BUFCTL: RXCLR Position        */
#define UUART_BUFCTL_RXCLR_Msk           (0x1ul << UUART_BUFCTL_RXCLR_Pos)                 /*!< UUART_T::BUFCTL: RXCLR Mask            */

#define UUART_BUFCTL_TXRST_Pos           (16)                                              /*!< UUART_T::BUFCTL: TXRST Position        */
#define UUART_BUFCTL_TXRST_Msk           (0x1ul << UUART_BUFCTL_TXRST_Pos)                 /*!< UUART_T::BUFCTL: TXRST Mask            */

#define UUART_BUFCTL_RXRST_Pos           (17)                                              /*!< UUART_T::BUFCTL: RXRST Position        */
#define UUART_BUFCTL_RXRST_Msk           (0x1ul << UUART_BUFCTL_RXRST_Pos)                 /*!< UUART_T::BUFCTL: RXRST Mask            */

#define UUART_BUFSTS_RXEMPTY_Pos         (0)                                               /*!< UUART_T::BUFSTS: RXEMPTY Position      */
#define UUART_BUFSTS_RXEMPTY_Msk         (0x1ul << UUART_BUFSTS_RXEMPTY_Pos)               /*!< UUART_T::BUFSTS: RXEMPTY Mask          */

#define UUART_BUFSTS_RXFULL_Pos          (1)                                               /*!< UUART_T::BUFSTS: RXFULL Position       */
#define UUART_BUFSTS_RXFULL_Msk          (0x1ul << UUART_BUFSTS_RXFULL_Pos)                /*!< UUART_T::BUFSTS: RXFULL Mask           */

#define UUART_BUFSTS_RXOVIF_Pos          (3)                                               /*!< UUART_T::BUFSTS: RXOVIF Position       */
#define UUART_BUFSTS_RXOVIF_Msk          (0x1ul << UUART_BUFSTS_RXOVIF_Pos)                /*!< UUART_T::BUFSTS: RXOVIF Mask           */

#define UUART_BUFSTS_TXEMPTY_Pos         (8)                                               /*!< UUART_T::BUFSTS: TXEMPTY Position      */
#define UUART_BUFSTS_TXEMPTY_Msk         (0x1ul << UUART_BUFSTS_TXEMPTY_Pos)               /*!< UUART_T::BUFSTS: TXEMPTY Mask          */

#define UUART_BUFSTS_TXFULL_Pos          (9)                                               /*!< UUART_T::BUFSTS: TXFULL Position       */
#define UUART_BUFSTS_TXFULL_Msk          (0x1ul << UUART_BUFSTS_TXFULL_Pos)                /*!< UUART_T::BUFSTS: TXFULL Mask           */

#define UUART_PDMACTL_PDMARST_Pos        (0)                                               /*!< UUART_T::PDMACTL: PDMARST Position     */
#define UUART_PDMACTL_PDMARST_Msk        (0x1ul << UUART_PDMACTL_PDMARST_Pos)              /*!< UUART_T::PDMACTL: PDMARST Mask         */

#define UUART_PDMACTL_TXPDMAEN_Pos       (1)                                               /*!< UUART_T::PDMACTL: TXPDMAEN Position    */
#define UUART_PDMACTL_TXPDMAEN_Msk       (0x1ul << UUART_PDMACTL_TXPDMAEN_Pos)             /*!< UUART_T::PDMACTL: TXPDMAEN Mask        */

#define UUART_PDMACTL_RXPDMAEN_Pos       (2)                                               /*!< UUART_T::PDMACTL: RXPDMAEN Position    */
#define UUART_PDMACTL_RXPDMAEN_Msk       (0x1ul << UUART_PDMACTL_RXPDMAEN_Pos)             /*!< UUART_T::PDMACTL: RXPDMAEN Mask        */

#define UUART_PDMACTL_PDMAEN_Pos         (3)                                               /*!< UUART_T::PDMACTL: PDMAEN Position      */
#define UUART_PDMACTL_PDMAEN_Msk         (0x1ul << UUART_PDMACTL_PDMAEN_Pos)               /*!< UUART_T::PDMACTL: PDMAEN Mask          */

#define UUART_WKCTL_WKEN_Pos             (0)                                               /*!< UUART_T::WKCTL: WKEN Position          */
#define UUART_WKCTL_WKEN_Msk             (0x1ul << UUART_WKCTL_WKEN_Pos)                   /*!< UUART_T::WKCTL: WKEN Mask              */

#define UUART_WKCTL_PDBOPT_Pos           (2)                                               /*!< UUART_T::WKCTL: PDBOPT Position        */
#define UUART_WKCTL_PDBOPT_Msk           (0x1ul << UUART_WKCTL_PDBOPT_Pos)                 /*!< UUART_T::WKCTL: PDBOPT Mask            */

#define UUART_WKSTS_WKF_Pos              (0)                                               /*!< UUART_T::WKSTS: WKF Position           */
#define UUART_WKSTS_WKF_Msk              (0x1ul << UUART_WKSTS_WKF_Pos)                    /*!< UUART_T::WKSTS: WKF Mask               */

#define UUART_PROTCTL_STOPB_Pos          (0)                                               /*!< UUART_T::PROTCTL: STOPB Position       */
#define UUART_PROTCTL_STOPB_Msk          (0x1ul << UUART_PROTCTL_STOPB_Pos)                /*!< UUART_T::PROTCTL: STOPB Mask           */

#define UUART_PROTCTL_PARITYEN_Pos       (1)                                               /*!< UUART_T::PROTCTL: PARITYEN Position    */
#define UUART_PROTCTL_PARITYEN_Msk       (0x1ul << UUART_PROTCTL_PARITYEN_Pos)             /*!< UUART_T::PROTCTL: PARITYEN Mask        */

#define UUART_PROTCTL_EVENPARITY_Pos     (2)                                               /*!< UUART_T::PROTCTL: EVENPARITY Position  */
#define UUART_PROTCTL_EVENPARITY_Msk     (0x1ul << UUART_PROTCTL_EVENPARITY_Pos)           /*!< UUART_T::PROTCTL: EVENPARITY Mask      */

#define UUART_PROTCTL_RTSAUTOEN_Pos      (3)                                               /*!< UUART_T::PROTCTL: RTSAUTOEN Position   */
#define UUART_PROTCTL_RTSAUTOEN_Msk      (0x1ul << UUART_PROTCTL_RTSAUTOEN_Pos)            /*!< UUART_T::PROTCTL: RTSAUTOEN Mask       */

#define UUART_PROTCTL_CTSAUTOEN_Pos      (4)                                               /*!< UUART_T::PROTCTL: CTSAUTOEN Position   */
#define UUART_PROTCTL_CTSAUTOEN_Msk      (0x1ul << UUART_PROTCTL_CTSAUTOEN_Pos)            /*!< UUART_T::PROTCTL: CTSAUTOEN Mask       */

#define UUART_PROTCTL_RTSAUDIREN_Pos     (5)                                               /*!< UUART_T::PROTCTL: RTSAUDIREN Position  */
#define UUART_PROTCTL_RTSAUDIREN_Msk     (0x1ul << UUART_PROTCTL_RTSAUDIREN_Pos)           /*!< UUART_T::PROTCTL: RTSAUDIREN Mask      */

#define UUART_PROTCTL_ABREN_Pos          (6)                                               /*!< UUART_T::PROTCTL: ABREN Position       */
#define UUART_PROTCTL_ABREN_Msk          (0x1ul << UUART_PROTCTL_ABREN_Pos)                /*!< UUART_T::PROTCTL: ABREN Mask           */

#define UUART_PROTCTL_DATWKEN_Pos        (9)                                               /*!< UUART_T::PROTCTL: DATWKEN Position     */
#define UUART_PROTCTL_DATWKEN_Msk        (0x1ul << UUART_PROTCTL_DATWKEN_Pos)              /*!< UUART_T::PROTCTL: DATWKEN Mask         */

#define UUART_PROTCTL_CTSWKEN_Pos        (10)                                              /*!< UUART_T::PROTCTL: CTSWKEN Position     */
#define UUART_PROTCTL_CTSWKEN_Msk        (0x1ul << UUART_PROTCTL_CTSWKEN_Pos)              /*!< UUART_T::PROTCTL: CTSWKEN Mask         */

#define UUART_PROTCTL_WAKECNT_Pos        (11)                                              /*!< UUART_T::PROTCTL: WAKECNT Position     */
#define UUART_PROTCTL_WAKECNT_Msk        (0xful << UUART_PROTCTL_WAKECNT_Pos)              /*!< UUART_T::PROTCTL: WAKECNT Mask         */

#define UUART_PROTCTL_BRDETITV_Pos       (16)                                              /*!< UUART_T::PROTCTL: BRDETITV Position    */
#define UUART_PROTCTL_BRDETITV_Msk       (0x1fful << UUART_PROTCTL_BRDETITV_Pos)           /*!< UUART_T::PROTCTL: BRDETITV Mask        */

#define UUART_PROTCTL_STICKEN_Pos        (26)                                              /*!< UUART_T::PROTCTL: STICKEN Position     */
#define UUART_PROTCTL_STICKEN_Msk        (0x1ul << UUART_PROTCTL_STICKEN_Pos)              /*!< UUART_T::PROTCTL: STICKEN Mask         */

#define UUART_PROTCTL_BCEN_Pos           (29)                                              /*!< UUART_T::PROTCTL: BCEN Position        */
#define UUART_PROTCTL_BCEN_Msk           (0x1ul << UUART_PROTCTL_BCEN_Pos)                 /*!< UUART_T::PROTCTL: BCEN Mask            */

#define UUART_PROTCTL_PROTEN_Pos         (31)                                              /*!< UUART_T::PROTCTL: PROTEN Position      */
#define UUART_PROTCTL_PROTEN_Msk         (0x1ul << UUART_PROTCTL_PROTEN_Pos)               /*!< UUART_T::PROTCTL: PROTEN Mask          */

#define UUART_PROTIEN_ABRIEN_Pos         (1)                                               /*!< UUART_T::PROTIEN: ABRIEN Position      */
#define UUART_PROTIEN_ABRIEN_Msk         (0x1ul << UUART_PROTIEN_ABRIEN_Pos)               /*!< UUART_T::PROTIEN: ABRIEN Mask          */

#define UUART_PROTIEN_RLSIEN_Pos         (2)                                               /*!< UUART_T::PROTIEN: RLSIEN Position      */
#define UUART_PROTIEN_RLSIEN_Msk         (0x1ul << UUART_PROTIEN_RLSIEN_Pos)               /*!< UUART_T::PROTIEN: RLSIEN Mask          */

#define UUART_PROTSTS_TXSTIF_Pos         (1)                                               /*!< UUART_T::PROTSTS: TXSTIF Position      */
#define UUART_PROTSTS_TXSTIF_Msk         (0x1ul << UUART_PROTSTS_TXSTIF_Pos)               /*!< UUART_T::PROTSTS: TXSTIF Mask          */

#define UUART_PROTSTS_TXENDIF_Pos        (2)                                               /*!< UUART_T::PROTSTS: TXENDIF Position     */
#define UUART_PROTSTS_TXENDIF_Msk        (0x1ul << UUART_PROTSTS_TXENDIF_Pos)              /*!< UUART_T::PROTSTS: TXENDIF Mask         */

#define UUART_PROTSTS_RXSTIF_Pos         (3)                                               /*!< UUART_T::PROTSTS: RXSTIF Position      */
#define UUART_PROTSTS_RXSTIF_Msk         (0x1ul << UUART_PROTSTS_RXSTIF_Pos)               /*!< UUART_T::PROTSTS: RXSTIF Mask          */

#define UUART_PROTSTS_RXENDIF_Pos        (4)                                               /*!< UUART_T::PROTSTS: RXENDIF Position     */
#define UUART_PROTSTS_RXENDIF_Msk        (0x1ul << UUART_PROTSTS_RXENDIF_Pos)              /*!< UUART_T::PROTSTS: RXENDIF Mask         */

#define UUART_PROTSTS_PARITYERR_Pos      (5)                                               /*!< UUART_T::PROTSTS: PARITYERR Position   */
#define UUART_PROTSTS_PARITYERR_Msk      (0x1ul << UUART_PROTSTS_PARITYERR_Pos)            /*!< UUART_T::PROTSTS: PARITYERR Mask       */

#define UUART_PROTSTS_FRMERR_Pos         (6)                                               /*!< UUART_T::PROTSTS: FRMERR Position      */
#define UUART_PROTSTS_FRMERR_Msk         (0x1ul << UUART_PROTSTS_FRMERR_Pos)               /*!< UUART_T::PROTSTS: FRMERR Mask          */

#define UUART_PROTSTS_BREAK_Pos          (7)                                               /*!< UUART_T::PROTSTS: BREAK Position       */
#define UUART_PROTSTS_BREAK_Msk          (0x1ul << UUART_PROTSTS_BREAK_Pos)                /*!< UUART_T::PROTSTS: BREAK Mask           */

#define UUART_PROTSTS_ABRDETIF_Pos       (9)                                               /*!< UUART_T::PROTSTS: ABRDETIF Position    */
#define UUART_PROTSTS_ABRDETIF_Msk       (0x1ul << UUART_PROTSTS_ABRDETIF_Pos)             /*!< UUART_T::PROTSTS: ABRDETIF Mask        */

#define UUART_PROTSTS_RXBUSY_Pos         (10)                                              /*!< UUART_T::PROTSTS: RXBUSY Position      */
#define UUART_PROTSTS_RXBUSY_Msk         (0x1ul << UUART_PROTSTS_RXBUSY_Pos)               /*!< UUART_T::PROTSTS: RXBUSY Mask          */

#define UUART_PROTSTS_ABERRSTS_Pos       (11)                                              /*!< UUART_T::PROTSTS: ABERRSTS Position    */
#define UUART_PROTSTS_ABERRSTS_Msk       (0x1ul << UUART_PROTSTS_ABERRSTS_Pos)             /*!< UUART_T::PROTSTS: ABERRSTS Mask        */

#define UUART_PROTSTS_CTSSYNCLV_Pos      (16)                                              /*!< UUART_T::PROTSTS: CTSSYNCLV Position   */
#define UUART_PROTSTS_CTSSYNCLV_Msk      (0x1ul << UUART_PROTSTS_CTSSYNCLV_Pos)            /*!< UUART_T::PROTSTS: CTSSYNCLV Mask       */

#define UUART_PROTSTS_CTSLV_Pos          (17)                                              /*!< UUART_T::PROTSTS: CTSLV Position       */
#define UUART_PROTSTS_CTSLV_Msk          (0x1ul << UUART_PROTSTS_CTSLV_Pos)                /*!< UUART_T::PROTSTS: CTSLV Mask           */

/**@}*/ /* UUART_CONST */
/**@}*/ /* end of UUART register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __UUART_REG_H__ */
