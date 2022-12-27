/**************************************************************************//**
 * @file     emac_reg.h
 * @version  V1.00
 * @brief    EMAC register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __EMAC_REG_H__
#define __EMAC_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup EMAC Ethernet MAC Controller(EMAC)
    Memory Mapped Structure for EMAC Controller
@{ */

typedef struct
{

    /**
@var EMAC_T::CAMCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAMCTL
</font><br><p> <font size="2">
Offset: 0x00  CAM Comparison Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>AUP</td><td><div style="word-wrap: break-word;"><b>Accept Unicast Packet
</b><br>
The AUP controls the unicast packet reception
<br>
If AUP is enabled, EMAC receives all incoming packet its destination MAC address is a unicast address.
<br>
0 = EMAC receives packet depends on the CAM comparison result.
<br>
1 = EMAC receives all unicast packets.
<br>
</div></td></tr><tr><td>
[1]</td><td>AMP</td><td><div style="word-wrap: break-word;"><b>Accept Multicast Packet
</b><br>
The AMP controls the multicast packet reception
<br>
If AMP is enabled, EMAC receives all incoming packet its destination MAC address is a multicast address.
<br>
0 = EMAC receives packet depends on the CAM comparison result.
<br>
1 = EMAC receives all multicast packets.
<br>
</div></td></tr><tr><td>
[2]</td><td>ABP</td><td><div style="word-wrap: break-word;"><b>Accept Broadcast Packet
</b><br>
The ABP controls the broadcast packet reception
<br>
If ABP is enabled, EMAC receives all incoming packet its destination MAC address is a broadcast address.
<br>
0 = EMAC receives packet depends on the CAM comparison result.
<br>
1 = EMAC receives all broadcast packets.
<br>
</div></td></tr><tr><td>
[3]</td><td>COMPEN</td><td><div style="word-wrap: break-word;"><b>Complement CAM Comparison Enable Bit
</b><br>
The COMPEN controls the complement of the CAM comparison result
<br>
If the CMPEN and COMPEN are both enabled, the incoming packet with specific destination MAC address
<br>
configured in CAM entry will be dropped
<br>
And the incoming packet with destination MAC address does not configured in any CAM entry will be received.
<br>
0 = Complement CAM comparison result Disabled.
<br>
1 = Complement CAM comparison result Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>CMPEN</td><td><div style="word-wrap: break-word;"><b>CAM Compare Enable Bit
</b><br>
The CMPEN controls the enable of CAM comparison function for destination MAC address recognition
<br>
If software wants to receive a packet with specific destination MAC address, configures the MAC address
<br>
into CAM 12~0, then enables that CAM entry and set CMPEN to 1.
<br>
0 = CAM comparison function for destination MAC address recognition Disabled.
<br>
1 = CAM comparison function for destination MAC address recognition Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAMEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAMEN
</font><br><p> <font size="2">
Offset: 0x04  CAM Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CAMxEN</td><td><div style="word-wrap: break-word;"><b>CAM Entry X Enable Bit
</b><br>
The CAMxEN controls the validation of CAM entry x.
<br>
The CAM entry 13, 14 and 15 are for PAUSE control frame transmission
<br>
If software wants to transmit a PAUSE control frame out to network, the enable bits of these three CAM
<br>
entries all must be enabled first.
<br>
0 = CAM entry x Disabled.
<br>
1 = CAM entry x Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM0M

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM0M
</font><br><p> <font size="2">
Offset: 0x08  CAM0 Most Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>MACADDR2</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 2
</b><br>
</div></td></tr><tr><td>
[15:8]</td><td>MACADDR3</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 3
</b><br>
</div></td></tr><tr><td>
[23:16]</td><td>MACADDR4</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 4
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR5</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 5
</b><br>
The CAMxM keeps the bit 47~16 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM0L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM0L
</font><br><p> <font size="2">
Offset: 0x0C  CAM0 Least Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:16]</td><td>MACADDR0</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 0
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR1</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 1
</b><br>
The CAMxL keeps the bit 15~0 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM1M

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM1M
</font><br><p> <font size="2">
Offset: 0x10  CAM1 Most Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>MACADDR2</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 2
</b><br>
</div></td></tr><tr><td>
[15:8]</td><td>MACADDR3</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 3
</b><br>
</div></td></tr><tr><td>
[23:16]</td><td>MACADDR4</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 4
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR5</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 5
</b><br>
The CAMxM keeps the bit 47~16 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM1L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM1L
</font><br><p> <font size="2">
Offset: 0x14  CAM1 Least Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:16]</td><td>MACADDR0</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 0
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR1</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 1
</b><br>
The CAMxL keeps the bit 15~0 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM2M

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM2M
</font><br><p> <font size="2">
Offset: 0x18  CAM2 Most Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>MACADDR2</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 2
</b><br>
</div></td></tr><tr><td>
[15:8]</td><td>MACADDR3</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 3
</b><br>
</div></td></tr><tr><td>
[23:16]</td><td>MACADDR4</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 4
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR5</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 5
</b><br>
The CAMxM keeps the bit 47~16 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM2L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM2L
</font><br><p> <font size="2">
Offset: 0x1C  CAM2 Least Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:16]</td><td>MACADDR0</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 0
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR1</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 1
</b><br>
The CAMxL keeps the bit 15~0 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM3M

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM3M
</font><br><p> <font size="2">
Offset: 0x20  CAM3 Most Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>MACADDR2</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 2
</b><br>
</div></td></tr><tr><td>
[15:8]</td><td>MACADDR3</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 3
</b><br>
</div></td></tr><tr><td>
[23:16]</td><td>MACADDR4</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 4
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR5</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 5
</b><br>
The CAMxM keeps the bit 47~16 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM3L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM3L
</font><br><p> <font size="2">
Offset: 0x24  CAM3 Least Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:16]</td><td>MACADDR0</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 0
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR1</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 1
</b><br>
The CAMxL keeps the bit 15~0 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM4M

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM4M
</font><br><p> <font size="2">
Offset: 0x28  CAM4 Most Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>MACADDR2</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 2
</b><br>
</div></td></tr><tr><td>
[15:8]</td><td>MACADDR3</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 3
</b><br>
</div></td></tr><tr><td>
[23:16]</td><td>MACADDR4</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 4
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR5</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 5
</b><br>
The CAMxM keeps the bit 47~16 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM4L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM4L
</font><br><p> <font size="2">
Offset: 0x2C  CAM4 Least Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:16]</td><td>MACADDR0</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 0
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR1</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 1
</b><br>
The CAMxL keeps the bit 15~0 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM5M

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM5M
</font><br><p> <font size="2">
Offset: 0x30  CAM5 Most Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>MACADDR2</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 2
</b><br>
</div></td></tr><tr><td>
[15:8]</td><td>MACADDR3</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 3
</b><br>
</div></td></tr><tr><td>
[23:16]</td><td>MACADDR4</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 4
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR5</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 5
</b><br>
The CAMxM keeps the bit 47~16 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM5L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM5L
</font><br><p> <font size="2">
Offset: 0x34  CAM5 Least Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:16]</td><td>MACADDR0</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 0
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR1</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 1
</b><br>
The CAMxL keeps the bit 15~0 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM6M

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM6M
</font><br><p> <font size="2">
Offset: 0x38  CAM6 Most Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>MACADDR2</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 2
</b><br>
</div></td></tr><tr><td>
[15:8]</td><td>MACADDR3</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 3
</b><br>
</div></td></tr><tr><td>
[23:16]</td><td>MACADDR4</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 4
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR5</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 5
</b><br>
The CAMxM keeps the bit 47~16 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM6L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM6L
</font><br><p> <font size="2">
Offset: 0x3C  CAM6 Least Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:16]</td><td>MACADDR0</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 0
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR1</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 1
</b><br>
The CAMxL keeps the bit 15~0 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM7M

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM7M
</font><br><p> <font size="2">
Offset: 0x40  CAM7 Most Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>MACADDR2</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 2
</b><br>
</div></td></tr><tr><td>
[15:8]</td><td>MACADDR3</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 3
</b><br>
</div></td></tr><tr><td>
[23:16]</td><td>MACADDR4</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 4
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR5</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 5
</b><br>
The CAMxM keeps the bit 47~16 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM7L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM7L
</font><br><p> <font size="2">
Offset: 0x44  CAM7 Least Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:16]</td><td>MACADDR0</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 0
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR1</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 1
</b><br>
The CAMxL keeps the bit 15~0 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM8M

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM8M
</font><br><p> <font size="2">
Offset: 0x48  CAM8 Most Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>MACADDR2</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 2
</b><br>
</div></td></tr><tr><td>
[15:8]</td><td>MACADDR3</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 3
</b><br>
</div></td></tr><tr><td>
[23:16]</td><td>MACADDR4</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 4
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR5</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 5
</b><br>
The CAMxM keeps the bit 47~16 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM8L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM8L
</font><br><p> <font size="2">
Offset: 0x4C  CAM8 Least Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:16]</td><td>MACADDR0</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 0
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR1</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 1
</b><br>
The CAMxL keeps the bit 15~0 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM9M

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM9M
</font><br><p> <font size="2">
Offset: 0x50  CAM9 Most Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>MACADDR2</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 2
</b><br>
</div></td></tr><tr><td>
[15:8]</td><td>MACADDR3</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 3
</b><br>
</div></td></tr><tr><td>
[23:16]</td><td>MACADDR4</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 4
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR5</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 5
</b><br>
The CAMxM keeps the bit 47~16 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM9L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM9L
</font><br><p> <font size="2">
Offset: 0x54  CAM9 Least Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:16]</td><td>MACADDR0</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 0
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR1</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 1
</b><br>
The CAMxL keeps the bit 15~0 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM10M

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM10M
</font><br><p> <font size="2">
Offset: 0x58  CAM10 Most Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>MACADDR2</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 2
</b><br>
</div></td></tr><tr><td>
[15:8]</td><td>MACADDR3</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 3
</b><br>
</div></td></tr><tr><td>
[23:16]</td><td>MACADDR4</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 4
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR5</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 5
</b><br>
The CAMxM keeps the bit 47~16 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM10L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM10L
</font><br><p> <font size="2">
Offset: 0x5C  CAM10 Least Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:16]</td><td>MACADDR0</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 0
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR1</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 1
</b><br>
The CAMxL keeps the bit 15~0 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM11M

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM11M
</font><br><p> <font size="2">
Offset: 0x60  CAM11 Most Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>MACADDR2</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 2
</b><br>
</div></td></tr><tr><td>
[15:8]</td><td>MACADDR3</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 3
</b><br>
</div></td></tr><tr><td>
[23:16]</td><td>MACADDR4</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 4
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR5</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 5
</b><br>
The CAMxM keeps the bit 47~16 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM11L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM11L
</font><br><p> <font size="2">
Offset: 0x64  CAM11 Least Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:16]</td><td>MACADDR0</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 0
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR1</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 1
</b><br>
The CAMxL keeps the bit 15~0 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM12M

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM12M
</font><br><p> <font size="2">
Offset: 0x68  CAM12 Most Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>MACADDR2</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 2
</b><br>
</div></td></tr><tr><td>
[15:8]</td><td>MACADDR3</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 3
</b><br>
</div></td></tr><tr><td>
[23:16]</td><td>MACADDR4</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 4
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR5</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 5
</b><br>
The CAMxM keeps the bit 47~16 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM12L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM12L
</font><br><p> <font size="2">
Offset: 0x6C  CAM12 Least Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:16]</td><td>MACADDR0</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 0
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR1</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 1
</b><br>
The CAMxL keeps the bit 15~0 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM13M

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM13M
</font><br><p> <font size="2">
Offset: 0x70  CAM13 Most Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>MACADDR2</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 2
</b><br>
</div></td></tr><tr><td>
[15:8]</td><td>MACADDR3</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 3
</b><br>
</div></td></tr><tr><td>
[23:16]</td><td>MACADDR4</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 4
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR5</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 5
</b><br>
The CAMxM keeps the bit 47~16 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM13L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM13L
</font><br><p> <font size="2">
Offset: 0x74  CAM13 Least Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:16]</td><td>MACADDR0</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 0
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR1</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 1
</b><br>
The CAMxL keeps the bit 15~0 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM14M

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM14M
</font><br><p> <font size="2">
Offset: 0x78  CAM14 Most Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>MACADDR2</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 2
</b><br>
</div></td></tr><tr><td>
[15:8]</td><td>MACADDR3</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 3
</b><br>
</div></td></tr><tr><td>
[23:16]</td><td>MACADDR4</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 4
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR5</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 5
</b><br>
The CAMxM keeps the bit 47~16 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM14L

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM14L
</font><br><p> <font size="2">
Offset: 0x7C  CAM14 Least Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:16]</td><td>MACADDR0</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 0
</b><br>
</div></td></tr><tr><td>
[31:24]</td><td>MACADDR1</td><td><div style="word-wrap: break-word;"><b>MAC Address Byte 1
</b><br>
The CAMxL keeps the bit 15~0 of MAC address
<br>
The x can be the 0~14
<br>
The register pair {EMAC_CAMxM, EMAC_CAMxL} represents a CAM entry and keeps a MAC address.
<br>
For example, if the MAC address 00-50-BA-33-BA-44 kept in CAM entry 1, the register EMAC_CAM1M is
<br>
0x0050_BA33 and EMAC_CAM1L is 0xBA44_0000.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM15MSB

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM15MSB
</font><br><p> <font size="2">
Offset: 0x80  CAM15 Most Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>OPCODE</td><td><div style="word-wrap: break-word;"><b>OP Code Field of PAUSE Control Frame
</b><br>
In the PAUSE control frame, an op code field defined and is 0x0001.
<br>
</div></td></tr><tr><td>
[31:16]</td><td>LENGTH</td><td><div style="word-wrap: break-word;"><b>LENGTH Field of PAUSE Control Frame
</b><br>
In the PAUSE control frame, a LENGTH field defined and is 0x8808.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CAM15LSB

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CAM15LSB
</font><br><p> <font size="2">
Offset: 0x84  CAM15 Least Significant Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:24]</td><td>OPERAND</td><td><div style="word-wrap: break-word;"><b>Pause Parameter
</b><br>
In the PAUSE control frame, an OPERAND field defined and controls how much time the destination
<br>
Ethernet MAC Controller paused
<br>
The unit of the OPERAND is a slot time, the 512-bit time.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::TXDSA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TXDSA
</font><br><p> <font size="2">
Offset: 0x88  Transmit Descriptor Link List Start Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>TXDSA</td><td><div style="word-wrap: break-word;"><b>Transmit Descriptor Link-list Start Address
</b><br>
The TXDSA keeps the start address of transmit descriptor link-list
<br>
If the software enables the bit TXON (EMAC_CTL[8]), the content of TXDSA will be loaded into the
<br>
current transmit descriptor start address register (EMAC_CTXDSA)
<br>
The TXDSA does not be updated by EMAC
<br>
During the operation, EMAC will ignore the bits [1:0] of TXDSA
<br>
This means that TX descriptors must locate at word boundary memory address.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::RXDSA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">RXDSA
</font><br><p> <font size="2">
Offset: 0x8C  Receive Descriptor Link List Start Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>RXDSA</td><td><div style="word-wrap: break-word;"><b>Receive Descriptor Link-list Start Address
</b><br>
The RXDSA keeps the start address of receive descriptor link-list
<br>
If the S/W enables the bit RXON (EMAC_CTL[0]), the content of RXDSA will be loaded into the current
<br>
receive descriptor start address register (EMAC_CRXDSA)
<br>
The RXDSA does not be updated by EMAC
<br>
During the operation, EMAC will ignore the bits [1:0] of RXDSA
<br>
This means that RX descriptors must locate at word boundary memory address.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL
</font><br><p> <font size="2">
Offset: 0x90  MAC Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>RXON</td><td><div style="word-wrap: break-word;"><b>Frame Reception ON
</b><br>
The RXON controls the normal packet reception of EMAC
<br>
If the RXON is set to high, the EMAC starts the packet reception process, including the RX
<br>
descriptor fetching, packet reception and RX descriptor modification.
<br>
It is necessary to finish EMAC initial sequence before enable RXON
<br>
Otherwise, the EMAC operation is undefined.
<br>
If the RXON is disabled during EMAC is receiving an incoming packet, the EMAC stops the packet
<br>
reception process after the current packet reception finished.
<br>
0 = Packet reception process stopped.
<br>
1 = Packet reception process started.
<br>
</div></td></tr><tr><td>
[1]</td><td>ALP</td><td><div style="word-wrap: break-word;"><b>Accept Long Packet
</b><br>
The ALP controls the long packet, which packet length is greater than 1518 bytes, reception
<br>
If the ALP is set to high, the EMAC will accept the long packet.
<br>
Otherwise, the long packet will be dropped.
<br>
0 = Ethernet MAC controller dropped the long packet.
<br>
1 = Ethernet MAC controller received the long packet.
<br>
</div></td></tr><tr><td>
[2]</td><td>ARP</td><td><div style="word-wrap: break-word;"><b>Accept Runt Packet
</b><br>
The ARP controls the runt packet, which length is less than 64 bytes, reception
<br>
If the ARP is set to high, the EMAC will accept the runt packet.
<br>
Otherwise, the runt packet will be dropped.
<br>
0 = Ethernet MAC controller dropped the runt packet.
<br>
1 = Ethernet MAC controller received the runt packet.
<br>
</div></td></tr><tr><td>
[3]</td><td>ACP</td><td><div style="word-wrap: break-word;"><b>Accept Control Packet
</b><br>
The ACP controls the control frame reception
<br>
If the ACP is set to high, the EMAC will accept the control frame
<br>
Otherwise, the control frame will be dropped
<br>
It is recommended that S/W only enable ACP while EMAC is operating on full duplex mode.
<br>
0 = Ethernet MAC controller dropped the control frame.
<br>
1 = Ethernet MAC controller received the control frame.
<br>
</div></td></tr><tr><td>
[4]</td><td>AEP</td><td><div style="word-wrap: break-word;"><b>Accept CRC Error Packet
</b><br>
The AEP controls the EMAC accepts or drops the CRC error packet
<br>
If the AEP is set to high, the incoming packet with CRC error will be received by EMAC as a good packet.
<br>
0 = Ethernet MAC controller dropped the CRC error packet.
<br>
1 = Ethernet MAC controller received the CRC error packet.
<br>
</div></td></tr><tr><td>
[5]</td><td>STRIPCRC</td><td><div style="word-wrap: break-word;"><b>Strip CRC Checksum
</b><br>
The STRIPCRC controls if the length of incoming packet is calculated with 4 bytes CRC checksum
<br>
If the STRIPCRC is set to high, 4 bytes CRC checksum is excluded from length calculation of incoming packet.
<br>
0 = The 4 bytes CRC checksum is included in packet length calculation.
<br>
1 = The 4 bytes CRC checksum is excluded in packet length calculation.
<br>
</div></td></tr><tr><td>
[6]</td><td>WOLEN</td><td><div style="word-wrap: break-word;"><b>Wake on LAN Enable Bit
</b><br>
The WOLEN high enables the functionality that Ethernet MAC controller checked if the incoming packet
<br>
is Magic Packet and wakeup system from Power-down mode.
<br>
If incoming packet was a Magic Packet and the system was in Power-down, the Ethernet MAC controller
<br>
would generate a wakeup event to wake system up from Power-down mode.
<br>
0 = Wake-up by Magic Packet function Disabled.
<br>
1 = Wake-up by Magic Packet function Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>TXON</td><td><div style="word-wrap: break-word;"><b>Frame Transmission ON
</b><br>
The TXON controls the normal packet transmission of EMAC
<br>
If the TXON is set to high, the EMAC starts the packet transmission process, including the TX
<br>
descriptor fetching, packet transmission and TX descriptor modification.
<br>
It is must to finish EMAC initial sequence before enable TXON
<br>
Otherwise, the EMAC operation is undefined.
<br>
If the TXON is disabled during EMAC is transmitting a packet out, the EMAC stops the packet
<br>
transmission process after the current packet transmission finished.
<br>
0 = Packet transmission process stopped.
<br>
1 = Packet transmission process started.
<br>
</div></td></tr><tr><td>
[9]</td><td>NODEF</td><td><div style="word-wrap: break-word;"><b>No Deferral
</b><br>
The NODEF controls the enable of deferral exceed counter
<br>
If NODEF is set to high, the deferral exceed counter is disabled
<br>
The NODEF is only useful while EMAC is operating on half duplex mode.
<br>
0 = The deferral exceed counter Enabled.
<br>
1 = The deferral exceed counter Disabled.
<br>
</div></td></tr><tr><td>
[16]</td><td>SDPZ</td><td><div style="word-wrap: break-word;"><b>Send PAUSE Frame
</b><br>
The SDPZ controls the PAUSE control frame transmission.
<br>
If S/W wants to send a PAUSE control frame out, the CAM entry 13, 14 and 15 must be configured
<br>
first and the corresponding CAM enable bit of CAMEN register also must be set.
<br>
Then, set SDPZ to 1 enables the PAUSE control frame transmission.
<br>
The SDPZ is a self-clear bit
<br>
This means after the PAUSE control frame transmission has completed, the SDPZ will be cleared automatically.
<br>
It is recommended that only enabling SNDPAUSE while EMAC is operating in Full Duplex mode.
<br>
0 = PAUSE control frame transmission completed.
<br>
1 = PAUSE control frame transmission Enabled.
<br>
</div></td></tr><tr><td>
[17]</td><td>SQECHKEN</td><td><div style="word-wrap: break-word;"><b>SQE Checking Enable Bit
</b><br>
The SQECHKEN controls the enable of SQE checking
<br>
The SQE checking is only available while EMAC is operating on 10M bps and half duplex mode
<br>
In other words, the SQECHKEN cannot affect EMAC operation, if the EMAC is operating on 100Mbps
<br>
or full duplex mode.
<br>
0 = SQE checking Disabled while EMAC is operating in 10Mbps and Half Duplex mode.
<br>
1 = SQE checking Enabled while EMAC is operating in 10Mbps and Half Duplex mode.
<br>
</div></td></tr><tr><td>
[18]</td><td>FUDUP</td><td><div style="word-wrap: break-word;"><b>Full Duplex Mode Selection
</b><br>
The FUDUP controls that if EMAC is operating on full or half duplex mode.
<br>
0 = EMAC operates in half duplex mode.
<br>
1 = EMAC operates in full duplex mode.
<br>
</div></td></tr><tr><td>
[19]</td><td>RMIIRXCTL</td><td><div style="word-wrap: break-word;"><b>RMII RX Control
</b><br>
The RMIIRXCTL control the receive data sample in RMII mode
<br>
It's necessary to set this bit high when RMIIEN (EMAC_CTL[ [22]) is high.
<br>
0 = RMII RX control disabled.
<br>
1 = RMII RX control enabled.
<br>
</div></td></tr><tr><td>
[20]</td><td>OPMODE</td><td><div style="word-wrap: break-word;"><b>Operation Mode Selection
</b><br>
The OPMODE defines that if the EMAC is operating on 10M or 100M bps mode
<br>
The RST (EMAC_CTL[24]) would not affect OPMODE value.
<br>
0 = EMAC operates in 10Mbps mode.
<br>
1 = EMAC operates in 100Mbps mode.
<br>
</div></td></tr><tr><td>
[22]</td><td>RMIIEN</td><td><div style="word-wrap: break-word;"><b>RMII Mode Enable Bit
</b><br>
This bit controls if Ethernet MAC controller connected with off-chip Ethernet PHY by MII
<br>
interface or RMII interface
<br>
The RST (EMAC_CTL[24]) would not affect RMIIEN value.
<br>
0 = Ethernet MAC controller RMII mode Disabled.
<br>
1 = Ethernet MAC controller RMII mode Enabled.
<br>
NOTE: This field must keep 1.
<br>
</div></td></tr><tr><td>
[24]</td><td>RST</td><td><div style="word-wrap: break-word;"><b>Software Reset
</b><br>
The RST implements a reset function to make the EMAC return default state
<br>
The RST is a self-clear bit
<br>
This means after the software reset finished, the RST will be cleared automatically
<br>
Enable RST can also reset all control and status registers, exclusive of the control bits
<br>
RMIIEN (EMAC_CTL[22]), and OPMODE (EMAC_CTL[20]).
<br>
The EMAC re-initial is necessary after the software reset completed.
<br>
0 = Software reset completed.
<br>
1 = Software reset Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::MIIMDAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MIIMDAT
</font><br><p> <font size="2">
Offset: 0x94  MII Management Data Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>DATA</td><td><div style="word-wrap: break-word;"><b>MII Management Data
</b><br>
The DATA is the 16 bits data that will be written into the registers of external PHY for MII
<br>
Management write command or the data from the registers of external PHY for MII Management read command.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::MIIMCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MIIMCTL
</font><br><p> <font size="2">
Offset: 0x98  MII Management Control and Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[4:0]</td><td>PHYREG</td><td><div style="word-wrap: break-word;"><b>PHY Register Address
</b><br>
The PHYREG keeps the address to indicate which register of external PHY is the target of the
<br>
MII management command.
<br>
</div></td></tr><tr><td>
[12:8]</td><td>PHYADDR</td><td><div style="word-wrap: break-word;"><b>PHY Address
</b><br>
The PHYADDR keeps the address to differentiate which external PHY is the target of the MII management command.
<br>
</div></td></tr><tr><td>
[16]</td><td>WRITE</td><td><div style="word-wrap: break-word;"><b>Write Command
</b><br>
The Write defines the MII management command is a read or write.
<br>
0 = MII management command is a read command.
<br>
1 = MII management command is a write command.
<br>
</div></td></tr><tr><td>
[17]</td><td>BUSY</td><td><div style="word-wrap: break-word;"><b>Busy Bit
</b><br>
The BUSY controls the enable of the MII management frame generation
<br>
If S/W wants to access registers of external PHY, it set BUSY to high and EMAC generates
<br>
the MII management frame to external PHY through MII Management I/F
<br>
The BUSY is a self-clear bit
<br>
This means the BUSY will be cleared automatically after the MII management command finished.
<br>
0 = MII management command generation finished.
<br>
1 = MII management command generation Enabled.
<br>
</div></td></tr><tr><td>
[18]</td><td>PREAMSP</td><td><div style="word-wrap: break-word;"><b>Preamble Suppress
</b><br>
The PREAMSP controls the preamble field generation of MII management frame
<br>
If the PREAMSP is set to high, the preamble field generation of MII management frame is skipped.
<br>
0 = Preamble field generation of MII management frame not skipped.
<br>
1 = Preamble field generation of MII management frame skipped.
<br>
</div></td></tr><tr><td>
[19]</td><td>MDCON</td><td><div style="word-wrap: break-word;"><b>MDC Clock ON
</b><br>
The MDC controls the MDC clock generation. If the MDCON is set to high, the MDC clock is turned on.
<br>
0 = MDC clock off.
<br>
1 = MDC clock on.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::FIFOCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">FIFOCTL
</font><br><p> <font size="2">
Offset: 0x9C  FIFO Threshold Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1:0]</td><td>RXFIFOTH</td><td><div style="word-wrap: break-word;"><b>RXFIFO Low Threshold
</b><br>
The RXFIFOTH controls when RXDMA requests internal arbiter for data transfer between RXFIFO
<br>
and system memory
<br>
The RXFIFOTH defines not only the high threshold of RXFIFO, but also the low threshold
<br>
The low threshold is the half of high threshold always
<br>
During the packet reception, if the RXFIFO reaches the high threshold, the RXDMA starts to
<br>
transfer frame data from RXFIFO to system memory
<br>
If the frame data in RXFIFO is less than low threshold, RXDMA stops to transfer the frame
<br>
data to system memory.
<br>
00 = Depend on the burst length setting
<br>
If the burst length is 8 words, high threshold is 8 words, too.
<br>
01 = RXFIFO high threshold is 64B and low threshold is 32B.
<br>
10 = RXFIFO high threshold is 128B and low threshold is 64B.
<br>
11 = RXFIFO high threshold is 192B and low threshold is 96B.
<br>
</div></td></tr><tr><td>
[9:8]</td><td>TXFIFOTH</td><td><div style="word-wrap: break-word;"><b>TXFIFO Low Threshold
</b><br>
The TXFIFOTH controls when TXDMA requests internal arbiter for data transfer between system
<br>
memory and TXFIFO
<br>
The TXFIFOTH defines not only the low threshold of TXFIFO, but also the high threshold
<br>
The high threshold is the twice of low threshold always
<br>
During the packet transmission, if the TXFIFO reaches the high threshold, the TXDMA stops
<br>
generate request to transfer frame data from system memory to TXFIFO
<br>
If the frame data in TXFIFO is less than low threshold, TXDMA starts to transfer frame data
<br>
from system memory to TXFIFO.
<br>
The TXFIFOTH also defines when the TXMAC starts to transmit frame out to network
<br>
The TXMAC starts to transmit the frame out while the TXFIFO first time reaches the high threshold
<br>
during the transmission of the frame
<br>
If the frame data length is less than TXFIFO high threshold, the TXMAC starts to transmit the frame
<br>
out after the frame data are all inside the TXFIFO.
<br>
00 = Undefined.
<br>
01 = TXFIFO low threshold is 64B and high threshold is 128B.
<br>
10 = TXFIFO low threshold is 80B and high threshold is 160B.
<br>
11 = TXFIFO low threshold is 96B and high threshold is 192B.
<br>
</div></td></tr><tr><td>
[21:20]</td><td>BURSTLEN</td><td><div style="word-wrap: break-word;"><b>DMA Burst Length
</b><br>
This defines the burst length of AHB bus cycle while EMAC accesses system memory.
<br>
00 = 4 words.
<br>
01 = 8 words.
<br>
10 = 16 words.
<br>
11 = 16 words.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::TXST

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TXST
</font><br><p> <font size="2">
Offset: 0xA0  Transmit Start Demand Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>TXST</td><td><div style="word-wrap: break-word;"><b>Transmit Start Demand
</b><br>
If the TX descriptor is not available for use of TXDMA after the TXON (EMAC_CTL[8]) is enabled,
<br>
the FSM (Finite State Machine) of TXDMA enters the Halt state and the frame transmission is halted
<br>
After the S/W has prepared the new TX descriptor for frame transmission, it must issue a write
<br>
command to EMAC_TXST register to make TXDMA to leave Halt state and continue the frame transmission.
<br>
The EMAC_TXST is a write only register and read from this register is undefined.
<br>
The write to EMAC_TXST register takes effect only when TXDMA stayed at Halt state.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::RXST

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">RXST
</font><br><p> <font size="2">
Offset: 0xA4  Receive Start Demand Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>RXST</td><td><div style="word-wrap: break-word;"><b>Receive Start Demand
</b><br>
If the RX descriptor is not available for use of RXDMA after the RXON (EMAC_CTL[0]) is enabled,
<br>
the FSM (Finite State Machine) of RXDMA enters the Halt state and the frame reception is halted
<br>
After the S/W has prepared the new RX descriptor for frame reception, it must issue a write
<br>
command to EMAC_RXST register to make RXDMA to leave Halt state and continue the frame reception.
<br>
The EMAC_RXST is a write only register and read from this register is undefined.
<br>
The write to EMAC_RXST register take effect only when RXDMA stayed at Halt state.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::MRFL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MRFL
</font><br><p> <font size="2">
Offset: 0xA8  Maximum Receive Frame Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>MRFL</td><td><div style="word-wrap: break-word;"><b>Maximum Receive Frame Length
</b><br>
The MRFL defines the maximum frame length for received frame
<br>
If the frame length of received frame is greater than MRFL, and bit MFLEIEN (EMAC_INTEN[8])
<br>
is also enabled, the bit MFLEIF (EMAC_INTSTS[8]) is set and the RX interrupt is triggered.
<br>
It is recommended that only use MRFL to qualify the length of received frame while S/W wants to
<br>
receive a frame which length is greater than 1518 bytes.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::INTEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTEN
</font><br><p> <font size="2">
Offset: 0xAC  MAC Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>RXIEN</td><td><div style="word-wrap: break-word;"><b>Receive Interrupt Enable Bit
</b><br>
The RXIEN controls the RX interrupt generation.
<br>
If RXIEN is enabled and RXIF (EMAC_INTSTS[0]) is high, EMAC generates the RX interrupt to CPU
<br>
If RXIEN is disabled, no RX interrupt is generated to CPU even any status bit EMAC_INTSTS[15:1]
<br>
is set and the corresponding bit of EMAC_INTEN is enabled
<br>
In other words, if S/W wants to receive RX interrupt from EMAC, this bit must be enabled
<br>
And, if S/W doesn't want to receive any RX interrupt from EMAC, disables this bit.
<br>
0 = RXIF (EMAC_INTSTS[0]) is masked and RX interrupt generation Disabled.
<br>
1 = RXIF (EMAC_INTSTS[0]) is not masked and RX interrupt generation Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>CRCEIEN</td><td><div style="word-wrap: break-word;"><b>CRC Error Interrupt Enable Bit
</b><br>
The CRCEIEN controls the CRCEIF (EMAC_INTSTS[1]) interrupt generation
<br>
If CRCEIF (EMAC_INTSTS[1]) is set, and both CRCEIEN and RXIEN (EMAC_INTEN[0]) are enabled, the
<br>
EMAC generates the RX interrupt to CPU
<br>
If CRCEIEN or RXIEN (EMAC_INTEN[0]) is disabled, no RX interrupt is generated to CPU even the
<br>
CRCEIF (EMAC_INTSTS[1]) is set.
<br>
0 = CRCEIF (EMAC_INTSTS[1]) trigger RX interrupt Disabled.
<br>
1 = CRCEIF (EMAC_INTSTS[1]) trigger RX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>RXOVIEN</td><td><div style="word-wrap: break-word;"><b>Receive FIFO Overflow Interrupt Enable Bit
</b><br>
The RXOVIEN controls the RXOVIF (EMAC_INTSTS[2]) interrupt generation
<br>
If RXOVIF (EMAC_INTSTS[2]) is set, and both RXOVIEN and RXIEN (EMAC_INTEN[0]) are enabled, the
<br>
EMAC generates the RX interrupt to CPU
<br>
If RXOVIEN or RXIEN (EMAC_INTEN[0]) is disabled, no RX interrupt is generated to CPU even the
<br>
RXOVIF (EMAC_INTSTS[2]) is set.
<br>
0 = RXOVIF (EMAC_INTSTS[2]) trigger RX interrupt Disabled.
<br>
1 = RXOVIF (EMAC_INTSTS[2]) trigger RX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>LPIEN</td><td><div style="word-wrap: break-word;"><b>Long Packet Interrupt Enable Bit
</b><br>
The LPIEN controls the LPIF (EMAC_INTSTS[3]) interrupt generation
<br>
If LPIF (EMAC_INTSTS[3]) is set, and both LPIEN and RXIEN (EMAC_INTEN[0]) are enabled, the EMAC
<br>
generates the RX interrupt to CPU
<br>
If LPIEN or RXIEN (EMAC_INTEN[0]) is disabled, no RX interrupt is generated to CPU even the LPIF
<br>
(EMAC_INTSTS[3]) is set.
<br>
0 = LPIF (EMAC_INTSTS[3]) trigger RX interrupt Disabled.
<br>
1 = LPIF (EMAC_INTSTS[3]) trigger RX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>RXGDIEN</td><td><div style="word-wrap: break-word;"><b>Receive Good Interrupt Enable Bit
</b><br>
The RXGDIEN controls the RXGDIF (EMAC_INTSTS[4]) interrupt generation
<br>
If RXGDIF (EMAC_INTSTS[4]) is set, and both RXGDIEN and RXIEN (EMAC_INTEN[0]) are enabled, the
<br>
EMAC generates the RX interrupt to CPU
<br>
If RXGDIEN or RXIEN (EMAC_INTEN[0]) is disabled, no RX interrupt is generated to CPU even the
<br>
RXGDIF (EMAC_INTSTS[4]) is set.
<br>
0 = RXGDIF (EMAC_INTSTS[4]) trigger RX interrupt Disabled.
<br>
1 = RXGDIF (EMAC_INTSTS[4]) trigger RX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>ALIEIEN</td><td><div style="word-wrap: break-word;"><b>Alignment Error Interrupt Enable Bit
</b><br>
The ALIEIEN controls the ALIEIF (EMAC_INTSTS[5]) interrupt generation
<br>
If ALIEIF (EMAC_INTSTS[5]) is set, and both ALIEIEN and RXIEN (EMAC_INTEN[0]) are enabled, the
<br>
EMAC generates the RX interrupt to CPU
<br>
If ALIEIEN or RXIEN (EMAC_INTEN[0]) is disabled, no RX interrupt is generated to CPU even the
<br>
ALIEIF (EMAC_INTSTS[5]) is set.
<br>
0 = ALIEIF (EMAC_INTSTS[5]) trigger RX interrupt Disabled.
<br>
1 = ALIEIF (EMAC_INTSTS[5]) trigger RX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>RPIEN</td><td><div style="word-wrap: break-word;"><b>Runt Packet Interrupt Enable Bit
</b><br>
The RPIEN controls the RPIF (EMAC_INTSTS[6]) interrupt generation
<br>
If RPIF (EMAC_INTSTS[6]) is set, and both RPIEN and RXIEN (EMAC_INTEN[0]) are enabled, the EMAC
<br>
generates the RX interrupt to CPU
<br>
If RPIEN or RXIEN (EMAC_INTEN[0]) is disabled, no RX interrupt is generated to CPU even the
<br>
RPIF (EMAC_INTSTS[6]) is set.
<br>
0 = RPIF (EMAC_INTSTS[6]) trigger RX interrupt Disabled.
<br>
1 = RPIF (EMAC_INTSTS[6]) trigger RX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[7]</td><td>MPCOVIEN</td><td><div style="word-wrap: break-word;"><b>Miss Packet Counter Overrun Interrupt Enable Bit
</b><br>
The MPCOVIEN controls the MPCOVIF (EMAC_INTSTS[7]) interrupt generation
<br>
If MPCOVIF (EMAC_INTSTS[7]) is set, and both MPCOVIEN and RXIEN (EMAC_INTEN[0]) are enabled,
<br>
the EMAC generates the RX interrupt to CPU
<br>
If MPCOVIEN or RXIEN (EMAC_INTEN[0]) is disabled, no RX interrupt is generated to CPU even the
<br>
MPCOVIF (EMAC_INTSTS[7]) is set.
<br>
0 = MPCOVIF (EMAC_INTSTS[7]) trigger RX interrupt Disabled.
<br>
1 = MPCOVIF (EMAC_INTSTS[7]) trigger RX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>MFLEIEN</td><td><div style="word-wrap: break-word;"><b>Maximum Frame Length Exceed Interrupt Enable Bit
</b><br>
The MFLEIEN controls the MFLEIF (EMAC_INTSTS[8]) interrupt generation
<br>
If MFLEIF (EMAC_INTSTS[8]) is set, and both MFLEIEN and RXIEN (EMAC_INTEN[0]) are enabled, the
<br>
EMAC generates the RX interrupt to CPU
<br>
If MFLEIEN or RXIEN (EMAC_INTEN[0]) is disabled, no RX interrupt is generated to CPU even the
<br>
MFLEIF (EMAC_INTSTS[8]) is set.
<br>
0 = MFLEIF (EMAC_INTSTS[8]) trigger RX interrupt Disabled.
<br>
1 = MFLEIF (EMAC_INTSTS[8]) trigger RX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[9]</td><td>DENIEN</td><td><div style="word-wrap: break-word;"><b>DMA Early Notification Interrupt Enable Bit
</b><br>
The DENIEN controls the DENIF (EMAC_INTSTS[9]) interrupt generation
<br>
If DENIF (EMAC_INTSTS[9]) is set, and both DENIEN and RXIEN (EMAC_INTEN[0]) are enabled, the
<br>
EMAC generates the RX interrupt to CPU
<br>
If DENIEN or RXIEN (EMAC_INTEN[0]) is disabled, no RX interrupt is generated to CPU even the
<br>
DENIF (EMAC_INTSTS[9]) is set.
<br>
0 = TDENIF (EMAC_INTSTS[9]) trigger RX interrupt Disabled.
<br>
1 = TDENIF (EMAC_INTSTS[9]) trigger RX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[10]</td><td>RDUIEN</td><td><div style="word-wrap: break-word;"><b>Receive Descriptor Unavailable Interrupt Enable Bit
</b><br>
The RDUIEN controls the RDUIF (EMAC_INTSTS[10]) interrupt generation
<br>
If RDUIF (EMAC_INTSTS[10]) is set, and both RDUIEN and RXIEN (EMAC_INTEN[0]) are enabled, the
<br>
EMAC generates the RX interrupt to CPU
<br>
If RDUIEN or RXIEN (EMAC_INTEN[0]) is disabled, no RX interrupt is generated to CPU even the
<br>
RDUIF (EMAC_MIOSTA[10]) register is set.
<br>
0 = RDUIF (EMAC_INTSTS[10]) trigger RX interrupt Disabled.
<br>
1 = RDUIF (EMAC_INTSTS[10]) trigger RX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[11]</td><td>RXBEIEN</td><td><div style="word-wrap: break-word;"><b>Receive Bus Error Interrupt Enable Bit
</b><br>
The RXBEIEN controls the RXBEIF (EMAC_INTSTS[11]) interrupt generation
<br>
If RXBEIF (EMAC_INTSTS[11]) is set, and both RXBEIEN and RXIEN (EMAC_INTEN[0]) are enabled, the
<br>
EMAC generates the RX interrupt to CPU
<br>
If RXBEIEN or RXIEN (EMAC_INTEN[0]) is disabled, no RX interrupt is generated to CPU even the
<br>
RXBEIF (EMAC_INTSTS[11]) is set.
<br>
0 = RXBEIF (EMAC_INTSTS[11]) trigger RX interrupt Disabled.
<br>
1 = RXBEIF (EMAC_INTSTS[11]) trigger RX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[14]</td><td>CFRIEN</td><td><div style="word-wrap: break-word;"><b>Control Frame Receive Interrupt Enable Bit
</b><br>
The CFRIEN controls the CFRIF (EMAC_INTSTS[14]) interrupt generation
<br>
If CFRIF (EMAC_INTSTS[14]) is set, and both CFRIEN and RXIEN (EMAC_INTEN[0]) are enabled, the
<br>
EMAC generates the RX interrupt to CPU
<br>
If CFRIEN or RXIEN (EMAC_INTEN[0]) is disabled, no RX interrupt is generated to CPU even the
<br>
CFRIF (EMAC_INTSTS[14]) register is set.
<br>
0 = CFRIF (EMAC_INTSTS[14]) trigger RX interrupt Disabled.
<br>
1 = CFRIF (EMAC_INTSTS[14]) trigger RX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[15]</td><td>WOLIEN</td><td><div style="word-wrap: break-word;"><b>Wake on LAN Interrupt Enable Bit
</b><br>
The WOLIEN controls the WOLIF (EMAC_INTSTS[15]) interrupt generation
<br>
If WOLIF (EMAC_INTSTS[15]) is set, and both WOLIEN and RXIEN (EMAC_INTEN[0]) are enabled,
<br>
the EMAC generates the RX interrupt to CPU
<br>
If WOLIEN or RXIEN (EMAC_INTEN[0]) is disabled, no RX interrupt is generated to CPU even the
<br>
WOLIF (EMAC_INTSTS[15]) is set.
<br>
0 = WOLIF (EMAC_INTSTS[15]) trigger RX interrupt Disabled.
<br>
1 = WOLIF (EMAC_INTSTS[15]) trigger RX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[16]</td><td>TXIEN</td><td><div style="word-wrap: break-word;"><b>Transmit Interrupt Enable Bit
</b><br>
The TXIEN controls the TX interrupt generation.
<br>
If TXIEN is enabled and TXIF (EMAC_INTSTS[16]) is high, EMAC generates the TX interrupt to CPU
<br>
If TXIEN is disabled, no TX interrupt is generated to CPU even any status bit of
<br>
EMAC_INTSTS[24:17] set and the corresponding bit of EMAC_INTEN is enabled
<br>
In other words, if S/W wants to receive TX interrupt from EMAC, this bit must be enabled
<br>
And, if S/W doesn't want to receive any TX interrupt from EMAC, disables this bit.
<br>
0 = TXIF (EMAC_INTSTS[16]) is masked and TX interrupt generation Disabled.
<br>
1 = TXIF (EMAC_INTSTS[16]) is not masked and TX interrupt generation Enabled.
<br>
</div></td></tr><tr><td>
[17]</td><td>TXUDIEN</td><td><div style="word-wrap: break-word;"><b>Transmit FIFO Underflow Interrupt Enable Bit
</b><br>
The TXUDIEN controls the TXUDIF (EMAC_INTSTS[17]) interrupt generation
<br>
If TXUDIF (EMAC_INTSTS[17]) is set, and both TXUDIEN and TXIEN (EMAC_INTEN[16]) are enabled,
<br>
the EMAC generates the TX interrupt to CPU
<br>
If TXUDIEN or TXIEN (EMAC_INTEN[16]) is disabled, no TX interrupt is generated to CPU even
<br>
the TXUDIF (EMAC_INTSTS[17]) is set.
<br>
0 = TXUDIF (EMAC_INTSTS[17]) TX interrupt Disabled.
<br>
1 = TXUDIF (EMAC_INTSTS[17]) TX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[18]</td><td>TXCPIEN</td><td><div style="word-wrap: break-word;"><b>Transmit Completion Interrupt Enable Bit
</b><br>
The TXCPIEN controls the TXCPIF (EMAC_INTSTS[18]) interrupt generation
<br>
If TXCPIF (EMAC_INTSTS[18]) is set, and both TXCPIEN and TXIEN (EMAC_INTEN[16]) are enabled,
<br>
the EMAC generates the TX interrupt to CPU
<br>
If TXCPIEN or TXIEN (EMAC_INTEN[16]) is disabled, no TX interrupt is generated to CPU even the
<br>
TXCPIF (EMAC_INTSTS[18]) is set.
<br>
0 = TXCPIF (EMAC_INTSTS[18]) trigger TX interrupt Disabled.
<br>
1 = TXCPIF (EMAC_INTSTS[18]) trigger TX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[19]</td><td>EXDEFIEN</td><td><div style="word-wrap: break-word;"><b>Defer Exceed Interrupt Enable Bit
</b><br>
The EXDEFIEN controls the EXDEFIF (EMAC_INTSTS[19]) interrupt generation
<br>
If EXDEFIF (EMAC_INTSTS[19]) is set, and both EXDEFIEN and TXIEN (EMAC_INTEN[16]) are enabled,
<br>
the EMAC generates the TX interrupt to CPU
<br>
If EXDEFIEN or TXIEN (EMAC_INTEN[16]) is disabled, no TX interrupt is generated to CPU even the
<br>
EXDEFIF (EMAC_INTSTS[19]) is set.
<br>
0 = EXDEFIF (EMAC_INTSTS[19]) trigger TX interrupt Disabled.
<br>
1 = EXDEFIF (EMAC_INTSTS[19]) trigger TX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[20]</td><td>NCSIEN</td><td><div style="word-wrap: break-word;"><b>No Carrier Sense Interrupt Enable Bit
</b><br>
The NCSIEN controls the NCSIF (EMAC_INTSTS[20]) interrupt generation
<br>
If NCSIF (EMAC_INTSTS[20]) is set, and both NCSIEN and TXIEN (EMAC_INTEN[16]) are enabled, the
<br>
EMAC generates the TX interrupt to CPU
<br>
If NCSIEN or TXIEN (EMAC_INTEN[16]) is disabled, no TX interrupt is generated to CPU even the
<br>
NCSIF (EMAC_INTSTS[20]) is set.
<br>
0 = NCSIF (EMAC_INTSTS[20]) trigger TX interrupt Disabled.
<br>
1 = NCSIF (EMAC_INTSTS[20]) trigger TX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[21]</td><td>TXABTIEN</td><td><div style="word-wrap: break-word;"><b>Transmit Abort Interrupt Enable Bit
</b><br>
The TXABTIEN controls the TXABTIF (EMAC_INTSTS[21]) interrupt generation
<br>
If TXABTIF (EMAC_INTSTS[21]) is set, and both TXABTIEN and TXIEN (EMAC_INTEN[16]) are enabled,
<br>
the EMAC generates the TX interrupt to CPU
<br>
If TXABTIEN or TXIEN (EMAC_INTEN[16]) is disabled, no TX interrupt is generated to CPU even the
<br>
TXABTIF (EMAC_INTSTS[21]) is set.
<br>
0 = TXABTIF (EMAC_INTSTS[21]) trigger TX interrupt Disabled.
<br>
1 = TXABTIF (EMAC_INTSTS[21]) trigger TX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[22]</td><td>LCIEN</td><td><div style="word-wrap: break-word;"><b>Late Collision Interrupt Enable Bit
</b><br>
The LCIEN controls the LCIF (EMAC_INTSTS[22]) interrupt generation
<br>
If LCIF (EMAC_INTSTS[22]) is set, and both LCIEN and TXIEN (EMAC_INTEN[16]) are enabled, the
<br>
EMAC generates the TX interrupt to CPU
<br>
If LCIEN or TXIEN (EMAC_INTEN[16]) is disabled, no TX interrupt is generated to CPU even the
<br>
LCIF (EMAC_INTSTS[22]) is set.
<br>
0 = LCIF (EMAC_INTSTS[22]) trigger TX interrupt Disabled.
<br>
1 = LCIF (EMAC_INTSTS[22]) trigger TX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[23]</td><td>TDUIEN</td><td><div style="word-wrap: break-word;"><b>Transmit Descriptor Unavailable Interrupt Enable Bit
</b><br>
The TDUIEN controls the TDUIF (EMAC_INTSTS[23]) interrupt generation
<br>
If TDUIF (EMAC_INTSTS[23]) is set, and both TDUIEN and TXIEN (EMAC_INTEN[16]) are enabled, the
<br>
EMAC generates the TX interrupt to CPU
<br>
If TDUIEN or TXIEN (EMAC_INTEN[16]) is disabled, no TX interrupt is generated to CPU even the
<br>
TDUIF (EMAC_INTSTS[23]) is set.
<br>
0 = TDUIF (EMAC_INTSTS[23]) trigger TX interrupt Disabled.
<br>
1 = TDUIF (EMAC_INTSTS[23]) trigger TX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[24]</td><td>TXBEIEN</td><td><div style="word-wrap: break-word;"><b>Transmit Bus Error Interrupt Enable Bit
</b><br>
The TXBEIEN controls the TXBEIF (EMAC_INTSTS[24]) interrupt generation
<br>
If TXBEIF (EMAC_INTSTS[24]) is set, and both TXBEIEN and TXIEN (EMAC_INTEN[16]) are enabled, the
<br>
EMAC generates the TX interrupt to CPU
<br>
If TXBEIEN or TXIEN (EMAC_INTEN[16]) is disabled, no TX interrupt is generated to CPU even the
<br>
TXBEIF (EMAC_INTSTS[24]) is set.
<br>
0 = TXBEIF (EMAC_INTSTS[24]) trigger TX interrupt Disabled.
<br>
1 = TXBEIF (EMAC_INTSTS[24]) trigger TX interrupt Enabled.
<br>
</div></td></tr><tr><td>
[28]</td><td>TSALMIEN</td><td><div style="word-wrap: break-word;"><b>Time Stamp Alarm Interrupt Enable Bit
</b><br>
The TSALMIEN controls the TSALMIF (EMAC_INTSTS[28]) interrupt generation
<br>
If TSALMIF (EMAC_INTSTS[28]) is set, and both TSALMIEN and TXIEN (EMAC_INTEN[16]) enabled, the
<br>
EMAC generates the TX interrupt to CPU
<br>
If TSALMIEN or TXIEN (EMAC_INTEN[16]) disabled, no TX interrupt generated to CPU even the
<br>
TXTSALMIF (EMAC_INTEN[28]) is set.
<br>
0 = TXTSALMIF (EMAC_INTSTS[28]) trigger TX interrupt Disabled.
<br>
1 = TXTSALMIF (EMAC_INTSTS[28]) trigger TX interrupt Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::INTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTSTS
</font><br><p> <font size="2">
Offset: 0xB0  MAC Interrupt Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>RXIF</td><td><div style="word-wrap: break-word;"><b>Receive Interrupt
</b><br>
The RXIF indicates the RX interrupt status.
<br>
If RXIF high and its corresponding enable bit, RXIEN (EMAC_INTEN[0]), is also high indicates
<br>
the EMAC generates RX interrupt to CPU
<br>
If RXIF is high but RXIEN (EMAC_INTEN[0]) is disabled, no RX interrupt is generated.
<br>
The RXIF is logic OR result of bit logic AND result of EMAC_INTSTS[15:1] and EMAC_INTEN[15:1]
<br>
In other words, if any bit of EMAC_INTSTS[15:1] is high and its corresponding enable bit in
<br>
EMAC_INTEN[15:1] is also enabled, the RXIF will be high.
<br>
Because the RXIF is a logic OR result, clears EMAC_INTSTS[15:1] makes RXIF be cleared, too.
<br>
0 = No status bit in EMAC_INTSTS[15:1] is set or no enable bit in EMAC_INTEN[15:1] is enabled.
<br>
1 = At least one status in EMAC_INTSTS[15:1] is set and its corresponding enable bit in
<br>
EMAC_INTEN[15:1] is enabled, too.
<br>
</div></td></tr><tr><td>
[1]</td><td>CRCEIF</td><td><div style="word-wrap: break-word;"><b>CRC Error Interrupt
</b><br>
The CRCEIF high indicates the incoming packet incurred the CRC error and the packet is dropped
<br>
If the AEP (EMAC_CTL[4]) is set, the CRC error packet will be regarded as a good packet and
<br>
CRCEIF will not be set.
<br>
If the CRCEIF is high and CRCEIEN (EMAC_INTEN[1]) is enabled, the RXIF will be high
<br>
Write 1 to this bit clears the CRCEIF status.
<br>
0 = The frame does not incur CRC error.
<br>
1 = The frame incurred CRC error.
<br>
</div></td></tr><tr><td>
[2]</td><td>RXOVIF</td><td><div style="word-wrap: break-word;"><b>Receive FIFO Overflow Interrupt
</b><br>
The RXOVIF high indicates the RXFIFO overflow occurred during packet reception
<br>
While the RXFIFO overflow occurred, the EMAC drops the current receiving packer
<br>
If the RXFIFO overflow occurred often, it is recommended that modify RXFIFO threshold control,
<br>
the RXFIFOTH of FFTCR register, to higher level.
<br>
If the RXOVIF is high and RXOVIEN (EMAC_INTEN[2]) is enabled, the RXIF will be high
<br>
Write 1 to this bit clears the RXOVIF status.
<br>
0 = No RXFIFO overflow occurred during packet reception.
<br>
1 = RXFIFO overflow occurred during packet reception.
<br>
</div></td></tr><tr><td>
[3]</td><td>LPIF</td><td><div style="word-wrap: break-word;"><b>Long Packet Interrupt Flag
</b><br>
The LPIF high indicates the length of the incoming packet is greater than 1518 bytes and the
<br>
incoming packet is dropped
<br>
If the ALP (EMAC_CTL[1]) is set, the long packet will be regarded as a good packet and LPIF will not be set.
<br>
If the LPIF is high and LPIEN (EMAC_INTEN[3]) is enabled, the RXIF will be high
<br>
Write 1 to this bit clears the LPIF status.
<br>
0 = The incoming frame is not a long frame or S/W wants to receive a long frame.
<br>
1 = The incoming frame is a long frame and dropped.
<br>
</div></td></tr><tr><td>
[4]</td><td>RXGDIF</td><td><div style="word-wrap: break-word;"><b>Receive Good Interrupt
</b><br>
The RXGDIF high indicates the frame reception has completed.
<br>
If the RXGDIF is high and RXGDIEN (EAMC_MIEN[4]) is enabled, the RXIF will be high
<br>
Write 1 to this bit clears the RXGDIF status.
<br>
0 = The frame reception has not complete yet.
<br>
1 = The frame reception has completed.
<br>
</div></td></tr><tr><td>
[5]</td><td>ALIEIF</td><td><div style="word-wrap: break-word;"><b>Alignment Error Interrupt
</b><br>
The ALIEIF high indicates the length of the incoming frame is not a multiple of byte
<br>
If the ALIEIF is high and ALIEIEN (EMAC_INTEN[5]) is enabled, the RXIF will be high
<br>
Write 1 to this bit clears the ALIEIF status.
<br>
0 = The frame length is a multiple of byte.
<br>
1 = The frame length is not a multiple of byte.
<br>
</div></td></tr><tr><td>
[6]</td><td>RPIF</td><td><div style="word-wrap: break-word;"><b>Runt Packet Interrupt
</b><br>
The RPIF high indicates the length of the incoming packet is less than 64 bytes and the packet is dropped
<br>
If the ARP (EMAC_CTL[2]) is set, the short packet is regarded as a good packet and RPIF will not be set.
<br>
If the RPIF is high and RPIEN (EMAC_INTEN[6]) is enabled, the RXIF will be high
<br>
Write 1 to this bit clears the RPIF status.
<br>
0 = The incoming frame is not a short frame or S/W wants to receive a short frame.
<br>
1 = The incoming frame is a short frame and dropped.
<br>
</div></td></tr><tr><td>
[7]</td><td>MPCOVIF</td><td><div style="word-wrap: break-word;"><b>Missed Packet Counter Overrun Interrupt Flag
</b><br>
The MPCOVIF high indicates the MPCNT, Missed Packet Count, has overflow
<br>
If the MPCOVIF is high and MPCOVIEN (EMAC_INTEN[7]) is enabled, the RXIF will be high
<br>
Write 1 to this bit clears the MPCOVIF status.
<br>
0 = The MPCNT has not rolled over yet.
<br>
1 = The MPCNT has rolled over yet.
<br>
</div></td></tr><tr><td>
[8]</td><td>MFLEIF</td><td><div style="word-wrap: break-word;"><b>Maximum Frame Length Exceed Interrupt Flag
</b><br>
The MFLEIF high indicates the length of the incoming packet has exceeded the length limitation
<br>
configured in DMARFC register and the incoming packet is dropped
<br>
If the MFLEIF is high and MFLEIEN (EMAC_INTEN[8]) is enabled, the RXIF will be high
<br>
Write 1 to this bit clears the MFLEIF status.
<br>
0 = The length of the incoming packet does not exceed the length limitation configured in DMARFC.
<br>
1 = The length of the incoming packet has exceeded the length limitation configured in DMARFC.
<br>
</div></td></tr><tr><td>
[9]</td><td>DENIF</td><td><div style="word-wrap: break-word;"><b>DMA Early Notification Interrupt
</b><br>
The DENIF high indicates the EMAC has received the LENGTH field of the incoming packet.
<br>
If the DENIF is high and DENIENI (EMAC_INTEN[9]) is enabled, the RXIF will be high
<br>
Write 1 to this bit clears the DENIF status.
<br>
0 = The LENGTH field of incoming packet has not received yet.
<br>
1 = The LENGTH field of incoming packet has received.
<br>
</div></td></tr><tr><td>
[10]</td><td>RDUIF</td><td><div style="word-wrap: break-word;"><b>Receive Descriptor Unavailable Interrupt
</b><br>
The RDUIF high indicates that there is no available RX descriptor for packet reception and
<br>
RXDMA will stay at Halt state
<br>
Once, the RXDMA enters the Halt state, S/W must issues a write command to RSDR register to
<br>
make RXDMA leave Halt state while new RX descriptor is available.
<br>
If the RDUIF is high and RDUIEN (EMAC_INTEN[10]) is enabled, the RXIF will be high
<br>
Write 1 to this bit clears the RDUIF status.
<br>
0 = RX descriptor is available.
<br>
1 = RX descriptor is unavailable.
<br>
</div></td></tr><tr><td>
[11]</td><td>RXBEIF</td><td><div style="word-wrap: break-word;"><b>Receive Bus Error Interrupt
</b><br>
The RXBEIF high indicates the memory controller replies ERROR response while EMAC access
<br>
system memory through RXDMA during packet reception process
<br>
Reset EMAC is recommended while RXBEIF status is high.
<br>
If the RXBEIF is high and RXBEIEN (EMAC_INTEN[11]) is enabled, the RXIF will be high
<br>
Write 1 to this bit clears the RXBEIF status.
<br>
0 = No ERROR response is received.
<br>
1 = ERROR response is received.
<br>
</div></td></tr><tr><td>
[14]</td><td>CFRIF</td><td><div style="word-wrap: break-word;"><b>Control Frame Receive Interrupt
</b><br>
The CFRIF high indicates EMAC receives a flow control frame
<br>
The CFRIF only available while EMAC is operating on full duplex mode.
<br>
If the CFRIF is high and CFRIEN (EMAC_INTEN[14]) is enabled, the RXIF will be high
<br>
Write 1 to this bit clears the CFRIF status.
<br>
0 = The EMAC does not receive the flow control frame.
<br>
1 = The EMAC receives a flow control frame.
<br>
</div></td></tr><tr><td>
[15]</td><td>WOLIF</td><td><div style="word-wrap: break-word;"><b>Wake on LAN Interrupt Flag
</b><br>
The WOLIF high indicates EMAC receives a Magic Packet
<br>
The CFRIF only available while system is in power down mode and WOLEN is set high.
<br>
If the WOLIF is high and WOLIEN (EMAC_INTEN[15]) is enabled, the RXIF will be high
<br>
Write 1 to this bit clears the WOLIF status.
<br>
0 = The EMAC does not receive the Magic Packet.
<br>
1 = The EMAC receives a Magic Packet.
<br>
</div></td></tr><tr><td>
[16]</td><td>TXIF</td><td><div style="word-wrap: break-word;"><b>Transmit Interrupt
</b><br>
The TXIF indicates the TX interrupt status.
<br>
If TXIF high and its corresponding enable bit, TXIEN (EMAC_INTEN[16]), is also high indicates
<br>
the EMAC generates TX interrupt to CPU
<br>
If TXIF is high but TXIEN (EMAC_INTEN[16]) is disabled, no TX interrupt is generated.
<br>
The TXIF is logic OR result of bit logic AND result of EMAC_INTSTS[28:17] and EMAC_INTEN[28:17]
<br>
In other words, if any bit of EMAC_INTSTS[28:17] is high and its corresponding enable bit
<br>
in EMAC_INTEN[28:17] is also enabled, the TXIF will be high
<br>
Because the TXIF is a logic OR result, clears EMAC_INTSTS[28:17] makes TXIF be cleared, too.
<br>
0 = No status bit in EMAC_INTSTS[28:17] is set or no enable bit in EMAC_INTEN[28:17] is enabled.
<br>
1 = At least one status in EMAC_INTSTS[28:17] is set and its corresponding enable bit
<br>
in EMAC_INTEN[28:17] is enabled, too.
<br>
</div></td></tr><tr><td>
[17]</td><td>TXUDIF</td><td><div style="word-wrap: break-word;"><b>Transmit FIFO Underflow Interrupt
</b><br>
The TXUDIF high indicates the TXFIFO underflow occurred during packet transmission
<br>
While the TXFIFO underflow occurred, the EMAC will retransmit the packet automatically
<br>
without S/W intervention
<br>
If the TXFIFO underflow occurred often, it is recommended that modify TXFIFO threshold control,
<br>
the TXFIFOTH of FFTCR register, to higher level.
<br>
If the TXUDIF is high and TXUDIEN (EMAC_INTEN[17]) is enabled, the TXIF will be high
<br>
Write 1 to this bit clears the TXUDIF status.
<br>
0 = No TXFIFO underflow occurred during packet transmission.
<br>
1 = TXFIFO underflow occurred during packet transmission.
<br>
</div></td></tr><tr><td>
[18]</td><td>TXCPIF</td><td><div style="word-wrap: break-word;"><b>Transmit Completion Interrupt
</b><br>
The TXCPIF indicates the packet transmission has completed correctly.
<br>
If the TXCPIF is high and TXCPIEN (EMAC_INTEN[18]) is enabled, the TXIF will be high
<br>
Write 1 to this bit clears the TXCPIF status.
<br>
0 = The packet transmission not completed.
<br>
1 = The packet transmission has completed.
<br>
</div></td></tr><tr><td>
[19]</td><td>EXDEFIF</td><td><div style="word-wrap: break-word;"><b>Defer Exceed Interrupt
</b><br>
The EXDEFIF high indicates the frame waiting for transmission has deferred over 0.32768ms
<br>
on 100Mbps mode, or 3.2768ms on 10Mbps mode.
<br>
The deferral exceed check will only be done while bit NODEF of MCMDR is disabled, and EMAC
<br>
is operating on half-duplex mode.
<br>
If the EXDEFIF is high and EXDEFIEN (EMAC_INTEN[19]) is enabled, the TXIF will be high
<br>
Write 1 to this bit clears the EXDEFIF status.
<br>
0 = Frame waiting for transmission has not deferred over 0.32768ms (100Mbps) or 3.2768ms (10Mbps).
<br>
1 = Frame waiting for transmission has deferred over 0.32768ms (100Mbps) or 3.2768ms (10Mbps).
<br>
</div></td></tr><tr><td>
[20]</td><td>NCSIF</td><td><div style="word-wrap: break-word;"><b>No Carrier Sense Interrupt
</b><br>
The NCSIF high indicates the MII I/F signal CRS does not active at the start of or during
<br>
the packet transmission
<br>
The NCSIF is only available while EMAC is operating on half-duplex mode
<br>
If the NCSIF is high and NCSIEN (EMAC_INTEN[20]) is enabled, the TXIF will be high.
<br>
Write 1 to this bit clears the NCSIF status.
<br>
0 = CRS signal actives correctly.
<br>
1 = CRS signal does not active at the start of or during the packet transmission.
<br>
</div></td></tr><tr><td>
[21]</td><td>TXABTIF</td><td><div style="word-wrap: break-word;"><b>Transmit Abort Interrupt
</b><br>
The TXABTIF high indicates the packet incurred 16 consecutive collisions during transmission,
<br>
and then the transmission process for this packet is aborted
<br>
The transmission abort is only available while EMAC is operating on half-duplex mode.
<br>
If the TXABTIF is high and TXABTIEN (EMAC_INTEN[21]) is enabled, the TXIF will be high
<br>
Write 1 to this bit clears the TXABTIF status.
<br>
0 = Packet does not incur 16 consecutive collisions during transmission.
<br>
1 = Packet incurred 16 consecutive collisions during transmission.
<br>
</div></td></tr><tr><td>
[22]</td><td>LCIF</td><td><div style="word-wrap: break-word;"><b>Late Collision Interrupt
</b><br>
The LCIF high indicates the collision occurred in the outside of 64 bytes collision window
<br>
This means after the 64 bytes of a frame has been transmitted out to the network, the collision
<br>
still occurred.
<br>
The late collision check will only be done while EMAC is operating on half-duplex mode
<br>
If the LCIF is high and LCIEN (EMAC_INTEN[22]) is enabled, the TXIF will be high.
<br>
Write 1 to this bit clears the LCIF status.
<br>
0 = No collision occurred in the outside of 64 bytes collision window.
<br>
1 = Collision occurred in the outside of 64 bytes collision window.
<br>
</div></td></tr><tr><td>
[23]</td><td>TDUIF</td><td><div style="word-wrap: break-word;"><b>Transmit Descriptor Unavailable Interrupt
</b><br>
The TDUIF high indicates that there is no available TX descriptor for packet transmission and
<br>
TXDMA will stay at Halt state.
<br>
Once, the TXDMA enters the Halt state, S/W must issues a write command to TSDR register to make
<br>
TXDMA leave Halt state while new TX descriptor is available.
<br>
If the TDUIF is high and TDUIEN (EMAC_INTEN[23]) is enabled, the TXIF will be high.
<br>
Write 1 to this bit clears the TDUIF status.
<br>
0 = TX descriptor is available.
<br>
1 = TX descriptor is unavailable.
<br>
</div></td></tr><tr><td>
[24]</td><td>TXBEIF</td><td><div style="word-wrap: break-word;"><b>Transmit Bus Error Interrupt
</b><br>
The TXBEIF high indicates the memory controller replies ERROR response while EMAC access system
<br>
memory through TXDMA during packet transmission process
<br>
Reset EMAC is recommended while TXBEIF status is high.
<br>
If the TXBEIF is high and TXBEIEN (EMAC_INTEN[24]) is enabled, the TXIF will be high.
<br>
Write 1 to this bit clears the TXBEIF status.
<br>
0 = No ERROR response is received.
<br>
1 = ERROR response is received.
<br>
</div></td></tr><tr><td>
[28]</td><td>TSALMIF</td><td><div style="word-wrap: break-word;"><b>Time Stamp Alarm Interrupt
</b><br>
The TSALMIF high indicates the EMAC_TSSEC register value equals to EMAC_ALMSEC register and
<br>
EMAC_TSSUBSEC register value equals to register EMAC_ALMSUBLSR.
<br>
If TSALMIF is high and TSALMIEN (EMAC_INTEN[28]) enabled, the TXIF will be high.
<br>
Write 1 to this bit clears the TSALMIF status.
<br>
0 = EMAC_TSSEC did not equal EMAC_ALMSEC or EMAC_TSSUBSEC did not equal EMAC_ALMSUBSEC.
<br>
1 = EMAC_TSSEC equals EMAC_ALMSEC and EMAC_TSSUBSEC equals EMAC_ALMSUBSEC.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::GENSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GENSTS
</font><br><p> <font size="2">
Offset: 0xB4  MAC General Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CFR</td><td><div style="word-wrap: break-word;"><b>Control Frame Received
</b><br>
The CFRIF high indicates EMAC receives a flow control frame
<br>
The CFRIF only available while EMAC is operating on full duplex mode.
<br>
0 = The EMAC does not receive the flow control frame.
<br>
1 = The EMAC receives a flow control frame.
<br>
</div></td></tr><tr><td>
[1]</td><td>RXHALT</td><td><div style="word-wrap: break-word;"><b>Receive Halted
</b><br>
The RXHALT high indicates the next normal packet reception process will be halted because
<br>
the bit RXON of MCMDR is disabled be S/W.
<br>
0 = Next normal packet reception process will go on.
<br>
1 = Next normal packet reception process will be halted.
<br>
</div></td></tr><tr><td>
[2]</td><td>RXFFULL</td><td><div style="word-wrap: break-word;"><b>RXFIFO Full
</b><br>
The RXFFULL indicates the RXFIFO is full due to four 64-byte packets are kept in RXFIFO
<br>
and the following incoming packet will be dropped.
<br>
0 = The RXFIFO is not full.
<br>
1 = The RXFIFO is full and the following incoming packet will be dropped.
<br>
</div></td></tr><tr><td>
[7:4]</td><td>COLCNT</td><td><div style="word-wrap: break-word;"><b>Collision Count
</b><br>
The COLCNT indicates that how many collisions occurred consecutively during a packet transmission
<br>
If the packet incurred 16 consecutive collisions during transmission, the COLCNT will be
<br>
0 and bit TXABTIF will be set to 1.
<br>
</div></td></tr><tr><td>
[8]</td><td>DEF</td><td><div style="word-wrap: break-word;"><b>Deferred Transmission
</b><br>
The DEF high indicates the packet transmission has deferred once
<br>
The DEF is only available while EMAC is operating on half-duplex mode.
<br>
0 = Packet transmission does not defer.
<br>
1 = Packet transmission has deferred once.
<br>
</div></td></tr><tr><td>
[9]</td><td>TXPAUSED</td><td><div style="word-wrap: break-word;"><b>Transmission Paused
</b><br>
The TXPAUSED high indicates the next normal packet transmission process will be paused temporally
<br>
because EMAC received a PAUSE control frame.
<br>
0 = Next normal packet transmission process will go on.
<br>
1 = Next normal packet transmission process will be paused.
<br>
</div></td></tr><tr><td>
[10]</td><td>SQE</td><td><div style="word-wrap: break-word;"><b>Signal Quality Error
</b><br>
The SQE high indicates the SQE error found at end of packet transmission on 10Mbps half-duplex mode
<br>
The SQE error check will only be done while both bit SQECHKEN (EMAC_CTL[17]) is enabled and EMAC
<br>
is operating on 10Mbps half-duplex mode.
<br>
0 = No SQE error found at end of packet transmission.
<br>
1 = SQE error found at end of packet transmission.
<br>
</div></td></tr><tr><td>
[11]</td><td>TXHALT</td><td><div style="word-wrap: break-word;"><b>Transmission Halted
</b><br>
The TXHALT high indicates the next normal packet transmission process will be halted because
<br>
the bit TXON (EMAC_CTL[8]) is disabled be S/W.
<br>
0 = Next normal packet transmission process will go on.
<br>
1 = Next normal packet transmission process will be halted.
<br>
</div></td></tr><tr><td>
[12]</td><td>RPSTS</td><td><div style="word-wrap: break-word;"><b>Remote Pause Status
</b><br>
The RPSTS indicates that remote pause counter down counting actives.
<br>
After Ethernet MAC controller sent PAUSE frame out successfully, it starts the remote pause
<br>
counter down counting
<br>
When this bit high, it's predictable that remote Ethernet MAC controller wouldn't start the packet
<br>
transmission until the down counting done.
<br>
0 = Remote pause counter down counting done.
<br>
1 = Remote pause counter down counting actives.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::MPCNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MPCNT
</font><br><p> <font size="2">
Offset: 0xB8  Missed Packet Count Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>MPCNT</td><td><div style="word-wrap: break-word;"><b>Miss Packet Count
</b><br>
The MPCNT indicates the number of packets that were dropped due to various types of receive errors
<br>
The following type of receiving error makes missed packet counter increase:
<br>
1. Incoming packet is incurred RXFIFO overflow.
<br>
2. Incoming packet is dropped due to RXON is disabled.
<br>
3. Incoming packet is incurred CRC error.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::RPCNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">RPCNT
</font><br><p> <font size="2">
Offset: 0xBC  MAC Receive Pause Count Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>RPCNT</td><td><div style="word-wrap: break-word;"><b>MAC Receive Pause Count
</b><br>
The RPCNT keeps the OPERAND field of the PAUSE control frame
<br>
It indicates how many slot time (512 bit time) the TX of EMAC will be paused.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::FRSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">FRSTS
</font><br><p> <font size="2">
Offset: 0xC8  DMA Receive Frame Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>RXFLT</td><td><div style="word-wrap: break-word;"><b>Receive Frame LENGTH
</b><br>
The RXFLT keeps the LENGTH field of each incoming Ethernet packet
<br>
If the bit DENIEN (EMAC_INTEN[9]) is enabled and the LENGTH field of incoming packet has
<br>
received, the bit DENIF (EMAC_INTSTS[9]) will be set and trigger interrupt.
<br>
And, the content of LENGTH field will be stored in RXFLT.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CTXDSA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTXDSA
</font><br><p> <font size="2">
Offset: 0xCC  Current Transmit Descriptor Start Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>CTXDSA</td><td><div style="word-wrap: break-word;"><b>Current Transmit Descriptor Start Address
</b><br>
The CTXDSA keeps the start address of TX descriptor that is used by TXDMA currently
<br>
The CTXDSA is read only and write to this register has no effect.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CTXBSA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTXBSA
</font><br><p> <font size="2">
Offset: 0xD0  Current Transmit Buffer Start Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>CTXBSA</td><td><div style="word-wrap: break-word;"><b>Current Transmit Buffer Start Address
</b><br>
The CTXDSA keeps the start address of TX frame buffer that is used by TXDMA currently
<br>
The CTXBSA is read only and write to this register has no effect.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CRXDSA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CRXDSA
</font><br><p> <font size="2">
Offset: 0xD4  Current Receive Descriptor Start Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>CRXDSA</td><td><div style="word-wrap: break-word;"><b>Current Receive Descriptor Start Address
</b><br>
The CRXDSA keeps the start address of RX descriptor that is used by RXDMA currently
<br>
The CRXDSA is read only and write to this register has no effect.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::CRXBSA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CRXBSA
</font><br><p> <font size="2">
Offset: 0xD8  Current Receive Buffer Start Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>CRXBSA</td><td><div style="word-wrap: break-word;"><b>Current Receive Buffer Start Address
</b><br>
The CRXBSA keeps the start address of RX frame buffer that is used by RXDMA currently
<br>
The CRXBSA is read only and write to this register has no effect.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::TSCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TSCTL
</font><br><p> <font size="2">
Offset: 0x100  Time Stamp Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>TSEN</td><td><div style="word-wrap: break-word;"><b>Time Stamp Function Enable Bit
</b><br>
This bit controls if the IEEE 1588 PTP time stamp function is enabled or not.
<br>
Set this bit high to enable IEEE 1588 PTP time stamp function while set this bit low
<br>
to disable IEEE 1588 PTP time stamp function.
<br>
0 = I EEE 1588 PTP time stamp function Disabled.
<br>
1 = IEEE 1588 PTP time stamp function Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>TSIEN</td><td><div style="word-wrap: break-word;"><b>Time Stamp Counter Initialization Enable Bit
</b><br>
Set this bit high enables Ethernet MAC controller to load value of register EMAC_UPDSEC
<br>
and EMAC_UPDSUBSEC to PTP time stamp counter.
<br>
After the load operation finished, Ethernet MAC controller clear this bit to low automatically.
<br>
0 = Time stamp counter initialization done.
<br>
1 = Time stamp counter initialization Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>TSMODE</td><td><div style="word-wrap: break-word;"><b>Time Stamp Fine Update Enable Bit
</b><br>
This bit chooses the time stamp counter update mode.
<br>
0 = Time stamp counter is in coarse update mode.
<br>
1 = Time stamp counter is in fine update mode.
<br>
</div></td></tr><tr><td>
[3]</td><td>TSUPDATE</td><td><div style="word-wrap: break-word;"><b>Time Stamp Counter Time Update Enable Bit
</b><br>
Set this bit high enables Ethernet MAC controller to add value of register EMAC_UPDSEC and
<br>
EMAC_UPDSUBSEC to PTP time stamp counter.
<br>
After the add operation finished, Ethernet MAC controller clear this bit to low automatically.
<br>
0 = No action.
<br>
1 = EMAC_UPDSEC updated to EMAC_TSSEC and EMAC_UPDSUBSEC updated to EMAC_TSSUBSEC.
<br>
</div></td></tr><tr><td>
[5]</td><td>TSALMEN</td><td><div style="word-wrap: break-word;"><b>Time Stamp Alarm Enable Bit
</b><br>
Set this bit high enable Ethernet MAC controller to set TSALMIF (EMAC_INTSTS[28]) high when
<br>
EMAC_TSSEC equals to EMAC_ALMSEC and EMAC_TSSUBSEC equals to EMAC_ALMSUBSEC.
<br>
0 = Alarm disabled when EMAC_TSSEC equals to EMAC_ALMSEC and EMAC_TSSUBSEC equals to EMAC_ALMSUBSEC.
<br>
1 = Alarm enabled when EMAC_TSSEC equals to EMAC_ALMSEC and EMAC_TSSUBSEC equals to EMAC_ALMSUBSEC.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::TSSEC

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TSSEC
</font><br><p> <font size="2">
Offset: 0x110  Time Stamp Counter Second Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SEC</td><td><div style="word-wrap: break-word;"><b>Time Stamp Counter Second
</b><br>
This register reflects the bit [63:32] value of 64-bit reference timing counter
<br>
This 32-bit value is used as the second part of time stamp when TSEN (EMAC_TSCTL[0]) is high.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::TSSUBSEC

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TSSUBSEC
</font><br><p> <font size="2">
Offset: 0x114  Time Stamp Counter Sub Second Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SUBSEC</td><td><div style="word-wrap: break-word;"><b>Time Stamp Counter Sub-second
</b><br>
This register reflects the bit [31:0] value of 64-bit reference timing counter
<br>
This 32-bit value is used as the sub-second part of time stamp when TSEN (EMAC_TSCTL[0]) is high.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::TSINC

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TSINC
</font><br><p> <font size="2">
Offset: 0x118  Time Stamp Increment Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>CNTINC</td><td><div style="word-wrap: break-word;"><b>Time Stamp Counter Increment
</b><br>
Time stamp counter increment value.
<br>
If TSEN (EMAC_TSCTL[0]) is high, EMAC adds EMAC_TSSUBSEC with this 8-bit value every
<br>
time when it wants to increase the EMAC_TSSUBSEC value.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::TSADDEND

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TSADDEND
</font><br><p> <font size="2">
Offset: 0x11C  Time Stamp Addend Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>ADDEND</td><td><div style="word-wrap: break-word;"><b>Time Stamp Counter Addend
</b><br>
This register keeps a 32-bit value for accumulator to enable increment of EMAC_TSSUBSEC.
<br>
If TSEN (EMAC_TSCTL[0]) and TSMODE (EMAC_TSCTL[2]) are both high, EMAC increases accumulator
<br>
with this 32-bit value in each HCLK
<br>
Once the accumulator is overflow, it generates a enable to increase EMAC_TSSUBSEC with an 8-bit
<br>
value kept in register EMAC_TSINC.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::UPDSEC

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">UPDSEC
</font><br><p> <font size="2">
Offset: 0x120  Time Stamp Update Second Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SEC</td><td><div style="word-wrap: break-word;"><b>Time Stamp Counter Second Update
</b><br>
When TSIEN (EMAC_TSCTL[1]) is high
<br>
EMAC loads this 32-bit value to EMAC_TSSEC directly
<br>
When TSUPDATE (EMAC_TSCTL[3]) is high, EMAC increases EMAC_TSSEC with this 32-bit value.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::UPDSUBSEC

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">UPDSUBSEC
</font><br><p> <font size="2">
Offset: 0x124  Time Stamp Update Sub Second Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SUBSEC</td><td><div style="word-wrap: break-word;"><b>Time Stamp Counter Sub-second Update
</b><br>
When TSIEN (EMAC_TSCTL[1]) is high
<br>
EMAC loads this 32-bit value to EMAC_TSSUBSEC directly
<br>
When TSUPDATE (EMAC_TSCTL[3]) is high, EMAC increases EMAC_TSSUBSEC with this 32-bit value.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::ALMSEC

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ALMSEC
</font><br><p> <font size="2">
Offset: 0x128  Time Stamp Alarm Second Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SEC</td><td><div style="word-wrap: break-word;"><b>Time Stamp Counter Second Alarm
</b><br>
Time stamp counter second part alarm value.
<br>
This value is only useful when ALMEN (EMAC_TSCTL[5]) high
<br>
If ALMEN (EMAC_TSCTL[5]) is high, EMAC_TSSEC equals to EMAC_ALMSEC and EMAC_TSSUBSEC equals to
<br>
EMAC_ALMSUBSEC, Ethernet MAC controller set TSALMIF (EMAC_INTSTS[28]) high.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EMAC_T::ALMSUBSEC

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ALMSUBSEC
</font><br><p> <font size="2">
Offset: 0x12C  Time Stamp Alarm Sub Second Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>SUBSEC</td><td><div style="word-wrap: break-word;"><b>Time Stamp Counter Sub-second Alarm
</b><br>
Time stamp counter sub-second part alarm value.
<br>
This value is only useful when ALMEN (EMAC_TSCTL[5]) high
<br>
If ALMEN (EMAC_TSCTL[5]) is high, EMAC_TSSEC equals to EMAC_ALMSEC and EMAC_TSSUBSEC equals to
<br>
EMAC_ALMSUBSEC, Ethernet MAC controller set TSALMIF (EMAC_INTSTS[28]) high.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CAMCTL;                /*!< [0x0000] CAM Comparison Control Register                                  */
    __IO uint32_t CAMEN;                 /*!< [0x0004] CAM Enable Register                                              */
    __IO uint32_t CAM0M;                 /*!< [0x0008] CAM0 Most Significant Word Register                              */
    __IO uint32_t CAM0L;                 /*!< [0x000c] CAM0 Least Significant Word Register                             */
    __IO uint32_t CAM1M;                 /*!< [0x0010] CAM1 Most Significant Word Register                              */
    __IO uint32_t CAM1L;                 /*!< [0x0014] CAM1 Least Significant Word Register                             */
    __IO uint32_t CAM2M;                 /*!< [0x0018] CAM2 Most Significant Word Register                              */
    __IO uint32_t CAM2L;                 /*!< [0x001c] CAM2 Least Significant Word Register                             */
    __IO uint32_t CAM3M;                 /*!< [0x0020] CAM3 Most Significant Word Register                              */
    __IO uint32_t CAM3L;                 /*!< [0x0024] CAM3 Least Significant Word Register                             */
    __IO uint32_t CAM4M;                 /*!< [0x0028] CAM4 Most Significant Word Register                              */
    __IO uint32_t CAM4L;                 /*!< [0x002c] CAM4 Least Significant Word Register                             */
    __IO uint32_t CAM5M;                 /*!< [0x0030] CAM5 Most Significant Word Register                              */
    __IO uint32_t CAM5L;                 /*!< [0x0034] CAM5 Least Significant Word Register                             */
    __IO uint32_t CAM6M;                 /*!< [0x0038] CAM6 Most Significant Word Register                              */
    __IO uint32_t CAM6L;                 /*!< [0x003c] CAM6 Least Significant Word Register                             */
    __IO uint32_t CAM7M;                 /*!< [0x0040] CAM7 Most Significant Word Register                              */
    __IO uint32_t CAM7L;                 /*!< [0x0044] CAM7 Least Significant Word Register                             */
    __IO uint32_t CAM8M;                 /*!< [0x0048] CAM8 Most Significant Word Register                              */
    __IO uint32_t CAM8L;                 /*!< [0x004c] CAM8 Least Significant Word Register                             */
    __IO uint32_t CAM9M;                 /*!< [0x0050] CAM9 Most Significant Word Register                              */
    __IO uint32_t CAM9L;                 /*!< [0x0054] CAM9 Least Significant Word Register                             */
    __IO uint32_t CAM10M;                /*!< [0x0058] CAM10 Most Significant Word Register                             */
    __IO uint32_t CAM10L;                /*!< [0x005c] CAM10 Least Significant Word Register                            */
    __IO uint32_t CAM11M;                /*!< [0x0060] CAM11 Most Significant Word Register                             */
    __IO uint32_t CAM11L;                /*!< [0x0064] CAM11 Least Significant Word Register                            */
    __IO uint32_t CAM12M;                /*!< [0x0068] CAM12 Most Significant Word Register                             */
    __IO uint32_t CAM12L;                /*!< [0x006c] CAM12 Least Significant Word Register                            */
    __IO uint32_t CAM13M;                /*!< [0x0070] CAM13 Most Significant Word Register                             */
    __IO uint32_t CAM13L;                /*!< [0x0074] CAM13 Least Significant Word Register                            */
    __IO uint32_t CAM14M;                /*!< [0x0078] CAM14 Most Significant Word Register                             */
    __IO uint32_t CAM14L;                /*!< [0x007c] CAM14 Least Significant Word Register                            */
    __IO uint32_t CAM15MSB;              /*!< [0x0080] CAM15 Most Significant Word Register                             */
    __IO uint32_t CAM15LSB;              /*!< [0x0084] CAM15 Least Significant Word Register                            */
    __IO uint32_t TXDSA;                 /*!< [0x0088] Transmit Descriptor Link List Start Address Register             */
    __IO uint32_t RXDSA;                 /*!< [0x008c] Receive Descriptor Link List Start Address Register              */
    __IO uint32_t CTL;                   /*!< [0x0090] MAC Control Register                                             */
    __IO uint32_t MIIMDAT;               /*!< [0x0094] MII Management Data Register                                     */
    __IO uint32_t MIIMCTL;               /*!< [0x0098] MII Management Control and Address Register                      */
    __IO uint32_t FIFOCTL;               /*!< [0x009c] FIFO Threshold Control Register                                  */
    __O  uint32_t TXST;                  /*!< [0x00a0] Transmit Start Demand Register                                   */
    __O  uint32_t RXST;                  /*!< [0x00a4] Receive Start Demand Register                                    */
    __IO uint32_t MRFL;                  /*!< [0x00a8] Maximum Receive Frame Control Register                           */
    __IO uint32_t INTEN;                 /*!< [0x00ac] MAC Interrupt Enable Register                                    */
    __IO uint32_t INTSTS;                /*!< [0x00b0] MAC Interrupt Status Register                                    */
    __IO uint32_t GENSTS;                /*!< [0x00b4] MAC General Status Register                                      */
    __IO uint32_t MPCNT;                 /*!< [0x00b8] Missed Packet Count Register                                     */
    __I  uint32_t RPCNT;                 /*!< [0x00bc] MAC Receive Pause Count Register                                 */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE0[2];
    /** @endcond */
    __IO uint32_t FRSTS;                 /*!< [0x00c8] DMA Receive Frame Status Register                                */
    __I  uint32_t CTXDSA;                /*!< [0x00cc] Current Transmit Descriptor Start Address Register               */
    __I  uint32_t CTXBSA;                /*!< [0x00d0] Current Transmit Buffer Start Address Register                   */
    __I  uint32_t CRXDSA;                /*!< [0x00d4] Current Receive Descriptor Start Address Register                */
    __I  uint32_t CRXBSA;                /*!< [0x00d8] Current Receive Buffer Start Address Register                    */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE1[9];
    /** @endcond */
    __IO uint32_t TSCTL;                 /*!< [0x0100] Time Stamp Control Register                                      */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE2[3];
    /** @endcond */
    __I  uint32_t TSSEC;                 /*!< [0x0110] Time Stamp Counter Second Register                               */
    __I  uint32_t TSSUBSEC;              /*!< [0x0114] Time Stamp Counter Sub Second Register                           */
    __IO uint32_t TSINC;                 /*!< [0x0118] Time Stamp Increment Register                                    */
    __IO uint32_t TSADDEND;              /*!< [0x011c] Time Stamp Addend Register                                       */
    __IO uint32_t UPDSEC;                /*!< [0x0120] Time Stamp Update Second Register                                */
    __IO uint32_t UPDSUBSEC;             /*!< [0x0124] Time Stamp Update Sub Second Register                            */
    __IO uint32_t ALMSEC;                /*!< [0x0128] Time Stamp Alarm Second Register                                 */
    __IO uint32_t ALMSUBSEC;             /*!< [0x012c] Time Stamp Alarm Sub Second Register                             */

} EMAC_T;

/**
    @addtogroup EMAC_CONST EMAC Bit Field Definition
    Constant Definitions for EMAC Controller
@{ */

#define EMAC_CAMCTL_AUP_Pos              (0)                                               /*!< EMAC_T::CAMCTL: AUP Position           */
#define EMAC_CAMCTL_AUP_Msk              (0x1ul << EMAC_CAMCTL_AUP_Pos)                    /*!< EMAC_T::CAMCTL: AUP Mask               */

#define EMAC_CAMCTL_AMP_Pos              (1)                                               /*!< EMAC_T::CAMCTL: AMP Position           */
#define EMAC_CAMCTL_AMP_Msk              (0x1ul << EMAC_CAMCTL_AMP_Pos)                    /*!< EMAC_T::CAMCTL: AMP Mask               */

#define EMAC_CAMCTL_ABP_Pos              (2)                                               /*!< EMAC_T::CAMCTL: ABP Position           */
#define EMAC_CAMCTL_ABP_Msk              (0x1ul << EMAC_CAMCTL_ABP_Pos)                    /*!< EMAC_T::CAMCTL: ABP Mask               */

#define EMAC_CAMCTL_COMPEN_Pos           (3)                                               /*!< EMAC_T::CAMCTL: COMPEN Position        */
#define EMAC_CAMCTL_COMPEN_Msk           (0x1ul << EMAC_CAMCTL_COMPEN_Pos)                 /*!< EMAC_T::CAMCTL: COMPEN Mask            */

#define EMAC_CAMCTL_CMPEN_Pos            (4)                                               /*!< EMAC_T::CAMCTL: CMPEN Position         */
#define EMAC_CAMCTL_CMPEN_Msk            (0x1ul << EMAC_CAMCTL_CMPEN_Pos)                  /*!< EMAC_T::CAMCTL: CMPEN Mask             */

#define EMAC_CAMEN_CAMxEN_Pos            (0)                                               /*!< EMAC_T::CAMEN: CAMxEN Position         */
#define EMAC_CAMEN_CAMxEN_Msk            (0x1ul << EMAC_CAMEN_CAMxEN_Pos)                  /*!< EMAC_T::CAMEN: CAMxEN Mask             */

#define EMAC_CAM0M_MACADDR2_Pos          (0)                                               /*!< EMAC_T::CAM0M: MACADDR2 Position       */
#define EMAC_CAM0M_MACADDR2_Msk          (0xfful << EMAC_CAM0M_MACADDR2_Pos)               /*!< EMAC_T::CAM0M: MACADDR2 Mask           */

#define EMAC_CAM0M_MACADDR3_Pos          (8)                                               /*!< EMAC_T::CAM0M: MACADDR3 Position       */
#define EMAC_CAM0M_MACADDR3_Msk          (0xfful << EMAC_CAM0M_MACADDR3_Pos)               /*!< EMAC_T::CAM0M: MACADDR3 Mask           */

#define EMAC_CAM0M_MACADDR4_Pos          (16)                                              /*!< EMAC_T::CAM0M: MACADDR4 Position       */
#define EMAC_CAM0M_MACADDR4_Msk          (0xfful << EMAC_CAM0M_MACADDR4_Pos)               /*!< EMAC_T::CAM0M: MACADDR4 Mask           */

#define EMAC_CAM0M_MACADDR5_Pos          (24)                                              /*!< EMAC_T::CAM0M: MACADDR5 Position       */
#define EMAC_CAM0M_MACADDR5_Msk          (0xfful << EMAC_CAM0M_MACADDR5_Pos)               /*!< EMAC_T::CAM0M: MACADDR5 Mask           */

#define EMAC_CAM0L_MACADDR0_Pos          (16)                                              /*!< EMAC_T::CAM0L: MACADDR0 Position       */
#define EMAC_CAM0L_MACADDR0_Msk          (0xfful << EMAC_CAM0L_MACADDR0_Pos)               /*!< EMAC_T::CAM0L: MACADDR0 Mask           */

#define EMAC_CAM0L_MACADDR1_Pos          (24)                                              /*!< EMAC_T::CAM0L: MACADDR1 Position       */
#define EMAC_CAM0L_MACADDR1_Msk          (0xfful << EMAC_CAM0L_MACADDR1_Pos)               /*!< EMAC_T::CAM0L: MACADDR1 Mask           */

#define EMAC_CAM1M_MACADDR2_Pos          (0)                                               /*!< EMAC_T::CAM1M: MACADDR2 Position       */
#define EMAC_CAM1M_MACADDR2_Msk          (0xfful << EMAC_CAM1M_MACADDR2_Pos)               /*!< EMAC_T::CAM1M: MACADDR2 Mask           */

#define EMAC_CAM1M_MACADDR3_Pos          (8)                                               /*!< EMAC_T::CAM1M: MACADDR3 Position       */
#define EMAC_CAM1M_MACADDR3_Msk          (0xfful << EMAC_CAM1M_MACADDR3_Pos)               /*!< EMAC_T::CAM1M: MACADDR3 Mask           */

#define EMAC_CAM1M_MACADDR4_Pos          (16)                                              /*!< EMAC_T::CAM1M: MACADDR4 Position       */
#define EMAC_CAM1M_MACADDR4_Msk          (0xfful << EMAC_CAM1M_MACADDR4_Pos)               /*!< EMAC_T::CAM1M: MACADDR4 Mask           */

#define EMAC_CAM1M_MACADDR5_Pos          (24)                                              /*!< EMAC_T::CAM1M: MACADDR5 Position       */
#define EMAC_CAM1M_MACADDR5_Msk          (0xfful << EMAC_CAM1M_MACADDR5_Pos)               /*!< EMAC_T::CAM1M: MACADDR5 Mask           */

#define EMAC_CAM1L_MACADDR0_Pos          (16)                                              /*!< EMAC_T::CAM1L: MACADDR0 Position       */
#define EMAC_CAM1L_MACADDR0_Msk          (0xfful << EMAC_CAM1L_MACADDR0_Pos)               /*!< EMAC_T::CAM1L: MACADDR0 Mask           */

#define EMAC_CAM1L_MACADDR1_Pos          (24)                                              /*!< EMAC_T::CAM1L: MACADDR1 Position       */
#define EMAC_CAM1L_MACADDR1_Msk          (0xfful << EMAC_CAM1L_MACADDR1_Pos)               /*!< EMAC_T::CAM1L: MACADDR1 Mask           */

#define EMAC_CAM2M_MACADDR2_Pos          (0)                                               /*!< EMAC_T::CAM2M: MACADDR2 Position       */
#define EMAC_CAM2M_MACADDR2_Msk          (0xfful << EMAC_CAM2M_MACADDR2_Pos)               /*!< EMAC_T::CAM2M: MACADDR2 Mask           */

#define EMAC_CAM2M_MACADDR3_Pos          (8)                                               /*!< EMAC_T::CAM2M: MACADDR3 Position       */
#define EMAC_CAM2M_MACADDR3_Msk          (0xfful << EMAC_CAM2M_MACADDR3_Pos)               /*!< EMAC_T::CAM2M: MACADDR3 Mask           */

#define EMAC_CAM2M_MACADDR4_Pos          (16)                                              /*!< EMAC_T::CAM2M: MACADDR4 Position       */
#define EMAC_CAM2M_MACADDR4_Msk          (0xfful << EMAC_CAM2M_MACADDR4_Pos)               /*!< EMAC_T::CAM2M: MACADDR4 Mask           */

#define EMAC_CAM2M_MACADDR5_Pos          (24)                                              /*!< EMAC_T::CAM2M: MACADDR5 Position       */
#define EMAC_CAM2M_MACADDR5_Msk          (0xfful << EMAC_CAM2M_MACADDR5_Pos)               /*!< EMAC_T::CAM2M: MACADDR5 Mask           */

#define EMAC_CAM2L_MACADDR0_Pos          (16)                                              /*!< EMAC_T::CAM2L: MACADDR0 Position       */
#define EMAC_CAM2L_MACADDR0_Msk          (0xfful << EMAC_CAM2L_MACADDR0_Pos)               /*!< EMAC_T::CAM2L: MACADDR0 Mask           */

#define EMAC_CAM2L_MACADDR1_Pos          (24)                                              /*!< EMAC_T::CAM2L: MACADDR1 Position       */
#define EMAC_CAM2L_MACADDR1_Msk          (0xfful << EMAC_CAM2L_MACADDR1_Pos)               /*!< EMAC_T::CAM2L: MACADDR1 Mask           */

#define EMAC_CAM3M_MACADDR2_Pos          (0)                                               /*!< EMAC_T::CAM3M: MACADDR2 Position       */
#define EMAC_CAM3M_MACADDR2_Msk          (0xfful << EMAC_CAM3M_MACADDR2_Pos)               /*!< EMAC_T::CAM3M: MACADDR2 Mask           */

#define EMAC_CAM3M_MACADDR3_Pos          (8)                                               /*!< EMAC_T::CAM3M: MACADDR3 Position       */
#define EMAC_CAM3M_MACADDR3_Msk          (0xfful << EMAC_CAM3M_MACADDR3_Pos)               /*!< EMAC_T::CAM3M: MACADDR3 Mask           */

#define EMAC_CAM3M_MACADDR4_Pos          (16)                                              /*!< EMAC_T::CAM3M: MACADDR4 Position       */
#define EMAC_CAM3M_MACADDR4_Msk          (0xfful << EMAC_CAM3M_MACADDR4_Pos)               /*!< EMAC_T::CAM3M: MACADDR4 Mask           */

#define EMAC_CAM3M_MACADDR5_Pos          (24)                                              /*!< EMAC_T::CAM3M: MACADDR5 Position       */
#define EMAC_CAM3M_MACADDR5_Msk          (0xfful << EMAC_CAM3M_MACADDR5_Pos)               /*!< EMAC_T::CAM3M: MACADDR5 Mask           */

#define EMAC_CAM3L_MACADDR0_Pos          (16)                                              /*!< EMAC_T::CAM3L: MACADDR0 Position       */
#define EMAC_CAM3L_MACADDR0_Msk          (0xfful << EMAC_CAM3L_MACADDR0_Pos)               /*!< EMAC_T::CAM3L: MACADDR0 Mask           */

#define EMAC_CAM3L_MACADDR1_Pos          (24)                                              /*!< EMAC_T::CAM3L: MACADDR1 Position       */
#define EMAC_CAM3L_MACADDR1_Msk          (0xfful << EMAC_CAM3L_MACADDR1_Pos)               /*!< EMAC_T::CAM3L: MACADDR1 Mask           */

#define EMAC_CAM4M_MACADDR2_Pos          (0)                                               /*!< EMAC_T::CAM4M: MACADDR2 Position       */
#define EMAC_CAM4M_MACADDR2_Msk          (0xfful << EMAC_CAM4M_MACADDR2_Pos)               /*!< EMAC_T::CAM4M: MACADDR2 Mask           */

#define EMAC_CAM4M_MACADDR3_Pos          (8)                                               /*!< EMAC_T::CAM4M: MACADDR3 Position       */
#define EMAC_CAM4M_MACADDR3_Msk          (0xfful << EMAC_CAM4M_MACADDR3_Pos)               /*!< EMAC_T::CAM4M: MACADDR3 Mask           */

#define EMAC_CAM4M_MACADDR4_Pos          (16)                                              /*!< EMAC_T::CAM4M: MACADDR4 Position       */
#define EMAC_CAM4M_MACADDR4_Msk          (0xfful << EMAC_CAM4M_MACADDR4_Pos)               /*!< EMAC_T::CAM4M: MACADDR4 Mask           */

#define EMAC_CAM4M_MACADDR5_Pos          (24)                                              /*!< EMAC_T::CAM4M: MACADDR5 Position       */
#define EMAC_CAM4M_MACADDR5_Msk          (0xfful << EMAC_CAM4M_MACADDR5_Pos)               /*!< EMAC_T::CAM4M: MACADDR5 Mask           */

#define EMAC_CAM4L_MACADDR0_Pos          (16)                                              /*!< EMAC_T::CAM4L: MACADDR0 Position       */
#define EMAC_CAM4L_MACADDR0_Msk          (0xfful << EMAC_CAM4L_MACADDR0_Pos)               /*!< EMAC_T::CAM4L: MACADDR0 Mask           */

#define EMAC_CAM4L_MACADDR1_Pos          (24)                                              /*!< EMAC_T::CAM4L: MACADDR1 Position       */
#define EMAC_CAM4L_MACADDR1_Msk          (0xfful << EMAC_CAM4L_MACADDR1_Pos)               /*!< EMAC_T::CAM4L: MACADDR1 Mask           */

#define EMAC_CAM5M_MACADDR2_Pos          (0)                                               /*!< EMAC_T::CAM5M: MACADDR2 Position       */
#define EMAC_CAM5M_MACADDR2_Msk          (0xfful << EMAC_CAM5M_MACADDR2_Pos)               /*!< EMAC_T::CAM5M: MACADDR2 Mask           */

#define EMAC_CAM5M_MACADDR3_Pos          (8)                                               /*!< EMAC_T::CAM5M: MACADDR3 Position       */
#define EMAC_CAM5M_MACADDR3_Msk          (0xfful << EMAC_CAM5M_MACADDR3_Pos)               /*!< EMAC_T::CAM5M: MACADDR3 Mask           */

#define EMAC_CAM5M_MACADDR4_Pos          (16)                                              /*!< EMAC_T::CAM5M: MACADDR4 Position       */
#define EMAC_CAM5M_MACADDR4_Msk          (0xfful << EMAC_CAM5M_MACADDR4_Pos)               /*!< EMAC_T::CAM5M: MACADDR4 Mask           */

#define EMAC_CAM5M_MACADDR5_Pos          (24)                                              /*!< EMAC_T::CAM5M: MACADDR5 Position       */
#define EMAC_CAM5M_MACADDR5_Msk          (0xfful << EMAC_CAM5M_MACADDR5_Pos)               /*!< EMAC_T::CAM5M: MACADDR5 Mask           */

#define EMAC_CAM5L_MACADDR0_Pos          (16)                                              /*!< EMAC_T::CAM5L: MACADDR0 Position       */
#define EMAC_CAM5L_MACADDR0_Msk          (0xfful << EMAC_CAM5L_MACADDR0_Pos)               /*!< EMAC_T::CAM5L: MACADDR0 Mask           */

#define EMAC_CAM5L_MACADDR1_Pos          (24)                                              /*!< EMAC_T::CAM5L: MACADDR1 Position       */
#define EMAC_CAM5L_MACADDR1_Msk          (0xfful << EMAC_CAM5L_MACADDR1_Pos)               /*!< EMAC_T::CAM5L: MACADDR1 Mask           */

#define EMAC_CAM6M_MACADDR2_Pos          (0)                                               /*!< EMAC_T::CAM6M: MACADDR2 Position       */
#define EMAC_CAM6M_MACADDR2_Msk          (0xfful << EMAC_CAM6M_MACADDR2_Pos)               /*!< EMAC_T::CAM6M: MACADDR2 Mask           */

#define EMAC_CAM6M_MACADDR3_Pos          (8)                                               /*!< EMAC_T::CAM6M: MACADDR3 Position       */
#define EMAC_CAM6M_MACADDR3_Msk          (0xfful << EMAC_CAM6M_MACADDR3_Pos)               /*!< EMAC_T::CAM6M: MACADDR3 Mask           */

#define EMAC_CAM6M_MACADDR4_Pos          (16)                                              /*!< EMAC_T::CAM6M: MACADDR4 Position       */
#define EMAC_CAM6M_MACADDR4_Msk          (0xfful << EMAC_CAM6M_MACADDR4_Pos)               /*!< EMAC_T::CAM6M: MACADDR4 Mask           */

#define EMAC_CAM6M_MACADDR5_Pos          (24)                                              /*!< EMAC_T::CAM6M: MACADDR5 Position       */
#define EMAC_CAM6M_MACADDR5_Msk          (0xfful << EMAC_CAM6M_MACADDR5_Pos)               /*!< EMAC_T::CAM6M: MACADDR5 Mask           */

#define EMAC_CAM6L_MACADDR0_Pos          (16)                                              /*!< EMAC_T::CAM6L: MACADDR0 Position       */
#define EMAC_CAM6L_MACADDR0_Msk          (0xfful << EMAC_CAM6L_MACADDR0_Pos)               /*!< EMAC_T::CAM6L: MACADDR0 Mask           */

#define EMAC_CAM6L_MACADDR1_Pos          (24)                                              /*!< EMAC_T::CAM6L: MACADDR1 Position       */
#define EMAC_CAM6L_MACADDR1_Msk          (0xfful << EMAC_CAM6L_MACADDR1_Pos)               /*!< EMAC_T::CAM6L: MACADDR1 Mask           */

#define EMAC_CAM7M_MACADDR2_Pos          (0)                                               /*!< EMAC_T::CAM7M: MACADDR2 Position       */
#define EMAC_CAM7M_MACADDR2_Msk          (0xfful << EMAC_CAM7M_MACADDR2_Pos)               /*!< EMAC_T::CAM7M: MACADDR2 Mask           */

#define EMAC_CAM7M_MACADDR3_Pos          (8)                                               /*!< EMAC_T::CAM7M: MACADDR3 Position       */
#define EMAC_CAM7M_MACADDR3_Msk          (0xfful << EMAC_CAM7M_MACADDR3_Pos)               /*!< EMAC_T::CAM7M: MACADDR3 Mask           */

#define EMAC_CAM7M_MACADDR4_Pos          (16)                                              /*!< EMAC_T::CAM7M: MACADDR4 Position       */
#define EMAC_CAM7M_MACADDR4_Msk          (0xfful << EMAC_CAM7M_MACADDR4_Pos)               /*!< EMAC_T::CAM7M: MACADDR4 Mask           */

#define EMAC_CAM7M_MACADDR5_Pos          (24)                                              /*!< EMAC_T::CAM7M: MACADDR5 Position       */
#define EMAC_CAM7M_MACADDR5_Msk          (0xfful << EMAC_CAM7M_MACADDR5_Pos)               /*!< EMAC_T::CAM7M: MACADDR5 Mask           */

#define EMAC_CAM7L_MACADDR0_Pos          (16)                                              /*!< EMAC_T::CAM7L: MACADDR0 Position       */
#define EMAC_CAM7L_MACADDR0_Msk          (0xfful << EMAC_CAM7L_MACADDR0_Pos)               /*!< EMAC_T::CAM7L: MACADDR0 Mask           */

#define EMAC_CAM7L_MACADDR1_Pos          (24)                                              /*!< EMAC_T::CAM7L: MACADDR1 Position       */
#define EMAC_CAM7L_MACADDR1_Msk          (0xfful << EMAC_CAM7L_MACADDR1_Pos)               /*!< EMAC_T::CAM7L: MACADDR1 Mask           */

#define EMAC_CAM8M_MACADDR2_Pos          (0)                                               /*!< EMAC_T::CAM8M: MACADDR2 Position       */
#define EMAC_CAM8M_MACADDR2_Msk          (0xfful << EMAC_CAM8M_MACADDR2_Pos)               /*!< EMAC_T::CAM8M: MACADDR2 Mask           */

#define EMAC_CAM8M_MACADDR3_Pos          (8)                                               /*!< EMAC_T::CAM8M: MACADDR3 Position       */
#define EMAC_CAM8M_MACADDR3_Msk          (0xfful << EMAC_CAM8M_MACADDR3_Pos)               /*!< EMAC_T::CAM8M: MACADDR3 Mask           */

#define EMAC_CAM8M_MACADDR4_Pos          (16)                                              /*!< EMAC_T::CAM8M: MACADDR4 Position       */
#define EMAC_CAM8M_MACADDR4_Msk          (0xfful << EMAC_CAM8M_MACADDR4_Pos)               /*!< EMAC_T::CAM8M: MACADDR4 Mask           */

#define EMAC_CAM8M_MACADDR5_Pos          (24)                                              /*!< EMAC_T::CAM8M: MACADDR5 Position       */
#define EMAC_CAM8M_MACADDR5_Msk          (0xfful << EMAC_CAM8M_MACADDR5_Pos)               /*!< EMAC_T::CAM8M: MACADDR5 Mask           */

#define EMAC_CAM8L_MACADDR0_Pos          (16)                                              /*!< EMAC_T::CAM8L: MACADDR0 Position       */
#define EMAC_CAM8L_MACADDR0_Msk          (0xfful << EMAC_CAM8L_MACADDR0_Pos)               /*!< EMAC_T::CAM8L: MACADDR0 Mask           */

#define EMAC_CAM8L_MACADDR1_Pos          (24)                                              /*!< EMAC_T::CAM8L: MACADDR1 Position       */
#define EMAC_CAM8L_MACADDR1_Msk          (0xfful << EMAC_CAM8L_MACADDR1_Pos)               /*!< EMAC_T::CAM8L: MACADDR1 Mask           */

#define EMAC_CAM9M_MACADDR2_Pos          (0)                                               /*!< EMAC_T::CAM9M: MACADDR2 Position       */
#define EMAC_CAM9M_MACADDR2_Msk          (0xfful << EMAC_CAM9M_MACADDR2_Pos)               /*!< EMAC_T::CAM9M: MACADDR2 Mask           */

#define EMAC_CAM9M_MACADDR3_Pos          (8)                                               /*!< EMAC_T::CAM9M: MACADDR3 Position       */
#define EMAC_CAM9M_MACADDR3_Msk          (0xfful << EMAC_CAM9M_MACADDR3_Pos)               /*!< EMAC_T::CAM9M: MACADDR3 Mask           */

#define EMAC_CAM9M_MACADDR4_Pos          (16)                                              /*!< EMAC_T::CAM9M: MACADDR4 Position       */
#define EMAC_CAM9M_MACADDR4_Msk          (0xfful << EMAC_CAM9M_MACADDR4_Pos)               /*!< EMAC_T::CAM9M: MACADDR4 Mask           */

#define EMAC_CAM9M_MACADDR5_Pos          (24)                                              /*!< EMAC_T::CAM9M: MACADDR5 Position       */
#define EMAC_CAM9M_MACADDR5_Msk          (0xfful << EMAC_CAM9M_MACADDR5_Pos)               /*!< EMAC_T::CAM9M: MACADDR5 Mask           */

#define EMAC_CAM9L_MACADDR0_Pos          (16)                                              /*!< EMAC_T::CAM9L: MACADDR0 Position       */
#define EMAC_CAM9L_MACADDR0_Msk          (0xfful << EMAC_CAM9L_MACADDR0_Pos)               /*!< EMAC_T::CAM9L: MACADDR0 Mask           */

#define EMAC_CAM9L_MACADDR1_Pos          (24)                                              /*!< EMAC_T::CAM9L: MACADDR1 Position       */
#define EMAC_CAM9L_MACADDR1_Msk          (0xfful << EMAC_CAM9L_MACADDR1_Pos)               /*!< EMAC_T::CAM9L: MACADDR1 Mask           */

#define EMAC_CAM10M_MACADDR2_Pos         (0)                                               /*!< EMAC_T::CAM10M: MACADDR2 Position      */
#define EMAC_CAM10M_MACADDR2_Msk         (0xfful << EMAC_CAM10M_MACADDR2_Pos)              /*!< EMAC_T::CAM10M: MACADDR2 Mask          */

#define EMAC_CAM10M_MACADDR3_Pos         (8)                                               /*!< EMAC_T::CAM10M: MACADDR3 Position      */
#define EMAC_CAM10M_MACADDR3_Msk         (0xfful << EMAC_CAM10M_MACADDR3_Pos)              /*!< EMAC_T::CAM10M: MACADDR3 Mask          */

#define EMAC_CAM10M_MACADDR4_Pos         (16)                                              /*!< EMAC_T::CAM10M: MACADDR4 Position      */
#define EMAC_CAM10M_MACADDR4_Msk         (0xfful << EMAC_CAM10M_MACADDR4_Pos)              /*!< EMAC_T::CAM10M: MACADDR4 Mask          */

#define EMAC_CAM10M_MACADDR5_Pos         (24)                                              /*!< EMAC_T::CAM10M: MACADDR5 Position      */
#define EMAC_CAM10M_MACADDR5_Msk         (0xfful << EMAC_CAM10M_MACADDR5_Pos)              /*!< EMAC_T::CAM10M: MACADDR5 Mask          */

#define EMAC_CAM10L_MACADDR0_Pos         (16)                                              /*!< EMAC_T::CAM10L: MACADDR0 Position      */
#define EMAC_CAM10L_MACADDR0_Msk         (0xfful << EMAC_CAM10L_MACADDR0_Pos)              /*!< EMAC_T::CAM10L: MACADDR0 Mask          */

#define EMAC_CAM10L_MACADDR1_Pos         (24)                                              /*!< EMAC_T::CAM10L: MACADDR1 Position      */
#define EMAC_CAM10L_MACADDR1_Msk         (0xfful << EMAC_CAM10L_MACADDR1_Pos)              /*!< EMAC_T::CAM10L: MACADDR1 Mask          */

#define EMAC_CAM11M_MACADDR2_Pos         (0)                                               /*!< EMAC_T::CAM11M: MACADDR2 Position      */
#define EMAC_CAM11M_MACADDR2_Msk         (0xfful << EMAC_CAM11M_MACADDR2_Pos)              /*!< EMAC_T::CAM11M: MACADDR2 Mask          */

#define EMAC_CAM11M_MACADDR3_Pos         (8)                                               /*!< EMAC_T::CAM11M: MACADDR3 Position      */
#define EMAC_CAM11M_MACADDR3_Msk         (0xfful << EMAC_CAM11M_MACADDR3_Pos)              /*!< EMAC_T::CAM11M: MACADDR3 Mask          */

#define EMAC_CAM11M_MACADDR4_Pos         (16)                                              /*!< EMAC_T::CAM11M: MACADDR4 Position      */
#define EMAC_CAM11M_MACADDR4_Msk         (0xfful << EMAC_CAM11M_MACADDR4_Pos)              /*!< EMAC_T::CAM11M: MACADDR4 Mask          */

#define EMAC_CAM11M_MACADDR5_Pos         (24)                                              /*!< EMAC_T::CAM11M: MACADDR5 Position      */
#define EMAC_CAM11M_MACADDR5_Msk         (0xfful << EMAC_CAM11M_MACADDR5_Pos)              /*!< EMAC_T::CAM11M: MACADDR5 Mask          */

#define EMAC_CAM11L_MACADDR0_Pos         (16)                                              /*!< EMAC_T::CAM11L: MACADDR0 Position      */
#define EMAC_CAM11L_MACADDR0_Msk         (0xfful << EMAC_CAM11L_MACADDR0_Pos)              /*!< EMAC_T::CAM11L: MACADDR0 Mask          */

#define EMAC_CAM11L_MACADDR1_Pos         (24)                                              /*!< EMAC_T::CAM11L: MACADDR1 Position      */
#define EMAC_CAM11L_MACADDR1_Msk         (0xfful << EMAC_CAM11L_MACADDR1_Pos)              /*!< EMAC_T::CAM11L: MACADDR1 Mask          */

#define EMAC_CAM12M_MACADDR2_Pos         (0)                                               /*!< EMAC_T::CAM12M: MACADDR2 Position      */
#define EMAC_CAM12M_MACADDR2_Msk         (0xfful << EMAC_CAM12M_MACADDR2_Pos)              /*!< EMAC_T::CAM12M: MACADDR2 Mask          */

#define EMAC_CAM12M_MACADDR3_Pos         (8)                                               /*!< EMAC_T::CAM12M: MACADDR3 Position      */
#define EMAC_CAM12M_MACADDR3_Msk         (0xfful << EMAC_CAM12M_MACADDR3_Pos)              /*!< EMAC_T::CAM12M: MACADDR3 Mask          */

#define EMAC_CAM12M_MACADDR4_Pos         (16)                                              /*!< EMAC_T::CAM12M: MACADDR4 Position      */
#define EMAC_CAM12M_MACADDR4_Msk         (0xfful << EMAC_CAM12M_MACADDR4_Pos)              /*!< EMAC_T::CAM12M: MACADDR4 Mask          */

#define EMAC_CAM12M_MACADDR5_Pos         (24)                                              /*!< EMAC_T::CAM12M: MACADDR5 Position      */
#define EMAC_CAM12M_MACADDR5_Msk         (0xfful << EMAC_CAM12M_MACADDR5_Pos)              /*!< EMAC_T::CAM12M: MACADDR5 Mask          */

#define EMAC_CAM12L_MACADDR0_Pos         (16)                                              /*!< EMAC_T::CAM12L: MACADDR0 Position      */
#define EMAC_CAM12L_MACADDR0_Msk         (0xfful << EMAC_CAM12L_MACADDR0_Pos)              /*!< EMAC_T::CAM12L: MACADDR0 Mask          */

#define EMAC_CAM12L_MACADDR1_Pos         (24)                                              /*!< EMAC_T::CAM12L: MACADDR1 Position      */
#define EMAC_CAM12L_MACADDR1_Msk         (0xfful << EMAC_CAM12L_MACADDR1_Pos)              /*!< EMAC_T::CAM12L: MACADDR1 Mask          */

#define EMAC_CAM13M_MACADDR2_Pos         (0)                                               /*!< EMAC_T::CAM13M: MACADDR2 Position      */
#define EMAC_CAM13M_MACADDR2_Msk         (0xfful << EMAC_CAM13M_MACADDR2_Pos)              /*!< EMAC_T::CAM13M: MACADDR2 Mask          */

#define EMAC_CAM13M_MACADDR3_Pos         (8)                                               /*!< EMAC_T::CAM13M: MACADDR3 Position      */
#define EMAC_CAM13M_MACADDR3_Msk         (0xfful << EMAC_CAM13M_MACADDR3_Pos)              /*!< EMAC_T::CAM13M: MACADDR3 Mask          */

#define EMAC_CAM13M_MACADDR4_Pos         (16)                                              /*!< EMAC_T::CAM13M: MACADDR4 Position      */
#define EMAC_CAM13M_MACADDR4_Msk         (0xfful << EMAC_CAM13M_MACADDR4_Pos)              /*!< EMAC_T::CAM13M: MACADDR4 Mask          */

#define EMAC_CAM13M_MACADDR5_Pos         (24)                                              /*!< EMAC_T::CAM13M: MACADDR5 Position      */
#define EMAC_CAM13M_MACADDR5_Msk         (0xfful << EMAC_CAM13M_MACADDR5_Pos)              /*!< EMAC_T::CAM13M: MACADDR5 Mask          */

#define EMAC_CAM13L_MACADDR0_Pos         (16)                                              /*!< EMAC_T::CAM13L: MACADDR0 Position      */
#define EMAC_CAM13L_MACADDR0_Msk         (0xfful << EMAC_CAM13L_MACADDR0_Pos)              /*!< EMAC_T::CAM13L: MACADDR0 Mask          */

#define EMAC_CAM13L_MACADDR1_Pos         (24)                                              /*!< EMAC_T::CAM13L: MACADDR1 Position      */
#define EMAC_CAM13L_MACADDR1_Msk         (0xfful << EMAC_CAM13L_MACADDR1_Pos)              /*!< EMAC_T::CAM13L: MACADDR1 Mask          */

#define EMAC_CAM14M_MACADDR2_Pos         (0)                                               /*!< EMAC_T::CAM14M: MACADDR2 Position      */
#define EMAC_CAM14M_MACADDR2_Msk         (0xfful << EMAC_CAM14M_MACADDR2_Pos)              /*!< EMAC_T::CAM14M: MACADDR2 Mask          */

#define EMAC_CAM14M_MACADDR3_Pos         (8)                                               /*!< EMAC_T::CAM14M: MACADDR3 Position      */
#define EMAC_CAM14M_MACADDR3_Msk         (0xfful << EMAC_CAM14M_MACADDR3_Pos)              /*!< EMAC_T::CAM14M: MACADDR3 Mask          */

#define EMAC_CAM14M_MACADDR4_Pos         (16)                                              /*!< EMAC_T::CAM14M: MACADDR4 Position      */
#define EMAC_CAM14M_MACADDR4_Msk         (0xfful << EMAC_CAM14M_MACADDR4_Pos)              /*!< EMAC_T::CAM14M: MACADDR4 Mask          */

#define EMAC_CAM14M_MACADDR5_Pos         (24)                                              /*!< EMAC_T::CAM14M: MACADDR5 Position      */
#define EMAC_CAM14M_MACADDR5_Msk         (0xfful << EMAC_CAM14M_MACADDR5_Pos)              /*!< EMAC_T::CAM14M: MACADDR5 Mask          */

#define EMAC_CAM14L_MACADDR0_Pos         (16)                                              /*!< EMAC_T::CAM14L: MACADDR0 Position      */
#define EMAC_CAM14L_MACADDR0_Msk         (0xfful << EMAC_CAM14L_MACADDR0_Pos)              /*!< EMAC_T::CAM14L: MACADDR0 Mask          */

#define EMAC_CAM14L_MACADDR1_Pos         (24)                                              /*!< EMAC_T::CAM14L: MACADDR1 Position      */
#define EMAC_CAM14L_MACADDR1_Msk         (0xfful << EMAC_CAM14L_MACADDR1_Pos)              /*!< EMAC_T::CAM14L: MACADDR1 Mask          */

#define EMAC_CAM15MSB_OPCODE_Pos         (0)                                               /*!< EMAC_T::CAM15MSB: OPCODE Position      */
#define EMAC_CAM15MSB_OPCODE_Msk         (0xfffful << EMAC_CAM15MSB_OPCODE_Pos)            /*!< EMAC_T::CAM15MSB: OPCODE Mask          */

#define EMAC_CAM15MSB_LENGTH_Pos         (16)                                              /*!< EMAC_T::CAM15MSB: LENGTH Position      */
#define EMAC_CAM15MSB_LENGTH_Msk         (0xfffful << EMAC_CAM15MSB_LENGTH_Pos)            /*!< EMAC_T::CAM15MSB: LENGTH Mask          */

#define EMAC_CAM15LSB_OPERAND_Pos        (24)                                              /*!< EMAC_T::CAM15LSB: OPERAND Position     */
#define EMAC_CAM15LSB_OPERAND_Msk        (0xfful << EMAC_CAM15LSB_OPERAND_Pos)             /*!< EMAC_T::CAM15LSB: OPERAND Mask         */

#define EMAC_TXDSA_TXDSA_Pos             (0)                                               /*!< EMAC_T::TXDSA: TXDSA Position          */
#define EMAC_TXDSA_TXDSA_Msk             (0xfffffffful << EMAC_TXDSA_TXDSA_Pos)            /*!< EMAC_T::TXDSA: TXDSA Mask              */

#define EMAC_RXDSA_RXDSA_Pos             (0)                                               /*!< EMAC_T::RXDSA: RXDSA Position          */
#define EMAC_RXDSA_RXDSA_Msk             (0xfffffffful << EMAC_RXDSA_RXDSA_Pos)            /*!< EMAC_T::RXDSA: RXDSA Mask              */

#define EMAC_CTL_RXON_Pos                (0)                                               /*!< EMAC_T::CTL: RXON Position             */
#define EMAC_CTL_RXON_Msk                (0x1ul << EMAC_CTL_RXON_Pos)                      /*!< EMAC_T::CTL: RXON Mask                 */

#define EMAC_CTL_ALP_Pos                 (1)                                               /*!< EMAC_T::CTL: ALP Position              */
#define EMAC_CTL_ALP_Msk                 (0x1ul << EMAC_CTL_ALP_Pos)                       /*!< EMAC_T::CTL: ALP Mask                  */

#define EMAC_CTL_ARP_Pos                 (2)                                               /*!< EMAC_T::CTL: ARP Position              */
#define EMAC_CTL_ARP_Msk                 (0x1ul << EMAC_CTL_ARP_Pos)                       /*!< EMAC_T::CTL: ARP Mask                  */

#define EMAC_CTL_ACP_Pos                 (3)                                               /*!< EMAC_T::CTL: ACP Position              */
#define EMAC_CTL_ACP_Msk                 (0x1ul << EMAC_CTL_ACP_Pos)                       /*!< EMAC_T::CTL: ACP Mask                  */

#define EMAC_CTL_AEP_Pos                 (4)                                               /*!< EMAC_T::CTL: AEP Position              */
#define EMAC_CTL_AEP_Msk                 (0x1ul << EMAC_CTL_AEP_Pos)                       /*!< EMAC_T::CTL: AEP Mask                  */

#define EMAC_CTL_STRIPCRC_Pos            (5)                                               /*!< EMAC_T::CTL: STRIPCRC Position         */
#define EMAC_CTL_STRIPCRC_Msk            (0x1ul << EMAC_CTL_STRIPCRC_Pos)                  /*!< EMAC_T::CTL: STRIPCRC Mask             */

#define EMAC_CTL_WOLEN_Pos               (6)                                               /*!< EMAC_T::CTL: WOLEN Position            */
#define EMAC_CTL_WOLEN_Msk               (0x1ul << EMAC_CTL_WOLEN_Pos)                     /*!< EMAC_T::CTL: WOLEN Mask                */

#define EMAC_CTL_TXON_Pos                (8)                                               /*!< EMAC_T::CTL: TXON Position             */
#define EMAC_CTL_TXON_Msk                (0x1ul << EMAC_CTL_TXON_Pos)                      /*!< EMAC_T::CTL: TXON Mask                 */

#define EMAC_CTL_NODEF_Pos               (9)                                               /*!< EMAC_T::CTL: NODEF Position            */
#define EMAC_CTL_NODEF_Msk               (0x1ul << EMAC_CTL_NODEF_Pos)                     /*!< EMAC_T::CTL: NODEF Mask                */

#define EMAC_CTL_SDPZ_Pos                (16)                                              /*!< EMAC_T::CTL: SDPZ Position             */
#define EMAC_CTL_SDPZ_Msk                (0x1ul << EMAC_CTL_SDPZ_Pos)                      /*!< EMAC_T::CTL: SDPZ Mask                 */

#define EMAC_CTL_SQECHKEN_Pos            (17)                                              /*!< EMAC_T::CTL: SQECHKEN Position         */
#define EMAC_CTL_SQECHKEN_Msk            (0x1ul << EMAC_CTL_SQECHKEN_Pos)                  /*!< EMAC_T::CTL: SQECHKEN Mask             */

#define EMAC_CTL_FUDUP_Pos               (18)                                              /*!< EMAC_T::CTL: FUDUP Position            */
#define EMAC_CTL_FUDUP_Msk               (0x1ul << EMAC_CTL_FUDUP_Pos)                     /*!< EMAC_T::CTL: FUDUP Mask                */

#define EMAC_CTL_RMIIRXCTL_Pos           (19)                                              /*!< EMAC_T::CTL: RMIIRXCTL Position        */
#define EMAC_CTL_RMIIRXCTL_Msk           (0x1ul << EMAC_CTL_RMIIRXCTL_Pos)                 /*!< EMAC_T::CTL: RMIIRXCTL Mask            */

#define EMAC_CTL_OPMODE_Pos              (20)                                              /*!< EMAC_T::CTL: OPMODE Position           */
#define EMAC_CTL_OPMODE_Msk              (0x1ul << EMAC_CTL_OPMODE_Pos)                    /*!< EMAC_T::CTL: OPMODE Mask               */

#define EMAC_CTL_RMIIEN_Pos              (22)                                              /*!< EMAC_T::CTL: RMIIEN Position           */
#define EMAC_CTL_RMIIEN_Msk              (0x1ul << EMAC_CTL_RMIIEN_Pos)                    /*!< EMAC_T::CTL: RMIIEN Mask               */

#define EMAC_CTL_RST_Pos                 (24)                                              /*!< EMAC_T::CTL: RST Position              */
#define EMAC_CTL_RST_Msk                 (0x1ul << EMAC_CTL_RST_Pos)                       /*!< EMAC_T::CTL: RST Mask                  */

#define EMAC_MIIMDAT_DATA_Pos            (0)                                               /*!< EMAC_T::MIIMDAT: DATA Position         */
#define EMAC_MIIMDAT_DATA_Msk            (0xfffful << EMAC_MIIMDAT_DATA_Pos)               /*!< EMAC_T::MIIMDAT: DATA Mask             */

#define EMAC_MIIMCTL_PHYREG_Pos          (0)                                               /*!< EMAC_T::MIIMCTL: PHYREG Position       */
#define EMAC_MIIMCTL_PHYREG_Msk          (0x1ful << EMAC_MIIMCTL_PHYREG_Pos)               /*!< EMAC_T::MIIMCTL: PHYREG Mask           */

#define EMAC_MIIMCTL_PHYADDR_Pos         (8)                                               /*!< EMAC_T::MIIMCTL: PHYADDR Position      */
#define EMAC_MIIMCTL_PHYADDR_Msk         (0x1ful << EMAC_MIIMCTL_PHYADDR_Pos)              /*!< EMAC_T::MIIMCTL: PHYADDR Mask          */

#define EMAC_MIIMCTL_WRITE_Pos           (16)                                              /*!< EMAC_T::MIIMCTL: WRITE Position        */
#define EMAC_MIIMCTL_WRITE_Msk           (0x1ul << EMAC_MIIMCTL_WRITE_Pos)                 /*!< EMAC_T::MIIMCTL: WRITE Mask            */

#define EMAC_MIIMCTL_BUSY_Pos            (17)                                              /*!< EMAC_T::MIIMCTL: BUSY Position         */
#define EMAC_MIIMCTL_BUSY_Msk            (0x1ul << EMAC_MIIMCTL_BUSY_Pos)                  /*!< EMAC_T::MIIMCTL: BUSY Mask             */

#define EMAC_MIIMCTL_PREAMSP_Pos         (18)                                              /*!< EMAC_T::MIIMCTL: PREAMSP Position      */
#define EMAC_MIIMCTL_PREAMSP_Msk         (0x1ul << EMAC_MIIMCTL_PREAMSP_Pos)               /*!< EMAC_T::MIIMCTL: PREAMSP Mask          */

#define EMAC_MIIMCTL_MDCON_Pos           (19)                                              /*!< EMAC_T::MIIMCTL: MDCON Position        */
#define EMAC_MIIMCTL_MDCON_Msk           (0x1ul << EMAC_MIIMCTL_MDCON_Pos)                 /*!< EMAC_T::MIIMCTL: MDCON Mask            */

#define EMAC_FIFOCTL_RXFIFOTH_Pos        (0)                                               /*!< EMAC_T::FIFOCTL: RXFIFOTH Position     */
#define EMAC_FIFOCTL_RXFIFOTH_Msk        (0x3ul << EMAC_FIFOCTL_RXFIFOTH_Pos)              /*!< EMAC_T::FIFOCTL: RXFIFOTH Mask         */

#define EMAC_FIFOCTL_TXFIFOTH_Pos        (8)                                               /*!< EMAC_T::FIFOCTL: TXFIFOTH Position     */
#define EMAC_FIFOCTL_TXFIFOTH_Msk        (0x3ul << EMAC_FIFOCTL_TXFIFOTH_Pos)              /*!< EMAC_T::FIFOCTL: TXFIFOTH Mask         */

#define EMAC_FIFOCTL_BURSTLEN_Pos        (20)                                              /*!< EMAC_T::FIFOCTL: BURSTLEN Position     */
#define EMAC_FIFOCTL_BURSTLEN_Msk        (0x3ul << EMAC_FIFOCTL_BURSTLEN_Pos)              /*!< EMAC_T::FIFOCTL: BURSTLEN Mask         */

#define EMAC_TXST_TXST_Pos               (0)                                               /*!< EMAC_T::TXST: TXST Position            */
#define EMAC_TXST_TXST_Msk               (0xfffffffful << EMAC_TXST_TXST_Pos)              /*!< EMAC_T::TXST: TXST Mask                */

#define EMAC_RXST_RXST_Pos               (0)                                               /*!< EMAC_T::RXST: RXST Position            */
#define EMAC_RXST_RXST_Msk               (0xfffffffful << EMAC_RXST_RXST_Pos)              /*!< EMAC_T::RXST: RXST Mask                */

#define EMAC_MRFL_MRFL_Pos               (0)                                               /*!< EMAC_T::MRFL: MRFL Position            */
#define EMAC_MRFL_MRFL_Msk               (0xfffful << EMAC_MRFL_MRFL_Pos)                  /*!< EMAC_T::MRFL: MRFL Mask                */

#define EMAC_INTEN_RXIEN_Pos             (0)                                               /*!< EMAC_T::INTEN: RXIEN Position          */
#define EMAC_INTEN_RXIEN_Msk             (0x1ul << EMAC_INTEN_RXIEN_Pos)                   /*!< EMAC_T::INTEN: RXIEN Mask              */

#define EMAC_INTEN_CRCEIEN_Pos           (1)                                               /*!< EMAC_T::INTEN: CRCEIEN Position        */
#define EMAC_INTEN_CRCEIEN_Msk           (0x1ul << EMAC_INTEN_CRCEIEN_Pos)                 /*!< EMAC_T::INTEN: CRCEIEN Mask            */

#define EMAC_INTEN_RXOVIEN_Pos           (2)                                               /*!< EMAC_T::INTEN: RXOVIEN Position        */
#define EMAC_INTEN_RXOVIEN_Msk           (0x1ul << EMAC_INTEN_RXOVIEN_Pos)                 /*!< EMAC_T::INTEN: RXOVIEN Mask            */

#define EMAC_INTEN_LPIEN_Pos             (3)                                               /*!< EMAC_T::INTEN: LPIEN Position          */
#define EMAC_INTEN_LPIEN_Msk             (0x1ul << EMAC_INTEN_LPIEN_Pos)                   /*!< EMAC_T::INTEN: LPIEN Mask              */

#define EMAC_INTEN_RXGDIEN_Pos           (4)                                               /*!< EMAC_T::INTEN: RXGDIEN Position        */
#define EMAC_INTEN_RXGDIEN_Msk           (0x1ul << EMAC_INTEN_RXGDIEN_Pos)                 /*!< EMAC_T::INTEN: RXGDIEN Mask            */

#define EMAC_INTEN_ALIEIEN_Pos           (5)                                               /*!< EMAC_T::INTEN: ALIEIEN Position        */
#define EMAC_INTEN_ALIEIEN_Msk           (0x1ul << EMAC_INTEN_ALIEIEN_Pos)                 /*!< EMAC_T::INTEN: ALIEIEN Mask            */

#define EMAC_INTEN_RPIEN_Pos             (6)                                               /*!< EMAC_T::INTEN: RPIEN Position          */
#define EMAC_INTEN_RPIEN_Msk             (0x1ul << EMAC_INTEN_RPIEN_Pos)                   /*!< EMAC_T::INTEN: RPIEN Mask              */

#define EMAC_INTEN_MPCOVIEN_Pos          (7)                                               /*!< EMAC_T::INTEN: MPCOVIEN Position       */
#define EMAC_INTEN_MPCOVIEN_Msk          (0x1ul << EMAC_INTEN_MPCOVIEN_Pos)                /*!< EMAC_T::INTEN: MPCOVIEN Mask           */

#define EMAC_INTEN_MFLEIEN_Pos           (8)                                               /*!< EMAC_T::INTEN: MFLEIEN Position        */
#define EMAC_INTEN_MFLEIEN_Msk           (0x1ul << EMAC_INTEN_MFLEIEN_Pos)                 /*!< EMAC_T::INTEN: MFLEIEN Mask            */

#define EMAC_INTEN_DENIEN_Pos            (9)                                               /*!< EMAC_T::INTEN: DENIEN Position         */
#define EMAC_INTEN_DENIEN_Msk            (0x1ul << EMAC_INTEN_DENIEN_Pos)                  /*!< EMAC_T::INTEN: DENIEN Mask             */

#define EMAC_INTEN_RDUIEN_Pos            (10)                                              /*!< EMAC_T::INTEN: RDUIEN Position         */
#define EMAC_INTEN_RDUIEN_Msk            (0x1ul << EMAC_INTEN_RDUIEN_Pos)                  /*!< EMAC_T::INTEN: RDUIEN Mask             */

#define EMAC_INTEN_RXBEIEN_Pos           (11)                                              /*!< EMAC_T::INTEN: RXBEIEN Position        */
#define EMAC_INTEN_RXBEIEN_Msk           (0x1ul << EMAC_INTEN_RXBEIEN_Pos)                 /*!< EMAC_T::INTEN: RXBEIEN Mask            */

#define EMAC_INTEN_CFRIEN_Pos            (14)                                              /*!< EMAC_T::INTEN: CFRIEN Position         */
#define EMAC_INTEN_CFRIEN_Msk            (0x1ul << EMAC_INTEN_CFRIEN_Pos)                  /*!< EMAC_T::INTEN: CFRIEN Mask             */

#define EMAC_INTEN_WOLIEN_Pos            (15)                                              /*!< EMAC_T::INTEN: WOLIEN Position         */
#define EMAC_INTEN_WOLIEN_Msk            (0x1ul << EMAC_INTEN_WOLIEN_Pos)                  /*!< EMAC_T::INTEN: WOLIEN Mask             */

#define EMAC_INTEN_TXIEN_Pos             (16)                                              /*!< EMAC_T::INTEN: TXIEN Position          */
#define EMAC_INTEN_TXIEN_Msk             (0x1ul << EMAC_INTEN_TXIEN_Pos)                   /*!< EMAC_T::INTEN: TXIEN Mask              */

#define EMAC_INTEN_TXUDIEN_Pos           (17)                                              /*!< EMAC_T::INTEN: TXUDIEN Position        */
#define EMAC_INTEN_TXUDIEN_Msk           (0x1ul << EMAC_INTEN_TXUDIEN_Pos)                 /*!< EMAC_T::INTEN: TXUDIEN Mask            */

#define EMAC_INTEN_TXCPIEN_Pos           (18)                                              /*!< EMAC_T::INTEN: TXCPIEN Position        */
#define EMAC_INTEN_TXCPIEN_Msk           (0x1ul << EMAC_INTEN_TXCPIEN_Pos)                 /*!< EMAC_T::INTEN: TXCPIEN Mask            */

#define EMAC_INTEN_EXDEFIEN_Pos          (19)                                              /*!< EMAC_T::INTEN: EXDEFIEN Position       */
#define EMAC_INTEN_EXDEFIEN_Msk          (0x1ul << EMAC_INTEN_EXDEFIEN_Pos)                /*!< EMAC_T::INTEN: EXDEFIEN Mask           */

#define EMAC_INTEN_NCSIEN_Pos            (20)                                              /*!< EMAC_T::INTEN: NCSIEN Position         */
#define EMAC_INTEN_NCSIEN_Msk            (0x1ul << EMAC_INTEN_NCSIEN_Pos)                  /*!< EMAC_T::INTEN: NCSIEN Mask             */

#define EMAC_INTEN_TXABTIEN_Pos          (21)                                              /*!< EMAC_T::INTEN: TXABTIEN Position       */
#define EMAC_INTEN_TXABTIEN_Msk          (0x1ul << EMAC_INTEN_TXABTIEN_Pos)                /*!< EMAC_T::INTEN: TXABTIEN Mask           */

#define EMAC_INTEN_LCIEN_Pos             (22)                                              /*!< EMAC_T::INTEN: LCIEN Position          */
#define EMAC_INTEN_LCIEN_Msk             (0x1ul << EMAC_INTEN_LCIEN_Pos)                   /*!< EMAC_T::INTEN: LCIEN Mask              */

#define EMAC_INTEN_TDUIEN_Pos            (23)                                              /*!< EMAC_T::INTEN: TDUIEN Position         */
#define EMAC_INTEN_TDUIEN_Msk            (0x1ul << EMAC_INTEN_TDUIEN_Pos)                  /*!< EMAC_T::INTEN: TDUIEN Mask             */

#define EMAC_INTEN_TXBEIEN_Pos           (24)                                              /*!< EMAC_T::INTEN: TXBEIEN Position        */
#define EMAC_INTEN_TXBEIEN_Msk           (0x1ul << EMAC_INTEN_TXBEIEN_Pos)                 /*!< EMAC_T::INTEN: TXBEIEN Mask            */

#define EMAC_INTEN_TSALMIEN_Pos          (28)                                              /*!< EMAC_T::INTEN: TSALMIEN Position       */
#define EMAC_INTEN_TSALMIEN_Msk          (0x1ul << EMAC_INTEN_TSALMIEN_Pos)                /*!< EMAC_T::INTEN: TSALMIEN Mask           */

#define EMAC_INTSTS_RXIF_Pos             (0)                                               /*!< EMAC_T::INTSTS: RXIF Position          */
#define EMAC_INTSTS_RXIF_Msk             (0x1ul << EMAC_INTSTS_RXIF_Pos)                   /*!< EMAC_T::INTSTS: RXIF Mask              */

#define EMAC_INTSTS_CRCEIF_Pos           (1)                                               /*!< EMAC_T::INTSTS: CRCEIF Position        */
#define EMAC_INTSTS_CRCEIF_Msk           (0x1ul << EMAC_INTSTS_CRCEIF_Pos)                 /*!< EMAC_T::INTSTS: CRCEIF Mask            */

#define EMAC_INTSTS_RXOVIF_Pos           (2)                                               /*!< EMAC_T::INTSTS: RXOVIF Position        */
#define EMAC_INTSTS_RXOVIF_Msk           (0x1ul << EMAC_INTSTS_RXOVIF_Pos)                 /*!< EMAC_T::INTSTS: RXOVIF Mask            */

#define EMAC_INTSTS_LPIF_Pos             (3)                                               /*!< EMAC_T::INTSTS: LPIF Position          */
#define EMAC_INTSTS_LPIF_Msk             (0x1ul << EMAC_INTSTS_LPIF_Pos)                   /*!< EMAC_T::INTSTS: LPIF Mask              */

#define EMAC_INTSTS_RXGDIF_Pos           (4)                                               /*!< EMAC_T::INTSTS: RXGDIF Position        */
#define EMAC_INTSTS_RXGDIF_Msk           (0x1ul << EMAC_INTSTS_RXGDIF_Pos)                 /*!< EMAC_T::INTSTS: RXGDIF Mask            */

#define EMAC_INTSTS_ALIEIF_Pos           (5)                                               /*!< EMAC_T::INTSTS: ALIEIF Position        */
#define EMAC_INTSTS_ALIEIF_Msk           (0x1ul << EMAC_INTSTS_ALIEIF_Pos)                 /*!< EMAC_T::INTSTS: ALIEIF Mask            */

#define EMAC_INTSTS_RPIF_Pos             (6)                                               /*!< EMAC_T::INTSTS: RPIF Position          */
#define EMAC_INTSTS_RPIF_Msk             (0x1ul << EMAC_INTSTS_RPIF_Pos)                   /*!< EMAC_T::INTSTS: RPIF Mask              */

#define EMAC_INTSTS_MPCOVIF_Pos          (7)                                               /*!< EMAC_T::INTSTS: MPCOVIF Position       */
#define EMAC_INTSTS_MPCOVIF_Msk          (0x1ul << EMAC_INTSTS_MPCOVIF_Pos)                /*!< EMAC_T::INTSTS: MPCOVIF Mask           */

#define EMAC_INTSTS_MFLEIF_Pos           (8)                                               /*!< EMAC_T::INTSTS: MFLEIF Position        */
#define EMAC_INTSTS_MFLEIF_Msk           (0x1ul << EMAC_INTSTS_MFLEIF_Pos)                 /*!< EMAC_T::INTSTS: MFLEIF Mask            */

#define EMAC_INTSTS_DENIF_Pos            (9)                                               /*!< EMAC_T::INTSTS: DENIF Position         */
#define EMAC_INTSTS_DENIF_Msk            (0x1ul << EMAC_INTSTS_DENIF_Pos)                  /*!< EMAC_T::INTSTS: DENIF Mask             */

#define EMAC_INTSTS_RDUIF_Pos            (10)                                              /*!< EMAC_T::INTSTS: RDUIF Position         */
#define EMAC_INTSTS_RDUIF_Msk            (0x1ul << EMAC_INTSTS_RDUIF_Pos)                  /*!< EMAC_T::INTSTS: RDUIF Mask             */

#define EMAC_INTSTS_RXBEIF_Pos           (11)                                              /*!< EMAC_T::INTSTS: RXBEIF Position        */
#define EMAC_INTSTS_RXBEIF_Msk           (0x1ul << EMAC_INTSTS_RXBEIF_Pos)                 /*!< EMAC_T::INTSTS: RXBEIF Mask            */

#define EMAC_INTSTS_CFRIF_Pos            (14)                                              /*!< EMAC_T::INTSTS: CFRIF Position         */
#define EMAC_INTSTS_CFRIF_Msk            (0x1ul << EMAC_INTSTS_CFRIF_Pos)                  /*!< EMAC_T::INTSTS: CFRIF Mask             */

#define EMAC_INTSTS_WOLIF_Pos            (15)                                              /*!< EMAC_T::INTSTS: WOLIF Position         */
#define EMAC_INTSTS_WOLIF_Msk            (0x1ul << EMAC_INTSTS_WOLIF_Pos)                  /*!< EMAC_T::INTSTS: WOLIF Mask             */

#define EMAC_INTSTS_TXIF_Pos             (16)                                              /*!< EMAC_T::INTSTS: TXIF Position          */
#define EMAC_INTSTS_TXIF_Msk             (0x1ul << EMAC_INTSTS_TXIF_Pos)                   /*!< EMAC_T::INTSTS: TXIF Mask              */

#define EMAC_INTSTS_TXUDIF_Pos           (17)                                              /*!< EMAC_T::INTSTS: TXUDIF Position        */
#define EMAC_INTSTS_TXUDIF_Msk           (0x1ul << EMAC_INTSTS_TXUDIF_Pos)                 /*!< EMAC_T::INTSTS: TXUDIF Mask            */

#define EMAC_INTSTS_TXCPIF_Pos           (18)                                              /*!< EMAC_T::INTSTS: TXCPIF Position        */
#define EMAC_INTSTS_TXCPIF_Msk           (0x1ul << EMAC_INTSTS_TXCPIF_Pos)                 /*!< EMAC_T::INTSTS: TXCPIF Mask            */

#define EMAC_INTSTS_EXDEFIF_Pos          (19)                                              /*!< EMAC_T::INTSTS: EXDEFIF Position       */
#define EMAC_INTSTS_EXDEFIF_Msk          (0x1ul << EMAC_INTSTS_EXDEFIF_Pos)                /*!< EMAC_T::INTSTS: EXDEFIF Mask           */

#define EMAC_INTSTS_NCSIF_Pos            (20)                                              /*!< EMAC_T::INTSTS: NCSIF Position         */
#define EMAC_INTSTS_NCSIF_Msk            (0x1ul << EMAC_INTSTS_NCSIF_Pos)                  /*!< EMAC_T::INTSTS: NCSIF Mask             */

#define EMAC_INTSTS_TXABTIF_Pos          (21)                                              /*!< EMAC_T::INTSTS: TXABTIF Position       */
#define EMAC_INTSTS_TXABTIF_Msk          (0x1ul << EMAC_INTSTS_TXABTIF_Pos)                /*!< EMAC_T::INTSTS: TXABTIF Mask           */

#define EMAC_INTSTS_LCIF_Pos             (22)                                              /*!< EMAC_T::INTSTS: LCIF Position          */
#define EMAC_INTSTS_LCIF_Msk             (0x1ul << EMAC_INTSTS_LCIF_Pos)                   /*!< EMAC_T::INTSTS: LCIF Mask              */

#define EMAC_INTSTS_TDUIF_Pos            (23)                                              /*!< EMAC_T::INTSTS: TDUIF Position         */
#define EMAC_INTSTS_TDUIF_Msk            (0x1ul << EMAC_INTSTS_TDUIF_Pos)                  /*!< EMAC_T::INTSTS: TDUIF Mask             */

#define EMAC_INTSTS_TXBEIF_Pos           (24)                                              /*!< EMAC_T::INTSTS: TXBEIF Position        */
#define EMAC_INTSTS_TXBEIF_Msk           (0x1ul << EMAC_INTSTS_TXBEIF_Pos)                 /*!< EMAC_T::INTSTS: TXBEIF Mask            */

#define EMAC_INTSTS_TSALMIF_Pos          (28)                                              /*!< EMAC_T::INTSTS: TSALMIF Position       */
#define EMAC_INTSTS_TSALMIF_Msk          (0x1ul << EMAC_INTSTS_TSALMIF_Pos)                /*!< EMAC_T::INTSTS: TSALMIF Mask           */

#define EMAC_GENSTS_CFR_Pos              (0)                                               /*!< EMAC_T::GENSTS: CFR Position           */
#define EMAC_GENSTS_CFR_Msk              (0x1ul << EMAC_GENSTS_CFR_Pos)                    /*!< EMAC_T::GENSTS: CFR Mask               */

#define EMAC_GENSTS_RXHALT_Pos           (1)                                               /*!< EMAC_T::GENSTS: RXHALT Position        */
#define EMAC_GENSTS_RXHALT_Msk           (0x1ul << EMAC_GENSTS_RXHALT_Pos)                 /*!< EMAC_T::GENSTS: RXHALT Mask            */

#define EMAC_GENSTS_RXFFULL_Pos          (2)                                               /*!< EMAC_T::GENSTS: RXFFULL Position       */
#define EMAC_GENSTS_RXFFULL_Msk          (0x1ul << EMAC_GENSTS_RXFFULL_Pos)                /*!< EMAC_T::GENSTS: RXFFULL Mask           */

#define EMAC_GENSTS_COLCNT_Pos           (4)                                               /*!< EMAC_T::GENSTS: COLCNT Position        */
#define EMAC_GENSTS_COLCNT_Msk           (0xful << EMAC_GENSTS_COLCNT_Pos)                 /*!< EMAC_T::GENSTS: COLCNT Mask            */

#define EMAC_GENSTS_DEF_Pos              (8)                                               /*!< EMAC_T::GENSTS: DEF Position           */
#define EMAC_GENSTS_DEF_Msk              (0x1ul << EMAC_GENSTS_DEF_Pos)                    /*!< EMAC_T::GENSTS: DEF Mask               */

#define EMAC_GENSTS_TXPAUSED_Pos         (9)                                               /*!< EMAC_T::GENSTS: TXPAUSED Position      */
#define EMAC_GENSTS_TXPAUSED_Msk         (0x1ul << EMAC_GENSTS_TXPAUSED_Pos)               /*!< EMAC_T::GENSTS: TXPAUSED Mask          */

#define EMAC_GENSTS_SQE_Pos              (10)                                              /*!< EMAC_T::GENSTS: SQE Position           */
#define EMAC_GENSTS_SQE_Msk              (0x1ul << EMAC_GENSTS_SQE_Pos)                    /*!< EMAC_T::GENSTS: SQE Mask               */

#define EMAC_GENSTS_TXHALT_Pos           (11)                                              /*!< EMAC_T::GENSTS: TXHALT Position        */
#define EMAC_GENSTS_TXHALT_Msk           (0x1ul << EMAC_GENSTS_TXHALT_Pos)                 /*!< EMAC_T::GENSTS: TXHALT Mask            */

#define EMAC_GENSTS_RPSTS_Pos            (12)                                              /*!< EMAC_T::GENSTS: RPSTS Position         */
#define EMAC_GENSTS_RPSTS_Msk            (0x1ul << EMAC_GENSTS_RPSTS_Pos)                  /*!< EMAC_T::GENSTS: RPSTS Mask             */

#define EMAC_MPCNT_MPCNT_Pos             (0)                                               /*!< EMAC_T::MPCNT: MPCNT Position          */
#define EMAC_MPCNT_MPCNT_Msk             (0xfffful << EMAC_MPCNT_MPCNT_Pos)                /*!< EMAC_T::MPCNT: MPCNT Mask              */

#define EMAC_RPCNT_RPCNT_Pos             (0)                                               /*!< EMAC_T::RPCNT: RPCNT Position          */
#define EMAC_RPCNT_RPCNT_Msk             (0xfffful << EMAC_RPCNT_RPCNT_Pos)                /*!< EMAC_T::RPCNT: RPCNT Mask              */

#define EMAC_FRSTS_RXFLT_Pos             (0)                                               /*!< EMAC_T::FRSTS: RXFLT Position          */
#define EMAC_FRSTS_RXFLT_Msk             (0xfffful << EMAC_FRSTS_RXFLT_Pos)                /*!< EMAC_T::FRSTS: RXFLT Mask              */

#define EMAC_CTXDSA_CTXDSA_Pos           (0)                                               /*!< EMAC_T::CTXDSA: CTXDSA Position        */
#define EMAC_CTXDSA_CTXDSA_Msk           (0xfffffffful << EMAC_CTXDSA_CTXDSA_Pos)          /*!< EMAC_T::CTXDSA: CTXDSA Mask            */

#define EMAC_CTXBSA_CTXBSA_Pos           (0)                                               /*!< EMAC_T::CTXBSA: CTXBSA Position        */
#define EMAC_CTXBSA_CTXBSA_Msk           (0xfffffffful << EMAC_CTXBSA_CTXBSA_Pos)          /*!< EMAC_T::CTXBSA: CTXBSA Mask            */

#define EMAC_CRXDSA_CRXDSA_Pos           (0)                                               /*!< EMAC_T::CRXDSA: CRXDSA Position        */
#define EMAC_CRXDSA_CRXDSA_Msk           (0xfffffffful << EMAC_CRXDSA_CRXDSA_Pos)          /*!< EMAC_T::CRXDSA: CRXDSA Mask            */

#define EMAC_CRXBSA_CRXBSA_Pos           (0)                                               /*!< EMAC_T::CRXBSA: CRXBSA Position        */
#define EMAC_CRXBSA_CRXBSA_Msk           (0xfffffffful << EMAC_CRXBSA_CRXBSA_Pos)          /*!< EMAC_T::CRXBSA: CRXBSA Mask            */

#define EMAC_TSCTL_TSEN_Pos              (0)                                               /*!< EMAC_T::TSCTL: TSEN Position           */
#define EMAC_TSCTL_TSEN_Msk              (0x1ul << EMAC_TSCTL_TSEN_Pos)                    /*!< EMAC_T::TSCTL: TSEN Mask               */

#define EMAC_TSCTL_TSIEN_Pos             (1)                                               /*!< EMAC_T::TSCTL: TSIEN Position          */
#define EMAC_TSCTL_TSIEN_Msk             (0x1ul << EMAC_TSCTL_TSIEN_Pos)                   /*!< EMAC_T::TSCTL: TSIEN Mask              */

#define EMAC_TSCTL_TSMODE_Pos            (2)                                               /*!< EMAC_T::TSCTL: TSMODE Position         */
#define EMAC_TSCTL_TSMODE_Msk            (0x1ul << EMAC_TSCTL_TSMODE_Pos)                  /*!< EMAC_T::TSCTL: TSMODE Mask             */

#define EMAC_TSCTL_TSUPDATE_Pos          (3)                                               /*!< EMAC_T::TSCTL: TSUPDATE Position       */
#define EMAC_TSCTL_TSUPDATE_Msk          (0x1ul << EMAC_TSCTL_TSUPDATE_Pos)                /*!< EMAC_T::TSCTL: TSUPDATE Mask           */

#define EMAC_TSCTL_TSALMEN_Pos           (5)                                               /*!< EMAC_T::TSCTL: TSALMEN Position        */
#define EMAC_TSCTL_TSALMEN_Msk           (0x1ul << EMAC_TSCTL_TSALMEN_Pos)                 /*!< EMAC_T::TSCTL: TSALMEN Mask            */

#define EMAC_TSSEC_SEC_Pos               (0)                                               /*!< EMAC_T::TSSEC: SEC Position            */
#define EMAC_TSSEC_SEC_Msk               (0xfffffffful << EMAC_TSSEC_SEC_Pos)              /*!< EMAC_T::TSSEC: SEC Mask                */

#define EMAC_TSSUBSEC_SUBSEC_Pos         (0)                                               /*!< EMAC_T::TSSUBSEC: SUBSEC Position      */
#define EMAC_TSSUBSEC_SUBSEC_Msk         (0xfffffffful << EMAC_TSSUBSEC_SUBSEC_Pos)        /*!< EMAC_T::TSSUBSEC: SUBSEC Mask          */

#define EMAC_TSINC_CNTINC_Pos            (0)                                               /*!< EMAC_T::TSINC: CNTINC Position         */
#define EMAC_TSINC_CNTINC_Msk            (0xfful << EMAC_TSINC_CNTINC_Pos)                 /*!< EMAC_T::TSINC: CNTINC Mask             */

#define EMAC_TSADDEND_ADDEND_Pos         (0)                                               /*!< EMAC_T::TSADDEND: ADDEND Position      */
#define EMAC_TSADDEND_ADDEND_Msk         (0xfffffffful << EMAC_TSADDEND_ADDEND_Pos)        /*!< EMAC_T::TSADDEND: ADDEND Mask          */

#define EMAC_UPDSEC_SEC_Pos              (0)                                               /*!< EMAC_T::UPDSEC: SEC Position           */
#define EMAC_UPDSEC_SEC_Msk              (0xfffffffful << EMAC_UPDSEC_SEC_Pos)             /*!< EMAC_T::UPDSEC: SEC Mask               */

#define EMAC_UPDSUBSEC_SUBSEC_Pos        (0)                                               /*!< EMAC_T::UPDSUBSEC: SUBSEC Position     */
#define EMAC_UPDSUBSEC_SUBSEC_Msk        (0xfffffffful << EMAC_UPDSUBSEC_SUBSEC_Pos)       /*!< EMAC_T::UPDSUBSEC: SUBSEC Mask         */

#define EMAC_ALMSEC_SEC_Pos              (0)                                               /*!< EMAC_T::ALMSEC: SEC Position           */
#define EMAC_ALMSEC_SEC_Msk              (0xfffffffful << EMAC_ALMSEC_SEC_Pos)             /*!< EMAC_T::ALMSEC: SEC Mask               */

#define EMAC_ALMSUBSEC_SUBSEC_Pos        (0)                                               /*!< EMAC_T::ALMSUBSEC: SUBSEC Position     */
#define EMAC_ALMSUBSEC_SUBSEC_Msk        (0xfffffffful << EMAC_ALMSUBSEC_SUBSEC_Pos)       /*!< EMAC_T::ALMSUBSEC: SUBSEC Mask         */

/**@}*/ /* EMAC_CONST */
/**@}*/ /* end of EMAC register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __EMAC_REG_H__ */
