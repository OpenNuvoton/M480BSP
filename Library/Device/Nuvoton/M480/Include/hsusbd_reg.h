/**************************************************************************//**
 * @file     hsusbd_reg.h
 * @version  V1.00
 * @brief    HSUSBD register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __HSUSBD_REG_H__
#define __HSUSBD_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup HSUSBD USB 2.0 Device Controller(HSUSBD)
    Memory Mapped Structure for HSUSBD Controller
@{ */

typedef struct
{

    /**
@var HSUSBD_EP_T::EPDAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EPDAT
</font><br><p> <font size="2">
Offset: 0x00  Endpoint n Data Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>EPDAT</td><td><div style="word-wrap: break-word;"><b>Endpoint A~L Data Register
</b><br>
Endpoint A~L data buffer for the buffer transaction (read or write).
<br>
Note: Only word access is supported.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_EP_T::EPDAT_BYTE

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EPDAT_BYTE
</font><br><p> <font size="2">
Offset: 0x00  Endpoint n Data Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>EPDAT</td><td><div style="word-wrap: break-word;"><b>Endpoint A~L Data Register
</b><br>
Endpoint A~L data buffer for the buffer transaction (read or write).
<br>
Note: Only byte access is supported.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_EP_T::EPINTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EPINTSTS
</font><br><p> <font size="2">
Offset: 0x04  Endpoint n Interrupt Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BUFFULLIF</td><td><div style="word-wrap: break-word;"><b>Buffer Full
</b><br>
For an IN endpoint, the currently selected buffer is full, or no buffer is available to the local side for writing (no space to write)
<br>
For an OUT endpoint, there is a buffer available on the local side, and there are FIFO full of bytes available to be read (entire packet is available for reading).
<br>
0 = The endpoint packet buffer is not full.
<br>
1 = The endpoint packet buffer is full.
<br>
Note: This bit is read-only.
<br>
</div></td></tr><tr><td>
[1]</td><td>BUFEMPTYIF</td><td><div style="word-wrap: break-word;"><b>Buffer Empty
</b><br>
For an IN endpoint, a buffer is available to the local side for writing up to FIFO full of bytes.
<br>
0 = The endpoint buffer is not empty.
<br>
1 = The endpoint buffer is empty.
<br>
For an OUT endpoint:
<br>
0 = The currently selected buffer has not a count of 0.
<br>
1 = The currently selected buffer has a count of 0, or no buffer is available on the local side (nothing to read).
<br>
Note: This bit is read-only.
<br>
</div></td></tr><tr><td>
[2]</td><td>SHORTTXIF</td><td><div style="word-wrap: break-word;"><b>Short Packet Transferred Interrupt
</b><br>
0 = The length of the last packet was not less than the Maximum Packet Size (EPMPS).
<br>
1 = The length of the last packet was less than the Maximum Packet Size (EPMPS).
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[3]</td><td>TXPKIF</td><td><div style="word-wrap: break-word;"><b>Data Packet Transmitted Interrupt
</b><br>
0 = Not a data packet is transmitted from the endpoint to the host.
<br>
1 = A data packet is transmitted from the endpoint to the host.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[4]</td><td>RXPKIF</td><td><div style="word-wrap: break-word;"><b>Data Packet Received Interrupt
</b><br>
0 = No data packet is received from the host by the endpoint.
<br>
1 = A data packet is received from the host by the endpoint.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[5]</td><td>OUTTKIF</td><td><div style="word-wrap: break-word;"><b>Data OUT Token Interrupt
</b><br>
0 = A Data OUT token has not been received from the host.
<br>
1 = A Data OUT token has been received from the host
<br>
This bit also set by PING token (in high-speed only).
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[6]</td><td>INTKIF</td><td><div style="word-wrap: break-word;"><b>Data IN Token Interrupt
</b><br>
0 = Not Data IN token has been received from the host.
<br>
1 = A Data IN token has been received from the host.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[7]</td><td>PINGIF</td><td><div style="word-wrap: break-word;"><b>PING Token Interrupt
</b><br>
0 = A Data PING token has not been received from the host.
<br>
1 = A Data PING token has been received from the host.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[8]</td><td>NAKIF</td><td><div style="word-wrap: break-word;"><b>USB NAK Sent
</b><br>
0 = The last USB IN packet could be provided, and was acknowledged with an ACK.
<br>
1 = The last USB IN packet could not be provided, and was acknowledged with a NAK.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[9]</td><td>STALLIF</td><td><div style="word-wrap: break-word;"><b>USB STALL Sent
</b><br>
0 = The last USB packet could be accepted or provided because the endpoint was stalled, and was acknowledged with a STALL.
<br>
1 = The last USB packet could not be accepted or provided because the endpoint was stalled, and was acknowledged with a STALL.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[10]</td><td>NYETIF</td><td><div style="word-wrap: break-word;"><b>NYET Sent
</b><br>
0 = The space available in the RAM is sufficient to accommodate the next on coming data packet.
<br>
1 = The space available in the RAM is not sufficient to accommodate the next on coming data packet.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[11]</td><td>ERRIF</td><td><div style="word-wrap: break-word;"><b>ERR Sent
</b><br>
0 = No any error in the transaction.
<br>
1 = There occurs any error in the transaction.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[12]</td><td>SHORTRXIF</td><td><div style="word-wrap: break-word;"><b>Bulk Out Short Packet Received
</b><br>
0 = No bulk out short packet is received.
<br>
1 = Received bulk out short packet (including zero length packet).
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_EP_T::EPINTEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EPINTEN
</font><br><p> <font size="2">
Offset: 0x08  Endpoint n Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BUFFULLIEN</td><td><div style="word-wrap: break-word;"><b>Buffer Full Interrupt
</b><br>
When set, this bit enables a local interrupt to be set when a buffer full condition is detected on the bus.
<br>
0 = Buffer full interrupt Disabled.
<br>
1 = Buffer full interrupt Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>BUFEMPTYIEN</td><td><div style="word-wrap: break-word;"><b>Buffer Empty Interrupt
</b><br>
When set, this bit enables a local interrupt to be set when a buffer empty condition is detected on the bus.
<br>
0 = Buffer empty interrupt Disabled.
<br>
1 = Buffer empty interrupt Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>SHORTTXIEN</td><td><div style="word-wrap: break-word;"><b>Short Packet Transferred Interrupt Enable Bit
</b><br>
When set, this bit enables a local interrupt to be set when a short data packet has been transferred to/from the host.
<br>
0 = Short data packet interrupt Disabled.
<br>
1 = Short data packet interrupt Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>TXPKIEN</td><td><div style="word-wrap: break-word;"><b>Data Packet Transmitted Interrupt Enable Bit
</b><br>
When set, this bit enables a local interrupt to be set when a data packet has been received from the host.
<br>
0 = Data packet has been received from the host interrupt Disabled.
<br>
1 = Data packet has been received from the host interrupt Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>RXPKIEN</td><td><div style="word-wrap: break-word;"><b>Data Packet Received Interrupt Enable Bit
</b><br>
When set, this bit enables a local interrupt to be set when a data packet has been transmitted to the host.
<br>
0 = Data packet has been transmitted to the host interrupt Disabled.
<br>
1 = Data packet has been transmitted to the host interrupt Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>OUTTKIEN</td><td><div style="word-wrap: break-word;"><b>Data OUT Token Interrupt Enable Bit
</b><br>
When set, this bit enables a local interrupt to be set when a Data OUT token has been received from the host.
<br>
0 = Data OUT token interrupt Disabled.
<br>
1 = Data OUT token interrupt Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>INTKIEN</td><td><div style="word-wrap: break-word;"><b>Data IN Token Interrupt Enable Bit
</b><br>
When set, this bit enables a local interrupt to be set when a Data IN token has been received from the host.
<br>
0 = Data IN token interrupt Disabled.
<br>
1 = Data IN token interrupt Enabled.
<br>
</div></td></tr><tr><td>
[7]</td><td>PINGIEN</td><td><div style="word-wrap: break-word;"><b>PING Token Interrupt Enable Bit
</b><br>
When set, this bit enables a local interrupt to be set when a PING token has been received from the host.
<br>
0 = PING token interrupt Disabled.
<br>
1 = PING token interrupt Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>NAKIEN</td><td><div style="word-wrap: break-word;"><b>USB NAK Sent Interrupt Enable Bit
</b><br>
When set, this bit enables a local interrupt to be set when a NAK token is sent to the host.
<br>
0 = NAK token interrupt Disabled.
<br>
1 = NAK token interrupt Enabled.
<br>
</div></td></tr><tr><td>
[9]</td><td>STALLIEN</td><td><div style="word-wrap: break-word;"><b>USB STALL Sent Interrupt Enable Bit
</b><br>
When set, this bit enables a local interrupt to be set when a stall token is sent to the host.
<br>
0 = STALL token interrupt Disabled.
<br>
1 = STALL token interrupt Enabled.
<br>
</div></td></tr><tr><td>
[10]</td><td>NYETIEN</td><td><div style="word-wrap: break-word;"><b>NYET Interrupt Enable Bit
</b><br>
When set, this bit enables a local interrupt to be set whenever NYET condition occurs on the bus for this endpoint.
<br>
0 = NYET condition interrupt Disabled.
<br>
1 = NYET condition interrupt Enabled.
<br>
</div></td></tr><tr><td>
[11]</td><td>ERRIEN</td><td><div style="word-wrap: break-word;"><b>ERR Interrupt Enable Bit
</b><br>
When set, this bit enables a local interrupt to be set whenever ERR condition occurs on the bus for this endpoint.
<br>
0 = Error event interrupt Disabled.
<br>
1 = Error event interrupt Enabled.
<br>
</div></td></tr><tr><td>
[12]</td><td>SHORTRXIEN</td><td><div style="word-wrap: break-word;"><b>Bulk Out Short Packet Interrupt Enable Bit
</b><br>
When set, this bit enables a local interrupt to be set whenever bulk out short packet occurs on the bus for this endpoint.
<br>
0 = Bulk out interrupt Disabled.
<br>
1 = Bulk out interrupt Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_EP_T::EPDATCNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EPDATCNT
</font><br><p> <font size="2">
Offset: 0x0C  Endpoint n Data Available Count Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>DATCNT</td><td><div style="word-wrap: break-word;"><b>Data Count
</b><br>
For an IN endpoint (EPDIR(USBD_EPxCFG[3] is high.), this register returns the number of valid bytes in the IN endpoint packet buffer.
<br>
For an OUT endpoint (EPDIR(USBD_EPxCFG[3] is low.), this register returns the number of received valid bytes in the Host OUT transfer.
<br>
</div></td></tr><tr><td>
[30:16]</td><td>DMALOOP</td><td><div style="word-wrap: break-word;"><b>DMA Loop
</b><br>
This register is the remaining DMA loop to complete. Each loop means 32-byte transfer.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_EP_T::EPRSPCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EPRSPCTL
</font><br><p> <font size="2">
Offset: 0x10  Endpoint n Response Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>FLUSH</td><td><div style="word-wrap: break-word;"><b>Buffer Flush
</b><br>
Writing 1 to this bit causes the packet buffer to be flushed and the corresponding EP_AVAIL register to be cleared
<br>
This bit is self-clearing
<br>
This bit should always be written after an configuration event.
<br>
0 = The packet buffer is not flushed.
<br>
1 = The packet buffer is flushed by user.
<br>
</div></td></tr><tr><td>
[2:1]</td><td>MODE</td><td><div style="word-wrap: break-word;"><b>Mode Control
</b><br>
The two bits decide the operation mode of the in-endpoint.
<br>
00: Auto-Validate Mode
<br>
01: Manual-Validate Mode
<br>
10: Fly Mode
<br>
11: Reserved
<br>
These bits are not valid for an out-endpoint
<br>
The auto validate mode will be activated when the reserved mode is selected
<br>
</div></td></tr><tr><td>
[3]</td><td>TOGGLE</td><td><div style="word-wrap: break-word;"><b>Endpoint Toggle
</b><br>
This bit is used to clear the endpoint data toggle bit
<br>
Reading this bit returns the current state of the endpoint data toggle bit.
<br>
The local CPU may use this bit to initialize the end-point's toggle in case of reception of a Set Interface request or a Clear Feature (ep_halt) request from the host
<br>
Only when toggle bit is "1", this bit can be written into the inversed write data bit[3].
<br>
0 = Not clear the endpoint data toggle bit.
<br>
1 = Clear the endpoint data toggle bit.
<br>
</div></td></tr><tr><td>
[4]</td><td>HALT</td><td><div style="word-wrap: break-word;"><b>Endpoint Halt
</b><br>
This bit is used to send a STALL handshake as response to the token from the host
<br>
When an Endpoint Set Feature (ep_halt) is detected by the local CPU, it must write a '1' to this bit.
<br>
0 = Not send a STALL handshake as response to the token from the host.
<br>
1 = Send a STALL handshake as response to the token from the host.
<br>
</div></td></tr><tr><td>
[5]</td><td>ZEROLEN</td><td><div style="word-wrap: break-word;"><b>Zero Length
</b><br>
This bit is used to send a zero-length packet response to an IN-token
<br>
When this bit is set, a zero packet is sent to the host on reception of an IN-token
<br>
This bit gets cleared once the zero length data packet is sent.
<br>
0 = A zero packet is not sent to the host on reception of an IN-token.
<br>
1 = A zero packet is sent to the host on reception of an IN-token.
<br>
</div></td></tr><tr><td>
[6]</td><td>SHORTTXEN</td><td><div style="word-wrap: break-word;"><b>Short Packet Transfer Enable
</b><br>
This bit is applicable only in case of Auto-Validate Method
<br>
This bit is set to validate any remaining data in the buffer which is not equal to the MPS of the endpoint, and happens to be the last transfer
<br>
This bit gets cleared once the data packet is sent.
<br>
0 = Not validate any remaining data in the buffer which is not equal to the MPS of the endpoint.
<br>
1 = Validate any remaining data in the buffer which is not equal to the MPS of the endpoint.
<br>
</div></td></tr><tr><td>
[7]</td><td>DISBUF</td><td><div style="word-wrap: break-word;"><b>Buffer Disable Bit
</b><br>
This bit is used to receive unknown size OUT short packet
<br>
The received packet size is reference USBD_EPxDATCNT register.
<br>
0 = Buffer Not Disabled when Bulk-OUT short packet is received.
<br>
1 = Buffer Disabled when Bulk-OUT short packet is received.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_EP_T::EPMPS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EPMPS
</font><br><p> <font size="2">
Offset: 0x14  Endpoint n Maximum Packet Size Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[10:0]</td><td>EPMPS</td><td><div style="word-wrap: break-word;"><b>Endpoint Maximum Packet Size
</b><br>
This field determines the Maximum Packet Size of the Endpoint.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_EP_T::EPTXCNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EPTXCNT
</font><br><p> <font size="2">
Offset: 0x18  Endpoint n Transfer Count Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[10:0]</td><td>TXCNT</td><td><div style="word-wrap: break-word;"><b>Endpoint Transfer Count
</b><br>
For IN endpoints, this field determines the total number of bytes to be sent to the host in case of manual validation method.
<br>
For OUT endpoints, this field has no effect.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_EP_T::EPCFG

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EPCFG
</font><br><p> <font size="2">
Offset: 0x1C  Endpoint n Configuration Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>EPEN</td><td><div style="word-wrap: break-word;"><b>Endpoint Valid
</b><br>
When set, this bit enables this endpoint
<br>
This bit has no effect on Endpoint 0, which is always enabled.
<br>
0 = The endpoint Disabled.
<br>
1 = The endpoint Enabled.
<br>
</div></td></tr><tr><td>
[2:1]</td><td>EPTYPE</td><td><div style="word-wrap: break-word;"><b>Endpoint Type
</b><br>
This field selects the type of this endpoint. Endpoint 0 is forced to a Control type.
<br>
00 = Reserved.
<br>
01 = Bulk.
<br>
10 = Interrupt.
<br>
11 = Isochronous.
<br>
</div></td></tr><tr><td>
[3]</td><td>EPDIR</td><td><div style="word-wrap: break-word;"><b>Endpoint Direction
</b><br>
0 = out-endpoint (Host OUT to Device).
<br>
1 = in-endpoint (Host IN to Device).
<br>
Note: A maximum of one OUT and IN endpoint is allowed for each endpoint number.
<br>
</div></td></tr><tr><td>
[7:4]</td><td>EPNUM</td><td><div style="word-wrap: break-word;"><b>Endpoint Number
</b><br>
This field selects the number of the endpoint. Valid numbers 1 to 15.
<br>
Note: Do not support two endpoints have same endpoint number.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_EP_T::EPBUFST

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EPBUFST
</font><br><p> <font size="2">
Offset: 0x20  Endpoint n RAM Start Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[11:0]</td><td>SADDR</td><td><div style="word-wrap: break-word;"><b>Endpoint Start Address
</b><br>
This is the start-address of the RAM space allocated for the endpoint A~L.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_EP_T::EPBUFEND

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EPBUFEND
</font><br><p> <font size="2">
Offset: 0x24  Endpoint n RAM End Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[11:0]</td><td>EADDR</td><td><div style="word-wrap: break-word;"><b>Endpoint End Address
</b><br>
This is the end-address of the RAM space allocated for the endpoint A~L.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */

    union
    {
        __IO uint32_t EPDAT;
        __IO uint8_t  EPDAT_BYTE;

    };                                  /*!< [0x0000] Endpoint n Data Register                                         */

    __IO uint32_t EPINTSTS;             /*!< [0x0004] Endpoint n Interrupt Status Register                             */
    __IO uint32_t EPINTEN;              /*!< [0x0008] Endpoint n Interrupt Enable Register                             */
    __I  uint32_t EPDATCNT;             /*!< [0x000c] Endpoint n Data Available Count Register                         */
    __IO uint32_t EPRSPCTL;             /*!< [0x0010] Endpoint n Response Control Register                             */
    __IO uint32_t EPMPS;                /*!< [0x0014] Endpoint n Maximum Packet Size Register                          */
    __IO uint32_t EPTXCNT;              /*!< [0x0018] Endpoint n Transfer Count Register                               */
    __IO uint32_t EPCFG;                /*!< [0x001c] Endpoint n Configuration Register                                */
    __IO uint32_t EPBUFST;              /*!< [0x0020] Endpoint n RAM Start Address Register                            */
    __IO uint32_t EPBUFEND;             /*!< [0x0024] Endpoint n RAM End Address Register                              */

} HSUSBD_EP_T;

typedef struct
{

    /**
@var HSUSBD_T::GINTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GINTSTS
</font><br><p> <font size="2">
Offset: 0x00  Global Interrupt Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>USBIF</td><td><div style="word-wrap: break-word;"><b>USB Interrupt
</b><br>
This bit conveys the interrupt status for USB specific events endpoint
<br>
When set, USB interrupt status register should be read to determine the cause of the interrupt.
<br>
0 = No interrupt event occurred.
<br>
1 = The related interrupt event is occurred.
<br>
</div></td></tr><tr><td>
[1]</td><td>CEPIF</td><td><div style="word-wrap: break-word;"><b>Control Endpoint Interrupt
</b><br>
This bit conveys the interrupt status for control endpoint
<br>
When set, Control-ep's interrupt status register should be read to determine the cause of the interrupt.
<br>
0 = No interrupt event occurred.
<br>
1 = The related interrupt event is occurred.
<br>
</div></td></tr><tr><td>
[2]</td><td>EPAIF</td><td><div style="word-wrap: break-word;"><b>Endpoint a Interrupt
</b><br>
When set, the corresponding Endpoint A's interrupt status register should be read to determine the cause of the interrupt.
<br>
0 = No interrupt event occurred.
<br>
1 = The related interrupt event is occurred.
<br>
</div></td></tr><tr><td>
[3]</td><td>EPBIF</td><td><div style="word-wrap: break-word;"><b>Endpoint B Interrupt
</b><br>
When set, the corresponding Endpoint B's interrupt status register should be read to determine the cause of the interrupt.
<br>
0 = No interrupt event occurred.
<br>
1 = The related interrupt event is occurred.
<br>
</div></td></tr><tr><td>
[4]</td><td>EPCIF</td><td><div style="word-wrap: break-word;"><b>Endpoint C Interrupt
</b><br>
When set, the corresponding Endpoint C's interrupt status register should be read to determine the cause of the interrupt.
<br>
0 = No interrupt event occurred.
<br>
1 = The related interrupt event is occurred.
<br>
</div></td></tr><tr><td>
[5]</td><td>EPDIF</td><td><div style="word-wrap: break-word;"><b>Endpoint D Interrupt
</b><br>
When set, the corresponding Endpoint D's interrupt status register should be read to determine the cause of the interrupt.
<br>
0 = No interrupt event occurred.
<br>
1 = The related interrupt event is occurred.
<br>
</div></td></tr><tr><td>
[6]</td><td>EPEIF</td><td><div style="word-wrap: break-word;"><b>Endpoint E Interrupt
</b><br>
When set, the corresponding Endpoint E's interrupt status register should be read to determine the cause of the interrupt.
<br>
0 = No interrupt event occurred.
<br>
1 = The related interrupt event is occurred.
<br>
</div></td></tr><tr><td>
[7]</td><td>EPFIF</td><td><div style="word-wrap: break-word;"><b>Endpoint F Interrupt
</b><br>
When set, the corresponding Endpoint F's interrupt status register should be read to determine the cause of the interrupt.
<br>
0 = No interrupt event occurred.
<br>
1 = The related interrupt event is occurred.
<br>
</div></td></tr><tr><td>
[8]</td><td>EPGIF</td><td><div style="word-wrap: break-word;"><b>Endpoint G Interrupt
</b><br>
When set, the corresponding Endpoint G's interrupt status register should be read to determine the cause of the interrupt.
<br>
0 = No interrupt event occurred.
<br>
1 = The related interrupt event is occurred.
<br>
</div></td></tr><tr><td>
[9]</td><td>EPHIF</td><td><div style="word-wrap: break-word;"><b>Endpoint H Interrupt
</b><br>
When set, the corresponding Endpoint H's interrupt status register should be read to determine the cause of the interrupt.
<br>
0 = No interrupt event occurred.
<br>
1 = The related interrupt event is occurred.
<br>
</div></td></tr><tr><td>
[10]</td><td>EPIIF</td><td><div style="word-wrap: break-word;"><b>Endpoint I Interrupt
</b><br>
When set, the corresponding Endpoint I's interrupt status register should be read to determine the cause of the interrupt.
<br>
0 = No interrupt event occurred.
<br>
1 = The related interrupt event is occurred.
<br>
</div></td></tr><tr><td>
[11]</td><td>EPJIF</td><td><div style="word-wrap: break-word;"><b>Endpoint J Interrupt
</b><br>
When set, the corresponding Endpoint J's interrupt status register should be read to determine the cause of the interrupt.
<br>
0 = No interrupt event occurred.
<br>
1 = The related interrupt event is occurred.
<br>
</div></td></tr><tr><td>
[12]</td><td>EPKIF</td><td><div style="word-wrap: break-word;"><b>Endpoint K Interrupt
</b><br>
When set, the corresponding Endpoint K's interrupt status register should be read to determine the cause of the interrupt.
<br>
0 = No interrupt event occurred.
<br>
1 = The related interrupt event is occurred.
<br>
</div></td></tr><tr><td>
[13]</td><td>EPLIF</td><td><div style="word-wrap: break-word;"><b>Endpoint L Interrupt
</b><br>
When set, the corresponding Endpoint L's interrupt status register should be read to determine the cause of the interrupt.
<br>
0 = No interrupt event occurred.
<br>
1 = The related interrupt event is occurred.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::GINTEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GINTEN
</font><br><p> <font size="2">
Offset: 0x08  Global Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>USBIEN</td><td><div style="word-wrap: break-word;"><b>USB Interrupt Enable Bit
</b><br>
When set, this bit enables a local interrupt to be generated when a USB event occurs on the bus.
<br>
0 = The related interrupt Disabled.
<br>
1 = The related interrupt Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>CEPIEN</td><td><div style="word-wrap: break-word;"><b>Control Endpoint Interrupt Enable Bit
</b><br>
When set, this bit enables a local interrupt to be generated when an interrupt is pending for the control endpoint.
<br>
0 = The related interrupt Disabled.
<br>
1 = The related interrupt Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>EPAIEN</td><td><div style="word-wrap: break-word;"><b>Interrupt Enable Control for Endpoint a
</b><br>
When set, this bit enables a local interrupt to be generated when an interrupt is pending for the endpoint A.
<br>
0 = The related interrupt Disabled.
<br>
1 = The related interrupt Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>EPBIEN</td><td><div style="word-wrap: break-word;"><b>Interrupt Enable Control for Endpoint B
</b><br>
When set, this bit enables a local interrupt to be generated when an interrupt is pending for the endpoint B
<br>
0 = The related interrupt Disabled.
<br>
1 = The related interrupt Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>EPCIEN</td><td><div style="word-wrap: break-word;"><b>Interrupt Enable Control for Endpoint C
</b><br>
When set, this bit enables a local interrupt to be generated when an interrupt is pending for the endpoint C
<br>
0 = The related interrupt Disabled.
<br>
1 = The related interrupt Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>EPDIEN</td><td><div style="word-wrap: break-word;"><b>Interrupt Enable Control for Endpoint D
</b><br>
When set, this bit enables a local interrupt to be generated when an interrupt is pending for the endpoint D
<br>
0 = The related interrupt Disabled.
<br>
1 = The related interrupt Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>EPEIEN</td><td><div style="word-wrap: break-word;"><b>Interrupt Enable Control for Endpoint E
</b><br>
When set, this bit enables a local interrupt to be generated when an interrupt is pending for the endpoint E
<br>
0 = The related interrupt Disabled.
<br>
1 = The related interrupt Enabled.
<br>
</div></td></tr><tr><td>
[7]</td><td>EPFIEN</td><td><div style="word-wrap: break-word;"><b>Interrupt Enable Control for Endpoint F
</b><br>
When set, this bit enables a local interrupt to be generated when an interrupt is pending for the endpoint F
<br>
0 = The related interrupt Disabled.
<br>
1 = The related interrupt Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>EPGIEN</td><td><div style="word-wrap: break-word;"><b>Interrupt Enable Control for Endpoint G
</b><br>
When set, this bit enables a local interrupt to be generated when an interrupt is pending for the endpoint G
<br>
0 = The related interrupt Disabled.
<br>
1 = The related interrupt Enabled.
<br>
</div></td></tr><tr><td>
[9]</td><td>EPHIEN</td><td><div style="word-wrap: break-word;"><b>Interrupt Enable Control for Endpoint H
</b><br>
When set, this bit enables a local interrupt to be generated when an interrupt is pending for the endpoint H
<br>
0 = The related interrupt Disabled.
<br>
1 = The related interrupt Enabled.
<br>
</div></td></tr><tr><td>
[10]</td><td>EPIIEN</td><td><div style="word-wrap: break-word;"><b>Interrupt Enable Control for Endpoint I
</b><br>
When set, this bit enables a local interrupt to be generated when an interrupt is pending for the endpoint I
<br>
0 = The related interrupt Disabled.
<br>
1 = The related interrupt Enabled.
<br>
</div></td></tr><tr><td>
[11]</td><td>EPJIEN</td><td><div style="word-wrap: break-word;"><b>Interrupt Enable Control for Endpoint J
</b><br>
When set, this bit enables a local interrupt to be generated when an interrupt is pending for the endpoint J
<br>
0 = The related interrupt Disabled.
<br>
1 = The related interrupt Enabled.
<br>
</div></td></tr><tr><td>
[12]</td><td>EPKIEN</td><td><div style="word-wrap: break-word;"><b>Interrupt Enable Control for Endpoint K
</b><br>
When set, this bit enables a local interrupt to be generated when an interrupt is pending for the endpoint K
<br>
0 = The related interrupt Disabled.
<br>
1 = The related interrupt Enabled.
<br>
</div></td></tr><tr><td>
[13]</td><td>EPLIEN</td><td><div style="word-wrap: break-word;"><b>Interrupt Enable Control for Endpoint L
</b><br>
When set, this bit enables a local interrupt to be generated when an interrupt is pending for the endpoint L
<br>
0 = The related interrupt Disabled.
<br>
1 = The related interrupt Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::BUSINTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BUSINTSTS
</font><br><p> <font size="2">
Offset: 0x10  USB Bus Interrupt Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SOFIF</td><td><div style="word-wrap: break-word;"><b>SOF Receive Control
</b><br>
This bit indicates when a start-of-frame packet has been received.
<br>
0 = No start-of-frame packet has been received.
<br>
1 = Start-of-frame packet has been received.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[1]</td><td>RSTIF</td><td><div style="word-wrap: break-word;"><b>Reset Status
</b><br>
When set, this bit indicates that either the USB root port reset is end.
<br>
0 = No USB root port reset is end.
<br>
1 = USB root port reset is end.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[2]</td><td>RESUMEIF</td><td><div style="word-wrap: break-word;"><b>Resume
</b><br>
When set, this bit indicates that a device resume has occurred.
<br>
0 = No device resume has occurred.
<br>
1 = Device resume has occurred.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[3]</td><td>SUSPENDIF</td><td><div style="word-wrap: break-word;"><b>Suspend Request
</b><br>
This bit is set as default and it has to be cleared by writing '1' before the USB reset
<br>
This bit is also set when a USB Suspend request is detected from the host.
<br>
0 = No USB Suspend request is detected from the host.
<br>
1= USB Suspend request is detected from the host.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[4]</td><td>HISPDIF</td><td><div style="word-wrap: break-word;"><b>High-speed Settle
</b><br>
0 = No valid high-speed reset protocol is detected.
<br>
1 = Valid high-speed reset protocol is over and the device has settled in high-speed.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[5]</td><td>DMADONEIF</td><td><div style="word-wrap: break-word;"><b>DMA Completion Interrupt
</b><br>
0 = No DMA transfer over.
<br>
1 = DMA transfer is over.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[6]</td><td>PHYCLKVLDIF</td><td><div style="word-wrap: break-word;"><b>Usable Clock Interrupt
</b><br>
0 = Usable clock is not available.
<br>
1 = Usable clock is available from the transceiver.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[8]</td><td>VBUSDETIF</td><td><div style="word-wrap: break-word;"><b>VBUS Detection Interrupt Status
</b><br>
0 = No VBUS is plug-in.
<br>
1 = VBUS is plug-in.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::BUSINTEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BUSINTEN
</font><br><p> <font size="2">
Offset: 0x14  USB Bus Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SOFIEN</td><td><div style="word-wrap: break-word;"><b>SOF Interrupt
</b><br>
This bit enables the SOF interrupt.
<br>
0 = SOF interrupt Disabled.
<br>
1 = SOF interrupt Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>RSTIEN</td><td><div style="word-wrap: break-word;"><b>Reset Status
</b><br>
This bit enables the USB-Reset interrupt.
<br>
0 = USB-Reset interrupt Disabled.
<br>
1 = USB-Reset interrupt Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>RESUMEIEN</td><td><div style="word-wrap: break-word;"><b>Resume
</b><br>
This bit enables the Resume interrupt.
<br>
0 = Resume interrupt Disabled.
<br>
1 = Resume interrupt Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>SUSPENDIEN</td><td><div style="word-wrap: break-word;"><b>Suspend Request
</b><br>
This bit enables the Suspend interrupt.
<br>
0 = Suspend interrupt Disabled.
<br>
1 = Suspend interrupt Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>HISPDIEN</td><td><div style="word-wrap: break-word;"><b>High-speed Settle
</b><br>
This bit enables the high-speed settle interrupt.
<br>
0 = High-speed settle interrupt Disabled.
<br>
1 = High-speed settle interrupt Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>DMADONEIEN</td><td><div style="word-wrap: break-word;"><b>DMA Completion Interrupt
</b><br>
This bit enables the DMA completion interrupt
<br>
0 = DMA completion interrupt Disabled.
<br>
1 = DMA completion interrupt Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>PHYCLKVLDIEN</td><td><div style="word-wrap: break-word;"><b>Usable Clock Interrupt
</b><br>
This bit enables the usable clock interrupt.
<br>
0 = Usable clock interrupt Disabled.
<br>
1 = Usable clock interrupt Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>VBUSDETIEN</td><td><div style="word-wrap: break-word;"><b>VBUS Detection Interrupt Enable Bit
</b><br>
This bit enables the VBUS floating detection interrupt.
<br>
0 = VBUS floating detection interrupt Disabled.
<br>
1 = VBUS floating detection interrupt Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::OPER

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">OPER
</font><br><p> <font size="2">
Offset: 0x18  USB Operational Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>RESUMEEN</td><td><div style="word-wrap: break-word;"><b>Generate Resume
</b><br>
0 = No Resume sequence to be initiated to the host.
<br>
1 = A Resume sequence to be initiated to the host if device remote wakeup is enabled
<br>
This bit is self-clearing.
<br>
</div></td></tr><tr><td>
[1]</td><td>HISPDEN</td><td><div style="word-wrap: break-word;"><b>USB High-speed
</b><br>
0 = The USB device controller to suppress the chirp-sequence during reset protocol, thereby allowing the USB device controller to settle in full-speed, even though it is connected to a USB2.0 Host.
<br>
1 = The USB device controller to initiate a chirp-sequence during reset protocol.
<br>
</div></td></tr><tr><td>
[2]</td><td>CURSPD</td><td><div style="word-wrap: break-word;"><b>USB Current Speed
</b><br>
0 = The device has settled in Full Speed.
<br>
1 = The USB device controller has settled in High-speed.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::FRAMECNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">FRAMECNT
</font><br><p> <font size="2">
Offset: 0x1C  USB Frame Count Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2:0]</td><td>MFRAMECNT</td><td><div style="word-wrap: break-word;"><b>Micro-frame Counter
</b><br>
This field contains the micro-frame number for the frame number in the frame counter field.
<br>
</div></td></tr><tr><td>
[13:3]</td><td>FRAMECNT</td><td><div style="word-wrap: break-word;"><b>Frame Counter
</b><br>
This field contains the frame count from the most recent start-of-frame packet.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::FADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">FADDR
</font><br><p> <font size="2">
Offset: 0x20  USB Function Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[6:0]</td><td>FADDR</td><td><div style="word-wrap: break-word;"><b>USB Function Address
</b><br>
This field contains the current USB address of the device
<br>
This field is cleared when a root port reset is detected
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::TEST

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TEST
</font><br><p> <font size="2">
Offset: 0x24  USB Test Mode Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2:0]</td><td>TESTMODE</td><td><div style="word-wrap: break-word;"><b>Test Mode Selection
</b><br>
000 = Normal Operation.
<br>
001 = Test_J.
<br>
010 = Test_K.
<br>
011 = Test_SE0_NAK.
<br>
100 = Test_Packet.
<br>
101 = Test_Force_Enable.
<br>
110 = Reserved.
<br>
111 = Reserved.
<br>
Note: This field is cleared when root port reset is detected.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::CEPDAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CEPDAT
</font><br><p> <font size="2">
Offset: 0x28  Control-Endpoint Data Buffer
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DAT</td><td><div style="word-wrap: break-word;"><b>Control-endpoint Data Buffer
</b><br>
Control endpoint data buffer for the buffer transaction (read or write).
<br>
Note: Only word access is supported.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::CEPDAT_BYTE

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CEPDAT_BYTE
</font><br><p> <font size="2">
Offset: 0x28  Control-Endpoint Data Buffer
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>DAT</td><td><div style="word-wrap: break-word;"><b>Control-endpoint Data Buffer
</b><br>
Control endpoint data buffer for the buffer transaction (read or write).
<br>
Note: Only byte access is supported.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::CEPCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CEPCTL
</font><br><p> <font size="2">
Offset: 0x2C  Control-Endpoint Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>NAKCLR</td><td><div style="word-wrap: break-word;"><b>No Acknowledge Control
</b><br>
This bit plays a crucial role in any control transfer.
<br>
0 = The bit is being cleared by the local CPU by writing zero, the USB device controller will be responding with NAKs for the subsequent status phase
<br>
This mechanism holds the host from moving to the next request, until the local CPU is also ready to process the next request.
<br>
1 = This bit is set to one by the USB device controller, whenever a setup token is received
<br>
The local CPU can take its own time to finish off any house-keeping work based on the request and then clear this bit.
<br>
Note: Only when CPU writes data[1:0] is 2'b10 or 2'b00, this bit can be updated.
<br>
</div></td></tr><tr><td>
[1]</td><td>STALLEN</td><td><div style="word-wrap: break-word;"><b>Stall Enable Bit
</b><br>
When this stall bit is set, the control endpoint sends a stall handshake in response to any in or out token thereafter
<br>
This is typically used for response to invalid/unsupported requests
<br>
When this bit is being set the NAK clear bit has to be cleared at the same time since the NAK clear bit has highest priority than STALL
<br>
It is automatically cleared on receipt of a next setup-token
<br>
So, the local CPU need not write again to clear this bit.
<br>
0 = No sends a stall handshake in response to any in or out token thereafter.
<br>
1 = The control endpoint sends a stall handshake in response to any in or out token thereafter.
<br>
Note: Only when CPU writes data[1:0] is 2'b10 or 2'b00, this bit can be updated.
<br>
</div></td></tr><tr><td>
[2]</td><td>ZEROLEN</td><td><div style="word-wrap: break-word;"><b>Zero Packet Length
</b><br>
This bit is valid for Auto Validation mode only.
<br>
0 = No zero length packet to the host during Data stage to an IN token.
<br>
1 = USB device controller can send a zero length packet to the host during Data stage to an IN token
<br>
This bit gets cleared once the zero length data packet is sent
<br>
So, the local CPU need not write again to clear this bit.
<br>
</div></td></tr><tr><td>
[3]</td><td>FLUSH</td><td><div style="word-wrap: break-word;"><b>CEP-flush Bit
</b><br>
0 = No the packet buffer and its corresponding USBD_CEPDATCNT register to be cleared.
<br>
1 = The packet buffer and its corresponding USBD_CEPDATCNT register to be cleared
<br>
This bit is self-cleaning.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::CEPINTEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CEPINTEN
</font><br><p> <font size="2">
Offset: 0x30  Control-Endpoint Interrupt Enable
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SETUPTKIEN</td><td><div style="word-wrap: break-word;"><b>Setup Token Interrupt Enable Bit
</b><br>
0 = The SETUP token interrupt in Control Endpoint Disabled.
<br>
1 = The SETUP token interrupt in Control Endpoint Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>SETUPPKIEN</td><td><div style="word-wrap: break-word;"><b>Setup Packet Interrupt
</b><br>
0 = The SETUP packet interrupt in Control Endpoint Disabled.
<br>
1 = The SETUP packet interrupt in Control Endpoint Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>OUTTKIEN</td><td><div style="word-wrap: break-word;"><b>Out Token Interrupt
</b><br>
0 = The OUT token interrupt in Control Endpoint Disabled.
<br>
1 = The OUT token interrupt in Control Endpoint Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>INTKIEN</td><td><div style="word-wrap: break-word;"><b>In Token Interrupt
</b><br>
0 = The IN token interrupt in Control Endpoint Disabled.
<br>
1 = The IN token interrupt in Control Endpoint Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>PINGIEN</td><td><div style="word-wrap: break-word;"><b>Ping Token Interrupt
</b><br>
0 = The ping token interrupt in Control Endpoint Disabled.
<br>
1 = The ping token interrupt Control Endpoint Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>TXPKIEN</td><td><div style="word-wrap: break-word;"><b>Data Packet Transmitted Interrupt
</b><br>
0 = The data packet transmitted interrupt in Control Endpoint Disabled.
<br>
1 = The data packet transmitted interrupt in Control Endpoint Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>RXPKIEN</td><td><div style="word-wrap: break-word;"><b>Data Packet Received Interrupt
</b><br>
0 = The data received interrupt in Control Endpoint Disabled.
<br>
1 = The data received interrupt in Control Endpoint Enabled.
<br>
</div></td></tr><tr><td>
[7]</td><td>NAKIEN</td><td><div style="word-wrap: break-word;"><b>NAK Sent Interrupt
</b><br>
0 = The NAK sent interrupt in Control Endpoint Disabled.
<br>
1 = The NAK sent interrupt in Control Endpoint Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>STALLIEN</td><td><div style="word-wrap: break-word;"><b>STALL Sent Interrupt
</b><br>
0 = The STALL sent interrupt in Control Endpoint Disabled.
<br>
1 = The STALL sent interrupt in Control Endpoint Enabled.
<br>
</div></td></tr><tr><td>
[9]</td><td>ERRIEN</td><td><div style="word-wrap: break-word;"><b>USB Error Interrupt
</b><br>
0 = The USB Error interrupt in Control Endpoint Disabled.
<br>
1 = The USB Error interrupt in Control Endpoint Enabled.
<br>
</div></td></tr><tr><td>
[10]</td><td>STSDONEIEN</td><td><div style="word-wrap: break-word;"><b>Status Completion Interrupt
</b><br>
0 = The Status Completion interrupt in Control Endpoint Disabled.
<br>
1 = The Status Completion interrupt in Control Endpoint Enabled.
<br>
</div></td></tr><tr><td>
[11]</td><td>BUFFULLIEN</td><td><div style="word-wrap: break-word;"><b>Buffer Full Interrupt
</b><br>
0 = The buffer full interrupt in Control Endpoint Disabled.
<br>
1 = The buffer full interrupt in Control Endpoint Enabled.
<br>
</div></td></tr><tr><td>
[12]</td><td>BUFEMPTYIEN</td><td><div style="word-wrap: break-word;"><b>Buffer Empty Interrupt
</b><br>
0 = The buffer empty interrupt in Control Endpoint Disabled.
<br>
1= The buffer empty interrupt in Control Endpoint Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::CEPINTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CEPINTSTS
</font><br><p> <font size="2">
Offset: 0x34  Control-Endpoint Interrupt Status
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SETUPTKIF</td><td><div style="word-wrap: break-word;"><b>Setup Token Interrupt
</b><br>
0 = Not a Setup token is received.
<br>
1 = A Setup token is received. Writing 1 clears this status bit
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[1]</td><td>SETUPPKIF</td><td><div style="word-wrap: break-word;"><b>Setup Packet Interrupt
</b><br>
This bit must be cleared (by writing 1) before the next setup packet can be received
<br>
If the bit is not cleared, then the successive setup packets will be overwritten in the setup packet buffer.
<br>
0 = Not a Setup packet has been received from the host.
<br>
1 = A Setup packet has been received from the host.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[2]</td><td>OUTTKIF</td><td><div style="word-wrap: break-word;"><b>Out Token Interrupt
</b><br>
0 = The control-endpoint does not received an OUT token from the host.
<br>
1 = The control-endpoint receives an OUT token from the host.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[3]</td><td>INTKIF</td><td><div style="word-wrap: break-word;"><b>in Token Interrupt
</b><br>
0 = The control-endpoint does not received an IN token from the host.
<br>
1 = The control-endpoint receives an IN token from the host.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[4]</td><td>PINGIF</td><td><div style="word-wrap: break-word;"><b>Ping Token Interrupt
</b><br>
0 = The control-endpoint does not received a ping token from the host.
<br>
1 = The control-endpoint receives a ping token from the host.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[5]</td><td>TXPKIF</td><td><div style="word-wrap: break-word;"><b>Data Packet Transmitted Interrupt
</b><br>
0 = Not a data packet is successfully transmitted to the host in response to an IN-token and an ACK-token is received for the same.
<br>
1 = A data packet is successfully transmitted to the host in response to an IN-token and an ACK-token is received for the same.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[6]</td><td>RXPKIF</td><td><div style="word-wrap: break-word;"><b>Data Packet Received Interrupt
</b><br>
0 = Not a data packet is successfully received from the host for an OUT-token and an ACK is sent to the host.
<br>
1 = A data packet is successfully received from the host for an OUT-token and an ACK is sent to the host.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[7]</td><td>NAKIF</td><td><div style="word-wrap: break-word;"><b>NAK Sent Interrupt
</b><br>
0 = Not a NAK-token is sent in response to an IN/OUT token.
<br>
1 = A NAK-token is sent in response to an IN/OUT token.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[8]</td><td>STALLIF</td><td><div style="word-wrap: break-word;"><b>STALL Sent Interrupt
</b><br>
0 = Not a stall-token is sent in response to an IN/OUT token.
<br>
1 = A stall-token is sent in response to an IN/OUT token.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[9]</td><td>ERRIF</td><td><div style="word-wrap: break-word;"><b>USB Error Interrupt
</b><br>
0 = No error had occurred during the transaction.
<br>
1 = An error had occurred during the transaction.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[10]</td><td>STSDONEIF</td><td><div style="word-wrap: break-word;"><b>Status Completion Interrupt
</b><br>
0 = Not a USB transaction has completed successfully.
<br>
1 = The status stage of a USB transaction has completed successfully.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[11]</td><td>BUFFULLIF</td><td><div style="word-wrap: break-word;"><b>Buffer Full Interrupt
</b><br>
0 = The control-endpoint buffer is not full.
<br>
1 = The control-endpoint buffer is full.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[12]</td><td>BUFEMPTYIF</td><td><div style="word-wrap: break-word;"><b>Buffer Empty Interrupt
</b><br>
0 = The control-endpoint buffer is not empty.
<br>
1 = The control-endpoint buffer is empty.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::CEPTXCNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CEPTXCNT
</font><br><p> <font size="2">
Offset: 0x38  Control-Endpoint In-transfer Data Count
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>TXCNT</td><td><div style="word-wrap: break-word;"><b>In-transfer Data Count
</b><br>
There is no mode selection for the control endpoint (but it operates like manual mode).The local-CPU has to fill the control-endpoint buffer with the data to be sent for an in-token and to write the count of bytes in this register
<br>
When zero is written into this field, a zero length packet is sent to the host
<br>
When the count written in the register is more than the MPS, the data sent will be of only MPS.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::CEPRXCNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CEPRXCNT
</font><br><p> <font size="2">
Offset: 0x3C  Control-Endpoint Out-transfer Data Count
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>RXCNT</td><td><div style="word-wrap: break-word;"><b>Out-transfer Data Count
</b><br>
The USB device controller maintains the count of the data received in case of an out transfer, during the control transfer.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::CEPDATCNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CEPDATCNT
</font><br><p> <font size="2">
Offset: 0x40  Control-Endpoint data count
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>DATCNT</td><td><div style="word-wrap: break-word;"><b>Control-endpoint Data Count
</b><br>
The USB device controller maintains the count of the data of control-endpoint.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::SETUP1_0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SETUP1_0
</font><br><p> <font size="2">
Offset: 0x44  Setup1 & Setup0 bytes
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>SETUP0</td><td><div style="word-wrap: break-word;"><b>Setup Byte 0[7:0]
</b><br>
This register provides byte 0 of the last setup packet received
<br>
For a Standard Device Request, the following bmRequestType information is returned.
<br>
Bit 7(Direction):
<br>
 0: Host to device
<br>
 1: Device to host
<br>
Bit 6-5 (Type):
<br>
 00: Standard
<br>
 01: Class
<br>
 10: Vendor
<br>
 11: Reserved
<br>
Bit 4-0 (Recipient)
<br>
 00000: Device
<br>
 00001: Interface
<br>
 00010: Endpoint
<br>
 00011: Other
<br>
 Others: Reserved
<br>
</div></td></tr><tr><td>
[15:8]</td><td>SETUP1</td><td><div style="word-wrap: break-word;"><b>Setup Byte 1[15:8]
</b><br>
This register provides byte 1 of the last setup packet received
<br>
For a Standard Device Request, the following bRequest Code information is returned.
<br>
00000000 = Get Status.
<br>
00000001 = Clear Feature.
<br>
00000010 = Reserved.
<br>
00000011 = Set Feature.
<br>
00000100 = Reserved.
<br>
00000101 = Set Address.
<br>
00000110 = Get Descriptor.
<br>
00000111 = Set Descriptor.
<br>
00001000 = Get Configuration.
<br>
00001001 = Set Configuration.
<br>
00001010 = Get Interface.
<br>
00001011 = Set Interface.
<br>
00001100 = Sync Frame.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::SETUP3_2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SETUP3_2
</font><br><p> <font size="2">
Offset: 0x48  Setup3 & Setup2 Bytes
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>SETUP2</td><td><div style="word-wrap: break-word;"><b>Setup Byte 2 [7:0]
</b><br>
This register provides byte 2 of the last setup packet received
<br>
For a Standard Device Request, the least significant byte of the wValue field is returned
<br>
</div></td></tr><tr><td>
[15:8]</td><td>SETUP3</td><td><div style="word-wrap: break-word;"><b>Setup Byte 3 [15:8]
</b><br>
This register provides byte 3 of the last setup packet received
<br>
For a Standard Device Request, the most significant byte of the wValue field is returned.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::SETUP5_4

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SETUP5_4
</font><br><p> <font size="2">
Offset: 0x4C  Setup5 & Setup4 Bytes
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>SETUP4</td><td><div style="word-wrap: break-word;"><b>Setup Byte 4[7:0]
</b><br>
This register provides byte 4 of the last setup packet received
<br>
For a Standard Device Request, the least significant byte of the wIndex is returned.
<br>
</div></td></tr><tr><td>
[15:8]</td><td>SETUP5</td><td><div style="word-wrap: break-word;"><b>Setup Byte 5[15:8]
</b><br>
This register provides byte 5 of the last setup packet received
<br>
For a Standard Device Request, the most significant byte of the wIndex field is returned.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::SETUP7_6

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SETUP7_6
</font><br><p> <font size="2">
Offset: 0x50  Setup7 & Setup6 Bytes
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>SETUP6</td><td><div style="word-wrap: break-word;"><b>Setup Byte 6[7:0]
</b><br>
This register provides byte 6 of the last setup packet received
<br>
For a Standard Device Request, the least significant byte of the wLength field is returned.
<br>
</div></td></tr><tr><td>
[15:8]</td><td>SETUP7</td><td><div style="word-wrap: break-word;"><b>Setup Byte 7[15:8]
</b><br>
This register provides byte 7 of the last setup packet received
<br>
For a Standard Device Request, the most significant byte of the wLength field is returned.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::CEPBUFST

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CEPBUFST
</font><br><p> <font size="2">
Offset: 0x54  Control Endpoint RAM Start Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[11:0]</td><td>SADDR</td><td><div style="word-wrap: break-word;"><b>Control-endpoint Start Address
</b><br>
This is the start-address of the RAM space allocated for the control-endpoint.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::CEPBUFEND

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CEPBUFEND
</font><br><p> <font size="2">
Offset: 0x58  Control Endpoint RAM End Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[11:0]</td><td>EADDR</td><td><div style="word-wrap: break-word;"><b>Control-endpoint End Address
</b><br>
This is the end-address of the RAM space allocated for the control-endpoint.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::DMACTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DMACTL
</font><br><p> <font size="2">
Offset: 0x5C  DMA Control Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>EPNUM</td><td><div style="word-wrap: break-word;"><b>DMA Endpoint Address Bits
</b><br>
Used to define the Endpoint Address
<br>
</div></td></tr><tr><td>
[4]</td><td>DMARD</td><td><div style="word-wrap: break-word;"><b>DMA Operation
</b><br>
0 : The operation is a DMA write (read from USB buffer)
<br>
DMA will check endpoint data available count (USBD_EPxDATCNT) according to EPNM setting before to perform DMA write operation.
<br>
1 : The operation is a DMA read (write to USB buffer).
<br>
</div></td></tr><tr><td>
[5]</td><td>DMAEN</td><td><div style="word-wrap: break-word;"><b>DMA Enable Bit
</b><br>
0 : DMA function Disabled.
<br>
1 : DMA function Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>SGEN</td><td><div style="word-wrap: break-word;"><b>Scatter Gather Function Enable Bit
</b><br>
0 : Scatter gather function Disabled.
<br>
1 : Scatter gather function Enabled.
<br>
</div></td></tr><tr><td>
[7]</td><td>DMARST</td><td><div style="word-wrap: break-word;"><b>Reset DMA State Machine
</b><br>
0 : No reset the DMA state machine.
<br>
1 : Reset the DMA state machine.
<br>
</div></td></tr><tr><td>
[8]</td><td>SVINEP</td><td><div style="word-wrap: break-word;"><b>Serve IN Endpoint
</b><br>
This bit is used to specify DMA serving endpoint-IN endpoint or OUT endpoint.
<br>
0: DMA serves OUT endpoint
<br>
1: DMA serves IN endpoint
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::DMACNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DMACNT
</font><br><p> <font size="2">
Offset: 0x60  DMA Count Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[19:0]</td><td>DMACNT</td><td><div style="word-wrap: break-word;"><b>DMA Transfer Count
</b><br>
The transfer count of the DMA operation to be performed is written to this register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::DMAADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DMAADDR
</font><br><p> <font size="2">
Offset: 0x700  AHB DMA Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>DMAADDR</td><td><div style="word-wrap: break-word;"><b>DMAADDR
</b><br>
The register specifies the address from which the DMA has to read / write
<br>
The address must WORD (32-bit) aligned.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBD_T::PHYCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PHYCTL
</font><br><p> <font size="2">
Offset: 0x704  USB PHY Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[8]</td><td>DPPUEN</td><td><div style="word-wrap: break-word;"><b>DP Pull-up
</b><br>
0 = Pull-up resistor on D+ Disabled.
<br>
1 = Pull-up resistor on D+ Enabled.
<br>
</div></td></tr><tr><td>
[9]</td><td>PHYEN</td><td><div style="word-wrap: break-word;"><b>PHY Suspend Enable Bit
</b><br>
0 = The USB PHY is suspend.
<br>
1 = The USB PHY is not suspend.
<br>
</div></td></tr><tr><td>
[24]</td><td>WKEN</td><td><div style="word-wrap: break-word;"><b>Wake-up Enable Bit
</b><br>
0 = The wake-up function Disabled.
<br>
1 = The wake-up function Enabled.
<br>
</div></td></tr><tr><td>
[31]</td><td>VBUSDET</td><td><div style="word-wrap: break-word;"><b>VBUS Status
</b><br>
0 = The VBUS is not detected yet.
<br>
1 = The VBUS is detected.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */

    __I  uint32_t GINTSTS;               /*!< [0x0000] Global Interrupt Status Register                                 */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t GINTEN;                /*!< [0x0008] Global Interrupt Enable Register                                 */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t BUSINTSTS;             /*!< [0x0010] USB Bus Interrupt Status Register                                */
    __IO uint32_t BUSINTEN;              /*!< [0x0014] USB Bus Interrupt Enable Register                                */
    __IO uint32_t OPER;                  /*!< [0x0018] USB Operational Register                                         */
    __I  uint32_t FRAMECNT;              /*!< [0x001c] USB Frame Count Register                                         */
    __IO uint32_t FADDR;                 /*!< [0x0020] USB Function Address Register                                    */
    __IO uint32_t TEST;                  /*!< [0x0024] USB Test Mode Register                                           */

    union
    {
        __IO uint32_t CEPDAT;
        __IO uint8_t  CEPDAT_BYTE;

    };                                   /*!< [0x0028] Control-Endpoint Data Buffer                                     */

    __IO uint32_t CEPCTL;                /*!< [0x002c] Control-Endpoint Control Register                                */
    __IO uint32_t CEPINTEN;              /*!< [0x0030] Control-Endpoint Interrupt Enable                                */
    __IO uint32_t CEPINTSTS;             /*!< [0x0034] Control-Endpoint Interrupt Status                                */
    __IO uint32_t CEPTXCNT;              /*!< [0x0038] Control-Endpoint In-transfer Data Count                          */
    __I  uint32_t CEPRXCNT;              /*!< [0x003c] Control-Endpoint Out-transfer Data Count                         */
    __I  uint32_t CEPDATCNT;             /*!< [0x0040] Control-Endpoint data count                                      */
    __I  uint32_t SETUP1_0;              /*!< [0x0044] Setup1 & Setup0 bytes                                            */
    __I  uint32_t SETUP3_2;              /*!< [0x0048] Setup3 & Setup2 Bytes                                            */
    __I  uint32_t SETUP5_4;              /*!< [0x004c] Setup5 & Setup4 Bytes                                            */
    __I  uint32_t SETUP7_6;              /*!< [0x0050] Setup7 & Setup6 Bytes                                            */
    __IO uint32_t CEPBUFST;              /*!< [0x0054] Control Endpoint RAM Start Address Register                      */
    __IO uint32_t CEPBUFEND;             /*!< [0x0058] Control Endpoint RAM End Address Register                        */
    __IO uint32_t DMACTL;                /*!< [0x005c] DMA Control Status Register                                      */
    __IO uint32_t DMACNT;                /*!< [0x0060] DMA Count Register                                               */

    HSUSBD_EP_T EP[12];

    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE2[303];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t DMAADDR;               /*!< [0x0700] AHB DMA Address Register                                         */
    __IO uint32_t PHYCTL;                /*!< [0x0704] USB PHY Control Register                                         */

} HSUSBD_T;

/**
    @addtogroup HSUSBD_CONST HSUSBD Bit Field Definition
    Constant Definitions for HSUSBD Controller
@{ */

#define HSUSBD_GINTSTS_USBIF_Pos         (0)                                               /*!< HSUSBD_T::GINTSTS: USBIF Position      */
#define HSUSBD_GINTSTS_USBIF_Msk         (0x1ul << HSUSBD_GINTSTS_USBIF_Pos)               /*!< HSUSBD_T::GINTSTS: USBIF Mask          */

#define HSUSBD_GINTSTS_CEPIF_Pos         (1)                                               /*!< HSUSBD_T::GINTSTS: CEPIF Position      */
#define HSUSBD_GINTSTS_CEPIF_Msk         (0x1ul << HSUSBD_GINTSTS_CEPIF_Pos)               /*!< HSUSBD_T::GINTSTS: CEPIF Mask          */

#define HSUSBD_GINTSTS_EPAIF_Pos         (2)                                               /*!< HSUSBD_T::GINTSTS: EPAIF Position      */
#define HSUSBD_GINTSTS_EPAIF_Msk         (0x1ul << HSUSBD_GINTSTS_EPAIF_Pos)               /*!< HSUSBD_T::GINTSTS: EPAIF Mask          */

#define HSUSBD_GINTSTS_EPBIF_Pos         (3)                                               /*!< HSUSBD_T::GINTSTS: EPBIF Position      */
#define HSUSBD_GINTSTS_EPBIF_Msk         (0x1ul << HSUSBD_GINTSTS_EPBIF_Pos)               /*!< HSUSBD_T::GINTSTS: EPBIF Mask          */

#define HSUSBD_GINTSTS_EPCIF_Pos         (4)                                               /*!< HSUSBD_T::GINTSTS: EPCIF Position      */
#define HSUSBD_GINTSTS_EPCIF_Msk         (0x1ul << HSUSBD_GINTSTS_EPCIF_Pos)               /*!< HSUSBD_T::GINTSTS: EPCIF Mask          */

#define HSUSBD_GINTSTS_EPDIF_Pos         (5)                                               /*!< HSUSBD_T::GINTSTS: EPDIF Position      */
#define HSUSBD_GINTSTS_EPDIF_Msk         (0x1ul << HSUSBD_GINTSTS_EPDIF_Pos)               /*!< HSUSBD_T::GINTSTS: EPDIF Mask          */

#define HSUSBD_GINTSTS_EPEIF_Pos         (6)                                               /*!< HSUSBD_T::GINTSTS: EPEIF Position      */
#define HSUSBD_GINTSTS_EPEIF_Msk         (0x1ul << HSUSBD_GINTSTS_EPEIF_Pos)               /*!< HSUSBD_T::GINTSTS: EPEIF Mask          */

#define HSUSBD_GINTSTS_EPFIF_Pos         (7)                                               /*!< HSUSBD_T::GINTSTS: EPFIF Position      */
#define HSUSBD_GINTSTS_EPFIF_Msk         (0x1ul << HSUSBD_GINTSTS_EPFIF_Pos)               /*!< HSUSBD_T::GINTSTS: EPFIF Mask          */

#define HSUSBD_GINTSTS_EPGIF_Pos         (8)                                               /*!< HSUSBD_T::GINTSTS: EPGIF Position      */
#define HSUSBD_GINTSTS_EPGIF_Msk         (0x1ul << HSUSBD_GINTSTS_EPGIF_Pos)               /*!< HSUSBD_T::GINTSTS: EPGIF Mask          */

#define HSUSBD_GINTSTS_EPHIF_Pos         (9)                                               /*!< HSUSBD_T::GINTSTS: EPHIF Position      */
#define HSUSBD_GINTSTS_EPHIF_Msk         (0x1ul << HSUSBD_GINTSTS_EPHIF_Pos)               /*!< HSUSBD_T::GINTSTS: EPHIF Mask          */

#define HSUSBD_GINTSTS_EPIIF_Pos         (10)                                              /*!< HSUSBD_T::GINTSTS: EPIIF Position      */
#define HSUSBD_GINTSTS_EPIIF_Msk         (0x1ul << HSUSBD_GINTSTS_EPIIF_Pos)               /*!< HSUSBD_T::GINTSTS: EPIIF Mask          */

#define HSUSBD_GINTSTS_EPJIF_Pos         (11)                                              /*!< HSUSBD_T::GINTSTS: EPJIF Position      */
#define HSUSBD_GINTSTS_EPJIF_Msk         (0x1ul << HSUSBD_GINTSTS_EPJIF_Pos)               /*!< HSUSBD_T::GINTSTS: EPJIF Mask          */

#define HSUSBD_GINTSTS_EPKIF_Pos         (12)                                              /*!< HSUSBD_T::GINTSTS: EPKIF Position      */
#define HSUSBD_GINTSTS_EPKIF_Msk         (0x1ul << HSUSBD_GINTSTS_EPKIF_Pos)               /*!< HSUSBD_T::GINTSTS: EPKIF Mask          */

#define HSUSBD_GINTSTS_EPLIF_Pos         (13)                                              /*!< HSUSBD_T::GINTSTS: EPLIF Position      */
#define HSUSBD_GINTSTS_EPLIF_Msk         (0x1ul << HSUSBD_GINTSTS_EPLIF_Pos)               /*!< HSUSBD_T::GINTSTS: EPLIF Mask          */

#define HSUSBD_GINTEN_USBIEN_Pos         (0)                                               /*!< HSUSBD_T::GINTEN: USBIEN Position      */
#define HSUSBD_GINTEN_USBIEN_Msk         (0x1ul << HSUSBD_GINTEN_USBIEN_Pos)               /*!< HSUSBD_T::GINTEN: USBIEN Mask          */

#define HSUSBD_GINTEN_CEPIEN_Pos         (1)                                               /*!< HSUSBD_T::GINTEN: CEPIEN Position      */
#define HSUSBD_GINTEN_CEPIEN_Msk         (0x1ul << HSUSBD_GINTEN_CEPIEN_Pos)               /*!< HSUSBD_T::GINTEN: CEPIEN Mask          */

#define HSUSBD_GINTEN_EPAIEN_Pos         (2)                                               /*!< HSUSBD_T::GINTEN: EPAIEN Position      */
#define HSUSBD_GINTEN_EPAIEN_Msk         (0x1ul << HSUSBD_GINTEN_EPAIEN_Pos)               /*!< HSUSBD_T::GINTEN: EPAIEN Mask          */

#define HSUSBD_GINTEN_EPBIEN_Pos         (3)                                               /*!< HSUSBD_T::GINTEN: EPBIEN Position      */
#define HSUSBD_GINTEN_EPBIEN_Msk         (0x1ul << HSUSBD_GINTEN_EPBIEN_Pos)               /*!< HSUSBD_T::GINTEN: EPBIEN Mask          */

#define HSUSBD_GINTEN_EPCIEN_Pos         (4)                                               /*!< HSUSBD_T::GINTEN: EPCIEN Position      */
#define HSUSBD_GINTEN_EPCIEN_Msk         (0x1ul << HSUSBD_GINTEN_EPCIEN_Pos)               /*!< HSUSBD_T::GINTEN: EPCIEN Mask          */

#define HSUSBD_GINTEN_EPDIEN_Pos         (5)                                               /*!< HSUSBD_T::GINTEN: EPDIEN Position      */
#define HSUSBD_GINTEN_EPDIEN_Msk         (0x1ul << HSUSBD_GINTEN_EPDIEN_Pos)               /*!< HSUSBD_T::GINTEN: EPDIEN Mask          */

#define HSUSBD_GINTEN_EPEIEN_Pos         (6)                                               /*!< HSUSBD_T::GINTEN: EPEIEN Position      */
#define HSUSBD_GINTEN_EPEIEN_Msk         (0x1ul << HSUSBD_GINTEN_EPEIEN_Pos)               /*!< HSUSBD_T::GINTEN: EPEIEN Mask          */

#define HSUSBD_GINTEN_EPFIEN_Pos         (7)                                               /*!< HSUSBD_T::GINTEN: EPFIEN Position      */
#define HSUSBD_GINTEN_EPFIEN_Msk         (0x1ul << HSUSBD_GINTEN_EPFIEN_Pos)               /*!< HSUSBD_T::GINTEN: EPFIEN Mask          */

#define HSUSBD_GINTEN_EPGIEN_Pos         (8)                                               /*!< HSUSBD_T::GINTEN: EPGIEN Position      */
#define HSUSBD_GINTEN_EPGIEN_Msk         (0x1ul << HSUSBD_GINTEN_EPGIEN_Pos)               /*!< HSUSBD_T::GINTEN: EPGIEN Mask          */

#define HSUSBD_GINTEN_EPHIEN_Pos         (9)                                               /*!< HSUSBD_T::GINTEN: EPHIEN Position      */
#define HSUSBD_GINTEN_EPHIEN_Msk         (0x1ul << HSUSBD_GINTEN_EPHIEN_Pos)               /*!< HSUSBD_T::GINTEN: EPHIEN Mask          */

#define HSUSBD_GINTEN_EPIIEN_Pos         (10)                                              /*!< HSUSBD_T::GINTEN: EPIIEN Position      */
#define HSUSBD_GINTEN_EPIIEN_Msk         (0x1ul << HSUSBD_GINTEN_EPIIEN_Pos)               /*!< HSUSBD_T::GINTEN: EPIIEN Mask          */

#define HSUSBD_GINTEN_EPJIEN_Pos         (11)                                              /*!< HSUSBD_T::GINTEN: EPJIEN Position      */
#define HSUSBD_GINTEN_EPJIEN_Msk         (0x1ul << HSUSBD_GINTEN_EPJIEN_Pos)               /*!< HSUSBD_T::GINTEN: EPJIEN Mask          */

#define HSUSBD_GINTEN_EPKIEN_Pos         (12)                                              /*!< HSUSBD_T::GINTEN: EPKIEN Position      */
#define HSUSBD_GINTEN_EPKIEN_Msk         (0x1ul << HSUSBD_GINTEN_EPKIEN_Pos)               /*!< HSUSBD_T::GINTEN: EPKIEN Mask          */

#define HSUSBD_GINTEN_EPLIEN_Pos         (13)                                              /*!< HSUSBD_T::GINTEN: EPLIEN Position      */
#define HSUSBD_GINTEN_EPLIEN_Msk         (0x1ul << HSUSBD_GINTEN_EPLIEN_Pos)               /*!< HSUSBD_T::GINTEN: EPLIEN Mask          */

#define HSUSBD_BUSINTSTS_SOFIF_Pos       (0)                                               /*!< HSUSBD_T::BUSINTSTS: SOFIF Position    */
#define HSUSBD_BUSINTSTS_SOFIF_Msk       (0x1ul << HSUSBD_BUSINTSTS_SOFIF_Pos)             /*!< HSUSBD_T::BUSINTSTS: SOFIF Mask        */

#define HSUSBD_BUSINTSTS_RSTIF_Pos       (1)                                               /*!< HSUSBD_T::BUSINTSTS: RSTIF Position    */
#define HSUSBD_BUSINTSTS_RSTIF_Msk       (0x1ul << HSUSBD_BUSINTSTS_RSTIF_Pos)             /*!< HSUSBD_T::BUSINTSTS: RSTIF Mask        */

#define HSUSBD_BUSINTSTS_RESUMEIF_Pos    (2)                                               /*!< HSUSBD_T::BUSINTSTS: RESUMEIF Position */
#define HSUSBD_BUSINTSTS_RESUMEIF_Msk    (0x1ul << HSUSBD_BUSINTSTS_RESUMEIF_Pos)          /*!< HSUSBD_T::BUSINTSTS: RESUMEIF Mask     */

#define HSUSBD_BUSINTSTS_SUSPENDIF_Pos   (3)                                               /*!< HSUSBD_T::BUSINTSTS: SUSPENDIF Position*/
#define HSUSBD_BUSINTSTS_SUSPENDIF_Msk   (0x1ul << HSUSBD_BUSINTSTS_SUSPENDIF_Pos)         /*!< HSUSBD_T::BUSINTSTS: SUSPENDIF Mask    */

#define HSUSBD_BUSINTSTS_HISPDIF_Pos     (4)                                               /*!< HSUSBD_T::BUSINTSTS: HISPDIF Position  */
#define HSUSBD_BUSINTSTS_HISPDIF_Msk     (0x1ul << HSUSBD_BUSINTSTS_HISPDIF_Pos)           /*!< HSUSBD_T::BUSINTSTS: HISPDIF Mask      */

#define HSUSBD_BUSINTSTS_DMADONEIF_Pos   (5)                                               /*!< HSUSBD_T::BUSINTSTS: DMADONEIF Position*/
#define HSUSBD_BUSINTSTS_DMADONEIF_Msk   (0x1ul << HSUSBD_BUSINTSTS_DMADONEIF_Pos)         /*!< HSUSBD_T::BUSINTSTS: DMADONEIF Mask    */

#define HSUSBD_BUSINTSTS_PHYCLKVLDIF_Pos (6)                                               /*!< HSUSBD_T::BUSINTSTS: PHYCLKVLDIF Position*/
#define HSUSBD_BUSINTSTS_PHYCLKVLDIF_Msk (0x1ul << HSUSBD_BUSINTSTS_PHYCLKVLDIF_Pos)       /*!< HSUSBD_T::BUSINTSTS: PHYCLKVLDIF Mask  */

#define HSUSBD_BUSINTSTS_VBUSDETIF_Pos   (8)                                               /*!< HSUSBD_T::BUSINTSTS: VBUSDETIF Position*/
#define HSUSBD_BUSINTSTS_VBUSDETIF_Msk   (0x1ul << HSUSBD_BUSINTSTS_VBUSDETIF_Pos)         /*!< HSUSBD_T::BUSINTSTS: VBUSDETIF Mask    */

#define HSUSBD_BUSINTEN_SOFIEN_Pos       (0)                                               /*!< HSUSBD_T::BUSINTEN: SOFIEN Position    */
#define HSUSBD_BUSINTEN_SOFIEN_Msk       (0x1ul << HSUSBD_BUSINTEN_SOFIEN_Pos)             /*!< HSUSBD_T::BUSINTEN: SOFIEN Mask        */

#define HSUSBD_BUSINTEN_RSTIEN_Pos       (1)                                               /*!< HSUSBD_T::BUSINTEN: RSTIEN Position    */
#define HSUSBD_BUSINTEN_RSTIEN_Msk       (0x1ul << HSUSBD_BUSINTEN_RSTIEN_Pos)             /*!< HSUSBD_T::BUSINTEN: RSTIEN Mask        */

#define HSUSBD_BUSINTEN_RESUMEIEN_Pos    (2)                                               /*!< HSUSBD_T::BUSINTEN: RESUMEIEN Position */
#define HSUSBD_BUSINTEN_RESUMEIEN_Msk    (0x1ul << HSUSBD_BUSINTEN_RESUMEIEN_Pos)          /*!< HSUSBD_T::BUSINTEN: RESUMEIEN Mask     */

#define HSUSBD_BUSINTEN_SUSPENDIEN_Pos   (3)                                               /*!< HSUSBD_T::BUSINTEN: SUSPENDIEN Position*/
#define HSUSBD_BUSINTEN_SUSPENDIEN_Msk   (0x1ul << HSUSBD_BUSINTEN_SUSPENDIEN_Pos)         /*!< HSUSBD_T::BUSINTEN: SUSPENDIEN Mask    */

#define HSUSBD_BUSINTEN_HISPDIEN_Pos     (4)                                               /*!< HSUSBD_T::BUSINTEN: HISPDIEN Position  */
#define HSUSBD_BUSINTEN_HISPDIEN_Msk     (0x1ul << HSUSBD_BUSINTEN_HISPDIEN_Pos)           /*!< HSUSBD_T::BUSINTEN: HISPDIEN Mask      */

#define HSUSBD_BUSINTEN_DMADONEIEN_Pos   (5)                                               /*!< HSUSBD_T::BUSINTEN: DMADONEIEN Position*/
#define HSUSBD_BUSINTEN_DMADONEIEN_Msk   (0x1ul << HSUSBD_BUSINTEN_DMADONEIEN_Pos)         /*!< HSUSBD_T::BUSINTEN: DMADONEIEN Mask    */

#define HSUSBD_BUSINTEN_PHYCLKVLDIEN_Pos (6)                                               /*!< HSUSBD_T::BUSINTEN: PHYCLKVLDIEN Position*/
#define HSUSBD_BUSINTEN_PHYCLKVLDIEN_Msk (0x1ul << HSUSBD_BUSINTEN_PHYCLKVLDIEN_Pos)       /*!< HSUSBD_T::BUSINTEN: PHYCLKVLDIEN Mask  */

#define HSUSBD_BUSINTEN_VBUSDETIEN_Pos   (8)                                               /*!< HSUSBD_T::BUSINTEN: VBUSDETIEN Position*/
#define HSUSBD_BUSINTEN_VBUSDETIEN_Msk   (0x1ul << HSUSBD_BUSINTEN_VBUSDETIEN_Pos)         /*!< HSUSBD_T::BUSINTEN: VBUSDETIEN Mask    */

#define HSUSBD_OPER_RESUMEEN_Pos         (0)                                               /*!< HSUSBD_T::OPER: RESUMEEN Position      */
#define HSUSBD_OPER_RESUMEEN_Msk         (0x1ul << HSUSBD_OPER_RESUMEEN_Pos)               /*!< HSUSBD_T::OPER: RESUMEEN Mask          */

#define HSUSBD_OPER_HISPDEN_Pos          (1)                                               /*!< HSUSBD_T::OPER: HISPDEN Position       */
#define HSUSBD_OPER_HISPDEN_Msk          (0x1ul << HSUSBD_OPER_HISPDEN_Pos)                /*!< HSUSBD_T::OPER: HISPDEN Mask           */

#define HSUSBD_OPER_CURSPD_Pos           (2)                                               /*!< HSUSBD_T::OPER: CURSPD Position        */
#define HSUSBD_OPER_CURSPD_Msk           (0x1ul << HSUSBD_OPER_CURSPD_Pos)                 /*!< HSUSBD_T::OPER: CURSPD Mask            */

#define HSUSBD_FRAMECNT_MFRAMECNT_Pos    (0)                                               /*!< HSUSBD_T::FRAMECNT: MFRAMECNT Position */
#define HSUSBD_FRAMECNT_MFRAMECNT_Msk    (0x7ul << HSUSBD_FRAMECNT_MFRAMECNT_Pos)          /*!< HSUSBD_T::FRAMECNT: MFRAMECNT Mask     */

#define HSUSBD_FRAMECNT_FRAMECNT_Pos     (3)                                               /*!< HSUSBD_T::FRAMECNT: FRAMECNT Position  */
#define HSUSBD_FRAMECNT_FRAMECNT_Msk     (0x7fful << HSUSBD_FRAMECNT_FRAMECNT_Pos)         /*!< HSUSBD_T::FRAMECNT: FRAMECNT Mask      */

#define HSUSBD_FADDR_FADDR_Pos           (0)                                               /*!< HSUSBD_T::FADDR: FADDR Position        */
#define HSUSBD_FADDR_FADDR_Msk           (0x7ful << HSUSBD_FADDR_FADDR_Pos)                /*!< HSUSBD_T::FADDR: FADDR Mask            */

#define HSUSBD_TEST_TESTMODE_Pos         (0)                                               /*!< HSUSBD_T::TEST: TESTMODE Position      */
#define HSUSBD_TEST_TESTMODE_Msk         (0x7ul << HSUSBD_TEST_TESTMODE_Pos)               /*!< HSUSBD_T::TEST: TESTMODE Mask          */

#define HSUSBD_CEPDAT_DAT_Pos            (0)                                               /*!< HSUSBD_T::CEPDAT: DAT Position         */
#define HSUSBD_CEPDAT_DAT_Msk            (0xfffffffful << HSUSBD_CEPDAT_DAT_Pos)           /*!< HSUSBD_T::CEPDAT: DAT Mask             */

#define HSUSBD_CEPCTL_NAKCLR_Pos         (0)                                               /*!< HSUSBD_T::CEPCTL: NAKCLR Position      */
#define HSUSBD_CEPCTL_NAKCLR_Msk         (0x1ul << HSUSBD_CEPCTL_NAKCLR_Pos)               /*!< HSUSBD_T::CEPCTL: NAKCLR Mask          */

#define HSUSBD_CEPCTL_STALLEN_Pos        (1)                                               /*!< HSUSBD_T::CEPCTL: STALLEN Position     */
#define HSUSBD_CEPCTL_STALLEN_Msk        (0x1ul << HSUSBD_CEPCTL_STALLEN_Pos)              /*!< HSUSBD_T::CEPCTL: STALLEN Mask         */

#define HSUSBD_CEPCTL_ZEROLEN_Pos        (2)                                               /*!< HSUSBD_T::CEPCTL: ZEROLEN Position     */
#define HSUSBD_CEPCTL_ZEROLEN_Msk        (0x1ul << HSUSBD_CEPCTL_ZEROLEN_Pos)              /*!< HSUSBD_T::CEPCTL: ZEROLEN Mask         */

#define HSUSBD_CEPCTL_FLUSH_Pos          (3)                                               /*!< HSUSBD_T::CEPCTL: FLUSH Position       */
#define HSUSBD_CEPCTL_FLUSH_Msk          (0x1ul << HSUSBD_CEPCTL_FLUSH_Pos)                /*!< HSUSBD_T::CEPCTL: FLUSH Mask           */

#define HSUSBD_CEPINTEN_SETUPTKIEN_Pos   (0)                                               /*!< HSUSBD_T::CEPINTEN: SETUPTKIEN Position*/
#define HSUSBD_CEPINTEN_SETUPTKIEN_Msk   (0x1ul << HSUSBD_CEPINTEN_SETUPTKIEN_Pos)         /*!< HSUSBD_T::CEPINTEN: SETUPTKIEN Mask    */

#define HSUSBD_CEPINTEN_SETUPPKIEN_Pos   (1)                                               /*!< HSUSBD_T::CEPINTEN: SETUPPKIEN Position*/
#define HSUSBD_CEPINTEN_SETUPPKIEN_Msk   (0x1ul << HSUSBD_CEPINTEN_SETUPPKIEN_Pos)         /*!< HSUSBD_T::CEPINTEN: SETUPPKIEN Mask    */

#define HSUSBD_CEPINTEN_OUTTKIEN_Pos     (2)                                               /*!< HSUSBD_T::CEPINTEN: OUTTKIEN Position  */
#define HSUSBD_CEPINTEN_OUTTKIEN_Msk     (0x1ul << HSUSBD_CEPINTEN_OUTTKIEN_Pos)           /*!< HSUSBD_T::CEPINTEN: OUTTKIEN Mask      */

#define HSUSBD_CEPINTEN_INTKIEN_Pos      (3)                                               /*!< HSUSBD_T::CEPINTEN: INTKIEN Position   */
#define HSUSBD_CEPINTEN_INTKIEN_Msk      (0x1ul << HSUSBD_CEPINTEN_INTKIEN_Pos)            /*!< HSUSBD_T::CEPINTEN: INTKIEN Mask       */

#define HSUSBD_CEPINTEN_PINGIEN_Pos      (4)                                               /*!< HSUSBD_T::CEPINTEN: PINGIEN Position   */
#define HSUSBD_CEPINTEN_PINGIEN_Msk      (0x1ul << HSUSBD_CEPINTEN_PINGIEN_Pos)            /*!< HSUSBD_T::CEPINTEN: PINGIEN Mask       */

#define HSUSBD_CEPINTEN_TXPKIEN_Pos      (5)                                               /*!< HSUSBD_T::CEPINTEN: TXPKIEN Position   */
#define HSUSBD_CEPINTEN_TXPKIEN_Msk      (0x1ul << HSUSBD_CEPINTEN_TXPKIEN_Pos)            /*!< HSUSBD_T::CEPINTEN: TXPKIEN Mask       */

#define HSUSBD_CEPINTEN_RXPKIEN_Pos      (6)                                               /*!< HSUSBD_T::CEPINTEN: RXPKIEN Position   */
#define HSUSBD_CEPINTEN_RXPKIEN_Msk      (0x1ul << HSUSBD_CEPINTEN_RXPKIEN_Pos)            /*!< HSUSBD_T::CEPINTEN: RXPKIEN Mask       */

#define HSUSBD_CEPINTEN_NAKIEN_Pos       (7)                                               /*!< HSUSBD_T::CEPINTEN: NAKIEN Position    */
#define HSUSBD_CEPINTEN_NAKIEN_Msk       (0x1ul << HSUSBD_CEPINTEN_NAKIEN_Pos)             /*!< HSUSBD_T::CEPINTEN: NAKIEN Mask        */

#define HSUSBD_CEPINTEN_STALLIEN_Pos     (8)                                               /*!< HSUSBD_T::CEPINTEN: STALLIEN Position  */
#define HSUSBD_CEPINTEN_STALLIEN_Msk     (0x1ul << HSUSBD_CEPINTEN_STALLIEN_Pos)           /*!< HSUSBD_T::CEPINTEN: STALLIEN Mask      */

#define HSUSBD_CEPINTEN_ERRIEN_Pos       (9)                                               /*!< HSUSBD_T::CEPINTEN: ERRIEN Position    */
#define HSUSBD_CEPINTEN_ERRIEN_Msk       (0x1ul << HSUSBD_CEPINTEN_ERRIEN_Pos)             /*!< HSUSBD_T::CEPINTEN: ERRIEN Mask        */

#define HSUSBD_CEPINTEN_STSDONEIEN_Pos   (10)                                              /*!< HSUSBD_T::CEPINTEN: STSDONEIEN Position*/
#define HSUSBD_CEPINTEN_STSDONEIEN_Msk   (0x1ul << HSUSBD_CEPINTEN_STSDONEIEN_Pos)         /*!< HSUSBD_T::CEPINTEN: STSDONEIEN Mask    */

#define HSUSBD_CEPINTEN_BUFFULLIEN_Pos   (11)                                              /*!< HSUSBD_T::CEPINTEN: BUFFULLIEN Position*/
#define HSUSBD_CEPINTEN_BUFFULLIEN_Msk   (0x1ul << HSUSBD_CEPINTEN_BUFFULLIEN_Pos)         /*!< HSUSBD_T::CEPINTEN: BUFFULLIEN Mask    */

#define HSUSBD_CEPINTEN_BUFEMPTYIEN_Pos  (12)                                              /*!< HSUSBD_T::CEPINTEN: BUFEMPTYIEN Position*/
#define HSUSBD_CEPINTEN_BUFEMPTYIEN_Msk  (0x1ul << HSUSBD_CEPINTEN_BUFEMPTYIEN_Pos)        /*!< HSUSBD_T::CEPINTEN: BUFEMPTYIEN Mask   */

#define HSUSBD_CEPINTSTS_SETUPTKIF_Pos   (0)                                               /*!< HSUSBD_T::CEPINTSTS: SETUPTKIF Position*/
#define HSUSBD_CEPINTSTS_SETUPTKIF_Msk   (0x1ul << HSUSBD_CEPINTSTS_SETUPTKIF_Pos)         /*!< HSUSBD_T::CEPINTSTS: SETUPTKIF Mask    */

#define HSUSBD_CEPINTSTS_SETUPPKIF_Pos   (1)                                               /*!< HSUSBD_T::CEPINTSTS: SETUPPKIF Position*/
#define HSUSBD_CEPINTSTS_SETUPPKIF_Msk   (0x1ul << HSUSBD_CEPINTSTS_SETUPPKIF_Pos)         /*!< HSUSBD_T::CEPINTSTS: SETUPPKIF Mask    */

#define HSUSBD_CEPINTSTS_OUTTKIF_Pos     (2)                                               /*!< HSUSBD_T::CEPINTSTS: OUTTKIF Position  */
#define HSUSBD_CEPINTSTS_OUTTKIF_Msk     (0x1ul << HSUSBD_CEPINTSTS_OUTTKIF_Pos)           /*!< HSUSBD_T::CEPINTSTS: OUTTKIF Mask      */

#define HSUSBD_CEPINTSTS_INTKIF_Pos      (3)                                               /*!< HSUSBD_T::CEPINTSTS: INTKIF Position   */
#define HSUSBD_CEPINTSTS_INTKIF_Msk      (0x1ul << HSUSBD_CEPINTSTS_INTKIF_Pos)            /*!< HSUSBD_T::CEPINTSTS: INTKIF Mask       */

#define HSUSBD_CEPINTSTS_PINGIF_Pos      (4)                                               /*!< HSUSBD_T::CEPINTSTS: PINGIF Position   */
#define HSUSBD_CEPINTSTS_PINGIF_Msk      (0x1ul << HSUSBD_CEPINTSTS_PINGIF_Pos)            /*!< HSUSBD_T::CEPINTSTS: PINGIF Mask       */

#define HSUSBD_CEPINTSTS_TXPKIF_Pos      (5)                                               /*!< HSUSBD_T::CEPINTSTS: TXPKIF Position   */
#define HSUSBD_CEPINTSTS_TXPKIF_Msk      (0x1ul << HSUSBD_CEPINTSTS_TXPKIF_Pos)            /*!< HSUSBD_T::CEPINTSTS: TXPKIF Mask       */

#define HSUSBD_CEPINTSTS_RXPKIF_Pos      (6)                                               /*!< HSUSBD_T::CEPINTSTS: RXPKIF Position   */
#define HSUSBD_CEPINTSTS_RXPKIF_Msk      (0x1ul << HSUSBD_CEPINTSTS_RXPKIF_Pos)            /*!< HSUSBD_T::CEPINTSTS: RXPKIF Mask       */

#define HSUSBD_CEPINTSTS_NAKIF_Pos       (7)                                               /*!< HSUSBD_T::CEPINTSTS: NAKIF Position    */
#define HSUSBD_CEPINTSTS_NAKIF_Msk       (0x1ul << HSUSBD_CEPINTSTS_NAKIF_Pos)             /*!< HSUSBD_T::CEPINTSTS: NAKIF Mask        */

#define HSUSBD_CEPINTSTS_STALLIF_Pos     (8)                                               /*!< HSUSBD_T::CEPINTSTS: STALLIF Position  */
#define HSUSBD_CEPINTSTS_STALLIF_Msk     (0x1ul << HSUSBD_CEPINTSTS_STALLIF_Pos)           /*!< HSUSBD_T::CEPINTSTS: STALLIF Mask      */

#define HSUSBD_CEPINTSTS_ERRIF_Pos       (9)                                               /*!< HSUSBD_T::CEPINTSTS: ERRIF Position    */
#define HSUSBD_CEPINTSTS_ERRIF_Msk       (0x1ul << HSUSBD_CEPINTSTS_ERRIF_Pos)             /*!< HSUSBD_T::CEPINTSTS: ERRIF Mask        */

#define HSUSBD_CEPINTSTS_STSDONEIF_Pos   (10)                                              /*!< HSUSBD_T::CEPINTSTS: STSDONEIF Position*/
#define HSUSBD_CEPINTSTS_STSDONEIF_Msk   (0x1ul << HSUSBD_CEPINTSTS_STSDONEIF_Pos)         /*!< HSUSBD_T::CEPINTSTS: STSDONEIF Mask    */

#define HSUSBD_CEPINTSTS_BUFFULLIF_Pos   (11)                                              /*!< HSUSBD_T::CEPINTSTS: BUFFULLIF Position*/
#define HSUSBD_CEPINTSTS_BUFFULLIF_Msk   (0x1ul << HSUSBD_CEPINTSTS_BUFFULLIF_Pos)         /*!< HSUSBD_T::CEPINTSTS: BUFFULLIF Mask    */

#define HSUSBD_CEPINTSTS_BUFEMPTYIF_Pos  (12)                                              /*!< HSUSBD_T::CEPINTSTS: BUFEMPTYIF Position*/
#define HSUSBD_CEPINTSTS_BUFEMPTYIF_Msk  (0x1ul << HSUSBD_CEPINTSTS_BUFEMPTYIF_Pos)        /*!< HSUSBD_T::CEPINTSTS: BUFEMPTYIF Mask   */

#define HSUSBD_CEPTXCNT_TXCNT_Pos        (0)                                               /*!< HSUSBD_T::CEPTXCNT: TXCNT Position     */
#define HSUSBD_CEPTXCNT_TXCNT_Msk        (0xfful << HSUSBD_CEPTXCNT_TXCNT_Pos)             /*!< HSUSBD_T::CEPTXCNT: TXCNT Mask         */

#define HSUSBD_CEPRXCNT_RXCNT_Pos        (0)                                               /*!< HSUSBD_T::CEPRXCNT: RXCNT Position     */
#define HSUSBD_CEPRXCNT_RXCNT_Msk        (0xfful << HSUSBD_CEPRXCNT_RXCNT_Pos)             /*!< HSUSBD_T::CEPRXCNT: RXCNT Mask         */

#define HSUSBD_CEPDATCNT_DATCNT_Pos      (0)                                               /*!< HSUSBD_T::CEPDATCNT: DATCNT Position   */
#define HSUSBD_CEPDATCNT_DATCNT_Msk      (0xfffful << HSUSBD_CEPDATCNT_DATCNT_Pos)         /*!< HSUSBD_T::CEPDATCNT: DATCNT Mask       */

#define HSUSBD_SETUP1_0_SETUP0_Pos       (0)                                               /*!< HSUSBD_T::SETUP1_0: SETUP0 Position    */
#define HSUSBD_SETUP1_0_SETUP0_Msk       (0xfful << HSUSBD_SETUP1_0_SETUP0_Pos)            /*!< HSUSBD_T::SETUP1_0: SETUP0 Mask        */

#define HSUSBD_SETUP1_0_SETUP1_Pos       (8)                                               /*!< HSUSBD_T::SETUP1_0: SETUP1 Position    */
#define HSUSBD_SETUP1_0_SETUP1_Msk       (0xfful << HSUSBD_SETUP1_0_SETUP1_Pos)            /*!< HSUSBD_T::SETUP1_0: SETUP1 Mask        */

#define HSUSBD_SETUP3_2_SETUP2_Pos       (0)                                               /*!< HSUSBD_T::SETUP3_2: SETUP2 Position    */
#define HSUSBD_SETUP3_2_SETUP2_Msk       (0xfful << HSUSBD_SETUP3_2_SETUP2_Pos)            /*!< HSUSBD_T::SETUP3_2: SETUP2 Mask        */

#define HSUSBD_SETUP3_2_SETUP3_Pos       (8)                                               /*!< HSUSBD_T::SETUP3_2: SETUP3 Position    */
#define HSUSBD_SETUP3_2_SETUP3_Msk       (0xfful << HSUSBD_SETUP3_2_SETUP3_Pos)            /*!< HSUSBD_T::SETUP3_2: SETUP3 Mask        */

#define HSUSBD_SETUP5_4_SETUP4_Pos       (0)                                               /*!< HSUSBD_T::SETUP5_4: SETUP4 Position    */
#define HSUSBD_SETUP5_4_SETUP4_Msk       (0xfful << HSUSBD_SETUP5_4_SETUP4_Pos)            /*!< HSUSBD_T::SETUP5_4: SETUP4 Mask        */

#define HSUSBD_SETUP5_4_SETUP5_Pos       (8)                                               /*!< HSUSBD_T::SETUP5_4: SETUP5 Position    */
#define HSUSBD_SETUP5_4_SETUP5_Msk       (0xfful << HSUSBD_SETUP5_4_SETUP5_Pos)            /*!< HSUSBD_T::SETUP5_4: SETUP5 Mask        */

#define HSUSBD_SETUP7_6_SETUP6_Pos       (0)                                               /*!< HSUSBD_T::SETUP7_6: SETUP6 Position    */
#define HSUSBD_SETUP7_6_SETUP6_Msk       (0xfful << HSUSBD_SETUP7_6_SETUP6_Pos)            /*!< HSUSBD_T::SETUP7_6: SETUP6 Mask        */

#define HSUSBD_SETUP7_6_SETUP7_Pos       (8)                                               /*!< HSUSBD_T::SETUP7_6: SETUP7 Position    */
#define HSUSBD_SETUP7_6_SETUP7_Msk       (0xfful << HSUSBD_SETUP7_6_SETUP7_Pos)            /*!< HSUSBD_T::SETUP7_6: SETUP7 Mask        */

#define HSUSBD_CEPBUFST_SADDR_Pos        (0)                                               /*!< HSUSBD_T::CEPBUFST: SADDR Position     */
#define HSUSBD_CEPBUFST_SADDR_Msk        (0xffful << HSUSBD_CEPBUFST_SADDR_Pos)            /*!< HSUSBD_T::CEPBUFST: SADDR Mask         */

#define HSUSBD_CEPBUFEND_EADDR_Pos       (0)                                               /*!< HSUSBD_T::CEPBUFEND: EADDR Position    */
#define HSUSBD_CEPBUFEND_EADDR_Msk       (0xffful << HSUSBD_CEPBUFEND_EADDR_Pos)           /*!< HSUSBD_T::CEPBUFEND: EADDR Mask        */

#define HSUSBD_DMACTL_EPNUM_Pos          (0)                                               /*!< HSUSBD_T::DMACTL: EPNUM Position       */
#define HSUSBD_DMACTL_EPNUM_Msk          (0xful << HSUSBD_DMACTL_EPNUM_Pos)                /*!< HSUSBD_T::DMACTL: EPNUM Mask           */

#define HSUSBD_DMACTL_DMARD_Pos          (4)                                               /*!< HSUSBD_T::DMACTL: DMARD Position       */
#define HSUSBD_DMACTL_DMARD_Msk          (0x1ul << HSUSBD_DMACTL_DMARD_Pos)                /*!< HSUSBD_T::DMACTL: DMARD Mask           */

#define HSUSBD_DMACTL_DMAEN_Pos          (5)                                               /*!< HSUSBD_T::DMACTL: DMAEN Position       */
#define HSUSBD_DMACTL_DMAEN_Msk          (0x1ul << HSUSBD_DMACTL_DMAEN_Pos)                /*!< HSUSBD_T::DMACTL: DMAEN Mask           */

#define HSUSBD_DMACTL_SGEN_Pos           (6)                                               /*!< HSUSBD_T::DMACTL: SGEN Position        */
#define HSUSBD_DMACTL_SGEN_Msk           (0x1ul << HSUSBD_DMACTL_SGEN_Pos)                 /*!< HSUSBD_T::DMACTL: SGEN Mask            */

#define HSUSBD_DMACTL_DMARST_Pos         (7)                                               /*!< HSUSBD_T::DMACTL: DMARST Position      */
#define HSUSBD_DMACTL_DMARST_Msk         (0x1ul << HSUSBD_DMACTL_DMARST_Pos)               /*!< HSUSBD_T::DMACTL: DMARST Mask          */

#define HSUSBD_DMACTL_SVINEP_Pos         (8)                                               /*!< HSUSBD_T::DMACTL: SVINEP Position      */
#define HSUSBD_DMACTL_SVINEP_Msk         (0x1ul << HSUSBD_DMACTL_SVINEP_Pos)               /*!< HSUSBD_T::DMACTL: SVINEP Mask          */

#define HSUSBD_DMACNT_DMACNT_Pos         (0)                                               /*!< HSUSBD_T::DMACNT: DMACNT Position      */
#define HSUSBD_DMACNT_DMACNT_Msk         (0xffffful << HSUSBD_DMACNT_DMACNT_Pos)           /*!< HSUSBD_T::DMACNT: DMACNT Mask          */

#define HSUSBD_EPDAT_EPDAT_Pos           (0)                                               /*!< HSUSBD_T::EPDAT: EPDAT Position        */
#define HSUSBD_EPDAT_EPDAT_Msk           (0xfffffffful << HSUSBD_EPDAT_EPDAT_Pos)          /*!< HSUSBD_T::EPDAT: EPDAT Mask            */

#define HSUSBD_EPINTSTS_BUFFULLIF_Pos    (0)                                               /*!< HSUSBD_T::EPINTSTS: BUFFULLIF Position */
#define HSUSBD_EPINTSTS_BUFFULLIF_Msk    (0x1ul << HSUSBD_EPINTSTS_BUFFULLIF_Pos)          /*!< HSUSBD_T::EPINTSTS: BUFFULLIF Mask     */

#define HSUSBD_EPINTSTS_BUFEMPTYIF_Pos   (1)                                               /*!< HSUSBD_T::EPINTSTS: BUFEMPTYIF Position*/
#define HSUSBD_EPINTSTS_BUFEMPTYIF_Msk   (0x1ul << HSUSBD_EPINTSTS_BUFEMPTYIF_Pos)         /*!< HSUSBD_T::EPINTSTS: BUFEMPTYIF Mask    */

#define HSUSBD_EPINTSTS_SHORTTXIF_Pos    (2)                                               /*!< HSUSBD_T::EPINTSTS: SHORTTXIF Position */
#define HSUSBD_EPINTSTS_SHORTTXIF_Msk    (0x1ul << HSUSBD_EPINTSTS_SHORTTXIF_Pos)          /*!< HSUSBD_T::EPINTSTS: SHORTTXIF Mask     */

#define HSUSBD_EPINTSTS_TXPKIF_Pos       (3)                                               /*!< HSUSBD_T::EPINTSTS: TXPKIF Position    */
#define HSUSBD_EPINTSTS_TXPKIF_Msk       (0x1ul << HSUSBD_EPINTSTS_TXPKIF_Pos)             /*!< HSUSBD_T::EPINTSTS: TXPKIF Mask        */

#define HSUSBD_EPINTSTS_RXPKIF_Pos       (4)                                               /*!< HSUSBD_T::EPINTSTS: RXPKIF Position    */
#define HSUSBD_EPINTSTS_RXPKIF_Msk       (0x1ul << HSUSBD_EPINTSTS_RXPKIF_Pos)             /*!< HSUSBD_T::EPINTSTS: RXPKIF Mask        */

#define HSUSBD_EPINTSTS_OUTTKIF_Pos      (5)                                               /*!< HSUSBD_T::EPINTSTS: OUTTKIF Position   */
#define HSUSBD_EPINTSTS_OUTTKIF_Msk      (0x1ul << HSUSBD_EPINTSTS_OUTTKIF_Pos)            /*!< HSUSBD_T::EPINTSTS: OUTTKIF Mask       */

#define HSUSBD_EPINTSTS_INTKIF_Pos       (6)                                               /*!< HSUSBD_T::EPINTSTS: INTKIF Position    */
#define HSUSBD_EPINTSTS_INTKIF_Msk       (0x1ul << HSUSBD_EPINTSTS_INTKIF_Pos)             /*!< HSUSBD_T::EPINTSTS: INTKIF Mask        */

#define HSUSBD_EPINTSTS_PINGIF_Pos       (7)                                               /*!< HSUSBD_T::EPINTSTS: PINGIF Position    */
#define HSUSBD_EPINTSTS_PINGIF_Msk       (0x1ul << HSUSBD_EPINTSTS_PINGIF_Pos)             /*!< HSUSBD_T::EPINTSTS: PINGIF Mask        */

#define HSUSBD_EPINTSTS_NAKIF_Pos        (8)                                               /*!< HSUSBD_T::EPINTSTS: NAKIF Position     */
#define HSUSBD_EPINTSTS_NAKIF_Msk        (0x1ul << HSUSBD_EPINTSTS_NAKIF_Pos)              /*!< HSUSBD_T::EPINTSTS: NAKIF Mask         */

#define HSUSBD_EPINTSTS_STALLIF_Pos      (9)                                               /*!< HSUSBD_T::EPINTSTS: STALLIF Position   */
#define HSUSBD_EPINTSTS_STALLIF_Msk      (0x1ul << HSUSBD_EPINTSTS_STALLIF_Pos)            /*!< HSUSBD_T::EPINTSTS: STALLIF Mask       */

#define HSUSBD_EPINTSTS_NYETIF_Pos       (10)                                              /*!< HSUSBD_T::EPINTSTS: NYETIF Position    */
#define HSUSBD_EPINTSTS_NYETIF_Msk       (0x1ul << HSUSBD_EPINTSTS_NYETIF_Pos)             /*!< HSUSBD_T::EPINTSTS: NYETIF Mask        */

#define HSUSBD_EPINTSTS_ERRIF_Pos        (11)                                              /*!< HSUSBD_T::EPINTSTS: ERRIF Position     */
#define HSUSBD_EPINTSTS_ERRIF_Msk        (0x1ul << HSUSBD_EPINTSTS_ERRIF_Pos)              /*!< HSUSBD_T::EPINTSTS: ERRIF Mask         */

#define HSUSBD_EPINTSTS_SHORTRXIF_Pos    (12)                                              /*!< HSUSBD_T::EPINTSTS: SHORTRXIF Position */
#define HSUSBD_EPINTSTS_SHORTRXIF_Msk    (0x1ul << HSUSBD_EPINTSTS_SHORTRXIF_Pos)          /*!< HSUSBD_T::EPINTSTS: SHORTRXIF Mask     */

#define HSUSBD_EPINTEN_BUFFULLIEN_Pos    (0)                                               /*!< HSUSBD_T::EPINTEN: BUFFULLIEN Position */
#define HSUSBD_EPINTEN_BUFFULLIEN_Msk    (0x1ul << HSUSBD_EPINTEN_BUFFULLIEN_Pos)          /*!< HSUSBD_T::EPINTEN: BUFFULLIEN Mask     */

#define HSUSBD_EPINTEN_BUFEMPTYIEN_Pos   (1)                                               /*!< HSUSBD_T::EPINTEN: BUFEMPTYIEN Position*/
#define HSUSBD_EPINTEN_BUFEMPTYIEN_Msk   (0x1ul << HSUSBD_EPINTEN_BUFEMPTYIEN_Pos)         /*!< HSUSBD_T::EPINTEN: BUFEMPTYIEN Mask    */

#define HSUSBD_EPINTEN_SHORTTXIEN_Pos    (2)                                               /*!< HSUSBD_T::EPINTEN: SHORTTXIEN Position */
#define HSUSBD_EPINTEN_SHORTTXIEN_Msk    (0x1ul << HSUSBD_EPINTEN_SHORTTXIEN_Pos)          /*!< HSUSBD_T::EPINTEN: SHORTTXIEN Mask     */

#define HSUSBD_EPINTEN_TXPKIEN_Pos       (3)                                               /*!< HSUSBD_T::EPINTEN: TXPKIEN Position    */
#define HSUSBD_EPINTEN_TXPKIEN_Msk       (0x1ul << HSUSBD_EPINTEN_TXPKIEN_Pos)             /*!< HSUSBD_T::EPINTEN: TXPKIEN Mask        */

#define HSUSBD_EPINTEN_RXPKIEN_Pos       (4)                                               /*!< HSUSBD_T::EPINTEN: RXPKIEN Position    */
#define HSUSBD_EPINTEN_RXPKIEN_Msk       (0x1ul << HSUSBD_EPINTEN_RXPKIEN_Pos)             /*!< HSUSBD_T::EPINTEN: RXPKIEN Mask        */

#define HSUSBD_EPINTEN_OUTTKIEN_Pos      (5)                                               /*!< HSUSBD_T::EPINTEN: OUTTKIEN Position   */
#define HSUSBD_EPINTEN_OUTTKIEN_Msk      (0x1ul << HSUSBD_EPINTEN_OUTTKIEN_Pos)            /*!< HSUSBD_T::EPINTEN: OUTTKIEN Mask       */

#define HSUSBD_EPINTEN_INTKIEN_Pos       (6)                                               /*!< HSUSBD_T::EPINTEN: INTKIEN Position    */
#define HSUSBD_EPINTEN_INTKIEN_Msk       (0x1ul << HSUSBD_EPINTEN_INTKIEN_Pos)             /*!< HSUSBD_T::EPINTEN: INTKIEN Mask        */

#define HSUSBD_EPINTEN_PINGIEN_Pos       (7)                                               /*!< HSUSBD_T::EPINTEN: PINGIEN Position    */
#define HSUSBD_EPINTEN_PINGIEN_Msk       (0x1ul << HSUSBD_EPINTEN_PINGIEN_Pos)             /*!< HSUSBD_T::EPINTEN: PINGIEN Mask        */

#define HSUSBD_EPINTEN_NAKIEN_Pos        (8)                                               /*!< HSUSBD_T::EPINTEN: NAKIEN Position     */
#define HSUSBD_EPINTEN_NAKIEN_Msk        (0x1ul << HSUSBD_EPINTEN_NAKIEN_Pos)              /*!< HSUSBD_T::EPINTEN: NAKIEN Mask         */

#define HSUSBD_EPINTEN_STALLIEN_Pos      (9)                                               /*!< HSUSBD_T::EPINTEN: STALLIEN Position   */
#define HSUSBD_EPINTEN_STALLIEN_Msk      (0x1ul << HSUSBD_EPINTEN_STALLIEN_Pos)            /*!< HSUSBD_T::EPINTEN: STALLIEN Mask       */

#define HSUSBD_EPINTEN_NYETIEN_Pos       (10)                                              /*!< HSUSBD_T::EPINTEN: NYETIEN Position    */
#define HSUSBD_EPINTEN_NYETIEN_Msk       (0x1ul << HSUSBD_EPINTEN_NYETIEN_Pos)             /*!< HSUSBD_T::EPINTEN: NYETIEN Mask        */

#define HSUSBD_EPINTEN_ERRIEN_Pos        (11)                                              /*!< HSUSBD_T::EPINTEN: ERRIEN Position     */
#define HSUSBD_EPINTEN_ERRIEN_Msk        (0x1ul << HSUSBD_EPINTEN_ERRIEN_Pos)              /*!< HSUSBD_T::EPINTEN: ERRIEN Mask         */

#define HSUSBD_EPINTEN_SHORTRXIEN_Pos    (12)                                              /*!< HSUSBD_T::EPINTEN: SHORTRXIEN Position */
#define HSUSBD_EPINTEN_SHORTRXIEN_Msk    (0x1ul << HSUSBD_EPINTEN_SHORTRXIEN_Pos)          /*!< HSUSBD_T::EPINTEN: SHORTRXIEN Mask     */

#define HSUSBD_EPDATCNT_DATCNT_Pos       (0)                                               /*!< HSUSBD_T::EPDATCNT: DATCNT Position    */
#define HSUSBD_EPDATCNT_DATCNT_Msk       (0xfffful << HSUSBD_EPDATCNT_DATCNT_Pos)          /*!< HSUSBD_T::EPDATCNT: DATCNT Mask        */

#define HSUSBD_EPDATCNT_DMALOOP_Pos      (16)                                              /*!< HSUSBD_T::EPDATCNT: DMALOOP Position   */
#define HSUSBD_EPDATCNT_DMALOOP_Msk      (0x7ffful << HSUSBD_EPDATCNT_DMALOOP_Pos)         /*!< HSUSBD_T::EPDATCNT: DMALOOP Mask       */

#define HSUSBD_EPRSPCTL_FLUSH_Pos        (0)                                               /*!< HSUSBD_T::EPRSPCTL: FLUSH Position     */
#define HSUSBD_EPRSPCTL_FLUSH_Msk        (0x1ul << HSUSBD_EPRSPCTL_FLUSH_Pos)              /*!< HSUSBD_T::EPRSPCTL: FLUSH Mask         */

#define HSUSBD_EPRSPCTL_MODE_Pos         (1)                                               /*!< HSUSBD_T::EPRSPCTL: MODE Position      */
#define HSUSBD_EPRSPCTL_MODE_Msk         (0x3ul << HSUSBD_EPRSPCTL_MODE_Pos)               /*!< HSUSBD_T::EPRSPCTL: MODE Mask          */

#define HSUSBD_EPRSPCTL_TOGGLE_Pos       (3)                                               /*!< HSUSBD_T::EPRSPCTL: TOGGLE Position    */
#define HSUSBD_EPRSPCTL_TOGGLE_Msk       (0x1ul << HSUSBD_EPRSPCTL_TOGGLE_Pos)             /*!< HSUSBD_T::EPRSPCTL: TOGGLE Mask        */

#define HSUSBD_EPRSPCTL_HALT_Pos         (4)                                               /*!< HSUSBD_T::EPRSPCTL: HALT Position      */
#define HSUSBD_EPRSPCTL_HALT_Msk         (0x1ul << HSUSBD_EPRSPCTL_HALT_Pos)               /*!< HSUSBD_T::EPRSPCTL: HALT Mask          */

#define HSUSBD_EPRSPCTL_ZEROLEN_Pos      (5)                                               /*!< HSUSBD_T::EPRSPCTL: ZEROLEN Position   */
#define HSUSBD_EPRSPCTL_ZEROLEN_Msk      (0x1ul << HSUSBD_EPRSPCTL_ZEROLEN_Pos)            /*!< HSUSBD_T::EPRSPCTL: ZEROLEN Mask       */

#define HSUSBD_EPRSPCTL_SHORTTXEN_Pos    (6)                                               /*!< HSUSBD_T::EPRSPCTL: SHORTTXEN Position */
#define HSUSBD_EPRSPCTL_SHORTTXEN_Msk    (0x1ul << HSUSBD_EPRSPCTL_SHORTTXEN_Pos)          /*!< HSUSBD_T::EPRSPCTL: SHORTTXEN Mask     */

#define HSUSBD_EPRSPCTL_DISBUF_Pos       (7)                                               /*!< HSUSBD_T::EPRSPCTL: DISBUF Position    */
#define HSUSBD_EPRSPCTL_DISBUF_Msk       (0x1ul << HSUSBD_EPRSPCTL_DISBUF_Pos)             /*!< HSUSBD_T::EPRSPCTL: DISBUF Mask        */

#define HSUSBD_EPMPS_EPMPS_Pos           (0)                                               /*!< HSUSBD_T::EPMPS: EPMPS Position        */
#define HSUSBD_EPMPS_EPMPS_Msk           (0x7fful << HSUSBD_EPMPS_EPMPS_Pos)               /*!< HSUSBD_T::EPMPS: EPMPS Mask            */

#define HSUSBD_EPTXCNT_TXCNT_Pos         (0)                                               /*!< HSUSBD_T::EPTXCNT: TXCNT Position      */
#define HSUSBD_EPTXCNT_TXCNT_Msk         (0x7fful << HSUSBD_EPTXCNT_TXCNT_Pos)             /*!< HSUSBD_T::EPTXCNT: TXCNT Mask          */

#define HSUSBD_EPCFG_EPEN_Pos            (0)                                               /*!< HSUSBD_T::EPCFG: EPEN Position         */
#define HSUSBD_EPCFG_EPEN_Msk            (0x1ul << HSUSBD_EPCFG_EPEN_Pos)                  /*!< HSUSBD_T::EPCFG: EPEN Mask             */

#define HSUSBD_EPCFG_EPTYPE_Pos          (1)                                               /*!< HSUSBD_T::EPCFG: EPTYPE Position       */
#define HSUSBD_EPCFG_EPTYPE_Msk          (0x3ul << HSUSBD_EPCFG_EPTYPE_Pos)                /*!< HSUSBD_T::EPCFG: EPTYPE Mask           */

#define HSUSBD_EPCFG_EPDIR_Pos           (3)                                               /*!< HSUSBD_T::EPCFG: EPDIR Position        */
#define HSUSBD_EPCFG_EPDIR_Msk           (0x1ul << HSUSBD_EPCFG_EPDIR_Pos)                 /*!< HSUSBD_T::EPCFG: EPDIR Mask            */

#define HSUSBD_EPCFG_EPNUM_Pos           (4)                                               /*!< HSUSBD_T::EPCFG: EPNUM Position        */
#define HSUSBD_EPCFG_EPNUM_Msk           (0xful << HSUSBD_EPCFG_EPNUM_Pos)                 /*!< HSUSBD_T::EPCFG: EPNUM Mask            */

#define HSUSBD_EPBUFST_SADDR_Pos         (0)                                               /*!< HSUSBD_T::EPBUFST: SADDR Position      */
#define HSUSBD_EPBUFST_SADDR_Msk         (0xffful << HSUSBD_EPBUFST_SADDR_Pos)             /*!< HSUSBD_T::EPBUFST: SADDR Mask          */

#define HSUSBD_EPBUFEND_EADDR_Pos        (0)                                               /*!< HSUSBD_T::EPBUFEND: EADDR Position     */
#define HSUSBD_EPBUFEND_EADDR_Msk        (0xffful << HSUSBD_EPBUFEND_EADDR_Pos)            /*!< HSUSBD_T::EPBUFEND: EADDR Mask         */

#define HSUSBD_DMAADDR_DMAADDR_Pos       (0)                                               /*!< HSUSBD_T::DMAADDR: DMAADDR Position    */
#define HSUSBD_DMAADDR_DMAADDR_Msk       (0xfffffffful << HSUSBD_DMAADDR_DMAADDR_Pos)      /*!< HSUSBD_T::DMAADDR: DMAADDR Mask        */

#define HSUSBD_PHYCTL_DPPUEN_Pos         (8)                                               /*!< HSUSBD_T::PHYCTL: DPPUEN Position      */
#define HSUSBD_PHYCTL_DPPUEN_Msk         (0x1ul << HSUSBD_PHYCTL_DPPUEN_Pos)               /*!< HSUSBD_T::PHYCTL: DPPUEN Mask          */

#define HSUSBD_PHYCTL_PHYEN_Pos          (9)                                               /*!< HSUSBD_T::PHYCTL: PHYEN Position       */
#define HSUSBD_PHYCTL_PHYEN_Msk          (0x1ul << HSUSBD_PHYCTL_PHYEN_Pos)                /*!< HSUSBD_T::PHYCTL: PHYEN Mask           */

#define HSUSBD_PHYCTL_WKEN_Pos           (24)                                              /*!< HSUSBD_T::PHYCTL: WKEN Position        */
#define HSUSBD_PHYCTL_WKEN_Msk           (0x1ul << HSUSBD_PHYCTL_WKEN_Pos)                 /*!< HSUSBD_T::PHYCTL: WKEN Mask            */

#define HSUSBD_PHYCTL_VBUSDET_Pos        (31)                                              /*!< HSUSBD_T::PHYCTL: VBUSDET Position     */
#define HSUSBD_PHYCTL_VBUSDET_Msk        (0x1ul << HSUSBD_PHYCTL_VBUSDET_Pos)              /*!< HSUSBD_T::PHYCTL: VBUSDET Mask         */

/**@}*/ /* HSUSBD_CONST */
/**@}*/ /* end of HSUSBD register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __HSUSBD_REG_H__ */
