/**
 * Assertion handler
 */

#include "platform/assert.h"

extern "C" void platform_assert(const char* expr, const char* file, int line)
{
    static_cast<void>(expr);
    static_cast<void>(file);
    static_cast<void>(line);
    for (;;) {}
}
