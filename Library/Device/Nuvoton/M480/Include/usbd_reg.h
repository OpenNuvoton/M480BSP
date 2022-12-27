/**************************************************************************//**
 * @file     usbd_reg.h
 * @version  V1.00
 * @brief    USBD register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __USBD_REG_H__
#define __USBD_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup USBD USB Device Controller(USBD)
    Memory Mapped Structure for USBD Controller
@{ */

typedef struct
{

    /**
@var USBD_EP_T::BUFSEG

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BUFSEG
</font><br><p> <font size="2">
Offset: 0x000  Endpoint n Buffer Segmentation Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[8:3]</td><td>BUFSEG</td><td><div style="word-wrap: break-word;"><b>Endpoint Buffer Segmentation
</b><br>
It is used to indicate the offset address for each endpoint with the USB SRAM starting address The effective starting address of the endpoint is
<br>
USBD_SRAM address + { BUFSEG, 3'b000}
<br>
Where the USBD_SRAM address = USBD_BA+0x100h.
<br>
Refer to the section 7.29.5.7 for the endpoint SRAM structure and its description.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBD_EP_T::MXPLD

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MXPLD
</font><br><p> <font size="2">
Offset: 0x004  Endpoint n Maximal Payload Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[8:0]</td><td>MXPLD</td><td><div style="word-wrap: break-word;"><b>Maximal Payload
</b><br>
Define the data length which is transmitted to host (IN token) or the actual data length which is received from the host (OUT token)
<br>
It also used to indicate that the endpoint is ready to be transmitted in IN token or received in OUT token.
<br>
(1) When the register is written by CPU,
<br>
For IN token, the value of MXPLD is used to define the data length to be transmitted and indicate the data buffer is ready.
<br>
For OUT token, it means that the controller is ready to receive data from the host and the value of MXPLD is the maximal data length comes from host.
<br>
(2) When the register is read by CPU,
<br>
For IN token, the value of MXPLD is indicated by the data length be transmitted to host
<br>
For OUT token, the value of MXPLD is indicated the actual data length receiving from host.
<br>
Note: Once MXPLD is written, the data packets will be transmitted/received immediately after IN/OUT token arrived.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBD_EP_T::CFG

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CFG
</font><br><p> <font size="2">
Offset: 0x008  Endpoint n Configuration Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>EPNUM</td><td><div style="word-wrap: break-word;"><b>Endpoint Number
</b><br>
These bits are used to define the endpoint number of the current endpoint
<br>
</div></td></tr><tr><td>
[4]</td><td>ISOCH</td><td><div style="word-wrap: break-word;"><b>Isochronous Endpoint
</b><br>
This bit is used to set the endpoint as Isochronous endpoint, no handshake.
<br>
0 = No Isochronous endpoint.
<br>
1 = Isochronous endpoint.
<br>
</div></td></tr><tr><td>
[6:5]</td><td>STATE</td><td><div style="word-wrap: break-word;"><b>Endpoint STATE
</b><br>
00 = Endpoint is Disabled.
<br>
01 = Out endpoint.
<br>
10 = IN endpoint.
<br>
11 = Undefined.
<br>
</div></td></tr><tr><td>
[7]</td><td>DSQSYNC</td><td><div style="word-wrap: break-word;"><b>Data Sequence Synchronization
</b><br>
0 = DATA0 PID.
<br>
1 = DATA1 PID.
<br>
Note: It is used to specify the DATA0 or DATA1 PID in the following IN token transaction
<br>
hardware will toggle automatically in IN token base on the bit.
<br>
</div></td></tr><tr><td>
[9]</td><td>CSTALL</td><td><div style="word-wrap: break-word;"><b>Clear STALL Response
</b><br>
0 = Disable the device to clear the STALL handshake in setup stage.
<br>
1 = Clear the device to response STALL handshake in setup stage.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBD_EP_T::CFGP

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CFGP
</font><br><p> <font size="2">
Offset: 0x00C  Endpoint n Set Stall and Clear In/Out Ready Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CLRRDY</td><td><div style="word-wrap: break-word;"><b>Clear Ready
</b><br>
When the USBD_MXPLDx register is set by user, it means that the endpoint is ready to transmit or receive data
<br>
If the user wants to disable this transaction before the transaction start, users can set this bit to 1 to disable it and it is auto clear to 0.
<br>
For IN token, write '1' to clear the IN token had ready to transmit the data to USB.
<br>
For OUT token, write '1' to clear the OUT token had ready to receive the data from USB.
<br>
This bit is write 1 only and is always 0 when it is read back.
<br>
</div></td></tr><tr><td>
[1]</td><td>SSTALL</td><td><div style="word-wrap: break-word;"><b>Set STALL
</b><br>
0 = Disable the device to response STALL.
<br>
1 = Set the device to respond STALL automatically.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t BUFSEG;               /*!< [0x0000] Endpoint n Buffer Segmentation Register                          */
    __IO uint32_t MXPLD;                /*!< [0x0004] Endpoint n Maximal Payload Register                              */
    __IO uint32_t CFG;                  /*!< [0x0008] Endpoint n Configuration Register                                */
    __IO uint32_t CFGP;                 /*!< [0x000c] Endpoint n Set Stall and Clear In/Out Ready Control Register     */

} USBD_EP_T;

typedef struct
{


    /**
@var USBD_T::INTEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTEN
</font><br><p> <font size="2">
Offset: 0x00  USB Device Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BUSIEN</td><td><div style="word-wrap: break-word;"><b>Bus Event Interrupt Enable Bit
</b><br>
0 = BUS event interrupt Disabled.
<br>
1 = BUS event interrupt Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>USBIEN</td><td><div style="word-wrap: break-word;"><b>USB Event Interrupt Enable Bit
</b><br>
0 = USB event interrupt Disabled.
<br>
1 = USB event interrupt Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>VBDETIEN</td><td><div style="word-wrap: break-word;"><b>VBUS Detection Interrupt Enable Bit
</b><br>
0 = VBUS detection Interrupt Disabled.
<br>
1 = VBUS detection Interrupt Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>NEVWKIEN</td><td><div style="word-wrap: break-word;"><b>USB No-event-wake-up Interrupt Enable Bit
</b><br>
0 = No-event-wake-up Interrupt Disabled.
<br>
1 = No-event-wake-up Interrupt Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>SOFIEN</td><td><div style="word-wrap: break-word;"><b>Start of Frame Interrupt Enable Bit
</b><br>
0 = SOF Interrupt Disabled.
<br>
1 = SOF Interrupt Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>WKEN</td><td><div style="word-wrap: break-word;"><b>Wake-up Function Enable Bit
</b><br>
0 = USB wake-up function Disabled.
<br>
1 = USB wake-up function Enabled.
<br>
</div></td></tr><tr><td>
[15]</td><td>INNAKEN</td><td><div style="word-wrap: break-word;"><b>Active NAK Function and Its Status in IN Token
</b><br>
0 = When device responds NAK after receiving IN token, IN NAK status will not be updated to USBD_EPSTS0 and USBD_EPSTS1register, so that the USB interrupt event will not be asserted.
<br>
1 = IN NAK status will be updated to USBD_EPSTS0 and USBD_EPSTS1 register and the USB interrupt event will be asserted, when the device responds NAK after receiving IN token.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBD_T::INTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTSTS
</font><br><p> <font size="2">
Offset: 0x04  USB Device Interrupt Event Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BUSIF</td><td><div style="word-wrap: break-word;"><b>BUS Interrupt Status
</b><br>
The BUS event means that there is one of the suspense or the resume function in the bus.
<br>
0 = No BUS event occurred.
<br>
1 = Bus event occurred; check USBD_ATTR[3:0] to know which kind of bus event was occurred, cleared by write 1 to USBD_INTSTS[0].
<br>
</div></td></tr><tr><td>
[1]</td><td>USBIF</td><td><div style="word-wrap: break-word;"><b>USB Event Interrupt Status
</b><br>
The USB event includes the SETUP Token, IN Token, OUT ACK, ISO IN, or ISO OUT events in the bus.
<br>
0 = No USB event occurred.
<br>
1 = USB event occurred, check EPSTS0~5[2:0] to know which kind of USB event was occurred, cleared by write 1 to USBD_INTSTS[1] or EPSTS0~11 and SETUP (USBD_INTSTS[31]).
<br>
</div></td></tr><tr><td>
[2]</td><td>VBDETIF</td><td><div style="word-wrap: break-word;"><b>VBUS Detection Interrupt Status
</b><br>
0 = There is not attached/detached event in the USB.
<br>
1 = There is attached/detached event in the USB bus and it is cleared by write 1 to USBD_INTSTS[2].
<br>
</div></td></tr><tr><td>
[3]</td><td>NEVWKIF</td><td><div style="word-wrap: break-word;"><b>No-event-wake-up Interrupt Status
</b><br>
0 = NEVWK event does not occur.
<br>
1 = No-event-wake-up event occurred, cleared by write 1 to USBD_INTSTS[3].
<br>
</div></td></tr><tr><td>
[4]</td><td>SOFIF</td><td><div style="word-wrap: break-word;"><b>Start of Frame Interrupt Status
</b><br>
0 = SOF event does not occur.
<br>
1 = SOF event occurred, cleared by write 1 to USBD_INTSTS[4].
<br>
</div></td></tr><tr><td>
[16]</td><td>EPEVT0</td><td><div style="word-wrap: break-word;"><b>Endpoint 0's USB Event Status
</b><br>
0 = No event occurred in endpoint 0.
<br>
1 = USB event occurred on Endpoint 0, check USBD_EPSTS0[3:0] to know which kind of USB event was occurred, cleared by write 1 to USBD_INTSTS[16] or USBD_INTSTS[1].
<br>
</div></td></tr><tr><td>
[17]</td><td>EPEVT1</td><td><div style="word-wrap: break-word;"><b>Endpoint 1's USB Event Status
</b><br>
0 = No event occurred in endpoint 1.
<br>
1 = USB event occurred on Endpoint 1, check USBD_EPSTS0[7:4] to know which kind of USB event was occurred, cleared by write 1 to USBD_INTSTS[17] or USBD_INTSTS[1].
<br>
</div></td></tr><tr><td>
[18]</td><td>EPEVT2</td><td><div style="word-wrap: break-word;"><b>Endpoint 2's USB Event Status
</b><br>
0 = No event occurred in endpoint 2.
<br>
1 = USB event occurred on Endpoint 2, check USBD_EPSTS0[11:8] to know which kind of USB event was occurred, cleared by write 1 to USBD_INTSTS[18] or USBD_INTSTS[1].
<br>
</div></td></tr><tr><td>
[19]</td><td>EPEVT3</td><td><div style="word-wrap: break-word;"><b>Endpoint 3's USB Event Status
</b><br>
0 = No event occurred in endpoint 3.
<br>
1 = USB event occurred on Endpoint 3, check USBD_EPSTS0[15:12] to know which kind of USB event was occurred, cleared by write 1 to USBD_INTSTS[19] or USBD_INTSTS[1].
<br>
</div></td></tr><tr><td>
[20]</td><td>EPEVT4</td><td><div style="word-wrap: break-word;"><b>Endpoint 4's USB Event Status
</b><br>
0 = No event occurred in endpoint 4.
<br>
1 = USB event occurred on Endpoint 4, check USBD_EPSTS0[19:16] to know which kind of USB event was occurred, cleared by write 1 to USBD_INTSTS[20] or USBD_INTSTS[1].
<br>
</div></td></tr><tr><td>
[21]</td><td>EPEVT5</td><td><div style="word-wrap: break-word;"><b>Endpoint 5's USB Event Status
</b><br>
0 = No event occurred in endpoint 5.
<br>
1 = USB event occurred on Endpoint 5, check USBD_EPSTS0[23:20] to know which kind of USB event was occurred, cleared by write 1 to USBD_INTSTS[21] or USBD_INTSTS[1].
<br>
</div></td></tr><tr><td>
[22]</td><td>EPEVT6</td><td><div style="word-wrap: break-word;"><b>Endpoint 6's USB Event Status
</b><br>
0 = No event occurred in endpoint 6.
<br>
1 = USB event occurred on Endpoint 6, check USBD_EPSTS0[27:24] to know which kind of USB event was occurred, cleared by write 1 to USBD_INTSTS[22] or USBD_INTSTS[1].
<br>
</div></td></tr><tr><td>
[23]</td><td>EPEVT7</td><td><div style="word-wrap: break-word;"><b>Endpoint 7's USB Event Status
</b><br>
0 = No event occurred in endpoint 7.
<br>
1 = USB event occurred on Endpoint 7, check USBD_EPSTS0[31:28] to know which kind of USB event was occurred, cleared by write 1 to USBD_INTSTS[23] or USBD_INTSTS[1].
<br>
</div></td></tr><tr><td>
[24]</td><td>EPEVT8</td><td><div style="word-wrap: break-word;"><b>Endpoint 8's USB Event Status
</b><br>
0 = No event occurred in endpoint 8.
<br>
1 = USB event occurred on Endpoint 8, check USBD_EPSTS1[3 :0] to know which kind of USB event was occurred, cleared by write 1 to USBD_INTSTS[24] or USBD_INTSTS[1].
<br>
</div></td></tr><tr><td>
[25]</td><td>EPEVT9</td><td><div style="word-wrap: break-word;"><b>Endpoint 9's USB Event Status
</b><br>
0 = No event occurred in endpoint 9.
<br>
1 = USB event occurred on Endpoint 9, check USBD_EPSTS1[7 :4] to know which kind of USB event was occurred, cleared by write 1 to USBD_INTSTS[25] or USBD_INTSTS[1].
<br>
</div></td></tr><tr><td>
[26]</td><td>EPEVT10</td><td><div style="word-wrap: break-word;"><b>Endpoint 10's USB Event Status
</b><br>
0 = No event occurred in endpoint 10.
<br>
1 = USB event occurred on Endpoint 10, check USBD_EPSTS1[11 :8] to know which kind of USB event was occurred, cleared by write 1 to USBD_INTSTS[26] or USBD_INTSTS[1].
<br>
</div></td></tr><tr><td>
[27]</td><td>EPEVT11</td><td><div style="word-wrap: break-word;"><b>Endpoint 11's USB Event Status
</b><br>
0 = No event occurred in endpoint 11.
<br>
1 = USB event occurred on Endpoint 11, check USBD_EPSTS1[ 15:12] to know which kind of USB event was occurred, cleared by write 1 to USBD_INTSTS[27] or USBD_INTSTS[1].
<br>
</div></td></tr><tr><td>
[31]</td><td>SETUP</td><td><div style="word-wrap: break-word;"><b>Setup Event Status
</b><br>
0 = No Setup event.
<br>
1 = Setup event occurred, cleared by write 1 to USBD_INTSTS[31].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBD_T::FADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">FADDR
</font><br><p> <font size="2">
Offset: 0x08  USB Device Function Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[6:0]</td><td>FADDR</td><td><div style="word-wrap: break-word;"><b>USB Device Function Address
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBD_T::EPSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EPSTS
</font><br><p> <font size="2">
Offset: 0x0C  USB Device Endpoint Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7]</td><td>OV</td><td><div style="word-wrap: break-word;"><b>Overrun
</b><br>
It indicates that the received data is over the maximum payload number or not.
<br>
0 = No overrun.
<br>
1 = Out Data is more than the Max Payload in MXPLD register or the Setup Data is more than 8 Bytes.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBD_T::ATTR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ATTR
</font><br><p> <font size="2">
Offset: 0x10  USB Device Bus Status and Attribution Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>USBRST</td><td><div style="word-wrap: break-word;"><b>USB Reset Status
</b><br>
0 = Bus no reset.
<br>
1 = Bus reset when SE0 (single-ended 0) more than 2.5us.
<br>
Note: This bit is read only.
<br>
</div></td></tr><tr><td>
[1]</td><td>SUSPEND</td><td><div style="word-wrap: break-word;"><b>Suspend Status
</b><br>
0 = Bus no suspend.
<br>
1 = Bus idle more than 3ms, either cable is plugged off or host is sleeping.
<br>
Note: This bit is read only.
<br>
</div></td></tr><tr><td>
[2]</td><td>RESUME</td><td><div style="word-wrap: break-word;"><b>Resume Status
</b><br>
0 = No bus resume.
<br>
1 = Resume from suspend.
<br>
Note: This bit is read only.
<br>
</div></td></tr><tr><td>
[3]</td><td>TOUT</td><td><div style="word-wrap: break-word;"><b>Time-out Status
</b><br>
0 = No time-out.
<br>
1 = No Bus response more than 18 bits time.
<br>
Note: This bit is read only.
<br>
</div></td></tr><tr><td>
[4]</td><td>PHYEN</td><td><div style="word-wrap: break-word;"><b>PHY Transceiver Function Enable Bit
</b><br>
0 = PHY transceiver function Disabled.
<br>
1 = PHY transceiver function Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>RWAKEUP</td><td><div style="word-wrap: break-word;"><b>Remote Wake-up
</b><br>
0 = Release the USB bus from K state.
<br>
1 = Force USB bus to K (USB_D+ low, USB_D-: high) state, used for remote wake-up.
<br>
</div></td></tr><tr><td>
[7]</td><td>USBEN</td><td><div style="word-wrap: break-word;"><b>USB Controller Enable Bit
</b><br>
0 = USB Controller Disabled.
<br>
1 = USB Controller Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>DPPUEN</td><td><div style="word-wrap: break-word;"><b>Pull-up Resistor on USB_DP Enable Bit
</b><br>
0 = Pull-up resistor in USB_D+ bus Disabled.
<br>
1 = Pull-up resistor in USB_D+ bus Active.
<br>
</div></td></tr><tr><td>
[10]</td><td>BYTEM</td><td><div style="word-wrap: break-word;"><b>CPU Access USB SRAM Size Mode Selection
</b><br>
0 = Word mode: The size of the transfer from CPU to USB SRAM can be Word only.
<br>
1 = Byte mode: The size of the transfer from CPU to USB SRAM can be Byte only.
<br>
</div></td></tr><tr><td>
[11]</td><td>LPMACK</td><td><div style="word-wrap: break-word;"><b>LPM Token Acknowledge Enable Bit
</b><br>
The NYET/ACK will be returned only on a successful LPM transaction if no errors in both the EXT token and the LPM token and a valid bLinkState = 0001 (L1) is received, else ERROR and STALL will be returned automatically, respectively.
<br>
0= the valid LPM Token will be NYET.
<br>
1= the valid LPM Token will be ACK.
<br>
</div></td></tr><tr><td>
[12]</td><td>L1SUSPEND</td><td><div style="word-wrap: break-word;"><b>LPM L1 Suspend
</b><br>
0 = Bus no L1 state suspend.
<br>
1 = This bit is set by the hardware when LPM command to enter the L1 state is successfully received and acknowledged.
<br>
Note: This bit is read only.
<br>
</div></td></tr><tr><td>
[13]</td><td>L1RESUME</td><td><div style="word-wrap: break-word;"><b>LPM L1 Resume
</b><br>
0 = Bus no LPM L1 state resume.
<br>
1 = LPM L1 state Resume from LPM L1 state suspend.
<br>
Note: This bit is read only.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBD_T::VBUSDET

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">VBUSDET
</font><br><p> <font size="2">
Offset: 0x14  USB Device VBUS Detection Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>VBUSDET</td><td><div style="word-wrap: break-word;"><b>Device VBUS Detection
</b><br>
0 = Controller is not attached to the USB host.
<br>
1 = Controller is attached to the USB host.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBD_T::STBUFSEG

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STBUFSEG
</font><br><p> <font size="2">
Offset: 0x18  SETUP Token Buffer Segmentation Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[8:3]</td><td>STBUFSEG</td><td><div style="word-wrap: break-word;"><b>SETUP Token Buffer Segmentation
</b><br>
It is used to indicate the offset address for the SETUP token with the USB Device SRAM starting address The effective starting address is
<br>
USBD_SRAM address + {STBUFSEG, 3'b000}
<br>
Where the USBD_SRAM address = USBD_BA+0x100h.
<br>
Note: It is used for SETUP token only.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBD_T::EPSTS0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EPSTS0
</font><br><p> <font size="2">
Offset: 0x20  USB Device Endpoint Status Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[03:00]</td><td>EPSTS0</td><td><div style="word-wrap: break-word;"><b>Endpoint 0 Status
</b><br>
These bits are used to indicate the current status of this endpoint
<br>
0000 = In ACK.
<br>
0001 = In NAK.
<br>
0010 = Out Packet Data0 ACK.
<br>
0011 = Setup ACK.
<br>
0110 = Out Packet Data1 ACK.
<br>
0111 = Isochronous transfer end.
<br>
</div></td></tr><tr><td>
[07:04]</td><td>EPSTS1</td><td><div style="word-wrap: break-word;"><b>Endpoint 1 Status
</b><br>
These bits are used to indicate the current status of this endpoint
<br>
0000 = In ACK.
<br>
0001 = In NAK.
<br>
0010 = Out Packet Data0 ACK.
<br>
0011 = Setup ACK.
<br>
0110 = Out Packet Data1 ACK.
<br>
0111 = Isochronous transfer end.
<br>
</div></td></tr><tr><td>
[11:08]</td><td>EPSTS2</td><td><div style="word-wrap: break-word;"><b>Endpoint 2 Status
</b><br>
These bits are used to indicate the current status of this endpoint
<br>
0000 = In ACK.
<br>
0001 = In NAK.
<br>
0010 = Out Packet Data0 ACK.
<br>
0011 = Setup ACK.
<br>
0110 = Out Packet Data1 ACK.
<br>
0111 = Isochronous transfer end.
<br>
</div></td></tr><tr><td>
[15:12]</td><td>EPSTS3</td><td><div style="word-wrap: break-word;"><b>Endpoint 3 Status
</b><br>
These bits are used to indicate the current status of this endpoint
<br>
0000 = In ACK.
<br>
0001 = In NAK.
<br>
0010 = Out Packet Data0 ACK.
<br>
0011 = Setup ACK.
<br>
0110 = Out Packet Data1 ACK.
<br>
0111 = Isochronous transfer end.
<br>
</div></td></tr><tr><td>
[19:16]</td><td>EPSTS4</td><td><div style="word-wrap: break-word;"><b>Endpoint 4 Status
</b><br>
These bits are used to indicate the current status of this endpoint
<br>
0000 = In ACK.
<br>
0001 = In NAK.
<br>
0010 = Out Packet Data0 ACK.
<br>
0011 = Setup ACK.
<br>
0110 = Out Packet Data1 ACK.
<br>
0111 = Isochronous transfer end.
<br>
</div></td></tr><tr><td>
[23:20]</td><td>EPSTS5</td><td><div style="word-wrap: break-word;"><b>Endpoint 5 Status
</b><br>
These bits are used to indicate the current status of this endpoint
<br>
0000 = In ACK.
<br>
0001 = In NAK.
<br>
0010 = Out Packet Data0 ACK.
<br>
0011 = Setup ACK.
<br>
0110 = Out Packet Data1 ACK.
<br>
0111 = Isochronous transfer end.
<br>
</div></td></tr><tr><td>
[27:24]</td><td>EPSTS6</td><td><div style="word-wrap: break-word;"><b>Endpoint 6 Status
</b><br>
These bits are used to indicate the current status of this endpoint
<br>
0000 = In ACK.
<br>
0001 = In NAK.
<br>
0010 = Out Packet Data0 ACK.
<br>
0011 = Setup ACK.
<br>
0110 = Out Packet Data1 ACK.
<br>
0111 = Isochronous transfer end.
<br>
</div></td></tr><tr><td>
[31:28]</td><td>EPSTS7</td><td><div style="word-wrap: break-word;"><b>Endpoint 7 Status
</b><br>
These bits are used to indicate the current status of this endpoint
<br>
0000 = In ACK.
<br>
0001 = In NAK.
<br>
0010 = Out Packet Data0 ACK.
<br>
0011 = Setup ACK.
<br>
0110 = Out Packet Data1 ACK.
<br>
0111 = Isochronous transfer end.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBD_T::EPSTS1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">EPSTS1
</font><br><p> <font size="2">
Offset: 0x24  USB Device Endpoint Status Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>EPSTS8</td><td><div style="word-wrap: break-word;"><b>Endpoint 8 Status
</b><br>
These bits are used to indicate the current status of this endpoint
<br>
0000 = In ACK.
<br>
0001 = In NAK.
<br>
0010 = Out Packet Data0 ACK.
<br>
0011 = Setup ACK.
<br>
0110 = Out Packet Data1 ACK.
<br>
0111 = Isochronous transfer end.
<br>
</div></td></tr><tr><td>
[7:4]</td><td>EPSTS9</td><td><div style="word-wrap: break-word;"><b>Endpoint 9 Status
</b><br>
These bits are used to indicate the current status of this endpoint
<br>
0000 = In ACK.
<br>
0001 = In NAK.
<br>
0010 = Out Packet Data0 ACK.
<br>
0011 = Setup ACK.
<br>
0110 = Out Packet Data1 ACK.
<br>
0111 = Isochronous transfer end.
<br>
</div></td></tr><tr><td>
[11:8]</td><td>EPSTS10</td><td><div style="word-wrap: break-word;"><b>Endpoint 10 Status
</b><br>
These bits are used to indicate the current status of this endpoint
<br>
0000 = In ACK.
<br>
0001 = In NAK.
<br>
0010 = Out Packet Data0 ACK.
<br>
0011 = Setup ACK.
<br>
0110 = Out Packet Data1 ACK.
<br>
0111 = Isochronous transfer end.
<br>
</div></td></tr><tr><td>
[15:12]</td><td>EPSTS11</td><td><div style="word-wrap: break-word;"><b>Endpoint 11 Status
</b><br>
These bits are used to indicate the current status of this endpoint
<br>
0000 = In ACK.
<br>
0001 = In NAK.
<br>
0010 = Out Packet Data0 ACK.
<br>
0011 = Setup ACK.
<br>
0110 = Out Packet Data1 ACK.
<br>
0111 = Isochronous transfer end.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBD_T::LPMATTR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">LPMATTR
</font><br><p> <font size="2">
Offset: 0x88  USB LPM Attribution Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>LPMLINKSTS</td><td><div style="word-wrap: break-word;"><b>LPM Link State
</b><br>
These bits contain the bLinkState received with last ACK LPM Token
<br>
</div></td></tr><tr><td>
[7:4]</td><td>LPMBESL</td><td><div style="word-wrap: break-word;"><b>LPM Best Effort Service Latency
</b><br>
These bits contain the BESL value received with last ACK LPM Token
<br>
</div></td></tr><tr><td>
[8]</td><td>LPMRWAKUP</td><td><div style="word-wrap: break-word;"><b>LPM Remote Wakeup
</b><br>
This bit contains the bRemoteWake value received with last ACK LPM Token
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBD_T::FN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">FN
</font><br><p> <font size="2">
Offset: 0x8C  USB Frame number Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[10:0]</td><td>FN</td><td><div style="word-wrap: break-word;"><b>Frame Number
</b><br>
These bits contain the 11-bits frame number in the last received SOF packet.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var USBD_T::SE0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SE0
</font><br><p> <font size="2">
Offset: 0x90  USB Device Drive SE0 Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SE0</td><td><div style="word-wrap: break-word;"><b>Drive Single Ended Zero in USB Bus
</b><br>
The Single Ended Zero (SE0) is when both lines (USB_D+ and USB_D-) are being pulled low.
<br>
0 = Normal operation.
<br>
1 = Force USB PHY transceiver to drive SE0.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */

    __IO uint32_t INTEN;                 /*!< [0x0000] USB Device Interrupt Enable Register                             */
    __IO uint32_t INTSTS;                /*!< [0x0004] USB Device Interrupt Event Status Register                       */
    __IO uint32_t FADDR;                 /*!< [0x0008] USB Device Function Address Register                             */
    __I  uint32_t EPSTS;                 /*!< [0x000c] USB Device Endpoint Status Register                              */
    __IO uint32_t ATTR;                  /*!< [0x0010] USB Device Bus Status and Attribution Register                   */
    __I  uint32_t VBUSDET;               /*!< [0x0014] USB Device VBUS Detection Register                               */
    __IO uint32_t STBUFSEG;              /*!< [0x0018] SETUP Token Buffer Segmentation Register                         */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[1];
    /// @endcond //HIDDEN_SYMBOLS
    __I  uint32_t EPSTS0;                /*!< [0x0020] USB Device Endpoint Status Register 0                            */
    __I  uint32_t EPSTS1;                /*!< [0x0024] USB Device Endpoint Status Register 1                            */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[24];
    /// @endcond //HIDDEN_SYMBOLS
    __I  uint32_t LPMATTR;               /*!< [0x0088] USB LPM Attribution Register                                     */
    __I  uint32_t FN;                    /*!< [0x008c] USB Frame number Register                                        */
    __IO uint32_t SE0;                   /*!< [0x0090] USB Device Drive SE0 Control Register                            */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE2[283];
    /// @endcond //HIDDEN_SYMBOLS
    USBD_EP_T     EP[12];                /*!< [0x500~0x5bc] USB End Point 0 ~ 11 Configuration Register                 */

} USBD_T;


/**
    @addtogroup USBD_CONST USBD Bit Field Definition
    Constant Definitions for USBD Controller
@{ */

#define USBD_INTEN_BUSIEN_Pos            (0)                                               /*!< USBD_T::INTEN: BUSIEN Position         */
#define USBD_INTEN_BUSIEN_Msk            (0x1ul << USBD_INTEN_BUSIEN_Pos)                  /*!< USBD_T::INTEN: BUSIEN Mask             */

#define USBD_INTEN_USBIEN_Pos            (1)                                               /*!< USBD_T::INTEN: USBIEN Position         */
#define USBD_INTEN_USBIEN_Msk            (0x1ul << USBD_INTEN_USBIEN_Pos)                  /*!< USBD_T::INTEN: USBIEN Mask             */

#define USBD_INTEN_VBDETIEN_Pos          (2)                                               /*!< USBD_T::INTEN: VBDETIEN Position       */
#define USBD_INTEN_VBDETIEN_Msk          (0x1ul << USBD_INTEN_VBDETIEN_Pos)                /*!< USBD_T::INTEN: VBDETIEN Mask           */

#define USBD_INTEN_NEVWKIEN_Pos          (3)                                               /*!< USBD_T::INTEN: NEVWKIEN Position       */
#define USBD_INTEN_NEVWKIEN_Msk          (0x1ul << USBD_INTEN_NEVWKIEN_Pos)                /*!< USBD_T::INTEN: NEVWKIEN Mask           */

#define USBD_INTEN_SOFIEN_Pos            (4)                                               /*!< USBD_T::INTEN: SOFIEN Position         */
#define USBD_INTEN_SOFIEN_Msk            (0x1ul << USBD_INTEN_SOFIEN_Pos)                  /*!< USBD_T::INTEN: SOFIEN Mask             */

#define USBD_INTEN_WKEN_Pos              (8)                                               /*!< USBD_T::INTEN: WKEN Position           */
#define USBD_INTEN_WKEN_Msk              (0x1ul << USBD_INTEN_WKEN_Pos)                    /*!< USBD_T::INTEN: WKEN Mask               */

#define USBD_INTEN_INNAKEN_Pos           (15)                                              /*!< USBD_T::INTEN: INNAKEN Position        */
#define USBD_INTEN_INNAKEN_Msk           (0x1ul << USBD_INTEN_INNAKEN_Pos)                 /*!< USBD_T::INTEN: INNAKEN Mask            */

#define USBD_INTSTS_BUSIF_Pos            (0)                                               /*!< USBD_T::INTSTS: BUSIF Position         */
#define USBD_INTSTS_BUSIF_Msk            (0x1ul << USBD_INTSTS_BUSIF_Pos)                  /*!< USBD_T::INTSTS: BUSIF Mask             */

#define USBD_INTSTS_USBIF_Pos            (1)                                               /*!< USBD_T::INTSTS: USBIF Position         */
#define USBD_INTSTS_USBIF_Msk            (0x1ul << USBD_INTSTS_USBIF_Pos)                  /*!< USBD_T::INTSTS: USBIF Mask             */

#define USBD_INTSTS_VBDETIF_Pos          (2)                                               /*!< USBD_T::INTSTS: VBDETIF Position       */
#define USBD_INTSTS_VBDETIF_Msk          (0x1ul << USBD_INTSTS_VBDETIF_Pos)                /*!< USBD_T::INTSTS: VBDETIF Mask           */

#define USBD_INTSTS_NEVWKIF_Pos          (3)                                               /*!< USBD_T::INTSTS: NEVWKIF Position       */
#define USBD_INTSTS_NEVWKIF_Msk          (0x1ul << USBD_INTSTS_NEVWKIF_Pos)                /*!< USBD_T::INTSTS: NEVWKIF Mask           */

#define USBD_INTSTS_SOFIF_Pos            (4)                                               /*!< USBD_T::INTSTS: SOFIF Position         */
#define USBD_INTSTS_SOFIF_Msk            (0x1ul << USBD_INTSTS_SOFIF_Pos)                  /*!< USBD_T::INTSTS: SOFIF Mask             */

#define USBD_INTSTS_EPEVT0_Pos           (16)                                              /*!< USBD_T::INTSTS: EPEVT0 Position        */
#define USBD_INTSTS_EPEVT0_Msk           (0x1ul << USBD_INTSTS_EPEVT0_Pos)                 /*!< USBD_T::INTSTS: EPEVT0 Mask            */

#define USBD_INTSTS_EPEVT1_Pos           (17)                                              /*!< USBD_T::INTSTS: EPEVT1 Position        */
#define USBD_INTSTS_EPEVT1_Msk           (0x1ul << USBD_INTSTS_EPEVT1_Pos)                 /*!< USBD_T::INTSTS: EPEVT1 Mask            */

#define USBD_INTSTS_EPEVT2_Pos           (18)                                              /*!< USBD_T::INTSTS: EPEVT2 Position        */
#define USBD_INTSTS_EPEVT2_Msk           (0x1ul << USBD_INTSTS_EPEVT2_Pos)                 /*!< USBD_T::INTSTS: EPEVT2 Mask            */

#define USBD_INTSTS_EPEVT3_Pos           (19)                                              /*!< USBD_T::INTSTS: EPEVT3 Position        */
#define USBD_INTSTS_EPEVT3_Msk           (0x1ul << USBD_INTSTS_EPEVT3_Pos)                 /*!< USBD_T::INTSTS: EPEVT3 Mask            */

#define USBD_INTSTS_EPEVT4_Pos           (20)                                              /*!< USBD_T::INTSTS: EPEVT4 Position        */
#define USBD_INTSTS_EPEVT4_Msk           (0x1ul << USBD_INTSTS_EPEVT4_Pos)                 /*!< USBD_T::INTSTS: EPEVT4 Mask            */

#define USBD_INTSTS_EPEVT5_Pos           (21)                                              /*!< USBD_T::INTSTS: EPEVT5 Position        */
#define USBD_INTSTS_EPEVT5_Msk           (0x1ul << USBD_INTSTS_EPEVT5_Pos)                 /*!< USBD_T::INTSTS: EPEVT5 Mask            */

#define USBD_INTSTS_EPEVT6_Pos           (22)                                              /*!< USBD_T::INTSTS: EPEVT6 Position        */
#define USBD_INTSTS_EPEVT6_Msk           (0x1ul << USBD_INTSTS_EPEVT6_Pos)                 /*!< USBD_T::INTSTS: EPEVT6 Mask            */

#define USBD_INTSTS_EPEVT7_Pos           (23)                                              /*!< USBD_T::INTSTS: EPEVT7 Position        */
#define USBD_INTSTS_EPEVT7_Msk           (0x1ul << USBD_INTSTS_EPEVT7_Pos)                 /*!< USBD_T::INTSTS: EPEVT7 Mask            */

#define USBD_INTSTS_EPEVT8_Pos           (24)                                              /*!< USBD_T::INTSTS: EPEVT8 Position        */
#define USBD_INTSTS_EPEVT8_Msk           (0x1ul << USBD_INTSTS_EPEVT8_Pos)                 /*!< USBD_T::INTSTS: EPEVT8 Mask            */

#define USBD_INTSTS_EPEVT9_Pos           (25)                                              /*!< USBD_T::INTSTS: EPEVT9 Position        */
#define USBD_INTSTS_EPEVT9_Msk           (0x1ul << USBD_INTSTS_EPEVT9_Pos)                 /*!< USBD_T::INTSTS: EPEVT9 Mask            */

#define USBD_INTSTS_EPEVT10_Pos          (26)                                              /*!< USBD_T::INTSTS: EPEVT10 Position       */
#define USBD_INTSTS_EPEVT10_Msk          (0x1ul << USBD_INTSTS_EPEVT10_Pos)                /*!< USBD_T::INTSTS: EPEVT10 Mask           */

#define USBD_INTSTS_EPEVT11_Pos          (27)                                              /*!< USBD_T::INTSTS: EPEVT11 Position       */
#define USBD_INTSTS_EPEVT11_Msk          (0x1ul << USBD_INTSTS_EPEVT11_Pos)                /*!< USBD_T::INTSTS: EPEVT11 Mask           */

#define USBD_INTSTS_SETUP_Pos            (31)                                              /*!< USBD_T::INTSTS: SETUP Position         */
#define USBD_INTSTS_SETUP_Msk            (0x1ul << USBD_INTSTS_SETUP_Pos)                  /*!< USBD_T::INTSTS: SETUP Mask             */

#define USBD_FADDR_FADDR_Pos             (0)                                               /*!< USBD_T::FADDR: FADDR Position          */
#define USBD_FADDR_FADDR_Msk             (0x7ful << USBD_FADDR_FADDR_Pos)                  /*!< USBD_T::FADDR: FADDR Mask              */

#define USBD_EPSTS_OV_Pos                (7)                                               /*!< USBD_T::EPSTS: OV Position             */
#define USBD_EPSTS_OV_Msk                (0x1ul << USBD_EPSTS_OV_Pos)                      /*!< USBD_T::EPSTS: OV Mask                 */

#define USBD_ATTR_USBRST_Pos             (0)                                               /*!< USBD_T::ATTR: USBRST Position          */
#define USBD_ATTR_USBRST_Msk             (0x1ul << USBD_ATTR_USBRST_Pos)                   /*!< USBD_T::ATTR: USBRST Mask              */

#define USBD_ATTR_SUSPEND_Pos            (1)                                               /*!< USBD_T::ATTR: SUSPEND Position         */
#define USBD_ATTR_SUSPEND_Msk            (0x1ul << USBD_ATTR_SUSPEND_Pos)                  /*!< USBD_T::ATTR: SUSPEND Mask             */

#define USBD_ATTR_RESUME_Pos             (2)                                               /*!< USBD_T::ATTR: RESUME Position          */
#define USBD_ATTR_RESUME_Msk             (0x1ul << USBD_ATTR_RESUME_Pos)                   /*!< USBD_T::ATTR: RESUME Mask              */

#define USBD_ATTR_TOUT_Pos               (3)                                               /*!< USBD_T::ATTR: TOUT Position            */
#define USBD_ATTR_TOUT_Msk               (0x1ul << USBD_ATTR_TOUT_Pos)                     /*!< USBD_T::ATTR: TOUT Mask                */

#define USBD_ATTR_PHYEN_Pos              (4)                                               /*!< USBD_T::ATTR: PHYEN Position           */
#define USBD_ATTR_PHYEN_Msk              (0x1ul << USBD_ATTR_PHYEN_Pos)                    /*!< USBD_T::ATTR: PHYEN Mask               */

#define USBD_ATTR_RWAKEUP_Pos            (5)                                               /*!< USBD_T::ATTR: RWAKEUP Position         */
#define USBD_ATTR_RWAKEUP_Msk            (0x1ul << USBD_ATTR_RWAKEUP_Pos)                  /*!< USBD_T::ATTR: RWAKEUP Mask             */

#define USBD_ATTR_USBEN_Pos              (7)                                               /*!< USBD_T::ATTR: USBEN Position           */
#define USBD_ATTR_USBEN_Msk              (0x1ul << USBD_ATTR_USBEN_Pos)                    /*!< USBD_T::ATTR: USBEN Mask               */

#define USBD_ATTR_DPPUEN_Pos             (8)                                               /*!< USBD_T::ATTR: DPPUEN Position          */
#define USBD_ATTR_DPPUEN_Msk             (0x1ul << USBD_ATTR_DPPUEN_Pos)                   /*!< USBD_T::ATTR: DPPUEN Mask              */

#define USBD_ATTR_BYTEM_Pos              (10)                                              /*!< USBD_T::ATTR: BYTEM Position           */
#define USBD_ATTR_BYTEM_Msk              (0x1ul << USBD_ATTR_BYTEM_Pos)                    /*!< USBD_T::ATTR: BYTEM Mask               */

#define USBD_ATTR_LPMACK_Pos             (11)                                              /*!< USBD_T::ATTR: LPMACK Position          */
#define USBD_ATTR_LPMACK_Msk             (0x1ul << USBD_ATTR_LPMACK_Pos)                   /*!< USBD_T::ATTR: LPMACK Mask              */

#define USBD_ATTR_L1SUSPEND_Pos          (12)                                              /*!< USBD_T::ATTR: L1SUSPEND Position       */
#define USBD_ATTR_L1SUSPEND_Msk          (0x1ul << USBD_ATTR_L1SUSPEND_Pos)                /*!< USBD_T::ATTR: L1SUSPEND Mask           */

#define USBD_ATTR_L1RESUME_Pos           (13)                                              /*!< USBD_T::ATTR: L1RESUME Position        */
#define USBD_ATTR_L1RESUME_Msk           (0x1ul << USBD_ATTR_L1RESUME_Pos)                 /*!< USBD_T::ATTR: L1RESUME Mask            */

#define USBD_VBUSDET_VBUSDET_Pos         (0)                                               /*!< USBD_T::VBUSDET: VBUSDET Position      */
#define USBD_VBUSDET_VBUSDET_Msk         (0x1ul << USBD_VBUSDET_VBUSDET_Pos)               /*!< USBD_T::VBUSDET: VBUSDET Mask          */

#define USBD_STBUFSEG_STBUFSEG_Pos       (3)                                               /*!< USBD_T::STBUFSEG: STBUFSEG Position    */
#define USBD_STBUFSEG_STBUFSEG_Msk       (0x3ful << USBD_STBUFSEG_STBUFSEG_Pos)            /*!< USBD_T::STBUFSEG: STBUFSEG Mask        */

#define USBD_EPSTS0_EPSTS0_Pos           (0)                                               /*!< USBD_T::EPSTS0: EPSTS0 Position        */
#define USBD_EPSTS0_EPSTS0_Msk           (0xful << USBD_EPSTS0_EPSTS0_Pos)                 /*!< USBD_T::EPSTS0: EPSTS0 Mask            */

#define USBD_EPSTS0_EPSTS1_Pos           (4)                                               /*!< USBD_T::EPSTS0: EPSTS1 Position        */
#define USBD_EPSTS0_EPSTS1_Msk           (0xful << USBD_EPSTS0_EPSTS1_Pos)                 /*!< USBD_T::EPSTS0: EPSTS1 Mask            */

#define USBD_EPSTS0_EPSTS2_Pos           (8)                                               /*!< USBD_T::EPSTS0: EPSTS2 Position        */
#define USBD_EPSTS0_EPSTS2_Msk           (0xful << USBD_EPSTS0_EPSTS2_Pos)                 /*!< USBD_T::EPSTS0: EPSTS2 Mask            */

#define USBD_EPSTS0_EPSTS3_Pos           (12)                                              /*!< USBD_T::EPSTS0: EPSTS3 Position        */
#define USBD_EPSTS0_EPSTS3_Msk           (0xful << USBD_EPSTS0_EPSTS3_Pos)                 /*!< USBD_T::EPSTS0: EPSTS3 Mask            */

#define USBD_EPSTS0_EPSTS4_Pos           (16)                                              /*!< USBD_T::EPSTS0: EPSTS4 Position        */
#define USBD_EPSTS0_EPSTS4_Msk           (0xful << USBD_EPSTS0_EPSTS4_Pos)                 /*!< USBD_T::EPSTS0: EPSTS4 Mask            */

#define USBD_EPSTS0_EPSTS5_Pos           (20)                                              /*!< USBD_T::EPSTS0: EPSTS5 Position        */
#define USBD_EPSTS0_EPSTS5_Msk           (0xful << USBD_EPSTS0_EPSTS5_Pos)                 /*!< USBD_T::EPSTS0: EPSTS5 Mask            */

#define USBD_EPSTS0_EPSTS6_Pos           (24)                                              /*!< USBD_T::EPSTS0: EPSTS6 Position        */
#define USBD_EPSTS0_EPSTS6_Msk           (0xful << USBD_EPSTS0_EPSTS6_Pos)                 /*!< USBD_T::EPSTS0: EPSTS6 Mask            */

#define USBD_EPSTS0_EPSTS7_Pos           (28)                                              /*!< USBD_T::EPSTS0: EPSTS7 Position        */
#define USBD_EPSTS0_EPSTS7_Msk           (0xful << USBD_EPSTS0_EPSTS7_Pos)                 /*!< USBD_T::EPSTS0: EPSTS7 Mask            */

#define USBD_EPSTS1_EPSTS8_Pos           (0)                                               /*!< USBD_T::EPSTS1: EPSTS8 Position        */
#define USBD_EPSTS1_EPSTS8_Msk           (0xful << USBD_EPSTS1_EPSTS8_Pos)                 /*!< USBD_T::EPSTS1: EPSTS8 Mask            */

#define USBD_EPSTS1_EPSTS9_Pos           (4)                                               /*!< USBD_T::EPSTS1: EPSTS9 Position        */
#define USBD_EPSTS1_EPSTS9_Msk           (0xful << USBD_EPSTS1_EPSTS9_Pos)                 /*!< USBD_T::EPSTS1: EPSTS9 Mask            */

#define USBD_EPSTS1_EPSTS10_Pos          (8)                                               /*!< USBD_T::EPSTS1: EPSTS10 Position       */
#define USBD_EPSTS1_EPSTS10_Msk          (0xful << USBD_EPSTS1_EPSTS10_Pos)                /*!< USBD_T::EPSTS1: EPSTS10 Mask           */

#define USBD_EPSTS1_EPSTS11_Pos          (12)                                              /*!< USBD_T::EPSTS1: EPSTS11 Position       */
#define USBD_EPSTS1_EPSTS11_Msk          (0xful << USBD_EPSTS1_EPSTS11_Pos)                /*!< USBD_T::EPSTS1: EPSTS11 Mask           */

#define USBD_LPMATTR_LPMLINKSTS_Pos      (0)                                               /*!< USBD_T::LPMATTR: LPMLINKSTS Position   */
#define USBD_LPMATTR_LPMLINKSTS_Msk      (0xful << USBD_LPMATTR_LPMLINKSTS_Pos)            /*!< USBD_T::LPMATTR: LPMLINKSTS Mask       */

#define USBD_LPMATTR_LPMBESL_Pos         (4)                                               /*!< USBD_T::LPMATTR: LPMBESL Position      */
#define USBD_LPMATTR_LPMBESL_Msk         (0xful << USBD_LPMATTR_LPMBESL_Pos)               /*!< USBD_T::LPMATTR: LPMBESL Mask          */

#define USBD_LPMATTR_LPMRWAKUP_Pos       (8)                                               /*!< USBD_T::LPMATTR: LPMRWAKUP Position    */
#define USBD_LPMATTR_LPMRWAKUP_Msk       (0x1ul << USBD_LPMATTR_LPMRWAKUP_Pos)             /*!< USBD_T::LPMATTR: LPMRWAKUP Mask        */

#define USBD_FN_FN_Pos                   (0)                                               /*!< USBD_T::FN: FN Position                */
#define USBD_FN_FN_Msk                   (0x7fful << USBD_FN_FN_Pos)                       /*!< USBD_T::FN: FN Mask                    */

#define USBD_SE0_SE0_Pos                 (0)                                               /*!< USBD_T::SE0: SE0 Position              */
#define USBD_SE0_SE0_Msk                 (0x1ul << USBD_SE0_SE0_Pos)                       /*!< USBD_T::SE0: SE0 Mask                  */

#define USBD_BUFSEG_BUFSEG_Pos           (3)                                               /*!< USBD_EP_T::BUFSEG: BUFSEG Position     */
#define USBD_BUFSEG_BUFSEG_Msk           (0x3ful << USBD_BUFSEG_BUFSEG_Pos)                /*!< USBD_EP_T::BUFSEG: BUFSEG Mask         */

#define USBD_MXPLD_MXPLD_Pos             (0)                                               /*!< USBD_EP_T::MXPLD: MXPLD Position       */
#define USBD_MXPLD_MXPLD_Msk             (0x1fful << USBD_MXPLD_MXPLD_Pos)                 /*!< USBD_EP_T::MXPLD: MXPLD Mask           */

#define USBD_CFG_EPNUM_Pos               (0)                                               /*!< USBD_EP_T::CFG: EPNUM Position         */
#define USBD_CFG_EPNUM_Msk               (0xful << USBD_CFG_EPNUM_Pos)                     /*!< USBD_EP_T::CFG: EPNUM Mask             */

#define USBD_CFG_ISOCH_Pos               (4)                                               /*!< USBD_EP_T::CFG: ISOCH Position         */
#define USBD_CFG_ISOCH_Msk               (0x1ul << USBD_CFG_ISOCH_Pos)                     /*!< USBD_EP_T::CFG: ISOCH Mask             */

#define USBD_CFG_STATE_Pos               (5)                                               /*!< USBD_EP_T::CFG: STATE Position         */
#define USBD_CFG_STATE_Msk               (0x3ul << USBD_CFG_STATE_Pos)                     /*!< USBD_EP_T::CFG: STATE Mask             */

#define USBD_CFG_DSQSYNC_Pos             (7)                                               /*!< USBD_EP_T::CFG: DSQSYNC Position       */
#define USBD_CFG_DSQSYNC_Msk             (0x1ul << USBD_CFG_DSQSYNC_Pos)                   /*!< USBD_EP_T::CFG: DSQSYNC Mask           */

#define USBD_CFG_CSTALL_Pos              (9)                                               /*!< USBD_EP_T::CFG: CSTALL Position        */
#define USBD_CFG_CSTALL_Msk              (0x1ul << USBD_CFG_CSTALL_Pos)                    /*!< USBD_EP_T::CFG: CSTALL Mask            */

#define USBD_CFGP_CLRRDY_Pos             (0)                                               /*!< USBD_EP_T::CFGP: CLRRDY Position       */
#define USBD_CFGP_CLRRDY_Msk             (0x1ul << USBD_CFGP_CLRRDY_Pos)                   /*!< USBD_EP_T::CFGP: CLRRDY Mask           */

#define USBD_CFGP_SSTALL_Pos             (1)                                               /*!< USBD_EP_T::CFGP: SSTALL Position       */
#define USBD_CFGP_SSTALL_Msk             (0x1ul << USBD_CFGP_SSTALL_Pos)                   /*!< USBD_EP_T::CFGP: SSTALL Mask           */

/**@}*/ /* USBD_CONST */
/**@}*/ /* end of USBD register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __USBD_REG_H__ */
