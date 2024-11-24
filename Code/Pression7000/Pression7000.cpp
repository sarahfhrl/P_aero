#include "Pression7000.h"

// Constructeur vide
Pression7000::Pression7000()
    : capteur(nullptr), capteurAddress(0) {}

// Initialisation avec les paramètres
bool Pression7000::init(uint8_t address, float minPressure, float maxPressure, const char* unit) {
    capteurAddress = address;

    // Allouer dynamiquement une instance de Honeywell_ABP
    capteur = new Honeywell_ABP(capteurAddress, minPressure, maxPressure, unit);

    // Initialiser la communication I2C
    Wire.begin();

    // Vérifier si l'objet capteur est bien initialisé
    return (capteur != nullptr);
}

// Lire la pression en Pascal
float Pression7000::lirePression() {
    if (capteur) {
        capteur->update();
        return capteur->pressure() * 6894.76; // Conversion de psi en Pascal
    }
    return 0.0; // Retourne 0 en cas d'erreur
}

// Lire la température en °C
float Pression7000::lireTemperature() {
    if (capteur) {
        capteur->update();
        return capteur->temperature();
    }
    return 0.0; // Retourne 0 en cas d'erreur
}
