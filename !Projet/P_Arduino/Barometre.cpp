#include "Barometre.h"

Barometre::Barometre() {} // Constructeur vide

bool Barometre::init() {
    return BARO.begin();
}

float Barometre::lireTemperature() {
    return BARO.readTemperature();
}

float Barometre::lirePression() {
    return BARO.readPressure();
}