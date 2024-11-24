#ifndef PRESSION125_H
#define PRESSION125_H

#include <SensirionI2CSdp.h>

#include <Wire.h>

class Pression125 {
public:
    Pression125();                // Constructeur vide
    bool init(uint8_t address);    // Initialisation avec adresse I2C
    float lirePression();          // Retourne la pression en Pascal
    float lireTemperature();       // Retourne la température en °C

private:
    SensirionI2CSdp* capteur;      // Pointeur vers l'instance du capteur
    uint8_t capteurAddress;        // Adresse I2C du capteur
};

#endif
