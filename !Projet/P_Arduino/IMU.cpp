#include "IMU.h"
#include <Wire.h>
#include <math.h>

#define GRAVITY 9.81 // Constante gravitationnelle en m/s²

CapteursIMU::CapteursIMU() {} // : offsetX(0), offsetY(0), offsetZ(0) {}

bool CapteursIMU::init() {
    // Initialiser le BMI270 et le BMM150
    if (!IMU.begin()) {
        return false;
    }

    Serial.println("BMI270 et BMM150 initialisés !");
    return true;
}

void CapteursIMU::lireDonnees(float &ax, float &ay, float &az, 
                              float &gx, float &gy, float &gz, 
                              float &mx, float &my, float &mz) {
    // Lire les données de l'accéléromètre
    if (IMU.accelerationAvailable()) {
        IMU.readAcceleration(ax, ay, az);
        //ax -= offsetX;
        //ay -= offsetY;
        //az -= offsetZ;
    }

    // Lire les données du gyroscope
    if (IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(gx, gy, gz);
    }

    // Lire les données du magnétomètre
    if (IMU.magneticFieldAvailable()) {
        IMU.readMagneticField(mx, my, mz);
    }
}

void CapteursIMU::recalibrer() { // n'est pas utilisé
    float ax, ay, az, gx, gy, gz, mx, my, mz;
    lireDonnees(ax, ay, az, gx, gy, gz, mx, my, mz);

    // Recalibrage de l'accéléromètre à l'aide de g
    float magnitude = sqrt(ax * ax + ay * ay + az * az);
    //offsetX = ax - (ax / magnitude) * GRAVITY;
    //offsetY = ay - (ay / magnitude) * GRAVITY;
    //offsetZ = az - (az / magnitude) * GRAVITY;

    // Recalibrage de la boussole (alignement sur le champ magnétique terrestre)
    float heading = atan2(my, mx);
    Serial.print("Calibration effectuée. Direction : ");
    Serial.println(heading * 180.0 / PI); // Afficher en degrés
}