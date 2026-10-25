// 3.2.3 DeepSleep Mode - Consumption
// Reveil toutes les T_sleep = 1 + 0,25 x N = 3,75 s.
//
// Le deep sleep coupe le coeur principal et la RAM : au reveil le programme
// REDEMARRE depuis setup(), il ne reprend pas. Tout le travail doit donc tenir
// dans setup(), et loop() n'est jamais atteinte.
//
// Pas de Serial ici, volontairement : c'est la version qui a servi a la capture
// captures/deep_sleep.csv. Un Serial.begin() allongerait la phase active, que
// nous avons mesuree a 640 ms (28,75 ms de domaine RTC + 61,25 ms de demarrage
// + 550,00 ms de LED allumee) pour une periode reelle de 4,369 s.

#include <Arduino.h>
#include <esp_sleep.h>

const int LED = LED_BUILTIN;              // GPIO 2
const unsigned long T_ON = 550;           // 50 x N, avec N = 11
const uint64_t T_SLEEP_US = 3750000ULL;   // (1 + 0,25 x 11) s

void setup() {
    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);
    delay(T_ON);
    digitalWrite(LED, LOW);

    esp_sleep_enable_timer_wakeup(T_SLEEP_US);
    esp_deep_sleep_start();               // ne rend jamais la main
}

void loop() {
    // jamais atteinte : esp_deep_sleep_start() ne revient pas
}
