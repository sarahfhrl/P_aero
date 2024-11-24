#include "Pression7000.h"

// Créer une instance du convertisseur
Pression7000 capteur;

void setup() {
    Serial.begin(9600);
    while (!Serial);

    // Initialiser le capteur avec ses paramètres
    if (!capteur.init(0x28, 0, 1, "psi")) {
        Serial.println("Échec de l'initialisation du capteur !");
        while (1); // Bloquer l'exécution si l'initialisation échoue
    }
}

void loop() {
    // Lire et afficher la pression en Pascal
    Serial.print("Pression (Pa) : ");
    Serial.println(capteur.lirePression());

    // Lire et afficher la température
    Serial.print("Température (°C) : ");
    Serial.println(capteur.lireTemperature());

    delay(1000);
}
