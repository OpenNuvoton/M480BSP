/*---------------------------------------------------------------------------------------------------------*/
/*                                                                                                         */
/* Version Information for HID Transfer Test Tool                                                          */
/*                                                                                                         */
/*---------------------------------------------------------------------------------------------------------*/

#ifndef _VERSION_H_
#define _VERSION_H_

/* Version numbers */
#define VER_MAJOR               1
#define VER_MINOR               1
#define VER_REVISION            0
#define VER_BUILD               0

/* String macros for converting numbers to strings */
#define STR(x)                  #x
#define XSTR(x)                 STR(x)

/* Version string for display (MAJOR.MINOR.REVISION) */
#define TOOL_VERSION_STR        XSTR(VER_MAJOR) "." XSTR(VER_MINOR) "." XSTR(VER_REVISION)

/* Convert version numbers to resource format */
#define VER_FILE_VERSION        VER_MAJOR,VER_MINOR,VER_REVISION,VER_BUILD
#define VER_PRODUCT_VERSION     VER_MAJOR,VER_MINOR,VER_REVISION,VER_BUILD

/* Version strings for resource file (MAJOR.MINOR.REVISION.BUILD) */
#define VER_FILE_VERSION_STR    XSTR(VER_MAJOR) "." XSTR(VER_MINOR) "." XSTR(VER_REVISION) "." XSTR(VER_BUILD)
#define VER_PRODUCT_VERSION_STR XSTR(VER_MAJOR) "." XSTR(VER_MINOR) "." XSTR(VER_REVISION) "." XSTR(VER_BUILD)

/* Company and product information */
#define VER_COMPANY_NAME        "Nuvoton Technology Corp."
#define VER_FILE_DESCRIPTION    "HID Transfer Test Tool"
#define VER_INTERNAL_NAME       "HIDTransferTest"
#define VER_LEGAL_COPYRIGHT     "Copyright (C) 2010-2026 Nuvoton Technology Corp. All rights reserved."
#define VER_ORIGINAL_FILENAME   "HIDTransferTest.exe"
#define VER_PRODUCT_NAME        "HID Transfer Test Tool"

#endif /* _VERSION_H_ */
