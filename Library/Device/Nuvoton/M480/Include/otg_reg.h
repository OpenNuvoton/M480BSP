/**************************************************************************//**
 * @file     otg_reg.h
 * @version  V1.00
 * @brief    OTG register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __OTG_REG_H__
#define __OTG_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup OTG USB On-The-Go Controller(OTG)
    Memory Mapped Structure for OTG Controller
@{ */

typedef struct
{


    /**
@var OTG_T::CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL
</font><br><p> <font size="2">
Offset: 0x00  OTG Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>VBUSDROP</td><td><div style="word-wrap: break-word;"><b>Drop VBUS Control
</b><br>
If user application running on this OTG A-device wants to conserve power, set this bit to drop VBUS
<br>
BUSREQ (OTG_CTL[1]) will be also cleared no matter A-device or B-device.
<br>
0 = Not drop the VBUS.
<br>
1 = Drop the VBUS.
<br>
</div></td></tr><tr><td>
[1]</td><td>BUSREQ</td><td><div style="word-wrap: break-word;"><b>OTG Bus Request
</b><br>
If OTG A-device wants to do data transfers via USB bus, setting this bit will drive VBUS high to detect USB device connection
<br>
If user won't use the bus any more, clearing this bit will drop VBUS to save power
<br>
This bit will be cleared when A-device goes to A_wait_vfall state
<br>
This bit will be also cleared if VBUSDROP (OTG_CTL[0]) bit is set or IDSTS (OTG_STATUS[1]) changed.
<br>
If user of an OTG-B Device wants to request VBUS, setting this bit will run SRP protocol
<br>
This bit will be cleared if SRP failure (OTG A-device does not provide VBUS after B-device issues ARP in specified interval, defined in OTG specification)
<br>
This bit will be also cleared if VBUSDROP (OTG_CTL[0]) bit is set IDSTS (OTG_STATUS[1]) changed.
<br>
0 = Not launch VBUS in OTG A-device or not request SRP in OTG B-device.
<br>
1 = Launch VBUS in OTG A-device or request SRP in OTG B-device.
<br>
</div></td></tr><tr><td>
[2]</td><td>HNPREQEN</td><td><div style="word-wrap: break-word;"><b>OTG HNP Request Enable Bit
</b><br>
When USB frame as A-device, set this bit when A-device allows to process HNP protocol -- A-device changes role from Host to Peripheral
<br>
This bit will be cleared when OTG state changes from a_suspend to a_peripheral or goes back to a_idle state
<br>
When USB frame as B-device, set this bit after the OTG A-device successfully sends a SetFeature (b_hnp_enable) command to the OTG B-device to start role change -- B-device changes role from Peripheral to Host
<br>
This bit will be cleared when OTG state changes from b_peripheral to b_wait_acon or goes back to b_idle state.
<br>
0 = HNP request Disabled.
<br>
1 = HNP request Enabled (A-device can change role from Host to Peripheral or B-device can change role from Peripheral to Host).
<br>
Note: Refer to OTG specification to get a_suspend, a_peripheral, a_idle and b_idle state.
<br>
</div></td></tr><tr><td>
[4]</td><td>OTGEN</td><td><div style="word-wrap: break-word;"><b>OTG Function Enable Bit
</b><br>
User needs to set this bit to enable OTG function while USB frame configured as OTG device
<br>
When USB frame not configured as OTG device, this bit is must be low.
<br>
0= OTG function Disabled.
<br>
1 = OTG function Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>WKEN</td><td><div style="word-wrap: break-word;"><b>OTG ID Pin Wake-up Enable Bit
</b><br>
0 = OTG ID pin status change wake-up function Disabled.
<br>
1 = OTG ID pin status change wake-up function Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var OTG_T::PHYCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PHYCTL
</font><br><p> <font size="2">
Offset: 0x04  OTG PHY Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>OTGPHYEN</td><td><div style="word-wrap: break-word;"><b>OTG PHY Enable
</b><br>
When USB frame is configured as OTG-device or ID-dependent, user needs to set this bit before using OTG function
<br>
If device is not configured as OTG-device nor ID-dependent , this bit is "don't care".
<br>
0 = OTG PHY Disabled.
<br>
1 = OTG PHY Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>IDDETEN</td><td><div style="word-wrap: break-word;"><b>ID Detection Enable Bit
</b><br>
0 = Detect ID pin status Disabled.
<br>
1 = Detect ID pin status Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>VBENPOL</td><td><div style="word-wrap: break-word;"><b>Off-chip USB VBUS Power Switch Enable Polarity
</b><br>
The OTG controller will enable off-chip USB VBUS power switch to provide VBUS power when need
<br>
A USB_VBUS_EN pin is used to control the off-chip USB VBUS power switch.
<br>
The polarity of enabling off-chip USB VBUS power switch (high active or low active) depends on the selected component
<br>
Set this bit as following according to the polarity of off-chip USB VBUS power switch.
<br>
0 = The off-chip USB VBUS power switch enable is active high.
<br>
1 = The off-chip USB VBUS power switch enable is active low.
<br>
</div></td></tr><tr><td>
[5]</td><td>VBSTSPOL</td><td><div style="word-wrap: break-word;"><b>Off-chip USB VBUS Power Switch Status Polarity
</b><br>
The polarity of off-chip USB VBUS power switch valid signal depends on the selected component
<br>
A USB_VBUS_ST pin is used to monitor the valid signal of the off-chip USB VBUS power switch
<br>
Set this bit as following according to the polarity of off-chip USB VBUS power switch.
<br>
0 = The polarity of off-chip USB VBUS power switch valid status is high.
<br>
1 = The polarity of off-chip USB VBUS power switch valid status is low.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var OTG_T::INTEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTEN
</font><br><p> <font size="2">
Offset: 0x08  OTG Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ROLECHGIEN</td><td><div style="word-wrap: break-word;"><b>Role (Host or Peripheral) Changed Interrupt Enable Bit
</b><br>
0 = Interrupt Disabled.
<br>
1 = Interrupt Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>VBEIEN</td><td><div style="word-wrap: break-word;"><b>VBUS Error Interrupt Enable Bit
</b><br>
0 = Interrupt Disabled.
<br>
1 = Interrupt Enabled.
<br>
Note: VBUS error means going to a_vbus_err state. Please refer to A-device state diagram in OTG spec.
<br>
</div></td></tr><tr><td>
[2]</td><td>SRPFIEN</td><td><div style="word-wrap: break-word;"><b>SRP Fail Interrupt Enable Bit
</b><br>
0 = Interrupt Disabled.
<br>
1 = Interrupt Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>HNPFIEN</td><td><div style="word-wrap: break-word;"><b>HNP Fail Interrupt Enable Bit
</b><br>
0 = Interrupt Disabled.
<br>
1 = Interrupt Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>GOIDLEIEN</td><td><div style="word-wrap: break-word;"><b>OTG Device Goes to IDLE State Interrupt Enable Bit
</b><br>
0 = Interrupt Disabled.
<br>
1 = Interrupt Enabled.
<br>
Note: Going to idle state means going to a_idle or b_idle state
<br>
Please refer to A-device state diagram and B-device state diagram in OTG spec.
<br>
</div></td></tr><tr><td>
[5]</td><td>IDCHGIEN</td><td><div style="word-wrap: break-word;"><b>IDSTS Changed Interrupt Enable Bit
</b><br>
If this bit is set to 1 and IDSTS (OTG_STATUS[1]) status is changed from high to low or from low to high, a interrupt will be asserted.
<br>
0 = Interrupt Disabled.
<br>
1 = Interrupt Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>PDEVIEN</td><td><div style="word-wrap: break-word;"><b>Act As Peripheral Interrupt Enable Bit
</b><br>
If this bit is set to 1 and the device is changed as a peripheral, a interrupt will be asserted.
<br>
0 = This device as a peripheral interrupt Disabled.
<br>
1 = This device as a peripheral interrupt Enabled.
<br>
</div></td></tr><tr><td>
[7]</td><td>HOSTIEN</td><td><div style="word-wrap: break-word;"><b>Act As Host Interrupt Enable Bit
</b><br>
If this bit is set to 1 and the device is changed as a host, a interrupt will be asserted.
<br>
0 = This device as a host interrupt Disabled.
<br>
1 = This device as a host interrupt Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>BVLDCHGIEN</td><td><div style="word-wrap: break-word;"><b>B-device Session Valid Status Changed Interrupt Enable Bit
</b><br>
If this bit is set to 1 and BVLD (OTG_STATUS[3]) status is changed from high to low or from low to high, a interrupt will be asserted.
<br>
0 = Interrupt Disabled.
<br>
1 = Interrupt Enabled.
<br>
</div></td></tr><tr><td>
[9]</td><td>AVLDCHGIEN</td><td><div style="word-wrap: break-word;"><b>A-device Session Valid Status Changed Interrupt Enable Bit
</b><br>
If this bit is set to 1 and AVLD (OTG_STATUS[4]) status is changed from high to low or from low to high, a interrupt will be asserted.
<br>
0 = Interrupt Disabled.
<br>
1 = Interrupt Enabled.
<br>
</div></td></tr><tr><td>
[10]</td><td>VBCHGIEN</td><td><div style="word-wrap: break-word;"><b>VBUSVLD Status Changed Interrupt Enable Bit
</b><br>
If this bit is set to 1 and VBUSVLD (OTG_STATUS[5]) status is changed from high to low or from low to high, a interrupt will be asserted.
<br>
0 = Interrupt Disabled.
<br>
1 = Interrupt Enabled.
<br>
</div></td></tr><tr><td>
[11]</td><td>SECHGIEN</td><td><div style="word-wrap: break-word;"><b>SESSEND Status Changed Interrupt Enable Bit
</b><br>
If this bit is set to 1 and SESSEND (OTG_STATUS[2]) status is changed from high to low or from low to high, a interrupt will be asserted.
<br>
0 = Interrupt Disabled.
<br>
1 = Interrupt Enabled.
<br>
</div></td></tr><tr><td>
[13]</td><td>SRPDETIEN</td><td><div style="word-wrap: break-word;"><b>SRP Detected Interrupt Enable Bit
</b><br>
0 = Interrupt Disabled.
<br>
1 = Interrupt Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var OTG_T::INTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTSTS
</font><br><p> <font size="2">
Offset: 0x0C  OTG Interrupt Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ROLECHGIF</td><td><div style="word-wrap: break-word;"><b>OTG Role Change Interrupt Status
</b><br>
This flag is set when the role of an OTG device changed from a host to a peripheral, or changed from a peripheral to a host while USB_ID pin status does not change.
<br>
0 = OTG device role not changed.
<br>
1 = OTG device role changed.
<br>
Note: Write 1 to clear this flag.
<br>
</div></td></tr><tr><td>
[1]</td><td>VBEIF</td><td><div style="word-wrap: break-word;"><b>VBUS Error Interrupt Status
</b><br>
This bit will be set when voltage on VBUS cannot reach a minimum valid threshold 4.4V within a maximum time of 100ms after OTG A-device starting to drive VBUS high.
<br>
0 = OTG A-device drives VBUS over threshold voltage before this interval expires.
<br>
1 = OTG A-device cannot drive VBUS over threshold voltage before this interval expires.
<br>
Note: Write 1 to clear this flag and recover from the VBUS error state.
<br>
</div></td></tr><tr><td>
[2]</td><td>SRPFIF</td><td><div style="word-wrap: break-word;"><b>SRP Fail Interrupt Status
</b><br>
After initiating SRP, an OTG B-device will wait for the OTG A-device to drive VBUS high at least TB_SRP_FAIL minimum, defined in OTG specification
<br>
This flag is set when the OTG B-device does not get VBUS high after this interval.
<br>
0 = OTG B-device gets VBUS high before this interval.
<br>
1 = OTG B-device does not get VBUS high before this interval.
<br>
Note: Write 1 to clear this flag.
<br>
</div></td></tr><tr><td>
[3]</td><td>HNPFIF</td><td><div style="word-wrap: break-word;"><b>HNP Fail Interrupt Status
</b><br>
When A-device has granted B-device to be host and USB bus is in SE0 (both USB_D+ and USB_D- low) state, this bit will be set when A-device does not connect after specified interval expires.
<br>
0 = A-device connects to B-device before specified interval expires.
<br>
1 = A-device does not connect to B-device before specified interval expires.
<br>
Note: Write 1 to clear this flag.
<br>
</div></td></tr><tr><td>
[4]</td><td>GOIDLEIF</td><td><div style="word-wrap: break-word;"><b>OTG Device Goes to IDLE Interrupt Status
</b><br>
Flag is set if the OTG device transfers from non-idle state to idle state
<br>
The OTG device will be neither a host nor a peripheral.
<br>
0 = OTG device does not go back to idle state (a_idle or b_idle).
<br>
1 = OTG device goes back to idle state(a_idle or b_idle).
<br>
Note 1: Going to idle state means going to a_idle or b_idle state. Please refer to OTG specification.
<br>
Note 2: Write 1 to clear this flag.
<br>
</div></td></tr><tr><td>
[5]</td><td>IDCHGIF</td><td><div style="word-wrap: break-word;"><b>ID State Change Interrupt Status
</b><br>
0 = IDSTS (OTG_STATUS[1]) not toggled.
<br>
1 = IDSTS (OTG_STATUS[1]) from high to low or from low to high.
<br>
Note: Write 1 to clear this flag.
<br>
</div></td></tr><tr><td>
[6]</td><td>PDEVIF</td><td><div style="word-wrap: break-word;"><b>Act As Peripheral Interrupt Status
</b><br>
0= This device does not act as a peripheral.
<br>
1 = This device acts as a peripheral.
<br>
Note: Write 1 to clear this flag.
<br>
</div></td></tr><tr><td>
[7]</td><td>HOSTIF</td><td><div style="word-wrap: break-word;"><b>Act As Host Interrupt Status
</b><br>
0= This device does not act as a host.
<br>
1 = This device acts as a host.
<br>
Note: Write 1 to clear this flag.
<br>
</div></td></tr><tr><td>
[8]</td><td>BVLDCHGIF</td><td><div style="word-wrap: break-word;"><b>B-device Session Valid State Change Interrupt Status
</b><br>
0 = BVLD (OTG_STATUS[3]) is not toggled.
<br>
1 = BVLD (OTG_STATUS[3]) from high to low or low to high.
<br>
Note: Write 1 to clear this status.
<br>
</div></td></tr><tr><td>
[9]</td><td>AVLDCHGIF</td><td><div style="word-wrap: break-word;"><b>A-device Session Valid State Change Interrupt Status
</b><br>
0 = AVLD (OTG_STATUS[4]) not toggled.
<br>
1 = AVLD (OTG_STATUS[4]) from high to low or low to high.
<br>
Note: Write 1 to clear this status.
<br>
</div></td></tr><tr><td>
[10]</td><td>VBCHGIF</td><td><div style="word-wrap: break-word;"><b>VBUSVLD State Change Interrupt Status
</b><br>
0 = VBUSVLD (OTG_STATUS[5]) not toggled.
<br>
1 = VBUSVLD (OTG_STATUS[5]) from high to low or from low to high.
<br>
Note: Write 1 to clear this status.
<br>
</div></td></tr><tr><td>
[11]</td><td>SECHGIF</td><td><div style="word-wrap: break-word;"><b>SESSEND State Change Interrupt Status
</b><br>
0 = SESSEND (OTG_STATUS[2]) not toggled.
<br>
1 = SESSEND (OTG_STATUS[2]) from high to low or from low to high.
<br>
Note: Write 1 to clear this flag.
<br>
</div></td></tr><tr><td>
[13]</td><td>SRPDETIF</td><td><div style="word-wrap: break-word;"><b>SRP Detected Interrupt Status
</b><br>
0 = SRP not detected.
<br>
1 = SRP detected.
<br>
Note: Write 1 to clear this status.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var OTG_T::STATUS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STATUS
</font><br><p> <font size="2">
Offset: 0x10  OTG Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>OVERCUR</td><td><div style="word-wrap: break-word;"><b>over Current Condition
</b><br>
The voltage on VBUS cannot reach a minimum VBUS valid threshold, 4.4V minimum, within a maximum time of 100ms after OTG A-device drives VBUS high.
<br>
0 = OTG A-device drives VBUS successfully.
<br>
1 = OTG A-device cannot drives VBUS high in this interval.
<br>
</div></td></tr><tr><td>
[1]</td><td>IDSTS</td><td><div style="word-wrap: break-word;"><b>USB_ID Pin State of Mini-b/Micro-plug
</b><br>
0 = Mini-A/Micro-A plug is attached.
<br>
1 = Mini-B/Micro-B plug is attached.
<br>
</div></td></tr><tr><td>
[2]</td><td>SESSEND</td><td><div style="word-wrap: break-word;"><b>Session End Status
</b><br>
When VBUS voltage is lower than 0.4V, this bit will be set to 1
<br>
Session end means no meaningful power on VBUS.
<br>
0 = Session is not end.
<br>
1 = Session is end.
<br>
</div></td></tr><tr><td>
[3]</td><td>BVLD</td><td><div style="word-wrap: break-word;"><b>B-device Session Valid Status
</b><br>
0 = B-device session is not valid.
<br>
1 = B-device session is valid.
<br>
</div></td></tr><tr><td>
[4]</td><td>AVLD</td><td><div style="word-wrap: break-word;"><b>A-device Session Valid Status
</b><br>
0 = A-device session is not valid.
<br>
1 = A-device session is valid.
<br>
</div></td></tr><tr><td>
[5]</td><td>VBUSVLD</td><td><div style="word-wrap: break-word;"><b>VBUS Valid Status
</b><br>
When VBUS is larger than 4.7V, this bit will be set to 1.
<br>
0 = VBUS is not valid.
<br>
1 = VBUS is valid.
<br>
</div></td></tr><tr><td>
[6]</td><td>ASPERI</td><td><div style="word-wrap: break-word;"><b>As Peripheral Status
</b><br>
When OTG as peripheral, this bit is set.
<br>
0: OTG not as peripheral
<br>
1: OTG as peripheral
<br>
</div></td></tr><tr><td>
[7]</td><td>ASHOST</td><td><div style="word-wrap: break-word;"><b>As Host Status
</b><br>
When OTG as Host, this bit is set.
<br>
0: OTG not as Host
<br>
1: OTG as Host
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CTL;                   /*!< [0x0000] OTG Control Register                                             */
    __IO uint32_t PHYCTL;                /*!< [0x0004] OTG PHY Control Register                                         */
    __IO uint32_t INTEN;                 /*!< [0x0008] OTG Interrupt Enable Register                                    */
    __IO uint32_t INTSTS;                /*!< [0x000c] OTG Interrupt Status Register                                    */
    __I  uint32_t STATUS;                /*!< [0x0010] OTG Status Register                                              */

} OTG_T;


/**
    @addtogroup OTG_CONST OTG Bit Field Definition
    Constant Definitions for OTG Controller
@{ */

#define OTG_CTL_VBUSDROP_Pos             (0)                                               /*!< OTG_T::CTL: VBUSDROP Position          */
#define OTG_CTL_VBUSDROP_Msk             (0x1ul << OTG_CTL_VBUSDROP_Pos)                   /*!< OTG_T::CTL: VBUSDROP Mask              */

#define OTG_CTL_BUSREQ_Pos               (1)                                               /*!< OTG_T::CTL: BUSREQ Position            */
#define OTG_CTL_BUSREQ_Msk               (0x1ul << OTG_CTL_BUSREQ_Pos)                     /*!< OTG_T::CTL: BUSREQ Mask                */

#define OTG_CTL_HNPREQEN_Pos             (2)                                               /*!< OTG_T::CTL: HNPREQEN Position          */
#define OTG_CTL_HNPREQEN_Msk             (0x1ul << OTG_CTL_HNPREQEN_Pos)                   /*!< OTG_T::CTL: HNPREQEN Mask              */

#define OTG_CTL_OTGEN_Pos                (4)                                               /*!< OTG_T::CTL: OTGEN Position             */
#define OTG_CTL_OTGEN_Msk                (0x1ul << OTG_CTL_OTGEN_Pos)                      /*!< OTG_T::CTL: OTGEN Mask                 */

#define OTG_CTL_WKEN_Pos                 (5)                                               /*!< OTG_T::CTL: WKEN Position              */
#define OTG_CTL_WKEN_Msk                 (0x1ul << OTG_CTL_WKEN_Pos)                       /*!< OTG_T::CTL: WKEN Mask                  */

#define OTG_PHYCTL_OTGPHYEN_Pos          (0)                                               /*!< OTG_T::PHYCTL: OTGPHYEN Position       */
#define OTG_PHYCTL_OTGPHYEN_Msk          (0x1ul << OTG_PHYCTL_OTGPHYEN_Pos)                /*!< OTG_T::PHYCTL: OTGPHYEN Mask           */

#define OTG_PHYCTL_IDDETEN_Pos           (1)                                               /*!< OTG_T::PHYCTL: IDDETEN Position        */
#define OTG_PHYCTL_IDDETEN_Msk           (0x1ul << OTG_PHYCTL_IDDETEN_Pos)                 /*!< OTG_T::PHYCTL: IDDETEN Mask            */

#define OTG_PHYCTL_VBENPOL_Pos           (4)                                               /*!< OTG_T::PHYCTL: VBENPOL Position        */
#define OTG_PHYCTL_VBENPOL_Msk           (0x1ul << OTG_PHYCTL_VBENPOL_Pos)                 /*!< OTG_T::PHYCTL: VBENPOL Mask            */

#define OTG_PHYCTL_VBSTSPOL_Pos          (5)                                               /*!< OTG_T::PHYCTL: VBSTSPOL Position       */
#define OTG_PHYCTL_VBSTSPOL_Msk          (0x1ul << OTG_PHYCTL_VBSTSPOL_Pos)                /*!< OTG_T::PHYCTL: VBSTSPOL Mask           */

#define OTG_INTEN_ROLECHGIEN_Pos         (0)                                               /*!< OTG_T::INTEN: ROLECHGIEN Position      */
#define OTG_INTEN_ROLECHGIEN_Msk         (0x1ul << OTG_INTEN_ROLECHGIEN_Pos)               /*!< OTG_T::INTEN: ROLECHGIEN Mask          */

#define OTG_INTEN_VBEIEN_Pos             (1)                                               /*!< OTG_T::INTEN: VBEIEN Position          */
#define OTG_INTEN_VBEIEN_Msk             (0x1ul << OTG_INTEN_VBEIEN_Pos)                   /*!< OTG_T::INTEN: VBEIEN Mask              */

#define OTG_INTEN_SRPFIEN_Pos            (2)                                               /*!< OTG_T::INTEN: SRPFIEN Position         */
#define OTG_INTEN_SRPFIEN_Msk            (0x1ul << OTG_INTEN_SRPFIEN_Pos)                  /*!< OTG_T::INTEN: SRPFIEN Mask             */

#define OTG_INTEN_HNPFIEN_Pos            (3)                                               /*!< OTG_T::INTEN: HNPFIEN Position         */
#define OTG_INTEN_HNPFIEN_Msk            (0x1ul << OTG_INTEN_HNPFIEN_Pos)                  /*!< OTG_T::INTEN: HNPFIEN Mask             */

#define OTG_INTEN_GOIDLEIEN_Pos          (4)                                               /*!< OTG_T::INTEN: GOIDLEIEN Position       */
#define OTG_INTEN_GOIDLEIEN_Msk          (0x1ul << OTG_INTEN_GOIDLEIEN_Pos)                /*!< OTG_T::INTEN: GOIDLEIEN Mask           */

#define OTG_INTEN_IDCHGIEN_Pos           (5)                                               /*!< OTG_T::INTEN: IDCHGIEN Position        */
#define OTG_INTEN_IDCHGIEN_Msk           (0x1ul << OTG_INTEN_IDCHGIEN_Pos)                 /*!< OTG_T::INTEN: IDCHGIEN Mask            */

#define OTG_INTEN_PDEVIEN_Pos            (6)                                               /*!< OTG_T::INTEN: PDEVIEN Position         */
#define OTG_INTEN_PDEVIEN_Msk            (0x1ul << OTG_INTEN_PDEVIEN_Pos)                  /*!< OTG_T::INTEN: PDEVIEN Mask             */

#define OTG_INTEN_HOSTIEN_Pos            (7)                                               /*!< OTG_T::INTEN: HOSTIEN Position         */
#define OTG_INTEN_HOSTIEN_Msk            (0x1ul << OTG_INTEN_HOSTIEN_Pos)                  /*!< OTG_T::INTEN: HOSTIEN Mask             */

#define OTG_INTEN_BVLDCHGIEN_Pos         (8)                                               /*!< OTG_T::INTEN: BVLDCHGIEN Position      */
#define OTG_INTEN_BVLDCHGIEN_Msk         (0x1ul << OTG_INTEN_BVLDCHGIEN_Pos)               /*!< OTG_T::INTEN: BVLDCHGIEN Mask          */

#define OTG_INTEN_AVLDCHGIEN_Pos         (9)                                               /*!< OTG_T::INTEN: AVLDCHGIEN Position      */
#define OTG_INTEN_AVLDCHGIEN_Msk         (0x1ul << OTG_INTEN_AVLDCHGIEN_Pos)               /*!< OTG_T::INTEN: AVLDCHGIEN Mask          */

#define OTG_INTEN_VBCHGIEN_Pos           (10)                                              /*!< OTG_T::INTEN: VBCHGIEN Position        */
#define OTG_INTEN_VBCHGIEN_Msk           (0x1ul << OTG_INTEN_VBCHGIEN_Pos)                 /*!< OTG_T::INTEN: VBCHGIEN Mask            */

#define OTG_INTEN_SECHGIEN_Pos           (11)                                              /*!< OTG_T::INTEN: SECHGIEN Position        */
#define OTG_INTEN_SECHGIEN_Msk           (0x1ul << OTG_INTEN_SECHGIEN_Pos)                 /*!< OTG_T::INTEN: SECHGIEN Mask            */

#define OTG_INTEN_SRPDETIEN_Pos          (13)                                              /*!< OTG_T::INTEN: SRPDETIEN Position       */
#define OTG_INTEN_SRPDETIEN_Msk          (0x1ul << OTG_INTEN_SRPDETIEN_Pos)                /*!< OTG_T::INTEN: SRPDETIEN Mask           */

#define OTG_INTSTS_ROLECHGIF_Pos         (0)                                               /*!< OTG_T::INTSTS: ROLECHGIF Position      */
#define OTG_INTSTS_ROLECHGIF_Msk         (0x1ul << OTG_INTSTS_ROLECHGIF_Pos)               /*!< OTG_T::INTSTS: ROLECHGIF Mask          */

#define OTG_INTSTS_VBEIF_Pos             (1)                                               /*!< OTG_T::INTSTS: VBEIF Position          */
#define OTG_INTSTS_VBEIF_Msk             (0x1ul << OTG_INTSTS_VBEIF_Pos)                   /*!< OTG_T::INTSTS: VBEIF Mask              */

#define OTG_INTSTS_SRPFIF_Pos            (2)                                               /*!< OTG_T::INTSTS: SRPFIF Position         */
#define OTG_INTSTS_SRPFIF_Msk            (0x1ul << OTG_INTSTS_SRPFIF_Pos)                  /*!< OTG_T::INTSTS: SRPFIF Mask             */

#define OTG_INTSTS_HNPFIF_Pos            (3)                                               /*!< OTG_T::INTSTS: HNPFIF Position         */
#define OTG_INTSTS_HNPFIF_Msk            (0x1ul << OTG_INTSTS_HNPFIF_Pos)                  /*!< OTG_T::INTSTS: HNPFIF Mask             */

#define OTG_INTSTS_GOIDLEIF_Pos          (4)                                               /*!< OTG_T::INTSTS: GOIDLEIF Position       */
#define OTG_INTSTS_GOIDLEIF_Msk          (0x1ul << OTG_INTSTS_GOIDLEIF_Pos)                /*!< OTG_T::INTSTS: GOIDLEIF Mask           */

#define OTG_INTSTS_IDCHGIF_Pos           (5)                                               /*!< OTG_T::INTSTS: IDCHGIF Position        */
#define OTG_INTSTS_IDCHGIF_Msk           (0x1ul << OTG_INTSTS_IDCHGIF_Pos)                 /*!< OTG_T::INTSTS: IDCHGIF Mask            */

#define OTG_INTSTS_PDEVIF_Pos            (6)                                               /*!< OTG_T::INTSTS: PDEVIF Position         */
#define OTG_INTSTS_PDEVIF_Msk            (0x1ul << OTG_INTSTS_PDEVIF_Pos)                  /*!< OTG_T::INTSTS: PDEVIF Mask             */

#define OTG_INTSTS_HOSTIF_Pos            (7)                                               /*!< OTG_T::INTSTS: HOSTIF Position         */
#define OTG_INTSTS_HOSTIF_Msk            (0x1ul << OTG_INTSTS_HOSTIF_Pos)                  /*!< OTG_T::INTSTS: HOSTIF Mask             */

#define OTG_INTSTS_BVLDCHGIF_Pos         (8)                                               /*!< OTG_T::INTSTS: BVLDCHGIF Position      */
#define OTG_INTSTS_BVLDCHGIF_Msk         (0x1ul << OTG_INTSTS_BVLDCHGIF_Pos)               /*!< OTG_T::INTSTS: BVLDCHGIF Mask          */

#define OTG_INTSTS_AVLDCHGIF_Pos         (9)                                               /*!< OTG_T::INTSTS: AVLDCHGIF Position      */
#define OTG_INTSTS_AVLDCHGIF_Msk         (0x1ul << OTG_INTSTS_AVLDCHGIF_Pos)               /*!< OTG_T::INTSTS: AVLDCHGIF Mask          */

#define OTG_INTSTS_VBCHGIF_Pos           (10)                                              /*!< OTG_T::INTSTS: VBCHGIF Position        */
#define OTG_INTSTS_VBCHGIF_Msk           (0x1ul << OTG_INTSTS_VBCHGIF_Pos)                 /*!< OTG_T::INTSTS: VBCHGIF Mask            */

#define OTG_INTSTS_SECHGIF_Pos           (11)                                              /*!< OTG_T::INTSTS: SECHGIF Position        */
#define OTG_INTSTS_SECHGIF_Msk           (0x1ul << OTG_INTSTS_SECHGIF_Pos)                 /*!< OTG_T::INTSTS: SECHGIF Mask            */

#define OTG_INTSTS_SRPDETIF_Pos          (13)                                              /*!< OTG_T::INTSTS: SRPDETIF Position       */
#define OTG_INTSTS_SRPDETIF_Msk          (0x1ul << OTG_INTSTS_SRPDETIF_Pos)                /*!< OTG_T::INTSTS: SRPDETIF Mask           */

#define OTG_STATUS_OVERCUR_Pos           (0)                                               /*!< OTG_T::STATUS: OVERCUR Position        */
#define OTG_STATUS_OVERCUR_Msk           (0x1ul << OTG_STATUS_OVERCUR_Pos)                 /*!< OTG_T::STATUS: OVERCUR Mask            */

#define OTG_STATUS_IDSTS_Pos             (1)                                               /*!< OTG_T::STATUS: IDSTS Position          */
#define OTG_STATUS_IDSTS_Msk             (0x1ul << OTG_STATUS_IDSTS_Pos)                   /*!< OTG_T::STATUS: IDSTS Mask              */

#define OTG_STATUS_SESSEND_Pos           (2)                                               /*!< OTG_T::STATUS: SESSEND Position        */
#define OTG_STATUS_SESSEND_Msk           (0x1ul << OTG_STATUS_SESSEND_Pos)                 /*!< OTG_T::STATUS: SESSEND Mask            */

#define OTG_STATUS_BVLD_Pos              (3)                                               /*!< OTG_T::STATUS: BVLD Position           */
#define OTG_STATUS_BVLD_Msk              (0x1ul << OTG_STATUS_BVLD_Pos)                    /*!< OTG_T::STATUS: BVLD Mask               */

#define OTG_STATUS_AVLD_Pos              (4)                                               /*!< OTG_T::STATUS: AVLD Position           */
#define OTG_STATUS_AVLD_Msk              (0x1ul << OTG_STATUS_AVLD_Pos)                    /*!< OTG_T::STATUS: AVLD Mask               */

#define OTG_STATUS_VBUSVLD_Pos           (5)                                               /*!< OTG_T::STATUS: VBUSVLD Position        */
#define OTG_STATUS_VBUSVLD_Msk           (0x1ul << OTG_STATUS_VBUSVLD_Pos)                 /*!< OTG_T::STATUS: VBUSVLD Mask            */

#define OTG_STATUS_ASPERI_Pos            (6)                                               /*!< OTG_T::STATUS: ASPERI Position         */
#define OTG_STATUS_ASPERI_Msk            (0x1ul << OTG_STATUS_ASPERI_Pos)                  /*!< OTG_T::STATUS: ASPERI Mask             */

#define OTG_STATUS_ASHOST_Pos            (7)                                               /*!< OTG_T::STATUS: ASHOST Position         */
#define OTG_STATUS_ASHOST_Msk            (0x1ul << OTG_STATUS_ASHOST_Pos)                  /*!< OTG_T::STATUS: ASHOST Mask             */

/**@}*/ /* OTG_CONST */
/**@}*/ /* end of OTG register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __OTG_REG_H__ */
