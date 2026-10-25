// 3.2.4 Response time with a button - version de reference
// La LED est allumee tant que le bouton est appuye, carte active en permanence.
// Sert de reference pour le temps de reponse bouton -> LED : la boucle ne
// contient aucun delai, donc le temps mesure est celui du chemin
// lecture GPIO -> ecriture GPIO.
//
// Cablage : le bouton reste sur GPIO 2 comme en partie 1 (resistance de tirage
// de 10 kOhm vers la masse, donc repos a LOW et appui a 3,3 V). La LED ne peut
// pas etre celle de la carte, qui partage GPIO 2 avec le bouton : on utilise une
// LED externe sur GPIO 4, libre et capable de sortie.
//
// Mesure a l'oscilloscope : une voie sur GPIO 2 (entree), une voie sur GPIO 4
// (sortie), declenchement sur le front montant de l'entree. Le temps de reponse
// est l'ecart entre les deux fronts.

#include <Arduino.h>

#define PREFIX "[Binome 11 - SALOMON & VOISSIER] "

const int BOUTON = 2;
const int LED = 4;

void setup() {
    Serial.begin(115200);
    delay(1000);
    pinMode(BOUTON, INPUT);
    pinMode(LED, OUTPUT);
    Serial.println(PREFIX "Temps de reponse bouton -> LED, carte active en permanence");
}

void loop() {
    // Scrutation serree : pas de delay, pas de Serial dans la boucle, pour ne pas
    // ajouter de retard a ce que l'on cherche justement a mesurer.
    digitalWrite(LED, digitalRead(BOUTON));
}
