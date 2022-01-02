# pico-ads1115

A C library for using [Texas Instrument ADS1115](https://www.ti.com/product/ADS1115) analog-to-digital converter with the Raspberry Pi Pico.

The ADS1115 is a 16-bit, 4 channel delta-sigma ADC. It is interfaced with I2C. Adafruit make a convenient ADC board with this chip ([Adafruit product ID 1085](https://www.adafruit.com/product/1085)).


## Wiring

ADS1115 | Pico 
--------|-----
SDA | SDA (e.g. pin 8)
SCL | SCL (e.g. pin 9)
VDD | 3V3(OUT)
GND | GND

(Note that I2C interfacing requires pull-up resistors, but Adafruit's board already includes these.)

## Software

1. Configure `CMakeLists.txt` in your base project to include the path to the **pico-mpr121** library. Add **pico-ads1115** to the list of target libraries. E.g. if the **pico-ads1115** library is located one directory above (`../`) the current one your `CMakeLists.txt` file should include
```cmake
.
.
.
include(pico_sdk_import.cmake)
add_subdirectory(../pico-ads1115/lib ads1115)

target_link_libraries(touch
        pico_stdlib
        hardware_i2c
        pico-ads1115
)
.
.
.
```

2. Use the library; see the examples directory.
