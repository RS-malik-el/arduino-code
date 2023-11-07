/**
 * 
 * e-mail : openprogramming23@gmail.com
 
 * gitHub : https://github.com/RS-malik-el
 *
 * @AUTEUR : Exaucé KIMBEMBE / @OpenProgramming
 * DATE : 06/11/2023
 * 
 * @Board : arduino
 * 
 * Le code permet de gérer les événements d'un bouton poussoir à l'aide de
 * la bibliothèque AceButton. Il est configuré pour détecter plusieurs types
 * d'événements tels que le clic simple, le double clic, la pression longue et
 * la répétition de clics. Ce code a été testé sur une carte Arduino et peut ne
 * pas fonctionner correctement sur d'autres types de cartes.
 * 
*/

#ifndef __AVR__
  #error Ce code a été tester sur une carte arduino et peux ne pas bien fonctionner sur un autre type de carte.
#endif

#include <AceButton.h>
#include <LiquidCrystal_I2C.h>

// Message à afficher sur l'écran lcd i2c
#define MSG_SENSOR_STATE   "  SENSOR STATE  "
#define MSG_CLICK_DETECTED " CLICK DETECTED "
#define MSG_DOUBLE_CLICK   "  DOUBLE CLICK  "
#define MSG_LONG_PRESS     "   LONG PRESS   "
#define MSG_RELEASED       "    RELEASED    "

using namespace ace_button;

#define PIN_BOUTON  3  // Pin du bouton poussoir

AceButton button(PIN_BOUTON,false);  // Création d'un objet AceButton pour le bouton
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Adresse I2C de l'écran LCD

uint8_t key_value = AceButton::kEventReleased;

// Prototype de la fonction
void gestionBouton(AceButton* button, uint8_t eventType, uint8_t buttonState);


void setup() {
  Serial.begin(115200); // Initialisation de la communication série
  Serial.println("Toucher le capteur\n");
  // Configuration de l'écran LCD I2C
  lcd.init();                     
  lcd.backlight();                 
  lcd.clear(); 
  lcd.setCursor(0,0);
  lcd.print("     WELCOME    ");  
  lcd.setCursor(0,1);
  lcd.print("@OPENPROGRAMMING");

  pinMode(PIN_BOUTON, INPUT_PULLUP); // Configuration du bouton poussoir en entrée

  // Configuration du bouton
  ButtonConfig* buttonConfig = button.getButtonConfig();
  buttonConfig->setEventHandler(gestionBouton);
  buttonConfig->setFeature(ButtonConfig::kFeatureClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureDoubleClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureLongPress);
  buttonConfig->setFeature(ButtonConfig::kFeatureSuppressAll);
  //buttonConfig->setFeature(ButtonConfig::kFeatureSuppressAfterClick);
  //buttonConfig->setFeature(ButtonConfig::kFeatureSuppressAfterLongPress);
  //buttonConfig->setFeature(ButtonConfig::kFeatureSuppressAfterDoubleClick);
  //buttonConfig->setFeature(ButtonConfig::kFeatureSuppressClickBeforeDoubleClick);

   delay(3000);
}


void loop() {
  lcd.setCursor(0,0);
  lcd.print(MSG_SENSOR_STATE); 

  if(key_value == AceButton::kEventReleased){
    lcd.setCursor(0,1);
   	lcd.print(MSG_RELEASED);
  }
  else{
    delay(1000);
    key_value = AceButton::kEventReleased;
  }
     
  button.check();
}


// Fonction de rappel pour le bouton
void gestionBouton(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventClicked:
      Serial.println(MSG_CLICK_DETECTED);
      lcd.setCursor(0,1);
   	  lcd.print(MSG_CLICK_DETECTED);
      key_value = AceButton::kEventClicked;
      break;
    case AceButton::kEventDoubleClicked:
      Serial.println(MSG_DOUBLE_CLICK);
      lcd.setCursor(0,1);
   	  lcd.print(MSG_DOUBLE_CLICK);
      key_value = AceButton::kEventDoubleClicked;
      break;
    case AceButton::kEventLongPressed:
      Serial.println(MSG_LONG_PRESS);
      lcd.setCursor(0,1);
   	  lcd.print(MSG_LONG_PRESS);
      key_value = AceButton::kEventLongPressed;
      break;
  }
}