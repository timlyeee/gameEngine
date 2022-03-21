
#pragma once
#include <cstdint>

#ifdef _USRDLL
    #define CC_DLL __declspec(dllexport)
#else /* use a DLL library */
    #define CC_DLL __declspec(dllimport)
#endif