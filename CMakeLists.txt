cmake_minimum_required(VERSION 3.1.0)

if(POLICY CMP0074)
  cmake_policy(SET CMP0074 NEW)
endif()

project(captnlog VERSION 1.00 LANGUAGES C)

# We don't support in tree builds, so help people make the right choice.
if(CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR)
    message(FATAL_ERROR "Building in-source is not supported! Create a build dir and remove ${CMAKE_SOURCE_DIR}/CMakeCache.txt")
endif()

set(CMAKE_C_STANDARD 99)

# Check for threading, win32 or posix.
find_package(Threads)

# Only use the pthread header if we don't have win32 threads.
if(CMAKE_USE_PTHREADS_INIT AND NOT CMAKE_USE_WIN32_THREADS_INIT)
    set(HAVE_PTHREAD_H TRUE BOOL)
endif()

add_library(captnlog STATIC src/captnlog.c src/captnlog.h)
target_include_directories(captnlog PUBLIC src ${CMAKE_CURRENT_BINARY_DIR}/src)

# We don't need to link anything if we have win32 threads. Affects MinGW builds primarily.
if(CMAKE_USE_PTHREADS_INIT AND NOT CMAKE_USE_WIN32_THREADS_INIT)
    target_link_libraries(captnlog Threads::Threads)
    target_compile_definitions(captnlog PRIVATE USE_PTHREADS=1)
endif()

# Set the max logging level to debug by default. See captnlog.h for possible levels.
if(CAPTNLOG_LEVEL)
    target_compile_definitions(captnlog PUBLIC LOGGINGLEVEL=${CAPTNLOG_LEVEL})
endif()

if(WIN32 OR "${CMAKE_SYSTEM}" MATCHES "Windows")
    target_compile_definitions(captnlog PRIVATE WIN32_LEAN_AND_MEAN=1 _CRT_SECURE_NO_DEPRECATE=1 _CRT_NONSTDC_NO_DEPRECATE=1 _WINSOCK_DEPRECATED_NO_WARNINGS=1 NOMINMAX=1)
endif()
