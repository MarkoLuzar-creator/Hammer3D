#pragma once

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;
typedef float f32;
typedef double f64;
typedef char b8;
typedef int b32;

#if defined(__clang__) || defined(__gcc__)
#define STATIC_ASSERT _Static_assert
#else
#define STATIC_ASSERT static_assert
#endif
STATIC_ASSERT(sizeof(u8) == 1, "Expected u8 to be 1 byte!");
STATIC_ASSERT(sizeof(u16) == 2, "Expected u16 to be 2 bytes!");
STATIC_ASSERT(sizeof(u32) == 4, "Expected u32 to be 4 bytes!");
STATIC_ASSERT(sizeof(u64) == 8, "Expected u64 to be 8 bytes!");
STATIC_ASSERT(sizeof(i8) == 1, "Expected i8 to be 1 byte!");
STATIC_ASSERT(sizeof(i16) == 2, "Expected i16 to be 2 bytes!");
STATIC_ASSERT(sizeof(i32) == 4, "Expected i32 to be 4 bytes!");
STATIC_ASSERT(sizeof(i64) == 8, "Expected i64 to be 8 bytes!");
STATIC_ASSERT(sizeof(f32) == 4, "Expected f32 to be 4 bytes!");
STATIC_ASSERT(sizeof(f64) == 8, "Expected f64 to be 8 bytes!");
STATIC_ASSERT(sizeof(b8) == 1, "Expected b8 to be 1 byte!");
STATIC_ASSERT(sizeof(b32) == 4, "Expected f64 to be 4 bytes!");

#define TRUE 1
#define FALSE 0

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) 
#define PLATFORM_WINDOWS
#ifndef _WIN64
#error "64-bit is required on Windows!"
#endif
#elif defined(__linux__) || defined(__gnu_linux__)
#define PLATFORM_LINUX
#if defined(__ANDROID__)
#define PLATFORM_ANDROID
#endif
#elif defined(__unix__)
#define PLATFORM_UNIX
#elif defined(_POSIX_VERSION)
#define PLATFORM_POSIX
#elif __APPLE__
#define MKPLATFORM_APPLE
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
#define PLATFORM_IOS
#define PLATFORM_IOS_SIMULATOR
#elif TARGET_OS_IPHONE
#define PLATFORM_IOS
#elif TARGET_OS_MAC
#else
#error "Unknown Apple platform"
#endif
#else
#error "Unknown platform!"
#endif

#ifdef HEXPORT
#ifdef _MSC_VER
#define HAPI __declspec(dllexport)
#else
#define HAPI __attribute__((visibility("default")))
#endif
#else
#ifdef _MSC_VER
#define HAPI __declspec(dllimport)
#else
#define HAPI
#endif
#endif