#ifndef BAROMETRE_H
#define BAROMETRE_H

#include <Arduino_LPS22HB.h>

class Barometre {
public:
    Barometre();
    bool init();
    float lireTemperature();
    float lirePression();
};

#endif