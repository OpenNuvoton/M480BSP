/**************************************************************************//**
 * @file     hsusbh_reg.h
 * @version  V1.00
 * @brief    HSUSBH register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __HSUSBH_REG_H__
#define __HSUSBH_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup HSUSBH High Speed USB Host Controller (HSUSBH)
    Memory Mapped Structure for HSUSBH Controller
@{ */

typedef struct
{


    /**
@var HSUSBH_T::EHCVNR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EHCVNR
</font><br><p> <font size="2">
Offset: 0x00  EHCI Version Number Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>CRLEN</td><td><div style="word-wrap: break-word;"><b>Capability Registers Length
</b><br>
This register is used as an offset to add to register base to find the beginning of the Operational Register Space.
<br>
</div></td></tr><tr><td>
[31:16]</td><td>VERSION</td><td><div style="word-wrap: break-word;"><b>Host Controller Interface Version Number
</b><br>
This is a two-byte register containing a BCD encoding of the EHCI revision number supported by this host controller
<br>
The most significant byte of this register represents a major revision and the least significant byte is the minor revision.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBH_T::EHCSPR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EHCSPR
</font><br><p> <font size="2">
Offset: 0x04  EHCI Structural Parameters Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>N_PORTS</td><td><div style="word-wrap: break-word;"><b>Number of Physical Downstream Ports
</b><br>
This field specifies the number of physical downstream ports implemented on this host controller
<br>
The value of this field determines how many port registers are addressable in the Operational Register Space (see Table 2-8)
<br>
Valid values are in the range of 1H to FH.
<br>
A zero in this field is undefined.
<br>
</div></td></tr><tr><td>
[4]</td><td>PPC</td><td><div style="word-wrap: break-word;"><b>Port Power Control
</b><br>
This field indicates whether the host controller implementation includes port power control
<br>
A one in this bit indicates the ports have port power switches
<br>
A zero in this bit indicates the port do not have port power stitches
<br>
The value of this field affects the functionality of the Port Power field in each port status and control register.
<br>
</div></td></tr><tr><td>
[11:8]</td><td>N_PCC</td><td><div style="word-wrap: break-word;"><b>Number of Ports Per Companion Controller
</b><br>
This field indicates the number of ports supported per companion host controller
<br>
It is used to indicate the port routing configuration to system software.
<br>
For example, if N_PORTS has a value of 6 and N_CC has a value of 2 then N_PCC could have a value of 3
<br>
The convention is that the first N_PCC ports are assumed to be routed to companion controller 1, the next N_PCC ports to companion controller 2, etc
<br>
In the previous example, the N_PCC could have been 4, where the first 4 are routed to companion controller 1 and the last two are routed to companion controller 2.
<br>
The number in this field must be consistent with N_PORTS and N_CC.
<br>
</div></td></tr><tr><td>
[15:12]</td><td>N_CC</td><td><div style="word-wrap: break-word;"><b>Number of Companion Controller
</b><br>
This field indicates the number of companion controllers associated with this USB 2.0 host controller.
<br>
A zero in this field indicates there are no companion host controllers
<br>
Port-ownership hand-off is not supported
<br>
Only high-speed devices are supported on the host controller root ports.
<br>
A value larger than zero in this field indicates there are companion USB 1.1 host controller(s)
<br>
Port-ownership hand-offs are supported
<br>
High, Full- and Low-speed devices are supported on the host controller root ports.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBH_T::EHCCPR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EHCCPR
</font><br><p> <font size="2">
Offset: 0x08  EHCI Capability Parameters Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>AC64</td><td><div style="word-wrap: break-word;"><b>64-bit Addressing Capability
</b><br>
0 = Data structure using 32-bit address memory pointers.
<br>
</div></td></tr><tr><td>
[1]</td><td>PFLF</td><td><div style="word-wrap: break-word;"><b>Programmable Frame List Flag
</b><br>
0 = System software must use a frame list length of 1024 elements with this EHCI host controller.
<br>
</div></td></tr><tr><td>
[2]</td><td>ASPC</td><td><div style="word-wrap: break-word;"><b>Asynchronous Schedule Park Capability
</b><br>
0 = This EHCI host controller doesn't support park feature of high-speed queue heads in the Asynchronous Schedule.
<br>
</div></td></tr><tr><td>
[7:4]</td><td>IST</td><td><div style="word-wrap: break-word;"><b>Isochronous Scheduling Threshold
</b><br>
This field indicates, relative to the current position of the executing host controller, where software can reliably update the isochronous schedule.
<br>
When bit [7] is zero, the value of the least significant 3 bits indicates the number of micro-frames a host controller can hold a set of isochronous data structures (one or more) before flushing the state.
<br>
</div></td></tr><tr><td>
[15:8]</td><td>EECP</td><td><div style="word-wrap: break-word;"><b>EHCI Extended Capabilities Pointer (EECP)
</b><br>
0 = No extended capabilities are implemented.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBH_T::UCMDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">UCMDR
</font><br><p> <font size="2">
Offset: 0x20  USB Command Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>RUN</td><td><div style="word-wrap: break-word;"><b>Run/Stop (R/W)
</b><br>
When set to a 1, the Host Controller proceeds with execution of the schedule
<br>
The Host Controller continues execution as long as this bit is set to a 1
<br>
When this bit is set to 0, the Host Controller completes the current and any actively pipelined transactions on the USB and then halts
<br>
The Host Controller must halt within 16 micro-frames after software clears the Run bit
<br>
The HC Halted bit in the status register indicates when the Host Controller has finished its pending pipelined transactions and has entered the stopped state
<br>
Software must not write a one to this field unless the host controller is in the Halted state (i.e.
<br>
HCHalted in the USBSTS register is a one)
<br>
Doing so will yield undefined results.
<br>
0 = Stop.
<br>
1 = Run.
<br>
</div></td></tr><tr><td>
[1]</td><td>HCRST</td><td><div style="word-wrap: break-word;"><b>Host Controller Reset (HCRESET) (R/W)
</b><br>
This control bit is used by software to reset the host controller
<br>
The effects of this on Root Hub registers are similar to a Chip Hardware Reset.
<br>
When software writes a one to this bit, the Host Controller resets its internal pipelines, timers, counters, state machines, etc
<br>
to their initial value
<br>
Any transaction currently in progress on USB is immediately terminated
<br>
A USB reset is not driven on downstream ports.
<br>
All operational registers, including port registers and port state machines are set to their initial values
<br>
Port ownership reverts to the companion host controller(s), with the side effects
<br>
Software must reinitialize the host controller in order to return the host controller to an operational state.
<br>
This bit is set to zero by the Host Controller when the reset process is complete
<br>
Software cannot terminate the reset process early by writing a zero to this register.
<br>
Software should not set this bit to a one when the HCHalted bit in the USBSTS register is a zero
<br>
Attempting to reset an actively running host controller will result in undefined behavior.
<br>
</div></td></tr><tr><td>
[3:2]</td><td>FLSZ</td><td><div style="word-wrap: break-word;"><b>Frame List Size (R/W or RO)
</b><br>
This field is R/W only if Programmable Frame List Flag in the HCCPARAMS registers is set to a one
<br>
This field specifies the size of the frame list
<br>
The size the frame list controls which bits in the Frame Index Register should be used for the Frame List Current index
<br>
Values mean:
<br>
00 = 1024 elements (4096 bytes) Default value.
<br>
01 = 512 elements (2048 bytes).
<br>
10 = 256 elements (1024 bytes) u2013 for resource-constrained environment.
<br>
11 = Reserved.
<br>
</div></td></tr><tr><td>
[4]</td><td>PSEN</td><td><div style="word-wrap: break-word;"><b>Periodic Schedule Enable (R/W)
</b><br>
This bit controls whether the host controller skips processing the Periodic Schedule. Values mean:
<br>
0 = Do not process the Periodic Schedule.
<br>
1 = Use the PERIODICLISTBASE register to access the Periodic Schedule.
<br>
</div></td></tr><tr><td>
[5]</td><td>ASEN</td><td><div style="word-wrap: break-word;"><b>Asynchronous Schedule Enable (R/W)
</b><br>
This bit controls whether the host controller skips processing the Asynchronous Schedule. Values mean:
<br>
0 = Do not process the Asynchronous Schedule.
<br>
1 = Use the ASYNCLISTADDR register to access the Asynchronous Schedule.
<br>
</div></td></tr><tr><td>
[6]</td><td>IAAD</td><td><div style="word-wrap: break-word;"><b>Interrupt on Asynchronous Advance Doorbell (R/W)
</b><br>
This bit is used as a doorbell by software to tell the host controller to issue an interrupt the next time it advances asynchronous schedule
<br>
Software must write a 1 to this bit to ring the doorbell.
<br>
When the host controller has evicted all appropriate cached schedule state, it sets the Interrupt on Asynchronous Advance status bit in the USBSTS register
<br>
If the Interrupt on Asynchronous Advance Enable bit in the USBINTR register is a one then the host controller will assert an interrupt at the next interrupt threshold.
<br>
The host controller sets this bit to a zero after it has set the Interrupt on Asynchronous Advance status bit in the USBSTS register to a one.
<br>
Software should not write a one to this bit when the asynchronous schedule is disabled
<br>
Doing so will yield undefined results.
<br>
</div></td></tr><tr><td>
[23:16]</td><td>ITC</td><td><div style="word-wrap: break-word;"><b>Interrupt Threshold Control (R/W)
</b><br>
This field is used by system software to select the maximum rate at which the host controller will issue interrupts
<br>
The only valid values are defined below
<br>
If software writes an invalid value to this register, the results are undefined
<br>
Value Maximum Interrupt Interval
<br>
0x00 = Reserved.
<br>
0x01 = 1 micro-frame.
<br>
0x02 = 2 micro-frames.
<br>
0x04 = 4 micro-frames.
<br>
0x08 = 8 micro-frames (default, equates to 1 ms).
<br>
0x10 = 16 micro-frames (2 ms).
<br>
0x20 = 32 micro-frames (4 ms).
<br>
0x40 = 64 micro-frames (8 ms).
<br>
Any other value in this register yields undefined results.
<br>
Software modifications to this bit while HCHalted bit is equal to zero results in undefined behavior.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBH_T::USTSR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">USTSR
</font><br><p> <font size="2">
Offset: 0x24  USB Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>USBINT</td><td><div style="word-wrap: break-word;"><b>USB Interrupt (USBINT) (R/WC)
</b><br>
The Host Controller sets this bit to 1 on the completion of a USB transaction, which results in the retirement of a Transfer Descriptor that had its IOC bit set.
<br>
The Host Controller also sets this bit to 1 when a short packet is detected (actual number of bytes received was less than the expected number of bytes).
<br>
</div></td></tr><tr><td>
[1]</td><td>UERRINT</td><td><div style="word-wrap: break-word;"><b>USB Error Interrupt (USBERRINT) (R/WC)
</b><br>
The Host Controller sets this bit to 1 when completion of a USB transaction results in an error condition (e.g., error counter underflow)
<br>
If the TD on which the error interrupt occurred also had its IOC bit set, both this bit and USBINT bit are set.
<br>
</div></td></tr><tr><td>
[2]</td><td>PCD</td><td><div style="word-wrap: break-word;"><b>Port Change Detect (R/WC)
</b><br>
The Host Controller sets this bit to a one when any port for which the Port Owner bit is set to zero has a change bit transition from a zero to a one or a Force Port Resume bit transition from a zero to a one as a result of a J-K transition detected on a suspended port
<br>
This bit will also be set as a result of the Connect Status Change being set to a one after system software has relinquished ownership of a connected port by writing a one to a port's Port Owner bit.
<br>
This bit is allowed to be maintained in the Auxiliary power well
<br>
Alternatively, it is also acceptable that on a D3 to D0 transition of the EHCI HC device, this bit is loaded with the OR of all of the PORTSC change bits (including: Force port resume, over-current change, enable/disable change and connect status change).
<br>
</div></td></tr><tr><td>
[3]</td><td>FLR</td><td><div style="word-wrap: break-word;"><b>Frame List Rollover (R/WC)
</b><br>
The Host Controller sets this bit to a one when the Frame List Index rolls over from its maximum value to zero
<br>
The exact value at which the rollover occurs depends on the frame list size
<br>
For example, if the frame list size (as programmed in the Frame List Size field of the USBCMD register) is 1024, the Frame Index Register rolls over every time FRINDEX[13] toggles
<br>
Similarly, if the size is 512, the Host Controller sets this bit to a one every time FRINDEX[12] toggles.
<br>
</div></td></tr><tr><td>
[4]</td><td>HSERR</td><td><div style="word-wrap: break-word;"><b>Host System Error (R/WC)
</b><br>
The Host Controller sets this bit to 1 when a serious error occurs during a host system access involving the Host Controller module.
<br>
</div></td></tr><tr><td>
[5]</td><td>IAA</td><td><div style="word-wrap: break-word;"><b>Interrupt on Asynchronous Advance (R/WC)
</b><br>
System software can force the host controller to issue an interrupt the next time the host controller advances the asynchronous schedule by writing a one to the Interrupt on Asynchronous Advance Doorbell bit in the USBCMD register
<br>
This status bit indicates the assertion of that interrupt source.
<br>
</div></td></tr><tr><td>
[12]</td><td>HCHalted</td><td><div style="word-wrap: break-word;"><b>HCHalted (RO)
</b><br>
This bit is a zero whenever the Run/Stop bit is a one
<br>
The Host Controller sets this bit to one after it has stopped executing as a result of the Run/Stop bit being set to 0, either by software or by the Host Controller hardware (e.g.
<br>
internal error).
<br>
</div></td></tr><tr><td>
[13]</td><td>RECLA</td><td><div style="word-wrap: break-word;"><b>Reclamation (RO)
</b><br>
This is a read-only status bit, which is used to detect an empty asynchronous schedule.
<br>
</div></td></tr><tr><td>
[14]</td><td>PSS</td><td><div style="word-wrap: break-word;"><b>Periodic Schedule Status (RO)
</b><br>
The bit reports the current real status of the Periodic Schedule
<br>
If this bit is a zero then the status of the Periodic Schedule is disabled
<br>
If this bit is a one then the status of the Periodic Schedule is enabled
<br>
The Host Controller is not required to immediately disable or enable the Periodic Schedule when software transitions the Periodic Schedule Enable bit in the USBCMD register
<br>
When this bit and the Periodic Schedule Enable bit are the same value, the Periodic Schedule is either enabled (1) or disabled (0).
<br>
</div></td></tr><tr><td>
[15]</td><td>ASS</td><td><div style="word-wrap: break-word;"><b>Asynchronous Schedule Status (RO)
</b><br>
The bit reports the current real status of the Asynchronous Schedule
<br>
If this bit is a zero then the status of them Asynchronous Schedule is disabled
<br>
If this bit is a one then the status of the Asynchronous Schedule is enabled
<br>
The Host Controller is not required to immediately disable or enable the Asynchronous Schedule when software transitions the Asynchronous Schedule Enable bit in the USBCMD register
<br>
When this bit and the Asynchronous Schedule Enable bit are the same value, the Asynchronous Schedule is either enabled (1) or disabled (0).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBH_T::UIENR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">UIENR
</font><br><p> <font size="2">
Offset: 0x28  USB Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>USBIEN</td><td><div style="word-wrap: break-word;"><b>USB Interrupt Enable or Disable Bit
</b><br>
When this bit is a one, and the USBINT bit in the USBSTS register is a one, the host controller will issue an interrupt at the next interrupt threshold
<br>
The interrupt is acknowledged by software clearing the USBINT bit.
<br>
0 = USB interrupt Disabled.
<br>
1 = USB interrupt Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>UERRIEN</td><td><div style="word-wrap: break-word;"><b>USB Error Interrupt Enable or Disable Bit
</b><br>
When this bit is a one, and the USBERRINT bit in the USBSTS register is a one, the host t controller will issue an interrupt at the next interrupt threshold
<br>
The interrupt is acknowledged by software clearing the USBERRINT bit.
<br>
0 = USB Error interrupt Disabled.
<br>
1 = USB Error interrupt Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>PCIEN</td><td><div style="word-wrap: break-word;"><b>Port Change Interrupt Enable or Disable Bit
</b><br>
When this bit is a one, and the Port Change Detect bit in the USBSTS register is a one, the host controller will issue an interrupt
<br>
The interrupt is acknowledged by software clearing the Port Change Detect bit.
<br>
0 = Port Change interrupt Disabled.
<br>
1 = Port Change interrupt Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>FLREN</td><td><div style="word-wrap: break-word;"><b>Frame List Rollover Enable or Disable Bit
</b><br>
When this bit is a one, and the Frame List Rollover bit in the USBSTS register is a one, the host controller will issue an interrupt
<br>
The interrupt is acknowledged by software clearing the Frame List Rollover bit.
<br>
0 = Frame List Rollover interrupt Disabled.
<br>
1 = Frame List Rollover interrupt Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>HSERREN</td><td><div style="word-wrap: break-word;"><b>Host System Error Enable or Disable Bit
</b><br>
When this bit is a one, and the Host System Error Status bit in the USBSTS register is a one, the host controller will issue an interrupt
<br>
The interrupt is acknowledged by software clearing the Host System Error bit.
<br>
0 = Host System Error interrupt Disabled.
<br>
1 = Host System Error interrupt Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>IAAEN</td><td><div style="word-wrap: break-word;"><b>Interrupt on Asynchronous Advance Enable or Disable Bit
</b><br>
When this bit is a one, and the Interrupt on Asynchronous Advance bit in the USBSTS register is a one, the host controller will issue an interrupt at the next interrupt threshold
<br>
The interrupt is acknowledged by software clearing the Interrupt on Asynchronous Advance bit.
<br>
0 = Interrupt on Asynchronous Advance Disabled.
<br>
1 = Interrupt on Asynchronous Advance Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBH_T::UFINDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">UFINDR
</font><br><p> <font size="2">
Offset: 0x2C  USB Frame Index Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[13:0]</td><td>FI</td><td><div style="word-wrap: break-word;"><b>Frame Index
</b><br>
The value in this register increment at the end of each time frame (e.g.
<br>
micro-frame)
<br>
Bits [N:3] are used for the Frame List current index
<br>
This means that each location of the frame list is accessed 8 times (frames or micro-frames) before moving to the next index
<br>
The following illustrates values of N based on the value of the Frame List Size field in the USBCMD register.
<br>
FLSZ (UCMDR[3:2] Number Elements N
<br>
0x0 1024 12
<br>
0x1 512 11
<br>
0x2 256 10
<br>
0x3 Reserved
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBH_T::UPFLBAR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">UPFLBAR
</font><br><p> <font size="2">
Offset: 0x34  USB Periodic Frame List Base Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:12]</td><td>BADDR</td><td><div style="word-wrap: break-word;"><b>Base Address
</b><br>
These bits correspond to memory address signals [31:12], respectively.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBH_T::UCALAR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">UCALAR
</font><br><p> <font size="2">
Offset: 0x38  USB Current Asynchronous List Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:5]</td><td>LPL</td><td><div style="word-wrap: break-word;"><b>Link Pointer Low (LPL)
</b><br>
These bits correspond to memory address signals [31:5], respectively
<br>
This field may only reference a Queue Head (QH).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBH_T::UASSTR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">UASSTR
</font><br><p> <font size="2">
Offset: 0x3C  USB Asynchronous Schedule Sleep Timer Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[11:0]</td><td>ASSTMR</td><td><div style="word-wrap: break-word;"><b>Asynchronous Schedule Sleep Timer
</b><br>
This field defines the AsyncSchedSleepTime of EHCI spec.
<br>
The asynchronous schedule sleep timer is used to control how often the host controller fetches asynchronous schedule list from system memory while the asynchronous schedule is empty.
<br>
The default value of this timer is 12'hBD6
<br>
Because this timer is implemented in UTMI clock (30MHz) domain, the default sleeping time will be about 100us.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBH_T::UCFGR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">UCFGR
</font><br><p> <font size="2">
Offset: 0x60  USB Configure Flag Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CF</td><td><div style="word-wrap: break-word;"><b>Configure Flag (CF)
</b><br>
Host software sets this bit as the last action in its process of configuring the Host Controller
<br>
This bit controls the default port-routing control logic
<br>
Bit values and side-effects are listed below.
<br>
0 = Port routing control logic default-routes each port to an implementation dependent classic host controller.
<br>
1 = Port routing control logic default-routes all ports to this host controller.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBH_T::UPSCR[2]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">UPSCR[2]
</font><br><p> <font size="2">
Offset: 0x64~0x68  USB Port 0~1 Status and Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CCS</td><td><div style="word-wrap: break-word;"><b>Current Connect Status (RO)
</b><br>
This value reflects the current state of the port, and may not correspond directly to the event that caused the Connect Status Change bit (Bit 1) to be set.
<br>
This field is zero if Port Power is zero.
<br>
0 = No device is present.
<br>
1 = Device is present on port.
<br>
</div></td></tr><tr><td>
[1]</td><td>CSC</td><td><div style="word-wrap: break-word;"><b>Connect Status Change (R/W)
</b><br>
Indicates a change has occurred in the port's Current Connect Status
<br>
The host controller sets this bit for all changes to the port device connect status, even if system software has not cleared an existing connect status change
<br>
For example, the insertion status changes twice before system software has cleared the changed condition, hub hardware will be "setting" an already-set bit (i.e., the bit will remain set).Software sets this bit to 0 by writing a 1 to it.
<br>
This field is zero if Port Power is zero.
<br>
0 = No change.
<br>
1 = Change in Current Connect Status.
<br>
</div></td></tr><tr><td>
[2]</td><td>PE</td><td><div style="word-wrap: break-word;"><b>Port Enabled/Disabled (R/W)
</b><br>
Ports can only be enabled by the host controller as a part of the reset and enable
<br>
Software cannot enable a port by writing a one to this field
<br>
The host controller will only set this bit to a one when the reset sequence determines that the attached device is a high-speed device.
<br>
Ports can be disabled by either a fault condition (disconnect event or other fault condition) or by host software
<br>
Note that the bit status does not change until the port state actually changes
<br>
There may be a delay in disabling or enabling a port due to other host controller and bus events.
<br>
When the port is disabled (0b) downstream propagation of data is blocked on this port, except for reset.
<br>
This field is zero if Port Power is zero.
<br>
0 = Port Disabled.
<br>
1 = Port Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>PEC</td><td><div style="word-wrap: break-word;"><b>Port Enable/Disable Change (R/WC)
</b><br>
For the root hub, this bit gets set to a one only when a port is disabled due to the appropriate conditions existing at the EOF2 point (See Chapter 11 of the USB Specification for the definition of a Port Error)
<br>
Software clears this bit by writing a 1 to it.
<br>
This field is zero if Port Power is zero.
<br>
0 = No change.
<br>
1 = Port enabled/disabled status has changed.
<br>
</div></td></tr><tr><td>
[4]</td><td>OCA</td><td><div style="word-wrap: break-word;"><b>Over-current Active (RO)
</b><br>
This bit will automatically transition from a one to a zero when the over current condition is removed.
<br>
0 = This port does not have an over-current condition.
<br>
1 = This port currently has an over-current condition.
<br>
</div></td></tr><tr><td>
[5]</td><td>OCC</td><td><div style="word-wrap: break-word;"><b>Over-current Change (R/WC)
</b><br>
1 = This bit gets set to a one when there is a change to Over-current Active
<br>
Software clears this bit by writing a one to this bit position.
<br>
</div></td></tr><tr><td>
[6]</td><td>FPR</td><td><div style="word-wrap: break-word;"><b>Force Port Resume (R/W)
</b><br>
This functionality defined for manipulating this bit depends on the value of the Suspend bit
<br>
For example, if the port is not suspended (Suspend and Enabled bits are a one) and software transitions this bit to a one, then the effects on the bus are undefined.
<br>
Software sets this bit to a 1 to drive resume signaling
<br>
The Host Controller sets this bit to a 1 if a J-to-K transition is detected while the port is in the Suspend state
<br>
When this bit transitions to a one because a J-to-K transition is detected, the Port Change Detect bit in the USBSTS register is also set to a one
<br>
If software sets this bit to a one, the host controller must not set the Port Change Detect bit.
<br>
Note that when the EHCI controller owns the port, the resume sequence follows the defined sequence documented in the USB Specification Revision 2.0
<br>
The resume signaling (Full-speed 'K') is driven on the port as long as this bit remains a one
<br>
Software must appropriately time the Resume and set this bit to a zero when the appropriate amount of time has elapsed
<br>
Writing a zero (from one) causes the port to return to high-speed mode (forcing the bus below the port into a high-speed idle)
<br>
This bit will remain a one until the port has switched to the high-speed idle
<br>
The host controller must complete this transition within 2 milliseconds of software setting this bit to a zero.
<br>
This field is zero if Port Power is zero.
<br>
0 = No resume (K-state) detected/driven on port.
<br>
1 = Resume detected/driven on port.
<br>
</div></td></tr><tr><td>
[7]</td><td>SUSPEND</td><td><div style="word-wrap: break-word;"><b>Suspend (R/W)
</b><br>
Port Enabled Bit and Suspend bit of this register define the port states as follows:
<br>
Port enable is 0 and suspend is 0 = Disable.
<br>
Port enable is 0 and suspend is 1 = Disable.
<br>
Port enable is 1 and suspend is 0 = Enable.
<br>
Port enable is 1 and suspend is 1 = Suspend.
<br>
When in suspend state, downstream propagation of data is blocked on this port, except for port reset
<br>
The blocking occurs at the end of the current transaction, if a transaction was in progress when this bit was written to 1
<br>
In the suspend state, the port is sensitive to resume detection
<br>
Note that the bit status does not change until the port is suspended and that there may be a delay in suspending a port if there is a transaction currently in progress on the USB.
<br>
A write of zero to this bit is ignored by the host controller
<br>
The host controller will unconditionally set this bit to a zero when:
<br>
Software sets the Force Port Resume bit to a zero (from a one).
<br>
Software sets the Port Reset bit to a one (from a zero).
<br>
If host software sets this bit to a one when the port is not enabled (i.e.
<br>
Port enabled bit is a zero) the results are undefined.
<br>
This field is zero if Port Power is zero.
<br>
0 = Port not in suspend state.
<br>
1 = Port in suspend state.
<br>
</div></td></tr><tr><td>
[8]</td><td>PRST</td><td><div style="word-wrap: break-word;"><b>Port Reset (R/W)
</b><br>
When software writes a one to this bit (from a zero), the bus reset sequence as defined in the USB Specification Revision 2.0 is started
<br>
Software writes a zero to this bit to terminate the bus reset sequence
<br>
Software must keep this bit at a one long enough to ensure the reset sequence, as specified in the USB Specification Revision 2.0, completes
<br>
Note: when software writes this bit to a one, it must also write a zero to the Port Enable bit.
<br>
Note that when software writes a zero to this bit there may be a delay before the bit status changes to a zero
<br>
The bit status will not read as a zero until after the reset has completed
<br>
If the port is in high-speed mode after reset is complete, the host controller will automatically enable this port (e.g.
<br>
set the Port Enable bit to a one)
<br>
A host controller must terminate the reset and stabilize the state of the port within 2 milliseconds of software transitioning this bit from a one to a zero
<br>
For example: if the port detects that the attached device is high-speed during reset, then the host controller must have the port in the enabled state within 2ms of software writing this bit to a zero.
<br>
The HCHalted bit in the USBSTS register should be a zero before software attempts to use this bit
<br>
The host controller may hold Port Reset asserted to a one when the HCHalted bit is a one.
<br>
This field is zero if Port Power is zero.
<br>
0 = Port is not in Reset.
<br>
1 = Port is in Reset.
<br>
</div></td></tr><tr><td>
[11:10]</td><td>LSTS</td><td><div style="word-wrap: break-word;"><b>Line Status (RO)
</b><br>
These bits reflect the current logical levels of the D+ (bit 11) and D- (bit 10) signal lines
<br>
These bits are used for detection of low-speed USB devices prior to the port reset and enable sequence
<br>
This field is valid only when the port enable bit is zero and the current connect status bit is set to a one.
<br>
The encoding of the bits are:
<br>
Bits[11:10] USB State Interpretation
<br>
00 = SE0 Not Low-speed device, perform EHCI reset.
<br>
01 = K-state Low-speed device, release ownership of port.
<br>
10 = J-state Not Low-speed device, perform EHCI reset.
<br>
11 = Undefined Not Low-speed device, perform EHCI reset.
<br>
This value of this field is undefined if Port Power is zero.
<br>
</div></td></tr><tr><td>
[12]</td><td>PP</td><td><div style="word-wrap: break-word;"><b>Port Power (PP)
</b><br>
Host controller has port power control switches
<br>
This bit represents the Current setting of the switch (0 = off, 1 = on)
<br>
When power is not available on a port (i.e.
<br>
PP equals a 0), the port is nonfunctional and will not report attaches, detaches, etc.
<br>
When an over-current condition is detected on a powered port and PPC is a one, the PP bit in each affected port may be transitioned by the host controller from a 1 to 0 (removing power from the port).
<br>
</div></td></tr><tr><td>
[13]</td><td>PO</td><td><div style="word-wrap: break-word;"><b>Port Owner (R/W)
</b><br>
This bit unconditionally goes to a 0b when the Configured bit in the CONFIGFLAG register makes a 0 to 1 transition
<br>
This bit unconditionally goes to 1 whenever the Configured bit is zero.
<br>
System software uses this field to release ownership of the port to a selected host controller (in the event that the attached device is not a high-speed device)
<br>
Software writes a one to this bit when the attached device is not a high-speed device
<br>
A one in this bit means that a companion host controller owns and controls the port.
<br>
</div></td></tr><tr><td>
[19:16]</td><td>PTC</td><td><div style="word-wrap: break-word;"><b>Port Test Control (R/W)
</b><br>
When this field is zero, the port is NOT operating in a test mode
<br>
A non-zero value indicates that it is operating in test mode and the specific test mode is indicated by the specific value
<br>
The encoding of the test mode bits are (0x6 ~ 0xF are reserved):
<br>
Bits Test Mode
<br>
0x0 = Test mode not enabled.
<br>
0x1 = Test J_STATE.
<br>
0x2 = Test K_STATE.
<br>
0x3 = Test SE0_NAK.
<br>
0x4 = Test Packet.
<br>
0x5 = Test FORCE_ENABLE.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBH_T::USBPCR0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">USBPCR0
</font><br><p> <font size="2">
Offset: 0xC4  USB PHY 0 Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[8]</td><td>SUSPEND</td><td><div style="word-wrap: break-word;"><b>Suspend Assertion
</b><br>
This bit controls the suspend mode of USB PHY 0.
<br>
While PHY was suspended, all circuits of PHY were powered down and outputs are tri-state.
<br>
This bit is 1'b0 in default
<br>
This means the USB PHY 0 is suspended in default
<br>
It is necessary to set this bit 1'b1 to make USB PHY 0 leave suspend mode before doing configuration of USB host.
<br>
0 = USB PHY 0 was suspended.
<br>
1 = USB PHY 0 was not suspended.
<br>
</div></td></tr><tr><td>
[11]</td><td>CLKVALID</td><td><div style="word-wrap: break-word;"><b>UTMI Clock Valid
</b><br>
This bit is a flag to indicate if the UTMI clock from USB 2.0 PHY is ready
<br>
S/W program must prevent to write other control registers before this UTMI clock valid flag is active.
<br>
0 = UTMI clock is not valid.
<br>
1 = UTMI clock is valid.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var HSUSBH_T::USBPCR1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">USBPCR1
</font><br><p> <font size="2">
Offset: 0xC8  USB PHY 1 Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[8]</td><td>SUSPEND</td><td><div style="word-wrap: break-word;"><b>Suspend Assertion
</b><br>
This bit controls the suspend mode of USB PHY 1.
<br>
While PHY was suspended, all circuits of PHY were powered down and outputs are tri-state.
<br>
This bit is 1'b0 in default
<br>
This means the USB PHY 0 is suspended in default
<br>
It is necessary to set this bit 1'b1 to make USB PHY 0 leave suspend mode before doing configuration of USB host.
<br>
0 = USB PHY 1 was suspended.
<br>
1 = USB PHY 1 was not suspended.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __I  uint32_t EHCVNR;                /*!< [0x0000] EHCI Version Number Register                                     */
    __I  uint32_t EHCSPR;                /*!< [0x0004] EHCI Structural Parameters Register                              */
    __I  uint32_t EHCCPR;                /*!< [0x0008] EHCI Capability Parameters Register                              */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[5];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t UCMDR;                 /*!< [0x0020] USB Command Register                                             */
    __IO uint32_t USTSR;                 /*!< [0x0024] USB Status Register                                              */
    __IO uint32_t UIENR;                 /*!< [0x0028] USB Interrupt Enable Register                                    */
    __IO uint32_t UFINDR;                /*!< [0x002c] USB Frame Index Register                                         */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t UPFLBAR;               /*!< [0x0034] USB Periodic Frame List Base Address Register                    */
    __IO uint32_t UCALAR;                /*!< [0x0038] USB Current Asynchronous List Address Register                   */
    __IO uint32_t UASSTR;                /*!< [0x003c] USB Asynchronous Schedule Sleep Timer Register                   */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE2[8];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t UCFGR;                 /*!< [0x0060] USB Configure Flag Register                                      */
    __IO uint32_t UPSCR[2];              /*!< [0x0064] ~ [0x0068] USB Port 0 & 1 Status and Control Register                           */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE3[22];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t USBPCR0;               /*!< [0x00c4] USB PHY 0 Control Register                                       */
    __IO uint32_t USBPCR1;               /*!< [0x00c8] USB PHY 1 Control Register                                       */

} HSUSBH_T;

/**
    @addtogroup HSUSBH_CONST HSUSBH Bit Field Definition
    Constant Definitions for HSUSBH Controller
@{ */

#define HSUSBH_EHCVNR_CRLEN_Pos          (0)                                               /*!< HSUSBH_T::EHCVNR: CRLEN Position       */
#define HSUSBH_EHCVNR_CRLEN_Msk          (0xfful << HSUSBH_EHCVNR_CRLEN_Pos)               /*!< HSUSBH_T::EHCVNR: CRLEN Mask           */

#define HSUSBH_EHCVNR_VERSION_Pos        (16)                                              /*!< HSUSBH_T::EHCVNR: VERSION Position     */
#define HSUSBH_EHCVNR_VERSION_Msk        (0xfffful << HSUSBH_EHCVNR_VERSION_Pos)           /*!< HSUSBH_T::EHCVNR: VERSION Mask         */

#define HSUSBH_EHCSPR_N_PORTS_Pos        (0)                                               /*!< HSUSBH_T::EHCSPR: N_PORTS Position     */
#define HSUSBH_EHCSPR_N_PORTS_Msk        (0xful << HSUSBH_EHCSPR_N_PORTS_Pos)              /*!< HSUSBH_T::EHCSPR: N_PORTS Mask         */

#define HSUSBH_EHCSPR_PPC_Pos            (4)                                               /*!< HSUSBH_T::EHCSPR: PPC Position         */
#define HSUSBH_EHCSPR_PPC_Msk            (0x1ul << HSUSBH_EHCSPR_PPC_Pos)                  /*!< HSUSBH_T::EHCSPR: PPC Mask             */

#define HSUSBH_EHCSPR_N_PCC_Pos          (8)                                               /*!< HSUSBH_T::EHCSPR: N_PCC Position       */
#define HSUSBH_EHCSPR_N_PCC_Msk          (0xful << HSUSBH_EHCSPR_N_PCC_Pos)                /*!< HSUSBH_T::EHCSPR: N_PCC Mask           */

#define HSUSBH_EHCSPR_N_CC_Pos           (12)                                              /*!< HSUSBH_T::EHCSPR: N_CC Position        */
#define HSUSBH_EHCSPR_N_CC_Msk           (0xful << HSUSBH_EHCSPR_N_CC_Pos)                 /*!< HSUSBH_T::EHCSPR: N_CC Mask            */

#define HSUSBH_EHCCPR_AC64_Pos           (0)                                               /*!< HSUSBH_T::EHCCPR: AC64 Position        */
#define HSUSBH_EHCCPR_AC64_Msk           (0x1ul << HSUSBH_EHCCPR_AC64_Pos)                 /*!< HSUSBH_T::EHCCPR: AC64 Mask            */

#define HSUSBH_EHCCPR_PFLF_Pos           (1)                                               /*!< HSUSBH_T::EHCCPR: PFLF Position        */
#define HSUSBH_EHCCPR_PFLF_Msk           (0x1ul << HSUSBH_EHCCPR_PFLF_Pos)                 /*!< HSUSBH_T::EHCCPR: PFLF Mask            */

#define HSUSBH_EHCCPR_ASPC_Pos           (2)                                               /*!< HSUSBH_T::EHCCPR: ASPC Position        */
#define HSUSBH_EHCCPR_ASPC_Msk           (0x1ul << HSUSBH_EHCCPR_ASPC_Pos)                 /*!< HSUSBH_T::EHCCPR: ASPC Mask            */

#define HSUSBH_EHCCPR_IST_Pos            (4)                                               /*!< HSUSBH_T::EHCCPR: IST Position         */
#define HSUSBH_EHCCPR_IST_Msk            (0xful << HSUSBH_EHCCPR_IST_Pos)                  /*!< HSUSBH_T::EHCCPR: IST Mask             */

#define HSUSBH_EHCCPR_EECP_Pos           (8)                                               /*!< HSUSBH_T::EHCCPR: EECP Position        */
#define HSUSBH_EHCCPR_EECP_Msk           (0xfful << HSUSBH_EHCCPR_EECP_Pos)                /*!< HSUSBH_T::EHCCPR: EECP Mask            */

#define HSUSBH_UCMDR_RUN_Pos             (0)                                               /*!< HSUSBH_T::UCMDR: RUN Position          */
#define HSUSBH_UCMDR_RUN_Msk             (0x1ul << HSUSBH_UCMDR_RUN_Pos)                   /*!< HSUSBH_T::UCMDR: RUN Mask              */

#define HSUSBH_UCMDR_HCRST_Pos           (1)                                               /*!< HSUSBH_T::UCMDR: HCRST Position        */
#define HSUSBH_UCMDR_HCRST_Msk           (0x1ul << HSUSBH_UCMDR_HCRST_Pos)                 /*!< HSUSBH_T::UCMDR: HCRST Mask            */

#define HSUSBH_UCMDR_FLSZ_Pos            (2)                                               /*!< HSUSBH_T::UCMDR: FLSZ Position         */
#define HSUSBH_UCMDR_FLSZ_Msk            (0x3ul << HSUSBH_UCMDR_FLSZ_Pos)                  /*!< HSUSBH_T::UCMDR: FLSZ Mask             */

#define HSUSBH_UCMDR_PSEN_Pos            (4)                                               /*!< HSUSBH_T::UCMDR: PSEN Position         */
#define HSUSBH_UCMDR_PSEN_Msk            (0x1ul << HSUSBH_UCMDR_PSEN_Pos)                  /*!< HSUSBH_T::UCMDR: PSEN Mask             */

#define HSUSBH_UCMDR_ASEN_Pos            (5)                                               /*!< HSUSBH_T::UCMDR: ASEN Position         */
#define HSUSBH_UCMDR_ASEN_Msk            (0x1ul << HSUSBH_UCMDR_ASEN_Pos)                  /*!< HSUSBH_T::UCMDR: ASEN Mask             */

#define HSUSBH_UCMDR_IAAD_Pos            (6)                                               /*!< HSUSBH_T::UCMDR: IAAD Position         */
#define HSUSBH_UCMDR_IAAD_Msk            (0x1ul << HSUSBH_UCMDR_IAAD_Pos)                  /*!< HSUSBH_T::UCMDR: IAAD Mask             */

#define HSUSBH_UCMDR_ITC_Pos             (16)                                              /*!< HSUSBH_T::UCMDR: ITC Position          */
#define HSUSBH_UCMDR_ITC_Msk             (0xfful << HSUSBH_UCMDR_ITC_Pos)                  /*!< HSUSBH_T::UCMDR: ITC Mask              */

#define HSUSBH_USTSR_USBINT_Pos          (0)                                               /*!< HSUSBH_T::USTSR: USBINT Position       */
#define HSUSBH_USTSR_USBINT_Msk          (0x1ul << HSUSBH_USTSR_USBINT_Pos)                /*!< HSUSBH_T::USTSR: USBINT Mask           */

#define HSUSBH_USTSR_UERRINT_Pos         (1)                                               /*!< HSUSBH_T::USTSR: UERRINT Position      */
#define HSUSBH_USTSR_UERRINT_Msk         (0x1ul << HSUSBH_USTSR_UERRINT_Pos)               /*!< HSUSBH_T::USTSR: UERRINT Mask          */

#define HSUSBH_USTSR_PCD_Pos             (2)                                               /*!< HSUSBH_T::USTSR: PCD Position          */
#define HSUSBH_USTSR_PCD_Msk             (0x1ul << HSUSBH_USTSR_PCD_Pos)                   /*!< HSUSBH_T::USTSR: PCD Mask              */

#define HSUSBH_USTSR_FLR_Pos             (3)                                               /*!< HSUSBH_T::USTSR: FLR Position          */
#define HSUSBH_USTSR_FLR_Msk             (0x1ul << HSUSBH_USTSR_FLR_Pos)                   /*!< HSUSBH_T::USTSR: FLR Mask              */

#define HSUSBH_USTSR_HSERR_Pos           (4)                                               /*!< HSUSBH_T::USTSR: HSERR Position        */
#define HSUSBH_USTSR_HSERR_Msk           (0x1ul << HSUSBH_USTSR_HSERR_Pos)                 /*!< HSUSBH_T::USTSR: HSERR Mask            */

#define HSUSBH_USTSR_IAA_Pos             (5)                                               /*!< HSUSBH_T::USTSR: IAA Position          */
#define HSUSBH_USTSR_IAA_Msk             (0x1ul << HSUSBH_USTSR_IAA_Pos)                   /*!< HSUSBH_T::USTSR: IAA Mask              */

#define HSUSBH_USTSR_HCHalted_Pos        (12)                                              /*!< HSUSBH_T::USTSR: HCHalted Position     */
#define HSUSBH_USTSR_HCHalted_Msk        (0x1ul << HSUSBH_USTSR_HCHalted_Pos)              /*!< HSUSBH_T::USTSR: HCHalted Mask         */

#define HSUSBH_USTSR_RECLA_Pos           (13)                                              /*!< HSUSBH_T::USTSR: RECLA Position        */
#define HSUSBH_USTSR_RECLA_Msk           (0x1ul << HSUSBH_USTSR_RECLA_Pos)                 /*!< HSUSBH_T::USTSR: RECLA Mask            */

#define HSUSBH_USTSR_PSS_Pos             (14)                                              /*!< HSUSBH_T::USTSR: PSS Position          */
#define HSUSBH_USTSR_PSS_Msk             (0x1ul << HSUSBH_USTSR_PSS_Pos)                   /*!< HSUSBH_T::USTSR: PSS Mask              */

#define HSUSBH_USTSR_ASS_Pos             (15)                                              /*!< HSUSBH_T::USTSR: ASS Position          */
#define HSUSBH_USTSR_ASS_Msk             (0x1ul << HSUSBH_USTSR_ASS_Pos)                   /*!< HSUSBH_T::USTSR: ASS Mask              */

#define HSUSBH_UIENR_USBIEN_Pos          (0)                                               /*!< HSUSBH_T::UIENR: USBIEN Position       */
#define HSUSBH_UIENR_USBIEN_Msk          (0x1ul << HSUSBH_UIENR_USBIEN_Pos)                /*!< HSUSBH_T::UIENR: USBIEN Mask           */

#define HSUSBH_UIENR_UERRIEN_Pos         (1)                                               /*!< HSUSBH_T::UIENR: UERRIEN Position      */
#define HSUSBH_UIENR_UERRIEN_Msk         (0x1ul << HSUSBH_UIENR_UERRIEN_Pos)               /*!< HSUSBH_T::UIENR: UERRIEN Mask          */

#define HSUSBH_UIENR_PCIEN_Pos           (2)                                               /*!< HSUSBH_T::UIENR: PCIEN Position        */
#define HSUSBH_UIENR_PCIEN_Msk           (0x1ul << HSUSBH_UIENR_PCIEN_Pos)                 /*!< HSUSBH_T::UIENR: PCIEN Mask            */

#define HSUSBH_UIENR_FLREN_Pos           (3)                                               /*!< HSUSBH_T::UIENR: FLREN Position        */
#define HSUSBH_UIENR_FLREN_Msk           (0x1ul << HSUSBH_UIENR_FLREN_Pos)                 /*!< HSUSBH_T::UIENR: FLREN Mask            */

#define HSUSBH_UIENR_HSERREN_Pos         (4)                                               /*!< HSUSBH_T::UIENR: HSERREN Position      */
#define HSUSBH_UIENR_HSERREN_Msk         (0x1ul << HSUSBH_UIENR_HSERREN_Pos)               /*!< HSUSBH_T::UIENR: HSERREN Mask          */

#define HSUSBH_UIENR_IAAEN_Pos           (5)                                               /*!< HSUSBH_T::UIENR: IAAEN Position        */
#define HSUSBH_UIENR_IAAEN_Msk           (0x1ul << HSUSBH_UIENR_IAAEN_Pos)                 /*!< HSUSBH_T::UIENR: IAAEN Mask            */

#define HSUSBH_UFINDR_FI_Pos             (0)                                               /*!< HSUSBH_T::UFINDR: FI Position          */
#define HSUSBH_UFINDR_FI_Msk             (0x3ffful << HSUSBH_UFINDR_FI_Pos)                /*!< HSUSBH_T::UFINDR: FI Mask              */

#define HSUSBH_UPFLBAR_BADDR_Pos         (12)                                              /*!< HSUSBH_T::UPFLBAR: BADDR Position      */
#define HSUSBH_UPFLBAR_BADDR_Msk         (0xffffful << HSUSBH_UPFLBAR_BADDR_Pos)           /*!< HSUSBH_T::UPFLBAR: BADDR Mask          */

#define HSUSBH_UCALAR_LPL_Pos            (5)                                               /*!< HSUSBH_T::UCALAR: LPL Position         */
#define HSUSBH_UCALAR_LPL_Msk            (0x7fffffful << HSUSBH_UCALAR_LPL_Pos)            /*!< HSUSBH_T::UCALAR: LPL Mask             */

#define HSUSBH_UASSTR_ASSTMR_Pos         (0)                                               /*!< HSUSBH_T::UASSTR: ASSTMR Position      */
#define HSUSBH_UASSTR_ASSTMR_Msk         (0xffful << HSUSBH_UASSTR_ASSTMR_Pos)             /*!< HSUSBH_T::UASSTR: ASSTMR Mask          */

#define HSUSBH_UCFGR_CF_Pos              (0)                                               /*!< HSUSBH_T::UCFGR: CF Position           */
#define HSUSBH_UCFGR_CF_Msk              (0x1ul << HSUSBH_UCFGR_CF_Pos)                    /*!< HSUSBH_T::UCFGR: CF Mask               */

#define HSUSBH_UPSCR_CCS_Pos             (0)                                               /*!< HSUSBH_T::UPSCR[2]: CCS Position       */
#define HSUSBH_UPSCR_CCS_Msk             (0x1ul << HSUSBH_UPSCR_CCS_Pos)                   /*!< HSUSBH_T::UPSCR[2]: CCS Mask           */

#define HSUSBH_UPSCR_CSC_Pos             (1)                                               /*!< HSUSBH_T::UPSCR[2]: CSC Position       */
#define HSUSBH_UPSCR_CSC_Msk             (0x1ul << HSUSBH_UPSCR_CSC_Pos)                   /*!< HSUSBH_T::UPSCR[2]: CSC Mask           */

#define HSUSBH_UPSCR_PE_Pos              (2)                                               /*!< HSUSBH_T::UPSCR[2]: PE Position        */
#define HSUSBH_UPSCR_PE_Msk              (0x1ul << HSUSBH_UPSCR_PE_Pos)                    /*!< HSUSBH_T::UPSCR[2]: PE Mask            */

#define HSUSBH_UPSCR_PEC_Pos             (3)                                               /*!< HSUSBH_T::UPSCR[2]: PEC Position       */
#define HSUSBH_UPSCR_PEC_Msk             (0x1ul << HSUSBH_UPSCR_PEC_Pos)                   /*!< HSUSBH_T::UPSCR[2]: PEC Mask           */

#define HSUSBH_UPSCR_OCA_Pos             (4)                                               /*!< HSUSBH_T::UPSCR[2]: OCA Position       */
#define HSUSBH_UPSCR_OCA_Msk             (0x1ul << HSUSBH_UPSCR_OCA_Pos)                   /*!< HSUSBH_T::UPSCR[2]: OCA Mask           */

#define HSUSBH_UPSCR_OCC_Pos             (5)                                               /*!< HSUSBH_T::UPSCR[2]: OCC Position       */
#define HSUSBH_UPSCR_OCC_Msk             (0x1ul << HSUSBH_UPSCR_OCC_Pos)                   /*!< HSUSBH_T::UPSCR[2]: OCC Mask           */

#define HSUSBH_UPSCR_FPR_Pos             (6)                                               /*!< HSUSBH_T::UPSCR[2]: FPR Position       */
#define HSUSBH_UPSCR_FPR_Msk             (0x1ul << HSUSBH_UPSCR_FPR_Pos)                   /*!< HSUSBH_T::UPSCR[2]: FPR Mask           */

#define HSUSBH_UPSCR_SUSPEND_Pos         (7)                                               /*!< HSUSBH_T::UPSCR[2]: SUSPEND Position   */
#define HSUSBH_UPSCR_SUSPEND_Msk         (0x1ul << HSUSBH_UPSCR_SUSPEND_Pos)               /*!< HSUSBH_T::UPSCR[2]: SUSPEND Mask       */

#define HSUSBH_UPSCR_PRST_Pos            (8)                                               /*!< HSUSBH_T::UPSCR[2]: PRST Position      */
#define HSUSBH_UPSCR_PRST_Msk            (0x1ul << HSUSBH_UPSCR_PRST_Pos)                  /*!< HSUSBH_T::UPSCR[2]: PRST Mask          */

#define HSUSBH_UPSCR_LSTS_Pos            (10)                                              /*!< HSUSBH_T::UPSCR[2]: LSTS Position      */
#define HSUSBH_UPSCR_LSTS_Msk            (0x3ul << HSUSBH_UPSCR_LSTS_Pos)                  /*!< HSUSBH_T::UPSCR[2]: LSTS Mask          */

#define HSUSBH_UPSCR_PP_Pos              (12)                                              /*!< HSUSBH_T::UPSCR[2]: PP Position        */
#define HSUSBH_UPSCR_PP_Msk              (0x1ul << HSUSBH_UPSCR_PP_Pos)                    /*!< HSUSBH_T::UPSCR[2]: PP Mask            */

#define HSUSBH_UPSCR_PO_Pos              (13)                                              /*!< HSUSBH_T::UPSCR[2]: PO Position        */
#define HSUSBH_UPSCR_PO_Msk              (0x1ul << HSUSBH_UPSCR_PO_Pos)                    /*!< HSUSBH_T::UPSCR[2]: PO Mask            */

#define HSUSBH_UPSCR_PTC_Pos             (16)                                              /*!< HSUSBH_T::UPSCR[2]: PTC Position       */
#define HSUSBH_UPSCR_PTC_Msk             (0xful << HSUSBH_UPSCR_PTC_Pos)                   /*!< HSUSBH_T::UPSCR[2]: PTC Mask           */

#define HSUSBH_USBPCR0_SUSPEND_Pos       (8)                                               /*!< HSUSBH_T::USBPCR0: SUSPEND Position    */
#define HSUSBH_USBPCR0_SUSPEND_Msk       (0x1ul << HSUSBH_USBPCR0_SUSPEND_Pos)             /*!< HSUSBH_T::USBPCR0: SUSPEND Mask        */

#define HSUSBH_USBPCR0_CLKVALID_Pos      (11)                                              /*!< HSUSBH_T::USBPCR0: CLKVALID Position   */
#define HSUSBH_USBPCR0_CLKVALID_Msk      (0x1ul << HSUSBH_USBPCR0_CLKVALID_Pos)            /*!< HSUSBH_T::USBPCR0: CLKVALID Mask       */

#define HSUSBH_USBPCR1_SUSPEND_Pos       (8)                                               /*!< HSUSBH_T::USBPCR1: SUSPEND Position    */
#define HSUSBH_USBPCR1_SUSPEND_Msk       (0x1ul << HSUSBH_USBPCR1_SUSPEND_Pos)             /*!< HSUSBH_T::USBPCR1: SUSPEND Mask        */

/**@}*/ /* HSUSBH_CONST */
/**@}*/ /* end of HSUSBH register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __HSUSBH_REG_H__ */
