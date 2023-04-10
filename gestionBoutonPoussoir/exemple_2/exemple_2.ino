/**
 * 
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 *
 * @AUTEUR : Exaucé KIMBEMBE / @OpenProgramming
 * DATE : 09/04/2023
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

using namespace ace_button;

#define PIN_BOUTON  2  // Pin du bouton poussoir

AceButton button(PIN_BOUTON);  // Création d'un objet AceButton pour le bouton

// Prototype de la fonction
void gestionBouton(AceButton* button, uint8_t eventType, uint8_t buttonState);


void setup() {
  
  Serial.begin(115200); // Initialisation de la communication série
  Serial.println("Appuyer sur le bouton poussoir\n");

  pinMode(PIN_BOUTON, INPUT_PULLUP); // Configuration du bouton poussoir en entrée

  // Configuration du bouton
  ButtonConfig* buttonConfig = button.getButtonConfig();
  buttonConfig->setEventHandler(gestionBouton);
  buttonConfig->setFeature(ButtonConfig::kFeatureClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureDoubleClick);
  buttonConfig->setFeature(ButtonConfig::kFeatureLongPress);
  buttonConfig->setFeature(ButtonConfig::kFeatureRepeatPress);
  //buttonConfig->setFeature(ButtonConfig::kFeatureSuppressAll);
  //buttonConfig->setFeature(ButtonConfig::kFeatureSuppressAfterClick);
  //buttonConfig->setFeature(ButtonConfig::kFeatureSuppressAfterLongPress);
  //buttonConfig->setFeature(ButtonConfig::kFeatureSuppressAfterDoubleClick);
  //buttonConfig->setFeature(ButtonConfig::kFeatureSuppressClickBeforeDoubleClick);
}


void loop() {
  button.check();
}


// Fonction de rappel pour le bouton
void gestionBouton(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventClicked:
      Serial.println("Le bouton est cliqué");
      break;
    case AceButton::kEventDoubleClicked:
      Serial.println("Le bouton est cliqué 2 fois");
      break;
    case AceButton::kEventLongPressed:
      Serial.println("Le bouton est pressé longtemps");
      break;
    case AceButton::kEventRepeatPressed:
      Serial.println("Le cliqué est répété");
      break;
  }
}