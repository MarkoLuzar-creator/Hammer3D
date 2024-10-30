#include "logger.h"

#include "asserts.h"

#include "platform/platform.h"

#include <stdio.h>

#include <string.h>

#include <stdarg.h>

void report_assertion_failure(const char* expression, const char* msg, const char* file, i32 line)
{
    log_output(LOG_LEVEL_FETAL, "Assertion Failure: %s, message: '%s', in file: %s, line: %d\n", expression, msg, file, line);
}

b8 initialize_logging()
{
    return TRUE;
}

void shutdown_logging()
{

}

void log_output(log_level level, const char* msg, ...)
{
    const char* level_strings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARNING]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
    b8 is_error = level < LOG_LEVEL_WARNING;

    const i32 msg_lenght = 32000;
    char out_msg[msg_lenght];
    memset(out_msg, 0, sizeof(out_msg));

    __builtin_va_list arg_ptr;
    va_start(arg_ptr, msg);
    vsnprintf(out_msg, msg_lenght, msg, arg_ptr);
    va_end(arg_ptr);

    char out_msg2[msg_lenght];
    sprintf(out_msg2, "%s%s\n", level_strings[level], out_msg);

    if (is_error)
    {
        platform_console_write_error(out_msg2, level);
    }
    else 
    {
        platform_console_write(out_msg2, level);
    }
}
