#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define PREFIX "[Binome 11 - SALOMON & VOISSIER] "

LiquidCrystal_I2C lcd(0x27, 16, 2);  // adresse, colonnes, lignes

unsigned long lastSecond = 0;

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println(PREFIX "LCD test start");

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("Great IoT Tutorial!");  // 19 caracteres pour 16 colonnes : a vous de choisir comment gerer
}

void loop() {
    unsigned long seconds = millis() / 1000;
    if (seconds != lastSecond) {
        lastSecond = seconds;

        lcd.setCursor(0, 1);
        lcd.print("Launched for ");
        lcd.print(seconds);
        lcd.print("s   ");  // les espaces effacent les restes de l'affichage precedent

        Serial.printf(PREFIX "Launched for %lus\n", seconds);
    }
}
