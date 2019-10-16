/**
 * @file
 *
 * @author OmniBlade
 *
 * @brief Logging functions and configuration.
 *
 * @copyright CaptainsLog is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version
 *            2 of the License, or (at your option) any later version.
 *            A full copy of the GNU General Public License can be found in
 *            LICENSE
 */
#ifndef LOG_CAPTNLOG_H
#define LOG_CAPTNLOG_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Default to debug logging */
#ifndef LOGGING_LEVEL
#define LOGGING_LEVEL 5
#endif

#define LOGLEVEL_NONE  0
#define LOGLEVEL_FATAL 1
#define LOGLEVEL_ERROR 2
#define LOGLEVEL_WARN  3
#define LOGLEVEL_INFO  4
#define LOGLEVEL_DEBUG 5
#define LOGLEVEL_TRACE 6

/* Conditionally define the function like macros for logging levels, allows only certain logging to be compiled into client program. */
#if LOGLEVEL_TRACE <= LOGGING_LEVEL
#define captain_trace(x, ...) captain_log(LOGLEVEL_TRACE, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define captain_trace(x, ...) ((void)0)
#endif

#if LOGLEVEL_DEBUG <= LOGGING_LEVEL
#define captain_debug(x, ...) captain_log(LOGLEVEL_DEBUG, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define captain_debug(x, ...) ((void)0)
#endif

#if LOGLEVEL_INFO <= LOGGING_LEVEL
#define captain_info(x, ...) captain_log(LOGLEVEL_INFO, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define captain_info(x, ...) ((void)0)
#endif

#if LOGLEVEL_WARN <= LOGGING_LEVEL
#define captain_warn(x, ...) captain_log(LOGLEVEL_WARN, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define captain_warn(x, ...) ((void)0)
#endif
  
#if LOGLEVEL_ERROR <= LOGGING_LEVEL
#define captain_error(x, ...) captain_log(LOGLEVEL_ERROR, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define captain_error(x, ...) ((void)0)
#endif

#if LOGLEVEL_FATAL <= LOGGING_LEVEL
#define captain_fatal(x, ...) captain_log(LOGLEVEL_FATAL, __FILE__, __LINE__, ##__VA_ARGS__)
#else
#define captain_fatal(x, ...) ((void)0)
#endif

#if LOGGING_LEVEL == LOGLEVEL_NONE
#define captain_init(level, filename, console, syslog, print_time) ((void)0)
#define captain_log(level, file, line, format, ...) ((void)0)
#define captain_line(fmt, ...) ((void)0)
#define captain_deinit() ((void)0)
#else
void captain_init(int level, const char *filename, bool console, bool syslog, bool print_time);
void captain_log(int level, const char *file, int line, const char *fmt, ...);
void captain_line(const char *fmt, ...);
void captain_deinit();
#endif

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* LOG_CAPTNLOG_H */
