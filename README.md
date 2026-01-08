# I2C DS3231 Demo

ESP-IDF project demonstrating I2C communication with the DS3231 Real-Time Clock (RTC) module, reading temperature data from the sensor.

## Description

This project reads temperature data from a DS3231 RTC module using I2C communication on an ESP32. The DS3231 includes an integrated temperature sensor that is read every 2 seconds and logged to the console.

## Hardware Requirements

- ESP32 development board
- DS3231 RTC module
- Connecting wires

## Pin Configuration

| Signal | GPIO Pin |
|--------|----------|
| SDA    | GPIO 6   |
| SCL    | GPIO 7   |

The internal pull-up resistors are enabled in the configuration.

## Software Requirements

- ESP-IDF v5.0 or later
- CMake 3.16 or later

## Building the Project

1. Set up the ESP-IDF environment:
```bash
. $HOME/esp/esp-idf/export.sh
```

2. Navigate to the project directory:
```bash
cd i2c_ds3231_demo
```

3. Configure the project (optional):
```bash
idf.py menuconfig
```

4. Build the project:
```bash
idf.py build
```

## Flashing and Running

1. Connect your ESP32 board to your computer

2. Flash the firmware:
```bash
idf.py -p /dev/ttyUSB0 flash
```
Replace `/dev/ttyUSB0` with your actual serial port.

3. Monitor the output:
```bash
idf.py -p /dev/ttyUSB0 monitor
```

To exit the monitor, press `Ctrl+]`.

## Output

The program logs temperature readings every 2 seconds:
```
I (1234) I2C_DEMO: Temp1: 24
I (1234) I2C_DEMO: Temp2: 128
```

The temperature is stored in two bytes:
- `Temp1`: Integer part of the temperature in Celsius
- `Temp2`: Fractional part (bit 7-6 represent 0.25°C increments)

## Hardware Connections

Connect the DS3231 module to your ESP32:
- DS3231 VCC → ESP32 3.3V
- DS3231 GND → ESP32 GND
- DS3231 SDA → ESP32 GPIO 6
- DS3231 SCL → ESP32 GPIO 7

## Configuration

Key I2C parameters in `main.c`:
- I2C Port: 0
- DS3231 Address: 0x68 (7-bit)
- SCL Speed: 100 kHz
- Temperature Register: 0x11

## License

This project is provided as-is for educational and demonstration purposes.
