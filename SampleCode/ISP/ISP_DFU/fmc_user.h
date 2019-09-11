/**************************************************************************//**
 * @file     fmc_user.h
 * @brief    M480 series FMC driver header file
 * @version  2.0.0
 *
 * @copyright (C) 2019 Nuvoton Technology Corp. All rights reserved.
 ******************************************************************************/
#ifndef FMC_USER_H
#define FMC_USER_H

#include "M480.h"

/*---------------------------------------------------------------------------------------------------------*/
/* Define parameter                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
#define ISPGO           0x01

int FMC_Read_User(unsigned int u32Addr, unsigned int *data);
void ReadData(unsigned int addr_start, unsigned int addr_end, unsigned int *data);
void WriteData(unsigned int addr_start, unsigned int addr_end, unsigned int *data);

#endif
