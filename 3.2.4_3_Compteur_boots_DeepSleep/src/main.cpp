// 3.2.4 Counting the boots - DeepSleep Mode
// Deux compteurs cote a cote pour montrer ce qui survit a quoi :
//
//   compteurOrdinaire  variable globale en RAM. La RAM principale n'est plus
//                      alimentee en deep sleep : elle est reinitialisee a chaque
//                      reveil, donc ce compteur affiche toujours 1.
//
//   compteurRTC        place en memoire RTC par RTC_DATA_ATTR. Ces 8 ko restent
//                      alimentes pendant le deep sleep, donc la valeur survit.
//                      Elle survit aussi a un reset logiciel, mais PAS a une
//                      coupure d'alimentation ni a l'appui sur EN : dans ces deux
//                      cas le domaine RTC perd son alimentation et repart a zero.
//                      Pour survivre a tout, il faudrait la flash (Preferences /
//                      NVS), au prix d'une ecriture et d'une usure limitee.
//
// esp_reset_reason() dit pourquoi la carte a demarre : ESP_RST_POWERON au premier
// allumage, ESP_RST_DEEPSLEEP apres un reveil. C'est la preuve qu'un reveil de deep
// sleep est bien un REDEMARRAGE et non une reprise d'execution.

#include <Arduino.h>
#include <esp_sleep.h>
#include <esp_system.h>

#define PREFIX "[Binome 11 - SALOMON & VOISSIER] "

const int LED = LED_BUILTIN;              // GPIO 2
const unsigned long T_ON = 550;           // 50 x N, avec N = 11
const uint64_t T_SLEEP_US = 3750000ULL;   // (1 + 0,25 x 11) s

int compteurOrdinaire = 0;                // en RAM : perdu a chaque deep sleep
RTC_DATA_ATTR int compteurRTC = 0;        // en memoire RTC : conserve

const char *raisonDuDemarrage(esp_reset_reason_t r) {
    switch (r) {
        case ESP_RST_POWERON:  return "ESP_RST_POWERON (mise sous tension)";
        case ESP_RST_DEEPSLEEP: return "ESP_RST_DEEPSLEEP (reveil de deep sleep)";
        case ESP_RST_SW:       return "ESP_RST_SW (reset logiciel)";
        case ESP_RST_EXT:      return "ESP_RST_EXT (broche EN)";
        case ESP_RST_PANIC:    return "ESP_RST_PANIC (exception)";
        case ESP_RST_WDT:      return "ESP_RST_WDT (chien de garde)";
        default:               return "autre";
    }
}

void setup() {
    Serial.begin(115200);
    delay(50);                            // laisser l'UART s'etablir

    compteurOrdinaire++;
    compteurRTC++;

    Serial.printf(PREFIX "boot #%d - raison: %s - compteur ordinaire: %d\n",
                  compteurRTC, raisonDuDemarrage(esp_reset_reason()), compteurOrdinaire);

    pinMode(LED, OUTPUT);
    digitalWrite(LED, HIGH);
    delay(T_ON);
    digitalWrite(LED, LOW);

    Serial.flush();
    esp_sleep_enable_timer_wakeup(T_SLEEP_US);
    esp_deep_sleep_start();
}

void loop() {
    // jamais atteinte
}
