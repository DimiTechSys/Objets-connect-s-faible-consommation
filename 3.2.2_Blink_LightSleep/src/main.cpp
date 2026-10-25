// 3.2.2 Light Sleep Mode - Consumption
// Memes parametres qu'en mode normal, mais la carte dort au lieu d'attendre.
// Le light sleep conserve la RAM et l'etat : l'execution REPREND apres
// esp_light_sleep_start(), elle ne redemarre pas. C'est pour cela que tout
// tient dans loop(), contrairement au deep sleep.
// Capture correspondante : captures/light_sleep.csv (20,48 mA sur 3 cycles complets ;
// phases de sommeil mesurees a 1450,00 ms de moyenne pour 1450 ms demandees).

#include <Arduino.h>
#include <esp_sleep.h>

#define PREFIX "[Binome 11 - SALOMON & VOISSIER] "

const int LED = LED_BUILTIN;              // GPIO 2
const unsigned long T_ON = 550;           // 50 x N, avec N = 11
const unsigned long PERIODE = 2000;
const uint64_t T_SOMMEIL_US = (PERIODE - T_ON) * 1000ULL;   // 1 450 000 us

void setup() {
    Serial.begin(115200);
    delay(1000);
    pinMode(LED, OUTPUT);
    Serial.println(PREFIX "Light sleep : 550 ms actif, 1450 ms de sommeil");
}

void loop() {
    digitalWrite(LED, HIGH);
    delay(T_ON);
    digitalWrite(LED, LOW);

    Serial.flush();                       // vider l'UART avant de couper l'horloge
    esp_sleep_enable_timer_wakeup(T_SOMMEIL_US);
    esp_light_sleep_start();              // reprend ici au reveil
}
