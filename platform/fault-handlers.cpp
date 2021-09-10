#include "em_device.h"

#include <cstdint>

/*-----------------------------------------------------------------------------
 * Types
 *---------------------------------------------------------------------------*/

struct StackedRegisters
{
    // caller-stacked registers
    unsigned int r0;
    unsigned int r1;
    unsigned int r2;
    unsigned int r3;
    unsigned int r12;

    unsigned int LR;
    unsigned int PC;
    unsigned int xPSR;
};

static volatile StackedRegisters* stackedRegisters{nullptr};

/*-----------------------------------------------------------------------------
 * Hard Fault Handler
 *---------------------------------------------------------------------------*/

extern "C" void HardFault_Handler_C(uint32_t msp, uint32_t excReturn)
{

    // TODO: Support DCRS, FTYPE, MODE, and ES bits of EXC_RETURN

    if (excReturn & EXC_RETURN_SPSEL) {
        // registers were pushed onto PSP during exception entry
        stackedRegisters = reinterpret_cast<StackedRegisters*>(__get_PSP());
    } else {
        // registeres were pushed onto MSP during exception entry
        stackedRegisters = reinterpret_cast<StackedRegisters*>(msp);
    }

    static_cast<void>(stackedRegisters);

    for (;;) {}
}

extern "C" void __attribute__((naked)) HardFault_Handler(void)
{
    /**
     * The "naked" function attribute instructs the compiler to not generate a
     * function prolog (e.g., don't push registers onto the stack). During the
     * assembly code, we save the EXC_RETURN value (stored in LR) and
     * current value of the MSP.
     *
     * The branch to `HardFault_Handler_C()` _may_ overwrite LR and MSP, good
     * thing we saved them for later!
     */

    asm volatile(
      "mov r0, sp \n\t"
      "mov r1, lr \n\t"
      "b HardFault_Handler_C\n\t");
}
