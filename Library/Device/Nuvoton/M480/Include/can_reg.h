/**************************************************************************//**
 * @file     can_reg.h
 * @version  V1.00
 * @brief    CAN register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __CAN_REG_H__
#define __CAN_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup CAN Controller Area Network Controller(CAN)
    Memory Mapped Structure for CAN Controller
@{ */


typedef struct
{

    /**
@var CAN_IF_T::CREQ

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CREQ
</font><br><p> <font size="2">
Offset: 0x20, 0x80  IFn Command Request Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[5:0]</td><td>MessageNumber</td><td><div style="word-wrap: break-word;"><b>Message Number
</b><br>
0x01-0x20: Valid Message Number, the Message Object in the Message
<br>
RAM is selected for data transfer.
<br>
0x00: Not a valid Message Number, interpreted as 0x20.
<br>
0x21-0x3F: Not a valid Message Number, interpreted as 0x01-0x1F.
<br>
</div></td></tr><tr><td>
[15]</td><td>Busy</td><td><div style="word-wrap: break-word;"><b>Busy Flag
</b><br>
0 = Read/write action has finished.
<br>
1 = Writing to the IFn Command Request Register is in progress
<br>
This bit can only be read by the software.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_IF_T::CMASK

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CMASK
</font><br><p> <font size="2">
Offset: 0x24, 0x84  IFn Command Mask Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>DAT_B</td><td><div style="word-wrap: break-word;"><b>Access Data Bytes [7:4]
</b><br>
Write Operation:
<br>
0 = Data Bytes [7:4] unchanged.
<br>
1 = Transfer Data Bytes [7:4] to Message Object.
<br>
Read Operation:
<br>
0 = Data Bytes [7:4] unchanged.
<br>
1 = Transfer Data Bytes [7:4] to IFn Message Buffer Register.
<br>
</div></td></tr><tr><td>
[1]</td><td>DAT_A</td><td><div style="word-wrap: break-word;"><b>Access Data Bytes [3:0]
</b><br>
Write Operation:
<br>
0 = Data Bytes [3:0] unchanged.
<br>
1 = Transfer Data Bytes [3:0] to Message Object.
<br>
Read Operation:
<br>
0 = Data Bytes [3:0] unchanged.
<br>
1 = Transfer Data Bytes [3:0] to IFn Message Buffer Register.
<br>
</div></td></tr><tr><td>
[2]</td><td>TxRqst_NewDat</td><td><div style="word-wrap: break-word;"><b>Access Transmission Request Bit When Write Operation
</b><br>
0 = TxRqst bit unchanged.
<br>
1 = Set TxRqst bit.
<br>
Note: If a transmission is requested by programming bit TxRqst/NewDat in the IFn Command Mask Register, bit TxRqst in the IFn Message Control Register will be ignored.
<br>
Access New Data Bit when Read Operation.
<br>
0 = NewDat bit remains unchanged.
<br>
1 = Clear NewDat bit in the Message Object.
<br>
Note: A read access to a Message Object can be combined with the reset of the control bits IntPnd and NewDat
<br>
The values of these bits transferred to the IFn Message Control Register always reflect the status before resetting these bits.
<br>
</div></td></tr><tr><td>
[3]</td><td>ClrIntPnd</td><td><div style="word-wrap: break-word;"><b>Clear Interrupt Pending Bit
</b><br>
Write Operation:
<br>
When writing to a Message Object, this bit is ignored.
<br>
Read Operation:
<br>
0 = IntPnd bit (CAN_IFn_MCON[13]) remains unchanged.
<br>
1 = Clear IntPnd bit in the Message Object.
<br>
</div></td></tr><tr><td>
[4]</td><td>Control</td><td><div style="word-wrap: break-word;"><b>Control Access Control Bits
</b><br>
Write Operation:
<br>
0 = Control Bits unchanged.
<br>
1 = Transfer Control Bits to Message Object.
<br>
Read Operation:
<br>
0 = Control Bits unchanged.
<br>
1 = Transfer Control Bits to IFn Message Buffer Register.
<br>
</div></td></tr><tr><td>
[5]</td><td>Arb</td><td><div style="word-wrap: break-word;"><b>Access Arbitration Bits
</b><br>
Write Operation:
<br>
0 = Arbitration bits unchanged.
<br>
1 = Transfer Identifier + Dir (CAN_IFn_ARB2[13]) + Xtd (CAN_IFn_ARB2[14]) + MsgVal (CAN_IFn_ARB2[15]) to Message Object.
<br>
Read Operation:
<br>
0 = Arbitration bits unchanged.
<br>
1 = Transfer Identifier + Dir + Xtd + MsgVal to IFn Message Buffer Register.
<br>
</div></td></tr><tr><td>
[6]</td><td>Mask</td><td><div style="word-wrap: break-word;"><b>Access Mask Bits
</b><br>
Write Operation:
<br>
0 = Mask bits unchanged.
<br>
1 = Transfer Identifier Mask + MDir + MXtd to Message Object.
<br>
Read Operation:
<br>
0 = Mask bits unchanged.
<br>
1 = Transfer Identifier Mask + MDir + MXtd to IFn Message Buffer Register.
<br>
</div></td></tr><tr><td>
[7]</td><td>WR_RD</td><td><div style="word-wrap: break-word;"><b>Write / Read Mode
</b><br>
0 = Read: Transfer data from the Message Object addressed by the Command Request Register into the selected Message Buffer Registers.
<br>
1 = Write: Transfer data from the selected Message Buffer Registers to the Message Object addressed by the Command Request Register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_IF_T::MASK1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MASK1
</font><br><p> <font size="2">
Offset: 0x28, 0x88  IFn Mask 1 Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>Msk</td><td><div style="word-wrap: break-word;"><b>Identifier Mask 15-0
</b><br>
0 = The corresponding bit in the identifier of the message object cannot inhibit the match in the acceptance filtering.
<br>
1 = The corresponding identifier bit is used for acceptance filtering.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_IF_T::MASK2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MASK2
</font><br><p> <font size="2">
Offset: 0x2C, 0x8C  IFn Mask 2 Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[12:0]</td><td>Msk</td><td><div style="word-wrap: break-word;"><b>Identifier Mask 28-16
</b><br>
0 = The corresponding bit in the identifier of the message object cannot inhibit the match in the acceptance filtering.
<br>
1 = The corresponding identifier bit is used for acceptance filtering.
<br>
</div></td></tr><tr><td>
[14]</td><td>MDir</td><td><div style="word-wrap: break-word;"><b>Mask Message Direction
</b><br>
0 = The message direction bit (Dir (CAN_IFn_ARB2[13])) has no effect on the acceptance filtering.
<br>
1 = The message direction bit (Dir) is used for acceptance filtering.
<br>
</div></td></tr><tr><td>
[15]</td><td>MXtd</td><td><div style="word-wrap: break-word;"><b>Mask Extended Identifier
</b><br>
0 = The extended identifier bit (IDE) has no effect on the acceptance filtering.
<br>
1 = The extended identifier bit (IDE) is used for acceptance filtering.
<br>
Note: When 11-bit (standard) Identifiers are used for a Message Object, the identifiers of received Data Frames are written into bits ID28 to ID18 (CAN_IFn_ARB2[12:2])
<br>
For acceptance filtering, only these bits together with mask bits Msk28 to Msk18 (CAN_IFn_MASK2[12:2]) are considered.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_IF_T::ARB1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ARB1
</font><br><p> <font size="2">
Offset: 0x30, 0x90  IFn Arbitration 1 Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>ID</td><td><div style="word-wrap: break-word;"><b>Message Identifier 15-0
</b><br>
ID28 - ID0, 29-bit Identifier (Extended Frame)
<br>
ID28 - ID18, 11-bit Identifier (Standard Frame)
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_IF_T::ARB2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ARB2
</font><br><p> <font size="2">
Offset: 0x34, 0x94  IFn Arbitration 2 Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[12:0]</td><td>ID</td><td><div style="word-wrap: break-word;"><b>Message Identifier 28-16
</b><br>
ID28 - ID0, 29-bit Identifier (Extended Frame)
<br>
ID28 - ID18, 11-bit Identifier (Standard Frame)
<br>
</div></td></tr><tr><td>
[13]</td><td>Dir</td><td><div style="word-wrap: break-word;"><b>Message Direction
</b><br>
0 = Direction is receive.
<br>
On TxRqst, a Remote Frame with the identifier of this Message Object is transmitted
<br>
On reception of a Data Frame with matching identifier, that message is stored in this Message Object.
<br>
1 = Direction is transmit.
<br>
On TxRqst, the respective Message Object is transmitted as a Data Frame
<br>
On reception of a Remote Frame with matching identifier, the TxRqst bit (CAN_IFn_CMASK[2]) of this Message Object is set (if RmtEn (CAN_IFn_MCON[9]) = one).
<br>
</div></td></tr><tr><td>
[14]</td><td>Xtd</td><td><div style="word-wrap: break-word;"><b>Extended Identifier
</b><br>
0 = The 11-bit (standard) Identifier will be used for this Message Object.
<br>
1 = The 29-bit (extended) Identifier will be used for this Message Object.
<br>
</div></td></tr><tr><td>
[15]</td><td>MsgVal</td><td><div style="word-wrap: break-word;"><b>Message Valid
</b><br>
0 = The Message Object is ignored by the Message Handler.
<br>
1 = The Message Object is configured and should be considered by the Message Handler.
<br>
Note: The application software must reset the MsgVal bit of all unused Messages Objects during the initialization before it resets bit Init (CAN_CON[0])
<br>
This bit must also be reset before the identifier Id28-0 (CAN_IFn_ARB1/2), the control bits Xtd (CAN_IFn_ARB2[14]), Dir (CAN_IFn_ARB2[13]), or the Data Length Code DLC3-0 (CAN_IFn_MCON[3:0]) are modified, or if the Messages Object is no longer required.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_IF_T::MCON

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MCON
</font><br><p> <font size="2">
Offset: 0x38, 0x98  IFn Message Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>DLC</td><td><div style="word-wrap: break-word;"><b>Data Length Code
</b><br>
0-8: Data Frame has 0-8 data bytes.
<br>
9-15: Data Frame has 8 data bytes
<br>
Note: The Data Length Code of a Message Object must be defined the same as in all the corresponding objects with the same identifier at other nodes
<br>
When the Message Handler stores a data frame, it will write the DLC to the value given by the received message.
<br>
Data(0): 1st data byte of a CAN Data Frame
<br>
Data(1): 2nd data byte of a CAN Data Frame
<br>
Data(2): 3rd data byte of a CAN Data Frame
<br>
Data(3): 4th data byte of a CAN Data Frame
<br>
Data(4): 5th data byte of a CAN Data Frame
<br>
Data(5): 6th data byte of a CAN Data Frame
<br>
Data(6): 7th data byte of a CAN Data Frame
<br>
Data(7): 8th data byte of a CAN Data Frame
<br>
Note: The Data(0) byte is the first data byte shifted into the shift register of the CAN Core during a reception while the Data(7) byte is the last
<br>
When the Message Handler stores a Data Frame, it will write all the eight data bytes into a Message Object
<br>
If the Data Length Code is less than 8, the remaining bytes of the Message Object will be overwritten by unspecified values.
<br>
</div></td></tr><tr><td>
[7]</td><td>EoB</td><td><div style="word-wrap: break-word;"><b>End of Buffer
</b><br>
0 = Message Object belongs to a FIFO Buffer and is not the last Message Object of that FIFO Buffer.
<br>
1 = Single Message Object or last Message Object of a FIFO Buffer.
<br>
Note: This bit is used to concatenate two or more Message Objects (up to 32) to build a FIFO Buffer
<br>
For single Message Objects (not belonging to a FIFO Buffer), this bit must always be set to one
<br>
</div></td></tr><tr><td>
[8]</td><td>TxRqst</td><td><div style="word-wrap: break-word;"><b>Transmit Request
</b><br>
0 = This Message Object is not waiting for transmission.
<br>
1 = The transmission of this Message Object is requested and is not yet done.
<br>
</div></td></tr><tr><td>
[9]</td><td>RmtEn</td><td><div style="word-wrap: break-word;"><b>Remote Enable Bit
</b><br>
0 = At the reception of a Remote Frame, TxRqst (CAN_IFn_MCON[8]) is left unchanged.
<br>
1 = At the reception of a Remote Frame, TxRqst is set.
<br>
</div></td></tr><tr><td>
[10]</td><td>RxIE</td><td><div style="word-wrap: break-word;"><b>Receive Interrupt Enable Bit
</b><br>
0 = IntPnd (CAN_IFn_MCON[13]) will be left unchanged after a successful reception of a frame.
<br>
1 = IntPnd will be set after a successful reception of a frame.
<br>
</div></td></tr><tr><td>
[11]</td><td>TxIE</td><td><div style="word-wrap: break-word;"><b>Transmit Interrupt Enable Bit
</b><br>
0 = IntPnd (CAN_IFn_MCON[13]) will be left unchanged after the successful transmission of a frame.
<br>
1 = IntPnd will be set after a successful transmission of a frame.
<br>
</div></td></tr><tr><td>
[12]</td><td>UMask</td><td><div style="word-wrap: break-word;"><b>Use Acceptance Mask
</b><br>
0 = Mask ignored.
<br>
1 = Use Mask (Msk28-0, MXtd, and MDir) for acceptance filtering.
<br>
Note: If the UMask bit is set to one, the Message Object's mask bits have to be programmed during initialization of the Message Object before MsgVal bit (CAN_IFn_ARB2[15]) is set to one.
<br>
</div></td></tr><tr><td>
[13]</td><td>IntPnd</td><td><div style="word-wrap: break-word;"><b>Interrupt Pending
</b><br>
0 = This message object is not the source of an interrupt.
<br>
1 = This message object is the source of an interrupt
<br>
The Interrupt Identifier in the Interrupt Register will point to this message object if there is no other interrupt source with higher priority.
<br>
</div></td></tr><tr><td>
[14]</td><td>MsgLst</td><td><div style="word-wrap: break-word;"><b>Message Lost (only valid for Message Objects with direction = receive).
</b><br>
0 = No message lost since last time this bit was reset by the CPU.
<br>
1 = The Message Handler stored a new message into this object when NewDat was still set, the CPU has lost a message.
<br>
</div></td></tr><tr><td>
[15]</td><td>NewDat</td><td><div style="word-wrap: break-word;"><b>New Data
</b><br>
0 = No new data has been written into the data portion of this Message Object by the Message Handler since last time this flag was cleared by the application software.
<br>
1 = The Message Handler or the application software has written new data into the data portion of this Message Object.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_IF_T::DAT_A1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DAT_A1
</font><br><p> <font size="2">
Offset: 0x3C, 0x9C  IFn Data A1 Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>Data_0_</td><td><div style="word-wrap: break-word;"><b>Data Byte 0
</b><br>
1st data byte of a CAN Data Frame
<br>
</div></td></tr><tr><td>
[15:8]</td><td>Data_1_</td><td><div style="word-wrap: break-word;"><b>Data Byte 1
</b><br>
2nd data byte of a CAN Data Frame
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_IF_T::DAT_A2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DAT_A2
</font><br><p> <font size="2">
Offset: 0x40, 0xA0  IFn Data A2 Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>Data_2_</td><td><div style="word-wrap: break-word;"><b>Data Byte 2
</b><br>
3rd data byte of CAN Data Frame
<br>
</div></td></tr><tr><td>
[15:8]</td><td>Data_3_</td><td><div style="word-wrap: break-word;"><b>Data Byte 3
</b><br>
4th data byte of CAN Data Frame
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_IF_T::DAT_B1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DAT_B1
</font><br><p> <font size="2">
Offset: 0x44, 0xA4  IFn Data B1 Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>Data_4_</td><td><div style="word-wrap: break-word;"><b>Data Byte 4
</b><br>
5th data byte of CAN Data Frame
<br>
</div></td></tr><tr><td>
[15:8]</td><td>Data_5_</td><td><div style="word-wrap: break-word;"><b>Data Byte 5
</b><br>
6th data byte of CAN Data Frame
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_IF_T::DAT_B2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DAT_B2
</font><br><p> <font size="2">
Offset: 0x48, 0xA8  IFn Data B2 Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>Data_6_</td><td><div style="word-wrap: break-word;"><b>Data Byte 6
</b><br>
7th data byte of CAN Data Frame.
<br>
</div></td></tr><tr><td>
[15:8]</td><td>Data_7_</td><td><div style="word-wrap: break-word;"><b>Data Byte 7
</b><br>
8th data byte of CAN Data Frame.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CREQ;         /*!< [0x0020] IFn Command Request Register                                     */
    __IO uint32_t CMASK;        /*!< [0x0024] IFn Command Mask Register                                        */
    __IO uint32_t MASK1;        /*!< [0x0028] IFn Mask 1 Register                                              */
    __IO uint32_t MASK2;        /*!< [0x002c] IFn Mask 2 Register                                              */
    __IO uint32_t ARB1;         /*!< [0x0030] IFn Arbitration 1 Register                                       */
    __IO uint32_t ARB2;         /*!< [0x0034] IFn Arbitration 2 Register                                       */
    __IO uint32_t MCON;         /*!< [0x0038] IFn Message Control Register                                     */
    __IO uint32_t DAT_A1;       /*!< [0x003c] IFn Data A1 Register                                             */
    __IO uint32_t DAT_A2;       /*!< [0x0040] IFn Data A2 Register                                             */
    __IO uint32_t DAT_B1;       /*!< [0x0044] IFn Data B1 Register                                             */
    __IO uint32_t DAT_B2;       /*!< [0x0048] IFn Data B2 Register                                             */
    /// @cond HIDDEN_SYMBOLS
    __I uint32_t RESERVE0[13];
    /// @endcond //HIDDEN_SYMBOLS
} CAN_IF_T;


typedef struct
{


    /**
@var CAN_T::CON

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CON
</font><br><p> <font size="2">
Offset: 0x00  Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>Init</td><td><div style="word-wrap: break-word;"><b>Init Initialization
</b><br>
0 = Normal Operation.
<br>
1 = Initialization is started.
<br>
</div></td></tr><tr><td>
[1]</td><td>IE</td><td><div style="word-wrap: break-word;"><b>Module Interrupt Enable Bit
</b><br>
0 = Function interrupt is Disabled.
<br>
1 = Function interrupt is Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>SIE</td><td><div style="word-wrap: break-word;"><b>Status Change Interrupt Enable Bit
</b><br>
0 = Disabled - No Status Change Interrupt will be generated.
<br>
1 = Enabled - An interrupt will be generated when a message transfer is successfully completed or a CAN bus error is detected.
<br>
</div></td></tr><tr><td>
[3]</td><td>EIE</td><td><div style="word-wrap: break-word;"><b>Error Interrupt Enable Bit
</b><br>
0 = Disabled - No Error Status Interrupt will be generated.
<br>
1 = Enabled - A change in the bits BOff (CAN_STATUS[7]) or EWarn (CAN_STATUS[6]) in the Status Register will generate an interrupt.
<br>
</div></td></tr><tr><td>
[5]</td><td>DAR</td><td><div style="word-wrap: break-word;"><b>Automatic Re-transmission Disable Bit
</b><br>
0 = Automatic Retransmission of disturbed messages Enabled.
<br>
1 = Automatic Retransmission Disabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>CCE</td><td><div style="word-wrap: break-word;"><b>Configuration Change Enable Bit
</b><br>
0 = No write access to the Bit Timing Register.
<br>
1 = Write access to the Bit Timing Register (CAN_BTIME) allowed. (while Init bit (CAN_CON[0]) = 1).
<br>
</div></td></tr><tr><td>
[7]</td><td>Test</td><td><div style="word-wrap: break-word;"><b>Test Mode Enable Bit
</b><br>
0 = Normal Operation.
<br>
1 = Test Mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_T::STATUS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STATUS
</font><br><p> <font size="2">
Offset: 0x04  Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2:0]</td><td>LEC</td><td><div style="word-wrap: break-word;"><b>Last Error Code (Type of the Last Error to Occur on the CAN Bus)
</b><br>
The LEC field holds a code, which indicates the type of the last error to occur on the CAN bus
<br>
This field will be cleared to '0' when a message has been transferred (reception or transmission) without error
<br>
The unused code '7' may be written by the CPU to check for updates
<br>
The Error! Reference source not found
<br>
describes the error code.
<br>
</div></td></tr><tr><td>
[3]</td><td>TxOK</td><td><div style="word-wrap: break-word;"><b>Transmitted a Message Successfully
</b><br>
0 = Since this bit was reset by the CPU, no message has been successfully transmitted
<br>
This bit is never reset by the CAN Core.
<br>
1 = Since this bit was last reset by the CPU, a message has been successfully (error free and acknowledged by at least one other node) transmitted.
<br>
</div></td></tr><tr><td>
[4]</td><td>RxOK</td><td><div style="word-wrap: break-word;"><b>Received a Message Successfully
</b><br>
0 = No message has been successfully received since this bit was last reset by the CPU
<br>
This bit is never reset by the CAN Core.
<br>
1 = A message has been successfully received since this bit was last reset by the CPU (independent of the result of acceptance filtering).
<br>
</div></td></tr><tr><td>
[5]</td><td>EPass</td><td><div style="word-wrap: break-word;"><b>Error Passive (Read Only)
</b><br>
0 = The CAN Core is error active.
<br>
1 = The CAN Core is in the error passive state as defined in the CAN Specification.
<br>
</div></td></tr><tr><td>
[6]</td><td>EWarn</td><td><div style="word-wrap: break-word;"><b>Error Warning Status (Read Only)
</b><br>
0 = Both error counters are below the error warning limit of 96.
<br>
1 = At least one of the error counters in the EML has reached the error warning limit of 96.
<br>
</div></td></tr><tr><td>
[7]</td><td>BOff</td><td><div style="word-wrap: break-word;"><b>Bus-off Status (Read Only)
</b><br>
0 = The CAN module is not in bus-off state.
<br>
1 = The CAN module is in bus-off state.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_T::ERR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ERR
</font><br><p> <font size="2">
Offset: 0x08  Error Counter Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>TEC</td><td><div style="word-wrap: break-word;"><b>Transmit Error Counter
</b><br>
Actual state of the Transmit Error Counter. Values between 0 and 255.
<br>
</div></td></tr><tr><td>
[14:8]</td><td>REC</td><td><div style="word-wrap: break-word;"><b>Receive Error Counter
</b><br>
Actual state of the Receive Error Counter. Values between 0 and 127.
<br>
</div></td></tr><tr><td>
[15]</td><td>RP</td><td><div style="word-wrap: break-word;"><b>Receive Error Passive
</b><br>
0 = The Receive Error Counter is below the error passive level.
<br>
1 = The Receive Error Counter has reached the error passive level as defined in the CAN Specification.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_T::BTIME

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BTIME
</font><br><p> <font size="2">
Offset: 0x0C  Bit Timing Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[5:0]</td><td>BRP</td><td><div style="word-wrap: break-word;"><b>Baud Rate Prescaler
</b><br>
0x01-0x3F: The value by which the oscillator frequency is divided for generating the bit time quanta
<br>
The bit time is built up from a multiple of this quanta
<br>
Valid values for the Baud Rate Prescaler are [0...63]
<br>
The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
<br>
</div></td></tr><tr><td>
[7:6]</td><td>SJW</td><td><div style="word-wrap: break-word;"><b>(Re)Synchronization Jump Width
</b><br>
0x0-0x3: Valid programmed values are [0...3]
<br>
The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
<br>
</div></td></tr><tr><td>
[11:8]</td><td>TSeg1</td><td><div style="word-wrap: break-word;"><b>Time Segment Before the Sample Point Minus Sync_Seg
</b><br>
0x01-0x0F: valid values for TSeg1 are [1...15]
<br>
The actual interpretation by the hardware of this value is such that one more than the value programmed is used.
<br>
</div></td></tr><tr><td>
[14:12]</td><td>TSeg2</td><td><div style="word-wrap: break-word;"><b>Time Segment After Sample Point
</b><br>
0x0-0x7: Valid values for TSeg2 are [0...7]
<br>
The actual interpretation by the hardware of this value is such that one more than the value programmed here is used.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_T::IIDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">IIDR
</font><br><p> <font size="2">
Offset: 0x10  Interrupt Identifier Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>IntId</td><td><div style="word-wrap: break-word;"><b>Interrupt Identifier (Indicates the Source of the Interrupt)
</b><br>
If several interrupts are pending, the CAN Interrupt Register will point to the pending interrupt with the highest priority, disregarding their chronological order
<br>
An interrupt remains pending until the application software has cleared it
<br>
If IntId is different from 0x0000 and IE (CAN_CON[1]) is set, the IRQ interrupt signal to the EIC is active
<br>
The interrupt remains active until IntId is back to value 0x0000 (the cause of the interrupt is reset) or until IE is reset.
<br>
The Status Interrupt has the highest priority
<br>
Among the message interrupts, the Message Object' s interrupt priority decreases with increasing message number.
<br>
A message interrupt is cleared by clearing the Message Object's IntPnd bit (CAN_IFn_MCON[13])
<br>
The Status Interrupt is cleared by reading the Status Register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_T::TEST

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TEST
</font><br><p> <font size="2">
Offset: 0x14  Test Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2]</td><td>Basic</td><td><div style="word-wrap: break-word;"><b>Basic Mode
</b><br>
0 = Basic Mode Disabled.
<br>
1= IF1 Registers used as Tx Buffer, IF2 Registers used as Rx Buffer.
<br>
</div></td></tr><tr><td>
[3]</td><td>Silent</td><td><div style="word-wrap: break-word;"><b>Silent Mode
</b><br>
0 = Normal operation.
<br>
1 = The module is in Silent Mode.
<br>
</div></td></tr><tr><td>
[4]</td><td>LBack</td><td><div style="word-wrap: break-word;"><b>Loop Back Mode Enable Bit
</b><br>
0 = Loop Back Mode is Disabled.
<br>
1 = Loop Back Mode is Enabled.
<br>
</div></td></tr><tr><td>
[6:5]</td><td>Tx</td><td><div style="word-wrap: break-word;"><b>Tx[1:0]: Control of CAN_TX Pin
</b><br>
00 = Reset value, CAN_TX pin is controlled by the CAN Core.
<br>
01 = Sample Point can be monitored at CAN_TX pin.
<br>
10 = CAN_TX pin drives a dominant ('0') value.
<br>
11 = CAN_TX pin drives a recessive ('1') value.
<br>
</div></td></tr><tr><td>
[7]</td><td>Rx</td><td><div style="word-wrap: break-word;"><b>Monitors the Actual Value of CAN_RX Pin (Read Only) *(1)
</b><br>
0 = The CAN bus is dominant (CAN_RX = '0').
<br>
1 = The CAN bus is recessive (CAN_RX = '1').
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_T::BRPE

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BRPE
</font><br><p> <font size="2">
Offset: 0x18  Baud Rate Prescaler Extension Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>BRPE</td><td><div style="word-wrap: break-word;"><b>BRPE: Baud Rate Prescaler Extension
</b><br>
0x00-0x0F: By programming BRPE, the Baud Rate Prescaler can be extended to values up to 1023
<br>
The actual interpretation by the hardware is that one more than the value programmed by BRPE (MSBs) and BTIME (LSBs) is used.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_T::TXREQ1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TXREQ1
</font><br><p> <font size="2">
Offset: 0x100  Transmission Request Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>TxRqst16_1</td><td><div style="word-wrap: break-word;"><b>Transmission Request Bits 16-1 (of All Message Objects)
</b><br>
0 = This Message Object is not waiting for transmission.
<br>
1 = The transmission of this Message Object is requested and is not yet done.
<br>
These bits are read only.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_T::TXREQ2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TXREQ2
</font><br><p> <font size="2">
Offset: 0x104  Transmission Request Register 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>TxRqst32_17</td><td><div style="word-wrap: break-word;"><b>Transmission Request Bits 32-17 (of All Message Objects)
</b><br>
0 = This Message Object is not waiting for transmission.
<br>
1 = The transmission of this Message Object is requested and is not yet done.
<br>
These bits are read only.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_T::NDAT1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">NDAT1
</font><br><p> <font size="2">
Offset: 0x120  New Data Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>NewData16_1</td><td><div style="word-wrap: break-word;"><b>New Data Bits 16-1 (of All Message Objects)
</b><br>
0 = No new data has been written into the data portion of this Message Object by the Message Handler since the last time this flag was cleared by the application software.
<br>
1 = The Message Handler or the application software has written new data into the data portion of this Message Object.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_T::NDAT2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">NDAT2
</font><br><p> <font size="2">
Offset: 0x124  New Data Register 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>NewData32_17</td><td><div style="word-wrap: break-word;"><b>New Data Bits 32-17 (of All Message Objects)
</b><br>
0 = No new data has been written into the data portion of this Message Object by the Message Handler since the last time this flag was cleared by the application software.
<br>
1 = The Message Handler or the application software has written new data into the data portion of this Message Object.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_T::IPND1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">IPND1
</font><br><p> <font size="2">
Offset: 0x140  Interrupt Pending Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>IntPnd16_1</td><td><div style="word-wrap: break-word;"><b>Interrupt Pending Bits 16-1 (of All Message Objects)
</b><br>
0 = This message object is not the source of an interrupt.
<br>
1 = This message object is the source of an interrupt.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_T::IPND2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">IPND2
</font><br><p> <font size="2">
Offset: 0x144  Interrupt Pending Register 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>IntPnd32_17</td><td><div style="word-wrap: break-word;"><b>Interrupt Pending Bits 32-17 (of All Message Objects)
</b><br>
0 = This message object is not the source of an interrupt.
<br>
1 = This message object is the source of an interrupt.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_T::MVLD1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MVLD1
</font><br><p> <font size="2">
Offset: 0x160  Message Valid Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>MsgVal16_1</td><td><div style="word-wrap: break-word;"><b>Message Valid Bits 16-1 (of All Message Objects) (Read Only)
</b><br>
0 = This Message Object is ignored by the Message Handler.
<br>
1 = This Message Object is configured and should be considered by the Message Handler.
<br>
Ex
<br>
CAN_MVLD1[0] means Message object No.1 is valid or not
<br>
If CAN_MVLD1[0] is set, message object No.1 is configured.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_T::MVLD2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MVLD2
</font><br><p> <font size="2">
Offset: 0x164  Message Valid Register 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>MsgVal32_17</td><td><div style="word-wrap: break-word;"><b>Message Valid Bits 32-17 (of All Message Objects) (Read Only)
</b><br>
0 = This Message Object is ignored by the Message Handler.
<br>
1 = This Message Object is configured and should be considered by the Message Handler.
<br>
Ex.CAN_MVLD2[15] means Message object No.32 is valid or not
<br>
If CAN_MVLD2[15] is set, message object No.32 is configured.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_T::WU_EN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">WU_EN
</font><br><p> <font size="2">
Offset: 0x168  Wake-up Enable Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>WAKUP_EN</td><td><div style="word-wrap: break-word;"><b>Wake-up Enable Bit
</b><br>
0 = The wake-up function Disabled.
<br>
1 = The wake-up function Enabled.
<br>
Note: User can wake-up system when there is a falling edge in the CAN_Rx pin.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CAN_T::WU_STATUS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">WU_STATUS
</font><br><p> <font size="2">
Offset: 0x16C  Wake-up Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>WAKUP_STS</td><td><div style="word-wrap: break-word;"><b>Wake-up Status
</b><br>
0 = No wake-up event occurred.
<br>
1 = Wake-up event occurred.
<br>
Note: This bit can be cleared by writing '0'.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CON;                   /*!< [0x0000] Control Register                                                 */
    __IO uint32_t STATUS;                /*!< [0x0004] Status Register                                                  */
    __I  uint32_t ERR;                   /*!< [0x0008] Error Counter Register                                           */
    __IO uint32_t BTIME;                 /*!< [0x000c] Bit Timing Register                                              */
    __I  uint32_t IIDR;                  /*!< [0x0010] Interrupt Identifier Register                                    */
    __IO uint32_t TEST;                  /*!< [0x0014] Test Register                                                    */
    __IO uint32_t BRPE;                  /*!< [0x0018] Baud Rate Prescaler Extension Register                           */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO CAN_IF_T IF[2];
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE2[8];
    /// @endcond //HIDDEN_SYMBOLS
    __I  uint32_t TXREQ1;                /*!< [0x0100] Transmission Request Register 1                                  */
    __I  uint32_t TXREQ2;                /*!< [0x0104] Transmission Request Register 2                                  */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE3[6];
    /// @endcond //HIDDEN_SYMBOLS
    __I  uint32_t NDAT1;                 /*!< [0x0120] New Data Register 1                                              */
    __I  uint32_t NDAT2;                 /*!< [0x0124] New Data Register 2                                              */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE4[6];
    /// @endcond //HIDDEN_SYMBOLS
    __I  uint32_t IPND1;                 /*!< [0x0140] Interrupt Pending Register 1                                     */
    __I  uint32_t IPND2;                 /*!< [0x0144] Interrupt Pending Register 2                                     */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE5[6];
    /// @endcond //HIDDEN_SYMBOLS
    __I  uint32_t MVLD1;                 /*!< [0x0160] Message Valid Register 1                                         */
    __I  uint32_t MVLD2;                 /*!< [0x0164] Message Valid Register 2                                         */
    __IO uint32_t WU_EN;                 /*!< [0x0168] Wake-up Enable Control Register                                  */
    __IO uint32_t WU_STATUS;             /*!< [0x016c] Wake-up Status Register                                          */

} CAN_T;

/**
    @addtogroup CAN_CONST CAN Bit Field Definition
    Constant Definitions for CAN Controller
@{ */

#define CAN_CON_INIT_Pos                 (0)                                               /*!< CAN_T::CON: Init Position              */
#define CAN_CON_INIT_Msk                 (0x1ul << CAN_CON_INIT_Pos)                       /*!< CAN_T::CON: Init Mask                  */

#define CAN_CON_IE_Pos                   (1)                                               /*!< CAN_T::CON: IE Position                */
#define CAN_CON_IE_Msk                   (0x1ul << CAN_CON_IE_Pos)                         /*!< CAN_T::CON: IE Mask                    */

#define CAN_CON_SIE_Pos                  (2)                                               /*!< CAN_T::CON: SIE Position               */
#define CAN_CON_SIE_Msk                  (0x1ul << CAN_CON_SIE_Pos)                        /*!< CAN_T::CON: SIE Mask                   */

#define CAN_CON_EIE_Pos                  (3)                                               /*!< CAN_T::CON: EIE Position               */
#define CAN_CON_EIE_Msk                  (0x1ul << CAN_CON_EIE_Pos)                        /*!< CAN_T::CON: EIE Mask                   */

#define CAN_CON_DAR_Pos                  (5)                                               /*!< CAN_T::CON: DAR Position               */
#define CAN_CON_DAR_Msk                  (0x1ul << CAN_CON_DAR_Pos)                        /*!< CAN_T::CON: DAR Mask                   */

#define CAN_CON_CCE_Pos                  (6)                                               /*!< CAN_T::CON: CCE Position               */
#define CAN_CON_CCE_Msk                  (0x1ul << CAN_CON_CCE_Pos)                        /*!< CAN_T::CON: CCE Mask                   */

#define CAN_CON_TEST_Pos                 (7)                                               /*!< CAN_T::CON: Test Position              */
#define CAN_CON_TEST_Msk                 (0x1ul << CAN_CON_TEST_Pos)                       /*!< CAN_T::CON: Test Mask                  */

#define CAN_STATUS_LEC_Pos               (0)                                               /*!< CAN_T::STATUS: LEC Position            */
#define CAN_STATUS_LEC_Msk               (0x7ul << CAN_STATUS_LEC_Pos)                     /*!< CAN_T::STATUS: LEC Mask                */

#define CAN_STATUS_TXOK_Pos              (3)                                               /*!< CAN_T::STATUS: TxOK Position           */
#define CAN_STATUS_TXOK_Msk              (0x1ul << CAN_STATUS_TXOK_Pos)                    /*!< CAN_T::STATUS: TxOK Mask               */

#define CAN_STATUS_RXOK_Pos              (4)                                               /*!< CAN_T::STATUS: RxOK Position           */
#define CAN_STATUS_RXOK_Msk              (0x1ul << CAN_STATUS_RXOK_Pos)                    /*!< CAN_T::STATUS: RxOK Mask               */

#define CAN_STATUS_EPASS_Pos             (5)                                               /*!< CAN_T::STATUS: EPass Position          */
#define CAN_STATUS_EPASS_Msk             (0x1ul << CAN_STATUS_EPASS_Pos)                   /*!< CAN_T::STATUS: EPass Mask              */

#define CAN_STATUS_EWARN_Pos             (6)                                               /*!< CAN_T::STATUS: EWarn Position          */
#define CAN_STATUS_EWARN_Msk             (0x1ul << CAN_STATUS_EWARN_Pos)                   /*!< CAN_T::STATUS: EWarn Mask              */

#define CAN_STATUS_BOFF_Pos              (7)                                               /*!< CAN_T::STATUS: BOff Position           */
#define CAN_STATUS_BOFF_Msk              (0x1ul << CAN_STATUS_BOFF_Pos)                    /*!< CAN_T::STATUS: BOff Mask               */

#define CAN_ERR_TEC_Pos                  (0)                                               /*!< CAN_T::ERR: TEC Position               */
#define CAN_ERR_TEC_Msk                  (0xfful << CAN_ERR_TEC_Pos)                       /*!< CAN_T::ERR: TEC Mask                   */

#define CAN_ERR_REC_Pos                  (8)                                               /*!< CAN_T::ERR: REC Position               */
#define CAN_ERR_REC_Msk                  (0x7ful << CAN_ERR_REC_Pos)                       /*!< CAN_T::ERR: REC Mask                   */

#define CAN_ERR_RP_Pos                   (15)                                              /*!< CAN_T::ERR: RP Position                */
#define CAN_ERR_RP_Msk                   (0x1ul << CAN_ERR_RP_Pos)                         /*!< CAN_T::ERR: RP Mask                    */

#define CAN_BTIME_BRP_Pos                (0)                                               /*!< CAN_T::BTIME: BRP Position             */
#define CAN_BTIME_BRP_Msk                (0x3ful << CAN_BTIME_BRP_Pos)                     /*!< CAN_T::BTIME: BRP Mask                 */

#define CAN_BTIME_SJW_Pos                (6)                                               /*!< CAN_T::BTIME: SJW Position             */
#define CAN_BTIME_SJW_Msk                (0x3ul << CAN_BTIME_SJW_Pos)                      /*!< CAN_T::BTIME: SJW Mask                 */

#define CAN_BTIME_TSEG1_Pos              (8)                                               /*!< CAN_T::BTIME: TSeg1 Position           */
#define CAN_BTIME_TSEG1_Msk              (0xful << CAN_BTIME_TSEG1_Pos)                    /*!< CAN_T::BTIME: TSeg1 Mask               */

#define CAN_BTIME_TSEG2_Pos              (12)                                              /*!< CAN_T::BTIME: TSeg2 Position           */
#define CAN_BTIME_TSEG2_Msk              (0x7ul << CAN_BTIME_TSEG2_Pos)                    /*!< CAN_T::BTIME: TSeg2 Mask               */

#define CAN_IIDR_IntId_Pos               (0)                                               /*!< CAN_T::IIDR: IntId Position            */
#define CAN_IIDR_IntId_Msk               (0xfffful << CAN_IIDR_IntId_Pos)                  /*!< CAN_T::IIDR: IntId Mask                */

#define CAN_TEST_BASIC_Pos               (2)                                               /*!< CAN_T::TEST: Basic Position            */
#define CAN_TEST_BASIC_Msk               (0x1ul << CAN_TEST_BASIC_Pos)                     /*!< CAN_T::TEST: Basic Mask                */

#define CAN_TEST_SILENT_Pos              (3)                                               /*!< CAN_T::TEST: Silent Position           */
#define CAN_TEST_SILENT_Msk              (0x1ul << CAN_TEST_SILENT_Pos)                    /*!< CAN_T::TEST: Silent Mask               */

#define CAN_TEST_LBACK_Pos               (4)                                               /*!< CAN_T::TEST: LBack Position            */
#define CAN_TEST_LBACK_Msk               (0x1ul << CAN_TEST_LBACK_Pos)                     /*!< CAN_T::TEST: LBack Mask                */

#define CAN_TEST_Tx_Pos                  (5)                                               /*!< CAN_T::TEST: Tx Position               */
#define CAN_TEST_Tx_Msk                  (0x3ul << CAN_TEST_Tx_Pos)                        /*!< CAN_T::TEST: Tx Mask                   */

#define CAN_TEST_Rx_Pos                  (7)                                               /*!< CAN_T::TEST: Rx Position               */
#define CAN_TEST_Rx_Msk                  (0x1ul << CAN_TEST_Rx_Pos)                        /*!< CAN_T::TEST: Rx Mask                   */

#define CAN_BRPE_BRPE_Pos                (0)                                               /*!< CAN_T::BRPE: BRPE Position             */
#define CAN_BRPE_BRPE_Msk                (0xful << CAN_BRPE_BRPE_Pos)                      /*!< CAN_T::BRPE: BRPE Mask                 */

#define CAN_IF_CREQ_MSGNUM_Pos   (0)                                               /*!< CAN_IF_T::CREQ: MessageNumber Position*/
#define CAN_IF_CREQ_MSGNUM_Msk   (0x3ful << CAN_IF_CREQ_MSGNUM_Pos)        /*!< CAN_IF_T::CREQ: MessageNumber Mask    */

#define CAN_IF_CREQ_BUSY_Pos            (15)                                              /*!< CAN_IF_T::CREQ: Busy Position         */
#define CAN_IF_CREQ_BUSY_Msk            (0x1ul << CAN_IF_CREQ_BUSY_Pos)                   /*!< CAN_IF_T::CREQ: Busy Mask             */

#define CAN_IF_CMASK_DATAB_Pos          (0)                                               /*!< CAN_IF_T::CMASK: DAT_B Position       */
#define CAN_IF_CMASK_DATAB_Msk          (0x1ul << CAN_IF_CMASK_DATAB_Pos)                /*!< CAN_IF_T::CMASK: DAT_B Mask           */

#define CAN_IF_CMASK_DATAA_Pos          (1)                                               /*!< CAN_IF_T::CMASK: DAT_A Position       */
#define CAN_IF_CMASK_DATAA_Msk          (0x1ul << CAN_IF_CMASK_DATAA_Pos)                /*!< CAN_IF_T::CMASK: DAT_A Mask           */

#define CAN_IF_CMASK_TXRQSTNEWDAT_Pos  (2)                                               /*!< CAN_IF_T::CMASK: TxRqst_NewDat Position*/
#define CAN_IF_CMASK_TXRQSTNEWDAT_Msk  (0x1ul << CAN_IF_CMASK_TXRQSTNEWDAT_Pos)        /*!< CAN_IF_T::CMASK: TxRqst_NewDat Mask   */

#define CAN_IF_CMASK_CLRINTPND_Pos      (3)                                               /*!< CAN_IF_T::CMASK: ClrIntPnd Position   */
#define CAN_IF_CMASK_CLRINTPND_Msk      (0x1ul << CAN_IF_CMASK_CLRINTPND_Pos)            /*!< CAN_IF_T::CMASK: ClrIntPnd Mask       */

#define CAN_IF_CMASK_CONTROL_Pos        (4)                                               /*!< CAN_IF_T::CMASK: Control Position     */
#define CAN_IF_CMASK_CONTROL_Msk        (0x1ul << CAN_IF_CMASK_CONTROL_Pos)              /*!< CAN_IF_T::CMASK: Control Mask         */

#define CAN_IF_CMASK_ARB_Pos            (5)                                               /*!< CAN_IF_T::CMASK: Arb Position         */
#define CAN_IF_CMASK_ARB_Msk            (0x1ul << CAN_IF_CMASK_ARB_Pos)                  /*!< CAN_IF_T::CMASK: Arb Mask             */

#define CAN_IF_CMASK_MASK_Pos           (6)                                               /*!< CAN_IF_T::CMASK: Mask Position        */
#define CAN_IF_CMASK_MASK_Msk           (0x1ul << CAN_IF_CMASK_MASK_Pos)                 /*!< CAN_IF_T::CMASK: Mask Mask            */

#define CAN_IF_CMASK_WRRD_Pos          (7)                                               /*!< CAN_IF_T::CMASK: WR_RD Position       */
#define CAN_IF_CMASK_WRRD_Msk          (0x1ul << CAN_IF_CMASK_WRRD_Pos)                /*!< CAN_IF_T::CMASK: WR_RD Mask           */

#define CAN_IF_MASK1_Msk_Pos            (0)                                               /*!< CAN_IF_T::MASK1: Msk Position         */
#define CAN_IF_MASK1_Msk_Msk            (0xfffful << CAN_IF_MASK1_Msk_Pos)               /*!< CAN_IF_T::MASK1: Msk Mask             */

#define CAN_IF_MASK2_Msk_Pos            (0)                                               /*!< CAN_IF_T::MASK2: Msk Position         */
#define CAN_IF_MASK2_Msk_Msk            (0x1ffful << CAN_IF_MASK2_Msk_Pos)               /*!< CAN_IF_T::MASK2: Msk Mask             */

#define CAN_IF_MASK2_MDIR_Pos           (14)                                              /*!< CAN_IF_T::MASK2: MDir Position        */
#define CAN_IF_MASK2_MDIR_Msk           (0x1ul << CAN_IF_MASK2_MDIR_Pos)                 /*!< CAN_IF_T::MASK2: MDir Mask            */

#define CAN_IF_MASK2_MXTD_Pos           (15)                                              /*!< CAN_IF_T::MASK2: MXtd Position        */
#define CAN_IF_MASK2_MXTD_Msk           (0x1ul << CAN_IF_MASK2_MXTD_Pos)                 /*!< CAN_IF_T::MASK2: MXtd Mask            */

#define CAN_IF_ARB1_ID_Pos              (0)                                               /*!< CAN_IF_T::ARB1: ID Position           */
#define CAN_IF_ARB1_ID_Msk              (0xfffful << CAN_IF_ARB1_ID_Pos)                 /*!< CAN_IF_T::ARB1: ID Mask               */

#define CAN_IF_ARB2_ID_Pos              (0)                                               /*!< CAN_IF_T::ARB2: ID Position           */
#define CAN_IF_ARB2_ID_Msk              (0x1ffful << CAN_IF_ARB2_ID_Pos)                 /*!< CAN_IF_T::ARB2: ID Mask               */

#define CAN_IF_ARB2_DIR_Pos             (13)                                              /*!< CAN_IF_T::ARB2: Dir Position          */
#define CAN_IF_ARB2_DIR_Msk             (0x1ul << CAN_IF_ARB2_DIR_Pos)                   /*!< CAN_IF_T::ARB2: Dir Mask              */

#define CAN_IF_ARB2_XTD_Pos             (14)                                              /*!< CAN_IF_T::ARB2: Xtd Position          */
#define CAN_IF_ARB2_XTD_Msk             (0x1ul << CAN_IF_ARB2_XTD_Pos)                   /*!< CAN_IF_T::ARB2: Xtd Mask              */

#define CAN_IF_ARB2_MSGVAL_Pos          (15)                                              /*!< CAN_IF_T::ARB2: MsgVal Position       */
#define CAN_IF_ARB2_MSGVAL_Msk          (0x1ul << CAN_IF_ARB2_MSGVAL_Pos)                /*!< CAN_IF_T::ARB2: MsgVal Mask           */

#define CAN_IF_MCON_DLC_Pos             (0)                                               /*!< CAN_IF_T::MCON: DLC Position          */
#define CAN_IF_MCON_DLC_Msk             (0xful << CAN_IF_MCON_DLC_Pos)                   /*!< CAN_IF_T::MCON: DLC Mask              */

#define CAN_IF_MCON_EOB_Pos             (7)                                               /*!< CAN_IF_T::MCON: EoB Position          */
#define CAN_IF_MCON_EOB_Msk             (0x1ul << CAN_IF_MCON_EOB_Pos)                   /*!< CAN_IF_T::MCON: EoB Mask              */

#define CAN_IF_MCON_TxRqst_Pos          (8)                                               /*!< CAN_IF_T::MCON: TxRqst Position       */
#define CAN_IF_MCON_TxRqst_Msk          (0x1ul << CAN_IF_MCON_TxRqst_Pos)                /*!< CAN_IF_T::MCON: TxRqst Mask           */

#define CAN_IF_MCON_RmtEn_Pos           (9)                                               /*!< CAN_IF_T::MCON: RmtEn Position        */
#define CAN_IF_MCON_RmtEn_Msk           (0x1ul << CAN_IF_MCON_RmtEn_Pos)                 /*!< CAN_IF_T::MCON: RmtEn Mask            */

#define CAN_IF_MCON_RXIE_Pos            (10)                                              /*!< CAN_IF_T::MCON: RxIE Position         */
#define CAN_IF_MCON_RXIE_Msk            (0x1ul << CAN_IF_MCON_RXIE_Pos)                  /*!< CAN_IF_T::MCON: RxIE Mask             */

#define CAN_IF_MCON_TXIE_Pos            (11)                                              /*!< CAN_IF_T::MCON: TxIE Position         */
#define CAN_IF_MCON_TXIE_Msk            (0x1ul << CAN_IF_MCON_TXIE_Pos)                  /*!< CAN_IF_T::MCON: TxIE Mask             */

#define CAN_IF_MCON_UMASK_Pos           (12)                                              /*!< CAN_IF_T::MCON: UMask Position        */
#define CAN_IF_MCON_UMASK_Msk           (0x1ul << CAN_IF_MCON_UMASK_Pos)                 /*!< CAN_IF_T::MCON: UMask Mask            */

#define CAN_IF_MCON_IntPnd_Pos          (13)                                              /*!< CAN_IF_T::MCON: IntPnd Position       */
#define CAN_IF_MCON_IntPnd_Msk          (0x1ul << CAN_IF_MCON_IntPnd_Pos)                /*!< CAN_IF_T::MCON: IntPnd Mask           */

#define CAN_IF_MCON_MsgLst_Pos          (14)                                              /*!< CAN_IF_T::MCON: MsgLst Position       */
#define CAN_IF_MCON_MsgLst_Msk          (0x1ul << CAN_IF_MCON_MsgLst_Pos)                /*!< CAN_IF_T::MCON: MsgLst Mask           */

#define CAN_IF_MCON_NEWDAT_Pos          (15)                                              /*!< CAN_IF_T::MCON: NewDat Position       */
#define CAN_IF_MCON_NEWDAT_Msk          (0x1ul << CAN_IF_MCON_NEWDAT_Pos)                 /*!< CAN_IF_T::MCON: NewDat Mask           */

#define CAN_IF_DAT_A1_DATA0_Pos       (0)                                               /*!< CAN_IF_T::DAT_A1: Data_0_ Position    */
#define CAN_IF_DAT_A1_DATA0_Msk       (0xfful << CAN_IF_DAT_A1_DATA0_Pos)            /*!< CAN_IF_T::DAT_A1: Data_0_ Mask        */

#define CAN_IF_DAT_A1_DATA1_Pos       (8)                                               /*!< CAN_IF_T::DAT_A1: Data_1_ Position    */
#define CAN_IF_DAT_A1_DATA1_Msk       (0xfful << CAN_IF_DAT_A1_DATA1_Pos)            /*!< CAN_IF_T::DAT_A1: Data_1_ Mask        */

#define CAN_IF_DAT_A2_DATA2_Pos       (0)                                               /*!< CAN_IF_T::DAT_A2: Data_2_ Position    */
#define CAN_IF_DAT_A2_DATA2_Msk       (0xfful << CAN_IF_DAT_A2_DATA2_Pos)            /*!< CAN_IF_T::DAT_A2: Data_2_ Mask        */

#define CAN_IF_DAT_A2_DATA3_Pos       (8)                                               /*!< CAN_IF_T::DAT_A2: Data_3_ Position    */
#define CAN_IF_DAT_A2_DATA3_Msk       (0xfful << CAN_IF_DAT_A2_DATA3_Pos)            /*!< CAN_IF_T::DAT_A2: Data_3_ Mask        */

#define CAN_IF_DAT_B1_DATA4_Pos       (0)                                               /*!< CAN_IF_T::DAT_B1: Data_4_ Position    */
#define CAN_IF_DAT_B1_DATA4_Msk       (0xfful << CAN_IF_DAT_B1_DATA4_Pos)            /*!< CAN_IF_T::DAT_B1: Data_4_ Mask        */

#define CAN_IF_DAT_B1_DATA5_Pos       (8)                                               /*!< CAN_IF_T::DAT_B1: Data_5_ Position    */
#define CAN_IF_DAT_B1_DATA5_Msk       (0xfful << CAN_IF_DAT_B1_DATA5_Pos)            /*!< CAN_IF_T::DAT_B1: Data_5_ Mask        */

#define CAN_IF_DAT_B2_DATA6_Pos       (0)                                               /*!< CAN_IF_T::DAT_B2: Data_6_ Position    */
#define CAN_IF_DAT_B2_DATA6_Msk       (0xfful << CAN_IF_DAT_B2_DATA6_Pos)            /*!< CAN_IF_T::DAT_B2: Data_6_ Mask        */

#define CAN_IF_DAT_B2_DATA7_Pos       (8)                                               /*!< CAN_IF_T::DAT_B2: Data_7_ Position    */
#define CAN_IF_DAT_B2_DATA7_Msk       (0xfful << CAN_IF_DAT_B2_DATA7_Pos)            /*!< CAN_IF_T::DAT_B2: Data_7_ Mask        */

#define CAN_TXREQ1_TXRQST16_1_Pos        (0)                                               /*!< CAN_T::TXREQ1: TxRqst16_1 Position     */
#define CAN_TXREQ1_TXRQST16_1_Msk        (0xfffful << CAN_TXREQ1_TXRQST16_1_Pos)           /*!< CAN_T::TXREQ1: TxRqst16_1 Mask         */

#define CAN_TXREQ2_TXRQST32_17_Pos       (0)                                               /*!< CAN_T::TXREQ2: TxRqst32_17 Position    */
#define CAN_TXREQ2_TXRQST32_17_Msk       (0xfffful << CAN_TXREQ2_TXRQST32_17_Pos)          /*!< CAN_T::TXREQ2: TxRqst32_17 Mask        */

#define CAN_NDAT1_NewData16_1_Pos        (0)                                               /*!< CAN_T::NDAT1: NewData16_1 Position     */
#define CAN_NDAT1_NewData16_1_Msk        (0xfffful << CAN_NDAT1_NewData16_1_Pos)           /*!< CAN_T::NDAT1: NewData16_1 Mask         */

#define CAN_NDAT2_NewData32_17_Pos       (0)                                               /*!< CAN_T::NDAT2: NewData32_17 Position    */
#define CAN_NDAT2_NewData32_17_Msk       (0xfffful << CAN_NDAT2_NewData32_17_Pos)          /*!< CAN_T::NDAT2: NewData32_17 Mask        */

#define CAN_IPND1_IntPnd16_1_Pos         (0)                                               /*!< CAN_T::IPND1: IntPnd16_1 Position      */
#define CAN_IPND1_IntPnd16_1_Msk         (0xfffful << CAN_IPND1_IntPnd16_1_Pos)            /*!< CAN_T::IPND1: IntPnd16_1 Mask          */

#define CAN_IPND2_IntPnd32_17_Pos        (0)                                               /*!< CAN_T::IPND2: IntPnd32_17 Position     */
#define CAN_IPND2_IntPnd32_17_Msk        (0xfffful << CAN_IPND2_IntPnd32_17_Pos)           /*!< CAN_T::IPND2: IntPnd32_17 Mask         */

#define CAN_MVLD1_MsgVal16_1_Pos         (0)                                               /*!< CAN_T::MVLD1: MsgVal16_1 Position      */
#define CAN_MVLD1_MsgVal16_1_Msk         (0xfffful << CAN_MVLD1_MsgVal16_1_Pos)            /*!< CAN_T::MVLD1: MsgVal16_1 Mask          */

#define CAN_MVLD2_MsgVal32_17_Pos        (0)                                               /*!< CAN_T::MVLD2: MsgVal32_17 Position     */
#define CAN_MVLD2_MsgVal32_17_Msk        (0xfffful << CAN_MVLD2_MsgVal32_17_Pos)           /*!< CAN_T::MVLD2: MsgVal32_17 Mask         */

#define CAN_WU_EN_WAKUP_EN_Pos           (0)                                               /*!< CAN_T::WU_EN: WAKUP_EN Position        */
#define CAN_WU_EN_WAKUP_EN_Msk           (0x1ul << CAN_WU_EN_WAKUP_EN_Pos)                 /*!< CAN_T::WU_EN: WAKUP_EN Mask            */

#define CAN_WU_STATUS_WAKUP_STS_Pos      (0)                                               /*!< CAN_T::WU_STATUS: WAKUP_STS Position   */
#define CAN_WU_STATUS_WAKUP_STS_Msk      (0x1ul << CAN_WU_STATUS_WAKUP_STS_Pos)            /*!< CAN_T::WU_STATUS: WAKUP_STS Mask       */

/**@}*/ /* CAN_CONST */
/**@}*/ /* end of CAN register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __CAN_REG_H__ */
