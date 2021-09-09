# EFR32BG22 Linker Scripts

The linker script for an application can be specified as follows:

```cmake
add_executable(foo)

target_link_options(foo PRIVATE 
    "-T${CMAKE_SOURCE_DIR}/linker/efr32bg22-standalone.ld")
```

There are three linker scripts to choose from:

* `efr32bg22-standalone.ld`: For applications that do not use bootloaders
* `efr32bg22-app.ld`: For applications that use bootloaders
* `efr32bg22-boot.ld`: For bootloaders

### Notable Sections

* `.vectors`: Interrupt vector table placed at beginning of flash. The core 
loads the MSP and Reset_Handler from this table on startup.
* `.app_properties`: Table of application-specific properties placed after `.vectors` near the beginning of flash.
* `.boot_message`: A region of RAM that persists through a system reset for storing messages from applications for the bootloader.
* `.reset_log`: A region of RAM that persists through a system reset for storing a circular buffer of reset log entries.
* `.heap`:  Ascending heap placed after `.preserved_ram`
* `.stack`: Descending stack placed at top of RAM.

### Symbols provided by linker scripts
```
__exidx_start
__exidx_end
__copy_table_start__
__copy_table_end__
__zero_table_start__
__zero_table_end__
__etext
__data_start__
__preinit_array_start
__preinit_array_end
__init_array_start
__init_array_end
__fini_array_start
__fini_array_end
__data_end__
__bss_start__
__bss_end__
__end__
end
__HeapBase
__HeapLimit
__StackLimit
__StackTop
__stack
__Vectors_End
__Vectors_Size
```

### Symbols required by linker scripts
```
Reset_Handler
```
