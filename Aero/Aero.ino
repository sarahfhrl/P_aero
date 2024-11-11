#include <Arduino.h>
#include "Humidite.h"

Humidite capteurHumidite;  // Création de l'objet capteurHumidite

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!capteurHumidite.init()) {
    Serial.println("HUMIDITE et TEMPERATURE marche pas !");
  }
}

void loop() {
  float temperature = capteurHumidite.lireTemperature();
  float humidite = capteurHumidite.lireHumidite();

  Serial.println(temperature);
  Serial.println(humidite);

  delay(1000); // Pause de 1 seconde
}