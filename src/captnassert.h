/**
 * @file
 *
 * @author OmniBlade
 *
 * @brief Assert macros to catch unexpected conditions with a variety of responses.
 *
 * @copyright CaptainsLog is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#ifndef LOG_CAPTNASSERT_H
#define LOG_CAPTNASSERT_H

#include "captnlog.h"
#include "captntrap.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define ASSERTS_NONE 0
#define ASSERTS_RELEASE 1
#define ASSERTS_DEBUG 2

#ifndef ASSERT_LEVEL
#define ASSERT_LEVEL ASSERTS_DEBUG
#endif

#if ASSERT_LEVEL == ASSERTS_DEBUG
#define captain_relassert(exp, to_throw, msg, ...) \
    do { \
        if (!(exp)) { \
            static volatile bool _ignore_assert = false; \
            static volatile bool _break = false; \
            if (!_ignore_assert) { \
                captain_fatal( \
                    "ASSERTION FAILED!\n" \
                    "  File:%s\n  Line:%d\n  Function:%s\n  Expression:%s\n\n", \
                    __FILE__, \
                    __LINE__, \
                    __CURRENT_FUNCTION__, \
                    #exp); \
                captain_assertfail( \
                    #exp, __FILE__, __LINE__, __CURRENT_FUNCTION__, &_ignore_assert, &_break, msg, ##__VA_ARGS__); \
            } \
            if (_break) { \
                captain_debugtrap(); \
            } \
        } \
    } while (false)

#define captain_dbgassert(exp, msg, ...) \
    do { \
        if (!(exp)) { \
            static volatile bool _ignore_assert = false; \
            static volatile bool _break = false; \
            if (!_ignore_assert) { \
                captain_fatal( \
                    "ASSERTION FAILED!\n" \
                    "  File:%s\n  Line:%d\n  Function:%s\n  Expression:%s\n\n", \
                    __FILE__, \
                    __LINE__, \
                    __CURRENT_FUNCTION__, \
                    #exp); \
                captain_assertfail( \
                    #exp, __FILE__, __LINE__, __CURRENT_FUNCTION__, &_ignore_assert, &_break, msg, ##__VA_ARGS__); \
            } \
            if (_break) { \
                captain_debugtrap(); \
            } \
        } \
    } while (false)
#define captain_assert(exp) \
    do { \
        if (!(exp)) { \
            static volatile bool _ignore_assert = false; \
            static volatile bool _break = false; \
            if (!_ignore_assert) { \
                captain_fatal( \
                    "ASSERTION FAILED!\n" \
                    "  File:%s\n  Line:%d\n  Function:%s\n  Expression:%s\n\n", \
                    __FILE__, \
                    __LINE__, \
                    __CURRENT_FUNCTION__, \
                    #exp); \
                captain_assertfail( \
                    #exp, __FILE__, __LINE__, __CURRENT_FUNCTION__, &_ignore_assert, &_break, NULL); \
            } \
            if (_break) { \
                captain_debugtrap(); \
            } \
        } \
    } while (false)
#elif ASSERT_LEVEL == ASSERTS_RELEASE
#define captain_relassert(exp, to_throw, msg, ...) \
    do { \
        if (!(exp)) { \
            throw to_throw; \
        } \
    } while (false)

#define captain_dbgassert(exp, msg, ...) ((void)0)
#define captain_assert(exp) ((void)0)
#else
#define captain_assert(exp, to_throw, msg, ...) ((void)0)
#define captain_dbgassert(exp, msg, ...) ((void)0)
#define captain_assert(exp) ((void)0)
#endif

#if ASSERT_LEVEL == ASSERTS_NONE
#define captain_assertfail(expr, file, line, func, ignore, allow_break, msg, ...) ((void)0)
#define captain_ignoreasserts(ignore) ((void)0)
#define captain_allowpopups(allow) ((void)0)
#else
void captain_assertfail(const char *expr, const char *file, int line, const char *func, volatile bool *ignore,
        volatile bool *allow_break, const char *msg, ...);
void captain_ignoreasserts(bool ignore);
void captain_allowpopups(bool allow);
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* LOG_CAPTNASSERT_H */
