/*
 * Copyright (c) 2021 Antonio González
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "ads1115.h"

void ads1115_init(uint8_t sda_pin, uint8_t scl_pin, uint16_t *config){
    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(sda_pin);
    gpio_pull_up(scl_pin);
    ads1115_read_config(config);
}

void ads1115_read_adc(uint16_t *config, uint16_t *adc_value){
    // If mode is single-shot, set bit 15 to start the conversion.
    if ((*config & ADS1115_MODE_MASK) == ADS1115_MODE_SINGLE_SHOT){
        *config |= 0x8000;//ADS1115_STATUS_START;
        ads1115_write_config(*config);

        // Wait until the conversion finishes before reading the value
        ads1115_read_config(config);
        while (*config & ADS1115_STATUS_MASK == ADS1115_STATUS_BUSY){
            ads1115_read_config(config);
        }
    }

    // Now read the value from last conversion
    uint8_t dst[2];
    i2c_write_blocking(ADS1115_I2C_PORT, ADS1115_I2C_ADDR,
                       &ADS1115_POINTER_CONVERSION, 1, true);
    i2c_read_blocking(ADS1115_I2C_PORT, ADS1115_I2C_ADDR, &dst, 2,
                      false);
    *adc_value = (dst[0] << 8) | dst[1];
}

float ads1115_raw_to_volts(uint16_t *config, uint16_t adc_value) {
    // Determine the full-scale voltage range (FSR) based on the 
    // PGA set in the configuration.
    float fsr;
    uint16_t pga = *config & ADS1115_PGA_MASK;
    switch (pga) {
        case ADS1115_PGA_6_144:
            fsr = 6.144;
            break;
        case ADS1115_PGA_4_096:
            fsr = 4.096;
            break;
        case ADS1115_PGA_2_048:
            fsr = 2.048;
            break;
        case ADS1115_PGA_1_024:
            fsr = 1.024;
            break;
        case ADS1115_PGA_0_512:
            fsr = 0.512;
            break;
        case ADS1115_PGA_0_256:
            fsr = 0.256;
            break;
    }

    // Convert the ADC value from two's complement to voltage
    float voltage;
    if (adc_value & 0x8000) {
        adc_value = (adc_value ^ 0xffff) + 1;
        voltage = -fsr * (float)adc_value / 0x8000;
    } else {
        voltage = fsr * (float)adc_value / 0x8000;
    }
    return voltage;
}

void ads1115_read_config(uint16_t *config){
    // Default configuration after power up should be 34179.
    // Default config with bit 15 cleared is 1411
    uint8_t dst[2];
    i2c_write_blocking(ADS1115_I2C_PORT, ADS1115_I2C_ADDR,
                       &ADS1115_POINTER_CONFIGURATION, 1, true);
    i2c_read_blocking(ADS1115_I2C_PORT, ADS1115_I2C_ADDR, &dst, 2,
                      false);
    *config = (dst[0] << 8) | dst[1];
}

void ads1115_write_config(uint16_t config){
    uint8_t src[3];
    src[0] = ADS1115_POINTER_CONFIGURATION;
    src[1] = (uint8_t)(config >> 8);
    src[2] = (uint8_t)(config & 0xff);
    i2c_write_blocking(ADS1115_I2C_PORT, ADS1115_I2C_ADDR, &src, 3,
                       false);
}

void ads1115_set_input_mux(uint16_t *config, enum ads1115_mux_t mux){
    *config &= ~ADS1115_MUX_MASK;
    *config |= mux;
}

void ads1115_set_pga(uint16_t *config, enum ads1115_pga_t pga){
    *config &= ~ADS1115_PGA_MASK;
    *config |= pga;
}

void ads1115_set_operating_mode(uint16_t *config,
                                enum ads1115_mode_t mode){
    *config &= ~ADS1115_MODE_MASK;
    *config |= mode;
}

void ads1115_set_data_rate(uint16_t *config, enum ads1115_rate_t rate){
    *config &= ~ADS1115_RATE_MASK;
    *config |= rate;
}