/**
 * 
 * e-mail : rachelsysteme@gmail.com
 * gitHub : https://github.com/RS-malik-el
 * Donation : paypal.me/RachelSysteme
 *
 * @AUTEUR : @OpenProgramming
 * DATE : 21/03/2023
 * 
 * @Board : Arduino
 * 
*/

//#define DECODE_NEC // Protocole utilisé
#include <IRremote.h>

#define PIN_IR_REC 2 // Pin reception infrarouge
#define LED_1      3 // Pin led 1 
#define LED_2      4 // Pin led 2
#define LED_3      5 // Pin led 3
#define LED_4      6 // Pin led 4

#define _REPEAT  0X1 // Valeur flag de répétition (appui maintenu du bouton)

#define CMD_1   0xF30CFF00 // Touche 1 de la télécommande
#define CMD_2   0xE718FF00 // Touche 2 de la télécommande
#define CMD_3   0xA15EFF00 // Touche 3 de la télécommande
#define CMD_4   0xF708FF00 // Touche 4 de la télécommande
 
uint32_t valCmd = 0 ; // Stocke la valeur du signal reçu

// Variables de contrôle de l'états des lampes
bool etat_1 = false; 
bool etat_2 = false;
bool etat_3 = false;
bool etat_4 = false;


void setup(){
  Serial.begin(115200);

  IrReceiver.setReceivePin(PIN_IR_REC);
  IrReceiver.start();
  printActiveIRProtocols(&Serial);
  Serial.println(" ");

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(LED_4, OUTPUT);
}


void loop(){

  if(IrReceiver.decode() == true){
  
    // reception de potentiel bruit ou d'appuis maintenu du bouton
    if (IrReceiver.decodedIRData.protocol == UNKNOWN || IrReceiver.decodedIRData.flags == _REPEAT){
      IrReceiver.resume(); // Préparation pour une nouvelle réception
      return; // fin loop
    }
    
    valCmd = IrReceiver.decodedIRData.decodedRawData; // Stockage de la valeur du signal reçu

    // Affichage des résulats dans le moniteur série
    IrReceiver.printIRResultShort(&Serial);

    IrReceiver.resume(); 

    if (valCmd == CMD_1) {
      etat_1 = not etat_1; 
      digitalWrite(LED_1, etat_1);
    }

    else if (valCmd == CMD_2) {
     etat_2 = not etat_2; 
     digitalWrite(LED_2, etat_2);       
    }

    else if (valCmd == CMD_3) {
      etat_3 = not etat_3;
      digitalWrite(LED_3, etat_3);  
    }

    else if (valCmd == CMD_4) {
      etat_4 = not etat_4;
      digitalWrite(LED_4, etat_4); 
    }
  }

}// Fin loop