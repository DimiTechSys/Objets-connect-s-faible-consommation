#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include <LiquidCrystal_I2C.h>

#define PREFIX "[Binome 11 - SALOMON & VOISSIER] "

Adafruit_BME680 bme;                 // I2C, SDA=21, SCL=22
LiquidCrystal_I2C lcd(0x27, 16, 2);  // adresse trouvee au scan

unsigned long lastReading = 0;
const unsigned long PERIOD_MS = 2000;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println(PREFIX "BME680 + LCD start");

    lcd.init();
    lcd.backlight();

    if (!bme.begin(0x77)) {  // bme.begin(0x76) si le scan a donne 0x76
        Serial.println(PREFIX "Could not find a valid BME680 sensor, check wiring!");
        lcd.setCursor(0, 0);
        lcd.print("BME680 error");
        while (1);
    }

    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150);
}

void loop() {
    if (millis() - lastReading < PERIOD_MS) return;
    lastReading = millis();

    if (!bme.performReading()) {
        Serial.println(PREFIX "Failed to perform reading");
        return;
    }

    float tempC = bme.temperature;
    float tempF = tempC * 9.0 / 5.0 + 32.0;
    float hum = bme.humidity;

    char line[17];  // 16 caracteres + fin de chaine

    snprintf(line, sizeof(line), "T: %5.1f C      ", tempC);
    lcd.setCursor(0, 0);
    lcd.print(line);

    snprintf(line, sizeof(line), "H: %5.1f %%      ", hum);
    lcd.setCursor(0, 1);
    lcd.print(line);

    Serial.printf(PREFIX "Temperature = %.2f C / %.2f F, Humidity = %.2f %%\n",
                  tempC, tempF, hum);
}
