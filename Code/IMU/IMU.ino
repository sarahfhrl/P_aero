#include "IMU.h"

CapteursIMU capteurs;

void setup() {
    Serial.begin(9600);
    if (!capteurs.init()) {
        Serial.println("Échec de l'initialisation des capteurs !");
        while (1); // Bloquer en cas d'erreur
    }
    Serial.println("Capteurs initialisés !");
    capteurs.recalibrer(); // Recalibrage initial
}

void loop() {
    float ax, ay, az, gx, gy, gz, mx, my, mz;

    // Lire les données des capteurs
    capteurs.lireDonnees(ax, ay, az, gx, gy, gz, mx, my, mz);

    // Afficher les données
    Serial.print("Accéléromètre : ax=");
    Serial.print(ax);
    Serial.print(", ay=");
    Serial.print(ay);
    Serial.print(", az=");
    Serial.println(az);

    Serial.print("Gyroscope : gx=");
    Serial.print(gx);
    Serial.print(", gy=");
    Serial.print(gy);
    Serial.print(", gz=");
    Serial.println(gz);

    Serial.print("Magnétomètre : mx=");
    Serial.print(mx);
    Serial.print(", my=");
    Serial.print(my);
    Serial.print(", mz=");
    Serial.println(mz);

    // Calculer et afficher l'inclinaison
    float pitch = capteurs.calculerInclinaison();
    Serial.print("Inclinaison (pitch) : ");
    Serial.println(pitch);

    delay(1000); // Pause de 1 seconde
}
