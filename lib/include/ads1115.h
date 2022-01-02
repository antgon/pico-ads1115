/*
 * Copyright (c) 2021-2022 Antonio González
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _ADS1115_H_
#define _ADS1115_H_

// #include <stdio.h>
#include "pico/stdlib.h"
// #include "pico.h"
#include "hardware/i2c.h"
#include "registers.h"

#ifndef ADS1115_I2C_PORT
#define ADS1115_I2C_PORT i2c_default
#endif

#ifndef ADS1115_I2C_ADDR
#define ADS1115_I2C_ADDR 0x48
#endif

/*! \brief Initialise the ADS115 device
 */
void ads1115_init(uint8_t sda_pin, uint8_t scl_pin, uint16_t *config);

/*! \brief Read the last converted value
 */
void ads1115_read_adc(uint16_t *config, uint16_t *adc_value);

/*! \brief Read the 16-bit configuration register
 *
 * After powering up, the default configuration value 
 * is 34179 (1411 after bit 15 has been cleared).
 */
void ads1115_read_config(uint16_t *config);

/*! \brief Write to the configuration register
 */
void ads1115_write_config(uint16_t config);

/*! \brief Convert a (raw) ADC value to voltage
 *
 * Converted values are 16-bit two's complement
 */
float ads1115_raw_to_volts(uint16_t *config, uint16_t adc_value);

/*! \brief Configure the programmable gain amplifier (PGA)
 *
 * Configures the PGA to achieve different full-scale voltage ranges.
 * Be aware that, whatever this setting, the absolute voltage of any
 * analog input should never be greater than VDD + 0.3 V.
 * 
 * The available full-scale ranges (FSR) are ±6.144 V, ±4.096 V 
 * (default), ±2.048 V, ±1.024 V, ±0.512 V, and ±0.256 V.
 */
void ads1115_set_pga(uint16_t *config, enum ads1115_pga_t pga);

/*! \brief Set the operating mode
 * 
 * The operating mode of the device can be continuous conversion or
 * single-shot.
 */
void ads1115_set_operating_mode(uint16_t *config,
                                enum ads1115_mode_t mode);

/*! \brief Set the data rate
 * 
 * Available data rates are 8, 16, 32, 64, 128 (default), 250, 475,
 * and 860 SPS.
 */
void ads1115_set_data_rate(uint16_t *config, enum ads1115_rate_t rate);

/* \brief Configure the input multiplexer
 * 
 * The input can be single-ended or differential. The options for 
 * differential signals are (AIN_P, AIN_N): (0, 1), (0, 3), (1, 3),
 * and (2, 3).
 */
void ads1115_set_input_mux(uint16_t *config, enum ads1115_mux_t mux);

// void set_comparator_mode();
// void set_comparator_polarity();
// void set_comparator_latching();
// void set_comparator_queue();

#endif
