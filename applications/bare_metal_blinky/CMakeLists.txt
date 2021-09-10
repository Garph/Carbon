carbon_add_embedded_executable(bare_metal_blinky)

target_sources(bare_metal_blinky PUBLIC app.cpp)

target_link_libraries(bare_metal_blinky
    PUBLIC
    gecko-sdk
    platform
    compiler-warnings
    )

target_link_options(bare_metal_blinky
    PUBLIC
    -T${CMAKE_SOURCE_DIR}/linker/efr32bg22-standalone.ld
    )
