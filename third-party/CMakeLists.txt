#------------------------------------------------------------------------------
# cmsis
#------------------------------------------------------------------------------

add_library(cmsis INTERFACE)

target_include_directories(cmsis INTERFACE cmsis/core)

#------------------------------------------------------------------------------
# gecko sdk
#------------------------------------------------------------------------------

add_library(gecko-sdk OBJECT)

target_compile_options(gecko-sdk PRIVATE "-w")

target_compile_definitions(gecko-sdk 
    PUBLIC 
    EFR32BG22C224F512IM40 
    __STARTUP_CLEAR_BSS)

target_link_libraries(gecko-sdk PUBLIC cmsis)

target_include_directories(gecko-sdk 
    PUBLIC 
    silicon-labs/gecko-sdk/device
    silicon-labs/gecko-sdk/emlib/include
    )

target_sources(gecko-sdk
    PRIVATE
    silicon-labs/gecko-sdk/startup_efr32bg22.c
    silicon-labs/gecko-sdk/system_efr32bg22.c
    # emlib
    silicon-labs/gecko-sdk/emlib/source/em_acmp.c
    silicon-labs/gecko-sdk/emlib/source/em_adc.c
    silicon-labs/gecko-sdk/emlib/source/em_aes.c
    silicon-labs/gecko-sdk/emlib/source/em_assert.c
    silicon-labs/gecko-sdk/emlib/source/em_burtc.c
    silicon-labs/gecko-sdk/emlib/source/em_can.c
    silicon-labs/gecko-sdk/emlib/source/em_cmu_fpga.c
    silicon-labs/gecko-sdk/emlib/source/em_cmu.c
    silicon-labs/gecko-sdk/emlib/source/em_core.c
    silicon-labs/gecko-sdk/emlib/source/em_cryotimer.c
    silicon-labs/gecko-sdk/emlib/source/em_crypto.c
    silicon-labs/gecko-sdk/emlib/source/em_csen.c
    silicon-labs/gecko-sdk/emlib/source/em_dac.c
    silicon-labs/gecko-sdk/emlib/source/em_dbg.c
    silicon-labs/gecko-sdk/emlib/source/em_dma.c
    silicon-labs/gecko-sdk/emlib/source/em_ebi.c
    silicon-labs/gecko-sdk/emlib/source/em_emu.c
    silicon-labs/gecko-sdk/emlib/source/em_eusart.c
    silicon-labs/gecko-sdk/emlib/source/em_gpcrc.c
    silicon-labs/gecko-sdk/emlib/source/em_gpio.c
    silicon-labs/gecko-sdk/emlib/source/em_i2c.c
    silicon-labs/gecko-sdk/emlib/source/em_iadc.c
    silicon-labs/gecko-sdk/emlib/source/em_idac.c
    silicon-labs/gecko-sdk/emlib/source/em_lcd.c
    silicon-labs/gecko-sdk/emlib/source/em_ldma.c
    silicon-labs/gecko-sdk/emlib/source/em_lesense.c
    silicon-labs/gecko-sdk/emlib/source/em_letimer.c
    silicon-labs/gecko-sdk/emlib/source/em_leuart.c
    silicon-labs/gecko-sdk/emlib/source/em_msc.c
    silicon-labs/gecko-sdk/emlib/source/em_opamp.c
    silicon-labs/gecko-sdk/emlib/source/em_pcnt.c
    silicon-labs/gecko-sdk/emlib/source/em_pdm.c
    silicon-labs/gecko-sdk/emlib/source/em_prs.c
    silicon-labs/gecko-sdk/emlib/source/em_qspi.c
    silicon-labs/gecko-sdk/emlib/source/em_rmu.c
    silicon-labs/gecko-sdk/emlib/source/em_rtc.c
    silicon-labs/gecko-sdk/emlib/source/em_rtcc.c
    silicon-labs/gecko-sdk/emlib/source/em_se.c
    silicon-labs/gecko-sdk/emlib/source/em_system.c
    silicon-labs/gecko-sdk/emlib/source/em_timer.c
    silicon-labs/gecko-sdk/emlib/source/em_usart.c
    silicon-labs/gecko-sdk/emlib/source/em_vcmp.c
    silicon-labs/gecko-sdk/emlib/source/em_vdac.c
    silicon-labs/gecko-sdk/emlib/source/em_wdog.c
    )

#------------------------------------------------------------------------------
# freertos
#------------------------------------------------------------------------------

# Note: link against "freertos-non-secure" or "freertos-secure" depending on 
# the application's requirements for memory protection & privileged execution.

# FreeRTOS is an interface library because it cannot be built without an 
# application-specific FreeRTOSConfig.h header (and potentially a few 
# application-specific hooks).

# The most straightforward way to include FreeRTOS into an application will be 
# to link against the interface library & make sure a FreeRTOSConfig.h header
# is in the application's include directories (in addition to compiling the 
# required hooks).

add_library(freertos INTERFACE)

target_include_directories(freertos INTERFACE freertos/include)

target_sources(freertos 
    INTERFACE
    freertos/source/queue.c
    freertos/source/stream_buffer.c
    freertos/source/event_groups.c
    freertos/source/list.c
    freertos/source/timers.c
    freertos/source/tasks.c
    freertos/source/croutine.c
    )

#------------------------------------------------------------------------------
# freertos-non-secure
#------------------------------------------------------------------------------

add_library(freertos-non-secure INTERFACE)

target_link_libraries(freertos-non-secure INTERFACE freertos)

target_include_directories(freertos-non-secure INTERFACE freertos/port/non_secure)

target_sources(freertos-non-secure
    INTERFACE
    freertos/port/non_secure/portasm.c
    freertos/port/non_secure/port.c
    )

#------------------------------------------------------------------------------
# freertos-secure
#------------------------------------------------------------------------------

add_library(freertos-secure INTERFACE)

target_link_libraries(freertos-secure INTERFACE freertos)

target_include_directories(freertos-secure INTERFACE freertos/port/secure)

target_sources(freertos-secure
    INTERFACE
    freertos/port/secure/secure_context.c
    freertos/port/secure/secure_heap.c
    freertos/port/secure/secure_context_port.c
    freertos/port/secure/secure_init.c
    )
