// 3.2.4 Response time with a button - version light sleep
// Meme fonction que la version de reference, mais la carte dort entre deux appuis
// au lieu de scruter le bouton en permanence.
//
// Pourquoi le light sleep et pas le deep sleep : le light sleep conserve la RAM et
// l'etat des peripheriques, l'execution reprend a l'instruction suivante. Le reveil
// par GPIO coute donc quelques centaines de microsecondes, contre les 90 ms de
// demarrage que nous avons mesurees en deep sleep (voir la note d'analyse). Pour
// une reaction a un appui, le deep sleep est disqualifie par ce seul chiffre.
//
// Cablage identique a la version de reference : bouton sur GPIO 2 (repos LOW),
// LED externe sur GPIO 4.

#include <Arduino.h>
#include <esp_sleep.h>
#include <driver/gpio.h>

#define PREFIX "[Binome 11 - SALOMON & VOISSIER] "

const gpio_num_t BOUTON = GPIO_NUM_2;
const int LED = 4;

void setup() {
    Serial.begin(115200);
    delay(1000);
    pinMode(BOUTON, INPUT);
    pinMode(LED, OUTPUT);

    // Reveil sur niveau haut : le bouton au repos est a LOW, l'appui le met a 3,3 V.
    gpio_wakeup_enable(BOUTON, GPIO_INTR_HIGH_LEVEL);
    esp_sleep_enable_gpio_wakeup();

    Serial.println(PREFIX "Bouton -> LED en light sleep, reveil sur GPIO 2");
}

void loop() {
    if (digitalRead(BOUTON) == HIGH) {
        digitalWrite(LED, HIGH);
        while (digitalRead(BOUTON) == HIGH) {
            delay(1);                     // LED allumee tant que l'appui dure
        }
        digitalWrite(LED, LOW);
    }

    // Plus rien a faire : on dort jusqu'au prochain appui, sans timer.
    Serial.flush();
    esp_light_sleep_start();
}
