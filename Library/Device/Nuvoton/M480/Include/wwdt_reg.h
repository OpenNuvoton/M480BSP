/**************************************************************************//**
 * @file     wwdt_reg.h
 * @version  V1.00
 * @brief    WWDT register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __WWDT_REG_H__
#define __WWDT_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup WWDT Window Watchdog Timer(WWDT)
    Memory Mapped Structure for WWDT Controller
@{ */

typedef struct
{


    /**
@var WWDT_T::RLDCNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">RLDCNT
</font><br><p> <font size="2">
Offset: 0x00  WWDT Reload Counter Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>RLDCNT</td><td><div style="word-wrap: break-word;"><b>WWDT Reload Counter Register
</b><br>
Writing 0x00005AA5 to this register will reload the WWDT counter value to 0x3F.
<br>
Note: User can only write WWDT_RLDCNT register to reload WWDT counter value when current WWDT counter value between 0 and CMPDAT (WWDT_CTL[21:16])
<br>
If user writes WWDT_RLDCNT when current WWDT counter value is larger than CMPDAT , WWDT reset signal will generate immediately.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var WWDT_T::CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL
</font><br><p> <font size="2">
Offset: 0x04  WWDT Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>WWDTEN</td><td><div style="word-wrap: break-word;"><b>WWDT Enable Control Bit
</b><br>
Set this bit to enable WWDT counter counting.
<br>
0 = WWDT counter is stopped.
<br>
1 = WWDT counter is starting counting.
<br>
</div></td></tr><tr><td>
[1]</td><td>INTEN</td><td><div style="word-wrap: break-word;"><b>WWDT Interrupt Enable Control Bit
</b><br>
If this bit is enabled, the WWDT counter compare match interrupt signal is generated and inform to CPU.
<br>
0 = WWDT counter compare match interrupt Disabled.
<br>
1 = WWDT counter compare match interrupt Enabled.
<br>
</div></td></tr><tr><td>
[11:8]</td><td>PSCSEL</td><td><div style="word-wrap: break-word;"><b>WWDT Counter Prescale Period Selection
</b><br>
0000 = Pre-scale is 1; Max time-out period is 1 * 64 * WWDT_CLK.
<br>
0001 = Pre-scale is 2; Max time-out period is 2 * 64 * WWDT_CLK.
<br>
0010 = Pre-scale is 4; Max time-out period is 4 * 64 * WWDT_CLK.
<br>
0011 = Pre-scale is 8; Max time-out period is 8 * 64 * WWDT_CLK.
<br>
0100 = Pre-scale is 16; Max time-out period is 16 * 64 * WWDT_CLK.
<br>
0101 = Pre-scale is 32; Max time-out period is 32 * 64 * WWDT_CLK.
<br>
0110 = Pre-scale is 64; Max time-out period is 64 * 64 * WWDT_CLK.
<br>
0111 = Pre-scale is 128; Max time-out period is 128 * 64 * WWDT_CLK.
<br>
1000 = Pre-scale is 192; Max time-out period is 192 * 64 * WWDT_CLK.
<br>
1001 = Pre-scale is 256; Max time-out period is 256 * 64 * WWDT_CLK.
<br>
1010 = Pre-scale is 384; Max time-out period is 384 * 64 * WWDT_CLK.
<br>
1011 = Pre-scale is 512; Max time-out period is 512 * 64 * WWDT_CLK.
<br>
1100 = Pre-scale is 768; Max time-out period is 768 * 64 * WWDT_CLK.
<br>
1101 = Pre-scale is 1024; Max time-out period is 1024 * 64 * WWDT_CLK.
<br>
1110 = Pre-scale is 1536; Max time-out period is 1536 * 64 * WWDT_CLK.
<br>
1111 = Pre-scale is 2048; Max time-out period is 2048 * 64 * WWDT_CLK.
<br>
</div></td></tr><tr><td>
[21:16]</td><td>CMPDAT</td><td><div style="word-wrap: break-word;"><b>WWDT Window Compare Register
</b><br>
Set this register to adjust the valid reload window.
<br>
Note: User can only write WWDT_RLDCNT register to reload WWDT counter value when current WWDT counter value between 0 and CMPDAT
<br>
If user writes WWDT_RLDCNT register when current WWDT counter value larger than CMPDAT, WWDT reset signal will generate immediately.
<br>
</div></td></tr><tr><td>
[31]</td><td>ICEDEBUG</td><td><div style="word-wrap: break-word;"><b>ICE Debug Mode Acknowledge Disable Control
</b><br>
0 = ICE debug mode acknowledgement effects WWDT counting.
<br>
WWDT down counter will be held while CPU is held by ICE.
<br>
1 = ICE debug mode acknowledgement Disabled.
<br>
WWDT down counter will keep going no matter CPU is held by ICE or not.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var WWDT_T::STATUS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STATUS
</font><br><p> <font size="2">
Offset: 0x08  WWDT Status Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>WWDTIF</td><td><div style="word-wrap: break-word;"><b>WWDT Compare Match Interrupt Flag
</b><br>
This bit indicates the interrupt flag status of WWDT while WWDT counter value matches CMPDAT (WWDT_CTL[21:16]).
<br>
0 = No effect.
<br>
1 = WWDT counter value matches CMPDAT.
<br>
Note: This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[1]</td><td>WWDTRF</td><td><div style="word-wrap: break-word;"><b>WWDT Timer-out Reset Flag
</b><br>
This bit indicates the system has been reset by WWDT time-out reset or not.
<br>
0 = WWDT time-out reset did not occur.
<br>
1 = WWDT time-out reset occurred.
<br>
Note: This bit is cleared by writing 1 to it.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var WWDT_T::CNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CNT
</font><br><p> <font size="2">
Offset: 0x0C  WWDT Counter Value Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[5:0]</td><td>CNTDAT</td><td><div style="word-wrap: break-word;"><b>WWDT Counter Value
</b><br>
CNTDAT will be updated continuously to monitor 6-bit WWDT down counter value.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __O  uint32_t RLDCNT;                /*!< [0x0000] WWDT Reload Counter Register                                     */
    __IO uint32_t CTL;                   /*!< [0x0004] WWDT Control Register                                            */
    __IO uint32_t STATUS;                /*!< [0x0008] WWDT Status Register                                             */
    __I  uint32_t CNT;                   /*!< [0x000c] WWDT Counter Value Register                                      */

} WWDT_T;

/**
    @addtogroup WWDT_CONST WWDT Bit Field Definition
    Constant Definitions for WWDT Controller
@{ */

#define WWDT_RLDCNT_RLDCNT_Pos           (0)                                               /*!< WWDT_T::RLDCNT: RLDCNT Position        */
#define WWDT_RLDCNT_RLDCNT_Msk           (0xfffffffful << WWDT_RLDCNT_RLDCNT_Pos)          /*!< WWDT_T::RLDCNT: RLDCNT Mask            */

#define WWDT_CTL_WWDTEN_Pos              (0)                                               /*!< WWDT_T::CTL: WWDTEN Position           */
#define WWDT_CTL_WWDTEN_Msk              (0x1ul << WWDT_CTL_WWDTEN_Pos)                    /*!< WWDT_T::CTL: WWDTEN Mask               */

#define WWDT_CTL_INTEN_Pos               (1)                                               /*!< WWDT_T::CTL: INTEN Position            */
#define WWDT_CTL_INTEN_Msk               (0x1ul << WWDT_CTL_INTEN_Pos)                     /*!< WWDT_T::CTL: INTEN Mask                */

#define WWDT_CTL_PSCSEL_Pos              (8)                                               /*!< WWDT_T::CTL: PSCSEL Position           */
#define WWDT_CTL_PSCSEL_Msk              (0xful << WWDT_CTL_PSCSEL_Pos)                    /*!< WWDT_T::CTL: PSCSEL Mask               */

#define WWDT_CTL_CMPDAT_Pos              (16)                                              /*!< WWDT_T::CTL: CMPDAT Position           */
#define WWDT_CTL_CMPDAT_Msk              (0x3ful << WWDT_CTL_CMPDAT_Pos)                   /*!< WWDT_T::CTL: CMPDAT Mask               */

#define WWDT_CTL_ICEDEBUG_Pos            (31)                                              /*!< WWDT_T::CTL: ICEDEBUG Position         */
#define WWDT_CTL_ICEDEBUG_Msk            (0x1ul << WWDT_CTL_ICEDEBUG_Pos)                  /*!< WWDT_T::CTL: ICEDEBUG Mask             */

#define WWDT_STATUS_WWDTIF_Pos           (0)                                               /*!< WWDT_T::STATUS: WWDTIF Position        */
#define WWDT_STATUS_WWDTIF_Msk           (0x1ul << WWDT_STATUS_WWDTIF_Pos)                 /*!< WWDT_T::STATUS: WWDTIF Mask            */

#define WWDT_STATUS_WWDTRF_Pos           (1)                                               /*!< WWDT_T::STATUS: WWDTRF Position        */
#define WWDT_STATUS_WWDTRF_Msk           (0x1ul << WWDT_STATUS_WWDTRF_Pos)                 /*!< WWDT_T::STATUS: WWDTRF Mask            */

#define WWDT_CNT_CNTDAT_Pos              (0)                                               /*!< WWDT_T::CNT: CNTDAT Position           */
#define WWDT_CNT_CNTDAT_Msk              (0x3ful << WWDT_CNT_CNTDAT_Pos)                   /*!< WWDT_T::CNT: CNTDAT Mask               */

/**@}*/ /* WWDT_CONST */
/**@}*/ /* end of WWDT register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __WWDT_REG_H__ */
