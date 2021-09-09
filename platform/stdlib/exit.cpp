#include "em_device.h"
#include "core_cm33.h"

extern "C" void _exit(int status)
{
    static_cast<void>(status);
    __NVIC_SystemReset();
}
