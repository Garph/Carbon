carbon_add_embedded_executable(neopixel_controller)

target_include_directories(neopixel_controller PUBLIC .)

target_sources(neopixel_controller 
    PUBLIC 
    app.cpp
    neopixel_lookup_table.cpp
    neopixel_controller.cpp
    )

target_link_libraries(neopixel_controller
    PUBLIC
    gecko-sdk
    platform
    compiler-warnings
    )

target_link_options(neopixel_controller
    PUBLIC
    -T${CMAKE_SOURCE_DIR}/linker/efr32bg22-standalone.ld
    )
