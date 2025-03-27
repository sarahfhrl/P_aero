#include "Pression125.h"

// Constructeur vide
Pression125::Pression125()
    : capteur(nullptr), capteurAddress(0) {}

// Destructeur
Pression125::~Pression125() {
    delete capteur;
}

// Initialisation avec les paramètres
bool Pression125::init(uint8_t address) {
    capteurAddress = address;

    // Allouer dynamiquement une instance de SensirionI2CSdp
    capteur = new SensirionI2CSdp();

    // Initialiser la communication I2C et le capteur
    Wire.begin();
    capteur->begin(Wire, capteurAddress);

    // Démarrer la mesure continue
    uint16_t error = capteur->startContinuousMeasurementWithDiffPressureTCompAndAveraging();
    if (error) {
        Serial.print("Erreur de démarrage de la mesure 125Pa : ");
        Serial.println(error);
        return false;
    }

    // Retourner true si l'objet est correctement initialisé
    return (capteur != nullptr);
}

// Lire la pression en Pascal
float Pression125::lirePression() {
    if (capteur) {
        float pression = 0.0;
        float temperature = 0.0;

        if (capteur->readMeasurement(pression, temperature) == 0) {
            return pression; // La pression est déjà en Pascal
        }
    }
    return 0.0; // Retourne 0 en cas d'erreur
}

// Lire la température en °C
float Pression125::lireTemperature() {
    if (capteur) {
        float pression = 0.0;
        float temperature = 0.0;

        if (capteur->readMeasurement(pression, temperature) == 0) {
            return temperature; // La température est en °C
        }
    }
    return 0.0; // Retourne 0 en cas d'erreur
}
