/******************************************************************************
 * @file     config.h
 * @version  V0.10
 * @brief
 *           Define the device setting.
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
/* Just select one */
#define MEDIAKEY    0
#define JOYSTICK    0

#if MEDIAKEY
    #define __HID__
    #define __MEDIAKEY__
#elif JOYSTICK
    #define __HID__
    #define __JOYSTICK__
#endif
