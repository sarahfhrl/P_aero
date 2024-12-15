#include "Pression125.h"

// Créer une instance du capteur Pression125
Pression125 capteur;

void setup() {
    Serial.begin(115200);

    // Initialiser le capteur avec son adresse I2C
    if (!capteur.init(0x25)) { // Remplacez 0x25 par l'adresse I2C réelle de votre capteur
        Serial.println("Échec de l'initialisation du capteur !");
        while (1); // Bloquer en cas d'erreur
    }
}

void loop() {
    // Lire et afficher la pression
    Serial.print("Pression (Pa) : ");
    Serial.println(capteur.lirePression());

    // Lire et afficher la température
    Serial.print("Température (°C) : ");
    Serial.println(capteur.lireTemperature());

    delay(1000);
}
