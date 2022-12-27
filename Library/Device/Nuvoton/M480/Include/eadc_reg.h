/**************************************************************************//**
 * @file     eadc_reg.h
 * @version  V1.00
 * @brief    EADC register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __EADC_REG_H__
#define __EADC_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup EADC Enhanced Analog to Digital Converter(EADC)
    Memory Mapped Structure for EADC Controller
@{ */

typedef struct
{


    /**
@var EADC_T::DAT[19]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DAT[19]
</font><br><p> <font size="2">
Offset: 0x00  ADC Data Register 0~18 for Sample Module 0~18
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>RESULT</td><td><div style="word-wrap: break-word;"><b>ADC Conversion Result
</b><br>
This field contains 12 bits conversion result.
<br>
When DMOF (EADC_CTL[9]) is set to 0, 12-bit ADC conversion result with unsigned format will be filled in RESULT[11:0] and zero will be filled in RESULT[15:12].
<br>
When DMOF (EADC_CTL[9]) set to 1, 12-bit ADC conversion result with 2'complement format will be filled in RESULT[11:0] and signed bits to will be filled in RESULT[15:12].
<br>
</div></td></tr><tr><td>
[16]</td><td>OV</td><td><div style="word-wrap: break-word;"><b>Overrun Flag
</b><br>
If converted data in RESULT[11:0] has not been read before new conversion result is loaded to this register, OV is set to 1.
<br>
0 = Data in RESULT[11:0] is recent conversion result.
<br>
1 = Data in RESULT[11:0] is overwrite.
<br>
Note: It is cleared by hardware after EADC_DAT register is read.
<br>
</div></td></tr><tr><td>
[17]</td><td>VALID</td><td><div style="word-wrap: break-word;"><b>Valid Flag
</b><br>
This bit is set to 1 when corresponding sample module channel analog input conversion is completed and cleared by hardware after EADC_DAT register is read.
<br>
0 = Data in RESULT[11:0] bits is not valid.
<br>
1 = Data in RESULT[11:0] bits is valid.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EADC_T::CURDAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CURDAT
</font><br><p> <font size="2">
Offset: 0x4C  ADC PDMA Current Transfer Data Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[17:0]</td><td>CURDAT</td><td><div style="word-wrap: break-word;"><b>ADC PDMA Current Transfer Data Register
</b><br>
This register is a shadow register of EADC_DATn (n=0~18) for PDMA support.
<br>
This is a read only register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EADC_T::CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL
</font><br><p> <font size="2">
Offset: 0x50  ADC Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ADCEN</td><td><div style="word-wrap: break-word;"><b>ADC Converter Enable Bit
</b><br>
0 = Disabled EADC.
<br>
1 = Enabled EADC.
<br>
Note: Before starting ADC conversion function, this bit should be set to 1
<br>
Clear it to 0 to disable ADC converter analog circuit power consumption.
<br>
</div></td></tr><tr><td>
[1]</td><td>ADCRST</td><td><div style="word-wrap: break-word;"><b>ADC Converter Control Circuits Reset
</b><br>
0 = No effect.
<br>
1 = Cause ADC control circuits reset to initial state, but not change the ADC registers value.
<br>
Note: ADCRST bit remains 1 during ADC reset, when ADC reset end, the ADCRST bit is automatically cleared to 0.
<br>
</div></td></tr><tr><td>
[2]</td><td>ADCIEN0</td><td><div style="word-wrap: break-word;"><b>Specific Sample Module ADC ADINT0 Interrupt Enable Bit
</b><br>
The ADC converter generates a conversion end ADIF0 (EADC_STATUS2[0]) upon the end of specific sample module ADC conversion
<br>
If ADCIEN0 bit is set then conversion end interrupt request ADINT0 is generated.
<br>
0 = Specific sample module ADC ADINT0 interrupt function Disabled.
<br>
1 = Specific sample module ADC ADINT0 interrupt function Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>ADCIEN1</td><td><div style="word-wrap: break-word;"><b>Specific Sample Module ADC ADINT1 Interrupt Enable Bit
</b><br>
The ADC converter generates a conversion end ADIF1 (EADC_STATUS2[1]) upon the end of specific sample module ADC conversion
<br>
If ADCIEN1 bit is set then conversion end interrupt request ADINT1 is generated.
<br>
0 = Specific sample module ADC ADINT1 interrupt function Disabled.
<br>
1 = Specific sample module ADC ADINT1 interrupt function Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>ADCIEN2</td><td><div style="word-wrap: break-word;"><b>Specific Sample Module ADC ADINT2 Interrupt Enable Bit
</b><br>
The ADC converter generates a conversion end ADIF2 (EADC_STATUS2[2]) upon the end of specific sample module ADC conversion
<br>
If ADCIEN2 bit is set then conversion end interrupt request ADINT2 is generated.
<br>
0 = Specific sample module ADC ADINT2 interrupt function Disabled.
<br>
1 = Specific sample module ADC ADINT2 interrupt function Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>ADCIEN3</td><td><div style="word-wrap: break-word;"><b>Specific Sample Module ADC ADINT3 Interrupt Enable Bit
</b><br>
The ADC converter generates a conversion end ADIF3 (EADC_STATUS2[3]) upon the end of specific sample module ADC conversion
<br>
If ADCIEN3 bit is set then conversion end interrupt request ADINT3 is generated.
<br>
0 = Specific sample module ADC ADINT3 interrupt function Disabled.
<br>
1 = Specific sample module ADC ADINT3 interrupt function Enabled.
<br>
</div></td></tr><tr><td>
[7:6]</td><td>RESSEL</td><td><div style="word-wrap: break-word;"><b>Resolution Selection
</b><br>
00 = 6-bit ADC result will be put at RESULT (EADC_DATn[5:0]).
<br>
01 = 8-bit ADC result will be put at RESULT (EADC_DATn[7:0]).
<br>
10 = 10-bit ADC result will be put at RESULT (EADC_DATn[9:0]).
<br>
11 = 12-bit ADC result will be put at RESULT (EADC_DATn[11:0]).
<br>
</div></td></tr><tr><td>
[8]</td><td>DIFFEN</td><td><div style="word-wrap: break-word;"><b>Differential Analog Input Mode Enable Bit
</b><br>
0 = Single-end analog input mode.
<br>
1 = Differential analog input mode.
<br>
</div></td></tr><tr><td>
[9]</td><td>DMOF</td><td><div style="word-wrap: break-word;"><b>ADC Differential Input Mode Output Format
</b><br>
0 = ADC conversion result will be filled in RESULT (EADC_DATn[15:0] , n= 0 ~18) with unsigned format.
<br>
1 = ADC conversion result will be filled in RESULT (EADC_DATn[15:0] , n= 0 ~18) with 2'complement format.
<br>
</div></td></tr><tr><td>
[11]</td><td>PDMAEN</td><td><div style="word-wrap: break-word;"><b>PDMA Transfer Enable Bit
</b><br>
When ADC conversion is completed, the converted data is loaded into EADC_DATn (n: 0 ~ 18) register, user can enable this bit to generate a PDMA data transfer request.
<br>
0 = PDMA data transfer Disabled.
<br>
1 = PDMA data transfer Enabled.
<br>
Note: When set this bit field to 1, user must set ADCIENn (EADC_CTL[5:2], n=0~3) = 0 to disable interrupt.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EADC_T::SWTRG

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SWTRG
</font><br><p> <font size="2">
Offset: 0x54  ADC Sample Module Software Start Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[18:0]</td><td>SWTRG</td><td><div style="word-wrap: break-word;"><b>ADC Sample Module 0~18 Software Force to Start ADC Conversion
</b><br>
0 = No effect.
<br>
1 = Cause an ADC conversion when the priority is given to sample module.
<br>
Note: After write this register to start ADC conversion, the EADC_PENDSTS register will show which sample module will conversion
<br>
If user want to disable the conversion of the sample module, user can write EADC_PENDSTS register to clear it.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EADC_T::PENDSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PENDSTS
</font><br><p> <font size="2">
Offset: 0x58  ADC Start of Conversion Pending Flag Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[18:0]</td><td>STPF</td><td><div style="word-wrap: break-word;"><b>ADC Sample Module 0~18 Start of Conversion Pending Flag
</b><br>
Read:
<br>
0 = There is no pending conversion for sample module.
<br>
1 = Sample module ADC start of conversion is pending.
<br>
Write:
<br>
1 = clear pending flag & cancel the conversion for sample module.
<br>
Note: This bit remains 1 during pending state, when the respective ADC conversion is end, the STPFn (n=0~18) bit is automatically cleared to 0
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EADC_T::OVSTS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">OVSTS
</font><br><p> <font size="2">
Offset: 0x5C  ADC Sample Module Start of Conversion Overrun Flag Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[18:0]</td><td>SPOVF</td><td><div style="word-wrap: break-word;"><b>ADC SAMPLE0~18 Overrun Flag
</b><br>
0 = No sample module event overrun.
<br>
1 = Indicates a new sample module event is generated while an old one event is pending.
<br>
Note: This bit is cleared by writing 1 to it.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EADC_T::SCTL[19]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SCTL[19]
</font><br><p> <font size="2">
Offset: 0x80  ADC Sample Module 0~18 Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[3:0]</td><td>CHSEL</td><td><div style="word-wrap: break-word;"><b>ADC Sample Module Channel Selection
</b><br>
00H = EADC_CH0 (slow channel).
<br>
01H = EADC_CH1 (slow channel).
<br>
02H = EADC_CH2 (slow channel).
<br>
03H = EADC_CH3 (slow channel).
<br>
04H = EADC_CH4 (slow channel).
<br>
05H = EADC_CH5 (slow channel).
<br>
06H = EADC_CH6 (slow channel).
<br>
07H = EADC_CH7 (slow channel).
<br>
08H = EADC_CH8 (slow channel).
<br>
09H = EADC_CH9 (slow channel).
<br>
0AH = EADC_CH10 (fast channel).
<br>
0BH = EADC_CH11 (fast channel).
<br>
0CH = EADC_CH12 (fast channel).
<br>
0DH = EADC_CH13 (fast channel).
<br>
0EH = EADC_CH14 (fast channel).
<br>
0FH = EADC_CH15 (fast channel).
<br>
</div></td></tr><tr><td>
[4]</td><td>EXTREN</td><td><div style="word-wrap: break-word;"><b>ADC External Trigger Rising Edge Enable Bit
</b><br>
0 = Rising edge Disabled when ADC selects EADC0_ST as trigger source.
<br>
1 = Rising edge Enabled when ADC selects EADC0_ST as trigger source.
<br>
</div></td></tr><tr><td>
[5]</td><td>EXTFEN</td><td><div style="word-wrap: break-word;"><b>ADC External Trigger Falling Edge Enable Bit
</b><br>
0 = Falling edge Disabled when ADC selects EADC0_ST as trigger source.
<br>
1 = Falling edge Enabled when ADC selects EADC0_ST as trigger source.
<br>
</div></td></tr><tr><td>
[7:6]</td><td>TRGDLYDIV</td><td><div style="word-wrap: break-word;"><b>ADC Sample Module Start of Conversion Trigger Delay Clock Divider Selection
</b><br>
Trigger delay clock frequency:
<br>
00 = ADC_CLK/1.
<br>
01 = ADC_CLK/2.
<br>
10 = ADC_CLK/4.
<br>
11 = ADC_CLK/16.
<br>
</div></td></tr><tr><td>
[15:8]</td><td>TRGDLYCNT</td><td><div style="word-wrap: break-word;"><b>ADC Sample Module Start of Conversion Trigger Delay Time
</b><br>
Trigger delay time = TRGDLYCNT x ADC_CLK x n (n=1,2,4,16 from TRGDLYDIV setting).
<br>
</div></td></tr><tr><td>
[20:16]</td><td>TRGSEL</td><td><div style="word-wrap: break-word;"><b>ADC Sample Module Start of Conversion Trigger Source Selection
</b><br>
0H = Disable trigger.
<br>
1H = External trigger from EADC0_ST pin input.
<br>
2H = ADC ADINT0 interrupt EOC (End of conversion) pulse trigger.
<br>
3H = ADC ADINT1 interrupt EOC (End of conversion) pulse trigger.
<br>
4H = Timer0 overflow pulse trigger.
<br>
5H = Timer1 overflow pulse trigger.
<br>
6H = Timer2 overflow pulse trigger.
<br>
7H = Timer3 overflow pulse trigger.
<br>
8H = EPWM0TG0.
<br>
9H = EPWM0TG1.
<br>
AH = EPWM0TG2.
<br>
BH = EPWM0TG3.
<br>
CH = EPWM0TG4.
<br>
DH = EPWM0TG5.
<br>
EH = EPWM1TG0.
<br>
FH = EPWM1TG1.
<br>
10H = EPWM1TG2.
<br>
11H = EPWM1TG3.
<br>
12H = EPWM1TG4.
<br>
13H = EPWM1TG5.
<br>
14H = BPWM0TG.
<br>
15H = BPWM1TG.
<br>
other = Reserved.
<br>
</div></td></tr><tr><td>
[22]</td><td>INTPOS</td><td><div style="word-wrap: break-word;"><b>Interrupt Flag Position Select
</b><br>
0 = Set ADIFn (EADC_STATUS2[n], n=0~3) at ADC end of conversion.
<br>
1 = Set ADIFn (EADC_STATUS2[n], n=0~3) at ADC start of conversion.
<br>
</div></td></tr><tr><td>
[23]</td><td>DBMEN</td><td><div style="word-wrap: break-word;"><b>Double Buffer Mode Enable Bit
</b><br>
0 = Sample has one sample result register. (default).
<br>
1 = Sample has two sample result registers.
<br>
</div></td></tr><tr><td>
[31:24]</td><td>EXTSMPT</td><td><div style="word-wrap: break-word;"><b>ADC Sampling Time Extend
</b><br>
When ADC converting at high conversion rate, the sampling time of analog input voltage may not enough if input channel loading is heavy, user can extend ADC sampling time after trigger source is coming to get enough sampling time.
<br>
The range of start delay time is from 0~255 ADC clock.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EADC_T::INTSRC[4]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INTSRC[4]
</font><br><p> <font size="2">
Offset: 0xD0  ADC interrupt 0~3 Source Enable Control Register.
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SPLIE0</td><td><div style="word-wrap: break-word;"><b>Sample Module 0 Interrupt Enable Bit
</b><br>
0 = Sample Module 0 interrupt Disabled.
<br>
1 = Sample Module 0 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>SPLIE1</td><td><div style="word-wrap: break-word;"><b>Sample Module 1 Interrupt Enable Bit
</b><br>
0 = Sample Module 1 interrupt Disabled.
<br>
1 = Sample Module 1 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>SPLIE2</td><td><div style="word-wrap: break-word;"><b>Sample Module 2 Interrupt Enable Bit
</b><br>
0 = Sample Module 2 interrupt Disabled.
<br>
1 = Sample Module 2 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>SPLIE3</td><td><div style="word-wrap: break-word;"><b>Sample Module 3 Interrupt Enable Bit
</b><br>
0 = Sample Module 3 interrupt Disabled.
<br>
1 = Sample Module 3 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>SPLIE4</td><td><div style="word-wrap: break-word;"><b>Sample Module 4 Interrupt Enable Bit
</b><br>
0 = Sample Module 4 interrupt Disabled.
<br>
1 = Sample Module 4 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[5]</td><td>SPLIE5</td><td><div style="word-wrap: break-word;"><b>Sample Module 5 Interrupt Enable Bit
</b><br>
0 = Sample Module 5 interrupt Disabled.
<br>
1 = Sample Module 5 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>SPLIE6</td><td><div style="word-wrap: break-word;"><b>Sample Module 6 Interrupt Enable Bit
</b><br>
0 = Sample Module 6 interrupt Disabled.
<br>
1 = Sample Module 6 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[7]</td><td>SPLIE7</td><td><div style="word-wrap: break-word;"><b>Sample Module 7 Interrupt Enable Bit
</b><br>
0 = Sample Module 7 interrupt Disabled.
<br>
1 = Sample Module 7 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>SPLIE8</td><td><div style="word-wrap: break-word;"><b>Sample Module 8 Interrupt Enable Bit
</b><br>
0 = Sample Module 8 interrupt Disabled.
<br>
1 = Sample Module 8 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[9]</td><td>SPLIE9</td><td><div style="word-wrap: break-word;"><b>Sample Module 9 Interrupt Enable Bit
</b><br>
0 = Sample Module 9 interrupt Disabled.
<br>
1 = Sample Module 9 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[10]</td><td>SPLIE10</td><td><div style="word-wrap: break-word;"><b>Sample Module 10 Interrupt Enable Bit
</b><br>
0 = Sample Module 10 interrupt Disabled.
<br>
1 = Sample Module 10 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[11]</td><td>SPLIE11</td><td><div style="word-wrap: break-word;"><b>Sample Module 11 Interrupt Enable Bit
</b><br>
0 = Sample Module 11 interrupt Disabled.
<br>
1 = Sample Module 11 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[12]</td><td>SPLIE12</td><td><div style="word-wrap: break-word;"><b>Sample Module 12 Interrupt Enable Bit
</b><br>
0 = Sample Module 12 interrupt Disabled.
<br>
1 = Sample Module 12 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[13]</td><td>SPLIE13</td><td><div style="word-wrap: break-word;"><b>Sample Module 13 Interrupt Enable Bit
</b><br>
0 = Sample Module 13 interrupt Disabled.
<br>
1 = Sample Module 13 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[14]</td><td>SPLIE14</td><td><div style="word-wrap: break-word;"><b>Sample Module 14 Interrupt Enable Bit
</b><br>
0 = Sample Module 14 interrupt Disabled.
<br>
1 = Sample Module 14 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[15]</td><td>SPLIE15</td><td><div style="word-wrap: break-word;"><b>Sample Module 15 Interrupt Enable Bit
</b><br>
0 = Sample Module 15 interrupt Disabled.
<br>
1 = Sample Module 15 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[16]</td><td>SPLIE16</td><td><div style="word-wrap: break-word;"><b>Sample Module 16 Interrupt Enable Bit
</b><br>
0 = Sample Module 16 interrupt Disabled.
<br>
1 = Sample Module 16 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[17]</td><td>SPLIE17</td><td><div style="word-wrap: break-word;"><b>Sample Module 17 Interrupt Enable Bit
</b><br>
0 = Sample Module 17 interrupt Disabled.
<br>
1 = Sample Module 17 interrupt Enabled.
<br>
</div></td></tr><tr><td>
[18]</td><td>SPLIE18</td><td><div style="word-wrap: break-word;"><b>Sample Module 18 Interrupt Enable Bit
</b><br>
0 = Sample Module 18 interrupt Disabled.
<br>
1 = Sample Module 18 interrupt Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EADC_T::CMP[4]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CMP[4]
</font><br><p> <font size="2">
Offset: 0xE0  ADC Result Compare Register 0~3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ADCMPEN</td><td><div style="word-wrap: break-word;"><b>ADC Result Compare Enable Bit
</b><br>
0 = Compare Disabled.
<br>
1 = Compare Enabled.
<br>
Set this bit to 1 to enable compare CMPDAT (EADC_CMPn[27:16], n=0~3) with specified sample module conversion result when converted data is loaded into EADC_DAT register.
<br>
</div></td></tr><tr><td>
[1]</td><td>ADCMPIE</td><td><div style="word-wrap: break-word;"><b>ADC Result Compare Interrupt Enable Bit
</b><br>
0 = Compare function interrupt Disabled.
<br>
1 = Compare function interrupt Enabled.
<br>
If the compare function is enabled and the compare condition matches the setting of CMPCOND (EADC_CMPn[2], n=0~3) and CMPMCNT (EADC_CMPn[11:8], n=0~3), ADCMPFn (EADC_STATUS2[7:4], n=0~3) will be asserted, in the meanwhile, if ADCMPIE is set to 1, a compare interrupt request is generated.
<br>
</div></td></tr><tr><td>
[2]</td><td>CMPCOND</td><td><div style="word-wrap: break-word;"><b>Compare Condition
</b><br>
0= Set the compare condition as that when a 12-bit ADC conversion result is less than the 12-bit CMPDAT (EADC_CMPn [27:16]), the internal match counter will increase one.
<br>
1= Set the compare condition as that when a 12-bit ADC conversion result is greater or equal to the 12-bit CMPDAT (EADC_CMPn [27:16]), the internal match counter will increase one.
<br>
Note: When the internal counter reaches the value to (CMPMCNT (EADC_CMPn[11:8], n=0~3) +1), the CMPF bit will be set.
<br>
</div></td></tr><tr><td>
[7:3]</td><td>CMPSPL</td><td><div style="word-wrap: break-word;"><b>Compare Sample Module Selection
</b><br>
00000 = Sample Module 0 conversion result EADC_DAT0 is selected to be compared.
<br>
00001 = Sample Module 1 conversion result EADC_DAT1 is selected to be compared.
<br>
00010 = Sample Module 2 conversion result EADC_DAT2 is selected to be compared.
<br>
00011 = Sample Module 3 conversion result EADC_DAT3 is selected to be compared.
<br>
00100 = Sample Module 4 conversion result EADC_DAT4 is selected to be compared.
<br>
00101 = Sample Module 5 conversion result EADC_DAT5 is selected to be compared.
<br>
00110 = Sample Module 6 conversion result EADC_DAT6 is selected to be compared.
<br>
00111 = Sample Module 7 conversion result EADC_DAT7 is selected to be compared.
<br>
01000 = Sample Module 8 conversion result EADC_DAT8 is selected to be compared.
<br>
01001 = Sample Module 9 conversion result EADC_DAT9 is selected to be compared.
<br>
01010 = Sample Module 10 conversion result EADC_DAT10 is selected to be compared.
<br>
01011 = Sample Module 11 conversion result EADC_DAT11 is selected to be compared.
<br>
01100 = Sample Module 12 conversion result EADC_DAT12 is selected to be compared.
<br>
01101 = Sample Module 13 conversion result EADC_DAT13 is selected to be compared.
<br>
01110 = Sample Module 14 conversion result EADC_DAT14 is selected to be compared.
<br>
01111 = Sample Module 15 conversion result EADC_DAT15 is selected to be compared.
<br>
10000 = Sample Module 16 conversion result EADC_DAT16 is selected to be compared.
<br>
10001 = Sample Module 17 conversion result EADC_DAT17 is selected to be compared.
<br>
10010 = Sample Module 18 conversion result EADC_DAT18 is selected to be compared.
<br>
</div></td></tr><tr><td>
[11:8]</td><td>CMPMCNT</td><td><div style="word-wrap: break-word;"><b>Compare Match Count
</b><br>
When the specified ADC sample module analog conversion result matches the compare condition defined by CMPCOND (EADC_CMPn[2], n=0~3), the internal match counter will increase 1
<br>
If the compare result does not meet the compare condition, the internal compare match counter will reset to 0
<br>
When the internal counter reaches the value to (CMPMCNT +1), the ADCMPFn (EADC_STATUS2[7:4], n=0~3) will be set.
<br>
</div></td></tr><tr><td>
[15]</td><td>CMPWEN</td><td><div style="word-wrap: break-word;"><b>Compare Window Mode Enable Bit
</b><br>
0 = ADCMPF0 (EADC_STATUS2[4]) will be set when EADC_CMP0 compared condition matched
<br>
ADCMPF2 (EADC_STATUS2[6]) will be set when EADC_CMP2 compared condition matched
<br>
1 = ADCMPF0 (EADC_STATUS2[4]) will be set when both EADC_CMP0 and EADC_CMP1 compared condition matched
<br>
ADCMPF2 (EADC_STATUS2[6]) will be set when both EADC_CMP2 and EADC_CMP3 compared condition matched.
<br>
Note: This bit is only present in EADC_CMP0 and EADC_CMP2 register.
<br>
</div></td></tr><tr><td>
[27:16]</td><td>CMPDAT</td><td><div style="word-wrap: break-word;"><b>Comparison Data
</b><br>
The 12 bits data is used to compare with conversion result of specified sample module
<br>
User can use it to monitor the external analog input pin voltage transition without imposing a load on software.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EADC_T::STATUS0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STATUS0
</font><br><p> <font size="2">
Offset: 0xF0  ADC Status Register 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>VALID</td><td><div style="word-wrap: break-word;"><b>EADC_DAT0~15 Data Valid Flag
</b><br>
It is a mirror of VALID bit in sample module ADC result data register EADC_DATn. (n=0~18).
<br>
</div></td></tr><tr><td>
[31:16]</td><td>OV</td><td><div style="word-wrap: break-word;"><b>EADC_DAT0~15 Overrun Flag
</b><br>
It is a mirror to OV bit in sample module ADC result data register EADC_DATn. (n=0~18).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EADC_T::STATUS1

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STATUS1
</font><br><p> <font size="2">
Offset: 0xF4  ADC Status Register 1
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[2:0]</td><td>VALID</td><td><div style="word-wrap: break-word;"><b>EADC_DAT16~18 Data Valid Flag
</b><br>
It is a mirror of VALID bit in sample module ADC result data register EADC_DATn. (n=0~18).
<br>
</div></td></tr><tr><td>
[18:16]</td><td>OV</td><td><div style="word-wrap: break-word;"><b>EADC_DAT16~18 Overrun Flag
</b><br>
It is a mirror to OV bit in sample module ADC result data register EADC_DATn. (n=0~18).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EADC_T::STATUS2

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STATUS2
</font><br><p> <font size="2">
Offset: 0xF8  ADC Status Register 2
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>ADIF0</td><td><div style="word-wrap: break-word;"><b>ADC ADINT0 Interrupt Flag
</b><br>
0 = No ADINT0 interrupt pulse received.
<br>
1 = ADINT0 interrupt pulse has been received.
<br>
Note1: This bit is cleared by writing 1 to it.
<br>
Note2:This bit indicates whether an ADC conversion of specific sample module has been completed
<br>
</div></td></tr><tr><td>
[1]</td><td>ADIF1</td><td><div style="word-wrap: break-word;"><b>ADC ADINT1 Interrupt Flag
</b><br>
0 = No ADINT1 interrupt pulse received.
<br>
1 = ADINT1 interrupt pulse has been received.
<br>
Note1: This bit is cleared by writing 1 to it.
<br>
Note2:This bit indicates whether an ADC conversion of specific sample module has been completed
<br>
</div></td></tr><tr><td>
[2]</td><td>ADIF2</td><td><div style="word-wrap: break-word;"><b>ADC ADINT2 Interrupt Flag
</b><br>
0 = No ADINT2 interrupt pulse received.
<br>
1 = ADINT2 interrupt pulse has been received.
<br>
Note1: This bit is cleared by writing 1 to it.
<br>
Note2:This bit indicates whether an ADC conversion of specific sample module has been completed
<br>
</div></td></tr><tr><td>
[3]</td><td>ADIF3</td><td><div style="word-wrap: break-word;"><b>ADC ADINT3 Interrupt Flag
</b><br>
0 = No ADINT3 interrupt pulse received.
<br>
1 = ADINT3 interrupt pulse has been received.
<br>
Note1: This bit is cleared by writing 1 to it.
<br>
Note2:This bit indicates whether an ADC conversion of specific sample module has been completed
<br>
</div></td></tr><tr><td>
[4]</td><td>ADCMPF0</td><td><div style="word-wrap: break-word;"><b>ADC Compare 0 Flag
</b><br>
When the specific sample module ADC conversion result meets setting condition in EADC_CMP0 then this bit is set to 1.
<br>
0 = Conversion result in EADC_DAT does not meet EADC_CMP0 register setting.
<br>
1 = Conversion result in EADC_DAT meets EADC_CMP0 register setting.
<br>
Note: This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[5]</td><td>ADCMPF1</td><td><div style="word-wrap: break-word;"><b>ADC Compare 1 Flag
</b><br>
When the specific sample module ADC conversion result meets setting condition in EADC_CMP1 then this bit is set to 1.
<br>
0 = Conversion result in EADC_DAT does not meet EADC_CMP1 register setting.
<br>
1 = Conversion result in EADC_DAT meets EADC_CMP1 register setting.
<br>
Note: This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[6]</td><td>ADCMPF2</td><td><div style="word-wrap: break-word;"><b>ADC Compare 2 Flag
</b><br>
When the specific sample module ADC conversion result meets setting condition in EADC_CMP2 then this bit is set to 1.
<br>
0 = Conversion result in EADC_DAT does not meet EADC_CMP2 register setting.
<br>
1 = Conversion result in EADC_DAT meets EADC_CMP2 register setting.
<br>
Note: This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[7]</td><td>ADCMPF3</td><td><div style="word-wrap: break-word;"><b>ADC Compare 3 Flag
</b><br>
When the specific sample module ADC conversion result meets setting condition in EADC_CMP3 then this bit is set to 1.
<br>
0 = Conversion result in EADC_DAT does not meet EADC_CMP3 register setting.
<br>
1 = Conversion result in EADC_DAT meets EADC_CMP3 register setting.
<br>
Note: This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[8]</td><td>ADOVIF0</td><td><div style="word-wrap: break-word;"><b>ADC ADINT0 Interrupt Flag Overrun
</b><br>
0 = ADINT0 interrupt flag is not overwritten to 1.
<br>
1 = ADINT0 interrupt flag is overwritten to 1.
<br>
Note: This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[9]</td><td>ADOVIF1</td><td><div style="word-wrap: break-word;"><b>ADC ADINT1 Interrupt Flag Overrun
</b><br>
0 = ADINT1 interrupt flag is not overwritten to 1.
<br>
1 = ADINT1 interrupt flag is overwritten to 1.
<br>
Note: This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[10]</td><td>ADOVIF2</td><td><div style="word-wrap: break-word;"><b>ADC ADINT2 Interrupt Flag Overrun
</b><br>
0 = ADINT2 interrupt flag is not overwritten to 1.
<br>
1 = ADINT2 interrupt flag is s overwritten to 1.
<br>
Note: This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[11]</td><td>ADOVIF3</td><td><div style="word-wrap: break-word;"><b>ADC ADINT3 Interrupt Flag Overrun
</b><br>
0 = ADINT3 interrupt flag is not overwritten to 1.
<br>
1 = ADINT3 interrupt flag is overwritten to 1.
<br>
Note: This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[12]</td><td>ADCMPO0</td><td><div style="word-wrap: break-word;"><b>ADC Compare 0 Output Status (Read Only)
</b><br>
The 12 bits compare0 data CMPDAT0 (EADC_CMP0[27:16]) is used to compare with conversion result of specified sample module
<br>
User can use it to monitor the external analog input pin voltage status.
<br>
0 = Conversion result in EADC_DAT less than CMPDAT0 setting.
<br>
1 = Conversion result in EADC_DAT great than or equal CMPDAT0 setting.
<br>
</div></td></tr><tr><td>
[13]</td><td>ADCMPO1</td><td><div style="word-wrap: break-word;"><b>ADC Compare 1 Output Status (Read Only)
</b><br>
The 12 bits compare1 data CMPDAT1 (EADC_CMP1[27:16]) is used to compare with conversion result of specified sample module
<br>
User can use it to monitor the external analog input pin voltage status.
<br>
0 = Conversion result in EADC_DAT less than CMPDAT1 setting.
<br>
1 = Conversion result in EADC_DAT great than or equal CMPDAT1 setting.
<br>
</div></td></tr><tr><td>
[14]</td><td>ADCMPO2</td><td><div style="word-wrap: break-word;"><b>ADC Compare 2 Output Status (Read Only)
</b><br>
The 12 bits compare2 data CMPDAT2 (EADC_CMP2[27:16]) is used to compare with conversion result of specified sample module
<br>
User can use it to monitor the external analog input pin voltage status.
<br>
0 = Conversion result in EADC_DAT less than CMPDAT2 setting.
<br>
1 = Conversion result in EADC_DAT great than or equal CMPDAT2 setting.
<br>
</div></td></tr><tr><td>
[15]</td><td>ADCMPO3</td><td><div style="word-wrap: break-word;"><b>ADC Compare 3 Output Status (Read Only)
</b><br>
The 12 bits compare3 data CMPDAT3 (EADC_CMP3[27:16]) is used to compare with conversion result of specified sample module
<br>
User can use it to monitor the external analog input pin voltage status.
<br>
0 = Conversion result in EADC_DAT less than CMPDAT3 setting.
<br>
1 = Conversion result in EADC_DAT great than or equal CMPDAT3 setting.
<br>
</div></td></tr><tr><td>
[20:16]</td><td>CHANNEL</td><td><div style="word-wrap: break-word;"><b>Current Conversion Channel (Read Only)
</b><br>
This filed reflects ADC current conversion channel when BUSY=1.
<br>
It is read only.
<br>
00H = EADC_CH0.
<br>
01H = EADC_CH1.
<br>
02H = EADC_CH2.
<br>
03H = EADC_CH3.
<br>
04H = EADC_CH4.
<br>
05H = EADC_CH5.
<br>
06H = EADC_CH6.
<br>
07H = EADC_CH7.
<br>
08H = EADC_CH8.
<br>
09H = EADC_CH9.
<br>
0AH = EADC_CH10.
<br>
0BH = EADC_CH11.
<br>
0CH = EADC_CH12.
<br>
0DH = EADC_CH13.
<br>
0EH = EADC_CH14.
<br>
0FH = EADC_CH15.
<br>
10H = VBG.
<br>
11H = VTEMP.
<br>
12H = VBAT/4.
<br>
</div></td></tr><tr><td>
[23]</td><td>BUSY</td><td><div style="word-wrap: break-word;"><b>Busy/Idle (Read Only)
</b><br>
0 = EADC is in idle state.
<br>
1 = EADC is busy at conversion.
<br>
</div></td></tr><tr><td>
[24]</td><td>ADOVIF</td><td><div style="word-wrap: break-word;"><b>All ADC Interrupt Flag Overrun Bits Check (Read Only)
</b><br>
n=0~3.
<br>
0 = None of ADINT interrupt flag ADOVIFn (EADC_STATUS2[11:8]) is overwritten to 1.
<br>
1 = Any one of ADINT interrupt flag ADOVIFn (EADC_STATUS2[11:8]) is overwritten to 1.
<br>
Note: This bit will keep 1 when any ADOVIFn Flag is equal to 1.
<br>
</div></td></tr><tr><td>
[25]</td><td>STOVF</td><td><div style="word-wrap: break-word;"><b>for All ADC Sample Module Start of Conversion Overrun Flags Check (Read Only)
</b><br>
n=0~18.
<br>
0 = None of sample module event overrun flag SPOVFn (EADC_OVSTS[n]) is set to 1.
<br>
1 = Any one of sample module event overrun flag SPOVFn (EADC_OVSTS[n]) is set to 1.
<br>
Note: This bit will keep 1 when any SPOVFn Flag is equal to 1.
<br>
</div></td></tr><tr><td>
[26]</td><td>AVALID</td><td><div style="word-wrap: break-word;"><b>for All Sample Module ADC Result Data Register EADC_DAT Data Valid Flag Check (Read Only)
</b><br>
n=0~18.
<br>
0 = None of sample module data register valid flag VALIDn (EADC_DATn[17]) is set to 1.
<br>
1 = Any one of sample module data register valid flag VALIDn (EADC_DATn[17]) is set to 1.
<br>
Note: This bit will keep 1 when any VALIDn Flag is equal to 1.
<br>
</div></td></tr><tr><td>
[27]</td><td>AOV</td><td><div style="word-wrap: break-word;"><b>for All Sample Module ADC Result Data Register Overrun Flags Check (Read Only)
</b><br>
n=0~18.
<br>
0 = None of sample module data register overrun flag OVn (EADC_DATn[16]) is set to 1.
<br>
1 = Any one of sample module data register overrun flag OVn (EADC_DATn[16]) is set to 1.
<br>
Note: This bit will keep 1 when any OVn Flag is equal to 1.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EADC_T::STATUS3

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STATUS3
</font><br><p> <font size="2">
Offset: 0xFC  ADC Status Register 3
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[4:0]</td><td>CURSPL</td><td><div style="word-wrap: break-word;"><b>ADC Current Sample Module
</b><br>
This register show the current ADC is controlled by which sample module control logic modules.
<br>
If the ADC is Idle, this bit filed will set to 0x1F.
<br>
This is a read only register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EADC_T::DDAT[4]

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DDAT[4]
</font><br><p> <font size="2">
Offset: 0x100  ADC Double Data Register 0 for Sample Module 0
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>RESULT</td><td><div style="word-wrap: break-word;"><b>ADC Conversion Results
</b><br>
This field contains 12 bits conversion results.
<br>
When the DMOF (EADC_CTL[9]) is set to 0, 12-bit ADC conversion result with unsigned format will be filled in RESULT [11:0] and zero will be filled in RESULT [15:12].
<br>
When DMOF (EADC_CTL[9]) set to 1, 12-bit ADC conversion result with 2'complement format will be filled in RESULT [11:0] and signed bits to will be filled in RESULT [15:12].
<br>
</div></td></tr><tr><td>
[16]</td><td>OV</td><td><div style="word-wrap: break-word;"><b>Overrun Flag
</b><br>
0 = Data in RESULT (EADC_DATn[15:0], n=0~3) is recent conversion result.
<br>
1 = Data in RESULT (EADC_DATn[15:0], n=0~3) is overwrite.
<br>
If converted data in RESULT[15:0] has not been read before new conversion result is loaded to this register, OV is set to 1
<br>
It is cleared by hardware after EADC_DDAT register is read.
<br>
</div></td></tr><tr><td>
[17]</td><td>VALID</td><td><div style="word-wrap: break-word;"><b>Valid Flag
</b><br>
0 = Double data in RESULT (EADC_DDATn[15:0]) is not valid.
<br>
1 = Double data in RESULT (EADC_DDATn[15:0]) is valid.
<br>
This bit is set to 1 when corresponding sample module channel analog input conversion is completed and cleared by hardware after EADC_DDATn register is read
<br>
(n=0~3).
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EADC_T::PWRM

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PWRM
</font><br><p> <font size="2">
Offset: 0x110  ADC Power Management Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>PWUPRDY</td><td><div style="word-wrap: break-word;"><b>ADC Power-up Sequence Completed and Ready for Conversion (Read Only)
</b><br>
0 = ADC is not ready for conversion may be in power down state or in the progress of start up.
<br>
1 = ADC is ready for conversion.
<br>
</div></td></tr><tr><td>
[1]</td><td>PWUCALEN</td><td><div style="word-wrap: break-word;"><b>Power Up Calibration Function Enable Control
</b><br>
0 = Disable the function of calibration at power up.
<br>
1 = Enable the function of calibration at power up.
<br>
Note: This bit work together with CALSEL (EADC_CALCTL [3]), see the following
<br>
{PWUCALEN, CALSEL } Description:
<br>
PWUCALEN is 0 and CALSEL is 0: No need to calibrate.
<br>
PWUCALEN is 0 and CALSEL is 1: No need to calibrate.
<br>
PWUCALEN is 1 and CALSEL is 0: Load calibration word when power up.
<br>
PWUCALEN is 1 and CALSEL is 1: Calibrate when power up.
<br>
</div></td></tr><tr><td>
[3:2]</td><td>PWDMOD</td><td><div style="word-wrap: break-word;"><b>ADC Power-down Mode
</b><br>
Set this bit fields to select ADC power down mode when system power-down.
<br>
00 = ADC Deep power down mode.
<br>
01 = ADC Power down.
<br>
10 = ADC Standby mode.
<br>
11 = ADC Deep power down mode.
<br>
Note: Different PWDMOD has different power down/up sequence, in order to avoid ADC powering up with wrong sequence; user must keep PWMOD consistent each time in power down and start up
<br>
</div></td></tr><tr><td>
[19:8]</td><td>LDOSUT</td><td><div style="word-wrap: break-word;"><b>ADC Internal LDO Start-up Time
</b><br>
Set this bit fields to control LDO start-up time
<br>
The minimum required LDO start-up time is 20us
<br>
LDO start-up time = (1/ADC_CLK) x LDOSUT.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EADC_T::CALCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CALCTL
</font><br><p> <font size="2">
Offset: 0x114  ADC Calibration Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1]</td><td>CALSTART</td><td><div style="word-wrap: break-word;"><b>Calibration Functional Block Start
</b><br>
0 = Stops calibration functional block.
<br>
1 = Starts calibration functional block.
<br>
Note: This bit is set by SW and clear by HW after re-calibration finish
<br>
</div></td></tr><tr><td>
[2]</td><td>CALDONE</td><td><div style="word-wrap: break-word;"><b>Calibration Functional Block Complete (Read Only)
</b><br>
0 = During a calibration.
<br>
1 = Calibration is completed.
<br>
</div></td></tr><tr><td>
[3]</td><td>CALSEL</td><td><div style="word-wrap: break-word;"><b>Select Calibration Functional Block
</b><br>
0 = Load calibration word when calibration functional block is active.
<br>
1 = Execute calibration when calibration functional block is active.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var EADC_T::CALDWRD

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CALDWRD
</font><br><p> <font size="2">
Offset: 0x118  ADC Calibration Load Word Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[6:0]</td><td>CALWORD</td><td><div style="word-wrap: break-word;"><b>Calibration Word Bits
</b><br>
Write to this register with the previous calibration word before load calibration action.
<br>
Read this register after calibration done.
<br>
Note: The calibration block contains two parts CALIBRATION and LOAD CALIBRATION; if the calibration block configure as CALIBRATION; then this register represent the result of calibration when calibration is completed; if configure as LOAD CALIBRATION ; configure this register before loading calibration action, after loading calibration complete, the laoded calibration word will apply to the ADC; while in loading calibration function the loaded value will not be equal to the original CALWORD until calibration is done.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __I  uint32_t DAT[19];               /*!< [0x0000] ADC Data Register 0~18 for Sample Module 0~18                    */
    __I  uint32_t CURDAT;                /*!< [0x004c] ADC PDMA Current Transfer Data Register                          */
    __IO uint32_t CTL;                   /*!< [0x0050] ADC Control Register                                             */
    __O  uint32_t SWTRG;                 /*!< [0x0054] ADC Sample Module Software Start Register                        */
    __IO uint32_t PENDSTS;               /*!< [0x0058] ADC Start of Conversion Pending Flag Register                    */
    __IO uint32_t OVSTS;                 /*!< [0x005c] ADC Sample Module Start of Conversion Overrun Flag Register      */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE0[8];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t SCTL[19];              /*!< [0x0080] ADC Sample Module 0~18 Control Register                          */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE1[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t INTSRC[4];             /*!< [0x00d0] ADC interrupt 0~3 Source Enable Control Register.                */
    __IO uint32_t CMP[4];                /*!< [0x00e0] ADC Result Compare Register 0~3                                  */
    __I  uint32_t STATUS0;               /*!< [0x00f0] ADC Status Register 0                                            */
    __I  uint32_t STATUS1;               /*!< [0x00f4] ADC Status Register 1                                            */
    __IO uint32_t STATUS2;               /*!< [0x00f8] ADC Status Register 2                                            */
    __I  uint32_t STATUS3;               /*!< [0x00fc] ADC Status Register 3                                            */
    __I  uint32_t DDAT[4];               /*!< [0x0100] ADC Double Data Register 0~3 for Sample Module 0~3               */
    __IO uint32_t PWRM;                  /*!< [0x0110] ADC Power Management Register                                    */
    __IO uint32_t CALCTL;                /*!< [0x0114] ADC Calibration Control Register                                 */
    __IO uint32_t CALDWRD;               /*!< [0x0118] ADC Calibration Load Word Register                               */
    /// @cond HIDDEN_SYMBOLS
    __I  uint32_t RESERVE2[5];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t PDMACTL;               /*!< [0x0130] ADC PDMA Control Register                                        */
} EADC_T;

/**
    @addtogroup EADC_CONST EADC Bit Field Definition
    Constant Definitions for EADC Controller
@{ */

#define EADC_DAT_RESULT_Pos              (0)                                                /*!< EADC_T::DAT: RESULT Position          */
#define EADC_DAT_RESULT_Msk              (0xfffful << EADC_DAT_RESULT_Pos)                  /*!< EADC_T::DAT: RESULT Mask              */

#define EADC_DAT_OV_Pos                  (16)                                               /*!< EADC_T::DAT: OV Position              */
#define EADC_DAT_OV_Msk                  (0x1ul << EADC_DAT_OV_Pos)                         /*!< EADC_T::DAT: OV Mask                  */

#define EADC_DAT_VALID_Pos               (17)                                               /*!< EADC_T::DAT: VALID Position           */
#define EADC_DAT_VALID_Msk               (0x1ul << EADC_DAT_VALID_Pos)                      /*!< EADC_T::DAT: VALID Mask               */

#define EADC_DAT0_RESULT_Pos             (0)                                               /*!< EADC_T::DAT0: RESULT Position          */
#define EADC_DAT0_RESULT_Msk             (0xfffful << EADC_DAT0_RESULT_Pos)                /*!< EADC_T::DAT0: RESULT Mask              */

#define EADC_DAT0_OV_Pos                 (16)                                              /*!< EADC_T::DAT0: OV Position              */
#define EADC_DAT0_OV_Msk                 (0x1ul << EADC_DAT0_OV_Pos)                       /*!< EADC_T::DAT0: OV Mask                  */

#define EADC_DAT0_VALID_Pos              (17)                                              /*!< EADC_T::DAT0: VALID Position           */
#define EADC_DAT0_VALID_Msk              (0x1ul << EADC_DAT0_VALID_Pos)                    /*!< EADC_T::DAT0: VALID Mask               */

#define EADC_DAT1_RESULT_Pos             (0)                                               /*!< EADC_T::DAT1: RESULT Position          */
#define EADC_DAT1_RESULT_Msk             (0xfffful << EADC_DAT1_RESULT_Pos)                /*!< EADC_T::DAT1: RESULT Mask              */

#define EADC_DAT1_OV_Pos                 (16)                                              /*!< EADC_T::DAT1: OV Position              */
#define EADC_DAT1_OV_Msk                 (0x1ul << EADC_DAT1_OV_Pos)                       /*!< EADC_T::DAT1: OV Mask                  */

#define EADC_DAT1_VALID_Pos              (17)                                              /*!< EADC_T::DAT1: VALID Position           */
#define EADC_DAT1_VALID_Msk              (0x1ul << EADC_DAT1_VALID_Pos)                    /*!< EADC_T::DAT1: VALID Mask               */

#define EADC_DAT2_RESULT_Pos             (0)                                               /*!< EADC_T::DAT2: RESULT Position          */
#define EADC_DAT2_RESULT_Msk             (0xfffful << EADC_DAT2_RESULT_Pos)                /*!< EADC_T::DAT2: RESULT Mask              */

#define EADC_DAT2_OV_Pos                 (16)                                              /*!< EADC_T::DAT2: OV Position              */
#define EADC_DAT2_OV_Msk                 (0x1ul << EADC_DAT2_OV_Pos)                       /*!< EADC_T::DAT2: OV Mask                  */

#define EADC_DAT2_VALID_Pos              (17)                                              /*!< EADC_T::DAT2: VALID Position           */
#define EADC_DAT2_VALID_Msk              (0x1ul << EADC_DAT2_VALID_Pos)                    /*!< EADC_T::DAT2: VALID Mask               */

#define EADC_DAT3_RESULT_Pos             (0)                                               /*!< EADC_T::DAT3: RESULT Position          */
#define EADC_DAT3_RESULT_Msk             (0xfffful << EADC_DAT3_RESULT_Pos)                /*!< EADC_T::DAT3: RESULT Mask              */

#define EADC_DAT3_OV_Pos                 (16)                                              /*!< EADC_T::DAT3: OV Position              */
#define EADC_DAT3_OV_Msk                 (0x1ul << EADC_DAT3_OV_Pos)                       /*!< EADC_T::DAT3: OV Mask                  */

#define EADC_DAT3_VALID_Pos              (17)                                              /*!< EADC_T::DAT3: VALID Position           */
#define EADC_DAT3_VALID_Msk              (0x1ul << EADC_DAT3_VALID_Pos)                    /*!< EADC_T::DAT3: VALID Mask               */

#define EADC_DAT4_RESULT_Pos             (0)                                               /*!< EADC_T::DAT4: RESULT Position          */
#define EADC_DAT4_RESULT_Msk             (0xfffful << EADC_DAT4_RESULT_Pos)                /*!< EADC_T::DAT4: RESULT Mask              */

#define EADC_DAT4_OV_Pos                 (16)                                              /*!< EADC_T::DAT4: OV Position              */
#define EADC_DAT4_OV_Msk                 (0x1ul << EADC_DAT4_OV_Pos)                       /*!< EADC_T::DAT4: OV Mask                  */

#define EADC_DAT4_VALID_Pos              (17)                                              /*!< EADC_T::DAT4: VALID Position           */
#define EADC_DAT4_VALID_Msk              (0x1ul << EADC_DAT4_VALID_Pos)                    /*!< EADC_T::DAT4: VALID Mask               */

#define EADC_DAT5_RESULT_Pos             (0)                                               /*!< EADC_T::DAT5: RESULT Position          */
#define EADC_DAT5_RESULT_Msk             (0xfffful << EADC_DAT5_RESULT_Pos)                /*!< EADC_T::DAT5: RESULT Mask              */

#define EADC_DAT5_OV_Pos                 (16)                                              /*!< EADC_T::DAT5: OV Position              */
#define EADC_DAT5_OV_Msk                 (0x1ul << EADC_DAT5_OV_Pos)                       /*!< EADC_T::DAT5: OV Mask                  */

#define EADC_DAT5_VALID_Pos              (17)                                              /*!< EADC_T::DAT5: VALID Position           */
#define EADC_DAT5_VALID_Msk              (0x1ul << EADC_DAT5_VALID_Pos)                    /*!< EADC_T::DAT5: VALID Mask               */

#define EADC_DAT6_RESULT_Pos             (0)                                               /*!< EADC_T::DAT6: RESULT Position          */
#define EADC_DAT6_RESULT_Msk             (0xfffful << EADC_DAT6_RESULT_Pos)                /*!< EADC_T::DAT6: RESULT Mask              */

#define EADC_DAT6_OV_Pos                 (16)                                              /*!< EADC_T::DAT6: OV Position              */
#define EADC_DAT6_OV_Msk                 (0x1ul << EADC_DAT6_OV_Pos)                       /*!< EADC_T::DAT6: OV Mask                  */

#define EADC_DAT6_VALID_Pos              (17)                                              /*!< EADC_T::DAT6: VALID Position           */
#define EADC_DAT6_VALID_Msk              (0x1ul << EADC_DAT6_VALID_Pos)                    /*!< EADC_T::DAT6: VALID Mask               */

#define EADC_DAT7_RESULT_Pos             (0)                                               /*!< EADC_T::DAT7: RESULT Position          */
#define EADC_DAT7_RESULT_Msk             (0xfffful << EADC_DAT7_RESULT_Pos)                /*!< EADC_T::DAT7: RESULT Mask              */

#define EADC_DAT7_OV_Pos                 (16)                                              /*!< EADC_T::DAT7: OV Position              */
#define EADC_DAT7_OV_Msk                 (0x1ul << EADC_DAT7_OV_Pos)                       /*!< EADC_T::DAT7: OV Mask                  */

#define EADC_DAT7_VALID_Pos              (17)                                              /*!< EADC_T::DAT7: VALID Position           */
#define EADC_DAT7_VALID_Msk              (0x1ul << EADC_DAT7_VALID_Pos)                    /*!< EADC_T::DAT7: VALID Mask               */

#define EADC_DAT8_RESULT_Pos             (0)                                               /*!< EADC_T::DAT8: RESULT Position          */
#define EADC_DAT8_RESULT_Msk             (0xfffful << EADC_DAT8_RESULT_Pos)                /*!< EADC_T::DAT8: RESULT Mask              */

#define EADC_DAT8_OV_Pos                 (16)                                              /*!< EADC_T::DAT8: OV Position              */
#define EADC_DAT8_OV_Msk                 (0x1ul << EADC_DAT8_OV_Pos)                       /*!< EADC_T::DAT8: OV Mask                  */

#define EADC_DAT8_VALID_Pos              (17)                                              /*!< EADC_T::DAT8: VALID Position           */
#define EADC_DAT8_VALID_Msk              (0x1ul << EADC_DAT8_VALID_Pos)                    /*!< EADC_T::DAT8: VALID Mask               */

#define EADC_DAT9_RESULT_Pos             (0)                                               /*!< EADC_T::DAT9: RESULT Position          */
#define EADC_DAT9_RESULT_Msk             (0xfffful << EADC_DAT9_RESULT_Pos)                /*!< EADC_T::DAT9: RESULT Mask              */

#define EADC_DAT9_OV_Pos                 (16)                                              /*!< EADC_T::DAT9: OV Position              */
#define EADC_DAT9_OV_Msk                 (0x1ul << EADC_DAT9_OV_Pos)                       /*!< EADC_T::DAT9: OV Mask                  */

#define EADC_DAT9_VALID_Pos              (17)                                              /*!< EADC_T::DAT9: VALID Position           */
#define EADC_DAT9_VALID_Msk              (0x1ul << EADC_DAT9_VALID_Pos)                    /*!< EADC_T::DAT9: VALID Mask               */

#define EADC_DAT10_RESULT_Pos            (0)                                               /*!< EADC_T::DAT10: RESULT Position         */
#define EADC_DAT10_RESULT_Msk            (0xfffful << EADC_DAT10_RESULT_Pos)               /*!< EADC_T::DAT10: RESULT Mask             */

#define EADC_DAT10_OV_Pos                (16)                                              /*!< EADC_T::DAT10: OV Position             */
#define EADC_DAT10_OV_Msk                (0x1ul << EADC_DAT10_OV_Pos)                      /*!< EADC_T::DAT10: OV Mask                 */

#define EADC_DAT10_VALID_Pos             (17)                                              /*!< EADC_T::DAT10: VALID Position          */
#define EADC_DAT10_VALID_Msk             (0x1ul << EADC_DAT10_VALID_Pos)                   /*!< EADC_T::DAT10: VALID Mask              */

#define EADC_DAT11_RESULT_Pos            (0)                                               /*!< EADC_T::DAT11: RESULT Position         */
#define EADC_DAT11_RESULT_Msk            (0xfffful << EADC_DAT11_RESULT_Pos)               /*!< EADC_T::DAT11: RESULT Mask             */

#define EADC_DAT11_OV_Pos                (16)                                              /*!< EADC_T::DAT11: OV Position             */
#define EADC_DAT11_OV_Msk                (0x1ul << EADC_DAT11_OV_Pos)                      /*!< EADC_T::DAT11: OV Mask                 */

#define EADC_DAT11_VALID_Pos             (17)                                              /*!< EADC_T::DAT11: VALID Position          */
#define EADC_DAT11_VALID_Msk             (0x1ul << EADC_DAT11_VALID_Pos)                   /*!< EADC_T::DAT11: VALID Mask              */

#define EADC_DAT12_RESULT_Pos            (0)                                               /*!< EADC_T::DAT12: RESULT Position         */
#define EADC_DAT12_RESULT_Msk            (0xfffful << EADC_DAT12_RESULT_Pos)               /*!< EADC_T::DAT12: RESULT Mask             */

#define EADC_DAT12_OV_Pos                (16)                                              /*!< EADC_T::DAT12: OV Position             */
#define EADC_DAT12_OV_Msk                (0x1ul << EADC_DAT12_OV_Pos)                      /*!< EADC_T::DAT12: OV Mask                 */

#define EADC_DAT12_VALID_Pos             (17)                                              /*!< EADC_T::DAT12: VALID Position          */
#define EADC_DAT12_VALID_Msk             (0x1ul << EADC_DAT12_VALID_Pos)                   /*!< EADC_T::DAT12: VALID Mask              */

#define EADC_DAT13_RESULT_Pos            (0)                                               /*!< EADC_T::DAT13: RESULT Position         */
#define EADC_DAT13_RESULT_Msk            (0xfffful << EADC_DAT13_RESULT_Pos)               /*!< EADC_T::DAT13: RESULT Mask             */

#define EADC_DAT13_OV_Pos                (16)                                              /*!< EADC_T::DAT13: OV Position             */
#define EADC_DAT13_OV_Msk                (0x1ul << EADC_DAT13_OV_Pos)                      /*!< EADC_T::DAT13: OV Mask                 */

#define EADC_DAT13_VALID_Pos             (17)                                              /*!< EADC_T::DAT13: VALID Position          */
#define EADC_DAT13_VALID_Msk             (0x1ul << EADC_DAT13_VALID_Pos)                   /*!< EADC_T::DAT13: VALID Mask              */

#define EADC_DAT14_RESULT_Pos            (0)                                               /*!< EADC_T::DAT14: RESULT Position         */
#define EADC_DAT14_RESULT_Msk            (0xfffful << EADC_DAT14_RESULT_Pos)               /*!< EADC_T::DAT14: RESULT Mask             */

#define EADC_DAT14_OV_Pos                (16)                                              /*!< EADC_T::DAT14: OV Position             */
#define EADC_DAT14_OV_Msk                (0x1ul << EADC_DAT14_OV_Pos)                      /*!< EADC_T::DAT14: OV Mask                 */

#define EADC_DAT14_VALID_Pos             (17)                                              /*!< EADC_T::DAT14: VALID Position          */
#define EADC_DAT14_VALID_Msk             (0x1ul << EADC_DAT14_VALID_Pos)                   /*!< EADC_T::DAT14: VALID Mask              */

#define EADC_DAT15_RESULT_Pos            (0)                                               /*!< EADC_T::DAT15: RESULT Position         */
#define EADC_DAT15_RESULT_Msk            (0xfffful << EADC_DAT15_RESULT_Pos)               /*!< EADC_T::DAT15: RESULT Mask             */

#define EADC_DAT15_OV_Pos                (16)                                              /*!< EADC_T::DAT15: OV Position             */
#define EADC_DAT15_OV_Msk                (0x1ul << EADC_DAT15_OV_Pos)                      /*!< EADC_T::DAT15: OV Mask                 */

#define EADC_DAT15_VALID_Pos             (17)                                              /*!< EADC_T::DAT15: VALID Position          */
#define EADC_DAT15_VALID_Msk             (0x1ul << EADC_DAT15_VALID_Pos)                   /*!< EADC_T::DAT15: VALID Mask              */

#define EADC_DAT16_RESULT_Pos            (0)                                               /*!< EADC_T::DAT16: RESULT Position         */
#define EADC_DAT16_RESULT_Msk            (0xfffful << EADC_DAT16_RESULT_Pos)               /*!< EADC_T::DAT16: RESULT Mask             */

#define EADC_DAT16_OV_Pos                (16)                                              /*!< EADC_T::DAT16: OV Position             */
#define EADC_DAT16_OV_Msk                (0x1ul << EADC_DAT16_OV_Pos)                      /*!< EADC_T::DAT16: OV Mask                 */

#define EADC_DAT16_VALID_Pos             (17)                                              /*!< EADC_T::DAT16: VALID Position          */
#define EADC_DAT16_VALID_Msk             (0x1ul << EADC_DAT16_VALID_Pos)                   /*!< EADC_T::DAT16: VALID Mask              */

#define EADC_DAT17_RESULT_Pos            (0)                                               /*!< EADC_T::DAT17: RESULT Position         */
#define EADC_DAT17_RESULT_Msk            (0xfffful << EADC_DAT17_RESULT_Pos)               /*!< EADC_T::DAT17: RESULT Mask             */

#define EADC_DAT17_OV_Pos                (16)                                              /*!< EADC_T::DAT17: OV Position             */
#define EADC_DAT17_OV_Msk                (0x1ul << EADC_DAT17_OV_Pos)                      /*!< EADC_T::DAT17: OV Mask                 */

#define EADC_DAT17_VALID_Pos             (17)                                              /*!< EADC_T::DAT17: VALID Position          */
#define EADC_DAT17_VALID_Msk             (0x1ul << EADC_DAT17_VALID_Pos)                   /*!< EADC_T::DAT17: VALID Mask              */

#define EADC_DAT18_RESULT_Pos            (0)                                               /*!< EADC_T::DAT18: RESULT Position         */
#define EADC_DAT18_RESULT_Msk            (0xfffful << EADC_DAT18_RESULT_Pos)               /*!< EADC_T::DAT18: RESULT Mask             */

#define EADC_DAT18_OV_Pos                (16)                                              /*!< EADC_T::DAT18: OV Position             */
#define EADC_DAT18_OV_Msk                (0x1ul << EADC_DAT18_OV_Pos)                      /*!< EADC_T::DAT18: OV Mask                 */

#define EADC_DAT18_VALID_Pos             (17)                                              /*!< EADC_T::DAT18: VALID Position          */
#define EADC_DAT18_VALID_Msk             (0x1ul << EADC_DAT18_VALID_Pos)                   /*!< EADC_T::DAT18: VALID Mask              */

#define EADC_CURDAT_CURDAT_Pos           (0)                                               /*!< EADC_T::CURDAT: CURDAT Position        */
#define EADC_CURDAT_CURDAT_Msk           (0x3fffful << EADC_CURDAT_CURDAT_Pos)             /*!< EADC_T::CURDAT: CURDAT Mask            */

#define EADC_CTL_ADCEN_Pos               (0)                                               /*!< EADC_T::CTL: ADCEN Position            */
#define EADC_CTL_ADCEN_Msk               (0x1ul << EADC_CTL_ADCEN_Pos)                     /*!< EADC_T::CTL: ADCEN Mask                */

#define EADC_CTL_ADCRST_Pos              (1)                                               /*!< EADC_T::CTL: ADCRST Position           */
#define EADC_CTL_ADCRST_Msk              (0x1ul << EADC_CTL_ADCRST_Pos)                    /*!< EADC_T::CTL: ADCRST Mask               */

#define EADC_CTL_ADCIEN0_Pos             (2)                                               /*!< EADC_T::CTL: ADCIEN0 Position          */
#define EADC_CTL_ADCIEN0_Msk             (0x1ul << EADC_CTL_ADCIEN0_Pos)                   /*!< EADC_T::CTL: ADCIEN0 Mask              */

#define EADC_CTL_ADCIEN1_Pos             (3)                                               /*!< EADC_T::CTL: ADCIEN1 Position          */
#define EADC_CTL_ADCIEN1_Msk             (0x1ul << EADC_CTL_ADCIEN1_Pos)                   /*!< EADC_T::CTL: ADCIEN1 Mask              */

#define EADC_CTL_ADCIEN2_Pos             (4)                                               /*!< EADC_T::CTL: ADCIEN2 Position          */
#define EADC_CTL_ADCIEN2_Msk             (0x1ul << EADC_CTL_ADCIEN2_Pos)                   /*!< EADC_T::CTL: ADCIEN2 Mask              */

#define EADC_CTL_ADCIEN3_Pos             (5)                                               /*!< EADC_T::CTL: ADCIEN3 Position          */
#define EADC_CTL_ADCIEN3_Msk             (0x1ul << EADC_CTL_ADCIEN3_Pos)                   /*!< EADC_T::CTL: ADCIEN3 Mask              */

#define EADC_CTL_RESSEL_Pos              (6)                                               /*!< EADC_T::CTL: RESSEL Position           */
#define EADC_CTL_RESSEL_Msk              (0x3ul << EADC_CTL_RESSEL_Pos)                    /*!< EADC_T::CTL: RESSEL Mask               */

#define EADC_CTL_DIFFEN_Pos              (8)                                               /*!< EADC_T::CTL: DIFFEN Position           */
#define EADC_CTL_DIFFEN_Msk              (0x1ul << EADC_CTL_DIFFEN_Pos)                    /*!< EADC_T::CTL: DIFFEN Mask               */

#define EADC_CTL_DMOF_Pos                (9)                                               /*!< EADC_T::CTL: DMOF Position             */
#define EADC_CTL_DMOF_Msk                (0x1ul << EADC_CTL_DMOF_Pos)                      /*!< EADC_T::CTL: DMOF Mask                 */

#define EADC_CTL_PDMAEN_Pos              (11)                                              /*!< EADC_T::CTL: PDMAEN Position           */
#define EADC_CTL_PDMAEN_Msk              (0x1ul << EADC_CTL_PDMAEN_Pos)                    /*!< EADC_T::CTL: PDMAEN Mask               */

#define EADC_SWTRG_SWTRG_Pos             (0)                                               /*!< EADC_T::SWTRG: SWTRG Position          */
#define EADC_SWTRG_SWTRG_Msk             (0x7fffful << EADC_SWTRG_SWTRG_Pos)               /*!< EADC_T::SWTRG: SWTRG Mask              */

#define EADC_PENDSTS_STPF_Pos            (0)                                               /*!< EADC_T::PENDSTS: STPF Position         */
#define EADC_PENDSTS_STPF_Msk            (0x7fffful << EADC_PENDSTS_STPF_Pos)              /*!< EADC_T::PENDSTS: STPF Mask             */

#define EADC_OVSTS_SPOVF_Pos             (0)                                               /*!< EADC_T::OVSTS: SPOVF Position          */
#define EADC_OVSTS_SPOVF_Msk             (0x7fffful << EADC_OVSTS_SPOVF_Pos)               /*!< EADC_T::OVSTS: SPOVF Mask              */

#define EADC_SCTL_CHSEL_Pos              (0)                                               /*!< EADC_T::SCTL: CHSEL Position           */
#define EADC_SCTL_CHSEL_Msk              (0xful << EADC_SCTL_CHSEL_Pos)                    /*!< EADC_T::SCTL: CHSEL Mask               */

#define EADC_SCTL_EXTREN_Pos             (4)                                               /*!< EADC_T::SCTL: EXTREN Position          */
#define EADC_SCTL_EXTREN_Msk             (0x1ul << EADC_SCTL_EXTREN_Pos)                   /*!< EADC_T::SCTL: EXTREN Mask              */

#define EADC_SCTL_EXTFEN_Pos             (5)                                               /*!< EADC_T::SCTL: EXTFEN Position          */
#define EADC_SCTL_EXTFEN_Msk             (0x1ul << EADC_SCTL_EXTFEN_Pos)                   /*!< EADC_T::SCTL: EXTFEN Mask              */

#define EADC_SCTL_TRGDLYDIV_Pos          (6)                                               /*!< EADC_T::SCTL: TRGDLYDIV Position       */
#define EADC_SCTL_TRGDLYDIV_Msk          (0x3ul << EADC_SCTL_TRGDLYDIV_Pos)                /*!< EADC_T::SCTL: TRGDLYDIV Mask           */

#define EADC_SCTL_TRGDLYCNT_Pos          (8)                                               /*!< EADC_T::SCTL: TRGDLYCNT Position       */
#define EADC_SCTL_TRGDLYCNT_Msk          (0xfful << EADC_SCTL_TRGDLYCNT_Pos)               /*!< EADC_T::SCTL: TRGDLYCNT Mask           */

#define EADC_SCTL_TRGSEL_Pos             (16)                                              /*!< EADC_T::SCTL: TRGSEL Position          */
#define EADC_SCTL_TRGSEL_Msk             (0x1ful << EADC_SCTL_TRGSEL_Pos)                  /*!< EADC_T::SCTL: TRGSEL Mask              */

#define EADC_SCTL_INTPOS_Pos             (22)                                              /*!< EADC_T::SCTL: INTPOS Position          */
#define EADC_SCTL_INTPOS_Msk             (0x1ul << EADC_SCTL_INTPOS_Pos)                   /*!< EADC_T::SCTL: INTPOS Mask              */

#define EADC_SCTL_DBMEN_Pos              (23)                                              /*!< EADC_T::SCTL: DBMEN Position           */
#define EADC_SCTL_DBMEN_Msk              (0x1ul << EADC_SCTL_DBMEN_Pos)                    /*!< EADC_T::SCTL: DBMEN Mask               */

#define EADC_SCTL_EXTSMPT_Pos            (24)                                              /*!< EADC_T::SCTL: EXTSMPT Position         */
#define EADC_SCTL_EXTSMPT_Msk            (0xfful << EADC_SCTL_EXTSMPT_Pos)                 /*!< EADC_T::SCTL: EXTSMPT Mask             */

#define EADC_SCTL0_CHSEL_Pos             (0)                                               /*!< EADC_T::SCTL0: CHSEL Position          */
#define EADC_SCTL0_CHSEL_Msk             (0xful << EADC_SCTL0_CHSEL_Pos)                   /*!< EADC_T::SCTL0: CHSEL Mask              */

#define EADC_SCTL0_EXTREN_Pos            (4)                                               /*!< EADC_T::SCTL0: EXTREN Position         */
#define EADC_SCTL0_EXTREN_Msk            (0x1ul << EADC_SCTL0_EXTREN_Pos)                  /*!< EADC_T::SCTL0: EXTREN Mask             */

#define EADC_SCTL0_EXTFEN_Pos            (5)                                               /*!< EADC_T::SCTL0: EXTFEN Position         */
#define EADC_SCTL0_EXTFEN_Msk            (0x1ul << EADC_SCTL0_EXTFEN_Pos)                  /*!< EADC_T::SCTL0: EXTFEN Mask             */

#define EADC_SCTL0_TRGDLYDIV_Pos         (6)                                               /*!< EADC_T::SCTL0: TRGDLYDIV Position      */
#define EADC_SCTL0_TRGDLYDIV_Msk         (0x3ul << EADC_SCTL0_TRGDLYDIV_Pos)               /*!< EADC_T::SCTL0: TRGDLYDIV Mask          */

#define EADC_SCTL0_TRGDLYCNT_Pos         (8)                                               /*!< EADC_T::SCTL0: TRGDLYCNT Position      */
#define EADC_SCTL0_TRGDLYCNT_Msk         (0xfful << EADC_SCTL0_TRGDLYCNT_Pos)              /*!< EADC_T::SCTL0: TRGDLYCNT Mask          */

#define EADC_SCTL0_TRGSEL_Pos            (16)                                              /*!< EADC_T::SCTL0: TRGSEL Position         */
#define EADC_SCTL0_TRGSEL_Msk            (0x1ful << EADC_SCTL0_TRGSEL_Pos)                 /*!< EADC_T::SCTL0: TRGSEL Mask             */

#define EADC_SCTL0_INTPOS_Pos            (22)                                              /*!< EADC_T::SCTL0: INTPOS Position         */
#define EADC_SCTL0_INTPOS_Msk            (0x1ul << EADC_SCTL0_INTPOS_Pos)                  /*!< EADC_T::SCTL0: INTPOS Mask             */

#define EADC_SCTL0_DBMEN_Pos             (23)                                              /*!< EADC_T::SCTL0: DBMEN Position          */
#define EADC_SCTL0_DBMEN_Msk             (0x1ul << EADC_SCTL0_DBMEN_Pos)                   /*!< EADC_T::SCTL0: DBMEN Mask              */

#define EADC_SCTL0_EXTSMPT_Pos           (24)                                              /*!< EADC_T::SCTL0: EXTSMPT Position        */
#define EADC_SCTL0_EXTSMPT_Msk           (0xfful << EADC_SCTL0_EXTSMPT_Pos)                /*!< EADC_T::SCTL0: EXTSMPT Mask            */

#define EADC_SCTL1_CHSEL_Pos             (0)                                               /*!< EADC_T::SCTL1: CHSEL Position          */
#define EADC_SCTL1_CHSEL_Msk             (0xful << EADC_SCTL1_CHSEL_Pos)                   /*!< EADC_T::SCTL1: CHSEL Mask              */

#define EADC_SCTL1_EXTREN_Pos            (4)                                               /*!< EADC_T::SCTL1: EXTREN Position         */
#define EADC_SCTL1_EXTREN_Msk            (0x1ul << EADC_SCTL1_EXTREN_Pos)                  /*!< EADC_T::SCTL1: EXTREN Mask             */

#define EADC_SCTL1_EXTFEN_Pos            (5)                                               /*!< EADC_T::SCTL1: EXTFEN Position         */
#define EADC_SCTL1_EXTFEN_Msk            (0x1ul << EADC_SCTL1_EXTFEN_Pos)                  /*!< EADC_T::SCTL1: EXTFEN Mask             */

#define EADC_SCTL1_TRGDLYDIV_Pos         (6)                                               /*!< EADC_T::SCTL1: TRGDLYDIV Position      */
#define EADC_SCTL1_TRGDLYDIV_Msk         (0x3ul << EADC_SCTL1_TRGDLYDIV_Pos)               /*!< EADC_T::SCTL1: TRGDLYDIV Mask          */

#define EADC_SCTL1_TRGDLYCNT_Pos         (8)                                               /*!< EADC_T::SCTL1: TRGDLYCNT Position      */
#define EADC_SCTL1_TRGDLYCNT_Msk         (0xfful << EADC_SCTL1_TRGDLYCNT_Pos)              /*!< EADC_T::SCTL1: TRGDLYCNT Mask          */

#define EADC_SCTL1_TRGSEL_Pos            (16)                                              /*!< EADC_T::SCTL1: TRGSEL Position         */
#define EADC_SCTL1_TRGSEL_Msk            (0x1ful << EADC_SCTL1_TRGSEL_Pos)                 /*!< EADC_T::SCTL1: TRGSEL Mask             */

#define EADC_SCTL1_INTPOS_Pos            (22)                                              /*!< EADC_T::SCTL1: INTPOS Position         */
#define EADC_SCTL1_INTPOS_Msk            (0x1ul << EADC_SCTL1_INTPOS_Pos)                  /*!< EADC_T::SCTL1: INTPOS Mask             */

#define EADC_SCTL1_DBMEN_Pos             (23)                                              /*!< EADC_T::SCTL1: DBMEN Position          */
#define EADC_SCTL1_DBMEN_Msk             (0x1ul << EADC_SCTL1_DBMEN_Pos)                   /*!< EADC_T::SCTL1: DBMEN Mask              */

#define EADC_SCTL1_EXTSMPT_Pos           (24)                                              /*!< EADC_T::SCTL1: EXTSMPT Position        */
#define EADC_SCTL1_EXTSMPT_Msk           (0xfful << EADC_SCTL1_EXTSMPT_Pos)                /*!< EADC_T::SCTL1: EXTSMPT Mask            */

#define EADC_SCTL2_CHSEL_Pos             (0)                                               /*!< EADC_T::SCTL2: CHSEL Position          */
#define EADC_SCTL2_CHSEL_Msk             (0xful << EADC_SCTL2_CHSEL_Pos)                   /*!< EADC_T::SCTL2: CHSEL Mask              */

#define EADC_SCTL2_EXTREN_Pos            (4)                                               /*!< EADC_T::SCTL2: EXTREN Position         */
#define EADC_SCTL2_EXTREN_Msk            (0x1ul << EADC_SCTL2_EXTREN_Pos)                  /*!< EADC_T::SCTL2: EXTREN Mask             */

#define EADC_SCTL2_EXTFEN_Pos            (5)                                               /*!< EADC_T::SCTL2: EXTFEN Position         */
#define EADC_SCTL2_EXTFEN_Msk            (0x1ul << EADC_SCTL2_EXTFEN_Pos)                  /*!< EADC_T::SCTL2: EXTFEN Mask             */

#define EADC_SCTL2_TRGDLYDIV_Pos         (6)                                               /*!< EADC_T::SCTL2: TRGDLYDIV Position      */
#define EADC_SCTL2_TRGDLYDIV_Msk         (0x3ul << EADC_SCTL2_TRGDLYDIV_Pos)               /*!< EADC_T::SCTL2: TRGDLYDIV Mask          */

#define EADC_SCTL2_TRGDLYCNT_Pos         (8)                                               /*!< EADC_T::SCTL2: TRGDLYCNT Position      */
#define EADC_SCTL2_TRGDLYCNT_Msk         (0xfful << EADC_SCTL2_TRGDLYCNT_Pos)              /*!< EADC_T::SCTL2: TRGDLYCNT Mask          */

#define EADC_SCTL2_TRGSEL_Pos            (16)                                              /*!< EADC_T::SCTL2: TRGSEL Position         */
#define EADC_SCTL2_TRGSEL_Msk            (0x1ful << EADC_SCTL2_TRGSEL_Pos)                 /*!< EADC_T::SCTL2: TRGSEL Mask             */

#define EADC_SCTL2_INTPOS_Pos            (22)                                              /*!< EADC_T::SCTL2: INTPOS Position         */
#define EADC_SCTL2_INTPOS_Msk            (0x1ul << EADC_SCTL2_INTPOS_Pos)                  /*!< EADC_T::SCTL2: INTPOS Mask             */

#define EADC_SCTL2_DBMEN_Pos             (23)                                              /*!< EADC_T::SCTL2: DBMEN Position          */
#define EADC_SCTL2_DBMEN_Msk             (0x1ul << EADC_SCTL2_DBMEN_Pos)                   /*!< EADC_T::SCTL2: DBMEN Mask              */

#define EADC_SCTL2_EXTSMPT_Pos           (24)                                              /*!< EADC_T::SCTL2: EXTSMPT Position        */
#define EADC_SCTL2_EXTSMPT_Msk           (0xfful << EADC_SCTL2_EXTSMPT_Pos)                /*!< EADC_T::SCTL2: EXTSMPT Mask            */

#define EADC_SCTL3_CHSEL_Pos             (0)                                               /*!< EADC_T::SCTL3: CHSEL Position          */
#define EADC_SCTL3_CHSEL_Msk             (0xful << EADC_SCTL3_CHSEL_Pos)                   /*!< EADC_T::SCTL3: CHSEL Mask              */

#define EADC_SCTL3_EXTREN_Pos            (4)                                               /*!< EADC_T::SCTL3: EXTREN Position         */
#define EADC_SCTL3_EXTREN_Msk            (0x1ul << EADC_SCTL3_EXTREN_Pos)                  /*!< EADC_T::SCTL3: EXTREN Mask             */

#define EADC_SCTL3_EXTFEN_Pos            (5)                                               /*!< EADC_T::SCTL3: EXTFEN Position         */
#define EADC_SCTL3_EXTFEN_Msk            (0x1ul << EADC_SCTL3_EXTFEN_Pos)                  /*!< EADC_T::SCTL3: EXTFEN Mask             */

#define EADC_SCTL3_TRGDLYDIV_Pos         (6)                                               /*!< EADC_T::SCTL3: TRGDLYDIV Position      */
#define EADC_SCTL3_TRGDLYDIV_Msk         (0x3ul << EADC_SCTL3_TRGDLYDIV_Pos)               /*!< EADC_T::SCTL3: TRGDLYDIV Mask          */

#define EADC_SCTL3_TRGDLYCNT_Pos         (8)                                               /*!< EADC_T::SCTL3: TRGDLYCNT Position      */
#define EADC_SCTL3_TRGDLYCNT_Msk         (0xfful << EADC_SCTL3_TRGDLYCNT_Pos)              /*!< EADC_T::SCTL3: TRGDLYCNT Mask          */

#define EADC_SCTL3_TRGSEL_Pos            (16)                                              /*!< EADC_T::SCTL3: TRGSEL Position         */
#define EADC_SCTL3_TRGSEL_Msk            (0x1ful << EADC_SCTL3_TRGSEL_Pos)                 /*!< EADC_T::SCTL3: TRGSEL Mask             */

#define EADC_SCTL3_INTPOS_Pos            (22)                                              /*!< EADC_T::SCTL3: INTPOS Position         */
#define EADC_SCTL3_INTPOS_Msk            (0x1ul << EADC_SCTL3_INTPOS_Pos)                  /*!< EADC_T::SCTL3: INTPOS Mask             */

#define EADC_SCTL3_DBMEN_Pos             (23)                                              /*!< EADC_T::SCTL3: DBMEN Position          */
#define EADC_SCTL3_DBMEN_Msk             (0x1ul << EADC_SCTL3_DBMEN_Pos)                   /*!< EADC_T::SCTL3: DBMEN Mask              */

#define EADC_SCTL3_EXTSMPT_Pos           (24)                                              /*!< EADC_T::SCTL3: EXTSMPT Position        */
#define EADC_SCTL3_EXTSMPT_Msk           (0xfful << EADC_SCTL3_EXTSMPT_Pos)                /*!< EADC_T::SCTL3: EXTSMPT Mask            */

#define EADC_SCTL4_CHSEL_Pos             (0)                                               /*!< EADC_T::SCTL4: CHSEL Position          */
#define EADC_SCTL4_CHSEL_Msk             (0xful << EADC_SCTL4_CHSEL_Pos)                   /*!< EADC_T::SCTL4: CHSEL Mask              */

#define EADC_SCTL4_EXTREN_Pos            (4)                                               /*!< EADC_T::SCTL4: EXTREN Position         */
#define EADC_SCTL4_EXTREN_Msk            (0x1ul << EADC_SCTL4_EXTREN_Pos)                  /*!< EADC_T::SCTL4: EXTREN Mask             */

#define EADC_SCTL4_EXTFEN_Pos            (5)                                               /*!< EADC_T::SCTL4: EXTFEN Position         */
#define EADC_SCTL4_EXTFEN_Msk            (0x1ul << EADC_SCTL4_EXTFEN_Pos)                  /*!< EADC_T::SCTL4: EXTFEN Mask             */

#define EADC_SCTL4_TRGDLYDIV_Pos         (6)                                               /*!< EADC_T::SCTL4: TRGDLYDIV Position      */
#define EADC_SCTL4_TRGDLYDIV_Msk         (0x3ul << EADC_SCTL4_TRGDLYDIV_Pos)               /*!< EADC_T::SCTL4: TRGDLYDIV Mask          */

#define EADC_SCTL4_TRGDLYCNT_Pos         (8)                                               /*!< EADC_T::SCTL4: TRGDLYCNT Position      */
#define EADC_SCTL4_TRGDLYCNT_Msk         (0xfful << EADC_SCTL4_TRGDLYCNT_Pos)              /*!< EADC_T::SCTL4: TRGDLYCNT Mask          */

#define EADC_SCTL4_TRGSEL_Pos            (16)                                              /*!< EADC_T::SCTL4: TRGSEL Position         */
#define EADC_SCTL4_TRGSEL_Msk            (0x1ful << EADC_SCTL4_TRGSEL_Pos)                 /*!< EADC_T::SCTL4: TRGSEL Mask             */

#define EADC_SCTL4_INTPOS_Pos            (22)                                              /*!< EADC_T::SCTL4: INTPOS Position         */
#define EADC_SCTL4_INTPOS_Msk            (0x1ul << EADC_SCTL4_INTPOS_Pos)                  /*!< EADC_T::SCTL4: INTPOS Mask             */

#define EADC_SCTL4_EXTSMPT_Pos           (24)                                              /*!< EADC_T::SCTL4: EXTSMPT Position        */
#define EADC_SCTL4_EXTSMPT_Msk           (0xfful << EADC_SCTL4_EXTSMPT_Pos)                /*!< EADC_T::SCTL4: EXTSMPT Mask            */

#define EADC_SCTL5_CHSEL_Pos             (0)                                               /*!< EADC_T::SCTL5: CHSEL Position          */
#define EADC_SCTL5_CHSEL_Msk             (0xful << EADC_SCTL5_CHSEL_Pos)                   /*!< EADC_T::SCTL5: CHSEL Mask              */

#define EADC_SCTL5_EXTREN_Pos            (4)                                               /*!< EADC_T::SCTL5: EXTREN Position         */
#define EADC_SCTL5_EXTREN_Msk            (0x1ul << EADC_SCTL5_EXTREN_Pos)                  /*!< EADC_T::SCTL5: EXTREN Mask             */

#define EADC_SCTL5_EXTFEN_Pos            (5)                                               /*!< EADC_T::SCTL5: EXTFEN Position         */
#define EADC_SCTL5_EXTFEN_Msk            (0x1ul << EADC_SCTL5_EXTFEN_Pos)                  /*!< EADC_T::SCTL5: EXTFEN Mask             */

#define EADC_SCTL5_TRGDLYDIV_Pos         (6)                                               /*!< EADC_T::SCTL5: TRGDLYDIV Position      */
#define EADC_SCTL5_TRGDLYDIV_Msk         (0x3ul << EADC_SCTL5_TRGDLYDIV_Pos)               /*!< EADC_T::SCTL5: TRGDLYDIV Mask          */

#define EADC_SCTL5_TRGDLYCNT_Pos         (8)                                               /*!< EADC_T::SCTL5: TRGDLYCNT Position      */
#define EADC_SCTL5_TRGDLYCNT_Msk         (0xfful << EADC_SCTL5_TRGDLYCNT_Pos)              /*!< EADC_T::SCTL5: TRGDLYCNT Mask          */

#define EADC_SCTL5_TRGSEL_Pos            (16)                                              /*!< EADC_T::SCTL5: TRGSEL Position         */
#define EADC_SCTL5_TRGSEL_Msk            (0x1ful << EADC_SCTL5_TRGSEL_Pos)                 /*!< EADC_T::SCTL5: TRGSEL Mask             */

#define EADC_SCTL5_INTPOS_Pos            (22)                                              /*!< EADC_T::SCTL5: INTPOS Position         */
#define EADC_SCTL5_INTPOS_Msk            (0x1ul << EADC_SCTL5_INTPOS_Pos)                  /*!< EADC_T::SCTL5: INTPOS Mask             */

#define EADC_SCTL5_EXTSMPT_Pos           (24)                                              /*!< EADC_T::SCTL5: EXTSMPT Position        */
#define EADC_SCTL5_EXTSMPT_Msk           (0xfful << EADC_SCTL5_EXTSMPT_Pos)                /*!< EADC_T::SCTL5: EXTSMPT Mask            */

#define EADC_SCTL6_CHSEL_Pos             (0)                                               /*!< EADC_T::SCTL6: CHSEL Position          */
#define EADC_SCTL6_CHSEL_Msk             (0xful << EADC_SCTL6_CHSEL_Pos)                   /*!< EADC_T::SCTL6: CHSEL Mask              */

#define EADC_SCTL6_EXTREN_Pos            (4)                                               /*!< EADC_T::SCTL6: EXTREN Position         */
#define EADC_SCTL6_EXTREN_Msk            (0x1ul << EADC_SCTL6_EXTREN_Pos)                  /*!< EADC_T::SCTL6: EXTREN Mask             */

#define EADC_SCTL6_EXTFEN_Pos            (5)                                               /*!< EADC_T::SCTL6: EXTFEN Position         */
#define EADC_SCTL6_EXTFEN_Msk            (0x1ul << EADC_SCTL6_EXTFEN_Pos)                  /*!< EADC_T::SCTL6: EXTFEN Mask             */

#define EADC_SCTL6_TRGDLYDIV_Pos         (6)                                               /*!< EADC_T::SCTL6: TRGDLYDIV Position      */
#define EADC_SCTL6_TRGDLYDIV_Msk         (0x3ul << EADC_SCTL6_TRGDLYDIV_Pos)               /*!< EADC_T::SCTL6: TRGDLYDIV Mask          */

#define EADC_SCTL6_TRGDLYCNT_Pos         (8)                                               /*!< EADC_T::SCTL6: TRGDLYCNT Position      */
#define EADC_SCTL6_TRGDLYCNT_Msk         (0xfful << EADC_SCTL6_TRGDLYCNT_Pos)              /*!< EADC_T::SCTL6: TRGDLYCNT Mask          */

#define EADC_SCTL6_TRGSEL_Pos            (16)                                              /*!< EADC_T::SCTL6: TRGSEL Position         */
#define EADC_SCTL6_TRGSEL_Msk            (0x1ful << EADC_SCTL6_TRGSEL_Pos)                 /*!< EADC_T::SCTL6: TRGSEL Mask             */

#define EADC_SCTL6_INTPOS_Pos            (22)                                              /*!< EADC_T::SCTL6: INTPOS Position         */
#define EADC_SCTL6_INTPOS_Msk            (0x1ul << EADC_SCTL6_INTPOS_Pos)                  /*!< EADC_T::SCTL6: INTPOS Mask             */

#define EADC_SCTL6_EXTSMPT_Pos           (24)                                              /*!< EADC_T::SCTL6: EXTSMPT Position        */
#define EADC_SCTL6_EXTSMPT_Msk           (0xfful << EADC_SCTL6_EXTSMPT_Pos)                /*!< EADC_T::SCTL6: EXTSMPT Mask            */

#define EADC_SCTL7_CHSEL_Pos             (0)                                               /*!< EADC_T::SCTL7: CHSEL Position          */
#define EADC_SCTL7_CHSEL_Msk             (0xful << EADC_SCTL7_CHSEL_Pos)                   /*!< EADC_T::SCTL7: CHSEL Mask              */

#define EADC_SCTL7_EXTREN_Pos            (4)                                               /*!< EADC_T::SCTL7: EXTREN Position         */
#define EADC_SCTL7_EXTREN_Msk            (0x1ul << EADC_SCTL7_EXTREN_Pos)                  /*!< EADC_T::SCTL7: EXTREN Mask             */

#define EADC_SCTL7_EXTFEN_Pos            (5)                                               /*!< EADC_T::SCTL7: EXTFEN Position         */
#define EADC_SCTL7_EXTFEN_Msk            (0x1ul << EADC_SCTL7_EXTFEN_Pos)                  /*!< EADC_T::SCTL7: EXTFEN Mask             */

#define EADC_SCTL7_TRGDLYDIV_Pos         (6)                                               /*!< EADC_T::SCTL7: TRGDLYDIV Position      */
#define EADC_SCTL7_TRGDLYDIV_Msk         (0x3ul << EADC_SCTL7_TRGDLYDIV_Pos)               /*!< EADC_T::SCTL7: TRGDLYDIV Mask          */

#define EADC_SCTL7_TRGDLYCNT_Pos         (8)                                               /*!< EADC_T::SCTL7: TRGDLYCNT Position      */
#define EADC_SCTL7_TRGDLYCNT_Msk         (0xfful << EADC_SCTL7_TRGDLYCNT_Pos)              /*!< EADC_T::SCTL7: TRGDLYCNT Mask          */

#define EADC_SCTL7_TRGSEL_Pos            (16)                                              /*!< EADC_T::SCTL7: TRGSEL Position         */
#define EADC_SCTL7_TRGSEL_Msk            (0x1ful << EADC_SCTL7_TRGSEL_Pos)                 /*!< EADC_T::SCTL7: TRGSEL Mask             */

#define EADC_SCTL7_INTPOS_Pos            (22)                                              /*!< EADC_T::SCTL7: INTPOS Position         */
#define EADC_SCTL7_INTPOS_Msk            (0x1ul << EADC_SCTL7_INTPOS_Pos)                  /*!< EADC_T::SCTL7: INTPOS Mask             */

#define EADC_SCTL7_EXTSMPT_Pos           (24)                                              /*!< EADC_T::SCTL7: EXTSMPT Position        */
#define EADC_SCTL7_EXTSMPT_Msk           (0xfful << EADC_SCTL7_EXTSMPT_Pos)                /*!< EADC_T::SCTL7: EXTSMPT Mask            */

#define EADC_SCTL8_CHSEL_Pos             (0)                                               /*!< EADC_T::SCTL8: CHSEL Position          */
#define EADC_SCTL8_CHSEL_Msk             (0xful << EADC_SCTL8_CHSEL_Pos)                   /*!< EADC_T::SCTL8: CHSEL Mask              */

#define EADC_SCTL8_EXTREN_Pos            (4)                                               /*!< EADC_T::SCTL8: EXTREN Position         */
#define EADC_SCTL8_EXTREN_Msk            (0x1ul << EADC_SCTL8_EXTREN_Pos)                  /*!< EADC_T::SCTL8: EXTREN Mask             */

#define EADC_SCTL8_EXTFEN_Pos            (5)                                               /*!< EADC_T::SCTL8: EXTFEN Position         */
#define EADC_SCTL8_EXTFEN_Msk            (0x1ul << EADC_SCTL8_EXTFEN_Pos)                  /*!< EADC_T::SCTL8: EXTFEN Mask             */

#define EADC_SCTL8_TRGDLYDIV_Pos         (6)                                               /*!< EADC_T::SCTL8: TRGDLYDIV Position      */
#define EADC_SCTL8_TRGDLYDIV_Msk         (0x3ul << EADC_SCTL8_TRGDLYDIV_Pos)               /*!< EADC_T::SCTL8: TRGDLYDIV Mask          */

#define EADC_SCTL8_TRGDLYCNT_Pos         (8)                                               /*!< EADC_T::SCTL8: TRGDLYCNT Position      */
#define EADC_SCTL8_TRGDLYCNT_Msk         (0xfful << EADC_SCTL8_TRGDLYCNT_Pos)              /*!< EADC_T::SCTL8: TRGDLYCNT Mask          */

#define EADC_SCTL8_TRGSEL_Pos            (16)                                              /*!< EADC_T::SCTL8: TRGSEL Position         */
#define EADC_SCTL8_TRGSEL_Msk            (0x1ful << EADC_SCTL8_TRGSEL_Pos)                 /*!< EADC_T::SCTL8: TRGSEL Mask             */

#define EADC_SCTL8_INTPOS_Pos            (22)                                              /*!< EADC_T::SCTL8: INTPOS Position         */
#define EADC_SCTL8_INTPOS_Msk            (0x1ul << EADC_SCTL8_INTPOS_Pos)                  /*!< EADC_T::SCTL8: INTPOS Mask             */

#define EADC_SCTL8_EXTSMPT_Pos           (24)                                              /*!< EADC_T::SCTL8: EXTSMPT Position        */
#define EADC_SCTL8_EXTSMPT_Msk           (0xfful << EADC_SCTL8_EXTSMPT_Pos)                /*!< EADC_T::SCTL8: EXTSMPT Mask            */

#define EADC_SCTL9_CHSEL_Pos             (0)                                               /*!< EADC_T::SCTL9: CHSEL Position          */
#define EADC_SCTL9_CHSEL_Msk             (0xful << EADC_SCTL9_CHSEL_Pos)                   /*!< EADC_T::SCTL9: CHSEL Mask              */

#define EADC_SCTL9_EXTREN_Pos            (4)                                               /*!< EADC_T::SCTL9: EXTREN Position         */
#define EADC_SCTL9_EXTREN_Msk            (0x1ul << EADC_SCTL9_EXTREN_Pos)                  /*!< EADC_T::SCTL9: EXTREN Mask             */

#define EADC_SCTL9_EXTFEN_Pos            (5)                                               /*!< EADC_T::SCTL9: EXTFEN Position         */
#define EADC_SCTL9_EXTFEN_Msk            (0x1ul << EADC_SCTL9_EXTFEN_Pos)                  /*!< EADC_T::SCTL9: EXTFEN Mask             */

#define EADC_SCTL9_TRGDLYDIV_Pos         (6)                                               /*!< EADC_T::SCTL9: TRGDLYDIV Position      */
#define EADC_SCTL9_TRGDLYDIV_Msk         (0x3ul << EADC_SCTL9_TRGDLYDIV_Pos)               /*!< EADC_T::SCTL9: TRGDLYDIV Mask          */

#define EADC_SCTL9_TRGDLYCNT_Pos         (8)                                               /*!< EADC_T::SCTL9: TRGDLYCNT Position      */
#define EADC_SCTL9_TRGDLYCNT_Msk         (0xfful << EADC_SCTL9_TRGDLYCNT_Pos)              /*!< EADC_T::SCTL9: TRGDLYCNT Mask          */

#define EADC_SCTL9_TRGSEL_Pos            (16)                                              /*!< EADC_T::SCTL9: TRGSEL Position         */
#define EADC_SCTL9_TRGSEL_Msk            (0x1ful << EADC_SCTL9_TRGSEL_Pos)                 /*!< EADC_T::SCTL9: TRGSEL Mask             */

#define EADC_SCTL9_INTPOS_Pos            (22)                                              /*!< EADC_T::SCTL9: INTPOS Position         */
#define EADC_SCTL9_INTPOS_Msk            (0x1ul << EADC_SCTL9_INTPOS_Pos)                  /*!< EADC_T::SCTL9: INTPOS Mask             */

#define EADC_SCTL9_EXTSMPT_Pos           (24)                                              /*!< EADC_T::SCTL9: EXTSMPT Position        */
#define EADC_SCTL9_EXTSMPT_Msk           (0xfful << EADC_SCTL9_EXTSMPT_Pos)                /*!< EADC_T::SCTL9: EXTSMPT Mask            */

#define EADC_SCTL10_CHSEL_Pos            (0)                                               /*!< EADC_T::SCTL10: CHSEL Position         */
#define EADC_SCTL10_CHSEL_Msk            (0xful << EADC_SCTL10_CHSEL_Pos)                  /*!< EADC_T::SCTL10: CHSEL Mask             */

#define EADC_SCTL10_EXTREN_Pos           (4)                                               /*!< EADC_T::SCTL10: EXTREN Position        */
#define EADC_SCTL10_EXTREN_Msk           (0x1ul << EADC_SCTL10_EXTREN_Pos)                 /*!< EADC_T::SCTL10: EXTREN Mask            */

#define EADC_SCTL10_EXTFEN_Pos           (5)                                               /*!< EADC_T::SCTL10: EXTFEN Position        */
#define EADC_SCTL10_EXTFEN_Msk           (0x1ul << EADC_SCTL10_EXTFEN_Pos)                 /*!< EADC_T::SCTL10: EXTFEN Mask            */

#define EADC_SCTL10_TRGDLYDIV_Pos        (6)                                               /*!< EADC_T::SCTL10: TRGDLYDIV Position     */
#define EADC_SCTL10_TRGDLYDIV_Msk        (0x3ul << EADC_SCTL10_TRGDLYDIV_Pos)              /*!< EADC_T::SCTL10: TRGDLYDIV Mask         */

#define EADC_SCTL10_TRGDLYCNT_Pos        (8)                                               /*!< EADC_T::SCTL10: TRGDLYCNT Position     */
#define EADC_SCTL10_TRGDLYCNT_Msk        (0xfful << EADC_SCTL10_TRGDLYCNT_Pos)             /*!< EADC_T::SCTL10: TRGDLYCNT Mask         */

#define EADC_SCTL10_TRGSEL_Pos           (16)                                              /*!< EADC_T::SCTL10: TRGSEL Position        */
#define EADC_SCTL10_TRGSEL_Msk           (0x1ful << EADC_SCTL10_TRGSEL_Pos)                /*!< EADC_T::SCTL10: TRGSEL Mask            */

#define EADC_SCTL10_INTPOS_Pos           (22)                                              /*!< EADC_T::SCTL10: INTPOS Position        */
#define EADC_SCTL10_INTPOS_Msk           (0x1ul << EADC_SCTL10_INTPOS_Pos)                 /*!< EADC_T::SCTL10: INTPOS Mask            */

#define EADC_SCTL10_EXTSMPT_Pos          (24)                                              /*!< EADC_T::SCTL10: EXTSMPT Position       */
#define EADC_SCTL10_EXTSMPT_Msk          (0xfful << EADC_SCTL10_EXTSMPT_Pos)               /*!< EADC_T::SCTL10: EXTSMPT Mask           */

#define EADC_SCTL11_CHSEL_Pos            (0)                                               /*!< EADC_T::SCTL11: CHSEL Position         */
#define EADC_SCTL11_CHSEL_Msk            (0xful << EADC_SCTL11_CHSEL_Pos)                  /*!< EADC_T::SCTL11: CHSEL Mask             */

#define EADC_SCTL11_EXTREN_Pos           (4)                                               /*!< EADC_T::SCTL11: EXTREN Position        */
#define EADC_SCTL11_EXTREN_Msk           (0x1ul << EADC_SCTL11_EXTREN_Pos)                 /*!< EADC_T::SCTL11: EXTREN Mask            */

#define EADC_SCTL11_EXTFEN_Pos           (5)                                               /*!< EADC_T::SCTL11: EXTFEN Position        */
#define EADC_SCTL11_EXTFEN_Msk           (0x1ul << EADC_SCTL11_EXTFEN_Pos)                 /*!< EADC_T::SCTL11: EXTFEN Mask            */

#define EADC_SCTL11_TRGDLYDIV_Pos        (6)                                               /*!< EADC_T::SCTL11: TRGDLYDIV Position     */
#define EADC_SCTL11_TRGDLYDIV_Msk        (0x3ul << EADC_SCTL11_TRGDLYDIV_Pos)              /*!< EADC_T::SCTL11: TRGDLYDIV Mask         */

#define EADC_SCTL11_TRGDLYCNT_Pos        (8)                                               /*!< EADC_T::SCTL11: TRGDLYCNT Position     */
#define EADC_SCTL11_TRGDLYCNT_Msk        (0xfful << EADC_SCTL11_TRGDLYCNT_Pos)             /*!< EADC_T::SCTL11: TRGDLYCNT Mask         */

#define EADC_SCTL11_TRGSEL_Pos           (16)                                              /*!< EADC_T::SCTL11: TRGSEL Position        */
#define EADC_SCTL11_TRGSEL_Msk           (0x1ful << EADC_SCTL11_TRGSEL_Pos)                /*!< EADC_T::SCTL11: TRGSEL Mask            */

#define EADC_SCTL11_INTPOS_Pos           (22)                                              /*!< EADC_T::SCTL11: INTPOS Position        */
#define EADC_SCTL11_INTPOS_Msk           (0x1ul << EADC_SCTL11_INTPOS_Pos)                 /*!< EADC_T::SCTL11: INTPOS Mask            */

#define EADC_SCTL11_EXTSMPT_Pos          (24)                                              /*!< EADC_T::SCTL11: EXTSMPT Position       */
#define EADC_SCTL11_EXTSMPT_Msk          (0xfful << EADC_SCTL11_EXTSMPT_Pos)               /*!< EADC_T::SCTL11: EXTSMPT Mask           */

#define EADC_SCTL12_CHSEL_Pos            (0)                                               /*!< EADC_T::SCTL12: CHSEL Position         */
#define EADC_SCTL12_CHSEL_Msk            (0xful << EADC_SCTL12_CHSEL_Pos)                  /*!< EADC_T::SCTL12: CHSEL Mask             */

#define EADC_SCTL12_EXTREN_Pos           (4)                                               /*!< EADC_T::SCTL12: EXTREN Position        */
#define EADC_SCTL12_EXTREN_Msk           (0x1ul << EADC_SCTL12_EXTREN_Pos)                 /*!< EADC_T::SCTL12: EXTREN Mask            */

#define EADC_SCTL12_EXTFEN_Pos           (5)                                               /*!< EADC_T::SCTL12: EXTFEN Position        */
#define EADC_SCTL12_EXTFEN_Msk           (0x1ul << EADC_SCTL12_EXTFEN_Pos)                 /*!< EADC_T::SCTL12: EXTFEN Mask            */

#define EADC_SCTL12_TRGDLYDIV_Pos        (6)                                               /*!< EADC_T::SCTL12: TRGDLYDIV Position     */
#define EADC_SCTL12_TRGDLYDIV_Msk        (0x3ul << EADC_SCTL12_TRGDLYDIV_Pos)              /*!< EADC_T::SCTL12: TRGDLYDIV Mask         */

#define EADC_SCTL12_TRGDLYCNT_Pos        (8)                                               /*!< EADC_T::SCTL12: TRGDLYCNT Position     */
#define EADC_SCTL12_TRGDLYCNT_Msk        (0xfful << EADC_SCTL12_TRGDLYCNT_Pos)             /*!< EADC_T::SCTL12: TRGDLYCNT Mask         */

#define EADC_SCTL12_TRGSEL_Pos           (16)                                              /*!< EADC_T::SCTL12: TRGSEL Position        */
#define EADC_SCTL12_TRGSEL_Msk           (0x1ful << EADC_SCTL12_TRGSEL_Pos)                /*!< EADC_T::SCTL12: TRGSEL Mask            */

#define EADC_SCTL12_INTPOS_Pos           (22)                                              /*!< EADC_T::SCTL12: INTPOS Position        */
#define EADC_SCTL12_INTPOS_Msk           (0x1ul << EADC_SCTL12_INTPOS_Pos)                 /*!< EADC_T::SCTL12: INTPOS Mask            */

#define EADC_SCTL12_EXTSMPT_Pos          (24)                                              /*!< EADC_T::SCTL12: EXTSMPT Position       */
#define EADC_SCTL12_EXTSMPT_Msk          (0xfful << EADC_SCTL12_EXTSMPT_Pos)               /*!< EADC_T::SCTL12: EXTSMPT Mask           */

#define EADC_SCTL13_CHSEL_Pos            (0)                                               /*!< EADC_T::SCTL13: CHSEL Position         */
#define EADC_SCTL13_CHSEL_Msk            (0xful << EADC_SCTL13_CHSEL_Pos)                  /*!< EADC_T::SCTL13: CHSEL Mask             */

#define EADC_SCTL13_EXTREN_Pos           (4)                                               /*!< EADC_T::SCTL13: EXTREN Position        */
#define EADC_SCTL13_EXTREN_Msk           (0x1ul << EADC_SCTL13_EXTREN_Pos)                 /*!< EADC_T::SCTL13: EXTREN Mask            */

#define EADC_SCTL13_EXTFEN_Pos           (5)                                               /*!< EADC_T::SCTL13: EXTFEN Position        */
#define EADC_SCTL13_EXTFEN_Msk           (0x1ul << EADC_SCTL13_EXTFEN_Pos)                 /*!< EADC_T::SCTL13: EXTFEN Mask            */

#define EADC_SCTL13_TRGDLYDIV_Pos        (6)                                               /*!< EADC_T::SCTL13: TRGDLYDIV Position     */
#define EADC_SCTL13_TRGDLYDIV_Msk        (0x3ul << EADC_SCTL13_TRGDLYDIV_Pos)              /*!< EADC_T::SCTL13: TRGDLYDIV Mask         */

#define EADC_SCTL13_TRGDLYCNT_Pos        (8)                                               /*!< EADC_T::SCTL13: TRGDLYCNT Position     */
#define EADC_SCTL13_TRGDLYCNT_Msk        (0xfful << EADC_SCTL13_TRGDLYCNT_Pos)             /*!< EADC_T::SCTL13: TRGDLYCNT Mask         */

#define EADC_SCTL13_TRGSEL_Pos           (16)                                              /*!< EADC_T::SCTL13: TRGSEL Position        */
#define EADC_SCTL13_TRGSEL_Msk           (0x1ful << EADC_SCTL13_TRGSEL_Pos)                /*!< EADC_T::SCTL13: TRGSEL Mask            */

#define EADC_SCTL13_INTPOS_Pos           (22)                                              /*!< EADC_T::SCTL13: INTPOS Position        */
#define EADC_SCTL13_INTPOS_Msk           (0x1ul << EADC_SCTL13_INTPOS_Pos)                 /*!< EADC_T::SCTL13: INTPOS Mask            */

#define EADC_SCTL13_EXTSMPT_Pos          (24)                                              /*!< EADC_T::SCTL13: EXTSMPT Position       */
#define EADC_SCTL13_EXTSMPT_Msk          (0xfful << EADC_SCTL13_EXTSMPT_Pos)               /*!< EADC_T::SCTL13: EXTSMPT Mask           */

#define EADC_SCTL14_CHSEL_Pos            (0)                                               /*!< EADC_T::SCTL14: CHSEL Position         */
#define EADC_SCTL14_CHSEL_Msk            (0xful << EADC_SCTL14_CHSEL_Pos)                  /*!< EADC_T::SCTL14: CHSEL Mask             */

#define EADC_SCTL14_EXTREN_Pos           (4)                                               /*!< EADC_T::SCTL14: EXTREN Position        */
#define EADC_SCTL14_EXTREN_Msk           (0x1ul << EADC_SCTL14_EXTREN_Pos)                 /*!< EADC_T::SCTL14: EXTREN Mask            */

#define EADC_SCTL14_EXTFEN_Pos           (5)                                               /*!< EADC_T::SCTL14: EXTFEN Position        */
#define EADC_SCTL14_EXTFEN_Msk           (0x1ul << EADC_SCTL14_EXTFEN_Pos)                 /*!< EADC_T::SCTL14: EXTFEN Mask            */

#define EADC_SCTL14_TRGDLYDIV_Pos        (6)                                               /*!< EADC_T::SCTL14: TRGDLYDIV Position     */
#define EADC_SCTL14_TRGDLYDIV_Msk        (0x3ul << EADC_SCTL14_TRGDLYDIV_Pos)              /*!< EADC_T::SCTL14: TRGDLYDIV Mask         */

#define EADC_SCTL14_TRGDLYCNT_Pos        (8)                                               /*!< EADC_T::SCTL14: TRGDLYCNT Position     */
#define EADC_SCTL14_TRGDLYCNT_Msk        (0xfful << EADC_SCTL14_TRGDLYCNT_Pos)             /*!< EADC_T::SCTL14: TRGDLYCNT Mask         */

#define EADC_SCTL14_TRGSEL_Pos           (16)                                              /*!< EADC_T::SCTL14: TRGSEL Position        */
#define EADC_SCTL14_TRGSEL_Msk           (0x1ful << EADC_SCTL14_TRGSEL_Pos)                /*!< EADC_T::SCTL14: TRGSEL Mask            */

#define EADC_SCTL14_INTPOS_Pos           (22)                                              /*!< EADC_T::SCTL14: INTPOS Position        */
#define EADC_SCTL14_INTPOS_Msk           (0x1ul << EADC_SCTL14_INTPOS_Pos)                 /*!< EADC_T::SCTL14: INTPOS Mask            */

#define EADC_SCTL14_EXTSMPT_Pos          (24)                                              /*!< EADC_T::SCTL14: EXTSMPT Position       */
#define EADC_SCTL14_EXTSMPT_Msk          (0xfful << EADC_SCTL14_EXTSMPT_Pos)               /*!< EADC_T::SCTL14: EXTSMPT Mask           */

#define EADC_SCTL15_CHSEL_Pos            (0)                                               /*!< EADC_T::SCTL15: CHSEL Position         */
#define EADC_SCTL15_CHSEL_Msk            (0xful << EADC_SCTL15_CHSEL_Pos)                  /*!< EADC_T::SCTL15: CHSEL Mask             */

#define EADC_SCTL15_EXTREN_Pos           (4)                                               /*!< EADC_T::SCTL15: EXTREN Position        */
#define EADC_SCTL15_EXTREN_Msk           (0x1ul << EADC_SCTL15_EXTREN_Pos)                 /*!< EADC_T::SCTL15: EXTREN Mask            */

#define EADC_SCTL15_EXTFEN_Pos           (5)                                               /*!< EADC_T::SCTL15: EXTFEN Position        */
#define EADC_SCTL15_EXTFEN_Msk           (0x1ul << EADC_SCTL15_EXTFEN_Pos)                 /*!< EADC_T::SCTL15: EXTFEN Mask            */

#define EADC_SCTL15_TRGDLYDIV_Pos        (6)                                               /*!< EADC_T::SCTL15: TRGDLYDIV Position     */
#define EADC_SCTL15_TRGDLYDIV_Msk        (0x3ul << EADC_SCTL15_TRGDLYDIV_Pos)              /*!< EADC_T::SCTL15: TRGDLYDIV Mask         */

#define EADC_SCTL15_TRGDLYCNT_Pos        (8)                                               /*!< EADC_T::SCTL15: TRGDLYCNT Position     */
#define EADC_SCTL15_TRGDLYCNT_Msk        (0xfful << EADC_SCTL15_TRGDLYCNT_Pos)             /*!< EADC_T::SCTL15: TRGDLYCNT Mask         */

#define EADC_SCTL15_TRGSEL_Pos           (16)                                              /*!< EADC_T::SCTL15: TRGSEL Position        */
#define EADC_SCTL15_TRGSEL_Msk           (0x1ful << EADC_SCTL15_TRGSEL_Pos)                /*!< EADC_T::SCTL15: TRGSEL Mask            */

#define EADC_SCTL15_INTPOS_Pos           (22)                                              /*!< EADC_T::SCTL15: INTPOS Position        */
#define EADC_SCTL15_INTPOS_Msk           (0x1ul << EADC_SCTL15_INTPOS_Pos)                 /*!< EADC_T::SCTL15: INTPOS Mask            */

#define EADC_SCTL15_EXTSMPT_Pos          (24)                                              /*!< EADC_T::SCTL15: EXTSMPT Position       */
#define EADC_SCTL15_EXTSMPT_Msk          (0xfful << EADC_SCTL15_EXTSMPT_Pos)               /*!< EADC_T::SCTL15: EXTSMPT Mask           */

#define EADC_SCTL16_EXTSMPT_Pos          (24)                                              /*!< EADC_T::SCTL16: EXTSMPT Position       */
#define EADC_SCTL16_EXTSMPT_Msk          (0xfful << EADC_SCTL16_EXTSMPT_Pos)               /*!< EADC_T::SCTL16: EXTSMPT Mask           */

#define EADC_SCTL17_EXTSMPT_Pos          (24)                                              /*!< EADC_T::SCTL17: EXTSMPT Position       */
#define EADC_SCTL17_EXTSMPT_Msk          (0xfful << EADC_SCTL17_EXTSMPT_Pos)               /*!< EADC_T::SCTL17: EXTSMPT Mask           */

#define EADC_SCTL18_EXTSMPT_Pos          (24)                                              /*!< EADC_T::SCTL18: EXTSMPT Position       */
#define EADC_SCTL18_EXTSMPT_Msk          (0xfful << EADC_SCTL18_EXTSMPT_Pos)               /*!< EADC_T::SCTL18: EXTSMPT Mask           */

#define EADC_INTSRC0_SPLIE0_Pos          (0)                                               /*!< EADC_T::INTSRC0: SPLIE0 Position       */
#define EADC_INTSRC0_SPLIE0_Msk          (0x1ul << EADC_INTSRC0_SPLIE0_Pos)                /*!< EADC_T::INTSRC0: SPLIE0 Mask           */

#define EADC_INTSRC0_SPLIE1_Pos          (1)                                               /*!< EADC_T::INTSRC0: SPLIE1 Position       */
#define EADC_INTSRC0_SPLIE1_Msk          (0x1ul << EADC_INTSRC0_SPLIE1_Pos)                /*!< EADC_T::INTSRC0: SPLIE1 Mask           */

#define EADC_INTSRC0_SPLIE2_Pos          (2)                                               /*!< EADC_T::INTSRC0: SPLIE2 Position       */
#define EADC_INTSRC0_SPLIE2_Msk          (0x1ul << EADC_INTSRC0_SPLIE2_Pos)                /*!< EADC_T::INTSRC0: SPLIE2 Mask           */

#define EADC_INTSRC0_SPLIE3_Pos          (3)                                               /*!< EADC_T::INTSRC0: SPLIE3 Position       */
#define EADC_INTSRC0_SPLIE3_Msk          (0x1ul << EADC_INTSRC0_SPLIE3_Pos)                /*!< EADC_T::INTSRC0: SPLIE3 Mask           */

#define EADC_INTSRC0_SPLIE4_Pos          (4)                                               /*!< EADC_T::INTSRC0: SPLIE4 Position       */
#define EADC_INTSRC0_SPLIE4_Msk          (0x1ul << EADC_INTSRC0_SPLIE4_Pos)                /*!< EADC_T::INTSRC0: SPLIE4 Mask           */

#define EADC_INTSRC0_SPLIE5_Pos          (5)                                               /*!< EADC_T::INTSRC0: SPLIE5 Position       */
#define EADC_INTSRC0_SPLIE5_Msk          (0x1ul << EADC_INTSRC0_SPLIE5_Pos)                /*!< EADC_T::INTSRC0: SPLIE5 Mask           */

#define EADC_INTSRC0_SPLIE6_Pos          (6)                                               /*!< EADC_T::INTSRC0: SPLIE6 Position       */
#define EADC_INTSRC0_SPLIE6_Msk          (0x1ul << EADC_INTSRC0_SPLIE6_Pos)                /*!< EADC_T::INTSRC0: SPLIE6 Mask           */

#define EADC_INTSRC0_SPLIE7_Pos          (7)                                               /*!< EADC_T::INTSRC0: SPLIE7 Position       */
#define EADC_INTSRC0_SPLIE7_Msk          (0x1ul << EADC_INTSRC0_SPLIE7_Pos)                /*!< EADC_T::INTSRC0: SPLIE7 Mask           */

#define EADC_INTSRC0_SPLIE8_Pos          (8)                                               /*!< EADC_T::INTSRC0: SPLIE8 Position       */
#define EADC_INTSRC0_SPLIE8_Msk          (0x1ul << EADC_INTSRC0_SPLIE8_Pos)                /*!< EADC_T::INTSRC0: SPLIE8 Mask           */

#define EADC_INTSRC0_SPLIE9_Pos          (9)                                               /*!< EADC_T::INTSRC0: SPLIE9 Position       */
#define EADC_INTSRC0_SPLIE9_Msk          (0x1ul << EADC_INTSRC0_SPLIE9_Pos)                /*!< EADC_T::INTSRC0: SPLIE9 Mask           */

#define EADC_INTSRC0_SPLIE10_Pos         (10)                                              /*!< EADC_T::INTSRC0: SPLIE10 Position      */
#define EADC_INTSRC0_SPLIE10_Msk         (0x1ul << EADC_INTSRC0_SPLIE10_Pos)               /*!< EADC_T::INTSRC0: SPLIE10 Mask          */

#define EADC_INTSRC0_SPLIE11_Pos         (11)                                              /*!< EADC_T::INTSRC0: SPLIE11 Position      */
#define EADC_INTSRC0_SPLIE11_Msk         (0x1ul << EADC_INTSRC0_SPLIE11_Pos)               /*!< EADC_T::INTSRC0: SPLIE11 Mask          */

#define EADC_INTSRC0_SPLIE12_Pos         (12)                                              /*!< EADC_T::INTSRC0: SPLIE12 Position      */
#define EADC_INTSRC0_SPLIE12_Msk         (0x1ul << EADC_INTSRC0_SPLIE12_Pos)               /*!< EADC_T::INTSRC0: SPLIE12 Mask          */

#define EADC_INTSRC0_SPLIE13_Pos         (13)                                              /*!< EADC_T::INTSRC0: SPLIE13 Position      */
#define EADC_INTSRC0_SPLIE13_Msk         (0x1ul << EADC_INTSRC0_SPLIE13_Pos)               /*!< EADC_T::INTSRC0: SPLIE13 Mask          */

#define EADC_INTSRC0_SPLIE14_Pos         (14)                                              /*!< EADC_T::INTSRC0: SPLIE14 Position      */
#define EADC_INTSRC0_SPLIE14_Msk         (0x1ul << EADC_INTSRC0_SPLIE14_Pos)               /*!< EADC_T::INTSRC0: SPLIE14 Mask          */

#define EADC_INTSRC0_SPLIE15_Pos         (15)                                              /*!< EADC_T::INTSRC0: SPLIE15 Position      */
#define EADC_INTSRC0_SPLIE15_Msk         (0x1ul << EADC_INTSRC0_SPLIE15_Pos)               /*!< EADC_T::INTSRC0: SPLIE15 Mask          */

#define EADC_INTSRC0_SPLIE16_Pos         (16)                                              /*!< EADC_T::INTSRC0: SPLIE16 Position      */
#define EADC_INTSRC0_SPLIE16_Msk         (0x1ul << EADC_INTSRC0_SPLIE16_Pos)               /*!< EADC_T::INTSRC0: SPLIE16 Mask          */

#define EADC_INTSRC0_SPLIE17_Pos         (17)                                              /*!< EADC_T::INTSRC0: SPLIE17 Position      */
#define EADC_INTSRC0_SPLIE17_Msk         (0x1ul << EADC_INTSRC0_SPLIE17_Pos)               /*!< EADC_T::INTSRC0: SPLIE17 Mask          */

#define EADC_INTSRC0_SPLIE18_Pos         (18)                                              /*!< EADC_T::INTSRC0: SPLIE18 Position      */
#define EADC_INTSRC0_SPLIE18_Msk         (0x1ul << EADC_INTSRC0_SPLIE18_Pos)               /*!< EADC_T::INTSRC0: SPLIE18 Mask          */

#define EADC_INTSRC1_SPLIE0_Pos          (0)                                               /*!< EADC_T::INTSRC1: SPLIE0 Position       */
#define EADC_INTSRC1_SPLIE0_Msk          (0x1ul << EADC_INTSRC1_SPLIE0_Pos)                /*!< EADC_T::INTSRC1: SPLIE0 Mask           */

#define EADC_INTSRC1_SPLIE1_Pos          (1)                                               /*!< EADC_T::INTSRC1: SPLIE1 Position       */
#define EADC_INTSRC1_SPLIE1_Msk          (0x1ul << EADC_INTSRC1_SPLIE1_Pos)                /*!< EADC_T::INTSRC1: SPLIE1 Mask           */

#define EADC_INTSRC1_SPLIE2_Pos          (2)                                               /*!< EADC_T::INTSRC1: SPLIE2 Position       */
#define EADC_INTSRC1_SPLIE2_Msk          (0x1ul << EADC_INTSRC1_SPLIE2_Pos)                /*!< EADC_T::INTSRC1: SPLIE2 Mask           */

#define EADC_INTSRC1_SPLIE3_Pos          (3)                                               /*!< EADC_T::INTSRC1: SPLIE3 Position       */
#define EADC_INTSRC1_SPLIE3_Msk          (0x1ul << EADC_INTSRC1_SPLIE3_Pos)                /*!< EADC_T::INTSRC1: SPLIE3 Mask           */

#define EADC_INTSRC1_SPLIE4_Pos          (4)                                               /*!< EADC_T::INTSRC1: SPLIE4 Position       */
#define EADC_INTSRC1_SPLIE4_Msk          (0x1ul << EADC_INTSRC1_SPLIE4_Pos)                /*!< EADC_T::INTSRC1: SPLIE4 Mask           */

#define EADC_INTSRC1_SPLIE5_Pos          (5)                                               /*!< EADC_T::INTSRC1: SPLIE5 Position       */
#define EADC_INTSRC1_SPLIE5_Msk          (0x1ul << EADC_INTSRC1_SPLIE5_Pos)                /*!< EADC_T::INTSRC1: SPLIE5 Mask           */

#define EADC_INTSRC1_SPLIE6_Pos          (6)                                               /*!< EADC_T::INTSRC1: SPLIE6 Position       */
#define EADC_INTSRC1_SPLIE6_Msk          (0x1ul << EADC_INTSRC1_SPLIE6_Pos)                /*!< EADC_T::INTSRC1: SPLIE6 Mask           */

#define EADC_INTSRC1_SPLIE7_Pos          (7)                                               /*!< EADC_T::INTSRC1: SPLIE7 Position       */
#define EADC_INTSRC1_SPLIE7_Msk          (0x1ul << EADC_INTSRC1_SPLIE7_Pos)                /*!< EADC_T::INTSRC1: SPLIE7 Mask           */

#define EADC_INTSRC1_SPLIE8_Pos          (8)                                               /*!< EADC_T::INTSRC1: SPLIE8 Position       */
#define EADC_INTSRC1_SPLIE8_Msk          (0x1ul << EADC_INTSRC1_SPLIE8_Pos)                /*!< EADC_T::INTSRC1: SPLIE8 Mask           */

#define EADC_INTSRC1_SPLIE9_Pos          (9)                                               /*!< EADC_T::INTSRC1: SPLIE9 Position       */
#define EADC_INTSRC1_SPLIE9_Msk          (0x1ul << EADC_INTSRC1_SPLIE9_Pos)                /*!< EADC_T::INTSRC1: SPLIE9 Mask           */

#define EADC_INTSRC1_SPLIE10_Pos         (10)                                              /*!< EADC_T::INTSRC1: SPLIE10 Position      */
#define EADC_INTSRC1_SPLIE10_Msk         (0x1ul << EADC_INTSRC1_SPLIE10_Pos)               /*!< EADC_T::INTSRC1: SPLIE10 Mask          */

#define EADC_INTSRC1_SPLIE11_Pos         (11)                                              /*!< EADC_T::INTSRC1: SPLIE11 Position      */
#define EADC_INTSRC1_SPLIE11_Msk         (0x1ul << EADC_INTSRC1_SPLIE11_Pos)               /*!< EADC_T::INTSRC1: SPLIE11 Mask          */

#define EADC_INTSRC1_SPLIE12_Pos         (12)                                              /*!< EADC_T::INTSRC1: SPLIE12 Position      */
#define EADC_INTSRC1_SPLIE12_Msk         (0x1ul << EADC_INTSRC1_SPLIE12_Pos)               /*!< EADC_T::INTSRC1: SPLIE12 Mask          */

#define EADC_INTSRC1_SPLIE13_Pos         (13)                                              /*!< EADC_T::INTSRC1: SPLIE13 Position      */
#define EADC_INTSRC1_SPLIE13_Msk         (0x1ul << EADC_INTSRC1_SPLIE13_Pos)               /*!< EADC_T::INTSRC1: SPLIE13 Mask          */

#define EADC_INTSRC1_SPLIE14_Pos         (14)                                              /*!< EADC_T::INTSRC1: SPLIE14 Position      */
#define EADC_INTSRC1_SPLIE14_Msk         (0x1ul << EADC_INTSRC1_SPLIE14_Pos)               /*!< EADC_T::INTSRC1: SPLIE14 Mask          */

#define EADC_INTSRC1_SPLIE15_Pos         (15)                                              /*!< EADC_T::INTSRC1: SPLIE15 Position      */
#define EADC_INTSRC1_SPLIE15_Msk         (0x1ul << EADC_INTSRC1_SPLIE15_Pos)               /*!< EADC_T::INTSRC1: SPLIE15 Mask          */

#define EADC_INTSRC1_SPLIE16_Pos         (16)                                              /*!< EADC_T::INTSRC1: SPLIE16 Position      */
#define EADC_INTSRC1_SPLIE16_Msk         (0x1ul << EADC_INTSRC1_SPLIE16_Pos)               /*!< EADC_T::INTSRC1: SPLIE16 Mask          */

#define EADC_INTSRC1_SPLIE17_Pos         (17)                                              /*!< EADC_T::INTSRC1: SPLIE17 Position      */
#define EADC_INTSRC1_SPLIE17_Msk         (0x1ul << EADC_INTSRC1_SPLIE17_Pos)               /*!< EADC_T::INTSRC1: SPLIE17 Mask          */

#define EADC_INTSRC1_SPLIE18_Pos         (18)                                              /*!< EADC_T::INTSRC1: SPLIE18 Position      */
#define EADC_INTSRC1_SPLIE18_Msk         (0x1ul << EADC_INTSRC1_SPLIE18_Pos)               /*!< EADC_T::INTSRC1: SPLIE18 Mask          */

#define EADC_INTSRC2_SPLIE0_Pos          (0)                                               /*!< EADC_T::INTSRC2: SPLIE0 Position       */
#define EADC_INTSRC2_SPLIE0_Msk          (0x1ul << EADC_INTSRC2_SPLIE0_Pos)                /*!< EADC_T::INTSRC2: SPLIE0 Mask           */

#define EADC_INTSRC2_SPLIE1_Pos          (1)                                               /*!< EADC_T::INTSRC2: SPLIE1 Position       */
#define EADC_INTSRC2_SPLIE1_Msk          (0x1ul << EADC_INTSRC2_SPLIE1_Pos)                /*!< EADC_T::INTSRC2: SPLIE1 Mask           */

#define EADC_INTSRC2_SPLIE2_Pos          (2)                                               /*!< EADC_T::INTSRC2: SPLIE2 Position       */
#define EADC_INTSRC2_SPLIE2_Msk          (0x1ul << EADC_INTSRC2_SPLIE2_Pos)                /*!< EADC_T::INTSRC2: SPLIE2 Mask           */

#define EADC_INTSRC2_SPLIE3_Pos          (3)                                               /*!< EADC_T::INTSRC2: SPLIE3 Position       */
#define EADC_INTSRC2_SPLIE3_Msk          (0x1ul << EADC_INTSRC2_SPLIE3_Pos)                /*!< EADC_T::INTSRC2: SPLIE3 Mask           */

#define EADC_INTSRC2_SPLIE4_Pos          (4)                                               /*!< EADC_T::INTSRC2: SPLIE4 Position       */
#define EADC_INTSRC2_SPLIE4_Msk          (0x1ul << EADC_INTSRC2_SPLIE4_Pos)                /*!< EADC_T::INTSRC2: SPLIE4 Mask           */

#define EADC_INTSRC2_SPLIE5_Pos          (5)                                               /*!< EADC_T::INTSRC2: SPLIE5 Position       */
#define EADC_INTSRC2_SPLIE5_Msk          (0x1ul << EADC_INTSRC2_SPLIE5_Pos)                /*!< EADC_T::INTSRC2: SPLIE5 Mask           */

#define EADC_INTSRC2_SPLIE6_Pos          (6)                                               /*!< EADC_T::INTSRC2: SPLIE6 Position       */
#define EADC_INTSRC2_SPLIE6_Msk          (0x1ul << EADC_INTSRC2_SPLIE6_Pos)                /*!< EADC_T::INTSRC2: SPLIE6 Mask           */

#define EADC_INTSRC2_SPLIE7_Pos          (7)                                               /*!< EADC_T::INTSRC2: SPLIE7 Position       */
#define EADC_INTSRC2_SPLIE7_Msk          (0x1ul << EADC_INTSRC2_SPLIE7_Pos)                /*!< EADC_T::INTSRC2: SPLIE7 Mask           */

#define EADC_INTSRC2_SPLIE8_Pos          (8)                                               /*!< EADC_T::INTSRC2: SPLIE8 Position       */
#define EADC_INTSRC2_SPLIE8_Msk          (0x1ul << EADC_INTSRC2_SPLIE8_Pos)                /*!< EADC_T::INTSRC2: SPLIE8 Mask           */

#define EADC_INTSRC2_SPLIE9_Pos          (9)                                               /*!< EADC_T::INTSRC2: SPLIE9 Position       */
#define EADC_INTSRC2_SPLIE9_Msk          (0x1ul << EADC_INTSRC2_SPLIE9_Pos)                /*!< EADC_T::INTSRC2: SPLIE9 Mask           */

#define EADC_INTSRC2_SPLIE10_Pos         (10)                                              /*!< EADC_T::INTSRC2: SPLIE10 Position      */
#define EADC_INTSRC2_SPLIE10_Msk         (0x1ul << EADC_INTSRC2_SPLIE10_Pos)               /*!< EADC_T::INTSRC2: SPLIE10 Mask          */

#define EADC_INTSRC2_SPLIE11_Pos         (11)                                              /*!< EADC_T::INTSRC2: SPLIE11 Position      */
#define EADC_INTSRC2_SPLIE11_Msk         (0x1ul << EADC_INTSRC2_SPLIE11_Pos)               /*!< EADC_T::INTSRC2: SPLIE11 Mask          */

#define EADC_INTSRC2_SPLIE12_Pos         (12)                                              /*!< EADC_T::INTSRC2: SPLIE12 Position      */
#define EADC_INTSRC2_SPLIE12_Msk         (0x1ul << EADC_INTSRC2_SPLIE12_Pos)               /*!< EADC_T::INTSRC2: SPLIE12 Mask          */

#define EADC_INTSRC2_SPLIE13_Pos         (13)                                              /*!< EADC_T::INTSRC2: SPLIE13 Position      */
#define EADC_INTSRC2_SPLIE13_Msk         (0x1ul << EADC_INTSRC2_SPLIE13_Pos)               /*!< EADC_T::INTSRC2: SPLIE13 Mask          */

#define EADC_INTSRC2_SPLIE14_Pos         (14)                                              /*!< EADC_T::INTSRC2: SPLIE14 Position      */
#define EADC_INTSRC2_SPLIE14_Msk         (0x1ul << EADC_INTSRC2_SPLIE14_Pos)               /*!< EADC_T::INTSRC2: SPLIE14 Mask          */

#define EADC_INTSRC2_SPLIE15_Pos         (15)                                              /*!< EADC_T::INTSRC2: SPLIE15 Position      */
#define EADC_INTSRC2_SPLIE15_Msk         (0x1ul << EADC_INTSRC2_SPLIE15_Pos)               /*!< EADC_T::INTSRC2: SPLIE15 Mask          */

#define EADC_INTSRC2_SPLIE16_Pos         (16)                                              /*!< EADC_T::INTSRC2: SPLIE16 Position      */
#define EADC_INTSRC2_SPLIE16_Msk         (0x1ul << EADC_INTSRC2_SPLIE16_Pos)               /*!< EADC_T::INTSRC2: SPLIE16 Mask          */

#define EADC_INTSRC2_SPLIE17_Pos         (17)                                              /*!< EADC_T::INTSRC2: SPLIE17 Position      */
#define EADC_INTSRC2_SPLIE17_Msk         (0x1ul << EADC_INTSRC2_SPLIE17_Pos)               /*!< EADC_T::INTSRC2: SPLIE17 Mask          */

#define EADC_INTSRC2_SPLIE18_Pos         (18)                                              /*!< EADC_T::INTSRC2: SPLIE18 Position      */
#define EADC_INTSRC2_SPLIE18_Msk         (0x1ul << EADC_INTSRC2_SPLIE18_Pos)               /*!< EADC_T::INTSRC2: SPLIE18 Mask          */

#define EADC_INTSRC3_SPLIE0_Pos          (0)                                               /*!< EADC_T::INTSRC3: SPLIE0 Position       */
#define EADC_INTSRC3_SPLIE0_Msk          (0x1ul << EADC_INTSRC3_SPLIE0_Pos)                /*!< EADC_T::INTSRC3: SPLIE0 Mask           */

#define EADC_INTSRC3_SPLIE1_Pos          (1)                                               /*!< EADC_T::INTSRC3: SPLIE1 Position       */
#define EADC_INTSRC3_SPLIE1_Msk          (0x1ul << EADC_INTSRC3_SPLIE1_Pos)                /*!< EADC_T::INTSRC3: SPLIE1 Mask           */

#define EADC_INTSRC3_SPLIE2_Pos          (2)                                               /*!< EADC_T::INTSRC3: SPLIE2 Position       */
#define EADC_INTSRC3_SPLIE2_Msk          (0x1ul << EADC_INTSRC3_SPLIE2_Pos)                /*!< EADC_T::INTSRC3: SPLIE2 Mask           */

#define EADC_INTSRC3_SPLIE3_Pos          (3)                                               /*!< EADC_T::INTSRC3: SPLIE3 Position       */
#define EADC_INTSRC3_SPLIE3_Msk          (0x1ul << EADC_INTSRC3_SPLIE3_Pos)                /*!< EADC_T::INTSRC3: SPLIE3 Mask           */

#define EADC_INTSRC3_SPLIE4_Pos          (4)                                               /*!< EADC_T::INTSRC3: SPLIE4 Position       */
#define EADC_INTSRC3_SPLIE4_Msk          (0x1ul << EADC_INTSRC3_SPLIE4_Pos)                /*!< EADC_T::INTSRC3: SPLIE4 Mask           */

#define EADC_INTSRC3_SPLIE5_Pos          (5)                                               /*!< EADC_T::INTSRC3: SPLIE5 Position       */
#define EADC_INTSRC3_SPLIE5_Msk          (0x1ul << EADC_INTSRC3_SPLIE5_Pos)                /*!< EADC_T::INTSRC3: SPLIE5 Mask           */

#define EADC_INTSRC3_SPLIE6_Pos          (6)                                               /*!< EADC_T::INTSRC3: SPLIE6 Position       */
#define EADC_INTSRC3_SPLIE6_Msk          (0x1ul << EADC_INTSRC3_SPLIE6_Pos)                /*!< EADC_T::INTSRC3: SPLIE6 Mask           */

#define EADC_INTSRC3_SPLIE7_Pos          (7)                                               /*!< EADC_T::INTSRC3: SPLIE7 Position       */
#define EADC_INTSRC3_SPLIE7_Msk          (0x1ul << EADC_INTSRC3_SPLIE7_Pos)                /*!< EADC_T::INTSRC3: SPLIE7 Mask           */

#define EADC_INTSRC3_SPLIE8_Pos          (8)                                               /*!< EADC_T::INTSRC3: SPLIE8 Position       */
#define EADC_INTSRC3_SPLIE8_Msk          (0x1ul << EADC_INTSRC3_SPLIE8_Pos)                /*!< EADC_T::INTSRC3: SPLIE8 Mask           */

#define EADC_INTSRC3_SPLIE9_Pos          (9)                                               /*!< EADC_T::INTSRC3: SPLIE9 Position       */
#define EADC_INTSRC3_SPLIE9_Msk          (0x1ul << EADC_INTSRC3_SPLIE9_Pos)                /*!< EADC_T::INTSRC3: SPLIE9 Mask           */

#define EADC_INTSRC3_SPLIE10_Pos         (10)                                              /*!< EADC_T::INTSRC3: SPLIE10 Position      */
#define EADC_INTSRC3_SPLIE10_Msk         (0x1ul << EADC_INTSRC3_SPLIE10_Pos)               /*!< EADC_T::INTSRC3: SPLIE10 Mask          */

#define EADC_INTSRC3_SPLIE11_Pos         (11)                                              /*!< EADC_T::INTSRC3: SPLIE11 Position      */
#define EADC_INTSRC3_SPLIE11_Msk         (0x1ul << EADC_INTSRC3_SPLIE11_Pos)               /*!< EADC_T::INTSRC3: SPLIE11 Mask          */

#define EADC_INTSRC3_SPLIE12_Pos         (12)                                              /*!< EADC_T::INTSRC3: SPLIE12 Position      */
#define EADC_INTSRC3_SPLIE12_Msk         (0x1ul << EADC_INTSRC3_SPLIE12_Pos)               /*!< EADC_T::INTSRC3: SPLIE12 Mask          */

#define EADC_INTSRC3_SPLIE13_Pos         (13)                                              /*!< EADC_T::INTSRC3: SPLIE13 Position      */
#define EADC_INTSRC3_SPLIE13_Msk         (0x1ul << EADC_INTSRC3_SPLIE13_Pos)               /*!< EADC_T::INTSRC3: SPLIE13 Mask          */

#define EADC_INTSRC3_SPLIE14_Pos         (14)                                              /*!< EADC_T::INTSRC3: SPLIE14 Position      */
#define EADC_INTSRC3_SPLIE14_Msk         (0x1ul << EADC_INTSRC3_SPLIE14_Pos)               /*!< EADC_T::INTSRC3: SPLIE14 Mask          */

#define EADC_INTSRC3_SPLIE15_Pos         (15)                                              /*!< EADC_T::INTSRC3: SPLIE15 Position      */
#define EADC_INTSRC3_SPLIE15_Msk         (0x1ul << EADC_INTSRC3_SPLIE15_Pos)               /*!< EADC_T::INTSRC3: SPLIE15 Mask          */

#define EADC_INTSRC3_SPLIE16_Pos         (16)                                              /*!< EADC_T::INTSRC3: SPLIE16 Position      */
#define EADC_INTSRC3_SPLIE16_Msk         (0x1ul << EADC_INTSRC3_SPLIE16_Pos)               /*!< EADC_T::INTSRC3: SPLIE16 Mask          */

#define EADC_INTSRC3_SPLIE17_Pos         (17)                                              /*!< EADC_T::INTSRC3: SPLIE17 Position      */
#define EADC_INTSRC3_SPLIE17_Msk         (0x1ul << EADC_INTSRC3_SPLIE17_Pos)               /*!< EADC_T::INTSRC3: SPLIE17 Mask          */

#define EADC_INTSRC3_SPLIE18_Pos         (18)                                              /*!< EADC_T::INTSRC3: SPLIE18 Position      */
#define EADC_INTSRC3_SPLIE18_Msk         (0x1ul << EADC_INTSRC3_SPLIE18_Pos)               /*!< EADC_T::INTSRC3: SPLIE18 Mask          */

#define EADC_CMP_ADCMPEN_Pos             (0)                                               /*!< EADC_T::CMP: ADCMPEN Position          */
#define EADC_CMP_ADCMPEN_Msk             (0x1ul << EADC_CMP_ADCMPEN_Pos)                   /*!< EADC_T::CMP: ADCMPEN Mask              */

#define EADC_CMP_ADCMPIE_Pos             (1)                                               /*!< EADC_T::CMP: ADCMPIE Position          */
#define EADC_CMP_ADCMPIE_Msk             (0x1ul << EADC_CMP_ADCMPIE_Pos)                   /*!< EADC_T::CMP: ADCMPIE Mask              */

#define EADC_CMP_CMPCOND_Pos             (2)                                               /*!< EADC_T::CMP: CMPCOND Position          */
#define EADC_CMP_CMPCOND_Msk             (0x1ul << EADC_CMP_CMPCOND_Pos)                   /*!< EADC_T::CMP: CMPCOND Mask              */

#define EADC_CMP_CMPSPL_Pos              (3)                                               /*!< EADC_T::CMP: CMPSPL Position           */
#define EADC_CMP_CMPSPL_Msk              (0x1ful << EADC_CMP_CMPSPL_Pos)                   /*!< EADC_T::CMP: CMPSPL Mask               */

#define EADC_CMP_CMPMCNT_Pos             (8)                                               /*!< EADC_T::CMP: CMPMCNT Position          */
#define EADC_CMP_CMPMCNT_Msk             (0xful << EADC_CMP_CMPMCNT_Pos)                   /*!< EADC_T::CMP: CMPMCNT Mask              */

#define EADC_CMP_CMPWEN_Pos              (15)                                              /*!< EADC_T::CMP: CMPWEN Position           */
#define EADC_CMP_CMPWEN_Msk              (0x1ul << EADC_CMP_CMPWEN_Pos)                    /*!< EADC_T::CMP: CMPWEN Mask               */

#define EADC_CMP_CMPDAT_Pos              (16)                                              /*!< EADC_T::CMP: CMPDAT Position           */
#define EADC_CMP_CMPDAT_Msk              (0xffful << EADC_CMP_CMPDAT_Pos)                  /*!< EADC_T::CMP: CMPDAT Mask               */

#define EADC_CMP0_ADCMPEN_Pos            (0)                                               /*!< EADC_T::CMP0: ADCMPEN Position         */
#define EADC_CMP0_ADCMPEN_Msk            (0x1ul << EADC_CMP0_ADCMPEN_Pos)                  /*!< EADC_T::CMP0: ADCMPEN Mask             */

#define EADC_CMP0_ADCMPIE_Pos            (1)                                               /*!< EADC_T::CMP0: ADCMPIE Position         */
#define EADC_CMP0_ADCMPIE_Msk            (0x1ul << EADC_CMP0_ADCMPIE_Pos)                  /*!< EADC_T::CMP0: ADCMPIE Mask             */

#define EADC_CMP0_CMPCOND_Pos            (2)                                               /*!< EADC_T::CMP0: CMPCOND Position         */
#define EADC_CMP0_CMPCOND_Msk            (0x1ul << EADC_CMP0_CMPCOND_Pos)                  /*!< EADC_T::CMP0: CMPCOND Mask             */

#define EADC_CMP0_CMPSPL_Pos             (3)                                               /*!< EADC_T::CMP0: CMPSPL Position          */
#define EADC_CMP0_CMPSPL_Msk             (0x1ful << EADC_CMP0_CMPSPL_Pos)                  /*!< EADC_T::CMP0: CMPSPL Mask              */

#define EADC_CMP0_CMPMCNT_Pos            (8)                                               /*!< EADC_T::CMP0: CMPMCNT Position         */
#define EADC_CMP0_CMPMCNT_Msk            (0xful << EADC_CMP0_CMPMCNT_Pos)                  /*!< EADC_T::CMP0: CMPMCNT Mask             */

#define EADC_CMP0_CMPWEN_Pos             (15)                                              /*!< EADC_T::CMP0: CMPWEN Position          */
#define EADC_CMP0_CMPWEN_Msk             (0x1ul << EADC_CMP0_CMPWEN_Pos)                   /*!< EADC_T::CMP0: CMPWEN Mask              */

#define EADC_CMP0_CMPDAT_Pos             (16)                                              /*!< EADC_T::CMP0: CMPDAT Position          */
#define EADC_CMP0_CMPDAT_Msk             (0xffful << EADC_CMP0_CMPDAT_Pos)                 /*!< EADC_T::CMP0: CMPDAT Mask              */

#define EADC_CMP1_ADCMPEN_Pos            (0)                                               /*!< EADC_T::CMP1: ADCMPEN Position         */
#define EADC_CMP1_ADCMPEN_Msk            (0x1ul << EADC_CMP1_ADCMPEN_Pos)                  /*!< EADC_T::CMP1: ADCMPEN Mask             */

#define EADC_CMP1_ADCMPIE_Pos            (1)                                               /*!< EADC_T::CMP1: ADCMPIE Position         */
#define EADC_CMP1_ADCMPIE_Msk            (0x1ul << EADC_CMP1_ADCMPIE_Pos)                  /*!< EADC_T::CMP1: ADCMPIE Mask             */

#define EADC_CMP1_CMPCOND_Pos            (2)                                               /*!< EADC_T::CMP1: CMPCOND Position         */
#define EADC_CMP1_CMPCOND_Msk            (0x1ul << EADC_CMP1_CMPCOND_Pos)                  /*!< EADC_T::CMP1: CMPCOND Mask             */

#define EADC_CMP1_CMPSPL_Pos             (3)                                               /*!< EADC_T::CMP1: CMPSPL Position          */
#define EADC_CMP1_CMPSPL_Msk             (0x1ful << EADC_CMP1_CMPSPL_Pos)                  /*!< EADC_T::CMP1: CMPSPL Mask              */

#define EADC_CMP1_CMPMCNT_Pos            (8)                                               /*!< EADC_T::CMP1: CMPMCNT Position         */
#define EADC_CMP1_CMPMCNT_Msk            (0xful << EADC_CMP1_CMPMCNT_Pos)                  /*!< EADC_T::CMP1: CMPMCNT Mask             */

#define EADC_CMP1_CMPWEN_Pos             (15)                                              /*!< EADC_T::CMP1: CMPWEN Position          */
#define EADC_CMP1_CMPWEN_Msk             (0x1ul << EADC_CMP1_CMPWEN_Pos)                   /*!< EADC_T::CMP1: CMPWEN Mask              */

#define EADC_CMP1_CMPDAT_Pos             (16)                                              /*!< EADC_T::CMP1: CMPDAT Position          */
#define EADC_CMP1_CMPDAT_Msk             (0xffful << EADC_CMP1_CMPDAT_Pos)                 /*!< EADC_T::CMP1: CMPDAT Mask              */

#define EADC_CMP2_ADCMPEN_Pos            (0)                                               /*!< EADC_T::CMP2: ADCMPEN Position         */
#define EADC_CMP2_ADCMPEN_Msk            (0x1ul << EADC_CMP2_ADCMPEN_Pos)                  /*!< EADC_T::CMP2: ADCMPEN Mask             */

#define EADC_CMP2_ADCMPIE_Pos            (1)                                               /*!< EADC_T::CMP2: ADCMPIE Position         */
#define EADC_CMP2_ADCMPIE_Msk            (0x1ul << EADC_CMP2_ADCMPIE_Pos)                  /*!< EADC_T::CMP2: ADCMPIE Mask             */

#define EADC_CMP2_CMPCOND_Pos            (2)                                               /*!< EADC_T::CMP2: CMPCOND Position         */
#define EADC_CMP2_CMPCOND_Msk            (0x1ul << EADC_CMP2_CMPCOND_Pos)                  /*!< EADC_T::CMP2: CMPCOND Mask             */

#define EADC_CMP2_CMPSPL_Pos             (3)                                               /*!< EADC_T::CMP2: CMPSPL Position          */
#define EADC_CMP2_CMPSPL_Msk             (0x1ful << EADC_CMP2_CMPSPL_Pos)                  /*!< EADC_T::CMP2: CMPSPL Mask              */

#define EADC_CMP2_CMPMCNT_Pos            (8)                                               /*!< EADC_T::CMP2: CMPMCNT Position         */
#define EADC_CMP2_CMPMCNT_Msk            (0xful << EADC_CMP2_CMPMCNT_Pos)                  /*!< EADC_T::CMP2: CMPMCNT Mask             */

#define EADC_CMP2_CMPWEN_Pos             (15)                                              /*!< EADC_T::CMP2: CMPWEN Position          */
#define EADC_CMP2_CMPWEN_Msk             (0x1ul << EADC_CMP2_CMPWEN_Pos)                   /*!< EADC_T::CMP2: CMPWEN Mask              */

#define EADC_CMP2_CMPDAT_Pos             (16)                                              /*!< EADC_T::CMP2: CMPDAT Position          */
#define EADC_CMP2_CMPDAT_Msk             (0xffful << EADC_CMP2_CMPDAT_Pos)                 /*!< EADC_T::CMP2: CMPDAT Mask              */

#define EADC_CMP3_ADCMPEN_Pos            (0)                                               /*!< EADC_T::CMP3: ADCMPEN Position         */
#define EADC_CMP3_ADCMPEN_Msk            (0x1ul << EADC_CMP3_ADCMPEN_Pos)                  /*!< EADC_T::CMP3: ADCMPEN Mask             */

#define EADC_CMP3_ADCMPIE_Pos            (1)                                               /*!< EADC_T::CMP3: ADCMPIE Position         */
#define EADC_CMP3_ADCMPIE_Msk            (0x1ul << EADC_CMP3_ADCMPIE_Pos)                  /*!< EADC_T::CMP3: ADCMPIE Mask             */

#define EADC_CMP3_CMPCOND_Pos            (2)                                               /*!< EADC_T::CMP3: CMPCOND Position         */
#define EADC_CMP3_CMPCOND_Msk            (0x1ul << EADC_CMP3_CMPCOND_Pos)                  /*!< EADC_T::CMP3: CMPCOND Mask             */

#define EADC_CMP3_CMPSPL_Pos             (3)                                               /*!< EADC_T::CMP3: CMPSPL Position          */
#define EADC_CMP3_CMPSPL_Msk             (0x1ful << EADC_CMP3_CMPSPL_Pos)                  /*!< EADC_T::CMP3: CMPSPL Mask              */

#define EADC_CMP3_CMPMCNT_Pos            (8)                                               /*!< EADC_T::CMP3: CMPMCNT Position         */
#define EADC_CMP3_CMPMCNT_Msk            (0xful << EADC_CMP3_CMPMCNT_Pos)                  /*!< EADC_T::CMP3: CMPMCNT Mask             */

#define EADC_CMP3_CMPWEN_Pos             (15)                                              /*!< EADC_T::CMP3: CMPWEN Position          */
#define EADC_CMP3_CMPWEN_Msk             (0x1ul << EADC_CMP3_CMPWEN_Pos)                   /*!< EADC_T::CMP3: CMPWEN Mask              */

#define EADC_CMP3_CMPDAT_Pos             (16)                                              /*!< EADC_T::CMP3: CMPDAT Position          */
#define EADC_CMP3_CMPDAT_Msk             (0xffful << EADC_CMP3_CMPDAT_Pos)                 /*!< EADC_T::CMP3: CMPDAT Mask              */

#define EADC_STATUS0_VALID_Pos           (0)                                               /*!< EADC_T::STATUS0: VALID Position        */
#define EADC_STATUS0_VALID_Msk           (0xfffful << EADC_STATUS0_VALID_Pos)              /*!< EADC_T::STATUS0: VALID Mask            */

#define EADC_STATUS0_OV_Pos              (16)                                              /*!< EADC_T::STATUS0: OV Position           */
#define EADC_STATUS0_OV_Msk              (0xfffful << EADC_STATUS0_OV_Pos)                 /*!< EADC_T::STATUS0: OV Mask               */

#define EADC_STATUS1_VALID_Pos           (0)                                               /*!< EADC_T::STATUS1: VALID Position        */
#define EADC_STATUS1_VALID_Msk           (0x7ul << EADC_STATUS1_VALID_Pos)                 /*!< EADC_T::STATUS1: VALID Mask            */

#define EADC_STATUS1_OV_Pos              (16)                                              /*!< EADC_T::STATUS1: OV Position           */
#define EADC_STATUS1_OV_Msk              (0x7ul << EADC_STATUS1_OV_Pos)                    /*!< EADC_T::STATUS1: OV Mask               */

#define EADC_STATUS2_ADIF0_Pos           (0)                                               /*!< EADC_T::STATUS2: ADIF0 Position        */
#define EADC_STATUS2_ADIF0_Msk           (0x1ul << EADC_STATUS2_ADIF0_Pos)                 /*!< EADC_T::STATUS2: ADIF0 Mask            */

#define EADC_STATUS2_ADIF1_Pos           (1)                                               /*!< EADC_T::STATUS2: ADIF1 Position        */
#define EADC_STATUS2_ADIF1_Msk           (0x1ul << EADC_STATUS2_ADIF1_Pos)                 /*!< EADC_T::STATUS2: ADIF1 Mask            */

#define EADC_STATUS2_ADIF2_Pos           (2)                                               /*!< EADC_T::STATUS2: ADIF2 Position        */
#define EADC_STATUS2_ADIF2_Msk           (0x1ul << EADC_STATUS2_ADIF2_Pos)                 /*!< EADC_T::STATUS2: ADIF2 Mask            */

#define EADC_STATUS2_ADIF3_Pos           (3)                                               /*!< EADC_T::STATUS2: ADIF3 Position        */
#define EADC_STATUS2_ADIF3_Msk           (0x1ul << EADC_STATUS2_ADIF3_Pos)                 /*!< EADC_T::STATUS2: ADIF3 Mask            */

#define EADC_STATUS2_ADCMPF0_Pos         (4)                                               /*!< EADC_T::STATUS2: ADCMPF0 Position      */
#define EADC_STATUS2_ADCMPF0_Msk         (0x1ul << EADC_STATUS2_ADCMPF0_Pos)               /*!< EADC_T::STATUS2: ADCMPF0 Mask          */

#define EADC_STATUS2_ADCMPF1_Pos         (5)                                               /*!< EADC_T::STATUS2: ADCMPF1 Position      */
#define EADC_STATUS2_ADCMPF1_Msk         (0x1ul << EADC_STATUS2_ADCMPF1_Pos)               /*!< EADC_T::STATUS2: ADCMPF1 Mask          */

#define EADC_STATUS2_ADCMPF2_Pos         (6)                                               /*!< EADC_T::STATUS2: ADCMPF2 Position      */
#define EADC_STATUS2_ADCMPF2_Msk         (0x1ul << EADC_STATUS2_ADCMPF2_Pos)               /*!< EADC_T::STATUS2: ADCMPF2 Mask          */

#define EADC_STATUS2_ADCMPF3_Pos         (7)                                               /*!< EADC_T::STATUS2: ADCMPF3 Position      */
#define EADC_STATUS2_ADCMPF3_Msk         (0x1ul << EADC_STATUS2_ADCMPF3_Pos)               /*!< EADC_T::STATUS2: ADCMPF3 Mask          */

#define EADC_STATUS2_ADOVIF0_Pos         (8)                                               /*!< EADC_T::STATUS2: ADOVIF0 Position      */
#define EADC_STATUS2_ADOVIF0_Msk         (0x1ul << EADC_STATUS2_ADOVIF0_Pos)               /*!< EADC_T::STATUS2: ADOVIF0 Mask          */

#define EADC_STATUS2_ADOVIF1_Pos         (9)                                               /*!< EADC_T::STATUS2: ADOVIF1 Position      */
#define EADC_STATUS2_ADOVIF1_Msk         (0x1ul << EADC_STATUS2_ADOVIF1_Pos)               /*!< EADC_T::STATUS2: ADOVIF1 Mask          */

#define EADC_STATUS2_ADOVIF2_Pos         (10)                                              /*!< EADC_T::STATUS2: ADOVIF2 Position      */
#define EADC_STATUS2_ADOVIF2_Msk         (0x1ul << EADC_STATUS2_ADOVIF2_Pos)               /*!< EADC_T::STATUS2: ADOVIF2 Mask          */

#define EADC_STATUS2_ADOVIF3_Pos         (11)                                              /*!< EADC_T::STATUS2: ADOVIF3 Position      */
#define EADC_STATUS2_ADOVIF3_Msk         (0x1ul << EADC_STATUS2_ADOVIF3_Pos)               /*!< EADC_T::STATUS2: ADOVIF3 Mask          */

#define EADC_STATUS2_ADCMPO0_Pos         (12)                                              /*!< EADC_T::STATUS2: ADCMPO0 Position      */
#define EADC_STATUS2_ADCMPO0_Msk         (0x1ul << EADC_STATUS2_ADCMPO0_Pos)               /*!< EADC_T::STATUS2: ADCMPO0 Mask          */

#define EADC_STATUS2_ADCMPO1_Pos         (13)                                              /*!< EADC_T::STATUS2: ADCMPO1 Position      */
#define EADC_STATUS2_ADCMPO1_Msk         (0x1ul << EADC_STATUS2_ADCMPO1_Pos)               /*!< EADC_T::STATUS2: ADCMPO1 Mask          */

#define EADC_STATUS2_ADCMPO2_Pos         (14)                                              /*!< EADC_T::STATUS2: ADCMPO2 Position      */
#define EADC_STATUS2_ADCMPO2_Msk         (0x1ul << EADC_STATUS2_ADCMPO2_Pos)               /*!< EADC_T::STATUS2: ADCMPO2 Mask          */

#define EADC_STATUS2_ADCMPO3_Pos         (15)                                              /*!< EADC_T::STATUS2: ADCMPO3 Position      */
#define EADC_STATUS2_ADCMPO3_Msk         (0x1ul << EADC_STATUS2_ADCMPO3_Pos)               /*!< EADC_T::STATUS2: ADCMPO3 Mask          */

#define EADC_STATUS2_CHANNEL_Pos         (16)                                              /*!< EADC_T::STATUS2: CHANNEL Position      */
#define EADC_STATUS2_CHANNEL_Msk         (0x1ful << EADC_STATUS2_CHANNEL_Pos)              /*!< EADC_T::STATUS2: CHANNEL Mask          */

#define EADC_STATUS2_BUSY_Pos            (23)                                              /*!< EADC_T::STATUS2: BUSY Position         */
#define EADC_STATUS2_BUSY_Msk            (0x1ul << EADC_STATUS2_BUSY_Pos)                  /*!< EADC_T::STATUS2: BUSY Mask             */

#define EADC_STATUS2_ADOVIF_Pos          (24)                                              /*!< EADC_T::STATUS2: ADOVIF Position       */
#define EADC_STATUS2_ADOVIF_Msk          (0x1ul << EADC_STATUS2_ADOVIF_Pos)                /*!< EADC_T::STATUS2: ADOVIF Mask           */

#define EADC_STATUS2_STOVF_Pos           (25)                                              /*!< EADC_T::STATUS2: STOVF Position        */
#define EADC_STATUS2_STOVF_Msk           (0x1ul << EADC_STATUS2_STOVF_Pos)                 /*!< EADC_T::STATUS2: STOVF Mask            */

#define EADC_STATUS2_AVALID_Pos          (26)                                              /*!< EADC_T::STATUS2: AVALID Position       */
#define EADC_STATUS2_AVALID_Msk          (0x1ul << EADC_STATUS2_AVALID_Pos)                /*!< EADC_T::STATUS2: AVALID Mask           */

#define EADC_STATUS2_AOV_Pos             (27)                                              /*!< EADC_T::STATUS2: AOV Position          */
#define EADC_STATUS2_AOV_Msk             (0x1ul << EADC_STATUS2_AOV_Pos)                   /*!< EADC_T::STATUS2: AOV Mask              */

#define EADC_STATUS3_CURSPL_Pos          (0)                                               /*!< EADC_T::STATUS3: CURSPL Position       */
#define EADC_STATUS3_CURSPL_Msk          (0x1ful << EADC_STATUS3_CURSPL_Pos)               /*!< EADC_T::STATUS3: CURSPL Mask           */

#define EADC_DDAT0_RESULT_Pos            (0)                                               /*!< EADC_T::DDAT0: RESULT Position         */
#define EADC_DDAT0_RESULT_Msk            (0xfffful << EADC_DDAT0_RESULT_Pos)               /*!< EADC_T::DDAT0: RESULT Mask             */

#define EADC_DDAT0_OV_Pos                (16)                                              /*!< EADC_T::DDAT0: OV Position             */
#define EADC_DDAT0_OV_Msk                (0x1ul << EADC_DDAT0_OV_Pos)                      /*!< EADC_T::DDAT0: OV Mask                 */

#define EADC_DDAT0_VALID_Pos             (17)                                              /*!< EADC_T::DDAT0: VALID Position          */
#define EADC_DDAT0_VALID_Msk             (0x1ul << EADC_DDAT0_VALID_Pos)                   /*!< EADC_T::DDAT0: VALID Mask              */

#define EADC_DDAT1_RESULT_Pos            (0)                                               /*!< EADC_T::DDAT1: RESULT Position         */
#define EADC_DDAT1_RESULT_Msk            (0xfffful << EADC_DDAT1_RESULT_Pos)               /*!< EADC_T::DDAT1: RESULT Mask             */

#define EADC_DDAT1_OV_Pos                (16)                                              /*!< EADC_T::DDAT1: OV Position             */
#define EADC_DDAT1_OV_Msk                (0x1ul << EADC_DDAT1_OV_Pos)                      /*!< EADC_T::DDAT1: OV Mask                 */

#define EADC_DDAT1_VALID_Pos             (17)                                              /*!< EADC_T::DDAT1: VALID Position          */
#define EADC_DDAT1_VALID_Msk             (0x1ul << EADC_DDAT1_VALID_Pos)                   /*!< EADC_T::DDAT1: VALID Mask              */

#define EADC_DDAT2_RESULT_Pos            (0)                                               /*!< EADC_T::DDAT2: RESULT Position         */
#define EADC_DDAT2_RESULT_Msk            (0xfffful << EADC_DDAT2_RESULT_Pos)               /*!< EADC_T::DDAT2: RESULT Mask             */

#define EADC_DDAT2_OV_Pos                (16)                                              /*!< EADC_T::DDAT2: OV Position             */
#define EADC_DDAT2_OV_Msk                (0x1ul << EADC_DDAT2_OV_Pos)                      /*!< EADC_T::DDAT2: OV Mask                 */

#define EADC_DDAT2_VALID_Pos             (17)                                              /*!< EADC_T::DDAT2: VALID Position          */
#define EADC_DDAT2_VALID_Msk             (0x1ul << EADC_DDAT2_VALID_Pos)                   /*!< EADC_T::DDAT2: VALID Mask              */

#define EADC_DDAT3_RESULT_Pos            (0)                                               /*!< EADC_T::DDAT3: RESULT Position         */
#define EADC_DDAT3_RESULT_Msk            (0xfffful << EADC_DDAT3_RESULT_Pos)               /*!< EADC_T::DDAT3: RESULT Mask             */

#define EADC_DDAT3_OV_Pos                (16)                                              /*!< EADC_T::DDAT3: OV Position             */
#define EADC_DDAT3_OV_Msk                (0x1ul << EADC_DDAT3_OV_Pos)                      /*!< EADC_T::DDAT3: OV Mask                 */

#define EADC_DDAT3_VALID_Pos             (17)                                              /*!< EADC_T::DDAT3: VALID Position          */
#define EADC_DDAT3_VALID_Msk             (0x1ul << EADC_DDAT3_VALID_Pos)                   /*!< EADC_T::DDAT3: VALID Mask              */

#define EADC_PWRM_PWUPRDY_Pos            (0)                                               /*!< EADC_T::PWRM: PWUPRDY Position         */
#define EADC_PWRM_PWUPRDY_Msk            (0x1ul << EADC_PWRM_PWUPRDY_Pos)                  /*!< EADC_T::PWRM: PWUPRDY Mask             */

#define EADC_PWRM_PWUCALEN_Pos           (1)                                               /*!< EADC_T::PWRM: PWUCALEN Position        */
#define EADC_PWRM_PWUCALEN_Msk           (0x1ul << EADC_PWRM_PWUCALEN_Pos)                 /*!< EADC_T::PWRM: PWUCALEN Mask            */

#define EADC_PWRM_PWDMOD_Pos             (2)                                               /*!< EADC_T::PWRM: PWDMOD Position          */
#define EADC_PWRM_PWDMOD_Msk             (0x3ul << EADC_PWRM_PWDMOD_Pos)                   /*!< EADC_T::PWRM: PWDMOD Mask              */

#define EADC_PWRM_LDOSUT_Pos             (8)                                               /*!< EADC_T::PWRM: LDOSUT Position          */
#define EADC_PWRM_LDOSUT_Msk             (0xffful << EADC_PWRM_LDOSUT_Pos)                 /*!< EADC_T::PWRM: LDOSUT Mask              */

#define EADC_CALCTL_CALSTART_Pos         (1)                                               /*!< EADC_T::CALCTL: CALSTART Position      */
#define EADC_CALCTL_CALSTART_Msk         (0x1ul << EADC_CALCTL_CALSTART_Pos)               /*!< EADC_T::CALCTL: CALSTART Mask          */

#define EADC_CALCTL_CALDONE_Pos          (2)                                               /*!< EADC_T::CALCTL: CALDONE Position       */
#define EADC_CALCTL_CALDONE_Msk          (0x1ul << EADC_CALCTL_CALDONE_Pos)                /*!< EADC_T::CALCTL: CALDONE Mask           */

#define EADC_CALCTL_CALSEL_Pos           (3)                                               /*!< EADC_T::CALCTL: CALSEL Position        */
#define EADC_CALCTL_CALSEL_Msk           (0x1ul << EADC_CALCTL_CALSEL_Pos)                 /*!< EADC_T::CALCTL: CALSEL Mask            */

#define EADC_CALDWRD_CALWORD_Pos         (0)                                               /*!< EADC_T::CALDWRD: CALWORD Position      */
#define EADC_CALDWRD_CALWORD_Msk         (0x7ful << EADC_CALDWRD_CALWORD_Pos)              /*!< EADC_T::CALDWRD: CALWORD Mask          */

/**@}*/ /* EADC_CONST */
/**@}*/ /* end of EADC register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __EADC_REG_H__ */
