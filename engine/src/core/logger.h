#pragma once
#include "defines.h"

enum LogLevels 
{
    LOG_LEVEL_FATAL,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_INFO,
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_TRACE,
};

HAPI b8 LoggerInitialize();
HAPI void LoggerShutdown();
HAPI void LoggerPrint(enum LogLevels logLevel, const char* msg, ...);

#define LOG_FATAL_ENABLED 1
#define LOG_ERROR_ENABLED 1
#define LOG_WARN_ENABLED 1
#define LOG_INFO_ENABLED 1
#ifdef DEBUG
#define LOG_DEBUG_ENABLED 1
#define LOG_TRACE_ENABLED 1
#else 
#define LOG_DEBUG_ENABLED 0
#define LOG_TRACE_ENABLED 0
#endif
#if LOG_FATAL_ENABLED == 1
#define HFATAL(msg, ...) LoggerPrint(LOG_LEVEL_FATAL, msg, ##__VA_ARGS__);
#else
#define HFATAL(msg, ...);
#endif
#if LOG_ERROR_ENABLED == 1
#define CHEAP_ERROR(msg, ...) LoggerPrint(LOG_LEVEL_ERROR, msg, ##__VA_ARGS__);
#else
#define CHEAP_ERROR(msg, ...);
#endif
#if LOG_WARN_ENABLED == 1
#define HWARN(msg, ...) LoggerPrint(LOG_LEVEL_WARN, msg, ##__VA_ARGS__);
#else
#define HWARN(msg, ...);
#endif
#if LOG_INFO_ENABLED == 1
#define HINFO(msg, ...) LoggerPrint(LOG_LEVEL_INFO, msg, ##__VA_ARGS__);
#else
#define HINFO(msg, ...);
#endif
#if LOG_DEBUG_ENABLED == 1
#define HDEBUG(msg, ...) LoggerPrint(LOG_LEVEL_DEBUG, msg, ##__VA_ARGS__);
#else
#define HDEBUG(msg, ...);
#endif
#if LOG_TRACE_ENABLED == 1
#define HTRACE(msg, ...) LoggerPrint(LOG_LEVEL_TRACE, msg, ##__VA_ARGS__);
#else
#define HTRACE(msg, ...);
#endif