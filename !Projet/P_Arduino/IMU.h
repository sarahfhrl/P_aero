#ifndef CAPTEURS_IMU_H
#define CAPTEURS_IMU_H

#include <Arduino_BMI270_BMM150.h>

class CapteursIMU {
public:
    CapteursIMU();                       // Constructeur vide
    bool init();                         // Initialisation des capteurs
    void lireDonnees(float &ax, float &ay, float &az, 
                     float &gx, float &gy, float &gz, 
                     float &mx, float &my, float &mz); // Lecture des données
    void recalibrer();                   // Recalibrage automatique
    float calculerInclinaison();         // Retourne l'inclinaison (pitch) en degrés

private:
    //float offsetX, offsetY, offsetZ;     // Offsets pour recalibrer l'accéléromètre
};

#endif
