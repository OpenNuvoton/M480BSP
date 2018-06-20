#ifndef PLATFORM_HH__
#define PLATFORM_HH__

#ifdef _MSC_VER
#include "windows_env.h"
#elif defined(__ARMCC_VERSION)
#include "m0_env.h"
#else
#include "ab1600.h"
#endif

#endif
