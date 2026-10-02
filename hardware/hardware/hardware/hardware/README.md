# Moto Care — Hardware Components

## Hardware Components

| Component | Qty | Purpose |
|---|---:|---|
| ESP32 DevKit V1 | 1 | Main microcontroller for sensor processing and system control |
| MPU6050 Accelerometer & Gyroscope | 1 | Measures acceleration, movement, and tilt for possible accident detection |
| DHT22 Temperature & Humidity Sensor | 1 | Measures temperature and humidity |
| 0.96" OLED (SSD1306) | 1 | Displays sensor readings and system status |
| LED | 1 | Provides visual alert during an accident condition |
| Active Buzzer | 1 | Provides audible alert during an accident condition |
| 220 Ω Resistor | 1 | Limits current through the LED |
| Breadboard / Prototype Enclosure | 1 | Used for circuit assembly and physical prototype construction |
| Jumper Wires | As required | Provides electrical connections between components |
| USB Power Supply | 1 | Provides power to the ESP32 and connected components |

## Sensor Configuration

| Sensor | ESP32 Connection | Function |
|---|---|---|
| MPU6050 SDA | GPIO 21 | I2C data communication |
| MPU6050 SCL | GPIO 22 | I2C clock communication |
| DHT22 DATA | GPIO 4 | Temperature and humidity data |
| OLED SDA | GPIO 21 | I2C data communication |
| OLED SCL | GPIO 22 | I2C clock communication |
| LED | GPIO 2 | Visual alert output |
| Buzzer | GPIO 25 | Audible alert output |

## Accident Detection

The Moto Care prototype uses the MPU6050 to monitor acceleration and tilt.

- Acceleration threshold: **18.0 m/s²**
- Tilt threshold: **60°**

When either threshold is exceeded, the LED and buzzer are activated and the OLED displays the alert status.

## Power Supply

The prototype is powered through the ESP32 USB power connection. The MPU6050, OLED, and DHT22 are supplied from the ESP32 3.3 V output, with a common ground connection.

## Hardware Notes

The current prototype does not include GPS, GSM/LTE, fuel sensing, or a dedicated communication module. These are future enhancements.
