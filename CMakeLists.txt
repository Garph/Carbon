cmake_minimum_required(VERSION 3.20)

# Check that CMAKE_BUILD_TYPE is set prior to `project()`
set(ALLOWABLE_BUILD_TYPES "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "CMAKE_BUILD_TYPE defaulted to \"Debug\"")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE 
                 PROPERTY STRINGS ${ALLOWABLE_BUILD_TYPES})
endif()

# Ensure CMAKE_BUILD_TYPE is valid
if(NOT CMAKE_BUILD_TYPE IN_LIST ALLOWABLE_BUILD_TYPES)
    message(FATAL_ERROR "Unsupported build type: ${CMAKE_BUILD_TYPE}")
endif()

project(Carbon LANGUAGES C CXX ASM)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
include(AddEmbeddedExecutable)

# Export a compilation database
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Place binaries and libraries in bin/ and lib/ respectively
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Always colorize compiler & linker output
if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcolor-diagnostics")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics")
endif()
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fdiagnostics-color")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fdiagnostics-color")
endif()

add_subdirectory(applications)
add_subdirectory(platform)
add_subdirectory(third-party)
