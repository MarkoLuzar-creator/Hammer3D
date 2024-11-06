#include "core/logger.h"
#include "core/asserts.h"
#include "platform/platform.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

b8 LoggerInitialize()
{
    // TODO: Create log file
   return TRUE; 
}

void LoggerShutdown()
{
    // TODO: cleanup logging write
}

void LoggerPrint(enum LogLevels logLevel, const char* msg, ...)
{
    const char* levelStrings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
    char log[32000];
    memset(log, 0, sizeof(log));
    snprintf(log, sizeof(log), "%s", levelStrings[logLevel]);
    const u32 logLength = strlen(log);
    __builtin_va_list arguments;
    va_start(arguments, msg);
    vsnprintf(log + logLength, sizeof(log) - logLength, msg, arguments);
    va_end(arguments);
    const u32 logCurrentLen = strlen(log);
    if (logCurrentLen < sizeof(log) - 1) 
    {
        log[logCurrentLen] = '\n';
        log[logCurrentLen + 1] = '\0';
    }

    b8 isError = logLevel < LOG_LEVEL_WARN;
    if (isError) platform_console_write_error(log, logLevel);
    else platform_console_write(log, logLevel);
}

void ReportAssertionFailure(const char* expression, const char* msg, const char* file, i32 line)
{
    LoggerPrint(LOG_LEVEL_FATAL, "Assertion Failure: %s, message: '%s', in file: %s, line: %d\n", expression, msg, file, line);
}
