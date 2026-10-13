#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include "secrets.h"

#define PREFIX "[Binome 11 - SALOMON & VOISSIER] "
#define CITY "Paris"

const unsigned long PERIOD_MS = 15UL * 60UL * 1000UL;  // 15 min : quota du plan gratuit
unsigned long lastRequest = 0;

bool connectWiFi() {
    Serial.printf(PREFIX "Connecting to %s\n", WIFI_SSID);
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED) {
        if (millis() - start > 20000) {
            Serial.printf(PREFIX "WiFi failed, status = %d\n", WiFi.status());
            return false;
        }
        delay(500);
    }
    Serial.print(PREFIX "Connected, IP: ");
    Serial.println(WiFi.localIP());
    return true;
}

void getWeather() {
    if (WiFi.status() != WL_CONNECTED && !connectWiFi()) return;

    String url = String("http://api.weatherstack.com/current?access_key=")
               + WEATHERSTACK_KEY + "&query=" + CITY;

    HTTPClient http;
    http.begin(url);
    int code = http.GET();

    if (code != 200) {
        Serial.printf(PREFIX "HTTP error: %d\n", code);
        http.end();
        return;
    }

    String payload = http.getString();
    http.end();

    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, payload);
    if (err) {
        Serial.printf(PREFIX "JSON error: %s\n", err.c_str());
        return;
    }

    // L'API renvoie HTTP 200 meme en cas d'erreur : il faut verifier "success"
    if (doc["success"].is<bool>() && !doc["success"].as<bool>()) {
        Serial.printf(PREFIX "API error: %s\n", doc["error"]["info"].as<const char*>());
        return;
    }

    const char* city      = doc["location"]["name"];
    const char* localtime = doc["location"]["localtime"];
    int temperature       = doc["current"]["temperature"];
    int windSpeed         = doc["current"]["wind_speed"];

    Serial.printf(PREFIX "City: %s\n", city);
    Serial.printf(PREFIX "Local time: %s\n", localtime);
    Serial.printf(PREFIX "Temperature: %d C\n", temperature);
    Serial.printf(PREFIX "Wind speed: %d km/h\n", windSpeed);
}

void setup() {
    Serial.begin(115200);
    delay(1000);
    connectWiFi();
    getWeather();
    lastRequest = millis();
}

void loop() {
    if (millis() - lastRequest >= PERIOD_MS) {
        lastRequest = millis();
        getWeather();
    }
}
