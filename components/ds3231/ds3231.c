#include "ds3231.h"

#include "esp_err.h"
#include "esp_log.h"
#include "driver/i2c_master.h"

static const char *TAG = "DS3231";

esp_err_t ds3231_read_register(
    i2c_master_dev_handle_t dev_handle,
    uint8_t reg_address,
    uint8_t *buffer,
    size_t buffer_size)
{
    if (buffer == NULL || buffer_size == 0) {
        ESP_LOGE(TAG, "Invalid buffer or size");
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t ret = i2c_master_transmit_receive(
        dev_handle,
        &reg_address, 1,          // ✅ Taille explicite
        buffer, buffer_size,       // ✅ Taille passée en paramètre
        -1
    );

    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to read register 0x%02X: %s",
                 reg_address, esp_err_to_name(ret));
    }

    return ret;
}

esp_err_t ds3231_read_temperature(
    i2c_master_dev_handle_t dev_handle,
    float *temperature)
{
    if (temperature == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    uint8_t temp_data[2];
    esp_err_t ret = ds3231_read_register(
        dev_handle,
        DS3231_REG_TEMP_MSB,
        temp_data,
        sizeof(temp_data)
    );

    if (ret != ESP_OK) {
        return ret;
    }

    // Conversion température
    int8_t temp_msb = (int8_t)temp_data[0];
    uint8_t temp_lsb = temp_data[1];
    *temperature = temp_msb + (temp_lsb >> 6) * DS3231_TEMPERATURE_PRECISION;

    return ESP_OK;
}