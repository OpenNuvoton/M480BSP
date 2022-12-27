/**************************************************************************//**
 * @file     spim_reg.h
 * @version  V1.00
 * @brief    SPIM register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __SPIM_REG_H__
#define __SPIM_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup SPIM Serial Peripheral Interface Controller Master Mode (SPIM)
    Memory Mapped Structure for SPIM Controller
@{ */

typedef struct
{


    /**
@var SPIM_T::CTL0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL0
</font><br><p> <font size="2">
Offset: 0x00  Control and Status Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CIPHOFF</td><td><div style="word-wrap: break-word;"><b>Cipher Disable Control
</b><br>
0 = Cipher function Enabled.
<br>
1 = Cipher function Disabled.
<br>
Note1: If there is not any KEY1(SPIM_KEY1[31:0]) or KEY2(SPIM_KEY2[31:0]) (KEY1 is 0x0000_0000 or KEY2 is 0x0000_0000), the cipher function will be disabled automatically.
<br>
Note2: When CIPHOFF(SPIM_CTL0[0]) is 0, both of KEY1(SPIM_KEY1[31:0]) and KEY2(SPIM_KEY2[31:0]) do not equal to 0x0000_0000 (i.e.
<br>
KEY1 != 0x0000_0000 and KEY2 != 0x0000_0000), cipher encryption/decryption is enabled.
<br>
Note3 : When cipher encryption/decryption is enabled, please set DESELTIM (SPIM_DMMCTL[20:16]) >= 0x10.
<br>
When cipher encryption/decryption is disabled, please set DESELTIM(SPIM_DMMCTL[20:16]) >= 0x8.
<br>
</div></td></tr><tr><td>
[2]</td><td>BALEN</td><td><div style="word-wrap: break-word;"><b>Balance the AHB Control Time Between Cipher Enable and Disable Control
</b><br>
When cipher is enabled, the AHB control signal will delay some time caused by the encoding or decoding calculation
<br>
Therefore, if set BALEN to 1, it will make the AHB signal processing time with cipher disabled be equal to that with cipher enabled.
<br>
Note: Only useful when cipher is disabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>B4ADDREN</td><td><div style="word-wrap: break-word;"><b>4-byte Address Mode Enable Control
</b><br>
0 = 4-byte address mode is disabled, and 3-byte address mode is enabled.
<br>
1 = 4-byte address mode is enabled.
<br>
Note: Used for DMA write mode, DMA read mode, and DMM mode.
<br>
</div></td></tr><tr><td>
[6]</td><td>IEN</td><td><div style="word-wrap: break-word;"><b>Interrupt Enable Control
</b><br>
0 = SPIM Interrupt Disabled.
<br>
1 = SPIM Interrupt Enabled.
<br>
</div></td></tr><tr><td>
[7]</td><td>IF</td><td><div style="word-wrap: break-word;"><b>Interrupt Flag
</b><br>
(1) Write Operation :
<br>
0 = No effect.
<br>
1 = Write 1 to clear.
<br>
(2) Read Operation :
<br>
0 = The transfer has not finished yet.
<br>
1 = The transfer has done.
<br>
</div></td></tr><tr><td>
[12:8]</td><td>DWIDTH</td><td><div style="word-wrap: break-word;"><b>Transmit/Receive Bit Length
</b><br>
This specifies how many bits are transmitted/received in one transmit/receive transaction.
<br>
0x7 = 8 bits.
<br>
0xF = 16 bits.
<br>
0x17 = 24 bits.
<br>
0x1F = 32 bits.
<br>
Others = Incorrect transfer result.
<br>
Note1: Only used for normal I/O mode.
<br>
Note2: Only 8, 16, 24, and 32 bits are allowed. Other bit length will result in incorrect transfer.
<br>
</div></td></tr><tr><td>
[14:13]</td><td>BURSTNUM</td><td><div style="word-wrap: break-word;"><b>Transmit/Receive Burst Number
</b><br>
This field specifies how many transmit/receive transactions should be executed continuously in one transfer.
<br>
0x0 = Only one transmit/receive transaction will be executed in one transfer.
<br>
0x1 = Two successive transmit/receive transactions will be executed in one transfer.
<br>
0x2 = Three successive transmit/receive transactions will be executed in one transfer.
<br>
0x3 = Four successive transmit/receive transactions will be executed in one transfer.
<br>
Note: Only used for normal I/O Mode.
<br>
</div></td></tr><tr><td>
[15]</td><td>QDIODIR</td><td><div style="word-wrap: break-word;"><b>SPI Interface Direction Select for Quad/Dual Mode
</b><br>
0 = Interface signals are input.
<br>
1 = Interface signals are output.
<br>
Note: Only used for normal I/O mode.
<br>
</div></td></tr><tr><td>
[19:16]</td><td>SUSPITV</td><td><div style="word-wrap: break-word;"><b>Suspend Interval
</b><br>
These four bits provide the configuration of suspend interval between two successive transmit/receive transactions in a transfer
<br>
The default value is 0x00
<br>
When BURSTNUM = 00, setting this field has no effect on transfer
<br>
The desired interval is obtained according to the following equation (from the last falling edge of current SPI clock to the first rising edge of next SPI clock):
<br>
  (SUSPITV+2)*period of AHB clock
<br>
  0x0 = 2 AHB clock cycles.
<br>
  0x1 = 3 AHB clock cycles.
<br>
  ......
<br>
  0xE = 16 AHB clock cycles.
<br>
  0xF = 17 AHB clock cycles.
<br>
  Note: Only used for normal I/O mode.
<br>
</div></td></tr><tr><td>
[21:20]</td><td>BITMODE</td><td><div style="word-wrap: break-word;"><b>SPI Interface Bit Mode
</b><br>
0x0 = Standard mode.
<br>
0x1 = Dual mode.
<br>
0x2 = Quad mode.
<br>
0x3 = Reserved.
<br>
Note: Only used for normal I/O mode.
<br>
</div></td></tr><tr><td>
[23:22]</td><td>OPMODE</td><td><div style="word-wrap: break-word;"><b>SPI Function Operation Mode
</b><br>
0x0 = Normal I/O mode. (Note1) (Note3)
<br>
0x1 = DMA write mode. (Note2) (Note3)
<br>
0x2 = DMA read mode. (Note3)
<br>
0x3 = Direct Memory Mapping mode (DMM mode) (Default). (Note4)
<br>
Note1 : After user uses Normal I/O mode of SPI flash controller to program the content of external SPI flash, please set CDINVAL(SPIM_CTL1[3]) to 0x1 (Set all cache data to be invalid).
<br>
Note2 : In DMA write mode, hardware will send just one page program command per operation
<br>
Users must take care of cross-page cases
<br>
After user uses DMA write mode of SPI flash controller to program the content of external SPI flash, please set CDINVAL(SPIM_CTL1[3]) to 0x1 (Set all cache data to be invalid).
<br>
Note3 : For external SPI flash with 32 MB, access address range of external SPI flash address is from 0x00000000 to 0x01FFFFFF when user uses Normal I/O mode, DMA write mode, and DMA read mode to write/read external SPI flash data
<br>
Please user check size of used SPI flash component to know access address range of external SPI flash.
<br>
Note4 : For external SPI flash with 32 MB, access address range of external SPI flash address is from 0x08000000 to 0x09FFFFFF when user uses Direct Memory mapping mode (DMM mode) to read external SPI flash data
<br>
Please user check size of used SPI flash component to know access address range of external SPI flash.
<br>
</div></td></tr><tr><td>
[31:24]</td><td>CMDCODE</td><td><div style="word-wrap: break-word;"><b>Page Program Command Code (Note4)
</b><br>
(1) 0x02 = Page program (Used for DMA Write mode).
<br>
(2) 0x32 = Quad page program with TYPE_1 program flow (Used for DMA Write mode). (Note3)
<br>
(3) 0x38 = Quad page program with TYPE_2 program flow (Used for DMA Write mode). (Note3)
<br>
(4) 0x40 = Quad page program with TYPE_3 program flow (Used for DMA Write mode). (Note3)
<br>
The Others = Reserved.
<br>
Read Command Code :
<br>
(1) 0x03 = Standard Read (Used for DMA Read/DMM mode).
<br>
(2) 0x0B = Fast Read (Used for DMA Read/DMM mode).
<br>
The fast read command code "0x0B" is similar to command code of standard read "0x03" except it can operate at highest possible frequency
<br>
(Note2)
<br>
(3) 0x3B = Fast Read Dual Output (Used for DMA Read/DMM mode).
<br>
(4) 0xBB = Fast Read Dual I/O (Used for DMA Read/DMM mode).
<br>
The fast read dual I/O command code "0xBB" is similar to command code of fast read dual output "0x3B" but with capability to input the address bits two bits per clock
<br>
(Note2)
<br>
(5) 0xEB = Fast quad read (Used for DMA Read/DMM mode).
<br>
(6) 0xE7 = Word quad read (Used for DMA Read/DMM mode).
<br>
The command code of word quad read "0xE7" is similar to command code of fast quad read "0xEB" except that the lowest address bit must equal to 0 and the number of dummy cycles is less than fast quad read
<br>
(Note2)
<br>
(7) 0x0D = DTR/DDR Fast read (Used for DMA Read/DMM mode).
<br>
(8) 0xBD = DTR/DDR dual read (Used for DMA Read/DMM mode).
<br>
(9) 0xED = DTR/DDR quad read (Used for DMA Read/DMM mode).
<br>
The Others command codes are Reserved.
<br>
The DTR/DDR read commands "0x0D,0xBD,0xED" improves throughput by transferring address and data on both the falling and rising edge of SPI flash clock (SPIM_CLK)
<br>
It is similar to those commands "0x0B, 0xBB, 0xEB" but allows transfer of address and data on rising edge and falling edge of SPI flash output clock
<br>
(Note2)
<br>
Note1: Quad mode of SPI Flash must be enabled first by normal I/O mode before using quad page program/quad read commands.
<br>
Note2: See SPI flash specifications for support items.
<br>
Note3: For TYPE_1, TYPE_2, and TYPE_3 of page program command code, refer to Figure 7.19-3, Figure 7.19-4, and Figure 7.19-5.
<br>
Note4: Please disable "continuous read mode" and "burst wrap mode" before DMA write mode of SPI flash controller is used to program data of external SPI flash
<br>
After user uses DMA write mode of SPI flash controller to program the content of external SPI flash, please set CDINVAL(SPIM_CTL1[3]) to 0x1 (Set all cache data to be invalid).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SPIM_T::CTL1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL1
</font><br><p> <font size="2">
Offset: 0x04  Control Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SPIMEN</td><td><div style="word-wrap: break-word;"><b>Go and Busy Status
</b><br>
(1) Write Operation :
<br>
0 = No effect.
<br>
1 = Start the transfer
<br>
This bit remains set during the transfer and is automatically cleared after transfer finished.
<br>
(2) Read Operation :
<br>
0 = The transfer has done.
<br>
1 = The transfer has not finished yet.
<br>
Note: All registers should be set before writing 1 to the SPIMEN bit
<br>
When a transfer is in progress, you should not write to any register of this peripheral.
<br>
</div></td></tr><tr><td>
[1]</td><td>CACHEOFF</td><td><div style="word-wrap: break-word;"><b>Cache Memory Function Disable Control
</b><br>
0 = Cache memory function enable. (Default value)
<br>
1 = Cache memory function disable.
<br>
Note: When CCM mode is enabled, the cache function will be disable by hardware automatically
<br>
When CCM mode is disabled, the cache function can be enable or disable by user.
<br>
</div></td></tr><tr><td>
[2]</td><td>CCMEN</td><td><div style="word-wrap: break-word;"><b>CCM (Core Coupled Memory) Mode Enable Control
</b><br>
0 = CCM mode disable. (Default value)
<br>
1 = CCM mode enable.
<br>
Note1: When CCM mode is enabled, the cache function will be disable by hardware automatically
<br>
When CCM mode is disabled, the cache function can be enabled or disabled by user.
<br>
Note2: When CCM mode is disabled, user accesses the core coupled memory by bus master
<br>
In this case, the SPI flash controller will send error response via HRESP bus signal to bus master.
<br>
Note3: When CCM mode needs to be enabled, user sets CCMEN to 1 and needs to read this register to show the current hardware status
<br>
When reading data of CCMEN is 1, MCU can start to read data from CCM memory space or write data to CCM memory space.
<br>
</div></td></tr><tr><td>
[3]</td><td>CDINVAL</td><td><div style="word-wrap: break-word;"><b>Cache Data Invalid Enable Control
</b><br>
(1) Write Operation:
<br>
0 = No effect.
<br>
1 = Set all cache data to be invalid. This bit is cleared by hardware automatically.
<br>
(2) Read Operation : No effect
<br>
Note: When SPI flash memory is page erasing or whole flash erasing, please set CDINVAL to 0x1
<br>
After user uses normal I/O mode or DMA write mode of SPI flash controller to program or erase the content of external SPI flash, please set CDINVAL to 0x1.
<br>
</div></td></tr><tr><td>
[4]</td><td>SS</td><td><div style="word-wrap: break-word;"><b>Slave Select Active Enable Control
</b><br>
0 = SPIM_SS is in active level.
<br>
1 = SPIM_SS is in inactive level (Default).
<br>
Note: This interface can only drive one device/slave at a given time
<br>
Therefore, the slave selects of the selected device must be set to its active level before starting any read or write transfer
<br>
Functional description of SSACTPOL(SPIM_CTL1[5]) and SS is shown in Table 2.
<br>
</div></td></tr><tr><td>
[5]</td><td>SSACTPOL</td><td><div style="word-wrap: break-word;"><b>Slave Select Active Level
</b><br>
It defines the active level of device/slave select signal (SPIM_SS), and we show in Table 2.
<br>
0 = The SPIM_SS slave select signal is active low.
<br>
1 = The SPIM_SS slave select signal is active high.
<br>
</div></td></tr><tr><td>
[11:8]</td><td>IDLETIME</td><td><div style="word-wrap: break-word;"><b>Idle Time Interval
</b><br>
In DMM mode, IDLETIME is set to control the minimum idle time between two SPI Flash accesses.
<br>
Minimum idle time = (IDLETIME + 1) * AHB clock cycle time.
<br>
Note1: Only used for DMM mode.
<br>
Note2 : AHB clock cycle time = 1/AHB clock frequency.
<br>
</div></td></tr><tr><td>
[31:16]</td><td>DIVIDER</td><td><div style="word-wrap: break-word;"><b>Clock Divider Register
</b><br>
The value in this field is the frequency divider of the AHB clock (HCLK) to generate the serial SPI output clock "SCLK" on the output SPIM_CLK pin
<br>
The desired frequency is obtained according to the following equation:
<br>
Note1: When set DIVIDER to zero, the frequency of SPIM_CLK will be equal to the frequency of HCLK.
<br>
Note2: SCLK is serial SPI output clock.
<br>
Note3: Please check the specification of the used SPI flash component to decide the frequency of SPI flash clock.
<br>
Note4: For DTR/DDR read commands "0x0D, 0xBD, 0xED", the setting values of DIVIDER are only 1,2,4,8,16,32,..., where n = 0,1,2,3,4, ...
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SPIM_T::RXCLKDLY

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">RXCLKDLY
</font><br><p> <font size="2">
Offset: 0x0C  RX Clock Delay Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>DWDELSEL</td><td><div style="word-wrap: break-word;"><b>SPI flash deselect time interval of DMA write mode
</b><br>
For DMA write mode only
<br>
This register sets the deselect time interval of SPI flash (i.e.
<br>
time interval of inactive level of SPIM_SS) when SPI flash controller operates on DMA write mode
<br>
(Note1)
<br>
Deselect time interval of DMA write mode = (DWDELSEL + 1) * AHB clock cycle time (Note2).
<br>
Note1: Please user check the used external SPI flash component to set this register value
<br>
In general case, the deselect time interval of SPI flash is greater than 50 ns when SPI flash performs the program operation.
<br>
Note2: AHB clock cycle time = 1/AHB clock frequency.
<br>
</div></td></tr><tr><td>
[18:16]</td><td>RDDLYSEL</td><td><div style="word-wrap: break-word;"><b>Sampling Clock Delay Selection for Received Data
</b><br>
For Normal I/O mode, DMA read mode, DMA write mode, and direct memory mapping mode
<br>
Determine the number of inserted delay cycles
<br>
Used to adjust the sampling clock of received data to latch the correct data.
<br>
0x0 : No delay. (Default Value)
<br>
0x1 : Delay 1 SPI flash clock.
<br>
0x2 : Delay 2 SPI flash clocks.
<br>
0x3 : Delay 3 SPI flash clocks.
<br>
...
<br>
0x7 : Delay 7 SPI flash clocks
<br>
Note : We can use manufacturer id or device id of external SPI flash component to determine the correct setting value of RDDLYSEL, and we give example as follows.
<br>
For example, manufacturer id and device id of external SPI flash for some vendor are 0xEF and 0x1234 separately
<br>
Firstly, we set RDDLYSEL to 0x0, and use read manufacturer id/device id command to read the manufacturer id of external SPI flash by using normal I/O mode (the manufacturer id is 0xEF (1110_1111) in this example).
<br>
If manufacturer id which reads from external SPI flash is 0xF7 (1111_0111), it denotes that manufacturer id is shifted the right by 1 bit and most significant bit (MSB) of manufacturer id is assigned to 1
<br>
According to manufacturer id reads from external SPI flash, we need to set RDDLYSEL to 0x1 to receive SPI flash data correctly.
<br>
</div></td></tr><tr><td>
[20]</td><td>RDEDGE</td><td><div style="word-wrap: break-word;"><b>Sampling Clock Edge Selection for Received Data
</b><br>
For Normal I/O mode, DMA read mode, DMA write mode, and direct memory mapping mode
<br>
0 : Use SPI input clock rising edge to sample received data. (Default Value)
<br>
1 : Use SPI input clock falling edge to sample received data.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SPIM_T::RX[4]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">RX[4]
</font><br><p> <font size="2">
Offset: 0x10 ~ 0x1C  Data Receive Register 0 ~ 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>RXDAT</td><td><div style="word-wrap: break-word;"><b>Data Receive Register
</b><br>
The Data Receive Registers hold the received data of the last executed transfer.
<br>
Number of valid RX registers is specified in SPIM_CTL0[BURSTNUM]
<br>
If BURSTNUM > 0, received data are held in the most significant RXDAT register first.
<br>
Number of valid-bit is specified in SPIM_CTL0[DWIDTH]
<br>
If DWIDTH is 16, 24, or 32, received data are held in the least significant byte of RXDAT register first.
<br>
In a byte, received data are held in the most significant bit of RXDAT register first.
<br>
Example 1: If SPIM_CTL0[BURSTNUM] = 0x3 and SPIM_CTL1[DWIDTH] = 0x17, received data will be held in the order SPIM_RX3[23:0], SPIM_RX2[23:0], SPIM_RX1[23:0], SPIM_RX0[23:0].
<br>
Example 2: If SPIM_CTL0[BURSTNUM = 0x0 and SPIM_CTL0[DWIDTH] = 0x17, received data will be held in the order SPIM_RX0[7:0], SPIM_RX0[15:8], SPIM_RX0[23:16].
<br>
Example 3: If SPIM_CTL0[BURSTNUM = 0x0 and SPIM_CTL0[DWIDTH] = 0x07, received data will be held in the order SPIM_RX0[7], SPIM_RX0[6], ...,
<br>
SPIM_RX0[0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SPIM_T::TX[4]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TX[4]
</font><br><p> <font size="2">
Offset: 0x20 ~ 0x2C  Data Transmit Register 0 ~ 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>TXDAT</td><td><div style="word-wrap: break-word;"><b>Data Transmit Register
</b><br>
The Data Transmit Registers hold the data to be transmitted in next transfer.
<br>
Number of valid TXDAT registers is specified in SPIM_CTL0[BURSTNUM]
<br>
If BURSTNUM > 0, data are transmitted in the most significant TXDAT register first.
<br>
Number of valid-bit is specified in SPIM_CTL0[DWIDTH]
<br>
If DWIDTH is 16, 24, or 32, data are transmitted in the least significant byte of TXDAT register first.
<br>
In a byte, data are transmitted in the most significant bit of TXDAT register first.
<br>
Example 1: If SPIM_CTL0[BURSTNUM] = 0x3 and SPIM_CTL1[DWIDTH] = 0x17, data will be transmitted in the order SPIM_TX3[23:0], SPIM_TX2[23:0], SPIM_TX1[23:0], SPIM_TX0[23:0] in next transfer.
<br>
Example 2: If SPIM_CTL0[BURSTNUM] = 0x0 and SPIM_CTL0[DWIDTH] = 0x17, data will be transmitted in the order SPIM_TX0[7:0], SPIM_TX0[15:8], SPIM_TX0[23:16] in next transfer.
<br>
Example 3: If SPIM_CTL0[BURSTNUM] = 0x0 and SPIM_CTL0[DWIDTH] = 0x07, data will be transmitted in the order SPIM_TX0[7], SPIM_TX0[6], ...,
<br>
SPIM_TX0[0] in next transfer.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SPIM_T::SRAMADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SRAMADDR
</font><br><p> <font size="2">
Offset: 0x30  SRAM Memory Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>ADDR</td><td><div style="word-wrap: break-word;"><b>SRAM Memory Address
</b><br>
For DMA Read mode, this is the destination address for DMA transfer.
<br>
For DMA Write mode, this is the source address for DMA transfer.
<br>
Note: This address must be word-aligned.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SPIM_T::DMACNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DMACNT
</font><br><p> <font size="2">
Offset: 0x34  DMA Transfer Byte Count Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:0]</td><td>DMACNT</td><td><div style="word-wrap: break-word;"><b>DMA Transfer Byte Count Register
</b><br>
It indicates the transfer length for DMA process.
<br>
Note1: The unit for counting is byte.
<br>
Note2: The number must be the multiple of 4.
<br>
Note3: Please check specification of used SPI flash to know maximum byte length of page program.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SPIM_T::FADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">FADDR
</font><br><p> <font size="2">
Offset: 0x38  SPI Flash Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>ADDR</td><td><div style="word-wrap: break-word;"><b>SPI Flash Address Register
</b><br>
For DMA Read mode, this is the source address for DMA transfer.
<br>
For DMA Write mode, this is the destination address for DMA transfer.
<br>
Note 1 : This address must be word-aligned.
<br>
Note 2 : For external SPI flash with 32 MB, the value of this SPI flash address register "ADDR" is from 0x00000000 to 0x01FFFFFF when user uses DMA write mode and DMA read mode to write/read external SPI flash data
<br>
Please user check size of used SPI flash component to know access address range of external SPI flash.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SPIM_T::KEY1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">KEY1
</font><br><p> <font size="2">
Offset: 0x3C  Cipher Key1 Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY1</td><td><div style="word-wrap: break-word;"><b>Cipher Key1 Register
</b><br>
This is the KEY1 data for cipher function.
<br>
Note1: If there is not any KEY1(SPIM_KEY1[31:0]) or KEY2(SPIM_KEY2[31:0]) (KEY1 is 0x0000_0000 or KEY2 is 0x0000_0000), the cipher function will be disabled automatically.
<br>
Note2: When CIPHOFF(SPIM_CTL0[0]) is 0, both of KEY1(SPIM_KEY1[31:0]) and KEY2(SPIM_KEY2[31:0]) do not equal to 0x0000_0000 (i.e.
<br>
KEY1 != 0x0000_0000 and KEY2 != 0x0000_0000), cipher encryption/decryption is enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SPIM_T::KEY2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">KEY2
</font><br><p> <font size="2">
Offset: 0x40  Cipher Key2 Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>KEY2</td><td><div style="word-wrap: break-word;"><b>Cipher Key2 Register
</b><br>
This is the KEY2 data for cipher function.
<br>
Note1: If there is not any KEY1(SPIM_KEY1[31:0]) or KEY2(SPIM_KEY2[31:0]) (KEY1 is 0x0000_0000 or KEY2 is 0x0000_0000), the cipher function will be disabled automatically.
<br>
Note2: When CIPHOFF(SPIM_CTL0[0]) is 0, both of KEY1(SPIM_KEY1[31:0]) and KEY2(SPIM_KEY2[31:0]) do not equal to 0x0000_0000 (i.e.
<br>
KEY1 != 0x0000_0000 and KEY2 != 0x0000_0000), cipher encryption/decryption is enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SPIM_T::DMMCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DMMCTL
</font><br><p> <font size="2">
Offset: 0x44  Direct Memory Mapping Mode Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:8]</td><td>CRMDAT</td><td><div style="word-wrap: break-word;"><b>Mode bits data for Continuous Read Mode (or performance enhance mode) (Default value = 0)
</b><br>
Only for direct memory mapping mode
<br>
Set the mode bits data for continuous read mode (or performance enhance mode).
<br>
When we set this mode bits currently (Note1) and set CREN(SPIM_DMMCTL[25]), this reduces the command phase by eight clocks and allows the read address to be immediately entered after SPIM_SS asserted to active
<br>
(Note1)
<br>
Note1 : Please check the used SPI flash specification to know the setting value of this mode bits data, and different SPI flash vendor may use different setting values.
<br>
Note2 : CRMDAT needs to used with CREN(SPIM_DMMCTL[25]).
<br>
</div></td></tr><tr><td>
[20:16]</td><td>DESELTIM</td><td><div style="word-wrap: break-word;"><b>SPI Flash Deselect Time
</b><br>
Only for direct memory mapping mode
<br>
Set the minimum time width of SPI flash deselect time (i.e.
<br>
Minimum SPIM_SS deselect time), and we show in Figure 7.19-8.
<br>
(1) Cache function disable :
<br>
Minimum time width of SPIM_SS deselect time = (DESELTIM + 1) * AHB clock cycle time.
<br>
(2) Cache function enable :
<br>
Minimum time width of SPIM_SS deselect time = (DESELTIM + 4) * AHB clock cycle time.
<br>
Note1 : AHB clock cycle time = 1/AHB clock frequency.
<br>
Note2 : When cipher encryption/decryption is enabled, please set this register value >= 0x10
<br>
When cipher encryption/decryption is disabled, please set this register value >= 0x8.
<br>
Note3 : Please check the used SPI flash specification to know the setting value of this register, and different SPI flash vendor may use different setting values.
<br>
</div></td></tr><tr><td>
[24]</td><td>BWEN</td><td><div style="word-wrap: break-word;"><b>16 bytes Burst Wrap Mode Enable Control Register (Default value = 0)
</b><br>
Only for WINBOND SPI flash, direct memory mapping mode, Cache enable, and read command code "0xEB, and 0xE7"
<br>
0 = Burst Wrap Mode Disable. (Default)
<br>
1 = Burst Wrap Mode Enable.
<br>
In direct memory mapping mode, both of quad read commands "0xEB" and "0xE7" support burst wrap mode for cache application and performance enhance
<br>
For cache application, the burst wrap mode can be used to fill the cache line quickly (In this SPI flash controller, we use cache data line with 16 bytes size)
<br>
For performance enhance with direct memory mapping mode and cache enable, when cache data is miss, the burst wrap mode can let MCU get the required SPI flash data quickly.
<br>
</div></td></tr><tr><td>
[25]</td><td>CREN</td><td><div style="word-wrap: break-word;"><b>Continuous Read Mode Enable Control
</b><br>
Only for direct memory mapping mode, read command codes 0xBB, 0xEB, 0xE7, 0x0D, 0xBD, 0xED (Note2)
<br>
0 = Continuous Read Mode Disable. (Default)
<br>
1 = Continuous Read Mode Enable.
<br>
For read operations of SPI flash, commands of fast read quad I/O (0xEB), word read quad I/O (0xE7 in Winbond SPI flash), fast read dual I/O (0xBB), DTR/DDR fast read (0x0D), DTR/DDR fast read dual I/O (0xBD), and DTR/DDR fast read quad I/O (0xED) can further reduce command overhead through setting the "continuous read mode" bits (8 bits) after the input address data.
<br>
Note: When user uses function of continuous read mode and sets USETEN (SPIM_CTL2[16]) to 1, CRMDAT(SPIM_DMMCTL[15:8]) must be set by used SPI flash specifications
<br>
When user uses function of continuous read mode and sets USETEN(SPIM_CTL2[16]) to 0, CRMDAT(SPIM_DMMCTL[15:8]) is set by default value of WINBOND SPI flash.
<br>
</div></td></tr><tr><td>
[26]</td><td>UACTSCLK</td><td><div style="word-wrap: break-word;"><b>User Sets SPI Flash Active SCLK Time
</b><br>
Only for direct memory mapping mode, DMA write mode, and DMA read mode
<br>
0 = According to DIVIDER(SPIM_CTL1[31:16]), ACTSCLKT(SPIM_DMMCTL[31:28]) is set by hardware automatically
<br>
(Default value)
<br>
1 = Set ACTSCLKT(SPIM_DMMCTL[31:28]) by user manually.
<br>
When user wants to set ACTSCLKT(SPIM_DMMCTL[31:28]) manually, please set UACTSCLK to 1.
<br>
</div></td></tr><tr><td>
[31:28]</td><td>ACTSCLKT</td><td><div style="word-wrap: break-word;"><b>SPI Flash Active SCLK Time
</b><br>
Only for direct memory mapping mode, DMA write mode, and DMA read mode
<br>
This register sets time interval between SPIM SS active edge and the position edge of the first serial SPI output clock, and we show in Figure 7.19-8.
<br>
(1) ACTSCLKT = 0 (function disable) :.
<br>
Time interval = 1 AHB clock cycle time.
<br>
(2) ACTSCLKT != 0 (function enable) :
<br>
Time interval = (ACTSCLKT + 3) * AHB clock cycle time.
<br>
Note1 : AHB clock cycle time = 1/AHB clock frequency.
<br>
Note2 : SCLK is SPI output clock
<br>
Note3 : Please check the used SPI flash specification to know the setting value of this register, and different SPI flash vendor may use different setting values.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SPIM_T::CTL2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL2
</font><br><p> <font size="2">
Offset: 0x48  Control Register 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[16]</td><td>USETEN</td><td><div style="word-wrap: break-word;"><b>User Set Value Enable Control
</b><br>
Only for direct memory mapping mode and DMA read mode with read commands 0x03,0x0B,0x3B,0xBB,0xEB,0xE7
<br>
0 = Hardware circuit of SPI flash controller will use the following default values of DCNUM(SPIM_CTL2[28:24]) and CRMDAT(SPIM_DMMCTL[15:8]) to configure SPI flash operations automatically.
<br>
Dummy cycle number (DCNUM) :
<br>
Dummy cycle number for read command 0x03 : 0x0
<br>
Dummy cycle number for read command 0x0B : 0x8
<br>
Dummy cycle number for read command 0x3B : 0x8
<br>
Dummy cycle number for read command 0xBB : 0x0
<br>
Dummy cycle number for read command 0xEB : 0x4
<br>
Dummy cycle number for read command 0xE7 : 0x2
<br>
Mode bits data for continuous read mode (CRMDAT) : 0x20
<br>
1 = If DCNUM(SPIM_CTL2[28:24]) and CRMDAT(SPIM_DMMCTL[15:8]) are not set as above default values, user must set USETEN to 0x1, DCNUM(SPIM_CTL2[28:24]) and CRMDAT(SPIM_DMMCTL[15:8]) to configure SPI flash operations manually.
<br>
For DTR/DDR command codes 0x0D, 0xBD, and 0xED, please set USETEN to 0x1.
<br>
</div></td></tr><tr><td>
[20]</td><td>DTRMPOFF</td><td><div style="word-wrap: break-word;"><b>Mode Phase OFF for DTR/DDR Command Codes 0x0D, 0xBD, and 0xED
</b><br>
Only for direct memory mapping mode and DMA read mode (Note1)
<br>
0 = mode cycle number (or performance enhance cycle number) does not equal to 0x0 in DTR/DDR read command codes 0x0D, 0xBD, and 0xED.
<br>
1 = mode cycle number (or performance enhance cycle number) equals to 0x0 in DTR/DDR read command codes 0x0D, 0xBD, and 0xED.
<br>
Note1 : Please check the used SPI flash specification to know the mode cycle number (or performance enhance cycle number) for DTR/DDR command codes 0x0D, 0xBD, and 0xED.
<br>
</div></td></tr><tr><td>
[28:24]</td><td>DCNUM</td><td><div style="word-wrap: break-word;"><b>Dummy Cycle Number
</b><br>
Only for direct memory mapping mode and DMA read mode (Note1)
<br>
Set number of dummy cycles
<br>
(1) For non-DTR/non-DDR command codes 0x03, 0x0B, 0x3B, 0xBB, 0xEB, and 0xE7 :
<br>
When read command code do not need any dummy cycles (i.e.
<br>
dummy cycle number = 0x0), user must set DCNUM to 0x0.
<br>
For command code 0xBB, if both mode cycle number (or performance enhance cycle number) and dummy cycle number do not equal to 0x0 simultaneously, user must set DCNUM to "mode cycle number + dummy cycle number" by used SPI flash specification.
<br>
For command code 0xBB, if there is only dummy cycle number (i.e.
<br>
dummy cycle number != 0x0 and mode cycle number = 0x0 (or performance enhance cycle number = 0x0)), user set DCNUM to dummy cycle number by used SPI flash specification.
<br>
For command codes 0x0B, 0x3B, 0xEB, and 0xE7, user only set DCNUM to dummy cycle number by used SPI flash specification.
<br>
(2) For DTR/DDR command codes 0x0D, 0xBD, and 0xED :
<br>
user sets DCNUM to dummy cycle number and DTRMPOFF(SPIM_CTL2[20]) by used SPI flash specification.
<br>
Note1 : Number of dummy cycles depends on the frequency of SPI output clock, SPI flash vendor, and read command types
<br>
Please check the used SPI flash specification to know the setting value of this number of dummy cycles.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CTL0;                  /*!< [0x0000] Control and Status Register 0                                    */
    __IO uint32_t CTL1;                  /*!< [0x0004] Control Register 1                                               */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t RXCLKDLY;              /*!< [0x000c] RX Clock Delay Control Register                                  */
    __I  uint32_t RX[4];                 /*!< [0x0010] ~ [0x001C] Data Receive Register 0~3                             */
    __IO uint32_t TX[4];                 /*!< [0x0020] ~ [0x002C] Data Transmit Register 0~3                            */
    __IO uint32_t SRAMADDR;              /*!< [0x0030] SRAM Memory Address Register                                     */
    __IO uint32_t DMACNT;                /*!< [0x0034] DMA Transfer Byte Count Register                                 */
    __IO uint32_t FADDR;                 /*!< [0x0038] SPI Flash Address Register                                       */
    __O  uint32_t KEY1;                  /*!< [0x003c] Cipher Key1 Register                                             */
    __O  uint32_t KEY2;                  /*!< [0x0040] Cipher Key2 Register                                             */
    __IO uint32_t DMMCTL;                /*!< [0x0044] Direct Memory Mapping Mode Control Register                      */
    __IO uint32_t CTL2;                  /*!< [0x0048] Control Register 2                                               */

} SPIM_T;

/**
    @addtogroup SPIM_CONST SPIM Bit Field Definition
    Constant Definitions for SPIM Controller
@{ */

#define SPIM_CTL0_CIPHOFF_Pos            (0)                                               /*!< SPIM_T::CTL0: CIPHOFF Position         */
#define SPIM_CTL0_CIPHOFF_Msk            (0x1ul << SPIM_CTL0_CIPHOFF_Pos)                  /*!< SPIM_T::CTL0: CIPHOFF Mask             */

#define SPIM_CTL0_BALEN_Pos              (2)                                               /*!< SPIM_T::CTL0: BALEN Position           */
#define SPIM_CTL0_BALEN_Msk              (0x1ul << SPIM_CTL0_BALEN_Pos)                    /*!< SPIM_T::CTL0: BALEN Mask               */

#define SPIM_CTL0_B4ADDREN_Pos           (5)                                               /*!< SPIM_T::CTL0: B4ADDREN Position        */
#define SPIM_CTL0_B4ADDREN_Msk           (0x1ul << SPIM_CTL0_B4ADDREN_Pos)                 /*!< SPIM_T::CTL0: B4ADDREN Mask            */

#define SPIM_CTL0_IEN_Pos                (6)                                               /*!< SPIM_T::CTL0: IEN Position             */
#define SPIM_CTL0_IEN_Msk                (0x1ul << SPIM_CTL0_IEN_Pos)                      /*!< SPIM_T::CTL0: IEN Mask                 */

#define SPIM_CTL0_IF_Pos                 (7)                                               /*!< SPIM_T::CTL0: IF Position              */
#define SPIM_CTL0_IF_Msk                 (0x1ul << SPIM_CTL0_IF_Pos)                       /*!< SPIM_T::CTL0: IF Mask                  */

#define SPIM_CTL0_DWIDTH_Pos             (8)                                               /*!< SPIM_T::CTL0: DWIDTH Position          */
#define SPIM_CTL0_DWIDTH_Msk             (0x1ful << SPIM_CTL0_DWIDTH_Pos)                  /*!< SPIM_T::CTL0: DWIDTH Mask              */

#define SPIM_CTL0_BURSTNUM_Pos           (13)                                              /*!< SPIM_T::CTL0: BURSTNUM Position        */
#define SPIM_CTL0_BURSTNUM_Msk           (0x3ul << SPIM_CTL0_BURSTNUM_Pos)                 /*!< SPIM_T::CTL0: BURSTNUM Mask            */

#define SPIM_CTL0_QDIODIR_Pos            (15)                                              /*!< SPIM_T::CTL0: QDIODIR Position         */
#define SPIM_CTL0_QDIODIR_Msk            (0x1ul << SPIM_CTL0_QDIODIR_Pos)                  /*!< SPIM_T::CTL0: QDIODIR Mask             */

#define SPIM_CTL0_SUSPITV_Pos            (16)                                              /*!< SPIM_T::CTL0: SUSPITV Position         */
#define SPIM_CTL0_SUSPITV_Msk            (0xful << SPIM_CTL0_SUSPITV_Pos)                  /*!< SPIM_T::CTL0: SUSPITV Mask             */

#define SPIM_CTL0_BITMODE_Pos            (20)                                              /*!< SPIM_T::CTL0: BITMODE Position         */
#define SPIM_CTL0_BITMODE_Msk            (0x3ul << SPIM_CTL0_BITMODE_Pos)                  /*!< SPIM_T::CTL0: BITMODE Mask             */

#define SPIM_CTL0_OPMODE_Pos             (22)                                              /*!< SPIM_T::CTL0: OPMODE Position          */
#define SPIM_CTL0_OPMODE_Msk             (0x3ul << SPIM_CTL0_OPMODE_Pos)                   /*!< SPIM_T::CTL0: OPMODE Mask              */

#define SPIM_CTL0_CMDCODE_Pos            (24)                                              /*!< SPIM_T::CTL0: CMDCODE Position         */
#define SPIM_CTL0_CMDCODE_Msk            (0xfful << SPIM_CTL0_CMDCODE_Pos)                 /*!< SPIM_T::CTL0: CMDCODE Mask             */

#define SPIM_CTL1_SPIMEN_Pos             (0)                                               /*!< SPIM_T::CTL1: SPIMEN Position          */
#define SPIM_CTL1_SPIMEN_Msk             (0x1ul << SPIM_CTL1_SPIMEN_Pos)                   /*!< SPIM_T::CTL1: SPIMEN Mask              */

#define SPIM_CTL1_CACHEOFF_Pos           (1)                                               /*!< SPIM_T::CTL1: CACHEOFF Position        */
#define SPIM_CTL1_CACHEOFF_Msk           (0x1ul << SPIM_CTL1_CACHEOFF_Pos)                 /*!< SPIM_T::CTL1: CACHEOFF Mask            */

#define SPIM_CTL1_CCMEN_Pos              (2)                                               /*!< SPIM_T::CTL1: CCMEN Position           */
#define SPIM_CTL1_CCMEN_Msk              (0x1ul << SPIM_CTL1_CCMEN_Pos)                    /*!< SPIM_T::CTL1: CCMEN Mask               */

#define SPIM_CTL1_CDINVAL_Pos            (3)                                               /*!< SPIM_T::CTL1: CDINVAL Position         */
#define SPIM_CTL1_CDINVAL_Msk            (0x1ul << SPIM_CTL1_CDINVAL_Pos)                  /*!< SPIM_T::CTL1: CDINVAL Mask             */

#define SPIM_CTL1_SS_Pos                 (4)                                               /*!< SPIM_T::CTL1: SS Position              */
#define SPIM_CTL1_SS_Msk                 (0x1ul << SPIM_CTL1_SS_Pos)                       /*!< SPIM_T::CTL1: SS Mask                  */

#define SPIM_CTL1_SSACTPOL_Pos           (5)                                               /*!< SPIM_T::CTL1: SSACTPOL Position        */
#define SPIM_CTL1_SSACTPOL_Msk           (0x1ul << SPIM_CTL1_SSACTPOL_Pos)                 /*!< SPIM_T::CTL1: SSACTPOL Mask            */

#define SPIM_CTL1_IDLETIME_Pos           (8)                                               /*!< SPIM_T::CTL1: IDLETIME Position        */
#define SPIM_CTL1_IDLETIME_Msk           (0xful << SPIM_CTL1_IDLETIME_Pos)                 /*!< SPIM_T::CTL1: IDLETIME Mask            */

#define SPIM_CTL1_DIVIDER_Pos            (16)                                              /*!< SPIM_T::CTL1: DIVIDER Position         */
#define SPIM_CTL1_DIVIDER_Msk            (0xfffful << SPIM_CTL1_DIVIDER_Pos)               /*!< SPIM_T::CTL1: DIVIDER Mask             */

#define SPIM_RXCLKDLY_DWDELSEL_Pos       (0)                                               /*!< SPIM_T::RXCLKDLY: DWDELSEL Position    */
#define SPIM_RXCLKDLY_DWDELSEL_Msk       (0xfful << SPIM_RXCLKDLY_DWDELSEL_Pos)            /*!< SPIM_T::RXCLKDLY: DWDELSEL Mask        */

#define SPIM_RXCLKDLY_RDDLYSEL_Pos       (16)                                              /*!< SPIM_T::RXCLKDLY: RDDLYSEL Position    */
#define SPIM_RXCLKDLY_RDDLYSEL_Msk       (0x7ul << SPIM_RXCLKDLY_RDDLYSEL_Pos)             /*!< SPIM_T::RXCLKDLY: RDDLYSEL Mask        */

#define SPIM_RXCLKDLY_RDEDGE_Pos         (20)                                              /*!< SPIM_T::RXCLKDLY: RDEDGE Position      */
#define SPIM_RXCLKDLY_RDEDGE_Msk         (0x1ul << SPIM_RXCLKDLY_RDEDGE_Pos)               /*!< SPIM_T::RXCLKDLY: RDEDGE Mask          */

#define SPIM_RX_RXDAT_Pos                (0)                                               /*!< SPIM_T::RX[4]: RXDAT Position          */
#define SPIM_RX_RXDAT_Msk                (0xfffffffful << SPIM_RX_RXDAT_Pos)               /*!< SPIM_T::RX[4]: RXDAT Mask              */

#define SPIM_TX_TXDAT_Pos                (0)                                               /*!< SPIM_T::TX[4]: TXDAT Position          */
#define SPIM_TX_TXDAT_Msk                (0xfffffffful << SPIM_TX_TXDAT_Pos)               /*!< SPIM_T::TX[4]: TXDAT Mask              */

#define SPIM_SRAMADDR_ADDR_Pos           (0)                                               /*!< SPIM_T::SRAMADDR: ADDR Position        */
#define SPIM_SRAMADDR_ADDR_Msk           (0xfffffffful << SPIM_SRAMADDR_ADDR_Pos)          /*!< SPIM_T::SRAMADDR: ADDR Mask            */

#define SPIM_DMACNT_DMACNT_Pos           (0)                                               /*!< SPIM_T::DMACNT: DMACNT Position        */
#define SPIM_DMACNT_DMACNT_Msk           (0xfffffful << SPIM_DMACNT_DMACNT_Pos)            /*!< SPIM_T::DMACNT: DMACNT Mask            */

#define SPIM_FADDR_ADDR_Pos              (0)                                               /*!< SPIM_T::FADDR: ADDR Position           */
#define SPIM_FADDR_ADDR_Msk              (0xfffffffful << SPIM_FADDR_ADDR_Pos)             /*!< SPIM_T::FADDR: ADDR Mask               */

#define SPIM_KEY1_KEY1_Pos               (0)                                               /*!< SPIM_T::KEY1: KEY1 Position            */
#define SPIM_KEY1_KEY1_Msk               (0xfffffffful << SPIM_KEY1_KEY1_Pos)              /*!< SPIM_T::KEY1: KEY1 Mask                */

#define SPIM_KEY2_KEY2_Pos               (0)                                               /*!< SPIM_T::KEY2: KEY2 Position            */
#define SPIM_KEY2_KEY2_Msk               (0xfffffffful << SPIM_KEY2_KEY2_Pos)              /*!< SPIM_T::KEY2: KEY2 Mask                */

#define SPIM_DMMCTL_CRMDAT_Pos           (8)                                               /*!< SPIM_T::DMMCTL: CRMDAT Position        */
#define SPIM_DMMCTL_CRMDAT_Msk           (0xfful << SPIM_DMMCTL_CRMDAT_Pos)                /*!< SPIM_T::DMMCTL: CRMDAT Mask            */

#define SPIM_DMMCTL_DESELTIM_Pos         (16)                                              /*!< SPIM_T::DMMCTL: DESELTIM Position      */
#define SPIM_DMMCTL_DESELTIM_Msk         (0x1ful << SPIM_DMMCTL_DESELTIM_Pos)              /*!< SPIM_T::DMMCTL: DESELTIM Mask          */

#define SPIM_DMMCTL_BWEN_Pos             (24)                                              /*!< SPIM_T::DMMCTL: BWEN Position          */
#define SPIM_DMMCTL_BWEN_Msk             (0x1ul << SPIM_DMMCTL_BWEN_Pos)                   /*!< SPIM_T::DMMCTL: BWEN Mask              */

#define SPIM_DMMCTL_CREN_Pos             (25)                                              /*!< SPIM_T::DMMCTL: CREN Position          */
#define SPIM_DMMCTL_CREN_Msk             (0x1ul << SPIM_DMMCTL_CREN_Pos)                   /*!< SPIM_T::DMMCTL: CREN Mask              */

#define SPIM_DMMCTL_UACTSCLK_Pos         (26)                                              /*!< SPIM_T::DMMCTL: UACTSCLK Position      */
#define SPIM_DMMCTL_UACTSCLK_Msk         (0x1ul << SPIM_DMMCTL_UACTSCLK_Pos)               /*!< SPIM_T::DMMCTL: UACTSCLK Mask          */

#define SPIM_DMMCTL_ACTSCLKT_Pos         (28)                                              /*!< SPIM_T::DMMCTL: ACTSCLKT Position      */
#define SPIM_DMMCTL_ACTSCLKT_Msk         (0xful << SPIM_DMMCTL_ACTSCLKT_Pos)               /*!< SPIM_T::DMMCTL: ACTSCLKT Mask          */

#define SPIM_CTL2_USETEN_Pos             (16)                                              /*!< SPIM_T::CTL2: USETEN Position          */
#define SPIM_CTL2_USETEN_Msk             (0x1ul << SPIM_CTL2_USETEN_Pos)                   /*!< SPIM_T::CTL2: USETEN Mask              */

#define SPIM_CTL2_DTRMPOFF_Pos           (20)                                              /*!< SPIM_T::CTL2: DTRMPOFF Position        */
#define SPIM_CTL2_DTRMPOFF_Msk           (0x1ul << SPIM_CTL2_DTRMPOFF_Pos)                 /*!< SPIM_T::CTL2: DTRMPOFF Mask            */

#define SPIM_CTL2_DCNUM_Pos              (24)                                              /*!< SPIM_T::CTL2: DCNUM Position           */
#define SPIM_CTL2_DCNUM_Msk              (0x1ful << SPIM_CTL2_DCNUM_Pos)                   /*!< SPIM_T::CTL2: DCNUM Mask               */

/**@}*/ /* SPIM_CONST */
/**@}*/ /* end of SPIM register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __SPIM_REG_H__ */
