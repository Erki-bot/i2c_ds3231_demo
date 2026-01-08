#include "dht11.h"

#include "esp_err.h"
#include "esp_log.h"
#include "soc/gpio_num.h"

static const char* TAG = "DHT11";

esp_err_t dht11_init(gpio_num_t pin)
{
    ESP_LOGI(TAG, "DHT11 Initialized on GPIO%d", pin);
    return ESP_OK;
}

esp_err_t dht11_read(dht11_data_t* data)
{
    esp_err_t err = ESP_OK;
    data->temperature = 23;
    data->humidity = 98;

    return err;
}
