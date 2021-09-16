#include "neopixel_controller.h"

#include "em_device.h"

#include "em_chip.h"
#include "em_emu.h"

extern "C" int main()
{
    CHIP_Init();

    EMU_DCDCInit_TypeDef dcdcInit = EMU_DCDCINIT_DEFAULT;
    EMU_DCDCInit(&dcdcInit);

    neopixel_controller_init();

    uint8_t i = 0;

    while (true) {

        for (; i < 255; i++) {
            neopixel_controller_send(0, i, 0);
            for (unsigned int d = 0; d < 1'000'000u / 4; d++) {}  // delay
        }

        for (; i > 0u; i--) {
            neopixel_controller_send(0, i, 0);
            for (unsigned int d = 0; d < 1'000'000u / 4; d++) {}  // delay
        }
    }

    return 0;
}
