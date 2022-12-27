/**************************************************************************//**
 * @file     ccap_reg.h
 * @version  V1.00
 * @brief    CCAP register definition header file
 *
 * SPDX-License-Identifier: Apache-2.0
 * @copyright (C) 2017-2020 Nuvoton Technology Corp. All rights reserved.
 *****************************************************************************/
#ifndef __CCAP_REG_H__
#define __CCAP_REG_H__

#if defined ( __CC_ARM   )
#pragma anon_unions
#endif

/**
   @addtogroup REGISTER Control Register
   @{
*/

/**
    @addtogroup CCAP Camera Capture Interface Controller (CCAP)
    Memory Mapped Structure for CCAP Controller
@{ */


typedef struct {


    /**
@var CCAP_T::CTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CTL
</font><br><p> <font size="2">
Offset: 0x00  Camera Capture Interface Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>CCAPEN</td><td><div style="word-wrap: break-word;"><b>Camera Capture Interface Enable
</b><br>
0 = Camera Capture Interface Disabled.
<br>
1 = Camera Capture Interface Enabled.
<br>
</div></td></tr><tr><td>
[3]</td><td>ADDRSW</td><td><div style="word-wrap: break-word;"><b>Packet Buffer Address Switch
</b><br>
0 = Packet buffer address switch Disabled.
<br>
1 = Packet buffer address switch Enabled.
<br>
</div></td></tr><tr><td>
[6]</td><td>PKTEN</td><td><div style="word-wrap: break-word;"><b>Packet Output Enable
</b><br>
0 = Packet output Disabled.
<br>
1 = Packet output Enabled.
<br>
</div></td></tr><tr><td>
[7]</td><td>MONO</td><td><div style="word-wrap: break-word;"><b>Monochrome CMOS Sensor Select
</b><br>
0 = Color CMOS Sensor.
<br>
1 = Monochrome CMOS Sensor. The U/V components are ignored when the MONO is enabled.
<br>
</div></td></tr><tr><td>
[16]</td><td>SHUTTER</td><td><div style="word-wrap: break-word;"><b>Image Capture Interface Automatically Disable The Capture Interface After A Frame Had Been Captured
</b><br>
0 = Shutter Disabled.
<br>
1 = Shutter Enabled.
<br>
</div></td></tr><tr><td>
[20]</td><td>UPDATE</td><td><div style="word-wrap: break-word;"><b>Update Register At New Frame
</b><br>
0 = Update register at new frame Disabled.
<br>
1 = Update register at new frame Enabled (Auto clear to 0 when register updated).
<br>
</div></td></tr><tr><td>
[24]</td><td>VPRST</td><td><div style="word-wrap: break-word;"><b>Capture Interface Reset
</b><br>
0 = Capture interface reset Disabled.
<br>
1 = Capture interface reset Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CCAP_T::PAR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PAR
</font><br><p> <font size="2">
Offset: 0x04  Camera Capture Interface Parameter Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>INFMT</td><td><div style="word-wrap: break-word;"><b>Sensor Input Data Format
</b><br>
0 = YCbCr422.
<br>
1 = RGB565.
<br>
</div></td></tr><tr><td>
[1]</td><td>SENTYPE</td><td><div style="word-wrap: break-word;"><b>Sensor Input Type
</b><br>
0 = CCIR601.
<br>
1 = CCIR656, VSync & Hsync embedded in the data signal.
<br>
</div></td></tr><tr><td>
[2:3]</td><td>INDATORD</td><td><div style="word-wrap: break-word;"><b>Sensor Input Data Order
</b><br>
If INFMT = 0 (YCbCr),.
<br>
 Byte 0 1 2 3
<br>
00 = Y0 U0 Y1 V0.
<br>
01 = Y0 V0 Y1 U0.
<br>
10 = U0 Y0 V0 Y1.
<br>
11 = V0 Y0 U0 Y1.
<br>
If INFMT = 1 (RGB565),.
<br>
00 = Byte0[R[4:0] G[5:3]] Byte1[G[2:0] B[4:0]]
<br>
01 = Byte0[B[4:0] G[5:3]] Byte1[G[2:0] R[4:0]]
<br>
10 = Byte0[G[2:0] B[4:0]] Byte1[R[4:0] G[5:3]]
<br>
11 = Byte0[G[2:0] R[4:0]] Byte1[B[4:0] G[5:3]]
<br>
</div></td></tr><tr><td>
[4:5]</td><td>OUTFMT</td><td><div style="word-wrap: break-word;"><b>Image Data Format Output To System Memory
</b><br>
00 = YCbCr422.
<br>
01 = Only output Y.
<br>
10 = RGB555.
<br>
11 = RGB565.
<br>
</div></td></tr><tr><td>
[6]</td><td>RANGE</td><td><div style="word-wrap: break-word;"><b>Scale Input YUV CCIR601 Color Range To Full Range
</b><br>
0 = default.
<br>
1 = Scale to full range.
<br>
</div></td></tr><tr><td>
[8]</td><td>PCLKP</td><td><div style="word-wrap: break-word;"><b>Sensor Pixel Clock Polarity
</b><br>
0 = Input video data and signals are latched by falling edge of Pixel Clock.
<br>
1 = Input video data and signals are latched by rising edge of Pixel Clock.
<br>
</div></td></tr><tr><td>
[9]</td><td>HSP</td><td><div style="word-wrap: break-word;"><b>Sensor Hsync Polarity
</b><br>
0 = Sync Low.
<br>
1 = Sync High.
<br>
</div></td></tr><tr><td>
[10]</td><td>VSP</td><td><div style="word-wrap: break-word;"><b>Sensor Vsync Polarity
</b><br>
0 = Sync Low.
<br>
1 = Sync High.
<br>
</div></td></tr><tr><td>
[18]</td><td>FBB</td><td><div style="word-wrap: break-word;"><b>Field By Blank
</b><br>
Hardware will tag field0 or field1 by vertical blanking instead of FIELD flag in CCIR-656 mode.
<br>
0 = Field by blank Disabled.
<br>
1 = Field by blank Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CCAP_T::INT

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">INT
</font><br><p> <font size="2">
Offset: 0x08  Camera Capture Interface Interrupt Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>VINTF</td><td><div style="word-wrap: break-word;"><b>Video Frame End Interrupt
</b><br>
If this bit shows 1, receiving a frame completed.
<br>
Write 1 to clear it.
<br>
</div></td></tr><tr><td>
[1]</td><td>MEINTF</td><td><div style="word-wrap: break-word;"><b>Bus Master Transfer Error Interrupt
</b><br>
If this bit shows 1, Transfer Error occurred. Write 1 to clear it.
<br>
</div></td></tr><tr><td>
[3]</td><td>ADDRMINTF</td><td><div style="word-wrap: break-word;"><b>Memory Address Match Interrupt
</b><br>
If this bit shows 1, Memory Address Match Interrupt occurred.
<br>
Write 1 to clear it.
<br>
</div></td></tr><tr><td>
[4]</td><td>MDINTF</td><td><div style="word-wrap: break-word;"><b>Motion Detection Output Finish Interrupt
</b><br>
If this bit shows 1, Motion Detection Output Finish Interrupt occurred.
<br>
Write 1 to clear it.
<br>
</div></td></tr><tr><td>
[16]</td><td>VIEN</td><td><div style="word-wrap: break-word;"><b>Video Frame End Interrupt Enable
</b><br>
0 = Video frame end interrupt Disabled.
<br>
1 = Video frame end interrupt Enabled.
<br>
</div></td></tr><tr><td>
[17]</td><td>MEIEN</td><td><div style="word-wrap: break-word;"><b>System Memory Error Interrupt Enable
</b><br>
0 = System memory error interrupt Disabled.
<br>
1 = System memory error interrupt Enabled.
<br>
</div></td></tr><tr><td>
[19]</td><td>ADDRMIEN</td><td><div style="word-wrap: break-word;"><b>Address Match Interrupt Enable
</b><br>
0 = Address match interrupt Disabled.
<br>
1 = Address match interrupt Enabled.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CCAP_T::POSTERIZE

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">POSTERIZE
</font><br><p> <font size="2">
Offset: 0x0C  YUV Component Posterizing Factor Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0:7]</td><td>VCOMP</td><td><div style="word-wrap: break-word;"><b>V Component Posterizing Factor
</b><br>
Final_V_Out = Original_V[7:0] & V_Posterizing_Factor.
<br>
</div></td></tr><tr><td>
[8:15]</td><td>UCOMP</td><td><div style="word-wrap: break-word;"><b>U Component Posterizing Factor
</b><br>
Final_U_Out = Original_U[7:0] & U_Posterizing_Factor.
<br>
</div></td></tr><tr><td>
[16:23]</td><td>YCOMP</td><td><div style="word-wrap: break-word;"><b>Y Component Posterizing Factor
</b><br>
Final_Y_Out = Original_Y[7:0] & Y_Posterizing_Factor.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CCAP_T::MD

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MD
</font><br><p> <font size="2">
Offset: 0x10  Motion Detection Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0]</td><td>MDEN</td><td><div style="word-wrap: break-word;"><b>Motion Detection Enable
</b><br>
0 = CCAP_MD Disabled.
<br>
1 = CCAP_MD Enabled.
<br>
</div></td></tr><tr><td>
[8]</td><td>MDBS</td><td><div style="word-wrap: break-word;"><b>Motion Detection Block Size
</b><br>
0 = 16x16.
<br>
1 = 8x8.
<br>
</div></td></tr><tr><td>
[9]</td><td>MDSM</td><td><div style="word-wrap: break-word;"><b>Motion Detection Save Mode
</b><br>
0 = 1 bit DIFF + 7 bit Y Differential.
<br>
1 = 1 bit DIFF only.
<br>
</div></td></tr><tr><td>
[10:11]</td><td>MDDF</td><td><div style="word-wrap: break-word;"><b>Motion Detection Detect Frequency
</b><br>
00 = Each frame.
<br>
01 = Every 2 frame.
<br>
10 = Every 3 frame.
<br>
11 = Every 4 frame.
<br>
</div></td></tr><tr><td>
[16:20]</td><td>MDTHR</td><td><div style="word-wrap: break-word;"><b>Motion Detection Differential Threshold
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CCAP_T::MDADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MDADDR
</font><br><p> <font size="2">
Offset: 0x14  Motion Detection Output Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0:31]</td><td>MDADDR</td><td><div style="word-wrap: break-word;"><b>Motion Detection Output Address Register (Word Alignment)
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CCAP_T::MDYADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">MDYADDR
</font><br><p> <font size="2">
Offset: 0x18  Motion Detection Temp Y Output Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0:31]</td><td>MDYADDR</td><td><div style="word-wrap: break-word;"><b>Motion Detection Temp Y Output Address Register (Word Alignment)
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CCAP_T::SEPIA

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">SEPIA
</font><br><p> <font size="2">
Offset: 0x1C  Sepia Effect Control Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0:7]</td><td>VCOMP</td><td><div style="word-wrap: break-word;"><b>Define the constant V component while Sepia color effect is turned on.
</b><br>
</div></td></tr><tr><td>
[8:15]</td><td>UCOMP</td><td><div style="word-wrap: break-word;"><b>Define the constant U component while Sepia color effect is turned on.
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CCAP_T::CWSP

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CWSP
</font><br><p> <font size="2">
Offset: 0x20  Cropping Window Starting Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0:11]</td><td>CWSADDRH</td><td><div style="word-wrap: break-word;"><b>Cropping Window Horizontal Starting Address
</b><br>
</div></td></tr><tr><td>
[16:26]</td><td>CWSADDRV</td><td><div style="word-wrap: break-word;"><b>Cropping Window Vertical Starting Address
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CCAP_T::CWS

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CWS
</font><br><p> <font size="2">
Offset: 0x24  Cropping Window Size Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0:11]</td><td>CIWW</td><td><div style="word-wrap: break-word;"><b>Cropping Image Window Width
</b><br>
</div></td></tr><tr><td>
[16:26]</td><td>CIWH</td><td><div style="word-wrap: break-word;"><b>Cropping Image Window Height
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CCAP_T::PKTSL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PKTSL
</font><br><p> <font size="2">
Offset: 0x28  Packet Scaling Vertical/Horizontal Factor Register (LSB)
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0:7]</td><td>PKTSHML</td><td><div style="word-wrap: break-word;"><b>Packet Scaling Horizontal Factor M (Lower 8-Bit)
</b><br>
Specifies the lower 8-bit of denominator part (M) of the horizontal scaling factor.
<br>
The lower 8-bit will be cascaded with higher 8-bit (PKDSHMH) to form a 16-bit denominator (M) of vertical factor.
<br>
The output image width will be equal to the image width * N/M.
<br>
Note: The value of N must be equal to or less than M.
<br>
</div></td></tr><tr><td>
[8:15]</td><td>PKTSHNL</td><td><div style="word-wrap: break-word;"><b>Packet Scaling Horizontal Factor N (Lower 8-Bit)
</b><br>
Specify the lower 8-bit of numerator part (N) of the horizontal scaling factor.
<br>
The lower 8-bit will be cascaded with higher 8-bit (PKDSHNH) to form a 16-bit numerator of horizontal factor.
<br>
</div></td></tr><tr><td>
[16:23]</td><td>PKTSVML</td><td><div style="word-wrap: break-word;"><b>Packet Scaling Vertical Factor M (Lower 8-Bit)
</b><br>
Specify the lower 8-bit of denominator part (M) of the vertical scaling factor.
<br>
The lower 8-bit will be cascaded with higher 8-bit (PKDSVMH) to form a 16-bit denominator (M) of vertical factor.
<br>
The output image width will be equal to the image height * N/M.
<br>
Note: The value of N must be equal to or less than M.
<br>
</div></td></tr><tr><td>
[24:31]</td><td>PKTSVNL</td><td><div style="word-wrap: break-word;"><b>Packet Scaling Vertical Factor N (Lower 8-Bit)
</b><br>
Specify the lower 8-bit of numerator part (N) of the vertical scaling factor.
<br>
The lower 8-bit will be cascaded with higher 8-bit (PKDSVNH) to form a 16-bit numerator of vertical factor
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CCAP_T::PLNSL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PLNSL
</font><br><p> <font size="2">
Offset: 0x2C  Planar Scaling Vertical/Horizontal Factor Register (LSB)
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0:7]</td><td>PLNSHML</td><td><div style="word-wrap: break-word;"><b>Planar Scaling Horizontal Factor M (Lower 8-Bit)
</b><br>
Specify the lower 8-bit of denominator part (M) of the horizontal scaling factor.
<br>
The lower 8-bit will be cascaded with higher 8-bit (PNDSHMH) to form a 16-bit denominator (M) of vertical factor.
<br>
The output image width will be equal to the image width * N/M.
<br>
Note: The value of N must be equal to or less than M.
<br>
</div></td></tr><tr><td>
[8:15]</td><td>PLNSHNL</td><td><div style="word-wrap: break-word;"><b>Planar Scaling Horizontal Factor N (Lower 8-Bit)
</b><br>
Specify the lower 8-bit of numerator part (N) of the horizontal scaling factor.
<br>
The lower 8-bit will be cascaded with higher 8-bit (PNDSHNH) to form a 16-bit numerator of horizontal factor.
<br>
</div></td></tr><tr><td>
[16:23]</td><td>PLNSVML</td><td><div style="word-wrap: break-word;"><b>Planar Scaling Vertical Factor M (Lower 8-Bit)
</b><br>
Specify the lower 8-bit of denominator part (M) of the vertical scaling factor.
<br>
The lower 8-bit will be cascaded with higher 8-bit (PNDSVMH) to form a 16-bit denominator (M) of vertical factor.
<br>
The output image width will be equal to the image height * N/M.
<br>
Note: The value of N must be equal to or less than M.
<br>
</div></td></tr><tr><td>
[24:31]</td><td>PLNSVNL</td><td><div style="word-wrap: break-word;"><b>Planar Scaling Vertical Factor N (Lower 8-Bit)
</b><br>
Specify the lower 8-bit of numerator part (N) of the vertical scaling factor.
<br>
The lower 8-bit will be cascaded with higher 8-bit (PNDSVNH) to form a 16-bit numerator of vertical factor.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CCAP_T::FRCTL

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">FRCTL
</font><br><p> <font size="2">
Offset: 0x30  Scaling Frame Rate Factor Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0:5]</td><td>FRM</td><td><div style="word-wrap: break-word;"><b>Scaling Frame Rate Factor M
</b><br>
Specify the denominator part (M) of the frame rate scaling factor.
<br>
The output image frame rate will be equal to input image frame rate * (N/M).
<br>
Note: The value of N must be equal to or less than M.
<br>
</div></td></tr><tr><td>
[8:13]</td><td>FRN</td><td><div style="word-wrap: break-word;"><b>Scaling Frame Rate Factor N
</b><br>
Specify the denominator part (N) of the frame rate scaling factor.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CCAP_T::STRIDE

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">STRIDE
</font><br><p> <font size="2">
Offset: 0x34  Frame Output Pixel Stride Width Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0:13]</td><td>PKTSTRIDE</td><td><div style="word-wrap: break-word;"><b>Packet Frame Output Pixel Stride Width
</b><br>
The output pixel stride size of packet pipe.
<br>
</div></td></tr><tr><td>
[16:29]</td><td>PLNSTRIDE</td><td><div style="word-wrap: break-word;"><b>Planar Frame Output Pixel Stride Width
</b><br>
The output pixel stride size of planar pipe.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CCAP_T::FIFOTH

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">FIFOTH
</font><br><p> <font size="2">
Offset: 0x3C  FIFO Threshold Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0:3]</td><td>PLNVFTH</td><td><div style="word-wrap: break-word;"><b>Planar V FIFO Threshold
</b><br>
</div></td></tr><tr><td>
[8:11]</td><td>PLNUFTH</td><td><div style="word-wrap: break-word;"><b>Planar U FIFO Threshold
</b><br>
</div></td></tr><tr><td>
[16:20]</td><td>PLNYFTH</td><td><div style="word-wrap: break-word;"><b>Planar Y FIFO Threshold
</b><br>
</div></td></tr><tr><td>
[24:28]</td><td>PKTFTH</td><td><div style="word-wrap: break-word;"><b>Packet FIFO Threshold
</b><br>
</div></td></tr><tr><td>
[31]</td><td>OVF</td><td><div style="word-wrap: break-word;"><b>FIFO Overflow Flag
</b><br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CCAP_T::CMPADDR

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">CMPADDR
</font><br><p> <font size="2">
Offset: 0x40  Compare Memory Base Address Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0:31]</td><td>CMPADDR</td><td><div style="word-wrap: break-word;"><b>Compare Memory Base Address
</b><br>
Word aligns address; ignore the bits [1:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CCAP_T::LUMA_Y1_THD

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">LUMA_Y1_THD
</font><br><p> <font size="2">
Offset: 0x44  Luminance Y8 to Y1 Threshold Value Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0:8]</td><td>LUMA_Y1_THRESH</td><td><div style="word-wrap: break-word;"><b>Luminance Y8 to Y1 Threshold Value
</b><br>
    |Specify the 8-bit threshold value for the luminance Y bit-8 to the luminance Y 1-bit conversion.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CCAP_T::PKTSM

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PKTSM
</font><br><p> <font size="2">
Offset: 0x48  Packet Scaling Vertical/Horizontal Factor Register (MSB)
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0:7]</td><td>PKTSHMH</td><td><div style="word-wrap: break-word;"><b>Packet Scaling Horizontal Factor M (Higher 8-Bit)
</b><br>
Specify the lower 8-bit of denominator part (M) of the horizontal scaling factor.
<br>
Please refer to the register CCAP_PKTSL?for the detailed operation.
<br>
</div></td></tr><tr><td>
[8:15]</td><td>PKTSHNH</td><td><div style="word-wrap: break-word;"><b>Packet Scaling Horizontal Factor N (Higher 8-Bit)
</b><br>
Specify the lower 8-bit of numerator part (N) of the horizontal scaling factor.
<br>
Please refer to the register CCAP_PKTSL for the detailed operation.
<br>
</div></td></tr><tr><td>
[16:23]</td><td>PKTSVMH</td><td><div style="word-wrap: break-word;"><b>Packet Scaling Vertical Factor M (Higher 8-Bit)
</b><br>
Specify the lower 8-bit of denominator part (M) of the vertical scaling factor.
<br>
Please refer to the register CCAP_PKTSL to check the cooperation between these two registers.
<br>
</div></td></tr><tr><td>
[24:31]</td><td>PKTSVNH</td><td><div style="word-wrap: break-word;"><b>Packet Scaling Vertical Factor N (Higher 8-Bit)
</b><br>
Specify the higher 8-bit of numerator part (N) of the vertical scaling factor.
<br>
Please refer to the register CCAP_PKTSL?to check the cooperation between these two registers.
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly


@var CCAP_T::PKTBA0

\htmlonly

<html><table class="fixed" border="1" style="border-collapse:collapse;" borderColor=black ><col width="75px" /><col width="125px" /><col width="700px" /><caption align="left"><font size="3">PKTBA0
</font><br><p> <font size="2">
Offset: 0x60  System Memory Packet Base Address 0 Register
</font></caption><thread><tr bgcolor="#8A0808" ><td><font color=white><b>Bits</b></font></td><td><font color=white><b>Field</b></font></td><td><font color=white><b>Descriptions</b></font></td></tr></thread><tbody>
<tr><td>
[0:31]</td><td>BASEADDR</td><td><div style="word-wrap: break-word;"><b>System Memory Packet Base Address 0
</b><br>
Word aligns address; ignore the bits [1:0].
<br>
</div></td></tr></tbody></table></html>

\endhtmlonly



 */
    __IO uint32_t CTL;
    __IO uint32_t PAR;
    __IO uint32_t INT;
    __IO uint32_t POSTERIZE;
    __IO uint32_t MD;
    __IO uint32_t MDADDR;
    __IO uint32_t MDYADDR;
    __IO uint32_t SEPIA;
    __IO uint32_t CWSP;
    __IO uint32_t CWS;
    __IO uint32_t PKTSL;
    __IO uint32_t PLNSL;
    __IO uint32_t FRCTL;
    __IO uint32_t STRIDE;
    /// @cond HIDDEN_SYMBOLS
    uint32_t RESERVE0[1];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t FIFOTH;
    __IO uint32_t CMPADDR;
    __IO uint32_t LUMA_Y1_THD;
    __IO uint32_t PKTSM;
    /// @cond HIDDEN_SYMBOLS
    uint32_t RESERVE2[5];
    /// @endcond //HIDDEN_SYMBOLS
    __IO uint32_t PKTBA0;
} CCAP_T;

/**
    @addtogroup CCAP_CONST CCAP Bit Field Definition
    Constant Definitions for CCAP Controller
@{ */

#define CCAP_CTL_CCAPEN_Pos               (0)                                               /*!< CCAP_T::CTL: CCAPEN Position                */
#define CCAP_CTL_CCAPEN_Msk               (0x1ul << CCAP_CTL_CCAPEN_Pos)                     /*!< CCAP_T::CTL: CCAPEN Mask                    */

#define CCAP_CTL_ADDRSW_Pos               (3)                                               /*!< CCAP_T::CTL: ADDRSW Position               */
#define CCAP_CTL_ADDRSW_Msk               (0x1ul << CCAP_CTL_ADDRSW_Pos)                     /*!< CCAP_T::CTL: ADDRSW Mask                   */

#define CCAP_CTL_PLNEN_Pos                (5)                                               /*!< CCAP_T::CTL: PLNEN Position                */
#define CCAP_CTL_PLNEN_Msk                (0x1ul << CCAP_CTL_PLNEN_Pos)                      /*!< CCAP_T::CTL: PLNEN Mask                    */

#define CCAP_CTL_PKTEN_Pos                (6)                                               /*!< CCAP_T::CTL: PKTEN Position                */
#define CCAP_CTL_PKTEN_Msk                (0x1ul << CCAP_CTL_PKTEN_Pos)                      /*!< CCAP_T::CTL: PKTEN Mask                    */

#define CCAP_CTL_MONO_Pos                 (7)                                               /*!< CCAP_T::CTL: MONO Position                */
#define CCAP_CTL_MONO_Msk                 (0x1ul << CCAP_CTL_MONO_Pos)                       /*!< CCAP_T::CTL: MONO Mask                    */

#define CCAP_CTL_SHUTTER_Pos              (16)                                              /*!< CCAP_T::CTL: SHUTTER Position              */
#define CCAP_CTL_SHUTTER_Msk              (0x1ul << CCAP_CTL_SHUTTER_Pos)                    /*!< CCAP_T::CTL: SHUTTER Mask                  */

#define CCAP_CTL_MY4_SWAP_Pos             (17)                                              /*!< CCAP_T::CTL: MY4_SWAP Position              */
#define CCAP_CTL_MY4_SWAP_Msk             (0x1ul << CCAP_CTL_MY4_SWAP_Pos)                   /*!< CCAP_T::CTL: MY4_SWAP Mask                  */

#define CCAP_CTL_MY8_MY4_Pos              (18)                                              /*!< CCAP_T::CTL: MY8_MY4 Position              */
#define CCAP_CTL_MY8_MY4_Msk              (0x1ul << CCAP_CTL_MY8_MY4_Pos)                    /*!< CCAP_T::CTL: MY8_MY4 Mask                  */

#define CCAP_CTL_Luma_Y_One_Pos           (19)                                              /*!< CCAP_T::CTL: Luma_Y_One Position              */
#define CCAP_CTL_Luma_Y_One_Msk           (0x1ul << CCAP_CTL_Luma_Y_One_Pos)                 /*!< CCAP_T::CTL: Luma_Y_One Mask                  */

#define CCAP_CTL_UPDATE_Pos               (20)                                              /*!< CCAP_T::CTL: UPDATE Position               */
#define CCAP_CTL_UPDATE_Msk               (0x1ul << CCAP_CTL_UPDATE_Pos)                     /*!< CCAP_T::CTL: UPDATE Mask                   */

#define CCAP_CTL_VPRST_Pos                (24)                                              /*!< CCAP_T::CTL: VPRST Position                */
#define CCAP_CTL_VPRST_Msk                (0x1ul << CCAP_CTL_VPRST_Pos)                      /*!< CCAP_T::CTL: VPRST Mask                    */

#define CCAP_PAR_INFMT_Pos                (0)                                               /*!< CCAP_T::PAR: INFMT Position                */
#define CCAP_PAR_INFMT_Msk                (0x1ul << CCAP_PAR_INFMT_Pos)                      /*!< CCAP_T::PAR: INFMT Mask                    */

#define CCAP_PAR_SENTYPE_Pos              (1)                                               /*!< CCAP_T::PAR: SENTYPE Position              */
#define CCAP_PAR_SENTYPE_Msk              (0x1ul << CCAP_PAR_SENTYPE_Pos)                    /*!< CCAP_T::PAR: SENTYPE Mask                  */

#define CCAP_PAR_INDATORD_Pos             (2)                                               /*!< CCAP_T::PAR: INDATORD Position             */
#define CCAP_PAR_INDATORD_Msk             (0x3ul << CCAP_PAR_INDATORD_Pos)                   /*!< CCAP_T::PAR: INDATORD Mask                 */

#define CCAP_PAR_OUTFMT_Pos               (4)                                               /*!< CCAP_T::PAR: OUTFMT Position               */
#define CCAP_PAR_OUTFMT_Msk               (0x3ul << CCAP_PAR_OUTFMT_Pos)                     /*!< CCAP_T::PAR: OUTFMT Mask                   */

#define CCAP_PAR_RANGE_Pos                (6)                                               /*!< CCAP_T::PAR: RANGE Position                */
#define CCAP_PAR_RANGE_Msk                (0x1ul << CCAP_PAR_RANGE_Pos)                      /*!< CCAP_T::PAR: RANGE Mask                    */

#define CCAP_PAR_PLNFMT_Pos               (7)                                               /*!< CCAP_T::PAR: PLNFMT Position               */
#define CCAP_PAR_PLNFMT_Msk               (0x1ul << CCAP_PAR_PLNFMT_Pos)                     /*!< CCAP_T::PAR: PLNFMT Mask                   */

#define CCAP_PAR_PCLKP_Pos                (8)                                               /*!< CCAP_T::PAR: PCLKP Position                */
#define CCAP_PAR_PCLKP_Msk                (0x1ul << CCAP_PAR_PCLKP_Pos)                      /*!< CCAP_T::PAR: PCLKP Mask                    */

#define CCAP_PAR_HSP_Pos                  (9)                                               /*!< CCAP_T::PAR: HSP Position                  */
#define CCAP_PAR_HSP_Msk                  (0x1ul << CCAP_PAR_HSP_Pos)                        /*!< CCAP_T::PAR: HSP Mask                      */

#define CCAP_PAR_VSP_Pos                  (10)                                              /*!< CCAP_T::PAR: VSP Position                  */
#define CCAP_PAR_VSP_Msk                  (0x1ul << CCAP_PAR_VSP_Pos)                        /*!< CCAP_T::PAR: VSP Mask                      */

#define CCAP_PAR_COLORCTL_Pos             (11)                                              /*!< CCAP_T::PAR: COLORCTL Position             */
#define CCAP_PAR_COLORCTL_Msk             (0x3ul << CCAP_PAR_COLORCTL_Pos)                   /*!< CCAP_T::PAR: COLORCTL Mask                 */

#define CCAP_PAR_FBB_Pos                  (18)                                              /*!< CCAP_T::PAR: FBB Position                  */
#define CCAP_PAR_FBB_Msk                  (0x1ul << CCAP_PAR_FBB_Pos)                        /*!< CCAP_T::PAR: FBB Mask                      */

#define CCAP_INT_VINTF_Pos                (0)                                               /*!< CCAP_T::INT: VINTF Position                */
#define CCAP_INT_VINTF_Msk                (0x1ul << CCAP_INT_VINTF_Pos)                      /*!< CCAP_T::INT: VINTF Mask                    */

#define CCAP_INT_MEINTF_Pos               (1)                                               /*!< CCAP_T::INT: MEINTF Position               */
#define CCAP_INT_MEINTF_Msk               (0x1ul << CCAP_INT_MEINTF_Pos)                     /*!< CCAP_T::INT: MEINTF Mask                   */

#define CCAP_INT_ADDRMINTF_Pos            (3)                                               /*!< CCAP_T::INT: ADDRMINTF Position            */
#define CCAP_INT_ADDRMINTF_Msk            (0x1ul << CCAP_INT_ADDRMINTF_Pos)                  /*!< CCAP_T::INT: ADDRMINTF Mask                */

#define CCAP_INT_MDINTF_Pos               (4)                                               /*!< CCAP_T::INT: MDINTF Position               */
#define CCAP_INT_MDINTF_Msk               (0x1ul << CCAP_INT_MDINTF_Pos)                     /*!< CCAP_T::INT: MDINTF Mask                   */

#define CCAP_INT_VIEN_Pos                 (16)                                              /*!< CCAP_T::INT: VIEN Position                 */
#define CCAP_INT_VIEN_Msk                 (0x1ul << CCAP_INT_VIEN_Pos)                       /*!< CCAP_T::INT: VIEN Mask                     */

#define CCAP_INT_MEIEN_Pos                (17)                                              /*!< CCAP_T::INT: MEIEN Position                */
#define CCAP_INT_MEIEN_Msk                (0x1ul << CCAP_INT_MEIEN_Pos)                      /*!< CCAP_T::INT: MEIEN Mask                    */

#define CCAP_INT_ADDRMIEN_Pos             (19)                                              /*!< CCAP_T::INT: ADDRMIEN Position             */
#define CCAP_INT_ADDRMIEN_Msk             (0x1ul << CCAP_INT_ADDRMIEN_Pos)                   /*!< CCAP_T::INT: ADDRMIEN Mask                 */

#define CCAP_CWSP_CWSADDRH_Pos            (0)                                               /*!< CCAP_T::CWSP: CWSADDRH Position            */
#define CCAP_CWSP_CWSADDRH_Msk            (0xffful << CCAP_CWSP_CWSADDRH_Pos)                /*!< CCAP_T::CWSP: CWSADDRH Mask                */

#define CCAP_CWSP_CWSADDRV_Pos            (16)                                              /*!< CCAP_T::CWSP: CWSADDRV Position            */
#define CCAP_CWSP_CWSADDRV_Msk            (0x7fful << CCAP_CWSP_CWSADDRV_Pos)                /*!< CCAP_T::CWSP: CWSADDRV Mask                */

#define CCAP_CWS_CWW_Pos                  (0)                                               /*!< CCAP_T::CWS: CWW Position                 */
#define CCAP_CWS_CWW_Msk                  (0xffful << CCAP_CWS_CWW_Pos)                      /*!< CCAP_T::CWS: CWW Mask                     */
#define CCAP_CWS_CWH_Pos                  (16)                                              /*!< CCAP_T::CWS: CIWH Position                 */
#define CCAP_CWS_CWH_Msk                  (0x7fful << CCAP_CWS_CWH_Pos)                      /*!< CCAP_T::CWS: CIWH Mask                     */

#define CCAP_PKTSL_PKTSHML_Pos            (0)                                               /*!< CCAP_T::PKTSL: PKTSHML Position            */
#define CCAP_PKTSL_PKTSHML_Msk            (0xfful << CCAP_PKTSL_PKTSHML_Pos)                 /*!< CCAP_T::PKTSL: PKTSHML Mask                */

#define CCAP_PKTSL_PKTSHNL_Pos            (8)                                               /*!< CCAP_T::PKTSL: PKTSHNL Position            */
#define CCAP_PKTSL_PKTSHNL_Msk            (0xfful << CCAP_PKTSL_PKTSHNL_Pos)                 /*!< CCAP_T::PKTSL: PKTSHNL Mask                */

#define CCAP_PKTSL_PKTSVML_Pos            (16)                                              /*!< CCAP_T::PKTSL: PKTSVML Position            */
#define CCAP_PKTSL_PKTSVML_Msk            (0xfful << CCAP_PKTSL_PKTSVML_Pos)                 /*!< CCAP_T::PKTSL: PKTSVML Mask                */

#define CCAP_PKTSL_PKTSVNL_Pos            (24)                                              /*!< CCAP_T::PKTSL: PKTSVNL Position            */
#define CCAP_PKTSL_PKTSVNL_Msk            (0xfful << CCAP_PKTSL_PKTSVNL_Pos)                 /*!< CCAP_T::PKTSL: PKTSVNL Mask                */

#define CCAP_FRCTL_FRM_Pos                (0)                                               /*!< CCAP_T::FRCTL: FRM Position                */
#define CCAP_FRCTL_FRM_Msk                (0x3ful << CCAP_FRCTL_FRM_Pos)                     /*!< CCAP_T::FRCTL: FRM Mask                    */

#define CCAP_FRCTL_FRN_Pos                (8)                                               /*!< CCAP_T::FRCTL: FRN Position                */
#define CCAP_FRCTL_FRN_Msk                (0x3ful << CCAP_FRCTL_FRN_Pos)                     /*!< CCAP_T::FRCTL: FRN Mask                    */

#define CCAP_STRIDE_PKTSTRIDE_Pos         (0)                                               /*!< CCAP_T::STRIDE: PKTSTRIDE Position         */
#define CCAP_STRIDE_PKTSTRIDE_Msk         (0x3ffful << CCAP_STRIDE_PKTSTRIDE_Pos)            /*!< CCAP_T::STRIDE: PKTSTRIDE Mask             */

#define CCAP_STRIDE_PLNSTRIDE_Pos         (16)                                              /*!< CCAP_T::STRIDE: PLNSTRIDE Position         */
#define CCAP_STRIDE_PLNSTRIDE_Msk         (0x3ffful << CCAP_STRIDE_PLNSTRIDE_Pos)            /*!< CCAP_T::STRIDE: PLNSTRIDE Mask             */

#define CCAP_FIFOTH_PLNVFTH_Pos           (0)                                               /*!< CCAP_T::FIFOTH: PLNVFTH Position           */
#define CCAP_FIFOTH_PLNVFTH_Msk           (0xful << CCAP_FIFOTH_PLNVFTH_Pos)                 /*!< CCAP_T::FIFOTH: PLNVFTH Mask               */

#define CCAP_FIFOTH_PLNUFTH_Pos           (8)                                               /*!< CCAP_T::FIFOTH: PLNUFTH Position           */
#define CCAP_FIFOTH_PLNUFTH_Msk           (0xful << CCAP_FIFOTH_PLNUFTH_Pos)                 /*!< CCAP_T::FIFOTH: PLNUFTH Mask               */

#define CCAP_FIFOTH_PLNYFTH_Pos           (16)                                              /*!< CCAP_T::FIFOTH: PLNYFTH Position           */
#define CCAP_FIFOTH_PLNYFTH_Msk           (0x1ful << CCAP_FIFOTH_PLNYFTH_Pos)                /*!< CCAP_T::FIFOTH: PLNYFTH Mask               */

#define CCAP_FIFOTH_PKTFTH_Pos            (24)                                              /*!< CCAP_T::FIFOTH: PKTFTH Position            */
#define CCAP_FIFOTH_PKTFTH_Msk            (0x1ful << CCAP_FIFOTH_PKTFTH_Pos)                 /*!< CCAP_T::FIFOTH: PKTFTH Mask                */

#define CCAP_FIFOTH_OVF_Pos               (31)                                              /*!< CCAP_T::FIFOTH: OVF Position               */
#define CCAP_FIFOTH_OVF_Msk               (0x1ul << CCAP_FIFOTH_OVF_Pos)                     /*!< CCAP_T::FIFOTH: OVF Mask                   */

#define CCAP_CMPADDR_CMPADDR_Pos          (0)                                               /*!< CCAP_T::CMPADDR: CMPADDR Position          */
#define CCAP_CMPADDR_CMPADDR_Msk          (0xfffffffful << CCAP_CMPADDR_CMPADDR_Pos)         /*!< CCAP_T::CMPADDR: CMPADDR Mask              */

#define CCAP_PKTSM_PKTSHMH_Pos            (0)                                               /*!< CCAP_T::PKTSM: PKTSHMH Position            */
#define CCAP_PKTSM_PKTSHMH_Msk            (0xfful << CCAP_PKTSM_PKTSHMH_Pos)                 /*!< CCAP_T::PKTSM: PKTSHMH Mask                */

#define CCAP_PKTSM_PKTSHNH_Pos            (8)                                               /*!< CCAP_T::PKTSM: PKTSHNH Position            */
#define CCAP_PKTSM_PKTSHNH_Msk            (0xfful << CCAP_PKTSM_PKTSHNH_Pos)                 /*!< CCAP_T::PKTSM: PKTSHNH Mask                */

#define CCAP_PKTSM_PKTSVMH_Pos            (16)                                              /*!< CCAP_T::PKTSM: PKTSVMH Position            */
#define CCAP_PKTSM_PKTSVMH_Msk            (0xfful << CCAP_PKTSM_PKTSVMH_Pos)                 /*!< CCAP_T::PKTSM: PKTSVMH Mask                */

#define CCAP_PKTSM_PKTSVNH_Pos            (24)                                              /*!< CCAP_T::PKTSM: PKTSVNH Position            */
#define CCAP_PKTSM_PKTSVNH_Msk            (0xfful << CCAP_PKTSM_PKTSVNH_Pos)                 /*!< CCAP_T::PKTSM: PKTSVNH Mask                */

#define CCAP_PKTBA0_BASEADDR_Pos          (0)                                               /*!< CCAP_T::PKTBA0: BASEADDR Position          */
#define CCAP_PKTBA0_BASEADDR_Msk          (0xfffffffful << CCAP_PKTBA0_BASEADDR_Pos)         /*!< CCAP_T::PKTBA0: BASEADDR Mask              */

/**@}*/ /* CCAP_CONST */
/**@}*/ /* end of CCAP register group */
/**@}*/ /* end of REGISTER group */

#if defined ( __CC_ARM   )
#pragma no_anon_unions
#endif

#endif /* __CCAP_REG_H__ */
