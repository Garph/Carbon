carbon_add_embedded_executable(neopixel-controller)

target_sources(neopixel-controller PUBLIC app.cpp)

target_link_libraries(neopixel-controller
    PUBLIC
    gecko-sdk
    stdlib
    )

target_link_options(neopixel-controller
    PUBLIC
    -T${CMAKE_SOURCE_DIR}/linker/efr32bg22-standalone.ld)
