#ifndef DS3231_H
#define DS3231_H

#include <stdint.h>
#include "esp_err.h"
#include "driver/i2c_master.h"

// Adresses des registres DS3231
#define DS3231_REG_SECONDS      0x00
#define DS3231_REG_TEMP_MSB     0x11
#define DS3231_REG_TEMP_LSB     0x12

// Constantes
#define DS3231_TEMPERATURE_PRECISION 0.25f
#define DS3231_I2C_ADDRESS          0x68

// Fonction générique de lecture
esp_err_t ds3231_read_register(
    i2c_master_dev_handle_t dev_handle,
    uint8_t reg_address,
    uint8_t *buffer,
    size_t buffer_size
);

// Fonction spécifique température
esp_err_t ds3231_read_temperature(
    i2c_master_dev_handle_t dev_handle,
    float *temperature
);

#endif // DS3231_H