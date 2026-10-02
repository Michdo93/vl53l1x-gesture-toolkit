# Hardware Wiring Guide

This project requires zero external components (no resistors, transistors, or complex shields required).

## Pinout Mapping

| VL53L1X Sensor | ESP32 GPIO | ESP32-C3 GPIO | Arduino Nano / Uno | Description |
| :--- | :--- | :--- | :--- | :--- |
| **VIN / VCC** | `3.3V` / `5V` | `3.3V` / `5V` | `5V` or `3.3V` | Main Power Supply |
| **GND** | `GND` | `GND` | `GND` | Ground |
| **SDA** | `GPIO 21` | `GPIO 8` | `A4` | I2C Data Line |
| **SCL** | `GPIO 22` | `GPIO 9` | `A5` | I2C Clock Line |

> **Note:** Ensure your VL53L1X breakout board features on-board pull-up resistors and a voltage regulator (standard on Adafruit, SparkFun, and Pololu breakout modules).
