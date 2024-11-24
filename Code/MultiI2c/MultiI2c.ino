#include <Wire.h>

#define TCA9548A_ADRESSE 0x70 // Adresse par défaut du TCA9548A

// Fonction pour sélectionner un canal du TCA9548A
void tcaSelect(uint8_t canal) {
    if (canal > 7) return; // Le TCA9548A a 8 canaux (0 à 7)
    Wire.beginTransmission(TCA9548A_ADRESSE);
    Wire.write(1 << canal); // Active uniquement le canal spécifié
    Wire.endTransmission();
}

void setup() {
    Wire.begin(); // Initialiser le bus I2C principal
    Wire.setClock(400000); // Fréquence élevée (400 kHz)
    Serial.begin(9600);
    delay(1000);
    Serial.println("TCA9548A Multiplexer Test");
}

void loop() {
    for (uint8_t canal = 0; canal < 2; canal++) { // Parcours des canaux 0 et 1
        tcaSelect(canal); // Sélectionner le canal du TCA9548A
        Serial.print("Lecture du canal ");
        Serial.println(canal);

        // Exemple : Lecture d'un capteur sur le canal sélectionné
        Wire.beginTransmission(0x20); // Adresse I2C du capteur
        Wire.write(0x00); // Commande ou registre à lire
        Wire.endTransmission();
        Wire.requestFrom(0x20, 2); // Lire 2 octets
        if (Wire.available() == 2) {
            int data = Wire.read() << 8 | Wire.read();
            Serial.print("Donnée lue : ");
            Serial.println(data);
        } else {
            Serial.println("Aucune donnée disponible.");
        }

        delay(500);
    }
}
