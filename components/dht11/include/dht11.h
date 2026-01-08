#ifndef DHT11_H
#define DHT11_H

#include <stdint.h>

#include "esp_err.h"
#include "soc/gpio_num.h"

// Structures
typedef struct {
    uint8_t temperature;
    uint8_t humidity;
} dht11_data_t;

// Fonctions
esp_err_t dht11_init(gpio_num_t pin);
esp_err_t dht11_read(dht11_data_t *data);

#endif // DHT11_H