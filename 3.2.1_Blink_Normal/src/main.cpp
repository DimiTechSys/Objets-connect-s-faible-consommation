// 3.2.1 Normal Mode - Consumption
// LED allumee pendant T_on, eteinte le reste de la periode, carte active en permanence.
// Reference a laquelle on compare le light sleep et le deep sleep.
// Capture correspondante : captures/normal_mode.csv (38,67 mA sur 4 cycles complets).

#include <Arduino.h>

#define PREFIX "[Binome 11 - SALOMON & VOISSIER] "

const int LED = LED_BUILTIN;              // GPIO 2 sur le DOIT DevKit V1
const unsigned long T_ON = 550;           // 50 x N, avec N = 11
const unsigned long PERIODE = 2000;       // identique pour tous les binomes

void setup() {
    Serial.begin(115200);
    delay(1000);
    pinMode(LED, OUTPUT);
    Serial.println(PREFIX "Mode normal : T_on = 550 ms sur 2000 ms (rapport cyclique 27,5 %)");
}

void loop() {
    digitalWrite(LED, HIGH);
    delay(T_ON);
    digitalWrite(LED, LOW);
    delay(PERIODE - T_ON);                // 1450 ms, carte toujours active
}
