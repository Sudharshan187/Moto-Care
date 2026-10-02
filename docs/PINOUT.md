# Moto Care — Pinout and Hardware Connections

## 1. Overview

This document describes the GPIO pin configuration and wiring used in the Moto Care automotive safety and monitoring prototype.

The system uses an ESP32 DevKit as the main controller.

## 2. ESP32 Pin Configuration

| Component    | Pin / Signal | ESP32 GPIO |
| ------------ | ------------ | ---------: |
| MPU6050      | SDA          |    GPIO 21 |
| MPU6050      | SCL          |    GPIO 22 |
| DHT22        | DATA         |     GPIO 4 |
| OLED SSD1306 | SDA          |    GPIO 21 |
| OLED SSD1306 | SCL          |    GPIO 22 |
| LED          | Control      |     GPIO 2 |
| Buzzer       | Control      |    GPIO 25 |
| MPU6050      | VCC          |       3.3V |
| OLED         | VCC          |       3.3V |
| DHT22        | VCC          |       3.3V |
| All modules  | GND          |        GND |

## 3. I2C Configuration

The MPU6050 and OLED display share the ESP32 I2C bus.

* **SDA:** GPIO 21
* **SCL:** GPIO 22
* **Supply:** 3.3V
* **Ground:** GND

The MPU6050 is detected at I2C address `0x68` or `0x69`, while the OLED uses address `0x3C`.

## 4. DHT22 Connection

* VCC → 3.3V
* DATA → GPIO 4
* GND → GND

The DHT22 provides temperature and humidity readings.

## 5. Alert Outputs

### LED

* ESP32 GPIO 2 → 220 Ω resistor → LED anode
* LED cathode → GND

### Buzzer

* Buzzer positive → GPIO 25
* Buzzer negative → GND

If a buzzer requires more current than an ESP32 GPIO can safely provide, a suitable transistor driver should be used.

## 6. Accident Detection Thresholds

The prototype uses the following thresholds:

* Acceleration > **18.0 m/s²**
* Tilt > **60°**

If either condition is detected, the system activates the LED and buzzer.

## 7. Important Notes

GPIO 1 (TX0) and GPIO 3 (RX0) are reserved for serial communication and should not be used for external hardware in this prototype.

The system does not currently include GPS, GSM, LTE, or a dedicated remote communication module.
