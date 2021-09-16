/**
 * stdlib _exit
 */

#include "em_device.h"
#include "em_chip.h"

#include "platform/reset.h"

extern "C" void _exit(int status)
{
    static_cast<void>(status);
    platform_reset();
}
