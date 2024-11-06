#pragma once

#include "defines.h"

#ifdef DEBUG
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif
HAPI void ReportAssertionFailure(const char* expression, const char* message, const char* file, i32 line);
#define HASSERT(expr)                                          \
{                                                                   \
    if (!expr)                                                      \
    {                                                               \
        ReportAssertionFailure(#expr, "", __FILE__, __LINE__);    \
        debugBreak();                                               \
    }                                                               \                                                    \                                                        \
}     

#define HASSERT_MSG(expr, message)                                          \
{                                                                                \
    if (!expr)                                                                   \
    {                                                                            \
        ReportAssertionFailure(#expr, message, __FILE__, __LINE__);            \
        debugBreak();                                                            \
    }                                                                            \                                                                     \
}     

#ifdef DEBUG
#define HASSERT_DEBUG(expr, message)                                        \
{                                                                                \
    if (!expr)                                                                   \
    {                                                                            \
        ReportAssertionFailure(#expr, "", __FILE__, __LINE__);                 \
        debugBreak();                                                            \
    }                                                                            \                                                                      \
}      
#else
#define HASSERT_DEBUG(expr)
#endif
#else
#define HASSERT(expr)
#define HASSERT_MSG(expr, message)
#define HASSERT_DEBUG(expr) 
#endif 
