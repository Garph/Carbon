/**
 * A single-file application to blink the on-board LED while in deep-sleep
 * using a low-energy timer peripheral.
 */

#include "em_device.h"

#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_letimer.h"
#include "em_prs.h"

#include "platform/oscillators.h"

/*-----------------------------------------------------------------------------
 * Constants
 *---------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------
 * Main
 *---------------------------------------------------------------------------*/

extern "C" int main(void)
{
    __NOP();

    /*-------------------------------------------------------------------------
     * Microcontroller-specific initialization
     *-----------------------------------------------------------------------*/

    // Erata fixes
    CHIP_Init();

    // Configure the EMU to reset the processor during LOCKUP
    BUS_RegBitWrite(&EMU->RSTCTRL, EMU_RSTCTRL_LOCKUPRMODE, 1u);

    // Use vector catch (VC) to debug trap on exceptions
    static constexpr uint32_t DEMCR_MASK =
      DCB_DEMCR_VC_SFERR_Msk | DCB_DEMCR_VC_HARDERR_Msk
      | DCB_DEMCR_VC_INTERR_Msk | DCB_DEMCR_VC_BUSERR_Msk
      | DCB_DEMCR_VC_STATERR_Msk | DCB_DEMCR_VC_CHKERR_Msk
      | DCB_DEMCR_VC_NOCPERR_Msk | DCB_DEMCR_VC_MMERR_Msk
      | DCB_DEMCR_VC_CORERESET_Msk;

    BUS_RegMaskedSet(&DCB->DEMCR, DEMCR_MASK);

    // Use all priority bits for "preempt priority" (no "sub-priority")
    NVIC_SetPriorityGrouping(0);

    // Set all configurable interrupt priorities to lowest priority
    static constexpr unsigned int NVIC_MINIMUM_PRIORITY =
      (1 << __NVIC_PRIO_BITS) - 1;
    for (int i = static_cast<int>(SVCall_IRQn); i < EXT_IRQ_COUNT; i++) {
        NVIC_SetPriority(static_cast<IRQn_Type>(i), NVIC_MINIMUM_PRIORITY);
    }

    /*-------------------------------------------------------------------------
     * Application-specific initialization
     *-----------------------------------------------------------------------*/

    /**
     * Clock Initialization
     * - The 20 MHz FSRCO is used for a system clock on startup
     * - Enable the 32.768 kHz LFRCO
     * - Configure clock branches to use FSRCO/LFRCO
     * - Enable peripheral clocks
     */

    CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);

    /**
     * Peripherals that run directly off of the APB Clock
     */
    CMU->CLKEN0_SET = CMU_CLKEN0_GPIO;
    CMU->CLKEN0_SET = CMU_CLKEN0_PRS;


    // Select the LFRCO to drive LETIMER0 (EM2/3 Group A peripherals)
    CMU->EM23GRPACLKCTRL_SET = CMU_EM23GRPACLKCTRL_CLKSEL_LFRCO;
    CMU->CLKEN0_SET = CMU_CLKEN0_LETIMER0;

    /**
     * LETIMER0 Initialization
     * - Underflow at 1 Hz
     */

    LETIMER_Init_TypeDef letimerInit = LETIMER_INIT_DEFAULT;
    letimerInit.topValue = CMU_ClockFreqGet(cmuClock_EM23GRPACLK);
    letimerInit.ufoa0 = letimerUFOAToggle;

    LETIMER_Init(LETIMER0, &letimerInit);

    /**
     * Route LETIMER0's underflow action to PRS
     */

    PRS_SourceAsyncSignalSet(0,
      PRS_ASYNC_CH_CTRL_SOURCESEL_LETIMER0,
      PRS_ASYNC_CH_CTRL_SIGSEL_LETIMER0CH0);


    /**
     * Configure LED0 pin as digital output
     */

    GPIO_PinModeSet(gpioPortB, 0UL, gpioModePushPull, 0);
    PRS_PinOutput(0, prsTypeAsync, gpioPortB, 0);

    /*-------------------------------------------------------------------------
     * App
     *-----------------------------------------------------------------------*/

    for (;;) {}
}
