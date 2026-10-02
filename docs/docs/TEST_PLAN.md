# Moto Care — Test Plan

## 1. Purpose

This document defines the testing procedure for the Moto Care automotive safety and monitoring prototype.

Testing is performed to verify sensor operation, display output, accident detection, and local alert functionality.

## 2. Testing Environment

### Hardware

* ESP32 DevKit V1
* MPU6050
* DHT22
* OLED SSD1306
* LED
* Buzzer
* 220 Ω resistor
* Jumper wires
* USB power supply
* Prototype enclosure

### Software

* Arduino IDE
* Embedded C/C++ Arduino program
* Adafruit MPU6050 library
* Adafruit Sensor library
* DHT library
* Adafruit GFX library
* Adafruit SSD1306 library

## 3. Test Cases

| Test ID | Test Description                       | Expected Result                               |
| ------- | -------------------------------------- | --------------------------------------------- |
| T01     | Power ON the system                    | ESP32 starts successfully                     |
| T02     | Check MPU6050                          | Acceleration and tilt values are displayed    |
| T03     | Check DHT22                            | Temperature and humidity values are displayed |
| T04     | Check OLED                             | Sensor values and system status are displayed |
| T05     | Normal operating condition             | LED and buzzer remain OFF                     |
| T06     | Controlled high-acceleration condition | Accident alert is activated                   |
| T07     | Controlled high-tilt condition         | Accident alert is activated                   |
| T08     | Check LED alert                        | LED turns ON during accident condition        |
| T09     | Check buzzer alert                     | Buzzer turns ON during accident condition     |

## 4. Normal Operation Test

During normal operation, the prototype continuously reads the connected sensors.

The OLED should display:

* Acceleration
* Tilt
* Temperature
* Humidity
* System status

The LED and buzzer should remain OFF when no accident condition is detected.

## 5. Accident Detection Test

The accident detection logic uses two conditions:

```text
Acceleration > 18.0 m/s²
OR
Tilt > 60°
```

When either condition is satisfied, the system should activate the local alert outputs.

Expected outputs:

* LED → ON
* Buzzer → ON
* OLED → Accident alert
* Serial Monitor → Accident alert message

## 6. Safety During Testing

The MPU6050 should not be deliberately hit, thrown, or dropped to simulate an accident.

Testing should be performed using controlled movement and safe tilt conditions.

## 7. Result Verification

For every test case, the following observations can be recorded:

| Parameter      | Observation             |
| -------------- | ----------------------- |
| ESP32 status   | Running / Error         |
| MPU6050        | Detected / Error        |
| DHT22          | Reading / Error         |
| OLED           | Working / Error         |
| LED            | ON / OFF                |
| Buzzer         | ON / OFF                |
| Accident alert | Detected / Not detected |

## 8. Acceptance Criteria

The prototype is considered to operate correctly when:

1. ESP32 starts without errors.
2. MPU6050 provides acceleration and tilt readings.
3. DHT22 provides temperature and humidity readings.
4. OLED displays sensor information.
5. LED operates as an alert indicator.
6. Buzzer operates as an audible alert.
7. Accident conditions trigger the local alert system.
8. Normal conditions do not unnecessarily trigger the alert.

## 9. Testing Limitation

The current prototype is a local embedded monitoring system. It does not test remote communication, GPS tracking, GSM/LTE messaging, or cloud-based emergency notification because those modules are not included in the current implementation.
