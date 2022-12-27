/**************************************************************************//**
 * @file     qspi_reg.h
 * @version  V1.00
 * @brief    QSPI register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __QSPI_REG_H__
#define __QSPI_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup QSPI Serial Peripheral Interface Controller(QSPI)
    Memory Mapped Structure for QSPI Controller
@{ */

typedef struct
{


    /**
@var QSPI_T::CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL
</font><br><p> <font size="2">
Offset: 0x00  QSPI Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>QSPIEN</td><td><div style="word-wrap: break-word;"><b>QSPI Transfer Control Enable Bit
</b><br>
In Master mode, the transfer will start when there is data in the FIFO buffer after this bit is set to 1
<br>
In Slave mode, this device is ready to receive data when this bit is set to 1.
<br>
0 = Transfer control Disabled.
<br>
1 = Transfer control Enabled.
<br>
Note: Before changing the configurations of QSPIx_CTL, QSPIx_CLKDIV, QSPIx_SSCTL and QSPIx_FIFOCTL registers, user shall clear the QSPIEN (QSPIx_CTL[0]) and confirm the QSPIENSTS (QSPIx_STATUS[15]) is 0.
<br>
</div></td></tr><tr><td>
[1]</td><td>RXNEG</td><td><div style="word-wrap: break-word;"><b>Receive on Negative Edge
</b><br>
0 = Received data input signal is latched on the rising edge of QSPI bus clock.
<br>
1 = Received data input signal is latched on the falling edge of QSPI bus clock.
<br>
</div></td></tr><tr><td>
[2]</td><td>TXNEG</td><td><div style="word-wrap: break-word;"><b>Transmit on Negative Edge
</b><br>
0 = Transmitted data output signal is changed on the rising edge of QSPI bus clock.
<br>
1 = Transmitted data output signal is changed on the falling edge of QSPI bus clock.
<br>
</div></td></tr><tr><td>
[3]</td><td>CLKPOL</td><td><div style="word-wrap: break-word;"><b>Clock Polarity
</b><br>
0 = QSPI bus clock is idle low.
<br>
1 = QSPI bus clock is idle high.
<br>
</div></td></tr><tr><td>
[7:4]</td><td>SUSPITV</td><td><div style="word-wrap: break-word;"><b>Suspend Interval (Master Only)
</b><br>
The four bits provide configurable suspend interval between two successive transmit/receive transaction in a transfer
<br>
The definition of the suspend interval is the interval between the last clock edge of the preceding transaction word and the first clock edge of the following transaction word
<br>
The default value is 0x3
<br>
The period of the suspend interval is obtained according to the following equation.
<br>
(SUSPITV[3:0] + 0.5) * period of QSPICLK clock cycle
<br>
Example:
<br>
SUSPITV = 0x0 .... 0.5 QSPICLK clock cycle.
<br>
SUSPITV = 0x1 .... 1.5 QSPICLK clock cycle.
<br>
.....
<br>
SUSPITV = 0xE .... 14.5 QSPICLK clock cycle.
<br>
SUSPITV = 0xF .... 15.5 QSPICLK clock cycle.
<br>
</div></td></tr><tr><td>
[12:8]</td><td>DWIDTH</td><td><div style="word-wrap: break-word;"><b>Data Width
</b><br>
This field specifies how many bits can be transmitted / received in one transaction
<br>
The minimum bit length is 8 bits and can up to 32 bits.
<br>
DWIDTH = 0x08 .... 8 bits.
<br>
DWIDTH = 0x09 .... 9 bits.
<br>
.....
<br>
DWIDTH = 0x1F .... 31 bits.
<br>
DWIDTH = 0x00 .... 32 bits.
<br>
</div></td></tr><tr><td>
[13]</td><td>LSB</td><td><div style="word-wrap: break-word;"><b>Send LSB First
</b><br>
0 = The MSB, which bit of transmit/receive register depends on the setting of DWIDTH, is transmitted/received first.
<br>
1 = The LSB, bit 0 of the QSPI TX register, is sent first to the QSPI data output pin, and the first bit received from the QSPI data input pin will be put in the LSB position of the RX register (bit 0 of QSPI_RX).
<br>
</div></td></tr><tr><td>
[14]</td><td>HALFDPX</td><td><div style="word-wrap: break-word;"><b>QSPI Half-duplex Transfer Enable Bit
</b><br>
This bit is used to select full-duplex or half-duplex for QSPI transfer
<br>
The bit field DATDIR (QSPIx_CTL[20]) can be used to set the data direction in half-duplex transfer.
<br>
0 = QSPI operates in full-duplex transfer.
<br>
1 = QSPI operates in half-duplex transfer.
<br>
</div></td></tr><tr><td>
[15]</td><td>RXONLY</td><td><div style="word-wrap: break-word;"><b>Receive-only Mode Enable Bit (Master Only)
</b><br>
This bit field is only available in Master mode
<br>
In receive-only mode, QSPI Master will generate QSPI bus clock continuously for receiving data bit from QSPI slave device and assert the BUSY status.
<br>
0 = Receive-only mode Disabled.
<br>
1 = Receive-only mode Enabled.
<br>
</div></td></tr><tr><td>
[16]</td><td>TWOBIT</td><td><div style="word-wrap: break-word;"><b>2-bit Transfer Mode Enable Bit (Only Supported in QSPI0)
</b><br>
0 = 2-Bit Transfer mode Disabled.
<br>
1 = 2-Bit Transfer mode Enabled.
<br>
Note: When 2-Bit Transfer mode is enabled, the first serial transmitted bit data is from the first FIFO buffer data, and the 2nd serial transmitted bit data is from the second FIFO buffer data
<br>
As the same as transmitted function, the first received bit data is stored into the first FIFO buffer and the 2nd received bit data is stored into the second FIFO buffer at the same time.
<br>
</div></td></tr><tr><td>
[17]</td><td>UNITIEN</td><td><div style="word-wrap: break-word;"><b>Unit Transfer Interrupt Enable Bit
</b><br>
0 = QSPI unit transfer interrupt Disabled.
<br>
1 = QSPI unit transfer interrupt Enabled.
<br>
</div></td></tr><tr><td>
[18]</td><td>SLAVE</td><td><div style="word-wrap: break-word;"><b>Slave Mode Control
</b><br>
0 = Master mode.
<br>
1 = Slave mode.
<br>
</div></td></tr><tr><td>
[19]</td><td>REORDER</td><td><div style="word-wrap: break-word;"><b>Byte Reorder Function Enable Bit
</b><br>
0 = Byte Reorder function Disabled.
<br>
1 = Byte Reorder function Enabled
<br>
A byte suspend interval will be inserted among each byte
<br>
The period of the byte suspend interval depends on the setting of SUSPITV.
<br>
Note: Byte Reorder function is only available if DWIDTH is defined as 16, 24, and 32 bits.
<br>
</div></td></tr><tr><td>
[20]</td><td>DATDIR</td><td><div style="word-wrap: break-word;"><b>Data Port Direction Control
</b><br>
This bit is used to select the data input/output direction in half-duplex transfer and Dual/Quad transfer
<br>
0 = QSPI data is input direction.
<br>
1 = QSPI data is output direction.
<br>
</div></td></tr><tr><td>
[21]</td><td>DUALIOEN</td><td><div style="word-wrap: break-word;"><b>Dual I/O Mode Enable Bit (Only Supported in QSPI0)
</b><br>
0 = Dual I/O mode Disabled.
<br>
1 = Dual I/O mode Enabled.
<br>
</div></td></tr><tr><td>
[22]</td><td>QUADIOEN</td><td><div style="word-wrap: break-word;"><b>Quad I/O Mode Enable Bit (Only Supported in QSPI0)
</b><br>
0 = Quad I/O mode Disabled.
<br>
1 = Quad I/O mode Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var QSPI_T::CLKDIV

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKDIV
</font><br><p> <font size="2">
Offset: 0x04  QSPI Clock Divider Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[8:0]</td><td>DIVIDER</td><td><div style="word-wrap: break-word;"><b>Clock Divider
</b><br>
The value in this field is the frequency divider for generating the peripheral clock, fspi_eclk, and the QSPI bus clock of QSPI Master
<br>
The frequency is obtained according to the following equation.
<br>
where
<br>
is the peripheral clock source, which is defined in the clock control register, CLK_CLKSEL2.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var QSPI_T::SSCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SSCTL
</font><br><p> <font size="2">
Offset: 0x08  QSPI Slave Select Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SS</td><td><div style="word-wrap: break-word;"><b>Slave Selection Control (Master Only)
</b><br>
If AUTOSS bit is cleared to 0,
<br>
0 = set the QSPIx_SS line to inactive state.
<br>
1 = set the QSPIx_SS line to active state.
<br>
If the AUTOSS bit is set to 1,
<br>
0 = Keep the QSPIx_SS line at inactive state.
<br>
1 = QSPIx_SS line will be automatically driven to active state for the duration of data transfer, and will be driven to inactive state for the rest of the time
<br>
The active state of QSPIx_SS is specified in SSACTPOL (QSPIx_SSCTL[2]).
<br>
</div></td></tr><tr><td>
[2]</td><td>SSACTPOL</td><td><div style="word-wrap: break-word;"><b>Slave Selection Active Polarity
</b><br>
This bit defines the active polarity of slave selection signal (QSPIx_SS).
<br>
0 = The slave selection signal QSPIx_SS is active low.
<br>
1 = The slave selection signal QSPIx_SS is active high.
<br>
</div></td></tr><tr><td>
[3]</td><td>AUTOSS</td><td><div style="word-wrap: break-word;"><b>Automatic Slave Selection Function Enable Bit (Master Only)
</b><br>
0 = Automatic slave selection function Disabled
<br>
Slave selection signal will be asserted/de-asserted according to SS (QSPIx_SSCTL[0]).
<br>
1 = Automatic slave selection function Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>SLV3WIRE</td><td><div style="word-wrap: break-word;"><b>Slave 3-wire Mode Enable Bit (Only Supported in QSPI0)
</b><br>
Slave 3-wire mode is only available in QSPI0
<br>
In Slave 3-wire mode, the QSPI controller can work with 3-wire interface including QSPI0_CLK, QSPI0_MISO and QSPI0_MOSI pins.
<br>
0 = 4-wire bi-direction interface.
<br>
1 = 3-wire bi-direction interface.
<br>
</div></td></tr><tr><td>
[5]</td><td>SLVTOIEN</td><td><div style="word-wrap: break-word;"><b>Slave Mode Time-out Interrupt Enable Bit (Only Supported in QSPI0)
</b><br>
0 = Slave mode time-out interrupt Disabled.
<br>
1 = Slave mode time-out interrupt Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>SLVTORST</td><td><div style="word-wrap: break-word;"><b>Slave Mode Time-out Reset Control (Only Supported in QSPI0)
</b><br>
0 = When Slave mode time-out event occurs, the TX and RX control circuit will not be reset.
<br>
1 = When Slave mode time-out event occurs, the TX and RX control circuit will be reset by hardware.
<br>
</div></td></tr><tr><td>
[8]</td><td>SLVBEIEN</td><td><div style="word-wrap: break-word;"><b>Slave Mode Bit Count Error Interrupt Enable Bit
</b><br>
0 = Slave mode bit count error interrupt Disabled.
<br>
1 = Slave mode bit count error interrupt Enabled.
<br>
</div></td></tr><tr><td>
[9]</td><td>SLVURIEN</td><td><div style="word-wrap: break-word;"><b>Slave Mode TX Under Run Interrupt Enable Bit
</b><br>
0 = Slave mode TX under run interrupt Disabled.
<br>
1 = Slave mode TX under run interrupt Enabled.
<br>
</div></td></tr><tr><td>
[12]</td><td>SSACTIEN</td><td><div style="word-wrap: break-word;"><b>Slave Select Active Interrupt Enable Bit
</b><br>
0 = Slave select active interrupt Disabled.
<br>
1 = Slave select active interrupt Enabled.
<br>
</div></td></tr><tr><td>
[13]</td><td>SSINAIEN</td><td><div style="word-wrap: break-word;"><b>Slave Select Inactive Interrupt Enable Bit
</b><br>
0 = Slave select inactive interrupt Disabled.
<br>
1 = Slave select inactive interrupt Enabled.
<br>
</div></td></tr><tr><td>
[31:16]</td><td>SLVTOCNT</td><td><div style="word-wrap: break-word;"><b>Slave Mode Time-out Period (Only Supported in QSPI0)
</b><br>
In Slave mode, these bits indicate the time-out period when there is bus clock input during slave select active
<br>
The clock source of the time-out counter is Slave peripheral clock
<br>
If the value is 0, it indicates the slave mode time-out function is disabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var QSPI_T::PDMACTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PDMACTL
</font><br><p> <font size="2">
Offset: 0x0C  QSPI PDMA Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>TXPDMAEN</td><td><div style="word-wrap: break-word;"><b>Transmit PDMA Enable Bit
</b><br>
0 = Transmit PDMA function Disabled.
<br>
1 = Transmit PDMA function Enabled.
<br>
Note: In QSPI Master mode with full duplex transfer, if both TX and RX PDMA functions are enabled, RX PDMA function cannot be enabled prior to TX PDMA function
<br>
User can enable TX PDMA function firstly or enable both functions simultaneously.
<br>
</div></td></tr><tr><td>
[1]</td><td>RXPDMAEN</td><td><div style="word-wrap: break-word;"><b>Receive PDMA Enable Bit
</b><br>
0 = Receive PDMA function Disabled.
<br>
1 = Receive PDMA function Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>PDMARST</td><td><div style="word-wrap: break-word;"><b>PDMA Reset
</b><br>
0 = No effect.
<br>
1 = Reset the PDMA control logic of the QSPI controller. This bit will be automatically cleared to 0.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var QSPI_T::FIFOCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">FIFOCTL
</font><br><p> <font size="2">
Offset: 0x10  QSPI FIFO Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>RXRST</td><td><div style="word-wrap: break-word;"><b>Receive Reset
</b><br>
0 = No effect.
<br>
1 = Reset receive FIFO pointer and receive circuit
<br>
The RXFULL bit will be cleared to 0 and the RXEMPTY bit will be set to 1
<br>
This bit will be cleared to 0 by hardware about 3 system clock cycles + 2 peripheral clock cycles after it is set to 1
<br>
User can read TXRXRST (QSPIx_STATUS[23]) to check if reset is accomplished or not.
<br>
</div></td></tr><tr><td>
[1]</td><td>TXRST</td><td><div style="word-wrap: break-word;"><b>Transmit Reset
</b><br>
0 = No effect.
<br>
1 = Reset transmit FIFO pointer and transmit circuit
<br>
The TXFULL bit will be cleared to 0 and the TXEMPTY bit will be set to 1
<br>
This bit will be cleared to 0 by hardware about 3 system clock cycles + 2 peripheral clock cycles after it is set to 1
<br>
User can read TXRXRST (QSPIx_STATUS[23]) to check if reset is accomplished or not.
<br>
Note: If TX underflow event occurs in QSPI Slave mode, this bit can be used to make QSPI return to idle state.
<br>
</div></td></tr><tr><td>
[2]</td><td>RXTHIEN</td><td><div style="word-wrap: break-word;"><b>Receive FIFO Threshold Interrupt Enable Bit
</b><br>
0 = RX FIFO threshold interrupt Disabled.
<br>
1 = RX FIFO threshold interrupt Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>TXTHIEN</td><td><div style="word-wrap: break-word;"><b>Transmit FIFO Threshold Interrupt Enable Bit
</b><br>
0 = TX FIFO threshold interrupt Disabled.
<br>
1 = TX FIFO threshold interrupt Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>RXTOIEN</td><td><div style="word-wrap: break-word;"><b>Slave Receive Time-out Interrupt Enable Bit
</b><br>
0 = Receive time-out interrupt Disabled.
<br>
1 = Receive time-out interrupt Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>RXOVIEN</td><td><div style="word-wrap: break-word;"><b>Receive FIFO Overrun Interrupt Enable Bit
</b><br>
0 = Receive FIFO overrun interrupt Disabled.
<br>
1 = Receive FIFO overrun interrupt Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>TXUFPOL</td><td><div style="word-wrap: break-word;"><b>TX Underflow Data Polarity
</b><br>
0 = The QSPI data out is keep 0 if there is TX underflow event in Slave mode.
<br>
1 = The QSPI data out is keep 1 if there is TX underflow event in Slave mode.
<br>
Note:
<br>
1. The TX underflow event occurs if there is no any data in TX FIFO when the slave selection signal is active.
<br>
2. When TX underflow event occurs, QSPIx_MISO pin state will be determined by this setting even though TX FIFO is not empty afterward
<br>
Data stored in TX FIFO will be sent through QSPIx_MISO pin in the next transfer frame.
<br>
</div></td></tr><tr><td>
[7]</td><td>TXUFIEN</td><td><div style="word-wrap: break-word;"><b>TX Underflow Interrupt Enable Bit
</b><br>
When TX underflow event occurs in Slave mode, TXUFIF (QSPIx_STATUS[19]) will be set to 1
<br>
This bit is used to enable the TX underflow interrupt.
<br>
0 = Slave TX underflow interrupt Disabled.
<br>
1 = Slave TX underflow interrupt Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>RXFBCLR</td><td><div style="word-wrap: break-word;"><b>Receive FIFO Buffer Clear
</b><br>
0 = No effect.
<br>
1 = Clear receive FIFO pointer
<br>
The RXFULL bit will be cleared to 0 and the RXEMPTY bit will be set to 1
<br>
This bit will be cleared to 0 by hardware about 1 system clock after it is set to 1.
<br>
Note: The RX shift register will not be cleared.
<br>
</div></td></tr><tr><td>
[9]</td><td>TXFBCLR</td><td><div style="word-wrap: break-word;"><b>Transmit FIFO Buffer Clear
</b><br>
0 = No effect.
<br>
1 = Clear transmit FIFO pointer
<br>
The TXFULL bit will be cleared to 0 and the TXEMPTY bit will be set to 1
<br>
This bit will be cleared to 0 by hardware about 1 system clock after it is set to 1.
<br>
Note: The TX shift register will not be cleared.
<br>
</div></td></tr><tr><td>
[26:24]</td><td>RXTH</td><td><div style="word-wrap: break-word;"><b>Receive FIFO Threshold
</b><br>
If the valid data count of the receive FIFO buffer is larger than the RXTH setting, the RXTHIF bit will be set to 1, else the RXTHIF bit will be cleared to 0
<br>
</div></td></tr><tr><td>
[30:28]</td><td>TXTH</td><td><div style="word-wrap: break-word;"><b>Transmit FIFO Threshold
</b><br>
If the valid data count of the transmit FIFO buffer is less than or equal to the TXTH setting, the TXTHIF bit will be set to 1, else the TXTHIF bit will be cleared to 0
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var QSPI_T::STATUS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STATUS
</font><br><p> <font size="2">
Offset: 0x14  QSPI Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BUSY</td><td><div style="word-wrap: break-word;"><b>Busy Status (Read Only)
</b><br>
0 = QSPI controller is in idle state.
<br>
1 = QSPI controller is in busy state.
<br>
The following listing are the bus busy conditions:
<br>
a. QSPIx_CTL[0] = 1 and TXEMPTY = 0.
<br>
b
<br>
For QSPI Master mode, QSPIx_CTL[0] = 1 and TXEMPTY = 1 but the current transaction is not finished yet.
<br>
c. For QSPI Master mode, QSPIx_CTL[0] = 1 and RXONLY = 1.
<br>
d
<br>
For QSPI Slave mode, the QSPIx_CTL[0] = 1 and there is serial clock input into the QSPI core logic when slave select is active.
<br>
For QSPI Slave mode, the QSPIx_CTL[0] = 1 and the transmit buffer or transmit shift register is not empty even if the slave select is inactive.
<br>
</div></td></tr><tr><td>
[1]</td><td>UNITIF</td><td><div style="word-wrap: break-word;"><b>Unit Transfer Interrupt Flag
</b><br>
0 = No transaction has been finished since this bit was cleared to 0.
<br>
1 = QSPI controller has finished one unit transfer.
<br>
Note: This bit will be cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[2]</td><td>SSACTIF</td><td><div style="word-wrap: break-word;"><b>Slave Select Active Interrupt Flag
</b><br>
0 = Slave select active interrupt was cleared or not occurred.
<br>
1 = Slave select active interrupt event occurred.
<br>
Note: Only available in Slave mode. This bit will be cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[3]</td><td>SSINAIF</td><td><div style="word-wrap: break-word;"><b>Slave Select Inactive Interrupt Flag
</b><br>
0 = Slave select inactive interrupt was cleared or not occurred.
<br>
1 = Slave select inactive interrupt event occurred.
<br>
Note: Only available in Slave mode. This bit will be cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[4]</td><td>SSLINE</td><td><div style="word-wrap: break-word;"><b>Slave Select Line Bus Status (Read Only)
</b><br>
0 = The slave select line status is 0.
<br>
1 = The slave select line status is 1.
<br>
Note: This bit is only available in Slave mode
<br>
If SSACTPOL (QSPIx_SSCTL[2]) is set 0, and the SSLINE is 1, the QSPI slave select is in inactive status.
<br>
</div></td></tr><tr><td>
[5]</td><td>SLVTOIF</td><td><div style="word-wrap: break-word;"><b>Slave Time-out Interrupt Flag (Only Supported in QSPI0)
</b><br>
When the slave select is active and the value of SLVTOCNT is not 0, as the bus clock is detected, the slave time-out counter in QSPI controller logic will be started
<br>
When the value of time-out counter is greater than or equal to the value of SLVTOCNT (QSPI_SSCTL[31:16]) before one transaction is done, the slave time-out interrupt event will be asserted.
<br>
0 = Slave time-out is not active.
<br>
1 = Slave time-out is active.
<br>
Note: This bit will be cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[6]</td><td>SLVBEIF</td><td><div style="word-wrap: break-word;"><b>Slave Mode Bit Count Error Interrupt Flag
</b><br>
In Slave mode, when the slave select line goes to inactive state, if bit counter is mismatch with DWIDTH, this interrupt flag will be set to 1.
<br>
0 = No Slave mode bit count error event.
<br>
1 = Slave mode bit count error event occurs.
<br>
Note: If the slave select active but there is no any bus clock input, the SLVBEIF also active when the slave select goes to inactive state
<br>
This bit will be cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[7]</td><td>SLVURIF</td><td><div style="word-wrap: break-word;"><b>Slave Mode TX Under Run Interrupt Flag
</b><br>
In Slave mode, if TX underflow event occurs and the slave select line goes to inactive state, this interrupt flag will be set to 1.
<br>
0 = No Slave TX under run event.
<br>
1 = Slave TX under run event occurs.
<br>
Note: This bit will be cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[8]</td><td>RXEMPTY</td><td><div style="word-wrap: break-word;"><b>Receive FIFO Buffer Empty Indicator (Read Only)
</b><br>
0 = Receive FIFO buffer is not empty.
<br>
1 = Receive FIFO buffer is empty.
<br>
</div></td></tr><tr><td>
[9]</td><td>RXFULL</td><td><div style="word-wrap: break-word;"><b>Receive FIFO Buffer Full Indicator (Read Only)
</b><br>
0 = Receive FIFO buffer is not full.
<br>
1 = Receive FIFO buffer is full.
<br>
</div></td></tr><tr><td>
[10]</td><td>RXTHIF</td><td><div style="word-wrap: break-word;"><b>Receive FIFO Threshold Interrupt Flag (Read Only)
</b><br>
0 = The valid data count within the receive FIFO buffer is smaller than or equal to the setting value of RXTH.
<br>
1 = The valid data count within the receive FIFO buffer is larger than the setting value of RXTH.
<br>
</div></td></tr><tr><td>
[11]</td><td>RXOVIF</td><td><div style="word-wrap: break-word;"><b>Receive FIFO Overrun Interrupt Flag
</b><br>
When the receive FIFO buffer is full, the follow-up data will be dropped and this bit will be set to 1.
<br>
0 = No FIFO is overrun.
<br>
1 = Receive FIFO is overrun.
<br>
Note: This bit will be cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[12]</td><td>RXTOIF</td><td><div style="word-wrap: break-word;"><b>Receive Time-out Interrupt Flag
</b><br>
0 = No receive FIFO time-out event.
<br>
1 = Receive FIFO buffer is not empty and no read operation on receive FIFO buffer over 64 QSPI peripheral clock periods in Master mode or over 576 QSPI peripheral clock periods in Slave mode
<br>
When the received FIFO buffer is read by software, the time-out status will be cleared automatically.
<br>
Note: This bit will be cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[15]</td><td>QSPIENSTS</td><td><div style="word-wrap: break-word;"><b>QSPI Enable Status (Read Only)
</b><br>
0 = The QSPI controller is disabled.
<br>
1 = The QSPI controller is enabled.
<br>
Note: The QSPI peripheral clock is asynchronous with the system clock
<br>
In order to make sure the QSPI control logic is disabled, this bit indicates the real status of QSPI controller.
<br>
</div></td></tr><tr><td>
[16]</td><td>TXEMPTY</td><td><div style="word-wrap: break-word;"><b>Transmit FIFO Buffer Empty Indicator (Read Only)
</b><br>
0 = Transmit FIFO buffer is not empty.
<br>
1 = Transmit FIFO buffer is empty.
<br>
</div></td></tr><tr><td>
[17]</td><td>TXFULL</td><td><div style="word-wrap: break-word;"><b>Transmit FIFO Buffer Full Indicator (Read Only)
</b><br>
0 = Transmit FIFO buffer is not full.
<br>
1 = Transmit FIFO buffer is full.
<br>
</div></td></tr><tr><td>
[18]</td><td>TXTHIF</td><td><div style="word-wrap: break-word;"><b>Transmit FIFO Threshold Interrupt Flag (Read Only)
</b><br>
0 = The valid data count within the transmit FIFO buffer is larger than the setting value of TXTH.
<br>
1 = The valid data count within the transmit FIFO buffer is less than or equal to the setting value of TXTH.
<br>
</div></td></tr><tr><td>
[19]</td><td>TXUFIF</td><td><div style="word-wrap: break-word;"><b>TX Underflow Interrupt Flag
</b><br>
When the TX underflow event occurs, this bit will be set to 1, the state of data output pin depends on the setting of TXUFPOL.
<br>
0 = No effect.
<br>
1 = No data in Transmit FIFO and TX shift register when the slave selection signal is active.
<br>
Note 1: This bit will be cleared by writing 1 to it.
<br>
Note 2: If reset slave's transmission circuit when slave selection signal is active, this flag will be set to 1 after 2 peripheral clock cycles + 3 system clock cycles since the reset operation is done.
<br>
</div></td></tr><tr><td>
[23]</td><td>TXRXRST</td><td><div style="word-wrap: break-word;"><b>TX or RX Reset Status (Read Only)
</b><br>
0 = The reset function of TXRST or RXRST is done.
<br>
1 = Doing the reset function of TXRST or RXRST.
<br>
Note: Both the reset operations of TXRST and RXRST need 3 system clock cycles + 2 peripheral clock cycles
<br>
User can check the status of this bit to monitor the reset function is doing or done.
<br>
</div></td></tr><tr><td>
[27:24]</td><td>RXCNT</td><td><div style="word-wrap: break-word;"><b>Receive FIFO Data Count (Read Only)
</b><br>
This bit field indicates the valid data count of receive FIFO buffer.
<br>
</div></td></tr><tr><td>
[31:28]</td><td>TXCNT</td><td><div style="word-wrap: break-word;"><b>Transmit FIFO Data Count (Read Only)
</b><br>
This bit field indicates the valid data count of transmit FIFO buffer.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var QSPI_T::TX

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TX
</font><br><p> <font size="2">
Offset: 0x20  QSPI Data Transmit Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>TX</td><td><div style="word-wrap: break-word;"><b>Data Transmit Register
</b><br>
The data transmit registers pass through the transmitted data into the 4-level transmit FIFO buffers
<br>
The number of valid bits depends on the setting of DWIDTH (QSPIx_CTL[12:8]) in SPI mode.
<br>
In SPI mode, if DWIDTH is set to 0x08, the bits TX[7:0] will be transmitted
<br>
If DWIDTH is set to 0x00 , the QSPI controller will perform a 32-bit transfer.
<br>
If WDWIDTH is set as 0x0, 0x1, or 0x3, all bits of this field are valid
<br>
Note: In Master mode, QSPI controller will start to transfer the QSPI bus clock after 1 APB clock and 6 peripheral clock cycles after user writes to this register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var QSPI_T::RX

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">RX
</font><br><p> <font size="2">
Offset: 0x30  QSPI Data Receive Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>RX</td><td><div style="word-wrap: break-word;"><b>Data Receive Register
</b><br>
There are 4-level FIFO buffers in this controller
<br>
The data receive register holds the data received from QSPI data input pin
<br>
This is a read only register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CTL;                   /*!< [0x0000] QSPI Control Register                                             */
    __IO uint32_t CLKDIV;                /*!< [0x0004] QSPI Clock Divider Register                                       */
    __IO uint32_t SSCTL;                 /*!< [0x0008] QSPI Slave Select Control Register                                */
    __IO uint32_t PDMACTL;               /*!< [0x000c] QSPI PDMA Control Register                                        */
    __IO uint32_t FIFOCTL;               /*!< [0x0010] QSPI FIFO Control Register                                        */
    __IO uint32_t STATUS;                /*!< [0x0014] QSPI Status Register                                              */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[2];
    /// @endcond //HIDDEN_SYMBOLS
    __O  uint32_t TX;                    /*!< [0x0020] QSPI Data Transmit Register                                       */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[3];
    /// @endcond //HIDDEN_SYMBOLS
    __I  uint32_t RX;                    /*!< [0x0030] QSPI Data Receive Register                                        */

} QSPI_T;

/**
    @addtogroup QSPI_CONST QSPI Bit Field Definition
    Constant Definitions for QSPI Controller
@{ */

#define QSPI_CTL_QSPIEN_Pos               (0)                                                /*!< QSPI_T::CTL: QSPIEN Position             */
#define QSPI_CTL_QSPIEN_Msk               (0x1ul << QSPI_CTL_QSPIEN_Pos)                     /*!< QSPI_T::CTL: QSPIEN Mask                 */

#define QSPI_CTL_RXNEG_Pos                (1)                                                /*!< QSPI_T::CTL: RXNEG Position             */
#define QSPI_CTL_RXNEG_Msk                (0x1ul << QSPI_CTL_RXNEG_Pos)                      /*!< QSPI_T::CTL: RXNEG Mask                 */

#define QSPI_CTL_TXNEG_Pos                (2)                                                /*!< QSPI_T::CTL: TXNEG Position             */
#define QSPI_CTL_TXNEG_Msk                (0x1ul << QSPI_CTL_TXNEG_Pos)                      /*!< QSPI_T::CTL: TXNEG Mask                 */

#define QSPI_CTL_CLKPOL_Pos               (3)                                                /*!< QSPI_T::CTL: CLKPOL Position            */
#define QSPI_CTL_CLKPOL_Msk               (0x1ul << QSPI_CTL_CLKPOL_Pos)                     /*!< QSPI_T::CTL: CLKPOL Mask                */

#define QSPI_CTL_SUSPITV_Pos              (4)                                                /*!< QSPI_T::CTL: SUSPITV Position           */
#define QSPI_CTL_SUSPITV_Msk              (0xful << QSPI_CTL_SUSPITV_Pos)                    /*!< QSPI_T::CTL: SUSPITV Mask               */

#define QSPI_CTL_DWIDTH_Pos               (8)                                                /*!< QSPI_T::CTL: DWIDTH Position            */
#define QSPI_CTL_DWIDTH_Msk               (0x1ful << QSPI_CTL_DWIDTH_Pos)                    /*!< QSPI_T::CTL: DWIDTH Mask                */

#define QSPI_CTL_LSB_Pos                  (13)                                               /*!< QSPI_T::CTL: LSB Position               */
#define QSPI_CTL_LSB_Msk                  (0x1ul << QSPI_CTL_LSB_Pos)                        /*!< QSPI_T::CTL: LSB Mask                   */

#define QSPI_CTL_HALFDPX_Pos              (14)                                               /*!< QSPI_T::CTL: HALFDPX Position           */
#define QSPI_CTL_HALFDPX_Msk              (0x1ul << QSPI_CTL_HALFDPX_Pos)                    /*!< QSPI_T::CTL: HALFDPX Mask               */

#define QSPI_CTL_RXONLY_Pos               (15)                                               /*!< QSPI_T::CTL: RXONLY Position            */
#define QSPI_CTL_RXONLY_Msk               (0x1ul << QSPI_CTL_RXONLY_Pos)                     /*!< QSPI_T::CTL: RXONLY Mask                */

#define QSPI_CTL_TWOBIT_Pos               (16)                                               /*!< QSPI_T::CTL: TWOBIT Position            */
#define QSPI_CTL_TWOBIT_Msk               (0x1ul << QSPI_CTL_TWOBIT_Pos)                     /*!< QSPI_T::CTL: TWOBIT Mask                */

#define QSPI_CTL_UNITIEN_Pos              (17)                                               /*!< QSPI_T::CTL: UNITIEN Position           */
#define QSPI_CTL_UNITIEN_Msk              (0x1ul << QSPI_CTL_UNITIEN_Pos)                    /*!< QSPI_T::CTL: UNITIEN Mask               */

#define QSPI_CTL_SLAVE_Pos                (18)                                               /*!< QSPI_T::CTL: SLAVE Position             */
#define QSPI_CTL_SLAVE_Msk                (0x1ul << QSPI_CTL_SLAVE_Pos)                      /*!< QSPI_T::CTL: SLAVE Mask                 */

#define QSPI_CTL_REORDER_Pos              (19)                                               /*!< QSPI_T::CTL: REORDER Position           */
#define QSPI_CTL_REORDER_Msk              (0x1ul << QSPI_CTL_REORDER_Pos)                    /*!< QSPI_T::CTL: REORDER Mask               */

#define QSPI_CTL_DATDIR_Pos               (20)                                               /*!< QSPI_T::CTL: DATDIR Position            */
#define QSPI_CTL_DATDIR_Msk               (0x1ul << QSPI_CTL_DATDIR_Pos)                     /*!< QSPI_T::CTL: DATDIR Mask                */

#define QSPI_CTL_DUALIOEN_Pos             (21)                                               /*!< QSPI_T::CTL: DUALIOEN Position          */
#define QSPI_CTL_DUALIOEN_Msk             (0x1ul << QSPI_CTL_DUALIOEN_Pos)                   /*!< QSPI_T::CTL: DUALIOEN Mask              */

#define QSPI_CTL_QUADIOEN_Pos             (22)                                               /*!< QSPI_T::CTL: QUADIOEN Position          */
#define QSPI_CTL_QUADIOEN_Msk             (0x1ul << QSPI_CTL_QUADIOEN_Pos)                   /*!< QSPI_T::CTL: QUADIOEN Mask              */

#define QSPI_CLKDIV_DIVIDER_Pos           (0)                                                /*!< QSPI_T::CLKDIV: DIVIDER Position        */
#define QSPI_CLKDIV_DIVIDER_Msk           (0x1fful << QSPI_CLKDIV_DIVIDER_Pos)               /*!< QSPI_T::CLKDIV: DIVIDER Mask            */

#define QSPI_SSCTL_SS_Pos                 (0)                                                /*!< QSPI_T::SSCTL: SS Position              */
#define QSPI_SSCTL_SS_Msk                 (0x1ul << QSPI_SSCTL_SS_Pos)                       /*!< QSPI_T::SSCTL: SS Mask                  */

#define QSPI_SSCTL_SSACTPOL_Pos           (2)                                                /*!< QSPI_T::SSCTL: SSACTPOL Position        */
#define QSPI_SSCTL_SSACTPOL_Msk           (0x1ul << QSPI_SSCTL_SSACTPOL_Pos)                 /*!< QSPI_T::SSCTL: SSACTPOL Mask            */

#define QSPI_SSCTL_AUTOSS_Pos             (3)                                                /*!< QSPI_T::SSCTL: AUTOSS Position          */
#define QSPI_SSCTL_AUTOSS_Msk             (0x1ul << QSPI_SSCTL_AUTOSS_Pos)                   /*!< QSPI_T::SSCTL: AUTOSS Mask              */

#define QSPI_SSCTL_SLV3WIRE_Pos           (4)                                                /*!< QSPI_T::SSCTL: SLV3WIRE Position        */
#define QSPI_SSCTL_SLV3WIRE_Msk           (0x1ul << QSPI_SSCTL_SLV3WIRE_Pos)                 /*!< QSPI_T::SSCTL: SLV3WIRE Mask            */

#define QSPI_SSCTL_SLVTOIEN_Pos           (5)                                                /*!< QSPI_T::SSCTL: SLVTOIEN Position        */
#define QSPI_SSCTL_SLVTOIEN_Msk           (0x1ul << QSPI_SSCTL_SLVTOIEN_Pos)                 /*!< QSPI_T::SSCTL: SLVTOIEN Mask            */

#define QSPI_SSCTL_SLVTORST_Pos           (6)                                                /*!< QSPI_T::SSCTL: SLVTORST Position        */
#define QSPI_SSCTL_SLVTORST_Msk           (0x1ul << QSPI_SSCTL_SLVTORST_Pos)                 /*!< QSPI_T::SSCTL: SLVTORST Mask            */

#define QSPI_SSCTL_SLVBEIEN_Pos           (8)                                                /*!< QSPI_T::SSCTL: SLVBEIEN Position        */
#define QSPI_SSCTL_SLVBEIEN_Msk           (0x1ul << QSPI_SSCTL_SLVBEIEN_Pos)                 /*!< QSPI_T::SSCTL: SLVBEIEN Mask            */

#define QSPI_SSCTL_SLVURIEN_Pos           (9)                                                /*!< QSPI_T::SSCTL: SLVURIEN Position        */
#define QSPI_SSCTL_SLVURIEN_Msk           (0x1ul << QSPI_SSCTL_SLVURIEN_Pos)                 /*!< QSPI_T::SSCTL: SLVURIEN Mask            */

#define QSPI_SSCTL_SSACTIEN_Pos           (12)                                               /*!< QSPI_T::SSCTL: SSACTIEN Position        */
#define QSPI_SSCTL_SSACTIEN_Msk           (0x1ul << QSPI_SSCTL_SSACTIEN_Pos)                 /*!< QSPI_T::SSCTL: SSACTIEN Mask            */

#define QSPI_SSCTL_SSINAIEN_Pos           (13)                                               /*!< QSPI_T::SSCTL: SSINAIEN Position        */
#define QSPI_SSCTL_SSINAIEN_Msk           (0x1ul << QSPI_SSCTL_SSINAIEN_Pos)                 /*!< QSPI_T::SSCTL: SSINAIEN Mask            */

#define QSPI_SSCTL_SLVTOCNT_Pos           (16)                                               /*!< QSPI_T::SSCTL: SLVTOCNT Position        */
#define QSPI_SSCTL_SLVTOCNT_Msk           (0xfffful << QSPI_SSCTL_SLVTOCNT_Pos)              /*!< QSPI_T::SSCTL: SLVTOCNT Mask            */

#define QSPI_PDMACTL_TXPDMAEN_Pos         (0)                                                /*!< QSPI_T::PDMACTL: TXPDMAEN Position      */
#define QSPI_PDMACTL_TXPDMAEN_Msk         (0x1ul << QSPI_PDMACTL_TXPDMAEN_Pos)               /*!< QSPI_T::PDMACTL: TXPDMAEN Mask          */

#define QSPI_PDMACTL_RXPDMAEN_Pos         (1)                                                /*!< QSPI_T::PDMACTL: RXPDMAEN Position      */
#define QSPI_PDMACTL_RXPDMAEN_Msk         (0x1ul << QSPI_PDMACTL_RXPDMAEN_Pos)               /*!< QSPI_T::PDMACTL: RXPDMAEN Mask          */

#define QSPI_PDMACTL_PDMARST_Pos          (2)                                                /*!< QSPI_T::PDMACTL: PDMARST Position       */
#define QSPI_PDMACTL_PDMARST_Msk          (0x1ul << QSPI_PDMACTL_PDMARST_Pos)                /*!< QSPI_T::PDMACTL: PDMARST Mask           */

#define QSPI_FIFOCTL_RXRST_Pos            (0)                                                /*!< QSPI_T::FIFOCTL: RXRST Position         */
#define QSPI_FIFOCTL_RXRST_Msk            (0x1ul << QSPI_FIFOCTL_RXRST_Pos)                  /*!< QSPI_T::FIFOCTL: RXRST Mask             */

#define QSPI_FIFOCTL_TXRST_Pos            (1)                                                /*!< QSPI_T::FIFOCTL: TXRST Position         */
#define QSPI_FIFOCTL_TXRST_Msk            (0x1ul << QSPI_FIFOCTL_TXRST_Pos)                  /*!< QSPI_T::FIFOCTL: TXRST Mask             */

#define QSPI_FIFOCTL_RXTHIEN_Pos          (2)                                                /*!< QSPI_T::FIFOCTL: RXTHIEN Position       */
#define QSPI_FIFOCTL_RXTHIEN_Msk          (0x1ul << QSPI_FIFOCTL_RXTHIEN_Pos)                /*!< QSPI_T::FIFOCTL: RXTHIEN Mask           */

#define QSPI_FIFOCTL_TXTHIEN_Pos          (3)                                                /*!< QSPI_T::FIFOCTL: TXTHIEN Position       */
#define QSPI_FIFOCTL_TXTHIEN_Msk          (0x1ul << QSPI_FIFOCTL_TXTHIEN_Pos)                /*!< QSPI_T::FIFOCTL: TXTHIEN Mask           */

#define QSPI_FIFOCTL_RXTOIEN_Pos          (4)                                                /*!< QSPI_T::FIFOCTL: RXTOIEN Position       */
#define QSPI_FIFOCTL_RXTOIEN_Msk          (0x1ul << QSPI_FIFOCTL_RXTOIEN_Pos)                /*!< QSPI_T::FIFOCTL: RXTOIEN Mask           */

#define QSPI_FIFOCTL_RXOVIEN_Pos          (5)                                                /*!< QSPI_T::FIFOCTL: RXOVIEN Position       */
#define QSPI_FIFOCTL_RXOVIEN_Msk          (0x1ul << QSPI_FIFOCTL_RXOVIEN_Pos)                /*!< QSPI_T::FIFOCTL: RXOVIEN Mask           */

#define QSPI_FIFOCTL_TXUFPOL_Pos          (6)                                                /*!< QSPI_T::FIFOCTL: TXUFPOL Position       */
#define QSPI_FIFOCTL_TXUFPOL_Msk          (0x1ul << QSPI_FIFOCTL_TXUFPOL_Pos)                /*!< QSPI_T::FIFOCTL: TXUFPOL Mask           */

#define QSPI_FIFOCTL_TXUFIEN_Pos          (7)                                                /*!< QSPI_T::FIFOCTL: TXUFIEN Position       */
#define QSPI_FIFOCTL_TXUFIEN_Msk          (0x1ul << QSPI_FIFOCTL_TXUFIEN_Pos)                /*!< QSPI_T::FIFOCTL: TXUFIEN Mask           */

#define QSPI_FIFOCTL_RXFBCLR_Pos          (8)                                                /*!< QSPI_T::FIFOCTL: RXFBCLR Position       */
#define QSPI_FIFOCTL_RXFBCLR_Msk          (0x1ul << QSPI_FIFOCTL_RXFBCLR_Pos)                /*!< QSPI_T::FIFOCTL: RXFBCLR Mask           */

#define QSPI_FIFOCTL_TXFBCLR_Pos          (9)                                                /*!< QSPI_T::FIFOCTL: TXFBCLR Position       */
#define QSPI_FIFOCTL_TXFBCLR_Msk          (0x1ul << QSPI_FIFOCTL_TXFBCLR_Pos)                /*!< QSPI_T::FIFOCTL: TXFBCLR Mask           */

#define QSPI_FIFOCTL_RXTH_Pos             (24)                                               /*!< QSPI_T::FIFOCTL: RXTH Position          */
#define QSPI_FIFOCTL_RXTH_Msk             (0x7ul << QSPI_FIFOCTL_RXTH_Pos)                   /*!< QSPI_T::FIFOCTL: RXTH Mask              */

#define QSPI_FIFOCTL_TXTH_Pos             (28)                                               /*!< QSPI_T::FIFOCTL: TXTH Position          */
#define QSPI_FIFOCTL_TXTH_Msk             (0x7ul << QSPI_FIFOCTL_TXTH_Pos)                   /*!< QSPI_T::FIFOCTL: TXTH Mask              */

#define QSPI_STATUS_BUSY_Pos              (0)                                                /*!< QSPI_T::STATUS: BUSY Position           */
#define QSPI_STATUS_BUSY_Msk              (0x1ul << QSPI_STATUS_BUSY_Pos)                    /*!< QSPI_T::STATUS: BUSY Mask               */

#define QSPI_STATUS_UNITIF_Pos            (1)                                                /*!< QSPI_T::STATUS: UNITIF Position         */
#define QSPI_STATUS_UNITIF_Msk            (0x1ul << QSPI_STATUS_UNITIF_Pos)                  /*!< QSPI_T::STATUS: UNITIF Mask             */

#define QSPI_STATUS_SSACTIF_Pos           (2)                                                /*!< QSPI_T::STATUS: SSACTIF Position        */
#define QSPI_STATUS_SSACTIF_Msk           (0x1ul << QSPI_STATUS_SSACTIF_Pos)                 /*!< QSPI_T::STATUS: SSACTIF Mask            */

#define QSPI_STATUS_SSINAIF_Pos           (3)                                                /*!< QSPI_T::STATUS: SSINAIF Position        */
#define QSPI_STATUS_SSINAIF_Msk           (0x1ul << QSPI_STATUS_SSINAIF_Pos)                 /*!< QSPI_T::STATUS: SSINAIF Mask            */

#define QSPI_STATUS_SSLINE_Pos            (4)                                                /*!< QSPI_T::STATUS: SSLINE Position         */
#define QSPI_STATUS_SSLINE_Msk            (0x1ul << QSPI_STATUS_SSLINE_Pos)                  /*!< QSPI_T::STATUS: SSLINE Mask             */

#define QSPI_STATUS_SLVTOIF_Pos           (5)                                                /*!< QSPI_T::STATUS: SLVTOIF Position        */
#define QSPI_STATUS_SLVTOIF_Msk           (0x1ul << QSPI_STATUS_SLVTOIF_Pos)                 /*!< QSPI_T::STATUS: SLVTOIF Mask            */

#define QSPI_STATUS_SLVBEIF_Pos           (6)                                                /*!< QSPI_T::STATUS: SLVBEIF Position        */
#define QSPI_STATUS_SLVBEIF_Msk           (0x1ul << QSPI_STATUS_SLVBEIF_Pos)                 /*!< QSPI_T::STATUS: SLVBEIF Mask            */

#define QSPI_STATUS_SLVURIF_Pos           (7)                                                /*!< QSPI_T::STATUS: SLVURIF Position        */
#define QSPI_STATUS_SLVURIF_Msk           (0x1ul << QSPI_STATUS_SLVURIF_Pos)                 /*!< QSPI_T::STATUS: SLVURIF Mask            */

#define QSPI_STATUS_RXEMPTY_Pos           (8)                                                /*!< QSPI_T::STATUS: RXEMPTY Position        */
#define QSPI_STATUS_RXEMPTY_Msk           (0x1ul << QSPI_STATUS_RXEMPTY_Pos)                 /*!< QSPI_T::STATUS: RXEMPTY Mask            */

#define QSPI_STATUS_RXFULL_Pos            (9)                                                /*!< QSPI_T::STATUS: RXFULL Position         */
#define QSPI_STATUS_RXFULL_Msk            (0x1ul << QSPI_STATUS_RXFULL_Pos)                  /*!< QSPI_T::STATUS: RXFULL Mask             */

#define QSPI_STATUS_RXTHIF_Pos            (10)                                               /*!< QSPI_T::STATUS: RXTHIF Position         */
#define QSPI_STATUS_RXTHIF_Msk            (0x1ul << QSPI_STATUS_RXTHIF_Pos)                  /*!< QSPI_T::STATUS: RXTHIF Mask             */

#define QSPI_STATUS_RXOVIF_Pos            (11)                                               /*!< QSPI_T::STATUS: RXOVIF Position         */
#define QSPI_STATUS_RXOVIF_Msk            (0x1ul << QSPI_STATUS_RXOVIF_Pos)                  /*!< QSPI_T::STATUS: RXOVIF Mask             */

#define QSPI_STATUS_RXTOIF_Pos            (12)                                               /*!< QSPI_T::STATUS: RXTOIF Position         */
#define QSPI_STATUS_RXTOIF_Msk            (0x1ul << QSPI_STATUS_RXTOIF_Pos)                  /*!< QSPI_T::STATUS: RXTOIF Mask             */

#define QSPI_STATUS_QSPIENSTS_Pos          (15)                                              /*!< QSPI_T::STATUS: QSPIENSTS Position       */
#define QSPI_STATUS_QSPIENSTS_Msk          (0x1ul << QSPI_STATUS_QSPIENSTS_Pos)              /*!< QSPI_T::STATUS: QSPIENSTS Mask           */

#define QSPI_STATUS_TXEMPTY_Pos           (16)                                               /*!< QSPI_T::STATUS: TXEMPTY Position        */
#define QSPI_STATUS_TXEMPTY_Msk           (0x1ul << QSPI_STATUS_TXEMPTY_Pos)                 /*!< QSPI_T::STATUS: TXEMPTY Mask            */

#define QSPI_STATUS_TXFULL_Pos            (17)                                               /*!< QSPI_T::STATUS: TXFULL Position         */
#define QSPI_STATUS_TXFULL_Msk            (0x1ul << QSPI_STATUS_TXFULL_Pos)                  /*!< QSPI_T::STATUS: TXFULL Mask             */

#define QSPI_STATUS_TXTHIF_Pos            (18)                                               /*!< QSPI_T::STATUS: TXTHIF Position         */
#define QSPI_STATUS_TXTHIF_Msk            (0x1ul << QSPI_STATUS_TXTHIF_Pos)                  /*!< QSPI_T::STATUS: TXTHIF Mask             */

#define QSPI_STATUS_TXUFIF_Pos            (19)                                               /*!< QSPI_T::STATUS: TXUFIF Position         */
#define QSPI_STATUS_TXUFIF_Msk            (0x1ul << QSPI_STATUS_TXUFIF_Pos)                  /*!< QSPI_T::STATUS: TXUFIF Mask             */

#define QSPI_STATUS_TXRXRST_Pos           (23)                                               /*!< QSPI_T::STATUS: TXRXRST Position        */
#define QSPI_STATUS_TXRXRST_Msk           (0x1ul << QSPI_STATUS_TXRXRST_Pos)                 /*!< QSPI_T::STATUS: TXRXRST Mask            */

#define QSPI_STATUS_RXCNT_Pos             (24)                                               /*!< QSPI_T::STATUS: RXCNT Position          */
#define QSPI_STATUS_RXCNT_Msk             (0xful << QSPI_STATUS_RXCNT_Pos)                   /*!< QSPI_T::STATUS: RXCNT Mask              */

#define QSPI_STATUS_TXCNT_Pos             (28)                                               /*!< QSPI_T::STATUS: TXCNT Position          */
#define QSPI_STATUS_TXCNT_Msk             (0xful << QSPI_STATUS_TXCNT_Pos)                   /*!< QSPI_T::STATUS: TXCNT Mask              */

#define QSPI_TX_TX_Pos                    (0)                                                /*!< QSPI_T::TX: TX Position                 */
#define QSPI_TX_TX_Msk                    (0xfffffffful << QSPI_TX_TX_Pos)                   /*!< QSPI_T::TX: TX Mask                     */

#define QSPI_RX_RX_Pos                    (0)                                                /*!< QSPI_T::RX: RX Position                 */
#define QSPI_RX_RX_Msk                    (0xfffffffful << QSPI_RX_RX_Pos)                   /*!< QSPI_T::RX: RX Mask                     */


/**@}*/ /* QSPI_CONST */
/**@}*/ /* end of QSPI register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __QSPI_REG_H__ */
