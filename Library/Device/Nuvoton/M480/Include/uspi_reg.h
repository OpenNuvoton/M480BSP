/**************************************************************************//**
 * @file     uspi_reg.h
 * @version  V1.00
 * @brief    USPI register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __USPI_REG_H__
#define __USPI_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup USPI SPI Mode of USCI Controller(USPI)
    Memory Mapped Structure for USPI Controller
@{ */

typedef struct
{


    /**
@var USPI_T::CTL

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


@var USPI_T::INTEN

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
[3]</td><td>RXSTIEN</td><td><div style="word-wrap: break-word;"><b>Receive Start Interrupt Enable Bit
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


@var USPI_T::BRGEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BRGEN
</font><br><p> <font size="2">
Offset: 0x08  USCI Baud Rate Generator Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>RCLKSEL</td><td><div style="word-wrap: break-word;"><b>Reference Clock Source Selection
</b><br>
This bit selects the source of reference clock (fREF_CLK).
<br>
0 = Peripheral device clock fPCLK.
<br>
1 = Reserved.
<br>
</div></td></tr><tr><td>
[1]</td><td>PTCLKSEL</td><td><div style="word-wrap: break-word;"><b>Protocol Clock Source Selection
</b><br>
This bit selects the source of protocol clock (fPROT_CLK).
<br>
0 = Reference clock fREF_CLK.
<br>
1 = fREF_CLK2 (its frequency is half of fREF_CLK).
<br>
</div></td></tr><tr><td>
[3:2]</td><td>SPCLKSEL</td><td><div style="word-wrap: break-word;"><b>Sample Clock Source Selection
</b><br>
This bit field used for the clock source selection of sample clock (fSAMP_CLK) for the protocol processor.
<br>
00 = fDIV_CLK.
<br>
01 = fPROT_CLK.
<br>
10 = fSCLK.
<br>
11 = fREF_CLK.
<br>
</div></td></tr><tr><td>
[4]</td><td>TMCNTEN</td><td><div style="word-wrap: break-word;"><b>Time Measurement Counter Enable Bit
</b><br>
This bit enables the 10-bit timing measurement counter.
<br>
0 = Time measurement counter is Disabled.
<br>
1 = Time measurement counter is Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>TMCNTSRC</td><td><div style="word-wrap: break-word;"><b>Time Measurement Counter Clock Source Selection
</b><br>
0 = Time measurement counter with fPROT_CLK.
<br>
1 = Time measurement counter with fDIV_CLK.
<br>
</div></td></tr><tr><td>
[25:16]</td><td>CLKDIV</td><td><div style="word-wrap: break-word;"><b>Clock Divider
</b><br>
This bit field defines the ratio between the protocol clock frequency fPROT_CLK and the clock divider frequency fDIV_CLK (fDIV_CLK = fPROT_CLK / (CLKDIV+1) ).
<br>
Note: In UART function, it can be updated by hardware in the 4th falling edge of the input data 0x55 when the auto baud rate function (ABREN(USPI_PROTCTL[6])) is enabled
<br>
The revised value is the average bit time between bit 5 and bit 6
<br>
The user can use revised CLKDIV and new BRDETITV (USPI_PROTCTL[24:16]) to calculate the precise baud rate.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USPI_T::DATIN0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DATIN0
</font><br><p> <font size="2">
Offset: 0x10  USCI Input Data Signal Configuration Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SYNCSEL</td><td><div style="word-wrap: break-word;"><b>Input Signal Synchronization Selection
</b><br>
This bit selects if the un-synchronized input signal (with optionally inverted) or the   synchronized (and optionally filtered) signal can be used as input for the   data shift unit.
<br>
0 = The un-synchronized signal can be taken as input for the data shift unit.
<br>
1 = The synchronized signal can be taken as input for the data shift unit.
<br>
Note: In SPI protocol, we suggest this bit   should be set as 0.
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
Note: In SPI protocol, we suggest this bit   should be set as 0.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USPI_T::CTLIN0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTLIN0
</font><br><p> <font size="2">
Offset: 0x20  USCI Input Control Signal Configuration Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SYNCSEL</td><td><div style="word-wrap: break-word;"><b>Input Synchronization Signal Selection
</b><br>
This bit selects if the un-synchronized input signal (with optionally inverted) or the   synchronized (and optionally filtered) signal can be used as input for the   data shift unit.
<br>
0 = The un-synchronized signal can be taken as input for the data shift unit.
<br>
1 = The synchronized signal can be taken as input for the data shift unit.
<br>
Note: In SPI protocol, we suggest this bit   should be set as 0.
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


@var USPI_T::CLKIN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKIN
</font><br><p> <font size="2">
Offset: 0x28  USCI Input Clock Signal Configuration Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SYNCSEL</td><td><div style="word-wrap: break-word;"><b>Input Synchronization Signal Selection
</b><br>
This bit selects if the un-synchronized input signal or the synchronized (and   optionally filtered) signal can be used as input for the data shift unit.
<br>
0 = The un-synchronized signal can be taken as input for the data shift unit.
<br>
1 = The synchronized signal can be taken as input for the data shift unit.
<br>
Note: In SPI protocol, we suggest this bit   should be set as 0.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USPI_T::LINECTL

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
This bit defines the relation between the internal shift data value and the output data signal of USCIx_DAT0/1 pin.
<br>
0 = Data output level is not inverted.
<br>
1 = Data output level is inverted.
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
Note: The control signal has different definitions in different protocol
<br>
In SPI protocol, the control signal means slave select signal
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
...
<br>
0xF: The data word contains 15 bits located at bit positions [14:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USPI_T::TXDAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TXDAT
</font><br><p> <font size="2">
Offset: 0x30  USCI Transmit Data Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>TXDAT</td><td><div style="word-wrap: break-word;"><b>Transmit Data
</b><br>
Software can use this bit field to write 16-bit transmit data for transmission
<br>
In order to avoid overwriting the transmit data, user have to check TXEMPTY (USPI_BUFSTS[8]) status before writing transmit data into this bit field.
<br>
</div></td></tr><tr><td>
[16]</td><td>PORTDIR</td><td><div style="word-wrap: break-word;"><b>Port Direction Control
</b><br>
This bit field is only available while USCI operates in SPI protocol (FUNMODE = 0x1) with half-duplex transfer
<br>
It is used to define the direction of the data port pin
<br>
When software writes USPI_TXDAT register, the transmit data and its port direction are settled simultaneously.
<br>
0 = The data pin is configured as output mode.
<br>
1 = The data pin is configured as input mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USPI_T::RXDAT

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
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USPI_T::BUFCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BUFCTL
</font><br><p> <font size="2">
Offset: 0x38  USCI Transmit/Receive Buffer Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[6]</td><td>TXUDRIEN</td><td><div style="word-wrap: break-word;"><b>Slave Transmit Under Run Interrupt Enable Bit
</b><br>
0 = Transmit under-run interrupt Disabled.
<br>
1 = Transmit under-run interrupt Enabled.
<br>
</div></td></tr><tr><td>
[7]</td><td>TXCLR</td><td><div style="word-wrap: break-word;"><b>Clear Transmit Buffer
</b><br>
0 = No effect.
<br>
1 = The transmit buffer is cleared
<br>
Should only be used while the buffer is not taking part in data traffic.
<br>
Note: It is cleared automatically after one PCLK cycle.
<br>
</div></td></tr><tr><td>
[14]</td><td>RXOVIEN</td><td><div style="word-wrap: break-word;"><b>Receive Buffer Overrun Interrupt Enable Bit
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
1 = The receive buffer is cleared
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
Note: It is cleared automatically after one PCLK cycle.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USPI_T::BUFSTS

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
[3]</td><td>RXOVIF</td><td><div style="word-wrap: break-word;"><b>Receive Buffer Over-run Interrupt Status
</b><br>
This bit indicates that a receive buffer overrun event has been detected
<br>
If RXOVIEN (USPI_BUFCTL[14]) is enabled, the corresponding interrupt request is activated
<br>
It is cleared by software writes 1 to this bit.
<br>
0 = A receive buffer overrun event has not been detected.
<br>
1 = A receive buffer overrun event has been detected.
<br>
</div></td></tr><tr><td>
[8]</td><td>TXEMPTY</td><td><div style="word-wrap: break-word;"><b>Transmit Buffer Empty Indicator
</b><br>
0 = Transmit buffer is not empty.
<br>
1 = Transmit buffer is empty and available for the next transmission datum.
<br>
</div></td></tr><tr><td>
[9]</td><td>TXFULL</td><td><div style="word-wrap: break-word;"><b>Transmit Buffer Full Indicator
</b><br>
0 = Transmit buffer is not full.
<br>
1 = Transmit buffer is full.
<br>
</div></td></tr><tr><td>
[11]</td><td>TXUDRIF</td><td><div style="word-wrap: break-word;"><b>Transmit Buffer Under-run Interrupt Status
</b><br>
This bit indicates that a transmit buffer under-run event has been detected
<br>
If enabled by TXUDRIEN (USPI_BUFCTL[6]), the corresponding interrupt request is activated
<br>
It is cleared by software writes 1 to this bit
<br>
0 = A transmit buffer under-run event has not been detected.
<br>
1 = A transmit buffer under-run event has been detected.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USPI_T::PDMACTL

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
Notice: The I2C is not supporting PDMA function.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USPI_T::WKCTL

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
[1]</td><td>WKADDREN</td><td><div style="word-wrap: break-word;"><b>Wake-up Address Match Enable Bit
</b><br>
0 = The chip is woken up according data toggle.
<br>
1 = The chip is woken up according address match.
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


@var USPI_T::WKSTS

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


@var USPI_T::PROTCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PROTCTL
</font><br><p> <font size="2">
Offset: 0x5C  USCI Protocol Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SLAVE</td><td><div style="word-wrap: break-word;"><b>Slave Mode Selection
</b><br>
0 = Master mode.
<br>
1 = Slave mode.
<br>
</div></td></tr><tr><td>
[1]</td><td>SLV3WIRE</td><td><div style="word-wrap: break-word;"><b>Slave 3-wire Mode Selection (Slave Only)
</b><br>
The SPI protocol can work with 3-wire interface (without slave select signal) in Slave mode.
<br>
0 = 4-wire bi-direction interface.
<br>
1 = 3-wire bi-direction interface.
<br>
</div></td></tr><tr><td>
[2]</td><td>SS</td><td><div style="word-wrap: break-word;"><b>Slave Select Control (Master Only)
</b><br>
If AUTOSS bit is cleared, setting this bit to 1 will set the slave select signal to active state, and setting this bit to 0 will set the slave select signal back to inactive state.
<br>
If the AUTOSS function is enabled (AUTOSS = 1), the setting value of this bit will not affect the current state of slave select signal.
<br>
Note: In SPI protocol, the internal slave select signal is active high.
<br>
</div></td></tr><tr><td>
[3]</td><td>AUTOSS</td><td><div style="word-wrap: break-word;"><b>Automatic Slave Select Function Enable (Master Only)
</b><br>
0 = Slave select signal will be controlled by the setting value of SS (USPI_PROTCTL[2]) bit.
<br>
1 = Slave select signal will be generated automatically
<br>
The slave select signal will be asserted by the SPI controller when transmit/receive is started, and will be de-asserted after each transmit/receive is finished.
<br>
</div></td></tr><tr><td>
[7:6]</td><td>SCLKMODE</td><td><div style="word-wrap: break-word;"><b>Serial Bus Clock Mode
</b><br>
This bit field defines the SCLK idle status, data transmit, and data receive edge.
<br>
MODE0 = The idle state of SPI clock is low level
<br>
Data is transmitted with falling edge and received with rising edge.
<br>
MODE1 = The idle state of SPI clock is low level
<br>
Data is transmitted with rising edge and received with falling edge.
<br>
MODE2 = The idle state of SPI clock is high level
<br>
Data is transmitted with rising edge and received with falling edge.
<br>
MODE3 = The idle state of SPI clock is high level
<br>
Data is transmitted with falling edge and received with rising edge.
<br>
</div></td></tr><tr><td>
[11:8]</td><td>SUSPITV</td><td><div style="word-wrap: break-word;"><b>Suspend Interval (Master Only)
</b><br>
This bit field provides the configurable suspend interval between two successive transmit/receive transaction in a transfer
<br>
The definition of the suspend interval is the interval between the last clock edge of the preceding transaction word and the first clock edge of the following transaction word
<br>
The default value is 0x3
<br>
The period of the suspend interval is obtained according to the following equation.
<br>
(SUSPITV[3:0] + 0.5) * period of SPI_CLK clock cycle
<br>
Example:
<br>
SUSPITV = 0x0 ... 0.5 SPI_CLK clock cycle.
<br>
SUSPITV = 0x1 ... 1.5 SPI_CLK clock cycle.
<br>
.....
<br>
SUSPITV = 0xE ... 14.5 SPI_CLK clock cycle.
<br>
SUSPITV = 0xF ... 15.5 SPI_CLK clock cycle.
<br>
</div></td></tr><tr><td>
[14:12]</td><td>TSMSEL</td><td><div style="word-wrap: break-word;"><b>Transmit Data Mode Selection
</b><br>
This bit field describes how receive and transmit data is shifted in and out.
<br>
TSMSEL = 000b: Full-duplex SPI.
<br>
TSMSEL = 100b: Half-duplex SPI.
<br>
Other values are reserved.
<br>
Note: Changing the value of this bit field will produce the TXRST and RXRST to clear the TX/RX data buffer automatically.
<br>
</div></td></tr><tr><td>
[25:16]</td><td>SLVTOCNT</td><td><div style="word-wrap: break-word;"><b>Slave Mode Time-out Period (Slave Only)
</b><br>
In Slave mode, this bit field is used for Slave time-out period
<br>
This bit field indicates how many clock periods (selected by TMCNTSRC, USPI_BRGEN[5]) between the two edges of input SCLK will assert the Slave time-out event
<br>
Writing 0x0 into this bit field will disable the Slave time-out function.
<br>
Example: Assume SLVTOCNT is 0x0A and TMCNTSRC (USPI_BRGEN[5]) is 1, it means the time-out event will occur if the state of SPI bus clock pin is not changed more than (10+1) periods of fDIV_CLK.
<br>
</div></td></tr><tr><td>
[28]</td><td>TXUDRPOL</td><td><div style="word-wrap: break-word;"><b>Transmit Under-run Data Polarity (for Slave)
</b><br>
This bit defines the transmitting data level when no data is available for transferring.
<br>
0 = The output data level is 0 if TX under run event occurs.
<br>
1 = The output data level is 1 if TX under run event occurs.
<br>
</div></td></tr><tr><td>
[31]</td><td>PROTEN</td><td><div style="word-wrap: break-word;"><b>SPI Protocol Enable Bit
</b><br>
0 = SPI Protocol Disabled.
<br>
1 = SPI Protocol Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USPI_T::PROTIEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PROTIEN
</font><br><p> <font size="2">
Offset: 0x60  USCI Protocol Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SSINAIEN</td><td><div style="word-wrap: break-word;"><b>Slave Select Inactive Interrupt Enable Control
</b><br>
This bit enables/disables the generation of a slave select interrupt if the slave select changes to inactive.
<br>
0 = Slave select inactive interrupt generation Disabled.
<br>
1 = Slave select inactive interrupt generation Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>SSACTIEN</td><td><div style="word-wrap: break-word;"><b>Slave Select Active Interrupt Enable Control
</b><br>
This bit enables/disables the generation of a slave select interrupt if the slave select changes to active.
<br>
0 = Slave select active interrupt generation Disabled.
<br>
1 = Slave select active interrupt generation Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>SLVTOIEN</td><td><div style="word-wrap: break-word;"><b>Slave Time-out Interrupt Enable Control
</b><br>
In SPI protocol, this bit enables the interrupt generation in case of a Slave time-out event.
<br>
0 = The Slave time-out interrupt Disabled.
<br>
1 = The Slave time-out interrupt Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>SLVBEIEN</td><td><div style="word-wrap: break-word;"><b>Slave Mode Bit Count Error Interrupt Enable Control
</b><br>
If data transfer is terminated by slave time-out or slave select inactive event in Slave mode, so that the transmit/receive data bit count does not match the setting of DWIDTH (USPI_LINECTL[11:8])
<br>
Bit count error event occurs.
<br>
0 = The Slave mode bit count error interrupt Disabled.
<br>
1 = The Slave mode bit count error interrupt Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USPI_T::PROTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PROTSTS
</font><br><p> <font size="2">
Offset: 0x64  USCI Protocol Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1]</td><td>TXSTIF</td><td><div style="word-wrap: break-word;"><b>Transmit Start Interrupt Flag
</b><br>
0 = Transmit start event does not occur.
<br>
1 = Transmit start event occurs.
<br>
Note: It is cleared by software writes 1 to this bit
<br>
</div></td></tr><tr><td>
[2]</td><td>TXENDIF</td><td><div style="word-wrap: break-word;"><b>Transmit End Interrupt Flag
</b><br>
0 = Transmit end event does not occur.
<br>
1 = Transmit end event occurs.
<br>
Note: It is cleared by software writes 1 to this bit
<br>
</div></td></tr><tr><td>
[3]</td><td>RXSTIF</td><td><div style="word-wrap: break-word;"><b>Receive Start Interrupt Flag
</b><br>
0 = Receive start event does not occur.
<br>
1 = Receive start event occurs.
<br>
Note: It is cleared by software writes 1 to this bit
<br>
</div></td></tr><tr><td>
[4]</td><td>RXENDIF</td><td><div style="word-wrap: break-word;"><b>Receive End Interrupt Flag
</b><br>
0 = Receive end event does not occur.
<br>
1 = Receive end event occurs.
<br>
Note: It is cleared by software writes 1 to this bit
<br>
</div></td></tr><tr><td>
[5]</td><td>SLVTOIF</td><td><div style="word-wrap: break-word;"><b>Slave Time-out Interrupt Flag (for Slave Only)
</b><br>
0 = Slave time-out event does not occur.
<br>
1 = Slave time-out event occurs.
<br>
Note: It is cleared by software writes 1 to this bit
<br>
</div></td></tr><tr><td>
[6]</td><td>SLVBEIF</td><td><div style="word-wrap: break-word;"><b>Slave Bit Count Error Interrupt Flag (for Slave Only)
</b><br>
0 = Slave bit count error event does not occur.
<br>
1 = Slave bit count error event occurs.
<br>
Note: It is cleared by software writes 1 to this bit.
<br>
</div></td></tr><tr><td>
[8]</td><td>SSINAIF</td><td><div style="word-wrap: break-word;"><b>Slave Select Inactive Interrupt Flag (for Slave Only)
</b><br>
This bit indicates that the internal slave select signal has changed to inactive
<br>
It is cleared by software writes 1 to this bit
<br>
0 = The slave select signal has not changed to inactive.
<br>
1 = The slave select signal has changed to inactive.
<br>
Note: The internal slave select signal is active high.
<br>
</div></td></tr><tr><td>
[9]</td><td>SSACTIF</td><td><div style="word-wrap: break-word;"><b>Slave Select Active Interrupt Flag (for Slave Only)
</b><br>
This bit indicates that the internal slave select signal has changed to active
<br>
It is cleared by software writes one to this bit
<br>
0 = The slave select signal has not changed to active.
<br>
1 = The slave select signal has changed to active.
<br>
Note: The internal slave select signal is active high.
<br>
</div></td></tr><tr><td>
[16]</td><td>SSLINE</td><td><div style="word-wrap: break-word;"><b>Slave Select Line Bus Status (Read Only)
</b><br>
This bit is only available in Slave mode
<br>
It used to monitor the current status of the input slave select signal on the bus.
<br>
0 = The slave select line status is 0.
<br>
1 = The slave select line status is 1.
<br>
</div></td></tr><tr><td>
[17]</td><td>BUSY</td><td><div style="word-wrap: break-word;"><b>Busy Status (Read Only)
</b><br>
0 = SPI is in idle state.
<br>
1 = SPI is in busy state.
<br>
The following listing are the bus busy conditions:
<br>
a. USPI_PROTCTL[31] = 1 and the TXEMPTY = 0.
<br>
b. For SPI Master mode, the TXEMPTY = 1 but the current transaction is not finished yet.
<br>
c. For SPI Slave mode, the USPI_PROTCTL[31] = 1 and there is serial clock input into the SPI core logic when slave select is active.
<br>
d. For SPI Slave mode, the USPI_PROTCTL[31] = 1 and the transmit buffer or transmit shift register is not empty even if the slave select is inactive.
<br>
</div></td></tr><tr><td>
[18]</td><td>SLVUDR</td><td><div style="word-wrap: break-word;"><b>Slave Mode Transmit Under-run Status (Read Only)
</b><br>
In Slave mode, if there is no available transmit data in buffer while transmit data shift out caused by input serial bus clock, this status flag will be set to 1
<br>
This bit indicates whether the current shift-out data of word transmission is switched to TXUDRPOL (USPI_PROTCTL[28]) or not.
<br>
0 = Slave transmit under-run event does not occur.
<br>
1 = Slave transmit under-run event occurs.
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
    __O  uint32_t TXDAT;                 /*!< [0x0030] USCI Transmit Data Register                                      */
    __I  uint32_t RXDAT;                 /*!< [0x0034] USCI Receive Data Register                                       */
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

} USPI_T;

/**
    @addtogroup USPI_CONST USPI Bit Field Definition
    Constant Definitions for USPI Controller
@{ */

#define USPI_CTL_FUNMODE_Pos             (0)                                               /*!< USPI_T::CTL: FUNMODE Position          */
#define USPI_CTL_FUNMODE_Msk             (0x7ul << USPI_CTL_FUNMODE_Pos)                   /*!< USPI_T::CTL: FUNMODE Mask              */

#define USPI_INTEN_TXSTIEN_Pos           (1)                                               /*!< USPI_T::INTEN: TXSTIEN Position        */
#define USPI_INTEN_TXSTIEN_Msk           (0x1ul << USPI_INTEN_TXSTIEN_Pos)                 /*!< USPI_T::INTEN: TXSTIEN Mask            */

#define USPI_INTEN_TXENDIEN_Pos          (2)                                               /*!< USPI_T::INTEN: TXENDIEN Position       */
#define USPI_INTEN_TXENDIEN_Msk          (0x1ul << USPI_INTEN_TXENDIEN_Pos)                /*!< USPI_T::INTEN: TXENDIEN Mask           */

#define USPI_INTEN_RXSTIEN_Pos           (3)                                               /*!< USPI_T::INTEN: RXSTIEN Position        */
#define USPI_INTEN_RXSTIEN_Msk           (0x1ul << USPI_INTEN_RXSTIEN_Pos)                 /*!< USPI_T::INTEN: RXSTIEN Mask            */

#define USPI_INTEN_RXENDIEN_Pos          (4)                                               /*!< USPI_T::INTEN: RXENDIEN Position       */
#define USPI_INTEN_RXENDIEN_Msk          (0x1ul << USPI_INTEN_RXENDIEN_Pos)                /*!< USPI_T::INTEN: RXENDIEN Mask           */

#define USPI_BRGEN_RCLKSEL_Pos           (0)                                               /*!< USPI_T::BRGEN: RCLKSEL Position        */
#define USPI_BRGEN_RCLKSEL_Msk           (0x1ul << USPI_BRGEN_RCLKSEL_Pos)                 /*!< USPI_T::BRGEN: RCLKSEL Mask            */

#define USPI_BRGEN_PTCLKSEL_Pos          (1)                                               /*!< USPI_T::BRGEN: PTCLKSEL Position       */
#define USPI_BRGEN_PTCLKSEL_Msk          (0x1ul << USPI_BRGEN_PTCLKSEL_Pos)                /*!< USPI_T::BRGEN: PTCLKSEL Mask           */

#define USPI_BRGEN_SPCLKSEL_Pos          (2)                                               /*!< USPI_T::BRGEN: SPCLKSEL Position       */
#define USPI_BRGEN_SPCLKSEL_Msk          (0x3ul << USPI_BRGEN_SPCLKSEL_Pos)                /*!< USPI_T::BRGEN: SPCLKSEL Mask           */

#define USPI_BRGEN_TMCNTEN_Pos           (4)                                               /*!< USPI_T::BRGEN: TMCNTEN Position        */
#define USPI_BRGEN_TMCNTEN_Msk           (0x1ul << USPI_BRGEN_TMCNTEN_Pos)                 /*!< USPI_T::BRGEN: TMCNTEN Mask            */

#define USPI_BRGEN_TMCNTSRC_Pos          (5)                                               /*!< USPI_T::BRGEN: TMCNTSRC Position       */
#define USPI_BRGEN_TMCNTSRC_Msk          (0x1ul << USPI_BRGEN_TMCNTSRC_Pos)                /*!< USPI_T::BRGEN: TMCNTSRC Mask           */

#define USPI_BRGEN_CLKDIV_Pos            (16)                                              /*!< USPI_T::BRGEN: CLKDIV Position         */
#define USPI_BRGEN_CLKDIV_Msk            (0x3fful << USPI_BRGEN_CLKDIV_Pos)                /*!< USPI_T::BRGEN: CLKDIV Mask             */

#define USPI_DATIN0_SYNCSEL_Pos          (0)                                               /*!< USPI_T::DATIN0: SYNCSEL Position       */
#define USPI_DATIN0_SYNCSEL_Msk          (0x1ul << USPI_DATIN0_SYNCSEL_Pos)                /*!< USPI_T::DATIN0: SYNCSEL Mask           */

#define USPI_DATIN0_ININV_Pos            (2)                                               /*!< USPI_T::DATIN0: ININV Position         */
#define USPI_DATIN0_ININV_Msk            (0x1ul << USPI_DATIN0_ININV_Pos)                  /*!< USPI_T::DATIN0: ININV Mask             */

#define USPI_CTLIN0_SYNCSEL_Pos          (0)                                               /*!< USPI_T::CTLIN0: SYNCSEL Position       */
#define USPI_CTLIN0_SYNCSEL_Msk          (0x1ul << USPI_CTLIN0_SYNCSEL_Pos)                /*!< USPI_T::CTLIN0: SYNCSEL Mask           */

#define USPI_CTLIN0_ININV_Pos            (2)                                               /*!< USPI_T::CTLIN0: ININV Position         */
#define USPI_CTLIN0_ININV_Msk            (0x1ul << USPI_CTLIN0_ININV_Pos)                  /*!< USPI_T::CTLIN0: ININV Mask             */

#define USPI_CLKIN_SYNCSEL_Pos           (0)                                               /*!< USPI_T::CLKIN: SYNCSEL Position        */
#define USPI_CLKIN_SYNCSEL_Msk           (0x1ul << USPI_CLKIN_SYNCSEL_Pos)                 /*!< USPI_T::CLKIN: SYNCSEL Mask            */

#define USPI_LINECTL_LSB_Pos             (0)                                               /*!< USPI_T::LINECTL: LSB Position          */
#define USPI_LINECTL_LSB_Msk             (0x1ul << USPI_LINECTL_LSB_Pos)                   /*!< USPI_T::LINECTL: LSB Mask              */

#define USPI_LINECTL_DATOINV_Pos         (5)                                               /*!< USPI_T::LINECTL: DATOINV Position      */
#define USPI_LINECTL_DATOINV_Msk         (0x1ul << USPI_LINECTL_DATOINV_Pos)               /*!< USPI_T::LINECTL: DATOINV Mask          */

#define USPI_LINECTL_CTLOINV_Pos         (7)                                               /*!< USPI_T::LINECTL: CTLOINV Position      */
#define USPI_LINECTL_CTLOINV_Msk         (0x1ul << USPI_LINECTL_CTLOINV_Pos)               /*!< USPI_T::LINECTL: CTLOINV Mask          */

#define USPI_LINECTL_DWIDTH_Pos          (8)                                               /*!< USPI_T::LINECTL: DWIDTH Position       */
#define USPI_LINECTL_DWIDTH_Msk          (0xful << USPI_LINECTL_DWIDTH_Pos)                /*!< USPI_T::LINECTL: DWIDTH Mask           */

#define USPI_TXDAT_TXDAT_Pos             (0)                                               /*!< USPI_T::TXDAT: TXDAT Position          */
#define USPI_TXDAT_TXDAT_Msk             (0xfffful << USPI_TXDAT_TXDAT_Pos)                /*!< USPI_T::TXDAT: TXDAT Mask              */

#define USPI_TXDAT_PORTDIR_Pos           (16)                                              /*!< USPI_T::TXDAT: PORTDIR Position        */
#define USPI_TXDAT_PORTDIR_Msk           (0x1ul << USPI_TXDAT_PORTDIR_Pos)                 /*!< USPI_T::TXDAT: PORTDIR Mask            */

#define USPI_RXDAT_RXDAT_Pos             (0)                                               /*!< USPI_T::RXDAT: RXDAT Position          */
#define USPI_RXDAT_RXDAT_Msk             (0xfffful << USPI_RXDAT_RXDAT_Pos)                /*!< USPI_T::RXDAT: RXDAT Mask              */

#define USPI_BUFCTL_TXUDRIEN_Pos         (6)                                               /*!< USPI_T::BUFCTL: TXUDRIEN Position      */
#define USPI_BUFCTL_TXUDRIEN_Msk         (0x1ul << USPI_BUFCTL_TXUDRIEN_Pos)               /*!< USPI_T::BUFCTL: TXUDRIEN Mask          */

#define USPI_BUFCTL_TXCLR_Pos            (7)                                               /*!< USPI_T::BUFCTL: TXCLR Position         */
#define USPI_BUFCTL_TXCLR_Msk            (0x1ul << USPI_BUFCTL_TXCLR_Pos)                  /*!< USPI_T::BUFCTL: TXCLR Mask             */

#define USPI_BUFCTL_RXOVIEN_Pos          (14)                                              /*!< USPI_T::BUFCTL: RXOVIEN Position       */
#define USPI_BUFCTL_RXOVIEN_Msk          (0x1ul << USPI_BUFCTL_RXOVIEN_Pos)                /*!< USPI_T::BUFCTL: RXOVIEN Mask           */

#define USPI_BUFCTL_RXCLR_Pos            (15)                                              /*!< USPI_T::BUFCTL: RXCLR Position         */
#define USPI_BUFCTL_RXCLR_Msk            (0x1ul << USPI_BUFCTL_RXCLR_Pos)                  /*!< USPI_T::BUFCTL: RXCLR Mask             */

#define USPI_BUFCTL_TXRST_Pos            (16)                                              /*!< USPI_T::BUFCTL: TXRST Position         */
#define USPI_BUFCTL_TXRST_Msk            (0x1ul << USPI_BUFCTL_TXRST_Pos)                  /*!< USPI_T::BUFCTL: TXRST Mask             */

#define USPI_BUFCTL_RXRST_Pos            (17)                                              /*!< USPI_T::BUFCTL: RXRST Position         */
#define USPI_BUFCTL_RXRST_Msk            (0x1ul << USPI_BUFCTL_RXRST_Pos)                  /*!< USPI_T::BUFCTL: RXRST Mask             */

#define USPI_BUFSTS_RXEMPTY_Pos          (0)                                               /*!< USPI_T::BUFSTS: RXEMPTY Position       */
#define USPI_BUFSTS_RXEMPTY_Msk          (0x1ul << USPI_BUFSTS_RXEMPTY_Pos)                /*!< USPI_T::BUFSTS: RXEMPTY Mask           */

#define USPI_BUFSTS_RXFULL_Pos           (1)                                               /*!< USPI_T::BUFSTS: RXFULL Position        */
#define USPI_BUFSTS_RXFULL_Msk           (0x1ul << USPI_BUFSTS_RXFULL_Pos)                 /*!< USPI_T::BUFSTS: RXFULL Mask            */

#define USPI_BUFSTS_RXOVIF_Pos           (3)                                               /*!< USPI_T::BUFSTS: RXOVIF Position        */
#define USPI_BUFSTS_RXOVIF_Msk           (0x1ul << USPI_BUFSTS_RXOVIF_Pos)                 /*!< USPI_T::BUFSTS: RXOVIF Mask            */

#define USPI_BUFSTS_TXEMPTY_Pos          (8)                                               /*!< USPI_T::BUFSTS: TXEMPTY Position       */
#define USPI_BUFSTS_TXEMPTY_Msk          (0x1ul << USPI_BUFSTS_TXEMPTY_Pos)                /*!< USPI_T::BUFSTS: TXEMPTY Mask           */

#define USPI_BUFSTS_TXFULL_Pos           (9)                                               /*!< USPI_T::BUFSTS: TXFULL Position        */
#define USPI_BUFSTS_TXFULL_Msk           (0x1ul << USPI_BUFSTS_TXFULL_Pos)                 /*!< USPI_T::BUFSTS: TXFULL Mask            */

#define USPI_BUFSTS_TXUDRIF_Pos          (11)                                              /*!< USPI_T::BUFSTS: TXUDRIF Position       */
#define USPI_BUFSTS_TXUDRIF_Msk          (0x1ul << USPI_BUFSTS_TXUDRIF_Pos)                /*!< USPI_T::BUFSTS: TXUDRIF Mask           */

#define USPI_PDMACTL_PDMARST_Pos         (0)                                               /*!< USPI_T::PDMACTL: PDMARST Position      */
#define USPI_PDMACTL_PDMARST_Msk         (0x1ul << USPI_PDMACTL_PDMARST_Pos)               /*!< USPI_T::PDMACTL: PDMARST Mask          */

#define USPI_PDMACTL_TXPDMAEN_Pos        (1)                                               /*!< USPI_T::PDMACTL: TXPDMAEN Position     */
#define USPI_PDMACTL_TXPDMAEN_Msk        (0x1ul << USPI_PDMACTL_TXPDMAEN_Pos)              /*!< USPI_T::PDMACTL: TXPDMAEN Mask         */

#define USPI_PDMACTL_RXPDMAEN_Pos        (2)                                               /*!< USPI_T::PDMACTL: RXPDMAEN Position     */
#define USPI_PDMACTL_RXPDMAEN_Msk        (0x1ul << USPI_PDMACTL_RXPDMAEN_Pos)              /*!< USPI_T::PDMACTL: RXPDMAEN Mask         */

#define USPI_PDMACTL_PDMAEN_Pos          (3)                                               /*!< USPI_T::PDMACTL: PDMAEN Position       */
#define USPI_PDMACTL_PDMAEN_Msk          (0x1ul << USPI_PDMACTL_PDMAEN_Pos)                /*!< USPI_T::PDMACTL: PDMAEN Mask           */

#define USPI_WKCTL_WKEN_Pos              (0)                                               /*!< USPI_T::WKCTL: WKEN Position           */
#define USPI_WKCTL_WKEN_Msk              (0x1ul << USPI_WKCTL_WKEN_Pos)                    /*!< USPI_T::WKCTL: WKEN Mask               */

#define USPI_WKCTL_WKADDREN_Pos          (1)                                               /*!< USPI_T::WKCTL: WKADDREN Position       */
#define USPI_WKCTL_WKADDREN_Msk          (0x1ul << USPI_WKCTL_WKADDREN_Pos)                /*!< USPI_T::WKCTL: WKADDREN Mask           */

#define USPI_WKCTL_PDBOPT_Pos            (2)                                               /*!< USPI_T::WKCTL: PDBOPT Position         */
#define USPI_WKCTL_PDBOPT_Msk            (0x1ul << USPI_WKCTL_PDBOPT_Pos)                  /*!< USPI_T::WKCTL: PDBOPT Mask             */

#define USPI_WKSTS_WKF_Pos               (0)                                               /*!< USPI_T::WKSTS: WKF Position            */
#define USPI_WKSTS_WKF_Msk               (0x1ul << USPI_WKSTS_WKF_Pos)                     /*!< USPI_T::WKSTS: WKF Mask                */

#define USPI_PROTCTL_SLAVE_Pos           (0)                                               /*!< USPI_T::PROTCTL: SLAVE Position        */
#define USPI_PROTCTL_SLAVE_Msk           (0x1ul << USPI_PROTCTL_SLAVE_Pos)                 /*!< USPI_T::PROTCTL: SLAVE Mask            */

#define USPI_PROTCTL_SLV3WIRE_Pos        (1)                                               /*!< USPI_T::PROTCTL: SLV3WIRE Position     */
#define USPI_PROTCTL_SLV3WIRE_Msk        (0x1ul << USPI_PROTCTL_SLV3WIRE_Pos)              /*!< USPI_T::PROTCTL: SLV3WIRE Mask         */

#define USPI_PROTCTL_SS_Pos              (2)                                               /*!< USPI_T::PROTCTL: SS Position           */
#define USPI_PROTCTL_SS_Msk              (0x1ul << USPI_PROTCTL_SS_Pos)                    /*!< USPI_T::PROTCTL: SS Mask               */

#define USPI_PROTCTL_AUTOSS_Pos          (3)                                               /*!< USPI_T::PROTCTL: AUTOSS Position       */
#define USPI_PROTCTL_AUTOSS_Msk          (0x1ul << USPI_PROTCTL_AUTOSS_Pos)                /*!< USPI_T::PROTCTL: AUTOSS Mask           */

#define USPI_PROTCTL_SCLKMODE_Pos        (6)                                               /*!< USPI_T::PROTCTL: SCLKMODE Position     */
#define USPI_PROTCTL_SCLKMODE_Msk        (0x3ul << USPI_PROTCTL_SCLKMODE_Pos)              /*!< USPI_T::PROTCTL: SCLKMODE Mask         */

#define USPI_PROTCTL_SUSPITV_Pos         (8)                                               /*!< USPI_T::PROTCTL: SUSPITV Position      */
#define USPI_PROTCTL_SUSPITV_Msk         (0xful << USPI_PROTCTL_SUSPITV_Pos)               /*!< USPI_T::PROTCTL: SUSPITV Mask          */

#define USPI_PROTCTL_TSMSEL_Pos          (12)                                              /*!< USPI_T::PROTCTL: TSMSEL Position       */
#define USPI_PROTCTL_TSMSEL_Msk          (0x7ul << USPI_PROTCTL_TSMSEL_Pos)                /*!< USPI_T::PROTCTL: TSMSEL Mask           */

#define USPI_PROTCTL_SLVTOCNT_Pos        (16)                                              /*!< USPI_T::PROTCTL: SLVTOCNT Position     */
#define USPI_PROTCTL_SLVTOCNT_Msk        (0x3fful << USPI_PROTCTL_SLVTOCNT_Pos)            /*!< USPI_T::PROTCTL: SLVTOCNT Mask         */

#define USPI_PROTCTL_TXUDRPOL_Pos        (28)                                              /*!< USPI_T::PROTCTL: TXUDRPOL Position     */
#define USPI_PROTCTL_TXUDRPOL_Msk        (0x1ul << USPI_PROTCTL_TXUDRPOL_Pos)              /*!< USPI_T::PROTCTL: TXUDRPOL Mask         */

#define USPI_PROTCTL_PROTEN_Pos          (31)                                              /*!< USPI_T::PROTCTL: PROTEN Position       */
#define USPI_PROTCTL_PROTEN_Msk          (0x1ul << USPI_PROTCTL_PROTEN_Pos)                /*!< USPI_T::PROTCTL: PROTEN Mask           */

#define USPI_PROTIEN_SSINAIEN_Pos        (0)                                               /*!< USPI_T::PROTIEN: SSINAIEN Position     */
#define USPI_PROTIEN_SSINAIEN_Msk        (0x1ul << USPI_PROTIEN_SSINAIEN_Pos)              /*!< USPI_T::PROTIEN: SSINAIEN Mask         */

#define USPI_PROTIEN_SSACTIEN_Pos        (1)                                               /*!< USPI_T::PROTIEN: SSACTIEN Position     */
#define USPI_PROTIEN_SSACTIEN_Msk        (0x1ul << USPI_PROTIEN_SSACTIEN_Pos)              /*!< USPI_T::PROTIEN: SSACTIEN Mask         */

#define USPI_PROTIEN_SLVTOIEN_Pos        (2)                                               /*!< USPI_T::PROTIEN: SLVTOIEN Position     */
#define USPI_PROTIEN_SLVTOIEN_Msk        (0x1ul << USPI_PROTIEN_SLVTOIEN_Pos)              /*!< USPI_T::PROTIEN: SLVTOIEN Mask         */

#define USPI_PROTIEN_SLVBEIEN_Pos        (3)                                               /*!< USPI_T::PROTIEN: SLVBEIEN Position     */
#define USPI_PROTIEN_SLVBEIEN_Msk        (0x1ul << USPI_PROTIEN_SLVBEIEN_Pos)              /*!< USPI_T::PROTIEN: SLVBEIEN Mask         */

#define USPI_PROTSTS_TXSTIF_Pos          (1)                                               /*!< USPI_T::PROTSTS: TXSTIF Position       */
#define USPI_PROTSTS_TXSTIF_Msk          (0x1ul << USPI_PROTSTS_TXSTIF_Pos)                /*!< USPI_T::PROTSTS: TXSTIF Mask           */

#define USPI_PROTSTS_TXENDIF_Pos         (2)                                               /*!< USPI_T::PROTSTS: TXENDIF Position      */
#define USPI_PROTSTS_TXENDIF_Msk         (0x1ul << USPI_PROTSTS_TXENDIF_Pos)               /*!< USPI_T::PROTSTS: TXENDIF Mask          */

#define USPI_PROTSTS_RXSTIF_Pos          (3)                                               /*!< USPI_T::PROTSTS: RXSTIF Position       */
#define USPI_PROTSTS_RXSTIF_Msk          (0x1ul << USPI_PROTSTS_RXSTIF_Pos)                /*!< USPI_T::PROTSTS: RXSTIF Mask           */

#define USPI_PROTSTS_RXENDIF_Pos         (4)                                               /*!< USPI_T::PROTSTS: RXENDIF Position      */
#define USPI_PROTSTS_RXENDIF_Msk         (0x1ul << USPI_PROTSTS_RXENDIF_Pos)               /*!< USPI_T::PROTSTS: RXENDIF Mask          */

#define USPI_PROTSTS_SLVTOIF_Pos         (5)                                               /*!< USPI_T::PROTSTS: SLVTOIF Position      */
#define USPI_PROTSTS_SLVTOIF_Msk         (0x1ul << USPI_PROTSTS_SLVTOIF_Pos)               /*!< USPI_T::PROTSTS: SLVTOIF Mask          */

#define USPI_PROTSTS_SLVBEIF_Pos         (6)                                               /*!< USPI_T::PROTSTS: SLVBEIF Position      */
#define USPI_PROTSTS_SLVBEIF_Msk         (0x1ul << USPI_PROTSTS_SLVBEIF_Pos)               /*!< USPI_T::PROTSTS: SLVBEIF Mask          */

#define USPI_PROTSTS_SSINAIF_Pos         (8)                                               /*!< USPI_T::PROTSTS: SSINAIF Position      */
#define USPI_PROTSTS_SSINAIF_Msk         (0x1ul << USPI_PROTSTS_SSINAIF_Pos)               /*!< USPI_T::PROTSTS: SSINAIF Mask          */

#define USPI_PROTSTS_SSACTIF_Pos         (9)                                               /*!< USPI_T::PROTSTS: SSACTIF Position      */
#define USPI_PROTSTS_SSACTIF_Msk         (0x1ul << USPI_PROTSTS_SSACTIF_Pos)               /*!< USPI_T::PROTSTS: SSACTIF Mask          */

#define USPI_PROTSTS_SSLINE_Pos          (16)                                              /*!< USPI_T::PROTSTS: SSLINE Position       */
#define USPI_PROTSTS_SSLINE_Msk          (0x1ul << USPI_PROTSTS_SSLINE_Pos)                /*!< USPI_T::PROTSTS: SSLINE Mask           */

#define USPI_PROTSTS_BUSY_Pos            (17)                                              /*!< USPI_T::PROTSTS: BUSY Position         */
#define USPI_PROTSTS_BUSY_Msk            (0x1ul << USPI_PROTSTS_BUSY_Pos)                  /*!< USPI_T::PROTSTS: BUSY Mask             */

#define USPI_PROTSTS_SLVUDR_Pos          (18)                                              /*!< USPI_T::PROTSTS: SLVUDR Position       */
#define USPI_PROTSTS_SLVUDR_Msk          (0x1ul << USPI_PROTSTS_SLVUDR_Pos)                /*!< USPI_T::PROTSTS: SLVUDR Mask           */

/**@}*/ /* USPI_CONST */
/**@}*/ /* end of USPI register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __USPI_REG_H__ */
