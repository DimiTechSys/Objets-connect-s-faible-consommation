// 3.2.4 Response time with an ADC - version deep sleep
// Meme fonction, mais la carte dort entre deux lectures.
//
// Limite a connaitre : l'ESP32 ne sait pas se reveiller sur un seuil analogique.
// Seul le coprocesseur ULP peut lire l'ADC pendant le deep sleep, et il se
// programme en assembleur (annexe 5 du sujet). Sans ULP, la seule strategie est
// de se reveiller periodiquement, lire, decider, se rendormir.
//
// La consequence est directe et c'est l'arbitrage du TP : le temps de reponse
// n'est plus celui de la chaine de mesure, il vaut au pire la periode de reveil,
// soit notre T_sleep de 3,75 s, plus les 90 ms de demarrage que nous avons
// mesurees. Raccourcir T_sleep ameliore la reponse et degrade la consommation ;
// l'allonger fait l'inverse. Pour une detection de lumiere ce compromis est
// acceptable ; pour reagir a un appui, il ne l'est pas, d'ou la version light
// sleep du bouton.
//
// Cablage identique a la version de reference : LDR sur GPIO 36, LED sur GPIO 4.

#include <Arduino.h>
#include <esp_sleep.h>

#define PREFIX "[Binome 11 - SALOMON & VOISSIER] "

const int LDR = 36;
const int LED = 4;
const int SEUIL = 2200;
const unsigned long T_SIGNAL = 550;       // duree d'allumage, notre T_on
const uint64_t T_SLEEP_US = 3750000ULL;   // notre T_sleep

void setup() {
    Serial.begin(115200);
    delay(50);
    pinMode(LED, OUTPUT);

    int mesure = analogRead(LDR);
    Serial.printf(PREFIX "LDR = %d (seuil %d)\n", mesure, SEUIL);

    if (mesure > SEUIL) {
        digitalWrite(LED, HIGH);
        delay(T_SIGNAL);
        digitalWrite(LED, LOW);
    }

    Serial.flush();
    esp_sleep_enable_timer_wakeup(T_SLEEP_US);
    esp_deep_sleep_start();
}

void loop() {
    // jamais atteinte
}
