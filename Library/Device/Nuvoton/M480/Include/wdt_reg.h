/**************************************************************************//**
 * @file     wdt_reg.h
 * @version  V1.00
 * @brief    WDT register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __WDT_REG_H__
#define __WDT_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup WDT Watch Dog Timer Controller(WDT)
    Memory Mapped Structure for WDT Controller
@{ */

typedef struct
{


    /**
@var WDT_T::CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL
</font><br><p> <font size="2">
Offset: 0x00  WDT Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>RSTCNT</td><td><div style="word-wrap: break-word;"><b>Reset WDT Up Counter (Write Protect)
</b><br>
0 = No effect.
<br>
1 = Reset the internal 18-bit WDT up counter value.
<br>
Note1: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
Note2: This bit will be automatically cleared by hardware.
<br>
</div></td></tr><tr><td>
[1]</td><td>RSTEN</td><td><div style="word-wrap: break-word;"><b>WDT Time-out Reset Enable Control (Write Protect)
</b><br>
Setting this bit will enable the WDT time-out reset function If the WDT up counter value has not been cleared after the specific WDT reset delay period expires.
<br>
0 = WDT time-out reset function Disabled.
<br>
1 = WDT time-out reset function Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[2]</td><td>RSTF</td><td><div style="word-wrap: break-word;"><b>WDT Time-out Reset Flag
</b><br>
This bit indicates the system has been reset by WDT time-out reset or not.
<br>
0 = WDT time-out reset did not occur.
<br>
1 = WDT time-out reset occurred.
<br>
Note: This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[3]</td><td>IF</td><td><div style="word-wrap: break-word;"><b>WDT Time-out Interrupt Flag
</b><br>
This bit will set to 1 while WDT up counter value reaches the selected WDT time-out interval
<br>
0 = WDT time-out interrupt did not occur.
<br>
1 = WDT time-out interrupt occurred.
<br>
Note: This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[4]</td><td>WKEN</td><td><div style="word-wrap: break-word;"><b>WDT Time-out Wake-up Function Control (Write Protect)
</b><br>
If this bit is set to 1, while WDT time-out interrupt flag IF (WDT_CTL[3]) is generated to 1 and interrupt enable bit INTEN (WDT_CTL[6]) is enabled, the WDT time-out interrupt signal will generate a wake-up trigger event to chip.
<br>
0 = Wake-up trigger event Disabled if WDT time-out interrupt signal generated.
<br>
1 = Wake-up trigger event Enabled if WDT time-out interrupt signal generated.
<br>
Note1: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
Note2: Chip can be woken-up by WDT time-out interrupt signal generated only if WDT clock source is selected to 10 kHz internal low speed RC oscillator (LIRC) or LXT.
<br>
</div></td></tr><tr><td>
[5]</td><td>WKF</td><td><div style="word-wrap: break-word;"><b>WDT Time-out Wake-up Flag (Write Protect)
</b><br>
This bit indicates the interrupt wake-up flag status of WDT
<br>
0 = WDT does not cause chip wake-up.
<br>
1 = Chip wake-up from Idle or Power-down mode if WDT time-out interrupt signal generated.
<br>
Note1: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
Note2: This bit is cleared by writing 1 to it.
<br>
</div></td></tr><tr><td>
[6]</td><td>INTEN</td><td><div style="word-wrap: break-word;"><b>WDT Time-out Interrupt Enable Control (Write Protect)
</b><br>
If this bit is enabled, the WDT time-out interrupt signal is generated and inform to CPU.
<br>
0 = WDT time-out interrupt Disabled.
<br>
1 = WDT time-out interrupt Enabled.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[7]</td><td>WDTEN</td><td><div style="word-wrap: break-word;"><b>WDT Enable Control (Write Protect)
</b><br>
0 = WDT Disabled (This action will reset the internal up counter value).
<br>
1 = WDT Enabled.
<br>
Note1: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
Note2: If CWDTEN[2:0] (combined by Config0[31] and Config0[4:3]) bits is not configure to 111, this bit is forced as 1 and user cannot change this bit to 0.
<br>
</div></td></tr><tr><td>
[10:8]</td><td>TOUTSEL</td><td><div style="word-wrap: break-word;"><b>WDT Time-out Interval Selection (Write Protect)
</b><br>
These three bits select the time-out interval period for the WDT.
<br>
000 = 24 * WDT_CLK.
<br>
001 = 26 * WDT_CLK.
<br>
010 = 28 * WDT_CLK.
<br>
011 = 210 * WDT_CLK.
<br>
100 = 212 * WDT_CLK.
<br>
101 = 214 * WDT_CLK.
<br>
110 = 216 * WDT_CLK.
<br>
111 = 218 * WDT_CLK.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr><tr><td>
[30]</td><td>SYNC</td><td><div style="word-wrap: break-word;"><b>WDT Enable Control SYNC Flag Indicator (Read Only)
</b><br>
If user execute enable/disable WDTEN (WDT_CTL[7]), this flag can be indicated enable/disable WDTEN function is completed or not.
<br>
0 = Set WDTEN bit is completed.
<br>
1 = Set WDTEN bit is synchronizing and not become active yet..
<br>
Note: Perform enable or disable WDTEN bit needs 2 * WDT_CLK period to become active.
<br>
</div></td></tr><tr><td>
[31]</td><td>ICEDEBUG</td><td><div style="word-wrap: break-word;"><b>ICE Debug Mode Acknowledge Disable Control (Write Protect)
</b><br>
0 = ICE debug mode acknowledgement affects WDT counting.
<br>
WDT up counter will be held while CPU is held by ICE.
<br>
1 = ICE debug mode acknowledgement Disabled.
<br>
WDT up counter will keep going no matter CPU is held by ICE or not.
<br>
Note: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var WDT_T::ALTCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">ALTCTL
</font><br><p> <font size="2">
Offset: 0x04  WDT Alternative Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[1:0]</td><td>RSTDSEL</td><td><div style="word-wrap: break-word;"><b>WDT Reset Delay Selection (Write Protect)
</b><br>
When WDT time-out happened, user has a time named WDT Reset Delay Period to clear WDT counter by setting RSTCNT (WDT_CTL[0]) to prevent WDT time-out reset happened
<br>
User can select a suitable setting of RSTDSEL for different WDT Reset Delay Period.
<br>
00 = WDT Reset Delay Period is 1026 * WDT_CLK.
<br>
01 = WDT Reset Delay Period is 130 * WDT_CLK.
<br>
10 = WDT Reset Delay Period is 18 * WDT_CLK.
<br>
11 = WDT Reset Delay Period is 3 * WDT_CLK.
<br>
Note1: This bit is write protected. Refer to the SYS_REGLCTL register.
<br>
Note2: This register will be reset to 0 if WDT time-out reset happened.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var WDT_T::RSTCNT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">RSTCNT
</font><br><p> <font size="2">
Offset: 0x08  WDT Reset Counter Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[31:0]</td><td>RSTCNT</td><td><div style="word-wrap: break-word;"><b>WDT Reset Counter Register
</b><br>
Writing 0x00005AA5 to this field will reset the internal 18-bit WDT up counter value to 0.
<br>
Note: Perform RSTCNT to reset counter needs 2 * WDT_CLK period to become active.
<br>
Note: RSTCNT (WDT_CTL[0]) bit is a write protected bit
<br>
RSTCNT (WDT_RSTCNT[31:0]) bits are not write protected.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CTL;                   /*!< [0x0000] WDT Control Register                                             */
    __IO uint32_t ALTCTL;                /*!< [0x0004] WDT Alternative Control Register                                 */
    __O  uint32_t RSTCNT;                /*!< [0x0008] WDT Reset Counter Register                                       */

} WDT_T;

/**
    @addtogroup WDT_CONST WDT Bit Field Definition
    Constant Definitions for WDT Controller
@{ */

#define WDT_CTL_RSTCNT_Pos               (0)                                               /*!< WDT_T::CTL: RSTCNT Position            */
#define WDT_CTL_RSTCNT_Msk               (0x1ul << WDT_CTL_RSTCNT_Pos)                     /*!< WDT_T::CTL: RSTCNT Mask                */

#define WDT_CTL_RSTEN_Pos                (1)                                               /*!< WDT_T::CTL: RSTEN Position             */
#define WDT_CTL_RSTEN_Msk                (0x1ul << WDT_CTL_RSTEN_Pos)                      /*!< WDT_T::CTL: RSTEN Mask                 */

#define WDT_CTL_RSTF_Pos                 (2)                                               /*!< WDT_T::CTL: RSTF Position              */
#define WDT_CTL_RSTF_Msk                 (0x1ul << WDT_CTL_RSTF_Pos)                       /*!< WDT_T::CTL: RSTF Mask                  */

#define WDT_CTL_IF_Pos                   (3)                                               /*!< WDT_T::CTL: IF Position                */
#define WDT_CTL_IF_Msk                   (0x1ul << WDT_CTL_IF_Pos)                         /*!< WDT_T::CTL: IF Mask                    */

#define WDT_CTL_WKEN_Pos                 (4)                                               /*!< WDT_T::CTL: WKEN Position              */
#define WDT_CTL_WKEN_Msk                 (0x1ul << WDT_CTL_WKEN_Pos)                       /*!< WDT_T::CTL: WKEN Mask                  */

#define WDT_CTL_WKF_Pos                  (5)                                               /*!< WDT_T::CTL: WKF Position               */
#define WDT_CTL_WKF_Msk                  (0x1ul << WDT_CTL_WKF_Pos)                        /*!< WDT_T::CTL: WKF Mask                   */

#define WDT_CTL_INTEN_Pos                (6)                                               /*!< WDT_T::CTL: INTEN Position             */
#define WDT_CTL_INTEN_Msk                (0x1ul << WDT_CTL_INTEN_Pos)                      /*!< WDT_T::CTL: INTEN Mask                 */

#define WDT_CTL_WDTEN_Pos                (7)                                               /*!< WDT_T::CTL: WDTEN Position             */
#define WDT_CTL_WDTEN_Msk                (0x1ul << WDT_CTL_WDTEN_Pos)                      /*!< WDT_T::CTL: WDTEN Mask                 */

#define WDT_CTL_TOUTSEL_Pos              (8)                                               /*!< WDT_T::CTL: TOUTSEL Position           */
#define WDT_CTL_TOUTSEL_Msk              (0x7ul << WDT_CTL_TOUTSEL_Pos)                    /*!< WDT_T::CTL: TOUTSEL Mask               */

#define WDT_CTL_SYNC_Pos                 (30)                                              /*!< WDT_T::CTL: SYNC Position              */
#define WDT_CTL_SYNC_Msk                 (0x1ul << WDT_CTL_SYNC_Pos)                       /*!< WDT_T::CTL: SYNC Mask                  */

#define WDT_CTL_ICEDEBUG_Pos             (31)                                              /*!< WDT_T::CTL: ICEDEBUG Position          */
#define WDT_CTL_ICEDEBUG_Msk             (0x1ul << WDT_CTL_ICEDEBUG_Pos)                   /*!< WDT_T::CTL: ICEDEBUG Mask              */

#define WDT_ALTCTL_RSTDSEL_Pos           (0)                                               /*!< WDT_T::ALTCTL: RSTDSEL Position        */
#define WDT_ALTCTL_RSTDSEL_Msk           (0x3ul << WDT_ALTCTL_RSTDSEL_Pos)                 /*!< WDT_T::ALTCTL: RSTDSEL Mask            */

#define WDT_RSTCNT_RSTCNT_Pos            (0)                                               /*!< WDT_T::RSTCNT: RSTCNT Position         */
#define WDT_RSTCNT_RSTCNT_Msk            (0xfffffffful << WDT_RSTCNT_RSTCNT_Pos)           /*!< WDT_T::RSTCNT: RSTCNT Mask             */

/**@}*/ /* WDT_CONST */
/**@}*/ /* end of WDT register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __WDT_REG_H__ */
