# Moto Care — Sensors

## Sensor Components

| Sensor                              | Qty | Purpose                                                     |
| ----------------------------------- | --: | ----------------------------------------------------------- |
| MPU6050 Accelerometer & Gyroscope   |   1 | Measures acceleration, movement, and tilt of the motorcycle |
| DHT22 Temperature & Humidity Sensor |   1 | Measures surrounding temperature and humidity               |

## MPU6050

The MPU6050 is the primary motion sensor used in the Moto Care prototype. It provides accelerometer and gyroscope measurements through the I2C interface.

| Parameter   | Details                          |
| ----------- | -------------------------------- |
| Sensor      | MPU6050                          |
| Quantity    | 1                                |
| Interface   | I2C                              |
| SDA         | GPIO 21                          |
| SCL         | GPIO 22                          |
| Supply      | 3.3 V                            |
| Application | Acceleration and tilt monitoring |

The acceleration magnitude and tilt angle are processed by the ESP32 to identify possible accident conditions.

## DHT22

The DHT22 is used to monitor temperature and humidity in the prototype.

| Parameter   | Details                             |
| ----------- | ----------------------------------- |
| Sensor      | DHT22                               |
| Quantity    | 1                                   |
| Interface   | Digital                             |
| Data Pin    | GPIO 4                              |
| Supply      | 3.3 V                               |
| Application | Temperature and humidity monitoring |

## Sensor Processing

The ESP32 continuously reads data from the MPU6050 and DHT22. The MPU6050 data is used for motion and accident-condition detection, while the DHT22 provides environmental readings.

The sensor values are displayed on the 0.96-inch OLED and are also available through the Serial Monitor.

## Accident Detection Thresholds

| Parameter    |   Threshold |
| ------------ | ----------: |
| Acceleration | > 18.0 m/s² |
| Tilt         |       > 60° |

If either threshold is exceeded, Moto Care activates the LED and buzzer to provide a local alert.
