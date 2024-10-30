#pragma once

#include "defines.h"

#define MOJASSERTIONS_ENABLED
#ifdef MOJASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

MOJAPI void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line);

#define MOJASSERT(expr)                                             \
{                                                                   \
    if (expr)                                                       \
    {                                                               \
                                                                    \
    }                                                               \
    else                                                            \
    {                                                               \
        report_assertion_failure(#expr, "", __FILE__, __LINE__);    \
        debugBreak();                                               \
    }                                                               \
}     

#define MOJASSERT_MSG(expr, message)                                             \
{                                                                                \
    if (expr)                                                                    \
    {                                                                            \
                                                                                 \
    }                                                                            \
    else                                                                         \
    {                                                                            \
        report_assertion_failure(#expr, message, __FILE__, __LINE__);            \
        debugBreak();                                                            \
    }                                                                            \
}     
                                                                           
#ifdef _DEBUG
#define MOJASSERT_DEBUG(expr, message)                                           \
{                                                                                \
    if (expr)                                                                    \
    {                                                                            \
                                                                                 \
    }                                                                            \
    else                                                                         \
    {                                                                            \
        report_assertion_failure(#expr, "", __FILE__, __LINE__);                 \
        debugBreak();                                                            \
    }                                                                            \
}                                                                                
#else
#define MOJASSERT_DEBUG(expr)
#endif
#else
#define MOJASSERT(expr)
#define MOJASSERT_MSG(expr, message)
#define MASSRT_DEBUG(expr)
#endif