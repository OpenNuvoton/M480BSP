/*
 * libmad - MPEG audio decoder library
 * Copyright (C) 2000-2004 Underbit Technologies, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * If you would like to negotiate alternate licensing terms, you may do
 * so by contacting: Underbit Technologies, Inc. <info@underbit.com>
 */

# ifdef __cplusplus
extern "C" {
# endif

// #define free free_dbg
// #define malloc malloc_dbg
// #define calloc calloc_dbg

#ifndef __WINS__       // This only works on target machine
# define FPM_ARM
//# define OPT_SPEED
//# define FPM_DEFAULT
#else                  // working on emulator
# define FPM_DEFAULT
//# define FPM_INTEL     
#endif



# define SIZEOF_INT 4
# define SIZEOF_LONG 4
# define SIZEOF_LONG_LONG 1

#include "decoder.h"


# ifdef __cplusplus
}
# endif
