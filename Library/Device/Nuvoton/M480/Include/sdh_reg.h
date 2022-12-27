/**************************************************************************//**
 * @file     sdh_reg.h
 * @version  V1.00
 * @brief    SDH register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __SDH_REG_H__
#define __SDH_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup SDH SD Card Host Interface(SDH)
    Memory Mapped Structure for SDH Controller
@{ */

typedef struct
{

    /**
@var SDH_T::FB

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">FB
</font><br><p> <font size="2">
Offset: 0x00~0x7C  Shared Buffer (FIFO)
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>BUFFER</td><td><div style="word-wrap: break-word;"><b>Shared Buffer
</b><br>
Buffer for DMA transfer
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SDH_T::DMACTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DMACTL
</font><br><p> <font size="2">
Offset: 0x400  DMA Control and Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>DMAEN</td><td><div style="word-wrap: break-word;"><b>DMA Engine Enable Bit
</b><br>
0 = DMA Disabled.
<br>
1 = DMA Enabled.
<br>
If this bit is cleared, DMA will ignore all requests from SD host and force bus master into IDLE state.
<br>
Note: If target abort is occurred, DMAEN will be cleared.
<br>
</div></td></tr><tr><td>
[1]</td><td>DMARST</td><td><div style="word-wrap: break-word;"><b>Software Engine Reset
</b><br>
0 = No effect.
<br>
1 = Reset internal state machine and pointers
<br>
The contents of control register will not be cleared
<br>
This bit will auto be cleared after few clock cycles.
<br>
Note: The software reset DMA related registers.
<br>
</div></td></tr><tr><td>
[3]</td><td>SGEN</td><td><div style="word-wrap: break-word;"><b>Scatter-gather Function Enable Bit
</b><br>
0 = Scatter-gather function Disabled (DMA will treat the starting address in DMASAR as starting pointer of a single block memory).
<br>
1 = Scatter-gather function Enabled (DMA will treat the starting address in DMASAR as a starting address of Physical Address Descriptor (PAD) table
<br>
The format of these Pads' will be described later).
<br>
</div></td></tr><tr><td>
[9]</td><td>DMABUSY</td><td><div style="word-wrap: break-word;"><b>DMA Transfer Is in Progress
</b><br>
This bit indicates if SD Host is granted and doing DMA transfer or not.
<br>
0 = DMA transfer is not in progress.
<br>
1 = DMA transfer is in progress.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SDH_T::DMASA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DMASA
</font><br><p> <font size="2">
Offset: 0x408  DMA Transfer Starting Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ORDER</td><td><div style="word-wrap: break-word;"><b>Determined to the PAD Table Fetching Is in Order or Out of Order
</b><br>
0 = PAD table is fetched in order.
<br>
1 = PAD table is fetched out of order.
<br>
Note: the bit0 is valid in scatter-gather mode when SGEN = 1.
<br>
</div></td></tr><tr><td>
[31:1]</td><td>DMASA</td><td><div style="word-wrap: break-word;"><b>DMA Transfer Starting Address
</b><br>
This field pads 0 as least significant bit indicates a 32-bit starting address of system memory (SRAM) for DMA to retrieve or fill in data.
<br>
If DMA is not in normal mode, this field will be interpreted as a starting address of Physical Address Descriptor (PAD) table.
<br>
Note: Starting address of the SRAM must be word aligned, for example, 0x0000_0000, 0x0000_0004.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SDH_T::DMABCNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DMABCNT
</font><br><p> <font size="2">
Offset: 0x40C  DMA Transfer Byte Count Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[25:0]</td><td>BCNT</td><td><div style="word-wrap: break-word;"><b>DMA Transfer Byte Count (Read Only)
</b><br>
This field indicates the remained byte count of DMA transfer
<br>
The value of this field is valid only when DMA is busy; otherwise, it is 0.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SDH_T::DMAINTEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DMAINTEN
</font><br><p> <font size="2">
Offset: 0x410  DMA Interrupt Enable Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ABORTIEN</td><td><div style="word-wrap: break-word;"><b>DMA Read/Write Target Abort Interrupt Enable Bit
</b><br>
0 = Target abort interrupt generation Disabled during DMA transfer.
<br>
1 = Target abort interrupt generation Enabled during DMA transfer.
<br>
</div></td></tr><tr><td>
[1]</td><td>WEOTIEN</td><td><div style="word-wrap: break-word;"><b>Wrong EOT Encountered Interrupt Enable Bit
</b><br>
0 = Interrupt generation Disabled when wrong EOT is encountered.
<br>
1 = Interrupt generation Enabled when wrong EOT is encountered.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SDH_T::DMAINTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DMAINTSTS
</font><br><p> <font size="2">
Offset: 0x414  DMA Interrupt Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ABORTIF</td><td><div style="word-wrap: break-word;"><b>DMA Read/Write Target Abort Interrupt Flag
</b><br>
0 = No bus ERROR response received.
<br>
1 = Bus ERROR response received.
<br>
Note1: This bit is read only, but can be cleared by writing '1' to it.
<br>
Note2: When DMA's bus master received ERROR response, it means that target abort is happened
<br>
DMA will stop transfer and respond this event and then go to IDLE state
<br>
When target abort occurred or WEOTIF is set, software must reset DMA and SD host, and then transfer those data again.
<br>
</div></td></tr><tr><td>
[1]</td><td>WEOTIF</td><td><div style="word-wrap: break-word;"><b>Wrong EOT Encountered Interrupt Flag
</b><br>
When DMA Scatter-Gather function is enabled, and EOT of the descriptor is encountered before DMA transfer finished (that means the total sector count of all PAD is less than the sector count of SD host), this bit will be set.
<br>
0 = No EOT encountered before DMA transfer finished.
<br>
1 = EOT encountered before DMA transfer finished.
<br>
Note: This bit is read only, but can be cleared by writing '1' to it.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SDH_T::GCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GCTL
</font><br><p> <font size="2">
Offset: 0x800  Global Control and Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>GCTLRST</td><td><div style="word-wrap: break-word;"><b>Software Engine Reset
</b><br>
0 = No effect.
<br>
1 = Reset SD host
<br>
The contents of control register will not be cleared
<br>
This bit will auto cleared after reset complete.
<br>
</div></td></tr><tr><td>
[1]</td><td>SDEN</td><td><div style="word-wrap: break-word;"><b>Secure Digital Functionality Enable Bit
</b><br>
0 = SD functionality disabled.
<br>
1 = SD functionality enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SDH_T::GINTEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GINTEN
</font><br><p> <font size="2">
Offset: 0x804  Global Interrupt Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>DTAIEN</td><td><div style="word-wrap: break-word;"><b>DMA READ/WRITE Target Abort Interrupt Enable Bit
</b><br>
0 = DMA READ/WRITE target abort interrupt generation disabled.
<br>
1 = DMA READ/WRITE target abort interrupt generation enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SDH_T::GINTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GINTSTS
</font><br><p> <font size="2">
Offset: 0x808  Global Interrupt Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>DTAIF</td><td><div style="word-wrap: break-word;"><b>DMA READ/WRITE Target Abort Interrupt Flag (Read Only)
</b><br>
This bit indicates DMA received an ERROR response from internal AHB bus during DMA read/write operation
<br>
When Target Abort is occurred, please reset all engine.
<br>
0 = No bus ERROR response received.
<br>
1 = Bus ERROR response received.
<br>
Note: This bit is read only, but can be cleared by writing '1' to it.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SDH_T::CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL
</font><br><p> <font size="2">
Offset: 0x820  SD Control and Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>COEN</td><td><div style="word-wrap: break-word;"><b>Command Output Enable Bit
</b><br>
0 = No effect. (Please use DMARST (SDH_CTL [0]) to clear this bit.)
<br>
1 = Enabled, SD host will output a command to SD card.
<br>
Note: When operation is finished, this bit will be cleared automatically, so don't write 0 to this bit (the controller will be abnormal).
<br>
</div></td></tr><tr><td>
[1]</td><td>RIEN</td><td><div style="word-wrap: break-word;"><b>Response Input Enable Bit
</b><br>
0 = No effect. (Please use DMARST (SDH_CTL [0]) to clear this bit.)
<br>
1 = Enabled, SD host will wait to receive a response from SD card.
<br>
Note: When operation is finished, this bit will be cleared automatically, so don't write 0 to this bit (the controller will be abnormal).
<br>
</div></td></tr><tr><td>
[2]</td><td>DIEN</td><td><div style="word-wrap: break-word;"><b>Data Input Enable Bit
</b><br>
0 = No effect. (Please use DMARST (SDH_CTL [0]) to clear this bit.)
<br>
1 = Enabled, SD host will wait to receive block data and the CRC16 value from SD card.
<br>
Note: When operation is finished, this bit will be cleared automatically, so don't write 0 to this bit (the controller will be abnormal).
<br>
</div></td></tr><tr><td>
[3]</td><td>DOEN</td><td><div style="word-wrap: break-word;"><b>Data Output Enable Bit
</b><br>
0 = No effect. (Please use DMARST (SDH_CTL [0]) to clear this bit.)
<br>
1 = Enabled, SD host will transfer block data and the CRC16 value to SD card.
<br>
Note: When operation is finished, this bit will be cleared automatically, so don't write 0 to this bit (the controller will be abnormal).
<br>
</div></td></tr><tr><td>
[4]</td><td>R2EN</td><td><div style="word-wrap: break-word;"><b>Response R2 Input Enable Bit
</b><br>
0 = No effect. (Please use DMARST (SDH_CTL [0]) to clear this bit.)
<br>
1 = Enabled, SD host will wait to receive a response R2 from SD card and store the response data into DMC's flash buffer (exclude CRC7).
<br>
Note: When operation is finished, this bit will be cleared automatically, so don't write 0 to this bit (the controller will be abnormal).
<br>
</div></td></tr><tr><td>
[5]</td><td>CLK74OEN</td><td><div style="word-wrap: break-word;"><b>Initial 74 Clock Cycles Output Enable Bit
</b><br>
0 = No effect. (Please use DMARST (SDH_CTL [0]) to clear this bit.)
<br>
1 = Enabled, SD host will output 74 clock cycles to SD card.
<br>
Note: When operation is finished, this bit will be cleared automatically, so don't write 0 to this bit (the controller will be abnormal).
<br>
</div></td></tr><tr><td>
[6]</td><td>CLK8OEN</td><td><div style="word-wrap: break-word;"><b>Generating 8 Clock Cycles Output Enable Bit
</b><br>
0 = No effect. (Please use DMARST (SDH_CTL [0]) to clear this bit.)
<br>
1 = Enabled, SD host will output 8 clock cycles.
<br>
Note: When operation is finished, this bit will be cleared automatically, so don't write 0 to this bit (the controller will be abnormal).
<br>
</div></td></tr><tr><td>
[7]</td><td>CLKKEEP</td><td><div style="word-wrap: break-word;"><b>SD Clock Enable Control
</b><br>
0 = SD host decided when to output clock and when to disable clock output automatically.
<br>
1 = SD clock always keeps free running.
<br>
</div></td></tr><tr><td>
[13:8]</td><td>CMDCODE</td><td><div style="word-wrap: break-word;"><b>SD Command Code
</b><br>
This register contains the SD command code (0x00 - 0x3F).
<br>
</div></td></tr><tr><td>
[14]</td><td>CTLRST</td><td><div style="word-wrap: break-word;"><b>Software Engine Reset
</b><br>
0 = No effect.
<br>
1 = Reset the internal state machine and counters
<br>
The contents of control register will not be cleared (but RIEN, DIEN, DOEN and R2_EN will be cleared)
<br>
This bit will be auto cleared after few clock cycles.
<br>
</div></td></tr><tr><td>
[15]</td><td>DBW</td><td><div style="word-wrap: break-word;"><b>SD Data Bus Width (for 1-bit / 4-bit Selection)
</b><br>
0 = Data bus width is 1-bit.
<br>
1 = Data bus width is 4-bit.
<br>
</div></td></tr><tr><td>
[23:16]</td><td>BLKCNT</td><td><div style="word-wrap: break-word;"><b>Block Counts to Be Transferred or Received
</b><br>
This field contains the block counts for data-in and data-out transfer
<br>
For READ_MULTIPLE_BLOCK and WRITE_MULTIPLE_BLOCK command, software can use this function to accelerate data transfer and improve performance
<br>
Don't fill 0x0 to this field.
<br>
Note: For READ_MULTIPLE_BLOCK and WRITE_MULTIPLE_BLOCK command, the actual total length is BLKCNT * (BLKLEN +1).
<br>
</div></td></tr><tr><td>
[27:24]</td><td>SDNWR</td><td><div style="word-wrap: break-word;"><b>NWR Parameter for Block Write Operation
</b><br>
This value indicates the NWR parameter for data block write operation in SD clock counts
<br>
The actual clock cycle will be SDNWR+1.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SDH_T::CMDARG

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CMDARG
</font><br><p> <font size="2">
Offset: 0x824  SD Command Argument Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>ARGUMENT</td><td><div style="word-wrap: break-word;"><b>SD Command Argument
</b><br>
This register contains a 32-bit value specifies the argument of SD command from host controller to SD card
<br>
Before trigger COEN (SDH_CTL [0]), software should fill argument in this field.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SDH_T::INTEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTEN
</font><br><p> <font size="2">
Offset: 0x828  SD Interrupt Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BLKDIEN</td><td><div style="word-wrap: break-word;"><b>Block Transfer Done Interrupt Enable Bit
</b><br>
0 = BLKDIF (SDH_INTEN[0]) trigger interrupt Disable.
<br>
1 = BLKDIF (SDH_INTEN[0]) trigger interrupt Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>CRCIEN</td><td><div style="word-wrap: break-word;"><b>CRC7, CRC16 and CRC Status Error Interrupt Enable Bit
</b><br>
0 = CRCIF (SDH_INTEN[1]) trigger interrupt Disable.
<br>
1 = CRCIF (SDH_INTEN[1]) trigger interrupt Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>CDIEN</td><td><div style="word-wrap: break-word;"><b>SD Card Detection Interrupt Enable Bit
</b><br>
Enable/Disable interrupts generation of SD controller when card is inserted or removed.
<br>
0 = CDIF (SDH_INTEN[8]) trigger interrupt Disable.
<br>
1 = CDIF (SDH_INTEN[8]) trigger interrupt Enabled.
<br>
</div></td></tr><tr><td>
[12]</td><td>RTOIEN</td><td><div style="word-wrap: break-word;"><b>Response Time-out Interrupt Enable Bit
</b><br>
Enable/Disable interrupts generation of SD controller when receiving response or R2 time-out
<br>
Time-out value is specified at TOUT register.
<br>
0 = RTOIF (SDH_INTEN[12]) trigger interrupt Disabled.
<br>
1 = RTOIF (SDH_INTEN[12]) trigger interrupt Enabled.
<br>
</div></td></tr><tr><td>
[13]</td><td>DITOIEN</td><td><div style="word-wrap: break-word;"><b>Data Input Time-out Interrupt Enable Bit
</b><br>
Enable/Disable interrupts generation of SD controller when data input time-out
<br>
Time-out value is specified at TOUT register.
<br>
0 = DITOIF (SDH_INTEN[13]) trigger interrupt Disabled.
<br>
1 = DITOIF (SDH_INTEN[13]) trigger interrupt Enabled.
<br>
</div></td></tr><tr><td>
[14]</td><td>WKIEN</td><td><div style="word-wrap: break-word;"><b>Wake-up Signal Generating Enable Bit
</b><br>
Enable/Disable wake-up signal generating of SD host when current using SD card issues an interrupt (wake-up) via DAT [1] to host.
<br>
0 = SD Card interrupt to wake-up chip Disabled.
<br>
1 = SD Card interrupt to wake-up chip Enabled.
<br>
</div></td></tr><tr><td>
[30]</td><td>CDSRC</td><td><div style="word-wrap: break-word;"><b>SD Card Detect Source Selection
</b><br>
0 = From SD card's DAT3 pin.
<br>
Host need clock to got data on pin DAT3
<br>
Please make sure CLKKEEP (SDH_CTL[7]) is 1 in order to generate free running clock for DAT3 pin.
<br>
1 = From GPIO pin.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SDH_T::INTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTSTS
</font><br><p> <font size="2">
Offset: 0x82C  SD Interrupt Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BLKDIF</td><td><div style="word-wrap: break-word;"><b>Block Transfer Done Interrupt Flag (Read Only)
</b><br>
This bit indicates that SD host has finished all data-in or data-out block transfer
<br>
If there is a CRC16 error or incorrect CRC status during multiple block data transfer, the transfer will be broken and this bit will also be set.
<br>
0 = Not finished yet.
<br>
1 = Done.
<br>
Note: This bit is read only, but can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[1]</td><td>CRCIF</td><td><div style="word-wrap: break-word;"><b>CRC7, CRC16 and CRC Status Error Interrupt Flag (Read Only)
</b><br>
This bit indicates that SD host has occurred CRC error during response in, data-in or data-out (CRC status error) transfer
<br>
When CRC error is occurred, software should reset SD engine
<br>
Some response (ex
<br>
R3) doesn't have CRC7 information with it; SD host will still calculate CRC7, get CRC error and set this flag
<br>
In this condition, software should ignore CRC error and clears this bit manually.
<br>
0 = No CRC error is occurred.
<br>
1 = CRC error is occurred.
<br>
Note: This bit is read only, but can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[2]</td><td>CRC7</td><td><div style="word-wrap: break-word;"><b>CRC7 Check Status (Read Only)
</b><br>
SD host will check CRC7 correctness during each response in
<br>
If that response does not contain CRC7 information (ex
<br>
R3), then software should turn off CRCIEN (SDH_INTEN[1]) and ignore this bit.
<br>
0 = Fault.
<br>
1 = OK.
<br>
</div></td></tr><tr><td>
[3]</td><td>CRC16</td><td><div style="word-wrap: break-word;"><b>CRC16 Check Status of Data-in Transfer (Read Only)
</b><br>
SD host will check CRC16 correctness after data-in transfer.
<br>
0 = Fault.
<br>
1 = OK.
<br>
</div></td></tr><tr><td>
[6:4]</td><td>CRCSTS</td><td><div style="word-wrap: break-word;"><b>CRC Status Value of Data-out Transfer (Read Only)
</b><br>
SD host will record CRC status of data-out transfer
<br>
Software could use this value to identify what type of error is during data-out transfer.
<br>
010 = Positive CRC status.
<br>
101 = Negative CRC status.
<br>
111 = SD card programming error occurs.
<br>
</div></td></tr><tr><td>
[7]</td><td>DAT0STS</td><td><div style="word-wrap: break-word;"><b>DAT0 Pin Status of Current Selected SD Port (Read Only)
</b><br>
This bit is the DAT0 pin status of current selected SD port.
<br>
</div></td></tr><tr><td>
[8]</td><td>CDIF</td><td><div style="word-wrap: break-word;"><b>SD Card Detection Interrupt Flag (Read Only)
</b><br>
This bit indicates that SD card is inserted or removed
<br>
Only when CDIEN (SDH_INTEN[8]) is set to 1, this bit is active.
<br>
0 = No card is inserted or removed.
<br>
1 = There is a card inserted in or removed from SD.
<br>
Note: This bit is read only, but can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[12]</td><td>RTOIF</td><td><div style="word-wrap: break-word;"><b>Response Time-out Interrupt Flag (Read Only)
</b><br>
This bit indicates that SD host counts to time-out value when receiving response or R2 (waiting start bit).
<br>
0 = Not time-out.
<br>
1 = Response time-out.
<br>
Note: This bit is read only, but can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[13]</td><td>DITOIF</td><td><div style="word-wrap: break-word;"><b>Data Input Time-out Interrupt Flag (Read Only)
</b><br>
This bit indicates that SD host counts to time-out value when receiving data (waiting start bit).
<br>
0 = Not time-out.
<br>
1 = Data input time-out.
<br>
Note: This bit is read only, but can be cleared by writing '1' to it.
<br>
</div></td></tr><tr><td>
[16]</td><td>CDSTS</td><td><div style="word-wrap: break-word;"><b>Card Detect Status of SD (Read Only)
</b><br>
This bit indicates the card detect pin status of SD, and is used for card detection
<br>
When there is a card inserted in or removed from SD, software should check this bit to confirm if there is really a card insertion or removal.
<br>
If CDSRC (SDH_INTEN[30]) = 0, to select DAT3 for card detection:.
<br>
0 = Card removed.
<br>
1 = Card inserted.
<br>
If CDSRC (SDH_INTEN[30]) = 1, to select GPIO for card detection:.
<br>
0 = Card inserted.
<br>
1 = Card removed.
<br>
</div></td></tr><tr><td>
[18]</td><td>DAT1STS</td><td><div style="word-wrap: break-word;"><b>DAT1 Pin Status of SD Port (Read Only)
</b><br>
This bit indicates the DAT1 pin status of SD port.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SDH_T::RESP0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">RESP0
</font><br><p> <font size="2">
Offset: 0x830  SD Receiving Response Token Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>RESPTK0</td><td><div style="word-wrap: break-word;"><b>SD Receiving Response Token 0
</b><br>
SD host controller will receive a response token for getting a reply from SD card when RIEN (SDH_CTL[1]) is set
<br>
This field contains response bit 47-16 of the response token.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SDH_T::RESP1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">RESP1
</font><br><p> <font size="2">
Offset: 0x834  SD Receiving Response Token Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>RESPTK1</td><td><div style="word-wrap: break-word;"><b>SD Receiving Response Token 1
</b><br>
SD host controller will receive a response token for getting a reply from SD card when RIEN (SDH_CTL[1]) is set
<br>
This register contains the bit 15-8 of the response token.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SDH_T::BLEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BLEN
</font><br><p> <font size="2">
Offset: 0x838  SD Block Length Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[10:0]</td><td>BLKLEN</td><td><div style="word-wrap: break-word;"><b>SD BLOCK LENGTH in Byte Unit
</b><br>
An 11-bit value specifies the SD transfer byte count of a block
<br>
The actual byte count is equal to BLKLEN+1.
<br>
Note: The default SD block length is 512 bytes
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SDH_T::TOUT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TOUT
</font><br><p> <font size="2">
Offset: 0x83C  SD Response/Data-in Time-out Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:0]</td><td>TOUT</td><td><div style="word-wrap: break-word;"><b>SD Response/Data-in Time-out Value
</b><br>
A 24-bit value specifies the time-out counts of response and data input
<br>
SD host controller will wait start bit of response or data-in until this value reached
<br>
The time period depends on SD engine clock frequency
<br>
Do not write a small number into this field, or you may never get response or data due to time-out.
<br>
Note: Filling 0x0 into this field will disable hardware time-out function.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */

    __IO uint32_t FB[32];                /*!< Shared Buffer (FIFO)                                                      */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[224];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t DMACTL;                /*!< [0x0400] DMA Control and Status Register                                  */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t DMASA;                 /*!< [0x0408] DMA Transfer Starting Address Register                           */
    __I  uint32_t DMABCNT;               /*!< [0x040c] DMA Transfer Byte Count Register                                 */
    __IO uint32_t DMAINTEN;              /*!< [0x0410] DMA Interrupt Enable Control Register                            */
    __IO uint32_t DMAINTSTS;             /*!< [0x0414] DMA Interrupt Status Register                                    */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE2[250];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t GCTL;                  /*!< [0x0800] Global Control and Status Register                               */
    __IO uint32_t GINTEN;                /*!< [0x0804] Global Interrupt Control Register                                */
    __I  uint32_t GINTSTS;               /*!< [0x0808] Global Interrupt Status Register                                 */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE3[5];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t CTL;                   /*!< [0x0820] SD Control and Status Register                                   */
    __IO uint32_t CMDARG;                /*!< [0x0824] SD Command Argument Register                                     */
    __IO uint32_t INTEN;                 /*!< [0x0828] SD Interrupt Control Register                                    */
    __IO uint32_t INTSTS;                /*!< [0x082c] SD Interrupt Status Register                                     */
    __I  uint32_t RESP0;                 /*!< [0x0830] SD Receiving Response Token Register 0                           */
    __I  uint32_t RESP1;                 /*!< [0x0834] SD Receiving Response Token Register 1                           */
    __IO uint32_t BLEN;                  /*!< [0x0838] SD Block Length Register                                         */
    __IO uint32_t TOUT;                  /*!< [0x083c] SD Response/Data-in Time-out Register                            */

} SDH_T;


/**
    @addtogroup SDH_CONST SDH Bit Field Definition
    Constant Definitions for SDH Controller
@{ */

#define SDH_DMACTL_DMAEN_Pos             (0)                                               /*!< SDH_T::DMACTL: DMAEN Position          */
#define SDH_DMACTL_DMAEN_Msk             (0x1ul << SDH_DMACTL_DMAEN_Pos)                   /*!< SDH_T::DMACTL: DMAEN Mask              */

#define SDH_DMACTL_DMARST_Pos            (1)                                               /*!< SDH_T::DMACTL: DMARST Position         */
#define SDH_DMACTL_DMARST_Msk            (0x1ul << SDH_DMACTL_DMARST_Pos)                  /*!< SDH_T::DMACTL: DMARST Mask             */

#define SDH_DMACTL_SGEN_Pos              (3)                                               /*!< SDH_T::DMACTL: SGEN Position           */
#define SDH_DMACTL_SGEN_Msk              (0x1ul << SDH_DMACTL_SGEN_Pos)                    /*!< SDH_T::DMACTL: SGEN Mask               */

#define SDH_DMACTL_DMABUSY_Pos           (9)                                               /*!< SDH_T::DMACTL: DMABUSY Position        */
#define SDH_DMACTL_DMABUSY_Msk           (0x1ul << SDH_DMACTL_DMABUSY_Pos)                 /*!< SDH_T::DMACTL: DMABUSY Mask            */

#define SDH_DMASA_ORDER_Pos              (0)                                               /*!< SDH_T::DMASA: ORDER Position           */
#define SDH_DMASA_ORDER_Msk              (0x1ul << SDH_DMASA_ORDER_Pos)                    /*!< SDH_T::DMASA: ORDER Mask               */

#define SDH_DMASA_DMASA_Pos              (1)                                               /*!< SDH_T::DMASA: DMASA Position           */
#define SDH_DMASA_DMASA_Msk              (0x7ffffffful << SDH_DMASA_DMASA_Pos)             /*!< SDH_T::DMASA: DMASA Mask               */

#define SDH_DMABCNT_BCNT_Pos             (0)                                               /*!< SDH_T::DMABCNT: BCNT Position          */
#define SDH_DMABCNT_BCNT_Msk             (0x3fffffful << SDH_DMABCNT_BCNT_Pos)             /*!< SDH_T::DMABCNT: BCNT Mask              */

#define SDH_DMAINTEN_ABORTIEN_Pos        (0)                                               /*!< SDH_T::DMAINTEN: ABORTIEN Position     */
#define SDH_DMAINTEN_ABORTIEN_Msk        (0x1ul << SDH_DMAINTEN_ABORTIEN_Pos)              /*!< SDH_T::DMAINTEN: ABORTIEN Mask         */

#define SDH_DMAINTEN_WEOTIEN_Pos         (1)                                               /*!< SDH_T::DMAINTEN: WEOTIEN Position      */
#define SDH_DMAINTEN_WEOTIEN_Msk         (0x1ul << SDH_DMAINTEN_WEOTIEN_Pos)               /*!< SDH_T::DMAINTEN: WEOTIEN Mask          */

#define SDH_DMAINTSTS_ABORTIF_Pos        (0)                                               /*!< SDH_T::DMAINTSTS: ABORTIF Position     */
#define SDH_DMAINTSTS_ABORTIF_Msk        (0x1ul << SDH_DMAINTSTS_ABORTIF_Pos)              /*!< SDH_T::DMAINTSTS: ABORTIF Mask         */

#define SDH_DMAINTSTS_WEOTIF_Pos         (1)                                               /*!< SDH_T::DMAINTSTS: WEOTIF Position      */
#define SDH_DMAINTSTS_WEOTIF_Msk         (0x1ul << SDH_DMAINTSTS_WEOTIF_Pos)               /*!< SDH_T::DMAINTSTS: WEOTIF Mask          */

#define SDH_GCTL_GCTLRST_Pos             (0)                                               /*!< SDH_T::GCTL: GCTLRST Position          */
#define SDH_GCTL_GCTLRST_Msk             (0x1ul << SDH_GCTL_GCTLRST_Pos)                   /*!< SDH_T::GCTL: GCTLRST Mask              */

#define SDH_GCTL_SDEN_Pos                (1)                                               /*!< SDH_T::GCTL: SDEN Position             */
#define SDH_GCTL_SDEN_Msk                (0x1ul << SDH_GCTL_SDEN_Pos)                      /*!< SDH_T::GCTL: SDEN Mask                 */

#define SDH_GINTEN_DTAIEN_Pos            (0)                                               /*!< SDH_T::GINTEN: DTAIEN Position         */
#define SDH_GINTEN_DTAIEN_Msk            (0x1ul << SDH_GINTEN_DTAIEN_Pos)                  /*!< SDH_T::GINTEN: DTAIEN Mask             */

#define SDH_GINTSTS_DTAIF_Pos            (0)                                               /*!< SDH_T::GINTSTS: DTAIF Position         */
#define SDH_GINTSTS_DTAIF_Msk            (0x1ul << SDH_GINTSTS_DTAIF_Pos)                  /*!< SDH_T::GINTSTS: DTAIF Mask             */

#define SDH_CTL_COEN_Pos                 (0)                                               /*!< SDH_T::CTL: COEN Position              */
#define SDH_CTL_COEN_Msk                 (0x1ul << SDH_CTL_COEN_Pos)                       /*!< SDH_T::CTL: COEN Mask                  */

#define SDH_CTL_RIEN_Pos                 (1)                                               /*!< SDH_T::CTL: RIEN Position              */
#define SDH_CTL_RIEN_Msk                 (0x1ul << SDH_CTL_RIEN_Pos)                       /*!< SDH_T::CTL: RIEN Mask                  */

#define SDH_CTL_DIEN_Pos                 (2)                                               /*!< SDH_T::CTL: DIEN Position              */
#define SDH_CTL_DIEN_Msk                 (0x1ul << SDH_CTL_DIEN_Pos)                       /*!< SDH_T::CTL: DIEN Mask                  */

#define SDH_CTL_DOEN_Pos                 (3)                                               /*!< SDH_T::CTL: DOEN Position              */
#define SDH_CTL_DOEN_Msk                 (0x1ul << SDH_CTL_DOEN_Pos)                       /*!< SDH_T::CTL: DOEN Mask                  */

#define SDH_CTL_R2EN_Pos                 (4)                                               /*!< SDH_T::CTL: R2EN Position              */
#define SDH_CTL_R2EN_Msk                 (0x1ul << SDH_CTL_R2EN_Pos)                       /*!< SDH_T::CTL: R2EN Mask                  */

#define SDH_CTL_CLK74OEN_Pos             (5)                                               /*!< SDH_T::CTL: CLK74OEN Position          */
#define SDH_CTL_CLK74OEN_Msk             (0x1ul << SDH_CTL_CLK74OEN_Pos)                   /*!< SDH_T::CTL: CLK74OEN Mask              */

#define SDH_CTL_CLK8OEN_Pos              (6)                                               /*!< SDH_T::CTL: CLK8OEN Position           */
#define SDH_CTL_CLK8OEN_Msk              (0x1ul << SDH_CTL_CLK8OEN_Pos)                    /*!< SDH_T::CTL: CLK8OEN Mask               */

#define SDH_CTL_CLKKEEP_Pos              (7)                                               /*!< SDH_T::CTL: CLKKEEP Position          */
#define SDH_CTL_CLKKEEP_Msk              (0x1ul << SDH_CTL_CLKKEEP_Pos)                    /*!< SDH_T::CTL: CLKKEEP Mask              */

#define SDH_CTL_CMDCODE_Pos              (8)                                               /*!< SDH_T::CTL: CMDCODE Position           */
#define SDH_CTL_CMDCODE_Msk              (0x3ful << SDH_CTL_CMDCODE_Pos)                   /*!< SDH_T::CTL: CMDCODE Mask               */

#define SDH_CTL_CTLRST_Pos               (14)                                              /*!< SDH_T::CTL: CTLRST Position            */
#define SDH_CTL_CTLRST_Msk               (0x1ul << SDH_CTL_CTLRST_Pos)                     /*!< SDH_T::CTL: CTLRST Mask                */

#define SDH_CTL_DBW_Pos                  (15)                                              /*!< SDH_T::CTL: DBW Position               */
#define SDH_CTL_DBW_Msk                  (0x1ul << SDH_CTL_DBW_Pos)                        /*!< SDH_T::CTL: DBW Mask                   */

#define SDH_CTL_BLKCNT_Pos               (16)                                              /*!< SDH_T::CTL: BLKCNT Position            */
#define SDH_CTL_BLKCNT_Msk               (0xfful << SDH_CTL_BLKCNT_Pos)                    /*!< SDH_T::CTL: BLKCNT Mask                */

#define SDH_CTL_SDNWR_Pos                (24)                                              /*!< SDH_T::CTL: SDNWR Position             */
#define SDH_CTL_SDNWR_Msk                (0xful << SDH_CTL_SDNWR_Pos)                      /*!< SDH_T::CTL: SDNWR Mask                 */

#define SDH_CMDARG_ARGUMENT_Pos          (0)                                               /*!< SDH_T::CMDARG: ARGUMENT Position       */
#define SDH_CMDARG_ARGUMENT_Msk          (0xfffffffful << SDH_CMDARG_ARGUMENT_Pos)         /*!< SDH_T::CMDARG: ARGUMENT Mask           */

#define SDH_INTEN_BLKDIEN_Pos            (0)                                               /*!< SDH_T::INTEN: BLKDIEN Position         */
#define SDH_INTEN_BLKDIEN_Msk            (0x1ul << SDH_INTEN_BLKDIEN_Pos)                  /*!< SDH_T::INTEN: BLKDIEN Mask             */

#define SDH_INTEN_CRCIEN_Pos             (1)                                               /*!< SDH_T::INTEN: CRCIEN Position          */
#define SDH_INTEN_CRCIEN_Msk             (0x1ul << SDH_INTEN_CRCIEN_Pos)                   /*!< SDH_T::INTEN: CRCIEN Mask              */

#define SDH_INTEN_CDIEN_Pos              (8)                                               /*!< SDH_T::INTEN: CDIEN Position          */
#define SDH_INTEN_CDIEN_Msk              (0x1ul << SDH_INTEN_CDIEN_Pos)                    /*!< SDH_T::INTEN: CDIEN Mask              */

#define SDH_INTEN_RTOIEN_Pos             (12)                                              /*!< SDH_T::INTEN: RTOIEN Position          */
#define SDH_INTEN_RTOIEN_Msk             (0x1ul << SDH_INTEN_RTOIEN_Pos)                   /*!< SDH_T::INTEN: RTOIEN Mask              */

#define SDH_INTEN_DITOIEN_Pos            (13)                                              /*!< SDH_T::INTEN: DITOIEN Position         */
#define SDH_INTEN_DITOIEN_Msk            (0x1ul << SDH_INTEN_DITOIEN_Pos)                  /*!< SDH_T::INTEN: DITOIEN Mask             */

#define SDH_INTEN_WKIEN_Pos              (14)                                              /*!< SDH_T::INTEN: WKIEN Position           */
#define SDH_INTEN_WKIEN_Msk              (0x1ul << SDH_INTEN_WKIEN_Pos)                    /*!< SDH_T::INTEN: WKIEN Mask               */

#define SDH_INTEN_CDSRC_Pos              (30)                                              /*!< SDH_T::INTEN: CDSRC Position          */
#define SDH_INTEN_CDSRC_Msk              (0x1ul << SDH_INTEN_CDSRC_Pos)                    /*!< SDH_T::INTEN: CDSRC Mask              */

#define SDH_INTSTS_BLKDIF_Pos            (0)                                               /*!< SDH_T::INTSTS: BLKDIF Position         */
#define SDH_INTSTS_BLKDIF_Msk            (0x1ul << SDH_INTSTS_BLKDIF_Pos)                  /*!< SDH_T::INTSTS: BLKDIF Mask             */

#define SDH_INTSTS_CRCIF_Pos             (1)                                               /*!< SDH_T::INTSTS: CRCIF Position          */
#define SDH_INTSTS_CRCIF_Msk             (0x1ul << SDH_INTSTS_CRCIF_Pos)                   /*!< SDH_T::INTSTS: CRCIF Mask              */

#define SDH_INTSTS_CRC7_Pos              (2)                                               /*!< SDH_T::INTSTS: CRC7 Position           */
#define SDH_INTSTS_CRC7_Msk              (0x1ul << SDH_INTSTS_CRC7_Pos)                    /*!< SDH_T::INTSTS: CRC7 Mask               */

#define SDH_INTSTS_CRC16_Pos             (3)                                               /*!< SDH_T::INTSTS: CRC16 Position          */
#define SDH_INTSTS_CRC16_Msk             (0x1ul << SDH_INTSTS_CRC16_Pos)                   /*!< SDH_T::INTSTS: CRC16 Mask              */

#define SDH_INTSTS_CRCSTS_Pos            (4)                                               /*!< SDH_T::INTSTS: CRCSTS Position         */
#define SDH_INTSTS_CRCSTS_Msk            (0x7ul << SDH_INTSTS_CRCSTS_Pos)                  /*!< SDH_T::INTSTS: CRCSTS Mask             */

#define SDH_INTSTS_DAT0STS_Pos           (7)                                               /*!< SDH_T::INTSTS: DAT0STS Position        */
#define SDH_INTSTS_DAT0STS_Msk           (0x1ul << SDH_INTSTS_DAT0STS_Pos)                 /*!< SDH_T::INTSTS: DAT0STS Mask            */

#define SDH_INTSTS_CDIF_Pos              (8)                                               /*!< SDH_T::INTSTS: CDIF Position          */
#define SDH_INTSTS_CDIF_Msk              (0x1ul << SDH_INTSTS_CDIF_Pos)                    /*!< SDH_T::INTSTS: CDIF Mask              */

#define SDH_INTSTS_RTOIF_Pos             (12)                                              /*!< SDH_T::INTSTS: RTOIF Position          */
#define SDH_INTSTS_RTOIF_Msk             (0x1ul << SDH_INTSTS_RTOIF_Pos)                   /*!< SDH_T::INTSTS: RTOIF Mask              */

#define SDH_INTSTS_DITOIF_Pos            (13)                                              /*!< SDH_T::INTSTS: DITOIF Position         */
#define SDH_INTSTS_DITOIF_Msk            (0x1ul << SDH_INTSTS_DITOIF_Pos)                  /*!< SDH_T::INTSTS: DITOIF Mask             */

#define SDH_INTSTS_CDSTS_Pos             (16)                                              /*!< SDH_T::INTSTS: CDSTS Position         */
#define SDH_INTSTS_CDSTS_Msk             (0x1ul << SDH_INTSTS_CDSTS_Pos)                   /*!< SDH_T::INTSTS: CDSTS Mask             */

#define SDH_INTSTS_DAT1STS_Pos           (18)                                              /*!< SDH_T::INTSTS: DAT1STS Position        */
#define SDH_INTSTS_DAT1STS_Msk           (0x1ul << SDH_INTSTS_DAT1STS_Pos)                 /*!< SDH_T::INTSTS: DAT1STS Mask            */

#define SDH_RESP0_RESPTK0_Pos            (0)                                               /*!< SDH_T::RESP0: RESPTK0 Position         */
#define SDH_RESP0_RESPTK0_Msk            (0xfffffffful << SDH_RESP0_RESPTK0_Pos)           /*!< SDH_T::RESP0: RESPTK0 Mask             */

#define SDH_RESP1_RESPTK1_Pos            (0)                                               /*!< SDH_T::RESP1: RESPTK1 Position         */
#define SDH_RESP1_RESPTK1_Msk            (0xfful << SDH_RESP1_RESPTK1_Pos)                 /*!< SDH_T::RESP1: RESPTK1 Mask             */

#define SDH_BLEN_BLKLEN_Pos              (0)                                               /*!< SDH_T::BLEN: BLKLEN Position           */
#define SDH_BLEN_BLKLEN_Msk              (0x7fful << SDH_BLEN_BLKLEN_Pos)                  /*!< SDH_T::BLEN: BLKLEN Mask               */

#define SDH_TOUT_TOUT_Pos                (0)                                               /*!< SDH_T::TOUT: TOUT Position             */
#define SDH_TOUT_TOUT_Msk                (0xfffffful << SDH_TOUT_TOUT_Pos)                 /*!< SDH_T::TOUT: TOUT Mask                 */

/**@}*/ /* SDH_CONST */
/**@}*/ /* end of SDH register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __SDH_REG_H__ */

