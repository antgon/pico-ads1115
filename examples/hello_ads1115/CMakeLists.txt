# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Pull in Raspberry Pi Pico SDK (must be before project)
include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

# Add pico-ads1115 directory
add_subdirectory(../../lib ads1115)

# Set the name of the project
project(hello_mpr121 C CXX ASM)

pico_sdk_init()
add_executable(${PROJECT_NAME} ${PROJECT_NAME}.c)

pico_add_extra_outputs(${PROJECT_NAME})

# Standard and additional libraries.
target_link_libraries(
        ${PROJECT_NAME}
        pico_stdlib
        hardware_i2c
        pico-ads1115
        )

# This stdio configuration alows to see the Pico output when connected
# to a picoprobe. Enable usb and disable uart for standalone operation
# (direct USB connection).
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_enable_stdio_usb(${PROJECT_NAME} 1)