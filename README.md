# Objets connectés faible consommation — Binôme 11 (SALOMON & VOISSIER)

Un projet PlatformIO par exercice, pour carte ESP32 DOIT DevKit V1 (framework Arduino).
Chaque dossier contient son `platformio.ini` et son code dans `src/main.cpp`.

| Dossier | Question | Contenu | Figure du rapport |
|---|---|---|---|
| [`1.3.2_Hello_Serial`](1.3.2_Hello_Serial) | 1.3.2 | Message « Hello Arduino World! » sur le port série | |
| [`1.4.2.1_Blink_SOS`](1.4.2.1_Blink_SOS) | 1.4.2 (1) | LED intégrée qui clignote SOS en morse | |
| [`1.4.2.2_Blink_SOS`](1.4.2.2_Blink_SOS) | 1.4.2 (2) | LED intégrée qui clignote SOS en morse | |
| [`1.4.2_digital_1_Button_polling`](1.4.2_digital_1_Button_polling) | 1.4.2 digital 1 | Compteur d'appuis sur bouton (GPIO 2), lecture en boucle avec anti-rebond | |
| [`1.4.2_digital_2_Button_interrupt`](1.4.2_digital_2_Button_interrupt) | 1.4.2 digital 2 | Même compteur, avec interruption sur front descendant | |
| [`1.5.2_Q1_ADC`](1.5.2_Q1_ADC) | 1.5.2 Q1 | Lecture ADC sur GPIO 36, conversion en millivolts | |
| [`1.5.2_Q2_LDR_calibration`](1.5.2_Q2_LDR_calibration) | 1.5.2 Q2 | Photorésistance calibrée sur 5 s, valeur ramenée sur 0-255 | |
| [`2.1.1_LCD`](2.1.1_LCD) | 2.1.1 | Écran LCD I2C 16x2 : texte et temps écoulé | |
| [`2.1.2.2_LCD_BME680`](2.1.2.2_LCD_BME680) | 2.1.2.2 | Température et humidité du BME680 sur le LCD et le port série | |
| [`2.2.1_3_Weatherstack`](2.2.1_3_Weatherstack) | 2.2.1 Q3 | Météo de Paris via l'API Weatherstack (HTTP + JSON) | |
| [`2.3_AdafruitIO_MQTT`](2.3_AdafruitIO_MQTT) | 2.3 | Envoi température et humidité du BME680 vers Adafruit IO en MQTT | |

## Compiler et téléverser

Ouvrir le dossier d'un exercice dans VS Code avec l'extension PlatformIO, ou en ligne de commande :

```bash
cd 2.3_AdafruitIO_MQTT
pio run --target upload
pio device monitor
```

## Secrets

Les projets `2.2.1_3_Weatherstack` et `2.3_AdafruitIO_MQTT` lisent leurs identifiants
(Wi-Fi, clé Weatherstack, clé Adafruit IO) dans `include/secrets.h`, qui n'est pas versionné.
Copier `include/secrets.example.h` en `include/secrets.h` et remplir les valeurs.
