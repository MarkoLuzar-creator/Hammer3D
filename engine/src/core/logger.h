#pragma once

#include "defines.h"

#define LOG_WARNING_ENABLED 1
#define LOG_INFO_ENABLED 1
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1

#if KRELEASE == 1
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif

typedef enum log_level
{
    LOG_LEVEL_FETAL,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_TRACE,
} log_level;

b8 initialize_logging();
void shutdown_logging();

MOJAPI void log_output(log_level level, const char* msg, ...);

#define MOJFATAL(msg, ...) log_output(LOG_LEVEL_FETAL, msg, ##__VA_ARGS__);

#define MOJERROR(msg, ...) log_output(LOG_LEVEL_ERROR, msg, ##__VA_ARGS__);

#if LOG_WARNING_ENABLED == 1
#define MOJWARING(msg, ...) log_output(LOG_LEVEL_WARNING, msg, ##__VA_ARGS__);
#else
#define MOJWARING(msg, ...);
#endif

#if LOG_INFO_ENABLED == 1
#define MOJINFO(msg, ...) log_output(LOG_LEVEL_INFO, msg, ##__VA_ARGS__);
#else
#define MOJINFO(msg, ...);
#endif

#if LOG_DEBUG_ENABLED == 1
#define MOJDEBUG(msg, ...) log_output(LOG_LEVEL_DEBUG, msg, ##__VA_ARGS__);
#else
#define MOJDEBUG(msg, ...);
#endif

#if LOG_TRACE_ENABLED == 1
#define MOJTRACE(msg, ...) log_output(LOG_LEVEL_TRACE, msg, ##__VA_ARGS__);
#else
#define MOJTRACE(msg, ...);
#endif