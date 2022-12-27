/**************************************************************************//**
 * @file     ui2c_reg.h
 * @version  V1.00
 * @brief    UI2C register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __UI2C_REG_H__
#define __UI2C_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup UI2C I2C Mode of USCI Controller(UI2C)
    Memory Mapped Structure for UI2C Controller
@{ */

typedef struct
{


    /**
@var UI2C_T::CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL
</font><br><p> <font size="2">
Offset: 0x00  USCI Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2:0]</td><td>FUNMODE</td><td><div style="word-wrap: break-word;"><b>Function Mode
</b><br>
This bit field selects the protocol for this USCI controller
<br>
Selecting a protocol that is not available or a reserved combination disables the USCI
<br>
When switching between two protocols, the USCI has to be disabled before selecting a new protocol
<br>
Simultaneously, the USCI will be reset when user write 000 to FUNMODE.
<br>
000 = The USCI is disabled. All protocol related state machines are set to idle state.
<br>
001 = The SPI protocol is selected.
<br>
010 = The UART protocol is selected.
<br>
100 = The I2C protocol is selected.
<br>
Note: Other bit combinations are reserved.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UI2C_T::BRGEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BRGEN
</font><br><p> <font size="2">
Offset: 0x08  USCI Baud Rate Generator Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>RCLKSEL</td><td><div style="word-wrap: break-word;"><b>Reference Clock Source Selection
</b><br>
This bit selects the source signal of reference clock (fREF_CLK).
<br>
0 = Peripheral device clock fPCLK.
<br>
1 = Reserved.
<br>
</div></td></tr><tr><td>
[1]</td><td>PTCLKSEL</td><td><div style="word-wrap: break-word;"><b>Protocol Clock Source Selection
</b><br>
This bit selects the source signal of protocol clock (fPROT_CLK).
<br>
0 = Reference clock fREF_CLK.
<br>
1 = fREF_CLK2 (its frequency is half of fREF_CLK).
<br>
</div></td></tr><tr><td>
[3:2]</td><td>SPCLKSEL</td><td><div style="word-wrap: break-word;"><b>Sample Clock Source Selection
</b><br>
This bit field used for the clock source selection of a sample clock (fSAMP_CLK) for the protocol processor.
<br>
00 = fSAMP_CLK = fDIV_CLK.
<br>
01 = fSAMP_CLK = fPROT_CLK.
<br>
10 = fSAMP_CLK = fSCLK.
<br>
11 = fSAMP_CLK = fREF_CLK.
<br>
</div></td></tr><tr><td>
[4]</td><td>TMCNTEN</td><td><div style="word-wrap: break-word;"><b>Time Measurement Counter Enable Bit
</b><br>
This bit enables the 10-bit timing measurement counter.
<br>
0 = Time measurement counter is Disabled.
<br>
1 = Time measurement counter is Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>TMCNTSRC</td><td><div style="word-wrap: break-word;"><b>Time Measurement Counter Clock Source Selection
</b><br>
0 = Time measurement counter with fPROT_CLK.
<br>
1 = Time measurement counter with fDIV_CLK.
<br>
</div></td></tr><tr><td>
[9:8]</td><td>PDSCNT</td><td><div style="word-wrap: break-word;"><b>Pre-divider for Sample Counter
</b><br>
This bit field defines the divide ratio of the clock division from sample clock fSAMP_CLK
<br>
The divided frequency fPDS_CNT = fSAMP_CLK / (PDSCNT+1).
<br>
</div></td></tr><tr><td>
[14:10]</td><td>DSCNT</td><td><div style="word-wrap: break-word;"><b>Denominator for Sample Counter
</b><br>
This bit field defines the divide ratio of the sample clock fSAMP_CLK.
<br>
The divided frequency fDS_CNT = fPDS_CNT / (DSCNT+1).
<br>
Note: The maximum value of DSCNT is 0xF on UART mode and suggest to set over 4 to confirm the receiver data is sampled in right value
<br>
</div></td></tr><tr><td>
[25:16]</td><td>CLKDIV</td><td><div style="word-wrap: break-word;"><b>Clock Divider
</b><br>
This bit field defines the ratio between the protocol clock frequency fPROT_CLK and the clock divider frequency fDIV_CLK (fDIV_CLK = fPROT_CLK / (CLKDIV+1) ).
<br>
Note: In UART function, it can be updated by hardware in the 4th falling edge of the input data 0x55 when the auto baud rate function (ABREN(USCI_PROTCTL[6])) is enabled
<br>
The revised value is the average bit time between bit 5 and bit 6
<br>
The user can use revised CLKDIV and new BRDETITV (USCI_PROTCTL[24:16]) to calculate the precise baud rate.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UI2C_T::LINECTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">LINECTL
</font><br><p> <font size="2">
Offset: 0x2C  USCI Line Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>LSB</td><td><div style="word-wrap: break-word;"><b>LSB First Transmission Selection
</b><br>
0 = The MSB, which bit of transmit/receive data buffer depends on the setting of DWIDTH, is transmitted/received first.
<br>
1 = The LSB, the bit 0 of data buffer, will be transmitted/received first.
<br>
</div></td></tr><tr><td>
[11:8]</td><td>DWIDTH</td><td><div style="word-wrap: break-word;"><b>Word Length of Transmission
</b><br>
This bit field defines the data word length (amount of bits) for reception and transmission
<br>
The data word is always right-aligned in the data buffer
<br>
USCI support word length from 4 to 16 bits.
<br>
0x0: The data word contains 16 bits located at bit positions [15:0].
<br>
0x1: Reserved.
<br>
0x2: Reserved.
<br>
0x3: Reserved.
<br>
0x4: The data word contains 4 bits located at bit positions [3:0].
<br>
0x5: The data word contains 5 bits located at bit positions [4:0].
<br>
...
<br>
0xF: The data word contains 15 bits located at bit positions [14:0].
<br>
Note: In UART protocol, the length can be configured as 6~13 bits
<br>
And in I2C protocol, the length fixed as 8 bits.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UI2C_T::TXDAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TXDAT
</font><br><p> <font size="2">
Offset: 0x30  USCI Transmit Data Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>TXDAT</td><td><div style="word-wrap: break-word;"><b>Transmit Data
</b><br>
Software can use this bit field to write 16-bit transmit data for transmission.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UI2C_T::RXDAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">RXDAT
</font><br><p> <font size="2">
Offset: 0x34  USCI Receive Data Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>RXDAT</td><td><div style="word-wrap: break-word;"><b>Received Data
</b><br>
This bit field monitors the received data which stored in receive data buffer.
<br>
Note 1: In I2C protocol, RXDAT[12:8] indicate the different transmission conditions which defined in I2C.
<br>
Note 2: In UART protocol, RXDAT[15:13] indicate the same frame status of BREAK, FRMERR and PARITYERR (USCI_PROTSTS[7:5]).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UI2C_T::DEVADDR0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DEVADDR0
</font><br><p> <font size="2">
Offset: 0x44  USCI Device Address Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[9:0]</td><td>DEVADDR</td><td><div style="word-wrap: break-word;"><b>Device Address
</b><br>
In I2C protocol, this bit field contains the programmed slave address
<br>
If the first received address byte are 1111 0AAXB, the AA bits are compared to the bits DEVADDR[9:8] to check for address match, where the X is R/W bit
<br>
Then the second address byte is also compared to DEVADDR[7:0].
<br>
Note 1: The DEVADDR [9:7] must be set 3'b000 when I2C operating in 7-bit address mode.
<br>
Note 2: When software set 10'h000, the address can not be used.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UI2C_T::DEVADDR1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DEVADDR1
</font><br><p> <font size="2">
Offset: 0x48  USCI Device Address Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[9:0]</td><td>DEVADDR</td><td><div style="word-wrap: break-word;"><b>Device Address
</b><br>
In I2C protocol, this bit field contains the programmed slave address
<br>
If the first received address byte are 1111 0AAXB, the AA bits are compared to the bits DEVADDR[9:8] to check for address match, where the X is R/W bit
<br>
Then the second address byte is also compared to DEVADDR[7:0].
<br>
Note 1: The DEVADDR [9:7] must be set 3'000 when I2C operating in 7-bit address mode.
<br>
Note 2: When software set 10'h000, the address can not be used.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UI2C_T::ADDRMSK0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ADDRMSK0
</font><br><p> <font size="2">
Offset: 0x4C  USCI Device Address Mask Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[9:0]</td><td>ADDRMSK</td><td><div style="word-wrap: break-word;"><b>USCI Device Address Mask
</b><br>
0 = Mask Disabled (the received corresponding register bit should be exact the same as address register.).
<br>
1 = Mask Enabled (the received corresponding address bit is don't care.).
<br>
USCI support multiple address recognition with two address mask register
<br>
When the bit in the address mask register is set to one, it means the received corresponding address bit is don't-care
<br>
If the bit is set to zero, that means the received corresponding register bit should be exact the same as address register.
<br>
Note: The wake-up function can not use address mask.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UI2C_T::ADDRMSK1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ADDRMSK1
</font><br><p> <font size="2">
Offset: 0x50  USCI Device Address Mask Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[9:0]</td><td>ADDRMSK</td><td><div style="word-wrap: break-word;"><b>USCI Device Address Mask
</b><br>
0 = Mask Disabled (the received corresponding register bit should be exact the same as address register.).
<br>
1 = Mask Enabled (the received corresponding address bit is don't care.).
<br>
USCI support multiple address recognition with two address mask register
<br>
When the bit in the address mask register is set to one, it means the received corresponding address bit is don't-care
<br>
If the bit is set to zero, that means the received corresponding register bit should be exact the same as address register.
<br>
Note: The wake-up function can not use address mask.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UI2C_T::WKCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">WKCTL
</font><br><p> <font size="2">
Offset: 0x54  USCI Wake-up Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>WKEN</td><td><div style="word-wrap: break-word;"><b>Wake-up Enable Bit
</b><br>
0 = Wake-up function Disabled.
<br>
1 = Wake-up function Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>WKADDREN</td><td><div style="word-wrap: break-word;"><b>Wake-up Address Match Enable Bit
</b><br>
0 = The chip is woken up according data toggle.
<br>
1 = The chip is woken up according address match.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UI2C_T::WKSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">WKSTS
</font><br><p> <font size="2">
Offset: 0x58  USCI Wake-up Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>WKF</td><td><div style="word-wrap: break-word;"><b>Wake-up Flag
</b><br>
When chip is woken up from Power-down mode, this bit is set to 1
<br>
Software can write 1 to clear this bit.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UI2C_T::PROTCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PROTCTL
</font><br><p> <font size="2">
Offset: 0x5C  USCI Protocol Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>GCFUNC</td><td><div style="word-wrap: break-word;"><b>General Call Function
</b><br>
0 = General Call Function Disabled.
<br>
1 = General Call Function Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>AA</td><td><div style="word-wrap: break-word;"><b>Assert Acknowledge Control
</b><br>
When AA=1 prior to address or data received, an acknowledged (low level to SDA) will be returned during the acknowledge clock pulse on the SCL line when 1.) A slave is acknowledging the address sent from master, 2.) The receiver devices are acknowledging the data sent by transmitter
<br>
When AA=0 prior to address or data received, a Not acknowledged (high level to SDA) will be returned during the acknowledge clock pulse on the SCL line.
<br>
</div></td></tr><tr><td>
[2]</td><td>STO</td><td><div style="word-wrap: break-word;"><b>I2C STOP Control
</b><br>
In Master mode, setting STO to transmit a STOP condition to bus then I2C hardware will check the bus condition if a STOP condition is detected this bit will be cleared by hardware automatically
<br>
In a slave mode, setting STO resets I2C hardware to the defined "not addressed" slave mode when bus error (USCI_PROTSTS.ERRIF = 1).
<br>
</div></td></tr><tr><td>
[3]</td><td>STA</td><td><div style="word-wrap: break-word;"><b>I2C START Control
</b><br>
Setting STA to logic 1 to enter Master mode, the I2C hardware sends a START or repeat START condition to bus when the bus is free.
<br>
</div></td></tr><tr><td>
[4]</td><td>ADDR10EN</td><td><div style="word-wrap: break-word;"><b>Address 10-bit Function Enable Bit
</b><br>
0 = Address match 10 bit function is disabled.
<br>
1 = Address match 10 bit function is enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>PTRG</td><td><div style="word-wrap: break-word;"><b>I2C Protocol Trigger (Write Only)
</b><br>
When a new state is present in the USCI_PROTSTS register, if the related interrupt enable bits are set, the I2C interrupt is requested
<br>
It must write one by software to this bit after the related interrupt flags are set to 1 and the I2C protocol function will go ahead until the STOP is active or the PROTEN is disabled.
<br>
0 = I2C's stretch disabled and the I2C protocol function will go ahead.
<br>
1 = I2C's stretch active.
<br>
</div></td></tr><tr><td>
[8]</td><td>SCLOUTEN</td><td><div style="word-wrap: break-word;"><b>SCL Output Enable Bit
</b><br>
This bit enables monitor pulling SCL to low
<br>
This monitor will pull SCL to low until it has had time to respond to an I2C interrupt.
<br>
0 = SCL output will be forced high due to open drain mechanism.
<br>
1 = I2C module may act as a slave peripheral just like in normal operation, the I2C holds the clock line low until it has had time to clear I2C interrupt.
<br>
</div></td></tr><tr><td>
[9]</td><td>MONEN</td><td><div style="word-wrap: break-word;"><b>Monitor Mode Enable Bit
</b><br>
This bit enables monitor mode
<br>
In monitor mode the SDA output will be put in high impedance mode
<br>
This prevents the I2C module from outputting data of any kind (including ACK) onto the I2C data bus.
<br>
0 = The monitor mode is disabled.
<br>
1 = The monitor mode is enabled.
<br>
Note: Depending on the state of the SCLOUTEN bit, the SCL output may be also forced high, preventing the module from having control over the I2C clock line.
<br>
</div></td></tr><tr><td>
[25:16]</td><td>TOCNT</td><td><div style="word-wrap: break-word;"><b>Time-out Clock Cycle
</b><br>
This bit field indicates how many clock cycle selected by TMCNTSRC (USCI_BRGEN [5]) when each interrupt flags are clear
<br>
The time-out is enable when TOCNT bigger than 0.
<br>
Note: The TMCNTSRC (USCI_BRGEN [5]) must be set zero on I2C mode.
<br>
</div></td></tr><tr><td>
[31]</td><td>PROTEN</td><td><div style="word-wrap: break-word;"><b>I2C Protocol Enable Bit
</b><br>
0 = I2C Protocol disable.
<br>
1 = I2C Protocol enable.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UI2C_T::PROTIEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PROTIEN
</font><br><p> <font size="2">
Offset: 0x60  USCI Protocol Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>TOIEN</td><td><div style="word-wrap: break-word;"><b>Time-out Interrupt Enable Control
</b><br>
In I2C protocol, this bit enables the interrupt generation in case of a time-out event.
<br>
0 = The time-out interrupt is disabled.
<br>
1 = The time-out interrupt is enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>STARIEN</td><td><div style="word-wrap: break-word;"><b>Start Condition Received Interrupt Enable Control
</b><br>
This bit enables the generation of a protocol interrupt if a start condition is detected.
<br>
0 = The start condition interrupt is disabled.
<br>
1 = The start condition interrupt is enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>STORIEN</td><td><div style="word-wrap: break-word;"><b>Stop Condition Received Interrupt Enable Control
</b><br>
This bit enables the generation of a protocol interrupt if a stop condition is detected.
<br>
0 = The stop condition interrupt is disabled.
<br>
1 = The stop condition interrupt is enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>NACKIEN</td><td><div style="word-wrap: break-word;"><b>Non - Acknowledge Interrupt Enable Control
</b><br>
This bit enables the generation of a protocol interrupt if a non - acknowledge is detected by a master.
<br>
0 = The non - acknowledge interrupt is disabled.
<br>
1 = The non - acknowledge interrupt is enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>ARBLOIEN</td><td><div style="word-wrap: break-word;"><b>Arbitration Lost Interrupt Enable Control
</b><br>
This bit enables the generation of a protocol interrupt if an arbitration lost event is detected.
<br>
0 = The arbitration lost interrupt is disabled.
<br>
1 = The arbitration lost interrupt is enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>ERRIEN</td><td><div style="word-wrap: break-word;"><b>Error Interrupt Enable Control
</b><br>
This bit enables the generation of a protocol interrupt if an I2C error condition is detected (indicated by ERR (USCI_PROTSTS [16])).
<br>
0 = The error interrupt is disabled.
<br>
1 = The error interrupt is enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>ACKIEN</td><td><div style="word-wrap: break-word;"><b>Acknowledge Interrupt Enable Control
</b><br>
This bit enables the generation of a protocol interrupt if an acknowledge is detected by a master.
<br>
0 = The acknowledge interrupt is disabled.
<br>
1 = The acknowledge interrupt is enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UI2C_T::PROTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PROTSTS
</font><br><p> <font size="2">
Offset: 0x64  USCI Protocol Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[5]</td><td>TOIF</td><td><div style="word-wrap: break-word;"><b>Time-out Interrupt Flag
</b><br>
0 = A time-out interrupt status has not occurred.
<br>
1 = A time-out interrupt status has occurred.
<br>
Note: It is cleared by software writing one into this bit
<br>
</div></td></tr><tr><td>
[6]</td><td>ONBUSY</td><td><div style="word-wrap: break-word;"><b>On Bus Busy
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
[8]</td><td>STARIF</td><td><div style="word-wrap: break-word;"><b>Start Condition Received Interrupt Flag
</b><br>
This bit indicates that a start condition or repeated start condition has been detected on master mode
<br>
However, this bit also indicates that a repeated start condition has been detected on slave mode.
<br>
A protocol interrupt can be generated if USCI_PROTCTL.STARIEN = 1.
<br>
0 = A start condition has not yet been detected.
<br>
1 = A start condition has been detected.
<br>
It is cleared by software writing one into this bit
<br>
</div></td></tr><tr><td>
[9]</td><td>STORIF</td><td><div style="word-wrap: break-word;"><b>Stop Condition Received Interrupt Flag
</b><br>
This bit indicates that a stop condition has been detected on the I2C bus lines
<br>
A protocol interrupt can be generated if USCI_PROTCTL.STORIEN = 1.
<br>
0 = A stop condition has not yet been detected.
<br>
1 = A stop condition has been detected.
<br>
It is cleared by software writing one into this bit
<br>
Note: This bit is set when slave RX mode.
<br>
</div></td></tr><tr><td>
[10]</td><td>NACKIF</td><td><div style="word-wrap: break-word;"><b>Non - Acknowledge Received Interrupt Flag
</b><br>
This bit indicates that a non - acknowledge has been received in master mode
<br>
A protocol interrupt can be generated if USCI_PROTCTL.NACKIEN = 1.
<br>
0 = A non - acknowledge has not been received.
<br>
1 = A non - acknowledge has been received.
<br>
It is cleared by software writing one into this bit
<br>
</div></td></tr><tr><td>
[11]</td><td>ARBLOIF</td><td><div style="word-wrap: break-word;"><b>Arbitration Lost Interrupt Flag
</b><br>
This bit indicates that an arbitration has been lost
<br>
A protocol interrupt can be generated if USCI_PROTCTL.ARBLOIEN = 1.
<br>
0 = An arbitration has not been lost.
<br>
1 = An arbitration has been lost.
<br>
It is cleared by software writing one into this bit
<br>
</div></td></tr><tr><td>
[12]</td><td>ERRIF</td><td><div style="word-wrap: break-word;"><b>Error Interrupt Flag
</b><br>
This bit indicates that a Bus Error occurs when a START or STOP condition is present at an illegal position in the formation frame
<br>
Example of illegal position are during the serial transfer of an address byte, a data byte or an acknowledge bit
<br>
A protocol interrupt can be generated if USCI_PROTCTL.ERRIEN = 1.
<br>
0 = An I2C error has not been detected.
<br>
1 = An I2C error has been detected.
<br>
It is cleared by software writing one into this bit
<br>
Note: This bit is set when slave mode, user must write one into STO register to the defined "not addressed" slave mode.
<br>
</div></td></tr><tr><td>
[13]</td><td>ACKIF</td><td><div style="word-wrap: break-word;"><b>Acknowledge Received Interrupt Flag
</b><br>
This bit indicates that an acknowledge has been received in master mode
<br>
A protocol interrupt can be generated if USCI_PROTCTL.ACKIEN = 1.
<br>
0 = An acknowledge has not been received.
<br>
1 = An acknowledge has been received.
<br>
It is cleared by software writing one into this bit
<br>
</div></td></tr><tr><td>
[14]</td><td>SLASEL</td><td><div style="word-wrap: break-word;"><b>Slave Select Status
</b><br>
This bit indicates that this device has been selected as slave.
<br>
0 = The device is not selected as slave.
<br>
1 = The device is selected as slave.
<br>
Note: This bit has no interrupt signal, and it will be cleared automatically by hardware.
<br>
</div></td></tr><tr><td>
[15]</td><td>SLAREAD</td><td><div style="word-wrap: break-word;"><b>Slave Read Request Status
</b><br>
This bit indicates that a slave read request has been detected.
<br>
0 = A slave R/W bit is 1 has not been detected.
<br>
1 = A slave R/W bit is 1 has been detected.
<br>
Note: This bit has no interrupt signal, and it will be cleared automatically by hardware.
<br>
</div></td></tr><tr><td>
[16]</td><td>WKAKDONE</td><td><div style="word-wrap: break-word;"><b>Wakeup Address Frame Acknowledge Bit Done
</b><br>
0 = The ACK bit cycle of address match frame isn't done.
<br>
1 = The ACK bit cycle of address match frame is done in power-down.
<br>
Note: This bit can't release when WKUPIF is set.
<br>
</div></td></tr><tr><td>
[17]</td><td>WRSTSWK</td><td><div style="word-wrap: break-word;"><b>Read/Write Status Bit in Address Wakeup Frame
</b><br>
0 = Write command be record on the address match wakeup frame.
<br>
1 = Read command be record on the address match wakeup frame.
<br>
</div></td></tr><tr><td>
[18]</td><td>BUSHANG</td><td><div style="word-wrap: break-word;"><b>Bus Hang-up
</b><br>
This bit indicates bus hang-up status
<br>
There is 4-bit counter count when SCL hold high and refer fSAMP_CLK
<br>
The hang-up counter will count to overflow and set this bit when SDA is low
<br>
The counter will be reset by falling edge of SCL signal.
<br>
0 = The bus is normal status for transmission.
<br>
1 = The bus is hang-up status for transmission.
<br>
Note: This bit has no interrupt signal, and it will be cleared automatically by hardware when a START condition is present.
<br>
</div></td></tr><tr><td>
[19]</td><td>ERRARBLO</td><td><div style="word-wrap: break-word;"><b>Error Arbitration Lost
</b><br>
This bit indicates bus arbitration lost due to bigger noise which is can't be filtered by input processor
<br>
The I2C can send start condition when ERRARBLO is set
<br>
Thus this bit doesn't be cared on slave mode.
<br>
0 = The bus is normal status for transmission.
<br>
1 = The bus is error arbitration lost status for transmission.
<br>
Note: This bit has no interrupt signal, and it will be cleared automatically by hardware when a START condition is present.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UI2C_T::ADMAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ADMAT
</font><br><p> <font size="2">
Offset: 0x88  I2C Slave Match Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ADMAT0</td><td><div style="word-wrap: break-word;"><b>USCI Address 0 Match Status Register
</b><br>
When address 0 is matched, hardware will inform which address used
<br>
This bit will set to 1, and software can write 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[1]</td><td>ADMAT1</td><td><div style="word-wrap: break-word;"><b>USCI Address 1 Match Status Register
</b><br>
When address 1 is matched, hardware will inform which address used
<br>
This bit will set to 1, and software can write 1 to clear this bit.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var UI2C_T::TMCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TMCTL
</font><br><p> <font size="2">
Offset: 0x8C  I2C Timing Configure Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[8:0]</td><td>STCTL</td><td><div style="word-wrap: break-word;"><b>Setup Time Configure Control Register
</b><br>
This field is used to generate a delay timing between SDA edge and SCL rising edge in transmission mode.
<br>
The delay setup time is numbers of peripheral clock = STCTL x fPCLK.
<br>
</div></td></tr><tr><td>
[24:16]</td><td>HTCTL</td><td><div style="word-wrap: break-word;"><b>Hold Time Configure Control Register
</b><br>
This field is used to generate the delay timing between SCL falling edge SDA edge in
<br>
transmission mode.
<br>
The delay hold time is numbers of peripheral clock = HTCTL x fPCLK.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CTL;                   /*!< [0x0000] USCI Control Register                                            */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t BRGEN;                 /*!< [0x0008] USCI Baud Rate Generator Register                                */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[8];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t LINECTL;               /*!< [0x002c] USCI Line Control Register                                       */
    __O  uint32_t TXDAT;                 /*!< [0x0030] USCI Transmit Data Register                                      */
    __I  uint32_t RXDAT;                 /*!< [0x0034] USCI Receive Data Register                                       */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE2[3];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t DEVADDR0;              /*!< [0x0044] USCI Device Address Register 0                                   */
    __IO uint32_t DEVADDR1;              /*!< [0x0048] USCI Device Address Register 1                                   */
    __IO uint32_t ADDRMSK0;              /*!< [0x004c] USCI Device Address Mask Register 0                              */
    __IO uint32_t ADDRMSK1;              /*!< [0x0050] USCI Device Address Mask Register 1                              */
    __IO uint32_t WKCTL;                 /*!< [0x0054] USCI Wake-up Control Register                                    */
    __IO uint32_t WKSTS;                 /*!< [0x0058] USCI Wake-up Status Register                                     */
    __IO uint32_t PROTCTL;               /*!< [0x005c] USCI Protocol Control Register                                   */
    __IO uint32_t PROTIEN;               /*!< [0x0060] USCI Protocol Interrupt Enable Register                          */
    __IO uint32_t PROTSTS;               /*!< [0x0064] USCI Protocol Status Register                                    */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE3[8];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t ADMAT;                 /*!< [0x0088] I2C Slave Match Address Register                                 */
    __IO uint32_t TMCTL;                 /*!< [0x008c] I2C Timing Configure Control Register                            */

} UI2C_T;

/**
    @addtogroup UI2C_CONST UI2C Bit Field Definition
    Constant Definitions for UI2C Controller
@{ */

#define UI2C_CTL_FUNMODE_Pos             (0)                                               /*!< UI2C_T::CTL: FUNMODE Position          */
#define UI2C_CTL_FUNMODE_Msk             (0x7ul << UI2C_CTL_FUNMODE_Pos)                   /*!< UI2C_T::CTL: FUNMODE Mask              */

#define UI2C_BRGEN_RCLKSEL_Pos           (0)                                               /*!< UI2C_T::BRGEN: RCLKSEL Position        */
#define UI2C_BRGEN_RCLKSEL_Msk           (0x1ul << UI2C_BRGEN_RCLKSEL_Pos)                 /*!< UI2C_T::BRGEN: RCLKSEL Mask            */

#define UI2C_BRGEN_PTCLKSEL_Pos          (1)                                               /*!< UI2C_T::BRGEN: PTCLKSEL Position       */
#define UI2C_BRGEN_PTCLKSEL_Msk          (0x1ul << UI2C_BRGEN_PTCLKSEL_Pos)                /*!< UI2C_T::BRGEN: PTCLKSEL Mask           */

#define UI2C_BRGEN_SPCLKSEL_Pos          (2)                                               /*!< UI2C_T::BRGEN: SPCLKSEL Position       */
#define UI2C_BRGEN_SPCLKSEL_Msk          (0x3ul << UI2C_BRGEN_SPCLKSEL_Pos)                /*!< UI2C_T::BRGEN: SPCLKSEL Mask           */

#define UI2C_BRGEN_TMCNTEN_Pos           (4)                                               /*!< UI2C_T::BRGEN: TMCNTEN Position        */
#define UI2C_BRGEN_TMCNTEN_Msk           (0x1ul << UI2C_BRGEN_TMCNTEN_Pos)                 /*!< UI2C_T::BRGEN: TMCNTEN Mask            */

#define UI2C_BRGEN_TMCNTSRC_Pos          (5)                                               /*!< UI2C_T::BRGEN: TMCNTSRC Position       */
#define UI2C_BRGEN_TMCNTSRC_Msk          (0x1ul << UI2C_BRGEN_TMCNTSRC_Pos)                /*!< UI2C_T::BRGEN: TMCNTSRC Mask           */

#define UI2C_BRGEN_PDSCNT_Pos            (8)                                               /*!< UI2C_T::BRGEN: PDSCNT Position         */
#define UI2C_BRGEN_PDSCNT_Msk            (0x3ul << UI2C_BRGEN_PDSCNT_Pos)                  /*!< UI2C_T::BRGEN: PDSCNT Mask             */

#define UI2C_BRGEN_DSCNT_Pos             (10)                                              /*!< UI2C_T::BRGEN: DSCNT Position          */
#define UI2C_BRGEN_DSCNT_Msk             (0x1ful << UI2C_BRGEN_DSCNT_Pos)                  /*!< UI2C_T::BRGEN: DSCNT Mask              */

#define UI2C_BRGEN_CLKDIV_Pos            (16)                                              /*!< UI2C_T::BRGEN: CLKDIV Position         */
#define UI2C_BRGEN_CLKDIV_Msk            (0x3fful << UI2C_BRGEN_CLKDIV_Pos)                /*!< UI2C_T::BRGEN: CLKDIV Mask             */

#define UI2C_LINECTL_LSB_Pos             (0)                                               /*!< UI2C_T::LINECTL: LSB Position          */
#define UI2C_LINECTL_LSB_Msk             (0x1ul << UI2C_LINECTL_LSB_Pos)                   /*!< UI2C_T::LINECTL: LSB Mask              */

#define UI2C_LINECTL_DWIDTH_Pos          (8)                                               /*!< UI2C_T::LINECTL: DWIDTH Position       */
#define UI2C_LINECTL_DWIDTH_Msk          (0xful << UI2C_LINECTL_DWIDTH_Pos)                /*!< UI2C_T::LINECTL: DWIDTH Mask           */

#define UI2C_TXDAT_TXDAT_Pos             (0)                                               /*!< UI2C_T::TXDAT: TXDAT Position          */
#define UI2C_TXDAT_TXDAT_Msk             (0xfffful << UI2C_TXDAT_TXDAT_Pos)                /*!< UI2C_T::TXDAT: TXDAT Mask              */

#define UI2C_RXDAT_RXDAT_Pos             (0)                                               /*!< UI2C_T::RXDAT: RXDAT Position          */
#define UI2C_RXDAT_RXDAT_Msk             (0xfffful << UI2C_RXDAT_RXDAT_Pos)                /*!< UI2C_T::RXDAT: RXDAT Mask              */

#define UI2C_DEVADDR0_DEVADDR_Pos        (0)                                               /*!< UI2C_T::DEVADDR0: DEVADDR Position     */
#define UI2C_DEVADDR0_DEVADDR_Msk        (0x3fful << UI2C_DEVADDR0_DEVADDR_Pos)            /*!< UI2C_T::DEVADDR0: DEVADDR Mask         */

#define UI2C_DEVADDR1_DEVADDR_Pos        (0)                                               /*!< UI2C_T::DEVADDR1: DEVADDR Position     */
#define UI2C_DEVADDR1_DEVADDR_Msk        (0x3fful << UI2C_DEVADDR1_DEVADDR_Pos)            /*!< UI2C_T::DEVADDR1: DEVADDR Mask         */

#define UI2C_ADDRMSK0_ADDRMSK_Pos        (0)                                               /*!< UI2C_T::ADDRMSK0: ADDRMSK Position     */
#define UI2C_ADDRMSK0_ADDRMSK_Msk        (0x3fful << UI2C_ADDRMSK0_ADDRMSK_Pos)            /*!< UI2C_T::ADDRMSK0: ADDRMSK Mask         */

#define UI2C_ADDRMSK1_ADDRMSK_Pos        (0)                                               /*!< UI2C_T::ADDRMSK1: ADDRMSK Position     */
#define UI2C_ADDRMSK1_ADDRMSK_Msk        (0x3fful << UI2C_ADDRMSK1_ADDRMSK_Pos)            /*!< UI2C_T::ADDRMSK1: ADDRMSK Mask         */

#define UI2C_WKCTL_WKEN_Pos              (0)                                               /*!< UI2C_T::WKCTL: WKEN Position           */
#define UI2C_WKCTL_WKEN_Msk              (0x1ul << UI2C_WKCTL_WKEN_Pos)                    /*!< UI2C_T::WKCTL: WKEN Mask               */

#define UI2C_WKCTL_WKADDREN_Pos          (1)                                               /*!< UI2C_T::WKCTL: WKADDREN Position       */
#define UI2C_WKCTL_WKADDREN_Msk          (0x1ul << UI2C_WKCTL_WKADDREN_Pos)                /*!< UI2C_T::WKCTL: WKADDREN Mask           */

#define UI2C_WKSTS_WKF_Pos               (0)                                               /*!< UI2C_T::WKSTS: WKF Position            */
#define UI2C_WKSTS_WKF_Msk               (0x1ul << UI2C_WKSTS_WKF_Pos)                     /*!< UI2C_T::WKSTS: WKF Mask                */

#define UI2C_PROTCTL_GCFUNC_Pos          (0)                                               /*!< UI2C_T::PROTCTL: GCFUNC Position       */
#define UI2C_PROTCTL_GCFUNC_Msk          (0x1ul << UI2C_PROTCTL_GCFUNC_Pos)                /*!< UI2C_T::PROTCTL: GCFUNC Mask           */

#define UI2C_PROTCTL_AA_Pos              (1)                                               /*!< UI2C_T::PROTCTL: AA Position           */
#define UI2C_PROTCTL_AA_Msk              (0x1ul << UI2C_PROTCTL_AA_Pos)                    /*!< UI2C_T::PROTCTL: AA Mask               */

#define UI2C_PROTCTL_STO_Pos             (2)                                               /*!< UI2C_T::PROTCTL: STO Position          */
#define UI2C_PROTCTL_STO_Msk             (0x1ul << UI2C_PROTCTL_STO_Pos)                   /*!< UI2C_T::PROTCTL: STO Mask              */

#define UI2C_PROTCTL_STA_Pos             (3)                                               /*!< UI2C_T::PROTCTL: STA Position          */
#define UI2C_PROTCTL_STA_Msk             (0x1ul << UI2C_PROTCTL_STA_Pos)                   /*!< UI2C_T::PROTCTL: STA Mask              */

#define UI2C_PROTCTL_ADDR10EN_Pos        (4)                                               /*!< UI2C_T::PROTCTL: ADDR10EN Position     */
#define UI2C_PROTCTL_ADDR10EN_Msk        (0x1ul << UI2C_PROTCTL_ADDR10EN_Pos)              /*!< UI2C_T::PROTCTL: ADDR10EN Mask         */

#define UI2C_PROTCTL_PTRG_Pos            (5)                                               /*!< UI2C_T::PROTCTL: PTRG Position         */
#define UI2C_PROTCTL_PTRG_Msk            (0x1ul << UI2C_PROTCTL_PTRG_Pos)                  /*!< UI2C_T::PROTCTL: PTRG Mask             */

#define UI2C_PROTCTL_SCLOUTEN_Pos        (8)                                               /*!< UI2C_T::PROTCTL: SCLOUTEN Position     */
#define UI2C_PROTCTL_SCLOUTEN_Msk        (0x1ul << UI2C_PROTCTL_SCLOUTEN_Pos)              /*!< UI2C_T::PROTCTL: SCLOUTEN Mask         */

#define UI2C_PROTCTL_MONEN_Pos           (9)                                               /*!< UI2C_T::PROTCTL: MONEN Position        */
#define UI2C_PROTCTL_MONEN_Msk           (0x1ul << UI2C_PROTCTL_MONEN_Pos)                 /*!< UI2C_T::PROTCTL: MONEN Mask            */

#define UI2C_PROTCTL_TOCNT_Pos           (16)                                              /*!< UI2C_T::PROTCTL: TOCNT Position        */
#define UI2C_PROTCTL_TOCNT_Msk           (0x3fful << UI2C_PROTCTL_TOCNT_Pos)               /*!< UI2C_T::PROTCTL: TOCNT Mask            */

#define UI2C_PROTCTL_PROTEN_Pos          (31)                                              /*!< UI2C_T::PROTCTL: PROTEN Position       */
#define UI2C_PROTCTL_PROTEN_Msk          (0x1ul << UI2C_PROTCTL_PROTEN_Pos)                /*!< UI2C_T::PROTCTL: PROTEN Mask           */

#define UI2C_PROTIEN_TOIEN_Pos           (0)                                               /*!< UI2C_T::PROTIEN: TOIEN Position        */
#define UI2C_PROTIEN_TOIEN_Msk           (0x1ul << UI2C_PROTIEN_TOIEN_Pos)                 /*!< UI2C_T::PROTIEN: TOIEN Mask            */

#define UI2C_PROTIEN_STARIEN_Pos         (1)                                               /*!< UI2C_T::PROTIEN: STARIEN Position      */
#define UI2C_PROTIEN_STARIEN_Msk         (0x1ul << UI2C_PROTIEN_STARIEN_Pos)               /*!< UI2C_T::PROTIEN: STARIEN Mask          */

#define UI2C_PROTIEN_STORIEN_Pos         (2)                                               /*!< UI2C_T::PROTIEN: STORIEN Position      */
#define UI2C_PROTIEN_STORIEN_Msk         (0x1ul << UI2C_PROTIEN_STORIEN_Pos)               /*!< UI2C_T::PROTIEN: STORIEN Mask          */

#define UI2C_PROTIEN_NACKIEN_Pos         (3)                                               /*!< UI2C_T::PROTIEN: NACKIEN Position      */
#define UI2C_PROTIEN_NACKIEN_Msk         (0x1ul << UI2C_PROTIEN_NACKIEN_Pos)               /*!< UI2C_T::PROTIEN: NACKIEN Mask          */

#define UI2C_PROTIEN_ARBLOIEN_Pos        (4)                                               /*!< UI2C_T::PROTIEN: ARBLOIEN Position     */
#define UI2C_PROTIEN_ARBLOIEN_Msk        (0x1ul << UI2C_PROTIEN_ARBLOIEN_Pos)              /*!< UI2C_T::PROTIEN: ARBLOIEN Mask         */

#define UI2C_PROTIEN_ERRIEN_Pos          (5)                                               /*!< UI2C_T::PROTIEN: ERRIEN Position       */
#define UI2C_PROTIEN_ERRIEN_Msk          (0x1ul << UI2C_PROTIEN_ERRIEN_Pos)                /*!< UI2C_T::PROTIEN: ERRIEN Mask           */

#define UI2C_PROTIEN_ACKIEN_Pos          (6)                                               /*!< UI2C_T::PROTIEN: ACKIEN Position       */
#define UI2C_PROTIEN_ACKIEN_Msk          (0x1ul << UI2C_PROTIEN_ACKIEN_Pos)                /*!< UI2C_T::PROTIEN: ACKIEN Mask           */

#define UI2C_PROTSTS_TOIF_Pos            (5)                                               /*!< UI2C_T::PROTSTS: TOIF Position         */
#define UI2C_PROTSTS_TOIF_Msk            (0x1ul << UI2C_PROTSTS_TOIF_Pos)                  /*!< UI2C_T::PROTSTS: TOIF Mask             */

#define UI2C_PROTSTS_ONBUSY_Pos          (6)                                               /*!< UI2C_T::PROTSTS: ONBUSY Position       */
#define UI2C_PROTSTS_ONBUSY_Msk          (0x1ul << UI2C_PROTSTS_ONBUSY_Pos)                /*!< UI2C_T::PROTSTS: ONBUSY Mask           */

#define UI2C_PROTSTS_STARIF_Pos          (8)                                               /*!< UI2C_T::PROTSTS: STARIF Position       */
#define UI2C_PROTSTS_STARIF_Msk          (0x1ul << UI2C_PROTSTS_STARIF_Pos)                /*!< UI2C_T::PROTSTS: STARIF Mask           */

#define UI2C_PROTSTS_STORIF_Pos          (9)                                               /*!< UI2C_T::PROTSTS: STORIF Position       */
#define UI2C_PROTSTS_STORIF_Msk          (0x1ul << UI2C_PROTSTS_STORIF_Pos)                /*!< UI2C_T::PROTSTS: STORIF Mask           */

#define UI2C_PROTSTS_NACKIF_Pos          (10)                                              /*!< UI2C_T::PROTSTS: NACKIF Position       */
#define UI2C_PROTSTS_NACKIF_Msk          (0x1ul << UI2C_PROTSTS_NACKIF_Pos)                /*!< UI2C_T::PROTSTS: NACKIF Mask           */

#define UI2C_PROTSTS_ARBLOIF_Pos         (11)                                              /*!< UI2C_T::PROTSTS: ARBLOIF Position      */
#define UI2C_PROTSTS_ARBLOIF_Msk         (0x1ul << UI2C_PROTSTS_ARBLOIF_Pos)               /*!< UI2C_T::PROTSTS: ARBLOIF Mask          */

#define UI2C_PROTSTS_ERRIF_Pos           (12)                                              /*!< UI2C_T::PROTSTS: ERRIF Position        */
#define UI2C_PROTSTS_ERRIF_Msk           (0x1ul << UI2C_PROTSTS_ERRIF_Pos)                 /*!< UI2C_T::PROTSTS: ERRIF Mask            */

#define UI2C_PROTSTS_ACKIF_Pos           (13)                                              /*!< UI2C_T::PROTSTS: ACKIF Position        */
#define UI2C_PROTSTS_ACKIF_Msk           (0x1ul << UI2C_PROTSTS_ACKIF_Pos)                 /*!< UI2C_T::PROTSTS: ACKIF Mask            */

#define UI2C_PROTSTS_SLASEL_Pos          (14)                                              /*!< UI2C_T::PROTSTS: SLASEL Position       */
#define UI2C_PROTSTS_SLASEL_Msk          (0x1ul << UI2C_PROTSTS_SLASEL_Pos)                /*!< UI2C_T::PROTSTS: SLASEL Mask           */

#define UI2C_PROTSTS_SLAREAD_Pos         (15)                                              /*!< UI2C_T::PROTSTS: SLAREAD Position      */
#define UI2C_PROTSTS_SLAREAD_Msk         (0x1ul << UI2C_PROTSTS_SLAREAD_Pos)               /*!< UI2C_T::PROTSTS: SLAREAD Mask          */

#define UI2C_PROTSTS_WKAKDONE_Pos        (16)                                              /*!< UI2C_T::PROTSTS: WKAKDONE Position     */
#define UI2C_PROTSTS_WKAKDONE_Msk        (0x1ul << UI2C_PROTSTS_WKAKDONE_Pos)              /*!< UI2C_T::PROTSTS: WKAKDONE Mask         */

#define UI2C_PROTSTS_WRSTSWK_Pos         (17)                                              /*!< UI2C_T::PROTSTS: WRSTSWK Position      */
#define UI2C_PROTSTS_WRSTSWK_Msk         (0x1ul << UI2C_PROTSTS_WRSTSWK_Pos)               /*!< UI2C_T::PROTSTS: WRSTSWK Mask          */

#define UI2C_PROTSTS_BUSHANG_Pos         (18)                                              /*!< UI2C_T::PROTSTS: BUSHANG Position      */
#define UI2C_PROTSTS_BUSHANG_Msk         (0x1ul << UI2C_PROTSTS_BUSHANG_Pos)               /*!< UI2C_T::PROTSTS: BUSHANG Mask          */

#define UI2C_PROTSTS_ERRARBLO_Pos        (19)                                              /*!< UI2C_T::PROTSTS: ERRARBLO Position     */
#define UI2C_PROTSTS_ERRARBLO_Msk        (0x1ul << UI2C_PROTSTS_ERRARBLO_Pos)              /*!< UI2C_T::PROTSTS: ERRARBLO Mask         */

#define UI2C_ADMAT_ADMAT0_Pos            (0)                                               /*!< UI2C_T::ADMAT: ADMAT0 Position         */
#define UI2C_ADMAT_ADMAT0_Msk            (0x1ul << UI2C_ADMAT_ADMAT0_Pos)                  /*!< UI2C_T::ADMAT: ADMAT0 Mask             */

#define UI2C_ADMAT_ADMAT1_Pos            (1)                                               /*!< UI2C_T::ADMAT: ADMAT1 Position         */
#define UI2C_ADMAT_ADMAT1_Msk            (0x1ul << UI2C_ADMAT_ADMAT1_Pos)                  /*!< UI2C_T::ADMAT: ADMAT1 Mask             */

#define UI2C_TMCTL_STCTL_Pos             (0)                                               /*!< UI2C_T::TMCTL: STCTL Position          */
#define UI2C_TMCTL_STCTL_Msk             (0x1fful << UI2C_TMCTL_STCTL_Pos)                 /*!< UI2C_T::TMCTL: STCTL Mask              */

#define UI2C_TMCTL_HTCTL_Pos             (16)                                              /*!< UI2C_T::TMCTL: HTCTL Position          */
#define UI2C_TMCTL_HTCTL_Msk             (0x1fful << UI2C_TMCTL_HTCTL_Pos)                 /*!< UI2C_T::TMCTL: HTCTL Mask              */

/**@}*/ /* UI2C_CONST */
/**@}*/ /* end of UI2C register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __UI2C_REG_H__ */
