/**************************************************************************//**
 * @file     sys_reg.h
 * @version  V1.00
 * @brief    SYS register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __SYS_REG_H__
#define __SYS_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup SYS System Manger Controller(SYS)
    Memory Mapped Structure for SYS Controller
@{ */

typedef struct
{


    /**
@var SYS_T::PDID

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PDID
</font><br><p> <font size="2">
Offset: 0x00  Part Device Identification Number Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>PDID</td><td><div style="word-wrap: break-word;"><b>Part Device Identification Number (Read Only)
</b><br>
This register reflects device part number code
<br>
Software can read this register to identify which device is used.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::RSTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">RSTSTS
</font><br><p> <font size="2">
Offset: 0x04  System Reset Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>PORF</td><td><div style="word-wrap: break-word;"><b>POR Reset Flag
</b><br>
The POR reset flag is set by the "Reset Signal" from the Power-on Reset (POR) Controller or bit CHIPRST (SYS_IPRST0[0]) to indicate the previous reset source.
<br>
0 = No reset from POR or CHIPRST.
<br>
1 = Power-on Reset (POR) or CHIPRST had issued the reset signal to reset the system.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[1]</td><td>PINRF</td><td><div style="word-wrap: break-word;"><b>NRESET Pin Reset Flag
</b><br>
The nRESET pin reset flag is set by the "Reset Signal" from the nRESET Pin to indicate the previous reset source.
<br>
0 = No reset from nRESET pin.
<br>
1 = Pin nRESET had issued the reset signal to reset the system.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[2]</td><td>WDTRF</td><td><div style="word-wrap: break-word;"><b>WDT Reset Flag
</b><br>
The WDT reset flag is set by the "Reset Signal" from the Watchdog Timer or Window Watchdog Timer to indicate the previous reset source.
<br>
0 = No reset from watchdog timer or window watchdog timer.
<br>
1 = The watchdog timer or window watchdog timer had issued the reset signal to reset the system.
<br>
Note1: Write 1 to clear this bit to 0.
<br>
Note2: Watchdog Timer register RSTF(WDT_CTL[2]) bit is set if the system has been reset by WDT time-out reset
<br>
Window Watchdog Timer register WWDTRF(WWDT_STATUS[1]) bit is set if the system has been reset by WWDT time-out reset.
<br>
</div></td></tr><tr><td>
[3]</td><td>LVRF</td><td><div style="word-wrap: break-word;"><b>LVR Reset Flag
</b><br>
The LVR reset flag is set by the "Reset Signal" from the Low Voltage Reset Controller to indicate the previous reset source.
<br>
0 = No reset from LVR.
<br>
1 = LVR controller had issued the reset signal to reset the system.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[4]</td><td>BODRF</td><td><div style="word-wrap: break-word;"><b>BOD Reset Flag
</b><br>
The BOD reset flag is set by the "Reset Signal" from the Brown-Out Detector to indicate the previous reset source.
<br>
0 = No reset from BOD.
<br>
1 = The BOD had issued the reset signal to reset the system.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[5]</td><td>SYSRF</td><td><div style="word-wrap: break-word;"><b>System Reset Flag
</b><br>
The system reset flag is set by the "Reset Signal" from the Cortex-M4 Core to indicate the previous reset source.
<br>
0 = No reset from Cortex-M4.
<br>
1 = The Cortex-M4 had issued the reset signal to reset the system by writing 1 to the bit SYSRESETREQ(AIRCR[2], Application Interrupt and Reset Control Register, address = 0xE000ED0C) in system control registers of Cortex-M4 core.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[7]</td><td>CPURF</td><td><div style="word-wrap: break-word;"><b>CPU Reset Flag
</b><br>
The CPU reset flag is set by hardware if software writes CPURST (SYS_IPRST0[1]) 1 to reset Cortex-M4 Core and Flash Memory Controller (FMC).
<br>
0 = No reset from CPU.
<br>
1 = The Cortex-M4 Core and FMC are reset by software setting CPURST to 1.
<br>
Note: Write to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[8]</td><td>CPULKRF</td><td><div style="word-wrap: break-word;"><b>CPU Lock-up Reset Flag
</b><br>
0 = No reset from CPU lock-up happened.
<br>
1 = The Cortex-M4 lock-up happened and chip is reset.
<br>
Note: Write 1 to clear this bit to 0.
<br>
Note2: When CPU lock-up happened under ICE is connected, This flag will set to 1 but chip will not reset.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::IPRST0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">IPRST0
</font><br><p> <font size="2">
Offset: 0x08  Peripheral  Reset Control Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CHIPRST</td><td><div style="word-wrap: break-word;"><b>Chip One-shot Reset (Write Protect)
</b><br>
Setting this bit will reset the whole chip, including Processor core and all peripherals, and this bit will automatically return to 0 after the 2 clock cycles.
<br>
The CHIPRST is same as the POR reset, all the chip controllers is reset and the chip setting from flash are also reload.
<br>
About the difference between CHIPRST and SYSRESETREQ(AIRCR[2]), please refer to section 6.2.2
<br>
0 = Chip normal operation.
<br>
1 = Chip one-shot reset.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[1]</td><td>CPURST</td><td><div style="word-wrap: break-word;"><b>Processor Core One-shot Reset (Write Protect)
</b><br>
Setting this bit will only reset the processor core and Flash Memory Controller(FMC), and this bit will automatically return to 0 after the 2 clock cycles.
<br>
0 = Processor core normal operation.
<br>
1 = Processor core one-shot reset.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[2]</td><td>PDMARST</td><td><div style="word-wrap: break-word;"><b>PDMA Controller Reset (Write Protect)
</b><br>
Setting this bit to 1 will generate a reset signal to the PDMA
<br>
User needs to set this bit to 0 to release from reset state.
<br>
0 = PDMA controller normal operation.
<br>
1 = PDMA controller reset.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[3]</td><td>EBIRST</td><td><div style="word-wrap: break-word;"><b>EBI Controller Reset (Write Protect)
</b><br>
Set this bit to 1 will generate a reset signal to the EBI
<br>
User needs to set this bit to 0 to release from the reset state.
<br>
0 = EBI controller normal operation.
<br>
1 = EBI controller reset.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[5]</td><td>EMACRST</td><td><div style="word-wrap: break-word;"><b>EMAC Controller Reset (Write Protect)
</b><br>
Setting this bit to 1 will generate a reset signal to the EMAC controller
<br>
User needs to set this bit to 0 to release from the reset state.
<br>
0 = EMAC controller normal operation.
<br>
1 = EMAC controller reset.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[6]</td><td>SDH0RST</td><td><div style="word-wrap: break-word;"><b>SDHOST0 Controller Reset (Write Protect)
</b><br>
Setting this bit to 1 will generate a reset signal to the SDHOST0 controller
<br>
User needs to set this bit to 0 to release from the reset state.
<br>
0 = SDHOST0 controller normal operation.
<br>
1 = SDHOST0 controller reset.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[7]</td><td>CRCRST</td><td><div style="word-wrap: break-word;"><b>CRC Calculation Controller Reset (Write Protect)
</b><br>
Set this bit to 1 will generate a reset signal to the CRC calculation controller
<br>
User needs to set this bit to 0 to release from the reset state.
<br>
0 = CRC calculation controller normal operation.
<br>
1 = CRC calculation controller reset.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[8]</td><td>CCAPRST</td><td><div style="word-wrap: break-word;"><b>CCAP Controller Reset (Write Protect)
</b><br>
Set this bit to 1 will generate a reset signal to the CCAP controller.
<br>
User needs to set this bit to 0 to release from the reset state.
<br>
0 = CCAP controller normal operation.
<br>
1 = CCAP controller reset.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[10]</td><td>HSUSBDRST</td><td><div style="word-wrap: break-word;"><b>HSUSBD Controller Reset (Write Protect)
</b><br>
Setting this bit to 1 will generate a reset signal to the HSUSBD controller
<br>
User needs to set this bit to 0 to release from the reset state.
<br>
0 = HSUSBD controller normal operation.
<br>
1 = HSUSBD controller reset.
<br>
</div></td></tr><tr><td>
[12]</td><td>CRPTRST</td><td><div style="word-wrap: break-word;"><b>CRYPTO Controller Reset (Write Protect)
</b><br>
Setting this bit to 1 will generate a reset signal to the CRYPTO controller
<br>
User needs to set this bit to 0 to release from the reset state.
<br>
0 = CRYPTO controller normal operation.
<br>
1 = CRYPTO controller reset.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[14]</td><td>SPIMRST</td><td><div style="word-wrap: break-word;"><b>SPIM Controller Reset
</b><br>
Setting this bit to 1 will generate a reset signal to the SPIM controller
<br>
User needs to set this bit to 0 to release from the reset state.
<br>
0 = SPIM controller normal operation.
<br>
1 = SPIM controller reset.
<br>
</div></td></tr><tr><td>
[16]</td><td>USBHRST</td><td><div style="word-wrap: break-word;"><b>USBH Controller Reset (Write Protect)
</b><br>
Set this bit to 1 will generate a reset signal to the USBH controller
<br>
User needs to set this bit to 0 to release from the reset state.
<br>
0 = USBH controller normal operation.
<br>
1 = USBH controller reset.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[17]</td><td>SDH1RST</td><td><div style="word-wrap: break-word;"><b>SDHOST1 Controller Reset (Write Protect)
</b><br>
Setting this bit to 1 will generate a reset signal to the SDHOST1 controller
<br>
User needs to set this bit to 0 to release from the reset state.
<br>
0 = SDHOST1 controller normal operation.
<br>
1 = SDHOST1 controller reset.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::IPRST1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">IPRST1
</font><br><p> <font size="2">
Offset: 0x0C  Peripheral Reset Control Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1]</td><td>GPIORST</td><td><div style="word-wrap: break-word;"><b>GPIO Controller Reset
</b><br>
0 = GPIO controller normal operation.
<br>
1 = GPIO controller reset.
<br>
</div></td></tr><tr><td>
[2]</td><td>TMR0RST</td><td><div style="word-wrap: break-word;"><b>Timer0 Controller Reset
</b><br>
0 = Timer0 controller normal operation.
<br>
1 = Timer0 controller reset.
<br>
</div></td></tr><tr><td>
[3]</td><td>TMR1RST</td><td><div style="word-wrap: break-word;"><b>Timer1 Controller Reset
</b><br>
0 = Timer1 controller normal operation.
<br>
1 = Timer1 controller reset.
<br>
</div></td></tr><tr><td>
[4]</td><td>TMR2RST</td><td><div style="word-wrap: break-word;"><b>Timer2 Controller Reset
</b><br>
0 = Timer2 controller normal operation.
<br>
1 = Timer2 controller reset.
<br>
</div></td></tr><tr><td>
[5]</td><td>TMR3RST</td><td><div style="word-wrap: break-word;"><b>Timer3 Controller Reset
</b><br>
0 = Timer3 controller normal operation.
<br>
1 = Timer3 controller reset.
<br>
</div></td></tr><tr><td>
[7]</td><td>ACMP01RST</td><td><div style="word-wrap: break-word;"><b>Analog Comparator 0/1 Controller Reset
</b><br>
0 = Analog Comparator 0/1 controller normal operation.
<br>
1 = Analog Comparator 0/1 controller reset.
<br>
</div></td></tr><tr><td>
[8]</td><td>I2C0RST</td><td><div style="word-wrap: break-word;"><b>I2C0 Controller Reset
</b><br>
0 = I2C0 controller normal operation.
<br>
1 = I2C0 controller reset.
<br>
</div></td></tr><tr><td>
[9]</td><td>I2C1RST</td><td><div style="word-wrap: break-word;"><b>I2C1 Controller Reset
</b><br>
0 = I2C1 controller normal operation.
<br>
1 = I2C1 controller reset.
<br>
</div></td></tr><tr><td>
[10]</td><td>I2C2RST</td><td><div style="word-wrap: break-word;"><b>I2C2 Controller Reset
</b><br>
0 = I2C2 controller normal operation.
<br>
1 = I2C2 controller reset.
<br>
</div></td></tr><tr><td>
[12]</td><td>QSPI0RST</td><td><div style="word-wrap: break-word;"><b>QSPI0 Controller Reset
</b><br>
0 = QSPI0 controller normal operation.
<br>
1 = QSPI0 controller reset.
<br>
</div></td></tr><tr><td>
[13]</td><td>SPI0RST</td><td><div style="word-wrap: break-word;"><b>SPI0 Controller Reset
</b><br>
0 = SPI0 controller normal operation.
<br>
1 = SPI0 controller reset.
<br>
</div></td></tr><tr><td>
[14]</td><td>SPI1RST</td><td><div style="word-wrap: break-word;"><b>SPI1 Controller Reset
</b><br>
0 = SPI1 controller normal operation.
<br>
1 = SPI1 controller reset.
<br>
</div></td></tr><tr><td>
[15]</td><td>SPI2RST</td><td><div style="word-wrap: break-word;"><b>SPI2 Controller Reset
</b><br>
0 = SPI2 controller normal operation.
<br>
1 = SPI2 controller reset.
<br>
</div></td></tr><tr><td>
[16]</td><td>UART0RST</td><td><div style="word-wrap: break-word;"><b>UART0 Controller Reset
</b><br>
0 = UART0 controller normal operation.
<br>
1 = UART0 controller reset.
<br>
</div></td></tr><tr><td>
[17]</td><td>UART1RST</td><td><div style="word-wrap: break-word;"><b>UART1 Controller Reset
</b><br>
0 = UART1 controller normal operation.
<br>
1 = UART1 controller reset.
<br>
</div></td></tr><tr><td>
[18]</td><td>UART2RST</td><td><div style="word-wrap: break-word;"><b>UART2 Controller Reset
</b><br>
0 = UART2 controller normal operation.
<br>
1 = UART2 controller reset.
<br>
</div></td></tr><tr><td>
[19]</td><td>UART3RST</td><td><div style="word-wrap: break-word;"><b>UART3 Controller Reset
</b><br>
0 = UART3 controller normal operation.
<br>
1 = UART3 controller reset.
<br>
</div></td></tr><tr><td>
[20]</td><td>UART4RST</td><td><div style="word-wrap: break-word;"><b>UART4 Controller Reset
</b><br>
0 = UART4 controller normal operation.
<br>
1 = UART4 controller reset.
<br>
</div></td></tr><tr><td>
[21]</td><td>UART5RST</td><td><div style="word-wrap: break-word;"><b>UART5 Controller Reset
</b><br>
0 = UART5 controller normal operation.
<br>
1 = UART5 controller reset.
<br>
</div></td></tr><tr><td>
[24]</td><td>CAN0RST</td><td><div style="word-wrap: break-word;"><b>CAN0 Controller Reset
</b><br>
0 = CAN0 controller normal operation.
<br>
1 = CAN0 controller reset.
<br>
</div></td></tr><tr><td>
[25]</td><td>CAN1RST</td><td><div style="word-wrap: break-word;"><b>CAN1 Controller Reset
</b><br>
0 = CAN1 controller normal operation.
<br>
1 = CAN1 controller reset.
<br>
</div></td></tr><tr><td>
[27]</td><td>USBDRST</td><td><div style="word-wrap: break-word;"><b>USBD Controller Reset
</b><br>
0 = USBD controller normal operation.
<br>
1 = USBD controller reset.
<br>
</div></td></tr><tr><td>
[28]</td><td>EADCRST</td><td><div style="word-wrap: break-word;"><b>EADC Controller Reset
</b><br>
0 = EADC controller normal operation.
<br>
1 = EADC controller reset.
<br>
</div></td></tr><tr><td>
[29]</td><td>I2S0RST</td><td><div style="word-wrap: break-word;"><b>I2S0 Controller Reset
</b><br>
0 = I2S0 controller normal operation.
<br>
1 = I2S0 controller reset.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::IPRST2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">IPRST2
</font><br><p> <font size="2">
Offset: 0x10  Peripheral Reset Control Register 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SC0RST</td><td><div style="word-wrap: break-word;"><b>SC0 Controller Reset
</b><br>
0 = SC0 controller normal operation.
<br>
1 = SC0 controller reset.
<br>
</div></td></tr><tr><td>
[1]</td><td>SC1RST</td><td><div style="word-wrap: break-word;"><b>SC1 Controller Reset
</b><br>
0 = SC1 controller normal operation.
<br>
1 = SC1 controller reset.
<br>
</div></td></tr><tr><td>
[2]</td><td>SC2RST</td><td><div style="word-wrap: break-word;"><b>SC2 Controller Reset
</b><br>
0 = SC2 controller normal operation.
<br>
1 = SC2 controller reset.
<br>
</div></td></tr><tr><td>
[6]</td><td>SPI3RST</td><td><div style="word-wrap: break-word;"><b>SPI3 Controller Reset
</b><br>
0 = SPI3 controller normal operation.
<br>
1 = SPI3 controller reset.
<br>
</div></td></tr><tr><td>
[8]</td><td>USCI0RST</td><td><div style="word-wrap: break-word;"><b>USCI0 Controller Reset
</b><br>
0 = USCI0 controller normal operation.
<br>
1 = USCI0 controller reset.
<br>
</div></td></tr><tr><td>
[9]</td><td>USCI1RST</td><td><div style="word-wrap: break-word;"><b>USCI1 Controller Reset
</b><br>
0 = USCI1 controller normal operation.
<br>
1 = USCI1 controller reset.
<br>
</div></td></tr><tr><td>
[12]</td><td>DACRST</td><td><div style="word-wrap: break-word;"><b>DAC Controller Reset
</b><br>
0 = DAC controller normal operation.
<br>
1 = DAC controller reset.
<br>
</div></td></tr><tr><td>
[16]</td><td>EPWM0RST</td><td><div style="word-wrap: break-word;"><b>EPWM0 Controller Reset
</b><br>
0 = EPWM0 controller normal operation.
<br>
1 = EPWM0 controller reset.
<br>
</div></td></tr><tr><td>
[17]</td><td>EPWM1RST</td><td><div style="word-wrap: break-word;"><b>EPWM1 Controller Reset
</b><br>
0 = EPWM1 controller normal operation.
<br>
1 = EPWM1 controller reset.
<br>
</div></td></tr><tr><td>
[18]</td><td>BPWM0RST</td><td><div style="word-wrap: break-word;"><b>BPWM0 Controller Reset
</b><br>
0 = BPWM0 controller normal operation.
<br>
1 = BPWM0 controller reset.
<br>
</div></td></tr><tr><td>
[19]</td><td>BPWM1RST</td><td><div style="word-wrap: break-word;"><b>BPWM1 Controller Reset
</b><br>
0 = BPWM1 controller normal operation.
<br>
1 = BPWM1 controller reset.
<br>
</div></td></tr><tr><td>
[22]</td><td>QEI0RST</td><td><div style="word-wrap: break-word;"><b>QEI0 Controller Reset
</b><br>
0 = QEI0 controller normal operation.
<br>
1 = QEI0 controller reset.
<br>
</div></td></tr><tr><td>
[23]</td><td>QEI1RST</td><td><div style="word-wrap: break-word;"><b>QEI1 Controller Reset
</b><br>
0 = QEI1 controller normal operation.
<br>
1 = QEI1 controller reset.
<br>
</div></td></tr><tr><td>
[26]</td><td>ECAP0RST</td><td><div style="word-wrap: break-word;"><b>ECAP0 Controller Reset
</b><br>
0 = ECAP0 controller normal operation.
<br>
1 = ECAP0 controller reset.
<br>
</div></td></tr><tr><td>
[27]</td><td>ECAP1RST</td><td><div style="word-wrap: break-word;"><b>ECAP1 Controller Reset
</b><br>
0 = ECAP1 controller normal operation.
<br>
1 = ECAP1 controller reset.
<br>
</div></td></tr><tr><td>
[28]</td><td>CAN2RST</td><td><div style="word-wrap: break-word;"><b>CAN2 Controller Reset
</b><br>
0 = CAN2 controller normal operation.
<br>
1 = CAN2 controller reset.
<br>
</div></td></tr><tr><td>
[30]</td><td>OPARST</td><td><div style="word-wrap: break-word;"><b>OP Amplifier (OPA) Controller Reset
</b><br>
0 = OPA controller normal operation.
<br>
1 = OPA controller reset.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::BODCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">BODCTL
</font><br><p> <font size="2">
Offset: 0x18  Brown-Out Detector Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BODEN</td><td><div style="word-wrap: break-word;"><b>Brown-out Detector Enable Bit (Write Protect)
</b><br>
The default value is set by flash controller user configuration register CBODEN(CONFIG0 [19]).
<br>
0 = Brown-out Detector function Disabled.
<br>
1 = Brown-out Detector function Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[3]</td><td>BODRSTEN</td><td><div style="word-wrap: break-word;"><b>Brown-out Reset Enable Bit (Write Protect)
</b><br>
The default value is set by flash controller user configuration register CBORST(CONFIG0[20]) bit .
<br>
0 = Brown-out INTERRUPT function Enabled.
<br>
1 = Brown-out RESET function Enabled.
<br>
Note1:
<br>
While the Brown-out Detector function is enabled (BODEN high) and BOD reset function is enabled (BODRSTEN high), BOD will assert a signal to reset chip when the detected voltage is lower than the threshold (BODOUT high).
<br>
While the BOD function is enabled (BODEN high) and BOD interrupt function is enabled (BODRSTEN low), BOD will assert an interrupt if BODOUT is high
<br>
BOD interrupt will keep till to the BODEN set to 0
<br>
BOD interrupt can be blocked by disabling the NVIC BOD interrupt or disabling BOD function (set BODEN low).
<br>
Note2: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[4]</td><td>BODIF</td><td><div style="word-wrap: break-word;"><b>Brown-out Detector Interrupt Flag
</b><br>
0 = Brown-out Detector does not detect any voltage draft at VDD down through or up through the voltage of BODVL setting.
<br>
1 = When Brown-out Detector detects the VDD is dropped down through the voltage of BODVL setting or the VDD is raised up through the voltage of BODVL setting, this bit is set to 1 and the brown-out interrupt is requested if brown-out interrupt is enabled.
<br>
Note: Write 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[5]</td><td>BODLPM</td><td><div style="word-wrap: break-word;"><b>Brown-out Detector Low Power Mode (Write Protect)
</b><br>
0 = BOD operate in normal mode (default).
<br>
1 = BOD Low Power mode Enabled.
<br>
Note1: The BOD consumes about 100uA in normal mode, the low power mode can reduce the current to about 1/10 but slow the BOD response.
<br>
Note2: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[6]</td><td>BODOUT</td><td><div style="word-wrap: break-word;"><b>Brown-out Detector Output Status
</b><br>
0 = Brown-out Detector output status is 0.
<br>
It means the detected voltage is higher than BODVL setting or BODEN is 0.
<br>
1 = Brown-out Detector output status is 1.
<br>
It means the detected voltage is lower than BODVL setting
<br>
If the BODEN is 0, BOD function disabled , this bit always responds 0000.
<br>
</div></td></tr><tr><td>
[7]</td><td>LVREN</td><td><div style="word-wrap: break-word;"><b>Low Voltage Reset Enable Bit (Write Protect)
</b><br>
The LVR function resets the chip when the input power voltage is lower than LVR circuit setting
<br>
LVR function is enabled by default.
<br>
0 = Low Voltage Reset function Disabled.
<br>
1 = Low Voltage Reset function Enabled.
<br>
Note1: After enabling the bit, the LVR function will be active with 100us delay for LVR output stable (default).
<br>
Note2: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[10:8]</td><td>BODDGSEL</td><td><div style="word-wrap: break-word;"><b>Brown-out Detector Output De-glitch Time Select (Write Protect)
</b><br>
000 = BOD output is sampled by RC10K clock.
<br>
001 = 4 system clock (HCLK).
<br>
010 = 8 system clock (HCLK).
<br>
011 = 16 system clock (HCLK).
<br>
100 = 32 system clock (HCLK).
<br>
101 = 64 system clock (HCLK).
<br>
110 = 128 system clock (HCLK).
<br>
111 = 256 system clock (HCLK).
<br>
Note: These bits are write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[14:12]</td><td>LVRDGSEL</td><td><div style="word-wrap: break-word;"><b>LVR Output De-glitch Time Select (Write Protect)
</b><br>
000 = Without de-glitch function.
<br>
001 = 4 system clock (HCLK).
<br>
010 = 8 system clock (HCLK).
<br>
011 = 16 system clock (HCLK).
<br>
100 = 32 system clock (HCLK).
<br>
101 = 64 system clock (HCLK).
<br>
110 = 128 system clock (HCLK).
<br>
111 = 256 system clock (HCLK).
<br>
Note: These bits are write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[18:16]</td><td>BODVL</td><td><div style="word-wrap: break-word;"><b>Brown-out Detector Threshold Voltage Selection (Write Protect)
</b><br>
The default value is set by flash controller user configuration register CBOV (CONFIG0 [23:21]).
<br>
000 = Brown-Out Detector threshold voltage is 1.6V.
<br>
001 = Brown-Out Detector threshold voltage is 1.8V.
<br>
010 = Brown-Out Detector threshold voltage is 2.0V.
<br>
011 = Brown-Out Detector threshold voltage is 2.2V.
<br>
100 = Brown-Out Detector threshold voltage is 2.4V.
<br>
101 = Brown-Out Detector threshold voltage is 2.6V.
<br>
110 = Brown-Out Detector threshold voltage is 2.8V.
<br>
111 = Brown-Out Detector threshold voltage is 3.0V.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::IVSCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">IVSCTL
</font><br><p> <font size="2">
Offset: 0x1C  Internal Voltage Source Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>VTEMPEN</td><td><div style="word-wrap: break-word;"><b>Temperature Sensor Enable Bit
</b><br>
This bit is used to enable/disable temperature sensor function.
<br>
0 = Temperature sensor function Disabled (default).
<br>
1 = Temperature sensor function Enabled.
<br>
Note: After this bit is set to 1, the value of temperature sensor output can be obtained through GPC.9.
<br>
</div></td></tr><tr><td>
[1]</td><td>VBATUGEN</td><td><div style="word-wrap: break-word;"><b>VBAT Unity Gain Buffer Enable Bit
</b><br>
This bit is used to enable/disable VBAT unity gain buffer function.
<br>
0 = VBAT unity gain buffer function Disabled (default).
<br>
1 = VBAT unity gain buffer function Enabled.
<br>
Note: After this bit is set to 1, the value of VBAT unity gain buffer output voltage can be obtained from ADC conversion result
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::PORCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PORCTL
</font><br><p> <font size="2">
Offset: 0x24  Power-On-Reset Controller Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>POROFF</td><td><div style="word-wrap: break-word;"><b>Power-on Reset Enable Bit (Write Protect)
</b><br>
When powered on, the POR circuit generates a reset signal to reset the whole chip function, but noise on the power may cause the POR active again
<br>
User can disable internal POR circuit to avoid unpredictable noise to cause chip reset by writing 0x5AA5 to this field.
<br>
The POR function will be active again when this field is set to another value or chip is reset by other reset source, including:
<br>
nRESET, Watchdog, LVR reset, BOD reset, ICE reset command and the software-chip reset function.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::VREFCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">VREFCTL
</font><br><p> <font size="2">
Offset: 0x28  VREF Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[4:0]</td><td>VREFCTL</td><td><div style="word-wrap: break-word;"><b>VREF Control Bits (Write Protect)
</b><br>
00000 = VREF is from external pin.
<br>
00011 = VREF is internal 1.6V.
<br>
00111 = VREF is internal 2.0V.
<br>
01011 = VREF is internal 2.5V.
<br>
01111 = VREF is internal 3.0V.
<br>
Others = Reserved.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[7:6]</td><td>PRELOAD_SEL</td><td><div style="word-wrap: break-word;"><b>Pre-load Timing Selection.
</b><br>
00 = pre-load time is 60us for 0.1uF Capacitor.
<br>
01 = pre-load time is 310us for 1uF Capacitor.
<br>
10 = pre-load time is 1270us for 4.7uF Capacitor.
<br>
11 = pre-load time is 2650us for 10uF Capacitor.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::USBPHY

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">USBPHY
</font><br><p> <font size="2">
Offset: 0x2C  USB PHY Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1:0]</td><td>USBROLE</td><td><div style="word-wrap: break-word;"><b>USB Role Option (Write Protect)
</b><br>
These two bits are used to select the role of USB.
<br>
00 = Standard USB Device mode.
<br>
01 = Standard USB Host mode.
<br>
10 = ID dependent mode.
<br>
11 = Reserved.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[2]</td><td>SBO</td><td><div style="word-wrap: break-word;"><b>Note: This bit must always be kept 1. If set to 0, the result is unpredictable
</b><br>
</div></td></tr><tr><td>
[8]</td><td>USBEN</td><td><div style="word-wrap: break-word;"><b>USB PHY Enable (Write Protect)
</b><br>
This bit is used to enable/disable USB PHY.
<br>
0 = USB PHY Disabled.
<br>
1 = USB PHY Enabled.
<br>
</div></td></tr><tr><td>
[17:16]</td><td>HSUSBROLE</td><td><div style="word-wrap: break-word;"><b>HSUSB Role Option (Write Protect)
</b><br>
These two bits are used to select the role of HSUSB
<br>
00 = Standard HSUSB Device mode.
<br>
01 = Standard HSUSB Host mode.
<br>
10 = ID dependent mode.
<br>
11 = Reserved.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[24]</td><td>HSUSBEN</td><td><div style="word-wrap: break-word;"><b>HSUSB PHY Enable (Write Protect)
</b><br>
This bit is used to enable/disable HSUSB PHY.
<br>
0 = HSUSB PHY Disabled.
<br>
1 = HSUSB PHY Enabled.
<br>
</div></td></tr><tr><td>
[25]</td><td>HSUSBACT</td><td><div style="word-wrap: break-word;"><b>HSUSB PHY Active Control
</b><br>
This bit is used to control HSUSB PHY at reset state or active state.
<br>
0 = HSUSB PHY at reset state.
<br>
1 = HSUSB PHY at active state.
<br>
Note: After set HSUSBEN (SYS_USBPHY[24]) to enable HSUSB PHY, user should keep HSUSB PHY at reset mode at lease 10uS before changing to active mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPA_MFPL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPA_MFPL
</font><br><p> <font size="2">
Offset: 0x30  GPIOA Low Byte Multiple Function Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>PA0MFP</td><td><div style="word-wrap: break-word;"><b>PA.0 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[7:4]</td><td>PA1MFP</td><td><div style="word-wrap: break-word;"><b>PA.1 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>PA2MFP</td><td><div style="word-wrap: break-word;"><b>PA.2 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[15:12]</td><td>PA3MFP</td><td><div style="word-wrap: break-word;"><b>PA.3 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>PA4MFP</td><td><div style="word-wrap: break-word;"><b>PA.4 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>PA5MFP</td><td><div style="word-wrap: break-word;"><b>PA.5 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[27:24]</td><td>PA6MFP</td><td><div style="word-wrap: break-word;"><b>PA.6 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[31:28]</td><td>PA7MFP</td><td><div style="word-wrap: break-word;"><b>PA.7 Multi-function Pin Selection
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPA_MFPH

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPA_MFPH
</font><br><p> <font size="2">
Offset: 0x34  GPIOA High Byte Multiple Function Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>PA8MFP</td><td><div style="word-wrap: break-word;"><b>PA.8 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[7:4]</td><td>PA9MFP</td><td><div style="word-wrap: break-word;"><b>PA.9 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>PA10MFP</td><td><div style="word-wrap: break-word;"><b>PA.10 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[15:12]</td><td>PA11MFP</td><td><div style="word-wrap: break-word;"><b>PA.11 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>PA12MFP</td><td><div style="word-wrap: break-word;"><b>PA.12 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>PA13MFP</td><td><div style="word-wrap: break-word;"><b>PA.13 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[27:24]</td><td>PA14MFP</td><td><div style="word-wrap: break-word;"><b>PA.14 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[31:28]</td><td>PA15MFP</td><td><div style="word-wrap: break-word;"><b>PA.15 Multi-function Pin Selection
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPB_MFPL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPB_MFPL
</font><br><p> <font size="2">
Offset: 0x38  GPIOB Low Byte Multiple Function Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>PB0MFP</td><td><div style="word-wrap: break-word;"><b>PB.0 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[7:4]</td><td>PB1MFP</td><td><div style="word-wrap: break-word;"><b>PB.1 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>PB2MFP</td><td><div style="word-wrap: break-word;"><b>PB.2 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[15:12]</td><td>PB3MFP</td><td><div style="word-wrap: break-word;"><b>PB.3 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>PB4MFP</td><td><div style="word-wrap: break-word;"><b>PB.4 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>PB5MFP</td><td><div style="word-wrap: break-word;"><b>PB.5 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[27:24]</td><td>PB6MFP</td><td><div style="word-wrap: break-word;"><b>PB.6 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[31:28]</td><td>PB7MFP</td><td><div style="word-wrap: break-word;"><b>PB.7 Multi-function Pin Selection
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPB_MFPH

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPB_MFPH
</font><br><p> <font size="2">
Offset: 0x3C  GPIOB High Byte Multiple Function Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>PB8MFP</td><td><div style="word-wrap: break-word;"><b>PB.8 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[7:4]</td><td>PB9MFP</td><td><div style="word-wrap: break-word;"><b>PB.9 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>PB10MFP</td><td><div style="word-wrap: break-word;"><b>PB.10 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[15:12]</td><td>PB11MFP</td><td><div style="word-wrap: break-word;"><b>PB.11 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>PB12MFP</td><td><div style="word-wrap: break-word;"><b>PB.12 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>PB13MFP</td><td><div style="word-wrap: break-word;"><b>PB.13 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[27:24]</td><td>PB14MFP</td><td><div style="word-wrap: break-word;"><b>PB.14 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[31:28]</td><td>PB15MFP</td><td><div style="word-wrap: break-word;"><b>PB.15 Multi-function Pin Selection
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPC_MFPL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPC_MFPL
</font><br><p> <font size="2">
Offset: 0x40  GPIOC Low Byte Multiple Function Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>PC0MFP</td><td><div style="word-wrap: break-word;"><b>PC.0 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[7:4]</td><td>PC1MFP</td><td><div style="word-wrap: break-word;"><b>PC.1 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>PC2MFP</td><td><div style="word-wrap: break-word;"><b>PC.2 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[15:12]</td><td>PC3MFP</td><td><div style="word-wrap: break-word;"><b>PC.3 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>PC4MFP</td><td><div style="word-wrap: break-word;"><b>PC.4 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>PC5MFP</td><td><div style="word-wrap: break-word;"><b>PC.5 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[27:24]</td><td>PC6MFP</td><td><div style="word-wrap: break-word;"><b>PC.6 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[31:28]</td><td>PC7MFP</td><td><div style="word-wrap: break-word;"><b>PC.7 Multi-function Pin Selection
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPC_MFPH

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPC_MFPH
</font><br><p> <font size="2">
Offset: 0x44  GPIOC High Byte Multiple Function Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>PC8MFP</td><td><div style="word-wrap: break-word;"><b>PC.8 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[7:4]</td><td>PC9MFP</td><td><div style="word-wrap: break-word;"><b>PC.9 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>PC10MFP</td><td><div style="word-wrap: break-word;"><b>PC.10 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[15:12]</td><td>PC11MFP</td><td><div style="word-wrap: break-word;"><b>PC.11 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>PC12MFP</td><td><div style="word-wrap: break-word;"><b>PC.12 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>PC13MFP</td><td><div style="word-wrap: break-word;"><b>PC.13 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[27:24]</td><td>PC14MFP</td><td><div style="word-wrap: break-word;"><b>PC.14 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[31:28]</td><td>PC15MFP</td><td><div style="word-wrap: break-word;"><b>PC.15 Multi-function Pin Selection
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPD_MFPL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPD_MFPL
</font><br><p> <font size="2">
Offset: 0x48  GPIOD Low Byte Multiple Function Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>PD0MFP</td><td><div style="word-wrap: break-word;"><b>PD.0 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[7:4]</td><td>PD1MFP</td><td><div style="word-wrap: break-word;"><b>PD.1 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>PD2MFP</td><td><div style="word-wrap: break-word;"><b>PD.2 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[15:12]</td><td>PD3MFP</td><td><div style="word-wrap: break-word;"><b>PD.3 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>PD4MFP</td><td><div style="word-wrap: break-word;"><b>PD.4 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>PD5MFP</td><td><div style="word-wrap: break-word;"><b>PD.5 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[27:24]</td><td>PD6MFP</td><td><div style="word-wrap: break-word;"><b>PD.6 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[31:28]</td><td>PD7MFP</td><td><div style="word-wrap: break-word;"><b>PD.7 Multi-function Pin Selection
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPD_MFPH

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPD_MFPH
</font><br><p> <font size="2">
Offset: 0x4C  GPIOD High Byte Multiple Function Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>PD8MFP</td><td><div style="word-wrap: break-word;"><b>PD.8 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[7:4]</td><td>PD9MFP</td><td><div style="word-wrap: break-word;"><b>PD.9 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>PD10MFP</td><td><div style="word-wrap: break-word;"><b>PD.10 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[15:12]</td><td>PD11MFP</td><td><div style="word-wrap: break-word;"><b>PD.11 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>PD12MFP</td><td><div style="word-wrap: break-word;"><b>PD.12 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>PD13MFP</td><td><div style="word-wrap: break-word;"><b>PD.13 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[27:24]</td><td>PD14MFP</td><td><div style="word-wrap: break-word;"><b>PD.14 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[31:28]</td><td>PD15MFP</td><td><div style="word-wrap: break-word;"><b>PD.15 Multi-function Pin Selection
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPE_MFPL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPE_MFPL
</font><br><p> <font size="2">
Offset: 0x50  GPIOE Low Byte Multiple Function Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>PE0MFP</td><td><div style="word-wrap: break-word;"><b>PE.0 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[7:4]</td><td>PE1MFP</td><td><div style="word-wrap: break-word;"><b>PE.1 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>PE2MFP</td><td><div style="word-wrap: break-word;"><b>PE.2 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[15:12]</td><td>PE3MFP</td><td><div style="word-wrap: break-word;"><b>PE.3 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>PE4MFP</td><td><div style="word-wrap: break-word;"><b>PE.4 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>PE5MFP</td><td><div style="word-wrap: break-word;"><b>PE.5 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[27:24]</td><td>PE6MFP</td><td><div style="word-wrap: break-word;"><b>PE.6 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[31:28]</td><td>PE7MFP</td><td><div style="word-wrap: break-word;"><b>PE.7 Multi-function Pin Selection
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPE_MFPH

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPE_MFPH
</font><br><p> <font size="2">
Offset: 0x54  GPIOE High Byte Multiple Function Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>PE8MFP</td><td><div style="word-wrap: break-word;"><b>PE.8 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[7:4]</td><td>PE9MFP</td><td><div style="word-wrap: break-word;"><b>PE.9 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>PE10MFP</td><td><div style="word-wrap: break-word;"><b>PE.10 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[15:12]</td><td>PE11MFP</td><td><div style="word-wrap: break-word;"><b>PE.11 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>PE12MFP</td><td><div style="word-wrap: break-word;"><b>PE.12 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>PE13MFP</td><td><div style="word-wrap: break-word;"><b>PE.13 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[27:24]</td><td>PE14MFP</td><td><div style="word-wrap: break-word;"><b>PE.14 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[31:28]</td><td>PE15MFP</td><td><div style="word-wrap: break-word;"><b>PE.15 Multi-function Pin Selection
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPF_MFPL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPF_MFPL
</font><br><p> <font size="2">
Offset: 0x58  GPIOF Low Byte Multiple Function Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>PF0MFP</td><td><div style="word-wrap: break-word;"><b>PF.0 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[7:4]</td><td>PF1MFP</td><td><div style="word-wrap: break-word;"><b>PF.1 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>PF2MFP</td><td><div style="word-wrap: break-word;"><b>PF.2 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[15:12]</td><td>PF3MFP</td><td><div style="word-wrap: break-word;"><b>PF.3 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>PF4MFP</td><td><div style="word-wrap: break-word;"><b>PF.4 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>PF5MFP</td><td><div style="word-wrap: break-word;"><b>PF.5 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[27:24]</td><td>PF6MFP</td><td><div style="word-wrap: break-word;"><b>PF.6 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[31:28]</td><td>PF7MFP</td><td><div style="word-wrap: break-word;"><b>PF.7 Multi-function Pin Selection
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPF_MFPH

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPF_MFPH
</font><br><p> <font size="2">
Offset: 0x5C  GPIOF High Byte Multiple Function Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>PF8MFP</td><td><div style="word-wrap: break-word;"><b>PF.8 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[7:4]</td><td>PF9MFP</td><td><div style="word-wrap: break-word;"><b>PF.9 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>PF10MFP</td><td><div style="word-wrap: break-word;"><b>PF.10 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[15:12]</td><td>PF11MFP</td><td><div style="word-wrap: break-word;"><b>PF.11 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>PF12MFP</td><td><div style="word-wrap: break-word;"><b>PF.12 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>PF13MFP</td><td><div style="word-wrap: break-word;"><b>PF.13 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[27:24]</td><td>PF14MFP</td><td><div style="word-wrap: break-word;"><b>PF.14 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[31:28]</td><td>PF15MFP</td><td><div style="word-wrap: break-word;"><b>PF.15 Multi-function Pin Selection
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPG_MFPL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPG_MFPL
</font><br><p> <font size="2">
Offset: 0x60  GPIOG Low Byte Multiple Function Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>PG0MFP</td><td><div style="word-wrap: break-word;"><b>PG.0 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[7:4]</td><td>PG1MFP</td><td><div style="word-wrap: break-word;"><b>PG.1 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>PG2MFP</td><td><div style="word-wrap: break-word;"><b>PG.2 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[15:12]</td><td>PG3MFP</td><td><div style="word-wrap: break-word;"><b>PG.3 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>PG4MFP</td><td><div style="word-wrap: break-word;"><b>PG.4 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>PG5MFP</td><td><div style="word-wrap: break-word;"><b>PG.5 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[27:24]</td><td>PG6MFP</td><td><div style="word-wrap: break-word;"><b>PG.6 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[31:28]</td><td>PG7MFP</td><td><div style="word-wrap: break-word;"><b>PG.7 Multi-function Pin Selection
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPG_MFPH

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPG_MFPH
</font><br><p> <font size="2">
Offset: 0x64  GPIOG High Byte Multiple Function Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>PG8MFP</td><td><div style="word-wrap: break-word;"><b>PG.8 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[7:4]</td><td>PG9MFP</td><td><div style="word-wrap: break-word;"><b>PG.9 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>PG10MFP</td><td><div style="word-wrap: break-word;"><b>PG.10 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[15:12]</td><td>PG11MFP</td><td><div style="word-wrap: break-word;"><b>PG.11 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>PG12MFP</td><td><div style="word-wrap: break-word;"><b>PG.12 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>PG13MFP</td><td><div style="word-wrap: break-word;"><b>PG.13 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[27:24]</td><td>PG14MFP</td><td><div style="word-wrap: break-word;"><b>PG.14 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[31:28]</td><td>PG15MFP</td><td><div style="word-wrap: break-word;"><b>PG.15 Multi-function Pin Selection
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPH_MFPL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPH_MFPL
</font><br><p> <font size="2">
Offset: 0x68  GPIOH Low Byte Multiple Function Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>PH0MFP</td><td><div style="word-wrap: break-word;"><b>PH.0 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[7:4]</td><td>PH1MFP</td><td><div style="word-wrap: break-word;"><b>PH.1 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>PH2MFP</td><td><div style="word-wrap: break-word;"><b>PH.2 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[15:12]</td><td>PH3MFP</td><td><div style="word-wrap: break-word;"><b>PH.3 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>PH4MFP</td><td><div style="word-wrap: break-word;"><b>PH.4 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>PH5MFP</td><td><div style="word-wrap: break-word;"><b>PH.5 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[27:24]</td><td>PH6MFP</td><td><div style="word-wrap: break-word;"><b>PH.6 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[31:28]</td><td>PH7MFP</td><td><div style="word-wrap: break-word;"><b>PH.7 Multi-function Pin Selection
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPH_MFPH

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPH_MFPH
</font><br><p> <font size="2">
Offset: 0x6C  GPIOH High Byte Multiple Function Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>PH8MFP</td><td><div style="word-wrap: break-word;"><b>PH.8 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[7:4]</td><td>PH9MFP</td><td><div style="word-wrap: break-word;"><b>PH.9 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[11:8]</td><td>PH10MFP</td><td><div style="word-wrap: break-word;"><b>PH.10 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[15:12]</td><td>PH11MFP</td><td><div style="word-wrap: break-word;"><b>PH.11 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[19:16]</td><td>PH12MFP</td><td><div style="word-wrap: break-word;"><b>PH.12 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[23:20]</td><td>PH13MFP</td><td><div style="word-wrap: break-word;"><b>PH.13 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[27:24]</td><td>PH14MFP</td><td><div style="word-wrap: break-word;"><b>PH.14 Multi-function Pin Selection
</b><br>
</div></td></tr><tr><td>
[31:28]</td><td>PH15MFP</td><td><div style="word-wrap: break-word;"><b>PH.15 Multi-function Pin Selection
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPA_MFOS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPA_MFOS
</font><br><p> <font size="2">
Offset: 0x80  GPIOA Multiple Function Output Select Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>MFOS0</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[1]</td><td>MFOS1</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[2]</td><td>MFOS2</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[3]</td><td>MFOS3</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[4]</td><td>MFOS4</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[5]</td><td>MFOS5</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[6]</td><td>MFOS6</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[7]</td><td>MFOS7</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[8]</td><td>MFOS8</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[9]</td><td>MFOS9</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[10]</td><td>MFOS10</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[11]</td><td>MFOS11</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[12]</td><td>MFOS12</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[13]</td><td>MFOS13</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[14]</td><td>MFOS14</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[15]</td><td>MFOS15</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPB_MFOS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPB_MFOS
</font><br><p> <font size="2">
Offset: 0x84  GPIOB Multiple Function Output Select Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>MFOS0</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[1]</td><td>MFOS1</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[2]</td><td>MFOS2</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[3]</td><td>MFOS3</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[4]</td><td>MFOS4</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[5]</td><td>MFOS5</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[6]</td><td>MFOS6</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[7]</td><td>MFOS7</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[8]</td><td>MFOS8</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[9]</td><td>MFOS9</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[10]</td><td>MFOS10</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[11]</td><td>MFOS11</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[12]</td><td>MFOS12</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[13]</td><td>MFOS13</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[14]</td><td>MFOS14</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[15]</td><td>MFOS15</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPC_MFOS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPC_MFOS
</font><br><p> <font size="2">
Offset: 0x88  GPIOC Multiple Function Output Select Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>MFOS0</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[1]</td><td>MFOS1</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[2]</td><td>MFOS2</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[3]</td><td>MFOS3</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[4]</td><td>MFOS4</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[5]</td><td>MFOS5</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[6]</td><td>MFOS6</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[7]</td><td>MFOS7</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[8]</td><td>MFOS8</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[9]</td><td>MFOS9</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[10]</td><td>MFOS10</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[11]</td><td>MFOS11</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[12]</td><td>MFOS12</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[13]</td><td>MFOS13</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[14]</td><td>MFOS14</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[15]</td><td>MFOS15</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPD_MFOS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPD_MFOS
</font><br><p> <font size="2">
Offset: 0x8C  GPIOD Multiple Function Output Select Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>MFOS0</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[1]</td><td>MFOS1</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[2]</td><td>MFOS2</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[3]</td><td>MFOS3</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[4]</td><td>MFOS4</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[5]</td><td>MFOS5</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[6]</td><td>MFOS6</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[7]</td><td>MFOS7</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[8]</td><td>MFOS8</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[9]</td><td>MFOS9</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[10]</td><td>MFOS10</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[11]</td><td>MFOS11</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[12]</td><td>MFOS12</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[13]</td><td>MFOS13</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[14]</td><td>MFOS14</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[15]</td><td>MFOS15</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPE_MFOS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPE_MFOS
</font><br><p> <font size="2">
Offset: 0x90  GPIOE Multiple Function Output Select Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>MFOS0</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[1]</td><td>MFOS1</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[2]</td><td>MFOS2</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[3]</td><td>MFOS3</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[4]</td><td>MFOS4</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[5]</td><td>MFOS5</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[6]</td><td>MFOS6</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[7]</td><td>MFOS7</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[8]</td><td>MFOS8</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[9]</td><td>MFOS9</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[10]</td><td>MFOS10</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[11]</td><td>MFOS11</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[12]</td><td>MFOS12</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[13]</td><td>MFOS13</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[14]</td><td>MFOS14</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[15]</td><td>MFOS15</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPF_MFOS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPF_MFOS
</font><br><p> <font size="2">
Offset: 0x94  GPIOF Multiple Function Output Select Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>MFOS0</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[1]</td><td>MFOS1</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[2]</td><td>MFOS2</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[3]</td><td>MFOS3</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[4]</td><td>MFOS4</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[5]</td><td>MFOS5</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[6]</td><td>MFOS6</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[7]</td><td>MFOS7</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[8]</td><td>MFOS8</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[9]</td><td>MFOS9</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[10]</td><td>MFOS10</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[11]</td><td>MFOS11</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[12]</td><td>MFOS12</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[13]</td><td>MFOS13</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[14]</td><td>MFOS14</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[15]</td><td>MFOS15</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPG_MFOS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPG_MFOS
</font><br><p> <font size="2">
Offset: 0x98  GPIOG Multiple Function Output Select Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>MFOS0</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[1]</td><td>MFOS1</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[2]</td><td>MFOS2</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[3]</td><td>MFOS3</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[4]</td><td>MFOS4</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[5]</td><td>MFOS5</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[6]</td><td>MFOS6</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[7]</td><td>MFOS7</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[8]</td><td>MFOS8</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[9]</td><td>MFOS9</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[10]</td><td>MFOS10</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[11]</td><td>MFOS11</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[12]</td><td>MFOS12</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[13]</td><td>MFOS13</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[14]</td><td>MFOS14</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[15]</td><td>MFOS15</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::GPH_MFOS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">GPH_MFOS
</font><br><p> <font size="2">
Offset: 0x9C  GPIOH Multiple Function Output Select Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>MFOS0</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[1]</td><td>MFOS1</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[2]</td><td>MFOS2</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[3]</td><td>MFOS3</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[4]</td><td>MFOS4</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[5]</td><td>MFOS5</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[6]</td><td>MFOS6</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[7]</td><td>MFOS7</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[8]</td><td>MFOS8</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[9]</td><td>MFOS9</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[10]</td><td>MFOS10</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[11]</td><td>MFOS11</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[12]</td><td>MFOS12</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[13]</td><td>MFOS13</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[14]</td><td>MFOS14</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr><tr><td>
[15]</td><td>MFOS15</td><td><div style="word-wrap: break-word;"><b>GPIOA-H Pin[n] Multiple Function Pin Output Mode Select
</b><br>
This bit used to select multiple function pin output mode type for Px.n pin
<br>
0 = Multiple function pin output mode type is Push-pull mode.
<br>
1 = Multiple function pin output mode type is Open-drain mode.
<br>
Note:
<br>
Max. n=15 for port A/B/E/G.
<br>
Max. n=14 for port C/D.
<br>
Max. n=11 for port F/H.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::SRAM_INTCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SRAM_INTCTL
</font><br><p> <font size="2">
Offset: 0xC0  System SRAM Interrupt Enable Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>PERRIEN</td><td><div style="word-wrap: break-word;"><b>SRAM Parity Check Error Interrupt Enable Bit
</b><br>
0 = SRAM parity check error interrupt Disabled.
<br>
1 = SRAM parity check error interrupt Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::SRAM_STATUS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SRAM_STATUS
</font><br><p> <font size="2">
Offset: 0xC4  System SRAM Parity Error Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>PERRIF</td><td><div style="word-wrap: break-word;"><b>SRAM Parity Check Error Flag
</b><br>
This bit indicates the System SRAM parity error occurred. Write 1 to clear this to 0.
<br>
0 = No System SRAM parity error.
<br>
1 = System SRAM parity error occur.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::SRAM_ERRADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SRAM_ERRADDR
</font><br><p> <font size="2">
Offset: 0xC8  System SRAM Parity Check Error Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>ERRADDR</td><td><div style="word-wrap: break-word;"><b>System SRAM Parity Error Address
</b><br>
This register shows system SRAM parity error byte address.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::SRAM_BISTCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SRAM_BISTCTL
</font><br><p> <font size="2">
Offset: 0xD0  System SRAM BIST Test Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SRBIST0</td><td><div style="word-wrap: break-word;"><b>SRAM Bank0 BIST Enable Bit (Write Protect)
</b><br>
This bit enables BIST test for SRAM bank0.
<br>
0 = system SRAM bank0 BIST Disabled.
<br>
1 = system SRAM bank0 BIST Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[1]</td><td>SRBIST1</td><td><div style="word-wrap: break-word;"><b>SRAM Bank1 BIST Enable Bit (Write Protect)
</b><br>
This bit enables BIST test for SRAM bank1.
<br>
0 = system SRAM bank1 BIST Disabled.
<br>
1 = system SRAM bank1 BIST Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[2]</td><td>CRBIST</td><td><div style="word-wrap: break-word;"><b>CACHE BIST Enable Bit (Write Protect)
</b><br>
This bit enables BIST test for CACHE RAM
<br>
0 = system CACHE BIST Disabled.
<br>
1 = system CACHE BIST Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[3]</td><td>CANBIST</td><td><div style="word-wrap: break-word;"><b>CAN BIST Enable Bit (Write Protect)
</b><br>
This bit enables BIST test for CAN RAM
<br>
0 = system CAN BIST Disabled.
<br>
1 = system CAN BIST Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[4]</td><td>USBBIST</td><td><div style="word-wrap: break-word;"><b>USB BIST Enable Bit (Write Protect)
</b><br>
This bit enables BIST test for USB RAM
<br>
0 = system USB BIST Disabled.
<br>
1 = system USB BIST Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[5]</td><td>SPIMBIST</td><td><div style="word-wrap: break-word;"><b>SPIM BIST Enable Bit (Write Protect)
</b><br>
This bit enables BIST test for SPIM RAM
<br>
0 = system SPIM BIST Disabled.
<br>
1 = system SPIM BIST Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[6]</td><td>EMCBIST</td><td><div style="word-wrap: break-word;"><b>EMC BIST Enable Bit (Write Protect)
</b><br>
This bit enables BIST test for EMC RAM
<br>
0 = system EMC BIST Disabled.
<br>
1 = system EMC BIST Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[7]</td><td>PDMABIST</td><td><div style="word-wrap: break-word;"><b>PDMA BIST Enable Bit (Write Protect)
</b><br>
This bit enables BIST test for PDMA RAM
<br>
0 = system PDMA BIST Disabled.
<br>
1 = system PDMA BIST Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[8]</td><td>HSUSBDBIST</td><td><div style="word-wrap: break-word;"><b>HSUSBD BIST Enable Bit (Write Protect)
</b><br>
This bit enables BIST test for HSUSBD RAM
<br>
0 = system HSUSBD BIST Disabled.
<br>
1 = system HSUSBD BIST Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[9]</td><td>HSUSBHBIST</td><td><div style="word-wrap: break-word;"><b>HSUSBH BIST Enable Bit (Write Protect)
</b><br>
This bit enables BIST test for HSUSBH RAM
<br>
0 = system HSUSBH BIST Disabled.
<br>
1 = system HSUSBH BIST Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[16]</td><td>SRB0S0</td><td><div style="word-wrap: break-word;"><b>SRAM Bank0 Section 0 BIST Select (Write Protect)
</b><br>
This bit define if the first 16KB section of SRAM bank0 is selected or not when doing bist test.
<br>
0 = SRAM bank0 section 0 is deselected when doing bist test.
<br>
1 = SRAM bank0 section 0 is selected when doing bist test.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
Note: At least one section of SRAM bank0 should be selected when doing SRAM bank0 bist test.
<br>
</div></td></tr><tr><td>
[17]</td><td>SRB0S1</td><td><div style="word-wrap: break-word;"><b>SRAM Bank0 Section 1 BIST Select (Write Protect)
</b><br>
This bit define if the second 16KB section of SRAM bank0 is selected or not when doing bist test.
<br>
0 = SRAM bank0 section 1 is deselected when doing bist test.
<br>
1 = SRAM bank0 section 1 is selected when doing bist test.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
Note: At least one section of SRAM bank0 should be selected when doing SRAM bank0 bist test.
<br>
</div></td></tr><tr><td>
[18]</td><td>SRB1S0</td><td><div style="word-wrap: break-word;"><b>SRAM Bank1 Section 0 BIST Select (Write Protect)
</b><br>
This bit define if the first 16KB section of SRAM bank1 is selected or not when doing bist test.
<br>
0 = SRAM bank1 first 16KB section is deselected when doing bist test.
<br>
1 = SRAM bank1 first 16KB section is selected when doing bist test.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
Note: At least one section of SRAM bank1 should be selected when doing SRAM bank1 bist test.
<br>
</div></td></tr><tr><td>
[19]</td><td>SRB1S1</td><td><div style="word-wrap: break-word;"><b>SRAM Bank1 Section 1 BIST Select (Write Protect)
</b><br>
This bit define if the second 16KB section of SRAM bank1 is selected or not when doing bist test.
<br>
0 = SRAM bank1 second 16KB section is deselected when doing bist test.
<br>
1 = SRAM bank1 second 16KB section is selected when doing bist test.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
Note: At least one section of SRAM bank1 should be selected when doing SRAM bank1 bist test.
<br>
</div></td></tr><tr><td>
[20]</td><td>SRB1S2</td><td><div style="word-wrap: break-word;"><b>SRAM Bank1 Section 0 BIST Select (Write Protect)
</b><br>
This bit define if the third 16KB section of SRAM bank1 is selected or not when doing bist test.
<br>
0 = SRAM bank1 third 16KB section is deselected when doing bist test.
<br>
1 = SRAM bank1 third 16KB section is selected when doing bist test.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
Note: At least one section of SRAM bank1 should be selected when doing SRAM bank1 bist test.
<br>
</div></td></tr><tr><td>
[21]</td><td>SRB1S3</td><td><div style="word-wrap: break-word;"><b>SRAM Bank1 Section 1 BIST Select (Write Protect)
</b><br>
This bit define if the fourth 16KB section of SRAM bank1 is selected or not when doing bist test.
<br>
0 = SRAM bank1 fourth 16KB section is deselected when doing bist test.
<br>
1 = SRAM bank1 fourth 16KB section is selected when doing bist test.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
Note: At least one section of SRAM bank1 should be selected when doing SRAM bank1 bist test.
<br>
</div></td></tr><tr><td>
[22]</td><td>SRB1S4</td><td><div style="word-wrap: break-word;"><b>SRAM Bank1 Section 0 BIST Select (Write Protect)
</b><br>
This bit define if the fifth 16KB section of SRAM bank1 is selected or not when doing bist test.
<br>
0 = SRAM bank1 fifth 16KB section is deselected when doing bist test.
<br>
1 = SRAM bank1 fifth 16KB section is selected when doing bist test.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
Note: At least one section of SRAM bank1 should be selected when doing SRAM bank1 bist test.
<br>
</div></td></tr><tr><td>
[23]</td><td>SRB1S5</td><td><div style="word-wrap: break-word;"><b>SRAM Bank1 Section 1 BIST Select (Write Protect)
</b><br>
This bit define if the sixth 16KB section of SRAM bank1 is selected or not when doing bist test.
<br>
0 = SRAM bank1 sixth 16KB section is deselected when doing bist test.
<br>
1 = SRAM bank1 sixth 16KB section is selected when doing bist test.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
Note: At least one section of SRAM bank1 should be selected when doing SRAM bank1 bist test.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::SRAM_BISTSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SRAM_BISTSTS
</font><br><p> <font size="2">
Offset: 0xD4  System SRAM BIST Test Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SRBISTEF0</td><td><div style="word-wrap: break-word;"><b>1st System SRAM BIST Fail Flag
</b><br>
0 = 1st system SRAM BIST test pass.
<br>
1 = 1st system SRAM BIST test fail.
<br>
</div></td></tr><tr><td>
[1]</td><td>SRBISTEF1</td><td><div style="word-wrap: break-word;"><b>2nd System SRAM BIST Fail Flag
</b><br>
0 = 2nd system SRAM BIST test pass.
<br>
1 = 2nd system SRAM BIST test fail.
<br>
</div></td></tr><tr><td>
[2]</td><td>CRBISTEF</td><td><div style="word-wrap: break-word;"><b>CACHE SRAM BIST Fail Flag
</b><br>
0 = System CACHE RAM BIST test pass.
<br>
1 = System CACHE RAM BIST test fail.
<br>
</div></td></tr><tr><td>
[3]</td><td>CANBEF</td><td><div style="word-wrap: break-word;"><b>CAN SRAM BIST Fail Flag
</b><br>
0 = CAN SRAM BIST test pass.
<br>
1 = CAN SRAM BIST test fail.
<br>
</div></td></tr><tr><td>
[4]</td><td>USBBEF</td><td><div style="word-wrap: break-word;"><b>USB SRAM BIST Fail Flag
</b><br>
0 = USB SRAM BIST test pass.
<br>
1 = USB SRAM BIST test fail.
<br>
</div></td></tr><tr><td>
[16]</td><td>SRBEND0</td><td><div style="word-wrap: break-word;"><b>1st SRAM BIST Test Finish
</b><br>
0 = 1st system SRAM BIST active.
<br>
1 =1st system SRAM BIST finish.
<br>
</div></td></tr><tr><td>
[17]</td><td>SRBEND1</td><td><div style="word-wrap: break-word;"><b>2nd SRAM BIST Test Finish
</b><br>
0 = 2nd system SRAM BIST is active.
<br>
1 = 2nd system SRAM BIST finish.
<br>
</div></td></tr><tr><td>
[18]</td><td>CRBEND</td><td><div style="word-wrap: break-word;"><b>CACHE SRAM BIST Test Finish
</b><br>
0 = System CACHE RAM BIST is active.
<br>
1 = System CACHE RAM BIST test finish.
<br>
</div></td></tr><tr><td>
[19]</td><td>CANBEND</td><td><div style="word-wrap: break-word;"><b>CAN SRAM BIST Test Finish
</b><br>
0 = CAN SRAM BIST is active.
<br>
1 = CAN SRAM BIST test finish.
<br>
</div></td></tr><tr><td>
[20]</td><td>USBBEND</td><td><div style="word-wrap: break-word;"><b>USB SRAM BIST Test Finish
</b><br>
0 = USB SRAM BIST is active.
<br>
1 = USB SRAM BIST test finish.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::HIRCTCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HIRCTCTL
</font><br><p> <font size="2">
Offset: 0xE4  HIRC48M Trim Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1:0]</td><td>FREQSEL</td><td><div style="word-wrap: break-word;"><b>Trim Frequency Selection
</b><br>
This field indicates the target frequency of 48 MHz internal high speed RC oscillator (HIRC) auto trim.
<br>
During auto trim operation, if clock error detected with CESTOPEN is set to 1 or trim retry limitation count reached, this field will be cleared to 00 automatically.
<br>
00 = Disable HIRC auto trim function.
<br>
01 = Enable HIRC auto trim function and trim HIRC to 48 MHz.
<br>
10 = Reserved..
<br>
11 = Reserved.
<br>
</div></td></tr><tr><td>
[5:4]</td><td>LOOPSEL</td><td><div style="word-wrap: break-word;"><b>Trim Calculation Loop Selection
</b><br>
This field defines that trim value calculation is based on how many reference clocks.
<br>
00 = Trim value calculation is based on average difference in 4 clocks of reference clock.
<br>
01 = Trim value calculation is based on average difference in 8 clocks of reference clock.
<br>
10 = Trim value calculation is based on average difference in 16 clocks of reference clock.
<br>
11 = Trim value calculation is based on average difference in 32 clocks of reference clock.
<br>
Note: For example, if LOOPSEL is set as 00, auto trim circuit will calculate trim value based on the average frequency difference in 4 clocks of reference clock.
<br>
</div></td></tr><tr><td>
[7:6]</td><td>RETRYCNT</td><td><div style="word-wrap: break-word;"><b>Trim Value Update Limitation Count
</b><br>
This field defines that how many times the auto trim circuit will try to update the HIRC trim value before the frequency of HIRC locked.
<br>
Once the HIRC locked, the internal trim value update counter will be reset.
<br>
If the trim value update counter reached this limitation value and frequency of HIRC still doesn't lock, the auto trim operation will be disabled and FREQSEL will be cleared to 00.
<br>
00 = Trim retry count limitation is 64 loops.
<br>
01 = Trim retry count limitation is 128 loops.
<br>
10 = Trim retry count limitation is 256 loops.
<br>
11 = Trim retry count limitation is 512 loops.
<br>
</div></td></tr><tr><td>
[8]</td><td>CESTOPEN</td><td><div style="word-wrap: break-word;"><b>Clock Error Stop Enable Bit
</b><br>
0 = The trim operation is keep going if clock is inaccuracy.
<br>
1 = The trim operation is stopped if clock is inaccuracy.
<br>
</div></td></tr><tr><td>
[9]</td><td>BOUNDEN</td><td><div style="word-wrap: break-word;"><b>Boundary Enable Bit
</b><br>
0 = Boundary function is disable.
<br>
1 = Boundary function is enable.
<br>
</div></td></tr><tr><td>
[10]</td><td>REFCKSEL</td><td><div style="word-wrap: break-word;"><b>Reference Clock Selection
</b><br>
0 = HIRC trim reference from external 32.768 kHz crystal oscillator.
<br>
1 = HIRC trim reference from internal USB synchronous mode.
<br>
Note: HIRC trim reference clock is 20Khz in test mode.
<br>
</div></td></tr><tr><td>
</td><td> </td><td><div style="word-wrap: break-word;"><b>[20:16  |BOUNDARY  |Boundary Selection
</b><br>
Fill the boundary range from 0x1 to 0x31, 0x0 is reserved.
<br>
Note1: This field is effective only when the BOUNDEN(SYS_HIRCTRIMCTL[9]) is enable.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::HIRCTIEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HIRCTIEN
</font><br><p> <font size="2">
Offset: 0xE8  HIRC48M Trim Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1]</td><td>TFAILIEN</td><td><div style="word-wrap: break-word;"><b>Trim Failure Interrupt Enable Bit
</b><br>
This bit controls if an interrupt will be triggered while HIRC trim value update limitation count reached and HIRC frequency still not locked on target frequency set by FREQSEL(SYS_HIRCTCTL[1:0]).
<br>
If this bit is high and TFAILIF(SYS_HIRCTISTS[1]) is set during auto trim operation, an interrupt will be triggered to notify that HIRC trim value update limitation count was reached.
<br>
0 = Disable TFAILIF(SYS_HIRCTISTS[1]) status to trigger an interrupt to CPU.
<br>
1 = Enable TFAILIF(SYS_HIRCTISTS[1]) status to trigger an interrupt to CPU.
<br>
</div></td></tr><tr><td>
[2]</td><td>CLKEIEN</td><td><div style="word-wrap: break-word;"><b>Clock Error Interrupt Enable Bit
</b><br>
This bit controls if CPU would get an interrupt while clock is inaccuracy during auto trim operation.
<br>
If this bit is set to1, and CLKERRIF(SYS_HIRCTISTS[2]) is set during auto trim operation, an interrupt will be triggered to notify the clock frequency is inaccuracy.
<br>
0 = Disable CLKERRIF(SYS_HIRCTISTS[2]) status to trigger an interrupt to CPU.
<br>
1 = Enable CLKERRIF(SYS_HIRCTISTS[2]) status to trigger an interrupt to CPU.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::HIRCTISTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">HIRCTISTS
</font><br><p> <font size="2">
Offset: 0xEC  HIRC48M Trim Interrupt Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>FREQLOCK</td><td><div style="word-wrap: break-word;"><b>HIRC Frequency Lock Status
</b><br>
This bit indicates the HIRC frequency is locked.
<br>
This is a status bit and doesn't trigger any interrupt
<br>
Write 1 to clear this to 0
<br>
This bit will be set automatically, if the frequency is lock and the RC_TRIM is enabled.
<br>
0 = The internal high-speed oscillator frequency doesn't lock at 48 MHz yet.
<br>
1 = The internal high-speed oscillator frequency locked at 48 MHz.
<br>
</div></td></tr><tr><td>
[1]</td><td>TFAILIF</td><td><div style="word-wrap: break-word;"><b>Trim Failure Interrupt Status
</b><br>
This bit indicates that HIRC trim value update limitation count reached and the HIRC clock frequency still doesn't be locked
<br>
Once this bit is set, the auto trim operation stopped and FREQSEL(SYS_HIRCTCTL[1:0]) will be cleared to 00 by hardware automatically.
<br>
If this bit is set and TFAILIEN(SYS_HIRCTIEN[1]) is high, an interrupt will be triggered to notify that HIRC trim value update limitation count was reached
<br>
Write 1 to clear this to 0.
<br>
0 = Trim value update limitation count does not reach.
<br>
1 = Trim value update limitation count reached and HIRC frequency still not locked.
<br>
</div></td></tr><tr><td>
[2]</td><td>CLKERRIF</td><td><div style="word-wrap: break-word;"><b>Clock Error Interrupt Status
</b><br>
When the frequency of 32.768 kHz external low speed crystal oscillator (LXT) or 48MHz internal high speed RC oscillator (HIRC) is shift larger to unreasonable value, this bit will be set and to be an indicate that clock frequency is inaccuracy.
<br>
Once this bit is set to 1, the auto trim operation stopped and FREQSEL(SYS_HIRCTCL[1:0]) will be cleared to 00 by hardware automatically if CESTOPEN(SYS_HIRCTCTL[8]) is set to 1.
<br>
If this bit is set and CLKEIEN(SYS_HIRCTIEN[2]) is high, an interrupt will be triggered to notify the clock frequency is inaccuracy.
<br>
Write 1 to clear this to 0.
<br>
0 = Clock frequency is accurate.
<br>
1 = Clock frequency is inaccurate.
<br>
</div></td></tr><tr><td>
[3]</td><td>OVBDIF</td><td><div style="word-wrap: break-word;"><b>Over Boundary Status
</b><br>
When the over boundary function is set, if there occurs the over boundary condition, this flag will be set.
<br>
Note1: Write 1 to clear this flag.
<br>
Note2: This function is only supported in M48xGC/M48xG8.
<br>
0 = Over boundary condition did not occur.
<br>
1 = Over boundary condition occurred.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::IRCTCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">IRCTCTL
</font><br><p> <font size="2">
Offset: 0xF0  HIRC Trim Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1:0]</td><td>FREQSEL</td><td><div style="word-wrap: break-word;"><b>Trim Frequency Selection
</b><br>
This field indicates the target frequency of 12 MHz internal high speed RC oscillator (HIRC) auto trim.
<br>
During auto trim operation, if clock error detected with CESTOPEN is set to 1 or trim retry limitation count reached, this field will be cleared to 00 automatically.
<br>
00 = Disable HIRC auto trim function.
<br>
01 = Enable HIRC auto trim function and trim HIRC to 12 MHz.
<br>
10 = Reserved..
<br>
11 = Reserved.
<br>
</div></td></tr><tr><td>
[5:4]</td><td>LOOPSEL</td><td><div style="word-wrap: break-word;"><b>Trim Calculation Loop Selection
</b><br>
This field defines that trim value calculation is based on how many reference clocks.
<br>
00 = Trim value calculation is based on average difference in 4 clocks of reference clock.
<br>
01 = Trim value calculation is based on average difference in 8 clocks of reference clock.
<br>
10 = Trim value calculation is based on average difference in 16 clocks of reference clock.
<br>
11 = Trim value calculation is based on average difference in 32 clocks of reference clock.
<br>
Note: For example, if LOOPSEL is set as 00, auto trim circuit will calculate trim value based on the average frequency difference in 4 clocks of reference clock.
<br>
</div></td></tr><tr><td>
[7:6]</td><td>RETRYCNT</td><td><div style="word-wrap: break-word;"><b>Trim Value Update Limitation Count
</b><br>
This field defines that how many times the auto trim circuit will try to update the HIRC trim value before the frequency of HIRC locked.
<br>
Once the HIRC locked, the internal trim value update counter will be reset.
<br>
If the trim value update counter reached this limitation value and frequency of HIRC still doesn't lock, the auto trim operation will be disabled and FREQSEL will be cleared to 00.
<br>
00 = Trim retry count limitation is 64 loops.
<br>
01 = Trim retry count limitation is 128 loops.
<br>
10 = Trim retry count limitation is 256 loops.
<br>
11 = Trim retry count limitation is 512 loops.
<br>
</div></td></tr><tr><td>
[8]</td><td>CESTOPEN</td><td><div style="word-wrap: break-word;"><b>Clock Error Stop Enable Bit
</b><br>
0 = The trim operation is keep going if clock is inaccuracy.
<br>
1 = The trim operation is stopped if clock is inaccuracy.
<br>
</div></td></tr><tr><td>
[10]</td><td>REFCKSEL</td><td><div style="word-wrap: break-word;"><b>Reference Clock Selection
</b><br>
0 = HIRC trim reference from external 32.768 kHz crystal oscillator.
<br>
1 = HIRC trim reference from internal USB synchronous mode.
<br>
Note: HIRC trim reference clock is 20Khz in test mode.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::IRCTIEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">IRCTIEN
</font><br><p> <font size="2">
Offset: 0xF4  HIRC Trim Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1]</td><td>TFAILIEN</td><td><div style="word-wrap: break-word;"><b>Trim Failure Interrupt Enable Bit
</b><br>
This bit controls if an interrupt will be triggered while HIRC trim value update limitation count reached and HIRC frequency still not locked on target frequency set by FREQSEL(SYS_IRCTCTL[1:0]).
<br>
If this bit is high and TFAILIF(SYS_IRCTISTS[1]) is set during auto trim operation, an interrupt will be triggered to notify that HIRC trim value update limitation count was reached.
<br>
0 = Disable TFAILIF(SYS_IRCTISTS[1]) status to trigger an interrupt to CPU.
<br>
1 = Enable TFAILIF(SYS_IRCTISTS[1]) status to trigger an interrupt to CPU.
<br>
</div></td></tr><tr><td>
[2]</td><td>CLKEIEN</td><td><div style="word-wrap: break-word;"><b>Clock Error Interrupt Enable Bit
</b><br>
This bit controls if CPU would get an interrupt while clock is inaccuracy during auto trim operation.
<br>
If this bit is set to1, and CLKERRIF(SYS_IRCTISTS[2]) is set during auto trim operation, an interrupt will be triggered to notify the clock frequency is inaccuracy.
<br>
0 = Disable CLKERRIF(SYS_IRCTISTS[2]) status to trigger an interrupt to CPU.
<br>
1 = Enable CLKERRIF(SYS_IRCTISTS[2]) status to trigger an interrupt to CPU.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::IRCTISTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">IRCTISTS
</font><br><p> <font size="2">
Offset: 0xF8  HIRC Trim Interrupt Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>FREQLOCK</td><td><div style="word-wrap: break-word;"><b>HIRC Frequency Lock Status
</b><br>
This bit indicates the HIRC frequency is locked.
<br>
This is a status bit and doesn't trigger any interrupt
<br>
Write 1 to clear this to 0
<br>
This bit will be set automatically, if the frequency is lock and the RC_TRIM is enabled.
<br>
0 = The internal high-speed oscillator frequency doesn't lock at 12 MHz yet.
<br>
1 = The internal high-speed oscillator frequency locked at 12 MHz.
<br>
</div></td></tr><tr><td>
[1]</td><td>TFAILIF</td><td><div style="word-wrap: break-word;"><b>Trim Failure Interrupt Status
</b><br>
This bit indicates that HIRC trim value update limitation count reached and the HIRC clock frequency still doesn't be locked
<br>
Once this bit is set, the auto trim operation stopped and FREQSEL(SYS_IRCTCTL[1:0]) will be cleared to 00 by hardware automatically.
<br>
If this bit is set and TFAILIEN(SYS_IRCTIEN[1]) is high, an interrupt will be triggered to notify that HIRC trim value update limitation count was reached
<br>
Write 1 to clear this to 0.
<br>
0 = Trim value update limitation count does not reach.
<br>
1 = Trim value update limitation count reached and HIRC frequency still not locked.
<br>
</div></td></tr><tr><td>
[2]</td><td>CLKERRIF</td><td><div style="word-wrap: break-word;"><b>Clock Error Interrupt Status
</b><br>
When the frequency of 32.768 kHz external low speed crystal oscillator (LXT) or 12MHz internal high speed RC oscillator (HIRC) is shift larger to unreasonable value, this bit will be set and to be an indicate that clock frequency is inaccuracy.
<br>
Once this bit is set to 1, the auto trim operation stopped and FREQSEL(SYS_IRCTCL[1:0]) will be cleared to 00 by hardware automatically if CESTOPEN(SYS_IRCTCTL[8]) is set to 1.
<br>
If this bit is set and CLKEIEN(SYS_IRCTIEN[2]) is high, an interrupt will be triggered to notify the clock frequency is inaccuracy.
<br>
Write 1 to clear this to 0.
<br>
0 = Clock frequency is accurate.
<br>
1 = Clock frequency is inaccurate.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::REGLCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">REGLCTL
</font><br><p> <font size="2">
Offset: 0x100  Register Lock Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[7:0]</td><td>REGLCTL</td><td><div style="word-wrap: break-word;"><b>Register Lock Control Code
</b><br>
Some registers have write-protection function
<br>
Writing these registers have to disable the protected function by writing the sequence value "59h", "16h", "88h" to this field.
<br>
After this sequence is completed, the REGLCTL bit will be set to 1 and write-protection registers can be normal write.
<br>
Register Lock Control Code
<br>
0 = Write-protection Enabled for writing protected registers
<br>
Any write to the protected register is ignored.
<br>
1 = Write-protection Disabled for writing protected registers.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::PORDISAN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PORDISAN
</font><br><p> <font size="2">
Offset: 0x1EC  Analog POR Disable Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>POROFFAN</td><td><div style="word-wrap: break-word;"><b>Power-on Reset Enable Bit (Write Protect)
</b><br>
After powered on, User can turn off internal analog POR circuit to save power by writing 0x5AA5 to this field.
<br>
The analog POR circuit will be active again when  this field is set to another value or chip is reset by other reset source, including:
<br>
nRESET, Watchdog, LVR reset, BOD reset, ICE reset command and the software-chip reset function.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::PLCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PLCTL
</font><br><p> <font size="2">
Offset: 0x1F8  Power Level Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1:0]</td><td>PLSEL</td><td><div style="word-wrap: break-word;"><b>Power Level Select(Write Protect)
</b><br>
00 = Power level is PL0.
<br>
01 = Power level is PL1.
<br>
Others = Reserved.
<br>
</div></td></tr><tr><td>
[21:16]</td><td>LVSSTEP</td><td><div style="word-wrap: break-word;"><b>LDO Voltage Scaling Step(Write Protect)
</b><br>
The LVSSTEP value is LDO voltage rising step.
<br>
Core voltage scaling voltage step = (LVSSTEP + 1) * 10mV.
<br>
</div></td></tr><tr><td>
[31:24]</td><td>LVSPRD</td><td><div style="word-wrap: break-word;"><b>LDO Voltage Scaling Period(Write Protect)
</b><br>
The LVSPRD value is the period of each LDO voltage rising step.
<br>
LDO voltage scaling period = (LVSPRD + 1) * 1us.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::PLSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PLSTS
</font><br><p> <font size="2">
Offset: 0x1FC  Power Level Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>PLCBUSY</td><td><div style="word-wrap: break-word;"><b>Power Level Change Busy Bit (Read Only)
</b><br>
This bit is set by hardware when core voltage is changing
<br>
After core voltage change is completed, this bit will be cleared automatically by hardware.
<br>
0 = Core voltage change is completed.
<br>
1 = Core voltage change is ongoing.
<br>
</div></td></tr><tr><td>
[9:8]</td><td>PLSTATUS</td><td><div style="word-wrap: break-word;"><b>Power Level Status (Read Only)
</b><br>
00 = Power level is PL0.
<br>
01 = Power level is PL1.
<br>
Others = Reserved.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var SYS_T::AHBMCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">AHBMCTL
</font><br><p> <font size="2">
Offset: 0x400  AHB Bus Matrix Priority Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>INTACTEN</td><td><div style="word-wrap: break-word;"><b>Highest AHB Bus Priority of Cortex M4 Core Enable Bit (Write Protect)
</b><br>
Enable Cortex-M4 Core With Highest AHB Bus Priority In AHB Bus Matrix
<br>
0 = Run robin mode.
<br>
1 = Cortex-M4 CPU with highest bus priority when interrupt occurred.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __I  uint32_t PDID;                  /*!< [0x0000] Part Device Identification Number Register                       */
    __IO uint32_t RSTSTS;                /*!< [0x0004] System Reset Status Register                                     */
    __IO uint32_t IPRST0;                /*!< [0x0008] Peripheral  Reset Control Register 0                             */
    __IO uint32_t IPRST1;                /*!< [0x000c] Peripheral Reset Control Register 1                              */
    __IO uint32_t IPRST2;                /*!< [0x0010] Peripheral Reset Control Register 2                              */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE0[1];
    /** @endcond */
    __IO uint32_t BODCTL;                /*!< [0x0018] Brown-Out Detector Control Register                              */
    __IO uint32_t IVSCTL;                /*!< [0x001c] Internal Voltage Source Control Register                         */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE1[1];
    /** @endcond */
    __IO uint32_t PORCTL;                /*!< [0x0024] Power-On-Reset Controller Register                               */
    __IO uint32_t VREFCTL;               /*!< [0x0028] VREF Control Register                                            */
    __IO uint32_t USBPHY;                /*!< [0x002c] USB PHY Control Register                                         */
    __IO uint32_t GPA_MFPL;              /*!< [0x0030] GPIOA Low Byte Multiple Function Control Register                */
    __IO uint32_t GPA_MFPH;              /*!< [0x0034] GPIOA High Byte Multiple Function Control Register               */
    __IO uint32_t GPB_MFPL;              /*!< [0x0038] GPIOB Low Byte Multiple Function Control Register                */
    __IO uint32_t GPB_MFPH;              /*!< [0x003c] GPIOB High Byte Multiple Function Control Register               */
    __IO uint32_t GPC_MFPL;              /*!< [0x0040] GPIOC Low Byte Multiple Function Control Register                */
    __IO uint32_t GPC_MFPH;              /*!< [0x0044] GPIOC High Byte Multiple Function Control Register               */
    __IO uint32_t GPD_MFPL;              /*!< [0x0048] GPIOD Low Byte Multiple Function Control Register                */
    __IO uint32_t GPD_MFPH;              /*!< [0x004c] GPIOD High Byte Multiple Function Control Register               */
    __IO uint32_t GPE_MFPL;              /*!< [0x0050] GPIOE Low Byte Multiple Function Control Register                */
    __IO uint32_t GPE_MFPH;              /*!< [0x0054] GPIOE High Byte Multiple Function Control Register               */
    __IO uint32_t GPF_MFPL;              /*!< [0x0058] GPIOF Low Byte Multiple Function Control Register                */
    __IO uint32_t GPF_MFPH;              /*!< [0x005c] GPIOF High Byte Multiple Function Control Register               */
    __IO uint32_t GPG_MFPL;              /*!< [0x0060] GPIOG Low Byte Multiple Function Control Register                */
    __IO uint32_t GPG_MFPH;              /*!< [0x0064] GPIOG High Byte Multiple Function Control Register               */
    __IO uint32_t GPH_MFPL;              /*!< [0x0068] GPIOH Low Byte Multiple Function Control Register                */
    __IO uint32_t GPH_MFPH;              /*!< [0x006c] GPIOH High Byte Multiple Function Control Register               */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE2[4];
    /** @endcond */
    __IO uint32_t GPA_MFOS;              /*!< [0x0080] GPIOA Multiple Function Output Select Register                   */
    __IO uint32_t GPB_MFOS;              /*!< [0x0084] GPIOB Multiple Function Output Select Register                   */
    __IO uint32_t GPC_MFOS;              /*!< [0x0088] GPIOC Multiple Function Output Select Register                   */
    __IO uint32_t GPD_MFOS;              /*!< [0x008c] GPIOD Multiple Function Output Select Register                   */
    __IO uint32_t GPE_MFOS;              /*!< [0x0090] GPIOE Multiple Function Output Select Register                   */
    __IO uint32_t GPF_MFOS;              /*!< [0x0094] GPIOF Multiple Function Output Select Register                   */
    __IO uint32_t GPG_MFOS;              /*!< [0x0098] GPIOG Multiple Function Output Select Register                   */
    __IO uint32_t GPH_MFOS;              /*!< [0x009c] GPIOH Multiple Function Output Select Register                   */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE3[8];
    /** @endcond */
    __IO uint32_t SRAM_INTCTL;           /*!< [0x00c0] System SRAM Interrupt Enable Control Register                    */
    __IO uint32_t SRAM_STATUS;           /*!< [0x00c4] System SRAM Parity Error Status Register                         */
    __I  uint32_t SRAM_ERRADDR;          /*!< [0x00c8] System SRAM Parity Check Error Address Register                  */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE4[1];
    /** @endcond */
    __IO uint32_t SRAM_BISTCTL;          /*!< [0x00d0] System SRAM BIST Test Control Register                           */
    __I  uint32_t SRAM_BISTSTS;          /*!< [0x00d4] System SRAM BIST Test Status Register                            */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE5[3];
    /** @endcond */
    __IO uint32_t HIRCTCTL;              /*!< [0x00e4] HIRC48M Trim Control Register                                    */
    __IO uint32_t HIRCTIEN;              /*!< [0x00e8] HIRC48M Trim Interrupt Enable Register                           */
    __IO uint32_t HIRCTISTS;             /*!< [0x00ec] HIRC48M Trim Interrupt Status Register                           */
    __IO uint32_t IRCTCTL;               /*!< [0x00f0] HIRC Trim Control Register                                       */
    __IO uint32_t IRCTIEN;               /*!< [0x00f4] HIRC Trim Interrupt Enable Register                              */
    __IO uint32_t IRCTISTS;              /*!< [0x00f8] HIRC Trim Interrupt Status Register                              */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE6[1];
    /** @endcond */
    __IO uint32_t REGLCTL;               /*!< [0x0100] Register Lock Control Register                                   */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE7[58];
    /** @endcond */
    __IO uint32_t PORDISAN;              /*!< [0x01ec] Analog POR Disable Control Register                              */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE8;
    /** @endcond */
    __I  uint32_t CSERVER;               /*!< [0x01f4] Chip Series Version Register                                     */
    __IO uint32_t PLCTL;                 /*!< [0x01f8] Power Level Control Register                                     */
    __I  uint32_t PLSTS;                 /*!< [0x01fc] Power Level Status Register                                      */
    /** @cond HIDDEN_SYMBOLS */
    __I  uint32_t RESERVE9[128];
    /** @endcond */
    __IO uint32_t AHBMCTL;               /*!< [0x0400] AHB Bus Matrix Priority Control Register                         */

} SYS_T;

/**
    @addtogroup SYS_CONST SYS Bit Field Definition
    Constant Definitions for SYS Controller
@{ */

#define SYS_PDID_PDID_Pos                (0)                                               /*!< SYS_T::PDID: PDID Position             */
#define SYS_PDID_PDID_Msk                (0xfffffffful << SYS_PDID_PDID_Pos)               /*!< SYS_T::PDID: PDID Mask                 */

#define SYS_RSTSTS_PORF_Pos              (0)                                               /*!< SYS_T::RSTSTS: PORF Position           */
#define SYS_RSTSTS_PORF_Msk              (0x1ul << SYS_RSTSTS_PORF_Pos)                    /*!< SYS_T::RSTSTS: PORF Mask               */

#define SYS_RSTSTS_PINRF_Pos             (1)                                               /*!< SYS_T::RSTSTS: PINRF Position          */
#define SYS_RSTSTS_PINRF_Msk             (0x1ul << SYS_RSTSTS_PINRF_Pos)                   /*!< SYS_T::RSTSTS: PINRF Mask              */

#define SYS_RSTSTS_WDTRF_Pos             (2)                                               /*!< SYS_T::RSTSTS: WDTRF Position          */
#define SYS_RSTSTS_WDTRF_Msk             (0x1ul << SYS_RSTSTS_WDTRF_Pos)                   /*!< SYS_T::RSTSTS: WDTRF Mask              */

#define SYS_RSTSTS_LVRF_Pos              (3)                                               /*!< SYS_T::RSTSTS: LVRF Position           */
#define SYS_RSTSTS_LVRF_Msk              (0x1ul << SYS_RSTSTS_LVRF_Pos)                    /*!< SYS_T::RSTSTS: LVRF Mask               */

#define SYS_RSTSTS_BODRF_Pos             (4)                                               /*!< SYS_T::RSTSTS: BODRF Position          */
#define SYS_RSTSTS_BODRF_Msk             (0x1ul << SYS_RSTSTS_BODRF_Pos)                   /*!< SYS_T::RSTSTS: BODRF Mask              */

#define SYS_RSTSTS_SYSRF_Pos             (5)                                               /*!< SYS_T::RSTSTS: SYSRF Position          */
#define SYS_RSTSTS_SYSRF_Msk             (0x1ul << SYS_RSTSTS_SYSRF_Pos)                   /*!< SYS_T::RSTSTS: SYSRF Mask              */

#define SYS_RSTSTS_CPURF_Pos             (7)                                               /*!< SYS_T::RSTSTS: CPURF Position          */
#define SYS_RSTSTS_CPURF_Msk             (0x1ul << SYS_RSTSTS_CPURF_Pos)                   /*!< SYS_T::RSTSTS: CPURF Mask              */

#define SYS_RSTSTS_CPULKRF_Pos           (8)                                               /*!< SYS_T::RSTSTS: CPULKRF Position        */
#define SYS_RSTSTS_CPULKRF_Msk           (0x1ul << SYS_RSTSTS_CPULKRF_Pos)                 /*!< SYS_T::RSTSTS: CPULKRF Mask            */

#define SYS_IPRST0_CHIPRST_Pos           (0)                                               /*!< SYS_T::IPRST0: CHIPRST Position        */
#define SYS_IPRST0_CHIPRST_Msk           (0x1ul << SYS_IPRST0_CHIPRST_Pos)                 /*!< SYS_T::IPRST0: CHIPRST Mask            */

#define SYS_IPRST0_CPURST_Pos            (1)                                               /*!< SYS_T::IPRST0: CPURST Position         */
#define SYS_IPRST0_CPURST_Msk            (0x1ul << SYS_IPRST0_CPURST_Pos)                  /*!< SYS_T::IPRST0: CPURST Mask             */

#define SYS_IPRST0_PDMARST_Pos           (2)                                               /*!< SYS_T::IPRST0: PDMARST Position        */
#define SYS_IPRST0_PDMARST_Msk           (0x1ul << SYS_IPRST0_PDMARST_Pos)                 /*!< SYS_T::IPRST0: PDMARST Mask            */

#define SYS_IPRST0_EBIRST_Pos            (3)                                               /*!< SYS_T::IPRST0: EBIRST Position         */
#define SYS_IPRST0_EBIRST_Msk            (0x1ul << SYS_IPRST0_EBIRST_Pos)                  /*!< SYS_T::IPRST0: EBIRST Mask             */

#define SYS_IPRST0_EMACRST_Pos           (5)                                               /*!< SYS_T::IPRST0: EMACRST Position        */
#define SYS_IPRST0_EMACRST_Msk           (0x1ul << SYS_IPRST0_EMACRST_Pos)                 /*!< SYS_T::IPRST0: EMACRST Mask            */

#define SYS_IPRST0_SDH0RST_Pos           (6)                                               /*!< SYS_T::IPRST0: SDH0RST Position        */
#define SYS_IPRST0_SDH0RST_Msk           (0x1ul << SYS_IPRST0_SDH0RST_Pos)                 /*!< SYS_T::IPRST0: SDH0RST Mask            */

#define SYS_IPRST0_CRCRST_Pos            (7)                                               /*!< SYS_T::IPRST0: CRCRST Position         */
#define SYS_IPRST0_CRCRST_Msk            (0x1ul << SYS_IPRST0_CRCRST_Pos)                  /*!< SYS_T::IPRST0: CRCRST Mask             */

#define SYS_IPRST0_CCAPRST_Pos           (8)                                               /*!< SYS_T::IPRST0: CCAPRST Position        */
#define SYS_IPRST0_CCAPRST_Msk           (0x1ul << SYS_IPRST0_CCAPRST_Pos)                 /*!< SYS_T::IPRST0: CCAPRST Mask            */

#define SYS_IPRST0_HSUSBDRST_Pos         (10)                                              /*!< SYS_T::IPRST0: HSUSBDRST Position      */
#define SYS_IPRST0_HSUSBDRST_Msk         (0x1ul << SYS_IPRST0_HSUSBDRST_Pos)               /*!< SYS_T::IPRST0: HSUSBDRST Mask          */

#define SYS_IPRST0_CRPTRST_Pos           (12)                                              /*!< SYS_T::IPRST0: CRPTRST Position        */
#define SYS_IPRST0_CRPTRST_Msk           (0x1ul << SYS_IPRST0_CRPTRST_Pos)                 /*!< SYS_T::IPRST0: CRPTRST Mask            */

#define SYS_IPRST0_SPIMRST_Pos           (14)                                              /*!< SYS_T::IPRST0: SPIMRST Position        */
#define SYS_IPRST0_SPIMRST_Msk           (0x1ul << SYS_IPRST0_SPIMRST_Pos)                 /*!< SYS_T::IPRST0: SPIMRST Mask            */

#define SYS_IPRST0_USBHRST_Pos           (16)                                              /*!< SYS_T::IPRST0: USBHRST Position        */
#define SYS_IPRST0_USBHRST_Msk           (0x1ul << SYS_IPRST0_USBHRST_Pos)                 /*!< SYS_T::IPRST0: USBHRST Mask            */

#define SYS_IPRST0_SDH1RST_Pos           (17)                                              /*!< SYS_T::IPRST0: SDH1RST Position        */
#define SYS_IPRST0_SDH1RST_Msk           (0x1ul << SYS_IPRST0_SDH1RST_Pos)                 /*!< SYS_T::IPRST0: SDH1RST Mask            */

#define SYS_IPRST1_GPIORST_Pos           (1)                                               /*!< SYS_T::IPRST1: GPIORST Position        */
#define SYS_IPRST1_GPIORST_Msk           (0x1ul << SYS_IPRST1_GPIORST_Pos)                 /*!< SYS_T::IPRST1: GPIORST Mask            */

#define SYS_IPRST1_TMR0RST_Pos           (2)                                               /*!< SYS_T::IPRST1: TMR0RST Position        */
#define SYS_IPRST1_TMR0RST_Msk           (0x1ul << SYS_IPRST1_TMR0RST_Pos)                 /*!< SYS_T::IPRST1: TMR0RST Mask            */

#define SYS_IPRST1_TMR1RST_Pos           (3)                                               /*!< SYS_T::IPRST1: TMR1RST Position        */
#define SYS_IPRST1_TMR1RST_Msk           (0x1ul << SYS_IPRST1_TMR1RST_Pos)                 /*!< SYS_T::IPRST1: TMR1RST Mask            */

#define SYS_IPRST1_TMR2RST_Pos           (4)                                               /*!< SYS_T::IPRST1: TMR2RST Position        */
#define SYS_IPRST1_TMR2RST_Msk           (0x1ul << SYS_IPRST1_TMR2RST_Pos)                 /*!< SYS_T::IPRST1: TMR2RST Mask            */

#define SYS_IPRST1_TMR3RST_Pos           (5)                                               /*!< SYS_T::IPRST1: TMR3RST Position        */
#define SYS_IPRST1_TMR3RST_Msk           (0x1ul << SYS_IPRST1_TMR3RST_Pos)                 /*!< SYS_T::IPRST1: TMR3RST Mask            */

#define SYS_IPRST1_ACMP01RST_Pos         (7)                                               /*!< SYS_T::IPRST1: ACMP01RST Position      */
#define SYS_IPRST1_ACMP01RST_Msk         (0x1ul << SYS_IPRST1_ACMP01RST_Pos)               /*!< SYS_T::IPRST1: ACMP01RST Mask          */

#define SYS_IPRST1_I2C0RST_Pos           (8)                                               /*!< SYS_T::IPRST1: I2C0RST Position        */
#define SYS_IPRST1_I2C0RST_Msk           (0x1ul << SYS_IPRST1_I2C0RST_Pos)                 /*!< SYS_T::IPRST1: I2C0RST Mask            */

#define SYS_IPRST1_I2C1RST_Pos           (9)                                               /*!< SYS_T::IPRST1: I2C1RST Position        */
#define SYS_IPRST1_I2C1RST_Msk           (0x1ul << SYS_IPRST1_I2C1RST_Pos)                 /*!< SYS_T::IPRST1: I2C1RST Mask            */

#define SYS_IPRST1_I2C2RST_Pos           (10)                                              /*!< SYS_T::IPRST1: I2C2RST Position        */
#define SYS_IPRST1_I2C2RST_Msk           (0x1ul << SYS_IPRST1_I2C2RST_Pos)                 /*!< SYS_T::IPRST1: I2C2RST Mask            */

#define SYS_IPRST1_QSPI0RST_Pos          (12)                                              /*!< SYS_T::IPRST1: QSPI0RST Position       */
#define SYS_IPRST1_QSPI0RST_Msk          (0x1ul << SYS_IPRST1_QSPI0RST_Pos)                /*!< SYS_T::IPRST1: QSPI0RST Mask           */

#define SYS_IPRST1_SPI0RST_Pos           (13)                                              /*!< SYS_T::IPRST1: SPI0RST Position        */
#define SYS_IPRST1_SPI0RST_Msk           (0x1ul << SYS_IPRST1_SPI0RST_Pos)                 /*!< SYS_T::IPRST1: SPI0RST Mask            */

#define SYS_IPRST1_SPI1RST_Pos           (14)                                              /*!< SYS_T::IPRST1: SPI1RST Position        */
#define SYS_IPRST1_SPI1RST_Msk           (0x1ul << SYS_IPRST1_SPI1RST_Pos)                 /*!< SYS_T::IPRST1: SPI1RST Mask            */

#define SYS_IPRST1_SPI2RST_Pos           (15)                                              /*!< SYS_T::IPRST1: SPI2RST Position        */
#define SYS_IPRST1_SPI2RST_Msk           (0x1ul << SYS_IPRST1_SPI2RST_Pos)                 /*!< SYS_T::IPRST1: SPI2RST Mask            */

#define SYS_IPRST1_UART0RST_Pos          (16)                                              /*!< SYS_T::IPRST1: UART0RST Position       */
#define SYS_IPRST1_UART0RST_Msk          (0x1ul << SYS_IPRST1_UART0RST_Pos)                /*!< SYS_T::IPRST1: UART0RST Mask           */

#define SYS_IPRST1_UART1RST_Pos          (17)                                              /*!< SYS_T::IPRST1: UART1RST Position       */
#define SYS_IPRST1_UART1RST_Msk          (0x1ul << SYS_IPRST1_UART1RST_Pos)                /*!< SYS_T::IPRST1: UART1RST Mask           */

#define SYS_IPRST1_UART2RST_Pos          (18)                                              /*!< SYS_T::IPRST1: UART2RST Position       */
#define SYS_IPRST1_UART2RST_Msk          (0x1ul << SYS_IPRST1_UART2RST_Pos)                /*!< SYS_T::IPRST1: UART2RST Mask           */

#define SYS_IPRST1_UART3RST_Pos          (19)                                              /*!< SYS_T::IPRST1: UART3RST Position       */
#define SYS_IPRST1_UART3RST_Msk          (0x1ul << SYS_IPRST1_UART3RST_Pos)                /*!< SYS_T::IPRST1: UART3RST Mask           */

#define SYS_IPRST1_UART4RST_Pos          (20)                                              /*!< SYS_T::IPRST1: UART4RST Position       */
#define SYS_IPRST1_UART4RST_Msk          (0x1ul << SYS_IPRST1_UART4RST_Pos)                /*!< SYS_T::IPRST1: UART4RST Mask           */

#define SYS_IPRST1_UART5RST_Pos          (21)                                              /*!< SYS_T::IPRST1: UART5RST Position       */
#define SYS_IPRST1_UART5RST_Msk          (0x1ul << SYS_IPRST1_UART5RST_Pos)                /*!< SYS_T::IPRST1: UART5RST Mask           */

#define SYS_IPRST1_UART6RST_Pos          (22)                                              /*!< SYS_T::IPRST1: UART6RST Position       */
#define SYS_IPRST1_UART6RST_Msk          (0x1ul << SYS_IPRST1_UART6RST_Pos)                /*!< SYS_T::IPRST1: UART6RST Mask           */

#define SYS_IPRST1_UART7RST_Pos          (23)                                              /*!< SYS_T::IPRST1: UART7RST Position       */
#define SYS_IPRST1_UART7RST_Msk          (0x1ul << SYS_IPRST1_UART7RST_Pos)                /*!< SYS_T::IPRST1: UART7RST Mask           */

#define SYS_IPRST1_CAN0RST_Pos           (24)                                              /*!< SYS_T::IPRST1: CAN0RST Position        */
#define SYS_IPRST1_CAN0RST_Msk           (0x1ul << SYS_IPRST1_CAN0RST_Pos)                 /*!< SYS_T::IPRST1: CAN0RST Mask            */

#define SYS_IPRST1_CAN1RST_Pos           (25)                                              /*!< SYS_T::IPRST1: CAN1RST Position        */
#define SYS_IPRST1_CAN1RST_Msk           (0x1ul << SYS_IPRST1_CAN1RST_Pos)                 /*!< SYS_T::IPRST1: CAN1RST Mask            */

#define SYS_IPRST1_OTGRST_Pos            (26)                                              /*!< SYS_T::IPRST1: OTGRST Position         */
#define SYS_IPRST1_OTGRST_Msk            (0x1ul << SYS_IPRST1_OTGRST_Pos)                  /*!< SYS_T::IPRST1: OTGRST Mask             */

#define SYS_IPRST1_USBDRST_Pos           (27)                                              /*!< SYS_T::IPRST1: USBDRST Position        */
#define SYS_IPRST1_USBDRST_Msk           (0x1ul << SYS_IPRST1_USBDRST_Pos)                 /*!< SYS_T::IPRST1: USBDRST Mask            */

#define SYS_IPRST1_EADCRST_Pos           (28)                                              /*!< SYS_T::IPRST1: EADCRST Position        */
#define SYS_IPRST1_EADCRST_Msk           (0x1ul << SYS_IPRST1_EADCRST_Pos)                 /*!< SYS_T::IPRST1: EADCRST Mask            */

#define SYS_IPRST1_I2S0RST_Pos           (29)                                              /*!< SYS_T::IPRST1: I2S0RST Position        */
#define SYS_IPRST1_I2S0RST_Msk           (0x1ul << SYS_IPRST1_I2S0RST_Pos)                 /*!< SYS_T::IPRST1: I2S0RST Mask            */

#define SYS_IPRST1_HSOTGRST_Pos          (30)                                              /*!< SYS_T::IPRST1: HSOTGRST Position       */
#define SYS_IPRST1_HSOTGRST_Msk          (0x1ul << SYS_IPRST1_HSOTGRST_Pos)                /*!< SYS_T::IPRST1: HSOTGRST Mask           */

#define SYS_IPRST1_TRNGRST_Pos           (31)                                              /*!< SYS_T::IPRST1: TRNGRST Position        */
#define SYS_IPRST1_TRNGRST_Msk           (0x1ul << SYS_IPRST1_TRNGRST_Pos)                 /*!< SYS_T::IPRST1: TRNGRST Mask            */

#define SYS_IPRST2_SC0RST_Pos            (0)                                               /*!< SYS_T::IPRST2: SC0RST Position         */
#define SYS_IPRST2_SC0RST_Msk            (0x1ul << SYS_IPRST2_SC0RST_Pos)                  /*!< SYS_T::IPRST2: SC0RST Mask             */

#define SYS_IPRST2_SC1RST_Pos            (1)                                               /*!< SYS_T::IPRST2: SC1RST Position         */
#define SYS_IPRST2_SC1RST_Msk            (0x1ul << SYS_IPRST2_SC1RST_Pos)                  /*!< SYS_T::IPRST2: SC1RST Mask             */

#define SYS_IPRST2_SC2RST_Pos            (2)                                               /*!< SYS_T::IPRST2: SC2RST Position         */
#define SYS_IPRST2_SC2RST_Msk            (0x1ul << SYS_IPRST2_SC2RST_Pos)                  /*!< SYS_T::IPRST2: SC2RST Mask             */

#define SYS_IPRST2_QSPI1RST_Pos          (4)                                               /*!< SYS_T::IPRST2: QSPI1RST Position       */
#define SYS_IPRST2_QSPI1RST_Msk          (0x1ul << SYS_IPRST2_QSPI1RST_Pos)                /*!< SYS_T::IPRST2: QSPI1RST Mask           */

#define SYS_IPRST2_SPI3RST_Pos           (6)                                               /*!< SYS_T::IPRST2: SPI3RST Position        */
#define SYS_IPRST2_SPI3RST_Msk           (0x1ul << SYS_IPRST2_SPI3RST_Pos)                 /*!< SYS_T::IPRST2: SPI3RST Mask            */

#define SYS_IPRST2_USCI0RST_Pos          (8)                                               /*!< SYS_T::IPRST2: USCI0RST Position       */
#define SYS_IPRST2_USCI0RST_Msk          (0x1ul << SYS_IPRST2_USCI0RST_Pos)                /*!< SYS_T::IPRST2: USCI0RST Mask           */

#define SYS_IPRST2_USCI1RST_Pos          (9)                                               /*!< SYS_T::IPRST2: USCI1RST Position       */
#define SYS_IPRST2_USCI1RST_Msk          (0x1ul << SYS_IPRST2_USCI1RST_Pos)                /*!< SYS_T::IPRST2: USCI1RST Mask           */

#define SYS_IPRST2_DACRST_Pos            (12)                                              /*!< SYS_T::IPRST2: DACRST Position         */
#define SYS_IPRST2_DACRST_Msk            (0x1ul << SYS_IPRST2_DACRST_Pos)                  /*!< SYS_T::IPRST2: DACRST Mask             */

#define SYS_IPRST2_EPWM0RST_Pos          (16)                                              /*!< SYS_T::IPRST2: EPWM0RST Position       */
#define SYS_IPRST2_EPWM0RST_Msk          (0x1ul << SYS_IPRST2_EPWM0RST_Pos)                /*!< SYS_T::IPRST2: EPWM0RST Mask           */

#define SYS_IPRST2_EPWM1RST_Pos          (17)                                              /*!< SYS_T::IPRST2: EPWM1RST Position       */
#define SYS_IPRST2_EPWM1RST_Msk          (0x1ul << SYS_IPRST2_EPWM1RST_Pos)                /*!< SYS_T::IPRST2: EPWM1RST Mask           */

#define SYS_IPRST2_BPWM0RST_Pos          (18)                                              /*!< SYS_T::IPRST2: BPWM0RST Position       */
#define SYS_IPRST2_BPWM0RST_Msk          (0x1ul << SYS_IPRST2_BPWM0RST_Pos)                /*!< SYS_T::IPRST2: BPWM0RST Mask           */

#define SYS_IPRST2_BPWM1RST_Pos          (19)                                              /*!< SYS_T::IPRST2: BPWM1RST Position       */
#define SYS_IPRST2_BPWM1RST_Msk          (0x1ul << SYS_IPRST2_BPWM1RST_Pos)                /*!< SYS_T::IPRST2: BPWM1RST Mask           */

#define SYS_IPRST2_QEI0RST_Pos           (22)                                              /*!< SYS_T::IPRST2: QEI0RST Position        */
#define SYS_IPRST2_QEI0RST_Msk           (0x1ul << SYS_IPRST2_QEI0RST_Pos)                 /*!< SYS_T::IPRST2: QEI0RST Mask            */

#define SYS_IPRST2_QEI1RST_Pos           (23)                                              /*!< SYS_T::IPRST2: QEI1RST Position        */
#define SYS_IPRST2_QEI1RST_Msk           (0x1ul << SYS_IPRST2_QEI1RST_Pos)                 /*!< SYS_T::IPRST2: QEI1RST Mask            */

#define SYS_IPRST2_ECAP0RST_Pos          (26)                                              /*!< SYS_T::IPRST2: ECAP0RST Position       */
#define SYS_IPRST2_ECAP0RST_Msk          (0x1ul << SYS_IPRST2_ECAP0RST_Pos)                /*!< SYS_T::IPRST2: ECAP0RST Mask           */

#define SYS_IPRST2_ECAP1RST_Pos          (27)                                              /*!< SYS_T::IPRST2: ECAP1RST Position       */
#define SYS_IPRST2_ECAP1RST_Msk          (0x1ul << SYS_IPRST2_ECAP1RST_Pos)                /*!< SYS_T::IPRST2: ECAP1RST Mask           */

#define SYS_IPRST2_CAN2RST_Pos           (28)                                              /*!< SYS_T::IPRST2: CAN2RST Position        */
#define SYS_IPRST2_CAN2RST_Msk           (0x1ul << SYS_IPRST2_CAN2RST_Pos)                 /*!< SYS_T::IPRST2: CAN2RST Mask            */

#define SYS_IPRST2_OPARST_Pos            (30)                                              /*!< SYS_T::IPRST2: OPARST Position         */
#define SYS_IPRST2_OPARST_Msk            (0x1ul << SYS_IPRST2_OPARST_Pos)                  /*!< SYS_T::IPRST2: OPARST Mask             */

#define SYS_IPRST2_EADC1RST_Pos          (31)                                              /*!< SYS_T::IPRST2: EADC1RST Position       */
#define SYS_IPRST2_EADC1RST_Msk          (0x1ul << SYS_IPRST2_EADC1RST_Pos)                /*!< SYS_T::IPRST2: EADC1RST Mask           */

#define SYS_BODCTL_BODEN_Pos             (0)                                               /*!< SYS_T::BODCTL: BODEN Position          */
#define SYS_BODCTL_BODEN_Msk             (0x1ul << SYS_BODCTL_BODEN_Pos)                   /*!< SYS_T::BODCTL: BODEN Mask              */

#define SYS_BODCTL_BODRSTEN_Pos          (3)                                               /*!< SYS_T::BODCTL: BODRSTEN Position       */
#define SYS_BODCTL_BODRSTEN_Msk          (0x1ul << SYS_BODCTL_BODRSTEN_Pos)                /*!< SYS_T::BODCTL: BODRSTEN Mask           */

#define SYS_BODCTL_BODIF_Pos             (4)                                               /*!< SYS_T::BODCTL: BODIF Position          */
#define SYS_BODCTL_BODIF_Msk             (0x1ul << SYS_BODCTL_BODIF_Pos)                   /*!< SYS_T::BODCTL: BODIF Mask              */

#define SYS_BODCTL_BODLPM_Pos            (5)                                               /*!< SYS_T::BODCTL: BODLPM Position         */
#define SYS_BODCTL_BODLPM_Msk            (0x1ul << SYS_BODCTL_BODLPM_Pos)                  /*!< SYS_T::BODCTL: BODLPM Mask             */

#define SYS_BODCTL_BODOUT_Pos            (6)                                               /*!< SYS_T::BODCTL: BODOUT Position         */
#define SYS_BODCTL_BODOUT_Msk            (0x1ul << SYS_BODCTL_BODOUT_Pos)                  /*!< SYS_T::BODCTL: BODOUT Mask             */

#define SYS_BODCTL_LVREN_Pos             (7)                                               /*!< SYS_T::BODCTL: LVREN Position          */
#define SYS_BODCTL_LVREN_Msk             (0x1ul << SYS_BODCTL_LVREN_Pos)                   /*!< SYS_T::BODCTL: LVREN Mask              */

#define SYS_BODCTL_BODDGSEL_Pos          (8)                                               /*!< SYS_T::BODCTL: BODDGSEL Position       */
#define SYS_BODCTL_BODDGSEL_Msk          (0x7ul << SYS_BODCTL_BODDGSEL_Pos)                /*!< SYS_T::BODCTL: BODDGSEL Mask           */

#define SYS_BODCTL_LVRDGSEL_Pos          (12)                                              /*!< SYS_T::BODCTL: LVRDGSEL Position       */
#define SYS_BODCTL_LVRDGSEL_Msk          (0x7ul << SYS_BODCTL_LVRDGSEL_Pos)                /*!< SYS_T::BODCTL: LVRDGSEL Mask           */

#define SYS_BODCTL_BODVL_Pos             (16)                                              /*!< SYS_T::BODCTL: BODVL Position          */
#define SYS_BODCTL_BODVL_Msk             (0x7ul << SYS_BODCTL_BODVL_Pos)                   /*!< SYS_T::BODCTL: BODVL Mask              */

#define SYS_IVSCTL_VTEMPEN_Pos           (0)                                               /*!< SYS_T::IVSCTL: VTEMPEN Position        */
#define SYS_IVSCTL_VTEMPEN_Msk           (0x1ul << SYS_IVSCTL_VTEMPEN_Pos)                 /*!< SYS_T::IVSCTL: VTEMPEN Mask            */

#define SYS_IVSCTL_VBATUGEN_Pos          (1)                                               /*!< SYS_T::IVSCTL: VBATUGEN Position       */
#define SYS_IVSCTL_VBATUGEN_Msk          (0x1ul << SYS_IVSCTL_VBATUGEN_Pos)                /*!< SYS_T::IVSCTL: VBATUGEN Mask           */

#define SYS_PORCTL_POROFF_Pos            (0)                                               /*!< SYS_T::PORCTL: POROFF Position         */
#define SYS_PORCTL_POROFF_Msk            (0xfffful << SYS_PORCTL_POROFF_Pos)               /*!< SYS_T::PORCTL: POROFF Mask             */

#define SYS_VREFCTL_VREFCTL_Pos          (0)                                               /*!< SYS_T::VREFCTL: VREFCTL Position       */
#define SYS_VREFCTL_VREFCTL_Msk          (0x1ful << SYS_VREFCTL_VREFCTL_Pos)               /*!< SYS_T::VREFCTL: VREFCTL Mask           */

#define SYS_VREFCTL_PRELOAD_SEL_Pos      (6)                                               /*!< SYS_T::VREFCTL: PRELOAD_SEL Position   */
#define SYS_VREFCTL_PRELOAD_SEL_Msk      (0x3ul << SYS_VREFCTL_PRELOAD_SEL_Pos)            /*!< SYS_T::VREFCTL: PRELOAD_SEL Mask       */

#define SYS_USBPHY_USBROLE_Pos           (0)                                               /*!< SYS_T::USBPHY: USBROLE Position        */
#define SYS_USBPHY_USBROLE_Msk           (0x3ul << SYS_USBPHY_USBROLE_Pos)                 /*!< SYS_T::USBPHY: USBROLE Mask            */

#define SYS_USBPHY_SBO_Pos               (2)                                               /*!< SYS_T::USBPHY: SBO Position            */
#define SYS_USBPHY_SBO_Msk               (0x1ul << SYS_USBPHY_SBO_Pos)                     /*!< SYS_T::USBPHY: SBO Mask                */

#define SYS_USBPHY_USBEN_Pos             (8)                                               /*!< SYS_T::USBPHY: USBEN Position          */
#define SYS_USBPHY_USBEN_Msk             (0x1ul << SYS_USBPHY_USBEN_Pos)                   /*!< SYS_T::USBPHY: USBEN Mask              */

#define SYS_USBPHY_HSUSBROLE_Pos         (16)                                              /*!< SYS_T::USBPHY: HSUSBROLE Position      */
#define SYS_USBPHY_HSUSBROLE_Msk         (0x3ul << SYS_USBPHY_HSUSBROLE_Pos)               /*!< SYS_T::USBPHY: HSUSBROLE Mask          */

#define SYS_USBPHY_HSUSBEN_Pos           (24)                                              /*!< SYS_T::USBPHY: HSUSBEN Position        */
#define SYS_USBPHY_HSUSBEN_Msk           (0x1ul << SYS_USBPHY_HSUSBEN_Pos)                 /*!< SYS_T::USBPHY: HSUSBEN Mask            */

#define SYS_USBPHY_HSUSBACT_Pos          (25)                                              /*!< SYS_T::USBPHY: HSUSBACT Position       */
#define SYS_USBPHY_HSUSBACT_Msk          (0x1ul << SYS_USBPHY_HSUSBACT_Pos)                /*!< SYS_T::USBPHY: HSUSBACT Mask           */

#define SYS_GPA_MFPL_PA0MFP_Pos          (0)                                               /*!< SYS_T::GPA_MFPL: PA0MFP Position       */
#define SYS_GPA_MFPL_PA0MFP_Msk          (0xful << SYS_GPA_MFPL_PA0MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA0MFP Mask           */

#define SYS_GPA_MFPL_PA1MFP_Pos          (4)                                               /*!< SYS_T::GPA_MFPL: PA1MFP Position       */
#define SYS_GPA_MFPL_PA1MFP_Msk          (0xful << SYS_GPA_MFPL_PA1MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA1MFP Mask           */

#define SYS_GPA_MFPL_PA2MFP_Pos          (8)                                               /*!< SYS_T::GPA_MFPL: PA2MFP Position       */
#define SYS_GPA_MFPL_PA2MFP_Msk          (0xful << SYS_GPA_MFPL_PA2MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA2MFP Mask           */

#define SYS_GPA_MFPL_PA3MFP_Pos          (12)                                              /*!< SYS_T::GPA_MFPL: PA3MFP Position       */
#define SYS_GPA_MFPL_PA3MFP_Msk          (0xful << SYS_GPA_MFPL_PA3MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA3MFP Mask           */

#define SYS_GPA_MFPL_PA4MFP_Pos          (16)                                              /*!< SYS_T::GPA_MFPL: PA4MFP Position       */
#define SYS_GPA_MFPL_PA4MFP_Msk          (0xful << SYS_GPA_MFPL_PA4MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA4MFP Mask           */

#define SYS_GPA_MFPL_PA5MFP_Pos          (20)                                              /*!< SYS_T::GPA_MFPL: PA5MFP Position       */
#define SYS_GPA_MFPL_PA5MFP_Msk          (0xful << SYS_GPA_MFPL_PA5MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA5MFP Mask           */

#define SYS_GPA_MFPL_PA6MFP_Pos          (24)                                              /*!< SYS_T::GPA_MFPL: PA6MFP Position       */
#define SYS_GPA_MFPL_PA6MFP_Msk          (0xful << SYS_GPA_MFPL_PA6MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA6MFP Mask           */

#define SYS_GPA_MFPL_PA7MFP_Pos          (28)                                              /*!< SYS_T::GPA_MFPL: PA7MFP Position       */
#define SYS_GPA_MFPL_PA7MFP_Msk          (0xful << SYS_GPA_MFPL_PA7MFP_Pos)                /*!< SYS_T::GPA_MFPL: PA7MFP Mask           */

#define SYS_GPA_MFPH_PA8MFP_Pos          (0)                                               /*!< SYS_T::GPA_MFPH: PA8MFP Position       */
#define SYS_GPA_MFPH_PA8MFP_Msk          (0xful << SYS_GPA_MFPH_PA8MFP_Pos)                /*!< SYS_T::GPA_MFPH: PA8MFP Mask           */

#define SYS_GPA_MFPH_PA9MFP_Pos          (4)                                               /*!< SYS_T::GPA_MFPH: PA9MFP Position       */
#define SYS_GPA_MFPH_PA9MFP_Msk          (0xful << SYS_GPA_MFPH_PA9MFP_Pos)                /*!< SYS_T::GPA_MFPH: PA9MFP Mask           */

#define SYS_GPA_MFPH_PA10MFP_Pos         (8)                                               /*!< SYS_T::GPA_MFPH: PA10MFP Position      */
#define SYS_GPA_MFPH_PA10MFP_Msk         (0xful << SYS_GPA_MFPH_PA10MFP_Pos)               /*!< SYS_T::GPA_MFPH: PA10MFP Mask          */

#define SYS_GPA_MFPH_PA11MFP_Pos         (12)                                              /*!< SYS_T::GPA_MFPH: PA11MFP Position      */
#define SYS_GPA_MFPH_PA11MFP_Msk         (0xful << SYS_GPA_MFPH_PA11MFP_Pos)               /*!< SYS_T::GPA_MFPH: PA11MFP Mask          */

#define SYS_GPA_MFPH_PA12MFP_Pos         (16)                                              /*!< SYS_T::GPA_MFPH: PA12MFP Position      */
#define SYS_GPA_MFPH_PA12MFP_Msk         (0xful << SYS_GPA_MFPH_PA12MFP_Pos)               /*!< SYS_T::GPA_MFPH: PA12MFP Mask          */

#define SYS_GPA_MFPH_PA13MFP_Pos         (20)                                              /*!< SYS_T::GPA_MFPH: PA13MFP Position      */
#define SYS_GPA_MFPH_PA13MFP_Msk         (0xful << SYS_GPA_MFPH_PA13MFP_Pos)               /*!< SYS_T::GPA_MFPH: PA13MFP Mask          */

#define SYS_GPA_MFPH_PA14MFP_Pos         (24)                                              /*!< SYS_T::GPA_MFPH: PA14MFP Position      */
#define SYS_GPA_MFPH_PA14MFP_Msk         (0xful << SYS_GPA_MFPH_PA14MFP_Pos)               /*!< SYS_T::GPA_MFPH: PA14MFP Mask          */

#define SYS_GPA_MFPH_PA15MFP_Pos         (28)                                              /*!< SYS_T::GPA_MFPH: PA15MFP Position      */
#define SYS_GPA_MFPH_PA15MFP_Msk         (0xful << SYS_GPA_MFPH_PA15MFP_Pos)               /*!< SYS_T::GPA_MFPH: PA15MFP Mask          */

#define SYS_GPB_MFPL_PB0MFP_Pos          (0)                                               /*!< SYS_T::GPB_MFPL: PB0MFP Position       */
#define SYS_GPB_MFPL_PB0MFP_Msk          (0xful << SYS_GPB_MFPL_PB0MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB0MFP Mask           */

#define SYS_GPB_MFPL_PB1MFP_Pos          (4)                                               /*!< SYS_T::GPB_MFPL: PB1MFP Position       */
#define SYS_GPB_MFPL_PB1MFP_Msk          (0xful << SYS_GPB_MFPL_PB1MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB1MFP Mask           */

#define SYS_GPB_MFPL_PB2MFP_Pos          (8)                                               /*!< SYS_T::GPB_MFPL: PB2MFP Position       */
#define SYS_GPB_MFPL_PB2MFP_Msk          (0xful << SYS_GPB_MFPL_PB2MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB2MFP Mask           */

#define SYS_GPB_MFPL_PB3MFP_Pos          (12)                                              /*!< SYS_T::GPB_MFPL: PB3MFP Position       */
#define SYS_GPB_MFPL_PB3MFP_Msk          (0xful << SYS_GPB_MFPL_PB3MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB3MFP Mask           */

#define SYS_GPB_MFPL_PB4MFP_Pos          (16)                                              /*!< SYS_T::GPB_MFPL: PB4MFP Position       */
#define SYS_GPB_MFPL_PB4MFP_Msk          (0xful << SYS_GPB_MFPL_PB4MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB4MFP Mask           */

#define SYS_GPB_MFPL_PB5MFP_Pos          (20)                                              /*!< SYS_T::GPB_MFPL: PB5MFP Position       */
#define SYS_GPB_MFPL_PB5MFP_Msk          (0xful << SYS_GPB_MFPL_PB5MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB5MFP Mask           */

#define SYS_GPB_MFPL_PB6MFP_Pos          (24)                                              /*!< SYS_T::GPB_MFPL: PB6MFP Position       */
#define SYS_GPB_MFPL_PB6MFP_Msk          (0xful << SYS_GPB_MFPL_PB6MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB6MFP Mask           */

#define SYS_GPB_MFPL_PB7MFP_Pos          (28)                                              /*!< SYS_T::GPB_MFPL: PB7MFP Position       */
#define SYS_GPB_MFPL_PB7MFP_Msk          (0xful << SYS_GPB_MFPL_PB7MFP_Pos)                /*!< SYS_T::GPB_MFPL: PB7MFP Mask           */

#define SYS_GPB_MFPH_PB8MFP_Pos          (0)                                               /*!< SYS_T::GPB_MFPH: PB8MFP Position       */
#define SYS_GPB_MFPH_PB8MFP_Msk          (0xful << SYS_GPB_MFPH_PB8MFP_Pos)                /*!< SYS_T::GPB_MFPH: PB8MFP Mask           */

#define SYS_GPB_MFPH_PB9MFP_Pos          (4)                                               /*!< SYS_T::GPB_MFPH: PB9MFP Position       */
#define SYS_GPB_MFPH_PB9MFP_Msk          (0xful << SYS_GPB_MFPH_PB9MFP_Pos)                /*!< SYS_T::GPB_MFPH: PB9MFP Mask           */

#define SYS_GPB_MFPH_PB10MFP_Pos         (8)                                               /*!< SYS_T::GPB_MFPH: PB10MFP Position      */
#define SYS_GPB_MFPH_PB10MFP_Msk         (0xful << SYS_GPB_MFPH_PB10MFP_Pos)               /*!< SYS_T::GPB_MFPH: PB10MFP Mask          */

#define SYS_GPB_MFPH_PB11MFP_Pos         (12)                                              /*!< SYS_T::GPB_MFPH: PB11MFP Position      */
#define SYS_GPB_MFPH_PB11MFP_Msk         (0xful << SYS_GPB_MFPH_PB11MFP_Pos)               /*!< SYS_T::GPB_MFPH: PB11MFP Mask          */

#define SYS_GPB_MFPH_PB12MFP_Pos         (16)                                              /*!< SYS_T::GPB_MFPH: PB12MFP Position      */
#define SYS_GPB_MFPH_PB12MFP_Msk         (0xful << SYS_GPB_MFPH_PB12MFP_Pos)               /*!< SYS_T::GPB_MFPH: PB12MFP Mask          */

#define SYS_GPB_MFPH_PB13MFP_Pos         (20)                                              /*!< SYS_T::GPB_MFPH: PB13MFP Position      */
#define SYS_GPB_MFPH_PB13MFP_Msk         (0xful << SYS_GPB_MFPH_PB13MFP_Pos)               /*!< SYS_T::GPB_MFPH: PB13MFP Mask          */

#define SYS_GPB_MFPH_PB14MFP_Pos         (24)                                              /*!< SYS_T::GPB_MFPH: PB14MFP Position      */
#define SYS_GPB_MFPH_PB14MFP_Msk         (0xful << SYS_GPB_MFPH_PB14MFP_Pos)               /*!< SYS_T::GPB_MFPH: PB14MFP Mask          */

#define SYS_GPB_MFPH_PB15MFP_Pos         (28)                                              /*!< SYS_T::GPB_MFPH: PB15MFP Position      */
#define SYS_GPB_MFPH_PB15MFP_Msk         (0xful << SYS_GPB_MFPH_PB15MFP_Pos)               /*!< SYS_T::GPB_MFPH: PB15MFP Mask          */

#define SYS_GPC_MFPL_PC0MFP_Pos          (0)                                               /*!< SYS_T::GPC_MFPL: PC0MFP Position       */
#define SYS_GPC_MFPL_PC0MFP_Msk          (0xful << SYS_GPC_MFPL_PC0MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC0MFP Mask           */

#define SYS_GPC_MFPL_PC1MFP_Pos          (4)                                               /*!< SYS_T::GPC_MFPL: PC1MFP Position       */
#define SYS_GPC_MFPL_PC1MFP_Msk          (0xful << SYS_GPC_MFPL_PC1MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC1MFP Mask           */

#define SYS_GPC_MFPL_PC2MFP_Pos          (8)                                               /*!< SYS_T::GPC_MFPL: PC2MFP Position       */
#define SYS_GPC_MFPL_PC2MFP_Msk          (0xful << SYS_GPC_MFPL_PC2MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC2MFP Mask           */

#define SYS_GPC_MFPL_PC3MFP_Pos          (12)                                              /*!< SYS_T::GPC_MFPL: PC3MFP Position       */
#define SYS_GPC_MFPL_PC3MFP_Msk          (0xful << SYS_GPC_MFPL_PC3MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC3MFP Mask           */

#define SYS_GPC_MFPL_PC4MFP_Pos          (16)                                              /*!< SYS_T::GPC_MFPL: PC4MFP Position       */
#define SYS_GPC_MFPL_PC4MFP_Msk          (0xful << SYS_GPC_MFPL_PC4MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC4MFP Mask           */

#define SYS_GPC_MFPL_PC5MFP_Pos          (20)                                              /*!< SYS_T::GPC_MFPL: PC5MFP Position       */
#define SYS_GPC_MFPL_PC5MFP_Msk          (0xful << SYS_GPC_MFPL_PC5MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC5MFP Mask           */

#define SYS_GPC_MFPL_PC6MFP_Pos          (24)                                              /*!< SYS_T::GPC_MFPL: PC6MFP Position       */
#define SYS_GPC_MFPL_PC6MFP_Msk          (0xful << SYS_GPC_MFPL_PC6MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC6MFP Mask           */

#define SYS_GPC_MFPL_PC7MFP_Pos          (28)                                              /*!< SYS_T::GPC_MFPL: PC7MFP Position       */
#define SYS_GPC_MFPL_PC7MFP_Msk          (0xful << SYS_GPC_MFPL_PC7MFP_Pos)                /*!< SYS_T::GPC_MFPL: PC7MFP Mask           */

#define SYS_GPC_MFPH_PC8MFP_Pos          (0)                                               /*!< SYS_T::GPC_MFPH: PC8MFP Position       */
#define SYS_GPC_MFPH_PC8MFP_Msk          (0xful << SYS_GPC_MFPH_PC8MFP_Pos)                /*!< SYS_T::GPC_MFPH: PC8MFP Mask           */

#define SYS_GPC_MFPH_PC9MFP_Pos          (4)                                               /*!< SYS_T::GPC_MFPH: PC9MFP Position       */
#define SYS_GPC_MFPH_PC9MFP_Msk          (0xful << SYS_GPC_MFPH_PC9MFP_Pos)                /*!< SYS_T::GPC_MFPH: PC9MFP Mask           */

#define SYS_GPC_MFPH_PC10MFP_Pos         (8)                                               /*!< SYS_T::GPC_MFPH: PC10MFP Position      */
#define SYS_GPC_MFPH_PC10MFP_Msk         (0xful << SYS_GPC_MFPH_PC10MFP_Pos)               /*!< SYS_T::GPC_MFPH: PC10MFP Mask          */

#define SYS_GPC_MFPH_PC11MFP_Pos         (12)                                              /*!< SYS_T::GPC_MFPH: PC11MFP Position      */
#define SYS_GPC_MFPH_PC11MFP_Msk         (0xful << SYS_GPC_MFPH_PC11MFP_Pos)               /*!< SYS_T::GPC_MFPH: PC11MFP Mask          */

#define SYS_GPC_MFPH_PC12MFP_Pos         (16)                                              /*!< SYS_T::GPC_MFPH: PC12MFP Position      */
#define SYS_GPC_MFPH_PC12MFP_Msk         (0xful << SYS_GPC_MFPH_PC12MFP_Pos)               /*!< SYS_T::GPC_MFPH: PC12MFP Mask          */

#define SYS_GPC_MFPH_PC13MFP_Pos         (20)                                              /*!< SYS_T::GPC_MFPH: PC13MFP Position      */
#define SYS_GPC_MFPH_PC13MFP_Msk         (0xful << SYS_GPC_MFPH_PC13MFP_Pos)               /*!< SYS_T::GPC_MFPH: PC13MFP Mask          */

#define SYS_GPC_MFPH_PC14MFP_Pos         (24)                                              /*!< SYS_T::GPC_MFPH: PC14MFP Position      */
#define SYS_GPC_MFPH_PC14MFP_Msk         (0xful << SYS_GPC_MFPH_PC14MFP_Pos)               /*!< SYS_T::GPC_MFPH: PC14MFP Mask          */

#define SYS_GPC_MFPH_PC15MFP_Pos         (28)                                              /*!< SYS_T::GPC_MFPH: PC15MFP Position      */
#define SYS_GPC_MFPH_PC15MFP_Msk         (0xful << SYS_GPC_MFPH_PC15MFP_Pos)               /*!< SYS_T::GPC_MFPH: PC15MFP Mask          */

#define SYS_GPD_MFPL_PD0MFP_Pos          (0)                                               /*!< SYS_T::GPD_MFPL: PD0MFP Position       */
#define SYS_GPD_MFPL_PD0MFP_Msk          (0xful << SYS_GPD_MFPL_PD0MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD0MFP Mask           */

#define SYS_GPD_MFPL_PD1MFP_Pos          (4)                                               /*!< SYS_T::GPD_MFPL: PD1MFP Position       */
#define SYS_GPD_MFPL_PD1MFP_Msk          (0xful << SYS_GPD_MFPL_PD1MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD1MFP Mask           */

#define SYS_GPD_MFPL_PD2MFP_Pos          (8)                                               /*!< SYS_T::GPD_MFPL: PD2MFP Position       */
#define SYS_GPD_MFPL_PD2MFP_Msk          (0xful << SYS_GPD_MFPL_PD2MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD2MFP Mask           */

#define SYS_GPD_MFPL_PD3MFP_Pos          (12)                                              /*!< SYS_T::GPD_MFPL: PD3MFP Position       */
#define SYS_GPD_MFPL_PD3MFP_Msk          (0xful << SYS_GPD_MFPL_PD3MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD3MFP Mask           */

#define SYS_GPD_MFPL_PD4MFP_Pos          (16)                                              /*!< SYS_T::GPD_MFPL: PD4MFP Position       */
#define SYS_GPD_MFPL_PD4MFP_Msk          (0xful << SYS_GPD_MFPL_PD4MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD4MFP Mask           */

#define SYS_GPD_MFPL_PD5MFP_Pos          (20)                                              /*!< SYS_T::GPD_MFPL: PD5MFP Position       */
#define SYS_GPD_MFPL_PD5MFP_Msk          (0xful << SYS_GPD_MFPL_PD5MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD5MFP Mask           */

#define SYS_GPD_MFPL_PD6MFP_Pos          (24)                                              /*!< SYS_T::GPD_MFPL: PD6MFP Position       */
#define SYS_GPD_MFPL_PD6MFP_Msk          (0xful << SYS_GPD_MFPL_PD6MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD6MFP Mask           */

#define SYS_GPD_MFPL_PD7MFP_Pos          (28)                                              /*!< SYS_T::GPD_MFPL: PD7MFP Position       */
#define SYS_GPD_MFPL_PD7MFP_Msk          (0xful << SYS_GPD_MFPL_PD7MFP_Pos)                /*!< SYS_T::GPD_MFPL: PD7MFP Mask           */

#define SYS_GPD_MFPH_PD8MFP_Pos          (0)                                               /*!< SYS_T::GPD_MFPH: PD8MFP Position       */
#define SYS_GPD_MFPH_PD8MFP_Msk          (0xful << SYS_GPD_MFPH_PD8MFP_Pos)                /*!< SYS_T::GPD_MFPH: PD8MFP Mask           */

#define SYS_GPD_MFPH_PD9MFP_Pos          (4)                                               /*!< SYS_T::GPD_MFPH: PD9MFP Position       */
#define SYS_GPD_MFPH_PD9MFP_Msk          (0xful << SYS_GPD_MFPH_PD9MFP_Pos)                /*!< SYS_T::GPD_MFPH: PD9MFP Mask           */

#define SYS_GPD_MFPH_PD10MFP_Pos         (8)                                               /*!< SYS_T::GPD_MFPH: PD10MFP Position      */
#define SYS_GPD_MFPH_PD10MFP_Msk         (0xful << SYS_GPD_MFPH_PD10MFP_Pos)               /*!< SYS_T::GPD_MFPH: PD10MFP Mask          */

#define SYS_GPD_MFPH_PD11MFP_Pos         (12)                                              /*!< SYS_T::GPD_MFPH: PD11MFP Position      */
#define SYS_GPD_MFPH_PD11MFP_Msk         (0xful << SYS_GPD_MFPH_PD11MFP_Pos)               /*!< SYS_T::GPD_MFPH: PD11MFP Mask          */

#define SYS_GPD_MFPH_PD12MFP_Pos         (16)                                              /*!< SYS_T::GPD_MFPH: PD12MFP Position      */
#define SYS_GPD_MFPH_PD12MFP_Msk         (0xful << SYS_GPD_MFPH_PD12MFP_Pos)               /*!< SYS_T::GPD_MFPH: PD12MFP Mask          */

#define SYS_GPD_MFPH_PD13MFP_Pos         (20)                                              /*!< SYS_T::GPD_MFPH: PD13MFP Position      */
#define SYS_GPD_MFPH_PD13MFP_Msk         (0xful << SYS_GPD_MFPH_PD13MFP_Pos)               /*!< SYS_T::GPD_MFPH: PD13MFP Mask          */

#define SYS_GPD_MFPH_PD14MFP_Pos         (24)                                              /*!< SYS_T::GPD_MFPH: PD14MFP Position      */
#define SYS_GPD_MFPH_PD14MFP_Msk         (0xful << SYS_GPD_MFPH_PD14MFP_Pos)               /*!< SYS_T::GPD_MFPH: PD14MFP Mask          */

#define SYS_GPD_MFPH_PD15MFP_Pos         (28)                                              /*!< SYS_T::GPD_MFPH: PD15MFP Position      */
#define SYS_GPD_MFPH_PD15MFP_Msk         (0xful << SYS_GPD_MFPH_PD15MFP_Pos)               /*!< SYS_T::GPD_MFPH: PD15MFP Mask          */

#define SYS_GPE_MFPL_PE0MFP_Pos          (0)                                               /*!< SYS_T::GPE_MFPL: PE0MFP Position       */
#define SYS_GPE_MFPL_PE0MFP_Msk          (0xful << SYS_GPE_MFPL_PE0MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE0MFP Mask           */

#define SYS_GPE_MFPL_PE1MFP_Pos          (4)                                               /*!< SYS_T::GPE_MFPL: PE1MFP Position       */
#define SYS_GPE_MFPL_PE1MFP_Msk          (0xful << SYS_GPE_MFPL_PE1MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE1MFP Mask           */

#define SYS_GPE_MFPL_PE2MFP_Pos          (8)                                               /*!< SYS_T::GPE_MFPL: PE2MFP Position       */
#define SYS_GPE_MFPL_PE2MFP_Msk          (0xful << SYS_GPE_MFPL_PE2MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE2MFP Mask           */

#define SYS_GPE_MFPL_PE3MFP_Pos          (12)                                              /*!< SYS_T::GPE_MFPL: PE3MFP Position       */
#define SYS_GPE_MFPL_PE3MFP_Msk          (0xful << SYS_GPE_MFPL_PE3MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE3MFP Mask           */

#define SYS_GPE_MFPL_PE4MFP_Pos          (16)                                              /*!< SYS_T::GPE_MFPL: PE4MFP Position       */
#define SYS_GPE_MFPL_PE4MFP_Msk          (0xful << SYS_GPE_MFPL_PE4MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE4MFP Mask           */

#define SYS_GPE_MFPL_PE5MFP_Pos          (20)                                              /*!< SYS_T::GPE_MFPL: PE5MFP Position       */
#define SYS_GPE_MFPL_PE5MFP_Msk          (0xful << SYS_GPE_MFPL_PE5MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE5MFP Mask           */

#define SYS_GPE_MFPL_PE6MFP_Pos          (24)                                              /*!< SYS_T::GPE_MFPL: PE6MFP Position       */
#define SYS_GPE_MFPL_PE6MFP_Msk          (0xful << SYS_GPE_MFPL_PE6MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE6MFP Mask           */

#define SYS_GPE_MFPL_PE7MFP_Pos          (28)                                              /*!< SYS_T::GPE_MFPL: PE7MFP Position       */
#define SYS_GPE_MFPL_PE7MFP_Msk          (0xful << SYS_GPE_MFPL_PE7MFP_Pos)                /*!< SYS_T::GPE_MFPL: PE7MFP Mask           */

#define SYS_GPE_MFPH_PE8MFP_Pos          (0)                                               /*!< SYS_T::GPE_MFPH: PE8MFP Position       */
#define SYS_GPE_MFPH_PE8MFP_Msk          (0xful << SYS_GPE_MFPH_PE8MFP_Pos)                /*!< SYS_T::GPE_MFPH: PE8MFP Mask           */

#define SYS_GPE_MFPH_PE9MFP_Pos          (4)                                               /*!< SYS_T::GPE_MFPH: PE9MFP Position       */
#define SYS_GPE_MFPH_PE9MFP_Msk          (0xful << SYS_GPE_MFPH_PE9MFP_Pos)                /*!< SYS_T::GPE_MFPH: PE9MFP Mask           */

#define SYS_GPE_MFPH_PE10MFP_Pos         (8)                                               /*!< SYS_T::GPE_MFPH: PE10MFP Position      */
#define SYS_GPE_MFPH_PE10MFP_Msk         (0xful << SYS_GPE_MFPH_PE10MFP_Pos)               /*!< SYS_T::GPE_MFPH: PE10MFP Mask          */

#define SYS_GPE_MFPH_PE11MFP_Pos         (12)                                              /*!< SYS_T::GPE_MFPH: PE11MFP Position      */
#define SYS_GPE_MFPH_PE11MFP_Msk         (0xful << SYS_GPE_MFPH_PE11MFP_Pos)               /*!< SYS_T::GPE_MFPH: PE11MFP Mask          */

#define SYS_GPE_MFPH_PE12MFP_Pos         (16)                                              /*!< SYS_T::GPE_MFPH: PE12MFP Position      */
#define SYS_GPE_MFPH_PE12MFP_Msk         (0xful << SYS_GPE_MFPH_PE12MFP_Pos)               /*!< SYS_T::GPE_MFPH: PE12MFP Mask          */

#define SYS_GPE_MFPH_PE13MFP_Pos         (20)                                              /*!< SYS_T::GPE_MFPH: PE13MFP Position      */
#define SYS_GPE_MFPH_PE13MFP_Msk         (0xful << SYS_GPE_MFPH_PE13MFP_Pos)               /*!< SYS_T::GPE_MFPH: PE13MFP Mask          */

#define SYS_GPE_MFPH_PE14MFP_Pos         (24)                                              /*!< SYS_T::GPE_MFPH: PE14MFP Position      */
#define SYS_GPE_MFPH_PE14MFP_Msk         (0xful << SYS_GPE_MFPH_PE14MFP_Pos)               /*!< SYS_T::GPE_MFPH: PE14MFP Mask          */

#define SYS_GPE_MFPH_PE15MFP_Pos         (28)                                              /*!< SYS_T::GPE_MFPH: PE15MFP Position      */
#define SYS_GPE_MFPH_PE15MFP_Msk         (0xful << SYS_GPE_MFPH_PE15MFP_Pos)               /*!< SYS_T::GPE_MFPH: PE15MFP Mask          */

#define SYS_GPF_MFPL_PF0MFP_Pos          (0)                                               /*!< SYS_T::GPF_MFPL: PF0MFP Position       */
#define SYS_GPF_MFPL_PF0MFP_Msk          (0xful << SYS_GPF_MFPL_PF0MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF0MFP Mask           */

#define SYS_GPF_MFPL_PF1MFP_Pos          (4)                                               /*!< SYS_T::GPF_MFPL: PF1MFP Position       */
#define SYS_GPF_MFPL_PF1MFP_Msk          (0xful << SYS_GPF_MFPL_PF1MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF1MFP Mask           */

#define SYS_GPF_MFPL_PF2MFP_Pos          (8)                                               /*!< SYS_T::GPF_MFPL: PF2MFP Position       */
#define SYS_GPF_MFPL_PF2MFP_Msk          (0xful << SYS_GPF_MFPL_PF2MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF2MFP Mask           */

#define SYS_GPF_MFPL_PF3MFP_Pos          (12)                                              /*!< SYS_T::GPF_MFPL: PF3MFP Position       */
#define SYS_GPF_MFPL_PF3MFP_Msk          (0xful << SYS_GPF_MFPL_PF3MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF3MFP Mask           */

#define SYS_GPF_MFPL_PF4MFP_Pos          (16)                                              /*!< SYS_T::GPF_MFPL: PF4MFP Position       */
#define SYS_GPF_MFPL_PF4MFP_Msk          (0xful << SYS_GPF_MFPL_PF4MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF4MFP Mask           */

#define SYS_GPF_MFPL_PF5MFP_Pos          (20)                                              /*!< SYS_T::GPF_MFPL: PF5MFP Position       */
#define SYS_GPF_MFPL_PF5MFP_Msk          (0xful << SYS_GPF_MFPL_PF5MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF5MFP Mask           */

#define SYS_GPF_MFPL_PF6MFP_Pos          (24)                                              /*!< SYS_T::GPF_MFPL: PF6MFP Position       */
#define SYS_GPF_MFPL_PF6MFP_Msk          (0xful << SYS_GPF_MFPL_PF6MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF6MFP Mask           */

#define SYS_GPF_MFPL_PF7MFP_Pos          (28)                                              /*!< SYS_T::GPF_MFPL: PF7MFP Position       */
#define SYS_GPF_MFPL_PF7MFP_Msk          (0xful << SYS_GPF_MFPL_PF7MFP_Pos)                /*!< SYS_T::GPF_MFPL: PF7MFP Mask           */

#define SYS_GPF_MFPH_PF8MFP_Pos          (0)                                               /*!< SYS_T::GPF_MFPH: PF8MFP Position       */
#define SYS_GPF_MFPH_PF8MFP_Msk          (0xful << SYS_GPF_MFPH_PF8MFP_Pos)                /*!< SYS_T::GPF_MFPH: PF8MFP Mask           */

#define SYS_GPF_MFPH_PF9MFP_Pos          (4)                                               /*!< SYS_T::GPF_MFPH: PF9MFP Position       */
#define SYS_GPF_MFPH_PF9MFP_Msk          (0xful << SYS_GPF_MFPH_PF9MFP_Pos)                /*!< SYS_T::GPF_MFPH: PF9MFP Mask           */

#define SYS_GPF_MFPH_PF10MFP_Pos         (8)                                               /*!< SYS_T::GPF_MFPH: PF10MFP Position      */
#define SYS_GPF_MFPH_PF10MFP_Msk         (0xful << SYS_GPF_MFPH_PF10MFP_Pos)               /*!< SYS_T::GPF_MFPH: PF10MFP Mask          */

#define SYS_GPF_MFPH_PF11MFP_Pos         (12)                                              /*!< SYS_T::GPF_MFPH: PF11MFP Position      */
#define SYS_GPF_MFPH_PF11MFP_Msk         (0xful << SYS_GPF_MFPH_PF11MFP_Pos)               /*!< SYS_T::GPF_MFPH: PF11MFP Mask          */

#define SYS_GPF_MFPH_PF12MFP_Pos         (16)                                              /*!< SYS_T::GPF_MFPH: PF12MFP Position      */
#define SYS_GPF_MFPH_PF12MFP_Msk         (0xful << SYS_GPF_MFPH_PF12MFP_Pos)               /*!< SYS_T::GPF_MFPH: PF12MFP Mask          */

#define SYS_GPF_MFPH_PF13MFP_Pos         (20)                                              /*!< SYS_T::GPF_MFPH: PF13MFP Position      */
#define SYS_GPF_MFPH_PF13MFP_Msk         (0xful << SYS_GPF_MFPH_PF13MFP_Pos)               /*!< SYS_T::GPF_MFPH: PF13MFP Mask          */

#define SYS_GPF_MFPH_PF14MFP_Pos         (24)                                              /*!< SYS_T::GPF_MFPH: PF14MFP Position      */
#define SYS_GPF_MFPH_PF14MFP_Msk         (0xful << SYS_GPF_MFPH_PF14MFP_Pos)               /*!< SYS_T::GPF_MFPH: PF14MFP Mask          */

#define SYS_GPF_MFPH_PF15MFP_Pos         (28)                                              /*!< SYS_T::GPF_MFPH: PF15MFP Position      */
#define SYS_GPF_MFPH_PF15MFP_Msk         (0xful << SYS_GPF_MFPH_PF15MFP_Pos)               /*!< SYS_T::GPF_MFPH: PF15MFP Mask          */

#define SYS_GPG_MFPL_PG0MFP_Pos          (0)                                               /*!< SYS_T::GPG_MFPL: PG0MFP Position       */
#define SYS_GPG_MFPL_PG0MFP_Msk          (0xful << SYS_GPG_MFPL_PG0MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG0MFP Mask           */

#define SYS_GPG_MFPL_PG1MFP_Pos          (4)                                               /*!< SYS_T::GPG_MFPL: PG1MFP Position       */
#define SYS_GPG_MFPL_PG1MFP_Msk          (0xful << SYS_GPG_MFPL_PG1MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG1MFP Mask           */

#define SYS_GPG_MFPL_PG2MFP_Pos          (8)                                               /*!< SYS_T::GPG_MFPL: PG2MFP Position       */
#define SYS_GPG_MFPL_PG2MFP_Msk          (0xful << SYS_GPG_MFPL_PG2MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG2MFP Mask           */

#define SYS_GPG_MFPL_PG3MFP_Pos          (12)                                              /*!< SYS_T::GPG_MFPL: PG3MFP Position       */
#define SYS_GPG_MFPL_PG3MFP_Msk          (0xful << SYS_GPG_MFPL_PG3MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG3MFP Mask           */

#define SYS_GPG_MFPL_PG4MFP_Pos          (16)                                              /*!< SYS_T::GPG_MFPL: PG4MFP Position       */
#define SYS_GPG_MFPL_PG4MFP_Msk          (0xful << SYS_GPG_MFPL_PG4MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG4MFP Mask           */

#define SYS_GPG_MFPL_PG5MFP_Pos          (20)                                              /*!< SYS_T::GPG_MFPL: PG5MFP Position       */
#define SYS_GPG_MFPL_PG5MFP_Msk          (0xful << SYS_GPG_MFPL_PG5MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG5MFP Mask           */

#define SYS_GPG_MFPL_PG6MFP_Pos          (24)                                              /*!< SYS_T::GPG_MFPL: PG6MFP Position       */
#define SYS_GPG_MFPL_PG6MFP_Msk          (0xful << SYS_GPG_MFPL_PG6MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG6MFP Mask           */

#define SYS_GPG_MFPL_PG7MFP_Pos          (28)                                              /*!< SYS_T::GPG_MFPL: PG7MFP Position       */
#define SYS_GPG_MFPL_PG7MFP_Msk          (0xful << SYS_GPG_MFPL_PG7MFP_Pos)                /*!< SYS_T::GPG_MFPL: PG7MFP Mask           */

#define SYS_GPG_MFPH_PG8MFP_Pos          (0)                                               /*!< SYS_T::GPG_MFPH: PG8MFP Position       */
#define SYS_GPG_MFPH_PG8MFP_Msk          (0xful << SYS_GPG_MFPH_PG8MFP_Pos)                /*!< SYS_T::GPG_MFPH: PG8MFP Mask           */

#define SYS_GPG_MFPH_PG9MFP_Pos          (4)                                               /*!< SYS_T::GPG_MFPH: PG9MFP Position       */
#define SYS_GPG_MFPH_PG9MFP_Msk          (0xful << SYS_GPG_MFPH_PG9MFP_Pos)                /*!< SYS_T::GPG_MFPH: PG9MFP Mask           */

#define SYS_GPG_MFPH_PG10MFP_Pos         (8)                                               /*!< SYS_T::GPG_MFPH: PG10MFP Position      */
#define SYS_GPG_MFPH_PG10MFP_Msk         (0xful << SYS_GPG_MFPH_PG10MFP_Pos)               /*!< SYS_T::GPG_MFPH: PG10MFP Mask          */

#define SYS_GPG_MFPH_PG11MFP_Pos         (12)                                              /*!< SYS_T::GPG_MFPH: PG11MFP Position      */
#define SYS_GPG_MFPH_PG11MFP_Msk         (0xful << SYS_GPG_MFPH_PG11MFP_Pos)               /*!< SYS_T::GPG_MFPH: PG11MFP Mask          */

#define SYS_GPG_MFPH_PG12MFP_Pos         (16)                                              /*!< SYS_T::GPG_MFPH: PG12MFP Position      */
#define SYS_GPG_MFPH_PG12MFP_Msk         (0xful << SYS_GPG_MFPH_PG12MFP_Pos)               /*!< SYS_T::GPG_MFPH: PG12MFP Mask          */

#define SYS_GPG_MFPH_PG13MFP_Pos         (20)                                              /*!< SYS_T::GPG_MFPH: PG13MFP Position      */
#define SYS_GPG_MFPH_PG13MFP_Msk         (0xful << SYS_GPG_MFPH_PG13MFP_Pos)               /*!< SYS_T::GPG_MFPH: PG13MFP Mask          */

#define SYS_GPG_MFPH_PG14MFP_Pos         (24)                                              /*!< SYS_T::GPG_MFPH: PG14MFP Position      */
#define SYS_GPG_MFPH_PG14MFP_Msk         (0xful << SYS_GPG_MFPH_PG14MFP_Pos)               /*!< SYS_T::GPG_MFPH: PG14MFP Mask          */

#define SYS_GPG_MFPH_PG15MFP_Pos         (28)                                              /*!< SYS_T::GPG_MFPH: PG15MFP Position      */
#define SYS_GPG_MFPH_PG15MFP_Msk         (0xful << SYS_GPG_MFPH_PG15MFP_Pos)               /*!< SYS_T::GPG_MFPH: PG15MFP Mask          */

#define SYS_GPH_MFPL_PH0MFP_Pos          (0)                                               /*!< SYS_T::GPH_MFPL: PH0MFP Position       */
#define SYS_GPH_MFPL_PH0MFP_Msk          (0xful << SYS_GPH_MFPL_PH0MFP_Pos)                /*!< SYS_T::GPH_MFPL: PH0MFP Mask           */

#define SYS_GPH_MFPL_PH1MFP_Pos          (4)                                               /*!< SYS_T::GPH_MFPL: PH1MFP Position       */
#define SYS_GPH_MFPL_PH1MFP_Msk          (0xful << SYS_GPH_MFPL_PH1MFP_Pos)                /*!< SYS_T::GPH_MFPL: PH1MFP Mask           */

#define SYS_GPH_MFPL_PH2MFP_Pos          (8)                                               /*!< SYS_T::GPH_MFPL: PH2MFP Position       */
#define SYS_GPH_MFPL_PH2MFP_Msk          (0xful << SYS_GPH_MFPL_PH2MFP_Pos)                /*!< SYS_T::GPH_MFPL: PH2MFP Mask           */

#define SYS_GPH_MFPL_PH3MFP_Pos          (12)                                              /*!< SYS_T::GPH_MFPL: PH3MFP Position       */
#define SYS_GPH_MFPL_PH3MFP_Msk          (0xful << SYS_GPH_MFPL_PH3MFP_Pos)                /*!< SYS_T::GPH_MFPL: PH3MFP Mask           */

#define SYS_GPH_MFPL_PH4MFP_Pos          (16)                                              /*!< SYS_T::GPH_MFPL: PH4MFP Position       */
#define SYS_GPH_MFPL_PH4MFP_Msk          (0xful << SYS_GPH_MFPL_PH4MFP_Pos)                /*!< SYS_T::GPH_MFPL: PH4MFP Mask           */

#define SYS_GPH_MFPL_PH5MFP_Pos          (20)                                              /*!< SYS_T::GPH_MFPL: PH5MFP Position       */
#define SYS_GPH_MFPL_PH5MFP_Msk          (0xful << SYS_GPH_MFPL_PH5MFP_Pos)                /*!< SYS_T::GPH_MFPL: PH5MFP Mask           */

#define SYS_GPH_MFPL_PH6MFP_Pos          (24)                                              /*!< SYS_T::GPH_MFPL: PH6MFP Position       */
#define SYS_GPH_MFPL_PH6MFP_Msk          (0xful << SYS_GPH_MFPL_PH6MFP_Pos)                /*!< SYS_T::GPH_MFPL: PH6MFP Mask           */

#define SYS_GPH_MFPL_PH7MFP_Pos          (28)                                              /*!< SYS_T::GPH_MFPL: PH7MFP Position       */
#define SYS_GPH_MFPL_PH7MFP_Msk          (0xful << SYS_GPH_MFPL_PH7MFP_Pos)                /*!< SYS_T::GPH_MFPL: PH7MFP Mask           */

#define SYS_GPH_MFPH_PH8MFP_Pos          (0)                                               /*!< SYS_T::GPH_MFPH: PH8MFP Position       */
#define SYS_GPH_MFPH_PH8MFP_Msk          (0xful << SYS_GPH_MFPH_PH8MFP_Pos)                /*!< SYS_T::GPH_MFPH: PH8MFP Mask           */

#define SYS_GPH_MFPH_PH9MFP_Pos          (4)                                               /*!< SYS_T::GPH_MFPH: PH9MFP Position       */
#define SYS_GPH_MFPH_PH9MFP_Msk          (0xful << SYS_GPH_MFPH_PH9MFP_Pos)                /*!< SYS_T::GPH_MFPH: PH9MFP Mask           */

#define SYS_GPH_MFPH_PH10MFP_Pos         (8)                                               /*!< SYS_T::GPH_MFPH: PH10MFP Position      */
#define SYS_GPH_MFPH_PH10MFP_Msk         (0xful << SYS_GPH_MFPH_PH10MFP_Pos)               /*!< SYS_T::GPH_MFPH: PH10MFP Mask          */

#define SYS_GPH_MFPH_PH11MFP_Pos         (12)                                              /*!< SYS_T::GPH_MFPH: PH11MFP Position      */
#define SYS_GPH_MFPH_PH11MFP_Msk         (0xful << SYS_GPH_MFPH_PH11MFP_Pos)               /*!< SYS_T::GPH_MFPH: PH11MFP Mask          */

#define SYS_GPH_MFPH_PH12MFP_Pos         (16)                                              /*!< SYS_T::GPH_MFPH: PH12MFP Position      */
#define SYS_GPH_MFPH_PH12MFP_Msk         (0xful << SYS_GPH_MFPH_PH12MFP_Pos)               /*!< SYS_T::GPH_MFPH: PH12MFP Mask          */

#define SYS_GPH_MFPH_PH13MFP_Pos         (20)                                              /*!< SYS_T::GPH_MFPH: PH13MFP Position      */
#define SYS_GPH_MFPH_PH13MFP_Msk         (0xful << SYS_GPH_MFPH_PH13MFP_Pos)               /*!< SYS_T::GPH_MFPH: PH13MFP Mask          */

#define SYS_GPH_MFPH_PH14MFP_Pos         (24)                                              /*!< SYS_T::GPH_MFPH: PH14MFP Position      */
#define SYS_GPH_MFPH_PH14MFP_Msk         (0xful << SYS_GPH_MFPH_PH14MFP_Pos)               /*!< SYS_T::GPH_MFPH: PH14MFP Mask          */

#define SYS_GPH_MFPH_PH15MFP_Pos         (28)                                              /*!< SYS_T::GPH_MFPH: PH15MFP Position      */
#define SYS_GPH_MFPH_PH15MFP_Msk         (0xful << SYS_GPH_MFPH_PH15MFP_Pos)               /*!< SYS_T::GPH_MFPH: PH15MFP Mask          */

#define SYS_GPA_MFOS_MFOS0_Pos           (0)                                               /*!< SYS_T::GPA_MFOS: MFOS0 Position        */
#define SYS_GPA_MFOS_MFOS0_Msk           (0x1ul << SYS_GPA_MFOS_MFOS0_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS0 Mask            */

#define SYS_GPA_MFOS_MFOS1_Pos           (1)                                               /*!< SYS_T::GPA_MFOS: MFOS1 Position        */
#define SYS_GPA_MFOS_MFOS1_Msk           (0x1ul << SYS_GPA_MFOS_MFOS1_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS1 Mask            */

#define SYS_GPA_MFOS_MFOS2_Pos           (2)                                               /*!< SYS_T::GPA_MFOS: MFOS2 Position        */
#define SYS_GPA_MFOS_MFOS2_Msk           (0x1ul << SYS_GPA_MFOS_MFOS2_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS2 Mask            */

#define SYS_GPA_MFOS_MFOS3_Pos           (3)                                               /*!< SYS_T::GPA_MFOS: MFOS3 Position        */
#define SYS_GPA_MFOS_MFOS3_Msk           (0x1ul << SYS_GPA_MFOS_MFOS3_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS3 Mask            */

#define SYS_GPA_MFOS_MFOS4_Pos           (4)                                               /*!< SYS_T::GPA_MFOS: MFOS4 Position        */
#define SYS_GPA_MFOS_MFOS4_Msk           (0x1ul << SYS_GPA_MFOS_MFOS4_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS4 Mask            */

#define SYS_GPA_MFOS_MFOS5_Pos           (5)                                               /*!< SYS_T::GPA_MFOS: MFOS5 Position        */
#define SYS_GPA_MFOS_MFOS5_Msk           (0x1ul << SYS_GPA_MFOS_MFOS5_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS5 Mask            */

#define SYS_GPA_MFOS_MFOS6_Pos           (6)                                               /*!< SYS_T::GPA_MFOS: MFOS6 Position        */
#define SYS_GPA_MFOS_MFOS6_Msk           (0x1ul << SYS_GPA_MFOS_MFOS6_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS6 Mask            */

#define SYS_GPA_MFOS_MFOS7_Pos           (7)                                               /*!< SYS_T::GPA_MFOS: MFOS7 Position        */
#define SYS_GPA_MFOS_MFOS7_Msk           (0x1ul << SYS_GPA_MFOS_MFOS7_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS7 Mask            */

#define SYS_GPA_MFOS_MFOS8_Pos           (8)                                               /*!< SYS_T::GPA_MFOS: MFOS8 Position        */
#define SYS_GPA_MFOS_MFOS8_Msk           (0x1ul << SYS_GPA_MFOS_MFOS8_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS8 Mask            */

#define SYS_GPA_MFOS_MFOS9_Pos           (9)                                               /*!< SYS_T::GPA_MFOS: MFOS9 Position        */
#define SYS_GPA_MFOS_MFOS9_Msk           (0x1ul << SYS_GPA_MFOS_MFOS9_Pos)                 /*!< SYS_T::GPA_MFOS: MFOS9 Mask            */

#define SYS_GPA_MFOS_MFOS10_Pos          (10)                                              /*!< SYS_T::GPA_MFOS: MFOS10 Position       */
#define SYS_GPA_MFOS_MFOS10_Msk          (0x1ul << SYS_GPA_MFOS_MFOS10_Pos)                /*!< SYS_T::GPA_MFOS: MFOS10 Mask           */

#define SYS_GPA_MFOS_MFOS11_Pos          (11)                                              /*!< SYS_T::GPA_MFOS: MFOS11 Position       */
#define SYS_GPA_MFOS_MFOS11_Msk          (0x1ul << SYS_GPA_MFOS_MFOS11_Pos)                /*!< SYS_T::GPA_MFOS: MFOS11 Mask           */

#define SYS_GPA_MFOS_MFOS12_Pos          (12)                                              /*!< SYS_T::GPA_MFOS: MFOS12 Position       */
#define SYS_GPA_MFOS_MFOS12_Msk          (0x1ul << SYS_GPA_MFOS_MFOS12_Pos)                /*!< SYS_T::GPA_MFOS: MFOS12 Mask           */

#define SYS_GPA_MFOS_MFOS13_Pos          (13)                                              /*!< SYS_T::GPA_MFOS: MFOS13 Position       */
#define SYS_GPA_MFOS_MFOS13_Msk          (0x1ul << SYS_GPA_MFOS_MFOS13_Pos)                /*!< SYS_T::GPA_MFOS: MFOS13 Mask           */

#define SYS_GPA_MFOS_MFOS14_Pos          (14)                                              /*!< SYS_T::GPA_MFOS: MFOS14 Position       */
#define SYS_GPA_MFOS_MFOS14_Msk          (0x1ul << SYS_GPA_MFOS_MFOS14_Pos)                /*!< SYS_T::GPA_MFOS: MFOS14 Mask           */

#define SYS_GPA_MFOS_MFOS15_Pos          (15)                                              /*!< SYS_T::GPA_MFOS: MFOS15 Position       */
#define SYS_GPA_MFOS_MFOS15_Msk          (0x1ul << SYS_GPA_MFOS_MFOS15_Pos)                /*!< SYS_T::GPA_MFOS: MFOS15 Mask           */

#define SYS_GPB_MFOS_MFOS0_Pos           (0)                                               /*!< SYS_T::GPB_MFOS: MFOS0 Position        */
#define SYS_GPB_MFOS_MFOS0_Msk           (0x1ul << SYS_GPB_MFOS_MFOS0_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS0 Mask            */

#define SYS_GPB_MFOS_MFOS1_Pos           (1)                                               /*!< SYS_T::GPB_MFOS: MFOS1 Position        */
#define SYS_GPB_MFOS_MFOS1_Msk           (0x1ul << SYS_GPB_MFOS_MFOS1_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS1 Mask            */

#define SYS_GPB_MFOS_MFOS2_Pos           (2)                                               /*!< SYS_T::GPB_MFOS: MFOS2 Position        */
#define SYS_GPB_MFOS_MFOS2_Msk           (0x1ul << SYS_GPB_MFOS_MFOS2_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS2 Mask            */

#define SYS_GPB_MFOS_MFOS3_Pos           (3)                                               /*!< SYS_T::GPB_MFOS: MFOS3 Position        */
#define SYS_GPB_MFOS_MFOS3_Msk           (0x1ul << SYS_GPB_MFOS_MFOS3_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS3 Mask            */

#define SYS_GPB_MFOS_MFOS4_Pos           (4)                                               /*!< SYS_T::GPB_MFOS: MFOS4 Position        */
#define SYS_GPB_MFOS_MFOS4_Msk           (0x1ul << SYS_GPB_MFOS_MFOS4_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS4 Mask            */

#define SYS_GPB_MFOS_MFOS5_Pos           (5)                                               /*!< SYS_T::GPB_MFOS: MFOS5 Position        */
#define SYS_GPB_MFOS_MFOS5_Msk           (0x1ul << SYS_GPB_MFOS_MFOS5_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS5 Mask            */

#define SYS_GPB_MFOS_MFOS6_Pos           (6)                                               /*!< SYS_T::GPB_MFOS: MFOS6 Position        */
#define SYS_GPB_MFOS_MFOS6_Msk           (0x1ul << SYS_GPB_MFOS_MFOS6_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS6 Mask            */

#define SYS_GPB_MFOS_MFOS7_Pos           (7)                                               /*!< SYS_T::GPB_MFOS: MFOS7 Position        */
#define SYS_GPB_MFOS_MFOS7_Msk           (0x1ul << SYS_GPB_MFOS_MFOS7_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS7 Mask            */

#define SYS_GPB_MFOS_MFOS8_Pos           (8)                                               /*!< SYS_T::GPB_MFOS: MFOS8 Position        */
#define SYS_GPB_MFOS_MFOS8_Msk           (0x1ul << SYS_GPB_MFOS_MFOS8_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS8 Mask            */

#define SYS_GPB_MFOS_MFOS9_Pos           (9)                                               /*!< SYS_T::GPB_MFOS: MFOS9 Position        */
#define SYS_GPB_MFOS_MFOS9_Msk           (0x1ul << SYS_GPB_MFOS_MFOS9_Pos)                 /*!< SYS_T::GPB_MFOS: MFOS9 Mask            */

#define SYS_GPB_MFOS_MFOS10_Pos          (10)                                              /*!< SYS_T::GPB_MFOS: MFOS10 Position       */
#define SYS_GPB_MFOS_MFOS10_Msk          (0x1ul << SYS_GPB_MFOS_MFOS10_Pos)                /*!< SYS_T::GPB_MFOS: MFOS10 Mask           */

#define SYS_GPB_MFOS_MFOS11_Pos          (11)                                              /*!< SYS_T::GPB_MFOS: MFOS11 Position       */
#define SYS_GPB_MFOS_MFOS11_Msk          (0x1ul << SYS_GPB_MFOS_MFOS11_Pos)                /*!< SYS_T::GPB_MFOS: MFOS11 Mask           */

#define SYS_GPB_MFOS_MFOS12_Pos          (12)                                              /*!< SYS_T::GPB_MFOS: MFOS12 Position       */
#define SYS_GPB_MFOS_MFOS12_Msk          (0x1ul << SYS_GPB_MFOS_MFOS12_Pos)                /*!< SYS_T::GPB_MFOS: MFOS12 Mask           */

#define SYS_GPB_MFOS_MFOS13_Pos          (13)                                              /*!< SYS_T::GPB_MFOS: MFOS13 Position       */
#define SYS_GPB_MFOS_MFOS13_Msk          (0x1ul << SYS_GPB_MFOS_MFOS13_Pos)                /*!< SYS_T::GPB_MFOS: MFOS13 Mask           */

#define SYS_GPB_MFOS_MFOS14_Pos          (14)                                              /*!< SYS_T::GPB_MFOS: MFOS14 Position       */
#define SYS_GPB_MFOS_MFOS14_Msk          (0x1ul << SYS_GPB_MFOS_MFOS14_Pos)                /*!< SYS_T::GPB_MFOS: MFOS14 Mask           */

#define SYS_GPB_MFOS_MFOS15_Pos          (15)                                              /*!< SYS_T::GPB_MFOS: MFOS15 Position       */
#define SYS_GPB_MFOS_MFOS15_Msk          (0x1ul << SYS_GPB_MFOS_MFOS15_Pos)                /*!< SYS_T::GPB_MFOS: MFOS15 Mask           */

#define SYS_GPC_MFOS_MFOS0_Pos           (0)                                               /*!< SYS_T::GPC_MFOS: MFOS0 Position        */
#define SYS_GPC_MFOS_MFOS0_Msk           (0x1ul << SYS_GPC_MFOS_MFOS0_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS0 Mask            */

#define SYS_GPC_MFOS_MFOS1_Pos           (1)                                               /*!< SYS_T::GPC_MFOS: MFOS1 Position        */
#define SYS_GPC_MFOS_MFOS1_Msk           (0x1ul << SYS_GPC_MFOS_MFOS1_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS1 Mask            */

#define SYS_GPC_MFOS_MFOS2_Pos           (2)                                               /*!< SYS_T::GPC_MFOS: MFOS2 Position        */
#define SYS_GPC_MFOS_MFOS2_Msk           (0x1ul << SYS_GPC_MFOS_MFOS2_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS2 Mask            */

#define SYS_GPC_MFOS_MFOS3_Pos           (3)                                               /*!< SYS_T::GPC_MFOS: MFOS3 Position        */
#define SYS_GPC_MFOS_MFOS3_Msk           (0x1ul << SYS_GPC_MFOS_MFOS3_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS3 Mask            */

#define SYS_GPC_MFOS_MFOS4_Pos           (4)                                               /*!< SYS_T::GPC_MFOS: MFOS4 Position        */
#define SYS_GPC_MFOS_MFOS4_Msk           (0x1ul << SYS_GPC_MFOS_MFOS4_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS4 Mask            */

#define SYS_GPC_MFOS_MFOS5_Pos           (5)                                               /*!< SYS_T::GPC_MFOS: MFOS5 Position        */
#define SYS_GPC_MFOS_MFOS5_Msk           (0x1ul << SYS_GPC_MFOS_MFOS5_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS5 Mask            */

#define SYS_GPC_MFOS_MFOS6_Pos           (6)                                               /*!< SYS_T::GPC_MFOS: MFOS6 Position        */
#define SYS_GPC_MFOS_MFOS6_Msk           (0x1ul << SYS_GPC_MFOS_MFOS6_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS6 Mask            */

#define SYS_GPC_MFOS_MFOS7_Pos           (7)                                               /*!< SYS_T::GPC_MFOS: MFOS7 Position        */
#define SYS_GPC_MFOS_MFOS7_Msk           (0x1ul << SYS_GPC_MFOS_MFOS7_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS7 Mask            */

#define SYS_GPC_MFOS_MFOS8_Pos           (8)                                               /*!< SYS_T::GPC_MFOS: MFOS8 Position        */
#define SYS_GPC_MFOS_MFOS8_Msk           (0x1ul << SYS_GPC_MFOS_MFOS8_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS8 Mask            */

#define SYS_GPC_MFOS_MFOS9_Pos           (9)                                               /*!< SYS_T::GPC_MFOS: MFOS9 Position        */
#define SYS_GPC_MFOS_MFOS9_Msk           (0x1ul << SYS_GPC_MFOS_MFOS9_Pos)                 /*!< SYS_T::GPC_MFOS: MFOS9 Mask            */

#define SYS_GPC_MFOS_MFOS10_Pos          (10)                                              /*!< SYS_T::GPC_MFOS: MFOS10 Position       */
#define SYS_GPC_MFOS_MFOS10_Msk          (0x1ul << SYS_GPC_MFOS_MFOS10_Pos)                /*!< SYS_T::GPC_MFOS: MFOS10 Mask           */

#define SYS_GPC_MFOS_MFOS11_Pos          (11)                                              /*!< SYS_T::GPC_MFOS: MFOS11 Position       */
#define SYS_GPC_MFOS_MFOS11_Msk          (0x1ul << SYS_GPC_MFOS_MFOS11_Pos)                /*!< SYS_T::GPC_MFOS: MFOS11 Mask           */

#define SYS_GPC_MFOS_MFOS12_Pos          (12)                                              /*!< SYS_T::GPC_MFOS: MFOS12 Position       */
#define SYS_GPC_MFOS_MFOS12_Msk          (0x1ul << SYS_GPC_MFOS_MFOS12_Pos)                /*!< SYS_T::GPC_MFOS: MFOS12 Mask           */

#define SYS_GPC_MFOS_MFOS13_Pos          (13)                                              /*!< SYS_T::GPC_MFOS: MFOS13 Position       */
#define SYS_GPC_MFOS_MFOS13_Msk          (0x1ul << SYS_GPC_MFOS_MFOS13_Pos)                /*!< SYS_T::GPC_MFOS: MFOS13 Mask           */

#define SYS_GPC_MFOS_MFOS14_Pos          (14)                                              /*!< SYS_T::GPC_MFOS: MFOS14 Position       */
#define SYS_GPC_MFOS_MFOS14_Msk          (0x1ul << SYS_GPC_MFOS_MFOS14_Pos)                /*!< SYS_T::GPC_MFOS: MFOS14 Mask           */

#define SYS_GPC_MFOS_MFOS15_Pos          (15)                                              /*!< SYS_T::GPC_MFOS: MFOS15 Position       */
#define SYS_GPC_MFOS_MFOS15_Msk          (0x1ul << SYS_GPC_MFOS_MFOS15_Pos)                /*!< SYS_T::GPC_MFOS: MFOS15 Mask           */

#define SYS_GPD_MFOS_MFOS0_Pos           (0)                                               /*!< SYS_T::GPD_MFOS: MFOS0 Position        */
#define SYS_GPD_MFOS_MFOS0_Msk           (0x1ul << SYS_GPD_MFOS_MFOS0_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS0 Mask            */

#define SYS_GPD_MFOS_MFOS1_Pos           (1)                                               /*!< SYS_T::GPD_MFOS: MFOS1 Position        */
#define SYS_GPD_MFOS_MFOS1_Msk           (0x1ul << SYS_GPD_MFOS_MFOS1_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS1 Mask            */

#define SYS_GPD_MFOS_MFOS2_Pos           (2)                                               /*!< SYS_T::GPD_MFOS: MFOS2 Position        */
#define SYS_GPD_MFOS_MFOS2_Msk           (0x1ul << SYS_GPD_MFOS_MFOS2_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS2 Mask            */

#define SYS_GPD_MFOS_MFOS3_Pos           (3)                                               /*!< SYS_T::GPD_MFOS: MFOS3 Position        */
#define SYS_GPD_MFOS_MFOS3_Msk           (0x1ul << SYS_GPD_MFOS_MFOS3_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS3 Mask            */

#define SYS_GPD_MFOS_MFOS4_Pos           (4)                                               /*!< SYS_T::GPD_MFOS: MFOS4 Position        */
#define SYS_GPD_MFOS_MFOS4_Msk           (0x1ul << SYS_GPD_MFOS_MFOS4_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS4 Mask            */

#define SYS_GPD_MFOS_MFOS5_Pos           (5)                                               /*!< SYS_T::GPD_MFOS: MFOS5 Position        */
#define SYS_GPD_MFOS_MFOS5_Msk           (0x1ul << SYS_GPD_MFOS_MFOS5_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS5 Mask            */

#define SYS_GPD_MFOS_MFOS6_Pos           (6)                                               /*!< SYS_T::GPD_MFOS: MFOS6 Position        */
#define SYS_GPD_MFOS_MFOS6_Msk           (0x1ul << SYS_GPD_MFOS_MFOS6_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS6 Mask            */

#define SYS_GPD_MFOS_MFOS7_Pos           (7)                                               /*!< SYS_T::GPD_MFOS: MFOS7 Position        */
#define SYS_GPD_MFOS_MFOS7_Msk           (0x1ul << SYS_GPD_MFOS_MFOS7_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS7 Mask            */

#define SYS_GPD_MFOS_MFOS8_Pos           (8)                                               /*!< SYS_T::GPD_MFOS: MFOS8 Position        */
#define SYS_GPD_MFOS_MFOS8_Msk           (0x1ul << SYS_GPD_MFOS_MFOS8_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS8 Mask            */

#define SYS_GPD_MFOS_MFOS9_Pos           (9)                                               /*!< SYS_T::GPD_MFOS: MFOS9 Position        */
#define SYS_GPD_MFOS_MFOS9_Msk           (0x1ul << SYS_GPD_MFOS_MFOS9_Pos)                 /*!< SYS_T::GPD_MFOS: MFOS9 Mask            */

#define SYS_GPD_MFOS_MFOS10_Pos          (10)                                              /*!< SYS_T::GPD_MFOS: MFOS10 Position       */
#define SYS_GPD_MFOS_MFOS10_Msk          (0x1ul << SYS_GPD_MFOS_MFOS10_Pos)                /*!< SYS_T::GPD_MFOS: MFOS10 Mask           */

#define SYS_GPD_MFOS_MFOS11_Pos          (11)                                              /*!< SYS_T::GPD_MFOS: MFOS11 Position       */
#define SYS_GPD_MFOS_MFOS11_Msk          (0x1ul << SYS_GPD_MFOS_MFOS11_Pos)                /*!< SYS_T::GPD_MFOS: MFOS11 Mask           */

#define SYS_GPD_MFOS_MFOS12_Pos          (12)                                              /*!< SYS_T::GPD_MFOS: MFOS12 Position       */
#define SYS_GPD_MFOS_MFOS12_Msk          (0x1ul << SYS_GPD_MFOS_MFOS12_Pos)                /*!< SYS_T::GPD_MFOS: MFOS12 Mask           */

#define SYS_GPD_MFOS_MFOS13_Pos          (13)                                              /*!< SYS_T::GPD_MFOS: MFOS13 Position       */
#define SYS_GPD_MFOS_MFOS13_Msk          (0x1ul << SYS_GPD_MFOS_MFOS13_Pos)                /*!< SYS_T::GPD_MFOS: MFOS13 Mask           */

#define SYS_GPD_MFOS_MFOS14_Pos          (14)                                              /*!< SYS_T::GPD_MFOS: MFOS14 Position       */
#define SYS_GPD_MFOS_MFOS14_Msk          (0x1ul << SYS_GPD_MFOS_MFOS14_Pos)                /*!< SYS_T::GPD_MFOS: MFOS14 Mask           */

#define SYS_GPD_MFOS_MFOS15_Pos          (15)                                              /*!< SYS_T::GPD_MFOS: MFOS15 Position       */
#define SYS_GPD_MFOS_MFOS15_Msk          (0x1ul << SYS_GPD_MFOS_MFOS15_Pos)                /*!< SYS_T::GPD_MFOS: MFOS15 Mask           */

#define SYS_GPE_MFOS_MFOS0_Pos           (0)                                               /*!< SYS_T::GPE_MFOS: MFOS0 Position        */
#define SYS_GPE_MFOS_MFOS0_Msk           (0x1ul << SYS_GPE_MFOS_MFOS0_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS0 Mask            */

#define SYS_GPE_MFOS_MFOS1_Pos           (1)                                               /*!< SYS_T::GPE_MFOS: MFOS1 Position        */
#define SYS_GPE_MFOS_MFOS1_Msk           (0x1ul << SYS_GPE_MFOS_MFOS1_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS1 Mask            */

#define SYS_GPE_MFOS_MFOS2_Pos           (2)                                               /*!< SYS_T::GPE_MFOS: MFOS2 Position        */
#define SYS_GPE_MFOS_MFOS2_Msk           (0x1ul << SYS_GPE_MFOS_MFOS2_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS2 Mask            */

#define SYS_GPE_MFOS_MFOS3_Pos           (3)                                               /*!< SYS_T::GPE_MFOS: MFOS3 Position        */
#define SYS_GPE_MFOS_MFOS3_Msk           (0x1ul << SYS_GPE_MFOS_MFOS3_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS3 Mask            */

#define SYS_GPE_MFOS_MFOS4_Pos           (4)                                               /*!< SYS_T::GPE_MFOS: MFOS4 Position        */
#define SYS_GPE_MFOS_MFOS4_Msk           (0x1ul << SYS_GPE_MFOS_MFOS4_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS4 Mask            */

#define SYS_GPE_MFOS_MFOS5_Pos           (5)                                               /*!< SYS_T::GPE_MFOS: MFOS5 Position        */
#define SYS_GPE_MFOS_MFOS5_Msk           (0x1ul << SYS_GPE_MFOS_MFOS5_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS5 Mask            */

#define SYS_GPE_MFOS_MFOS6_Pos           (6)                                               /*!< SYS_T::GPE_MFOS: MFOS6 Position        */
#define SYS_GPE_MFOS_MFOS6_Msk           (0x1ul << SYS_GPE_MFOS_MFOS6_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS6 Mask            */

#define SYS_GPE_MFOS_MFOS7_Pos           (7)                                               /*!< SYS_T::GPE_MFOS: MFOS7 Position        */
#define SYS_GPE_MFOS_MFOS7_Msk           (0x1ul << SYS_GPE_MFOS_MFOS7_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS7 Mask            */

#define SYS_GPE_MFOS_MFOS8_Pos           (8)                                               /*!< SYS_T::GPE_MFOS: MFOS8 Position        */
#define SYS_GPE_MFOS_MFOS8_Msk           (0x1ul << SYS_GPE_MFOS_MFOS8_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS8 Mask            */

#define SYS_GPE_MFOS_MFOS9_Pos           (9)                                               /*!< SYS_T::GPE_MFOS: MFOS9 Position        */
#define SYS_GPE_MFOS_MFOS9_Msk           (0x1ul << SYS_GPE_MFOS_MFOS9_Pos)                 /*!< SYS_T::GPE_MFOS: MFOS9 Mask            */

#define SYS_GPE_MFOS_MFOS10_Pos          (10)                                              /*!< SYS_T::GPE_MFOS: MFOS10 Position       */
#define SYS_GPE_MFOS_MFOS10_Msk          (0x1ul << SYS_GPE_MFOS_MFOS10_Pos)                /*!< SYS_T::GPE_MFOS: MFOS10 Mask           */

#define SYS_GPE_MFOS_MFOS11_Pos          (11)                                              /*!< SYS_T::GPE_MFOS: MFOS11 Position       */
#define SYS_GPE_MFOS_MFOS11_Msk          (0x1ul << SYS_GPE_MFOS_MFOS11_Pos)                /*!< SYS_T::GPE_MFOS: MFOS11 Mask           */

#define SYS_GPE_MFOS_MFOS12_Pos          (12)                                              /*!< SYS_T::GPE_MFOS: MFOS12 Position       */
#define SYS_GPE_MFOS_MFOS12_Msk          (0x1ul << SYS_GPE_MFOS_MFOS12_Pos)                /*!< SYS_T::GPE_MFOS: MFOS12 Mask           */

#define SYS_GPE_MFOS_MFOS13_Pos          (13)                                              /*!< SYS_T::GPE_MFOS: MFOS13 Position       */
#define SYS_GPE_MFOS_MFOS13_Msk          (0x1ul << SYS_GPE_MFOS_MFOS13_Pos)                /*!< SYS_T::GPE_MFOS: MFOS13 Mask           */

#define SYS_GPE_MFOS_MFOS14_Pos          (14)                                              /*!< SYS_T::GPE_MFOS: MFOS14 Position       */
#define SYS_GPE_MFOS_MFOS14_Msk          (0x1ul << SYS_GPE_MFOS_MFOS14_Pos)                /*!< SYS_T::GPE_MFOS: MFOS14 Mask           */

#define SYS_GPE_MFOS_MFOS15_Pos          (15)                                              /*!< SYS_T::GPE_MFOS: MFOS15 Position       */
#define SYS_GPE_MFOS_MFOS15_Msk          (0x1ul << SYS_GPE_MFOS_MFOS15_Pos)                /*!< SYS_T::GPE_MFOS: MFOS15 Mask           */

#define SYS_GPF_MFOS_MFOS0_Pos           (0)                                               /*!< SYS_T::GPF_MFOS: MFOS0 Position        */
#define SYS_GPF_MFOS_MFOS0_Msk           (0x1ul << SYS_GPF_MFOS_MFOS0_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS0 Mask            */

#define SYS_GPF_MFOS_MFOS1_Pos           (1)                                               /*!< SYS_T::GPF_MFOS: MFOS1 Position        */
#define SYS_GPF_MFOS_MFOS1_Msk           (0x1ul << SYS_GPF_MFOS_MFOS1_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS1 Mask            */

#define SYS_GPF_MFOS_MFOS2_Pos           (2)                                               /*!< SYS_T::GPF_MFOS: MFOS2 Position        */
#define SYS_GPF_MFOS_MFOS2_Msk           (0x1ul << SYS_GPF_MFOS_MFOS2_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS2 Mask            */

#define SYS_GPF_MFOS_MFOS3_Pos           (3)                                               /*!< SYS_T::GPF_MFOS: MFOS3 Position        */
#define SYS_GPF_MFOS_MFOS3_Msk           (0x1ul << SYS_GPF_MFOS_MFOS3_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS3 Mask            */

#define SYS_GPF_MFOS_MFOS4_Pos           (4)                                               /*!< SYS_T::GPF_MFOS: MFOS4 Position        */
#define SYS_GPF_MFOS_MFOS4_Msk           (0x1ul << SYS_GPF_MFOS_MFOS4_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS4 Mask            */

#define SYS_GPF_MFOS_MFOS5_Pos           (5)                                               /*!< SYS_T::GPF_MFOS: MFOS5 Position        */
#define SYS_GPF_MFOS_MFOS5_Msk           (0x1ul << SYS_GPF_MFOS_MFOS5_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS5 Mask            */

#define SYS_GPF_MFOS_MFOS6_Pos           (6)                                               /*!< SYS_T::GPF_MFOS: MFOS6 Position        */
#define SYS_GPF_MFOS_MFOS6_Msk           (0x1ul << SYS_GPF_MFOS_MFOS6_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS6 Mask            */

#define SYS_GPF_MFOS_MFOS7_Pos           (7)                                               /*!< SYS_T::GPF_MFOS: MFOS7 Position        */
#define SYS_GPF_MFOS_MFOS7_Msk           (0x1ul << SYS_GPF_MFOS_MFOS7_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS7 Mask            */

#define SYS_GPF_MFOS_MFOS8_Pos           (8)                                               /*!< SYS_T::GPF_MFOS: MFOS8 Position        */
#define SYS_GPF_MFOS_MFOS8_Msk           (0x1ul << SYS_GPF_MFOS_MFOS8_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS8 Mask            */

#define SYS_GPF_MFOS_MFOS9_Pos           (9)                                               /*!< SYS_T::GPF_MFOS: MFOS9 Position        */
#define SYS_GPF_MFOS_MFOS9_Msk           (0x1ul << SYS_GPF_MFOS_MFOS9_Pos)                 /*!< SYS_T::GPF_MFOS: MFOS9 Mask            */

#define SYS_GPF_MFOS_MFOS10_Pos          (10)                                              /*!< SYS_T::GPF_MFOS: MFOS10 Position       */
#define SYS_GPF_MFOS_MFOS10_Msk          (0x1ul << SYS_GPF_MFOS_MFOS10_Pos)                /*!< SYS_T::GPF_MFOS: MFOS10 Mask           */

#define SYS_GPF_MFOS_MFOS11_Pos          (11)                                              /*!< SYS_T::GPF_MFOS: MFOS11 Position       */
#define SYS_GPF_MFOS_MFOS11_Msk          (0x1ul << SYS_GPF_MFOS_MFOS11_Pos)                /*!< SYS_T::GPF_MFOS: MFOS11 Mask           */

#define SYS_GPF_MFOS_MFOS12_Pos          (12)                                              /*!< SYS_T::GPF_MFOS: MFOS12 Position       */
#define SYS_GPF_MFOS_MFOS12_Msk          (0x1ul << SYS_GPF_MFOS_MFOS12_Pos)                /*!< SYS_T::GPF_MFOS: MFOS12 Mask           */

#define SYS_GPF_MFOS_MFOS13_Pos          (13)                                              /*!< SYS_T::GPF_MFOS: MFOS13 Position       */
#define SYS_GPF_MFOS_MFOS13_Msk          (0x1ul << SYS_GPF_MFOS_MFOS13_Pos)                /*!< SYS_T::GPF_MFOS: MFOS13 Mask           */

#define SYS_GPF_MFOS_MFOS14_Pos          (14)                                              /*!< SYS_T::GPF_MFOS: MFOS14 Position       */
#define SYS_GPF_MFOS_MFOS14_Msk          (0x1ul << SYS_GPF_MFOS_MFOS14_Pos)                /*!< SYS_T::GPF_MFOS: MFOS14 Mask           */

#define SYS_GPF_MFOS_MFOS15_Pos          (15)                                              /*!< SYS_T::GPF_MFOS: MFOS15 Position       */
#define SYS_GPF_MFOS_MFOS15_Msk          (0x1ul << SYS_GPF_MFOS_MFOS15_Pos)                /*!< SYS_T::GPF_MFOS: MFOS15 Mask           */

#define SYS_GPG_MFOS_MFOS0_Pos           (0)                                               /*!< SYS_T::GPG_MFOS: MFOS0 Position        */
#define SYS_GPG_MFOS_MFOS0_Msk           (0x1ul << SYS_GPG_MFOS_MFOS0_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS0 Mask            */

#define SYS_GPG_MFOS_MFOS1_Pos           (1)                                               /*!< SYS_T::GPG_MFOS: MFOS1 Position        */
#define SYS_GPG_MFOS_MFOS1_Msk           (0x1ul << SYS_GPG_MFOS_MFOS1_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS1 Mask            */

#define SYS_GPG_MFOS_MFOS2_Pos           (2)                                               /*!< SYS_T::GPG_MFOS: MFOS2 Position        */
#define SYS_GPG_MFOS_MFOS2_Msk           (0x1ul << SYS_GPG_MFOS_MFOS2_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS2 Mask            */

#define SYS_GPG_MFOS_MFOS3_Pos           (3)                                               /*!< SYS_T::GPG_MFOS: MFOS3 Position        */
#define SYS_GPG_MFOS_MFOS3_Msk           (0x1ul << SYS_GPG_MFOS_MFOS3_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS3 Mask            */

#define SYS_GPG_MFOS_MFOS4_Pos           (4)                                               /*!< SYS_T::GPG_MFOS: MFOS4 Position        */
#define SYS_GPG_MFOS_MFOS4_Msk           (0x1ul << SYS_GPG_MFOS_MFOS4_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS4 Mask            */

#define SYS_GPG_MFOS_MFOS5_Pos           (5)                                               /*!< SYS_T::GPG_MFOS: MFOS5 Position        */
#define SYS_GPG_MFOS_MFOS5_Msk           (0x1ul << SYS_GPG_MFOS_MFOS5_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS5 Mask            */

#define SYS_GPG_MFOS_MFOS6_Pos           (6)                                               /*!< SYS_T::GPG_MFOS: MFOS6 Position        */
#define SYS_GPG_MFOS_MFOS6_Msk           (0x1ul << SYS_GPG_MFOS_MFOS6_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS6 Mask            */

#define SYS_GPG_MFOS_MFOS7_Pos           (7)                                               /*!< SYS_T::GPG_MFOS: MFOS7 Position        */
#define SYS_GPG_MFOS_MFOS7_Msk           (0x1ul << SYS_GPG_MFOS_MFOS7_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS7 Mask            */

#define SYS_GPG_MFOS_MFOS8_Pos           (8)                                               /*!< SYS_T::GPG_MFOS: MFOS8 Position        */
#define SYS_GPG_MFOS_MFOS8_Msk           (0x1ul << SYS_GPG_MFOS_MFOS8_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS8 Mask            */

#define SYS_GPG_MFOS_MFOS9_Pos           (9)                                               /*!< SYS_T::GPG_MFOS: MFOS9 Position        */
#define SYS_GPG_MFOS_MFOS9_Msk           (0x1ul << SYS_GPG_MFOS_MFOS9_Pos)                 /*!< SYS_T::GPG_MFOS: MFOS9 Mask            */

#define SYS_GPG_MFOS_MFOS10_Pos          (10)                                              /*!< SYS_T::GPG_MFOS: MFOS10 Position       */
#define SYS_GPG_MFOS_MFOS10_Msk          (0x1ul << SYS_GPG_MFOS_MFOS10_Pos)                /*!< SYS_T::GPG_MFOS: MFOS10 Mask           */

#define SYS_GPG_MFOS_MFOS11_Pos          (11)                                              /*!< SYS_T::GPG_MFOS: MFOS11 Position       */
#define SYS_GPG_MFOS_MFOS11_Msk          (0x1ul << SYS_GPG_MFOS_MFOS11_Pos)                /*!< SYS_T::GPG_MFOS: MFOS11 Mask           */

#define SYS_GPG_MFOS_MFOS12_Pos          (12)                                              /*!< SYS_T::GPG_MFOS: MFOS12 Position       */
#define SYS_GPG_MFOS_MFOS12_Msk          (0x1ul << SYS_GPG_MFOS_MFOS12_Pos)                /*!< SYS_T::GPG_MFOS: MFOS12 Mask           */

#define SYS_GPG_MFOS_MFOS13_Pos          (13)                                              /*!< SYS_T::GPG_MFOS: MFOS13 Position       */
#define SYS_GPG_MFOS_MFOS13_Msk          (0x1ul << SYS_GPG_MFOS_MFOS13_Pos)                /*!< SYS_T::GPG_MFOS: MFOS13 Mask           */

#define SYS_GPG_MFOS_MFOS14_Pos          (14)                                              /*!< SYS_T::GPG_MFOS: MFOS14 Position       */
#define SYS_GPG_MFOS_MFOS14_Msk          (0x1ul << SYS_GPG_MFOS_MFOS14_Pos)                /*!< SYS_T::GPG_MFOS: MFOS14 Mask           */

#define SYS_GPG_MFOS_MFOS15_Pos          (15)                                              /*!< SYS_T::GPG_MFOS: MFOS15 Position       */
#define SYS_GPG_MFOS_MFOS15_Msk          (0x1ul << SYS_GPG_MFOS_MFOS15_Pos)                /*!< SYS_T::GPG_MFOS: MFOS15 Mask           */

#define SYS_GPH_MFOS_MFOS0_Pos           (0)                                               /*!< SYS_T::GPH_MFOS: MFOS0 Position        */
#define SYS_GPH_MFOS_MFOS0_Msk           (0x1ul << SYS_GPH_MFOS_MFOS0_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS0 Mask            */

#define SYS_GPH_MFOS_MFOS1_Pos           (1)                                               /*!< SYS_T::GPH_MFOS: MFOS1 Position        */
#define SYS_GPH_MFOS_MFOS1_Msk           (0x1ul << SYS_GPH_MFOS_MFOS1_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS1 Mask            */

#define SYS_GPH_MFOS_MFOS2_Pos           (2)                                               /*!< SYS_T::GPH_MFOS: MFOS2 Position        */
#define SYS_GPH_MFOS_MFOS2_Msk           (0x1ul << SYS_GPH_MFOS_MFOS2_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS2 Mask            */

#define SYS_GPH_MFOS_MFOS3_Pos           (3)                                               /*!< SYS_T::GPH_MFOS: MFOS3 Position        */
#define SYS_GPH_MFOS_MFOS3_Msk           (0x1ul << SYS_GPH_MFOS_MFOS3_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS3 Mask            */

#define SYS_GPH_MFOS_MFOS4_Pos           (4)                                               /*!< SYS_T::GPH_MFOS: MFOS4 Position        */
#define SYS_GPH_MFOS_MFOS4_Msk           (0x1ul << SYS_GPH_MFOS_MFOS4_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS4 Mask            */

#define SYS_GPH_MFOS_MFOS5_Pos           (5)                                               /*!< SYS_T::GPH_MFOS: MFOS5 Position        */
#define SYS_GPH_MFOS_MFOS5_Msk           (0x1ul << SYS_GPH_MFOS_MFOS5_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS5 Mask            */

#define SYS_GPH_MFOS_MFOS6_Pos           (6)                                               /*!< SYS_T::GPH_MFOS: MFOS6 Position        */
#define SYS_GPH_MFOS_MFOS6_Msk           (0x1ul << SYS_GPH_MFOS_MFOS6_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS6 Mask            */

#define SYS_GPH_MFOS_MFOS7_Pos           (7)                                               /*!< SYS_T::GPH_MFOS: MFOS7 Position        */
#define SYS_GPH_MFOS_MFOS7_Msk           (0x1ul << SYS_GPH_MFOS_MFOS7_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS7 Mask            */

#define SYS_GPH_MFOS_MFOS8_Pos           (8)                                               /*!< SYS_T::GPH_MFOS: MFOS8 Position        */
#define SYS_GPH_MFOS_MFOS8_Msk           (0x1ul << SYS_GPH_MFOS_MFOS8_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS8 Mask            */

#define SYS_GPH_MFOS_MFOS9_Pos           (9)                                               /*!< SYS_T::GPH_MFOS: MFOS9 Position        */
#define SYS_GPH_MFOS_MFOS9_Msk           (0x1ul << SYS_GPH_MFOS_MFOS9_Pos)                 /*!< SYS_T::GPH_MFOS: MFOS9 Mask            */

#define SYS_GPH_MFOS_MFOS10_Pos          (10)                                              /*!< SYS_T::GPH_MFOS: MFOS10 Position       */
#define SYS_GPH_MFOS_MFOS10_Msk          (0x1ul << SYS_GPH_MFOS_MFOS10_Pos)                /*!< SYS_T::GPH_MFOS: MFOS10 Mask           */

#define SYS_GPH_MFOS_MFOS11_Pos          (11)                                              /*!< SYS_T::GPH_MFOS: MFOS11 Position       */
#define SYS_GPH_MFOS_MFOS11_Msk          (0x1ul << SYS_GPH_MFOS_MFOS11_Pos)                /*!< SYS_T::GPH_MFOS: MFOS11 Mask           */

#define SYS_GPH_MFOS_MFOS12_Pos          (12)                                              /*!< SYS_T::GPH_MFOS: MFOS12 Position       */
#define SYS_GPH_MFOS_MFOS12_Msk          (0x1ul << SYS_GPH_MFOS_MFOS12_Pos)                /*!< SYS_T::GPH_MFOS: MFOS12 Mask           */

#define SYS_GPH_MFOS_MFOS13_Pos          (13)                                              /*!< SYS_T::GPH_MFOS: MFOS13 Position       */
#define SYS_GPH_MFOS_MFOS13_Msk          (0x1ul << SYS_GPH_MFOS_MFOS13_Pos)                /*!< SYS_T::GPH_MFOS: MFOS13 Mask           */

#define SYS_GPH_MFOS_MFOS14_Pos          (14)                                              /*!< SYS_T::GPH_MFOS: MFOS14 Position       */
#define SYS_GPH_MFOS_MFOS14_Msk          (0x1ul << SYS_GPH_MFOS_MFOS14_Pos)                /*!< SYS_T::GPH_MFOS: MFOS14 Mask           */

#define SYS_GPH_MFOS_MFOS15_Pos          (15)                                              /*!< SYS_T::GPH_MFOS: MFOS15 Position       */
#define SYS_GPH_MFOS_MFOS15_Msk          (0x1ul << SYS_GPH_MFOS_MFOS15_Pos)                /*!< SYS_T::GPH_MFOS: MFOS15 Mask           */

#define SYS_SRAM_INTCTL_PERRIEN_Pos      (0)                                               /*!< SYS_T::SRAM_INTCTL: PERRIEN Position   */
#define SYS_SRAM_INTCTL_PERRIEN_Msk      (0x1ul << SYS_SRAM_INTCTL_PERRIEN_Pos)            /*!< SYS_T::SRAM_INTCTL: PERRIEN Mask       */

#define SYS_SRAM_STATUS_PERRIF_Pos       (0)                                               /*!< SYS_T::SRAM_STATUS: PERRIF Position    */
#define SYS_SRAM_STATUS_PERRIF_Msk       (0x1ul << SYS_SRAM_STATUS_PERRIF_Pos)             /*!< SYS_T::SRAM_STATUS: PERRIF Mask        */

#define SYS_SRAM_ERRADDR_ERRADDR_Pos     (0)                                               /*!< SYS_T::SRAM_ERRADDR: ERRADDR Position  */
#define SYS_SRAM_ERRADDR_ERRADDR_Msk     (0xfffffffful << SYS_SRAM_ERRADDR_ERRADDR_Pos)    /*!< SYS_T::SRAM_ERRADDR: ERRADDR Mask      */

#define SYS_SRAM_BISTCTL_SRBIST0_Pos     (0)                                               /*!< SYS_T::SRAM_BISTCTL: SRBIST0 Position  */
#define SYS_SRAM_BISTCTL_SRBIST0_Msk     (0x1ul << SYS_SRAM_BISTCTL_SRBIST0_Pos)           /*!< SYS_T::SRAM_BISTCTL: SRBIST0 Mask      */

#define SYS_SRAM_BISTCTL_SRBIST1_Pos     (1)                                               /*!< SYS_T::SRAM_BISTCTL: SRBIST1 Position  */
#define SYS_SRAM_BISTCTL_SRBIST1_Msk     (0x1ul << SYS_SRAM_BISTCTL_SRBIST1_Pos)           /*!< SYS_T::SRAM_BISTCTL: SRBIST1 Mask      */

#define SYS_SRAM_BISTCTL_CRBIST_Pos      (2)                                               /*!< SYS_T::SRAM_BISTCTL: CRBIST Position   */
#define SYS_SRAM_BISTCTL_CRBIST_Msk      (0x1ul << SYS_SRAM_BISTCTL_CRBIST_Pos)            /*!< SYS_T::SRAM_BISTCTL: CRBIST Mask       */

#define SYS_SRAM_BISTCTL_CANBIST_Pos     (3)                                               /*!< SYS_T::SRAM_BISTCTL: CANBIST Position  */
#define SYS_SRAM_BISTCTL_CANBIST_Msk     (0x1ul << SYS_SRAM_BISTCTL_CANBIST_Pos)           /*!< SYS_T::SRAM_BISTCTL: CANBIST Mask      */

#define SYS_SRAM_BISTCTL_USBBIST_Pos     (4)                                               /*!< SYS_T::SRAM_BISTCTL: USBBIST Position  */
#define SYS_SRAM_BISTCTL_USBBIST_Msk     (0x1ul << SYS_SRAM_BISTCTL_USBBIST_Pos)           /*!< SYS_T::SRAM_BISTCTL: USBBIST Mask      */

#define SYS_SRAM_BISTCTL_SPIMBIST_Pos    (5)                                               /*!< SYS_T::SRAM_BISTCTL: SPIMBIST Position */
#define SYS_SRAM_BISTCTL_SPIMBIST_Msk    (0x1ul << SYS_SRAM_BISTCTL_SPIMBIST_Pos)          /*!< SYS_T::SRAM_BISTCTL: SPIMBIST Mask     */

#define SYS_SRAM_BISTCTL_EMCBIST_Pos     (6)                                               /*!< SYS_T::SRAM_BISTCTL: EMCBIST Position  */
#define SYS_SRAM_BISTCTL_EMCBIST_Msk     (0x1ul << SYS_SRAM_BISTCTL_EMCBIST_Pos)           /*!< SYS_T::SRAM_BISTCTL: EMCBIST Mask      */

#define SYS_SRAM_BISTCTL_PDMABIST_Pos    (7)                                               /*!< SYS_T::SRAM_BISTCTL: PDMABIST Position */
#define SYS_SRAM_BISTCTL_PDMABIST_Msk    (0x1ul << SYS_SRAM_BISTCTL_PDMABIST_Pos)          /*!< SYS_T::SRAM_BISTCTL: PDMABIST Mask     */

#define SYS_SRAM_BISTCTL_HSUSBDBIST_Pos  (8)                                               /*!< SYS_T::SRAM_BISTCTL: HSUSBDBIST Position*/
#define SYS_SRAM_BISTCTL_HSUSBDBIST_Msk  (0x1ul << SYS_SRAM_BISTCTL_HSUSBDBIST_Pos)        /*!< SYS_T::SRAM_BISTCTL: HSUSBDBIST Mask   */

#define SYS_SRAM_BISTCTL_HSUSBHBIST_Pos  (9)                                               /*!< SYS_T::SRAM_BISTCTL: HSUSBHBIST Position*/
#define SYS_SRAM_BISTCTL_HSUSBHBIST_Msk  (0x1ul << SYS_SRAM_BISTCTL_HSUSBHBIST_Pos)        /*!< SYS_T::SRAM_BISTCTL: HSUSBHBIST Mask   */

#define SYS_SRAM_BISTCTL_SRB0S0_Pos      (16)                                              /*!< SYS_T::SRAM_BISTCTL: SRB0S0 Position   */
#define SYS_SRAM_BISTCTL_SRB0S0_Msk      (0x1ul << SYS_SRAM_BISTCTL_SRB0S0_Pos)            /*!< SYS_T::SRAM_BISTCTL: SRB0S0 Mask       */

#define SYS_SRAM_BISTCTL_SRB0S1_Pos      (17)                                              /*!< SYS_T::SRAM_BISTCTL: SRB0S1 Position   */
#define SYS_SRAM_BISTCTL_SRB0S1_Msk      (0x1ul << SYS_SRAM_BISTCTL_SRB0S1_Pos)            /*!< SYS_T::SRAM_BISTCTL: SRB0S1 Mask       */

#define SYS_SRAM_BISTCTL_SRB1S0_Pos      (18)                                              /*!< SYS_T::SRAM_BISTCTL: SRB1S0 Position   */
#define SYS_SRAM_BISTCTL_SRB1S0_Msk      (0x1ul << SYS_SRAM_BISTCTL_SRB1S0_Pos)            /*!< SYS_T::SRAM_BISTCTL: SRB1S0 Mask       */

#define SYS_SRAM_BISTCTL_SRB1S1_Pos      (19)                                              /*!< SYS_T::SRAM_BISTCTL: SRB1S1 Position   */
#define SYS_SRAM_BISTCTL_SRB1S1_Msk      (0x1ul << SYS_SRAM_BISTCTL_SRB1S1_Pos)            /*!< SYS_T::SRAM_BISTCTL: SRB1S1 Mask       */

#define SYS_SRAM_BISTCTL_SRB1S2_Pos      (20)                                              /*!< SYS_T::SRAM_BISTCTL: SRB1S2 Position   */
#define SYS_SRAM_BISTCTL_SRB1S2_Msk      (0x1ul << SYS_SRAM_BISTCTL_SRB1S2_Pos)            /*!< SYS_T::SRAM_BISTCTL: SRB1S2 Mask       */

#define SYS_SRAM_BISTCTL_SRB1S3_Pos      (21)                                              /*!< SYS_T::SRAM_BISTCTL: SRB1S3 Position   */
#define SYS_SRAM_BISTCTL_SRB1S3_Msk      (0x1ul << SYS_SRAM_BISTCTL_SRB1S3_Pos)            /*!< SYS_T::SRAM_BISTCTL: SRB1S3 Mask       */

#define SYS_SRAM_BISTCTL_SRB1S4_Pos      (22)                                              /*!< SYS_T::SRAM_BISTCTL: SRB1S4 Position   */
#define SYS_SRAM_BISTCTL_SRB1S4_Msk      (0x1ul << SYS_SRAM_BISTCTL_SRB1S4_Pos)            /*!< SYS_T::SRAM_BISTCTL: SRB1S4 Mask       */

#define SYS_SRAM_BISTCTL_SRB1S5_Pos      (23)                                              /*!< SYS_T::SRAM_BISTCTL: SRB1S5 Position   */
#define SYS_SRAM_BISTCTL_SRB1S5_Msk      (0x1ul << SYS_SRAM_BISTCTL_SRB1S5_Pos)            /*!< SYS_T::SRAM_BISTCTL: SRB1S5 Mask       */

#define SYS_SRAM_BISTSTS_SRBISTEF0_Pos   (0)                                               /*!< SYS_T::SRAM_BISTSTS: SRBISTEF0 Position*/
#define SYS_SRAM_BISTSTS_SRBISTEF0_Msk   (0x1ul << SYS_SRAM_BISTSTS_SRBISTEF0_Pos)         /*!< SYS_T::SRAM_BISTSTS: SRBISTEF0 Mask    */

#define SYS_SRAM_BISTSTS_SRBISTEF1_Pos   (1)                                               /*!< SYS_T::SRAM_BISTSTS: SRBISTEF1 Position*/
#define SYS_SRAM_BISTSTS_SRBISTEF1_Msk   (0x1ul << SYS_SRAM_BISTSTS_SRBISTEF1_Pos)         /*!< SYS_T::SRAM_BISTSTS: SRBISTEF1 Mask    */

#define SYS_SRAM_BISTSTS_CRBISTEF_Pos    (2)                                               /*!< SYS_T::SRAM_BISTSTS: CRBISTEF Position */
#define SYS_SRAM_BISTSTS_CRBISTEF_Msk    (0x1ul << SYS_SRAM_BISTSTS_CRBISTEF_Pos)          /*!< SYS_T::SRAM_BISTSTS: CRBISTEF Mask     */

#define SYS_SRAM_BISTSTS_CANBEF_Pos      (3)                                               /*!< SYS_T::SRAM_BISTSTS: CANBEF Position   */
#define SYS_SRAM_BISTSTS_CANBEF_Msk      (0x1ul << SYS_SRAM_BISTSTS_CANBEF_Pos)            /*!< SYS_T::SRAM_BISTSTS: CANBEF Mask       */

#define SYS_SRAM_BISTSTS_USBBEF_Pos      (4)                                               /*!< SYS_T::SRAM_BISTSTS: USBBEF Position   */
#define SYS_SRAM_BISTSTS_USBBEF_Msk      (0x1ul << SYS_SRAM_BISTSTS_USBBEF_Pos)            /*!< SYS_T::SRAM_BISTSTS: USBBEF Mask       */

#define SYS_SRAM_BISTSTS_SRBEND0_Pos     (16)                                              /*!< SYS_T::SRAM_BISTSTS: SRBEND0 Position  */
#define SYS_SRAM_BISTSTS_SRBEND0_Msk     (0x1ul << SYS_SRAM_BISTSTS_SRBEND0_Pos)           /*!< SYS_T::SRAM_BISTSTS: SRBEND0 Mask      */

#define SYS_SRAM_BISTSTS_SRBEND1_Pos     (17)                                              /*!< SYS_T::SRAM_BISTSTS: SRBEND1 Position  */
#define SYS_SRAM_BISTSTS_SRBEND1_Msk     (0x1ul << SYS_SRAM_BISTSTS_SRBEND1_Pos)           /*!< SYS_T::SRAM_BISTSTS: SRBEND1 Mask      */

#define SYS_SRAM_BISTSTS_CRBEND_Pos      (18)                                              /*!< SYS_T::SRAM_BISTSTS: CRBEND Position   */
#define SYS_SRAM_BISTSTS_CRBEND_Msk      (0x1ul << SYS_SRAM_BISTSTS_CRBEND_Pos)            /*!< SYS_T::SRAM_BISTSTS: CRBEND Mask       */

#define SYS_SRAM_BISTSTS_CANBEND_Pos     (19)                                              /*!< SYS_T::SRAM_BISTSTS: CANBEND Position  */
#define SYS_SRAM_BISTSTS_CANBEND_Msk     (0x1ul << SYS_SRAM_BISTSTS_CANBEND_Pos)           /*!< SYS_T::SRAM_BISTSTS: CANBEND Mask      */

#define SYS_SRAM_BISTSTS_USBBEND_Pos     (20)                                              /*!< SYS_T::SRAM_BISTSTS: USBBEND Position  */
#define SYS_SRAM_BISTSTS_USBBEND_Msk     (0x1ul << SYS_SRAM_BISTSTS_USBBEND_Pos)           /*!< SYS_T::SRAM_BISTSTS: USBBEND Mask      */

#define SYS_HIRCTCTL_FREQSEL_Pos         (0)                                               /*!< SYS_T::HIRCTCTL: FREQSEL Position      */
#define SYS_HIRCTCTL_FREQSEL_Msk         (0x3ul << SYS_HIRCTCTL_FREQSEL_Pos)               /*!< SYS_T::HIRCTCTL: FREQSEL Mask          */

#define SYS_HIRCTCTL_LOOPSEL_Pos         (4)                                               /*!< SYS_T::HIRCTCTL: LOOPSEL Position      */
#define SYS_HIRCTCTL_LOOPSEL_Msk         (0x3ul << SYS_HIRCTCTL_LOOPSEL_Pos)               /*!< SYS_T::HIRCTCTL: LOOPSEL Mask          */

#define SYS_HIRCTCTL_RETRYCNT_Pos        (6)                                               /*!< SYS_T::HIRCTCTL: RETRYCNT Position     */
#define SYS_HIRCTCTL_RETRYCNT_Msk        (0x3ul << SYS_HIRCTCTL_RETRYCNT_Pos)              /*!< SYS_T::HIRCTCTL: RETRYCNT Mask         */

#define SYS_HIRCTCTL_CESTOPEN_Pos        (8)                                               /*!< SYS_T::HIRCTCTL: CESTOPEN Position     */
#define SYS_HIRCTCTL_CESTOPEN_Msk        (0x1ul << SYS_HIRCTCTL_CESTOPEN_Pos)              /*!< SYS_T::HIRCTCTL: CESTOPEN Mask         */

#define SYS_HIRCTCTL_BOUNDEN_Pos         (9)                                               /*!< SYS_T::HIRCTCTL: BOUNDEN Position      */
#define SYS_HIRCTCTL_BOUNDEN_Msk         (0x1ul << SYS_HIRCTCTL_BOUNDEN_Pos)               /*!< SYS_T::HIRCTCTL: BOUNDEN Mask          */  

#define SYS_HIRCTCTL_REFCKSEL_Pos        (10)                                              /*!< SYS_T::HIRCTCTL: REFCKSEL Position     */
#define SYS_HIRCTCTL_REFCKSEL_Msk        (0x1ul << SYS_HIRCTCTL_REFCKSEL_Pos)              /*!< SYS_T::HIRCTCTL: REFCKSEL Mask         */

#define SYS_HIRCTCTL_BOUNDARY_Pos        (16)                                              /*!< SYS_T::HIRCTCTL: BOUNDARY Position     */
#define SYS_HIRCTCTL_BOUNDARY_Msk        (0x1ful << SYS_HIRCTCTL_BOUNDARY_Pos)             /*!< SYS_T::HIRCTCTL: BOUNDARY Mask         */

#define SYS_HIRCTIEN_TFAILIEN_Pos        (1)                                               /*!< SYS_T::HIRCTIEN: TFAILIEN Position     */
#define SYS_HIRCTIEN_TFAILIEN_Msk        (0x1ul << SYS_HIRCTIEN_TFAILIEN_Pos)              /*!< SYS_T::HIRCTIEN: TFAILIEN Mask         */

#define SYS_HIRCTIEN_CLKEIEN_Pos         (2)                                               /*!< SYS_T::HIRCTIEN: CLKEIEN Position      */
#define SYS_HIRCTIEN_CLKEIEN_Msk         (0x1ul << SYS_HIRCTIEN_CLKEIEN_Pos)               /*!< SYS_T::HIRCTIEN: CLKEIEN Mask          */

#define SYS_HIRCTISTS_FREQLOCK_Pos       (0)                                               /*!< SYS_T::HIRCTISTS: FREQLOCK Position    */
#define SYS_HIRCTISTS_FREQLOCK_Msk       (0x1ul << SYS_HIRCTISTS_FREQLOCK_Pos)             /*!< SYS_T::HIRCTISTS: FREQLOCK Mask        */

#define SYS_HIRCTISTS_TFAILIF_Pos        (1)                                               /*!< SYS_T::HIRCTISTS: TFAILIF Position     */
#define SYS_HIRCTISTS_TFAILIF_Msk        (0x1ul << SYS_HIRCTISTS_TFAILIF_Pos)              /*!< SYS_T::HIRCTISTS: TFAILIF Mask         */

#define SYS_HIRCTISTS_CLKERRIF_Pos       (2)                                               /*!< SYS_T::HIRCTISTS: CLKERRIF Position    */
#define SYS_HIRCTISTS_CLKERRIF_Msk       (0x1ul << SYS_HIRCTISTS_CLKERRIF_Pos)             /*!< SYS_T::HIRCTISTS: CLKERRIF Mask        */

#define SYS_HIRCTISTS_OVBDIF_Pos         (3)                                               /*!< SYS_T::HIRCTISTS: OVBDIF Position      */
#define SYS_HIRCTISTS_OVBDIF_Msk         (0x1ul << SYS_HIRCTISTS_OVBDIF_Pos)               /*!< SYS_T::HIRCTISTS: OVBDIF Mask          */

#define SYS_IRCTCTL_FREQSEL_Pos          (0)                                               /*!< SYS_T::IRCTCTL: FREQSEL Position       */
#define SYS_IRCTCTL_FREQSEL_Msk          (0x3ul << SYS_IRCTCTL_FREQSEL_Pos)                /*!< SYS_T::IRCTCTL: FREQSEL Mask           */

#define SYS_IRCTCTL_LOOPSEL_Pos          (4)                                               /*!< SYS_T::IRCTCTL: LOOPSEL Position       */
#define SYS_IRCTCTL_LOOPSEL_Msk          (0x3ul << SYS_IRCTCTL_LOOPSEL_Pos)                /*!< SYS_T::IRCTCTL: LOOPSEL Mask           */

#define SYS_IRCTCTL_RETRYCNT_Pos         (6)                                               /*!< SYS_T::IRCTCTL: RETRYCNT Position      */
#define SYS_IRCTCTL_RETRYCNT_Msk         (0x3ul << SYS_IRCTCTL_RETRYCNT_Pos)               /*!< SYS_T::IRCTCTL: RETRYCNT Mask          */

#define SYS_IRCTCTL_CESTOPEN_Pos         (8)                                               /*!< SYS_T::IRCTCTL: CESTOPEN Position      */
#define SYS_IRCTCTL_CESTOPEN_Msk         (0x1ul << SYS_IRCTCTL_CESTOPEN_Pos)               /*!< SYS_T::IRCTCTL: CESTOPEN Mask          */

#define SYS_IRCTCTL_REFCKSEL_Pos         (10)                                              /*!< SYS_T::IRCTCTL: REFCKSEL Position      */
#define SYS_IRCTCTL_REFCKSEL_Msk         (0x1ul << SYS_IRCTCTL_REFCKSEL_Pos)               /*!< SYS_T::IRCTCTL: REFCKSEL Mask          */

#define SYS_IRCTIEN_TFAILIEN_Pos         (1)                                               /*!< SYS_T::IRCTIEN: TFAILIEN Position      */
#define SYS_IRCTIEN_TFAILIEN_Msk         (0x1ul << SYS_IRCTIEN_TFAILIEN_Pos)               /*!< SYS_T::IRCTIEN: TFAILIEN Mask          */

#define SYS_IRCTIEN_CLKEIEN_Pos          (2)                                               /*!< SYS_T::IRCTIEN: CLKEIEN Position       */
#define SYS_IRCTIEN_CLKEIEN_Msk          (0x1ul << SYS_IRCTIEN_CLKEIEN_Pos)                /*!< SYS_T::IRCTIEN: CLKEIEN Mask           */

#define SYS_IRCTISTS_FREQLOCK_Pos        (0)                                               /*!< SYS_T::IRCTISTS: FREQLOCK Position     */
#define SYS_IRCTISTS_FREQLOCK_Msk        (0x1ul << SYS_IRCTISTS_FREQLOCK_Pos)              /*!< SYS_T::IRCTISTS: FREQLOCK Mask         */

#define SYS_IRCTISTS_TFAILIF_Pos         (1)                                               /*!< SYS_T::IRCTISTS: TFAILIF Position      */
#define SYS_IRCTISTS_TFAILIF_Msk         (0x1ul << SYS_IRCTISTS_TFAILIF_Pos)               /*!< SYS_T::IRCTISTS: TFAILIF Mask          */

#define SYS_IRCTISTS_CLKERRIF_Pos        (2)                                               /*!< SYS_T::IRCTISTS: CLKERRIF Position     */
#define SYS_IRCTISTS_CLKERRIF_Msk        (0x1ul << SYS_IRCTISTS_CLKERRIF_Pos)              /*!< SYS_T::IRCTISTS: CLKERRIF Mask         */

#define SYS_REGLCTL_REGLCTL_Pos          (0)                                               /*!< SYS_T::REGLCTL: REGLCTL Position       */
#define SYS_REGLCTL_REGLCTL_Msk          (0x1ul << SYS_REGLCTL_REGLCTL_Pos)                /*!< SYS_T::REGLCTL: REGLCTL Mask           */

#define SYS_PORDISAN_POROFFAN_Pos        (0)                                               /*!< SYS_T::PORDISAN: POROFFAN Position     */
#define SYS_PORDISAN_POROFFAN_Msk        (0xfffful << SYS_PORDISAN_POROFFAN_Pos)           /*!< SYS_T::PORDISAN: POROFFAN Mask         */

#define SYS_CSERVER_VERSION_Pos          (0)                                               /*!< SYS_T::CSERVER: VERSION Position       */
#define SYS_CSERVER_VERSION_Msk          (0xfful << SYS_CSERVER_VERSION_Pos)               /*!< SYS_T::CSERVER: VERSION Mask           */

#define SYS_PLCTL_PLSEL_Pos              (0)                                               /*!< SYS_T::PLCTL: PLSEL Position           */
#define SYS_PLCTL_PLSEL_Msk              (0x3ul << SYS_PLCTL_PLSEL_Pos)                    /*!< SYS_T::PLCTL: PLSEL Mask               */

#define SYS_PLCTL_LVSSTEP_Pos            (16)                                              /*!< SYS_T::PLCTL: LVSSTEP Position         */
#define SYS_PLCTL_LVSSTEP_Msk            (0x3ful << SYS_PLCTL_LVSSTEP_Pos)                 /*!< SYS_T::PLCTL: LVSSTEP Mask             */

#define SYS_PLCTL_LVSPRD_Pos             (24)                                              /*!< SYS_T::PLCTL: LVSPRD Position          */
#define SYS_PLCTL_LVSPRD_Msk             (0xfful << SYS_PLCTL_LVSPRD_Pos)                  /*!< SYS_T::PLCTL: LVSPRD Mask              */

#define SYS_PLSTS_PLCBUSY_Pos            (0)                                               /*!< SYS_T::PLSTS: PLCBUSY Position         */
#define SYS_PLSTS_PLCBUSY_Msk            (0x1ul << SYS_PLSTS_PLCBUSY_Pos)                  /*!< SYS_T::PLSTS: PLCBUSY Mask             */

#define SYS_PLSTS_PLSTATUS_Pos           (8)                                               /*!< SYS_T::PLSTS: PLSTATUS Position        */
#define SYS_PLSTS_PLSTATUS_Msk           (0x3ul << SYS_PLSTS_PLSTATUS_Pos)                 /*!< SYS_T::PLSTS: PLSTATUS Mask            */

#define SYS_AHBMCTL_INTACTEN_Pos         (0)                                               /*!< SYS_T::AHBMCTL: INTACTEN Position      */
#define SYS_AHBMCTL_INTACTEN_Msk         (0x1ul << SYS_AHBMCTL_INTACTEN_Pos)               /*!< SYS_T::AHBMCTL: INTACTEN Mask          */

/**@}*/ /* SYS_CONST */
/**@}*/ /* end of SYS register group */

/**
    @addtogroup NMI NMI Controller (NMI)
    Memory Mapped Structure for NMI Controller
@{ */

typedef struct
{


    /**
@var NMI_T::NMIEN

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">NMIEN
</font><br><p> <font size="2">
Offset: 0x00  NMI Source Interrupt Enable Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BODOUT</td><td><div style="word-wrap: break-word;"><b>BOD NMI Source Enable (Write Protect)
</b><br>
0 = BOD NMI source Disabled.
<br>
1 = BOD NMI source Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[1]</td><td>IRC_INT</td><td><div style="word-wrap: break-word;"><b>IRC TRIM NMI Source Enable (Write Protect)
</b><br>
0 = IRC TRIM NMI source Disabled.
<br>
1 = IRC TRIM NMI source Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[2]</td><td>PWRWU_INT</td><td><div style="word-wrap: break-word;"><b>Power-down Mode Wake-up NMI Source Enable (Write Protect)
</b><br>
0 = Power-down mode wake-up NMI source Disabled.
<br>
1 = Power-down mode wake-up NMI source Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[3]</td><td>SRAM_PERR</td><td><div style="word-wrap: break-word;"><b>SRAM Parity Check NMI Source Enable (Write Protect)
</b><br>
0 = SRAM parity check error NMI source Disabled.
<br>
1 = SRAM parity check error NMI source Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[4]</td><td>CLKFAIL</td><td><div style="word-wrap: break-word;"><b>Clock Fail Detected and IRC Auto Trim Interrupt NMI Source Enable (Write Protect)
</b><br>
0 = Clock fail detected and IRC Auto Trim interrupt NMI source Disabled.
<br>
1 = Clock fail detected and IRC Auto Trim interrupt NMI source Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[6]</td><td>RTC_INT</td><td><div style="word-wrap: break-word;"><b>RTC NMI Source Enable (Write Protect)
</b><br>
0 = RTC NMI source Disabled.
<br>
1 = RTC NMI source Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[7]</td><td>TAMPER_INT</td><td><div style="word-wrap: break-word;"><b>TAMPER_INT NMI Source Enable (Write Protect)
</b><br>
0 = Backup register tamper detected NMI source Disabled.
<br>
1 = Backup register tamper detected NMI source Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[8]</td><td>EINT0</td><td><div style="word-wrap: break-word;"><b>External Interrupt From PA.6 or PB.5 Pin NMI Source Enable (Write Protect)
</b><br>
0 = External interrupt from PA.6 or PB.5 pin NMI source Disabled.
<br>
1 = External interrupt from PA.6 or PB.5 pin NMI source Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[9]</td><td>EINT1</td><td><div style="word-wrap: break-word;"><b>External Interrupt From PA.7, PB.4 or PD.15 Pin NMI Source Enable (Write Protect)
</b><br>
0 = External interrupt from PA.7, PB.4 or PD.15 pin NMI source Disabled.
<br>
1 = External interrupt from PA.7, PB.4 or PD.15 pin NMI source Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[10]</td><td>EINT2</td><td><div style="word-wrap: break-word;"><b>External Interrupt From PB.3 or PC.6 Pin NMI Source Enable (Write Protect)
</b><br>
0 = External interrupt from PB.3 or PC.6 pin NMI source Disabled.
<br>
1 = External interrupt from PB.3 or PC.6 pin NMI source Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[11]</td><td>EINT3</td><td><div style="word-wrap: break-word;"><b>External Interrupt From PB.2 or PC.7 Pin NMI Source Enable (Write Protect)
</b><br>
0 = External interrupt from PB.2 or PC.7 pin NMI source Disabled.
<br>
1 = External interrupt from PB.2 or PC.7 pin NMI source Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[12]</td><td>EINT4</td><td><div style="word-wrap: break-word;"><b>External Interrupt From PA.8, PB.6 or PF.15 Pin NMI Source Enable (Write Protect)
</b><br>
0 = External interrupt from PA.8, PB.6 or PF.15 pin NMI source Disabled.
<br>
1 = External interrupt from PA.8, PB.6 or PF.15 pin NMI source Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[13]</td><td>EINT5</td><td><div style="word-wrap: break-word;"><b>External Interrupt From PB.7 or PF.14 Pin NMI Source Enable (Write Protect)
</b><br>
0 = External interrupt from PB.7 or PF.14 pin NMI source Disabled.
<br>
1 = External interrupt from PB.7 or PF.14 pin NMI source Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[14]</td><td>UART0_INT</td><td><div style="word-wrap: break-word;"><b>UART0 NMI Source Enable (Write Protect)
</b><br>
0 = UART0 NMI source Disabled.
<br>
1 = UART0 NMI source Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[15]</td><td>UART1_INT</td><td><div style="word-wrap: break-word;"><b>UART1 NMI Source Enable (Write Protect)
</b><br>
0 = UART1 NMI source Disabled.
<br>
1 = UART1 NMI source Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var NMI_T::NMISTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">NMISTS
</font><br><p> <font size="2">
Offset: 0x04  NMI Source Interrupt Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>BODOUT</td><td><div style="word-wrap: break-word;"><b>BOD Interrupt Flag (Read Only)
</b><br>
0 = BOD interrupt is deasserted.
<br>
1 = BOD interrupt is asserted.
<br>
</div></td></tr><tr><td>
[1]</td><td>IRC_INT</td><td><div style="word-wrap: break-word;"><b>IRC TRIM Interrupt Flag (Read Only)
</b><br>
0 = HIRC TRIM interrupt is deasserted.
<br>
1 = HIRC TRIM interrupt is asserted.
<br>
</div></td></tr><tr><td>
[2]</td><td>PWRWU_INT</td><td><div style="word-wrap: break-word;"><b>Power-down Mode Wake-up Interrupt Flag (Read Only)
</b><br>
0 = Power-down mode wake-up interrupt is deasserted.
<br>
1 = Power-down mode wake-up interrupt is asserted.
<br>
</div></td></tr><tr><td>
[3]</td><td>SRAM_PERR</td><td><div style="word-wrap: break-word;"><b>SRAM ParityCheck Error Interrupt Flag (Read Only)
</b><br>
0 = SRAM parity check error interrupt is deasserted.
<br>
1 = SRAM parity check error interrupt is asserted.
<br>
</div></td></tr><tr><td>
[4]</td><td>CLKFAIL</td><td><div style="word-wrap: break-word;"><b>Clock Fail Detected or IRC Auto Trim Interrupt Flag (Read Only)
</b><br>
0 = Clock fail detected or IRC Auto Trim interrupt is deasserted.
<br>
1 = Clock fail detected or IRC Auto Trim interrupt is asserted.
<br>
</div></td></tr><tr><td>
[6]</td><td>RTC_INT</td><td><div style="word-wrap: break-word;"><b>RTC Interrupt Flag (Read Only)
</b><br>
0 = RTC interrupt is deasserted.
<br>
1 = RTC interrupt is asserted.
<br>
</div></td></tr><tr><td>
[7]</td><td>TAMPER_INT</td><td><div style="word-wrap: break-word;"><b>TAMPER_INT Interrupt Flag (Read Only)
</b><br>
0 = Backup register tamper detected interrupt is deasserted.
<br>
1 = Backup register tamper detected interrupt is asserted.
<br>
</div></td></tr><tr><td>
[8]</td><td>EINT0</td><td><div style="word-wrap: break-word;"><b>External Interrupt From PA.6 or PB.5 Pin Interrupt Flag (Read Only)
</b><br>
0 = External Interrupt from PA.6 or PB.5 interrupt is deasserted.
<br>
1 = External Interrupt from PA.6 or PB.5 interrupt is asserted.
<br>
</div></td></tr><tr><td>
[9]</td><td>EINT1</td><td><div style="word-wrap: break-word;"><b>External Interrupt From PA.7, PB.4 or PD.15 Pin Interrupt Flag (Read Only)
</b><br>
0 = External Interrupt from PA.7, PB.4 or PD.15 interrupt is deasserted.
<br>
1 = External Interrupt from PA.7, PB.4 or PD.15 interrupt is asserted.
<br>
</div></td></tr><tr><td>
[10]</td><td>EINT2</td><td><div style="word-wrap: break-word;"><b>External Interrupt From PB.3 or PC.6 Pin Interrupt Flag (Read Only)
</b><br>
0 = External Interrupt from PB.3 or PC.6 interrupt is deasserted.
<br>
1 = External Interrupt from PB.3 or PC.6 interrupt is asserted.
<br>
</div></td></tr><tr><td>
[11]</td><td>EINT3</td><td><div style="word-wrap: break-word;"><b>External Interrupt From PB.2 or PC.7 Pin Interrupt Flag (Read Only)
</b><br>
0 = External Interrupt from PB.2 or PC.7 interrupt is deasserted.
<br>
1 = External Interrupt from PB.2 or PC.7 interrupt is asserted.
<br>
</div></td></tr><tr><td>
[12]</td><td>EINT4</td><td><div style="word-wrap: break-word;"><b>External Interrupt From PA.8, PB.6 or PF.15 Pin Interrupt Flag (Read Only)
</b><br>
0 = External Interrupt from PA.8, PB.6 or PF.15 interrupt is deasserted.
<br>
1 = External Interrupt from PA.8, PB.6 or PF.15 interrupt is asserted.
<br>
</div></td></tr><tr><td>
[13]</td><td>EINT5</td><td><div style="word-wrap: break-word;"><b>External Interrupt From PB.7 or PF.14 Pin Interrupt Flag (Read Only)
</b><br>
0 = External Interrupt from PB.7 or PF.14 interrupt is deasserted.
<br>
1 = External Interrupt from PB.7 or PF.14 interrupt is asserted.
<br>
</div></td></tr><tr><td>
[14]</td><td>UART0_INT</td><td><div style="word-wrap: break-word;"><b>UART0 Interrupt Flag (Read Only)
</b><br>
0 = UART1 interrupt is deasserted.
<br>
1 = UART1 interrupt is asserted.
<br>
</div></td></tr><tr><td>
[15]</td><td>UART1_INT</td><td><div style="word-wrap: break-word;"><b>UART1 Interrupt Flag (Read Only)
</b><br>
0 = UART1 interrupt is deasserted.
<br>
1 = UART1 interrupt is asserted.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t NMIEN;                 /*!< [0x0000] NMI Source Interrupt Enable Register                             */
    __I  uint32_t NMISTS;                /*!< [0x0004] NMI Source Interrupt Status Register                             */

} NMI_T;

/**
    @addtogroup NMI_CONST NMI Bit Field Definition
    Constant Definitions for NMI Controller
@{ */

#define NMI_NMIEN_BODOUT_Pos             (0)                                               /*!< NMI_T::NMIEN: BODOUT Position          */
#define NMI_NMIEN_BODOUT_Msk             (0x1ul << NMI_NMIEN_BODOUT_Pos)                   /*!< NMI_T::NMIEN: BODOUT Mask              */

#define NMI_NMIEN_IRC_INT_Pos            (1)                                               /*!< NMI_T::NMIEN: IRC_INT Position         */
#define NMI_NMIEN_IRC_INT_Msk            (0x1ul << NMI_NMIEN_IRC_INT_Pos)                  /*!< NMI_T::NMIEN: IRC_INT Mask             */

#define NMI_NMIEN_PWRWU_INT_Pos          (2)                                               /*!< NMI_T::NMIEN: PWRWU_INT Position       */
#define NMI_NMIEN_PWRWU_INT_Msk          (0x1ul << NMI_NMIEN_PWRWU_INT_Pos)                /*!< NMI_T::NMIEN: PWRWU_INT Mask           */

#define NMI_NMIEN_SRAM_PERR_Pos          (3)                                               /*!< NMI_T::NMIEN: SRAM_PERR Position       */
#define NMI_NMIEN_SRAM_PERR_Msk          (0x1ul << NMI_NMIEN_SRAM_PERR_Pos)                /*!< NMI_T::NMIEN: SRAM_PERR Mask           */

#define NMI_NMIEN_CLKFAIL_Pos            (4)                                               /*!< NMI_T::NMIEN: CLKFAIL Position         */
#define NMI_NMIEN_CLKFAIL_Msk            (0x1ul << NMI_NMIEN_CLKFAIL_Pos)                  /*!< NMI_T::NMIEN: CLKFAIL Mask             */

#define NMI_NMIEN_RTC_INT_Pos            (6)                                               /*!< NMI_T::NMIEN: RTC_INT Position         */
#define NMI_NMIEN_RTC_INT_Msk            (0x1ul << NMI_NMIEN_RTC_INT_Pos)                  /*!< NMI_T::NMIEN: RTC_INT Mask             */

#define NMI_NMIEN_TAMPER_INT_Pos         (7)                                               /*!< NMI_T::NMIEN: TAMPER_INT Position      */
#define NMI_NMIEN_TAMPER_INT_Msk         (0x1ul << NMI_NMIEN_TAMPER_INT_Pos)               /*!< NMI_T::NMIEN: TAMPER_INT Mask          */

#define NMI_NMIEN_EINT0_Pos              (8)                                               /*!< NMI_T::NMIEN: EINT0 Position           */
#define NMI_NMIEN_EINT0_Msk              (0x1ul << NMI_NMIEN_EINT0_Pos)                    /*!< NMI_T::NMIEN: EINT0 Mask               */

#define NMI_NMIEN_EINT1_Pos              (9)                                               /*!< NMI_T::NMIEN: EINT1 Position           */
#define NMI_NMIEN_EINT1_Msk              (0x1ul << NMI_NMIEN_EINT1_Pos)                    /*!< NMI_T::NMIEN: EINT1 Mask               */

#define NMI_NMIEN_EINT2_Pos              (10)                                              /*!< NMI_T::NMIEN: EINT2 Position           */
#define NMI_NMIEN_EINT2_Msk              (0x1ul << NMI_NMIEN_EINT2_Pos)                    /*!< NMI_T::NMIEN: EINT2 Mask               */

#define NMI_NMIEN_EINT3_Pos              (11)                                              /*!< NMI_T::NMIEN: EINT3 Position           */
#define NMI_NMIEN_EINT3_Msk              (0x1ul << NMI_NMIEN_EINT3_Pos)                    /*!< NMI_T::NMIEN: EINT3 Mask               */

#define NMI_NMIEN_EINT4_Pos              (12)                                              /*!< NMI_T::NMIEN: EINT4 Position           */
#define NMI_NMIEN_EINT4_Msk              (0x1ul << NMI_NMIEN_EINT4_Pos)                    /*!< NMI_T::NMIEN: EINT4 Mask               */

#define NMI_NMIEN_EINT5_Pos              (13)                                              /*!< NMI_T::NMIEN: EINT5 Position           */
#define NMI_NMIEN_EINT5_Msk              (0x1ul << NMI_NMIEN_EINT5_Pos)                    /*!< NMI_T::NMIEN: EINT5 Mask               */

#define NMI_NMIEN_UART0_INT_Pos          (14)                                              /*!< NMI_T::NMIEN: UART0_INT Position       */
#define NMI_NMIEN_UART0_INT_Msk          (0x1ul << NMI_NMIEN_UART0_INT_Pos)                /*!< NMI_T::NMIEN: UART0_INT Mask           */

#define NMI_NMIEN_UART1_INT_Pos          (15)                                              /*!< NMI_T::NMIEN: UART1_INT Position       */
#define NMI_NMIEN_UART1_INT_Msk          (0x1ul << NMI_NMIEN_UART1_INT_Pos)                /*!< NMI_T::NMIEN: UART1_INT Mask           */

#define NMI_NMISTS_BODOUT_Pos            (0)                                               /*!< NMI_T::NMISTS: BODOUT Position         */
#define NMI_NMISTS_BODOUT_Msk            (0x1ul << NMI_NMISTS_BODOUT_Pos)                  /*!< NMI_T::NMISTS: BODOUT Mask             */

#define NMI_NMISTS_IRC_INT_Pos           (1)                                               /*!< NMI_T::NMISTS: IRC_INT Position        */
#define NMI_NMISTS_IRC_INT_Msk           (0x1ul << NMI_NMISTS_IRC_INT_Pos)                 /*!< NMI_T::NMISTS: IRC_INT Mask            */

#define NMI_NMISTS_PWRWU_INT_Pos         (2)                                               /*!< NMI_T::NMISTS: PWRWU_INT Position      */
#define NMI_NMISTS_PWRWU_INT_Msk         (0x1ul << NMI_NMISTS_PWRWU_INT_Pos)               /*!< NMI_T::NMISTS: PWRWU_INT Mask          */

#define NMI_NMISTS_SRAM_PERR_Pos         (3)                                               /*!< NMI_T::NMISTS: SRAM_PERR Position      */
#define NMI_NMISTS_SRAM_PERR_Msk         (0x1ul << NMI_NMISTS_SRAM_PERR_Pos)               /*!< NMI_T::NMISTS: SRAM_PERR Mask          */

#define NMI_NMISTS_CLKFAIL_Pos           (4)                                               /*!< NMI_T::NMISTS: CLKFAIL Position        */
#define NMI_NMISTS_CLKFAIL_Msk           (0x1ul << NMI_NMISTS_CLKFAIL_Pos)                 /*!< NMI_T::NMISTS: CLKFAIL Mask            */

#define NMI_NMISTS_RTC_INT_Pos           (6)                                               /*!< NMI_T::NMISTS: RTC_INT Position        */
#define NMI_NMISTS_RTC_INT_Msk           (0x1ul << NMI_NMISTS_RTC_INT_Pos)                 /*!< NMI_T::NMISTS: RTC_INT Mask            */

#define NMI_NMISTS_TAMPER_INT_Pos        (7)                                               /*!< NMI_T::NMISTS: TAMPER_INT Position     */
#define NMI_NMISTS_TAMPER_INT_Msk        (0x1ul << NMI_NMISTS_TAMPER_INT_Pos)              /*!< NMI_T::NMISTS: TAMPER_INT Mask         */

#define NMI_NMISTS_EINT0_Pos             (8)                                               /*!< NMI_T::NMISTS: EINT0 Position          */
#define NMI_NMISTS_EINT0_Msk             (0x1ul << NMI_NMISTS_EINT0_Pos)                   /*!< NMI_T::NMISTS: EINT0 Mask              */

#define NMI_NMISTS_EINT1_Pos             (9)                                               /*!< NMI_T::NMISTS: EINT1 Position          */
#define NMI_NMISTS_EINT1_Msk             (0x1ul << NMI_NMISTS_EINT1_Pos)                   /*!< NMI_T::NMISTS: EINT1 Mask              */

#define NMI_NMISTS_EINT2_Pos             (10)                                              /*!< NMI_T::NMISTS: EINT2 Position          */
#define NMI_NMISTS_EINT2_Msk             (0x1ul << NMI_NMISTS_EINT2_Pos)                   /*!< NMI_T::NMISTS: EINT2 Mask              */

#define NMI_NMISTS_EINT3_Pos             (11)                                              /*!< NMI_T::NMISTS: EINT3 Position          */
#define NMI_NMISTS_EINT3_Msk             (0x1ul << NMI_NMISTS_EINT3_Pos)                   /*!< NMI_T::NMISTS: EINT3 Mask              */

#define NMI_NMISTS_EINT4_Pos             (12)                                              /*!< NMI_T::NMISTS: EINT4 Position          */
#define NMI_NMISTS_EINT4_Msk             (0x1ul << NMI_NMISTS_EINT4_Pos)                   /*!< NMI_T::NMISTS: EINT4 Mask              */

#define NMI_NMISTS_EINT5_Pos             (13)                                              /*!< NMI_T::NMISTS: EINT5 Position          */
#define NMI_NMISTS_EINT5_Msk             (0x1ul << NMI_NMISTS_EINT5_Pos)                   /*!< NMI_T::NMISTS: EINT5 Mask              */

#define NMI_NMISTS_UART0_INT_Pos         (14)                                              /*!< NMI_T::NMISTS: UART0_INT Position      */
#define NMI_NMISTS_UART0_INT_Msk         (0x1ul << NMI_NMISTS_UART0_INT_Pos)               /*!< NMI_T::NMISTS: UART0_INT Mask          */

#define NMI_NMISTS_UART1_INT_Pos         (15)                                              /*!< NMI_T::NMISTS: UART1_INT Position      */
#define NMI_NMISTS_UART1_INT_Msk         (0x1ul << NMI_NMISTS_UART1_INT_Pos)               /*!< NMI_T::NMISTS: UART1_INT Mask          */

/**@}*/ /* NMI_CONST */
/**@}*/ /* end of NMI register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __SYS_REG_H__ */
