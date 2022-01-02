/*
 * Copyright (c) 2021-2022 Antonio González
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "ads1115.h"

// #define ADS1115_I2C_PORT i2c0
// const uint8_t ADS1115_I2C_ADDR = 0x48;
#define I2C_FREQ 400000
const uint8_t ADS1115_SDA_PIN = 12;
const uint8_t ADS1115_SCL_PIN = 13;

int main() {
    stdio_init_all();

    // Initialise I2C
    i2c_init(ADS1115_I2C_PORT, I2C_FREQ);

    // Initialise ADC
    uint16_t config;
    ads1115_init(ADS1115_SDA_PIN, ADS1115_SCL_PIN, &config);
    
    // Modify the default configuration as needed. In this example the
    // signal will be differential, measured between pins A0 and A3,
    // and the full-scale voltage range is set to +/- 4.096 V.
    ads1115_set_input_mux(&config, ADS1115_MUX_DIFF_0_3);
    ads1115_set_pga(&config, ADS1115_PGA_4_096);

    // Write the configuration for this to have an effect.
    ads1115_write_config(config);

    // Data containers
    float volts;
    uint16_t adc_value;

    while (1) {
        // Read a value, convert to volts, and print.
        ads1115_read_adc(&config, &adc_value);
        volts = ads1115_raw_to_volts(&config, adc_value);
        printf("ADC: %u  Voltage: %f\n", adc_value, volts);

        sleep_ms(1000);
    }
}