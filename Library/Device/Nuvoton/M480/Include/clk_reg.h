/**************************************************************************//**
 * @file     clk_reg.h
 * @version  V1.00
 * @brief    CLK register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __CLK_REG_H__
#define __CLK_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup CLK System Clock Controller(CLK)
    Memory Mapped Structure for CLK Controller
@{ */

typedef struct
{


    /**
@var CLK_T::PWRCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWRCTL
</font><br><p> <font size="2">
Offset: 0x00  System Power-down Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>HXTEN</td><td><div style="word-wrap: break-word;"><b>HXT Enable Bit (Write Protect)
</b><br>
The bit default value is set by flash controller user configuration register CONFIG0 [26]
<br>
When the default clock source is from HXT, this bit is set to 1 automatically.
<br>
0 = 4~24 MHz external high speed crystal (HXT) Disabled.
<br>
1 = 4~24 MHz external high speed crystal (HXT) Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[1]</td><td>LXTEN</td><td><div style="word-wrap: break-word;"><b>LXT Enable Bit (Write Protect)
</b><br>
0 = 32.768 kHz external low speed crystal (LXT) Disabled.
<br>
1 = 32.768 kHz external low speed crystal (LXT) Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[2]</td><td>HIRCEN</td><td><div style="word-wrap: break-word;"><b>HIRC Enable Bit (Write Protect)
</b><br>
0 = 12 MHz internal high speed RC oscillator (HIRC) Disabled.
<br>
1 = 12 MHz internal high speed RC oscillator (HIRC) Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[3]</td><td>LIRCEN</td><td><div style="word-wrap: break-word;"><b>LIRC Enable Bit (Write Protect)
</b><br>
0 = 10 kHz internal low speed RC oscillator (LIRC) Disabled.
<br>
1 = 10 kHz internal low speed RC oscillator (LIRC) Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[4]</td><td>PDWKDLY</td><td><div style="word-wrap: break-word;"><b>Enable the Wake-up Delay Counter (Write Protect)
</b><br>
When the chip wakes up from Power-down mode, the clock control will delay certain clock cycles to wait system clock stable.
<br>
The delayed clock cycle is 4096 clock cycles when chip works at 4~24 MHz external high speed crystal oscillator (HXT), and 256 clock cycles when chip works at 12 MHz internal high speed RC oscillator (HIRC).
<br>
0 = Clock cycles delay Disabled.
<br>
1 = Clock cycles delay Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[5]</td><td>PDWKIEN</td><td><div style="word-wrap: break-word;"><b>Power-down Mode Wake-up Interrupt Enable Bit (Write Protect)
</b><br>
0 = Power-down mode wake-up interrupt Disabled.
<br>
1 = Power-down mode wake-up interrupt Enabled.
<br>
Note1: The interrupt will occur when both PDWKIF and PDWKIEN are high.
<br>
Note2: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[6]</td><td>PDWKIF</td><td><div style="word-wrap: break-word;"><b>Power-down Mode Wake-up Interrupt Status
</b><br>
Set by "Power-down wake-up event", it indicates that resume from Power-down mode.
<br>
The flag is set if any wake-up source is occurred. Refer Power Modes and Wake-up Sources chapter.
<br>
Note1: Write 1 to clear the bit to 0.
<br>
Note2: This bit works only if PDWKIEN (CLK_PWRCTL[5]) set to 1.
<br>
</div></td></tr><tr><td>
[7]</td><td>PDEN</td><td><div style="word-wrap: break-word;"><b>System Power-down Enable (Write Protect)
</b><br>
When this bit is set to 1, Power-down mode is enabled and chip keeps active till the CPU sleep mode is also active and then the chip enters Power-down mode.
<br>
When chip wakes up from Power-down mode, this bit is auto cleared
<br>
Users need to set this bit again for next Power-down.
<br>
In Power-down mode, HXT and the HIRC will be disabled in this mode, but LXT and LIRC are not controlled by Power-down mode.
<br>
In Power-down mode, the PLL and system clock are disabled, and ignored the clock source selection
<br>
The clocks of peripheral are not controlled by Power-down mode, if the peripheral clock source is from LXT or LIRC.
<br>
0 = Chip will not enter Power-down mode after CPU sleep command WFI.
<br>
1 = Chip enters Power-down mode after CPU sleep command WFI.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[11:10]</td><td>HXTGAIN</td><td><div style="word-wrap: break-word;"><b>HXT Gain Control Bit (Write Protect)
</b><br>
This is a protected register. Please refer to open lock sequence to program it.
<br>
Gain control is used to enlarge the gain of crystal to make sure crystal work normally
<br>
If gain control is enabled, crystal will consume more power than gain control off.
<br>
00 = HXT frequency is lower than from 8 MHz.
<br>
01 = HXT frequency is from 8 MHz to 12 MHz.
<br>
10 = HXT frequency is from 12 MHz to 16 MHz.
<br>
11 = HXT frequency is higher than 16 MHz.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[12]</td><td>HXTSELTYP</td><td><div style="word-wrap: break-word;"><b>HXT Crystal Type Select Bit (Write Protect)
</b><br>
This is a protected register. Please refer to open lock sequence to program it.
<br>
0 = Select INV type.
<br>
1 = Select GM type.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[13]</td><td>HXTTBEN</td><td><div style="word-wrap: break-word;"><b>HXT Crystal TURBO Mode (Write Protect)
</b><br>
This is a protected register. Please refer to open lock sequence to program it.
<br>
0 = HXT Crystal TURBO mode disabled.
<br>
1 = HXT Crystal TURBO mode enabled.
<br>
</div></td></tr><tr><td>
[17:16]</td><td>HIRCSTBS</td><td><div style="word-wrap: break-word;"><b>HIRC Stable Count Select (Write Protect)
</b><br>
00 = HIRC stable count is 64 clocks.
<br>
01 = HIRC stable count is 24 clocks.
<br>
others = Reserved.
<br>
</div></td></tr><tr><td>
[18]</td><td>HIRCEN</td><td><div style="word-wrap: break-word;"><b>HIRC48M Enable Bit (Write Protect)
</b><br>
0 = 48 MHz internal high speed RC oscillator (HIRC) Disabled.
<br>
1 = 48 MHz internal high speed RC oscillator (HIRC) Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::AHBCLK

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AHBCLK
</font><br><p> <font size="2">
Offset: 0x04  AHB Devices Clock Enable Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1]</td><td>PDMACKEN</td><td><div style="word-wrap: break-word;"><b>PDMA Controller Clock Enable Bit
</b><br>
0 = PDMA peripheral clock Disabled.
<br>
1 = PDMA peripheral clock Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>ISPCKEN</td><td><div style="word-wrap: break-word;"><b>Flash ISP Controller Clock Enable Bit
</b><br>
0 = Flash ISP peripheral clock Disabled.
<br>
1 = Flash ISP peripheral clock Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>EBICKEN</td><td><div style="word-wrap: break-word;"><b>EBI Controller Clock Enable Bit
</b><br>
0 = EBI peripheral clock Disabled.
<br>
1 = EBI peripheral clock Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>EMACCKEN</td><td><div style="word-wrap: break-word;"><b>Ethernet Controller Clock Enable Bit
</b><br>
0 = Ethernet Controller engine clock Disabled.
<br>
1 = Ethernet Controller engine clock Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>SDH0CKEN</td><td><div style="word-wrap: break-word;"><b>SD0 Controller Clock Enable Bit
</b><br>
0 = SD0 engine clock Disabled.
<br>
1 = SD0 engine clock Enabled.
<br>
</div></td></tr><tr><td>
[7]</td><td>CRCCKEN</td><td><div style="word-wrap: break-word;"><b>CRC Generator Controller Clock Enable Bit
</b><br>
0 = CRC peripheral clock Disabled.
<br>
1 = CRC peripheral clock Enabled.
<br>
</div></td></tr><tr><td>
[10]</td><td>HSUSBDCKEN</td><td><div style="word-wrap: break-word;"><b>HSUSB Device Clock Enable Bit
</b><br>
0 = HSUSB device controller's clock Disabled.
<br>
1 = HSUSB device controller's clock Enabled.
<br>
</div></td></tr><tr><td>
[12]</td><td>CRPTCKEN</td><td><div style="word-wrap: break-word;"><b>Cryptographic Accelerator Clock Enable Bit
</b><br>
0 = Cryptographic Accelerator clock Disabled.
<br>
1 = Cryptographic Accelerator clock Enabled.
<br>
</div></td></tr><tr><td>
[14]</td><td>SPIMCKEN</td><td><div style="word-wrap: break-word;"><b>SPIM Controller Clock Enable Bit
</b><br>
0 = SPIM controller clock Disabled.
<br>
1 = SPIM controller clock Enabled.
<br>
</div></td></tr><tr><td>
[15]</td><td>FMCIDLE</td><td><div style="word-wrap: break-word;"><b>Flash Memory Controller Clock Enable Bit in IDLE Mode
</b><br>
0 = FMC clock Disabled when chip is under IDLE mode.
<br>
1 = FMC clock Enabled when chip is under IDLE mode.
<br>
</div></td></tr><tr><td>
[16]</td><td>USBHCKEN</td><td><div style="word-wrap: break-word;"><b>USB HOST Controller Clock Enable Bit
</b><br>
0 = USB HOST peripheral clock Disabled.
<br>
1 = USB HOST peripheral clock Enabled.
<br>
</div></td></tr><tr><td>
[17]</td><td>SDH1CKEN</td><td><div style="word-wrap: break-word;"><b>SD1 Controller Clock Enable Bit
</b><br>
0 = SD1 engine clock Disabled.
<br>
1 = SD1 engine clock Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::APBCLK0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">APBCLK0
</font><br><p> <font size="2">
Offset: 0x08  APB Devices Clock Enable Control Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>WDTCKEN</td><td><div style="word-wrap: break-word;"><b>Watchdog Timer Clock Enable Bit (Write Protect)
</b><br>
0 = Watchdog timer clock Disabled.
<br>
1 = Watchdog timer clock Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[1]</td><td>RTCCKEN</td><td><div style="word-wrap: break-word;"><b>Real-time-clock APB Interface Clock Enable Bit
</b><br>
This bit is used to control the RTC APB clock only
<br>
The RTC peripheral clock source is selected from RTCSEL(CLK_CLKSEL3[8])
<br>
It can be selected to 32.768 kHz external low speed crystal or 10 kHz internal low speed RC oscillator (LIRC).
<br>
0 = RTC clock Disabled.
<br>
1 = RTC clock Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>TMR0CKEN</td><td><div style="word-wrap: break-word;"><b>Timer0 Clock Enable Bit
</b><br>
0 = Timer0 clock Disabled.
<br>
1 = Timer0 clock Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>TMR1CKEN</td><td><div style="word-wrap: break-word;"><b>Timer1 Clock Enable Bit
</b><br>
0 = Timer1 clock Disabled.
<br>
1 = Timer1 clock Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>TMR2CKEN</td><td><div style="word-wrap: break-word;"><b>Timer2 Clock Enable Bit
</b><br>
0 = Timer2 clock Disabled.
<br>
1 = Timer2 clock Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>TMR3CKEN</td><td><div style="word-wrap: break-word;"><b>Timer3 Clock Enable Bit
</b><br>
0 = Timer3 clock Disabled.
<br>
1 = Timer3 clock Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>CLKOCKEN</td><td><div style="word-wrap: break-word;"><b>CLKO Clock Enable Bit
</b><br>
0 = CLKO clock Disabled.
<br>
1 = CLKO clock Enabled.
<br>
</div></td></tr><tr><td>
[7]</td><td>ACMP01CKEN</td><td><div style="word-wrap: break-word;"><b>Analog Comparator 0/1 Clock Enable Bit
</b><br>
0 = Analog comparator 0/1 clock Disabled.
<br>
1 = Analog comparator 0/1 clock Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>I2C0CKEN</td><td><div style="word-wrap: break-word;"><b>I2C0 Clock Enable Bit
</b><br>
0 = I2C0 clock Disabled.
<br>
1 = I2C0 clock Enabled.
<br>
</div></td></tr><tr><td>
[9]</td><td>I2C1CKEN</td><td><div style="word-wrap: break-word;"><b>I2C1 Clock Enable Bit
</b><br>
0 = I2C1 clock Disabled.
<br>
1 = I2C1 clock Enabled.
<br>
</div></td></tr><tr><td>
[10]</td><td>I2C2CKEN</td><td><div style="word-wrap: break-word;"><b>I2C2 Clock Enable Bit
</b><br>
0 = I2C2 clock Disabled.
<br>
1 = I2C2 clock Enabled.
<br>
</div></td></tr><tr><td>
[12]</td><td>QSPI0CKEN</td><td><div style="word-wrap: break-word;"><b>QSPI0 Clock Enable Bit
</b><br>
0 = QSPI0 clock Disabled.
<br>
1 = QSPI0 clock Enabled.
<br>
</div></td></tr><tr><td>
[13]</td><td>SPI0CKEN</td><td><div style="word-wrap: break-word;"><b>SPI0 Clock Enable Bit
</b><br>
0 = SPI0 clock Disabled.
<br>
1 = SPI0 clock Enabled.
<br>
</div></td></tr><tr><td>
[14]</td><td>SPI1CKEN</td><td><div style="word-wrap: break-word;"><b>SPI1 Clock Enable Bit
</b><br>
0 = SPI1 clock Disabled.
<br>
1 = SPI1 clock Enabled.
<br>
</div></td></tr><tr><td>
[15]</td><td>SPI2CKEN</td><td><div style="word-wrap: break-word;"><b>SPI2 Clock Enable Bit
</b><br>
0 = SPI2 clock Disabled.
<br>
1 = SPI2 clock Enabled.
<br>
</div></td></tr><tr><td>
[16]</td><td>UART0CKEN</td><td><div style="word-wrap: break-word;"><b>UART0 Clock Enable Bit
</b><br>
0 = UART0 clock Disabled.
<br>
1 = UART0 clock Enabled.
<br>
</div></td></tr><tr><td>
[17]</td><td>UART1CKEN</td><td><div style="word-wrap: break-word;"><b>UART1 Clock Enable Bit
</b><br>
0 = UART1 clock Disabled.
<br>
1 = UART1 clock Enabled.
<br>
</div></td></tr><tr><td>
[18]</td><td>UART2CKEN</td><td><div style="word-wrap: break-word;"><b>UART2 Clock Enable Bit
</b><br>
0 = UART2 clock Disabled.
<br>
1 = UART2 clock Enabled.
<br>
</div></td></tr><tr><td>
[19]</td><td>UART3CKEN</td><td><div style="word-wrap: break-word;"><b>UART3 Clock Enable Bit
</b><br>
0 = UART3 clock Disabled.
<br>
1 = UART3 clock Enabled.
<br>
</div></td></tr><tr><td>
[20]</td><td>UART4CKEN</td><td><div style="word-wrap: break-word;"><b>UART4 Clock Enable Bit
</b><br>
0 = UART4 clock Disabled.
<br>
1 = UART4 clock Enabled.
<br>
</div></td></tr><tr><td>
[21]</td><td>UART5CKEN</td><td><div style="word-wrap: break-word;"><b>UART5 Clock Enable Bit
</b><br>
0 = UART5 clock Disabled.
<br>
1 = UART5 clock Enabled.
<br>
</div></td></tr><tr><td>
[24]</td><td>CAN0CKEN</td><td><div style="word-wrap: break-word;"><b>CAN0 Clock Enable Bit
</b><br>
0 = CAN0 clock Disabled.
<br>
1 = CAN0 clock Enabled.
<br>
</div></td></tr><tr><td>
[25]</td><td>CAN1CKEN</td><td><div style="word-wrap: break-word;"><b>CAN1 Clock Enable Bit
</b><br>
0 = CAN1 clock Disabled.
<br>
1 = CAN1 clock Enabled.
<br>
</div></td></tr><tr><td>
[26]</td><td>OTGCKEN</td><td><div style="word-wrap: break-word;"><b>USB OTG Clock Enable Bit
</b><br>
0 = USB OTG clock Disabled.
<br>
1 = USB OTG clock Enabled.
<br>
</div></td></tr><tr><td>
[27]</td><td>USBDCKEN</td><td><div style="word-wrap: break-word;"><b>USB Device Clock Enable Bit
</b><br>
0 = USB Device clock Disabled.
<br>
1 = USB Device clock Enabled.
<br>
</div></td></tr><tr><td>
[28]</td><td>EADCCKEN</td><td><div style="word-wrap: break-word;"><b>Enhanced Analog-digital-converter (EADC) Clock Enable Bit
</b><br>
0 = EADC clock Disabled.
<br>
1 = EADC clock Enabled.
<br>
</div></td></tr><tr><td>
[29]</td><td>I2S0CKEN</td><td><div style="word-wrap: break-word;"><b>I2S0 Clock Enable Bit
</b><br>
0 = I2S0 Clock Disabled.
<br>
1 = I2S0 Clock Enabled.
<br>
</div></td></tr><tr><td>
[30]</td><td>HSOTGCKEN</td><td><div style="word-wrap: break-word;"><b>HSUSB OTG Clock Enable Bit
</b><br>
0 = HSUSB OTG clock Disabled.
<br>
1 = HSUSB OTG clock Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::APBCLK1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">APBCLK1
</font><br><p> <font size="2">
Offset: 0x0C  APB Devices Clock Enable Control Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SC0CKEN</td><td><div style="word-wrap: break-word;"><b>SC0 Clock Enable Bit
</b><br>
0 = SC0 clock Disabled.
<br>
1 = SC0 clock Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>SC1CKEN</td><td><div style="word-wrap: break-word;"><b>SC1 Clock Enable Bit
</b><br>
0 = SC1 clock Disabled.
<br>
1 = SC1 clock Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>SC2CKEN</td><td><div style="word-wrap: break-word;"><b>SC2 Clock Enable Bit
</b><br>
0 = SC2 clock Disabled.
<br>
1 = SC2 clock Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>SPI3CKEN</td><td><div style="word-wrap: break-word;"><b>SPI3 Clock Enable Bit
</b><br>
0 = SPI3 clock Disabled.
<br>
1 = SPI3 clock Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>USCI0CKEN</td><td><div style="word-wrap: break-word;"><b>USCI0 Clock Enable Bit
</b><br>
0 = USCI0 clock Disabled.
<br>
1 = USCI0 clock Enabled.
<br>
</div></td></tr><tr><td>
[9]</td><td>USCI1CKEN</td><td><div style="word-wrap: break-word;"><b>USCI1 Clock Enable Bit
</b><br>
0 = USCI1 clock Disabled.
<br>
1 = USCI1 clock Enabled.
<br>
</div></td></tr><tr><td>
[12]</td><td>DACCKEN</td><td><div style="word-wrap: break-word;"><b>DAC Clock Enable Bit
</b><br>
0 = DAC clock Disabled.
<br>
1 = DAC clock Enabled.
<br>
</div></td></tr><tr><td>
[16]</td><td>EPWM0CKEN</td><td><div style="word-wrap: break-word;"><b>EPWM0 Clock Enable Bit
</b><br>
0 = EPWM0 clock Disabled.
<br>
1 = EPWM0 clock Enabled.
<br>
</div></td></tr><tr><td>
[17]</td><td>EPWM1CKEN</td><td><div style="word-wrap: break-word;"><b>EPWM1 Clock Enable Bit
</b><br>
0 = EPWM1 clock Disabled.
<br>
1 = EPWM1 clock Enabled.
<br>
</div></td></tr><tr><td>
[18]</td><td>BPWM0CKEN</td><td><div style="word-wrap: break-word;"><b>BPWM0 Clock Enable Bit
</b><br>
0 = BPWM0 clock Disabled.
<br>
1 = BPWM0 clock Enabled.
<br>
</div></td></tr><tr><td>
[19]</td><td>BPWM1CKEN</td><td><div style="word-wrap: break-word;"><b>BPWM1 Clock Enable Bit
</b><br>
0 = BPWM1 clock Disabled.
<br>
1 = BPWM1 clock Enabled.
<br>
</div></td></tr><tr><td>
[22]</td><td>QEI0CKEN</td><td><div style="word-wrap: break-word;"><b>QEI0 Clock Enable Bit
</b><br>
0 = QEI0 clock Disabled.
<br>
1 = QEI0 clock Enabled.
<br>
</div></td></tr><tr><td>
[23]</td><td>QEI1CKEN</td><td><div style="word-wrap: break-word;"><b>QEI1 Clock Enable Bit
</b><br>
0 = QEI1 clock Disabled.
<br>
1 = QEI1 clock Enabled.
<br>
</div></td></tr><tr><td>
[26]</td><td>ECAP0CKEN</td><td><div style="word-wrap: break-word;"><b>ECAP0 Clock Enable Bit
</b><br>
0 = ECAP0 clock Disabled.
<br>
1 = ECAP0 clock Enabled.
<br>
</div></td></tr><tr><td>
[27]</td><td>ECAP1CKEN</td><td><div style="word-wrap: break-word;"><b>ECAP1 Clock Enable Bit
</b><br>
0 = ECAP1 clock Disabled.
<br>
1 = ECAP1 clock Enabled.
<br>
</div></td></tr><tr><td>
[30]</td><td>OPACKEN</td><td><div style="word-wrap: break-word;"><b>OP Amplifier (OPA) Clock Enable Bit
</b><br>
0 = OPA clock Disabled.
<br>
1 = OPA clock Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::CLKSEL0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKSEL0
</font><br><p> <font size="2">
Offset: 0x10  Clock Source Select Control Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2:0]</td><td>HCLKSEL</td><td><div style="word-wrap: break-word;"><b>HCLK Clock Source Selection (Write Protect)
</b><br>
Before clock switching, the related clock sources (both pre-select and new-select) must be turned on.
<br>
The default value is reloaded from the value of CFOSC (CONFIG0[26]) in user configuration register of Flash controller by any reset
<br>
Therefore the default value is either 000b or 111b.
<br>
000 = Clock source from HXT.
<br>
001 = Clock source from LXT.
<br>
010 = Clock source from PLL.
<br>
011 = Clock source from LIRC.
<br>
111 = Clock source from HIRC.
<br>
Other = Reserved.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[5:3]</td><td>STCLKSEL</td><td><div style="word-wrap: break-word;"><b>Cortex-M4 SysTick Clock Source Selection (Write Protect)
</b><br>
If SYST_CTRL[2]=0, SysTick uses listed clock source below.
<br>
000 = Clock source from HXT.
<br>
001 = Clock source from LXT.
<br>
010 = Clock source from HXT/2.
<br>
011 = Clock source from HCLK/2.
<br>
111 = Clock source from HIRC/2.
<br>
Note: if SysTick clock source is not from HCLK (i.e
<br>
SYST_CTRL[2] = 0), SysTick clock source must less than or equal to HCLK/2.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[8]</td><td>USBSEL</td><td><div style="word-wrap: break-word;"><b>USB Clock Source Selection (Write Protect)
</b><br>
0 = Clock source from RC48M.
<br>
1 = Clock source from PLL.
<br>
</div></td></tr><tr><td>
[21:20]</td><td>SDH0SEL</td><td><div style="word-wrap: break-word;"><b>SD0 Engine Clock Source Selection (Write Protect)
</b><br>
00 = Clock source from HXT clock.
<br>
01 = Clock source from PLL clock.
<br>
10 = Clock source from HCLK.
<br>
11 = Clock source from HIRC clock.
<br>
</div></td></tr><tr><td>
[23:22]</td><td>SDH1SEL</td><td><div style="word-wrap: break-word;"><b>SD1 Engine Clock Source Selection (Write Protect)
</b><br>
00 = Clock source from HXT clock.
<br>
01 = Clock source from PLL clock.
<br>
10 = Clock source from HCLK.
<br>
11 = Clock source from HIRC clock.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::CLKSEL1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKSEL1
</font><br><p> <font size="2">
Offset: 0x14  Clock Source Select Control Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1:0]</td><td>WDTSEL</td><td><div style="word-wrap: break-word;"><b>Watchdog Timer Clock Source Selection (Write Protect)
</b><br>
00 = Reserved.
<br>
01 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
<br>
10 = Clock source from HCLK/2048.
<br>
11 = Clock source from 10 kHz internal low speed RC oscillator (LIRC).
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[10:8]</td><td>TMR0SEL</td><td><div style="word-wrap: break-word;"><b>TIMER0 Clock Source Selection
</b><br>
000 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
<br>
010 = Clock source from PCLK0.
<br>
011 = Clock source from external clock TM0 pin.
<br>
101 = Clock source from 10 kHz internal low speed RC oscillator (LIRC).
<br>
111 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
Others = Reserved.
<br>
</div></td></tr><tr><td>
[14:12]</td><td>TMR1SEL</td><td><div style="word-wrap: break-word;"><b>TIMER1 Clock Source Selection
</b><br>
000 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
<br>
010 = Clock source from PCLK0.
<br>
011 = Clock source from external clock TM1 pin.
<br>
101 = Clock source from 10 kHz internal low speed RC oscillator (LIRC).
<br>
111 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
Others = Reserved.
<br>
</div></td></tr><tr><td>
[18:16]</td><td>TMR2SEL</td><td><div style="word-wrap: break-word;"><b>TIMER2 Clock Source Selection
</b><br>
000 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
<br>
010 = Clock source from PCLK1.
<br>
011 = Clock source from external clock TM2 pin.
<br>
101 = Clock source from 10 kHz internal low speed RC oscillator (LIRC).
<br>
111 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
Others = Reserved.
<br>
</div></td></tr><tr><td>
[22:20]</td><td>TMR3SEL</td><td><div style="word-wrap: break-word;"><b>TIMER3 Clock Source Selection
</b><br>
000 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
001 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
<br>
010 = Clock source from PCLK1.
<br>
011 = Clock source from external clock TM3 pin.
<br>
101 = Clock source from 10 kHz internal low speed RC oscillator (LIRC).
<br>
111 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
Others = Reserved.
<br>
</div></td></tr><tr><td>
[25:24]</td><td>UART0SEL</td><td><div style="word-wrap: break-word;"><b>UART0 Clock Source Selection
</b><br>
00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
01 = Clock source from PLL.
<br>
10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
<br>
11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
</div></td></tr><tr><td>
[27:26]</td><td>UART1SEL</td><td><div style="word-wrap: break-word;"><b>UART1 Clock Source Selection
</b><br>
00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
01 = Clock source from PLL.
<br>
10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
<br>
11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
</div></td></tr><tr><td>
[29:28]</td><td>CLKOSEL</td><td><div style="word-wrap: break-word;"><b>Clock Divider Clock Source Selection
</b><br>
00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
01 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
<br>
10 = Clock source from HCLK.
<br>
11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
</div></td></tr><tr><td>
[31:30]</td><td>WWDTSEL</td><td><div style="word-wrap: break-word;"><b>Window Watchdog Timer Clock Source Selection
</b><br>
10 = Clock source from HCLK/2048.
<br>
11 = Clock source from 10 kHz internal low speed RC oscillator (LIRC).
<br>
Others = Reserved.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::CLKSEL2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKSEL2
</font><br><p> <font size="2">
Offset: 0x18  Clock Source Select Control Register 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>EPWM0SEL</td><td><div style="word-wrap: break-word;"><b>EPWM0 Clock Source Selection
</b><br>
The peripheral clock source of EPWM0 is defined by EPWM0SEL.
<br>
0 = Clock source from PLL.
<br>
1 = Clock source from PCLK0.
<br>
</div></td></tr><tr><td>
[1]</td><td>EPWM1SEL</td><td><div style="word-wrap: break-word;"><b>EPWM1 Clock Source Selection
</b><br>
The peripheral clock source of EPWM1 is defined by EPWM1SEL.
<br>
0 = Clock source from PLL.
<br>
1 = Clock source from PCLK1.
<br>
</div></td></tr><tr><td>
[3:2]</td><td>QSPI0SEL</td><td><div style="word-wrap: break-word;"><b>QSPI0 Clock Source Selection
</b><br>
00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
01 = Clock source from PLL.
<br>
10 = Clock source from PCLK0.
<br>
11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
</div></td></tr><tr><td>
[5:4]</td><td>SPI0SEL</td><td><div style="word-wrap: break-word;"><b>SPI0 Clock Source Selection
</b><br>
00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
01 = Clock source from PLL.
<br>
10 = Clock source from PCLK1.
<br>
11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
</div></td></tr><tr><td>
[7:6]</td><td>SPI1SEL</td><td><div style="word-wrap: break-word;"><b>SPI1 Clock Source Selection
</b><br>
00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
01 = Clock source from PLL.
<br>
10 = Clock source from PCLK0.
<br>
11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
</div></td></tr><tr><td>
[8]</td><td>BPWM0SEL</td><td><div style="word-wrap: break-word;"><b>BPWM0 Clock Source Selection
</b><br>
The peripheral clock source of BPWM0 is defined by BPWM0SEL.
<br>
0 = Clock source from PLL.
<br>
1 = Clock source from PCLK0.
<br>
</div></td></tr><tr><td>
[9]</td><td>BPWM1SEL</td><td><div style="word-wrap: break-word;"><b>BPWM1 Clock Source Selection
</b><br>
The peripheral clock source of BPWM1 is defined by BPWM1SEL.
<br>
0 = Clock source from PLL.
<br>
1 = Clock source from PCLK1.
<br>
</div></td></tr><tr><td>
[11:10]</td><td>SPI2SEL</td><td><div style="word-wrap: break-word;"><b>SPI2 Clock Source Selection
</b><br>
00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
01 = Clock source from PLL.
<br>
10 = Clock source from PCLK1.
<br>
11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
</div></td></tr><tr><td>
[13:12]</td><td>SPI3SEL</td><td><div style="word-wrap: break-word;"><b>SPI3 Clock Source Selection
</b><br>
00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
01 = Clock source from PLL.
<br>
10 = Clock source from PCLK0.
<br>
11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::CLKSEL3

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKSEL3
</font><br><p> <font size="2">
Offset: 0x1C  Clock Source Select Control Register 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1:0]</td><td>SC0SEL</td><td><div style="word-wrap: break-word;"><b>SC0 Clock Source Selection
</b><br>
00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
01 = Clock source from PLL.
<br>
10 = Clock source from PCLK0.
<br>
11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
</div></td></tr><tr><td>
[3:2]</td><td>SC1SEL</td><td><div style="word-wrap: break-word;"><b>SC0 Clock Source Selection
</b><br>
00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
01 = Clock source from PLL.
<br>
10 = Clock source from PCLK1.
<br>
11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
</div></td></tr><tr><td>
[5:4]</td><td>SC2SEL</td><td><div style="word-wrap: break-word;"><b>SC2 Clock Source Selection
</b><br>
00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
01 = Clock source from PLL.
<br>
10 = Clock source from PCLK0.
<br>
11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
</div></td></tr><tr><td>
[8]</td><td>RTCSEL</td><td><div style="word-wrap: break-word;"><b>RTC Clock Source Selection
</b><br>
0 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
<br>
1 = Clock source from 10 kHz internal low speed RC oscillator (LIRC).
<br>
</div></td></tr><tr><td>
[17:16]</td><td>I2S0SEL</td><td><div style="word-wrap: break-word;"><b>I2S0 Clock Source Selection
</b><br>
00 = Clock source from HXT clock.
<br>
01 = Clock source from PLL clock.
<br>
10 = Clock source from PCLK.
<br>
11 = Clock source from HIRC clock.
<br>
</div></td></tr><tr><td>
[25:24]</td><td>UART2SEL</td><td><div style="word-wrap: break-word;"><b>UART2 Clock Source Selection
</b><br>
00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
01 = Clock source from PLL.
<br>
10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
<br>
11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
</div></td></tr><tr><td>
[27:26]</td><td>UART3SEL</td><td><div style="word-wrap: break-word;"><b>UART3 Clock Source Selection
</b><br>
00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
01 = Clock source from PLL.
<br>
10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
<br>
11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
</div></td></tr><tr><td>
[29:28]</td><td>UART4SEL</td><td><div style="word-wrap: break-word;"><b>UART4 Clock Source Selection
</b><br>
00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
01 = Clock source from PLL.
<br>
10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
<br>
11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
</div></td></tr><tr><td>
[31:30]</td><td>UART5SEL</td><td><div style="word-wrap: break-word;"><b>UART5 Clock Source Selection
</b><br>
00 = Clock source from 4~24 MHz external high speed crystal oscillator (HXT).
<br>
01 = Clock source from PLL.
<br>
10 = Clock source from 32.768 kHz external low speed crystal oscillator (LXT).
<br>
11 = Clock source from 12 MHz internal high speed RC oscillator (HIRC).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::CLKDIV0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKDIV0
</font><br><p> <font size="2">
Offset: 0x20  Clock Divider Number Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>HCLKDIV</td><td><div style="word-wrap: break-word;"><b>HCLK Clock Divide Number From HCLK Clock Source
</b><br>
HCLK clock frequency = (HCLK clock source frequency) / (HCLKDIV + 1).
<br>
</div></td></tr><tr><td>
[7:4]</td><td>USBDIV</td><td><div style="word-wrap: break-word;"><b>USB Clock Divide Number From PLL Clock
</b><br>
USB clock frequency = (PLL frequency) / (USBDIV + 1).
<br>
</div></td></tr><tr><td>
[11:8]</td><td>UART0DIV</td><td><div style="word-wrap: break-word;"><b>UART0 Clock Divide Number From UART0 Clock Source
</b><br>
UART0 clock frequency = (UART0 clock source frequency) / (UART0DIV + 1).
<br>
</div></td></tr><tr><td>
[15:12]</td><td>UART1DIV</td><td><div style="word-wrap: break-word;"><b>UART1 Clock Divide Number From UART1 Clock Source
</b><br>
UART1 clock frequency = (UART1 clock source frequency) / (UART1DIV + 1).
<br>
</div></td></tr><tr><td>
[23:16]</td><td>EADCDIV</td><td><div style="word-wrap: break-word;"><b>EADC Clock Divide Number From EADC Clock Source
</b><br>
EADC clock frequency = (EADC clock source frequency) / (EADCDIV + 1).
<br>
</div></td></tr><tr><td>
[31:24]</td><td>SDH0DIV</td><td><div style="word-wrap: break-word;"><b>SD0 Clock Divide Number From SD0 Clock Source
</b><br>
SD0 clock frequency = (SD0 clock source frequency) / (SDH0DIV + 1).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::CLKDIV1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKDIV1
</font><br><p> <font size="2">
Offset: 0x24  Clock Divider Number Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>SC0DIV</td><td><div style="word-wrap: break-word;"><b>SC0 Clock Divide Number From SC0 Clock Source
</b><br>
SC0 clock frequency = (SC0 clock source frequency ) / (SC0DIV + 1).
<br>
</div></td></tr><tr><td>
[15:8]</td><td>SC1DIV</td><td><div style="word-wrap: break-word;"><b>SC1 Clock Divide Number From SC1 Clock Source
</b><br>
SC1 clock frequency = (SC1 clock source frequency ) / (SC1DIV + 1).
<br>
</div></td></tr><tr><td>
[23:16]</td><td>SC2DIV</td><td><div style="word-wrap: break-word;"><b>SC2 Clock Divide Number From SC2 Clock Source
</b><br>
SC2 clock frequency = (SC2 clock source frequency ) / (SC2DIV + 1).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::CLKDIV3

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKDIV3
</font><br><p> <font size="2">
Offset: 0x2C  Clock Divider Number Register 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[23:16]</td><td>EMACDIV</td><td><div style="word-wrap: break-word;"><b>Ethernet Clock Divide Number Form HCLK
</b><br>
EMAC MDCLK clock frequency = (HCLK) / (EMACDIV + 1).
<br>
</div></td></tr><tr><td>
[31:24]</td><td>SDH1DIV</td><td><div style="word-wrap: break-word;"><b>SD1 Clock Divide Number From SD1 Clock Source
</b><br>
SD1 clock frequency = (SD1 clock source frequency) / (SDH1DIV + 1).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::CLKDIV4

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKDIV4
</font><br><p> <font size="2">
Offset: 0x30  Clock Divider Number Register 4
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>UART2DIV</td><td><div style="word-wrap: break-word;"><b>UART2 Clock Divide Number From UART2 Clock Source
</b><br>
UART2 clock frequency = (UART2 clock source frequency) / (UART2DIV + 1).
<br>
</div></td></tr><tr><td>
[7:4]</td><td>UART3DIV</td><td><div style="word-wrap: break-word;"><b>UART3 Clock Divide Number From UART3 Clock Source
</b><br>
UART3 clock frequency = (UART3 clock source frequency) / (UART3DIV + 1).
<br>
</div></td></tr><tr><td>
[11:8]</td><td>UART4DIV</td><td><div style="word-wrap: break-word;"><b>UART4 Clock Divide Number From UART4 Clock Source
</b><br>
UART4 clock frequency = (UART4 clock source frequency) / (UART4DIV + 1).
<br>
</div></td></tr><tr><td>
[15:12]</td><td>UART5DIV</td><td><div style="word-wrap: break-word;"><b>UART5 Clock Divide Number From UART5 Clock Source
</b><br>
UART5 clock frequency = (UART5 clock source frequency) / (UART5DIV + 1).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::PCLKDIV

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PCLKDIV
</font><br><p> <font size="2">
Offset: 0x34  APB Clock Divider Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2:0]</td><td>APB0DIV</td><td><div style="word-wrap: break-word;"><b>APB0 Clock Divider
</b><br>
APB0 clock can be divided from HCLK
<br>
000: PCLK0 = HCLK.
<br>
001: PCLK0 = 1/2 HCLK.
<br>
010: PCLK0 = 1/4 HCLK.
<br>
011: PCLK0 = 1/8 HCLK.
<br>
100: PCLK0 = 1/16 HCLK.
<br>
Others: Reserved.
<br>
</div></td></tr><tr><td>
[6:4]</td><td>APB1DIV</td><td><div style="word-wrap: break-word;"><b>APB1 Clock Divider
</b><br>
APB1 clock can be divided from HCLK
<br>
000: PCLK1 = HCLK.
<br>
001: PCLK1 = 1/2 HCLK.
<br>
010: PCLK1 = 1/4 HCLK.
<br>
011: PCLK1 = 1/8 HCLK.
<br>
100: PCLK1 = 1/16 HCLK.
<br>
Others: Reserved.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::PLLCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PLLCTL
</font><br><p> <font size="2">
Offset: 0x40  PLL Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[8:0]</td><td>FBDIV</td><td><div style="word-wrap: break-word;"><b>PLL Feedback Divider Control (Write Protect)
</b><br>
Refer to the formulas below the table.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[13:9]</td><td>INDIV</td><td><div style="word-wrap: break-word;"><b>PLL Input Divider Control (Write Protect)
</b><br>
Refer to the formulas below the table.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[15:14]</td><td>OUTDIV</td><td><div style="word-wrap: break-word;"><b>PLL Output Divider Control (Write Protect)
</b><br>
Refer to the formulas below the table.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[16]</td><td>PD</td><td><div style="word-wrap: break-word;"><b>Power-down Mode (Write Protect)
</b><br>
If set the PDEN bit to 1 in CLK_PWRCTL register, the PLL will enter Power-down mode, too.
<br>
0 = PLL is in normal mode.
<br>
1 = PLL is in Power-down mode (default).
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[17]</td><td>BP</td><td><div style="word-wrap: break-word;"><b>PLL Bypass Control (Write Protect)
</b><br>
0 = PLL is in normal mode (default).
<br>
1 = PLL clock output is same as PLL input clock FIN.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[18]</td><td>OE</td><td><div style="word-wrap: break-word;"><b>PLL OE (FOUT Enable) Pin Control (Write Protect)
</b><br>
0 = PLL FOUT Enabled.
<br>
1 = PLL FOUT is fixed low.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[19]</td><td>PLLSRC</td><td><div style="word-wrap: break-word;"><b>PLL Source Clock Selection (Write Protect)
</b><br>
0 = PLL source clock from 4~24 MHz external high-speed crystal oscillator (HXT).
<br>
1 = PLL source clock from 12 MHz internal high-speed oscillator (HIRC).
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[23]</td><td>STBSEL</td><td><div style="word-wrap: break-word;"><b>PLL Stable Counter Selection (Write Protect)
</b><br>
0 = PLL stable time is 6144 PLL source clock (suitable for source clock is equal to or less than 12 MHz).
<br>
1 = PLL stable time is 12288 PLL source clock (suitable for source clock is larger than 12 MHz).
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::STATUS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STATUS
</font><br><p> <font size="2">
Offset: 0x50  Clock Status Monitor Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>HXTSTB</td><td><div style="word-wrap: break-word;"><b>HXT Clock Source Stable Flag (Read Only)
</b><br>
0 = 4~24 MHz external high speed crystal oscillator (HXT) clock is not stable or disabled.
<br>
1 = 4~24 MHz external high speed crystal oscillator (HXT) clock is stable and enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>LXTSTB</td><td><div style="word-wrap: break-word;"><b>LXT Clock Source Stable Flag (Read Only)
</b><br>
0 = 32.768 kHz external low speed crystal oscillator (LXT) clock is not stable or disabled.
<br>
1 = 32.768 kHz external low speed crystal oscillator (LXT) clock is stabled and enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>PLLSTB</td><td><div style="word-wrap: break-word;"><b>Internal PLL Clock Source Stable Flag (Read Only)
</b><br>
0 = Internal PLL clock is not stable or disabled.
<br>
1 = Internal PLL clock is stable and enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>LIRCSTB</td><td><div style="word-wrap: break-word;"><b>LIRC Clock Source Stable Flag (Read Only)
</b><br>
0 = 10 kHz internal low speed RC oscillator (LIRC) clock is not stable or disabled.
<br>
1 = 10 kHz internal low speed RC oscillator (LIRC) clock is stable and enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>HIRCSTB</td><td><div style="word-wrap: break-word;"><b>HIRC Clock Source Stable Flag (Read Only)
</b><br>
0 = 12 MHz internal high speed RC oscillator (HIRC) clock is not stable or disabled.
<br>
1 = 12 MHz internal high speed RC oscillator (HIRC) clock is stable and enabled.
<br>
Note: This bit is read only.
<br>
</div></td></tr><tr><td>
[6]</td><td>HIRC48MSTB</td><td><div style="word-wrap: break-word;"><b>HIRC 48MHz Clock Source Stable Flag (Read Only)
</b><br>
0 = 48 MHz internal high speed RC oscillator (HIRC) clock is not stable or disabled.
<br>
1 = 48 MHz internal high speed RC oscillator (HIRC) clock is stable and enabled.
<br>
Note: This bit is read only.
<br>
</div></td></tr><tr><td>
[7]</td><td>CLKSFAIL</td><td><div style="word-wrap: break-word;"><b>Clock Switching Fail Flag (Read Only)
</b><br>
This bit is updated when software switches system clock source
<br>
If switch target clock is stable, this bit will be set to 0
<br>
If switch target clock is not stable, this bit will be set to 1.
<br>
0 = Clock switching success.
<br>
1 = Clock switching failure.
<br>
Note: Write 1 to clear the bit to 0.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::CLKOCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKOCTL
</font><br><p> <font size="2">
Offset: 0x60  Clock Output Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>FREQSEL</td><td><div style="word-wrap: break-word;"><b>Clock Output Frequency Selection
</b><br>
The formula of output frequency is
<br>
Fout = Fin/2(N+1).
<br>
Fin is the input clock frequency.
<br>
Fout is the frequency of divider output clock.
<br>
N is the 4-bit value of FREQSEL[3:0].
<br>
</div></td></tr><tr><td>
[4]</td><td>CLKOEN</td><td><div style="word-wrap: break-word;"><b>Clock Output Enable Bit
</b><br>
0 = Clock Output function Disabled.
<br>
1 = Clock Output function Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>DIV1EN</td><td><div style="word-wrap: break-word;"><b>Clock Output Divide One Enable Bit
</b><br>
0 = Clock Output will output clock with source frequency divided by FREQSEL.
<br>
1 = Clock Output will output clock with source frequency.
<br>
</div></td></tr><tr><td>
[6]</td><td>CLK1HZEN</td><td><div style="word-wrap: break-word;"><b>Clock Output 1Hz Enable Bit
</b><br>
0 = 1 Hz clock output for 32.768 kHz frequency compensation Disabled.
<br>
1 = 1 Hz clock output for 32.768 kHz frequency compensation Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::CLKDCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKDCTL
</font><br><p> <font size="2">
Offset: 0x70  Clock Fail Detector Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[4]</td><td>HXTFDEN</td><td><div style="word-wrap: break-word;"><b>HXT Clock Fail Detector Enable Bit
</b><br>
0 = 4~24 MHz external high speed crystal oscillator (HXT) clock fail detector Disabled.
<br>
1 = 4~24 MHz external high speed crystal oscillator (HXT) clock fail detector Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>HXTFIEN</td><td><div style="word-wrap: break-word;"><b>HXT Clock Fail Interrupt Enable Bit
</b><br>
0 = 4~24 MHz external high speed crystal oscillator (HXT) clock fail interrupt Disabled.
<br>
1 = 4~24 MHz external high speed crystal oscillator (HXT) clock fail interrupt Enabled.
<br>
</div></td></tr><tr><td>
[12]</td><td>LXTFDEN</td><td><div style="word-wrap: break-word;"><b>LXT Clock Fail Detector Enable Bit
</b><br>
0 = 32.768 kHz external low speed crystal oscillator (LXT) clock fail detector Disabled.
<br>
1 = 32.768 kHz external low speed crystal oscillator (LXT) clock fail detector Enabled.
<br>
</div></td></tr><tr><td>
[13]</td><td>LXTFIEN</td><td><div style="word-wrap: break-word;"><b>LXT Clock Fail Interrupt Enable Bit
</b><br>
0 = 32.768 kHz external low speed crystal oscillator (LXT) clock fail interrupt Disabled.
<br>
1 = 32.768 kHz external low speed crystal oscillator (LXT) clock fail interrupt Enabled.
<br>
</div></td></tr><tr><td>
[16]</td><td>HXTFQDEN</td><td><div style="word-wrap: break-word;"><b>HXT Clock Frequency Range Detector Enable Bit
</b><br>
0 = 4~24 MHz external high speed crystal oscillator (HXT) clock frequency range detector Disabled.
<br>
1 = 4~24 MHz external high speed crystal oscillator (HXT) clock frequency range detector Enabled.
<br>
</div></td></tr><tr><td>
[17]</td><td>HXTFQIEN</td><td><div style="word-wrap: break-word;"><b>HXT Clock Frequency Range Detector Interrupt Enable Bit
</b><br>
0 = 4~24 MHz external high speed crystal oscillator (HXT) clock frequency range detector fail interrupt Disabled.
<br>
1 = 4~24 MHz external high speed crystal oscillator (HXT) clock frequency range detector fail interrupt Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::CLKDSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CLKDSTS
</font><br><p> <font size="2">
Offset: 0x74  Clock Fail Detector Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>HXTFIF</td><td><div style="word-wrap: break-word;"><b>HXT Clock Fail Interrupt Flag
</b><br>
0 = 4~24 MHz external high speed crystal oscillator (HXT) clock is normal.
<br>
1 = 4~24 MHz external high speed crystal oscillator (HXT) clock stops.
<br>
Note: Write 1 to clear the bit to 0.
<br>
</div></td></tr><tr><td>
[1]</td><td>LXTFIF</td><td><div style="word-wrap: break-word;"><b>LXT Clock Fail Interrupt Flag
</b><br>
0 = 32.768 kHz external low speed crystal oscillator (LXT) clock is normal.
<br>
1 = 32.768 kHz external low speed crystal oscillator (LXT) stops.
<br>
Note: Write 1 to clear the bit to 0.
<br>
</div></td></tr><tr><td>
[8]</td><td>HXTFQIF</td><td><div style="word-wrap: break-word;"><b>HXT Clock Frequency Range Detector Interrupt Flag
</b><br>
0 = 4~24 MHz external high speed crystal oscillator (HXT) clock frequency is normal.
<br>
1 = 4~24 MHz external high speed crystal oscillator (HXT) clock frequency is abnormal.
<br>
Note: Write 1 to clear the bit to 0.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::CDUPB

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CDUPB
</font><br><p> <font size="2">
Offset: 0x78  Clock Frequency Range Detector Upper Boundary Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[9:0]</td><td>UPERBD</td><td><div style="word-wrap: break-word;"><b>HXT Clock Frequency Range Detector Upper Boundary Value
</b><br>
The bits define the maximum value of frequency range detector window.
<br>
When HXT frequency higher than this maximum frequency value, the HXT Clock Frequency Range Detector Interrupt Flag will set to 1.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::CDLOWB

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CDLOWB
</font><br><p> <font size="2">
Offset: 0x7C  Clock Frequency Range Detector Lower Boundary Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[9:0]</td><td>LOWERBD</td><td><div style="word-wrap: break-word;"><b>HXT Clock Frequency Range Detector Lower Boundary Value
</b><br>
The bits define the minimum value of frequency range detector window.
<br>
When HXT frequency lower than this minimum frequency value, the HXT Clock Frequency Range Detector Interrupt Flag will set to 1.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::PMUCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PMUCTL
</font><br><p> <font size="2">
Offset: 0x90  Power Manager Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2:0]</td><td>PDMSEL</td><td><div style="word-wrap: break-word;"><b>Power-down Mode Selection (Write Protect)
</b><br>
This is a protected register. Please refer to open lock sequence to program it.
<br>
These bits control chip power-down mode grade selection when CPU execute WFI/WFE instruction.
<br>
000 = Power-down mode is selected. (PD)
<br>
001 = Low leakage Power-down mode is selected (LLPD).
<br>
010 =Fast wake-up Power-down mode is selected (FWPD).
<br>
011 = Reserved.
<br>
100 = Standby Power-down mode 0 is selected (SPD0) (SRAM retention).
<br>
101 = Standby Power-down mode 1 is selected (SPD1).
<br>
110 = Deep Power-down mode is selected (DPD).
<br>
111 = Reserved.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[3]</td><td>DPDHOLDEN</td><td><div style="word-wrap: break-word;"><b>Deep-Power-Down Mode GPIO Hold Enable
</b><br>
0 = When GPIO enters deep power-down mode, all I/O status are tri-state.
<br>
1 = When GPIO enters deep power-down mode, all I/O status are hold to keep normal operating status.
<br>
    After chip was waked up from deep power-down mode, the I/O are still keep hold status until user set CLK_IOPDCTL[0]
<br>
    to release I/O hold status.
<br>
</div></td></tr><tr><td>
[8]</td><td>WKTMREN</td><td><div style="word-wrap: break-word;"><b>Wake-up Timer Enable (Write Protect)
</b><br>
This is a protected register. Please refer to open lock sequence to program it.
<br>
0 = Wake-up timer disable at DPD/SPD mode.
<br>
1 = Wake-up timer enabled at DPD/SPD mode.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[11:9]</td><td>WKTMRIS</td><td><div style="word-wrap: break-word;"><b>Wake-up Timer Time-out Interval Select (Write Protect)
</b><br>
This is a protected register. Please refer to open lock sequence to program it.
<br>
These bits control wake-up timer time-out interval when chip at DPD/SPD mode.
<br>
000 = Time-out interval is 128 OSC10K clocks (12.8 ms).
<br>
001 = Time-out interval is 256 OSC10K clocks (25.6 ms).
<br>
010 = Time-out interval is 512 OSC10K clocks (51.2 ms).
<br>
011 = Time-out interval is 1024 OSC10K clocks (102.4ms).
<br>
100 = Time-out interval is 4096 OSC10K clocks (409.6ms).
<br>
101 = Time-out interval is 8192 OSC10K clocks (819.2ms).
<br>
110 = Time-out interval is 16384 OSC10K clocks (1638.4ms).
<br>
111 = Time-out interval is 65536 OSC10K clocks (6553.6ms).
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[17:16]</td><td>WKPINEN</td><td><div style="word-wrap: break-word;"><b>Wake-up Pin Enable (Write Protect)
</b><br>
This is a protected register. Please refer to open lock sequence to program it.
<br>
00 = Wake-up pin disable at Deep Power-down mode.
<br>
01 = Wake-up pin rising edge enabled at Deep Power-down mode.
<br>
10 = Wake-up pin falling edge enabled at Deep Power-down mode.
<br>
11 = Wake-up pin both edge enabled at Deep Power-down mode.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[18]</td><td>ACMPSPWK</td><td><div style="word-wrap: break-word;"><b>ACMP Standby Power-down Mode Wake-up Enable (Write Protect)
</b><br>
This is a protected register. Please refer to open lock sequence to program it.
<br>
0 = ACMP wake-up disable at Standby Power-down mode.
<br>
1 = ACMP wake-up enabled at Standby Power-down mode.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[23]</td><td>RTCWKEN</td><td><div style="word-wrap: break-word;"><b>RTC Wake-up Enable (Write Protect)
</b><br>
This is a protected register. Please refer to open lock sequence to program it.
<br>
0 = RTC wake-up disable at Deep Power-down mode or Standby Power-down mode.
<br>
1 = RTC wake-up enabled at Deep Power-down mode or Standby Power-down mode.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::PMUSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PMUSTS
</font><br><p> <font size="2">
Offset: 0x94  Power Manager Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>PINWK</td><td><div style="word-wrap: break-word;"><b>Pin Wake-up Flag (Read Only)
</b><br>
This flag indicates that wake-up of chip from Deep Power-down mode was requested by a transition of the WAKEUP pin (GPC.0)
<br>
This flag is cleared when DPD mode is entered.
<br>
</div></td></tr><tr><td>
[1]</td><td>TMRWK</td><td><div style="word-wrap: break-word;"><b>Timer Wake-up Flag (Read Only)
</b><br>
This flag indicates that wake-up of chip from Deep Power-down mode (DPD) or Standby Power-down (SPD) mode was requested by wakeup timer time-out
<br>
This flag is cleared when DPD or SPD mode is entered.
<br>
</div></td></tr><tr><td>
[2]</td><td>RTCWK</td><td><div style="word-wrap: break-word;"><b>RTC Wake-up Flag (Read Only)
</b><br>
This flag indicates that wakeup of device from Deep Power-down mode (DPD) or Standby Power-down (SPD) mode was requested with a RTC alarm, tick time or tamper happened
<br>
This flag is cleared when DPD or SPD mode is entered.
<br>
</div></td></tr><tr><td>
[8]</td><td>GPAWK</td><td><div style="word-wrap: break-word;"><b>GPA Wake-up Flag (Read Only)
</b><br>
This flag indicates that wake-up of chip from Standby Power-down mode was requested by a transition of selected one GPA group pins
<br>
This flag is cleared when SPD mode is entered.
<br>
</div></td></tr><tr><td>
[9]</td><td>GPBWK</td><td><div style="word-wrap: break-word;"><b>GPB Wake-up Flag (Read Only)
</b><br>
This flag indicates that wake-up of chip from Standby Power-down mode was requested by a transition of selected one GPB group pins
<br>
This flag is cleared when SPD mode is entered.
<br>
</div></td></tr><tr><td>
[10]</td><td>GPCWK</td><td><div style="word-wrap: break-word;"><b>GPC Wake-up Flag (Read Only)
</b><br>
This flag indicates that wake-up of chip from Standby Power-down mode was requested by a transition of selected one GPC group pins
<br>
This flag is cleared when SPD mode is entered.
<br>
</div></td></tr><tr><td>
[11]</td><td>GPDWK</td><td><div style="word-wrap: break-word;"><b>GPD Wake-up Flag (Read Only)
</b><br>
This flag indicates that wake-up of chip from Standby Power-down mode was requested by a transition of selected one GPD group pins
<br>
This flag is cleared when SPD mode is entered.
<br>
</div></td></tr><tr><td>
[12]</td><td>LVRWK</td><td><div style="word-wrap: break-word;"><b>LVR Wake-up Flag (Read Only)
</b><br>
This flag indicates that wakeup of device from Standby Power-down mode was requested with a LVR happened
<br>
This flag is cleared when SPD mode is entered.
<br>
</div></td></tr><tr><td>
[13]</td><td>BODWK</td><td><div style="word-wrap: break-word;"><b>BOD Wake-up Flag (Read Only)
</b><br>
This flag indicates that wakeup of device from Standby Power-down mode (SPD) was requested with a BOD happened
<br>
This flag is cleared when SPD mode is entered.
<br>
</div></td></tr><tr><td>
[14]</td><td>ACMPWK</td><td><div style="word-wrap: break-word;"><b>ACMP Wake-up Flag (Read Only)
</b><br>
This flag indicates that wakeup of device from Standby Power-down mode (SPD) was requested with a ACMP transition
<br>
This flag is cleared when SPD mode is entered.
<br>
</div></td></tr><tr><td>
[31]</td><td>CLRWK</td><td><div style="word-wrap: break-word;"><b>Clear Wake-up Flag
</b><br>
0 = No clear.
<br>
1 = Clear all wake-up flag.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::LDOCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">LDOCTL
</font><br><p> <font size="2">
Offset: 0x98  LDO Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[18]</td><td>PDBIASEN</td><td><div style="word-wrap: break-word;"><b>Power-down Bias Enable Bit
</b><br>
0 = Reserved.
<br>
1 = Power-down bias enabled.
<br>
Note: This bit should set to 1 before chip enter power-down mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::SWKDBCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SWKDBCTL
</font><br><p> <font size="2">
Offset: 0x9C  Standby Power-down Wake-up De-bounce Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>SWKDBCLKSEL</td><td><div style="word-wrap: break-word;"><b>Standby Power-down Wake-up De-bounce Sampling Cycle Selection
</b><br>
0000 = Sample wake-up input once per 1 clocks.
<br>
0001 = Sample wake-up input once per 2 clocks.
<br>
0010 = Sample wake-up input once per 4 clocks.
<br>
0011 = Sample wake-up input once per 8 clocks.
<br>
0100 = Sample wake-up input once per 16 clocks.
<br>
0101 = Sample wake-up input once per 32 clocks.
<br>
0110 = Sample wake-up input once per 64 clocks.
<br>
0111 = Sample wake-up input once per 128 clocks.
<br>
1000 = Sample wake-up input once per 256 clocks.
<br>
1001 = Sample wake-up input once per 2*256 clocks.
<br>
1010 = Sample wake-up input once per 4*256 clocks.
<br>
1011 = Sample wake-up input once per 8*256 clocks.
<br>
1100 = Sample wake-up input once per 16*256 clocks.
<br>
1101 = Sample wake-up input once per 32*256 clocks.
<br>
1110 = Sample wake-up input once per 64*256 clocks.
<br>
1111 = Sample wake-up input once per 128*256 clocks.
<br>
Note: De-bounce counter clock source is the 10 kHz internal low speed RC oscillator (LIRC).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::PASWKCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PASWKCTL
</font><br><p> <font size="2">
Offset: 0xA0  GPA Standby Power-down Wake-up Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>WKEN</td><td><div style="word-wrap: break-word;"><b>Standby Power-down Pin Wake-up Enable Bit
</b><br>
0 = GPA group pin wake-up function disabled.
<br>
1 = GPA group pin wake-up function enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>PRWKEN</td><td><div style="word-wrap: break-word;"><b>Pin Rising Edge Wake-up Enable Bit
</b><br>
0 = GPA group pin rising edge wake-up function disabled.
<br>
1 = GPA group pin rising edge wake-up function enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>PFWKEN</td><td><div style="word-wrap: break-word;"><b>Pin Falling Edge Wake-up Enable Bit
</b><br>
0 = GPA group pin falling edge wake-up function disabled.
<br>
1 = GPA group pin falling edge wake-up function enabled.
<br>
</div></td></tr><tr><td>
[7:4]</td><td>WKPSEL</td><td><div style="word-wrap: break-word;"><b>GPA Standby Power-down Wake-up Pin Select
</b><br>
0000 = GPA.0 wake-up function enabled.
<br>
0001 = GPA.1 wake-up function enabled.
<br>
0010 = GPA.2 wake-up function enabled.
<br>
0011 = GPA.3 wake-up function enabled.
<br>
0100 = GPA.4 wake-up function enabled.
<br>
0101 = GPA.5 wake-up function enabled.
<br>
0110 = GPA.6 wake-up function enabled.
<br>
0111 = GPA.7 wake-up function enabled.
<br>
1000 = GPA.8 wake-up function enabled.
<br>
1001 = GPA.9 wake-up function enabled.
<br>
1010 = GPA.10 wake-up function enabled.
<br>
1011 = GPA.11 wake-up function enabled.
<br>
1100 = GPA.12 wake-up function enabled.
<br>
1101 = GPA.13 wake-up function enabled.
<br>
1110 = GPA.14 wake-up function enabled.
<br>
1111 = GPA.15 wake-up function enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>DBEN</td><td><div style="word-wrap: break-word;"><b>GPA Input Signal De-bounce Enable Bit
</b><br>
The DBEN bit is used to enable the de-bounce function for each corresponding IO
<br>
If the input signal pulse width cannot be sampled by continuous two de-bounce sample cycle, the input signal transition is seen as the signal bounce and will not trigger the wake-up
<br>
The de-bounce clock source is the 10 kHz internal low speed RC oscillator.
<br>
0 = Standby power-down wake-up pin De-bounce function disable.
<br>
1 = Standby power-down wake-up pin De-bounce function enable.
<br>
The de-bounce function is valid only for edge triggered.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::PBSWKCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PBSWKCTL
</font><br><p> <font size="2">
Offset: 0xA4  GPB Standby Power-down Wake-up Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>WKEN</td><td><div style="word-wrap: break-word;"><b>Standby Power-down Pin Wake-up Enable Bit
</b><br>
0 = GPB group pin wake-up function disabled.
<br>
1 = GPB group pin wake-up function enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>PRWKEN</td><td><div style="word-wrap: break-word;"><b>Pin Rising Edge Wake-up Enable Bit
</b><br>
0 = GPB group pin rising edge wake-up function disabled.
<br>
1 = GPB group pin rising edge wake-up function enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>PFWKEN</td><td><div style="word-wrap: break-word;"><b>Pin Falling Edge Wake-up Enable Bit
</b><br>
0 = GPB group pin falling edge wake-up function disabled.
<br>
1 = GPB group pin falling edge wake-up function enabled.
<br>
</div></td></tr><tr><td>
[7:4]</td><td>WKPSEL</td><td><div style="word-wrap: break-word;"><b>GPB Standby Power-down Wake-up Pin Select
</b><br>
0000 = GPB.0 wake-up function enabled.
<br>
0001 = GPB.1 wake-up function enabled.
<br>
0010 = GPB.2 wake-up function enabled.
<br>
0011 = GPB.3 wake-up function enabled.
<br>
0100 = GPB.4 wake-up function enabled.
<br>
0101 = GPB.5 wake-up function enabled.
<br>
0110 = GPB.6 wake-up function enabled.
<br>
0111 = GPB.7 wake-up function enabled.
<br>
1000 = GPB.8 wake-up function enabled.
<br>
1001 = GPB.9 wake-up function enabled.
<br>
1010 = GPB.10 wake-up function enabled.
<br>
1011 = GPB.11 wake-up function enabled.
<br>
1100 = GPB.12 wake-up function enabled.
<br>
1101 = GPB.13 wake-up function enabled.
<br>
1110 = GPB.14 wake-up function enabled.
<br>
1111 = GPB.15 wake-up function enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>DBEN</td><td><div style="word-wrap: break-word;"><b>GPB Input Signal De-bounce Enable Bit
</b><br>
The DBEN bit is used to enable the de-bounce function for each corresponding IO
<br>
If the input signal pulse width cannot be sampled by continuous two de-bounce sample cycle, the input signal transition is seen as the signal bounce and will not trigger the wake-up
<br>
The de-bounce clock source is the 10 kHz internal low speed RC oscillator.
<br>
0 = Standby power-down wake-up pin De-bounce function disable.
<br>
1 = Standby power-down wake-up pin De-bounce function enable.
<br>
The de-bounce function is valid only for edge triggered.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::PCSWKCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PCSWKCTL
</font><br><p> <font size="2">
Offset: 0xA8  GPC Standby Power-down Wake-up Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>WKEN</td><td><div style="word-wrap: break-word;"><b>Standby Power-down Pin Wake-up Enable Bit
</b><br>
0 = GPC group pin wake-up function disabled.
<br>
1 = GPC group pin wake-up function enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>PRWKEN</td><td><div style="word-wrap: break-word;"><b>Pin Rising Edge Wake-up Enable Bit
</b><br>
0 = GPC group pin rising edge wake-up function disabled.
<br>
1 = GPC group pin rising edge wake-up function enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>PFWKEN</td><td><div style="word-wrap: break-word;"><b>Pin Falling Edge Wake-up Enable Bit
</b><br>
0 = GPC group pin falling edge wake-up function disabled.
<br>
1 = GPC group pin falling edge wake-up function enabled.
<br>
</div></td></tr><tr><td>
[7:4]</td><td>WKPSEL</td><td><div style="word-wrap: break-word;"><b>GPC Standby Power-down Wake-up Pin Select
</b><br>
0000 = GPC.0 wake-up function enabled.
<br>
0001 = GPC.1 wake-up function enabled.
<br>
0010 = GPC.2 wake-up function enabled.
<br>
0011 = GPC.3 wake-up function enabled.
<br>
0100 = GPC.4 wake-up function enabled.
<br>
0101 = GPC.5 wake-up function enabled.
<br>
0110 = GPC.6 wake-up function enabled.
<br>
0111 = GPC.7 wake-up function enabled.
<br>
1000 = GPC.8 wake-up function enabled.
<br>
1001 = GPC.9 wake-up function enabled.
<br>
1010 = GPC.10 wake-up function enabled.
<br>
1011 = GPC.11 wake-up function enabled.
<br>
1100 = GPC.12 wake-up function enabled.
<br>
1101 = GPC.13 wake-up function enabled.
<br>
1110 = GPC.14 wake-up function enabled.
<br>
1111 = GPC.15 wake-up function enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>DBEN</td><td><div style="word-wrap: break-word;"><b>GPC Input Signal De-bounce Enable Bit
</b><br>
The DBEN bit is used to enable the de-bounce function for each corresponding IO
<br>
If the input signal pulse width cannot be sampled by continuous two de-bounce sample cycle, the input signal transition is seen as the signal bounce and will not trigger the wake-up
<br>
The de-bounce clock source is the 10 kHz internal low speed RC oscillator.
<br>
0 = Standby power-down wake-up pin De-bounce function disable.
<br>
1 = Standby power-down wake-up pin De-bounce function enable.
<br>
The de-bounce function is valid only for edge triggered.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::PDSWKCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PDSWKCTL
</font><br><p> <font size="2">
Offset: 0xAC  GPD Standby Power-down Wake-up Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>WKEN</td><td><div style="word-wrap: break-word;"><b>Standby Power-down Pin Wake-up Enable Bit
</b><br>
0 = GPD group pin wake-up function disabled.
<br>
1 = GPD group pin wake-up function enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>PRWKEN</td><td><div style="word-wrap: break-word;"><b>Pin Rising Edge Wake-up Enable Bit
</b><br>
0 = GPD group pin rising edge wake-up function disabled.
<br>
1 = GPD group pin rising edge wake-up function enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>PFWKEN</td><td><div style="word-wrap: break-word;"><b>Pin Falling Edge Wake-up Enable Bit
</b><br>
0 = GPD group pin falling edge wake-up function disabled.
<br>
1 = GPD group pin falling edge wake-up function enabled.
<br>
</div></td></tr><tr><td>
[7:4]</td><td>WKPSEL</td><td><div style="word-wrap: break-word;"><b>GPD Standby Power-down Wake-up Pin Select
</b><br>
0000 = GPD.0 wake-up function enabled.
<br>
0001 = GPD.1 wake-up function enabled.
<br>
0010 = GPD.2 wake-up function enabled.
<br>
0011 = GPD.3 wake-up function enabled.
<br>
0100 = GPD.4 wake-up function enabled.
<br>
0101 = GPD.5 wake-up function enabled.
<br>
0110 = GPD.6 wake-up function enabled.
<br>
0111 = GPD.7 wake-up function enabled.
<br>
1000 = GPD.8 wake-up function enabled.
<br>
1001 = GPD.9 wake-up function enabled.
<br>
1010 = GPD.10 wake-up function enabled.
<br>
1011 = GPD.11 wake-up function enabled.
<br>
1100 = GPD.12 wake-up function enabled.
<br>
1101 = GPD.13 wake-up function enabled.
<br>
1110 = GPD.14 wake-up function enabled.
<br>
1111 = GPD.15 wake-up function enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>DBEN</td><td><div style="word-wrap: break-word;"><b>GPD Input Signal De-bounce Enable Bit
</b><br>
The DBEN bit is used to enable the de-bounce function for each corresponding IO
<br>
If the input signal pulse width cannot be sampled by continuous two de-bounce sample cycle, the input signal transition is seen as the signal bounce and will not trigger the wake-up
<br>
The de-bounce clock source is the 10 kHz internal low speed RC oscillator.
<br>
0 = Standby power-down wake-up pin De-bounce function disable.
<br>
1 = Standby power-down wake-up pin De-bounce function enable.
<br>
The de-bounce function is valid only for edge triggered.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CLK_T::IOPDCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">IOPDCTL
</font><br><p> <font size="2">
Offset: 0xB0  GPIO Standby Power-down Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>IOHR</td><td><div style="word-wrap: break-word;"><b>GPIO Hold Release
</b><br>
When GPIO enter standby power-down mode, all I/O status are hold to keep normal operating status
<br>
After chip was waked up from standby power-down mode, the I/O are still keep hold status until user set this bit to release I/O hold status.
<br>
This bit is auto cleared by hardware.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t PWRCTL;                /*!< [0x0000] System Power-down Control Register                               */
    __IO uint32_t AHBCLK;                /*!< [0x0004] AHB Devices Clock Enable Control Register                        */
    __IO uint32_t APBCLK0;               /*!< [0x0008] APB Devices Clock Enable Control Register 0                      */
    __IO uint32_t APBCLK1;               /*!< [0x000c] APB Devices Clock Enable Control Register 1                      */
    __IO uint32_t CLKSEL0;               /*!< [0x0010] Clock Source Select Control Register 0                           */
    __IO uint32_t CLKSEL1;               /*!< [0x0014] Clock Source Select Control Register 1                           */
    __IO uint32_t CLKSEL2;               /*!< [0x0018] Clock Source Select Control Register 2                           */
    __IO uint32_t CLKSEL3;               /*!< [0x001c] Clock Source Select Control Register 3                           */
    __IO uint32_t CLKDIV0;               /*!< [0x0020] Clock Divider Number Register 0                                  */
    __IO uint32_t CLKDIV1;               /*!< [0x0024] Clock Divider Number Register 1                                  */
    __IO uint32_t CLKDIV2;               /*!< [0x0028] Clock Divider Number Register 2                                  */
    __IO uint32_t CLKDIV3;               /*!< [0x002c] Clock Divider Number Register 3                                  */
    __IO uint32_t CLKDIV4;               /*!< [0x0030] Clock Divider Number Register 4                                  */
    __IO uint32_t PCLKDIV;               /*!< [0x0034] APB Clock Divider Register                                       */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE1[2];
    /** @endcond */
    __IO uint32_t PLLCTL;                /*!< [0x0040] PLL Control Register                                             */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE2[3];
    /** @endcond */
    __I  uint32_t STATUS;                /*!< [0x0050] Clock Status Monitor Register                                    */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE3[3];
    /** @endcond */
    __IO uint32_t CLKOCTL;               /*!< [0x0060] Clock Output Control Register                                    */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE4[3];
    /** @endcond */
    __IO uint32_t CLKDCTL;               /*!< [0x0070] Clock Fail Detector Control Register                             */
    __IO uint32_t CLKDSTS;               /*!< [0x0074] Clock Fail Detector Status Register                              */
    __IO uint32_t CDUPB;                 /*!< [0x0078] Clock Frequency Range Detector Upper Boundary Register           */
    __IO uint32_t CDLOWB;                /*!< [0x007c] Clock Frequency Range Detector Lower Boundary Register           */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE5[4];
    /** @endcond */
    __IO uint32_t PMUCTL;                /*!< [0x0090] Power Manager Control Register                                   */
    __IO uint32_t PMUSTS;                /*!< [0x0094] Power Manager Status Register                                    */
    __IO uint32_t LDOCTL;                /*!< [0x0098] LDO Control Register                                             */
    __IO uint32_t SWKDBCTL;              /*!< [0x009c] Standby Power-down Wake-up De-bounce Control Register            */
    __IO uint32_t PASWKCTL;              /*!< [0x00a0] GPA Standby Power-down Wake-up Control Register                  */
    __IO uint32_t PBSWKCTL;              /*!< [0x00a4] GPB Standby Power-down Wake-up Control Register                  */
    __IO uint32_t PCSWKCTL;              /*!< [0x00a8] GPC Standby Power-down Wake-up Control Register                  */
    __IO uint32_t PDSWKCTL;              /*!< [0x00ac] GPD Standby Power-down Wake-up Control Register                  */
    __IO uint32_t IOPDCTL;               /*!< [0x00b0] GPIO Standby Power-down Control Register                         */

} CLK_T;

/**
    @addtogroup CLK_CONST CLK Bit Field Definition
    Constant Definitions for CLK Controller
@{ */

#define CLK_PWRCTL_HXTEN_Pos             (0)                                               /*!< CLK_T::PWRCTL: HXTEN Position          */
#define CLK_PWRCTL_HXTEN_Msk             (0x1ul << CLK_PWRCTL_HXTEN_Pos)                   /*!< CLK_T::PWRCTL: HXTEN Mask              */

#define CLK_PWRCTL_LXTEN_Pos             (1)                                               /*!< CLK_T::PWRCTL: LXTEN Position          */
#define CLK_PWRCTL_LXTEN_Msk             (0x1ul << CLK_PWRCTL_LXTEN_Pos)                   /*!< CLK_T::PWRCTL: LXTEN Mask              */

#define CLK_PWRCTL_HIRCEN_Pos            (2)                                               /*!< CLK_T::PWRCTL: HIRCEN Position         */
#define CLK_PWRCTL_HIRCEN_Msk            (0x1ul << CLK_PWRCTL_HIRCEN_Pos)                  /*!< CLK_T::PWRCTL: HIRCEN Mask             */

#define CLK_PWRCTL_LIRCEN_Pos            (3)                                               /*!< CLK_T::PWRCTL: LIRCEN Position         */
#define CLK_PWRCTL_LIRCEN_Msk            (0x1ul << CLK_PWRCTL_LIRCEN_Pos)                  /*!< CLK_T::PWRCTL: LIRCEN Mask             */

#define CLK_PWRCTL_PDWKDLY_Pos           (4)                                               /*!< CLK_T::PWRCTL: PDWKDLY Position        */
#define CLK_PWRCTL_PDWKDLY_Msk           (0x1ul << CLK_PWRCTL_PDWKDLY_Pos)                 /*!< CLK_T::PWRCTL: PDWKDLY Mask            */

#define CLK_PWRCTL_PDWKIEN_Pos           (5)                                               /*!< CLK_T::PWRCTL: PDWKIEN Position        */
#define CLK_PWRCTL_PDWKIEN_Msk           (0x1ul << CLK_PWRCTL_PDWKIEN_Pos)                 /*!< CLK_T::PWRCTL: PDWKIEN Mask            */

#define CLK_PWRCTL_PDWKIF_Pos            (6)                                               /*!< CLK_T::PWRCTL: PDWKIF Position         */
#define CLK_PWRCTL_PDWKIF_Msk            (0x1ul << CLK_PWRCTL_PDWKIF_Pos)                  /*!< CLK_T::PWRCTL: PDWKIF Mask             */

#define CLK_PWRCTL_PDEN_Pos              (7)                                               /*!< CLK_T::PWRCTL: PDEN Position           */
#define CLK_PWRCTL_PDEN_Msk              (0x1ul << CLK_PWRCTL_PDEN_Pos)                    /*!< CLK_T::PWRCTL: PDEN Mask               */

#define CLK_PWRCTL_HXTGAIN_Pos           (10)                                              /*!< CLK_T::PWRCTL: HXTGAIN Position        */
#define CLK_PWRCTL_HXTGAIN_Msk           (0x3ul << CLK_PWRCTL_HXTGAIN_Pos)                 /*!< CLK_T::PWRCTL: HXTGAIN Mask            */

#define CLK_PWRCTL_HXTSELTYP_Pos         (12)                                              /*!< CLK_T::PWRCTL: HXTSELTYP Position      */
#define CLK_PWRCTL_HXTSELTYP_Msk         (0x1ul << CLK_PWRCTL_HXTSELTYP_Pos)               /*!< CLK_T::PWRCTL: HXTSELTYP Mask          */

#define CLK_PWRCTL_HXTTBEN_Pos           (13)                                              /*!< CLK_T::PWRCTL: HXTTBEN Position        */
#define CLK_PWRCTL_HXTTBEN_Msk           (0x1ul << CLK_PWRCTL_HXTTBEN_Pos)                 /*!< CLK_T::PWRCTL: HXTTBEN Mask            */

#define CLK_PWRCTL_HIRCSTBS_Pos          (16)                                              /*!< CLK_T::PWRCTL: HIRCSTBS Position       */
#define CLK_PWRCTL_HIRCSTBS_Msk          (0x3ul << CLK_PWRCTL_HIRCSTBS_Pos)                /*!< CLK_T::PWRCTL: HIRCSTBS Mask           */

#define CLK_PWRCTL_HIRC48MEN_Pos         (18)                                              /*!< CLK_T::PWRCTL: HIRC48MEN Position      */
#define CLK_PWRCTL_HIRC48MEN_Msk         (0x1ul << CLK_PWRCTL_HIRC48MEN_Pos)               /*!< CLK_T::PWRCTL: HIRC48MEN Mask          */

#define CLK_AHBCLK_PDMACKEN_Pos          (1)                                               /*!< CLK_T::AHBCLK: PDMACKEN Position       */
#define CLK_AHBCLK_PDMACKEN_Msk          (0x1ul << CLK_AHBCLK_PDMACKEN_Pos)                /*!< CLK_T::AHBCLK: PDMACKEN Mask           */

#define CLK_AHBCLK_ISPCKEN_Pos           (2)                                               /*!< CLK_T::AHBCLK: ISPCKEN Position        */
#define CLK_AHBCLK_ISPCKEN_Msk           (0x1ul << CLK_AHBCLK_ISPCKEN_Pos)                 /*!< CLK_T::AHBCLK: ISPCKEN Mask            */

#define CLK_AHBCLK_EBICKEN_Pos           (3)                                               /*!< CLK_T::AHBCLK: EBICKEN Position        */
#define CLK_AHBCLK_EBICKEN_Msk           (0x1ul << CLK_AHBCLK_EBICKEN_Pos)                 /*!< CLK_T::AHBCLK: EBICKEN Mask            */

#define CLK_AHBCLK_EMACCKEN_Pos          (5)                                               /*!< CLK_T::AHBCLK: EMACCKEN Position       */
#define CLK_AHBCLK_EMACCKEN_Msk          (0x1ul << CLK_AHBCLK_EMACCKEN_Pos)                /*!< CLK_T::AHBCLK: EMACCKEN Mask           */

#define CLK_AHBCLK_SDH0CKEN_Pos          (6)                                               /*!< CLK_T::AHBCLK: SDH0CKEN Position       */
#define CLK_AHBCLK_SDH0CKEN_Msk          (0x1ul << CLK_AHBCLK_SDH0CKEN_Pos)                /*!< CLK_T::AHBCLK: SDH0CKEN Mask           */

#define CLK_AHBCLK_CRCCKEN_Pos           (7)                                               /*!< CLK_T::AHBCLK: CRCCKEN Position        */
#define CLK_AHBCLK_CRCCKEN_Msk           (0x1ul << CLK_AHBCLK_CRCCKEN_Pos)                 /*!< CLK_T::AHBCLK: CRCCKEN Mask            */

#define CLK_AHBCLK_CCAPCKEN_Pos          (8)                                               /*!< CLK_T::AHBCLK: CCAPCKEN Position       */
#define CLK_AHBCLK_CCAPCKEN_Msk          (0x1ul << CLK_AHBCLK_CCAPCKEN_Pos)                /*!< CLK_T::AHBCLK: CCAPCKEN Mask           */

#define CLK_AHBCLK_SENCKEN_Pos           (9)                                               /*!< CLK_T::AHBCLK: SENCKEN Position        */
#define CLK_AHBCLK_SENCKEN_Msk           (0x1ul << CLK_AHBCLK_SENCKEN_Pos)                 /*!< CLK_T::AHBCLK: SENCKEN Mask            */

#define CLK_AHBCLK_HSUSBDCKEN_Pos        (10)                                              /*!< CLK_T::AHBCLK: HSUSBDCKEN Position     */
#define CLK_AHBCLK_HSUSBDCKEN_Msk        (0x1ul << CLK_AHBCLK_HSUSBDCKEN_Pos)              /*!< CLK_T::AHBCLK: HSUSBDCKEN Mask         */

#define CLK_AHBCLK_CRPTCKEN_Pos          (12)                                              /*!< CLK_T::AHBCLK: CRPTCKEN Position       */
#define CLK_AHBCLK_CRPTCKEN_Msk          (0x1ul << CLK_AHBCLK_CRPTCKEN_Pos)                /*!< CLK_T::AHBCLK: CRPTCKEN Mask           */

#define CLK_AHBCLK_SPIMCKEN_Pos          (14)                                              /*!< CLK_T::AHBCLK: SPIMCKEN Position       */
#define CLK_AHBCLK_SPIMCKEN_Msk          (0x1ul << CLK_AHBCLK_SPIMCKEN_Pos)                /*!< CLK_T::AHBCLK: SPIMCKEN Mask           */

#define CLK_AHBCLK_FMCIDLE_Pos           (15)                                              /*!< CLK_T::AHBCLK: FMCIDLE Position        */
#define CLK_AHBCLK_FMCIDLE_Msk           (0x1ul << CLK_AHBCLK_FMCIDLE_Pos)                 /*!< CLK_T::AHBCLK: FMCIDLE Mask            */

#define CLK_AHBCLK_USBHCKEN_Pos          (16)                                              /*!< CLK_T::AHBCLK: USBHCKEN Position       */
#define CLK_AHBCLK_USBHCKEN_Msk          (0x1ul << CLK_AHBCLK_USBHCKEN_Pos)                /*!< CLK_T::AHBCLK: USBHCKEN Mask           */

#define CLK_AHBCLK_SDH1CKEN_Pos          (17)                                              /*!< CLK_T::AHBCLK: SDH1CKEN Position       */
#define CLK_AHBCLK_SDH1CKEN_Msk          (0x1ul << CLK_AHBCLK_SDH1CKEN_Pos)                /*!< CLK_T::AHBCLK: SDH1CKEN Mask           */

#define CLK_APBCLK0_WDTCKEN_Pos          (0)                                               /*!< CLK_T::APBCLK0: WDTCKEN Position       */
#define CLK_APBCLK0_WDTCKEN_Msk          (0x1ul << CLK_APBCLK0_WDTCKEN_Pos)                /*!< CLK_T::APBCLK0: WDTCKEN Mask           */

#define CLK_APBCLK0_RTCCKEN_Pos          (1)                                               /*!< CLK_T::APBCLK0: RTCCKEN Position       */
#define CLK_APBCLK0_RTCCKEN_Msk          (0x1ul << CLK_APBCLK0_RTCCKEN_Pos)                /*!< CLK_T::APBCLK0: RTCCKEN Mask           */

#define CLK_APBCLK0_TMR0CKEN_Pos         (2)                                               /*!< CLK_T::APBCLK0: TMR0CKEN Position      */
#define CLK_APBCLK0_TMR0CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR0CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR0CKEN Mask          */

#define CLK_APBCLK0_TMR1CKEN_Pos         (3)                                               /*!< CLK_T::APBCLK0: TMR1CKEN Position      */
#define CLK_APBCLK0_TMR1CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR1CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR1CKEN Mask          */

#define CLK_APBCLK0_TMR2CKEN_Pos         (4)                                               /*!< CLK_T::APBCLK0: TMR2CKEN Position      */
#define CLK_APBCLK0_TMR2CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR2CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR2CKEN Mask          */

#define CLK_APBCLK0_TMR3CKEN_Pos         (5)                                               /*!< CLK_T::APBCLK0: TMR3CKEN Position      */
#define CLK_APBCLK0_TMR3CKEN_Msk         (0x1ul << CLK_APBCLK0_TMR3CKEN_Pos)               /*!< CLK_T::APBCLK0: TMR3CKEN Mask          */

#define CLK_APBCLK0_CLKOCKEN_Pos         (6)                                               /*!< CLK_T::APBCLK0: CLKOCKEN Position      */
#define CLK_APBCLK0_CLKOCKEN_Msk         (0x1ul << CLK_APBCLK0_CLKOCKEN_Pos)               /*!< CLK_T::APBCLK0: CLKOCKEN Mask          */

#define CLK_APBCLK0_ACMP01CKEN_Pos       (7)                                               /*!< CLK_T::APBCLK0: ACMP01CKEN Position    */
#define CLK_APBCLK0_ACMP01CKEN_Msk       (0x1ul << CLK_APBCLK0_ACMP01CKEN_Pos)             /*!< CLK_T::APBCLK0: ACMP01CKEN Mask        */

#define CLK_APBCLK0_I2C0CKEN_Pos         (8)                                               /*!< CLK_T::APBCLK0: I2C0CKEN Position      */
#define CLK_APBCLK0_I2C0CKEN_Msk         (0x1ul << CLK_APBCLK0_I2C0CKEN_Pos)               /*!< CLK_T::APBCLK0: I2C0CKEN Mask          */

#define CLK_APBCLK0_I2C1CKEN_Pos         (9)                                               /*!< CLK_T::APBCLK0: I2C1CKEN Position      */
#define CLK_APBCLK0_I2C1CKEN_Msk         (0x1ul << CLK_APBCLK0_I2C1CKEN_Pos)               /*!< CLK_T::APBCLK0: I2C1CKEN Mask          */

#define CLK_APBCLK0_I2C2CKEN_Pos         (10)                                              /*!< CLK_T::APBCLK0: I2C2CKEN Position      */
#define CLK_APBCLK0_I2C2CKEN_Msk         (0x1ul << CLK_APBCLK0_I2C2CKEN_Pos)               /*!< CLK_T::APBCLK0: I2C2CKEN Mask          */

#define CLK_APBCLK0_QSPI0CKEN_Pos        (12)                                              /*!< CLK_T::APBCLK0: QSPI0CKEN Position     */
#define CLK_APBCLK0_QSPI0CKEN_Msk        (0x1ul << CLK_APBCLK0_QSPI0CKEN_Pos)              /*!< CLK_T::APBCLK0: QSPI0CKEN Mask         */

#define CLK_APBCLK0_SPI0CKEN_Pos         (13)                                              /*!< CLK_T::APBCLK0: SPI0CKEN Position      */
#define CLK_APBCLK0_SPI0CKEN_Msk         (0x1ul << CLK_APBCLK0_SPI0CKEN_Pos)               /*!< CLK_T::APBCLK0: SPI0CKEN Mask          */

#define CLK_APBCLK0_SPI1CKEN_Pos         (14)                                              /*!< CLK_T::APBCLK0: SPI1CKEN Position      */
#define CLK_APBCLK0_SPI1CKEN_Msk         (0x1ul << CLK_APBCLK0_SPI1CKEN_Pos)               /*!< CLK_T::APBCLK0: SPI1CKEN Mask          */

#define CLK_APBCLK0_SPI2CKEN_Pos         (15)                                              /*!< CLK_T::APBCLK0: SPI2CKEN Position      */
#define CLK_APBCLK0_SPI2CKEN_Msk         (0x1ul << CLK_APBCLK0_SPI2CKEN_Pos)               /*!< CLK_T::APBCLK0: SPI2CKEN Mask          */

#define CLK_APBCLK0_UART0CKEN_Pos        (16)                                              /*!< CLK_T::APBCLK0: UART0CKEN Position     */
#define CLK_APBCLK0_UART0CKEN_Msk        (0x1ul << CLK_APBCLK0_UART0CKEN_Pos)              /*!< CLK_T::APBCLK0: UART0CKEN Mask         */

#define CLK_APBCLK0_UART1CKEN_Pos        (17)                                              /*!< CLK_T::APBCLK0: UART1CKEN Position     */
#define CLK_APBCLK0_UART1CKEN_Msk        (0x1ul << CLK_APBCLK0_UART1CKEN_Pos)              /*!< CLK_T::APBCLK0: UART1CKEN Mask         */

#define CLK_APBCLK0_UART2CKEN_Pos        (18)                                              /*!< CLK_T::APBCLK0: UART2CKEN Position     */
#define CLK_APBCLK0_UART2CKEN_Msk        (0x1ul << CLK_APBCLK0_UART2CKEN_Pos)              /*!< CLK_T::APBCLK0: UART2CKEN Mask         */

#define CLK_APBCLK0_UART3CKEN_Pos        (19)                                              /*!< CLK_T::APBCLK0: UART3CKEN Position     */
#define CLK_APBCLK0_UART3CKEN_Msk        (0x1ul << CLK_APBCLK0_UART3CKEN_Pos)              /*!< CLK_T::APBCLK0: UART3CKEN Mask         */

#define CLK_APBCLK0_UART4CKEN_Pos        (20)                                              /*!< CLK_T::APBCLK0: UART4CKEN Position     */
#define CLK_APBCLK0_UART4CKEN_Msk        (0x1ul << CLK_APBCLK0_UART4CKEN_Pos)              /*!< CLK_T::APBCLK0: UART4CKEN Mask         */

#define CLK_APBCLK0_UART5CKEN_Pos        (21)                                              /*!< CLK_T::APBCLK0: UART5CKEN Position     */
#define CLK_APBCLK0_UART5CKEN_Msk        (0x1ul << CLK_APBCLK0_UART5CKEN_Pos)              /*!< CLK_T::APBCLK0: UART5CKEN Mask         */

#define CLK_APBCLK0_UART6CKEN_Pos        (22)                                              /*!< CLK_T::APBCLK0: UART6CKEN Position     */
#define CLK_APBCLK0_UART6CKEN_Msk        (0x1ul << CLK_APBCLK0_UART6CKEN_Pos)              /*!< CLK_T::APBCLK0: UART6CKEN Mask         */

#define CLK_APBCLK0_UART7CKEN_Pos        (23)                                              /*!< CLK_T::APBCLK0: UART7CKEN Position     */
#define CLK_APBCLK0_UART7CKEN_Msk        (0x1ul << CLK_APBCLK0_UART7CKEN_Pos)              /*!< CLK_T::APBCLK0: UART7CKEN Mask         */

#define CLK_APBCLK0_CAN0CKEN_Pos         (24)                                              /*!< CLK_T::APBCLK0: CAN0CKEN Position      */
#define CLK_APBCLK0_CAN0CKEN_Msk         (0x1ul << CLK_APBCLK0_CAN0CKEN_Pos)               /*!< CLK_T::APBCLK0: CAN0CKEN Mask          */

#define CLK_APBCLK0_CAN1CKEN_Pos         (25)                                              /*!< CLK_T::APBCLK0: CAN1CKEN Position      */
#define CLK_APBCLK0_CAN1CKEN_Msk         (0x1ul << CLK_APBCLK0_CAN1CKEN_Pos)               /*!< CLK_T::APBCLK0: CAN1CKEN Mask          */

#define CLK_APBCLK0_OTGCKEN_Pos          (26)                                              /*!< CLK_T::APBCLK0: OTGCKEN Position       */
#define CLK_APBCLK0_OTGCKEN_Msk          (0x1ul << CLK_APBCLK0_OTGCKEN_Pos)                /*!< CLK_T::APBCLK0: OTGCKEN Mask           */

#define CLK_APBCLK0_USBDCKEN_Pos         (27)                                              /*!< CLK_T::APBCLK0: USBDCKEN Position      */
#define CLK_APBCLK0_USBDCKEN_Msk         (0x1ul << CLK_APBCLK0_USBDCKEN_Pos)               /*!< CLK_T::APBCLK0: USBDCKEN Mask          */

#define CLK_APBCLK0_EADCCKEN_Pos         (28)                                              /*!< CLK_T::APBCLK0: EADCCKEN Position      */
#define CLK_APBCLK0_EADCCKEN_Msk         (0x1ul << CLK_APBCLK0_EADCCKEN_Pos)               /*!< CLK_T::APBCLK0: EADCCKEN Mask          */

#define CLK_APBCLK0_I2S0CKEN_Pos         (29)                                              /*!< CLK_T::APBCLK0: I2S0CKEN Position      */
#define CLK_APBCLK0_I2S0CKEN_Msk         (0x1ul << CLK_APBCLK0_I2S0CKEN_Pos)               /*!< CLK_T::APBCLK0: I2S0CKEN Mask          */

#define CLK_APBCLK0_HSOTGCKEN_Pos        (30)                                              /*!< CLK_T::APBCLK0: HSOTGCKEN Position     */
#define CLK_APBCLK0_HSOTGCKEN_Msk        (0x1ul << CLK_APBCLK0_HSOTGCKEN_Pos)              /*!< CLK_T::APBCLK0: HSOTGCKEN Mask         */

#define CLK_APBCLK1_SC0CKEN_Pos          (0)                                               /*!< CLK_T::APBCLK1: SC0CKEN Position       */
#define CLK_APBCLK1_SC0CKEN_Msk          (0x1ul << CLK_APBCLK1_SC0CKEN_Pos)                /*!< CLK_T::APBCLK1: SC0CKEN Mask           */

#define CLK_APBCLK1_SC1CKEN_Pos          (1)                                               /*!< CLK_T::APBCLK1: SC1CKEN Position       */
#define CLK_APBCLK1_SC1CKEN_Msk          (0x1ul << CLK_APBCLK1_SC1CKEN_Pos)                /*!< CLK_T::APBCLK1: SC1CKEN Mask           */

#define CLK_APBCLK1_SC2CKEN_Pos          (2)                                               /*!< CLK_T::APBCLK1: SC2CKEN Position       */
#define CLK_APBCLK1_SC2CKEN_Msk          (0x1ul << CLK_APBCLK1_SC2CKEN_Pos)                /*!< CLK_T::APBCLK1: SC2CKEN Mask           */

#define CLK_APBCLK1_QSPI1CKEN_Pos        (4)                                               /*!< CLK_T::APBCLK1: QSPI1CKEN Position     */
#define CLK_APBCLK1_QSPI1CKEN_Msk        (0x1ul << CLK_APBCLK1_QSPI1CKEN_Pos)              /*!< CLK_T::APBCLK1: QSPI1CKEN Mask         */

#define CLK_APBCLK1_SPI3CKEN_Pos         (6)                                               /*!< CLK_T::APBCLK1: SPI3CKEN Position      */
#define CLK_APBCLK1_SPI3CKEN_Msk         (0x1ul << CLK_APBCLK1_SPI3CKEN_Pos)               /*!< CLK_T::APBCLK1: SPI3CKEN Mask          */

#define CLK_APBCLK1_USCI0CKEN_Pos        (8)                                               /*!< CLK_T::APBCLK1: USCI0CKEN Position     */
#define CLK_APBCLK1_USCI0CKEN_Msk        (0x1ul << CLK_APBCLK1_USCI0CKEN_Pos)              /*!< CLK_T::APBCLK1: USCI0CKEN Mask         */

#define CLK_APBCLK1_USCI1CKEN_Pos        (9)                                               /*!< CLK_T::APBCLK1: USCI1CKEN Position     */
#define CLK_APBCLK1_USCI1CKEN_Msk        (0x1ul << CLK_APBCLK1_USCI1CKEN_Pos)              /*!< CLK_T::APBCLK1: USCI1CKEN Mask         */

#define CLK_APBCLK1_DACCKEN_Pos          (12)                                              /*!< CLK_T::APBCLK1: DACCKEN Position       */
#define CLK_APBCLK1_DACCKEN_Msk          (0x1ul << CLK_APBCLK1_DACCKEN_Pos)                /*!< CLK_T::APBCLK1: DACCKEN Mask           */

#define CLK_APBCLK1_EPWM0CKEN_Pos        (16)                                              /*!< CLK_T::APBCLK1: EPWM0CKEN Position     */
#define CLK_APBCLK1_EPWM0CKEN_Msk        (0x1ul << CLK_APBCLK1_EPWM0CKEN_Pos)              /*!< CLK_T::APBCLK1: EPWM0CKEN Mask         */

#define CLK_APBCLK1_EPWM1CKEN_Pos        (17)                                              /*!< CLK_T::APBCLK1: EPWM1CKEN Position     */
#define CLK_APBCLK1_EPWM1CKEN_Msk        (0x1ul << CLK_APBCLK1_EPWM1CKEN_Pos)              /*!< CLK_T::APBCLK1: EPWM1CKEN Mask         */

#define CLK_APBCLK1_BPWM0CKEN_Pos        (18)                                              /*!< CLK_T::APBCLK1: BPWM0CKEN Position     */
#define CLK_APBCLK1_BPWM0CKEN_Msk        (0x1ul << CLK_APBCLK1_BPWM0CKEN_Pos)              /*!< CLK_T::APBCLK1: BPWM0CKEN Mask         */

#define CLK_APBCLK1_BPWM1CKEN_Pos        (19)                                              /*!< CLK_T::APBCLK1: BPWM1CKEN Position     */
#define CLK_APBCLK1_BPWM1CKEN_Msk        (0x1ul << CLK_APBCLK1_BPWM1CKEN_Pos)              /*!< CLK_T::APBCLK1: BPWM1CKEN Mask         */

#define CLK_APBCLK1_QEI0CKEN_Pos         (22)                                              /*!< CLK_T::APBCLK1: QEI0CKEN Position      */
#define CLK_APBCLK1_QEI0CKEN_Msk         (0x1ul << CLK_APBCLK1_QEI0CKEN_Pos)               /*!< CLK_T::APBCLK1: QEI0CKEN Mask          */

#define CLK_APBCLK1_QEI1CKEN_Pos         (23)                                              /*!< CLK_T::APBCLK1: QEI1CKEN Position      */
#define CLK_APBCLK1_QEI1CKEN_Msk         (0x1ul << CLK_APBCLK1_QEI1CKEN_Pos)               /*!< CLK_T::APBCLK1: QEI1CKEN Mask          */

#define CLK_APBCLK1_TRNGCKEN_Pos         (25)                                              /*!< CLK_T::APBCLK1: TRNGCKEN Position     */
#define CLK_APBCLK1_TRNGCKEN_Msk         (0x1ul << CLK_APBCLK1_TRNGCKEN_Pos)               /*!< CLK_T::APBCLK1: TRNGCKEN Mask         */

#define CLK_APBCLK1_ECAP0CKEN_Pos        (26)                                              /*!< CLK_T::APBCLK1: ECAP0CKEN Position     */
#define CLK_APBCLK1_ECAP0CKEN_Msk        (0x1ul << CLK_APBCLK1_ECAP0CKEN_Pos)              /*!< CLK_T::APBCLK1: ECAP0CKEN Mask         */

#define CLK_APBCLK1_ECAP1CKEN_Pos        (27)                                              /*!< CLK_T::APBCLK1: ECAP1CKEN Position     */
#define CLK_APBCLK1_ECAP1CKEN_Msk        (0x1ul << CLK_APBCLK1_ECAP1CKEN_Pos)              /*!< CLK_T::APBCLK1: ECAP1CKEN Mask         */

#define CLK_APBCLK1_CAN2CKEN_Pos         (28)                                              /*!< CLK_T::APBCLK1: CAN2CKEN Position      */
#define CLK_APBCLK1_CAN2CKEN_Msk         (0x1ul << CLK_APBCLK1_CAN2CKEN_Pos)               /*!< CLK_T::APBCLK1: CAN2CKEN Mask          */

#define CLK_APBCLK1_OPACKEN_Pos          (30)                                              /*!< CLK_T::APBCLK1: OPACKEN Position       */
#define CLK_APBCLK1_OPACKEN_Msk          (0x1ul << CLK_APBCLK1_OPACKEN_Pos)                /*!< CLK_T::APBCLK1: OPACKEN Mask           */

#define CLK_APBCLK1_EADC1CKEN_Pos        (31)                                              /*!< CLK_T::APBCLK1: EADC1CKEN Position     */
#define CLK_APBCLK1_EADC1CKEN_Msk        (0x1ul << CLK_APBCLK1_EADC1CKEN_Pos)              /*!< CLK_T::APBCLK1: EADC1CKEN Mask         */

#define CLK_CLKSEL0_HCLKSEL_Pos          (0)                                               /*!< CLK_T::CLKSEL0: HCLKSEL Position       */
#define CLK_CLKSEL0_HCLKSEL_Msk          (0x7ul << CLK_CLKSEL0_HCLKSEL_Pos)                /*!< CLK_T::CLKSEL0: HCLKSEL Mask           */

#define CLK_CLKSEL0_STCLKSEL_Pos         (3)                                               /*!< CLK_T::CLKSEL0: STCLKSEL Position      */
#define CLK_CLKSEL0_STCLKSEL_Msk         (0x7ul << CLK_CLKSEL0_STCLKSEL_Pos)               /*!< CLK_T::CLKSEL0: STCLKSEL Mask          */

#define CLK_CLKSEL0_USBSEL_Pos           (8)                                               /*!< CLK_T::CLKSEL0: PCLK0SEL Position      */
#define CLK_CLKSEL0_USBSEL_Msk           (0x1ul << CLK_CLKSEL0_USBSEL_Pos)                 /*!< CLK_T::CLKSEL0: PCLK0SEL Mask          */

#define CLK_CLKSEL0_CCAPSEL_Pos          (16)                                              /*!< CLK_T::CLKSEL0: CCAPSEL Position      */
#define CLK_CLKSEL0_CCAPSEL_Msk          (0x3ul << CLK_CLKSEL0_CCAPSEL_Pos)                /*!< CLK_T::CLKSEL0: CCAPSEL Mask          */

#define CLK_CLKSEL0_SDH0SEL_Pos          (20)                                              /*!< CLK_T::CLKSEL0: SDH0SEL Position       */
#define CLK_CLKSEL0_SDH0SEL_Msk          (0x3ul << CLK_CLKSEL0_SDH0SEL_Pos)                /*!< CLK_T::CLKSEL0: SDH0SEL Mask           */

#define CLK_CLKSEL0_SDH1SEL_Pos          (22)                                              /*!< CLK_T::CLKSEL0: SDH1SEL Position       */
#define CLK_CLKSEL0_SDH1SEL_Msk          (0x3ul << CLK_CLKSEL0_SDH1SEL_Pos)                /*!< CLK_T::CLKSEL0: SDH1SEL Mask           */

#define CLK_CLKSEL1_WDTSEL_Pos           (0)                                               /*!< CLK_T::CLKSEL1: WDTSEL Position        */
#define CLK_CLKSEL1_WDTSEL_Msk           (0x3ul << CLK_CLKSEL1_WDTSEL_Pos)                 /*!< CLK_T::CLKSEL1: WDTSEL Mask            */

#define CLK_CLKSEL1_TMR0SEL_Pos          (8)                                               /*!< CLK_T::CLKSEL1: TMR0SEL Position       */
#define CLK_CLKSEL1_TMR0SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR0SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR0SEL Mask           */

#define CLK_CLKSEL1_TMR1SEL_Pos          (12)                                              /*!< CLK_T::CLKSEL1: TMR1SEL Position       */
#define CLK_CLKSEL1_TMR1SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR1SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR1SEL Mask           */

#define CLK_CLKSEL1_TMR2SEL_Pos          (16)                                              /*!< CLK_T::CLKSEL1: TMR2SEL Position       */
#define CLK_CLKSEL1_TMR2SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR2SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR2SEL Mask           */

#define CLK_CLKSEL1_TMR3SEL_Pos          (20)                                              /*!< CLK_T::CLKSEL1: TMR3SEL Position       */
#define CLK_CLKSEL1_TMR3SEL_Msk          (0x7ul << CLK_CLKSEL1_TMR3SEL_Pos)                /*!< CLK_T::CLKSEL1: TMR3SEL Mask           */

#define CLK_CLKSEL1_UART0SEL_Pos         (24)                                              /*!< CLK_T::CLKSEL1: UART0SEL Position      */
#define CLK_CLKSEL1_UART0SEL_Msk         (0x3ul << CLK_CLKSEL1_UART0SEL_Pos)               /*!< CLK_T::CLKSEL1: UART0SEL Mask          */

#define CLK_CLKSEL1_UART1SEL_Pos         (26)                                              /*!< CLK_T::CLKSEL1: UART1SEL Position      */
#define CLK_CLKSEL1_UART1SEL_Msk         (0x3ul << CLK_CLKSEL1_UART1SEL_Pos)               /*!< CLK_T::CLKSEL1: UART1SEL Mask          */

#define CLK_CLKSEL1_CLKOSEL_Pos          (28)                                              /*!< CLK_T::CLKSEL1: CLKOSEL Position       */
#define CLK_CLKSEL1_CLKOSEL_Msk          (0x3ul << CLK_CLKSEL1_CLKOSEL_Pos)                /*!< CLK_T::CLKSEL1: CLKOSEL Mask           */

#define CLK_CLKSEL1_WWDTSEL_Pos          (30)                                              /*!< CLK_T::CLKSEL1: WWDTSEL Position       */
#define CLK_CLKSEL1_WWDTSEL_Msk          (0x3ul << CLK_CLKSEL1_WWDTSEL_Pos)                /*!< CLK_T::CLKSEL1: WWDTSEL Mask           */

#define CLK_CLKSEL2_EPWM0SEL_Pos         (0)                                               /*!< CLK_T::CLKSEL2: EPWM0SEL Position      */
#define CLK_CLKSEL2_EPWM0SEL_Msk         (0x1ul << CLK_CLKSEL2_EPWM0SEL_Pos)               /*!< CLK_T::CLKSEL2: EPWM0SEL Mask          */

#define CLK_CLKSEL2_EPWM1SEL_Pos         (1)                                               /*!< CLK_T::CLKSEL2: EPWM1SEL Position      */
#define CLK_CLKSEL2_EPWM1SEL_Msk         (0x1ul << CLK_CLKSEL2_EPWM1SEL_Pos)               /*!< CLK_T::CLKSEL2: EPWM1SEL Mask          */

#define CLK_CLKSEL2_QSPI0SEL_Pos         (2)                                               /*!< CLK_T::CLKSEL2: QSPI0SEL Position      */
#define CLK_CLKSEL2_QSPI0SEL_Msk         (0x3ul << CLK_CLKSEL2_QSPI0SEL_Pos)               /*!< CLK_T::CLKSEL2: QSPI0SEL Mask          */

#define CLK_CLKSEL2_SPI0SEL_Pos          (4)                                               /*!< CLK_T::CLKSEL2: SPI0SEL Position       */
#define CLK_CLKSEL2_SPI0SEL_Msk          (0x3ul << CLK_CLKSEL2_SPI0SEL_Pos)                /*!< CLK_T::CLKSEL2: SPI0SEL Mask           */

#define CLK_CLKSEL2_SPI1SEL_Pos          (6)                                               /*!< CLK_T::CLKSEL2: SPI1SEL Position       */
#define CLK_CLKSEL2_SPI1SEL_Msk          (0x3ul << CLK_CLKSEL2_SPI1SEL_Pos)                /*!< CLK_T::CLKSEL2: SPI1SEL Mask           */

#define CLK_CLKSEL2_BPWM0SEL_Pos         (8)                                               /*!< CLK_T::CLKSEL2: BPWM0SEL Position      */
#define CLK_CLKSEL2_BPWM0SEL_Msk         (0x1ul << CLK_CLKSEL2_BPWM0SEL_Pos)               /*!< CLK_T::CLKSEL2: BPWM0SEL Mask          */

#define CLK_CLKSEL2_BPWM1SEL_Pos         (9)                                               /*!< CLK_T::CLKSEL2: BPWM1SEL Position      */
#define CLK_CLKSEL2_BPWM1SEL_Msk         (0x1ul << CLK_CLKSEL2_BPWM1SEL_Pos)               /*!< CLK_T::CLKSEL2: BPWM1SEL Mask          */

#define CLK_CLKSEL2_SPI2SEL_Pos          (10)                                              /*!< CLK_T::CLKSEL2: SPI2SEL Position       */
#define CLK_CLKSEL2_SPI2SEL_Msk          (0x3ul << CLK_CLKSEL2_SPI2SEL_Pos)                /*!< CLK_T::CLKSEL2: SPI2SEL Mask           */

#define CLK_CLKSEL2_SPI3SEL_Pos          (12)                                              /*!< CLK_T::CLKSEL2: SPI3SEL Position       */
#define CLK_CLKSEL2_SPI3SEL_Msk          (0x3ul << CLK_CLKSEL2_SPI3SEL_Pos)                /*!< CLK_T::CLKSEL2: SPI3SEL Mask           */

#define CLK_CLKSEL3_SC0SEL_Pos           (0)                                               /*!< CLK_T::CLKSEL3: SC0SEL Position        */
#define CLK_CLKSEL3_SC0SEL_Msk           (0x3ul << CLK_CLKSEL3_SC0SEL_Pos)                 /*!< CLK_T::CLKSEL3: SC0SEL Mask            */

#define CLK_CLKSEL3_SC1SEL_Pos           (2)                                               /*!< CLK_T::CLKSEL3: SC1SEL Position        */
#define CLK_CLKSEL3_SC1SEL_Msk           (0x3ul << CLK_CLKSEL3_SC1SEL_Pos)                 /*!< CLK_T::CLKSEL3: SC1SEL Mask            */

#define CLK_CLKSEL3_SC2SEL_Pos           (4)                                               /*!< CLK_T::CLKSEL3: SC2SEL Position        */
#define CLK_CLKSEL3_SC2SEL_Msk           (0x3ul << CLK_CLKSEL3_SC2SEL_Pos)                 /*!< CLK_T::CLKSEL3: SC2SEL Mask            */

#define CLK_CLKSEL3_RTCSEL_Pos           (8)                                               /*!< CLK_T::CLKSEL3: RTCSEL Position        */
#define CLK_CLKSEL3_RTCSEL_Msk           (0x1ul << CLK_CLKSEL3_RTCSEL_Pos)                 /*!< CLK_T::CLKSEL3: RTCSEL Mask            */

#define CLK_CLKSEL3_QSPI1SEL_Pos         (12)                                              /*!< CLK_T::CLKSEL3: QSPI1SEL Position      */
#define CLK_CLKSEL3_QSPI1SEL_Msk         (0x3ul << CLK_CLKSEL3_QSPI1SEL_Pos)               /*!< CLK_T::CLKSEL3: QSPI1SEL Mask          */

#define CLK_CLKSEL3_I2S0SEL_Pos          (16)                                              /*!< CLK_T::CLKSEL3: I2S0SEL Position       */
#define CLK_CLKSEL3_I2S0SEL_Msk          (0x3ul << CLK_CLKSEL3_I2S0SEL_Pos)                /*!< CLK_T::CLKSEL3: I2S0SEL Mask           */

#define CLK_CLKSEL3_UART6SEL_Pos         (20)                                              /*!< CLK_T::CLKSEL3: UART6SEL Position      */
#define CLK_CLKSEL3_UART6SEL_Msk         (0x3ul << CLK_CLKSEL3_UART6SEL_Pos)               /*!< CLK_T::CLKSEL3: UART6SEL Mask          */

#define CLK_CLKSEL3_UART7SEL_Pos         (22)                                              /*!< CLK_T::CLKSEL3: UART7SEL Position      */
#define CLK_CLKSEL3_UART7SEL_Msk         (0x3ul << CLK_CLKSEL3_UART7SEL_Pos)               /*!< CLK_T::CLKSEL3: UART7SEL Mask          */

#define CLK_CLKSEL3_UART2SEL_Pos         (24)                                              /*!< CLK_T::CLKSEL3: UART2SEL Position      */
#define CLK_CLKSEL3_UART2SEL_Msk         (0x3ul << CLK_CLKSEL3_UART2SEL_Pos)               /*!< CLK_T::CLKSEL3: UART2SEL Mask          */

#define CLK_CLKSEL3_UART3SEL_Pos         (26)                                              /*!< CLK_T::CLKSEL3: UART3SEL Position      */
#define CLK_CLKSEL3_UART3SEL_Msk         (0x3ul << CLK_CLKSEL3_UART3SEL_Pos)               /*!< CLK_T::CLKSEL3: UART3SEL Mask          */

#define CLK_CLKSEL3_UART4SEL_Pos         (28)                                              /*!< CLK_T::CLKSEL3: UART4SEL Position      */
#define CLK_CLKSEL3_UART4SEL_Msk         (0x3ul << CLK_CLKSEL3_UART4SEL_Pos)               /*!< CLK_T::CLKSEL3: UART4SEL Mask          */

#define CLK_CLKSEL3_UART5SEL_Pos         (30)                                              /*!< CLK_T::CLKSEL3: UART5SEL Position      */
#define CLK_CLKSEL3_UART5SEL_Msk         (0x3ul << CLK_CLKSEL3_UART5SEL_Pos)               /*!< CLK_T::CLKSEL3: UART5SEL Mask          */

#define CLK_CLKDIV0_HCLKDIV_Pos          (0)                                               /*!< CLK_T::CLKDIV0: HCLKDIV Position       */
#define CLK_CLKDIV0_HCLKDIV_Msk          (0xful << CLK_CLKDIV0_HCLKDIV_Pos)                /*!< CLK_T::CLKDIV0: HCLKDIV Mask           */

#define CLK_CLKDIV0_USBDIV_Pos           (4)                                               /*!< CLK_T::CLKDIV0: USBDIV Position        */
#define CLK_CLKDIV0_USBDIV_Msk           (0xful << CLK_CLKDIV0_USBDIV_Pos)                 /*!< CLK_T::CLKDIV0: USBDIV Mask            */

#define CLK_CLKDIV0_UART0DIV_Pos         (8)                                               /*!< CLK_T::CLKDIV0: UART0DIV Position      */
#define CLK_CLKDIV0_UART0DIV_Msk         (0xful << CLK_CLKDIV0_UART0DIV_Pos)               /*!< CLK_T::CLKDIV0: UART0DIV Mask          */

#define CLK_CLKDIV0_UART1DIV_Pos         (12)                                              /*!< CLK_T::CLKDIV0: UART1DIV Position      */
#define CLK_CLKDIV0_UART1DIV_Msk         (0xful << CLK_CLKDIV0_UART1DIV_Pos)               /*!< CLK_T::CLKDIV0: UART1DIV Mask          */

#define CLK_CLKDIV0_EADCDIV_Pos          (16)                                              /*!< CLK_T::CLKDIV0: EADCDIV Position       */
#define CLK_CLKDIV0_EADCDIV_Msk          (0xfful << CLK_CLKDIV0_EADCDIV_Pos)               /*!< CLK_T::CLKDIV0: EADCDIV Mask           */

#define CLK_CLKDIV0_SDH0DIV_Pos          (24)                                              /*!< CLK_T::CLKDIV0: SDH0DIV Position       */
#define CLK_CLKDIV0_SDH0DIV_Msk          (0xfful << CLK_CLKDIV0_SDH0DIV_Pos)               /*!< CLK_T::CLKDIV0: SDH0DIV Mask           */

#define CLK_CLKDIV1_SC0DIV_Pos           (0)                                               /*!< CLK_T::CLKDIV1: SC0DIV Position        */
#define CLK_CLKDIV1_SC0DIV_Msk           (0xfful << CLK_CLKDIV1_SC0DIV_Pos)                /*!< CLK_T::CLKDIV1: SC0DIV Mask            */

#define CLK_CLKDIV1_SC1DIV_Pos           (8)                                               /*!< CLK_T::CLKDIV1: SC1DIV Position        */
#define CLK_CLKDIV1_SC1DIV_Msk           (0xfful << CLK_CLKDIV1_SC1DIV_Pos)                /*!< CLK_T::CLKDIV1: SC1DIV Mask            */

#define CLK_CLKDIV1_SC2DIV_Pos           (16)                                              /*!< CLK_T::CLKDIV1: SC2DIV Position        */
#define CLK_CLKDIV1_SC2DIV_Msk           (0xfful << CLK_CLKDIV1_SC2DIV_Pos)                /*!< CLK_T::CLKDIV1: SC2DIV Mask            */

#define CLK_CLKDIV2_I2SDIV_Pos           (0)                                               /*!< CLK_T::CLKDIV2: I2SDIV Position        */
#define CLK_CLKDIV2_I2SDIV_Msk           (0xful << CLK_CLKDIV2_I2SDIV_Pos)                 /*!< CLK_T::CLKDIV2: I2SDIV Mask            */

#define CLK_CLKDIV2_EADC1DIV_Pos         (24)                                              /*!< CLK_T::CLKDIV2: EADC1DIV Position      */
#define CLK_CLKDIV2_EADC1DIV_Msk         (0xfful << CLK_CLKDIV2_EADC1DIV_Pos)              /*!< CLK_T::CLKDIV2: EADC1DIV Mask          */

#define CLK_CLKDIV3_CCAPDIV_Pos          (0)                                               /*!< CLK_T::CLKDIV3: CCAPDIV Position       */
#define CLK_CLKDIV3_CCAPDIV_Msk          (0xfful << CLK_CLKDIV3_CCAPDIV_Pos)               /*!< CLK_T::CLKDIV3: CCAPDIV Mask           */

#define CLK_CLKDIV3_VSENSEDIV_Pos        (8)                                               /*!< CLK_T::CLKDIV3: VSENSEDIV Position     */
#define CLK_CLKDIV3_VSENSEDIV_Msk        (0xfful << CLK_CLKDIV3_VSENSEDIV_Pos)             /*!< CLK_T::CLKDIV3: VSENSEDIV Mask         */

#define CLK_CLKDIV3_EMACDIV_Pos          (16)                                              /*!< CLK_T::CLKDIV3: EMACDIV Position       */
#define CLK_CLKDIV3_EMACDIV_Msk          (0xfful << CLK_CLKDIV3_EMACDIV_Pos)               /*!< CLK_T::CLKDIV3: EMACDIV Mask           */

#define CLK_CLKDIV3_SDH1DIV_Pos          (24)                                              /*!< CLK_T::CLKDIV3: SDH1DIV Position       */
#define CLK_CLKDIV3_SDH1DIV_Msk          (0xfful << CLK_CLKDIV3_SDH1DIV_Pos)               /*!< CLK_T::CLKDIV3: SDH1DIV Mask           */

#define CLK_CLKDIV4_UART2DIV_Pos         (0)                                               /*!< CLK_T::CLKDIV4: UART2DIV Position      */
#define CLK_CLKDIV4_UART2DIV_Msk         (0xful << CLK_CLKDIV4_UART2DIV_Pos)               /*!< CLK_T::CLKDIV4: UART2DIV Mask          */

#define CLK_CLKDIV4_UART3DIV_Pos         (4)                                               /*!< CLK_T::CLKDIV4: UART3DIV Position      */
#define CLK_CLKDIV4_UART3DIV_Msk         (0xful << CLK_CLKDIV4_UART3DIV_Pos)               /*!< CLK_T::CLKDIV4: UART3DIV Mask          */

#define CLK_CLKDIV4_UART4DIV_Pos         (8)                                               /*!< CLK_T::CLKDIV4: UART4DIV Position      */
#define CLK_CLKDIV4_UART4DIV_Msk         (0xful << CLK_CLKDIV4_UART4DIV_Pos)               /*!< CLK_T::CLKDIV4: UART4DIV Mask          */

#define CLK_CLKDIV4_UART5DIV_Pos         (12)                                              /*!< CLK_T::CLKDIV4: UART5DIV Position      */
#define CLK_CLKDIV4_UART5DIV_Msk         (0xful << CLK_CLKDIV4_UART5DIV_Pos)               /*!< CLK_T::CLKDIV4: UART5DIV Mask          */

#define CLK_CLKDIV4_UART6DIV_Pos         (16)                                              /*!< CLK_T::CLKDIV4: UART6DIV Position      */
#define CLK_CLKDIV4_UART6DIV_Msk         (0xful << CLK_CLKDIV4_UART6DIV_Pos)               /*!< CLK_T::CLKDIV4: UART6DIV Mask          */

#define CLK_CLKDIV4_UART7DIV_Pos         (20)                                              /*!< CLK_T::CLKDIV4: UART7DIV Position      */
#define CLK_CLKDIV4_UART7DIV_Msk         (0xful << CLK_CLKDIV4_UART7DIV_Pos)               /*!< CLK_T::CLKDIV4: UART7DIV Mask          */

#define CLK_PCLKDIV_APB0DIV_Pos          (0)                                               /*!< CLK_T::PCLKDIV: APB0DIV Position       */
#define CLK_PCLKDIV_APB0DIV_Msk          (0x7ul << CLK_PCLKDIV_APB0DIV_Pos)                /*!< CLK_T::PCLKDIV: APB0DIV Mask           */

#define CLK_PCLKDIV_APB1DIV_Pos          (4)                                               /*!< CLK_T::PCLKDIV: APB1DIV Position       */
#define CLK_PCLKDIV_APB1DIV_Msk          (0x7ul << CLK_PCLKDIV_APB1DIV_Pos)                /*!< CLK_T::PCLKDIV: APB1DIV Mask           */

#define CLK_PLLCTL_FBDIV_Pos             (0)                                               /*!< CLK_T::PLLCTL: FBDIV Position          */
#define CLK_PLLCTL_FBDIV_Msk             (0x1fful << CLK_PLLCTL_FBDIV_Pos)                 /*!< CLK_T::PLLCTL: FBDIV Mask              */

#define CLK_PLLCTL_INDIV_Pos             (9)                                               /*!< CLK_T::PLLCTL: INDIV Position          */
#define CLK_PLLCTL_INDIV_Msk             (0x1ful << CLK_PLLCTL_INDIV_Pos)                  /*!< CLK_T::PLLCTL: INDIV Mask              */

#define CLK_PLLCTL_OUTDIV_Pos            (14)                                              /*!< CLK_T::PLLCTL: OUTDIV Position         */
#define CLK_PLLCTL_OUTDIV_Msk            (0x3ul << CLK_PLLCTL_OUTDIV_Pos)                  /*!< CLK_T::PLLCTL: OUTDIV Mask             */

#define CLK_PLLCTL_PD_Pos                (16)                                              /*!< CLK_T::PLLCTL: PD Position             */
#define CLK_PLLCTL_PD_Msk                (0x1ul << CLK_PLLCTL_PD_Pos)                      /*!< CLK_T::PLLCTL: PD Mask                 */

#define CLK_PLLCTL_BP_Pos                (17)                                              /*!< CLK_T::PLLCTL: BP Position             */
#define CLK_PLLCTL_BP_Msk                (0x1ul << CLK_PLLCTL_BP_Pos)                      /*!< CLK_T::PLLCTL: BP Mask                 */

#define CLK_PLLCTL_OE_Pos                (18)                                              /*!< CLK_T::PLLCTL: OE Position             */
#define CLK_PLLCTL_OE_Msk                (0x1ul << CLK_PLLCTL_OE_Pos)                      /*!< CLK_T::PLLCTL: OE Mask                 */

#define CLK_PLLCTL_PLLSRC_Pos            (19)                                              /*!< CLK_T::PLLCTL: PLLSRC Position         */
#define CLK_PLLCTL_PLLSRC_Msk            (0x1ul << CLK_PLLCTL_PLLSRC_Pos)                  /*!< CLK_T::PLLCTL: PLLSRC Mask             */

#define CLK_PLLCTL_STBSEL_Pos            (23)                                              /*!< CLK_T::PLLCTL: STBSEL Position         */
#define CLK_PLLCTL_STBSEL_Msk            (0x1ul << CLK_PLLCTL_STBSEL_Pos)                  /*!< CLK_T::PLLCTL: STBSEL Mask             */

#define CLK_STATUS_HXTSTB_Pos            (0)                                               /*!< CLK_T::STATUS: HXTSTB Position         */
#define CLK_STATUS_HXTSTB_Msk            (0x1ul << CLK_STATUS_HXTSTB_Pos)                  /*!< CLK_T::STATUS: HXTSTB Mask             */

#define CLK_STATUS_LXTSTB_Pos            (1)                                               /*!< CLK_T::STATUS: LXTSTB Position         */
#define CLK_STATUS_LXTSTB_Msk            (0x1ul << CLK_STATUS_LXTSTB_Pos)                  /*!< CLK_T::STATUS: LXTSTB Mask             */

#define CLK_STATUS_PLLSTB_Pos            (2)                                               /*!< CLK_T::STATUS: PLLSTB Position         */
#define CLK_STATUS_PLLSTB_Msk            (0x1ul << CLK_STATUS_PLLSTB_Pos)                  /*!< CLK_T::STATUS: PLLSTB Mask             */

#define CLK_STATUS_LIRCSTB_Pos           (3)                                               /*!< CLK_T::STATUS: LIRCSTB Position        */
#define CLK_STATUS_LIRCSTB_Msk           (0x1ul << CLK_STATUS_LIRCSTB_Pos)                 /*!< CLK_T::STATUS: LIRCSTB Mask            */

#define CLK_STATUS_HIRCSTB_Pos           (4)                                               /*!< CLK_T::STATUS: HIRCSTB Position        */
#define CLK_STATUS_HIRCSTB_Msk           (0x1ul << CLK_STATUS_HIRCSTB_Pos)                 /*!< CLK_T::STATUS: HIRCSTB Mask            */

#define CLK_STATUS_HIRC48MSTB_Pos        (6)                                               /*!< CLK_T::STATUS: HIRC48MSTB Position     */
#define CLK_STATUS_HIRC48MSTB_Msk        (0x1ul << CLK_STATUS_HIRC48MSTB_Pos)              /*!< CLK_T::STATUS: HIRC48MSTB Mask         */

#define CLK_STATUS_CLKSFAIL_Pos          (7)                                               /*!< CLK_T::STATUS: CLKSFAIL Position       */
#define CLK_STATUS_CLKSFAIL_Msk          (0x1ul << CLK_STATUS_CLKSFAIL_Pos)                /*!< CLK_T::STATUS: CLKSFAIL Mask           */

#define CLK_CLKOCTL_FREQSEL_Pos          (0)                                               /*!< CLK_T::CLKOCTL: FREQSEL Position       */
#define CLK_CLKOCTL_FREQSEL_Msk          (0xful << CLK_CLKOCTL_FREQSEL_Pos)                /*!< CLK_T::CLKOCTL: FREQSEL Mask           */

#define CLK_CLKOCTL_CLKOEN_Pos           (4)                                               /*!< CLK_T::CLKOCTL: CLKOEN Position        */
#define CLK_CLKOCTL_CLKOEN_Msk           (0x1ul << CLK_CLKOCTL_CLKOEN_Pos)                 /*!< CLK_T::CLKOCTL: CLKOEN Mask            */

#define CLK_CLKOCTL_DIV1EN_Pos           (5)                                               /*!< CLK_T::CLKOCTL: DIV1EN Position        */
#define CLK_CLKOCTL_DIV1EN_Msk           (0x1ul << CLK_CLKOCTL_DIV1EN_Pos)                 /*!< CLK_T::CLKOCTL: DIV1EN Mask            */

#define CLK_CLKOCTL_CLK1HZEN_Pos         (6)                                               /*!< CLK_T::CLKOCTL: CLK1HZEN Position      */
#define CLK_CLKOCTL_CLK1HZEN_Msk         (0x1ul << CLK_CLKOCTL_CLK1HZEN_Pos)               /*!< CLK_T::CLKOCTL: CLK1HZEN Mask          */

#define CLK_CLKDCTL_HXTFDEN_Pos          (4)                                               /*!< CLK_T::CLKDCTL: HXTFDEN Position       */
#define CLK_CLKDCTL_HXTFDEN_Msk          (0x1ul << CLK_CLKDCTL_HXTFDEN_Pos)                /*!< CLK_T::CLKDCTL: HXTFDEN Mask           */

#define CLK_CLKDCTL_HXTFIEN_Pos          (5)                                               /*!< CLK_T::CLKDCTL: HXTFIEN Position       */
#define CLK_CLKDCTL_HXTFIEN_Msk          (0x1ul << CLK_CLKDCTL_HXTFIEN_Pos)                /*!< CLK_T::CLKDCTL: HXTFIEN Mask           */

#define CLK_CLKDCTL_LXTFDEN_Pos          (12)                                              /*!< CLK_T::CLKDCTL: LXTFDEN Position       */
#define CLK_CLKDCTL_LXTFDEN_Msk          (0x1ul << CLK_CLKDCTL_LXTFDEN_Pos)                /*!< CLK_T::CLKDCTL: LXTFDEN Mask           */

#define CLK_CLKDCTL_LXTFIEN_Pos          (13)                                              /*!< CLK_T::CLKDCTL: LXTFIEN Position       */
#define CLK_CLKDCTL_LXTFIEN_Msk          (0x1ul << CLK_CLKDCTL_LXTFIEN_Pos)                /*!< CLK_T::CLKDCTL: LXTFIEN Mask           */

#define CLK_CLKDCTL_HXTFQDEN_Pos         (16)                                              /*!< CLK_T::CLKDCTL: HXTFQDEN Position      */
#define CLK_CLKDCTL_HXTFQDEN_Msk         (0x1ul << CLK_CLKDCTL_HXTFQDEN_Pos)               /*!< CLK_T::CLKDCTL: HXTFQDEN Mask          */

#define CLK_CLKDCTL_HXTFQIEN_Pos         (17)                                              /*!< CLK_T::CLKDCTL: HXTFQIEN Position      */
#define CLK_CLKDCTL_HXTFQIEN_Msk         (0x1ul << CLK_CLKDCTL_HXTFQIEN_Pos)               /*!< CLK_T::CLKDCTL: HXTFQIEN Mask          */

#define CLK_CLKDSTS_HXTFIF_Pos           (0)                                               /*!< CLK_T::CLKDSTS: HXTFIF Position        */
#define CLK_CLKDSTS_HXTFIF_Msk           (0x1ul << CLK_CLKDSTS_HXTFIF_Pos)                 /*!< CLK_T::CLKDSTS: HXTFIF Mask            */

#define CLK_CLKDSTS_LXTFIF_Pos           (1)                                               /*!< CLK_T::CLKDSTS: LXTFIF Position        */
#define CLK_CLKDSTS_LXTFIF_Msk           (0x1ul << CLK_CLKDSTS_LXTFIF_Pos)                 /*!< CLK_T::CLKDSTS: LXTFIF Mask            */

#define CLK_CLKDSTS_HXTFQIF_Pos          (8)                                               /*!< CLK_T::CLKDSTS: HXTFQIF Position       */
#define CLK_CLKDSTS_HXTFQIF_Msk          (0x1ul << CLK_CLKDSTS_HXTFQIF_Pos)                /*!< CLK_T::CLKDSTS: HXTFQIF Mask           */

#define CLK_CDUPB_UPERBD_Pos             (0)                                               /*!< CLK_T::CDUPB: UPERBD Position          */
#define CLK_CDUPB_UPERBD_Msk             (0x3fful << CLK_CDUPB_UPERBD_Pos)                 /*!< CLK_T::CDUPB: UPERBD Mask              */

#define CLK_CDLOWB_LOWERBD_Pos           (0)                                               /*!< CLK_T::CDLOWB: LOWERBD Position        */
#define CLK_CDLOWB_LOWERBD_Msk           (0x3fful << CLK_CDLOWB_LOWERBD_Pos)               /*!< CLK_T::CDLOWB: LOWERBD Mask            */

#define CLK_PMUCTL_PDMSEL_Pos            (0)                                               /*!< CLK_T::PMUCTL: PDMSEL Position         */
#define CLK_PMUCTL_PDMSEL_Msk            (0x7ul << CLK_PMUCTL_PDMSEL_Pos)                  /*!< CLK_T::PMUCTL: PDMSEL Mask             */

#define CLK_PMUCTL_DPDHOLDEN_Pos         (3)                                               /*!< CLK_T::PMUCTL: DPDHOLDEN Position      */
#define CLK_PMUCTL_DPDHOLDEN_Msk         (0x1ul << CLK_PMUCTL_DPDHOLDEN_Pos)               /*!< CLK_T::PMUCTL: DPDHOLDEN Mask          */

#define CLK_PMUCTL_SRETSEL_Pos           (4)                                               /*!< CLK_T::PMUCTL: SRETSEL Position        */
#define CLK_PMUCTL_SRETSEL_Msk           (0x7ul << CLK_PMUCTL_SRETSEL_Pos)                 /*!< CLK_T::PMUCTL: SRETSEL Mask            */

#define CLK_PMUCTL_WKTMREN_Pos           (8)                                               /*!< CLK_T::PMUCTL: WKTMREN Position        */
#define CLK_PMUCTL_WKTMREN_Msk           (0x1ul << CLK_PMUCTL_WKTMREN_Pos)                 /*!< CLK_T::PMUCTL: WKTMREN Mask            */

#define CLK_PMUCTL_WKTMRIS_Pos           (9)                                               /*!< CLK_T::PMUCTL: WKTMRIS Position        */
#define CLK_PMUCTL_WKTMRIS_Msk           (0xful << CLK_PMUCTL_WKTMRIS_Pos)                 /*!< CLK_T::PMUCTL: WKTMRIS Mask            */

#define CLK_PMUCTL_WKPINEN_Pos           (16)                                              /*!< CLK_T::PMUCTL: WKPINEN Position        */
#define CLK_PMUCTL_WKPINEN_Msk           (0x3ul << CLK_PMUCTL_WKPINEN_Pos)                 /*!< CLK_T::PMUCTL: WKPINEN Mask            */

#define CLK_PMUCTL_ACMPSPWK_Pos          (18)                                              /*!< CLK_T::PMUCTL: ACMPSPWK Position       */
#define CLK_PMUCTL_ACMPSPWK_Msk          (0x1ul << CLK_PMUCTL_ACMPSPWK_Pos)                /*!< CLK_T::PMUCTL: ACMPSPWK Mask           */

#define CLK_PMUCTL_RTCWKEN_Pos           (23)                                              /*!< CLK_T::PMUCTL: RTCWKEN Position        */
#define CLK_PMUCTL_RTCWKEN_Msk           (0x1ul << CLK_PMUCTL_RTCWKEN_Pos)                 /*!< CLK_T::PMUCTL: RTCWKEN Mask            */

#define CLK_PMUCTL_WKPINEN1_Pos          (24)                                              /*!< CLK_T::PMUCTL: WKPINEN1 Position       */
#define CLK_PMUCTL_WKPINEN1_Msk          (0x3ul << CLK_PMUCTL_WKPINEN1_Pos)                /*!< CLK_T::PMUCTL: WKPINEN1 Mask           */

#define CLK_PMUCTL_WKPINEN2_Pos          (26)                                              /*!< CLK_T::PMUCTL: WKPINEN2 Position       */
#define CLK_PMUCTL_WKPINEN2_Msk          (0x3ul << CLK_PMUCTL_WKPINEN2_Pos)                /*!< CLK_T::PMUCTL: WKPINEN2 Mask           */

#define CLK_PMUCTL_WKPINEN3_Pos          (28)                                              /*!< CLK_T::PMUCTL: WKPINEN3 Position       */
#define CLK_PMUCTL_WKPINEN3_Msk          (0x3ul << CLK_PMUCTL_WKPINEN3_Pos)                /*!< CLK_T::PMUCTL: WKPINEN3 Mask           */

#define CLK_PMUCTL_WKPINEN4_Pos          (30)                                              /*!< CLK_T::PMUCTL: WKPINEN4 Position       */
#define CLK_PMUCTL_WKPINEN4_Msk          (0x3ul << CLK_PMUCTL_WKPINEN4_Pos)                /*!< CLK_T::PMUCTL: WKPINEN4 Mask           */

#define CLK_PMUSTS_PINWK_Pos             (0)                                               /*!< CLK_T::PMUSTS: PINWK Position          */
#define CLK_PMUSTS_PINWK_Msk             (0x1ul << CLK_PMUSTS_PINWK_Pos)                   /*!< CLK_T::PMUSTS: PINWK Mask              */

#define CLK_PMUSTS_TMRWK_Pos             (1)                                               /*!< CLK_T::PMUSTS: TMRWK Position          */
#define CLK_PMUSTS_TMRWK_Msk             (0x1ul << CLK_PMUSTS_TMRWK_Pos)                   /*!< CLK_T::PMUSTS: TMRWK Mask              */

#define CLK_PMUSTS_RTCWK_Pos             (2)                                               /*!< CLK_T::PMUSTS: RTCWK Position          */
#define CLK_PMUSTS_RTCWK_Msk             (0x1ul << CLK_PMUSTS_RTCWK_Pos)                   /*!< CLK_T::PMUSTS: RTCWK Mask              */

#define CLK_PMUSTS_PINWK1_Pos            (3)                                               /*!< CLK_T::PMUSTS: PINWK1 Position         */
#define CLK_PMUSTS_PINWK1_Msk            (0x1ul << CLK_PMUSTS_PINWK1_Pos)                  /*!< CLK_T::PMUSTS: PINWK1 Mask             */

#define CLK_PMUSTS_PINWK2_Pos            (4)                                               /*!< CLK_T::PMUSTS: PINWK2 Position         */
#define CLK_PMUSTS_PINWK2_Msk            (0x1ul << CLK_PMUSTS_PINWK2_Pos)                  /*!< CLK_T::PMUSTS: PINWK2 Mask             */

#define CLK_PMUSTS_PINWK3_Pos            (5)                                               /*!< CLK_T::PMUSTS: PINWK3 Position         */
#define CLK_PMUSTS_PINWK3_Msk            (0x1ul << CLK_PMUSTS_PINWK3_Pos)                  /*!< CLK_T::PMUSTS: PINWK3 Mask             */

#define CLK_PMUSTS_PINWK4_Pos            (6)                                               /*!< CLK_T::PMUSTS: PINWK4 Position         */
#define CLK_PMUSTS_PINWK4_Msk            (0x1ul << CLK_PMUSTS_PINWK4_Pos)                  /*!< CLK_T::PMUSTS: PINWK4 Mask             */

#define CLK_PMUSTS_GPAWK_Pos             (8)                                               /*!< CLK_T::PMUSTS: GPAWK Position          */
#define CLK_PMUSTS_GPAWK_Msk             (0x1ul << CLK_PMUSTS_GPAWK_Pos)                   /*!< CLK_T::PMUSTS: GPAWK Mask              */

#define CLK_PMUSTS_GPBWK_Pos             (9)                                               /*!< CLK_T::PMUSTS: GPBWK Position          */
#define CLK_PMUSTS_GPBWK_Msk             (0x1ul << CLK_PMUSTS_GPBWK_Pos)                   /*!< CLK_T::PMUSTS: GPBWK Mask              */

#define CLK_PMUSTS_GPCWK_Pos             (10)                                              /*!< CLK_T::PMUSTS: GPCWK Position          */
#define CLK_PMUSTS_GPCWK_Msk             (0x1ul << CLK_PMUSTS_GPCWK_Pos)                   /*!< CLK_T::PMUSTS: GPCWK Mask              */

#define CLK_PMUSTS_GPDWK_Pos             (11)                                              /*!< CLK_T::PMUSTS: GPDWK Position          */
#define CLK_PMUSTS_GPDWK_Msk             (0x1ul << CLK_PMUSTS_GPDWK_Pos)                   /*!< CLK_T::PMUSTS: GPDWK Mask              */

#define CLK_PMUSTS_LVRWK_Pos             (12)                                              /*!< CLK_T::PMUSTS: LVRWK Position          */
#define CLK_PMUSTS_LVRWK_Msk             (0x1ul << CLK_PMUSTS_LVRWK_Pos)                   /*!< CLK_T::PMUSTS: LVRWK Mask              */

#define CLK_PMUSTS_BODWK_Pos             (13)                                              /*!< CLK_T::PMUSTS: BODWK Position          */
#define CLK_PMUSTS_BODWK_Msk             (0x1ul << CLK_PMUSTS_BODWK_Pos)                   /*!< CLK_T::PMUSTS: BODWK Mask              */

#define CLK_PMUSTS_ACMPWK_Pos            (14)                                              /*!< CLK_T::PMUSTS: ACMPWK Position         */
#define CLK_PMUSTS_ACMPWK_Msk            (0x1ul << CLK_PMUSTS_ACMPWK_Pos)                  /*!< CLK_T::PMUSTS: ACMPWK Mask             */

#define CLK_PMUSTS_CLRWK_Pos             (31)                                              /*!< CLK_T::PMUSTS: CLRWK Position          */
#define CLK_PMUSTS_CLRWK_Msk             (0x1ul << CLK_PMUSTS_CLRWK_Pos)                   /*!< CLK_T::PMUSTS: CLRWK Mask              */

#define CLK_LDOCTL_PDBIASEN_Pos          (18)                                              /*!< CLK_T::LDOCTL: PDBIASEN Position       */
#define CLK_LDOCTL_PDBIASEN_Msk          (0x1ul << CLK_LDOCTL_PDBIASEN_Pos)                /*!< CLK_T::LDOCTL: PDBIASEN Mask           */

#define CLK_SWKDBCTL_SWKDBCLKSEL_Pos     (0)                                               /*!< CLK_T::SWKDBCTL: SWKDBCLKSEL Position  */
#define CLK_SWKDBCTL_SWKDBCLKSEL_Msk     (0xful << CLK_SWKDBCTL_SWKDBCLKSEL_Pos)           /*!< CLK_T::SWKDBCTL: SWKDBCLKSEL Mask      */

#define CLK_PASWKCTL_WKEN_Pos            (0)                                               /*!< CLK_T::PASWKCTL: WKEN Position         */
#define CLK_PASWKCTL_WKEN_Msk            (0x1ul << CLK_PASWKCTL_WKEN_Pos)                  /*!< CLK_T::PASWKCTL: WKEN Mask             */

#define CLK_PASWKCTL_PRWKEN_Pos          (1)                                               /*!< CLK_T::PASWKCTL: PRWKEN Position       */
#define CLK_PASWKCTL_PRWKEN_Msk          (0x1ul << CLK_PASWKCTL_PRWKEN_Pos)                /*!< CLK_T::PASWKCTL: PRWKEN Mask           */

#define CLK_PASWKCTL_PFWKEN_Pos          (2)                                               /*!< CLK_T::PASWKCTL: PFWKEN Position       */
#define CLK_PASWKCTL_PFWKEN_Msk          (0x1ul << CLK_PASWKCTL_PFWKEN_Pos)                /*!< CLK_T::PASWKCTL: PFWKEN Mask           */

#define CLK_PASWKCTL_WKPSEL_Pos          (4)                                               /*!< CLK_T::PASWKCTL: WKPSEL Position       */
#define CLK_PASWKCTL_WKPSEL_Msk          (0xful << CLK_PASWKCTL_WKPSEL_Pos)                /*!< CLK_T::PASWKCTL: WKPSEL Mask           */

#define CLK_PASWKCTL_DBEN_Pos            (8)                                               /*!< CLK_T::PASWKCTL: DBEN Position         */
#define CLK_PASWKCTL_DBEN_Msk            (0x1ul << CLK_PASWKCTL_DBEN_Pos)                  /*!< CLK_T::PASWKCTL: DBEN Mask             */

#define CLK_PBSWKCTL_WKEN_Pos            (0)                                               /*!< CLK_T::PBSWKCTL: WKEN Position         */
#define CLK_PBSWKCTL_WKEN_Msk            (0x1ul << CLK_PBSWKCTL_WKEN_Pos)                  /*!< CLK_T::PBSWKCTL: WKEN Mask             */

#define CLK_PBSWKCTL_PRWKEN_Pos          (1)                                               /*!< CLK_T::PBSWKCTL: PRWKEN Position       */
#define CLK_PBSWKCTL_PRWKEN_Msk          (0x1ul << CLK_PBSWKCTL_PRWKEN_Pos)                /*!< CLK_T::PBSWKCTL: PRWKEN Mask           */

#define CLK_PBSWKCTL_PFWKEN_Pos          (2)                                               /*!< CLK_T::PBSWKCTL: PFWKEN Position       */
#define CLK_PBSWKCTL_PFWKEN_Msk          (0x1ul << CLK_PBSWKCTL_PFWKEN_Pos)                /*!< CLK_T::PBSWKCTL: PFWKEN Mask           */

#define CLK_PBSWKCTL_WKPSEL_Pos          (4)                                               /*!< CLK_T::PBSWKCTL: WKPSEL Position       */
#define CLK_PBSWKCTL_WKPSEL_Msk          (0xful << CLK_PBSWKCTL_WKPSEL_Pos)                /*!< CLK_T::PBSWKCTL: WKPSEL Mask           */

#define CLK_PBSWKCTL_DBEN_Pos            (8)                                               /*!< CLK_T::PBSWKCTL: DBEN Position         */
#define CLK_PBSWKCTL_DBEN_Msk            (0x1ul << CLK_PBSWKCTL_DBEN_Pos)                  /*!< CLK_T::PBSWKCTL: DBEN Mask             */

#define CLK_PCSWKCTL_WKEN_Pos            (0)                                               /*!< CLK_T::PCSWKCTL: WKEN Position         */
#define CLK_PCSWKCTL_WKEN_Msk            (0x1ul << CLK_PCSWKCTL_WKEN_Pos)                  /*!< CLK_T::PCSWKCTL: WKEN Mask             */

#define CLK_PCSWKCTL_PRWKEN_Pos          (1)                                               /*!< CLK_T::PCSWKCTL: PRWKEN Position       */
#define CLK_PCSWKCTL_PRWKEN_Msk          (0x1ul << CLK_PCSWKCTL_PRWKEN_Pos)                /*!< CLK_T::PCSWKCTL: PRWKEN Mask           */

#define CLK_PCSWKCTL_PFWKEN_Pos          (2)                                               /*!< CLK_T::PCSWKCTL: PFWKEN Position       */
#define CLK_PCSWKCTL_PFWKEN_Msk          (0x1ul << CLK_PCSWKCTL_PFWKEN_Pos)                /*!< CLK_T::PCSWKCTL: PFWKEN Mask           */

#define CLK_PCSWKCTL_WKPSEL_Pos          (4)                                               /*!< CLK_T::PCSWKCTL: WKPSEL Position       */
#define CLK_PCSWKCTL_WKPSEL_Msk          (0xful << CLK_PCSWKCTL_WKPSEL_Pos)                /*!< CLK_T::PCSWKCTL: WKPSEL Mask           */

#define CLK_PCSWKCTL_DBEN_Pos            (8)                                               /*!< CLK_T::PCSWKCTL: DBEN Position         */
#define CLK_PCSWKCTL_DBEN_Msk            (0x1ul << CLK_PCSWKCTL_DBEN_Pos)                  /*!< CLK_T::PCSWKCTL: DBEN Mask             */

#define CLK_PDSWKCTL_WKEN_Pos            (0)                                               /*!< CLK_T::PDSWKCTL: WKEN Position         */
#define CLK_PDSWKCTL_WKEN_Msk            (0x1ul << CLK_PDSWKCTL_WKEN_Pos)                  /*!< CLK_T::PDSWKCTL: WKEN Mask             */

#define CLK_PDSWKCTL_PRWKEN_Pos          (1)                                               /*!< CLK_T::PDSWKCTL: PRWKEN Position       */
#define CLK_PDSWKCTL_PRWKEN_Msk          (0x1ul << CLK_PDSWKCTL_PRWKEN_Pos)                /*!< CLK_T::PDSWKCTL: PRWKEN Mask           */

#define CLK_PDSWKCTL_PFWKEN_Pos          (2)                                               /*!< CLK_T::PDSWKCTL: PFWKEN Position       */
#define CLK_PDSWKCTL_PFWKEN_Msk          (0x1ul << CLK_PDSWKCTL_PFWKEN_Pos)                /*!< CLK_T::PDSWKCTL: PFWKEN Mask           */

#define CLK_PDSWKCTL_WKPSEL_Pos          (4)                                               /*!< CLK_T::PDSWKCTL: WKPSEL Position       */
#define CLK_PDSWKCTL_WKPSEL_Msk          (0xful << CLK_PDSWKCTL_WKPSEL_Pos)                /*!< CLK_T::PDSWKCTL: WKPSEL Mask           */

#define CLK_PDSWKCTL_DBEN_Pos            (8)                                               /*!< CLK_T::PDSWKCTL: DBEN Position         */
#define CLK_PDSWKCTL_DBEN_Msk            (0x1ul << CLK_PDSWKCTL_DBEN_Pos)                  /*!< CLK_T::PDSWKCTL: DBEN Mask             */

#define CLK_IOPDCTL_IOHR_Pos             (0)                                               /*!< CLK_T::IOPDCTL: IOHR Position          */
#define CLK_IOPDCTL_IOHR_Msk             (0x1ul << CLK_IOPDCTL_IOHR_Pos)                   /*!< CLK_T::IOPDCTL: IOHR Mask              */

/**@}*/ /* CLK_CONST */
/**@}*/ /* end of CLK register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __CLK_REG_H__ */
