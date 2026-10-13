#include <Arduino.h>

void buttonReleased();

volatile int count = 0;              
volatile bool countChanged = false;

volatile unsigned long lastInterruptTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  pinMode(2, INPUT);
  Serial.begin(9600);

  // Appelle buttonReleased() à chaque front descendant (HIGH -> LOW = relâchement)
  attachInterrupt(digitalPinToInterrupt(2), buttonReleased, FALLING);
}

void buttonReleased() {
  unsigned long now = millis();
  if (now - lastInterruptTime > debounceDelay) {  // anti-rebond
    count++;
    countChanged = true;
    lastInterruptTime = now;
  }
}

void loop() {

  if (countChanged) {
    countChanged = false;
    Serial.print("[Binome 11 - SALOMON & VOISSIER] count = ");
    Serial.println(count);
  }
}