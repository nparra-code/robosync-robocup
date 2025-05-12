/**
 * \file        vl6180x_lib.h
 * \brief       VL6180 library
 * \details     VL6180 library for ESP32-S3
 * 
 * \author      Nelson Parra
 * \version     0.1.0
 * \date        22/04/2025
 * \copyright   Unlicensed
 */

#ifndef __VL6180X_LIB_H__
#define __VL6180X_LIB_H__


#include "platform_esp32s3.h"

#include "vl6180x_api.h"

#include "sdkconfig.h"
#include "freertos/task.h"

#define VL6180X_I2C_ADDR 0x29
#define I2C_FREQUENCY 400000 ///< I2C frequency in Hz

typedef struct
{
    uint8_t addr;        ///< I2C address of the VL6180x sensor. Default is 0x29 using VL6180X_I2C_ADDR. If not, spy address using an I2C scanner.
    uint8_t irq;         ///< GPIO pin connected to the IRQ pin of the VL6180x sensor

    // Peripheral handles
    i2c_t i2c_handle;   ///< I2C handle for the VL6180x sensor
    gpio_t gpio_handle; ///< GPIO handle for the IRQ pin
    
} VL6180x_t;

/**
 * @brief Initialize the I2C master driver
 * 
 * @param vl6180x_i2c Pointer to the VL6180x structure
 * @param port I2C port number
 * @param scl GPIO pin number for SCL
 * @param sda GPIO pin number for SDA
 */
void VL6180x_Init(VL6180x_t *vl6180x_i2c, i2c_port_t port, uint8_t scl, uint8_t sda);

/**
 * @brief Deinitialize the I2C master driver
 * 
 * @param vl6180x_i2c Pointer to the VL6180x structure
 */
void VL6180x_Deinit(VL6180x_t *vl6180x_i2c);

/**
 * @brief Get the range from the VL6180x sensor
 * 
 * @param vl6180x_i2c Pointer to the VL6180x structure
 * @return int32_t Range in mm
 */
int32_t VL6180x_GetRange(VL6180x_t *vl6180x_i2c);

#endif /* __VL6180X_LIB_H__ */