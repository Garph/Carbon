#include "em_device.h"
#include "em_chip.h"

extern "C" void _exit(int status)
{
    static_cast<void>(status);
    CHIP_Reset();
}
