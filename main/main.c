#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"
#include "ds3231.h"

static const char *TAG = "MAIN";

// Configuration I2C
static const i2c_port_num_t I2C_PORT = 0;
static const gpio_num_t SDA_PIN = GPIO_NUM_6;
static const gpio_num_t SCL_PIN = GPIO_NUM_7;

i2c_master_bus_handle_t bus_handle;

void ds3231_task(void *args)
{
    // Configuration device DS3231
    i2c_device_config_t dev_config = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = DS3231_I2C_ADDRESS,
        .scl_speed_hz = 100000,
    };

    i2c_master_dev_handle_t ds3231_dev;
    ESP_ERROR_CHECK(i2c_master_bus_add_device(bus_handle, &dev_config, &ds3231_dev));

    ESP_LOGI(TAG, "DS3231 initialized successfully");

    // Boucle de lecture
    while (1)
    {
        float temperature;
        esp_err_t ret = ds3231_read_temperature(ds3231_dev, &temperature);

        if (ret == ESP_OK) {
            ESP_LOGI(TAG, "Temperature: %.2f°C", temperature);
        } else {
            ESP_LOGE(TAG, "Failed to read temperature");
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main(void)
{
    // Configuration bus I2C
    i2c_master_bus_config_t bus_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_PORT,
        .scl_io_num = SCL_PIN,
        .sda_io_num = SDA_PIN,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    ESP_ERROR_CHECK(i2c_new_master_bus(&bus_config, &bus_handle));

    vTaskDelay(2000/portTICK_PERIOD_MS);

    xTaskCreate(ds3231_task, "DS3231 Task", 2048, NULL, 5, NULL);
}