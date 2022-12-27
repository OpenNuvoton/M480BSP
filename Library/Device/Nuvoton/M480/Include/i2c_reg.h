/**************************************************************************//**
 * @file     i2c_reg.h
 * @version  V1.00
 * @brief    I2C register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __I2C_REG_H__
#define __I2C_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup I2C Inter-IC Bus Controller(I2C)
    Memory Mapped Structure for I2C Controller
@{ */

typedef struct
{


    /**
@var I2C_T::CTL0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL0
</font><br><p> <font size="2">
Offset: 0x00  I2C Control Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2]</td><td>AA</td><td><div style="word-wrap: break-word;"><b>Assert Acknowledge Control
</b><br>
When AA =1 prior to address or data is received, an acknowledged (low level to SDA) will be returned during the acknowledge clock pulse on the SCL line when 1.) A slave is acknowledging the address sent from master, 2.) The receiver devices are acknowledging the data sent by transmitter
<br>
When AA=0 prior to address or data received, a Not acknowledged (high level to SDA) will be returned during the acknowledge clock pulse on the SCL line
<br>
</div></td></tr><tr><td>
[3]</td><td>SI</td><td><div style="word-wrap: break-word;"><b>I2C Interrupt Flag
</b><br>
When a new I2C state is present in the I2C_STATUS register, the SI flag is set by hardware
<br>
If bit INTEN (I2C_CTL [7]) is set, the I2C interrupt is requested
<br>
SI must be cleared by software
<br>
Clear SI by writing 1 to this bit.
<br>
For ACKMEN is set in slave read mode, the SI flag is set in 8th clock period for user to confirm the acknowledge bit and 9th clock period for user to read the data in the data buffer.
<br>
</div></td></tr><tr><td>
[4]</td><td>STO</td><td><div style="word-wrap: break-word;"><b>I2C STOP Control
</b><br>
In Master mode, setting STO to transmit a STOP condition to bus then I2C controller will check the bus condition if a STOP condition is detected
<br>
This bit will be cleared by hardware automatically.
<br>
</div></td></tr><tr><td>
[5]</td><td>STA</td><td><div style="word-wrap: break-word;"><b>I2C START Control
</b><br>
Setting STA to logic 1 to enter Master mode, the I2C hardware sends a START or repeat START condition to bus when the bus is free.
<br>
</div></td></tr><tr><td>
[6]</td><td>I2CEN</td><td><div style="word-wrap: break-word;"><b>I2C Controller Enable Bit
</b><br>
Set to enable I2C serial function controller
<br>
When I2CEN=1 the I2C serial function enable
<br>
The multi-function pin function must set to SDA, and SCL of I2C function first.
<br>
0 = I2C controller Disabled.
<br>
1 = I2C controller Enabled.
<br>
</div></td></tr><tr><td>
[7]</td><td>INTEN</td><td><div style="word-wrap: break-word;"><b>Enable Interrupt
</b><br>
0 = I2C interrupt Disabled.
<br>
1 = I2C interrupt Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::ADDR0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ADDR0
</font><br><p> <font size="2">
Offset: 0x04  I2C Slave Address Register0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>GC</td><td><div style="word-wrap: break-word;"><b>General Call Function
</b><br>
0 = General Call Function Disabled.
<br>
1 = General Call Function Enabled.
<br>
</div></td></tr><tr><td>
[10:1]</td><td>ADDR</td><td><div style="word-wrap: break-word;"><b>I2C Address
</b><br>
The content of this register is irrelevant when I2C is in Master mode
<br>
In the slave mode, the seven most significant bits must be loaded with the chip's own address
<br>
The I2C hardware will react if either of the address is matched.
<br>
Note: When software set 10'h000, the address can not be used.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::DAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DAT
</font><br><p> <font size="2">
Offset: 0x08  I2C Data Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>DAT</td><td><div style="word-wrap: break-word;"><b>I2C Data
</b><br>
Bit [7:0] is located with the 8-bit transferred/received data of I2C serial port.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::STATUS0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STATUS0
</font><br><p> <font size="2">
Offset: 0x0C  I2C Status Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>STATUS</td><td><div style="word-wrap: break-word;"><b>I2C Status
</b><br>
The three least significant bits are always 0
<br>
The five most significant bits contain the status code
<br>
There are 28 possible status codes
<br>
When the content of I2C_STATUS is F8H, no serial interrupt is requested
<br>
Others I2C_STATUS values correspond to defined I2C states
<br>
When each of these states is entered, a status interrupt is requested (SI = 1)
<br>
A valid status code is present in I2C_STATUS one cycle after SI is set by hardware and is still present one cycle after SI has been reset by software
<br>
In addition, states 00H stands for a Bus Error
<br>
A Bus Error occurs when a START or STOP condition is present at an illegal position in the formation frame
<br>
Example of illegal position are during the serial transfer of an address byte, a data byte or an acknowledge bit.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::CLKDIV

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKDIV
</font><br><p> <font size="2">
Offset: 0x10  I2C Clock Divided Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[9:0]</td><td>DIVIDER</td><td><div style="word-wrap: break-word;"><b>I2C Clock Divided
</b><br>
Indicates the I2C clock rate: Data Baud Rate of I2C = (system clock) / (4x (I2C_CLKDIV+1)).
<br>
Note: The minimum value of I2C_CLKDIV is 4.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::TOCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TOCTL
</font><br><p> <font size="2">
Offset: 0x14  I2C Time-out Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>TOIF</td><td><div style="word-wrap: break-word;"><b>Time-out Flag
</b><br>
This bit is set by hardware when I2C time-out happened and it can interrupt CPU if I2C interrupt enable bit (INTEN) is set to 1.
<br>
Note: Software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[1]</td><td>TOCDIV4</td><td><div style="word-wrap: break-word;"><b>Time-out Counter Input Clock Divided by 4
</b><br>
When Enabled, The time-out period is extend 4 times.
<br>
0 = Time-out period is extend 4 times Disabled.
<br>
1 = Time-out period is extend 4 times Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>TOCEN</td><td><div style="word-wrap: break-word;"><b>Time-out Counter Enable Bit
</b><br>
When Enabled, the 14-bit time-out counter will start counting when SI is clear
<br>
Setting flag SI to '1' will reset counter and re-start up counting after SI is cleared.
<br>
0 = Time-out counter Disabled.
<br>
1 = Time-out counter Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::ADDR1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ADDR1
</font><br><p> <font size="2">
Offset: 0x18  I2C Slave Address Register1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>GC</td><td><div style="word-wrap: break-word;"><b>General Call Function
</b><br>
0 = General Call Function Disabled.
<br>
1 = General Call Function Enabled.
<br>
</div></td></tr><tr><td>
[10:1]</td><td>ADDR</td><td><div style="word-wrap: break-word;"><b>I2C Address
</b><br>
The content of this register is irrelevant when I2C is in Master mode
<br>
In the slave mode, the seven most significant bits must be loaded with the chip's own address
<br>
The I2C hardware will react if either of the address is matched.
<br>
Note: When software set 10'h000, the address can not be used.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::ADDR2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ADDR2
</font><br><p> <font size="2">
Offset: 0x1C  I2C Slave Address Register2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>GC</td><td><div style="word-wrap: break-word;"><b>General Call Function
</b><br>
0 = General Call Function Disabled.
<br>
1 = General Call Function Enabled.
<br>
</div></td></tr><tr><td>
[10:1]</td><td>ADDR</td><td><div style="word-wrap: break-word;"><b>I2C Address
</b><br>
The content of this register is irrelevant when I2C is in Master mode
<br>
In the slave mode, the seven most significant bits must be loaded with the chip's own address
<br>
The I2C hardware will react if either of the address is matched.
<br>
Note: When software set 10'h000, the address can not be used.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::ADDR3

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ADDR3
</font><br><p> <font size="2">
Offset: 0x20  I2C Slave Address Register3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>GC</td><td><div style="word-wrap: break-word;"><b>General Call Function
</b><br>
0 = General Call Function Disabled.
<br>
1 = General Call Function Enabled.
<br>
</div></td></tr><tr><td>
[10:1]</td><td>ADDR</td><td><div style="word-wrap: break-word;"><b>I2C Address
</b><br>
The content of this register is irrelevant when I2C is in Master mode
<br>
In the slave mode, the seven most significant bits must be loaded with the chip's own address
<br>
The I2C hardware will react if either of the address is matched.
<br>
Note: When software set 10'h000, the address can not be used.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::ADDRMSK0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ADDRMSK0
</font><br><p> <font size="2">
Offset: 0x24  I2C Slave Address Mask Register0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[10:1]</td><td>ADDRMSK</td><td><div style="word-wrap: break-word;"><b>I2C Address Mask
</b><br>
0 = Mask Disabled (the received corresponding register bit should be exact the same as address register.).
<br>
1 = Mask Enabled (the received corresponding address bit is don't care.).
<br>
I2C bus controllers support multiple address recognition with four address mask register
<br>
When the bit in the address mask register is set to one, it means the received corresponding address bit is don't-care
<br>
If the bit is set to zero, that means the received corresponding register bit should be exact the same as address register.
<br>
Note: The wake-up function can not use address mask.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::ADDRMSK1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ADDRMSK1
</font><br><p> <font size="2">
Offset: 0x28  I2C Slave Address Mask Register1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[10:1]</td><td>ADDRMSK</td><td><div style="word-wrap: break-word;"><b>I2C Address Mask
</b><br>
0 = Mask Disabled (the received corresponding register bit should be exact the same as address register.).
<br>
1 = Mask Enabled (the received corresponding address bit is don't care.).
<br>
I2C bus controllers support multiple address recognition with four address mask register
<br>
When the bit in the address mask register is set to one, it means the received corresponding address bit is don't-care
<br>
If the bit is set to zero, that means the received corresponding register bit should be exact the same as address register.
<br>
Note: The wake-up function can not use address mask.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::ADDRMSK2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ADDRMSK2
</font><br><p> <font size="2">
Offset: 0x2C  I2C Slave Address Mask Register2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[10:1]</td><td>ADDRMSK</td><td><div style="word-wrap: break-word;"><b>I2C Address Mask
</b><br>
0 = Mask Disabled (the received corresponding register bit should be exact the same as address register.).
<br>
1 = Mask Enabled (the received corresponding address bit is don't care.).
<br>
I2C bus controllers support multiple address recognition with four address mask register
<br>
When the bit in the address mask register is set to one, it means the received corresponding address bit is don't-care
<br>
If the bit is set to zero, that means the received corresponding register bit should be exact the same as address register.
<br>
Note: The wake-up function can not use address mask.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::ADDRMSK3

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ADDRMSK3
</font><br><p> <font size="2">
Offset: 0x30  I2C Slave Address Mask Register3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[10:1]</td><td>ADDRMSK</td><td><div style="word-wrap: break-word;"><b>I2C Address Mask
</b><br>
0 = Mask Disabled (the received corresponding register bit should be exact the same as address register.).
<br>
1 = Mask Enabled (the received corresponding address bit is don't care.).
<br>
I2C bus controllers support multiple address recognition with four address mask register
<br>
When the bit in the address mask register is set to one, it means the received corresponding address bit is don't-care
<br>
If the bit is set to zero, that means the received corresponding register bit should be exact the same as address register.
<br>
Note: The wake-up function can not use address mask.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::WKCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">WKCTL
</font><br><p> <font size="2">
Offset: 0x3C  I2C Wake-up Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>WKEN</td><td><div style="word-wrap: break-word;"><b>I2C Wake-up Enable Bit
</b><br>
0 = I2C wake-up function Disabled.
<br>
1 = I2C wake-up function Enabled.
<br>
</div></td></tr><tr><td>
[7]</td><td>NHDBUSEN</td><td><div style="word-wrap: break-word;"><b>I2C No Hold BUS Enable Bit
</b><br>
0 = I2C hold bus after wake-up.
<br>
1 = I2C don't hold bus after wake-up.
<br>
Note: I2C controller could response when WKIF event is not clear, it may cause error data transmitted or received
<br>
If data transmitted or received when WKIF event is not clear, user must reset I2C controller and execute the original operation again.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::WKSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">WKSTS
</font><br><p> <font size="2">
Offset: 0x40  I2C Wake-up Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>WKIF</td><td><div style="word-wrap: break-word;"><b>I2C Wake-up Flag
</b><br>
When chip is woken up from Power-down mode by I2C, this bit is set to 1
<br>
Software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[1]</td><td>WKAKDONE</td><td><div style="word-wrap: break-word;"><b>Wakeup Address Frame Acknowledge Bit Done
</b><br>
0 = The ACK bit cycle of address match frame isn't done.
<br>
1 = The ACK bit cycle of address match frame is done in power-down.
<br>
Note: This bit can't release WKIF. Software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[2]</td><td>WRSTSWK</td><td><div style="word-wrap: break-word;"><b>Read/Write Status Bit in Address Wakeup Frame
</b><br>
0 = Write command be record on the address match wakeup frame.
<br>
1 = Read command be record on the address match wakeup frame.
<br>
Note: This bit will be cleared when software can write 1 to WKAKDONE bit.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::CTL1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL1
</font><br><p> <font size="2">
Offset: 0x44  I2C Control Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>TXPDMAEN</td><td><div style="word-wrap: break-word;"><b>PDMA Transmit Channel Available
</b><br>
0 = Transmit PDMA function disable.
<br>
1 = Transmit PDMA function enable.
<br>
</div></td></tr><tr><td>
[1]</td><td>RXPDMAEN</td><td><div style="word-wrap: break-word;"><b>PDMA Receive Channel Available
</b><br>
0 = Receive PDMA function disable.
<br>
1 = Receive PDMA function enable.
<br>
</div></td></tr><tr><td>
[2]</td><td>PDMARST</td><td><div style="word-wrap: break-word;"><b>PDMA Reset
</b><br>
0 = No effect.
<br>
1 = Reset the I2C request to PDMA.
<br>
</div></td></tr><tr><td>
[8]</td><td>PDMASTR</td><td><div style="word-wrap: break-word;"><b>PDMA Stretch Bit
</b><br>
0 = I2C send STOP automatically after PDMA transfer done. (only master TX)
<br>
1 = I2C SCL bus is stretched by hardware after PDMA transfer done if the SI is not cleared
<br>
(only master TX)
<br>
</div></td></tr><tr><td>
[9]</td><td>ADDR10EN</td><td><div style="word-wrap: break-word;"><b>Address 10-bit Function Enable
</b><br>
0 = Address match 10-bit function is disabled.
<br>
1 = Address match 10-bit function is enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::STATUS1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STATUS1
</font><br><p> <font size="2">
Offset: 0x48  I2C Status Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ADMAT0</td><td><div style="word-wrap: break-word;"><b>I2C Address 0 Match Status Register
</b><br>
When address 0 is matched, hardware will inform which address used
<br>
This bit will set to 1, and software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[1]</td><td>ADMAT1</td><td><div style="word-wrap: break-word;"><b>I2C Address 1 Match Status Register
</b><br>
When address 1 is matched, hardware will inform which address used
<br>
This bit will set to 1, and software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[2]</td><td>ADMAT2</td><td><div style="word-wrap: break-word;"><b>I2C Address 2 Match Status Register
</b><br>
When address 2 is matched, hardware will inform which address used
<br>
This bit will set to 1, and software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[3]</td><td>ADMAT3</td><td><div style="word-wrap: break-word;"><b>I2C Address 3 Match Status Register
</b><br>
When address 3 is matched, hardware will inform which address used
<br>
This bit will set to 1, and software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[8]</td><td>ONBUSY</td><td><div style="word-wrap: break-word;"><b>On Bus Busy
</b><br>
Indicates that a communication is in progress on the bus
<br>
It is set by hardware when a START condition is detected
<br>
It is cleared by hardware when a STOP condition is detected.
<br>
0 = The bus is IDLE (both SCLK and SDA High).
<br>
1 = The bus is busy.
<br>
Note:This bit is read only.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::TMCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TMCTL
</font><br><p> <font size="2">
Offset: 0x4C  I2C Timing Configure Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[8:0]</td><td>STCTL</td><td><div style="word-wrap: break-word;"><b>Setup Time Configure Control Register
</b><br>
This field is used to generate a delay timing between SDA falling edge and SCL rising edge in transmission mode.
<br>
The delay setup time is numbers of peripheral clock = STCTL x PCLK.
<br>
Note: Setup time setting should not make SCL output less than three PCLKs.
<br>
</div></td></tr><tr><td>
[24:16]</td><td>HTCTL</td><td><div style="word-wrap: break-word;"><b>Hold Time Configure Control Register
</b><br>
This field is used to generate the delay timing between SCL falling edge and SDA rising edge in transmission mode.
<br>
The delay hold time is numbers of peripheral clock = HTCTL x PCLK.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::BUSCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BUSCTL
</font><br><p> <font size="2">
Offset: 0x50  I2C Bus Management Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ACKMEN</td><td><div style="word-wrap: break-word;"><b>Acknowledge Control by Manual
</b><br>
In order to allow ACK control in slave reception including the command and data, slave byte control mode must be enabled by setting the ACKMEN bit.
<br>
0 = Slave byte control Disabled.
<br>
1 = Slave byte control Enabled
<br>
The 9th bit can response the ACK or NACK according the received data by user
<br>
When the byte is received, stretching the SCLK signal low between the 8th and 9th SCLK pulse.
<br>
Note: If the BMDEN=1 and this bit is enabled, the information of I2C_STATUS will be fixed as 0xF0 in slave receive condition.
<br>
</div></td></tr><tr><td>
[1]</td><td>PECEN</td><td><div style="word-wrap: break-word;"><b>Packet Error Checking Calculation Enable Bit
</b><br>
0 = Packet Error Checking Calculation Disabled.
<br>
1 = Packet Error Checking Calculation Enabled.
<br>
Note: When I2C enter power down mode, the bit should be enabled after wake-up if needed PEC calculation.
<br>
</div></td></tr><tr><td>
[2]</td><td>BMDEN</td><td><div style="word-wrap: break-word;"><b>Bus Management Device Default Address Enable Bit
</b><br>
0 = Device default address Disable
<br>
When the address 0'b1100001x coming and the both of BMDEN and ACKMEN are enabled, the device responses NACKed
<br>
1 = Device default address Enabled
<br>
When the address 0'b1100001x coming and the both of BMDEN and ACKMEN are enabled, the device responses ACKed.
<br>
</div></td></tr><tr><td>
[3]</td><td>BMHEN</td><td><div style="word-wrap: break-word;"><b>Bus Management Host Enable Bit
</b><br>
0 = Host function Disabled.
<br>
1 = Host function Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>ALERTEN</td><td><div style="word-wrap: break-word;"><b>Bus Management Alert Enable Bit
</b><br>
Device Mode (BMHEN=0).
<br>
0 = Release the BM_ALERT pin high and Alert Response Header disabled: 0001100x followed by NACK if both of BMDEN and ACKMEN are enabled.
<br>
1 = Drive BM_ALERT pin low and Alert Response Address Header enables: 0001100x followed by ACK if both of BMDEN and ACKMEN are enabled.
<br>
Host Mode (BMHEN=1).
<br>
0 = BM_ALERT pin not supported.
<br>
1 = BM_ALERT pin supported.
<br>
</div></td></tr><tr><td>
[5]</td><td>SCTLOSTS</td><td><div style="word-wrap: break-word;"><b>Suspend/Control Data Output Status
</b><br>
0 = The output of SUSCON pin is low.
<br>
1 = The output of SUSCON pin is high.
<br>
</div></td></tr><tr><td>
[6]</td><td>SCTLOEN</td><td><div style="word-wrap: break-word;"><b>Suspend or Control Pin Output Enable Bit
</b><br>
0 = The SUSCON pin in input.
<br>
1 = The output enable is active on the SUSCON pin.
<br>
</div></td></tr><tr><td>
[7]</td><td>BUSEN</td><td><div style="word-wrap: break-word;"><b>BUS Enable Bit
</b><br>
0 = The system management function is Disabled.
<br>
1 = The system management function is Enable.
<br>
Note: When the bit is enabled, the internal 14-bit counter is used to calculate the time out event of clock low condition.
<br>
</div></td></tr><tr><td>
[8]</td><td>PECTXEN</td><td><div style="word-wrap: break-word;"><b>Packet Error Checking Byte Transmission/Reception
</b><br>
0 = No PEC transfer.
<br>
1 = PEC transmission is requested.
<br>
Note: This bit has no effect in slave mode when ACKMEN=0.
<br>
</div></td></tr><tr><td>
[9]</td><td>TIDLE</td><td><div style="word-wrap: break-word;"><b>Timer Check in Idle State
</b><br>
The BUSTOUT is used to calculate the time-out of clock low in bus active and the idle period in bus Idle
<br>
This bit is used to define which condition is enabled.
<br>
0 = The BUSTOUT is used to calculate the clock low period in bus active.
<br>
1 = The BUSTOUT is used to calculate the IDLE period in bus Idle.
<br>
Note: The BUSY (I2C_BUSSTS[0]) indicate the current bus state.
<br>
</div></td></tr><tr><td>
[10]</td><td>PECCLR</td><td><div style="word-wrap: break-word;"><b>PEC Clear at Repeat Start
</b><br>
The calculation of PEC starts when PECEN is set to 1 and it is clear when the STA or STO bit is detected
<br>
This PECCLR bit is used to enable the condition of REPEAT START can clear the PEC calculation.
<br>
0 = The PEC calculation is cleared by "Repeat Start" function is Disabled.
<br>
1 = The PEC calculation is cleared by "Repeat Start"" function is Enabled.
<br>
</div></td></tr><tr><td>
[11]</td><td>ACKM9SI</td><td><div style="word-wrap: break-word;"><b>Acknowledge Manual Enable Extra SI Interrupt
</b><br>
0 = There is no SI interrupt in the 9th clock cycle when the BUSEN=1 and ACKMEN=1.
<br>
1 = There is SI interrupt in the 9th clock cycle when the BUSEN=1 and ACKMEN=1.
<br>
</div></td></tr><tr><td>
[12]</td><td>BCDIEN</td><td><div style="word-wrap: break-word;"><b>Packet Error Checking Byte Count Done Interrupt Enable Bit
</b><br>
0 = Indicates the byte count done interrupt is Disabled.
<br>
1 = Indicates the byte count done interrupt is Enabled.
<br>
Note: This bit is used in PECEN=1.
<br>
</div></td></tr><tr><td>
[13]</td><td>PECDIEN</td><td><div style="word-wrap: break-word;"><b>Packet Error Checking Byte Transfer Done Interrupt Enable Bit
</b><br>
0 = Indicates the PEC transfer done interrupt is Disabled.
<br>
1 = Indicates the PEC transfer done interrupt is Enabled.
<br>
Note: This bit is used in PECEN=1.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::BUSTCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BUSTCTL
</font><br><p> <font size="2">
Offset: 0x54  I2C Bus Management Timer Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BUSTOEN</td><td><div style="word-wrap: break-word;"><b>Bus Time Out Enable Bit
</b><br>
0 = Indicates the bus clock low time-out detection is Disabled.
<br>
1 = Indicates the bus clock low time-out detection is Enabled (bus clock is low for more than TTime-out (in BIDLE=0) or high more than TTime-out(in BIDLE =1)
<br>
</div></td></tr><tr><td>
[1]</td><td>CLKTOEN</td><td><div style="word-wrap: break-word;"><b>Cumulative Clock Low Time Out Enable Bit
</b><br>
0 = Indicates the cumulative clock low time-out detection is Disabled.
<br>
1 = Indicates the cumulative clock low time-out detection is Enabled.
<br>
For Master, it calculates the period from START to ACK
<br>
For Slave, it calculates the period from START to STOP
<br>
</div></td></tr><tr><td>
[2]</td><td>BUSTOIEN</td><td><div style="word-wrap: break-word;"><b>Time-out Interrupt Enable Bit
</b><br>
BUSY =1.
<br>
0 = Indicates the SCLK low time-out interrupt is Disabled.
<br>
1 = Indicates the SCLK low time-out interrupt is Enabled.
<br>
BUSY =0.
<br>
0 = Indicates the bus IDLE time-out interrupt is Disabled.
<br>
1 = Indicates the bus IDLE time-out interrupt is Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>CLKTOIEN</td><td><div style="word-wrap: break-word;"><b>Extended Clock Time Out Interrupt Enable Bit
</b><br>
0 = Indicates the clock time out interrupt is Disabled.
<br>
1 = Indicates the clock time out interrupt is Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>TORSTEN</td><td><div style="word-wrap: break-word;"><b>Time Out Reset Enable Bit
</b><br>
0 = Indicates the I2C state machine reset is Disable.
<br>
1 = Indicates the I2C state machine reset is Enable. (The clock and data bus will be released to high)
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::BUSSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BUSSTS
</font><br><p> <font size="2">
Offset: 0x58  I2C Bus Management Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BUSY</td><td><div style="word-wrap: break-word;"><b>Bus Busy
</b><br>
Indicates that a communication is in progress on the bus
<br>
It is set by hardware when a START condition is detected
<br>
It is cleared by hardware when a STOP condition is detected
<br>
0 = The bus is IDLE (both SCLK and SDA High).
<br>
1 = The bus is busy.
<br>
</div></td></tr><tr><td>
[1]</td><td>BCDONE</td><td><div style="word-wrap: break-word;"><b>Byte Count Transmission/Receive Done
</b><br>
0 = Indicates the byte count transmission/ receive is not finished when the PECEN is set.
<br>
1 = Indicates the byte count transmission/ receive is finished when the PECEN is set.
<br>
Note: Software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[2]</td><td>PECERR</td><td><div style="word-wrap: break-word;"><b>PEC Error in Reception
</b><br>
0 = Indicates the PEC value equal the received PEC data packet.
<br>
1 = Indicates the PEC value doesn't match the receive PEC data packet.
<br>
Note: Software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[3]</td><td>ALERT</td><td><div style="word-wrap: break-word;"><b>SMBus Alert Status
</b><br>
Device Mode (BMHEN =0).
<br>
0 = Indicates SMBALERT pin state is low.
<br>
1 = Indicates SMBALERT pin state is high.
<br>
Host Mode (BMHEN =1).
<br>
0 = No SMBALERT event.
<br>
1 = Indicates there is SMBALERT event (falling edge) is detected in SMALERT pin when the BMHEN = 1 (SMBus host configuration) and the ALERTEN = 1.
<br>
Note:
<br>
1. The SMBALERT pin is an open-drain pin, the pull-high resistor is must in the system
<br>
2. Software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[4]</td><td>SCTLDIN</td><td><div style="word-wrap: break-word;"><b>Bus Suspend or Control Signal Input Status
</b><br>
0 = The input status of SUSCON pin is 0.
<br>
1 = The input status of SUSCON pin is 1.
<br>
</div></td></tr><tr><td>
[5]</td><td>BUSTO</td><td><div style="word-wrap: break-word;"><b>Bus Time-out Status
</b><br>
0 = Indicates that there is no any time-out or external clock time-out.
<br>
1 = Indicates that a time-out or external clock time-out occurred.
<br>
In bus busy, the bit indicates the total clock low time-out event occurred otherwise, it indicates the bus idle time-out event occurred.
<br>
Note: Software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[6]</td><td>CLKTO</td><td><div style="word-wrap: break-word;"><b>Clock Low Cumulate Time-out Status
</b><br>
0 = Indicates that the cumulative clock low is no any time-out.
<br>
1 = Indicates that the cumulative clock low time-out occurred.
<br>
Note: Software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[7]</td><td>PECDONE</td><td><div style="word-wrap: break-word;"><b>PEC Byte Transmission/Receive Done
</b><br>
0 = Indicates the PEC transmission/ receive is not finished when the PECEN is set.
<br>
1 = Indicates the PEC transmission/ receive is finished when the PECEN is set.
<br>
Note: Software can write 1 to clear this bit.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::PKTSIZE

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PKTSIZE
</font><br><p> <font size="2">
Offset: 0x5C  I2C Packet Error Checking Byte Number Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[8:0]</td><td>PLDSIZE</td><td><div style="word-wrap: break-word;"><b>Transfer Byte Number
</b><br>
The transmission or receive byte number in one transaction when the PECEN is set
<br>
The maximum transaction or receive byte is 256 Bytes.
<br>
Notice: The byte number counting includes address, command code, and data frame.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::PKTCRC

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PKTCRC
</font><br><p> <font size="2">
Offset: 0x60  I2C Packet Error Checking Byte Value Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>PECCRC</td><td><div style="word-wrap: break-word;"><b>Packet Error Checking Byte Value
</b><br>
This byte indicates the packet error checking content after transmission or receive byte count by using the C(x) = X8 + X2 + X + 1
<br>
It is read only.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::BUSTOUT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BUSTOUT
</font><br><p> <font size="2">
Offset: 0x64  I2C Bus Management Timer Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>BUSTO</td><td><div style="word-wrap: break-word;"><b>Bus Management Time-out Value
</b><br>
Indicate the bus time-out value in bus is IDLE or SCLK low.
<br>
Note: If the user wants to revise the value of BUSTOUT, the TORSTEN (I2C_BUSTCTL[4]) bit shall be set to 1 and clear to 0 first in the BUSEN(I2C_BUSCTL[7]) is set.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var I2C_T::CLKTOUT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKTOUT
</font><br><p> <font size="2">
Offset: 0x68  I2C Bus Management Clock Low Timer Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>CLKTO</td><td><div style="word-wrap: break-word;"><b>Bus Clock Low Timer
</b><br>
The field is used to configure the cumulative clock extension time-out.
<br>
Note: If the user wants to revise the value of CLKLTOUT, the TORSTEN bit shall be set to 1 and clear to 0 first in the BUSEN is set.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CTL0;                  /*!< [0x0000] I2C Control Register 0                                           */
    __IO uint32_t ADDR0;                 /*!< [0x0004] I2C Slave Address Register0                                      */
    __IO uint32_t DAT;                   /*!< [0x0008] I2C Data Register                                                */
    __I  uint32_t STATUS0;               /*!< [0x000c] I2C Status Register 0                                            */
    __IO uint32_t CLKDIV;                /*!< [0x0010] I2C Clock Divided Register                                       */
    __IO uint32_t TOCTL;                 /*!< [0x0014] I2C Time-out Control Register                                    */
    __IO uint32_t ADDR1;                 /*!< [0x0018] I2C Slave Address Register1                                      */
    __IO uint32_t ADDR2;                 /*!< [0x001c] I2C Slave Address Register2                                      */
    __IO uint32_t ADDR3;                 /*!< [0x0020] I2C Slave Address Register3                                      */
    __IO uint32_t ADDRMSK0;              /*!< [0x0024] I2C Slave Address Mask Register0                                 */
    __IO uint32_t ADDRMSK1;              /*!< [0x0028] I2C Slave Address Mask Register1                                 */
    __IO uint32_t ADDRMSK2;              /*!< [0x002c] I2C Slave Address Mask Register2                                 */
    __IO uint32_t ADDRMSK3;              /*!< [0x0030] I2C Slave Address Mask Register3                                 */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[2];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t WKCTL;                 /*!< [0x003c] I2C Wake-up Control Register                                     */
    __IO uint32_t WKSTS;                 /*!< [0x0040] I2C Wake-up Status Register                                      */
    __IO uint32_t CTL1;                  /*!< [0x0044] I2C Control Register 1                                           */
    __IO uint32_t STATUS1;               /*!< [0x0048] I2C Status Register 1                                            */
    __IO uint32_t TMCTL;                 /*!< [0x004c] I2C Timing Configure Control Register                            */
    __IO uint32_t BUSCTL;                /*!< [0x0050] I2C Bus Management Control Register                              */
    __IO uint32_t BUSTCTL;               /*!< [0x0054] I2C Bus Management Timer Control Register                        */
    __IO uint32_t BUSSTS;                /*!< [0x0058] I2C Bus Management Status Register                               */
    __IO uint32_t PKTSIZE;               /*!< [0x005c] I2C Packet Error Checking Byte Number Register                   */
    __I  uint32_t PKTCRC;                /*!< [0x0060] I2C Packet Error Checking Byte Value Register                    */
    __IO uint32_t BUSTOUT;               /*!< [0x0064] I2C Bus Management Timer Register                                */
    __IO uint32_t CLKTOUT;               /*!< [0x0068] I2C Bus Management Clock Low Timer Register                      */

} I2C_T;

/**
    @addtogroup I2C_CONST I2C Bit Field Definition
    Constant Definitions for I2C Controller
@{ */

#define I2C_CTL0_AA_Pos                  (2)                                               /*!< I2C_T::CTL: AA Position                */
#define I2C_CTL0_AA_Msk                  (0x1ul << I2C_CTL0_AA_Pos)                        /*!< I2C_T::CTL: AA Mask                    */

#define I2C_CTL0_SI_Pos                  (3)                                               /*!< I2C_T::CTL: SI Position                */
#define I2C_CTL0_SI_Msk                  (0x1ul << I2C_CTL0_SI_Pos)                        /*!< I2C_T::CTL: SI Mask                    */

#define I2C_CTL0_STO_Pos                 (4)                                               /*!< I2C_T::CTL: STO Position               */
#define I2C_CTL0_STO_Msk                 (0x1ul << I2C_CTL0_STO_Pos)                       /*!< I2C_T::CTL: STO Mask                   */

#define I2C_CTL0_STA_Pos                 (5)                                               /*!< I2C_T::CTL: STA Position               */
#define I2C_CTL0_STA_Msk                 (0x1ul << I2C_CTL0_STA_Pos)                       /*!< I2C_T::CTL: STA Mask                   */

#define I2C_CTL0_I2CEN_Pos               (6)                                               /*!< I2C_T::CTL: I2CEN Position             */
#define I2C_CTL0_I2CEN_Msk               (0x1ul << I2C_CTL0_I2CEN_Pos)                     /*!< I2C_T::CTL: I2CEN Mask                 */

#define I2C_CTL0_INTEN_Pos               (7)                                               /*!< I2C_T::CTL: INTEN Position             */
#define I2C_CTL0_INTEN_Msk               (0x1ul << I2C_CTL0_INTEN_Pos)                     /*!< I2C_T::CTL: INTEN Mask                 */

#define I2C_ADDR0_GC_Pos                 (0)                                               /*!< I2C_T::ADDR0: GC Position              */
#define I2C_ADDR0_GC_Msk                 (0x1ul << I2C_ADDR0_GC_Pos)                       /*!< I2C_T::ADDR0: GC Mask                  */

#define I2C_ADDR0_ADDR_Pos               (1)                                               /*!< I2C_T::ADDR0: ADDR Position            */
#define I2C_ADDR0_ADDR_Msk               (0x3fful << I2C_ADDR0_ADDR_Pos)                   /*!< I2C_T::ADDR0: ADDR Mask                */

#define I2C_DAT_DAT_Pos                  (0)                                               /*!< I2C_T::DAT: DAT Position               */
#define I2C_DAT_DAT_Msk                  (0xfful << I2C_DAT_DAT_Pos)                       /*!< I2C_T::DAT: DAT Mask                   */

#define I2C_STATUS0_STATUS_Pos           (0)                                               /*!< I2C_T::STATUS: STATUS Position         */
#define I2C_STATUS0_STATUS_Msk           (0xfful << I2C_STATUS_STATUS0_Pos)                /*!< I2C_T::STATUS: STATUS Mask             */

#define I2C_CLKDIV_DIVIDER_Pos           (0)                                               /*!< I2C_T::CLKDIV: DIVIDER Position        */
#define I2C_CLKDIV_DIVIDER_Msk           (0x3fful << I2C_CLKDIV_DIVIDER_Pos)               /*!< I2C_T::CLKDIV: DIVIDER Mask            */

#define I2C_TOCTL_TOIF_Pos               (0)                                               /*!< I2C_T::TOCTL: TOIF Position            */
#define I2C_TOCTL_TOIF_Msk               (0x1ul << I2C_TOCTL_TOIF_Pos)                     /*!< I2C_T::TOCTL: TOIF Mask                */

#define I2C_TOCTL_TOCDIV4_Pos            (1)                                               /*!< I2C_T::TOCTL: TOCDIV4 Position         */
#define I2C_TOCTL_TOCDIV4_Msk            (0x1ul << I2C_TOCTL_TOCDIV4_Pos)                  /*!< I2C_T::TOCTL: TOCDIV4 Mask             */

#define I2C_TOCTL_TOCEN_Pos              (2)                                               /*!< I2C_T::TOCTL: TOCEN Position           */
#define I2C_TOCTL_TOCEN_Msk              (0x1ul << I2C_TOCTL_TOCEN_Pos)                    /*!< I2C_T::TOCTL: TOCEN Mask               */

#define I2C_ADDR1_GC_Pos                 (0)                                               /*!< I2C_T::ADDR1: GC Position              */
#define I2C_ADDR1_GC_Msk                 (0x1ul << I2C_ADDR1_GC_Pos)                       /*!< I2C_T::ADDR1: GC Mask                  */

#define I2C_ADDR1_ADDR_Pos               (1)                                               /*!< I2C_T::ADDR1: ADDR Position            */
#define I2C_ADDR1_ADDR_Msk               (0x3fful << I2C_ADDR1_ADDR_Pos)                   /*!< I2C_T::ADDR1: ADDR Mask                */

#define I2C_ADDR2_GC_Pos                 (0)                                               /*!< I2C_T::ADDR2: GC Position              */
#define I2C_ADDR2_GC_Msk                 (0x1ul << I2C_ADDR2_GC_Pos)                       /*!< I2C_T::ADDR2: GC Mask                  */

#define I2C_ADDR2_ADDR_Pos               (1)                                               /*!< I2C_T::ADDR2: ADDR Position            */
#define I2C_ADDR2_ADDR_Msk               (0x3fful << I2C_ADDR2_ADDR_Pos)                   /*!< I2C_T::ADDR2: ADDR Mask                */

#define I2C_ADDR3_GC_Pos                 (0)                                               /*!< I2C_T::ADDR3: GC Position              */
#define I2C_ADDR3_GC_Msk                 (0x1ul << I2C_ADDR3_GC_Pos)                       /*!< I2C_T::ADDR3: GC Mask                  */

#define I2C_ADDR3_ADDR_Pos               (1)                                               /*!< I2C_T::ADDR3: ADDR Position            */
#define I2C_ADDR3_ADDR_Msk               (0x3fful << I2C_ADDR3_ADDR_Pos)                   /*!< I2C_T::ADDR3: ADDR Mask                */

#define I2C_ADDRMSK0_ADDRMSK_Pos         (1)                                               /*!< I2C_T::ADDRMSK0: ADDRMSK Position      */
#define I2C_ADDRMSK0_ADDRMSK_Msk         (0x3fful << I2C_ADDRMSK0_ADDRMSK_Pos)             /*!< I2C_T::ADDRMSK0: ADDRMSK Mask          */

#define I2C_ADDRMSK1_ADDRMSK_Pos         (1)                                               /*!< I2C_T::ADDRMSK1: ADDRMSK Position      */
#define I2C_ADDRMSK1_ADDRMSK_Msk         (0x3fful << I2C_ADDRMSK1_ADDRMSK_Pos)             /*!< I2C_T::ADDRMSK1: ADDRMSK Mask          */

#define I2C_ADDRMSK2_ADDRMSK_Pos         (1)                                               /*!< I2C_T::ADDRMSK2: ADDRMSK Position      */
#define I2C_ADDRMSK2_ADDRMSK_Msk         (0x3fful << I2C_ADDRMSK2_ADDRMSK_Pos)             /*!< I2C_T::ADDRMSK2: ADDRMSK Mask          */

#define I2C_ADDRMSK3_ADDRMSK_Pos         (1)                                               /*!< I2C_T::ADDRMSK3: ADDRMSK Position      */
#define I2C_ADDRMSK3_ADDRMSK_Msk         (0x3fful << I2C_ADDRMSK3_ADDRMSK_Pos)             /*!< I2C_T::ADDRMSK3: ADDRMSK Mask          */

#define I2C_WKCTL_WKEN_Pos               (0)                                               /*!< I2C_T::WKCTL: WKEN Position            */
#define I2C_WKCTL_WKEN_Msk               (0x1ul << I2C_WKCTL_WKEN_Pos)                     /*!< I2C_T::WKCTL: WKEN Mask                */

#define I2C_WKCTL_NHDBUSEN_Pos           (7)                                               /*!< I2C_T::WKCTL: NHDBUSEN Position        */
#define I2C_WKCTL_NHDBUSEN_Msk           (0x1ul << I2C_WKCTL_NHDBUSEN_Pos)                 /*!< I2C_T::WKCTL: NHDBUSEN Mask            */

#define I2C_WKSTS_WKIF_Pos               (0)                                               /*!< I2C_T::WKSTS: WKIF Position            */
#define I2C_WKSTS_WKIF_Msk               (0x1ul << I2C_WKSTS_WKIF_Pos)                     /*!< I2C_T::WKSTS: WKIF Mask                */

#define I2C_WKSTS_WKAKDONE_Pos           (1)                                               /*!< I2C_T::WKSTS: WKAKDONE Position        */
#define I2C_WKSTS_WKAKDONE_Msk           (0x1ul << I2C_WKSTS_WKAKDONE_Pos)                 /*!< I2C_T::WKSTS: WKAKDONE Mask            */

#define I2C_WKSTS_WRSTSWK_Pos            (2)                                               /*!< I2C_T::WKSTS: WRSTSWK Position         */
#define I2C_WKSTS_WRSTSWK_Msk            (0x1ul << I2C_WKSTS_WRSTSWK_Pos)                  /*!< I2C_T::WKSTS: WRSTSWK Mask             */

#define I2C_CTL1_TXPDMAEN_Pos            (0)                                               /*!< I2C_T::CTL1: TXPDMAEN Position         */
#define I2C_CTL1_TXPDMAEN_Msk            (0x1ul << I2C_CTL1_TXPDMAEN_Pos)                  /*!< I2C_T::CTL1: TXPDMAEN Mask             */

#define I2C_CTL1_RXPDMAEN_Pos            (1)                                               /*!< I2C_T::CTL1: RXPDMAEN Position         */
#define I2C_CTL1_RXPDMAEN_Msk            (0x1ul << I2C_CTL1_RXPDMAEN_Pos)                  /*!< I2C_T::CTL1: RXPDMAEN Mask             */

#define I2C_CTL1_PDMARST_Pos             (2)                                               /*!< I2C_T::CTL1: PDMARST Position          */
#define I2C_CTL1_PDMARST_Msk             (0x1ul << I2C_CTL1_PDMARST_Pos)                   /*!< I2C_T::CTL1: PDMARST Mask              */

#define I2C_CTL1_PDMASTR_Pos             (8)                                               /*!< I2C_T::CTL1: PDMASTR Position          */
#define I2C_CTL1_PDMASTR_Msk             (0x1ul << I2C_CTL1_PDMASTR_Pos)                   /*!< I2C_T::CTL1: PDMASTR Mask              */

#define I2C_CTL1_ADDR10EN_Pos            (9)                                               /*!< I2C_T::CTL1: ADDR10EN Position         */
#define I2C_CTL1_ADDR10EN_Msk            (0x1ul << I2C_CTL1_ADDR10EN_Pos)                  /*!< I2C_T::CTL1: ADDR10EN Mask             */

#define I2C_STATUS1_ADMAT0_Pos           (0)                                               /*!< I2C_T::STATUS1: ADMAT0 Position        */
#define I2C_STATUS1_ADMAT0_Msk           (0x1ul << I2C_STATUS1_ADMAT0_Pos)                 /*!< I2C_T::STATUS1: ADMAT0 Mask            */

#define I2C_STATUS1_ADMAT1_Pos           (1)                                               /*!< I2C_T::STATUS1: ADMAT1 Position        */
#define I2C_STATUS1_ADMAT1_Msk           (0x1ul << I2C_STATUS1_ADMAT1_Pos)                 /*!< I2C_T::STATUS1: ADMAT1 Mask            */

#define I2C_STATUS1_ADMAT2_Pos           (2)                                               /*!< I2C_T::STATUS1: ADMAT2 Position        */
#define I2C_STATUS1_ADMAT2_Msk           (0x1ul << I2C_STATUS1_ADMAT2_Pos)                 /*!< I2C_T::STATUS1: ADMAT2 Mask            */

#define I2C_STATUS1_ADMAT3_Pos           (3)                                               /*!< I2C_T::STATUS1: ADMAT3 Position        */
#define I2C_STATUS1_ADMAT3_Msk           (0x1ul << I2C_STATUS1_ADMAT3_Pos)                 /*!< I2C_T::STATUS1: ADMAT3 Mask            */

#define I2C_STATUS1_ONBUSY_Pos           (8)                                               /*!< I2C_T::STATUS1: ONBUSY Position        */
#define I2C_STATUS1_ONBUSY_Msk           (0x1ul << I2C_STATUS1_ONBUSY_Pos)                 /*!< I2C_T::STATUS1: ONBUSY Mask            */

#define I2C_TMCTL_STCTL_Pos              (0)                                               /*!< I2C_T::TMCTL: STCTL Position           */
#define I2C_TMCTL_STCTL_Msk              (0x1fful << I2C_TMCTL_STCTL_Pos)                  /*!< I2C_T::TMCTL: STCTL Mask               */

#define I2C_TMCTL_HTCTL_Pos              (16)                                              /*!< I2C_T::TMCTL: HTCTL Position           */
#define I2C_TMCTL_HTCTL_Msk              (0x1fful << I2C_TMCTL_HTCTL_Pos)                  /*!< I2C_T::TMCTL: HTCTL Mask               */

#define I2C_BUSCTL_ACKMEN_Pos            (0)                                               /*!< I2C_T::BUSCTL: ACKMEN Position         */
#define I2C_BUSCTL_ACKMEN_Msk            (0x1ul << I2C_BUSCTL_ACKMEN_Pos)                  /*!< I2C_T::BUSCTL: ACKMEN Mask             */

#define I2C_BUSCTL_PECEN_Pos             (1)                                               /*!< I2C_T::BUSCTL: PECEN Position          */
#define I2C_BUSCTL_PECEN_Msk             (0x1ul << I2C_BUSCTL_PECEN_Pos)                   /*!< I2C_T::BUSCTL: PECEN Mask              */

#define I2C_BUSCTL_BMDEN_Pos             (2)                                               /*!< I2C_T::BUSCTL: BMDEN Position          */
#define I2C_BUSCTL_BMDEN_Msk             (0x1ul << I2C_BUSCTL_BMDEN_Pos)                   /*!< I2C_T::BUSCTL: BMDEN Mask              */

#define I2C_BUSCTL_BMHEN_Pos             (3)                                               /*!< I2C_T::BUSCTL: BMHEN Position          */
#define I2C_BUSCTL_BMHEN_Msk             (0x1ul << I2C_BUSCTL_BMHEN_Pos)                   /*!< I2C_T::BUSCTL: BMHEN Mask              */

#define I2C_BUSCTL_ALERTEN_Pos           (4)                                               /*!< I2C_T::BUSCTL: ALERTEN Position        */
#define I2C_BUSCTL_ALERTEN_Msk           (0x1ul << I2C_BUSCTL_ALERTEN_Pos)                 /*!< I2C_T::BUSCTL: ALERTEN Mask            */

#define I2C_BUSCTL_SCTLOSTS_Pos          (5)                                               /*!< I2C_T::BUSCTL: SCTLOSTS Position       */
#define I2C_BUSCTL_SCTLOSTS_Msk          (0x1ul << I2C_BUSCTL_SCTLOSTS_Pos)                /*!< I2C_T::BUSCTL: SCTLOSTS Mask           */

#define I2C_BUSCTL_SCTLOEN_Pos           (6)                                               /*!< I2C_T::BUSCTL: SCTLOEN Position        */
#define I2C_BUSCTL_SCTLOEN_Msk           (0x1ul << I2C_BUSCTL_SCTLOEN_Pos)                 /*!< I2C_T::BUSCTL: SCTLOEN Mask            */

#define I2C_BUSCTL_BUSEN_Pos             (7)                                               /*!< I2C_T::BUSCTL: BUSEN Position          */
#define I2C_BUSCTL_BUSEN_Msk             (0x1ul << I2C_BUSCTL_BUSEN_Pos)                   /*!< I2C_T::BUSCTL: BUSEN Mask              */

#define I2C_BUSCTL_PECTXEN_Pos           (8)                                               /*!< I2C_T::BUSCTL: PECTXEN Position        */
#define I2C_BUSCTL_PECTXEN_Msk           (0x1ul << I2C_BUSCTL_PECTXEN_Pos)                 /*!< I2C_T::BUSCTL: PECTXEN Mask            */

#define I2C_BUSCTL_TIDLE_Pos             (9)                                               /*!< I2C_T::BUSCTL: TIDLE Position          */
#define I2C_BUSCTL_TIDLE_Msk             (0x1ul << I2C_BUSCTL_TIDLE_Pos)                   /*!< I2C_T::BUSCTL: TIDLE Mask              */

#define I2C_BUSCTL_PECCLR_Pos            (10)                                              /*!< I2C_T::BUSCTL: PECCLR Position         */
#define I2C_BUSCTL_PECCLR_Msk            (0x1ul << I2C_BUSCTL_PECCLR_Pos)                  /*!< I2C_T::BUSCTL: PECCLR Mask             */

#define I2C_BUSCTL_ACKM9SI_Pos           (11)                                              /*!< I2C_T::BUSCTL: ACKM9SI Position        */
#define I2C_BUSCTL_ACKM9SI_Msk           (0x1ul << I2C_BUSCTL_ACKM9SI_Pos)                 /*!< I2C_T::BUSCTL: ACKM9SI Mask            */

#define I2C_BUSCTL_BCDIEN_Pos            (12)                                              /*!< I2C_T::BUSCTL: BCDIEN Position         */
#define I2C_BUSCTL_BCDIEN_Msk            (0x1ul << I2C_BUSCTL_BCDIEN_Pos)                  /*!< I2C_T::BUSCTL: BCDIEN Mask             */

#define I2C_BUSCTL_PECDIEN_Pos           (13)                                              /*!< I2C_T::BUSCTL: PECDIEN Position        */
#define I2C_BUSCTL_PECDIEN_Msk           (0x1ul << I2C_BUSCTL_PECDIEN_Pos)                 /*!< I2C_T::BUSCTL: PECDIEN Mask            */

#define I2C_BUSTCTL_BUSTOEN_Pos          (0)                                               /*!< I2C_T::BUSTCTL: BUSTOEN Position       */
#define I2C_BUSTCTL_BUSTOEN_Msk          (0x1ul << I2C_BUSTCTL_BUSTOEN_Pos)                /*!< I2C_T::BUSTCTL: BUSTOEN Mask           */

#define I2C_BUSTCTL_CLKTOEN_Pos          (1)                                               /*!< I2C_T::BUSTCTL: CLKTOEN Position       */
#define I2C_BUSTCTL_CLKTOEN_Msk          (0x1ul << I2C_BUSTCTL_CLKTOEN_Pos)                /*!< I2C_T::BUSTCTL: CLKTOEN Mask           */

#define I2C_BUSTCTL_BUSTOIEN_Pos         (2)                                               /*!< I2C_T::BUSTCTL: BUSTOIEN Position      */
#define I2C_BUSTCTL_BUSTOIEN_Msk         (0x1ul << I2C_BUSTCTL_BUSTOIEN_Pos)               /*!< I2C_T::BUSTCTL: BUSTOIEN Mask          */

#define I2C_BUSTCTL_CLKTOIEN_Pos         (3)                                               /*!< I2C_T::BUSTCTL: CLKTOIEN Position      */
#define I2C_BUSTCTL_CLKTOIEN_Msk         (0x1ul << I2C_BUSTCTL_CLKTOIEN_Pos)               /*!< I2C_T::BUSTCTL: CLKTOIEN Mask          */

#define I2C_BUSTCTL_TORSTEN_Pos          (4)                                               /*!< I2C_T::BUSTCTL: TORSTEN Position       */
#define I2C_BUSTCTL_TORSTEN_Msk          (0x1ul << I2C_BUSTCTL_TORSTEN_Pos)                /*!< I2C_T::BUSTCTL: TORSTEN Mask           */

#define I2C_BUSSTS_BUSY_Pos              (0)                                               /*!< I2C_T::BUSSTS: BUSY Position           */
#define I2C_BUSSTS_BUSY_Msk              (0x1ul << I2C_BUSSTS_BUSY_Pos)                    /*!< I2C_T::BUSSTS: BUSY Mask               */

#define I2C_BUSSTS_BCDONE_Pos            (1)                                               /*!< I2C_T::BUSSTS: BCDONE Position         */
#define I2C_BUSSTS_BCDONE_Msk            (0x1ul << I2C_BUSSTS_BCDONE_Pos)                  /*!< I2C_T::BUSSTS: BCDONE Mask             */

#define I2C_BUSSTS_PECERR_Pos            (2)                                               /*!< I2C_T::BUSSTS: PECERR Position         */
#define I2C_BUSSTS_PECERR_Msk            (0x1ul << I2C_BUSSTS_PECERR_Pos)                  /*!< I2C_T::BUSSTS: PECERR Mask             */

#define I2C_BUSSTS_ALERT_Pos             (3)                                               /*!< I2C_T::BUSSTS: ALERT Position          */
#define I2C_BUSSTS_ALERT_Msk             (0x1ul << I2C_BUSSTS_ALERT_Pos)                   /*!< I2C_T::BUSSTS: ALERT Mask              */

#define I2C_BUSSTS_SCTLDIN_Pos           (4)                                               /*!< I2C_T::BUSSTS: SCTLDIN Position        */
#define I2C_BUSSTS_SCTLDIN_Msk           (0x1ul << I2C_BUSSTS_SCTLDIN_Pos)                 /*!< I2C_T::BUSSTS: SCTLDIN Mask            */

#define I2C_BUSSTS_BUSTO_Pos             (5)                                               /*!< I2C_T::BUSSTS: BUSTO Position          */
#define I2C_BUSSTS_BUSTO_Msk             (0x1ul << I2C_BUSSTS_BUSTO_Pos)                   /*!< I2C_T::BUSSTS: BUSTO Mask              */

#define I2C_BUSSTS_CLKTO_Pos             (6)                                               /*!< I2C_T::BUSSTS: CLKTO Position          */
#define I2C_BUSSTS_CLKTO_Msk             (0x1ul << I2C_BUSSTS_CLKTO_Pos)                   /*!< I2C_T::BUSSTS: CLKTO Mask              */

#define I2C_BUSSTS_PECDONE_Pos           (7)                                               /*!< I2C_T::BUSSTS: PECDONE Position        */
#define I2C_BUSSTS_PECDONE_Msk           (0x1ul << I2C_BUSSTS_PECDONE_Pos)                 /*!< I2C_T::BUSSTS: PECDONE Mask            */

#define I2C_PKTSIZE_PLDSIZE_Pos          (0)                                               /*!< I2C_T::PKTSIZE: PLDSIZE Position       */
#define I2C_PKTSIZE_PLDSIZE_Msk          (0x1fful << I2C_PKTSIZE_PLDSIZE_Pos)              /*!< I2C_T::PKTSIZE: PLDSIZE Mask           */

#define I2C_PKTCRC_PECCRC_Pos            (0)                                               /*!< I2C_T::PKTCRC: PECCRC Position         */
#define I2C_PKTCRC_PECCRC_Msk            (0xfful << I2C_PKTCRC_PECCRC_Pos)                 /*!< I2C_T::PKTCRC: PECCRC Mask             */

#define I2C_BUSTOUT_BUSTO_Pos            (0)                                               /*!< I2C_T::BUSTOUT: BUSTO Position         */
#define I2C_BUSTOUT_BUSTO_Msk            (0xfful << I2C_BUSTOUT_BUSTO_Pos)                 /*!< I2C_T::BUSTOUT: BUSTO Mask             */

#define I2C_CLKTOUT_CLKTO_Pos            (0)                                               /*!< I2C_T::CLKTOUT: CLKTO Position         */
#define I2C_CLKTOUT_CLKTO_Msk            (0xfful << I2C_CLKTOUT_CLKTO_Pos)                 /*!< I2C_T::CLKTOUT: CLKTO Mask             */

/**@}*/ /* I2C_CONST */
/**@}*/ /* end of I2C register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __I2C_REG_H__ */
