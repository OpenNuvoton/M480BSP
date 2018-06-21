/*********************************************************************
*                 SEGGER Software GmbH                               *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2018  SEGGER Microcontroller GmbH                *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.48 - Graphical user interface for embedded applications **
All  Intellectual Property rights in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product. This file may
only be used in accordance with the following terms:

The  software has  been licensed by SEGGER Software GmbH to Nuvoton Technology Corporationat the address: No. 4, Creation Rd. III, Hsinchu Science Park, Taiwan
for the purposes  of  creating  libraries  for its 
Arm Cortex-M and  Arm9 32-bit microcontrollers, commercialized and distributed by Nuvoton Technology Corporation
under  the terms and conditions  of  an  End  User  
License  Agreement  supplied  with  the libraries.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
Licensing information
Licensor:                 SEGGER Software GmbH
Licensed to:              Nuvoton Technology Corporation, No. 4, Creation Rd. III, Hsinchu Science Park, 30077 Hsinchu City, Taiwan
Licensed SEGGER software: emWin
License number:           GUI-00735
License model:            emWin License Agreement, signed February 27, 2018
Licensed platform:        Cortex-M and ARM9 32-bit series microcontroller designed and manufactured by or for Nuvoton Technology Corporation
----------------------------------------------------------------------
Support and Update Agreement (SUA)
SUA period:               2018-03-26 - 2019-03-27
Contact to extend SUA:    sales@segger.com
-------------------------- END-OF-HEADER -----------------------------

File    : IP_FS.h
Purpose : Header file for file system abstraction layer.
*/

#ifndef IP_FS_H               // Avoid multiple inclusion.
#define IP_FS_H

#include "SEGGER.h"

#if defined(__cplusplus)
  extern "C" {                // Make sure we have C-declarations in C++ programs.
#endif

/*********************************************************************
*
*       Types
*
**********************************************************************
*/

typedef struct {
  //
  // Read only file operations. These have to be present on ANY file system, even the simplest one.
  //
  void* (*pfOpenFile)             (const char* sFilename);
  int   (*pfCloseFile)            (void* hFile);
  int   (*pfReadAt)               (void* hFile, void* pBuffer, U32 Pos, U32 NumBytes);
  long  (*pfGetLen)               (void* hFile);
  //
  // Directory query operations.
  //
  void  (*pfForEachDirEntry)      (void* pContext, const char* sDir, void (*pf)(void*, void*));
  void  (*pfGetDirEntryFileName)  (void* pFileEntry, char* sFileName, U32 SizeOfBuffer);
  U32   (*pfGetDirEntryFileSize)  (void* pFileEntry, U32* pFileSizeHigh);
  U32   (*pfGetDirEntryFileTime)  (void* pFileEntry);
  int   (*pfGetDirEntryAttributes)(void* pFileEntry);
  //
  // Write file operations.
  //
  void* (*pfCreate)               (const char* sFileName);
  void* (*pfDeleteFile)           (const char* sFilename);
  int   (*pfRenameFile)           (const char* sOldFilename, const char* sNewFilename);
  int   (*pfWriteAt)              (void* hFile, void* pBuffer, U32 Pos, U32 NumBytes);
  //
  // Additional directory operations
  //
  int   (*pfMKDir)                (const char* sDirName);
  int   (*pfRMDir)                (const char* sDirName);
  //
  // Additional operations
  //
  int   (*pfIsFolder)             (const char* sPath);
  int   (*pfMove)                 (const char* sOldFilename, const char* sNewFilename);
} IP_FS_API;

typedef struct {
  const          char* sPath;
  const unsigned char* pData;
        unsigned int   FileSize;
} IP_FS_READ_ONLY_FILE_ENTRY;

typedef struct IP_FS_READ_ONLY_FILE_HOOK_STRUCT IP_FS_READ_ONLY_FILE_HOOK;
struct IP_FS_READ_ONLY_FILE_HOOK_STRUCT {
  IP_FS_READ_ONLY_FILE_HOOK* pNext;
  IP_FS_READ_ONLY_FILE_ENTRY FileEntry;
};

/*********************************************************************
*
*       API functions
*
**********************************************************************
*/

#define IP_FS_FS                    IP_FS_emFile
#define IP_FS_FS_AllowHiddenAccess  IP_FS_emFile_AllowHiddenAccess
#define IP_FS_FS_DenyHiddenAccess   IP_FS_emFile_DenyHiddenAccess

extern const IP_FS_API IP_FS_ReadOnly;                  // Read-only file system, typically located in flash memory.
extern const IP_FS_API IP_FS_Win32;                     // File system interface for Win32.
extern const IP_FS_API IP_FS_Linux;                     // File system interface for Linux
extern const IP_FS_API IP_FS_emFile;                    // Target file system (emFile), shows and allows access to hidden files.
extern const IP_FS_API IP_FS_emFile_AllowHiddenAccess;  // Target file system (emFile), does not show hidden files but allows access to them.
extern const IP_FS_API IP_FS_emFile_DenyHiddenAccess;   // Target file system (emFile), does not show hidden files and does not allow access to them.

//
// Helper functions for Read Only file system layer.
//
void IP_FS_READ_ONLY_ClrFileHooks(void);
void IP_FS_READ_ONLY_AddFileHook (IP_FS_READ_ONLY_FILE_HOOK* pHook, const char* sPath, const unsigned char* pData, unsigned int FileSize);

//
// Helper functions for Win32 file system layer.
//
void IP_FS_WIN32_ConfigBaseDir(const char* sDir);


#if defined(__cplusplus)
}                             // Make sure we have C-declarations in C++ programs.
#endif

#endif                        // Avoid multiple inclusion.

/*************************** End of file ****************************/
