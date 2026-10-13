#include <Arduino.h>
#include <Wire.h>
#include <WiFi.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "secrets.h"

#define PREFIX "[Binome 11 - SALOMON & VOISSIER] "

#define AIO_SERVER "io.adafruit.com"
#define AIO_PORT   1883  // MQTT non chiffre

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_PORT, IO_USERNAME, IO_KEY);

// Un "topic" MQTT par feed : <username>/feeds/<nom_du_feed>
Adafruit_MQTT_Publish tempFeed(&mqtt, IO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish humFeed(&mqtt, IO_USERNAME "/feeds/humidity");

Adafruit_BME680 bme;

const unsigned long PERIOD_MS = 10000;  // 2 valeurs / 10 s = 12 / min
unsigned long lastSend = 0;

void connectWiFi() {
    Serial.printf(PREFIX "Connecting to %s\n", WIFI_SSID);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    Serial.print(PREFIX "WiFi connected, IP: ");
    Serial.println(WiFi.localIP());
}

void connectMQTT() {
    if (mqtt.connected()) return;

    Serial.println(PREFIX "Connecting to Adafruit IO (MQTT)");
    int8_t ret;
    while ((ret = mqtt.connect()) != 0) {
        Serial.printf(PREFIX "MQTT error: %s, retry in 5 s\n", mqtt.connectErrorString(ret));
        mqtt.disconnect();
        delay(5000);
    }
    Serial.println(PREFIX "MQTT connected");
}

void setup() {
    Serial.begin(115200);
    delay(1000);

    if (!bme.begin()) {  // bme.begin(0x76) si besoin
        Serial.println(PREFIX "BME680 not found");
        while (1);
    }
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150);

    connectWiFi();
}

void loop() {
    if (WiFi.status() != WL_CONNECTED) connectWiFi();
    connectMQTT();  // reconnecte si la connexion au broker est tombee

    if (millis() - lastSend < PERIOD_MS) return;
    lastSend = millis();

    if (!bme.performReading()) {
        Serial.println(PREFIX "BME680 reading failed");
        return;
    }

    bool okT = tempFeed.publish(bme.temperature);
    bool okH = humFeed.publish(bme.humidity);

    Serial.printf(PREFIX "Sent: temperature = %.2f C (%s), humidity = %.2f %% (%s)\n",
                  bme.temperature, okT ? "OK" : "FAIL",
                  bme.humidity,    okH ? "OK" : "FAIL");
}
