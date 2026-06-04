Overview
--------
ISP_DFU is a sample code that implements a USB DFU (Device Firmware Upgrade)
in-system programmer (ISP). Once the ISP_DFU firmware is running on the target
device, it enumerates as a USB DFU device, allowing the host PC to download
application firmware directly over USB without any additional programmer hardware.

To perform the firmware download, the dfu-util command-line tool is required on
the host side.

DFU Utility Tool (dfu-util)
============================

Download
--------
dfu-util can be downloaded from the official release page:
  https://dfu-util.sourceforge.net/releases/

Usage
-----
Use the following command to download firmware to the target device via DFU:

  .\dfu-util.exe -a 0 -d 0x416:0xBDF0 -D [file]

Parameters:
  -a 0           : Select alternate interface 0
  -d 0x416:0xBDF0: Target device USB Vendor ID (0x416) and Product ID (0xBDF0)
  -D [file]      : Path to the firmware binary file to download (e.g., firmware.bin)

Example:
  .\dfu-util.exe -a 0 -d 0x416:0xBDF0 -D TIMER_Periodic.bin
