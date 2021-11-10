/*
 * Copyright (c) 2021 Antonio González
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

/* MPR121 hello_mpr121 example.

Whenever a sensor (electrode) is touched, the on-board LED lights on and the sensor number is printed.
*/

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"

// I2C definitions: port and pin numbers
#define I2C_PORT i2c0
#define I2C_SDA 8
#define I2C_SCL 9


// Include the ADS1115 library only after the definitions above.
#include "ads1115.h"

int main()
{
    stdio_init_all();

    // Initialise I2C.
    i2c_init(I2C_PORT, ADS1115_I2C_FREQ);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Initialise the ADC.
    ads1115_init();

    // Initialise data variables.
    
    while (1)
    {
        // Pause for these many ms.
        sleep_ms(200);
    }

    return 0;
}
