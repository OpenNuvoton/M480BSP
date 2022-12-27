/**************************************************************************//**
 * @file     hsotg_reg.h
 * @version  V1.00
 * @brief    HSOTG register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __HSOTG_REG_H__
#define __HSOTG_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup HSOTG High Speed USB On-The-Go Controller(HSOTG)
    Memory Mapped Structure for HSOTG Controller
@{ */

typedef struct
{


    /**
@var HSOTG_T::CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL
</font><br><p> <font size="2">
Offset: 0x00  HSOTG Control Register
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


@var HSOTG_T::PHYCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PHYCTL
</font><br><p> <font size="2">
Offset: 0x04  HSOTG PHY Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>OTGPHYEN</td><td><div style="word-wrap: break-word;"><b>OTG PHY Enable
</b><br>
When USB frame is configured as OTG-device or ID-dependent, user needs to set this bit before using OTG function
<br>
If device is not configured as OTG-device nor ID-dependent, this bit is "don't care".
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


@var HSOTG_T::INTEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTEN
</font><br><p> <font size="2">
Offset: 0x08  HSOTG Interrupt Enable Register
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


@var HSOTG_T::INTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTSTS
</font><br><p> <font size="2">
Offset: 0x0C  HSOTG Interrupt Status Register
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


@var HSOTG_T::STATUS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STATUS
</font><br><p> <font size="2">
Offset: 0x10  HSOTG Status Register
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
When VBUS is larger than 4.7V and A-device drives VBUS , this bit will be set to 1.
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
    __IO uint32_t CTL;                   /*!< [0x0000] HSOTG Control Register                                           */
    __IO uint32_t PHYCTL;                /*!< [0x0004] HSOTG PHY Control Register                                       */
    __IO uint32_t INTEN;                 /*!< [0x0008] HSOTG Interrupt Enable Register                                  */
    __IO uint32_t INTSTS;                /*!< [0x000c] HSOTG Interrupt Status Register                                  */
    __I  uint32_t STATUS;                /*!< [0x0010] HSOTG Status Register                                            */

} HSOTG_T;

/**
    @addtogroup HSOTG_CONST HSOTG Bit Field Definition
    Constant Definitions for HSOTG Controller
@{ */

#define HSOTG_CTL_VBUSDROP_Pos           (0)                                               /*!< HSOTG_T::CTL: VBUSDROP Position        */
#define HSOTG_CTL_VBUSDROP_Msk           (0x1ul << HSOTG_CTL_VBUSDROP_Pos)                 /*!< HSOTG_T::CTL: VBUSDROP Mask            */

#define HSOTG_CTL_BUSREQ_Pos             (1)                                               /*!< HSOTG_T::CTL: BUSREQ Position          */
#define HSOTG_CTL_BUSREQ_Msk             (0x1ul << HSOTG_CTL_BUSREQ_Pos)                   /*!< HSOTG_T::CTL: BUSREQ Mask              */

#define HSOTG_CTL_HNPREQEN_Pos           (2)                                               /*!< HSOTG_T::CTL: HNPREQEN Position        */
#define HSOTG_CTL_HNPREQEN_Msk           (0x1ul << HSOTG_CTL_HNPREQEN_Pos)                 /*!< HSOTG_T::CTL: HNPREQEN Mask            */

#define HSOTG_CTL_OTGEN_Pos              (4)                                               /*!< HSOTG_T::CTL: OTGEN Position           */
#define HSOTG_CTL_OTGEN_Msk              (0x1ul << HSOTG_CTL_OTGEN_Pos)                    /*!< HSOTG_T::CTL: OTGEN Mask               */

#define HSOTG_CTL_WKEN_Pos               (5)                                               /*!< HSOTG_T::CTL: WKEN Position            */
#define HSOTG_CTL_WKEN_Msk               (0x1ul << HSOTG_CTL_WKEN_Pos)                     /*!< HSOTG_T::CTL: WKEN Mask                */

#define HSOTG_PHYCTL_OTGPHYEN_Pos        (0)                                               /*!< HSOTG_T::PHYCTL: OTGPHYEN Position     */
#define HSOTG_PHYCTL_OTGPHYEN_Msk        (0x1ul << HSOTG_PHYCTL_OTGPHYEN_Pos)              /*!< HSOTG_T::PHYCTL: OTGPHYEN Mask         */

#define HSOTG_PHYCTL_IDDETEN_Pos         (1)                                               /*!< HSOTG_T::PHYCTL: IDDETEN Position      */
#define HSOTG_PHYCTL_IDDETEN_Msk         (0x1ul << HSOTG_PHYCTL_IDDETEN_Pos)               /*!< HSOTG_T::PHYCTL: IDDETEN Mask          */

#define HSOTG_PHYCTL_VBENPOL_Pos         (4)                                               /*!< HSOTG_T::PHYCTL: VBENPOL Position      */
#define HSOTG_PHYCTL_VBENPOL_Msk         (0x1ul << HSOTG_PHYCTL_VBENPOL_Pos)               /*!< HSOTG_T::PHYCTL: VBENPOL Mask          */

#define HSOTG_PHYCTL_VBSTSPOL_Pos        (5)                                               /*!< HSOTG_T::PHYCTL: VBSTSPOL Position     */
#define HSOTG_PHYCTL_VBSTSPOL_Msk        (0x1ul << HSOTG_PHYCTL_VBSTSPOL_Pos)              /*!< HSOTG_T::PHYCTL: VBSTSPOL Mask         */

#define HSOTG_INTEN_ROLECHGIEN_Pos       (0)                                               /*!< HSOTG_T::INTEN: ROLECHGIEN Position    */
#define HSOTG_INTEN_ROLECHGIEN_Msk       (0x1ul << HSOTG_INTEN_ROLECHGIEN_Pos)             /*!< HSOTG_T::INTEN: ROLECHGIEN Mask        */

#define HSOTG_INTEN_VBEIEN_Pos           (1)                                               /*!< HSOTG_T::INTEN: VBEIEN Position        */
#define HSOTG_INTEN_VBEIEN_Msk           (0x1ul << HSOTG_INTEN_VBEIEN_Pos)                 /*!< HSOTG_T::INTEN: VBEIEN Mask            */

#define HSOTG_INTEN_SRPFIEN_Pos          (2)                                               /*!< HSOTG_T::INTEN: SRPFIEN Position       */
#define HSOTG_INTEN_SRPFIEN_Msk          (0x1ul << HSOTG_INTEN_SRPFIEN_Pos)                /*!< HSOTG_T::INTEN: SRPFIEN Mask           */

#define HSOTG_INTEN_HNPFIEN_Pos          (3)                                               /*!< HSOTG_T::INTEN: HNPFIEN Position       */
#define HSOTG_INTEN_HNPFIEN_Msk          (0x1ul << HSOTG_INTEN_HNPFIEN_Pos)                /*!< HSOTG_T::INTEN: HNPFIEN Mask           */

#define HSOTG_INTEN_GOIDLEIEN_Pos        (4)                                               /*!< HSOTG_T::INTEN: GOIDLEIEN Position     */
#define HSOTG_INTEN_GOIDLEIEN_Msk        (0x1ul << HSOTG_INTEN_GOIDLEIEN_Pos)              /*!< HSOTG_T::INTEN: GOIDLEIEN Mask         */

#define HSOTG_INTEN_IDCHGIEN_Pos         (5)                                               /*!< HSOTG_T::INTEN: IDCHGIEN Position      */
#define HSOTG_INTEN_IDCHGIEN_Msk         (0x1ul << HSOTG_INTEN_IDCHGIEN_Pos)               /*!< HSOTG_T::INTEN: IDCHGIEN Mask          */

#define HSOTG_INTEN_PDEVIEN_Pos          (6)                                               /*!< HSOTG_T::INTEN: PDEVIEN Position       */
#define HSOTG_INTEN_PDEVIEN_Msk          (0x1ul << HSOTG_INTEN_PDEVIEN_Pos)                /*!< HSOTG_T::INTEN: PDEVIEN Mask           */

#define HSOTG_INTEN_HOSTIEN_Pos          (7)                                               /*!< HSOTG_T::INTEN: HOSTIEN Position       */
#define HSOTG_INTEN_HOSTIEN_Msk          (0x1ul << HSOTG_INTEN_HOSTIEN_Pos)                /*!< HSOTG_T::INTEN: HOSTIEN Mask           */

#define HSOTG_INTEN_BVLDCHGIEN_Pos       (8)                                               /*!< HSOTG_T::INTEN: BVLDCHGIEN Position    */
#define HSOTG_INTEN_BVLDCHGIEN_Msk       (0x1ul << HSOTG_INTEN_BVLDCHGIEN_Pos)             /*!< HSOTG_T::INTEN: BVLDCHGIEN Mask        */

#define HSOTG_INTEN_AVLDCHGIEN_Pos       (9)                                               /*!< HSOTG_T::INTEN: AVLDCHGIEN Position    */
#define HSOTG_INTEN_AVLDCHGIEN_Msk       (0x1ul << HSOTG_INTEN_AVLDCHGIEN_Pos)             /*!< HSOTG_T::INTEN: AVLDCHGIEN Mask        */

#define HSOTG_INTEN_VBCHGIEN_Pos         (10)                                              /*!< HSOTG_T::INTEN: VBCHGIEN Position      */
#define HSOTG_INTEN_VBCHGIEN_Msk         (0x1ul << HSOTG_INTEN_VBCHGIEN_Pos)               /*!< HSOTG_T::INTEN: VBCHGIEN Mask          */

#define HSOTG_INTEN_SECHGIEN_Pos         (11)                                              /*!< HSOTG_T::INTEN: SECHGIEN Position      */
#define HSOTG_INTEN_SECHGIEN_Msk         (0x1ul << HSOTG_INTEN_SECHGIEN_Pos)               /*!< HSOTG_T::INTEN: SECHGIEN Mask          */

#define HSOTG_INTEN_SRPDETIEN_Pos        (13)                                              /*!< HSOTG_T::INTEN: SRPDETIEN Position     */
#define HSOTG_INTEN_SRPDETIEN_Msk        (0x1ul << HSOTG_INTEN_SRPDETIEN_Pos)              /*!< HSOTG_T::INTEN: SRPDETIEN Mask         */

#define HSOTG_INTSTS_ROLECHGIF_Pos       (0)                                               /*!< HSOTG_T::INTSTS: ROLECHGIF Position    */
#define HSOTG_INTSTS_ROLECHGIF_Msk       (0x1ul << HSOTG_INTSTS_ROLECHGIF_Pos)             /*!< HSOTG_T::INTSTS: ROLECHGIF Mask        */

#define HSOTG_INTSTS_VBEIF_Pos           (1)                                               /*!< HSOTG_T::INTSTS: VBEIF Position        */
#define HSOTG_INTSTS_VBEIF_Msk           (0x1ul << HSOTG_INTSTS_VBEIF_Pos)                 /*!< HSOTG_T::INTSTS: VBEIF Mask            */

#define HSOTG_INTSTS_SRPFIF_Pos          (2)                                               /*!< HSOTG_T::INTSTS: SRPFIF Position       */
#define HSOTG_INTSTS_SRPFIF_Msk          (0x1ul << HSOTG_INTSTS_SRPFIF_Pos)                /*!< HSOTG_T::INTSTS: SRPFIF Mask           */

#define HSOTG_INTSTS_HNPFIF_Pos          (3)                                               /*!< HSOTG_T::INTSTS: HNPFIF Position       */
#define HSOTG_INTSTS_HNPFIF_Msk          (0x1ul << HSOTG_INTSTS_HNPFIF_Pos)                /*!< HSOTG_T::INTSTS: HNPFIF Mask           */

#define HSOTG_INTSTS_GOIDLEIF_Pos        (4)                                               /*!< HSOTG_T::INTSTS: GOIDLEIF Position     */
#define HSOTG_INTSTS_GOIDLEIF_Msk        (0x1ul << HSOTG_INTSTS_GOIDLEIF_Pos)              /*!< HSOTG_T::INTSTS: GOIDLEIF Mask         */

#define HSOTG_INTSTS_IDCHGIF_Pos         (5)                                               /*!< HSOTG_T::INTSTS: IDCHGIF Position      */
#define HSOTG_INTSTS_IDCHGIF_Msk         (0x1ul << HSOTG_INTSTS_IDCHGIF_Pos)               /*!< HSOTG_T::INTSTS: IDCHGIF Mask          */

#define HSOTG_INTSTS_PDEVIF_Pos          (6)                                               /*!< HSOTG_T::INTSTS: PDEVIF Position       */
#define HSOTG_INTSTS_PDEVIF_Msk          (0x1ul << HSOTG_INTSTS_PDEVIF_Pos)                /*!< HSOTG_T::INTSTS: PDEVIF Mask           */

#define HSOTG_INTSTS_HOSTIF_Pos          (7)                                               /*!< HSOTG_T::INTSTS: HOSTIF Position       */
#define HSOTG_INTSTS_HOSTIF_Msk          (0x1ul << HSOTG_INTSTS_HOSTIF_Pos)                /*!< HSOTG_T::INTSTS: HOSTIF Mask           */

#define HSOTG_INTSTS_BVLDCHGIF_Pos       (8)                                               /*!< HSOTG_T::INTSTS: BVLDCHGIF Position    */
#define HSOTG_INTSTS_BVLDCHGIF_Msk       (0x1ul << HSOTG_INTSTS_BVLDCHGIF_Pos)             /*!< HSOTG_T::INTSTS: BVLDCHGIF Mask        */

#define HSOTG_INTSTS_AVLDCHGIF_Pos       (9)                                               /*!< HSOTG_T::INTSTS: AVLDCHGIF Position    */
#define HSOTG_INTSTS_AVLDCHGIF_Msk       (0x1ul << HSOTG_INTSTS_AVLDCHGIF_Pos)             /*!< HSOTG_T::INTSTS: AVLDCHGIF Mask        */

#define HSOTG_INTSTS_VBCHGIF_Pos         (10)                                              /*!< HSOTG_T::INTSTS: VBCHGIF Position      */
#define HSOTG_INTSTS_VBCHGIF_Msk         (0x1ul << HSOTG_INTSTS_VBCHGIF_Pos)               /*!< HSOTG_T::INTSTS: VBCHGIF Mask          */

#define HSOTG_INTSTS_SECHGIF_Pos         (11)                                              /*!< HSOTG_T::INTSTS: SECHGIF Position      */
#define HSOTG_INTSTS_SECHGIF_Msk         (0x1ul << HSOTG_INTSTS_SECHGIF_Pos)               /*!< HSOTG_T::INTSTS: SECHGIF Mask          */

#define HSOTG_INTSTS_SRPDETIF_Pos        (13)                                              /*!< HSOTG_T::INTSTS: SRPDETIF Position     */
#define HSOTG_INTSTS_SRPDETIF_Msk        (0x1ul << HSOTG_INTSTS_SRPDETIF_Pos)              /*!< HSOTG_T::INTSTS: SRPDETIF Mask         */

#define HSOTG_STATUS_OVERCUR_Pos         (0)                                               /*!< HSOTG_T::STATUS: OVERCUR Position      */
#define HSOTG_STATUS_OVERCUR_Msk         (0x1ul << HSOTG_STATUS_OVERCUR_Pos)               /*!< HSOTG_T::STATUS: OVERCUR Mask          */

#define HSOTG_STATUS_IDSTS_Pos           (1)                                               /*!< HSOTG_T::STATUS: IDSTS Position        */
#define HSOTG_STATUS_IDSTS_Msk           (0x1ul << HSOTG_STATUS_IDSTS_Pos)                 /*!< HSOTG_T::STATUS: IDSTS Mask            */

#define HSOTG_STATUS_SESSEND_Pos         (2)                                               /*!< HSOTG_T::STATUS: SESSEND Position      */
#define HSOTG_STATUS_SESSEND_Msk         (0x1ul << HSOTG_STATUS_SESSEND_Pos)               /*!< HSOTG_T::STATUS: SESSEND Mask          */

#define HSOTG_STATUS_BVLD_Pos            (3)                                               /*!< HSOTG_T::STATUS: BVLD Position         */
#define HSOTG_STATUS_BVLD_Msk            (0x1ul << HSOTG_STATUS_BVLD_Pos)                  /*!< HSOTG_T::STATUS: BVLD Mask             */

#define HSOTG_STATUS_AVLD_Pos            (4)                                               /*!< HSOTG_T::STATUS: AVLD Position         */
#define HSOTG_STATUS_AVLD_Msk            (0x1ul << HSOTG_STATUS_AVLD_Pos)                  /*!< HSOTG_T::STATUS: AVLD Mask             */

#define HSOTG_STATUS_VBUSVLD_Pos         (5)                                               /*!< HSOTG_T::STATUS: VBUSVLD Position      */
#define HSOTG_STATUS_VBUSVLD_Msk         (0x1ul << HSOTG_STATUS_VBUSVLD_Pos)               /*!< HSOTG_T::STATUS: VBUSVLD Mask          */

#define HSOTG_STATUS_ASPERI_Pos          (6)                                               /*!< HSOTG_T::STATUS: ASPERI Position       */
#define HSOTG_STATUS_ASPERI_Msk          (0x1ul << HSOTG_STATUS_ASPERI_Pos)                /*!< HSOTG_T::STATUS: ASPERI Mask           */

#define HSOTG_STATUS_ASHOST_Pos          (7)                                               /*!< HSOTG_T::STATUS: ASHOST Position       */
#define HSOTG_STATUS_ASHOST_Msk          (0x1ul << HSOTG_STATUS_ASHOST_Pos)                /*!< HSOTG_T::STATUS: ASHOST Mask           */

/**@}*/ /* HSOTG_CONST */
/**@}*/ /* end of HSOTG register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __HSOTG_REG_H__ */
