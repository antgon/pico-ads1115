cmake_minimum_required(VERSION 3.13)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
add_subdirectory($ENV{PICO_SDK_CONTRIB}/pico-ads1115/lib ads1115)

# Set name of project
project(hello_ads1115 C CXX ASM)

pico_sdk_init()

add_executable(${PROJECT_NAME} ${PROJECT_NAME}.c)

target_link_libraries(
        ${PROJECT_NAME}
        pico_stdlib
        hardware_i2c
        pico-ads1115
)
        
pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})
