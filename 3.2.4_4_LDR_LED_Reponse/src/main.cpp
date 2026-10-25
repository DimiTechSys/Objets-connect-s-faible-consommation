// 3.2.4 Response time with an ADC - version de reference
// La LED s'allume tant que la LDR depasse un seuil, carte active en permanence.
//
// Cablage : LDR en pont diviseur sur GPIO 36 (ADC1_CH0), comme en partie 1.5 ;
// ADC1 et non ADC2, car ADC2 devient inutilisable des que le Wi-Fi est actif.
// LED externe sur GPIO 4 : GPIO 36 est input-only et la LED de la carte est sur
// GPIO 2, qu'on garde libre.
//
// Le seuil vient de notre propre calibration de la partie 1.5 : 474 dans
// l'obscurite, 4095 en pleine lumiere (valeur saturee). On place le seuil a
// mi-chemin de la plage reellement exploitable, en gardant a l'esprit que 4095
// est une saturation de l'ADC et non la vraie borne haute de la LDR.
//
// Mesure a l'oscilloscope : une voie sur le point milieu du pont (entree), une
// voie sur GPIO 4 (sortie). Le temps de reponse inclut ici la duree de la
// conversion analogique-numerique, contrairement au cas du bouton.

#include <Arduino.h>

#define PREFIX "[Binome 11 - SALOMON & VOISSIER] "

const int LDR = 36;
const int LED = 4;
const int SEUIL = 2200;                   // entre nos 474 (obscurite) et 4095 (sature)

void setup() {
    Serial.begin(115200);
    delay(1000);
    pinMode(LED, OUTPUT);
    Serial.printf(PREFIX "Temps de reponse LDR -> LED, seuil = %d\n", SEUIL);
}

void loop() {
    // Scrutation serree, sans delay ni Serial : le temps mesure doit etre celui
    // de la chaine ADC -> decision -> sortie, rien d'autre.
    digitalWrite(LED, analogRead(LDR) > SEUIL ? HIGH : LOW);
}
