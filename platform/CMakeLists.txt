#------------------------------------------------------------------------------
# platform-intf
#------------------------------------------------------------------------------

add_library(platform-intf INTERFACE)

target_include_directories(platform-intf INTERFACE include)

target_link_libraries(platform-intf INTERFACE compiler-warnings)

#------------------------------------------------------------------------------
# platform
#------------------------------------------------------------------------------

add_library(platform OBJECT)

target_link_libraries(platform
    PUBLIC
    platform-intf
    PRIVATE
    gecko-sdk
    )

target_sources(platform
    PRIVATE
    source/assert.cpp
    source/exceptions.cpp
    source/reset.cpp
    source/syscall.cpp
    )
