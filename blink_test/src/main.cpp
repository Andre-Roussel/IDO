#include <Arduino.h>

void setup() {

  //Placer la broche LED_BUILTIN en mode sortie
  pinMode(LED_BUILTIN,OUTPUT);

}

void loop() {
  // En premier lieu, allumer la LED_BUILTIN
  // Faire une pause de 200 ms
  // Éteindre la LED_BUILTIN
  // Faire une pause de 200 ms

  digitalWrite(LED_BUILTIN,HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN,LOW);
  delay(200);
  
}