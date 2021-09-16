#include <platform/reset.h>

#include "em_device.h"
#include "em_chip.h"

extern "C" void platform_reset()
{
    CHIP_Reset();
}
