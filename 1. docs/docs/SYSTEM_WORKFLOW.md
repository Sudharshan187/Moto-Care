# Moto Care — System Workflow

## 1. System Overview

Moto Care is an ESP32-based automotive safety and monitoring prototype designed to monitor motion, tilt, temperature, and humidity.

The system provides local accident alerts using an LED and buzzer and displays sensor information on an OLED display.

## 2. System Workflow

```text
             POWER ON
                |
                v
        ESP32 INITIALIZATION
                |
        +-------+-------+
        |               |
        v               v
   Initialize       Initialize
    MPU6050           DHT22
        |               |
        +-------+-------+
                |
                v
        Read Sensor Data
                |
       +--------+--------+
       |                 |
       v                 v
   MPU6050             DHT22
 Acceleration          Temperature
    & Tilt             & Humidity
       |                 |
       +--------+--------+
                |
                v
       ESP32 Data Processing
                |
                v
       Accident Condition Check
                |
        +-------+-------+
        |               |
       NO              YES
        |               |
        v               v
  Normal Status     LED ON
                    Buzzer ON
        |               |
        +-------+-------+
                |
                v
          OLED Display
                |
                v
          Repeat Cycle
```

## 3. Processing Sequence

### Step 1 — Power Supply

The ESP32 and connected sensors receive power from the USB/5V power source.

### Step 2 — Initialization

The ESP32 initializes:

* MPU6050
* DHT22
* OLED display
* LED
* Buzzer
* I2C communication

### Step 3 — Sensor Data Collection

The MPU6050 provides:

* X-axis acceleration
* Y-axis acceleration
* Z-axis acceleration
* Tilt information

The DHT22 provides:

* Temperature
* Humidity

### Step 4 — Data Processing

The ESP32 calculates the overall acceleration magnitude and tilt angle from the MPU6050 measurements.

### Step 5 — Accident Detection

The controller checks the measured values against the predefined thresholds.

```text
Acceleration > 18.0 m/s²
              OR
Tilt > 60°
              |
              v
       Accident Alert
```

### Step 6 — Local Alert

When an accident condition is detected:

* LED turns ON
* Buzzer turns ON
* OLED displays an accident alert
* Serial monitor reports the alert

### Step 7 — Normal Operation

When the readings remain within the defined limits:

* LED remains OFF
* Buzzer remains OFF
* OLED displays normal sensor readings
* System continues monitoring

## 4. Continuous Monitoring

After completing one monitoring cycle, the ESP32 waits for approximately one second and repeats the process.

This creates continuous local monitoring of the prototype.

## 5. Current System Boundary

The current prototype provides local monitoring and alerting only.

GPS tracking, GSM/LTE communication, cloud connectivity, and remote emergency notification are not part of the current hardware implementation and can be considered future enhancements.
