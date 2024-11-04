#include "core/logger.h"
#include "core/asserts.h"

#include "platform/platform.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void logger_initialize()
{
    
}
void logger_shutdown()
{

}

void log_output(log_levels level, const char* msg, ...)
{
    const char* level_strings[6] = {"[FATAL]: ", "[ERROR]: ", "[WARN]: ", "[INFO]: ", "[DEBUG]: ", "[TRACE]: "};
    b8 is_error = level < LOG_LEVEL_WARN;

    const i32 msg_length = 32000;
    char out_msg[msg_length];
    memset(out_msg, 0, sizeof(out_msg));

    __builtin_va_list arg_ptr;
    va_start(arg_ptr, msg);
    vsnprintf(out_msg, msg_length, msg, arg_ptr);
    va_end(arg_ptr);

    char out_msg2[msg_length];
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
void report_assertion_failure(const char* expression, const char* msg, const char* file, i32 line)
{
    log_output(LOG_LEVEL_FATAL, "Assertion Failure: %s, message: '%s', in file: %s, line: %d\n", expression, msg, file, line);
}
