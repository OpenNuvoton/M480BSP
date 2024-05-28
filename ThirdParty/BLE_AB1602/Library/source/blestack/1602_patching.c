
#include <stdint.h>
#if defined(PATCH_MASTER)
    #pragma message "/*********************************/"
    #pragma message "/***** patch_init_master.txt *****/"
    #pragma message "/*********************************/"
    #include "patch_init_master.txt"
#else
    ////#pragma message "/*********************************/"
    ////#pragma message "/***** 1602_patching.txt *****/"
    ////#pragma message "/*********************************/"
    #include "1602_patching.txt"
#endif

const uint32_t sizeof_gPatch_EdataInit = sizeof(gPatch_EdataInit);
const uint32_t sizeof_gPatch_CsrInit = sizeof(gPatch_CsrInit);
