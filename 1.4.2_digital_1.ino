const int buttonPin = 2;

int count = 0;               // variable GLOBALE
int buttonState = LOW;
int lastButtonState = LOW;   // état au tour précédent

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50; 

void setup() {
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);        // indispensable pour l'affichage !
}

void loop() {
  int reading = digitalRead(buttonPin);

  // Si l'état a changé, on note l'heure (le bouton "bouge")
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // Si l'état est stable depuis plus de 50 ms, on le relis
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      // Front descendant : le bouton vient d'être RELÂCHÉ (HIGH -> LOW) & count + 1
      if (buttonState == LOW) {
        count++;
        Serial.print("[Binome 11 - SALOMON & VOISSIER] count = ");
        Serial.println(count);   // affiché UNIQUEMENT quand ça change
      }
    }
  }

  lastButtonState = reading;
}