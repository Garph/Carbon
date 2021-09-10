add_library(platform OBJECT)

target_sources(platform 
    PRIVATE
    assert.cpp
    exit.cpp 
    fault-handlers.cpp
    )

target_include_directories(platform
    PUBLIC
    include
    )

target_link_libraries(platform PRIVATE gecko-sdk)
