#pragma once

#include "defines.h"

typedef enum
{
    LOG_LEVEL_FATAL,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_TRACE,
} log_levels;

CHEAP_API void logger_initialize();
CHEAP_API void logger_shutdown();

CHEAP_API void log_output(log_levels level, const char* msg, ...);

#define LOG_FATAL_ENABLED 1
#define LOG_ERROR_ENABLED 1
#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1

#ifdef _DEBUG
    #define LOG_DEBUG_ENABLED 1
    #define LOG_TRACE_ENABLED 1
#else 
    #define LOG_DEBUG_ENABLED 0
    #define LOG_TRACE_ENABLED 0
#endif

#if LOG_FATAL_ENABLED == 1
    #define CHEAP_FATAL(msg, ...) log_output(LOG_LEVEL_FATAL, msg, ##__VA_ARGS__);
#else
    #define CHEAP_FATAL(msg, ...);
#endif

#if LOG_ERROR_ENABLED == 1
    #define CHEAP_ERROR(msg, ...) log_output(LOG_LEVEL_ERROR, msg, ##__VA_ARGS__);
#else
    #define CHEAP_ERROR(msg, ...);
#endif

#if LOG_WARN_ENABLED == 1
    #define CHEAP_WARN(msg, ...) log_output(LOG_LEVEL_WARN, msg, ##__VA_ARGS__);
#else
    #define CHEAP_WARN(msg, ...);
#endif

#if LOG_INFO_ENABLED == 1
    #define CHEAP_INFO(msg, ...) log_output(LOG_LEVEL_INFO, msg, ##__VA_ARGS__);
#else
    #define CHEAP_INFO(msg, ...);
#endif

#if LOG_DEBUG_ENABLED == 1
    #define CHEAP_DEBUG(msg, ...) log_output(LOG_LEVEL_DEBUG, msg, ##__VA_ARGS__);
#else
    #define CHEAP_DEBUG(msg, ...);
#endif

#if LOG_TRACE_ENABLED == 1
    #define CHEAP_TRACE(msg, ...) log_output(LOG_LEVEL_TRACE, msg, ##__VA_ARGS__);
#else
    #define CHEAP_TRACE(msg, ...);
#endif