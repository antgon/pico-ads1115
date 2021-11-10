/*
 * Copyright (c) 2021 Antonio González
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _ADS1115_H_
#define _ADS1115_H_

#include "pico.h"
#include "hardware/i2c.h"

/** \file ads1115.h
 * \brief Library for using an ADS1115 analog-to-digital converter
 * with the Raspberry Pi Pico
 *
*/

#ifndef I2C_PORT
#define I2C_PORT i2c0
#endif

#ifndef ADS1115_ADDR
#define ADS1115_ADDR 0x48
#endif

#ifndef ADS1115_I2C_FREQ
#define ADS1115_I2C_FREQ 100000
#endif

/*! \brief ADS115 register map
 */
enum ads1115_register {    
   
};

/*! \brief 
 *
 */
void ads1115_init(void);

/*! \brief Write a value to the specified register
 *
 * \param reg The register address
 * \param val The value to write
 */
static void ads1115_write(enum ads1115_register reg, uint8_t val) {
    uint8_t buf[] = {reg, val};
    i2c_write_blocking(I2C_PORT, ADS1115_ADDR, buf, 2, false);
}

/*! \brief Read a byte from the specified register
 *
 * \param reg The register address
 * \param buf The buffer to read into
 */
static void ads1115_read(enum ads1115_register reg, uint8_t *buf) {
    i2c_write_blocking(I2C_PORT, ADS1115_ADDR, &reg, 1, true);
    i2c_read_blocking(I2C_PORT, ADS1115_ADDR, buf, 1, false);
}

#endif
