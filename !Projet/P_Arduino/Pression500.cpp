#include "Pression500.h"

DFRobot_LWLP lwlp;

Pression500::Pression500() {} // Constructeur vide

bool Pression500::init() {
  if (int error = !lwlp.begin()) {
      return false;
  }

  auto data = lwlp.getData();
  if (data.temperature > 80 || data.presure > 599) {
    return false;
  }
  return true;
}


float Pression500::lireTemperature() {
  return lwlp.getData().temperature;
}

float Pression500::lirePression() {
  return lwlp.getData().presure;
}