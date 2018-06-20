/******************************************************************************
Copyright (c) Airoha 2016 - All rights reserved

FILE NAME 
    cfg_sector.c
DESCRIPTION
NOTES
********************************************************************************/
#include <stdint.h>
#include "m0_env.h"
/*useful macro*/
#define STRING2(x) #x
#define DEFINE_STRING(x) #x" = "STRING2(x)


#ifdef XO16M_CORE_ADJ
    #warning "XO16M_CORE_ADJ enabled"
    #define XO16M_CORE_ADJ_3WIRE_NUM 2
#else
    #define XO16M_CORE_ADJ_3WIRE_NUM 0
#endif

#ifdef RF_6_DBM
    #warning "RF_6_DBM enabled"
    #define RF_6_DBM_3WIRE_NUM 2
    #define RF_6_DBM_CSR_NUM 1
#else
    #define RF_6_DBM_3WIRE_NUM 0
    #define RF_6_DBM_CSR_NUM 0    
#endif

/*Adie 3wire number*/
#define ADIE_3WIRE_NUM (21+RF_6_DBM_3WIRE_NUM+XO16M_CORE_ADJ_3WIRE_NUM)
#define ADIE_CSR_NUM (10 + RF_6_DBM_CSR_NUM)


const CFG_PARAMETER_STRU_BASE  cfg_sector =
{
               
        
				    .NumOfAfeRegInit = ADIE_3WIRE_NUM,

                    .AfeRegInit = 
                    {
                      {0x0153,0x38},
                      {0x8080,0x2C},
                      {0x786D,0x2A},
                      {0xA130,0x1F},
                      {0x2703,0x1B},
                      {0x801C,0x3B},
                      {0xF700,0x24},
                      {0x000C,0x25},
                      {0x53FF,0x26},
                      {0x02A0,0x28},
                      {0xFFFF,0x29},
					 #ifdef RF_6_DBM
					  {0x0FFF,0x30},
					  {0x0340,0x0A},
					 #endif // RF_6_DBM
                      {0x1915,0x07},
                      {0x10E3,0x31},
                      {0x68F0,0x5F},
                      {0x0004,0x43},
                      {0x0088,0x5A},
                      {0x0603,0x5B},
                      {0xDF46,0x5C},
                      {0x041C,0x5E},  //SPI  transport
                      {0xA83A,0x34},
                      {0x000C,0x35},
                      #ifdef XO16M_CORE_ADJ                      
                      {0x06C1,0x37},
                      {0x0089,0x39},
                      #endif
                    },

                    .NumOfCsrRegInit = ADIE_CSR_NUM,

                    .CsrRegInit = 
                    {
                        {0xB040,0x04,0x01636150},
                        {0xB00C,0x04,0x035C5F39},
                        {0xB000,0x04,0x00661F29},
                        {0xB004,0x04,0x33392628},
                        {0xB008,0x04,0x34462821},
                        {0x1008,0x04,0x00000001},
                       #ifndef RF_6_DBM
					              {0x1024,0x04,0x000D0D0D},
					             #else  // RF_6_DBM
					              {0x1024,0x04,0x000F0F0F},
		           			    {0x1028,0x04,0x00004E00},
					             #endif // RF_6_DBM
                        {0x3018,0x04,0x00010267},
                        {0x1300,0x04,0x00000000},     //set A die GPIO 0~7 as input, prevent from interfering B die GPIO
                        {0x302E,0x01,0x06},                   //enable controller connection event protect offset
                      //  {0x1314,0x04,0x0000010C},   //debug bt
                    }                
};

