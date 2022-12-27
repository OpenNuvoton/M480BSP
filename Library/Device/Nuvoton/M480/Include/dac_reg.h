/**************************************************************************//**
 * @file     dac_reg.h
 * @version  V1.00
 * @brief    DAC register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __DAC_REG_H__
#define __DAC_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
  @{
*/

/**
    @addtogroup DAC Digital to Analog Converter(DAC)
    Memory Mapped Structure for DAC Controller
@{ */

typedef struct
{


    /**
@var DAC_T::CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL
</font><br><p> <font size="2">
Offset: 0x00  DAC Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>DACEN</td><td><div style="word-wrap: break-word;"><b>DAC Enable Bit
</b><br>
0 = DAC is Disabled.
<br>
1 = DAC is Enabled.
<br>
</div></td></tr><tr><td>
[1]</td><td>DACIEN</td><td><div style="word-wrap: break-word;"><b>DAC Interrupt Enable Bit
</b><br>
0 = Interrupt is Disabled.
<br>
1 = Interrupt is Enabled.
<br>
</div></td></tr><tr><td>
[2]</td><td>DMAEN</td><td><div style="word-wrap: break-word;"><b>DMA Mode Enable Bit
</b><br>
0 = DMA mode Disabled.
<br>
1 = DMA mode Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>DMAURIEN</td><td><div style="word-wrap: break-word;"><b>DMA Under-run Interrupt Enable Bit
</b><br>
0 = DMA under-run interrupt Disabled.
<br>
1 = DMA under-run interrupt Enabled.
<br>
</div></td></tr><tr><td>
[4]</td><td>TRGEN</td><td><div style="word-wrap: break-word;"><b>Trigger Mode Enable Bit
</b><br>
0 = DAC event trigger mode Disabled.
<br>
1 = DAC event trigger mode Enabled.
<br>
</div></td></tr><tr><td>
[7:5]</td><td>TRGSEL</td><td><div style="word-wrap: break-word;"><b>Trigger Source Selection
</b><br>
000 = Software trigger.
<br>
001 = External pin DAC0_ST trigger.
<br>
010 = Timer 0 trigger.
<br>
011 = Timer 1 trigger.
<br>
100 = Timer 2 trigger.
<br>
101 = Timer 3 trigger.
<br>
110 = EPWM0 trigger.
<br>
111 = EPWM1 trigger.
<br>
</div></td></tr><tr><td>
[8]</td><td>BYPASS</td><td><div style="word-wrap: break-word;"><b>Bypass Buffer Mode
</b><br>
0 = Output voltage buffer Enabled.
<br>
1 = Output voltage buffer Disabled.
<br>
</div></td></tr><tr><td>
[10]</td><td>LALIGN</td><td><div style="word-wrap: break-word;"><b>DAC Data Left-aligned Enabled Control
</b><br>
0 = Right alignment.
<br>
1 = Left alignment.
<br>
</div></td></tr><tr><td>
[13:12]</td><td>ETRGSEL</td><td><div style="word-wrap: break-word;"><b>External Pin Trigger Selection
</b><br>
00 = Low level trigger.
<br>
01 = High level trigger.
<br>
10 = Falling edge trigger.
<br>
11 = Rising edge trigger.
<br>
</div></td></tr><tr><td>
[15:14]</td><td>BWSEL</td><td><div style="word-wrap: break-word;"><b>DAC Data Bit-width Selection
</b><br>
00 = data is 12 bits.
<br>
01 = data is 8 bits.
<br>
Others = reserved.
<br>
</div></td></tr><tr><td>
[16]</td><td>GRPEN</td><td><div style="word-wrap: break-word;"><b>DAC Group Mode Enable Bit
</b><br>
0 = DAC0 and DAC1 are not grouped.
<br>
1 = DAC0 and DAC1 are grouped.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var DAC_T::SWTRG

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SWTRG
</font><br><p> <font size="2">
Offset: 0x04  DAC Software Trigger Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>SWTRG</td><td><div style="word-wrap: break-word;"><b>Software Trigger
</b><br>
0 = Software trigger Disabled.
<br>
1 = Software trigger Enabled.
<br>
User writes this bit to generate one shot pulse and it is cleared to 0 by hardware automatically; Reading this bit will always get 0.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var DAC_T::DAT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DAT
</font><br><p> <font size="2">
Offset: 0x08  DAC Data Holding Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[15:0]</td><td>DACDAT</td><td><div style="word-wrap: break-word;"><b>DAC 12-bit Holding Data
</b><br>
These bits are written by user software which specifies 12-bit conversion data for DAC output
<br>
The unused bits (DAC_DAT[3:0] in left-alignment mode and DAC_DAT[15:12] in right alignment mode) are ignored by DAC controller hardware.
<br>
12 bit left alignment: user has to load data into DAC_DAT[15:4] bits.
<br>
12 bit right alignment: user has to load data into DAC_DAT[11:0] bits.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var DAC_T::DATOUT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">DATOUT
</font><br><p> <font size="2">
Offset: 0x0C  DAC Data Output Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[11:0]</td><td>DATOUT</td><td><div style="word-wrap: break-word;"><b>DAC 12-bit Output Data
</b><br>
These bits are current digital data for DAC output conversion.
<br>
It is loaded from DAC_DAT register and user cannot write it directly.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var DAC_T::STATUS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STATUS
</font><br><p> <font size="2">
Offset: 0x10  DAC Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>FINISH</td><td><div style="word-wrap: break-word;"><b>DAC Conversion Complete Finish Flag
</b><br>
0 = DAC is in conversion state.
<br>
1 = DAC conversion finish.
<br>
This bit set to 1 when conversion time counter counts to SETTLET
<br>
It is cleared to 0 when DAC starts a new conversion
<br>
User writes 1 to clear this bit to 0.
<br>
</div></td></tr><tr><td>
[1]</td><td>DMAUDR</td><td><div style="word-wrap: break-word;"><b>DMA Under-run Interrupt Flag
</b><br>
0 = No DMA under-run error condition occurred.
<br>
1 = DMA under-run error condition occurred.
<br>
User writes 1 to clear this bit.
<br>
</div></td></tr><tr><td>
[8]</td><td>BUSY</td><td><div style="word-wrap: break-word;"><b>DAC Busy Flag (Read Only)
</b><br>
0 = DAC is ready for next conversion.
<br>
1 = DAC is busy in conversion.
<br>
This is read only bit.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var DAC_T::TCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">TCTL
</font><br><p> <font size="2">
Offset: 0x14  DAC Timing Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[9:0]</td><td>SETTLET</td><td><div style="word-wrap: break-word;"><b>DAC Output Settling Time
</b><br>
User software needs to write appropriate value to these bits to meet DAC conversion settling time base on PCLK (APB clock) speed.
<br>
For example, DAC controller clock speed is 80MHz and DAC conversion settling time is 1 us, SETTLETvalue must be greater than 0x50.
<br>
SELTTLET = DAC controller clock speed x settling time.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CTL;                   /*!< [0x0000] DAC Control Register                                             */
    __IO uint32_t SWTRG;                 /*!< [0x0004] DAC Software Trigger Control Register                            */
    __IO uint32_t DAT;                   /*!< [0x0008] DAC Data Holding Register                                        */
    __I  uint32_t DATOUT;                /*!< [0x000c] DAC Data Output Register                                         */
    __IO uint32_t STATUS;                /*!< [0x0010] DAC Status Register                                              */
    __IO uint32_t TCTL;                  /*!< [0x0014] DAC Timing Control Register                                      */

} DAC_T;

/**
    @addtogroup DAC_CONST DAC Bit Field Definition
    Constant Definitions for DAC Controller
@{ */

#define DAC_CTL_DACEN_Pos                (0)                                               /*!< DAC_T::CTL: DACEN Position             */
#define DAC_CTL_DACEN_Msk                (0x1ul << DAC_CTL_DACEN_Pos)                      /*!< DAC_T::CTL: DACEN Mask                 */

#define DAC_CTL_DACIEN_Pos               (1)                                               /*!< DAC_T::CTL: DACIEN Position            */
#define DAC_CTL_DACIEN_Msk               (0x1ul << DAC_CTL_DACIEN_Pos)                     /*!< DAC_T::CTL: DACIEN Mask                */

#define DAC_CTL_DMAEN_Pos                (2)                                               /*!< DAC_T::CTL: DMAEN Position             */
#define DAC_CTL_DMAEN_Msk                (0x1ul << DAC_CTL_DMAEN_Pos)                      /*!< DAC_T::CTL: DMAEN Mask                 */

#define DAC_CTL_DMAURIEN_Pos             (3)                                               /*!< DAC_T::CTL: DMAURIEN Position          */
#define DAC_CTL_DMAURIEN_Msk             (0x1ul << DAC_CTL_DMAURIEN_Pos)                   /*!< DAC_T::CTL: DMAURIEN Mask              */

#define DAC_CTL_TRGEN_Pos                (4)                                               /*!< DAC_T::CTL: TRGEN Position             */
#define DAC_CTL_TRGEN_Msk                (0x1ul << DAC_CTL_TRGEN_Pos)                      /*!< DAC_T::CTL: TRGEN Mask                 */

#define DAC_CTL_TRGSEL_Pos               (5)                                               /*!< DAC_T::CTL: TRGSEL Position            */
#define DAC_CTL_TRGSEL_Msk               (0x7ul << DAC_CTL_TRGSEL_Pos)                     /*!< DAC_T::CTL: TRGSEL Mask                */

#define DAC_CTL_BYPASS_Pos               (8)                                               /*!< DAC_T::CTL: BYPASS Position            */
#define DAC_CTL_BYPASS_Msk               (0x1ul << DAC_CTL_BYPASS_Pos)                     /*!< DAC_T::CTL: BYPASS Mask                */

#define DAC_CTL_LALIGN_Pos               (10)                                              /*!< DAC_T::CTL: LALIGN Position            */
#define DAC_CTL_LALIGN_Msk               (0x1ul << DAC_CTL_LALIGN_Pos)                     /*!< DAC_T::CTL: LALIGN Mask                */

#define DAC_CTL_ETRGSEL_Pos              (12)                                              /*!< DAC_T::CTL: ETRGSEL Position           */
#define DAC_CTL_ETRGSEL_Msk              (0x3ul << DAC_CTL_ETRGSEL_Pos)                    /*!< DAC_T::CTL: ETRGSEL Mask               */

#define DAC_CTL_BWSEL_Pos                (14)                                              /*!< DAC_T::CTL: BWSEL Position             */
#define DAC_CTL_BWSEL_Msk                (0x3ul << DAC_CTL_BWSEL_Pos)                      /*!< DAC_T::CTL: BWSEL Mask                 */

#define DAC_CTL_GRPEN_Pos                (16)                                              /*!< DAC_T::CTL: GRPEN Position             */
#define DAC_CTL_GRPEN_Msk                (0x1ul << DAC_CTL_GRPEN_Pos)                      /*!< DAC_T::CTL: GRPEN Mask                 */

#define DAC_SWTRG_SWTRG_Pos              (0)                                               /*!< DAC_T::SWTRG: SWTRG Position           */
#define DAC_SWTRG_SWTRG_Msk              (0x1ul << DAC_SWTRG_SWTRG_Pos)                    /*!< DAC_T::SWTRG: SWTRG Mask               */

#define DAC_DAT_DACDAT_Pos               (0)                                               /*!< DAC_T::DAT: DACDAT Position            */
#define DAC_DAT_DACDAT_Msk               (0xfffful << DAC_DAT_DACDAT_Pos)                  /*!< DAC_T::DAT: DACDAT Mask                */

#define DAC_DATOUT_DATOUT_Pos            (0)                                               /*!< DAC_T::DATOUT: DATOUT Position         */
#define DAC_DATOUT_DATOUT_Msk            (0xffful << DAC_DATOUT_DATOUT_Pos)                /*!< DAC_T::DATOUT: DATOUT Mask             */

#define DAC_STATUS_FINISH_Pos            (0)                                               /*!< DAC_T::STATUS: FINISH Position         */
#define DAC_STATUS_FINISH_Msk            (0x1ul << DAC_STATUS_FINISH_Pos)                  /*!< DAC_T::STATUS: FINISH Mask             */

#define DAC_STATUS_DMAUDR_Pos            (1)                                               /*!< DAC_T::STATUS: DMAUDR Position         */
#define DAC_STATUS_DMAUDR_Msk            (0x1ul << DAC_STATUS_DMAUDR_Pos)                  /*!< DAC_T::STATUS: DMAUDR Mask             */

#define DAC_STATUS_BUSY_Pos              (8)                                               /*!< DAC_T::STATUS: BUSY Position           */
#define DAC_STATUS_BUSY_Msk              (0x1ul << DAC_STATUS_BUSY_Pos)                    /*!< DAC_T::STATUS: BUSY Mask               */

#define DAC_TCTL_SETTLET_Pos             (0)                                               /*!< DAC_T::TCTL: SETTLET Position          */
#define DAC_TCTL_SETTLET_Msk             (0x3fful << DAC_TCTL_SETTLET_Pos)                 /*!< DAC_T::TCTL: SETTLET Mask              */

/**@}*/ /* DAC_CONST */
/**@}*/ /* end of DAC register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __DAC_REG_H__ */
