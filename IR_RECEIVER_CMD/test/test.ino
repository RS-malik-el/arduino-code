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
#define _REPEAT  0X1 // Valeur flag de répétition (appui maintenu du bouton)

void setup(){
  Serial.begin(115200);

  IrReceiver.setReceivePin(PIN_IR_REC);
  IrReceiver.start();
  printActiveIRProtocols(&Serial);
  Serial.println(" ");
}


void loop(){

  if(IrReceiver.decode() == true){
  
    // reception de potentiel bruit ou d'appuis maintenu du bouton
    if (IrReceiver.decodedIRData.protocol == UNKNOWN || IrReceiver.decodedIRData.flags == _REPEAT){
      IrReceiver.resume(); // Préparation pour une nouvelle réception
      return; // fin loop
    }
    
    // Affichage des résulats dans le moniteur série
    IrReceiver.printIRResultShort(&Serial);
    Serial.print("\nAdresse : 0x");
    Serial.println(IrReceiver.decodedIRData.address);
    Serial.print("Commande : 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);
    Serial.print("Valeur du signal : 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    Serial.println(String(IrReceiver.decodedIRData.numberOfBits) + " Bits\n\n");
    
    IrReceiver.resume(); // Préparation pour une nouvelle réception
  }

}// Fin loop