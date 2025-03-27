#include "Humidite.h"

Humidite::Humidite() {} // Constructeur vide

bool Humidite::init() {
    return HS300x.begin();
}

float Humidite::lireTemperature() {
    return HS300x.readTemperature();
}

float Humidite::lireHumidite() {
    return HS300x.readHumidity();
}