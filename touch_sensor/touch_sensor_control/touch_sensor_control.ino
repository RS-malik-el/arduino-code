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
#define MSG_0 " BLINKING SPEED "

// Pins utiliser
#define TOUCH_PIN 3 // Broche du capteur tactile 
#define LED_PIN   4 // Broche de connexion de la led

// Temps de clignotement en ms
#define ATTENTE_MIN 100  
#define ATTENTE_MAX 2000
#define VAL_INCRE   100 // Valeur d'incréméntation

LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adresse I2C de l'écran LCD

unsigned long prev_t = millis();
int attente = ATTENTE_MIN;
bool state = true; // Etat de la led

void setup() {
  // Configuration de l'écran LCD I2C
  lcd.init();                     
  lcd.backlight();                 
  lcd.clear(); 
  lcd.setCursor(0,0);
  lcd.print("    WELCOME     ");  
  lcd.setCursor(0,1);
  lcd.print("@OPENPROGRAMMING");  

  // Configuration des pins
  pinMode(TOUCH_PIN, INPUT);   
  pinMode(LED_PIN, OUTPUT); 
  digitalWrite(LED_PIN,state);

  delay(3000);

  // Mise a jour de l'ecran lcd
  lcd.setCursor(0,1);
  lcd.print("Delay : "+String(attente)+" ms         "); 
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print(MSG_0); 

  // Incrémentation de l'attente
  if (digitalRead(TOUCH_PIN)==true){
    delay(100);
    if (digitalRead(TOUCH_PIN)==true){return 0;}

    attente+=VAL_INCRE; // incrémentation de la variable

    // Remise à la valaur minimum 
    if(attente > ATTENTE_MAX){attente = ATTENTE_MIN;}

    // Mise a jour de l'ecran lcd
    lcd.setCursor(0,1);
    lcd.print("Delay : "+String(attente)+" ms         ");  
  }

  // Clignotement de la led
  if((millis()-prev_t)>=attente){
    state = not state;
    digitalWrite(LED_PIN,state);
    prev_t = millis();
  }
}