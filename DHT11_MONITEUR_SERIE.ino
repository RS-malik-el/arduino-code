/*
 *AUTEUR: RACHEL SYSTEME
 *DATE  : 15 FEVRIER 2022
 *
 ***Lire et afficher la température et l'humidité sur le moniteur série
 */

#include <DHT.h>

#define dht_pin 2 

// Déclaration de l'objet de type DHT
DHT dht(dht_pin,DHT11);

// Variables de stockage des données
float temperature = 0;
float humidity = 0;

void setup() {
  Serial.begin(9600);// initialisation de la communcation série
  dht.begin();//initialisation du capteur
  Serial.println("CAPTEUR DHT11");
}

void loop() {
  temperature = dht.readTemperature();
    Serial.print("TEMPERATURE : ");
    Serial.print(temperature);
    Serial.println(" °C");

  humidity = dht.readHumidity();
    Serial.print("HUMIDITY : ");
    Serial.print(humidity);
    Serial.println("%");

  Serial.println("");
  delay(1000);
}
