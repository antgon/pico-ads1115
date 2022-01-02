/*
 * Copyright (c) 2021-2022 Antonio González
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "ads1115.h"

void ads1115_init(i2c_inst_t *i2c_port, uint8_t i2c_addr,
                  ads1115_adc_t *adc) {
    adc->i2c_port = i2c_port;
    adc->i2c_addr = i2c_addr;
    ads1115_read_config(adc);
}

void ads1115_read_adc(uint16_t *adc_value, ads1115_adc_t *adc){
    // If mode is single-shot, set bit 15 to start the conversion.
    if ((adc->config & ADS1115_MODE_MASK) == ADS1115_MODE_SINGLE_SHOT) {
        adc->config |= 0x8000;//ADS1115_STATUS_START;
        ads1115_write_config(adc);

        // Wait until the conversion finishes before reading the value
        ads1115_read_config(adc);
        while (adc->config & ADS1115_STATUS_MASK == ADS1115_STATUS_BUSY){
            ads1115_read_config(adc);
        }
    }

    // Now read the value from last conversion
    uint8_t dst[2];
    i2c_write_blocking(adc->i2c_port, adc->i2c_addr,
                       &ADS1115_POINTER_CONVERSION, 1, true);
    i2c_read_blocking(adc->i2c_port, adc->i2c_addr, &dst, 2,
                      false);
    *adc_value = (dst[0] << 8) | dst[1];
}

float ads1115_raw_to_volts(uint16_t adc_value, ads1115_adc_t *adc) {
    // Determine the full-scale voltage range (FSR) based on the 
    // PGA set in the configuration.
    float fsr;
    uint16_t pga = adc->config & ADS1115_PGA_MASK;
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

void ads1115_read_config(ads1115_adc_t *adc){
    // Default configuration after power up should be 34179.
    // Default config with bit 15 cleared is 1411
    uint8_t dst[2];
    i2c_write_blocking(adc->i2c_port, adc->i2c_addr,
                       &ADS1115_POINTER_CONFIGURATION, 1, true);
    i2c_read_blocking(adc->i2c_port, adc->i2c_addr, &dst, 2,
                      false);
    adc->config = (dst[0] << 8) | dst[1];
}

void ads1115_write_config(ads1115_adc_t *adc) {
    uint8_t src[3];
    src[0] = ADS1115_POINTER_CONFIGURATION;
    src[1] = (uint8_t)(adc->config >> 8);
    src[2] = (uint8_t)(adc->config & 0xff);
    i2c_write_blocking(adc->i2c_port, adc->i2c_addr, &src, 3,
                       false);
}

void ads1115_set_input_mux(enum ads1115_mux_t mux, ads1115_adc_t *adc) {
    adc->config &= ~ADS1115_MUX_MASK;
    adc->config |= mux;
}

void ads1115_set_pga(enum ads1115_pga_t pga, ads1115_adc_t *adc){
    adc->config &= ~ADS1115_PGA_MASK;
    adc->config |= pga;
}

void ads1115_set_operating_mode(enum ads1115_mode_t mode,
                                ads1115_adc_t *adc) {
    adc->config &= ~ADS1115_MODE_MASK;
    adc->config |= mode;
}

void ads1115_set_data_rate(enum ads1115_rate_t rate,
                           ads1115_adc_t *adc) {
    adc->config &= ~ADS1115_RATE_MASK;
    adc->config |= rate;
}