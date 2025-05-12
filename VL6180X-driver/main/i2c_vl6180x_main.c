/*
 * SPDX-FileCopyrightText: 2023 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: Unlicense OR CC0-1.0
 */

#include "vl6180x_lib.h"

#define I2C_SCL 15
#define I2C_SDA 16

void app_main(void)
{

    // Initialize the VL6180x sensor
    VL6180x_t vl6180x_dev;
    vl6180x_dev.addr = VL6180X_I2C_ADDR; // Default I2C address
    vl6180x_dev.irq = 0; // No IRQ pin used

    // Initialize the I2C driver
    VL6180x_Init(&vl6180x_dev, I2C_NUM_1, I2C_SCL, I2C_SDA);

    while (1) {
        ESP_LOGI("VL6180x", "Range: %ld mm", VL6180x_GetRange(&vl6180x_dev));
    }
}
