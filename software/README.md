# Moto Care — Software

## Software Implementation

The Moto Care prototype is programmed using Arduino C/C++ in the Arduino IDE. The ESP32 acts as the main controller and performs sensor data acquisition, processing, accident-condition detection, display control, and local alert generation.

## Development Environment

| Software            | Purpose                                       |
| ------------------- | --------------------------------------------- |
| Arduino IDE         | Writing, compiling, and uploading the program |
| ESP32 Board Package | ESP32 board support                           |
| Arduino C/C++       | Embedded system programming                   |
| Serial Monitor      | Monitoring sensor readings and system status  |

## Libraries Used

| Library          | Purpose                               |
| ---------------- | ------------------------------------- |
| Wire             | I2C communication                     |
| Adafruit MPU6050 | MPU6050 sensor communication          |
| Adafruit Sensor  | Common sensor interface               |
| DHT              | DHT22 temperature and humidity sensor |
| Adafruit GFX     | Graphics and text support             |
| Adafruit SSD1306 | OLED display control                  |
| math.h           | Mathematical calculations             |

## Program Operation

The software follows the sequence below:

1. Initialize the ESP32 GPIO pins and I2C interface.
2. Initialize the OLED display.
3. Initialize the DHT22 sensor.
4. Detect and initialize the MPU6050 sensor.
5. Read acceleration and tilt values from the MPU6050.
6. Read temperature and humidity from the DHT22.
7. Calculate the acceleration magnitude and tilt angle.
8. Compare the sensor values with the accident-detection thresholds.
9. Activate the LED and buzzer when a possible accident condition is detected.
10. Display sensor readings and system status on the OLED.
11. Print sensor readings and status information to the Serial Monitor.
12. Repeat the monitoring process continuously.

## Accident Detection Logic

The prototype uses threshold-based detection.

* Acceleration threshold: **18.0 m/s²**
* Tilt threshold: **60°**

If the acceleration exceeds 18.0 m/s² or the tilt exceeds 60°, the system generates a local accident alert.

## Output

The software provides the following outputs:

* Acceleration reading
* Tilt angle
* Temperature
* Humidity
* OLED system status
* LED visual alert
* Buzzer audible alert
* Serial Monitor readings

## Current Implementation

The current software operates locally on the ESP32. GPS tracking, GSM/LTE communication, cloud connectivity, and mobile-app communication are not implemented in the present prototype and may be considered for future development.
