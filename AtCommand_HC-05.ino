/*
	Ce programme permet de configurer le module bluetooth HC-05/06
	
 *** AUTEUR : RACHEl SYSTEME
 *** DATE   : 11 / 03 / 2022
 *** YOUTUBE: https://www.youtube.com/channel/UCf4jGfp-BFp6GLd6eTptVMg?sub_confirmation=1

 *** Liste AT COMMAND : https://s3-sa-east-1.amazonaws.com/robocore-lojavirtual/709/HC-05_ATCommandSet.pdf

 NB:
 	Rassurez - vous d'activer le mode commande du module bluetooth
 	lors de sa mise sous tension. Appuyer sur le bouton se trouvant
 	sur le module bluetooth avant sa mise sous tension et le maintenir
	pendant la mise sous tension puis le relacher après quelque seconde.
	La led du module bluetooth clignotera très lentement indiquant ainsi
	que le module bluetooth est en mode commande. 
*/

#include <SoftwareSerial.h>

#define _RX 10
#define _TX 11

// Création de l'objet SoftwareSerial
SoftwareSerial mySerial(_RX,_TX);

void setup(){
  // Initialisation de la communication Série
  Serial.begin(9600);
  /*
  	*** Initialisation de la communication SoftwareSerial
  	*** En mode commande, la vitèsse d'échange du HC-05 / HC-06
  	*** est de 38400
  */
  mySerial.begin(38400); 
  Serial.println("Saisir AT commands :");
}

void loop(){
  /*
  	 *** Vérification des caractères en attende via la liason SoftwareSerial
  	 *** S'il y a les caractères en attente, on l'affiche dans le moniteur série 
  */
	if (mySerial.available())
    	Serial.write(mySerial.read());
 	/*
  	 *** Vérification des caractères en attende via la liason Serial
  	 *** S'il y a les caractères en attente, on les transmet au module bluetooth
  */
 	if (Serial.available())
    	mySerial.write(Serial.read());
}
