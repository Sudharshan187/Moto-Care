#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <math.h>

// =====================================================
// PIN CONFIGURATION
// =====================================================

#define SDA_PIN 21
#define SCL_PIN 22

#define DHT_PIN 4
#define DHT_TYPE DHT22

#define LED_PIN 2
#define BUZZER_PIN 25

// =====================================================
// OLED CONFIGURATION
// =====================================================

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  OLED_RESET
);

// =====================================================
// SENSOR OBJECTS
// =====================================================

Adafruit_MPU6050 mpu;
DHT dht(DHT_PIN, DHT_TYPE);

// =====================================================
// SENSOR STATUS
// =====================================================

bool oledOK = false;
bool mpuOK = false;

// =====================================================
// ACCIDENT SETTINGS
// =====================================================

const float IMPACT_THRESHOLD = 18.0;
const float TILT_THRESHOLD = 50.0;

// =====================================================
// BUZZER SETTINGS
// =====================================================

// Buzzer every 30 seconds
const unsigned long BUZZER_INTERVAL = 30000;

// Normal buzzer sound duration
const unsigned long BUZZER_DURATION = 1000;

// Accident alarm duration
const unsigned long ACCIDENT_DURATION = 10000;

// =====================================================
// TIMERS
// =====================================================

unsigned long lastDisplay = 0;
unsigned long lastBuzzer = 0;
unsigned long buzzerStart = 0;
unsigned long accidentStart = 0;

// =====================================================
// STATES
// =====================================================

bool buzzerActive = false;
bool accidentDetected = false;

// =====================================================
// I2C SCANNER
// =====================================================

void scanI2C()
{
  Serial.println();
  Serial.println("I2C SCANNER");
  Serial.println("----------------");

  int devices = 0;

  for (byte address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);

    byte error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at 0x");

      if (address < 16)
      {
        Serial.print("0");
      }

      Serial.println(address, HEX);

      devices++;
    }
  }

  if (devices == 0)
  {
    Serial.println("NO I2C DEVICES FOUND!");
  }
  else
  {
    Serial.print("Total I2C devices: ");
    Serial.println(devices);
  }

  Serial.println("----------------");
}

// =====================================================
// OLED INITIALIZATION
// =====================================================

void startOLED()
{
  if (display.begin(
        SSD1306_SWITCHCAPVCC,
        OLED_ADDRESS))
  {
    oledOK = true;

    Serial.println("OLED FOUND!");

    display.clearDisplay();

    display.setTextColor(SSD1306_WHITE);

    display.setTextSize(2);

    display.setCursor(15, 5);
    display.println("MOTO");

    display.setCursor(15, 32);
    display.println("SHIELD");

    display.display();

    delay(2000);
  }
  else
  {
    Serial.println("OLED NOT FOUND!");
  }
}

// =====================================================
// MPU6050 INITIALIZATION
// =====================================================

void startMPU()
{
  Serial.println();
  Serial.println("Testing MPU6050...");

  // Try 0x68
  if (mpu.begin(0x68, &Wire))
  {
    mpuOK = true;

    Serial.println("MPU6050 FOUND at 0x68");
  }

  // Try 0x69
  else if (mpu.begin(0x69, &Wire))
  {
    mpuOK = true;

    Serial.println("MPU6050 FOUND at 0x69");
  }

  else
  {
    mpuOK = false;

    Serial.println("MPU6050 NOT FOUND!");
  }

  if (mpuOK)
  {
    mpu.setAccelerometerRange(
      MPU6050_RANGE_8_G
    );

    mpu.setGyroRange(
      MPU6050_RANGE_500_DEG
    );

    mpu.setFilterBandwidth(
      MPU6050_BAND_21_HZ
    );

    Serial.println("MPU6050 CONFIGURED");
  }
}

// =====================================================
// SETUP
// =====================================================

void setup()
{
  Serial.begin(115200);

  delay(1000);

  Serial.println();
  Serial.println("================================");
  Serial.println("       MOTOSHIELD SYSTEM");
  Serial.println("================================");

  // ---------------------------------------------------
  // GPIO
  // ---------------------------------------------------

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  digitalWrite(LED_PIN, HIGH);
  digitalWrite(BUZZER_PIN, LOW);

  // ---------------------------------------------------
  // I2C
  // ---------------------------------------------------

  Wire.begin(
    SDA_PIN,
    SCL_PIN
  );

  delay(500);

  // ---------------------------------------------------
  // SCAN I2C
  // ---------------------------------------------------

  scanI2C();

  // ---------------------------------------------------
  // OLED
  // ---------------------------------------------------

  startOLED();

  // ---------------------------------------------------
  // MPU6050
  // ---------------------------------------------------

  startMPU();

  // ---------------------------------------------------
  // DHT22
  // ---------------------------------------------------

  dht.begin();

  Serial.println("DHT22 READY");

  delay(2000);

  // ---------------------------------------------------
  // LED TEST
  // ---------------------------------------------------

  Serial.println();
  Serial.println("LED TEST");

  for (int i = 0; i < 3; i++)
  {
    digitalWrite(LED_PIN, LOW);
    delay(250);

    digitalWrite(LED_PIN, HIGH);
    delay(250);
  }

  // ---------------------------------------------------
  // BUZZER TEST
  // ---------------------------------------------------

  Serial.println("BUZZER TEST");

  digitalWrite(BUZZER_PIN, HIGH);

  delay(500);

  digitalWrite(BUZZER_PIN, LOW);

  delay(300);

  // ---------------------------------------------------
  // NORMAL STATE
  // ---------------------------------------------------

  digitalWrite(LED_PIN, HIGH);
  digitalWrite(BUZZER_PIN, LOW);

  Serial.println();
  Serial.println("================================");
  Serial.println("       MOTOSHIELD READY");
  Serial.println("================================");
}

// =====================================================
// READ MPU6050
// =====================================================

void readMPU(
  float &acceleration,
  float &tilt
)
{
  acceleration = 0;
  tilt = 0;

  if (!mpuOK)
  {
    return;
  }

  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temperature;

  mpu.getEvent(
    &accel,
    &gyro,
    &temperature
  );

  // Total acceleration
  acceleration = sqrt(
    accel.acceleration.x *
    accel.acceleration.x +

    accel.acceleration.y *
    accel.acceleration.y +

    accel.acceleration.z *
    accel.acceleration.z
  );

  // Tilt angle
  tilt = atan2(
    accel.acceleration.x,
    accel.acceleration.z
  ) * 180.0 / PI;
}

// =====================================================
// NORMAL BUZZER
// =====================================================

void normalBuzzer()
{
  unsigned long currentTime = millis();

  // Start buzzer every 30 seconds
  if (!buzzerActive &&
      currentTime - lastBuzzer >= BUZZER_INTERVAL)
  {
    lastBuzzer = currentTime;

    buzzerStart = currentTime;

    buzzerActive = true;

    digitalWrite(
      BUZZER_PIN,
      HIGH
    );

    Serial.println();
    Serial.println("********************************");
    Serial.println("BUZZER: ON");
    Serial.println("30 SECOND ALERT");
    Serial.println("********************************");
  }

  // Stop buzzer
  if (buzzerActive &&
      currentTime - buzzerStart >= BUZZER_DURATION)
  {
    buzzerActive = false;

    digitalWrite(
      BUZZER_PIN,
      LOW
    );

    Serial.println("BUZZER: OFF");
  }
}

// =====================================================
// ACCIDENT ALARM
// =====================================================

void accidentAlarm()
{
  unsigned long currentTime = millis();

  // ---------------------------------------------------
  // BLINK LED
  // ---------------------------------------------------

  if ((currentTime / 250) % 2 == 0)
  {
    digitalWrite(
      LED_PIN,
      HIGH
    );
  }
  else
  {
    digitalWrite(
      LED_PIN,
      LOW
    );
  }

  // ---------------------------------------------------
  // BUZZER
  // ---------------------------------------------------

  digitalWrite(
    BUZZER_PIN,
    HIGH
  );

  // ---------------------------------------------------
  // OLED ACCIDENT SCREEN
  // ---------------------------------------------------

  if (oledOK)
  {
    display.clearDisplay();

    display.setTextColor(
      SSD1306_WHITE
    );

    display.setTextSize(2);

    display.setCursor(0, 0);
    display.println("ACCIDENT");

    display.setCursor(0, 22);
    display.println("DETECTED!");

    display.setTextSize(1);

    display.setCursor(0, 45);
    display.println("BUZZER: ON");

    display.setCursor(0, 56);
    display.println("CHECK RIDER");

    display.display();
  }

  // ---------------------------------------------------
  // CLEAR AFTER 10 SECONDS
  // ---------------------------------------------------

  if (currentTime - accidentStart >= ACCIDENT_DURATION)
  {
    accidentDetected = false;

    digitalWrite(
      BUZZER_PIN,
      LOW
    );

    digitalWrite(
      LED_PIN,
      HIGH
    );

    Serial.println("ACCIDENT ALERT CLEARED");
  }
}

// =====================================================
// OLED DASHBOARD
// =====================================================

void showDashboard(
  float acceleration,
  float tilt,
  float temperature,
  float humidity
)
{
  if (!oledOK)
  {
    return;
  }

  display.clearDisplay();

  display.setTextColor(
    SSD1306_WHITE
  );

  display.setTextSize(1);

  // ---------------------------------------------------
  // TITLE
  // ---------------------------------------------------

  display.setCursor(0, 0);

  display.println(
    "MOTOSHIELD"
  );

  // ---------------------------------------------------
  // TEMPERATURE
  // ---------------------------------------------------

  display.setCursor(0, 11);

  display.print("Temp: ");

  if (!isnan(temperature))
  {
    display.print(
      temperature,
      1
    );

    display.println(" C");
  }
  else
  {
    display.println("ERROR");
  }

  // ---------------------------------------------------
  // HUMIDITY
  // ---------------------------------------------------

  display.setCursor(0, 22);

  display.print("Hum : ");

  if (!isnan(humidity))
  {
    display.print(
      humidity,
      0
    );

    display.println(" %");
  }
  else
  {
    display.println("ERROR");
  }

  // ---------------------------------------------------
  // ACCELERATION
  // ---------------------------------------------------

  display.setCursor(0, 33);

  display.print("Accel:");

  if (mpuOK)
  {
    display.print(
      acceleration,
      1
    );

    display.println(
      "m/s2"
    );
  }
  else
  {
    display.println("ERROR");
  }

  // ---------------------------------------------------
  // TILT
  // ---------------------------------------------------

  display.setCursor(0, 44);

  display.print("Tilt :");

  if (mpuOK)
  {
    display.print(
      tilt,
      1
    );

    display.println(
      " deg"
    );
  }
  else
  {
    display.println("ERROR");
  }

  // ---------------------------------------------------
  // STATUS
  // ---------------------------------------------------

  display.setCursor(0, 55);

  display.print("STATUS:");

  display.println(
    "RUNNING"
  );

  display.display();
}

// =====================================================
// MAIN LOOP
// =====================================================

void loop()
{
  // ---------------------------------------------------
  // MPU DATA
  // ---------------------------------------------------

  float acceleration = 0;

  float tilt = 0;

  readMPU(
    acceleration,
    tilt
  );

  // ---------------------------------------------------
  // DHT DATA
  // ---------------------------------------------------

  float temperature =
    dht.readTemperature();

  float humidity =
    dht.readHumidity();

  // ---------------------------------------------------
  // ACCIDENT DETECTION
  // ---------------------------------------------------

  bool impact = false;

  bool tiltDetected = false;

  if (mpuOK)
  {
    if (acceleration >= IMPACT_THRESHOLD)
    {
      impact = true;
    }

    if (abs(tilt) >= TILT_THRESHOLD)
    {
      tiltDetected = true;
    }
  }

  // ---------------------------------------------------
  // TRIGGER ACCIDENT
  // ---------------------------------------------------

  if ((impact || tiltDetected) &&
      !accidentDetected)
  {
    accidentDetected = true;

    accidentStart = millis();

    Serial.println();
    Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!");
    Serial.println("   ACCIDENT DETECTED");
    Serial.println("   EMERGENCY ALERT");
    Serial.println("!!!!!!!!!!!!!!!!!!!!!!!!");
  }

  // ---------------------------------------------------
  // ACCIDENT MODE
  // ---------------------------------------------------

  if (accidentDetected)
  {
    accidentAlarm();

    delay(20);

    return;
  }

  // ---------------------------------------------------
  // NORMAL MODE
  // ---------------------------------------------------

  // LED always ON
  digitalWrite(
    LED_PIN,
    HIGH
  );

  // Buzzer every 30 seconds
  normalBuzzer();

  // ---------------------------------------------------
  // UPDATE DASHBOARD
  // ---------------------------------------------------

  if (millis() - lastDisplay >= 1000)
  {
    lastDisplay = millis();

    // -------------------------------------------------
    // SERIAL OUTPUT
    // -------------------------------------------------

    Serial.println();
    Serial.println("--------------------------------");
    Serial.println("       MOTOSHIELD DASHBOARD");
    Serial.println("--------------------------------");

    Serial.print(
      "Acceleration : "
    );

    if (mpuOK)
    {
      Serial.print(
        acceleration,
        2
      );

      Serial.println(
        " m/s2"
      );
    }
    else
    {
      Serial.println(
        "ERROR"
      );
    }

    Serial.print(
      "Tilt         : "
    );

    if (mpuOK)
    {
      Serial.print(
        tilt,
        1
      );

      Serial.println(
        " deg"
      );
    }
    else
    {
      Serial.println(
        "ERROR"
      );
    }

    Serial.print(
      "Temperature  : "
    );

    if (!isnan(temperature))
    {
      Serial.print(
        temperature,
        1
      );

      Serial.println(
        " C"
      );
    }
    else
    {
      Serial.println(
        "ERROR"
      );
    }

    Serial.print(
      "Humidity     : "
    );

    if (!isnan(humidity))
    {
      Serial.print(
        humidity,
        1
      );

      Serial.println(
        " %"
      );
    }
    else
    {
      Serial.println(
        "ERROR"
      );
    }

    Serial.println(
      "LED          : ON"
    );

    if (buzzerActive)
    {
      Serial.println(
        "BUZZER       : ON"
      );
    }
    else
    {
      Serial.println(
        "BUZZER       : OFF"
      );
    }

    Serial.println(
      "SYSTEM       : RUNNING"
    );

    // -------------------------------------------------
    // OLED
    // -------------------------------------------------

    showDashboard(
      acceleration,
      tilt,
      temperature,
      humidity
    );
  }

  delay(20);
}