# CMake toolchain file to compile for Cortex-M33 devices with 
# the GNU ARM Embedded toolchain

set(CMAKE_SYSTEM_NAME       Generic)
set(CMAKE_SYSTEM_PROCESSOR  ARM)

set(CMAKE_C_COMPILER        arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER      arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER      arm-none-eabi-gcc)
set(CMAKE_SIZE              arm-none-eabi-size)
set(CMAKE_OBJCOPY           arm-none-eabi-objcopy)

string(JOIN " " _COMMON_FLAGS
    
    # Cortex-M33 Arch
    "-mthumb"
    "-mcpu=cortex-m33"
    "-mfpu=fpv5-sp-d16"
    "-mfloat-abi=hard"

    # TODO: Do a deep dive on these compiler flags
    "-fno-builtin"

    # Creates seperate sections within the object file. The linker can remove
    # unused sections.
    "-ffunction-sections"
    "-fdata-sections"

    # Prevent the reordering of instructions in the function prolog
    "-mno-sched-prolog"
    )

string(JOIN " " _CXX_FLAGS
    # Disable C++ foot guns
    "-fno-exceptions"
    "-fno-threadsafe-statics"
    "-fno-rtti"
    )

set(CMAKE_C_FLAGS_INIT              "${_COMMON_FLAGS}")
set(CMAKE_CXX_FLAGS_INIT            "${_COMMON_FLAGS} ${_CXX_FLAGS}")
set(CMAKE_ASM_FLAGS_INIT            "${_COMMON_FLAGS} -x assembler-with-cpp")
set(CMAKE_EXE_LINKER_FLAGS_INIT     "${_COMMON_FLAGS} --specs=nano.specs --specs=nosys.specs -Xlinker --gc-sections")

#------------------------------------------------------------------------------
# CMAKE_BUILD_TYPE: Debug
#------------------------------------------------------------------------------

set(_DEBUG_FLAGS                "-Og -g")
set(CMAKE_C_FLAGS_DEBUG_INIT    ${_DEBUG_FLAGS})
set(CMAKE_CXX_FLAGS_DEBUG_INIT  ${_DEBUG_FLAGS})
