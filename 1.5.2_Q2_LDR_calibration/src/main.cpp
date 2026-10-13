#include <Arduino.h>

const int ldrPin = 36;
const String prefix = "[Binome 11 - SALOMON & VOISSIER] ";

int sensorValue = 0;
int sensorMin = 4095;   // valeur min observée (init au max possible)
int sensorMax = 0;      // valeur max observée (init au min possible)
int calibratedValue = 0;

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println(prefix + "Calibration starting for 5 seconds...");
    Serial.println(prefix + "Expose the LDR to light, then cover it during this time.");

    unsigned long calibrationStart = millis();
    while (millis() - calibrationStart < 5000) {
        sensorValue = analogRead(ldrPin);
        if (sensorValue > sensorMax) sensorMax = sensorValue;
        if (sensorValue < sensorMin) sensorMin = sensorValue;
    }

    Serial.println(prefix + "Calibration done.");
    Serial.println(prefix + "Min = " + String(sensorMin) + " / Max = " + String(sensorMax));
}

void loop() {
    sensorValue = analogRead(ldrPin);

    // On empêche une valeur hors de la plage calibrée (sécurité)
    sensorValue = constrain(sensorValue, sensorMin, sensorMax);

    // On ramène la plage [sensorMin, sensorMax] vers [0, 255]
    calibratedValue = map(sensorValue, sensorMin, sensorMax, 0, 255);

    Serial.println(prefix + "Raw: " + String(sensorValue) +
                    " | Calibrated (0-255): " + String(calibratedValue));

    delay(1000);
}
