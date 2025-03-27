#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <ArduinoBLE.h>
#include "Pression125.h"
#include "Pression500.h"
#include "Barometre.h"
#include "Humidite.h"
#include "IMU.h"

// faire bluetooth en multithread 100ms

// Adresses I2C des capteurs
#define ADDR_PRESSION125 0x25
#define ADDR_PRESSION500 0x76

BLEService sensorService("180C"); 
BLECharacteristic commandCharacteristic("2A58", BLEWrite, 1);   // Commande du PC (1 = démarrer, 0 = arrêter)

// Création des instances des capteurs
Pression125 capteur125;
Pression500 capteur500;
Barometre barometre;
Humidite humidite;
CapteursIMU imu;

bool isAcquisitionRunning = false; // État de l'acquisition
const int chipSelect = 10;  // Broche CS pour le module microSD
File myFile;

String toPrint = "";
String buffer[10];
int bufferIndex = 0;

void setup() {
  delay(5000); // temps de sécurité pour que les condensateurs se chargent

  Serial.begin(115200);

  toPrint.reserve(700); // reserve 700 octets dans la memoire
  for (int i = 0; i < 10; i++) {
    buffer[i].reserve(100);
  }
  Wire.begin();  // Initialiser le bus I2C
  delay(100);

  // Initialisation du capteur Pression125
  Wire.beginTransmission(ADDR_PRESSION125);
  Wire.endTransmission();
  if (!capteur125.init(ADDR_PRESSION125)) {
    Serial.println("Échec de l'initialisation du capteur Pression125 !");
  }

  delay(200);

  // Initialisation du capteur Pression500
  Wire.beginTransmission(ADDR_PRESSION500);
  Wire.endTransmission();
  if (!capteur500.init()) {  // Initialisation avec l'adresse I2C du 500Pa
    Serial.println("Échec de l'initialisation du capteur Pression500 !");
  }

  delay(50);

  if (!barometre.init()) { // Remplacez 0x25 par l'adresse I2C réelle de votre capteur
    Serial.println("Échec de l'initialisation du barometre !");
  }

  delay(50);
  
  if (!humidite.init()) {
    Serial.println("Échec de l'initialisation du humidite !");
  }

  delay(50);
  
  if (!imu.init()) {
    Serial.println("Échec de l'initialisation du IMU !");
  }
  //imu.recalibrer(); // Recalibrage initial

  delay(50);

  // Initialisation de la carte SD
  if (!SD.begin(chipSelect)) {
    Serial.println("Échec de l'initialisation de la carte SD!");
  }

  //barometre.lireTemperature(); // probleme avec le baro
  delay(50);

  float moyTemperature = (humidite.lireTemperature() + capteur125.lireTemperature() + capteur500.lireTemperature() + barometre.lireTemperature()) / 4;
  float pressionBarometre = barometre.lirePression();
  float humiditeHumidite = humidite.lireHumidite();

  float rohAir = (pressionBarometre*1000*0.029)/(8.31*(moyTemperature+273.15)); // environ 1020mbar

  myFile = SD.open("data.txt", FILE_WRITE);
  if (myFile) {
    // Écrire les données sous forme brute
    myFile.print("MoyTemperature (°C)"); myFile.print(";"); myFile.print(moyTemperature); myFile.print(";");
    myFile.print("PressionBarometre (kPa)"); myFile.print(";"); myFile.print(pressionBarometre); myFile.print(";");
    myFile.print("Humidite (%)"); myFile.print(";"); myFile.print(humiditeHumidite); myFile.print(";");
    myFile.print("roh_air (kg/m3)"); myFile.print(";"); myFile.println(rohAir);
    myFile.println("Timestamp (ms);P125 (Pa);P500 (Pa);"
                   "Ax (m/s²);Ay (m/s²);Az (m/s²);Gx (°/s);Gy (°/s);Gz (°/s);"
                   "Mx (µT);My (µT);Mz (µT)");
    myFile.close(); // Fermer le fichier
  } else {
    //Serial.println("Erreur d'ouverture du fichier!");
  }

  delay(50);

  BLE.setLocalName("Nano33BLE");
  BLE.setAdvertisedService(sensorService);

  // Bluetooth
  if (!BLE.begin()) {
    Serial.println("Erreur lors de l'initialisation du BLE !");
  }

  // Ajouter les caractéristiques au service
  sensorService.addCharacteristic(commandCharacteristic);
  BLE.addService(sensorService);

  BLE.advertise();
  Serial.println("BLE actif, en attente de connexion...");

  delay(50);

  Serial.print("Temperature125 ");
  Serial.println(capteur125.lireTemperature());
  Serial.print("Temperature500 ");
  Serial.println(capteur500.lireTemperature());

  Serial.println(" ");
  Serial.println("START");
  Serial.println(" ");

  // Quand y'a une echec ça ne veux pas forcement dire que sa marche pas T_T
}

void loop() {
  BLEDevice central = BLE.central();

  if (central) {
    Serial.println("Connecté à un périphérique !");
    while (central.connected()) {
        // Vérifie si une commande a été reçue
        if (commandCharacteristic.written()) {
          uint8_t command;
          commandCharacteristic.readValue(&command, 1); // Lire la valeur de la commande
          isAcquisitionRunning = (command == 1);
          Serial.println(isAcquisitionRunning ? "Acquisition démarrée" : "Acquisition arrêtée");
        }
        if (isAcquisitionRunning) {
          aquisition();
        }
      }
    }
  if (isAcquisitionRunning) {
        aquisition();
  }
}

void aquisition() {
  // Lire les données des capteurs
  float ax, ay, az, gx, gy, gz, mx, my, mz;
  float pression125 = capteur125.lirePression(); // prend 2ms
  float pression500 = capteur500.lirePression(); // prend 62ms

  imu.lireDonnees(ax, ay, az, gx, gy, gz, mx, my, mz); // prend 13.5ms

  // Obtenir le temps depuis le démarrage
  unsigned long timestamp = millis();

  // Construire la ligne de données
  String toPrint = String(timestamp) + ";" + String(pression125) + ";" + String(pression500)
                 + ";" + String(ax) + ";" + String(ay) + ";" + String(az)
                 + ";" + String(gx) + ";" + String(gy) + ";" + String(gz)
                 + ";" + String(mx) + ";" + String(my) + ";" + String(mz);

  // Ajouter la ligne au buffer
  buffer[bufferIndex] = toPrint;
  bufferIndex++;

  // Si le buffer est plein (10 lignes)
  if (bufferIndex == 10) {
    // Ouvrir le fichier en mode écriture
    myFile = SD.open("data.txt", FILE_WRITE);
    if (myFile) {
      // Écrire toutes les lignes du buffer dans le fichier
      for (int i = 0; i < 10; i++) {
        myFile.println(buffer[i]);
      }
      myFile.close(); // Fermer le fichier
    } else {
      //Serial.println("Erreur d'ouverture du fichier!");
    }

    // Réinitialiser le buffer
    bufferIndex = 0;
  }

  //Serial.println(timestamp);
  //Serial.print(" pression125 ");
  //Serial.print(pression125);
  //Serial.print(" pression500 ");
  //Serial.println(pression500);
}