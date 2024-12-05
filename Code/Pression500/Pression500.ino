#include <Arduino.h>
#include "Pression500.h"

Pression500 capteurPression;  // Création de l'objet capteurHumidite

void setup() {
  Serial.begin(115200);
  while (!Serial);

  if (!capteurPression.init()) {
    Serial.println("Pression et TEMPERATURE marche pas !");
  }
}

void loop() {
  float temperature = capteurPression.lireTemperature();
  float humidite = capteurPression.lirePression();

  Serial.println(temperature);
  Serial.println(humidite);

  delay(1000); // Pause de 1 seconde
}
