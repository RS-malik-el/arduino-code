/**
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 * 
 * @AUTHEUR : RACHEL SYSTEME
 * DATE : 20/08/2021
 * 
 * @Board : arduino Uno
 * 
 * Ce programme propose une utilisation de la fonction millis():
 *  *millis() est une fonction qui renvois le temps écoulé depuis la mise sous tension de la carte.
 *  *comparer à la fonction "delay", "millis" est une fonction non-bloquante.
 * 
 *  *Dans ce programme nous allons nous servir des valeurs renvoyé par la fonction "millis" afin de
 *  faire un ensemble de 3 LEDS ensemble puis de façon individuelle.
 * 
 * Merci de bien vouloir vous abonnez à la chaîne et de la partager s'il vous plaît !!!
**/

const byte pin_led[3] = {2, 3, 4}; // pins auquels sont connecté les leds
bool etat = false;                 // variable de changement d'état de la led
byte indice_led = 0;               // indice de la led dans le tableau (utilisé pour le clignotement individuel)

unsigned long temps_depart = millis(); // temps initial de référence
const int dure_clignotage = 250;       // temps de clignotement
const int dure_1 = 5000;               // temps pris pour la séquence de clignotement d'ensemble
const int dure_2 = 10000;              // temps pris pour la séquence de clignotement individuel

unsigned long attente_1 = millis() + dure_1; // temps d'attente avant passage à la séquence de clignotement individuel
unsigned long attente_2 = attente_1 + dure_2;// temps d'attente avant passage à la séquence de clignotement d'ensemble

// prototypes des fonctions
void tout_clignote(void);  
void clignote_solo(void);
void update(void); 

// programme initial
void setup() {
  // pins définit comme sortie
  for(byte i = 0; i <= 2; i++ ){
    pinMode(pin_led[i],OUTPUT);
    digitalWrite(pin_led[i], etat);
  }
}

// programme principal
void loop() {
  // appel aux fonctions
  tout_clignote();  
  clignote_solo();
  update();    
}

// fonction permettant de faire clignoter toutes les leds
void tout_clignote(){
  if(millis() <= attente_1){
      if( (millis() - temps_depart) >= dure_clignotage){
        etat = !etat;
        for(byte i = 0; i <= 2; i++){
          digitalWrite(pin_led[i],etat);
        }
      temps_depart = millis();
    }
  }
}

// fonction permettant de faire clignoter à tout de rôle
void clignote_solo(){
  if(millis() >= attente_1 && millis() <= attente_2){
    // Allumage de la led
    if( (millis() - temps_depart) <= dure_clignotage)
      digitalWrite(pin_led[indice_led],HIGH);
    // Extinction de la led
    if( (millis()-temps_depart) >= dure_clignotage &&
        (millis() - temps_depart) <= dure_clignotage*2)
    {
      digitalWrite(pin_led[indice_led],LOW);
    }           

    // mise à jour du temps de départ et implémentation de l'indice des positions des leds
    if((millis() - temps_depart) >= dure_clignotage*2){
      temps_depart = millis();  // mise à jour du temps de départ
      indice_led++;             // impléméntation
      indice_led %= 3;   // indice_led sera remis à 0 à chaque fois que la valeur incrémentée sera égale à 3
    }    
  }
}

// fonction permettant de mettre à jour le temps de passage de chaque
// séquence de clignotement 
void update(){
  if(millis() >= attente_2){
    attente_1 = millis() + dure_1;
    attente_2 = attente_1 + dure_2;
  }    
}
