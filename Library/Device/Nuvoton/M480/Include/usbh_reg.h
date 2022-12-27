/**************************************************************************//**
 * @file     usbh_reg.h
 * @version  V1.00
 * @brief    USBH register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __USBH_REG_H__
#define __USBH_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup USBH USB Host Controller(USBH)
    Memory Mapped Structure for USBH Controller
@{ */

typedef struct
{

    /**
@var USBH_T::HcRevision

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcRevision
</font><br><p> <font size="2">
Offset: 0x00  Host Controller Revision Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>REV</td><td><div style="word-wrap: break-word;"><b>Revision Number
</b><br>
Indicates the Open HCI Specification revision number implemented by the Hardware
<br>
Host Controller supports 1.1 specification.
<br>
(X.Y = XYh).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcControl

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcControl
</font><br><p> <font size="2">
Offset: 0x04  Host Controller Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1:0]</td><td>CBSR</td><td><div style="word-wrap: break-word;"><b>Control Bulk Service Ratio
</b><br>
This specifies the service ratio between Control and Bulk EDs
<br>
Before processing any of the non-periodic lists, HC must compare the ratio specified with its internal count on how many nonempty Control EDs have been processed, in determining whether to continue serving another Control ED or switching to Bulk EDs
<br>
The internal count will be retained when crossing the frame boundary
<br>
In case of reset, HCD is responsible for restoring this
<br>
Value.
<br>
00 = Number of Control EDs over Bulk EDs served is 1:1.
<br>
01 = Number of Control EDs over Bulk EDs served is 2:1.
<br>
10 = Number of Control EDs over Bulk EDs served is 3:1.
<br>
11 = Number of Control EDs over Bulk EDs served is 4:1.
<br>
</div></td></tr><tr><td>
[2]</td><td>PLE</td><td><div style="word-wrap: break-word;"><b>Periodic List Enable Bit
</b><br>
When set, this bit enables processing of the Periodic (interrupt and isochronous) list
<br>
The Host Controller checks this bit prior to attempting any periodic transfers in a frame.
<br>
0 = Processing of the Periodic (Interrupt and Isochronous) list after next SOF (Start-Of-Frame) Disabled.
<br>
1 = Processing of the Periodic (Interrupt and Isochronous) list in the next frame Enabled.
<br>
Note: To enable the processing of the Isochronous list, user has to set both PLE and IE (HcControl[3]) high.
<br>
</div></td></tr><tr><td>
[3]</td><td>IE</td><td><div style="word-wrap: break-word;"><b>Isochronous List Enable Bit
</b><br>
Both ISOEn and PLE (HcControl[2]) high enables Host Controller to process the Isochronous list
<br>
Either ISOEn or PLE (HcControl[2]) is low disables Host Controller to process the Isochronous list.
<br>
0 = Processing of the Isochronous list after next SOF (Start-Of-Frame) Disabled.
<br>
1 = Processing of the Isochronous list in the next frame Enabled, if the PLE (HcControl[2]) is high, too.
<br>
</div></td></tr><tr><td>
[4]</td><td>CLE</td><td><div style="word-wrap: break-word;"><b>Control List Enable Bit
</b><br>
0 = Processing of the Control list after next SOF (Start-Of-Frame) Disabled.
<br>
1 = Processing of the Control list in the next frame Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>BLE</td><td><div style="word-wrap: break-word;"><b>Bulk List Enable Bit
</b><br>
0 = Processing of the Bulk list after next SOF (Start-Of-Frame) Disabled.
<br>
1 = Processing of the Bulk list in the next frame Enabled.
<br>
</div></td></tr><tr><td>
[7:6]</td><td>HCFS</td><td><div style="word-wrap: break-word;"><b>Host Controller Functional State
</b><br>
This field sets the Host Controller state
<br>
The Controller may force a state change from USBSUSPEND to USBRESUME after detecting resume signaling from a downstream port
<br>
States are:
<br>
00 = USBSUSPEND.
<br>
01 = USBOPERATIONAL.
<br>
10 = USBRESUME.
<br>
11 = USBRESET.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcCommandStatus

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcCommandStatus
</font><br><p> <font size="2">
Offset: 0x08  Host Controller Command Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>HCR</td><td><div style="word-wrap: break-word;"><b>Host Controller Reset
</b><br>
This bit is set to initiate the software reset of Host Controller
<br>
This bit is cleared by the Host Controller, upon completed of the reset operation.
<br>
This bit, when set, didn't reset the Root Hub and no subsequent reset signaling be asserted to its downstream ports.
<br>
0 = Host Controller is not in software reset state.
<br>
1 = Host Controller is in software reset state.
<br>
</div></td></tr><tr><td>
[1]</td><td>CLF</td><td><div style="word-wrap: break-word;"><b>Control List Filled
</b><br>
Set high to indicate there is an active TD on the Control List
<br>
It may be set by either software or the Host Controller and cleared by the Host Controller each time it begins processing the head of the Control List.
<br>
0 = No active TD found or Host Controller begins to process the head of the Control list.
<br>
1 = An active TD added or found on the Control list.
<br>
</div></td></tr><tr><td>
[2]</td><td>BLF</td><td><div style="word-wrap: break-word;"><b>Bulk List Filled
</b><br>
Set high to indicate there is an active TD on the Bulk list
<br>
This bit may be set by either software or the Host Controller and cleared by the Host Controller each time it begins processing the head of the Bulk list.
<br>
0 = No active TD found or Host Controller begins to process the head of the Bulk list.
<br>
1 = An active TD added or found on the Bulk list.
<br>
</div></td></tr><tr><td>
[17:16]</td><td>SOC</td><td><div style="word-wrap: break-word;"><b>Schedule Overrun Count
</b><br>
These bits are incremented on each scheduling overrun error
<br>
It is initialized to 00b and wraps around at 11b
<br>
This will be incremented when a scheduling overrun is detected even if SO (HcInterruptStatus[0]) has already been set.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcInterruptStatus

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcInterruptStatus
</font><br><p> <font size="2">
Offset: 0x0C  Host Controller Interrupt Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SO</td><td><div style="word-wrap: break-word;"><b>Scheduling Overrun
</b><br>
Set when the List Processor determines a Schedule Overrun has occurred.
<br>
0 = Schedule Overrun didn't occur.
<br>
1 = Schedule Overrun has occurred.
<br>
</div></td></tr><tr><td>
[1]</td><td>WDH</td><td><div style="word-wrap: break-word;"><b>Write Back Done Head
</b><br>
Set after the Host Controller has written HcDoneHead to HccaDoneHead
<br>
Further updates of the HccaDoneHead will not occur until this bit has been cleared.
<br>
0 =.Host Controller didn't update HccaDoneHead.
<br>
1 =.Host Controller has written HcDoneHead to HccaDoneHead.
<br>
</div></td></tr><tr><td>
[2]</td><td>SF</td><td><div style="word-wrap: break-word;"><b>Start of Frame
</b><br>
Set when the Frame Management functional block signals a 'Start of Frame' event
<br>
Host Control generates a SOF token at the same time.
<br>
0 =.Not the start of a frame.
<br>
1 =.Indicate the start of a frame and Host Controller generates a SOF token.
<br>
</div></td></tr><tr><td>
[3]</td><td>RD</td><td><div style="word-wrap: break-word;"><b>Resume Detected
</b><br>
Set when Host Controller detects resume signaling on a downstream port.
<br>
0 = No resume signaling detected on a downstream port.
<br>
1 = Resume signaling detected on a downstream port.
<br>
</div></td></tr><tr><td>
[5]</td><td>FNO</td><td><div style="word-wrap: break-word;"><b>Frame Number Overflow
</b><br>
This bit is set when bit 15 of Frame Number changes from 1 to 0 or from 0 to 1.
<br>
0 = The bit 15 of Frame Number didn't change.
<br>
1 = The bit 15 of Frame Number changes from 1 to 0 or from 0 to 1.
<br>
</div></td></tr><tr><td>
[6]</td><td>RHSC</td><td><div style="word-wrap: break-word;"><b>Root Hub Status Change
</b><br>
This bit is set when the content of HcRhStatus or the content of HcRhPortStatus register has changed.
<br>
0 = The content of HcRhStatus and the content of HcRhPortStatus register didn't change.
<br>
1 = The content of HcRhStatus or the content of HcRhPortStatus register has changed.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcInterruptEnable

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcInterruptEnable
</font><br><p> <font size="2">
Offset: 0x10  Host Controller Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SO</td><td><div style="word-wrap: break-word;"><b>Scheduling Overrun Enable Bit
</b><br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Interrupt generation due to SO (HcInterruptStatus[0]) Enabled.
<br>
Read Operation:
<br>
0 = Interrupt generation due to SO (HcInterruptStatus[0]) Disabled.
<br>
1 = Interrupt generation due to SO (HcInterruptStatus[0]) Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>WDH</td><td><div style="word-wrap: break-word;"><b>Write Back Done Head Enable Bit
</b><br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Interrupt generation due to WDH (HcInterruptStatus[1]) Enabled.
<br>
Read Operation:
<br>
0 = Interrupt generation due to WDH (HcInterruptStatus[1]) Disabled.
<br>
1 = Interrupt generation due to WDH (HcInterruptStatus[1]) Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>SF</td><td><div style="word-wrap: break-word;"><b>Start of Frame Enable Bit
</b><br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Interrupt generation due to SF (HcInterruptStatus[2]) Enabled.
<br>
Read Operation:
<br>
0 = Interrupt generation due to SF (HcInterruptStatus[2]) Disabled.
<br>
1 = Interrupt generation due to SF (HcInterruptStatus[2]) Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>RD</td><td><div style="word-wrap: break-word;"><b>Resume Detected Enable Bit
</b><br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Interrupt generation due to RD (HcInterruptStatus[3]) Enabled.
<br>
Read Operation:
<br>
0 = Interrupt generation due to RD (HcInterruptStatus[3]) Disabled.
<br>
1 = Interrupt generation due to RD (HcInterruptStatus[3]) Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>FNO</td><td><div style="word-wrap: break-word;"><b>Frame Number Overflow Enable Bit
</b><br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Interrupt generation due to FNO (HcInterruptStatus[5]) Enabled.
<br>
Read Operation:
<br>
0 = Interrupt generation due to FNO (HcInterruptStatus[5]) Disabled.
<br>
1 = Interrupt generation due to FNO (HcInterruptStatus[5]) Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>RHSC</td><td><div style="word-wrap: break-word;"><b>Root Hub Status Change Enable Bit
</b><br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Interrupt generation due to RHSC (HcInterruptStatus[6]) Enabled.
<br>
Read Operation:
<br>
0 = Interrupt generation due to RHSC (HcInterruptStatus[6]) Disabled.
<br>
1 = Interrupt generation due to RHSC (HcInterruptStatus[6]) Enabled.
<br>
</div></td></tr><tr><td>
[31]</td><td>MIE</td><td><div style="word-wrap: break-word;"><b>Master Interrupt Enable Bit
</b><br>
This bit is a global interrupt enable
<br>
A write of '1' allows interrupts to be enabled via the specific enable bits listed above.
<br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Interrupt generation due to RHSC (HcInterruptStatus[6]), FNO (HcInterruptStatus[5]), RD (HcInterruptStatus[3]), SF (HcInterruptStatus[2]), WDH (HcInterruptStatus[1]) or SO (HcInterruptStatus[0]) Enabled if the corresponding bit in HcInterruptEnable is high.
<br>
Read Operation:
<br>
0 = Interrupt generation due to RHSC (HcInterruptStatus[6]), FNO (HcInterruptStatus[5]), RD (HcInterruptStatus[3]), SF (HcInterruptStatus[2]), WDH (HcInterruptStatus[1]) or SO (HcInterruptStatus[0]) Disabled even if the corresponding bit in HcInterruptEnable is high.
<br>
1 = Interrupt generation due to RHSC (HcInterruptStatus[6]), FNO (HcInterruptStatus[5]), RD (HcInterruptStatus[3]), SF (HcInterruptStatus[2]), WDH (HcInterruptStatus[1]) or SO (HcInterruptStatus[0]) Enabled if the corresponding bit in HcInterruptEnable is high.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcInterruptDisable

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcInterruptDisable
</font><br><p> <font size="2">
Offset: 0x14  Host Controller Interrupt Disable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SO</td><td><div style="word-wrap: break-word;"><b>Scheduling Overrun Disable Bit
</b><br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Interrupt generation due to SO (HcInterruptStatus[0]) Disabled.
<br>
Read Operation:
<br>
0 = Interrupt generation due to SO (HcInterruptStatus[0]) Disabled.
<br>
1 = Interrupt generation due to SO (HcInterruptStatus[0]) Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>WDH</td><td><div style="word-wrap: break-word;"><b>Write Back Done Head Disable Bit
</b><br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Interrupt generation due to WDH (HcInterruptStatus[1]) Disabled.
<br>
Read Operation:
<br>
0 = Interrupt generation due to WDH (HcInterruptStatus[1]) Disabled.
<br>
1 = Interrupt generation due to WDH (HcInterruptStatus[1]) Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>SF</td><td><div style="word-wrap: break-word;"><b>Start of Frame Disable Bit
</b><br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Interrupt generation due to SF (HcInterruptStatus[2]) Disabled.
<br>
Read Operation:
<br>
0 = Interrupt generation due to SF (HcInterruptStatus[2]) Disabled.
<br>
1 = Interrupt generation due to SF (HcInterruptStatus[2]) Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>RD</td><td><div style="word-wrap: break-word;"><b>Resume Detected Disable Bit
</b><br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Interrupt generation due to RD (HcInterruptStatus[3]) Disabled.
<br>
Read Operation:
<br>
0 = Interrupt generation due to RD (HcInterruptStatus[3]) Disabled.
<br>
1 = Interrupt generation due to RD (HcInterruptStatus[3]) Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>FNO</td><td><div style="word-wrap: break-word;"><b>Frame Number Overflow Disable Bit
</b><br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Interrupt generation due to FNO (HcInterruptStatus[5]) Disabled.
<br>
Read Operation:
<br>
0 = Interrupt generation due to FNO (HcInterruptStatus[5]) Disabled.
<br>
1 = Interrupt generation due to FNO (HcInterruptStatus[5]) Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>RHSC</td><td><div style="word-wrap: break-word;"><b>Root Hub Status Change Disable Bit
</b><br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Interrupt generation due to RHSC (HcInterruptStatus[6]) Disabled.
<br>
Read Operation:
<br>
0 = Interrupt generation due to RHSC (HcInterruptStatus[6]) Disabled.
<br>
1 = Interrupt generation due to RHSC (HcInterruptStatus[6]) Enabled.
<br>
</div></td></tr><tr><td>
[31]</td><td>MIE</td><td><div style="word-wrap: break-word;"><b>Master Interrupt Disable Bit
</b><br>
Global interrupt disable. Writing '1' to disable all interrupts.
<br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Interrupt generation due to RHSC (HcInterruptStatus[6]), FNO (HcInterruptStatus[5]), RD (HcInterruptStatus[3]), SF (HcInterruptStatus[2]), WDH (HcInterruptStatus[1]) or SO (HcInterruptStatus[0]) Disabled if the corresponding bit in HcInterruptEnable is high.
<br>
Read Operation:
<br>
0 = Interrupt generation due to RHSC (HcInterruptStatus[6]), FNO (HcInterruptStatus[5]), RD (HcInterruptStatus[3]), SF (HcInterruptStatus[2]), WDH (HcInterruptStatus[1]) or SO (HcInterruptStatus[0]) Disabled even if the corresponding bit in HcInterruptEnable is high.
<br>
1 = Interrupt generation due to RHSC (HcInterruptStatus[6]), FNO (HcInterruptStatus[5]), RD (HcInterruptStatus[3]), SF (HcInterruptStatus[2]), WDH (HcInterruptStatus[1]) or SO (HcInterruptStatus[0]) Enabled if the corresponding bit in HcInterruptEnable is high.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcHCCA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcHCCA
</font><br><p> <font size="2">
Offset: 0x18  Host Controller Communication Area Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:8]</td><td>HCCA</td><td><div style="word-wrap: break-word;"><b>Host Controller Communication Area
</b><br>
Pointer to indicate base address of the Host Controller Communication Area (HCCA).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcPeriodCurrentED

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcPeriodCurrentED
</font><br><p> <font size="2">
Offset: 0x1C  Host Controller Period Current ED Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:4]</td><td>PCED</td><td><div style="word-wrap: break-word;"><b>Periodic Current ED
</b><br>
Pointer to indicate physical address of the current Isochronous or Interrupt Endpoint Descriptor.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcControlHeadED

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcControlHeadED
</font><br><p> <font size="2">
Offset: 0x20  Host Controller Control Head ED Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:4]</td><td>CHED</td><td><div style="word-wrap: break-word;"><b>Control Head ED
</b><br>
Pointer to indicate physical address of the first Endpoint Descriptor of the Control list.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcControlCurrentED

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcControlCurrentED
</font><br><p> <font size="2">
Offset: 0x24  Host Controller Control Current ED Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:4]</td><td>CCED</td><td><div style="word-wrap: break-word;"><b>Control Current Head ED
</b><br>
Pointer to indicate the physical address of the current Endpoint Descriptor of the Control list.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcBulkHeadED

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcBulkHeadED
</font><br><p> <font size="2">
Offset: 0x28  Host Controller Bulk Head ED Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:4]</td><td>BHED</td><td><div style="word-wrap: break-word;"><b>Bulk Head ED
</b><br>
Pointer to indicate the physical address of the first Endpoint Descriptor of the Bulk list.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcBulkCurrentED

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcBulkCurrentED
</font><br><p> <font size="2">
Offset: 0x2C  Host Controller Bulk Current ED Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:4]</td><td>BCED</td><td><div style="word-wrap: break-word;"><b>Bulk Current Head ED
</b><br>
Pointer to indicate the physical address of the current endpoint of the Bulk list.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcDoneHead

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcDoneHead
</font><br><p> <font size="2">
Offset: 0x30  Host Controller Done Head Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:4]</td><td>DH</td><td><div style="word-wrap: break-word;"><b>Done Head
</b><br>
Pointer to indicate the physical address of the last completed Transfer Descriptor that was added to the Done queue.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcFmInterval

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcFmInterval
</font><br><p> <font size="2">
Offset: 0x34  Host Controller Frame Interval Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[13:0]</td><td>FI</td><td><div style="word-wrap: break-word;"><b>Frame Interval
</b><br>
This field specifies the length of a frame as (bit times - 1)
<br>
For 12,000 bit times in a frame, a value of 11,999 is stored here.
<br>
</div></td></tr><tr><td>
[30:16]</td><td>FSMPS</td><td><div style="word-wrap: break-word;"><b>FS Largest Data Packet
</b><br>
This field specifies a value that is loaded into the Largest Data Packet Counter at the beginning of each frame.
<br>
</div></td></tr><tr><td>
[31]</td><td>FIT</td><td><div style="word-wrap: break-word;"><b>Frame Interval Toggle
</b><br>
This bit is toggled by Host Controller Driver when it loads a new value into FI (HcFmInterval[13:0]).
<br>
0 = Host Controller Driver didn't load new value into FI (HcFmInterval[13:0]).
<br>
1 = Host Controller Driver loads a new value into FI (HcFmInterval[13:0]).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcFmRemaining

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcFmRemaining
</font><br><p> <font size="2">
Offset: 0x38  Host Controller Frame Remaining Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[13:0]</td><td>FR</td><td><div style="word-wrap: break-word;"><b>Frame Remaining
</b><br>
When the Host Controller is in the USBOPERATIONAL state, this 14-bit field decrements each 12 MHz clock period
<br>
When the count reaches 0, (end of frame) the counter reloads with Frame Interval
<br>
In addition, the counter loads when the Host Controller transitions into USBOPERATIONAL.
<br>
</div></td></tr><tr><td>
[31]</td><td>FRT</td><td><div style="word-wrap: break-word;"><b>Frame Remaining Toggle
</b><br>
This bit is loaded from the FIT (HcFmInterval[31]) whenever FR (HcFmRemaining[13:0]) reaches 0.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcFmNumber

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcFmNumber
</font><br><p> <font size="2">
Offset: 0x3C  Host Controller Frame Number Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>FN</td><td><div style="word-wrap: break-word;"><b>Frame Number
</b><br>
This 16-bit incrementing counter field is incremented coincident with the re-load of FR (HcFmRemaining[13:0])
<br>
The count rolls over from 'FFFFh' to '0h.'
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcPeriodicStart

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcPeriodicStart
</font><br><p> <font size="2">
Offset: 0x40  Host Controller Periodic Start Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[13:0]</td><td>PS</td><td><div style="word-wrap: break-word;"><b>Periodic Start
</b><br>
This field contains a value used by the List Processor to determine where in a frame the Periodic List processing must begin.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcLSThreshold

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcLSThreshold
</font><br><p> <font size="2">
Offset: 0x44  Host Controller Low-speed Threshold Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[11:0]</td><td>LST</td><td><div style="word-wrap: break-word;"><b>Low-speed Threshold
</b><br>
This field contains a value which is compared to the FR (HcFmRemaining[13:0]) field prior to initiating a Low-speed transaction
<br>
The transaction is started only if FR (HcFmRemaining[13:0]) >= this field
<br>
The value is calculated by Host Controller Driver with the consideration of transmission and setup overhead.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcRhDescriptorA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcRhDescriptorA
</font><br><p> <font size="2">
Offset: 0x48  Host Controller Root Hub Descriptor A Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>NDP</td><td><div style="word-wrap: break-word;"><b>Number Downstream Ports
</b><br>
USB host control supports two downstream ports and only one port is available in this series of chip.
<br>
</div></td></tr><tr><td>
[8]</td><td>PSM</td><td><div style="word-wrap: break-word;"><b>Power Switching Mode
</b><br>
This bit is used to specify how the power switching of the Root Hub ports is controlled.
<br>
0 = Global Switching.
<br>
1 = Individual Switching.
<br>
</div></td></tr><tr><td>
[11]</td><td>OCPM</td><td><div style="word-wrap: break-word;"><b>over Current Protection Mode
</b><br>
This bit describes how the over current status for the Root Hub ports reported
<br>
This bit is only valid when NOCP (HcRhDescriptorA[12]) is cleared.
<br>
0 = Global Over current.
<br>
1 = Individual Over current.
<br>
</div></td></tr><tr><td>
[12]</td><td>NOCP</td><td><div style="word-wrap: break-word;"><b>No over Current Protection
</b><br>
This bit describes how the over current status for the Root Hub ports reported.
<br>
0 = Over current status is reported.
<br>
1 = Over current status is not reported.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcRhDescriptorB

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcRhDescriptorB
</font><br><p> <font size="2">
Offset: 0x4C  Host Controller Root Hub Descriptor B Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:16]</td><td>PPCM</td><td><div style="word-wrap: break-word;"><b>Port Power Control Mask
</b><br>
Global power switching
<br>
This field is only valid if PowerSwitchingMode is set (individual port switching)
<br>
When set, the port only responds to individual port power switching commands (Set/ClearPortPower)
<br>
When cleared, the port only responds to global power switching commands (Set/ClearGlobalPower).
<br>
0 = Port power controlled by global power switching.
<br>
1 = Port power controlled by port power switching.
<br>
Note: PPCM[15:2] and PPCM[0] are reserved.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcRhStatus

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcRhStatus
</font><br><p> <font size="2">
Offset: 0x50  Host Controller Root Hub Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>LPS</td><td><div style="word-wrap: break-word;"><b>Clear Global Power
</b><br>
In global power mode (PSM (HcRhDescriptorA[8]) = 0), this bit is written to one to clear all ports' power.
<br>
This bit always read as zero.
<br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Clear global power.
<br>
</div></td></tr><tr><td>
[1]</td><td>OCI</td><td><div style="word-wrap: break-word;"><b>over Current Indicator
</b><br>
This bit reflects the state of the over current status pin
<br>
This field is only valid if NOCP (HcRhDesA[12]) and OCPM (HcRhDesA[11]) are cleared.
<br>
0 = No over current condition.
<br>
1 = Over current condition.
<br>
</div></td></tr><tr><td>
[15]</td><td>DRWE</td><td><div style="word-wrap: break-word;"><b>Device Remote Wakeup Enable Bit
</b><br>
This bit controls if port's Connect Status Change as a remote wake-up event.
<br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Connect Status Change as a remote wake-up event Enabled.
<br>
Read Operation:
<br>
0 = Connect Status Change as a remote wake-up event Disabled.
<br>
1 = Connect Status Change as a remote wake-up event Enabled.
<br>
</div></td></tr><tr><td>
[16]</td><td>LPSC</td><td><div style="word-wrap: break-word;"><b>Set Global Power
</b><br>
In global power mode (PSM (HcRhDescriptorA[8]) = 0), this bit is written to one to enable power to all ports.
<br>
This bit always read as zero.
<br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Set global power.
<br>
</div></td></tr><tr><td>
[17]</td><td>OCIC</td><td><div style="word-wrap: break-word;"><b>over Current Indicator Change
</b><br>
This bit is set by hardware when a change has occurred in OCI (HcRhStatus[1]).
<br>
Write 1 to clear this bit to zero.
<br>
0 = OCI (HcRhStatus[1]) didn't change.
<br>
1 = OCI (HcRhStatus[1]) change.
<br>
</div></td></tr><tr><td>
[31]</td><td>CRWE</td><td><div style="word-wrap: break-word;"><b>Clear Remote Wake-up Enable Bit
</b><br>
This bit is use to clear DRWE (HcRhStatus[15]).
<br>
This bit always read as zero.
<br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Clear DRWE (HcRhStatus[15]).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcRhPortStatus[2]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcRhPortStatus[2]
</font><br><p> <font size="2">
Offset: 0x54  Host Controller Root Hub Port Status
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CCS</td><td><div style="word-wrap: break-word;"><b>CurrentConnectStatus (Read) or ClearPortEnable Bit (Write)
</b><br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Clear port enable.
<br>
Read Operation:
<br>
0 = No device connected.
<br>
1 = Device connected.
<br>
</div></td></tr><tr><td>
[1]</td><td>PES</td><td><div style="word-wrap: break-word;"><b>Port Enable Status
</b><br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Set port enable.
<br>
Read Operation:
<br>
0 = Port Disabled.
<br>
1 = Port Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>PSS</td><td><div style="word-wrap: break-word;"><b>Port Suspend Status
</b><br>
This bit indicates the port is suspended
<br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Set port suspend.
<br>
Read Operation:
<br>
0 = Port is not suspended.
<br>
1 = Port is selectively suspended.
<br>
</div></td></tr><tr><td>
[3]</td><td>POCI</td><td><div style="word-wrap: break-word;"><b>Port over Current Indicator (Read) or Clear Port Suspend (Write)
</b><br>
This bit reflects the state of the over current status pin dedicated to this port
<br>
This field is only valid if NOCP (HcRhDescriptorA[12]) is cleared and OCPM (HcRhDescriptorA[11]) is set.
<br>
This bit is also used to initiate the selective result sequence for the port.
<br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Clear port suspend.
<br>
Read Operation:
<br>
0 = No over current condition.
<br>
1 = Over current condition.
<br>
</div></td></tr><tr><td>
[4]</td><td>PRS</td><td><div style="word-wrap: break-word;"><b>Port Reset Status
</b><br>
This bit reflects the reset state of the port.
<br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Set port reset.
<br>
Read Operation
<br>
0 = Port reset signal is not active.
<br>
1 = Port reset signal is active.
<br>
</div></td></tr><tr><td>
[8]</td><td>PPS</td><td><div style="word-wrap: break-word;"><b>Port Power Status
</b><br>
This bit reflects the power state of the port regardless of the power switching mode.
<br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Port Power Enabled.
<br>
Read Operation:
<br>
0 = Port power is Disabled.
<br>
1 = Port power is Enabled.
<br>
</div></td></tr><tr><td>
[9]</td><td>LSDA</td><td><div style="word-wrap: break-word;"><b>Low Speed Device Attached (Read) or Clear Port Power (Write)
</b><br>
This bit defines the speed (and bud idle) of the attached device
<br>
It is only valid when CCS (HcRhPortStatus1[0]) is set.
<br>
This bit is also used to clear port power.
<br>
Write Operation:
<br>
0 = No effect.
<br>
1 = Clear PPS (HcRhPortStatus1[8]).
<br>
Read Operation:
<br>
0 = Full Speed device.
<br>
1 = Low-speed device.
<br>
</div></td></tr><tr><td>
[16]</td><td>CSC</td><td><div style="word-wrap: break-word;"><b>Connect Status Change
</b><br>
This bit indicates connect or disconnect event has been detected (CCS (HcRhPortStatus1[0]) changed).
<br>
Write 1 to clear this bit to zero.
<br>
0 = No connect/disconnect event (CCS (HcRhPortStatus1[0]) didn't change).
<br>
1 = Hardware detection of connect/disconnect event (CCS (HcRhPortStatus1[0]) changed).
<br>
</div></td></tr><tr><td>
[17]</td><td>PESC</td><td><div style="word-wrap: break-word;"><b>Port Enable Status Change
</b><br>
This bit indicates that the port has been disabled (PES (HcRhPortStatus1[1]) cleared) due to a hardware event.
<br>
Write 1 to clear this bit to zero.
<br>
0 = PES (HcRhPortStatus1[1]) didn't change.
<br>
1 = PES (HcRhPortStatus1[1]) changed.
<br>
</div></td></tr><tr><td>
[18]</td><td>PSSC</td><td><div style="word-wrap: break-word;"><b>Port Suspend Status Change
</b><br>
This bit indicates the completion of the selective resume sequence for the port.
<br>
Write 1 to clear this bit to zero.
<br>
0 = Port resume is not completed.
<br>
1 = Port resume completed.
<br>
</div></td></tr><tr><td>
[19]</td><td>OCIC</td><td><div style="word-wrap: break-word;"><b>Port over Current Indicator Change
</b><br>
This bit is set when POCI (HcRhPortStatus1[3]) changes.
<br>
Write 1 to clear this bit to zero.
<br>
0 = POCI (HcRhPortStatus1[3]) didn't change.
<br>
1 = POCI (HcRhPortStatus1[3]) changes.
<br>
</div></td></tr><tr><td>
[20]</td><td>PRSC</td><td><div style="word-wrap: break-word;"><b>Port Reset Status Change
</b><br>
This bit indicates that the port reset signal has completed.
<br>
Write 1 to clear this bit to zero.
<br>
0 = Port reset is not complete.
<br>
1 = Port reset is complete.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcPhyControl

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcPhyControl
</font><br><p> <font size="2">
Offset: 0x200  Host Controller PHY Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[27]</td><td>STBYEN</td><td><div style="word-wrap: break-word;"><b>USB Transceiver Standby Enable Bit
</b><br>
This bit controls if USB transceiver could enter the standby mode to reduce power consumption.
<br>
0 = The USB transceiver would never enter the standby mode.
<br>
1 = The USB transceiver will enter standby mode while port is in power off state (port power is inactive).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBH_T::HcMiscControl

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HcMiscControl
</font><br><p> <font size="2">
Offset: 0x204  Host Controller Miscellaneous Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1]</td><td>ABORT</td><td><div style="word-wrap: break-word;"><b>AHB Bus ERROR Response
</b><br>
This bit indicates there is an ERROR response received in AHB bus.
<br>
0 = No ERROR response received.
<br>
1 = ERROR response received.
<br>
</div></td></tr><tr><td>
[3]</td><td>OCAL</td><td><div style="word-wrap: break-word;"><b>over Current Active Low
</b><br>
This bit controls the polarity of over current flag from external power IC.
<br>
0 = Over current flag is high active.
<br>
1 = Over current flag is low active.
<br>
</div></td></tr><tr><td>
[16]</td><td>DPRT1</td><td><div style="word-wrap: break-word;"><b>Disable Port 1
</b><br>
This bit controls if the connection between USB host controller and transceiver of port 1 is disabled
<br>
If the connection is disabled, the USB host controller will not recognize any event of USB bus.
<br>
Set this bit high, the transceiver of port 1 will also be forced into the standby mode no matter what USB host controller operation is.
<br>
0 = The connection between USB host controller and transceiver of port 1 Enabled.
<br>
1 = The connection between USB host controller and transceiver of port 1 Disabled and the transceiver of port 1 will also be forced into the standby mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __I  uint32_t HcRevision;            /*!< [0x0000] Host Controller Revision Register                                */
    __IO uint32_t HcControl;             /*!< [0x0004] Host Controller Control Register                                 */
    __IO uint32_t HcCommandStatus;       /*!< [0x0008] Host Controller Command Status Register                          */
    __IO uint32_t HcInterruptStatus;     /*!< [0x000c] Host Controller Interrupt Status Register                        */
    __IO uint32_t HcInterruptEnable;     /*!< [0x0010] Host Controller Interrupt Enable Register                        */
    __IO uint32_t HcInterruptDisable;    /*!< [0x0014] Host Controller Interrupt Disable Register                       */
    __IO uint32_t HcHCCA;                /*!< [0x0018] Host Controller Communication Area Register                      */
    __IO uint32_t HcPeriodCurrentED;     /*!< [0x001c] Host Controller Period Current ED Register                       */
    __IO uint32_t HcControlHeadED;       /*!< [0x0020] Host Controller Control Head ED Register                         */
    __IO uint32_t HcControlCurrentED;    /*!< [0x0024] Host Controller Control Current ED Register                      */
    __IO uint32_t HcBulkHeadED;          /*!< [0x0028] Host Controller Bulk Head ED Register                            */
    __IO uint32_t HcBulkCurrentED;       /*!< [0x002c] Host Controller Bulk Current ED Register                         */
    __IO uint32_t HcDoneHead;            /*!< [0x0030] Host Controller Done Head Register                               */
    __IO uint32_t HcFmInterval;          /*!< [0x0034] Host Controller Frame Interval Register                          */
    __I  uint32_t HcFmRemaining;         /*!< [0x0038] Host Controller Frame Remaining Register                         */
    __I  uint32_t HcFmNumber;            /*!< [0x003c] Host Controller Frame Number Register                            */
    __IO uint32_t HcPeriodicStart;       /*!< [0x0040] Host Controller Periodic Start Register                          */
    __IO uint32_t HcLSThreshold;         /*!< [0x0044] Host Controller Low-speed Threshold Register                     */
    __IO uint32_t HcRhDescriptorA;       /*!< [0x0048] Host Controller Root Hub Descriptor A Register                   */
    __IO uint32_t HcRhDescriptorB;       /*!< [0x004c] Host Controller Root Hub Descriptor B Register                   */
    __IO uint32_t HcRhStatus;            /*!< [0x0050] Host Controller Root Hub Status Register                         */
    __IO uint32_t HcRhPortStatus[2];     /*!< [0x0054] Host Controller Root Hub Port Status [1]                         */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[105];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t HcPhyControl;          /*!< [0x0200] Host Controller PHY Control Register                             */
    __IO uint32_t HcMiscControl;         /*!< [0x0204] Host Controller Miscellaneous Control Register                   */

} USBH_T;

/**
    @addtogroup USBH_CONST USBH Bit Field Definition
    Constant Definitions for USBH Controller
@{ */

#define USBH_HcRevision_REV_Pos          (0)                                               /*!< USBH_T::HcRevision: REV Position       */
#define USBH_HcRevision_REV_Msk          (0xfful << USBH_HcRevision_REV_Pos)               /*!< USBH_T::HcRevision: REV Mask           */

#define USBH_HcControl_CBSR_Pos          (0)                                               /*!< USBH_T::HcControl: CBSR Position       */
#define USBH_HcControl_CBSR_Msk          (0x3ul << USBH_HcControl_CBSR_Pos)                /*!< USBH_T::HcControl: CBSR Mask           */

#define USBH_HcControl_PLE_Pos           (2)                                               /*!< USBH_T::HcControl: PLE Position        */
#define USBH_HcControl_PLE_Msk           (0x1ul << USBH_HcControl_PLE_Pos)                 /*!< USBH_T::HcControl: PLE Mask            */

#define USBH_HcControl_IE_Pos            (3)                                               /*!< USBH_T::HcControl: IE Position         */
#define USBH_HcControl_IE_Msk            (0x1ul << USBH_HcControl_IE_Pos)                  /*!< USBH_T::HcControl: IE Mask             */

#define USBH_HcControl_CLE_Pos           (4)                                               /*!< USBH_T::HcControl: CLE Position        */
#define USBH_HcControl_CLE_Msk           (0x1ul << USBH_HcControl_CLE_Pos)                 /*!< USBH_T::HcControl: CLE Mask            */

#define USBH_HcControl_BLE_Pos           (5)                                               /*!< USBH_T::HcControl: BLE Position        */
#define USBH_HcControl_BLE_Msk           (0x1ul << USBH_HcControl_BLE_Pos)                 /*!< USBH_T::HcControl: BLE Mask            */

#define USBH_HcControl_HCFS_Pos          (6)                                               /*!< USBH_T::HcControl: HCFS Position       */
#define USBH_HcControl_HCFS_Msk          (0x3ul << USBH_HcControl_HCFS_Pos)                /*!< USBH_T::HcControl: HCFS Mask           */

#define USBH_HcCommandStatus_HCR_Pos     (0)                                               /*!< USBH_T::HcCommandStatus: HCR Position  */
#define USBH_HcCommandStatus_HCR_Msk     (0x1ul << USBH_HcCommandStatus_HCR_Pos)           /*!< USBH_T::HcCommandStatus: HCR Mask      */

#define USBH_HcCommandStatus_CLF_Pos     (1)                                               /*!< USBH_T::HcCommandStatus: CLF Position  */
#define USBH_HcCommandStatus_CLF_Msk     (0x1ul << USBH_HcCommandStatus_CLF_Pos)           /*!< USBH_T::HcCommandStatus: CLF Mask      */

#define USBH_HcCommandStatus_BLF_Pos     (2)                                               /*!< USBH_T::HcCommandStatus: BLF Position  */
#define USBH_HcCommandStatus_BLF_Msk     (0x1ul << USBH_HcCommandStatus_BLF_Pos)           /*!< USBH_T::HcCommandStatus: BLF Mask      */

#define USBH_HcCommandStatus_SOC_Pos     (16)                                              /*!< USBH_T::HcCommandStatus: SOC Position  */
#define USBH_HcCommandStatus_SOC_Msk     (0x3ul << USBH_HcCommandStatus_SOC_Pos)           /*!< USBH_T::HcCommandStatus: SOC Mask      */

#define USBH_HcInterruptStatus_SO_Pos    (0)                                               /*!< USBH_T::HcInterruptStatus: SO Position */
#define USBH_HcInterruptStatus_SO_Msk    (0x1ul << USBH_HcInterruptStatus_SO_Pos)          /*!< USBH_T::HcInterruptStatus: SO Mask     */

#define USBH_HcInterruptStatus_WDH_Pos   (1)                                               /*!< USBH_T::HcInterruptStatus: WDH Position*/
#define USBH_HcInterruptStatus_WDH_Msk   (0x1ul << USBH_HcInterruptStatus_WDH_Pos)         /*!< USBH_T::HcInterruptStatus: WDH Mask    */

#define USBH_HcInterruptStatus_SF_Pos    (2)                                               /*!< USBH_T::HcInterruptStatus: SF Position */
#define USBH_HcInterruptStatus_SF_Msk    (0x1ul << USBH_HcInterruptStatus_SF_Pos)          /*!< USBH_T::HcInterruptStatus: SF Mask     */

#define USBH_HcInterruptStatus_RD_Pos    (3)                                               /*!< USBH_T::HcInterruptStatus: RD Position */
#define USBH_HcInterruptStatus_RD_Msk    (0x1ul << USBH_HcInterruptStatus_RD_Pos)          /*!< USBH_T::HcInterruptStatus: RD Mask     */

#define USBH_HcInterruptStatus_FNO_Pos   (5)                                               /*!< USBH_T::HcInterruptStatus: FNO Position*/
#define USBH_HcInterruptStatus_FNO_Msk   (0x1ul << USBH_HcInterruptStatus_FNO_Pos)         /*!< USBH_T::HcInterruptStatus: FNO Mask    */

#define USBH_HcInterruptStatus_RHSC_Pos  (6)                                               /*!< USBH_T::HcInterruptStatus: RHSC Position*/
#define USBH_HcInterruptStatus_RHSC_Msk  (0x1ul << USBH_HcInterruptStatus_RHSC_Pos)        /*!< USBH_T::HcInterruptStatus: RHSC Mask   */

#define USBH_HcInterruptEnable_SO_Pos    (0)                                               /*!< USBH_T::HcInterruptEnable: SO Position */
#define USBH_HcInterruptEnable_SO_Msk    (0x1ul << USBH_HcInterruptEnable_SO_Pos)          /*!< USBH_T::HcInterruptEnable: SO Mask     */

#define USBH_HcInterruptEnable_WDH_Pos   (1)                                               /*!< USBH_T::HcInterruptEnable: WDH Position*/
#define USBH_HcInterruptEnable_WDH_Msk   (0x1ul << USBH_HcInterruptEnable_WDH_Pos)         /*!< USBH_T::HcInterruptEnable: WDH Mask    */

#define USBH_HcInterruptEnable_SF_Pos    (2)                                               /*!< USBH_T::HcInterruptEnable: SF Position */
#define USBH_HcInterruptEnable_SF_Msk    (0x1ul << USBH_HcInterruptEnable_SF_Pos)          /*!< USBH_T::HcInterruptEnable: SF Mask     */

#define USBH_HcInterruptEnable_RD_Pos    (3)                                               /*!< USBH_T::HcInterruptEnable: RD Position */
#define USBH_HcInterruptEnable_RD_Msk    (0x1ul << USBH_HcInterruptEnable_RD_Pos)          /*!< USBH_T::HcInterruptEnable: RD Mask     */

#define USBH_HcInterruptEnable_FNO_Pos   (5)                                               /*!< USBH_T::HcInterruptEnable: FNO Position*/
#define USBH_HcInterruptEnable_FNO_Msk   (0x1ul << USBH_HcInterruptEnable_FNO_Pos)         /*!< USBH_T::HcInterruptEnable: FNO Mask    */

#define USBH_HcInterruptEnable_RHSC_Pos  (6)                                               /*!< USBH_T::HcInterruptEnable: RHSC Position*/
#define USBH_HcInterruptEnable_RHSC_Msk  (0x1ul << USBH_HcInterruptEnable_RHSC_Pos)        /*!< USBH_T::HcInterruptEnable: RHSC Mask   */

#define USBH_HcInterruptEnable_MIE_Pos   (31)                                              /*!< USBH_T::HcInterruptEnable: MIE Position*/
#define USBH_HcInterruptEnable_MIE_Msk   (0x1ul << USBH_HcInterruptEnable_MIE_Pos)         /*!< USBH_T::HcInterruptEnable: MIE Mask    */

#define USBH_HcInterruptDisable_SO_Pos   (0)                                               /*!< USBH_T::HcInterruptDisable: SO Position*/
#define USBH_HcInterruptDisable_SO_Msk   (0x1ul << USBH_HcInterruptDisable_SO_Pos)         /*!< USBH_T::HcInterruptDisable: SO Mask    */

#define USBH_HcInterruptDisable_WDH_Pos  (1)                                               /*!< USBH_T::HcInterruptDisable: WDH Position*/
#define USBH_HcInterruptDisable_WDH_Msk  (0x1ul << USBH_HcInterruptDisable_WDH_Pos)        /*!< USBH_T::HcInterruptDisable: WDH Mask   */

#define USBH_HcInterruptDisable_SF_Pos   (2)                                               /*!< USBH_T::HcInterruptDisable: SF Position*/
#define USBH_HcInterruptDisable_SF_Msk   (0x1ul << USBH_HcInterruptDisable_SF_Pos)         /*!< USBH_T::HcInterruptDisable: SF Mask    */

#define USBH_HcInterruptDisable_RD_Pos   (3)                                               /*!< USBH_T::HcInterruptDisable: RD Position*/
#define USBH_HcInterruptDisable_RD_Msk   (0x1ul << USBH_HcInterruptDisable_RD_Pos)         /*!< USBH_T::HcInterruptDisable: RD Mask    */

#define USBH_HcInterruptDisable_FNO_Pos  (5)                                               /*!< USBH_T::HcInterruptDisable: FNO Position*/
#define USBH_HcInterruptDisable_FNO_Msk  (0x1ul << USBH_HcInterruptDisable_FNO_Pos)        /*!< USBH_T::HcInterruptDisable: FNO Mask   */

#define USBH_HcInterruptDisable_RHSC_Pos (6)                                               /*!< USBH_T::HcInterruptDisable: RHSC Position*/
#define USBH_HcInterruptDisable_RHSC_Msk (0x1ul << USBH_HcInterruptDisable_RHSC_Pos)       /*!< USBH_T::HcInterruptDisable: RHSC Mask  */

#define USBH_HcInterruptDisable_MIE_Pos  (31)                                              /*!< USBH_T::HcInterruptDisable: MIE Position*/
#define USBH_HcInterruptDisable_MIE_Msk  (0x1ul << USBH_HcInterruptDisable_MIE_Pos)        /*!< USBH_T::HcInterruptDisable: MIE Mask   */

#define USBH_HcHCCA_HCCA_Pos             (8)                                               /*!< USBH_T::HcHCCA: HCCA Position          */
#define USBH_HcHCCA_HCCA_Msk             (0xfffffful << USBH_HcHCCA_HCCA_Pos)              /*!< USBH_T::HcHCCA: HCCA Mask              */

#define USBH_HcPeriodCurrentED_PCED_Pos  (4)                                               /*!< USBH_T::HcPeriodCurrentED: PCED Position*/
#define USBH_HcPeriodCurrentED_PCED_Msk  (0xffffffful << USBH_HcPeriodCurrentED_PCED_Pos)  /*!< USBH_T::HcPeriodCurrentED: PCED Mask   */

#define USBH_HcControlHeadED_CHED_Pos    (4)                                               /*!< USBH_T::HcControlHeadED: CHED Position */
#define USBH_HcControlHeadED_CHED_Msk    (0xffffffful << USBH_HcControlHeadED_CHED_Pos)    /*!< USBH_T::HcControlHeadED: CHED Mask     */

#define USBH_HcControlCurrentED_CCED_Pos (4)                                               /*!< USBH_T::HcControlCurrentED: CCED Position*/
#define USBH_HcControlCurrentED_CCED_Msk (0xffffffful << USBH_HcControlCurrentED_CCED_Pos) /*!< USBH_T::HcControlCurrentED: CCED Mask  */

#define USBH_HcBulkHeadED_BHED_Pos       (4)                                               /*!< USBH_T::HcBulkHeadED: BHED Position    */
#define USBH_HcBulkHeadED_BHED_Msk       (0xffffffful << USBH_HcBulkHeadED_BHED_Pos)       /*!< USBH_T::HcBulkHeadED: BHED Mask        */

#define USBH_HcBulkCurrentED_BCED_Pos    (4)                                               /*!< USBH_T::HcBulkCurrentED: BCED Position */
#define USBH_HcBulkCurrentED_BCED_Msk    (0xffffffful << USBH_HcBulkCurrentED_BCED_Pos)    /*!< USBH_T::HcBulkCurrentED: BCED Mask     */

#define USBH_HcDoneHead_DH_Pos           (4)                                               /*!< USBH_T::HcDoneHead: DH Position        */
#define USBH_HcDoneHead_DH_Msk           (0xffffffful << USBH_HcDoneHead_DH_Pos)           /*!< USBH_T::HcDoneHead: DH Mask            */

#define USBH_HcFmInterval_FI_Pos         (0)                                               /*!< USBH_T::HcFmInterval: FI Position      */
#define USBH_HcFmInterval_FI_Msk         (0x3ffful << USBH_HcFmInterval_FI_Pos)            /*!< USBH_T::HcFmInterval: FI Mask          */

#define USBH_HcFmInterval_FSMPS_Pos      (16)                                              /*!< USBH_T::HcFmInterval: FSMPS Position   */
#define USBH_HcFmInterval_FSMPS_Msk      (0x7ffful << USBH_HcFmInterval_FSMPS_Pos)         /*!< USBH_T::HcFmInterval: FSMPS Mask       */

#define USBH_HcFmInterval_FIT_Pos        (31)                                              /*!< USBH_T::HcFmInterval: FIT Position     */
#define USBH_HcFmInterval_FIT_Msk        (0x1ul << USBH_HcFmInterval_FIT_Pos)              /*!< USBH_T::HcFmInterval: FIT Mask         */

#define USBH_HcFmRemaining_FR_Pos        (0)                                               /*!< USBH_T::HcFmRemaining: FR Position     */
#define USBH_HcFmRemaining_FR_Msk        (0x3ffful << USBH_HcFmRemaining_FR_Pos)           /*!< USBH_T::HcFmRemaining: FR Mask         */

#define USBH_HcFmRemaining_FRT_Pos       (31)                                              /*!< USBH_T::HcFmRemaining: FRT Position    */
#define USBH_HcFmRemaining_FRT_Msk       (0x1ul << USBH_HcFmRemaining_FRT_Pos)             /*!< USBH_T::HcFmRemaining: FRT Mask        */

#define USBH_HcFmNumber_FN_Pos           (0)                                               /*!< USBH_T::HcFmNumber: FN Position        */
#define USBH_HcFmNumber_FN_Msk           (0xfffful << USBH_HcFmNumber_FN_Pos)              /*!< USBH_T::HcFmNumber: FN Mask            */

#define USBH_HcPeriodicStart_PS_Pos      (0)                                               /*!< USBH_T::HcPeriodicStart: PS Position   */
#define USBH_HcPeriodicStart_PS_Msk      (0x3ffful << USBH_HcPeriodicStart_PS_Pos)         /*!< USBH_T::HcPeriodicStart: PS Mask       */

#define USBH_HcLSThreshold_LST_Pos       (0)                                               /*!< USBH_T::HcLSThreshold: LST Position    */
#define USBH_HcLSThreshold_LST_Msk       (0xffful << USBH_HcLSThreshold_LST_Pos)           /*!< USBH_T::HcLSThreshold: LST Mask        */

#define USBH_HcRhDescriptorA_NDP_Pos     (0)                                               /*!< USBH_T::HcRhDescriptorA: NDP Position  */
#define USBH_HcRhDescriptorA_NDP_Msk     (0xfful << USBH_HcRhDescriptorA_NDP_Pos)          /*!< USBH_T::HcRhDescriptorA: NDP Mask      */

#define USBH_HcRhDescriptorA_PSM_Pos     (8)                                               /*!< USBH_T::HcRhDescriptorA: PSM Position  */
#define USBH_HcRhDescriptorA_PSM_Msk     (0x1ul << USBH_HcRhDescriptorA_PSM_Pos)           /*!< USBH_T::HcRhDescriptorA: PSM Mask      */

#define USBH_HcRhDescriptorA_OCPM_Pos    (11)                                              /*!< USBH_T::HcRhDescriptorA: OCPM Position */
#define USBH_HcRhDescriptorA_OCPM_Msk    (0x1ul << USBH_HcRhDescriptorA_OCPM_Pos)          /*!< USBH_T::HcRhDescriptorA: OCPM Mask     */

#define USBH_HcRhDescriptorA_NOCP_Pos    (12)                                              /*!< USBH_T::HcRhDescriptorA: NOCP Position */
#define USBH_HcRhDescriptorA_NOCP_Msk    (0x1ul << USBH_HcRhDescriptorA_NOCP_Pos)          /*!< USBH_T::HcRhDescriptorA: NOCP Mask     */

#define USBH_HcRhDescriptorB_PPCM_Pos    (16)                                              /*!< USBH_T::HcRhDescriptorB: PPCM Position */
#define USBH_HcRhDescriptorB_PPCM_Msk    (0xfffful << USBH_HcRhDescriptorB_PPCM_Pos)       /*!< USBH_T::HcRhDescriptorB: PPCM Mask     */

#define USBH_HcRhStatus_LPS_Pos          (0)                                               /*!< USBH_T::HcRhStatus: LPS Position       */
#define USBH_HcRhStatus_LPS_Msk          (0x1ul << USBH_HcRhStatus_LPS_Pos)                /*!< USBH_T::HcRhStatus: LPS Mask           */

#define USBH_HcRhStatus_OCI_Pos          (1)                                               /*!< USBH_T::HcRhStatus: OCI Position       */
#define USBH_HcRhStatus_OCI_Msk          (0x1ul << USBH_HcRhStatus_OCI_Pos)                /*!< USBH_T::HcRhStatus: OCI Mask           */

#define USBH_HcRhStatus_DRWE_Pos         (15)                                              /*!< USBH_T::HcRhStatus: DRWE Position      */
#define USBH_HcRhStatus_DRWE_Msk         (0x1ul << USBH_HcRhStatus_DRWE_Pos)               /*!< USBH_T::HcRhStatus: DRWE Mask          */

#define USBH_HcRhStatus_LPSC_Pos         (16)                                              /*!< USBH_T::HcRhStatus: LPSC Position      */
#define USBH_HcRhStatus_LPSC_Msk         (0x1ul << USBH_HcRhStatus_LPSC_Pos)               /*!< USBH_T::HcRhStatus: LPSC Mask          */

#define USBH_HcRhStatus_OCIC_Pos         (17)                                              /*!< USBH_T::HcRhStatus: OCIC Position      */
#define USBH_HcRhStatus_OCIC_Msk         (0x1ul << USBH_HcRhStatus_OCIC_Pos)               /*!< USBH_T::HcRhStatus: OCIC Mask          */

#define USBH_HcRhStatus_CRWE_Pos         (31)                                              /*!< USBH_T::HcRhStatus: CRWE Position      */
#define USBH_HcRhStatus_CRWE_Msk         (0x1ul << USBH_HcRhStatus_CRWE_Pos)               /*!< USBH_T::HcRhStatus: CRWE Mask          */

#define USBH_HcRhPortStatus_CCS_Pos      (0)                                               /*!< USBH_T::HcRhPortStatus1: CCS Position  */
#define USBH_HcRhPortStatus_CCS_Msk      (0x1ul << USBH_HcRhPortStatus_CCS_Pos)            /*!< USBH_T::HcRhPortStatus1: CCS Mask      */

#define USBH_HcRhPortStatus_PES_Pos      (1)                                               /*!< USBH_T::HcRhPortStatus1: PES Position  */
#define USBH_HcRhPortStatus_PES_Msk      (0x1ul << USBH_HcRhPortStatus_PES_Pos)            /*!< USBH_T::HcRhPortStatus1: PES Mask      */

#define USBH_HcRhPortStatus_PSS_Pos      (2)                                               /*!< USBH_T::HcRhPortStatus1: PSS Position  */
#define USBH_HcRhPortStatus_PSS_Msk      (0x1ul << USBH_HcRhPortStatus_PSS_Pos)            /*!< USBH_T::HcRhPortStatus1: PSS Mask      */

#define USBH_HcRhPortStatus_POCI_Pos     (3)                                               /*!< USBH_T::HcRhPortStatus1: POCI Position */
#define USBH_HcRhPortStatus_POCI_Msk     (0x1ul << USBH_HcRhPortStatus_POCI_Pos)           /*!< USBH_T::HcRhPortStatus1: POCI Mask     */

#define USBH_HcRhPortStatus_PRS_Pos      (4)                                               /*!< USBH_T::HcRhPortStatus1: PRS Position  */
#define USBH_HcRhPortStatus_PRS_Msk      (0x1ul << USBH_HcRhPortStatus_PRS_Pos)            /*!< USBH_T::HcRhPortStatus1: PRS Mask      */

#define USBH_HcRhPortStatus_PPS_Pos      (8)                                               /*!< USBH_T::HcRhPortStatus1: PPS Position  */
#define USBH_HcRhPortStatus_PPS_Msk      (0x1ul << USBH_HcRhPortStatus_PPS_Pos)            /*!< USBH_T::HcRhPortStatus1: PPS Mask      */

#define USBH_HcRhPortStatus_LSDA_Pos     (9)                                               /*!< USBH_T::HcRhPortStatus1: LSDA Position */
#define USBH_HcRhPortStatus_LSDA_Msk     (0x1ul << USBH_HcRhPortStatus_LSDA_Pos)           /*!< USBH_T::HcRhPortStatus1: LSDA Mask     */

#define USBH_HcRhPortStatus_CSC_Pos      (16)                                              /*!< USBH_T::HcRhPortStatus1: CSC Position  */
#define USBH_HcRhPortStatus_CSC_Msk      (0x1ul << USBH_HcRhPortStatus_CSC_Pos)            /*!< USBH_T::HcRhPortStatus1: CSC Mask      */

#define USBH_HcRhPortStatus_PESC_Pos     (17)                                              /*!< USBH_T::HcRhPortStatus1: PESC Position */
#define USBH_HcRhPortStatus_PESC_Msk     (0x1ul << USBH_HcRhPortStatus_PESC_Pos)           /*!< USBH_T::HcRhPortStatus1: PESC Mask     */

#define USBH_HcRhPortStatus_PSSC_Pos     (18)                                              /*!< USBH_T::HcRhPortStatus1: PSSC Position */
#define USBH_HcRhPortStatus_PSSC_Msk     (0x1ul << USBH_HcRhPortStatus_PSSC_Pos)           /*!< USBH_T::HcRhPortStatus1: PSSC Mask     */

#define USBH_HcRhPortStatus_OCIC_Pos     (19)                                              /*!< USBH_T::HcRhPortStatus1: OCIC Position */
#define USBH_HcRhPortStatus_OCIC_Msk     (0x1ul << USBH_HcRhPortStatus_OCIC_Pos)           /*!< USBH_T::HcRhPortStatus1: OCIC Mask     */

#define USBH_HcRhPortStatus_PRSC_Pos     (20)                                              /*!< USBH_T::HcRhPortStatus1: PRSC Position */
#define USBH_HcRhPortStatus_PRSC_Msk     (0x1ul << USBH_HcRhPortStatus_PRSC_Pos)           /*!< USBH_T::HcRhPortStatus1: PRSC Mask     */

#define USBH_HcPhyControl_STBYEN_Pos     (27)                                              /*!< USBH_T::HcPhyControl: STBYEN Position  */
#define USBH_HcPhyControl_STBYEN_Msk     (0x1ul << USBH_HcPhyControl_STBYEN_Pos)           /*!< USBH_T::HcPhyControl: STBYEN Mask      */

#define USBH_HcMiscControl_ABORT_Pos     (1)                                               /*!< USBH_T::HcMiscControl: ABORT Position  */
#define USBH_HcMiscControl_ABORT_Msk     (0x1ul << USBH_HcMiscControl_ABORT_Pos)           /*!< USBH_T::HcMiscControl: ABORT Mask      */

#define USBH_HcMiscControl_OCAL_Pos      (3)                                               /*!< USBH_T::HcMiscControl: OCAL Position   */
#define USBH_HcMiscControl_OCAL_Msk      (0x1ul << USBH_HcMiscControl_OCAL_Pos)            /*!< USBH_T::HcMiscControl: OCAL Mask       */

#define USBH_HcMiscControl_DPRT1_Pos     (16)                                              /*!< USBH_T::HcMiscControl: DPRT1 Position  */
#define USBH_HcMiscControl_DPRT1_Msk     (0x1ul << USBH_HcMiscControl_DPRT1_Pos)           /*!< USBH_T::HcMiscControl: DPRT1 Mask      */

/**@}*/ /* USBH_CONST */
/**@}*/ /* end of USBH register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __USBH_REG_H__ */
