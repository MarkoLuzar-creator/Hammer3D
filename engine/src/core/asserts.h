#pragma once

#include "defines.h"

#define KASSERTIONS_ENABLED

#ifdef KASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak()
#else
#define debugBreak() __builtin_trap()
#endif

MAPI void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line);

#define MASSERT(expr)                                                   \
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


#define MASSERT_MSG(expr, message)                                                   \
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
#define MASSERT_DEBUG(expr, message)                                                 \
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
#define MASSERT_DEBUG(expr)
#endif

#else
#define MASSERT(expr)
#define MASSERT_MSG(expr, message)
#define MASSRT_DEBUG(expr)
#endif