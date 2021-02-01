#pragma once

// Platform detection

#ifdef _WIN32
    #define SH_WIN

    #ifdef _WIN64
        #define SH_WIN64
    #else
        #define SH_WIN32
    #endif
#elif defined(__APPLE__) || defined(__MACH__)
    #define SH_OSX
#elif defined(__linux__)
    #define SH_LINUX
#endif


// Debug

#ifdef DEBUG
    #define SH_DEBUG
#endif

// Debugger

//#define SH_DEBUGGER

// Profiling

#define SH_PROFILE
