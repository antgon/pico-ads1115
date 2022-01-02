/*
 * Copyright (c) 2021-2022 Antonio González
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _REGISTERS_H_
#define _REGISTERS_H_

/* i2c_write does not work if I pass the register address as a #define. It only works if the address is a const uint8_t and it is passed as a pointer (&)*/
static const uint8_t ADS1115_POINTER_CONVERSION = 0x00;
static const uint8_t ADS1115_POINTER_CONFIGURATION = 0x01;
static const uint8_t ADS1115_POINTER_LO_THRESH = 0x02;
static const uint8_t ADS1115_POINTER_HI_THRESH = 0x03;

// Operational status; bit 15
static const uint16_t ADS1115_STATUS_MASK = 0x8000;
enum ads1115_status_t {
    ADS1115_STATUS_START = 0x01,
    ADS1115_STATUS_BUSY = 0x00
};

// Input multiplexer configuration; bits 14-12
static const uint16_t ADS1115_MUX_MASK = 0x7000;
enum ads1115_mux_t {
    ADS1115_MUX_DIFF_0_1 = 0x0000, // default
    ADS1115_MUX_DIFF_0_3 = 0x1000,
    ADS1115_MUX_DIFF_1_3 = 0x2000,
    ADS1115_MUX_DIFF_2_3 = 0x3000,
    ADS1115_MUX_SINGLE_0 = 0x4000,
    ADS1115_MUX_SINGLE_1 = 0x5000,
    ADS1115_MUX_SINGLE_2 = 0x6000,
    ADS1115_MUX_SINGLE_3 = 0x7000
};

// Programmable gain amplifier; bits 11-9
// Full-scale range (FSR) options are ±6.144V, ±4.096V, ±2.048V,
// ±1.024V, ±0.512V, ±0.256V.
static const uint16_t ADS1115_PGA_MASK = 0x0E00;
enum ads1115_pga_t {
    ADS1115_PGA_6_144 = 0x0000,
    ADS1115_PGA_4_096 = 0x0200,
    ADS1115_PGA_2_048 = 0x0400, // default
    ADS1115_PGA_1_024 = 0x0600,
    ADS1115_PGA_0_512 = 0x0800,
    ADS1115_PGA_0_256 = 0x0A00
};

// Operating mode; bit 8
static const uint16_t ADS1115_MODE_MASK = 0x0100;
enum ads1115_mode_t {
    ADS1115_MODE_CONTINUOUS = 0x0000,
    ADS1115_MODE_SINGLE_SHOT = 0x0100 // default
};

// Data rate; configuration register bits 7-5.
static const uint16_t ADS1115_RATE_MASK = 0x00E0;
enum ads1115_rate_t {
    ADS1115_RATE_8_SPS = 0x0000,
    ADS1115_RATE_16_SPS = 0x0020,
    ADS1115_RATE_32_SPS = 0x0040,
    ADS1115_RATE_64_SPS = 0x0060,
    ADS1115_RATE_128_SPS = 0x0080, ///< default
    ADS1115_RATE_250_SPS = 0x00A0,
    ADS1115_RATE_475_SPS = 0x00C0,
    ADS1115_RATE_860_SPS = 0x00E0
};

// Comparator mode, bit 4
static const uint16_t ADS1115_COMP_MODE_MASK = 0x0010;
enum ads1115_comp_mode_t {
    ADS1115_COMPARATOR_TRADITIONAL = 0x0000, // default
    ADS1115_COMPARATOR_WINDOW = 0x0010
};

// Comparator polarity, bit 3
static const uint16_t ADS1115_COMP_POL_MASK = 0x0008;
enum ads1115_comp_pol_t {
    ADS1115_COMPARATOR_POLARITY_LO = 0x0000, // default
    ADS1115_COMPARATOR_POLARITY_HI = 0x0008
};

// Latching comparator, bit 2
static const uint16_t ADS1115_COMP_LAT_MASK = 0x0004;
enum ads1115_comp_lat_t {
    ADS1115_COMPARATOR_NONLATCHING = 0x0000, // default
    ADS1115_COMPARATOR_LATCHING = 0x0004
};

// Comparator queue and disable, bits 1-0
static const uint16_t ADS1115_COMP_QUE_MASK = 0x0003;
enum ads1115_comp_que_t {
    ADS1115_COMPARATOR_QUE_1 = 0x0000,
    ADS1115_COMPARATOR_QUE_2 = 0x0001,
    ADS1115_COMPARATOR_QUE_4 = 0x0002,
    ADS1115_COMPARATOR_QUE_DISABLE = 0x0003 // default
};

#endif