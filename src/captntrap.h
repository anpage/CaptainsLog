/**
 * @file
 *
 * @author OmniBlade
 *
 * @brief Debug trap intrinsic.
 *
 * @copyright CaptainsLog is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#ifndef LOG_CAPTNTRAP_H
#define LOG_CAPTNTRAP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Temp macro for intrinsic inlining */
#if defined __GNUC__ || defined __clang__
#define trap_inline extern __attribute__((gnu_inline, always_inline)) inline
#else
#define trap_inline inline
#endif

#ifndef __has_builtin
#define __has_builtin(x) 0
#endif

#if __has_builtin(__builtin_debugtrap)
#define captain_debugtrap __builtin_debugtrap
#elif defined _WIN32
#include <intrin.h>
#define captain_debugtrap __debugbreak
/* If we have GCC or compiler that tries to be compatible, use GCC inline assembly. */
#elif defined __GNUC__ || defined __clang__
#if defined(__i386__) || defined(__x86_64__)
    trap_inline void captain_debugtrap(void)
    {
        __asm__ volatile("int $0x03");
}
#elif defined(__arm__)
    trap_inline void captain_debugtrap(void)
    {
        __asm__ volatile("bkpt #3");
    }
#elif defined(__aarch64__)
    trap_inline void captain_debugtrap(void)
    {
        /* same values as used by msvc __debugbreak on arm64 */
        __asm__ volatile("brk #0xF000");
    }
#elif defined(__powerpc__)
    trap_inline void captain_debugtrap(void)
    {
        __asm__ volatile(".4byte 0x7d821008");
    }
#else
#error captain_debugtrap not currently supported on this processor platform, see captntrap.h
#endif /* CPU architectures on GCC like compilers */
#elif defined __WATCOMC__
void captain_debugtrap(void);
#pragma aux captain_debugtrap = "int 3"
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* LOG_CAPTNTRAP_H */
