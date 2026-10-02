# Moto Care — Hardware Components

## 1. Overview

The Moto Care system is an ESP32-based automotive safety and monitoring prototype. The hardware consists of an ESP32 development board, motion sensor, temperature and humidity sensor, OLED display, LED indicator, buzzer, resistor, jumper wires, and a compact prototype enclosure.

The ESP32 acts as the main controller and processes the sensor data to identify possible accident conditions and provide local alerts.

## 2. Hardware Components

| Component                           |    Quantity | Purpose                                                       |
| ----------------------------------- | ----------: | ------------------------------------------------------------- |
| ESP32 DevKit V1                     |           1 | Main microcontroller for sensor processing and system control |
| MPU6050 Accelerometer & Gyroscope   |           1 | Measures acceleration, movement, and tilt                     |
| DHT22 Temperature & Humidity Sensor |           1 | Measures temperature and humidity                             |
| 0.96" OLED SSD1306                  |           1 | Displays sensor readings and system status                    |
| LED                                 |           1 | Provides visual alert during an accident condition            |
| Active Buzzer                       |           1 | Provides audible alert during an accident condition           |
| 220 Ω Resistor                      |           1 | Limits current through the LED                                |
| Breadboard / Prototype Enclosure    |           1 | Used for circuit assembly and physical prototype construction |
| Jumper Wires                        | As required | Provides electrical connections between components            |
| USB Power Supply                    |           1 | Provides power to the ESP32 and connected components          |

## 3. ESP32 Development Board

The ESP32 DevKit V1 is the central controller of the Moto Care system.

### Main functions

* Reads data from the MPU6050.
* Reads temperature and humidity from the DHT22.
* Processes sensor values.
* Calculates acceleration magnitude and tilt.
* Checks accident detection thresholds.
* Controls the OLED display.
* Controls the LED and buzzer alerts.
* Sends system information to the Serial Monitor.

## 4. MPU6050

The MPU6050 is a combined accelerometer and gyroscope module connected to the ESP32 using the I2C communication interface.

### Functions

* Measures acceleration along X, Y, and Z axes.
* Provides gyroscope measurements.
* Helps determine the tilt of the prototype.
* Provides motion information for accident-condition detection.

### Connection

| MPU6050 Pin | ESP32   |
| ----------- | ------- |
| VCC         | 3.3V    |
| GND         | GND     |
| SDA         | GPIO 21 |
| SCL         | GPIO 22 |

## 5. DHT22 Sensor

The DHT22 is used to measure environmental temperature and humidity.

### Connection

| DHT22 Pin/Signal | ESP32  |
| ---------------- | ------ |
| VCC              | 3.3V   |
| DATA             | GPIO 4 |
| GND              | GND    |

The sensor readings are displayed on the OLED and reported through the Serial Monitor.

## 6. OLED Display

The 0.96-inch SSD1306 OLED display provides a local visual interface for the system.

It displays:

* Acceleration
* Tilt
* Temperature
* Humidity
* System status
* Accident alert status

### Connection

| OLED Pin | ESP32   |
| -------- | ------- |
| VCC      | 3.3V    |
| GND      | GND     |
| SDA      | GPIO 21 |
| SCL      | GPIO 22 |

The OLED uses the I2C address `0x3C` in the current implementation.

## 7. LED Alert

An LED is used as a visual warning indicator.

### Connection

```text
ESP32 GPIO 2
      |
    220 Ω
      |
     LED
      |
     GND
```

When an accident condition is detected, the ESP32 turns the LED ON.

## 8. Buzzer Alert

The buzzer provides an audible local warning.

### Connection

* Positive → GPIO 25
* Negative → GND

When an accident condition is detected, the ESP32 activates the buzzer.

If a buzzer requires more current than an ESP32 GPIO can safely provide, a suitable transistor driver circuit should be used.

## 9. Accident Detection Configuration

The current prototype uses two threshold conditions.

```text
Acceleration > 18.0 m/s²
OR
Tilt > 60°
```

If either condition is satisfied:

```text
LED    → ON
Buzzer → ON
OLED   → Accident Alert
```

Otherwise, the system remains in normal monitoring mode.

## 10. Complete Pin Configuration

| Component | Signal  | ESP32 GPIO |
| --------- | ------- | ---------: |
| MPU6050   | SDA     |    GPIO 21 |
| MPU6050   | SCL     |    GPIO 22 |
| DHT22     | DATA    |     GPIO 4 |
| OLED      | SDA     |    GPIO 21 |
| OLED      | SCL     |    GPIO 22 |
| LED       | Control |     GPIO 2 |
| Buzzer    | Control |    GPIO 25 |

## 11. Power Configuration

The ESP32 is powered through USB.

The connected sensors and display operate from the ESP32's 3.3V supply in the current prototype.

All components share a common ground.

## 12. Physical Prototype

The components are assembled and integrated inside a compact prototype enclosure.

The enclosure provides:

* Protection for the electronic components.
* Compact physical integration.
* Easy access to the ESP32 USB connection.
* A practical demonstration model for the Moto Care system.

## 13. Hardware Limitations

The current prototype does not contain:

* GPS module
* Fuel-level sensor
* GSM/LTE communication module
* Dedicated remote emergency communication
* Camera
* TPMS

These features can be considered for future versions of the Moto Care system.

## 14. Hardware Summary

The combination of the ESP32, MPU6050, DHT22, OLED, LED, and buzzer provides the core hardware required for the Moto Care prototype.

The system collects sensor information, processes the readings using the ESP32, displays important information locally, and generates visual and audible alerts when a possible accident condition is detected.
