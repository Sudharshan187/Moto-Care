# data/

This folder contains the sensor data collected during the development, testing, and evaluation of the **Moto Care – Automotive Safety + Emergency Systems** prototype.

The collected data is used to verify the operation of the sensors, observe normal operating conditions, and evaluate the accident-condition detection logic implemented on the ESP32.

## Data Sources

The data in this project can be obtained from the following sensors and system outputs:

| Data Source | Parameters     | Purpose                                  |
| ----------- | -------------- | ---------------------------------------- |
| MPU6050     | Acceleration   | Monitor sudden movement and acceleration |
| MPU6050     | Tilt angle     | Identify excessive vehicle tilt          |
| DHT22       | Temperature    | Monitor environmental temperature        |
| DHT22       | Humidity       | Monitor environmental humidity           |
| ESP32       | System status  | Monitor overall system operation         |
| LED         | ON/OFF status  | Record visual alert condition            |
| Buzzer      | ON/OFF status  | Record audible alert condition           |
| OLED        | Display status | Verify displayed sensor information      |

## Recorded Parameters

The main parameters considered during testing are:

* Acceleration in **m/s²**
* Tilt angle in **degrees**
* Temperature in **°C**
* Humidity in **%**
* Accident alert status
* LED status
* Buzzer status
* Overall system status

## Normal Operating Data

Normal operating data represents sensor readings obtained while the prototype is operating without an accident condition.

Example:

```text
Acceleration : 9.6 m/s2
Tilt         : 8.4 deg
Temperature  : 29.1 C
Humidity     : 63.5 %
LED          : OFF
BUZZER       : OFF
SYSTEM       : RUNNING
```

These values are used to confirm that the sensors and ESP32 are functioning correctly during normal operation.

## Accident-Condition Test Data

Controlled testing can be used to evaluate the accident-detection logic. The system considers a possible accident condition when:

```text
Acceleration > 18.0 m/s2
OR
Tilt > 60°
```

When either condition is satisfied, the system activates the local alert devices.

Example:

```text
Acceleration : 19.4 m/s2
Tilt         : 64.2 deg
Temperature  : 29.4 C
Humidity     : 62.8 %
LED          : ON
BUZZER       : ON
SYSTEM       : RUNNING
```

The above values are examples of the expected output format. Actual experimental readings should be added to the repository after testing.

## Data Collection Method

Sensor readings are collected by the ESP32 during system operation. The MPU6050 communicates with the ESP32 through the I2C interface, while the DHT22 provides temperature and humidity readings through its digital data connection.

The ESP32 processes the readings and sends the results to:

1. OLED display
2. Serial Monitor
3. Local LED alert
4. Local buzzer alert

## Testing Data

Testing data can be organized according to different test conditions:

| Test | Condition                   | Parameters Observed |
| ---- | --------------------------- | ------------------- |
| T01  | System power-on             | System status       |
| T02  | Normal stationary condition | Acceleration, tilt  |
| T03  | Normal movement             | Acceleration, tilt  |
| T04  | Controlled tilt             | Tilt angle          |
| T05  | Temperature measurement     | Temperature         |
| T06  | Humidity measurement        | Humidity            |
| T07  | Accident threshold test     | Acceleration, tilt  |
| T08  | Alert output test           | LED, buzzer         |
| T09  | Complete system test        | All parameters      |

## Data Storage

The current Moto Care prototype does not use a cloud database or remote data-storage system. Sensor readings are observed through the OLED display and Serial Monitor during testing.

Recorded test results can be manually saved as:

```text
.csv
.txt
.xlsx
```

files and placed inside this folder for project documentation.

## Data Privacy and Safety

Only project-related sensor readings should be stored in this folder. Personal information, passwords, API keys, Wi-Fi credentials, or other confidential information should not be uploaded to the repository.

## Future Data Collection

Future versions of Moto Care can support continuous data logging using an SD card, cloud storage, or a mobile application. Larger datasets could also be used for developing more advanced accident-detection algorithms and machine-learning-based sensor analysis.

## Current Project Status

The current prototype uses **real-time sensor readings and threshold-based accident detection**. It does not use a machine-learning model or remote data-collection system. Therefore, this folder is primarily intended for storing and documenting experimental sensor readings and test results.
