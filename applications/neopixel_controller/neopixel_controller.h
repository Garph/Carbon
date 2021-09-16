#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

/*-----------------------------------------------------------------------------
 * Constants
 *---------------------------------------------------------------------------*/

/**
 * Number of LEDs in the neopixel strip
 */
static constexpr size_t NUM_LEDS = 60;

extern const std::array<const uint32_t, 256> neopixel_lookup_table;

/*-----------------------------------------------------------------------------
 * Public Functions
 *---------------------------------------------------------------------------*/

/**
 * Initialize hardware for the neopixel controller
 */
void neopixel_controller_init();

/**
 * Transmit pixel intensity levels to LED strip
 */
void neopixel_controller_send(uint8_t red, uint8_t green, uint8_t blue);
