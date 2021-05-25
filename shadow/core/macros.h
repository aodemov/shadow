#pragma once

#include <memory>

template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T, typename ... Args>
constexpr Scope<T> MakeScope(Args&& ... args)
{
    return std::make_unique<T>(std::forward<Args>(args)...);
}

template<typename T>
using Ref = std::shared_ptr<T>;
template<typename T, typename ... Args>
constexpr Ref<T> MakeRef(Args&& ... args)
{
    return std::make_shared<T>(std::forward<Args>(args)...);
}

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

#define SH_DEBUGGER

// Profiling

// #define SH_PROFILE
