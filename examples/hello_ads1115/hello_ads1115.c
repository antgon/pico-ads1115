/*
 * Copyright (c) 2021-2022 Antonio González
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* ADS1115 hello_ads1115 example

A differential signal is measured between pins A0 and A3. The measured value will be printed to stdout (raw value and voltage).
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "ads1115.h"

#define I2C_PORT i2c0
#define I2C_FREQ 400000
#define ADS1115_I2C_ADDR 0x48
const uint8_t SDA_PIN = 20;
const uint8_t SCL_PIN = 21;

struct ads1115_adc adc;

int main() {
    stdio_init_all();

    // Initialise I2C
    i2c_init(I2C_PORT, I2C_FREQ);
    gpio_set_function(SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(SDA_PIN);
    gpio_pull_up(SCL_PIN);

    // Initialise ADC
    ads1115_init(I2C_PORT, ADS1115_I2C_ADDR, &adc);
    
    // Modify the default configuration as needed. In this example the
    // signal will be differential, measured between pins A0 and A3,
    // and the full-scale voltage range is set to +/- 4.096 V.
    ads1115_set_input_mux(ADS1115_MUX_DIFF_0_3, &adc);
    ads1115_set_pga(ADS1115_PGA_4_096, &adc);
    ads1115_set_data_rate(ADS1115_RATE_475_SPS, &adc);

    // Write the configuration for this to have an effect.
    ads1115_write_config(&adc);

    // Data containers
    float volts;
    uint16_t adc_value;

    while (1) {
        // Read a value, convert to volts, and print.
        ads1115_read_adc(&adc_value, &adc);
        volts = ads1115_raw_to_volts(adc_value, &adc);
        printf("ADC: %u  Voltage: %f\n", adc_value, volts);

        sleep_ms(10);
    }
}