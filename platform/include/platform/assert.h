/**
 * Assertion handler
 */

#pragma once

#include <assert.h>

#ifdef __cplusplus
extern "C" {
#endif

void platform_assert(const char* expr, const char* file, int line);

#undef assert
#ifdef NDEBUG
#define assert(expr) ((void)0)
#else
#define assert(expr)                                    \
    do {                                                \
        if (!(expr)) {                                  \
            platform_assert(#expr, __FILE__, __LINE__); \
        }                                               \
    } while (0)
#endif

#ifdef __cplusplus
}
#endif
