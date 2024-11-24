#ifndef PRESSION7000_H
#define PRESSION7000_H

#include <Honeywell_ABP.h>
#include <Wire.h>

class Pression7000 {
public:
    Pression7000(); // Constructeur vide
    bool init(uint8_t address, float minPressure, float maxPressure, const char* unit); // Initialisation
    float lirePression(); // Lire la pression en Pascal
    float lireTemperature(); // Lire la température en °C

private:
    Honeywell_ABP* capteur; // Pointeur pour une instance du capteur
    uint8_t capteurAddress; // Adresse du capteur
};

#endif
