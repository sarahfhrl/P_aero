#ifndef PRESSION500_H
#define PRESSION500_H

#include <DFRobot_LWLP.h>

class Pression500 {
public:
    Pression500();
    bool init();
    float lireTemperature();
    float lirePression();
};

#endif