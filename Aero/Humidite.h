#ifndef HUMIDITE_H
#define HUMIDITE_H

#include <Arduino_HS300x.h>

class Humidite {
public:
    Humidite();
    bool init();
    float lireTemperature();
    float lireHumidite();
};

#endif