#include "Pression500.h"

DFRobot_LWLP lwlp;

Pression500::Pression500() {} // Constructeur vide

bool Pression500::init() {
    return lwlp.begin();
}

float Pression500::lireTemperature() {
    return lwlp.getData().temperature;
}

float Pression500::lirePression() {
    return lwlp.getData().presure;
}