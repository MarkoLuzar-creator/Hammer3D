#pragma once

#include "defines.h"

#ifdef _DEBUG

    #if _MSC_VER
        #include <intrin.h>
        #define debugBreak() __debugbreak()
    #else
        #define debugBreak() __builtin_trap()
    #endif

    CHEAP_API void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line);

    #define CHEAP_ASSERT(expr)                                          \
    {                                                                   \
        if (!expr)                                                      \
        {                                                               \
            report_assertion_failure(#expr, "", __FILE__, __LINE__);    \
            debugBreak();                                               \
        }                                                               \                                                    \                                                        \
    }     

    #define CHEAP_ASSERT_MSG(expr, message)                                          \
    {                                                                                \
        if (!expr)                                                                   \
        {                                                                            \
            report_assertion_failure(#expr, message, __FILE__, __LINE__);            \
            debugBreak();                                                            \
        }                                                                            \                                                                     \
    }     

    #ifdef _DEBUG
        #define CHEAP_ASSERT_DEBUG(expr, message)                                        \
        {                                                                                \
            if (!expr)                                                                   \
            {                                                                            \
                report_assertion_failure(#expr, "", __FILE__, __LINE__);                 \
                debugBreak();                                                            \
            }                                                                            \                                                                      \
        }      
    #else
        #define CHEAP_ASSERT_DEBUG(expr)
    #endif

#else
    #define CHEAP_ASSERT(expr)
    #define CHEAP_ASSERT_MSG(expr, message)
    #define CHEAP_ASSERT_DEBUG(expr) 
#endif 
