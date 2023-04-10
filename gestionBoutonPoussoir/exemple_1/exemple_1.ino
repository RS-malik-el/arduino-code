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
 * Ce code est conçu pour détecter les pressions et les relâchements d'un bouton
 * poussoir, en utilisant la bibliothèque AceButton. Il allume également une LED
 * connectée sur une broche de sortie en fonction de l'état du bouton. Assurez-vous
 * d'utiliser ce code sur une carte Arduino compatible, car il peut ne pas bien
 * fonctionner sur d'autres types de cartes.
 * 
*/

#ifndef __AVR__
  #error Ce code a été tester sur une carte arduino et peux ne pas bien fonctionner sur un autre type de carte.
#endif

#include <AceButton.h>

using namespace ace_button;

#define PIN_BOUTON  2   // Pin du bouton poussoir
#define PIN_LED     13  // Pin de la LED

AceButton button(PIN_BOUTON);  // Création d'un objet AceButton pour le bouton

// Prototype de la fonction
void gestionBouton(AceButton* button, uint8_t eventType, uint8_t buttonState);


void setup() {
  
  Serial.begin(115200); // Initialisation de la communication série
  Serial.println("Appuyer sur le bouton poussoir\n");

  pinMode(PIN_LED, OUTPUT);  // Configuration de la broche LED en sortie
  pinMode(PIN_BOUTON, INPUT_PULLUP); // Configuration du bouton poussoir en entrée

  button.setEventHandler(gestionBouton);  // Définition de la fonction de rappel pour le bouton
}


void loop() {
  button.check();
}


// Fonction de rappel pour le bouton
void gestionBouton(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("Le bouton est pressé");
      digitalWrite(PIN_LED, not buttonState);
      break;
    case AceButton::kEventReleased:
      Serial.println("Le bouton est relaché");
      digitalWrite(PIN_LED, not buttonState);
      break;
  }
}