function(carbon_add_embedded_executable TARGET)

    add_executable(${TARGET} ${ARGN})

    set_target_properties(${TARGET} PROPERTIES SUFFIX .elf)

    # Output a Map file
    target_link_options(${TARGET} PUBLIC
        -Wl,-Map=$<TARGET_FILE_DIR:${TARGET}>/$<TARGET_FILE_BASE_NAME:${TARGET}>.map)

    add_custom_command(
        TARGET ${TARGET}
        POST_BUILD
        # Print executable size
        COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${TARGET}>
        # Copy the executable, converting to Intel hex format in the process
        COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${TARGET}>
                $<TARGET_FILE_DIR:${TARGET}>/$<TARGET_FILE_BASE_NAME:${TARGET}>.hex)

endfunction()
