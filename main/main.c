#include <stdio.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "driver/i2c_master.h"
#include "freertos/task.h"

#define DATA_LENGTH 2

// Functions definition

static const i2c_port_num_t i2c_port = 0;
static gpio_num_t sda_pin = GPIO_NUM_6;
static gpio_num_t scl_pin = GPIO_NUM_7;
static uint16_t ds3231_address = 0b1101000;
static uint8_t temperature_reg_address[1] = {0x11};

static const char *TAG = "I2C_DEMO";


void app_main()
{
    i2c_master_bus_config_t i2c_mst_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = i2c_port,
        .scl_io_num = scl_pin,
        .sda_io_num = sda_pin,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };

    i2c_master_bus_handle_t bus_handle;

    esp_err_t esp_err = i2c_new_master_bus(&i2c_mst_config, &bus_handle);

    if (esp_err != ESP_OK)
    {
        ESP_LOGE(TAG, "failed to initiate the i2c bus");
        abort();
    }

    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = ds3231_address,
        .scl_speed_hz = 100000,
    };

    i2c_master_dev_handle_t dev_handle;

    esp_err = i2c_master_bus_add_device(bus_handle, &dev_cfg, &dev_handle);

    if (esp_err != ESP_OK)
    {
        ESP_LOGE(TAG, "failed to attach device to the i2c bus");
        abort();
    }

    uint8_t data_rd[2];

   while (1)
   {
       vTaskDelay(2000/portTICK_PERIOD_MS);
       // i2c_master_receive(dev_handle, data_rd, DATA_LENGTH, -1);

       i2c_master_transmit_receive(
           dev_handle,
           temperature_reg_address, sizeof(temperature_reg_address),
           data_rd, sizeof(data_rd),
           -1);
       ESP_LOGI(TAG, "Temp1: %d", data_rd[0]);
       ESP_LOGI(TAG, "Temp2: %d", data_rd[1]);

   }


}

