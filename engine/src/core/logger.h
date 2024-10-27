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

typedef enum
{
    LOG_LEVEL_FETAL = 0,
    LOG_LEVEL_ERROR = 1,
    LOG_LEVEL_WARNING = 2,
    LOG_LEVEL_INFO = 3,
    LOG_LEVEL_DEBUG = 4,
    LOG_LEVEL_TRACE = 5,
} log_level;

b8 initialize_logging();
void shutdown_logging();

KAPI void log_output(log_level level, const char *msg, ...);

#define KFATAL(msg, ...) log_output(LOG_LEVEL_FETAL, msg, ##__VA_ARGS__);

#define KERROR(msg, ...) log_output(LOG_LEVEL_ERROR, msg, ##__VA_ARGS__);

#if LOG_WARNING_ENABLED == 1
#define KWARNING(msg, ...) log_output(LOG_LEVEL_WARNING, msg, ##__VA_ARGS__);
#else
#define KWARNING(msg, ...);
#endif

#if LOG_INFO_ENABLED == 1
#define KINFO(msg, ...) log_output(LOG_LEVEL_INFO, msg, ##__VA_ARGS__);
#else
#define KINFO(msg, ...);
#endif

#if LOG_DEBUG_ENABLED == 1
#define KDEBUG(msg, ...) log_output(LOG_LEVEL_DEBUG, msg, ##__VA_ARGS__);
#else
#define KDEBUG(msg, ...);
#endif

#if LOG_TRACE_ENABLED == 1
#define KTRACE(msg, ...) log_output(LOG_LEVEL_TRACE, msg, ##__VA_ARGS__);
#else
#define KTRACE(msg, ...);
#endif