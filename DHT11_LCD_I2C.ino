/*
 *AUTEUR: RACHEL SYSTEME
 *DATE  : 15 FEVRIER 2022
 *
 ***Lire et afficher la température et l'humidité sur un écran LCD I2C
 */
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define dht_pin 2 

// Déclaration de l'objet de type DHT
DHT dht(dht_pin,DHT11);

// Déclaration de l'objet de type LiquidCrystal_I2C
LiquidCrystal_I2C lcd(0x27,16,2);

float temperature = 0;
float humidity = 0;

// Création d'un caractère personalisé "°"
byte deg[8]={
  B00110,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup() {
  dht.begin();//initialisation du capteur
  //initialisation de l'écran I2C
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.createChar(0,deg);

  lcd.setCursor(0,0);
  lcd.print("TEMP: ");
  lcd.setCursor(0,1);
  lcd.print("HUMIDITY:");
}

void loop() {
  temperature = dht.readTemperature();
    lcd.setCursor(6,0);
    lcd.print(temperature);
    lcd.write(0);
    lcd.print("C");

  humidity = dht.readHumidity();
    lcd.setCursor(10,1);
    lcd.print(humidity);
    lcd.print("%");

  delay(1000);
}
