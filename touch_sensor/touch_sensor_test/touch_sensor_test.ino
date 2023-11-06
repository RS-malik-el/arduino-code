/**
 * @email : openprogramming23@gmail.com
 * @Auteur : Exaucé KIMBEMBE
 * @Date : 06/11/2023
 * 
 *@Board : ARDUINO 
 * 
*/
#include <LiquidCrystal_I2C.h>

// Message à afficher sur l'écran lcd i2c
#define MSG_0       "  SENSOR STATE  "
#define MSG_TOUCH   "PRESSES DETECTED"
#define MSG_RELEASE " PRESS RELEASED "

#define TOUCH_PIN 3 // Broche du capteur tactile 

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adresse I2C de l'écran LCD

void setup() {
  // Configuration de l'écran LCD I2C
  lcd.init();                     
  lcd.backlight();                 
  lcd.clear(); 
  lcd.setCursor(0,0);
  lcd.print("WELCOME");  
  lcd.setCursor(0,1);
  lcd.print("@OPENPROGRAMMING");  

  // Configuration des pins
  pinMode(TOUCH_PIN, INPUT);  

  delay(3000); 
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print(MSG_0); 

  if (digitalRead(TOUCH_PIN)==true) {
    lcd.setCursor(0,1);
    lcd.print(MSG_TOUCH);  
  } else {
    lcd.setCursor(0,1);
    lcd.print(MSG_RELEASE);  
  }
}